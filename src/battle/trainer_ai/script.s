    .ifndef ASM_BATTLE_SCRIPT_INC
    .set ASM_BATTLE_SCRIPT_INC, 1

#include "constants/battle.h"
#include "constants/moves.h"
#include "constants/items.h"
#include "constants/battle/trainer_ai.h"
#include "generated/abilities.h"
#include "generated/genders.h"
#include "generated/pokemon_types.h"
#include "macros/aicmd.inc"

    .text

    .global gTrainerAITable
gTrainerAITable:

FlagTable:
    LabelDistance Basic_Main,              FlagTable // AI_FLAG_BASIC
    LabelDistance EvalAttack_Main,         FlagTable // AI_FLAG_EVAL_ATTACK
    LabelDistance Expert_Main,             FlagTable // AI_FLAG_EXPERT
    LabelDistance SetupFirstTurn_Main,     FlagTable // AI_FLAG_SETUP_FIRST_TURN
    LabelDistance Risky_Main,              FlagTable // AI_FLAG_RISKY
    LabelDistance PrioritizeExtremes_Main, FlagTable // AI_FLAG_PRIORITIZE_EXTREMES
    LabelDistance BatonPass_Main,          FlagTable // AI_FLAG_BATON_PASS
    LabelDistance TagStrategy_Main,        FlagTable // AI_FLAG_TAG_STRATEGY
    LabelDistance CheckHP_Main,            FlagTable // AI_FLAG_CHECK_HP
    LabelDistance Weather_Main,            FlagTable // AI_FLAG_WEATHER
    LabelDistance Harrassment_Main,        FlagTable // AI_FLAG_HARRASSMENT
    LabelDistance Terminate,               FlagTable // AI_FLAG_UNUSED_11
    LabelDistance Terminate,               FlagTable // AI_FLAG_UNUSED_12
    LabelDistance Terminate,               FlagTable // AI_FLAG_UNUSED_13
    LabelDistance Terminate,               FlagTable // AI_FLAG_UNUSED_14
    LabelDistance Terminate,               FlagTable // AI_FLAG_UNUSED_15
    LabelDistance Terminate,               FlagTable // AI_FLAG_UNUSED_16
    LabelDistance Terminate,               FlagTable // AI_FLAG_UNUSED_17
    LabelDistance Terminate,               FlagTable // AI_FLAG_UNUSED_18
    LabelDistance Terminate,               FlagTable // AI_FLAG_UNUSED_19
    LabelDistance Terminate,               FlagTable // AI_FLAG_UNUSED_20
    LabelDistance Terminate,               FlagTable // AI_FLAG_UNUSED_21
    LabelDistance Terminate,               FlagTable // AI_FLAG_UNUSED_22
    LabelDistance Terminate,               FlagTable // AI_FLAG_UNUSED_23
    LabelDistance Terminate,               FlagTable // AI_FLAG_UNUSED_24
    LabelDistance Terminate,               FlagTable // AI_FLAG_UNUSED_25
    LabelDistance Terminate,               FlagTable // AI_FLAG_UNUSED_26
    LabelDistance Terminate,               FlagTable // AI_FLAG_UNUSED_27
    LabelDistance Terminate,               FlagTable // AI_FLAG_UNUSED_28
    LabelDistance RoamingPokemon_Main,     FlagTable // AI_FLAG_ROAMING_POKEMON
    LabelDistance Safari_Main,             FlagTable // AI_FLAG_SAFARI
    LabelDistance CatchTutorial_Main,      FlagTable // AI_FLAG_CATCH_TUTORIAL

Basic_Main:
    // Ignore this flag on partner battlers.
    IfTargetIsPartner Terminate

    // Score the move according to its damage. If the AI does not know any
    // moves which are eligible for scoring, skip ahead.
    FlagMoveDamageScore USE_MAX_DAMAGE
    IfLoadedEqualTo AI_NO_COMPARISON_MADE, Basic_CheckSoundproof

Basic_CheckForImmunity:
    // Check for any immunity to the current move based on move type and what
    // we know the battler's ability to be (if we do at all).
    IfMoveEffectivenessEquals TYPE_MULTI_IMMUNE, ScoreMinus10
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_MOLD_BREAKER, Basic_NoImmunityAbility
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_VOLT_ABSORB, Basic_CheckElectricAbsorption
    IfLoadedEqualTo ABILITY_MOTOR_DRIVE, Basic_CheckElectricAbsorption
    IfLoadedEqualTo ABILITY_LIGHTNING_ROD, Basic_CheckElectricAbsorption
    IfLoadedEqualTo ABILITY_WATER_ABSORB, Basic_CheckWaterAbsorption
    IfLoadedEqualTo ABILITY_STORM_DRAIN, Basic_CheckWaterAbsorption
    IfLoadedEqualTo ABILITY_FLASH_FIRE, Basic_CheckFireAbsorption
    IfLoadedEqualTo ABILITY_EARTH_EATER, Basic_CheckGroundAbsorption
    IfLoadedEqualTo ABILITY_SAP_SIPPER, Basic_CheckGrassAbsorption
    IfLoadedEqualTo ABILITY_WONDER_GUARD, Basic_CheckWonderGuard
    IfLoadedEqualTo ABILITY_WIND_RIDER, Basic_CheckWindAbsorption
    IfLoadedEqualTo ABILITY_LEVITATE, Basic_CheckGroundAbsorption
    IfLoadedEqualTo ABILITY_DRY_SKIN, Basic_CheckWaterAbsorption2
    GoTo Basic_NoImmunityAbility

Basic_CheckElectricAbsorption:
    LoadTypeFrom LOAD_MOVE_TYPE
    IfTempEqualTo TYPE_ELECTRIC, ScoreMinus12
    GoTo Basic_NoImmunityAbility

Basic_CheckWaterAbsorption:
    LoadTypeFrom LOAD_MOVE_TYPE
    IfTempEqualTo TYPE_WATER, ScoreMinus12
    GoTo Basic_NoImmunityAbility

Basic_CheckFireAbsorption:
    LoadTypeFrom LOAD_MOVE_TYPE
    IfTempEqualTo TYPE_FIRE, ScoreMinus12
    GoTo Basic_NoImmunityAbility

Basic_CheckGroundAbsorption:
    LoadTypeFrom LOAD_MOVE_TYPE
    IfTempEqualTo TYPE_GROUND, ScoreMinus12
    GoTo Basic_NoImmunityAbility

Basic_CheckGrassAbsorption:
    LoadTypeFrom LOAD_MOVE_TYPE
    IfTempEqualTo TYPE_GRASS, ScoreMinus12
    GoTo Basic_NoImmunityAbility

Basic_CheckWonderGuard:
    IfMoveEffectivenessEquals TYPE_MULTI_DOUBLE_DAMAGE, Basic_NoImmunityAbility
    IfMoveEffectivenessEquals TYPE_MULTI_QUADRUPLE_DAMAGE, Basic_NoImmunityAbility
    GoTo ScoreMinus12

Basic_CheckWaterAbsorption2:
    LoadTypeFrom LOAD_MOVE_TYPE
    IfTempEqualTo TYPE_WATER, ScoreMinus12
    GoTo Basic_NoImmunityAbility

Basic_CheckWindAbsorption:
    IfCurrentMoveIsWind ScoreMinus12
    GoTo Basic_NoImmunityAbility

Basic_NoImmunityAbility:
    FlagMoveDamageScore USE_MAX_DAMAGE
    IfLoadedEqualTo AI_NO_COMPARISON_MADE, Basic_CheckSoundproof

Basic_CheckSoundproof:
    // Check for immunity to sound-based moves. This defers to the same sound-move list that
    // the battle engine itself uses, so the two cannot drift apart.
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedNotEqualTo ABILITY_SOUNDPROOF, Basic_ScoreMoveEffect
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_MOLD_BREAKER, Basic_ScoreMoveEffect
    IfCurrentMoveIsSound ScoreMinus10

Basic_ScoreMoveEffect:
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STATUS_SLEEP, Basic_CheckCannotSleep
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_POWDER, Basic_CheckPowder
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_HALVE_DEFENSE, Basic_CheckCannotExplode
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_HALVE_SP_DEFENSE, Basic_CheckCannotExplode
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_RECOVER_DAMAGE_SLEEP, Basic_CheckDreamEater
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ATK_UP, Basic_CheckHighStatStage_Attack
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DEF_UP, Basic_CheckHighStatStage_Defense
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SPEED_UP, Basic_CheckHighStatStage_Speed
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_ATK_UP, Basic_CheckHighStatStage_SpAttack
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_DEF_UP, Basic_CheckHighStatStage_SpDefense
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ACC_UP, Basic_CheckHighStatStage_Accuracy
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_EVA_UP, Basic_CheckHighStatStage_Evasion
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ATK_DOWN, Basic_CheckLowStatStage_Attack
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SWITCH_LOWER_ATKS, Basic_CheckLowStatStage_Attack
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DEF_DOWN, Basic_CheckLowStatStage_Defense
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SPEED_DOWN, Basic_CheckLowStatStage_Speed
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_ATK_DOWN, Basic_CheckLowStatStage_SpAttack
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_DEF_DOWN, Basic_CheckLowStatStage_SpDefense
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ACC_DOWN, Basic_CheckLowStatStage_Accuracy
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_EVA_DOWN, Basic_CheckLowStatStage_Evasion
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_RESET_STAT_CHANGES, Basic_CheckStatStageImbalance
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_BIDE, Basic_CheckNonStandardDamageOrChargeTurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_FORCE_SWITCH, Basic_CheckCanForceSwitch
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_RESTORE_HALF_HP, Basic_CheckCanRecoverHP
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_HEAL_ALLIES_QUARTER, Basic_CheckLifeDew
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STATUS_BADLY_POISON, Basic_CheckCannotPoison
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SET_LIGHT_SCREEN, Basic_CheckAlreadyUnderLightScreen
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_AURORA_VEIL, Basic_CheckAuroraVeil
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ONE_HIT_KO, Basic_CheckOHKOWouldFail
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_40_DAMAGE_FLAT, Basic_CheckNonStandardDamageOrChargeTurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_PREVENT_STAT_REDUCTION, Basic_CheckAlreadyUnderMist
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_CRIT_UP_2, Basic_CheckAlreadyPumpedUp
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STATUS_CONFUSE, Basic_CheckCannotConfuse
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ATK_UP_2, Basic_CheckHighStatStage_Attack
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DEF_UP_2, Basic_CheckHighStatStage_Defense
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SPEED_UP_2, Basic_CheckHighStatStage_Speed
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_ATK_UP_2, Basic_CheckHighStatStage_SpAttack
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_DEF_UP_2, Basic_CheckHighStatStage_SpDefense
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ACC_UP_2, Basic_CheckHighStatStage_Accuracy
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_EVA_UP_2, Basic_CheckHighStatStage_Evasion
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ATK_DOWN_2, Basic_CheckLowStatStage_Attack
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DEF_DOWN_2, Basic_CheckLowStatStage_Defense
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SPEED_DOWN_2, Basic_CheckLowStatStage_Speed
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_ATK_DOWN_2, Basic_CheckLowStatStage_SpAttack
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_DEF_DOWN_2, Basic_CheckLowStatStage_SpDefense
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_EVA_DOWN_2, Basic_CheckLowStatStage_Accuracy
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ACC_DOWN_2, Basic_CheckLowStatStage_Evasion
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SET_REFLECT, Basic_CheckAlreadyUnderReflect
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STATUS_POISON, Basic_CheckCannotPoison
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STATUS_PARALYZE, Basic_CheckCannotParalyze
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SET_SUBSTITUTE, Basic_CheckCannotSubstitute
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_RECHARGE_AFTER, Basic_CheckNonStandardDamageOrChargeTurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STATUS_LEECH_SEED, Basic_CheckCannotLeechSeed
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DISABLE, Basic_CheckCannotDisable
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_LEVEL_DAMAGE_FLAT, Basic_CheckNonStandardDamageOrChargeTurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_RANDOM_DAMAGE_1_TO_150_LEVEL, Basic_CheckNonStandardDamageOrChargeTurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_COUNTER, Basic_CheckNonStandardDamageOrChargeTurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ENCORE, Basic_CheckCannotEncore
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DAMAGE_WHILE_ASLEEP, Basic_CheckAttackerAsleep
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_NEXT_ATTACK_ALWAYS_HITS, Basic_CheckLockOn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_USE_RANDOM_LEARNED_MOVE_SLEEP, Basic_CheckAttackerAsleep
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_PREVENT_ESCAPE, Basic_CheckMeanLook
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STATUS_NIGHTMARE, Basic_CheckNightmare
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_EVA_UP_2_MINIMIZE, Basic_CheckHighStatStage_Evasion
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_CURSE, Basic_CheckCurse
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SET_SPIKES, Basic_CheckSpikes
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_FORESIGHT, Basic_CheckForesight
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ALL_FAINT_3_TURNS, Basic_CheckPerishSong
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_WEATHER_SANDSTORM, Basic_CheckSandstorm
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ATK_UP_2_STATUS_CONFUSION, Basic_CheckCannotConfuse
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_INFATUATE, Basic_CheckCannotAttract
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_POWER_BASED_ON_FRIENDSHIP, Basic_CheckNonStandardDamageOrChargeTurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_RANDOM_POWER_MAYBE_HEAL, Basic_CheckNonStandardDamageOrChargeTurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_POWER_BASED_ON_LOW_FRIENDSHIP, Basic_CheckNonStandardDamageOrChargeTurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_PREVENT_STATUS, Basic_CheckAlreadyUnderSafeguard
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_PSYWAVE, Basic_CheckMagnitude
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_PASS_STATS_AND_STATUS, Basic_CheckBatonPass
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_20_DAMAGE_FLAT, Basic_CheckNonStandardDamageOrChargeTurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_HEAL_HALF_MORE_IN_SUN, Basic_CheckCanRecoverHP
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_UNUSED_133, Basic_CheckCanRecoverHP
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_UNUSED_134, Basic_CheckCanRecoverHP
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_RANDOM_TYPE_BASED_ON_IVS, Basic_CheckNonStandardDamageOrChargeTurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_WEATHER_RAIN, Basic_CheckRainDance
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_WEATHER_SUN, Basic_CheckSunnyDay
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_MAX_ATK_LOSE_HALF_MAX_HP, Basic_CheckBellyDrum
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_COPY_STAT_CHANGES, Basic_CheckStatStageImbalance
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_MIRROR_COAT, Basic_CheckNonStandardDamageOrChargeTurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_FIRST_TURN_ONLY, Basic_CheckFirstTurnInBattle
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_FLEE_FROM_WILD_BATTLE, Basic_CheckTeleport
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DEF_UP_DOUBLE_ROLLOUT_POWER, Basic_CheckHighStatStage_Defense
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_UNUSED_157, Basic_CheckCanRecoverHP
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ALWAYS_FLINCH_FIRST_TURN_ONLY, Basic_CheckFirstTurnInBattle
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STOCKPILE, Basic_CheckMaxStockpile
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SPIT_UP, Basic_CheckCanSpitUpOrSwallow
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SWALLOW, Basic_CheckCanSpitUpOrSwallow
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_WEATHER_HAIL, Basic_CheckHail
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_TORMENT, Basic_CheckTorment
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_ATK_UP_CAUSE_CONFUSION, Basic_CheckCannotConfuse
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STATUS_BURN, Basic_CheckCannotBurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_FAINT_AND_ATK_SP_ATK_DOWN_2, Basic_CheckMemento
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_HIT_LAST_WHIFF_IF_HIT, Basic_CheckNonStandardDamageOrChargeTurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_BOOST_ALLY_POWER_BY_50_PERCENT, Basic_CheckHelpingHand
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SWITCH_HELD_ITEMS, Basic_CheckCanRemoveItem
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_GROUND_TRAP_USER_CONTINUOUS_HEAL, Basic_CheckAlreadyIngrained
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_LOWER_OWN_ATK_AND_DEF, Basic_CheckNonStandardDamageOrChargeTurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_RECYCLE, Basic_CheckCanRecycle
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STATUS_SLEEP_NEXT_TURN, Basic_CheckCannotSleep
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_REMOVE_HELD_ITEM, Basic_CheckCanRemoveItem
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SET_HP_EQUAL_TO_USER, Basic_CheckNonStandardDamageOrChargeTurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_HEAL_STATUS, Basic_CheckCanRefreshStatus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_INCREASE_POWER_WITH_WEIGHT, Basic_CheckNonStandardDamageOrChargeTurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ATK_DEF_DOWN, Basic_CheckTickle
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DEF_SPD_UP, Basic_CheckCosmicPower
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ATK_DEF_UP, Basic_CheckBulkUp
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_ATK_SP_DEF_UP, Basic_CheckCalmMind
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ATK_SPD_UP, Basic_CheckDragonDance
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_QUIVER_DANCE, Basic_CheckQuiverDance
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SHELL_SMASH, Basic_CheckShellSmash
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_HEAL_HALF_REMOVE_FLYING_TYPE, Basic_CheckCanRecoverHP
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_REST, Basic_CheckCanRecoverHP
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_GRAVITY, Basic_CheckGravityActive
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_POWER_BASED_ON_LOW_SPEED, Basic_CheckNonStandardDamageOrChargeTurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_NATURAL_GIFT, Basic_CheckNaturalGift
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DOUBLE_SPEED_3_TURNS, Basic_CheckTailwind
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_METAL_BURST, Basic_CheckMetalBurst
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_PREVENT_ITEM_USE, Basic_CheckEmbargo
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_FLING, Basic_CheckFling
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_TRANSFER_STATUS, Basic_CheckCanPsychoShift
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_PREVENT_HEALING, Basic_CheckHealBlock
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SUPRESS_ABILITY, Basic_CheckGastroAcid
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_USE_LAST_USED_MOVE, Basic_CheckCopycat
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_INCREASE_POWER_WITH_MORE_STAT_UP, Basic_CheckNonStandardDamageOrChargeTurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_FAIL_IF_NOT_USED_ALL_OTHER_MOVES, Basic_CheckLastResort
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SET_ABILITY_TO_INSOMNIA, Basic_CheckWorrySeed
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_TOXIC_SPIKES, Basic_CheckToxicSpikes
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SWAP_STAT_CHANGES, Basic_CheckStatStageImbalance
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_RESTORE_HP_EVERY_TURN, Basic_CheckAquaRing
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_GIVE_GROUND_IMMUNITY, Basic_CheckMagnetRise
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_REMOVE_HAZARDS_SCREENS_EVA_DOWN, Basic_CheckDefog
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_TRICK_ROOM, Basic_CheckTrickRoom
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_ATK_DOWN_2_OPPOSITE_GENDER, Basic_CheckCaptivate
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STEALTH_ROCK, Basic_CheckStealthRock
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_FAINT_FULL_RESTORE_NEXT_MON, Basic_CheckLunarDance
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ATK_SP_ATK_UP, Basic_CheckGrowth
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_ATK_UP_3, Basic_CheckHighStatStage_SpAttack
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_DEF_UP_DOUBLE_ELECTRIC_POWER, Basic_CheckCharge
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_TAUNT, Basic_CheckTaunt
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_MAKE_SHARED_MOVES_UNUSEABLE, Basic_CheckImprison
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_TRANSFORM, Basic_CheckTransform
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STICKY_WEB, Basic_CheckStickyWeb
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_HEAL_IN_3_TURNS, Basic_CheckCanRecoverHP
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STEEL_BEAM, Basic_CheckSteelBeam
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SURVIVE_WITH_1_HP, Basic_CheckEndure
    PopOrEnd

Basic_CheckCannotSleep:
    // If the target cannot be put to sleep for any reason, score -10.
    IfStatus AI_BATTLER_DEFENDER, MON_CONDITION_ANY, ScoreMinus10
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_SAFEGUARD, ScoreMinus10
    IfFieldConditionsMask FIELD_CONDITION_UPROAR, ScoreMinus10
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_INSOMNIA, ScoreMinus10
    IfLoadedEqualTo ABILITY_VITAL_SPIRIT, ScoreMinus10
    IfLoadedEqualTo ABILITY_SWEET_VEIL, ScoreMinus10

    // Yawn does nothing to a target which is already drowsy.
    IfCurrentMoveEffectNotEqualTo BATTLE_EFFECT_STATUS_SLEEP_NEXT_TURN, Basic_CheckCannotSleep_Terminate
    IfMoveEffect AI_BATTLER_DEFENDER, MOVE_EFFECT_YAWN, ScoreMinus10

Basic_CheckCannotSleep_Terminate:
    PopOrEnd

Basic_CheckCannotExplode:
    // If the target is immune, score -10.
    IfMoveEffectivenessEquals TYPE_MULTI_IMMUNE, ScoreMinus10

    // If the target has Damp and we do not have Mold Breaker, score -10.
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_MOLD_BREAKER, Basic_CheckLastMon
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_DAMP, ScoreMinus10

Basic_CheckLastMon:
    // If we are on our last Pokemon and the target is not also on their last Pokemon,
    // score -10.
    CountAlivePartyBattlers AI_BATTLER_ATTACKER
    IfLoadedNotEqualTo 0, Basic_Explode_Terminate
    CountAlivePartyBattlers AI_BATTLER_DEFENDER
    IfLoadedNotEqualTo 0, ScoreMinus10

    // If the target is also on their last Pokemon, score -1 instead of -10.
    GoTo ScoreMinus1

Basic_Explode_Terminate:
    PopOrEnd 

Basic_CheckNightmare:
    // If the target is immune to the effect of Nightmare for any reason, score -8/-10.
    IfVolatileStatus AI_BATTLER_DEFENDER, VOLATILE_CONDITION_NIGHTMARE, ScoreMinus10
    IfNotStatus AI_BATTLER_DEFENDER, MON_CONDITION_SLEEP, ScoreMinus8
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_MAGIC_GUARD, ScoreMinus10
    PopOrEnd 

Basic_CheckDreamEater:
    // If the target is immune to Dream Eater for any reason, score -8/-10.
    IfNotStatus AI_BATTLER_DEFENDER, MON_CONDITION_SLEEP, ScoreMinus8
    IfMoveEffectivenessEquals TYPE_MULTI_IMMUNE, ScoreMinus10
    PopOrEnd 

Basic_CheckBellyDrum:
    // If the attacker is at half HP or less, score -10.
    IfHPPercentLessThan AI_BATTLER_ATTACKER, 51, ScoreMinus10

    // General comments on stat-boosting Status moves below:
    //   - If the attacker has Contrary, the move lowers the stat instead, so score -10.
    //   - If the attacker has Simple and is already at +2, score -10.
    //   - If the attacker is already at +6, score -10.
    //   - Special cases for Speed (Trick Room active -> -10) and Accuracy/Evasion (attacker has No Guard -> -10)
Basic_CheckHighStatStage_Attack:
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_CONTRARY, ScoreMinus10
    IfLoadedNotEqualTo ABILITY_SIMPLE, Basic_CheckHighStatStage_Attack_NoSimple
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_ATTACK, 8, ScoreMinus10
    PopOrEnd 

Basic_CheckHighStatStage_Attack_NoSimple:
    IfStatStageEqualTo AI_BATTLER_ATTACKER, BATTLE_STAT_ATTACK, 12, ScoreMinus10
    PopOrEnd 

Basic_CheckHighStatStage_Defense:
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_CONTRARY, ScoreMinus10
    IfLoadedNotEqualTo ABILITY_SIMPLE, Basic_CheckHighStatStage_Defense_NoSimple
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_DEFENSE, 8, ScoreMinus10
    PopOrEnd 

Basic_CheckHighStatStage_Defense_NoSimple:
    IfStatStageEqualTo AI_BATTLER_ATTACKER, BATTLE_STAT_DEFENSE, 12, ScoreMinus10
    PopOrEnd 

Basic_CheckHighStatStage_Speed:
    IfFieldConditionsMask FIELD_CONDITION_TRICK_ROOM, ScoreMinus10
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_CONTRARY, ScoreMinus10
    IfLoadedNotEqualTo ABILITY_SIMPLE, Basic_CheckHighStatStage_Speed_NoSimple
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_SPEED, 8, ScoreMinus10
    PopOrEnd 

Basic_CheckHighStatStage_Speed_NoSimple:
    IfStatStageEqualTo AI_BATTLER_ATTACKER, BATTLE_STAT_SPEED, 12, ScoreMinus10
    PopOrEnd 

Basic_CheckHighStatStage_SpAttack:
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_CONTRARY, ScoreMinus10
    IfLoadedNotEqualTo ABILITY_SIMPLE, Basic_CheckHighStatStage_SpAttack_NoSimple
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_ATTACK, 8, ScoreMinus10
    PopOrEnd 

Basic_CheckHighStatStage_SpAttack_NoSimple:
    IfStatStageEqualTo AI_BATTLER_ATTACKER, BATTLE_STAT_SP_ATTACK, 12, ScoreMinus10
    PopOrEnd 

Basic_CheckHighStatStage_SpDefense:
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_CONTRARY, ScoreMinus10
    IfLoadedNotEqualTo ABILITY_SIMPLE, Basic_CheckHighStatStage_SpDefense_NoSimple
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_DEFENSE, 8, ScoreMinus10
    PopOrEnd 

Basic_CheckHighStatStage_SpDefense_NoSimple:
    IfStatStageEqualTo AI_BATTLER_ATTACKER, BATTLE_STAT_SP_DEFENSE, 12, ScoreMinus10
    PopOrEnd 

Basic_CheckHighStatStage_Accuracy:
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_NO_GUARD, ScoreMinus10
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_NO_GUARD, ScoreMinus10
    IfLoadedEqualTo ABILITY_CONTRARY, ScoreMinus10
    IfLoadedNotEqualTo ABILITY_SIMPLE, Basic_CheckHighStatStage_Accuracy_NoSimple
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_ACCURACY, 8, ScoreMinus10
    PopOrEnd 

Basic_CheckHighStatStage_Accuracy_NoSimple:
    IfStatStageEqualTo AI_BATTLER_ATTACKER, BATTLE_STAT_ACCURACY, 12, ScoreMinus10
    PopOrEnd 

Basic_CheckHighStatStage_Evasion:
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_NO_GUARD, ScoreMinus10
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_NO_GUARD, ScoreMinus10
    IfLoadedEqualTo ABILITY_CONTRARY, ScoreMinus10
    IfLoadedNotEqualTo ABILITY_SIMPLE, Basic_CheckHighStatStage_Evasion_NoSimple
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_EVASION, 8, ScoreMinus10
    PopOrEnd 

Basic_CheckHighStatStage_Evasion_NoSimple:
    IfStatStageEqualTo AI_BATTLER_ATTACKER, BATTLE_STAT_EVASION, 12, ScoreMinus10
    PopOrEnd 

    // General comments on stat-reducing Status moves below:
    //   - If the target is already at -6, score -10.
    //   - If the target has White Smoke or Clear Body, score -10.
    //   - If reducing Attack -> -10 if the target has Hyper Cutter
    //   - If reducing Speed -> -10 if Trick Room is currently active
    //   - If reducing Speed -> -10 if the target has Speed Boost
    //   - If reducing Accuracy or Evasion -> -10 if either battler has No Guard
    //   - If reducing Accuracy -> -10 if the target has Keen Eye
Basic_CheckLowStatStage_Attack:
    IfStatStageEqualTo AI_BATTLER_DEFENDER, BATTLE_STAT_ATTACK, 0, ScoreMinus10
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_HYPER_CUTTER, ScoreMinus10
    GoTo Basic_CheckClearBodyEffect

Basic_CheckLowStatStage_Defense:
    IfStatStageEqualTo AI_BATTLER_DEFENDER, BATTLE_STAT_DEFENSE, 0, ScoreMinus10
    GoTo Basic_CheckClearBodyEffect

Basic_CheckLowStatStage_Speed:
    IfFieldConditionsMask FIELD_CONDITION_TRICK_ROOM, ScoreMinus10
    IfStatStageEqualTo AI_BATTLER_DEFENDER, BATTLE_STAT_SPEED, 0, ScoreMinus10
    CheckBattlerAbility AI_BATTLER_DEFENDER, ABILITY_SPEED_BOOST
    IfLoadedEqualTo AI_HAVE, ScoreMinus10
    GoTo Basic_CheckClearBodyEffect

Basic_CheckLowStatStage_SpAttack:
    IfStatStageEqualTo AI_BATTLER_DEFENDER, BATTLE_STAT_SP_ATTACK, 0, ScoreMinus10
    GoTo Basic_CheckClearBodyEffect

Basic_CheckLowStatStage_SpDefense:
    IfStatStageEqualTo AI_BATTLER_DEFENDER, BATTLE_STAT_SP_DEFENSE, 0, ScoreMinus10
    GoTo Basic_CheckClearBodyEffect

Basic_CheckLowStatStage_Accuracy:
    IfStatStageEqualTo AI_BATTLER_DEFENDER, BATTLE_STAT_ACCURACY, 0, ScoreMinus10
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_NO_GUARD, ScoreMinus10
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_KEEN_EYE, ScoreMinus10
    IfLoadedEqualTo ABILITY_ILLUMINATE, ScoreMinus10
    IfLoadedEqualTo ABILITY_NO_GUARD, ScoreMinus10
    GoTo Basic_CheckClearBodyEffect

Basic_CheckLowStatStage_Evasion:
    IfStatStageEqualTo AI_BATTLER_DEFENDER, BATTLE_STAT_EVASION, 0, ScoreMinus10
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_NO_GUARD, ScoreMinus10
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_NO_GUARD, ScoreMinus10

Basic_CheckClearBodyEffect:
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_CLEAR_BODY, ScoreMinus10
    IfLoadedEqualTo ABILITY_WHITE_SMOKE, ScoreMinus10
    PopOrEnd 

Basic_CheckStatStageImbalance:
    // The name is a little esoteric; an "imbalance" is regarded as the attacker
    // having any reduced stat stage or the target having any increased stat stage.
    //
    // If neither of those are true, score -10.
    IfStatStageLessThan AI_BATTLER_ATTACKER, BATTLE_STAT_ATTACK, 6, Basic_CheckStatStageImbalance_Terminate
    IfStatStageLessThan AI_BATTLER_ATTACKER, BATTLE_STAT_DEFENSE, 6, Basic_CheckStatStageImbalance_Terminate
    IfStatStageLessThan AI_BATTLER_ATTACKER, BATTLE_STAT_SPEED, 6, Basic_CheckStatStageImbalance_Terminate
    IfStatStageLessThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_ATTACK, 6, Basic_CheckStatStageImbalance_Terminate
    IfStatStageLessThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_DEFENSE, 6, Basic_CheckStatStageImbalance_Terminate
    IfStatStageLessThan AI_BATTLER_ATTACKER, BATTLE_STAT_ACCURACY, 6, Basic_CheckStatStageImbalance_Terminate
    IfStatStageLessThan AI_BATTLER_ATTACKER, BATTLE_STAT_EVASION, 6, Basic_CheckStatStageImbalance_Terminate
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_ATTACK, 6, Basic_CheckStatStageImbalance_Terminate
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_DEFENSE, 6, Basic_CheckStatStageImbalance_Terminate
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_SPEED, 6, Basic_CheckStatStageImbalance_Terminate
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_SP_ATTACK, 6, Basic_CheckStatStageImbalance_Terminate
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_SP_DEFENSE, 6, Basic_CheckStatStageImbalance_Terminate
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_ACCURACY, 6, Basic_CheckStatStageImbalance_Terminate
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_EVASION, 6, Basic_CheckStatStageImbalance_Terminate
    GoTo ScoreMinus10

Basic_CheckStatStageImbalance_Terminate:
    PopOrEnd 

Basic_CheckCanForceSwitch:
    // If the target cannot be forced out for any reason, score -10.
    CountAlivePartyBattlers AI_BATTLER_DEFENDER
    IfLoadedEqualTo 0, ScoreMinus10
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_MOLD_BREAKER, Basic_CheckCanForceSwitch_Terminate
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_SUCTION_CUPS, ScoreMinus10

Basic_CheckCanForceSwitch_Terminate:
    PopOrEnd 

Basic_CheckLifeDew:
    // Life Dew heals both slots, so it is only wasted when there is nothing left to heal on
    // either of them.
    LoadBattleType 
    IfLoadedNotMask BATTLE_TYPE_DOUBLES, Basic_CheckCanRecoverHP
    IfBattlerFainted AI_BATTLER_ATTACKER_PARTNER, Basic_CheckCanRecoverHP
    IfHPPercentNotEqualTo AI_BATTLER_ATTACKER, 100, Basic_CheckLifeDew_Terminate
    IfHPPercentEqualTo AI_BATTLER_ATTACKER_PARTNER, 100, ScoreMinus20

Basic_CheckLifeDew_Terminate:
    PopOrEnd

Basic_CheckCanRecoverHP:
    // Healing is wasted at full HP and mostly wasted just below it.
    IfHPPercentEqualTo AI_BATTLER_ATTACKER, 100, ScoreMinus20
    IfHPPercentLessThan AI_BATTLER_ATTACKER, 85, Basic_CheckCanRecoverHP_Terminate
    AddToMoveScore -6

Basic_CheckCanRecoverHP_Terminate:
    PopOrEnd 

Basic_CheckCannotPoison:
    // If the target is immune to the usual effects of Poison for any reason, score -10.
    LoadTypeFrom LOAD_DEFENDER_TYPE_1
    IfLoadedEqualTo TYPE_STEEL, ScoreMinus10
    IfLoadedEqualTo TYPE_POISON, ScoreMinus10
    LoadTypeFrom LOAD_DEFENDER_TYPE_2
    IfLoadedEqualTo TYPE_STEEL, ScoreMinus10
    IfLoadedEqualTo TYPE_POISON, ScoreMinus10

    // Check for immunity by ability
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_IMMUNITY, ScoreMinus10
    IfLoadedEqualTo ABILITY_MAGIC_GUARD, ScoreMinus10
    IfLoadedEqualTo ABILITY_POISON_HEAL, ScoreMinus10

    IfLoadedNotEqualTo ABILITY_LEAF_GUARD, Basic_CheckCannotPoison_Hydration
    LoadCurrentWeather 
    IfLoadedEqualTo AI_WEATHER_SUNNY, ScoreMinus10

Basic_CheckCannotPoison_Hydration:
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedNotEqualTo ABILITY_HYDRATION, Basic_CheckCannotPoison_StatusOrSafeguard
    LoadCurrentWeather 
    IfLoadedEqualTo AI_WEATHER_RAINING, ScoreMinus10

Basic_CheckCannotPoison_StatusOrSafeguard:
    IfStatus AI_BATTLER_DEFENDER, MON_CONDITION_ANY, ScoreMinus10
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_SAFEGUARD, ScoreMinus10
    PopOrEnd 

Basic_CheckAlreadyUnderLightScreen:
    // If already under the effect of Light Screen, score -8.
    IfSideCondition AI_BATTLER_ATTACKER, SIDE_CONDITION_LIGHT_SCREEN, ScoreMinus8
    PopOrEnd 

Basic_CheckAuroraVeil:
    // If the attacker has Mega Sol, score -10 (move will fail; it never sees hail).
    // If not currently hailing, score -10 (move will fail).
    // If already under the effect of Aurora Veil, score -10.
    // If already under the effect of both Light Screen and Reflect, score -8.
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_MEGA_SOL, ScoreMinus10
    LoadCurrentWeather
    IfLoadedNotEqualTo AI_WEATHER_HAILING, ScoreMinus10
    IfFieldConditionsMask FIELD_CONDITION_AURORA_VEIL_PERM, ScoreMinus10
    IfSideCondition AI_BATTLER_ATTACKER, SIDE_CONDITION_AURORA_VEIL, ScoreMinus10
    IfSideCondition AI_BATTLER_ATTACKER, SIDE_CONDITION_LIGHT_SCREEN, Basic_CheckAuroraVeil_CheckReflect
    PopOrEnd

