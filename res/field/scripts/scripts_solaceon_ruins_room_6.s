#include "macros/scrcmd.inc"
#include "res/text/bank/solaceon_ruins_room_6.h"
#include "res/field/events/events_solaceon_ruins_room_6.h"


    ScriptEntry SolaceonRuinsRoom6_OnTransition
    ScriptEntry SolaceonRuinsRoom6_Counterpart
    ScriptEntry SolaceonRuinsRoom6_CounterpartBattle
    ScriptEntryEnd

SolaceonRuinsRoom6_OnTransition:
    GetPlayerGender VAR_MAP_LOCAL_0
    GoToIfEq VAR_MAP_LOCAL_0, GENDER_MALE, SolaceonRuinsRoom6_SetCounterpartGraphicsDawn
    GoToIfEq VAR_MAP_LOCAL_0, GENDER_FEMALE, SolaceonRuinsRoom6_SetCounterpartGraphicsLucas
    End

SolaceonRuinsRoom6_SetCounterpartGraphicsDawn:
    SetVar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_PLAYER_F
    End

SolaceonRuinsRoom6_SetCounterpartGraphicsLucas:
    SetVar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_PLAYER_M
    End

SolaceonRuinsRoom6_Counterpart:
    LockAll
    FacePlayer
    Message SolaceonRuinsRoom6_Text_CounterpartTalk
    WaitButton
    CloseMessage
    ReleaseAll
    End

SolaceonRuinsRoom6_CounterpartBattle:
    GoToIfSet FLAG_BEATEN_SOLACEON_RUINS_COUNTERPART, SolaceonRuinsRoom6_CounterpartBattleDone
    LockAll
    ApplyMovement LOCALID_SOLACEON_RUINS_ROOM_6_COUNTERPART, SolaceonRuinsRoom6_Movement_CounterpartNoticePlayer
    WaitMovement
    GetPlayerGender VAR_0x800C
    GoToIfEq VAR_0x800C, GENDER_MALE, SolaceonRuinsRoom6_CounterpartTauntDawn
    GoToIfEq VAR_0x800C, GENDER_FEMALE, SolaceonRuinsRoom6_CounterpartTauntLucas
    End

SolaceonRuinsRoom6_CounterpartBattleDone:
    End

SolaceonRuinsRoom6_CounterpartTauntDawn:
    BufferPlayerName 0
    Message SolaceonRuinsRoom6_Text_DawnNoticePlayer
    WaitButton
    CloseMessage
    GoTo SolaceonRuinsRoom6_CounterpartApproach

SolaceonRuinsRoom6_CounterpartTauntLucas:
    BufferPlayerName 0
    Message SolaceonRuinsRoom6_Text_LucasNoticePlayer
    WaitButton
    CloseMessage
    GoTo SolaceonRuinsRoom6_CounterpartApproach

SolaceonRuinsRoom6_CounterpartApproach:
    Common_SetCounterpartBGM
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    GoToIfEq VAR_0x8004, 4, SolaceonRuinsRoom6_CounterpartApproachX4
    GoToIfEq VAR_0x8004, 5, SolaceonRuinsRoom6_CounterpartApproachX5
    GoToIfEq VAR_0x8004, 6, SolaceonRuinsRoom6_CounterpartApproachX6
    End

SolaceonRuinsRoom6_CounterpartApproachX4:
    ApplyMovement LOCALID_SOLACEON_RUINS_ROOM_6_COUNTERPART, SolaceonRuinsRoom6_Movement_CounterpartApproachX4
    GoTo SolaceonRuinsRoom6_CounterpartChallenge

SolaceonRuinsRoom6_CounterpartApproachX5:
    ApplyMovement LOCALID_SOLACEON_RUINS_ROOM_6_COUNTERPART, SolaceonRuinsRoom6_Movement_CounterpartApproachX5
    GoTo SolaceonRuinsRoom6_CounterpartChallenge

SolaceonRuinsRoom6_CounterpartApproachX6:
    ApplyMovement LOCALID_SOLACEON_RUINS_ROOM_6_COUNTERPART, SolaceonRuinsRoom6_Movement_CounterpartApproachX6
    GoTo SolaceonRuinsRoom6_CounterpartChallenge

SolaceonRuinsRoom6_CounterpartChallenge:
    WaitMovement
    GoToIfEq VAR_0x800C, GENDER_MALE, SolaceonRuinsRoom6_CounterpartReadyDawn
    GoToIfEq VAR_0x800C, GENDER_FEMALE, SolaceonRuinsRoom6_CounterpartReadyLucas
    End

SolaceonRuinsRoom6_CounterpartReadyDawn:
    Message SolaceonRuinsRoom6_Text_DawnReady
    ShowYesNoMenu VAR_0x800D
    GoToIfEq VAR_0x800D, MENU_YES, SolaceonRuinsRoom6_DawnBattle
    GoToIfEq VAR_0x800D, MENU_NO, SolaceonRuinsRoom6_DawnDecline
    End

