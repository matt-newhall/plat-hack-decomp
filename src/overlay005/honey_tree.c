#include "overlay005/honey_tree.h"

#include <nitro.h>
#include <string.h>

#include "constants/map_object.h"
#include "generated/map_headers.h"

#include "field/field_system.h"
#include "overlay005/land_data.h"
#include "overlay005/map_prop.h"
#include "overlay005/map_prop_animation.h"

#include "heap.h"
#include "inlines.h"
#include "map_matrix.h"
#include "narc.h"
#include "player_avatar.h"
#include "save_player.h"
#include "special_encounter.h"
#include "terrain_collision_manager.h"

#include "res/field/props/models/prop_models.naix"

#define HONEY_ROLL_NONE 0xFFFF

// Single weighted honey-tree encounter table
typedef struct HoneyEncounterHeader {
    u16 count;
    u16 totalWeight;
} HoneyEncounterHeader;

typedef struct HoneyEncounter {
    u16 species;
    u16 weight;
} HoneyEncounter;

static void DoTreeShakingAnimation(FieldSystem *fieldSystem, MapPropManager *param1, const int param2);
static u8 GetTreeIdFromMapId(const int param0);
static const BOOL GetShakingValue(const int numShakes, u8 *value);
static const BOOL SixHoursSinceSlathered(const int param0);
static u8 *HoneyTree_ReadTable(void);
static u16 RollHoneyEncounter(const u8 *table);

static const int sHoneyTreeMapIds[NUM_HONEY_TREES] = {
    MAP_HEADER_ROUTE_205_SOUTH,
    MAP_HEADER_ROUTE_205_NORTH,
    MAP_HEADER_ROUTE_206,
    MAP_HEADER_ROUTE_207,
    MAP_HEADER_ROUTE_208,
    MAP_HEADER_ROUTE_209,
    MAP_HEADER_ROUTE_210_SOUTH,
    MAP_HEADER_ROUTE_210_NORTH,
    MAP_HEADER_ROUTE_211_EAST,
    MAP_HEADER_ROUTE_212_NORTH,
    MAP_HEADER_ROUTE_212_SOUTH,
    MAP_HEADER_ROUTE_213,
    MAP_HEADER_ROUTE_214,
    MAP_HEADER_ROUTE_215,
    MAP_HEADER_ROUTE_218,
    MAP_HEADER_ROUTE_221,
    MAP_HEADER_ROUTE_222,
    MAP_HEADER_VALLEY_WINDWORKS_OUTSIDE,
    MAP_HEADER_ETERNA_FOREST_OUTSIDE,
    MAP_HEADER_FUEGO_IRONWORKS_OUTSIDE,
    MAP_HEADER_FLOAROMA_MEADOW
};

// Seems they considered having version exclusive Honey Tree encounters.
static const int sEncounterTableIndexes_DPt[] = {
    0x2,
    0x3,
    0x4
};

// These IDs ultimately point to the same encounters.
static const int sEncounterTableIndexes_P_Unused[] = {
    0x5,
    0x6,
    0x7
};

HoneyTreeShakeList *HoneyTree_ShakeDataInit(void)
{
    HoneyTreeShakeList *data = Heap_Alloc(HEAP_ID_FIELD1, sizeof(HoneyTreeShakeList));

    for (u8 i = 0; i < NUM_HONEY_TREES; i++) {
        data->trees[i].shakeValue = 0;
        data->trees[i].isShaking = FALSE;
    }

    return data;
}

void HoneyTree_FreeShakeData(HoneyTreeShakeList **data)
{
    Heap_Free(*data);
    *data = NULL;
}

BOOL HoneyTree_TryInteract(FieldSystem *fieldSystem, int *eventId)
{
    TerrainCollisionHitbox v0;
    int x, z;
    BOOL isFacingHoneyTree;

    *eventId = SCRIPT_ID(COMMON_SCRIPTS, 8);

    x = Player_GetXPos(fieldSystem->playerAvatar);
    z = Player_GetZPos(fieldSystem->playerAvatar);

    if (PlayerAvatar_GetDir(fieldSystem->playerAvatar) == DIR_NORTH) { // Honey Trees can only be interacted with from below.
        TerrainCollisionHitbox_Init(x, z, 0, -1, 1, 1, &v0);
        isFacingHoneyTree = FieldSystem_FindCollidingLoadedMapPropByModelID(fieldSystem, honey_tree_nsbmd, &v0, NULL);
    } else {
        isFacingHoneyTree = FALSE;
    }

    return isFacingHoneyTree;
}

