#include "macros/btlcmd.inc"

    .data

_000:
    PlayBattleAnimation BTLSCR_PLAYER, BATTLE_ANIMATION_WEATHER_RAIN
    Wait
    // It started to rain!
    PrintMessage BattleStrings_Text_ItStartedToRain, TAG_NONE
    Wait
    WaitButtonABTime 30
    UpdateVar OPCODE_FLAG_ON, BTLVAR_FIELD_CONDITIONS, FIELD_CONDITION_RAINING_PERM
    SetTerrainBackground
    Wait
    // An electric current ran across the battlefield!
    PrintMessage BattleStrings_Text_ElectricTerrainStarted, TAG_NONE
    Wait
    WaitButtonABTime 30
    End
