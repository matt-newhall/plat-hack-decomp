#include "macros/scrcmd.inc"
#include "res/text/bank/acuity_lakefront.h"
#include "res/field/events/events_acuity_lakefront.h"


    ScriptEntry AcuityLakefront_OnTransition
    ScriptEntry AcuityLakefront_OnLoad
    ScriptEntry AcuityLakefront_ArrowSignpostLakeAcuity
    ScriptEntryEnd

AcuityLakefront_OnLoad:
    GoToIfUnset FLAG_TEAM_GALACTIC_LEFT_LAKE_VERITY, AcuityLakefront_RemoveWarpsLakeAcuityNormal
    GoToIfSet FLAG_TEAM_GALACTIC_LEFT_LAKE_VERITY, AcuityLakefront_RemoveWarpsLakeAcuityLowWater
    End

AcuityLakefront_RemoveWarpsLakeAcuityNormal:
    SetWarpEventPos 2, 305, 229
    SetWarpEventPos 3, 306, 229
    End

AcuityLakefront_RemoveWarpsLakeAcuityLowWater:
    SetWarpEventPos 0, 305, 229
    SetWarpEventPos 1, 306, 229
    End

AcuityLakefront_OnTransition:
    CheckBadgeAcquired BADGE_ID_ICICLE, VAR_MAP_LOCAL_0
    CallIfEq VAR_MAP_LOCAL_0, TRUE, AcuityLakefront_SetVeilstoneGymMaylene
    GoToIfUnset FLAG_TEAM_GALACTIC_LEFT_LAKE_VERITY, AcuityLakefront_RemoveWarpsLakeAcuityNormal
    GoToIfSet FLAG_TEAM_GALACTIC_LEFT_LAKE_VERITY, AcuityLakefront_RemoveWarpsLakeAcuityLowWater
    End

AcuityLakefront_SetVeilstoneGymMaylene:
    SetFlag FLAG_HIDE_SNOWPOINT_CITY_POKECENTER_1F_MAYLENE
    ClearFlag FLAG_HIDE_VEILSTONE_CITY_GYM_MAYLENE
    Return

AcuityLakefront_ArrowSignpostLakeAcuity:
    ShowArrowSign AcuityLakefront_Text_SignLakeAcuityAhead
    End

    .balign 4, 0
