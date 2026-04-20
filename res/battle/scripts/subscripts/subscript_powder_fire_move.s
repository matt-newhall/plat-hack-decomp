#include "macros/btlcmd.inc"

    .data

_000:
    PrintAttackMessage
    Wait
    WaitButtonABTime 30
    CheckIgnoreWeather _005
    CompareVarToValue OPCODE_FLAG_NOT, BTLVAR_FIELD_CONDITIONS, FIELD_CONDITION_RAINING, _005
    // The rain quenched the powder!
    PrintMessage pl_msg_00000368_01346, TAG_NONE
    Wait
    WaitButtonABTime 30
    GoTo _015

_005:
    CheckAbility CHECK_HAVE, BTLSCR_ATTACKER, ABILITY_MAGIC_GUARD, _010
    UpdateVarFromVar OPCODE_SET, BTLVAR_MSG_BATTLER_TEMP, BTLVAR_ATTACKER
    UpdateMonDataFromVar OPCODE_GET, BTLSCR_MSG_TEMP, BATTLEMON_MAX_HP, BTLVAR_HP_CALC_TEMP
    DivideVarByValue BTLVAR_HP_CALC_TEMP, 4
    UpdateVar OPCODE_MUL, BTLVAR_HP_CALC_TEMP, -1

_010:
    // When the flame touched the powder on the Pokémon, it exploded!
    PrintMessage pl_msg_00000368_01345, TAG_NONE
    Wait
    WaitButtonABTime 30
    CheckAbility CHECK_HAVE, BTLSCR_ATTACKER, ABILITY_MAGIC_GUARD, _015
    Call BATTLE_SUBSCRIPT_UPDATE_HP

_015:
    UnlockMoveChoice BTLSCR_ATTACKER
    End
