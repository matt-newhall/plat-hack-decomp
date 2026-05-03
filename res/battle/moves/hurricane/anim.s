#include "macros/btlanimcmd.inc"

L_0:
    InitPokemonSpriteManager
    LoadPokemonSpriteDummyResources 0
    LoadPokemonSpriteDummyResources 1
    LoadPokemonSpriteDummyResources 2
    LoadPokemonSpriteDummyResources 3
    AddPokemonSprite BATTLER_ROLE_PLAYER_1, FALSE, BATTLE_ANIM_MON_SPRITE_0, 0
    AddPokemonSprite BATTLER_ROLE_ENEMY_1, FALSE, BATTLE_ANIM_MON_SPRITE_1, 1
    AddPokemonSprite BATTLER_ROLE_PLAYER_2, FALSE, BATTLE_ANIM_MON_SPRITE_2, 2
    AddPokemonSprite BATTLER_ROLE_ENEMY_2, FALSE, BATTLE_ANIM_MON_SPRITE_3, 3
    SetVar BATTLE_ANIM_VAR_BG_MOVE_STEP_X, 1
    SetVar BATTLE_ANIM_VAR_BG_MOVE_STEP_Y, 0
    SetVar BATTLE_ANIM_VAR_BG_SCREEN_MODE, BATTLE_BG_SCREEN_REVERSE_ENEMY_ONLY
    SetVar BATTLE_ANIM_VAR_BG_ANIM_MODE, BATTLE_BG_ANIM_REVERSE_ENEMY_ONLY
    SwitchBg 19, BATTLE_BG_SWITCH_MODE_FADE | BATTLE_BG_SWITCH_FLAG_MOVE
    WaitForBgSwitch
    Func_RenderPokemonSprites 0
    LoadParticleSystem 0, twister_spa
    WaitForAnimTasks
    FreePokemonSpriteManager
    RemovePokemonSprite BATTLE_ANIM_MON_SPRITE_0
    RemovePokemonSprite BATTLE_ANIM_MON_SPRITE_1
    RemovePokemonSprite BATTLE_ANIM_MON_SPRITE_2
    RemovePokemonSprite BATTLE_ANIM_MON_SPRITE_3
    SetCameraProjection 0, 0
    CreateEmitter 0, 0, EMITTER_CB_SET_POS_TO_DEFENDER_SIDE
    CreateEmitter 0, 1, EMITTER_CB_SET_POS_TO_DEFENDER_SIDE
    Delay 10
    PlaySoundEffectR SEQ_SE_DP_060
    Delay 10
    Func_Shake 3, 0, 1, 15, BATTLE_ANIM_BATTLER_SPRITE_DEFENDER
    WaitForAnimTasks
    SetVar BATTLE_ANIM_VAR_BG_MOVE_STEP_X, 1
    SetVar BATTLE_ANIM_VAR_BG_MOVE_STEP_Y, 0
    SetVar BATTLE_ANIM_VAR_BG_SCREEN_MODE, BATTLE_BG_SCREEN_REVERSE_ENEMY_ONLY
    SetVar BATTLE_ANIM_VAR_BG_ANIM_MODE, BATTLE_BG_ANIM_REVERSE_ENEMY_ONLY
    RestoreBg 19, BATTLE_BG_SWITCH_MODE_FADE | BATTLE_BG_SWITCH_FLAG_STOP
    WaitForBgSwitch
    UnloadParticleSystem 0
    End
