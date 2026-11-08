#include "macros/scrcmd.inc"
#include "res/text/bank/route_210_north.h"


    ScriptEntry Route210North_BlackBelt
    ScriptEntry Route210North_ArrowSignCelesticTown
    ScriptEntry Route210North_SignGrandmaWilmasHouse
    ScriptEntry Route210North_RivalTrainer
    ScriptEntry Route210North_RivalMon
    ScriptEntry Route210North_PaulTrainer
    ScriptEntry Route210North_PaulMon
    ScriptEntryEnd

Route210North_BlackBelt:
    NPCMessage Route210North_Text_HowDoesDefogWork
    End

Route210North_ArrowSignCelesticTown:
    ShowArrowSign Route210North_Text_SignCelesticTown
    End

Route210North_RivalTrainer:
    PlaySE SEQ_SE_CONFIRM
    Message Route210North_Text_RivalBattling
    WaitButton
    CloseMessage
    End

Route210North_RivalMon:
    PlaySE SEQ_SE_CONFIRM
    PlayCry SPECIES_HERACROSS
    Message Route210North_Text_RivalMon
    WaitCry
    WaitButton
    CloseMessage
    End

Route210North_PaulTrainer:
    PlaySE SEQ_SE_CONFIRM
    Message Route210North_Text_PaulBattling
    WaitButton
    CloseMessage
    End

Route210North_PaulMon:
    PlaySE SEQ_SE_CONFIRM
    PlayCry SPECIES_ELECTIVIRE
    Message Route210North_Text_PaulMon
    WaitCry
    WaitButton
    CloseMessage
    End

Route210North_SignGrandmaWilmasHouse:
    ShowLandmarkSign Route210North_Text_SignGrandmaWilmasHouse
    End

    .balign 4, 0
