#include "macros/scrcmd.inc"
#include "res/text/bank/special_met_location_names.h"
#include "res/text/bank/trainers_school.h"


    ScriptEntry _0032
    ScriptEntry _0154
    ScriptEntry _0167
    ScriptEntry _0169
    ScriptEntry _017C
    ScriptEntry _018F
    ScriptEntry _01A2
    ScriptEntry _01A4
    ScriptEntry _01A6
    ScriptEntry _02E4
    ScriptEntry _03D9
    ScriptEntry _049C
    ScriptEntryEnd

_0032:
    GoToIfSet FLAG_UNK_0x01F4, TrainersSchool_RivalAlreadyLeft
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    BufferPlayerName 0
    BufferRivalName 1
    Message 0
    PlayFanfare SEQ_FANFA4
    BufferPlayerName 0
    Message 1
    WaitFanfare
    RemoveItem ITEM_PARCEL, 1, VAR_RESULT
    BufferPlayerName 0
    BufferRivalName 1
    Message 2
    SetVar VAR_0x8004, ITEM_TOWN_MAP
    SetVar VAR_0x8005, 1
    Common_GiveItemQuantity
    BufferRivalName 1
    Message 3
    CloseMessage
    GetPlayerDir VAR_RESULT
    SetVar VAR_0x8008, VAR_RESULT
    GoToIfEq VAR_0x8008, 0, _00A4
    GoToIfEq VAR_0x8008, 2, _00BE
    GoTo _00D8
    End

_00A4:
    ApplyMovement 1, _0114
    ApplyMovement LOCALID_PLAYER, _0138
    WaitMovement
    GoTo _00F2
    End

_00BE:
    ApplyMovement 1, _0124
    ApplyMovement LOCALID_PLAYER, _0148
    WaitMovement
    GoTo _00F2
    End

_00D8:
    ApplyMovement 1, _0124
    ApplyMovement LOCALID_PLAYER, _0148
    WaitMovement
    GoTo _00F2
    End

_00F2:
    PlaySE SEQ_SE_DP_KAIDAN2
    RemoveObject 1
    SetFlag FLAG_UNK_0x01F4
    WaitSE SEQ_SE_DP_KAIDAN2
    SetVar VAR_POKETCH_CAMPAIGN_STATE, 1
    SetFlag FLAG_TALKED_TO_TRAINERS_SCHOOL_RIVAL
    SetVar VAR_JUBILIFE_CITY_STATE, 3
    ClearFlag FLAG_HIDE_JUBILIFE_CITY_POKETCH_CO_PRESIDENT
    SetFlag FLAG_HIDE_JUBILIFE_CITY_LOOKER
    ClearFlag FLAG_HIDE_JUBILIFE_GALACTIC_GRUNTS
    ClearFlag FLAG_HIDE_JUBILIFE_ROWAN
    ClearFlag FLAG_HIDE_JUBILIFE_CITY_COUNTERPART
    ReleaseAll
    End

TrainersSchool_RivalAlreadyLeft:
    End

    .balign 4, 0
_0114:
    WalkFastEast
    WalkFastSouth 8
    WalkOnSpotFastSouth
    EndMovement

    .balign 4, 0
_0124:
    WalkFastSouth 4
    WalkFastEast
    WalkFastSouth 4
    WalkOnSpotFastSouth
    EndMovement

    .balign 4, 0
_0138:
    Delay8
    WalkOnSpotNormalEast
    WalkOnSpotNormalSouth
    EndMovement

    .balign 4, 0
_0148:
    Delay8
    WalkOnSpotNormalSouth
    EndMovement

_0154:
    NPCMessage 4
    End

_0167:
    End

_0169:
    NPCMessage 6
    End

_017C:
    NPCMessage 8
    End

_018F:
    NPCMessage 7
    End

_01A2:
    End

_01A4:
    End

_01A6:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet FLAG_UNK_0x0112, _02A8
    GoToIfSet FLAG_UNK_0x010C, _02BD
    Message 9
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_YES, _01E7
    GoToIfEq VAR_RESULT, MENU_NO, _02D3
    End

_01E7:
    Message 10
    CloseMessage
    GetPlayerStarterSpecies VAR_RESULT
    GoToIfEq VAR_RESULT, SPECIES_TURTWIG, _0220
    GoToIfEq VAR_RESULT, SPECIES_CHIMCHAR, _022E
    GoTo _0212
    End

