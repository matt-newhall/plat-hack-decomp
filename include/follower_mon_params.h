#ifndef POKEPLATINUM_FOLLOWER_MON_PARAMS_H
#define POKEPLATINUM_FOLLOWER_MON_PARAMS_H

#include <nitro.h>

/**
 * @brief How quickly a follower bobs up and down as it walks.
 *
 * HGSS stores this per species in narc a/1/4/1 as the low nibble of a byte;
 * the high nibble is an unrelated property, which is why its OVERWORLD_BOUNCE_MED
 * bobs at the same rate as OVERWORLD_BOUNCE_FAST.
 */
enum FollowerBounceSpeed {
    FOLLOWER_BOUNCE_FAST = 0,
    FOLLOWER_BOUNCE_SLOW
};

typedef struct {
    u8 isLarge;
    u8 bounceSpeed;
} FollowerMonParams;

/**
 * @brief Checks whether a species is too big to follow onto a height-restricted map.
 *
 * @param species
 * @return TRUE if the species should be left in its ball on such maps
 */
BOOL FollowerMon_IsLargeSpecies(u16 species);

/**
 * @brief Gets a species' bounce speed.
 *
 * @param species
 * @return One of enum FollowerBounceSpeed
 */
u8 FollowerMon_GetBounceSpeed(u16 species);

#endif // POKEPLATINUM_FOLLOWER_MON_PARAMS_H
