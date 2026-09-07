#include "berry_patches.h"

#include "constants/heap.h"
#include "constants/items.h"

#include "berry_data.h"
#include "heap.h"
#include "narc.h"

#include "data/berry_yields.h"

#define MAX_MOISTURE_RATING 100
#define MAX_YIELD_RATING    5

static void ZeroBerryPatch(BerryPatch *berryPatch);
static int CalcMinutesRemainingInStage(const BerryGrowthData *growthData, int berryID, enum MulchType mulchType);

void BerryPatches_Clear(BerryPatch *patches)
{
    MI_CpuClear8(patches, sizeof(BerryPatch) * MAX_BERRY_PATCHES);
    for (int i = 0; i < MAX_BERRY_PATCHES; i++) {
        patches[i].growthStage = BERRY_GROWTH_STAGE_NONE;
        patches[i].berryID = 0;
    }
}

void BerryPatches_Init(BerryPatch *patches, const BerryPatchInit *initPatches, int initSize)
{
    BerryPatches_Clear(patches);

    for (int i = 0; i < MAX_BERRY_PATCHES && i < initSize; i++) {
        int berryID = initPatches[i].berryItemID - FIRST_BERRY_IDX + 1;

        patches[i].berryID = berryID;
        patches[i].growthStage = BERRY_GROWTH_STAGE_FRUIT;
        patches[i].yield = initPatches[i].yield != 0 ? initPatches[i].yield : sBerryYields[berryID - 1];
        patches[i].moistureRating = MAX_MOISTURE_RATING;
        patches[i].yieldRating = MAX_YIELD_RATING;
    }
}

BerryGrowthData *BerryGrowthData_Init(enum HeapID heapID)
{
    BerryGrowthData *growthData;
    BerryData *berryData;
    NARC *narc = BerryData_NARC_ctor(heapID);
    growthData = Heap_Alloc(heapID, sizeof(BerryGrowthData) * NUM_BERRIES);

    for (int i = 0; i < NUM_BERRIES; i++) {
        berryData = BerryData_LoadFromOpenNARC(narc, i, heapID);

        growthData[i].stageDuration = BerryData_GetAttribute(berryData, BERRYATTR_STAGE_DURATION);
        growthData[i].moistureDrainRate = BerryData_GetAttribute(berryData, BERRYATTR_MOISTURE_DRAIN_RATE);
        growthData[i].yieldCategory = BerryData_GetAttribute(berryData, BERRYATTR_YIELD_CATEGORY);

        Heap_Free(berryData);
    }

    BerryData_NARC_dtor(narc);
    return growthData;
}

static void ZeroBerryPatch(BerryPatch *berryPatch)
{
    berryPatch->berryID = 0;
    berryPatch->growthStage = BERRY_GROWTH_STAGE_NONE;
    berryPatch->stageMinutesRemaining = 0;
    berryPatch->moistureMinutesRemaining = 0;
    berryPatch->replantCount = 0;
    berryPatch->yield = 0;
    berryPatch->moistureRating = 0;
    berryPatch->yieldRating = 0;
    berryPatch->mulchType = MULCH_TYPE_NONE;
    berryPatch->isGrowing = FALSE;
}

static int CalcMinutesRemainingInStage(const BerryGrowthData *growthData, int berryID, enum MulchType mulchType)
{
    int minutesRemaining = growthData[berryID - 1].stageDuration * 60;

    if (mulchType == MULCH_TYPE_GROWTH) {
        minutesRemaining = (minutesRemaining * 3) / 4;
    } else if (mulchType == MULCH_TYPE_DAMP) {
        minutesRemaining = minutesRemaining + (minutesRemaining / 2);
    }

    return minutesRemaining;
}

enum BerryGrowthStage BerryPatches_GetPatchGrowthStage(const BerryPatch *patches, int patchID)
{
    return patches[patchID].growthStage;
}

int BerryPatches_GetPatchBerryID(const BerryPatch *patches, int patchID)
{
    return patches[patchID].berryID;
}

enum SoilMoisture BerryPatches_GetPatchMoisture(const BerryPatch *patches, int patchID)
{
    int moistureRating = patches[patchID].moistureRating;
    if (moistureRating == 0) {
        return SOIL_VERY_DRY;
    } else if (moistureRating <= 50) {
        return SOIL_DRY;
    } else {
        return SOIL_MOIST;
    }
}

int BerryPatches_GetPatchYieldRating(const BerryPatch *patches, int patchID)
{
    return patches[patchID].yieldRating;
}

void BerryPatches_PlantInPatch(BerryPatch *patches, int patchID, const BerryGrowthData *growthData, int berryID)
{
    patches[patchID].berryID = berryID;
    patches[patchID].growthStage = BERRY_GROWTH_STAGE_PLANTED;
    patches[patchID].stageMinutesRemaining = CalcMinutesRemainingInStage(growthData, berryID, patches[patchID].mulchType);
    patches[patchID].moistureMinutesRemaining = 0;
    patches[patchID].replantCount = 0;
    patches[patchID].yield = 0;
    patches[patchID].moistureRating = MAX_MOISTURE_RATING;
    patches[patchID].yieldRating = MAX_YIELD_RATING;
    patches[patchID].isGrowing = TRUE;
}

void BerryPatches_ResetPatchMoisture(BerryPatch *patches, int patchID)
{
    patches[patchID].moistureRating = MAX_MOISTURE_RATING;
}

BOOL BerryPatches_IsPatchGrowing(const BerryPatch *patches, int patchID)
{
    return patches[patchID].isGrowing;
}

void BerryPatches_SetIsPatchGrowing(BerryPatch *patches, int patchID, BOOL isGrowing)
{
    patches[patchID].isGrowing = isGrowing;
}

enum MulchType BerryPatches_GetPatchMulchType(const BerryPatch *patches, int patchID)
{
    return patches[patchID].mulchType;
}

void BerryPatches_SetPatchMulchType(BerryPatch *patches, int patchID, enum MulchType mulchType)
{
    patches[patchID].mulchType = mulchType;
}

int BerryPatches_GetPatchYield(const BerryPatch *patches, int patchID)
{
    return patches[patchID].yield;
}

int BerryPatches_HarvestPatch(BerryPatch *patches, int patchID)
{
    int yield = patches[patchID].yield;
    ZeroBerryPatch(&patches[patchID]);
    return yield;
}
