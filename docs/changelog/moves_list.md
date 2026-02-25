# Implemented changes

Herein are all of the changes that have been made to moves as part of the base engine for Pokemon Tempered Platinum. I have attempted to sort these into fields to indicate what effect these have on gameplay.

## Major Changes

Arm Thrust, Barrage, Beat Up, Bonemerang, Bone Rush, Bullet Seed, Double Hit, Double Slap, Comet Punch, Double Kick, Fury Attack, Fury Swipes, Icicle Spear, Pin Missile, Rock Blast, Spike Cannon, Triple Kick, Twineedle ✅
- If a Focus Sash activates before the last strike is dealt, the following strike will cause the defending Pokémon to faint. A Focus Band can still activate repeatedly to prevent fainting, but each chance is independent. Sturdy will activate with each hit if the defending Pokémon has a maximum HP of 1.

Bug Buzz, Chatter, Grass Whistle, Growl, Hyper Voice, Metal Sound, Screech, Sing, Snore, Supersonic, Uproar ✅
- Can now hit Pokémon even if they are behind a substitute

Cotton Spore, Poison Powder, Sleep Powder, Spore, Stun Spore ✅
- Grass-type Pokémon are now immune to powder moves.

Dark Void ✅
- Dark Void can now only be successfully used by Darkrai (or a Pokémon that has transformed into Darkrai).

Defog ✅
- Defog now clears away Spikes, Toxic Spikes, Stealth Rock, and Sticky Web on both the user's and target's side of the field. In addition to Light Screen, Reflect, Safeguard, and Mist, it also clears away Aurora Veil from the target's side of the field only.
- Defog no longer lowers the evasion of a Pokémon behind a substitute.

Encore ✅
- Encore now lasts exactly 3 turns.
- A Pokémon affected by Encore can now select the target of its moves.
- If a Pokémon is forced to use Focus Punch on a turn it chose another move, the charging message does not appear and it can be executed regardless of whether the Pokémon took damage that turn.
- Encore once again fails if the target's last move was a move that calls other moves.

Fire Fang ✅
- Fire Fang no longer bypasses Wonder Guard.

Growth ✅
- Growth now increases the user's Attack by one stage in addition to increasing Special Attack by one stage.
- In harsh sunlight, Growth raises Attack and Special Attack by two stages each.

Hidden Power ✅
- Now has a fixed base power of 60.

Howl ✅
- Howl raises the user and its allies' Attack stats by one stage.
- Howl is now a sound-based move. As such, it cannot affect allies with the Ability Soundproof. However, Howl always affects the user even it has Soundproof.
- Howl cannot affect allies if they are behind a substitute. However, it is not blocked by protection moves.

Jump Kick, High Jump Kick ✅
- The crash damage is now (always) equal to half of the user's max HP, rounded down.

Knock Off ✅
- Knock Off now removes the held item rather than rendering it unusable; this means that the Pokémon can obtain another item if its held item is removed by Knock Off. However, Recycle still cannot recover an item removed by Knock Off.
- If the user faints due to the target's Rough Skin, it cannot remove the target's held item.
- However, Knock Off will still remove the target's held item if the user faints due to its own held Life Orb.
- If Knock Off causes a Pokémon with the Sticky Hold Ability to faint, it can now remove that Pokémon's held item.
- Knock Off can now remove a held Griseous Orb from any Pokémon other than Giratina.
- Knock Off cannot remove a Plate if the target is Arceus (Multitype has no effect on Knock Off).
- If those Pokémon use Knock Off on a target holding this item (whenever or not the target benefits from holding the item), the item will not be removed.
- If Knock Off is used on a Pokémon that is holding an item that can be knocked off, its base power will be boosted by 50%.
- Knock Off cannot remove the held item of a target that has Sticky Hold or if it hits the target's substitute, but the bonus damage will apply anyway.
- If used on a Pokémon weak to Dark-type moves holding a Colbur Berry, the Colbur Berry will still be eaten, but Knock Off will get the damage boost regardless.
- If used on a Pokémon that cannot lose its held item — such as a Pokémon holding its corresponding Mega Stone — this move will not receive the boost.
- Additionally, the boost will also not be applied if the user of Knock Off targets a Pokémon holding an item that would not be able to be removed from it.

Rapid Spin ✅
- When inflicting damage, Rapid Spin now also raises the user's Speed by one stage.

