#include "macros/btlcmd.inc"

    .data

_000:
    // {0} was prevented from healing due to {1}!
    PrintMessage pl_msg_00000368_01054, TAG_NICKNAME_MOVE, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait 
    WaitButtonABTime 30
    End 
