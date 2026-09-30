#include "macros/btlcmd.inc"

    .data

_000:
    CompareVarToValue OPCODE_FLAG_SET, BTLVAR_FIELD_CONDITIONS, FIELD_CONDITION_TERRAIN_PERM, _done
    CompareVarToValue OPCODE_FLAG_NOT, BTLVAR_FIELD_CONDITIONS, FIELD_CONDITION_TERRAIN, _done
    CompareVarToValue OPCODE_FLAG_SET, BTLVAR_FIELD_CONDITIONS, FIELD_CONDITION_ELECTRIC_TERRAIN, _electric
    CompareVarToValue OPCODE_FLAG_SET, BTLVAR_FIELD_CONDITIONS, FIELD_CONDITION_GRASSY_TERRAIN, _grassy
    CompareVarToValue OPCODE_FLAG_SET, BTLVAR_FIELD_CONDITIONS, FIELD_CONDITION_MISTY_TERRAIN, _misty
    // The weirdness disappeared from the battlefield!
    PrintMessage BattleStrings_Text_PsychicTerrainEnded, TAG_NONE
    GoTo _end

_electric:
    // The electricity disappeared from the battlefield.
    PrintMessage BattleStrings_Text_ElectricTerrainEnded, TAG_NONE
    GoTo _end

_grassy:
    // The grass disappeared from the battlefield.
    PrintMessage BattleStrings_Text_GrassyTerrainEnded, TAG_NONE
    GoTo _end

_misty:
    // The mist disappeared from the battlefield.
    PrintMessage BattleStrings_Text_MistyTerrainEnded, TAG_NONE

_end:
    Wait
    WaitButtonABTime 30
    UpdateVar OPCODE_FLAG_OFF, BTLVAR_FIELD_CONDITIONS, FIELD_CONDITION_TERRAIN
    SetTerrainBackground
    Wait
    End

_done:
    End
