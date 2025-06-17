#include "macros/btlcmd.inc"


_000:
    UpdateVar OPCODE_FLAG_ON, BTLVAR_SIDE_CONDITIONS_ATTACKER, SIDE_CONDITION_FLEE_FAILED
    // Can’t escape!
    PrintMessage BattleStrings_Text_CantEscape, TAG_NONE
    Wait 
    WaitButtonABTime 30
    End 
