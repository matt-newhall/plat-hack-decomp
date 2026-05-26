#include "macros/btlcmd.inc"


_000:
    ShowAbilityPopupAuto BTLSCR_MSG_BATTLER_TEMP
    // {0} is slow to get going!
    PrintMessage BattleStrings_Text_PokemonCantGetItGoingBecauseOfItsAbility_Ally, TAG_NICKNAME, BTLSCR_MSG_BATTLER_TEMP
    Wait 
    WaitButtonABTime 30
    End 
