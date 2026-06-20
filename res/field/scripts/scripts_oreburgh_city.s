#include "macros/scrcmd.inc"
#include "res/text/bank/oreburgh_city.h"
#include "res/field/events/events_oreburgh_city.h"

    ScriptEntry OreburghCity_Rival
    ScriptEntry OreburghCity_Youngster
    ScriptEntry OreburghCity_TriggerYoungster
    ScriptEntry OreburghCity_TriggerRival
    ScriptEntry OreburghCity_Hiker
    ScriptEntry OreburghCity_Worker1
    ScriptEntry OreburghCity_Worker2
    ScriptEntry OreburghCity_Worker3
    ScriptEntry OreburghCity_Worker4
    ScriptEntry OreburghCity_BattleGirl1
    ScriptEntry OreburghCity_SchoolKidF
    ScriptEntry OreburghCity_Guitarist
    ScriptEntry OreburghCity_PokefanF
    ScriptEntry OreburghCity_Camper
    ScriptEntry OreburghCity_MapSign
    ScriptEntry OreburghCity_GymSignpost
    ScriptEntry OreburghCity_ScrollingSignOreburghMiningMuseum
    ScriptEntry OreburghCity_ScrollingSignOreburghMine
    ScriptEntry OreburghCity_Machop1
    ScriptEntry OreburghCity_BattleGirl2
    ScriptEntry OreburghCity_Machop3
    ScriptEntry OreburghCity_Machop2
    ScriptEntry OreburghCity_DrifloonInteract
    ScriptEntry OreburghCity_Collector
    ScriptEntryEnd

OreburghCity_Rival:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet FLAG_TALKED_TO_OREBURGH_CITY_RIVAL, OreburghCity_IToldYouTheGymLeaderWentDownToTheOreburghMine
    BufferRivalName 0
    BufferPlayerName 1
    Message OreburghCity_Text_TheGymLeadersGoneOffToTheCoalMine
    WaitButton
    SetFlag FLAG_TALKED_TO_OREBURGH_CITY_RIVAL
    CloseMessage
    ReleaseAll
    End

OreburghCity_IToldYouTheGymLeaderWentDownToTheOreburghMine:
    BufferRivalName 0
    Message OreburghCity_Text_IToldYouTheGymLeaderWentDownToTheOreburghMine
    WaitButton
    CloseMessage
    ReleaseAll
    End

OreburghCity_Youngster:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfBadgeAcquired BADGE_ID_COAL, OreburghCity_CanISeeYourTrainerCase
    GoToIfSet FLAG_ROARK_RETURNED_TO_OREBURGH_GYM, OreburghCity_TheGymLeadersWaitingForYou
    Message OreburghCity_Text_IsThatGuyInFrontOfTheGymYourFriend
    WaitButton
    CloseMessage
    ReleaseAll
    End

OreburghCity_CanISeeYourTrainerCase:
    Message OreburghCity_Text_CanISeeYourTrainerCase
    WaitButton
    CloseMessage
    ReleaseAll
    End

OreburghCity_TheGymLeadersWaitingForYou:
    Message OreburghCity_Text_TheGymLeadersWaitingForYou
    WaitButton
    CloseMessage
    ReleaseAll
    End

OreburghCity_TriggerRival:
    LockAll
    ClearFlag FLAG_HIDE_OREBURGH_CITY_RIVAL
    SetObjectEventMovementType LOCALID_RIVAL, MOVEMENT_TYPE_LOOK_WEST
    SetObjectEventDir LOCALID_RIVAL, DIR_WEST
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    GoToIfEq VAR_0x8005, 748, OreburghCity_RivalRunIntoPlayerZ748
    GoToIfEq VAR_0x8005, 749, OreburghCity_RivalRunIntoPlayerZ749
    GoToIfEq VAR_0x8005, 750, OreburghCity_RivalRunIntoPlayerZ750
    GoTo OreburghCity_RivalRunIntoPlayerZ751
    End

OreburghCity_RivalRunIntoPlayerZ748:
    SetObjectEventPos LOCALID_RIVAL, 271, 748
    AddObject LOCALID_RIVAL
    ApplyMovement LOCALID_PLAYER, OreburghCity_Movement_PlayerGetPushedByRival
    ApplyMovement LOCALID_RIVAL, OreburghCity_Movement_RivalRunIntoPlayer
    WaitMovement
    GoTo OreburghCity_NextStopTheEternaGymBadge
    End

