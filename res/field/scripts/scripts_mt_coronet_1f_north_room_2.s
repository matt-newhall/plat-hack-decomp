#include "macros/scrcmd.inc"


    ScriptEntry MtCoronet1FNorthRoom2_Unused
    ScriptEntry MtCoronet1FNorthRoom2_OnTransition
    ScriptEntry MtCoronet1FNorthRoom2_OnLoad
    ScriptEntryEnd

MtCoronet1FNorthRoom2_OnTransition:
    CallIfNe VAR_ICEBERG_RUINS_STATE, RUINS_STATE_CAUGHT_REGI, MtCoronet1FNorthRoom2_ResetIcebergRuinsState
    GoToIfUnset FLAG_REGIS_UNLOCKED, MtCoronet1FNorthRoom2_RemoveWarpIcebergRuinsWithRegice
    GoTo MtCoronet1FNorthRoom2_RemoveWarpIcebergRuinsWithoutRegice
    End

MtCoronet1FNorthRoom2_ResetIcebergRuinsState:
    SetVar VAR_ICEBERG_RUINS_STATE, 0
    Return

MtCoronet1FNorthRoom2_OnLoad:
    GoToIfUnset FLAG_REGIS_UNLOCKED, MtCoronet1FNorthRoom2_RemoveWarpIcebergRuinsWithRegice
    GoTo MtCoronet1FNorthRoom2_RemoveWarpIcebergRuinsWithoutRegice
    End

MtCoronet1FNorthRoom2_RemoveWarpIcebergRuinsWithRegice:
    SetWarpEventPos 3, 17, 16
    End

MtCoronet1FNorthRoom2_RemoveWarpIcebergRuinsWithoutRegice:
    SetWarpEventPos 2, 17, 16
    End

MtCoronet1FNorthRoom2_Unused:
    End

    .balign 4, 0
