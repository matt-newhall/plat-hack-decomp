#include "macros/btlcmd.inc"


_000:
    TryPowerOfAlchemy _009
    ShowAbilityPopupSaved BTLSCR_MSG_BATTLER_TEMP
    WaitAbilityPopupAnim
    // {0} acquired {1}!
    PrintMessage BattleStrings_Text_PokemonAcquiredAbility_Ally, TAG_NICKNAME_ABILITY, BTLSCR_MSG_BATTLER_TEMP, BTLSCR_MSG_BATTLER_TEMP
    Wait
    WaitButtonABTime 30
    HideAbilityPopup

_009:
    Call BATTLE_SUBSCRIPT_FAINT_MON
    End
