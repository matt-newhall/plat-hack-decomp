#include "macros/btlanimcmd.inc"

L_0:
    LoadParticleResource 0, extrasensory_spa
    LoadParticleResource 1, psywave_spa
    SetVar BATTLE_ANIM_VAR_BG_MOVE_STEP_Y, 8
    SwitchBg 52, BATTLE_BG_SWITCH_MODE_FADE | BATTLE_BG_SWITCH_FLAG_MOVE
    WaitForBgSwitch
    PlaySoundEffectL SEQ_SE_DP_W020
    CreateEmitter 0, 0, EMITTER_CB_SET_POS_TO_ATTACKER
    Delay 10
    CreateEmitter 1, 1, EMITTER_CB_SET_POS_TO_DEFENDER
    Func_Shake 4, 0, 1, 4, BATTLE_ANIM_BATTLER_SPRITE_DEFENDER
    Func_FadeBattlerSprite BATTLE_ANIM_DEFENDER, 0, 2, BATTLE_COLOR_WHITE, 10, 0
    PlayLoopedSoundEffectR SEQ_SE_DP_161, 4, 2
    WaitForAllEmitters
    UnloadParticleSystem 0
    UnloadParticleSystem 1
    SetVar BATTLE_ANIM_VAR_BG_MOVE_STEP_Y, 8
    RestoreBg 52, BATTLE_BG_SWITCH_MODE_FADE | BATTLE_BG_SWITCH_FLAG_STOP
    WaitForBgSwitch
    End
