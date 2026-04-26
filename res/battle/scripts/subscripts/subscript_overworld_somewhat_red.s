#include "macros/btlcmd.inc"

    .data

_000:
    UpdateVar OPCODE_SET, BTLVAR_MSG_MOVE_TEMP, MOVE_MAGMA_STORM
    PlayMoveAnimation BTLSCR_MSG_TEMP
    Wait 
    UpdateVar OPCODE_SET, BTLVAR_MOVE_EFFECT_CHANCE, 0
    UpdateVar OPCODE_FLAG_OFF, BTLVAR_BATTLE_CTX_STATUS, SYSCTL_PLAYED_MOVE_ANIMATION
    // A vortex of swirling magma prevents retreat!
    PrintMessage BattleStrings_Text_MagmaStormWeatherAnnounced, TAG_NONE
    Wait 
    WaitButtonABTime 30
    UpdateVar OPCODE_FLAG_ON, BTLVAR_FIELD_CONDITIONS, FIELD_CONDITION_MAGMA_STORM_PERM
    End 
