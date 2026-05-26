#include "macros/btlcmd.inc"


_000:
    ShowAbilityPopupAuto BTLSCR_ATTACKER
    // {0} is loafing around!
    PrintMessage BattleStrings_Text_PokemonIsLoafingAround_Ally, TAG_NICKNAME, BTLSCR_ATTACKER
    Wait 
    WaitButtonABTime 30
    UnlockMoveChoice BTLSCR_ATTACKER
    End 
