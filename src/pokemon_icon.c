#include "pokemon_icon.h"

#include <nitro.h>
#include <string.h>

#include "constants/pokemon.h"
#include "constants/species.h"

#include "pokemon.h"

#include "res/pokemon/pl_poke_icon.naix"
#include "res/pokemon/species_icon_palettes.h"

static inline u32 IconTilesIndex(u32 icon)
{
    return icon + icon_00000_NCGR;
}

u32 BoxPokemon_IconSpriteIndex(const BoxPokemon *boxMon)
{
    BOOL reencrypt = BoxPokemon_EnterDecryptionContext((BoxPokemon *)boxMon);

    u32 species = BoxPokemon_GetValue((BoxPokemon *)boxMon, MON_DATA_SPECIES, NULL);
    BOOL isEgg = BoxPokemon_GetValue((BoxPokemon *)boxMon, MON_DATA_IS_EGG, NULL);
    u32 form = BoxPokemon_IconFormOffset((BoxPokemon *)boxMon);
    u32 index = PokeIconSpriteIndex(species, isEgg, form);

    BoxPokemon_ExitDecryptionContext((BoxPokemon *)boxMon, reencrypt);
    return index;
}

u32 Pokemon_IconSpriteIndex(Pokemon *mon)
{
    return BoxPokemon_IconSpriteIndex((const BoxPokemon *)Pokemon_GetBoxPokemon(mon));
}

