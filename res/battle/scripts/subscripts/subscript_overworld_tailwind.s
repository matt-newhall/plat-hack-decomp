#include "macros/btlcmd.inc"

    .data

_000:
    UpdateVar OPCODE_SET, BTLVAR_MSG_MOVE_TEMP, MOVE_TAILWIND
    PlayMoveAnimation BTLSCR_MSG_TEMP
    // The tailwind blew from behind the foe!
    PrintMessage pl_msg_00000368_01231, TAG_NONE_SIDE_CONSCIOUS, BTLSCR_ATTACKER
    Wait 
    WaitButtonABTime 30
    UpdateVar OPCODE_FLAG_ON, BTLVAR_FIELD_CONDITIONS, FIELD_CONDITION_TAILWIND_PERM
    End 
