#include "macros/scrcmd.inc"
#include "res/text/bank/solaceon_town.h"
#include "res/field/events/events_solaceon_town.h"


    ScriptEntry SolaceonTown_Rancher1
    ScriptEntry SolaceonTown_Cowgirl1
    ScriptEntry SolaceonTown_Twin
    ScriptEntry SolaceonTown_Cowgirl2
    ScriptEntry SolaceonTown_Rancher2
    ScriptEntry SolaceonTown_RuinManiac
    ScriptEntry SolaceonTown_MapSign
    ScriptEntry SolaceonTown_SignPokemonDayCare
    ScriptEntry SolaceonTown_SignPokemonNewsPress
    ScriptEntry SolaceonTown_OnTransition
    ScriptEntry SolaceonTown_OnResume
    ScriptEntry SolaceonTown_TriggerRival
    ScriptEntry SolaceonTown_DrifloonInteract
    ScriptEntry SolaceonTown_Onlooker1
    ScriptEntry SolaceonTown_Onlooker2
    ScriptEntry SolaceonTown_Onlooker3
    ScriptEntry SolaceonTown_Onlooker4
    ScriptEntry SolaceonTown_Onlooker5
    ScriptEntry SolaceonTown_Onlooker6
    ScriptEntry SolaceonTown_Onlooker7
    ScriptEntryEnd

SolaceonTown_OnResume:
    End

SolaceonTown_OnTransition:
    CheckDaycareHasEgg VAR_MAP_LOCAL_0
    GoToIfNe VAR_MAP_LOCAL_0, FALSE, SolaceonTown_SetDayCareManDirEast
    End

SolaceonTown_SetDayCareManDirEast:
    SetObjectEventDir LOCALID_DAY_CARE_MAN, DIR_EAST
    End

SolaceonTown_Rancher1:
    NPCMessage SolaceonTown_Text_BreathingInRefreshingAir
    End

SolaceonTown_Cowgirl1:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfBadgeAcquired BADGE_ID_RELIC, SolaceonTown_TakeATourThroughTheRuins
    Message SolaceonTown_Text_TakeItEasySlowAndCasual
    WaitButton
    CloseMessage
    ReleaseAll
    End

SolaceonTown_TakeATourThroughTheRuins:
    Message SolaceonTown_Text_TakeATourThroughTheRuins
    WaitButton
    CloseMessage
    ReleaseAll
    End

SolaceonTown_Twin:
    NPCMessage SolaceonTown_Text_ImTooLittle
    End

SolaceonTown_Cowgirl2:
    NPCMessage SolaceonTown_Text_EverySundayIVisitTheLostTower
    End

SolaceonTown_Rancher2:
    NPCMessage SolaceonTown_Text_OverTimeTheTownCameToBe
    End

SolaceonTown_RuinManiac:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    CheckPoketchAppRegistered POKETCH_APPID_POKEMONHISTORY, VAR_RESULT
    GoToIfEq VAR_RESULT, TRUE, SolaceonTown_EachPokemonHasItsOwnHistory
    GetLocalDexSeenCount VAR_RESULT
    GoToIfLt VAR_RESULT, 50, SolaceonTown_IfYoureCompetentYoudHaveMetFiftyPokemon
    Message SolaceonTown_Text_ThisHeresAPoketchAppPokemonHistory
    SetVar VAR_0x8004, POKETCH_APPID_POKEMONHISTORY
    Common_GivePoketchApp
    WaitButton
    CloseMessage
    ReleaseAll
    End

SolaceonTown_IfYoureCompetentYoudHaveMetFiftyPokemon:
    Message SolaceonTown_Text_IfYoureCompetentYoudHaveMetFiftyPokemon
    WaitButton
    CloseMessage
    ReleaseAll
    End

SolaceonTown_EachPokemonHasItsOwnHistory:
    Message SolaceonTown_Text_EachPokemonHasItsOwnHistory
    WaitButton
    CloseMessage
    ReleaseAll
    End

SolaceonTown_MapSign:
    ShowMapSign SolaceonTown_Text_MapSign
    End

SolaceonTown_SignPokemonDayCare:
    ShowLandmarkSign SolaceonTown_Text_SignPokemonDayCare
    End

SolaceonTown_SignPokemonNewsPress:
    ShowLandmarkSign SolaceonTown_Text_SignPokemonNewsPress
    End

SolaceonTown_TriggerRival:
    LockAll
    ApplyMovement LOCALID_PLAYER, SolaceonTown_Movement_PlayerNoticeRival
    WaitMovement
    Common_SetRivalBGM
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    SetObjectEventPos LOCALID_RIVAL, VAR_0x8004, 0x295
    ClearFlag FLAG_HIDE_SOLACEON_TOWN_RIVAL
    AddObject LOCALID_RIVAL
    LockObject LOCALID_RIVAL
    ApplyMovement LOCALID_PLAYER, SolaceonTown_Movement_PlayerFaceNorth
    ApplyMovement LOCALID_RIVAL, SolaceonTown_Movement_RivalWalkSouth
    WaitMovement
    Message SolaceonTown_Text_Yahoo
    CloseMessage
    ApplyMovement LOCALID_RIVAL, SolaceonTown_Movement_RivalLookAround
    WaitMovement
    BufferRivalName 0
    BufferPlayerName 1
    Message SolaceonTown_Text_IGotSomethingCool
    ApplyMovement LOCALID_RIVAL, SolaceonTown_Movement_RivalExclamationMark
    WaitMovement
    Message SolaceonTown_Text_CheckOutTheRuins
    CloseMessage
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    CallIfEq VAR_0x8004, 557, SolaceonTown_RivalLeaveFromX557
    CallIfEq VAR_0x8004, 558, SolaceonTown_RivalLeaveFromX558
    CallIfEq VAR_0x8004, 559, SolaceonTown_RivalLeaveFromX559
    CallIfEq VAR_0x8004, 560, SolaceonTown_RivalLeaveFromX560
    CallIfEq VAR_0x8004, 561, SolaceonTown_RivalLeaveFromX561
    CallIfEq VAR_0x8004, 562, SolaceonTown_RivalLeaveFromX562
    CallIfEq VAR_0x8004, 563, SolaceonTown_RivalLeaveFromX563
    WaitMovement
    RemoveObject LOCALID_RIVAL
    Common_FadeToDefaultMusic2
    SetVar VAR_SOLACEON_TOWN_STATE, 1
    ReleaseAll
    End

    .balign 4, 0
