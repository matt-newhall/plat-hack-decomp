#include "macros/btlcmd.inc"


_000:
    ShowAbilityPopupAuto BTLSCR_MSG_BATTLER_TEMP
    // {1}’s {0} made it shudder!
    PrintMessage BattleStrings_Text_PokemonsAbilityMadeItShudder_Ally, TAG_ABILITY_NICKNAME, BTLSCR_MSG_BATTLER_TEMP, BTLSCR_MSG_TEMP
    Wait 
    WaitButtonABTime 30
    End 
