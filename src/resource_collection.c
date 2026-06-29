#include "resource_collection.h"

#include <nitro.h>
#include <string.h>

#include "constants/heap.h"

#include "heap.h"
#include "system.h"

#define RESOURCE_ID_INVALID (-1)

// --- Dedicated bank-D texture-image VRAM region for large overworld sprites ---
//
// The overworld maps banks A+B (256 KB) as texture slots 0-1, managed by the
// shared NNS Lnk manager; map geometry + every billboard compete for it. Large
// 64x64 sprites (e.g. Giratina-Origin followers, ~16 KB each) can exhaust it
// when many small sprites are also resident. To let large and small coexist,
// fieldmap.c maps the otherwise-unused bank D as texture slot 2 (base address
// 0x40000), and large texture allocations are routed here instead of into the
// shared pool. The NNS manager never touches slot 2, so the two never collide.
//
// Bank D is also borrowed by the legendary/mythical encounter motion-blur effect
// (encounter_effect.c remaps texture to bank A only during the effect); the
// follower is hidden during encounters and respawns with a fresh texture upload
// afterwards, so no re-upload hook is needed here.
//
// Layout: 4 fixed 32 KB slots. Covers up to four concurrent large sprites of
// <= 32 KB each (a 16-colour 64x64 16-frame sheet is exactly 32 KB).
#define BANK_D_TEX_BASE          0x40000 // texture-image address of slot 2 (bank D)
#define BANK_D_SLOT_SIZE         0x8000  // 32 KB per slot
#define BANK_D_SLOT_COUNT        4       // 4 * 32 KB = 128 KB (all of bank D)
#define LARGE_TEX_VRAM_THRESHOLD 0x3000  // texSize > 12 KB routes to bank D

static BOOL sBankDSlotUsed[BANK_D_SLOT_COUNT];

void LargeSpriteVram_ResetBankD(void)
{
    for (int i = 0; i < BANK_D_SLOT_COUNT; i++) {
        sBankDSlotUsed[i] = FALSE;
    }
}

static NNSGfdTexKey BankD_AllocTexVram(u32 size)
{
    if (size > BANK_D_SLOT_SIZE) {
        return NNS_GFD_ALLOC_ERROR_TEXKEY;
    }

    size = NNSi_GfdGetTexKeyRoundupSize(size);

    for (int i = 0; i < BANK_D_SLOT_COUNT; i++) {
        if (!sBankDSlotUsed[i]) {
            sBankDSlotUsed[i] = TRUE;
            return NNS_GfdMakeTexKey(BANK_D_TEX_BASE + i * BANK_D_SLOT_SIZE, size, FALSE);
        }
    }

    return NNS_GFD_ALLOC_ERROR_TEXKEY;
}

static BOOL BankD_OwnsTexKey(NNSGfdTexKey key)
{
    if (key == NNS_GFD_ALLOC_ERROR_TEXKEY) {
        return FALSE;
    }

    u32 addr = NNS_GfdGetTexKeyAddr(key);
    return addr >= BANK_D_TEX_BASE && addr < BANK_D_TEX_BASE + (BANK_D_SLOT_COUNT * BANK_D_SLOT_SIZE);
}

static int BankD_FreeTexVram(NNSGfdTexKey key)
{
    int slot = (NNS_GfdGetTexKeyAddr(key) - BANK_D_TEX_BASE) / BANK_D_SLOT_SIZE;

    if (slot >= 0 && slot < BANK_D_SLOT_COUNT && sBankDSlotUsed[slot]) {
        sBankDSlotUsed[slot] = FALSE;
        return 0;
    }

    return 1;
}

static Resource *ResourceCollection_AllocResource(ResourceCollection *collection);
static void Resource_Init(Resource *resource);
static TextureResource *TextureResourceManager_AllocTexture(const TextureResourceManager *texMgr);
static void TextureResource_Init(TextureResource *texResource);
static void TexRes_AllocVRam(const NNSG3dResTex *texRes, NNSGfdTexKey *texKey, NNSGfdTexKey *tex4x4Key, NNSGfdPlttKey *paletteKey);
static NNSG3dResTex *TextureResource_GetTexRes(const TextureResource *texResource);
static NNSG3dResTex *TextureResource_GetTexResWithData(const TextureResource *texResource);
static void TexRes_UploadToVRam(NNSG3dResTex *texRes, TextureResource *texResource);
static void TexRes_AssignVRamKeys(NNSG3dResTex *texRes, NNSGfdTexKey texKey, NNSGfdTexKey tex4x4Key, NNSGfdPlttKey paletteKey);
static void TexRes_ReleaseVRamKeys(NNSG3dResTex *texRes);
static void *CreateStrippedTexture(void *resFile, enum HeapID heapID);
static u32 GetStrippedTextureResourceSize(const void *resFile);

