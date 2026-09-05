#include "macros/scrcmd.inc"
#include "res/text/bank/route_206.h"
#include "res/text/bank/menu_entries.h"
#include "res/field/events/events_route_206.h"


    ScriptEntry Route206_OnTransition
    ScriptEntry Route206_OnResume
    ScriptEntry Route206_Hiker
    ScriptEntry Route206_ArrowSignpostEternaCity
    ScriptEntry Route206_ArrowSignpostOreburghCity
    ScriptEntry Route206_JulienTrainerCount
    ScriptEntry Route206_JulienApproachesPlayer
    ScriptEntry Route206_RoySkirmishZone
    ScriptEntry Route206_StartBPCount
    ScriptEntryEnd

Route206_OnTransition:
    SetFlag FLAG_FIRST_ARRIVAL_CYCLING_ROAD_UNUSED
    End

Route206_StartBPCount:
    LockAll
    Message Route206_Text_ChallengeComplete
    SetVar VAR_ROY_BP_COUNTER 0
    SetVar VAR_PROMOTIONAL_TRAINERS_COUNTED 0
    GoTo Route206_RoyCountTrainers

Route206_RoyCountTrainers:
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 0, Route206_CheckCamperDiego
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 1, Route206_CheckPicnickerTori
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 2, Route206_CheckLassCassidy
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 3, Route206_CheckYoungsterWayne
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 4, Route206_CheckHikerReginald
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 5, Route206_CheckCollectorTerry
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 6, Route206_CheckPicnickerAna
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 7, Route206_CheckCamperParker
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 8, Route206_CheckRuinManiacGerald
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 9, Route206_CheckHikerLorenzo
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 10, Route206_CheckMiraWaywardCave
    GoToIfEq VAR_ROY_BP_COUNTER, 0, Route206_NoBP
    BufferNumber 0, VAR_ROY_BP_COUNTER
    Message Route206_Text_RoyGiveBP
    ScrCmd_298 VAR_ROY_BP_COUNTER
    PlayFanfare SEQ_PL_POINTGET3
    WaitFanfare
    WaitButton
    CloseMessage
    SetVar VAR_EXITING_SKIRMISH_ZONE_SUCCESS 0
    ReleaseAll
    End

Route206_NoBP:
    Message Route206_Text_RoyNoBP
    WaitButton
    CloseMessage
    SetVar VAR_EXITING_SKIRMISH_ZONE_SUCCESS 0
    ReleaseAll
    End

Route206_SkirmishTrainerDefeated:
    AddVar VAR_ROY_BP_COUNTER 2
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route206_RoyCountTrainers

Route206_SkirmishBossDefeated:
    AddVar VAR_ROY_BP_COUNTER 10
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route206_RoyCountTrainers

Route206_CheckCamperDiego:
    CheckTrainerFlag TRAINER_CAMPER_DIEGO
    GoToIfDefeated TRAINER_CAMPER_DIEGO, Route206_SkirmishTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route206_RoyCountTrainers

Route206_CheckPicnickerTori:
    CheckTrainerFlag TRAINER_PICNICKER_TORI
    GoToIfDefeated TRAINER_PICNICKER_TORI, Route206_SkirmishTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route206_RoyCountTrainers

Route206_CheckLassCassidy:
    CheckTrainerFlag TRAINER_LASS_CASSIDY
    GoToIfDefeated TRAINER_LASS_CASSIDY, Route206_SkirmishTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route206_RoyCountTrainers

Route206_CheckYoungsterWayne:
    CheckTrainerFlag TRAINER_YOUNGSTER_WAYNE
    GoToIfDefeated TRAINER_YOUNGSTER_WAYNE, Route206_SkirmishTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route206_RoyCountTrainers

Route206_CheckHikerReginald:
    CheckTrainerFlag TRAINER_HIKER_REGINALD
    GoToIfDefeated TRAINER_HIKER_REGINALD, Route206_SkirmishTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route206_RoyCountTrainers

Route206_CheckCollectorTerry:
    CheckTrainerFlag TRAINER_COLLECTOR_TERRY
    GoToIfDefeated TRAINER_COLLECTOR_TERRY, Route206_SkirmishTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route206_RoyCountTrainers

