#include "macros/scrcmd.inc"
#include "res/text/bank/route_212_south.h"
#include "res/text/bank/menu_entries.h"


    ScriptEntry Route212South_SchoolKidM
    ScriptEntry Route212South_Lady
    ScriptEntry Route212South_Collector
    ScriptEntry Route212South_ArrowSignPastoriaCity
    ScriptEntry Route212South_SignShardsWanted
    ScriptEntry Route212South_PolicemanDanny
    ScriptEntry Route212South_OnTransition
    ScriptEntry Route212South_TrainerTips
    ScriptEntry Route212South_JulienTrainerCount
    ScriptEntryEnd

Route212South_OnTransition:
    GetTimeOfDay VAR_MAP_LOCAL_0
    GoToIfInRange VAR_MAP_LOCAL_0, TIMEOFDAY_MORNING, TIMEOFDAY_TWILIGHT, Route212South_SetPolicemanNoBattle
    GoToIfInRange VAR_MAP_LOCAL_0, TIMEOFDAY_NIGHT, TIMEOFDAY_LATE_NIGHT, Route212South_SetPolicemanBattle
    End

Route212South_SetPolicemanNoBattle:
    ClearFlag FLAG_HIDE_ROUTE_212_SOUTH_POLICEMAN_DANNY_NO_BATTLE
    SetFlag FLAG_HIDE_ROUTE_212_SOUTH_POLICEMAN_DANNY
    End

Route212South_SetPolicemanBattle:
    ClearFlag FLAG_HIDE_ROUTE_212_SOUTH_POLICEMAN_DANNY
    SetFlag FLAG_HIDE_ROUTE_212_SOUTH_POLICEMAN_DANNY_NO_BATTLE
    End

Route212South_SchoolKidM:
    NPCMessage Route212South_Text_CrossLogsOnBike
    End

Route212South_Lady:
    NPCMessage Route212South_Text_ImNotStuck
    End

Route212South_Collector:
    NPCMessage Route212South_Text_HowAboutPokemonMansion
    End

Route212South_ArrowSignPastoriaCity:
    ShowArrowSign Route212South_Text_SignPastoriaCity
    End

Route212South_SignShardsWanted:
    ShowLandmarkSign Route212South_Text_SignShardsWanted
    End

Route212South_TrainerTips:
    ShowScrollingSign Route212South_Text_TrainerTipsBog
    End

Route212South_PolicemanDanny:
    NPCMessage Route212South_Text_ConstantPatrol
    End

Route212South_JulienTrainerCount:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet FLAG_ROUTE_212_SOUTH_PROMOTIONAL_ITEM_RECIEVED, Route212South_PromotionalItemRecieved
    SetVar VAR_JULIEN_TRAINERS_REMAINING 12
    SetVar VAR_PROMOTIONAL_TRAINERS_COUNTED 0
    GoTo Route212South_CountTrainers

Route212South_CountTrainers:
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 0, Route212South_CheckFishermanJuan
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 1, Route212South_CheckFishermanJosh
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 2, Route212South_CheckFishermanTravis
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 3, Route212South_CheckRangerTaylor
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 4, Route212South_CheckRangerAllison
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 5, Route212South_CheckRangerJeffrey
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 6, Route212South_CheckPolicemanDanny
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 7, Route212South_CheckScientistStefano
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 8, Route212South_CheckCollectorDean
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 9, Route212South_CheckScientistShaun
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 10, Route212South_CheckParasolLadyAlexa
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 11, Route212South_CheckParasolLadySabrina
    GoToIfEq VAR_JULIEN_TRAINERS_REMAINING, 1, Route212South_JulienTrainerCountSingular
    GoToIfEq VAR_JULIEN_TRAINERS_REMAINING, 0, Route212South_WonPromotional
    BufferNumber 0, VAR_JULIEN_TRAINERS_REMAINING
    Message Route212South_Text_JulienTrainerCount
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route212South_JulienTrainerCountSingular:
    BufferNumber 0, VAR_JULIEN_TRAINERS_REMAINING
    Message Route212South_Text_JulienTrainerCountSingular
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route212South_PromotionalTrainerDefeated:
    SubVar VAR_JULIEN_TRAINERS_REMAINING 1
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route212South_CountTrainers

