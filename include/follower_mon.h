#ifndef POKEPLATINUM_FOLLOWER_MON_H
#define POKEPLATINUM_FOLLOWER_MON_H

#include "field/field_system_decl.h"
#include "overlay005/map_object_anim_cmd.h"

void FollowerMon_UpdateFollower(FieldSystem *fieldSystem);
void FollowerMon_RestoreFollower(FieldSystem *fieldSystem);
void FollowerMon_SaveState(FieldSystem *fieldSystem);
void FollowerMon_Despawn(FieldSystem *fieldSystem);

MapObjectAnimCmd *FollowerMon_BuildTrailingAnim(FieldSystem *fieldSystem, const MapObjectAnimCmd *playerCmds);

#endif // POKEPLATINUM_FOLLOWER_MON_H