Basic_CheckAuroraVeil_CheckReflect:
    IfSideCondition AI_BATTLER_ATTACKER, SIDE_CONDITION_REFLECT, ScoreMinus8
    PopOrEnd

Basic_CheckOHKOWouldFail:
    // If the OHKO move would always fail for any reason, score -10.
    IfMoveEffectivenessEquals TYPE_MULTI_IMMUNE, ScoreMinus10
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_MOLD_BREAKER, Basic_CheckOHKOWouldFail_Levels
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_STURDY, ScoreMinus10

Basic_CheckOHKOWouldFail_Levels:
    IfLevel CHECK_LOWER_THAN_TARGET, ScoreMinus10
    PopOrEnd 

Basic_CheckMagnitude:
    // If the target's ability is Levitate and the attacker's ability is not Mold Breaker, score -10.
    IfLoadedEqualTo ABILITY_MOLD_BREAKER, Basic_CheckNonStandardDamageOrChargeTurn
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_LEVITATE, ScoreMinus10

Basic_CheckPowder:
    // Powder does nothing to a Grass-type, nor to a target behind Safety Goggles or Overcoat.
    // Mold Breaker ignores the ability, but neither the typing nor the item.
    LoadTypeFrom LOAD_DEFENDER_TYPE_1
    IfLoadedEqualTo TYPE_GRASS, ScoreMinus10
    LoadTypeFrom LOAD_DEFENDER_TYPE_2
    IfLoadedEqualTo TYPE_GRASS, ScoreMinus10
    LoadHeldItemEffect AI_BATTLER_DEFENDER
    IfLoadedEqualTo HOLD_EFFECT_OVERCOAT, ScoreMinus10
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_MOLD_BREAKER, Basic_CheckPowder_Terminate
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_OVERCOAT, ScoreMinus10

Basic_CheckPowder_Terminate:
    PopOrEnd

Basic_CheckNonStandardDamageOrChargeTurn:
    // If the target is immune to this move by its typing or due to the target's ability being
    // Wonder Guard, score -10.
    IfMoveEffectivenessEquals TYPE_MULTI_IMMUNE, ScoreMinus10
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedNotEqualTo ABILITY_WONDER_GUARD, Basic_CheckNonStandardDamageOrChargeTurn_Terminate
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_MOLD_BREAKER, Basic_CheckNonStandardDamageOrChargeTurn_Terminate
    IfMoveEffectivenessEquals TYPE_MULTI_DOUBLE_DAMAGE, Basic_CheckNonStandardDamageOrChargeTurn_Terminate
    IfMoveEffectivenessEquals TYPE_MULTI_QUADRUPLE_DAMAGE, Basic_CheckNonStandardDamageOrChargeTurn_Terminate
    GoTo ScoreMinus10

Basic_CheckNonStandardDamageOrChargeTurn_Terminate:
    PopOrEnd 

Basic_CheckAlreadyUnderMist:
    // If already under the effect of Mist, score -8.
    IfSideCondition AI_BATTLER_ATTACKER, SIDE_CONDITION_MIST, ScoreMinus8
    PopOrEnd 

Basic_CheckAlreadyPumpedUp:
    // If already under the effect of Focus Energy, score -10.
    IfVolatileStatus AI_BATTLER_ATTACKER, VOLATILE_CONDITION_FOCUS_ENERGY, ScoreMinus10
    PopOrEnd 

Basic_CheckCannotConfuse:
    // If the target is already confused, score -5.
    IfVolatileStatus AI_BATTLER_DEFENDER, VOLATILE_CONDITION_CONFUSION, ScoreMinus5

    // If the target otherwise cannot be confused, score -10.
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_OWN_TEMPO, ScoreMinus10
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_SAFEGUARD, ScoreMinus10
    PopOrEnd 

Basic_CheckAlreadyUnderReflect:
    // If already under the effect of Reflect, score -8.
    IfSideCondition AI_BATTLER_ATTACKER, SIDE_CONDITION_REFLECT, ScoreMinus8
    PopOrEnd 

Basic_CheckCannotParalyze:
    // If the target cannot be paralyzed for any reason, score -10.
    IfMoveEffectivenessEquals TYPE_MULTI_IMMUNE, ScoreMinus10
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_LIMBER, ScoreMinus10
    IfLoadedEqualTo ABILITY_MAGIC_GUARD, ScoreMinus10
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_MOLD_BREAKER, Basic_CheckCannotParalyze_ImmuneToStatus
    IfMoveEqualTo MOVE_THUNDER_WAVE, Basic_CheckCannotParalyze_ThunderWave
    GoTo Basic_CheckCannotParalyze_ImmuneToStatus

Basic_CheckCannotParalyze_ThunderWave:
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_MOTOR_DRIVE, ScoreMinus10
    IfLoadedEqualTo ABILITY_VOLT_ABSORB, ScoreMinus10

Basic_CheckCannotParalyze_ImmuneToStatus:
    IfStatus AI_BATTLER_DEFENDER, MON_CONDITION_ANY, ScoreMinus10
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_SAFEGUARD, ScoreMinus10
    PopOrEnd 

Basic_CheckCannotSubstitute:
    // If the attacker's Substitute would fail, score -8/-10.
    IfVolatileStatus AI_BATTLER_ATTACKER, VOLATILE_CONDITION_SUBSTITUTE, ScoreMinus8
    IfHPPercentLessThan AI_BATTLER_ATTACKER, 26, ScoreMinus10
    PopOrEnd 

Basic_CheckCannotLeechSeed:
    // If the target is already Seeded or immune to the effects of Leech Seed, score -10.
    IfMoveEffect AI_BATTLER_DEFENDER, MOVE_EFFECT_LEECH_SEED, ScoreMinus10
    LoadTypeFrom LOAD_DEFENDER_TYPE_1
    IfLoadedEqualTo TYPE_GRASS, ScoreMinus10
    LoadTypeFrom LOAD_DEFENDER_TYPE_2
    IfLoadedEqualTo TYPE_GRASS, ScoreMinus10
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_MAGIC_GUARD, ScoreMinus10
    PopOrEnd 

Basic_CheckCannotDisable:
    // If the target is already Disabled, score -8.
    IfBattlerUnderEffect AI_BATTLER_DEFENDER, CHECK_DISABLE, ScoreMinus8
    PopOrEnd 

Basic_CheckCannotEncore:
    // If the target is already Encored, score -8.
    IfBattlerUnderEffect AI_BATTLER_DEFENDER, CHECK_ENCORE, ScoreMinus8
    PopOrEnd 

Basic_CheckAttackerAsleep:
    // If the attacker is not currently asleep, score -8.
    IfNotStatus AI_BATTLER_ATTACKER, MON_CONDITION_SLEEP, ScoreMinus8
    PopOrEnd 

Basic_CheckLockOn:
    // If the target is already Locked On, or either battler has No Guard, score -10.
    IfMoveEffect AI_BATTLER_ATTACKER, MOVE_EFFECT_LOCK_ON, Basic_CheckLockOn_Target
    GoTo Basic_CheckLockOn_NoGuard

Basic_CheckLockOn_Target:
    IfLockOnTarget AI_BATTLER_ATTACKER, AI_BATTLER_DEFENDER, ScoreMinus10

Basic_CheckLockOn_NoGuard:
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_NO_GUARD, ScoreMinus10
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_NO_GUARD, ScoreMinus10
    PopOrEnd 

Basic_CheckMeanLook:
    // If the target is already under the effect of Mean Look, score -10.
    IfVolatileStatus AI_BATTLER_DEFENDER, VOLATILE_CONDITION_MEAN_LOOK, ScoreMinus10
    PopOrEnd 

Basic_CheckCurse:
    // Branch for a Ghost-type using Curse
    LoadTypeFrom LOAD_ATTACKER_TYPE_1
    IfLoadedEqualTo TYPE_GHOST, Basic_CheckCurse_GhostType
    LoadTypeFrom LOAD_ATTACKER_TYPE_2
    IfLoadedEqualTo TYPE_GHOST, Basic_CheckCurse_GhostType

    // If the attacker has Simple, treat it like a boosting move for both Attack and Defense.
    // That is, if either Attack or Defense are already +2, score -10.
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_CONTRARY, ScoreMinus10
    IfLoadedNotEqualTo ABILITY_SIMPLE, Basic_CheckCurse_NoSimple
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_ATTACK, 8, ScoreMinus10
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_DEFENSE, 8, ScoreMinus10
    PopOrEnd 

Basic_CheckCurse_NoSimple:
    // If the attacker does not have Simple and either Attack or Defense are already +6, score -10.
    IfStatStageEqualTo AI_BATTLER_ATTACKER, BATTLE_STAT_ATTACK, 12, ScoreMinus10
    IfStatStageEqualTo AI_BATTLER_ATTACKER, BATTLE_STAT_DEFENSE, 12, ScoreMinus8
    PopOrEnd 

Basic_CheckCurse_GhostType:
    // If the target is immune to the effect, score -10.
    IfVolatileStatus AI_BATTLER_DEFENDER, VOLATILE_CONDITION_CURSE, ScoreMinus10
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_MAGIC_GUARD, ScoreMinus10
    PopOrEnd 

Basic_CheckSpikes:
    // If the target already has 3 layers of Spikes or is on their last Pokemon, score -10.
    LoadSpikesLayers AI_BATTLER_DEFENDER, SIDE_CONDITION_SPIKES
    IfLoadedEqualTo 3, ScoreMinus10
    CountAlivePartyBattlers AI_BATTLER_DEFENDER
    IfLoadedEqualTo 0, ScoreMinus10
    PopOrEnd 

Basic_CheckForesight:
    // The move has nothing to do unless the target is a Ghost-type, whose Normal and Fighting
    // immunities it lifts, or has actually raised its Evasion for the move to see through.
    IfVolatileStatus AI_BATTLER_DEFENDER, VOLATILE_CONDITION_FORESIGHT, ScoreMinus10
    LoadTypeFrom LOAD_DEFENDER_TYPE_1
    IfLoadedEqualTo TYPE_GHOST, Basic_CheckForesight_Terminate
    LoadTypeFrom LOAD_DEFENDER_TYPE_2
    IfLoadedEqualTo TYPE_GHOST, Basic_CheckForesight_Terminate
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_EVASION, 6, Basic_CheckForesight_Terminate
    AddToMoveScore -10

Basic_CheckForesight_Terminate:
    PopOrEnd

Basic_CheckPerishSong:
    // If the target is already under the effect, score -10.
    IfMoveEffect AI_BATTLER_DEFENDER, MOVE_EFFECT_PERISH_SONG, ScoreMinus10
    PopOrEnd 

Basic_CheckSandstorm:
    // If the current weather is Sand, score -8.
    LoadCurrentWeather 
    IfLoadedEqualTo AI_WEATHER_SANDSTORM, ScoreMinus8
    PopOrEnd 

Basic_CheckCannotAttract:
    // If the target cannot be Infatuated for any reason, score -10.
    IfVolatileStatus AI_BATTLER_DEFENDER, VOLATILE_CONDITION_ATTRACT, ScoreMinus10
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_OBLIVIOUS, ScoreMinus10
    PopOrEnd 

Basic_CheckAlreadyUnderSafeguard:
    // If already under the effect of Safeguard, score -8.
    IfSideCondition AI_BATTLER_ATTACKER, SIDE_CONDITION_SAFEGUARD, ScoreMinus8
    PopOrEnd 

Basic_CheckMemento:
    // If the target's ability blocks the stat drop and the attacker does not have Mold Breaker,
    // score -10.
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_MOLD_BREAKER, Basic_CheckMemento_CheckStatStages
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_CLEAR_BODY, ScoreMinus10
    IfLoadedEqualTo ABILITY_WHITE_SMOKE, ScoreMinus10

Basic_CheckMemento_CheckStatStages:
    // If the target's Attack is already at -6, score -10.
    IfStatStageEqualTo AI_BATTLER_DEFENDER, BATTLE_STAT_ATTACK, 0, ScoreMinus10

    // If the target's SpAttack is already at -6, score -8.
    IfStatStageEqualTo AI_BATTLER_DEFENDER, BATTLE_STAT_SP_ATTACK, 0, ScoreMinus8

    // If the attacker is on their last Pokemon, score -10.
    CountAlivePartyBattlers AI_BATTLER_ATTACKER
    IfLoadedEqualTo 0, ScoreMinus10
    PopOrEnd 

Basic_CheckTeleport:
    // Outside a wild battle Teleport is a switch, so it fails outright with nothing to switch to.
    CountAlivePartyBattlers AI_BATTLER_ATTACKER
    IfLoadedEqualTo 0, ScoreMinus20
    PopOrEnd

Basic_CheckBatonPass:
    // If the attacker is on its last Pokemon, there is nothing to pass to.
    CountAlivePartyBattlers AI_BATTLER_ATTACKER
    IfLoadedEqualTo 0, ScoreMinus20
    PopOrEnd 

Basic_CheckRainDance:
    // If the attacker's ability is Swift Swim or Hydration, skip the defender-Hydration check below.
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_SWIFT_SWIM, Basic_CheckCurrentWeatherIsRain
    IfLoadedEqualTo ABILITY_HYDRATION, Basic_CheckCurrentWeatherIsRain

    // If the target's ability is Hydration and they are currently statused, score -8.
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedNotEqualTo ABILITY_HYDRATION, Basic_CheckCurrentWeatherIsRain
    IfStatus AI_BATTLER_DEFENDER, MON_CONDITION_ANY, ScoreMinus8

Basic_CheckCurrentWeatherIsRain:
    // If the weather is currently Rain, score -8.
    LoadCurrentWeather 
    IfLoadedEqualTo AI_WEATHER_RAINING, ScoreMinus8
    PopOrEnd 

Basic_CheckSunnyDay:
    // If the attacker's ability is any of Flower Gift, Leaf Guard, or Solar Power, skip the defender-
    // Hydration check below.
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_FLOWER_GIFT, Basic_CheckCurrentWeatherIsSun
    IfLoadedEqualTo ABILITY_LEAF_GUARD, Basic_CheckCurrentWeatherIsSun
    IfLoadedEqualTo ABILITY_SOLAR_POWER, Basic_CheckCurrentWeatherIsSun

    // If the target's ability is Hydration and they are currently statused, score -10.
    // Why does this consider Hydration? This is clearly a bug, but what was the intention?
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedNotEqualTo ABILITY_HYDRATION, Basic_CheckCurrentWeatherIsSun
    IfStatus AI_BATTLER_DEFENDER, MON_CONDITION_ANY, ScoreMinus10

Basic_CheckCurrentWeatherIsSun:
    // If the weather is currently Sun, score -8.
    LoadCurrentWeather 
    IfLoadedEqualTo AI_WEATHER_SUNNY, ScoreMinus8
    PopOrEnd 

Basic_CheckFirstTurnInBattle:
    // Fake Out and First Impression simply fail on any turn but the one the user came in on,
    // so the penalty has to outweigh every bonus EvalAttack can hand them, the last-ditch
    // priority bonus included.
    LoadIsFirstTurnInBattle AI_BATTLER_ATTACKER
    IfLoadedNotEqualTo FALSE, Basic_CheckFirstTurnInBattle_Terminate
    AddToMoveScore -20

Basic_CheckFirstTurnInBattle_Terminate:
    PopOrEnd

Basic_CheckMaxStockpile:
    // If the Stockpile count is already at 3, score -10.
    LoadStockpileCount AI_BATTLER_ATTACKER
    IfLoadedEqualTo 3, ScoreMinus10
    PopOrEnd 

Basic_CheckCanSpitUpOrSwallow:
    // If the target is immune to the move by its typing or the Stockpile count is 0, score -10.
    // Note that this means that Swallow will never be used against a Ghost-type Pokemon, even though
    // it would still have an effect.
    IfMoveEffectivenessEquals TYPE_MULTI_IMMUNE, ScoreMinus10
    LoadStockpileCount AI_BATTLER_ATTACKER
    IfLoadedEqualTo 0, ScoreMinus10

    // Treat Swallow like a standard recovery move.
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SWALLOW, Basic_CheckCanRecoverHP
    PopOrEnd 

Basic_CheckHail:
    // If the current weather is Hail, score -8.
    LoadCurrentWeather 
    IfLoadedEqualTo AI_WEATHER_HAILING, ScoreMinus8

    // If any opposing battler's ability is Ice Body, score -8.
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedNotEqualTo ABILITY_ICE_BODY, Basic_CheckHail_Terminate
    AddToMoveScore -8

    // If an attacker's ability is also Ice Body, score +8 (undo the previous modifier).
    // This feels like a bug of misintention; the intention here seems to be for an attacker with
    // Ice Body to have an incentive to use Hail, but that is not realized. Instead, such an
    // attacker can only have a disincentive undone.
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedNotEqualTo ABILITY_ICE_BODY, Basic_CheckHail_Terminate
    AddToMoveScore 8

Basic_CheckHail_Terminate:
    PopOrEnd 

Basic_CheckTorment:
    // If the target is already under the effect, score -10.
    IfVolatileStatus AI_BATTLER_DEFENDER, VOLATILE_CONDITION_TORMENT, ScoreMinus10
    PopOrEnd 

Basic_CheckCannotBurn:
    // If the target cannot be burned for any reason, score -10.
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_WATER_VEIL, ScoreMinus10
    IfLoadedEqualTo ABILITY_WATER_BUBBLE, ScoreMinus10
    IfLoadedEqualTo ABILITY_MAGIC_GUARD, ScoreMinus10
    IfStatus AI_BATTLER_DEFENDER, MON_CONDITION_ANY, ScoreMinus10
    LoadTypeFrom LOAD_DEFENDER_TYPE_1
    IfLoadedEqualTo TYPE_FIRE, ScoreMinus10
    LoadTypeFrom LOAD_DEFENDER_TYPE_2
    IfLoadedEqualTo TYPE_FIRE, ScoreMinus10
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_SAFEGUARD, ScoreMinus10
    PopOrEnd 

Basic_CheckHelpingHand:
    // If the battle type is not Doubles, score -10.
    LoadBattleType 
    IfLoadedNotMask BATTLE_TYPE_DOUBLES, ScoreMinus10
    PopOrEnd 

Basic_CheckCanRemoveItem:
    // If the defender's ability is Sticky Hold or they do not have a held item, score -10.
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_STICKY_HOLD, ScoreMinus10
    LoadHeldItem AI_BATTLER_DEFENDER
    IfLoadedEqualTo ITEM_NONE, ScoreMinus10
    PopOrEnd 

Basic_CheckAlreadyIngrained:
    // If the attacker is already under the effect, score -10.
    IfMoveEffect AI_BATTLER_ATTACKER, MOVE_EFFECT_INGRAIN, ScoreMinus10
    PopOrEnd 

Basic_CheckCanRecycle:
    // If there is no item to be recycled, score -10.
    LoadRecycleItem AI_BATTLER_ATTACKER
    IfLoadedEqualTo ITEM_NONE, ScoreMinus10
    PopOrEnd 

Basic_CheckCanRefreshStatus:
    // If the attacker is not Burned, Poisoned, or Paralyzed, score -10.
    IfNotStatus AI_BATTLER_ATTACKER, MON_CONDITION_FACADE_BOOST, ScoreMinus10
    PopOrEnd 

Basic_CheckTickle:
    // If the target's ability is Clear Body or White Smoke and the attacker's ability is not
    // Mold Breaker, score -10.
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_MOLD_BREAKER, Basic_CheckTickle_CheckStatStages
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_CLEAR_BODY, ScoreMinus10
    IfLoadedEqualTo ABILITY_WHITE_SMOKE, ScoreMinus10

Basic_CheckTickle_CheckStatStages:
    // If the target's Attack is at -6, score -10.
    // If the target's Defense is at -6, score -8.
    IfStatStageEqualTo AI_BATTLER_DEFENDER, BATTLE_STAT_ATTACK, 0, ScoreMinus10
    IfStatStageEqualTo AI_BATTLER_DEFENDER, BATTLE_STAT_DEFENSE, 0, ScoreMinus8
    PopOrEnd 

Basic_CheckCosmicPower:
    // If the attacker's ability is Simple and either Defense or SpDefense are already at
    // +3, score -10.
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_CONTRARY, ScoreMinus10
    IfLoadedNotEqualTo ABILITY_SIMPLE, Basic_CheckCosmicPower_NoSimple
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_DEFENSE, 8, ScoreMinus10
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_DEFENSE, 8, ScoreMinus10
    PopOrEnd 

Basic_CheckCosmicPower_NoSimple:
    // If the attacker's Defense is already at +6, score -10.
    // If the attacker's SpDefense is already at +6, score -8.
    IfStatStageEqualTo AI_BATTLER_ATTACKER, BATTLE_STAT_DEFENSE, 12, ScoreMinus10
    IfStatStageEqualTo AI_BATTLER_ATTACKER, BATTLE_STAT_SP_DEFENSE, 12, ScoreMinus8
    PopOrEnd 

Basic_CheckBulkUp:
    // If the attacker's ability is Simple and either Attack or Defense are already at
    // +3, score -10.
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_CONTRARY, ScoreMinus10
    IfLoadedNotEqualTo ABILITY_SIMPLE, Basic_CheckBulkUp_NoSimple
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_ATTACK, 8, ScoreMinus10
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_DEFENSE, 8, ScoreMinus10
    PopOrEnd 

Basic_CheckBulkUp_NoSimple:
    // If the attacker's Attack is already at +6, score -10.
    // If the attacker's Defense is already at +6, score -8.
    IfStatStageEqualTo AI_BATTLER_ATTACKER, BATTLE_STAT_ATTACK, 12, ScoreMinus10
    IfStatStageEqualTo AI_BATTLER_ATTACKER, BATTLE_STAT_DEFENSE, 12, ScoreMinus8
    PopOrEnd 

Basic_CheckCalmMind:
    // If the attacker's ability is Simple and either SpAttack or SpDefense are already at
    // +3, score -10.
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_CONTRARY, ScoreMinus10
    IfLoadedNotEqualTo ABILITY_SIMPLE, Basic_CheckCalmMind_NoSimple
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_ATTACK, 8, ScoreMinus10
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_DEFENSE, 8, ScoreMinus10
    PopOrEnd 

Basic_CheckCalmMind_NoSimple:
    // If the attacker's SpAttack is already at +6, score -10.
    // If the attacker's SpDefense is already at +6, score -8.
    IfStatStageEqualTo AI_BATTLER_ATTACKER, BATTLE_STAT_SP_ATTACK, 12, ScoreMinus10
    IfStatStageEqualTo AI_BATTLER_ATTACKER, BATTLE_STAT_SP_DEFENSE, 12, ScoreMinus8
    PopOrEnd 

Basic_CheckDragonDance:
    // If Trick Room is in effect, score -10.
    IfFieldConditionsMask FIELD_CONDITION_TRICK_ROOM, ScoreMinus10

    // If the attacker's ability is Simple and either Attack or Speed are already at
    // +3, score -10.
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_CONTRARY, ScoreMinus10
    IfLoadedNotEqualTo ABILITY_SIMPLE, Basic_CheckDragonDance_NoSimple
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_ATTACK, 8, ScoreMinus10
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_SPEED, 8, ScoreMinus10
    PopOrEnd 

Basic_CheckDragonDance_NoSimple:
    // If the attacker's Attack is already at +6, score -10.
    // If the attacker's Speed is already at +6, score -8.
    IfStatStageEqualTo AI_BATTLER_ATTACKER, BATTLE_STAT_ATTACK, 12, ScoreMinus10
    IfStatStageEqualTo AI_BATTLER_ATTACKER, BATTLE_STAT_SPEED, 12, ScoreMinus8
    PopOrEnd 

Basic_CheckQuiverDance:
    // If Trick Room is in effect, score -10.
    IfFieldConditionsMask FIELD_CONDITION_TRICK_ROOM, ScoreMinus10

    // If the attacker's ability is Simple and either Sp. Atk, Sp. Def or Speed
    // are already at +3, score -10.
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_CONTRARY, ScoreMinus10
    IfLoadedNotEqualTo ABILITY_SIMPLE, Basic_CheckQuiverDance_NoSimple
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_ATTACK, 8, ScoreMinus10
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_DEFENSE, 8, ScoreMinus10
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_SPEED, 8, ScoreMinus10
    PopOrEnd 

Basic_CheckQuiverDance_NoSimple:
    // If the attacker's Sp. Atk is already at +6, score -10.
    // If the attacker's Sp. Def is already at +6, score -10.
    // If the attacker's Speed is already at +6, score -8.
    IfStatStageEqualTo AI_BATTLER_ATTACKER, BATTLE_STAT_SP_ATTACK, 12, ScoreMinus10
    IfStatStageEqualTo AI_BATTLER_ATTACKER, BATTLE_STAT_SP_DEFENSE, 12, ScoreMinus10
    IfStatStageEqualTo AI_BATTLER_ATTACKER, BATTLE_STAT_SPEED, 12, ScoreMinus8
    PopOrEnd

Basic_CheckShellSmash:
    // If Trick Room is in effect, score -10.
    IfFieldConditionsMask FIELD_CONDITION_TRICK_ROOM, ScoreMinus10

    // If the attacker's ability is Simple and Attack, Sp. Atk, or Speed are already at
    // +3, score -10.
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_CONTRARY, ScoreMinus10
    IfLoadedNotEqualTo ABILITY_SIMPLE, Basic_CheckShellSmash_NoSimple
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_ATTACK, 8, ScoreMinus10
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_ATTACK, 8, ScoreMinus10
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_SPEED, 8, ScoreMinus10
    PopOrEnd

Basic_CheckShellSmash_NoSimple:
    // Only score -10 if Attack, Sp. Atk, and Speed are all already at +6.
    IfStatStageLessThan AI_BATTLER_ATTACKER, BATTLE_STAT_ATTACK, 12, Basic_CheckShellSmash_End
    IfStatStageLessThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_ATTACK, 12, Basic_CheckShellSmash_End
    IfStatStageLessThan AI_BATTLER_ATTACKER, BATTLE_STAT_SPEED, 12, Basic_CheckShellSmash_End
    GoTo ScoreMinus10

Basic_CheckShellSmash_End:
    PopOrEnd

Basic_CheckGravityActive:
    // If Gravity is already active, score -10.
    IfFieldConditionsMask FIELD_CONDITION_GRAVITY, ScoreMinus10
    PopOrEnd 

Basic_CheckNaturalGift:
    // If the attacker does not have an eligible berry or the target is immune to that berry's
    // Natural Gift type, score -10.
    LoadHeldItem AI_BATTLER_ATTACKER
    IfLoadedNotInTable Basic_NaturalGiftBerries, ScoreMinus10
    IfMoveEffectivenessEquals TYPE_MULTI_IMMUNE, ScoreMinus10
    PopOrEnd 

Basic_NaturalGiftBerries:
    TableEntry ITEM_CHERI_BERRY
    TableEntry ITEM_CHESTO_BERRY
    TableEntry ITEM_PECHA_BERRY
    TableEntry ITEM_RAWST_BERRY
    TableEntry ITEM_ASPEAR_BERRY
    TableEntry ITEM_LEPPA_BERRY
    TableEntry ITEM_ORAN_BERRY
    TableEntry ITEM_PERSIM_BERRY
    TableEntry ITEM_LUM_BERRY
    TableEntry ITEM_SITRUS_BERRY
    TableEntry ITEM_FIGY_BERRY
    TableEntry ITEM_WIKI_BERRY
    TableEntry ITEM_MAGO_BERRY
    TableEntry ITEM_AGUAV_BERRY
    TableEntry ITEM_IAPAPA_BERRY
    TableEntry ITEM_RAZZ_BERRY
    TableEntry ITEM_BLUK_BERRY
    TableEntry ITEM_NANAB_BERRY
    TableEntry ITEM_WEPEAR_BERRY
    TableEntry ITEM_PINAP_BERRY
    TableEntry ITEM_POMEG_BERRY
    TableEntry ITEM_KELPSY_BERRY
    TableEntry ITEM_QUALOT_BERRY
    TableEntry ITEM_HONDEW_BERRY
    TableEntry ITEM_GREPA_BERRY
    TableEntry ITEM_TAMATO_BERRY
    TableEntry ITEM_CORNN_BERRY
    TableEntry ITEM_MAGOST_BERRY
    TableEntry ITEM_RABUTA_BERRY
    TableEntry ITEM_NOMEL_BERRY
    TableEntry ITEM_SPELON_BERRY
    TableEntry ITEM_PAMTRE_BERRY
    TableEntry ITEM_WATMEL_BERRY
    TableEntry ITEM_DURIN_BERRY
    TableEntry ITEM_BELUE_BERRY
    TableEntry ITEM_OCCA_BERRY
    TableEntry ITEM_PASSHO_BERRY
    TableEntry ITEM_WACAN_BERRY
    TableEntry ITEM_RINDO_BERRY
    TableEntry ITEM_YACHE_BERRY
    TableEntry ITEM_CHOPLE_BERRY
    TableEntry ITEM_KEBIA_BERRY
    TableEntry ITEM_SHUCA_BERRY
    TableEntry ITEM_COBA_BERRY
    TableEntry ITEM_PAYAPA_BERRY
    TableEntry ITEM_TANGA_BERRY
    TableEntry ITEM_CHARTI_BERRY
    TableEntry ITEM_KASIB_BERRY
    TableEntry ITEM_HABAN_BERRY
    TableEntry ITEM_COLBUR_BERRY
    TableEntry ITEM_BABIRI_BERRY
    TableEntry ITEM_CHILAN_BERRY
    TableEntry ITEM_LIECHI_BERRY
    TableEntry ITEM_GANLON_BERRY
    TableEntry ITEM_SALAC_BERRY
    TableEntry ITEM_PETAYA_BERRY
    TableEntry ITEM_APICOT_BERRY
    TableEntry ITEM_LANSAT_BERRY
    TableEntry ITEM_STARF_BERRY
    TableEntry ITEM_ENIGMA_BERRY
    TableEntry ITEM_MICLE_BERRY
    TableEntry ITEM_CUSTAP_BERRY
    TableEntry ITEM_JABOCA_BERRY
    TableEntry ITEM_ROWAP_BERRY
    TableEntry ITEM_ROSELI_BERRY
    TableEntry TABLE_END

Basic_CheckTailwind:
    // If Trick Room is currently active or Tailwind is already active for the attacker's side
    // of the field, score -10.
    IfFieldConditionsMask FIELD_CONDITION_TRICK_ROOM, ScoreMinus10
    IfFieldConditionsMask FIELD_CONDITION_TAILWIND_PERM, ScoreMinus10
    IfSideCondition AI_BATTLER_ATTACKER, SIDE_CONDITION_TAILWIND, ScoreMinus10
    PopOrEnd 

Basic_CheckMetalBurst:
    // If the target is immune to Metal Burst due to its typing (?), score -10.
    IfMoveEffectivenessEquals TYPE_MULTI_IMMUNE, ScoreMinus10

    // If the target moves last anyway - Stall, or a Lagging Tail/Full Incense - it will already
    // have attacked, so there is nothing left to reflect. Score -10.
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_STALL, ScoreMinus10
    LoadHeldItemEffect AI_BATTLER_DEFENDER
    IfLoadedEqualTo HOLD_EFFECT_PRIORITY_DOWN, ScoreMinus10

    // If the attacker is the one forced to move last, it is guaranteed to have been hit first,
    // so skip the speed check below.
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_STALL, Basic_CheckMetalBurst_Terminate
    LoadHeldItemEffect AI_BATTLER_ATTACKER
    IfLoadedEqualTo HOLD_EFFECT_PRIORITY_DOWN, Basic_CheckMetalBurst_Terminate

    // If the attacker moves first there is nothing to reflect and the move simply fails.
    IfSpeedCompareEqualTo COMPARE_SPEED_FASTER, ScoreMinus20
    IfSpeedCompareEqualTo COMPARE_SPEED_TIE, ScoreMinus20

Basic_CheckMetalBurst_Terminate:
    PopOrEnd 

Basic_CheckEmbargo:
    // If the target is already under the respective effect, score -10.
    IfMoveEffect AI_BATTLER_DEFENDER, MOVE_EFFECT_EMBARGO, ScoreMinus10

    // If a recyclable item for the target's side exists, terminate.
    LoadRecycleItem AI_BATTLER_DEFENDER
    IfLoadedEqualTo ITEM_NONE, Basic_CheckEmbargo_Terminate

    // If the battle is taking place in the Frontier, score -10.
    LoadBattleType 
    IfLoadedMask BATTLE_TYPE_FRONTIER, ScoreMinus10

Basic_CheckEmbargo_Terminate:
    PopOrEnd 

Basic_CheckFling:
    // If the target is immune to the move due to its typing (?), score -10.
    IfMoveEffectivenessEquals TYPE_MULTI_IMMUNE, ScoreMinus10

    // If Fling would have 0 base power, score -10.
    LoadFlingPower AI_BATTLER_ATTACKER
    IfLoadedLessThan 10, ScoreMinus10

    // If the attacker's ability is Multitype, score -10.
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_MULTITYPE, ScoreMinus10

    // Branch according to possible status effects.
    LoadHeldItemEffect AI_BATTLER_ATTACKER
    IfLoadedInTable Basic_FlingItems_Poison, Basic_FlingPoison
    IfLoadedInTable Basic_FlingItems_Burn, Basic_FlingBurn
    IfLoadedInTable Basic_FlingItems_Paralyze, Basic_FlingParalyze
    PopOrEnd 

Basic_FlingPoison:
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_SAFEGUARD, Basic_FlingPoison_AttackerChecks
    IfStatus AI_BATTLER_DEFENDER, MON_CONDITION_ANY, Basic_FlingPoison_AttackerChecks
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_POISON_HEAL, Basic_FlingPoison_AttackerChecks
    LoadTypeFrom LOAD_DEFENDER_TYPE_1
    IfLoadedEqualTo TYPE_POISON, Basic_FlingPoison_AttackerChecks
    IfLoadedEqualTo TYPE_STEEL, Basic_FlingPoison_AttackerChecks
    LoadTypeFrom LOAD_DEFENDER_TYPE_2
    IfLoadedEqualTo TYPE_POISON, Basic_FlingPoison_AttackerChecks
    IfLoadedEqualTo TYPE_STEEL, Basic_FlingPoison_AttackerChecks
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_IMMUNITY, Basic_FlingPoison_AttackerChecks
    IfLoadedEqualTo ABILITY_POISON_HEAL, Basic_FlingPoison_AttackerChecks
    IfLoadedEqualTo ABILITY_MAGIC_GUARD, Basic_FlingPoison_AttackerChecks
    PopOrEnd 