Route212South_WonPromotional:
    Message Route212South_Text_PromotionalRouteCongrats
    InitGlobalTextListMenu 30, 13, 0, VAR_RESULT, NO_EXIT_ON_B
    SetMenuXOriginToRight
    AddListMenuEntry MenuEntries_Text_Julien_LoadedDice, 0
    AddListMenuEntry MenuEntries_Text_Julien_Passho, 1
    ShowListMenu
    GoToIfEq VAR_RESULT, 0, Route212South_GiveLoadedDice
    GoToIfEq VAR_RESULT, 1, Route212South_GivePasshoBerry
    End

Route212South_GiveLoadedDice:
    SetVar VAR_0x8004, ITEM_LOADED_DICE
    SetVar VAR_0x8005, 1
    GoToIfCannotFitItem VAR_0x8004, VAR_0x8005, VAR_RESULT, Route212South_BagIsFull
    Common_GiveItemQuantity
    SetFlag FLAG_ROUTE_212_SOUTH_PROMOTIONAL_ITEM_RECIEVED
    GoTo Route212South_PromotionalItemRecieved

Route212South_GivePasshoBerry:
    SetVar VAR_0x8004, ITEM_PASSHO_BERRY
    SetVar VAR_0x8005, 5
    GoToIfCannotFitItem VAR_0x8004, VAR_0x8005, VAR_RESULT, Route212South_BagIsFull
    Common_GiveItemQuantity
    SetFlag FLAG_ROUTE_212_SOUTH_PROMOTIONAL_ITEM_RECIEVED
    GoTo Route212South_PromotionalItemRecieved

Route212South_PromotionalItemRecieved:
    Message Route212South_Text_WatchOutForMorePromotions
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route212South_CheckFishermanJuan:
    CheckTrainerFlag TRAINER_FISHERMAN_JUAN
    GoToIfDefeated TRAINER_FISHERMAN_JUAN, Route212South_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route212South_CountTrainers

Route212South_CheckFishermanJosh:
    CheckTrainerFlag TRAINER_FISHERMAN_JOSH
    GoToIfDefeated TRAINER_FISHERMAN_JOSH, Route212South_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route212South_CountTrainers

Route212South_CheckFishermanTravis:
    CheckTrainerFlag TRAINER_FISHERMAN_TRAVIS
    GoToIfDefeated TRAINER_FISHERMAN_TRAVIS, Route212South_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route212South_CountTrainers

Route212South_CheckRangerTaylor:
    CheckTrainerFlag TRAINER_RANGER_TAYLOR
    GoToIfDefeated TRAINER_RANGER_TAYLOR, Route212South_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route212South_CountTrainers

Route212South_CheckRangerAllison:
    CheckTrainerFlag TRAINER_RANGER_ALLISON
    GoToIfDefeated TRAINER_RANGER_ALLISON, Route212South_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route212South_CountTrainers

Route212South_CheckRangerJeffrey:
    CheckTrainerFlag TRAINER_RANGER_JEFFREY
    GoToIfDefeated TRAINER_RANGER_JEFFREY, Route212South_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route212South_CountTrainers

Route212South_CheckPolicemanDanny:
    CheckTrainerFlag TRAINER_POLICEMAN_DANNY
    GoToIfDefeated TRAINER_POLICEMAN_DANNY, Route212South_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route212South_CountTrainers

Route212South_CheckScientistStefano:
    CheckTrainerFlag TRAINER_SCIENTIST_STEFANO
    GoToIfDefeated TRAINER_SCIENTIST_STEFANO, Route212South_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route212South_CountTrainers

Route212South_CheckCollectorDean:
    CheckTrainerFlag TRAINER_COLLECTOR_DEAN
    GoToIfDefeated TRAINER_COLLECTOR_DEAN, Route212South_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route212South_CountTrainers

Route212South_CheckScientistShaun:
    CheckTrainerFlag TRAINER_SCIENTIST_SHAUN
    GoToIfDefeated TRAINER_SCIENTIST_SHAUN, Route212South_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route212South_CountTrainers

Route212South_CheckParasolLadyAlexa:
    CheckTrainerFlag TRAINER_PARASOL_LADY_ALEXA
    GoToIfDefeated TRAINER_PARASOL_LADY_ALEXA, Route212South_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route212South_CountTrainers

Route212South_CheckParasolLadySabrina:
    CheckTrainerFlag TRAINER_PARASOL_LADY_SABRINA
    GoToIfDefeated TRAINER_PARASOL_LADY_SABRINA, Route212South_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route212South_CountTrainers

Route212South_BagIsFull:
    Common_MessageBagIsFull
    CloseMessage
    ReleaseAll
    End
