#include "macros/scrcmd.inc"
#include "res/text/bank/flower_shop.h"


    ScriptEntry FlowerShop_PokemonBreederF
    ScriptEntry FlowerShop_Lass
    ScriptEntry FlowerShop_Beauty
    ScriptEntryEnd

FlowerShop_PokemonBreederF:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet FLAG_OBTAINED_FLOWER_SHOP_BERRY, FlowerShop_LetYourPokemonHoldThatBerry
    Message FlowerShop_Text_BerriesAreRareNowPleaseTakeThisOne
    SetVar VAR_0x8004, ITEM_ORAN_BERRY
    SetVar VAR_0x8005, 1
    GoToIfCannotFitItem VAR_0x8004, VAR_0x8005, VAR_RESULT, FlowerShop_BagIsFull
    SetFlag FLAG_OBTAINED_FLOWER_SHOP_BERRY
    Common_GiveItemQuantityNoLineFeed
    CloseMessage
    ReleaseAll
    End

FlowerShop_LetYourPokemonHoldThatBerry:
    Message FlowerShop_Text_LetYourPokemonHoldThatBerry
    WaitButton
    CloseMessage
    ReleaseAll
    End

FlowerShop_BagIsFull:
    Common_MessageBagIsFull
    CloseMessage
    ReleaseAll
    End

FlowerShop_Lass:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message FlowerShop_Text_TheSoilInSinnohIsTooDryToPlantNewBerries
    WaitButton
    CloseMessage
    ReleaseAll
    End

FlowerShop_Beauty:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    ShowAccessoryShop
    ReleaseAll
    End

    .balign 4, 0