ResourceCollection *ResourceCollection_New(s32 capacity, enum HeapID heapID)
{
    ResourceCollection *resMgr = Heap_Alloc(heapID, sizeof(ResourceCollection));
    GF_ASSERT(resMgr);

    resMgr->resources = Heap_Alloc(heapID, sizeof(Resource) * capacity);
    GF_ASSERT(resMgr->resources);

    for (int i = 0; i < capacity; i++) {
        Resource_Init(resMgr->resources + i);
    }

    resMgr->capacity = capacity;
    resMgr->count = 0;

    return resMgr;
}

void ResourceCollection_Delete(ResourceCollection *collection)
{
    GF_ASSERT(collection);

    ResourceCollection_Clear(collection);
    Heap_Free(collection->resources);
    Heap_Free(collection);
}

BOOL ResourceCollection_IsIDUnused(ResourceCollection *collection, int id)
{
    GF_ASSERT(collection);
    return ResourceCollection_FindResource(collection, id) == NULL;
}

Resource *ResourceCollection_Add(ResourceCollection *collection, void *data, int id)
{
    GF_ASSERT(collection);

    Resource *resource = ResourceCollection_AllocResource(collection);
    GF_ASSERT(resource);

    GF_ASSERT(ResourceCollection_IsIDUnused(collection, id) == TRUE);

    resource->data = data;
    resource->id = id;
    collection->count++;

    return resource;
}

Resource *ResourceCollection_AddFromFile(ResourceCollection *collection, const char *filename, int id, enum HeapID heapID)
{
    GF_ASSERT(collection);
    GF_ASSERT(filename);

    Resource *resource = ResourceCollection_AllocResource(collection);

    GF_ASSERT(resource);
    GF_ASSERT(ResourceCollection_IsIDUnused(collection, id) == TRUE);

    resource->data = ReadFileToHeap(heapID, filename);
    GF_ASSERT(resource->data);
    resource->id = id;

    collection->count++;

    return resource;
}

void ResourceCollection_Remove(ResourceCollection *collection, Resource *resource)
{
    GF_ASSERT(collection);
    GF_ASSERT(resource);

    if (resource->data) {
        Heap_Free(resource->data);
        resource->data = NULL;
    }

    resource->id = RESOURCE_ID_INVALID;
    collection->count--;
}

void ResourceCollection_Clear(ResourceCollection *resMgr)
{
    GF_ASSERT(resMgr);
    GF_ASSERT(resMgr->resources);

    for (int i = 0; i < resMgr->capacity; i++) {
        if (resMgr->resources[i].id != RESOURCE_ID_INVALID) {
            ResourceCollection_Remove(resMgr, resMgr->resources + i);
        }
    }
}

Resource *ResourceCollection_FindResource(ResourceCollection *collection, int id)
{
    GF_ASSERT(collection);

    for (int i = 0; i < collection->capacity; i++) {
        if (collection->resources[i].id == id) {
            return collection->resources + i;
        }
    }

    return NULL;
}

void *Resource_GetData(Resource *resource)
{
    GF_ASSERT(resource);
    return resource->data;
}

void Resource_SetData(Resource *resource, void *data)
{
    GF_ASSERT(resource);

    if (resource->data) {
        Heap_Free(resource->data);
    }

    resource->data = data;
}

int Resource_GetID(Resource *resource)
{
    GF_ASSERT(resource);
    return resource->id;
}

static Resource *ResourceCollection_AllocResource(ResourceCollection *collection)
{
    GF_ASSERT(collection);

    for (int i = 0; i < collection->capacity; i++) {
        if (collection->resources[i].id == RESOURCE_ID_INVALID) {
            return collection->resources + i;
        }
    }

    return NULL;
}

