#include "macros/btlcmd.inc"


_000:
    TryPowerOfAlchemy _010
    // {0} acquired {1}!
    PrintMessage BattleStrings_Text_PokemonAcquiredAbility_Ally, TAG_NICKNAME_ABILITY, BTLSCR_MSG_BATTLER_TEMP, BTLSCR_MSG_BATTLER_TEMP
    Wait
    WaitButtonABTime 30

_010:
    IncrementGameRecord BTLSCR_FAINTED_MON, BATTLER_TYPE_SOLO_ENEMY, RECORD_FAINTED_IN_BATTLE
    IncrementGameRecord BTLSCR_FAINTED_MON, BATTLER_TYPE_SOLO_PLAYER, RECORD_FAINTED_ENEMY_MON
    PlayFaintAnimation 
    Wait 
    HealthbarSlideOut BTLSCR_FAINTED_MON
    // {0} fainted!
    PrintMessage BattleStrings_Text_PokemonFainted_Ally, TAG_NICKNAME, BTLSCR_FAINTED_MON
    Wait 
    WaitButtonABTime 30
    CompareVarToValue OPCODE_FLAG_SET, BTLVAR_BATTLE_CTX_STATUS_2, SYSCTL_NO_EXPERIENCE_GIVEN, _023

_023:
    End 
