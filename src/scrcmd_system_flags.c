#include "scrcmd_system_flags.h"

#include "generated/badges.h"
#include "generated/movement_types.h"

#include "struct_defs/player_data.h"

#include "constants/battle/condition.h"
#include "field/field_system.h"
#include "field_overworld_state.h"
#include "field_script_context.h"
#include "follower_mon.h"
#include "inlines.h"
#include "map_object.h"
#include "map_object_move.h"
#include "overlay005/ov5_021ECC20.h"
#include "party.h"
#include "player_avatar.h"
#include "pokedex.h"
#include "pokemon.h"
#include "save_player.h"
#include "savedata.h"
#include "system_flags.h"
#include "trainer_info.h"
#include "vars_flags.h"

BOOL ScrCmd_CheckPokedexAcquired(ScriptContext *ctx)
{
    const Pokedex *pokedex = SaveData_GetPokedex(ctx->fieldSystem->saveData);
    u16 *destVar = ScriptContext_GetVarPointer(ctx);
    *destVar = Pokedex_IsObtained(pokedex);
    return FALSE;
}

BOOL ScrCmd_GivePokedex(ScriptContext *ctx)
{
    Pokedex *pokedex = SaveData_GetPokedex(ctx->fieldSystem->saveData);
    Pokedex_ObtainPokedex(pokedex);
    return FALSE;
}

BOOL ScrCmd_CheckRunningShoesAcquired(ScriptContext *ctx)
{
    u16 *destVar = ScriptContext_GetVarPointer(ctx);
    FieldOverworldState *overworldState = SaveData_GetFieldOverworldState(ctx->fieldSystem->saveData);
    PlayerData *playerData = FieldOverworldState_GetPlayerData(overworldState);
    *destVar = PlayerData_HasRunningShoes(playerData);
    return FALSE;
}

BOOL ScrCmd_GiveRunningShoes(ScriptContext *ctx)
{
    FieldOverworldState *overworldState = SaveData_GetFieldOverworldState(ctx->fieldSystem->saveData);
    PlayerData *playerData = FieldOverworldState_GetPlayerData(overworldState);
    PlayerData_SetRunningShoes(playerData, TRUE);
    return FALSE;
}

BOOL ScrCmd_CheckBadgeAcquired(ScriptContext *ctx)
{
    u16 badgeNum = ScriptContext_GetVar(ctx);
    u16 *destVar = ScriptContext_GetVarPointer(ctx);

    GF_ASSERT(badgeNum < MAX_BADGES);
    *destVar = TrainerInfo_HasBadge(SaveData_GetTrainerInfo(ctx->fieldSystem->saveData), badgeNum);

    return FALSE;
}

BOOL ScrCmd_GiveBadge(ScriptContext *ctx)
{
    u16 badgeNum = ScriptContext_GetVar(ctx);

    GF_ASSERT(badgeNum < MAX_BADGES);
    TrainerInfo_SetBadge(SaveData_GetTrainerInfo(ctx->fieldSystem->saveData), badgeNum);

    return FALSE;
}

BOOL ScrCmd_CheckBagAcquired(ScriptContext *ctx)
{
    u16 *destVar = ScriptContext_GetVarPointer(ctx);
    *destVar = SystemFlag_CheckBagAcquired(SaveData_GetVarsFlags(ctx->fieldSystem->saveData));
    return FALSE;
}

// Game Freak moment.
static const u8 sBadgeIDs[MAX_BADGES] = {
    BADGE_ID_COAL,
    BADGE_ID_FOREST,
    BADGE_ID_COBBLE,
    BADGE_ID_FEN,
    BADGE_ID_RELIC,
    BADGE_ID_MINE,
    BADGE_ID_ICICLE,
    BADGE_ID_BEACON,
};

BOOL ScrCmd_CountBadgesAcquired(ScriptContext *ctx)
{
    u16 i, count;
    u16 *destVar = ScriptContext_GetVarPointer(ctx);
    for (i = 0, count = 0; i < MAX_BADGES; i++) {
        if (TrainerInfo_HasBadge(SaveData_GetTrainerInfo(ctx->fieldSystem->saveData), sBadgeIDs[i]) == TRUE) {
            count++;
        }
    }

    *destVar = count;
    return FALSE;
}

BOOL ScrCmd_GiveBag(ScriptContext *ctx)
{
    SystemFlag_SetBagAcquired(SaveData_GetVarsFlags(ctx->fieldSystem->saveData));
    return FALSE;
}

BOOL ScrCmd_CheckHasPartner(ScriptContext *ctx)
{
    u16 *destVar = ScriptContext_GetVarPointer(ctx);
    *destVar = SystemFlag_CheckHasPartner(SaveData_GetVarsFlags(ctx->fieldSystem->saveData));
    return FALSE;
}

