#include "macros/btlcmd.inc"


_000:
    GoToIfStatStageChangeUnblocked _apply
    End

_apply:
    ShowAbilityPopupAuto BTLSCR_SIDE_EFFECT_MON
    Call BATTLE_SUBSCRIPT_UPDATE_STAT_STAGE
    End
