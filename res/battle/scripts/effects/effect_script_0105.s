#include "macros/btlcmd.inc"


_000:
    CompareMonDataToValue OPCODE_FLAG_NOT, BTLSCR_DEFENDER, BATTLEMON_STATUS, MON_CONDITION_ANY, _009
    UpdateVar OPCODE_SET, BTLVAR_POWER_MULTI, 20

_009:
    CalcCrit
    CalcDamage
    End
