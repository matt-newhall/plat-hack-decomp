#include "macros/scrcmd.inc"
#include "res/field/events/events_spring_path.h"


    ScriptEntry SpringPath_Psyduck
    ScriptEntryEnd

SpringPath_Psyduck:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    CheckItem ITEM_SECRETPOTION, 1, VAR_RESULT
    GoToIfEq VAR_RESULT, TRUE, SpringPath_UseSecretPotion
    ReleaseAll
    End

SpringPath_UseSecretPotion:
    PlayCry SPECIES_PSYDUCK
    WaitCry
    ApplyMovement LOCALID_PSYDUCK_3, SpringPath_Movement_PsyduckExclamationMark
    ApplyMovement LOCALID_PSYDUCK_4, SpringPath_Movement_PsyduckExclamationMark
    ApplyMovement LOCALID_PSYDUCK_1, SpringPath_Movement_PsyduckExclamationMark
    ApplyMovement LOCALID_PSYDUCK_2, SpringPath_Movement_PsyduckExclamationMark
    WaitMovement
    ApplyMovement LOCALID_PSYDUCK_3, SpringPath_Movement_PsyduckConfusedLeave
    ApplyMovement LOCALID_PSYDUCK_4, SpringPath_Movement_PsyduckLeave
    ApplyMovement LOCALID_PSYDUCK_1, SpringPath_Movement_Psyduck1Leave
    ApplyMovement LOCALID_PSYDUCK_2, SpringPath_Movement_PsyduckLeave
    WaitMovement
    RemoveObject LOCALID_PSYDUCK_3
    RemoveObject LOCALID_PSYDUCK_4
    RemoveObject LOCALID_PSYDUCK_1
    RemoveObject LOCALID_PSYDUCK_2
    SetFlag FLAG_HIDE_SPRING_PATH_PSYDUCK
    ReleaseAll
    End

    .balign 4, 0
SpringPath_Movement_PsyduckExclamationMark:
    EmoteExclamationMark
    Delay8 4
    EndMovement

    .balign 4, 0
SpringPath_Movement_PsyduckConfusedLeave:
    Delay8
    WalkOnSpotNormalSouth
    WalkOnSpotNormalWest
    WalkOnSpotNormalNorth
    WalkOnSpotNormalEast
    WalkOnSpotNormalSouth
    EmoteExclamationMark
    Delay8
    WalkFastEast 8
    EndMovement

    .balign 4, 0
SpringPath_Movement_Psyduck1Leave:
    WalkNormalSouth
    WalkNormalEast 8
    EndMovement

    .balign 4, 0
SpringPath_Movement_PsyduckLeave:
    WalkNormalEast 8
    EndMovement

    .balign 4, 0
