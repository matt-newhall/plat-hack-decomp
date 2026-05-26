#include "macros/btlcmd.inc"


_000:
    TryPluck _024, _023
    // {0} stole and ate its foe’s {1}!
    PrintMessage BattleStrings_Text_PokemonStoleAndAteItsFoesItem_Ally, TAG_NICKNAME_ITEM, BTLSCR_ATTACKER, BTLSCR_DEFENDER
    Wait 
    WaitButtonABTime 30
    RemoveItem BTLSCR_DEFENDER
    UpdateVarFromVar OPCODE_SET, BTLVAR_MSG_BATTLER_TEMP, BTLVAR_ATTACKER
    CompareVarToValue OPCODE_EQU, BTLVAR_SCRIPT_TEMP, 0, _023
    CallFromVar BTLVAR_SCRIPT_TEMP

_023:
    End 

_024:
    ShowAbilityPopupAuto BTLSCR_DEFENDER
    // {0}’s item cannot be removed!
    PrintMessage BattleStrings_Text_PokemonsItemCannotBeRemoved_Ally, TAG_NICKNAME, BTLSCR_DEFENDER
    Wait
    WaitButtonABTime 30
    End