Recycle ✅
- Recycle allows the user to recover a held item that the user had previously consumed during the battle.
- Consumed items are tracked by the Pokémon that consumed them, and are not forgotten even if switched out.
- A Pokémon may only have one consumed item at a time; if a Pokémon consumes an item, then obtains another and consumes it,
    the original consumed item cannot be restored, even if the second item is restored and transferred to another Pokémon.
- Recycle can no longer restore items lost via Bug Bite and Pluck.

String Shot ✅
- String Shot now decreases the targets' Speed stat by two stages.

Sweet Scent ✅
- Sweet Scent now lowers the targets' evasion by two stages.

Tail Glow ✅
- Tail Glow now increases the user's Special Attack by three stages.

Tailwind ✅
- Tailwind now lasts for four turns.

Taunt ✅
- The duration of Taunt is now three turns if the user acts before the target, or four turns if the target acted before the user.
- Pokémon with Oblivious cannot become taunted.

Teleport ✅
- Now switches the user out with -6 priority.
- Fails if the user has no other available Pokemon in their party.
- In wild battles, if a wild Pokemon uses Teleport, it will still attempt to flee the battle. This move will fail for wild Pokemon in double battles.
- If the user is holding a Smoke Ball, Teleport will succeed regardless of trapping moves and Abilities.
- Teleport will succeed regardless of Ingrain.

Toxic ✅
- If Toxic is used by a Poison-type Pokémon, that move will never miss, even if the target is in the semi-invulnerable turn of a move such as Fly or Dig. If that Pokémon uses any additional moves after Toxic in the same turn, those moves will never miss either—this is known as the Toxic sure-hit glitch.
- A Pokémon that becomes badly poisoned with Toxic will now change to regular poison after the battle ends.

Wish ✅
- Wish now heals for half of the user's maximum HP rather than the recipient's.

## Minor Differences

Beat Up ✅
- Instead of using each party member's Attack stat, the user's Attack alone is used to calculate the damage of each strike. Because of this, Beat Up is now affected by boosts like from Swords Dance and Attack-boosting items like Choice Band.
- Furthermore, the base power per strike is no longer 10, but instead individually based on the Attack base stats of the party Pokémon.
- Beat Up now receives STAB from Dark-type users, no longer dealing typeless damage, and is affected by Technician.

Bind, Clamp, Fire Spin, Magma Storm, Sand Tomb, Whirlpool, Wrap ✅
- Now lasts for four to five turns.
- If a Grip Claw is held by the user, will now always last for six turns.
- The end turn damage is increased from 1/16 to 1/8 of the target's maximum HP.
- Ghost-type Pokémon cannot be trapped.

Block, Mean Look, Spider Web ✅
- If a Pokémon traps a target with either of these moves and then switches with Baton Pass, the target will no longer be trapped.
- Pokémon affected by this status can also switch out with U-Turn/Volt Switch.
- No longer affects Ghost-type Pokémon. It will now hit the target even if it has used Protect or Detect.

Body Slam, Dragon Rush, Stomp ✅
- If the target has used Minimize, deals double its regular damage.
- In Stomp's case, the damage dealt will be doubled instead of its power (resulting in virtually the same effect).
- Bypasses accuracy checks to always hit if target has used Minimize, unless the target is in the semi-invulnerable turn of a move such as Dig or Fly.

Brick Break ✅
- Brick Break no longer removes Light Screen and Reflect if the target is immune to Brick Break.

Chatter ✅
- Always confuses the target.
- Can be copied by Mirror Move.

Curse ✅
- Curse is now a Ghost-type move.
- Curse can now hit through a substitute.
- In a Single Battle, if the user is not already Ghost-type and becomes Ghost-type before executing Curse (due to Color Change), Curse will execute as it does for all Ghost types, hurting the user and inflicting the curse.
- In a Double Battle, if the user is not already Ghost-type and becomes Ghost-type before executing Curse (due to Color Change), Curse will now target a random opponent.
- Ghost-type Pokémon are no longer able to choose targets for Curse in a Double Battle, and will always attempt to inflict the curse on a random opponent.

Dream Eater ✅
- Dream Eater can now hit a substitute and will properly heal the user when damaging a substitute, even if it was broken.
- Affected by Liquid Ooze

Embargo ✅
- Embargo now negates the Speed drop from the Iron Ball, Macho Brace, and Power items (such as the Power Bracer).
- Embargo can now be used successfully on a Pokémon with Multitype and Origin Forme Giratina. However, Embargo cannot negate form-changing effects of items.
- If the target of Fling is under the effect of Embargo, items thrown at it now activate as usual.
- If a Pokémon affected by Embargo uses Bug Bite or Pluck, it will now receive the effects of a consumed held Berry.

