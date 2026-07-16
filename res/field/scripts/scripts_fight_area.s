#include "macros/scrcmd.inc"
#include "res/text/bank/fight_area.h"
#include "res/field/events/events_fight_area.h"


    ScriptEntry FightArea_OnFrameRival
    ScriptEntry FightArea_AceTrainerM1
    ScriptEntry FightArea_AceTrainerF1
    ScriptEntry FightArea_PokemonBreederM
    ScriptEntry FightArea_Twin
    ScriptEntry FightArea_BattleGirl1
    ScriptEntry FightArea_Sailor1
    ScriptEntry FightArea_Fisherman
    ScriptEntry FightArea_MapSign
    ScriptEntry FightArea_ArrowSignpostBattleFrontier
    ScriptEntry FightArea_ArrowSignpostRt225
    ScriptEntry FightArea_Sailor2
    ScriptEntry FightArea_BlackBelt1
    ScriptEntry FightArea_OnTransition
    ScriptEntry FightArea_Buck
    ScriptEntry FightArea_DrifloonInteract
    ScriptEntry FightArea_Palmer
    ScriptEntry FightArea_TriggerPalmerBlockFrontier
    ScriptEntryEnd

FightArea_OnTransition:
    GoToIfGe VAR_STARK_MOUNTAIN_ROOM_3_STATE, 1, FightArea_HideRival
    End

FightArea_HideRival:
    SetFlag FLAG_HIDE_FIGHT_AREA_RIVAL
    End

FightArea_CheckForWeekend_Unused:
    GetDayOfWeek VAR_MAP_LOCAL_0
    GoToIfEq VAR_MAP_LOCAL_0, DAY_OF_WEEK_SUNDAY, FightArea_ActivateRivalFight_Unused
    GoToIfEq VAR_MAP_LOCAL_0, DAY_OF_WEEK_SATURDAY, FightArea_ActivateRivalFight_Unused
    End

FightArea_ActivateRivalFight_Unused:
    SetObjectEventPos LOCALID_RIVAL, 658, 430
    SetObjectEventMovementType LOCALID_RIVAL, MOVEMENT_TYPE_LOOK_SOUTH
    SetObjectEventDir LOCALID_RIVAL, DIR_SOUTH
    ClearFlag FLAG_HIDE_FIGHT_AREA_RIVAL
    End

