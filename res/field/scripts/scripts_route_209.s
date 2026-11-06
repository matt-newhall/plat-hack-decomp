#include "macros/scrcmd.inc"
#include "res/text/bank/route_209.h"
#include "res/text/bank/menu_entries.h"

    ScriptEntry Route209_PokefanM
    ScriptEntry Route209_HallowedTower
    ScriptEntry Route209_ArrowSignpostHearthomeCity
    ScriptEntry Route209_ArrowSignpostSolaceonTown
    ScriptEntry Route209_Fisherman
    ScriptEntry Route209_JoggerRichard
    ScriptEntry Route209_JoggerRaul
    ScriptEntry Route209_OnTransition
    ScriptEntry Route209_TrainerTips
    ScriptEntry Route209_JulienTrainerCount
    ScriptEntryEnd

Route209_OnTransition:
    GetTimeOfDay VAR_MAP_LOCAL_0
    GoToIfEq VAR_MAP_LOCAL_0, TIMEOFDAY_MORNING, Route209_SetJoggersBattle
    GoToIfInRange VAR_MAP_LOCAL_0, TIMEOFDAY_DAY, TIMEOFDAY_LATE_NIGHT, Route209_SetJoggersNoBattle
    End

Route209_SetJoggersBattle:
    ClearFlag FLAG_HIDE_ROUTE_209_JOGGER_RICHARD
    ClearFlag FLAG_HIDE_ROUTE_209_JOGGER_RAUL
    SetFlag FLAG_HIDE_ROUTE_209_JOGGER_RICHARD_NO_BATTLE
    SetFlag FLAG_HIDE_ROUTE_209_JOGGER_RAUL_NO_BATTLE
    End

Route209_SetJoggersNoBattle:
    ClearFlag FLAG_HIDE_ROUTE_209_JOGGER_RICHARD_NO_BATTLE
    ClearFlag FLAG_HIDE_ROUTE_209_JOGGER_RAUL_NO_BATTLE
    SetFlag FLAG_HIDE_ROUTE_209_JOGGER_RICHARD
    SetFlag FLAG_HIDE_ROUTE_209_JOGGER_RAUL
    End

Route209_PokefanM:
    NPCMessage Route209_Text_ThisIsTheLostTower
    End

Route209_HallowedTower:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    GoToIfEq VAR_HALLOWED_TOWER_STATE, 1, Route209_EncounterSpiritomb
    CheckItem ITEM_ODD_KEYSTONE, 1, VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, Route209_ThereIsABrokenTower
    Message Route209_Text_WouldYouLikeToUseTheOddKeystone
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_YES, Route209_UseOddKeystone
    CloseMessage
    ReleaseAll
    End

Route209_UseOddKeystone:
    BufferPlayerName 0
    Message Route209_Text_PlayerUsedTheOddKeystone
    WaitButton
    RemoveItem ITEM_ODD_KEYSTONE, 1, VAR_RESULT
    SetVar VAR_HALLOWED_TOWER_STATE, 1
    CloseMessage
    ReleaseAll
    End

Route209_EncounterSpiritomb:
    WaitSE SEQ_SE_CONFIRM
    PlayCry SPECIES_SPIRITOMB
    Message Route209_Text_SpiritombCry
    WaitCry
    CloseMessage
    StartWildBattle SPECIES_SPIRITOMB, 70
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, Route209_BlackOut
    SetVar VAR_HALLOWED_TOWER_STATE, 0
    ClearSpiritombCounter
    End

Route209_BlackOut:
    BlackOutFromBattle
    ReleaseAll
    End

Route209_ThereIsABrokenTower:
    Message Route209_Text_ThereIsABrokenTower
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route209_Fisherman:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    SetVar VAR_0x8004, ITEM_GOOD_ROD
    BufferItemNameWithArticle 0, VAR_0x8004
    CapitalizeFirstLetter 0
    GoToIfSet FLAG_GOOD_ROD_OBTAINED, Route209_AskExplainHowToFish
    Message Route209_Text_GoodRodIsReallyGoodWouldntYouAgree
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_YES, Route209_AcceptGoodRod
    GoToIfEq VAR_RESULT, MENU_NO, Route209_RefuseGoodRod
    End

Route209_AskExplainHowToFish:
    BufferItemName 0, VAR_0x8004
    Message Route209_Text_DoINeedToExplainHowToFish
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_YES, Route209_ExplainHowToFish
    GoToIfEq VAR_RESULT, MENU_NO, Route209_WhenYouReelPokemonYouBattleIt
    End

Route209_ExplainHowToFish:
    Message Route209_Text_ExplainHowToFish
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route209_WhenYouReelPokemonYouBattleIt:
    Message Route209_Text_WhenYouReelPokemonYouBattleIt
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route209_RefuseGoodRod:
    Message Route209_Text_YouDontLikeToFish
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route209_AcceptGoodRod:
    Message Route209_Text_TakeThisGoodRod
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route209_ArrowSignpostHearthomeCity:
    ShowArrowSign Route209_Text_SignRt209HearthomeCity
    End

Route209_ArrowSignpostSolaceonTown:
    ShowArrowSign Route209_Text_Rt209SolaceonTown
    End

Route209_TrainerTips:
    ShowScrollingSign Route209_Text_TrainerTipsRegisterKeyItems
    End

Route209_JoggerRichard:
    NPCMessage Route209_Text_DoYouJogEveryMorning
    End

Route209_JoggerRaul:
    NPCMessage Route209_Text_AWildPokemonChasedAfterMe
    End

