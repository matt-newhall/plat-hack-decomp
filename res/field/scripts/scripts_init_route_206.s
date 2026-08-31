#include "macros/scrcmd.inc"


    InitScriptEntry_OnResume 2
    InitScriptEntry_OnTransition 1
    InitScriptEntry_OnFrameTable InitScriptFrameTable
    InitScriptEntryEnd

InitScriptFrameTable:
    InitScriptGoToIfEqual VAR_EXITING_SKIRMISH_ZONE_SUCCESS 1, 9
    InitScriptFrameTableEnd


    InitScriptEnd
