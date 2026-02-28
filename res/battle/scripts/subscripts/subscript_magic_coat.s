#include "macros/btlcmd.inc"


_000:
    PrintAttackMessage 
    Wait 
    WaitButtonABTime 15
    CheckIgnorableAbility CHECK_HAVE, BTLSCR_DEFENDER, ABILITY_MAGIC_BOUNCE, _003
    // {0}’s {1} was bounced back by Magic Coat!
    PrintMessage BattleStrings_Text_PokemonsMoveWasBouncedBackByMagicCoat_Ally, TAG_NICKNAME_MOVE, BTLSCR_ATTACKER, BTLSCR_ATTACKER
    Wait 
    WaitButtonABTime 30
    GoTo _005

_003:
    // {0}’s {1} was bounced back by Magic Bounce!
    PrintMessage BattleStrings_Text_MagicBounceTriggered_Ally, TAG_NICKNAME_MOVE, BTLSCR_ATTACKER, BTLSCR_ATTACKER
    Wait 
    WaitButtonABTime 30

_005:
    MagicCoat 
    UpdateVar OPCODE_FLAG_OFF, BTLVAR_BATTLE_CTX_STATUS, SYSCTL_PLAYED_MOVE_ANIMATION
    End 
