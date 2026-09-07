#include "macros/btlcmd.inc"

    .data

_000:
    CompareVarToValue OPCODE_NEQ, BTLVAR_SIDE_EFFECT_TYPE, SIDE_EFFECT_TYPE_DIRECT, _wore_off
    PrintAttackMessage 
    Wait 
    Call BATTLE_SUBSCRIPT_RECOVER_HP

_wore_off:
    // {0}’s stockpiled effect wore off!
    PrintMessage BattleStrings_Text_PokemonsStockpiledEffectWoreOff_Ally, TAG_NICKNAME, BTLSCR_ATTACKER
    Wait 
    WaitButtonABTime 30
    UpdateMonDataFromVar OPCODE_GET, BTLSCR_ATTACKER, BATTLEMON_STOCKPILE_DEF_BOOSTS, BTLVAR_CALC_TEMP
    UpdateMonData OPCODE_SET, BTLSCR_ATTACKER, BATTLEMON_STOCKPILE_DEF_BOOSTS, 0
    CompareVarToValue OPCODE_EQU, BTLVAR_CALC_TEMP, 0, _sp_defense
    CheckSimple BTLSCR_ATTACKER, _defense_simple
    GoTo _defense_drop

_defense_simple:
    UpdateVar OPCODE_MUL, BTLVAR_CALC_TEMP, 2

_defense_drop:
    UpdateMonDataFromVar OPCODE_SUB_TO_ZERO, BTLSCR_ATTACKER, BATTLEMON_DEFENSE_STAGE, BTLVAR_CALC_TEMP
    UpdateVar OPCODE_SET, BTLVAR_MSG_TEMP, BATTLE_STAT_DEFENSE
    PlayBattleAnimation BTLSCR_ATTACKER, BATTLE_ANIMATION_STAT_DROP
    Wait 
    CompareVarToValue OPCODE_EQU, BTLVAR_CALC_TEMP, 1, _defense_fell
    CompareVarToValue OPCODE_EQU, BTLVAR_CALC_TEMP, 2, _defense_harshly_fell
    // {0}’s {1} severely fell!
    PrintMessage BattleStrings_Text_PokemonsStatSeverelyFell_Ally, TAG_NICKNAME_STAT, BTLSCR_ATTACKER, BTLSCR_MSG_TEMP
    GoTo _defense_shown

_defense_fell:
    // {0}’s {1} fell!
    PrintMessage BattleStrings_Text_PokemonsStatFell_Ally, TAG_NICKNAME_STAT, BTLSCR_ATTACKER, BTLSCR_MSG_TEMP
    GoTo _defense_shown

_defense_harshly_fell:
    // {0}’s {1} harshly fell!
    PrintMessage BattleStrings_Text_PokemonsStatHarshlyFell_Ally, TAG_NICKNAME_STAT, BTLSCR_ATTACKER, BTLSCR_MSG_TEMP

_defense_shown:
    Wait 
    WaitButtonABTime 30

_sp_defense:
    UpdateMonDataFromVar OPCODE_GET, BTLSCR_ATTACKER, BATTLEMON_STOCKPILE_SPDEF_BOOSTS, BTLVAR_CALC_TEMP
    UpdateMonData OPCODE_SET, BTLSCR_ATTACKER, BATTLEMON_STOCKPILE_SPDEF_BOOSTS, 0
    CompareVarToValue OPCODE_EQU, BTLVAR_CALC_TEMP, 0, _end
    CheckSimple BTLSCR_ATTACKER, _sp_defense_simple
    GoTo _sp_defense_drop

_sp_defense_simple:
    UpdateVar OPCODE_MUL, BTLVAR_CALC_TEMP, 2

_sp_defense_drop:
    UpdateMonDataFromVar OPCODE_SUB_TO_ZERO, BTLSCR_ATTACKER, BATTLEMON_SP_DEFENSE_STAGE, BTLVAR_CALC_TEMP
    UpdateVar OPCODE_SET, BTLVAR_MSG_TEMP, BATTLE_STAT_SP_DEFENSE
    PlayBattleAnimation BTLSCR_ATTACKER, BATTLE_ANIMATION_STAT_DROP
    Wait 
    CompareVarToValue OPCODE_EQU, BTLVAR_CALC_TEMP, 1, _sp_defense_fell
    CompareVarToValue OPCODE_EQU, BTLVAR_CALC_TEMP, 2, _sp_defense_harshly_fell
    // {0}’s {1} severely fell!
    PrintMessage BattleStrings_Text_PokemonsStatSeverelyFell_Ally, TAG_NICKNAME_STAT, BTLSCR_ATTACKER, BTLSCR_MSG_TEMP
    GoTo _sp_defense_shown

_sp_defense_fell:
    // {0}’s {1} fell!
    PrintMessage BattleStrings_Text_PokemonsStatFell_Ally, TAG_NICKNAME_STAT, BTLSCR_ATTACKER, BTLSCR_MSG_TEMP
    GoTo _sp_defense_shown

_sp_defense_harshly_fell:
    // {0}’s {1} harshly fell!
    PrintMessage BattleStrings_Text_PokemonsStatHarshlyFell_Ally, TAG_NICKNAME_STAT, BTLSCR_ATTACKER, BTLSCR_MSG_TEMP

_sp_defense_shown:
    Wait 
    WaitButtonABTime 30

_end:
    End 
