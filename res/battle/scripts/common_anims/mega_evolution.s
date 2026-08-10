#include "macros/btlanimcmd.inc"

    .equ MEGA_OFFSET_X_SOLO_PLAYER,   -500 // correct
    .equ MEGA_OFFSET_Y_SOLO_PLAYER,   3655 // correct
    .equ MEGA_OFFSET_X_SOLO_ENEMY,    600 // correct
    .equ MEGA_OFFSET_Y_SOLO_ENEMY,    5220 // correct
    .equ MEGA_OFFSET_X_PLAYER_SLOT_1, 340 // correct enough?
    .equ MEGA_OFFSET_Y_PLAYER_SLOT_1, 3520 // correct enough?
    .equ MEGA_OFFSET_X_ENEMY_SLOT_1,  1600 // correct
    .equ MEGA_OFFSET_Y_ENEMY_SLOT_1,  5065 // correct
    .equ MEGA_OFFSET_X_PLAYER_SLOT_2, -670 // correct enough?
    .equ MEGA_OFFSET_Y_PLAYER_SLOT_2, 2990 // correct enough?
    .equ MEGA_OFFSET_X_ENEMY_SLOT_2,  1455 // correct enough?
    .equ MEGA_OFFSET_Y_ENEMY_SLOT_2,  5400 // correct enough?

// Energy draw-in. Currently Solar Beam's charge, which is light streaming inward.
// Self-Destruct's gather is the other candidate — swap all three lines together:
//     .equ MEGA_CHARGE_PARTICLES, psycho_boost_spa
//     .equ MEGA_CHARGE_EMITTER,   4
//     .equ MEGA_CHARGE_SOUND,     SEQ_SE_DP_W376
    .equ MEGA_CHARGE_PARTICLES, solar_beam_spa
    .equ MEGA_CHARGE_EMITTER,   19
    .equ MEGA_CHARGE_SOUND,     SEQ_SE_DP_SHUSHU

// Frames of gather before the shell starts. The gather lives in its own particle
// system, so it keeps resolving underneath the shell rather than being waited out.
    .equ MEGA_CHARGE_GLOW_AT,     20
    .equ MEGA_CHARGE_FRAMES,      45
    .equ MEGA_CHARGE_AFTER_GLOW,  MEGA_CHARGE_FRAMES - MEGA_CHARGE_GLOW_AT

    .equ MEGA_CHARGE_SYSTEM, 1
    .equ MEGA_BURST_SYSTEM,  0

    .equ MEGA_SHAKE_TARGET,   BATTLE_ANIM_BATTLER_SPRITES | BATTLE_ANIM_ATTACKER
    .equ MEGA_SHAKE_EXTENT_X, 3
    .equ MEGA_SHAKE_INTERVAL, 1
    .equ MEGA_SHAKE_CYCLES,   8

