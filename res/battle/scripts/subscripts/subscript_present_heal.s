#include "macros/btlcmd.inc"


_000:
    CompareVarToValue OPCODE_FLAG_SET, BTLVAR_MOVE_STATUS_FLAGS, MOVE_STATUS_DID_NOT_HIT, _014
    PrintAttackMessage 
    Wait 
    Call BATTLE_SUBSCRIPT_RECOVER_HP

_014:
    End 
