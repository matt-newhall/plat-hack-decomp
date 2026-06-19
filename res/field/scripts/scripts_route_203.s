#include "macros/scrcmd.inc"
#include "res/text/bank/route_203.h"
#include "res/field/events/events_route_203.h"


    ScriptEntry Route203_Lass
    ScriptEntry Route203_ArrowSignpostJubilifeCity
    ScriptEntry Route203_ArrowSignpostOreburghCity
    ScriptEntry Route203_TrainerTipsSignpostEast
    ScriptEntry Route203_TrainerTipsSignpostWest
    ScriptEntryEnd

Route203_Lass:
    NPCMessage Route203_Text_YourFavoritePokemonShouldBePlacedAtTheTop
    End

Route203_ArrowSignpostJubilifeCity:
    ShowArrowSign Route203_Text_Rt203JubilifeCity
    End

Route203_ArrowSignpostOreburghCity:
    ShowArrowSign Route203_Text_Rt203OreburghCity
    End

Route203_TrainerTipsSignpostEast:
    ShowScrollingSign Route203_Text_TrainerTipsIfAPokemonIsAboutToEvolveItCanBeInstantlyStopped
    End

Route203_TrainerTipsSignpostWest:
    ShowScrollingSign Route203_Text_TrainerTipsPokemonMovesUseEnergyCalledPowerPoints
    End

    .balign 4, 0
