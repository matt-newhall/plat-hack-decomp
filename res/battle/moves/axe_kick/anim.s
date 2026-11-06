#include "macros/btlanimcmd.inc"

L_0:
    LoadParticleResource 0, mega_kick_spa
    WaitForAllEmitters
    LoadParticleResource 1, blaze_kick_spa
    WaitForAllEmitters
    ResetVars
    SetVar BATTLE_ANIM_VAR_BG_SCREEN_MODE, 1
    SwitchBg 0, BATTLE_BG_SWITCH_MODE_FADE
    PlaySoundEffectR SEQ_SE_DP_W172
    CreateEmitter 1, 1, EMITTER_CB_SET_POS_TO_DEFENDER
    Delay 5
    CreateEmitter 0, 1, EMITTER_CB_SET_POS_TO_DEFENDER
    CreateEmitter 0, 2, EMITTER_CB_SET_POS_TO_DEFENDER
    CreateEmitter 0, 0, EMITTER_CB_SET_POS_TO_DEFENDER
    CreateEmitter 0, 3, EMITTER_CB_SET_POS_TO_DEFENDER
    PlayDelayedSoundEffectR SEQ_SE_DP_140, 1
    Func_Shake 4, 0, 1, 2, 264
    Delay 1
    Func_ShakeBg 5, 0, 1, 3, 0
    WaitForAnimTasks
    WaitForAllEmitters
    UnloadParticleSystem 0
    WaitForAnimTasks
    UnloadParticleSystem 1
    WaitForAnimTasks
    ResetVars
    SetVar BATTLE_ANIM_VAR_BG_SCREEN_MODE, 1
    RestoreBg 0, BATTLE_BG_SWITCH_MODE_FADE
    WaitForBgSwitch
    End