OreburghCity_RivalRunIntoPlayerZ749:
    SetObjectEventPos LOCALID_RIVAL, 271, 749
    AddObject LOCALID_RIVAL
    ApplyMovement LOCALID_PLAYER, OreburghCity_Movement_PlayerGetPushedByRival
    ApplyMovement LOCALID_RIVAL, OreburghCity_Movement_RivalRunIntoPlayer
    WaitMovement
    GoTo OreburghCity_NextStopTheEternaGymBadge
    End

OreburghCity_RivalRunIntoPlayerZ750:
    SetObjectEventPos LOCALID_RIVAL, 271, 750
    AddObject LOCALID_RIVAL
    ApplyMovement LOCALID_PLAYER, OreburghCity_Movement_PlayerGetPushedByRival
    ApplyMovement LOCALID_RIVAL, OreburghCity_Movement_RivalRunIntoPlayer
    WaitMovement
    GoTo OreburghCity_NextStopTheEternaGymBadge
    End

OreburghCity_RivalRunIntoPlayerZ751:
    SetObjectEventPos LOCALID_RIVAL, 271, 751
    AddObject LOCALID_RIVAL
    ApplyMovement LOCALID_PLAYER, OreburghCity_Movement_PlayerGetPushedByRival
    ApplyMovement LOCALID_RIVAL, OreburghCity_Movement_RivalRunIntoPlayer
    WaitMovement
    GoTo OreburghCity_NextStopTheEternaGymBadge
    End

OreburghCity_NextStopTheEternaGymBadge:
    PlaySE SEQ_SE_DP_WALL_HIT2
    Message OreburghCity_Text_BigThud
    CloseMessage
    Common_SetRivalBGM
    BufferRivalName 0
    BufferPlayerName 1
    Message OreburghCity_Text_EternaCityIsTheNextPlaceWithAGymThatGivesAwayBadgesRight
    CloseMessage
    ApplyMovement LOCALID_RIVAL, OreburghCity_Movement_RivalWalkOnSpotEast
    WaitMovement
    Message OreburghCity_Text_IWentToRoute207ButYouCantGoThereWithoutABicycle
    ApplyMovement LOCALID_RIVAL, OreburghCity_Movement_RivalWalkOnSpotWest
    WaitMovement
    Message OreburghCity_Text_NextStopTheEternaGymBadge
    CloseMessage
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    GoToIfEq VAR_0x8005, 748, OreburghCity_RivalLeaveZ748
    GoToIfEq VAR_0x8005, 749, OreburghCity_RivalLeaveZ749
    GoToIfEq VAR_0x8005, 750, OreburghCity_RivalLeaveZ750
    GoTo OreburghCity_RivalLeaveZ751
    End

OreburghCity_RivalLeaveZ748:
    ApplyMovement LOCALID_PLAYER, OreburghCity_Movement_PlayerWatchRivalLeaveZ748
    ApplyMovement LOCALID_RIVAL, OreburghCity_Movement_RivalLeaveZ748
    WaitMovement
    GoTo OreburghCity_RemoveRival
    End

OreburghCity_RivalLeaveZ749:
    ApplyMovement LOCALID_PLAYER, OreburghCity_Movement_PlayerWatchRivalLeaveZ749
    ApplyMovement LOCALID_RIVAL, OreburghCity_Movement_RivalLeaveZ749
    WaitMovement
    GoTo OreburghCity_RemoveRival
    End

OreburghCity_RivalLeaveZ750:
    ApplyMovement LOCALID_PLAYER, OreburghCity_Movement_PlayerWatchRivalLeaveZ750
    ApplyMovement LOCALID_RIVAL, OreburghCity_Movement_RivalLeaveZ750
    WaitMovement
    GoTo OreburghCity_RemoveRival
    End

OreburghCity_RivalLeaveZ751:
    ApplyMovement LOCALID_PLAYER, OreburghCity_Movement_PlayerWatchRivalLeaveZ751
    ApplyMovement LOCALID_RIVAL, OreburghCity_Movement_RivalLeaveZ751
    WaitMovement
    GoTo OreburghCity_RemoveRival
    End

OreburghCity_RemoveRival:
    PlaySE SEQ_SE_DP_KAIDAN2
    RemoveObject LOCALID_RIVAL
    Common_FadeToDefaultMusic2
    SetVar VAR_OREBURGH_STATE, 3
    ReleaseAll
    End

    .balign 4, 0
