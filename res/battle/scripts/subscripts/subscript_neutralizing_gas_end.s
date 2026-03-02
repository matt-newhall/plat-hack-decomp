#include "macros/btlcmd.inc"

    .data

_000:
    // Neutralizing Gas wore off!
    PrintMessage BattleStrings_Text_AnnounceNeutralizingGasDisabled, TAG_NONE
    Wait
    WaitButtonABTime 30
    End