Basic_FlingPoison_AttackerChecks:
    IfSideCondition AI_BATTLER_ATTACKER, SIDE_CONDITION_SAFEGUARD, ScoreMinus5
    IfStatus AI_BATTLER_ATTACKER, MON_CONDITION_ANY, ScoreMinus5
    LoadTypeFrom LOAD_ATTACKER_TYPE_1
    IfLoadedEqualTo TYPE_POISON, ScoreMinus5
    IfLoadedEqualTo TYPE_STEEL, ScoreMinus5
    LoadTypeFrom LOAD_ATTACKER_TYPE_2
    IfLoadedEqualTo TYPE_POISON, ScoreMinus5
    IfLoadedEqualTo TYPE_STEEL, ScoreMinus5
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_KLUTZ, ScoreMinus5
    IfLoadedEqualTo ABILITY_IMMUNITY, ScoreMinus5
    IfLoadedEqualTo ABILITY_POISON_HEAL, ScoreMinus5
    IfLoadedEqualTo ABILITY_MAGIC_GUARD, ScoreMinus5
    IfLoadedEqualTo ABILITY_GUTS, ScoreMinus5
    AddToMoveScore 3
    PopOrEnd 

Basic_FlingBurn:
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_SAFEGUARD, Basic_FlingBurn_AttackerChecks
    IfStatus AI_BATTLER_DEFENDER, MON_CONDITION_ANY, Basic_FlingBurn_AttackerChecks
    LoadTypeFrom LOAD_DEFENDER_TYPE_1
    IfLoadedEqualTo TYPE_FIRE, Basic_FlingBurn_AttackerChecks
    LoadTypeFrom LOAD_DEFENDER_TYPE_2
    IfLoadedEqualTo TYPE_FIRE, Basic_FlingBurn_AttackerChecks
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_MAGIC_GUARD, Basic_FlingBurn_AttackerChecks
    IfLoadedEqualTo ABILITY_WATER_VEIL, Basic_FlingBurn_AttackerChecks
    IfLoadedEqualTo ABILITY_WATER_BUBBLE, Basic_FlingBurn_AttackerChecks
    PopOrEnd 

Basic_FlingBurn_AttackerChecks:
    IfSideCondition AI_BATTLER_ATTACKER, SIDE_CONDITION_SAFEGUARD, ScoreMinus5
    IfStatus AI_BATTLER_ATTACKER, MON_CONDITION_ANY, ScoreMinus5
    LoadTypeFrom LOAD_ATTACKER_TYPE_1
    IfLoadedEqualTo TYPE_FIRE, ScoreMinus5
    LoadTypeFrom LOAD_ATTACKER_TYPE_2
    IfLoadedEqualTo TYPE_FIRE, ScoreMinus5
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_KLUTZ, ScoreMinus5
    IfLoadedEqualTo ABILITY_MAGIC_GUARD, ScoreMinus5
    IfLoadedEqualTo ABILITY_WATER_VEIL, ScoreMinus5
    IfLoadedEqualTo ABILITY_WATER_BUBBLE, ScoreMinus5
    IfLoadedEqualTo ABILITY_GUTS, ScoreMinus5
    AddToMoveScore 3
    PopOrEnd 

Basic_FlingParalyze:
    // If the target cannot be Paralyzed, score -5.
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_SAFEGUARD, ScoreMinus5
    IfStatus AI_BATTLER_DEFENDER, MON_CONDITION_ANY, ScoreMinus5
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_LIMBER, ScoreMinus5
    PopOrEnd 

Basic_FlingItems_Poison:
    TableEntry HOLD_EFFECT_PSN_USER
    TableEntry HOLD_EFFECT_STRENGTHEN_POISON
    TableEntry TABLE_END

Basic_FlingItems_Burn:
    TableEntry HOLD_EFFECT_BRN_USER
    TableEntry TABLE_END

Basic_FlingItems_Paralyze:
    TableEntry HOLD_EFFECT_PIKA_SPATK_UP
    TableEntry TABLE_END

Basic_CheckCanPsychoShift:
    // If the attacker does not have a status condition or the target already has a status
    // condition, score -10.
    IfNotStatus AI_BATTLER_ATTACKER, MON_CONDITION_ANY, ScoreMinus10
    IfStatus AI_BATTLER_DEFENDER, MON_CONDITION_ANY, ScoreMinus10

    // If the target is protected by Safeguard, score -10.
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_SAFEGUARD, ScoreMinus10

    // Branch according to the attacker's status condition.
    IfStatus AI_BATTLER_ATTACKER, MON_CONDITION_ANY_POISON, Basic_PsychoShift_Poison
    IfStatus AI_BATTLER_ATTACKER, MON_CONDITION_BURN, Basic_PsychoShift_Burn
    IfStatus AI_BATTLER_ATTACKER, MON_CONDITION_PARALYSIS, Basic_PsychoShift_Paralysis
    GoTo Basic_PsychoShift_Terminate

Basic_PsychoShift_Poison:
    // If the attacker has Poison Heal, score -10.
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_POISON_HEAL, ScoreMinus10

    // If the target is immune to the effects of poison for any reason, score -10.
    LoadTypeFrom LOAD_DEFENDER_TYPE_1
    IfLoadedEqualTo TYPE_POISON, ScoreMinus10
    IfLoadedEqualTo TYPE_STEEL, ScoreMinus10
    LoadTypeFrom LOAD_DEFENDER_TYPE_2
    IfLoadedEqualTo TYPE_POISON, ScoreMinus10
    IfLoadedEqualTo TYPE_STEEL, ScoreMinus10
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_IMMUNITY, ScoreMinus10
    IfLoadedEqualTo ABILITY_POISON_HEAL, ScoreMinus10
    IfLoadedEqualTo ABILITY_MAGIC_GUARD, ScoreMinus10
    GoTo Basic_PsychoShift_Terminate

Basic_PsychoShift_Burn:
    // If the target is immune to the effects of burn for any reason, score -10.
    LoadTypeFrom LOAD_DEFENDER_TYPE_1
    IfLoadedEqualTo TYPE_FIRE, ScoreMinus10
    LoadTypeFrom LOAD_DEFENDER_TYPE_2
    IfLoadedEqualTo TYPE_FIRE, ScoreMinus10
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_MAGIC_GUARD, ScoreMinus10
    IfLoadedEqualTo ABILITY_WATER_VEIL, ScoreMinus10
    IfLoadedEqualTo ABILITY_WATER_BUBBLE, ScoreMinus10
    GoTo Basic_PsychoShift_Terminate

Basic_PsychoShift_Paralysis:
    // If the target's ability is Limber, score -10.
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_LIMBER, ScoreMinus10

Basic_PsychoShift_Terminate:
    PopOrEnd 

Basic_CheckHealBlock:
    // If the target is already under the effect, score -10.
    IfMoveEffect AI_BATTLER_DEFENDER, MOVE_EFFECT_HEAL_BLOCK, ScoreMinus10
    PopOrEnd 

Basic_CheckGastroAcid:
    // If the target is already under the effect, score -10.
    IfMoveEffect AI_BATTLER_DEFENDER, MOVE_EFFECT_ABILITY_SUPPRESSED, ScoreMinus10

    // If the target has any of the following abilities, score -10.
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_MULTITYPE, ScoreMinus10
    IfLoadedEqualTo ABILITY_TRUANT, ScoreMinus10
    IfLoadedEqualTo ABILITY_SLOW_START, ScoreMinus10
    IfLoadedEqualTo ABILITY_STENCH, ScoreMinus10
    IfLoadedEqualTo ABILITY_RUN_AWAY, ScoreMinus10
    IfLoadedEqualTo ABILITY_PICKUP, ScoreMinus10
    IfLoadedEqualTo ABILITY_HONEY_GATHER, ScoreMinus10
    PopOrEnd 

Basic_CheckCopycat:
    // If it's the first turn of the battle and the attacker is faster than its target, score -10.
    LoadTurnCount 
    IfLoadedNotEqualTo 0, Basic_CheckCopycat_Terminate
    IfSpeedCompareEqualTo COMPARE_SPEED_FASTER, ScoreMinus10

Basic_CheckCopycat_Terminate:
    PopOrEnd 

Basic_CheckLastResort:
    // If the attacker has yet to use all of its other moves, score -10.
    IfCanUseLastResort AI_BATTLER_ATTACKER, Basic_CheckLastResort_Terminate
    AddToMoveScore -10

Basic_CheckLastResort_Terminate:
    PopOrEnd 

Basic_CheckWorrySeed:
    // If the target has any of the following abilities, score -10.
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_TRUANT, ScoreMinus10
    IfLoadedEqualTo ABILITY_INSOMNIA, ScoreMinus10
    IfLoadedEqualTo ABILITY_VITAL_SPIRIT, ScoreMinus10
    IfLoadedEqualTo ABILITY_SWEET_VEIL, ScoreMinus10
    IfLoadedEqualTo ABILITY_MULTITYPE, ScoreMinus10

    // If the target is asleep and does not know either Sleep Talk or Snore, score -10.
    IfNotStatus AI_BATTLER_DEFENDER, MON_CONDITION_SLEEP, Basic_CheckWorrySeed_Terminate
    IfMoveKnown AI_BATTLER_DEFENDER, MOVE_SLEEP_TALK, Basic_CheckWorrySeed_Terminate
    IfMoveKnown AI_BATTLER_DEFENDER, MOVE_SNORE, Basic_CheckWorrySeed_Terminate
    AddToMoveScore -10

Basic_CheckWorrySeed_Terminate:
    PopOrEnd 

Basic_CheckToxicSpikes:
    // If the target's side of the field already has 2 layers of Toxic Spikes, score -10.
    LoadSpikesLayers AI_BATTLER_DEFENDER, SIDE_CONDITION_TOXIC_SPIKES
    IfLoadedEqualTo 2, ScoreMinus10

    // If the target is the last battler, score -10.
    CountAlivePartyBattlers AI_BATTLER_DEFENDER
    IfLoadedEqualTo 0, ScoreMinus10
    PopOrEnd 
    PopOrEnd 

Basic_CheckAquaRing:
    // If the attacker is already under the effect, score -10.
    IfMoveEffect AI_BATTLER_ATTACKER, MOVE_EFFECT_AQUA_RING, ScoreMinus10
    PopOrEnd 

Basic_CheckMagnetRise:
    // If the attacker is already under the effect, score -10.
    IfMoveEffect AI_BATTLER_ATTACKER, MOVE_EFFECT_MAGNET_RISE, ScoreMinus10

    // If the attacker's ability is Levitate, score -10.
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_LEVITATE, ScoreMinus10

    // If either of the attacker's types are Flying, score -10.
    LoadTypeFrom LOAD_ATTACKER_TYPE_1
    IfLoadedEqualTo TYPE_FLYING, ScoreMinus10
    LoadTypeFrom LOAD_ATTACKER_TYPE_2
    IfLoadedEqualTo TYPE_FLYING, ScoreMinus10
    PopOrEnd 

Basic_CheckDefog:
    // If the target's Evasion is not at -6 or their side of the field has Light Screen or
    // Reflect, ignore all other checks.
    IfStatStageNotEqualTo AI_BATTLER_DEFENDER, BATTLE_STAT_EVASION, 0, Basic_CheckDefog_Terminate
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_LIGHT_SCREEN, Basic_CheckDefog_Terminate
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_REFLECT, Basic_CheckDefog_Terminate

    // If the current weather is Deep Fog, ignore all other checks.
    LoadCurrentWeather 
    IfLoadedEqualTo AI_WEATHER_DEEP_FOG, Basic_CheckDefog_Terminate

    // If the target is on their last Pokemon, score -10.
    CountAlivePartyBattlers AI_BATTLER_DEFENDER
    IfLoadedEqualTo 0, ScoreMinus10

    // If the target's side of the field has none of Spikes, Stealth Rock, or Toxic Spikes
    // active, score -10.
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_SPIKES, Basic_CheckDefog_Terminate
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_STEALTH_ROCK, Basic_CheckDefog_Terminate
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_TOXIC_SPIKES, Basic_CheckDefog_Terminate
    GoTo ScoreMinus10

Basic_CheckDefog_Terminate:
    PopOrEnd 

Basic_CheckTrickRoom:
    // If the attacker is faster than the target, score -10.
    // Treat speed ties as being faster than the target.
    IfSpeedCompareEqualTo COMPARE_SPEED_FASTER, ScoreMinus10
    IfSpeedCompareEqualTo COMPARE_SPEED_TIE, ScoreMinus10
    PopOrEnd 

Basic_CheckCaptivate:
    // If the target's ability is any of Oblivious, Clear Body, or White Smoke and the attacker's
    // ability is not Mold Breaker, score -10.
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_MOLD_BREAKER, Basic_CheckCaptivate_CheckGender
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_OBLIVIOUS, ScoreMinus10
    IfLoadedEqualTo ABILITY_CLEAR_BODY, ScoreMinus10
    IfLoadedEqualTo ABILITY_WHITE_SMOKE, ScoreMinus10

Basic_CheckCaptivate_CheckGender:
    // If the target and the attacker share gender or the target has no gender, score -10.
    LoadGender AI_BATTLER_ATTACKER
    IfLoadedEqualTo GENDER_MALE, Basic_CheckCaptivate_CheckMale
    IfLoadedEqualTo GENDER_FEMALE, Basic_CheckCaptivate_CheckFemale
    GoTo ScoreMinus10

Basic_CheckCaptivate_CheckMale:
    LoadGender AI_BATTLER_DEFENDER
    IfLoadedEqualTo GENDER_FEMALE, Basic_CheckCaptivate_CheckStatStage
    GoTo ScoreMinus10

Basic_CheckCaptivate_CheckFemale:
    LoadGender AI_BATTLER_DEFENDER
    IfLoadedEqualTo GENDER_MALE, Basic_CheckCaptivate_CheckStatStage
    GoTo ScoreMinus10

Basic_CheckCaptivate_CheckStatStage:
    // If the target is already at -6, score -10.
    IfStatStageLessThan AI_BATTLER_DEFENDER, BATTLE_STAT_SP_ATTACK, 1, ScoreMinus10
    PopOrEnd 

Basic_CheckStealthRock:
    // If the target's side of the field is already under the effect of Stealth Rock, score -10.
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_STEALTH_ROCK, ScoreMinus10

    // If the target is on their last Pokemon, score -10.
    CountAlivePartyBattlers AI_BATTLER_DEFENDER
    IfLoadedEqualTo 0, ScoreMinus10
    PopOrEnd 

Basic_CheckLunarDance:
    // Start at -20
    AddToMoveScore -20

    // If the attacker is on their last Pokemon, score additional -10.
    CountAlivePartyBattlers AI_BATTLER_ATTACKER
    IfLoadedEqualTo 0, ScoreMinus10

    // If none of the attacker's party members are statused, at less than 100% HP, or at
    // less than full PP on all of their moves, score -10.
    IfAnyPartyMemberIsWounded AI_BATTLER_ATTACKER, Basic_CheckLunarDance_Terminate
    IfPartyMemberStatus AI_BATTLER_ATTACKER, MON_CONDITION_ANY, Basic_CheckLunarDance_Terminate
    IfAnyPartyMemberUsedPP AI_BATTLER_ATTACKER, Basic_CheckLunarDance_Terminate
    GoTo ScoreMinus10

Basic_CheckLunarDance_Terminate:
    PopOrEnd

Basic_CheckGrowth:
    // If the attacker's ability is Simple and either Attack or SpAttack are already at
    // +3, score -10. Otherwise score -10 only once both are maxed out.
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_CONTRARY, ScoreMinus10
    IfLoadedNotEqualTo ABILITY_SIMPLE, Basic_CheckGrowth_NoSimple
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_ATTACK, 8, ScoreMinus10
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_ATTACK, 8, ScoreMinus10
    PopOrEnd

Basic_CheckGrowth_NoSimple:
    IfStatStageNotEqualTo AI_BATTLER_ATTACKER, BATTLE_STAT_ATTACK, 12, Basic_CheckGrowth_Terminate
    IfStatStageEqualTo AI_BATTLER_ATTACKER, BATTLE_STAT_SP_ATTACK, 12, ScoreMinus10

Basic_CheckGrowth_Terminate:
    PopOrEnd

Basic_CheckCharge:
    // Charge persists until it is spent, so re-applying it while it is already up wastes
    // a turn. Otherwise fall through to the usual SpDefense saturation check.
    IfMoveEffect AI_BATTLER_ATTACKER, MOVE_EFFECT_CHARGE, ScoreMinus10
    GoTo Basic_CheckHighStatStage_SpDefense

Basic_CheckTaunt:
    // If the target is already taunted, score -10.
    IfTargetIsTaunted ScoreMinus10
    PopOrEnd

Basic_CheckImprison:
    // If the attacker has already used Imprison, score -10.
    IfMoveEffect AI_BATTLER_ATTACKER, MOVE_EFFECT_IMPRISON, ScoreMinus10
    PopOrEnd

Basic_CheckTransform:
    // Transforming into a mon which is itself a copy, or transforming a second time, both
    // accomplish nothing. Score -10.
    IfVolatileStatus AI_BATTLER_ATTACKER, VOLATILE_CONDITION_TRANSFORM, ScoreMinus10
    IfVolatileStatus AI_BATTLER_DEFENDER, VOLATILE_CONDITION_TRANSFORM, ScoreMinus10
    PopOrEnd

Basic_CheckStickyWeb:
    // If the target's side of the field is already under the effect of Sticky Web, or the
    // target has nothing left to switch to, score -10.
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_STICKY_WEB, ScoreMinus10
    CountAlivePartyBattlers AI_BATTLER_DEFENDER
    IfLoadedEqualTo 0, ScoreMinus10
    PopOrEnd

Basic_CheckSteelBeam:
    // Steel Beam costs the user half of their maximum HP on hit, unless they have Magic
    // Guard. Above half HP the cost is survivable, so leave the score alone.
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_MAGIC_GUARD, Basic_CheckSteelBeam_Terminate
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER, 50, Basic_CheckSteelBeam_Terminate

    // Below half HP this faints the user; if there is nobody left behind them, score -10.
    CountAlivePartyBattlers AI_BATTLER_ATTACKER
    IfLoadedEqualTo 0, ScoreMinus10
    GoTo ScoreMinus5

Basic_CheckSteelBeam_Terminate:
    PopOrEnd

Basic_CheckEndure:
    // Endure shares Protect's diminishing success chance, so score it down the deeper we
    // already are into a chain of protection moves.
    LoadProtectChain AI_BATTLER_ATTACKER
    IfLoadedGreaterThan 1, ScoreMinus10
    IfLoadedEqualTo 1, ScoreMinus2
    PopOrEnd

ScoreMinus1:
    AddToMoveScore -1
    PopOrEnd 

ScoreMinus2:
    AddToMoveScore -2
    PopOrEnd 

ScoreMinus3:
    AddToMoveScore -3
    PopOrEnd 

ScoreMinus5:
    AddToMoveScore -5
    PopOrEnd 

ScoreMinus6: // unused
    AddToMoveScore -6
    PopOrEnd 

ScoreMinus8:
    AddToMoveScore -8
    PopOrEnd 

ScoreMinus10:
    AddToMoveScore -10
    PopOrEnd 

ScoreMinus12:
    AddToMoveScore -12
    PopOrEnd 

ScoreMinus20:
    AddToMoveScore -20
    PopOrEnd

ScoreMinus30:
    AddToMoveScore -30
    PopOrEnd 

ScorePlus1:
    AddToMoveScore 1
    PopOrEnd 

ScorePlus2:
    AddToMoveScore 2
    PopOrEnd 

ScorePlus3:
    AddToMoveScore 3
    PopOrEnd 

ScorePlus5:
    AddToMoveScore 5
    PopOrEnd 

ScorePlus6:
    AddToMoveScore 6
    PopOrEnd

ScorePlus7:
    AddToMoveScore 7
    PopOrEnd

ScorePlus8:
    AddToMoveScore 8
    PopOrEnd

ScorePlus9:
    AddToMoveScore 9
    PopOrEnd

ScorePlus10:
    AddToMoveScore 10
    PopOrEnd 

Expert_Main:
    // This flag will never target its partner.
    IfTargetIsPartner Terminate

    // Evaluate moves which match a known effect according to this jump table.
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STATUS_SLEEP, Expert_StatusSleep
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STATUS_SLEEP_NEXT_TURN, Expert_StatusSleep
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_RECOVER_HALF_DAMAGE_DEALT, Expert_DrainMove
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_HALVE_DEFENSE, Expert_Explosion
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_HALVE_SP_DEFENSE, Expert_Explosion
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_COPY_MOVE, Expert_MirrorMove
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ATK_UP, Expert_Setup
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DEF_UP, Expert_Setup
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_EVA_UP, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_BYPASS_ACCURACY, Expert_BypassAccuracyMove
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ATK_DOWN, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DEF_DOWN, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SPEED_DOWN, Expert_StatusSpeedDown
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_ATK_DOWN, Expert_StatusSpAttackDown
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ACC_DOWN, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_EVA_DOWN, Expert_StatusEvasionDown
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_RESET_STAT_CHANGES, Expert_Haze
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_BIDE, Expert_Bide
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_FORCE_SWITCH, Expert_ForceSwitch
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_CONVERSION, Expert_Conversion
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_RESTORE_HALF_HP, Expert_Recovery
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_HEAL_ALLIES_QUARTER, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STATUS_BADLY_POISON, Expert_StatusPoison
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SET_LIGHT_SCREEN, Expert_Screen
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_AURORA_VEIL, Expert_AuroraVeil
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_REST, Expert_Rest
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ONE_HIT_KO, Expert_OHKOMove
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_CHARGE_TURN_HIGH_CRIT, Expert_ChargeTurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_BIND_HIT, Expert_BindingMove
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DOUBLE_POWER_EACH_TURN_LOCK_INTO, Expert_Rollout
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STATUS_CONFUSE, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_NATURE_POWER, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ATK_UP_2, Expert_Setup
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DEF_UP_2, Expert_Setup
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SPEED_UP_2, Expert_SetupSpeed
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_ATK_UP_2, Expert_Setup
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_DEF_UP_2, Expert_Setup
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_CRIT_UP_2, Expert_FocusEnergy
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_TRANSFORM, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ATK_DOWN_2, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DEF_DOWN_2, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SPEED_DOWN_2, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_ATK_DOWN_2, Expert_StatusSpAttackDown
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_DEF_DOWN_2, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_EVA_DOWN_2, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ACC_DOWN_2, Expert_StatusEvasionDown
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SET_REFLECT, Expert_Screen
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STATUS_POISON, Expert_StatusPoison
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STATUS_BURN, Expert_StatusBurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STATUS_PARALYZE, Expert_StatusParalyze
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_PARALYZE_HIT, Expert_StatusParalyzeHit
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ATK_UP_2_STATUS_CONFUSION, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_LOWER_SPEED_HIT, Expert_SpeedDownOnHit
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_LOWER_ATTACK_HIT, Expert_AttackDropOnHit
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_LOWER_SP_ATK_HIT, Expert_AttackDropOnHit
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_BOOST_ATTACK_ON_KO, Expert_FellStinger
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_CHARGE_TURN_HIGH_CRIT_FLINCH, Expert_ChargeTurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_PRIORITY_NEG_1_BYPASS_ACCURACY, Expert_SlowMove
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DOUBLE_POWER_IF_HIT, Expert_SlowMove
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DRAGON_TAIL, Expert_SlowMove
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_FLEE_FROM_WILD_BATTLE, Expert_SlowMove
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SET_SUBSTITUTE, Expert_Substitute
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STATUS_LEECH_SEED, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DISABLE, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_COUNTER, Expert_CounterMove
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ENCORE, Expert_Encore
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_AVERAGE_HP, Expert_PainSplit
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_NEXT_ATTACK_ALWAYS_HITS, Expert_LockOn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_USE_RANDOM_LEARNED_MOVE_SLEEP, Expert_SleepTalk
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_KO_MON_THAT_DEFEATED_USER, Expert_DestinyBond
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_CURE_PARTY_STATUS, Expert_HealBell
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_PREVENT_ESCAPE, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_EVA_UP_2_MINIMIZE, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_CURSE, Expert_Curse
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_RAISE_ATTACK_HIT, Expert_PowerUpPunch
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STOCKPILE, Expert_Setup
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_PROTECT, Expert_Protect
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_PROTECT_HURT_ON_CONTACT, Expert_Protect
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_PROTECT_LOWER_SPEED_CONTACT, Expert_Protect
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SET_SPIKES, Expert_Spikes
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_FORESIGHT, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_POWDER, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_COPY_MOVE_FOR_BATTLE, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DECREASE_LAST_MOVE_PP, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SURVIVE_WITH_1_HP, Expert_Endure
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_PASS_STATS_AND_STATUS, Expert_BatonPass
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_HIT_BEFORE_SWITCH, Expert_Pursuit
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_HEAL_HALF_MORE_IN_SUN, Expert_Synthesis
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_UNUSED_133, Expert_Synthesis
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_UNUSED_134, Expert_Synthesis
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_WEATHER_SANDSTORM, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_WEATHER_RAIN, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_WEATHER_SUN, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_MAX_ATK_LOSE_HALF_MAX_HP, Expert_BellyDrum
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_COPY_STAT_CHANGES, Expert_PsychUp
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_MIRROR_COAT, Expert_CounterMove
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_CHARGE_TURN_DEF_UP, Expert_ChargeTurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_CHARGE_TURN_SP_ATK_UP, Expert_ChargeTurn
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_UNUSED_157, Expert_Recovery
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ALWAYS_FLINCH_FIRST_TURN_ONLY, Expert_FakeOut
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SWALLOW, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_WEATHER_HAIL, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_ATK_UP_CAUSE_CONFUSION, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_FAINT_AND_ATK_SP_ATK_DOWN_2, Expert_Memento
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_HIT_LAST_WHIFF_IF_HIT, Expert_SlowMove
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SWITCH_HELD_ITEMS, Expert_Trick
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SWITCH_LOWER_ATKS, Expert_PartingShot
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SWITCH_HIT, Expert_SwitchHit
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_COPY_ABILITY, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_GROUND_TRAP_USER_CONTINUOUS_HEAL, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_APPLY_MAGIC_COAT, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_RECYCLE, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_REMOVE_SCREENS, Expert_BrickBreak
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SET_HP_EQUAL_TO_USER, Expert_Endeavor
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SWITCH_ABILITIES, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_HEAL_STATUS, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STEAL_STATUS_MOVE, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_TAUNT, Expert_Taunt
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ATK_DEF_DOWN, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DEF_SPD_UP, Expert_Setup
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ATK_DEF_UP, Expert_Setup
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_ATK_SP_DEF_UP, Expert_Setup
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ATK_SPD_UP, Expert_Setup
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_QUIVER_DANCE, Expert_Setup
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SHELL_SMASH, Expert_Setup
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_ATK_UP_3, Expert_Setup
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ATK_SP_ATK_UP, Expert_Setup
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_HEAL_HALF_REMOVE_FLYING_TYPE, Expert_Recovery
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_GRAVITY, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DOUBLE_SPEED_3_TURNS, Expert_Tailwind
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_METAL_BURST, Expert_MetalBurst
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_PREVENT_ITEM_USE, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_FLING, Expert_Fling
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_TRANSFER_STATUS, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_PREVENT_HEALING, Expert_HealBlock
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SUPRESS_ABILITY, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_USE_LAST_USED_MOVE, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_USE_MOVE_FIRST, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SET_ABILITY_TO_INSOMNIA, Expert_WorrySeed
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_HIT_FIRST_IF_TARGET_ATTACKING, Expert_SuckerPunch
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_TOXIC_SPIKES, Expert_ToxicSpikes
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SWAP_STAT_CHANGES, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_RESTORE_HP_EVERY_TURN, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_GIVE_GROUND_IMMUNITY, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_REMOVE_HAZARDS_SCREENS_EVA_DOWN, Expert_Defog
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_TRICK_ROOM, Expert_TrickRoom
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_ATK_DOWN_2_OPPOSITE_GENDER, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STEALTH_ROCK, Expert_Hazards
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STICKY_WEB, Expert_StickyWeb
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_MAKE_SHARED_MOVES_UNUSEABLE, Expert_Imprison
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_FAINT_FULL_RESTORE_NEXT_MON, Expert_HealingWish
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_LOWER_SP_DEF_2_HIT, Expert_AcidSpray

    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_PREVENT_STAT_REDUCTION, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_CALL_RANDOM_MOVE, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_INFATUATE, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_PREVENT_STATUS, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DEF_UP_DOUBLE_ROLLOUT_POWER, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_TORMENT, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_DEF_UP_DOUBLE_ELECTRIC_POWER, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_USE_RANDOM_ALLY_MOVE, Expert_StatusMoveBonus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_CONFUSE_ALL, Expert_StatusMoveBonus

    // All other moves have no additional logic.
    PopOrEnd 

Expert_StatusMoveBonus:
    // Status moves which get no judgement of their own beyond whatever Basic already applied.
    // +6 puts them level with the bonus EvalAttack hands the best damaging move 80% of the time,
    // so they compete with attacking rather than being crowded out by it.
    AddToMoveScore 6
    PopOrEnd

Expert_StatusSleep:
    AddToMoveScore 6
    IfRandomGreaterThan 63, Expert_StatusSleep_End
    IfAttackerCanKO Expert_StatusSleep_End
    IfStatus AI_BATTLER_DEFENDER, MON_CONDITION_ANY, Expert_StatusSleep_End
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_SAFEGUARD, Expert_StatusSleep_End
    IfFieldConditionsMask FIELD_CONDITION_UPROAR, Expert_StatusSleep_End
    IfMoveEffect AI_BATTLER_DEFENDER, MOVE_EFFECT_YAWN, Expert_StatusSleep_End
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_INSOMNIA, Expert_StatusSleep_End
    IfLoadedEqualTo ABILITY_VITAL_SPIRIT, Expert_StatusSleep_End
    IfLoadedEqualTo ABILITY_SWEET_VEIL, Expert_StatusSleep_End
    AddToMoveScore 1
    IfMoveEffectKnown AI_BATTLER_ATTACKER, BATTLE_EFFECT_RECOVER_DAMAGE_SLEEP, Expert_StatusSleep_CheckTargetCanAct
    IfMoveEffectKnown AI_BATTLER_ATTACKER, BATTLE_EFFECT_STATUS_NIGHTMARE, Expert_StatusSleep_CheckTargetCanAct
    GoTo Expert_StatusSleep_CheckHex

Expert_StatusSleep_CheckTargetCanAct:
    IfMoveKnown AI_BATTLER_DEFENDER, MOVE_SNORE, Expert_StatusSleep_CheckHex
    IfMoveKnown AI_BATTLER_DEFENDER, MOVE_SLEEP_TALK, Expert_StatusSleep_CheckHex
    AddToMoveScore 1

Expert_StatusSleep_CheckHex:
    IfMoveKnown AI_BATTLER_ATTACKER, MOVE_HEX, Expert_StatusSleep_ScorePlus1
    LoadBattleType 
    IfLoadedNotMask BATTLE_TYPE_DOUBLES, Expert_StatusSleep_End
    IfMoveKnown AI_BATTLER_ATTACKER_PARTNER, MOVE_HEX, Expert_StatusSleep_ScorePlus1
    PopOrEnd

Expert_StatusSleep_ScorePlus1:
    AddToMoveScore 1

Expert_StatusSleep_End:
    PopOrEnd

Expert_DrainMove:
    // If the target is immune to or resists the move, ~80.5% chance of score -3.
    IfMoveEffectivenessEquals TYPE_MULTI_IMMUNE, Expert_DrainMove_TryScoreMinus3
    IfMoveEffectivenessEquals TYPE_MULTI_HALF_DAMAGE, Expert_DrainMove_TryScoreMinus3
    IfMoveEffectivenessEquals TYPE_MULTI_QUARTER_DAMAGE, Expert_DrainMove_TryScoreMinus3
    GoTo Expert_DrainMove_End

Expert_DrainMove_TryScoreMinus3:
    IfRandomLessThan 50, Expert_DrainMove_End
    AddToMoveScore -3

Expert_DrainMove_End:
    PopOrEnd 

Expert_Explosion:
    CountAlivePartyBattlers AI_BATTLER_ATTACKER
    IfLoadedNotEqualTo 0, Expert_Explosion_Score
    CountAlivePartyBattlers AI_BATTLER_DEFENDER
    IfLoadedNotEqualTo 0, Expert_Explosion_End

Expert_Explosion_Score:
    IfHPPercentLessThan AI_BATTLER_ATTACKER, 10, ScorePlus10
    IfHPPercentLessThan AI_BATTLER_ATTACKER, 33, Expert_Explosion_TryScorePlus8
    IfHPPercentLessThan AI_BATTLER_ATTACKER, 66, Expert_Explosion_CoinFlipScorePlus7
    IfRandomLessThan 13, ScorePlus7
    PopOrEnd

Expert_Explosion_TryScorePlus8:
    IfRandomLessThan 179, ScorePlus8
    PopOrEnd

Expert_Explosion_CoinFlipScorePlus7:
    IfRandomLessThan 128, ScorePlus7

Expert_Explosion_End:
    PopOrEnd

Expert_Memento:
    CountAlivePartyBattlers AI_BATTLER_ATTACKER
    IfLoadedEqualTo 0, Expert_Memento_End
    AddToMoveScore 6
    IfHPPercentLessThan AI_BATTLER_ATTACKER, 10, ScorePlus10
    IfHPPercentLessThan AI_BATTLER_ATTACKER, 33, Expert_Explosion_TryScorePlus8
    IfHPPercentLessThan AI_BATTLER_ATTACKER, 66, Expert_Explosion_CoinFlipScorePlus7
    IfRandomLessThan 13, ScorePlus7

Expert_Memento_End:
    PopOrEnd

Expert_MirrorMove:
    // If the attacker is faster than its target and the last-used move by that target is in the below
    // list, 50% chance of score +2.
    //
    // Otherwise, if the last-used move by the target is *not* in the table, 68.75% chance of score -1.
    IfSpeedCompareEqualTo COMPARE_SPEED_SLOWER, Expert_MirrorMove_TryScoreMinus1
    LoadBattlerPreviousMove AI_BATTLER_DEFENDER
    IfLoadedNotInTable Expert_MirrorMove_MoveTable, Expert_MirrorMove_TryScoreMinus1
    IfRandomLessThan 128, Expert_MirrorMove_End
    AddToMoveScore 2
    GoTo Expert_MirrorMove_End

Expert_MirrorMove_TryScoreMinus1:
    LoadBattlerPreviousMove AI_BATTLER_DEFENDER
    IfLoadedInTable Expert_MirrorMove_MoveTable, Expert_MirrorMove_End
    IfRandomLessThan 80, Expert_MirrorMove_End
    AddToMoveScore -1

Expert_MirrorMove_End:
    PopOrEnd 

Expert_MirrorMove_MoveTable:
    TableEntry MOVE_SLEEP_POWDER
    TableEntry MOVE_LOVELY_KISS
    TableEntry MOVE_SPORE
    TableEntry MOVE_HYPNOSIS
    TableEntry MOVE_SING
    TableEntry MOVE_GRASS_WHISTLE
    TableEntry MOVE_SHADOW_PUNCH
    TableEntry MOVE_SAND_ATTACK
    TableEntry MOVE_SMOKE_SCREEN
    TableEntry MOVE_TOXIC
    TableEntry MOVE_SHEER_COLD
    TableEntry MOVE_CROSS_CHOP
    TableEntry MOVE_AEROBLAST
    TableEntry MOVE_CONFUSE_RAY
    TableEntry MOVE_SWEET_KISS
    TableEntry MOVE_SCREECH
    TableEntry MOVE_COTTON_SPORE
    TableEntry MOVE_SCARY_FACE
    TableEntry MOVE_FAKE_TEARS
    TableEntry MOVE_METAL_SOUND
    TableEntry MOVE_THUNDER_WAVE
    TableEntry MOVE_GLARE
    TableEntry MOVE_POISON_POWDER
    TableEntry MOVE_SHADOW_BALL
    TableEntry MOVE_DYNAMIC_PUNCH
    TableEntry MOVE_HYPER_BEAM
    TableEntry MOVE_EXTREME_SPEED
    TableEntry MOVE_ATTRACT
    TableEntry MOVE_SWAGGER
    TableEntry MOVE_TORMENT
    TableEntry MOVE_FLATTER
    TableEntry MOVE_TRICK
    TableEntry MOVE_SUPERPOWER
    TableEntry MOVE_SKILL_SWAP
    TableEntry MOVE_PSYCHO_SHIFT
    TableEntry MOVE_SPIKY_SHIELD
    TableEntry MOVE_SUCKER_PUNCH
    TableEntry MOVE_HEART_SWAP
    TableEntry MOVE_CAPTIVATE
    TableEntry MOVE_DARK_VOID
    TableEntry TABLE_END







