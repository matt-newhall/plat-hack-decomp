#include "macros/btlcmd.inc"

    .data

_000:
    PrintAttackMessage 
    Wait 
    UpdateMonDataFromVar OPCODE_GET, BTLSCR_ATTACKER, BATTLEMON_MAX_HP, BTLVAR_HP_CALC_TEMP
    UpdateVar OPCODE_ADD, BTLVAR_HP_CALC_TEMP, 1
    DivideVarByValue BTLVAR_HP_CALC_TEMP, 2
    UpdateVarFromVar OPCODE_SET, BTLVAR_MSG_BATTLER_TEMP, BTLVAR_ATTACKER
    Call BATTLE_SUBSCRIPT_RECOVER_HP
    End 
