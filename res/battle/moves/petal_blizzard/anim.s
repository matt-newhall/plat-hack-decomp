#include "macros/btlanimcmd.inc"

L_0:
    LoadParticleResource 0, sweet_scent_spa
    PlaySoundEffectC SEQ_SE_DP_W230
    CreateEmitter 0, 1, EMITTER_CB_GENERIC
    SetExtraParams 0, 2, 3, 0, 0, 0
    SetExtraParams 1, -2000, 8000, 0
    CreateEmitter 0, 3, EMITTER_CB_NONE
    CreateEmitter 0, 4, EMITTER_CB_SET_POS_TO_DEFENDER
    Func_FadeBattlerSprite 8, 0, 2, 23199, 12
    Func_FadeBattlerSprite 16, 0, 2, 23199, 12
    Delay 20
    LoadParticleSystem 1, pound_spa
    PlaySoundEffectR SEQ_SE_DP_030
    CreateEmitter 1, 1, EMITTER_CB_SET_POS_TO_DEFENDER
    Func_MoveBattlerX 1, 4, 264
    Delay 8
    PlaySoundEffectR SEQ_SE_DP_030
    CreateEmitter 1, 1, EMITTER_CB_SET_POS_TO_DEFENDER
    Func_MoveBattlerX 1, -4, 264
    Delay 8
    PlaySoundEffectR SEQ_SE_DP_030
    CreateEmitter 1, 1, EMITTER_CB_SET_POS_TO_DEFENDER
    Func_MoveBattlerX 1, -4, 264
    Delay 8
    PlaySoundEffectR SEQ_SE_DP_030
    CreateEmitter 1, 1, EMITTER_CB_SET_POS_TO_DEFENDER
    Func_MoveBattlerX 1, 4, 264
    Delay 8
    WaitForAllEmitters
    UnloadParticleSystem 0
    End
