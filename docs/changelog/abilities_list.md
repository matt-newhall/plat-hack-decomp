# Implemented changes

Herein are all of the changes that have been made to moves as part of the base engine for Pokemon Tempered Platinum. I have attempted to sort these into fields to indicate what effect these have on gameplay.

## Major Changes

Arena Trap ✅
- Ghost-type Pokémon who are normally grounded are now immune to Arena Trap.

Heatproof ✅
- Halves the damage done from the burn status ailment, from 1⁄16 to 1⁄32 of the Pokémon's maximum HP.

Inner Focus, Oblivious, Own Tempo, Scrappy ✅
- Blocks Intimidate

Lightning Rod, Storm Drain ✅
- Along with its previous effects, gives the Pokémon immunity to all Electric-type and Water-type moves respectively, and raises the Pokémon's Special Attack by one stage whenever it is hit by an Electric-type or Water-type move. If the Pokémon is protected from the move, its Special Attack will not increase.
- A Ground-type Pokémon will now activate Lightning Rod and boost its Special Attack.
- Lightning Rod can now redirect Electric-type Hidden Power, Judgment, and Natural Gift.

Magnet Pull ✅
- Steel-type Pokémon are now unaffected by Magnet Pull if they have Ghost as another type.

Normalize ✅
- Normal-type moves used by the Pokémon with this Ability now receive a 20% power boost, except moves that cannot be affected by Normalize. This boost applies to both moves that are originally Normal-type and moves that become Normal-type due to Normalize.
- Hidden Power, Weather Ball, Natural Gift, Judgment, and Techno Blast are not affected.

Oblivious ✅
- Prevents the Pokémon from being afflicted by Taunt.
- If the Pokémon with this Ability is infatuated and is holding a Mental Herb, the Mental Herb will be consumed before Oblivious cures the Pokémon of infatuation.
- If the Pokémon is holding a Mental Herb, it will be consumed before Oblivious cures the Pokémon of the Taunt.
- If a taunted Pokémon gains this Ability in battle (such as from Skill Swap), it will shake off the taunt. If a Pokémon with Oblivious is taunted by a Pokémon with an Ability like Mold Breaker, the taunting will take effect, but it will then be cured once the Pokémon regains Oblivious.

Shadow Tag ✅
- Ghost-type Pokémon are now immune to Shadow Tag.

Stench ✅
- Has a 10% chance of making the target flinch when hit by a damaging move used by the Pokémon with this Ability.
- Does not stack with King's Rock or Razor Fang, nor does it stack with moves that already have a chance to flinch.
- Each strike of a multistrike move has an independent chance of causing the target to flinch.

Sticky Hold ✅
- If the Pokémon is knocked out by Knock Off, Sticky Hold does not protect the held item.

Sturdy ✅
- In addition to Sturdy's previous effect, Sturdy now works like a Focus Sash, causing the Pokémon to have 1 HP remaining if another Pokémon's attack or confusion damage would have brought it from full health to 0 HP.
- Sturdy will activate as long as a Pokémon has full HP before the attack, and therefore it can activate multiple times if the Pokémon is brought back to full health, or if the Pokémon has a maximum of 1 HP.
- If a Pokémon with Sturdy is holding a Focus Sash, Sturdy will activate first.
- A Pokémon with Mold Breaker will ignore Sturdy.
- Destiny Bond and Perish Song will not cause Sturdy to activate.
- When a multistrike move hits a Pokémon with Sturdy, Sturdy's effect can only activate for hits while the user has full HP.

Wonder Guard ✅
- Beat Up & Fire Fang no longer bypass Wonder Guard. More specifically, Beat Up now deals Dark-type damage.

## Minor Differences

Color Change ✅
- Now activates after the last hit of a multistrike move.

Download ✅
- Now takes into account the defensive stats of opponents behind a substitute.

Effect Spore ✅
- Grass-type Pokémon are now immune to Effect Spore.
- When a Pokémon with this Ability is hit by a move that makes contact, there is a 9% chance of poison, 10% chance of paralysis, and 11% chance of sleep.

