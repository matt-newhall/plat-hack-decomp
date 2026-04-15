#include "macros/btlcmd.inc"


_000:
    // {0} was prevented from healing due to {1}!
    PrintMessage BattleStrings_Text_PokemonWasPreventedFromHealingDueToMove_Ally, TAG_NICKNAME_MOVE, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait 
    WaitButtonABTime 30
    End 
