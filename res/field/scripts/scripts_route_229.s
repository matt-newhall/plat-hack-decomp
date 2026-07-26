#include "macros/scrcmd.inc"
#include "res/text/bank/route_229.h"
#include "res/field/events/events_route_229.h"


    ScriptEntry Route229_PokefanM
    ScriptEntry Route229_ArrowSignpostResortArea
    ScriptEntry Route229_SpeakToDesertBlocker
    ScriptEntry Route229_SpeakToDesertBlockerStep
    ScriptEntryEnd

Route229_PokefanM:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet FLAG_RECEIVED_ROUTE_229_NUGGET, Route229_ThoseAreMyNuggets
    Message Route229_Text_MakeItUpWithThis
    SetVar VAR_0x8004, ITEM_NUGGET
    SetVar VAR_0x8005, 1
    GoToIfCannotFitItem VAR_0x8004, VAR_0x8005, VAR_RESULT, Route229_BagIsFull
    Common_GiveItemQuantity
    SetFlag FLAG_RECEIVED_ROUTE_229_NUGGET
    SetVar VAR_0x8004, ITEM_NUGGET
    SetVar VAR_0x8005, 1
    GoToIfCannotFitItem VAR_0x8004, VAR_0x8005, VAR_RESULT, Route229_ThoseAreMyNuggets
    Message Route229_Text_TakeAnother
    Common_GiveItemQuantity
    GoTo Route229_ThoseAreMyNuggets
    End

Route229_ThoseAreMyNuggets:
    Message Route229_Text_ThoseAreMyNuggets
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route229_BagIsFull:
    Common_MessageBagIsFull
    CloseMessage
    ReleaseAll
    End

Route229_ArrowSignpostResortArea:
    ShowArrowSign Route229_Text_SignRt229ResortArea
    End

Route229_SpeakToDesertBlocker:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message Route229_Text_BlockDesertPersonSpeak
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route229_SpeakToDesertBlockerStep:
    GoToIfSet FLAG_HIDE_ROUTE_229_BLOCK_DESERT, Route229_DesertBlockStep_NoOp
    LockAll
    ApplyMovement LOCALID_PLAYER, Route229_Movement_PlayerLookSouth
    ApplyMovement LOCALID_BLOCKER, Route229_Movement_BlockerNoticeYou
    WaitMovement
    Message Route229_Text_BlockDesertPersonSpeak
    WaitButton
    CloseMessage
    ApplyMovement LOCALID_PLAYER, Route229_Movement_PlayerStepBack
    WaitMovement
    ReleaseAll
    End

Route229_DesertBlockStep_NoOp:
    End

    .balign 4, 0
Route229_Movement_PlayerLookSouth:
    FaceSouth
    EndMovement

    .balign 4, 0
Route229_Movement_BlockerNoticeYou:
    FaceNorth
    EmoteExclamationMark
    EndMovement

    .balign 4, 0
Route229_Movement_PlayerStepBack:
    WalkNormalEast
    EndMovement
