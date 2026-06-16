#include "macros/scrcmd.inc"
#include "res/field/events/events_victory_road_1f.h"
#include "res/text/bank/victory_road_1f.h"


    ScriptEntry VictoryRoad_OnTransition
    ScriptEntry VictoryRoad_Collector
    ScriptEntry VictoryRoad_LeagueCheck
    ScriptEntry VictoryRoad_LeagueCheckTrigger
    ScriptEntryEnd

VictoryRoad_OnTransition:
    SetFlag FLAG_FIRST_ARRIVAL_VICTORY_ROAD
    GoToIfEq VAR_VICTORY_ROAD_LEAGUECHECK_STATE, 1, VictoryRoad_LeagueCheckMovedAside
VictoryRoad_OnTransitionCollector:
    GoToIfUnset FLAG_GAME_COMPLETED, VictoryRoad_DontHideCollector
    GetNationalDexEnabled VAR_MAP_LOCAL_0
    GoToIfEq VAR_MAP_LOCAL_0, FALSE, VictoryRoad_DontHideCollector
    SetFlag FLAG_HIDE_VICTORY_ROAD_1F_COLLECTOR
VictoryRoad_DontHideCollector:
    End

VictoryRoad_LeagueCheckMovedAside:
    SetObjectEventPos LOCALID_LEAGUECHECK, 40, 16
    SetObjectEventDir LOCALID_LEAGUECHECK, DIR_WEST
    GoTo VictoryRoad_OnTransitionCollector

VictoryRoad_Collector:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet FLAG_GAME_COMPLETED, VictoryRoad1F_YoullMeetManyPokemon
    Message VictoryRoad1F_Text_AimForPokemonLeague
    GoTo VictoryRoad1F_CollectorEnd
    End

VictoryRoad1F_YoullMeetManyPokemon:
    Message VictoryRoad1F_Text_YoullMeetManyPokemon
    GoTo VictoryRoad1F_CollectorEnd
    End

VictoryRoad1F_CollectorEnd:
    WaitButton
    CloseMessage
    ReleaseAll
    End

VictoryRoad_LeagueCheck:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message VictoryRoad1F_Text_LeagueCheckTalk
    WaitButton
    CloseMessage
    ReleaseAll
    End

VictoryRoad_LeagueCheckTrigger:
    LockAll
    GoToIfSet FLAG_UNLOCK_POKEMON_LEAGUE, VictoryRoad_LeagueCheckAllow
    ApplyMovement LOCALID_LEAGUECHECK, VictoryRoad_Movement_Exclaim
    WaitMovement
    Message VictoryRoad1F_Text_LeagueCheckBlock
    WaitButton
    CloseMessage
    ApplyMovement LOCALID_PLAYER, VictoryRoad_Movement_PlayerStepBack
    WaitMovement
    ReleaseAll
    End

VictoryRoad_LeagueCheckAllow:
    ApplyMovement LOCALID_LEAGUECHECK, VictoryRoad_Movement_Exclaim
    WaitMovement
    Message VictoryRoad1F_Text_LeagueCheckAllow
    WaitButton
    CloseMessage
    ApplyMovement LOCALID_LEAGUECHECK, VictoryRoad_Movement_LeagueCheckStepAside
    WaitMovement
    SetVar VAR_VICTORY_ROAD_LEAGUECHECK_STATE, 1
    ReleaseAll
    End

    .balign 4, 0
VictoryRoad_Movement_Exclaim:
    EmoteExclamationMark
    EndMovement

    .balign 4, 0
VictoryRoad_Movement_PlayerStepBack:
    WalkNormalSouth
    EndMovement

    .balign 4, 0
VictoryRoad_Movement_LeagueCheckStepAside:
    WalkNormalNorth
    WalkNormalEast 2
    FaceWest
    EndMovement

    .balign 4, 0
