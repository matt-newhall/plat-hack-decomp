#include "macros/btlanimcmd.inc"

.data

L_0:
    LoadParticleResource 0, attack_order_spa
    CreateEmitter 0, 1, EMITTER_CB_SET_POS_TO_ATTACKER
    Delay 11
    PlayPannedSoundEffect SEQ_SE_DP_W456, BATTLE_SOUND_PAN_LEFT
    Delay 10
    Func_Shake 2, 0, 1, 16, BATTLE_ANIM_BATTLER_SPRITE_ATTACKER
    WaitForAllEmitters
    UnloadParticleSystem 0
    End
