#include "macros/btlcmd.inc"


_000:
    TrySetSport _018
    // Electricity’s power was weakened!
    BufferMessage BattleStrings_Text_ElectricitysPowerWasWeakened, TAG_NONE
    UpdateVar OPCODE_SET, BTLVAR_SIDE_EFFECT_FLAGS_INDIRECT, MOVE_SIDE_EFFECT_ON_HIT|MOVE_SUBSCRIPT_PTR_PRINT_MESSAGE_AND_PLAY_ANIMATION
    End 

_018:
    UpdateVar OPCODE_FLAG_ON, BTLVAR_MOVE_STATUS_FLAGS, MOVE_STATUS_FAILED
    End 
