#include "follower_mon.h"

#include "constants/map_object.h"
#include "constants/player_avatar.h"
#include "constants/scrcmd.h"

#include "generated/movement_actions.h"

#include "field/field_system.h"
#include "overlay005/follower_ball_effect.h"
#include "overlay005/ov5_021EB1A0.h"
#include "billboard.h"
#include "generated/genders.h"
#include "generated/movement_types.h"
#include "generated/object_events_gfx.h"
#include "follower_mon_gfx.h"
#include "heap.h"
#include "location.h"
#include "constants/field/dynamic_map_features.h"
#include "follower_mon_params.h"
#include "map_header.h"
#include "map_header_data.h"
#include "persisted_map_features_init.h"
#include "map_object.h"
#include "script_manager.h"
#include "map_object_move.h"
#include "party.h"
#include "player_avatar.h"
#include "pokemon.h"
#include "savedata.h"
#include "sound_playback.h"
#include "system_flags.h"
#include "terrain_collision_manager.h"
#include "unk_020655F4.h"

// i initially had this on 0xFD but that was an ID collision with
// some dynamic objects like Veilstone Gym tires
#define FOLLOWER_LOCAL_ID LOCALID_FOLLOWER

#define FOLLOWER_RECALL_TURN_DELAY   11
#define FOLLOWER_RECALL_SHRINK_FRAMES 6
#define FOLLOWER_RECALL_BALL_FRAMES   10
#define FOLLOWER_RECALL_MIN_SCALE     (FX32_ONE / 4)

enum FollowerRecallState {
    FOLLOWER_RECALL_STATE_TURN = 0,
    FOLLOWER_RECALL_STATE_HOLD,
    FOLLOWER_RECALL_STATE_SHRINK,
    FOLLOWER_RECALL_STATE_BALL
};

static u16 FollowerMon_GetLeadGfxID(FieldSystem *fieldSystem, u16 *species, u8 *gender)
{
    Party *party = SaveData_GetParty(fieldSystem->saveData);
    int partyCount = Party_GetCurrentCount(party);
    Pokemon *lead = NULL;
    int i;

    for (i = 0; i < partyCount; i++) {
        lead = Party_GetPokemonBySlotIndex(party, i);

        if (Pokemon_GetValue(lead, MON_DATA_HP, NULL)) {
            break;
        }
    }

    if (lead == NULL || Pokemon_GetValue(lead, MON_DATA_IS_EGG, NULL)) {
        return OBJ_EVENT_GFX_INVISIBLE;
    }

    *species = (u16)Pokemon_GetValue(lead, MON_DATA_SPECIES, NULL);
    *gender  = (u8)Pokemon_GetValue(lead, MON_DATA_GENDER, NULL);

    return FollowerMon_GetGfxID(
        *species,
        (u8)Pokemon_GetValue(lead, MON_DATA_FORM, NULL),
        *gender == GENDER_FEMALE,
        (BOOL)Pokemon_IsShiny(lead));
}

static BOOL FollowerMon_IsAllowedOnMap(FieldSystem *fieldSystem, u16 species)
{
    if (PersistedMapFeatures_IsCurrentDynamicMap(fieldSystem, DYNAMIC_MAP_FEATURES_DISTORTION_WORLD) == TRUE) {
        return FALSE;
    }

    switch (MapHeader_GetFollowMode(fieldSystem->location->mapId)) {
    case MAP_FOLLOW_MODE_PREVENT:
        return FALSE;
    case MAP_FOLLOW_MODE_HEIGHT_RESTRICT:
        return FollowerMon_IsLargeSpecies(species) == FALSE;
    }

    return TRUE;
}

static void FollowerMon_StorePosition(FieldSystem *fieldSystem, MapObject *follower, u16 species, u8 gender)
{
    fieldSystem->followMon.species = species;
    fieldSystem->followMon.gender  = gender;
    fieldSystem->followMon.x       = (s16)MapObject_GetX(follower);
    fieldSystem->followMon.z       = (s16)MapObject_GetZ(follower);
    fieldSystem->followMon.dir     = (u8)MapObject_GetFacingDir(follower);
    fieldSystem->followMon.active  = TRUE;
}

