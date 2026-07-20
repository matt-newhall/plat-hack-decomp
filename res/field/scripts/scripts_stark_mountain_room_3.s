#include "macros/scrcmd.inc"
#include "res/text/bank/stark_mountain_room_3.h"
#include "res/field/events/events_stark_mountain_room_3.h"


    ScriptEntry StarkMountainRoom3_OnTransition
    ScriptEntry StarkMountainRoom3_OnLoad
    ScriptEntry StarkMountainRoom3_Unused
    ScriptEntry StarkMountainRoom3_Heatran
    ScriptEntry StarkMountainRoom3_OnFrameCharon
    ScriptEntryEnd

StarkMountainRoom3_OnTransition:
    SetVar VAR_MAP_LOCAL_0, VAR_STARK_MOUNTAIN_ROOM_3_STATE
    CallIfGe VAR_STARK_MOUNTAIN_ROOM_3_STATE, 1, StarkMountainRoom3_HideBuck
    Call StarkMountainRoom3_TryHideHeatran
    End

StarkMountainRoom3_HideBuck:
    SetFlag FLAG_HIDE_STARK_MOUNTAIN_ROOM_3_BUCK
    Return

StarkMountainRoom3_TryHideHeatran:
    GoToIfSet FLAG_CAUGHT_HEATRAN, StarkMountainRoom3_HideHeatran
    CheckGameCompleted VAR_MAP_LOCAL_0
    GoToIfEq VAR_MAP_LOCAL_0, FALSE, StarkMountainRoom3_HideHeatran
    GetNationalDexEnabled VAR_MAP_LOCAL_0
    GoToIfEq VAR_MAP_LOCAL_0, FALSE, StarkMountainRoom3_HideHeatran
    GoToIfUnset FLAG_CAUGHT_MESPRIT, StarkMountainRoom3_HideHeatran
    GoToIfNe VAR_STARK_MOUNTAIN_ROOM_3_STATE, 1, StarkMountainRoom3_HideHeatran
    ClearFlag FLAG_HIDE_STARK_MOUNTAIN_ROOM_3_HEATRAN
    Return

StarkMountainRoom3_HideHeatran:
    SetFlag FLAG_HIDE_STARK_MOUNTAIN_ROOM_3_HEATRAN
    Return

StarkMountainRoom3_OnLoad:
    GoToIfSet FLAG_MAP_LOCAL, StarkMountainRoom3_RemoveHeatran
    End

StarkMountainRoom3_RemoveHeatran:
    SetFlag FLAG_HIDE_STARK_MOUNTAIN_ROOM_3_HEATRAN
    RemoveObject LOCALID_HEATRAN
    ClearFlag FLAG_MAP_LOCAL
    End

StarkMountainRoom3_UnusedMovement:
    WalkNormalWest
    WalkOnSpotNormalEast
    WalkOnSpotNormalSouth
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_BuckWalkOnSpotNorth:
    WalkOnSpotNormalNorth
    EndMovement

StarkMountainRoom3_UnusedMovement2:
    WalkOnSpotNormalNorth
    EndMovement

StarkMountainRoom3_UnusedMovement3:
    Delay8
    WalkNormalSouth 9
    EndMovement

StarkMountainRoom3_Unused:
    BufferPlayerName 1
    NPCMessage StarkMountainRoom3_Text_ThatWasWicked
    End

StarkMountainRoom3_Heatran:
    LockAll
    PlaySE SEQ_SE_CONFIRM
    WaitSE SEQ_SE_CONFIRM
    CallIfUnset FLAG_BATTLED_STARK_MOUNTAIN_ROOM_3_HEATRAN, StarkMountainRoom3_SetFlagBattledHeatran
    SetVar VAR_STARK_MOUNTAIN_ROOM_3_STATE, 2
    PlayCry SPECIES_HEATRAN
    Message StarkMountainRoom3_Text_HeatranCry
    CloseMessage
    SetFlag FLAG_MAP_LOCAL
    StartLegendaryBattle SPECIES_HEATRAN, 50
    ClearFlag FLAG_MAP_LOCAL
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, StarkMountainRoom3_LostBattle
    CheckLostBattle VAR_RESULT
    CallIfEq VAR_RESULT, FALSE, StarkMountainRoom3_UnlockVSSeekerLvl5
    CheckDidNotCapture VAR_RESULT
    GoToIfEq VAR_RESULT, TRUE, StarkMountainRoom3_HeatranDisappeared
    GoTo StarkMountainRoom3_CaughtHeatran
    End

