#include "macros/btlcmd.inc"


_000:
    CompareMonDataToValue OPCODE_EQU, BTLSCR_ATTACKER, BATTLEMON_STOCKPILE_COUNT, 0, _064
    UpdateMonDataFromVar OPCODE_GET, BTLSCR_ATTACKER, BATTLEMON_STOCKPILE_COUNT, BTLVAR_MOVE_POWER
    UpdateVar OPCODE_MUL, BTLVAR_MOVE_POWER, 100
    UpdateMonData OPCODE_SET, BTLSCR_ATTACKER, BATTLEMON_STOCKPILE_COUNT, 0
    UpdateVar OPCODE_SET, BTLVAR_SIDE_EFFECT_FLAGS_INDIRECT, MOVE_SIDE_EFFECT_ON_HIT|MOVE_SUBSCRIPT_PTR_STOCKPILE_RELEASE
    CalcCrit 
    CalcDamage 
    End 

_064:
    PrintAttackMessage 
    Wait 
    WaitButtonABTime 30
    // But it failed to spit up a thing!
    PrintMessage BattleStrings_Text_ButItFailedToSpitUpAThing, TAG_NONE
    Wait 
    WaitButtonABTime 30
    UpdateVar OPCODE_FLAG_ON, BTLVAR_MOVE_STATUS_FLAGS, MOVE_STATUS_NO_MORE_WORK
    End 
