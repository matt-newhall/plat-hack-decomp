#include "macros/btlcmd.inc"

    .data

_000:
    PrintMessage BattleStrings_Text_PokemonFloatedOnAirBalloon_Ally, TAG_NICKNAME_ITEM, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30
    End