StarkMountainRoom3_CaughtHeatran:
    SetFlag FLAG_CAUGHT_HEATRAN
    ReleaseAll
    End

StarkMountainRoom3_HeatranDisappeared:
    Message StarkMountainRoom3_Text_HeatranDisappeared
    WaitButton
    CloseMessage
    ReleaseAll
    End

StarkMountainRoom3_LostBattle:
    SetVar VAR_STARK_MOUNTAIN_ROOM_3_STATE, 1
    BlackOutFromBattle
    ReleaseAll
    End

StarkMountainRoom3_SetFlagBattledHeatran:
    SetFlag FLAG_BATTLED_STARK_MOUNTAIN_ROOM_3_HEATRAN
    Return

StarkMountainRoom3_UnlockVSSeekerLvl5:
    SetFlag FLAG_UNLOCKED_VS_SEEKER_LVL_5
    Return

StarkMountainRoom3_UnusedMovement4:
    WalkNormalNorth 6
    EndMovement

StarkMountainRoom3_UnusedMovement5:
    WalkNormalSouth 6
    EndMovement

StarkMountainRoom3_UnusedMovement6:
    Delay8 4
    WalkOnSpotNormalSouth
    EndMovement

StarkMountainRoom3_OnFrameCharon:
    LockAll
    PlaySE SEQ_SE_DP_FW089
    ScrCmd_29F 0
    StopSE SEQ_SE_DP_FW089
    ApplyMovement LOCALID_BUCK, StarkMountainRoom3_Movement_BuckWalkNorth
    ApplyMovement LOCALID_PLAYER, StarkMountainRoom3_Movement_PlayerWalkNorth
    WaitMovement
    ApplyMovement LOCALID_BUCK, StarkMountainRoom3_Movement_BuckWalkOnSpotNorth
    WaitMovement
    Message StarkMountainRoom3_Text_WhatsGoingOnHere
    CloseMessage
    Message StarkMountainRoom3_Text_MagmaStoneWillBeMine
    WaitButton
    CloseMessage
    Message StarkMountainRoom3_Text_CharonRedChain
    WaitButton
    CloseMessage
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    AddFreeCamera VAR_0x8004, VAR_0x8005
    ApplyFreeCameraMovement StarkMountainRoom3_Movement_CameraMoveNorth
    WaitMovement
    ApplyMovement LOCALID_CHARON, StarkMountainRoom3_Movement_CharonApproachStone
    WaitMovement
    Message StarkMountainRoom3_Text_CharonUseMagmaStone
    WaitButton
    CloseMessage
    ReleaseObject LOCALID_MAGMA_STONE
    FlickerObject LOCALID_MAGMA_STONE, 6, 8
    ShakeObject LOCALID_MAGMA_STONE, 8, 90, 1, 0
    LockObject LOCALID_MAGMA_STONE
    PlaySE SEQ_SE_DP_FW089
    ScrCmd_29F 0
    StopSE SEQ_SE_DP_FW089
    FadeScreenOut FADE_SCREEN_SPEED_SLOW, COLOR_WHITE
    WaitFadeScreen
    RemoveObject LOCALID_MAGMA_STONE
    ClearFlag FLAG_HIDE_STARK_MOUNTAIN_ROOM_3_HEATRAN
    AddObject LOCALID_HEATRAN
    FadeScreenIn FADE_SCREEN_SPEED_SLOW, COLOR_WHITE
    WaitFadeScreen
    PlayCry SPECIES_HEATRAN
    ReleaseObject LOCALID_HEATRAN
    ShakeObject LOCALID_HEATRAN, 8, 90, 3, 0
    LockObject LOCALID_HEATRAN
    Message StarkMountainRoom3_Text_HeatranAwakens
    WaitButton
    CloseMessage
    Message StarkMountainRoom3_Text_CharonMasterBall
    WaitButton
    CloseMessage
    PlaySE SEQ_SE_DP_NAGERU
    WaitSE SEQ_SE_DP_NAGERU
    FadeScreenOut FADE_SCREEN_SPEED_FAST, COLOR_WHITE
    WaitFadeScreen
    RemoveObject LOCALID_HEATRAN
    SetFlag FLAG_HIDE_STARK_MOUNTAIN_ROOM_3_HEATRAN
    FadeScreenIn FADE_SCREEN_SPEED_FAST, COLOR_WHITE
    WaitFadeScreen
    PlaySE SEQ_SE_DP_BOWA
    WaitSE SEQ_SE_DP_BOWA
    Message StarkMountainRoom3_Text_CharonCaughtHeatran
    WaitButton
    CloseMessage
    ApplyMovement LOCALID_CHARON, StarkMountainRoom3_Movement_CharonWalkSouth
    ApplyFreeCameraMovement StarkMountainRoom3_Movement_CameraMoveSouth
    WaitMovement
    RestoreCamera
    ApplyMovement LOCALID_GRUNT_M_1, StarkMountainRoom3_Movement_GruntM1HoldBuck
    ApplyMovement LOCALID_GRUNT_M_2, StarkMountainRoom3_Movement_GruntM2HoldBuck
    WaitMovement
    Message StarkMountainRoom3_Text_CharonChallenge
    WaitButton
    CloseMessage
    Message StarkMountainRoom3_Text_BuckHealsYou
    WaitButton
    CloseMessage
    HealParty
    CheckHasTwoAliveMons VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, StarkMountainRoom3_CharonNotWorthIt
    StartTrainerBattle TRAINER_CHARON_STARK_MOUNTAIN
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, StarkMountainRoom3_CharonLostBattle
    GoTo StarkMountainRoom3_CharonDefeated
    End

