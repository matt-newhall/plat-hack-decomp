#include "macros/scrcmd.inc"
#include "res/text/bank/route_210_south.h"
#include "res/text/bank/menu_entries.h"
#include "res/field/events/events_route_210_south.h"


    ScriptEntry Route210South_Psyduck
    ScriptEntry Route210South_Unused
    ScriptEntry Route210South_AceTrainerF
    ScriptEntry Route210South_SignCafeCabin
    ScriptEntry Route210South_ArrowSignpostSolaceonTown
    ScriptEntry Route210South_JoggerWyatt
    ScriptEntry Route210South_OnTransition
    ScriptEntry Route210South_LeaderExhibition
    ScriptEntry Route210South_Commentator
    ScriptEntryEnd

Route210South_OnTransition:
    GetTimeOfDay VAR_MAP_LOCAL_0
    GoToIfEq VAR_MAP_LOCAL_0, TIMEOFDAY_MORNING, Route210South_SetJoggerBattle
    GoToIfInRange VAR_MAP_LOCAL_0, TIMEOFDAY_DAY, TIMEOFDAY_LATE_NIGHT, Route210South_SetJoggerNoBattle
    End

Route210South_SetJoggerBattle:
    ClearFlag FLAG_HIDE_ROUTE_210_SOUTH_JOGGER_WYATT
    SetFlag FLAG_HIDE_ROUTE_210_SOUTH_JOGGER_WYATT_NO_BATTLE
    End

Route210South_SetJoggerNoBattle:
    ClearFlag FLAG_HIDE_ROUTE_210_SOUTH_JOGGER_WYATT_NO_BATTLE
    SetFlag FLAG_HIDE_ROUTE_210_SOUTH_JOGGER_WYATT
    End

Route210South_Psyduck:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    CheckItem ITEM_SECRETPOTION, 1, VAR_RESULT
    GoToIfEq VAR_RESULT, TRUE, Route210South_AskUseSecretPotion
    Message Route210South_Text_PsyduckAreStandingFirm
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route210South_AskUseSecretPotion:
    Message Route210South_Text_AskUseSecretPotion
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_YES, Route210South_UseSecretPotion
    GoToIfEq VAR_RESULT, MENU_NO, Route210South_DontUseSecretPotion
    End

Route210South_DontUseSecretPotion:
    CloseMessage
    ReleaseAll
    End

Route210South_UseSecretPotion:
    BufferPlayerName 0
    BufferItemName 1, ITEM_SECRETPOTION
    Message Route210South_Text_PlayerUsedTheSecretPotion
    CloseMessage
    PlayCry SPECIES_PSYDUCK
    WaitCry
    ApplyMovement LOCALID_PSYDUCK_3, Route210South_Movement_PsyduckExclamationMark
    ApplyMovement LOCALID_PSYDUCK_4, Route210South_Movement_PsyduckExclamationMark
    ApplyMovement LOCALID_PSYDUCK_2, Route210South_Movement_PsyduckExclamationMark
    ApplyMovement LOCALID_PSYDUCK_1, Route210South_Movement_PsyduckExclamationMark
    WaitMovement
    ApplyMovement LOCALID_PSYDUCK_3, Route210South_Movement_Psyduck3Leave
    ApplyMovement LOCALID_PSYDUCK_4, Route210South_Movement_Psyduck4Leave
    ApplyMovement LOCALID_PSYDUCK_2, Route210South_Movement_Psyduck2Leave
    ApplyMovement LOCALID_PSYDUCK_1, Route210South_Movement_Psyduck1Leave
    WaitMovement
    RemoveObject LOCALID_PSYDUCK_3
    RemoveObject LOCALID_PSYDUCK_4
    RemoveObject LOCALID_PSYDUCK_2
    RemoveObject LOCALID_PSYDUCK_1
    WaitTime 45, VAR_RESULT
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    GoToIfEq VAR_0x8004, 560, Route210South_SetCynthiaPositionX560
    GoToIfEq VAR_0x8004, 561, Route210South_SetCynthiaPositionX561
    End

Route210South_SetCynthiaPositionX560:
    SetObjectEventPos LOCALID_CYNTHIA, 560, 596
    SetObjectEventMovementType LOCALID_CYNTHIA, MOVEMENT_TYPE_LOOK_NORTH
    GoTo Route210South_CynthiaEnter

