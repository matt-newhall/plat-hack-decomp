#include "macros/scrcmd.inc"
#include "res/text/bank/sandgem_town_pokecenter_1f.h"
#include "res/field/events/events_sandgem_town_pokecenter_1f.h"


    ScriptEntry SandgemTownPokecenter1F_PokecenterNurse
    ScriptEntry SandgemTownPokecenter1F_BreederM
    ScriptEntry SandgemTownPokecenter1F_ExpertM
    ScriptEntry SandgemTownPokecenter1F_Lass
    ScriptEntry SandgemTown_Guitarist
    ScriptEntryEnd

SandgemTownPokecenter1F_PokecenterNurse:
    Common_CallPokecenterNurse LOCALID_POKECENTER_NURSE
    End

SandgemTownPokecenter1F_BreederM:
    NPCMessage SandgemTownPokecenter1F_Text_ThatLadyAtTheCounterWillHealYourPokemon
    End

SandgemTownPokecenter1F_ExpertM:
    NPCMessage SandgemTownPokecenter1F_Text_DoYouSeeThatPCOverThere
    End

SandgemTownPokecenter1F_Lass:
    NPCMessage SandgemTownPokecenter1F_Text_TheTopFloorIsTheCommunicationClub
    End

SandgemTown_Guitarist:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet FLAG_TALKED_TO_VEILSTONE_CITY_PRIZE_EXCHANGE_GUITARIST, SandgemTown_AskTellHiddenPowerType
    SetFlag FLAG_TALKED_TO_VEILSTONE_CITY_PRIZE_EXCHANGE_GUITARIST
    Message SandgemTown_Text_ICanTellHiddenPowerTypes
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_NO, SandgemTown_IfYouWantAskMe
    GoTo SandgemTown_TryTellHiddenPowerType
    End

SandgemTown_AskTellHiddenPowerType:
    Message SandgemTown_Text_IllTellHiddenPowerTypes
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_NO, SandgemTown_IfYouWantAskMe
    GoTo SandgemTown_TryTellHiddenPowerType
    End

SandgemTown_TryTellHiddenPowerType:
    CloseMessage
    FadeScreenOut
    WaitFadeScreen
    SelectMoveTutorPokemon
    GetSelectedPartySlot VAR_0x8000
    ReturnToField
    FadeScreenIn
    WaitFadeScreen
    GoToIfEq VAR_0x8000, PARTY_SLOT_NONE, SandgemTown_IfYouWantAskMe
    GetPartyMonSpecies VAR_0x8000, VAR_0x8001
    GoToIfEq VAR_0x8001, 0, SandgemTown_EggsCantLearnMoves
    CalcHiddenPowerType VAR_0x8000, VAR_0x8004
    GoToIfEq VAR_0x8004, -1, SandgemTown_PokemonCantLearnHiddenPower
    CheckPartyMonHasMove VAR_RESULT, MOVE_HIDDEN_POWER, VAR_0x8000
    GoToIfEq VAR_RESULT, 0, SandgemTown_PokemonsHiddenPowerWouldBeType
    BufferTypeName 0, VAR_0x8004
    Message SandgemTown_Text_PokemonsHiddenPowerIsType
    GoTo SandgemTown_GuitaristEnd
    End

SandgemTown_PokemonCantLearnHiddenPower:
    Message SandgemTown_Text_PokemonCantLearnHiddenPower
    GoTo SandgemTown_GuitaristEnd
    End

SandgemTown_IfYouWantAskMe:
    Message SandgemTown_Text_IfYouWantAskMe
    GoTo SandgemTown_GuitaristEnd
    End

SandgemTown_EggsCantLearnMoves:
    Message SandgemTown_Text_EggsCantLearnMoves
    GoTo SandgemTown_GuitaristEnd
    End

SandgemTown_PokemonsHiddenPowerWouldBeType:
    BufferTypeName 0, VAR_0x8004
    Message SandgemTown_Text_PokemonsHiddenPowerWouldBeType
    GoTo SandgemTown_GuitaristEnd
    End

SandgemTown_GuitaristEnd:
    WaitButton
    CloseMessage
    ReleaseAll
    End

    .balign 4, 0