u32 PokeIconSpriteIndex(u32 species, u32 isEgg, u32 form)
{
    if (isEgg == TRUE) {
        if (species == SPECIES_MANAPHY) {
            return IconTilesIndex(ICON_MANAPHY_EGG);
        }

        return IconTilesIndex(ICON_EGG);
    }

    form = Pokemon_SanitizeFormId(species, form);

    if (form != 0) {
        if (species == SPECIES_DEOXYS) {
            return IconTilesIndex(ICON_DEOXYS_ATTACK) + form - 1;
        }

        if (species == SPECIES_UNOWN) {
            return IconTilesIndex(ICON_UNOWN_B) + form - 1;
        }

        if (species == SPECIES_BURMY) {
            return IconTilesIndex(ICON_BURMY_SANDY) + form - 1;
        }

        if (species == SPECIES_WORMADAM) {
            return IconTilesIndex(ICON_WORMADAM_SANDY) + form - 1;
        }

        if (species == SPECIES_SHELLOS) {
            return IconTilesIndex(ICON_SHELLOS_EAST_SEA) + form - 1;
        }

        if (species == SPECIES_GASTRODON) {
            return IconTilesIndex(ICON_GASTRODON_EAST_SEA) + form - 1;
        }

        if (species == SPECIES_GIRATINA) {
            return IconTilesIndex(ICON_GIRATINA_ORIGIN) + form - 1;
        }

        if (species == SPECIES_SHAYMIN) {
            return IconTilesIndex(ICON_SHAYMIN_SKY) + form - 1;
        }

        if (species == SPECIES_ROTOM) {
            return IconTilesIndex(ICON_ROTOM_HEAT) + form - 1;
        }

        if (species == SPECIES_LUCARIO) {
            return IconTilesIndex(ICON_LUCARIO_MEGA) + form - 1;
        }

        if (species == SPECIES_TYRANITAR) {
            return IconTilesIndex(ICON_TYRANITAR_MEGA) + form - 1;
        }

        if (species == SPECIES_VENUSAUR) {
            return IconTilesIndex(ICON_VENUSAUR_MEGA) + form - 1;
        }

        if (species == SPECIES_BLASTOISE) {
            return IconTilesIndex(ICON_BLASTOISE_MEGA) + form - 1;
        }

        if (species == SPECIES_BEEDRILL) {
            return IconTilesIndex(ICON_BEEDRILL_MEGA) + form - 1;
        }

        if (species == SPECIES_PIDGEOT) {
            return IconTilesIndex(ICON_PIDGEOT_MEGA) + form - 1;
        }

        if (species == SPECIES_SLOWBRO) {
            return IconTilesIndex(ICON_SLOWBRO_MEGA) + form - 1;
        }

        if (species == SPECIES_GENGAR) {
            return IconTilesIndex(ICON_GENGAR_MEGA) + form - 1;
        }

        if (species == SPECIES_PINSIR) {
            return IconTilesIndex(ICON_PINSIR_MEGA) + form - 1;
        }

        if (species == SPECIES_AMPHAROS) {
            return IconTilesIndex(ICON_AMPHAROS_MEGA) + form - 1;
        }

        if (species == SPECIES_STEELIX) {
            return IconTilesIndex(ICON_STEELIX_MEGA) + form - 1;
        }

        if (species == SPECIES_SCIZOR) {
            return IconTilesIndex(ICON_SCIZOR_MEGA) + form - 1;
        }

        if (species == SPECIES_HERACROSS) {
            return IconTilesIndex(ICON_HERACROSS_MEGA) + form - 1;
        }

        if (species == SPECIES_HOUNDOOM) {
            return IconTilesIndex(ICON_HOUNDOOM_MEGA) + form - 1;
        }

        if (species == SPECIES_SCEPTILE) {
            return IconTilesIndex(ICON_SCEPTILE_MEGA) + form - 1;
        }

        if (species == SPECIES_BLAZIKEN) {
            return IconTilesIndex(ICON_BLAZIKEN_MEGA) + form - 1;
        }

        if (species == SPECIES_SWAMPERT) {
            return IconTilesIndex(ICON_SWAMPERT_MEGA) + form - 1;
        }

        if (species == SPECIES_SABLEYE) {
            return IconTilesIndex(ICON_SABLEYE_MEGA) + form - 1;
        }

        if (species == SPECIES_MAWILE) {
            return IconTilesIndex(ICON_MAWILE_MEGA) + form - 1;
        }

        if (species == SPECIES_AGGRON) {
            return IconTilesIndex(ICON_AGGRON_MEGA) + form - 1;
        }

        if (species == SPECIES_MEDICHAM) {
            return IconTilesIndex(ICON_MEDICHAM_MEGA) + form - 1;
        }

        if (species == SPECIES_MANECTRIC) {
            return IconTilesIndex(ICON_MANECTRIC_MEGA) + form - 1;
        }

        if (species == SPECIES_BANETTE) {
            return IconTilesIndex(ICON_BANETTE_MEGA) + form - 1;
        }

        if (species == SPECIES_ALAKAZAM) {
            return IconTilesIndex(ICON_ALAKAZAM_MEGA) + form - 1;
        }

        if (species == SPECIES_GYARADOS) {
            return IconTilesIndex(ICON_GYARADOS_MEGA) + form - 1;
        }

        if (species == SPECIES_ABSOL) {
            return IconTilesIndex(ICON_ABSOL_MEGA) + form - 1;
        }

        if (species == SPECIES_GLALIE) {
            return IconTilesIndex(ICON_GLALIE_MEGA) + form - 1;
        }

        if (species == SPECIES_SALAMENCE) {
            return IconTilesIndex(ICON_SALAMENCE_MEGA) + form - 1;
        }

        if (species == SPECIES_LOPUNNY) {
            return IconTilesIndex(ICON_LOPUNNY_MEGA) + form - 1;
        }

        if (species == SPECIES_GARCHOMP) {
            return IconTilesIndex(ICON_GARCHOMP_MEGA) + form - 1;
        }

        if (species == SPECIES_ABOMASNOW) {
            return IconTilesIndex(ICON_ABOMASNOW_MEGA) + form - 1;
        }

        if (species == SPECIES_GALLADE) {
            return IconTilesIndex(ICON_GALLADE_MEGA) + form - 1;
        }
    }

    if (species > NATIONAL_DEX_COUNT) {
        species = SPECIES_NONE;
    }

    return IconTilesIndex(species);
}