BOOL ScrCmd_SetHasPartner(ScriptContext *ctx)
{
    FieldSystem *fieldSystem = ctx->fieldSystem;
    VarsFlags *varsFlags = SaveData_GetVarsFlags(fieldSystem->saveData);

    if (SystemFlag_CheckHasPartner(varsFlags) == FALSE) {
        MapObject *follower = MapObjMan_GetLocalMapObjByMovementType(
            fieldSystem->mapObjMan, MOVEMENT_TYPE_FOLLOW_PLAYER);

        if (follower != NULL) {
            MapObject_Delete(follower);
        }

        fieldSystem->followMon.active = FALSE;
    }

    SystemFlag_SetHasPartner(varsFlags);
    return FALSE;
}

BOOL ScrCmd_ClearHasPartner(ScriptContext *ctx)
{
    SystemFlag_ClearHasPartner(SaveData_GetVarsFlags(ctx->fieldSystem->saveData));
    return FALSE;
}

BOOL ScrCmd_CheckStepFlag(ScriptContext *ctx)
{
    u16 *destVar = ScriptContext_GetVarPointer(ctx);
    *destVar = SystemFlag_CheckStep(SaveData_GetVarsFlags(ctx->fieldSystem->saveData));
    return FALSE;
}

BOOL ScrCmd_SetStepFlag(ScriptContext *ctx)
{
    SystemFlag_SetStep(SaveData_GetVarsFlags(ctx->fieldSystem->saveData));
    return FALSE;
}

BOOL ScrCmd_ClearStepFlag(ScriptContext *ctx)
{
    SystemFlag_ClearStep(SaveData_GetVarsFlags(ctx->fieldSystem->saveData));
    return FALSE;
}

BOOL ScrCmd_CheckGameCompleted(ScriptContext *ctx)
{
    u16 *destVar = ScriptContext_GetVarPointer(ctx);
    *destVar = SystemFlag_CheckGameCompleted(SaveData_GetVarsFlags(ctx->fieldSystem->saveData));
    return FALSE;
}

BOOL ScrCmd_SetGameCompleted(ScriptContext *ctx)
{
    SystemFlag_SetGameCompleted(SaveData_GetVarsFlags(ctx->fieldSystem->saveData));
    return FALSE;
}

BOOL ScrCmd_Strength(ScriptContext *ctx)
{
    u16 *destVar;
    VarsFlags *varsFlags = SaveData_GetVarsFlags(ctx->fieldSystem->saveData);

    switch (ScriptContext_ReadByte(ctx)) {
    case 1:
        SystemFlag_HandleStrengthActive(varsFlags, HANDLE_FLAG_SET);
        break;

    case 0:
        SystemFlag_HandleStrengthActive(varsFlags, HANDLE_FLAG_CLEAR);
        break;

    case 2:
        destVar = ScriptContext_GetVarPointer(ctx);
        *destVar = SystemFlag_HandleStrengthActive(varsFlags, HANDLE_FLAG_CHECK);
        break;

    default:
        GF_ASSERT(FALSE);
    }

    return FALSE;
}

BOOL ScrCmd_Flash(ScriptContext *ctx)
{
    u16 *destVar;
    VarsFlags *varsFlags = SaveData_GetVarsFlags(ctx->fieldSystem->saveData);

    switch (ScriptContext_ReadByte(ctx)) {
    case 1:
        SystemFlag_SetFlashActive(varsFlags);
        break;

    case 0:
        SystemFlag_ClearFlashActive(varsFlags);
        break;

    case 2:
        destVar = ScriptContext_GetVarPointer(ctx);
        *destVar = SystemFlag_CheckFlashActive(varsFlags);
        break;

    default:
        GF_ASSERT(FALSE);
    }

    return FALSE;
}

BOOL ScrCmd_Defog(ScriptContext *ctx)
{
    u16 *destVar;
    VarsFlags *varsFlags = SaveData_GetVarsFlags(ctx->fieldSystem->saveData);

    switch (ScriptContext_ReadByte(ctx)) {
    case 1:
        SystemFlag_SetDefogActive(varsFlags);
        break;

    case 0:
        SystemFlag_ClearDefogActive(varsFlags);
        break;

    case 2:
        destVar = ScriptContext_GetVarPointer(ctx);
        *destVar = SystemFlag_CheckDefogActive(varsFlags);
        break;

    default:
        GF_ASSERT(FALSE);
    }

    return FALSE;
}

BOOL ScrCmd_SendOutFollowingPoke(ScriptContext *ctx)
{
    FollowerMon_UpdateFollower(ctx->fieldSystem);
    return FALSE;
}

