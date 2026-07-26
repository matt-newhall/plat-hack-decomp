#include "roaming_pokemon.h"

#include <nitro.h>
#include <string.h>

#include "constants/species.h"
#include "generated/map_headers.h"

#include "struct_defs/special_encounter.h"

#include "heap.h"
#include "inlines.h"
#include "pokemon.h"
#include "save_player.h"
#include "savedata.h"
#include "special_encounter.h"
#include "trainer_info.h"

static u8 PickHerdLocation(void);
static void MoveHerd(SpecialEncounter *speEnc, const int playerPreviousMap);

// filter roamers to just these regions and they are now a shared pool
// like Run and Bun
static const u8 sRoamerAllowedRoutes[] = {
    RI_ROUTE_219,
    RI_ROUTE_220,
    RI_ROUTE_221,
    RI_ROUTE_222,
    RI_ROUTE_223,
    RI_ROUTE_224,
};

// All outdoor areas with encounters on the mainland except Trophy Garden, Great Marsh, and the ones past Sunyshore City
static const int RoamingPokemonRoutes[RI_MAX] = {
    [RI_ROUTE_201] = MAP_HEADER_ROUTE_201,
    [RI_ROUTE_202] = MAP_HEADER_ROUTE_202,
    [RI_ROUTE_203] = MAP_HEADER_ROUTE_203,
    [RI_ROUTE_204_SOUTH] = MAP_HEADER_ROUTE_204_SOUTH,
    [RI_ROUTE_204_NORTH] = MAP_HEADER_ROUTE_204_NORTH,
    [RI_ROUTE_205_SOUTH] = MAP_HEADER_ROUTE_205_SOUTH,
    [RI_ROUTE_205_NORTH] = MAP_HEADER_ROUTE_205_NORTH,
    [RI_ROUTE_206] = MAP_HEADER_ROUTE_206,
    [RI_ROUTE_207] = MAP_HEADER_ROUTE_207,
    [RI_ROUTE_208] = MAP_HEADER_ROUTE_208,
    [RI_ROUTE_209] = MAP_HEADER_ROUTE_209,
    [RI_ROUTE_210_SOUTH] = MAP_HEADER_ROUTE_210_SOUTH,
    [RI_ROUTE_210_NORTH] = MAP_HEADER_ROUTE_210_NORTH,
    [RI_ROUTE_211_WEST] = MAP_HEADER_ROUTE_211_WEST,
    [RI_ROUTE_211_EAST] = MAP_HEADER_ROUTE_211_EAST,
    [RI_ROUTE_212_NORTH] = MAP_HEADER_ROUTE_212_NORTH,
    [RI_ROUTE_212_SOUTH] = MAP_HEADER_ROUTE_212_SOUTH,
    [RI_ROUTE_213] = MAP_HEADER_ROUTE_213,
    [RI_ROUTE_214] = MAP_HEADER_ROUTE_214,
    [RI_ROUTE_215] = MAP_HEADER_ROUTE_215,
    [RI_ROUTE_216] = MAP_HEADER_ROUTE_216,
    [RI_ROUTE_217] = MAP_HEADER_ROUTE_217,
    [RI_ROUTE_218] = MAP_HEADER_ROUTE_218,
    [RI_ROUTE_219] = MAP_HEADER_ROUTE_219,
    [RI_ROUTE_220] = MAP_HEADER_ROUTE_220,
    [RI_ROUTE_221] = MAP_HEADER_ROUTE_221,
    [RI_ROUTE_222] = MAP_HEADER_ROUTE_222,
    [RI_ROUTE_223] = MAP_HEADER_ROUTE_223,
    [RI_ROUTE_224] = MAP_HEADER_ROUTE_224,
    [RI_VALLEY_WINDWORKS_OUTSIDE] = MAP_HEADER_VALLEY_WINDWORKS_OUTSIDE,
    [RI_FUEGO_IRONWORKS_OUTSIDE] = MAP_HEADER_FUEGO_IRONWORKS_OUTSIDE,
};

static u8 PickHerdLocation(void)
{
    return sRoamerAllowedRoutes[LCRNG_RandMod(NELEMS(sRoamerAllowedRoutes))];
}

// moves roamers to a new location
static void MoveHerd(SpecialEncounter *speEnc, const int playerPreviousMap)
{
    int currentRoute = -1;
    u8 newIndex;
    int newRoute;

    for (u8 i = 0; i < ROAMING_SLOT_MAX; i++) {
        if (SpecialEncounter_IsRoamerActive(speEnc, i)) {
            currentRoute = RoamingPokemonRoutes[SpecialEncounter_GetRoamerRouteIndex(speEnc, i)];
            break;
        }
    }

    if (currentRoute == -1) {
        return;
    }

    while (TRUE) {
        newIndex = PickHerdLocation();
        newRoute = RoamingPokemonRoutes[newIndex];

        if ((newRoute != playerPreviousMap) && (newRoute != currentRoute)) {
            break;
        }
    }

    for (u8 i = 0; i < ROAMING_SLOT_MAX; i++) {
        if (SpecialEncounter_IsRoamerActive(speEnc, i)) {
            SpecialEncounter_SetRoamerRouteIndex(speEnc, i, newIndex);
            Roamer_SetData(SpecialEncounter_GetRoamer(speEnc, i), ROAMER_DATA_MAP_ID, newRoute);
        }
    }

    SpecialEncounter_FlagRoamerPositionsChanged();
}