static void Resource_Init(Resource *resource)
{
    GF_ASSERT(resource);

    resource->id = RESOURCE_ID_INVALID;
    resource->data = NULL;
}

TextureResourceManager *TextureResourceManager_New(s32 maxTextures, enum HeapID heapID)
{
    TextureResourceManager *texMgr = Heap_Alloc(heapID, sizeof(TextureResourceManager));

    texMgr->resources = ResourceCollection_New(maxTextures, heapID);
    texMgr->textures = Heap_Alloc(heapID, sizeof(TextureResource) * maxTextures);

    for (int i = 0; i < maxTextures; i++) {
        TextureResource_Init(texMgr->textures + i);
    }

    return texMgr;
}

void TextureResourceManager_Delete(TextureResourceManager *texMgr)
{
    GF_ASSERT(texMgr);

    TextureResourceManager_Clear(texMgr);
    ResourceCollection_Delete(texMgr->resources);
    Heap_Free(texMgr->textures);
    Heap_Free(texMgr);
}

BOOL TextureResourceManager_IsIDUnused(const TextureResourceManager *texMgr, int id)
{
    GF_ASSERT(texMgr);
    return ResourceCollection_IsIDUnused(texMgr->resources, id);
}

TextureResource *TextureResourceManager_AddTexture(const TextureResourceManager *texMgr, void *data, int id, enum TextureResourceMode mode, enum HeapID heapID)
{
    TextureResource *texResource;
    void *resourceData;

    GF_ASSERT(texMgr);

    texResource = TextureResourceManager_AllocTexture(texMgr);
    texResource->mode = mode;

    if (texResource->mode == TEX_RESOURCE_MODE_SEPARATED) {
        resourceData = CreateStrippedTexture(data, heapID);
        texResource->textureData = data;
    } else {
        resourceData = data;
        texResource->textureData = NULL;
    }

    texResource->resource = ResourceCollection_Add(texMgr->resources, resourceData, id);

    return texResource;
}

TextureResource *TextureResourceManager_AddTextureAndAllocVRam(TextureResourceManager *texMgr, void *data, int id, enum TextureResourceMode mode, enum HeapID heapID)
{
    TextureResource *texResource = TextureResourceManager_AddTexture(texMgr, data, id, mode, heapID);
    TextureResource_AllocVRam(texResource);

    return texResource;
}

void TextureResourceManager_RemoveTexture(TextureResourceManager *texMgr, TextureResource *texResource)
{
    GF_ASSERT(texMgr);
    GF_ASSERT(texResource);

    if (texResource->mode == TEX_RESOURCE_MODE_SEPARATED && (texResource->texDataDiscarded == 0)) {
        Heap_Free(texResource->textureData);
        texResource->mode = NULL;
    }

    if (texResource->resource) {
        ResourceCollection_Remove(texMgr->resources, texResource->resource);
    }

    if (texResource->texKey != NNS_GFD_ALLOC_ERROR_TEXKEY) {
        if (BankD_OwnsTexKey(texResource->texKey)) {
            GF_ASSERT(BankD_FreeTexVram(texResource->texKey) == 0);
        } else {
            GF_ASSERT(NNS_GfdFreeTexVram(texResource->texKey) == 0);
        }
    }

    if (texResource->tex4x4Key != NNS_GFD_ALLOC_ERROR_TEXKEY) {
        GF_ASSERT(NNS_GfdFreeTexVram(texResource->tex4x4Key) == 0);
    }

    if (texResource->paletteKey != NNS_GFD_ALLOC_ERROR_PLTTKEY) {
        GF_ASSERT(NNS_GfdFreePlttVram(texResource->paletteKey) == 0);
    }

    TextureResource_Init(texResource);
}

void TextureResourceManager_RemoveTextureWithID(TextureResourceManager *texMgr, int id)
{
    GF_ASSERT(texMgr);
    TextureResourceManager_RemoveTexture(texMgr, TextureResourceManager_FindTextureResource(texMgr, id));
}

void TextureResourceManager_Clear(TextureResourceManager *texMgr)
{
    GF_ASSERT(texMgr);
    GF_ASSERT(texMgr->textures);

    for (int i = 0; i < texMgr->resources->capacity; i++) {
        if (texMgr->textures[i].resource) {
            TextureResourceManager_RemoveTexture(texMgr, texMgr->textures + i);
        }
    }
}

