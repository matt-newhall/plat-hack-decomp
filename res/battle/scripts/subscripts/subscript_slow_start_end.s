#include "macros/btlcmd.inc"


_000:
    ShowAbilityPopupAuto BTLSCR_MSG_BATTLER_TEMP
    // {0} finally got its act together!
    PrintMessage BattleStrings_Text_PokemonFinallyGotItsActTogether_Ally, TAG_NICKNAME_ABILITY, BTLSCR_MSG_TEMP, BTLSCR_MSG_BATTLER_TEMP
    Wait 
    WaitButtonABTime 30
    End 