BOOL ScrCmd_SendBackFollowingPoke(ScriptContext *ctx)
{
    FieldSystem *fieldSystem = ctx->fieldSystem;
    MapObject *follower = MapObjMan_GetLocalMapObjByMovementType(
        fieldSystem->mapObjMan, MOVEMENT_TYPE_FOLLOW_PLAYER);

    if (follower != NULL) {
        MapObject_Delete(follower);
    }

    fieldSystem->followMon.active = FALSE;

    return FALSE;
}

BOOL ScrCmd_CheckHasFollower(ScriptContext *ctx)
{
    u16 *destVar = ScriptContext_GetVarPointer(ctx);
    *destVar = MapObjMan_GetLocalMapObjByMovementType(
        ctx->fieldSystem->mapObjMan, MOVEMENT_TYPE_FOLLOW_PLAYER) != NULL;
    return FALSE;
}

BOOL ScrCmd_FollowPokeFacePlayer(ScriptContext *ctx)
{
    FieldSystem *fieldSystem = ctx->fieldSystem;
    MapObject *follower = MapObjMan_GetLocalMapObjByMovementType(
        fieldSystem->mapObjMan, MOVEMENT_TYPE_FOLLOW_PLAYER);

    if (follower == NULL) {
        return FALSE;
    }

    int playerDir = PlayerAvatar_GetDir(fieldSystem->playerAvatar);
    ov5_021ECDFC(follower, Direction_GetOpposite(playerDir));
    return FALSE;
}

BOOL ScrCmd_GetFollowerPartySlot(ScriptContext *ctx)
{
    u16 *destVar = ScriptContext_GetVarPointer(ctx);
    Party *party = SaveData_GetParty(ctx->fieldSystem->saveData);
    int count = Party_GetCurrentCount(party);
    int i;
    for (i = 0; i < count; i++) {
        if (Pokemon_GetValue(Party_GetPokemonBySlotIndex(party, i), MON_DATA_HP, NULL)) {
            *destVar = (u16)i;
            return FALSE;
        }
    }
    *destVar = 0;
    return FALSE;
}

static Pokemon *GetFollowerLead(FieldSystem *fieldSystem)
{
    Party *party = SaveData_GetParty(fieldSystem->saveData);
    int count = Party_GetCurrentCount(party);
    int i;
    for (i = 0; i < count; i++) {
        Pokemon *mon = Party_GetPokemonBySlotIndex(party, i);
        if (Pokemon_GetValue(mon, MON_DATA_HP, NULL)) {
            return mon;
        }
    }
    return Party_GetPokemonBySlotIndex(party, 0);
}

BOOL ScrCmd_GetFollowerMonHPPercent(ScriptContext *ctx)
{
    u16 *destVar = ScriptContext_GetVarPointer(ctx);
    Pokemon *lead = GetFollowerLead(ctx->fieldSystem);
    u32 hp = Pokemon_GetValue(lead, MON_DATA_HP, NULL);
    u32 maxHp = Pokemon_GetValue(lead, MON_DATA_MAX_HP, NULL);
    *destVar = (maxHp > 0) ? (u16)(hp * 100 / maxHp) : 0;
    return FALSE;
}

#define FOLLOWER_STATUS_NONE      0
#define FOLLOWER_STATUS_SLEEP     1
#define FOLLOWER_STATUS_POISON    2
#define FOLLOWER_STATUS_BURN      3
#define FOLLOWER_STATUS_FROZEN    4
#define FOLLOWER_STATUS_PARALYZED 5

BOOL ScrCmd_GetFollowerMonStatus(ScriptContext *ctx)
{
    u16 *destVar = ScriptContext_GetVarPointer(ctx);
    Pokemon *lead = GetFollowerLead(ctx->fieldSystem);
    u32 condition = Pokemon_GetValue(lead, MON_DATA_STATUS, NULL);

    if (condition & MON_CONDITION_SLEEP) {
        *destVar = FOLLOWER_STATUS_SLEEP;
    } else if (condition & MON_CONDITION_ANY_POISON) {
        *destVar = FOLLOWER_STATUS_POISON;
    } else if (condition & MON_CONDITION_BURN) {
        *destVar = FOLLOWER_STATUS_BURN;
    } else if (condition & MON_CONDITION_FREEZE) {
        *destVar = FOLLOWER_STATUS_FROZEN;
    } else if (condition & MON_CONDITION_PARALYSIS) {
        *destVar = FOLLOWER_STATUS_PARALYZED;
    } else {
        *destVar = FOLLOWER_STATUS_NONE;
    }

    return FALSE;
}
