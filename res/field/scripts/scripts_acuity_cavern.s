#include "macros/scrcmd.inc"
#include "res/field/events/events_acuity_cavern.h"


    ScriptEntry AcuityCavern_OnTransition
    ScriptEntryEnd

AcuityCavern_OnTransition:
    SetFlag FLAG_FIRST_ARRIVAL_ACUITY_CAVERN
    End

    .balign 4, 0
