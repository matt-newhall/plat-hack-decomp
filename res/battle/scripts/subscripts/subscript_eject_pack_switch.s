#include "macros/btlcmd.inc"


_000:
    PlayBattleAnimation BTLSCR_SIDE_EFFECT_MON, BATTLE_ANIMATION_HELD_ITEM
    Wait
    WaitButtonABTime 15

_normal_switch:
    // {0}'s {1} activated!
    PrintMessage BattleStrings_Text_PokemonsEjectButtonActivated_Ally, TAG_NICKNAME_ITEM, BTLSCR_SIDE_EFFECT_MON, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30
    RemoveItem BTLSCR_SIDE_EFFECT_MON
    CompareVarToValue OPCODE_FLAG_NOT, BTLVAR_BATTLE_TYPE, BATTLE_TYPE_TRAINER, _player_switch
    CompareVarToValue OPCODE_FLAG_SET, BTLVAR_SIDE_EFFECT_MON, 1, _ai_switch
    GoTo _player_switch

_player_switch:
    UpdateVarFromVar OPCODE_SET, BTLVAR_SWITCHED_MON, BTLVAR_SIDE_EFFECT_MON
    DeletePokemon BTLSCR_SWITCHED_MON
    Wait
    HealthbarSlideOut BTLSCR_SWITCHED_MON
    Wait
    UpdateVar OPCODE_FLAG_ON, BTLVAR_BATTLE_CTX_STATUS_2, SYSCTL_UTURN_ACTIVE
    GoToSubscript BATTLE_SUBSCRIPT_SHOW_PARTY_LIST

_ai_switch:
    UpdateVarFromVar OPCODE_SET, BTLVAR_SWITCHED_MON, BTLVAR_SIDE_EFFECT_MON
    DeletePokemon BTLSCR_SWITCHED_MON
    Wait
    HealthbarSlideOut BTLSCR_SWITCHED_MON
    Wait
    UpdateVar OPCODE_FLAG_ON, BTLVAR_BATTLE_CTX_STATUS_2, SYSCTL_UTURN_ACTIVE
    SwitchAndUpdateMon BTLSCR_SWITCHED_MON
    Wait
    PokemonSendOut BTLSCR_SWITCHED_MON
    WaitTime 72
    HealthbarSlideIn BTLSCR_SWITCHED_MON
    Wait
    UpdateVar OPCODE_SET, BTLVAR_MSG_TEMP, MOVE_ROAR
    Call BATTLE_SUBSCRIPT_HAZARDS_CHECK
    End