Route210South_SetCynthiaPositionX561:
    SetObjectEventPos LOCALID_CYNTHIA, 561, 596
    SetObjectEventMovementType LOCALID_CYNTHIA, MOVEMENT_TYPE_LOOK_NORTH
    GoTo Route210South_CynthiaEnter

Route210South_CynthiaEnter:
    ClearFlag FLAG_HIDE_ROUTE_210_SOUTH_CYNTHIA
    AddObject LOCALID_CYNTHIA
    LockObject LOCALID_CYNTHIA
    ApplyMovement LOCALID_CYNTHIA, Route210South_Movement_CynthiaEnter
    WaitMovement
    ApplyMovement LOCALID_PLAYER, Route210South_Movement_PlayerWalkOnSpotSouth
    WaitMovement
    Message Route210South_Text_DeliverThisOldCharm
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_YES, Route210South_AcceptOldCharm
    GoToIfEq VAR_RESULT, MENU_NO, Route210South_RefuseOldCharm
    End

Route210South_RefuseOldCharm:
    Message Route210South_Text_WillYouGoToCelestic
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_YES, Route210South_AcceptOldCharm
    GoToIfEq VAR_RESULT, MENU_NO, Route210South_RefuseOldCharm
    End

Route210South_AcceptOldCharm:
    SetVar VAR_0x8004, ITEM_OLD_CHARM
    SetVar VAR_0x8005, 1
    Common_GiveItemQuantity
    Message Route210South_Text_ImCountingOnYou
    CloseMessage
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    GoToIfEq VAR_0x8004, 560, Route210South_CynthiaLeaveX560
    GoToIfEq VAR_0x8004, 561, Route210South_CynthiaLeaveX561
    End

Route210South_CynthiaLeaveX560:
    ApplyMovement LOCALID_CYNTHIA, Route210South_Movement_CynthiaLeaveX560
    WaitMovement
    GoTo Route210South_RemoveCynthia

Route210South_CynthiaLeaveX561:
    ApplyMovement LOCALID_CYNTHIA, Route210South_Movement_CynthiaLeaveX561
    WaitMovement
    GoTo Route210South_RemoveCynthia

Route210South_RemoveCynthia:
    RemoveObject LOCALID_CYNTHIA
    SetFlag FLAG_USED_SECRETPOTION
    ReleaseAll
    End

    .balign 4, 0
Route210South_Movement_PsyduckExclamationMark:
    EmoteExclamationMark
    Delay8 4
    EndMovement

    .balign 4, 0
Route210South_Movement_Psyduck3Leave:
    WalkNormalNorth
    WalkOnSpotNormalSouth
    Delay8 8
    WalkNormalNorth 8
    EndMovement

    .balign 4, 0
Route210South_Movement_Psyduck4Leave:
    WalkNormalNorth 2
    WalkOnSpotNormalSouth 2
    Delay8 6
    WalkNormalNorth 8
    EndMovement

    .balign 4, 0
Route210South_Movement_Psyduck2Leave:
    WalkOnSpotNormalEast
    WalkOnSpotNormalWest
    WalkOnSpotNormalEast
    Delay8 2
    WalkOnSpotNormalNorth
    WalkFastNorth 2
    Delay8 2
    WalkNormalWest 3
    WalkOnSpotNormalEast
    EmoteExclamationMark
    WalkFastEast 3
    WalkFastNorth 8
    EndMovement

    .balign 4, 0
Route210South_Movement_Psyduck1Leave:
    WalkNormalNorth 2
    Delay8 8
    WalkNormalNorth 8
    EndMovement

    .balign 4, 0
Route210South_Movement_CynthiaEnter:
    WalkNormalNorth 7
    EndMovement

    .balign 4, 0
Route210South_Movement_CynthiaLeaveX560:
    WalkNormalSouth 9
    EndMovement

    .balign 4, 0
Route210South_Movement_CynthiaLeaveX561:
    WalkNormalSouth 9
    EndMovement

    .balign 4, 0
Route210South_Movement_PlayerWalkOnSpotSouth:
    WalkOnSpotNormalSouth
    EndMovement

