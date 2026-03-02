#include "macros/btlcmd.inc"

    .data

_000:
    // {0} filled the air with Neutralizing Gas!
    PrintMessage pl_msg_00000368_01322, TAG_NICKNAME, BTLSCR_MSG_BATTLER_TEMP
    Wait
    WaitButtonABTime 30
    End
