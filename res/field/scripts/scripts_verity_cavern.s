#include "macros/scrcmd.inc"
#include "res/field/events/events_verity_cavern.h"


    ScriptEntry VerityCavern_OnTransition
    ScriptEntryEnd

VerityCavern_OnTransition:
    SetFlag FLAG_FIRST_ARRIVAL_VERITY_CAVERN
    End

    .balign 4, 0
