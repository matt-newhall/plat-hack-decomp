#include "macros/scrcmd.inc"
#include "res/text/bank/route_204_north.h"
#include "res/field/events/events_route_204_north.h"


    ScriptEntry Route204North_Youngster
    ScriptEntry Route204North_AceTrainerF
    ScriptEntry Route204North_ArrowSignpostFloaromaTown
    ScriptEntry Route204North_RivalTrigger
    ScriptEntryEnd

Route204North_Youngster:
    NPCMessage Route204North_Text_AreYouRaisingDifferentKindsOfPokemon
    End

Route204North_AceTrainerF:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet FLAG_RECEIVED_ROUTE_204_NORTH_TM78, Route204North_CaptivateOnlyWorksAgainstTheOppositeGender
    Message Route204North_Text_IdLikeYouToHaveThisTM
    SetVar VAR_0x8004, ITEM_TM78
    SetVar VAR_0x8005, 1
    GoToIfCannotFitItem VAR_0x8004, VAR_0x8005, VAR_RESULT, Route204North_BagIsFull
    Common_GiveItemQuantity
    SetFlag FLAG_RECEIVED_ROUTE_204_NORTH_TM78
    GoTo Route204North_CaptivateOnlyWorksAgainstTheOppositeGender

Route204North_CaptivateOnlyWorksAgainstTheOppositeGender:
    Message Route204North_Text_CaptivateOnlyWorksAgainstTheOppositeGender
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route204North_BagIsFull:
    Common_MessageBagIsFull
    CloseMessage
    ReleaseAll
    End

Route204North_ArrowSignpostFloaromaTown:
    ShowArrowSign Route204North_Text_Rt204FloaromaTown
    End

Route204North_RivalTrigger:
    LockAll
    ClearFlag FLAG_HIDE_ROUTE_203_RIVAL
    AddObject LOCALID_RIVAL
    ApplyMovement LOCALID_RIVAL, Route204North_Movement_RivalNoticePlayer
    WaitMovement
    Common_SetRivalBGM
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    GoToIfEq VAR_0x8004, 170, Route204North_RivalApproachX170
    GoToIfEq VAR_0x8004, 171, Route204North_RivalApproachX171
    GoToIfEq VAR_0x8004, 172, Route204North_RivalApproachX172
    End

Route204North_RivalApproachX170:
    ApplyMovement LOCALID_RIVAL, Route204North_Movement_RivalApproachX170
    WaitMovement
    ApplyMovement LOCALID_PLAYER, Route204North_Movement_PlayerFaceSouth
    GoTo Route204North_RivalIntro

Route204North_RivalApproachX171:
    ApplyMovement LOCALID_RIVAL, Route204North_Movement_RivalApproachX171
    WaitMovement
    ApplyMovement LOCALID_PLAYER, Route204North_Movement_PlayerFaceSouth
    GoTo Route204North_RivalIntro

Route204North_RivalApproachX172:
    ApplyMovement LOCALID_RIVAL, Route204North_Movement_RivalApproachX172
    WaitMovement
    ApplyMovement LOCALID_PLAYER, Route204North_Movement_PlayerFaceSouth
    GoTo Route204North_RivalIntro

Route204North_RivalIntro:
    BufferRivalName 0
    BufferPlayerName 1
    Message Route204North_Text_OfCourseIGotTougherIllDemonstrateItToYou
    CloseMessage
    GetPlayerStarterSpecies VAR_RESULT
    GoToIfEq VAR_RESULT, SPECIES_TURTWIG, Route204North_StartRivalBattleTurtwig
    GoToIfEq VAR_RESULT, SPECIES_CHIMCHAR, Route204North_StartRivalBattleChimchar
    GoTo Route204North_StartRivalBattlePiplup

Route204North_StartRivalBattlePiplup:
    StartTrainerBattle TRAINER_RIVAL_ROUTE_203_PIPLUP
    GoTo Route204North_RivalBattleEnd

Route204North_StartRivalBattleTurtwig:
    StartTrainerBattle TRAINER_RIVAL_ROUTE_203_TURTWIG
    GoTo Route204North_RivalBattleEnd

Route204North_StartRivalBattleChimchar:
    StartTrainerBattle TRAINER_RIVAL_ROUTE_203_CHIMCHAR
    GoTo Route204North_RivalBattleEnd

Route204North_RivalBattleEnd:
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, Route204North_BlackOutRivalBattle
    BufferRivalName 0
    Message Route204North_Text_WhatDoYouMeanILost
    CloseMessage
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    GoToIfEq VAR_0x8004, 170, Route204North_RivalLeaveX170
    GoToIfEq VAR_0x8004, 171, Route204North_RivalLeaveX171
    GoToIfEq VAR_0x8004, 172, Route204North_RivalLeaveX172
    End

Route204North_RivalLeaveX170:
    ApplyMovement LOCALID_RIVAL, Route204North_Movement_RivalLeaveX170
    WaitMovement
    GoTo Route204North_RemoveRival

Route204North_RivalLeaveX171:
    ApplyMovement LOCALID_RIVAL, Route204North_Movement_RivalLeaveX171
    WaitMovement
    GoTo Route204North_RemoveRival

Route204North_RivalLeaveX172:
    ApplyMovement LOCALID_RIVAL, Route204North_Movement_RivalLeaveX172
    WaitMovement
    GoTo Route204North_RemoveRival

Route204North_RemoveRival:
    RemoveObject LOCALID_RIVAL
    SetFlag FLAG_HIDE_ROUTE_203_RIVAL
    SetVar VAR_ROUTE_204_RIVAL_STATE, 1
    ReleaseAll
    End

Route204North_BlackOutRivalBattle:
    SetFlag FLAG_HIDE_ROUTE_203_RIVAL
    BlackOutFromBattle
    ReleaseAll
    End

    .balign 4, 0
Route204North_Movement_RivalNoticePlayer:
    WalkFastWest 9
    Delay8
    FaceNorth
    EmoteExclamationMark
    Delay8
    EndMovement

    .balign 4, 0
Route204North_Movement_RivalApproachX170:
    WalkFastWest 2
    WalkFastNorth 1
    EndMovement

    .balign 4, 0
Route204North_Movement_RivalApproachX171:
    WalkFastWest 1
    WalkFastNorth 1
    EndMovement

    .balign 4, 0
Route204North_Movement_RivalApproachX172:
    WalkFastNorth 1
    EndMovement

    .balign 4, 0
Route204North_Movement_PlayerFaceSouth:
    FaceSouth
    EndMovement

    .balign 4, 0
Route204North_Movement_RivalLeaveX170:
    WalkFastEast 1
    WalkFastNorth 4
    WalkFastEast 10
    EndMovement

    .balign 4, 0
Route204North_Movement_RivalLeaveX171:
    WalkFastEast 1
    WalkFastNorth 4
    WalkFastEast 10
    EndMovement

    .balign 4, 0
Route204North_Movement_RivalLeaveX172:
    WalkFastWest 1
    WalkFastNorth 4
    WalkFastEast 10
    EndMovement
