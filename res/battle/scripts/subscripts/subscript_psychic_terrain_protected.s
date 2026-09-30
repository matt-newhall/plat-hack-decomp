#include "macros/btlcmd.inc"

    .data

_000:
    PrintAttackMessage
    Wait
    WaitButtonABTime 30
    // {0} is protected by the Psychic Terrain!
    PrintMessage BattleStrings_Text_PokemonIsProtectedByThePsychicTerrain_Ally, TAG_NICKNAME, BTLSCR_DEFENDER
    Wait
    WaitButtonABTime 30
    End
