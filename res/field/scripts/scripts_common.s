#include "macros/scrcmd.inc"
#include "generated/distribution_events.h"
#include "generated/player_transitions.h"
#include "generated/time_of_day.h"
#include "constants/trainer_card_levels.h"
#include "generated/tutor_locations.h"
#include "res/text/bank/common_strings.h"
#include "res/text/bank/menu_entries.h"
#include "res/field/events/events_pokemon_mansion.h"
#include "res/field/events/events_pokemon_mansion_office.h"
#include "res/field/events/events_pokemon_mansion_maids_room.h"

    ScriptEntry CommonScript_HandleSignpostInput @ 0x7D0
    ScriptEntry CommonScript_CheckBagPocketForItem @ 0x7D1
    ScriptEntry CommonScript_PokecenterNurse @ 0x7D2
    ScriptEntry _03E8 @ 0x7D3
    ScriptEntry _043B @ 0x7D4
    ScriptEntry CommonScript_SaveAndStoreResult @ 0x7D5
    ScriptEntry CommonScript_SaveGame  @ 0x7D6
    ScriptEntry CommonScript_EmptyScript2 @ 0x7D7
    ScriptEntry _05EA @ 0x7D8
    ScriptEntry CommonScript_ObtainPoketchApp @ 0x7D9
    ScriptEntry CommonScript_EmptyScript1 @ 0x7DA
    ScriptEntry CommonScript_EmptyScript3 @ 0x7DB
    ScriptEntry CommonScript_SendToUndergroundPC @ 0x7DC
    ScriptEntry CommonScript_ObtainUndergroundTrap @ 0x7DD
    ScriptEntry CommonScript_ObtainUndergroundSphere @ 0x7DE
    ScriptEntry CommonScript_ObtainAccessoryWaitForConfirm @ 0x7DF
    ScriptEntry CommonScript_AddItemQuantityNoLineFeed @ 0x7E0
    ScriptEntry CommonScript_BagIsFull @ 0x7E1
    ScriptEntry _0BEE @ 0x7E2
    ScriptEntry CommonScript_VendorGreetingGeneric @ 0x7E3
    ScriptEntry CommonScript_PlayerHouseBlackOutRecover @ 0x7E4
    ScriptEntry CommonScript_PokecenterBlackOutRecover @ 0x7E5
    ScriptEntry CommonScript_EmptyScript4 @ 0x7E6
    ScriptEntry _0FA7 @ 0x7E7
    ScriptEntry CommonScript_EmptyScript5 @ 0x7E8
    ScriptEntry _1282 @ 0x7E9
    ScriptEntry _12A8 @ 0x7EA
    ScriptEntry CommonScript_Vent @ 0x7EB
    ScriptEntry _12CD @ 0x7EC
    ScriptEntry _12E0 @ 0x7ED
    ScriptEntry _12F3 @ 0x7EE
    ScriptEntry CommonScript_HatchEgg @ 0x7EF
    ScriptEntry _138C @ 0x7F0
    ScriptEntry _139D @ 0x7F1
    ScriptEntry _048B @ 0x7F2
    ScriptEntry _13AB @ 0x7F3
    ScriptEntry CommonScript_ObtainContestBackdropWaitForConfirm @ 0x7F4
    ScriptEntry CommonScript_EmptyScript6 @ 0x7F5
    ScriptEntry CommonScript_PrintPlateObtainedMessage @ 0x7F6
    ScriptEntry _1477 @ 0x7F7
    ScriptEntry CommonScript_SetCounterpartBGM @ 0x7F8
    ScriptEntry CommonScript_FadeToDefaultMusic @ 0x7F9
    ScriptEntry CommonScript_SetRivalBGM @ 0x7FA
    ScriptEntry CommonScript_FadeToDefaultMusic @ 0x7FB
    ScriptEntry CommonScript_AddItemQuantity @ 0x7FC
    ScriptEntry CommonScript_ObtainContestBackdrop @ 0x7FD
    ScriptEntry CommonScript_SendToUndergroundPCWithLinefeed @ 0x7FE
    ScriptEntry CommonScript_ObtainAccessory @ 0x7FF
    ScriptEntry CommonScript_SetFollowMeBGM @ 0x800
    ScriptEntry CommonScript_FadeToDefaultMusic @ 0x801
    ScriptEntry _15E7 @ 0x802
    ScriptEntry _1636 @ 0x803
    ScriptEntry _164A @ 0x804
    ScriptEntry _165E @ 0x805
    ScriptEntry CommonScript_Frontier_CheckAllFrontierGoldPrintsObtained @ 0x806
    ScriptEntry CommonScript_SetLookerBGM @ 0x807
    ScriptEntry CommonScript_FadeToDefaultMusic @ 0x808
    ScriptEntry CommonScript_GriseousOrbCouldNotBeRemoved @ 0x809
    ScriptEntry CommonScript_PortablePC_Simple @ 0x80A
    ScriptEntry CommonScript_Drifloon_Fly @ 0x80B
    ScriptEntry CommonScript_RocketMansionGrunt1 @ 0x80C
    ScriptEntry CommonScript_RocketMansionGrunt2 @ 0x80D
    ScriptEntry CommonScript_RocketMansionGrunt3 @ 0x80E
    ScriptEntry CommonScript_RocketMansionGrunt4 @ 0x80F
    ScriptEntry CommonScript_RocketMansionGrunt5 @ 0x810
    ScriptEntry CommonScript_RocketMansionGrunt6 @ 0x811
    ScriptEntry CommonScript_RocketMansionGrunt7 @ 0x812
    ScriptEntry CommonScript_RocketMansionAriana @ 0x813
    ScriptEntry CommonScript_RocketMansionBacklot @ 0x814
    ScriptEntry CommonScript_RocketMansionButler @ 0x815
    ScriptEntryEnd

CommonScript_EmptyScript1:
    End

CommonScript_EmptyScript2:
    End

CommonScript_PokecenterNurse:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GetTrainerCardLevel VAR_RESULT
    GoToIfGe VAR_RESULT, TRAINER_CARD_LEVEL_GOLD, CommonScript_PokecenterNurse_GoldCard
    SetVar VAR_0x8004, CommonStrings_Text_PokecenterGreeting_Day
    GetTimeOfDay VAR_RESULT
    Dummy1F9 VAR_RESULT
    SetVar VAR_0x8004, CommonStrings_Text_PokecenterGreeting_Morning
    GoToIfEq VAR_RESULT, TIMEOFDAY_MORNING, CommonScript_PokecenterNurse_Greeting
    SetVar VAR_0x8004, CommonStrings_Text_PokecenterGreeting_Night
    GoToIfEq VAR_RESULT, TIMEOFDAY_DAY, CommonScript_PokecenterNurse_Greeting
    SetVar VAR_0x8004, CommonStrings_Text_PokecenterGreeting_Day
CommonScript_PokecenterNurse_Greeting:
    MessageVar VAR_0x8004
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_YES, CommonScript_PokecenterNurse_AcceptHealPokemon
    GoToIfEq VAR_RESULT, MENU_NO, CommonScript_PokecenterNurse_DeclineHealPokemon
    End

CommonScript_PokecenterNurse_DeclineHealPokemon:
    Message CommonStrings_Text_PokecenterHopeToSeeYouAgain1
    WaitButton
    CloseMessage
    ReleaseAll
    ReturnCommonScript
    End

CommonScript_PokecenterNurse_AcceptHealPokemon:
    SetPlayerState PLAYER_TRANSITION_HEALING
    ChangePlayerState
    ApplyMovement LOCALID_PLAYER, CommonScript_PokecenterNurse_PlayerGivePokemonMovement
    WaitMovement
    GetTrainerCardLevel VAR_RESULT
    CallIfGe VAR_RESULT, TRAINER_CARD_LEVEL_GOLD, CommonScript_PokecenterNurse_TakePokemonMessage_GoldCard
    CallIfLt VAR_RESULT, TRAINER_CARD_LEVEL_GOLD, CommonScript_PokecenterNurse_TakePokemonMessage
    Call CommonScript_PokecenterNurse_HealPokemon
    GoToIfUnset FLAG_POKECENTER_IDENTIFIED_POKERUS, CommonScript_PokecenterNurse_CheckPokerus
    GoTo CommonScript_PokecenterNurse_FarewellAfterHeal

CommonScript_PokecenterNurse_TakePokemonMessage:
    Message CommonStrings_Text_PokecenterTakeYourPokemon
    Return

CommonScript_PokecenterNurse_TakePokemonMessage_GoldCard:
    Message CommonStrings_Text_PokecenterTakeYourPokemon_GoldCard
    Return

CommonScript_PokecenterNurse_HealPokemon:
    ApplyMovement VAR_0x8007, CommonScript_PokecenterNurse_TurnToMachineMovement
    WaitMovement
    CountPartyNonEggs VAR_0x8006
    PlayPokecenterHealingAnimation VAR_0x8006
    ApplyMovement VAR_0x8007, CommonScript_PokecenterNurse_TurnToPlayerMovement
    WaitMovement
    HealParty
    Return

CommonScript_PokecenterNurse_FarewellAfterHeal:
    GoToIfEq VAR_0x8004, TRUE, CommonScript_PokecenterNurse_FarewellAfterHeal_GoldCard
    Message CommonStrings_Text_PokecenterRestoredYourPokemon
    ApplyMovement LOCALID_PLAYER, CommonScript_PokecenterNurse_PlayerRetrievePokemonMovement
    WaitMovement
    SetPlayerState PLAYER_TRANSITION_WALKING
    ChangePlayerState
    ApplyMovement VAR_0x8007, CommonScript_PokecenterNurse_NurseBowMovement
    WaitMovement
    Message CommonStrings_Text_PokecenterHopeToSeeYouAgain1
    WaitButton
    CloseMessage
    ReleaseAll
    ReturnCommonScript
    End

CommonScript_PokecenterNurse_FarewellAfterHeal_GoldCard:
    Message CommonStrings_Text_PokecenterThankYouForWaiting
    ApplyMovement LOCALID_PLAYER, CommonScript_PokecenterNurse_PlayerRetrievePokemonMovement
    WaitMovement
    SetPlayerState PLAYER_TRANSITION_WALKING
    ChangePlayerState
    ApplyMovement VAR_0x8007, CommonScript_PokecenterNurse_NurseBowMovement
    WaitMovement
    Message CommonStrings_Text_PokecenterHopeToSeeYouAgain2
    WaitButton
    CloseMessage
    ReleaseAll
    ReturnCommonScript
    End

CommonScript_PokecenterNurse_CheckPokerus:
    CheckPartyPokerus VAR_0x8006
    GoToIfEq VAR_0x8006, TRUE, CommonScript_PokecenterNurse_IdentifiedPokerus
    GoTo CommonScript_PokecenterNurse_FarewellAfterHeal

CommonScript_PokecenterNurse_IdentifiedPokerus:
    SetFlag FLAG_POKECENTER_IDENTIFIED_POKERUS
    ApplyMovement LOCALID_PLAYER, CommonScript_PokecenterNurse_PlayerRetrievePokemonMovement
    WaitMovement
    SetPlayerState PLAYER_TRANSITION_WALKING
    ChangePlayerState
    Message CommonStrings_Text_PokecenterYourPokemonMayBeInfected
    WaitButton
    CloseMessage
    ReleaseAll
    ReturnCommonScript
    End

CommonScript_PokecenterNurse_GoldCard:
    GoToIfSet FLAG_POKECENTER_GOLD_TRAINER_CARD_SEEN, CommonScript_PokecenterNurse_GoldCard_PreviouslySeen
    SetFlag FLAG_POKECENTER_GOLD_TRAINER_CARD_SEEN
    Message CommonStrings_Text_PokecenterGreeting_Interrupted
    BufferPlayerName 0
    Message CommonStrings_Text_PokecenterThatTrainerCard
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_YES, CommonScript_PokecenterNurse_AcceptHealPokemon_GoldCard
    Message CommonStrings_Text_PokecenterHopeToSeeYouAgain2
    WaitButton
    CloseMessage
    ReleaseAll
    ReturnCommonScript
    End

CommonScript_PokecenterNurse_GoldCard_PreviouslySeen:
    BufferPlayerName 0
    Message CommonStrings_Text_PokecenterGreatToSeeYou
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_YES, CommonScript_PokecenterNurse_AcceptHealPokemon_GoldCard
    Message CommonStrings_Text_PokecenterHopeToSeeYouAgain2
    WaitButton
    CloseMessage
    ReleaseAll
    ReturnCommonScript
    End

