#include "constants/items.h"

#define COMMON_PICKUP_ENTRIES 9

static const u16 sCommonPickupItems[] = {
    ITEM_POTION,
    ITEM_ANTIDOTE,
    ITEM_SUPER_POTION,
    ITEM_GREAT_BALL,
    ITEM_REPEL,
    ITEM_ESCAPE_ROPE,
    ITEM_FULL_HEAL,
    ITEM_HYPER_POTION,
    ITEM_ULTRA_BALL,
    ITEM_REVIVE,
    ITEM_RARE_CANDY,
    ITEM_SUN_STONE,
    ITEM_MOON_STONE,
    ITEM_HEART_SCALE,
    ITEM_FULL_RESTORE,
    ITEM_MAX_REVIVE,
    ITEM_PP_UP,
    ITEM_MAX_ELIXIR,
};

static const u16 sRarePickupItems[] = {
    ITEM_HYPER_POTION,
    ITEM_NUGGET,
    ITEM_KINGS_ROCK,
    ITEM_FULL_RESTORE,
    ITEM_ETHER,
    ITEM_IRON_BALL,
    ITEM_DESTINY_KNOT,
    ITEM_ELIXIR,
    ITEM_DESTINY_KNOT,
    ITEM_LEFTOVERS,
    ITEM_DESTINY_KNOT,
};

static const u8 sCommonPickupRate[] = {
    30,
    40,
    50,
    60,
    70,
    80,
    90,
    94,
    98,
};

static const u8 sHoneyGatherRate[] = {
    5,
    10,
    15,
    20,
    25,
    30,
    35,
    40,
    45,
    50,
};
