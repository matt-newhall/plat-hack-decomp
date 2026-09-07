#include "macros/scrcmd.inc"
#include "res/field/events/events_victory_road_1f.h"
#include "res/text/bank/victory_road_1f.h"


    ScriptEntry VictoryRoad_OnTransition
    ScriptEntry VictoryRoad_Collector
    ScriptEntry VictoryRoad_LeagueCheck
    ScriptEntry VictoryRoad_LeagueCheckTrigger
    ScriptEntry VictoryRoad_PaulTrigger
    ScriptEntry VictoryRoad_CounterpartTrigger
    ScriptEntryEnd

VictoryRoad_OnTransition:
    SetFlag FLAG_FIRST_ARRIVAL_VICTORY_ROAD
    SetFlag FLAG_HIDE_VICTORY_ROAD_1F_PAUL
    GetPlayerGender VAR_MAP_LOCAL_0
    CallIfEq VAR_MAP_LOCAL_0, GENDER_MALE, VictoryRoad_SetCounterpartGraphicsDawn
    CallIfEq VAR_MAP_LOCAL_0, GENDER_FEMALE, VictoryRoad_SetCounterpartGraphicsLucas
    GoToIfEq VAR_VICTORY_ROAD_LEAGUECHECK_STATE, 1, VictoryRoad_LeagueCheckMovedAside
VictoryRoad_OnTransitionCollector:
    GoToIfUnset FLAG_GAME_COMPLETED, VictoryRoad_DontHideCollector
    GetNationalDexEnabled VAR_MAP_LOCAL_0
    GoToIfEq VAR_MAP_LOCAL_0, FALSE, VictoryRoad_DontHideCollector
    SetFlag FLAG_HIDE_VICTORY_ROAD_1F_COLLECTOR
VictoryRoad_DontHideCollector:
    End

VictoryRoad_LeagueCheckMovedAside:
    SetObjectEventPos LOCALID_LEAGUECHECK, 40, 16
    SetObjectEventDir LOCALID_LEAGUECHECK, DIR_WEST
    GoTo VictoryRoad_OnTransitionCollector

VictoryRoad_SetCounterpartGraphicsDawn:
    SetVar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_PLAYER_F
    Return

VictoryRoad_SetCounterpartGraphicsLucas:
    SetVar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_PLAYER_M
    Return

VictoryRoad_Collector:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet FLAG_GAME_COMPLETED, VictoryRoad1F_YoullMeetManyPokemon
    Message VictoryRoad1F_Text_AimForPokemonLeague
    GoTo VictoryRoad1F_CollectorEnd
    End

VictoryRoad1F_YoullMeetManyPokemon:
    Message VictoryRoad1F_Text_YoullMeetManyPokemon
    GoTo VictoryRoad1F_CollectorEnd
    End

VictoryRoad1F_CollectorEnd:
    WaitButton
    CloseMessage
    ReleaseAll
    End

VictoryRoad_LeagueCheck:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message VictoryRoad1F_Text_LeagueCheckTalk
    WaitButton
    CloseMessage
    ReleaseAll
    End

VictoryRoad_LeagueCheckTrigger:
    LockAll
    GoToIfSet FLAG_UNLOCK_POKEMON_LEAGUE, VictoryRoad_LeagueCheckAllow
    ApplyMovement LOCALID_LEAGUECHECK, VictoryRoad_Movement_Exclaim
    WaitMovement
    Message VictoryRoad1F_Text_LeagueCheckBlock
    WaitButton
    CloseMessage
    ApplyMovement LOCALID_PLAYER, VictoryRoad_Movement_PlayerStepBack
    WaitMovement
    ReleaseAll
    End

VictoryRoad_LeagueCheckAllow:
    ApplyMovement LOCALID_LEAGUECHECK, VictoryRoad_Movement_Exclaim
    WaitMovement
    Message VictoryRoad1F_Text_LeagueCheckAllow
    WaitButton
    CloseMessage
    ApplyMovement LOCALID_LEAGUECHECK, VictoryRoad_Movement_LeagueCheckStepAside
    WaitMovement
    SetVar VAR_VICTORY_ROAD_LEAGUECHECK_STATE, 1
    ReleaseAll
    End

VictoryRoad_PaulTrigger:
    GoToIfSet FLAG_DEFEATED_PAUL_VICTORY_ROAD, VictoryRoad_PaulIgnore
    LockAll
    PlaySE SEQ_SE_DP_KAIDAN2
    ClearFlag FLAG_HIDE_VICTORY_ROAD_1F_PAUL
    AddObject LOCALID_PAUL
    ApplyMovement LOCALID_PAUL, VictoryRoad_Movement_PaulArrive
    ApplyMovement LOCALID_PLAYER, VictoryRoad_Movement_PlayerFacePaul
    WaitMovement
    Common_SetRivalBGM
    BufferPlayerName 0
    Message VictoryRoad1F_Text_PaulNotice
    WaitButton
    CloseMessage
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    GoToIfEq VAR_0x8005, 40, VictoryRoad_PaulStepNorth
    GoToIfEq VAR_0x8005, 42, VictoryRoad_PaulStepSouth
    GoTo VictoryRoad_PaulWalkOver

