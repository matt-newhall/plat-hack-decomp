#include "macros/btlanimcmd.inc"

L_0:
    LoadParticleResource 0, ice_shard_spa
    LoadParticleResource 1, avalanche_spa
    PlaySoundEffectL SEQ_SE_DP_W196
    CreateEmitter 1, 2, EMITTER_CB_SET_POS_TO_DEFENDER
    PlaySoundEffectR SEQ_SE_DP_W070
    Delay 2
    PlaySoundEffectR SEQ_SE_DP_W070
    Delay 2
    PlaySoundEffectR SEQ_SE_DP_W070
    Delay 2
    PlaySoundEffectR SEQ_SE_DP_W070
    Delay 2
    PlaySoundEffectR SEQ_SE_DP_W070
    Delay 2
    PlaySoundEffectR SEQ_SE_DP_W070
    Delay 2
    PlaySoundEffectR SEQ_SE_DP_W070
    Delay 2
    PlaySoundEffectR SEQ_SE_DP_W070
    Delay 2
    CreateEmitter 0, 1, EMITTER_CB_SET_POS_TO_DEFENDER
    Delay 10
    CreateEmitter 0, 1, EMITTER_CB_SET_POS_TO_DEFENDER
    CreateEmitter 1, 5, EMITTER_CB_SET_POS_TO_DEFENDER
    Delay 5
    CreateEmitter 0, 0, EMITTER_CB_SET_POS_TO_DEFENDER
    PlayLoopedSoundEffectR SEQ_SE_DP_030, 2, 3
    Func_FadeBattlerSprite BATTLE_ANIM_DEFENDER, 1, 1, 0x7000, 12,
    Func_Shake 5, 0, 1, 3, BATTLE_ANIM_BATTLER_SPRITE_DEFENDER
    WaitForAllEmitters
    UnloadParticleSystem 0
    UnloadParticleSystem 1
    WaitForAnimTasks
    End