Expert_BindingMove:
    // Trapping locks the target in and chips it every turn it stays there, so it competes with
    // the best damaging move rather than sitting under it.
    IfRandomLessThan 205, ScorePlus6
    GoTo ScorePlus8

Expert_Rollout:
    // Rollout snowballs as long as it keeps connecting, and Basic already rules out the cases
    // where it cannot.
    GoTo ScorePlus7

Expert_SuckerPunch:
    // A repeated Sucker Punch is the easiest thing in the game to play around, so back off from
    // using it twice running whether or not the first one landed.
    LoadBattlerPreviousMove AI_BATTLER_ATTACKER
    IfLoadedNotEqualTo MOVE_SUCKER_PUNCH, Expert_SuckerPunch_End
    IfRandomLessThan 128, Expert_SuckerPunch_End
    AddToMoveScore -20

Expert_SuckerPunch_End:
    PopOrEnd

Expert_Spikes:
    // A layer already down means the next one buys less.
    LoadSpikesLayers AI_BATTLER_DEFENDER, SIDE_CONDITION_SPIKES
    IfLoadedEqualTo 0, Expert_Hazards
    AddToMoveScore -1
    GoTo Expert_Hazards

Expert_ToxicSpikes:
    LoadSpikesLayers AI_BATTLER_DEFENDER, SIDE_CONDITION_TOXIC_SPIKES
    IfLoadedEqualTo 0, Expert_Hazards
    AddToMoveScore -1

Expert_Hazards:
    // Hazards pay off over the switches still to come, so they are worth the most on the turn
    // the AI comes in and worth less every turn after that.
    LoadIsFirstTurnInBattle AI_BATTLER_ATTACKER
    IfLoadedNotEqualTo FALSE, Expert_Hazards_FirstTurn
    IfRandomLessThan 64, ScorePlus6
    GoTo ScorePlus7

Expert_Hazards_FirstTurn:
    IfRandomLessThan 64, ScorePlus8
    GoTo ScorePlus9

Expert_StickyWeb:
    // Sticky Web scores higher than the other hazards: it pays out on the switch itself rather
    // than only chipping.
    LoadIsFirstTurnInBattle AI_BATTLER_ATTACKER
    IfLoadedNotEqualTo FALSE, Expert_StickyWeb_FirstTurn
    IfRandomLessThan 64, ScorePlus6
    GoTo ScorePlus9

Expert_StickyWeb_FirstTurn:
    IfRandomLessThan 64, ScorePlus9
    AddToMoveScore 12
    PopOrEnd

Expert_Imprison:
    // Imprison does nothing at all unless the two sides actually share a move.
    IfBattlersShareMove ScorePlus9
    GoTo ScoreMinus20

Expert_Tailwind:
    // Speed control is only worth the turn while something on the other side is still moving
    // first. Basic already rules out a Tailwind which is up.
    IfAnyOpponentOutspeedsSide ScorePlus9
    GoTo ScorePlus5

Expert_TrickRoom:
    // Setting Trick Room while it is already up would only end it early.
    IfFieldConditionsMask FIELD_CONDITION_TRICK_ROOM, ScoreMinus20
    IfAnyOpponentOutspeedsSide ScorePlus10
    GoTo ScorePlus5

Expert_FakeOut:
    // Fake Out is worth the turn for the flinch, which Shield Dust and Inner Focus both stop.
    // Basic already penalises it on every turn but the first.
    LoadIsFirstTurnInBattle AI_BATTLER_ATTACKER
    IfLoadedEqualTo FALSE, Expert_FakeOut_End
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_SHIELD_DUST, Expert_FakeOut_End
    IfLoadedEqualTo ABILITY_INNER_FOCUS, Expert_FakeOut_End
    AddToMoveScore 9

Expert_FakeOut_End:
    PopOrEnd

Expert_DestinyBond:
    // Destiny Bond only cashes in if the AI is going down anyway, and it has to move first for
    // the tag to be on the board when it does.
    IfDoesNotMoveFirst Expert_DestinyBond_WhenSlower
    IfDefenderCanKO Expert_DestinyBond_WhenDying
    GoTo ScorePlus6

Expert_DestinyBond_WhenDying:
    IfRandomLessThan 50, ScorePlus6
    GoTo ScorePlus7

Expert_DestinyBond_WhenSlower:
    IfRandomLessThan 128, ScorePlus6
    GoTo ScorePlus5

Expert_Setup:
    // Shared entry for every stat-boosting setup move.
    //
    // Unaware reads straight through the boost, and spending the turn in front of something
    // which is about to knock the AI out wastes it outright. A Sturdy or Focus Sash user at
    // full HP survives that hit, so it can still afford to set up.
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_UNAWARE, ScoreMinus20
    IfDefenderCanKO Expert_Setup_CheckSurvivesKO
    GoTo Expert_Setup_Classify

Expert_Setup_CheckSurvivesKO:
    IfHPPercentNotEqualTo AI_BATTLER_ATTACKER, 100, ScoreMinus20
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_STURDY, Expert_Setup_Classify
    LoadHeldItemEffect AI_BATTLER_ATTACKER
    IfLoadedNotEqualTo HOLD_EFFECT_ENDURE, ScoreMinus20

Expert_Setup_Classify:
    // Moves boosting one offensive and one defensive stat are judged on the half the target
    // can actually pressure: a purely physical attacker facing a physical-boosting move means
    // the boost is being spent to wall rather than to sweep, and likewise for special.
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SHELL_SMASH, Expert_ShellSmash
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_ATK_UP_2, Expert_SetupSpecialSweeper
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_ATK_UP_3, Expert_SetupSpecialSweeper
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ATK_DEF_UP, Expert_SetupSplitPhysical
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_CURSE, Expert_SetupSplitPhysical
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_ATK_SP_DEF_UP, Expert_SetupSplitSpecial
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_QUIVER_DANCE, Expert_SetupSplitSpecial
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DEF_UP, Expert_SetupDefensive
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DEF_UP_2, Expert_SetupDefensive
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SP_DEF_UP_2, Expert_SetupDefensive
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DEF_SPD_UP, Expert_SetupDefensive
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STOCKPILE, Expert_SetupDefensive

Expert_SetupOffensive:
    // +6 puts setup level with the bonus EvalAttack hands the best damaging move 80% of the
    // time, so it competes with attacking rather than being crowded out by it. A target which
    // cannot act this turn is a free one.
    AddToMoveScore 6
    IfBattlerIncapacitated AI_BATTLER_DEFENDER, Expert_SetupOffensive_ScorePlus3
    GoTo Expert_Setup_CheckSlowAndFragile

Expert_SetupOffensive_ScorePlus3:
    AddToMoveScore 3
    GoTo Expert_Setup_CheckSlowAndFragile

Expert_SetupDefensive:
    AddToMoveScore 6
    IfRandomLessThan 13, Expert_Setup_CheckSlowAndFragile
    IfBattlerIncapacitated AI_BATTLER_DEFENDER, Expert_SetupDefensive_ScorePlus2
    GoTo Expert_SetupDefensive_CheckBothDefenses

Expert_SetupDefensive_ScorePlus2:
    AddToMoveScore 2

Expert_SetupDefensive_CheckBothDefenses:
    // A move covering both defenses is worth more while neither of them is invested in yet.
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_DEF_SPD_UP, Expert_SetupDefensive_CheckDefenseStages
    IfCurrentMoveEffectNotEqualTo BATTLE_EFFECT_STOCKPILE, Expert_Setup_CheckSlowAndFragile

Expert_SetupDefensive_CheckDefenseStages:
    IfStatStageLessThan AI_BATTLER_ATTACKER, BATTLE_STAT_DEFENSE, 8, Expert_SetupDefensive_ScorePlus2Again
    IfStatStageLessThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_DEFENSE, 8, Expert_SetupDefensive_ScorePlus2Again
    GoTo Expert_Setup_CheckSlowAndFragile

Expert_SetupDefensive_ScorePlus2Again:
    AddToMoveScore 2
    GoTo Expert_Setup_CheckSlowAndFragile

Expert_SetupSplitPhysical:
    IfBattlerHasMoveOfClass AI_BATTLER_DEFENDER, CLASS_SPECIAL, Expert_SetupOffensive
    IfBattlerHasMoveOfClass AI_BATTLER_DEFENDER, CLASS_PHYSICAL, Expert_SetupDefensive
    GoTo Expert_SetupOffensive

Expert_SetupSplitSpecial:
    IfBattlerHasMoveOfClass AI_BATTLER_DEFENDER, CLASS_PHYSICAL, Expert_SetupOffensive
    IfBattlerHasMoveOfClass AI_BATTLER_DEFENDER, CLASS_SPECIAL, Expert_SetupDefensive
    GoTo Expert_SetupOffensive

Expert_SetupSpecialSweeper:
    // Nasty Plot and Tail Glow want a turn they can spare: either the target cannot act, or
    // it is slow enough not to threaten the AI inside three of them.
    AddToMoveScore 6
    IfBattlerIncapacitated AI_BATTLER_DEFENDER, Expert_SetupSpecialSweeper_ScorePlus3
    IfDefenderCanKOInHits 3, Expert_SetupSpecialSweeper_CheckSpAttackStage
    AddToMoveScore 1
    IfDoesNotMoveFirst Expert_SetupSpecialSweeper_CheckSpAttackStage
    AddToMoveScore 1
    GoTo Expert_SetupSpecialSweeper_CheckSpAttackStage

Expert_SetupSpecialSweeper_ScorePlus3:
    AddToMoveScore 3

Expert_SetupSpecialSweeper_CheckSpAttackStage:
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_ATTACK, 7, Expert_SetupSpecialSweeper_ScoreMinus1
    GoTo Expert_Setup_CheckSlowAndFragile

Expert_SetupSpecialSweeper_ScoreMinus1:
    AddToMoveScore -1

Expert_Setup_CheckSlowAndFragile:
    // Boosting is a losing trade against something which both moves first and only needs two
    // turns to finish the job.
    IfMovesFirst Expert_Setup_End
    IfDefenderCanKOInHits 2, ScoreMinus5

Expert_Setup_End:
    PopOrEnd

Expert_SetupSpeed:
    // Outspeeding is the whole point of Agility and Rock Polish; there is nothing to buy when
    // the AI is already faster.
    IfSpeedCompareEqualTo COMPARE_SPEED_SLOWER, Expert_SetupSpeed_ScorePlus7
    GoTo ScoreMinus20

Expert_SetupSpeed_ScorePlus7:
    AddToMoveScore 7
    PopOrEnd

Expert_ShellSmash:
    // Shell Smash gives up both defenses, so it is only worth it off a neutral board.
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_ATTACK, 6, ScoreMinus20
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_ATTACK, 6, ScoreMinus20
    AddToMoveScore 6
    IfBattlerIncapacitated AI_BATTLER_DEFENDER, Expert_ShellSmash_ScorePlus3
    GoTo Expert_ShellSmash_CheckKO

Expert_ShellSmash_ScorePlus3:
    AddToMoveScore 3

Expert_ShellSmash_CheckKO:
    // Moving first means taking the next hit through the drops, unless a White Herb undoes
    // them first.
    IfDoesNotMoveFirst Expert_ShellSmash_CheckKOAtCurrentStats
    IfDefenderCanKOAfterShellSmash ScoreMinus2
    GoTo ScorePlus2

Expert_ShellSmash_CheckKOAtCurrentStats:
    IfDefenderCanKO ScoreMinus2
    GoTo ScorePlus2

Expert_BellyDrum:
    // Belly Drum is all-in: it is worth the HP against a target which cannot punish the turn,
    // or which still cannot finish the AI off at half HP.
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_UNAWARE, ScoreMinus20
    IfBattlerIncapacitated AI_BATTLER_DEFENDER, Expert_BellyDrum_ScorePlus9
    IfDefenderCanKOAfterBellyDrum Expert_BellyDrum_ScorePlus4
    AddToMoveScore 8
    PopOrEnd

Expert_BellyDrum_ScorePlus9:
    AddToMoveScore 9
    PopOrEnd

Expert_BellyDrum_ScorePlus4:
    AddToMoveScore 4
    PopOrEnd

Expert_FocusEnergy:
    // Nothing crits through Battle Armor or Shell Armor, so the move is dead against them.
    // Otherwise it is worth more to a user which is already stacking crit rate.
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_BATTLE_ARMOR, ScoreMinus20
    IfLoadedEqualTo ABILITY_SHELL_ARMOR, ScoreMinus20
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_SUPER_LUCK, Expert_FocusEnergy_ScorePlus7
    IfLoadedEqualTo ABILITY_SNIPER, Expert_FocusEnergy_ScorePlus7
    LoadHeldItemEffect AI_BATTLER_ATTACKER
    IfLoadedEqualTo HOLD_EFFECT_CRITRATE_UP, Expert_FocusEnergy_ScorePlus7
    IfLoadedEqualTo HOLD_EFFECT_CHANSEY_CRITRATE_UP, Expert_FocusEnergy_ScorePlus7
    IfLoadedEqualTo HOLD_EFFECT_FARFETCHD_CRITRATE_UP, Expert_FocusEnergy_ScorePlus7
    IfMoveEffectKnown AI_BATTLER_ATTACKER, BATTLE_EFFECT_HIGH_CRITICAL, Expert_FocusEnergy_ScorePlus7
    IfMoveEffectKnown AI_BATTLER_ATTACKER, BATTLE_EFFECT_HIGH_CRITICAL_BURN_HIT, Expert_FocusEnergy_ScorePlus7
    IfMoveEffectKnown AI_BATTLER_ATTACKER, BATTLE_EFFECT_HIGH_CRITICAL_POISON_HIT, Expert_FocusEnergy_ScorePlus7
    IfMoveEffectKnown AI_BATTLER_ATTACKER, BATTLE_EFFECT_CHARGE_TURN_HIGH_CRIT, Expert_FocusEnergy_ScorePlus7
    IfMoveEffectKnown AI_BATTLER_ATTACKER, BATTLE_EFFECT_CHARGE_TURN_HIGH_CRIT_FLINCH, Expert_FocusEnergy_ScorePlus7
    AddToMoveScore 6
    PopOrEnd

Expert_FocusEnergy_ScorePlus7:
    AddToMoveScore 7
    PopOrEnd

Expert_Curse:
    // A Ghost-type Curse is not a setup move at all, and is left to Basic for now.
    LoadTypeFrom LOAD_ATTACKER_TYPE_1
    IfLoadedEqualTo TYPE_GHOST, Expert_Curse_End
    LoadTypeFrom LOAD_ATTACKER_TYPE_2
    IfLoadedEqualTo TYPE_GHOST, Expert_Curse_End
    GoTo Expert_Setup

Expert_Curse_End:
    PopOrEnd

Expert_PowerUpPunch:
    // The other moves sharing this effect only boost by chance, so they are judged on damage
    // alone; Power-Up Punch always boosts and is treated as setup.
    IfMoveNotEqualTo MOVE_POWER_UP_PUNCH, Expert_PowerUpPunch_End
    GoTo Expert_Setup

Expert_PowerUpPunch_End:
    PopOrEnd

Expert_BypassAccuracyMove:
    IfStatStageLessThan AI_BATTLER_ATTACKER, BATTLE_STAT_ACCURACY, 6, Expert_BypassAccuracyMove_TryScorePlus6
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_EVASION, 6, Expert_BypassAccuracyMove_TryScorePlus6
    PopOrEnd

Expert_BypassAccuracyMove_TryScorePlus6:
    IfRandomGreaterThan 170, Expert_BypassAccuracyMove_End
    AddToMoveScore 6

Expert_BypassAccuracyMove_End:
    PopOrEnd

Expert_FellStinger:
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_ATTACK, 11, Expert_FellStinger_End
    IfCurrentMoveDoesNotKill ROLL_FOR_DAMAGE, Expert_FellStinger_End
    IfSpeedCompareEqualTo COMPARE_SPEED_SLOWER, Expert_FellStinger_ScorePlus6
    AddToMoveScore 9
    PopOrEnd

Expert_FellStinger_ScorePlus6:
    AddToMoveScore 6

Expert_FellStinger_End:
    PopOrEnd

Expert_AttackDropOnHit:
    // Only the moves whose drop is guaranteed are scored
    IfMoveEqualTo MOVE_LUNGE, Expert_AttackDropOnHit_CheckBestDamage
    IfMoveEqualTo MOVE_SNARL, Expert_AttackDropOnHit_CheckBestDamage
    IfMoveEqualTo MOVE_STRUGGLE_BUG, Expert_AttackDropOnHit_CheckBestDamage
    PopOrEnd

Expert_AttackDropOnHit_CheckBestDamage:
    // Ignore if already HDM
    FlagBestDamageMove
    IfLoadedEqualTo AI_MOVE_IS_HIGHEST_DAMAGE, Expert_AttackDropOnHit_End

    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_CONTRARY, Expert_AttackDropOnHit_ScorePlus5
    IfLoadedEqualTo ABILITY_CLEAR_BODY, Expert_AttackDropOnHit_ScorePlus5
    IfLoadedEqualTo ABILITY_WHITE_SMOKE, Expert_AttackDropOnHit_ScorePlus5
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_LOWER_ATTACK_HIT, Expert_AttackDropOnHit_CheckPhysical
    IfBattlerHasMoveOfClass AI_BATTLER_DEFENDER, CLASS_SPECIAL, Expert_AttackDropOnHit_ScorePlus6
    GoTo Expert_AttackDropOnHit_ScorePlus5

Expert_AttackDropOnHit_CheckPhysical:
    IfBattlerHasMoveOfClass AI_BATTLER_DEFENDER, CLASS_PHYSICAL, Expert_AttackDropOnHit_ScorePlus6
    GoTo Expert_AttackDropOnHit_ScorePlus5

Expert_AttackDropOnHit_ScorePlus6:
    AddToMoveScore 6
    GoTo Expert_AttackDropOnHit_CheckDoubles

Expert_AttackDropOnHit_ScorePlus5:
    AddToMoveScore 5

Expert_AttackDropOnHit_CheckDoubles:
    LoadBattleType 
    IfLoadedNotMask BATTLE_TYPE_DOUBLES, Expert_AttackDropOnHit_End
    IfMoveEqualTo MOVE_SNARL, Expert_AttackDropOnHit_ScorePlus1
    IfMoveEqualTo MOVE_STRUGGLE_BUG, Expert_AttackDropOnHit_ScorePlus1
    PopOrEnd

Expert_AttackDropOnHit_ScorePlus1:
    AddToMoveScore 1

Expert_AttackDropOnHit_End:
    PopOrEnd

Expert_SpeedDownOnHit:
    // Only the moves whose drop is guaranteed are judged on it
    IfMoveEqualTo MOVE_ICY_WIND, Expert_SpeedDownOnHit_CheckBestDamage
    IfMoveEqualTo MOVE_ROCK_TOMB, Expert_SpeedDownOnHit_CheckBestDamage
    IfMoveEqualTo MOVE_MUD_SHOT, Expert_SpeedDownOnHit_CheckBestDamage
    IfMoveEqualTo MOVE_BULLDOZE, Expert_SpeedDownOnHit_CheckBestDamage
    IfMoveEqualTo MOVE_ELECTROWEB, Expert_SpeedDownOnHit_CheckBestDamage
    PopOrEnd

Expert_SpeedDownOnHit_CheckBestDamage:
    // A move EvalAttack already picked as the best hit has been paid for once; it does not also
    // get paid for the drop.
    FlagBestDamageMove
    IfLoadedEqualTo AI_MOVE_IS_HIGHEST_DAMAGE, Expert_SpeedDownOnHit_End

    // Otherwise the drop is what buys the turn, and it buys the most when it takes the speed
    // lead off a target which cannot shrug the drop off.
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_CONTRARY, Expert_SpeedDownOnHit_ScorePlus5
    IfLoadedEqualTo ABILITY_CLEAR_BODY, Expert_SpeedDownOnHit_ScorePlus5
    IfLoadedEqualTo ABILITY_WHITE_SMOKE, Expert_SpeedDownOnHit_ScorePlus5
    IfSpeedCompareNotEqualTo COMPARE_SPEED_SLOWER, Expert_SpeedDownOnHit_ScorePlus5
    AddToMoveScore 6
    GoTo Expert_SpeedDownOnHit_CheckDoubles

Expert_SpeedDownOnHit_ScorePlus5:
    AddToMoveScore 5

Expert_SpeedDownOnHit_CheckDoubles:
    // Icy Wind and Electroweb hit both opposing slots, so the drop lands twice.
    LoadBattleType 
    IfLoadedNotMask BATTLE_TYPE_DOUBLES, Expert_SpeedDownOnHit_End
    IfMoveEqualTo MOVE_ICY_WIND, Expert_SpeedDownOnHit_ScorePlus1
    IfMoveEqualTo MOVE_ELECTROWEB, Expert_SpeedDownOnHit_ScorePlus1
    PopOrEnd

Expert_SpeedDownOnHit_ScorePlus1:
    AddToMoveScore 1

Expert_SpeedDownOnHit_End:
    PopOrEnd

Expert_StatusSpeedDown:
    // If the attacker is slower than its target, 72.7% chance of score +2.
    //
    // If the attacker is faster than its target, score -3.
    IfSpeedCompareEqualTo COMPARE_SPEED_SLOWER, Expert_StatusSpeedDown_TryScorePlus2
    AddToMoveScore -3
    GoTo Expert_StatusSpeedDown_End

Expert_StatusSpeedDown_TryScorePlus2:
    IfRandomLessThan 70, Expert_StatusSpeedDown_End
    AddToMoveScore 2

Expert_StatusSpeedDown_End:
    PopOrEnd 

Expert_StatusSpAttackDown:
    // If the target is at any stat stage other than +0, additional score -1. Also, further modify
    // the score according to all of the following which apply:
    // - If the attacker's HP is at 90% or lower, additional score -1.
    // - If the target is at -3 stat stage or lower, 80.5% chance of additional score -2.
    //
    // If the target's HP is at 70% or lower, additional score -2.
    //
    // If the move last used by the target was not a Physical move, 50% chance of score -2.
    IfStatStageEqualTo AI_BATTLER_DEFENDER, BATTLE_STAT_SP_ATTACK, 6, Expert_StatusSpAttackDown_CheckTargetHP
    AddToMoveScore -1
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER, 90, Expert_StatusSpAttackDown_CheckTargetStatStage
    AddToMoveScore -1

Expert_StatusSpAttackDown_CheckTargetStatStage:
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_SP_ATTACK, 3, Expert_StatusSpAttackDown_CheckTargetHP
    IfRandomLessThan 50, Expert_StatusSpAttackDown_CheckTargetHP
    AddToMoveScore -2

Expert_StatusSpAttackDown_CheckTargetHP:
    IfHPPercentGreaterThan AI_BATTLER_DEFENDER, 70, Expert_StatusSpAttackDown_CheckLastUsedMove
    AddToMoveScore -2

Expert_StatusSpAttackDown_CheckLastUsedMove:
    LoadDefenderLastUsedMoveClass 
    IfLoadedNotEqualTo CLASS_PHYSICAL, Expert_StatusSpAttackDown_End
    IfRandomLessThan 128, Expert_StatusSpAttackDown_End
    AddToMoveScore -2

Expert_StatusSpAttackDown_End:
    PopOrEnd 

Expert_StatusSpAttackDown_PreSplitSpecialTypes:
    TableEntry TYPE_FIRE
    TableEntry TYPE_WATER
    TableEntry TYPE_GRASS
    TableEntry TYPE_ELECTRIC
    TableEntry TYPE_PSYCHIC
    TableEntry TYPE_ICE
    TableEntry TYPE_DRAGON
    TableEntry TYPE_DARK
    TableEntry TABLE_END

Expert_StatusEvasionDown:
    // If the attacker's HP is < 70%, 80.5% chance of additional score -2.
    //
    // Otherwise, if the target's stat stage is -3 or lower, 80.5% chance of additional score -2.
    //
    // If the target's HP is <= 70%, score -2.
    IfHPPercentLessThan AI_BATTLER_ATTACKER, 70, Expert_StatusEvasionDown_TryScoreMinus2
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_EVASION, 3, Expert_StatusEvasionDown_CheckTargetHP

Expert_StatusEvasionDown_TryScoreMinus2:
    IfRandomLessThan 50, Expert_StatusEvasionDown_CheckTargetHP
    AddToMoveScore -2

Expert_StatusEvasionDown_CheckTargetHP:
    IfHPPercentGreaterThan AI_BATTLER_DEFENDER, 70, Expert_StatusEvasionDown_End
    AddToMoveScore -2

Expert_StatusEvasionDown_End:
    PopOrEnd 

Expert_Haze:
    // If any of the attacker's stat stages are at +3 or higher, or any of the target's stat stages
    // are at -3 or lower, 80.4% chance of additional score -3.
    //
    // If any of the attacker's stat stages are at -3 or lower, or any of the target's stat stages
    // are at +3 or higher, 80.4% chance of additional score +3.
    //
    // Otherwise, score -1.
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_ATTACK, 8, Expert_Haze_TryScoreMinus3
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_DEFENSE, 8, Expert_Haze_TryScoreMinus3
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_ATTACK, 8, Expert_Haze_TryScoreMinus3
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_DEFENSE, 8, Expert_Haze_TryScoreMinus3
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_EVASION, 8, Expert_Haze_TryScoreMinus3
    IfStatStageLessThan AI_BATTLER_DEFENDER, BATTLE_STAT_ATTACK, 4, Expert_Haze_TryScoreMinus3
    IfStatStageLessThan AI_BATTLER_DEFENDER, BATTLE_STAT_DEFENSE, 4, Expert_Haze_TryScoreMinus3
    IfStatStageLessThan AI_BATTLER_DEFENDER, BATTLE_STAT_SP_ATTACK, 4, Expert_Haze_TryScoreMinus3
    IfStatStageLessThan AI_BATTLER_DEFENDER, BATTLE_STAT_SP_DEFENSE, 4, Expert_Haze_TryScoreMinus3
    IfStatStageLessThan AI_BATTLER_DEFENDER, BATTLE_STAT_ACCURACY, 4, Expert_Haze_TryScoreMinus3
    GoTo Expert_Haze_CheckToEncourage

Expert_Haze_TryScoreMinus3:
    IfRandomLessThan 50, Expert_Haze_CheckToEncourage
    AddToMoveScore -3

Expert_Haze_CheckToEncourage:
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_ATTACK, 8, Expert_Haze_TryScorePlus3
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_DEFENSE, 8, Expert_Haze_TryScorePlus3
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_SP_ATTACK, 8, Expert_Haze_TryScorePlus3
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_SP_DEFENSE, 8, Expert_Haze_TryScorePlus3
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_EVASION, 8, Expert_Haze_TryScorePlus3
    IfStatStageLessThan AI_BATTLER_ATTACKER, BATTLE_STAT_ATTACK, 4, Expert_Haze_TryScorePlus3
    IfStatStageLessThan AI_BATTLER_ATTACKER, BATTLE_STAT_DEFENSE, 4, Expert_Haze_TryScorePlus3
    IfStatStageLessThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_ATTACK, 4, Expert_Haze_TryScorePlus3
    IfStatStageLessThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_DEFENSE, 4, Expert_Haze_TryScorePlus3
    IfStatStageLessThan AI_BATTLER_ATTACKER, BATTLE_STAT_ACCURACY, 4, Expert_Haze_TryScorePlus3
    IfRandomLessThan 50, Expert_Haze_End
    AddToMoveScore -1
    GoTo Expert_Haze_End

Expert_Haze_TryScorePlus3:
    IfRandomLessThan 50, Expert_Haze_End
    AddToMoveScore 3

Expert_Haze_End:
    PopOrEnd 

Expert_Bide:
    // If the attacker's HP is <= 90%, score -2.
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER, 90, Expert_Bide_End
    AddToMoveScore -2

Expert_Bide_End:
    PopOrEnd 

Expert_ForceSwitch:
    // If the target has been in battle for longer than more than 3 turns, 75% chance of score +2.
    //
    // If the target's side of the field has Spikes, Stealth Rock, or Toxic Spikes set, 50% chance of
    // score +2.
    //
    // If the target has a stat stage of +3 or higher in any of the following stats, 50% chance of
    // score +2:
    // - Attack
    // - Defense
    // - SpAttack
    // - SpDefense
    // - Evasion
    //
    // Otherwise, score -3.
    LoadBattlerTurnCount AI_BATTLER_DEFENDER
    IfLoadedGreaterThan 3, Expert_ForceSwitch_75PercentScorePlus2
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_SPIKES, Expert_ForceSwitch_50PercentScorePlus2
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_STEALTH_ROCK, Expert_ForceSwitch_50PercentScorePlus2
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_TOXIC_SPIKES, Expert_ForceSwitch_50PercentScorePlus2
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_ATTACK, 8, Expert_ForceSwitch_50PercentScorePlus2
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_DEFENSE, 8, Expert_ForceSwitch_50PercentScorePlus2
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_SP_ATTACK, 8, Expert_ForceSwitch_50PercentScorePlus2
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_SP_DEFENSE, 8, Expert_ForceSwitch_50PercentScorePlus2
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_EVASION, 8, Expert_ForceSwitch_50PercentScorePlus2
    AddToMoveScore -3
    GoTo Expert_ForceSwitch_End

Expert_ForceSwitch_75PercentScorePlus2:
    IfRandomLessThan 64, Expert_ForceSwitch_50PercentScorePlus2
    AddToMoveScore 2

Expert_ForceSwitch_50PercentScorePlus2:
    IfRandomLessThan 128, Expert_ForceSwitch_End
    AddToMoveScore 2

Expert_ForceSwitch_End:
    PopOrEnd 

Expert_Conversion:
    // If the attacker's HP is <= 90%, additional score -2.
    //
    // If it is NOT the first global turn of the battle, ~78.1% chance of score -2.
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER, 90, Expert_Conversion_CheckTurnCount
    AddToMoveScore -2

Expert_Conversion_CheckTurnCount:
    LoadTurnCount 
    IfLoadedEqualTo 0, Expert_Conversion_End
    IfRandomLessThan 200, ScoreMinus2

Expert_Conversion_End:
    PopOrEnd 

Expert_Synthesis:
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_MEGA_SOL, Expert_Synthesis_InSun
    LoadCurrentWeather 
    IfLoadedEqualTo AI_WEATHER_HAILING, Expert_Synthesis_ScoreMinus2
    IfLoadedEqualTo AI_WEATHER_RAINING, Expert_Synthesis_ScoreMinus2
    IfLoadedEqualTo AI_WEATHER_SANDSTORM, Expert_Synthesis_ScoreMinus2
    IfLoadedNotEqualTo AI_WEATHER_SUNNY, Expert_Recovery

Expert_Synthesis_InSun:
    IfShouldRecover 67, ScorePlus7
    GoTo Expert_Recovery

Expert_Synthesis_ScoreMinus2:
    AddToMoveScore -2
    GoTo Expert_Recovery

Expert_Recovery:
    IfShouldRecover 50, ScorePlus7
    GoTo ScorePlus5


Expert_Screen:
    AddToMoveScore 6
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_SET_REFLECT, Expert_Screen_CheckPhysical
    IfBattlerHasMoveOfClass AI_BATTLER_DEFENDER, CLASS_SPECIAL, Expert_Screen_Bonus
    PopOrEnd

Expert_Screen_CheckPhysical:
    IfBattlerHasMoveOfClass AI_BATTLER_DEFENDER, CLASS_PHYSICAL, Expert_Screen_Bonus
    PopOrEnd

Expert_Screen_Bonus:
    LoadHeldItemEffect AI_BATTLER_ATTACKER
    IfLoadedNotEqualTo HOLD_EFFECT_EXTEND_SCREENS, Expert_Screen_TryScorePlus1
    AddToMoveScore 1

Expert_Screen_TryScorePlus1:
    IfRandomLessThan 128, Expert_Screen_End
    AddToMoveScore 1

Expert_Screen_End:
    PopOrEnd

Expert_AuroraVeil:
    AddToMoveScore 6
    GoTo Expert_Screen_Bonus

Expert_Rest:
    IfShouldRecover 100, Expert_Rest_CheckSleepIsCheap
    GoTo ScorePlus5

Expert_Rest_CheckSleepIsCheap:
    LoadHeldItemEffect AI_BATTLER_ATTACKER
    IfLoadedInTable Expert_Rest_SleepCuringItems, ScorePlus8
    IfMoveKnown AI_BATTLER_ATTACKER, MOVE_SLEEP_TALK, ScorePlus8
    IfMoveKnown AI_BATTLER_ATTACKER, MOVE_SNORE, ScorePlus8
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_SHED_SKIN, ScorePlus8
    IfLoadedEqualTo ABILITY_EARLY_BIRD, ScorePlus8
    IfLoadedNotEqualTo ABILITY_HYDRATION, ScorePlus7
    LoadCurrentWeather 
    IfLoadedEqualTo AI_WEATHER_RAINING, ScorePlus8
    GoTo ScorePlus7

Expert_Rest_SleepCuringItems:
    TableEntry HOLD_EFFECT_SLP_RESTORE
    TableEntry HOLD_EFFECT_STATUS_RESTORE
    TableEntry TABLE_END

Expert_OHKOMove:
    // Coin flip to tie HDM
    IfRandomLessThan 128, ScorePlus5
    GoTo ScorePlus6



Expert_StatusBurn:
    AddToMoveScore 6
    IfRandomGreaterThan 94, Expert_StatusBurn_End
    IfBattlerHasMoveOfClass AI_BATTLER_DEFENDER, CLASS_PHYSICAL, Expert_StatusBurn_ScorePlus1
    GoTo Expert_StatusBurn_CheckHex

Expert_StatusBurn_ScorePlus1:
    AddToMoveScore 1

Expert_StatusBurn_CheckHex:
    IfMoveKnown AI_BATTLER_ATTACKER, MOVE_HEX, Expert_StatusBurn_ScorePlus1AndEnd
    LoadBattleType 
    IfLoadedNotMask BATTLE_TYPE_DOUBLES, Expert_StatusBurn_End
    IfMoveKnown AI_BATTLER_ATTACKER_PARTNER, MOVE_HEX, Expert_StatusBurn_ScorePlus1AndEnd
    PopOrEnd

Expert_StatusBurn_ScorePlus1AndEnd:
    AddToMoveScore 1

Expert_StatusBurn_End:
    PopOrEnd

