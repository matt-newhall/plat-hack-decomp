#include "constants/items.h"

// Number of berries a patch of each species holds. Patches never grow, drain or
// replant, so this is simply the amount handed over on the one harvest a patch
// ever gets. Indexed by BERRY_ID(), i.e. berryID - 1.
//
// A patch may override its species value; see sBerryInitTable in berry_init.h.
static const u16 sBerryYields[NUM_BERRIES + 1] = {
    [BERRY_ID(ORAN)] = 40,

    [BERRY_ID(CHERI)] = 30,
    [BERRY_ID(CHESTO)] = 30,
    [BERRY_ID(PECHA)] = 30,
    [BERRY_ID(RAWST)] = 30,
    [BERRY_ID(ASPEAR)] = 30,
    [BERRY_ID(LEPPA)] = 30,
    [BERRY_ID(PERSIM)] = 30,
    [BERRY_ID(LUM)] = 30,
    [BERRY_ID(SITRUS)] = 30,

    [BERRY_ID(FIGY)] = 20,
    [BERRY_ID(WIKI)] = 20,
    [BERRY_ID(MAGO)] = 20,
    [BERRY_ID(AGUAV)] = 20,
    [BERRY_ID(IAPAPA)] = 20,

    [BERRY_ID(ENIGMA)] = 3,

    [BERRY_ID(OCCA)] = 2,
    [BERRY_ID(KEBIA)] = 2,
    [BERRY_ID(SHUCA)] = 2,
    [BERRY_ID(COBA)] = 2,
    [BERRY_ID(PAYAPA)] = 2,
    [BERRY_ID(TANGA)] = 2,
    [BERRY_ID(COLBUR)] = 2,
    [BERRY_ID(LANSAT)] = 2,
    [BERRY_ID(MICLE)] = 2,
    [BERRY_ID(JABOCA)] = 2,
    [BERRY_ID(ROWAP)] = 2,
    [NUM_BERRIES] = 2, // Roseli sits outside the contiguous berry block; see BerryData_LoadDataByItemID

    [BERRY_ID(LIECHI)] = 1,
    [BERRY_ID(GANLON)] = 1,
    [BERRY_ID(SALAC)] = 1,
    [BERRY_ID(PETAYA)] = 1,
    [BERRY_ID(APICOT)] = 1,
    [BERRY_ID(STARF)] = 1,
    [BERRY_ID(CUSTAP)] = 1,

    // Not currently placed in any patch; values are placeholders.
    [BERRY_ID(RAZZ)] = 2,
    [BERRY_ID(BLUK)] = 2,
    [BERRY_ID(NANAB)] = 2,
    [BERRY_ID(WEPEAR)] = 2,
    [BERRY_ID(PINAP)] = 2,
    [BERRY_ID(POMEG)] = 2,
    [BERRY_ID(KELPSY)] = 2,
    [BERRY_ID(QUALOT)] = 2,
    [BERRY_ID(HONDEW)] = 2,
    [BERRY_ID(GREPA)] = 2,
    [BERRY_ID(TAMATO)] = 2,
    [BERRY_ID(CORNN)] = 2,
    [BERRY_ID(MAGOST)] = 2,
    [BERRY_ID(RABUTA)] = 2,
    [BERRY_ID(NOMEL)] = 2,
    [BERRY_ID(SPELON)] = 2,
    [BERRY_ID(PAMTRE)] = 2,
    [BERRY_ID(WATMEL)] = 2,
    [BERRY_ID(DURIN)] = 2,
    [BERRY_ID(BELUE)] = 2,
    [BERRY_ID(PASSHO)] = 2,
    [BERRY_ID(WACAN)] = 2,
    [BERRY_ID(RINDO)] = 2,
    [BERRY_ID(YACHE)] = 2,
    [BERRY_ID(CHOPLE)] = 2,
    [BERRY_ID(CHARTI)] = 2,
    [BERRY_ID(KASIB)] = 2,
    [BERRY_ID(HABAN)] = 2,
    [BERRY_ID(BABIRI)] = 2,
    [BERRY_ID(CHILAN)] = 2,
};
