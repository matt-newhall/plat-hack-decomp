#include "macros/scrcmd.inc"
#include "res/text/bank/survival_area_south_house.h"


    ScriptEntry SurvivalAreaSouthHouse_BlackBelt
    ScriptEntry SurvivalAreaSouthHouse_RotomPC
    ScriptEntryEnd

SurvivalAreaSouthHouse_BlackBelt:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet FLAG_FOUGHT_ROTOM_SURVIVAL_AREA, SurvivalAreaSouthHouse_BlackBelt_GiveFacade
    Message SurvivalAreaSouthHouse_Text_FacadeTMGoToPC
    WaitButton
    CloseMessage
    ReleaseAll
    End

SurvivalAreaSouthHouse_BlackBelt_GiveFacade:
    GoToIfSet FLAG_RECEIVED_SURVIVAL_AREA_SOUTH_HOUSE_TM42, SurvivalAreaSouthHouse_ExplainFacade
    Message SurvivalAreaSouthHouse_Text_YouWantTM
    WaitButton
    SetVar VAR_0x8004, ITEM_TM42
    SetVar VAR_0x8005, 1
    GoToIfCannotFitItem VAR_0x8004, VAR_0x8005, VAR_RESULT, SurvivalAreaSouthHouse_BagIsFull
    Common_GiveItemQuantity
    SetFlag FLAG_RECEIVED_SURVIVAL_AREA_SOUTH_HOUSE_TM42
    GoTo SurvivalAreaSouthHouse_ExplainFacade

SurvivalAreaSouthHouse_ExplainFacade:
    Message SurvivalAreaSouthHouse_Text_ExplainFacade
    WaitButton
    CloseMessage
    ReleaseAll
    End

SurvivalAreaSouthHouse_BagIsFull:
    Common_MessageBagIsFull
    CloseMessage
    ReleaseAll
    End

SurvivalAreaSouthHouse_RotomPC:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    GoToIfSet FLAG_FOUGHT_ROTOM_SURVIVAL_AREA, SurvivalAreaSouthHouse_RotomPC_Fought
    Message SurvivalAreaSouthHouse_Text_RotomPCBeforeFight
    ShowYesNoMenu VAR_0x8008
    GoToIfEq VAR_0x8008, 1, SurvivalAreaSouthHouse_RotomPC_StartFight

SurvivalAreaSouthHouse_RotomPC_StartFight:
    BufferPlayerName 0
    Message SurvivalAreaSouthHouse_Text_RotomPCConfirmFight
    CloseMessage
    PlayCry SPECIES_ROTOM
    WaitCry
    StartWildBattle SPECIES_ROTOM, 60
    CheckWonBattle VAR_RESULT
    SetFlag FLAG_FOUGHT_ROTOM_SURVIVAL_AREA
    GoToIfEq VAR_RESULT, FALSE, SurvivalAreaSouthHouse_BlackOut
    CheckDidNotCapture VAR_RESULT
    GoToIfEq VAR_RESULT, TRUE, SurvivalAreaSouthHouse_RotomPC_Failed
    ReleaseAll
    End

SurvivalAreaSouthHouse_RotomPC_Fought:
    Message SurvivalAreaSouthHouse_Text_RotomPCAfterFight
    WaitButton
    CloseMessage
    ReleaseAll
    End

SurvivalAreaSouthHouse_RotomPC_Failed:
    Message SurvivalAreaSouthHouse_Text_RotomPCFailCatch
    WaitButton
    CloseMessage
    ReleaseAll
    End

SurvivalAreaSouthHouse_BlackOut:
    BlackOutFromBattle
    ReleaseAll
    End
