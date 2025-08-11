#include "macros/btlcmd.inc"

    .data

_000:
    CompareVarToValue OPCODE_EQU, BTLVAR_CURRENT_MOVE, MOVE_DARK_VOID, _001
    GoTo _002

_001:
    CompareMonDataToValue OPCODE_EQU, BTLSCR_ATTACKER, BATTLEMON_SPECIES, 491, _002
    PrintAttackMessage 
    Wait 
    WaitButtonABTime 30
    PrintMessage pl_msg_00000368_00796, TAG_NONE
    Wait 
    WaitButtonABTime 30
    UpdateVar OPCODE_FLAG_ON, BTLVAR_MOVE_STATUS_FLAGS, MOVE_STATUS_NO_MORE_WORK
    End

_002:
    UpdateVar OPCODE_SET, BTLVAR_SIDE_EFFECT_FLAGS_DIRECT, MOVE_SIDE_EFFECT_TO_DEFENDER|MOVE_SUBSCRIPT_PTR_SLEEP
    End