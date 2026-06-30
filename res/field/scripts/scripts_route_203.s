#include "macros/scrcmd.inc"
#include "generated/species.h"
#include "res/text/bank/route_203.h"
#include "res/field/events/events_route_203.h"


    ScriptEntry Route203_Lass
    ScriptEntry Route203_ArrowSignpostJubilifeCity
    ScriptEntry Route203_ArrowSignpostOreburghCity
    ScriptEntry Route203_TrainerTipsSignpostEast
    ScriptEntry Route203_TrainerTipsSignpostWest
    ScriptEntry Route203_PaulTrigger
    ScriptEntry Route203_Hariyama
    ScriptEntryEnd

Route203_Lass:
    NPCMessage Route203_Text_YourFavoritePokemonShouldBePlacedAtTheTop
    End

Route203_Hariyama:
    LockAll
    FacePlayer
    GoToIfSet FLAG_ROCK_SMASH_UNLOCKED, Route203_HariyamaFlavour
    PlayCry SPECIES_HARIYAMA
    WaitCry
    WaitTime 30, VAR_RESULT
    ApplyMovement LOCALID_HARIYAMA, Route203_Movement_HariyamaFaceRock
    WaitMovement
    WaitTime 8, VAR_RESULT
    RockSmashBreakAtObject LOCALID_HARIYAMA, VAR_0x8005
    WaitTime 10, VAR_RESULT
    RemoveObject LOCALID_HARIYAMA_ROCK

Route203_HariyamaWaitSmash:
    WaitTime 1, VAR_RESULT
    GoToIfEq VAR_0x8005, 0, Route203_HariyamaWaitSmash
    SetFlag FLAG_ROCK_SMASH_UNLOCKED
    WaitTime 10, VAR_RESULT
    FacePlayer
    Message Route203_Text_HariyamaLearnedRockSmash
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route203_HariyamaFlavour:
    Message Route203_Text_HariyamaFlavour
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route203_ArrowSignpostJubilifeCity:
    ShowArrowSign Route203_Text_Rt203JubilifeCity
    End

Route203_ArrowSignpostOreburghCity:
    ShowArrowSign Route203_Text_Rt203OreburghCity
    End

Route203_TrainerTipsSignpostEast:
    ShowScrollingSign Route203_Text_TrainerTipsIfAPokemonIsAboutToEvolveItCanBeInstantlyStopped
    End

Route203_TrainerTipsSignpostWest:
    ShowScrollingSign Route203_Text_TrainerTipsPokemonMovesUseEnergyCalledPowerPoints
    End

Route203_PaulTrigger:
    LockAll
    ClearFlag FLAG_HIDE_ROUTE_203_PAUL
    AddObject LOCALID_PAUL
    ApplyMovement LOCALID_PAUL, Route203_Movement_PaulNoticePlayer
    WaitMovement
    Common_SetRivalBGM
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    GoToIfEq VAR_0x8004, 215, Route203_PaulApproachX215
    GoToIfEq VAR_0x8004, 216, Route203_PaulApproachX216
    GoToIfEq VAR_0x8004, 217, Route203_PaulApproachX217
    GoTo Route203_PaulApproach

Route203_PaulApproachX215:
    ApplyMovement LOCALID_PAUL, Route203_Movement_PaulApproachX215
    WaitMovement
    GoTo Route203_PaulApproach

Route203_PaulApproachX216:
    ApplyMovement LOCALID_PAUL, Route203_Movement_PaulApproachX216
    WaitMovement
    GoTo Route203_PaulApproach

Route203_PaulApproachX217:
    ApplyMovement LOCALID_PAUL, Route203_Movement_PaulApproachX217
    WaitMovement
    GoTo Route203_PaulApproach

Route203_PaulApproach:
    ApplyMovement LOCALID_PLAYER, Route203_Movement_PlayerFaceSouth
    WaitMovement
    ApplyMovement LOCALID_PAUL, Route203_Movement_PaulApproach
    WaitMovement
    BufferRivalName 0
    BufferPlayerName 1
    Message Route203_Text_PaulIntro
    WaitButton
    CloseMessage
    StartTrainerBattle TRAINER_PAUL_ROUTE_203
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, Route203_BlackOutPaulBattle
    BufferRivalName 0
    Message Route203_Text_PaulAfterBattle
    WaitButton
    CloseMessage
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    GoToIfEq VAR_0x8004, 215, Route203_PaulApproachHariyamaX215
    GoToIfEq VAR_0x8004, 216, Route203_PaulApproachHariyamaX216
    GoToIfEq VAR_0x8004, 217, Route203_PaulApproachHariyamaX217
    GoTo Route203_PaulApproachHariyamaX218