TextureResource *TextureResourceManager_FindTextureResource(const TextureResourceManager *texMgr, int id)
{
    GF_ASSERT(texMgr);

    for (int i = 0; i < texMgr->resources->capacity; i++) {
        // Combining these two checks into one doesn't match
        if (texMgr->textures[i].resource) {
            int texId = TextureResource_GetID(texMgr->textures + i);
            if (texId == id) {
                return texMgr->textures + i;
            }
        }
    }

    return NULL;
}

int TextureResource_GetID(const TextureResource *texResource)
{
    GF_ASSERT(texResource);
    return Resource_GetID(texResource->resource);
}

NNSG3dResTex *TextureResource_GetUnderlyingResource(const TextureResource *texResource)
{
    GF_ASSERT(texResource);
    return TextureResource_GetTexRes(texResource);
}

void TextureResource_UploadToVRam(TextureResource *texResource)
{
    GF_ASSERT(texResource);
    GF_ASSERT(texResource->texDataDiscarded == FALSE);

    if (texResource->paletteKey == NNS_GFD_ALLOC_ERROR_PLTTKEY) {
        GF_ASSERT(FALSE);
        return;
    }

    NNSG3dResTex *texRes = TextureResource_GetTexResWithData(texResource);
    TexRes_UploadToVRam(texRes, texResource);
}

void TextureResourceManager_UploadResourceToVRam(TextureResourceManager *texMgr, int id)
{
    GF_ASSERT(texMgr);
    TextureResource_UploadToVRam(TextureResourceManager_FindTextureResource(texMgr, id));
}

// Discards the texture data of a texture resource. Only do this after the texture has been uploaded to VRAM.
// Only allowed for TEX_RESOURCE_MODE_SEPARATED resources.
void TextureResource_DiscardTextureData(TextureResource *texResource)
{
    GF_ASSERT(texResource);

    // Discarding texture data is not allowed for normal texture resources
    if (texResource->mode == TEX_RESOURCE_MODE_NORMAL) {
        GF_ASSERT(FALSE);
        return;
    }

    if (texResource->texDataDiscarded) {
        GF_ASSERT(FALSE);
        return;
    }

    TexRes_ReleaseVRamKeys(TextureResource_GetTexResWithData(texResource));
    TexRes_AssignVRamKeys(
        TextureResource_GetTexRes(texResource),
        texResource->texKey,
        texResource->tex4x4Key,
        texResource->paletteKey);
    Heap_Free(texResource->textureData);

    texResource->textureData = NULL;
    texResource->texDataDiscarded = TRUE;
}

void TextureResourceManager_DiscardTextureData(TextureResourceManager *texMgr, int id)
{
    GF_ASSERT(texMgr);
    TextureResource_DiscardTextureData(TextureResourceManager_FindTextureResource(texMgr, id));
}

void TextureResource_AllocVRam(TextureResource *texResource)
{
    GF_ASSERT(texResource);
    GF_ASSERT(texResource->texDataDiscarded == FALSE);

    if (texResource->paletteKey != NNS_GFD_ALLOC_ERROR_PLTTKEY) {
        GF_ASSERT(FALSE);
        return;
    }

    NNSG3dResTex *texRes = TextureResource_GetTexResWithData(texResource);
    TexRes_AllocVRam(texRes, &texResource->texKey, &texResource->tex4x4Key, &texResource->paletteKey);
}

NNSGfdTexKey TextureResource_GetTexKey(const TextureResource *texResource)
{
    GF_ASSERT(texResource);
    return texResource->texKey;
}

NNSGfdTexKey TextureResource_GetTex4x4Key(const TextureResource *texResource)
{
    GF_ASSERT(texResource);
    return texResource->tex4x4Key;
}

NNSGfdPlttKey TextureResource_GetPaletteKey(const TextureResource *texResource)
{
    GF_ASSERT(texResource);
    return texResource->paletteKey;
}

u32 Utility_GetStrippedTextureResourceSize(NNSG3dResFileHeader *resFile)
{
    return GetStrippedTextureResourceSize(resFile);
}

