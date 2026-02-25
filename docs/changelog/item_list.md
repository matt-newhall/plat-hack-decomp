# Item Changes

Herein are all of the changes that have been made to items as part of the base engine for Pokemon Tempered Platinum.

## Major Changes

Aguav Berry, Figy Berry, Iapapa Berry, Mago Berry, Wiki Berry
- The restored amount is decreased to ⅓ of the holder's HP, when it drops to ¼ or below.

Focus Band
- If Focus Band activates on a multistrike move, the holder will now only survive the strike that activated it, and the Focus Band will have to activate independently on each subsequent hit.

Focus Sash
- Focus Sash will only protect its holder from the first strike of a multistrike move.

Iron Ball
- If held by a Flying-type Pokémon, it takes 1× damage from Ground-type moves, regardless of its other types. This does not apply if the holder is grounded by any other effect.
- All of the effects of the Iron Ball are negated by Klutz and Embargo.

King's Rock, Razor Fang
- Grants all attacking moves that do not already have a chance to flinch a 10% chance of causing each target to flinch.

Mental Herb
- If the holder is infatuated or affected by Taunt, Encore, Torment, Heal Block, or Disable, it consumes the Mental Herb and is cured of all these effects.

Metronome
- The Metronome now boosts the power of a move by 20% for each previous, consecutive turn it has been used successfully, up to a maximum increase of 100% (which requires using the same move 6 or more times in a row).

Soul Dew
- If held by Latios or Latias, it increases the power of its Psychic- and Dragon-type moves by approximately 20%, instead of raising Special Attack and Special Defence by 50%.

## Number Adjustments

Fresh Water
- Restores 30HP

Soda Pop
- Restores 50HP

Energy Powder, Super Potion
- Restores 60HP

Lemonade
- Restores 70HP

Energy Root, Hyper Potion
- Restores 120HP

Duck Ball
- If used at night or in a cave, the Dusk Ball has a 3× catch rate modifier (down from 3.5×); otherwise, it has a 1× modifier.

Nest Ball
- Slight adjustment to formula for catch rate modifier.

Net Ball
- If used against a Water- or Bug-type Pokémon, the Net Ball has a 3.5× catch rate modifier (up from 3×); otherwise, it has a 1× modifier.

Quick Ball
- If used on the first turn of the encounter, the Quick Ball has a 5× catch rate modifier (up from 4×); otherwise, it has a 1× modifier.

Repeat Ball
- If used on a Pokémon that is already registered as owned in the player's Pokédex, the Net Ball has a 3.5× catch rate modifier (up from 3×); otherwise, it has a 1× modifier.

Safari Ball
- The Safari Ball's catch rate modifier is once again 1× (down from 1.5×).

Timer Ball
- Slight adjustment to formula for catch rate modifier.

## Minor Changes

Black Sludge, Leftovers
- These items cannot heal Pokémon affected by Heal Block.

Cleanse Tag
- Cleanse Tag's encounter rate reduction does not apply if it is held by a Pokémon with Illuminate, Arena Trap, No Guard, Stench, White Smoke, or Quick Feet, or if the Pokémon has Sand Veil or Snow Cloak and the appropriate weather condition is in effect. However, Cleanse Tag is still cumulative with the overworld effects of Intimidate and Keen Eye.

Grip Claw
- When held by a Pokémon, it causes binding moves used by the holder to always bind for 7 turns (up from 5 turns).

Lagging Tail, Full Incense
- If multiple Pokémon with the Ability Stall or that are holding a Lagging Tail or Full Incense use moves with the same priority, the Pokémon move relatively according to Speed (the order is reversed during Trick Room).

Life Orb
- The Life Orb now displays a message when it inflicts damage.
- Life Orb now causes damage to the holder when hitting a substitute.

Light Ball
- If held by a Pikachu, it doubles both its Attack and Special Attack, instead of doubling move power.

Shell Bell
- The Shell Bell activates even if the move only hits a Pokémon's substitute.
- The Shell Bell cannot heal a Pokémon affected by Heal Block.

Smoke Ball
- If the player's Pokémon holding a Smoke Ball faints, the player is no longer guaranteed to flee successfully.
- If held by a Pokémon, it can Teleport successfully, regardless of trapping moves and Abilities.

## Ignored

I have ignored the following item changes due to not being relevant to Pokemon Tempered Platinum. This is due to EVs being (largely) disabled, items not being able to be used in battle, and preventing from using breeding to obtain Pokemon.

**Power Items**

All power items, when equipped, now grant the Pokemon holding the item with 8 EVs in a specific stat upon gaining experience from battle.

**EV Boosting Vitamins**

The cap on EV boosting vitamins has been removed, allowing you to use vitamins on a Pokemon with more than 100 EVs in the stat that it affects.

**X Items**

X Items now raise their respective stat by 2 stages instead of just 1 stage.

**Destiny Knot**

From Generation VI onward, if held by a Pokémon in a Day Care, Nursery, or during a picnic, any Eggs produced by that Pokémon will inherit 5 of their individual values (IVs) at random from either of their parents, instead of the 3 they normally would. Each IV is independently inherited from a random parent.

**EXP. Share**

The modern EXP. Share has not been implemented - I have left the default as-is for now.

**Life Orb**

The Life Orb does increase the damage dealt from Future Sight and Doom Desire. *ignored as these moves are not in Pokemon Tempered Platinum*

**Mental Herb**

If a Pokémon with Oblivious and holding a Mental Herb is infatuated or affected by Taunt, the Mental Herb will be consumed before Oblivious cures the Pokémon of infatuation or the Taunt. *I couldn't replicate this on Showdown, so leaving it out*

If a Pokémon holding a Mental Herb triggers Cute Charm of multiple Pokémon with a single attack, the Mental Herb will be consumed immediately after the first Ability activates, so by the time the second Ability activates the holder no longer has a Mental Herb. *No multi-target contact moves*

**Timer and Nest Balls**

Rounding in gen V onwards works a bit differently. Most fractions are approximated as a fraction of n/4096. I have approximated these to be as accurate as possible in these formulas.
