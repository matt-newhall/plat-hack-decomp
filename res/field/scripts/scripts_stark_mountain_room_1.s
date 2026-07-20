#include "macros/scrcmd.inc"
#include "res/text/bank/stark_mountain_room_1.h"
#include "res/field/events/events_stark_mountain_room_1.h"


    ScriptEntry StarkMountainOutside_OnTransition
    ScriptEntry StarkMountainRoom1_OnFrameGruntAmbush
    ScriptEntryEnd

StarkMountainOutside_OnTransition:
    SetFlag FLAG_FIRST_ARRIVAL_STARK_MOUNTAIN_INTERIOR
    SetFlag FLAG_HIDE_ROUTE_227_BUCK
    End

StarkMountainRoom1_OnFrameGruntAmbush:
    LockAll
    ApplyMovement LOCALID_GRUNT_M_1, StarkMountainRoom1_Movement_GruntWalkSouth
    ApplyMovement LOCALID_GRUNT_M_2, StarkMountainRoom1_Movement_GruntWalkSouth
    WaitMovement
    Message StarkMountainRoom1_Text_NobodyFollowsUsUp
    CloseMessage
    CheckHasTwoAliveMons VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, StarkMountainRoom1_OnlyOnePokemon
    StartTrainerBattle TRAINER_GALACTIC_GRUNT_STARK_MOUNTAIN_1, TRAINER_GALACTIC_GRUNT_STARK_MOUNTAIN_2
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, StarkMountainRoom1_LostBattle
    Message StarkMountainRoom1_Text_CharonWillHaveOurHeads
    CloseMessage
    ApplyMovement LOCALID_PLAYER, StarkMountainRoom1_Movement_PlayerMoveAside
    WaitMovement
    ApplyMovement LOCALID_GRUNT_M_1, StarkMountainRoom1_Movement_GruntM1Flee
    WaitMovement
    PlaySE SEQ_SE_DP_KAIDAN2
    WaitSE SEQ_SE_DP_KAIDAN2
    ApplyMovement LOCALID_GRUNT_M_2, StarkMountainRoom1_Movement_GruntM2WalkOnSpotWest
    WaitMovement
    Message StarkMountainRoom1_Text_YouDidntSeeUs
    CloseMessage
    ApplyMovement LOCALID_GRUNT_M_2, StarkMountainRoom1_Movement_GruntM2Flee
    WaitMovement
    PlaySE SEQ_SE_DP_KAIDAN2
    WaitSE SEQ_SE_DP_KAIDAN2
    RemoveObject LOCALID_GRUNT_M_1
    RemoveObject LOCALID_GRUNT_M_2
    SetFlag FLAG_HIDE_STARK_MOUNTAIN_ROOM_1_TEAM_GALACTIC
    SetVar VAR_STARK_MOUNTAIN_ROOM_1_STATE, 1
    ReleaseAll
    End

StarkMountainRoom1_OnlyOnePokemon:
    Message StarkMountainRoom1_Text_OnlyOnePokemon
    CloseMessage
    ApplyMovement LOCALID_GRUNT_M_1, StarkMountainRoom1_Movement_GruntWalkBack
    ApplyMovement LOCALID_GRUNT_M_2, StarkMountainRoom1_Movement_GruntWalkBack
    WaitMovement
    ReleaseAll
    End

StarkMountainRoom1_LostBattle:
    BlackOutFromBattle
    ReleaseAll
    End

    .balign 4, 0
StarkMountainRoom1_Movement_GruntWalkSouth:
    WalkNormalSouth
    EndMovement

    .balign 4, 0
StarkMountainRoom1_Movement_GruntWalkBack:
    WalkNormalNorth
    WalkOnSpotNormalSouth
    EndMovement

    .balign 4, 0
StarkMountainRoom1_Movement_PlayerMoveAside:
    Delay8 2
    WalkNormalWest
    WalkOnSpotNormalEast
    EndMovement

    .balign 4, 0
StarkMountainRoom1_Movement_GruntM1Flee:
    WalkNormalSouth 2
    SetInvisible
    EndMovement

    .balign 4, 0
StarkMountainRoom1_Movement_GruntM2WalkOnSpotWest:
    WalkOnSpotNormalWest
    EndMovement

    .balign 4, 0
StarkMountainRoom1_Movement_GruntM2Flee:
    WalkNormalWest
    WalkNormalSouth 2
    SetInvisible
    EndMovement