static TextureResource *TextureResourceManager_AllocTexture(const TextureResourceManager *texMgr)
{
    for (int i = 0; i < texMgr->resources->capacity; i++) {
        if (texMgr->textures[i].resource == NULL) {
            return texMgr->textures + i;
        }
    }

    return NULL;
}

static void TextureResource_Init(TextureResource *texResource)
{
    texResource->resource = NULL;
    texResource->texKey = NNS_GFD_ALLOC_ERROR_TEXKEY;
    texResource->tex4x4Key = NNS_GFD_ALLOC_ERROR_TEXKEY;
    texResource->paletteKey = NNS_GFD_ALLOC_ERROR_PLTTKEY;
    texResource->texDataDiscarded = 0;
    texResource->textureData = NULL;
    texResource->texDataDiscarded = 0;
}

static NNSG3dResTex *TextureResource_GetTexRes(const TextureResource *texResource)
{
    return NNS_G3dGetTex(Resource_GetData(texResource->resource));
}

static NNSG3dResTex *TextureResource_GetTexResWithData(const TextureResource *texResource)
{
    void *texData = texResource->mode == TEX_RESOURCE_MODE_NORMAL
        ? Resource_GetData(texResource->resource)
        : texResource->textureData;

    return NNS_G3dGetTex(texData);
}

static void TexRes_AllocVRam(const NNSG3dResTex *texRes, NNSGfdTexKey *texKey, NNSGfdTexKey *tex4x4Key, NNSGfdPlttKey *paletteKey)
{
    u32 texSize = NNS_G3dTexGetRequiredSize(texRes);
    u32 tex4x4Size = NNS_G3dTex4x4GetRequiredSize(texRes);
    u32 paletteSize = NNS_G3dPlttGetRequiredSize(texRes);

    if (texSize != 0) {
        // Large sprites get their own bank-D region so they don't compete with
        // map geometry + normal sprites in the shared A+B pool.
        if (texSize > LARGE_TEX_VRAM_THRESHOLD) {
            *texKey = BankD_AllocTexVram(texSize);
        } else {
            *texKey = NNS_GfdAllocTexVram(texSize, FALSE, 0);
        }
    }

    if (tex4x4Size != 0) {
        *tex4x4Key = NNS_GfdAllocTexVram(tex4x4Size, TRUE, 0);
    }

    if (paletteSize != 0) {
        *paletteKey = NNS_GfdAllocPlttVram(paletteSize, texRes->tex4x4Info.flag & NNS_G3D_RESPLTT_USEPLTT4, 0);
    }
}

static void TexRes_UploadToVRam(NNSG3dResTex *texRes, TextureResource *texResource)
{
    TexRes_AssignVRamKeys(texRes, texResource->texKey, texResource->tex4x4Key, texResource->paletteKey);

    DC_FlushRange(texRes, texRes->header.size);

    NNS_G3dTexLoad(texRes, TRUE);
    NNS_G3dPlttLoad(texRes, TRUE);
}

static void TexRes_AssignVRamKeys(NNSG3dResTex *texRes, NNSGfdTexKey texKey, NNSGfdTexKey tex4x4Key, NNSGfdPlttKey paletteKey)
{
    NNS_G3dTexSetTexKey(texRes, texKey, tex4x4Key);
    NNS_G3dPlttSetPlttKey(texRes, paletteKey);
}

static void TexRes_ReleaseVRamKeys(NNSG3dResTex *texRes)
{
    NNSGfdTexKey texKey;
    NNSGfdTexKey tex4x4Key;

    NNS_G3dTexReleaseTexKey(texRes, &texKey, &tex4x4Key);
    NNS_G3dPlttReleasePlttKey(texRes);
}

// Duplicates a texture resource without the actual texture data
static void *CreateStrippedTexture(void *resFile, enum HeapID heapID)
{
    u32 size = GetStrippedTextureResourceSize(resFile);
    void *stripped = Heap_Alloc(heapID, size);
    memcpy(stripped, resFile, size);

    return stripped;
}

// Calculates the size of a texture resource without the actual texture data
static u32 GetStrippedTextureResourceSize(const void *resFile)
{
    NNSG3dResTex *texture = NNS_G3dGetTex(resFile);
    GF_ASSERT(texture);

    u8 *texData = (u8 *)texture + texture->texInfo.ofsTex;
    return (u32)(texData - (u8 *)resFile);
}