_0212:
    StartTrainerBattle TRAINER_SCHOOL_KID_HARRISON
    GoTo _023C
    End

_0220:
    StartTrainerBattle TRAINER_SCHOOL_KID_HARRISON
    GoTo _023C
    End

_022E:
    StartTrainerBattle TRAINER_SCHOOL_KID_HARRISON
    GoTo _023C
    End

_023C:
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, _02DE
    SetFlag FLAG_UNK_0x010C
    GoToIfSet FLAG_UNK_0x010D, _0274
    GoToIfUnset FLAG_UNK_0x010D, _0269
    End

_0269:
    Message 12
    WaitButton
    CloseMessage
    ReleaseAll
    End

_0274:
    Message 13
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_NO, TrainersSchool_RefusedEgg
    GetPartyCount VAR_RESULT
    GoToIfGe VAR_RESULT, 6, TrainersSchool_PartyIsFull
    PlayFanfare SEQ_FANFA4
    WaitFanfare
    GetRandom VAR_RESULT, 14
    CallIfEq VAR_RESULT, 0, TrainersSchool_GiveEgg0
    CallIfEq VAR_RESULT, 1, TrainersSchool_GiveEgg1
    CallIfEq VAR_RESULT, 2, TrainersSchool_GiveEgg2
    CallIfEq VAR_RESULT, 3, TrainersSchool_GiveEgg3
    CallIfEq VAR_RESULT, 4, TrainersSchool_GiveEgg4
    CallIfEq VAR_RESULT, 5, TrainersSchool_GiveEgg5
    CallIfEq VAR_RESULT, 6, TrainersSchool_GiveEgg6
    CallIfEq VAR_RESULT, 7, TrainersSchool_GiveEgg7
    CallIfEq VAR_RESULT, 8, TrainersSchool_GiveEgg8
    CallIfEq VAR_RESULT, 9, TrainersSchool_GiveEgg9
    CallIfEq VAR_RESULT, 10, TrainersSchool_GiveEgg10
    CallIfEq VAR_RESULT, 11, TrainersSchool_GiveEgg11
    CallIfEq VAR_RESULT, 12, TrainersSchool_GiveEgg12
    CallIfEq VAR_RESULT, 13, TrainersSchool_GiveEgg13
    SetFlag FLAG_UNK_0x0112
    GoTo _02A8
    End

TrainersSchool_GiveEgg0:
    GiveEgg SPECIES_CLEFFA, SPECIAL_METLOC_NAME_TRAVELING_MAN
    Return

TrainersSchool_GiveEgg1:
    GiveEgg SPECIES_IGGLYBUFF, SPECIAL_METLOC_NAME_TRAVELING_MAN
    Return

TrainersSchool_GiveEgg2:
    GiveEgg SPECIES_PICHU, SPECIAL_METLOC_NAME_TRAVELING_MAN
    Return

TrainersSchool_GiveEgg3:
    GiveEgg SPECIES_MANTYKE, SPECIAL_METLOC_NAME_TRAVELING_MAN
    Return

TrainersSchool_GiveEgg4:
    GiveEgg SPECIES_AZURILL, SPECIAL_METLOC_NAME_TRAVELING_MAN
    Return

TrainersSchool_GiveEgg5:
    GiveEgg SPECIES_SMOOCHUM, SPECIAL_METLOC_NAME_TRAVELING_MAN
    Return

TrainersSchool_GiveEgg6:
    GiveEgg SPECIES_ELEKID, SPECIAL_METLOC_NAME_TRAVELING_MAN
    Return

TrainersSchool_GiveEgg7:
    GiveEgg SPECIES_MAGBY, SPECIAL_METLOC_NAME_TRAVELING_MAN
    Return

TrainersSchool_GiveEgg8:
    GiveEgg SPECIES_BONSLY, SPECIAL_METLOC_NAME_TRAVELING_MAN
    Return

TrainersSchool_GiveEgg9:
    GiveEgg SPECIES_MIME_JR, SPECIAL_METLOC_NAME_TRAVELING_MAN
    Return

TrainersSchool_GiveEgg10:
    GiveEgg SPECIES_CHINGLING, SPECIAL_METLOC_NAME_TRAVELING_MAN
    Return

