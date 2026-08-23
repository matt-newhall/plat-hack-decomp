#include "constants/battle/trainer_ai.h"

#include <nitro.h>
#include <string.h>

#include "constants/battle.h"
#include "constants/battle/battle_script.h"
#include "constants/items.h"
#include "constants/species.h"
#include "generated/abilities.h"

#include "struct_decls/battle_system.h"
#include "struct_defs/battle_system.h"

#include "battle/ai_context.h"
#include "battle/battle_context.h"
#include "battle/battle_controller_player.h"
#include "battle/battle_lib.h"
#include "battle/battle_system.h"
#include "battle/common.h"
#include "battle/trainer_ai.h"
#include "pch/global_pch.h"

#include "assert.h"
#include "flags.h"
#include "party.h"
#include "pokemon.h"

#define AI_CONTEXT (battleCtx->aiContext)

// Moves with an effect ID in either of these tables do not use the standard damage-calculation during scoring.
static const u16 sNoDamageCalcMoveEffects[] = {
    BATTLE_EFFECT_HALVE_DEFENSE,
    BATTLE_EFFECT_HALVE_SP_DEFENSE,
    0xFFFF
};

static const u16 sAltPowerMoveEffects[] = {
    BATTLE_EFFECT_POWER_BASED_ON_LOW_SPEED,
    BATTLE_EFFECT_NATURAL_GIFT,
    BATTLE_EFFECT_JUDGEMENT,
    BATTLE_EFFECT_40_DAMAGE_FLAT,
    BATTLE_EFFECT_LEVEL_DAMAGE_FLAT,
    BATTLE_EFFECT_RANDOM_DAMAGE_1_TO_150_LEVEL,
    BATTLE_EFFECT_POWER_BASED_ON_FRIENDSHIP,
    BATTLE_EFFECT_POWER_BASED_ON_LOW_FRIENDSHIP,
    BATTLE_EFFECT_20_DAMAGE_FLAT,
    BATTLE_EFFECT_INCREASE_POWER_WITH_WEIGHT,
    BATTLE_EFFECT_HEAVY_SLAM,
    BATTLE_EFFECT_PSYWAVE, // Magnitude; Psywave itself uses RANDOM_DAMAGE_1_TO_150_LEVEL
    BATTLE_EFFECT_INCREASE_POWER_WITH_MORE_STAT_UP,
    BATTLE_EFFECT_SPIT_UP,
    BATTLE_EFFECT_HIGHER_POWER_WHEN_LOW_PP,
    BATTLE_EFFECT_INCREASE_POWER_WITH_LESS_HP,
    BATTLE_EFFECT_HALVE_HP,
    0xFFFF
};

// Moves whose damage this turn is too unreliable to compete for the "best damaging move"
// bonus: they either spend a turn charging, escalate over several turns, or cost the user
// their own Pokemon. They are also skipped when deciding which *other* move is the best, so
// that an excluded move cannot rob a legitimate pick of the bonus.
static const u16 sExcludedFromBestDamageMoveEffects[] = {
    BATTLE_EFFECT_HALVE_DEFENSE, // Explosion
    BATTLE_EFFECT_HALVE_SP_DEFENSE, // Self-Destruct, Misty Explosion
    BATTLE_EFFECT_DOUBLE_POWER_EACH_TURN_LOCK_INTO, // Rollout, Ice Ball
    BATTLE_EFFECT_BIND_HIT, // Wrap, Fire Spin, Clamp, Infestation, Sand Tomb, Magma Storm

    // Charge moves which leave the user exposed for the turn they spend charging. The
    // semi-invulnerable charge moves (Fly, Dig, Dive, Bounce, Shadow Force) are deliberately
    // absent, as dodging for that turn is not the same liability. Solar Beam and Solar Blade
    // are absent as they resolve in a single turn under sun.
    BATTLE_EFFECT_CHARGE_TURN_HIGH_CRIT,
    BATTLE_EFFECT_CHARGE_TURN_HIGH_CRIT_FLINCH, // Sky Attack
    BATTLE_EFFECT_CHARGE_TURN_DEF_UP, // Skull Bash
    BATTLE_EFFECT_CHARGE_TURN_SP_ATK_UP, // Meteor Beam
    0xFFFF
};

// Of the above, the moves which should not be treated as able to secure a KO either. The
// remainder (trapping moves and Meteor Beam) still earn the kill bonuses.
static const u16 sNoKillCheckMoveEffects[] = {
    BATTLE_EFFECT_HALVE_DEFENSE,
    BATTLE_EFFECT_HALVE_SP_DEFENSE,
    BATTLE_EFFECT_DOUBLE_POWER_EACH_TURN_LOCK_INTO,
    0xFFFF
};

typedef void (*AICommandFunc)(BattleSystem *, BattleContext *);

enum AIEvalStep {
    AI_EVAL_STEP_INIT,
    AI_EVAL_STEP_EVAL,
    AI_EVAL_STEP_END,
};

