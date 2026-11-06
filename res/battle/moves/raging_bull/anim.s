#include "macros/btlanimcmd.inc"

L_0:
    LoadParticleResource 0, rage_spa
    PlaySoundEffectL SEQ_SE_DP_131
    Func_FadeBattlerSprite 2, 0, 2, 31, 10, 0
    WaitForAnimTasks
    WaitForAllEmitters
    UnloadParticleSystem 0
    LoadParticleSystem 0, take_down_spa
    WaitForAnimTasks
    FreePokemonSpriteManager
    RemovePokemonSprite BATTLE_ANIM_MON_SPRITE_0
    RemovePokemonSprite BATTLE_ANIM_MON_SPRITE_1
    RemovePokemonSprite BATTLE_ANIM_MON_SPRITE_2
    RemovePokemonSprite BATTLE_ANIM_MON_SPRITE_3
    PlaySoundEffectL SEQ_SE_DP_W029
    Func_MoveBattler 258, -16, 8, 4
    WaitForAnimTasks
    Delay 15
    PlaySoundEffectR SEQ_SE_DP_140
    Func_MoveBattler 258, 32, -16, 4
    WaitForAnimTasks
    CreateEmitter 0, 1, EMITTER_CB_SET_POS_TO_DEFENDER
    CreateEmitter 0, 0, EMITTER_CB_SET_POS_TO_DEFENDER
    CreateEmitter 0, 2, EMITTER_CB_SET_POS_TO_DEFENDER
    Func_Shake 4, 0, 1, 4, 264
    Func_MoveBattler 258, -16, 8, 4
    WaitForAnimTasks
    End
