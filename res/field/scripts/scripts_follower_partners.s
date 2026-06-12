#include "macros/scrcmd.inc"
#include "res/text/bank/follower_partners.h"


    ScriptEntry FollowerPartners_Rival
    ScriptEntry _00F9
    ScriptEntry FollowerPartners_Cheryl
    ScriptEntry FollowerPartners_Buck
    ScriptEntry FollowerPartners_Mira
    ScriptEntry FollowerPartners_Marley
    ScriptEntry FollowerMon_Talk
    ScriptEntryEnd

FollowerPartners_Rival:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfGe VAR_FOLLOWER_RIVAL_STATE, 3, FollowerPartners_Rival_PostStarterMessage
    BufferPlayerName 1
    Message FollowerPartners_Text_Rival_HeyPlayerYouCanChooseFirst
    WaitButton
    CloseMessage
    ReleaseAll
    End

FollowerPartners_Rival_PostStarterMessage:
    GoToIfGe VAR_FOLLOWER_RIVAL_TIMES_TALKED, 5, FollowerPartners_Rival_HeyThatsEnoughTalkingAlready
    GoToIfEq VAR_FOLLOWER_RIVAL_TIMES_TALKED, 4, FollowerPartners_Rival_HeyDoYouKnowAboutTheChampion
    GoToIfEq VAR_FOLLOWER_RIVAL_TIMES_TALKED, 3, FollowerPartners_Rival_ThatLakeHasAMiragePokemonLivingInIt
    GoToIfEq VAR_FOLLOWER_RIVAL_TIMES_TALKED, 2, FollowerPartners_Rival_DoYouBelieveIt
    GoToIfEq VAR_FOLLOWER_RIVAL_TIMES_TALKED, 1, FollowerPartners_Rival_PokemonAllHaveDifferentMovesHuh
    BufferRivalName 0
    Message FollowerPartners_Text_Rival_ThatPokemonBattle
    WaitButton
    GoTo FollowerPartners_Rival_IncreaseTimesTalked
    End

FollowerPartners_Rival_Unused:
    BufferRivalName 0
    Message FollowerPartners_Text_Rival_AllRightLetsMoveOut
    WaitButton
    CloseMessage
    ReleaseAll
    End

FollowerPartners_Rival_HeyThatsEnoughTalkingAlready:
    BufferRivalName 0
    Message FollowerPartners_Text_Rival_HeyThatsEnoughTalkingAlready
    WaitButton
    CloseMessage
    ReleaseAll
    End

FollowerPartners_Rival_HeyDoYouKnowAboutTheChampion:
    BufferRivalName 0
    Message FollowerPartners_Text_Rival_HeyDoYouKnowAboutTheChampion
    WaitButton
    GoTo FollowerPartners_Rival_IncreaseTimesTalked
    End

FollowerPartners_Rival_ThatLakeHasAMiragePokemonLivingInIt:
    BufferRivalName 0
    Message FollowerPartners_Text_Rival_ThatLakeHasAMiragePokemonLivingInIt
    WaitButton
    GoTo FollowerPartners_Rival_IncreaseTimesTalked
    End

FollowerPartners_Rival_DoYouBelieveIt:
    BufferRivalName 0
    BufferRivalStarterSpeciesName 1
    Message FollowerPartners_Text_Rival_DoYouBelieveIt
    WaitButton
    GoTo FollowerPartners_Rival_IncreaseTimesTalked
    End

FollowerPartners_Rival_PokemonAllHaveDifferentMovesHuh:
    BufferRivalName 0
    Message FollowerPartners_Text_Rival_PokemonAllHaveDifferentMovesHuh
    WaitButton
    GoTo FollowerPartners_Rival_IncreaseTimesTalked
    End

FollowerPartners_Rival_IncreaseTimesTalked:
    AddVar VAR_FOLLOWER_RIVAL_TIMES_TALKED, 1
    CloseMessage
    ReleaseAll
    End

_00F9:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfGe VAR_UNK_0x40CB, 2, _0126
    GoToIfEq VAR_UNK_0x40CB, 1, _0131
    BufferRivalName 0
    GoTo _013C
    End

