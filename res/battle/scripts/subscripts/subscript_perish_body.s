#include "macros/btlcmd.inc"

    .data

_000:
    TryPerishBody _002 _001
    ShowAbilityPopupAuto BTLSCR_DEFENDER
    // Both Pokémon will faint in three turns!
    PrintMessage BattleStrings_Text_PerishBodyTriggered, TAG_NONE
    Wait
    WaitButtonABTime 30
    GoTo _002

_001:
    ShowAbilityPopupAuto BTLSCR_DEFENDER
    // Both Pokémon will faint in three turns!
    PrintMessage BattleStrings_Text_PerishBodyCountdown_Ally, TAG_NICKNAME, BTLSCR_ATTACKER
    Wait
    WaitButtonABTime 30

_002:
    End
