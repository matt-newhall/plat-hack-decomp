#include "macros/btlcmd.inc"


_000:
    PlayBattleAnimation BTLSCR_DEFENDER, BATTLE_ANIMATION_HELD_ITEM
    Wait
    WaitButtonABTime 15
    CheckIgnorableAbility CHECK_HAVE, BTLSCR_ATTACKER, ABILITY_SUCTION_CUPS, _suction_cups
    CompareMonDataToValue OPCODE_EQU, BTLSCR_ATTACKER, BATTLEMON_MOVE_EFFECTS_MASK, MOVE_EFFECT_INGRAIN, _ingrain

_normal_switch:
    // {0}'s {1} was held up!
    PrintMessage BattleStrings_Text_PokemonsRedCardWasHeldUp_Ally, TAG_NICKNAME_ITEM, BTLSCR_DEFENDER, BTLSCR_DEFENDER
    Wait
    WaitButtonABTime 30
    RemoveItem BTLSCR_DEFENDER
    CompareVarToValue OPCODE_FLAG_NOT, BTLVAR_BATTLE_TYPE, BATTLE_TYPE_TRAINER, _check_wild_flee
    GoTo _neutralizing_gas_check

_check_wild_flee:
    CompareVarToValue OPCODE_FLAG_NOT, BTLVAR_BATTLE_TYPE, BATTLE_TYPE_DOUBLES, _flee

_neutralizing_gas_check:
    CompareVarToValue OPCODE_FLAG_NOT, BTLVAR_BATTLE_CTX_STATUS_2, SYSCTL_NEUTRALIZING_GAS_ACTIVE, _do_switch
    CompareMonDataToValue OPCODE_NEQ, BTLSCR_ATTACKER, BATTLEMON_ABILITY, ABILITY_NEUTRALIZING_GAS, _do_switch
    UpdateVar OPCODE_FLAG_OFF, BTLVAR_BATTLE_CTX_STATUS_2, SYSCTL_NEUTRALIZING_GAS_ACTIVE
    // Neutralizing Gas wore off!
    PrintMessage BattleStrings_Text_AnnounceNeutralizingGasDisabled, TAG_NONE
    Wait
    WaitButtonABTime 30

_neutralizing_gas_wearoff_loop:
    TriggerNeutralizingGasWearOffStep _do_switch
    CallFromVar BTLVAR_SCRIPT_TEMP
    GoTo _neutralizing_gas_wearoff_loop

_do_switch:
    DeletePokemon BTLSCR_ATTACKER
    Wait
    HealthbarSlideOut BTLSCR_ATTACKER
    Wait
    UpdateVar OPCODE_FLAG_ON, BTLVAR_BATTLE_CTX_STATUS_2, SYSCTL_UTURN_ACTIVE
    SwitchAndUpdateMon BTLSCR_ATTACKER
    Wait
    PokemonSendOut BTLSCR_ATTACKER
    WaitTime 72
    HealthbarSlideIn BTLSCR_ATTACKER
    Wait
    // {0} was dragged out!
    PrintMessage BattleStrings_Text_PokemonWasDraggedOut_Ally, TAG_NICKNAME, BTLSCR_ATTACKER
    Wait
    WaitButtonABTime 30
    UpdateVarFromVar OPCODE_SET, BTLVAR_SWITCHED_MON, BTLVAR_ATTACKER
    UpdateVar OPCODE_SET, BTLVAR_MSG_TEMP, MOVE_ROAR
    Call BATTLE_SUBSCRIPT_HAZARDS_CHECK
    End

_flee:
    FadeOutBattle
    SwitchToxic
    ResetSleepTurns
    Wait
    UpdateVar OPCODE_FLAG_ON, BTLVAR_RESULT_MASK, BATTLE_RESULT_PLAYER_FLED
    End

_suction_cups:
    // {0}'s {1} was held up!
    PrintMessage BattleStrings_Text_PokemonsRedCardWasHeldUp_Ally, TAG_NICKNAME_ITEM, BTLSCR_DEFENDER, BTLSCR_DEFENDER
    Wait
    WaitButtonABTime 30
    RemoveItem BTLSCR_DEFENDER
    ShowAbilityPopupAuto BTLSCR_ATTACKER
    // {0} is anchored in place with its suction cups!
    PrintMessage BattleStrings_Text_PokemonAnchorsItselfWithAbility_Ally, TAG_NICKNAME, BTLSCR_ATTACKER
    Wait
    WaitButtonABTime 30
    End

_ingrain:
    // {0}'s {1} was held up!
    PrintMessage BattleStrings_Text_PokemonsRedCardWasHeldUp_Ally, TAG_NICKNAME_ITEM, BTLSCR_DEFENDER, BTLSCR_DEFENDER
    Wait
    WaitButtonABTime 30
    RemoveItem BTLSCR_DEFENDER
    // {0} anchored itself with its roots!
    PrintMessage BattleStrings_Text_PokemonAnchoredItselfWithItsRoots_Ally, TAG_NICKNAME, BTLSCR_ATTACKER
    Wait
    WaitButtonABTime 30
    End