FightArea_OnFrameRival:
    LockAll
    ScrCmd_32D
    ApplyMovement LOCALID_RIVAL, FightArea_Movement_RivalNoticePlayer
    WaitMovement
    ApplyMovement LOCALID_PLAYER, FightArea_Movement_PlayerWalkToRival
    WaitMovement
    BufferRivalName 0
    BufferPlayerName 1
    Message FightArea_Text_ComeWithMe
    CloseMessage
    Common_SetFollowMeBGM
    ApplyMovement LOCALID_PLAYER, FightArea_Movement_PlayerWalkToPokecenter
    ApplyMovement LOCALID_RIVAL, FightArea_Movement_RivalWalkToPokecenter
    WaitMovement
    BufferRivalName 0
    Message FightArea_Text_WhereAreTheDrifloon
    WaitButton
    CloseMessage
    ApplyMovement LOCALID_PLAYER, FightArea_Movement_PlayerWalkToFrontierGate
    ApplyMovement LOCALID_RIVAL, FightArea_Movement_RivalWalkToFrontierGate
    WaitMovement
    Common_FadeToDefaultMusic3
    SetVar VAR_FIGHT_AREA_STATE, 1
    ScrCmd_32E
    ApplyMovement LOCALID_RIVAL, FightArea_Movement_RivalFacePlayer
    ApplyMovement LOCALID_PLAYER, FightArea_Movement_PlayerFaceRival
    WaitMovement
    BufferRivalName 0
    Message FightArea_Text_ImOffToTheFronti
    SetObjectEventPos LOCALID_PALMER, 655, 423
    ClearFlag FLAG_HIDE_FIGHT_AREA_PALMER
    AddObject LOCALID_PALMER
    StopSE SEQ_SE_CONFIRM
    PlaySE SEQ_SE_DP_WALL_HIT2
    MessageInstant FightArea_Text_BigThud
    ApplyMovement LOCALID_PALMER, FightArea_Movement_PalmerEnter
    ApplyMovement LOCALID_RIVAL, FightArea_Movement_RivalGetPushedBack
    ApplyMovement LOCALID_PLAYER, FightArea_Movement_PlayerFaceRivalThenPalmer
    WaitMovement
    ApplyMovement LOCALID_PALMER, FightArea_Movement_PalmerLookAround
    WaitMovement
    Message FightArea_Text_WhatsThisAllAbout
    CloseMessage
    BufferRivalName 0
    Message FightArea_Text_WhatTheDaddy
    CloseMessage
    ApplyMovement LOCALID_RIVAL, FightArea_Movement_RivalWalkToPalmer
    WaitMovement
    BufferRivalName 0
    BufferPlayerName 1
    Message FightArea_Text_IfItIsntRival
    Message FightArea_Text_LookingForwardToChallenge
    CloseMessage
    ApplyMovement LOCALID_RIVAL, FightArea_Movement_RivalLookWest
    ApplyMovement LOCALID_PLAYER, FightArea_Movement_PlayerLookEast
    BufferRivalName 0
    Message FightArea_Text_DadIsTowerTycoon
    Message FightArea_Text_WhatToDo
    Message FightArea_Text_GoingToGetStronger
    CloseMessage
    ApplyMovement LOCALID_RIVAL, FightArea_Movement_RivalLeave
    ApplyMovement LOCALID_PLAYER, FightArea_Movement_PlayerWatchRivalLeave
    WaitMovement
    RemoveObject LOCALID_RIVAL
    ApplyMovement LOCALID_BUCK, FightArea_Movement_BuckWalkToPlayer
    ApplyMovement LOCALID_PLAYER, FightArea_Movement_PlayerFaceBuck
    WaitMovement
    Message FightArea_Text_ComeToSurvivalArea
    CloseMessage
    ApplyMovement LOCALID_BUCK, FightArea_Movement_BuckLeave
    ApplyMovement LOCALID_PLAYER, FightArea_Movement_PlayerWatchBuckLeave
    WaitMovement
    RemoveObject LOCALID_BUCK
    SetVar VAR_FIGHT_AREA_STATE, 2
    ReleaseAll
    End

    .balign 4, 0
FightArea_Movement_RivalNoticePlayer:
    WalkOnSpotNormalWest
    EmoteExclamationMark
    EndMovement

FightArea_UnusedMovement:
    WalkNormalWest
    EndMovement

    .balign 4, 0
FightArea_Movement_RivalWalkToPokecenter:
    WalkNormalEast 17
    WalkNormalNorth 2
    WalkNormalEast 2
    WalkOnSpotNormalNorth
    EndMovement

    .balign 4, 0
FightArea_Movement_RivalWalkToFrontierGate:
    WalkNormalEast 7
    WalkNormalNorth 6
    WalkNormalEast
    WalkOnSpotNormalNorth
    EndMovement

    .balign 4, 0
FightArea_Movement_RivalWalkNorth:
    WalkNormalNorth
    EndMovement

    .balign 4, 0
FightArea_Movement_RivalFacePlayer:
    WalkOnSpotFastWest
    EndMovement

    .balign 4, 0
FightArea_Movement_RivalGetPushedBack:
    FaceNorth
    LockDir
    WalkFastSouth 2
    UnlockDir
    EndMovement

FightArea_UnusedMovement2:
    EmoteExclamationMark
    EndMovement

    .balign 4, 0
FightArea_Movement_RivalWalkToPalmer:
    WalkFastNorth 2
    EndMovement

    .balign 4, 0
FightArea_Movement_RivalLeave:
    WalkFastSouth 8
    EndMovement

    .balign 4, 0
FightArea_Movement_PalmerEnter:
    WalkFastSouth
    EndMovement

    .balign 4, 0
FightArea_Movement_PalmerLookAround:
    WalkOnSpotNormalWest
    Delay8
    WalkOnSpotNormalEast
    Delay8
    WalkOnSpotNormalSouth
    EndMovement

    .balign 4, 0
FightArea_Movement_PlayerWalkToRival:
    WalkNormalEast 4
    EndMovement

    .balign 4, 0
FightArea_Movement_PlayerWalkToPokecenter:
    WalkNormalEast 18
    WalkNormalNorth 2
    WalkNormalEast 1
    WalkOnSpotNormalNorth
    EndMovement

    .balign 4, 0
FightArea_Movement_PlayerWalkToFrontierGate:
    WalkNormalEast 8
    WalkNormalNorth 6
    EndMovement

    .balign 4, 0