Route210South_UnusedMovement:
    Delay8
    WalkOnSpotNormalEast
    Delay8
    WalkOnSpotNormalNorth
    EndMovement

Route210South_UnusedMovement2:
    Delay8
    WalkOnSpotNormalWest
    Delay8
    WalkOnSpotNormalNorth
    EndMovement

Route210South_Unused:
    NPCMessage Route210South_Text_Dummy6
    End

Route210South_AceTrainerF:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet FLAG_RECEIVED_ROUTE_210_SOUTH_TM51, Route210South_BirdPokemonWouldCrash
    Message Route210South_Text_YouShouldRestToo
    SetVar VAR_0x8004, ITEM_TM51
    SetVar VAR_0x8005, 1
    GoToIfCannotFitItem VAR_0x8004, VAR_0x8005, VAR_RESULT, Route210South_BagIsFull
    Common_GiveItemQuantity
    SetFlag FLAG_RECEIVED_ROUTE_210_SOUTH_TM51
    GoTo Route210South_BirdPokemonWouldCrash

Route210South_BirdPokemonWouldCrash:
    Message Route210South_Text_BirdPokemonWouldCrash
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route210South_BagIsFull:
    Common_MessageBagIsFull
    CloseMessage
    ReleaseAll
    End

Route210South_SignCafeCabin:
    ShowLandmarkSign Route210South_Text_SignCafeCabin
    End

Route210South_ArrowSignpostSolaceonTown:
    ShowArrowSign Route210South_Text_SignRt210SolaceonTown
    End

Route210South_JoggerWyatt:
    NPCMessage Route210South_Text_WellKeepOnRunning
    End

Route210South_LeaderExhibition:
    GetPlayerMapPos VAR_0x8000, VAR_0x8001
    AddFreeCamera VAR_0x8000, VAR_0x8001
    CallIfEq VAR_0x8000, 565, Route210South_ExhibitionCameraPanFrom565
    CallIfEq VAR_0x8000, 566, Route210South_ExhibitionCameraPanFrom566
    CallIfEq VAR_0x8000, 567, Route210South_ExhibitionCameraPanFrom567
    Message Route210South_Text_ExhibitionWinnerWhitney
    WaitButton
    CloseMessage
    FadeScreenOut
    WaitFadeScreen
    ApplyMovement LOCALID_MILTANK, Route210South_Movement_LeaderVanish
    ApplyMovement LOCALID_PIDGEOT, Route210South_Movement_LeaderVanish
    WaitMovement
    FadeScreenIn
    WaitFadeScreen
    ApplyMovement LOCALID_WHITNEY, Route210South_Movement_FaceEast
    ApplyMovement LOCALID_FALKNER, Route210South_Movement_FaceWest
    WaitMovement
    LockAll
    Message Route210South_Text_FalknerThanks
    WaitButton
    CloseMessage
    Message Route210South_Text_WhitneyThanks
    WaitButton
    CloseMessage
    ApplyMovement LOCALID_COMMENTATOR, Route210South_Movement_CommentatorNoticePlayer
    WaitMovement
    Message Route210South_Text_CommentatorCallOver
    WaitButton
    CloseMessage
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    CallIfEq VAR_0x8004, 565, Route210South_ExhibitionPlayerApproach565
    CallIfEq VAR_0x8004, 566, Route210South_ExhibitionPlayerApproach566
    CallIfEq VAR_0x8004, 567, Route210South_ExhibitionPlayerApproach567
    Message Route210South_Text_CommentatorGreet5Badges
    WaitButton
    CloseMessage
    ApplyMovement LOCALID_FALKNER, Route210South_Movement_FalknerApproachPlayer
    ApplyMovement LOCALID_WHITNEY, Route210South_Movement_WhitneyApproachPlayer
    ApplyFreeCameraMovement Route210South_Movement_CameraFollowToPlayer
    WaitMovement
    Message Route210South_Text_CommentatorPrizeBattle
    InitGlobalTextMenu 1, 1, 0, VAR_RESULT, FALSE
    AddMenuEntry MenuEntries_Text_Route210Leaders_Falkner, 0
    AddMenuEntry MenuEntries_Text_Route210Leaders_Whitney, 1
    ShowMenu
    GoToIfEq VAR_RESULT, 0, Route210South_ExhibitionFightFalkner
    GoToIfEq VAR_RESULT, 1, Route210South_ExhibitionFightWhitney
    End