SolaceonRuinsRoom6_CounterpartReadyLucas:
    Message SolaceonRuinsRoom6_Text_LucasReady
    ShowYesNoMenu VAR_0x800D
    GoToIfEq VAR_0x800D, MENU_YES, SolaceonRuinsRoom6_LucasBattle
    GoToIfEq VAR_0x800D, MENU_NO, SolaceonRuinsRoom6_LucasDecline
    End

SolaceonRuinsRoom6_DawnBattle:
    Message SolaceonRuinsRoom6_Text_DawnHereICome
    WaitButton
    CloseMessage
    GetPlayerStarterSpecies VAR_0x800C
    GoToIfEq VAR_0x800C, SPECIES_TURTWIG, SolaceonRuinsRoom6_DawnBattleTurtwig
    GoToIfEq VAR_0x800C, SPECIES_CHIMCHAR, SolaceonRuinsRoom6_DawnBattleChimchar
    GoTo SolaceonRuinsRoom6_DawnBattlePiplup

SolaceonRuinsRoom6_DawnBattleTurtwig:
    StartTrainerBattle TRAINER_DAWN_SOLACEON_RUINS_TURTWIG, TRAINER_NONE
    GoTo SolaceonRuinsRoom6_DawnBattleResult

SolaceonRuinsRoom6_DawnBattleChimchar:
    StartTrainerBattle TRAINER_DAWN_SOLACEON_RUINS_CHIMCHAR, TRAINER_NONE
    GoTo SolaceonRuinsRoom6_DawnBattleResult

SolaceonRuinsRoom6_DawnBattlePiplup:
    StartTrainerBattle TRAINER_DAWN_SOLACEON_RUINS_PIPLUP, TRAINER_NONE
    GoTo SolaceonRuinsRoom6_DawnBattleResult

SolaceonRuinsRoom6_DawnBattleResult:
    CheckWonBattle VAR_0x800C
    GoToIfEq VAR_0x800C, FALSE, SolaceonRuinsRoom6_CounterpartBattleLost
    Message SolaceonRuinsRoom6_Text_DawnDefeat
    WaitButton
    CloseMessage
    GoTo SolaceonRuinsRoom6_CounterpartLeave

SolaceonRuinsRoom6_LucasBattle:
    Message SolaceonRuinsRoom6_Text_LucasHereICome
    WaitButton
    CloseMessage
    GetPlayerStarterSpecies VAR_0x800C
    GoToIfEq VAR_0x800C, SPECIES_TURTWIG, SolaceonRuinsRoom6_LucasBattleTurtwig
    GoToIfEq VAR_0x800C, SPECIES_CHIMCHAR, SolaceonRuinsRoom6_LucasBattleChimchar
    GoTo SolaceonRuinsRoom6_LucasBattlePiplup

SolaceonRuinsRoom6_LucasBattleTurtwig:
    StartTrainerBattle TRAINER_LUCAS_SOLACEON_RUINS_TURTWIG, TRAINER_NONE
    GoTo SolaceonRuinsRoom6_LucasBattleResult

SolaceonRuinsRoom6_LucasBattleChimchar:
    StartTrainerBattle TRAINER_LUCAS_SOLACEON_RUINS_CHIMCHAR, TRAINER_NONE
    GoTo SolaceonRuinsRoom6_LucasBattleResult

SolaceonRuinsRoom6_LucasBattlePiplup:
    StartTrainerBattle TRAINER_LUCAS_SOLACEON_RUINS_PIPLUP, TRAINER_NONE
    GoTo SolaceonRuinsRoom6_LucasBattleResult

SolaceonRuinsRoom6_LucasBattleResult:
    CheckWonBattle VAR_0x800C
    GoToIfEq VAR_0x800C, FALSE, SolaceonRuinsRoom6_CounterpartBattleLost
    Message SolaceonRuinsRoom6_Text_LucasDefeat
    WaitButton
    CloseMessage
    GoTo SolaceonRuinsRoom6_CounterpartLeave

SolaceonRuinsRoom6_CounterpartBattleLost:
    BlackOutFromBattle
    ReleaseAll
    End

SolaceonRuinsRoom6_CounterpartLeave:
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    GoToIfEq VAR_0x8004, 4, SolaceonRuinsRoom6_CounterpartLeaveX4
    GoToIfEq VAR_0x8004, 5, SolaceonRuinsRoom6_CounterpartLeaveX5
    GoToIfEq VAR_0x8004, 6, SolaceonRuinsRoom6_CounterpartLeaveX6
    End

SolaceonRuinsRoom6_CounterpartLeaveX4:
    ApplyMovement LOCALID_SOLACEON_RUINS_ROOM_6_COUNTERPART, SolaceonRuinsRoom6_Movement_CounterpartLeaveX4
    GoTo SolaceonRuinsRoom6_CounterpartLeaveFinish

