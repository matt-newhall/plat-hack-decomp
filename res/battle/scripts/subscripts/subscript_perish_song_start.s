#include "macros/btlcmd.inc"

    .data

_000:
    TryPerishSong _009
    Call BATTLE_SUBSCRIPT_ATTACK_MESSAGE_AND_ANIMATION
    // All Pokémon hearing the song will faint in three turns!
    PrintMessage pl_msg_00000368_00822, TAG_NONE
    Wait
    WaitButtonABTime 30
    UpdateVar OPCODE_SET, BTLVAR_MSG_MOVE_TEMP, MOVE_PERISH_SONG
    UpdateVar OPCODE_SET, BTLVAR_MSG_ABILITY_TEMP, ABILITY_SOUNDPROOF
    UpdateVar OPCODE_SET, BTLVAR_BATTLER_SPEED_TEMP, 0

_003:
    GetMonBySpeedOrder BTLVAR_MSG_BATTLER_TEMP
    CheckIsPranksterDarkImmune BTLSCR_MSG_TEMP, _005
    CheckIsPerishSongAffected BTLSCR_MSG_TEMP, _007
    // {0}'s {1} blocks {2}!
    PrintMessage pl_msg_00000368_00689, TAG_NICKNAME_ABILITY_MOVE, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30
    GoTo _007

_005:
    // It doesn't affect {0}...
    PrintMessage pl_msg_00000368_00027, TAG_NICKNAME, BTLSCR_MSG_TEMP
    Wait
    WaitButtonABTime 30

_007:
    UpdateVar OPCODE_ADD, BTLVAR_BATTLER_SPEED_TEMP, 1
    GoToIfValidMon BTLVAR_BATTLER_SPEED_TEMP, _003
    End

_009:
    UpdateVar OPCODE_FLAG_ON, BTLVAR_MOVE_STATUS_FLAGS, MOVE_STATUS_009
    End
