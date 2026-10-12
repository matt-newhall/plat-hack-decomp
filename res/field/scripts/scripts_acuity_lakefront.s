#include "macros/scrcmd.inc"
#include "res/text/bank/acuity_lakefront.h"
#include "res/field/events/events_acuity_lakefront.h"


    ScriptEntry AcuityLakefront_OnTransition
    ScriptEntry AcuityLakefront_OnLoad
    ScriptEntry AcuityLakefront_ArrowSignpostLakeAcuity
    ScriptEntry AcuityLakefront_PaulTrigger
    ScriptEntryEnd

AcuityLakefront_OnLoad:
    GoToIfUnset FLAG_TEAM_GALACTIC_LEFT_LAKE_VERITY, AcuityLakefront_RemoveWarpsLakeAcuityNormal
    GoToIfSet FLAG_TEAM_GALACTIC_LEFT_LAKE_VERITY, AcuityLakefront_RemoveWarpsLakeAcuityLowWater
    End

AcuityLakefront_RemoveWarpsLakeAcuityNormal:
    SetWarpEventPos 2, 305, 229
    SetWarpEventPos 3, 306, 229
    End

AcuityLakefront_RemoveWarpsLakeAcuityLowWater:
    SetWarpEventPos 0, 305, 229
    SetWarpEventPos 1, 306, 229
    End

AcuityLakefront_OnTransition:
    SetFlag FLAG_HIDE_ACUITY_LAKEFRONT_PAUL
    CheckBadgeAcquired BADGE_ID_ICICLE, VAR_MAP_LOCAL_0
    CallIfEq VAR_MAP_LOCAL_0, TRUE, AcuityLakefront_SetVeilstoneGymMaylene
    GoToIfUnset FLAG_TEAM_GALACTIC_LEFT_LAKE_VERITY, AcuityLakefront_RemoveWarpsLakeAcuityNormal
    GoToIfSet FLAG_TEAM_GALACTIC_LEFT_LAKE_VERITY, AcuityLakefront_RemoveWarpsLakeAcuityLowWater
    End

AcuityLakefront_SetVeilstoneGymMaylene:
    SetFlag FLAG_HIDE_SNOWPOINT_CITY_POKECENTER_1F_MAYLENE
    ClearFlag FLAG_HIDE_VEILSTONE_CITY_GYM_MAYLENE
    Return

AcuityLakefront_ArrowSignpostLakeAcuity:
    ShowArrowSign AcuityLakefront_Text_SignLakeAcuityAhead
    End

AcuityLakefront_PaulTrigger:
    GoToIfSet FLAG_DEFEATED_PAUL_ACUITY_LAKEFRONT, AcuityLakefront_PaulIgnore
    LockAll
    ClearFlag FLAG_HIDE_ACUITY_LAKEFRONT_PAUL
    AddObject LOCALID_PAUL
    ApplyMovement LOCALID_PAUL, AcuityLakefront_Movement_PaulArrive
    ApplyMovement LOCALID_PLAYER, AcuityLakefront_Movement_PlayerFacePaul
    WaitMovement
    Common_SetRivalBGM
    BufferPlayerName 0
    Message AcuityLakefront_Text_PaulNotice
    WaitButton
    CloseMessage
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    CallIfEq VAR_0x8004, 311, AcuityLakefront_PaulStepEast
    ApplyMovement LOCALID_PAUL, AcuityLakefront_Movement_PaulWalkSouth
    WaitMovement
    Message AcuityLakefront_Text_PaulPreBattle
    WaitButton
    CloseMessage
    StartTrainerBattle TRAINER_PAUL_ACUITY_LAKEFRONT
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, AcuityLakefront_PaulBlackOut
    BufferPlayerName 0
    Message AcuityLakefront_Text_PaulAfterBattle
    WaitButton
    CloseMessage
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    CallIfEq VAR_0x8004, 311, AcuityLakefront_PaulStepWest
    ApplyMovement LOCALID_PAUL, AcuityLakefront_Movement_PaulWalkNorth
    WaitMovement
    RemoveObject LOCALID_PAUL
    SetFlag FLAG_DEFEATED_PAUL_ACUITY_LAKEFRONT
    Common_FadeToDefaultMusic2
    ReleaseAll
    End

AcuityLakefront_PaulStepEast:
    ApplyMovement LOCALID_PAUL, AcuityLakefront_Movement_PaulStepEast
    Return

AcuityLakefront_PaulStepWest:
    ApplyMovement LOCALID_PAUL, AcuityLakefront_Movement_PaulStepWest
    Return

AcuityLakefront_PaulBlackOut:
    SetFlag FLAG_HIDE_ACUITY_LAKEFRONT_PAUL
    BlackOutFromBattle
    ReleaseAll
    End

AcuityLakefront_PaulIgnore:
    End

    .balign 4, 0
AcuityLakefront_Movement_PaulArrive:
    WalkNormalSouth 4
    EmoteExclamationMark
    Delay8 2
    EndMovement

    .balign 4, 0
AcuityLakefront_Movement_PlayerFacePaul:
    WalkOnSpotNormalNorth
    EndMovement

    .balign 4, 0
AcuityLakefront_Movement_PaulStepEast:
    WalkNormalEast
    EndMovement

    .balign 4, 0
AcuityLakefront_Movement_PaulStepWest:
    WalkNormalWest
    EndMovement

    .balign 4, 0
AcuityLakefront_Movement_PaulWalkSouth:
    WalkNormalSouth 5
    EndMovement

    .balign 4, 0
AcuityLakefront_Movement_PaulWalkNorth:
    WalkNormalNorth 6
    EndMovement

    .balign 4, 0
