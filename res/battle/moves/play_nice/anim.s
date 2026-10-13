#include "macros/btlanimcmd.inc"

L_0:
    LoadParticleResource 0, attract_spa
    Func_PlayfulHops 1
    Func_PlayfulHops
    PlayLoopedSoundEffectR SEQ_SE_DP_W204, 8, 4
    WaitForAnimTasks
    WaitForAllEmitters
    UnloadParticleSystem 0
    End
