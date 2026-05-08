#include "macros/btlcmd.inc"

    .data

_000:
    PlayBattleAnimation BTLSCR_MSG_TEMP, BATTLE_ANIMATION_HELD_ITEM
    Wait
    WaitButtonABTime 15
    PrintMessage BattleStrings_Text_PokemonsItemPopped_Ally, TAG_NICKNAME_ITEM, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30
    RemoveItem BTLSCR_MSG_TEMP
    End
