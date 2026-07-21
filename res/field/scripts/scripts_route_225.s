#include "macros/scrcmd.inc"
#include "res/text/bank/route_225.h"
#include "res/field/events/events_route_225.h"


    ScriptEntry Route225_ArrowSignpostFightArea
    ScriptEntry Route225_ArrowSignpostSurvivalArea
    ScriptEntry Route225_DahliaApproach
    ScriptEntryEnd

Route225_ArrowSignpostFightArea:
    ShowArrowSign Route225_Text_SignRt225FightArea
    End

Route225_ArrowSignpostSurvivalArea:
    ShowArrowSign Route225_Text_SignRt225SurvivalArea
    End

Route225_DahliaApproach:
    GoToIfSet FLAG_HIDE_DAHLIA_ROUTE_225, Route225_DahliaApproachEnd
    LockAll
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    ApplyMovement LOCALID_ARCADE_STAR_DAHLIA, Route225_Movement_DahliaNoticePlayer
    WaitMovement
    CallIfEq VAR_0x8004, 614, Route225_PlayerApproachFrom614
    CallIfEq VAR_0x8004, 615, Route225_PlayerApproachFrom615
    ApplyMovement LOCALID_ARCADE_STAR_DAHLIA, Route225_Movement_DahliaMeet
    WaitMovement
    CheckHasTwoAliveMons VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, Route225_DahliaNotReady
    Message Route225_Text_DahliaChallenge
    WaitButton
    CloseMessage
    StartTrainerBattle TRAINER_ARCADE_STAR_DAHLIA_ROUTE_225
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, Route225_DahliaBlackOut
    Message Route225_Text_DahliaDefeated
    WaitButton
    CloseMessage
    SetVar VAR_0x8004, ITEM_EJECT_BUTTON
    SetVar VAR_0x8005, 2
    Common_GiveItemQuantity
    SetVar VAR_0x8004, ITEM_EJECT_PACK
    SetVar VAR_0x8005, 2
    Common_GiveItemQuantity
    Message Route225_Text_DahliaFarewell
    WaitButton
    CloseMessage
    ApplyMovement LOCALID_ARCADE_STAR_DAHLIA, Route225_Movement_DahliaLeave
    WaitMovement
    PlaySE SEQ_SE_DP_KAIDAN2
    RemoveObject LOCALID_ARCADE_STAR_DAHLIA
    SetFlag FLAG_HIDE_DAHLIA_ROUTE_225
    ReleaseAll
    End

Route225_DahliaNotReady:
    Message Route225_Text_DahliaNotReady
    WaitButton
    CloseMessage
    ApplyMovement LOCALID_ARCADE_STAR_DAHLIA, Route225_Movement_DahliaWalkBack
    WaitMovement
    CallIfEq VAR_0x8004, 614, Route225_ResetPlayerTo614
    CallIfEq VAR_0x8004, 615, Route225_ResetPlayerTo615
    ReleaseAll
    End

Route225_ResetPlayerTo614:
    ApplyMovement LOCALID_PLAYER, Route225_Movement_PlayerBackTo614
    WaitMovement
    Return

Route225_ResetPlayerTo615:
    ApplyMovement LOCALID_PLAYER, Route225_Movement_PlayerBackTo615
    WaitMovement
    Return

Route225_DahliaBlackOut:
    BlackOutFromBattle
    ReleaseAll
    End

Route225_DahliaApproachEnd:
    End

Route225_PlayerApproachFrom614:
    ApplyMovement LOCALID_PLAYER, Route225_Movement_PlayerApproachFrom614
    WaitMovement
    Return

Route225_PlayerApproachFrom615:
    ApplyMovement LOCALID_PLAYER, Route225_Movement_PlayerApproachFrom615
    WaitMovement
    Return

    .balign 4, 0
Route225_Movement_DahliaNoticePlayer:
    WalkNormalWest 6
    EmoteExclamationMark
    EndMovement

    .balign 4, 0
Route225_Movement_DahliaMeet:
    WalkNormalWest
    EndMovement

    .balign 4, 0
Route225_Movement_DahliaLeave:
    WalkNormalEast 9
    SetInvisible
    EndMovement

    .balign 4, 0
Route225_Movement_DahliaWalkBack:
    WalkNormalEast 7
    FaceWest
    EndMovement

    .balign 4, 0
Route225_Movement_PlayerApproachFrom614:
    WalkNormalNorth
    WalkNormalEast 2
    EndMovement

    .balign 4, 0
Route225_Movement_PlayerApproachFrom615:
    WalkNormalNorth
    WalkNormalEast
    EndMovement

    .balign 4, 0
Route225_Movement_PlayerBackTo614:
    WalkNormalWest 2
    WalkNormalSouth 2
    FaceNorth
    EndMovement

    .balign 4, 0
Route225_Movement_PlayerBackTo615:
    WalkNormalWest
    WalkNormalSouth 2
    FaceNorth
    EndMovement
