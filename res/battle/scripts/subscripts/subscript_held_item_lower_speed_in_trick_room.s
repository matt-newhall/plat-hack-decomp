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
    CheckSimple BTLSCR_MSG_TEMP, _lower_2
    // The {1} lowered {0}'s {2}!
    PrintMessage BattleStrings_Text_TheItemLoweredPokemonsStat_Ally, TAG_NICKNAME_ITEM_STAT, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30
    RemoveItem BTLSCR_MSG_TEMP
    UpdateMonData OPCODE_SUB, BTLSCR_MSG_TEMP, BATTLEMON_SPEED_STAGE, 1
    GoTo _end

_lower_2:
    // The {1} harshly lowered {0}'s {2}!
    PrintMessage BattleStrings_Text_TheItemHarshlyLoweredPokemonsStat_Ally, TAG_NICKNAME_ITEM_STAT, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30
    RemoveItem BTLSCR_MSG_TEMP
    UpdateMonData OPCODE_SUB, BTLSCR_MSG_TEMP, BATTLEMON_SPEED_STAGE, 2
    GoTo _end

_raise:
    PlayBattleAnimation BTLSCR_MSG_TEMP, BATTLE_ANIMATION_STAT_BOOST
    Wait
    CheckSimple BTLSCR_MSG_TEMP, _raise_2
    // The {1} raised {0}'s {2}!
    PrintMessage BattleStrings_Text_TheItemRaisedPokemonsStat_Ally, TAG_NICKNAME_ITEM_STAT, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30
    RemoveItem BTLSCR_MSG_TEMP
    UpdateMonData OPCODE_ADD, BTLSCR_MSG_TEMP, BATTLEMON_SPEED_STAGE, 1
    GoTo _end

_raise_2:
    // The {1} sharply raised {0}'s {2}!
    PrintMessage BattleStrings_Text_TheItemSharplyRaisedPokemonsStat_Ally, TAG_NICKNAME_ITEM_STAT, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30
    RemoveItem BTLSCR_MSG_TEMP
    UpdateMonData OPCODE_ADD, BTLSCR_MSG_TEMP, BATTLEMON_SPEED_STAGE, 2

_end:
    End