Expert_StatusPoison:
    AddToMoveScore 6
    IfRandomGreaterThan 96, Expert_StatusPoison_End
    IfAttackerCanKO Expert_StatusPoison_End
    IfHPPercentLessThan AI_BATTLER_DEFENDER, 21, Expert_StatusPoison_End

    LoadTypeFrom LOAD_DEFENDER_TYPE_1
    IfLoadedEqualTo TYPE_STEEL, Expert_StatusPoison_End
    IfLoadedEqualTo TYPE_POISON, Expert_StatusPoison_End
    LoadTypeFrom LOAD_DEFENDER_TYPE_2
    IfLoadedEqualTo TYPE_STEEL, Expert_StatusPoison_End
    IfLoadedEqualTo TYPE_POISON, Expert_StatusPoison_End
    IfStatus AI_BATTLER_DEFENDER, MON_CONDITION_ANY, Expert_StatusPoison_End
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_SAFEGUARD, Expert_StatusPoison_End
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_IMMUNITY, Expert_StatusPoison_End
    IfLoadedEqualTo ABILITY_MAGIC_GUARD, Expert_StatusPoison_End
    IfLoadedEqualTo ABILITY_POISON_HEAL, Expert_StatusPoison_End
    IfLoadedEqualTo ABILITY_LEAF_GUARD, Expert_StatusPoison_CheckSun
    IfLoadedEqualTo ABILITY_HYDRATION, Expert_StatusPoison_CheckRain
    GoTo Expert_StatusPoison_CheckPayoff

Expert_StatusPoison_CheckSun:
    LoadCurrentWeather 
    IfLoadedEqualTo AI_WEATHER_SUNNY, Expert_StatusPoison_End
    GoTo Expert_StatusPoison_CheckPayoff

Expert_StatusPoison_CheckRain:
    LoadCurrentWeather 
    IfLoadedEqualTo AI_WEATHER_RAINING, Expert_StatusPoison_End

Expert_StatusPoison_CheckPayoff:
    IfMoveKnown AI_BATTLER_ATTACKER, MOVE_HEX, Expert_StatusPoison_CheckTargetIsHarmless
    IfMoveKnown AI_BATTLER_ATTACKER, MOVE_VENOSHOCK, Expert_StatusPoison_CheckTargetIsHarmless
    GoTo Expert_StatusPoison_End

Expert_StatusPoison_CheckTargetIsHarmless:
    IfBattlerHasMoveOfClass AI_BATTLER_DEFENDER, CLASS_PHYSICAL, Expert_StatusPoison_End
    IfBattlerHasMoveOfClass AI_BATTLER_DEFENDER, CLASS_SPECIAL, Expert_StatusPoison_End
    AddToMoveScore 2

Expert_StatusPoison_End:
    PopOrEnd

Expert_StatusParalyze:
    // Paralysis is worth the most when it buys the speed lead outright, when the AI has a way
    // to cash the status in, or when it stacks onto a target already losing turns. Fake Out is
    // left out of the flinch list because it is dead after the turn the user came in on.
    IfParalysisFlipsSpeed Expert_StatusParalyze_ScorePlus8
    IfMoveKnown AI_BATTLER_ATTACKER, MOVE_HEX, Expert_StatusParalyze_ScorePlus8
    IfMoveEffectKnown AI_BATTLER_ATTACKER, BATTLE_EFFECT_FLINCH_HIT, Expert_StatusParalyze_ScorePlus8
    IfMoveEffectKnown AI_BATTLER_ATTACKER, BATTLE_EFFECT_FLINCH_BURN_HIT, Expert_StatusParalyze_ScorePlus8
    IfMoveEffectKnown AI_BATTLER_ATTACKER, BATTLE_EFFECT_FLINCH_FREEZE_HIT, Expert_StatusParalyze_ScorePlus8
    IfMoveEffectKnown AI_BATTLER_ATTACKER, BATTLE_EFFECT_FLINCH_PARALYZE_HIT, Expert_StatusParalyze_ScorePlus8
    IfMoveEffectKnown AI_BATTLER_ATTACKER, BATTLE_EFFECT_FLINCH_MINIMIZE_DOUBLE_HIT, Expert_StatusParalyze_ScorePlus8
    IfMoveEffectKnown AI_BATTLER_ATTACKER, BATTLE_EFFECT_FLINCH_DOUBLE_DAMAGE_FLY_OR_BOUNCE, Expert_StatusParalyze_ScorePlus8
    IfMoveEffectKnown AI_BATTLER_ATTACKER, BATTLE_EFFECT_CHARGE_TURN_HIGH_CRIT_FLINCH, Expert_StatusParalyze_ScorePlus8
    IfVolatileStatus AI_BATTLER_DEFENDER, VOLATILE_CONDITION_ATTRACT, Expert_StatusParalyze_ScorePlus8
    IfVolatileStatus AI_BATTLER_DEFENDER, VOLATILE_CONDITION_CONFUSION, Expert_StatusParalyze_ScorePlus8
    AddToMoveScore 7
    GoTo Expert_StatusParalyze_TryScoreMinus1

Expert_StatusParalyze_ScorePlus8:
    AddToMoveScore 8

Expert_StatusParalyze_TryScoreMinus1:
    IfRandomLessThan 128, Expert_StatusParalyze_End
    AddToMoveScore -1

Expert_StatusParalyze_End:
    PopOrEnd

Expert_StatusParalyzeHit:
    // If the target is immune to or would resist the move, do not apply any further modifiers.
    //
    // Treat the moves whose paralysis is guaranteed as paralysis-inflicting status moves. The
    // rest of this effect's moves only have a 10-30% chance and are left to ordinary scoring.
    IfMoveEffectivenessEquals TYPE_MULTI_IMMUNE, Expert_StatusParalyzeHit_End
    IfMoveEffectivenessEquals TYPE_MULTI_QUARTER_DAMAGE, Expert_StatusParalyzeHit_End
    IfMoveEffectivenessEquals TYPE_MULTI_HALF_DAMAGE, Expert_StatusParalyzeHit_End
    IfMoveEqualTo MOVE_NUZZLE, Expert_StatusParalyze
    IfMoveEqualTo MOVE_ZAP_CANNON, Expert_StatusParalyze
    PopOrEnd 

Expert_StatusParalyzeHit_End:
    PopOrEnd 

Expert_SlowMove:
    IfDefenderCanKO Expert_SlowMove_CheckSurvives
    GoTo Expert_SlowMove_Continue

Expert_SlowMove_CheckSurvives:
    IfHPPercentNotEqualTo AI_BATTLER_ATTACKER, 100, ScoreMinus20
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_STURDY, Expert_SlowMove_Continue
    LoadHeldItemEffect AI_BATTLER_ATTACKER
    IfLoadedNotEqualTo HOLD_EFFECT_ENDURE, ScoreMinus20

Expert_SlowMove_Continue:
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_HIT_LAST_WHIFF_IF_HIT, Expert_FocusPunch
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_FLEE_FROM_WILD_BATTLE, Expert_Teleport
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_PRIORITY_NEG_1_BYPASS_ACCURACY, Expert_BypassAccuracyMove
    PopOrEnd


Expert_Substitute:
    IfHPPercentLessThan AI_BATTLER_ATTACKER, 51, ScoreMinus20
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_INFILTRATOR, ScoreMinus20

    AddToMoveScore 6
    IfNotStatus AI_BATTLER_DEFENDER, MON_CONDITION_SLEEP, Expert_Substitute_CheckSeeded
    AddToMoveScore 2

Expert_Substitute_CheckSeeded:
    IfDoesNotMoveFirst Expert_Substitute_TryScoreMinus1
    IfMoveEffect AI_BATTLER_DEFENDER, MOVE_EFFECT_LEECH_SEED, Expert_Substitute_ScorePlus2
    GoTo Expert_Substitute_TryScoreMinus1

Expert_Substitute_ScorePlus2:
    AddToMoveScore 2

Expert_Substitute_TryScoreMinus1:
    IfRandomLessThan 128, Expert_Substitute_CheckSound
    AddToMoveScore -1

Expert_Substitute_CheckSound:
    IfBattlerKnowsSoundMove AI_BATTLER_DEFENDER, Expert_Substitute_ScoreMinus8
    PopOrEnd

Expert_Substitute_ScoreMinus8:
    AddToMoveScore -8
    PopOrEnd

Expert_CounterMove:
    AddToMoveScore 6
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_MIRROR_COAT, Expert_CounterMove_CheckSpecialOnly
    IfBattlerHasMoveOfClass AI_BATTLER_DEFENDER, CLASS_SPECIAL, Expert_CounterMove_WrongSplit
    IfBattlerHasMoveOfClass AI_BATTLER_DEFENDER, CLASS_PHYSICAL, Expert_CounterMove_RightSplit
    GoTo Expert_CounterMove_WrongSplit

Expert_CounterMove_CheckSpecialOnly:
    IfBattlerHasMoveOfClass AI_BATTLER_DEFENDER, CLASS_PHYSICAL, Expert_CounterMove_WrongSplit
    IfBattlerHasMoveOfClass AI_BATTLER_DEFENDER, CLASS_SPECIAL, Expert_CounterMove_RightSplit

Expert_CounterMove_WrongSplit:
    IfDefenderCanKO Expert_CounterMove_CheckSurvivesNoBonus
    GoTo Expert_CounterMove_CheckSpeed

Expert_CounterMove_RightSplit:
    IfDefenderCanKO Expert_CounterMove_CheckSurvives
    IfRandomLessThan 205, Expert_CounterMove_ScorePlus2
    GoTo Expert_CounterMove_CheckSpeed

Expert_CounterMove_CheckSurvivesNoBonus:
    IfHPPercentNotEqualTo AI_BATTLER_ATTACKER, 100, ScoreMinus20
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_STURDY, Expert_CounterMove_CheckSpeed
    LoadHeldItemEffect AI_BATTLER_ATTACKER
    IfLoadedEqualTo HOLD_EFFECT_ENDURE, Expert_CounterMove_CheckSpeed
    GoTo ScoreMinus20

Expert_CounterMove_CheckSurvives:
    IfHPPercentNotEqualTo AI_BATTLER_ATTACKER, 100, ScoreMinus20
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_STURDY, Expert_CounterMove_ScorePlus2
    LoadHeldItemEffect AI_BATTLER_ATTACKER
    IfLoadedEqualTo HOLD_EFFECT_ENDURE, Expert_CounterMove_ScorePlus2
    GoTo ScoreMinus20

Expert_CounterMove_ScorePlus2:
    AddToMoveScore 2

Expert_CounterMove_CheckSpeed:
    IfSpeedCompareEqualTo COMPARE_SPEED_SLOWER, Expert_CounterMove_CheckStatusMoves
    IfRandomGreaterThan 63, Expert_CounterMove_CheckStatusMoves
    AddToMoveScore -1

Expert_CounterMove_CheckStatusMoves:
    IfBattlerHasMoveOfClass AI_BATTLER_DEFENDER, CLASS_STATUS, Expert_CounterMove_TryScoreMinus1
    PopOrEnd

Expert_CounterMove_TryScoreMinus1:
    IfRandomGreaterThan 63, Expert_CounterMove_End
    AddToMoveScore -1

Expert_CounterMove_End:
    PopOrEnd

Expert_MetalBurst:
    AddToMoveScore 6
    IfDefenderCanKO Expert_MetalBurst_CheckSurvives
    IfRandomGreaterThan 204, Expert_CounterMove_CheckStatusMoves
    AddToMoveScore 1
    GoTo Expert_CounterMove_CheckStatusMoves

Expert_MetalBurst_CheckSurvives:
    IfHPPercentNotEqualTo AI_BATTLER_ATTACKER, 100, ScoreMinus20
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_STURDY, Expert_MetalBurst_ScorePlus2
    LoadHeldItemEffect AI_BATTLER_ATTACKER
    IfLoadedEqualTo HOLD_EFFECT_ENDURE, Expert_MetalBurst_ScorePlus2
    GoTo ScoreMinus20

Expert_MetalBurst_ScorePlus2:
    AddToMoveScore 2
    GoTo Expert_CounterMove_CheckStatusMoves


Expert_AcidSpray:
    IfMoveNotEqualTo MOVE_ACID_SPRAY, Expert_AcidSpray_End
    AddToMoveScore 6

Expert_AcidSpray_End:
    PopOrEnd

Expert_Taunt:
    // Taunt earns its turn when it shuts a specific threat out: a Trick Room the target is still
    // able to set, or a Defog which would strip the AI's own Aurora Veil before it moves again.
    IfFieldConditionsMask FIELD_CONDITION_TRICK_ROOM, Expert_Taunt_CheckDefog
    IfMoveKnown AI_BATTLER_DEFENDER, MOVE_TRICK_ROOM, ScorePlus9

Expert_Taunt_CheckDefog:
    IfDoesNotMoveFirst ScorePlus5
    IfNotSideCondition AI_BATTLER_ATTACKER, SIDE_CONDITION_AURORA_VEIL, ScorePlus5
    IfMoveKnown AI_BATTLER_DEFENDER, MOVE_DEFOG, ScorePlus9
    GoTo ScorePlus5

Expert_Encore:
    // Encore needs a move to lock the target into, so it does nothing on the turn the target
    // came in, nor against one which is already locked.
    IfBattlerUnderEffect AI_BATTLER_DEFENDER, CHECK_ENCORE, ScoreMinus20
    LoadIsFirstTurnInBattle AI_BATTLER_DEFENDER
    IfLoadedNotEqualTo FALSE, ScoreMinus20

    // Moving first is what makes Encore worth it, but only against a move worth locking the
    // target into. Anything else and the turn is better spent elsewhere.
    IfDoesNotMoveFirst Expert_Encore_WhenSlower
    LoadBattlerPreviousMove AI_BATTLER_DEFENDER
    LoadEffectOfLoadedMove 
    IfLoadedinTable Expert_Encore_EncouragedMoveEffects, ScorePlus7
    PopOrEnd

Expert_Encore_WhenSlower:
    IfRandomLessThan 128, ScorePlus5
    GoTo ScorePlus6


Expert_Encore_EncouragedMoveEffects:
    TableEntry BATTLE_EFFECT_RECOVER_DAMAGE_SLEEP
    TableEntry BATTLE_EFFECT_ATK_UP
    TableEntry BATTLE_EFFECT_DEF_UP
    TableEntry BATTLE_EFFECT_SPEED_UP
    TableEntry BATTLE_EFFECT_SP_ATK_UP
    TableEntry BATTLE_EFFECT_RESET_STAT_CHANGES
    TableEntry BATTLE_EFFECT_FORCE_SWITCH
    TableEntry BATTLE_EFFECT_CONVERSION
    TableEntry BATTLE_EFFECT_STATUS_BADLY_POISON
    TableEntry BATTLE_EFFECT_SET_LIGHT_SCREEN
    TableEntry BATTLE_EFFECT_AURORA_VEIL
    TableEntry BATTLE_EFFECT_REST
    TableEntry BATTLE_EFFECT_HALVE_HP
    TableEntry BATTLE_EFFECT_SP_DEF_UP_2
    TableEntry BATTLE_EFFECT_STATUS_CONFUSE
    TableEntry BATTLE_EFFECT_STATUS_POISON
    TableEntry BATTLE_EFFECT_STATUS_PARALYZE
    TableEntry BATTLE_EFFECT_STATUS_LEECH_SEED
    TableEntry BATTLE_EFFECT_DO_NOTHING
    TableEntry BATTLE_EFFECT_ATK_UP_2
    TableEntry BATTLE_EFFECT_ENCORE
    TableEntry BATTLE_EFFECT_NEXT_ATTACK_ALWAYS_HITS
    TableEntry BATTLE_EFFECT_CURE_PARTY_STATUS
    TableEntry BATTLE_EFFECT_PREVENT_ESCAPE
    TableEntry BATTLE_EFFECT_STATUS_NIGHTMARE
    TableEntry BATTLE_EFFECT_PROTECT
    TableEntry BATTLE_EFFECT_PROTECT_HURT_ON_CONTACT
    TableEntry BATTLE_EFFECT_PROTECT_LOWER_SPEED_CONTACT
    TableEntry BATTLE_EFFECT_SWITCH_ABILITIES
    TableEntry BATTLE_EFFECT_FORESIGHT
    TableEntry BATTLE_EFFECT_ALL_FAINT_3_TURNS
    TableEntry BATTLE_EFFECT_WEATHER_SANDSTORM
    TableEntry BATTLE_EFFECT_SURVIVE_WITH_1_HP
    TableEntry BATTLE_EFFECT_ATK_UP_2_STATUS_CONFUSION
    TableEntry BATTLE_EFFECT_INFATUATE
    TableEntry BATTLE_EFFECT_PREVENT_STATUS
    TableEntry BATTLE_EFFECT_WEATHER_RAIN
    TableEntry BATTLE_EFFECT_WEATHER_SUN
    TableEntry BATTLE_EFFECT_MAX_ATK_LOSE_HALF_MAX_HP
    TableEntry BATTLE_EFFECT_COPY_STAT_CHANGES
    TableEntry BATTLE_EFFECT_ALWAYS_FLINCH_FIRST_TURN_ONLY
    TableEntry BATTLE_EFFECT_STOCKPILE
    TableEntry BATTLE_EFFECT_SPIT_UP
    TableEntry BATTLE_EFFECT_SWALLOW
    TableEntry BATTLE_EFFECT_WEATHER_HAIL
    TableEntry BATTLE_EFFECT_TORMENT
    TableEntry BATTLE_EFFECT_STATUS_BURN
    TableEntry BATTLE_EFFECT_MAKE_GLOBAL_TARGET
    TableEntry BATTLE_EFFECT_MAKE_GLOBAL_TARGET_POWDER
    TableEntry BATTLE_EFFECT_SP_DEF_UP_DOUBLE_ELECTRIC_POWER
    TableEntry BATTLE_EFFECT_SWITCH_HELD_ITEMS
    TableEntry BATTLE_EFFECT_COPY_ABILITY
    TableEntry BATTLE_EFFECT_GROUND_TRAP_USER_CONTINUOUS_HEAL
    TableEntry BATTLE_EFFECT_RECYCLE
    TableEntry BATTLE_EFFECT_REMOVE_HELD_ITEM
    TableEntry BATTLE_EFFECT_SWITCH_ABILITIES
    TableEntry BATTLE_EFFECT_HEAL_STATUS
    TableEntry BATTLE_EFFECT_CONFUSE_ALL
    TableEntry BATTLE_EFFECT_CHARGE_TURN_SP_ATK_UP
    TableEntry BATTLE_EFFECT_ATK_SPD_UP
    TableEntry BATTLE_EFFECT_QUIVER_DANCE
    TableEntry BATTLE_EFFECT_GRAVITY
    TableEntry BATTLE_EFFECT_NATURAL_GIFT
    TableEntry BATTLE_EFFECT_REMOVE_PROTECT
    TableEntry BATTLE_EFFECT_DOUBLE_SPEED_3_TURNS
    TableEntry BATTLE_EFFECT_FLING
    TableEntry BATTLE_EFFECT_TRANSFER_STATUS
    TableEntry BATTLE_EFFECT_PREVENT_HEALING
    TableEntry BATTLE_EFFECT_SUPRESS_ABILITY
    TableEntry BATTLE_EFFECT_SET_ABILITY_TO_INSOMNIA
    TableEntry BATTLE_EFFECT_SWAP_STAT_CHANGES
    TableEntry BATTLE_EFFECT_RESTORE_HP_EVERY_TURN
    TableEntry BATTLE_EFFECT_GIVE_GROUND_IMMUNITY
    TableEntry BATTLE_EFFECT_TRICK_ROOM
    TableEntry TABLE_END

Expert_PainSplit:
    // If the opponent's HP < 80%, score -1.
    //
    // If the attacker is slower than its opponent:
    // - If the attacker's HP > 60%, score -1.
    // - Otherwise, score +1.
    //
    // If the attacker's HP > 40%, score -1.
    //
    // Otherwise, score -1.
    IfHPPercentLessThan AI_BATTLER_DEFENDER, 80, Expert_PainSplit_ScoreMinus1
    IfSpeedCompareEqualTo COMPARE_SPEED_SLOWER, Expert_PainSplit_CheckUserHP
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER, 40, Expert_PainSplit_ScoreMinus1
    AddToMoveScore 1
    GoTo Expert_PainSplit_End

Expert_PainSplit_CheckUserHP:
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER, 60, Expert_PainSplit_ScoreMinus1
    AddToMoveScore 1
    GoTo Expert_PainSplit_End

Expert_PainSplit_ScoreMinus1:
    AddToMoveScore -1

Expert_PainSplit_End:
    PopOrEnd 

Expert_LockOn:
    // 50% chance of score +2.
    IfRandomLessThan 128, Expert_LockOn_End
    AddToMoveScore 2

Expert_LockOn_End:
    PopOrEnd 

Expert_SleepTalk:
    // If the attacker is asleep, score +10.
    //
    // Otherwise, score -5.
    IfStatus AI_BATTLER_ATTACKER, MON_CONDITION_SLEEP, ScorePlus10
    AddToMoveScore -5
    PopOrEnd 


Expert_HealBell:
    // If neither the attacker nor any of its party members have a non-volatile status condition,
    // score -5.
    IfStatus AI_BATTLER_ATTACKER, MON_CONDITION_ANY, Expert_HealBell_End
    IfPartyMemberStatus AI_BATTLER_ATTACKER, MON_CONDITION_ANY, Expert_HealBell_End
    AddToMoveScore -5

Expert_HealBell_End:
    PopOrEnd 


Expert_Protect:
    // Protect is worth a turn only if the AI survives that turn. Chip damage it is already
    // taking would finish the job while it sits behind the shield.
    IfResidualDamageKOsAttacker ScoreMinus20

    // A repeated Protect is read easily, and a third in a row is never worth it.
    LoadProtectChain AI_BATTLER_ATTACKER
    IfLoadedGreaterThan 1, ScoreMinus20
    IfLoadedEqualTo 0, Expert_Protect_Score
    IfRandomLessThan 128, ScoreMinus20

Expert_Protect_Score:
    AddToMoveScore 6

    // Stalling costs the AI more than the target when the AI is the one bleeding, and buys more
    // when the target is.
    IfStatus AI_BATTLER_ATTACKER, MON_CONDITION_ANY_POISON, Expert_Protect_ScoreMinus2
    IfStatus AI_BATTLER_ATTACKER, MON_CONDITION_BURN, Expert_Protect_ScoreMinus2
    IfVolatileStatus AI_BATTLER_ATTACKER, VOLATILE_CONDITION_CURSE, Expert_Protect_ScoreMinus2
    IfVolatileStatus AI_BATTLER_ATTACKER, VOLATILE_CONDITION_ATTRACT, Expert_Protect_ScoreMinus2
    IfMoveEffect AI_BATTLER_ATTACKER, MOVE_EFFECT_PERISH_SONG, Expert_Protect_ScoreMinus2
    IfMoveEffect AI_BATTLER_ATTACKER, MOVE_EFFECT_LEECH_SEED, Expert_Protect_ScoreMinus2
    IfMoveEffect AI_BATTLER_ATTACKER, MOVE_EFFECT_YAWN, Expert_Protect_ScoreMinus2
    GoTo Expert_Protect_CheckTarget

Expert_Protect_ScoreMinus2:
    AddToMoveScore -2

Expert_Protect_CheckTarget:
    IfStatus AI_BATTLER_DEFENDER, MON_CONDITION_ANY_POISON, Expert_Protect_ScorePlus1
    IfStatus AI_BATTLER_DEFENDER, MON_CONDITION_BURN, Expert_Protect_ScorePlus1
    IfVolatileStatus AI_BATTLER_DEFENDER, VOLATILE_CONDITION_CURSE, Expert_Protect_ScorePlus1
    IfVolatileStatus AI_BATTLER_DEFENDER, VOLATILE_CONDITION_ATTRACT, Expert_Protect_ScorePlus1
    IfMoveEffect AI_BATTLER_DEFENDER, MOVE_EFFECT_PERISH_SONG, Expert_Protect_ScorePlus1
    IfMoveEffect AI_BATTLER_DEFENDER, MOVE_EFFECT_LEECH_SEED, Expert_Protect_ScorePlus1
    IfMoveEffect AI_BATTLER_DEFENDER, MOVE_EFFECT_YAWN, Expert_Protect_ScorePlus1
    GoTo Expert_Protect_CheckFirstTurn

Expert_Protect_ScorePlus1:
    AddToMoveScore 1

Expert_Protect_CheckFirstTurn:
    // Nothing has been set up to stall for yet on the turn the AI comes in, though in doubles
    // the partner may still get something out of the turn.
    LoadBattleType 
    IfLoadedMask BATTLE_TYPE_DOUBLES, Expert_Protect_End
    LoadIsFirstTurnInBattle AI_BATTLER_ATTACKER
    IfLoadedEqualTo FALSE, Expert_Protect_End
    AddToMoveScore -1

Expert_Protect_End:
    PopOrEnd




Expert_Endure:
    // If the attacker's HP < 4%, score -1.
    //
    // If the attacker's HP < 35%, 72.7% chance of score +1.
    IfHPPercentLessThan AI_BATTLER_ATTACKER, 4, Expert_Endure_ScoreMinus1
    IfHPPercentLessThan AI_BATTLER_ATTACKER, 35, Expert_Endure_TryScorePlus1

Expert_Endure_ScoreMinus1:
    AddToMoveScore -1
    GoTo Expert_Endure_End

Expert_Endure_TryScorePlus1:
    IfRandomLessThan 70, Expert_Endure_End
    AddToMoveScore 1

Expert_Endure_End:
    PopOrEnd 

Expert_BatonPass:
    CountAlivePartyBattlers AI_BATTLER_ATTACKER
    IfLoadedEqualTo 0, Expert_BatonPass_End
    IfVolatileStatus AI_BATTLER_ATTACKER, VOLATILE_CONDITION_SUBSTITUTE, Expert_BatonPass_ScorePlus14
    SumPositiveStatStages AI_BATTLER_ATTACKER
    IfLoadedEqualTo 0, Expert_BatonPass_End

Expert_BatonPass_ScorePlus14:
    AddToMoveScore 14

Expert_BatonPass_End:
    PopOrEnd

Expert_Pursuit:
    IfCurrentMoveKills ROLL_FOR_DAMAGE, Expert_Pursuit_ScorePlus10
    IfHPPercentLessThan AI_BATTLER_DEFENDER, 20, Expert_Pursuit_ScorePlus10
    IfHPPercentGreaterThan AI_BATTLER_DEFENDER, 39, Expert_Pursuit_CheckSpeed
    IfRandomLessThan 128, Expert_Pursuit_CheckSpeed
    AddToMoveScore 8
    GoTo Expert_Pursuit_CheckSpeed

Expert_Pursuit_ScorePlus10:
    AddToMoveScore 10

Expert_Pursuit_CheckSpeed:
    IfSpeedCompareEqualTo COMPARE_SPEED_SLOWER, Expert_Pursuit_End
    AddToMoveScore 3

Expert_Pursuit_End:
    PopOrEnd




Expert_PsychUp:
    // If the opponent has any of Attack, Defense, SpAttack, SpDefense, or Evasion at +3 stages or
    // higher:
    // - If the attacker's Evasion stat is at +0 stages or lower, score +2.
    // - If the attacker has any of Attack, Defense, SpAttack, or SpDefense at +0 stages or lower,
    // score +1.
    // - Otherwise, 80.4% chance of score -2.
    //
    // Otherwise, score -2.
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_ATTACK, 8, Expert_PsychUp_CheckUserStatStages
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_DEFENSE, 8, Expert_PsychUp_CheckUserStatStages
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_SP_ATTACK, 8, Expert_PsychUp_CheckUserStatStages
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_SP_DEFENSE, 8, Expert_PsychUp_CheckUserStatStages
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_EVASION, 8, Expert_PsychUp_CheckUserStatStages
    GoTo Expert_PsychUp_ScoreMinus2

Expert_PsychUp_CheckUserStatStages:
    IfStatStageLessThan AI_BATTLER_ATTACKER, BATTLE_STAT_ATTACK, 7, Expert_PsychUp_ScorePlus1
    IfStatStageLessThan AI_BATTLER_ATTACKER, BATTLE_STAT_DEFENSE, 7, Expert_PsychUp_ScorePlus1
    IfStatStageLessThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_ATTACK, 7, Expert_PsychUp_ScorePlus1
    IfStatStageLessThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_DEFENSE, 7, Expert_PsychUp_ScorePlus1
    IfStatStageLessThan AI_BATTLER_ATTACKER, BATTLE_STAT_EVASION, 7, Expert_PsychUp_ScorePlus2
    IfRandomLessThan 50, Expert_PsychUp_End
    GoTo Expert_PsychUp_ScoreMinus2

Expert_PsychUp_ScorePlus2:
    AddToMoveScore 1

Expert_PsychUp_ScorePlus1:
    AddToMoveScore 1
    PopOrEnd 

Expert_PsychUp_ScoreMinus2:
    AddToMoveScore -2

Expert_PsychUp_End:
    PopOrEnd 


Expert_ChargeTurn:
    // Sky Attack, Skull Bash and Meteor Beam spend a turn charging in the open, dealing nothing
    // and inviting a free hit. A Power Herb resolves them the same turn instead, which is worth
    // actively chasing: these effects are excluded from EvalAttack's best-damage and KO bonuses,
    // so the Power Herb case has to supply its own incentive. The semi-invulnerable charge moves
    // are absent - dodging for the turn is not the same liability - as are Solar Beam and Solar
    // Blade, which are left entirely to the ordinary damage scoring.
    LoadHeldItemEffect AI_BATTLER_ATTACKER
    IfLoadedEqualTo HOLD_EFFECT_CHARGE_SKIP, Expert_ChargeTurn_ScorePlus9
    AddToMoveScore -20
    PopOrEnd

Expert_ChargeTurn_ScorePlus9:
    AddToMoveScore 9
    PopOrEnd




Expert_FocusPunch:
    // If the opponent is immune to or would resist the move, score -1.
    //
    // If the attacker is behind a Substitute, score +5.
    //
    // If the opponent is asleep, score +1.
    //
    // If the opponent is confused or infatuated, 60.9% chance of score +1.
    //
    // If it is not the attacker's first turn in battle, 21.875% chance of score +1.
    IfMoveEffectivenessEquals TYPE_MULTI_IMMUNE, Expert_FocusPunch_ScoreMinus1
    IfMoveEffectivenessEquals TYPE_MULTI_QUARTER_DAMAGE, Expert_FocusPunch_ScoreMinus1
    IfMoveEffectivenessEquals TYPE_MULTI_HALF_DAMAGE, Expert_FocusPunch_ScoreMinus1
    IfVolatileStatus AI_BATTLER_ATTACKER, VOLATILE_CONDITION_SUBSTITUTE, ScorePlus5
    IfStatus AI_BATTLER_DEFENDER, MON_CONDITION_SLEEP, Expert_FocusPunch_ScorePlus1
    IfVolatileStatus AI_BATTLER_DEFENDER, VOLATILE_CONDITION_ATTRACT, Expert_FocusPunch_TryScorePlus1
    IfVolatileStatus AI_BATTLER_DEFENDER, VOLATILE_CONDITION_CONFUSION, Expert_FocusPunch_TryScorePlus1
    LoadIsFirstTurnInBattle AI_BATTLER_ATTACKER
    IfLoadedNotEqualTo FALSE, Expert_FocusPunch_End
    IfRandomLessThan 200, Expert_FocusPunch_End
    AddToMoveScore 1
    GoTo Expert_FocusPunch_End

Expert_FocusPunch_ScoreMinus1:
    AddToMoveScore -1
    GoTo Expert_FocusPunch_End

Expert_FocusPunch_TryScorePlus1:
    IfRandomLessThan 100, Expert_FocusPunch_End

Expert_FocusPunch_ScorePlus1:
    AddToMoveScore 1

Expert_FocusPunch_End:
    PopOrEnd 

Expert_PartingShot:
    AddToMoveScore 6
    IfDefenderCanKO Expert_PartingShot_CheckSpeed
    GoTo Expert_PartingShot_CheckAttacker

Expert_PartingShot_CheckSpeed:
    IfDoesNotMoveFirst Expert_PartingShot_CheckAttacker
    AddToMoveScore 7

Expert_PartingShot_CheckAttacker:
    IfBattlerHasMoveOfClass AI_BATTLER_DEFENDER, CLASS_PHYSICAL, Expert_PartingShot_TryScorePlus1
    IfBattlerHasMoveOfClass AI_BATTLER_DEFENDER, CLASS_SPECIAL, Expert_PartingShot_TryScorePlus1
    GoTo Expert_PartingShot_CheckParty

Expert_PartingShot_TryScorePlus1:
    IfRandomGreaterThan 84, Expert_PartingShot_CheckParty
    AddToMoveScore 1

Expert_PartingShot_CheckParty:
    CountAlivePartyBattlers AI_BATTLER_ATTACKER
    IfLoadedNotEqualTo 0, Expert_PartingShot_CheckAbility
    IfRandomGreaterThan 170, Expert_PartingShot_CheckAbility
    AddToMoveScore -1

Expert_PartingShot_CheckAbility:
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_CONTRARY, Expert_PartingShot_ScoreMinus2
    IfLoadedEqualTo ABILITY_DEFIANT, Expert_PartingShot_ScoreMinus2
    IfLoadedEqualTo ABILITY_COMPETITIVE, Expert_PartingShot_ScoreMinus2
    GoTo Expert_PivotRegenerator

Expert_PartingShot_ScoreMinus2:
    AddToMoveScore -2
    GoTo Expert_PivotRegenerator

Expert_SwitchHit:
    IfAttackerCanKO Expert_SwitchHit_End
    CountAlivePartyBattlers AI_BATTLER_ATTACKER
    IfLoadedEqualTo 0, Expert_SwitchHit_End
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedNotEqualTo ABILITY_REGENERATOR, Expert_SwitchHit_End
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER, 75, Expert_SwitchHit_End
    AddToMoveScore 6

Expert_SwitchHit_End:
    PopOrEnd

Expert_Teleport:
    AddToMoveScore 6

Expert_PivotRegenerator:
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedNotEqualTo ABILITY_REGENERATOR, Expert_PivotRegenerator_End
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER, 75, Expert_PivotRegenerator_End
    AddToMoveScore 2

Expert_PivotRegenerator_End:
    PopOrEnd

Expert_Trick:
    LoadHeldItemEffect AI_BATTLER_ATTACKER
    IfLoadedInTable Expert_Trick_StatusItems, Expert_Trick_CoinFlipScorePlus7
    IfLoadedInTable Expert_Trick_DisruptiveItems, ScorePlus7
    GoTo ScorePlus5

Expert_Trick_CoinFlipScorePlus7:
    IfRandomLessThan 128, ScorePlus6
    GoTo ScorePlus7

Expert_Trick_StatusItems:
    TableEntry HOLD_EFFECT_PSN_USER
    TableEntry HOLD_EFFECT_BRN_USER
    TableEntry HOLD_EFFECT_HP_RESTORE_PSN_TYPE
    TableEntry TABLE_END

Expert_Trick_DisruptiveItems:
    TableEntry HOLD_EFFECT_SPEED_DOWN_GROUNDED
    TableEntry HOLD_EFFECT_PRIORITY_DOWN
    TableEntry HOLD_EFFECT_DMG_USER_CONTACT_XFR
    TableEntry TABLE_END

Expert_BrickBreak:
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_REFLECT, Expert_BrickBreak_ScreenIsUp
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_LIGHT_SCREEN, Expert_BrickBreak_ScreenIsUp
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_AURORA_VEIL, Expert_BrickBreak_ScreenIsUp
    PopOrEnd

