#include "macros/btlcmd.inc"


_000:
    CheckIgnorableAbility CHECK_HAVE, BTLSCR_DEFENDER, ABILITY_OBLIVIOUS, _048
    UpdateVar OPCODE_SET, BTLVAR_SIDE_EFFECT_FLAGS_DIRECT, MOVE_SIDE_EFFECT_TO_DEFENDER|MOVE_SUBSCRIPT_PTR_SP_ATTACK_DOWN_2_STAGES
    End 

_048:
    PrintAttackMessage 
    Wait 
    WaitButtonABTime 15
    ShowAbilityPopupAuto BTLSCR_DEFENDER
    // It doesn’t affect {0}...
    PrintMessage BattleStrings_Text_ItDoesntAffectPokemon_Ally, TAG_NICKNAME, BTLSCR_DEFENDER
    Wait 
    WaitButtonABTime 30
    UpdateVar OPCODE_FLAG_ON, BTLVAR_MOVE_STATUS_FLAGS, MOVE_STATUS_NO_MORE_WORK
    End 