u16 BoxPokemon_IconFormOffset(const BoxPokemon *boxMon)
{
    u32 speciesOrEgg = BoxPokemon_GetValue((BoxPokemon *)boxMon, MON_DATA_SPECIES_OR_EGG, NULL);

    switch (speciesOrEgg) {
    case SPECIES_UNOWN:
        return BoxPokemon_GetForm((BoxPokemon *)boxMon);
    case SPECIES_DEOXYS:
    case SPECIES_BURMY:
    case SPECIES_WORMADAM:
    case SPECIES_SHELLOS:
    case SPECIES_GASTRODON:
    case SPECIES_GIRATINA:
    case SPECIES_SHAYMIN:
    case SPECIES_ROTOM:
    case SPECIES_TYRANITAR:
    case SPECIES_LUCARIO:
    case SPECIES_VENUSAUR:
    case SPECIES_BLASTOISE:
    case SPECIES_BEEDRILL:
    case SPECIES_PIDGEOT:
    case SPECIES_SLOWBRO:
    case SPECIES_GENGAR:
    case SPECIES_PINSIR:
    case SPECIES_AMPHAROS:
    case SPECIES_STEELIX:
    case SPECIES_SCIZOR:
    case SPECIES_HERACROSS:
    case SPECIES_HOUNDOOM:
    case SPECIES_SCEPTILE:
    case SPECIES_BLAZIKEN:
    case SPECIES_SWAMPERT:
    case SPECIES_SABLEYE:
    case SPECIES_MAWILE:
    case SPECIES_AGGRON:
    case SPECIES_MEDICHAM:
    case SPECIES_MANECTRIC:
    case SPECIES_BANETTE:
    case SPECIES_ALAKAZAM:
    case SPECIES_GYARADOS:
    case SPECIES_ABSOL:
    case SPECIES_GLALIE:
    case SPECIES_SALAMENCE:
    case SPECIES_LOPUNNY:
    case SPECIES_GARCHOMP:
    case SPECIES_ABOMASNOW:
    case SPECIES_GALLADE:
        return BoxPokemon_GetValue((BoxPokemon *)boxMon, MON_DATA_FORM, NULL);
    }

    return 0;
}

const u8 PokeIconPaletteIndex(u32 species, u32 form, u32 isEgg)
{
    if (isEgg == TRUE) {
        if (species == SPECIES_MANAPHY) {
            species = ICON_MANAPHY_EGG;
        } else {
            species = ICON_EGG;
        }
    } else if (species > NATIONAL_DEX_COUNT) {
        species = SPECIES_NONE;
    } else if (form != 0) {
        if (species == SPECIES_DEOXYS) {
            species = ICON_DEOXYS_ATTACK + form - 1;
        } else if (species == SPECIES_UNOWN) {
            species = ICON_UNOWN_A + form - 1;
        } else if (species == SPECIES_BURMY) {
            species = ICON_BURMY_SANDY + form - 1;
        } else if (species == SPECIES_WORMADAM) {
            species = ICON_WORMADAM_SANDY + form - 1;
        } else if (species == SPECIES_SHELLOS) {
            species = ICON_SHELLOS_EAST_SEA + form - 1;
        } else if (species == SPECIES_GASTRODON) {
            species = ICON_GASTRODON_EAST_SEA + form - 1;
        } else if (species == SPECIES_GIRATINA) {
            species = ICON_GIRATINA_ORIGIN + form - 1;
        } else if (species == SPECIES_SHAYMIN) {
            species = ICON_SHAYMIN_SKY + form - 1;
        } else if (species == SPECIES_ROTOM) {
            species = ICON_ROTOM_HEAT + form - 1;
        } else if (species == SPECIES_LUCARIO) {
            species = ICON_LUCARIO_MEGA + form - 1;
        } else if (species == SPECIES_TYRANITAR) {
            species = ICON_TYRANITAR_MEGA + form - 1;
        } else if (species == SPECIES_VENUSAUR) {
            species = ICON_VENUSAUR_MEGA + form - 1;
        } else if (species == SPECIES_BLASTOISE) {
            species = ICON_BLASTOISE_MEGA + form - 1;
        } else if (species == SPECIES_BEEDRILL) {
            species = ICON_BEEDRILL_MEGA + form - 1;
        } else if (species == SPECIES_PIDGEOT) {
            species = ICON_PIDGEOT_MEGA + form - 1;
        } else if (species == SPECIES_SLOWBRO) {
            species = ICON_SLOWBRO_MEGA + form - 1;
        } else if (species == SPECIES_GENGAR) {
            species = ICON_GENGAR_MEGA + form - 1;
        } else if (species == SPECIES_PINSIR) {
            species = ICON_PINSIR_MEGA + form - 1;
        } else if (species == SPECIES_AMPHAROS) {
            species = ICON_AMPHAROS_MEGA + form - 1;
        } else if (species == SPECIES_STEELIX) {
            species = ICON_STEELIX_MEGA + form - 1;
        } else if (species == SPECIES_SCIZOR) {
            species = ICON_SCIZOR_MEGA + form - 1;
        } else if (species == SPECIES_HERACROSS) {
            species = ICON_HERACROSS_MEGA + form - 1;
        } else if (species == SPECIES_HOUNDOOM) {
            species = ICON_HOUNDOOM_MEGA + form - 1;
        } else if (species == SPECIES_SCEPTILE) {
            species = ICON_SCEPTILE_MEGA + form - 1;
        } else if (species == SPECIES_BLAZIKEN) {
            species = ICON_BLAZIKEN_MEGA + form - 1;
        } else if (species == SPECIES_SWAMPERT) {
            species = ICON_SWAMPERT_MEGA + form - 1;
        } else if (species == SPECIES_SABLEYE) {
            species = ICON_SABLEYE_MEGA + form - 1;
        } else if (species == SPECIES_MAWILE) {
            species = ICON_MAWILE_MEGA + form - 1;
        } else if (species == SPECIES_AGGRON) {
            species = ICON_AGGRON_MEGA + form - 1;
        } else if (species == SPECIES_MEDICHAM) {
            species = ICON_MEDICHAM_MEGA + form - 1;
        } else if (species == SPECIES_MANECTRIC) {
            species = ICON_MANECTRIC_MEGA + form - 1;
        } else if (species == SPECIES_BANETTE) {
            species = ICON_BANETTE_MEGA + form - 1;
        } else if (species == SPECIES_ALAKAZAM) {
            species = ICON_ALAKAZAM_MEGA + form - 1;
        } else if (species == SPECIES_GYARADOS) {
            species = ICON_GYARADOS_MEGA + form - 1;
        } else if (species == SPECIES_ABSOL) {
            species = ICON_ABSOL_MEGA + form - 1;
        } else if (species == SPECIES_GLALIE) {
            species = ICON_GLALIE_MEGA + form - 1;
        } else if (species == SPECIES_SALAMENCE) {
            species = ICON_SALAMENCE_MEGA + form - 1;
        } else if (species == SPECIES_LOPUNNY) {
            species = ICON_LOPUNNY_MEGA + form - 1;
        } else if (species == SPECIES_GARCHOMP) {
            species = ICON_GARCHOMP_MEGA + form - 1;
        } else if (species == SPECIES_ABOMASNOW) {
            species = ICON_ABOMASNOW_MEGA + form - 1;
        } else if (species == SPECIES_GALLADE) {
            species = ICON_GALLADE_MEGA + form - 1;
        }
    }

    return sPokemonIconPaletteIndex[species];
}

