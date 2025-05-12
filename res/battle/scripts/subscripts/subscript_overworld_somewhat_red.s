#include "macros/btlcmd.inc"

    .data

_000:
    UpdateVar OPCODE_SET, BTLVAR_MSG_MOVE_TEMP, MOVE_MAGMA_STORM
    PlayMoveAnimation BTLSCR_MSG_TEMP
    Wait 
    UpdateVar OPCODE_SET, BTLVAR_MOVE_EFFECT_CHANCE, 0
    UpdateVar OPCODE_FLAG_OFF, BTLVAR_BATTLE_CTX_STATUS, SYSCTL_PLAYED_MOVE_ANIMATION
    // {0} became trapped by swirling magma!
    PrintMessage pl_msg_00000368_01247, TAG_NICKNAME, BTLSCR_DEFENDER
    Wait 
    WaitButtonABTime 30
    UpdateVar OPCODE_FLAG_ON, BTLVAR_FIELD_CONDITIONS, FIELD_CONDITION_MAGMA_STORM_PERM
    End 
