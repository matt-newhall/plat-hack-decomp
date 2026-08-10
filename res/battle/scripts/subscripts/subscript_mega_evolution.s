#include "macros/btlcmd.inc"

_000:
    CompareMonDataToValue OPCODE_FLAG_NOT, BTLSCR_MSG_TEMP, BATTLEMON_VOLATILE_STATUS, VOLATILE_CONDITION_SUBSTITUTE, _016
    PlayBattleAnimation BTLSCR_MSG_TEMP, BATTLE_ANIMATION_SUB_OUT
    Wait
    RestoreSprite BTLSCR_MSG_TEMP
    Wait
    PlayBattleAnimation BTLSCR_MSG_TEMP, BATTLE_ANIMATION_SUB_IN
    Wait

_016:
    // {0}'s {1} is reacting to {2}'s Mega Ring!
    PrintMessage BattleStrings_Text_MegaStoneReacting_Ally, TAG_NICKNAME_ITEM_TRNAME, BTLSCR_MSG_BATTLER_TEMP, BTLSCR_MSG_BATTLER_TEMP, BTLSCR_MSG_BATTLER_TEMP
    Wait
    WaitButtonABTime 30
    PlayBattleAnimation BTLSCR_MSG_TEMP, BATTLE_ANIMATION_MEGA_EVOLUTION
    WaitTime 265
    ChangeForm BTLSCR_MSG_TEMP
    Wait
    // Replay the send-out animation and cry so the new sprite introduces itself.
    // Skipped behind a Substitute, where the mon is not the visible sprite.
    CompareMonDataToValue OPCODE_FLAG_SET, BTLSCR_MSG_TEMP, BATTLEMON_VOLATILE_STATUS, VOLATILE_CONDITION_SUBSTITUTE, _entry_anim_done
    PlayEntryAnimation BTLSCR_MSG_TEMP
    Wait

_entry_anim_done:
    // {0} has Mega Evolved into Mega {1}!
    PrintMessage BattleStrings_Text_MegaEvolved_Ally, TAG_NICKNAME_POKE, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30
    CompareMonDataToValue OPCODE_FLAG_NOT, BTLSCR_MSG_TEMP, BATTLEMON_VOLATILE_STATUS, VOLATILE_CONDITION_SUBSTITUTE, _058
    PlayBattleAnimation BTLSCR_MSG_TEMP, BATTLE_ANIMATION_SUB_OUT
    Wait
    RefreshSprite BTLSCR_MSG_TEMP
    Wait
    PlayBattleAnimation BTLSCR_MSG_TEMP, BATTLE_ANIMATION_SUB_IN
    Wait

_058:
    End