Route206_CheckPicnickerAna:
    CheckTrainerFlag TRAINER_PICNICKER_ANA
    GoToIfDefeated TRAINER_PICNICKER_ANA, Route206_SkirmishTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route206_RoyCountTrainers

Route206_CheckCamperParker:
    CheckTrainerFlag TRAINER_CAMPER_PARKER
    GoToIfDefeated TRAINER_CAMPER_PARKER, Route206_SkirmishTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route206_RoyCountTrainers

Route206_CheckRuinManiacGerald:
    CheckTrainerFlag TRAINER_RUIN_MANIAC_GERALD
    GoToIfDefeated TRAINER_RUIN_MANIAC_GERALD, Route206_SkirmishTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route206_RoyCountTrainers

Route206_CheckHikerLorenzo:
    CheckTrainerFlag TRAINER_HIKER_LORENZO
    GoToIfDefeated TRAINER_HIKER_LORENZO, Route206_SkirmishTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route206_RoyCountTrainers

Route206_CheckMiraWaywardCave:
    GoToIfSet FLAG_SKIRMISH_MIRA_DEFEATED, Route206_SkirmishBossDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route206_RoyCountTrainers


Route206_OnResume:
    CallIfSet FLAG_ON_CYCLING_ROAD, Route206_ForceBicycling
    GetPreviousMapID VAR_MAP_LOCAL_0
    GoToIfEq VAR_MAP_LOCAL_0, MAP_HEADER_ROUTE_206_CYCLING_ROAD_NORTH_GATE, Route206_TrySetFlagsCyclingRoad
    GoToIfEq VAR_MAP_LOCAL_0, MAP_HEADER_ROUTE_206_CYCLING_ROAD_SOUTH_GATE, Route206_TrySetFlagsCyclingRoad
    End

Route206_TrySetFlagsCyclingRoad:
    GoToIfSet FLAG_UNK_0x0003, Route206_OnResumeEnd
    GetPlayerMapPos VAR_MAP_LOCAL_0, VAR_MAP_LOCAL_1
    GoToIfLt VAR_MAP_LOCAL_0, 299, Route206_OnResumeEnd
    GoToIfGt VAR_MAP_LOCAL_0, 306, Route206_OnResumeEnd
    GoToIfEq VAR_MAP_LOCAL_1, 576, Route206_SetFlagsCyclingRoad
    GoToIfEq VAR_MAP_LOCAL_1, 681, Route206_SetFlagsCyclingRoad
    End

Route206_SetFlagsCyclingRoad:
    SetFlag FLAG_UNK_0x0003
    SetFlag FLAG_ON_CYCLING_ROAD
    SetCyclingBGM
    ForceBicycling TRUE
    End

Route206_OnResumeEnd:
    End

Route206_ForceBicycling:
    ForceBicycling TRUE
    Return

Route206_Hiker:
    NPCMessage Route206_Text_IHeardThereWereTwoCavesOnRoute206
    End

Route206_ArrowSignpostEternaCity:
    ShowArrowSign Route206_Text_Rt206EternaCity
    End

Route206_ArrowSignpostOreburghCity:
    ShowArrowSign Route206_Text_Rt206OreburghCity
    End

Route206_BagIsFull:
    Common_MessageBagIsFull
    CloseMessage
    ReleaseAll
    End

Route206_JulienApproachesPlayer:
    LockAll
    ApplyMovement LOCALID_JULIEN, Route206_Movement_JulienNoticePlayer
    WaitMovement
    SetVar VAR_ROUTE_206_JULIEN_STATE, 1
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    GoToIfEq VAR_0x8004, 301, Route206_JulienApproachX301
    GoToIfEq VAR_0x8004, 302, Route206_JulienApproachX302
    GoToIfEq VAR_0x8004, 303, Route206_JulienApproachX303
    GoToIfEq VAR_0x8004, 304, Route206_JulienApproachX304
    End

Route206_JulienIntro:
    Message Route206_Text_ExplainPromotion
    WaitButton
    CloseMessage
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    GoToIfEq VAR_0x8004, 301, Route206_JulienLeaveX301
    GoToIfEq VAR_0x8004, 302, Route206_JulienLeaveX302
    GoToIfEq VAR_0x8004, 303, Route206_JulienLeaveX303
    GoToIfEq VAR_0x8004, 304, Route206_JulienLeaveX304
    End

