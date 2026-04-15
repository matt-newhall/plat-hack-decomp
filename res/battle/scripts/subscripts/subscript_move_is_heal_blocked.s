#include "macros/btlcmd.inc"


_000:
    // Missing an UpdateVar now we got rid of Heal Block
    // {0} can’t use {2} because of {1}!
    PrintMessage BattleStrings_Text_PokemonCantUseMoveBecauseOfMove_Ally, TAG_NICKNAME_MOVE_MOVE, BTLSCR_ATTACKER, BTLSCR_MSG_TEMP, BTLSCR_ATTACKER
    Wait 
    WaitButtonABTime 30
    End 