TrainersSchool_GiveEgg11:
    GiveEgg SPECIES_TYROGUE, SPECIAL_METLOC_NAME_TRAVELING_MAN
    Return

TrainersSchool_GiveEgg12:
    GiveEgg SPECIES_TOGEPI, SPECIAL_METLOC_NAME_TRAVELING_MAN
    Return

TrainersSchool_GiveEgg13:
    GiveEgg SPECIES_BUDEW, SPECIAL_METLOC_NAME_TRAVELING_MAN
    Return

TrainersSchool_RefusedEgg:
    Message 28
    WaitButton
    CloseMessage
    ReleaseAll
    End

TrainersSchool_PartyIsFull:
    Message 29
    WaitButton
    CloseMessage
    ReleaseAll
    End

_02A8:
    Message 14
    WaitButton
    CloseMessage
    ReleaseAll
    End

_02B3:
    Common_MessageBagIsFull
    CloseMessage
    ReleaseAll
    End

_02BD:
    GoToIfSet FLAG_UNK_0x010D, _0274
    Message 12
    WaitButton
    CloseMessage
    ReleaseAll
    End

_02D3:
    Message 11
    WaitButton
    CloseMessage
    ReleaseAll
    End

_02DE:
    BlackOutFromBattle
    ReleaseAll
    End

_02E4:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet FLAG_UNK_0x010D, _039C
    Message 15
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_YES, _031A
    GoToIfEq VAR_RESULT, MENU_NO, _03A7
    End

_031A:
    Message 16
    CloseMessage
    GetPlayerStarterSpecies VAR_RESULT
    GoToIfEq VAR_RESULT, SPECIES_TURTWIG, _0353
    GoToIfEq VAR_RESULT, SPECIES_CHIMCHAR, _0361
    GoTo _0345
    End

_0345:
    StartTrainerBattle TRAINER_SCHOOL_KID_CHRISTINE
    GoTo _036F
    End

_0353:
    StartTrainerBattle TRAINER_SCHOOL_KID_CHRISTINE
    GoTo _036F
    End

_0361:
    StartTrainerBattle TRAINER_SCHOOL_KID_CHRISTINE
    GoTo _036F
    End

_036F:
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, _03D3
    SetFlag FLAG_UNK_0x010D
    GoToIfSet FLAG_UNK_0x010C, _03BD
    GoToIfUnset FLAG_UNK_0x010C, _03B2
    End

_039C:
    Message 18
    WaitButton
    CloseMessage
    ReleaseAll
    End

_03A7:
    Message 17
    WaitButton
    CloseMessage
    ReleaseAll
    End

_03B2:
    Message 18
    WaitButton
    CloseMessage
    ReleaseAll
    End

_03BD:
    GoToIfSet FLAG_UNK_0x0112, _03B2
    Message 19
    WaitButton
    CloseMessage
    ReleaseAll
    End

_03D3:
    BlackOutFromBattle
    ReleaseAll
    End

_03D9:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    Message 20
    GoTo _03EA
    End

_03EA:
    Message 21
    InitGlobalTextMenu 7, 2, 0, VAR_RESULT
    AddMenuEntryImm 0, 0
    AddMenuEntryImm 1, 1
    AddMenuEntryImm 2, 2
    AddMenuEntryImm 3, 3
    AddMenuEntryImm 4, 4
    AddMenuEntryImm 5, 5
    ShowMenuMultiColumn 2
    SetVar VAR_0x8008, VAR_RESULT
    GoToIfEq VAR_0x8008, 0, _045F
    GoToIfEq VAR_0x8008, 1, _046A
    GoToIfEq VAR_0x8008, 2, _0475
    GoToIfEq VAR_0x8008, 3, _0480
    GoToIfEq VAR_0x8008, 4, _048B
    GoTo _0496
    End

_045F:
    Message 22
    GoTo _03EA
    End

_046A:
    Message 23
    GoTo _03EA
    End

_0475:
    Message 24
    GoTo _03EA
    End

_0480:
    Message 25
    GoTo _03EA
    End

_048B:
    Message 26
    GoTo _03EA
    End

_0496:
    CloseMessage
    ReleaseAll
    End

_049C:
    EventMessage 27
    End

    .balign 4, 0