Route206_JulienTrainerCount:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet FLAG_ROUTE_206_PROMOTIONAL_ITEM_RECIEVED, Route206_PromotionalItemRecieved
    SetVar VAR_JULIEN_TRAINERS_REMAINING 9
    SetVar VAR_PROMOTIONAL_TRAINERS_COUNTED 0
    GoTo Route206_CountTrainers

Route206_CountTrainers:
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 0, Route206_CheckCyclistAxel
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 1, Route206_CheckCyclistMegan
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 2, Route206_CheckCyclistJames
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 3, Route206_CheckCyclistNicole
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 4, Route206_CheckCyclistJohn
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 5, Route206_CheckCyclistKayla
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 6, Route206_CheckCyclistRyan
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 7, Route206_CheckCyclistRachel
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 8, Route206_CheckHikerTheodore
    GoToIfEq VAR_JULIEN_TRAINERS_REMAINING, 1, Route206_JulienTrainerCountSingular
    GoToIfEq VAR_JULIEN_TRAINERS_REMAINING, 0, Route206_WonPromotional
    BufferNumber 0, VAR_JULIEN_TRAINERS_REMAINING
    Message Route206_Text_JulienTrainerCount
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route206_JulienTrainerCountSingular:
    BufferNumber 0, VAR_JULIEN_TRAINERS_REMAINING
    Message Route206_Text_JulienTrainerCountSingular
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route206_PromotionalTrainerDefeated:
    SubVar VAR_JULIEN_TRAINERS_REMAINING 1
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route206_CountTrainers

Route206_WonPromotional:
    Message Route206_Text_PromotionalRouteCongrats
    InitGlobalTextListMenu 30, 13, 0, VAR_RESULT, NO_EXIT_ON_B
    SetMenuXOriginToRight
    AddListMenuEntry MenuEntries_Text_Julien_WideLens, 0
    AddListMenuEntry MenuEntries_Text_Julien_Charti, 1
    ShowListMenu
    GoToIfEq VAR_RESULT, 0, Route206_GiveWideLens
    GoToIfEq VAR_RESULT, 1, Route206_GiveCharti
    End

Route206_GiveWideLens:
    SetVar VAR_0x8004, ITEM_WIDE_LENS
    SetVar VAR_0x8005, 1
    GoToIfCannotFitItem VAR_0x8004, VAR_0x8005, VAR_RESULT, Route206_BagIsFull
    Common_GiveItemQuantity
    SetFlag FLAG_ROUTE_206_PROMOTIONAL_ITEM_RECIEVED
    GoTo Route206_PromotionalItemRecieved

Route206_GiveCharti:
    SetVar VAR_0x8004, ITEM_CHARTI_BERRY
    SetVar VAR_0x8005, 5
    GoToIfCannotFitItem VAR_0x8004, VAR_0x8005, VAR_RESULT, Route206_BagIsFull
    Common_GiveItemQuantity
    SetFlag FLAG_ROUTE_206_PROMOTIONAL_ITEM_RECIEVED
    GoTo Route206_PromotionalItemRecieved

Route206_PromotionalItemRecieved:
    Message Route206_Text_WatchOutForMorePromotions
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route206_CheckCyclistAxel:
    CheckTrainerFlag TRAINER_CYCLIST_AXEL
    GoToIfDefeated TRAINER_CYCLIST_AXEL, Route206_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route206_CountTrainers

Route206_CheckCyclistMegan:
    CheckTrainerFlag TRAINER_CYCLIST_MEGAN
    GoToIfDefeated TRAINER_CYCLIST_MEGAN, Route206_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route206_CountTrainers

Route206_CheckCyclistJames:
    CheckTrainerFlag TRAINER_CYCLIST_JAMES
    GoToIfDefeated TRAINER_CYCLIST_JAMES, Route206_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route206_CountTrainers

Route206_CheckCyclistNicole:
    CheckTrainerFlag TRAINER_CYCLIST_NICOLE
    GoToIfDefeated TRAINER_CYCLIST_NICOLE, Route206_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route206_CountTrainers

Route206_CheckCyclistJohn:
    CheckTrainerFlag TRAINER_CYCLIST_JOHN
    GoToIfDefeated TRAINER_CYCLIST_JOHN, Route206_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route206_CountTrainers