u16 HoneyTree_GetTreeSlatherStatus(FieldSystem *fieldSystem)
{
    u8 treeId;
    PlayerHoneyTreeStates *treeDat;
    HoneyTree *tree;

    treeId = GetTreeIdFromMapId(fieldSystem->location->mapId);
    GF_ASSERT(treeId != NUM_HONEY_TREES);

    treeDat = SpecialEncounter_GetPlayerHoneyTreeStates(SaveData_GetSpecialEncounters(fieldSystem->saveData));
    tree = SpecialEncounter_GetHoneyTree(treeId, treeDat);

    if (SixHoursSinceSlathered(tree->minutesRemaining)) {
        return TREE_STATUS_ENCOUNTER; // tree can have Pokemon
    } else if (tree->minutesRemaining != 0) {
        return TREE_STATUS_SLATHERED; // tree is slathered
    } else {
        return TREE_STATUS_BARE; // tree is bare
    }
}

void HoneyTree_SlatherTree(FieldSystem *fieldSystem)
{
    u8 treeId;
    PlayerHoneyTreeStates *treeDat;
    HoneyTree *tree;

    treeId = GetTreeIdFromMapId(fieldSystem->location->mapId);
    GF_ASSERT(treeId != NUM_HONEY_TREES);

    treeDat = SpecialEncounter_GetPlayerHoneyTreeStates(SaveData_GetSpecialEncounters(fieldSystem->saveData));
    tree = SpecialEncounter_GetHoneyTree(treeId, treeDat);

    tree->minutesRemaining = (24 * 60); // kept non-zero so the tree reads as slathered until the immediate battle unslathers it

    // Honey trees give an immediate encounter
    u8 *table = HoneyTree_ReadTable();
    u16 index = RollHoneyEncounter(table);
    Heap_Free(table);

    tree->encounterTableIndex = 0;
    tree->encounterGroup = 0;
    tree->numShakes = 0;
    tree->encounterSlot = (index == HONEY_ROLL_NONE) ? 0 : (u8)index;

    SpecialEncounter_SetLastSlatheredTreeId(treeId, treeDat);
}

void HoneyTree_StopShaking(FieldSystem *fieldSystem)
{
    u8 treeId = GetTreeIdFromMapId(fieldSystem->location->mapId);
    GF_ASSERT(treeId != NUM_HONEY_TREES);

    if (fieldSystem->unk_A8->trees[treeId].isShaking) {
        u8 v1;
        MapProp *v2;
        MapPropManager *v3;
        NNSG3dRenderObj *v4;

        v1 = LandDataManager_GetTrackedTargetLoadedMapsQuadrant(fieldSystem->landDataMan);

        LandDataManager_GetLoadedMapPropManager(v1, fieldSystem->landDataMan, &v3);

        v2 = MapPropManager_FindLoadedPropByModelID(v3, honey_tree_nsbmd);
        v4 = MapProp_GetRenderObj(v2);

        if (v2 != NULL) {
            MapPropAnimationManager_RemoveAnimationFromRenderObj(fieldSystem->mapPropAnimMan, v4, honey_tree_nsbmd, fieldSystem->unk_A8->trees[treeId].shakeValue);
        }

        fieldSystem->unk_A8->trees[treeId].isShaking = FALSE;
    }
}

// Related to the Honey Tree shaking animation. Not sure what exactly this value represents. Number of times the anim repeats, maybe?
static const BOOL GetShakingValue(const int numShakes, u8 *value)
{
    u8 unused;
    BOOL isShaking = TRUE;

    if (numShakes == 3) {
        *value = 2;
    } else if (numShakes == 2) {
        *value = 1;
    } else if (numShakes == 1) {
        *value = 0;
    } else {
        isShaking = FALSE;
    }

    return isShaking;
}