FightArea_Movement_PlayerWalkNorth:
    WalkNormalNorth
    EndMovement

    .balign 4, 0
FightArea_Movement_PlayerFaceRival:
    WalkOnSpotNormalEast
    EndMovement

    .balign 4, 0
FightArea_Movement_PlayerFaceRivalThenPalmer:
    Delay8
    WalkOnSpotFastSouth
    Delay4
    WalkOnSpotFastNorth
    EndMovement

    .balign 4, 0
FightArea_Movement_PlayerWatchBuckLeave:
    Delay8
    WalkOnSpotNormalSouth
    EndMovement

    .balign 4, 0
FightArea_Movement_PlayerWatchRivalLeave:
    WalkOnSpotNormalSouth
    EndMovement

FightArea_UnusedMovement3:
    Delay8
    WalkOnSpotNormalNorth
    EndMovement

    .balign 4, 0
FightArea_Movement_PlayerFaceBuck:
    Delay8 2
    WalkOnSpotNormalEast
    EndMovement

    .balign 4, 0
FightArea_Movement_BuckWalkToPlayer:
    WalkNormalWest 2
    EndMovement

    .balign 4, 0
FightArea_Movement_BuckLeave:
    WalkNormalSouth 7
    EndMovement

FightArea_UnusedMovement4:
    WalkOnSpotNormalWest
    EndMovement

FightArea_UnusedMovement5:
    WalkNormalEast 10
    EndMovement

FightArea_AceTrainerM1:
    NPCMessage FightArea_Text_BattleTowerLooms
    End

FightArea_AceTrainerF1:
    NPCMessage FightArea_Text_BattledManyTrainers
    End

FightArea_PokemonBreederM:
    NPCMessage FightArea_Text_LandIsCraggy
    End

FightArea_Twin:
    NPCMessage FightArea_Text_EliteFourComeSometimes
    End

FightArea_BattleGirl1:
    NPCMessage FightArea_Text_NotUsedToSinnohPokemon
    End

FightArea_BlackBelt1:
    NPCMessage FightArea_Text_NoEndToBecomingTough
    End

FightArea_Sailor1:
    NPCMessage FightArea_Text_ThrillWithNewDiscoveries
    End

FightArea_Fisherman:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    BufferItemName 0, ITEM_SUPER_ROD
    GoToIfSet FLAG_SUPER_ROD_OBTAINED, FightArea_AdviceForFishing
    Message FightArea_Text_SuperRoodReallyGood
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_NO, FightArea_DontYouLikeToFish
    Message FightArea_Text_TakeThisSuperRod
    SetVar VAR_0x8004, ITEM_SUPER_ROD
    SetVar VAR_0x8005, 1
    Common_GiveItemQuantity
    SetFlag FLAG_SUPER_ROD_OBTAINED
    Message FightArea_Text_TryLuckAtFishing
    WaitButton
    CloseMessage
    ReleaseAll
    End

FightArea_DontYouLikeToFish:
    Message FightArea_Text_DontYouLikeToFish
    WaitButton
    CloseMessage
    ReleaseAll
    End

FightArea_AdviceForFishing:
    Message FightArea_Text_AdviceForFishing
    WaitButton
    CloseMessage
    ReleaseAll
    End

FightArea_MapSign:
    ShowMapSign FightArea_Text_MapSign
    End

FightArea_ArrowSignpostBattleFrontier:
    ShowArrowSign FightArea_Text_SignBattleFrontierAhead
    End

FightArea_ArrowSignpostRt225:
    ShowArrowSign FightArea_Text_SignRt225Ahead
    End

FightArea_Sailor2:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    FacePlayer
    GetPlayerDir VAR_0x8004
    Message FightArea_Text_SailToSnowpointCity
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_YES, FightArea_SailToSnowpointCity
    GoToIfEq VAR_RESULT, MENU_NO, FightArea_YoudRatherFly
    End

FightArea_YoudRatherFly:
    Message FightArea_Text_YoudRatherFly
    WaitButton
    CloseMessage
    ReleaseAll
    End

FightArea_SailToSnowpointCity:
    Message FightArea_Text_AnchorsAweigh
    CloseMessage
    Call FightArea_SailorEnterShip
    CallIfEq VAR_0x8004, DIR_SOUTH, FightArea_PlayerEnterShipSouth
    CallIfEq VAR_0x8004, DIR_EAST, FightArea_PlayerEnterShipEast
    CallIfEq VAR_0x8004, DIR_WEST, FightArea_PlayerEnterShipWest
    TakeShipToSnowpoint
    ReleaseAll
    End

