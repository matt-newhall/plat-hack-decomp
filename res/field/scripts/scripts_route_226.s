#include "macros/scrcmd.inc"
#include "res/text/bank/route_226.h"


    ScriptEntry Route226_ArrowSignpostSurvivalArea
    ScriptEntry Route226_ArrowSignpostRt227Rt228
    ScriptEntry Route226_GruntGuardConvo
    ScriptEntryEnd

Route226_ArrowSignpostSurvivalArea:
    ShowArrowSign Route226_Text_SignRt226SurvivalArea
    End

Route226_ArrowSignpostRt227Rt228:
    ShowArrowSign Route226_Text_SignRt227Rt228
    End

Route226_GruntGuardConvo:
    Message Route226_Text_Grunt_KeepEyesPeeled
    CloseMessage
    Message Route226_Text_Grunt_SoLongAgo
    CloseMessage
    Message Route226_Text_Grunt_CommanderCharon
    CloseMessage 
    Message Route226_Text_SignGrunt_FromTheWest
    CloseMessage
    End
