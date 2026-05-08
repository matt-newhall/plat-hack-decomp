#include "macros/btlcmd.inc"

    .data

_000:
    CompareMonDataToValue OPCODE_EQU, BTLSCR_MSG_TEMP, BATTLEMON_SPEED_STAGE, 0, _end
    PlayBattleAnimation BTLSCR_MSG_TEMP, BATTLE_ANIMATION_HELD_ITEM
    Wait
    WaitButtonABTime 15
    PlayBattleAnimation BTLSCR_MSG_TEMP, BATTLE_ANIMATION_STAT_DROP
    Wait
    // The {1} lowered {0}'s {2}!
    PrintMessage BattleStrings_Text_TheItemLoweredPokemonsStat_Ally, TAG_NICKNAME_ITEM_STAT, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30
    RemoveItem BTLSCR_MSG_TEMP
    UpdateMonData OPCODE_SUB, BTLSCR_MSG_TEMP, BATTLEMON_SPEED_STAGE, 1

_end:
    End
