#include "macros/btlcmd.inc"

    .data

_000:
    // {0} was hurt by {1}'s Spiky Shield!
    PrintMessage BattleStrings_Text_SpikyShield_AllyHurtByAlly, TAG_NICKNAME_NICKNAME, BTLSCR_ATTACKER, BTLSCR_DEFENDER
    Wait
    WaitButtonABTime 30
    UpdateVarFromVar OPCODE_SET, BTLVAR_MSG_BATTLER_TEMP, BTLVAR_ATTACKER
    UpdateVar OPCODE_FLAG_ON, BTLVAR_BATTLE_CTX_STATUS, SYSCTL_SKIP_SPRITE_BLINK
    Call BATTLE_SUBSCRIPT_UPDATE_HP
    End