static void AICmd_IfRandomLessThan(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfRandomGreaterThan(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfRandomEqualTo(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfRandomNotEqualTo(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_AddToMoveScore(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfHPPercentLessThan(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfHPPercentGreaterThan(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfHPPercentEqualTo(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfHPPercentNotEqualTo(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfStatus(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfNotStatus(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfVolatileStatus(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfNotVolatileStatus(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfMoveEffect(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfNotMoveEffect(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfSideCondition(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfNotSideCondition(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfLoadedLessThan(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfLoadedGreaterThan(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfLoadedEqualTo(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfLoadedNotEqualTo(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfLoadedMask(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfLoadedNotMask(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfMoveEqualTo(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfMoveNotEqualTo(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfLoadedInTable(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfLoadedNotInTable(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfAttackerHasDamagingMoves(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfAttackerHasNoDamagingMoves(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadTurnCount(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadTypeFrom(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadMovePower(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_FlagMoveDamageScore(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadBattlerPreviousMove(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfTempEqualTo(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfTempNotEqualTo(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfSpeedCompareEqualTo(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfSpeedCompareNotEqualTo(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_CountAlivePartyBattlers(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadCurrentMove(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadCurrentMoveEffect(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadBattlerAbility(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_CalcMaxEffectiveness(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfMoveEffectivenessEquals(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfPartyMemberStatus(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfPartyMemberNotStatus(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadCurrentWeather(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfCurrentMoveEffectEqualTo(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfCurrentMoveEffectNotEqualTo(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfStatStageLessThan(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfStatStageGreaterThan(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfStatStageEqualTo(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfStatStageNotEqualTo(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfCurrentMoveKills(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfCurrentMoveDoesNotKill(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfMoveKnown(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfMoveNotKnown(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfMoveEffectKnown(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfMoveEffectNotKnown(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfBattlerUnderEffect(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfCurrentMoveMatchesEffect(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_Escape(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_Dummy3E(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_Dummy3F(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadHeldItem(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadHeldItemEffect(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadGender(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadIsFirstTurnInBattle(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadStockpileCount(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadBattleType(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadRecycleItem(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadTypeOfLoadedMove(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadPowerOfLoadedMove(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadEffectOfLoadedMove(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadProtectChain(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_PushAndGoTo(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_GoTo(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_PopOrEnd(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfLevel(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfTargetIsTaunted(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfTargetIsNotTaunted(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfTargetIsPartner(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_FlagBattlerIsType(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_CheckBattlerAbility(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfActivatedFlashFire(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfHeldItemEqualTo(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfFieldConditionsMask(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadSpikesLayers(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfAnyPartyMemberIsWounded(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfAnyPartyMemberUsedPP(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadFlingPower(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadCurrentMovePP(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfCanUseLastResort(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadCurrentMoveClass(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadDefenderLastUsedMoveClass(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadBattlerSpeedRank(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadBattlerTurnCount(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfPartyMemberDealsMoreDamage(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfHasSuperEffectiveMove(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfBattlerDealsMoreDamage(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_SumPositiveStatStages(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_DiffStatStages(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfBattlerHasHigherStat(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfBattlerHasLowerStat(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfBattlerHasEqualStat(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_CheckIfHighestDamageWithPartner(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfBattlerFainted(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfBattlerNotFainted(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_LoadAbility(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfLockOnTarget(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfCurrentMoveIsSound(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfCurrentMoveIsWind(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_FlagBestDamageMove(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfCurrentMoveHasPriority(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfDefenderCanKO(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfDefenderCanKOInHits(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfDefenderCannotKOInHits(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfDefenderCanKOAfterShellSmash(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfDefenderCanKOAfterBellyDrum(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfBattlerIncapacitated(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfBattlerHasDamagingMoveOfClass(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfBattlersShareMove(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfAnyOpponentOutspeedsSide(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfParalysisFlipsSpeed(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfAttackerCanKO(BattleSystem *battleSys, BattleContext *battleCtx);
static void AICmd_IfResidualDamageKOsAttacker(BattleSystem *battleSys, BattleContext *battleCtx);

static u8 TrainerAI_MainSingles(BattleSystem *battleSys, BattleContext *battleCtx);
static u8 TrainerAI_MainDoubles(BattleSystem *battleSys, BattleContext *battleCtx);
static void TrainerAI_EvalMoves(BattleSystem *battleSys, BattleContext *battleCtx);
static void TrainerAI_RecordLastMove(BattleSystem *battleSys, BattleContext *battleCtx);
static void AIScript_PushCursor(BattleSystem *battleSys, BattleContext *battleCtx, int address);
static BOOL AIScript_PopCursor(BattleSystem *battleSys, BattleContext *battleCtx);
static int AIScript_Read(BattleContext *battleCtx);
static int AIScript_ReadOffset(BattleContext *battleCtx, int ofs);
static void AIScript_Iter(BattleContext *battleCtx, int i);
static u8 AIScript_Battler(BattleContext *battleCtx, u8 inBattler);
static s32 TrainerAI_CalcAllDamage(BattleSystem *battleSys, BattleContext *battleCtx, int attacker, u16 *moves, s32 *damageVals, u16 heldItem, u8 *ivs, int ability, BOOL embargo, BOOL varyDamage);
static s32 TrainerAI_CalcDamage(BattleSystem *battleSys, BattleContext *battleCtx, u16 move, u16 heldItem, u8 *ivs, int attacker, int ability, BOOL embargo, u8 variance);
static int TrainerAI_MoveType(BattleSystem *battleSys, BattleContext *battleCtx, int battler, int move);
static int TrainerAI_SumRaisedStatStages(BattleContext *battleCtx, int battler, int firstStat);
static BOOL AI_MoveEffectInTable(BattleContext *battleCtx, const u16 *effects, u16 move);
static BOOL AI_MoveHasDamageEstimate(BattleContext *battleCtx, u16 move);
static int TrainerAI_HitCountMultiplier(BattleSystem *battleSys, BattleContext *battleCtx, u16 move, int attacker, int ability, u16 heldItem);
static void TrainerAI_GetStats(BattleContext *battleCtx, int battler, int *buf1, int *buf2, int stat);

static BOOL AI_PerishSongKO(BattleContext *battleCtx, int battler);
static BOOL AI_CannotDamageWonderGuard(BattleSystem *battleSys, BattleContext *battleCtx, int battler);
static BOOL AI_PartyMonThreatensSlot(BattleSystem *battleSys, BattleContext *battleCtx, Pokemon *mon, int defender, BOOL wantSuperEffective);
static BOOL AI_OnlyIneffectiveMoves(BattleSystem *battleSys, BattleContext *battleCtx, int battler);
static BOOL AI_HasSuperEffectiveMove(BattleSystem *battleSys, BattleContext *battleCtx, int battler, BOOL alwaysSwitch);
static BOOL AI_HasAbsorbAbilityInParty(BattleSystem *battleSys, BattleContext *battleCtx, int battler);
static BOOL AI_HasPartyMemberWithSuperEffectiveMove(BattleSystem *battleSys, BattleContext *battleCtx, int battler, u32 checkEffectiveness, u8 rand);
static BOOL AI_IsAsleepWithNaturalCure(BattleSystem *battleSys, BattleContext *battleCtx, int battler);
static BOOL TrainerAI_ShouldSwitch(BattleSystem *battleSys, BattleContext *battleCtx, int battler);
static BOOL TrainerAI_ShouldUseItem(BattleSystem *battleSys, int battler);

static const AICommandFunc sAICommandTable[] = {
#include "data/scripts/aicmd.h"
};

void TrainerAI_Init(BattleSystem *battleSys, BattleContext *battleCtx, u8 battler, u8 initScore)
{
    // must declare these up here to match
    int i;
    u8 invalidMoves;

    // explicit memset
    u8 *adrs = (u8 *)&AI_CONTEXT;
    for (i = 0; i < XtOffset(AIContext *, battlerMoves); i++) {
        adrs[i] = 0;
    }

    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        if (initScore & 1) {
            AI_CONTEXT.moveScore[i] = 100;
        } else {
            AI_CONTEXT.moveScore[i] = 0;
        }

        initScore = initScore >> 1;
    }

    // pick damage rolls for moves and score invalid moves to 0
    invalidMoves = BattleSystem_CheckInvalidMoves(battleSys, battleCtx, battler, 0, CHECK_INVALID_ALL);
    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        if (invalidMoves & FlagIndex(i)) {
            AI_CONTEXT.moveScore[i] = 0;
        }

        AI_CONTEXT.moveDamageRolls[i] = 100 - (BattleSystem_RandNext(battleSys) % 16);
    }

    AI_CONTEXT.scriptStackSize = 0;

    // roaming Pokemon have special AI; otherwise, copy the AI behavior from the trainer data
    if (battleSys->battleType & BATTLE_TYPE_ROAMER) {
        AI_CONTEXT.thinkingMask = AI_FLAG_ROAMING_POKEMON;
    } else {
        AI_CONTEXT.thinkingMask = battleSys->trainers[battler].header.aiMask;
    }

    // force double-battle strategies, if applicable
    if (battleSys->battleType & BATTLE_TYPE_DOUBLES) {
        AI_CONTEXT.thinkingMask |= AI_FLAG_TAG_STRATEGY;
    }
}

u8 TrainerAI_Main(BattleSystem *battleSys, u8 battler)
{
    u8 result;
    BattleContext *battleCtx = battleSys->battleCtx;

    if ((AI_CONTEXT.stateFlags & AI_STATUS_FLAG_CONTINUE) == FALSE) {
        AI_CONTEXT.attacker = battler;
        AI_CONTEXT.defender = BattleSystem_RandomOpponent(battleSys, battleCtx, battler);

        TrainerAI_Init(battleSys, battleCtx, AI_CONTEXT.attacker, AI_INIT_SCORE_ALL_MOVES);
    }

    if ((battleSys->battleType & BATTLE_TYPE_DOUBLES) == FALSE) {
        result = TrainerAI_MainSingles(battleSys, battleCtx);
    } else {
        result = TrainerAI_MainDoubles(battleSys, battleCtx);
    }

    return result;
}

/**
 * @brief Main action-choice routine for single battles.
 *
 * @param battleSys
 * @param battleCtx
 * @return The action that the AI picked for its turn. See enum AIActionChoice.
 */
static u8 TrainerAI_MainSingles(BattleSystem *battleSys, BattleContext *battleCtx)
{
    int i;
    u8 maxScoreMoves[4];
    u8 maxScoreMoveSlots[4];
    u8 numMaxScoreMoves;
    u8 action = AI_ENEMY_ATTACK_1;
    u16 move;

    TrainerAI_RecordLastMove(battleSys, battleCtx);

    while (AI_CONTEXT.thinkingMask) {
        if (AI_CONTEXT.thinkingMask & AI_FLAG_BASIC) {
            if ((AI_CONTEXT.stateFlags & AI_STATUS_FLAG_CONTINUE) == FALSE) {
                AI_CONTEXT.evalStep = AI_EVAL_STEP_INIT;
            }

            TrainerAI_EvalMoves(battleSys, battleCtx);
        }

        AI_CONTEXT.thinkingMask = AI_CONTEXT.thinkingMask >> 1;
        AI_CONTEXT.thinkingBitShift++;
        AI_CONTEXT.moveSlot = 0;
    }

    if (AI_CONTEXT.stateFlags & AI_STATUS_FLAG_ESCAPE) {
        action = AI_ENEMY_ESCAPE;
    } else if (AI_CONTEXT.stateFlags & AI_STATUS_FLAG_SAFARI) {
        action = AI_ENEMY_SAFARI;
    } else {
        // Get the move with the highest score; break ties randomly
        numMaxScoreMoves = 1;
        maxScoreMoves[0] = AI_CONTEXT.moveScore[0];
        maxScoreMoveSlots[0] = AI_ENEMY_ATTACK_1;

        for (i = 1; i < LEARNED_MOVES_MAX; i++) {
            if (battleCtx->battleMons[AI_CONTEXT.attacker].moves[i]) { // Attacker has a move in this slot
                // Append to the list of max-score moves if equal score to the current max
                if (maxScoreMoves[0] == AI_CONTEXT.moveScore[i]) {
                    maxScoreMoves[numMaxScoreMoves] = AI_CONTEXT.moveScore[i];
                    maxScoreMoveSlots[numMaxScoreMoves++] = i;
                }

                // Set to be the maximum score if higher score than the current max
                if (maxScoreMoves[0] < AI_CONTEXT.moveScore[i]) {
                    numMaxScoreMoves = 1;
                    maxScoreMoves[0] = AI_CONTEXT.moveScore[i];
                    maxScoreMoveSlots[0] = i;
                }
            }
        }

        action = maxScoreMoveSlots[BattleSystem_RandNext(battleSys) % numMaxScoreMoves];
    }

    AI_CONTEXT.selectedTarget[AI_CONTEXT.attacker] = AI_CONTEXT.defender;
    return action;
}

/**
 * @brief Main action-choice routine for double battles.
 *
 * @param battleSys
 * @param battleCtx
 * @return The action that the AI picked for its turn. See enum AIActionChoice.
 */
static u8 TrainerAI_MainDoubles(BattleSystem *battleSys, BattleContext *battleCtx)
{
    int battler, battlerCount, thinkingMask;
    s16 maxScoreForBattler[MAX_BATTLERS];
    u8 battlerTemp[MAX_BATTLERS];
    s8 actionForBattler[MAX_BATTLERS];
    s16 maxScore;
    u16 move;
    s8 moveSlot;

    for (battler = 0; battler < MAX_BATTLERS; battler++) {
        if (battler == AI_CONTEXT.attacker || battleCtx->battleMons[battler].curHP == 0) {
            actionForBattler[battler] = -1;
            maxScoreForBattler[battler] = -1;
            continue;
        }

        TrainerAI_Init(battleSys, battleCtx, AI_CONTEXT.attacker, 0xf);

        // Record the last moves of enemy battlers
        AI_CONTEXT.defender = battler;
        if ((battler & 1) != (AI_CONTEXT.attacker & 1)) {
            TrainerAI_RecordLastMove(battleSys, battleCtx);
        }

        AI_CONTEXT.thinkingBitShift = 0;
        AI_CONTEXT.moveSlot = 0;
        thinkingMask = AI_CONTEXT.thinkingMask;

        // Evaluate moves according with the current battler as the target
        while (thinkingMask) {
            if (thinkingMask & AI_FLAG_BASIC) {
                if ((AI_CONTEXT.stateFlags & AI_STATUS_FLAG_CONTINUE) == FALSE) {
                    AI_CONTEXT.evalStep = AI_EVAL_STEP_INIT;
                }

                TrainerAI_EvalMoves(battleSys, battleCtx);
            }

            thinkingMask >>= 1;
            AI_CONTEXT.thinkingBitShift++;
            AI_CONTEXT.moveSlot = 0;
        }

        if (AI_CONTEXT.stateFlags & AI_STATUS_FLAG_ESCAPE) {
            actionForBattler[battler] = AI_ENEMY_ESCAPE;
        } else if (AI_CONTEXT.stateFlags & AI_STATUS_FLAG_SAFARI) {
            actionForBattler[battler] = AI_ENEMY_SAFARI;
        } else {
            u8 tmpMaxScores[4];
            u8 tmpMaxScoreMoveSlots[4];
            int numMaxScoreMoves, i;

            // Pick a random move from among the highest-scored moves on this target
            tmpMaxScores[0] = AI_CONTEXT.moveScore[0];
            tmpMaxScoreMoveSlots[0] = 0;
            numMaxScoreMoves = 1;

            for (i = 1; i < LEARNED_MOVES_MAX; i++) {
                if (battleCtx->battleMons[AI_CONTEXT.attacker].moves[i]) {
                    // Same score as max: append to list of possible max-score moves
                    if (tmpMaxScores[0] == AI_CONTEXT.moveScore[i]) {
                        tmpMaxScores[numMaxScoreMoves] = AI_CONTEXT.moveScore[i];
                        tmpMaxScoreMoveSlots[numMaxScoreMoves] = i;
                        numMaxScoreMoves++;
                    }

                    // Higher score than max: set as new max score
                    if (tmpMaxScores[0] < AI_CONTEXT.moveScore[i]) {
                        tmpMaxScores[0] = AI_CONTEXT.moveScore[i];
                        tmpMaxScoreMoveSlots[0] = i;
                        numMaxScoreMoves = 1;
                    }
                }
            }

            actionForBattler[battler] = tmpMaxScoreMoveSlots[BattleSystem_RandNext(battleSys) % numMaxScoreMoves];
            maxScoreForBattler[battler] = tmpMaxScores[0];

            // Score moves on an ally below 100 to -1 (basically, never use them)
            if (battler == (AI_CONTEXT.attacker ^ 2)) {
                if (maxScoreForBattler[battler] < 100) {
                    maxScoreForBattler[battler] = -1;
                }
            }
        }
    }

    // Get the highest overall score among all the possible targets
    maxScore = maxScoreForBattler[0];
    battlerTemp[0] = 0;
    battlerCount = 1;
    for (battler = 1; battler < MAX_BATTLERS; battler++) {
        if (maxScore == maxScoreForBattler[battler]) {
            battlerTemp[battlerCount++] = battler;
        }

        if (maxScore < maxScoreForBattler[battler]) {
            maxScore = maxScoreForBattler[battler];
            battlerTemp[0] = battler;
            battlerCount = 1;
        }
    }

    // Pick a random target from among the maximum-scored targets
    AI_CONTEXT.selectedTarget[AI_CONTEXT.attacker] = battlerTemp[(BattleSystem_RandNext(battleSys) % battlerCount)];
    moveSlot = actionForBattler[AI_CONTEXT.selectedTarget[AI_CONTEXT.attacker]];
    move = battleCtx->battleMons[AI_CONTEXT.attacker].moves[moveSlot];

    // Override targets as needed
    if (AI_CONTEXT.moveTable[move].range == RANGE_USER_OR_ALLY
        && BattleSystem_GetBattlerSide(battleSys, AI_CONTEXT.selectedTarget[AI_CONTEXT.attacker]) == 0) {
        AI_CONTEXT.selectedTarget[AI_CONTEXT.attacker] = AI_CONTEXT.attacker;
    }

    if (move == MOVE_CURSE && Move_IsGhostCurse(battleCtx, move, AI_CONTEXT.attacker) == FALSE) {
        AI_CONTEXT.selectedTarget[AI_CONTEXT.attacker] = AI_CONTEXT.attacker;
    }

    return moveSlot;
}

/**
 * @brief Evaluation loop for scoring each move available to the AI.
 *
 * This does NOT score the potential choices of using an item or switching
 * a Pokemon for turn.
 *
 * @param battleSys
 * @param battleCtx
 */
static void TrainerAI_EvalMoves(BattleSystem *battleSys, BattleContext *battleCtx)
{
    while (AI_CONTEXT.evalStep != AI_EVAL_STEP_END) {
        switch (AI_CONTEXT.evalStep) {
        case AI_EVAL_STEP_INIT:
            battleCtx->aiScriptCursor = battleCtx->aiScriptTemp[AI_CONTEXT.thinkingBitShift];

            if (battleCtx->battleMons[AI_CONTEXT.attacker].ppCur[AI_CONTEXT.moveSlot] == 0) {
                AI_CONTEXT.move = MOVE_NONE;
            } else {
                AI_CONTEXT.move = battleCtx->battleMons[AI_CONTEXT.attacker].moves[AI_CONTEXT.moveSlot];
            }

            AI_CONTEXT.evalStep++;
            break;

        case AI_EVAL_STEP_EVAL:
            if (AI_CONTEXT.move != MOVE_NONE) {
                sAICommandTable[battleCtx->aiScriptTemp[battleCtx->aiScriptCursor]](battleSys, battleCtx);
            } else {
                AI_CONTEXT.moveScore[AI_CONTEXT.moveSlot] = 0;
                AI_CONTEXT.stateFlags |= AI_STATUS_FLAG_DONE;
            }

            if (AI_CONTEXT.stateFlags & AI_STATUS_FLAG_DONE) {
                // If we haven't gone through all the moves, loop back to INIT state and evaluate the next move
                AI_CONTEXT.moveSlot++;
                if (AI_CONTEXT.moveSlot < LEARNED_MOVES_MAX
                    && (AI_CONTEXT.stateFlags & AI_STATUS_FLAG_BREAK) == FALSE) {
                    AI_CONTEXT.evalStep = AI_EVAL_STEP_INIT;
                } else {
                    AI_CONTEXT.evalStep++;
                }

                AI_CONTEXT.stateFlags &= AI_STATUS_FLAG_DONE_OFF;
            }

            break;

        case AI_EVAL_STEP_END:
            break;
        }
    }
}

static void AICmd_IfRandomLessThan(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int val = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    if ((BattleSystem_RandNext(battleSys) % 256) < val) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfRandomGreaterThan(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int val = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    if ((BattleSystem_RandNext(battleSys) % 256) > val) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfRandomEqualTo(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int val = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    if ((BattleSystem_RandNext(battleSys) % 256) == val) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfRandomNotEqualTo(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int val = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    if ((BattleSystem_RandNext(battleSys) % 256) != val) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_AddToMoveScore(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int val = AIScript_Read(battleCtx);
    int score = AI_CONTEXT.moveScore[AI_CONTEXT.moveSlot] + val;

    // Clamping
    if (score < 0) {
        score = 0;
    } else if (score > 127) {
        score = 127;
    }

    AI_CONTEXT.moveScore[AI_CONTEXT.moveSlot] = score;
}

static void AICmd_IfHPPercentLessThan(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int targetPercent = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);
    u32 hpPercent = battleCtx->battleMons[battler].curHP * 100 / battleCtx->battleMons[battler].maxHP;

    if (hpPercent < targetPercent) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfHPPercentGreaterThan(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int targetPercent = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);
    u32 hpPercent = battleCtx->battleMons[battler].curHP * 100 / battleCtx->battleMons[battler].maxHP;

    if (hpPercent > targetPercent) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfHPPercentEqualTo(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int targetPercent = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);
    u32 hpPercent = battleCtx->battleMons[battler].curHP * 100 / battleCtx->battleMons[battler].maxHP;

    if (hpPercent == targetPercent) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfHPPercentNotEqualTo(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int targetPercent = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);
    u32 hpPercent = battleCtx->battleMons[battler].curHP * 100 / battleCtx->battleMons[battler].maxHP;

    if (hpPercent != targetPercent) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfStatus(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    u32 mask = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    if (battleCtx->battleMons[battler].status & mask) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfNotStatus(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    u32 mask = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    if ((battleCtx->battleMons[battler].status & mask) == FALSE) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfVolatileStatus(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    u32 mask = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    if (battleCtx->battleMons[battler].statusVolatile & mask) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfNotVolatileStatus(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    u32 mask = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    if ((battleCtx->battleMons[battler].statusVolatile & mask) == FALSE) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfMoveEffect(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    u32 mask = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    if (battleCtx->battleMons[battler].moveEffectsMask & mask) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfNotMoveEffect(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    u32 mask = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    if ((battleCtx->battleMons[battler].moveEffectsMask & mask) == FALSE) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfSideCondition(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    u32 mask = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);
    u8 side = BattleSystem_GetBattlerSide(battleSys, battler);

    if (battleCtx->sideConditionsMask[side] & mask) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfNotSideCondition(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    u32 mask = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);
    u8 side = BattleSystem_GetBattlerSide(battleSys, battler);

    if ((battleCtx->sideConditionsMask[side] & mask) == FALSE) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfLoadedLessThan(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int val = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    if (AI_CONTEXT.calcTemp < val) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfLoadedGreaterThan(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int val = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    if (AI_CONTEXT.calcTemp > val) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfLoadedEqualTo(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int val = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    if (AI_CONTEXT.calcTemp == val) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfLoadedNotEqualTo(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int val = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    if (AI_CONTEXT.calcTemp != val) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfLoadedMask(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int mask = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    if (AI_CONTEXT.calcTemp & mask) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfLoadedNotMask(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int mask = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    if ((AI_CONTEXT.calcTemp & mask) == FALSE) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfMoveEqualTo(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int val = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    if (AI_CONTEXT.move == val) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfMoveNotEqualTo(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int val = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    if (AI_CONTEXT.move != val) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfLoadedInTable(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int ofs = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    int val;

    while ((val = AIScript_ReadOffset(battleCtx, ofs)) != 0xFFFFFFFF) {
        if (AI_CONTEXT.calcTemp == val) {
            AIScript_Iter(battleCtx, jump);
            break;
        }

        ofs++;
    }
}

static void AICmd_IfLoadedNotInTable(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int ofs = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    int val;

    while ((val = AIScript_ReadOffset(battleCtx, ofs)) != 0xFFFFFFFF) {
        if (AI_CONTEXT.calcTemp == val) {
            return;
        }

        ofs++;
    }

    AIScript_Iter(battleCtx, jump);
}

static void AICmd_IfAttackerHasDamagingMoves(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    int jump = AIScript_Read(battleCtx);

    int i;
    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        if (battleCtx->battleMons[AI_CONTEXT.attacker].moves[i] != MOVE_NONE
            && MOVE_DATA(battleCtx->battleMons[AI_CONTEXT.attacker].moves[i]).power) {
            break;
        }
    }

    if (i < LEARNED_MOVES_MAX) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfAttackerHasNoDamagingMoves(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    int jump = AIScript_Read(battleCtx);

    int i;
    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        if (battleCtx->battleMons[AI_CONTEXT.attacker].moves[i] != MOVE_NONE
            && MOVE_DATA(battleCtx->battleMons[AI_CONTEXT.attacker].moves[i]).power) {
            break;
        }
    }

    if (i == LEARNED_MOVES_MAX) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_LoadTurnCount(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    AI_CONTEXT.calcTemp = battleCtx->totalTurns;
}

static void AICmd_LoadTypeFrom(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int param = AIScript_Read(battleCtx);
    int partner;

    switch (param) {
    case LOAD_ATTACKER_TYPE_1:
        AI_CONTEXT.calcTemp = BattleMon_Get(battleCtx, AI_CONTEXT.attacker, BATTLEMON_TYPE_1, NULL);
        break;

    case LOAD_DEFENDER_TYPE_1:
        AI_CONTEXT.calcTemp = BattleMon_Get(battleCtx, AI_CONTEXT.defender, BATTLEMON_TYPE_1, NULL);
        break;

    case LOAD_ATTACKER_TYPE_2:
        AI_CONTEXT.calcTemp = BattleMon_Get(battleCtx, AI_CONTEXT.attacker, BATTLEMON_TYPE_2, NULL);
        break;

    case LOAD_DEFENDER_TYPE_2:
        AI_CONTEXT.calcTemp = BattleMon_Get(battleCtx, AI_CONTEXT.defender, BATTLEMON_TYPE_2, NULL);
        break;

    case LOAD_MOVE_TYPE:
        AI_CONTEXT.calcTemp = MOVE_DATA(AI_CONTEXT.move).type;
        break;

    case LOAD_ATTACKER_PARTNER_TYPE_1:
        partner = BattleSystem_GetPartner(battleSys, AI_CONTEXT.attacker);
        AI_CONTEXT.calcTemp = BattleMon_Get(battleCtx, partner, BATTLEMON_TYPE_1, NULL);
        break;

    case LOAD_DEFENDER_PARTNER_TYPE_1:
        partner = BattleSystem_GetPartner(battleSys, AI_CONTEXT.defender);
        AI_CONTEXT.calcTemp = BattleMon_Get(battleCtx, partner, BATTLEMON_TYPE_1, NULL);
        break;

    case LOAD_ATTACKER_PARTNER_TYPE_2:
        partner = BattleSystem_GetPartner(battleSys, AI_CONTEXT.attacker);
        AI_CONTEXT.calcTemp = BattleMon_Get(battleCtx, partner, BATTLEMON_TYPE_2, NULL);
        break;

    case LOAD_DEFENDER_PARTNER_TYPE_2:
        partner = BattleSystem_GetPartner(battleSys, AI_CONTEXT.defender);
        AI_CONTEXT.calcTemp = BattleMon_Get(battleCtx, partner, BATTLEMON_TYPE_1, NULL);
        break;

    default:
        GF_ASSERT(FALSE);
        break;
    }
}

static void AICmd_FlagBattlerIsType(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int type = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    if (MON_HAS_TYPE(battler, type)) {
        AI_CONTEXT.calcTemp = TRUE;
    } else {
        AI_CONTEXT.calcTemp = FALSE;
    }
}

static void AICmd_LoadMovePower(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    AI_CONTEXT.calcTemp = MOVE_DATA(AI_CONTEXT.move).power;
}

static void AICmd_FlagMoveDamageScore(BattleSystem *battleSys, BattleContext *battleCtx)
{
    int i = 0, noCalcIdx, altPowerIdx;
    s32 moveDamage[LEARNED_MOVES_MAX];
    BOOL varyDamage;
    u8 ivs[STAT_MAX];

    AIScript_Iter(battleCtx, 1);

    varyDamage = AIScript_Read(battleCtx);

    for (noCalcIdx = 0; sNoDamageCalcMoveEffects[noCalcIdx] != 0xFFFF; noCalcIdx++) {
        if (MOVE_DATA(AI_CONTEXT.move).effect == sNoDamageCalcMoveEffects[noCalcIdx]) {
            break;
        }
    }

    for (altPowerIdx = 0; sAltPowerMoveEffects[altPowerIdx] != 0xFFFF; altPowerIdx++) {
        if (MOVE_DATA(AI_CONTEXT.move).effect == sAltPowerMoveEffects[altPowerIdx]) {
            break;
        }
    }

    if (sAltPowerMoveEffects[altPowerIdx] != 0xFFFF
        || (MOVE_DATA(AI_CONTEXT.move).power > 1 && sNoDamageCalcMoveEffects[noCalcIdx] == 0xFFFF)) {
        for (i = 0; i < STAT_MAX; i++) {
            ivs[i] = BattleMon_Get(battleCtx, AI_CONTEXT.attacker, BATTLEMON_HP_IV + i, NULL);
        }

        TrainerAI_CalcAllDamage(battleSys,
            battleCtx,
            AI_CONTEXT.attacker,
            battleCtx->battleMons[AI_CONTEXT.attacker].moves,
            moveDamage,
            battleCtx->battleMons[AI_CONTEXT.attacker].heldItem,
            ivs,
            Battler_Ability(battleCtx, AI_CONTEXT.attacker),
            battleCtx->battleMons[AI_CONTEXT.attacker].moveEffectsData.embargoTurns,
            varyDamage);

        for (i = 0; i < LEARNED_MOVES_MAX; i++) {
            if (moveDamage[i] > moveDamage[AI_CONTEXT.moveSlot]) {
                break;
            }
        }

        if (i == LEARNED_MOVES_MAX) {
            AI_CONTEXT.calcTemp = AI_MOVE_IS_HIGHEST_DAMAGE;
        } else {
            AI_CONTEXT.calcTemp = AI_NOT_HIGHEST_DAMAGE;
        }
    } else {
        AI_CONTEXT.calcTemp = AI_NO_COMPARISON_MADE;
    }
}

static void AICmd_LoadBattlerPreviousMove(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    AI_CONTEXT.calcTemp = battleCtx->movePrevByBattler[battler];
}

static void AICmd_IfTempEqualTo(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int val = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    if (val == AI_CONTEXT.calcTemp) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfTempNotEqualTo(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int val = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    if (val != AI_CONTEXT.calcTemp) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfSpeedCompareEqualTo(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int val = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    if (BattleSystem_CompareBattlerSpeed(battleSys, battleCtx, AI_CONTEXT.attacker, AI_CONTEXT.defender, TRUE) == val) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfSpeedCompareNotEqualTo(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int val = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    if (BattleSystem_CompareBattlerSpeed(battleSys, battleCtx, AI_CONTEXT.attacker, AI_CONTEXT.defender, TRUE) != val) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_CountAlivePartyBattlers(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);

    AI_CONTEXT.calcTemp = 0;

    u8 battler = AIScript_Battler(battleCtx, inBattler);
    Party *party = BattleSystem_GetParty(battleSys, battler);
    u8 battlerSlot, partnerSlot;

    if (battleSys->battleType & BATTLE_TYPE_DOUBLES) {
        battlerSlot = battleCtx->selectedPartySlot[battler];
        partnerSlot = battleCtx->selectedPartySlot[BattleSystem_GetPartner(battleSys, battler)];
    } else {
        battlerSlot = partnerSlot = battleCtx->selectedPartySlot[battler];
    }

    for (int i = 0; i < BattleSystem_GetPartyCount(battleSys, battler); i++) {
        Pokemon *mon = Party_GetPokemonBySlotIndex(party, i);

        if (i != battlerSlot
            && i != partnerSlot
            && Pokemon_GetValue(mon, MON_DATA_HP, NULL) != 0
            && Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_NONE
            && Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_EGG) {
            AI_CONTEXT.calcTemp++;
        }
    }
}

static void AICmd_LoadCurrentMove(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    AI_CONTEXT.calcTemp = AI_CONTEXT.move;
}

static void AICmd_LoadCurrentMoveEffect(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    AI_CONTEXT.calcTemp = MOVE_DATA(AI_CONTEXT.move).effect;
}

static void AICmd_LoadBattlerAbility(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    if (battleCtx->battleMons[battler].moveEffectsMask & MOVE_EFFECT_ABILITY_SUPPRESSED) {
        AI_CONTEXT.calcTemp = ABILITY_NONE;
    } else if (AI_CONTEXT.attacker != battler && inBattler != AI_BATTLER_ATTACKER_PARTNER) {
        // If we already know an opponent's ability, load that ability
        if (AI_CONTEXT.battlerAbilities[battler]) {
            AI_CONTEXT.calcTemp = AI_CONTEXT.battlerAbilities[battler];
        } else {
            // If the opponent has an ability that traps us, we should already know about it (because it self-announces)
            u8 knownAbility = Battler_Ability(battleCtx, battler);
            if (knownAbility == ABILITY_SHADOW_TAG
                || knownAbility == ABILITY_MAGNET_PULL
                || knownAbility == ABILITY_ARENA_TRAP) {
                AI_CONTEXT.calcTemp = knownAbility;
            } else {
                // Try to guess the opponent's ability (flip a coin)
                int ability1 = SpeciesData_GetSpeciesValue(battleCtx->battleMons[battler].species, SPECIES_DATA_ABILITY_1);
                int ability2 = SpeciesData_GetSpeciesValue(battleCtx->battleMons[battler].species, SPECIES_DATA_ABILITY_2);

                if (ability1 && ability2) {
                    if (BattleSystem_RandNext(battleSys) & 1) {
                        AI_CONTEXT.calcTemp = ability1;
                    } else {
                        AI_CONTEXT.calcTemp = ability2;
                    }
                } else if (ability1) {
                    AI_CONTEXT.calcTemp = ability1;
                } else {
                    AI_CONTEXT.calcTemp = ability2;
                }
            }
        }
    } else {
        AI_CONTEXT.calcTemp = Battler_Ability(battleCtx, battler);
    }
}

static void AICmd_CheckBattlerAbility(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int expected = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);
    int tmpAbility;

    if (battleCtx->battleMons[battler].moveEffectsMask & MOVE_EFFECT_ABILITY_SUPPRESSED) {
        tmpAbility = ABILITY_NONE;
    } else if (inBattler == AI_BATTLER_DEFENDER || inBattler == AI_BATTLER_DEFENDER_PARTNER) {
        // If we already know an opponent's ability, load that ability
        if (AI_CONTEXT.battlerAbilities[battler]) {
            tmpAbility = AI_CONTEXT.battlerAbilities[battler];
            AI_CONTEXT.calcTemp = AI_CONTEXT.battlerAbilities[battler];
        } else {
            // If the opponent has an ability that traps us, we should already know about it (because it self-announces)
            u8 knownAbility = Battler_Ability(battleCtx, battler);
            if (knownAbility == ABILITY_SHADOW_TAG
                || knownAbility == ABILITY_MAGNET_PULL
                || knownAbility == ABILITY_ARENA_TRAP) {
                tmpAbility = knownAbility;
            } else {
                // Try to guess the opponent's ability (flip a coin)
                int ability1 = SpeciesData_GetSpeciesValue(battleCtx->battleMons[battler].species, SPECIES_DATA_ABILITY_1);
                int ability2 = SpeciesData_GetSpeciesValue(battleCtx->battleMons[battler].species, SPECIES_DATA_ABILITY_2);

                if (ability1 && ability2) {
                    // If the opponent has two abilities, but neither are the expected one,
                    // prefer ability 1 for the final check
                    if (ability1 != expected && ability2 != expected) {
                        tmpAbility = ability1;
                        // Otherwise, pretend that we don't know about it
                    } else {
                        tmpAbility = ABILITY_NONE;
                    }
                } else if (ability1) {
                    tmpAbility = ability1;
                } else {
                    tmpAbility = ability2;
                }
            }
        }
    } else {
        tmpAbility = Battler_Ability(battleCtx, battler);
    }

    if (tmpAbility == ABILITY_NONE) {
        AI_CONTEXT.calcTemp = AI_UNKNOWN;
    } else if (tmpAbility == expected) {
        AI_CONTEXT.calcTemp = AI_HAVE;
    } else {
        AI_CONTEXT.calcTemp = AI_NOT_HAVE;
    }
}

static void AICmd_CalcMaxEffectiveness(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    AI_CONTEXT.calcTemp = TYPE_MULTI_IMMUNE;

    for (int i = 0; i < LEARNED_MOVES_MAX; i++) {
        u32 damage = TYPE_MULTI_BASE_DAMAGE;
        u32 effectiveness = 0;
        u16 move = battleCtx->battleMons[AI_CONTEXT.attacker].moves[i];
        int moveType = TrainerAI_MoveType(battleSys, battleCtx, AI_CONTEXT.attacker, move);

        if (move) {
            damage = BattleSystem_ApplyTypeChart(battleSys,
                battleCtx,
                move,
                moveType,
                AI_CONTEXT.attacker,
                AI_CONTEXT.defender,
                damage,
                &effectiveness);

            if (damage == TYPE_MULTI_STAB_DAMAGE * 2) {
                damage = TYPE_MULTI_DOUBLE_DAMAGE;
            } else if (damage == TYPE_MULTI_STAB_DAMAGE * 4) {
                damage = TYPE_MULTI_QUADRUPLE_DAMAGE;
            } else if (damage == TYPE_MULTI_STAB_DAMAGE / 2) {
                damage = TYPE_MULTI_HALF_DAMAGE;
            } else if (damage == TYPE_MULTI_STAB_DAMAGE / 4) {
                damage = TYPE_MULTI_QUARTER_DAMAGE;
            }

            if (effectiveness & MOVE_STATUS_IMMUNE) {
                damage = TYPE_MULTI_IMMUNE;
            }

            if (AI_CONTEXT.calcTemp < damage) {
                AI_CONTEXT.calcTemp = damage;
            }
        }
    }
}

static void AICmd_IfMoveEffectivenessEquals(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int expected = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u32 damage = TYPE_MULTI_BASE_DAMAGE;
    u32 effectiveness = 0;

    damage = BattleSystem_ApplyTypeChart(battleSys,
        battleCtx,
        AI_CONTEXT.move,
        TrainerAI_MoveType(battleSys, battleCtx, AI_CONTEXT.attacker, AI_CONTEXT.move),
        AI_CONTEXT.attacker,
        AI_CONTEXT.defender,
        damage,
        &effectiveness);

    if (damage == TYPE_MULTI_STAB_DAMAGE * 2) {
        damage = TYPE_MULTI_DOUBLE_DAMAGE;
    } else if (damage == TYPE_MULTI_STAB_DAMAGE * 4) {
        damage = TYPE_MULTI_QUADRUPLE_DAMAGE;
    } else if (damage == TYPE_MULTI_STAB_DAMAGE / 2) {
        damage = TYPE_MULTI_HALF_DAMAGE;
    } else if (damage == TYPE_MULTI_STAB_DAMAGE / 4) {
        damage = TYPE_MULTI_QUARTER_DAMAGE;
    }

    if (effectiveness & MOVE_STATUS_IMMUNE) {
        damage = TYPE_MULTI_IMMUNE;
    }

    if (damage == expected) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfPartyMemberStatus(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    Party *party; // this must be declared first to match
    int inBattler = AIScript_Read(battleCtx);
    u32 statusMask = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    u8 slot1, slot2;
    if (battleSys->battleType & BATTLE_TYPE_DOUBLES) {
        slot1 = battleCtx->selectedPartySlot[battler];
        slot2 = battleCtx->selectedPartySlot[BattleSystem_GetPartner(battleSys, battler)];
    } else {
        slot1 = slot2 = battleCtx->selectedPartySlot[battler];
    }

    party = BattleSystem_GetParty(battleSys, battler);
    for (int i = 0; i < BattleSystem_GetPartyCount(battleSys, battler); i++) {
        Pokemon *mon = Party_GetPokemonBySlotIndex(party, i);

        if (i != slot1 && i != slot2
            && Pokemon_GetValue(mon, MON_DATA_HP, NULL) != 0
            && Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_NONE
            && Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_EGG
            && (Pokemon_GetValue(mon, MON_DATA_STATUS, NULL) & statusMask)) {
            AIScript_Iter(battleCtx, jump);
            return;
        }
    }
}

static void AICmd_IfPartyMemberNotStatus(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    Party *party; // this must be declared first to match
    int inBattler = AIScript_Read(battleCtx);
    u32 statusMask = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    u8 slot1, slot2;
    if (battleSys->battleType & BATTLE_TYPE_DOUBLES) {
        slot1 = battleCtx->selectedPartySlot[battler];
        slot2 = battleCtx->selectedPartySlot[BattleSystem_GetPartner(battleSys, battler)];
    } else {
        slot1 = slot2 = battleCtx->selectedPartySlot[battler];
    }

    party = BattleSystem_GetParty(battleSys, battler);
    for (int i = 0; i < BattleSystem_GetPartyCount(battleSys, battler); i++) {
        Pokemon *mon = Party_GetPokemonBySlotIndex(party, i);

        if (i != slot1 && i != slot2
            && Pokemon_GetValue(mon, MON_DATA_HP, NULL) != 0
            && Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_NONE
            && Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_EGG
            && (Pokemon_GetValue(mon, MON_DATA_STATUS, NULL) & statusMask) == FALSE) {
            AIScript_Iter(battleCtx, jump);
            return;
        }
    }
}

static void AICmd_LoadCurrentWeather(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    AI_CONTEXT.calcTemp = AI_WEATHER_CLEAR;

    if (WEATHER_IS_RAIN) {
        AI_CONTEXT.calcTemp = AI_WEATHER_RAINING;
    }

    if (WEATHER_IS_SAND) {
        AI_CONTEXT.calcTemp = AI_WEATHER_SANDSTORM;
    }

    if (WEATHER_IS_SUN) {
        AI_CONTEXT.calcTemp = AI_WEATHER_SUNNY;
    }

    if (WEATHER_IS_HAIL) {
        AI_CONTEXT.calcTemp = AI_WEATHER_HAILING;
    }

    if (WEATHER_IS_FOG) {
        AI_CONTEXT.calcTemp = AI_WEATHER_DEEP_FOG;
    }
}

static void AICmd_IfCurrentMoveEffectEqualTo(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int expected = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    if (MOVE_DATA(AI_CONTEXT.move).effect == expected) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfCurrentMoveEffectNotEqualTo(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int expected = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    if (MOVE_DATA(AI_CONTEXT.move).effect != expected) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfStatStageLessThan(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int stat = AIScript_Read(battleCtx);
    int val = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    if (battleCtx->battleMons[battler].statBoosts[stat] < val) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfStatStageGreaterThan(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int stat = AIScript_Read(battleCtx);
    int val = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    if (battleCtx->battleMons[battler].statBoosts[stat] > val) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfStatStageEqualTo(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int stat = AIScript_Read(battleCtx);
    int val = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    if (battleCtx->battleMons[battler].statBoosts[stat] == val) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfStatStageNotEqualTo(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int stat = AIScript_Read(battleCtx);
    int val = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    if (battleCtx->battleMons[battler].statBoosts[stat] != val) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfCurrentMoveKills(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    BOOL useDamageRoll = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    if (AI_MoveEffectInTable(battleCtx, sNoKillCheckMoveEffects, AI_CONTEXT.move)) {
        return;
    }

    int roll;
    if (useDamageRoll == TRUE) {
        roll = AI_CONTEXT.moveDamageRolls[AI_CONTEXT.moveSlot];
    } else {
        roll = 100;
    }

    int noCalcIdx;
    for (noCalcIdx = 0; sNoDamageCalcMoveEffects[noCalcIdx] != 0xFFFF; noCalcIdx++) {
        if (MOVE_DATA(AI_CONTEXT.move).effect == sNoDamageCalcMoveEffects[noCalcIdx]) {
            break;
        }
    }

    int altPowerIdx;
    for (altPowerIdx = 0; sAltPowerMoveEffects[altPowerIdx] != 0xFFFF; altPowerIdx++) {
        if (MOVE_DATA(AI_CONTEXT.move).effect == sAltPowerMoveEffects[altPowerIdx]) {
            break;
        }
    }

    if (sAltPowerMoveEffects[altPowerIdx] != 0xFFFF
        || (MOVE_DATA(AI_CONTEXT.move).power > 1 && sNoDamageCalcMoveEffects[noCalcIdx] == 0xFFFF)) {
        u8 ivs[STAT_MAX];
        for (int stat = STAT_HP; stat < STAT_MAX; stat++) {
            ivs[stat] = BattleMon_Get(battleCtx, AI_CONTEXT.attacker, BATTLEMON_HP_IV + stat, NULL);
        }

        u32 damage = TrainerAI_CalcDamage(battleSys,
            battleCtx,
            AI_CONTEXT.move,
            battleCtx->battleMons[AI_CONTEXT.attacker].heldItem,
            ivs,
            AI_CONTEXT.attacker,
            Battler_Ability(battleCtx, AI_CONTEXT.attacker),
            battleCtx->battleMons[AI_CONTEXT.attacker].moveEffectsData.embargoTurns,
            roll);

        if (battleCtx->battleMons[AI_CONTEXT.defender].curHP <= damage) {
            AIScript_Iter(battleCtx, jump);
        }
    }
}

static void AICmd_IfCurrentMoveDoesNotKill(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    BOOL useDamageRoll = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    // Mirror of AICmd_IfCurrentMoveKills: these moves never count as securing a KO.
    if (AI_MoveEffectInTable(battleCtx, sNoKillCheckMoveEffects, AI_CONTEXT.move)) {
        AIScript_Iter(battleCtx, jump);
        return;
    }

    int roll;
    if (useDamageRoll == TRUE) {
        roll = AI_CONTEXT.moveDamageRolls[AI_CONTEXT.moveSlot];
    } else {
        roll = 100;
    }

    int noCalcIdx;
    for (noCalcIdx = 0; sNoDamageCalcMoveEffects[noCalcIdx] != 0xFFFF; noCalcIdx++) {
        if (MOVE_DATA(AI_CONTEXT.move).effect == sNoDamageCalcMoveEffects[noCalcIdx]) {
            break;
        }
    }

    int altPowerIdx;
    for (altPowerIdx = 0; sAltPowerMoveEffects[altPowerIdx] != 0xFFFF; altPowerIdx++) {
        if (MOVE_DATA(AI_CONTEXT.move).effect == sAltPowerMoveEffects[altPowerIdx]) {
            break;
        }
    }

    if (sAltPowerMoveEffects[altPowerIdx] != 0xFFFF
        || (MOVE_DATA(AI_CONTEXT.move).power > 1 && sNoDamageCalcMoveEffects[noCalcIdx] == 0xFFFF)) {
        u8 ivs[STAT_MAX];
        for (int stat = STAT_HP; stat < STAT_MAX; stat++) {
            ivs[stat] = BattleMon_Get(battleCtx, AI_CONTEXT.attacker, BATTLEMON_HP_IV + stat, NULL);
        }

        u32 damage = TrainerAI_CalcDamage(battleSys,
            battleCtx,
            AI_CONTEXT.move,
            battleCtx->battleMons[AI_CONTEXT.attacker].heldItem,
            ivs,
            AI_CONTEXT.attacker,
            Battler_Ability(battleCtx, AI_CONTEXT.attacker),
            battleCtx->battleMons[AI_CONTEXT.attacker].moveEffectsData.embargoTurns,
            roll);

        if (battleCtx->battleMons[AI_CONTEXT.defender].curHP > damage) {
            AIScript_Iter(battleCtx, jump);
        }
    }
}

static void AICmd_IfMoveKnown(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int move = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);
    int i;

    switch (inBattler) {
    case AI_BATTLER_ATTACKER:
        for (i = 0; i < LEARNED_MOVES_MAX; i++) {
            if (battleCtx->battleMons[battler].moves[i] == move) {
                break;
            }
        }

        if (i < LEARNED_MOVES_MAX) {
            AIScript_Iter(battleCtx, jump);
        }
        break;

    case AI_BATTLER_ATTACKER_PARTNER:
        if (battleCtx->battleMons[battler].curHP == 0) {
            break;
        }

        for (i = 0; i < LEARNED_MOVES_MAX; i++) {
            if (battleCtx->battleMons[battler].moves[i] == move) {
                break;
            }
        }

        if (i < LEARNED_MOVES_MAX) {
            AIScript_Iter(battleCtx, jump);
        }
        break;

    case AI_BATTLER_DEFENDER:
        for (i = 0; i < LEARNED_MOVES_MAX; i++) {
            if (AI_CONTEXT.battlerMoves[battler][i] == move) {
                break;
            }
        }

        if (i < LEARNED_MOVES_MAX) {
            AIScript_Iter(battleCtx, jump);
        }
        break;

    default:
        break;
    }
}

static void AICmd_IfMoveNotKnown(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int move = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);
    int i;

    switch (inBattler) {
    case AI_BATTLER_ATTACKER:
        for (i = 0; i < LEARNED_MOVES_MAX; i++) {
            if (battleCtx->battleMons[battler].moves[i] == move) {
                break;
            }
        }

        if (i == LEARNED_MOVES_MAX) {
            AIScript_Iter(battleCtx, jump);
        }
        break;

    case AI_BATTLER_ATTACKER_PARTNER:
        if (battleCtx->battleMons[battler].curHP == 0) {
            break;
        }

        for (i = 0; i < LEARNED_MOVES_MAX; i++) {
            if (battleCtx->battleMons[battler].moves[i] == move) {
                break;
            }
        }

        if (i == LEARNED_MOVES_MAX) {
            AIScript_Iter(battleCtx, jump);
        }
        break;

    case AI_BATTLER_DEFENDER:
        for (i = 0; i < LEARNED_MOVES_MAX; i++) {
            if (AI_CONTEXT.battlerMoves[battler][i] == move) {
                break;
            }
        }

        if (i == LEARNED_MOVES_MAX) {
            AIScript_Iter(battleCtx, jump);
        }
        break;

    default:
        break;
    }
}

static void AICmd_IfMoveEffectKnown(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int effect = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);
    int i;

    switch (inBattler) {
    case AI_BATTLER_ATTACKER:
        for (i = 0; i < LEARNED_MOVES_MAX; i++) {
            if (battleCtx->battleMons[battler].moves[i]
                && MOVE_DATA(battleCtx->battleMons[battler].moves[i]).effect == effect) {
                break;
            }
        }

        if (i < LEARNED_MOVES_MAX) {
            AIScript_Iter(battleCtx, jump);
        }
        break;

    case AI_BATTLER_DEFENDER:
        for (i = 0; i < LEARNED_MOVES_MAX; i++) {
            if (AI_CONTEXT.battlerMoves[battler][i]
                && MOVE_DATA(AI_CONTEXT.battlerMoves[battler][i]).effect == effect) {
                break;
            }
        }

        if (i < LEARNED_MOVES_MAX) {
            AIScript_Iter(battleCtx, jump);
        }
        break;

    default:
        break;
    }
}

static void AICmd_IfMoveEffectNotKnown(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int effect = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);
    int i;

    switch (inBattler) {
    case AI_BATTLER_ATTACKER:
        for (i = 0; i < LEARNED_MOVES_MAX; i++) {
            if (battleCtx->battleMons[battler].moves[i]
                && MOVE_DATA(battleCtx->battleMons[battler].moves[i]).effect == effect) {
                break;
            }
        }

        if (i == LEARNED_MOVES_MAX) {
            AIScript_Iter(battleCtx, jump);
        }
        break;

    case AI_BATTLER_DEFENDER:
        for (i = 0; i < LEARNED_MOVES_MAX; i++) {
            if (AI_CONTEXT.battlerMoves[battler][i]
                && MOVE_DATA(AI_CONTEXT.battlerMoves[battler][i]).effect == effect) {
                break;
            }
        }

        if (i == LEARNED_MOVES_MAX) {
            AIScript_Iter(battleCtx, jump);
        }
        break;

    default:
        break;
    }
}

static void AICmd_IfBattlerUnderEffect(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int check = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    switch (check) {
    case CHECK_DISABLE:
        if (battleCtx->battleMons[battler].moveEffectsData.disabledTurns) {
            AIScript_Iter(battleCtx, jump);
        }
        break;

    case CHECK_ENCORE:
        if (battleCtx->battleMons[battler].moveEffectsData.encoredTurns) {
            AIScript_Iter(battleCtx, jump);
        }
        break;

    default:
        break;
    }
}

static void AICmd_IfCurrentMoveMatchesEffect(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int check = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    switch (check) {
    case CHECK_DISABLE:
        if (battleCtx->battleMons[AI_CONTEXT.attacker].moveEffectsData.disabledMove == AI_CONTEXT.move) {
            AIScript_Iter(battleCtx, jump);
        }
        break;

    case CHECK_ENCORE:
        if (battleCtx->battleMons[AI_CONTEXT.attacker].moveEffectsData.encoredMove == AI_CONTEXT.move) {
            AIScript_Iter(battleCtx, jump);
        }
        break;

    default:
        break;
    }
}

static void AICmd_Escape(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    AI_CONTEXT.stateFlags |= (AI_STATUS_FLAG_DONE | AI_STATUS_FLAG_ESCAPE | AI_STATUS_FLAG_BREAK);
}

static void AICmd_Dummy3E(BattleSystem *battleSys, BattleContext *battleCtx)
{
    return;
}

static void AICmd_Dummy3F(BattleSystem *battleSys, BattleContext *battleCtx)
{
    return;
}

static void AICmd_LoadHeldItem(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    AI_CONTEXT.calcTemp = battleCtx->battleMons[battler].heldItem;
}

static void AICmd_LoadHeldItemEffect(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    if (AI_CONTEXT.attacker != battler) {
        AI_CONTEXT.calcTemp = BattleSystem_GetItemData(battleCtx, AI_CONTEXT.battlerHeldItems[battler], ITEM_PARAM_HOLD_EFFECT);
    } else {
        AI_CONTEXT.calcTemp = BattleSystem_GetItemData(battleCtx, battleCtx->battleMons[battler].heldItem, ITEM_PARAM_HOLD_EFFECT);
    }
}

static void AICmd_IfHeldItemEqualTo(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int expected = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);
    u16 heldItem;

    if ((battler & 1) == (AI_CONTEXT.attacker & 1)) {
        heldItem = battleCtx->battleMons[battler].heldItem;
    } else {
        heldItem = AI_CONTEXT.battlerHeldItems[battler];
    }

    if (heldItem == expected) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfFieldConditionsMask(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    u32 mask = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    if (battleCtx->fieldConditionsMask & mask) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_LoadSpikesLayers(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    u32 sideCondition = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);
    u8 side = BattleSystem_GetBattlerSide(battleSys, battler);

    switch (sideCondition) {
    case SIDE_CONDITION_SPIKES:
        AI_CONTEXT.calcTemp = battleCtx->sideConditions[side].spikesLayers;
        break;

    case SIDE_CONDITION_TOXIC_SPIKES:
        AI_CONTEXT.calcTemp = battleCtx->sideConditions[side].toxicSpikesLayers;
        break;
    }
}

static void AICmd_IfAnyPartyMemberIsWounded(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    for (int i = 0; i < BattleSystem_GetPartyCount(battleSys, battler); i++) {
        Pokemon *mon = BattleSystem_GetPartyPokemon(battleSys, battler, i);

        if (i != battleCtx->selectedPartySlot[battler]
            && Pokemon_GetValue(mon, MON_DATA_HP, NULL) != Pokemon_GetValue(mon, MON_DATA_MAX_HP, NULL)) {
            AIScript_Iter(battleCtx, jump);
            break;
        }
    }
}

static void AICmd_IfAnyPartyMemberUsedPP(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);
    int moveSlot; // must be declared outside of the loop to match

    for (int partySlot = 0; partySlot < BattleSystem_GetPartyCount(battleSys, battler); partySlot++) {
        Pokemon *mon = BattleSystem_GetPartyPokemon(battleSys, battler, partySlot);

        if (partySlot != battleCtx->selectedPartySlot[battler]) {
            for (moveSlot = 0; moveSlot < LEARNED_MOVES_MAX; moveSlot++) {
                if (Pokemon_GetValue(mon, MON_DATA_MOVE1_PP + moveSlot, NULL) != Pokemon_GetValue(mon, MON_DATA_MOVE1_MAX_PP + moveSlot, NULL)) {
                    AIScript_Iter(battleCtx, jump);
                    break;
                }
            }

            if (moveSlot != LEARNED_MOVES_MAX) {
                break;
            }
        }
    }
}

static void AICmd_LoadFlingPower(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    AI_CONTEXT.calcTemp = Battler_ItemFlingPower(battleCtx, battler);
}

static void AICmd_LoadCurrentMovePP(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    AI_CONTEXT.calcTemp = battleCtx->battleMons[AI_CONTEXT.attacker].ppCur[AI_CONTEXT.moveSlot];
}

static void AICmd_IfCanUseLastResort(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);
    int numKnownMoves = Battler_CountMoves(battleSys, battleCtx, battler);

    if (battleCtx->battleMons[battler].moveEffectsData.lastResortCount >= (numKnownMoves - 1) && numKnownMoves > 1) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_LoadCurrentMoveClass(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    AI_CONTEXT.calcTemp = MOVE_DATA(AI_CONTEXT.move).class;
}

static void AICmd_LoadDefenderLastUsedMoveClass(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    AI_CONTEXT.calcTemp = MOVE_DATA(battleCtx->movePrevByBattler[AI_CONTEXT.defender]).class;
}

static void AICmd_LoadBattlerSpeedRank(BattleSystem *battleSys, BattleContext *battleCtx)
{
    // Must declare C89-style to match
    int i, j;
    int speedOrder[4];
    int cmp1, cmp2;
    int maxBattlers;
    int battler;
    int inBattler;

    AIScript_Iter(battleCtx, 1);

    inBattler = AIScript_Read(battleCtx);
    battler = AIScript_Battler(battleCtx, inBattler);
    maxBattlers = BattleSystem_GetMaxBattlers(battleSys);

    for (i = 0; i < maxBattlers; i++) {
        speedOrder[i] = i;
    }

    for (i = 0; i < maxBattlers - 1; i++) {
        for (j = i + 1; j < maxBattlers; j++) {
            cmp1 = speedOrder[i];
            cmp2 = speedOrder[j];

            if (BattleSystem_CompareBattlerSpeed(battleSys, battleCtx, cmp1, cmp2, TRUE)) {
                speedOrder[i] = cmp2;
                speedOrder[j] = cmp1;
            }
        }
    }

    for (i = 0; i < maxBattlers; i++) {
        if (speedOrder[i] == battler) {
            AI_CONTEXT.calcTemp = i;
            break;
        }
    }
}

static void AICmd_LoadBattlerTurnCount(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int battler = AIScript_Battler(battleCtx, inBattler);

    AI_CONTEXT.calcTemp = battleCtx->totalTurns - battleCtx->battleMons[battler].moveEffectsData.fakeOutTurnNumber;
}

static void AICmd_IfPartyMemberDealsMoreDamage(BattleSystem *battleSys, BattleContext *battleCtx)
{
    // Declare C89-style to match
    int i, j;
    BOOL varyDamage;
    int jump;
    int battler;
    s32 activeMonDamage;
    s32 partyMonDamage;
    s32 allDamageVals[LEARNED_MOVES_MAX];
    u16 partyMonMoves[LEARNED_MOVES_MAX];
    u8 ivs[STAT_MAX];
    Pokemon *partyMon;

    AIScript_Iter(battleCtx, 1);

    varyDamage = AIScript_Read(battleCtx);
    jump = AIScript_Read(battleCtx);
    battler = AI_CONTEXT.attacker;

    for (i = 0; i < 6; i++) {
        ivs[i] = BattleMon_Get(battleCtx, battler, BATTLEMON_HP_IV + i, NULL);
    }

    activeMonDamage = TrainerAI_CalcAllDamage(battleSys,
        battleCtx,
        AI_CONTEXT.attacker,
        battleCtx->battleMons[battler].moves,
        allDamageVals,
        battleCtx->battleMons[battler].heldItem,
        ivs,
        Battler_Ability(battleCtx, battler),
        battleCtx->battleMons[battler].moveEffectsData.embargoTurns,
        varyDamage);

    for (i = 0; i < BattleSystem_GetPartyCount(battleSys, battler); i++) {
        if (i != battleCtx->selectedPartySlot[battler]) {
            partyMon = BattleSystem_GetPartyPokemon(battleSys, battler, i);

            if (Pokemon_GetValue(partyMon, MON_DATA_HP, NULL) != 0
                && Pokemon_GetValue(partyMon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_NONE
                && Pokemon_GetValue(partyMon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_EGG) {
                for (j = 0; j < LEARNED_MOVES_MAX; j++) {
                    partyMonMoves[j] = Pokemon_GetValue(partyMon, MON_DATA_MOVE1 + j, NULL);
                }

                for (j = 0; j < STAT_MAX; j++) {
                    ivs[j] = Pokemon_GetValue(partyMon, MON_DATA_HP_IV + j, NULL);
                }

                partyMonDamage = TrainerAI_CalcAllDamage(battleSys,
                    battleCtx,
                    AI_CONTEXT.attacker,
                    partyMonMoves,
                    allDamageVals,
                    Pokemon_GetValue(partyMon, MON_DATA_HELD_ITEM, NULL),
                    ivs,
                    Pokemon_GetValue(partyMon, MON_DATA_ABILITY, NULL),
                    FALSE,
                    varyDamage);

                if (partyMonDamage > activeMonDamage) {
                    AIScript_Iter(battleCtx, jump);
                    break;
                }
            }
        }
    }
}

static void AICmd_IfHasSuperEffectiveMove(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int jump = AIScript_Read(battleCtx);

    if (AI_HasSuperEffectiveMove(battleSys, battleCtx, AI_CONTEXT.attacker, TRUE) == TRUE) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfBattlerDealsMoreDamage(BattleSystem *battleSys, BattleContext *battleCtx)
{
    int i;
    int inBattler;
    BOOL varyDamage;
    int jump;
    int battler;
    int roll;
    s32 aiDamage;
    s32 battlerDamage;
    s32 damageVals[LEARNED_MOVES_MAX];
    u8 ivs[STAT_MAX];

    AIScript_Iter(battleCtx, 1);

    inBattler = AIScript_Read(battleCtx);
    varyDamage = AIScript_Read(battleCtx);
    jump = AIScript_Read(battleCtx);

    for (i = 0; i < STAT_MAX; i++) {
        ivs[i] = BattleMon_Get(battleCtx, AI_CONTEXT.attacker, BATTLEMON_HP_IV + i, NULL);
    }

    aiDamage = TrainerAI_CalcAllDamage(battleSys,
        battleCtx,
        AI_CONTEXT.attacker,
        battleCtx->battleMons[AI_CONTEXT.attacker].moves,
        damageVals,
        battleCtx->battleMons[AI_CONTEXT.attacker].heldItem,
        ivs,
        Battler_Ability(battleCtx, AI_CONTEXT.attacker),
        battleCtx->battleMons[AI_CONTEXT.attacker].moveEffectsData.embargoTurns,
        varyDamage);
    battler = AIScript_Battler(battleCtx, inBattler);

    if (varyDamage == TRUE) {
        roll = AI_CONTEXT.moveDamageRolls[AI_CONTEXT.moveSlot];
    } else {
        roll = 100;
    }

    battlerDamage = TrainerAI_CalcDamage(battleSys,
        battleCtx,
        battleCtx->movePrevByBattler[battler],
        battleCtx->battleMons[battler].heldItem,
        ivs,
        battler,
        Battler_Ability(battleCtx, battler),
        battleCtx->battleMons[battler].moveEffectsData.embargoTurns,
        roll);

    if (battlerDamage > aiDamage) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_SumPositiveStatStages(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int battler = AIScript_Battler(battleCtx, inBattler);

    AI_CONTEXT.calcTemp = 0;

    for (int stat = BATTLE_STAT_HP; stat < BATTLE_STAT_MAX; stat++) {
        if (battleCtx->battleMons[battler].statBoosts[stat] > 6) {
            AI_CONTEXT.calcTemp += battleCtx->battleMons[battler].statBoosts[stat] - 6;
        }
    }
}

static void AICmd_DiffStatStages(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int stat = AIScript_Read(battleCtx);
    int battler = AIScript_Battler(battleCtx, inBattler);

    AI_CONTEXT.calcTemp = battleCtx->battleMons[battler].statBoosts[stat] - battleCtx->battleMons[AI_CONTEXT.attacker].statBoosts[stat];
}

static void AICmd_IfBattlerHasHigherStat(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int stat = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    int battler = AIScript_Battler(battleCtx, inBattler);

    int aiStat, battlerStat;
    TrainerAI_GetStats(battleCtx, battler, &aiStat, &battlerStat, stat);

    if (aiStat < battlerStat) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfBattlerHasLowerStat(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int stat = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    int battler = AIScript_Battler(battleCtx, inBattler);

    int aiStat, battlerStat;
    TrainerAI_GetStats(battleCtx, battler, &aiStat, &battlerStat, stat);

    if (aiStat > battlerStat) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfBattlerHasEqualStat(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int stat = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    int battler = AIScript_Battler(battleCtx, inBattler);

    int aiStat, battlerStat;
    TrainerAI_GetStats(battleCtx, battler, &aiStat, &battlerStat, stat);

    if (aiStat == battlerStat) {
        AIScript_Iter(battleCtx, jump);
    }
}

/**
 * @brief Get the values for a given stat for the AI battler and another given battler.
 *
 * @param battleCtx
 * @param battler   The other battler whose stats will be retrieved.
 * @param buf1      Buffer to hold the stat-value for the AI battler.
 * @param buf2      Buffer to hold the stat-value for the given other battler.
 * @param stat      Which stat value to load.
 */
static void TrainerAI_GetStats(BattleContext *battleCtx, int battler, int *buf1, int *buf2, int stat)
{
    switch (stat) {
    case BATTLE_STAT_HP:
        *buf1 = battleCtx->battleMons[AI_CONTEXT.attacker].curHP;
        *buf2 = battleCtx->battleMons[battler].curHP;
        break;

    case BATTLE_STAT_ATTACK:
        *buf1 = battleCtx->battleMons[AI_CONTEXT.attacker].attack;
        *buf2 = battleCtx->battleMons[battler].attack;
        break;

    case BATTLE_STAT_DEFENSE:
        *buf1 = battleCtx->battleMons[AI_CONTEXT.attacker].defense;
        *buf2 = battleCtx->battleMons[battler].defense;
        break;

    case BATTLE_STAT_SP_ATTACK:
        *buf1 = battleCtx->battleMons[AI_CONTEXT.attacker].spAttack;
        *buf2 = battleCtx->battleMons[battler].spAttack;
        break;

    case BATTLE_STAT_SP_DEFENSE:
        *buf1 = battleCtx->battleMons[AI_CONTEXT.attacker].spDefense;
        *buf2 = battleCtx->battleMons[battler].spDefense;
        break;

    case BATTLE_STAT_SPEED:
        *buf1 = battleCtx->battleMons[AI_CONTEXT.attacker].speed;
        *buf2 = battleCtx->battleMons[battler].speed;
        break;

    default:
        GF_ASSERT(FALSE);
        break;
    }
}

static void AICmd_CheckIfHighestDamageWithPartner(BattleSystem *battleSys, BattleContext *battleCtx)
{
    int i = 0, j, k;
    s32 moveDamage;
    s32 damageVals[LEARNED_MOVES_MAX];
    BOOL varyDamage;
    u8 ivs[STAT_MAX];
    int battler;

    AIScript_Iter(battleCtx, 1);
    varyDamage = AIScript_Read(battleCtx);

    for (j = 0; sNoDamageCalcMoveEffects[j] != 0xFFFF; j++) {
        if (MOVE_DATA(AI_CONTEXT.move).effect == sNoDamageCalcMoveEffects[j]) {
            break;
        }
    }

    for (k = 0; sAltPowerMoveEffects[k] != 0xFFFF; k++) {
        if (MOVE_DATA(AI_CONTEXT.move).effect == sAltPowerMoveEffects[k]) {
            break;
        }
    }

    if (sAltPowerMoveEffects[k] != 0xFFFF
        || (MOVE_DATA(AI_CONTEXT.move).power > 1 && sNoDamageCalcMoveEffects[j] == 0xFFFF)) {
        battler = AI_CONTEXT.attacker;

        for (j = 0; j < MAX_BATTLERS_PER_SIDE; j++) {
            for (i = STAT_HP; i < STAT_MAX; i++) {
                ivs[i] = BattleMon_Get(battleCtx, battler, BATTLEMON_HP_IV + i, NULL);
            }

            TrainerAI_CalcAllDamage(battleSys,
                battleCtx,
                battler,
                battleCtx->battleMons[battler].moves,
                damageVals,
                battleCtx->battleMons[battler].heldItem,
                ivs,
                Battler_Ability(battleCtx, battler),
                battleCtx->battleMons[battler].moveEffectsData.embargoTurns,
                varyDamage);

            // Update to the partner for the next iteration
            battler = BattleSystem_GetPartner(battleSys, AI_CONTEXT.attacker);

            if (j == 0) {
                moveDamage = damageVals[AI_CONTEXT.moveSlot];
            }

            for (i = 0; i < LEARNED_MOVES_MAX; i++) {
                if (damageVals[i] > moveDamage) {
                    break;
                }
            }

            if (i == LEARNED_MOVES_MAX) {
                AI_CONTEXT.calcTemp = AI_MOVE_IS_HIGHEST_DAMAGE;
            } else {
                AI_CONTEXT.calcTemp = AI_NOT_HIGHEST_DAMAGE;
                break;
            }
        }
    } else {
        AI_CONTEXT.calcTemp = AI_NO_COMPARISON_MADE;
    }
}

static void AICmd_IfBattlerFainted(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    GF_ASSERT(inBattler != AI_BATTLER_ATTACKER);
    GF_ASSERT(inBattler != AI_BATTLER_DEFENDER);

    int battler = AIScript_Battler(battleCtx, inBattler);
    if (battleCtx->battlersSwitchingMask & FlagIndex(battler)) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfBattlerNotFainted(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    GF_ASSERT(inBattler != AI_BATTLER_ATTACKER);
    GF_ASSERT(inBattler != AI_BATTLER_DEFENDER);

    int battler = AIScript_Battler(battleCtx, inBattler);
    if ((battleCtx->battlersSwitchingMask & FlagIndex(battler)) == FALSE) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_LoadGender(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    AI_CONTEXT.calcTemp = battleCtx->battleMons[battler].gender;
}

static void AICmd_LoadIsFirstTurnInBattle(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    if (battleCtx->battleMons[battler].moveEffectsData.fakeOutTurnNumber < battleCtx->totalTurns) {
        AI_CONTEXT.calcTemp = FALSE;
    } else {
        AI_CONTEXT.calcTemp = TRUE;
    }
}

static void AICmd_LoadStockpileCount(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    AI_CONTEXT.calcTemp = battleCtx->battleMons[battler].moveEffectsData.stockpileCount;
}

static void AICmd_LoadBattleType(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    AI_CONTEXT.calcTemp = battleSys->battleType;
}

static void AICmd_LoadRecycleItem(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    int partySlot = battleCtx->selectedPartySlot[battler];
    AI_CONTEXT.calcTemp = battleCtx->recycleItem[battler][partySlot];
}

static void AICmd_LoadTypeOfLoadedMove(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    AI_CONTEXT.calcTemp = MOVE_DATA(AI_CONTEXT.calcTemp).type;
}

static void AICmd_LoadPowerOfLoadedMove(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    AI_CONTEXT.calcTemp = MOVE_DATA(AI_CONTEXT.calcTemp).power;
}

static void AICmd_LoadEffectOfLoadedMove(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    AI_CONTEXT.calcTemp = MOVE_DATA(AI_CONTEXT.calcTemp).effect;
}

static void AICmd_LoadProtectChain(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    if (battleCtx->moveProtect[battler] != MOVE_PROTECT
        && battleCtx->moveProtect[battler] != MOVE_DETECT
        && battleCtx->moveProtect[battler] != MOVE_ENDURE
        && battleCtx->moveProtect[battler] != MOVE_SILK_TRAP
        && battleCtx->moveProtect[battler] != MOVE_SPIKY_SHIELD) {
        AI_CONTEXT.calcTemp = 0;
    } else {
        AI_CONTEXT.calcTemp = battleCtx->battleMons[battler].moveEffectsData.protectSuccessTurns;
    }
}

static void AICmd_PushAndGoTo(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    int jump = AIScript_Read(battleCtx);
    AIScript_PushCursor(battleSys, battleCtx, jump);
}

static void AICmd_GoTo(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    int jump = AIScript_Read(battleCtx);
    AIScript_Iter(battleCtx, jump);
}

static void AICmd_PopOrEnd(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    if (AIScript_PopCursor(battleSys, battleCtx) == TRUE) {
        return;
    }

    AI_CONTEXT.stateFlags |= AI_STATUS_FLAG_DONE;
}

static void AICmd_IfLevel(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int op = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    switch (op) {
    case CHECK_HIGHER_THAN_TARGET:
        if (battleCtx->battleMons[AI_CONTEXT.attacker].level > battleCtx->battleMons[AI_CONTEXT.defender].level) {
            AIScript_Iter(battleCtx, jump);
        }
        break;

    case CHECK_LOWER_THAN_TARGET:
        if (battleCtx->battleMons[AI_CONTEXT.attacker].level < battleCtx->battleMons[AI_CONTEXT.defender].level) {
            AIScript_Iter(battleCtx, jump);
        }
        break;

    case CHECK_EQUAL_TO_TARGET:
        if (battleCtx->battleMons[AI_CONTEXT.attacker].level == battleCtx->battleMons[AI_CONTEXT.defender].level) {
            AIScript_Iter(battleCtx, jump);
        }
        break;

    default:
        break;
    }
}

static void AICmd_IfTargetIsTaunted(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    int jump = AIScript_Read(battleCtx);

    if (battleCtx->battleMons[AI_CONTEXT.defender].moveEffectsData.tauntedTurns) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfTargetIsNotTaunted(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    int jump = AIScript_Read(battleCtx);

    if (battleCtx->battleMons[AI_CONTEXT.defender].moveEffectsData.tauntedTurns == 0) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfTargetIsPartner(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int jump = AIScript_Read(battleCtx);

    if ((AI_CONTEXT.attacker & 1) == (AI_CONTEXT.defender & 1)) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfActivatedFlashFire(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    if (battleCtx->battleMons[battler].moveEffectsData.flashFire) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_LoadAbility(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    AI_CONTEXT.calcTemp = Battler_Ability(battleCtx, battler);
}

static void AICmd_IfLockOnTarget(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inAttacker = AIScript_Read(battleCtx);
    int inTarget = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 attacker = AIScript_Battler(battleCtx, inAttacker);
    u8 target = AIScript_Battler(battleCtx, inTarget);

    if ((battleCtx->battleMons[attacker].moveEffectsMask & MOVE_EFFECT_LOCK_ON)
        && battleCtx->battleMons[attacker].moveEffectsData.lockOnTarget == target) {
        AIScript_Iter(battleCtx, jump);
    }
}

/**
 * @brief Check whether a move's effect appears in one of the AI's effect tables.
 *
 * @param battleCtx
 * @param effects   A 0xFFFF-terminated table of battle effects.
 * @param move
 * @return TRUE if the move's effect is listed.
 */
static BOOL AI_MoveEffectInTable(BattleContext *battleCtx, const u16 *effects, u16 move)
{
    for (int i = 0; effects[i] != 0xFFFF; i++) {
        if (MOVE_DATA(move).effect == effects[i]) {
            return TRUE;
        }
    }

    return FALSE;
}

/**
 * @brief Check whether the AI is able to put a damage figure on a move at all.
 *
 * Moves with an alternate-power effect always qualify, because their listed power is only a
 * placeholder. Everything else needs real power and an effect the AI knows how to model.
 *
 * @param battleCtx
 * @param move
 * @return TRUE if scoring can compute damage for this move.
 */
static BOOL AI_MoveHasDamageEstimate(BattleContext *battleCtx, u16 move)
{
    if (AI_MoveEffectInTable(battleCtx, sAltPowerMoveEffects, move)) {
        return TRUE;
    }

    return MOVE_DATA(move).power > 1 && AI_MoveEffectInTable(battleCtx, sNoDamageCalcMoveEffects, move) == FALSE;
}

/**
 * @brief Classify the current move against the rest of the attacker's moveset, using each
 * move's own damage roll for this turn.
 *
 * A move which would KO the target is always flagged as a best-damage move, so that several
 * lethal options compete on equal footing rather than only the single biggest hit.
 *
 * Sets AI_CONTEXT.calcTemp to AI_NO_COMPARISON_MADE, AI_NOT_HIGHEST_DAMAGE, or
 * AI_MOVE_IS_HIGHEST_DAMAGE.
 *
 * @param battleSys
 * @param battleCtx
 */
static void AICmd_FlagBestDamageMove(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    u16 *moves = battleCtx->battleMons[AI_CONTEXT.attacker].moves;

    if (AI_MoveHasDamageEstimate(battleCtx, AI_CONTEXT.move) == FALSE
        || AI_MoveEffectInTable(battleCtx, sExcludedFromBestDamageMoveEffects, AI_CONTEXT.move)) {
        AI_CONTEXT.calcTemp = AI_NO_COMPARISON_MADE;
        return;
    }

    u8 ivs[STAT_MAX];
    for (int i = 0; i < STAT_MAX; i++) {
        ivs[i] = BattleMon_Get(battleCtx, AI_CONTEXT.attacker, BATTLEMON_HP_IV + i, NULL);
    }

    s32 moveDamage[LEARNED_MOVES_MAX];
    TrainerAI_CalcAllDamage(battleSys,
        battleCtx,
        AI_CONTEXT.attacker,
        moves,
        moveDamage,
        battleCtx->battleMons[AI_CONTEXT.attacker].heldItem,
        ivs,
        Battler_Ability(battleCtx, AI_CONTEXT.attacker),
        battleCtx->battleMons[AI_CONTEXT.attacker].moveEffectsData.embargoTurns,
        TRUE);

    if (moveDamage[AI_CONTEXT.moveSlot] >= battleCtx->battleMons[AI_CONTEXT.defender].curHP) {
        AI_CONTEXT.calcTemp = AI_MOVE_IS_HIGHEST_DAMAGE;
        return;
    }

    for (int i = 0; i < LEARNED_MOVES_MAX; i++) {
        if (i == AI_CONTEXT.moveSlot
            || moves[i] == MOVE_NONE
            || battleCtx->battleMons[AI_CONTEXT.attacker].ppCur[i] == 0
            || AI_MoveEffectInTable(battleCtx, sExcludedFromBestDamageMoveEffects, moves[i])) {
            continue;
        }

        if (moveDamage[i] > moveDamage[AI_CONTEXT.moveSlot]) {
            AI_CONTEXT.calcTemp = AI_NOT_HIGHEST_DAMAGE;
            return;
        }
    }

    AI_CONTEXT.calcTemp = AI_MOVE_IS_HIGHEST_DAMAGE;
}

/**
 * @brief Compute the damage which the target's best move would deal to the attacker.
 *
 * Uses this turn's damage rolls rather than maximum damage.
 *
 * @param battleSys
 * @param battleCtx
 * @return The largest damage roll coming back at the attacker.
 */
static s32 AI_MaxIncomingDamage(BattleSystem *battleSys, BattleContext *battleCtx)
{
    int attacker = AI_CONTEXT.attacker;
    int defender = AI_CONTEXT.defender;

    u8 ivs[STAT_MAX];
    for (int i = 0; i < STAT_MAX; i++) {
        ivs[i] = BattleMon_Get(battleCtx, defender, BATTLEMON_HP_IV + i, NULL);
    }

    // TrainerAI_CalcAllDamage always scores against AI_CONTEXT.defender, so the two battlers
    // have to be swapped to measure damage coming the other way.
    s32 damageVals[LEARNED_MOVES_MAX];
    AI_CONTEXT.defender = attacker;

    s32 maxDamage = TrainerAI_CalcAllDamage(battleSys,
        battleCtx,
        defender,
        battleCtx->battleMons[defender].moves,
        damageVals,
        battleCtx->battleMons[defender].heldItem,
        ivs,
        Battler_Ability(battleCtx, defender),
        battleCtx->battleMons[defender].moveEffectsData.embargoTurns,
        TRUE);

    AI_CONTEXT.defender = defender;

    return maxDamage;
}

/**
 * @brief Check whether the target's best move would knock the attacker out.
 *
 * @param battleSys
 * @param battleCtx
 */
static void AICmd_IfDefenderCanKO(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    int jump = AIScript_Read(battleCtx);

    if (AI_MaxIncomingDamage(battleSys, battleCtx) >= battleCtx->battleMons[AI_CONTEXT.attacker].curHP) {
        AIScript_Iter(battleCtx, jump);
    }
}

/**
 * @brief Check whether the target's best move would knock the attacker out within a given
 * number of hits, assuming it keeps picking that move.
 *
 * @param battleSys
 * @param battleCtx
 */
/**
 * @brief Check whether the attacker's best move would knock the target out.
 *
 * Uses this turn's damage rolls rather than maximum damage.
 *
 * @param battleSys
 * @param battleCtx
 */
static void AICmd_IfAttackerCanKO(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    int jump = AIScript_Read(battleCtx);

    int attacker = AI_CONTEXT.attacker;

    u8 ivs[STAT_MAX];
    for (int i = 0; i < STAT_MAX; i++) {
        ivs[i] = BattleMon_Get(battleCtx, attacker, BATTLEMON_HP_IV + i, NULL);
    }

    s32 damageVals[LEARNED_MOVES_MAX];
    s32 maxDamage = TrainerAI_CalcAllDamage(battleSys,
        battleCtx,
        attacker,
        battleCtx->battleMons[attacker].moves,
        damageVals,
        battleCtx->battleMons[attacker].heldItem,
        ivs,
        Battler_Ability(battleCtx, attacker),
        battleCtx->battleMons[attacker].moveEffectsData.embargoTurns,
        TRUE);

    if (maxDamage >= battleCtx->battleMons[AI_CONTEXT.defender].curHP) {
        AIScript_Iter(battleCtx, jump);
    }
}

/**
 * @brief Estimate the HP a battler will lose to end-of-turn effects, net of the healing it
 * gets back over the same window.
 *
 * The order mirrors the turn-end sequence in BattleControllerPlayer_CheckMonConditions, so
 * that a battler which is about to be finished off by chip damage can be spotted before the
 * AI commits a turn to stalling.
 *
 * @param battleSys
 * @param battleCtx
 * @param battler
 * @return Net HP lost at the end of this turn; negative if the battler nets healing.
 */
static int AI_ResidualDamage(BattleSystem *battleSys, BattleContext *battleCtx, int battler)
{
    BattleMon *mon = &battleCtx->battleMons[battler];
    int ability = Battler_Ability(battleCtx, battler);
    int itemEffect = Battler_HeldItemEffect(battleCtx, battler);
    int type1 = BattleMon_Get(battleCtx, battler, BATTLEMON_TYPE_1, NULL);
    int type2 = BattleMon_Get(battleCtx, battler, BATTLEMON_TYPE_2, NULL);
    int damage = 0;

    if (NO_CLOUD_NINE && (mon->moveEffectsMask & MOVE_EFFECT_NO_WEATHER_DAMAGE) == FALSE) {
        if (WEATHER_IS_SAND
            && type1 != TYPE_ROCK && type2 != TYPE_ROCK
            && type1 != TYPE_STEEL && type2 != TYPE_STEEL
            && type1 != TYPE_GROUND && type2 != TYPE_GROUND
            && ability != ABILITY_SAND_VEIL
            && ability != ABILITY_SAND_FORCE
            && ability != ABILITY_SAND_RUSH
            && ability != ABILITY_OVERCOAT
            && itemEffect != HOLD_EFFECT_OVERCOAT) {
            damage += BattleSystem_Divide(mon->maxHP, 16);
        }

        if (WEATHER_IS_HAIL) {
            if (ability == ABILITY_ICE_BODY) {
                damage -= BattleSystem_Divide(mon->maxHP, 16);
            } else if (type1 != TYPE_ICE
                && type2 != TYPE_ICE
                && ability != ABILITY_OVERCOAT
                && ability != ABILITY_SNOW_CLOAK
                && itemEffect != HOLD_EFFECT_OVERCOAT) {
                damage += BattleSystem_Divide(mon->maxHP, 16);
            }
        }

        if (WEATHER_IS_RAIN && ability == ABILITY_RAIN_DISH) {
            damage -= BattleSystem_Divide(mon->maxHP, 16);
        }

        if (WEATHER_IS_SUN && (ability == ABILITY_DRY_SKIN || ability == ABILITY_SOLAR_POWER)) {
            damage += BattleSystem_Divide(mon->maxHP, 8);
        } else if (WEATHER_IS_RAIN && ability == ABILITY_DRY_SKIN) {
            damage -= BattleSystem_Divide(mon->maxHP, 8);
        }
    }

    if (itemEffect == HOLD_EFFECT_HP_RESTORE_GRADUAL) {
        damage -= BattleSystem_Divide(mon->maxHP, 16);
    }

    if (mon->moveEffectsMask & MOVE_EFFECT_INGRAIN) {
        damage -= BattleSystem_Divide(mon->maxHP, 16);
    }

    if (mon->moveEffectsMask & MOVE_EFFECT_AQUA_RING) {
        damage -= BattleSystem_Divide(mon->maxHP, 16);
    }

    // Magic Guard stops every source below, and only those.
    if (ability == ABILITY_MAGIC_GUARD) {
        return damage;
    }

    if ((mon->moveEffectsMask & MOVE_EFFECT_LEECH_SEED)
        && battleCtx->battleMons[mon->moveEffectsMask & MOVE_EFFECT_LEECH_SEED_RECIPIENT].curHP) {
        damage += BattleSystem_Divide(mon->maxHP, 8);
    }

    if (mon->status & MON_CONDITION_POISON) {
        damage += ability == ABILITY_POISON_HEAL
            ? -BattleSystem_Divide(mon->maxHP, 8)
            : BattleSystem_Divide(mon->maxHP, 8);
    }

    if (mon->status & MON_CONDITION_TOXIC) {
        if (ability == ABILITY_POISON_HEAL) {
            damage -= BattleSystem_Divide(mon->maxHP, 8);
        } else {
            // The counter is incremented before it is applied, so the next tick is one stage
            // above the stage on the board now.
            int stage = (mon->status & MON_CONDITION_TOXIC_COUNTER) >> 8;

            if (stage < (MON_CONDITION_TOXIC_COUNTER >> 8)) {
                stage++;
            }

            damage += BattleSystem_Divide(mon->maxHP, 16) * stage;
        }
    }

    if (mon->status & MON_CONDITION_BURN) {
        damage += BattleSystem_Divide(mon->maxHP, ability == ABILITY_HEATPROOF ? 32 : 16);
    }

    if ((mon->statusVolatile & VOLATILE_CONDITION_NIGHTMARE) && (mon->status & MON_CONDITION_SLEEP)) {
        damage += BattleSystem_Divide(mon->maxHP, 4);
    }

    if (mon->statusVolatile & VOLATILE_CONDITION_CURSE) {
        damage += BattleSystem_Divide(mon->maxHP, 4);
    }

    // The bind counter is decremented before the tick, so the last turn of a bind deals nothing.
    if ((mon->statusVolatile & VOLATILE_CONDITION_BIND)
        && (mon->statusVolatile - (1 << VOLATILE_CONDITION_BIND_SHIFT)) & VOLATILE_CONDITION_BIND) {
        damage += BattleSystem_Divide(mon->maxHP, 8);
    }

    if ((mon->status & MON_CONDITION_SLEEP)
        && BattleSystem_CountAbility(battleSys, battleCtx, COUNT_ALIVE_BATTLERS_THEIR_SIDE_FLAG, battler, ABILITY_BAD_DREAMS)) {
        damage += BattleSystem_Divide(mon->maxHP, 8);
    }

    return damage;
}

/**
 * @brief Check whether end-of-turn chip damage alone would knock the attacker out.
 *
 * @param battleSys
 * @param battleCtx
 */
static void AICmd_IfResidualDamageKOsAttacker(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    int jump = AIScript_Read(battleCtx);

    int attacker = AI_CONTEXT.attacker;

    if (AI_ResidualDamage(battleSys, battleCtx, attacker) >= battleCtx->battleMons[attacker].curHP) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfDefenderCanKOInHits(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    int hits = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    if (AI_MaxIncomingDamage(battleSys, battleCtx) * hits >= battleCtx->battleMons[AI_CONTEXT.attacker].curHP) {
        AIScript_Iter(battleCtx, jump);
    }
}

/**
 * @brief Inverse of AICmd_IfDefenderCanKOInHits.
 *
 * @param battleSys
 * @param battleCtx
 */
static void AICmd_IfDefenderCannotKOInHits(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    int hits = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);

    if (AI_MaxIncomingDamage(battleSys, battleCtx) * hits < battleCtx->battleMons[AI_CONTEXT.attacker].curHP) {
        AIScript_Iter(battleCtx, jump);
    }
}

/**
 * @brief Check whether the target could knock the attacker out through the defensive drops
 * which Shell Smash is about to apply.
 *
 * A White Herb restores the drops as soon as they land, so the attacker's current stages
 * stand in that case.
 *
 * @param battleSys
 * @param battleCtx
 */
static void AICmd_IfDefenderCanKOAfterShellSmash(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    int jump = AIScript_Read(battleCtx);

    int attacker = AI_CONTEXT.attacker;
    BattleMon *mon = &battleCtx->battleMons[attacker];
    s8 def = mon->statBoosts[BATTLE_STAT_DEFENSE];
    s8 spDef = mon->statBoosts[BATTLE_STAT_SP_DEFENSE];

    if (Battler_HeldItemEffect(battleCtx, attacker) != HOLD_EFFECT_STATDOWN_RESTORE) {
        if (mon->statBoosts[BATTLE_STAT_DEFENSE] > 0) {
            mon->statBoosts[BATTLE_STAT_DEFENSE]--;
        }

        if (mon->statBoosts[BATTLE_STAT_SP_DEFENSE] > 0) {
            mon->statBoosts[BATTLE_STAT_SP_DEFENSE]--;
        }
    }

    s32 maxDamage = AI_MaxIncomingDamage(battleSys, battleCtx);

    mon->statBoosts[BATTLE_STAT_DEFENSE] = def;
    mon->statBoosts[BATTLE_STAT_SP_DEFENSE] = spDef;

    if (maxDamage >= mon->curHP) {
        AIScript_Iter(battleCtx, jump);
    }
}

/**
 * @brief Check whether the target could knock the attacker out of the HP which Belly Drum
 * is about to leave it on, counting a pinch berry which the cost would trigger.
 *
 * @param battleSys
 * @param battleCtx
 */
static void AICmd_IfDefenderCanKOAfterBellyDrum(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    int jump = AIScript_Read(battleCtx);

    int attacker = AI_CONTEXT.attacker;
    BattleMon *mon = &battleCtx->battleMons[attacker];
    int hp = mon->curHP - mon->maxHP / 2;

    if (hp <= mon->maxHP / 2 && Battler_HeldItemEffect(battleCtx, attacker) == HOLD_EFFECT_HP_PCT_RESTORE) {
        hp += BattleSystem_Divide(mon->maxHP * Battler_HeldItemPower(battleCtx, attacker, ITEM_POWER_CHECK_ALL), 100);
    }

    if (AI_MaxIncomingDamage(battleSys, battleCtx) >= hp) {
        AIScript_Iter(battleCtx, jump);
    }
}

/**
 * @brief Check whether a battler will be unable to act this turn.
 *
 * Covers sleep, a freeze which none of the battler's own moves would thaw, the recharge turn
 * owed after a move like Hyper Beam, and a Truant loaf.
 *
 * @param battleCtx
 * @param battler
 * @return TRUE if the battler cannot move this turn.
 */
static BOOL AI_BattlerIsIncapacitated(BattleContext *battleCtx, int battler)
{
    if (battleCtx->battleMons[battler].status & MON_CONDITION_SLEEP) {
        return TRUE;
    }

    if (battleCtx->battleMons[battler].statusVolatile & VOLATILE_CONDITION_RECHARGING) {
        return TRUE;
    }

    if (Battler_CheckTruant(battleCtx, battler)) {
        return TRUE;
    }

    if ((battleCtx->battleMons[battler].status & MON_CONDITION_FREEZE) == FALSE) {
        return FALSE;
    }

    for (int i = 0; i < LEARNED_MOVES_MAX; i++) {
        u16 move = battleCtx->battleMons[battler].moves[i];

        if (move == MOVE_NONE) {
            continue;
        }

        if (move == MOVE_SCALD
            || MOVE_DATA(move).effect == BATTLE_EFFECT_THAW_AND_BURN_HIT
            || MOVE_DATA(move).effect == BATTLE_EFFECT_RECOIL_BURN_HIT) {
            return FALSE;
        }
    }

    return TRUE;
}

static void AICmd_IfBattlerIncapacitated(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    if (AI_BattlerIsIncapacitated(battleCtx, battler)) {
        AIScript_Iter(battleCtx, jump);
    }
}

/**
 * @brief Check whether a battler knows a damaging move of a given class.
 *
 * @param battleSys
 * @param battleCtx
 */
static void AICmd_IfBattlerHasDamagingMoveOfClass(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);

    int inBattler = AIScript_Read(battleCtx);
    int class = AIScript_Read(battleCtx);
    int jump = AIScript_Read(battleCtx);
    u8 battler = AIScript_Battler(battleCtx, inBattler);

    for (int i = 0; i < LEARNED_MOVES_MAX; i++) {
        u16 move = battleCtx->battleMons[battler].moves[i];

        if (move != MOVE_NONE && MOVE_DATA(move).class == class) {
            AIScript_Iter(battleCtx, jump);
            return;
        }
    }
}

/**
 * @brief Check whether the attacker and its target have any move in common.
 *
 * @param battleSys
 * @param battleCtx
 */
static void AICmd_IfBattlersShareMove(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    int jump = AIScript_Read(battleCtx);

    u16 *attackerMoves = battleCtx->battleMons[AI_CONTEXT.attacker].moves;
    u16 *defenderMoves = battleCtx->battleMons[AI_CONTEXT.defender].moves;

    for (int i = 0; i < LEARNED_MOVES_MAX; i++) {
        if (attackerMoves[i] == MOVE_NONE) {
            continue;
        }

        for (int j = 0; j < LEARNED_MOVES_MAX; j++) {
            if (attackerMoves[i] == defenderMoves[j]) {
                AIScript_Iter(battleCtx, jump);
                return;
            }
        }
    }
}

/**
 * @brief Check whether any battler on the opposing side outspeeds the attacker or its partner.
 *
 * Speed-control moves are only worth the turn while something on the other side is still
 * moving first, which in a double battle means measuring both of the AI's slots.
 *
 * @param battleSys
 * @param battleCtx
 */
static void AICmd_IfAnyOpponentOutspeedsSide(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    int jump = AIScript_Read(battleCtx);

    int attacker = AI_CONTEXT.attacker;
    int partner = attacker ^ 2;
    int maxBattlers = BattleSystem_GetMaxBattlers(battleSys);

    for (int opponent = 0; opponent < maxBattlers; opponent++) {
        if ((opponent & 1) == (attacker & 1) || battleCtx->battleMons[opponent].curHP == 0) {
            continue;
        }

        if (BattleSystem_CompareBattlerSpeed(battleSys, battleCtx, opponent, attacker, TRUE) == COMPARE_SPEED_FASTER) {
            AIScript_Iter(battleCtx, jump);
            return;
        }

        if (partner < maxBattlers
            && battleCtx->battleMons[partner].curHP
            && BattleSystem_CompareBattlerSpeed(battleSys, battleCtx, opponent, partner, TRUE) == COMPARE_SPEED_FASTER) {
            AIScript_Iter(battleCtx, jump);
            return;
        }
    }
}

/**
 * @brief Check whether paralyzing the target would take the speed lead off it.
 *
 * Asks the engine for the comparison with the status applied rather than assuming a fixed
 * divisor, so the answer tracks whatever the paralysis modifier and Quick Feet actually do.
 *
 * @param battleSys
 * @param battleCtx
 */
static void AICmd_IfParalysisFlipsSpeed(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    int jump = AIScript_Read(battleCtx);

    int attacker = AI_CONTEXT.attacker;
    int defender = AI_CONTEXT.defender;

    if (BattleSystem_CompareBattlerSpeed(battleSys, battleCtx, defender, attacker, TRUE) != COMPARE_SPEED_FASTER) {
        return;
    }

    u32 status = battleCtx->battleMons[defender].status;
    battleCtx->battleMons[defender].status |= MON_CONDITION_PARALYSIS;

    int compare = BattleSystem_CompareBattlerSpeed(battleSys, battleCtx, defender, attacker, TRUE);

    battleCtx->battleMons[defender].status = status;

    if (compare != COMPARE_SPEED_FASTER) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfCurrentMoveHasPriority(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    int jump = AIScript_Read(battleCtx);

    if (MOVE_DATA(AI_CONTEXT.move).priority > 0) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfCurrentMoveIsSound(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    int jump = AIScript_Read(battleCtx);

    if (BattleSystem_IsSoundMove(AI_CONTEXT.move)) {
        AIScript_Iter(battleCtx, jump);
    }
}

static void AICmd_IfCurrentMoveIsWind(BattleSystem *battleSys, BattleContext *battleCtx)
{
    AIScript_Iter(battleCtx, 1);
    int jump = AIScript_Read(battleCtx);

    if (BattleSystem_IsWindMove(AI_CONTEXT.move)) {
        AIScript_Iter(battleCtx, jump);
    }
}

/**
 * @brief Push an address for the AI script onto the cursor stack.
 *
 * @param battleSys
 * @param battleCtx
 * @param offset    Distance to jump ahead after pushing the cursor.
 */
static void AIScript_PushCursor(BattleSystem *battleSys, BattleContext *battleCtx, int offset)
{
    AI_CONTEXT.scriptStackPointer[AI_CONTEXT.scriptStackSize++] = battleCtx->aiScriptCursor;
    AIScript_Iter(battleCtx, offset);

    GF_ASSERT(AI_CONTEXT.scriptStackSize <= AI_MAX_STACK_SIZE);
}

/**
 * @brief Pop the top element of the cursor stack into the cursor.
 *
 * @param battleSys
 * @param battleCtx
 * @return TRUE if the cursor stack had an element to be popped; FALSE
 * if it was empty.
 */
static BOOL AIScript_PopCursor(BattleSystem *battleSys, BattleContext *battleCtx)
{
    if (AI_CONTEXT.scriptStackSize) {
        AI_CONTEXT.scriptStackSize--;
        battleCtx->aiScriptCursor = AI_CONTEXT.scriptStackPointer[AI_CONTEXT.scriptStackSize];
        return TRUE;
    }

    return FALSE;
}

/**
 * @brief Record the last move used by an active battler, if it is not
 * already known.
 *
 * @param battleSys
 * @param battleCtx
 */
static void TrainerAI_RecordLastMove(BattleSystem *battleSys, BattleContext *battleCtx)
{
    for (int i = 0; i < LEARNED_MOVES_MAX; i++) {
        if (AI_CONTEXT.battlerMoves[AI_CONTEXT.defender][i] == battleCtx->movePrevByBattler[AI_CONTEXT.defender]) {
            break;
        }

        if (AI_CONTEXT.battlerMoves[AI_CONTEXT.defender][i] == MOVE_NONE) {
            AI_CONTEXT.battlerMoves[AI_CONTEXT.defender][i] = battleCtx->movePrevByBattler[AI_CONTEXT.defender];
            break;
        }
    }
}

/**
 * @brief Read a word from the AI script at the current cursor position,
 * then increment the cursor.
 *
 * @param battleCtx
 * @return Current word for the AI script under the cursor.
 */
static int AIScript_Read(BattleContext *battleCtx)
{
    int word = battleCtx->aiScriptTemp[battleCtx->aiScriptCursor];
    battleCtx->aiScriptCursor++;

    return word;
}

/**
 * @brief Read a word from the AI script at the current cursor position
 * offset by a specified value, then increment the cursor.
 *
 * @param battleCtx
 * @return Current word for the AI script under the cursor + an offset.
 */
static int AIScript_ReadOffset(BattleContext *battleCtx, int ofs)
{
    return battleCtx->aiScriptTemp[battleCtx->aiScriptCursor + ofs];
}

/**
 * @brief Increment the cursor for the AI script by a fixed amount.
 *
 * @param battleCtx
 * @param i         Amount by which to increment the script cursor.
 */
static void AIScript_Iter(BattleContext *battleCtx, int i)
{
    battleCtx->aiScriptCursor += i;
}

/**
 * @brief Determine the true battler ID for an input battler value as
 * recognized by the AI script.
 *
 * @param battleCtx
 * @param inBattler The input battler value.
 * @return True battler ID for the input battler value.
 */
static u8 AIScript_Battler(BattleContext *battleCtx, u8 inBattler)
{
    // the order of this switch statement must be maintained to match
    switch (inBattler) {
    case AI_BATTLER_ATTACKER:
        return AI_CONTEXT.attacker;

    case AI_BATTLER_DEFENDER:
    default:
        return AI_CONTEXT.defender;

    case AI_BATTLER_ATTACKER_PARTNER:
        return AI_CONTEXT.attacker ^ 2;

    case AI_BATTLER_DEFENDER_PARTNER:
        return AI_CONTEXT.defender ^ 2;
    }
}

/**
 * @brief Calculate the damage that will be done by all of an attacker's moves.
 *
 * @param battleSys
 * @param battleCtx
 * @param attacker      The attacker's battler ID.
 * @param moves         The attacker's moveset.
 * @param damageVals    Out-param for all damage values as computed by the routine.
 * @param heldItem      The attacker's held item.
 * @param ivs           The attacker's IVs. Used for calculating Hidden Power params.
 * @param ability       The attacker's ability.
 * @param embargoTurns  Number of turns that the attacker is still under Embargo.
 * @param varyDamage    If TRUE, apply random damage variance to each calculation.
 * @return              The highest damage value among all considered moves.
 */
static s32 TrainerAI_CalcAllDamage(BattleSystem *battleSys, BattleContext *battleCtx, int attacker, u16 *moves, s32 *damageVals, u16 heldItem, u8 *ivs, int ability, int embargoTurns, BOOL varyDamage)
{
    int i, noCalcIdx, altPowerIdx;
    s32 maxDamage;
    u8 damageRoll;

    maxDamage = 0;

    // Step 1: Compute the true damage of a given move.
    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        noCalcIdx = 0;
        while (sNoDamageCalcMoveEffects[noCalcIdx] != 0xFFFF) {
            if (MOVE_DATA(moves[i]).effect == sNoDamageCalcMoveEffects[noCalcIdx]) {
                break;
            }

            noCalcIdx++;
        }

        altPowerIdx = 0;
        while (sAltPowerMoveEffects[altPowerIdx] != 0xFFFF) {
            if (MOVE_DATA(moves[i]).effect == sAltPowerMoveEffects[altPowerIdx]) {
                break;
            }

            altPowerIdx++;
        }

        if (sAltPowerMoveEffects[altPowerIdx] != 0xFFFF
            || (moves[i] != MOVE_NONE && sNoDamageCalcMoveEffects[noCalcIdx] == 0xFFFF && MOVE_DATA(moves[i]).power > 1)) {
            if (varyDamage == TRUE) {
                damageRoll = AI_CONTEXT.moveDamageRolls[i];
            } else {
                damageRoll = 100;
            }

            damageVals[i] = TrainerAI_CalcDamage(battleSys, battleCtx, moves[i], heldItem, ivs, attacker, ability, embargoTurns, damageRoll);
        } else {
            damageVals[i] = 0;
        }
    }

    // Step 2: Determine the maximum-damage of all moves.
    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        if (maxDamage < damageVals[i]) {
            maxDamage = damageVals[i];
        }
    }

    return maxDamage;
}

#include "data/battle/weight_to_power.h"
#include "data/battle/pp_scaled_power.h"

/**
 * @brief Damage calculation routine visible to the AI.
 *
 * @param battleSys
 * @param battleCtx
 * @param move          The move being used
 * @param heldItem      The attacker's held item.
 * @param ivs           The attacker's IVs. Used for Hidden Power calculation.
 * @param attacker      The attacker's ID.
 * @param ability       The attacker's ability.
 * @param embargoTurns  Number of turns that the attacker is still under Embargo.
 * @param variance      Variance factor applied to the damage value. This is presumed
 *                      to be a value in the range [85..100].
 * @return Calculated damage value.
 */
static s32 TrainerAI_CalcDamage(BattleSystem *battleSys, BattleContext *battleCtx, u16 move, u16 heldItem, u8 *ivs, int attacker, int ability, int embargoTurns, u8 variance)
{
    // must declare C89-style to match
    int defendingSide;
    int power;
    int type;
    int typeTmp;
    u32 effectivenessFlags;
    s32 damage;

    defendingSide = BattleSystem_GetBattlerSide(battleSys, AI_CONTEXT.defender);
    damage = 0;
    power = 0;
    type = 0;
    effectivenessFlags = 0;

    // heldItem arrives as the raw field rather than through Battler_HeldItem, which is what
    // suppresses items under Klutz and Embargo everywhere else.
    if (ability == ABILITY_KLUTZ || embargoTurns != 0) {
        heldItem = ITEM_NONE;
    }

    switch (move) {
    case MOVE_NATURAL_GIFT:
        power = BattleSystem_GetItemData(battleCtx, heldItem, ITEM_PARAM_NATURAL_GIFT_POWER);

        if (power == 0) {
            return 0;
        }

        type = BattleSystem_GetItemData(battleCtx, heldItem, ITEM_PARAM_NATURAL_GIFT_TYPE);
        break;

    case MOVE_JUDGMENT:
        power = 0;

        switch (BattleSystem_GetItemData(battleCtx, heldItem, ITEM_PARAM_HOLD_EFFECT)) {
        case HOLD_EFFECT_ARCEUS_FIGHTING:
            type = TYPE_FIGHTING;
            break;

        case HOLD_EFFECT_ARCEUS_FLYING:
            type = TYPE_FLYING;
            break;

        case HOLD_EFFECT_ARCEUS_POISON:
            type = TYPE_POISON;
            break;

        case HOLD_EFFECT_ARCEUS_GROUND:
            type = TYPE_GROUND;
            break;

        case HOLD_EFFECT_ARCEUS_ROCK:
            type = TYPE_ROCK;
            break;

        case HOLD_EFFECT_ARCEUS_BUG:
            type = TYPE_BUG;
            break;

        case HOLD_EFFECT_ARCEUS_GHOST:
            type = TYPE_GHOST;
            break;

        case HOLD_EFFECT_ARCEUS_STEEL:
            type = TYPE_STEEL;
            break;

        case HOLD_EFFECT_ARCEUS_FIRE:
            type = TYPE_FIRE;
            break;

        case HOLD_EFFECT_ARCEUS_WATER:
            type = TYPE_WATER;
            break;

        case HOLD_EFFECT_ARCEUS_GRASS:
            type = TYPE_GRASS;
            break;

        case HOLD_EFFECT_ARCEUS_ELECTRIC:
            type = TYPE_ELECTRIC;
            break;

        case HOLD_EFFECT_ARCEUS_PSYCHIC:
            type = TYPE_PSYCHIC;
            break;

        case HOLD_EFFECT_ARCEUS_ICE:
            type = TYPE_ICE;
            break;

        case HOLD_EFFECT_ARCEUS_DRAGON:
            type = TYPE_DRAGON;
            break;

        case HOLD_EFFECT_ARCEUS_DARK:
            type = TYPE_DARK;
            break;

        case HOLD_EFFECT_ARCEUS_FAIRY:
            type = TYPE_FAIRY;
            break;

        default:
            type = TYPE_NORMAL;
            break;
        }

        break;

    case MOVE_HIDDEN_POWER:
        type = ((ivs[STAT_HP] & 1) >> 0)
            | ((ivs[STAT_ATTACK] & 1) << 1)
            | ((ivs[STAT_DEFENSE] & 1) << 2)
            | ((ivs[STAT_SPEED] & 1) << 3)
            | ((ivs[STAT_SPECIAL_ATTACK] & 1) << 4)
            | ((ivs[STAT_SPECIAL_DEFENSE] & 1) << 5);

        type = (type * 15 / 63) + 1;

        if (type >= TYPE_FAIRY) {
            type++;
        }
        break;

    case MOVE_GYRO_BALL:
        if (battleCtx->monSpeedValues[attacker] == 0) {
            power = 1;
            type = TYPE_NORMAL;
            break;
        }

        power = 1 + 25 * battleCtx->monSpeedValues[AI_CONTEXT.defender] / battleCtx->monSpeedValues[attacker];

        if (power > 150) {
            power = 150;
        }

        type = TYPE_NORMAL; // default to the base move type
        break;

    case MOVE_DRAGON_RAGE:
        damage = 40;
        break;

    case MOVE_SEISMIC_TOSS:
    case MOVE_NIGHT_SHADE:
        damage = battleCtx->battleMons[attacker].level;
        break;

    case MOVE_PSYWAVE:
        // thinking E(X) is roughly half level here
        damage = battleCtx->battleMons[attacker].level / 2;
        break;

    case MOVE_RETURN:
        power = battleCtx->battleMons[attacker].friendship * 10 / 25;
        type = TYPE_NORMAL;
        break;

    case MOVE_MAGNITUDE:
        // Default Magnitude to BP 50
        power = 50;
        type = TYPE_NORMAL;
        break;

    case MOVE_SONIC_BOOM:
        damage = 20;
        break;

    case MOVE_SUPER_FANG:
        damage = battleCtx->battleMons[AI_CONTEXT.defender].curHP / 2;

        if (damage == 0) {
            damage = 1;
        }

        break;

    case MOVE_LOW_KICK:
    case MOVE_GRASS_KNOT: {
        int i;

        int monWeight = battleCtx->battleMons[AI_CONTEXT.defender].weight;

        if (Battler_IgnorableAbility(battleCtx, attacker, AI_CONTEXT.defender, ABILITY_LIGHT_METAL)) {
            monWeight /= 2;
        }

        for (i = 0; sWeightToPower[i][0] != 0xFFFF; i++) {
            if (sWeightToPower[i][0] >= monWeight) {
                break;
            }
        }

        if (sWeightToPower[i][0] != 0xFFFF) {
            power = sWeightToPower[i][1];
        } else {
            power = 120;
        }

        break;
    }

    case MOVE_VENOSHOCK:
        if (battleCtx->battleMons[AI_CONTEXT.defender].status & (MON_CONDITION_POISON | MON_CONDITION_TOXIC)) {
            power = MOVE_DATA(move).power * 2;
        }

        break;

    case MOVE_HEX:
        if (battleCtx->battleMons[AI_CONTEXT.defender].status & MON_CONDITION_ANY) {
            power = MOVE_DATA(move).power * 2;
        }

        break;

    // The following moves have their real power computed by a battle-script command at
    // execution time, so scoring never sees it. Mirror each of those commands here.
    case MOVE_DREAM_EATER:
        if ((battleCtx->battleMons[AI_CONTEXT.defender].status & MON_CONDITION_SLEEP) == FALSE) {
            return 0;
        }

        break;

    case MOVE_SNORE:
        if ((battleCtx->battleMons[attacker].status & MON_CONDITION_SLEEP) == FALSE) {
            return 0;
        }

        break;

    case MOVE_SPIT_UP:
        if (battleCtx->battleMons[attacker].moveEffectsData.stockpileCount == 0) {
            return 0;
        }

        power = battleCtx->battleMons[attacker].moveEffectsData.stockpileCount * 100;
        break;

    case MOVE_ERUPTION:
    case MOVE_WATER_SPOUT:
        power = MOVE_DATA(move).power * battleCtx->battleMons[attacker].curHP / battleCtx->battleMons[attacker].maxHP;

        if (power < 1) {
            power = 1;
        }

        break;

    case MOVE_FACADE:
        if (battleCtx->battleMons[attacker].status & MON_CONDITION_FACADE_BOOST) {
            power = MOVE_DATA(move).power * 2;
        }

        break;

    case MOVE_BRINE:
        if (battleCtx->battleMons[AI_CONTEXT.defender].curHP <= battleCtx->battleMons[AI_CONTEXT.defender].maxHP / 2) {
            power = MOVE_DATA(move).power * 2;
        }

        break;

    case MOVE_PAYBACK:
        if (BattleSystem_CompareBattlerSpeed(battleSys, battleCtx, attacker, AI_CONTEXT.defender, TRUE) == COMPARE_SPEED_SLOWER) {
            power = MOVE_DATA(move).power * 2;
        }

        break;

    case MOVE_STORED_POWER:
        power = 20 + 20 * TrainerAI_SumRaisedStatStages(battleCtx, attacker, BATTLE_STAT_ATTACK);

        if (power > 860) {
            power = 860;
        }

        break;

    case MOVE_PUNISHMENT:
        power = 60 + 20 * TrainerAI_SumRaisedStatStages(battleCtx, AI_CONTEXT.defender, BATTLE_STAT_HP);

        if (power > 200) {
            power = 200;
        }

        break;

    case MOVE_WEATHER_BALL:
        power = MOVE_DATA(move).power;

        if (Battler_Ability(battleCtx, attacker) == ABILITY_MEGA_SOL) {
            power *= 2;
            type = TYPE_FIRE;
        } else if (NO_CLOUD_NINE && (battleCtx->fieldConditionsMask & FIELD_CONDITION_WEATHER)) {
            power *= 2;

            if (WEATHER_IS_RAIN) {
                type = TYPE_WATER;
            } else if (WEATHER_IS_SAND) {
                type = TYPE_ROCK;
            } else if (WEATHER_IS_SUN) {
                type = TYPE_FIRE;
            } else if (WEATHER_IS_HAIL) {
                type = TYPE_ICE;
            }
        }

        break;

    case MOVE_FURY_CUTTER:
        power = MOVE_DATA(move).power;

        for (int i = 0; i < battleCtx->battleMons[attacker].moveEffectsData.furyCutterCount && i < 4; i++) {
            power *= 2;
        }

        break;

    case MOVE_ROLLOUT:
    case MOVE_ICE_BALL: {
        int rolloutTurns = 0;

        if (battleCtx->battleMons[attacker].statusVolatile & VOLATILE_CONDITION_MOVE_LOCKED) {
            rolloutTurns = 5 - battleCtx->battleMons[attacker].moveEffectsData.rolloutCount;
        }

        power = MOVE_DATA(move).power;

        for (int i = 0; i < rolloutTurns; i++) {
            power *= 2;
        }

        if (battleCtx->battleMons[attacker].statusVolatile & VOLATILE_CONDITION_DEFENSE_CURL) {
            power *= 2;
        }

        break;
    }

    case MOVE_FLAIL:
    case MOVE_REVERSAL:
        power = BattleAI_CalcFlailPower(battleCtx->battleMons[attacker].curHP, battleCtx->battleMons[attacker].maxHP);
        break;

    case MOVE_TRUMP_CARD: {
        int slot = Battler_SlotForMove(&battleCtx->battleMons[attacker], move);
        int ppCur = slot < LEARNED_MOVES_MAX ? battleCtx->battleMons[attacker].ppCur[slot] : 0;
        int ppCost = Battler_Ability(battleCtx, AI_CONTEXT.defender) == ABILITY_PRESSURE ? 2 : 1;

        ppCur = ppCur > ppCost ? ppCur - ppCost : 0;

        if (ppCur > 4) {
            ppCur = 4;
        }

        power = sCurrentPPScaledPower[ppCur];
        break;
    }

    case MOVE_HEAVY_SLAM: {
        int atkWeight = battleCtx->battleMons[attacker].weight;
        int defWeight = battleCtx->battleMons[AI_CONTEXT.defender].weight;

        if (Battler_Ability(battleCtx, attacker) == ABILITY_LIGHT_METAL) {
            atkWeight /= 2;
        }

        if (Battler_IgnorableAbility(battleCtx, attacker, AI_CONTEXT.defender, ABILITY_LIGHT_METAL)) {
            defWeight /= 2;
        }

        if (atkWeight >= defWeight * 5) {
            power = 120;
        } else if (atkWeight >= defWeight * 4) {
            power = 100;
        } else if (atkWeight >= defWeight * 3) {
            power = 80;
        } else if (atkWeight >= defWeight * 2) {
            power = 60;
        } else {
            power = 40;
        }

        break;
    }

    default:
        // Move has no special calculation logic; default to the basic calc
        power = 0;
        type = TYPE_NORMAL;
        break;
    }

    if (damage == 0) {
        int criticalMul = 1;

        if (BattleSystem_MoveAlwaysCrits(battleSys, battleCtx, attacker, AI_CONTEXT.defender, move, ability, heldItem)) {
            criticalMul = ability == ABILITY_SNIPER ? 3 : 2;
        }

        damage = BattleSystem_CalcMoveDamage(battleSys,
            battleCtx,
            move,
            battleCtx->sideConditionsMask[defendingSide],
            battleCtx->fieldConditionsMask,
            power,
            type,
            attacker,
            AI_CONTEXT.defender,
            criticalMul);

        if (criticalMul == 2) {
            damage = damage * 3 / 2;
        } else if (criticalMul == 3) {
            damage = damage * 9 / 4;
        }
    } else {
        battleCtx->battleStatusMask |= SYSCTL_IGNORE_TYPE_CHECKS;
    }

    damage = BattleSystem_ApplyTypeChart(battleSys,
        battleCtx,
        move,
        type,
        attacker,
        AI_CONTEXT.defender,
        damage,
        &effectivenessFlags);
    battleCtx->battleStatusMask &= ~SYSCTL_IGNORE_TYPE_CHECKS;

    if (effectivenessFlags & MOVE_STATUS_IMMUNE) {
        damage = 0;
    } else {
        damage = BattleSystem_Divide(damage * variance, 100);
        damage = BattleSystem_Divide(damage * TrainerAI_HitCountMultiplier(battleSys, battleCtx, move, attacker, ability, heldItem), 100);
    }

    return damage;
}

/**
 * @brief Work out how many times a move is expected to connect, as a percentage multiplier to
 * apply to a single hit's damage.
 *
 * All hits are assumed to land, matching the AI's existing habit of ignoring accuracy. The
 * multi-hit values mirror the switch AI's own damage routine so the two agree.
 *
 * @param battleSys
 * @param battleCtx
 * @param move
 * @param attacker  The attacker's battler ID.
 * @param ability   The attacker's ability.
 * @param heldItem  The attacker's held item.
 * @return Percentage multiplier, where 100 means a single hit.
 */
static int TrainerAI_HitCountMultiplier(BattleSystem *battleSys, BattleContext *battleCtx, u16 move, int attacker, int ability, u16 heldItem)
{
    switch (MOVE_DATA(move).effect) {
    case BATTLE_EFFECT_HIT_TWICE:
    case BATTLE_EFFECT_POISON_MULTI_HIT:
        return 200;

    case BATTLE_EFFECT_HIT_THREE_TIMES:
        return 600;

    case BATTLE_EFFECT_MULTI_HIT:
        if (ability == ABILITY_SKILL_LINK) {
            return 500;
        }

        if (BattleSystem_GetItemData(battleCtx, heldItem, ITEM_PARAM_HOLD_EFFECT) == HOLD_EFFECT_LOADED_DICE) {
            return 400;
        }

        return 300;
    }

    if (ability == ABILITY_PARENTAL_BOND
        && BattleSystem_ParentalBondAppliesToMove(battleCtx, move)
        && BattleSystem_MoveTargetCount(battleSys, battleCtx, attacker, move) == 1) {
        return 125;
    }

    return 100;
}

/**
 * @brief Sum a battler's positive stat stages, as used by Stored Power and Punishment.
 *
 * @param battleCtx
 * @param battler
 * @param firstStat The first stat to count from. Stored Power counts from Attack; Punishment
 *                  counts from HP. Both are mirrored from their battle-script commands.
 * @return The total number of stages the battler is boosted by.
 */
static int TrainerAI_SumRaisedStatStages(BattleContext *battleCtx, int battler, int firstStat)
{
    int sumBoosts = 0;

    for (int i = firstStat; i < BATTLE_STAT_MAX; i++) {
        if (battleCtx->battleMons[battler].statBoosts[i] > DEFAULT_STAT_STAGE) {
            sumBoosts += battleCtx->battleMons[battler].statBoosts[i] - DEFAULT_STAT_STAGE;
        }
    }

    return sumBoosts;
}

/**
 * @brief Compute the type of a move. Variable-type moves will have their type
 * computed according to the usual routines (i.e., Natural Gift, Judgment,
 * Hidden Power, and Weather Ball). Moves without a variable typing will be
 * returned as TYPE_NORMAL.
 *
 * @param battleSys
 * @param battleCtx
 * @param battler   The battler using the move.
 * @param move      The move being used.
 * @return The type of the move.
 */
static int TrainerAI_MoveType(BattleSystem *battleSys, BattleContext *battleCtx, int battler, int move)
{
    int result;

    switch (move) {
    case MOVE_NATURAL_GIFT:
        result = Battler_NaturalGiftType(battleCtx, battler);
        break;

    case MOVE_JUDGMENT:
        switch (Battler_HeldItemEffect(battleCtx, battler)) {
        case HOLD_EFFECT_ARCEUS_FIGHTING:
            result = TYPE_FIGHTING;
            break;

        case HOLD_EFFECT_ARCEUS_FLYING:
            result = TYPE_FLYING;
            break;

        case HOLD_EFFECT_ARCEUS_POISON:
            result = TYPE_POISON;
            break;

        case HOLD_EFFECT_ARCEUS_GROUND:
            result = TYPE_GROUND;
            break;

        case HOLD_EFFECT_ARCEUS_ROCK:
            result = TYPE_ROCK;
            break;

        case HOLD_EFFECT_ARCEUS_BUG:
            result = TYPE_BUG;
            break;

        case HOLD_EFFECT_ARCEUS_GHOST:
            result = TYPE_GHOST;
            break;

        case HOLD_EFFECT_ARCEUS_STEEL:
            result = TYPE_STEEL;
            break;

        case HOLD_EFFECT_ARCEUS_FIRE:
            result = TYPE_FIRE;
            break;

        case HOLD_EFFECT_ARCEUS_WATER:
            result = TYPE_WATER;
            break;

        case HOLD_EFFECT_ARCEUS_GRASS:
            result = TYPE_GRASS;
            break;

        case HOLD_EFFECT_ARCEUS_ELECTRIC:
            result = TYPE_ELECTRIC;
            break;

        case HOLD_EFFECT_ARCEUS_PSYCHIC:
            result = TYPE_PSYCHIC;
            break;

        case HOLD_EFFECT_ARCEUS_ICE:
            result = TYPE_ICE;
            break;

        case HOLD_EFFECT_ARCEUS_DRAGON:
            result = TYPE_DRAGON;
            break;

        case HOLD_EFFECT_ARCEUS_DARK:
            result = TYPE_DARK;
            break;

        case HOLD_EFFECT_ARCEUS_FAIRY:
            result = TYPE_FAIRY;
            break;

        default:
            result = TYPE_NORMAL;
            break;
        }
        break;

    case MOVE_HIDDEN_POWER:
        result = ((battleCtx->battleMons[battler].hpIV & 1) >> 0)
            | ((battleCtx->battleMons[battler].attackIV & 1) << 1)
            | ((battleCtx->battleMons[battler].defenseIV & 1) << 2)
            | ((battleCtx->battleMons[battler].speedIV & 1) << 3)
            | ((battleCtx->battleMons[battler].spAttackIV & 1) << 4)
            | ((battleCtx->battleMons[battler].spDefenseIV & 1) << 5);
        result = (result * 15 / 63) + 1;

        if (result >= TYPE_FAIRY) {
            result++;
        }
        break;

    case MOVE_WEATHER_BALL:
        result = TYPE_NORMAL;

        if (Battler_Ability(battleCtx, battler) == ABILITY_MEGA_SOL) {
            result = TYPE_FIRE;
        } else if (NO_CLOUD_NINE && (battleCtx->fieldConditionsMask & FIELD_CONDITION_WEATHER)) {
            if (WEATHER_IS_RAIN) {
                result = TYPE_WATER;
            }

            if (WEATHER_IS_SAND) {
                result = TYPE_ROCK;
            }

            if (WEATHER_IS_SUN) {
                result = TYPE_FIRE;
            }

            if (WEATHER_IS_HAIL) {
                result = TYPE_ICE;
            }
        }
        break;

    default:
        result = TYPE_NORMAL;
        break;
    }

    return result;
}

/**
 * @brief Check if Perish Song is active on a battler and the battler should
 * faint at the end of the turn. If so, treat the next switch as post-KO switch
 * AI.
 *
 * This routine is bugged; it functionally does nothing. The Perish Song turn
 * count decrements at the end of the turn, so the AI never sees that it WILL
 * die to Perish Song.
 *
 * @param battleCtx
 * @param battler   The AI's battler.
 * @return TRUE if the AI has a switch to make, FALSE otherwise.
 */
static BOOL AI_PerishSongKO(BattleContext *battleCtx, int battler)
{
    if ((battleCtx->battleMons[battler].moveEffectsMask & MOVE_EFFECT_PERISH_SONG)
        && battleCtx->battleMons[battler].moveEffectsData.perishSongTurns == 0) {
        battleCtx->aiSwitchedPartySlot[battler] = 6;
        return TRUE;
    }

    return FALSE;
}

/**
 * @brief Check if an AI's battler cannot damage the opponent's Pokemon due to
 * Wonder Guard. If so, switch to the best-scoring party member which can break
 * through it, 66% of the time.
 *
 * This routine does NOT apply to double-battles.
 *
 * @param battleSys
 * @param battleCtx
 * @param battler   The AI's battler.
 * @return TRUE if the AI has a switch to make, FALSE otherwise.
 */
static BOOL AI_CannotDamageWonderGuard(BattleSystem *battleSys, BattleContext *battleCtx, int battler)
{
    int i;
    int slot;
    u16 move;
    int moveType;
    u32 effectiveness;

    if (BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_DOUBLES) {
        return FALSE;
    }

    if (Battler_Ability(battleCtx, BATTLER_OPP(battler)) == ABILITY_WONDER_GUARD) {
        // Check if we have a super-effective move against the opponent
        for (i = 0; i < LEARNED_MOVES_MAX; i++) {
            move = battleCtx->battleMons[battler].moves[i];

            if (move) {
                moveType = TrainerAI_MoveType(battleSys, battleCtx, battler, move);

                effectiveness = 0;
                BattleSystem_ApplyTypeChart(battleSys, battleCtx, move, moveType, battler, BATTLER_OPP(battler), 0, &effectiveness);

                if (effectiveness & MOVE_STATUS_SUPER_EFFECTIVE) {
                    return FALSE;
                }
            }
        }

        // Otherwise send in whichever party member scores highest against the Wonder
        // Guard mon while still being able to break it. One roll for the decision,
        // not one per candidate.
        slot = BattleAI_PostKOSwitchInSuperEffective(battleSys, battler);

        if (slot < MAX_PARTY_SIZE && BattleSystem_RandNext(battleSys) % 3 < 2) {
            battleCtx->aiSwitchedPartySlot[battler] = slot;
            return TRUE;
        }
    }

    return FALSE;
}

/**
 * @brief Check whether a party Pokemon holds a damaging move of the wanted
 * effectiveness against an opposing battler.
 *
 * @param battleSys
 * @param battleCtx
 * @param mon
 * @param defender              The opposing battler. A fainted slot never qualifies.
 * @param wantSuperEffective    TRUE to look for a super-effective move, FALSE for a
 *                              normally-effective one.
 * @return TRUE if such a move exists.
 */
static BOOL AI_PartyMonThreatensSlot(BattleSystem *battleSys, BattleContext *battleCtx, Pokemon *mon, int defender, BOOL wantSuperEffective)
{
    int j;
    u16 move;
    int moveType;
    u32 effectiveness;

    if (battleCtx->battleMons[defender].curHP == 0) {
        return FALSE;
    }

    for (j = 0; j < LEARNED_MOVES_MAX; j++) {
        move = Pokemon_GetValue(mon, MON_DATA_MOVE1 + j, NULL);

        if (move && MOVE_DATA(move).power) {
            moveType = Move_CalcVariableType(battleSys, battleCtx, mon, move);

            effectiveness = 0;
            BattleSystem_CalcEffectiveness(battleCtx,
                move,
                moveType,
                Pokemon_GetValue(mon, MON_DATA_ABILITY, NULL),
                Battler_Ability(battleCtx, defender),
                Battler_HeldItemEffect(battleCtx, defender),
                BattleMon_Get(battleCtx, defender, BATTLEMON_TYPE_1, NULL),
                BattleMon_Get(battleCtx, defender, BATTLEMON_TYPE_2, NULL),
                &effectiveness);

            if (wantSuperEffective) {
                if (effectiveness & MOVE_STATUS_SUPER_EFFECTIVE) {
                    return TRUE;
                }
            } else if (effectiveness == 0) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

/**
 * @brief Check if an AI's battler only has moves which do not deal damage to either
 * of the opponent's Pokemon.
 *
 * Switches 50% of the time to a bench Pokemon which can damage an opponent,
 * preferring one with a super-effective move. One roll per Pokemon.
 *
 * @param battleSys
 * @param battleCtx
 * @param battler   The AI's battler.
 * @return TRUE if the AI has a switch to make, FALSE otherwise.
 */
static BOOL AI_OnlyIneffectiveMoves(BattleSystem *battleSys, BattleContext *battleCtx, int battler)
{
    int i;
    int pass;
    u8 defender1, defender2;
    u8 aiSlot1, aiSlot2;
    u16 move;
    int type;
    u32 effectiveness;
    int start, end;
    int numMoves;
    Pokemon *mon;

    // "Player" consts here refer to the AI's perspective.
    if (BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_DOUBLES) {
        defender1 = BATTLER_PLAYER_1;
        defender2 = BATTLER_PLAYER_2;
    } else {
        defender1 = BATTLER_PLAYER_1;
        defender2 = BATTLER_PLAYER_1;
    }

    // Check all of this mon's attacking moves for immunities. If any of our moves can deal damage to
    // either of the opponents' battlers, do not switch.
    numMoves = 0;
    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        move = battleCtx->battleMons[battler].moves[i];
        type = TrainerAI_MoveType(battleSys, battleCtx, battler, move);

        if (move && MOVE_DATA(move).power) {
            numMoves++;

            effectiveness = 0;
            if (battleCtx->battleMons[defender1].curHP) {
                BattleSystem_ApplyTypeChart(battleSys, battleCtx, move, type, battler, defender1, 0, &effectiveness);
            }

            if ((effectiveness & MOVE_STATUS_INEFFECTIVE) == FALSE) {
                return FALSE;
            }

            effectiveness = 0;
            if (battleCtx->battleMons[defender2].curHP) {
                BattleSystem_ApplyTypeChart(battleSys, battleCtx, move, type, battler, defender2, 0, &effectiveness);
            }

            if ((effectiveness & MOVE_STATUS_INEFFECTIVE) == FALSE) {
                return FALSE;
            }
        }
    }

    // If we have more than 1 attacking move, do not switch.
    if (numMoves < 2) {
        return FALSE;
    }

    aiSlot1 = battler;
    if ((BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_TAG) || (BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_2vs2)) {
        aiSlot2 = aiSlot1;
    } else {
        aiSlot2 = BattleSystem_GetPartner(battleSys, battler);
    }

    start = 0;
    end = BattleSystem_GetPartyCount(battleSys, battler);

    // The first pass takes a bench Pokemon with a super-effective move against either
    // opponent; the second settles for a normally-effective one. Either way it is a
    // single 50% roll per Pokemon.
    for (pass = 0; pass < 2; pass++) {
        for (i = start; i < end; i++) {
            mon = BattleSystem_GetPartyPokemon(battleSys, battler, i);

            if (Pokemon_GetValue(mon, MON_DATA_HP, NULL) != 0
                && Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_NONE
                && Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_EGG
                && i != battleCtx->selectedPartySlot[aiSlot1]
                && i != battleCtx->selectedPartySlot[aiSlot2]
                && i != battleCtx->aiSwitchedPartySlot[aiSlot1]
                && i != battleCtx->aiSwitchedPartySlot[aiSlot2]
                && (AI_PartyMonThreatensSlot(battleSys, battleCtx, mon, defender1, pass == 0)
                    || AI_PartyMonThreatensSlot(battleSys, battleCtx, mon, defender2, pass == 0))
                && (BattleSystem_RandNext(battleSys) & 1)) {
                battleCtx->aiSwitchedPartySlot[battler] = i;
                return TRUE;
            }
        }
    }

    return FALSE;
}

/**
 * @brief Check if an AI's battler has a super-effective move against either of the
 * opponent's Pokemon.
 *
 * @param battleSys
 * @param battleCtx
 * @param battler   The AI's battler.
 * @param flag      If TRUE, will always return TRUE if the AI's battler has a super-
 *                  effective move. If FALSE, returns TRUE 90% of the time for either
 *                  target against which the battler has a super-effective move.
 * @return TRUE if the AI's battler has a super-effective move.
 */
static BOOL AI_HasSuperEffectiveMove(BattleSystem *battleSys, BattleContext *battleCtx, int battler, BOOL flag)
{
    int i;
    u32 effectiveness;
    u8 defender;
    u8 oppositeSlot;
    u16 move;
    int type;

    // Look at the slot directly across from us on the opposite side. i.e.,
    // AI slot 1 looks at player slot 1, AI slot 2 looks at player slot 2
    oppositeSlot = BattleSystem_GetBattlerType(battleSys, battler) ^ 1;
    defender = BattleSystem_GetBattlerOfType(battleSys, oppositeSlot);

    if ((battleCtx->battlersSwitchingMask & FlagIndex(defender)) == FALSE) {
        // Check if the player's battler is weak to any of our moves
        for (i = 0; i < LEARNED_MOVES_MAX; i++) {
            move = battleCtx->battleMons[battler].moves[i];
            type = TrainerAI_MoveType(battleSys, battleCtx, battler, move);

            if (move) {
                effectiveness = 0;
                BattleSystem_ApplyTypeChart(battleSys, battleCtx, move, type, battler, defender, 0, &effectiveness);

                // If the defending mon is weak to our move, return TRUE 90-100% of the time.
                if (effectiveness & MOVE_STATUS_SUPER_EFFECTIVE) {
                    if (flag) {
                        return TRUE;
                    } else if (BattleSystem_RandNext(battleSys) % 10 != 0) {
                        return TRUE;
                    }
                }
            }
        }
    }

    // Check the defender's partner the same way as above.
    if ((BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_DOUBLES) == FALSE) {
        return FALSE;
    }
    defender = BattleSystem_GetPartner(battleSys, defender);

    if ((battleCtx->battlersSwitchingMask & FlagIndex(defender)) == FALSE) {
        for (i = 0; i < LEARNED_MOVES_MAX; i++) {
            move = battleCtx->battleMons[battler].moves[i];
            type = TrainerAI_MoveType(battleSys, battleCtx, battler, move);

            if (move) {
                effectiveness = 0;
                BattleSystem_ApplyTypeChart(battleSys, battleCtx, move, type, battler, defender, 0, &effectiveness);

                // If the defending mon is weak to our move, return TRUE 90-100% of the time.
                if (effectiveness & MOVE_STATUS_SUPER_EFFECTIVE) {
                    if (flag) {
                        return TRUE;
                    } else if (BattleSystem_RandNext(battleSys) % 10 != 0) {
                        return TRUE;
                    }
                }
            }
        }
    }

    return FALSE;
}

/**
 * @brief Check whether an ability makes its holder immune to the given move.
 *
 * Covers the damage-absorbing abilities plus Levitate, which is not an absorb but
 * reads identically from the switch AI's point of view.
 *
 * @param ability
 * @param move
 * @param moveType  The move's resolved type, not its base type.
 * @return TRUE if the ability absorbs the move.
 */
static BOOL AI_AbilityAbsorbsMove(int ability, u16 move, int moveType)
{
    switch (ability) {
    case ABILITY_VOLT_ABSORB:
    case ABILITY_LIGHTNING_ROD:
    case ABILITY_MOTOR_DRIVE:
        return moveType == TYPE_ELECTRIC;

    case ABILITY_WATER_ABSORB:
    case ABILITY_STORM_DRAIN:
    case ABILITY_DRY_SKIN:
        return moveType == TYPE_WATER;

    case ABILITY_FLASH_FIRE:
        return moveType == TYPE_FIRE;

    case ABILITY_SAP_SIPPER:
        return moveType == TYPE_GRASS;

    case ABILITY_EARTH_EATER:
    case ABILITY_LEVITATE:
        return moveType == TYPE_GROUND;

    case ABILITY_SOUNDPROOF:
        return BattleSystem_IsSoundMove(move);

    case ABILITY_WIND_RIDER:
        return BattleSystem_IsWindMove(move);
    }

    return FALSE;
}

/**
 * @brief Check if the AI's party has a Pokemon on the bench which is immune to the
 * move that last hit it and can threaten the attacker back.
 *
 * Switches 50% of the time to a bench Pokemon whose ability absorbs the move and
 * which also holds a super-effective move against the attacker. Mold Breaker on the
 * attacker disables the check entirely, as it ignores every ability involved.
 *
 * @param battleSys
 * @param battleCtx
 * @param battler   The AI's battler.
 * @return BOOL
 */
static BOOL AI_HasAbsorbAbilityInParty(BattleSystem *battleSys, BattleContext *battleCtx, int battler)
{
    int i, j;
    u8 aiSlot1, aiSlot2;
    u16 lastMove;
    int lastMoveType;
    int attacker;
    u16 move;
    int moveType;
    u32 effectiveness;
    BOOL hasSuperEffective;
    int start, end;
    Pokemon *mon;

    // If we already threaten the mon in front of us, only consider the pivot 1/3
    // of the time. This check sits above the stay-in veto in the cascade, so it is
    // the only thing holding a winning matchup on the field.
    if (AI_HasSuperEffectiveMove(battleSys, battleCtx, battler, TRUE) && BattleSystem_RandNext(battleSys) % 3 != 0) {
        return FALSE;
    }

    lastMove = battleCtx->moveHit[battler];
    attacker = battleCtx->moveHitBattler[battler];

    // Nothing has hit us yet, or what did hit us deals no damage.
    if (lastMove == MOVE_NONE || attacker == BATTLER_NONE || MOVE_DATA(lastMove).power == 0) {
        return FALSE;
    }

    if (Battler_Ability(battleCtx, attacker) == ABILITY_MOLD_BREAKER) {
        return FALSE;
    }

    lastMoveType = battleCtx->moveHitType[battler];

    // Our own ability already absorbs it, so there is nothing to gain.
    if (AI_AbilityAbsorbsMove(Battler_Ability(battleCtx, battler), lastMove, lastMoveType)) {
        return FALSE;
    }

    aiSlot1 = battler;
    if ((BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_TAG) || (BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_2vs2)) {
        aiSlot2 = aiSlot1;
    } else {
        aiSlot2 = BattleSystem_GetPartner(battleSys, battler);
    }

    start = 0;
    end = BattleSystem_GetPartyCount(battleSys, battler);

    for (i = start; i < end; i++) {
        mon = BattleSystem_GetPartyPokemon(battleSys, battler, i);

        if (Pokemon_GetValue(mon, MON_DATA_HP, NULL) != 0
            && Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_NONE
            && Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_EGG
            && i != battleCtx->selectedPartySlot[aiSlot1]
            && i != battleCtx->selectedPartySlot[aiSlot2]
            && i != battleCtx->aiSwitchedPartySlot[aiSlot1]
            && i != battleCtx->aiSwitchedPartySlot[aiSlot2]
            && AI_AbilityAbsorbsMove(Pokemon_GetValue(mon, MON_DATA_ABILITY, NULL), lastMove, lastMoveType)) {
            hasSuperEffective = FALSE;

            // The pivot is only worth it if the switch-in threatens back.
            for (j = 0; j < LEARNED_MOVES_MAX; j++) {
                move = Pokemon_GetValue(mon, MON_DATA_MOVE1 + j, NULL);

                if (move) {
                    moveType = Move_CalcVariableType(battleSys, battleCtx, mon, move);

                    effectiveness = 0;
                    BattleSystem_CalcEffectiveness(battleCtx,
                        move,
                        moveType,
                        Pokemon_GetValue(mon, MON_DATA_ABILITY, NULL),
                        Battler_Ability(battleCtx, attacker),
                        Battler_HeldItemEffect(battleCtx, attacker),
                        BattleMon_Get(battleCtx, attacker, BATTLEMON_TYPE_1, NULL),
                        BattleMon_Get(battleCtx, attacker, BATTLEMON_TYPE_2, NULL),
                        &effectiveness);

                    if (effectiveness & MOVE_STATUS_SUPER_EFFECTIVE) {
                        hasSuperEffective = TRUE;
                        break;
                    }
                }
            }

            if (hasSuperEffective && (BattleSystem_RandNext(battleSys) & 1)) {
                battleCtx->aiSwitchedPartySlot[battler] = i;
                return TRUE;
            }
        }
    }

    return FALSE;
}

/**
 * @brief Check if the AI has a party member with a super-effective move, constrained
 * to mons with a certain effectiveness matchup against the move that last hit us.
 *
 * Rolls once per qualifying party member, not once per super-effective move.
 *
 * @param battleSys
 * @param battleCtx
 * @param battler               The AI's battler.
 * @param checkEffectiveness    The desired effectiveness mask against the last move.
 * @param rand                  Random odds to switch, if conditions are met.
 * @return TRUE if the AI should switch, FALSE if not.
 */
static BOOL AI_HasPartyMemberWithSuperEffectiveMove(BattleSystem *battleSys, BattleContext *battleCtx, int battler, u32 checkEffectiveness, u8 rand)
{
    int i, j;
    u8 aiSlot1, aiSlot2;
    u16 move;
    int moveType;
    u32 effectiveness;
    BOOL hasSuperEffective;
    int start, end;
    Pokemon *mon;

    if (battleCtx->moveHit[battler] == MOVE_NONE || battleCtx->moveHitBattler[battler] == BATTLER_NONE) {
        return FALSE;
    }

    // If the last move that hit us is a status move, do not switch.
    if (MOVE_DATA(battleCtx->moveHit[battler]).power == 0) {
        return FALSE;
    }

    aiSlot1 = battler;
    if ((BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_TAG) || (BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_2vs2)) {
        aiSlot2 = aiSlot1;
    } else {
        aiSlot2 = BattleSystem_GetPartner(battleSys, battler);
    }

    start = 0;
    end = BattleSystem_GetPartyCount(battleSys, battler);

    for (i = start; i < end; i++) {
        mon = BattleSystem_GetPartyPokemon(battleSys, battler, i);

        if (Pokemon_GetValue(mon, MON_DATA_HP, NULL) != 0
            && Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_NONE
            && Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_EGG
            && i != battleCtx->selectedPartySlot[aiSlot1]
            && i != battleCtx->selectedPartySlot[aiSlot2]
            && i != battleCtx->aiSwitchedPartySlot[aiSlot1]
            && i != battleCtx->aiSwitchedPartySlot[aiSlot2]) {
            effectiveness = 0;
            moveType = TrainerAI_MoveType(battleSys, battleCtx, battleCtx->moveHitBattler[battler], battleCtx->moveHit[battler]);

            BattleSystem_CalcEffectiveness(battleCtx,
                battleCtx->moveHit[battler],
                moveType,
                Battler_Ability(battleCtx, battleCtx->moveHitBattler[battler]),
                Pokemon_GetValue(mon, MON_DATA_ABILITY, NULL),
                BattleSystem_GetItemData(battleCtx, Pokemon_GetValue(mon, MON_DATA_HELD_ITEM, NULL), ITEM_PARAM_HOLD_EFFECT),
                Pokemon_GetValue(mon, MON_DATA_TYPE_1, NULL),
                Pokemon_GetValue(mon, MON_DATA_TYPE_2, NULL),
                &effectiveness);

            if (effectiveness & checkEffectiveness) {
                hasSuperEffective = FALSE;

                for (j = 0; j < LEARNED_MOVES_MAX; j++) {
                    move = Pokemon_GetValue(mon, MON_DATA_MOVE1 + j, NULL);

                    if (move) {
                        moveType = Move_CalcVariableType(battleSys, battleCtx, mon, move);

                        effectiveness = 0;
                        BattleSystem_CalcEffectiveness(battleCtx,
                            move,
                            moveType,
                            Pokemon_GetValue(mon, MON_DATA_ABILITY, NULL),
                            Battler_Ability(battleCtx, battleCtx->moveHitBattler[battler]),
                            Battler_HeldItemEffect(battleCtx, battleCtx->moveHitBattler[battler]),
                            BattleMon_Get(battleCtx, battleCtx->moveHitBattler[battler], BATTLEMON_TYPE_1, NULL),
                            BattleMon_Get(battleCtx, battleCtx->moveHitBattler[battler], BATTLEMON_TYPE_2, NULL),
                            &effectiveness);

                        if (effectiveness & MOVE_STATUS_SUPER_EFFECTIVE) {
                            hasSuperEffective = TRUE;
                            break;
                        }
                    }
                }

                if (hasSuperEffective && BattleSystem_RandNext(battleSys) % rand == 0) {
                    battleCtx->aiSwitchedPartySlot[battler] = i;
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}

/**
 * @brief Check if the AI's battler is asleep and has Natural Cure + an eligible switch.
 *
 * @param battleSys
 * @param battleCtx
 * @param battler   The AI's battler.
 * @return TRUE if the AI should switch, FALSE otherwise.
 */
static BOOL AI_IsAsleepWithNaturalCure(BattleSystem *battleSys, BattleContext *battleCtx, int battler)
{
    // Don't switch if we aren't asleep, don't have Natural Cure, or are below 50% HP.
    if ((battleCtx->battleMons[battler].status & MON_CONDITION_SLEEP) == FALSE
        || Battler_Ability(battleCtx, battler) != ABILITY_NATURAL_CURE
        || battleCtx->battleMons[battler].curHP < (battleCtx->battleMons[battler].maxHP / 2)) {
        return FALSE;
    }

    // Check for the move that last hit you; i.e., don't switch on your first turn.
    // Switch 50% of the time, and use post-KO switch logic.
    if (battleCtx->moveHit[battler] == MOVE_NONE && (BattleSystem_RandNext(battleSys) & 1)) {
        battleCtx->aiSwitchedPartySlot[battler] = 6;
        return TRUE;
    }

    // If the last move that hit you is a status move, switch 50% of the time, following
    // post-KO switch logic.
    if (MOVE_DATA(battleCtx->moveHit[battler]).power == 0 && (BattleSystem_RandNext(battleSys) & 1)) {
        battleCtx->aiSwitchedPartySlot[battler] = 6;
        return TRUE;
    }

    // If we have a party member with an immunity to the last move that also has a
    // super-effective move, switch 50% of the time.
    if (AI_HasPartyMemberWithSuperEffectiveMove(battleSys, battleCtx, battler, MOVE_STATUS_INEFFECTIVE, 2)) {
        return TRUE;
    }

    // If we have a party member which resists the last move and also has a
    // super-effective move, switch 50% of the time.
    if (AI_HasPartyMemberWithSuperEffectiveMove(battleSys, battleCtx, battler, MOVE_STATUS_NOT_VERY_EFFECTIVE, 2)) {
        return TRUE;
    }

    // Randomly switch 50% of the time, following post-KO switch logic.
    if (BattleSystem_RandNext(battleSys) & 1) {
        battleCtx->aiSwitchedPartySlot[battler] = 6;
        return TRUE;
    }

    return FALSE;
}

/**
 * @brief Check if the AI should switch for turn.
 *
 * @param battleSys
 * @param battleCtx
 * @param battler   TRUE if the battler
 * @return BOOL
 */
static BOOL TrainerAI_ShouldSwitch(BattleSystem *battleSys, BattleContext *battleCtx, int battler)
{
    int i;
    int alivePartyMons;
    u8 aiSlot1, aiSlot2;
    int start, end;
    Pokemon *mon;

    // Don't try to make illegal switches
    // This definition is naive: the AI does not consider itself immune to Magnet Pull from an ally,
    // Shadow Tag if it also has Shadow Tag, Arena Trap if it is a Flying-type, or always able to switch
    // if it is holding a Shed Shell.
    if (MON_IS_NOT_TYPE(battler, TYPE_GHOST) && ((battleCtx->battleMons[battler].statusVolatile & VOLATILE_CONDITION_TRAPPED)
        || (battleCtx->battleMons[battler].moveEffectsMask & MOVE_EFFECT_INGRAIN)
        || BattleSystem_CountAbility(battleSys, battleCtx, COUNT_ALL_BATTLERS_EXCEPT_ME, battler, ABILITY_SHADOW_TAG)
        || BattleSystem_CountAbility(battleSys, battleCtx, COUNT_ALL_BATTLERS_THEIR_SIDE, battler, ABILITY_ARENA_TRAP)
        || (BattleSystem_CountAbility(battleSys, battleCtx, COUNT_ALL_BATTLERS_EXCEPT_ME, battler, ABILITY_MAGNET_PULL)
            && MON_HAS_TYPE(battler, TYPE_STEEL)))) {
        return FALSE;
    }

    alivePartyMons = 0;
    aiSlot1 = battler;
    if ((BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_TAG) || (BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_2vs2)) {
        aiSlot2 = aiSlot1;
    } else {
        aiSlot2 = BattleSystem_GetPartner(battleSys, battler);
    }

    // Check for living party members (obviously, do not try to switch if there are none).
    start = 0;
    end = BattleSystem_GetPartyCount(battleSys, battler);
    for (i = start; i < end; i++) {
        mon = BattleSystem_GetPartyPokemon(battleSys, battler, i);

        if (Pokemon_GetValue(mon, MON_DATA_HP, NULL) != 0
            && Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_NONE
            && Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_EGG
            && i != battleCtx->selectedPartySlot[aiSlot1]
            && i != battleCtx->selectedPartySlot[aiSlot2]
            && i != battleCtx->aiSwitchedPartySlot[aiSlot1]
            && i != battleCtx->aiSwitchedPartySlot[aiSlot2]) {
            alivePartyMons++;
        }
    }

    if (alivePartyMons) {
        if (AI_PerishSongKO(battleCtx, battler)) {
            return TRUE;
        }

        if (AI_CannotDamageWonderGuard(battleSys, battleCtx, battler)) {
            return TRUE;
        }

        if (AI_OnlyIneffectiveMoves(battleSys, battleCtx, battler)) {
            return TRUE;
        }

        if (AI_HasAbsorbAbilityInParty(battleSys, battleCtx, battler)) {
            return TRUE;
        }

        if (AI_IsAsleepWithNaturalCure(battleSys, battleCtx, battler)) {
            return TRUE;
        }

        // Do not switch if we have a super-effective move.
        // Note that this has a 10% chance of returning FALSE for each of our
        // moves that are super-effective against either opponent.
        if (AI_HasSuperEffectiveMove(battleSys, battleCtx, battler, FALSE)) {
            return FALSE;
        }

        // 50% of the time, switch to a party member with an immunity to the last move that hit
        // this battler which also has a super-effective move against an opposing Pokemon.
        if (AI_HasPartyMemberWithSuperEffectiveMove(battleSys, battleCtx, battler, MOVE_STATUS_INEFFECTIVE, 2)) {
            return TRUE;
        }
    }

    return FALSE;
}

int TrainerAI_PickCommand(BattleSystem *battleSys, int battler)
{
    // must declare C89-style to match
    int i;
    u8 battler1, battler2;
    u32 battleType;
    int end;
    Pokemon *mon;
    BattleContext *battleCtx = battleSys->battleCtx;
    battleType = BattleSystem_GetBattleType(battleSys);

    if ((battleType & BATTLE_TYPE_TRAINER) || BattleSystem_GetBattlerSide(battleSys, battler) == BATTLE_SIDE_PLAYER) {
        if (TrainerAI_ShouldSwitch(battleSys, battleCtx, battler)) {
            // If this is a switch which should use the post-KO switch logic, then do so.
            // If there is no valid battler, pick the first one in party order.
            if (battleCtx->aiSwitchedPartySlot[battler] == 6) {
                if ((i = BattleAI_PostKOSwitchIn(battleSys, battler)) == 6) {
                    battler1 = battler;
                    if ((battleType & BATTLE_TYPE_TAG) || (battleType & BATTLE_TYPE_2vs2)) {
                        battler2 = battler1;
                    } else {
                        battler2 = BattleSystem_GetPartner(battleSys, battler);
                    }

                    end = BattleSystem_GetPartyCount(battleSys, battler);
                    for (i = 0; i < end; i++) {
                        mon = BattleSystem_GetPartyPokemon(battleSys, battler, i);

                        if (Pokemon_GetValue(mon, MON_DATA_HP, NULL) != 0
                            && i != battleCtx->selectedPartySlot[battler1]
                            && i != battleCtx->selectedPartySlot[battler2]
                            && i != battleCtx->aiSwitchedPartySlot[battler1]
                            && i != battleCtx->aiSwitchedPartySlot[battler2]) {
                            break;
                        }
                    }
                }

                battleCtx->aiSwitchedPartySlot[battler] = i;
            }

            return PLAYER_INPUT_PARTY;
        }

        // Check if the AI determines that it should use an item
        if (TrainerAI_ShouldUseItem(battleSys, battler)) {
            return PLAYER_INPUT_ITEM;
        }
    }

    return PLAYER_INPUT_FIGHT;
}

/**
 * @brief Determine if the AI should use an item on its active battler.
 *
 * Several buffers will be filled, if an item should be used:
 * 1. The item type (e.g., Full Restore, Potion, etc.)
 * 2. Any parameters for the item, e.g. what status condition it heals
 * 3. What item number is used
 *
 * The trainer's pocket of items will also be updated appropriately.
 *
 * @param battleSys
 * @param battler   The AI's battler.
 * @return          TRUE if an item should be used, FALSE if not.
 */
static BOOL TrainerAI_ShouldUseItem(BattleSystem *battleSys, int battler)
{
    int i;
    u8 aliveMons = 0;
    u16 item;
    u8 hpRestore;
    BOOL result;
    Party *party;
    Pokemon *mon;
    BattleContext *battleCtx = battleSys->battleCtx;
    AI_CONTEXT.usedItemCondition[battler >> 1] = 0;
    result = FALSE;

    // Don't let the AI partners ever use items in battle against trainers.
    if ((battleSys->battleType & BATTLE_TYPE_TRAINER_WITH_AI_PARTNER) == BATTLE_TYPE_TRAINER_WITH_AI_PARTNER
        && BattleSystem_GetBattlerType(battleSys, battler) == BATTLER_TYPE_PLAYER_SIDE_SLOT_2) {
        return result;
    }

    // Don't try to use items if it's illegal to do so.
    if (battleCtx->battleMons[battler].moveEffectsMask & MOVE_EFFECT_EMBARGO) {
        return result;
    }

    party = BattleSystem_GetParty(battleSys, battler);
    for (i = 0; i < Party_GetCurrentCount(party); i++) {
        mon = Party_GetPokemonBySlotIndex(party, i);

        if (Pokemon_GetValue(mon, MON_DATA_HP, NULL) != 0
            && Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_NONE
            && Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_EGG) {
            aliveMons++;
        }
    }

    for (i = 0; i < MAX_TRAINER_ITEMS; i++) {
        if (i == 0 || aliveMons <= AI_CONTEXT.trainerItemCounts[battler >> 1] - i + 1) {
            item = AI_CONTEXT.trainerItems[battler >> 1][i];

            if (item == ITEM_NONE) {
                continue;
            }

            if (item == ITEM_FULL_RESTORE) {
                if (battleCtx->battleMons[battler].curHP < (battleCtx->battleMons[battler].maxHP / 4)
                    && battleCtx->battleMons[battler].curHP) {
                    AI_CONTEXT.usedItemType[battler >> 1] = ITEM_AI_CATEGORY_FULL_RESTORE;
                    result = TRUE;
                }
            } else if (BattleSystem_GetItemData(battleCtx, item, ITEM_PARAM_HP_RESTORE)) {
                hpRestore = BattleSystem_GetItemData(battleCtx, item, ITEM_PARAM_HP_RESTORED);

                // Use an HP restore item if the battler is at less than 1/4 HP or if the full HP restore
                // value of the item would be used.
                if (hpRestore) {
                    if (battleCtx->battleMons[battler].curHP
                        && (battleCtx->battleMons[battler].curHP < (battleCtx->battleMons[battler].maxHP / 4)
                            || (battleCtx->battleMons[battler].maxHP - battleCtx->battleMons[battler].curHP) > hpRestore)) {
                        AI_CONTEXT.usedItemType[battler >> 1] = ITEM_AI_CATEGORY_RECOVER_HP;
                        result = TRUE;
                    }
                }
            } else if (BattleSystem_GetItemData(battleCtx, item, ITEM_PARAM_HEAL_SLEEP)) {
                if (battleCtx->battleMons[battler].status & MON_CONDITION_SLEEP) {
                    AI_CONTEXT.usedItemCondition[battler >> 1] |= FlagIndex(5);
                    AI_CONTEXT.usedItemType[battler >> 1] = ITEM_AI_CATEGORY_RECOVER_STATUS;
                    result = TRUE;
                }
            } else if (BattleSystem_GetItemData(battleCtx, item, ITEM_PARAM_HEAL_POISON)) {
                if ((battleCtx->battleMons[battler].status & MON_CONDITION_POISON)
                    || (battleCtx->battleMons[battler].status & MON_CONDITION_TOXIC)) {
                    AI_CONTEXT.usedItemCondition[battler >> 1] |= FlagIndex(4);
                    AI_CONTEXT.usedItemType[battler >> 1] = ITEM_AI_CATEGORY_RECOVER_STATUS;
                    result = TRUE;
                }
            } else if (BattleSystem_GetItemData(battleCtx, item, ITEM_PARAM_HEAL_BURN)) {
                if (battleCtx->battleMons[battler].status & MON_CONDITION_BURN) {
                    AI_CONTEXT.usedItemCondition[battler >> 1] |= FlagIndex(3);
                    AI_CONTEXT.usedItemType[battler >> 1] = ITEM_AI_CATEGORY_RECOVER_STATUS;
                    result = TRUE;
                }
            } else if (BattleSystem_GetItemData(battleCtx, item, ITEM_PARAM_HEAL_FREEZE)) {
                if (battleCtx->battleMons[battler].status & MON_CONDITION_FREEZE) {
                    AI_CONTEXT.usedItemCondition[battler >> 1] |= FlagIndex(2);
                    AI_CONTEXT.usedItemType[battler >> 1] = ITEM_AI_CATEGORY_RECOVER_STATUS;
                    result = TRUE;
                }
            } else if (BattleSystem_GetItemData(battleCtx, item, ITEM_PARAM_HEAL_PARALYSIS)) {
                if (battleCtx->battleMons[battler].status & MON_CONDITION_PARALYSIS) {
                    AI_CONTEXT.usedItemCondition[battler >> 1] |= FlagIndex(1);
                    AI_CONTEXT.usedItemType[battler >> 1] = ITEM_AI_CATEGORY_RECOVER_STATUS;
                    result = TRUE;
                }
            } else if (BattleSystem_GetItemData(battleCtx, item, ITEM_PARAM_HEAL_CONFUSION)) {
                if (battleCtx->battleMons[battler].statusVolatile & VOLATILE_CONDITION_CONFUSION) {
                    AI_CONTEXT.usedItemCondition[battler >> 1] |= FlagIndex(0);
                    AI_CONTEXT.usedItemType[battler >> 1] = ITEM_AI_CATEGORY_RECOVER_STATUS;
                    result = TRUE;
                }
                // Don't try to use any of these until after the first turn that a mon is in play.
            } else if ((battleCtx->battleMons[battler].moveEffectsData.fakeOutTurnNumber - battleCtx->totalTurns) >= 0) {
                if (BattleSystem_GetItemData(battleCtx, item, ITEM_PARAM_ATK_STAGES)) {
                    AI_CONTEXT.usedItemCondition[battler >> 1] = BATTLE_STAT_ATTACK;
                    AI_CONTEXT.usedItemType[battler >> 1] = ITEM_AI_CATEGORY_STAT_BOOSTER;
                    result = TRUE;
                } else if (BattleSystem_GetItemData(battleCtx, item, ITEM_PARAM_DEF_STAGES)) {
                    AI_CONTEXT.usedItemCondition[battler >> 1] = BATTLE_STAT_DEFENSE;
                    AI_CONTEXT.usedItemType[battler >> 1] = ITEM_AI_CATEGORY_STAT_BOOSTER;
                    result = TRUE;
                } else if (BattleSystem_GetItemData(battleCtx, item, ITEM_PARAM_SPATK_STAGES)) {
                    AI_CONTEXT.usedItemCondition[battler >> 1] = BATTLE_STAT_SP_ATTACK;
                    AI_CONTEXT.usedItemType[battler >> 1] = ITEM_AI_CATEGORY_STAT_BOOSTER;
                    result = TRUE;
                } else if (BattleSystem_GetItemData(battleCtx, item, ITEM_PARAM_SPDEF_STAGES)) {
                    AI_CONTEXT.usedItemCondition[battler >> 1] = BATTLE_STAT_SP_DEFENSE;
                    AI_CONTEXT.usedItemType[battler >> 1] = ITEM_AI_CATEGORY_STAT_BOOSTER;
                    result = TRUE;
                } else if (BattleSystem_GetItemData(battleCtx, item, ITEM_PARAM_SPEED_STAGES)) {
                    AI_CONTEXT.usedItemCondition[battler >> 1] = BATTLE_STAT_SPEED;
                    AI_CONTEXT.usedItemType[battler >> 1] = ITEM_AI_CATEGORY_STAT_BOOSTER;
                    result = TRUE;
                } else if (BattleSystem_GetItemData(battleCtx, item, ITEM_PARAM_ACC_STAGES)) {
                    AI_CONTEXT.usedItemCondition[battler >> 1] = BATTLE_STAT_ACCURACY;
                    AI_CONTEXT.usedItemType[battler >> 1] = ITEM_AI_CATEGORY_STAT_BOOSTER;
                    result = TRUE;
                } else if (BattleSystem_GetItemData(battleCtx, item, ITEM_PARAM_GUARD_SPEC)
                    && (battleCtx->sideConditionsMask[1] & SIDE_CONDITION_MIST) == FALSE) {
                    AI_CONTEXT.usedItemType[battler >> 1] = ITEM_AI_CATEGORY_GUARD_SPEC;
                    result = TRUE;
                }
            } else {
                // Unrecognized item type
                AI_CONTEXT.usedItemType[battler >> 1] = ITEM_AI_CATEGORY_MAX;
            }

            if (result == TRUE) {
                AI_CONTEXT.usedItem[battler >> 1] = item;
                AI_CONTEXT.trainerItems[battler >> 1][i] = 0;
            }
        }
    }

    return result;
}
