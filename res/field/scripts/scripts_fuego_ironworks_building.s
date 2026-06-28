#include "macros/scrcmd.inc"
#include "res/text/bank/fuego_ironworks_building.h"
#include "res/text/bank/menu_entries.h"


    ScriptEntry FuegoIronworksBuilding_OnTransition
    ScriptEntry FuegoIronworksBuilding_MrFuego
    ScriptEntry FuegoIronworksBuilding_Scyther
    ScriptEntryEnd

FuegoIronworksBuilding_OnTransition:
    SetFlag FLAG_FIRST_ARRIVAL_FUEGO_IRONWORKS
    End

FuegoIronworksBuilding_MrFuego:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet FLAG_CUT_UNLOCKED, FuegoIronworksBuilding_AlreadyBeaten
    Message FuegoIronworksBuilding_Text_FuegoChallenge
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_YES, FuegoIronworksBuilding_FuegoBattle
    GoToIfEq VAR_RESULT, MENU_NO, FuegoIronworksBuilding_FuegoDecline
    End

FuegoIronworksBuilding_FuegoBattle:
    Message FuegoIronworksBuilding_Text_FuegoAccept
    WaitButton
    CloseMessage
    StartTrainerBattle TRAINER_MR_FUEGO, TRAINER_NONE
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, FuegoIronworksBuilding_FuegoBattleLost
    SetFlag FLAG_CUT_UNLOCKED
    Message FuegoIronworksBuilding_Text_FuegoDefeat
    WaitButton
    Message FuegoIronworksBuilding_Text_FuegoGrantsCut
    GoTo FuegoIronworksBuilding_MrFuegoEnd
    End

FuegoIronworksBuilding_FuegoBattleLost:
    BlackOutFromBattle
    ReleaseAll
    End

FuegoIronworksBuilding_FuegoDecline:
    Message FuegoIronworksBuilding_Text_FuegoDecline
    GoTo FuegoIronworksBuilding_MrFuegoEnd
    End

FuegoIronworksBuilding_AlreadyBeaten:
    Message FuegoIronworksBuilding_Text_AlreadyBeaten
    GoTo FuegoIronworksBuilding_MrFuegoEnd
    End

FuegoIronworksBuilding_MrFuegoEnd:
    WaitButton
    CloseMessage
    ReleaseAll
    End

FuegoIronworksBuilding_Scyther:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    PlayCry SPECIES_SCYTHER
    Message FuegoIronworksBuilding_Text_ScytherCry
    WaitButton
    WaitCry
    CloseMessage
    ReleaseAll
    End

    .balign 4, 0
