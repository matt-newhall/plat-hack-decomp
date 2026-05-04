# Removals and Ignored Changes

If anyone in this repository is looking to take over updating the rest of these changes, here is the TL;DR of what is missing. I only made all of the changes required to form the engine base for Pokemon Tempered Platinum, so any moves/abilities/mechanics that we were planning to remove, some visual bugs and an assortment of other random changes are not updated. Thankfully I've (hopefully reasonably) documented all of these changes if anyone wants to have a crack at them.

## Removed Moves

- Conversion
- Conversion2
- Assist
- Heal Block
- Healing Wish
- Lunar Dance
- Copycat
- Me First
- Sheer Cold
- Future Sight
- Doom Desire
- False Swipe
- Mud Sport
- Water Sport
- Mirror Move
- Acupressure
- Thief
- Covet

### Change List

Heal Block
- Affected Pokémon can no longer be healed by Black Sludge, Leftovers, or Shell Bell. Affected Pokémon will no longer consume held HP-restoring Berries or Berry Juice. If an affected Pokémon consumes an HP-restoring Berry via Fling, Bug Bite, or Pluck, it will not have its HP restored.
- Affected Pokémon with the Ability Dry Skin or Water Absorb will take no damage from Water-type moves, but will not be healed by them either. Affected Pokémon with the Ability Volt Absorb will take no damage from Electric-type moves, but will not be healed by them either. Affected Pokémon with the Ability Dry Skin or Rain Dish are prevented from healing during rain. Affected Pokémon with the Ability Ice Body are prevented from healing during hail, but are not damaged by it either. Affected Pokémon with the ability Poison Heal will not be healed or damaged if they are poisoned.

Conversion
- Conversion can now be used on Curse, which is now a Ghost-type move.
- Conversion now changes the user's current type to match the type of the move the user has in its first move slot (even if that move cannot be selected in battle).

Conversion 2
- Conversion 2 now targets an adjacent Pokémon and bypasses accuracy checks to always hit, unless the target is in the semi-invulnerable turn of a move such as Dig or Fly. It will randomly change the user's current type to a type that either resists or is immune to the type of the move last used by the target, including status moves. Conversion 2 will not change the user to any of its current types. In an Inverse Battle, Conversion 2 considers resistances based on inverse type matchups.
- If the last move the target used was a move that calls another move (such as Metronome), the type of the called move will be considered. If the last move the target used is a move that changes type (such as Hidden Power), the type it was changed to will be considered. If the last move the target used had its type changed, such as with Normalize, the type it changes to will be considered. Conversion 2 will fail if the last move the target used was Struggle, typeless Revelation Dance, or if there is no type that resists that move (i.e., a Normal-type move in an Inverse Battle).
- Conversion 2 is not affected by Substitute, Protect, Detect

Absorb, Drain Punch, Giga Drain, Leech Life, Mega Drain
- Cannot be used if the user is under the effects of Heal Block

Healing Wish
- The receiving Pokémon is now sent out at the end of the turn rather than immediately sending it out.
- If the Pokémon sent out to replace the user already has full health and no status condition, Healing Wish's effect will not activate until a Pokémon is placed in that position (either by switching in or using Ally Switch). A pending Healing Wish will not activate if a Pokémon already in that position loses HP or gains a status condition; it will only activate when a new Pokémon is placed in that position. Each position can only have a single instance of Healing Wish pending (using it multiple times does not stack). Healing Wish can stack with Lunar Dance.

Lunar Dance
- The receiving Pokémon is now sent out at the end of the turn after all other Pokémon have moved.

