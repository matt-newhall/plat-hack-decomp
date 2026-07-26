#include "macros/scrcmd.inc"


    InitScriptEntry_OnTransition 1
    InitScriptEntry_OnResume 5
    InitScriptEntry_OnFrameTable InitScriptFrameTable
    InitScriptEntryEnd

InitScriptFrameTable:
    InitScriptGoToIfEqual VAR_PALMER_FIGHT_AREA_EVENT, 1, 6
    InitScriptGoToIfEqual VAR_UNK_0x40D9, 1, 2
    InitScriptGoToIfEqual VAR_UNK_0x40D9, 2, 3
    InitScriptFrameTableEnd

    InitScriptEnd