static MapObject *FollowerMon_Spawn(FieldSystem *fieldSystem, u16 gfxID, int x, int z, int dir)
{
    ObjectEvent objectEvent;
    MapObject *follower;

    ObjectEvent_SetLocalID(&objectEvent, FOLLOWER_LOCAL_ID);
    ObjectEvent_SetGraphicsID(&objectEvent, gfxID);
    ObjectEvent_SetMovementType(&objectEvent, MOVEMENT_TYPE_FOLLOW_PLAYER);
    ObjectEvent_SetTrainerType(&objectEvent, 0);
    ObjectEvent_SetHiddenFlag(&objectEvent, 0);
    ObjectEvent_SetScript(&objectEvent, SCRIPT_ID(FOLLOWER_PARTNERS, 6));
    ObjectEvent_SetInitialDir(&objectEvent, dir);
    ObjectEvent_SetDataAt(&objectEvent, 0, 0);
    ObjectEvent_SetDataAt(&objectEvent, 0, 1);
    ObjectEvent_SetDataAt(&objectEvent, 0, 2);
    ObjectEvent_SetMovementRangeX(&objectEvent, 0);
    ObjectEvent_SetMovementRangeZ(&objectEvent, 0);
    ObjectEvent_SetX(&objectEvent, x);
    ObjectEvent_SetY(&objectEvent, 0);
    ObjectEvent_SetZ(&objectEvent, z);

    follower = MapObjectMan_AddMapObjectFromHeader(
        fieldSystem->mapObjMan, &objectEvent, fieldSystem->location->mapId);

    if (follower == NULL) {
        return NULL;
    }

    MapObject_SetStatusFlagOn(follower, MAP_OBJ_STATUS_PERSISTENT);
    MapObject_RecalculateObjectHeight(follower);

    return follower;
}

static MapObject *FollowerMon_FindAndReuse(FieldSystem *fieldSystem, u16 gfxID, u16 species, u8 gender)
{
    MapObject *follower = MapObjMan_GetLocalMapObjByMovementType(fieldSystem->mapObjMan, MOVEMENT_TYPE_FOLLOW_PLAYER);

    if (follower == NULL) {
        return NULL;
    }

    if (MapObject_GetGraphicsID(follower) == gfxID) {
        MapObject_SetScript(follower, SCRIPT_ID(FOLLOWER_PARTNERS, 6));
        FollowerMon_StorePosition(fieldSystem, follower, species, gender);
        return follower;
    }

    MapObject_SetFlagAndDeleteObject(follower);
    return NULL;
}

void FollowerMon_UpdateFollower(FieldSystem *fieldSystem)
{
    u16 species;
    u8  gender;
    u16 gfxID;
    MapObject *follower;
    int x, z, dir;

    if (SystemFlag_CheckHasPartner(SaveData_GetVarsFlags(fieldSystem->saveData)) == TRUE) {
        return;
    }

    // Surf/Waterfall/Bike
    if (PlayerAvatar_GetPlayerState(fieldSystem->playerAvatar) == PLAYER_STATE_SURFING
        || PlayerAvatar_GetPlayerState(fieldSystem->playerAvatar) == PLAYER_STATE_CYCLING) {
        return;
    }

    gfxID = FollowerMon_GetLeadGfxID(fieldSystem, &species, &gender);

    if (gfxID == OBJ_EVENT_GFX_INVISIBLE) {
        return;
    }

    if (FollowerMon_IsAllowedOnMap(fieldSystem, species) == FALSE) {
        return;
    }

    if (FollowerMon_FindAndReuse(fieldSystem, gfxID, species, gender) != NULL) {
        return;
    }

    x   = Player_GetXPos(fieldSystem->playerAvatar);
    z   = Player_GetZPos(fieldSystem->playerAvatar);
    dir = PlayerAvatar_GetDir(fieldSystem->playerAvatar);

    switch (dir) {
    case FACE_UP:    z += 1; break;
    case FACE_DOWN:  z -= 1; break;
    case FACE_LEFT:  x += 1; break;
    case FACE_RIGHT: x -= 1; break;
    }

    if (TileBehavior_IsNull(TerrainCollisionManager_GetTileBehavior(fieldSystem, x, z))) {
        return;
    }

    follower = FollowerMon_Spawn(fieldSystem, gfxID, x, z, dir);

    if (follower == NULL) {
        return;
    }

    FollowerMon_StorePosition(fieldSystem, follower, species, gender);
    FollowerBallEffect_Start(follower);
}

