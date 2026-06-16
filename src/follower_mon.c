#include "follower_mon.h"

#include "constants/player_avatar.h"

#include "field/field_system.h"
#include "generated/genders.h"
#include "generated/movement_types.h"
#include "generated/object_events_gfx.h"
#include "follower_mon_gfx.h"
#include "location.h"
#include "map_header_data.h"
#include "map_object.h"
#include "script_manager.h"
#include "map_object_move.h"
#include "party.h"
#include "player_avatar.h"
#include "pokemon.h"
#include "savedata.h"
#include "system_flags.h"
#include "terrain_collision_manager.h"

#define FOLLOWER_LOCAL_ID 253

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

    // Surf/Waterfall
    if (PlayerAvatar_GetPlayerState(fieldSystem->playerAvatar) == PLAYER_STATE_SURFING) {
        return;
    }

    gfxID = FollowerMon_GetLeadGfxID(fieldSystem, &species, &gender);

    if (gfxID == OBJ_EVENT_GFX_INVISIBLE) {
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
