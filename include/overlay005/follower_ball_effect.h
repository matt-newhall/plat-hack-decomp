#ifndef POKEPLATINUM_OVERLAY005_FOLLOWER_BALL_EFFECT_H
#define POKEPLATINUM_OVERLAY005_FOLLOWER_BALL_EFFECT_H

#include "struct_decls/map_object.h"

#include "overlay005/field_effect_manager.h"

#include "overworld_anim_manager.h"

/**
 * @brief Allocates the follower ball effect's shared resources.
 *
 * @param fieldEffMan
 * @return The renderer context, owned by the field effect manager
 */
void *FollowerBallEffect_New(FieldEffectManager *fieldEffMan);

/**
 * @brief Frees the follower ball effect's shared resources.
 *
 * @param context
 */
void FollowerBallEffect_Free(void *context);

/**
 * @brief Plays the Poke Ball burst that accompanies a follower being sent out at a map object's position.
 *
 * The effect runs itself to completion and tidies up, so the caller only needs
 * to hide whatever is being recalled.
 *
 * @param mapObj The object being put away
 * @return The animation manager driving the effect
 */
OverworldAnimManager *FollowerBallEffect_Start(MapObject *mapObj);

#endif // POKEPLATINUM_OVERLAY005_FOLLOWER_BALL_EFFECT_H