Gluttony ✅
- Pinch berries, such as the Figy Berry and Mago Berry, are now eaten at 25% HP or less instead of being eaten at 50% HP or less, so are now affected by Gluttony.

Guts ✅
- Attack boost no longer activates if a Pokémon is frozen and uses a move that thaws it out, such as Flame Wheel or Flare Blitz.

Illuminate, Keen Eye ✅
- Ignores the target's evasion stages.
- Prevents other Pokemon from lowering the accuracy stat stage of the Pokemon with this ability.

Pressure ✅
- Pressure increases the PP consumption of an opponent's Imprison and Snatch even though those are self-targeting moves; in Snatch's case the additional PP is consumed even if Snatch fails or snatches a move from a Pokémon other than the one with Pressure.
- Pressure now only affects opponents' moves, not allies.

Serene Grace ✅
- Boosts the 10% flinch chance due to King's Rock or Razor Fang to 20%.

Soundproof ✅
- Pokémon with Soundproof can now be affected by Heal Bell.
- Pokémon on the field with Soundproof cannot be affected by Heal Bell (inactive Pokémon can be affected by Heal Bell even if they have Soundproof).
- Pokémon with Soundproof are no longer immune to their own sound-based moves.
- Author's note: this effectively translates to 'Heal Bell can now be used by Soundproof Pokémon to heal status, and using it will heal Pokémon in your party that also have the Soundproof ability, but will fail to heal ally Pokémon with Soundproof.'

Stall ✅
- If multiple Pokémon with Stall or that are holding a Lagging Tail or Full Incense use moves with the same priority, the Pokémon move relatively according to Speed (the order is reversed during Trick Room).

Synchronize ✅
- When a Pokémon with Synchronize is badly poisoned by another Pokémon, that Pokémon will now be inflicted with the bad poison condition, rather than the regular poison condition.
- If used by a burned/paralyzed/poisoned/badly poisoned Pokémon targeting a Pokémon with Synchronize, Syncronize now activates before Psycho Shift cures the user of its status condition. Therefore, Synchronize will fail to inflict the status condition anew in such a case.
- If multiple Pokémon receive a status from the same move, Synchronize now gets an opportunity to activate for any Pokémon that has it, regardless of what order they received the status in.
- Toxic Spikes do not activate this Ability, even if another Pokémon forced the Pokémon with this Ability to switch in by using a move like Roar or Dragon Tail.

## Incredibly Minor / Flavour Text

Air Lock, Cloud Nine ✅
- When a Pokémon with a weather-nullifying ability is brought out, the message "The effects of weather disappeared." will be displayed.

Anger Point ✅
- No longer activates if the Pokémon's substitute is hit.

Anticipation ✅
- The moves Selfdestruct and Explosion are now treated like all other Normal-type moves and thus no longer trigger Anticipation.
- Counter, Metal Burst, and Mirror Coat are counted as attacking moves of their types, so can trigger Anticipation.
- No longer factors in the effects of Scrappy, Normalize, or Gravity on type matchups when determining if it should display a trigger message.
- Hidden Power is now treated as its effective type rather than Normal-type.

Flash Fire ✅
- Now functional even if the user is frozen. The Pokémon will not be thawed out, however.

Flower Gift ✅
- If a Pokémon transforms into Cherrim, the Pokémon will remain in the same form as the target Cherrim, regardless of the weather.
- If Cherrim loses Flower Gift or Flower Gift is suppressed (such as by Gastro Acid), it will revert to its Overcast Form.

Flower Gift, Forecast, Trace ✅
- Role Play now fails if the target has any of these abilities.

Forecast ✅
- If a Pokémon transforms into Castform, the Pokémon will remain in the same form as the target Castform, regardless of the weather.
- If Castform loses Forecast or Forecast is suppressed with Gastro Acid, it will revert to its normal form and not be able to change form. If Castform regains Forecast, it will change form to match the current weather, unless it would be in its normal form in the current weather.

Huge Power, Hustle, Pure Power, Rivalry ✅
- No longer affects confusion damage.

