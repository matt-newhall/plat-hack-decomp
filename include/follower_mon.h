#ifndef POKEPLATINUM_FOLLOWER_MON_H
#define POKEPLATINUM_FOLLOWER_MON_H

#include "struct_decls/map_object.h"

#include "field/field_system_decl.h"
#include "overlay005/map_object_anim_cmd.h"

void FollowerMon_UpdateFollower(FieldSystem *fieldSystem);
void FollowerMon_RestoreFollower(FieldSystem *fieldSystem);
void FollowerMon_SaveState(FieldSystem *fieldSystem);
void FollowerMon_Despawn(FieldSystem *fieldSystem);

/**
 * @brief Checks whether a map object is the player's following Pokemon.
 *
 * Partner NPCs share MOVEMENT_TYPE_FOLLOW_PLAYER with the follower
 *
 * @param mapObj
 * @return TRUE if the object is the follower
 */
BOOL FollowerMon_IsFollowerObject(const MapObject *mapObj);

/**
 * @brief Checks whether a movement action carries its object onto a new tile.
 *
 * @param action
 * @return TRUE if the action is a real step
 */
BOOL FollowerMon_IsWalkingAction(u16 action);

/**
 * @brief Begins the return-to-ball sequence for the follower.
 *
 * @param fieldSystem
 * @return FALSE if no follower is out, in which case there is nothing to wait for
 */
BOOL FollowerMon_StartRecall(FieldSystem *fieldSystem);

/**
 * @brief Advances the return-to-ball sequence by one frame.
 *
 * The follower turns to face the player, holds a beat, then vanishes with the
 * ball sound. Drive this once per frame until it reports completion.
 *
 * @param fieldSystem
 * @return TRUE once the follower has been sent back
 */
BOOL FollowerMon_UpdateRecall(FieldSystem *fieldSystem);

MapObjectAnimCmd *FollowerMon_BuildTrailingAnim(FieldSystem *fieldSystem, const MapObjectAnimCmd *playerCmds);

#endif // POKEPLATINUM_FOLLOWER_MON_H
