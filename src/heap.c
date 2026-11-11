#include "heap.h"

#include <nitro.h>
#include <stdarg.h>
#include <string.h>

#include "error_message_reset.h"
#include "unk_020366A0.h"

typedef struct HeapInfo {
    NNSFndHeapHandle *heapHandles;
    NNSFndHeapHandle *parentHeapHandles;
    void **subHeapRawPtrs;
    u16 *numMemBlocks;
    u8 *heapIdxs;
    u16 totalNumHeaps;
    u16 nTemplates;
    u16 maxHeaps;
    u16 unallocatedHeapID;
} HeapInfo;

typedef struct MemoryBlock {
    u8 filler_00[12];
    u32 heapID : 8;
    u32 filler_0D : 24;
} MemoryBlock;

static HeapInfo sHeapInfo;

static BOOL CreateHeapInternal(enum HeapID parent, enum HeapID child, u32 size, s32 alignment);

void Heap_InitSystem(const HeapParam *templates, u32 nTemplates, u32 totalNumHeaps, u32 preSize)
{
    void *ptr;
    u32 i;
    u32 usableHeaps = nTemplates + 24;

    if (totalNumHeaps < usableHeaps) {
        totalNumHeaps = usableHeaps;
    }

    if (preSize != 0) {
        // force align
        while (preSize % 4 != 0) {
            preSize++;
        }
        OS_AllocFromMainArenaLo(preSize, 4);
    }

    sHeapInfo.heapHandles = OS_AllocFromMainArenaLo(
        (usableHeaps + 1) * sizeof(NNSFndHeapHandle)
            + usableHeaps * sizeof(NNSFndHeapHandle)
            + usableHeaps * sizeof(void *)
            + totalNumHeaps * sizeof(u16)
            + totalNumHeaps,
        4);
    sHeapInfo.parentHeapHandles = sHeapInfo.heapHandles + (usableHeaps + 1);
    sHeapInfo.subHeapRawPtrs = (void **)(sHeapInfo.parentHeapHandles + usableHeaps);
    sHeapInfo.numMemBlocks = (u16 *)(sHeapInfo.subHeapRawPtrs + usableHeaps);
    sHeapInfo.heapIdxs = (u8 *)(sHeapInfo.numMemBlocks + totalNumHeaps);
    sHeapInfo.totalNumHeaps = (u16)totalNumHeaps;
    sHeapInfo.nTemplates = (u16)nTemplates;
    sHeapInfo.unallocatedHeapID = (u16)usableHeaps;
    sHeapInfo.maxHeaps = (u16)usableHeaps;

    for (i = 0; i < nTemplates; i++) {
        switch (templates[i].arena) {
        case OS_ARENA_MAIN:
        default:
            ptr = OS_AllocFromMainArenaLo(templates[i].size, 4);
            break;
        case OS_ARENA_MAINEX:
            ptr = OS_AllocFromMainExArenaHi(templates[i].size, 4);
            break;
        }

        if (ptr != NULL) {
            sHeapInfo.heapHandles[i] = NNS_FndCreateExpHeap(ptr, templates[i].size);
            sHeapInfo.heapIdxs[i] = (u8)i;
        } else {
            GF_ASSERT(FALSE);
        }
    }

    for (i = nTemplates; i < usableHeaps + 1; i++) {
        sHeapInfo.heapHandles[i] = NNS_FND_HEAP_INVALID_HANDLE;
        sHeapInfo.heapIdxs[i] = (u8)sHeapInfo.unallocatedHeapID;
    }

    while (i < totalNumHeaps) {
        sHeapInfo.heapIdxs[i++] = (u8)sHeapInfo.unallocatedHeapID;
    }

    for (i = 0; i < totalNumHeaps; i++) {
        sHeapInfo.numMemBlocks[i] = 0;
    }
}

static s32 FindFirstAvailableHeapHandle(void)
{
    s32 i;

    for (i = sHeapInfo.nTemplates; i < sHeapInfo.maxHeaps; i++) {
        if (sHeapInfo.heapHandles[i] == NNS_FND_HEAP_INVALID_HANDLE) {
            return i;
        }
    }

    return -1;
}

BOOL Heap_Create(enum HeapID parent, enum HeapID child, u32 size)
{
    return CreateHeapInternal(parent, child, size, 4);
}

BOOL Heap_CreateAtEnd(enum HeapID parent, enum HeapID child, u32 size)
{
    return CreateHeapInternal(parent, child, size, -4);
}