CommonScript_PokecenterNurse_AcceptHealPokemon_GoldCard:
    SetVar VAR_0x8004, TRUE
    GoTo CommonScript_PokecenterNurse_AcceptHealPokemon

    .balign 4, 0
CommonScript_PokecenterNurse_NurseBowMovement:
    PokecenterNurseBow
    Delay4
    EndMovement

    .balign 4, 0
CommonScript_PokecenterNurse_PlayerGivePokemonMovement:
    PlayerGive
    EndMovement

    .balign 4, 0
CommonScript_PokecenterNurse_PlayerRetrievePokemonMovement:
    PlayerReceive
    EndMovement

CommonScript_HandleSignpostInput:
    SetVar VAR_0x8008, VAR_RESULT
    GoToIfEq VAR_0x8008, 0, CommonScript_ScrollOutSignpost
    GoToIfEq VAR_0x8008, 1, CommonScript_RemoveSignpostOpenStartMenu
    GetSignpostInput
    SetVar VAR_0x8008, VAR_RESULT
    GoToIfEq VAR_0x8008, 1, CommonScript_RemoveSignpostOpenStartMenu
    SetSignpostCommand SIGNPOST_CMD_SCROLL_OUT
    ReturnCommonScript
    End

CommonScript_ScrollOutSignpost:
    SetSignpostCommand SIGNPOST_CMD_SCROLL_OUT
    ReturnCommonScript
    End

CommonScript_RemoveSignpostOpenStartMenu:
    SetSignpostCommand SIGNPOST_CMD_REMOVE
    WaitForSignpostDone
    ShowStartMenu
    ReturnCommonScript
    End

CommonScript_CheckBagPocketForItem:
    Call CommonScript_GetBagPocketForItem
    ReturnCommonScript
    End

CommonScript_GetBagPocketForItem:
    GetItemPocket VAR_0x8004, VAR_RESULT
    SetVar VAR_0x8008, VAR_RESULT
    GoToIfEq VAR_0x8008, POCKET_KEY_ITEMS, CommonScript_PlayFanfare_SEQ_FANFA3
    GoToIfEq VAR_0x8008, POCKET_ITEMS, CommonScript_PlayFanfare_SEQ_FANFA4
    GoToIfEq VAR_0x8008, POCKET_BERRIES, CommonScript_PlayFanfare_SEQ_FANFA4
    GoToIfEq VAR_0x8008, POCKET_MEDICINE, CommonScript_PlayFanfare_SEQ_FANFA4
    GoToIfEq VAR_0x8008, POCKET_BALLS, CommonScript_PlayFanfare_SEQ_FANFA4
    GoToIfEq VAR_0x8008, POCKET_BATTLE_ITEMS, CommonScript_PlayFanfare_SEQ_FANFA4
    GoToIfEq VAR_0x8008, POCKET_MAIL, CommonScript_PlayFanfare_SEQ_FANFA2
    GoToIfEq VAR_0x8008, POCKET_TMHMS, CommonScript_PlayFanfare_SEQ_WAZA
    End

CommonScript_PlayFanfare_SEQ_FANFA4:
    PlayFanfare SEQ_FANFA4
    Return

CommonScript_PlayFanfare_SEQ_WAZA:
    PlayFanfare SEQ_WAZA
    Return

CommonScript_PlayFanfare_SEQ_FANFA3:
    PlayFanfare SEQ_FANFA3
    Return

CommonScript_PlayFanfare_SEQ_FANFA2:
    PlayFanfare SEQ_FANFA2
    Return

CommonScript_Unused:
    ReturnCommonScript
    End

_03E8:
    LockAll
    GetPartyCount VAR_0x8004
    SetVar VAR_0x8005, 0
_03F4:
    SurvivePoison VAR_RESULT, VAR_0x8005
    GoToIfEq VAR_RESULT, 0, _040F
    BufferPartyMonNickname 0, VAR_0x8005
    Message pl_msg_00000213_00066
_040F:
    AddVar VAR_0x8005, 1
    GoToIfNe VAR_0x8004, VAR_0x8005, _03F4
    CountAliveMonsExcept VAR_RESULT, 6
    GoToIfEq VAR_RESULT, 0, _0457
    CloseMessage
    ReleaseAll
    End

_043B:
    FadeScreenIn
    WaitFadeScreen
    WaitABPress
    FadeScreenOut
    WaitFadeScreen
    End

_0457:
    BufferPlayerName 0
    Message pl_msg_00000213_00011
    WaitABPress
    CloseMessage
    FadeOutBGM 0, 10
    FadeScreenOut
    WaitFadeScreen
    WaitForTransition
    BlackOutFromBattle2
    End

CommonScript_SaveAndStoreResult:
    ClearFlag FLAG_SAVE_EXTRA_BLOCK
    Call CommonScript_SaveGame_Dialog
    StoreSaveResult VAR_RESULT
    CloseMessage
    End

_048B:
    Message pl_msg_00000213_00020
    WaitABPress
    CloseMessage
    End

CommonScript_SaveGame:
    SetFlag FLAG_SAVE_EXTRA_BLOCK
    Call CommonScript_SaveGame_Dialog
    SetVar VAR_MAP_LOCAL_0, VAR_RESULT
    ReturnCommonScript
    End

CommonScript_SaveGame_Dialog:
    CheckSaveType VAR_RESULT
    GoToIfEq VAR_RESULT, SAVE_TYPE_OVERWRITE, CommonScript_SaveGame_ImpossibleToSave
    OpenSaveInfo
    Message pl_msg_00000213_00013
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_NO, CommonScript_SaveGame_Cancel
    CheckSaveType VAR_RESULT
    GoToIfEq VAR_RESULT, SAVE_TYPE_NO_DATA_EXISTS, CommonScript_SaveGame_SavingALotOfData
    GoToIfEq VAR_RESULT, SAVE_TYPE_FULL_SAVE, CommonScript_SaveGame_FullSave_OverwriteCheck
    GoToIfEq VAR_RESULT, SAVE_TYPE_QUICK_SAVE, CommonScript_SaveGame_QuickSave_OverwriteCheck
    End

CommonScript_SaveGame_ImpossibleToSave:
    Message pl_msg_00000213_00020
    WaitABPress
    SetVar VAR_RESULT, 0
    Return

CommonScript_SaveGame_FullSave_OverwriteCheck:
    Message pl_msg_00000213_00014
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_NO, CommonScript_SaveGame_Cancel
CommonScript_SaveGame_SavingALotOfData:
    Message pl_msg_00000213_00021
    GoTo CommonScript_SaveGame_StartSave

CommonScript_SaveGame_QuickSave_OverwriteCheck:
    Message pl_msg_00000213_00014
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_NO, CommonScript_SaveGame_Cancel
    GoToIfUnset FLAG_SAVE_EXTRA_BLOCK, CommonScript_QuickSave_Save
    GoToIfSet FLAG_SAVE_EXTRA_BLOCK, CommonScript_QuickSave_CheckMiscFlag
    End

CommonScript_SaveGame_StartSave:
    ScrCmd_258
    WaitTime 2, VAR_RESULT
    Call CommonScript_SaveGame_DoSave
    ScrCmd_259
    GoTo CommonScript_SaveGame_SaveComplete

CommonScript_SaveGame_DoSave:
    ShowSavingIcon
    CallIfSet FLAG_SAVE_EXTRA_BLOCK, CommonScript_SaveGame_SaveExtraBlock
    TrySaveGame VAR_RESULT
    HideSavingIcon
    Return

CommonScript_SaveGame_SaveComplete:
    GoToIfEq VAR_RESULT, 0, CommonScript_SaveGame_SaveError
    BufferPlayerName 0
    Message CommonStrings_Text_PlayerSavedTheGame
    PlaySE SEQ_SE_DP_SAVE
    WaitSE SEQ_SE_DP_SAVE
    WaitABPressTime 30
    CloseSaveInfo
    Return

CommonScript_SaveGame_Cancel:
    CloseSaveInfo
    SetVar VAR_RESULT, 0
    Return

CommonScript_SaveGame_SaveError:
    Message CommonStrings_Text_SaveError
    WaitABPress
    CloseSaveInfo
    Return

CommonScript_QuickSave_DoFullSave:
    Message pl_msg_00000213_00021
    GoTo CommonScript_SaveGame_StartSave
    End

CommonScript_SaveGame_SaveExtraBlock:
    SaveExtraData
    ClearFlag FLAG_SAVE_EXTRA_BLOCK
    Return

CommonScript_QuickSave_Save:
    Message CommonStrings_Text_SavingDontTurnOffThePower
    GoTo CommonScript_SaveGame_StartSave
    End

CommonScript_QuickSave_CheckMiscFlag:
    CheckIsMiscSaveInit VAR_RESULT
    GoToIfEq VAR_RESULT, 0, CommonScript_QuickSave_DoFullSave
    GoTo CommonScript_QuickSave_Save
    End

_05EA:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    CheckItem ITEM_HONEY, 1, VAR_RESULT
    GoToIfNe VAR_RESULT, 0, _0632
    GetHoneyTreeStatus VAR_RESULT
    GoToIfEq VAR_RESULT, TREE_STATUS_BARE, _065F
    GoToIfEq VAR_RESULT, TREE_STATUS_SLATHERED, _066A
    GoToIfEq VAR_RESULT, TREE_STATUS_ENCOUNTER, _06F4
    End

_0632:
    GetHoneyTreeStatus VAR_RESULT
    GoToIfEq VAR_RESULT, TREE_STATUS_BARE, _0675
    GoToIfEq VAR_RESULT, TREE_STATUS_SLATHERED, _067E
    GoToIfEq VAR_RESULT, TREE_STATUS_ENCOUNTER, _06F4
    End

_065F:
    Message pl_msg_00000213_00046
    WaitButton
    CloseMessage
    ReleaseAll
    End

_066A:
    Message pl_msg_00000213_00048
    WaitButton
    CloseMessage
    ReleaseAll
    End

_0675:
    Message pl_msg_00000213_00047
    GoTo _06BB

_067E:
    Message pl_msg_00000213_00049
    GoTo _06BB

CommonScript_Unused2:
    CheckItem ITEM_HONEY, 1, VAR_RESULT
    GoToIfNe VAR_RESULT, 0, _06BB
    CloseMessage
    ReleaseAll
    End

_06A2:
    CheckItem ITEM_HONEY, 1, VAR_RESULT
    GoToIfNe VAR_RESULT, 0, _06BB
    ReleaseAll
    End

_06BB:
    Message pl_msg_00000213_00050
    ShowYesNoMenu VAR_RESULT
    CloseMessage
    GoToIfEq VAR_RESULT, MENU_YES, _06D5
    ReleaseAll
    End

_06D5:
    RemoveItem ITEM_HONEY, 1, VAR_RESULT
    IncrementTrainerScore2 TRAINER_SCORE_EVENT_HONEY_USED
    SlatherHoneyTree
    WaitTime 10, VAR_RESULT
    Message pl_msg_00000213_00051
    WaitButton
    CloseMessage
    ReleaseAll
    End

_06F4:
    IncrementGameRecord RECORD_UNK_117
    StartHoneyTreeBattle
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, _0713
    ScrCmd_12A
    GoTo _06A2

_0713:
    BlackOutFromBattle
    ReleaseAll
    End

CommonScript_ObtainPoketchApp:
    Call CommonScript_InternalObtainPoketchApp
    ReturnCommonScript
    End

