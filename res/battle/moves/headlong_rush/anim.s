#include "macros/btlanimcmd.inc"

L_0:
    LoadParticleResource 0, head_smash_spa
    PlaySoundEffectR SEQ_SE_DP_143
    Func_MoveBattler 258, -16, 8, 4
    WaitForAnimTasks
    Delay 15
    ResetVars
    SetVar BATTLE_ANIM_VAR_BG_SCREEN_MODE, 1
    SwitchBg 40, BATTLE_BG_SWITCH_MODE_FADE
    Func_MoveBattler 258, 32, -16, 4
    WaitForAnimTasks
    Func_ShakeBg 4, 4, 0, 10, 0
    PlaySoundEffectR SEQ_SE_DP_186
    Func_Shake 2, 0, 1, 2, 264
    Func_MoveBattler 258, -16, 8, 4
    Func_FadeBattlerSprite 8, 0, 1, 31, 14, 0
    WaitForAnimTasks
    WaitForAllEmitters
    UnloadParticleSystem 0
    ResetVars
    SetVar BATTLE_ANIM_VAR_BG_SCREEN_MODE, 1
    RestoreBg 40, BATTLE_BG_SWITCH_MODE_FADE
    WaitForBgSwitch
    End
