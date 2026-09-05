#include "scrcmd_game_corner_prize.h"

#include <nitro.h>
#include <string.h>

#include "generated/items.h"

#include "field_script_context.h"
#include "inlines.h"

typedef struct GameCornerPrize {
    u16 item;
    u16 price;
} GameCornerPrize;

BOOL ScrCmd_GetGameCornerPrizeData(ScriptContext *ctx)
{
    u16 index = ScriptContext_GetVar(ctx);
    u16 *item = ScriptContext_GetVarPointer(ctx);
    u16 *price = ScriptContext_GetVarPointer(ctx);

    static const GameCornerPrize sGameCornerPrizeData[] = {
        { ITEM_TM58, 100 },
        { ITEM_TM32, 100 },
        { ITEM_TM33, 100 },
        { ITEM_TM16, 100 },
        { ITEM_TM44, 100 },
        { ITEM_TM68, 100 }
    };

    *item = sGameCornerPrizeData[index].item;
    *price = sGameCornerPrizeData[index].price;

    return FALSE;
}