CommonScript_InternalObtainPoketchApp:
    BufferPlayerName 0
    BufferPoketchAppName 1, VAR_0x8004
    PlayFanfare SEQ_POCKETCH
    Message CommonStrings_Text_ObtainedPoketchApp
    WaitFanfare
    Message CommonStrings_Text_InstalledPoketchApp
    RegisterPoketchApp VAR_0x8004
    CallIfEq VAR_0x8004, POKETCH_APPID_DIGITALWATCH, CommonScript_ObtainedPoketchDigitalWatch
    CallIfEq VAR_0x8004, POKETCH_APPID_CALCULATOR, CommonScript_ObtainedPoketchCalculator
    CallIfEq VAR_0x8004, POKETCH_APPID_MEMOPAD, CommonScript_ObtainedPoketchMemopad
    CallIfEq VAR_0x8004, POKETCH_APPID_PEDOMETER, CommonScript_ObtainedPoketchPedometer
    CallIfEq VAR_0x8004, POKETCH_APPID_PARTYSTATUS, CommonScript_ObtainedPoketchPartyStatus
    CallIfEq VAR_0x8004, POKETCH_APPID_FRIENDSHIPCHECKER, CommonScript_ObtainedPoketchFriendshipChecker
    CallIfEq VAR_0x8004, POKETCH_APPID_DOWSINGMACHINE, CommonScript_ObtainedPoketchDowsingMachine
    CallIfEq VAR_0x8004, POKETCH_APPID_BERRYSEARCHER, CommonScript_ObtainedPoketchBerrySearcher
    CallIfEq VAR_0x8004, POKETCH_APPID_DAYCARECHECKER, CommonScript_ObtainedPoketchDayCareChecker
    CallIfEq VAR_0x8004, POKETCH_APPID_POKEMONHISTORY, CommonScript_ObtainedPoketchPokemonHistory
    CallIfEq VAR_0x8004, POKETCH_APPID_COUNTER, CommonScript_ObtainedPoketchCounter
    CallIfEq VAR_0x8004, POKETCH_APPID_ANALOGWATCH, CommonScript_ObtainedPoketchAnalogWatch
    CallIfEq VAR_0x8004, POKETCH_APPID_MARKINGMAP, CommonScript_ObtainedPoketchMarkingMap
    CallIfEq VAR_0x8004, POKETCH_APPID_LINKSEARCHER, CommonScript_ObtainedPoketchLinkSearcher
    CallIfEq VAR_0x8004, POKETCH_APPID_COINTOSS, CommonScript_ObtainedPoketchCoinToss
    CallIfEq VAR_0x8004, POKETCH_APPID_MOVETESTER, CommonScript_ObtainedPoketchMoveTester
    CallIfEq VAR_0x8004, POKETCH_APPID_CALENDAR, CommonScript_ObtainedPoketchCalendar
    CallIfEq VAR_0x8004, POKETCH_APPID_DOTART, CommonScript_ObtainedPoketchDotArt
    CallIfEq VAR_0x8004, POKETCH_APPID_ROULETTE, CommonScript_ObtainedPoketchRoulette
    CallIfEq VAR_0x8004, POKETCH_APPID_TRAINERCOUNTER, CommonScript_ObtainedPoketchRadarChainCounter
    CallIfEq VAR_0x8004, POKETCH_APPID_KITCHENTIMER, CommonScript_ObtainedPoketchKitchenTimer
    CallIfEq VAR_0x8004, POKETCH_APPID_COLORCHANGER, CommonScript_ObtainedPoketchColorChanger
    CallIfEq VAR_0x8004, POKETCH_APPID_MATCHUPCHECKER, CommonScript_ObtainedPoketchMatchupChecker
    CallIfEq VAR_0x8004, POKETCH_APPID_STOPWATCH, CommonScript_ObtainedPoketchStopwatch
    CallIfEq VAR_0x8004, POKETCH_APPID_ALARMCLOCK, CommonScript_ObtainedPoketchAlarmClock
    Return

CommonScript_ObtainedPoketchDigitalWatch:
    Message pl_msg_00000213_00083
    Return

CommonScript_ObtainedPoketchCalculator:
    Message pl_msg_00000213_00084
    Return

CommonScript_ObtainedPoketchMemopad:
    Message pl_msg_00000213_00085
    Return

CommonScript_ObtainedPoketchPedometer:
    Message pl_msg_00000213_00086
    Return

CommonScript_ObtainedPoketchPartyStatus:
    Message pl_msg_00000213_00087
    Return

CommonScript_ObtainedPoketchFriendshipChecker:
    Message pl_msg_00000213_00088
    Return

CommonScript_ObtainedPoketchDowsingMachine:
    Message pl_msg_00000213_00089
    Return

CommonScript_ObtainedPoketchBerrySearcher:
    Message pl_msg_00000213_00090
    Return

CommonScript_ObtainedPoketchDayCareChecker:
    Message pl_msg_00000213_00091
    Return

CommonScript_ObtainedPoketchPokemonHistory:
    Message pl_msg_00000213_00092
    Return

CommonScript_ObtainedPoketchCounter:
    Message CommonStrings_Text_ObtainedPoketchCounter
    Return

CommonScript_ObtainedPoketchAnalogWatch:
    Message pl_msg_00000213_00094
    Return

CommonScript_ObtainedPoketchMarkingMap:
    Message pl_msg_00000213_00095
    Return

CommonScript_ObtainedPoketchLinkSearcher:
    Message pl_msg_00000213_00096
    Return

CommonScript_ObtainedPoketchCoinToss:
    Message pl_msg_00000213_00097
    Return

CommonScript_ObtainedPoketchMoveTester:
    Message pl_msg_00000213_00098
    Return

CommonScript_ObtainedPoketchCalendar:
    Message pl_msg_00000213_00099
    Return

CommonScript_ObtainedPoketchDotArt:
    Message pl_msg_00000213_00100
    Return

CommonScript_ObtainedPoketchRoulette:
    Message pl_msg_00000213_00101
    Return

CommonScript_ObtainedPoketchRadarChainCounter:
    Message pl_msg_00000213_00102
    Return

CommonScript_ObtainedPoketchKitchenTimer:
    Message pl_msg_00000213_00103
    Return

CommonScript_ObtainedPoketchColorChanger:
    Message pl_msg_00000213_00104
    Return

CommonScript_ObtainedPoketchMatchupChecker:
    Message pl_msg_00000213_00105
    Return

CommonScript_ObtainedPoketchStopwatch:
    Message pl_msg_00000213_00106
    Return

CommonScript_ObtainedPoketchAlarmClock:
    Message pl_msg_00000213_00107
    Return

CommonScript_EmptyScript3:
    End

CommonScript_SendToUndergroundPC:
    Call CommonScript_ObtainUndergroundItem
    Message pl_msg_00000213_00109
    WaitButton
    ReturnCommonScript
    End

CommonScript_SendToUndergroundPCWithLinefeed:
    Call CommonScript_ObtainUndergroundItem
    Message pl_msg_00000213_00128
    ReturnCommonScript
    End

CommonScript_ObtainUndergroundItem:
    PlayFanfare SEQ_FANFA4
    SendGoodToPC VAR_0x8004, VAR_0x8005, VAR_RESULT
    BufferUndergroundGoodsNameWithArticle 0, VAR_0x8004
    Message pl_msg_00000213_00108
    BufferUndergroundGoodsName 0, VAR_0x8004
    WaitFanfare
    Return

CommonScript_ObtainUndergroundTrap:
    Call CommonScript_InternalObtainUndergroundTrap
    ReturnCommonScript
    End

CommonScript_InternalObtainUndergroundTrap:
    PlayFanfare SEQ_FANFA4
    GiveTrap VAR_0x8004, VAR_0x8005, VAR_RESULT
    BufferUndergroundTrapName 0, VAR_0x8004
    Message pl_msg_00000213_00080
    WaitFanfare
    Return

CommonScript_ObtainUndergroundSphere:
    Call CommonScript_InternalObtainUndergroundSphere
    ReturnCommonScript
    End

CommonScript_InternalObtainUndergroundSphere:
    PlayFanfare SEQ_FANFA4
    GiveSphere VAR_0x8004, VAR_0x8005, VAR_RESULT
    BufferUndergroundItemName 0, VAR_0x8004
    BufferNumber 1, VAR_0x8005
    Message pl_msg_00000213_00081
    WaitFanfare
    Return

CommonScript_ObtainAccessoryWaitForConfirm:
    Call CommonScript_InternalObtainAccessory
    Message CommonStrings_Text_PutAwayItemInTheFashionCaseNoLineFeed
    WaitButton
    ReturnCommonScript
    End

CommonScript_ObtainAccessory:
    Call CommonScript_InternalObtainAccessory
    Message CommonStrings_Text_PutAwayItemInTheFashionCase
    ReturnCommonScript
    End

CommonScript_InternalObtainAccessory:
    PlayFanfare SEQ_ACCE
    AddAccessory VAR_0x8004, VAR_0x8005
    BufferAccessoryName 0, VAR_0x8004
    Message CommonStrings_Text_ObtainedItem
    WaitFanfare
    BufferPlayerName 0
    BufferAccessoryName 1, VAR_0x8004
    Return

CommonScript_ObtainContestBackdropWaitForConfirm:
    Call CommonScript_InternalObtainContestBackdrop
    Message CommonStrings_Text_PutAwayItemInTheFashionCaseNoLineFeed
    WaitButton
    ReturnCommonScript
    End

CommonScript_ObtainContestBackdrop:
    Call CommonScript_InternalObtainContestBackdrop
    Message CommonStrings_Text_PutAwayItemInTheFashionCase
    ReturnCommonScript
    End

CommonScript_InternalObtainContestBackdrop:
    PlayFanfare SEQ_FANFA4
    AddContestBackdrop VAR_0x8004
    BufferContestBackdropName 0, VAR_0x8004
    Message CommonStrings_Text_ObtainedItem
    WaitFanfare
    BufferPlayerName 0
    BufferContestBackdropName 1, VAR_0x8004
    Return

CommonScript_AddItemQuantityNoLineFeed:
    Call CommonScript_InternalAddItemQuantityNoLineFeed
    ReturnCommonScript
    End

CommonScript_InternalAddItemQuantityNoLineFeed:
    Call CommonScript_GetBagPocketForItem
    AddItem VAR_0x8004, VAR_0x8005, VAR_RESULT
    GetItemPocket VAR_0x8004, VAR_RESULT
    CallIfEq VAR_RESULT, POCKET_KEY_ITEMS, CommonScript_PrintMessageObtainedKeyItem
    CallIfNe VAR_RESULT, POCKET_KEY_ITEMS, CommonScript_PrepareMessageObtainedItem
    Message CommonStrings_Text_PutItemInThePocketNoLineFeed
    WaitButton
    Return

CommonScript_AddItemQuantity:
    Call CommonScript_InternalAddItemQuantity
    ReturnCommonScript
    End

CommonScript_InternalAddItemQuantity:
    Call CommonScript_GetBagPocketForItem
    AddItem VAR_0x8004, VAR_0x8005, VAR_RESULT
    GetItemPocket VAR_0x8004, VAR_RESULT
    CallIfEq VAR_RESULT, POCKET_KEY_ITEMS, CommonScript_PrintMessageObtainedKeyItem
    CallIfNe VAR_RESULT, POCKET_KEY_ITEMS, CommonScript_PrepareMessageObtainedItem
    Message CommonStrings_Text_PutItemInThePocket
    Return

CommonScript_PrintMessageObtainedKeyItem:
    BufferPlayerName 0
    BufferItemName 1, VAR_0x8004
    Message CommonStrings_Text_ObtainedKeyItem
    GoTo CommonScript_AfterObtainedItem

CommonScript_PrepareMessageObtainedItem:
    GoToIfGt VAR_0x8005, 1, CommonScript_PrintMessageObtainedItemsPlural
    BufferItemName 0, VAR_0x8004
    GoTo CommonScript_PrintMessageObtainedItem

CommonScript_PrintMessageObtainedItemsPlural:
    BufferItemNamePlural 0, VAR_0x8004
CommonScript_PrintMessageObtainedItem:
    Message CommonStrings_Text_ObtainedItem
    GoTo CommonScript_AfterObtainedItem

CommonScript_AfterObtainedItem:
    WaitFanfare
    CheckItemIsPlate VAR_0x8004, VAR_RESULT
    CallIfEq VAR_RESULT, TRUE, CommonScript_DeterminePlateMessage
    BufferPlayerName 0
    GoToIfGt VAR_0x8005, 1, CommonScript_BufferPocketNameItemsPlural
    BufferItemName 1, VAR_0x8004
    GoTo CommonScript_BufferPocketName

CommonScript_BufferPocketNameItemsPlural:
    BufferItemNamePlural 1, VAR_0x8004
