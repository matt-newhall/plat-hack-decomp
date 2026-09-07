#include "macros/scrcmd.inc"
#include "res/text/bank/fight_area_mart.h"


    ScriptEntry FightAreaMart_CommonVendor
    ScriptEntry FightAreaMart_Unused
    ScriptEntry FightAreaMart_Socialite
    ScriptEntry FightAreaMart_Clown
    ScriptEntryEnd

FightAreaMart_CommonVendor:
    PokeMartCommonWithGreeting
    End

FightAreaMart_Unused:
    End

FightAreaMart_Socialite:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message FightAreaMart_Text_HoldWhatItems
    WaitButton
    CloseMessage
    ReleaseAll
    End

FightAreaMart_Clown:
    NPCMessage FightAreaMart_Text_TheyDontSellThat
    End

    .balign 4, 0
