#include "macros/btlanimcmd.inc"

L_0:
    LoadParticleResource 0, twister_spa
    SetCameraProjection 0, 0
    CreateEmitter 0, 0, EMITTER_CB_SET_POS_TO_DEFENDER_SIDE
    CreateEmitter 0, 1, EMITTER_CB_SET_POS_TO_DEFENDER_SIDE
    Delay 10
    PlaySoundEffectR SEQ_SE_DP_060
    Delay 10
    Func_Shake 3, 0, 1, 15, 264
    Func_Shake 3, 0, 1, 15, 272
    LoadParticleSystem 0, leaf_blade_spa
    CreateEmitter 0, 0, EMITTER_CB_SET_POS_TO_DEFENDER
    PlaySoundEffectL SEQ_SE_DP_KAZE
    Delay 40
    LoadParticleSystem 1, pound_spa
    PlaySoundEffectR SEQ_SE_DP_030
    CreateEmitter 1, 1, EMITTER_CB_SET_POS_TO_DEFENDER
    Func_Shake 3, 0, 1, 10, 264
    Delay 8
    PlaySoundEffectR SEQ_SE_DP_030
    CreateEmitter 1, 1, EMITTER_CB_SET_POS_TO_DEFENDER
    Delay 8
    PlaySoundEffectR SEQ_SE_DP_030
    CreateEmitter 1, 1, EMITTER_CB_SET_POS_TO_DEFENDER
    Delay 8
    WaitForAllEmitters
    UnloadParticleSystem 0
    End