OreburghCity_Movement_PlayerGetPushedByRival:
    Delay4 7
    LockDir
    WalkFastWest
    UnlockDir
    FaceEast
    EndMovement

    .balign 4, 0
OreburghCity_Movement_RivalRunIntoPlayer:
    WalkFastWest 9
    EndMovement

    .balign 4, 0
OreburghCity_Movement_RivalLeaveZ748:
    WalkFastSouth
    WalkFastWest 4
    WalkOnSpotFastWest
    EndMovement

    .balign 4, 0
OreburghCity_Movement_RivalLeaveZ749:
    WalkFastSouth
    WalkFastWest 3
    WalkFastNorth
    WalkFastWest
    WalkOnSpotFastWest
    EndMovement

    .balign 4, 0
OreburghCity_Movement_RivalLeaveZ750:
    WalkFastNorth
    WalkFastWest 4
    WalkOnSpotFastWest
    EndMovement

    .balign 4, 0
OreburghCity_Movement_RivalLeaveZ751:
    WalkFastNorth
    WalkFastWest 3
    WalkFastNorth
    WalkFastWest
    WalkOnSpotFastWest
    EndMovement

    .balign 4, 0
OreburghCity_Movement_PlayerWatchRivalLeaveZ748:
    WalkOnSpotNormalSouth
    WalkOnSpotNormalWest
    EndMovement

    .balign 4, 0
OreburghCity_Movement_PlayerWatchRivalLeaveZ749:
    WalkOnSpotNormalSouth
    WalkOnSpotNormalWest
    EndMovement

    .balign 4, 0
OreburghCity_Movement_PlayerWatchRivalLeaveZ750:
    WalkOnSpotNormalNorth
    WalkOnSpotNormalWest
    EndMovement

    .balign 4, 0
OreburghCity_Movement_PlayerWatchRivalLeaveZ751:
    WalkOnSpotNormalNorth
    WalkOnSpotNormalWest
    EndMovement

    .balign 4, 0
OreburghCity_Movement_RivalWalkOnSpotEast:
    WalkOnSpotNormalEast
    EndMovement

    .balign 4, 0
OreburghCity_Movement_RivalWalkOnSpotWest:
    WalkOnSpotNormalWest
    EndMovement

OreburghCity_Hiker:
    NPCMessage OreburghCity_Text_UpAheadTheresAHugeMountainThatTowersAboveEverything
    End

OreburghCity_Worker1:
    NPCMessage OreburghCity_Text_TheseVentsExchangeTheHotAirDownBelowWithTheFreshAirOutside
    End

OreburghCity_Worker2:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet FLAG_RECEIVED_OREBURGH_CITY_SUPER_POTION, OreburghCity_FeelingHaleAndHeartyPutsASmileOnMyFace
    Message OreburghCity_Text_HereTakeOneOfThese
    SetVar VAR_0x8004, ITEM_SUPER_POTION
    SetVar VAR_0x8005, 1
    GoToIfCannotFitItem VAR_0x8004, VAR_0x8005, VAR_RESULT, OreburghCity_BagIsFull
    Common_GiveItemQuantity
    SetFlag FLAG_RECEIVED_OREBURGH_CITY_SUPER_POTION
    GoTo OreburghCity_FeelingHaleAndHeartyPutsASmileOnMyFace
    End

OreburghCity_FeelingHaleAndHeartyPutsASmileOnMyFace:
    Message OreburghCity_Text_FeelingHaleAndHeartyPutsASmileOnMyFace
    WaitButton
    CloseMessage
    ReleaseAll
    End

OreburghCity_BagIsFull:
    Common_MessageBagIsFull
    CloseMessage
    ReleaseAll
    End

OreburghCity_Worker3:
    NPCMessage OreburghCity_Text_ThisPileOfDirtySandIsCalledASlagHeap
    End

OreburghCity_Worker4:
    NPCMessage OreburghCity_Text_ChopChopMachopChopChopAwayOnRocks
    End

OreburghCity_TriggerYoungster:
    LockAll
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    GoToIfEq VAR_0x8004, 296, OreburghCity_YoungsterApproachX296
    GoToIfEq VAR_0x8004, 297, OreburghCity_YoungsterApproachX297
    GoToIfEq VAR_0x8004, 298, OreburghCity_YoungsterApproachX298
    GoTo OreburghCity_YoungsterApproachX299
    End

