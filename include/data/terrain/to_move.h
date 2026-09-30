#include "constants/battle/terrain.h"
#include "constants/moves.h"

// clang-format off
static const u16 sTerrainMove[] = {
    [TERRAIN_PLAIN]       = MOVE_EARTH_POWER,
    [TERRAIN_SAND]        = MOVE_EARTH_POWER,
    [TERRAIN_GRASS]       = MOVE_ENERGY_BALL,
    [TERRAIN_PUDDLE]      = MOVE_ENERGY_BALL,
    [TERRAIN_MOUNTAIN]    = MOVE_POWER_GEM,
    [TERRAIN_CAVE]        = MOVE_POWER_GEM,
    [TERRAIN_SNOW]        = MOVE_ICE_BEAM,
    [TERRAIN_WATER]       = MOVE_HYDRO_PUMP,
    [TERRAIN_ICE]         = MOVE_ICE_BEAM,
    [TERRAIN_BUILDING]    = MOVE_TRI_ATTACK,
    [TERRAIN_GREAT_MARSH] = MOVE_MUD_BOMB,
    [TERRAIN_BRIDGE]      = MOVE_AIR_SLASH,
    [TERRAIN_SPECIAL]     = MOVE_TRI_ATTACK,
};

static const struct {
    u32 fieldCondition;
    u16 move;
} sFieldTerrainMove[] = {
    { FIELD_CONDITION_ELECTRIC_TERRAIN, MOVE_THUNDERBOLT },
    { FIELD_CONDITION_GRASSY_TERRAIN,   MOVE_ENERGY_BALL },
    { FIELD_CONDITION_MISTY_TERRAIN,    MOVE_MOONBLAST   },
    { FIELD_CONDITION_PSYCHIC_TERRAIN,  MOVE_PSYCHIC     },
};
// clang-format on