_0126:
    BufferRivalName 0
    WaitButton
    CloseMessage
    ReleaseAll
    End

_0131:
    BufferRivalName 0
    GoTo _013C
    End

_013C:
    WaitButton
    CloseMessage
    AddVar VAR_UNK_0x40CB, 1
    ReleaseAll
    End

FollowerPartners_Cheryl:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfGe VAR_FOLLOWER_CHERYL_TIMES_TALKED, 2, FollowerPartners_Cheryl_PlayerBattlingWithYouMakesMeFeelElated
    GoToIfEq VAR_FOLLOWER_CHERYL_TIMES_TALKED, 1, FollowerPartners_Cheryl_MyPokemonIsAnExcellentHealer
    BufferPlayerName 0
    Message FollowerPartners_Text_Cheryl_ItsStartlingToSeeTwoWildPokemon
    GoTo FollowerPartners_Cheryl_IncreaseTimesTalked
    End

FollowerPartners_Cheryl_MyPokemonIsAnExcellentHealer:
    Message FollowerPartners_Text_Cheryl_MyPokemonIsAnExcellentHealer
    GoTo FollowerPartners_Cheryl_IncreaseTimesTalked
    End

FollowerPartners_Cheryl_PlayerBattlingWithYouMakesMeFeelElated:
    BufferPlayerName 0
    Message FollowerPartners_Text_Cheryl_PlayerBattlingWithYouMakesMeFeelElated
    WaitButton
    CloseMessage
    ReleaseAll
    End

FollowerPartners_Cheryl_IncreaseTimesTalked:
    AddVar VAR_FOLLOWER_CHERYL_TIMES_TALKED, 1
    WaitButton
    CloseMessage
    ReleaseAll
    End

FollowerPartners_Buck:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfGe VAR_FOLLOWER_BUCK_TIMES_TALKED, 3, FollowerPartners_Buck_ItMightBeCoolBeingAGymLeaderOrEliteFour
    GoToIfEq VAR_FOLLOWER_BUCK_TIMES_TALKED, 2, FollowerPartners_Buck_MyBigBrothersOneOfTheEliteFour
    GoToIfEq VAR_FOLLOWER_BUCK_TIMES_TALKED, 1, FollowerPartners_Buck_TheresNoLawThatSaysIHaveToBeTough
    BufferPlayerName 0
    Message FollowerPartners_Text_Buck_ThisIsWhereIRaisedMyPokemon
    GoTo FollowerPartners_Buck_IncreaseTimesTalked
    End

FollowerPartners_Buck_TheresNoLawThatSaysIHaveToBeTough:
    Message FollowerPartners_Text_Buck_TheresNoLawThatSaysIHaveToBeTough
    GoTo FollowerPartners_Buck_IncreaseTimesTalked
    End

FollowerPartners_Buck_MyBigBrothersOneOfTheEliteFour:
    Message FollowerPartners_Text_Buck_MyBigBrothersOneOfTheEliteFour
    GoTo FollowerPartners_Buck_IncreaseTimesTalked
    End

FollowerPartners_Buck_ItMightBeCoolBeingAGymLeaderOrEliteFour:
    Message FollowerPartners_Text_Buck_ItMightBeCoolBeingAGymLeaderOrEliteFour
    WaitButton
    CloseMessage
    ReleaseAll
    End

FollowerPartners_Buck_IncreaseTimesTalked:
    AddVar VAR_FOLLOWER_BUCK_TIMES_TALKED, 1
    WaitButton
    CloseMessage
    ReleaseAll
    End

FollowerPartners_Mira:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfGe VAR_FOLLOWER_MIRA_TIMES_TALKED, 2, FollowerPartners_Mira_PlayerDidYouGetToBeSoGood
    GoToIfEq VAR_FOLLOWER_MIRA_TIMES_TALKED, 1, FollowerPartners_Mira_ThisCaveItsSoEasyToGetConfusedHere
    BufferPlayerName 0
    Message FollowerPartners_Text_Mira_ILikeHelpfulPokemonMovesLikeGrowlAndMinimize
    GoTo FollowerPartners_Mira_IncreaseTimesTalked
    End

