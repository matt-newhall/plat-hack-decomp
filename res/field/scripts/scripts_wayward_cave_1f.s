#include "macros/scrcmd.inc"
#include "res/text/bank/wayward_cave_1f.h"
#include "res/field/events/events_wayward_cave_1f.h"

    ScriptEntry WaywardCave1F_OnTransition
    ScriptEntry WaywardCave1F_Mira
    ScriptEntry WaywardCave1F_Roy
    ScriptEntryEnd

WaywardCave1F_OnTransition:
    SetFlag FLAG_FIRST_ARRIVAL_WAYWARD_CAVE
    End

WaywardCave1F_Mira:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message WaywardCave1F_Text_MiraBattle
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_YES, WaywardCave1F_BattleMira
    CloseMessage
    ReleaseAll
    End

WaywardCave1F_BattleMira:
    CloseMessage
    StartTrainerBattle TRAINER_MIRA_WAYWARD_CAVE
    FacePlayer
    LockAll
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, WaywardCave_BlackOutMiraBattle
    Message WaywardCave1F_Text_Congrats
    WaitButton
    CloseMessage
    SetFlag FLAG_SKIRMISH_MIRA_DEFEATED
    SetVar VAR_EXITING_SKIRMISH_ZONE_SUCCESS 1
    FadeScreenOut
    WaitFadeScreen
    Warp MAP_HEADER_ROUTE_206, 0, 310, 609, DIR_NORTH
    FadeScreenIn
    WaitFadeScreen
    ReleaseAll
    End

WaywardCave_BlackOutMiraBattle:
    BlackOutFromBattle
    ReleaseAll
    End

WaywardCave1F_Roy:
    Message WaywardCave1F_RoySureYouWannaLeave
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_YES, WaywardCave1F_GiveUp
    CloseMessage
    End

WaywardCave1F_GiveUp:
    SetVar VAR_EXITING_SKIRMISH_ZONE_SUCCESS 1
    FadeScreenOut
    WaitFadeScreen
    Warp MAP_HEADER_ROUTE_206, 0, 310, 609, DIR_NORTH
    FadeScreenIn
    WaitFadeScreen
    End

    .balign 4, 0
WaywardCave1F_Movement_PlayerWalkOnSpotEast:
    WalkOnSpotNormalEast
    EndMovement

    .balign 4, 0
WaywardCave1F_Movement_PlayerWalkOnSpotNorth:
    WalkOnSpotNormalNorth
    EndMovement

    .balign 4, 0
WaywardCave1F_Movement_PlayerWalkNorthOnSpotSouth:
    WalkNormalNorth
    WalkOnSpotNormalSouth
    EndMovement

    .balign 4, 0
WaywardCave1F_Movement_PlayerWalkEastOnSpotWest:
    WalkNormalEast
    WalkOnSpotNormalWest
    EndMovement

WaywardCave1F_UnusedMovement:
    Delay8 5
    WalkNormalWest
    EndMovement

WaywardCave1F_UnusedMovement2:
    Delay8 5
    WalkNormalNorth
    WalkOnSpotNormalWest
    EndMovement

    .balign 4, 0
WaywardCave1F_Movement_MiraWalkOnSpotWestExclamationMark:
    WalkOnSpotNormalWest
    EmoteExclamationMark
    EndMovement

    .balign 4, 0
WaywardCave1F_Movement_MiraWalkOnSpotSouthExclamationMark:
    WalkOnSpotNormalSouth
    EmoteExclamationMark
    EndMovement

    .balign 4, 0
WaywardCave1F_Movement_MiraWalkWestLeave:
    Delay8 3
    WalkNormalWest
    WalkOnSpotNormalSouth
    EndMovement

    .balign 4, 0
WaywardCave1F_Movement_MiraWalkSouthLeave:
    Delay8 3
    WalkNormalSouth
    WalkOnSpotNormalSouth
    EndMovement
