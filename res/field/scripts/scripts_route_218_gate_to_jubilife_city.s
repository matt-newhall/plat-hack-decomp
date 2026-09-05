#include "macros/scrcmd.inc"
#include "res/text/bank/route_218_gate_to_jubilife_city.h"


    ScriptEntry Route218GateToJubilifeCity_Policeman
    ScriptEntry Route218GateToJubilifeCity_Fisherman
    ScriptEntryEnd

Route218GateToJubilifeCity_Policeman:
    NPCMessage Route218GateToJubilifeCity_Text_GreatFishingHole
    End

Route218GateToJubilifeCity_Fisherman:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message Route218GateToJubilifeCity_Text_OldRodGoodRight
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_YES, Route218GateToJubilifeCity_AcceptOldRod
    GoToIfEq VAR_RESULT, MENU_NO, Route218GateToJubilifeCity_RefuseOldRod
    End

Route218GateToJubilifeCity_DidYouNeedTips:
    BufferItemName 0, VAR_0x8004
    Message Route218GateToJubilifeCity_Text_DidYouNeedTips
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_YES, Route218GateToJubilifeCity_ExplainFishing
    GoToIfEq VAR_RESULT, MENU_NO, Route218GateToJubilifeCity_FishingTwiceTheFun
    End

Route218GateToJubilifeCity_ExplainFishing:
    Message Route218GateToJubilifeCity_Text_ExplainFishing
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route218GateToJubilifeCity_FishingTwiceTheFun:
    Message Route218GateToJubilifeCity_Text_FishingTwiceTheFun
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route218GateToJubilifeCity_RefuseOldRod:
    Message Route218GateToJubilifeCity_Text_YouDontLikeToFish
    WaitButton
    CloseMessage
    ReleaseAll
    End

Route218GateToJubilifeCity_AcceptOldRod:
    Message Route218GateToJubilifeCity_Text_HereYouGo
    WaitButton
    CloseMessage
    ReleaseAll
    End

    .balign 4, 0
