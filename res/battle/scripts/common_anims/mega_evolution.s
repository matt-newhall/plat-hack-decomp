#include "macros/btlanimcmd.inc"

.data

L_0:
    LoadParticleResource 0, 312
    InitSpriteManager 0, 1, 1, 1, 1, 1, 0, 0
    LoadCharResObj 0, 32
    LoadPlttRes 0, 32, 1
    LoadCellResObj 0, 32
    LoadAnimResObj 0, 32
    AddSpriteWithFunc 0, 33, 32, 32, 32, 32, 0, 0, 73, 75
    PlayPannedSoundEffect 1957, BATTLE_SOUND_PAN_LEFT
    CreateEmitter 0, 1, EMITTER_CB_SET_POS_TO_ATTACKER
    CreateEmitter 0, 2, EMITTER_CB_SET_POS_TO_ATTACKER
    CreateEmitter 0, 3, EMITTER_CB_SET_POS_TO_ATTACKER
    CreateEmitter 0, 4, EMITTER_CB_SET_POS_TO_ATTACKER
    Delay 100
    UnloadParticleSystem 0
    FreeSpriteManager 0
    WaitForAnimTasks
    End