CommonScript_BufferPocketName:
    GetItemPocket VAR_0x8004, VAR_RESULT
    SetVar VAR_0x8008, VAR_RESULT
    GoToIfEq VAR_0x8008, POCKET_KEY_ITEMS, CommonScript_BufferPocketNameKeyItems
    GoToIfEq VAR_0x8008, POCKET_ITEMS, CommonScript_BufferPocketNameItems
    GoToIfEq VAR_0x8008, POCKET_BERRIES, CommonScript_BufferPocketNameBerries
    GoToIfEq VAR_0x8008, POCKET_MEDICINE, CommonScript_BufferPocketNameMedicine
    GoToIfEq VAR_0x8008, POCKET_BALLS, CommonScript_BufferPocketNameBalls
    GoToIfEq VAR_0x8008, POCKET_BATTLE_ITEMS, CommonScript_BufferPocketNameBattleItems
    GoToIfEq VAR_0x8008, POCKET_MAIL, CommonScript_BufferPocketNameMail
    GoToIfEq VAR_0x8008, POCKET_TMHMS, CommonScript_BufferPocketNameTMHMs
    End

CommonScript_BufferPocketNameItems:
    GetItemPocket VAR_0x8004, VAR_RESULT
    BufferPocketName 2, VAR_RESULT
    GoTo CommonScript_BufferPocketNameReturn

CommonScript_BufferPocketNameKeyItems:
    GetItemPocket VAR_0x8004, VAR_RESULT
    BufferPocketName 2, VAR_RESULT
    GoTo CommonScript_BufferPocketNameReturn

CommonScript_BufferPocketNameBattleItems:
    GetItemPocket VAR_0x8004, VAR_RESULT
    BufferPocketName 2, VAR_RESULT
    GoTo CommonScript_BufferPocketNameReturn

CommonScript_BufferPocketNameMail:
    GetItemPocket VAR_0x8004, VAR_RESULT
    BufferPocketName 2, VAR_RESULT
    GoTo CommonScript_BufferPocketNameReturn

CommonScript_BufferPocketNameMedicine:
    GetItemPocket VAR_0x8004, VAR_RESULT
    BufferPocketName 2, VAR_RESULT
    GoTo CommonScript_BufferPocketNameReturn

CommonScript_BufferPocketNameBerries:
    GetItemPocket VAR_0x8004, VAR_RESULT
    BufferPocketName 2, VAR_RESULT
    GoTo CommonScript_BufferPocketNameReturn

CommonScript_BufferPocketNameBalls:
    GetItemPocket VAR_0x8004, VAR_RESULT
    BufferPocketName 2, VAR_RESULT
    GoTo CommonScript_BufferPocketNameReturn

CommonScript_BufferPocketNameTMHMs:
    GetItemPocket VAR_0x8004, VAR_RESULT
    BufferPocketName 2, VAR_RESULT
    GoTo CommonScript_BufferPocketNameReturn

CommonScript_BufferPocketNameReturn:
    Return

CommonScript_BagIsFull:
    Call CommonScript_InternalBagIsFull
    ReturnCommonScript
    End

CommonScript_InternalBagIsFull:
    Message CommonStrings_Text_BagIsFull
    WaitButton
    Return

_0BEE:
    LockAll
    PlaySE SEQ_SE_DP_PC_ON
    Call _0C06
    BufferPlayerName 0
    Message pl_msg_00000213_00032
    GoTo _0C1C

_0C06:
    GoToIfSet FLAG_UNK_0x0BFF, _PC_Boot_Skip
    LoadPCAnimation ANIMATION_TAG_PC
    PlayPCBootUpAnimation ANIMATION_TAG_PC
    WaitForAnimation ANIMATION_TAG_PC
_PC_Boot_Skip:
    Return

_0C11:
    GoToIfSet FLAG_UNK_0x0BFF, _PC_Shutdown_Skip
    PlayPCShutDownAnimation ANIMATION_TAG_PC
    WaitForAnimation ANIMATION_TAG_PC
    UnloadAnimation ANIMATION_TAG_PC
_PC_Shutdown_Skip:
    Return

_0C1C:
    BufferPlayerName 0
    Message pl_msg_00000213_00033
    InitGlobalTextMenu 1, 1, 0, VAR_0x8006
    CallIfUnset FLAG_MET_BEBE, _0C7B
    CallIfSet FLAG_MET_BEBE, _0C81
    AddMenuEntryImm 60, 1
    GetNationalDexEnabled VAR_RESULT
    CallIfEq VAR_RESULT, 0, _0C87
    CallIfEq VAR_RESULT, 1, _0C8D
    GoToIfSet FLAG_GAME_COMPLETED, _0C93
    GoToIfUnset FLAG_GAME_COMPLETED, _0CDD
    End

_0C7B:
    AddMenuEntryImm 58, 0
    Return

_0C81:
    AddMenuEntryImm 59, 0
    Return

_0C87:
    AddMenuEntryImm 63, 2
    Return

_0C8D:
    AddMenuEntryImm 62, 2
    Return

_0C93:
    AddMenuEntryImm 61, 3
    AddMenuEntryImm 24, 4
    AddMenuEntryImm 25, 5
    AddMenuEntryImm 65, 6
    AddMenuEntryImm 64, 7
    ShowMenu
    SetVar VAR_0x8008, VAR_0x8006
    GoToIfEq VAR_0x8008, 0, _0D16
    GoToIfEq VAR_0x8008, 1, _0E45
    GoToIfEq VAR_0x8008, 2, _0F62
    GoToIfEq VAR_0x8008, 3, _0F2C
    GoToIfEq VAR_0x8008, 4, PreDamageHandler
    GoToIfEq VAR_0x8008, 5, VolatileStatus_Submenu
    GoToIfEq VAR_0x8008, 6, _PCPokevialHandler
    GoTo _0F70

_0CDD:
    AddMenuEntryImm 24, 3
    AddMenuEntryImm 25, 4
    AddMenuEntryImm 65, 5
    AddMenuEntryImm 64, 6
    ShowMenu
    SetVar VAR_0x8008, VAR_0x8006
    GoToIfEq VAR_0x8008, 0, _0D16
    GoToIfEq VAR_0x8008, 1, _0E45
    GoToIfEq VAR_0x8008, 2, _0F62
    GoToIfEq VAR_0x8008, 3, PreDamageHandler
    GoToIfEq VAR_0x8008, 4, VolatileStatus_Submenu
    GoToIfEq VAR_0x8008, 5, _PCPokevialHandler
    GoTo _0F70

_0D16:
    PlaySE SEQ_SE_DP_PC_LOGIN
    BufferPlayerName 0
    Message pl_msg_00000213_00034
    Call _0D2C
    GoTo _0D73

_0D2C:
    InitGlobalTextListMenu 1, 1, 0, VAR_RESULT
    AddListMenuEntry MenuEntries_Text_PokemonStorageDepositPokemon, 0, MenuEntries_Text_PokemonStorageDepositPokemonDescription
    AddListMenuEntry MenuEntries_Text_PokemonStorageWithdrawPokemon, 1, MenuEntries_Text_PokemonStorageWithdrawPokemonDescription
    AddListMenuEntry MenuEntries_Text_PokemonStorageMovePokemon, 2, MenuEntries_Text_PokemonStorageMovePokemonDescription
    AddListMenuEntry MenuEntries_Text_PokemonStorageMoveItems, 3, MenuEntries_Text_PokemonStorageMoveItemsDescription
    CallIfSet FLAG_CONTEST_HALL_VISITED, _0D69
    AddListMenuEntry MenuEntries_Text_PokemonStorageSeeYa, 5, MenuEntries_Text_PokemonStorageSeeYaDescription
    Return

_0D69:
    AddListMenuEntry MenuEntries_Text_PokemonStorageComparePokemon, 4, MenuEntries_Text_PokemonStorageComparePokemonDescription
    Return

_0D73:
    ShowListMenu
    SetVar VAR_0x8008, VAR_RESULT
    GoToIfEq VAR_0x8008, 0, _0DC2
    GoToIfEq VAR_0x8008, 1, _0DD5
    GoToIfEq VAR_0x8008, 2, _0DE8
    GoToIfEq VAR_0x8008, 3, _0DFB
    GoToIfEq VAR_0x8008, 4, _0E0E
    GoTo _0C1C

_0DC2:
    CloseMessage
    Call _0F94
    OpenPokemonStorage 0
    ReturnToField
    GoTo _0E21

_0DD5:
    CloseMessage
    Call _0F94
    OpenPokemonStorage 1
    ReturnToField
    GoTo _0E21

_0DE8:
    CloseMessage
    Call _0F94
    OpenPokemonStorage 2
    ReturnToField
    GoTo _0E21

_0DFB:
    CloseMessage
    Call _0F94
    OpenPokemonStorage 3
    ReturnToField
    GoTo _0E21

_0E0E:
    CloseMessage
    Call _0F94
    OpenPokemonStorage 4
    ReturnToField
    GoTo _0E21

_0E21:
    ScrCmd_30B
    BufferPlayerName 0
    MessageInstant 33
    Call _0D2C
    Call _0C06
    FadeScreenIn
    GoTo _0D73

_0E45:
    PlaySE SEQ_SE_DP_PC_LOGIN
    BufferPlayerName 0
    Message pl_msg_00000213_00035
    GoTo _0E55

_0E55:
    Call _0E61
    GoTo _0E83

_0E61:
    InitGlobalTextListMenu 1, 1, 0, VAR_RESULT
    AddListMenuEntry 71, 0, 80
    AddListMenuEntry 72, 1, 81
    AddListMenuEntry 73, 3, 82
    Return

_0E83:
    ShowListMenu
    SetVar VAR_0x8008, VAR_RESULT
    GoToIfEq VAR_0x8008, 0, _0EAB
    GoToIfEq VAR_0x8008, 1, _0EE0
    GoTo _0C1C

_0EAB:
    CloseMessage
    ScrCmd_1B4 VAR_RESULT
    GoToIfEq VAR_RESULT, 0, _0EC6
    ScrCmd_1B3
    GoTo _0ECF

_0EC6:
    Message pl_msg_00000213_00052
    GoTo _0E55

_0ECF:
    BufferPlayerName 0
    OpenMessage
    Call _0E61
    GoTo _0E83

_0EE0:
    ScrCmd_2AB VAR_RESULT
    GoToIfEq VAR_RESULT, 0, _0F01
    CloseMessage
    Call _0F94
    OpenSealCapsuleEditor
    GoTo _0F0A

_0F01:
    Message pl_msg_00000213_00118
    GoTo _0E55

_0F0A:
    BufferPlayerName 0
    MessageInstant 33
    Call _0E61
    Call _0C06
    FadeScreenIn
    GoTo _0E83

_0F2C:
    PlaySE SEQ_SE_DP_PC_LOGIN
    CloseMessage
    ScrCmd_336 VAR_RESULT
    GoToIfEq VAR_RESULT, 1, _0F59
    Call _0F94
    ScrCmd_0B1
    ReturnToField
    Call _0F80
    GoTo _0C1C

_0F59:
    Message pl_msg_00000213_00131
    GoTo _0C1C

PreDamageHandler:
    CloseMessage
    Call _0F94
    OpenPartyMenuForSetHP
    ReturnToField
    Call _0F80
    GoTo _0C1C

_PokevialCore:
    CloseMessage
    PlayFanfare SEQ_ASA
    WaitFanfare
    HealParty
    Message pl_msg_00000213_00132
    CloseMessage
    Return

_PCPokevialHandler:
    Call _PokevialCore
    GoTo _0C1C

_0F62:
    PlaySE SEQ_SE_DP_PC_LOGIN
    CallCommonScript 0x26DF
    GoTo _0C1C

_0F70:
    CloseMessage
    PlaySE SEQ_SE_DP_PC_LOGOFF
    Call _0C11
    ClearFlag FLAG_UNK_0x0BFF
    ReleaseAll
    End

_0F80:
    Call _0C06
    FadeScreenIn
    WaitFadeScreen
    Return

_0F94:
    FadeScreenOut
    WaitFadeScreen
    GoToIfSet FLAG_UNK_0x0BFF, _PC_Unload_Skip
    UnloadAnimation ANIMATION_TAG_PC
_PC_Unload_Skip:
    Return

VolatileStatus_Submenu:
    Message CommonStrings_Text_StatusSubmenu_Header
    InitGlobalTextListMenu 1, 1, 0, VAR_RESULT
    AddListMenuEntry 26, 0
    AddListMenuEntry 27, 1
    AddListMenuEntry 28, 2
    AddListMenuEntry 29, 3
    AddListMenuEntry 30, 4
    AddListMenuEntry 31, 5
    AddListMenuEntry 5, 6
    ShowListMenu
    SetVar VAR_0x8008, VAR_RESULT
    GoToIfEq VAR_0x8008, 0xFFFE, _0C1C
    GoToIfEq VAR_0x8008, 6, _0C1C
    CloseMessage
    Call _0F94
    OpenPartyMenuForStatusInflict VAR_0x8008
    ReturnToField
    Call _0F80
    GoTo _0C1C

