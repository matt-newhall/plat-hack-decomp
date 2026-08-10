#include "macros/scrcmd.inc"
#include "res/text/bank/route_219.h"
#include "res/field/events/events_route_219.h"


    ScriptEntry Route_219_ArrowSignSandgemBeach
    ScriptEntry Route_219_Worker
    ScriptEntry Route_219_BlockAccessToPalPark
    ScriptEntryEnd

Route_219_ArrowSignSandgemBeach:
    ShowArrowSign Route219_Text_SignSandgemBeach
    End

Route_219_Worker:
    NPCMessage Route219_Text_WorkerNoAccess
    End

Route_219_BlockAccessToPalPark:
    LockAll
    GetPlayerMapPos VAR_0x8000, VAR_0x8001
    CallIfEq VAR_0x8000, 170, Route_219_WorkerBlockPlayerWest
    CallIfEq VAR_0x8000, 171, Route_219_WorkerBlockPlayerWest
    CallIfEq VAR_0x8000, 172, Route_219_WorkerBlockPlayerWest
    CallIfEq VAR_0x8000, 173, Route_219_WorkerBlockPlayerWest
    CallIfEq VAR_0x8000, 174, Route_219_WorkerBlockPlayerWest
    CallIfEq VAR_0x8000, 175, Route_219_WorkerBlockPlayerWest
    CallIfEq VAR_0x8000, 177, Route_219_WorkerBlockPlayerEast
    CallIfEq VAR_0x8000, 178, Route_219_WorkerBlockPlayerEast
    CallIfEq VAR_0x8000, 179, Route_219_WorkerBlockPlayerEast
    CallIfEq VAR_0x8000, 180, Route_219_WorkerBlockPlayerEast
    CallIfEq VAR_0x8000, 181, Route_219_WorkerBlockPlayerEast
    NPCMessage Route219_Text_WorkerNoAccess
    ApplyMovement LOCALID_PLAYER, Route_219_PlayerWalkNorth
    WaitMovement
    ApplyMovement LOCALID_WORKER, Route_219_WorkerReset
    WaitMovement
    ReleaseAll
    End

    .balign 4, 0
Route_219_WorkerBlockPlayerWest:
    ApplyMovement LOCALID_WORKER, Route_219_WorkerTurnWestAndEmote
    WaitMovement
    Return

    .balign 4, 0
Route_219_WorkerTurnWestAndEmote:
    FaceWest
    EmoteExclamationMark
    Delay16
    EndMovement

    .balign 4, 0
Route_219_WorkerBlockPlayerEast:
    ApplyMovement LOCALID_WORKER, Route_219_WorkerTurnEastAndEmote
    WaitMovement
    Return

    .balign 4, 0
Route_219_WorkerTurnEastAndEmote:
    FaceEast
    EmoteExclamationMark
    Delay16
    EndMovement

    .balign 4, 0
Route_219_PlayerWalkNorth:
    WalkNormalNorth
    EndMovement

    .balign 4, 0
Route_219_WorkerReset:
    FaceNorth
    EndMovement
