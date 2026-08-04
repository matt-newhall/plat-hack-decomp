#include "macros/btlanimcmd.inc"

.data

L_0:
    LoadParticleResource 0, 312
    PlayPannedSoundEffect 1957, BATTLE_SOUND_PAN_LEFT
    CreateEmitter 0, 1, EMITTER_CB_SET_POS_TO_ATTACKER
    CreateEmitter 0, 2, EMITTER_CB_SET_POS_TO_ATTACKER
    CreateEmitter 0, 3, EMITTER_CB_SET_POS_TO_ATTACKER
    CreateEmitter 0, 4, EMITTER_CB_SET_POS_TO_ATTACKER
    Delay 60
    Func_FadeBg FADE_BG_TYPE_BASE, 1, 0, 16, BATTLE_COLOR_WHITE
    Func_FadeBattlerSprite BATTLE_ANIM_BATTLER_PLAYER_1, 0, 1, BATTLE_COLOR_WHITE, 16, 60
    Func_FadeBattlerSprite BATTLE_ANIM_BATTLER_ENEMY_1, 0, 1, BATTLE_COLOR_WHITE, 16, 60
    Func_FadeBattlerSprite BATTLE_ANIM_BATTLER_PLAYER_2, 0, 1, BATTLE_COLOR_WHITE, 16, 60
    Func_FadeBattlerSprite BATTLE_ANIM_BATTLER_ENEMY_2, 0, 1, BATTLE_COLOR_WHITE, 16, 60
    Delay 20
    PlayLoopedSoundEffect 1926, 117, 4, 8
    Delay 20
    Func_FadeBg FADE_BG_TYPE_BASE, 1, 16, 0, BATTLE_COLOR_WHITE
    Func_Shake 4, 0, 1, 6, BATTLE_ANIM_BATTLER_SPRITE_DEFENDER
    WaitForAnimTasks
    WaitForAllEmitters
    UnloadParticleSystem 0
    End
