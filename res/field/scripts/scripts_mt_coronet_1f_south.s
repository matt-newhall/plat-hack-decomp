#include "macros/scrcmd.inc"
#include "res/text/bank/mt_coronet_1f_south.h"
#include "res/field/events/events_mt_coronet_1f_south.h"


    ScriptEntry MtCoronet1FSouth_TriggerCyrus
    ScriptEntryEnd

MtCoronet1FSouth_TriggerCyrus:
    LockAll
    ApplyMovement LOCALID_PLAYER, MtCoronet1FSouth_Movement_PlayerWatchCyrusWalkToPlayer
    ApplyMovement LOCALID_CYRUS, MtCoronet1FSouth_Movement_CyrusWalkToPlayer
    ApplyMovement LOCALID_SATURN, MtCoronet1FSouth_Movement_CyrusWalkToPlayer
    WaitMovement
    Message MtCoronet1FSouth_Text_AccordingToOneTheoryMtCoronetIsWhereTheSinnohRegionBegan
    CloseMessage
    ApplyMovement LOCALID_CYRUS, MtCoronet1FSouth_Movement_CyrusWalkOnSpotNorth
    ApplyMovement LOCALID_PLAYER, MtCoronet1FSouth_Movement_PlayerWalkOnSpotNorthEast
    WaitMovement
    Message MtCoronet1FSouth_Text_InANewlyCreatedWorld
    ApplyMovement LOCALID_CYRUS, MtCoronet1FSouth_Movement_CyrusWalkOnSpotWest
    WaitMovement
    Message MtCoronet1FSouth_Text_ButWhatBecameOfThatWorld
    CloseMessage
    ApplyMovement LOCALID_SATURN, MtCoronet1FSouth_Movement_SaturnLookDown
    WaitMovement
    Message MtCoronet1FSouth_Text_SaturnAgrees
    CloseMessage
    ApplyMovement LOCALID_SATURN, MtCoronet1FSouth_Movement_SaturnLookWest
    WaitMovement
    ApplyMovement LOCALID_PLAYER, MtCoronet1FSouth_Movement_PlayerMoveAsideAndWatchCyrusLeave
    ApplyMovement LOCALID_CYRUS, MtCoronet1FSouth_Movement_CyrusLeave
    ApplyMovement LOCALID_SATURN, MtCoronet1FSouth_Movement_SaturnLeave
    WaitMovement
    RemoveObject LOCALID_CYRUS
    ApplyMovement LOCALID_SATURN, MtCoronet1FSouth_Movement_SaturnReturn
    ApplyMovement LOCALID_PLAYER, MtCoronet1FSouth_Movement_PlayerStepBackNorth
    WaitMovement
    Message MtCoronet1FSouth_Text_SaturnSpotsYou
    CloseMessage
    StartTrainerBattle TRAINER_COMMANDER_SATURN_MT_CORONET
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, MtCoronet1FSouth_BlackOut
    Message MtCoronet1FSouth_Text_SaturnDefeated
    CloseMessage
    ApplyMovement LOCALID_SATURN, MtCoronet1FSouth_Movement_SaturnLeaveWest
    WaitMovement
    RemoveObject LOCALID_SATURN
    SetVar VAR_MT_CORONET_1F_SOUTH_STATE, 1
    ReleaseAll
    End

MtCoronet1FSouth_BlackOut:
    BlackOutFromBattle
    ReleaseAll
    End

    .balign 4, 0
MtCoronet1FSouth_Movement_CyrusWalkToPlayer:
    WalkNormalSouth 6
    WalkOnSpotNormalWest
    EndMovement

    .balign 4, 0
MtCoronet1FSouth_Movement_CyrusWalkOnSpotNorth:
    WalkOnSpotNormalNorth
    EndMovement

    .balign 4, 0
MtCoronet1FSouth_Movement_CyrusWalkOnSpotWest:
    WalkOnSpotNormalWest
    EndMovement

    .balign 4, 0
MtCoronet1FSouth_Movement_CyrusLeave:
    Delay8 3
    WalkNormalWest 10
    EndMovement

    .balign 4, 0
MtCoronet1FSouth_Movement_SaturnLookDown:
    FaceSouth
    EndMovement

    .balign 4, 0
MtCoronet1FSouth_Movement_SaturnLookWest:
    FaceWest
    EndMovement

    .balign 4, 0
MtCoronet1FSouth_Movement_SaturnLeave:
    Delay8 3
    WalkNormalSouth 1
    WalkNormalWest 10
    EndMovement

    .balign 4, 0
MtCoronet1FSouth_Movement_SaturnReturn:
    WalkNormalEast 8
    EndMovement

    .balign 4, 0
MtCoronet1FSouth_Movement_SaturnLeaveWest:
    WalkNormalWest 10
    EndMovement

    .balign 4, 0
MtCoronet1FSouth_Movement_PlayerStepBackNorth:
    WalkNormalNorth 2
    FaceWest
    EndMovement

    .balign 4, 0
MtCoronet1FSouth_Movement_PlayerWatchCyrusWalkToPlayer:
    WalkOnSpotNormalNorth
    Delay8 4
    WalkOnSpotNormalEast
    EndMovement

    .balign 4, 0
MtCoronet1FSouth_Movement_PlayerWalkOnSpotNorthEast:
    Delay8 3
    WalkOnSpotNormalNorth
    Delay8
    WalkOnSpotNormalEast
    EndMovement

    .balign 4, 0
MtCoronet1FSouth_Movement_PlayerMoveAsideAndWatchCyrusLeave:
    WalkNormalSouth 2
    WalkOnSpotNormalNorth
    Delay8 2
    WalkOnSpotNormalWest
    EndMovement
