#include "macros/btlcmd.inc"


_000:
    ShowAbilityPopupAuto BTLSCR_MSG_BATTLER_TEMP
    // The effects of the weather disappeared.
    PrintMessage BattleStrings_Text_AnnounceWeatherDisabled, TAG_NONE
    Wait
    WaitButtonABTime 30
    End
