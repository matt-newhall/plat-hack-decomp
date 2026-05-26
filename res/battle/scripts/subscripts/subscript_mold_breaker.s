#include "macros/btlcmd.inc"


_000:
    ShowAbilityPopupAuto BTLSCR_MSG_BATTLER_TEMP
    // {0} has {1}!
    PrintMessage BattleStrings_Text_PokemonWasAbility_Ally, TAG_NICKNAME, BTLSCR_MSG_BATTLER_TEMP
    Wait 
    WaitButtonABTime 30
    End 