static void DoTreeShakingAnimation(FieldSystem *fieldSystem, MapPropManager *param1, const int param2)
{
    u16 mapId;
    u8 treeId;

    mapId = MapMatrix_GetMapHeaderIDAtIndex(fieldSystem->mapMatrix, param2);
    treeId = GetTreeIdFromMapId(mapId);

    if (treeId != NUM_HONEY_TREES) {
        PlayerHoneyTreeStates *treeDat;
        HoneyTree *tree;
        MapProp *v4;

        treeDat = SpecialEncounter_GetPlayerHoneyTreeStates(SaveData_GetSpecialEncounters(fieldSystem->saveData));
        tree = SpecialEncounter_GetHoneyTree(treeId, treeDat);

        if (SixHoursSinceSlathered(tree->minutesRemaining)) {
            BOOL isShaking;
            u8 shakeValue;

            isShaking = GetShakingValue(tree->numShakes, &shakeValue);

            if (!isShaking) {
                return;
            }

            v4 = MapPropManager_FindLoadedPropByModelID(param1, honey_tree_nsbmd);

            if (v4 != NULL) {
                NNSG3dRenderObj *v7;

                v7 = MapProp_GetRenderObj(v4);

                MapPropAnimationManager_RemoveAnimationFromRenderObj(fieldSystem->mapPropAnimMan, v7, honey_tree_nsbmd, fieldSystem->unk_A8->trees[treeId].shakeValue);

                fieldSystem->unk_A8->trees[treeId].shakeValue = shakeValue;
                fieldSystem->unk_A8->trees[treeId].isShaking = isShaking;

                MapPropAnimationManager_AddAnimationToRenderObj(honey_tree_nsbmd, shakeValue, 1, v7, fieldSystem->mapPropAnimMan);
            }
        }
    }
}

// Returns NUM_HONEY_TREES if map does not have a Honey Tree.
static u8 GetTreeIdFromMapId(const int mapId)
{
    u8 i;
    for (i = 0; i < NUM_HONEY_TREES; i++) {
        if (mapId == sHoneyTreeMapIds[i]) {
            return i;
        }
    }

    return i;
}

static const BOOL SixHoursSinceSlathered(const int minutesLeft)
{
    if ((0 < minutesLeft) && (minutesLeft <= (18 * 60))) {
        return TRUE;
    } else {
        return FALSE;
    }
}

static u8 *HoneyTree_ReadTable(void)
{
    int member = ((GAME_VERSION == VERSION_DIAMOND) || (GAME_VERSION == VERSION_PLATINUM))
        ? sEncounterTableIndexes_DPt[0]
        : sEncounterTableIndexes_P_Unused[0];

    return NARC_AllocAtEndAndReadWholeMemberByIndexPair(NARC_INDEX_ARC__ENCDATA_EX, member, HEAP_ID_FIELD1);
}

static u16 RollHoneyEncounter(const u8 *table)
{
    const HoneyEncounterHeader *header = (const HoneyEncounterHeader *)table;
    const HoneyEncounter *entries = (const HoneyEncounter *)(table + sizeof(HoneyEncounterHeader));

    if (header->totalWeight == 0) {
        return HONEY_ROLL_NONE;
    }

    int roll = LCRNG_RandMod(header->totalWeight);

    for (u16 i = 0; i < header->count; i++) {
        if (roll < entries[i].weight) {
            return i;
        }

        roll -= entries[i].weight;
    }

    return HONEY_ROLL_NONE;
}

int HoneyTree_GetSpecies(FieldSystem *fieldSystem)
{
    u8 treeId = GetTreeIdFromMapId(fieldSystem->location->mapId);
    GF_ASSERT(treeId != NUM_HONEY_TREES);

    PlayerHoneyTreeStates *treeDat = SpecialEncounter_GetPlayerHoneyTreeStates(SaveData_GetSpecialEncounters(fieldSystem->saveData));
    HoneyTree *tree = SpecialEncounter_GetHoneyTree(treeId, treeDat);

    u8 *table = HoneyTree_ReadTable();
    const HoneyEncounter *entries = (const HoneyEncounter *)(table + sizeof(HoneyEncounterHeader));

    int species = entries[tree->encounterSlot].species;
    Heap_Free(table);

    return species;
}

void ov5_021F0030(void *param0, const int param1, MapPropManager *const mapPropManager)
{
    FieldSystem *fieldSystem;

    if (param1 < 0) {
        return;
    }

    fieldSystem = (FieldSystem *)param0;
    DoTreeShakingAnimation(fieldSystem, mapPropManager, param1);
}

void HoneyTree_Unslather(FieldSystem *fieldSystem)
{
    PlayerHoneyTreeStates *treeDat;
    HoneyTree *tree;
    u8 treeId = GetTreeIdFromMapId(fieldSystem->location->mapId);
    GF_ASSERT(treeId != NUM_HONEY_TREES);

    fieldSystem->unk_A8->trees[treeId].isShaking = FALSE;

    treeDat = SpecialEncounter_GetPlayerHoneyTreeStates(SaveData_GetSpecialEncounters(fieldSystem->saveData));
    tree = SpecialEncounter_GetHoneyTree(treeId, treeDat);

    tree->minutesRemaining = 0;
}
