#include "overlay006/roamer_after_battle.h"

#include <nitro.h>
#include <string.h>

#include "constants/battle.h"
#include "constants/roamer_states.h"

#include "struct_defs/special_encounter.h"

#include "field/field_system.h"

#include "field_battle_data_transfer.h"
#include "heap.h"
#include "inlines.h"
#include "party.h"
#include "pokemon.h"
#include "roaming_pokemon.h"
#include "special_encounter.h"
#include "system_vars.h"
#include "vars_flags.h"

static void MoveRoamersOffMap(SpecialEncounter *param0, const int currentMap);
static Roamer *GetBattledRoamer(SpecialEncounter *speEnc, const int species);

void RoamerAfterBattle_UpdateRoamers(FieldSystem *fieldSystem, FieldBattleDTO *battleParams)
{
    u16 roamerHP;
    u8 roamerStatus;
    int wildSpecies;
    SpecialEncounter *specialEncounter;
    Roamer *roamer;
    Party *enemyParty = battleParams->parties[1];
    Pokemon *enemyMon = Party_GetPokemonBySlotIndex(enemyParty, 0);
    specialEncounter = SaveData_GetSpecialEncounters(fieldSystem->saveData);
    wildSpecies = Pokemon_GetValue(enemyMon, MON_DATA_SPECIES, NULL);
    roamer = GetBattledRoamer(specialEncounter, wildSpecies);

    if (roamer != NULL) {
        roamerHP = (u16)(Pokemon_GetValue(enemyMon, MON_DATA_HP, NULL));
        roamerStatus = (u8)(Pokemon_GetValue(enemyMon, MON_DATA_STATUS, NULL));

        if (battleParams->resultMask == BATTLE_RESULT_WIN && roamerHP == 0) {
            // Defeated: roamer stays in pool at full HP
            Pokemon *healedMon = Pokemon_New(HEAP_ID_FIELD1);

            Pokemon_InitAndCalcStats(
                healedMon,
                Roamer_GetData(roamer, ROAMER_DATA_SPECIES),
                Roamer_GetData(roamer, ROAMER_DATA_LEVEL),
                Roamer_GetData(roamer, ROAMER_DATA_IVS),
                Roamer_GetData(roamer, ROAMER_DATA_PERSONALITY));
            Roamer_SetData(roamer, ROAMER_DATA_CURRENT_HP, Pokemon_GetValue(healedMon, MON_DATA_MAX_HP, NULL));
            Roamer_SetData(roamer, ROAMER_DATA_STATUS, 0);
            Heap_Free(healedMon);
        } else if (battleParams->resultMask == BATTLE_RESULT_CAPTURED_MON) {
            SpecialEncounter_ZeroRoamerData(&roamer);
            SystemVars_SetRoamingSpeciesState(SaveData_GetVarsFlags(fieldSystem->saveData), wildSpecies, ROAMER_STATE_CAPTURED);
        } else {
            // Fled: keep chip damage
            Roamer_SetData(roamer, ROAMER_DATA_CURRENT_HP, roamerHP);
            Roamer_SetData(roamer, ROAMER_DATA_STATUS, roamerStatus);
        }

        MoveRoamersOffMap(specialEncounter, fieldSystem->location->mapId); // all roamers leave if you encounter one
    } else {
        if (LCRNG_RandMod(100) < 30) { // 30% chance for roamers to leave even if you don't encounter one
            MoveRoamersOffMap(specialEncounter, fieldSystem->location->mapId);
        }
    }
}

// Relocates the whole roamer herd if it is currently on the player's map.
static void MoveRoamersOffMap(SpecialEncounter *speEnc, const int currentMap)
{
    for (u8 i = 0; i < ROAMING_SLOT_MAX; i++) {
        if (SpecialEncounter_IsRoamerActive(speEnc, i)) {
            if (currentMap == RoamingPokemon_GetRouteFromId(SpecialEncounter_GetRoamerRouteIndex(speEnc, i))) {
                RoamingPokemon_MoveAllLocations(speEnc);
            }

            break;
        }
    }
}

static Roamer *GetBattledRoamer(SpecialEncounter *speEnc, const int species)
{
    u8 i;
    Roamer *roamer;

    for (i = 0; i < ROAMING_SLOT_MAX; i++) {
        if (SpecialEncounter_IsRoamerActive(speEnc, i)) {
            roamer = SpecialEncounter_GetRoamer(speEnc, i);

            if (species == Roamer_GetData(roamer, ROAMER_DATA_SPECIES)) {
                return roamer;
            }
        }
    }

    return NULL;
}