Endure ✅
- Effects that require damage to be done to the Pokémon (such as contact Abilities) will now trigger if a Pokémon endures a hit when already at 1 HP.

Explosion, Selfdestruct ✅
- If all targets have already fainted this turn such that there is no target when the move is being executed, the user will now faint regardless.

Facade ✅
- When using Facade, Burn's effect of halving the damage done by physical moves is now ignored (this never applied to Guts).

Feint ✅
- Feint can now inflict damage even if the target has not used Protect or Detect.
- Feint can now be copied by Mirror Move.

Gust, Twister ✅
- Twister can now hit a Pokémon during the semi-invulnerable turns of Fly, Bounce and Sky Drop, and if it does, will deal double the damage.
- If the user is hit by Gust or Twister during the semi-invulnerable turn, the damage dealt will be doubled rather than the move's power (resulting in virtually the same effect).

Ingrain ✅
- Ghost-type Pokémon under the effects of Ingrain are now able to switch out. However, they still cannot be forced to switch by moves that switch the target out.

Heal Bell ✅
- Heal Bell now always affects the user, even if it has Soundproof; however, other active Pokémon with Soundproof are still unaffected by it.

Light Screen, Reflect ✅
- Removed from a Pokémon's side of the field if it is hit by Brick Break or Defog. Is not removed if the target is immune to the move (e.g. a Ghost-type Pokémon targeted by Brick Break).
- Always reduces damage by 1/3 in double battles

Magic Coat ✅
- Magic Coat's effect no longer ends if it reflects a move, so it can reflect multiple moves per turn.
- In battles with multiple opponents, if a reflectable move targets multiple Pokémon on a side, then the move can be reflected at multiple opponents.
- Can now reflect Defog, Disable, Embargo, Encore, Foresight, Heal Block, Miracle Eye, Odor Sleuth, Roar, Spikes, Spite, Stealth Rock, Taunt, Torment, Toxic Spikes & Whirlwind

Mimic ✅
- The mimicked move now has the max PP as opposed to 5.
- Mimic is no longer able to copy Transform.

Nature Power ✅
- Building/Distortion/Link - Tri Attack
- Sand/Plain (Earthquake => Earth Power)
- Cave/Rock (Rock Slide => Power Gem)
- Tall Grass (Seed Bomb => Energy Ball)
- Water - Hydro Pump
- Snow/Ice (Blizzard => Ice Beam)
- Marsh - Mud Bomb

Outrage, Petal Dance, Thrash ✅
- It is disrupted if it is not successful due to missing, sleeping, paralysis, freeze, flinching, a Protecting target, or immunity from a type or Wonder Guard. If a disruption occurs on what would have been the final, confusion-inducing turn of the move, the user will still become confused.

Payback ✅
- Payback's power no longer doubles if the target switches out.

Perish Song ✅
- Pokémon with Soundproof are no longer immune to their own moves, so if a Pokémon uses Perish Song, it will now gain a perish count even if it has Soundproof. However, other Pokémon with Soundproof are still immune to Perish Song.

Roar, Whirlwind ✅
- In wild Pokémon battles, these moves will now always fail if the user's level is less than the target's.
- In Trainer battles, these moves will now succeed if they hit, regardless of either Pokémon's level.
- Bypass accuracy checks to always hit, unless the target is in the semi-invulnerable turn of a move (such as Dig or Fly).
- Can now hit a target even if it has used Protect or Detect.

Skill Swap ✅
- If the two Abilities being swapped both have an effect or message that activates when gained (such as Intimidate and Unnerve), the Pokémon using Skill Swap will always have its new Ability activate first.
- If it is an Ability such as Intimidate that activates when it is gained, it will activate for both Pokémon after being gained this way.

Snatch ✅
- Snatch no longer steals moves that were stolen by another Pokémon's Snatch on the same turn. The order in which moves are stolen is the same as the order in which Snatch was executed.
- Acupressure and Psych Up can no longer be stolen. All moves that can be stolen either affect only the user or affect the user's entire team.
- Rest and Swallow can now only be stolen if they would have an effect when used by the original user (regardless of whether or not they would have an effect on the user of Snatch).
- If Swallow is stolen and the user of Snatch is not under the effects of Stockpile, it will nonetheless recover 25% of its max HP.
- Acupressure & Psych Up can no longer be stolen by Snatch
- Conversion, Healing Wish, Imprison, Lucky Chant, Lunar Dance, Magnet Rise, Power Trick, Recycle & Wish can now be stolen by Snatch

