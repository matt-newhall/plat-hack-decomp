#include "macros/btlcmd.inc"


_000:
    IfSameSide BTLSCR_ATTACKER, BTLSCR_ENEMY, _016
    RecordPayDayUse

_016:
    // Coins scattered everywhere!
    PrintMessage BattleStrings_Text_CoinsScatteredEverywhere, TAG_NONE
    Wait
    WaitButtonABTime 30
    End
