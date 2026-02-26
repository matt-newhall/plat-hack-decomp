#include "macros/btlcmd.inc"

    .data

_000:
    TryToxicDebris _010
    UpdateVar OPCODE_FLAG_OFF, BTLVAR_BATTLE_CTX_STATUS, SYSCTL_PLAYED_MOVE_ANIMATION
    UpdateVar OPCODE_SET, BTLVAR_MSG_MOVE_TEMP, MOVE_TOXIC_SPIKES
    PlayMoveAnimationOnMons BTLSCR_MSG_TEMP, BTLSCR_DEFENDER, BTLSCR_ATTACKER
    UpdateVar OPCODE_FLAG_ON, BTLVAR_BATTLE_CTX_STATUS, SYSCTL_PLAYED_MOVE_ANIMATION
    // Poison spikes were scattered all around your team’s feet!
    PrintMessage pl_msg_00000368_01288, TAG_NICKNAME_ABILITY, BTLSCR_DEFENDER, BTLSCR_DEFENDER
    Wait 
    WaitButtonABTime 30
    End 

_010:
    End 
