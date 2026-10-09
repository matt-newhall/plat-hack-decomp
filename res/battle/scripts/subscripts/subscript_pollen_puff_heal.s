#include "macros/btlcmd.inc"


_000:
    CompareVarToValue OPCODE_FLAG_SET, BTLVAR_MOVE_STATUS_FLAGS, MOVE_STATUS_MISSED|MOVE_STATUS_SEMI_INVULNERABLE, _failed
    CompareMonDataToValue OPCODE_NEQ, BTLSCR_ATTACKER, BATTLEMON_HEAL_BLOCK_TURNS, 0, _failed
    PrintAttackMessage
    Wait
    CompareMonDataToValue OPCODE_NEQ, BTLSCR_DEFENDER, BATTLEMON_HEAL_BLOCK_TURNS, 0, _heal_blocked
    UpdateMonDataFromVar OPCODE_GET, BTLSCR_DEFENDER, BATTLEMON_MAX_HP, BTLVAR_HP_CALC_TEMP
    UpdateVar OPCODE_ADD, BTLVAR_HP_CALC_TEMP, 1
    DivideVarByValue BTLVAR_HP_CALC_TEMP, 2
    UpdateVarFromVar OPCODE_SET, BTLVAR_MSG_BATTLER_TEMP, BTLVAR_DEFENDER
    Call BATTLE_SUBSCRIPT_RECOVER_HP
    End

_heal_blocked:
    WaitButtonABTime 30
    UpdateVar OPCODE_SET, BTLVAR_MSG_MOVE_TEMP, MOVE_HEAL_BLOCK
    // {0} was prevented from healing due to {1}!
    PrintMessage BattleStrings_Text_PokemonWasPreventedFromHealingDueToMove_Ally, TAG_NICKNAME_MOVE, BTLSCR_DEFENDER, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30
    UpdateVar OPCODE_FLAG_ON, BTLVAR_MOVE_STATUS_FLAGS, MOVE_STATUS_NO_MORE_WORK
    End

_failed:
    UpdateVar OPCODE_FLAG_ON, BTLVAR_MOVE_STATUS_FLAGS, MOVE_STATUS_FAILED
    End
