#include "macros/btlcmd.inc"


_000:
    ShowAbilityPopupAuto BTLSCR_MSG_TEMP
    WaitButtonABTime 15
    // {0} frisked its foe and found one {1}!
    PrintMessage BattleStrings_Text_PokemonFriskedItsFoeAndFoundOneItem_Ally, TAG_NICKNAME_ITEM, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait 
    WaitButtonABTime 30
    End 
