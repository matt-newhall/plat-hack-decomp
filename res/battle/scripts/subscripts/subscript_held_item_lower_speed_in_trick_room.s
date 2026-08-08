#include "macros/btlcmd.inc"

    .data

_000:
    CheckContrary BTLSCR_MSG_TEMP, _contrary
    CompareMonDataToValue OPCODE_EQU, BTLSCR_MSG_TEMP, BATTLEMON_SPEED_STAGE, 0, _end
    GoTo _apply

_contrary:
    CompareMonDataToValue OPCODE_EQU, BTLSCR_MSG_TEMP, BATTLEMON_SPEED_STAGE, 12, _end

_apply:
    PlayBattleAnimation BTLSCR_MSG_TEMP, BATTLE_ANIMATION_HELD_ITEM
    Wait
    WaitButtonABTime 15
    CheckContrary BTLSCR_MSG_TEMP, _raise
    PlayBattleAnimation BTLSCR_MSG_TEMP, BATTLE_ANIMATION_STAT_DROP
    Wait
    // The {1} lowered {0}'s {2}!
    PrintMessage BattleStrings_Text_TheItemLoweredPokemonsStat_Ally, TAG_NICKNAME_ITEM_STAT, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30
    RemoveItem BTLSCR_MSG_TEMP
    UpdateMonData OPCODE_SUB, BTLSCR_MSG_TEMP, BATTLEMON_SPEED_STAGE, 1
    GoTo _end

_raise:
    PlayBattleAnimation BTLSCR_MSG_TEMP, BATTLE_ANIMATION_STAT_BOOST
    Wait
    // The {1} raised {0}'s {2}!
    PrintMessage BattleStrings_Text_TheItemRaisedPokemonsStat_Ally, TAG_NICKNAME_ITEM_STAT, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30
    RemoveItem BTLSCR_MSG_TEMP
    UpdateMonData OPCODE_ADD, BTLSCR_MSG_TEMP, BATTLEMON_SPEED_STAGE, 1

_end:
    End
