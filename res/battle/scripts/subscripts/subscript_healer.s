#include "macros/btlcmd.inc"


_000:
    ShowAbilityPopupAuto BTLSCR_SIDE_EFFECT_MON
    UpdateMonData OPCODE_SET, BTLSCR_MSG_TEMP, BATTLEMON_STATUS, MON_CONDITION_NONE
    UpdateMonData OPCODE_FLAG_OFF, BTLSCR_MSG_TEMP, BATTLEMON_VOLATILE_STATUS, VOLATILE_CONDITION_NIGHTMARE
    // {0} was cured of its {2} status!
    PrintMessage BattleStrings_Text_PokemonWasCuredOfItsStatus_Ally, TAG_NICKNAME_ABILITY_STATUS, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait
    SetHealthbarStatus BTLSCR_MSG_TEMP, BATTLE_ANIMATION_NONE
    WaitButtonABTime 30
    End