SolaceonTown_Movement_RivalWalkSouth:
    WalkFastSouth 7
    EndMovement

    .balign 4, 0
SolaceonTown_Movement_RivalLookAround:
    WalkOnSpotFastWest
    Delay8
    WalkOnSpotFastEast
    Delay8
    WalkOnSpotFastSouth
    EndMovement

    .balign 4, 0
SolaceonTown_Movement_RivalExclamationMark:
    EmoteExclamationMark
    EndMovement

SolaceonTown_RivalLeaveFromX557:
    ApplyMovement LOCALID_RIVAL, SolaceonTown_Movement_RivalLeaveFromX557
    Return

SolaceonTown_RivalLeaveFromX558:
    ApplyMovement LOCALID_RIVAL, SolaceonTown_Movement_RivalLeaveFromX558
    Return

SolaceonTown_RivalLeaveFromX559:
    ApplyMovement LOCALID_RIVAL, SolaceonTown_Movement_RivalLeaveFromX559
    Return

SolaceonTown_RivalLeaveFromX560:
    ApplyMovement LOCALID_RIVAL, SolaceonTown_Movement_RivalLeaveFromX560
    Return

SolaceonTown_RivalLeaveFromX561:
    ApplyMovement LOCALID_RIVAL, SolaceonTown_Movement_RivalLeaveFromX561
    Return

SolaceonTown_RivalLeaveFromX562:
    ApplyMovement LOCALID_RIVAL, SolaceonTown_Movement_RivalLeaveFromX562
    Return

SolaceonTown_RivalLeaveFromX563:
    ApplyMovement LOCALID_RIVAL, SolaceonTown_Movement_RivalLeaveFromX563
    Return

    .balign 4, 0
SolaceonTown_Movement_RivalLeaveFromX557:
    WalkFastEast 3
    WalkFastSouth 9
    EndMovement

    .balign 4, 0
SolaceonTown_Movement_RivalLeaveFromX558:
    WalkFastEast 2
    WalkFastSouth 9
    EndMovement

    .balign 4, 0
SolaceonTown_Movement_RivalLeaveFromX559:
    WalkFastEast 1
    WalkFastSouth 9
    EndMovement

    .balign 4, 0
SolaceonTown_Movement_RivalLeaveFromX560:
    WalkFastSouth 9
    EndMovement

    .balign 4, 0
SolaceonTown_Movement_RivalLeaveFromX561:
    WalkFastWest 1
    WalkFastSouth 9
    EndMovement

    .balign 4, 0
SolaceonTown_Movement_RivalLeaveFromX562:
    WalkFastWest 2
    WalkFastSouth 9
    EndMovement

    .balign 4, 0
SolaceonTown_Movement_RivalLeaveFromX563:
    WalkFastWest 3
    WalkFastSouth 9
    EndMovement

    .balign 4, 0
SolaceonTown_Movement_PlayerNoticeRival:
    Delay8
    EmoteExclamationMark
    Delay8 3
    EndMovement

    .balign 4, 0
SolaceonTown_Movement_PlayerFaceNorth:
    FaceNorth
    EndMovement

    .balign 4, 0

SolaceonTown_DrifloonInteract:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Common_CallDrifloon
    ReleaseAll
    End

SolaceonTown_Onlooker1:
    EventMessage SolaceonTown_Text_OnlookerCowgirl
    End

SolaceonTown_Onlooker2:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message SolaceonTown_Text_OnlookerHiker
    WaitButton
    CloseMessage
    ApplyMovement LOCALID_ONLOOKER_2, SolaceonTown_Movement_OnlookerWatchFight
    WaitMovement
    ReleaseAll
    End

SolaceonTown_Onlooker3:
    EventMessage SolaceonTown_Text_OnlookerYoungster1
    End

SolaceonTown_Onlooker4:
    EventMessage SolaceonTown_Text_OnlookerYoungster2
    End

SolaceonTown_Onlooker5:
    EventMessage SolaceonTown_Text_OnlookerGuitarist
    End

SolaceonTown_Onlooker6:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message SolaceonTown_Text_OnlookerClown
    WaitButton
    CloseMessage
    ApplyMovement LOCALID_ONLOOKER_6, SolaceonTown_Movement_OnlookerWatchFight
    WaitMovement
    ReleaseAll
    End

SolaceonTown_Onlooker7:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message SolaceonTown_Text_OnlookerArtist
    WaitButton
    CloseMessage
    ApplyMovement LOCALID_ONLOOKER_7, SolaceonTown_Movement_OnlookerWatchFight
    WaitMovement
    ReleaseAll
    End

    .balign 4, 0
SolaceonTown_Movement_OnlookerWatchFight:
    FaceNorth
    EndMovement
