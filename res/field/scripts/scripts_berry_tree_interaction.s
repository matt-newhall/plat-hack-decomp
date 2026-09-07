#include "macros/scrcmd.inc"
#include "res/text/bank/berry_trees.h"
#include "constants/items.h"
#include "generated/berry_growth_stages.h"


    ScriptEntry BerryTreeMainScript
    ScriptEntry BerryTree_PlantBerryScript
    ScriptEntry BerryTree_WaterBerryScript
    ScriptEntry BerryTree_ApplyMulchScript
    ScriptEntryEnd

// Patches never grow or replant, so one is only ever bearing fruit or spent.
BerryTreeMainScript:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GetBerryItemID VAR_0x8000
    GetBerryYield VAR_0x8001
    GetBerryGrowthStage VAR_RESULT
    SetVar VAR_0x8008, VAR_RESULT
    GoToIfEq VAR_0x8008, BERRY_GROWTH_STAGE_NONE, BerryTree_ShowEmptySoilMessage
    GoTo BerryTree_FruitState
    End

BerryTree_FruitState:
    BufferNumber 1, VAR_0x8001
    GoToIfGt VAR_0x8001, 1, BerryTree_ShowMultipleBerriesMessage
    BufferItemNameWithArticle 0, VAR_0x8000
    Message BerryTrees_Text_ThereIsBerryWantToPickIt
    GoTo BerryTree_ShowHarvestMenu

BerryTree_ShowMultipleBerriesMessage:
    BufferItemNamePlural 0, VAR_0x8000
    Message BerryTrees_Text_ThereAreBerriesWantToPickThem
BerryTree_ShowHarvestMenu:
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_NO, BerryTree_ShowLeftBerryMessage
    GoToIfCannotFitItem VAR_0x8000, VAR_0x8001, VAR_RESULT, BerryTree_CheckBagSpace
    BufferNumber 1, VAR_0x8001
    GoToIfGt VAR_0x8001, 1, BerryTree_ShowMultipleBerriesPickedMessage
    BufferItemName 0, VAR_0x8000
    Message BerryTrees_Text_YouPickedTheBerry
    GoTo BerryTree_HarvestBerries

BerryTree_ShowMultipleBerriesPickedMessage:
    BufferItemNamePlural 0, VAR_0x8000
    Message BerryTrees_Text_YouPickedTheBerries
BerryTree_HarvestBerries:
    PlayFanfare SEQ_KINOMI
    WaitFanfare
    HarvestBerry
    BufferPlayerName 0
    GoToIfGt VAR_0x8001, 1, BerryTree_ShowMultipleBerriesStoredMessage
    BufferItemName 1, VAR_0x8000
    GoTo BerryTree_ShowBerriesStoredMessage

BerryTree_ShowMultipleBerriesStoredMessage:
    BufferItemNamePlural 1, VAR_0x8000
BerryTree_ShowBerriesStoredMessage:
    GetItemPocket VAR_0x8000, VAR_RESULT
    BufferPocketName 3, VAR_RESULT
    Message BerryTrees_Text_PlayerPutAwayBerriesInBagPocket
    WaitButton
    GoTo BerryTree_CloseAndEnd

BerryTree_CheckBagSpace:
    GoToIfGt VAR_0x8001, 1, BerryTree_ShowMultipleBerriesBagFullMessage
    BufferItemName 0, VAR_0x8000
    GoTo BerryTree_ShowBagFullMessage

BerryTree_ShowMultipleBerriesBagFullMessage:
    BufferItemNamePlural 0, VAR_0x8000
BerryTree_ShowBagFullMessage:
    Message BerryTrees_Text_BagIsFullBerriesCouldntBeTaken
    WaitButton
    GoTo BerryTree_CloseAndEnd

BerryTree_ShowLeftBerryMessage:
    BufferPlayerName 0
    GoToIfGt VAR_0x8001, 1, BerryTree_ShowLeftBerriesMessage
    BufferItemName 1, VAR_0x8000
    Message BerryTrees_Text_PlayerLeftBerryWhereItWas
    GoTo BerryTree_EndLeftBerryMessage

BerryTree_ShowLeftBerriesMessage:
    BufferItemNamePlural 1, VAR_0x8000
    Message BerryTrees_Text_PlayerLeftBerriesWhereTheyWere
BerryTree_EndLeftBerryMessage:
    WaitButton
    GoTo BerryTree_CloseAndEnd

BerryTree_ShowEmptySoilMessage:
    Message BerryTrees_Text_SoftEarthySoilAfterHarvest
    WaitButton
    GoTo BerryTree_CloseAndEnd

BerryTree_CloseAndEnd:
    CloseMessage
BerryTree_ReleaseAndEnd:
    ReleaseAll
    End

// Planting is disabled. The slot is kept so the script IDs after it do not shift.
BerryTree_PlantBerryScript:
    End

BerryTree_WaterBerryScript:
    LockAll
    SetBerryWateringState BERRY_WATERING_START
    Message BerryTrees_Text_ThereAllHappy
    WaitButton
    SetBerryWateringState BERRY_WATERING_END
    CloseMessage
    ReleaseAll
    End

BerryTree_ApplyMulchScript:
    LockAll
    SetVar VAR_RESULT, VAR_0x8000
    SetVar VAR_0x8005, VAR_0x8000
    RemoveItem VAR_0x8005, 1, VAR_0x8004
    SetBerryMulch VAR_0x8005
    BufferItemName 0, VAR_0x8005
    Message BerryTrees_Text_MulchWasScatteredOnSoilAfterHarvest
    WaitButton
    GoTo BerryTree_CloseAndEnd
