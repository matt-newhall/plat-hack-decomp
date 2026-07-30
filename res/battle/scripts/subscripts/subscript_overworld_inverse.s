#include "macros/btlcmd.inc"

    .data

_000:
    CompareVarToValue OPCODE_FLAG_SET, BTLVAR_FIELD_CONDITIONS, FIELD_CONDITION_INVERSE_PERM, _001
    UpdateVar OPCODE_FLAG_ON, BTLVAR_FIELD_CONDITIONS, FIELD_CONDITION_INVERSE_PERM
    // The rules of this world are inverted!
    PrintMessage BattleStrings_Text_InverseBattleAnnounced, TAG_NONE
    Wait
    WaitButtonABTime 30

_001:
    End