Route210South_ExhibitionCameraPanFrom565:
    ApplyFreeCameraMovement Route210South_Movement_CameraPanFrom565
    WaitMovement
    Return

Route210South_ExhibitionCameraPanFrom566:
    ApplyFreeCameraMovement Route210South_Movement_CameraPanFrom566
    WaitMovement
    Return

Route210South_ExhibitionCameraPanFrom567:
    ApplyFreeCameraMovement Route210South_Movement_CameraPanFrom567
    WaitMovement
    Return

Route210South_ExhibitionPlayerApproach565:
    ApplyMovement LOCALID_PLAYER, Route210South_Movement_PlayerApproach565
    WaitMovement
    Return

Route210South_ExhibitionPlayerApproach566:
    ApplyMovement LOCALID_PLAYER, Route210South_Movement_PlayerApproach566
    WaitMovement
    Return

Route210South_ExhibitionPlayerApproach567:
    ApplyMovement LOCALID_PLAYER, Route210South_Movement_PlayerApproach567
    WaitMovement
    Return

Route210South_ExhibitionFightFalkner:
    CloseMessage
    SetVar VAR_0x8006, 0
    ApplyMovement LOCALID_FALKNER, Route210South_Movement_FalknerToFight
    ApplyMovement LOCALID_PLAYER, Route210South_Movement_PlayerToFight
    ApplyFreeCameraMovement Route210South_Movement_CameraToFight
    WaitMovement
    GoTo Route210South_ExhibitionSetupBattle

Route210South_ExhibitionFightWhitney:
    CloseMessage
    SetVar VAR_0x8006, 1
    ApplyMovement LOCALID_FALKNER, Route210South_Movement_FalknerStepAside
    WaitMovement
    ApplyMovement LOCALID_WHITNEY, Route210South_Movement_WhitneyToFight
    ApplyMovement LOCALID_PLAYER, Route210South_Movement_PlayerToFight
    ApplyFreeCameraMovement Route210South_Movement_CameraToFight
    WaitMovement
    GoTo Route210South_ExhibitionSetupBattle

Route210South_ExhibitionSetupBattle:
    WaitTime 30, VAR_RESULT
    FadeScreenOut
    WaitFadeScreen
    CallIfEq VAR_0x8006, 0, Route210South_ExhibitionSendOutPidgeot
    CallIfEq VAR_0x8006, 1, Route210South_ExhibitionSendOutMiltank
    SetPosition LOCALID_COMMENTATOR, 561, 0, 632, DIR_SOUTH
    ApplyMovement LOCALID_COMMENTATOR, Route210South_Movement_SpectatorFaceSouth
    WaitMovement
    CheckHasFollower VAR_RESULT
    CallIfEq VAR_RESULT, TRUE, Route210South_ExhibitionPlaceFollower
    FadeScreenIn
    WaitFadeScreen
    GoToIfEq VAR_0x8006, 0, Route210South_ExhibitionBattleFalkner
    GoToIfEq VAR_0x8006, 1, Route210South_ExhibitionBattleWhitney
    End

Route210South_ExhibitionSendOutPidgeot:
    SetPosition LOCALID_PIDGEOT, 559, 0, 634, DIR_EAST
    SetPosition LOCALID_WHITNEY, 559, 0, 632, DIR_SOUTH
    ApplyMovement LOCALID_PIDGEOT, Route210South_Movement_SendOutReveal
    ApplyMovement LOCALID_WHITNEY, Route210South_Movement_SpectatorFaceSouth
    WaitMovement
    Return

Route210South_ExhibitionSendOutMiltank:
    SetPosition LOCALID_MILTANK, 559, 0, 634, DIR_EAST
    SetPosition LOCALID_FALKNER, 559, 0, 632, DIR_SOUTH
    ApplyMovement LOCALID_MILTANK, Route210South_Movement_SendOutReveal
    ApplyMovement LOCALID_FALKNER, Route210South_Movement_SpectatorFaceSouth
    WaitMovement
    Return

