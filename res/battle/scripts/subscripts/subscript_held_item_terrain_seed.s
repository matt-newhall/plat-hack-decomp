#include "macros/btlcmd.inc"

    .data

_000:
    CompareVarToValue OPCODE_EQU, BTLVAR_MSG_TEMP, BATTLE_STAT_SP_DEFENSE, _sp_defense

_defense:
    CheckContrary BTLSCR_MSG_TEMP, _defense_contrary
    CompareMonDataToValue OPCODE_EQU, BTLSCR_MSG_TEMP, BATTLEMON_DEFENSE_STAGE, 12, _end
    PlayBattleAnimation BTLSCR_MSG_TEMP, BATTLE_ANIMATION_HELD_ITEM
    Wait
    WaitButtonABTime 15
    PlayBattleAnimation BTLSCR_MSG_TEMP, BATTLE_ANIMATION_STAT_BOOST
    Wait
    CheckSimple BTLSCR_MSG_TEMP, _defense_raise_2
    // The {1} raised {0}'s {2}!
    PrintMessage BattleStrings_Text_TheItemRaisedPokemonsStat_Ally, TAG_NICKNAME_ITEM_STAT, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30
    RemoveItem BTLSCR_MSG_TEMP
    UpdateMonData OPCODE_ADD, BTLSCR_MSG_TEMP, BATTLEMON_DEFENSE_STAGE, 1
    GoTo _end

_defense_raise_2:
    // The {1} sharply raised {0}'s {2}!
    PrintMessage BattleStrings_Text_TheItemSharplyRaisedPokemonsStat_Ally, TAG_NICKNAME_ITEM_STAT, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30
    RemoveItem BTLSCR_MSG_TEMP
    UpdateMonData OPCODE_ADD, BTLSCR_MSG_TEMP, BATTLEMON_DEFENSE_STAGE, 2
    GoTo _end

_defense_contrary:
    CompareMonDataToValue OPCODE_EQU, BTLSCR_MSG_TEMP, BATTLEMON_DEFENSE_STAGE, 0, _end
    PlayBattleAnimation BTLSCR_MSG_TEMP, BATTLE_ANIMATION_HELD_ITEM
    Wait
    WaitButtonABTime 15
    PlayBattleAnimation BTLSCR_MSG_TEMP, BATTLE_ANIMATION_STAT_DROP
    Wait
    CheckSimple BTLSCR_MSG_TEMP, _defense_lower_2
    // The {1} lowered {0}'s {2}!
    PrintMessage BattleStrings_Text_TheItemLoweredPokemonsStat_Ally, TAG_NICKNAME_ITEM_STAT, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30
    RemoveItem BTLSCR_MSG_TEMP
    UpdateMonData OPCODE_SUB, BTLSCR_MSG_TEMP, BATTLEMON_DEFENSE_STAGE, 1
    GoTo _end

_defense_lower_2:
    // The {1} harshly lowered {0}'s {2}!
    PrintMessage BattleStrings_Text_TheItemHarshlyLoweredPokemonsStat_Ally, TAG_NICKNAME_ITEM_STAT, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30
    RemoveItem BTLSCR_MSG_TEMP
    UpdateMonData OPCODE_SUB, BTLSCR_MSG_TEMP, BATTLEMON_DEFENSE_STAGE, 2
    GoTo _end

_sp_defense:
    CheckContrary BTLSCR_MSG_TEMP, _sp_defense_contrary
    CompareMonDataToValue OPCODE_EQU, BTLSCR_MSG_TEMP, BATTLEMON_SP_DEFENSE_STAGE, 12, _end
    PlayBattleAnimation BTLSCR_MSG_TEMP, BATTLE_ANIMATION_HELD_ITEM
    Wait
    WaitButtonABTime 15
    PlayBattleAnimation BTLSCR_MSG_TEMP, BATTLE_ANIMATION_STAT_BOOST
    Wait
    CheckSimple BTLSCR_MSG_TEMP, _sp_defense_raise_2
    // The {1} raised {0}'s {2}!
    PrintMessage BattleStrings_Text_TheItemRaisedPokemonsStat_Ally, TAG_NICKNAME_ITEM_STAT, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30
    RemoveItem BTLSCR_MSG_TEMP
    UpdateMonData OPCODE_ADD, BTLSCR_MSG_TEMP, BATTLEMON_SP_DEFENSE_STAGE, 1
    GoTo _end

_sp_defense_raise_2:
    // The {1} sharply raised {0}'s {2}!
    PrintMessage BattleStrings_Text_TheItemSharplyRaisedPokemonsStat_Ally, TAG_NICKNAME_ITEM_STAT, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30
    RemoveItem BTLSCR_MSG_TEMP
    UpdateMonData OPCODE_ADD, BTLSCR_MSG_TEMP, BATTLEMON_SP_DEFENSE_STAGE, 2
    GoTo _end

_sp_defense_contrary:
    CompareMonDataToValue OPCODE_EQU, BTLSCR_MSG_TEMP, BATTLEMON_SP_DEFENSE_STAGE, 0, _end
    PlayBattleAnimation BTLSCR_MSG_TEMP, BATTLE_ANIMATION_HELD_ITEM
    Wait
    WaitButtonABTime 15
    PlayBattleAnimation BTLSCR_MSG_TEMP, BATTLE_ANIMATION_STAT_DROP
    Wait
    CheckSimple BTLSCR_MSG_TEMP, _sp_defense_lower_2
    // The {1} lowered {0}'s {2}!
    PrintMessage BattleStrings_Text_TheItemLoweredPokemonsStat_Ally, TAG_NICKNAME_ITEM_STAT, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30
    RemoveItem BTLSCR_MSG_TEMP
    UpdateMonData OPCODE_SUB, BTLSCR_MSG_TEMP, BATTLEMON_SP_DEFENSE_STAGE, 1
    GoTo _end

_sp_defense_lower_2:
    // The {1} harshly lowered {0}'s {2}!
    PrintMessage BattleStrings_Text_TheItemHarshlyLoweredPokemonsStat_Ally, TAG_NICKNAME_ITEM_STAT, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30
    RemoveItem BTLSCR_MSG_TEMP
    UpdateMonData OPCODE_SUB, BTLSCR_MSG_TEMP, BATTLEMON_SP_DEFENSE_STAGE, 2
    GoTo _end

_end:
    End
