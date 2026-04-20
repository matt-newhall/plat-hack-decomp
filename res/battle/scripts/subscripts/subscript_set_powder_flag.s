#include "macros/btlcmd.inc"

    .data

_000:
    CheckSubstitute BTLSCR_DEFENDER, _015
    CheckPowderImmunity BTLSCR_DEFENDER, _010
    PrintAttackMessage
    Wait
    CompareVarToValue OPCODE_FLAG_SET, BTLVAR_MOVE_STATUS_FLAGS, MOVE_STATUS_MISSED|MOVE_STATUS_SEMI_INVULNERABLE, _005
    PlayMoveAnimation BTLSCR_ATTACKER
    Wait
    SetTurnFlag BTLSCR_DEFENDER, TURN_FLAG_POWDERED, 1
    // {0} was covered in powder!
    PrintMessage BattleStrings_Text_PowderUsed_Ally, TAG_NICKNAME, BTLSCR_DEFENDER
    Wait
    WaitButtonABTime 30
    End

_005:
    UpdateVar OPCODE_FLAG_ON, BTLVAR_MOVE_STATUS_FLAGS, MOVE_STATUS_NO_MORE_WORK
    WaitButtonABTime 30
    // {0} evaded the attack!
    PrintMessage BattleStrings_Text_PokemonEvadedTheAttack_Ally, TAG_NICKNAME, BTLSCR_DEFENDER
    Wait
    WaitButtonABTime 30
    End

_010:
    PrintAttackMessage
    Wait
    WaitButtonABTime 30
    UpdateVar OPCODE_FLAG_ON, BTLVAR_MOVE_STATUS_FLAGS, MOVE_STATUS_NO_MORE_WORK
    // It doesn't affect {0}...
    PrintMessage BattleStrings_Text_ItDoesntAffectPokemon_Ally, TAG_NICKNAME, BTLSCR_DEFENDER
    Wait
    WaitButtonABTime 30
    End

_015:
    UpdateVar OPCODE_FLAG_ON, BTLVAR_MOVE_STATUS_FLAGS, MOVE_STATUS_FAILED
    End