StarkMountainRoom3_CharonLostBattle:
    BlackOutFromBattle
    ReleaseAll
    End

StarkMountainRoom3_CharonNotWorthIt:
    Message StarkMountainRoom3_Text_CharonNotWorthIt
    WaitButton
    CloseMessage
    ReleaseAll
    End

StarkMountainRoom3_CharonDefeated:
    Message StarkMountainRoom3_Text_CharonDefeated
    WaitButton
    CloseMessage
    Message StarkMountainRoom3_Text_CharonEscapes
    WaitButton
    CloseMessage
    FadeScreenOut
    WaitFadeScreen
    RemoveObject LOCALID_CHARON
    RemoveObject LOCALID_GRUNT_M_1
    RemoveObject LOCALID_GRUNT_M_2
    SetFlag FLAG_HIDE_STARK_MOUNTAIN_ROOM_3_TEAM_GALACTIC
    FadeScreenIn
    WaitFadeScreen
    ApplyMovement LOCALID_BUCK, StarkMountainRoom3_Movement_BuckWalkOnSpotNorth
    WaitMovement
    Message StarkMountainRoom3_Text_BuckAftermath
    WaitButton
    CloseMessage
    ApplyMovement LOCALID_BUCK, StarkMountainRoom3_Movement_BuckFaceEast
    ApplyMovement LOCALID_PLAYER, StarkMountainRoom3_Movement_PlayerFaceWest
    WaitMovement
    BufferPlayerName 0
    Message StarkMountainRoom3_Text_BuckTeleportOut
    WaitButton
    CloseMessage
    SetVar VAR_STARK_MOUNTAIN_ROOM_3_STATE, 1
    SetVar VAR_STARK_MOUNTAIN_OUTSIDE_STATE, 2
    ClearFlag FLAG_HIDE_STARK_MOUNTAIN_OUTSIDE_BUCK
    FadeScreenOut
    WaitFadeScreen
    Warp MAP_HEADER_STARK_MOUNTAIN_OUTSIDE, 0, 751, 233, DIR_WEST
    FadeScreenIn
    WaitFadeScreen
    End

    .balign 4, 0