CommonScript_EmptyScript4:
    End

_0FA7:
    FadeScreenOut
    WaitFadeScreen
    OpenSealCapsuleEditor
    FadeScreenIn
    WaitFadeScreen
    End

CommonScript_VendorGreetingGeneric:
    Message CommonStrings_Text_VendorGreetingGeneric
    ReturnCommonScript
    End

CommonScript_PlayerHouseBlackOutRecover:
    LockAll
    ApplyMovement LOCALID_PLAYER, CommonScript_PlayerHouseBlackOutRecover_PlayerTurnToMomMovement
    ApplyMovement 0, CommonScript_PlayerHouseBlackOutRecover_MomTurnToPlayerMovement
    WaitMovement
    FadeScreenIn
    WaitFadeScreen
    BufferPlayerName 0
    Message CommonStrings_Text_YouHadQuiteTheExperienceOutThere
    FadeScreenOut
    WaitFadeScreen
    CloseMessage
    PlayFanfare SEQ_ASA
    WaitFanfare
    HealParty
    FadeScreenIn
    WaitFadeScreen
    CallIfSet FLAG_HAS_POKEDEX, CommonScript_PlayerHouseBlackOutRecover_BeforePokedexMessage
    CallIfUnset FLAG_HAS_POKEDEX, CommonScript_PlayerHouseBlackOutRecover_AfterPokedexMessage
    WaitButton
    CloseMessage
    ReleaseAll
    End

CommonScript_PlayerHouseBlackOutRecover_BeforePokedexMessage:
    Message CommonStrings_Text_YourPokemonAreLookingGreat_BeforePokedex
    Return

CommonScript_PlayerHouseBlackOutRecover_AfterPokedexMessage:
    Message CommonStrings_Text_YourPokemonAreLookingGreat_AfterPokedex
    Return

CommonScript_PokecenterBlackOutRecover:
    LockAll
    FadeScreenIn
    WaitFadeScreen
    SetPlayerState PLAYER_TRANSITION_HEALING
    ChangePlayerState
    ApplyMovement LOCALID_PLAYER, CommonScript_PokecenterNurse_PlayerGivePokemonMovement
    WaitMovement
    Message CommonStrings_Text_PokecenterFirstLetsRestoreYourPokemon
    Call CommonScript_PokecenterNurse_FindNurseObject
    Call CommonScript_PokecenterNurse_HealPokemon
    GoToIfBadgeAcquired BADGE_ID_COAL, CommonScript_PokecenterBlackOutRecover_HasCoalBadge
    Message CommonStrings_Text_PokecenterHealedToPerfectHealth
    ApplyMovement LOCALID_PLAYER, CommonScript_PokecenterNurse_PlayerRetrievePokemonMovement
    WaitMovement
    SetPlayerState PLAYER_TRANSITION_WALKING
    ChangePlayerState
    ApplyMovement VAR_0x8007, CommonScript_PokecenterNurse_NurseBowMovement
    WaitMovement
    Message CommonStrings_Text_PokecenterGoodLuckTrainer
    WaitButton
    CloseMessage
    ReleaseAll
    End

CommonScript_PokecenterBlackOutRecover_HasCoalBadge:
    ApplyMovement LOCALID_PLAYER, CommonScript_PokecenterNurse_PlayerRetrievePokemonMovement
    WaitMovement
    SetPlayerState PLAYER_TRANSITION_WALKING
    ChangePlayerState
    ApplyMovement VAR_0x8007, CommonScript_PokecenterNurse_NurseBowMovement
    WaitMovement
    Message CommonStrings_Text_PokecenterAllHappyAndHealthy
    WaitButton
    CloseMessage
    ReleaseAll
    End

CommonScript_PokecenterNurse_FindNurseObject:
    GetCurrentMapID VAR_0x8004
    GoToIfEq VAR_0x8004, MAP_HEADER_JUBILIFE_CITY_POKECENTER_1F, CommonScript_PokecenterNurse_FindNurseObject_Jubilife
    GoToIfEq VAR_0x8004, MAP_HEADER_CANALAVE_CITY_POKECENTER_1F, CommonScript_PokecenterNurse_FindNurseObject_Canalave
    GoToIfEq VAR_0x8004, MAP_HEADER_OREBURGH_CITY_POKECENTER_1F, CommonScript_PokecenterNurse_FindNurseObject_Oreburgh
    GoToIfEq VAR_0x8004, MAP_HEADER_ETERNA_CITY_POKECENTER_1F, CommonScript_PokecenterNurse_FindNurseObject_Eterna
    GoToIfEq VAR_0x8004, MAP_HEADER_HEARTHOME_CITY_POKECENTER_1F, CommonScript_PokecenterNurse_FindNurseObject_Hearthome
    GoToIfEq VAR_0x8004, MAP_HEADER_PASTORIA_CITY_POKECENTER_1F, CommonScript_PokecenterNurse_FindNurseObject_Pastoria
    GoToIfEq VAR_0x8004, MAP_HEADER_VEILSTONE_CITY_POKECENTER_1F, CommonScript_PokecenterNurse_FindNurseObject_Veilstone
    GoToIfEq VAR_0x8004, MAP_HEADER_SUNYSHORE_CITY_POKECENTER_1F, CommonScript_PokecenterNurse_FindNurseObject_Sunyshore
    GoToIfEq VAR_0x8004, MAP_HEADER_SNOWPOINT_CITY_POKECENTER_1F, CommonScript_PokecenterNurse_FindNurseObject_Snowpoint
    GoToIfEq VAR_0x8004, MAP_HEADER_POKEMON_LEAGUE_SOUTH_POKECENTER_1F, CommonScript_PokecenterNurse_FindNurseObject_PokemonLeagueSouth
    GoToIfEq VAR_0x8004, MAP_HEADER_FIGHT_AREA_POKECENTER_1F, CommonScript_PokecenterNurse_FindNurseObject_FightArea
    GoToIfEq VAR_0x8004, MAP_HEADER_SANDGEM_TOWN_POKECENTER_1F, CommonScript_PokecenterNurse_FindNurseObject_Sandgem
    GoToIfEq VAR_0x8004, MAP_HEADER_FLOAROMA_TOWN_POKECENTER_1F, CommonScript_PokecenterNurse_FindNurseObject_Floaroma
    GoToIfEq VAR_0x8004, MAP_HEADER_SOLACEON_TOWN_POKECENTER_1F, CommonScript_PokecenterNurse_FindNurseObject_Solaceon
    GoToIfEq VAR_0x8004, MAP_HEADER_CELESTIC_TOWN_POKECENTER_1F, CommonScript_PokecenterNurse_FindNurseObject_Celestic
    GoToIfEq VAR_0x8004, MAP_HEADER_SURVIVAL_AREA_POKECENTER_1F, CommonScript_PokecenterNurse_FindNurseObject_SurvivalArea
    GoToIfEq VAR_0x8004, MAP_HEADER_RESORT_AREA_POKECENTER_1F, CommonScript_PokecenterNurse_FindNurseObject_ResortArea
    GoToIfEq VAR_0x8004, MAP_HEADER_POKEMON_LEAGUE_NORTH_POKECENTER_1F, CommonScript_PokecenterNurse_FindNurseObject_PokemonLeagueNorth
    SetVar VAR_0x8007, 0
    Return

CommonScript_PokecenterNurse_FindNurseObject_Jubilife:
    SetVar VAR_0x8007, 3
    Return

CommonScript_PokecenterNurse_FindNurseObject_Canalave:
    SetVar VAR_0x8007, 1
    Return

CommonScript_PokecenterNurse_FindNurseObject_Oreburgh:
    SetVar VAR_0x8007, 3
    Return

CommonScript_PokecenterNurse_FindNurseObject_Eterna:
    SetVar VAR_0x8007, 3
    Return

CommonScript_PokecenterNurse_FindNurseObject_Hearthome:
    SetVar VAR_0x8007, 0
    Return

CommonScript_PokecenterNurse_FindNurseObject_Pastoria:
    SetVar VAR_0x8007, 0
    Return

CommonScript_PokecenterNurse_FindNurseObject_Veilstone:
    SetVar VAR_0x8007, 0
    Return

CommonScript_PokecenterNurse_FindNurseObject_Sunyshore:
    SetVar VAR_0x8007, 0
    Return

CommonScript_PokecenterNurse_FindNurseObject_Snowpoint:
    SetVar VAR_0x8007, 0
    Return

CommonScript_PokecenterNurse_FindNurseObject_PokemonLeagueSouth:
    SetVar VAR_0x8007, 0
    Return

CommonScript_PokecenterNurse_FindNurseObject_FightArea:
    SetVar VAR_0x8007, 0
    Return

CommonScript_PokecenterNurse_FindNurseObject_Sandgem:
    SetVar VAR_0x8007, 3
    Return

CommonScript_PokecenterNurse_FindNurseObject_Floaroma:
    SetVar VAR_0x8007, 2
    Return

CommonScript_PokecenterNurse_FindNurseObject_Solaceon:
    SetVar VAR_0x8007, 0
    Return

CommonScript_PokecenterNurse_FindNurseObject_Celestic:
    SetVar VAR_0x8007, 0
    Return

CommonScript_PokecenterNurse_FindNurseObject_SurvivalArea:
    SetVar VAR_0x8007, 0
    Return

CommonScript_PokecenterNurse_FindNurseObject_ResortArea:
    SetVar VAR_0x8007, 0
    Return

CommonScript_PokecenterNurse_FindNurseObject_PokemonLeagueNorth:
    SetVar VAR_0x8007, 3
    Return

    .balign 4, 0
CommonScript_PlayerHouseBlackOutRecover_PlayerTurnToMomMovement:
    FaceWest
    EndMovement

    .balign 4, 0
CommonScript_PlayerHouseBlackOutRecover_MomTurnToPlayerMovement:
    FaceEast
    EndMovement

    .balign 4, 0
CommonScript_PokecenterNurse_TurnToMachineMovement:
    FaceWest
    EndMovement

CommonScript_UnusedMovement:
    FaceNorth
    EndMovement

CommonScript_UnusedMovement2:
    FaceEast
    EndMovement

    .balign 4, 0
CommonScript_PokecenterNurse_TurnToPlayerMovement:
    FaceSouth
    EndMovement

CommonScript_EmptyScript5:
    End

_1282:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FadeScreenOut
    WaitFadeScreen
    ScrCmd_205
    ReturnToField
    FadeScreenIn
    WaitFadeScreen
    ReleaseAll
    End

_12A8:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    MessageFromTrainerType
    WaitButton
    CloseMessage
    ReleaseAll
    End

CommonScript_Vent:
    NPCMessage CommonStrings_Text_ItsAnAirVentThatExchangesTheUndergroundTunnelsAir
    End

_12CD:
    NPCMessage pl_msg_00000213_00070
    End

_12E0:
    NPCMessage pl_msg_00000213_00071
    End

_12F3:
    CheckItem ITEM_BICYCLE, 1, VAR_RESULT
    GoToIfEq VAR_RESULT, 0, CommonScript_End
    LockAll
    PlaySE SEQ_SE_CONFIRM
    CheckPlayerOnBike VAR_RESULT
    GoToIfEq VAR_RESULT, TRUE, _133C
    Message pl_msg_00000213_00073
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_NO, _1359
    SetPlayerBike TRUE
    CloseMessage
    ReleaseAll
    End

_133C:
    Message pl_msg_00000213_00074
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_NO, _1359
    SetPlayerBike FALSE
    CloseMessage
    ReleaseAll
    End

_1359:
    CloseMessage
    ReleaseAll
    End

CommonScript_End:
    End

CommonScript_HatchEgg:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    Message CommonStrings_Text_Oh
    WaitABPress
    FadeScreenOut
    WaitFadeScreen
    CloseMessage
    HatchEgg
    FadeScreenIn
    WaitFadeScreen
    ReleaseAll
    End

_138C:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    Message pl_msg_00000213_00079
    WaitABPress
    CloseMessage
    ReleaseAll
    End

_139D:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    ScrCmd_0A5
    ReleaseAll
    End

_13AB:
    NPCMessage pl_msg_00000213_00082
    End

CommonScript_PrintPlateObtainedMessage:
    Call CommonScript_DeterminePlateMessage
    ReturnCommonScript
    End