VictoryRoad_PaulStepNorth:
    ApplyMovement LOCALID_PAUL, VictoryRoad_Movement_PaulStepNorth
    GoTo VictoryRoad_PaulWalkOver

VictoryRoad_PaulStepSouth:
    ApplyMovement LOCALID_PAUL, VictoryRoad_Movement_PaulStepSouth
    GoTo VictoryRoad_PaulWalkOver

VictoryRoad_PaulWalkOver:
    ApplyMovement LOCALID_PAUL, VictoryRoad_Movement_PaulWalkWest
    WaitMovement
    Message VictoryRoad1F_Text_PaulPreBattle
    WaitButton
    CloseMessage
    StartTrainerBattle TRAINER_PAUL_VICTORY_ROAD
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, VictoryRoad_PaulBlackOut
    BufferPlayerName 0
    Message VictoryRoad1F_Text_PaulAfterBattle
    WaitButton
    CloseMessage
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    GoToIfEq VAR_0x8005, 40, VictoryRoad_PaulReturnSouth
    GoToIfEq VAR_0x8005, 42, VictoryRoad_PaulReturnNorth
    GoTo VictoryRoad_PaulLeave

VictoryRoad_PaulReturnSouth:
    ApplyMovement LOCALID_PAUL, VictoryRoad_Movement_PaulStepSouth
    GoTo VictoryRoad_PaulLeave

VictoryRoad_PaulReturnNorth:
    ApplyMovement LOCALID_PAUL, VictoryRoad_Movement_PaulStepNorth
    GoTo VictoryRoad_PaulLeave

VictoryRoad_PaulLeave:
    ApplyMovement LOCALID_PAUL, VictoryRoad_Movement_PaulWalkEast
    WaitMovement
    PlaySE SEQ_SE_DP_KAIDAN2
    RemoveObject LOCALID_PAUL
    WaitSE SEQ_SE_DP_KAIDAN2
    SetFlag FLAG_DEFEATED_PAUL_VICTORY_ROAD
    Common_FadeToDefaultMusic2
    ReleaseAll
    End

VictoryRoad_PaulBlackOut:
    SetFlag FLAG_HIDE_VICTORY_ROAD_1F_PAUL
    BlackOutFromBattle
    ReleaseAll
    End

VictoryRoad_PaulIgnore:
    End

VictoryRoad_CounterpartTrigger:
    GoToIfSet FLAG_DEFEATED_VICTORY_ROAD_COUNTERPART, VictoryRoad_CounterpartIgnore
    LockAll
    ClearFlag FLAG_HIDE_VICTORY_ROAD_COUNTERPART
    AddObject LOCALID_COUNTERPART
    ApplyMovement LOCALID_PLAYER, VictoryRoad_Movement_Exclaim
    WaitMovement
    Common_SetCounterpartBGM
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    CallIfEq VAR_0x8004, 14, VictoryRoad_PlayerX14
    CallIfEq VAR_0x8004, 16, VictoryRoad_PlayerX16
    ApplyMovement LOCALID_COUNTERPART, VictoryRoad_Movement_Counterpart8North
    WaitMovement
    GetPlayerGender VAR_0x8000
    CallIfEq VAR_0x8000, GENDER_MALE, VictoryRoad_DawnPreBattle
    CallIfEq VAR_0x8000, GENDER_FEMALE, VictoryRoad_LucasPreBattle
    End

VictoryRoad_PlayerX14:
    ApplyMovement LOCALID_COUNTERPART, VictoryRoad_Movement_CounterpartLeft
    Return

VictoryRoad_PlayerX16:
    ApplyMovement LOCALID_COUNTERPART, VictoryRoad_Movement_CounterpartRight
    Return

VictoryRoad_DawnPreBattle:
    Message VictoryRoad1F_Text_DawnPreBattle
    WaitButton
    CloseMessage
    GetPlayerStarterSpecies VAR_0x800C
    GoToIfEq VAR_0x800C, SPECIES_TURTWIG, VictoryRoad_DawnBattleTurtwig
    GoToIfEq VAR_0x800C, SPECIES_CHIMCHAR, VictoryRoad_DawnBattleChimchar
    GoTo VictoryRoad_DawnBattlePiplup

VictoryRoad_DawnBattleTurtwig:
    StartTrainerBattle TRAINER_DAWN_VICTORY_ROAD_TURTWIG, TRAINER_NONE
    GoTo VictoryRoad_DawnBattleResult