// Used when Teleporting/Flying
void RoamingPokemon_RandomizeAllLocations(SpecialEncounter *speEnc)
{
    MoveHerd(speEnc, SpecialEncounter_GetPlayerPreviousMap(speEnc));
}

// When the player changes maps. Moves the whole roamer herd to a new allowed route.
void RoamingPokemon_MoveAllLocations(SpecialEncounter *speEnc)
{
    MoveHerd(speEnc, SpecialEncounter_GetPlayerPreviousMap(speEnc));
}

int RoamingPokemon_GetRouteFromId(const u8 routeId)
{
    GF_ASSERT(routeId < RI_MAX);
    return RoamingPokemonRoutes[routeId];
}

BOOL RoamingPokemon_AnyRoamersActive(SpecialEncounter *speEnc)
{

    for (u8 i = 0; i < ROAMING_SLOT_MAX; i++) {
        if (SpecialEncounter_IsRoamerActive(speEnc, i)) {
            return TRUE;
        }
    }

    return FALSE;
}

// Runs when the player changes maps. Roamers cannot move to the map the player just left.
void RoamingPokemon_UpdatePlayerRecentRoutes(SpecialEncounter *speEnc, const int newMap)
{
    if (RoamingPokemon_AnyRoamersActive(speEnc)) {
        SpecialEncounter_UpdateRecentRoutes(speEnc, newMap);
    }
}

void RoamingPokemon_ActivateSlot(SaveData *saveData, const u8 slot)
{
    Pokemon *roamerMonData;
    Roamer *newRoamer;
    SpecialEncounter *speEnc;
    TrainerInfo *trainer;
    int species;
    u8 level;

    speEnc = SaveData_GetSpecialEncounters(saveData);
    newRoamer = SpecialEncounter_GetRoamer(speEnc, slot);

    switch (slot) {
    case ROAMING_SLOT_MESPRIT:
        species = SPECIES_MESPRIT;
        level = 50;
        break;
    case ROAMING_SLOT_CRESSELIA:
        species = SPECIES_CRESSELIA;
        level = 50;
        break;
    case ROAMING_SLOT_UXIE:
        species = SPECIES_UXIE;
        level = 60;
        break;
    case ROAMING_SLOT_MOLTRES:
        species = SPECIES_MOLTRES;
        level = 60;
        break;
    case ROAMING_SLOT_ZAPDOS:
        species = SPECIES_ZAPDOS;
        level = 60;
        break;
    case ROAMING_SLOT_ARTICUNO:
        species = SPECIES_ARTICUNO;
        level = 60;
        break;
    case ROAMING_SLOT_AZELF:
        species = SPECIES_AZELF;
        level = 60;
        break;
    case ROAMING_SLOT_LATIOS:
        species = SPECIES_LATIOS;
        level = 60;
        break;
    case ROAMING_SLOT_LATIAS:
        species = SPECIES_LATIAS;
        level = 60;
        break;
    case ROAMING_SLOT_RAIKOU:
        species = SPECIES_RAIKOU;
        level = 60;
        break;
    case ROAMING_SLOT_SUICUNE:
        species = SPECIES_SUICUNE;
        level = 60;
        break;
    case ROAMING_SLOT_ENTEI:
        species = SPECIES_ENTEI;
        level = 60;
        break;
    default:
        GF_ASSERT(0);
        return;
    }

    Roamer_SetData(newRoamer, ROAMER_DATA_SPECIES, species);
    Roamer_SetData(newRoamer, ROAMER_DATA_LEVEL, level);

    trainer = SaveData_GetTrainerInfo(saveData);
    roamerMonData = Pokemon_New(HEAP_ID_FIELD1);

    Pokemon_Init(roamerMonData);
    Pokemon_InitWith(roamerMonData, species, level, INIT_IVS_RANDOM, FALSE, 0, OTID_SET, TrainerInfo_ID_LowHalf(trainer));
    Roamer_SetData(newRoamer, ROAMER_DATA_STATUS, 0);
    Roamer_SetData(newRoamer, ROAMER_DATA_ACTIVE, 1);
    Roamer_SetData(newRoamer, ROAMER_DATA_IVS, Pokemon_GetValue(roamerMonData, MON_DATA_COMBINED_IVS, NULL));
    Roamer_SetData(newRoamer, ROAMER_DATA_PERSONALITY, Pokemon_GetValue(roamerMonData, MON_DATA_PERSONALITY, NULL));
    Roamer_SetData(newRoamer, ROAMER_DATA_CURRENT_HP, Pokemon_GetValue(roamerMonData, MON_DATA_MAX_HP, NULL));
    Heap_Free(roamerMonData);

    int herdIndex = -1;

    for (u8 i = 0; i < ROAMING_SLOT_MAX; i++) {
        if ((i != slot) && SpecialEncounter_IsRoamerActive(speEnc, i)) {
            herdIndex = SpecialEncounter_GetRoamerRouteIndex(speEnc, i);
            break;
        }
    }

    if (herdIndex == -1) {
        herdIndex = PickHerdLocation();
    }

    SpecialEncounter_SetRoamerRouteIndex(speEnc, slot, herdIndex);
    Roamer_SetData(newRoamer, ROAMER_DATA_MAP_ID, RoamingPokemonRoutes[herdIndex]);
}
