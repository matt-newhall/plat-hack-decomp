#include "macros/scrcmd.inc"


    InitScriptEntry_OnTransition 3
    InitScriptEntry_OnLoad 4
    InitScriptEntry_OnFrameTable Route228_InitScriptFrameTable
    InitScriptEntryEnd

Route228_InitScriptFrameTable:
    InitScriptGoToIfEqual VAR_ROUTE_228_ARGENTA_STATE, 0, 5
    InitScriptFrameTableEnd

    InitScriptEnd
