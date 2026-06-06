#include "follower_mon.h"

#include "field/field_system.h"
#include "generated/genders.h"
#include "generated/movement_types.h"
#include "generated/object_events_gfx.h"
#include "follower_mon_gfx.h"
#include "location.h"
#include "map_header_data.h"
#include "map_object.h"
#include "map_object_move.h"
#include "map_tile_behavior.h"
#include "party.h"
#include "player_avatar.h"
#include "pokemon.h"
#include "savedata.h"
#include "terrain_collision_manager.h"

void FollowerMon_UpdateFollower(FieldSystem *fieldSystem)
{
    Party *party;
    Pokemon *lead;
    u16 species;
    u8  gender;
    u16 gfxID;
    MapObject *follower;
    int x;
    int z;
    int i;
    int partyCount;
    int dir;

    party = SaveData_GetParty(fieldSystem->saveData);
    partyCount = Party_GetCurrentCount(party);

    for (i = 0; i < partyCount; i++) {
        lead = Party_GetPokemonBySlotIndex(party, i);

        if (Pokemon_GetValue(lead, MON_DATA_HP, NULL)) {
            break;
        }
    }

    if (Pokemon_GetValue(lead, MON_DATA_IS_EGG, NULL)) {
        return;
    }

    species = (u16)Pokemon_GetValue(lead, MON_DATA_SPECIES, NULL);
    gender  = (u8)Pokemon_GetValue(lead, MON_DATA_GENDER, NULL);
    gfxID   = FollowerMon_GetGfxID(species, gender == GENDER_FEMALE);

    if (gfxID == OBJ_EVENT_GFX_INVISIBLE) {
        return;
    }

    follower = MapObjMan_GetLocalMapObjByMovementType(fieldSystem->mapObjMan, MOVEMENT_TYPE_FOLLOW_PLAYER);
    if (follower != NULL) {
        if (MapObject_GetGraphicsID(follower) == gfxID) {
            return;
        }
        MapObject_SetFlagAndDeleteObject(follower);
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

    {
        u8 behavior = TerrainCollisionManager_GetTileBehavior(fieldSystem, x, z);
        if (TileBehavior_IsNull(behavior)
                || TileBehavior_IsDoor(behavior)
                || TileBehavior_IsWarpPanel(behavior)
                || TileBehavior_IsWarpEntranceNorth(behavior)
                || TileBehavior_IsWarpEntranceSouth(behavior)
                || TileBehavior_IsWarpEntranceEast(behavior)
                || TileBehavior_IsWarpEntranceWest(behavior)) {
            return;
        }
    }

    {
        ObjectEvent objectEvent;
        ObjectEvent_SetLocalID(&objectEvent, 253);
        ObjectEvent_SetGraphicsID(&objectEvent, gfxID);
        ObjectEvent_SetMovementType(&objectEvent, MOVEMENT_TYPE_FOLLOW_PLAYER);
        ObjectEvent_SetTrainerType(&objectEvent, 0);
        ObjectEvent_SetHiddenFlag(&objectEvent, 0);
        ObjectEvent_SetScript(&objectEvent, 0xFFFF);
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
    }

    if (follower == NULL) {
        return;
    }

    MapObject_SetStatusFlagOn(follower, MAP_OBJ_STATUS_PERSISTENT);
    MapObject_RecalculateObjectHeight(follower);

    fieldSystem->followMon.species = species;
    fieldSystem->followMon.gender  = gender;
    fieldSystem->followMon.active  = TRUE;
}