OreburghCity_YoungsterApproachX296:
    ApplyMovement LOCALID_PLAYER, OreburghCity_Movement_PlayerFaceEast
    ApplyMovement LOCALID_YOUNGSTER, OreburghCity_Movement_YoungsterApproachWest3
    WaitMovement
    GoTo OreburghCity_IllTakeYouToThePokemonGym
    End

OreburghCity_YoungsterApproachX297:
    ApplyMovement LOCALID_PLAYER, OreburghCity_Movement_PlayerFaceEast
    ApplyMovement LOCALID_YOUNGSTER, OreburghCity_Movement_YoungsterApproachWest2
    WaitMovement
    GoTo OreburghCity_IllTakeYouToThePokemonGym
    End

OreburghCity_YoungsterApproachX298:
    ApplyMovement LOCALID_PLAYER, OreburghCity_Movement_PlayerFaceEast
    ApplyMovement LOCALID_YOUNGSTER, OreburghCity_Movement_YoungsterApproachWest1
    WaitMovement
    GoTo OreburghCity_IllTakeYouToThePokemonGym
    End

OreburghCity_YoungsterApproachX299:
    ApplyMovement LOCALID_PLAYER, OreburghCity_Movement_PlayerFaceEast
    ApplyMovement LOCALID_YOUNGSTER, OreburghCity_Movement_YoungsterApproachWest0
    WaitMovement
    GoTo OreburghCity_IllTakeYouToThePokemonGym
    End

OreburghCity_IllTakeYouToThePokemonGym:
    Message OreburghCity_Text_IllTakeYouToThePokemonGym
    CloseMessage
    Common_SetFollowMeBGM
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    GoToIfEq VAR_0x8004, 299, OreburghCity_WalkWithYoungsterToTheGymX299
    GoToIfEq VAR_0x8004, 298, OreburghCity_WalkWithYoungsterToTheGymX298
    GoToIfEq VAR_0x8004, 297, OreburghCity_WalkWithYoungsterToTheGymX297
    GoTo OreburghCity_WalkWithYoungsterToTheGymX296
    End

OreburghCity_WalkWithYoungsterToTheGymX299:
    ApplyMovement LOCALID_PLAYER, OreburghCity_Movement_PlayerWalkToTheGymX299
    ApplyMovement LOCALID_YOUNGSTER, OreburghCity_Movement_YoungsterWalkToTheGymX299
    WaitMovement
    GoTo OreburghCity_HuhTheresSomeoneThere
    End

OreburghCity_WalkWithYoungsterToTheGymX298:
    ApplyMovement LOCALID_PLAYER, OreburghCity_Movement_PlayerWalkToTheGymX298
    ApplyMovement LOCALID_YOUNGSTER, OreburghCity_Movement_YoungsterWalkToTheGymX298
    WaitMovement
    GoTo OreburghCity_HuhTheresSomeoneThere
    End

OreburghCity_WalkWithYoungsterToTheGymX297:
    ApplyMovement LOCALID_PLAYER, OreburghCity_Movement_PlayerWalkToTheGymX297
    ApplyMovement LOCALID_YOUNGSTER, OreburghCity_Movement_YoungsterWalkToTheGymX297
    WaitMovement
    GoTo OreburghCity_HuhTheresSomeoneThere
    End

OreburghCity_WalkWithYoungsterToTheGymX296:
    ApplyMovement LOCALID_PLAYER, OreburghCity_Movement_PlayerWalkToTheGymX296
    ApplyMovement LOCALID_YOUNGSTER, OreburghCity_Movement_YoungsterWalkToTheGymX296
    WaitMovement
    GoTo OreburghCity_HuhTheresSomeoneThere
    End

OreburghCity_HuhTheresSomeoneThere:
    Message OreburghCity_Text_HuhTheresSomeoneThere
    WaitButton
    CloseMessage
    Common_FadeToDefaultMusic3
    SetVar VAR_OREBURGH_STATE, 1
    ReleaseAll
    End

    .balign 4, 0
OreburghCity_Movement_PlayerFaceEast:
    WalkOnSpotNormalEast
    EndMovement

    .balign 4, 0
OreburghCity_Movement_YoungsterApproachWest3:
    EmoteExclamationMark
    WalkNormalWest 3
    EndMovement

    .balign 4, 0
OreburghCity_Movement_YoungsterApproachWest2:
    EmoteExclamationMark
    WalkNormalWest 2
    EndMovement

    .balign 4, 0
OreburghCity_Movement_YoungsterApproachWest1:
    EmoteExclamationMark
    WalkNormalWest
    EndMovement

    .balign 4, 0
