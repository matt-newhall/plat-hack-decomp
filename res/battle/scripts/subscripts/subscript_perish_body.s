#include "macros/btlcmd.inc"

    .data

_000:
    TryPerishBody _002 _001
    // {0}’s {1} was unleashed!
    PrintMessage BattleStrings_Text_PerishBodyUnleashed_Ally, TAG_NICKNAME_ABILITY, BTLSCR_DEFENDER, BTLSCR_DEFENDER
    Wait 
    WaitButtonABTime 30
    // Both Pokémon will faint in three turns!
    PrintMessage BattleStrings_Text_PerishBodyTriggered, TAG_NONE
    Wait 
    WaitButtonABTime 30
    GoTo _002

_001:
    // {0}’s {1} was unleashed!
    PrintMessage BattleStrings_Text_PerishBodyUnleashed_Ally, TAG_NICKNAME_ABILITY, BTLSCR_DEFENDER, BTLSCR_DEFENDER
    Wait 
    WaitButtonABTime 30
    // Both Pokémon will faint in three turns!
    PrintMessage BattleStrings_Text_PerishBodyCountdown_Ally, TAG_NICKNAME, BTLSCR_ATTACKER
    Wait 
    WaitButtonABTime 30

_002:
    End 
