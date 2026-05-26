#include "macros/btlcmd.inc"


_000:
    ChangeStatStage _041, _059, _060
    CompareVarToValue OPCODE_NEQ, BTLVAR_SIDE_EFFECT_TYPE, SIDE_EFFECT_TYPE_DIRECT, _010
    PrintAttackMessage
    Wait

_010:
    CompareVarToValue OPCODE_NEQ, BTLVAR_SIDE_EFFECT_TYPE, SIDE_EFFECT_TYPE_DIRECT, _018
    CheckPowderImmunity BTLSCR_DEFENDER, _061, _overcoat_popup

_016:
    PlayMoveAnimation BTLSCR_ATTACKER
    Wait

_018:
    CompareVarToValue OPCODE_FLAG_SET, BTLVAR_BATTLE_CTX_STATUS_2, SYSCTL_UPDATE_STAT_STAGES, _036
    PlayBattleAnimationFromVar BTLSCR_SIDE_EFFECT_MON, BTLVAR_SCRIPT_TEMP
    Wait
    CompareVarToValue OPCODE_FLAG_NOT, BTLVAR_BATTLE_CTX_STATUS_2, SYSCTL_STAT_STAGE_CHANGE_SHOWN, _036
    UpdateVar OPCODE_FLAG_ON, BTLVAR_BATTLE_CTX_STATUS_2, SYSCTL_UPDATE_STAT_STAGES

_036:
    PrintBufferedMessage
    Wait
    WaitButtonABTime 30
    Call BATTLE_SUBSCRIPT_DEFIANT_CHECK
    Call BATTLE_SUBSCRIPT_COMPETITIVE_CHECK
    End

_041:
    CompareVarToValue OPCODE_NEQ, BTLVAR_SIDE_EFFECT_TYPE, SIDE_EFFECT_TYPE_DIRECT, _blocking_popup_check
    PrintAttackMessage
    Wait
    WaitButtonABTime 30

_blocking_popup_check:
    CompareVarToValue OPCODE_FLAG_SET, BTLVAR_BATTLE_CTX_STATUS, SYSCTL_FAIL_STAT_STAGE_CHANGE, _048
    ShowAbilityPopupAuto BTLSCR_SIDE_EFFECT_MON

_048:
    CompareVarToValue OPCODE_FLAG_SET, BTLVAR_BATTLE_CTX_STATUS, SYSCTL_TURN_OFF_MESSAGES, _059
    WaitButtonABTime 30
    PrintBufferedMessage
    Wait
    WaitButtonABTime 30

_059:
    End

_060:
    UpdateVar OPCODE_FLAG_ON, BTLVAR_MOVE_STATUS_FLAGS, MOVE_STATUS_FAILED
    End

_overcoat_popup:
    ShowAbilityPopupAuto BTLSCR_DEFENDER
    GoTo _061

_061:
    WaitButtonABTime 30
    PrintMessage BattleStrings_Text_ItDoesntAffectPokemon_Ally, TAG_NICKNAME, BTLSCR_SIDE_EFFECT_MON
    Wait
    WaitButtonABTime 30
    UpdateVar OPCODE_FLAG_ON, BTLVAR_MOVE_STATUS_FLAGS, MOVE_STATUS_NO_MORE_WORK
    End