static BOOL CreateHeapInternal(enum HeapID parent, enum HeapID child, u32 size, s32 alignment)
{
    GF_ASSERT(OS_GetProcMode() != OS_PROCMODE_IRQ);

    u8 *ptr = sHeapInfo.heapIdxs;
    if (sHeapInfo.unallocatedHeapID == ptr[child]) {
        NNSFndHeapHandle parentHeap = sHeapInfo.heapHandles[ptr[parent]];
        if (parentHeap != NNS_FND_HEAP_INVALID_HANDLE) {
            void *newHeapAddr = NNS_FndAllocFromExpHeapEx(parentHeap, size, alignment);
            if (newHeapAddr != NULL) {
                s32 i = FindFirstAvailableHeapHandle();
                if (i >= 0) {
                    sHeapInfo.heapHandles[i] = NNS_FndCreateExpHeap(newHeapAddr, size);

                    if (sHeapInfo.heapHandles[i] != NNS_FND_HEAP_INVALID_HANDLE) {
                        sHeapInfo.parentHeapHandles[i] = parentHeap;
                        sHeapInfo.subHeapRawPtrs[i] = newHeapAddr;
                        sHeapInfo.heapIdxs[child] = (u8)i;

                        return TRUE;
                    } else {
                        GF_ASSERT(FALSE);
                    }
                } else {
                    GF_ASSERT(FALSE);
                }
            } else {
                GF_ASSERT(FALSE);
            }
        } else {
            GF_ASSERT(FALSE);
        }
    } else {
        GF_ASSERT(FALSE);
    }
    return FALSE;
}

void Heap_Destroy(enum HeapID heapID)
{
    GF_ASSERT(OS_GetProcMode() != OS_PROCMODE_IRQ);

    NNSFndHeapHandle handle = sHeapInfo.heapHandles[sHeapInfo.heapIdxs[heapID]];

    if (handle != NNS_FND_HEAP_INVALID_HANDLE) {
        NNS_FndDestroyExpHeap(handle);

        u8 index = sHeapInfo.heapIdxs[heapID];
        NNSFndHeapHandle parentHeap = sHeapInfo.parentHeapHandles[index];
        void *childRaw = sHeapInfo.subHeapRawPtrs[index];
        if (parentHeap != NNS_FND_HEAP_INVALID_HANDLE && childRaw != NULL) {
            NNS_FndFreeToExpHeap(parentHeap, childRaw);
        } else {
            GF_ASSERT(FALSE);
        }

        sHeapInfo.heapHandles[sHeapInfo.heapIdxs[heapID]] = NULL;
        sHeapInfo.parentHeapHandles[sHeapInfo.heapIdxs[heapID]] = NULL;
        sHeapInfo.subHeapRawPtrs[sHeapInfo.heapIdxs[heapID]] = NULL;

        sHeapInfo.heapIdxs[heapID] = (u8)sHeapInfo.unallocatedHeapID;
    }
}

static void *AllocFromHeapInternal(NNSFndHeapHandle heap, u32 size, s32 alignment, enum HeapID heapID)
{
    GF_ASSERT(heap != NNS_FND_HEAP_INVALID_HANDLE);

    OSIntrMode intrMode = OS_DisableInterrupts();
    size += sizeof(MemoryBlock);
    void *ptr = NNS_FndAllocFromExpHeapEx(heap, size, alignment);

    OS_RestoreInterrupts(intrMode);
    if (ptr != NULL) {
        ((MemoryBlock *)ptr)->heapID = heapID;

        ptr += sizeof(MemoryBlock);
    }

    return ptr;
}

static void AllocFail(void)
{
    if (CommMan_IsInitialized()) {
        ErrorMessageReset_PrintErrorAndReset();
    }
}

void *Heap_Alloc(u32 heapID, u32 size)
{
    void *ptr = NULL;

    if ((u32)heapID < sHeapInfo.totalNumHeaps) {
        u8 index = sHeapInfo.heapIdxs[heapID];
        ptr = AllocFromHeapInternal(sHeapInfo.heapHandles[index], size, 4, heapID);
    }

    if (ptr != NULL) {
        sHeapInfo.numMemBlocks[heapID]++;
    } else {
        AllocFail();
    }

    return ptr;
}

void *Heap_AllocAtEnd(u32 heapID, u32 size)
{
    void *ptr = NULL;

    if ((u32)heapID < sHeapInfo.totalNumHeaps) {
        u8 index = sHeapInfo.heapIdxs[heapID];
        ptr = AllocFromHeapInternal(sHeapInfo.heapHandles[index], size, -4, heapID);
    }

    if (ptr != NULL) {
        sHeapInfo.numMemBlocks[heapID]++;
    } else {
        AllocFail();
    }

    return ptr;
}

void Heap_Free(void *ptr)
{
    ptr -= sizeof(MemoryBlock);
    enum HeapID heapID = (enum HeapID)((MemoryBlock *)ptr)->heapID;

    if ((u32)heapID < sHeapInfo.totalNumHeaps) {
        u8 index = sHeapInfo.heapIdxs[heapID];
        NNSFndHeapHandle heap = sHeapInfo.heapHandles[index];

        GF_ASSERT(heap != NNS_FND_HEAP_INVALID_HANDLE);

        if (sHeapInfo.numMemBlocks[heapID] == 0) {
            GF_heap_c_dummy_return_true(heapID);
        }

        GF_ASSERT(sHeapInfo.numMemBlocks[heapID] != 0);

        sHeapInfo.numMemBlocks[heapID]--;

        OSIntrMode intrMode = OS_DisableInterrupts();
        NNS_FndFreeToExpHeap(heap, ptr);
        OS_RestoreInterrupts(intrMode);
        return;
    }

    GF_ASSERT(FALSE);
}