CommonScript_DeterminePlateMessage:
    AddVar VAR_NUM_PLATES_OBTAINED, 1
    CallIfGe VAR_NUM_PLATES_OBTAINED, 9, CommonScript_ResetPlateCount
    CallIfEq VAR_NUM_PLATES_OBTAINED, 1, CommonScript_Print1PlateObtainedMessage
    CallIfEq VAR_NUM_PLATES_OBTAINED, 2, CommonScript_Print2PlatesObtainedMessage
    CallIfEq VAR_NUM_PLATES_OBTAINED, 3, CommonScript_Print3PlatesObtainedMessage
    CallIfEq VAR_NUM_PLATES_OBTAINED, 4, CommonScript_Print4PlatesObtainedMessage
    CallIfEq VAR_NUM_PLATES_OBTAINED, 5, CommonScript_Print5PlatesObtainedMessage
    CallIfEq VAR_NUM_PLATES_OBTAINED, 6, CommonScript_Print6PlatesObtainedMessage
    CallIfEq VAR_NUM_PLATES_OBTAINED, 7, CommonScript_Print7PlatesObtainedMessage
    CallIfEq VAR_NUM_PLATES_OBTAINED, 8, CommonScript_Print8PlatesObtainedMessage
    Return

CommonScript_ResetPlateCount:
    SetVar VAR_NUM_PLATES_OBTAINED, 1
    Return

CommonScript_Print1PlateObtainedMessage:
    Message pl_msg_00000213_00110
    Return

CommonScript_Print2PlatesObtainedMessage:
    Message pl_msg_00000213_00111
    Return

CommonScript_Print3PlatesObtainedMessage:
    Message pl_msg_00000213_00112
    Return

CommonScript_Print4PlatesObtainedMessage:
    Message pl_msg_00000213_00113
    Return

CommonScript_Print5PlatesObtainedMessage:
    Message pl_msg_00000213_00114
    Return

CommonScript_Print6PlatesObtainedMessage:
    Message pl_msg_00000213_00115
    Return

CommonScript_Print7PlatesObtainedMessage:
    Message pl_msg_00000213_00116
    Return

CommonScript_Print8PlatesObtainedMessage:
    Message pl_msg_00000213_00117
    Return

CommonScript_EmptyScript6:
    End

_1477:
    LockAll
    GetCurrentMapID VAR_0x8004
    GoToIfEq VAR_0x8004, 220, _14AC
    GoToIfEq VAR_0x8004, 0x248, _14AC
    GoToIfEq VAR_0x8004, 0x249, _14AC
    GoTo _1570
    End

_14AC:
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    GoToIfNe VAR_0x8004, 31, _1570
    GoToIfNe VAR_0x8005, 52, _1570
    CheckGameCompleted VAR_MAP_LOCAL_0
    GoToIfEq VAR_MAP_LOCAL_0, FALSE, _1570
    GetNationalDexEnabled VAR_MAP_LOCAL_0
    GoToIfEq VAR_MAP_LOCAL_0, 0, _1570
    CheckDistributionEvent DISTRIBUTION_EVENT_ARCEUS, VAR_MAP_LOCAL_0
    GoToIfEq VAR_MAP_LOCAL_0, FALSE, _1570
    GoToIfSet FLAG_CAUGHT_ARCEUS, _1570
    BufferPlayerName 0
    Message pl_msg_00000213_00122
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_NO, _157B
    BufferPlayerName 0
    Message pl_msg_00000213_00123
    CloseMessage
    WaitTime 30, VAR_RESULT
    PlayMusic SEQ_FUE
    WaitTime 0x21C, VAR_RESULT
    GetPlayerMapPos VAR_0x8004, VAR_0x8005
    FadeScreenOut FADE_SCREEN_SPEED_SLOW, COLOR_WHITE
    WaitFadeScreen
    Warp MAP_HEADER_HALL_OF_ORIGIN, 0, VAR_0x8004, VAR_0x8005, DIR_NORTH
    FadeScreenIn FADE_SCREEN_SPEED_SLOW, COLOR_WHITE
    WaitFadeScreen
    Message pl_msg_00000213_00124
    WaitButton
    CloseMessage
    ReleaseAll
    End

_1570:
    Message pl_msg_00000213_00125
    WaitButton
    CloseMessage
    ReleaseAll
    End

_157B:
    CloseMessage
    ReleaseAll
    End

CommonScript_SetCounterpartBGM:
    StopMusic 0
    GetPlayerGender VAR_RESULT
    CallIfEq VAR_RESULT, GENDER_MALE, CommonScript_SetTheGirlBGM
    CallIfEq VAR_RESULT, GENDER_FEMALE, CommonScript_SetTheBoyBGM
    ReturnCommonScript
    End

CommonScript_SetTheGirlBGM:
    SetBGM SEQ_THE_GIRL
    Return

CommonScript_SetTheBoyBGM:
    SetBGM SEQ_THE_BOY
    Return

CommonScript_SetRivalBGM:
    StopMusic 0
    SetBGM SEQ_THE_RIV
    ReturnCommonScript
    End

CommonScript_SetFollowMeBGM:
    StopMusic 0
    SetBGM SEQ_TSURETEKE
    ReturnCommonScript
    End

CommonScript_SetLookerBGM:
    StopMusic 0
    SetBGM SEQ_PL_HANDSOME
    ReturnCommonScript
    End

CommonScript_FadeToDefaultMusic:
    FadeOutBGM 0, 30
    StopMusic 0
    PlayDefaultMusic
    ReturnCommonScript
    End

_15E7:
    FadeScreenOut
    WaitFadeScreen
    ScrCmd_0B3 VAR_RESULT
    SetVar VAR_0x8004, VAR_RESULT
    ScrCmd_2F6 VAR_0x8005, VAR_0x8004, VAR_RESULT
    GoToIfEq VAR_RESULT, 0, _1624
    ReturnToField
    FadeScreenIn
    WaitFadeScreen
    ReturnCommonScript
    End

_1624:
    ReturnToField
    FadeScreenIn
    WaitFadeScreen
    ReturnCommonScript
    End

_1636:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    SetVar VAR_0x8004, TUTOR_LOCATION_ROUTE_212
    GoTo _1672
    End

_164A:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    SetVar VAR_0x8004, TUTOR_LOCATION_SURVIVAL_AREA
    GoTo _1672
    End

_165E:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    SetVar VAR_0x8004, TUTOR_LOCATION_SNOWPOINT_CITY
    GoTo _1672
    End

_1672:
    Message pl_msg_00000213_00129
    ShowMoveTutorMoveSelectionMenu 0xFF, VAR_0x8004, VAR_RESULT
    SetVar VAR_0x8003, VAR_RESULT
    GoToIfEq VAR_0x8003, -2, _16A4
    ShowShardCost 21, 1, VAR_0x8003, VAR_RESULT
    WaitABPress
    CloseShardCostWindow
    GoTo _16A4
    End

_16A4:
    CloseMessage
    ReleaseAll
    End

CommonScript_Frontier_CheckAllFrontierGoldPrintsObtained:
    GoToIfSet FLAG_OBTAINED_ALL_BATTLE_FRONTIER_GOLD_PRINTS, CommonScript_Frontier_End
    GoToIfNe VAR_BATTLE_FACTORY_PRINT_STATE, 4, CommonScript_Frontier_End
    GoToIfNe VAR_BATTLE_HALL_PRINT_STATE, 4, CommonScript_Frontier_End
    GoToIfNe VAR_BATTLE_CASTLE_PRINT_STATE, 4, CommonScript_Frontier_End
    GoToIfNe VAR_BATTLE_ARCADE_PRINT_STATE, 4, CommonScript_Frontier_End
    GoToIfNe VAR_BATTLE_TOWER_PRINT_STATE, 4, CommonScript_Frontier_End
    SetFlag FLAG_OBTAINED_ALL_BATTLE_FRONTIER_GOLD_PRINTS
    IncrementTrainerScore TRAINER_SCORE_EVENT_ALL_BATTLE_FRONTIER_GOLD_PRINTS
    GoTo CommonScript_Frontier_End
    End

CommonScript_Frontier_End:
    ReturnCommonScript
    End

CommonScript_GriseousOrbCouldNotBeRemoved:
    Message CommonStrings_Text_GriseousOrbCouldNotBeRemoved
    WaitButton
    CloseMessage
    ReleaseAll
    ReturnCommonScript
    End

CommonScript_PortablePC_Simple:
    LockAll
    SetFlag FLAG_UNK_0x0BFF
    PlaySE SEQ_SE_DP_PC_ON
    BufferPlayerName 0
    Message pl_msg_00000213_00032

_SimplePCMenu:
    BufferPlayerName 0
    Message pl_msg_00000213_00033
    InitGlobalTextMenu 1, 1, 0, VAR_0x8006
    CallIfUnset FLAG_MET_BEBE, _SimplePC_SomeonesPC
    CallIfSet FLAG_MET_BEBE, _SimplePC_BebePC
    AddMenuEntryImm 24, 1
    AddMenuEntryImm 25, 2
    AddMenuEntryImm 65, 3
    AddMenuEntryImm 64, 4
    ShowMenu
    SetVar VAR_0x8008, VAR_0x8006
    GoToIfEq VAR_0x8008, 0, _SimplePC_StorageEntry
    GoToIfEq VAR_0x8008, 1, _SimplePC_PreDamageHandler
    GoToIfEq VAR_0x8008, 2, _SimplePC_VolatileStatus_Submenu
    GoToIfEq VAR_0x8008, 3, _SimplePCPokevialHandler
    GoTo _0F70

_SimplePC_SomeonesPC:
    AddMenuEntryImm 58, 0
    Return

_SimplePC_BebePC:
    AddMenuEntryImm 59, 0
    Return

_SimplePC_StorageEntry:
    PlaySE SEQ_SE_DP_PC_LOGIN
    BufferPlayerName 0
    Message pl_msg_00000213_00034
    Call _0D2C
    GoTo _SimplePC_StorageLoop

_SimplePC_StorageLoop:
    ShowListMenu
    SetVar VAR_0x8008, VAR_RESULT
    GoToIfEq VAR_0x8008, 0, _SimplePC_Deposit
    GoToIfEq VAR_0x8008, 1, _SimplePC_Withdraw
    GoToIfEq VAR_0x8008, 2, _SimplePC_Move
    GoToIfEq VAR_0x8008, 3, _SimplePC_MoveItems
    GoToIfEq VAR_0x8008, 4, _SimplePC_Compare
    GoTo _SimplePCMenu

_SimplePC_Deposit:
    CloseMessage
    Call _0F94
    OpenPokemonStorage 0
    ReturnToField
    GoTo _SimplePC_PostStorage

_SimplePC_Withdraw:
    CloseMessage
    Call _0F94
    OpenPokemonStorage 1
    ReturnToField
    GoTo _SimplePC_PostStorage

_SimplePC_Move:
    CloseMessage
    Call _0F94
    OpenPokemonStorage 2
    ReturnToField
    GoTo _SimplePC_PostStorage

_SimplePC_MoveItems:
    CloseMessage
    Call _0F94
    OpenPokemonStorage 3
    ReturnToField
    GoTo _SimplePC_PostStorage

_SimplePC_Compare:
    CloseMessage
    Call _0F94
    OpenPokemonStorage 4
    ReturnToField
    GoTo _SimplePC_PostStorage

_SimplePC_PostStorage:
    ScrCmd_30B
    BufferPlayerName 0
    MessageInstant 33
    Call _0D2C
    Call _0C06
    FadeScreenIn
    GoTo _SimplePC_StorageLoop

_SimplePCPokevialHandler:
    Call _PokevialCore
    GoTo _SimplePCMenu

_SimplePC_PreDamageHandler:
    CloseMessage
    Call _0F94
    OpenPartyMenuForSetHP
    ReturnToField
    Call _0F80
    GoTo _SimplePCMenu

_SimplePC_VolatileStatus_Submenu:
    Message CommonStrings_Text_StatusSubmenu_Header
    InitGlobalTextListMenu 1, 1, 0, VAR_RESULT
    AddListMenuEntry 26, 0
    AddListMenuEntry 27, 1
    AddListMenuEntry 28, 2
    AddListMenuEntry 29, 3
    AddListMenuEntry 30, 4
    AddListMenuEntry 31, 5
    AddListMenuEntry 5, 6
    ShowListMenu
    SetVar VAR_0x8008, VAR_RESULT
    GoToIfEq VAR_0x8008, 0xFFFE, _SimplePCMenu
    GoToIfEq VAR_0x8008, 6, _SimplePCMenu
    CloseMessage
    Call _0F94
    OpenPartyMenuForStatusInflict VAR_0x8008
    ReturnToField
    Call _0F80
    GoTo _SimplePCMenu

    .balign 4, 0