Expert_BrickBreak_ScreenIsUp:
    IfRandomLessThan 205, ScorePlus8
    GoTo ScorePlus7

Expert_Endeavor:
    // If the opponent's HP < 70%, score -1 and terminate.
    //
    // If the attacker is slower than its opponent:
    // - If the attacker's HP > 50%, score -1.
    // - Otherwise, score +1.
    //
    // If the attacker is faster than its opponent:
    // - If the attacker's HP > 40%, score -1.
    // - Otherwise, score +1.
    IfHPPercentLessThan AI_BATTLER_DEFENDER, 70, Expert_Endeavor_ScoreMinus1
    IfSpeedCompareEqualTo COMPARE_SPEED_SLOWER, Expert_Endeavor_SlowerCheckHP
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER, 40, Expert_Endeavor_ScoreMinus1
    AddToMoveScore 1
    GoTo Expert_Endeavor_End

Expert_Endeavor_SlowerCheckHP:
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER, 50, Expert_Endeavor_ScoreMinus1
    AddToMoveScore 1
    GoTo Expert_Endeavor_End

Expert_Endeavor_ScoreMinus1:
    AddToMoveScore -1

Expert_Endeavor_End:
    PopOrEnd 








Expert_Fling:
    LoadHeldItemEffect AI_BATTLER_ATTACKER
    IfLoadedEqualTo HOLD_EFFECT_SOMETIMES_FLINCH, Expert_Fling_Flinch
    IfLoadedEqualTo HOLD_EFFECT_PIKA_SPATK_UP, Expert_StatusParalyze
    IfLoadedEqualTo HOLD_EFFECT_BRN_USER, Expert_StatusBurn
    IfLoadedEqualTo HOLD_EFFECT_PSN_USER, Expert_StatusPoison
    IfLoadedEqualTo HOLD_EFFECT_STRENGTHEN_POISON, Expert_StatusPoison
    PopOrEnd

Expert_Fling_Flinch:
    IfSpeedCompareEqualTo COMPARE_SPEED_SLOWER, Expert_Fling_End
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_SHIELD_DUST, Expert_Fling_End
    IfLoadedEqualTo ABILITY_INNER_FOCUS, Expert_Fling_End
    AddToMoveScore 9

Expert_Fling_End:
    PopOrEnd

Expert_HealBlock:
    // If the opponent knows a move with any of the following effects, 90.2% chance of score +1:
    // - Dream Eater
    // - Restore half HP
    // - Roost
    // - Sun-boosted recovery
    // - Rest
    // - Swallow
    // - Draining moves
    // - Ingrain
    // - Aqua Ring
    // - Leech Seed
    // - Lunar Dance, Healing Wish
    //
    // If the attacker is under the effect of Leech Seed or the opponent is under the effect of Ingrain
    // or Aqua Ring, 90.2% chance of score +1.
    //
    // Otherwise, 56.4% chance of score +1.
    IfMoveEffectKnown AI_BATTLER_DEFENDER, BATTLE_EFFECT_RECOVER_DAMAGE_SLEEP, Expert_HealBlock_TryScorePlus1
    IfMoveEffectKnown AI_BATTLER_DEFENDER, BATTLE_EFFECT_RESTORE_HALF_HP, Expert_HealBlock_TryScorePlus1
    IfMoveEffectKnown AI_BATTLER_DEFENDER, BATTLE_EFFECT_HEAL_ALLIES_QUARTER, Expert_HealBlock_TryScorePlus1
    IfMoveEffectKnown AI_BATTLER_DEFENDER, BATTLE_EFFECT_HEAL_HALF_REMOVE_FLYING_TYPE, Expert_HealBlock_TryScorePlus1
    IfMoveEffectKnown AI_BATTLER_DEFENDER, BATTLE_EFFECT_UNUSED_157, Expert_HealBlock_TryScorePlus1
    IfMoveEffectKnown AI_BATTLER_DEFENDER, BATTLE_EFFECT_HEAL_HALF_MORE_IN_SUN, Expert_HealBlock_TryScorePlus1
    IfMoveEffectKnown AI_BATTLER_DEFENDER, BATTLE_EFFECT_REST, Expert_HealBlock_TryScorePlus1
    IfMoveEffectKnown AI_BATTLER_DEFENDER, BATTLE_EFFECT_SWALLOW, Expert_HealBlock_TryScorePlus1
    IfMoveEffectKnown AI_BATTLER_DEFENDER, BATTLE_EFFECT_RECOVER_HALF_DAMAGE_DEALT, Expert_HealBlock_TryScorePlus1
    IfMoveEffectKnown AI_BATTLER_DEFENDER, BATTLE_EFFECT_RECOVER_THREE_QUARTER_DAMAGE_DEALT, Expert_HealBlock_TryScorePlus1
    IfMoveEffectKnown AI_BATTLER_DEFENDER, BATTLE_EFFECT_GROUND_TRAP_USER_CONTINUOUS_HEAL, Expert_HealBlock_TryScorePlus1
    IfMoveEffectKnown AI_BATTLER_DEFENDER, BATTLE_EFFECT_RESTORE_HP_EVERY_TURN, Expert_HealBlock_TryScorePlus1
    IfMoveEffectKnown AI_BATTLER_DEFENDER, BATTLE_EFFECT_STATUS_LEECH_SEED, Expert_HealBlock_TryScorePlus1
    IfMoveEffectKnown AI_BATTLER_DEFENDER, BATTLE_EFFECT_FAINT_FULL_RESTORE_NEXT_MON, Expert_HealBlock_TryScorePlus1
    IfMoveEffect AI_BATTLER_ATTACKER, MOVE_EFFECT_LEECH_SEED, Expert_HealBlock_TryScorePlus1
    IfMoveEffect AI_BATTLER_DEFENDER, MOVE_EFFECT_AQUA_RING, Expert_HealBlock_TryScorePlus1
    IfMoveEffect AI_BATTLER_DEFENDER, MOVE_EFFECT_INGRAIN, Expert_HealBlock_TryScorePlus1
    IfRandomLessThan 96, Expert_HealBlock_TryScorePlus1
    GoTo Expert_HealBlock_End

Expert_HealBlock_TryScorePlus1:
    IfRandomLessThan 25, Expert_HealBlock_End
    AddToMoveScore 1

Expert_HealBlock_End:
    PopOrEnd 

Expert_WorrySeed:
    // If the opponent knows the move Rest, additional score +1.
    //
    // If the attacker's HP >= 50%, 50% chance of additional score +1.
    //
    // 75% chance of score +1.
    IfMoveNotKnown AI_BATTLER_DEFENDER, MOVE_REST, Expert_WorrySeed_CheckUserHP
    AddToMoveScore 1

Expert_WorrySeed_CheckUserHP:
    IfHPPercentLessThan AI_BATTLER_ATTACKER, 50, Expert_WorrySeed_TryScorePlus1
    IfRandomLessThan 128, Expert_WorrySeed_TryScorePlus1
    AddToMoveScore 1

Expert_WorrySeed_TryScorePlus1:
    IfRandomLessThan 64, Expert_WorrySeed_End
    AddToMoveScore 1
    GoTo Expert_WorrySeed_End

Expert_WorrySeed_End:
    PopOrEnd 



Expert_Defog:
    // If the opponent's side of the field is under the effect of Light Screen or Reflect:
    // - If the attacker's HP < 30% and there are no remaining party members:
    //   - 80.5% chance of additional score -2.
    //   - If the opponent's HP > 70%, score -2.
    // - Start at score +1.
    // - If the opponent has at least one remaining party member and their side of the field is
    // under the effect of Spikes, Stealth Rock, or Toxic Spikes, 50% chance of score -1.
    // - Proceed to the final if-block below.
    //
    // If the opponent's side of the field is under the effect of Spikes, Stealth Rock, or Toxic
    // Spikes, additional score -2.
    //
    // If all of the following conditions are met, score -2:
    // - The attacker's HP >= 70%
    // - The opponent's Evasion stat is at -2 stage or greater
    // - The opponent's HP <= 70%
    // Otherwise:
    // - 80.5% chance of additional score -2.
    // - If the opponent's HP <= 70% score -2.
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_LIGHT_SCREEN, Expert_Defog_ScreenScrubbing
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_REFLECT, Expert_Defog_ScreenScrubbing
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_SPIKES, Expert_Defog_ScoreMinus2AndEnd
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_STEALTH_ROCK, Expert_Defog_ScoreMinus2AndEnd
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_TOXIC_SPIKES, Expert_Defog_ScoreMinus2AndEnd
    GoTo Expert_Defog_CheckUserHPAndOpponentEvasion

Expert_Defog_ScreenScrubbing:
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER, 30, Expert_Defog_ScreenScrubbingCheckHazards
    CountAlivePartyBattlers AI_BATTLER_ATTACKER
    IfLoadedEqualTo 0, Expert_Defog_TryScoreMinus2

Expert_Defog_ScreenScrubbingCheckHazards:
    AddToMoveScore 1
    CountAlivePartyBattlers AI_BATTLER_DEFENDER
    IfLoadedEqualTo 0, Expert_Defog_End
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_SPIKES, Expert_Defog_TryScoreMinus1
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_STEALTH_ROCK, Expert_Defog_TryScoreMinus1
    IfSideCondition AI_BATTLER_DEFENDER, SIDE_CONDITION_TOXIC_SPIKES, Expert_Defog_TryScoreMinus1
    GoTo Expert_Defog_CheckUserHPAndOpponentEvasion

Expert_Defog_ScoreMinus2AndEnd:
    AddToMoveScore -2
    GoTo Expert_Defog_CheckUserHPAndOpponentEvasion

Expert_Defog_TryScoreMinus1:
    IfRandomLessThan 128, Expert_Defog_CheckUserHPAndOpponentEvasion
    AddToMoveScore -1
    GoTo Expert_Defog_CheckUserHPAndOpponentEvasion

Expert_Defog_CheckUserHPAndOpponentEvasion:
    IfHPPercentLessThan AI_BATTLER_ATTACKER, 70, Expert_Defog_TryScoreMinus2
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_EVASION, 3, Expert_Defog_CheckOpponentHP

Expert_Defog_TryScoreMinus2:
    IfRandomLessThan 50, Expert_Defog_CheckOpponentHP
    AddToMoveScore -2

Expert_Defog_CheckOpponentHP:
    IfHPPercentGreaterThan AI_BATTLER_DEFENDER, 70, Expert_Defog_End
    AddToMoveScore -2

Expert_Defog_End:
    PopOrEnd 



Expert_HealingWish:
    // If the attacker's HP >= 80% and the attacker is faster than its opponent, 25% of score -5.
    //
    // If the attacker's HP > 50%, 80.5% chance of score -1.
    //
    // 75% chance to ignore this section of modifiers:
    // - Start at score +1.
    // - If the attacker does not have a super-effective move against its opponent, 25% chance of
    // additional score +1.
    // - If a party member deals more damage than the attacker, 50% chance of additional score +1.
    //
    // If the attacker's HP <= 30%, 50% chance of score +1.
    IfHPPercentLessThan AI_BATTLER_ATTACKER, 80, Expert_HealingWish_HappyPath
    IfSpeedCompareEqualTo COMPARE_SPEED_SLOWER, Expert_HealingWish_HappyPath
    IfRandomLessThan 192, Expert_HealingWish_End
    GoTo ScoreMinus5

Expert_HealingWish_HappyPath:
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER, 50, Expert_HealingWish_TryScoreMinus1
    IfRandomLessThan 192, Expert_HealingWish_CheckUserAtLowHP
    AddToMoveScore 1
    IfHasSuperEffectiveMove Expert_HealingWish_CheckPartyMemberDamage
    IfRandomLessThan 192, Expert_HealingWish_CheckPartyMemberDamage
    AddToMoveScore 1

Expert_HealingWish_CheckPartyMemberDamage:
    IfPartyMemberDealsMoreDamage USE_MAX_DAMAGE, Expert_HealingWish_TryScorePlus1
    GoTo Expert_HealingWish_CheckUserAtLowHP

Expert_HealingWish_TryScorePlus1:
    IfRandomLessThan 128, Expert_HealingWish_CheckUserAtLowHP
    AddToMoveScore 1

Expert_HealingWish_CheckUserAtLowHP:
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER, 30, Expert_HealingWish_End
    IfRandomLessThan 128, Expert_HealingWish_End
    AddToMoveScore 1
    GoTo Expert_HealingWish_End

Expert_HealingWish_TryScoreMinus1:
    IfRandomLessThan 50, Expert_HealingWish_End
    AddToMoveScore -1

Expert_HealingWish_End:
    PopOrEnd 

EvalAttack_Main:
    // Never target the partner.
    IfTargetIsPartner Terminate

    // Classify this move against the rest of the moveset, using the damage roll that was
    // picked for each slot at the start of the turn. Anything which would KO the target also
    // counts as a best-damage move, so several lethal options compete on equal footing.
    FlagBestDamageMove
    IfLoadedEqualTo AI_MOVE_IS_HIGHEST_DAMAGE, EvalAttack_ScoreBestDamage
    GoTo EvalAttack_CheckKill

EvalAttack_ScoreBestDamage:
    // 80% chance of score +6, otherwise score +8.
    IfRandomLessThan 205, EvalAttack_ScoreBestDamage_Plus6
    AddToMoveScore 8
    GoTo EvalAttack_CheckKill

EvalAttack_ScoreBestDamage_Plus6:
    AddToMoveScore 6

EvalAttack_CheckKill:
    IfCurrentMoveKills ROLL_FOR_DAMAGE, EvalAttack_ApplyKillBonuses
    GoTo EvalAttack_CheckLastDitchPriority

EvalAttack_ApplyKillBonuses:
    // Taking the KO first is worth far more than taking it second, so the bonus depends on
    // whether we expect to move first. A speed tie counts as moving first.
    IfSpeedCompareEqualTo COMPARE_SPEED_SLOWER, EvalAttack_KillWhenSlower
    AddToMoveScore 6
    GoTo EvalAttack_CheckLastDitchPriority

EvalAttack_KillWhenSlower:
    // Priority still buys us the first hit even when we lose the speed check.
    IfCurrentMoveHasPriority EvalAttack_KillWithPriority
    AddToMoveScore 3
    GoTo EvalAttack_CheckLastDitchPriority

EvalAttack_KillWithPriority:
    AddToMoveScore 6

EvalAttack_CheckLastDitchPriority:
    // If we are slower than a target which can knock us out, a priority attack is the only
    // move we are certain to get away, so score it far above everything else.
    LoadMovePower
    IfLoadedEqualTo 0, EvalAttack_CheckHighCrit
    IfCurrentMoveHasPriority EvalAttack_LastDitch_CheckSpeed
    GoTo EvalAttack_CheckHighCrit

EvalAttack_LastDitch_CheckSpeed:
    IfSpeedCompareNotEqualTo COMPARE_SPEED_SLOWER, EvalAttack_CheckHighCrit
    IfDefenderCanKO EvalAttack_LastDitch_Score
    GoTo EvalAttack_CheckHighCrit

EvalAttack_LastDitch_Score:
    AddToMoveScore 11

EvalAttack_CheckHighCrit:
    // A high critical-hit ratio is only worth chasing when the move is already resolving
    // super-effectively: 50% chance of score +1.
    LoadCurrentMoveEffect
    IfLoadedNotInTable EvalAttack_HighCritEffects, EvalAttack_Terminate
    IfMoveEffectivenessEquals TYPE_MULTI_DOUBLE_DAMAGE, EvalAttack_TryScorePlus1
    IfMoveEffectivenessEquals TYPE_MULTI_QUADRUPLE_DAMAGE, EvalAttack_TryScorePlus1
    PopOrEnd

EvalAttack_TryScorePlus1:
    IfRandomLessThan 128, EvalAttack_Terminate
    AddToMoveScore 1

EvalAttack_Terminate:
    PopOrEnd

EvalAttack_HighCritEffects:
    TableEntry BATTLE_EFFECT_HIGH_CRITICAL
    TableEntry BATTLE_EFFECT_HIGH_CRITICAL_BURN_HIT
    TableEntry BATTLE_EFFECT_HIGH_CRITICAL_POISON_HIT
    TableEntry BATTLE_EFFECT_CHARGE_TURN_HIGH_CRIT
    TableEntry BATTLE_EFFECT_CHARGE_TURN_HIGH_CRIT_FLINCH
    TableEntry BATTLE_EFFECT_ALWAYS_CRIT
    TableEntry TABLE_END

SetupFirstTurn_Main:
    IfTargetIsPartner Terminate

    // If this is not the first turn, terminate.
    LoadTurnCount 
    IfLoadedNotEqualTo 0, SetupFirstTurn_Terminate

    // If the current move's effect is not known tobe a setup move, break.
    LoadCurrentMoveEffect 
    IfLoadedNotInTable SetupFirstTurn_SetupEffects, SetupFirstTurn_Terminate

    // 68.75% of the time, score +2.
    IfRandomLessThan 80, SetupFirstTurn_Terminate
    AddToMoveScore 2

SetupFirstTurn_Terminate:
    PopOrEnd 

SetupFirstTurn_SetupEffects:
    TableEntry BATTLE_EFFECT_ATK_UP
    TableEntry BATTLE_EFFECT_DEF_UP
    TableEntry BATTLE_EFFECT_SPEED_UP
    TableEntry BATTLE_EFFECT_SP_ATK_UP
    TableEntry BATTLE_EFFECT_SP_DEF_UP
    TableEntry BATTLE_EFFECT_ACC_UP
    TableEntry BATTLE_EFFECT_EVA_UP
    TableEntry BATTLE_EFFECT_ATK_DOWN
    TableEntry BATTLE_EFFECT_SWITCH_LOWER_ATKS
    TableEntry BATTLE_EFFECT_DEF_DOWN
    TableEntry BATTLE_EFFECT_SPEED_DOWN
    TableEntry BATTLE_EFFECT_SP_ATK_DOWN
    TableEntry BATTLE_EFFECT_SP_DEF_DOWN
    TableEntry BATTLE_EFFECT_ACC_DOWN
    TableEntry BATTLE_EFFECT_EVA_DOWN
    TableEntry BATTLE_EFFECT_CONVERSION
    TableEntry BATTLE_EFFECT_SET_LIGHT_SCREEN
    TableEntry BATTLE_EFFECT_AURORA_VEIL
    TableEntry BATTLE_EFFECT_SP_DEF_UP_2
    TableEntry BATTLE_EFFECT_CRIT_UP_2
    TableEntry BATTLE_EFFECT_STATUS_CONFUSE
    TableEntry BATTLE_EFFECT_ATK_UP_2
    TableEntry BATTLE_EFFECT_DEF_UP_2
    TableEntry BATTLE_EFFECT_SPEED_UP_2
    TableEntry BATTLE_EFFECT_SP_ATK_UP_2
    TableEntry BATTLE_EFFECT_SP_DEF_UP_2
    TableEntry BATTLE_EFFECT_ACC_UP_2
    TableEntry BATTLE_EFFECT_EVA_UP_2
    TableEntry BATTLE_EFFECT_ATK_DOWN_2
    TableEntry BATTLE_EFFECT_DEF_DOWN_2
    TableEntry BATTLE_EFFECT_SPEED_DOWN_2
    TableEntry BATTLE_EFFECT_SP_ATK_DOWN_2
    TableEntry BATTLE_EFFECT_SP_DEF_DOWN_2
    TableEntry BATTLE_EFFECT_EVA_DOWN_2
    TableEntry BATTLE_EFFECT_ACC_DOWN_2
    TableEntry BATTLE_EFFECT_SET_REFLECT
    TableEntry BATTLE_EFFECT_STATUS_POISON
    TableEntry BATTLE_EFFECT_STATUS_PARALYZE
    TableEntry BATTLE_EFFECT_SET_SUBSTITUTE
    TableEntry BATTLE_EFFECT_STATUS_LEECH_SEED
    TableEntry BATTLE_EFFECT_EVA_UP_2_MINIMIZE
    TableEntry BATTLE_EFFECT_CURSE
    TableEntry BATTLE_EFFECT_ATK_UP_2_STATUS_CONFUSION
    TableEntry BATTLE_EFFECT_STATUS_SLEEP_NEXT_TURN
    TableEntry BATTLE_EFFECT_DEF_UP_DOUBLE_ROLLOUT_POWER
    TableEntry BATTLE_EFFECT_TORMENT
    TableEntry BATTLE_EFFECT_SP_ATK_UP_CAUSE_CONFUSION
    TableEntry BATTLE_EFFECT_STATUS_BURN
    TableEntry BATTLE_EFFECT_GROUND_TRAP_USER_CONTINUOUS_HEAL
    TableEntry BATTLE_EFFECT_CONFUSE_ALL
    TableEntry BATTLE_EFFECT_ATK_DEF_DOWN
    TableEntry BATTLE_EFFECT_DEF_SPD_UP
    TableEntry BATTLE_EFFECT_ATK_DEF_UP
    TableEntry BATTLE_EFFECT_SP_ATK_SP_DEF_UP
    TableEntry BATTLE_EFFECT_DOUBLE_SPEED_3_TURNS
    TableEntry BATTLE_EFFECT_GIVE_GROUND_IMMUNITY
    TableEntry BATTLE_EFFECT_REMOVE_HAZARDS_SCREENS_EVA_DOWN
    TableEntry TABLE_END

PrioritizeExtremes_Main:
    // Do not target your partner.
    IfTargetIsPartner Terminate

    // This routine applies to move effects which:
    //   1. have variable power,
    //   2. deal flat damage,
    //   3. are associated with a high base-power, or
    //   4. have zero power (i.e., status moves).
    //
    // For a full list of move effects which fit one of the first three criteria,
    // refer to sNoDamageCalcMoveEffects and sAltPowerMoveEffects.
    FlagMoveDamageScore USE_MAX_DAMAGE
    IfLoadedNotEqualTo AI_NO_COMPARISON_MADE, PrioritizeExtremes_Terminate

    // ~61% of the time, score +2.
    IfRandomLessThan 100, PrioritizeExtremes_Terminate
    AddToMoveScore 2

PrioritizeExtremes_Terminate:
    PopOrEnd 

Risky_Main:
    // Do not target your partner.
    IfTargetIsPartner Terminate

    // Only apply this routine to certain move effects.
    LoadCurrentMoveEffect 
    IfLoadedNotInTable Risky_RiskyEffects, Risky_Terminate

    // 50% of the time, score +2.
    IfRandomLessThan 128, Risky_Terminate
    AddToMoveScore 2

Risky_Terminate:
    PopOrEnd 

Risky_RiskyEffects:
    TableEntry BATTLE_EFFECT_STATUS_SLEEP
    TableEntry BATTLE_EFFECT_HALVE_DEFENSE
    TableEntry BATTLE_EFFECT_HALVE_SP_DEFENSE
    TableEntry BATTLE_EFFECT_COPY_MOVE
    TableEntry BATTLE_EFFECT_ONE_HIT_KO
    TableEntry BATTLE_EFFECT_HIGH_CRITICAL
    TableEntry BATTLE_EFFECT_STATUS_CONFUSE
    TableEntry BATTLE_EFFECT_CALL_RANDOM_MOVE
    TableEntry BATTLE_EFFECT_RANDOM_DAMAGE_1_TO_150_LEVEL
    TableEntry BATTLE_EFFECT_COUNTER
    TableEntry BATTLE_EFFECT_KO_MON_THAT_DEFEATED_USER
    TableEntry BATTLE_EFFECT_ATK_UP_2_STATUS_CONFUSION
    TableEntry BATTLE_EFFECT_INFATUATE
    TableEntry BATTLE_EFFECT_RANDOM_POWER_MAYBE_HEAL
    TableEntry BATTLE_EFFECT_RAISE_ALL_STATS_HIT
    TableEntry BATTLE_EFFECT_MAX_ATK_LOSE_HALF_MAX_HP
    TableEntry BATTLE_EFFECT_MIRROR_COAT
    TableEntry BATTLE_EFFECT_HIT_LAST_WHIFF_IF_HIT
    TableEntry BATTLE_EFFECT_DOUBLE_POWER_IF_HIT
    TableEntry BATTLE_EFFECT_CONFUSE_ALL
    TableEntry BATTLE_EFFECT_POWER_BASED_ON_LOW_SPEED
    TableEntry BATTLE_EFFECT_METAL_BURST
    TableEntry BATTLE_EFFECT_DOUBLE_POWER_IF_MOVING_SECOND
    TableEntry BATTLE_EFFECT_USE_MOVE_FIRST
    TableEntry BATTLE_EFFECT_HIT_FIRST_IF_TARGET_ATTACKING
    TableEntry TABLE_END

BatonPass_Main:
    IfTargetIsPartner Terminate

    // If there are no other party members alive, break.
    CountAlivePartyBattlers AI_BATTLER_ATTACKER
    IfLoadedEqualTo 0, BatonPass_Terminate

    // If the move deals damage, ignore it for this flag.
    FlagMoveDamageScore USE_MAX_DAMAGE
    IfLoadedNotEqualTo AI_NO_COMPARISON_MADE, BatonPass_Terminate

    // If the attacker does not know Baton Pass, 31.25% chance of no score changes.
    IfMoveEffectKnown AI_BATTLER_ATTACKER, BATTLE_EFFECT_PASS_STATS_AND_STATUS, BatonPass_EvalMove
    IfRandomLessThan 80, Risky_Terminate

BatonPass_EvalMove:
    // Handle these +2 boosting moves separately.
    IfMoveEqualTo MOVE_SWORDS_DANCE, BatonPass_SetupAtHighHP
    IfMoveEqualTo MOVE_DRAGON_DANCE, BatonPass_SetupAtHighHP
    IfMoveEqualTo MOVE_CALM_MIND, BatonPass_SetupAtHighHP
    IfMoveEqualTo MOVE_NASTY_PLOT, BatonPass_SetupAtHighHP

    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_PROTECT, BatonPass_EvalProtect
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_PROTECT_HURT_ON_CONTACT, BatonPass_EvalProtect
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_PROTECT_LOWER_SPEED_CONTACT, BatonPass_EvalProtect

    IfMoveEqualTo MOVE_BATON_PASS, BatonPass_EvalBatonPass

    // ~92% of the time, score +3.
    IfRandomLessThan 20, Risky_Terminate
    AddToMoveScore 3

BatonPass_SetupAtHighHP:
    // On turn 1 of the entire battle, score +5.
    LoadTurnCount 
    IfLoadedEqualTo 0, ScorePlus5

    // If the attacker is at < 60% HP, score -10.
    IfHPPercentLessThan AI_BATTLER_ATTACKER, 60, ScoreMinus10

    // Otherwise, score +1.
    GoTo ScorePlus1

BatonPass_EvalProtect:
    // If the current move's effect is Protect and the last move that we used
    // is either Detect or Protect, score -2.
    LoadBattlerPreviousMove AI_BATTLER_ATTACKER
    IfLoadedInTable BatonPass_ProtectDetect, ScoreMinus2

    // Else, score +2.
    AddToMoveScore 2
    PopOrEnd 

BatonPass_ProtectDetect:
    TableEntry MOVE_PROTECT
    TableEntry MOVE_DETECT
    TableEntry MOVE_SPIKY_SHIELD
    TableEntry TABLE_END

BatonPass_EvalBatonPass:
    // On turn 1 of the entire battle, score -2.
    LoadTurnCount 
    IfLoadedEqualTo 0, ScoreMinus2

    // Score +1 for each positive stat stage for Attack or Special Attack
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_ATTACK, 8, ScorePlus3
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_ATTACK, 7, ScorePlus2
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_ATTACK, 6, ScorePlus1
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_ATTACK, 8, ScorePlus3
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_ATTACK, 7, ScorePlus2
    IfStatStageGreaterThan AI_BATTLER_ATTACKER, BATTLE_STAT_SP_ATTACK, 6, ScorePlus1
    PopOrEnd 

BatonPass_Terminate:
    PopOrEnd 

TagStrategy_Main:
    IfTargetIsPartner TagStrategy_Partner

    // If the move does not deal damage, skip ahead
    FlagMoveDamageScore USE_MAX_DAMAGE
    IfLoadedEqualTo AI_NO_COMPARISON_MADE, TagStrategy_CheckSpecialScoring

    // Flat-damage move effects have a special handler; this includes OHKO moves
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ONE_HIT_KO, TagStrategy_ScoreMove
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_40_DAMAGE_FLAT, TagStrategy_ScoreMove
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_LEVEL_DAMAGE_FLAT, TagStrategy_ScoreMove
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_RANDOM_DAMAGE_1_TO_150_LEVEL, TagStrategy_ScoreMove
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_20_DAMAGE_FLAT, TagStrategy_ScoreMove

    // If the move is not-very-effective, try to reduce its score
    IfMoveEffectivenessEquals TYPE_MULTI_HALF_DAMAGE, TagStrategy_TryScoreMinus1
    IfMoveEffectivenessEquals TYPE_MULTI_QUARTER_DAMAGE, TagStrategy_TryScoreMinus2

    // All other moves
    GoTo TagStrategy_ScoreMove

TagStrategy_TryScoreMinus1:
    // If the maximum roll would kill, do not reduce the score
    IfCurrentMoveKills USE_MAX_DAMAGE, TagStrategy_ScoreMove

    // If the target is on their last Pokemon, do not reduce the score
    IfHPPercentEqualTo AI_BATTLER_DEFENDER_PARTNER, 0, TagStrategy_ScoreMove

    // 75% of the time, reduce score by 1
    IfRandomLessThan 64, TagStrategy_ScoreMove
    AddToMoveScore -1
    GoTo TagStrategy_ScoreMove

TagStrategy_TryScoreMinus2:
    // If the maximum roll would kill, do not reduce the score
    IfCurrentMoveKills USE_MAX_DAMAGE, TagStrategy_ScoreMove

    // If the target is on their last Pokemon, do not reduce the score
    IfHPPercentEqualTo AI_BATTLER_DEFENDER_PARTNER, 0, TagStrategy_ScoreMove

    // 75% of the time, reduce score by 2
    IfRandomLessThan 64, TagStrategy_ScoreMove
    AddToMoveScore -2
    GoTo TagStrategy_ScoreMove

TagStrategy_ScoreMove:
    // If this is not a highest-damage move for the attacking side, handle the move "normally"
    CheckIfHighestDamageWithPartner USE_MAX_DAMAGE
    IfLoadedNotEqualTo AI_MOVE_IS_HIGHEST_DAMAGE, TagStrategy_CheckBeforeScoring

    // Handle Explosion and Self-Destruct like "normal" moves
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_HALVE_DEFENSE, TagStrategy_CheckSpecialScoring
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_HALVE_SP_DEFENSE, TagStrategy_CheckSpecialScoring

    // Sometimes prioritize using priority +1 moves
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_PRIORITY_1, TagStrategy_TryScorePlus1

    // 50% of the time, increase score by 1
    IfRandomLessThan 128, TagStrategy_CheckBeforeScoring
    AddToMoveScore 1

    // Proceed to "normal" handling
    GoTo TagStrategy_CheckSpecialScoring

TagStrategy_TryScorePlus1:
    // ~80.5% of the time, increase score by 1
    IfRandomLessThan 50, TagStrategy_CheckBeforeScoring
    AddToMoveScore 1
    GoTo TagStrategy_CheckSpecialScoring

TagStrategy_CheckBeforeScoring:
    // Flat-damage move effects have a special handler; this includes OHKO moves
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ONE_HIT_KO, TagStrategy_CheckSpecialScoring
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_40_DAMAGE_FLAT, TagStrategy_CheckSpecialScoring
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_LEVEL_DAMAGE_FLAT, TagStrategy_CheckSpecialScoring
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_RANDOM_DAMAGE_1_TO_150_LEVEL, TagStrategy_CheckSpecialScoring
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_20_DAMAGE_FLAT, TagStrategy_CheckSpecialScoring

    // If the move is super-effective, try to increase its score
    IfMoveEffectivenessEquals TYPE_MULTI_DOUBLE_DAMAGE, TagStrategy_TryPrioritizingDoubleEffective
    IfMoveEffectivenessEquals TYPE_MULTI_QUADRUPLE_DAMAGE, TagStrategy_TryPrioritizingQuadEffective

    GoTo TagStrategy_CheckSpecialScoring

TagStrategy_TryPrioritizingDoubleEffective:
    // ~61% of the time, score +1
    IfRandomLessThan 100, TagStrategy_CheckSpecialScoring
    AddToMoveScore 1
    GoTo TagStrategy_CheckSpecialScoring

TagStrategy_TryPrioritizingQuadEffective:
    // 75% of the time, score +1
    IfRandomLessThan 64, TagStrategy_CheckSpecialScoring
    AddToMoveScore 1
    GoTo TagStrategy_CheckSpecialScoring

TagStrategy_CheckSpecialScoring:
    // Handle each of these moves with their own routine
    IfMoveEqualTo MOVE_SKILL_SWAP, TagStrategy_SkillSwap
    LoadTypeFrom LOAD_MOVE_TYPE
    IfMoveEqualTo MOVE_RAIN_DANCE, TagStrategy_RainDance
    IfMoveEqualTo MOVE_SUNNY_DAY, TagStrategy_SunnyDay
    IfMoveEqualTo MOVE_HAIL, TagStrategy_Hail
    IfMoveEqualTo MOVE_SANDSTORM, TagStrategy_Sandstorm
    IfMoveEqualTo MOVE_GRAVITY, TagStrategy_Gravity
    IfMoveEqualTo MOVE_TRICK_ROOM, TagStrategy_TrickRoom
    IfMoveEqualTo MOVE_FOLLOW_ME, TagStrategy_FollowMe
    LoadTypeFrom LOAD_MOVE_TYPE
    IfLoadedEqualTo TYPE_ELECTRIC, TagStrategy_CheckElectricMove
    IfLoadedEqualTo TYPE_FIRE, TagStrategy_CheckFireMove
    IfLoadedEqualTo TYPE_WATER, TagStrategy_CheckWaterMove
    IfLoadedEqualTo TYPE_GROUND, TagStrategy_CheckGroundMove
    IfMoveKnown AI_BATTLER_ATTACKER_PARTNER, MOVE_HELPING_HAND, TagStrategy_PartnerKnowsHelpingHand
    PopOrEnd 

TagStrategy_RainDance:
    // If the move is Rain Dance, apply modifiers for each of the attacker and partner which meet the
    // following conditions:
    //  - The battler has Hydration and is currently statused -> score +2
    //  - The battler has Dry Skin -> score +2
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_HYDRATION, TagStrategy_RainDance_SelfHasHydration
    IfLoadedEqualTo ABILITY_DRY_SKIN, TagStrategy_RainDance_SelfScorePlus2
    GoTo TagStrategy_RainDance_CheckPartner

TagStrategy_RainDance_SelfHasHydration:
    IfNotStatus AI_BATTLER_ATTACKER, MON_CONDITION_ANY, TagStrategy_RainDance_CheckPartner

TagStrategy_RainDance_SelfScorePlus2:
    AddToMoveScore 2
    GoTo TagStrategy_RainDance_CheckPartner

TagStrategy_RainDance_CheckPartner:
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_HYDRATION
    IfLoadedEqualTo AI_HAVE, TagStrategy_RainDance_PartnerHasHydration
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_DRY_SKIN
    IfLoadedEqualTo AI_HAVE, TagStrategy_RainDance_PartnerScorePlus2
    GoTo TagStrategy_RainDance_End

TagStrategy_RainDance_PartnerHasHydration:
    IfNotStatus AI_BATTLER_ATTACKER_PARTNER, MON_CONDITION_ANY, TagStrategy_RainDance_End

