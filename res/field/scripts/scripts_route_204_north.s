#include "macros/scrcmd.inc"
#include "res/text/bank/route_204_north.h"
#include "res/text/bank/menu_entries.h"
#include "res/field/events/events_route_204_north.h"


    ScriptEntry Route204North_Youngster
    ScriptEntry Route204North_AceTrainerF
    ScriptEntry Route204North_ArrowSignpostFloaromaTown
    ScriptEntry Route204North_RivalTrigger
    ScriptEntry Route204North_JulienTrainerCount
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

Route204North_JulienTrainerCount:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet FLAG_ROUTE_204_PROMOTIONAL_ITEM_RECIEVED, Route204North_PromotionalItemRecieved
    SetVar VAR_JULIEN_TRAINERS_REMAINING 6
    SetVar VAR_PROMOTIONAL_TRAINERS_COUNTED 0
    GoTo Route204North_CountTrainers

Route204North_CountTrainers:
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 0, Route204North_CheckBugCatcherBrandon
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 1, Route204North_CheckAromaLadyTaylor
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 2, Route204North_CheckTwinsLivAndLiz
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 3, Route204North_CheckLassSarah
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 4, Route204North_CheckLassSamantha
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 5, Route204North_CheckYoungsterTyler
    GoToIfEq VAR_JULIEN_TRAINERS_REMAINING, 1, Route204North_JulienTrainerCountSingular
    GoToIfEq VAR_JULIEN_TRAINERS_REMAINING, 0, Route204North_WonPromotional
    BufferNumber 0, VAR_JULIEN_TRAINERS_REMAINING
    Message Route204North_Text_JulienTrainerCount
    WaitButton
    CloseMessage
    ReleaseAll
    End
    
Route204North_JulienTrainerCountSingular:
    BufferNumber 0, VAR_JULIEN_TRAINERS_REMAINING
    Message Route204North_Text_JulienTrainerCountSingular
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route204North_PromotionalTrainerDefeated:
    SubVar VAR_JULIEN_TRAINERS_REMAINING 1
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route204North_CountTrainers

Route204North_WonPromotional:
    Message Route204North_Text_PromotionalRouteCongrats
    InitGlobalTextListMenu 30, 13, 0, VAR_RESULT, NO_EXIT_ON_B
    SetMenuXOriginToRight
    AddListMenuEntry MenuEntries_Text_Julien_SilkScarf, 0
    AddListMenuEntry MenuEntries_Text_Julien_Chilan, 1
    ShowListMenu
    GoToIfEq VAR_RESULT, 0, Route204North_GiveSilkScarf
    GoToIfEq VAR_RESULT, 1, Route204North_GiveChilan
    End

Route204North_GiveSilkScarf:
    SetVar VAR_0x8004, ITEM_SILK_SCARF
    SetVar VAR_0x8005, 1
    GoToIfCannotFitItem VAR_0x8004, VAR_0x8005, VAR_RESULT, Route204North_BagIsFull
    Common_GiveItemQuantity
    SetFlag FLAG_ROUTE_204_PROMOTIONAL_ITEM_RECIEVED
    GoTo Route204North_PromotionalItemRecieved

Route204North_GiveChilan:
    SetVar VAR_0x8004, ITEM_CHILAN_BERRY
    SetVar VAR_0x8005, 5
    GoToIfCannotFitItem VAR_0x8004, VAR_0x8005, VAR_RESULT, Route204North_BagIsFull
    Common_GiveItemQuantity
    SetFlag FLAG_ROUTE_204_PROMOTIONAL_ITEM_RECIEVED
    GoTo Route204North_PromotionalItemRecieved

Route204North_PromotionalItemRecieved:
    Message Route204North_Text_WatchOutForMorePromotions
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route204North_CheckBugCatcherBrandon:
    CheckTrainerFlag TRAINER_BUG_CATCHER_BRANDON
    GoToIfDefeated TRAINER_BUG_CATCHER_BRANDON, Route204North_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route204North_CountTrainers

Route204North_CheckAromaLadyTaylor:
    CheckTrainerFlag TRAINER_AROMA_LADY_TAYLOR
    GoToIfDefeated TRAINER_AROMA_LADY_TAYLOR, Route204North_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route204North_CountTrainers

Route204North_CheckTwinsLivAndLiz:
    CheckTrainerFlag TRAINER_TWINS_LIV_AND_LIZ
    GoToIfDefeated TRAINER_TWINS_LIV_AND_LIZ, Route204North_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route204North_CountTrainers

Route204North_CheckLassSarah:
    CheckTrainerFlag TRAINER_LASS_SARAH
    GoToIfDefeated TRAINER_LASS_SARAH, Route204North_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route204North_CountTrainers

Route204North_CheckLassSamantha:
    CheckTrainerFlag TRAINER_LASS_SAMANTHA
    GoToIfDefeated TRAINER_LASS_SAMANTHA, Route204North_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route204North_CountTrainers

Route204North_CheckYoungsterTyler:
    CheckTrainerFlag TRAINER_YOUNGSTER_TYLER
    GoToIfDefeated TRAINER_YOUNGSTER_TYLER, Route204North_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route204North_CountTrainers

    