Route210South_ExhibitionPlaceFollower:
    ApplyMovement LOCALID_FOLLOWER, Route210South_Movement_FollowerToFightSpot
    WaitMovement
    Return

Route210South_ExhibitionBattleFalkner:
    Message Route210South_Text_FalknerLetsGo
    WaitButton
    CloseMessage
    StartTrainerBattle TRAINER_LEADER_FALKNER
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, Route210South_ExhibitionBlackOut
    SetTrainerFlag TRAINER_LEADER_FALKNER
    GoTo Route210South_ExhibitionVictory

Route210South_ExhibitionBattleWhitney:
    Message Route210South_Text_WhitneyLetsGo
    WaitButton
    CloseMessage
    StartTrainerBattle TRAINER_LEADER_WHITNEY
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, Route210South_ExhibitionBlackOut
    SetTrainerFlag TRAINER_LEADER_WHITNEY
    GoTo Route210South_ExhibitionVictory

Route210South_ExhibitionBlackOut:
    RestoreCamera
    BlackOutFromBattle
    ReleaseAll
    End

Route210South_ExhibitionVictory:
    FadeScreenOut
    WaitFadeScreen
    RemoveObject LOCALID_PIDGEOT
    RemoveObject LOCALID_MILTANK
    CheckHasFollower VAR_RESULT
    CallIfEq VAR_RESULT, TRUE, Route210South_ExhibitionFollowerBehind
    FadeScreenIn
    WaitFadeScreen
    CallIfEq VAR_0x8006, 0, Route210South_ExhibitionRewardFalkner
    CallIfEq VAR_0x8006, 1, Route210South_ExhibitionRewardWhitney
    Message Route210South_Text_CommentatorVictoryComment
    WaitButton
    CloseMessage
    ApplyMovement LOCALID_FALKNER, Route210South_Movement_LeaderLeaveSouth
    ApplyMovement LOCALID_WHITNEY, Route210South_Movement_LeaderLeaveSouth
    ApplyMovement LOCALID_COMMENTATOR, Route210South_Movement_LeaderLeaveSouth
    ApplyMovement LOCALID_ONLOOKER_1, Route210South_Movement_OnlookerLeaveSouth
    ApplyMovement LOCALID_ONLOOKER_2, Route210South_Movement_OnlookerLeaveSouth
    ApplyMovement LOCALID_ONLOOKER_3, Route210South_Movement_OnlookerLeaveSouth
    ApplyMovement LOCALID_ONLOOKER_4, Route210South_Movement_OnlookerLeaveSouth
    ApplyMovement LOCALID_ONLOOKER_5, Route210South_Movement_OnlookerLeaveSouth
    ApplyMovement LOCALID_ONLOOKER_6, Route210South_Movement_OnlookerLeaveSouth
    ApplyMovement LOCALID_ONLOOKER_7, Route210South_Movement_OnlookerLeaveSouth
    WaitMovement
    RemoveObject LOCALID_FALKNER
    RemoveObject LOCALID_WHITNEY
    RemoveObject LOCALID_COMMENTATOR
    RemoveObject LOCALID_ONLOOKER_1
    RemoveObject LOCALID_ONLOOKER_2
    RemoveObject LOCALID_ONLOOKER_3
    RemoveObject LOCALID_ONLOOKER_4
    RemoveObject LOCALID_ONLOOKER_5
    RemoveObject LOCALID_ONLOOKER_6
    RemoveObject LOCALID_ONLOOKER_7
    SetFlag FLAG_HIDE_JOHTO_LEADER_BATTLE_SOLACEON_TOWN
    SetVar VAR_ROUTE_210_SOUTH_STATE, 1
    RestoreCamera
    ReleaseAll
    End

Route210South_ExhibitionFollowerBehind:
    ApplyMovement LOCALID_FOLLOWER, Route210South_Movement_FollowerBehindPlayer
    WaitMovement
    Return

Route210South_ExhibitionRewardFalkner:
    ApplyMovement LOCALID_FALKNER, Route210South_Movement_LeaderWalkUp
    WaitMovement
    Message Route210South_Text_FalknerThanksReward
    WaitButton
    CloseMessage
    SetVar VAR_0x8004, ITEM_TM08
    SetVar VAR_0x8005, 1
    Common_GiveItemQuantity
    Return