Future Sight
- Future Sight now calculates its damage when it hits rather than when it is selected. Future Sight uses the user's Special Attack and the hit Pokémon's Special Defense at the time damage is dealt.
- It now inflicts damage as a Psychic-type move; therefore, it is affected by type effectiveness (so cannot affect Dark-type Pokémon), can receive STAB, and will not necessarily hit through Wonder Guard. If the user is on the field and has Normalize when Future Sight hits, it hits as a Normal-type move respectively (regardless of whether this was the case when the move was used).
- Future Sight can now land a critical hit.
- If the user is not on the field when Future Sight hits, its Ability and held item are not applied.
- In battles with multiple opponents, Future Sight may now target a slot without an active Pokémon. (If a Pokémon occupies the selected slot by the time the attack is due, Future Sight will attack as intended.) If there is no target at the targeted slot by the time the attack is due, Future Sight will still fail without further notice.
- A Pokémon can now endure Future Sight with Endure or Sturdy, in addition to the Focus Sash and Focus Band. Future Sight disappears with no message if it would hit the Pokémon that used the move.

Doom Desire
- Doom Desire now calculates its damage when it hits rather than when it is selected. Doom Desire uses the user's Special Attack and the hit Pokémon's Special Defense at the time damage is dealt.
- It now inflicts damage as a Steel-type move; therefore, it is affected by type effectiveness, can receive STAB, and will not necessarily hit through Wonder Guard. If the user has Normalize when Doom Desire hits, it hits as a Normal-type move (regardless of whether this was the case when the move was used). Doom Desire can now land a critical hit.
- In battles with multiple opponents, Doom Desire may now target a slot without an active Pokémon. (If a Pokémon occupies the selected slot by the time the attack is due, Doom Desire will attack as intended.) If there is no target at the targeted slot by the time the attack is due, Doom Desire will still fail without further notice.
- A Pokémon can now endure Doom Desire with Endure or Sturdy, in addition to the Focus Sash and Focus Band. Doom Desire disappears with no message if it would hit the Pokémon that used the move.

Mud Sport, Water Sport
- Now active for five turns, even if the user switches out
- Reduces damage of Electric/Fire-type moves by 67% on both sides.

Mirror Move
- Mirror Move now allows the user to simply select a Pokemon on the field to replicates their move, and no longer has to be the last move that targeted the user.

Covet, Thief
- If the user faints when using an item-stealing move (such as due to the target's Rough Skin), it cannot steal the target's held item. If this move causes a Pokémon with the Sticky Hold Ability to faint, it can now steal its held item.

## Removed Mechanics

Anything in this section was not added into the engine for a specific reason - I'll list the reasons alongside them.

**Destiny Bond**

A Pokémon defeated by this move will now faint after the Pokémon that used Destiny Bond, meaning that if Destiny Bond is used by the last Pokémon on a player's team, and the last Pokémon on the opposing team makes it faint, the opposing player will win. *PvP only - hack is for Nuzlockes where a wipe is a wipe*

Destiny Bond will always fail if it was successfully executed on the previous turn. *Mechanic removed in rom hack*

**Encore**

If a Pokémon is forced to use Acupressure on a turn it chose another move, it will always target the user, not an ally. *Removed Acupressure*

**Endure**

Endure can now protect against the end-of-turn effects of Future Sight and Doom Desire. *Removed Future Sight & Doom Desire*

**Follow Me**

Follow Me does not redirect Future Sight or Doom Desire. *Removed Future Sight & Doom Desire*

**Haze**

The effects of Dire Hit are once again unaffected by Haze. *Removed Dire Hit/made it unusable*

**Knock Off**

Wild Pokémon cannot remove held items of the player's Pokémon. *Rom hack mechanic is such that items are always removed*

**Roost**

If a Flying-type Pokémon successfully uses Roost, it will now lose its Flying type until the end of the turn *Only relevant for mono-Flying Pokemon, of which there are none*

If a Pokémon is ungrounded only due to its Flying type, successfully using Roost will make it grounded until the end of the turn. *No practical gen IV effects, e.g. Rototiller, Terrain, etc*

**Spit Up, Stockpile**

For each Stockpile that successfully changed a defensive stat, that stat will drop by two stages if the Pokémon has Simple at the time of using Swallow. *Removed Simple*

The Stockpile removal is now shown as a stat change. *Visual change only*

**Switcheroo, Trick, Covet, Thief**

No longer switch a Trainer's Pokémon's items permanently; however, items switched in wild battles are permanently switched. *Rom hack mechanic is such that items are always removed*