Route204North_ArrowSignpostFloaromaTown:
    ShowArrowSign Route204North_Text_Rt204FloaromaTown
    End

Route204North_RivalTrigger:
    LockAll
    ClearFlag FLAG_HIDE_ROUTE_204_RIVAL
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
    ApplyMovement LOCALID_JULIEN, Route204North_Movement_JulienFaceWest
    WaitMovement
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
    SetFlag FLAG_HIDE_ROUTE_204_RIVAL
    SetVar VAR_ROUTE_204_RIVAL_STATE, 1
    GoTo Route204North_JulienApproachPlayer
    End

Route204North_BlackOutRivalBattle:
    SetFlag FLAG_HIDE_ROUTE_204_RIVAL
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

Route204North_JulienApproachPlayer:
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    GoToIfEq VAR_0x8004, 170, Route204North_JulienApproachX170
    GoToIfEq VAR_0x8004, 171, Route204North_JulienApproachX171
    GoToIfEq VAR_0x8004, 172, Route204North_JulienApproachX172
    End

Route204North_JulienApproachX170:
    ApplyMovement LOCALID_JULIEN, Route204North_Movement_JulienApproachX170
    WaitMovement
    ApplyMovement LOCALID_PLAYER, Route204North_Movement_PlayerFaceNorth
    GoTo Route204North_JulienIntro

Route204North_JulienApproachX171:
    ApplyMovement LOCALID_JULIEN, Route204North_Movement_JulienApproachX171
    WaitMovement
    ApplyMovement LOCALID_PLAYER, Route204North_Movement_PlayerFaceNorth
    GoTo Route204North_JulienIntro

Route204North_JulienApproachX172:
    ApplyMovement LOCALID_JULIEN, Route204North_Movement_JulienApproachX172
    WaitMovement
    ApplyMovement LOCALID_PLAYER, Route204North_Movement_PlayerFaceNorth
    GoTo Route204North_JulienIntro

    .balign 4, 0
Route204North_Movement_JulienApproachX170:
    WalkNormalNorth 2
    WalkNormalWest 5
    WalkNormalSouth 2
    EndMovement

    .balign 4, 0
Route204North_Movement_JulienApproachX171:
    WalkNormalNorth 2
    WalkNormalWest 4
    WalkNormalSouth 2
    EndMovement

    .balign 4, 0
Route204North_Movement_JulienApproachX172:
    WalkNormalNorth 2
    WalkNormalWest 3
    WalkNormalSouth 2
    EndMovement

Route204North_JulienIntro:
    Message Route204North_Text_BonjourChamp
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_YES, Route204North_IHaveTime
    GoToIfEq VAR_RESULT, MENU_NO, Route204North_IDontHaveTime
    CloseMessage

Route204North_IHaveTime:
    Message Route204North_Text_SocietyOfBattleConnoisseurs
    WaitButton
    CloseMessage
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    GoToIfEq VAR_0x8004, 170, Route204North_JulienLeaveX170
    GoToIfEq VAR_0x8004, 171, Route204North_JulienLeaveX171
    GoToIfEq VAR_0x8004, 172, Route204North_JulienLeaveX172
    End

Route204North_IDontHaveTime:
    Message Route204North_Text_SuitYourself
    WaitButton
    CloseMessage
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    GoToIfEq VAR_0x8004, 170, Route204North_JulienLeaveX170
    GoToIfEq VAR_0x8004, 171, Route204North_JulienLeaveX171
    GoToIfEq VAR_0x8004, 172, Route204North_JulienLeaveX172
    End

Route204North_JulienLeaveX170:
    ApplyMovement LOCALID_JULIEN, Route204North_Movement_JulienLeaveX170
    WaitMovement
    ReleaseAll
    EndMovement

Route204North_JulienLeaveX171:
    ApplyMovement LOCALID_JULIEN, Route204North_Movement_JulienLeaveX171
    WaitMovement
    ReleaseAll
    EndMovement

Route204North_JulienLeaveX172:
    ApplyMovement LOCALID_JULIEN, Route204North_Movement_JulienLeaveX172
    WaitMovement
    ReleaseAll
    EndMovement

    .balign 4, 0
Route204North_Movement_JulienLeaveX170:
    WalkNormalNorth 2
    WalkNormalEast 5
    WalkNormalSouth 2
    EndMovement

    .balign 4, 0
Route204North_Movement_JulienLeaveX171:
    WalkNormalNorth 2
    WalkNormalEast 4
    WalkNormalSouth 2
    EndMovement

    .balign 4, 0
Route204North_Movement_JulienLeaveX172:
    WalkNormalNorth 2
    WalkNormalEast 3
    WalkNormalSouth 2
    EndMovement

    .balign 4, 0
Route204North_Movement_PlayerFaceSouth:
    FaceSouth
    EndMovement

    .balign 4, 0
Route204North_Movement_PlayerFaceNorth:
    FaceNorth
    EndMovement

.balign 4, 0
Route204North_Movement_JulienFaceWest:
    FaceWest
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
