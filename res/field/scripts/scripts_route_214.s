#include "macros/scrcmd.inc"
#include "res/text/bank/route_214.h"


    ScriptEntry Route214_ArrowSignVeilstoneCity
    ScriptEntry Route214_ArrowSignLakeValor
    ScriptEntry Route214_OnTransition
    ScriptEntry Route214_OnLoad
    ScriptEntryEnd

Route214_OnLoad:
    CheckHasCaughtSpecies SPECIES_UNOWN, VAR_MAP_LOCAL_0
    GoToIfEq VAR_MAP_LOCAL_0, TRUE, Route214_RemoveWarpsManiacCaveShortAndLong
    GoTo Route214_RemoveWarpsManiacCaveShortAndTunnel

Route214_RemoveWarpsManiacCaveShortAndLong:
    SetWarpEventPos 2, 710, 670
    SetWarpEventPos 3, 710, 670
    End

Route214_RemoveWarpsManiacCaveShortAndTunnel:
    SetWarpEventPos 2, 710, 670
    SetWarpEventPos 4, 710, 670
    End

Route214_RemoveWarpsManiacCaveLongAndTunnel:
    SetWarpEventPos 3, 710, 670
    SetWarpEventPos 4, 710, 670
    End

Route214_OnTransition:
    CheckHasCaughtSpecies SPECIES_UNOWN, VAR_MAP_LOCAL_0
    GoToIfEq VAR_MAP_LOCAL_0, TRUE, Route214_RemoveWarpsManiacCaveShortAndLong
    GoTo Route214_RemoveWarpsManiacCaveShortAndTunnel

Route214_ArrowSignVeilstoneCity:
    ShowArrowSign Route214_Text_SignVeilstoneCity
    End

Route214_ArrowSignLakeValor:
    ShowArrowSign Route214_Text_SignLakeValor
    End