Route210South_ExhibitionRewardWhitney:
    ApplyMovement LOCALID_WHITNEY, Route210South_Movement_LeaderWalkUp
    WaitMovement
    Message Route210South_Text_WhitneyThanksReward
    WaitButton
    CloseMessage
    SetVar VAR_0x8004, ITEM_TM42
    SetVar VAR_0x8005, 1
    Common_GiveItemQuantity
    Return

Route210South_Commentator:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message Route210South_Text_CommentatorIdle
    WaitButton
    CloseMessage
    ReleaseAll
    End

    .balign 4, 0
Route210South_Movement_CameraPanFrom565:
    Delay8
    WalkNormalSouth 6
    WalkNormalWest 2
    EndMovement

    .balign 4, 0
Route210South_Movement_CameraPanFrom566:
    Delay8
    WalkNormalSouth 6
    WalkNormalWest 3
    EndMovement

    .balign 4, 0
Route210South_Movement_CameraPanFrom567:
    Delay8
    WalkNormalSouth 6
    WalkNormalWest 4
    EndMovement

    .balign 4, 0
Route210South_Movement_CameraFollowToPlayer:
    WalkNormalEast 3
    WalkNormalNorth 2
    EndMovement

    .balign 4, 0
Route210South_Movement_PlayerToFight:
    WalkNormalWest 4
    WalkNormalSouth 3
    FaceWest
    EndMovement

    .balign 4, 0
Route210South_Movement_FalknerToFight:
    WalkNormalWest 6
    WalkNormalSouth 3
    FaceEast
    EndMovement

    .balign 4, 0
Route210South_Movement_WhitneyToFight:
    WalkNormalWest 6
    WalkNormalSouth 2
    FaceEast
    EndMovement

    .balign 4, 0
Route210South_Movement_FalknerStepAside:
    WalkNormalNorth
    EndMovement

    .balign 4, 0
Route210South_Movement_CameraToFight:
    WalkNormalWest 6
    WalkNormalSouth 3
    EndMovement

    .balign 4, 0
Route210South_Movement_SendOutReveal:
    SetVisible
    FaceEast
    EndMovement

    .balign 4, 0
Route210South_Movement_SpectatorFaceSouth:
    FaceSouth
    EndMovement

    .balign 4, 0
Route210South_Movement_LeaderWalkUp:
    WalkNormalEast 3
    EndMovement

    .balign 4, 0
Route210South_Movement_FollowerBehindPlayer:
    WalkNormalEast 2
    FaceWest
    EndMovement

    .balign 4, 0
Route210South_Movement_FollowerToFightSpot:
    WalkNormalWest
    WalkNormalSouth
    FaceWest
    EndMovement

    .balign 4, 0
Route210South_Movement_LeaderVanish:
    SetInvisible
    EndMovement

    .balign 4, 0
Route210South_Movement_FaceEast:
    FaceEast
    EndMovement

    .balign 4, 0
Route210South_Movement_FaceWest:
    FaceWest
    EndMovement

    .balign 4, 0
Route210South_Movement_CommentatorNoticePlayer:
    FaceNorth
    EmoteExclamationMark
    EndMovement

    .balign 4, 0
Route210South_Movement_PlayerApproach565:
    WalkNormalEast
    WalkNormalSouth 4
    EndMovement

    .balign 4, 0
Route210South_Movement_PlayerApproach566:
    WalkNormalSouth 4
    EndMovement

    .balign 4, 0
Route210South_Movement_PlayerApproach567:
    WalkNormalWest
    WalkNormalSouth 4
    EndMovement

    .balign 4, 0
Route210South_Movement_FalknerApproachPlayer:
    WalkNormalNorth 3
    WalkNormalEast 2
    FaceEast
    EndMovement

    .balign 4, 0
Route210South_Movement_WhitneyApproachPlayer:
    WalkNormalNorth 2
    WalkNormalEast 6
    FaceEast
    EndMovement

    .balign 4, 0
Route210South_Movement_LeaderLeaveSouth:
    WalkFastSouth 10
    EndMovement

    .balign 4, 0
Route210South_Movement_OnlookerLeaveSouth:
    WalkFastSouth 6
    EndMovement

    .balign 4, 0
