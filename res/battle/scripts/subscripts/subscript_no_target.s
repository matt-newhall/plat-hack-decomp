#include "macros/btlcmd.inc"

    .data

_000:
    PrintAttackMessage 
    Wait 
    WaitButtonABTime 30
    // But there was no target...
    PrintMessage pl_msg_00000368_01234, TAG_NONE
    Wait 
    WaitButtonABTime 30
    UnlockMoveChoice BTLSCR_ATTACKER
    End 