void FollowerMon_RestoreFollower(FieldSystem *fieldSystem)
{
    u16 species;
    u8  gender;
    u16 gfxID;
    MapObject *follower;
    int x, z, dir;

    if (fieldSystem->followMon.active == FALSE) {
        return;
    }

    if (SystemFlag_CheckHasPartner(SaveData_GetVarsFlags(fieldSystem->saveData)) == TRUE) {
        return;
    }

    gfxID = FollowerMon_GetLeadGfxID(fieldSystem, &species, &gender);

    if (gfxID == OBJ_EVENT_GFX_INVISIBLE) {
        return;
    }

    if (FollowerMon_IsAllowedOnMap(fieldSystem, species) == FALSE) {
        return;
    }

    if (FollowerMon_FindAndReuse(fieldSystem, gfxID, species, gender) != NULL) {
        return;
    }

    x   = fieldSystem->followMon.x;
    z   = fieldSystem->followMon.z;
    dir = fieldSystem->followMon.dir;

    if (TileBehavior_IsNull(TerrainCollisionManager_GetTileBehavior(fieldSystem, x, z))) {
        return;
    }

    follower = FollowerMon_Spawn(fieldSystem, gfxID, x, z, dir);

    if (follower == NULL) {
        return;
    }

    FollowerMon_StorePosition(fieldSystem, follower, species, gender);
}

void FollowerMon_SaveState(FieldSystem *fieldSystem)
{
    MapObject *follower = MapObjMan_GetLocalMapObjByMovementType(fieldSystem->mapObjMan, MOVEMENT_TYPE_FOLLOW_PLAYER);

    if (follower != NULL) {
        fieldSystem->followMon.x      = (s16)MapObject_GetX(follower);
        fieldSystem->followMon.z      = (s16)MapObject_GetZ(follower);
        fieldSystem->followMon.dir    = (u8)MapObject_GetFacingDir(follower);
        fieldSystem->followMon.active = TRUE;
    } else {
        fieldSystem->followMon.active = FALSE;
    }
}

static BOOL FollowerMon_IsDelayAction(u16 action)
{
    switch (action) {
    case MOVEMENT_ACTION_DELAY_1:
    case MOVEMENT_ACTION_DELAY_2:
    case MOVEMENT_ACTION_DELAY_4:
    case MOVEMENT_ACTION_DELAY_8:
    case MOVEMENT_ACTION_DELAY_15:
    case MOVEMENT_ACTION_DELAY_16:
    case MOVEMENT_ACTION_DELAY_32:
        return TRUE;
    default:
        return FALSE;
    }
}

static BOOL FollowerMon_IsStationaryAction(u16 action, int dir)
{
    static const u16 bases[] = {
        MOVEMENT_ACTION_FACE_NORTH,
        MOVEMENT_ACTION_WALK_ON_SPOT_SLOWER_NORTH,
        MOVEMENT_ACTION_WALK_ON_SPOT_SLOW_NORTH,
        MOVEMENT_ACTION_WALK_ON_SPOT_NORMAL_NORTH,
        MOVEMENT_ACTION_WALK_ON_SPOT_FAST_NORTH,
        MOVEMENT_ACTION_WALK_ON_SPOT_FASTER_NORTH,
        MOVEMENT_ACTION_JUMP_ON_SPOT_SLOW_NORTH,
        MOVEMENT_ACTION_JUMP_ON_SPOT_FAST_NORTH,
    };

    for (u32 i = 0; i < NELEMS(bases); i++) {
        if (MovementAction_TurnActionTowardsDir(dir, bases[i]) == action) {
            return TRUE;
        }
    }

    return FALSE;
}

