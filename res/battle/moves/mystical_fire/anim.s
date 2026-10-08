#include "macros/btlanimcmd.inc"

L_0:
    LoadParticleResource 0, will_o_wisp_spa
    LoadParticleResource 1, sacred_fire_spa
    Func_FadeBg FADE_BG_TYPE_BASE, 1, 0, 12, 0x1803
    PlayMovingSoundEffectAtkDef SEQ_SE_DP_W052, BATTLE_SOUND_PAN_LEFT, BATTLE_SOUND_PAN_RIGHT, 4, 2
    CreateEmitter 0, 0, EMITTER_CB_GENERIC
    SetExtraParams 0, 2, 6, 1, 16, 0
    SetExtraParams 3, 0, 0, 0, 0
    Delay 30
    CreateEmitter 1, 1, EMITTER_CB_SET_POS_TO_DEFENDER
    CreateEmitter 1, 2, EMITTER_CB_SET_POS_TO_DEFENDER
    PlaySoundEffectR SEQ_SE_DP_W172B
    Func_Shake 2, 0, 1, 2, BATTLE_ANIM_BATTLER_SPRITE_DEFENDER
    WaitForAllEmitters
    UnloadParticleSystem 0
    UnloadParticleSystem 1
    Func_FadeBg FADE_BG_TYPE_BASE, 1, 12, 0, 0x1803
    WaitForAnimTasks
    End