Immunity, Insomnia, Limber, Magma Armor, Vital Spirit, Water Veil ✅
- When a statused Pokemon with the relevant Ability enters battle, it will be cured of its status.
- If a statused Pokemon (with the relevant ability & status pair) has this Ability as its original Ability but not its current Ability, it will remain statused when switched out.
- If a statused Pokemon (with the relevant ability & status pair) has this Ability, and is holding a Berry that would restore this status, the Berry will be eaten and cure the Pokémon of the status before the Ability has a chance to activate.

Klutz ✅
- Prevents the Pokémon from using Fling.
- If a Pokémon with Klutz uses Bug Bite or Pluck, it will now receive the effects of a consumed held Berry.
- All effects of the Iron Ball are now negated by Klutz. However, Klutz still does not negate the Speed drop from the Macho Brace and Power items.
- Klutz cannot prevent the form-changing effects of items, but will still negate the other effects of those items (e.g. if a Giratina holding a Griseous Orb has Klutz, it will remain in its Origin Forme, but will not receive the 20% boost in the power of Dragon- and Ghost-type moves).

Leaf Guard ✅
- Rest will now fail if used by a Pokémon with Leaf Guard during harsh sunlight.

Magic Guard ✅
- No longer grants immunity to being fully paralyzed.
- No longer prevents poisoning from Toxic Spikes (but it still prevents poison damage).

Minus, Plus ✅
- When a Pokémon with Plus or Minus enters a battle and has an ally with either Plus or Minus (instead of specifically requiring the opposing ability), the Special Attack stat of the Pokémon is increased by 50%.

Mold Breaker ✅
- If a Pokémon with Mold Breaker forces a Pokémon to switch in by using a move that switches the target out (such as Roar or Whirlwind), ignorable Abilities are ignored when applying entry hazards.
- For example, a Pokémon with Levitate switched in this way will be affected by Spikes and Toxic Spikes (unless it is also ungrounded for other reasons); if a Poison-type Pokémon with Levitate is switched in this way, it will remove Toxic Spikes from its side of the field (unless it is also ungrounded for other reasons).
- If a Pokémon with Mold Breaker attacks, it does not gain Attack due to an ally's Flower Gift.

Multitype ✅
- If a Pokémon transforms into Arceus, the Pokémon will now be in the same form as the target Arceus, regardless of its own held item.
- No longer has an effect on items; instead, item-manipulating effects cannot affect Arceus if they would cause it to hold a Plate or take a Plate it already holds.

Natural Cure ✅
- No longer heals any status conditions upon completing a battle.

Own Tempo ✅
- If the Pokémon with this Ability is confused and is holding a Persim or Lum Berry, the Berry will be eaten before Own Tempo cures the Pokémon of confusion.

Run Away ✅
- From Generation V onward, when the player's Pokémon with Run Away faints in a wild battle, if the player attempts to flee instead of sending out another Pokémon, escape is no longer guaranteed in this situation.

Shed Skin ✅
- Now has a 1/3 chance of curing the Pokémon, up from 30%.

Skill Link ✅
- When Triple Kick is used by a Pokémon with Skill Link, there will be one accuracy check for all strikes instead of individual checks for each strike.

Sniper ✅
- Can now be activated by Beat Up.
- Rather than changing the critical hit multiplier directly, Sniper now multiplies by 1.5 the damage dealt by a move that deals a critical hit, applied last to damage as part of the "final" modifiers that get applied to the damage, resulting in virtually the same effect.

Speed Boost ✅
- Will not activate at the end of the turn if the user failed to escape from a wild encounter during that turn.

Technician ✅
- No longer applies for any means of confusion damage, including the one induced by disobedience.
- Struggle and Beat Up are now boosted by Technician.
- Technician no longer takes into account base power modifiers, but does consider variable base power (e.g. Rollout, Ice Ball, Gust, Acrobatics), which must be 60 or less to be boosted by Technician.

Trace ✅
- Even if a Pokémon had previously activated Trace, if it gains Trace again (e.g. via Skill Swap), Trace will activate at the first opportunity.
