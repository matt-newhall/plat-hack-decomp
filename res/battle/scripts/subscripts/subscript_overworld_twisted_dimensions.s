#include "macros/btlcmd.inc"

    .data

_000:
    CompareVarToValue OPCODE_FLAG_SET, BTLVAR_FIELD_CONDITIONS, FIELD_CONDITION_TRICK_ROOM_PERM, _002
    UpdateVar OPCODE_FLAG_ON, BTLVAR_FIELD_CONDITIONS, FIELD_CONDITION_TRICK_ROOM_PERM
    Call BATTLE_SUBSCRIPT_OVERWORLD_TRICK_ROOM

_002:
    End