#include "macros/btlcmd.inc"

    .data

_loop:
    SetupEjectPack
    CompareVarToValue OPCODE_EQU, BTLVAR_SCRIPT_TEMP, 0, _done
    Call BATTLE_SUBSCRIPT_EJECT_PACK_SWITCH
    GoTo _loop

_done:
    End