TagStrategy_RainDance_PartnerScorePlus2:
    AddToMoveScore 2
    GoTo TagStrategy_RainDance_End

TagStrategy_RainDance_End:
    PopOrEnd 

TagStrategy_SunnyDay:
    // If the move is Sunny Day, apply modifiers for each of the attacker and partner which meet the
    // following conditions:
    //  - The battler has Leaf Guard, is not currently statused, and is at 30% HP or higher -> score +2
    //  - The battler has Flower Gift -> score +2
    //  - The battler has Dry Skin -> score -2
    //  - The battler has Solar Power and is at 50% HP or higher -> score +1
    //  - The battler has Solar Power, is at less than 50% HP -> 50% chance of score -2
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_LEAF_GUARD, TagStrategy_SunnyDay_SelfHasLeafGuard
    IfLoadedEqualTo ABILITY_FLOWER_GIFT, TagStrategy_SunnyDay_SelfScorePlus2
    IfLoadedEqualTo ABILITY_DRY_SKIN, TagStrategy_SunnyDay_SelfScoreMinus2
    IfLoadedEqualTo ABILITY_SOLAR_POWER, TagStrategy_SunnyDay_SelfHasSolarPower
    GoTo TagStrategy_SunnyDay_CheckPartner

TagStrategy_SunnyDay_SelfHasLeafGuard:
    IfStatus AI_BATTLER_ATTACKER, MON_CONDITION_ANY, TagStrategy_SunnyDay_CheckPartner
    IfHPPercentLessThan AI_BATTLER_ATTACKER, 30, TagStrategy_SunnyDay_CheckPartner

TagStrategy_SunnyDay_SelfScorePlus2:
    AddToMoveScore 2
    GoTo TagStrategy_SunnyDay_CheckPartner

TagStrategy_SunnyDay_SelfScoreMinus2:
    AddToMoveScore -2
    GoTo TagStrategy_SunnyDay_CheckPartner

TagStrategy_SunnyDay_SelfHasSolarPower:
    IfHPPercentLessThan AI_BATTLER_ATTACKER, 50, TagStrategy_SunnyDay_SelfTryScoreMinus2
    AddToMoveScore 1

TagStrategy_SunnyDay_SelfTryScoreMinus2:
    IfRandomLessThan 128, TagStrategy_SunnyDay_CheckPartner
    AddToMoveScore -2

TagStrategy_SunnyDay_CheckPartner:
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_LEAF_GUARD
    IfLoadedEqualTo AI_HAVE, TagStrategy_SunnyDay_PartnerHasLeafGuard
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_FLOWER_GIFT
    IfLoadedEqualTo AI_HAVE, TagStrategy_SunnyDay_PartnerScorePlus2
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_DRY_SKIN
    IfLoadedEqualTo AI_HAVE, TagStrategy_SunnyDay_PartnerScoreMinus2
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_SOLAR_POWER
    IfLoadedEqualTo AI_HAVE, TagStrategy_SunnyDay_PartnerHasSolarPower
    GoTo TagStrategy_SunnyDay_End

TagStrategy_SunnyDay_PartnerHasLeafGuard:
    IfStatus AI_BATTLER_ATTACKER_PARTNER, MON_CONDITION_ANY, TagStrategy_SunnyDay_End
    IfHPPercentLessThan AI_BATTLER_ATTACKER_PARTNER, 30, TagStrategy_SunnyDay_End

TagStrategy_SunnyDay_PartnerScorePlus2:
    AddToMoveScore 2
    GoTo TagStrategy_SunnyDay_End

TagStrategy_SunnyDay_PartnerScoreMinus2:
    AddToMoveScore -2
    GoTo TagStrategy_SunnyDay_End

TagStrategy_SunnyDay_PartnerHasSolarPower:
    IfHPPercentLessThan AI_BATTLER_ATTACKER_PARTNER, 50, TagStrategy_SunnyDay_PartnerTryScoreMinus2
    AddToMoveScore 1

TagStrategy_SunnyDay_PartnerTryScoreMinus2:
    IfRandomLessThan 128, TagStrategy_SunnyDay_End
    AddToMoveScore -2

TagStrategy_SunnyDay_End:
    PopOrEnd 

TagStrategy_Hail:
    // If the move is Hail, apply modifiers for each of the attacker and partner which meet the
    // following conditions:
    //  - The battler has Ice Body -> score +2
    //  - The battler has Snow Cloak -> score +2
    //  - The battler knows Blizzard -> score +2
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_ICE_BODY, TagStrategy_Hail_SelfScorePlus2
    IfLoadedEqualTo ABILITY_SNOW_CLOAK, TagStrategy_Hail_SelfScorePlus2
    IfMoveKnown AI_BATTLER_ATTACKER, MOVE_BLIZZARD, TagStrategy_Hail_SelfScorePlus2
    GoTo TagStrategy_Hail_CheckPartner

TagStrategy_Hail_SelfScorePlus2:
    AddToMoveScore 2

TagStrategy_Hail_CheckPartner:
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_ICE_BODY
    IfLoadedEqualTo AI_HAVE, TagStrategy_Hail_PartnerScorePlus2
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_SNOW_CLOAK
    IfLoadedEqualTo AI_HAVE, TagStrategy_Hail_PartnerScorePlus2
    IfMoveKnown AI_BATTLER_ATTACKER_PARTNER, MOVE_BLIZZARD, TagStrategy_Hail_PartnerScorePlus2
    GoTo TagStrategy_Hail_End

TagStrategy_Hail_PartnerScorePlus2:
    AddToMoveScore 2

TagStrategy_Hail_End:
    PopOrEnd 

TagStrategy_Sandstorm:
    // If the move is Sandstorm, apply modifiers for each of the attacker and partner which meet the
    // following conditions:
    //  - The battler has Sand Veil -> score +2
    //  - The battler has a Rock typing -> score +2
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_SAND_VEIL, TagStrategy_Sandstorm_SelfScorePlus2
    LoadTypeFrom LOAD_ATTACKER_TYPE_1
    IfLoadedEqualTo TYPE_ROCK, TagStrategy_Sandstorm_SelfScorePlus2
    LoadTypeFrom LOAD_ATTACKER_TYPE_2
    IfLoadedEqualTo TYPE_ROCK, TagStrategy_Sandstorm_SelfScorePlus2
    GoTo TagStrategy_Sandstorm_CheckPartner

TagStrategy_Sandstorm_SelfScorePlus2:
    AddToMoveScore 2
    GoTo TagStrategy_Sandstorm_CheckPartner

TagStrategy_Sandstorm_CheckPartner:
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_SAND_VEIL
    IfLoadedEqualTo AI_HAVE, TagStrategy_Sandstorm_PartnerScorePlus2
    LoadTypeFrom LOAD_ATTACKER_PARTNER_TYPE_1
    IfLoadedEqualTo TYPE_ROCK, TagStrategy_Sandstorm_PartnerScorePlus2
    LoadTypeFrom LOAD_ATTACKER_PARTNER_TYPE_2
    IfLoadedEqualTo TYPE_ROCK, TagStrategy_Sandstorm_PartnerScorePlus2
    GoTo TagStrategy_Sandstorm_End

TagStrategy_Sandstorm_PartnerScorePlus2:
    AddToMoveScore 2

TagStrategy_Sandstorm_End:
    PopOrEnd 

TagStrategy_Gravity:
    // If Gravity is currently active, score -30
    IfFieldConditionsMask FIELD_CONDITION_GRAVITY, TagStrategy_PartnerScoreMinus30

    // Apply the following score modifiers:
    //  - For each allied battler which has Levitate, a Flying typing, or is under the effect of
    //    Magnet Rise -> score -5
    //  - For each enemy battler which has Levitate, a Flying typing, or is under the effect of
    //    Magnet Rise -> 75% chance of score +3
    CheckBattlerAbility AI_BATTLER_ATTACKER, ABILITY_LEVITATE
    IfLoadedEqualTo AI_HAVE, TagStrategy_Gravity_SelfScoreMinus5
    FlagBattlerIsType AI_BATTLER_ATTACKER, TYPE_FLYING
    IfLoadedEqualTo AI_HAVE, TagStrategy_Gravity_SelfScoreMinus5
    IfMoveEffect AI_BATTLER_ATTACKER, MOVE_EFFECT_MAGNET_RISE, TagStrategy_Gravity_SelfScoreMinus5
    GoTo TagStrategy_Gravity_CheckPartner

TagStrategy_Gravity_SelfScoreMinus5:
    AddToMoveScore -5
    GoTo TagStrategy_Gravity_CheckPartner

TagStrategy_Gravity_CheckPartner:
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_LEVITATE
    IfLoadedEqualTo AI_HAVE, TagStrategy_Gravity_PartnerScoreMinus5
    FlagBattlerIsType AI_BATTLER_ATTACKER_PARTNER, TYPE_FLYING
    IfLoadedEqualTo AI_HAVE, TagStrategy_Gravity_PartnerScoreMinus5
    IfMoveEffect AI_BATTLER_ATTACKER_PARTNER, MOVE_EFFECT_MAGNET_RISE, TagStrategy_Gravity_PartnerScoreMinus5
    GoTo TagStrategy_Gravity_CheckTarget

TagStrategy_Gravity_PartnerScoreMinus5:
    AddToMoveScore -5
    GoTo TagStrategy_Gravity_CheckTarget

TagStrategy_Gravity_CheckTarget:
    CheckBattlerAbility AI_BATTLER_DEFENDER, ABILITY_LEVITATE
    IfLoadedEqualTo AI_HAVE, TagStrategy_Gravity_TargetTryScorePlus3
    FlagBattlerIsType AI_BATTLER_DEFENDER, TYPE_FLYING
    IfLoadedEqualTo AI_HAVE, TagStrategy_Gravity_TargetTryScorePlus3
    IfMoveEffect AI_BATTLER_DEFENDER, MOVE_EFFECT_MAGNET_RISE, TagStrategy_Gravity_TargetTryScorePlus3
    GoTo TagStrategy_Gravity_CheckTargetPartner

TagStrategy_Gravity_TargetTryScorePlus3:
    IfRandomLessThan 64, TagStrategy_Gravity_CheckTargetPartner
    AddToMoveScore 3
    GoTo TagStrategy_Gravity_CheckTargetPartner

TagStrategy_Gravity_CheckTargetPartner:
    CheckBattlerAbility AI_BATTLER_DEFENDER_PARTNER, ABILITY_LEVITATE
    IfLoadedEqualTo AI_HAVE, TagStrategy_Gravity_TargetPartnerTryScorePlus3
    FlagBattlerIsType AI_BATTLER_DEFENDER_PARTNER, TYPE_FLYING
    IfLoadedEqualTo AI_HAVE, TagStrategy_Gravity_TargetPartnerTryScorePlus3
    IfMoveEffect AI_BATTLER_DEFENDER_PARTNER, MOVE_EFFECT_MAGNET_RISE, TagStrategy_Gravity_TargetPartnerTryScorePlus3
    GoTo TagStrategy_Gravity_End

TagStrategy_Gravity_TargetPartnerTryScorePlus3:
    IfRandomLessThan 64, TagStrategy_Gravity_End
    AddToMoveScore 3
    GoTo TagStrategy_Gravity_End

TagStrategy_Gravity_End:
    PopOrEnd 

TagStrategy_TrickRoom:
    // If the battle has been reduced to either side having only one active Pokemon, score -30
    IfHPPercentEqualTo AI_BATTLER_ATTACKER_PARTNER, 0, ScoreMinus30
    IfHPPercentEqualTo AI_BATTLER_DEFENDER_PARTNER, 0, ScoreMinus30
    IfHPPercentEqualTo AI_BATTLER_DEFENDER, 0, ScoreMinus30

    // Branch according to the attacker's Speed-ordering in battle
    LoadBattlerSpeedRank AI_BATTLER_ATTACKER
    IfLoadedEqualTo 0, TagStrategy_TrickRoom_SelfMovesFirst
    IfLoadedEqualTo 1, TagStrategy_TrickRoom_SelfMovesSecond
    IfLoadedEqualTo 2, TagStrategy_TrickRoom_SelfMovesThird
    IfLoadedEqualTo 3, TagStrategy_TrickRoom_SelfMovesLast
    GoTo TagStrategy_TrickRoom_End

TagStrategy_TrickRoom_SelfMovesFirst:
    // If our partner moves second, score -30
    LoadBattlerSpeedRank AI_BATTLER_ATTACKER_PARTNER
    IfLoadedEqualTo 1, ScoreMinus30
    IfLoadedEqualTo 0, ScoreMinus30
    GoTo TagStrategy_TrickRoom_ScoreMinus5

TagStrategy_TrickRoom_SelfMovesSecond:
    // If our partner moves before us, score -30
    LoadBattlerSpeedRank AI_BATTLER_ATTACKER_PARTNER
    IfLoadedEqualTo 0, ScoreMinus30
    GoTo TagStrategy_TrickRoom_ScoreMinus5

TagStrategy_TrickRoom_SelfMovesThird:
    // If our partner does not move last in turn-order, score -5
    LoadBattlerSpeedRank AI_BATTLER_ATTACKER_PARTNER
    IfLoadedNotEqualTo 3, TagStrategy_TrickRoom_ScoreMinus5

    // 75% chance of score +5, 25% chance of score -5
    IfRandomLessThan 64, TagStrategy_TrickRoom_ScoreMinus5
    AddToMoveScore 5
    GoTo TagStrategy_TrickRoom_End

TagStrategy_TrickRoom_SelfMovesLast:
    // If our partner does not move third in turn-order, score -5
    LoadBattlerSpeedRank AI_BATTLER_ATTACKER_PARTNER
    IfLoadedNotEqualTo 2, TagStrategy_TrickRoom_ScoreMinus5

    // 75% chance of score +5, 25% chance of score -5
    IfRandomLessThan 64, TagStrategy_TrickRoom_ScoreMinus5
    AddToMoveScore 5
    GoTo TagStrategy_TrickRoom_End

TagStrategy_TrickRoom_ScoreMinus5:
    AddToMoveScore -5

TagStrategy_TrickRoom_End:
    PopOrEnd 

TagStrategy_FollowMe:
    // If the move is Follow Me, apply a score modifier according to the following conditional tree:
    //  - If the attacker's HP > 90%, and:
    //    - If the partner's HP > 90%, 75% chance of score -1
    //    - If the partner's HP is between 50% and 90%, 75% chance of score +1
    //    - If the partner's HP is between 30% and 50%, 75% chance of score +2
    //    - If the partner's HP is < 30%, 75% chance of score +3
    //  - If the attacker's HP is between 50% and 90%, and:
    //    - If the partner's HP > 90%, 75% chance of score -2
    //    - If the partner's HP is between 50% and 90%, 75% chance of score -1
    //    - If the partner's HP is between 30% and 50%, 75% chance of score +1
    //    - If the partner's HP is < 30%, 75% chance of score +2
    //  - If the attacker's HP is between 30% and 50%, and:
    //    - If the partner's HP > 90%, 75% chance of score -2
    //    - If the partner's HP is between 50% and 90%, 75% chance of score -2
    //    - If the partner's HP is between 30% and 50%, 75% chance of score +1
    //    - If the partner's HP is < 30%, 75% chance of score +2
    //  - If the attacker's HP < 30%, 75% chance of score -5
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER, 90, TagStrategy_FollowMe_SelfHighHP
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER, 50, TagStrategy_FollowMe_SelfMediumHP
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER, 30, TagStrategy_FollowMe_SelfLowHP
    IfRandomLessThan 64, TagStrategy_FollowMe_End
    GoTo ScoreMinus5

TagStrategy_FollowMe_SelfHighHP:
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER_PARTNER, 90, TagStrategy_FollowMe_TryScoreMinus1
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER_PARTNER, 50, TagStrategy_FollowMe_TryScorePlus1
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER_PARTNER, 30, TagStrategy_FollowMe_TryScorePlus2
    GoTo TagStrategy_FollowMe_TryScorePlus3

TagStrategy_FollowMe_SelfMediumHP:
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER_PARTNER, 90, TagStrategy_FollowMe_TryScoreMinus2
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER_PARTNER, 50, TagStrategy_FollowMe_TryScoreMinus1
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER_PARTNER, 30, TagStrategy_FollowMe_TryScorePlus1
    GoTo TagStrategy_FollowMe_TryScorePlus2

TagStrategy_FollowMe_SelfLowHP:
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER_PARTNER, 90, TagStrategy_FollowMe_TryScoreMinus2
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER_PARTNER, 50, TagStrategy_FollowMe_TryScoreMinus2
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER_PARTNER, 30, TagStrategy_FollowMe_TryScorePlus1
    GoTo TagStrategy_FollowMe_TryScorePlus2

TagStrategy_FollowMe_TryScoreMinus1:
    IfRandomLessThan 64, TagStrategy_FollowMe_End
    AddToMoveScore -1
    GoTo TagStrategy_FollowMe_End

TagStrategy_FollowMe_TryScoreMinus2:
    IfRandomLessThan 64, TagStrategy_FollowMe_End
    AddToMoveScore -2
    GoTo TagStrategy_FollowMe_End

TagStrategy_FollowMe_TryScorePlus1:
    IfRandomLessThan 64, TagStrategy_FollowMe_End
    AddToMoveScore 1
    GoTo TagStrategy_FollowMe_End

TagStrategy_FollowMe_TryScorePlus2:
    IfRandomLessThan 64, TagStrategy_FollowMe_End
    AddToMoveScore 2
    GoTo TagStrategy_FollowMe_End

TagStrategy_FollowMe_TryScorePlus3:
    IfRandomLessThan 64, TagStrategy_FollowMe_End
    AddToMoveScore 3
    GoTo TagStrategy_FollowMe_End

TagStrategy_FollowMe_End:
    PopOrEnd 

TagStrategy_PartnerKnowsHelpingHand:
    // If our partner knows Helping Hand, then damaging moves (aside from flat-damage moves)
    // get score +1
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_ONE_HIT_KO, TagStrategy_PartnerHelpingHand_End
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_40_DAMAGE_FLAT, TagStrategy_PartnerHelpingHand_End
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_LEVEL_DAMAGE_FLAT, TagStrategy_PartnerHelpingHand_End
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_RANDOM_DAMAGE_1_TO_150_LEVEL, TagStrategy_PartnerHelpingHand_End
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_20_DAMAGE_FLAT, TagStrategy_PartnerHelpingHand_End
    FlagMoveDamageScore USE_MAX_DAMAGE
    IfLoadedNotEqualTo AI_NO_COMPARISON_MADE, ScorePlus1

TagStrategy_PartnerHelpingHand_End:
    PopOrEnd 

TagStrategy_Unused_1:
    IfStatus AI_BATTLER_ATTACKER, MON_CONDITION_ANY, TagStrategy_Unused_2
    PopOrEnd 

TagStrategy_Unused_2:
    FlagMoveDamageScore USE_MAX_DAMAGE
    IfLoadedEqualTo AI_NO_COMPARISON_MADE, ScoreMinus5
    AddToMoveScore 1
    IfLoadedEqualTo AI_MOVE_IS_HIGHEST_DAMAGE, ScorePlus2
    PopOrEnd 

TagStrategy_SkillSwap:
    // If the move is Skill Swap and:
    //  - The attacker has Truant, Slow Start, Stall, or Klutz, score +5
    //  - The target has Shadow Tag, Pure Power, Huge Power, Mold Breaker, Solid Rock, Filter, or
    //    Flower Gift, score +2
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_TRUANT, ScorePlus5
    IfLoadedEqualTo ABILITY_SLOW_START, ScorePlus5
    IfLoadedEqualTo ABILITY_STALL, ScorePlus5
    IfLoadedEqualTo ABILITY_KLUTZ, ScorePlus5
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_SHADOW_TAG, ScorePlus2
    IfLoadedEqualTo ABILITY_PURE_POWER, ScorePlus2
    IfLoadedEqualTo ABILITY_HUGE_POWER, ScorePlus2
    IfLoadedEqualTo ABILITY_MOLD_BREAKER, ScorePlus2
    IfLoadedEqualTo ABILITY_SOLID_ROCK, ScorePlus2
    IfLoadedEqualTo ABILITY_FILTER, ScorePlus2
    IfLoadedEqualTo ABILITY_FLOWER_GIFT, ScorePlus2
    PopOrEnd 

TagStrategy_CheckElectricMove:
    // If the move is Discharge, handle it similarly to Earthquake. Otherwise, apply all of the
    // following which are met:
    //  - The target's partner would redirect the move with Lightning Rod, score -1; additional
    //    score -8 if the target's partner is also a Ground type
    //  - The attacker's partner has Lightning Rod, score -10
    //
    // Stalwart ignores redirection entirely, so neither penalty applies to its user.
    IfMoveEqualTo MOVE_DISCHARGE, TagStrategy_SpreadElectricMove
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_STALWART, TagStrategy_CheckElectric_End
    CheckBattlerAbility AI_BATTLER_DEFENDER_PARTNER, ABILITY_LIGHTNING_ROD
    IfLoadedEqualTo AI_HAVE, TagStrategy_TargetProtectedByLightningRod
    GoTo TagStrategy_PartnerHasLightningRod

TagStrategy_TargetProtectedByLightningRod:
    AddToMoveScore -1
    FlagBattlerIsType AI_BATTLER_DEFENDER_PARTNER, TYPE_GROUND
    IfLoadedEqualTo AI_NOT_HAVE, TagStrategy_PartnerHasLightningRod
    AddToMoveScore -8

TagStrategy_PartnerHasLightningRod:
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_LIGHTNING_ROD
    IfLoadedEqualTo AI_HAVE, ScoreMinus10
    IfMoveEqualTo MOVE_DISCHARGE, TagStrategy_SpreadElectricMove
    GoTo TagStrategy_CheckElectric_End

TagStrategy_SpreadElectricMove:
    // If our partner has Volt Absorb or Motor Drive, score +3
    //
    // If our partner otherwise has a Water or Flying typing, score -10
    //
    // If our partner otherwise has a Ground typing, score +3
    //
    // Else, score -3
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_MOTOR_DRIVE
    IfLoadedEqualTo AI_HAVE, ScorePlus3
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_VOLT_ABSORB
    IfLoadedEqualTo AI_HAVE, ScorePlus3
    FlagBattlerIsType AI_BATTLER_ATTACKER_PARTNER, TYPE_WATER
    IfLoadedEqualTo AI_HAVE, ScoreMinus10
    FlagBattlerIsType AI_BATTLER_ATTACKER_PARTNER, TYPE_FLYING
    IfLoadedEqualTo AI_HAVE, ScoreMinus10

    // BUG: This should be before the checks for all other types; in its present position, the
    // vanilla trainer AI will never use Discharge if their partner is, e.g., Swampert or Gliscor
    // (which should be treated as Immune to the move, but are not).
    FlagBattlerIsType AI_BATTLER_ATTACKER_PARTNER, TYPE_GROUND
    IfLoadedEqualTo AI_HAVE, ScorePlus3
    AddToMoveScore -3

TagStrategy_CheckElectric_End:
    PopOrEnd 

TagStrategy_CheckWaterMove:
    // If the move is Surf, handle it similarly to Earthquake. Otherwise, apply all of the
    // following which are met:
    //  - The target's partner would redirect the move with Storm Drain, score -1
    //  - The attacker's partner has Storm Drain, score -10
    //
    // Stalwart ignores redirection entirely, so neither penalty applies to its user.
    IfMoveEqualTo MOVE_SURF, TagStrategy_SpreadWaterMove
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_STALWART, TagStrategy_CheckWater_End
    CheckBattlerAbility AI_BATTLER_DEFENDER_PARTNER, ABILITY_STORM_DRAIN
    IfLoadedEqualTo AI_NOT_HAVE, TagStrategy_CheckPartnerStormDrain
    AddToMoveScore -1

TagStrategy_CheckPartnerStormDrain:
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_STORM_DRAIN
    IfLoadedEqualTo AI_HAVE, ScoreMinus10

    // This line should never result in a branch
    IfMoveEqualTo MOVE_SURF, TagStrategy_SpreadWaterMove
    GoTo TagStrategy_CheckWater_End

TagStrategy_SpreadWaterMove:
    // If our partner has Dry Skin or Water Absorb, score +3
    //
    // If our partner otherwise has a Ground or Fire typing, score -10
    //
    // Else, score -3
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_DRY_SKIN
    IfLoadedEqualTo AI_HAVE, ScorePlus3
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_WATER_ABSORB
    IfLoadedEqualTo AI_HAVE, ScorePlus3

    // BUG: This should also include a similar check for the Rock type
    FlagBattlerIsType AI_BATTLER_ATTACKER_PARTNER, TYPE_GROUND
    IfLoadedEqualTo AI_HAVE, ScoreMinus10
    FlagBattlerIsType AI_BATTLER_ATTACKER_PARTNER, TYPE_FIRE
    IfLoadedEqualTo AI_HAVE, ScoreMinus10
    AddToMoveScore -3

TagStrategy_CheckWater_End:
    PopOrEnd 

TagStrategy_CheckGroundMove:
    // If the move is Earthquake or Magnitude, check spread. Otherwise, apply all of the
    // following which are met:
    IfMoveEqualTo MOVE_EARTHQUAKE, TagStrategy_SpreadGroundMove
    IfMoveEqualTo MOVE_MAGNITUDE, TagStrategy_SpreadGroundMove
    GoTo TagStrategy_CheckGround_End

TagStrategy_SpreadGroundMove:
    // If our partner has Earth Eater or Levitate, score +3
    //
    // If our partner is weak to Ground, score -10
    //
    // Else, score -3
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_EARTH_EATER
    IfLoadedEqualTo AI_HAVE, ScorePlus3
    IfMoveEffect AI_BATTLER_ATTACKER_PARTNER, MOVE_EFFECT_MAGNET_RISE, Expert_Haze_TryScorePlus3
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_LEVITATE
    IfLoadedEqualTo AI_HAVE, ScorePlus3
    FlagBattlerIsType AI_BATTLER_ATTACKER_PARTNER, TYPE_FLYING
    IfLoadedEqualTo AI_HAVE, ScorePlus3

    FlagBattlerIsType AI_BATTLER_ATTACKER_PARTNER, TYPE_ROCK
    IfLoadedEqualTo AI_HAVE, ScoreMinus10
    FlagBattlerIsType AI_BATTLER_ATTACKER_PARTNER, TYPE_FIRE
    IfLoadedEqualTo AI_HAVE, ScoreMinus10
    FlagBattlerIsType AI_BATTLER_ATTACKER_PARTNER, TYPE_ELECTRIC
    IfLoadedEqualTo AI_HAVE, ScoreMinus10
    FlagBattlerIsType AI_BATTLER_ATTACKER_PARTNER, TYPE_STEEL
    IfLoadedEqualTo AI_HAVE, ScoreMinus10
    FlagBattlerIsType AI_BATTLER_ATTACKER_PARTNER, TYPE_POISON
    IfLoadedEqualTo AI_HAVE, ScoreMinus10
    AddToMoveScore -3

TagStrategy_CheckGround_End:
    PopOrEnd 

TagStrategy_CheckFireMove:
    // If the AI's Flash Fire has been activated, score additional +1 on top of all further modifiers
    //
    // If the move is Lava Plume, then:
    //  - If our partner has Dry Skin or Flash Fire, score +3
    //  - If our partner has a Grass, Steel, Ice, or Bug typing, score -10
    //  - Otherwise, score -3
    IfActivatedFlashFire AI_BATTLER_ATTACKER, TagStrategy_FlashFireScorePlus1
    GoTo TagStrategy_CheckLavaPlume

TagStrategy_FlashFireScorePlus1:
    AddToMoveScore 1

TagStrategy_CheckLavaPlume:
    IfMoveEqualTo MOVE_LAVA_PLUME, TagStrategy_SpreadFireMove
    GoTo TagStrategy_CheckFire_End

TagStrategy_SpreadFireMove:
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_DRY_SKIN
    IfLoadedEqualTo AI_HAVE, ScoreMinus3
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_FLASH_FIRE
    IfLoadedEqualTo AI_HAVE, ScorePlus3
    FlagBattlerIsType AI_BATTLER_ATTACKER_PARTNER, TYPE_GRASS
    IfLoadedEqualTo AI_HAVE, ScoreMinus10
    FlagBattlerIsType AI_BATTLER_ATTACKER_PARTNER, TYPE_STEEL
    IfLoadedEqualTo AI_HAVE, ScoreMinus10
    FlagBattlerIsType AI_BATTLER_ATTACKER_PARTNER, TYPE_ICE
    IfLoadedEqualTo AI_HAVE, ScoreMinus10
    FlagBattlerIsType AI_BATTLER_ATTACKER_PARTNER, TYPE_BUG
    IfLoadedEqualTo AI_HAVE, ScoreMinus10
    AddToMoveScore -3

TagStrategy_CheckFire_End:
    PopOrEnd 

TagStrategy_Partner:
    IfBattlerFainted AI_BATTLER_ATTACKER_PARTNER, TagStrategy_PartnerScoreMinus30
    FlagMoveDamageScore USE_MAX_DAMAGE
    IfLoadedEqualTo AI_NO_COMPARISON_MADE, TagStrategy_PartnerStatusMove
    LoadTypeFrom LOAD_MOVE_TYPE
    IfLoadedEqualTo TYPE_FIRE, TagStrategy_CheckPartnerFireAbsorption
    IfLoadedEqualTo TYPE_ELECTRIC, TagStrategy_CheckPartnerElectricAbsorption
    IfLoadedEqualTo TYPE_WATER, TagStrategy_CheckPartnerWaterAbsorption
    IfMoveEqualTo MOVE_FLING, TagStrategy_PartnerTrick

TagStrategy_ScoreMinus30:
    GoTo ScoreMinus30

TagStrategy_CheckPartnerFireAbsorption:
    // If our partner has Flash Fire and has not yet activated Flash Fire, score +3
    //
    // Otherwise, score -30
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_FLASH_FIRE
    IfLoadedEqualTo AI_HAVE, TagStrategy_CheckPartnerFlashFireActive
    GoTo TagStrategy_ScoreMinus30

TagStrategy_CheckPartnerFlashFireActive:
    IfActivatedFlashFire AI_BATTLER_ATTACKER_PARTNER, TagStrategy_ScoreMinus30
    GoTo ScorePlus3

TagStrategy_CheckPartnerElectricAbsorption:
    // If our partner has Motor Drive:
    //  - 62.5% chance of no score change
    //  - If our partner is at +6 speed, score -30
    //  - Else, score +3
    //
    // If our partner has Volt Absorb:
    //  - If our partner is at 100% HP, score -10
    //  - If our partner's HP >90%, no score change
    //  - If our partner's HP >75%, 25% chance of score +3, 75% chance of no change
    //  - If our partner's HP >50%, 50% chance of score +3, 50% chance of no change
    //  - Else, 75% chance of score +3, 25% chance of no change
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_MOTOR_DRIVE
    IfLoadedEqualTo AI_HAVE, TagStrategy_CheckPartnerMotorDrive
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_VOLT_ABSORB
    IfLoadedEqualTo AI_HAVE, TagStrategy_CheckPartnerVoltAbsorb
    GoTo TagStrategy_ScoreMinus30

TagStrategy_CheckPartnerMotorDrive:
    IfRandomLessThan 160, TagStrategy_CheckElectricAbsorption_End
    IfStatStageEqualTo AI_BATTLER_ATTACKER_PARTNER, BATTLE_STAT_SPEED, 12, TagStrategy_ScoreMinus30
    GoTo ScorePlus3

TagStrategy_CheckPartnerVoltAbsorb:
    IfHPPercentEqualTo AI_BATTLER_ATTACKER_PARTNER, 100, ScoreMinus10
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER_PARTNER, 90, TagStrategy_CheckElectricAbsorption_End
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER_PARTNER, 75, TagStrategy_PartnerVoltAbsorb_75PercentHP
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER_PARTNER, 50, TagStrategy_PartnerVoltAbsorb_50PercentHP
    GoTo TagStrategy_PartnerVoltAbsorb_LessThan50PercentHP

TagStrategy_PartnerVoltAbsorb_75PercentHP:
    IfRandomLessThan 64, ScorePlus3
    GoTo TagStrategy_CheckElectricAbsorption_End

TagStrategy_PartnerVoltAbsorb_50PercentHP:
    IfRandomLessThan 128, ScorePlus3
    GoTo TagStrategy_CheckElectricAbsorption_End

TagStrategy_PartnerVoltAbsorb_LessThan50PercentHP:
    IfRandomLessThan 192, ScorePlus3
    GoTo TagStrategy_CheckElectricAbsorption_End

TagStrategy_CheckElectricAbsorption_End:
    PopOrEnd 

TagStrategy_CheckPartnerWaterAbsorption:
    // If our partner has Water Absorb or Dry Skin:
    //  - If our partner is at 100% HP, score -10
    //  - If our partner's HP >90%, no score change
    //  - If our partner's HP >75%, 25% chance of score +3, 75% chance of no change
    //  - If our partner's HP >50%, 50% chance of score +3, 50% chance of no change
    //  - Else, 75% chance of score +3, 25% chance of no change
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_WATER_ABSORB
    IfLoadedEqualTo AI_HAVE, TagStrategy_PartnerWaterAbsorb
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_DRY_SKIN
    IfLoadedEqualTo AI_HAVE, TagStrategy_PartnerWaterAbsorb
    GoTo TagStrategy_ScoreMinus30

TagStrategy_PartnerWaterAbsorb:
    IfHPPercentEqualTo AI_BATTLER_ATTACKER_PARTNER, 100, ScoreMinus10
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER_PARTNER, 90, TagStrategy_CheckWaterAbsorption_End
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER_PARTNER, 75, TagStrategy_PartnerWaterAbsorb_75PercentHP
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER_PARTNER, 50, TagStrategy_PartnerWaterAbsorb_50PercentHP
    GoTo TagStrategy_PartnerWaterAbsorb_LessThan50PercentHP

TagStrategy_PartnerWaterAbsorb_75PercentHP:
    IfRandomLessThan 64, ScorePlus3
    GoTo TagStrategy_CheckWaterAbsorption_End

TagStrategy_PartnerWaterAbsorb_50PercentHP:
    IfRandomLessThan 128, ScorePlus3
    GoTo TagStrategy_CheckWaterAbsorption_End

TagStrategy_PartnerWaterAbsorb_LessThan50PercentHP:
    IfRandomLessThan 192, ScorePlus3
    GoTo TagStrategy_CheckWaterAbsorption_End

TagStrategy_CheckWaterAbsorption_End:
    PopOrEnd 

TagStrategy_PartnerStatusMove:
    IfMoveEqualTo MOVE_SKILL_SWAP, TagStrategy_PartnerSkillSwap
    IfMoveEqualTo MOVE_WILL_O_WISP, TagStrategy_PartnerWillOWisp
    IfMoveEqualTo MOVE_THUNDER_WAVE, TagStrategy_PartnerThunderWave
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STATUS_BADLY_POISON, TagStrategy_PartnerPoisonStatus
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_STATUS_POISON, TagStrategy_PartnerPoisonStatus
    IfMoveEqualTo MOVE_HELPING_HAND, TagStrategy_PartnerUsingHelpingHand
    IfMoveEqualTo MOVE_SWAGGER, TagStrategy_PartnerSwagger
    IfMoveEqualTo MOVE_TRICK, TagStrategy_PartnerTrick
    IfMoveEqualTo MOVE_GASTRO_ACID, TagStrategy_PartnerGastroAcid
    GoTo TagStrategy_PartnerScoreMinus30