// Both particle systems load from a single sprite-manager preamble, the way move
// animations that use more than one do it.
    .macro LoadMegaParticleResources
    InitPokemonSpriteManager
    LoadPokemonSpriteDummyResources 0
    LoadPokemonSpriteDummyResources 1
    LoadPokemonSpriteDummyResources 2
    LoadPokemonSpriteDummyResources 3
    AddPokemonSprite BATTLER_ROLE_PLAYER_1, FALSE, BATTLE_ANIM_MON_SPRITE_0, 0
    AddPokemonSprite BATTLER_ROLE_ENEMY_1, FALSE, BATTLE_ANIM_MON_SPRITE_1, 1
    AddPokemonSprite BATTLER_ROLE_PLAYER_2, FALSE, BATTLE_ANIM_MON_SPRITE_2, 2
    AddPokemonSprite BATTLER_ROLE_ENEMY_2, FALSE, BATTLE_ANIM_MON_SPRITE_3, 3
    Func_RenderPokemonSprites 0
    LoadParticleSystem MEGA_BURST_SYSTEM, luster_purge_spa
    WaitForAnimTasks
    LoadParticleSystem MEGA_CHARGE_SYSTEM, MEGA_CHARGE_PARTICLES
    WaitForAnimTasks
    FreePokemonSpriteManager
    RemovePokemonSprite BATTLE_ANIM_MON_SPRITE_0
    RemovePokemonSprite BATTLE_ANIM_MON_SPRITE_1
    RemovePokemonSprite BATTLE_ANIM_MON_SPRITE_2
    RemovePokemonSprite BATTLE_ANIM_MON_SPRITE_3
    .endm

    .macro MegaEvolutionEmitter particleSystem:req, resourceID:req
    CreateEmitter \particleSystem, \resourceID, EMITTER_CB_GENERIC
    GenericEmitterCbParams EMITTER_PRIORITY_MODE_NONE, EMITTER_TARGET_MODE_DEFAULT, EMITTER_POS_NORMAL_OFFSET_EX_START, EMITTER_AXIS_NONE, EMITTER_BHV_FLAG_NONE, EMITTER_CAMERA_MODE_FIXED_ANGLE_0
    EmitterOffsetPosParams BATTLE_PTCL_FLIP_DISABLE, MEGA_OFFSET_X_SOLO_PLAYER, MEGA_OFFSET_Y_SOLO_PLAYER, 0
    EmitterOffsetPosParams BATTLE_PTCL_FLIP_DISABLE, MEGA_OFFSET_X_SOLO_ENEMY, MEGA_OFFSET_Y_SOLO_ENEMY, 0
    EmitterOffsetPosParams BATTLE_PTCL_FLIP_DISABLE, MEGA_OFFSET_X_PLAYER_SLOT_1, MEGA_OFFSET_Y_PLAYER_SLOT_1, 0
    EmitterOffsetPosParams BATTLE_PTCL_FLIP_DISABLE, MEGA_OFFSET_X_ENEMY_SLOT_1, MEGA_OFFSET_Y_ENEMY_SLOT_1, 0
    EmitterOffsetPosParams BATTLE_PTCL_FLIP_DISABLE, MEGA_OFFSET_X_PLAYER_SLOT_2, MEGA_OFFSET_Y_PLAYER_SLOT_2, 0
    EmitterOffsetPosParams BATTLE_PTCL_FLIP_DISABLE, MEGA_OFFSET_X_ENEMY_SLOT_2, MEGA_OFFSET_Y_ENEMY_SLOT_2, 0
    .endm

.data

L_0:
    LoadMegaParticleResources

    // Draw energy in, then let it keep resolving while the shell takes over.
    MegaEvolutionEmitter MEGA_CHARGE_SYSTEM, MEGA_CHARGE_EMITTER
    PlayPannedSoundEffect MEGA_CHARGE_SOUND, BATTLE_SOUND_PAN_LEFT
    Delay MEGA_CHARGE_GLOW_AT
    // Attacker tinted pale yellow (0x33FF) as the light gathers.
    Func_FadeBattlerSprite BATTLE_ANIM_ATTACKER, 0, 2, 13311, 10, 0
    Delay MEGA_CHARGE_AFTER_GLOW

    InitSpriteManager 0, 1, 1, 1, 1, 1, 0, 0
    LoadCharResObj 0, 32
    LoadPlttRes 0, 32, 1
    LoadCellResObj 0, 32
    LoadAnimResObj 0, 32
    AddSpriteWithFunc 0, 33, 32, 32, 32, 32, 0, 0, 73, 75
    PlayPannedSoundEffect SEQ_SE_DP_W360, BATTLE_SOUND_PAN_LEFT
    MegaEvolutionEmitter MEGA_BURST_SYSTEM, 1
    MegaEvolutionEmitter MEGA_BURST_SYSTEM, 2
    MegaEvolutionEmitter MEGA_BURST_SYSTEM, 3
    MegaEvolutionEmitter MEGA_BURST_SYSTEM, 4
    Delay 75
    PlayPannedSoundEffect SEQ_SE_DP_W360C, BATTLE_SOUND_PAN_LEFT
    Func_Shake MEGA_SHAKE_EXTENT_X, 0, MEGA_SHAKE_INTERVAL, MEGA_SHAKE_CYCLES, MEGA_SHAKE_TARGET
    Delay 25
    UnloadParticleSystem MEGA_BURST_SYSTEM
    UnloadParticleSystem MEGA_CHARGE_SYSTEM
    FreeSpriteManager 0
    WaitForAnimTasks
    End
