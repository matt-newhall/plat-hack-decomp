#include "macros/btlanimcmd.inc"

L_0:
    LoadParticleResource 0, psycho_cut_spa
    LoadParticleResource 1, night_slash_spa
    SetVar BATTLE_ANIM_VAR_BG_MOVE_STEP_Y, 8
    SwitchBg 52, BATTLE_BG_SWITCH_MODE_FADE | BATTLE_BG_SWITCH_FLAG_MOVE
    WaitForBgSwitch
    PlaySoundEffectL SEQ_SE_DP_020
    CreateEmitter 0, 5, EMITTER_CB_GENERIC
    SetExtraParams 0, 2, 1, 0, 0, 0
    CreateEmitter 0, 0, EMITTER_CB_GENERIC
    SetExtraParams 0, 2, 1, 0, 0, 0
    CreateEmitter 0, 1, EMITTER_CB_GENERIC
    SetExtraParams 0, 2, 1, 0, 0, 0
    Delay 45
    PlayLoopedSoundEffectC SEQ_SE_DP_HURU, 2, 9
    JumpIfBattlerSide BATTLER_ROLE_ATTACKER, L_1, L_2
    End

L_1:
    JumpIfContest L_3
    CreateEmitter 0, 2, EMITTER_CB_SET_POS_TO_ATTACKER
    Jump L_4

L_3:
    CreateEmitter 0, 4, EMITTER_CB_SET_POS_TO_ATTACKER
    Jump L_4

L_2:
    CreateEmitter 0, 3, EMITTER_CB_SET_POS_TO_ATTACKER

L_4:
    Func_MoveEmitterA2BLinear 0, 0, 0, 0, 20, 64
    Delay 19
    PlaySoundEffectC SEQ_SE_DP_BRADE
    PlayDelayedSoundEffectC SEQ_SE_DP_W233, 10
    CreateEmitter 1, 4, EMITTER_CB_SET_POS_TO_DEFENDER
    CreateEmitter 1, 0, EMITTER_CB_SET_POS_TO_DEFENDER
    Func_Shake 1, 0, 1, 6, BATTLE_ANIM_BATTLER_SPRITE_DEFENDER
    WaitForAllEmitters
    UnloadParticleSystem 0
    UnloadParticleSystem 1
    SetVar BATTLE_ANIM_VAR_BG_MOVE_STEP_Y, 8
    RestoreBg 52, BATTLE_BG_SWITCH_MODE_FADE | BATTLE_BG_SWITCH_FLAG_STOP
    WaitForBgSwitch
    End