SolaceonRuinsRoom6_CounterpartLeaveX5:
    ApplyMovement LOCALID_SOLACEON_RUINS_ROOM_6_COUNTERPART, SolaceonRuinsRoom6_Movement_CounterpartLeaveX5
    GoTo SolaceonRuinsRoom6_CounterpartLeaveFinish

SolaceonRuinsRoom6_CounterpartLeaveX6:
    ApplyMovement LOCALID_SOLACEON_RUINS_ROOM_6_COUNTERPART, SolaceonRuinsRoom6_Movement_CounterpartLeaveX6
    GoTo SolaceonRuinsRoom6_CounterpartLeaveFinish

SolaceonRuinsRoom6_CounterpartLeaveFinish:
    WaitMovement
    RemoveObject LOCALID_SOLACEON_RUINS_ROOM_6_COUNTERPART
    SetFlag FLAG_BEATEN_SOLACEON_RUINS_COUNTERPART
    ReleaseAll
    End

SolaceonRuinsRoom6_DawnDecline:
    Message SolaceonRuinsRoom6_Text_DawnDecline
    WaitButton
    CloseMessage
    GoTo SolaceonRuinsRoom6_CounterpartDeclineReturn

SolaceonRuinsRoom6_LucasDecline:
    Message SolaceonRuinsRoom6_Text_LucasDecline
    WaitButton
    CloseMessage
    GoTo SolaceonRuinsRoom6_CounterpartDeclineReturn

SolaceonRuinsRoom6_CounterpartDeclineReturn:
    ApplyMovement LOCALID_PLAYER, SolaceonRuinsRoom6_Movement_PlayerStepBack
    GoToIfEq VAR_0x8004, 4, SolaceonRuinsRoom6_CounterpartReturnX4
    GoToIfEq VAR_0x8004, 5, SolaceonRuinsRoom6_CounterpartReturnX5
    GoToIfEq VAR_0x8004, 6, SolaceonRuinsRoom6_CounterpartReturnX6
    End

SolaceonRuinsRoom6_CounterpartReturnX4:
    ApplyMovement LOCALID_SOLACEON_RUINS_ROOM_6_COUNTERPART, SolaceonRuinsRoom6_Movement_CounterpartReturnX4
    WaitMovement
    Common_FadeToDefaultMusic
    ReleaseAll
    End

SolaceonRuinsRoom6_CounterpartReturnX5:
    ApplyMovement LOCALID_SOLACEON_RUINS_ROOM_6_COUNTERPART, SolaceonRuinsRoom6_Movement_CounterpartReturnX5
    WaitMovement
    Common_FadeToDefaultMusic
    ReleaseAll
    End

SolaceonRuinsRoom6_CounterpartReturnX6:
    ApplyMovement LOCALID_SOLACEON_RUINS_ROOM_6_COUNTERPART, SolaceonRuinsRoom6_Movement_CounterpartReturnX6
    WaitMovement
    Common_FadeToDefaultMusic
    ReleaseAll
    End

    .balign 4, 0
SolaceonRuinsRoom6_Movement_CounterpartNoticePlayer:
    WalkOnSpotNormalNorth
    EmoteExclamationMark
    Delay16
    EndMovement

    .balign 4, 0
SolaceonRuinsRoom6_Movement_CounterpartApproachX4:
    WalkNormalWest
    WalkNormalNorth 2
    EndMovement

    .balign 4, 0
SolaceonRuinsRoom6_Movement_CounterpartApproachX5:
    WalkNormalNorth 2
    EndMovement

    .balign 4, 0
SolaceonRuinsRoom6_Movement_CounterpartApproachX6:
    WalkNormalEast
    WalkNormalNorth 2
    EndMovement

    .balign 4, 0
SolaceonRuinsRoom6_Movement_PlayerStepBack:
    LockDir
    WalkNormalNorth
    UnlockDir
    EndMovement

    .balign 4, 0
SolaceonRuinsRoom6_Movement_CounterpartReturnX4:
    WalkNormalSouth 2
    WalkNormalEast
    WalkOnSpotNormalNorth
    EndMovement

    .balign 4, 0
SolaceonRuinsRoom6_Movement_CounterpartReturnX5:
    WalkNormalSouth 2
    WalkOnSpotNormalNorth
    EndMovement

    .balign 4, 0
SolaceonRuinsRoom6_Movement_CounterpartReturnX6:
    WalkNormalSouth 2
    WalkNormalWest
    WalkOnSpotNormalNorth
    EndMovement

    .balign 4, 0
SolaceonRuinsRoom6_Movement_CounterpartLeaveX4:
    WalkNormalEast 2
    WalkNormalNorth 3
    WalkNormalEast
    EndMovement

    .balign 4, 0
SolaceonRuinsRoom6_Movement_CounterpartLeaveX5:
    WalkNormalEast
    WalkNormalNorth 3
    WalkNormalEast
    EndMovement

    .balign 4, 0
SolaceonRuinsRoom6_Movement_CounterpartLeaveX6:
    WalkNormalWest 1
    WalkNormalNorth 3
    WalkNormalEast 2
    EndMovement
