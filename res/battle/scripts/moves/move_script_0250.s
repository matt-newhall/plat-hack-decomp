#include "macros/btlcmd.inc"


_000:
    UpdateVar OPCODE_FLAG_ON, BTLVAR_BATTLE_CTX_STATUS, SYSCTL_HIT_DURING_DIVE
    // {0} was trapped in the vortex!
    BufferMessage BattleStrings_Text_PokemonWasTrappedInAVortex_Ally, TAG_NICKNAME, BTLSCR_DEFENDER
    GoToEffectScript 