Route206_CheckCyclistKayla:
    CheckTrainerFlag TRAINER_CYCLIST_KAYLA
    GoToIfDefeated TRAINER_CYCLIST_KAYLA, Route206_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route206_CountTrainers

Route206_CheckCyclistRyan:
    CheckTrainerFlag TRAINER_CYCLIST_RYAN
    GoToIfDefeated TRAINER_CYCLIST_RYAN, Route206_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route206_CountTrainers

Route206_CheckCyclistRachel:
    CheckTrainerFlag TRAINER_CYCLIST_RACHEL
    GoToIfDefeated TRAINER_CYCLIST_RACHEL, Route206_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route206_CountTrainers

Route206_CheckHikerTheodore:
    CheckTrainerFlag TRAINER_HIKER_THEODORE
    GoToIfDefeated TRAINER_HIKER_THEODORE, Route206_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route206_CountTrainers

Route206_RoySkirmishZone:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet FLAG_ROY_INTRODUCED, Route206_SkirmishZoneMenu
    Message Route206_Text_RoyIntroduction
    SetFlag FLAG_ROY_INTRODUCED
    GoTo Route206_SkirmishZoneMenu

Route206_SkirmishZoneMenu:
    Message Route206_Text_RoyWannaChallenge
    InitGlobalTextListMenu 30, 11, 0, VAR_RESULT
    SetMenuXOriginToRight
    AddListMenuEntry MenuEntries_Text_BattleTower_Challenge, 0
    AddListMenuEntry pl_msg_00000361_00040, 1
    AddListMenuEntry MenuEntries_Text_Exit, 2
    ShowListMenu
    GoToIfEq VAR_RESULT, 0, Route206_ChallengeSkirmishZone
    GoToIfEq VAR_RESULT, 1, Route206_ShowSkirmishRules
    CloseMessage
    ReleaseAll
    End

 Route206_ChallengeSkirmishZone:
    GoToIfSet FLAG_WAYWARD_CAVE_SKIMISH_ZONE_ENTERED, Route206_AlreadyChallengedZone
    Message Route206_Text_KnockEmDead
    WaitButton
    CloseMessage
    SetFlag FLAG_PORTA_PC_DISABLED
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    GoToIfEq VAR_0x8004, 309, Route206_ChallengeZoneX309
    GoToIfEq VAR_0x8004, 311, Route206_ChallengeZoneX311
    GoToIfEq VAR_0x8005, 609, Route206_ChallengeZoneY609
    End

 Route206_AlreadyChallengedZone:
    Message Route206_Text_AlreadyChallengedZone
    WaitButton
    CloseMessage
    ReleaseAll
    End

 Route206_ShowSkirmishRules:
    Message Route206_Text_SkirmishZoneRules
    WaitButton
    CloseMessage
    ReleaseAll
    End


.balign 4, 0
Route206_Movement_JulienNoticePlayer:
    EmoteExclamationMark
    Delay8
    EndMovement

Route206_JulienApproachX301:
    ApplyMovement LOCALID_JULIEN, Route206_Movement_JulienApproachX301
    WaitMovement
    GoTo Route206_JulienIntro

   .balign 4, 0
Route206_Movement_JulienApproachX301:
    WalkNormalSouth 2
    WalkNormalEast 5
    WalkNormalNorth 1
    EndMovement

Route206_JulienApproachX302:
    ApplyMovement LOCALID_JULIEN, Route206_Movement_JulienApproachX302
    WaitMovement
    GoTo Route206_JulienIntro

   .balign 4, 0
Route206_Movement_JulienApproachX302:
    WalkNormalSouth 2
    WalkNormalEast 6
    WalkNormalNorth 1
    EndMovement


Route206_JulienApproachX303:
    ApplyMovement LOCALID_JULIEN, Route206_Movement_JulienApproachX303
    WaitMovement
    GoTo Route206_JulienIntro

   .balign 4, 0
Route206_Movement_JulienApproachX303:
    WalkNormalSouth 2
    WalkNormalEast 7
    WalkNormalNorth 1
    EndMovement


Route206_JulienApproachX304:
    ApplyMovement LOCALID_JULIEN, Route206_Movement_JulienApproachX304
    WaitMovement
    GoTo Route206_JulienIntro

   .balign 4, 0