CommonScript_Drifloon_Fly:
    PlayCry SPECIES_DRIFLOON
    Message CommonStrings_Text_DrifloonFly_Intro
    InitGlobalTextListMenu 1, 1, 0, VAR_RESULT
    CallIfSet FLAG_FIRST_ARRIVAL_TWINLEAF_TOWN, CommonScript_Drifloon_AddTwinleaf
    CallIfSet FLAG_FIRST_ARRIVAL_SANDGEM_TOWN, CommonScript_Drifloon_AddSandgem
    CallIfSet FLAG_FIRST_ARRIVAL_JUBILIFE_CITY, CommonScript_Drifloon_AddJubilife
    CallIfSet FLAG_FIRST_ARRIVAL_FLOAROMA_TOWN, CommonScript_Drifloon_AddFloaroma
    CallIfSet FLAG_FIRST_ARRIVAL_ETERNA_CITY, CommonScript_Drifloon_AddEterna
    CallIfSet FLAG_FIRST_ARRIVAL_OREBURGH_CITY, CommonScript_Drifloon_AddOreburgh
    CallIfSet FLAG_FIRST_ARRIVAL_HEARTHOME_CITY, CommonScript_Drifloon_AddHearthome
    CallIfSet FLAG_FIRST_ARRIVAL_SOLACEON_TOWN, CommonScript_Drifloon_AddSolaceon
    CallIfSet FLAG_FIRST_ARRIVAL_PASTORIA_CITY, CommonScript_Drifloon_AddPastoria
    CallIfSet FLAG_FIRST_ARRIVAL_VEILSTONE_CITY, CommonScript_Drifloon_AddVeilstone
    CallIfSet FLAG_FIRST_ARRIVAL_CELESTIC_TOWN, CommonScript_Drifloon_AddCelestic
    CallIfSet FLAG_FIRST_ARRIVAL_SNOWPOINT_CITY, CommonScript_Drifloon_AddSnowpoint
    CallIfSet FLAG_FIRST_ARRIVAL_FIGHT_AREA, CommonScript_Drifloon_AddFightArea
    CallIfSet FLAG_FIRST_ARRIVAL_SURVIVAL_AREA, CommonScript_Drifloon_AddSurvivalArea
    CallIfSet FLAG_FIRST_ARRIVAL_RESORT_AREA, CommonScript_Drifloon_AddResortArea
    CallIfSet FLAG_FIRST_ARRIVAL_CANALAVE_CITY, CommonScript_Drifloon_AddCanalave
    CallIfSet FLAG_FIRST_ARRIVAL_SUNYSHORE_CITY, CommonScript_Drifloon_AddSunyshore
    CallIfSet FLAG_FIRST_ARRIVAL_OUTSIDE_VICTORY_ROAD, CommonScript_Drifloon_AddVictoryRoad
    CallIfSet FLAG_FIRST_ARRIVAL_POKEMON_LEAGUE, CommonScript_Drifloon_AddPokemonLeague
    AddListMenuEntry MenuEntries_Text_Drifloon_NeverMind, 0xFF
    ShowListMenuRememberCursor VAR_0x8004, VAR_0x8005
    GoToIfEq VAR_RESULT, 0xEEEE, CommonScript_Drifloon_Cancel
    GoToIfEq VAR_RESULT, 0xFF, CommonScript_Drifloon_Cancel
    GoToIfEq VAR_RESULT, 0, CommonScript_Drifloon_FlyTwinleaf
    GoToIfEq VAR_RESULT, 1, CommonScript_Drifloon_FlySandgem
    GoToIfEq VAR_RESULT, 2, CommonScript_Drifloon_FlyJubilife
    GoToIfEq VAR_RESULT, 3, CommonScript_Drifloon_FlyFloaroma
    GoToIfEq VAR_RESULT, 4, CommonScript_Drifloon_FlyEterna
    GoToIfEq VAR_RESULT, 5, CommonScript_Drifloon_FlyOreburgh
    GoToIfEq VAR_RESULT, 6, CommonScript_Drifloon_FlyHearthome
    GoToIfEq VAR_RESULT, 7, CommonScript_Drifloon_FlySolaceon
    GoToIfEq VAR_RESULT, 8, CommonScript_Drifloon_FlyPastoria
    GoToIfEq VAR_RESULT, 9, CommonScript_Drifloon_FlyVeilstone
    GoToIfEq VAR_RESULT, 10, CommonScript_Drifloon_FlyCelestic
    GoToIfEq VAR_RESULT, 11, CommonScript_Drifloon_FlySnowpoint
    GoToIfEq VAR_RESULT, 12, CommonScript_Drifloon_FlyCanalave
    GoToIfEq VAR_RESULT, 13, CommonScript_Drifloon_FlySunyshore
    GoToIfEq VAR_RESULT, 14, CommonScript_Drifloon_FlyVictoryRoad
    GoToIfEq VAR_RESULT, 15, CommonScript_Drifloon_FlyPokemonLeague
    GoToIfEq VAR_RESULT, 16, CommonScript_Drifloon_FlyFightArea
    GoToIfEq VAR_RESULT, 17, CommonScript_Drifloon_FlySurvivalArea
    GoToIfEq VAR_RESULT, 18, CommonScript_Drifloon_FlyResortArea
    GoTo CommonScript_Drifloon_Cancel

CommonScript_Drifloon_Cancel:
    CloseMessage
    ReturnCommonScript
    End

CommonScript_Drifloon_FlyTwinleaf:
    CloseMessage
    ReturnCommonScript
    UseFly MAP_HEADER_TWINLEAF_TOWN, 0x74, 0x376
    End

CommonScript_Drifloon_FlySandgem:
    CloseMessage
    ReturnCommonScript
    UseFly MAP_HEADER_SANDGEM_TOWN, 0xB1, 0x34B
    End

CommonScript_Drifloon_FlyJubilife:
    CloseMessage
    ReturnCommonScript
    UseFly MAP_HEADER_JUBILIFE_CITY, 0xB4, 0x309
    End

CommonScript_Drifloon_FlyFloaroma:
    CloseMessage
    ReturnCommonScript
    UseFly MAP_HEADER_FLOAROMA_TOWN, 0xB0, 0x29B
    End

CommonScript_Drifloon_FlyEterna:
    CloseMessage
    ReturnCommonScript
    UseFly MAP_HEADER_ETERNA_CITY, 0x131, 0x213
    End

CommonScript_Drifloon_FlyOreburgh:
    CloseMessage
    ReturnCommonScript
    UseFly MAP_HEADER_OREBURGH_CITY, 0x12F, 0x2F5
    End

CommonScript_Drifloon_FlyHearthome:
    CloseMessage
    ReturnCommonScript
    UseFly MAP_HEADER_HEARTHOME_CITY, 0x1D1, 0x2BA
    End

CommonScript_Drifloon_FlySolaceon:
    CloseMessage
    ReturnCommonScript
    UseFly MAP_HEADER_SOLACEON_TOWN, 0x236, 0x291
    End

CommonScript_Drifloon_FlyPastoria:
    CloseMessage
    ReturnCommonScript
    UseFly MAP_HEADER_PASTORIA_CITY, 0x258, 0x330
    End

CommonScript_Drifloon_FlyVeilstone:
    CloseMessage
    ReturnCommonScript
    UseFly MAP_HEADER_VEILSTONE_CITY, 0x2CD, 0x264
    End

CommonScript_Drifloon_FlyCelestic:
    CloseMessage
    ReturnCommonScript
    UseFly MAP_HEADER_CELESTIC_TOWN, 0x1D8, 0x21B
    End

CommonScript_Drifloon_FlySnowpoint:
    CloseMessage
    ReturnCommonScript
    UseFly MAP_HEADER_SNOWPOINT_CITY, 0x17B, 0xEA
    End

CommonScript_Drifloon_FlyCanalave:
    CloseMessage
    ReturnCommonScript
    UseFly MAP_HEADER_CANALAVE_CITY, 0x3A, 0x2D3
    End

CommonScript_Drifloon_FlySunyshore:
    CloseMessage
    ReturnCommonScript
    UseFly MAP_HEADER_SUNYSHORE_CITY, 0x35C, 0x311
    End

CommonScript_Drifloon_FlyVictoryRoad:
    CloseMessage
    ReturnCommonScript
    UseFly MAP_HEADER_POKEMON_LEAGUE, 0x34A, 0x257
    End

CommonScript_Drifloon_FlyPokemonLeague:
    CloseMessage
    ReturnCommonScript
    UseFly MAP_HEADER_POKEMON_LEAGUE, 0x34F, 0x230
    End

CommonScript_Drifloon_FlyFightArea:
    CloseMessage
    ReturnCommonScript
    UseFly MAP_HEADER_FIGHT_AREA, 0x287, 0x1AE
    End

CommonScript_Drifloon_FlySurvivalArea:
    CloseMessage
    ReturnCommonScript
    UseFly MAP_HEADER_SURVIVAL_AREA, 0x293, 0x153
    End

CommonScript_Drifloon_FlyResortArea:
    CloseMessage
    ReturnCommonScript
    UseFly MAP_HEADER_RESORT_AREA, 0x322, 0x1D9
    End

CommonScript_Drifloon_AddTwinleaf:
    AddListMenuEntry MenuEntries_Text_Drifloon_TwinleafTown, 0
    Return

CommonScript_Drifloon_AddSandgem:
    AddListMenuEntry MenuEntries_Text_Drifloon_SandgemTown, 1
    Return

CommonScript_Drifloon_AddJubilife:
    AddListMenuEntry MenuEntries_Text_Drifloon_JubilifeCity, 2
    Return

CommonScript_Drifloon_AddFloaroma:
    AddListMenuEntry MenuEntries_Text_Drifloon_FloaromaTown, 3
    Return

CommonScript_Drifloon_AddEterna:
    AddListMenuEntry MenuEntries_Text_Drifloon_EternaCity, 4
    Return

CommonScript_Drifloon_AddOreburgh:
    AddListMenuEntry MenuEntries_Text_Drifloon_OreburghCity, 5
    Return

CommonScript_Drifloon_AddHearthome:
    AddListMenuEntry MenuEntries_Text_Drifloon_HearthomeCity, 6
    Return

CommonScript_Drifloon_AddSolaceon:
    AddListMenuEntry MenuEntries_Text_Drifloon_SolaceonTown, 7
    Return

CommonScript_Drifloon_AddPastoria:
    AddListMenuEntry MenuEntries_Text_Drifloon_PastoriaCity, 8
    Return

CommonScript_Drifloon_AddVeilstone:
    AddListMenuEntry MenuEntries_Text_Drifloon_VeilstoneCity, 9
    Return

CommonScript_Drifloon_AddCelestic:
    AddListMenuEntry MenuEntries_Text_Drifloon_CelesticTown, 10
    Return

CommonScript_Drifloon_AddSnowpoint:
    AddListMenuEntry MenuEntries_Text_Drifloon_SnowpointCity, 11
    Return

CommonScript_Drifloon_AddCanalave:
    AddListMenuEntry MenuEntries_Text_Drifloon_CanalabeCity, 12
    Return

CommonScript_Drifloon_AddSunyshore:
    AddListMenuEntry MenuEntries_Text_Drifloon_SunshoreCity, 13
    Return

CommonScript_Drifloon_AddVictoryRoad:
    AddListMenuEntry MenuEntries_Text_Drifloon_VictoryRoad, 14
    Return

CommonScript_Drifloon_AddPokemonLeague:
    AddListMenuEntry MenuEntries_Text_Drifloon_PokemonLeague, 15
    Return

CommonScript_Drifloon_AddFightArea:
    AddListMenuEntry MenuEntries_Text_Drifloon_FightArea, 16
    Return

CommonScript_Drifloon_AddSurvivalArea:
    AddListMenuEntry MenuEntries_Text_Drifloon_SurvivalArea, 17
    Return

CommonScript_Drifloon_AddResortArea:
    AddListMenuEntry MenuEntries_Text_Drifloon_ResortArea, 18
    Return

    .balign 4, 0
