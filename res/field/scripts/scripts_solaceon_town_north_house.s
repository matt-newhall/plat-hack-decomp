#include "macros/scrcmd.inc"
#include "res/text/bank/solaceon_town_north_house.h"


    ScriptEntry SolaceonTownNorthHouse_OldWoman
    ScriptEntry SolaceonTownNorthHouse_Lass
    ScriptEntryEnd

SolaceonTownNorthHouse_OldWoman:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet FLAG_RECEIVED_SOLACEON_TOWN_NORTH_HOUSE_UNOWN, SolaceonTownNorthHouse_CherishThoseWhoRemain
    SetVar VAR_MAP_LOCAL_2, SPECIES_UNOWN
    BufferSpeciesNameFromVar 1, VAR_MAP_LOCAL_2, 0, 0
    Message SolaceonTownNorthHouse_Text_UnownReflectsYourJourney
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_NO, SolaceonTownNorthHouse_DontAcceptUnown
    GetPartyCount VAR_RESULT
    GoToIfEq VAR_RESULT, 6, SolaceonTownNorthHouse_PartyIsFull
    Call SolaceonTownNorthHouse_GetUnownForm
    Message SolaceonTownNorthHouse_Text_TakeGoodCareOfIt
    PlayFanfare SEQ_FANFA4
    BufferPlayerName 0
    Message SolaceonTownNorthHouse_Text_PlayerReceivedTheUnown
    WaitFanfare
    GivePokemonWithForm SPECIES_UNOWN, 35, VAR_MAP_LOCAL_1, ITEM_NONE, VAR_RESULT
    SetFlag FLAG_RECEIVED_SOLACEON_TOWN_NORTH_HOUSE_UNOWN
    Message SolaceonTownNorthHouse_Text_AskNicknameUnown
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_YES, SolaceonTownNorthHouse_NicknameUnown
    GoToIfEq VAR_RESULT, MENU_NO, SolaceonTownNorthHouse_DontNicknameUnown
    End

SolaceonTownNorthHouse_GetUnownForm:
    GetGameRecord RECORD_PLAYER_MON_FAINTED, VAR_MAP_LOCAL_0, VAR_MAP_LOCAL_1
    GoToIfNe VAR_MAP_LOCAL_0, 0, SolaceonTownNorthHouse_SetUnownFormQuestion
    GoToIfEq VAR_MAP_LOCAL_1, 0, SolaceonTownNorthHouse_SetUnownFormExclamation
    GoToIfGt VAR_MAP_LOCAL_1, 26, SolaceonTownNorthHouse_SetUnownFormQuestion
    SubVar VAR_MAP_LOCAL_1, 1
    Return

SolaceonTownNorthHouse_SetUnownFormExclamation:
    SetVar VAR_MAP_LOCAL_1, UNOWN_FORM_EXC
    Return

SolaceonTownNorthHouse_SetUnownFormQuestion:
    SetVar VAR_MAP_LOCAL_1, UNOWN_FORM_QUE
    Return

SolaceonTownNorthHouse_NicknameUnown:
    CloseMessage
    GetPartyCount VAR_MAP_LOCAL_0
    SubVar VAR_MAP_LOCAL_0, 1
    FadeScreenOut
    WaitFadeScreen
    OpenPokemonNamingScreen VAR_MAP_LOCAL_0, VAR_RESULT
    CallIfNe VAR_RESULT, 1, SolaceonTownNorthHouse_IncrementRecordPokemonNicknamed
    FadeScreenIn
    WaitFadeScreen
    ReleaseAll
    End

SolaceonTownNorthHouse_IncrementRecordPokemonNicknamed:
    IncrementGameRecord RECORD_POKEMON_NICKNAMED
    Return

SolaceonTownNorthHouse_DontNicknameUnown:
    CloseMessage
    ReleaseAll
    End

SolaceonTownNorthHouse_PartyIsFull:
    Message SolaceonTownNorthHouse_Text_AlreadyWholeTeam
    GoTo SolaceonTownNorthHouse_OldWomanEnd
    End

SolaceonTownNorthHouse_DontAcceptUnown:
    Message SolaceonTownNorthHouse_Text_ItWillWait
    GoTo SolaceonTownNorthHouse_OldWomanEnd
    End

SolaceonTownNorthHouse_CherishThoseWhoRemain:
    Message SolaceonTownNorthHouse_Text_CherishThoseWhoRemain
    GoTo SolaceonTownNorthHouse_OldWomanEnd
    End

SolaceonTownNorthHouse_OldWomanEnd:
    WaitButton
    CloseMessage
    ReleaseAll
    End

SolaceonTownNorthHouse_Lass:
    NPCMessage SolaceonTownNorthHouse_Text_ItHasntBeenProvenThatPokemonLayEggs
    End

    .balign 4, 0
