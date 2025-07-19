#include "macros/btlcmd.inc"

    .data

_000:
    UpdateVar OPCODE_FLAG_ON, BTLVAR_SIDE_CONDITIONS_ATTACKER, SIDE_CONDITION_FLEE_FAILED
    // Can’t escape!
    PrintMessage pl_msg_00000368_00042, TAG_NONE
    Wait 
    WaitButtonABTime 30
    End 