CommonScript_RocketMansionGrunt1:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    PlayTrainerEncounterBGM TRAINER_ROCKET_GRUNT_MANSION_1
    Message CommonStrings_Text_RocketGrunt1Intro
    WaitButton
    CloseMessage
    StartTrainerBattle TRAINER_ROCKET_GRUNT_MANSION_1
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, CommonScript_RocketMansion_BlackOut
    Message CommonStrings_Text_RocketGruntFlee
    WaitButton
    CloseMessage
    FadeScreenOut
    WaitFadeScreen
    SetTrainerFlag TRAINER_ROCKET_GRUNT_MANSION_1
    SetFlag FLAG_HIDE_MANSION_ROCKET_GRUNT_1
    RemoveObject LOCALID_MANSION_ROCKET_GRUNT_1
    FadeScreenIn
    WaitFadeScreen
    GoTo CommonScript_RocketMansion_AnnounceRemaining

CommonScript_RocketMansionGrunt2:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    PlayTrainerEncounterBGM TRAINER_ROCKET_GRUNT_MANSION_2
    Message CommonStrings_Text_RocketGrunt2Intro
    WaitButton
    CloseMessage
    StartTrainerBattle TRAINER_ROCKET_GRUNT_MANSION_2
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, CommonScript_RocketMansion_BlackOut
    Message CommonStrings_Text_RocketGruntFlee
    WaitButton
    CloseMessage
    FadeScreenOut
    WaitFadeScreen
    SetTrainerFlag TRAINER_ROCKET_GRUNT_MANSION_2
    SetFlag FLAG_HIDE_MANSION_ROCKET_GRUNT_2
    RemoveObject LOCALID_MANSION_ROCKET_GRUNT_2
    FadeScreenIn
    WaitFadeScreen
    GoTo CommonScript_RocketMansion_AnnounceRemaining

CommonScript_RocketMansionGrunt3:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    PlayTrainerEncounterBGM TRAINER_ROCKET_GRUNT_MANSION_3
    Message CommonStrings_Text_RocketGrunt3Intro
    WaitButton
    CloseMessage
    StartTrainerBattle TRAINER_ROCKET_GRUNT_MANSION_3
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, CommonScript_RocketMansion_BlackOut
    Message CommonStrings_Text_RocketGruntFlee
    WaitButton
    CloseMessage
    FadeScreenOut
    WaitFadeScreen
    SetTrainerFlag TRAINER_ROCKET_GRUNT_MANSION_3
    SetFlag FLAG_HIDE_MANSION_ROCKET_GRUNT_3
    RemoveObject LOCALID_OFFICE_ROCKET_GRUNT_1
    FadeScreenIn
    WaitFadeScreen
    GoTo CommonScript_RocketMansion_AnnounceRemaining

CommonScript_RocketMansionGrunt4:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    PlayTrainerEncounterBGM TRAINER_ROCKET_GRUNT_MANSION_4
    Message CommonStrings_Text_RocketGrunt4Intro
    WaitButton
    CloseMessage
    StartTrainerBattle TRAINER_ROCKET_GRUNT_MANSION_4
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, CommonScript_RocketMansion_BlackOut
    Message CommonStrings_Text_RocketGruntFlee
    WaitButton
    CloseMessage
    FadeScreenOut
    WaitFadeScreen
    SetTrainerFlag TRAINER_ROCKET_GRUNT_MANSION_4
    SetFlag FLAG_HIDE_MANSION_ROCKET_GRUNT_4
    RemoveObject LOCALID_OFFICE_ROCKET_GRUNT_2
    FadeScreenIn
    WaitFadeScreen
    GoTo CommonScript_RocketMansion_AnnounceRemaining

CommonScript_RocketMansionGrunt5:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    PlayTrainerEncounterBGM TRAINER_ROCKET_GRUNT_MANSION_5
    Message CommonStrings_Text_RocketGrunt5Intro
    WaitButton
    CloseMessage
    StartTrainerBattle TRAINER_ROCKET_GRUNT_MANSION_5
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, CommonScript_RocketMansion_BlackOut
    Message CommonStrings_Text_RocketGruntFlee
    WaitButton
    CloseMessage
    FadeScreenOut
    WaitFadeScreen
    SetTrainerFlag TRAINER_ROCKET_GRUNT_MANSION_5
    SetFlag FLAG_HIDE_MANSION_ROCKET_GRUNT_5
    RemoveObject LOCALID_MAIDS_ROCKET_GRUNT_1
    FadeScreenIn
    WaitFadeScreen
    GoTo CommonScript_RocketMansion_AnnounceRemaining

CommonScript_RocketMansionGrunt6:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    PlayTrainerEncounterBGM TRAINER_ROCKET_GRUNT_MANSION_6
    Message CommonStrings_Text_RocketGrunt6Intro
    WaitButton
    CloseMessage
    StartTrainerBattle TRAINER_ROCKET_GRUNT_MANSION_6
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, CommonScript_RocketMansion_BlackOut
    Message CommonStrings_Text_RocketGruntFlee
    WaitButton
    CloseMessage
    FadeScreenOut
    WaitFadeScreen
    SetTrainerFlag TRAINER_ROCKET_GRUNT_MANSION_6
    SetFlag FLAG_HIDE_MANSION_ROCKET_GRUNT_6
    RemoveObject LOCALID_MAIDS_ROCKET_GRUNT_2
    FadeScreenIn
    WaitFadeScreen
    GoTo CommonScript_RocketMansion_AnnounceRemaining

CommonScript_RocketMansionGrunt7:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    PlayTrainerEncounterBGM TRAINER_ROCKET_GRUNT_MANSION_7
    Message CommonStrings_Text_RocketGrunt7Intro
    WaitButton
    CloseMessage
    StartTrainerBattle TRAINER_ROCKET_GRUNT_MANSION_7
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, CommonScript_RocketMansion_BlackOut
    Message CommonStrings_Text_RocketGruntFlee
    WaitButton
    CloseMessage
    FadeScreenOut
    WaitFadeScreen
    SetTrainerFlag TRAINER_ROCKET_GRUNT_MANSION_7
    SetFlag FLAG_HIDE_MANSION_ROCKET_GRUNT_7
    RemoveObject LOCALID_MAIDS_ROCKET_GRUNT_3
    FadeScreenIn
    WaitFadeScreen
    GoTo CommonScript_RocketMansion_AnnounceRemaining

CommonScript_RocketMansion_CountRemaining:
    SetVar VAR_0x8004, 0
    GoToIfSet FLAG_HIDE_MANSION_ROCKET_GRUNT_1, CommonScript_RocketMansion_Count2
    AddVar VAR_0x8004, 1
CommonScript_RocketMansion_Count2:
    GoToIfSet FLAG_HIDE_MANSION_ROCKET_GRUNT_2, CommonScript_RocketMansion_Count3
    AddVar VAR_0x8004, 1
CommonScript_RocketMansion_Count3:
    GoToIfSet FLAG_HIDE_MANSION_ROCKET_GRUNT_3, CommonScript_RocketMansion_Count4
    AddVar VAR_0x8004, 1
CommonScript_RocketMansion_Count4:
    GoToIfSet FLAG_HIDE_MANSION_ROCKET_GRUNT_4, CommonScript_RocketMansion_Count5
    AddVar VAR_0x8004, 1
CommonScript_RocketMansion_Count5:
    GoToIfSet FLAG_HIDE_MANSION_ROCKET_GRUNT_5, CommonScript_RocketMansion_Count6
    AddVar VAR_0x8004, 1
CommonScript_RocketMansion_Count6:
    GoToIfSet FLAG_HIDE_MANSION_ROCKET_GRUNT_6, CommonScript_RocketMansion_Count7
    AddVar VAR_0x8004, 1
CommonScript_RocketMansion_Count7:
    GoToIfSet FLAG_HIDE_MANSION_ROCKET_GRUNT_7, CommonScript_RocketMansion_CountDone
    AddVar VAR_0x8004, 1
CommonScript_RocketMansion_CountDone:
    Return

CommonScript_RocketMansion_AnnounceRemaining:
    Call CommonScript_RocketMansion_CountRemaining
    GoToIfEq VAR_0x8004, 0, CommonScript_RocketMansion_AllGruntsDefeated
    GoToIfEq VAR_0x8004, 1, CommonScript_RocketMansion_OneGruntLeft
    BufferNumber 0, VAR_0x8004
    Message CommonStrings_Text_RocketGruntsRemain
    WaitButton
    CloseMessage
    ReleaseAll
    End

CommonScript_RocketMansion_OneGruntLeft:
    Message CommonStrings_Text_RocketOneGruntLeft
    WaitButton
    CloseMessage
    ReleaseAll
    End

CommonScript_RocketMansion_AllGruntsDefeated:
    SetFlag FLAG_MANSION_ALL_GRUNTS_DEFEATED
    Message CommonStrings_Text_RocketAllGruntsDefeated
    WaitButton
    CloseMessage
    ReleaseAll
    End

CommonScript_RocketMansion_BlackOut:
    BlackOutFromBattle
    ReleaseAll
    End

CommonScript_RocketMansionAriana:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfUnset FLAG_MANSION_ALL_GRUNTS_DEFEATED, CommonScript_RocketMansion_ArianaBrushOff
    PlayTrainerEncounterBGM TRAINER_ROCKET_ARIANA
    Message CommonStrings_Text_ArianaChallenge
    WaitButton
    CloseMessage
    StartTrainerBattle TRAINER_ROCKET_ARIANA
    CheckWonBattle VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, CommonScript_RocketMansion_BlackOut
    Message CommonStrings_Text_ArianaDefeat
    WaitButton
    CloseMessage
    FadeScreenOut
    WaitFadeScreen
    SetFlag FLAG_MANSION_ROCKET_CLEARED
    RemoveObject LOCALID_MANSION_ARIANA
    SetPosition LOCALID_PLAYER, 33, 0, 7, DIR_NORTH
    CheckHasFollower VAR_RESULT
    CallIfEq VAR_RESULT, TRUE, CommonScript_RocketMansion_PlaceFollower
    ClearFlag FLAG_HIDE_MANSION_STAFF_PRE_CLEAR
    ClearFlag FLAG_ALT_MUSIC_POKEMON_MANSION
    FadeOutBGM 0, 30
    StopMusic 0
    PlayDefaultMusic
    FadeInBGM 30
    FadeScreenIn
    WaitFadeScreen
    ApplyMovement LOCALID_MANSION_BACKLOT, CommonScript_RocketMansion_Movement_BacklotApproach
    ApplyMovement LOCALID_MANSION_BUTLER, CommonScript_RocketMansion_Movement_ButlerApproach
    WaitMovement
    Message CommonStrings_Text_BacklotThanks
    WaitButton
    CloseMessage
    ApplyMovement LOCALID_MANSION_BACKLOT, CommonScript_RocketMansion_Movement_BacklotLeave
    ApplyMovement LOCALID_MANSION_BUTLER, CommonScript_RocketMansion_Movement_ButlerLeave
    WaitMovement
    RemoveObject LOCALID_MANSION_BACKLOT
    RemoveObject LOCALID_MANSION_BUTLER
    ReleaseAll
    End

CommonScript_RocketMansion_PlaceFollower:
    SetPosition 253, 33, 0, 8, DIR_NORTH
    Return

CommonScript_RocketMansion_ArianaBrushOff:
    Message CommonStrings_Text_ArianaBrushOff
    WaitButton
    CloseMessage
    ReleaseAll
    End

CommonScript_RocketMansionBacklot:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message CommonStrings_Text_BacklotWorried
    WaitButton
    CloseMessage
    ReleaseAll
    End

CommonScript_RocketMansionButler:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message CommonStrings_Text_ButlerWorried
    WaitButton
    CloseMessage
    ReleaseAll
    End

    .balign 4, 0
CommonScript_RocketMansion_Movement_BacklotApproach:
    WalkNormalSouth 3
    EndMovement

    .balign 4, 0
CommonScript_RocketMansion_Movement_ButlerApproach:
    WalkNormalSouth 3
    EndMovement

    .balign 4, 0
CommonScript_RocketMansion_Movement_BacklotLeave:
    WalkNormalEast 1
    WalkNormalSouth 1
    WalkNormalEast 8
    SetInvisible
    EndMovement

    .balign 4, 0
CommonScript_RocketMansion_Movement_ButlerLeave:
    WalkNormalEast 2
    WalkNormalSouth 1
    WalkNormalEast 8
    SetInvisible
    EndMovement

    .balign 4, 0
