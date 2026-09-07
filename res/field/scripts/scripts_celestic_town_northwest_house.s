#include "macros/scrcmd.inc"
#include "res/text/bank/celestic_town_northwest_house.h"


    ScriptEntry CelesticTownNorthwestHouse_Unused
    ScriptEntry CelesticTownNorthwestHouse_ExpertF
    ScriptEntry CelesticTownNorthwestHouse_ExpertM
    ScriptEntryEnd

CelesticTownNorthwestHouse_Unused:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message CelesticTownNorthwestHouse_Text_AWhileSinceCustomer
    Common_VendorGreeting
    CloseMessageWithoutErasing
    PokeMartCommon
    ReleaseAll
    End

CelesticTownNorthwestHouse_ExpertF:
    PokeMartCommonWithGreeting
    End

CelesticTownNorthwestHouse_ExpertM:
    PokeMartSpecialtiesWithGreeting MART_SPECIALTIES_ID_CELESTIC
    End

    .balign 4, 0