Route206_Movement_JulienApproachX304:
    WalkNormalSouth 2
    WalkNormalEast 8
    WalkNormalNorth 1
    EndMovement


Route206_JulienLeaveX301:
    ApplyMovement LOCALID_JULIEN, Route206_Movement_JulienLeaveX301
    WaitMovement
    ReleaseAll
    End

   .balign 4, 0
Route206_Movement_JulienLeaveX301:
    WalkNormalSouth 1
    WalkNormalWest 5
    WalkNormalNorth 2
    FaceEast
    EndMovement


Route206_JulienLeaveX302:
    ApplyMovement LOCALID_JULIEN, Route206_Movement_JulienLeaveX302
    WaitMovement
    ReleaseAll
    End

   .balign 4, 0
Route206_Movement_JulienLeaveX302:
    WalkNormalSouth 1
    WalkNormalWest 6
    WalkNormalNorth 2
    FaceEast
    EndMovement


Route206_JulienLeaveX303:
    ApplyMovement LOCALID_JULIEN, Route206_Movement_JulienLeaveX303
    WaitMovement
    ReleaseAll
    End

   .balign 4, 0
Route206_Movement_JulienLeaveX303:
    WalkNormalSouth 1
    WalkNormalWest 7
    WalkNormalNorth 2
    FaceEast
    EndMovement


Route206_JulienLeaveX304:
    ApplyMovement LOCALID_JULIEN, Route206_Movement_JulienLeaveX304
    WaitMovement
    ReleaseAll
    End

   .balign 4, 0
Route206_Movement_JulienLeaveX304:
    WalkNormalSouth 1
    WalkNormalWest 8
    WalkNormalNorth 2
    FaceEast
    EndMovement

Route206_ChallengeZoneX309:
    ApplyMovement LOCALID_ROY, Route206_Movement_RoyMoveRight
    WaitMovement
    ApplyMovement LOCALID_PLAYER, Route206_Movement_PlayerMoveRight
    WaitMovement
    ApplyMovement LOCALID_PLAYER, Route206_Movement_PlayerMoveUp
    WaitMovement
    SetFlag FLAG_WAYWARD_CAVE_SKIMISH_ZONE_ENTERED
    Warp MAP_HEADER_WAYWARD_CAVE_1F, 0, 41, 52, DIR_NORTH
    ReleaseAll
    End

Route206_ChallengeZoneX311:
    ApplyMovement LOCALID_ROY, Route206_Movement_RoyMoveLeft
    WaitMovement
    ApplyMovement LOCALID_PLAYER, Route206_Movement_PlayerMoveLeft
    WaitMovement
    ApplyMovement LOCALID_PLAYER, Route206_Movement_PlayerMoveUp
    WaitMovement
    SetFlag FLAG_WAYWARD_CAVE_SKIMISH_ZONE_ENTERED
    Warp MAP_HEADER_WAYWARD_CAVE_1F, 0, 41, 52, DIR_NORTH
    ReleaseAll
    End

Route206_ChallengeZoneY609:
    ApplyMovement LOCALID_ROY, Route206_Movement_RoyMoveRight
    WaitMovement
    ApplyMovement LOCALID_PLAYER, Route206_Movement_PlayerMoveUp
    WaitMovement
    ApplyMovement LOCALID_PLAYER, Route206_Movement_PlayerMoveUp
    WaitMovement
    SetFlag FLAG_WAYWARD_CAVE_SKIMISH_ZONE_ENTERED
    Warp MAP_HEADER_WAYWARD_CAVE_1F, 0, 41, 52, DIR_NORTH
    ReleaseAll
    End

.balign 4, 0
Route206_Movement_RoyMoveLeft:
    WalkNormalWest 1
    FaceEast
    EndMovement

.balign 4, 0
Route206_Movement_RoyMoveRight:
    WalkNormalEast 1
    FaceWest
    EndMovement

.balign 4, 0
Route206_Movement_PlayerMoveLeft:
    WalkNormalWest 1
    EndMovement

.balign 4, 0
Route206_Movement_PlayerMoveRight:
    WalkNormalEast 1
    EndMovement

.balign 4, 0
Route206_Movement_PlayerMoveUp:
    WalkNormalNorth 1
    EndMovement

    .balign 4, 0
