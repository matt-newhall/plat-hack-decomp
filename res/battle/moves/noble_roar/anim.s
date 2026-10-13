#include "macros/btlanimcmd.inc"

L_0:
    LoadParticleResource 0, hyper_voice_spa
    PlayPokemonCry 0, -117, 127
    CreateEmitter 0, 1, EMITTER_CB_GENERIC
    SetExtraParams 0, 2, 22, 16, 0, 0
    CreateEmitter 0, 0, EMITTER_CB_SET_POS_TO_DEFENDER
    Func_FadeBg 0, 1, 0, 8, 13311
    Func_Shake 0, 2, 1, 2, 264
    Func_Shake 0, 2, 1, 2, 272
    WaitForAnimTasks
    Func_FadeBg 0, 1, 8, 0, 13311
    WaitForAnimTasks
    WaitForPokemonCries 0
    Delay 2
    WaitForAllEmitters
    UnloadParticleSystem 0
    End
