#include "macros/btlcmd.inc"


_000:
    CompareMonDataToValue OPCODE_FLAG_SET, BTLSCR_DEFENDER, BATTLEMON_MOVE_EFFECTS_MASK, MOVE_EFFECT_SEMI_INVULNERABLE, _056
    CompareMonDataToValue OPCODE_FLAG_SET, BTLSCR_DEFENDER, BATTLEMON_VOLATILE_STATUS, VOLATILE_CONDITION_TRANSFORM, _056
    CompareMonDataToValue OPCODE_FLAG_SET, BTLSCR_ATTACKER, BATTLEMON_VOLATILE_STATUS, VOLATILE_CONDITION_TRANSFORM, _056
    CheckSubstitute BTLSCR_DEFENDER, _056
    WaitButtonABTime 15
    ShowAbilityPopupAuto BTLSCR_ATTACKER
    Transform
    MarkEntryAbilitiesAnnounced BTLSCR_ATTACKER
    ChangeForm BTLSCR_ATTACKER
    Wait
    // {0} transformed into {1}!
    PrintMessage BattleStrings_Text_PokemonTransformedIntoPokemon_AllyAlly, TAG_NICKNAME_POKE, BTLSCR_ATTACKER, BTLSCR_DEFENDER
    Wait
    WaitButtonABTime 30

_056:
    End
