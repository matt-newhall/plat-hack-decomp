#include "macros/btlanimcmd.inc"

L_0:
    LoadParticleResource 0, flamethrower_spa
    PlayLoopedSoundEffectL SEQ_SE_DP_W052, 3, 6
    CreateEmitter 0, 0, EMITTER_CB_SET_POS_TO_DEFENDER_SIDE
    Func_Shake 2, 0, 1, 14, BATTLE_ANIM_BATTLER_SPRITE_ATTACKER
    Delay 3
    Func_FadeBattlerSprite BATTLE_ANIM_DEFENDER, 0, 1, BATTLE_COLOR_RED, 10, 25
    Func_FadeBattlerSprite BATTLE_ANIM_DEFENDER_PARTNER, 0, 1, BATTLE_COLOR_RED, 10, 25
    Func_Shake 2, 0, 1, 14, BATTLE_ANIM_BATTLER_SPRITE_DEFENDER
    Func_Shake 2, 0, 1, 14, BATTLE_ANIM_BATTLER_SPRITE_DEFENDER_PARTNER
    WaitForAllEmitters
    UnloadParticleSystem 0
    WaitForAnimTasks
    End
