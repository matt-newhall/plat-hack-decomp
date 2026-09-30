#include "macros/btlanimcmd.inc"

L_0:
    LoadParticleResource 0, rapid_spin_spa
    LoadParticleResource 1, ice_punch_spa
    Func_FadeBg FADE_BG_TYPE_BASE, 1, 0, 8, BATTLE_COLOR_LIGHT_BLUE
    PlaySoundEffectL SEQ_SE_DP_207
    CreateEmitter 0, 1, EMITTER_CB_SET_POS_TO_ATTACKER
    CreateEmitter 0, 2, EMITTER_CB_SET_POS_TO_ATTACKER
    Delay 8
    CreateEmitter 1, 2, EMITTER_CB_SET_POS_TO_DEFENDER
    CreateEmitter 1, 0, EMITTER_CB_SET_POS_TO_DEFENDER
    CreateEmitter 1, 1, EMITTER_CB_SET_POS_TO_DEFENDER
    Func_Shake 2, 0, 1, 8, BATTLE_ANIM_BATTLER_SPRITE_DEFENDER
    PlayLoopedSoundEffectR SEQ_SE_DP_143, 6, 3
    PlayDelayedSoundEffectR SEQ_SE_DP_W280, 5
    Func_FadeBattlerSprite BATTLE_ANIM_DEFENDER, 0, 2, BATTLE_COLOR_LIGHT_BLUE, 14, 0
    WaitForAllEmitters
    UnloadParticleSystem 0
    UnloadParticleSystem 1
    Func_FadeBg FADE_BG_TYPE_BASE, 1, 8, 0, BATTLE_COLOR_LIGHT_BLUE
    WaitForAnimTasks
    End