TagStrategy_PartnerSkillSwap:
    // If our partner has Truant or Slow Start, score +10.
    //
    // If we can give Levitate to an Electric-type partner, score +1; additional +1 if our partner
    // is mono-Electric.
    //
    // If we can give an Accuracy-increasing ability and our partner has an inaccurate move, score +3.
    //
    // Otherwise, score -30.
    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_TRUANT, ScorePlus10
    IfLoadedEqualTo ABILITY_SLOW_START, ScorePlus10

    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedNotEqualTo ABILITY_LEVITATE, TagStrategy_PartnerSkillSwap_GiveAccuracyIncrease

    LoadBattlerAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_LEVITATE, TagStrategy_PartnerScoreMinus30

    LoadTypeFrom LOAD_DEFENDER_TYPE_1
    IfLoadedNotEqualTo TYPE_ELECTRIC, TagStrategy_PartnerSkillSwap_GiveAccuracyIncrease
    AddToMoveScore 1

    LoadTypeFrom LOAD_DEFENDER_TYPE_2
    IfLoadedNotEqualTo TYPE_ELECTRIC, TagStrategy_PartnerSkillSwap_GiveAccuracyIncrease
    AddToMoveScore 1

    PopOrEnd 

TagStrategy_PartnerSkillSwap_GiveAccuracyIncrease:
    LoadBattlerAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_COMPOUND_EYES, TagStrategy_PartnerSkillSwap_PartnerHasInaccurateMove
    IfLoadedEqualTo ABILITY_NO_GUARD, TagStrategy_PartnerSkillSwap_PartnerHasInaccurateMove
    GoTo TagStrategy_PartnerScoreMinus30

TagStrategy_PartnerSkillSwap_PartnerHasInaccurateMove:
    IfMoveKnown AI_BATTLER_ATTACKER_PARTNER, MOVE_FIRE_BLAST, TagStrategy_PartnerSkillSwap_ScorePlus3
    IfMoveKnown AI_BATTLER_ATTACKER_PARTNER, MOVE_THUNDER, TagStrategy_PartnerSkillSwap_ScorePlus3
    IfMoveKnown AI_BATTLER_ATTACKER_PARTNER, MOVE_CROSS_CHOP, TagStrategy_PartnerSkillSwap_ScorePlus3
    IfMoveKnown AI_BATTLER_ATTACKER_PARTNER, MOVE_HYDRO_PUMP, TagStrategy_PartnerSkillSwap_ScorePlus3
    IfMoveKnown AI_BATTLER_ATTACKER_PARTNER, MOVE_DYNAMIC_PUNCH, TagStrategy_PartnerSkillSwap_ScorePlus3
    IfMoveKnown AI_BATTLER_ATTACKER_PARTNER, MOVE_BLIZZARD, TagStrategy_PartnerSkillSwap_ScorePlus3
    IfMoveKnown AI_BATTLER_ATTACKER_PARTNER, MOVE_ZAP_CANNON, TagStrategy_PartnerSkillSwap_ScorePlus3
    IfMoveKnown AI_BATTLER_ATTACKER_PARTNER, MOVE_MEGAHORN, TagStrategy_PartnerSkillSwap_ScorePlus3
    IfMoveKnown AI_BATTLER_ATTACKER_PARTNER, MOVE_FOCUS_BLAST, TagStrategy_PartnerSkillSwap_ScorePlus3
    IfMoveKnown AI_BATTLER_ATTACKER_PARTNER, MOVE_GUNK_SHOT, TagStrategy_PartnerSkillSwap_ScorePlus3
    IfMoveKnown AI_BATTLER_ATTACKER_PARTNER, MOVE_MAGMA_STORM, TagStrategy_PartnerSkillSwap_ScorePlus3
    IfMoveKnown AI_BATTLER_ATTACKER_PARTNER, MOVE_POWER_WHIP, TagStrategy_PartnerSkillSwap_ScorePlus3
    IfMoveKnown AI_BATTLER_ATTACKER_PARTNER, MOVE_SEED_FLARE, TagStrategy_PartnerSkillSwap_ScorePlus3
    IfMoveKnown AI_BATTLER_ATTACKER_PARTNER, MOVE_HEAD_SMASH, TagStrategy_PartnerSkillSwap_ScorePlus3
    GoTo TagStrategy_PartnerScoreMinus30

TagStrategy_PartnerSkillSwap_ScorePlus3:
    GoTo ScorePlus3

TagStrategy_PartnerWillOWisp:
    // If our partner has Flash Fire, handle it identically to the earlier Fire Absorption routine
    //
    // If our partner meets all of the following conditions, score +5:
    //  - Has the Guts ability
    //  - Is not currently statused
    //  - Does not have a Fire typing
    //  - Is not holding a Flame Orb or Toxic Orb
    //  - Is at 81% HP or greater
    //
    // Otherwise, score -30
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_FLASH_FIRE
    IfLoadedEqualTo AI_HAVE, TagStrategy_CheckPartnerFireAbsorption

    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_GUTS
    IfLoadedNotEqualTo AI_HAVE, TagStrategy_PartnerScoreMinus30

    IfStatus AI_BATTLER_ATTACKER_PARTNER, MON_CONDITION_ANY, TagStrategy_PartnerScoreMinus30

    LoadTypeFrom LOAD_DEFENDER_TYPE_1
    IfLoadedEqualTo TYPE_FIRE, TagStrategy_PartnerScoreMinus30
    LoadTypeFrom LOAD_DEFENDER_TYPE_2
    IfLoadedEqualTo TYPE_FIRE, TagStrategy_PartnerScoreMinus30

    IfHeldItemEqualTo AI_BATTLER_ATTACKER_PARTNER, ITEM_FLAME_ORB, TagStrategy_PartnerScoreMinus30
    IfHeldItemEqualTo AI_BATTLER_ATTACKER_PARTNER, ITEM_TOXIC_ORB, TagStrategy_PartnerScoreMinus30

    IfHPPercentLessThan AI_BATTLER_ATTACKER_PARTNER, 81, TagStrategy_PartnerScoreMinus30

    GoTo ScorePlus5

TagStrategy_PartnerThunderWave:
    // If our partner has a Ground typing or has an ability other than Motor Drive or Volt Absorb, score -30
    //
    // Otherwise, handle the move identically to other Electric moves
    LoadTypeFrom LOAD_DEFENDER_TYPE_1
    IfLoadedEqualTo TYPE_GROUND, TagStrategy_PartnerScoreMinus30
    LoadTypeFrom LOAD_DEFENDER_TYPE_2
    IfLoadedEqualTo TYPE_GROUND, TagStrategy_PartnerScoreMinus30

    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_MOTOR_DRIVE
    IfLoadedEqualTo AI_HAVE, TagStrategy_CheckPartnerElectricAbsorption

    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_VOLT_ABSORB
    IfLoadedEqualTo AI_HAVE, TagStrategy_CheckPartnerElectricAbsorption

    GoTo TagStrategy_PartnerScoreMinus30

TagStrategy_PartnerPoisonStatus:
    // If our partner meets all of the following conditions, score +5:
    //  - Has the Poison Heal ability
    //  - Is not currently statused
    //  - Is not holding a Toxic Orb
    //  - Is at 81% HP or greater
    //
    // Otherwise, score -30
    //
    // BUG: This routine should also consider if the partner has a Poison or Steel typing.
    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_POISON_HEAL
    IfLoadedNotEqualTo AI_HAVE, TagStrategy_PartnerScoreMinus30

    IfStatus AI_BATTLER_DEFENDER, MON_CONDITION_ANY, TagStrategy_PartnerScoreMinus30

    IfHeldItemEqualTo AI_BATTLER_ATTACKER_PARTNER, ITEM_TOXIC_ORB, TagStrategy_PartnerScoreMinus30

    IfHPPercentGreaterThan AI_BATTLER_ATTACKER_PARTNER, 91, TagStrategy_PartnerScoreMinus30

    GoTo ScorePlus5

TagStrategy_PartnerUsingHelpingHand:
    // If we do not have a partner, score -30
    //
    // If our partner has more than 50% HP or would move first in the turn, 75% chance of score +2,
    // 25% chance of score -1
    //
    // Else, no score changes
    IfHPPercentEqualTo AI_BATTLER_ATTACKER_PARTNER, 0, ScoreMinus30
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER_PARTNER, 50, TagStrategy_PartnerUsingHelpingHand_TryScorePlus2
    LoadBattlerSpeedRank AI_BATTLER_ATTACKER_PARTNER
    IfLoadedLessThan 1, TagStrategy_PartnerUsingHelpingHand_TryScorePlus2
    GoTo TagStrategy_PartnerUsingHelpingHand_End

TagStrategy_PartnerUsingHelpingHand_TryScorePlus2:
    IfRandomLessThan 64, ScoreMinus1
    AddToMoveScore 2

TagStrategy_PartnerUsingHelpingHand_End:
    PopOrEnd 

TagStrategy_PartnerSwagger:
    // If our partner is holding neither a Persim Berry nor a Lum Berry, score -30
    //
    // If our partner is at less than +2 Attack, score +3
    //
    // Otherwise, no score changes
    //
    // Curiously, this does not consider if our partner's ability is Own Tempo.
    IfHeldItemEqualTo AI_BATTLER_DEFENDER, ITEM_PERSIM_BERRY, TagStrategy_PartnerSwagger_TryScorePlus3
    IfHeldItemEqualTo AI_BATTLER_DEFENDER, ITEM_LUM_BERRY, TagStrategy_PartnerSwagger_TryScorePlus3
    GoTo TagStrategy_PartnerScoreMinus30

TagStrategy_PartnerSwagger_TryScorePlus3:
    IfStatStageGreaterThan AI_BATTLER_DEFENDER, BATTLE_STAT_ATTACK, 7, TagStrategy_PartnerSwagger_End
    AddToMoveScore 3

TagStrategy_PartnerSwagger_End:
    PopOrEnd 

TagStrategy_PartnerTrick:
    PopOrEnd 

TagStrategy_PartnerGastroAcid:
    // If our partner's ability is already suppressed, score -30
    //
    // If our partner has Truant or Slow Start, score +5
    //
    // Otherwise, no score changes
    IfMoveEffect AI_BATTLER_ATTACKER_PARTNER, MOVE_EFFECT_ABILITY_SUPPRESSED, TagStrategy_PartnerScoreMinus30

    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_TRUANT
    IfLoadedEqualTo AI_HAVE, TagStrategy_PartnerGastroAcid_ScorePlus5

    CheckBattlerAbility AI_BATTLER_ATTACKER_PARTNER, ABILITY_SLOW_START
    IfLoadedEqualTo AI_HAVE, TagStrategy_PartnerGastroAcid_ScorePlus5

    GoTo TagStrategy_PartnerGastroAcid_End

TagStrategy_PartnerGastroAcid_ScorePlus5:
    AddToMoveScore 5

TagStrategy_PartnerGastroAcid_End:
    PopOrEnd 

TagStrategy_PartnerScoreMinus30:
    AddToMoveScore -30
    PopOrEnd 

CheckHP_Main:
    IfTargetIsPartner TagStrategy_Partner

    // Which moves apply to the routine depends on the attacker's HP percentage
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER, 70, CheckHP_GT70Percent // >70%
    IfHPPercentGreaterThan AI_BATTLER_ATTACKER, 30, CheckHP_31To70Percent // 31-70%
    LoadCurrentMoveEffect 
    IfLoadedInTable CheckHP_DiscourageAtLowHP, CheckHP_TryScoreMinus2 // 1-30%
    GoTo CheckHP_Target

CheckHP_GT70Percent:
    LoadCurrentMoveEffect 
    IfLoadedInTable CheckHP_DiscourageAtHighHP, CheckHP_TryScoreMinus2
    GoTo CheckHP_Target

CheckHP_31To70Percent:
    LoadCurrentMoveEffect 
    IfLoadedInTable CheckHP_DiscourageAtMediumHP, CheckHP_TryScoreMinus2
    GoTo CheckHP_Target

CheckHP_TryScoreMinus2:
    // ~80.5% of the time, score -2
    IfRandomLessThan 50, CheckHP_Target
    AddToMoveScore -2

CheckHP_Target:
    // The second round is similar to the first, but looks at the target's HP instead of
    // the attacker's.
    IfHPPercentGreaterThan AI_BATTLER_DEFENDER, 70, CheckHP_Target_GT70Percent
    IfHPPercentGreaterThan AI_BATTLER_DEFENDER, 30, CheckHP_Target_31To70Percent
    LoadCurrentMoveEffect 
    IfLoadedInTable CheckHP_Target_DiscourageAtLowHP, CheckHP_Target_TryScoreMinus2
    GoTo CheckHP_Terminate

CheckHP_Target_GT70Percent:
    LoadCurrentMoveEffect 
    IfLoadedInTable CheckHP_Target_DiscourageAtHighHP, CheckHP_Target_TryScoreMinus2
    GoTo CheckHP_Terminate

CheckHP_Target_31To70Percent:
    LoadCurrentMoveEffect 
    IfLoadedInTable CheckHP_Target_DiscourageAtMediumHP, CheckHP_Target_TryScoreMinus2
    GoTo CheckHP_Terminate

CheckHP_Target_TryScoreMinus2:
    // ~80.5% of the time, score -2
    IfRandomLessThan 50, CheckHP_Terminate
    AddToMoveScore -2

CheckHP_Terminate:
    PopOrEnd 

CheckHP_DiscourageAtHighHP:
    TableEntry BATTLE_EFFECT_HALVE_DEFENSE
    TableEntry BATTLE_EFFECT_HALVE_SP_DEFENSE
    TableEntry BATTLE_EFFECT_RESTORE_HALF_HP
    TableEntry BATTLE_EFFECT_HEAL_ALLIES_QUARTER
    TableEntry BATTLE_EFFECT_REST
    TableEntry BATTLE_EFFECT_KO_MON_THAT_DEFEATED_USER
    TableEntry BATTLE_EFFECT_INCREASE_POWER_WITH_LESS_HP
    TableEntry BATTLE_EFFECT_SURVIVE_WITH_1_HP
    TableEntry BATTLE_EFFECT_HEAL_HALF_MORE_IN_SUN
    TableEntry BATTLE_EFFECT_FAINT_AND_ATK_SP_ATK_DOWN_2
    TableEntry BATTLE_EFFECT_HEAL_HALF_REMOVE_FLYING_TYPE
    TableEntry BATTLE_EFFECT_FAINT_FULL_RESTORE_NEXT_MON
    TableEntry TABLE_END

CheckHP_DiscourageAtMediumHP:
    TableEntry BATTLE_EFFECT_HALVE_DEFENSE
    TableEntry BATTLE_EFFECT_HALVE_SP_DEFENSE
    TableEntry BATTLE_EFFECT_ATK_UP
    TableEntry BATTLE_EFFECT_DEF_UP
    TableEntry BATTLE_EFFECT_SPEED_UP
    TableEntry BATTLE_EFFECT_SP_ATK_UP
    TableEntry BATTLE_EFFECT_SP_DEF_UP
    TableEntry BATTLE_EFFECT_ACC_UP
    TableEntry BATTLE_EFFECT_EVA_UP
    TableEntry BATTLE_EFFECT_ATK_DOWN
    TableEntry BATTLE_EFFECT_SWITCH_LOWER_ATKS
    TableEntry BATTLE_EFFECT_DEF_DOWN
    TableEntry BATTLE_EFFECT_SPEED_DOWN
    TableEntry BATTLE_EFFECT_SP_ATK_DOWN
    TableEntry BATTLE_EFFECT_SP_DEF_DOWN
    TableEntry BATTLE_EFFECT_ACC_DOWN
    TableEntry BATTLE_EFFECT_EVA_DOWN
    TableEntry BATTLE_EFFECT_BIDE
    TableEntry BATTLE_EFFECT_CONVERSION
    TableEntry BATTLE_EFFECT_SET_LIGHT_SCREEN
    TableEntry BATTLE_EFFECT_AURORA_VEIL
    TableEntry BATTLE_EFFECT_PREVENT_STAT_REDUCTION
    TableEntry BATTLE_EFFECT_CRIT_UP_2
    TableEntry BATTLE_EFFECT_ATK_UP_2
    TableEntry BATTLE_EFFECT_DEF_UP_2
    TableEntry BATTLE_EFFECT_SPEED_UP_2
    TableEntry BATTLE_EFFECT_SP_ATK_UP_2
    TableEntry BATTLE_EFFECT_SP_DEF_UP_2
    TableEntry BATTLE_EFFECT_ACC_UP_2
    TableEntry BATTLE_EFFECT_EVA_UP_2
    TableEntry BATTLE_EFFECT_ATK_DOWN_2
    TableEntry BATTLE_EFFECT_DEF_DOWN_2
    TableEntry BATTLE_EFFECT_SPEED_DOWN_2
    TableEntry BATTLE_EFFECT_SP_ATK_DOWN_2
    TableEntry BATTLE_EFFECT_SP_DEF_DOWN_2
    TableEntry BATTLE_EFFECT_EVA_DOWN_2
    TableEntry BATTLE_EFFECT_ACC_DOWN_2
    TableEntry BATTLE_EFFECT_PREVENT_STATUS
    TableEntry BATTLE_EFFECT_MAX_ATK_LOSE_HALF_MAX_HP
    TableEntry BATTLE_EFFECT_ATK_DEF_DOWN
    TableEntry BATTLE_EFFECT_DEF_SPD_UP
    TableEntry BATTLE_EFFECT_ATK_DEF_UP
    TableEntry BATTLE_EFFECT_SP_ATK_SP_DEF_UP
    TableEntry BATTLE_EFFECT_ATK_SPD_UP
    TableEntry BATTLE_EFFECT_QUIVER_DANCE
    TableEntry BATTLE_EFFECT_SP_ATK_DOWN_2_OPPOSITE_GENDER
    TableEntry TABLE_END

CheckHP_DiscourageAtLowHP:
    TableEntry BATTLE_EFFECT_ATK_UP
    TableEntry BATTLE_EFFECT_DEF_UP
    TableEntry BATTLE_EFFECT_SPEED_UP
    TableEntry BATTLE_EFFECT_SP_ATK_UP
    TableEntry BATTLE_EFFECT_SP_DEF_UP
    TableEntry BATTLE_EFFECT_ACC_UP
    TableEntry BATTLE_EFFECT_EVA_UP
    TableEntry BATTLE_EFFECT_ATK_DOWN
    TableEntry BATTLE_EFFECT_SWITCH_LOWER_ATKS
    TableEntry BATTLE_EFFECT_DEF_DOWN
    TableEntry BATTLE_EFFECT_SPEED_DOWN
    TableEntry BATTLE_EFFECT_SP_ATK_DOWN
    TableEntry BATTLE_EFFECT_SP_DEF_DOWN
    TableEntry BATTLE_EFFECT_ACC_DOWN
    TableEntry BATTLE_EFFECT_EVA_DOWN
    TableEntry BATTLE_EFFECT_BIDE
    TableEntry BATTLE_EFFECT_CONVERSION
    TableEntry BATTLE_EFFECT_SET_LIGHT_SCREEN
    TableEntry BATTLE_EFFECT_AURORA_VEIL
    TableEntry BATTLE_EFFECT_PREVENT_STAT_REDUCTION
    TableEntry BATTLE_EFFECT_CRIT_UP_2
    TableEntry BATTLE_EFFECT_ATK_UP_2
    TableEntry BATTLE_EFFECT_DEF_UP_2
    TableEntry BATTLE_EFFECT_SPEED_UP_2
    TableEntry BATTLE_EFFECT_SP_ATK_UP_2
    TableEntry BATTLE_EFFECT_SP_DEF_UP_2
    TableEntry BATTLE_EFFECT_ACC_UP_2
    TableEntry BATTLE_EFFECT_EVA_UP_2
    TableEntry BATTLE_EFFECT_ATK_DOWN_2
    TableEntry BATTLE_EFFECT_DEF_DOWN_2
    TableEntry BATTLE_EFFECT_SPEED_DOWN_2
    TableEntry BATTLE_EFFECT_SP_ATK_DOWN_2
    TableEntry BATTLE_EFFECT_SP_DEF_DOWN_2
    TableEntry BATTLE_EFFECT_EVA_DOWN_2
    TableEntry BATTLE_EFFECT_ACC_DOWN_2
    TableEntry BATTLE_EFFECT_POWDER
    TableEntry BATTLE_EFFECT_NEXT_ATTACK_ALWAYS_HITS
    TableEntry BATTLE_EFFECT_PREVENT_STATUS
    TableEntry BATTLE_EFFECT_MAX_ATK_LOSE_HALF_MAX_HP
    TableEntry BATTLE_EFFECT_COPY_STAT_CHANGES
    TableEntry BATTLE_EFFECT_MIRROR_COAT
    TableEntry BATTLE_EFFECT_DECREASE_POWER_WITH_LESS_USER_HP
    TableEntry BATTLE_EFFECT_ATK_DEF_DOWN
    TableEntry BATTLE_EFFECT_DEF_SPD_UP
    TableEntry BATTLE_EFFECT_ATK_DEF_UP
    TableEntry BATTLE_EFFECT_SP_ATK_SP_DEF_UP
    TableEntry BATTLE_EFFECT_ATK_SPD_UP
    TableEntry BATTLE_EFFECT_QUIVER_DANCE
    TableEntry BATTLE_EFFECT_CHARGE_TURN_SP_ATK_UP
    TableEntry BATTLE_EFFECT_METAL_BURST
    TableEntry BATTLE_EFFECT_SP_ATK_DOWN_2_OPPOSITE_GENDER
    TableEntry TABLE_END

CheckHP_Target_DiscourageAtHighHP:
    TableEntry TABLE_END

CheckHP_Target_DiscourageAtMediumHP:
    TableEntry BATTLE_EFFECT_ATK_UP
    TableEntry BATTLE_EFFECT_DEF_UP
    TableEntry BATTLE_EFFECT_SPEED_UP
    TableEntry BATTLE_EFFECT_SP_ATK_UP
    TableEntry BATTLE_EFFECT_SP_DEF_UP
    TableEntry BATTLE_EFFECT_ACC_UP
    TableEntry BATTLE_EFFECT_EVA_UP
    TableEntry BATTLE_EFFECT_ATK_DOWN
    TableEntry BATTLE_EFFECT_SWITCH_LOWER_ATKS
    TableEntry BATTLE_EFFECT_DEF_DOWN
    TableEntry BATTLE_EFFECT_SPEED_DOWN
    TableEntry BATTLE_EFFECT_SP_ATK_DOWN
    TableEntry BATTLE_EFFECT_SP_DEF_DOWN
    TableEntry BATTLE_EFFECT_ACC_DOWN
    TableEntry BATTLE_EFFECT_EVA_DOWN
    TableEntry BATTLE_EFFECT_PREVENT_STAT_REDUCTION
    TableEntry BATTLE_EFFECT_CRIT_UP_2
    TableEntry BATTLE_EFFECT_ATK_UP_2
    TableEntry BATTLE_EFFECT_DEF_UP_2
    TableEntry BATTLE_EFFECT_SPEED_UP_2
    TableEntry BATTLE_EFFECT_SP_ATK_UP_2
    TableEntry BATTLE_EFFECT_SP_DEF_UP_2
    TableEntry BATTLE_EFFECT_ACC_UP_2
    TableEntry BATTLE_EFFECT_EVA_UP_2
    TableEntry BATTLE_EFFECT_ATK_DOWN_2
    TableEntry BATTLE_EFFECT_DEF_DOWN_2
    TableEntry BATTLE_EFFECT_SPEED_DOWN_2
    TableEntry BATTLE_EFFECT_SP_ATK_DOWN_2
    TableEntry BATTLE_EFFECT_SP_DEF_DOWN_2
    TableEntry BATTLE_EFFECT_EVA_DOWN_2
    TableEntry BATTLE_EFFECT_ACC_DOWN_2
    TableEntry BATTLE_EFFECT_STATUS_POISON
    TableEntry BATTLE_EFFECT_AVERAGE_HP
    TableEntry BATTLE_EFFECT_ALL_FAINT_3_TURNS
    TableEntry BATTLE_EFFECT_PREVENT_STATUS
    TableEntry BATTLE_EFFECT_ATK_DEF_DOWN
    TableEntry BATTLE_EFFECT_DEF_SPD_UP
    TableEntry BATTLE_EFFECT_ATK_DEF_UP
    TableEntry BATTLE_EFFECT_SP_ATK_SP_DEF_UP
    TableEntry BATTLE_EFFECT_ATK_SPD_UP
    TableEntry BATTLE_EFFECT_QUIVER_DANCE
    TableEntry BATTLE_EFFECT_STEEL_BEAM
    TableEntry BATTLE_EFFECT_SP_ATK_DOWN_2_OPPOSITE_GENDER
    TableEntry TABLE_END

CheckHP_Target_DiscourageAtLowHP:
    TableEntry BATTLE_EFFECT_STATUS_SLEEP
    TableEntry BATTLE_EFFECT_HALVE_DEFENSE // done
    TableEntry BATTLE_EFFECT_HALVE_SP_DEFENSE
    TableEntry BATTLE_EFFECT_ATK_UP
    TableEntry BATTLE_EFFECT_DEF_UP
    TableEntry BATTLE_EFFECT_SPEED_UP
    TableEntry BATTLE_EFFECT_SP_ATK_UP
    TableEntry BATTLE_EFFECT_SP_DEF_UP
    TableEntry BATTLE_EFFECT_ACC_UP
    TableEntry BATTLE_EFFECT_EVA_UP
    TableEntry BATTLE_EFFECT_ATK_DOWN
    TableEntry BATTLE_EFFECT_SWITCH_LOWER_ATKS
    TableEntry BATTLE_EFFECT_DEF_DOWN
    TableEntry BATTLE_EFFECT_SPEED_DOWN
    TableEntry BATTLE_EFFECT_SP_ATK_DOWN
    TableEntry BATTLE_EFFECT_SP_DEF_DOWN
    TableEntry BATTLE_EFFECT_ACC_DOWN
    TableEntry BATTLE_EFFECT_EVA_DOWN
    TableEntry BATTLE_EFFECT_BIDE
    TableEntry BATTLE_EFFECT_CONVERSION
    TableEntry BATTLE_EFFECT_STATUS_BADLY_POISON
    TableEntry BATTLE_EFFECT_SET_LIGHT_SCREEN
    TableEntry BATTLE_EFFECT_AURORA_VEIL
    TableEntry BATTLE_EFFECT_ONE_HIT_KO
    TableEntry BATTLE_EFFECT_HALVE_HP
    TableEntry BATTLE_EFFECT_HALVE_HP
    TableEntry BATTLE_EFFECT_PREVENT_STAT_REDUCTION
    TableEntry BATTLE_EFFECT_CRIT_UP_2
    TableEntry BATTLE_EFFECT_STATUS_CONFUSE
    TableEntry BATTLE_EFFECT_ATK_UP_2
    TableEntry BATTLE_EFFECT_DEF_UP_2
    TableEntry BATTLE_EFFECT_SPEED_UP_2
    TableEntry BATTLE_EFFECT_SP_ATK_UP_2
    TableEntry BATTLE_EFFECT_SP_DEF_UP_2
    TableEntry BATTLE_EFFECT_ACC_UP_2
    TableEntry BATTLE_EFFECT_EVA_UP_2
    TableEntry BATTLE_EFFECT_ATK_DOWN_2
    TableEntry BATTLE_EFFECT_DEF_DOWN_2
    TableEntry BATTLE_EFFECT_SPEED_DOWN_2
    TableEntry BATTLE_EFFECT_SP_ATK_DOWN_2
    TableEntry BATTLE_EFFECT_SP_DEF_DOWN_2
    TableEntry BATTLE_EFFECT_EVA_DOWN_2
    TableEntry BATTLE_EFFECT_ACC_DOWN_2
    TableEntry BATTLE_EFFECT_STATUS_POISON
    TableEntry BATTLE_EFFECT_STATUS_PARALYZE
    TableEntry BATTLE_EFFECT_AVERAGE_HP
    TableEntry BATTLE_EFFECT_NEXT_ATTACK_ALWAYS_HITS
    TableEntry BATTLE_EFFECT_DECREASE_LAST_MOVE_PP
    TableEntry BATTLE_EFFECT_ALL_FAINT_3_TURNS
    TableEntry BATTLE_EFFECT_ATK_UP_2_STATUS_CONFUSION
    TableEntry BATTLE_EFFECT_DOUBLE_POWER_EACH_TURN
    TableEntry BATTLE_EFFECT_INFATUATE
    TableEntry BATTLE_EFFECT_PREVENT_STATUS
    TableEntry BATTLE_EFFECT_COPY_STAT_CHANGES
    TableEntry BATTLE_EFFECT_MIRROR_COAT
    TableEntry BATTLE_EFFECT_STATUS_BURN
    TableEntry BATTLE_EFFECT_ATK_DEF_DOWN
    TableEntry BATTLE_EFFECT_DEF_SPD_UP
    TableEntry BATTLE_EFFECT_ATK_DEF_UP
    TableEntry BATTLE_EFFECT_SP_ATK_SP_DEF_UP
    TableEntry BATTLE_EFFECT_ATK_SPD_UP
    TableEntry BATTLE_EFFECT_QUIVER_DANCE
    TableEntry BATTLE_EFFECT_STEEL_BEAM
    TableEntry BATTLE_EFFECT_SP_ATK_DOWN_2_OPPOSITE_GENDER
    TableEntry TABLE_END

Weather_Main:
    IfTargetIsPartner Terminate

    // If it is not the first turn of the battle, break.
    LoadTurnCount 
    IfLoadedNotEqualTo 0, Weather_Terminate

    // For each weather, don't try to set it if it's already active from the field.
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_WEATHER_SUN, Weather_Sun
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_WEATHER_RAIN, Weather_Rain
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_WEATHER_SANDSTORM, Weather_Sand
    IfCurrentMoveEffectEqualTo BATTLE_EFFECT_WEATHER_HAIL, Weather_Hail

Weather_Sun:
    LoadCurrentWeather 
    IfLoadedEqualTo AI_WEATHER_SUNNY, Weather_Terminate
    GoTo Weather_ScorePlus5

Weather_Rain:
    LoadCurrentWeather 
    IfLoadedEqualTo AI_WEATHER_RAINING, Weather_Terminate
    GoTo Weather_ScorePlus5

Weather_Sand:
    LoadCurrentWeather 
    IfLoadedEqualTo AI_WEATHER_SANDSTORM, Weather_Terminate
    GoTo Weather_ScorePlus5

Weather_Hail:
    LoadCurrentWeather 
    IfLoadedEqualTo AI_WEATHER_HAILING, Weather_Terminate
    GoTo Weather_ScorePlus5

Weather_ScorePlus5:
    // On the attacker's first turn only, score +5.
    LoadIsFirstTurnInBattle AI_BATTLER_ATTACKER
    IfLoadedEqualTo FALSE, Weather_Terminate
    AddToMoveScore 5

Weather_Terminate:
    PopOrEnd 

Harrassment_Main:
    IfTargetIsPartner Terminate

    // If the move is not judged to be a Harrassment move within the context
    // of this routine, break.
    LoadCurrentMoveEffect 
    IfLoadedNotInTable Harrassment_Effects, Harrassment_Terminate

    // 50% of the time, score +2.
    IfRandomLessThan 128, Harrassment_Terminate
    AddToMoveScore 2

Harrassment_Terminate:
    PopOrEnd 

Harrassment_Effects:
    TableEntry BATTLE_EFFECT_STATUS_SLEEP
    TableEntry BATTLE_EFFECT_ATK_DOWN
    TableEntry BATTLE_EFFECT_SWITCH_LOWER_ATKS
    TableEntry BATTLE_EFFECT_DEF_DOWN
    TableEntry BATTLE_EFFECT_ACC_DOWN
    TableEntry BATTLE_EFFECT_EVA_DOWN
    TableEntry BATTLE_EFFECT_STATUS_CONFUSE
    TableEntry BATTLE_EFFECT_ATK_DOWN_2
    TableEntry BATTLE_EFFECT_DEF_DOWN_2
    TableEntry BATTLE_EFFECT_SPEED_DOWN_2
    TableEntry BATTLE_EFFECT_SP_DEF_DOWN_2
    TableEntry BATTLE_EFFECT_STATUS_POISON
    TableEntry BATTLE_EFFECT_STATUS_PARALYZE
    TableEntry BATTLE_EFFECT_STATUS_LEECH_SEED
    TableEntry BATTLE_EFFECT_ENCORE
    TableEntry BATTLE_EFFECT_DECREASE_LAST_MOVE_PP
    TableEntry BATTLE_EFFECT_SET_SPIKES
    TableEntry BATTLE_EFFECT_ATK_UP_2_STATUS_CONFUSION
    TableEntry BATTLE_EFFECT_INFATUATE
    TableEntry BATTLE_EFFECT_TORMENT
    TableEntry BATTLE_EFFECT_SP_ATK_UP_CAUSE_CONFUSION
    TableEntry BATTLE_EFFECT_STATUS_BURN
    TableEntry BATTLE_EFFECT_NATURE_POWER
    TableEntry BATTLE_EFFECT_STATUS_SLEEP_NEXT_TURN
    TableEntry BATTLE_EFFECT_REMOVE_HELD_ITEM
    TableEntry BATTLE_EFFECT_SECRET_POWER
    TableEntry BATTLE_EFFECT_CONFUSE_ALL
    TableEntry BATTLE_EFFECT_ATK_DEF_DOWN
    TableEntry BATTLE_EFFECT_PREVENT_ITEM_USE
    TableEntry BATTLE_EFFECT_TRANSFER_STATUS
    TableEntry BATTLE_EFFECT_TOXIC_SPIKES
    TableEntry BATTLE_EFFECT_REMOVE_HAZARDS_SCREENS_EVA_DOWN
    TableEntry BATTLE_EFFECT_SP_ATK_DOWN_2_OPPOSITE_GENDER
    TableEntry TABLE_END

RoamingPokemon_Main:
    // If the Roamer is trapped, break from this routine
    // Otherwise, override all other possible moves and Escape
    IfVolatileStatus AI_BATTLER_ATTACKER, VOLATILE_CONDITION_BIND, RoamingPokemon_Trapped
    IfVolatileStatus AI_BATTLER_ATTACKER, VOLATILE_CONDITION_MEAN_LOOK, RoamingPokemon_Trapped
    LoadAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_SHADOW_TAG, RoamingPokemon_Trapped
    LoadAbility AI_BATTLER_ATTACKER
    IfLoadedEqualTo ABILITY_LEVITATE, RoamingPokemon_NotTrapped
    LoadAbility AI_BATTLER_DEFENDER
    IfLoadedEqualTo ABILITY_ARENA_TRAP, RoamingPokemon_Trapped

RoamingPokemon_NotTrapped:
    Escape 

RoamingPokemon_Trapped:
    PopOrEnd 

Safari_Main:
    Dummy3E 1
    Dummy3F 
    Escape 

CatchTutorial_Main:
    // If the target is at 20% or less HP, flee from the battle
    IfHPPercentEqualTo AI_BATTLER_DEFENDER, 20, CatchTutorial_Escape
    IfHPPercentLessThan AI_BATTLER_DEFENDER, 20, CatchTutorial_Escape
    PopOrEnd 

CatchTutorial_Escape:
    Escape 

Terminate:
    PopOrEnd 

    .endif
