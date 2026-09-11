#include "macros/btlcmd.inc"


_000:
    GoToIfStatStageChangeUnblocked _apply
    End

_apply:
    ShowAbilityPopupAuto BTLSCR_MSG_BATTLER_TEMP
    Call BATTLE_SUBSCRIPT_UPDATE_STAT_STAGE
    End
