#include "overlay005/follower_ball_effect.h"

#include <nitro.h>
#include <string.h>

#include "constants/field/field_effect_renderer.h"

#include "struct_decls/map_object.h"

#include "overlay005/field_effect_manager.h"

#include "map_object.h"
#include "overworld_anim_manager.h"
#include "simple3d.h"

#define FLDEFF_MEMBER_BALL_BURST      202
#define FLDEFF_MEMBER_BALL_BURST_ANIM 203

#define BALL_EFFECT_HEIGHT (FX32_ONE * 6)

typedef struct FollowerBallEffectResources {
    FieldEffectManager *fieldEffMan;
    Simple3DModel burstModel;
    Simple3DAnimation burstAnim;
} FollowerBallEffectResources;

typedef struct FollowerBallEffectUserData {
    FieldEffectManager *fieldEffMan;
    FollowerBallEffectResources *resources;
    MapObject *mapObj;
} FollowerBallEffectUserData;

typedef struct FollowerBallEffect {
    FollowerBallEffectUserData userData;
    Simple3DAnimation burstAnim;
    Simple3DRenderObj burstRenderObj;
} FollowerBallEffect;

static void FollowerBallEffectResources_Init(FollowerBallEffectResources *resources);
static void FollowerBallEffectResources_Free(FollowerBallEffectResources *resources);

static const OverworldAnimManagerFuncs sFollowerBallEffectAnimFuncs;

void *FollowerBallEffect_New(FieldEffectManager *fieldEffMan)
{
    FollowerBallEffectResources *resources = FieldEffectManager_HeapAllocInit(fieldEffMan, sizeof(FollowerBallEffectResources), FALSE, 0);
    resources->fieldEffMan = fieldEffMan;

    FollowerBallEffectResources_Init(resources);
    return resources;
}

void FollowerBallEffect_Free(void *context)
{
    FollowerBallEffectResources *resources = context;

    FollowerBallEffectResources_Free(resources);
    FieldEffectManager_HeapFree(resources);
}

static void FollowerBallEffectResources_Init(FollowerBallEffectResources *resources)
{
    FieldEffectManager_LoadModel(resources->fieldEffMan, &resources->burstModel, 0, FLDEFF_MEMBER_BALL_BURST, FALSE);
    FieldEffectManager_LoadAnimation(resources->fieldEffMan, &resources->burstAnim, 0, FLDEFF_MEMBER_BALL_BURST_ANIM, FALSE);
}

static void FollowerBallEffectResources_Free(FollowerBallEffectResources *resources)
{
    Simple3D_FreeModel(&resources->burstModel);
    Simple3D_FreeAnimation(&resources->burstAnim);
}

OverworldAnimManager *FollowerBallEffect_Start(MapObject *mapObj)
{
    FieldEffectManager *fieldEffMan = MapObject_GetFieldEffectManager(mapObj);
    FollowerBallEffectUserData userData;
    VecFx32 pos;
    int taskPriority;

    userData.fieldEffMan = fieldEffMan;
    userData.resources = FieldEffectManager_GetRendererContext(fieldEffMan, FIELD_EFFECT_RENDERER_FOLLOWER_BALL);
    userData.mapObj = mapObj;

    MapObject_GetPosPtr(mapObj, &pos);
    pos.y += BALL_EFFECT_HEIGHT;

    taskPriority = MapObject_CalculateTaskPriority(mapObj, 2);

    return FieldEffectManager_InitAnimManager(fieldEffMan, &sFollowerBallEffectAnimFuncs, &pos, 0, &userData, taskPriority);
}

static BOOL FollowerBallEffect_AnimInit(OverworldAnimManager *animMan, void *context)
{
    FollowerBallEffect *renderer = context;
    const FollowerBallEffectUserData *userData = OverworldAnimManager_GetUserData(animMan);

    renderer->userData = *userData;

    FieldEffectManager_ApplyAnimCopyToModel(renderer->userData.fieldEffMan,
        &renderer->burstAnim,
        &renderer->userData.resources->burstModel,
        &renderer->userData.resources->burstAnim,
        0);

    Simple3D_CreateRenderObjectWithAnim(&renderer->burstRenderObj,
        &renderer->userData.resources->burstModel,
        &renderer->burstAnim);

    Simple3D_SetAnimFrame(&renderer->burstAnim, 0);
    return TRUE;
}

static void FollowerBallEffect_AnimExit(OverworldAnimManager *animMan, void *context)
{
    FollowerBallEffect *renderer = context;
    Simple3D_FreeAnimation(&renderer->burstAnim);
}

static void FollowerBallEffect_AnimTick(OverworldAnimManager *animMan, void *context)
{
    FollowerBallEffect *renderer = context;

    if (Simple3D_HasAnimationReachedEnd(&renderer->burstAnim) == TRUE) {
        FieldEffectManager_FinishAnimManager(animMan);
        return;
    }

    Simple3D_UpdateAnim(&renderer->burstAnim, FX32_ONE, FALSE);
}

static void FollowerBallEffect_AnimRender(OverworldAnimManager *animMan, void *context)
{
    FollowerBallEffect *renderer = context;
    VecFx32 pos;

    OverworldAnimManager_GetPosition(animMan, &pos);

    Simple3D_DrawRenderObjWithPos(&renderer->burstRenderObj, &pos);
}

static const OverworldAnimManagerFuncs sFollowerBallEffectAnimFuncs = {
    sizeof(FollowerBallEffect),
    FollowerBallEffect_AnimInit,
    FollowerBallEffect_AnimExit,
    FollowerBallEffect_AnimTick,
    FollowerBallEffect_AnimRender
};
