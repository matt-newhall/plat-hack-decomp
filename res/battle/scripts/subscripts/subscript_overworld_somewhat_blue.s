#include "macros/btlcmd.inc"

    .data

_000:
    UpdateVar OPCODE_SET, BTLVAR_MSG_MOVE_TEMP, MOVE_AURORA_VEIL
    PlayMoveAnimation BTLSCR_MSG_TEMP
    Wait 
    UpdateVar OPCODE_SET, BTLVAR_MOVE_EFFECT_CHANCE, 0
    UpdateVar OPCODE_FLAG_OFF, BTLVAR_BATTLE_CTX_STATUS, SYSCTL_PLAYED_MOVE_ANIMATION
    // The opposing side is covered by a protective veil!
    PrintMessage BattleStrings_Text_AuroraVeilWeatherAnnounced, TAG_NONE
    Wait 
    WaitButtonABTime 30
    UpdateVar OPCODE_FLAG_ON, BTLVAR_FIELD_CONDITIONS, FIELD_CONDITION_AURORA_VEIL_PERM
    End 
