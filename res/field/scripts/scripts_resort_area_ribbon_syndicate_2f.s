#include "macros/scrcmd.inc"
#include "res/text/bank/resort_area_ribbon_syndicate_2f.h"

    .data

    ScriptEntry _0012
    ScriptEntry _02E8
    ScriptEntry _02FB
    ScriptEntry _030E
    ScriptEntryEnd

_0012:
    PlayFanfare SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet FLAG_UNK_0x0AA5, _00E2
    GoToIfEq VAR_MAP_LOCAL_A, 1, _00E2
    GetFirstNonEggInParty VAR_MAP_LOCAL_0
    BufferPlayerName 0
    BufferPartyMonNickname 1, VAR_MAP_LOCAL_0
    Message 0
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_NO, _0058
    GoTo _0063

_0058:
    Message 1
    WaitABXPadPress
    CloseMessage
    ReleaseAll
    End

_0063:
    Message 2
    CloseMessage
    Call _0160
    GoTo _0074

_0074:
    Message 3
    GetRandom VAR_RESULT, 4
    GoToIfEq VAR_RESULT, 0, _00AA
    GoToIfEq VAR_RESULT, 1, _00B3
    GoToIfEq VAR_RESULT, 2, _00BC
    GoTo _00C5

_00AA:
    Message 4
    GoTo _00CE

_00B3:
    Message 5
    GoTo _00CE

_00BC:
    Message 6
    GoTo _00CE

_00C5:
    Message 7
    GoTo _00CE

_00CE:
    CloseMessage
    PlayFanfare SEQ_SE_DP_FW367
    Call _00ED
    WaitABXPadPress
    CloseMessage
    ReleaseAll
    End

_00E2:
    Message 9
    WaitABXPadPress
    CloseMessage
    ReleaseAll
    End

_00ED:
    GetRandom VAR_RESULT, 100
    GoToIfLt VAR_RESULT, 5, _0113
    GoToIfLt VAR_RESULT, 30, _0124
    GoTo _0135

_0113:
    ScrCmd_1BA 30, VAR_MAP_LOCAL_0
    Call _0146
    Message 8
    Return

_0124:
    ScrCmd_1BA 10, VAR_MAP_LOCAL_0
    Call _0146
    Message 10
    Return

_0135:
    ScrCmd_1BA 5, VAR_MAP_LOCAL_0
    Call _0146
    Message 11
    Return

_0146:
    WaitFanfare SEQ_SE_DP_FW367
    SetFlag FLAG_UNK_0x0AA5
    SetVar VAR_MAP_LOCAL_A, 1
    ApplyMovement 1, _02DC
    WaitMovement
    Return

_0160:
    GetPlayerMapPos VAR_0x8005, VAR_0x8006
    GoToIfEq VAR_0x8005, 11, _0193
    GoToIfEq VAR_0x8005, 13, _01AB
    GoToIfEq VAR_0x8006, 4, _01C3
    GoTo _01DB

_0193:
    ApplyMovement LOCALID_PLAYER, _026C
    ApplyMovement 2, _0210
    WaitMovement
    GoTo _01F3

_01AB:
    ApplyMovement LOCALID_PLAYER, _0280
    ApplyMovement 2, _0224
    WaitMovement
    GoTo _01F3

_01C3:
    ApplyMovement LOCALID_PLAYER, _0294
    ApplyMovement 2, _023C
    WaitMovement
    GoTo _01F3

_01DB:
    ApplyMovement LOCALID_PLAYER, _02AC
    ApplyMovement 2, _0250
    WaitMovement
    GoTo _01F3

_01F3:
    ApplyMovement 0, _02C4
    ApplyMovement 1, _02CC
    ApplyMovement 3, _02D4
    WaitMovement
    Return

    .balign 4, 0
_0210:
    MoveAction_015 2
    MoveAction_013 2
    MoveAction_015 3
    MoveAction_034
    EndMovement

    .balign 4, 0
_0224:
    MoveAction_013
    MoveAction_015
    MoveAction_013
    MoveAction_015 4
    MoveAction_034
    EndMovement

    .balign 4, 0
_023C:
    MoveAction_015 2
    MoveAction_013 2
    MoveAction_015 3
    MoveAction_034
    EndMovement

    .balign 4, 0
_0250:
    MoveAction_015
    MoveAction_013
    MoveAction_015 2
    MoveAction_013
    MoveAction_015 2
    MoveAction_034
    EndMovement

    .balign 4, 0
_026C:
    MoveAction_015 3
    MoveAction_013 2
    MoveAction_015 2
    MoveAction_033
    EndMovement

    .balign 4, 0
_0280:
    MoveAction_063 2
    MoveAction_013 2
    MoveAction_015 3
    MoveAction_033
    EndMovement

    .balign 4, 0
_0294:
    MoveAction_013
    MoveAction_015 3
    MoveAction_013 2
    MoveAction_015
    MoveAction_033
    EndMovement

    .balign 4, 0
_02AC:
    MoveAction_063 2
    MoveAction_015 3
    MoveAction_013
    MoveAction_015
    MoveAction_033
    EndMovement

    .balign 4, 0
_02C4:
    MoveAction_013
    EndMovement

    .balign 4, 0
_02CC:
    MoveAction_015 3
    EndMovement

    .balign 4, 0
_02D4:
    MoveAction_012 4
    EndMovement

    .balign 4, 0
_02DC:
    MoveAction_012
    MoveAction_033
    EndMovement

_02E8:
    PlayFanfare SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message 12
    WaitABXPadPress
    CloseMessage
    ReleaseAll
    End

_02FB:
    PlayFanfare SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message 13
    WaitABXPadPress
    CloseMessage
    ReleaseAll
    End

_030E:
    PlayFanfare SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message 14
    WaitABXPadPress
    CloseMessage
    ReleaseAll
    End

    .byte 0
    .byte 0
    .byte 0
