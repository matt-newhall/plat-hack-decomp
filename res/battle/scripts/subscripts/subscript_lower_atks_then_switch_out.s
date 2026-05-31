#include "macros/btlcmd.inc"

    .data

_000:
    // If both Attack and Sp.Atk are already at -6, the move fails entirely — no stat drops, no switch.
    CompareMonDataToValue OPCODE_NEQ, BTLSCR_DEFENDER, BATTLEMON_ATTACK_STAGE, 0, _do_stat_drops
    CompareMonDataToValue OPCODE_EQU, BTLSCR_DEFENDER, BATTLEMON_SP_ATTACK_STAGE, 0, _fail_both_at_min

_do_stat_drops:
    // Stat drops always happen regardless of whether the user can switch out.
    // subscript_use_move skips the animation for DIRECT effects, expecting this subscript to
    // handle it — the animation is triggered inside BATTLE_SUBSCRIPT_UPDATE_STAT_STAGE (_016).
    UpdateVarFromVar OPCODE_SET, BTLVAR_SIDE_EFFECT_MON, BTLVAR_DEFENDER
    UpdateVar OPCODE_FLAG_ON, BTLVAR_BATTLE_CTX_STATUS_2, SYSCTL_STAT_STAGE_CHANGE_SHOWN
    UpdateVar OPCODE_SET, BTLVAR_SIDE_EFFECT_PARAM, MOVE_SUBSCRIPT_PTR_ATTACK_DOWN_1_STAGE
    Call BATTLE_SUBSCRIPT_UPDATE_STAT_STAGE
    UpdateVar OPCODE_FLAG_ON, BTLVAR_BATTLE_CTX_STATUS, SYSCTL_TURN_OFF_MESSAGES
    UpdateVar OPCODE_SET, BTLVAR_SIDE_EFFECT_PARAM, MOVE_SUBSCRIPT_PTR_SP_ATTACK_DOWN_1_STAGE
    Call BATTLE_SUBSCRIPT_UPDATE_STAT_STAGE
    // SYSCTL_UPDATE_STAT_STAGES is set by subscript_update_stat_stage only when a stat actually
    // changed. If neither drop landed (Mist, Clear Body, or both stats at -6), skip the switch.
    CompareVarToValue OPCODE_FLAG_NOT, BTLVAR_BATTLE_CTX_STATUS_2, SYSCTL_UPDATE_STAT_STAGES, _no_effect
    UpdateVar OPCODE_FLAG_OFF, BTLVAR_BATTLE_CTX_STATUS_2, SYSCTL_UPDATE_STAT_STAGES
    UpdateVar OPCODE_FLAG_OFF, BTLVAR_BATTLE_CTX_STATUS_2, SYSCTL_STAT_STAGE_CHANGE_SHOWN
    UpdateVar OPCODE_FLAG_OFF, BTLVAR_BATTLE_CTX_STATUS, SYSCTL_TURN_OFF_MESSAGES
    // Wild mons and trainers with no remaining mons skip the switch-out entirely.
    TryReplaceFaintedMon BTLSCR_ATTACKER, TRUE, _172
    UpdateVarFromVar OPCODE_SET, BTLVAR_SWITCHED_MON, BTLVAR_ATTACKER
    // {0} went back to {1}!
    PrintMessage BattleStrings_Text_PokemonWentBackToTrainer_Ally, TAG_NICKNAME_TRNAME, BTLSCR_SWITCHED_MON, BTLSCR_SWITCHED_MON
    Wait
    WaitButtonABTime 30
    Call BATTLE_SUBSCRIPT_PURSUIT
    TryRestoreStatusOnSwitch BTLSCR_ATTACKER, _138
    UpdateMonData OPCODE_SET, BTLSCR_ATTACKER, BATTLEMON_STATUS, MON_CONDITION_NONE
    GoTo _141

_138:
    TryRegeneratorOnSwitch BTLSCR_ATTACKER, _141
    UpdateMonDataFromVar OPCODE_GET, BTLSCR_ATTACKER, BATTLEMON_MAX_HP, BTLVAR_HP_CALC_TEMP
    DivideVarByValue BTLVAR_HP_CALC_TEMP, 3
    UpdateHealthBarValue BTLSCR_ATTACKER

_141:
    UpdateVar OPCODE_FLAG_OFF, BTLVAR_BATTLE_CTX_STATUS, SYSCTL_PLAYED_MOVE_ANIMATION
    UpdateVar OPCODE_SET, BTLVAR_MOVE_EFFECT_CHANCE, 1
    PlayMoveAnimation BTLSCR_ATTACKER
    Wait
    DeletePokemon BTLSCR_ATTACKER
    Wait
    HealthbarSlideOut BTLSCR_ATTACKER
    Wait
    // Parting Shot's own stat drops must not trigger Eject Pack — clear before switching.
    UpdateVar OPCODE_FLAG_OFF, BTLVAR_BATTLE_CTX_STATUS_2, SYSCTL_EJECT_PACK_PENDING_MASK
    UpdateVar OPCODE_FLAG_ON, BTLVAR_BATTLE_CTX_STATUS_2, SYSCTL_UTURN_ACTIVE
    UpdateVar OPCODE_FLAG_OFF, BTLVAR_BATTLE_CTX_STATUS, SYSCTL_TRY_SYNCHRONIZE_STATUS
    UpdateVar OPCODE_SET, BTLVAR_ATTACKER_SELF_TURN_STATUS_FLAGS, SELF_TURN_FLAG_CLEAR
    GoToSubscript BATTLE_SUBSCRIPT_SHOW_PARTY_LIST

_no_effect:
    // Stat drops were blocked (Mist, Clear Body, etc.) — the blocking messages were already shown,
    // so just clean up and end without setting MOVE_STATUS_FAILED or showing "But it failed!".
    UpdateVar OPCODE_FLAG_OFF, BTLVAR_BATTLE_CTX_STATUS_2, SYSCTL_UPDATE_STAT_STAGES
    UpdateVar OPCODE_FLAG_OFF, BTLVAR_BATTLE_CTX_STATUS_2, SYSCTL_STAT_STAGE_CHANGE_SHOWN
    UpdateVar OPCODE_FLAG_OFF, BTLVAR_BATTLE_CTX_STATUS, SYSCTL_TURN_OFF_MESSAGES
    GoTo _172

_fail_both_at_min:
    // Both stats were already at -6 — no messages have been shown yet, so show "But it failed!".
    UpdateVar OPCODE_FLAG_ON, BTLVAR_MOVE_STATUS_FLAGS, MOVE_STATUS_FAILED

_172:
    End