Route209_JulienTrainerCount:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet FLAG_ROUTE_209_PROMOTIONAL_ITEM_RECIEVED, Route209_PromotionalItemRecieved
    SetVar VAR_JULIEN_TRAINERS_REMAINING 8
    SetVar VAR_PROMOTIONAL_TRAINERS_COUNTED 0
    GoTo Route209_CountTrainers

Route209_CountTrainers:
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 0, Route209_CheckBreederAlbert
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 1, Route209_CheckBreederJennifer
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 2, Route209_CheckCowgirlShelley
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 3, Route209_CheckJoggerRichard
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 4, Route209_CheckJoggerRaul
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 5, Route209_CheckPokeKidDanielle
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 6, Route209_CheckTwinsEmmaAndLil
    GoToIfEq VAR_PROMOTIONAL_TRAINERS_COUNTED, 7, Route209_CheckYoungCoupleTyAndSue
    GoToIfEq VAR_JULIEN_TRAINERS_REMAINING, 1, Route209_JulienTrainerCountSingular
    GoToIfEq VAR_JULIEN_TRAINERS_REMAINING, 0, Route209_WonPromotional
    BufferNumber 0, VAR_JULIEN_TRAINERS_REMAINING
    Message Route209_Text_JulienTrainerCount
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route209_JulienTrainerCountSingular:
    BufferNumber 0, VAR_JULIEN_TRAINERS_REMAINING
    Message Route209_Text_JulienTrainerCountSingular
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route209_PromotionalTrainerDefeated:
    SubVar VAR_JULIEN_TRAINERS_REMAINING 1
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route209_CountTrainers

Route209_WonPromotional:
    Message Route209_Text_PromotionalRouteCongrats
    InitGlobalTextListMenu 30, 13, 0, VAR_RESULT, NO_EXIT_ON_B
    SetMenuXOriginToRight
    AddListMenuEntry MenuEntries_Text_Julien_ProtectivePads, 0
    AddListMenuEntry MenuEntries_Text_Julien_Kasib, 1
    ShowListMenu
    GoToIfEq VAR_RESULT, 0, Route209_GiveProtectivePads
    GoToIfEq VAR_RESULT, 1, Route209_GiveKasibBerry
    End

Route209_GiveProtectivePads:
    SetVar VAR_0x8004, ITEM_PROTECTIVE_PADS
    SetVar VAR_0x8005, 1
    GoToIfCannotFitItem VAR_0x8004, VAR_0x8005, VAR_RESULT, Route209_BagIsFull
    Common_GiveItemQuantity
    SetFlag FLAG_ROUTE_209_PROMOTIONAL_ITEM_RECIEVED
    GoTo Route209_PromotionalItemRecieved

Route209_GiveKasibBerry:
    SetVar VAR_0x8004, ITEM_KASIB_BERRY
    SetVar VAR_0x8005, 5
    GoToIfCannotFitItem VAR_0x8004, VAR_0x8005, VAR_RESULT, Route209_BagIsFull
    Common_GiveItemQuantity
    SetFlag FLAG_ROUTE_209_PROMOTIONAL_ITEM_RECIEVED
    GoTo Route209_PromotionalItemRecieved

Route209_PromotionalItemRecieved:
    Message Route209_Text_WatchOutForMorePromotions
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route209_CheckBreederAlbert:
    CheckTrainerFlag TRAINER_BREEDER_ALBERT
    GoToIfDefeated TRAINER_BREEDER_ALBERT, Route209_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route209_CountTrainers

Route209_CheckBreederJennifer:
    CheckTrainerFlag TRAINER_BREEDER_JENNIFER
    GoToIfDefeated TRAINER_BREEDER_JENNIFER, Route209_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route209_CountTrainers

Route209_CheckCowgirlShelley:
    CheckTrainerFlag TRAINER_COWGIRL_SHELLEY
    GoToIfDefeated TRAINER_COWGIRL_SHELLEY, Route209_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route209_CountTrainers

Route209_CheckJoggerRichard:
    CheckTrainerFlag TRAINER_JOGGER_RICHARD
    GoToIfDefeated TRAINER_JOGGER_RICHARD, Route209_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route209_CountTrainers

Route209_CheckJoggerRaul:
    CheckTrainerFlag TRAINER_JOGGER_RAUL
    GoToIfDefeated TRAINER_JOGGER_RAUL, Route209_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route209_CountTrainers

Route209_CheckPokeKidDanielle:
    CheckTrainerFlag TRAINER_POKE_KID_DANIELLE
    GoToIfDefeated TRAINER_POKE_KID_DANIELLE, Route209_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route209_CountTrainers

Route209_CheckTwinsEmmaAndLil:
    CheckTrainerFlag TRAINER_TWINS_EMMA_AND_LIL
    GoToIfDefeated TRAINER_TWINS_EMMA_AND_LIL, Route209_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route209_CountTrainers

Route209_CheckYoungCoupleTyAndSue:
    CheckTrainerFlag TRAINER_YOUNG_COUPLE_TY_AND_SUE
    GoToIfDefeated TRAINER_YOUNG_COUPLE_TY_AND_SUE, Route209_PromotionalTrainerDefeated
    AddVar VAR_PROMOTIONAL_TRAINERS_COUNTED 1
    GoTo Route209_CountTrainers

Route209_BagIsFull:
    Common_MessageBagIsFull
    CloseMessage
    ReleaseAll
    End

    .balign 4, 0
