#include "macros/btlcmd.inc"

    .data

_000:
    TryPowerOfAlchemy _009
    // {0} acquired {1}!
    PrintMessage pl_msg_00000368_01021, TAG_NICKNAME_ABILITY, BTLSCR_MSG_BATTLER_TEMP, BTLSCR_MSG_BATTLER_TEMP
    Wait
    WaitButtonABTime 30

_009:
    Call BATTLE_SUBSCRIPT_FAINT_MON
    End
