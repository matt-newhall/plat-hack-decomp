#include "macros/scrcmd.inc"
#include "res/text/bank/route_228.h"
#include "res/field/events/events_route_228.h"


    ScriptEntry Route228_ArrowSignpostRt226
    ScriptEntry Route228_ArrowSignpostRt229
    ScriptEntry Route228_OnTransition
    ScriptEntry Route228_OnLoad
    ScriptEntry Route228_Argenta
    ScriptEntryEnd

Route228_OnTransition:
    CallIfNe VAR_ROCK_PEAK_RUINS_STATE, RUINS_STATE_CAUGHT_REGI, Route228_ResetRockPeakRuinsState
    GoToIfUnset FLAG_REGIS_UNLOCKED, Route228_RemoveWarpRockPeakRuinsWithRegirock
    GoTo Route228_RemoveWarpRockPeakRuinsWithoutRegirock
    End

Route228_ResetRockPeakRuinsState:
    SetVar VAR_ROCK_PEAK_RUINS_STATE, 0
    Return

Route228_OnLoad:
    GoToIfUnset FLAG_REGIS_UNLOCKED, Route228_RemoveWarpRockPeakRuinsWithRegirock
    GoTo Route228_RemoveWarpRockPeakRuinsWithoutRegirock
    End

Route228_RemoveWarpRockPeakRuinsWithRegirock:
    SetWarpEventPos 5, 783, 339
    End

Route228_RemoveWarpRockPeakRuinsWithoutRegirock:
    SetWarpEventPos 4, 783, 339
    End

Route228_ArrowSignpostRt226:
    ShowArrowSign Route228_Text_SignRt228Rt226
    End

Route228_ArrowSignpostRt229:
    ShowArrowSign Route228_Text_SignRt228Rt229
    End

Route228_Argenta:
    LockAll
    ApplyMovement LOCALID_HALL_MATRON_ARGENTA, Route228_Movement_ArgentaNoticePlayer
    WaitMovement
    ApplyMovement LOCALID_HALL_MATRON_ARGENTA, Route228_Movement_ArgentaApproach
    ApplyMovement LOCALID_PLAYER, Route228_Movement_PlayerFaceEast
    WaitMovement
    CheckHasTwoAliveMons VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, Route228_ArgentaNotReady
    Message Route228_Text_ArgentaPrebattle
    WaitButton
    CloseMessage
    StartTrainerBattle TRAINER_HALL_MATRON_ARGENTA_ROUTE_228
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, Route228_ArgentaBlackOut
    Message Route228_Text_ArgentaDefeated
    WaitButton
    CloseMessage
    SetVar VAR_0x8004, ITEM_ABILITY_CAPSULE
    SetVar VAR_0x8005, 2
    Common_GiveItemQuantity
    Message Route228_Text_ArgentaFarewell
    WaitButton
    CloseMessage
    ApplyMovement LOCALID_HALL_MATRON_ARGENTA, Route228_Movement_ArgentaLeaveSouth
    WaitMovement
    RemoveObject LOCALID_HALL_MATRON_ARGENTA
    SetFlag FLAG_HIDE_ARGENTA_ROUTE_228
    SetVar VAR_ROUTE_228_ARGENTA_STATE, 1
    ReleaseAll
    End

Route228_ArgentaBlackOut:
    BlackOutFromBattle
    ReleaseAll
    End

Route228_ArgentaNotReady:
    Message Route228_Text_ArgentaNotReady
    WaitButton
    CloseMessage
    ApplyMovement LOCALID_PLAYER, Route228_Movement_PlayerWalkWest
    WaitMovement
    PlaySE SEQ_SE_DP_KAIDAN2
    FadeScreenOut
    WaitFadeScreen
    Warp MAP_HEADER_ROUTE_228_GATE_TO_ROUTE_226, 0, 10, 7, DIR_WEST
    FadeScreenIn
    WaitFadeScreen
    ReleaseAll
    End

    .balign 4, 0
Route228_Movement_ArgentaNoticePlayer:
    FaceWest
    EmoteExclamationMark
    EndMovement

    .balign 4, 0
Route228_Movement_ArgentaApproach:
    WalkNormalWest 4
    EndMovement

    .balign 4, 0
Route228_Movement_ArgentaLeaveSouth:
    WalkNormalSouth 8
    EndMovement

    .balign 4, 0
Route228_Movement_PlayerFaceEast:
    FaceEast
    EndMovement

    .balign 4, 0
Route228_Movement_PlayerWalkWest:
    FaceWest
    EndMovement

    .balign 4, 0
