#include "macros/btlanimcmd.inc"

L_0:
    LoadParticleResource 0, outrage_spa
    InitPokemonSpriteManager
    LoadPokemonSpriteDummyResources 0
    LoadPokemonSpriteDummyResources 1
    AddPokemonSprite BATTLER_ROLE_ATTACKER, FALSE, BATTLE_ANIM_MON_SPRITE_0, 0
    AddPokemonSprite BATTLER_ROLE_ATTACKER, FALSE, BATTLE_ANIM_MON_SPRITE_1, 1
    Delay 1
    ResetVars
    SetVar BATTLE_ANIM_VAR_BG_SCREEN_MODE, 1
    SwitchBg 22, BATTLE_BG_SWITCH_MODE_FADE
    WaitForBgSwitch
    PlayLoopedSoundEffectL SEQ_SE_DP_W082, 4, 2
    CreateEmitter 0, 0, EMITTER_CB_SET_POS_TO_ATTACKER
    CreateEmitter 0, 1, EMITTER_CB_SET_POS_TO_ATTACKER
    Func_FadeBattlerSprite 8, 0, 3, 31, 10, 10
    Func_Shake 3, 0, 0, 13, 264
    BeginLoop 2
    Func_FadeBg 0, 0, 0, 10, 31
    Delay 10
    Func_FadeBg 0, 0, 10, 0, 31
    Delay 10
    EndLoop
    Func_FadeBg 0, 0, 0, 10, 31
    Delay 10
    Func_FadeBg 0, 0, 10, 0, 31
    PlayMovingSoundEffectAtkDef SEQ_SE_DP_W053B, -117, 117, 4, 2
    Delay 10
    WaitForAllEmitters
    UnloadParticleSystem 0
    SetVar BATTLE_ANIM_VAR_BG_SCREEN_MODE, 1
    RestoreBg 22, BATTLE_BG_SWITCH_MODE_FADE
    WaitForBgSwitch
    RemovePokemonSprite BATTLE_ANIM_MON_SPRITE_0
    RemovePokemonSprite BATTLE_ANIM_MON_SPRITE_1
    FreePokemonSpriteManager
    End