FollowerPartners_Mira_ThisCaveItsSoEasyToGetConfusedHere:
    Message FollowerPartners_Text_Mira_ThisCaveItsSoEasyToGetConfusedHere
    GoTo FollowerPartners_Mira_IncreaseTimesTalked
    End

FollowerPartners_Mira_PlayerDidYouGetToBeSoGood:
    BufferPlayerName 0
    Message FollowerPartners_Text_Mira_PlayerDidYouGetToBeSoGood
    WaitButton
    CloseMessage
    ReleaseAll
    End

FollowerPartners_Mira_IncreaseTimesTalked:
    AddVar VAR_FOLLOWER_MIRA_TIMES_TALKED, 1
    WaitButton
    CloseMessage
    ReleaseAll
    End
    End

FollowerPartners_Marley:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfGe VAR_FOLLOWER_MARLEY_TIMES_TALKED, 1, FollowerPartners_Marley_ThePokemonAmongFlowers
    BufferPlayerName 0
    Message FollowerPartners_Text_Marley_YoureVeryChatty
    GoTo FollowerPartners_Marley_IncreaseTimesTalked
    End

FollowerPartners_Marley_ThePokemonAmongFlowers:
    Message FollowerPartners_Text_Marley_ThePokemonAmongFlowers
    WaitButton
    CloseMessage
    ReleaseAll
    End

FollowerPartners_Marley_IncreaseTimesTalked:
    AddVar VAR_FOLLOWER_MARLEY_TIMES_TALKED, 1
    WaitButton
    CloseMessage
    ReleaseAll
    End

FollowerMon_Talk:
    LockAll
    FollowPokeFacePlayer
    GetFollowerPartySlot VAR_RESULT
    BufferPartyMonNickname 0, VAR_RESULT
    GetPartyMonSpecies VAR_RESULT, VAR_FOLLOWER_MON_SPECIES
    PlayCry VAR_FOLLOWER_MON_SPECIES
    GetFollowerMonStatus VAR_RESULT
    GoToIfNe VAR_RESULT, 0, FollowerMon_Talk_Status
    GetFollowerMonHPPercent VAR_RESULT
    GoToIfGe VAR_RESULT, 80, FollowerMon_Talk_VeryHigh
    GoToIfGe VAR_RESULT, 60, FollowerMon_Talk_High
    GoToIfGe VAR_RESULT, 40, FollowerMon_Talk_Medium
    GoToIfGe VAR_RESULT, 20, FollowerMon_Talk_Low
    GoTo FollowerMon_Talk_VeryLow

FollowerMon_Talk_Status:
    GoToIfEq VAR_RESULT, 1, FollowerMon_Talk_Sleep
    GoToIfEq VAR_RESULT, 2, FollowerMon_Talk_Poison
    GoToIfEq VAR_RESULT, 3, FollowerMon_Talk_Burn
    GoToIfEq VAR_RESULT, 4, FollowerMon_Talk_Frozen
    GoTo FollowerMon_Talk_Paralyzed

