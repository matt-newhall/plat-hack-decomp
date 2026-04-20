#include "macros/btlcmd.inc"


_000:
    PrintAttackMessage 
    Wait 
    WaitButtonABTime 30
    // But there was no target...
    PrintMessage BattleStrings_Text_ButThereWasNoTarget, TAG_NONE
    Wait 
    WaitButtonABTime 30
    UnlockMoveChoice BTLSCR_ATTACKER
    End 