void Heap_FreeExplicit(u32 heapID, void *ptr)
{
    GF_ASSERT(OS_GetProcMode() != OS_PROCMODE_IRQ);

    if ((u32)heapID < sHeapInfo.totalNumHeaps) {
        u8 index = sHeapInfo.heapIdxs[heapID];
        NNSFndHeapHandle heap = sHeapInfo.heapHandles[index];

        GF_ASSERT(heap != NNS_FND_HEAP_INVALID_HANDLE);

        ptr -= sizeof(MemoryBlock);
        GF_ASSERT(((MemoryBlock *)ptr)->heapID == heapID);

        NNS_FndFreeToExpHeap(heap, ptr);
        GF_ASSERT(sHeapInfo.numMemBlocks[heapID] != 0);
        sHeapInfo.numMemBlocks[heapID]--;
        return;
    }

    GF_ASSERT(FALSE);
}

u32 HeapExp_FndGetTotalFreeSize(u32 heapID)
{
    if ((u32)heapID < sHeapInfo.totalNumHeaps) {
        u8 index = sHeapInfo.heapIdxs[heapID];
        return NNS_FndGetTotalFreeSizeForExpHeap(sHeapInfo.heapHandles[index]);
    }

    GF_ASSERT(FALSE);
    return 0;
}

static void HeapDebug_DesmumeLog(char *s)
{
    asm("swi 0xFC");
}

void HeapDebug_Log(const char *fmt, ...)
{
    char s[256];
    va_list va;

    va_start(va, fmt);
    OS_VSNPrintf(s, sizeof(s), fmt, va);
    va_end(va);

    HeapDebug_DesmumeLog(s);
}

static u32 sField1Low;
static u32 sFollowerLow;

void HeapDebug_ResetFieldLows(void)
{
    sField1Low = 0xFFFFFFFF;
    sFollowerLow = 0xFFFFFFFF;
    HeapDebug_Log("[heap] field load: APPLICATION free %u\n", HeapExp_FndGetTotalFreeSize(HEAP_ID_APPLICATION));
}

void HeapDebug_LogFieldLows(void)
{
    u32 field1 = HeapExp_FndGetTotalFreeSize(HEAP_ID_FIELD1);
    u32 follower = HeapExp_FndGetTotalFreeSize(HEAP_ID_FOLLOWER);

    if (field1 < sField1Low || follower < sFollowerLow) {
        sField1Low = field1 < sField1Low ? field1 : sField1Low;
        sFollowerLow = follower < sFollowerLow ? follower : sFollowerLow;
        HeapDebug_Log("[heap] new low: FIELD1 free %u (low %u) | FOLLOWER free %u (low %u)\n", field1, sField1Low, follower, sFollowerLow);
    }
}

BOOL Heap_CanAlloc(u32 heapID, u32 size)
{
    if ((u32)heapID >= sHeapInfo.totalNumHeaps) {
        return FALSE;
    }

    NNSFndHeapHandle heap = sHeapInfo.heapHandles[sHeapInfo.heapIdxs[heapID]];

    if (heap == NNS_FND_HEAP_INVALID_HANDLE) {
        return FALSE;
    }

    return NNS_FndGetAllocatableSizeForExpHeapEx(heap, 4) >= size + sizeof(MemoryBlock);
}

void HeapExp_FndInitAllocator(NNSFndAllocator *pAllocator, u32 heapID, int alignment)
{
    if ((u32)heapID < sHeapInfo.totalNumHeaps) {
        u8 index = sHeapInfo.heapIdxs[heapID];
        NNS_FndInitAllocatorForExpHeap(pAllocator, sHeapInfo.heapHandles[index], alignment);
        return;
    }

    GF_ASSERT(FALSE);
}

void Heap_Realloc(void *ptr, u32 newSize)
{
    GF_ASSERT(OS_GetProcMode() != OS_PROCMODE_IRQ);

    newSize += sizeof(MemoryBlock);
    ptr -= sizeof(MemoryBlock);

    if (NNS_FndGetSizeForMBlockExpHeap(ptr) >= newSize) {
        u32 heapID = ((MemoryBlock *)ptr)->heapID;
        u8 index = sHeapInfo.heapIdxs[heapID];

        NNS_FndResizeForMBlockExpHeap(sHeapInfo.heapHandles[index], ptr, newSize);
        return;
    }
    GF_ASSERT(FALSE);
}

BOOL GF_heap_c_dummy_return_true(u32 heapID)
{
    return TRUE;
}
