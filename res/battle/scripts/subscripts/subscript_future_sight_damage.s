#include "macros/btlcmd.inc"


_000:
    PrintBufferedMessage
    Wait
    WaitButtonABTime 30
    PrepareFutureSight
    CheckMoveHit BTLSCR_MSG_ATTACKER, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP, _missed
    CalcCrit
    CalcDamage
    ApplyTypeEffectiveness
    FinishFutureSight
    CompareVarToValue OPCODE_FLAG_SET, BTLVAR_MOVE_STATUS_FLAGS, MOVE_STATUS_INEFFECTIVE|MOVE_STATUS_WONDER_GUARD, _no_effect
    UpdateVar OPCODE_SET, BTLVAR_MOVE_EFFECT_CHANCE, 1
    PlayMoveAnimationOnMons BTLSCR_MSG_TEMP, BTLSCR_MSG_ATTACKER, BTLSCR_MSG_TEMP
    Wait
    UpdateVar OPCODE_FLAG_OFF, BTLVAR_BATTLE_CTX_STATUS, SYSCTL_PLAYED_MOVE_ANIMATION
    CompareMonDataToValue OPCODE_FLAG_NOT, BTLSCR_MSG_TEMP, BATTLEMON_VOLATILE_STATUS, VOLATILE_CONDITION_SUBSTITUTE, _hit
    UpdateVar OPCODE_MUL, BTLVAR_HP_CALC_TEMP, -1
    CompareMonDataToVar OPCODE_LTE, BTLSCR_MSG_TEMP, BATTLEMON_SUBSTITUTE_HP, BTLVAR_HP_CALC_TEMP, _substitute_broken
    UpdateMonDataFromVar OPCODE_SUB, BTLSCR_MSG_TEMP, BATTLEMON_SUBSTITUTE_HP, BTLVAR_HP_CALC_TEMP
    GoTo _substitute_hit

_substitute_broken:
    UpdateMonData OPCODE_SET, BTLSCR_MSG_TEMP, BATTLEMON_SUBSTITUTE_HP, 0
    UpdateMonData OPCODE_FLAG_OFF, BTLSCR_MSG_TEMP, BATTLEMON_VOLATILE_STATUS, VOLATILE_CONDITION_SUBSTITUTE

_substitute_hit:
    Call BATTLE_SUBSCRIPT_HIT_SUBSTITUTE
    GoTo _messages

_hit:
    CheckHoldOnWith1HP BTLSCR_MSG_TEMP
    Call BATTLE_SUBSCRIPT_UPDATE_HP
    CompareMonDataToValue OPCODE_FLAG_NOT, BTLSCR_MSG_TEMP, BATTLEMON_VOLATILE_STATUS, VOLATILE_CONDITION_RAGE, _messages
    CompareMonDataToValue OPCODE_EQU, BTLSCR_MSG_TEMP, BATTLEMON_CUR_HP, 0, _messages
    CompareMonDataToValue OPCODE_EQU, BTLSCR_MSG_TEMP, BATTLEMON_ATTACK_STAGE, 12, _messages
    UpdateMonData OPCODE_ADD, BTLSCR_MSG_TEMP, BATTLEMON_ATTACK_STAGE, 1
    // {0}’s rage is building!
    PrintMessage BattleStrings_Text_PokemonsRageIsBuilding_Ally, TAG_NICKNAME, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30

_messages:
    Call BATTLE_SUBSCRIPT_CRITICAL_HIT
    Call BATTLE_SUBSCRIPT_MOVE_FOLLOWUP_MESSAGE
    End

_no_effect:
    CompareVarToValue OPCODE_FLAG_NOT, BTLVAR_MOVE_STATUS_FLAGS, MOVE_STATUS_WONDER_GUARD, _doesnt_affect
    ShowAbilityPopupAuto BTLSCR_MSG_TEMP

_doesnt_affect:
    // It doesn’t affect {0}…
    PrintMessage BattleStrings_Text_ItDoesntAffectPokemon_Ally, TAG_NICKNAME, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30
    End

_missed:
    FinishFutureSight
    WaitButtonABTime 30
    // But it failed!
    PrintMessage BattleStrings_Text_ButItFailed, TAG_NONE
    Wait
    WaitButtonABTime 30
    End