OreburghCity_Movement_YoungsterApproachWest0:
    EmoteExclamationMark
    WalkOnSpotNormalWest
    EndMovement

    .balign 4, 0
OreburghCity_Movement_PlayerWalkToTheGymX299:
    Delay8 2
    WalkNormalWest
    WalkNormalSouth 12
    WalkNormalWest 13
    EndMovement

    .balign 4, 0
OreburghCity_Movement_PlayerWalkToTheGymX298:
    Delay8 2
    WalkNormalSouth 12
    WalkNormalWest 13
    EndMovement

    .balign 4, 0
OreburghCity_Movement_PlayerWalkToTheGymX297:
    WalkNormalEast
    WalkNormalSouth 12
    WalkNormalWest 13
    EndMovement

    .balign 4, 0
OreburghCity_Movement_PlayerWalkToTheGymX296:
    WalkNormalEast 2
    WalkNormalSouth 12
    WalkNormalWest 13
    EndMovement

    .balign 4, 0
OreburghCity_Movement_YoungsterWalkToTheGymX299:
    WalkNormalSouth
    WalkNormalWest 2
    WalkNormalSouth 11
    WalkNormalWest 14
    EndMovement

    .balign 4, 0
OreburghCity_Movement_YoungsterWalkToTheGymX298:
    WalkNormalSouth
    WalkNormalWest
    WalkNormalSouth 11
    WalkNormalWest 14
    EndMovement

    .balign 4, 0
OreburghCity_Movement_YoungsterWalkToTheGymX297:
    WalkNormalSouth 12
    WalkNormalWest 14
    EndMovement

    .balign 4, 0
OreburghCity_Movement_YoungsterWalkToTheGymX296:
    WalkNormalEast
    WalkNormalSouth 12
    WalkNormalWest 14
    EndMovement

OreburghCity_BattleGirl1:
    NPCMessage OreburghCity_Text_TMsAreSingleUseOnlyButHMsCanBeUsedOverAndOver
    End

OreburghCity_SchoolKidF:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet FLAG_ROARK_RETURNED_TO_OREBURGH_GYM, OreburghCity_TheGymLeaderIsYoungButHesTheMinesSafetySupervisor
    Message OreburghCity_Text_TheGymLeaderWentOffToWorkInTheMine
    WaitButton
    CloseMessage
    ReleaseAll
    End

OreburghCity_TheGymLeaderIsYoungButHesTheMinesSafetySupervisor:
    Message OreburghCity_Text_TheGymLeaderIsYoungButHesTheMinesSafetySupervisor
    WaitButton
    CloseMessage
    ReleaseAll
    End

OreburghCity_Guitarist:
    NPCMessage OreburghCity_Text_HaveYouSeenTheVents
    End

OreburghCity_PokefanF:
    NPCMessage OreburghCity_Text_EveryonesProudOfTheMine
    End

OreburghCity_Camper:
    NPCMessage OreburghCity_Text_WhenIRunAroundWithMyRunningShoesOnImTheCenterOfAttention
    End

OreburghCity_MapSign:
    ShowMapSign OreburghCity_Text_MapSign
    End

OreburghCity_GymSignpost:
    ShowScrollingSign OreburghCity_Text_OreburgCityPokemonGymCallMeRoarkTheRock
    End

OreburghCity_ScrollingSignOreburghMiningMuseum:
    ShowLandmarkSign OreburghCity_Text_OreburghMiningMuseumCoalMiningAndYou
    End

OreburghCity_ScrollingSignOreburghMine:
    ShowLandmarkSign OreburghCity_Text_OreburghMineBewareOfBusyPokemon
    End

OreburghCity_Machop1:
    PokemonCryAndMessage SPECIES_MACHOP, OreburghCity_Text_MachopMachoChopo
    End

OreburghCity_BattleGirl2:
    NPCMessage OreburghCity_Text_ThatsWhatFossilsAre
    End

OreburghCity_Machop3:
    PokemonCryAndMessage SPECIES_MACHOP, OreburghCity_Text_MachopPigyooh
    End

OreburghCity_Machop2:
    PokemonCryAndMessage SPECIES_MACHOP, OreburghCity_Text_MachopGwoohGogogooh
    End

    .balign 4, 0

OreburghCity_DrifloonInteract:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Common_CallDrifloon
    ReleaseAll
    End

OreburghCity_Collector:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message OreburghCity_Text_CollectorCheckOutTheGym
    WaitButton
    CloseMessage
    ReleaseAll
    End
