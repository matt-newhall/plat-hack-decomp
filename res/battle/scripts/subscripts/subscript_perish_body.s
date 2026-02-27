#include "macros/btlcmd.inc"

    .data

_000:
    TryPerishBody _002 _001
    // {0}’s {1} was unleashed!
    PrintMessage pl_msg_00000368_01298, TAG_NICKNAME_ABILITY, BTLSCR_DEFENDER, BTLSCR_DEFENDER
    Wait 
    WaitButtonABTime 30
    // Both Pokémon will faint in three turns!
    PrintMessage pl_msg_00000368_01294, TAG_NONE
    Wait 
    WaitButtonABTime 30
    GoTo _002

_001:
    // {0}’s {1} was unleashed!
    PrintMessage pl_msg_00000368_01298, TAG_NICKNAME_ABILITY, BTLSCR_DEFENDER, BTLSCR_DEFENDER
    Wait 
    WaitButtonABTime 30
    // Both Pokémon will faint in three turns!
    PrintMessage pl_msg_00000368_01295, TAG_NICKNAME, BTLSCR_ATTACKER
    Wait 
    WaitButtonABTime 30

_002:
    End 