const u8 BoxPokemon_IconPaletteIndex(const BoxPokemon *boxMon)
{
    BOOL reencrypt = BoxPokemon_EnterDecryptionContext((BoxPokemon *)boxMon);

    u32 form = BoxPokemon_IconFormOffset(boxMon);
    u32 species = BoxPokemon_GetValue((BoxPokemon *)boxMon, MON_DATA_SPECIES, NULL);
    u32 isEgg = BoxPokemon_GetValue((BoxPokemon *)boxMon, MON_DATA_IS_EGG, NULL);

    BoxPokemon_ExitDecryptionContext((BoxPokemon *)boxMon, reencrypt);

    return PokeIconPaletteIndex(species, form, isEgg);
}

const u8 Pokemon_IconPaletteIndex(Pokemon *mon)
{
    return BoxPokemon_IconPaletteIndex((const BoxPokemon *)Pokemon_GetBoxPokemon(mon));
}

u32 PokeIconPalettesFileIndex(void)
{
    return shared_pals_NCLR;
}

u32 PokeIconCellsFileIndex(void)
{
    return shared_cell_NCER;
}

u32 PokeIcon32KCellsFileIndex(void)
{
    return shared_cell_32k_NCER;
}

u32 PokeIcon64KCellsFileIndex(void)
{
    return shared_cell_64k_NCER;
}

u32 PokeIconAnimationFileIndex(void)
{
    return shared_anim_NANR;
}

u32 PokeIcon32KAnimationFileIndex(void)
{
    return shared_anim_32k_NANR;
}

u32 PokeIcon64KAnimationFileIndex(void)
{
    return shared_anim_64k_NANR;
}
