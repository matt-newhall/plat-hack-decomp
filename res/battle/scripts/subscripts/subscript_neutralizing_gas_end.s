#include "macros/btlcmd.inc"

    .data

_000:
    // Neutralizing Gas wore off!
    PrintMessage pl_msg_00000368_01325, TAG_NONE
    Wait
    WaitButtonABTime 30
    End
