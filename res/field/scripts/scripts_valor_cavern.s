#include "macros/scrcmd.inc"
#include "res/text/bank/valor_cavern.h"
#include "res/field/events/events_valor_cavern.h"


    ScriptEntry ValorCavern_OnTransition
    ScriptEntry ValorCavern_OnLoad
    ScriptEntry ValorCavern_Saturn
    ScriptEntry ValorCavern_OnFrameSaturnBattle
    ScriptEntryEnd

ValorCavern_OnTransition:
    SetFlag FLAG_FIRST_ARRIVAL_VALOR_CAVERN
    ClearHasPartner
    GoToIfUnset FLAG_GALACTIC_LEFT_LAKE_VALOR, ValorCavern_RemoveWarpLakeValorNormal
    GoToIfSet FLAG_GALACTIC_LEFT_LAKE_VALOR, ValorCavern_RemoveWarpLakeValorDrained
    End

ValorCavern_RemoveWarpLakeValorNormal:
    SetWarpEventPos 1, 10, 29
    End

ValorCavern_RemoveWarpLakeValorDrained:
    SetWarpEventPos 0, 10, 29
    End

ValorCavern_OnLoad:
    SetFlag FLAG_FIRST_ARRIVAL_VALOR_CAVERN
    GoToIfUnset FLAG_GALACTIC_LEFT_LAKE_VALOR, ValorCavern_RemoveWarpLakeValorNormal
    GoToIfSet FLAG_GALACTIC_LEFT_LAKE_VALOR, ValorCavern_RemoveWarpLakeValorDrained
    End

ValorCavern_Saturn:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    Message ValorCavern_Text_SaturnMissionIsProceeding
    WaitButton
    CloseMessage
    FacePlayer
    ApplyMovement LOCALID_SATURN, ValorCavern_Movement_SaturnExclamationMark
    WaitMovement
    WaitTime 30, VAR_RESULT
    Message ValorCavern_Text_SaturnBattleIntro
    CloseMessage
    StartTrainerBattle TRAINER_COMMANDER_SATURN_VALOR_CAVERN
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, ValorCavern_LostBattleCommanderSaturn
    Message ValorCavern_Text_SaturnPostBattle
    CloseMessage
    FadeScreenOut
    WaitFadeScreen
    RemoveObject LOCALID_SATURN
    SetFlag FLAG_DEFEATED_COMMANDER_SATURN_VALOR_CAVERN
    SetFlag FLAG_ALT_MUSIC_LAKE_VALOR
    FadeScreenIn
    WaitFadeScreen
    ReleaseAll
    End

    .balign 4, 0
ValorCavern_Movement_SaturnExclamationMark:
    EmoteExclamationMark
    EndMovement

ValorCavern_LostBattleCommanderSaturn:
    BlackOutFromBattle
    ReleaseAll
    End

    .balign 4, 0
ValorCavern_OnFrameSaturnBattle:
    GoToIfSet FLAG_HIDE_LAKE_VALOR_GALACTIC, ValorCavern_OnFrameSaturnBattle_Skip
    LockAll
    SetPlayerBike FALSE
    ApplyMovement LOCALID_PAUL, ValorCavern_Movement_PaulApproach
    ApplyMovement LOCALID_PLAYER, ValorCavern_Movement_PlayerApproach
    WaitMovement
    ApplyMovement LOCALID_SATURN, ValorCavern_Movement_SaturnNotice
    WaitMovement
    WaitTime 30, VAR_RESULT
    Message ValorCavern_Text_SaturnMissionIsProceeding
    WaitButton
    CloseMessage
    Message ValorCavern_Text_SaturnBattleIntro
    WaitButton
    CloseMessage
    Message ValorCavern_Text_PaulTeamUp
    WaitButton
    CloseMessage
    StartTagBattle TRAINER_PAUL_LAKE_VALOR_ALLY, TRAINER_COMMANDER_SATURN_VALOR_CAVERN, TRAINER_GALACTIC_GRUNT_VALOR_CAVERN
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, ValorCavern_LostBattleCommanderSaturn
    Message ValorCavern_Text_SaturnPostBattle
    CloseMessage
    FadeScreenOut
    WaitFadeScreen
    RemoveObject LOCALID_SATURN
    RemoveObject LOCALID_GALACTIC_GRUNT_VALOR_CAVERN
    FadeScreenIn
    WaitFadeScreen
    Message ValorCavern_Text_PaulFarewell
    WaitButton
    CloseMessage
    ApplyMovement LOCALID_PAUL, ValorCavern_Movement_PaulLeave
    WaitMovement
    PlaySE SEQ_SE_DP_KAIDAN2
    RemoveObject LOCALID_PAUL
    WaitSE SEQ_SE_DP_KAIDAN2
    ClearHasPartner
    SetFlag FLAG_DEFEATED_COMMANDER_SATURN_VALOR_CAVERN
    SetFlag FLAG_ALT_MUSIC_LAKE_VALOR
    SetVar VAR_VALOR_CAVERN_SATURN_STATE, 1
    SetVar VAR_LAKE_VALOR_PAUL_STATE, 2
    ReleaseAll
    End

ValorCavern_OnFrameSaturnBattle_Skip:
    End

    .balign 4, 0
ValorCavern_Movement_PlayerApproach:
    WalkNormalNorth 8
    EndMovement

    .balign 4, 0
ValorCavern_Movement_PaulApproach:
    WalkNormalNorth 8
    EndMovement

    .balign 4, 0
ValorCavern_Movement_SaturnNotice:
    EmoteExclamationMark
    Delay15
    FaceSouth
    EndMovement

    .balign 4, 0
ValorCavern_Movement_PaulLeave:
    WalkNormalSouth 8
    SetInvisible
    EndMovement

    .balign 4, 0