Uproar ✅
- Uproar now causes the user to make an uproar for exactly 3 turns.
- When Uproar is initially used (i.e. when the user is not already making an uproar), any sleeping Pokémon on the field are woken up (even if they have the Ability Soundproof). This is now the only time Uproar wakes up Pokémon that are already asleep.
- While a Pokémon is making an uproar, Pokémon cannot fall asleep (even if they have Soundproof).
- Pokémon can be made drowsy by Yawn, but a drowsy Pokémon cannot fall asleep during an uproar (even if it has Soundproof).
- If Uproar fails to be executed completely on any turn—such as if it is used against a Ghost-type Pokémon, a protected Pokémon, or a Pokémon with the Ability Soundproof—the user immediately calms down and is no longer forced to use Uproar.

## Incredibly Specific Interactions / Rounding Errors

Acupressure ✅
- Acupressure will no longer fail if the target is the user and the user is behind a substitute; it will still fail if targeting an ally behind a Substitute.

Arm Thrust, Barrage, Bone Rush, Bullet Seed, Comet Punch, Double Slap, Fury Attack, Fury Swipes, Icicle Spear, Pin Missile, Rock Blast, Spike Cannon ✅
- There is now a 35% chance that it will hit 2 times, a 35% chance it will hit 3 times, a 15% chance it will hit 4 times, and a 15% chance it will hit 5 times.

Aromatherapy ✅
- Aromatherapy cannot affect allies behind a substitute, but still affects the user even if it is behind a substitute.

Bide ✅
- Bide can no longer hit Ghost-type Pokémon.
- If Bide is called through another move, it will have +1 priority on its subsequent turns.

Bug Bite, Pluck ✅
- The user will now receive the effects of the target's held Berry even if it has the Ability Klutz or is affected by Embargo.
- The effect of a Jaboca Berry will now activate before the Berry can be stolen, and also a Coba/Tanga Berry if the move was Pluck/Bug Bite respectively.

