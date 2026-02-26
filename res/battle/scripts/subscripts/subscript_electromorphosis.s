#include "macros/btlcmd.inc"

    .data

_000:
    UpdateMonData OPCODE_FLAG_ON, BTLSCR_DEFENDER, BATTLEMON_MOVE_EFFECTS_MASK, MOVE_EFFECT_CHARGE
    // {0} was charged with power!
    PrintMessage BattleStrings_Text_ElectromorphosisCharged_Ally, TAG_NICKNAME, BTLSCR_DEFENDER
    Wait 
    WaitButtonABTime 30
    End 