StarkMountainRoom3_Movement_CharonApproachStone:
    WalkNormalNorth 2
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_PlayerWalkNorth:
    WalkNormalNorth 3
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_PlayerWatchGruntsLeave:
    Delay8 2
    WalkOnSpotNormalEast
    Delay8 2
    WalkOnSpotNormalNorth
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_BuckWalkNorth:
    Delay8
    WalkNormalNorth 2
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_CameraMoveNorth:
    WalkNormalNorth 4
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_CameraMoveSouth:
    Delay8 2
    WalkNormalSouth 4
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_BuckFaceEast:
    WalkOnSpotNormalEast
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_PlayerFaceWest:
    WalkOnSpotNormalWest
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_CharonGrabMagmaStone:
    WalkNormalNorth 2
    Delay8 2
    WalkOnSpotNormalSouth
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_CharonLookAround:
    WalkOnSpotFastWest
    Delay8
    WalkOnSpotFastEast
    Delay8
    WalkOnSpotFastSouth
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_CharonWalkOnSpotSouth:
    WalkOnSpotNormalSouth
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_CharonWalkSouth:
    Delay8 2
    WalkNormalSouth 3
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_CharonLeave:
    WalkNormalSouth
    WalkNormalEast
    WalkNormalSouth 3
    WalkNormalWest
    WalkNormalSouth
    SetInvisible
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_GruntM1WatchLookerWalkToCharon:
    Delay8 3
    Delay4
    WalkOnSpotNormalNorth
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_GruntM2WatchLookerWalkToCharon:
    Delay8
    WalkOnSpotNormalSouth
    Delay8
    WalkOnSpotNormalWest
    Delay4
    WalkOnSpotNormalNorth
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_GruntM1WalkOnSpotEast:
    WalkOnSpotNormalEast
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_GruntM2WalkOnSpotEast:
    WalkOnSpotNormalEast
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_GruntM1FaceGruntM2:
    WalkOnSpotNormalEast
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_GruntM2FaceGruntM1:
    WalkOnSpotNormalWest
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_GruntM1HoldBuck:
    WalkNormalWest
    WalkNormalSouth
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_GruntM2HoldBuck:
    WalkNormalSouth
    WalkNormalWest 2
    WalkOnSpotNormalSouth
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_GruntM1WalkOnSpotFastEast:
    WalkOnSpotFastEast 3
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_GruntM2WalkOnSpotFastWest:
    WalkOnSpotFastWest 3
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_GruntM1Leave:
    WalkFastEast 2
    WalkFastSouth 5
    WalkFastWest
    WalkFastSouth
    SetInvisible
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_GruntM2Leave:
    WalkFastSouth 5
    WalkFastWest
    WalkFastSouth
    SetInvisible
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_CroagunkStealMagmaStone:
    WalkFastWest 2
    WalkFastNorth 3
    WalkOnSpotNormalNorth
    WalkFastSouth 3
    WalkFastEast 2
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_LookerWalkToCharon:
    WalkNormalWest 3
    WalkNormalNorth 3
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_LookerPushCharonSouth:
    WalkNormalWest
    WalkNormalNorth
    WalkNormalEast
    WalkNormalSouth 2
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_Policeman1Enter:
    WalkNormalNorth 2
    WalkNormalEast
    WalkNormalNorth 3
    WalkNormalWest 2
    WalkOnSpotNormalNorth
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_Policeman1LeaveWithCharon:
    WalkNormalEast
    WalkNormalSouth
    WalkNormalEast
    WalkNormalSouth 3
    WalkNormalWest
    WalkNormalSouth 2
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_Policeman2Enter:
    WalkNormalEast
    WalkNormalNorth 4
    WalkNormalWest
    WalkOnSpotNormalNorth
    EndMovement

    .balign 4, 0
StarkMountainRoom3_Movement_Policeman2LeaveWithCharon:
    WalkNormalEast
    WalkNormalSouth 3
    WalkNormalWest
    WalkNormalSouth 2
    SetInvisible
    EndMovement
