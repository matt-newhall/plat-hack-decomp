#include "macros/scrcmd.inc"
#include "res/text/bank/lake_valor_drained.h"
#include "res/field/events/events_lake_valor_drained.h"


    ScriptEntry LakeValorDrained_GruntM1
    ScriptEntry LakeValorDrained_GruntF
    ScriptEntry LakeValorDrained_GruntM2
    ScriptEntry LakeValorDrained_Magikarp
    ScriptEntry LakeValorDrained_OnTransition
    ScriptEntry LakeValorDrained_PaulJoin
    ScriptEntry LakeValorDrained_PaulStepBack
    ScriptEntryEnd

LakeValorDrained_GruntM1:
    NPCMessage LakeValorDrained_Text_WhatYouDoWant
    End

LakeValorDrained_GruntF:
    NPCMessage LakeValorDrained_Text_MagikarpWorthless
    End

LakeValorDrained_GruntM2:
    NPCMessage LakeValorDrained_Text_NextStopLakeVerity
    End

LakeValorDrained_Magikarp:
    PokemonCryAndMessage SPECIES_MAGIKARP, LakeValorDrained_Text_MagikarpIsFlopping, 11
    End

LakeValorDrained_OnTransition:
    GoToIfSet FLAG_DEFEATED_COMMANDER_SATURN_VALOR_CAVERN, LakeValorDrained_OnTransition_Done
    SetVar VAR_LAKE_VALOR_PAUL_STATE, 0
    SetVar VAR_FOLLOWER_PAUL_TIMES_TALKED, 0
    ClearHasPartner
    End

LakeValorDrained_OnTransition_Done:
    End

LakeValorDrained_PaulJoin:
    LockAll
    SetPlayerBike FALSE
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    CallIfEq VAR_0x8005, 11, LakeValorDrained_PaulWalkToPlayerRow
    CallIfEq VAR_0x8005, 10, LakeValorDrained_PaulNoticeSameRow
    BufferPlayerName 0
    Message LakeValorDrained_Text_PaulJoin
    WaitButton
    PlayFanfare SEQ_GONIN
    Message LakeValorDrained_Text_PlayerDecidedToGoWithPaul
    WaitFanfare
    WaitButton
    CloseMessage
    SetVar VAR_PARTNER_TRAINER_ID, TRAINER_PAUL_LAKE_VALOR_ALLY
    SetHasPartner
    SetVar VAR_LAKE_VALOR_PAUL_STATE, 1
    SetMovementType LOCALID_PAUL, MOVEMENT_TYPE_FOLLOW_PLAYER
    SetObjectFlagIsPersistent LOCALID_PAUL, TRUE
    ReleaseAll
    End

LakeValorDrained_PaulNoticeSameRow:
    ApplyMovement LOCALID_PAUL, LakeValorDrained_Movement_PaulExclaimFaceEast
    WaitMovement
    Return

LakeValorDrained_PaulWalkToPlayerRow:
    ApplyMovement LOCALID_PAUL, LakeValorDrained_Movement_PaulExclaimWalkDown
    WaitMovement
    Return

LakeValorDrained_PaulStepBack:
    LockAll
    ApplyMovement LOCALID_PAUL, LakeValorDrained_Movement_PaulFacePlayer
    WaitMovement
    Message LakeValorDrained_Text_PaulStepBack
    WaitButton
    CloseMessage
    SetVar VAR_LAKE_VALOR_PAUL_STATE, 0
    ClearHasPartner
    SetMovementType LOCALID_PAUL, MOVEMENT_TYPE_LOOK_EAST
    SetObjectFlagIsPersistent LOCALID_PAUL, FALSE
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    CallIfEq VAR_0x8005, 11, LakeValorDrained_PaulReturnHomeRow11
    CallIfEq VAR_0x8005, 10, LakeValorDrained_PaulReturnHomeRow10
    ReleaseAll
    End

LakeValorDrained_PaulReturnHomeRow10:
    ApplyMovement LOCALID_PAUL, LakeValorDrained_Movement_PaulReturnHomeRow10
    WaitMovement
    Return

LakeValorDrained_PaulReturnHomeRow11:
    ApplyMovement LOCALID_PAUL, LakeValorDrained_Movement_PaulReturnHomeRow11
    WaitMovement
    Return

    .balign 4, 0
LakeValorDrained_Movement_PaulExclaimFaceEast:
    EmoteExclamationMark
    Delay15
    FaceEast
    EndMovement

    .balign 4, 0
LakeValorDrained_Movement_PaulExclaimWalkDown:
    EmoteExclamationMark
    Delay15
    WalkNormalSouth
    FaceEast
    EndMovement

    .balign 4, 0
LakeValorDrained_Movement_PaulFacePlayer:
    WalkOnSpotNormalEast
    EndMovement

    .balign 4, 0
LakeValorDrained_Movement_PaulReturnHomeRow10:
    WalkNormalWest
    FaceEast
    EndMovement

    .balign 4, 0
LakeValorDrained_Movement_PaulReturnHomeRow11:
    WalkNormalWest
    WalkNormalNorth
    FaceEast
    EndMovement

    .balign 4, 0
