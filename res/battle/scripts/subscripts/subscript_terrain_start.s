#include "macros/btlcmd.inc"

    .data

_000:
    SetTerrainBackground
    Wait
    CompareVarToValue OPCODE_FLAG_SET, BTLVAR_FIELD_CONDITIONS, FIELD_CONDITION_ELECTRIC_TERRAIN, _electric
    CompareVarToValue OPCODE_FLAG_SET, BTLVAR_FIELD_CONDITIONS, FIELD_CONDITION_GRASSY_TERRAIN, _grassy
    CompareVarToValue OPCODE_FLAG_SET, BTLVAR_FIELD_CONDITIONS, FIELD_CONDITION_MISTY_TERRAIN, _misty
    // The battlefield got weird!
    PrintMessage BattleStrings_Text_PsychicTerrainStarted, TAG_NONE
    GoTo _end

_electric:
    // An electric current ran across the battlefield!
    PrintMessage BattleStrings_Text_ElectricTerrainStarted, TAG_NONE
    GoTo _end

_grassy:
    // Grass grew to cover the battlefield!
    PrintMessage BattleStrings_Text_GrassyTerrainStarted, TAG_NONE
    GoTo _end

_misty:
    // Mist swirled about the battlefield!
    PrintMessage BattleStrings_Text_MistyTerrainStarted, TAG_NONE

_end:
    Wait
    WaitButtonABTime 30
    End
