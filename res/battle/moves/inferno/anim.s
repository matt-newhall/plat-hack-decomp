#include "macros/btlanimcmd.inc"

L_0:
    LoadParticleResource 0, blast_burn_spa
    WaitForAllEmitters
    LoadParticleResource 1, fire_spin_spa
    WaitForAllEmitters
    ResetVars
    SetVar BATTLE_ANIM_VAR_BG_FADE_TYPE, 1
    SetVar BATTLE_ANIM_VAR_BG_MOVE_STEP_X, 0
    SetVar BATTLE_ANIM_VAR_BG_MOVE_STEP_Y, 32
    SwitchBg 43, BATTLE_BG_SWITCH_MODE_FADE | BATTLE_BG_SWITCH_FLAG_MOVE
    WaitForBgSwitch
    PlaySoundEffectR SEQ_SE_DP_W463
    PlayLoopedSoundEffectL SEQ_SE_DP_W085, 1, 2
    CreateEmitterEx 0, 3, 0, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 3, -90, -90, -90, -90, 48, 24, 7, 0, 0
    CreateEmitterEx 0, 4, 1, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 4, -90, -90, -90, -90, 48, 24, 7, 0, 0
    CreateEmitterEx 0, 5, 2, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 5, -90, -90, -90, -90, 48, 24, 7, 0, 0
    CreateEmitterEx 0, 6, 0, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 6, -45, -45, -45, -45, 48, 24, 7, 0, 0
    CreateEmitterEx 0, 7, 1, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 7, -45, -45, -45, -45, 48, 24, 7, 0, 0
    CreateEmitterEx 0, 8, 2, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 8, -45, -45, -45, -45, 48, 24, 7, 0, 0
    CreateEmitterEx 0, 9, 0, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 9, 0, 0, 0, 0, 48, 24, 7, 0, 0
    CreateEmitterEx 0, 10, 1, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 10, 0, 0, 0, 0, 48, 24, 7, 0, 0
    CreateEmitterEx 0, 11, 2, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 11, 0, 0, 0, 0, 48, 24, 7, 0, 0
    CreateEmitterEx 0, 9, 0, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 9, 45, 45, 45, 45, 48, 24, 7, 0, 0
    CreateEmitterEx 0, 10, 1, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 10, 45, 45, 45, 45, 48, 24, 7, 0, 0
    CreateEmitterEx 0, 11, 2, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 11, 45, 45, 45, 45, 48, 24, 7, 0, 0
    CreateEmitterEx 0, 12, 0, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 12, 90, 90, 90, 90, 48, 24, 7, 0, 0
    CreateEmitterEx 0, 13, 1, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 13, 90, 90, 90, 90, 48, 24, 7, 0, 0
    CreateEmitterEx 0, 14, 2, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 14, 90, 90, 90, 90, 48, 24, 7, 0, 0
    Delay 8
    PlayLoopedSoundEffectL SEQ_SE_DP_W085, 1, 2
    CreateEmitterEx 0, 3, 0, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 3, -90, -90, -90, -90, 64, 24, 7, 0, 0
    CreateEmitterEx 0, 4, 1, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 4, -90, -90, -90, -90, 64, 24, 7, 0, 0
    CreateEmitterEx 0, 5, 2, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 5, -90, -90, -90, -90, 64, 24, 7, 0, 0
    CreateEmitterEx 0, 6, 0, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 6, -45, -45, -45, -45, 64, 24, 7, 0, 0
    CreateEmitterEx 0, 7, 1, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 7, -45, -45, -45, -45, 64, 24, 7, 0, 0
    CreateEmitterEx 0, 8, 2, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 8, -45, -45, -45, -45, 64, 24, 7, 0, 0
    CreateEmitterEx 0, 9, 0, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 9, 0, 0, 0, 0, 64, 24, 7, 0, 0
    CreateEmitterEx 0, 10, 1, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 10, 0, 0, 0, 0, 64, 24, 7, 0, 0
    CreateEmitterEx 0, 11, 2, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 11, 0, 0, 0, 0, 64, 24, 7, 0, 0
    CreateEmitterEx 0, 9, 0, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 9, 45, 45, 45, 45, 64, 24, 7, 0, 0
    CreateEmitterEx 0, 10, 1, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 10, 45, 45, 45, 45, 64, 24, 7, 0, 0
    CreateEmitterEx 0, 11, 2, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 11, 45, 45, 45, 45, 64, 24, 7, 0, 0
    CreateEmitterEx 0, 12, 0, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 12, 90, 90, 90, 90, 64, 24, 7, 0, 0
    CreateEmitterEx 0, 13, 1, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 13, 90, 90, 90, 90, 64, 24, 7, 0, 0
    CreateEmitterEx 0, 14, 2, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_RevolveEmitter 14, 90, 90, 90, 90, 64, 24, 7, 0, 0
    Delay 8
    PlaySoundEffectR SEQ_SE_DP_W463
    Func_FadeBattlerSprite 8, 1, 1, 31, 12
    Func_Shake 5, 0, 1, 3, 264
    CreateEmitter 1, 0, EMITTER_CB_SET_POS_TO_DEFENDER
    CreateEmitter 1, 1, EMITTER_CB_SET_POS_TO_DEFENDER
    WaitForAllEmitters
    ResetVars
    SetVar BATTLE_ANIM_VAR_BG_FADE_TYPE, 1
    SetVar BATTLE_ANIM_VAR_BG_MOVE_STEP_X, 0
    SetVar BATTLE_ANIM_VAR_BG_MOVE_STEP_Y, 32
    RestoreBg 43, BATTLE_BG_SWITCH_MODE_FADE | BATTLE_BG_SWITCH_FLAG_STOP
    WaitForBgSwitch
    UnloadParticleSystem 0
    UnloadParticleSystem 1
    WaitForAnimTasks
    End