static void FollowerMon_PushAnim(MapObjectAnimCmd *cmds, int *out, u16 action, u16 count)
{
    if (*out > 0 && cmds[*out - 1].movementAction == action) {
        cmds[*out - 1].count += count;
        return;
    }

    cmds[*out].movementAction = action;
    cmds[*out].count = count;
    (*out)++;
}

static int FollowerMon_DirFromDelta(int dx, int dz)
{
    if (dx == 0 && dz < 0) {
        return DIR_NORTH;
    }
    if (dx == 0 && dz > 0) {
        return DIR_SOUTH;
    }
    if (dx < 0 && dz == 0) {
        return DIR_WEST;
    }
    if (dx > 0 && dz == 0) {
        return DIR_EAST;
    }
    return DIR_NONE;
}

MapObjectAnimCmd *FollowerMon_BuildTrailingAnim(FieldSystem *fieldSystem, const MapObjectAnimCmd *playerCmds)
{
    MapObject *follower;
    MapObjectAnimCmd *result;
    int px, pz, fx, fz, cmdCount, totalCount, out, moves;

    if (SystemFlag_CheckHasPartner(SaveData_GetVarsFlags(fieldSystem->saveData)) == TRUE) {
        return NULL;
    }

    follower = MapObjMan_GetLocalMapObjByMovementType(fieldSystem->mapObjMan, MOVEMENT_TYPE_FOLLOW_PLAYER);

    if (follower == NULL) {
        return NULL;
    }

    px = Player_GetXPos(fieldSystem->playerAvatar);
    pz = Player_GetZPos(fieldSystem->playerAvatar);
    fx = MapObject_GetX(follower);
    fz = MapObject_GetZ(follower);

    cmdCount = 0;
    totalCount = 0;
    while (playerCmds[cmdCount].movementAction != MOVEMENT_ACTION_END) {
        totalCount += playerCmds[cmdCount].count;
        cmdCount++;
    }

    result = Heap_Alloc(HEAP_ID_FIELD1, sizeof(MapObjectAnimCmd) * (totalCount + cmdCount + 1));

    if (result == NULL) {
        return NULL;
    }

    out = 0;
    moves = 0;

    for (int i = 0; i < cmdCount; i++) {
        u16 action = playerCmds[i].movementAction;
        u16 count = playerCmds[i].count;
        int dir = MovementAction_GetDirFromAction(action);

        if (FollowerMon_IsDelayAction(action)) {
            FollowerMon_PushAnim(result, &out, action, count);
            continue;
        }

        if (dir == DIR_NONE || FollowerMon_IsStationaryAction(action, dir)) {
            continue;
        }

        for (int step = 0; step < count; step++) {
            int pnx = px + MapObject_GetDxFromDir(dir);
            int pnz = pz + MapObject_GetDzFromDir(dir);
            int fStepDir;

            if (pnx == fx && pnz == fz) {
                fStepDir = dir;
            } else {
                fStepDir = FollowerMon_DirFromDelta(px - fx, pz - fz);

                if (fStepDir == DIR_NONE) {
                    fStepDir = dir;
                }
            }

            FollowerMon_PushAnim(result, &out, MovementAction_TurnActionTowardsDir(fStepDir, action), 1);

            fx += MapObject_GetDxFromDir(fStepDir);
            fz += MapObject_GetDzFromDir(fStepDir);
            px = pnx;
            pz = pnz;
            moves++;
        }
    }

    if (moves == 0) {
        Heap_Free(result);
        return NULL;
    }

    result[out].movementAction = MOVEMENT_ACTION_END;
    result[out].count = 0;

    return result;
}

static MapObject *FollowerMon_GetObject(FieldSystem *fieldSystem)
{
    MapObject *follower = MapObjMan_GetLocalMapObjByMovementType(fieldSystem->mapObjMan, MOVEMENT_TYPE_FOLLOW_PLAYER);

    if (follower != NULL && MapObject_GetLocalID(follower) == FOLLOWER_LOCAL_ID) {
        return follower;
    }

    return NULL;
}

