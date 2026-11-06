# Removals and Ignored Changes

If anyone in this repository is looking to take over updating the rest of these changes, here is the TL;DR of what is missing. I only made all of the changes required to form the engine base for Pokemon Tempered Platinum, so any changes to specific moves/abilities/items for the ROM are currently unimplemented. Thankfully I've (hopefully reasonably) documented all of these changes if anyone wants to have a crack at them.

## Removed Mechanics

Anything in this section was not added into the engine for a specific reason - I'll list the reasons alongside them.

**Destiny Bond**

A Pokémon defeated by this move will now faint after the Pokémon that used Destiny Bond, meaning that if Destiny Bond is used by the last Pokémon on a player's team, and the last Pokémon on the opposing team makes it faint, the opposing player will win. *PvP only - hack is for Nuzlockes where a wipe is a wipe*

Destiny Bond will always fail if it was successfully executed on the previous turn. *Mechanic removed in rom hack*

**Haze**

The effects of Dire Hit are once again unaffected by Haze. *Removed Dire Hit/made it unusable*

**Knock Off**

Wild Pokémon cannot remove held items of the player's Pokémon. *Rom hack mechanic is such that items are always removed*

**Switcheroo, Trick, Covet, Thief**

No longer switch a Trainer's Pokémon's items permanently; however, items switched in wild battles are permanently switched. *Rom hack mechanic is such that items are always removed*
