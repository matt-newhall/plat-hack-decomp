#include "macros/btlcmd.inc"


_000:
    PrintAttackMessage
    Wait
    WaitButtonABTime 30
    // {0} is about to be attacked by its {1}!
    PrintMessage BattleStrings_Text_PokemonIsAboutToBeAttackedByItsItem_Ally, TAG_NICKNAME_ITEM, BTLSCR_DEFENDER, BTLSCR_DEFENDER
    Wait
    WaitButtonABTime 30
    PlayMoveAnimation BTLSCR_ATTACKER
    Wait
    End
