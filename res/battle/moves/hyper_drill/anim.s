#include "macros/btlanimcmd.inc"

L_0:
    LoadParticleResource 0, horn_drill_spa
    ResetVars
    SetVar BATTLE_ANIM_VAR_BG_SCREEN_MODE, 1
    SwitchBg 6, BATTLE_BG_SWITCH_MODE_FADE
    Func_MoveBattler 258, 14, -8, 2
    WaitForAnimTasks
    PlaySoundEffectR SEQ_SE_DP_W030
    PlayDelayedSoundEffectR SEQ_SE_DP_145, 5
    JumpIfBattlerSide 0, L_1, L_2
    End

L_1:
    CreateEmitter 0, 3, EMITTER_CB_SET_POS_TO_DEFENDER
    CreateEmitter 0, 0, EMITTER_CB_SET_POS_TO_DEFENDER
    CreateEmitter 0, 6, EMITTER_CB_SET_POS_TO_DEFENDER
    Func_Shake 1, 0, 1, 12, 264
    WaitForAllEmitters
    UnloadParticleSystem 0
    Func_MoveBattler 258, -14, 8, 2
    ResetVars
    SetVar BATTLE_ANIM_VAR_BG_SCREEN_MODE, 1
    RestoreBg 6, BATTLE_BG_SWITCH_MODE_FADE
    WaitForBgSwitch
    WaitForAnimTasks
    End

L_2:
    CreateEmitter 0, 4, EMITTER_CB_SET_POS_TO_DEFENDER
    CreateEmitter 0, 1, EMITTER_CB_SET_POS_TO_DEFENDER
    CreateEmitter 0, 7, EMITTER_CB_SET_POS_TO_DEFENDER
    Func_Shake 1, 0, 1, 12, 264
    WaitForAllEmitters
    UnloadParticleSystem 0
    Func_MoveBattler 258, -14, 8, 2
    ResetVars
    SetVar BATTLE_ANIM_VAR_BG_SCREEN_MODE, 1
    RestoreBg 6, BATTLE_BG_SWITCH_MODE_FADE
    WaitForBgSwitch
    WaitForAnimTasks
    End
