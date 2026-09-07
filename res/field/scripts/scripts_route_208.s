#include "macros/scrcmd.inc"
#include "res/text/bank/route_208.h"


    ScriptEntry Route208_ArrowSignpostMtCoronet
    ScriptEntry Route208_ArrowSignpostHearthomeCity
    ScriptEntry Route208_SignBerryMastersHouse
    ScriptEntry Route208_BlackBelt
    ScriptEntry Route208_TrainerTips
    ScriptEntryEnd

Route208_ArrowSignpostMtCoronet:
    ShowArrowSign Route208_Text_SignRt208MtCoronet
    End

Route208_ArrowSignpostHearthomeCity:
    ShowArrowSign Route208_Text_SignRt208HearthomeCity
    End

Route208_SignBerryMastersHouse:
    ShowLandmarkSign Route208_Text_SignBerryMastersHouse
    End

Route208_TrainerTips:
    ShowScrollingSign Route208_Text_TrainerTipsWatchBerrySoilColor
    End

Route208_BlackBelt:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message Route208_Text_GoToRoute209
    WaitButton
    CloseMessage
    ReleaseAll
    End

    .balign 4, 0
