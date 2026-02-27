#include "macros/btlcmd.inc"


_000:
    CheckIgnorableAbility CHECK_HAVE, BTLSCR_DEFENDER, ABILITY_OBLIVIOUS, _048
    UpdateVar OPCODE_SET, BTLVAR_SIDE_EFFECT_FLAGS_DIRECT, MOVE_SIDE_EFFECT_TO_DEFENDER|MOVE_SUBSCRIPT_PTR_SP_ATTACK_DOWN_2_STAGES
    End 

_048:
    PrintAttackMessage 
    Wait 
    WaitButtonABTime 15
    // {0}’s {1} made {2} ineffective!
    PrintMessage BattleStrings_Text_PokemonsAbilityMadeMoveIneffective_Ally, TAG_NICKNAME_ABILITY_MOVE, BTLSCR_DEFENDER, BTLSCR_DEFENDER, BTLSCR_ATTACKER
    Wait 
    WaitButtonABTime 30
    UpdateVar OPCODE_FLAG_ON, BTLVAR_MOVE_STATUS_FLAGS, MOVE_STATUS_NO_MORE_WORK
    End 
