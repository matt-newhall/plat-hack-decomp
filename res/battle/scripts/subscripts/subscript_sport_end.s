#include "macros/btlcmd.inc"


_000:
    CompareVarToValue OPCODE_EQU, BTLVAR_SCRIPT_TEMP, TYPE_FIRE, _water
    // The effects of Mud Sport have faded.
    PrintMessage BattleStrings_Text_MudSportEnded, TAG_NONE
    GoTo _end

_water:
    // The effects of Water Sport have faded.
    PrintMessage BattleStrings_Text_WaterSportEnded, TAG_NONE

_end:
    Wait 
    WaitButtonABTime 30
    End 