VictoryRoad_DawnBattleChimchar:
    StartTrainerBattle TRAINER_DAWN_VICTORY_ROAD_CHIMCHAR, TRAINER_NONE
    GoTo VictoryRoad_DawnBattleResult

VictoryRoad_DawnBattlePiplup:
    StartTrainerBattle TRAINER_DAWN_VICTORY_ROAD_PIPLUP, TRAINER_NONE
    GoTo VictoryRoad_DawnBattleResult

VictoryRoad_DawnBattleResult:
    CheckWonBattle VAR_0x800C
    GoToIfEq VAR_0x800C, FALSE, VictoryRoad_CounterpartBlackOut
    Message VictoryRoad_Text_DawnDefeat
    WaitButton
    CloseMessage
    GoTo VictoryRoad_CounterpartLeave

VictoryRoad_LucasPreBattle:
    Message VictoryRoad1F_Text_LucasPreBattle
    WaitButton
    CloseMessage
    GetPlayerStarterSpecies VAR_0x800C
    GoToIfEq VAR_0x800C, SPECIES_TURTWIG, VictoryRoad_LucasBattleTurtwig
    GoToIfEq VAR_0x800C, SPECIES_CHIMCHAR, VictoryRoad_LucasBattleChimchar
    GoTo VictoryRoad_LucasBattlePiplup

VictoryRoad_LucasBattleTurtwig:
    StartTrainerBattle TRAINER_LUCAS_VICTORY_ROAD_TURTWIG, TRAINER_NONE
    GoTo VictoryRoad_LucasBattleResult

VictoryRoad_LucasBattleChimchar:
    StartTrainerBattle TRAINER_LUCAS_VICTORY_ROAD_CHIMCHAR, TRAINER_NONE
    GoTo VictoryRoad_LucasBattleResult

VictoryRoad_LucasBattlePiplup:
    StartTrainerBattle TRAINER_LUCAS_VICTORY_ROAD_PIPLUP, TRAINER_NONE
    GoTo VictoryRoad_LucasBattleResult

VictoryRoad_LucasBattleResult:
    CheckWonBattle VAR_0x800C
    GoToIfEq VAR_0x800C, FALSE, VictoryRoad_CounterpartBlackOut
    Message VictoryRoad_Text_LucasDefeat
    WaitButton
    CloseMessage
    GoTo VictoryRoad_CounterpartLeave

VictoryRoad_CounterpartLeave:
    ApplyMovement LOCALID_COUNTERPART, VictoryRoad_Movement_CounterpartLeave
    WaitMovement
    SetFlag FLAG_HIDE_VICTORY_ROAD_COUNTERPART
    RemoveObject LOCALID_COUNTERPART
    Common_FadeToDefaultMusic
    SetFlag FLAG_DEFEATED_VICTORY_ROAD_COUNTERPART
    ReleaseAll
    End

VictoryRoad_CounterpartBlackOut:
    SetFlag FLAG_HIDE_VICTORY_ROAD_COUNTERPART
    BlackOutFromBattle
    ReleaseAll
    End

VictoryRoad_CounterpartIgnore:
    End

    .balign 4, 0
VictoryRoad_Movement_Exclaim:
    WalkOnSpotNormalSouth
    EmoteExclamationMark
    EndMovement

    .balign 4, 0
VictoryRoad_Movement_PlayerStepBack:
    WalkNormalSouth
    EndMovement

    .balign 4, 0
VictoryRoad_Movement_LeagueCheckStepAside:
    WalkNormalNorth
    WalkNormalEast 2
    FaceWest
    EndMovement

    .balign 4, 0
VictoryRoad_Movement_PaulArrive:
    Delay8 4
    EmoteExclamationMark
    Delay8 2
    EndMovement

    .balign 4, 0
VictoryRoad_Movement_PlayerFacePaul:
    Delay8 4
    WalkOnSpotNormalEast
    EndMovement

    .balign 4, 0
VictoryRoad_Movement_PaulStepNorth:
    WalkNormalNorth
    EndMovement

    .balign 4, 0
VictoryRoad_Movement_PaulStepSouth:
    WalkNormalSouth
    EndMovement

    .balign 4, 0
VictoryRoad_Movement_PaulWalkWest:
    WalkNormalWest 4
    EndMovement

    .balign 4, 0
VictoryRoad_Movement_PaulWalkEast:
    WalkNormalEast 4
    EndMovement

    .balign 4, 0
VictoryRoad_Movement_CounterpartLeft:
    WalkNormalWest
    EndMovement

    .balign 4, 0
VictoryRoad_Movement_CounterpartRight:
    WalkNormalEast
    EndMovement

    .balign 4, 0
VictoryRoad_Movement_Counterpart8North:
    WalkNormalNorth 8
    EndMovement

    .balign 4, 0
VictoryRoad_Movement_CounterpartLeave:
    WalkNormalSouth 8
    EndMovement

    .balign 4, 0
