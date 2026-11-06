#include "macros/btlanimcmd.inc"

L_0:
    LoadParticleResource 0, silver_wind_spa
    PlaySoundEffectC SEQ_SE_DP_W016
    CreateEmitter 0, 0, EMITTER_CB_GENERIC
    SetExtraParams 0, 2, 0, 0, 0, 0
    Func_FadeBg FADE_BG_TYPE_BASE, 1, 0, 12, 0x7E9F
    WaitForAnimTasks
    CreateEmitter 0, 1, EMITTER_CB_GENERIC
    SetExtraParams 0, 2, 0, 0, 0, 0
    PlaySoundEffectC SEQ_SE_DP_W234
    WaitForAllEmitters
    UnloadParticleSystem 0
    Func_FadeBg FADE_BG_TYPE_BASE, 1, 12, 0, 0x7E9F
    WaitForAnimTasks
    StopSoundEffect SEQ_SE_DP_W016
    StopSoundEffect SEQ_SE_DP_W234
    End

