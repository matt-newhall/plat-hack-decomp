#include "macros/btlcmd.inc"

    .data

_000:
    ShowAbilityPopupAuto BTLSCR_MSG_BATTLER_TEMP
    // {0} filled the air with Neutralizing Gas!
    PrintMessage BattleStrings_Text_NeutralizingGasAnnounced_Ally, TAG_NICKNAME, BTLSCR_MSG_BATTLER_TEMP
    Wait
    WaitButtonABTime 30
    End