FightArea_SailorEnterShip:
    ApplyMovement LOCALID_SAILOR_2, FightArea_Movement_Sailor2WalkToShip
    WaitMovement
    PlaySE SEQ_SE_DP_KAIDAN2
    ApplyMovement LOCALID_SAILOR_2, FightArea_Movement_SetInvisible
    WaitMovement
    Return

FightArea_PlayerEnterShipSouth:
    ApplyMovement LOCALID_PLAYER, FightArea_Movement_PlayerWalkToShipSouth
    WaitMovement
    PlaySE SEQ_SE_DP_KAIDAN2
    ApplyMovement LOCALID_PLAYER, FightArea_Movement_SetInvisible
    WaitMovement
    Return

FightArea_PlayerEnterShipEast:
    ApplyMovement LOCALID_PLAYER, FightArea_Movement_PlayerWalkToShipEast
    WaitMovement
    PlaySE SEQ_SE_DP_KAIDAN2
    ApplyMovement LOCALID_PLAYER, FightArea_Movement_SetInvisible
    WaitMovement
    Return

FightArea_PlayerEnterShipWest:
    ApplyMovement LOCALID_PLAYER, FightArea_Movement_PlayerWalkToShipWest
    WaitMovement
    PlaySE SEQ_SE_DP_KAIDAN2
    ApplyMovement LOCALID_PLAYER, FightArea_Movement_SetInvisible
    WaitMovement
    Return

    .balign 4, 0
FightArea_Movement_Sailor2WalkToShip:
    FaceSouth
    Delay15
    EndMovement

    .balign 4, 0
FightArea_Movement_SetInvisible:
    SetInvisible
    EndMovement

    .balign 4, 0
FightArea_Movement_PlayerWalkToShipSouth:
    WalkNormalSouth
    Delay15
    EndMovement

    .balign 4, 0
FightArea_Movement_PlayerWalkToShipEast:
    WalkNormalEast
    FaceSouth
    Delay15
    EndMovement

    .balign 4, 0
FightArea_Movement_PlayerWalkToShipWest:
    WalkNormalWest
    FaceSouth
    Delay15
    EndMovement

FightArea_Buck:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message FightArea_Text_WhoAreYouGuys
    WaitButton
    ApplyMovement LOCALID_BUCK, FightArea_Movement_BuckWalkOnSpotWest
    WaitMovement
    CloseMessage
    ReleaseAll
    End

    .balign 4, 0
FightArea_Movement_BuckWalkOnSpotWest:
    WalkOnSpotNormalWest
    EndMovement

    .balign 0

FightArea_DrifloonInteract:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Common_CallDrifloon
    ReleaseAll
    End

FightArea_Palmer:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message FightArea_Text_FrontierIsOffLimits
    WaitButton
    ApplyMovement LOCALID_PALMER, FightArea_Movement_PalmerFaceSouth
    WaitMovement
    CloseMessage
    ReleaseAll
    End

FightArea_TriggerPalmerBlockFrontier:
    LockAll
    ApplyMovement LOCALID_PALMER, FightArea_Movement_PalmerNoticePlayer
    WaitMovement
    Message FightArea_Text_FrontierIsOffLimits
    WaitButton
    CloseMessage
    ApplyMovement LOCALID_PLAYER, FightArea_Movement_PlayerStepBackSouth
    ApplyMovement LOCALID_PALMER, FightArea_Movement_PalmerFaceSouth
    WaitMovement
    ReleaseAll
    End

    .balign 4, 0
FightArea_Movement_PalmerNoticePlayer:
    WalkOnSpotNormalWest
    EmoteExclamationMark
    EndMovement

    .balign 4, 0
FightArea_Movement_PalmerFaceSouth:
    FaceSouth
    EndMovement

    .balign 4, 0
FightArea_Movement_PlayerStepBackSouth:
    WalkNormalSouth
    EndMovement

    .balign 4, 0
FightArea_Movement_PlayerLookEast:
    WalkOnSpotNormalEast
    EndMovement

    .balign 4, 0
FightArea_Movement_RivalLookWest:
    WalkOnSpotNormalWest
    EndMovement