static void FollowerMon_ShrinkIntoBall(MapObject *follower, int frame)
{
    Billboard *billboard = ov5_021EB1A0(follower);
    VecFx32 scale;
    fx32 progress;

    if (billboard == NULL) {
        return;
    }

    if (frame > FOLLOWER_RECALL_SHRINK_FRAMES) {
        frame = FOLLOWER_RECALL_SHRINK_FRAMES;
    }

    progress = (FX32_ONE - FOLLOWER_RECALL_MIN_SCALE) * frame / FOLLOWER_RECALL_SHRINK_FRAMES;
    scale.x = FX32_ONE - progress;
    scale.y = scale.x;
    scale.z = scale.x;

    Billboard_SetScale(billboard, &scale);

}

static void FollowerMon_FadeBall(MapObject *follower, int frame)
{
    Billboard *billboard = ov5_021EB1A0(follower);
    NNSG3dResMdl *model;
    int alpha;

    if (billboard == NULL) {
        return;
    }

    alpha = 31 - ((31 * frame) / FOLLOWER_RECALL_BALL_FRAMES);

    if (alpha < 0) {
        alpha = 0;
    }

    model = Billboard_GetModel(billboard);

    NNS_G3dMdlUseMdlAlpha(model);
    NNS_G3dMdlSetMdlAlphaAll(model, alpha);
}

BOOL FollowerMon_StartRecall(FieldSystem *fieldSystem)
{
    if (FollowerMon_GetObject(fieldSystem) == NULL) {
        return FALSE;
    }

    fieldSystem->followMon.recallState = FOLLOWER_RECALL_STATE_TURN;
    fieldSystem->followMon.recallTimer = 0;

    return TRUE;
}

BOOL FollowerMon_UpdateRecall(FieldSystem *fieldSystem)
{
    MapObject *follower = FollowerMon_GetObject(fieldSystem);
    int dir;

    if (follower == NULL) {
        return TRUE;
    }

    switch (fieldSystem->followMon.recallState) {
    case FOLLOWER_RECALL_STATE_TURN:
        dir = sub_02064488(MapObject_GetX(follower),
            MapObject_GetZ(follower),
            Player_GetXPos(fieldSystem->playerAvatar),
            Player_GetZPos(fieldSystem->playerAvatar));

        ov5_021ECDFC(follower, dir);
        fieldSystem->followMon.recallState = FOLLOWER_RECALL_STATE_HOLD;
        break;

    case FOLLOWER_RECALL_STATE_HOLD:
        fieldSystem->followMon.recallTimer++;

        if (fieldSystem->followMon.recallTimer < FOLLOWER_RECALL_TURN_DELAY) {
            break;
        }

        Sound_PlayEffect(SEQ_SE_DP_BOWA2);

        fieldSystem->followMon.recallTimer = 0;
        fieldSystem->followMon.recallState = FOLLOWER_RECALL_STATE_SHRINK;
        break;

    case FOLLOWER_RECALL_STATE_SHRINK:
        fieldSystem->followMon.recallTimer++;
        FollowerMon_ShrinkIntoBall(follower, fieldSystem->followMon.recallTimer);

        if (fieldSystem->followMon.recallTimer < FOLLOWER_RECALL_SHRINK_FRAMES) {
            break;
        }

        sub_02061AD4(follower, OBJ_EVENT_GFX_POKEBALL);

        fieldSystem->followMon.recallTimer = 0;
        fieldSystem->followMon.recallState = FOLLOWER_RECALL_STATE_BALL;
        break;

    case FOLLOWER_RECALL_STATE_BALL:
        fieldSystem->followMon.recallTimer++;
        FollowerMon_FadeBall(follower, fieldSystem->followMon.recallTimer);

        if (fieldSystem->followMon.recallTimer < FOLLOWER_RECALL_BALL_FRAMES) {
            break;
        }

        FollowerMon_FadeBall(follower, 0);
        FollowerMon_Despawn(fieldSystem);
        return TRUE;
    }

    return FALSE;
}

void FollowerMon_Despawn(FieldSystem *fieldSystem)
{
    MapObject *follower = MapObjMan_GetLocalMapObjByMovementType(fieldSystem->mapObjMan, MOVEMENT_TYPE_FOLLOW_PLAYER);

    if (follower != NULL) {
        MapObject_Delete(follower);
    }

    fieldSystem->followMon.active = FALSE;
}
