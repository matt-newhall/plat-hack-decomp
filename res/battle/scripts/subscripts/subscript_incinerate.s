#include "macros/btlcmd.inc"


_000:
    TryIncinerate _sticky_hold, _end
    // {0}’s {1} was burnt up!
    PrintMessage BattleStrings_Text_PokemonsItemWasBurntUp_Ally, TAG_NICKNAME_ITEM, BTLSCR_DEFENDER, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30

_end:
    End

_sticky_hold:
    ShowAbilityPopupAuto BTLSCR_DEFENDER
    // {0}’s item cannot be removed!
    PrintMessage BattleStrings_Text_PokemonsItemCannotBeRemoved_Ally, TAG_NICKNAME, BTLSCR_DEFENDER
    Wait
    WaitButtonABTime 30
    End