Charge ✅
- If the user's next move is not Electric-type, Charge no longer wears off, and instead remains active for the next move that is. However, if the user attempted to use an Electric-type move, Charge will still wear off even if a condition prevented the move from being used, such as being asleep or flinching. Missing an Electric-type move will remove the buff.
- Multiple instances of the Charge effect (using Charge multiple times while the user's Ability is Normalize) are not cumulative; the next Electric-type move will still only deal twice as much damage, and no instances of the effect will linger to be used on subsequent moves.

Counter, Mirror Coat ✅
- If the Pokémon using Counter is hit by a physical attack that deals 0 damage (for example, False Swipe when the user of Counter already has 1 HP), Counter becomes a physical move with 1 base power.

Covet, Thief ✅
- Can now steal a held Griseous Orb as long as neither the user nor the target is Giratina.
- Plates cannot be stolen if either the user or the target is Arceus (Multitype has no effect on Covet/Thief).

Crush Grip, Wring Out ✅
- Changed Damage Formula

Earthquake, Magnitude ✅
- If either move hits a Pokémon during the semi-invulnerable turn of Dig, instead of doubling in power, the damage is doubled instead, resulting in virtually the same effect.

Fly ✅
- The user can also be hit with Hurricane during the semi-invulnerable turn of Fly.

Focus Energy ✅
- The effect of Focus Energy can now be copied by Psych Up or Transform.

Focus Punch ✅
- PP is no longer consumed if the user loses its focus and fails to execute the move.
- If the user loses focus, it is ignored when determining the last move used (for the purposes of Encore, etc.).
- If a Pokémon becomes locked into Focus Punch by Encore but selected a different move that turn and hasn't already moved, it will use Focus Punch at the priority of the move it selected regardless of whether it took damage that turn, and the charging message will not appear.

Foresight, Miracle Eye, Odor Sleuth ✅
- Will once again fail if used against a Pokémon already under its effect.

Gyro Ball ✅
- If the user of Gyro Ball has a Speed stat that rounds down to 0, the move's power is set to 1, entirely ignoring the Gyro Ball damage formula.

Haze ✅
- The effects of Focus Energy are once again unaffected by Haze.

Heal Order, Milk Drink, Recover, Roost, Slack Off, Soft-boiled ✅
- Restores 50% of the user's maximum HP, rounded up.

Helping Hand ✅
- It no longer boosts confusion damage.

Judgment, Natural Gift, Weather Ball ✅
- Unaffected by Normalize.

Lock-On, Mind Reader ✅
- Multiple Pokémon can have the effect of Mind Reader or Lock-On on the same target.
- Mind Reader will not fail if another Pokémon has used Mind Reader or Lock-On on the same target; it will only fail if the user already has the effect active on its current target.

Memento ✅
- The user will not faint if Memento fails (such as if it has no target, the move misses, or is blocked by a substitute), or if it is blocked by a protection move.
- However, the user will faint if Memento is unable to affect the target's stats but still hits (such as due to Clear Body or if both stats are already at -6).

Metronome ✅
- Metronome can now call moves even if they would fail due to Gravity or Heal Block.
- Metronome can call moves that the user knows.
- If Metronome calls a move the user knows and its user is holding a Choice Band, Choice Specs, or Choice Scarf, the move Metronome called will be locked by the Choice item. Otherwise, Metronome is the locked move.
- If Metronome calls a multi-turn move such as Rollout or Dig and its user is holding a Choice Band, Choice Specs, or Choice Scarf, and the user doesn't know the move, the move will activate on the first turn, but will fail and end the move on the next turn.

Psych Up ✅
- Psych Up now also copies the target's critical hit ratio. (e.g. If the target has the effect of Focus Energy, the user also gains that effect; if the user has the effect of Focus Energy but the target does not, the user loses that effect.)

Psycho Shift ✅
- Psycho Shift will now inflict the status condition on the target, then cure the user. Therefore, if Psycho Shift is used on a Pokémon with Synchronize, the user of Psycho Shift will already be afflicted with a status condition when Synchronize activates.

Psywave ✅
- Psywave now deals Floor((Level_user * (r+50))/100), with 0 <= r <= 100. However, if this calculation produces a value of 0, Psywave deals 1 HP of damage instead.

Rage ✅
- Removes the generation IV 'rage glitch'

Safeguard ✅
- Safeguard no longer prevents allies from being confused by a Figy, Wiki, Mago, Aguav or Iapapa Berry (regardless of whether it is consumed as a held item, via Fling, or via Bug Bite or Pluck).
- Safeguard no longer prevents allies from being burned or poisoned by a held Flame Orb or Toxic Orb.
- Safeguard now protects the user from being inflicted with a status condition when making contact with a Pokémon with the Ability Effect Spore, Static, Flame Body or Poison Point.

Sleep Talk ✅
- Sleep Talk now works multiple times if used while holding a choice item.

Spit Up ✅
- Damage done by Spit Up is now varied by the standard random [0.85, 1] damage modifier during damage calculation.

Spit Up, Swallow ✅
- Stockpiles that did not result in stat changes (most likely because the stat was already maxed out) are not taken into account for this adjustment, but Stockpiles that resulted in stat changes which were later erased by a move such as Haze or Clear Smog are.
- In this implementation, Stockpile will just not increment if both stats are maxed.

Struggle ✅
- Struggle's recoil calculation is now subject to standard rounding; for example, a Pokémon with 201 maximum HP using Struggle will have its recoil round down to 50, but 202 or 203 HP will round up to 51 recoil damage.
- Struggle no longer activates the Chilan Berry.
- Struggle's power is now boosted by Technician.

Sucker Punch ✅
- Sucker Punch will now succeed if the opponent is using Me First (despite the fact that Me First is a status move).

Surf, Whirlpool ✅
- If either move hits a Pokémon during the semi-invulnerable turn of Dive, instead of doubling in power, the damage is doubled instead, resulting in virtually the same effect.

Switcheroo, Trick ✅
- Switcheroo/Trick can now exchange a Griseous Orb, but still fail if either Pokémon holds a Griseous Orb and either Pokémon is Giratina.
- Switcheroo/Trick can now exchange items with a Pokémon that has Multitype, but still fail if either Pokémon holds a Plate and either Pokémon is Arceus.

Toxic Spikes ✅
- Toxic Spikes does not activate the Ability Synchronize at all, even if a Pokémon on the field directly causes Synchronizing Pokémon to switch in, such as by using a move like Roar or Dragon Tail.

Triple Kick ✅
- If the user has the Ability Skill Link, the move will have only one accuracy check.

Yawn ✅
- Yawn no longer fails during an uproar, but drowsiness cannot cause a Pokémon to fall asleep during an uproar.