Route203_PaulApproachHariyamaX215:
    ApplyMovement LOCALID_PAUL, Route203_Movement_PaulApproachHariyamaX215
    WaitMovement
    GoTo Route203_PaulApproachHariyama

Route203_PaulApproachHariyamaX216:
    ApplyMovement LOCALID_PAUL, Route203_Movement_PaulApproachHariyamaX216
    WaitMovement
    GoTo Route203_PaulApproachHariyama

Route203_PaulApproachHariyamaX217:
    ApplyMovement LOCALID_PAUL, Route203_Movement_PaulApproachHariyamaX217
    WaitMovement
    GoTo Route203_PaulApproachHariyama

Route203_PaulApproachHariyamaX218:
    ApplyMovement LOCALID_PAUL, Route203_Movement_PaulApproachHariyamaX218
    WaitMovement
    GoTo Route203_PaulApproachHariyama

Route203_PaulApproachHariyama:
    Message Route203_Text_PaulHariyama
    WaitButton
    CloseMessage
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    GoToIfEq VAR_0x8004, 217, Route203_PaulLeaveX217
    GoTo Route203_PaulLeaveOther

Route203_PaulLeaveX217:
    ApplyMovement LOCALID_PAUL, Route203_Movement_PaulLeaveX217
    WaitMovement
    GoTo Route203_PaulRemove

Route203_PaulLeaveOther:
    ApplyMovement LOCALID_PAUL, Route203_Movement_PaulLeaveOther
    WaitMovement
    GoTo Route203_PaulRemove

Route203_PaulRemove:
    RemoveObject LOCALID_PAUL
    SetFlag FLAG_HIDE_ROUTE_203_PAUL
    SetVar VAR_ROUTE_203_PAUL_STATE, 1
    ReleaseAll
    End

Route203_BlackOutPaulBattle:
    SetFlag FLAG_HIDE_ROUTE_204_RIVAL
    BlackOutFromBattle
    ReleaseAll
    End

    .balign 4, 0
Route203_Movement_PaulNoticePlayer:
    WalkNormalWest 8
    Delay8
    FaceNorth
    EmoteExclamationMark
    Delay8
    EndMovement

    .balign 4, 0
Route203_Movement_PaulApproachX215:
    WalkNormalWest 3
    EndMovement

    .balign 4, 0
Route203_Movement_PaulApproachX216:
    WalkNormalWest 2
    EndMovement

    .balign 4, 0
Route203_Movement_PaulApproachX217:
    WalkNormalWest 1
    EndMovement

    .balign 4, 0
Route203_Movement_PaulApproach:
    WalkNormalNorth 3
    EndMovement

    .balign 4, 0
Route203_Movement_PlayerFaceSouth:
    FaceSouth
    EndMovement

    .balign 4, 0
Route203_Movement_PaulApproachHariyamaX215:
    WalkNormalEast 3
    WalkNormalNorth 3
    WalkNormalEast 1
    WalkNormalNorth 1
    EndMovement

    .balign 4, 0
Route203_Movement_PaulApproachHariyamaX216:
    WalkNormalEast 2
    WalkNormalNorth 3
    WalkNormalEast 1
    WalkNormalNorth 1
    EndMovement

    .balign 4, 0
Route203_Movement_PaulApproachHariyamaX217:
    WalkNormalEast 1
    WalkNormalNorth 3
    WalkNormalEast 1
    WalkNormalNorth 1
    EndMovement

    .balign 4, 0
Route203_Movement_PaulApproachHariyamaX218:
    WalkNormalWest 1
    WalkNormalNorth 3
    WalkNormalEast 2
    WalkNormalNorth 1
    EndMovement

    .balign 4, 0
Route203_Movement_PaulLeaveX217:
    WalkNormalWest 1
    WalkNormalSouth 7
    WalkNormalEast 7
    EndMovement

    .balign 4, 0
Route203_Movement_PaulLeaveOther:
    WalkNormalWest 2
    WalkNormalSouth 7
    WalkNormalEast 9
    EndMovement

    .balign 4, 0
Route203_Movement_HariyamaFaceRock:
    FaceEast
    EndMovement
