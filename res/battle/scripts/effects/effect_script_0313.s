#include "macros/btlcmd.inc"


_000:
    CompareMonDataToValue OPCODE_EQU, BTLSCR_DEFENDER, BATTLEMON_HELD_ITEM, ITEM_NONE, _failed
    CalcCrit 
    CalcDamage 
    End 

_failed:
    UpdateVar OPCODE_FLAG_ON, BTLVAR_MOVE_STATUS_FLAGS, MOVE_STATUS_FAILED
    End 
