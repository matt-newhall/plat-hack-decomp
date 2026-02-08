#include "macros/btlcmd.inc"

    .data

_000:
    // The uproar woke up the {0}!
    PrintMessage pl_msg_00000368_00305, TAG_NICKNAME, BTLSCR_MSG_TEMP
    Wait 
    SetHealthbarStatus BTLSCR_MSG_TEMP, BATTLE_ANIMATION_NONE
    WaitButtonABTime 30
    UpdateMonData OPCODE_FLAG_OFF, BTLSCR_MSG_TEMP, BATTLEMON_STATUS, MON_CONDITION_SLEEP
    UpdateMonData OPCODE_FLAG_OFF, BTLSCR_MSG_TEMP, BATTLEMON_VOLATILE_STATUS, VOLATILE_CONDITION_NIGHTMARE
    End 
