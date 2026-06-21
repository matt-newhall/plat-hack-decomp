#include "macros/scrcmd.inc"
#include "res/text/bank/solaceon_ruins_room_7.h"
#include "res/field/events/events_solaceon_ruins_room_7.h"


    ScriptEntry SolaceonRuinsRoom7_Inscription
    ScriptEntry SolaceonRuinsRoom7_Fantina
    ScriptEntryEnd

SolaceonRuinsRoom7_Inscription:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    MessageUnown SolaceonRuinsRoom7_Text_AllLivesTouchOtherLives
    WaitButton
    CloseMessage
    ReleaseAll
    End

SolaceonRuinsRoom7_Fantina:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message 1
    WaitButton
    CloseMessage
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    GoToIfEq 0x8004, 6, SolaceonRuinsRoom7_FantinaX6
    GoTo SolaceonRuinsRoom7_FantinaXNot6

SolaceonRuinsRoom7_FantinaX6:
    ApplyMovement LOCALID_FANTINA, SolaceonRuinsRoom7_Movement_FantinaWalkAroundPlayer
    WaitMovement
    PlayFanfare SEQ_SE_DP_KAIDAN2
    RemoveObject LOCALID_FANTINA
    WaitFanfare
    SetFlag FLAG_HIDE_HEARTHOME_CITY_GYM_GUIDE
    ReleaseAll
    End

SolaceonRuinsRoom7_FantinaXNot6:
    ApplyMovement LOCALID_FANTINA, SolaceonRuinsRoom7_Movement_FantinaWalkEast
    WaitMovement
    PlayFanfare SEQ_SE_DP_KAIDAN2
    RemoveObject LOCALID_FANTINA
    WaitFanfare
    SetFlag FLAG_HIDE_HEARTHOME_CITY_GYM_GUIDE
    ReleaseAll
    End

    .balign 4, 0
SolaceonRuinsRoom7_Movement_FantinaWalkAroundPlayer:
    WalkNormalNorth 1
    WalkNormalEast 2
    WalkNormalSouth 1
    WalkNormalEast 2
    EndMovement

    .balign 4, 0
SolaceonRuinsRoom7_Movement_FantinaWalkEast:
    WalkNormalEast 4
    EndMovement

