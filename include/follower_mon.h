#ifndef POKEPLATINUM_FOLLOWER_MON_H
#define POKEPLATINUM_FOLLOWER_MON_H

#include "constants/heap.h"
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
 * @brief Checks whether an overworld graphics ID is a Pokemon sprite.
 *
 * Covers the follower and any NPC partner Pokemon, which share the same
 * sprite set and so share the follower heap.
 *
 * @param gfxID
 * @return TRUE for any OBJ_EVENT_GFX_PKMN_* ID
 */
BOOL FollowerMon_IsMonGfxID(int gfxID);

/**
 * @brief Picks the heap a follower allocation should come from.
 *
 * Prefers the dedicated follower heap and only spills into FIELD1 when the
 * block does not fit, so follower memory never competes with vanilla objects
 * unless the follower budget is exhausted.
 *
 * @param size Allocation size in bytes
 * @return HEAP_ID_FOLLOWER if the block fits there, otherwise HEAP_ID_FIELD1
 */
enum HeapID FollowerMon_PickHeap(u32 size);

/**
 * @brief Checks whether a movement action carries its object onto a new tile.
 *
 * @param action
 * @return TRUE if the action is a real step
 */
BOOL FollowerMon_IsWalkingAction(u16 action);

/**
 * @brief Picks the action the follower should use for one trailing step.
 *
 * @param playerAction Action the player is currently running
 * @param stepDir Direction of the follower's next step
 * @param lastJumpAction Multi-tile jump the follower has already reacted to
 * @return The action for the caller to turn towards stepDir
 */
u16 FollowerMon_ResolveStepAction(u16 playerAction, int stepDir, u16 *lastJumpAction);

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