FollowerMon_Talk_Sleep:
    GetRandom VAR_RESULT, 4
    GoToIfEq VAR_RESULT, 0, FollowerMon_Talk_Sleep_0
    GoToIfEq VAR_RESULT, 1, FollowerMon_Talk_Sleep_1
    GoToIfEq VAR_RESULT, 2, FollowerMon_Talk_Sleep_2
    Message FollowerPartners_Text_Status_Sleep_3
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_Sleep_0:
    Message FollowerPartners_Text_Status_Sleep_0
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_Sleep_1:
    Message FollowerPartners_Text_Status_Sleep_1
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_Sleep_2:
    Message FollowerPartners_Text_Status_Sleep_2
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_Poison:
    Message FollowerPartners_Text_Status_Poison
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_Burn:
    Message FollowerPartners_Text_Status_Burn
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_Frozen:
    GetRandom VAR_RESULT, 3
    GoToIfEq VAR_RESULT, 0, FollowerMon_Talk_Frozen_0
    GoToIfEq VAR_RESULT, 1, FollowerMon_Talk_Frozen_1
    Message FollowerPartners_Text_Status_Frozen_2
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_Frozen_0:
    Message FollowerPartners_Text_Status_Frozen_0
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_Frozen_1:
    Message FollowerPartners_Text_Status_Frozen_1
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_Paralyzed:
    GetRandom VAR_RESULT, 3
    GoToIfEq VAR_RESULT, 0, FollowerMon_Talk_Paralyzed_0
    GoToIfEq VAR_RESULT, 1, FollowerMon_Talk_Paralyzed_1
    Message FollowerPartners_Text_Status_Paralyzed_2
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_Paralyzed_0:
    Message FollowerPartners_Text_Status_Paralyzed_0
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_Paralyzed_1:
    Message FollowerPartners_Text_Status_Paralyzed_1
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_VeryLow:
    GetRandom VAR_RESULT, 4
    GoToIfEq VAR_RESULT, 0, FollowerMon_Talk_VeryLow_0
    GoToIfEq VAR_RESULT, 1, FollowerMon_Talk_VeryLow_1
    GoToIfEq VAR_RESULT, 2, FollowerMon_Talk_VeryLow_2
    Message FollowerPartners_Text_VeryLow_3
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_VeryLow_0:
    Message FollowerPartners_Text_VeryLow_0
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_VeryLow_1:
    Message FollowerPartners_Text_VeryLow_1
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_VeryLow_2:
    Message FollowerPartners_Text_VeryLow_2
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_Low:
    GetRandom VAR_RESULT, 4
    GoToIfEq VAR_RESULT, 0, FollowerMon_Talk_Low_0
    GoToIfEq VAR_RESULT, 1, FollowerMon_Talk_Low_1
    GoToIfEq VAR_RESULT, 2, FollowerMon_Talk_Low_2
    Message FollowerPartners_Text_Low_3
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_Low_0:
    Message FollowerPartners_Text_Low_0
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_Low_1:
    Message FollowerPartners_Text_Low_1
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_Low_2:
    Message FollowerPartners_Text_Low_2
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_Medium:
    GetRandom VAR_RESULT, 4
    GoToIfEq VAR_RESULT, 0, FollowerMon_Talk_Medium_0
    GoToIfEq VAR_RESULT, 1, FollowerMon_Talk_Medium_1
    GoToIfEq VAR_RESULT, 2, FollowerMon_Talk_Medium_2
    Message FollowerPartners_Text_Medium_3
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_Medium_0:
    Message FollowerPartners_Text_Medium_0
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_Medium_1:
    Message FollowerPartners_Text_Medium_1
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_Medium_2:
    Message FollowerPartners_Text_Medium_2
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_High:
    GetRandom VAR_RESULT, 4
    GoToIfEq VAR_RESULT, 0, FollowerMon_Talk_High_0
    GoToIfEq VAR_RESULT, 1, FollowerMon_Talk_High_1
    GoToIfEq VAR_RESULT, 2, FollowerMon_Talk_High_2
    Message FollowerPartners_Text_High_3
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_High_0:
    Message FollowerPartners_Text_High_0
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_High_1:
    Message FollowerPartners_Text_High_1
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_High_2:
    Message FollowerPartners_Text_High_2
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_VeryHigh:
    GetRandom VAR_RESULT, 4
    GoToIfEq VAR_RESULT, 0, FollowerMon_Talk_VeryHigh_0
    GoToIfEq VAR_RESULT, 1, FollowerMon_Talk_VeryHigh_1
    GoToIfEq VAR_RESULT, 2, FollowerMon_Talk_VeryHigh_2
    Message FollowerPartners_Text_VeryHigh_3
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_VeryHigh_0:
    Message FollowerPartners_Text_VeryHigh_0
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_VeryHigh_1:
    Message FollowerPartners_Text_VeryHigh_1
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_VeryHigh_2:
    Message FollowerPartners_Text_VeryHigh_2
    GoTo FollowerMon_Talk_End

FollowerMon_Talk_End:
    WaitCry
    WaitButton
    CloseMessage
    ReleaseAll
    End

    .balign 4, 0
