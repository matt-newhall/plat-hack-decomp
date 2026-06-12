#include <nitro.h>
#include <string.h>

#include "generated/object_events_gfx.h"

#include "overlay005/berry_graphics_data.h"
#include "overlay005/berry_graphics_table.h"
#include "overlay005/const_ov5_021FAF40.h"
#include "overlay005/const_ov5_021FAF48.h"
#include "overlay005/const_ov5_021FAF50.h"
#include "overlay005/const_ov5_021FB470.h"
#include "overlay005/const_ov5_021FB484.h"
#include "overlay005/const_ov5_021FB51C.h"
#include "overlay005/const_ov5_021FB5BC.h"
#include "overlay005/const_ov5_021FB97C.h"
#include "overlay005/const_ov5_021FC194.h"
#include "overlay005/const_ov5_021FC9B4.h"
#include "overlay005/const_ov5_021FD77C.h"
#include "overlay005/ov5_021EB1A0.h"
#include "overlay005/ov5_021ECA70.h"
#include "overlay005/ov5_021ECC20.h"
#include "overlay005/ov5_021ECE40.h"

#include "billboard.h"
#include "constants/map_object.h"
#include "map_object.h"
#include "overlay005/struct_ov5_021EC700.h"
#include "overlay005/struct_ov5_021ECD10.h"
#include "overlay005/struct_ov5_021ED2D0.h"
#include "overlay005/struct_ov5_021EDD04.h"
#include "overlay005/struct_ov5_021FB0F0.h"
#include "overlay005/struct_ov5_021FB97C.h"

#include "berry_patch_graphics.h"

static const UnkStruct_ov5_021FB0F0 Unk_ov5_021FB0F0 = {
    ov5_021EBA0C,
    ov5_021EBAD0,
    ov5_021EBA34,
    ov5_021EBA60,
    ov5_021EBA8C
};

static const UnkStruct_ov5_021FB0F0 Unk_ov5_021FAF88 = {
    ov5_021EBA0C,
    ov5_021EBF50,
    ov5_021EBA34,
    ov5_021EBA60,
    ov5_021EBA8C
};

static const UnkStruct_ov5_021FB0F0 Unk_ov5_021FAF60 = {
    ov5_021EBA0C,
    ov5_021EC3F0,
    ov5_021EBA34,
    ov5_021EBA60,
    ov5_021EBA8C
};

static const UnkStruct_ov5_021FB0F0 Unk_ov5_021FAFB0 = {
    ov5_021EBA0C,
    ov5_021EC454,
    ov5_021EBA34,
    ov5_021EBA60,
    ov5_021EBA8C
};

static const UnkStruct_ov5_021FB0F0 Unk_ov5_021FAFEC = {
    ov5_021EBA0C,
    ov5_021EC4BC,
    ov5_021EBA34,
    ov5_021EBA60,
    ov5_021EBA8C
};

static const UnkStruct_ov5_021FB0F0 Unk_ov5_021FB014 = {
    ov5_021EBA0C,
    ov5_021EC15C,
    ov5_021EBA34,
    ov5_021EBA60,
    ov5_021EBA8C
};

static const UnkStruct_ov5_021FB0F0 Unk_ov5_021FB0DC = {
    ov5_021EBA0C,
    ov5_021EC554,
    ov5_021EBA34,
    ov5_021EBA60,
    ov5_021EBA8C
};

static const UnkStruct_ov5_021FB0F0 Unk_ov5_021FB0C8 = {
    ov5_021EBA0C,
    ov5_021EC5C0,
    ov5_021EBA34,
    ov5_021EBA60,
    ov5_021EBA8C
};

static const UnkStruct_ov5_021FB0F0 Unk_ov5_021FAFD8 = {
    ov5_021EB2EC,
    ov5_021EB398,
    ov5_021EB314,
    ov5_021EB328,
    ov5_021EB354
};

static void FollowerMon_AnimCallback(MapObject *mapObj)
{
    Billboard *billboard;
    int dir;
    int animNum;
    int draw;

    if (ov5_021EDD94(mapObj) == 1) {
        return;
    }

    billboard = ov5_021EB1A0(mapObj);
    if (billboard == NULL) {
        return;
    }

    dir     = MapObject_GetFacingDir(mapObj);
    animNum = ov5_021EDF18(dir);
    Billboard_SetAnimNum(billboard, animNum);

    Billboard_AdvanceAnim(billboard, FX32_ONE);

    ov5_021EDEB4(mapObj, billboard);

    draw = 1;
    if (MapObject_CheckStatusFlag(mapObj, MAP_OBJ_STATUS_HIDE)) {
        draw = 0;
    }
    if (MapObject_CheckStatusFlag(mapObj, MAP_OBJ_STATUS_12) && !MapObject_CheckStatusFlag(mapObj, MAP_OBJ_STATUS_13)) {
        draw = 0;
    }
    Billboard_SetDrawFlag(billboard, draw);
}

static const UnkStruct_ov5_021FB0F0 Unk_ov5_FollowerMon = {
    ov5_021EB2EC,
    FollowerMon_AnimCallback,
    ov5_021EB314,
    ov5_021EB328,
    ov5_021EB354
};

static const UnkStruct_ov5_021FB0F0 Unk_ov5_021FB0A0 = {
    ov5_021EB2EC,
    ov5_021EB40C,
    ov5_021EB314,
    ov5_021EB328,
    ov5_021EB354
};

static const UnkStruct_ov5_021FB0F0 Unk_ov5_021FB03C = {
    ov5_021EB2EC,
    ov5_021EB438,
    ov5_021EB314,
    ov5_021EB328,
    ov5_021EB354
};

static const UnkStruct_ov5_021FB0F0 Unk_ov5_021FB08C = {
    ov5_021EB2EC,
    ov5_021EB720,
    ov5_021EB314,
    ov5_021EB328,
    ov5_021EB354
};

static const UnkStruct_ov5_021FB0F0 Unk_ov5_021FB064 = {
    ov5_021EB7F8,
    ov5_021EB8B8,
    ov5_021EB834,
    ov5_021EB848,
    ov5_021EB874
};

static const UnkStruct_ov5_021FB0F0 Unk_ov5_021FB000 = {
    ov5_021EC734,
    ov5_021EC75C,
    ov5_021EC760,
    ov5_021EC778,
    ov5_021EC790
};

static const UnkStruct_ov5_021FB0F0 BerryPatchRenderer = {
    BerryPatchGraphics_NewGraphics,
    BerryPatchGraphics_UpdateGraphics,
    BerryPatchGraphics_FreeGraphics,
    BerryPatchGraphics_PauseGraphics,
    BerryPatchGraphics_ResumeGraphics
};

static const UnkStruct_ov5_021FB0F0 Unk_ov5_021FB078 = {
    ov5_021EB2EC,
    ov5_021EB944,
    ov5_021EB314,
    ov5_021EB328,
    ov5_021EB354
};

static const UnkStruct_ov5_021FB0F0 Unk_ov5_021FB050 = {
    ov5_021EC7B8,
    ov5_021EC75C,
    ov5_021EC760,
    ov5_021EC778,
    ov5_021EC7D0
};

const UnkStruct_ov5_021FB0F0 Unk_ov5_021FB470 = {
    ov5_021ECE18,
    ov5_021ECE30,
    ov5_021ECE34,
    ov5_021ECE38,
    ov5_021ECE3C
};

const UnkStruct_ov5_021FB0F0 Unk_ov5_021FAF9C = {
    ov5_021ECA70,
    ov5_021ECA90,
    ov5_021ECABC,
    ov5_021ECAC4,
    ov5_021ECAF0
};

const UnkStruct_ov5_021FB0F0 Unk_ov5_021FB0B4 = {
    ov5_021ECB34,
    ov5_021ECB58,
    ov5_021ECB78,
    ov5_021ECAC4,
    ov5_021ECAF0
};

const UnkStruct_ov5_021FB0F0 dummy = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

const UnkStruct_ov5_021FB0F0 Unk_ov5_021FAFC4 = {
    ov5_021EC824,
    ov5_021EC8EC,
    ov5_021EC858,
    ov5_021EC86C,
    ov5_021EC898
};

const UnkStruct_ov5_021FB0F0 Unk_ov5_021FB028 = {
    ov5_021EC938,
    ov5_021EC9E8,
    ov5_021EC95C,
    ov5_021EC970,
    ov5_021EC9A0
};

const UnkStruct_ov5_021FB97C Unk_ov5_021FB97C[] = {
    { 0x0, &Unk_ov5_021FB0F0 },
    { 0x1, &Unk_ov5_021FAFD8 },
    { 0x2, &Unk_ov5_021FAFD8 },
    { 0x3, &Unk_ov5_021FAFD8 },
    { 0x4, &Unk_ov5_021FAFD8 },
    { 0x5, &Unk_ov5_021FAFD8 },
    { 0x6, &Unk_ov5_021FAFD8 },
    { 0x7, &Unk_ov5_021FAFD8 },
    { 0x8, &Unk_ov5_021FAFD8 },
    { 0x9, &Unk_ov5_021FAFD8 },
    { 0xA, &Unk_ov5_021FAFD8 },
    { 0xB, &Unk_ov5_021FAFD8 },
    { 0xC, &Unk_ov5_021FAFD8 },
    { 0xD, &Unk_ov5_021FAFD8 },
    { 0xE, &Unk_ov5_021FAFD8 },
    { 0xf, &Unk_ov5_021FAFD8 },
    { 0x10, &Unk_ov5_021FAFD8 },
    { 0x11, &Unk_ov5_021FAFD8 },
    { 0x12, &Unk_ov5_021FAFD8 },
    { 0x13, &Unk_ov5_021FAFD8 },
    { 0x14, &Unk_ov5_021FAFD8 },
    { 0x15, &Unk_ov5_021FAF88 },
    { 0x16, &Unk_ov5_021FAFD8 },
    { 0x17, &Unk_ov5_021FAFD8 },
    { 0x18, &Unk_ov5_021FAFD8 },
    { 0x19, &Unk_ov5_021FAFD8 },
    { 0x1A, &Unk_ov5_021FB08C },
    { 0x1B, &Unk_ov5_021FAFD8 },
    { 0x1C, &Unk_ov5_021FAFD8 },
    { 0x1D, &Unk_ov5_021FAFD8 },
    { 0x1E, &Unk_ov5_021FAFD8 },
    { 0x1f, &Unk_ov5_021FAFD8 },
    { 0x20, &Unk_ov5_021FAFD8 },
    { 0x21, &Unk_ov5_021FAFD8 },
    { 0x22, &Unk_ov5_021FAFD8 },
    { 0x23, &Unk_ov5_021FAFD8 },
    { 0x24, &Unk_ov5_021FAFD8 },
    { 0x25, &Unk_ov5_021FAFD8 },
    { 0x26, &Unk_ov5_021FAFD8 },
    { 0x27, &Unk_ov5_021FAFD8 },
    { 0x28, &Unk_ov5_021FAFD8 },
    { 0x29, &Unk_ov5_021FAFD8 },
    { 0x2A, &Unk_ov5_021FAFD8 },
    { 0x2B, &Unk_ov5_021FAFD8 },
    { 0x2C, &Unk_ov5_021FAFD8 },
    { 0x2D, &Unk_ov5_021FAFD8 },
    { 0x2E, &Unk_ov5_021FAFD8 },
    { 0x2f, &Unk_ov5_021FAFD8 },
    { 0x30, &Unk_ov5_021FAFD8 },
    { 0x31, &Unk_ov5_021FAFD8 },
    { 0x32, &Unk_ov5_021FAFD8 },
    { 0x33, &Unk_ov5_021FAFD8 },
    { 0x34, &Unk_ov5_021FAFD8 },
    { 0x35, &Unk_ov5_021FAFD8 },
    { 0x36, &Unk_ov5_021FAFD8 },
    { 0x37, &Unk_ov5_021FAFD8 },
    { 0x38, &Unk_ov5_021FAFD8 },
    { 0x39, &Unk_ov5_021FAFD8 },
    { 0x3A, &Unk_ov5_021FAFD8 },
    { 0x3B, &Unk_ov5_021FAFD8 },
    { 0x3C, &Unk_ov5_021FAFD8 },
    { 0x3D, &Unk_ov5_021FAFD8 },
    { 0x3E, &Unk_ov5_021FAFD8 },
    { 0x3f, &Unk_ov5_021FAFD8 },
    { 0x40, &Unk_ov5_021FAFD8 },
    { 0x41, &Unk_ov5_021FAFD8 },
    { 0x42, &Unk_ov5_021FAFD8 },
    { 0x43, &Unk_ov5_021FAFD8 },
    { 0x44, &Unk_ov5_021FAFD8 },
    { 0x45, &Unk_ov5_021FAFD8 },
    { 0x46, &Unk_ov5_021FAFD8 },
    { 0x47, &Unk_ov5_021FAFD8 },
    { 0x48, &Unk_ov5_021FAFD8 },
    { 0x49, &Unk_ov5_021FAFD8 },
    { 0x4A, &Unk_ov5_021FAFD8 },
    { 0x4B, &Unk_ov5_021FAFD8 },
    { 0x4C, &Unk_ov5_021FAFD8 },
    { 0x4D, &Unk_ov5_021FAFD8 },
    { 0x4E, &Unk_ov5_021FAFD8 },
    { 0x4f, &Unk_ov5_021FAFD8 },
    { 0x50, &Unk_ov5_021FAFD8 },
    { 0x51, &Unk_ov5_021FAFD8 },
    { 0x52, &Unk_ov5_021FAFD8 },
    { 0x53, &Unk_ov5_021FAFD8 },
    { 0x54, &Unk_ov5_021FB0A0 },
    { 0x55, &Unk_ov5_021FB0A0 },
    { 0x56, &Unk_ov5_021FB0A0 },
    { 0x57, &Unk_ov5_021FB0A0 },
    { 0x58, &Unk_ov5_021FAFD8 },
    { 0x59, &Unk_ov5_021FAFD8 },
    { 0x5A, &Unk_ov5_021FAFD8 },
    { 0x5B, &Unk_ov5_021FB000 },
    { 0x5C, &Unk_ov5_021FB000 },
    { 0x5D, &Unk_ov5_021FB000 },
    { 0x5E, &Unk_ov5_021FB000 },
    { 0x5f, &Unk_ov5_021FB000 },
    { 0x60, &Unk_ov5_021FB000 },
    { 0x61, &Unk_ov5_021FB0F0 },
    { 0x62, &Unk_ov5_021FAF88 },
    { 0x63, &Unk_ov5_021FAFD8 },
    { 0x64, &BerryPatchRenderer },
    { 0x76, &Unk_ov5_021FB050 },
    { 0x78, &Unk_ov5_021FAFD8 },
    { 0x79, &Unk_ov5_021FAFD8 },
    { 0x7A, &Unk_ov5_021FAFD8 },
    { 0x7B, &Unk_ov5_021FAFD8 },
    { 0x7C, &Unk_ov5_021FAFD8 },
    { 0x7D, &Unk_ov5_021FAFD8 },
    { 0x7E, &Unk_ov5_021FAFD8 },
    { 0x7f, &Unk_ov5_021FAFD8 },
    { 0x80, &Unk_ov5_021FAFD8 },
    { 0x81, &Unk_ov5_021FAFD8 },
    { 0x82, &Unk_ov5_021FAFD8 },
    { 0x83, &Unk_ov5_021FAFD8 },
    { 0x84, &Unk_ov5_021FAFD8 },
    { 0x85, &Unk_ov5_021FAFD8 },
    { 0x86, &Unk_ov5_021FAFD8 },
    { 0x87, &Unk_ov5_021FAFD8 },
    { 0x88, &Unk_ov5_021FAFD8 },
    { 0x89, &Unk_ov5_021FAFD8 },
    { 0x8A, &Unk_ov5_021FAFD8 },
    { 0x8B, &Unk_ov5_021FAFD8 },
    { 0x8C, &Unk_ov5_021FAFD8 },
    { 0x8D, &Unk_ov5_021FAFD8 },
    { 0x8E, &Unk_ov5_021FAFD8 },
    { 0x8f, &Unk_ov5_021FAFD8 },
    { 0x90, &Unk_ov5_021FAFD8 },
    { 0x91, &Unk_ov5_021FAFD8 },
    { 0x92, &Unk_ov5_021FAFD8 },
    { 0x93, &Unk_ov5_021FAFD8 },
    { 0x94, &Unk_ov5_021FAFD8 },
    { 0x95, &Unk_ov5_021FAFD8 },
    { 0x96, &Unk_ov5_021FAFD8 },
    { 0x97, &Unk_ov5_021FB0B4 },
    { 0x98, &Unk_ov5_021FB0B4 },
    { 0x99, &Unk_ov5_021FB0B4 },
    { 0x9A, &Unk_ov5_021FAF9C },
    { 0x9B, &Unk_ov5_021FAF9C },
    { 0x9C, &Unk_ov5_021FB03C },
    { 0x9D, &Unk_ov5_021FB03C },
    { 0x9E, &Unk_ov5_021FAFD8 },
    { 0x9f, &Unk_ov5_021FB03C },
    { 0xA0, &Unk_ov5_021FB03C },
    { 0xA1, &Unk_ov5_021FB03C },
    { 0xA2, &Unk_ov5_021FAFD8 },
    { 0xA3, &Unk_ov5_021FAFD8 },
    { 0xA4, &Unk_ov5_021FAFD8 },
    { 0xA5, &Unk_ov5_021FAFD8 },
    { 0xA6, &Unk_ov5_021FAFD8 },
    { 0xA7, &Unk_ov5_021FAFD8 },
    { 0xA8, &Unk_ov5_021FAFD8 },
    { 0xA9, &Unk_ov5_021FAFD8 },
    { 0xAA, &Unk_ov5_021FAFD8 },
    { 0xAB, &Unk_ov5_021FAFD8 },
    { 0xAC, &Unk_ov5_021FAFD8 },
    { 0xAD, &Unk_ov5_021FB078 },
    { 0xAE, &Unk_ov5_021FB0A0 },
    { 0xaf, &Unk_ov5_021FAFD8 },
    { 0xB0, &Unk_ov5_021FAFB0 },
    { 0xB1, &Unk_ov5_021FAFB0 },
    { 0xB4, &Unk_ov5_021FAFEC },
    { 0xB5, &Unk_ov5_021FAFEC },
    { 0xB2, &Unk_ov5_021FAF60 },
    { 0xB3, &Unk_ov5_021FAF60 },
    { 0xB6, &Unk_ov5_021FB0A0 },
    { 0xB7, &Unk_ov5_021FB000 },
    { 0xB8, &Unk_ov5_021FB0A0 },
    { 0xB9, &Unk_ov5_021FAFD8 },
    { 0xBA, &Unk_ov5_021FB0F0 },
    { 0xBB, &Unk_ov5_021FB0F0 },
    { 0xBC, &Unk_ov5_021FB014 },
    { 0xBD, &Unk_ov5_021FB014 },
    { 0xBE, &Unk_ov5_021FAFD8 },
    { 0xbf, &Unk_ov5_021FAFD8 },
    { 0xC0, &Unk_ov5_021FAFD8 },
    { 0xC1, &Unk_ov5_021FAFD8 },
    { 0xC2, &Unk_ov5_021FAFD8 },
    { 0xC3, &Unk_ov5_021FB064 },
    { 0xC4, &Unk_ov5_021FB0DC },
    { 0xC5, &Unk_ov5_021FB0DC },
    { 0xC6, &Unk_ov5_021FAFB0 },
    { 0xC7, &Unk_ov5_021FAFB0 },
    { 0xC8, &Unk_ov5_021FB0C8 },
    { 0xC9, &Unk_ov5_021FB0C8 },
    { 0xCA, &Unk_ov5_021FB0A0 },
    { 0xCB, &Unk_ov5_021FB0A0 },
    { 0xCC, &Unk_ov5_021FAFD8 },
    { 0xCD, &Unk_ov5_021FAFD8 },
    { 0xCE, &Unk_ov5_021FAFD8 },
    { 0xcf, &Unk_ov5_021FAFD8 },
    { 0xD0, &Unk_ov5_021FAFD8 },
    { 0xD1, &Unk_ov5_021FB000 },
    { 0xD2, &Unk_ov5_021FB0F0 },
    { 0xD3, &Unk_ov5_021FB0F0 },
    { 0xD4, &Unk_ov5_021FB0F0 },
    { 0xD5, &Unk_ov5_021FAFD8 },
    { 0xD6, &Unk_ov5_021FAFD8 },
    { 0xD7, &Unk_ov5_021FAFD8 },
    { 0xD8, &Unk_ov5_021FAFD8 },
    { 0xD9, &Unk_ov5_021FAFD8 },
    { 0xDA, &Unk_ov5_021FAFD8 },
    { 0xDB, &Unk_ov5_021FAFD8 },
    { 0xDC, &Unk_ov5_021FAFD8 },
    { 0xDD, &Unk_ov5_021FAFD8 },
    { 0xDE, &Unk_ov5_021FAFD8 },
    { 0xdf, &Unk_ov5_021FAFD8 },
    { 0xE0, &Unk_ov5_021FAFD8 },
    { 0xE1, &Unk_ov5_021FAFD8 },
    { 0xE2, &Unk_ov5_021FAFD8 },
    { 0xE3, &Unk_ov5_021FAFD8 },
    { 0xE4, &Unk_ov5_021FAFD8 },
    { 0xE5, &Unk_ov5_021FAFD8 },
    { 0xE6, &Unk_ov5_021FB03C },
    { 0xE7, &Unk_ov5_021FAFD8 },
    { 0xE8, &Unk_ov5_021FAFD8 },
    { 0xE9, &Unk_ov5_021FAFD8 },
    { 0xEA, &Unk_ov5_021FAFD8 },
    { 0xEB, &Unk_ov5_021FAFD8 },
    { 0xEC, &Unk_ov5_021FAFD8 },
    { 0xED, &Unk_ov5_021FAFD8 },
    { 0xEE, &Unk_ov5_021FAFD8 },
    { 0xef, &Unk_ov5_021FAFD8 },
    { 0xf0, &Unk_ov5_021FAFD8 },
    { 0xf1, &Unk_ov5_021FAFD8 },
    { 0xf2, &Unk_ov5_021FAFD8 },
    { 0xf3, &Unk_ov5_021FAFD8 },
    { 0xf4, &Unk_ov5_021FAFD8 },
    { 0xf5, &Unk_ov5_021FAFD8 },
    { 0xf6, &Unk_ov5_021FAFD8 },
    { 0xf7, &Unk_ov5_021FAFD8 },
    { 0xf8, &Unk_ov5_021FB0A0 },
    { 0xf9, &Unk_ov5_021FB0A0 },
    { 0xfa, &Unk_ov5_021FB0A0 },
    { 0xfb, &Unk_ov5_021FB0A0 },
    { 0xfc, &Unk_ov5_021FB0F0 },
    { 0xfd, &Unk_ov5_021FB0F0 },
    { 0xfe, &Unk_ov5_021FB0F0 },
    { 0xff, &Unk_ov5_021FB0F0 },
    { 0x100, &Unk_ov5_021FAFB0 },
    { 0x101, &Unk_ov5_021FAFB0 },
    { 0x102, &Unk_ov5_021FAF60 },
    { 0x103, &Unk_ov5_021FAF60 },
    { 0x104, &Unk_ov5_021FAFB0 },
    { 0x105, &Unk_ov5_021FAFB0 },
    { 0x106, &Unk_ov5_021FB000 },
    { 0x107, &Unk_ov5_021FB0F0 },
    { 0x108, &Unk_ov5_021FAFC4 },
    { 0x109, &Unk_ov5_021FB028 },
    { 0x10A, &Unk_ov5_021FB028 },
    { 0x10B, &Unk_ov5_021FB028 },
    { 0x10C, &Unk_ov5_021FAFB0 },
    { 0x10D, &Unk_ov5_021FAFB0 },
    { 0x10E, &Unk_ov5_021FB0DC },
    { 0x10f, &Unk_ov5_021FB0DC },
    { 0x110, &Unk_ov5_021FAFB0 },
    { 0x111, &Unk_ov5_021FAFB0 },
    { 0x112, &Unk_ov5_021FB0DC },
    { 0x113, &Unk_ov5_021FB0DC },
    { OBJ_EVENT_GFX_PKMN_BULBASAUR, &Unk_ov5_FollowerMon },  // SPECIES_BULBASAUR
    { OBJ_EVENT_GFX_PKMN_IVYSAUR, &Unk_ov5_FollowerMon },  // SPECIES_IVYSAUR
    { OBJ_EVENT_GFX_PKMN_VENUSAUR, &Unk_ov5_FollowerMon },  // SPECIES_VENUSAUR
    { OBJ_EVENT_GFX_PKMN_VENUSAUR_F, &Unk_ov5_FollowerMon },  // female
    { OBJ_EVENT_GFX_PKMN_CHARMANDER, &Unk_ov5_FollowerMon },  // SPECIES_CHARMANDER
    { OBJ_EVENT_GFX_PKMN_CHARMELEON, &Unk_ov5_FollowerMon },  // SPECIES_CHARMELEON
    { OBJ_EVENT_GFX_PKMN_CHARIZARD, &Unk_ov5_FollowerMon },  // SPECIES_CHARIZARD
    { OBJ_EVENT_GFX_PKMN_SQUIRTLE, &Unk_ov5_FollowerMon },  // SPECIES_SQUIRTLE
    { OBJ_EVENT_GFX_PKMN_WARTORTLE, &Unk_ov5_FollowerMon },  // SPECIES_WARTORTLE
    { OBJ_EVENT_GFX_PKMN_BLASTOISE, &Unk_ov5_FollowerMon },  // SPECIES_BLASTOISE
    { OBJ_EVENT_GFX_PKMN_CATERPIE, &Unk_ov5_FollowerMon },  // SPECIES_CATERPIE
    { OBJ_EVENT_GFX_PKMN_METAPOD, &Unk_ov5_FollowerMon },  // SPECIES_METAPOD
    { OBJ_EVENT_GFX_PKMN_BUTTERFREE, &Unk_ov5_FollowerMon },  // SPECIES_BUTTERFREE
    { OBJ_EVENT_GFX_PKMN_WEEDLE, &Unk_ov5_FollowerMon },  // SPECIES_WEEDLE
    { OBJ_EVENT_GFX_PKMN_KAKUNA, &Unk_ov5_FollowerMon },  // SPECIES_KAKUNA
    { OBJ_EVENT_GFX_PKMN_BEEDRILL, &Unk_ov5_FollowerMon },  // SPECIES_BEEDRILL
    { OBJ_EVENT_GFX_PKMN_PIDGEY, &Unk_ov5_FollowerMon },  // SPECIES_PIDGEY
    { OBJ_EVENT_GFX_PKMN_PIDGEOTTO, &Unk_ov5_FollowerMon },  // SPECIES_PIDGEOTTO
    { OBJ_EVENT_GFX_PKMN_PIDGEOT, &Unk_ov5_FollowerMon },  // SPECIES_PIDGEOT
    { OBJ_EVENT_GFX_PKMN_RATTATA, &Unk_ov5_FollowerMon },  // SPECIES_RATTATA
    { OBJ_EVENT_GFX_PKMN_RATICATE, &Unk_ov5_FollowerMon },  // SPECIES_RATICATE
    { OBJ_EVENT_GFX_PKMN_SPEAROW, &Unk_ov5_FollowerMon },  // SPECIES_SPEAROW
    { OBJ_EVENT_GFX_PKMN_FEAROW, &Unk_ov5_FollowerMon },  // SPECIES_FEAROW
    { OBJ_EVENT_GFX_PKMN_EKANS, &Unk_ov5_FollowerMon },  // SPECIES_EKANS
    { OBJ_EVENT_GFX_PKMN_ARBOK, &Unk_ov5_FollowerMon },  // SPECIES_ARBOK
    { OBJ_EVENT_GFX_PKMN_PIKACHU, &Unk_ov5_FollowerMon },  // SPECIES_PIKACHU
    { OBJ_EVENT_GFX_PKMN_PIKACHU_F, &Unk_ov5_FollowerMon },  // female
    { OBJ_EVENT_GFX_PKMN_RAICHU, &Unk_ov5_FollowerMon },  // SPECIES_RAICHU
    { OBJ_EVENT_GFX_PKMN_SANDSHREW, &Unk_ov5_FollowerMon },  // SPECIES_SANDSHREW
    { OBJ_EVENT_GFX_PKMN_SANDSLASH, &Unk_ov5_FollowerMon },  // SPECIES_SANDSLASH
    { OBJ_EVENT_GFX_PKMN_NIDORAN_F, &Unk_ov5_FollowerMon },  // SPECIES_NIDORAN_F
    { OBJ_EVENT_GFX_PKMN_NIDORINA, &Unk_ov5_FollowerMon },  // SPECIES_NIDORINA
    { OBJ_EVENT_GFX_PKMN_NIDOQUEEN, &Unk_ov5_FollowerMon },  // SPECIES_NIDOQUEEN
    { OBJ_EVENT_GFX_PKMN_NIDORAN_M, &Unk_ov5_FollowerMon },  // SPECIES_NIDORAN_M
    { OBJ_EVENT_GFX_PKMN_NIDORINO, &Unk_ov5_FollowerMon },  // SPECIES_NIDORINO
    { OBJ_EVENT_GFX_PKMN_NIDOKING, &Unk_ov5_FollowerMon },  // SPECIES_NIDOKING
    { OBJ_EVENT_GFX_PKMN_CLEFAIRY, &Unk_ov5_FollowerMon },  // SPECIES_CLEFAIRY
    { OBJ_EVENT_GFX_PKMN_CLEFABLE, &Unk_ov5_FollowerMon },  // SPECIES_CLEFABLE
    { OBJ_EVENT_GFX_PKMN_VULPIX, &Unk_ov5_FollowerMon },  // SPECIES_VULPIX
    { OBJ_EVENT_GFX_PKMN_NINETALES, &Unk_ov5_FollowerMon },  // SPECIES_NINETALES
    { OBJ_EVENT_GFX_PKMN_JIGGLYPUFF, &Unk_ov5_FollowerMon },  // SPECIES_JIGGLYPUFF
    { OBJ_EVENT_GFX_PKMN_WIGGLYTUFF, &Unk_ov5_FollowerMon },  // SPECIES_WIGGLYTUFF
    { OBJ_EVENT_GFX_PKMN_ZUBAT, &Unk_ov5_FollowerMon },  // SPECIES_ZUBAT
    { OBJ_EVENT_GFX_PKMN_GOLBAT, &Unk_ov5_FollowerMon },  // SPECIES_GOLBAT
    { OBJ_EVENT_GFX_PKMN_ODDISH, &Unk_ov5_FollowerMon },  // SPECIES_ODDISH
    { OBJ_EVENT_GFX_PKMN_GLOOM, &Unk_ov5_FollowerMon },  // SPECIES_GLOOM
    { OBJ_EVENT_GFX_PKMN_VILEPLUME, &Unk_ov5_FollowerMon },  // SPECIES_VILEPLUME
    { OBJ_EVENT_GFX_PKMN_PARAS, &Unk_ov5_FollowerMon },  // SPECIES_PARAS
    { OBJ_EVENT_GFX_PKMN_PARASECT, &Unk_ov5_FollowerMon },  // SPECIES_PARASECT
    { OBJ_EVENT_GFX_PKMN_VENONAT, &Unk_ov5_FollowerMon },  // SPECIES_VENONAT
    { OBJ_EVENT_GFX_PKMN_VENOMOTH, &Unk_ov5_FollowerMon },  // SPECIES_VENOMOTH
    { OBJ_EVENT_GFX_PKMN_DIGLETT, &Unk_ov5_FollowerMon },  // SPECIES_DIGLETT
    { OBJ_EVENT_GFX_PKMN_DUGTRIO, &Unk_ov5_FollowerMon },  // SPECIES_DUGTRIO
    { OBJ_EVENT_GFX_PKMN_MEOWTH, &Unk_ov5_FollowerMon },  // SPECIES_MEOWTH
    { OBJ_EVENT_GFX_PKMN_PERSIAN, &Unk_ov5_FollowerMon },  // SPECIES_PERSIAN
    { OBJ_EVENT_GFX_PKMN_PSYDUCK, &Unk_ov5_FollowerMon },  // SPECIES_PSYDUCK
    { OBJ_EVENT_GFX_PKMN_GOLDUCK, &Unk_ov5_FollowerMon },  // SPECIES_GOLDUCK
    { OBJ_EVENT_GFX_PKMN_MANKEY, &Unk_ov5_FollowerMon },  // SPECIES_MANKEY
    { OBJ_EVENT_GFX_PKMN_PRIMEAPE, &Unk_ov5_FollowerMon },  // SPECIES_PRIMEAPE
    { OBJ_EVENT_GFX_PKMN_GROWLITHE, &Unk_ov5_FollowerMon },  // SPECIES_GROWLITHE
    { OBJ_EVENT_GFX_PKMN_ARCANINE, &Unk_ov5_FollowerMon },  // SPECIES_ARCANINE
    { OBJ_EVENT_GFX_PKMN_POLIWAG, &Unk_ov5_FollowerMon },  // SPECIES_POLIWAG
    { OBJ_EVENT_GFX_PKMN_POLIWHIRL, &Unk_ov5_FollowerMon },  // SPECIES_POLIWHIRL
    { OBJ_EVENT_GFX_PKMN_POLIWRATH, &Unk_ov5_FollowerMon },  // SPECIES_POLIWRATH
    { OBJ_EVENT_GFX_PKMN_ABRA, &Unk_ov5_FollowerMon },  // SPECIES_ABRA
    { OBJ_EVENT_GFX_PKMN_KADABRA, &Unk_ov5_FollowerMon },  // SPECIES_KADABRA
    { OBJ_EVENT_GFX_PKMN_ALAKAZAM, &Unk_ov5_FollowerMon },  // SPECIES_ALAKAZAM
    { OBJ_EVENT_GFX_PKMN_MACHOP, &Unk_ov5_FollowerMon },  // SPECIES_MACHOP
    { OBJ_EVENT_GFX_PKMN_MACHOKE, &Unk_ov5_FollowerMon },  // SPECIES_MACHOKE
    { OBJ_EVENT_GFX_PKMN_MACHAMP, &Unk_ov5_FollowerMon },  // SPECIES_MACHAMP
    { OBJ_EVENT_GFX_PKMN_BELLSPROUT, &Unk_ov5_FollowerMon },  // SPECIES_BELLSPROUT
    { OBJ_EVENT_GFX_PKMN_WEEPINBELL, &Unk_ov5_FollowerMon },  // SPECIES_WEEPINBELL
    { OBJ_EVENT_GFX_PKMN_VICTREEBEL, &Unk_ov5_FollowerMon },  // SPECIES_VICTREEBEL
    { OBJ_EVENT_GFX_PKMN_TENTACOOL, &Unk_ov5_FollowerMon },  // SPECIES_TENTACOOL
    { OBJ_EVENT_GFX_PKMN_TENTACRUEL, &Unk_ov5_FollowerMon },  // SPECIES_TENTACRUEL
    { OBJ_EVENT_GFX_PKMN_GEODUDE, &Unk_ov5_FollowerMon },  // SPECIES_GEODUDE
    { OBJ_EVENT_GFX_PKMN_GRAVELER, &Unk_ov5_FollowerMon },  // SPECIES_GRAVELER
    { OBJ_EVENT_GFX_PKMN_GOLEM, &Unk_ov5_FollowerMon },  // SPECIES_GOLEM
    { OBJ_EVENT_GFX_PKMN_PONYTA, &Unk_ov5_FollowerMon },  // SPECIES_PONYTA
    { OBJ_EVENT_GFX_PKMN_RAPIDASH, &Unk_ov5_FollowerMon },  // SPECIES_RAPIDASH
    { OBJ_EVENT_GFX_PKMN_SLOWPOKE, &Unk_ov5_FollowerMon },  // SPECIES_SLOWPOKE
    { OBJ_EVENT_GFX_PKMN_SLOWBRO, &Unk_ov5_FollowerMon },  // SPECIES_SLOWBRO
    { OBJ_EVENT_GFX_PKMN_MAGNEMITE, &Unk_ov5_FollowerMon },  // SPECIES_MAGNEMITE
    { OBJ_EVENT_GFX_PKMN_MAGNETON, &Unk_ov5_FollowerMon },  // SPECIES_MAGNETON
    { OBJ_EVENT_GFX_PKMN_FARFETCHD, &Unk_ov5_FollowerMon },  // SPECIES_FARFETCHD
    { OBJ_EVENT_GFX_PKMN_DODUO, &Unk_ov5_FollowerMon },  // SPECIES_DODUO
    { OBJ_EVENT_GFX_PKMN_DODRIO, &Unk_ov5_FollowerMon },  // SPECIES_DODRIO
    { OBJ_EVENT_GFX_PKMN_SEEL, &Unk_ov5_FollowerMon },  // SPECIES_SEEL
    { OBJ_EVENT_GFX_PKMN_DEWGONG, &Unk_ov5_FollowerMon },  // SPECIES_DEWGONG
    { OBJ_EVENT_GFX_PKMN_GRIMER, &Unk_ov5_FollowerMon },  // SPECIES_GRIMER
    { OBJ_EVENT_GFX_PKMN_MUK, &Unk_ov5_FollowerMon },  // SPECIES_MUK
    { OBJ_EVENT_GFX_PKMN_SHELLDER, &Unk_ov5_FollowerMon },  // SPECIES_SHELLDER
    { OBJ_EVENT_GFX_PKMN_CLOYSTER, &Unk_ov5_FollowerMon },  // SPECIES_CLOYSTER
    { OBJ_EVENT_GFX_PKMN_GASTLY, &Unk_ov5_FollowerMon },  // SPECIES_GASTLY
    { OBJ_EVENT_GFX_PKMN_HAUNTER, &Unk_ov5_FollowerMon },  // SPECIES_HAUNTER
    { OBJ_EVENT_GFX_PKMN_GENGAR, &Unk_ov5_FollowerMon },  // SPECIES_GENGAR
    { OBJ_EVENT_GFX_PKMN_ONIX, &Unk_ov5_FollowerMon },  // SPECIES_ONIX
    { OBJ_EVENT_GFX_PKMN_DROWZEE, &Unk_ov5_FollowerMon },  // SPECIES_DROWZEE
    { OBJ_EVENT_GFX_PKMN_HYPNO, &Unk_ov5_FollowerMon },  // SPECIES_HYPNO
    { OBJ_EVENT_GFX_PKMN_KRABBY, &Unk_ov5_FollowerMon },  // SPECIES_KRABBY
    { OBJ_EVENT_GFX_PKMN_KINGLER, &Unk_ov5_FollowerMon },  // SPECIES_KINGLER
    { OBJ_EVENT_GFX_PKMN_VOLTORB, &Unk_ov5_FollowerMon },  // SPECIES_VOLTORB
    { OBJ_EVENT_GFX_PKMN_ELECTRODE, &Unk_ov5_FollowerMon },  // SPECIES_ELECTRODE
    { OBJ_EVENT_GFX_PKMN_EXEGGCUTE, &Unk_ov5_FollowerMon },  // SPECIES_EXEGGCUTE
    { OBJ_EVENT_GFX_PKMN_EXEGGUTOR, &Unk_ov5_FollowerMon },  // SPECIES_EXEGGUTOR
    { OBJ_EVENT_GFX_PKMN_CUBONE, &Unk_ov5_FollowerMon },  // SPECIES_CUBONE
    { OBJ_EVENT_GFX_PKMN_MAROWAK, &Unk_ov5_FollowerMon },  // SPECIES_MAROWAK
    { OBJ_EVENT_GFX_PKMN_HITMONLEE, &Unk_ov5_FollowerMon },  // SPECIES_HITMONLEE
    { OBJ_EVENT_GFX_PKMN_HITMONCHAN, &Unk_ov5_FollowerMon },  // SPECIES_HITMONCHAN
    { OBJ_EVENT_GFX_PKMN_LICKITUNG, &Unk_ov5_FollowerMon },  // SPECIES_LICKITUNG
    { OBJ_EVENT_GFX_PKMN_KOFFING, &Unk_ov5_FollowerMon },  // SPECIES_KOFFING
    { OBJ_EVENT_GFX_PKMN_WEEZING, &Unk_ov5_FollowerMon },  // SPECIES_WEEZING
    { OBJ_EVENT_GFX_PKMN_RHYHORN, &Unk_ov5_FollowerMon },  // SPECIES_RHYHORN
    { OBJ_EVENT_GFX_PKMN_RHYDON, &Unk_ov5_FollowerMon },  // SPECIES_RHYDON
    { OBJ_EVENT_GFX_PKMN_CHANSEY, &Unk_ov5_FollowerMon },  // SPECIES_CHANSEY
    { OBJ_EVENT_GFX_PKMN_TANGELA, &Unk_ov5_FollowerMon },  // SPECIES_TANGELA
    { OBJ_EVENT_GFX_PKMN_KANGASKHAN, &Unk_ov5_FollowerMon },  // SPECIES_KANGASKHAN
    { OBJ_EVENT_GFX_PKMN_HORSEA, &Unk_ov5_FollowerMon },  // SPECIES_HORSEA
    { OBJ_EVENT_GFX_PKMN_SEADRA, &Unk_ov5_FollowerMon },  // SPECIES_SEADRA
    { OBJ_EVENT_GFX_PKMN_GOLDEEN, &Unk_ov5_FollowerMon },  // SPECIES_GOLDEEN
    { OBJ_EVENT_GFX_PKMN_SEAKING, &Unk_ov5_FollowerMon },  // SPECIES_SEAKING
    { OBJ_EVENT_GFX_PKMN_STARYU, &Unk_ov5_FollowerMon },  // SPECIES_STARYU
    { OBJ_EVENT_GFX_PKMN_STARMIE, &Unk_ov5_FollowerMon },  // SPECIES_STARMIE
    { OBJ_EVENT_GFX_PKMN_MR_MIME, &Unk_ov5_FollowerMon },  // SPECIES_MR_MIME
    { OBJ_EVENT_GFX_PKMN_SCYTHER, &Unk_ov5_FollowerMon },  // SPECIES_SCYTHER
    { OBJ_EVENT_GFX_PKMN_JYNX, &Unk_ov5_FollowerMon },  // SPECIES_JYNX
    { OBJ_EVENT_GFX_PKMN_ELECTABUZZ, &Unk_ov5_FollowerMon },  // SPECIES_ELECTABUZZ
    { OBJ_EVENT_GFX_PKMN_MAGMAR, &Unk_ov5_FollowerMon },  // SPECIES_MAGMAR
    { OBJ_EVENT_GFX_PKMN_PINSIR, &Unk_ov5_FollowerMon },  // SPECIES_PINSIR
    { OBJ_EVENT_GFX_PKMN_TAUROS, &Unk_ov5_FollowerMon },  // SPECIES_TAUROS
    { OBJ_EVENT_GFX_PKMN_MAGIKARP, &Unk_ov5_FollowerMon },  // SPECIES_MAGIKARP
    { OBJ_EVENT_GFX_PKMN_GYARADOS, &Unk_ov5_FollowerMon },  // SPECIES_GYARADOS
    { OBJ_EVENT_GFX_PKMN_LAPRAS, &Unk_ov5_FollowerMon },  // SPECIES_LAPRAS
    { OBJ_EVENT_GFX_PKMN_DITTO, &Unk_ov5_FollowerMon },  // SPECIES_DITTO
    { OBJ_EVENT_GFX_PKMN_EEVEE, &Unk_ov5_FollowerMon },  // SPECIES_EEVEE
    { OBJ_EVENT_GFX_PKMN_VAPOREON, &Unk_ov5_FollowerMon },  // SPECIES_VAPOREON
    { OBJ_EVENT_GFX_PKMN_JOLTEON, &Unk_ov5_FollowerMon },  // SPECIES_JOLTEON
    { OBJ_EVENT_GFX_PKMN_FLAREON, &Unk_ov5_FollowerMon },  // SPECIES_FLAREON
    { OBJ_EVENT_GFX_PKMN_PORYGON, &Unk_ov5_FollowerMon },  // SPECIES_PORYGON
    { OBJ_EVENT_GFX_PKMN_OMANYTE, &Unk_ov5_FollowerMon },  // SPECIES_OMANYTE
    { OBJ_EVENT_GFX_PKMN_OMASTAR, &Unk_ov5_FollowerMon },  // SPECIES_OMASTAR
    { OBJ_EVENT_GFX_PKMN_KABUTO, &Unk_ov5_FollowerMon },  // SPECIES_KABUTO
    { OBJ_EVENT_GFX_PKMN_KABUTOPS, &Unk_ov5_FollowerMon },  // SPECIES_KABUTOPS
    { OBJ_EVENT_GFX_PKMN_AERODACTYL, &Unk_ov5_FollowerMon },  // SPECIES_AERODACTYL
    { OBJ_EVENT_GFX_PKMN_SNORLAX, &Unk_ov5_FollowerMon },  // SPECIES_SNORLAX
    { OBJ_EVENT_GFX_PKMN_ARTICUNO, &Unk_ov5_FollowerMon },  // SPECIES_ARTICUNO
    { OBJ_EVENT_GFX_PKMN_ZAPDOS, &Unk_ov5_FollowerMon },  // SPECIES_ZAPDOS
    { OBJ_EVENT_GFX_PKMN_MOLTRES, &Unk_ov5_FollowerMon },  // SPECIES_MOLTRES
    { OBJ_EVENT_GFX_PKMN_DRATINI, &Unk_ov5_FollowerMon },  // SPECIES_DRATINI
    { OBJ_EVENT_GFX_PKMN_DRAGONAIR, &Unk_ov5_FollowerMon },  // SPECIES_DRAGONAIR
    { OBJ_EVENT_GFX_PKMN_DRAGONITE, &Unk_ov5_FollowerMon },  // SPECIES_DRAGONITE
    { OBJ_EVENT_GFX_PKMN_MEWTWO, &Unk_ov5_FollowerMon },  // SPECIES_MEWTWO
    { OBJ_EVENT_GFX_PKMN_MEW, &Unk_ov5_FollowerMon },  // SPECIES_MEW
    { OBJ_EVENT_GFX_PKMN_CHIKORITA, &Unk_ov5_FollowerMon },  // SPECIES_CHIKORITA
    { OBJ_EVENT_GFX_PKMN_BAYLEEF, &Unk_ov5_FollowerMon },  // SPECIES_BAYLEEF
    { OBJ_EVENT_GFX_PKMN_BAYLEEF_F, &Unk_ov5_FollowerMon },  // female
    { OBJ_EVENT_GFX_PKMN_CYNDAQUIL, &Unk_ov5_FollowerMon },  // SPECIES_CYNDAQUIL
    { OBJ_EVENT_GFX_PKMN_QUILAVA, &Unk_ov5_FollowerMon },  // SPECIES_QUILAVA
    { OBJ_EVENT_GFX_PKMN_TYPHLOSION, &Unk_ov5_FollowerMon },  // SPECIES_TYPHLOSION
    { OBJ_EVENT_GFX_PKMN_TOTODILE, &Unk_ov5_FollowerMon },  // SPECIES_TOTODILE
    { OBJ_EVENT_GFX_PKMN_CROCONAW, &Unk_ov5_FollowerMon },  // SPECIES_CROCONAW
    { OBJ_EVENT_GFX_PKMN_FERALIGATR, &Unk_ov5_FollowerMon },  // SPECIES_FERALIGATR
    { OBJ_EVENT_GFX_PKMN_SENTRET, &Unk_ov5_FollowerMon },  // SPECIES_SENTRET
    { OBJ_EVENT_GFX_PKMN_FURRET, &Unk_ov5_FollowerMon },  // SPECIES_FURRET
    { OBJ_EVENT_GFX_PKMN_HOOTHOOT, &Unk_ov5_FollowerMon },  // SPECIES_HOOTHOOT
    { OBJ_EVENT_GFX_PKMN_NOCTOWL, &Unk_ov5_FollowerMon },  // SPECIES_NOCTOWL
    { OBJ_EVENT_GFX_PKMN_LEDYBA, &Unk_ov5_FollowerMon },  // SPECIES_LEDYBA
    { OBJ_EVENT_GFX_PKMN_LEDIAN, &Unk_ov5_FollowerMon },  // SPECIES_LEDIAN
    { OBJ_EVENT_GFX_PKMN_SPINARAK, &Unk_ov5_FollowerMon },  // SPECIES_SPINARAK
    { OBJ_EVENT_GFX_PKMN_ARIADOS, &Unk_ov5_FollowerMon },  // SPECIES_ARIADOS
    { OBJ_EVENT_GFX_PKMN_CROBAT, &Unk_ov5_FollowerMon },  // SPECIES_CROBAT
    { OBJ_EVENT_GFX_PKMN_CHINCHOU, &Unk_ov5_FollowerMon },  // SPECIES_CHINCHOU
    { OBJ_EVENT_GFX_PKMN_LANTURN, &Unk_ov5_FollowerMon },  // SPECIES_LANTURN
    { OBJ_EVENT_GFX_PKMN_PICHU, &Unk_ov5_FollowerMon },  // SPECIES_PICHU
    { OBJ_EVENT_GFX_PKMN_CLEFFA, &Unk_ov5_FollowerMon },  // SPECIES_CLEFFA
    { OBJ_EVENT_GFX_PKMN_IGGLYBUFF, &Unk_ov5_FollowerMon },  // SPECIES_IGGLYBUFF
    { OBJ_EVENT_GFX_PKMN_TOGEPI, &Unk_ov5_FollowerMon },  // SPECIES_TOGEPI
    { OBJ_EVENT_GFX_PKMN_TOGETIC, &Unk_ov5_FollowerMon },  // SPECIES_TOGETIC
    { OBJ_EVENT_GFX_PKMN_NATU, &Unk_ov5_FollowerMon },  // SPECIES_NATU
    { OBJ_EVENT_GFX_PKMN_XATU, &Unk_ov5_FollowerMon },  // SPECIES_XATU
    { OBJ_EVENT_GFX_PKMN_MAREEP, &Unk_ov5_FollowerMon },  // SPECIES_MAREEP
    { OBJ_EVENT_GFX_PKMN_FLAAFFY, &Unk_ov5_FollowerMon },  // SPECIES_FLAAFFY
    { OBJ_EVENT_GFX_PKMN_AMPHAROS, &Unk_ov5_FollowerMon },  // SPECIES_AMPHAROS
    { OBJ_EVENT_GFX_PKMN_BELLOSSOM, &Unk_ov5_FollowerMon },  // SPECIES_BELLOSSOM
    { OBJ_EVENT_GFX_PKMN_MARILL, &Unk_ov5_FollowerMon },  // SPECIES_MARILL
    { OBJ_EVENT_GFX_PKMN_AZUMARILL, &Unk_ov5_FollowerMon },  // SPECIES_AZUMARILL
    { OBJ_EVENT_GFX_PKMN_SUDOWOODO, &Unk_ov5_FollowerMon },  // SPECIES_SUDOWOODO
    { OBJ_EVENT_GFX_PKMN_POLITOED, &Unk_ov5_FollowerMon },  // SPECIES_POLITOED
    { OBJ_EVENT_GFX_PKMN_HOPPIP, &Unk_ov5_FollowerMon },  // SPECIES_HOPPIP
    { OBJ_EVENT_GFX_PKMN_SKIPLOOM, &Unk_ov5_FollowerMon },  // SPECIES_SKIPLOOM
    { OBJ_EVENT_GFX_PKMN_JUMPLUFF, &Unk_ov5_FollowerMon },  // SPECIES_JUMPLUFF
    { OBJ_EVENT_GFX_PKMN_AIPOM, &Unk_ov5_FollowerMon },  // SPECIES_AIPOM
    { OBJ_EVENT_GFX_PKMN_SUNKERN, &Unk_ov5_FollowerMon },  // SPECIES_SUNKERN
    { OBJ_EVENT_GFX_PKMN_SUNFLORA, &Unk_ov5_FollowerMon },  // SPECIES_SUNFLORA
    { OBJ_EVENT_GFX_PKMN_YANMA, &Unk_ov5_FollowerMon },  // SPECIES_YANMA
    { OBJ_EVENT_GFX_PKMN_WOOPER, &Unk_ov5_FollowerMon },  // SPECIES_WOOPER
    { OBJ_EVENT_GFX_PKMN_QUAGSIRE, &Unk_ov5_FollowerMon },  // SPECIES_QUAGSIRE
    { OBJ_EVENT_GFX_PKMN_ESPEON, &Unk_ov5_FollowerMon },  // SPECIES_ESPEON
    { OBJ_EVENT_GFX_PKMN_UMBREON, &Unk_ov5_FollowerMon },  // SPECIES_UMBREON
    { OBJ_EVENT_GFX_PKMN_MURKROW, &Unk_ov5_FollowerMon },  // SPECIES_MURKROW
    { OBJ_EVENT_GFX_PKMN_SLOWKING, &Unk_ov5_FollowerMon },  // SPECIES_SLOWKING
    { OBJ_EVENT_GFX_PKMN_MISDREAVUS, &Unk_ov5_FollowerMon },  // SPECIES_MISDREAVUS
    { OBJ_EVENT_GFX_PKMN_UNOWN, &Unk_ov5_FollowerMon },  // SPECIES_UNOWN
    { OBJ_EVENT_GFX_PKMN_WOBBUFFET, &Unk_ov5_FollowerMon },  // SPECIES_WOBBUFFET
    { OBJ_EVENT_GFX_PKMN_WOBBUFFET_F, &Unk_ov5_FollowerMon },  // female
    { OBJ_EVENT_GFX_PKMN_GIRAFARIG, &Unk_ov5_FollowerMon },  // SPECIES_GIRAFARIG
    { OBJ_EVENT_GFX_PKMN_PINECO, &Unk_ov5_FollowerMon },  // SPECIES_PINECO
    { OBJ_EVENT_GFX_PKMN_FORRETRESS, &Unk_ov5_FollowerMon },  // SPECIES_FORRETRESS
    { OBJ_EVENT_GFX_PKMN_DUNSPARCE, &Unk_ov5_FollowerMon },  // SPECIES_DUNSPARCE
    { OBJ_EVENT_GFX_PKMN_GLIGAR, &Unk_ov5_FollowerMon },  // SPECIES_GLIGAR
    { OBJ_EVENT_GFX_PKMN_STEELIX, &Unk_ov5_FollowerMon },  // SPECIES_STEELIX
    { OBJ_EVENT_GFX_PKMN_STEELIX_F, &Unk_ov5_FollowerMon },  // female
    { OBJ_EVENT_GFX_PKMN_SNUBBULL, &Unk_ov5_FollowerMon },  // SPECIES_SNUBBULL
    { OBJ_EVENT_GFX_PKMN_GRANBULL, &Unk_ov5_FollowerMon },  // SPECIES_GRANBULL
    { OBJ_EVENT_GFX_PKMN_QWILFISH, &Unk_ov5_FollowerMon },  // SPECIES_QWILFISH
    { OBJ_EVENT_GFX_PKMN_SCIZOR, &Unk_ov5_FollowerMon },  // SPECIES_SCIZOR
    { OBJ_EVENT_GFX_PKMN_SHUCKLE, &Unk_ov5_FollowerMon },  // SPECIES_SHUCKLE
    { OBJ_EVENT_GFX_PKMN_HERACROSS, &Unk_ov5_FollowerMon },  // SPECIES_HERACROSS
    { OBJ_EVENT_GFX_PKMN_HERACROSS_F, &Unk_ov5_FollowerMon },  // female
    { OBJ_EVENT_GFX_PKMN_SNEASEL, &Unk_ov5_FollowerMon },  // SPECIES_SNEASEL
    { OBJ_EVENT_GFX_PKMN_TEDDIURSA, &Unk_ov5_FollowerMon },  // SPECIES_TEDDIURSA
    { OBJ_EVENT_GFX_PKMN_URSARING, &Unk_ov5_FollowerMon },  // SPECIES_URSARING
    { OBJ_EVENT_GFX_PKMN_SLUGMA, &Unk_ov5_FollowerMon },  // SPECIES_SLUGMA
    { OBJ_EVENT_GFX_PKMN_MAGCARGO, &Unk_ov5_FollowerMon },  // SPECIES_MAGCARGO
    { OBJ_EVENT_GFX_PKMN_SWINUB, &Unk_ov5_FollowerMon },  // SPECIES_SWINUB
    { OBJ_EVENT_GFX_PKMN_PILOSWINE, &Unk_ov5_FollowerMon },  // SPECIES_PILOSWINE
    { OBJ_EVENT_GFX_PKMN_CORSOLA, &Unk_ov5_FollowerMon },  // SPECIES_CORSOLA
    { OBJ_EVENT_GFX_PKMN_REMORAID, &Unk_ov5_FollowerMon },  // SPECIES_REMORAID
    { OBJ_EVENT_GFX_PKMN_OCTILLERY, &Unk_ov5_FollowerMon },  // SPECIES_OCTILLERY
    { OBJ_EVENT_GFX_PKMN_DELIBIRD, &Unk_ov5_FollowerMon },  // SPECIES_DELIBIRD
    { OBJ_EVENT_GFX_PKMN_MANTINE, &Unk_ov5_FollowerMon },  // SPECIES_MANTINE
    { OBJ_EVENT_GFX_PKMN_SKARMORY, &Unk_ov5_FollowerMon },  // SPECIES_SKARMORY
    { OBJ_EVENT_GFX_PKMN_HOUNDOUR, &Unk_ov5_FollowerMon },  // SPECIES_HOUNDOUR
    { OBJ_EVENT_GFX_PKMN_HOUNDOOM, &Unk_ov5_FollowerMon },  // SPECIES_HOUNDOOM
    { OBJ_EVENT_GFX_PKMN_KINGDRA, &Unk_ov5_FollowerMon },  // SPECIES_KINGDRA
    { OBJ_EVENT_GFX_PKMN_PHANPY, &Unk_ov5_FollowerMon },  // SPECIES_PHANPY
    { OBJ_EVENT_GFX_PKMN_DONPHAN, &Unk_ov5_FollowerMon },  // SPECIES_DONPHAN
    { OBJ_EVENT_GFX_PKMN_PORYGON2, &Unk_ov5_FollowerMon },  // SPECIES_PORYGON2
    { OBJ_EVENT_GFX_PKMN_STANTLER, &Unk_ov5_FollowerMon },  // SPECIES_STANTLER
    { OBJ_EVENT_GFX_PKMN_SMEARGLE, &Unk_ov5_FollowerMon },  // SPECIES_SMEARGLE
    { OBJ_EVENT_GFX_PKMN_TYROGUE, &Unk_ov5_FollowerMon },  // SPECIES_TYROGUE
    { OBJ_EVENT_GFX_PKMN_HITMONTOP, &Unk_ov5_FollowerMon },  // SPECIES_HITMONTOP
    { OBJ_EVENT_GFX_PKMN_SMOOCHUM, &Unk_ov5_FollowerMon },  // SPECIES_SMOOCHUM
    { OBJ_EVENT_GFX_PKMN_ELEKID, &Unk_ov5_FollowerMon },  // SPECIES_ELEKID
    { OBJ_EVENT_GFX_PKMN_MAGBY, &Unk_ov5_FollowerMon },  // SPECIES_MAGBY
    { OBJ_EVENT_GFX_PKMN_MILTANK, &Unk_ov5_FollowerMon },  // SPECIES_MILTANK
    { OBJ_EVENT_GFX_PKMN_BLISSEY, &Unk_ov5_FollowerMon },  // SPECIES_BLISSEY
    { OBJ_EVENT_GFX_PKMN_RAIKOU, &Unk_ov5_FollowerMon },  // SPECIES_RAIKOU
    { OBJ_EVENT_GFX_PKMN_ENTEI, &Unk_ov5_FollowerMon },  // SPECIES_ENTEI
    { OBJ_EVENT_GFX_PKMN_SUICUNE, &Unk_ov5_FollowerMon },  // SPECIES_SUICUNE
    { OBJ_EVENT_GFX_PKMN_LARVITAR, &Unk_ov5_FollowerMon },  // SPECIES_LARVITAR
    { OBJ_EVENT_GFX_PKMN_PUPITAR, &Unk_ov5_FollowerMon },  // SPECIES_PUPITAR
    { OBJ_EVENT_GFX_PKMN_TYRANITAR, &Unk_ov5_FollowerMon },  // SPECIES_TYRANITAR
    { OBJ_EVENT_GFX_PKMN_LUGIA, &Unk_ov5_FollowerMon },  // SPECIES_LUGIA
    { OBJ_EVENT_GFX_PKMN_HO_OH, &Unk_ov5_FollowerMon },  // SPECIES_HO_OH
    { OBJ_EVENT_GFX_PKMN_CELEBI, &Unk_ov5_FollowerMon },  // SPECIES_CELEBI
    { OBJ_EVENT_GFX_PKMN_TREECKO, &Unk_ov5_FollowerMon },  // SPECIES_TREECKO
    { OBJ_EVENT_GFX_PKMN_GROVYLE, &Unk_ov5_FollowerMon },  // SPECIES_GROVYLE
    { OBJ_EVENT_GFX_PKMN_SCEPTILE, &Unk_ov5_FollowerMon },  // SPECIES_SCEPTILE
    { OBJ_EVENT_GFX_PKMN_TORCHIC, &Unk_ov5_FollowerMon },  // SPECIES_TORCHIC
    { OBJ_EVENT_GFX_PKMN_COMBUSKEN, &Unk_ov5_FollowerMon },  // SPECIES_COMBUSKEN
    { OBJ_EVENT_GFX_PKMN_BLAZIKEN, &Unk_ov5_FollowerMon },  // SPECIES_BLAZIKEN
    { OBJ_EVENT_GFX_PKMN_MUDKIP, &Unk_ov5_FollowerMon },  // SPECIES_MUDKIP
    { OBJ_EVENT_GFX_PKMN_MARSHTOMP, &Unk_ov5_FollowerMon },  // SPECIES_MARSHTOMP
    { OBJ_EVENT_GFX_PKMN_SWAMPERT, &Unk_ov5_FollowerMon },  // SPECIES_SWAMPERT
    { OBJ_EVENT_GFX_PKMN_POOCHYENA, &Unk_ov5_FollowerMon },  // SPECIES_POOCHYENA
    { OBJ_EVENT_GFX_PKMN_MIGHTYENA, &Unk_ov5_FollowerMon },  // SPECIES_MIGHTYENA
    { OBJ_EVENT_GFX_PKMN_ZIGZAGOON, &Unk_ov5_FollowerMon },  // SPECIES_ZIGZAGOON
    { OBJ_EVENT_GFX_PKMN_LINOONE, &Unk_ov5_FollowerMon },  // SPECIES_LINOONE
    { OBJ_EVENT_GFX_PKMN_WURMPLE, &Unk_ov5_FollowerMon },  // SPECIES_WURMPLE
    { OBJ_EVENT_GFX_PKMN_SILCOON, &Unk_ov5_FollowerMon },  // SPECIES_SILCOON
    { OBJ_EVENT_GFX_PKMN_BEAUTIFLY, &Unk_ov5_FollowerMon },  // SPECIES_BEAUTIFLY
    { OBJ_EVENT_GFX_PKMN_CASCOON, &Unk_ov5_FollowerMon },  // SPECIES_CASCOON
    { OBJ_EVENT_GFX_PKMN_DUSTOX, &Unk_ov5_FollowerMon },  // SPECIES_DUSTOX
    { OBJ_EVENT_GFX_PKMN_LOTAD, &Unk_ov5_FollowerMon },  // SPECIES_LOTAD
    { OBJ_EVENT_GFX_PKMN_LOMBRE, &Unk_ov5_FollowerMon },  // SPECIES_LOMBRE
    { OBJ_EVENT_GFX_PKMN_LUDICOLO, &Unk_ov5_FollowerMon },  // SPECIES_LUDICOLO
    { OBJ_EVENT_GFX_PKMN_SEEDOT, &Unk_ov5_FollowerMon },  // SPECIES_SEEDOT
    { OBJ_EVENT_GFX_PKMN_NUZLEAF, &Unk_ov5_FollowerMon },  // SPECIES_NUZLEAF
    { OBJ_EVENT_GFX_PKMN_SHIFTRY, &Unk_ov5_FollowerMon },  // SPECIES_SHIFTRY
    { OBJ_EVENT_GFX_PKMN_TAILLOW, &Unk_ov5_FollowerMon },  // SPECIES_TAILLOW
    { OBJ_EVENT_GFX_PKMN_SWELLOW, &Unk_ov5_FollowerMon },  // SPECIES_SWELLOW
    { OBJ_EVENT_GFX_PKMN_WINGULL, &Unk_ov5_FollowerMon },  // SPECIES_WINGULL
    { OBJ_EVENT_GFX_PKMN_PELIPPER, &Unk_ov5_FollowerMon },  // SPECIES_PELIPPER
    { OBJ_EVENT_GFX_PKMN_RALTS, &Unk_ov5_FollowerMon },  // SPECIES_RALTS
    { OBJ_EVENT_GFX_PKMN_KIRLIA, &Unk_ov5_FollowerMon },  // SPECIES_KIRLIA
    { OBJ_EVENT_GFX_PKMN_GARDEVOIR, &Unk_ov5_FollowerMon },  // SPECIES_GARDEVOIR
    { OBJ_EVENT_GFX_PKMN_SURSKIT, &Unk_ov5_FollowerMon },  // SPECIES_SURSKIT
    { OBJ_EVENT_GFX_PKMN_MASQUERAIN, &Unk_ov5_FollowerMon },  // SPECIES_MASQUERAIN
    { OBJ_EVENT_GFX_PKMN_SHROOMISH, &Unk_ov5_FollowerMon },  // SPECIES_SHROOMISH
    { OBJ_EVENT_GFX_PKMN_BRELOOM, &Unk_ov5_FollowerMon },  // SPECIES_BRELOOM
    { OBJ_EVENT_GFX_PKMN_SLAKOTH, &Unk_ov5_FollowerMon },  // SPECIES_SLAKOTH
    { OBJ_EVENT_GFX_PKMN_VIGOROTH, &Unk_ov5_FollowerMon },  // SPECIES_VIGOROTH
    { OBJ_EVENT_GFX_PKMN_SLAKING, &Unk_ov5_FollowerMon },  // SPECIES_SLAKING
    { OBJ_EVENT_GFX_PKMN_NINCADA, &Unk_ov5_FollowerMon },  // SPECIES_NINCADA
    { OBJ_EVENT_GFX_PKMN_NINJASK, &Unk_ov5_FollowerMon },  // SPECIES_NINJASK
    { OBJ_EVENT_GFX_PKMN_SHEDINJA, &Unk_ov5_FollowerMon },  // SPECIES_SHEDINJA
    { OBJ_EVENT_GFX_PKMN_WHISMUR, &Unk_ov5_FollowerMon },  // SPECIES_WHISMUR
    { OBJ_EVENT_GFX_PKMN_LOUDRED, &Unk_ov5_FollowerMon },  // SPECIES_LOUDRED
    { OBJ_EVENT_GFX_PKMN_EXPLOUD, &Unk_ov5_FollowerMon },  // SPECIES_EXPLOUD
    { OBJ_EVENT_GFX_PKMN_MAKUHITA, &Unk_ov5_FollowerMon },  // SPECIES_MAKUHITA
    { OBJ_EVENT_GFX_PKMN_HARIYAMA, &Unk_ov5_FollowerMon },  // SPECIES_HARIYAMA
    { OBJ_EVENT_GFX_PKMN_AZURILL, &Unk_ov5_FollowerMon },  // SPECIES_AZURILL
    { OBJ_EVENT_GFX_PKMN_NOSEPASS, &Unk_ov5_FollowerMon },  // SPECIES_NOSEPASS
    { OBJ_EVENT_GFX_PKMN_SKITTY, &Unk_ov5_FollowerMon },  // SPECIES_SKITTY
    { OBJ_EVENT_GFX_PKMN_DELCATTY, &Unk_ov5_FollowerMon },  // SPECIES_DELCATTY
    { OBJ_EVENT_GFX_PKMN_SABLEYE, &Unk_ov5_FollowerMon },  // SPECIES_SABLEYE
    { OBJ_EVENT_GFX_PKMN_MAWILE, &Unk_ov5_FollowerMon },  // SPECIES_MAWILE
    { OBJ_EVENT_GFX_PKMN_ARON, &Unk_ov5_FollowerMon },  // SPECIES_ARON
    { OBJ_EVENT_GFX_PKMN_LAIRON, &Unk_ov5_FollowerMon },  // SPECIES_LAIRON
    { OBJ_EVENT_GFX_PKMN_AGGRON, &Unk_ov5_FollowerMon },  // SPECIES_AGGRON
    { OBJ_EVENT_GFX_PKMN_MEDITITE, &Unk_ov5_FollowerMon },  // SPECIES_MEDITITE
    { OBJ_EVENT_GFX_PKMN_MEDICHAM, &Unk_ov5_FollowerMon },  // SPECIES_MEDICHAM
    { OBJ_EVENT_GFX_PKMN_ELECTRIKE, &Unk_ov5_FollowerMon },  // SPECIES_ELECTRIKE
    { OBJ_EVENT_GFX_PKMN_MANECTRIC, &Unk_ov5_FollowerMon },  // SPECIES_MANECTRIC
    { OBJ_EVENT_GFX_PKMN_PLUSLE, &Unk_ov5_FollowerMon },  // SPECIES_PLUSLE
    { OBJ_EVENT_GFX_PKMN_MINUN, &Unk_ov5_FollowerMon },  // SPECIES_MINUN
    { OBJ_EVENT_GFX_PKMN_VOLBEAT, &Unk_ov5_FollowerMon },  // SPECIES_VOLBEAT
    { OBJ_EVENT_GFX_PKMN_ILLUMISE, &Unk_ov5_FollowerMon },  // SPECIES_ILLUMISE
    { OBJ_EVENT_GFX_PKMN_ROSELIA, &Unk_ov5_FollowerMon },  // SPECIES_ROSELIA
    { OBJ_EVENT_GFX_PKMN_GULPIN, &Unk_ov5_FollowerMon },  // SPECIES_GULPIN
    { OBJ_EVENT_GFX_PKMN_SWALOT, &Unk_ov5_FollowerMon },  // SPECIES_SWALOT
    { OBJ_EVENT_GFX_PKMN_CARVANHA, &Unk_ov5_FollowerMon },  // SPECIES_CARVANHA
    { OBJ_EVENT_GFX_PKMN_SHARPEDO, &Unk_ov5_FollowerMon },  // SPECIES_SHARPEDO
    { OBJ_EVENT_GFX_PKMN_WAILMER, &Unk_ov5_FollowerMon },  // SPECIES_WAILMER
    { OBJ_EVENT_GFX_PKMN_WAILORD, &Unk_ov5_FollowerMon },  // SPECIES_WAILORD
    { OBJ_EVENT_GFX_PKMN_NUMEL, &Unk_ov5_FollowerMon },  // SPECIES_NUMEL
    { OBJ_EVENT_GFX_PKMN_CAMERUPT, &Unk_ov5_FollowerMon },  // SPECIES_CAMERUPT
    { OBJ_EVENT_GFX_PKMN_TORKOAL, &Unk_ov5_FollowerMon },  // SPECIES_TORKOAL
    { OBJ_EVENT_GFX_PKMN_SPOINK, &Unk_ov5_FollowerMon },  // SPECIES_SPOINK
    { OBJ_EVENT_GFX_PKMN_GRUMPIG, &Unk_ov5_FollowerMon },  // SPECIES_GRUMPIG
    { OBJ_EVENT_GFX_PKMN_SPINDA, &Unk_ov5_FollowerMon },  // SPECIES_SPINDA
    { OBJ_EVENT_GFX_PKMN_TRAPINCH, &Unk_ov5_FollowerMon },  // SPECIES_TRAPINCH
    { OBJ_EVENT_GFX_PKMN_VIBRAVA, &Unk_ov5_FollowerMon },  // SPECIES_VIBRAVA
    { OBJ_EVENT_GFX_PKMN_FLYGON, &Unk_ov5_FollowerMon },  // SPECIES_FLYGON
    { OBJ_EVENT_GFX_PKMN_CACNEA, &Unk_ov5_FollowerMon },  // SPECIES_CACNEA
    { OBJ_EVENT_GFX_PKMN_CACTURNE, &Unk_ov5_FollowerMon },  // SPECIES_CACTURNE
    { OBJ_EVENT_GFX_PKMN_SWABLU, &Unk_ov5_FollowerMon },  // SPECIES_SWABLU
    { OBJ_EVENT_GFX_PKMN_ALTARIA, &Unk_ov5_FollowerMon },  // SPECIES_ALTARIA
    { OBJ_EVENT_GFX_PKMN_ZANGOOSE, &Unk_ov5_FollowerMon },  // SPECIES_ZANGOOSE
    { OBJ_EVENT_GFX_PKMN_SEVIPER, &Unk_ov5_FollowerMon },  // SPECIES_SEVIPER
    { OBJ_EVENT_GFX_PKMN_LUNATONE, &Unk_ov5_FollowerMon },  // SPECIES_LUNATONE
    { OBJ_EVENT_GFX_PKMN_SOLROCK, &Unk_ov5_FollowerMon },  // SPECIES_SOLROCK
    { OBJ_EVENT_GFX_PKMN_BARBOACH, &Unk_ov5_FollowerMon },  // SPECIES_BARBOACH
    { OBJ_EVENT_GFX_PKMN_WHISCASH, &Unk_ov5_FollowerMon },  // SPECIES_WHISCASH
    { OBJ_EVENT_GFX_PKMN_CORPHISH, &Unk_ov5_FollowerMon },  // SPECIES_CORPHISH
    { OBJ_EVENT_GFX_PKMN_CRAWDAUNT, &Unk_ov5_FollowerMon },  // SPECIES_CRAWDAUNT
    { OBJ_EVENT_GFX_PKMN_BALTOY, &Unk_ov5_FollowerMon },  // SPECIES_BALTOY
    { OBJ_EVENT_GFX_PKMN_CLAYDOL, &Unk_ov5_FollowerMon },  // SPECIES_CLAYDOL
    { OBJ_EVENT_GFX_PKMN_LILEEP, &Unk_ov5_FollowerMon },  // SPECIES_LILEEP
    { OBJ_EVENT_GFX_PKMN_CRADILY, &Unk_ov5_FollowerMon },  // SPECIES_CRADILY
    { OBJ_EVENT_GFX_PKMN_ANORITH, &Unk_ov5_FollowerMon },  // SPECIES_ANORITH
    { OBJ_EVENT_GFX_PKMN_ARMALDO, &Unk_ov5_FollowerMon },  // SPECIES_ARMALDO
    { OBJ_EVENT_GFX_PKMN_FEEBAS, &Unk_ov5_FollowerMon },  // SPECIES_FEEBAS
    { OBJ_EVENT_GFX_PKMN_MILOTIC, &Unk_ov5_FollowerMon },  // SPECIES_MILOTIC
    { OBJ_EVENT_GFX_PKMN_CASTFORM, &Unk_ov5_FollowerMon },  // SPECIES_CASTFORM
    { OBJ_EVENT_GFX_PKMN_KECLEON, &Unk_ov5_FollowerMon },  // SPECIES_KECLEON
    { OBJ_EVENT_GFX_PKMN_SHUPPET, &Unk_ov5_FollowerMon },  // SPECIES_SHUPPET
    { OBJ_EVENT_GFX_PKMN_BANETTE, &Unk_ov5_FollowerMon },  // SPECIES_BANETTE
    { OBJ_EVENT_GFX_PKMN_DUSKULL, &Unk_ov5_FollowerMon },  // SPECIES_DUSKULL
    { OBJ_EVENT_GFX_PKMN_DUSCLOPS, &Unk_ov5_FollowerMon },  // SPECIES_DUSCLOPS
    { OBJ_EVENT_GFX_PKMN_TROPIUS, &Unk_ov5_FollowerMon },  // SPECIES_TROPIUS
    { OBJ_EVENT_GFX_PKMN_CHIMECHO, &Unk_ov5_FollowerMon },  // SPECIES_CHIMECHO
    { OBJ_EVENT_GFX_PKMN_ABSOL, &Unk_ov5_FollowerMon },  // SPECIES_ABSOL
    { OBJ_EVENT_GFX_PKMN_WYNAUT, &Unk_ov5_FollowerMon },  // SPECIES_WYNAUT
    { OBJ_EVENT_GFX_PKMN_SNORUNT, &Unk_ov5_FollowerMon },  // SPECIES_SNORUNT
    { OBJ_EVENT_GFX_PKMN_GLALIE, &Unk_ov5_FollowerMon },  // SPECIES_GLALIE
    { OBJ_EVENT_GFX_PKMN_SPHEAL, &Unk_ov5_FollowerMon },  // SPECIES_SPHEAL
    { OBJ_EVENT_GFX_PKMN_SEALEO, &Unk_ov5_FollowerMon },  // SPECIES_SEALEO
    { OBJ_EVENT_GFX_PKMN_WALREIN, &Unk_ov5_FollowerMon },  // SPECIES_WALREIN
    { OBJ_EVENT_GFX_PKMN_CLAMPERL, &Unk_ov5_FollowerMon },  // SPECIES_CLAMPERL
    { OBJ_EVENT_GFX_PKMN_HUNTAIL, &Unk_ov5_FollowerMon },  // SPECIES_HUNTAIL
    { OBJ_EVENT_GFX_PKMN_GOREBYSS, &Unk_ov5_FollowerMon },  // SPECIES_GOREBYSS
    { OBJ_EVENT_GFX_PKMN_RELICANTH, &Unk_ov5_FollowerMon },  // SPECIES_RELICANTH
    { OBJ_EVENT_GFX_PKMN_LUVDISC, &Unk_ov5_FollowerMon },  // SPECIES_LUVDISC
    { OBJ_EVENT_GFX_PKMN_BAGON, &Unk_ov5_FollowerMon },  // SPECIES_BAGON
    { OBJ_EVENT_GFX_PKMN_SHELGON, &Unk_ov5_FollowerMon },  // SPECIES_SHELGON
    { OBJ_EVENT_GFX_PKMN_SALAMENCE, &Unk_ov5_FollowerMon },  // SPECIES_SALAMENCE
    { OBJ_EVENT_GFX_PKMN_BELDUM, &Unk_ov5_FollowerMon },  // SPECIES_BELDUM
    { OBJ_EVENT_GFX_PKMN_METANG, &Unk_ov5_FollowerMon },  // SPECIES_METANG
    { OBJ_EVENT_GFX_PKMN_METAGROSS, &Unk_ov5_FollowerMon },  // SPECIES_METAGROSS
    { OBJ_EVENT_GFX_PKMN_REGIROCK, &Unk_ov5_FollowerMon },  // SPECIES_REGIROCK
    { OBJ_EVENT_GFX_PKMN_REGICE, &Unk_ov5_FollowerMon },  // SPECIES_REGICE
    { OBJ_EVENT_GFX_PKMN_REGISTEEL, &Unk_ov5_FollowerMon },  // SPECIES_REGISTEEL
    { OBJ_EVENT_GFX_PKMN_LATIAS, &Unk_ov5_FollowerMon },  // SPECIES_LATIAS
    { OBJ_EVENT_GFX_PKMN_LATIOS, &Unk_ov5_FollowerMon },  // SPECIES_LATIOS
    { OBJ_EVENT_GFX_PKMN_KYOGRE, &Unk_ov5_FollowerMon },  // SPECIES_KYOGRE
    { OBJ_EVENT_GFX_PKMN_GROUDON, &Unk_ov5_FollowerMon },  // SPECIES_GROUDON
    { OBJ_EVENT_GFX_PKMN_RAYQUAZA, &Unk_ov5_FollowerMon },  // SPECIES_RAYQUAZA
    { OBJ_EVENT_GFX_PKMN_JIRACHI, &Unk_ov5_FollowerMon },  // SPECIES_JIRACHI
    { OBJ_EVENT_GFX_PKMN_DEOXYS, &Unk_ov5_FollowerMon },  // SPECIES_DEOXYS
    { OBJ_EVENT_GFX_PKMN_TURTWIG, &Unk_ov5_FollowerMon },  // SPECIES_TURTWIG
    { OBJ_EVENT_GFX_PKMN_GROTLE, &Unk_ov5_FollowerMon },  // SPECIES_GROTLE
    { OBJ_EVENT_GFX_PKMN_TORTERRA, &Unk_ov5_FollowerMon },  // SPECIES_TORTERRA
    { OBJ_EVENT_GFX_PKMN_CHIMCHAR, &Unk_ov5_FollowerMon },  // SPECIES_CHIMCHAR
    { OBJ_EVENT_GFX_PKMN_MONFERNO, &Unk_ov5_FollowerMon },  // SPECIES_MONFERNO
    { OBJ_EVENT_GFX_PKMN_INFERNAPE, &Unk_ov5_FollowerMon },  // SPECIES_INFERNAPE
    { OBJ_EVENT_GFX_PKMN_PIPLUP, &Unk_ov5_FollowerMon },  // SPECIES_PIPLUP
    { OBJ_EVENT_GFX_PKMN_PRINPLUP, &Unk_ov5_FollowerMon },  // SPECIES_PRINPLUP
    { OBJ_EVENT_GFX_PKMN_EMPOLEON, &Unk_ov5_FollowerMon },  // SPECIES_EMPOLEON
    { OBJ_EVENT_GFX_PKMN_STARLY, &Unk_ov5_FollowerMon },  // SPECIES_STARLY
    { OBJ_EVENT_GFX_PKMN_STARAVIA, &Unk_ov5_FollowerMon },  // SPECIES_STARAVIA
    { OBJ_EVENT_GFX_PKMN_STARAPTOR, &Unk_ov5_FollowerMon },  // SPECIES_STARAPTOR
    { OBJ_EVENT_GFX_PKMN_BIDOOF, &Unk_ov5_FollowerMon },  // SPECIES_BIDOOF
    { OBJ_EVENT_GFX_PKMN_BIBAREL, &Unk_ov5_FollowerMon },  // SPECIES_BIBAREL
    { OBJ_EVENT_GFX_PKMN_KRICKETOT, &Unk_ov5_FollowerMon },  // SPECIES_KRICKETOT
    { OBJ_EVENT_GFX_PKMN_KRICKETUNE, &Unk_ov5_FollowerMon },  // SPECIES_KRICKETUNE
    { OBJ_EVENT_GFX_PKMN_SHINX, &Unk_ov5_FollowerMon },  // SPECIES_SHINX
    { OBJ_EVENT_GFX_PKMN_LUXIO, &Unk_ov5_FollowerMon },  // SPECIES_LUXIO
    { OBJ_EVENT_GFX_PKMN_LUXRAY, &Unk_ov5_FollowerMon },  // SPECIES_LUXRAY
    { OBJ_EVENT_GFX_PKMN_BUDEW, &Unk_ov5_FollowerMon },  // SPECIES_BUDEW
    { OBJ_EVENT_GFX_PKMN_ROSERADE, &Unk_ov5_FollowerMon },  // SPECIES_ROSERADE
    { OBJ_EVENT_GFX_PKMN_CRANIDOS, &Unk_ov5_FollowerMon },  // SPECIES_CRANIDOS
    { OBJ_EVENT_GFX_PKMN_RAMPARDOS, &Unk_ov5_FollowerMon },  // SPECIES_RAMPARDOS
    { OBJ_EVENT_GFX_PKMN_SHIELDON, &Unk_ov5_FollowerMon },  // SPECIES_SHIELDON
    { OBJ_EVENT_GFX_PKMN_BASTIODON, &Unk_ov5_FollowerMon },  // SPECIES_BASTIODON
    { OBJ_EVENT_GFX_PKMN_BURMY, &Unk_ov5_FollowerMon },  // SPECIES_BURMY
    { OBJ_EVENT_GFX_PKMN_WORMADAM, &Unk_ov5_FollowerMon },  // SPECIES_WORMADAM
    { OBJ_EVENT_GFX_PKMN_MOTHIM, &Unk_ov5_FollowerMon },  // SPECIES_MOTHIM
    { OBJ_EVENT_GFX_PKMN_COMBEE, &Unk_ov5_FollowerMon },  // SPECIES_COMBEE
    { OBJ_EVENT_GFX_PKMN_COMBEE_F, &Unk_ov5_FollowerMon },  // female
    { OBJ_EVENT_GFX_PKMN_VESPIQUEN, &Unk_ov5_FollowerMon },  // SPECIES_VESPIQUEN
    { OBJ_EVENT_GFX_PKMN_PACHIRISU, &Unk_ov5_FollowerMon },  // SPECIES_PACHIRISU
    { OBJ_EVENT_GFX_PKMN_BUIZEL, &Unk_ov5_FollowerMon },  // SPECIES_BUIZEL
    { OBJ_EVENT_GFX_PKMN_FLOATZEL, &Unk_ov5_FollowerMon },  // SPECIES_FLOATZEL
    { OBJ_EVENT_GFX_PKMN_CHERUBI, &Unk_ov5_FollowerMon },  // SPECIES_CHERUBI
    { OBJ_EVENT_GFX_PKMN_CHERRIM, &Unk_ov5_FollowerMon },  // SPECIES_CHERRIM
    { OBJ_EVENT_GFX_PKMN_SHELLOS, &Unk_ov5_FollowerMon },  // SPECIES_SHELLOS
    { OBJ_EVENT_GFX_PKMN_GASTRODON, &Unk_ov5_FollowerMon },  // SPECIES_GASTRODON
    { OBJ_EVENT_GFX_PKMN_AMBIPOM, &Unk_ov5_FollowerMon },  // SPECIES_AMBIPOM
    { OBJ_EVENT_GFX_PKMN_DRIFLOON, &Unk_ov5_FollowerMon },  // SPECIES_DRIFLOON
    { OBJ_EVENT_GFX_PKMN_DRIFBLIM, &Unk_ov5_FollowerMon },  // SPECIES_DRIFBLIM
    { OBJ_EVENT_GFX_PKMN_BUNEARY, &Unk_ov5_FollowerMon },  // SPECIES_BUNEARY
    { OBJ_EVENT_GFX_PKMN_LOPUNNY, &Unk_ov5_FollowerMon },  // SPECIES_LOPUNNY
    { OBJ_EVENT_GFX_PKMN_MISMAGIUS, &Unk_ov5_FollowerMon },  // SPECIES_MISMAGIUS
    { OBJ_EVENT_GFX_PKMN_HONCHKROW, &Unk_ov5_FollowerMon },  // SPECIES_HONCHKROW
    { OBJ_EVENT_GFX_PKMN_GLAMEOW, &Unk_ov5_FollowerMon },  // SPECIES_GLAMEOW
    { OBJ_EVENT_GFX_PKMN_PURUGLY, &Unk_ov5_FollowerMon },  // SPECIES_PURUGLY
    { OBJ_EVENT_GFX_PKMN_CHINGLING, &Unk_ov5_FollowerMon },  // SPECIES_CHINGLING
    { OBJ_EVENT_GFX_PKMN_STUNKY, &Unk_ov5_FollowerMon },  // SPECIES_STUNKY
    { OBJ_EVENT_GFX_PKMN_SKUNTANK, &Unk_ov5_FollowerMon },  // SPECIES_SKUNTANK
    { OBJ_EVENT_GFX_PKMN_BRONZOR, &Unk_ov5_FollowerMon },  // SPECIES_BRONZOR
    { OBJ_EVENT_GFX_PKMN_BRONZONG, &Unk_ov5_FollowerMon },  // SPECIES_BRONZONG
    { OBJ_EVENT_GFX_PKMN_BONSLY, &Unk_ov5_FollowerMon },  // SPECIES_BONSLY
    { OBJ_EVENT_GFX_PKMN_MIMEJR, &Unk_ov5_FollowerMon },  // SPECIES_MIMEJR
    { OBJ_EVENT_GFX_PKMN_HAPPINY, &Unk_ov5_FollowerMon },  // SPECIES_HAPPINY
    { OBJ_EVENT_GFX_PKMN_CHATOT, &Unk_ov5_FollowerMon },  // SPECIES_CHATOT
    { OBJ_EVENT_GFX_PKMN_SPIRITOMB, &Unk_ov5_FollowerMon },  // SPECIES_SPIRITOMB
    { OBJ_EVENT_GFX_PKMN_GIBLE, &Unk_ov5_FollowerMon },  // SPECIES_GIBLE
    { OBJ_EVENT_GFX_PKMN_GABITE, &Unk_ov5_FollowerMon },  // SPECIES_GABITE
    { OBJ_EVENT_GFX_PKMN_GARCHOMP, &Unk_ov5_FollowerMon },  // SPECIES_GARCHOMP
    { OBJ_EVENT_GFX_PKMN_MUNCHLAX, &Unk_ov5_FollowerMon },  // SPECIES_MUNCHLAX
    { OBJ_EVENT_GFX_PKMN_RIOLU, &Unk_ov5_FollowerMon },  // SPECIES_RIOLU
    { OBJ_EVENT_GFX_PKMN_LUCARIO, &Unk_ov5_FollowerMon },  // SPECIES_LUCARIO
    { OBJ_EVENT_GFX_PKMN_HIPPOPOTAS, &Unk_ov5_FollowerMon },  // SPECIES_HIPPOPOTAS
    { OBJ_EVENT_GFX_PKMN_HIPPOPOTAS_F, &Unk_ov5_FollowerMon },  // female
    { OBJ_EVENT_GFX_PKMN_HIPPOWDON, &Unk_ov5_FollowerMon },  // SPECIES_HIPPOWDON
    { OBJ_EVENT_GFX_PKMN_HIPPOWDON_F, &Unk_ov5_FollowerMon },  // female
    { OBJ_EVENT_GFX_PKMN_SKORUPI, &Unk_ov5_FollowerMon },  // SPECIES_SKORUPI
    { OBJ_EVENT_GFX_PKMN_DRAPION, &Unk_ov5_FollowerMon },  // SPECIES_DRAPION
    { OBJ_EVENT_GFX_PKMN_CROAGUNK, &Unk_ov5_FollowerMon },  // SPECIES_CROAGUNK
    { OBJ_EVENT_GFX_PKMN_TOXICROAK, &Unk_ov5_FollowerMon },  // SPECIES_TOXICROAK
    { OBJ_EVENT_GFX_PKMN_CARNIVINE, &Unk_ov5_FollowerMon },  // SPECIES_CARNIVINE
    { OBJ_EVENT_GFX_PKMN_FINNEON, &Unk_ov5_FollowerMon },  // SPECIES_FINNEON
    { OBJ_EVENT_GFX_PKMN_LUMINEON, &Unk_ov5_FollowerMon },  // SPECIES_LUMINEON
    { OBJ_EVENT_GFX_PKMN_MANTYKE, &Unk_ov5_FollowerMon },  // SPECIES_MANTYKE
    { OBJ_EVENT_GFX_PKMN_SNOVER, &Unk_ov5_FollowerMon },  // SPECIES_SNOVER
    { OBJ_EVENT_GFX_PKMN_ABOMASNOW, &Unk_ov5_FollowerMon },  // SPECIES_ABOMASNOW
    { OBJ_EVENT_GFX_PKMN_WEAVILE, &Unk_ov5_FollowerMon },  // SPECIES_WEAVILE
    { OBJ_EVENT_GFX_PKMN_MAGNEZONE, &Unk_ov5_FollowerMon },  // SPECIES_MAGNEZONE
    { OBJ_EVENT_GFX_PKMN_LICKILICKY, &Unk_ov5_FollowerMon },  // SPECIES_LICKILICKY
    { OBJ_EVENT_GFX_PKMN_RHYPERIOR, &Unk_ov5_FollowerMon },  // SPECIES_RHYPERIOR
    { OBJ_EVENT_GFX_PKMN_TANGROWTH, &Unk_ov5_FollowerMon },  // SPECIES_TANGROWTH
    { OBJ_EVENT_GFX_PKMN_ELECTIVIRE, &Unk_ov5_FollowerMon },  // SPECIES_ELECTIVIRE
    { OBJ_EVENT_GFX_PKMN_MAGMORTAR, &Unk_ov5_FollowerMon },  // SPECIES_MAGMORTAR
    { OBJ_EVENT_GFX_PKMN_TOGEKISS, &Unk_ov5_FollowerMon },  // SPECIES_TOGEKISS
    { OBJ_EVENT_GFX_PKMN_LEAFEON, &Unk_ov5_FollowerMon },  // SPECIES_LEAFEON
    { OBJ_EVENT_GFX_PKMN_GLACEON, &Unk_ov5_FollowerMon },  // SPECIES_GLACEON
    { OBJ_EVENT_GFX_PKMN_GLISCOR, &Unk_ov5_FollowerMon },  // SPECIES_GLISCOR
    { OBJ_EVENT_GFX_PKMN_MAMOSWINE, &Unk_ov5_FollowerMon },  // SPECIES_MAMOSWINE
    { OBJ_EVENT_GFX_PKMN_PORYGON_Z, &Unk_ov5_FollowerMon },  // SPECIES_PORYGON_Z
    { OBJ_EVENT_GFX_PKMN_GALLADE, &Unk_ov5_FollowerMon },  // SPECIES_GALLADE
    { OBJ_EVENT_GFX_PKMN_PROBOPASS, &Unk_ov5_FollowerMon },  // SPECIES_PROBOPASS
    { OBJ_EVENT_GFX_PKMN_DUSKNOIR, &Unk_ov5_FollowerMon },  // SPECIES_DUSKNOIR
    { OBJ_EVENT_GFX_PKMN_FROSLASS, &Unk_ov5_FollowerMon },  // SPECIES_FROSLASS
    { OBJ_EVENT_GFX_PKMN_ROTOM, &Unk_ov5_FollowerMon },  // SPECIES_ROTOM
    { OBJ_EVENT_GFX_PKMN_UXIE, &Unk_ov5_FollowerMon },  // SPECIES_UXIE
    { OBJ_EVENT_GFX_PKMN_MESPRIT, &Unk_ov5_FollowerMon },  // SPECIES_MESPRIT
    { OBJ_EVENT_GFX_PKMN_AZELF, &Unk_ov5_FollowerMon },  // SPECIES_AZELF
    { OBJ_EVENT_GFX_PKMN_DIALGA, &Unk_ov5_FollowerMon },  // SPECIES_DIALGA
    { OBJ_EVENT_GFX_PKMN_PALKIA, &Unk_ov5_FollowerMon },  // SPECIES_PALKIA
    { OBJ_EVENT_GFX_PKMN_HEATRAN, &Unk_ov5_FollowerMon },  // SPECIES_HEATRAN
    { OBJ_EVENT_GFX_PKMN_REGIGIGAS, &Unk_ov5_FollowerMon },  // SPECIES_REGIGIGAS
    { OBJ_EVENT_GFX_PKMN_GIRATINA, &Unk_ov5_FollowerMon },  // SPECIES_GIRATINA
    { OBJ_EVENT_GFX_PKMN_CRESSELIA, &Unk_ov5_FollowerMon },  // SPECIES_CRESSELIA
    { OBJ_EVENT_GFX_PKMN_PHIONE, &Unk_ov5_FollowerMon },  // SPECIES_PHIONE
    { OBJ_EVENT_GFX_PKMN_MANAPHY, &Unk_ov5_FollowerMon },  // SPECIES_MANAPHY
    { OBJ_EVENT_GFX_PKMN_DARKRAI, &Unk_ov5_FollowerMon },  // SPECIES_DARKRAI
    { OBJ_EVENT_GFX_PKMN_SHAYMIN, &Unk_ov5_FollowerMon },  // SPECIES_SHAYMIN
    { OBJ_EVENT_GFX_PKMN_ARCEUS, &Unk_ov5_FollowerMon },  // SPECIES_ARCEUS
    { OBJ_EVENT_GFX_PKMN_GIRATINA_O, &Unk_ov5_FollowerMon },  // SPECIES_GIRATINA origin form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FIGHTING, &Unk_ov5_FollowerMon },  // SPECIES_ARCEUS fighting type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FLYING, &Unk_ov5_FollowerMon },  // SPECIES_ARCEUS flying type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_POISON, &Unk_ov5_FollowerMon },  // SPECIES_ARCEUS poison type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GROUND, &Unk_ov5_FollowerMon },  // SPECIES_ARCEUS ground type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ROCK, &Unk_ov5_FollowerMon },  // SPECIES_ARCEUS rock type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_BUG, &Unk_ov5_FollowerMon },  // SPECIES_ARCEUS bug type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GHOST, &Unk_ov5_FollowerMon },  // SPECIES_ARCEUS ghost type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_STEEL, &Unk_ov5_FollowerMon },  // SPECIES_ARCEUS steel type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FAIRY, &Unk_ov5_FollowerMon },  // SPECIES_ARCEUS fairy type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FIRE, &Unk_ov5_FollowerMon },  // SPECIES_ARCEUS fire type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_WATER, &Unk_ov5_FollowerMon },  // SPECIES_ARCEUS water type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GRASS, &Unk_ov5_FollowerMon },  // SPECIES_ARCEUS grass type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ELECTRIC, &Unk_ov5_FollowerMon },  // SPECIES_ARCEUS electric type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_PSYCHIC, &Unk_ov5_FollowerMon },  // SPECIES_ARCEUS psychic type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ICE, &Unk_ov5_FollowerMon },  // SPECIES_ARCEUS ice type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_DRAGON, &Unk_ov5_FollowerMon },  // SPECIES_ARCEUS dragon type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_DARK, &Unk_ov5_FollowerMon },  // SPECIES_ARCEUS dark type
    { OBJ_EVENT_GFX_PKMN_DEOXYS_ATTACK, &Unk_ov5_FollowerMon },  // SPECIES_DEOXYS attack form
    { OBJ_EVENT_GFX_PKMN_DEOXYS_DEFENSE, &Unk_ov5_FollowerMon },  // SPECIES_DEOXYS defense form
    { OBJ_EVENT_GFX_PKMN_DEOXYS_SPEED, &Unk_ov5_FollowerMon },  // SPECIES_DEOXYS speed form
    { OBJ_EVENT_GFX_PKMN_BURMY_SANDY, &Unk_ov5_FollowerMon },  // SPECIES_BURMY sandy cloak
    { OBJ_EVENT_GFX_PKMN_BURMY_TRASH, &Unk_ov5_FollowerMon },  // SPECIES_BURMY trash cloak
    { OBJ_EVENT_GFX_PKMN_WORMADAM_SANDY, &Unk_ov5_FollowerMon },  // SPECIES_WORMADAM sandy cloak
    { OBJ_EVENT_GFX_PKMN_WORMADAM_TRASH, &Unk_ov5_FollowerMon },  // SPECIES_WORMADAM trash cloak
    { OBJ_EVENT_GFX_PKMN_SHELLOS_EAST, &Unk_ov5_FollowerMon },  // SPECIES_SHELLOS east sea
    { OBJ_EVENT_GFX_PKMN_GASTRODON_EAST, &Unk_ov5_FollowerMon },  // SPECIES_GASTRODON east sea
    { OBJ_EVENT_GFX_PKMN_ROTOM_HEAT, &Unk_ov5_FollowerMon },  // SPECIES_ROTOM heat
    { OBJ_EVENT_GFX_PKMN_ROTOM_WASH, &Unk_ov5_FollowerMon },  // SPECIES_ROTOM wash
    { OBJ_EVENT_GFX_PKMN_ROTOM_FROST, &Unk_ov5_FollowerMon },  // SPECIES_ROTOM frost
    { OBJ_EVENT_GFX_PKMN_ROTOM_FAN, &Unk_ov5_FollowerMon },  // SPECIES_ROTOM fan
    { OBJ_EVENT_GFX_PKMN_ROTOM_MOW, &Unk_ov5_FollowerMon },  // SPECIES_ROTOM mow
    { OBJ_EVENT_GFX_PKMN_SHAYMIN_SKY, &Unk_ov5_FollowerMon },  // SPECIES_SHAYMIN sky form
    { OBJ_EVENT_GFX_PKMN_BULBASAUR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BULBASAUR
    { OBJ_EVENT_GFX_PKMN_IVYSAUR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_IVYSAUR
    { OBJ_EVENT_GFX_PKMN_VENUSAUR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_VENUSAUR
    { OBJ_EVENT_GFX_PKMN_VENUSAUR_F_SHINY, &Unk_ov5_FollowerMon },  // shiny female
    { OBJ_EVENT_GFX_PKMN_CHARMANDER_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CHARMANDER
    { OBJ_EVENT_GFX_PKMN_CHARMELEON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CHARMELEON
    { OBJ_EVENT_GFX_PKMN_CHARIZARD_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CHARIZARD
    { OBJ_EVENT_GFX_PKMN_SQUIRTLE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SQUIRTLE
    { OBJ_EVENT_GFX_PKMN_WARTORTLE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_WARTORTLE
    { OBJ_EVENT_GFX_PKMN_BLASTOISE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BLASTOISE
    { OBJ_EVENT_GFX_PKMN_CATERPIE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CATERPIE
    { OBJ_EVENT_GFX_PKMN_METAPOD_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_METAPOD
    { OBJ_EVENT_GFX_PKMN_BUTTERFREE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BUTTERFREE
    { OBJ_EVENT_GFX_PKMN_WEEDLE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_WEEDLE
    { OBJ_EVENT_GFX_PKMN_KAKUNA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_KAKUNA
    { OBJ_EVENT_GFX_PKMN_BEEDRILL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BEEDRILL
    { OBJ_EVENT_GFX_PKMN_PIDGEY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PIDGEY
    { OBJ_EVENT_GFX_PKMN_PIDGEOTTO_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PIDGEOTTO
    { OBJ_EVENT_GFX_PKMN_PIDGEOT_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PIDGEOT
    { OBJ_EVENT_GFX_PKMN_RATTATA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_RATTATA
    { OBJ_EVENT_GFX_PKMN_RATICATE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_RATICATE
    { OBJ_EVENT_GFX_PKMN_SPEAROW_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SPEAROW
    { OBJ_EVENT_GFX_PKMN_FEAROW_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_FEAROW
    { OBJ_EVENT_GFX_PKMN_EKANS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_EKANS
    { OBJ_EVENT_GFX_PKMN_ARBOK_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ARBOK
    { OBJ_EVENT_GFX_PKMN_PIKACHU_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PIKACHU
    { OBJ_EVENT_GFX_PKMN_PIKACHU_F_SHINY, &Unk_ov5_FollowerMon },  // shiny female
    { OBJ_EVENT_GFX_PKMN_RAICHU_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_RAICHU
    { OBJ_EVENT_GFX_PKMN_SANDSHREW_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SANDSHREW
    { OBJ_EVENT_GFX_PKMN_SANDSLASH_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SANDSLASH
    { OBJ_EVENT_GFX_PKMN_NIDORAN_F_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_NIDORAN_F
    { OBJ_EVENT_GFX_PKMN_NIDORINA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_NIDORINA
    { OBJ_EVENT_GFX_PKMN_NIDOQUEEN_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_NIDOQUEEN
    { OBJ_EVENT_GFX_PKMN_NIDORAN_M_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_NIDORAN_M
    { OBJ_EVENT_GFX_PKMN_NIDORINO_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_NIDORINO
    { OBJ_EVENT_GFX_PKMN_NIDOKING_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_NIDOKING
    { OBJ_EVENT_GFX_PKMN_CLEFAIRY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CLEFAIRY
    { OBJ_EVENT_GFX_PKMN_CLEFABLE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CLEFABLE
    { OBJ_EVENT_GFX_PKMN_VULPIX_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_VULPIX
    { OBJ_EVENT_GFX_PKMN_NINETALES_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_NINETALES
    { OBJ_EVENT_GFX_PKMN_JIGGLYPUFF_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_JIGGLYPUFF
    { OBJ_EVENT_GFX_PKMN_WIGGLYTUFF_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_WIGGLYTUFF
    { OBJ_EVENT_GFX_PKMN_ZUBAT_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ZUBAT
    { OBJ_EVENT_GFX_PKMN_GOLBAT_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GOLBAT
    { OBJ_EVENT_GFX_PKMN_ODDISH_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ODDISH
    { OBJ_EVENT_GFX_PKMN_GLOOM_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GLOOM
    { OBJ_EVENT_GFX_PKMN_VILEPLUME_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_VILEPLUME
    { OBJ_EVENT_GFX_PKMN_PARAS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PARAS
    { OBJ_EVENT_GFX_PKMN_PARASECT_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PARASECT
    { OBJ_EVENT_GFX_PKMN_VENONAT_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_VENONAT
    { OBJ_EVENT_GFX_PKMN_VENOMOTH_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_VENOMOTH
    { OBJ_EVENT_GFX_PKMN_DIGLETT_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DIGLETT
    { OBJ_EVENT_GFX_PKMN_DUGTRIO_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DUGTRIO
    { OBJ_EVENT_GFX_PKMN_MEOWTH_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MEOWTH
    { OBJ_EVENT_GFX_PKMN_PERSIAN_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PERSIAN
    { OBJ_EVENT_GFX_PKMN_PSYDUCK_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PSYDUCK
    { OBJ_EVENT_GFX_PKMN_GOLDUCK_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GOLDUCK
    { OBJ_EVENT_GFX_PKMN_MANKEY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MANKEY
    { OBJ_EVENT_GFX_PKMN_PRIMEAPE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PRIMEAPE
    { OBJ_EVENT_GFX_PKMN_GROWLITHE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GROWLITHE
    { OBJ_EVENT_GFX_PKMN_ARCANINE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ARCANINE
    { OBJ_EVENT_GFX_PKMN_POLIWAG_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_POLIWAG
    { OBJ_EVENT_GFX_PKMN_POLIWHIRL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_POLIWHIRL
    { OBJ_EVENT_GFX_PKMN_POLIWRATH_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_POLIWRATH
    { OBJ_EVENT_GFX_PKMN_ABRA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ABRA
    { OBJ_EVENT_GFX_PKMN_KADABRA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_KADABRA
    { OBJ_EVENT_GFX_PKMN_ALAKAZAM_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ALAKAZAM
    { OBJ_EVENT_GFX_PKMN_MACHOP_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MACHOP
    { OBJ_EVENT_GFX_PKMN_MACHOKE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MACHOKE
    { OBJ_EVENT_GFX_PKMN_MACHAMP_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MACHAMP
    { OBJ_EVENT_GFX_PKMN_BELLSPROUT_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BELLSPROUT
    { OBJ_EVENT_GFX_PKMN_WEEPINBELL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_WEEPINBELL
    { OBJ_EVENT_GFX_PKMN_VICTREEBEL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_VICTREEBEL
    { OBJ_EVENT_GFX_PKMN_TENTACOOL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_TENTACOOL
    { OBJ_EVENT_GFX_PKMN_TENTACRUEL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_TENTACRUEL
    { OBJ_EVENT_GFX_PKMN_GEODUDE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GEODUDE
    { OBJ_EVENT_GFX_PKMN_GRAVELER_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GRAVELER
    { OBJ_EVENT_GFX_PKMN_GOLEM_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GOLEM
    { OBJ_EVENT_GFX_PKMN_PONYTA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PONYTA
    { OBJ_EVENT_GFX_PKMN_RAPIDASH_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_RAPIDASH
    { OBJ_EVENT_GFX_PKMN_SLOWPOKE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SLOWPOKE
    { OBJ_EVENT_GFX_PKMN_SLOWBRO_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SLOWBRO
    { OBJ_EVENT_GFX_PKMN_MAGNEMITE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MAGNEMITE
    { OBJ_EVENT_GFX_PKMN_MAGNETON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MAGNETON
    { OBJ_EVENT_GFX_PKMN_FARFETCHD_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_FARFETCHD
    { OBJ_EVENT_GFX_PKMN_DODUO_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DODUO
    { OBJ_EVENT_GFX_PKMN_DODRIO_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DODRIO
    { OBJ_EVENT_GFX_PKMN_SEEL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SEEL
    { OBJ_EVENT_GFX_PKMN_DEWGONG_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DEWGONG
    { OBJ_EVENT_GFX_PKMN_GRIMER_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GRIMER
    { OBJ_EVENT_GFX_PKMN_MUK_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MUK
    { OBJ_EVENT_GFX_PKMN_SHELLDER_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SHELLDER
    { OBJ_EVENT_GFX_PKMN_CLOYSTER_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CLOYSTER
    { OBJ_EVENT_GFX_PKMN_GASTLY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GASTLY
    { OBJ_EVENT_GFX_PKMN_HAUNTER_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_HAUNTER
    { OBJ_EVENT_GFX_PKMN_GENGAR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GENGAR
    { OBJ_EVENT_GFX_PKMN_ONIX_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ONIX
    { OBJ_EVENT_GFX_PKMN_DROWZEE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DROWZEE
    { OBJ_EVENT_GFX_PKMN_HYPNO_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_HYPNO
    { OBJ_EVENT_GFX_PKMN_KRABBY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_KRABBY
    { OBJ_EVENT_GFX_PKMN_KINGLER_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_KINGLER
    { OBJ_EVENT_GFX_PKMN_VOLTORB_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_VOLTORB
    { OBJ_EVENT_GFX_PKMN_ELECTRODE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ELECTRODE
    { OBJ_EVENT_GFX_PKMN_EXEGGCUTE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_EXEGGCUTE
    { OBJ_EVENT_GFX_PKMN_EXEGGUTOR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_EXEGGUTOR
    { OBJ_EVENT_GFX_PKMN_CUBONE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CUBONE
    { OBJ_EVENT_GFX_PKMN_MAROWAK_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MAROWAK
    { OBJ_EVENT_GFX_PKMN_HITMONLEE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_HITMONLEE
    { OBJ_EVENT_GFX_PKMN_HITMONCHAN_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_HITMONCHAN
    { OBJ_EVENT_GFX_PKMN_LICKITUNG_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LICKITUNG
    { OBJ_EVENT_GFX_PKMN_KOFFING_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_KOFFING
    { OBJ_EVENT_GFX_PKMN_WEEZING_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_WEEZING
    { OBJ_EVENT_GFX_PKMN_RHYHORN_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_RHYHORN
    { OBJ_EVENT_GFX_PKMN_RHYDON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_RHYDON
    { OBJ_EVENT_GFX_PKMN_CHANSEY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CHANSEY
    { OBJ_EVENT_GFX_PKMN_TANGELA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_TANGELA
    { OBJ_EVENT_GFX_PKMN_KANGASKHAN_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_KANGASKHAN
    { OBJ_EVENT_GFX_PKMN_HORSEA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_HORSEA
    { OBJ_EVENT_GFX_PKMN_SEADRA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SEADRA
    { OBJ_EVENT_GFX_PKMN_GOLDEEN_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GOLDEEN
    { OBJ_EVENT_GFX_PKMN_SEAKING_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SEAKING
    { OBJ_EVENT_GFX_PKMN_STARYU_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_STARYU
    { OBJ_EVENT_GFX_PKMN_STARMIE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_STARMIE
    { OBJ_EVENT_GFX_PKMN_MR_MIME_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MR_MIME
    { OBJ_EVENT_GFX_PKMN_SCYTHER_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SCYTHER
    { OBJ_EVENT_GFX_PKMN_JYNX_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_JYNX
    { OBJ_EVENT_GFX_PKMN_ELECTABUZZ_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ELECTABUZZ
    { OBJ_EVENT_GFX_PKMN_MAGMAR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MAGMAR
    { OBJ_EVENT_GFX_PKMN_PINSIR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PINSIR
    { OBJ_EVENT_GFX_PKMN_TAUROS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_TAUROS
    { OBJ_EVENT_GFX_PKMN_MAGIKARP_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MAGIKARP
    { OBJ_EVENT_GFX_PKMN_GYARADOS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GYARADOS
    { OBJ_EVENT_GFX_PKMN_LAPRAS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LAPRAS
    { OBJ_EVENT_GFX_PKMN_DITTO_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DITTO
    { OBJ_EVENT_GFX_PKMN_EEVEE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_EEVEE
    { OBJ_EVENT_GFX_PKMN_VAPOREON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_VAPOREON
    { OBJ_EVENT_GFX_PKMN_JOLTEON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_JOLTEON
    { OBJ_EVENT_GFX_PKMN_FLAREON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_FLAREON
    { OBJ_EVENT_GFX_PKMN_PORYGON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PORYGON
    { OBJ_EVENT_GFX_PKMN_OMANYTE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_OMANYTE
    { OBJ_EVENT_GFX_PKMN_OMASTAR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_OMASTAR
    { OBJ_EVENT_GFX_PKMN_KABUTO_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_KABUTO
    { OBJ_EVENT_GFX_PKMN_KABUTOPS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_KABUTOPS
    { OBJ_EVENT_GFX_PKMN_AERODACTYL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_AERODACTYL
    { OBJ_EVENT_GFX_PKMN_SNORLAX_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SNORLAX
    { OBJ_EVENT_GFX_PKMN_ARTICUNO_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ARTICUNO
    { OBJ_EVENT_GFX_PKMN_ZAPDOS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ZAPDOS
    { OBJ_EVENT_GFX_PKMN_MOLTRES_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MOLTRES
    { OBJ_EVENT_GFX_PKMN_DRATINI_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DRATINI
    { OBJ_EVENT_GFX_PKMN_DRAGONAIR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DRAGONAIR
    { OBJ_EVENT_GFX_PKMN_DRAGONITE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DRAGONITE
    { OBJ_EVENT_GFX_PKMN_MEWTWO_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MEWTWO
    { OBJ_EVENT_GFX_PKMN_MEW_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MEW
    { OBJ_EVENT_GFX_PKMN_CHIKORITA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CHIKORITA
    { OBJ_EVENT_GFX_PKMN_BAYLEEF_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BAYLEEF
    { OBJ_EVENT_GFX_PKMN_BAYLEEF_F_SHINY, &Unk_ov5_FollowerMon },  // shiny female
    { OBJ_EVENT_GFX_PKMN_CYNDAQUIL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CYNDAQUIL
    { OBJ_EVENT_GFX_PKMN_QUILAVA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_QUILAVA
    { OBJ_EVENT_GFX_PKMN_TYPHLOSION_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_TYPHLOSION
    { OBJ_EVENT_GFX_PKMN_TOTODILE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_TOTODILE
    { OBJ_EVENT_GFX_PKMN_CROCONAW_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CROCONAW
    { OBJ_EVENT_GFX_PKMN_FERALIGATR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_FERALIGATR
    { OBJ_EVENT_GFX_PKMN_SENTRET_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SENTRET
    { OBJ_EVENT_GFX_PKMN_FURRET_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_FURRET
    { OBJ_EVENT_GFX_PKMN_HOOTHOOT_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_HOOTHOOT
    { OBJ_EVENT_GFX_PKMN_NOCTOWL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_NOCTOWL
    { OBJ_EVENT_GFX_PKMN_LEDYBA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LEDYBA
    { OBJ_EVENT_GFX_PKMN_LEDIAN_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LEDIAN
    { OBJ_EVENT_GFX_PKMN_SPINARAK_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SPINARAK
    { OBJ_EVENT_GFX_PKMN_ARIADOS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ARIADOS
    { OBJ_EVENT_GFX_PKMN_CROBAT_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CROBAT
    { OBJ_EVENT_GFX_PKMN_CHINCHOU_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CHINCHOU
    { OBJ_EVENT_GFX_PKMN_LANTURN_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LANTURN
    { OBJ_EVENT_GFX_PKMN_PICHU_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PICHU
    { OBJ_EVENT_GFX_PKMN_CLEFFA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CLEFFA
    { OBJ_EVENT_GFX_PKMN_IGGLYBUFF_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_IGGLYBUFF
    { OBJ_EVENT_GFX_PKMN_TOGEPI_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_TOGEPI
    { OBJ_EVENT_GFX_PKMN_TOGETIC_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_TOGETIC
    { OBJ_EVENT_GFX_PKMN_NATU_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_NATU
    { OBJ_EVENT_GFX_PKMN_XATU_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_XATU
    { OBJ_EVENT_GFX_PKMN_MAREEP_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MAREEP
    { OBJ_EVENT_GFX_PKMN_FLAAFFY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_FLAAFFY
    { OBJ_EVENT_GFX_PKMN_AMPHAROS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_AMPHAROS
    { OBJ_EVENT_GFX_PKMN_BELLOSSOM_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BELLOSSOM
    { OBJ_EVENT_GFX_PKMN_MARILL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MARILL
    { OBJ_EVENT_GFX_PKMN_AZUMARILL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_AZUMARILL
    { OBJ_EVENT_GFX_PKMN_SUDOWOODO_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SUDOWOODO
    { OBJ_EVENT_GFX_PKMN_POLITOED_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_POLITOED
    { OBJ_EVENT_GFX_PKMN_HOPPIP_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_HOPPIP
    { OBJ_EVENT_GFX_PKMN_SKIPLOOM_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SKIPLOOM
    { OBJ_EVENT_GFX_PKMN_JUMPLUFF_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_JUMPLUFF
    { OBJ_EVENT_GFX_PKMN_AIPOM_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_AIPOM
    { OBJ_EVENT_GFX_PKMN_SUNKERN_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SUNKERN
    { OBJ_EVENT_GFX_PKMN_SUNFLORA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SUNFLORA
    { OBJ_EVENT_GFX_PKMN_YANMA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_YANMA
    { OBJ_EVENT_GFX_PKMN_WOOPER_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_WOOPER
    { OBJ_EVENT_GFX_PKMN_QUAGSIRE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_QUAGSIRE
    { OBJ_EVENT_GFX_PKMN_ESPEON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ESPEON
    { OBJ_EVENT_GFX_PKMN_UMBREON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_UMBREON
    { OBJ_EVENT_GFX_PKMN_MURKROW_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MURKROW
    { OBJ_EVENT_GFX_PKMN_SLOWKING_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SLOWKING
    { OBJ_EVENT_GFX_PKMN_MISDREAVUS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MISDREAVUS
    { OBJ_EVENT_GFX_PKMN_UNOWN_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_UNOWN
    { OBJ_EVENT_GFX_PKMN_WOBBUFFET_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_WOBBUFFET
    { OBJ_EVENT_GFX_PKMN_WOBBUFFET_F_SHINY, &Unk_ov5_FollowerMon },  // shiny female
    { OBJ_EVENT_GFX_PKMN_GIRAFARIG_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GIRAFARIG
    { OBJ_EVENT_GFX_PKMN_PINECO_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PINECO
    { OBJ_EVENT_GFX_PKMN_FORRETRESS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_FORRETRESS
    { OBJ_EVENT_GFX_PKMN_DUNSPARCE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DUNSPARCE
    { OBJ_EVENT_GFX_PKMN_GLIGAR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GLIGAR
    { OBJ_EVENT_GFX_PKMN_STEELIX_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_STEELIX
    { OBJ_EVENT_GFX_PKMN_STEELIX_F_SHINY, &Unk_ov5_FollowerMon },  // shiny female
    { OBJ_EVENT_GFX_PKMN_SNUBBULL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SNUBBULL
    { OBJ_EVENT_GFX_PKMN_GRANBULL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GRANBULL
    { OBJ_EVENT_GFX_PKMN_QWILFISH_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_QWILFISH
    { OBJ_EVENT_GFX_PKMN_SCIZOR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SCIZOR
    { OBJ_EVENT_GFX_PKMN_SHUCKLE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SHUCKLE
    { OBJ_EVENT_GFX_PKMN_HERACROSS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_HERACROSS
    { OBJ_EVENT_GFX_PKMN_HERACROSS_F_SHINY, &Unk_ov5_FollowerMon },  // shiny female
    { OBJ_EVENT_GFX_PKMN_SNEASEL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SNEASEL
    { OBJ_EVENT_GFX_PKMN_TEDDIURSA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_TEDDIURSA
    { OBJ_EVENT_GFX_PKMN_URSARING_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_URSARING
    { OBJ_EVENT_GFX_PKMN_SLUGMA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SLUGMA
    { OBJ_EVENT_GFX_PKMN_MAGCARGO_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MAGCARGO
    { OBJ_EVENT_GFX_PKMN_SWINUB_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SWINUB
    { OBJ_EVENT_GFX_PKMN_PILOSWINE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PILOSWINE
    { OBJ_EVENT_GFX_PKMN_CORSOLA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CORSOLA
    { OBJ_EVENT_GFX_PKMN_REMORAID_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_REMORAID
    { OBJ_EVENT_GFX_PKMN_OCTILLERY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_OCTILLERY
    { OBJ_EVENT_GFX_PKMN_DELIBIRD_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DELIBIRD
    { OBJ_EVENT_GFX_PKMN_MANTINE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MANTINE
    { OBJ_EVENT_GFX_PKMN_SKARMORY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SKARMORY
    { OBJ_EVENT_GFX_PKMN_HOUNDOUR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_HOUNDOUR
    { OBJ_EVENT_GFX_PKMN_HOUNDOOM_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_HOUNDOOM
    { OBJ_EVENT_GFX_PKMN_KINGDRA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_KINGDRA
    { OBJ_EVENT_GFX_PKMN_PHANPY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PHANPY
    { OBJ_EVENT_GFX_PKMN_DONPHAN_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DONPHAN
    { OBJ_EVENT_GFX_PKMN_PORYGON2_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PORYGON2
    { OBJ_EVENT_GFX_PKMN_STANTLER_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_STANTLER
    { OBJ_EVENT_GFX_PKMN_SMEARGLE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SMEARGLE
    { OBJ_EVENT_GFX_PKMN_TYROGUE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_TYROGUE
    { OBJ_EVENT_GFX_PKMN_HITMONTOP_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_HITMONTOP
    { OBJ_EVENT_GFX_PKMN_SMOOCHUM_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SMOOCHUM
    { OBJ_EVENT_GFX_PKMN_ELEKID_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ELEKID
    { OBJ_EVENT_GFX_PKMN_MAGBY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MAGBY
    { OBJ_EVENT_GFX_PKMN_MILTANK_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MILTANK
    { OBJ_EVENT_GFX_PKMN_BLISSEY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BLISSEY
    { OBJ_EVENT_GFX_PKMN_RAIKOU_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_RAIKOU
    { OBJ_EVENT_GFX_PKMN_ENTEI_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ENTEI
    { OBJ_EVENT_GFX_PKMN_SUICUNE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SUICUNE
    { OBJ_EVENT_GFX_PKMN_LARVITAR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LARVITAR
    { OBJ_EVENT_GFX_PKMN_PUPITAR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PUPITAR
    { OBJ_EVENT_GFX_PKMN_TYRANITAR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_TYRANITAR
    { OBJ_EVENT_GFX_PKMN_LUGIA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LUGIA
    { OBJ_EVENT_GFX_PKMN_HO_OH_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_HO_OH
    { OBJ_EVENT_GFX_PKMN_CELEBI_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CELEBI
    { OBJ_EVENT_GFX_PKMN_TREECKO_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_TREECKO
    { OBJ_EVENT_GFX_PKMN_GROVYLE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GROVYLE
    { OBJ_EVENT_GFX_PKMN_SCEPTILE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SCEPTILE
    { OBJ_EVENT_GFX_PKMN_TORCHIC_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_TORCHIC
    { OBJ_EVENT_GFX_PKMN_COMBUSKEN_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_COMBUSKEN
    { OBJ_EVENT_GFX_PKMN_BLAZIKEN_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BLAZIKEN
    { OBJ_EVENT_GFX_PKMN_MUDKIP_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MUDKIP
    { OBJ_EVENT_GFX_PKMN_MARSHTOMP_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MARSHTOMP
    { OBJ_EVENT_GFX_PKMN_SWAMPERT_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SWAMPERT
    { OBJ_EVENT_GFX_PKMN_POOCHYENA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_POOCHYENA
    { OBJ_EVENT_GFX_PKMN_MIGHTYENA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MIGHTYENA
    { OBJ_EVENT_GFX_PKMN_ZIGZAGOON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ZIGZAGOON
    { OBJ_EVENT_GFX_PKMN_LINOONE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LINOONE
    { OBJ_EVENT_GFX_PKMN_WURMPLE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_WURMPLE
    { OBJ_EVENT_GFX_PKMN_SILCOON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SILCOON
    { OBJ_EVENT_GFX_PKMN_BEAUTIFLY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BEAUTIFLY
    { OBJ_EVENT_GFX_PKMN_CASCOON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CASCOON
    { OBJ_EVENT_GFX_PKMN_DUSTOX_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DUSTOX
    { OBJ_EVENT_GFX_PKMN_LOTAD_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LOTAD
    { OBJ_EVENT_GFX_PKMN_LOMBRE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LOMBRE
    { OBJ_EVENT_GFX_PKMN_LUDICOLO_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LUDICOLO
    { OBJ_EVENT_GFX_PKMN_SEEDOT_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SEEDOT
    { OBJ_EVENT_GFX_PKMN_NUZLEAF_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_NUZLEAF
    { OBJ_EVENT_GFX_PKMN_SHIFTRY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SHIFTRY
    { OBJ_EVENT_GFX_PKMN_TAILLOW_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_TAILLOW
    { OBJ_EVENT_GFX_PKMN_SWELLOW_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SWELLOW
    { OBJ_EVENT_GFX_PKMN_WINGULL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_WINGULL
    { OBJ_EVENT_GFX_PKMN_PELIPPER_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PELIPPER
    { OBJ_EVENT_GFX_PKMN_RALTS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_RALTS
    { OBJ_EVENT_GFX_PKMN_KIRLIA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_KIRLIA
    { OBJ_EVENT_GFX_PKMN_GARDEVOIR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GARDEVOIR
    { OBJ_EVENT_GFX_PKMN_SURSKIT_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SURSKIT
    { OBJ_EVENT_GFX_PKMN_MASQUERAIN_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MASQUERAIN
    { OBJ_EVENT_GFX_PKMN_SHROOMISH_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SHROOMISH
    { OBJ_EVENT_GFX_PKMN_BRELOOM_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BRELOOM
    { OBJ_EVENT_GFX_PKMN_SLAKOTH_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SLAKOTH
    { OBJ_EVENT_GFX_PKMN_VIGOROTH_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_VIGOROTH
    { OBJ_EVENT_GFX_PKMN_SLAKING_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SLAKING
    { OBJ_EVENT_GFX_PKMN_NINCADA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_NINCADA
    { OBJ_EVENT_GFX_PKMN_NINJASK_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_NINJASK
    { OBJ_EVENT_GFX_PKMN_SHEDINJA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SHEDINJA
    { OBJ_EVENT_GFX_PKMN_WHISMUR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_WHISMUR
    { OBJ_EVENT_GFX_PKMN_LOUDRED_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LOUDRED
    { OBJ_EVENT_GFX_PKMN_EXPLOUD_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_EXPLOUD
    { OBJ_EVENT_GFX_PKMN_MAKUHITA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MAKUHITA
    { OBJ_EVENT_GFX_PKMN_HARIYAMA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_HARIYAMA
    { OBJ_EVENT_GFX_PKMN_AZURILL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_AZURILL
    { OBJ_EVENT_GFX_PKMN_NOSEPASS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_NOSEPASS
    { OBJ_EVENT_GFX_PKMN_SKITTY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SKITTY
    { OBJ_EVENT_GFX_PKMN_DELCATTY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DELCATTY
    { OBJ_EVENT_GFX_PKMN_SABLEYE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SABLEYE
    { OBJ_EVENT_GFX_PKMN_MAWILE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MAWILE
    { OBJ_EVENT_GFX_PKMN_ARON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ARON
    { OBJ_EVENT_GFX_PKMN_LAIRON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LAIRON
    { OBJ_EVENT_GFX_PKMN_AGGRON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_AGGRON
    { OBJ_EVENT_GFX_PKMN_MEDITITE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MEDITITE
    { OBJ_EVENT_GFX_PKMN_MEDICHAM_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MEDICHAM
    { OBJ_EVENT_GFX_PKMN_ELECTRIKE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ELECTRIKE
    { OBJ_EVENT_GFX_PKMN_MANECTRIC_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MANECTRIC
    { OBJ_EVENT_GFX_PKMN_PLUSLE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PLUSLE
    { OBJ_EVENT_GFX_PKMN_MINUN_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MINUN
    { OBJ_EVENT_GFX_PKMN_VOLBEAT_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_VOLBEAT
    { OBJ_EVENT_GFX_PKMN_ILLUMISE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ILLUMISE
    { OBJ_EVENT_GFX_PKMN_ROSELIA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ROSELIA
    { OBJ_EVENT_GFX_PKMN_GULPIN_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GULPIN
    { OBJ_EVENT_GFX_PKMN_SWALOT_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SWALOT
    { OBJ_EVENT_GFX_PKMN_CARVANHA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CARVANHA
    { OBJ_EVENT_GFX_PKMN_SHARPEDO_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SHARPEDO
    { OBJ_EVENT_GFX_PKMN_WAILMER_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_WAILMER
    { OBJ_EVENT_GFX_PKMN_WAILORD_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_WAILORD
    { OBJ_EVENT_GFX_PKMN_NUMEL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_NUMEL
    { OBJ_EVENT_GFX_PKMN_CAMERUPT_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CAMERUPT
    { OBJ_EVENT_GFX_PKMN_TORKOAL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_TORKOAL
    { OBJ_EVENT_GFX_PKMN_SPOINK_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SPOINK
    { OBJ_EVENT_GFX_PKMN_GRUMPIG_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GRUMPIG
    { OBJ_EVENT_GFX_PKMN_SPINDA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SPINDA
    { OBJ_EVENT_GFX_PKMN_TRAPINCH_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_TRAPINCH
    { OBJ_EVENT_GFX_PKMN_VIBRAVA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_VIBRAVA
    { OBJ_EVENT_GFX_PKMN_FLYGON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_FLYGON
    { OBJ_EVENT_GFX_PKMN_CACNEA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CACNEA
    { OBJ_EVENT_GFX_PKMN_CACTURNE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CACTURNE
    { OBJ_EVENT_GFX_PKMN_SWABLU_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SWABLU
    { OBJ_EVENT_GFX_PKMN_ALTARIA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ALTARIA
    { OBJ_EVENT_GFX_PKMN_ZANGOOSE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ZANGOOSE
    { OBJ_EVENT_GFX_PKMN_SEVIPER_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SEVIPER
    { OBJ_EVENT_GFX_PKMN_LUNATONE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LUNATONE
    { OBJ_EVENT_GFX_PKMN_SOLROCK_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SOLROCK
    { OBJ_EVENT_GFX_PKMN_BARBOACH_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BARBOACH
    { OBJ_EVENT_GFX_PKMN_WHISCASH_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_WHISCASH
    { OBJ_EVENT_GFX_PKMN_CORPHISH_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CORPHISH
    { OBJ_EVENT_GFX_PKMN_CRAWDAUNT_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CRAWDAUNT
    { OBJ_EVENT_GFX_PKMN_BALTOY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BALTOY
    { OBJ_EVENT_GFX_PKMN_CLAYDOL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CLAYDOL
    { OBJ_EVENT_GFX_PKMN_LILEEP_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LILEEP
    { OBJ_EVENT_GFX_PKMN_CRADILY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CRADILY
    { OBJ_EVENT_GFX_PKMN_ANORITH_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ANORITH
    { OBJ_EVENT_GFX_PKMN_ARMALDO_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ARMALDO
    { OBJ_EVENT_GFX_PKMN_FEEBAS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_FEEBAS
    { OBJ_EVENT_GFX_PKMN_MILOTIC_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MILOTIC
    { OBJ_EVENT_GFX_PKMN_CASTFORM_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CASTFORM
    { OBJ_EVENT_GFX_PKMN_KECLEON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_KECLEON
    { OBJ_EVENT_GFX_PKMN_SHUPPET_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SHUPPET
    { OBJ_EVENT_GFX_PKMN_BANETTE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BANETTE
    { OBJ_EVENT_GFX_PKMN_DUSKULL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DUSKULL
    { OBJ_EVENT_GFX_PKMN_DUSCLOPS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DUSCLOPS
    { OBJ_EVENT_GFX_PKMN_TROPIUS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_TROPIUS
    { OBJ_EVENT_GFX_PKMN_CHIMECHO_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CHIMECHO
    { OBJ_EVENT_GFX_PKMN_ABSOL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ABSOL
    { OBJ_EVENT_GFX_PKMN_WYNAUT_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_WYNAUT
    { OBJ_EVENT_GFX_PKMN_SNORUNT_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SNORUNT
    { OBJ_EVENT_GFX_PKMN_GLALIE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GLALIE
    { OBJ_EVENT_GFX_PKMN_SPHEAL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SPHEAL
    { OBJ_EVENT_GFX_PKMN_SEALEO_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SEALEO
    { OBJ_EVENT_GFX_PKMN_WALREIN_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_WALREIN
    { OBJ_EVENT_GFX_PKMN_CLAMPERL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CLAMPERL
    { OBJ_EVENT_GFX_PKMN_HUNTAIL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_HUNTAIL
    { OBJ_EVENT_GFX_PKMN_GOREBYSS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GOREBYSS
    { OBJ_EVENT_GFX_PKMN_RELICANTH_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_RELICANTH
    { OBJ_EVENT_GFX_PKMN_LUVDISC_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LUVDISC
    { OBJ_EVENT_GFX_PKMN_BAGON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BAGON
    { OBJ_EVENT_GFX_PKMN_SHELGON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SHELGON
    { OBJ_EVENT_GFX_PKMN_SALAMENCE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SALAMENCE
    { OBJ_EVENT_GFX_PKMN_BELDUM_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BELDUM
    { OBJ_EVENT_GFX_PKMN_METANG_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_METANG
    { OBJ_EVENT_GFX_PKMN_METAGROSS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_METAGROSS
    { OBJ_EVENT_GFX_PKMN_REGIROCK_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_REGIROCK
    { OBJ_EVENT_GFX_PKMN_REGICE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_REGICE
    { OBJ_EVENT_GFX_PKMN_REGISTEEL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_REGISTEEL
    { OBJ_EVENT_GFX_PKMN_LATIAS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LATIAS
    { OBJ_EVENT_GFX_PKMN_LATIOS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LATIOS
    { OBJ_EVENT_GFX_PKMN_KYOGRE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_KYOGRE
    { OBJ_EVENT_GFX_PKMN_GROUDON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GROUDON
    { OBJ_EVENT_GFX_PKMN_RAYQUAZA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_RAYQUAZA
    { OBJ_EVENT_GFX_PKMN_JIRACHI_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_JIRACHI
    { OBJ_EVENT_GFX_PKMN_DEOXYS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DEOXYS
    { OBJ_EVENT_GFX_PKMN_TURTWIG_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_TURTWIG
    { OBJ_EVENT_GFX_PKMN_GROTLE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GROTLE
    { OBJ_EVENT_GFX_PKMN_TORTERRA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_TORTERRA
    { OBJ_EVENT_GFX_PKMN_CHIMCHAR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CHIMCHAR
    { OBJ_EVENT_GFX_PKMN_MONFERNO_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MONFERNO
    { OBJ_EVENT_GFX_PKMN_INFERNAPE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_INFERNAPE
    { OBJ_EVENT_GFX_PKMN_PIPLUP_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PIPLUP
    { OBJ_EVENT_GFX_PKMN_PRINPLUP_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PRINPLUP
    { OBJ_EVENT_GFX_PKMN_EMPOLEON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_EMPOLEON
    { OBJ_EVENT_GFX_PKMN_STARLY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_STARLY
    { OBJ_EVENT_GFX_PKMN_STARAVIA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_STARAVIA
    { OBJ_EVENT_GFX_PKMN_STARAPTOR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_STARAPTOR
    { OBJ_EVENT_GFX_PKMN_BIDOOF_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BIDOOF
    { OBJ_EVENT_GFX_PKMN_BIBAREL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BIBAREL
    { OBJ_EVENT_GFX_PKMN_KRICKETOT_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_KRICKETOT
    { OBJ_EVENT_GFX_PKMN_KRICKETUNE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_KRICKETUNE
    { OBJ_EVENT_GFX_PKMN_SHINX_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SHINX
    { OBJ_EVENT_GFX_PKMN_LUXIO_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LUXIO
    { OBJ_EVENT_GFX_PKMN_LUXRAY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LUXRAY
    { OBJ_EVENT_GFX_PKMN_BUDEW_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BUDEW
    { OBJ_EVENT_GFX_PKMN_ROSERADE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ROSERADE
    { OBJ_EVENT_GFX_PKMN_CRANIDOS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CRANIDOS
    { OBJ_EVENT_GFX_PKMN_RAMPARDOS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_RAMPARDOS
    { OBJ_EVENT_GFX_PKMN_SHIELDON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SHIELDON
    { OBJ_EVENT_GFX_PKMN_BASTIODON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BASTIODON
    { OBJ_EVENT_GFX_PKMN_BURMY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BURMY
    { OBJ_EVENT_GFX_PKMN_WORMADAM_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_WORMADAM
    { OBJ_EVENT_GFX_PKMN_MOTHIM_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MOTHIM
    { OBJ_EVENT_GFX_PKMN_COMBEE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_COMBEE
    { OBJ_EVENT_GFX_PKMN_COMBEE_F_SHINY, &Unk_ov5_FollowerMon },  // shiny female
    { OBJ_EVENT_GFX_PKMN_VESPIQUEN_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_VESPIQUEN
    { OBJ_EVENT_GFX_PKMN_PACHIRISU_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PACHIRISU
    { OBJ_EVENT_GFX_PKMN_BUIZEL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BUIZEL
    { OBJ_EVENT_GFX_PKMN_FLOATZEL_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_FLOATZEL
    { OBJ_EVENT_GFX_PKMN_CHERUBI_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CHERUBI
    { OBJ_EVENT_GFX_PKMN_CHERRIM_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CHERRIM
    { OBJ_EVENT_GFX_PKMN_SHELLOS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SHELLOS
    { OBJ_EVENT_GFX_PKMN_GASTRODON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GASTRODON
    { OBJ_EVENT_GFX_PKMN_AMBIPOM_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_AMBIPOM
    { OBJ_EVENT_GFX_PKMN_DRIFLOON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DRIFLOON
    { OBJ_EVENT_GFX_PKMN_DRIFBLIM_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DRIFBLIM
    { OBJ_EVENT_GFX_PKMN_BUNEARY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BUNEARY
    { OBJ_EVENT_GFX_PKMN_LOPUNNY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LOPUNNY
    { OBJ_EVENT_GFX_PKMN_MISMAGIUS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MISMAGIUS
    { OBJ_EVENT_GFX_PKMN_HONCHKROW_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_HONCHKROW
    { OBJ_EVENT_GFX_PKMN_GLAMEOW_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GLAMEOW
    { OBJ_EVENT_GFX_PKMN_PURUGLY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PURUGLY
    { OBJ_EVENT_GFX_PKMN_CHINGLING_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CHINGLING
    { OBJ_EVENT_GFX_PKMN_STUNKY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_STUNKY
    { OBJ_EVENT_GFX_PKMN_SKUNTANK_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SKUNTANK
    { OBJ_EVENT_GFX_PKMN_BRONZOR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BRONZOR
    { OBJ_EVENT_GFX_PKMN_BRONZONG_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BRONZONG
    { OBJ_EVENT_GFX_PKMN_BONSLY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_BONSLY
    { OBJ_EVENT_GFX_PKMN_MIMEJR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MIMEJR
    { OBJ_EVENT_GFX_PKMN_HAPPINY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_HAPPINY
    { OBJ_EVENT_GFX_PKMN_CHATOT_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CHATOT
    { OBJ_EVENT_GFX_PKMN_SPIRITOMB_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SPIRITOMB
    { OBJ_EVENT_GFX_PKMN_GIBLE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GIBLE
    { OBJ_EVENT_GFX_PKMN_GABITE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GABITE
    { OBJ_EVENT_GFX_PKMN_GARCHOMP_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GARCHOMP
    { OBJ_EVENT_GFX_PKMN_MUNCHLAX_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MUNCHLAX
    { OBJ_EVENT_GFX_PKMN_RIOLU_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_RIOLU
    { OBJ_EVENT_GFX_PKMN_LUCARIO_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LUCARIO
    { OBJ_EVENT_GFX_PKMN_HIPPOPOTAS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_HIPPOPOTAS
    { OBJ_EVENT_GFX_PKMN_HIPPOPOTAS_F_SHINY, &Unk_ov5_FollowerMon },  // shiny female
    { OBJ_EVENT_GFX_PKMN_HIPPOWDON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_HIPPOWDON
    { OBJ_EVENT_GFX_PKMN_HIPPOWDON_F_SHINY, &Unk_ov5_FollowerMon },  // shiny female
    { OBJ_EVENT_GFX_PKMN_SKORUPI_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SKORUPI
    { OBJ_EVENT_GFX_PKMN_DRAPION_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DRAPION
    { OBJ_EVENT_GFX_PKMN_CROAGUNK_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CROAGUNK
    { OBJ_EVENT_GFX_PKMN_TOXICROAK_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_TOXICROAK
    { OBJ_EVENT_GFX_PKMN_CARNIVINE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CARNIVINE
    { OBJ_EVENT_GFX_PKMN_FINNEON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_FINNEON
    { OBJ_EVENT_GFX_PKMN_LUMINEON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LUMINEON
    { OBJ_EVENT_GFX_PKMN_MANTYKE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MANTYKE
    { OBJ_EVENT_GFX_PKMN_SNOVER_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SNOVER
    { OBJ_EVENT_GFX_PKMN_ABOMASNOW_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ABOMASNOW
    { OBJ_EVENT_GFX_PKMN_WEAVILE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_WEAVILE
    { OBJ_EVENT_GFX_PKMN_MAGNEZONE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MAGNEZONE
    { OBJ_EVENT_GFX_PKMN_LICKILICKY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LICKILICKY
    { OBJ_EVENT_GFX_PKMN_RHYPERIOR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_RHYPERIOR
    { OBJ_EVENT_GFX_PKMN_TANGROWTH_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_TANGROWTH
    { OBJ_EVENT_GFX_PKMN_ELECTIVIRE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ELECTIVIRE
    { OBJ_EVENT_GFX_PKMN_MAGMORTAR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MAGMORTAR
    { OBJ_EVENT_GFX_PKMN_TOGEKISS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_TOGEKISS
    { OBJ_EVENT_GFX_PKMN_LEAFEON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_LEAFEON
    { OBJ_EVENT_GFX_PKMN_GLACEON_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GLACEON
    { OBJ_EVENT_GFX_PKMN_GLISCOR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GLISCOR
    { OBJ_EVENT_GFX_PKMN_MAMOSWINE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MAMOSWINE
    { OBJ_EVENT_GFX_PKMN_PORYGON_Z_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PORYGON_Z
    { OBJ_EVENT_GFX_PKMN_GALLADE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GALLADE
    { OBJ_EVENT_GFX_PKMN_PROBOPASS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PROBOPASS
    { OBJ_EVENT_GFX_PKMN_DUSKNOIR_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DUSKNOIR
    { OBJ_EVENT_GFX_PKMN_FROSLASS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_FROSLASS
    { OBJ_EVENT_GFX_PKMN_ROTOM_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ROTOM
    { OBJ_EVENT_GFX_PKMN_UXIE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_UXIE
    { OBJ_EVENT_GFX_PKMN_MESPRIT_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MESPRIT
    { OBJ_EVENT_GFX_PKMN_AZELF_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_AZELF
    { OBJ_EVENT_GFX_PKMN_DIALGA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DIALGA
    { OBJ_EVENT_GFX_PKMN_PALKIA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PALKIA
    { OBJ_EVENT_GFX_PKMN_HEATRAN_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_HEATRAN
    { OBJ_EVENT_GFX_PKMN_REGIGIGAS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_REGIGIGAS
    { OBJ_EVENT_GFX_PKMN_GIRATINA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_GIRATINA
    { OBJ_EVENT_GFX_PKMN_CRESSELIA_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_CRESSELIA
    { OBJ_EVENT_GFX_PKMN_PHIONE_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_PHIONE
    { OBJ_EVENT_GFX_PKMN_MANAPHY_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_MANAPHY
    { OBJ_EVENT_GFX_PKMN_DARKRAI_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_DARKRAI
    { OBJ_EVENT_GFX_PKMN_SHAYMIN_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_SHAYMIN
    { OBJ_EVENT_GFX_PKMN_ARCEUS_SHINY, &Unk_ov5_FollowerMon },  // shiny SPECIES_ARCEUS
    { OBJ_EVENT_GFX_PKMN_GIRATINA_O_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FIGHTING_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FLYING_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_POISON_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GROUND_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ROCK_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_BUG_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GHOST_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_STEEL_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FAIRY_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FIRE_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_WATER_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GRASS_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ELECTRIC_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_PSYCHIC_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ICE_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_DRAGON_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_DARK_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_DEOXYS_ATTACK_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_DEOXYS_DEFENSE_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_DEOXYS_SPEED_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_BURMY_SANDY_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_BURMY_TRASH_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_WORMADAM_SANDY_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_WORMADAM_TRASH_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_SHELLOS_EAST_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_GASTRODON_EAST_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ROTOM_HEAT_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ROTOM_WASH_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ROTOM_FROST_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ROTOM_FAN_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ROTOM_MOW_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_SHAYMIN_SKY_SHINY, &Unk_ov5_FollowerMon },  // shiny alt form
    { 0xffff, NULL }
};

const UnkStruct_ov5_021ED2D0 Unk_ov5_021FC9B4[] = {
    { OBJ_EVENT_GFX_PLAYER_M, 0x5A },
    { OBJ_EVENT_GFX_NINJA_BOY, 0x0 },
    { OBJ_EVENT_GFX_TWIN, 0x1 },
    { OBJ_EVENT_GFX_SCHOOL_KID_M, 0x2 },
    { OBJ_EVENT_GFX_YOUNGSTER, 0x3 },
    { OBJ_EVENT_GFX_BUG_CATCHER, 0x4 },
    { OBJ_EVENT_GFX_LASS, 0x5 },
    { OBJ_EVENT_GFX_BATTLE_GIRL, 0x6 },
    { OBJ_EVENT_GFX_SCHOOL_KID_F, 0x7 },
    { OBJ_EVENT_GFX_POKEMON_BREEDER_M, 0x8 },
    { OBJ_EVENT_GFX_GUITARIST, 0x9 },
    { OBJ_EVENT_GFX_ACE_TRAINER_M, 0xA },
    { OBJ_EVENT_GFX_POKEMON_BREEDER_F, 0xB },
    { OBJ_EVENT_GFX_BEAUTY, 0xC },
    { OBJ_EVENT_GFX_ACE_TRAINER_F, 0xD },
    { OBJ_EVENT_GFX_POKEFAN_M, 0xE },
    { OBJ_EVENT_GFX_POKEFAN_F, 0xF },
    { OBJ_EVENT_GFX_EXPERT_M, 0x10 },
    { OBJ_EVENT_GFX_EXPERT_F, 0x11 },
    { OBJ_EVENT_GFX_COLLECTOR, 0x12 },
    { OBJ_EVENT_GFX_HIKER, 0x13 },
    { OBJ_EVENT_GFX_PLAYER_M_BIKE, 0x5C },
    { OBJ_EVENT_GFX_REPORTER, 0x14 },
    { OBJ_EVENT_GFX_CAMERAMAN, 0x15 },
    { OBJ_EVENT_GFX_CASHIER_M, 0x16 },
    { OBJ_EVENT_GFX_CASHIER_F, 0x17 },
    { OBJ_EVENT_GFX_POKECENTER_NURSE, 0x18 },
    { OBJ_EVENT_GFX_TEALA, 0x19 },
    { OBJ_EVENT_GFX_UNUSED_RECEPTIONIST, 0x1A },
    { OBJ_EVENT_GFX_SCIENTIST_M, 0x1B },
    { OBJ_EVENT_GFX_SCIENTIST_F, 0x1C },
    { OBJ_EVENT_GFX_ROUGHNECK, 0x1D },
    { OBJ_EVENT_GFX_SKIER_M, 0x1E },
    { OBJ_EVENT_GFX_SKIER_F, 0x1F },
    { OBJ_EVENT_GFX_POLICEMAN, 0x20 },
    { OBJ_EVENT_GFX_IDOL, 0x21 },
    { OBJ_EVENT_GFX_GENTLEMAN, 0x22 },
    { OBJ_EVENT_GFX_SOCIALITE, 0x23 },
    { OBJ_EVENT_GFX_CYCLIST_M, 0x24 },
    { OBJ_EVENT_GFX_CYCLIST_F, 0x25 },
    { OBJ_EVENT_GFX_WORKER, 0x26 },
    { OBJ_EVENT_GFX_RANCHER, 0x27 },
    { OBJ_EVENT_GFX_COWGIRL, 0x28 },
    { OBJ_EVENT_GFX_CLOWN, 0x29 },
    { OBJ_EVENT_GFX_ARTIST, 0x2A },
    { OBJ_EVENT_GFX_JOGGER, 0x2B },
    { OBJ_EVENT_GFX_SWIMMER_M, 0x2C },
    { OBJ_EVENT_GFX_SWIMMER_F, 0x2D },
    { OBJ_EVENT_GFX_TUBER_F, 0x2E },
    { OBJ_EVENT_GFX_TUBER_M, 0x2F },
    { OBJ_EVENT_GFX_RUIN_MANIAC, 0x30 },
    { OBJ_EVENT_GFX_BLACK_BELT, 0x31 },
    { OBJ_EVENT_GFX_CAMPER, 0x32 },
    { OBJ_EVENT_GFX_PICNICKER, 0x33 },
    { OBJ_EVENT_GFX_FISHERMAN, 0x34 },
    { OBJ_EVENT_GFX_PARASOL_LADY, 0x35 },
    { OBJ_EVENT_GFX_SAILOR, 0x36 },
    { OBJ_EVENT_GFX_DUMMY_057, 0x37 },
    { OBJ_EVENT_GFX_DUMMY_058, 0x38 },
    { OBJ_EVENT_GFX_WAITER, 0x39 },
    { OBJ_EVENT_GFX_WAITRESS, 0x3A },
    { OBJ_EVENT_GFX_DUMMY_061, 0x3B },
    { OBJ_EVENT_GFX_RICH_BOY, 0x3C },
    { OBJ_EVENT_GFX_LADY, 0x3D },
    { OBJ_EVENT_GFX_SNOWPOINT_NPC_M, 0x3E },
    { OBJ_EVENT_GFX_SNOWPOINT_NPC_F, 0x3F },
    { OBJ_EVENT_GFX_DUMMY_066, 0x40 },
    { OBJ_EVENT_GFX_DUMMY_067, 0x41 },
    { OBJ_EVENT_GFX_ACE_TRAINER_SNOW_M, 0x42 },
    { OBJ_EVENT_GFX_ACE_TRAINER_SNOW_F, 0x43 },
    { OBJ_EVENT_GFX_PSYCHIC, 0x44 },
    { OBJ_EVENT_GFX_PIKACHU, 0x45 },
    { OBJ_EVENT_GFX_CLEFAIRY, 0x46 },
    { OBJ_EVENT_GFX_JIGGLYPUFF, 0x47 },
    { OBJ_EVENT_GFX_PSYDUCK, 0x48 },
    { OBJ_EVENT_GFX_DUMMY_075, 0x49 },
    { OBJ_EVENT_GFX_DUMMY_076, 0x4A },
    { OBJ_EVENT_GFX_DUMMY_077, 0x4B },
    { OBJ_EVENT_GFX_TORCHIC, 0x4C },
    { OBJ_EVENT_GFX_SKITTY, 0x4D },
    { OBJ_EVENT_GFX_DUMMY_080, 0x4E },
    { OBJ_EVENT_GFX_BABY_IN_PRAM, 0x4F },
    { OBJ_EVENT_GFX_MIDDLE_AGED_MAN, 0x50 },
    { OBJ_EVENT_GFX_MIDDLE_AGED_WOMAN, 0x51 },
    { OBJ_EVENT_GFX_STRENGTH_BOULDER, 0x52 },
    { OBJ_EVENT_GFX_ROCK_SMASH, 0x53 },
    { OBJ_EVENT_GFX_CUT_TREE, 0x54 },
    { OBJ_EVENT_GFX_POKEBALL, 0x55 },
    { OBJ_EVENT_GFX_UNUSED_WOMAN_1, 0x56 },
    { OBJ_EVENT_GFX_UNUSED_WOMAN_2, 0x57 },
    { OBJ_EVENT_GFX_UNUSED_WOMAN_3, 0x58 },
    { OBJ_EVENT_GFX_PLAYER_F, 0x5B },
    { OBJ_EVENT_GFX_PLAYER_F_BIKE, 0x5D },
    { OBJ_EVENT_GFX_PROF_ROWAN, 0x5E },
    { 0x1000, 0x5F },
    { 0x1001, 0x60 },
    { 0x1002, 0x61 },
    { 0x1003, 0x62 },
    { OBJ_EVENT_GFX_CYRUS, 0x63 },
    { OBJ_EVENT_GFX_MARS, 0x64 },
    { OBJ_EVENT_GFX_SATURN, 0x65 },
    { OBJ_EVENT_GFX_JUPITER, 0x66 },
    { OBJ_EVENT_GFX_GRUNT_M, 0x67 },
    { OBJ_EVENT_GFX_GRUNT_F, 0x68 },
    { OBJ_EVENT_GFX_ROARK, 0x69 },
    { OBJ_EVENT_GFX_GARDENIA, 0x6A },
    { OBJ_EVENT_GFX_CRASHER_WAKE, 0x6B },
    { OBJ_EVENT_GFX_MAYLENE, 0x6C },
    { OBJ_EVENT_GFX_FANTINA, 0x6D },
    { OBJ_EVENT_GFX_CANDICE, 0x6E },
    { OBJ_EVENT_GFX_BYRON, 0x6F },
    { OBJ_EVENT_GFX_VOLKNER, 0x70 },
    { OBJ_EVENT_GFX_AARON, 0x71 },
    { OBJ_EVENT_GFX_BERTHA, 0x72 },
    { OBJ_EVENT_GFX_FLINT, 0x73 },
    { OBJ_EVENT_GFX_LUCIAN, 0x74 },
    { OBJ_EVENT_GFX_CYNTHIA, 0x75 },
    { OBJ_EVENT_GFX_UNUSED_MAN, 0x76 },
    { OBJ_EVENT_GFX_MOM, 0x77 },
    { OBJ_EVENT_GFX_CHERYL, 0x78 },
    { OBJ_EVENT_GFX_RILEY, 0x79 },
    { OBJ_EVENT_GFX_MARLEY, 0x7A },
    { OBJ_EVENT_GFX_BUCK, 0x7B },
    { OBJ_EVENT_GFX_MIRA, 0x7C },
    { OBJ_EVENT_GFX_DUMMY_146, 0x7D },
    { OBJ_EVENT_GFX_DUMMY_147, 0x7E },
    { OBJ_EVENT_GFX_BARRY, 0x7F },
    { OBJ_EVENT_GFX_UNUSED_BIG_MAN_1, 0x80 },
    { OBJ_EVENT_GFX_UNUSED_BIG_MAN_2, 0x81 },
    { OBJ_EVENT_GFX_UXIE, 0x82 },
    { OBJ_EVENT_GFX_MESPRIT, 0x83 },
    { OBJ_EVENT_GFX_AZELF, 0x84 },
    { OBJ_EVENT_GFX_DIALGA, 0x85 },
    { OBJ_EVENT_GFX_PALKIA, 0x86 },
    { OBJ_EVENT_GFX_ARCEUS, 0x87 },
    { OBJ_EVENT_GFX_DARKRAI, 0x88 },
    { OBJ_EVENT_GFX_SHAYMIN, 0x89 },
    { OBJ_EVENT_GFX_CRESSELIA, 0x8A },
    { OBJ_EVENT_GFX_GIRATINA_ALTERED, 0x8B },
    { OBJ_EVENT_GFX_HEATRAN, 0x8C },
    { OBJ_EVENT_GFX_DUMMY_162, 0x8D },
    { OBJ_EVENT_GFX_RECEPTIONIST, 0x8E },
    { OBJ_EVENT_GFX_OLD_MAN, 0x8F },
    { OBJ_EVENT_GFX_OLD_WOMAN, 0x90 },
    { OBJ_EVENT_GFX_PROF_OAK, 0x91 },
    { OBJ_EVENT_GFX_JASMINE, 0x92 },
    { OBJ_EVENT_GFX_GYM_GUIDE, 0x93 },
    { OBJ_EVENT_GFX_PALMER, 0x94 },
    { OBJ_EVENT_GFX_UNUSED_BIG_MAN_3, 0x95 },
    { OBJ_EVENT_GFX_UNUSED_BIG_MAN_4, 0x96 },
    { OBJ_EVENT_GFX_UNUSED_BIG_MAN_5, 0x97 },
    { OBJ_EVENT_GFX_STARLY, 0x98 },
    { OBJ_EVENT_GFX_BRIEFCASE, 0x99 },
    { OBJ_EVENT_GFX_MAID, 0x9A },
    { OBJ_EVENT_GFX_PLAYER_M_HOLDING_POKE_BALL, 0x9B },
    { OBJ_EVENT_GFX_PLAYER_F_HOLDING_POKE_BALL, 0x9C },
    { OBJ_EVENT_GFX_PLAYER_M_SPRAYDUCK, 0x9D },
    { OBJ_EVENT_GFX_PLAYER_F_SPRAYDUCK, 0x9E },
    { OBJ_EVENT_GFX_PLAYER_M_SURF, 0x9F },
    { OBJ_EVENT_GFX_PLAYER_F_SURF, 0xA0 },
    { OBJ_EVENT_GFX_VENT, 0xA1 },
    { OBJ_EVENT_GFX_REGIGIGAS, 0xA2 },
    { OBJ_EVENT_GFX_DRIFLOON, 0xA3 },
    { OBJ_EVENT_GFX_PLAYER_M_CONTEST, 0xA4 },
    { OBJ_EVENT_GFX_PLAYER_F_CONTEST, 0xA5 },
    { OBJ_EVENT_GFX_PLAYER_M_FISHING, 0xA6 },
    { OBJ_EVENT_GFX_PLAYER_F_FISHING, 0xA7 },
    { OBJ_EVENT_GFX_MOSS_ROCK, 0xA8 },
    { OBJ_EVENT_GFX_ICE_ROCK, 0xA9 },
    { OBJ_EVENT_GFX_BOLLARD, 0xAA },
    { 0x1004, 0xAB },
    { 0x1005, 0xAC },
    { 0x1006, 0xAD },
    { 0x1007, 0xAE },
    { 0x1008, 0xAF },
    { 0x1009, 0xB0 },
    { 0x100A, 0xB1 },
    { 0x100B, 0xB2 },
    { 0x100C, 0xB3 },
    { 0x100D, 0xB4 },
    { 0x100E, 0xB5 },
    { (0x1000 + 0xf), 0xB6 },
    { 0x1010, 0xB7 },
    { 0x1011, 0xB8 },
    { 0x1012, 0xB9 },
    { 0x1013, 0xBA },
    { 0x1014, 0xBB },
    { 0x1015, 0xBC },
    { 0x1016, 0xBD },
    { 0x1017, 0xBE },
    { 0x1018, 0xBF },
    { 0x1019, 0xC0 },
    { 0x101A, 0xC1 },
    { 0x101B, 0xC2 },
    { 0x101C, 0xC3 },
    { 0x101D, 0xC4 },
    { 0x101E, 0xC5 },
    { (0x1000 + 0x1f), 0xC6 },
    { 0x1020, 0xC7 },
    { 0x1021, 0xC8 },
    { 0x1022, 0xC9 },
    { 0x1023, 0xCA },
    { 0x1024, 0xCB },
    { 0x1025, 0xCC },
    { 0x1026, 0xCD },
    { 0x1027, 0xCE },
    { 0x1028, 0xCF },
    { 0x1029, 0xD0 },
    { 0x102A, 0xD1 },
    { 0x102B, 0xD2 },
    { 0x102C, 0xD3 },
    { 0x102D, 0xD4 },
    { 0x102E, 0xD5 },
    { (0x1000 + 0x2f), 0xD6 },
    { 0x1030, 0xD7 },
    { 0x1031, 0xD8 },
    { 0x1032, 0xD9 },
    { 0x1033, 0xDA },
    { 0x1034, 0xDB },
    { 0x1035, 0xDC },
    { 0x1036, 0xDD },
    { 0x1037, 0xDE },
    { 0x1038, 0xDF },
    { 0x1039, 0xE0 },
    { 0x103A, 0xE1 },
    { 0x103B, 0xE2 },
    { 0x103C, 0xE3 },
    { 0x103D, 0xE4 },
    { 0x103E, 0xE5 },
    { (0x1000 + 0x3f), 0xE6 },
    { 0x1040, 0xE7 },
    { 0x1041, 0xE8 },
    { 0x1042, 0xE9 },
    { 0x1043, 0xEA },
    { 0x1044, 0xEB },
    { 0x1045, 0xEC },
    { 0x1046, 0xED },
    { 0x1047, 0xEE },
    { 0x1048, 0xEF },
    { 0x1049, 0xF0 },
    { 0x104A, 0xF1 },
    { 0x104B, 0xF2 },
    { 0x104C, 0xF3 },
    { 0x104D, 0xF4 },
    { 0x104E, 0xF5 },
    { (0x1000 + 0x4f), 0xF6 },
    { 0x1050, 0xF7 },
    { 0x1051, 0xF8 },
    { 0x1052, 0xF9 },
    { 0x1053, 0xFA },
    { 0x1054, 0xFB },
    { 0x1055, 0xFC },
    { 0x1056, 0xFD },
    { 0x1057, 0xFE },
    { 0x1058, 0xFF },
    { 0x1059, 0x100 },
    { 0x105A, 0x101 },
    { 0x105B, 0x102 },
    { 0x105C, 0x103 },
    { 0x105D, 0x104 },
    { 0x105E, 0x105 },
    { (0x1000 + 0x5f), 0x106 },
    { 0x1060, 0x107 },
    { 0x1061, 0x108 },
    { 0x1062, 0x109 },
    { 0x1063, 0x10A },
    { 0x1064, 0x10B },
    { 0x1065, 0x10C },
    { 0x1066, 0x10D },
    { 0x1067, 0x10E },
    { 0x1068, 0x10F },
    { 0x1069, 0x110 },
    { 0x106A, 0x111 },
    { 0x106B, 0x112 },
    { 0x106C, 0x113 },
    { 0x106D, 0x114 },
    { 0x106E, 0x115 },
    { (0x1000 + 0x6f), 0x116 },
    { 0x1070, 0x117 },
    { 0x1071, 0x118 },
    { 0x1072, 0x119 },
    { 0x1073, 0x11A },
    { 0x1074, 0x11B },
    { 0x1075, 0x11C },
    { 0x1076, 0x11D },
    { 0x1077, 0x11E },
    { 0x1078, 0x11F },
    { 0x1079, 0x120 },
    { 0x107A, 0x121 },
    { 0x107B, 0x122 },
    { 0x107C, 0x123 },
    { 0x107D, 0x124 },
    { 0x107E, 0x125 },
    { (0x1000 + 0x7f), 0x126 },
    { 0x1080, 0x127 },
    { 0x1081, 0x128 },
    { 0x1082, 0x129 },
    { 0x1083, 0x12A },
    { 0x1084, 0x12B },
    { 0x1085, 0x12C },
    { 0x1086, 0x12D },
    { 0x1087, 0x12E },
    { 0x1088, 0x12F },
    { 0x1089, 0x130 },
    { 0x108A, 0x131 },
    { 0x108B, 0x132 },
    { 0x108C, 0x133 },
    { 0x108D, 0x134 },
    { 0x108E, 0x135 },
    { (0x1000 + 0x8f), 0x136 },
    { 0x1090, 0x137 },
    { 0x1091, 0x138 },
    { 0x1092, 0x139 },
    { 0x1093, 0x13A },
    { 0x1094, 0x13B },
    { 0x1095, 0x13C },
    { 0x1096, 0x13D },
    { 0x1097, 0x13E },
    { 0x1098, 0x13F },
    { 0x1099, 0x140 },
    { 0x109A, 0x141 },
    { 0x109B, 0x142 },
    { 0x109C, 0x143 },
    { 0x109D, 0x144 },
    { 0x109E, 0x145 },
    { (0x1000 + 0x9f), 0x146 },
    { 0x10A0, 0x147 },
    { 0x10A1, 0x148 },
    { 0x10A2, 0x149 },
    { 0x10A3, 0x14A },
    { 0x10A4, 0x14B },
    { 0x10A5, 0x14C },
    { 0x10A6, 0x14D },
    { 0x10A7, 0x14E },
    { 0x10A8, 0x14F },
    { 0x10A9, 0x150 },
    { 0x10AA, 0x151 },
    { 0x10AB, 0x152 },
    { 0x10AC, 0x153 },
    { 0x10AD, 0x154 },
    { 0x10AE, 0x155 },
    { (0x1000 + 0xaf), 0x156 },
    { 0x10B0, 0x157 },
    { 0x10B1, 0x158 },
    { 0x10B2, 0x159 },
    { 0x10B3, 0x15A },
    { 0x10B4, 0x15B },
    { 0x10B5, 0x15C },
    { 0x10B6, 0x15D },
    { 0x10B7, 0x15E },
    { 0x10B8, 0x15F },
    { 0x10B9, 0x160 },
    { 0x10BA, 0x161 },
    { 0x10BB, 0x162 },
    { 0x10BC, 0x163 },
    { 0x10BD, 0x164 },
    { 0x10BE, 0x165 },
    { (0x1000 + 0xbf), 0x166 },
    { 0x10C0, 0x167 },
    { OBJ_EVENT_GFX_MYSTERY_GIFT_DELIVERYMAN, 0x169 },
    { OBJ_EVENT_GFX_KID_WITH_NDS, 0x168 },
    { OBJ_EVENT_GFX_MAGIKARP, 0x16A },
    { OBJ_EVENT_GFX_PLAYER_M_POKETCH, 0x16B },
    { OBJ_EVENT_GFX_PLAYER_F_POKETCH, 0x16C },
    { OBJ_EVENT_GFX_PLAYER_M_SAVE, 0x16D },
    { OBJ_EVENT_GFX_PLAYER_F_SAVE, 0x16E },
    { OBJ_EVENT_GFX_UNK_200, 0x16F },
    { OBJ_EVENT_GFX_UNK_201, 0x170 },
    { OBJ_EVENT_GFX_GALACTIC_HQ_DOOR, 0x171 },
    { OBJ_EVENT_GFX_CAVE_PAINTING, 0x172 },
    { OBJ_EVENT_GFX_PACHIRISU, 0x173 },
    { OBJ_EVENT_GFX_SHROOMISH, 0x174 },
    { OBJ_EVENT_GFX_BUNEARY, 0x175 },
    { OBJ_EVENT_GFX_HAPPINY, 0x176 },
    { OBJ_EVENT_GFX_MACHOP, 0x177 },
    { OBJ_EVENT_GFX_PLAYER_M_HEARTHOME_GYM, 0x5A },
    { OBJ_EVENT_GFX_PLAYER_F_HEARTHOME_GYM, 0x5B },
    { OBJ_EVENT_GFX_UNK_212, 0x5A },
    { OBJ_EVENT_GFX_LOOKER, 0x178 },
    { OBJ_EVENT_GFX_CHARON, 0x179 },
    { OBJ_EVENT_GFX_THORTON, 0x17A },
    { OBJ_EVENT_GFX_ARGENTA, 0x17B },
    { OBJ_EVENT_GFX_DARACH, 0x17C },
    { OBJ_EVENT_GFX_DAHLIA, 0x17D },
    { OBJ_EVENT_GFX_CAITLIN, 0x17E },
    { OBJ_EVENT_GFX_TURTWIG, 0x17F },
    { OBJ_EVENT_GFX_GROTLE, 0x180 },
    { OBJ_EVENT_GFX_TORTERRA, 0x181 },
    { OBJ_EVENT_GFX_CHIMCHAR, 0x182 },
    { OBJ_EVENT_GFX_MONFERNO, 0x183 },
    { OBJ_EVENT_GFX_INFERNAPE, 0x184 },
    { OBJ_EVENT_GFX_PIPLUP, 0x185 },
    { OBJ_EVENT_GFX_PRINPLUP, 0x186 },
    { OBJ_EVENT_GFX_EMPOLEON, 0x187 },
    { OBJ_EVENT_GFX_CROAGUNK, 0x188 },
    { OBJ_EVENT_GFX_GIRATINA_ORIGIN, 0x189 },
    { OBJ_EVENT_GFX_FRONTIER_SINGLE_ATTENDANT, 0x18A },
    { OBJ_EVENT_GFX_FRONTIER_MULTI_ATTENDANT, 0x18B },
    { OBJ_EVENT_GFX_FRONTIER_BOOTH_ATTENDANT, 0x18C },
    { OBJ_EVENT_GFX_WIFI_PLAZA_ATTENDANT_M, 0x18D },
    { OBJ_EVENT_GFX_WIFI_PLAZA_ATTENDANT_F, 0x18E },
    { OBJ_EVENT_GFX_PIKACHU_UNUSED, 0x18F },
    { OBJ_EVENT_GFX_ROTOM_HEAT, 0x190 },
    { OBJ_EVENT_GFX_ROTOM_FAN, 0x191 },
    { OBJ_EVENT_GFX_ROTOM_FROST, 0x192 },
    { OBJ_EVENT_GFX_ROTOM_WASH, 0x193 },
    { OBJ_EVENT_GFX_ROTOM_MOW, 0x194 },
    { OBJ_EVENT_GFX_GAME_DIRECTOR, 0x195 },
    { OBJ_EVENT_GFX_OVEN_UNUSED, 0x196 },
    { OBJ_EVENT_GFX_FAN_UNUSED, 0x197 },
    { OBJ_EVENT_GFX_FRIDGE_UNUSED, 0x198 },
    { OBJ_EVENT_GFX_WASHING_MACHINE_UNUSED, 0x199 },
    { OBJ_EVENT_GFX_LAWNMOWER_UNUSED, 0x19A },
    { OBJ_EVENT_GFX_GRUNTS_GROUP_OF_4, 0x19B },
    { OBJ_EVENT_GFX_GRUNTS_GROUP_OF_3, 0x19C },
    { OBJ_EVENT_GFX_CAVE_PAINTING_SHARDS_LEFT, 0x19D },
    { OBJ_EVENT_GFX_CAVE_PAINTING_SHARDS_RIGHT, 0x19E },
    { OBJ_EVENT_GFX_DP_PLAYER_M, 0x1A1 },
    { OBJ_EVENT_GFX_DP_PLAYER_F, 0x1A2 },
    { OBJ_EVENT_GFX_UNK_254, 0x1A3 },
    { OBJ_EVENT_GFX_UNK_255, 0x1A4 },
    { OBJ_EVENT_GFX_PLAYER_M_VS_SEEKER, 0x19F },
    { OBJ_EVENT_GFX_PLAYER_F_VS_SEEKER, 0x1A0 },
    { 0x102, 0x9F },
    { 0x103, 0xA0 },
    { 0x104, 0x9B },
    { 0x105, 0x9C },
    { 0x107, 0x5B },
    { 0x108, 0x83 },
    { 0x109, 0x82 },
    { 0x10A, 0x83 },
    { 0x10B, 0x84 },
    { 0x10C, 0x16D },
    { 0x10D, 0x16E },
    { 0x10E, 0x16B },
    { 0x10f, 0x16C },
    { 0x110, 0x16D },
    { 0x111, 0x16E },
    { 0x112, 0x16B },
    { 0x113, 0x16C },
    { OBJ_EVENT_GFX_PKMN_BULBASAUR, 0x1d8 },  // SPECIES_BULBASAUR
    { OBJ_EVENT_GFX_PKMN_IVYSAUR, 0x1d9 },  // SPECIES_IVYSAUR
    { OBJ_EVENT_GFX_PKMN_VENUSAUR, 0x1da },  // SPECIES_VENUSAUR
    { OBJ_EVENT_GFX_PKMN_VENUSAUR_F, 0x1db },  // female
    { OBJ_EVENT_GFX_PKMN_CHARMANDER, 0x1dc },  // SPECIES_CHARMANDER
    { OBJ_EVENT_GFX_PKMN_CHARMELEON, 0x1dd },  // SPECIES_CHARMELEON
    { OBJ_EVENT_GFX_PKMN_CHARIZARD, 0x1de },  // SPECIES_CHARIZARD
    { OBJ_EVENT_GFX_PKMN_SQUIRTLE, 0x1df },  // SPECIES_SQUIRTLE
    { OBJ_EVENT_GFX_PKMN_WARTORTLE, 0x1e0 },  // SPECIES_WARTORTLE
    { OBJ_EVENT_GFX_PKMN_BLASTOISE, 0x1e1 },  // SPECIES_BLASTOISE
    { OBJ_EVENT_GFX_PKMN_CATERPIE, 0x1e2 },  // SPECIES_CATERPIE
    { OBJ_EVENT_GFX_PKMN_METAPOD, 0x1e3 },  // SPECIES_METAPOD
    { OBJ_EVENT_GFX_PKMN_BUTTERFREE, 0x1e4 },  // SPECIES_BUTTERFREE
    { OBJ_EVENT_GFX_PKMN_WEEDLE, 0x1e5 },  // SPECIES_WEEDLE
    { OBJ_EVENT_GFX_PKMN_KAKUNA, 0x1e6 },  // SPECIES_KAKUNA
    { OBJ_EVENT_GFX_PKMN_BEEDRILL, 0x1e7 },  // SPECIES_BEEDRILL
    { OBJ_EVENT_GFX_PKMN_PIDGEY, 0x1e8 },  // SPECIES_PIDGEY
    { OBJ_EVENT_GFX_PKMN_PIDGEOTTO, 0x1e9 },  // SPECIES_PIDGEOTTO
    { OBJ_EVENT_GFX_PKMN_PIDGEOT, 0x1ea },  // SPECIES_PIDGEOT
    { OBJ_EVENT_GFX_PKMN_RATTATA, 0x1eb },  // SPECIES_RATTATA
    { OBJ_EVENT_GFX_PKMN_RATICATE, 0x1ec },  // SPECIES_RATICATE
    { OBJ_EVENT_GFX_PKMN_SPEAROW, 0x1ed },  // SPECIES_SPEAROW
    { OBJ_EVENT_GFX_PKMN_FEAROW, 0x1ee },  // SPECIES_FEAROW
    { OBJ_EVENT_GFX_PKMN_EKANS, 0x1ef },  // SPECIES_EKANS
    { OBJ_EVENT_GFX_PKMN_ARBOK, 0x1f0 },  // SPECIES_ARBOK
    { OBJ_EVENT_GFX_PKMN_PIKACHU, 0x1f1 },  // SPECIES_PIKACHU
    { OBJ_EVENT_GFX_PKMN_PIKACHU_F, 0x1f2 },  // female
    { OBJ_EVENT_GFX_PKMN_RAICHU, 0x1f3 },  // SPECIES_RAICHU
    { OBJ_EVENT_GFX_PKMN_SANDSHREW, 0x1f4 },  // SPECIES_SANDSHREW
    { OBJ_EVENT_GFX_PKMN_SANDSLASH, 0x1f5 },  // SPECIES_SANDSLASH
    { OBJ_EVENT_GFX_PKMN_NIDORAN_F, 0x1f6 },  // SPECIES_NIDORAN_F
    { OBJ_EVENT_GFX_PKMN_NIDORINA, 0x1f7 },  // SPECIES_NIDORINA
    { OBJ_EVENT_GFX_PKMN_NIDOQUEEN, 0x1f8 },  // SPECIES_NIDOQUEEN
    { OBJ_EVENT_GFX_PKMN_NIDORAN_M, 0x1f9 },  // SPECIES_NIDORAN_M
    { OBJ_EVENT_GFX_PKMN_NIDORINO, 0x1fa },  // SPECIES_NIDORINO
    { OBJ_EVENT_GFX_PKMN_NIDOKING, 0x1fb },  // SPECIES_NIDOKING
    { OBJ_EVENT_GFX_PKMN_CLEFAIRY, 0x1fc },  // SPECIES_CLEFAIRY
    { OBJ_EVENT_GFX_PKMN_CLEFABLE, 0x1fd },  // SPECIES_CLEFABLE
    { OBJ_EVENT_GFX_PKMN_VULPIX, 0x1fe },  // SPECIES_VULPIX
    { OBJ_EVENT_GFX_PKMN_NINETALES, 0x1ff },  // SPECIES_NINETALES
    { OBJ_EVENT_GFX_PKMN_JIGGLYPUFF, 0x200 },  // SPECIES_JIGGLYPUFF
    { OBJ_EVENT_GFX_PKMN_WIGGLYTUFF, 0x201 },  // SPECIES_WIGGLYTUFF
    { OBJ_EVENT_GFX_PKMN_ZUBAT, 0x202 },  // SPECIES_ZUBAT
    { OBJ_EVENT_GFX_PKMN_GOLBAT, 0x203 },  // SPECIES_GOLBAT
    { OBJ_EVENT_GFX_PKMN_ODDISH, 0x204 },  // SPECIES_ODDISH
    { OBJ_EVENT_GFX_PKMN_GLOOM, 0x205 },  // SPECIES_GLOOM
    { OBJ_EVENT_GFX_PKMN_VILEPLUME, 0x206 },  // SPECIES_VILEPLUME
    { OBJ_EVENT_GFX_PKMN_PARAS, 0x207 },  // SPECIES_PARAS
    { OBJ_EVENT_GFX_PKMN_PARASECT, 0x208 },  // SPECIES_PARASECT
    { OBJ_EVENT_GFX_PKMN_VENONAT, 0x209 },  // SPECIES_VENONAT
    { OBJ_EVENT_GFX_PKMN_VENOMOTH, 0x20a },  // SPECIES_VENOMOTH
    { OBJ_EVENT_GFX_PKMN_DIGLETT, 0x20b },  // SPECIES_DIGLETT
    { OBJ_EVENT_GFX_PKMN_DUGTRIO, 0x20c },  // SPECIES_DUGTRIO
    { OBJ_EVENT_GFX_PKMN_MEOWTH, 0x20d },  // SPECIES_MEOWTH
    { OBJ_EVENT_GFX_PKMN_PERSIAN, 0x20e },  // SPECIES_PERSIAN
    { OBJ_EVENT_GFX_PKMN_PSYDUCK, 0x20f },  // SPECIES_PSYDUCK
    { OBJ_EVENT_GFX_PKMN_GOLDUCK, 0x210 },  // SPECIES_GOLDUCK
    { OBJ_EVENT_GFX_PKMN_MANKEY, 0x211 },  // SPECIES_MANKEY
    { OBJ_EVENT_GFX_PKMN_PRIMEAPE, 0x212 },  // SPECIES_PRIMEAPE
    { OBJ_EVENT_GFX_PKMN_GROWLITHE, 0x213 },  // SPECIES_GROWLITHE
    { OBJ_EVENT_GFX_PKMN_ARCANINE, 0x214 },  // SPECIES_ARCANINE
    { OBJ_EVENT_GFX_PKMN_POLIWAG, 0x215 },  // SPECIES_POLIWAG
    { OBJ_EVENT_GFX_PKMN_POLIWHIRL, 0x216 },  // SPECIES_POLIWHIRL
    { OBJ_EVENT_GFX_PKMN_POLIWRATH, 0x217 },  // SPECIES_POLIWRATH
    { OBJ_EVENT_GFX_PKMN_ABRA, 0x218 },  // SPECIES_ABRA
    { OBJ_EVENT_GFX_PKMN_KADABRA, 0x219 },  // SPECIES_KADABRA
    { OBJ_EVENT_GFX_PKMN_ALAKAZAM, 0x21a },  // SPECIES_ALAKAZAM
    { OBJ_EVENT_GFX_PKMN_MACHOP, 0x21b },  // SPECIES_MACHOP
    { OBJ_EVENT_GFX_PKMN_MACHOKE, 0x21c },  // SPECIES_MACHOKE
    { OBJ_EVENT_GFX_PKMN_MACHAMP, 0x21d },  // SPECIES_MACHAMP
    { OBJ_EVENT_GFX_PKMN_BELLSPROUT, 0x21e },  // SPECIES_BELLSPROUT
    { OBJ_EVENT_GFX_PKMN_WEEPINBELL, 0x21f },  // SPECIES_WEEPINBELL
    { OBJ_EVENT_GFX_PKMN_VICTREEBEL, 0x220 },  // SPECIES_VICTREEBEL
    { OBJ_EVENT_GFX_PKMN_TENTACOOL, 0x221 },  // SPECIES_TENTACOOL
    { OBJ_EVENT_GFX_PKMN_TENTACRUEL, 0x222 },  // SPECIES_TENTACRUEL
    { OBJ_EVENT_GFX_PKMN_GEODUDE, 0x223 },  // SPECIES_GEODUDE
    { OBJ_EVENT_GFX_PKMN_GRAVELER, 0x224 },  // SPECIES_GRAVELER
    { OBJ_EVENT_GFX_PKMN_GOLEM, 0x225 },  // SPECIES_GOLEM
    { OBJ_EVENT_GFX_PKMN_PONYTA, 0x226 },  // SPECIES_PONYTA
    { OBJ_EVENT_GFX_PKMN_RAPIDASH, 0x227 },  // SPECIES_RAPIDASH
    { OBJ_EVENT_GFX_PKMN_SLOWPOKE, 0x228 },  // SPECIES_SLOWPOKE
    { OBJ_EVENT_GFX_PKMN_SLOWBRO, 0x229 },  // SPECIES_SLOWBRO
    { OBJ_EVENT_GFX_PKMN_MAGNEMITE, 0x22a },  // SPECIES_MAGNEMITE
    { OBJ_EVENT_GFX_PKMN_MAGNETON, 0x22b },  // SPECIES_MAGNETON
    { OBJ_EVENT_GFX_PKMN_FARFETCHD, 0x22c },  // SPECIES_FARFETCHD
    { OBJ_EVENT_GFX_PKMN_DODUO, 0x22d },  // SPECIES_DODUO
    { OBJ_EVENT_GFX_PKMN_DODRIO, 0x22e },  // SPECIES_DODRIO
    { OBJ_EVENT_GFX_PKMN_SEEL, 0x22f },  // SPECIES_SEEL
    { OBJ_EVENT_GFX_PKMN_DEWGONG, 0x230 },  // SPECIES_DEWGONG
    { OBJ_EVENT_GFX_PKMN_GRIMER, 0x231 },  // SPECIES_GRIMER
    { OBJ_EVENT_GFX_PKMN_MUK, 0x232 },  // SPECIES_MUK
    { OBJ_EVENT_GFX_PKMN_SHELLDER, 0x233 },  // SPECIES_SHELLDER
    { OBJ_EVENT_GFX_PKMN_CLOYSTER, 0x234 },  // SPECIES_CLOYSTER
    { OBJ_EVENT_GFX_PKMN_GASTLY, 0x235 },  // SPECIES_GASTLY
    { OBJ_EVENT_GFX_PKMN_HAUNTER, 0x236 },  // SPECIES_HAUNTER
    { OBJ_EVENT_GFX_PKMN_GENGAR, 0x237 },  // SPECIES_GENGAR
    { OBJ_EVENT_GFX_PKMN_ONIX, 0x238 },  // SPECIES_ONIX
    { OBJ_EVENT_GFX_PKMN_DROWZEE, 0x239 },  // SPECIES_DROWZEE
    { OBJ_EVENT_GFX_PKMN_HYPNO, 0x23a },  // SPECIES_HYPNO
    { OBJ_EVENT_GFX_PKMN_KRABBY, 0x23b },  // SPECIES_KRABBY
    { OBJ_EVENT_GFX_PKMN_KINGLER, 0x23c },  // SPECIES_KINGLER
    { OBJ_EVENT_GFX_PKMN_VOLTORB, 0x23d },  // SPECIES_VOLTORB
    { OBJ_EVENT_GFX_PKMN_ELECTRODE, 0x23e },  // SPECIES_ELECTRODE
    { OBJ_EVENT_GFX_PKMN_EXEGGCUTE, 0x23f },  // SPECIES_EXEGGCUTE
    { OBJ_EVENT_GFX_PKMN_EXEGGUTOR, 0x240 },  // SPECIES_EXEGGUTOR
    { OBJ_EVENT_GFX_PKMN_CUBONE, 0x241 },  // SPECIES_CUBONE
    { OBJ_EVENT_GFX_PKMN_MAROWAK, 0x242 },  // SPECIES_MAROWAK
    { OBJ_EVENT_GFX_PKMN_HITMONLEE, 0x243 },  // SPECIES_HITMONLEE
    { OBJ_EVENT_GFX_PKMN_HITMONCHAN, 0x244 },  // SPECIES_HITMONCHAN
    { OBJ_EVENT_GFX_PKMN_LICKITUNG, 0x245 },  // SPECIES_LICKITUNG
    { OBJ_EVENT_GFX_PKMN_KOFFING, 0x246 },  // SPECIES_KOFFING
    { OBJ_EVENT_GFX_PKMN_WEEZING, 0x247 },  // SPECIES_WEEZING
    { OBJ_EVENT_GFX_PKMN_RHYHORN, 0x248 },  // SPECIES_RHYHORN
    { OBJ_EVENT_GFX_PKMN_RHYDON, 0x249 },  // SPECIES_RHYDON
    { OBJ_EVENT_GFX_PKMN_CHANSEY, 0x24a },  // SPECIES_CHANSEY
    { OBJ_EVENT_GFX_PKMN_TANGELA, 0x24b },  // SPECIES_TANGELA
    { OBJ_EVENT_GFX_PKMN_KANGASKHAN, 0x24c },  // SPECIES_KANGASKHAN
    { OBJ_EVENT_GFX_PKMN_HORSEA, 0x24d },  // SPECIES_HORSEA
    { OBJ_EVENT_GFX_PKMN_SEADRA, 0x24e },  // SPECIES_SEADRA
    { OBJ_EVENT_GFX_PKMN_GOLDEEN, 0x24f },  // SPECIES_GOLDEEN
    { OBJ_EVENT_GFX_PKMN_SEAKING, 0x250 },  // SPECIES_SEAKING
    { OBJ_EVENT_GFX_PKMN_STARYU, 0x251 },  // SPECIES_STARYU
    { OBJ_EVENT_GFX_PKMN_STARMIE, 0x252 },  // SPECIES_STARMIE
    { OBJ_EVENT_GFX_PKMN_MR_MIME, 0x253 },  // SPECIES_MR_MIME
    { OBJ_EVENT_GFX_PKMN_SCYTHER, 0x254 },  // SPECIES_SCYTHER
    { OBJ_EVENT_GFX_PKMN_JYNX, 0x255 },  // SPECIES_JYNX
    { OBJ_EVENT_GFX_PKMN_ELECTABUZZ, 0x256 },  // SPECIES_ELECTABUZZ
    { OBJ_EVENT_GFX_PKMN_MAGMAR, 0x257 },  // SPECIES_MAGMAR
    { OBJ_EVENT_GFX_PKMN_PINSIR, 0x258 },  // SPECIES_PINSIR
    { OBJ_EVENT_GFX_PKMN_TAUROS, 0x259 },  // SPECIES_TAUROS
    { OBJ_EVENT_GFX_PKMN_MAGIKARP, 0x25a },  // SPECIES_MAGIKARP
    { OBJ_EVENT_GFX_PKMN_GYARADOS, 0x25b },  // SPECIES_GYARADOS
    { OBJ_EVENT_GFX_PKMN_LAPRAS, 0x25c },  // SPECIES_LAPRAS
    { OBJ_EVENT_GFX_PKMN_DITTO, 0x25d },  // SPECIES_DITTO
    { OBJ_EVENT_GFX_PKMN_EEVEE, 0x25e },  // SPECIES_EEVEE
    { OBJ_EVENT_GFX_PKMN_VAPOREON, 0x25f },  // SPECIES_VAPOREON
    { OBJ_EVENT_GFX_PKMN_JOLTEON, 0x260 },  // SPECIES_JOLTEON
    { OBJ_EVENT_GFX_PKMN_FLAREON, 0x261 },  // SPECIES_FLAREON
    { OBJ_EVENT_GFX_PKMN_PORYGON, 0x262 },  // SPECIES_PORYGON
    { OBJ_EVENT_GFX_PKMN_OMANYTE, 0x263 },  // SPECIES_OMANYTE
    { OBJ_EVENT_GFX_PKMN_OMASTAR, 0x264 },  // SPECIES_OMASTAR
    { OBJ_EVENT_GFX_PKMN_KABUTO, 0x265 },  // SPECIES_KABUTO
    { OBJ_EVENT_GFX_PKMN_KABUTOPS, 0x266 },  // SPECIES_KABUTOPS
    { OBJ_EVENT_GFX_PKMN_AERODACTYL, 0x267 },  // SPECIES_AERODACTYL
    { OBJ_EVENT_GFX_PKMN_SNORLAX, 0x268 },  // SPECIES_SNORLAX
    { OBJ_EVENT_GFX_PKMN_ARTICUNO, 0x269 },  // SPECIES_ARTICUNO
    { OBJ_EVENT_GFX_PKMN_ZAPDOS, 0x26a },  // SPECIES_ZAPDOS
    { OBJ_EVENT_GFX_PKMN_MOLTRES, 0x26b },  // SPECIES_MOLTRES
    { OBJ_EVENT_GFX_PKMN_DRATINI, 0x26c },  // SPECIES_DRATINI
    { OBJ_EVENT_GFX_PKMN_DRAGONAIR, 0x26d },  // SPECIES_DRAGONAIR
    { OBJ_EVENT_GFX_PKMN_DRAGONITE, 0x26e },  // SPECIES_DRAGONITE
    { OBJ_EVENT_GFX_PKMN_MEWTWO, 0x26f },  // SPECIES_MEWTWO
    { OBJ_EVENT_GFX_PKMN_MEW, 0x270 },  // SPECIES_MEW
    { OBJ_EVENT_GFX_PKMN_CHIKORITA, 0x271 },  // SPECIES_CHIKORITA
    { OBJ_EVENT_GFX_PKMN_BAYLEEF, 0x272 },  // SPECIES_BAYLEEF
    { OBJ_EVENT_GFX_PKMN_BAYLEEF_F, 0x273 },  // female
    { OBJ_EVENT_GFX_PKMN_CYNDAQUIL, 0x274 },  // SPECIES_CYNDAQUIL
    { OBJ_EVENT_GFX_PKMN_QUILAVA, 0x275 },  // SPECIES_QUILAVA
    { OBJ_EVENT_GFX_PKMN_TYPHLOSION, 0x276 },  // SPECIES_TYPHLOSION
    { OBJ_EVENT_GFX_PKMN_TOTODILE, 0x277 },  // SPECIES_TOTODILE
    { OBJ_EVENT_GFX_PKMN_CROCONAW, 0x278 },  // SPECIES_CROCONAW
    { OBJ_EVENT_GFX_PKMN_FERALIGATR, 0x279 },  // SPECIES_FERALIGATR
    { OBJ_EVENT_GFX_PKMN_SENTRET, 0x27a },  // SPECIES_SENTRET
    { OBJ_EVENT_GFX_PKMN_FURRET, 0x27b },  // SPECIES_FURRET
    { OBJ_EVENT_GFX_PKMN_HOOTHOOT, 0x27c },  // SPECIES_HOOTHOOT
    { OBJ_EVENT_GFX_PKMN_NOCTOWL, 0x27d },  // SPECIES_NOCTOWL
    { OBJ_EVENT_GFX_PKMN_LEDYBA, 0x27e },  // SPECIES_LEDYBA
    { OBJ_EVENT_GFX_PKMN_LEDIAN, 0x27f },  // SPECIES_LEDIAN
    { OBJ_EVENT_GFX_PKMN_SPINARAK, 0x280 },  // SPECIES_SPINARAK
    { OBJ_EVENT_GFX_PKMN_ARIADOS, 0x281 },  // SPECIES_ARIADOS
    { OBJ_EVENT_GFX_PKMN_CROBAT, 0x282 },  // SPECIES_CROBAT
    { OBJ_EVENT_GFX_PKMN_CHINCHOU, 0x283 },  // SPECIES_CHINCHOU
    { OBJ_EVENT_GFX_PKMN_LANTURN, 0x284 },  // SPECIES_LANTURN
    { OBJ_EVENT_GFX_PKMN_PICHU, 0x285 },  // SPECIES_PICHU
    { OBJ_EVENT_GFX_PKMN_CLEFFA, 0x286 },  // SPECIES_CLEFFA
    { OBJ_EVENT_GFX_PKMN_IGGLYBUFF, 0x287 },  // SPECIES_IGGLYBUFF
    { OBJ_EVENT_GFX_PKMN_TOGEPI, 0x288 },  // SPECIES_TOGEPI
    { OBJ_EVENT_GFX_PKMN_TOGETIC, 0x289 },  // SPECIES_TOGETIC
    { OBJ_EVENT_GFX_PKMN_NATU, 0x28a },  // SPECIES_NATU
    { OBJ_EVENT_GFX_PKMN_XATU, 0x28b },  // SPECIES_XATU
    { OBJ_EVENT_GFX_PKMN_MAREEP, 0x28c },  // SPECIES_MAREEP
    { OBJ_EVENT_GFX_PKMN_FLAAFFY, 0x28d },  // SPECIES_FLAAFFY
    { OBJ_EVENT_GFX_PKMN_AMPHAROS, 0x28e },  // SPECIES_AMPHAROS
    { OBJ_EVENT_GFX_PKMN_BELLOSSOM, 0x28f },  // SPECIES_BELLOSSOM
    { OBJ_EVENT_GFX_PKMN_MARILL, 0x290 },  // SPECIES_MARILL
    { OBJ_EVENT_GFX_PKMN_AZUMARILL, 0x291 },  // SPECIES_AZUMARILL
    { OBJ_EVENT_GFX_PKMN_SUDOWOODO, 0x292 },  // SPECIES_SUDOWOODO
    { OBJ_EVENT_GFX_PKMN_POLITOED, 0x293 },  // SPECIES_POLITOED
    { OBJ_EVENT_GFX_PKMN_HOPPIP, 0x294 },  // SPECIES_HOPPIP
    { OBJ_EVENT_GFX_PKMN_SKIPLOOM, 0x295 },  // SPECIES_SKIPLOOM
    { OBJ_EVENT_GFX_PKMN_JUMPLUFF, 0x296 },  // SPECIES_JUMPLUFF
    { OBJ_EVENT_GFX_PKMN_AIPOM, 0x297 },  // SPECIES_AIPOM
    { OBJ_EVENT_GFX_PKMN_SUNKERN, 0x298 },  // SPECIES_SUNKERN
    { OBJ_EVENT_GFX_PKMN_SUNFLORA, 0x299 },  // SPECIES_SUNFLORA
    { OBJ_EVENT_GFX_PKMN_YANMA, 0x29a },  // SPECIES_YANMA
    { OBJ_EVENT_GFX_PKMN_WOOPER, 0x29b },  // SPECIES_WOOPER
    { OBJ_EVENT_GFX_PKMN_QUAGSIRE, 0x29c },  // SPECIES_QUAGSIRE
    { OBJ_EVENT_GFX_PKMN_ESPEON, 0x29d },  // SPECIES_ESPEON
    { OBJ_EVENT_GFX_PKMN_UMBREON, 0x29e },  // SPECIES_UMBREON
    { OBJ_EVENT_GFX_PKMN_MURKROW, 0x29f },  // SPECIES_MURKROW
    { OBJ_EVENT_GFX_PKMN_SLOWKING, 0x2a0 },  // SPECIES_SLOWKING
    { OBJ_EVENT_GFX_PKMN_MISDREAVUS, 0x2a1 },  // SPECIES_MISDREAVUS
    { OBJ_EVENT_GFX_PKMN_UNOWN, 0x2a2 },  // SPECIES_UNOWN
    { OBJ_EVENT_GFX_PKMN_WOBBUFFET, 0x2a3 },  // SPECIES_WOBBUFFET
    { OBJ_EVENT_GFX_PKMN_WOBBUFFET_F, 0x2a4 },  // female
    { OBJ_EVENT_GFX_PKMN_GIRAFARIG, 0x2a5 },  // SPECIES_GIRAFARIG
    { OBJ_EVENT_GFX_PKMN_PINECO, 0x2a6 },  // SPECIES_PINECO
    { OBJ_EVENT_GFX_PKMN_FORRETRESS, 0x2a7 },  // SPECIES_FORRETRESS
    { OBJ_EVENT_GFX_PKMN_DUNSPARCE, 0x2a8 },  // SPECIES_DUNSPARCE
    { OBJ_EVENT_GFX_PKMN_GLIGAR, 0x2a9 },  // SPECIES_GLIGAR
    { OBJ_EVENT_GFX_PKMN_STEELIX, 0x2aa },  // SPECIES_STEELIX
    { OBJ_EVENT_GFX_PKMN_STEELIX_F, 0x2ab },  // female
    { OBJ_EVENT_GFX_PKMN_SNUBBULL, 0x2ac },  // SPECIES_SNUBBULL
    { OBJ_EVENT_GFX_PKMN_GRANBULL, 0x2ad },  // SPECIES_GRANBULL
    { OBJ_EVENT_GFX_PKMN_QWILFISH, 0x2ae },  // SPECIES_QWILFISH
    { OBJ_EVENT_GFX_PKMN_SCIZOR, 0x2af },  // SPECIES_SCIZOR
    { OBJ_EVENT_GFX_PKMN_SHUCKLE, 0x2b0 },  // SPECIES_SHUCKLE
    { OBJ_EVENT_GFX_PKMN_HERACROSS, 0x2b1 },  // SPECIES_HERACROSS
    { OBJ_EVENT_GFX_PKMN_HERACROSS_F, 0x2b2 },  // female
    { OBJ_EVENT_GFX_PKMN_SNEASEL, 0x2b3 },  // SPECIES_SNEASEL
    { OBJ_EVENT_GFX_PKMN_TEDDIURSA, 0x2b4 },  // SPECIES_TEDDIURSA
    { OBJ_EVENT_GFX_PKMN_URSARING, 0x2b5 },  // SPECIES_URSARING
    { OBJ_EVENT_GFX_PKMN_SLUGMA, 0x2b6 },  // SPECIES_SLUGMA
    { OBJ_EVENT_GFX_PKMN_MAGCARGO, 0x2b7 },  // SPECIES_MAGCARGO
    { OBJ_EVENT_GFX_PKMN_SWINUB, 0x2b8 },  // SPECIES_SWINUB
    { OBJ_EVENT_GFX_PKMN_PILOSWINE, 0x2b9 },  // SPECIES_PILOSWINE
    { OBJ_EVENT_GFX_PKMN_CORSOLA, 0x2ba },  // SPECIES_CORSOLA
    { OBJ_EVENT_GFX_PKMN_REMORAID, 0x2bb },  // SPECIES_REMORAID
    { OBJ_EVENT_GFX_PKMN_OCTILLERY, 0x2bc },  // SPECIES_OCTILLERY
    { OBJ_EVENT_GFX_PKMN_DELIBIRD, 0x2bd },  // SPECIES_DELIBIRD
    { OBJ_EVENT_GFX_PKMN_MANTINE, 0x2be },  // SPECIES_MANTINE
    { OBJ_EVENT_GFX_PKMN_SKARMORY, 0x2bf },  // SPECIES_SKARMORY
    { OBJ_EVENT_GFX_PKMN_HOUNDOUR, 0x2c0 },  // SPECIES_HOUNDOUR
    { OBJ_EVENT_GFX_PKMN_HOUNDOOM, 0x2c1 },  // SPECIES_HOUNDOOM
    { OBJ_EVENT_GFX_PKMN_KINGDRA, 0x2c2 },  // SPECIES_KINGDRA
    { OBJ_EVENT_GFX_PKMN_PHANPY, 0x2c3 },  // SPECIES_PHANPY
    { OBJ_EVENT_GFX_PKMN_DONPHAN, 0x2c4 },  // SPECIES_DONPHAN
    { OBJ_EVENT_GFX_PKMN_PORYGON2, 0x2c5 },  // SPECIES_PORYGON2
    { OBJ_EVENT_GFX_PKMN_STANTLER, 0x2c6 },  // SPECIES_STANTLER
    { OBJ_EVENT_GFX_PKMN_SMEARGLE, 0x2c7 },  // SPECIES_SMEARGLE
    { OBJ_EVENT_GFX_PKMN_TYROGUE, 0x2c8 },  // SPECIES_TYROGUE
    { OBJ_EVENT_GFX_PKMN_HITMONTOP, 0x2c9 },  // SPECIES_HITMONTOP
    { OBJ_EVENT_GFX_PKMN_SMOOCHUM, 0x2ca },  // SPECIES_SMOOCHUM
    { OBJ_EVENT_GFX_PKMN_ELEKID, 0x2cb },  // SPECIES_ELEKID
    { OBJ_EVENT_GFX_PKMN_MAGBY, 0x2cc },  // SPECIES_MAGBY
    { OBJ_EVENT_GFX_PKMN_MILTANK, 0x2cd },  // SPECIES_MILTANK
    { OBJ_EVENT_GFX_PKMN_BLISSEY, 0x2ce },  // SPECIES_BLISSEY
    { OBJ_EVENT_GFX_PKMN_RAIKOU, 0x2cf },  // SPECIES_RAIKOU
    { OBJ_EVENT_GFX_PKMN_ENTEI, 0x2d0 },  // SPECIES_ENTEI
    { OBJ_EVENT_GFX_PKMN_SUICUNE, 0x2d1 },  // SPECIES_SUICUNE
    { OBJ_EVENT_GFX_PKMN_LARVITAR, 0x2d2 },  // SPECIES_LARVITAR
    { OBJ_EVENT_GFX_PKMN_PUPITAR, 0x2d3 },  // SPECIES_PUPITAR
    { OBJ_EVENT_GFX_PKMN_TYRANITAR, 0x2d4 },  // SPECIES_TYRANITAR
    { OBJ_EVENT_GFX_PKMN_LUGIA, 0x2d5 },  // SPECIES_LUGIA
    { OBJ_EVENT_GFX_PKMN_HO_OH, 0x2d6 },  // SPECIES_HO_OH
    { OBJ_EVENT_GFX_PKMN_CELEBI, 0x2d7 },  // SPECIES_CELEBI
    { OBJ_EVENT_GFX_PKMN_TREECKO, 0x2d8 },  // SPECIES_TREECKO
    { OBJ_EVENT_GFX_PKMN_GROVYLE, 0x2d9 },  // SPECIES_GROVYLE
    { OBJ_EVENT_GFX_PKMN_SCEPTILE, 0x2da },  // SPECIES_SCEPTILE
    { OBJ_EVENT_GFX_PKMN_TORCHIC, 0x2db },  // SPECIES_TORCHIC
    { OBJ_EVENT_GFX_PKMN_COMBUSKEN, 0x2dc },  // SPECIES_COMBUSKEN
    { OBJ_EVENT_GFX_PKMN_BLAZIKEN, 0x2dd },  // SPECIES_BLAZIKEN
    { OBJ_EVENT_GFX_PKMN_MUDKIP, 0x2de },  // SPECIES_MUDKIP
    { OBJ_EVENT_GFX_PKMN_MARSHTOMP, 0x2df },  // SPECIES_MARSHTOMP
    { OBJ_EVENT_GFX_PKMN_SWAMPERT, 0x2e0 },  // SPECIES_SWAMPERT
    { OBJ_EVENT_GFX_PKMN_POOCHYENA, 0x2e1 },  // SPECIES_POOCHYENA
    { OBJ_EVENT_GFX_PKMN_MIGHTYENA, 0x2e2 },  // SPECIES_MIGHTYENA
    { OBJ_EVENT_GFX_PKMN_ZIGZAGOON, 0x2e3 },  // SPECIES_ZIGZAGOON
    { OBJ_EVENT_GFX_PKMN_LINOONE, 0x2e4 },  // SPECIES_LINOONE
    { OBJ_EVENT_GFX_PKMN_WURMPLE, 0x2e5 },  // SPECIES_WURMPLE
    { OBJ_EVENT_GFX_PKMN_SILCOON, 0x2e6 },  // SPECIES_SILCOON
    { OBJ_EVENT_GFX_PKMN_BEAUTIFLY, 0x2e7 },  // SPECIES_BEAUTIFLY
    { OBJ_EVENT_GFX_PKMN_CASCOON, 0x2e8 },  // SPECIES_CASCOON
    { OBJ_EVENT_GFX_PKMN_DUSTOX, 0x2e9 },  // SPECIES_DUSTOX
    { OBJ_EVENT_GFX_PKMN_LOTAD, 0x2ea },  // SPECIES_LOTAD
    { OBJ_EVENT_GFX_PKMN_LOMBRE, 0x2eb },  // SPECIES_LOMBRE
    { OBJ_EVENT_GFX_PKMN_LUDICOLO, 0x2ec },  // SPECIES_LUDICOLO
    { OBJ_EVENT_GFX_PKMN_SEEDOT, 0x2ed },  // SPECIES_SEEDOT
    { OBJ_EVENT_GFX_PKMN_NUZLEAF, 0x2ee },  // SPECIES_NUZLEAF
    { OBJ_EVENT_GFX_PKMN_SHIFTRY, 0x2ef },  // SPECIES_SHIFTRY
    { OBJ_EVENT_GFX_PKMN_TAILLOW, 0x2f0 },  // SPECIES_TAILLOW
    { OBJ_EVENT_GFX_PKMN_SWELLOW, 0x2f1 },  // SPECIES_SWELLOW
    { OBJ_EVENT_GFX_PKMN_WINGULL, 0x2f2 },  // SPECIES_WINGULL
    { OBJ_EVENT_GFX_PKMN_PELIPPER, 0x2f3 },  // SPECIES_PELIPPER
    { OBJ_EVENT_GFX_PKMN_RALTS, 0x2f4 },  // SPECIES_RALTS
    { OBJ_EVENT_GFX_PKMN_KIRLIA, 0x2f5 },  // SPECIES_KIRLIA
    { OBJ_EVENT_GFX_PKMN_GARDEVOIR, 0x2f6 },  // SPECIES_GARDEVOIR
    { OBJ_EVENT_GFX_PKMN_SURSKIT, 0x2f7 },  // SPECIES_SURSKIT
    { OBJ_EVENT_GFX_PKMN_MASQUERAIN, 0x2f8 },  // SPECIES_MASQUERAIN
    { OBJ_EVENT_GFX_PKMN_SHROOMISH, 0x2f9 },  // SPECIES_SHROOMISH
    { OBJ_EVENT_GFX_PKMN_BRELOOM, 0x2fa },  // SPECIES_BRELOOM
    { OBJ_EVENT_GFX_PKMN_SLAKOTH, 0x2fb },  // SPECIES_SLAKOTH
    { OBJ_EVENT_GFX_PKMN_VIGOROTH, 0x2fc },  // SPECIES_VIGOROTH
    { OBJ_EVENT_GFX_PKMN_SLAKING, 0x2fd },  // SPECIES_SLAKING
    { OBJ_EVENT_GFX_PKMN_NINCADA, 0x2fe },  // SPECIES_NINCADA
    { OBJ_EVENT_GFX_PKMN_NINJASK, 0x2ff },  // SPECIES_NINJASK
    { OBJ_EVENT_GFX_PKMN_SHEDINJA, 0x300 },  // SPECIES_SHEDINJA
    { OBJ_EVENT_GFX_PKMN_WHISMUR, 0x301 },  // SPECIES_WHISMUR
    { OBJ_EVENT_GFX_PKMN_LOUDRED, 0x302 },  // SPECIES_LOUDRED
    { OBJ_EVENT_GFX_PKMN_EXPLOUD, 0x303 },  // SPECIES_EXPLOUD
    { OBJ_EVENT_GFX_PKMN_MAKUHITA, 0x304 },  // SPECIES_MAKUHITA
    { OBJ_EVENT_GFX_PKMN_HARIYAMA, 0x305 },  // SPECIES_HARIYAMA
    { OBJ_EVENT_GFX_PKMN_AZURILL, 0x306 },  // SPECIES_AZURILL
    { OBJ_EVENT_GFX_PKMN_NOSEPASS, 0x307 },  // SPECIES_NOSEPASS
    { OBJ_EVENT_GFX_PKMN_SKITTY, 0x308 },  // SPECIES_SKITTY
    { OBJ_EVENT_GFX_PKMN_DELCATTY, 0x309 },  // SPECIES_DELCATTY
    { OBJ_EVENT_GFX_PKMN_SABLEYE, 0x30a },  // SPECIES_SABLEYE
    { OBJ_EVENT_GFX_PKMN_MAWILE, 0x30b },  // SPECIES_MAWILE
    { OBJ_EVENT_GFX_PKMN_ARON, 0x30c },  // SPECIES_ARON
    { OBJ_EVENT_GFX_PKMN_LAIRON, 0x30d },  // SPECIES_LAIRON
    { OBJ_EVENT_GFX_PKMN_AGGRON, 0x30e },  // SPECIES_AGGRON
    { OBJ_EVENT_GFX_PKMN_MEDITITE, 0x30f },  // SPECIES_MEDITITE
    { OBJ_EVENT_GFX_PKMN_MEDICHAM, 0x310 },  // SPECIES_MEDICHAM
    { OBJ_EVENT_GFX_PKMN_ELECTRIKE, 0x311 },  // SPECIES_ELECTRIKE
    { OBJ_EVENT_GFX_PKMN_MANECTRIC, 0x312 },  // SPECIES_MANECTRIC
    { OBJ_EVENT_GFX_PKMN_PLUSLE, 0x313 },  // SPECIES_PLUSLE
    { OBJ_EVENT_GFX_PKMN_MINUN, 0x314 },  // SPECIES_MINUN
    { OBJ_EVENT_GFX_PKMN_VOLBEAT, 0x315 },  // SPECIES_VOLBEAT
    { OBJ_EVENT_GFX_PKMN_ILLUMISE, 0x316 },  // SPECIES_ILLUMISE
    { OBJ_EVENT_GFX_PKMN_ROSELIA, 0x317 },  // SPECIES_ROSELIA
    { OBJ_EVENT_GFX_PKMN_GULPIN, 0x318 },  // SPECIES_GULPIN
    { OBJ_EVENT_GFX_PKMN_SWALOT, 0x319 },  // SPECIES_SWALOT
    { OBJ_EVENT_GFX_PKMN_CARVANHA, 0x31a },  // SPECIES_CARVANHA
    { OBJ_EVENT_GFX_PKMN_SHARPEDO, 0x31b },  // SPECIES_SHARPEDO
    { OBJ_EVENT_GFX_PKMN_WAILMER, 0x31c },  // SPECIES_WAILMER
    { OBJ_EVENT_GFX_PKMN_WAILORD, 0x31d },  // SPECIES_WAILORD
    { OBJ_EVENT_GFX_PKMN_NUMEL, 0x31e },  // SPECIES_NUMEL
    { OBJ_EVENT_GFX_PKMN_CAMERUPT, 0x31f },  // SPECIES_CAMERUPT
    { OBJ_EVENT_GFX_PKMN_TORKOAL, 0x320 },  // SPECIES_TORKOAL
    { OBJ_EVENT_GFX_PKMN_SPOINK, 0x321 },  // SPECIES_SPOINK
    { OBJ_EVENT_GFX_PKMN_GRUMPIG, 0x322 },  // SPECIES_GRUMPIG
    { OBJ_EVENT_GFX_PKMN_SPINDA, 0x323 },  // SPECIES_SPINDA
    { OBJ_EVENT_GFX_PKMN_TRAPINCH, 0x324 },  // SPECIES_TRAPINCH
    { OBJ_EVENT_GFX_PKMN_VIBRAVA, 0x325 },  // SPECIES_VIBRAVA
    { OBJ_EVENT_GFX_PKMN_FLYGON, 0x326 },  // SPECIES_FLYGON
    { OBJ_EVENT_GFX_PKMN_CACNEA, 0x327 },  // SPECIES_CACNEA
    { OBJ_EVENT_GFX_PKMN_CACTURNE, 0x328 },  // SPECIES_CACTURNE
    { OBJ_EVENT_GFX_PKMN_SWABLU, 0x329 },  // SPECIES_SWABLU
    { OBJ_EVENT_GFX_PKMN_ALTARIA, 0x32a },  // SPECIES_ALTARIA
    { OBJ_EVENT_GFX_PKMN_ZANGOOSE, 0x32b },  // SPECIES_ZANGOOSE
    { OBJ_EVENT_GFX_PKMN_SEVIPER, 0x32c },  // SPECIES_SEVIPER
    { OBJ_EVENT_GFX_PKMN_LUNATONE, 0x32d },  // SPECIES_LUNATONE
    { OBJ_EVENT_GFX_PKMN_SOLROCK, 0x32e },  // SPECIES_SOLROCK
    { OBJ_EVENT_GFX_PKMN_BARBOACH, 0x32f },  // SPECIES_BARBOACH
    { OBJ_EVENT_GFX_PKMN_WHISCASH, 0x330 },  // SPECIES_WHISCASH
    { OBJ_EVENT_GFX_PKMN_CORPHISH, 0x331 },  // SPECIES_CORPHISH
    { OBJ_EVENT_GFX_PKMN_CRAWDAUNT, 0x332 },  // SPECIES_CRAWDAUNT
    { OBJ_EVENT_GFX_PKMN_BALTOY, 0x333 },  // SPECIES_BALTOY
    { OBJ_EVENT_GFX_PKMN_CLAYDOL, 0x334 },  // SPECIES_CLAYDOL
    { OBJ_EVENT_GFX_PKMN_LILEEP, 0x335 },  // SPECIES_LILEEP
    { OBJ_EVENT_GFX_PKMN_CRADILY, 0x336 },  // SPECIES_CRADILY
    { OBJ_EVENT_GFX_PKMN_ANORITH, 0x337 },  // SPECIES_ANORITH
    { OBJ_EVENT_GFX_PKMN_ARMALDO, 0x338 },  // SPECIES_ARMALDO
    { OBJ_EVENT_GFX_PKMN_FEEBAS, 0x339 },  // SPECIES_FEEBAS
    { OBJ_EVENT_GFX_PKMN_MILOTIC, 0x33a },  // SPECIES_MILOTIC
    { OBJ_EVENT_GFX_PKMN_CASTFORM, 0x33b },  // SPECIES_CASTFORM
    { OBJ_EVENT_GFX_PKMN_KECLEON, 0x33c },  // SPECIES_KECLEON
    { OBJ_EVENT_GFX_PKMN_SHUPPET, 0x33d },  // SPECIES_SHUPPET
    { OBJ_EVENT_GFX_PKMN_BANETTE, 0x33e },  // SPECIES_BANETTE
    { OBJ_EVENT_GFX_PKMN_DUSKULL, 0x33f },  // SPECIES_DUSKULL
    { OBJ_EVENT_GFX_PKMN_DUSCLOPS, 0x340 },  // SPECIES_DUSCLOPS
    { OBJ_EVENT_GFX_PKMN_TROPIUS, 0x341 },  // SPECIES_TROPIUS
    { OBJ_EVENT_GFX_PKMN_CHIMECHO, 0x342 },  // SPECIES_CHIMECHO
    { OBJ_EVENT_GFX_PKMN_ABSOL, 0x343 },  // SPECIES_ABSOL
    { OBJ_EVENT_GFX_PKMN_WYNAUT, 0x344 },  // SPECIES_WYNAUT
    { OBJ_EVENT_GFX_PKMN_SNORUNT, 0x345 },  // SPECIES_SNORUNT
    { OBJ_EVENT_GFX_PKMN_GLALIE, 0x346 },  // SPECIES_GLALIE
    { OBJ_EVENT_GFX_PKMN_SPHEAL, 0x347 },  // SPECIES_SPHEAL
    { OBJ_EVENT_GFX_PKMN_SEALEO, 0x348 },  // SPECIES_SEALEO
    { OBJ_EVENT_GFX_PKMN_WALREIN, 0x349 },  // SPECIES_WALREIN
    { OBJ_EVENT_GFX_PKMN_CLAMPERL, 0x34a },  // SPECIES_CLAMPERL
    { OBJ_EVENT_GFX_PKMN_HUNTAIL, 0x34b },  // SPECIES_HUNTAIL
    { OBJ_EVENT_GFX_PKMN_GOREBYSS, 0x34c },  // SPECIES_GOREBYSS
    { OBJ_EVENT_GFX_PKMN_RELICANTH, 0x34d },  // SPECIES_RELICANTH
    { OBJ_EVENT_GFX_PKMN_LUVDISC, 0x34e },  // SPECIES_LUVDISC
    { OBJ_EVENT_GFX_PKMN_BAGON, 0x34f },  // SPECIES_BAGON
    { OBJ_EVENT_GFX_PKMN_SHELGON, 0x350 },  // SPECIES_SHELGON
    { OBJ_EVENT_GFX_PKMN_SALAMENCE, 0x351 },  // SPECIES_SALAMENCE
    { OBJ_EVENT_GFX_PKMN_BELDUM, 0x352 },  // SPECIES_BELDUM
    { OBJ_EVENT_GFX_PKMN_METANG, 0x353 },  // SPECIES_METANG
    { OBJ_EVENT_GFX_PKMN_METAGROSS, 0x354 },  // SPECIES_METAGROSS
    { OBJ_EVENT_GFX_PKMN_REGIROCK, 0x355 },  // SPECIES_REGIROCK
    { OBJ_EVENT_GFX_PKMN_REGICE, 0x356 },  // SPECIES_REGICE
    { OBJ_EVENT_GFX_PKMN_REGISTEEL, 0x357 },  // SPECIES_REGISTEEL
    { OBJ_EVENT_GFX_PKMN_LATIAS, 0x358 },  // SPECIES_LATIAS
    { OBJ_EVENT_GFX_PKMN_LATIOS, 0x359 },  // SPECIES_LATIOS
    { OBJ_EVENT_GFX_PKMN_KYOGRE, 0x35a },  // SPECIES_KYOGRE
    { OBJ_EVENT_GFX_PKMN_GROUDON, 0x35b },  // SPECIES_GROUDON
    { OBJ_EVENT_GFX_PKMN_RAYQUAZA, 0x35c },  // SPECIES_RAYQUAZA
    { OBJ_EVENT_GFX_PKMN_JIRACHI, 0x35d },  // SPECIES_JIRACHI
    { OBJ_EVENT_GFX_PKMN_DEOXYS, 0x35e },  // SPECIES_DEOXYS
    { OBJ_EVENT_GFX_PKMN_TURTWIG, 0x35f },  // SPECIES_TURTWIG
    { OBJ_EVENT_GFX_PKMN_GROTLE, 0x360 },  // SPECIES_GROTLE
    { OBJ_EVENT_GFX_PKMN_TORTERRA, 0x361 },  // SPECIES_TORTERRA
    { OBJ_EVENT_GFX_PKMN_CHIMCHAR, 0x362 },  // SPECIES_CHIMCHAR
    { OBJ_EVENT_GFX_PKMN_MONFERNO, 0x363 },  // SPECIES_MONFERNO
    { OBJ_EVENT_GFX_PKMN_INFERNAPE, 0x364 },  // SPECIES_INFERNAPE
    { OBJ_EVENT_GFX_PKMN_PIPLUP, 0x365 },  // SPECIES_PIPLUP
    { OBJ_EVENT_GFX_PKMN_PRINPLUP, 0x366 },  // SPECIES_PRINPLUP
    { OBJ_EVENT_GFX_PKMN_EMPOLEON, 0x367 },  // SPECIES_EMPOLEON
    { OBJ_EVENT_GFX_PKMN_STARLY, 0x368 },  // SPECIES_STARLY
    { OBJ_EVENT_GFX_PKMN_STARAVIA, 0x369 },  // SPECIES_STARAVIA
    { OBJ_EVENT_GFX_PKMN_STARAPTOR, 0x36a },  // SPECIES_STARAPTOR
    { OBJ_EVENT_GFX_PKMN_BIDOOF, 0x36b },  // SPECIES_BIDOOF
    { OBJ_EVENT_GFX_PKMN_BIBAREL, 0x36c },  // SPECIES_BIBAREL
    { OBJ_EVENT_GFX_PKMN_KRICKETOT, 0x36d },  // SPECIES_KRICKETOT
    { OBJ_EVENT_GFX_PKMN_KRICKETUNE, 0x36e },  // SPECIES_KRICKETUNE
    { OBJ_EVENT_GFX_PKMN_SHINX, 0x36f },  // SPECIES_SHINX
    { OBJ_EVENT_GFX_PKMN_LUXIO, 0x370 },  // SPECIES_LUXIO
    { OBJ_EVENT_GFX_PKMN_LUXRAY, 0x371 },  // SPECIES_LUXRAY
    { OBJ_EVENT_GFX_PKMN_BUDEW, 0x372 },  // SPECIES_BUDEW
    { OBJ_EVENT_GFX_PKMN_ROSERADE, 0x373 },  // SPECIES_ROSERADE
    { OBJ_EVENT_GFX_PKMN_CRANIDOS, 0x374 },  // SPECIES_CRANIDOS
    { OBJ_EVENT_GFX_PKMN_RAMPARDOS, 0x375 },  // SPECIES_RAMPARDOS
    { OBJ_EVENT_GFX_PKMN_SHIELDON, 0x376 },  // SPECIES_SHIELDON
    { OBJ_EVENT_GFX_PKMN_BASTIODON, 0x377 },  // SPECIES_BASTIODON
    { OBJ_EVENT_GFX_PKMN_BURMY, 0x378 },  // SPECIES_BURMY
    { OBJ_EVENT_GFX_PKMN_WORMADAM, 0x379 },  // SPECIES_WORMADAM
    { OBJ_EVENT_GFX_PKMN_MOTHIM, 0x37a },  // SPECIES_MOTHIM
    { OBJ_EVENT_GFX_PKMN_COMBEE, 0x37b },  // SPECIES_COMBEE
    { OBJ_EVENT_GFX_PKMN_COMBEE_F, 0x37c },  // female
    { OBJ_EVENT_GFX_PKMN_VESPIQUEN, 0x37d },  // SPECIES_VESPIQUEN
    { OBJ_EVENT_GFX_PKMN_PACHIRISU, 0x37e },  // SPECIES_PACHIRISU
    { OBJ_EVENT_GFX_PKMN_BUIZEL, 0x37f },  // SPECIES_BUIZEL
    { OBJ_EVENT_GFX_PKMN_FLOATZEL, 0x380 },  // SPECIES_FLOATZEL
    { OBJ_EVENT_GFX_PKMN_CHERUBI, 0x381 },  // SPECIES_CHERUBI
    { OBJ_EVENT_GFX_PKMN_CHERRIM, 0x382 },  // SPECIES_CHERRIM
    { OBJ_EVENT_GFX_PKMN_SHELLOS, 0x383 },  // SPECIES_SHELLOS
    { OBJ_EVENT_GFX_PKMN_GASTRODON, 0x384 },  // SPECIES_GASTRODON
    { OBJ_EVENT_GFX_PKMN_AMBIPOM, 0x385 },  // SPECIES_AMBIPOM
    { OBJ_EVENT_GFX_PKMN_DRIFLOON, 0x386 },  // SPECIES_DRIFLOON
    { OBJ_EVENT_GFX_PKMN_DRIFBLIM, 0x387 },  // SPECIES_DRIFBLIM
    { OBJ_EVENT_GFX_PKMN_BUNEARY, 0x388 },  // SPECIES_BUNEARY
    { OBJ_EVENT_GFX_PKMN_LOPUNNY, 0x389 },  // SPECIES_LOPUNNY
    { OBJ_EVENT_GFX_PKMN_MISMAGIUS, 0x38a },  // SPECIES_MISMAGIUS
    { OBJ_EVENT_GFX_PKMN_HONCHKROW, 0x38b },  // SPECIES_HONCHKROW
    { OBJ_EVENT_GFX_PKMN_GLAMEOW, 0x38c },  // SPECIES_GLAMEOW
    { OBJ_EVENT_GFX_PKMN_PURUGLY, 0x38d },  // SPECIES_PURUGLY
    { OBJ_EVENT_GFX_PKMN_CHINGLING, 0x38e },  // SPECIES_CHINGLING
    { OBJ_EVENT_GFX_PKMN_STUNKY, 0x38f },  // SPECIES_STUNKY
    { OBJ_EVENT_GFX_PKMN_SKUNTANK, 0x390 },  // SPECIES_SKUNTANK
    { OBJ_EVENT_GFX_PKMN_BRONZOR, 0x391 },  // SPECIES_BRONZOR
    { OBJ_EVENT_GFX_PKMN_BRONZONG, 0x392 },  // SPECIES_BRONZONG
    { OBJ_EVENT_GFX_PKMN_BONSLY, 0x393 },  // SPECIES_BONSLY
    { OBJ_EVENT_GFX_PKMN_MIMEJR, 0x394 },  // SPECIES_MIMEJR
    { OBJ_EVENT_GFX_PKMN_HAPPINY, 0x395 },  // SPECIES_HAPPINY
    { OBJ_EVENT_GFX_PKMN_CHATOT, 0x396 },  // SPECIES_CHATOT
    { OBJ_EVENT_GFX_PKMN_SPIRITOMB, 0x397 },  // SPECIES_SPIRITOMB
    { OBJ_EVENT_GFX_PKMN_GIBLE, 0x398 },  // SPECIES_GIBLE
    { OBJ_EVENT_GFX_PKMN_GABITE, 0x399 },  // SPECIES_GABITE
    { OBJ_EVENT_GFX_PKMN_GARCHOMP, 0x39a },  // SPECIES_GARCHOMP
    { OBJ_EVENT_GFX_PKMN_MUNCHLAX, 0x39b },  // SPECIES_MUNCHLAX
    { OBJ_EVENT_GFX_PKMN_RIOLU, 0x39c },  // SPECIES_RIOLU
    { OBJ_EVENT_GFX_PKMN_LUCARIO, 0x39d },  // SPECIES_LUCARIO
    { OBJ_EVENT_GFX_PKMN_HIPPOPOTAS, 0x39e },  // SPECIES_HIPPOPOTAS
    { OBJ_EVENT_GFX_PKMN_HIPPOPOTAS_F, 0x39f },  // female
    { OBJ_EVENT_GFX_PKMN_HIPPOWDON, 0x3a0 },  // SPECIES_HIPPOWDON
    { OBJ_EVENT_GFX_PKMN_HIPPOWDON_F, 0x3a1 },  // female
    { OBJ_EVENT_GFX_PKMN_SKORUPI, 0x3a2 },  // SPECIES_SKORUPI
    { OBJ_EVENT_GFX_PKMN_DRAPION, 0x3a3 },  // SPECIES_DRAPION
    { OBJ_EVENT_GFX_PKMN_CROAGUNK, 0x3a4 },  // SPECIES_CROAGUNK
    { OBJ_EVENT_GFX_PKMN_TOXICROAK, 0x3a5 },  // SPECIES_TOXICROAK
    { OBJ_EVENT_GFX_PKMN_CARNIVINE, 0x3a6 },  // SPECIES_CARNIVINE
    { OBJ_EVENT_GFX_PKMN_FINNEON, 0x3a7 },  // SPECIES_FINNEON
    { OBJ_EVENT_GFX_PKMN_LUMINEON, 0x3a8 },  // SPECIES_LUMINEON
    { OBJ_EVENT_GFX_PKMN_MANTYKE, 0x3a9 },  // SPECIES_MANTYKE
    { OBJ_EVENT_GFX_PKMN_SNOVER, 0x3aa },  // SPECIES_SNOVER
    { OBJ_EVENT_GFX_PKMN_ABOMASNOW, 0x3ab },  // SPECIES_ABOMASNOW
    { OBJ_EVENT_GFX_PKMN_WEAVILE, 0x3ac },  // SPECIES_WEAVILE
    { OBJ_EVENT_GFX_PKMN_MAGNEZONE, 0x3ad },  // SPECIES_MAGNEZONE
    { OBJ_EVENT_GFX_PKMN_LICKILICKY, 0x3ae },  // SPECIES_LICKILICKY
    { OBJ_EVENT_GFX_PKMN_RHYPERIOR, 0x3af },  // SPECIES_RHYPERIOR
    { OBJ_EVENT_GFX_PKMN_TANGROWTH, 0x3b0 },  // SPECIES_TANGROWTH
    { OBJ_EVENT_GFX_PKMN_ELECTIVIRE, 0x3b1 },  // SPECIES_ELECTIVIRE
    { OBJ_EVENT_GFX_PKMN_MAGMORTAR, 0x3b2 },  // SPECIES_MAGMORTAR
    { OBJ_EVENT_GFX_PKMN_TOGEKISS, 0x3b3 },  // SPECIES_TOGEKISS
    { OBJ_EVENT_GFX_PKMN_LEAFEON, 0x3b4 },  // SPECIES_LEAFEON
    { OBJ_EVENT_GFX_PKMN_GLACEON, 0x3b5 },  // SPECIES_GLACEON
    { OBJ_EVENT_GFX_PKMN_GLISCOR, 0x3b6 },  // SPECIES_GLISCOR
    { OBJ_EVENT_GFX_PKMN_MAMOSWINE, 0x3b7 },  // SPECIES_MAMOSWINE
    { OBJ_EVENT_GFX_PKMN_PORYGON_Z, 0x3b8 },  // SPECIES_PORYGON_Z
    { OBJ_EVENT_GFX_PKMN_GALLADE, 0x3b9 },  // SPECIES_GALLADE
    { OBJ_EVENT_GFX_PKMN_PROBOPASS, 0x3ba },  // SPECIES_PROBOPASS
    { OBJ_EVENT_GFX_PKMN_DUSKNOIR, 0x3bb },  // SPECIES_DUSKNOIR
    { OBJ_EVENT_GFX_PKMN_FROSLASS, 0x3bc },  // SPECIES_FROSLASS
    { OBJ_EVENT_GFX_PKMN_ROTOM, 0x3bd },  // SPECIES_ROTOM
    { OBJ_EVENT_GFX_PKMN_UXIE, 0x3be },  // SPECIES_UXIE
    { OBJ_EVENT_GFX_PKMN_MESPRIT, 0x3bf },  // SPECIES_MESPRIT
    { OBJ_EVENT_GFX_PKMN_AZELF, 0x3c0 },  // SPECIES_AZELF
    { OBJ_EVENT_GFX_PKMN_DIALGA, 0x3c1 },  // SPECIES_DIALGA
    { OBJ_EVENT_GFX_PKMN_PALKIA, 0x3c2 },  // SPECIES_PALKIA
    { OBJ_EVENT_GFX_PKMN_HEATRAN, 0x3c3 },  // SPECIES_HEATRAN
    { OBJ_EVENT_GFX_PKMN_REGIGIGAS, 0x3c4 },  // SPECIES_REGIGIGAS
    { OBJ_EVENT_GFX_PKMN_GIRATINA, 0x3c5 },  // SPECIES_GIRATINA
    { OBJ_EVENT_GFX_PKMN_CRESSELIA, 0x3c6 },  // SPECIES_CRESSELIA
    { OBJ_EVENT_GFX_PKMN_PHIONE, 0x3c7 },  // SPECIES_PHIONE
    { OBJ_EVENT_GFX_PKMN_MANAPHY, 0x3c8 },  // SPECIES_MANAPHY
    { OBJ_EVENT_GFX_PKMN_DARKRAI, 0x3c9 },  // SPECIES_DARKRAI
    { OBJ_EVENT_GFX_PKMN_SHAYMIN, 0x3ca },  // SPECIES_SHAYMIN
    { OBJ_EVENT_GFX_PKMN_ARCEUS, 0x3cb },  // SPECIES_ARCEUS
    { OBJ_EVENT_GFX_PKMN_GIRATINA_O, 0x3cc },  // SPECIES_GIRATINA origin form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FIGHTING, 0x3cd },  // SPECIES_ARCEUS fighting type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FLYING, 0x3ce },  // SPECIES_ARCEUS flying type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_POISON, 0x3cf },  // SPECIES_ARCEUS poison type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GROUND, 0x3d0 },  // SPECIES_ARCEUS ground type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ROCK, 0x3d1 },  // SPECIES_ARCEUS rock type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_BUG, 0x3d2 },  // SPECIES_ARCEUS bug type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GHOST, 0x3d3 },  // SPECIES_ARCEUS ghost type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_STEEL, 0x3d4 },  // SPECIES_ARCEUS steel type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FAIRY, 0x3d5 },  // SPECIES_ARCEUS fairy type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FIRE, 0x3d6 },  // SPECIES_ARCEUS fire type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_WATER, 0x3d7 },  // SPECIES_ARCEUS water type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GRASS, 0x3d8 },  // SPECIES_ARCEUS grass type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ELECTRIC, 0x3d9 },  // SPECIES_ARCEUS electric type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_PSYCHIC, 0x3da },  // SPECIES_ARCEUS psychic type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ICE, 0x3db },  // SPECIES_ARCEUS ice type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_DRAGON, 0x3dc },  // SPECIES_ARCEUS dragon type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_DARK, 0x3dd },  // SPECIES_ARCEUS dark type
    { OBJ_EVENT_GFX_PKMN_DEOXYS_ATTACK, 0x3df },  // SPECIES_DEOXYS attack form
    { OBJ_EVENT_GFX_PKMN_DEOXYS_DEFENSE, 0x3e0 },  // SPECIES_DEOXYS defense form
    { OBJ_EVENT_GFX_PKMN_DEOXYS_SPEED, 0x3e1 },  // SPECIES_DEOXYS speed form
    { OBJ_EVENT_GFX_PKMN_BURMY_SANDY, 0x3e2 },  // SPECIES_BURMY sandy cloak
    { OBJ_EVENT_GFX_PKMN_BURMY_TRASH, 0x3e3 },  // SPECIES_BURMY trash cloak
    { OBJ_EVENT_GFX_PKMN_WORMADAM_SANDY, 0x3e4 },  // SPECIES_WORMADAM sandy cloak
    { OBJ_EVENT_GFX_PKMN_WORMADAM_TRASH, 0x3e5 },  // SPECIES_WORMADAM trash cloak
    { OBJ_EVENT_GFX_PKMN_SHELLOS_EAST, 0x3e6 },  // SPECIES_SHELLOS east sea
    { OBJ_EVENT_GFX_PKMN_GASTRODON_EAST, 0x3e7 },  // SPECIES_GASTRODON east sea
    { OBJ_EVENT_GFX_PKMN_ROTOM_HEAT, 0x3e8 },  // SPECIES_ROTOM heat
    { OBJ_EVENT_GFX_PKMN_ROTOM_WASH, 0x3e9 },  // SPECIES_ROTOM wash
    { OBJ_EVENT_GFX_PKMN_ROTOM_FROST, 0x3ea },  // SPECIES_ROTOM frost
    { OBJ_EVENT_GFX_PKMN_ROTOM_FAN, 0x3eb },  // SPECIES_ROTOM fan
    { OBJ_EVENT_GFX_PKMN_ROTOM_MOW, 0x3ec },  // SPECIES_ROTOM mow
    { OBJ_EVENT_GFX_PKMN_SHAYMIN_SKY, 0x3ed },  // SPECIES_SHAYMIN sky form
    { OBJ_EVENT_GFX_PKMN_BULBASAUR_SHINY, 0x3ee },  // shiny SPECIES_BULBASAUR
    { OBJ_EVENT_GFX_PKMN_IVYSAUR_SHINY, 0x3ef },  // shiny SPECIES_IVYSAUR
    { OBJ_EVENT_GFX_PKMN_VENUSAUR_SHINY, 0x3f0 },  // shiny SPECIES_VENUSAUR
    { OBJ_EVENT_GFX_PKMN_VENUSAUR_F_SHINY, 0x3f1 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_CHARMANDER_SHINY, 0x3f2 },  // shiny SPECIES_CHARMANDER
    { OBJ_EVENT_GFX_PKMN_CHARMELEON_SHINY, 0x3f3 },  // shiny SPECIES_CHARMELEON
    { OBJ_EVENT_GFX_PKMN_CHARIZARD_SHINY, 0x3f4 },  // shiny SPECIES_CHARIZARD
    { OBJ_EVENT_GFX_PKMN_SQUIRTLE_SHINY, 0x3f5 },  // shiny SPECIES_SQUIRTLE
    { OBJ_EVENT_GFX_PKMN_WARTORTLE_SHINY, 0x3f6 },  // shiny SPECIES_WARTORTLE
    { OBJ_EVENT_GFX_PKMN_BLASTOISE_SHINY, 0x3f7 },  // shiny SPECIES_BLASTOISE
    { OBJ_EVENT_GFX_PKMN_CATERPIE_SHINY, 0x3f8 },  // shiny SPECIES_CATERPIE
    { OBJ_EVENT_GFX_PKMN_METAPOD_SHINY, 0x3f9 },  // shiny SPECIES_METAPOD
    { OBJ_EVENT_GFX_PKMN_BUTTERFREE_SHINY, 0x3fa },  // shiny SPECIES_BUTTERFREE
    { OBJ_EVENT_GFX_PKMN_WEEDLE_SHINY, 0x3fb },  // shiny SPECIES_WEEDLE
    { OBJ_EVENT_GFX_PKMN_KAKUNA_SHINY, 0x3fc },  // shiny SPECIES_KAKUNA
    { OBJ_EVENT_GFX_PKMN_BEEDRILL_SHINY, 0x3fd },  // shiny SPECIES_BEEDRILL
    { OBJ_EVENT_GFX_PKMN_PIDGEY_SHINY, 0x3fe },  // shiny SPECIES_PIDGEY
    { OBJ_EVENT_GFX_PKMN_PIDGEOTTO_SHINY, 0x3ff },  // shiny SPECIES_PIDGEOTTO
    { OBJ_EVENT_GFX_PKMN_PIDGEOT_SHINY, 0x400 },  // shiny SPECIES_PIDGEOT
    { OBJ_EVENT_GFX_PKMN_RATTATA_SHINY, 0x401 },  // shiny SPECIES_RATTATA
    { OBJ_EVENT_GFX_PKMN_RATICATE_SHINY, 0x402 },  // shiny SPECIES_RATICATE
    { OBJ_EVENT_GFX_PKMN_SPEAROW_SHINY, 0x403 },  // shiny SPECIES_SPEAROW
    { OBJ_EVENT_GFX_PKMN_FEAROW_SHINY, 0x404 },  // shiny SPECIES_FEAROW
    { OBJ_EVENT_GFX_PKMN_EKANS_SHINY, 0x405 },  // shiny SPECIES_EKANS
    { OBJ_EVENT_GFX_PKMN_ARBOK_SHINY, 0x406 },  // shiny SPECIES_ARBOK
    { OBJ_EVENT_GFX_PKMN_PIKACHU_SHINY, 0x407 },  // shiny SPECIES_PIKACHU
    { OBJ_EVENT_GFX_PKMN_PIKACHU_F_SHINY, 0x408 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_RAICHU_SHINY, 0x409 },  // shiny SPECIES_RAICHU
    { OBJ_EVENT_GFX_PKMN_SANDSHREW_SHINY, 0x40a },  // shiny SPECIES_SANDSHREW
    { OBJ_EVENT_GFX_PKMN_SANDSLASH_SHINY, 0x40b },  // shiny SPECIES_SANDSLASH
    { OBJ_EVENT_GFX_PKMN_NIDORAN_F_SHINY, 0x40c },  // shiny SPECIES_NIDORAN_F
    { OBJ_EVENT_GFX_PKMN_NIDORINA_SHINY, 0x40d },  // shiny SPECIES_NIDORINA
    { OBJ_EVENT_GFX_PKMN_NIDOQUEEN_SHINY, 0x40e },  // shiny SPECIES_NIDOQUEEN
    { OBJ_EVENT_GFX_PKMN_NIDORAN_M_SHINY, 0x40f },  // shiny SPECIES_NIDORAN_M
    { OBJ_EVENT_GFX_PKMN_NIDORINO_SHINY, 0x410 },  // shiny SPECIES_NIDORINO
    { OBJ_EVENT_GFX_PKMN_NIDOKING_SHINY, 0x411 },  // shiny SPECIES_NIDOKING
    { OBJ_EVENT_GFX_PKMN_CLEFAIRY_SHINY, 0x412 },  // shiny SPECIES_CLEFAIRY
    { OBJ_EVENT_GFX_PKMN_CLEFABLE_SHINY, 0x413 },  // shiny SPECIES_CLEFABLE
    { OBJ_EVENT_GFX_PKMN_VULPIX_SHINY, 0x414 },  // shiny SPECIES_VULPIX
    { OBJ_EVENT_GFX_PKMN_NINETALES_SHINY, 0x415 },  // shiny SPECIES_NINETALES
    { OBJ_EVENT_GFX_PKMN_JIGGLYPUFF_SHINY, 0x416 },  // shiny SPECIES_JIGGLYPUFF
    { OBJ_EVENT_GFX_PKMN_WIGGLYTUFF_SHINY, 0x417 },  // shiny SPECIES_WIGGLYTUFF
    { OBJ_EVENT_GFX_PKMN_ZUBAT_SHINY, 0x418 },  // shiny SPECIES_ZUBAT
    { OBJ_EVENT_GFX_PKMN_GOLBAT_SHINY, 0x419 },  // shiny SPECIES_GOLBAT
    { OBJ_EVENT_GFX_PKMN_ODDISH_SHINY, 0x41a },  // shiny SPECIES_ODDISH
    { OBJ_EVENT_GFX_PKMN_GLOOM_SHINY, 0x41b },  // shiny SPECIES_GLOOM
    { OBJ_EVENT_GFX_PKMN_VILEPLUME_SHINY, 0x41c },  // shiny SPECIES_VILEPLUME
    { OBJ_EVENT_GFX_PKMN_PARAS_SHINY, 0x41d },  // shiny SPECIES_PARAS
    { OBJ_EVENT_GFX_PKMN_PARASECT_SHINY, 0x41e },  // shiny SPECIES_PARASECT
    { OBJ_EVENT_GFX_PKMN_VENONAT_SHINY, 0x41f },  // shiny SPECIES_VENONAT
    { OBJ_EVENT_GFX_PKMN_VENOMOTH_SHINY, 0x420 },  // shiny SPECIES_VENOMOTH
    { OBJ_EVENT_GFX_PKMN_DIGLETT_SHINY, 0x421 },  // shiny SPECIES_DIGLETT
    { OBJ_EVENT_GFX_PKMN_DUGTRIO_SHINY, 0x422 },  // shiny SPECIES_DUGTRIO
    { OBJ_EVENT_GFX_PKMN_MEOWTH_SHINY, 0x423 },  // shiny SPECIES_MEOWTH
    { OBJ_EVENT_GFX_PKMN_PERSIAN_SHINY, 0x424 },  // shiny SPECIES_PERSIAN
    { OBJ_EVENT_GFX_PKMN_PSYDUCK_SHINY, 0x425 },  // shiny SPECIES_PSYDUCK
    { OBJ_EVENT_GFX_PKMN_GOLDUCK_SHINY, 0x426 },  // shiny SPECIES_GOLDUCK
    { OBJ_EVENT_GFX_PKMN_MANKEY_SHINY, 0x427 },  // shiny SPECIES_MANKEY
    { OBJ_EVENT_GFX_PKMN_PRIMEAPE_SHINY, 0x428 },  // shiny SPECIES_PRIMEAPE
    { OBJ_EVENT_GFX_PKMN_GROWLITHE_SHINY, 0x429 },  // shiny SPECIES_GROWLITHE
    { OBJ_EVENT_GFX_PKMN_ARCANINE_SHINY, 0x42a },  // shiny SPECIES_ARCANINE
    { OBJ_EVENT_GFX_PKMN_POLIWAG_SHINY, 0x42b },  // shiny SPECIES_POLIWAG
    { OBJ_EVENT_GFX_PKMN_POLIWHIRL_SHINY, 0x42c },  // shiny SPECIES_POLIWHIRL
    { OBJ_EVENT_GFX_PKMN_POLIWRATH_SHINY, 0x42d },  // shiny SPECIES_POLIWRATH
    { OBJ_EVENT_GFX_PKMN_ABRA_SHINY, 0x42e },  // shiny SPECIES_ABRA
    { OBJ_EVENT_GFX_PKMN_KADABRA_SHINY, 0x42f },  // shiny SPECIES_KADABRA
    { OBJ_EVENT_GFX_PKMN_ALAKAZAM_SHINY, 0x430 },  // shiny SPECIES_ALAKAZAM
    { OBJ_EVENT_GFX_PKMN_MACHOP_SHINY, 0x431 },  // shiny SPECIES_MACHOP
    { OBJ_EVENT_GFX_PKMN_MACHOKE_SHINY, 0x432 },  // shiny SPECIES_MACHOKE
    { OBJ_EVENT_GFX_PKMN_MACHAMP_SHINY, 0x433 },  // shiny SPECIES_MACHAMP
    { OBJ_EVENT_GFX_PKMN_BELLSPROUT_SHINY, 0x434 },  // shiny SPECIES_BELLSPROUT
    { OBJ_EVENT_GFX_PKMN_WEEPINBELL_SHINY, 0x435 },  // shiny SPECIES_WEEPINBELL
    { OBJ_EVENT_GFX_PKMN_VICTREEBEL_SHINY, 0x436 },  // shiny SPECIES_VICTREEBEL
    { OBJ_EVENT_GFX_PKMN_TENTACOOL_SHINY, 0x437 },  // shiny SPECIES_TENTACOOL
    { OBJ_EVENT_GFX_PKMN_TENTACRUEL_SHINY, 0x438 },  // shiny SPECIES_TENTACRUEL
    { OBJ_EVENT_GFX_PKMN_GEODUDE_SHINY, 0x439 },  // shiny SPECIES_GEODUDE
    { OBJ_EVENT_GFX_PKMN_GRAVELER_SHINY, 0x43a },  // shiny SPECIES_GRAVELER
    { OBJ_EVENT_GFX_PKMN_GOLEM_SHINY, 0x43b },  // shiny SPECIES_GOLEM
    { OBJ_EVENT_GFX_PKMN_PONYTA_SHINY, 0x43c },  // shiny SPECIES_PONYTA
    { OBJ_EVENT_GFX_PKMN_RAPIDASH_SHINY, 0x43d },  // shiny SPECIES_RAPIDASH
    { OBJ_EVENT_GFX_PKMN_SLOWPOKE_SHINY, 0x43e },  // shiny SPECIES_SLOWPOKE
    { OBJ_EVENT_GFX_PKMN_SLOWBRO_SHINY, 0x43f },  // shiny SPECIES_SLOWBRO
    { OBJ_EVENT_GFX_PKMN_MAGNEMITE_SHINY, 0x440 },  // shiny SPECIES_MAGNEMITE
    { OBJ_EVENT_GFX_PKMN_MAGNETON_SHINY, 0x441 },  // shiny SPECIES_MAGNETON
    { OBJ_EVENT_GFX_PKMN_FARFETCHD_SHINY, 0x442 },  // shiny SPECIES_FARFETCHD
    { OBJ_EVENT_GFX_PKMN_DODUO_SHINY, 0x443 },  // shiny SPECIES_DODUO
    { OBJ_EVENT_GFX_PKMN_DODRIO_SHINY, 0x444 },  // shiny SPECIES_DODRIO
    { OBJ_EVENT_GFX_PKMN_SEEL_SHINY, 0x445 },  // shiny SPECIES_SEEL
    { OBJ_EVENT_GFX_PKMN_DEWGONG_SHINY, 0x446 },  // shiny SPECIES_DEWGONG
    { OBJ_EVENT_GFX_PKMN_GRIMER_SHINY, 0x447 },  // shiny SPECIES_GRIMER
    { OBJ_EVENT_GFX_PKMN_MUK_SHINY, 0x448 },  // shiny SPECIES_MUK
    { OBJ_EVENT_GFX_PKMN_SHELLDER_SHINY, 0x449 },  // shiny SPECIES_SHELLDER
    { OBJ_EVENT_GFX_PKMN_CLOYSTER_SHINY, 0x44a },  // shiny SPECIES_CLOYSTER
    { OBJ_EVENT_GFX_PKMN_GASTLY_SHINY, 0x44b },  // shiny SPECIES_GASTLY
    { OBJ_EVENT_GFX_PKMN_HAUNTER_SHINY, 0x44c },  // shiny SPECIES_HAUNTER
    { OBJ_EVENT_GFX_PKMN_GENGAR_SHINY, 0x44d },  // shiny SPECIES_GENGAR
    { OBJ_EVENT_GFX_PKMN_ONIX_SHINY, 0x44e },  // shiny SPECIES_ONIX
    { OBJ_EVENT_GFX_PKMN_DROWZEE_SHINY, 0x44f },  // shiny SPECIES_DROWZEE
    { OBJ_EVENT_GFX_PKMN_HYPNO_SHINY, 0x450 },  // shiny SPECIES_HYPNO
    { OBJ_EVENT_GFX_PKMN_KRABBY_SHINY, 0x451 },  // shiny SPECIES_KRABBY
    { OBJ_EVENT_GFX_PKMN_KINGLER_SHINY, 0x452 },  // shiny SPECIES_KINGLER
    { OBJ_EVENT_GFX_PKMN_VOLTORB_SHINY, 0x453 },  // shiny SPECIES_VOLTORB
    { OBJ_EVENT_GFX_PKMN_ELECTRODE_SHINY, 0x454 },  // shiny SPECIES_ELECTRODE
    { OBJ_EVENT_GFX_PKMN_EXEGGCUTE_SHINY, 0x455 },  // shiny SPECIES_EXEGGCUTE
    { OBJ_EVENT_GFX_PKMN_EXEGGUTOR_SHINY, 0x456 },  // shiny SPECIES_EXEGGUTOR
    { OBJ_EVENT_GFX_PKMN_CUBONE_SHINY, 0x457 },  // shiny SPECIES_CUBONE
    { OBJ_EVENT_GFX_PKMN_MAROWAK_SHINY, 0x458 },  // shiny SPECIES_MAROWAK
    { OBJ_EVENT_GFX_PKMN_HITMONLEE_SHINY, 0x459 },  // shiny SPECIES_HITMONLEE
    { OBJ_EVENT_GFX_PKMN_HITMONCHAN_SHINY, 0x45a },  // shiny SPECIES_HITMONCHAN
    { OBJ_EVENT_GFX_PKMN_LICKITUNG_SHINY, 0x45b },  // shiny SPECIES_LICKITUNG
    { OBJ_EVENT_GFX_PKMN_KOFFING_SHINY, 0x45c },  // shiny SPECIES_KOFFING
    { OBJ_EVENT_GFX_PKMN_WEEZING_SHINY, 0x45d },  // shiny SPECIES_WEEZING
    { OBJ_EVENT_GFX_PKMN_RHYHORN_SHINY, 0x45e },  // shiny SPECIES_RHYHORN
    { OBJ_EVENT_GFX_PKMN_RHYDON_SHINY, 0x45f },  // shiny SPECIES_RHYDON
    { OBJ_EVENT_GFX_PKMN_CHANSEY_SHINY, 0x460 },  // shiny SPECIES_CHANSEY
    { OBJ_EVENT_GFX_PKMN_TANGELA_SHINY, 0x461 },  // shiny SPECIES_TANGELA
    { OBJ_EVENT_GFX_PKMN_KANGASKHAN_SHINY, 0x462 },  // shiny SPECIES_KANGASKHAN
    { OBJ_EVENT_GFX_PKMN_HORSEA_SHINY, 0x463 },  // shiny SPECIES_HORSEA
    { OBJ_EVENT_GFX_PKMN_SEADRA_SHINY, 0x464 },  // shiny SPECIES_SEADRA
    { OBJ_EVENT_GFX_PKMN_GOLDEEN_SHINY, 0x465 },  // shiny SPECIES_GOLDEEN
    { OBJ_EVENT_GFX_PKMN_SEAKING_SHINY, 0x466 },  // shiny SPECIES_SEAKING
    { OBJ_EVENT_GFX_PKMN_STARYU_SHINY, 0x467 },  // shiny SPECIES_STARYU
    { OBJ_EVENT_GFX_PKMN_STARMIE_SHINY, 0x468 },  // shiny SPECIES_STARMIE
    { OBJ_EVENT_GFX_PKMN_MR_MIME_SHINY, 0x469 },  // shiny SPECIES_MR_MIME
    { OBJ_EVENT_GFX_PKMN_SCYTHER_SHINY, 0x46a },  // shiny SPECIES_SCYTHER
    { OBJ_EVENT_GFX_PKMN_JYNX_SHINY, 0x46b },  // shiny SPECIES_JYNX
    { OBJ_EVENT_GFX_PKMN_ELECTABUZZ_SHINY, 0x46c },  // shiny SPECIES_ELECTABUZZ
    { OBJ_EVENT_GFX_PKMN_MAGMAR_SHINY, 0x46d },  // shiny SPECIES_MAGMAR
    { OBJ_EVENT_GFX_PKMN_PINSIR_SHINY, 0x46e },  // shiny SPECIES_PINSIR
    { OBJ_EVENT_GFX_PKMN_TAUROS_SHINY, 0x46f },  // shiny SPECIES_TAUROS
    { OBJ_EVENT_GFX_PKMN_MAGIKARP_SHINY, 0x470 },  // shiny SPECIES_MAGIKARP
    { OBJ_EVENT_GFX_PKMN_GYARADOS_SHINY, 0x471 },  // shiny SPECIES_GYARADOS
    { OBJ_EVENT_GFX_PKMN_LAPRAS_SHINY, 0x472 },  // shiny SPECIES_LAPRAS
    { OBJ_EVENT_GFX_PKMN_DITTO_SHINY, 0x473 },  // shiny SPECIES_DITTO
    { OBJ_EVENT_GFX_PKMN_EEVEE_SHINY, 0x474 },  // shiny SPECIES_EEVEE
    { OBJ_EVENT_GFX_PKMN_VAPOREON_SHINY, 0x475 },  // shiny SPECIES_VAPOREON
    { OBJ_EVENT_GFX_PKMN_JOLTEON_SHINY, 0x476 },  // shiny SPECIES_JOLTEON
    { OBJ_EVENT_GFX_PKMN_FLAREON_SHINY, 0x477 },  // shiny SPECIES_FLAREON
    { OBJ_EVENT_GFX_PKMN_PORYGON_SHINY, 0x478 },  // shiny SPECIES_PORYGON
    { OBJ_EVENT_GFX_PKMN_OMANYTE_SHINY, 0x479 },  // shiny SPECIES_OMANYTE
    { OBJ_EVENT_GFX_PKMN_OMASTAR_SHINY, 0x47a },  // shiny SPECIES_OMASTAR
    { OBJ_EVENT_GFX_PKMN_KABUTO_SHINY, 0x47b },  // shiny SPECIES_KABUTO
    { OBJ_EVENT_GFX_PKMN_KABUTOPS_SHINY, 0x47c },  // shiny SPECIES_KABUTOPS
    { OBJ_EVENT_GFX_PKMN_AERODACTYL_SHINY, 0x47d },  // shiny SPECIES_AERODACTYL
    { OBJ_EVENT_GFX_PKMN_SNORLAX_SHINY, 0x47e },  // shiny SPECIES_SNORLAX
    { OBJ_EVENT_GFX_PKMN_ARTICUNO_SHINY, 0x47f },  // shiny SPECIES_ARTICUNO
    { OBJ_EVENT_GFX_PKMN_ZAPDOS_SHINY, 0x480 },  // shiny SPECIES_ZAPDOS
    { OBJ_EVENT_GFX_PKMN_MOLTRES_SHINY, 0x481 },  // shiny SPECIES_MOLTRES
    { OBJ_EVENT_GFX_PKMN_DRATINI_SHINY, 0x482 },  // shiny SPECIES_DRATINI
    { OBJ_EVENT_GFX_PKMN_DRAGONAIR_SHINY, 0x483 },  // shiny SPECIES_DRAGONAIR
    { OBJ_EVENT_GFX_PKMN_DRAGONITE_SHINY, 0x484 },  // shiny SPECIES_DRAGONITE
    { OBJ_EVENT_GFX_PKMN_MEWTWO_SHINY, 0x485 },  // shiny SPECIES_MEWTWO
    { OBJ_EVENT_GFX_PKMN_MEW_SHINY, 0x486 },  // shiny SPECIES_MEW
    { OBJ_EVENT_GFX_PKMN_CHIKORITA_SHINY, 0x487 },  // shiny SPECIES_CHIKORITA
    { OBJ_EVENT_GFX_PKMN_BAYLEEF_SHINY, 0x488 },  // shiny SPECIES_BAYLEEF
    { OBJ_EVENT_GFX_PKMN_BAYLEEF_F_SHINY, 0x489 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_CYNDAQUIL_SHINY, 0x48a },  // shiny SPECIES_CYNDAQUIL
    { OBJ_EVENT_GFX_PKMN_QUILAVA_SHINY, 0x48b },  // shiny SPECIES_QUILAVA
    { OBJ_EVENT_GFX_PKMN_TYPHLOSION_SHINY, 0x48c },  // shiny SPECIES_TYPHLOSION
    { OBJ_EVENT_GFX_PKMN_TOTODILE_SHINY, 0x48d },  // shiny SPECIES_TOTODILE
    { OBJ_EVENT_GFX_PKMN_CROCONAW_SHINY, 0x48e },  // shiny SPECIES_CROCONAW
    { OBJ_EVENT_GFX_PKMN_FERALIGATR_SHINY, 0x48f },  // shiny SPECIES_FERALIGATR
    { OBJ_EVENT_GFX_PKMN_SENTRET_SHINY, 0x490 },  // shiny SPECIES_SENTRET
    { OBJ_EVENT_GFX_PKMN_FURRET_SHINY, 0x491 },  // shiny SPECIES_FURRET
    { OBJ_EVENT_GFX_PKMN_HOOTHOOT_SHINY, 0x492 },  // shiny SPECIES_HOOTHOOT
    { OBJ_EVENT_GFX_PKMN_NOCTOWL_SHINY, 0x493 },  // shiny SPECIES_NOCTOWL
    { OBJ_EVENT_GFX_PKMN_LEDYBA_SHINY, 0x494 },  // shiny SPECIES_LEDYBA
    { OBJ_EVENT_GFX_PKMN_LEDIAN_SHINY, 0x495 },  // shiny SPECIES_LEDIAN
    { OBJ_EVENT_GFX_PKMN_SPINARAK_SHINY, 0x496 },  // shiny SPECIES_SPINARAK
    { OBJ_EVENT_GFX_PKMN_ARIADOS_SHINY, 0x497 },  // shiny SPECIES_ARIADOS
    { OBJ_EVENT_GFX_PKMN_CROBAT_SHINY, 0x498 },  // shiny SPECIES_CROBAT
    { OBJ_EVENT_GFX_PKMN_CHINCHOU_SHINY, 0x499 },  // shiny SPECIES_CHINCHOU
    { OBJ_EVENT_GFX_PKMN_LANTURN_SHINY, 0x49a },  // shiny SPECIES_LANTURN
    { OBJ_EVENT_GFX_PKMN_PICHU_SHINY, 0x49b },  // shiny SPECIES_PICHU
    { OBJ_EVENT_GFX_PKMN_CLEFFA_SHINY, 0x49c },  // shiny SPECIES_CLEFFA
    { OBJ_EVENT_GFX_PKMN_IGGLYBUFF_SHINY, 0x49d },  // shiny SPECIES_IGGLYBUFF
    { OBJ_EVENT_GFX_PKMN_TOGEPI_SHINY, 0x49e },  // shiny SPECIES_TOGEPI
    { OBJ_EVENT_GFX_PKMN_TOGETIC_SHINY, 0x49f },  // shiny SPECIES_TOGETIC
    { OBJ_EVENT_GFX_PKMN_NATU_SHINY, 0x4a0 },  // shiny SPECIES_NATU
    { OBJ_EVENT_GFX_PKMN_XATU_SHINY, 0x4a1 },  // shiny SPECIES_XATU
    { OBJ_EVENT_GFX_PKMN_MAREEP_SHINY, 0x4a2 },  // shiny SPECIES_MAREEP
    { OBJ_EVENT_GFX_PKMN_FLAAFFY_SHINY, 0x4a3 },  // shiny SPECIES_FLAAFFY
    { OBJ_EVENT_GFX_PKMN_AMPHAROS_SHINY, 0x4a4 },  // shiny SPECIES_AMPHAROS
    { OBJ_EVENT_GFX_PKMN_BELLOSSOM_SHINY, 0x4a5 },  // shiny SPECIES_BELLOSSOM
    { OBJ_EVENT_GFX_PKMN_MARILL_SHINY, 0x4a6 },  // shiny SPECIES_MARILL
    { OBJ_EVENT_GFX_PKMN_AZUMARILL_SHINY, 0x4a7 },  // shiny SPECIES_AZUMARILL
    { OBJ_EVENT_GFX_PKMN_SUDOWOODO_SHINY, 0x4a8 },  // shiny SPECIES_SUDOWOODO
    { OBJ_EVENT_GFX_PKMN_POLITOED_SHINY, 0x4a9 },  // shiny SPECIES_POLITOED
    { OBJ_EVENT_GFX_PKMN_HOPPIP_SHINY, 0x4aa },  // shiny SPECIES_HOPPIP
    { OBJ_EVENT_GFX_PKMN_SKIPLOOM_SHINY, 0x4ab },  // shiny SPECIES_SKIPLOOM
    { OBJ_EVENT_GFX_PKMN_JUMPLUFF_SHINY, 0x4ac },  // shiny SPECIES_JUMPLUFF
    { OBJ_EVENT_GFX_PKMN_AIPOM_SHINY, 0x4ad },  // shiny SPECIES_AIPOM
    { OBJ_EVENT_GFX_PKMN_SUNKERN_SHINY, 0x4ae },  // shiny SPECIES_SUNKERN
    { OBJ_EVENT_GFX_PKMN_SUNFLORA_SHINY, 0x4af },  // shiny SPECIES_SUNFLORA
    { OBJ_EVENT_GFX_PKMN_YANMA_SHINY, 0x4b0 },  // shiny SPECIES_YANMA
    { OBJ_EVENT_GFX_PKMN_WOOPER_SHINY, 0x4b1 },  // shiny SPECIES_WOOPER
    { OBJ_EVENT_GFX_PKMN_QUAGSIRE_SHINY, 0x4b2 },  // shiny SPECIES_QUAGSIRE
    { OBJ_EVENT_GFX_PKMN_ESPEON_SHINY, 0x4b3 },  // shiny SPECIES_ESPEON
    { OBJ_EVENT_GFX_PKMN_UMBREON_SHINY, 0x4b4 },  // shiny SPECIES_UMBREON
    { OBJ_EVENT_GFX_PKMN_MURKROW_SHINY, 0x4b5 },  // shiny SPECIES_MURKROW
    { OBJ_EVENT_GFX_PKMN_SLOWKING_SHINY, 0x4b6 },  // shiny SPECIES_SLOWKING
    { OBJ_EVENT_GFX_PKMN_MISDREAVUS_SHINY, 0x4b7 },  // shiny SPECIES_MISDREAVUS
    { OBJ_EVENT_GFX_PKMN_UNOWN_SHINY, 0x4b8 },  // shiny SPECIES_UNOWN
    { OBJ_EVENT_GFX_PKMN_WOBBUFFET_SHINY, 0x4b9 },  // shiny SPECIES_WOBBUFFET
    { OBJ_EVENT_GFX_PKMN_WOBBUFFET_F_SHINY, 0x4ba },  // shiny female
    { OBJ_EVENT_GFX_PKMN_GIRAFARIG_SHINY, 0x4bb },  // shiny SPECIES_GIRAFARIG
    { OBJ_EVENT_GFX_PKMN_PINECO_SHINY, 0x4bc },  // shiny SPECIES_PINECO
    { OBJ_EVENT_GFX_PKMN_FORRETRESS_SHINY, 0x4bd },  // shiny SPECIES_FORRETRESS
    { OBJ_EVENT_GFX_PKMN_DUNSPARCE_SHINY, 0x4be },  // shiny SPECIES_DUNSPARCE
    { OBJ_EVENT_GFX_PKMN_GLIGAR_SHINY, 0x4bf },  // shiny SPECIES_GLIGAR
    { OBJ_EVENT_GFX_PKMN_STEELIX_SHINY, 0x4c0 },  // shiny SPECIES_STEELIX
    { OBJ_EVENT_GFX_PKMN_STEELIX_F_SHINY, 0x4c1 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_SNUBBULL_SHINY, 0x4c2 },  // shiny SPECIES_SNUBBULL
    { OBJ_EVENT_GFX_PKMN_GRANBULL_SHINY, 0x4c3 },  // shiny SPECIES_GRANBULL
    { OBJ_EVENT_GFX_PKMN_QWILFISH_SHINY, 0x4c4 },  // shiny SPECIES_QWILFISH
    { OBJ_EVENT_GFX_PKMN_SCIZOR_SHINY, 0x4c5 },  // shiny SPECIES_SCIZOR
    { OBJ_EVENT_GFX_PKMN_SHUCKLE_SHINY, 0x4c6 },  // shiny SPECIES_SHUCKLE
    { OBJ_EVENT_GFX_PKMN_HERACROSS_SHINY, 0x4c7 },  // shiny SPECIES_HERACROSS
    { OBJ_EVENT_GFX_PKMN_HERACROSS_F_SHINY, 0x4c8 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_SNEASEL_SHINY, 0x4c9 },  // shiny SPECIES_SNEASEL
    { OBJ_EVENT_GFX_PKMN_TEDDIURSA_SHINY, 0x4ca },  // shiny SPECIES_TEDDIURSA
    { OBJ_EVENT_GFX_PKMN_URSARING_SHINY, 0x4cb },  // shiny SPECIES_URSARING
    { OBJ_EVENT_GFX_PKMN_SLUGMA_SHINY, 0x4cc },  // shiny SPECIES_SLUGMA
    { OBJ_EVENT_GFX_PKMN_MAGCARGO_SHINY, 0x4cd },  // shiny SPECIES_MAGCARGO
    { OBJ_EVENT_GFX_PKMN_SWINUB_SHINY, 0x4ce },  // shiny SPECIES_SWINUB
    { OBJ_EVENT_GFX_PKMN_PILOSWINE_SHINY, 0x4cf },  // shiny SPECIES_PILOSWINE
    { OBJ_EVENT_GFX_PKMN_CORSOLA_SHINY, 0x4d0 },  // shiny SPECIES_CORSOLA
    { OBJ_EVENT_GFX_PKMN_REMORAID_SHINY, 0x4d1 },  // shiny SPECIES_REMORAID
    { OBJ_EVENT_GFX_PKMN_OCTILLERY_SHINY, 0x4d2 },  // shiny SPECIES_OCTILLERY
    { OBJ_EVENT_GFX_PKMN_DELIBIRD_SHINY, 0x4d3 },  // shiny SPECIES_DELIBIRD
    { OBJ_EVENT_GFX_PKMN_MANTINE_SHINY, 0x4d4 },  // shiny SPECIES_MANTINE
    { OBJ_EVENT_GFX_PKMN_SKARMORY_SHINY, 0x4d5 },  // shiny SPECIES_SKARMORY
    { OBJ_EVENT_GFX_PKMN_HOUNDOUR_SHINY, 0x4d6 },  // shiny SPECIES_HOUNDOUR
    { OBJ_EVENT_GFX_PKMN_HOUNDOOM_SHINY, 0x4d7 },  // shiny SPECIES_HOUNDOOM
    { OBJ_EVENT_GFX_PKMN_KINGDRA_SHINY, 0x4d8 },  // shiny SPECIES_KINGDRA
    { OBJ_EVENT_GFX_PKMN_PHANPY_SHINY, 0x4d9 },  // shiny SPECIES_PHANPY
    { OBJ_EVENT_GFX_PKMN_DONPHAN_SHINY, 0x4da },  // shiny SPECIES_DONPHAN
    { OBJ_EVENT_GFX_PKMN_PORYGON2_SHINY, 0x4db },  // shiny SPECIES_PORYGON2
    { OBJ_EVENT_GFX_PKMN_STANTLER_SHINY, 0x4dc },  // shiny SPECIES_STANTLER
    { OBJ_EVENT_GFX_PKMN_SMEARGLE_SHINY, 0x4dd },  // shiny SPECIES_SMEARGLE
    { OBJ_EVENT_GFX_PKMN_TYROGUE_SHINY, 0x4de },  // shiny SPECIES_TYROGUE
    { OBJ_EVENT_GFX_PKMN_HITMONTOP_SHINY, 0x4df },  // shiny SPECIES_HITMONTOP
    { OBJ_EVENT_GFX_PKMN_SMOOCHUM_SHINY, 0x4e0 },  // shiny SPECIES_SMOOCHUM
    { OBJ_EVENT_GFX_PKMN_ELEKID_SHINY, 0x4e1 },  // shiny SPECIES_ELEKID
    { OBJ_EVENT_GFX_PKMN_MAGBY_SHINY, 0x4e2 },  // shiny SPECIES_MAGBY
    { OBJ_EVENT_GFX_PKMN_MILTANK_SHINY, 0x4e3 },  // shiny SPECIES_MILTANK
    { OBJ_EVENT_GFX_PKMN_BLISSEY_SHINY, 0x4e4 },  // shiny SPECIES_BLISSEY
    { OBJ_EVENT_GFX_PKMN_RAIKOU_SHINY, 0x4e5 },  // shiny SPECIES_RAIKOU
    { OBJ_EVENT_GFX_PKMN_ENTEI_SHINY, 0x4e6 },  // shiny SPECIES_ENTEI
    { OBJ_EVENT_GFX_PKMN_SUICUNE_SHINY, 0x4e7 },  // shiny SPECIES_SUICUNE
    { OBJ_EVENT_GFX_PKMN_LARVITAR_SHINY, 0x4e8 },  // shiny SPECIES_LARVITAR
    { OBJ_EVENT_GFX_PKMN_PUPITAR_SHINY, 0x4e9 },  // shiny SPECIES_PUPITAR
    { OBJ_EVENT_GFX_PKMN_TYRANITAR_SHINY, 0x4ea },  // shiny SPECIES_TYRANITAR
    { OBJ_EVENT_GFX_PKMN_LUGIA_SHINY, 0x4eb },  // shiny SPECIES_LUGIA
    { OBJ_EVENT_GFX_PKMN_HO_OH_SHINY, 0x4ec },  // shiny SPECIES_HO_OH
    { OBJ_EVENT_GFX_PKMN_CELEBI_SHINY, 0x4ed },  // shiny SPECIES_CELEBI
    { OBJ_EVENT_GFX_PKMN_TREECKO_SHINY, 0x4ee },  // shiny SPECIES_TREECKO
    { OBJ_EVENT_GFX_PKMN_GROVYLE_SHINY, 0x4ef },  // shiny SPECIES_GROVYLE
    { OBJ_EVENT_GFX_PKMN_SCEPTILE_SHINY, 0x4f0 },  // shiny SPECIES_SCEPTILE
    { OBJ_EVENT_GFX_PKMN_TORCHIC_SHINY, 0x4f1 },  // shiny SPECIES_TORCHIC
    { OBJ_EVENT_GFX_PKMN_COMBUSKEN_SHINY, 0x4f2 },  // shiny SPECIES_COMBUSKEN
    { OBJ_EVENT_GFX_PKMN_BLAZIKEN_SHINY, 0x4f3 },  // shiny SPECIES_BLAZIKEN
    { OBJ_EVENT_GFX_PKMN_MUDKIP_SHINY, 0x4f4 },  // shiny SPECIES_MUDKIP
    { OBJ_EVENT_GFX_PKMN_MARSHTOMP_SHINY, 0x4f5 },  // shiny SPECIES_MARSHTOMP
    { OBJ_EVENT_GFX_PKMN_SWAMPERT_SHINY, 0x4f6 },  // shiny SPECIES_SWAMPERT
    { OBJ_EVENT_GFX_PKMN_POOCHYENA_SHINY, 0x4f7 },  // shiny SPECIES_POOCHYENA
    { OBJ_EVENT_GFX_PKMN_MIGHTYENA_SHINY, 0x4f8 },  // shiny SPECIES_MIGHTYENA
    { OBJ_EVENT_GFX_PKMN_ZIGZAGOON_SHINY, 0x4f9 },  // shiny SPECIES_ZIGZAGOON
    { OBJ_EVENT_GFX_PKMN_LINOONE_SHINY, 0x4fa },  // shiny SPECIES_LINOONE
    { OBJ_EVENT_GFX_PKMN_WURMPLE_SHINY, 0x4fb },  // shiny SPECIES_WURMPLE
    { OBJ_EVENT_GFX_PKMN_SILCOON_SHINY, 0x4fc },  // shiny SPECIES_SILCOON
    { OBJ_EVENT_GFX_PKMN_BEAUTIFLY_SHINY, 0x4fd },  // shiny SPECIES_BEAUTIFLY
    { OBJ_EVENT_GFX_PKMN_CASCOON_SHINY, 0x4fe },  // shiny SPECIES_CASCOON
    { OBJ_EVENT_GFX_PKMN_DUSTOX_SHINY, 0x4ff },  // shiny SPECIES_DUSTOX
    { OBJ_EVENT_GFX_PKMN_LOTAD_SHINY, 0x500 },  // shiny SPECIES_LOTAD
    { OBJ_EVENT_GFX_PKMN_LOMBRE_SHINY, 0x501 },  // shiny SPECIES_LOMBRE
    { OBJ_EVENT_GFX_PKMN_LUDICOLO_SHINY, 0x502 },  // shiny SPECIES_LUDICOLO
    { OBJ_EVENT_GFX_PKMN_SEEDOT_SHINY, 0x503 },  // shiny SPECIES_SEEDOT
    { OBJ_EVENT_GFX_PKMN_NUZLEAF_SHINY, 0x504 },  // shiny SPECIES_NUZLEAF
    { OBJ_EVENT_GFX_PKMN_SHIFTRY_SHINY, 0x505 },  // shiny SPECIES_SHIFTRY
    { OBJ_EVENT_GFX_PKMN_TAILLOW_SHINY, 0x506 },  // shiny SPECIES_TAILLOW
    { OBJ_EVENT_GFX_PKMN_SWELLOW_SHINY, 0x507 },  // shiny SPECIES_SWELLOW
    { OBJ_EVENT_GFX_PKMN_WINGULL_SHINY, 0x508 },  // shiny SPECIES_WINGULL
    { OBJ_EVENT_GFX_PKMN_PELIPPER_SHINY, 0x509 },  // shiny SPECIES_PELIPPER
    { OBJ_EVENT_GFX_PKMN_RALTS_SHINY, 0x50a },  // shiny SPECIES_RALTS
    { OBJ_EVENT_GFX_PKMN_KIRLIA_SHINY, 0x50b },  // shiny SPECIES_KIRLIA
    { OBJ_EVENT_GFX_PKMN_GARDEVOIR_SHINY, 0x50c },  // shiny SPECIES_GARDEVOIR
    { OBJ_EVENT_GFX_PKMN_SURSKIT_SHINY, 0x50d },  // shiny SPECIES_SURSKIT
    { OBJ_EVENT_GFX_PKMN_MASQUERAIN_SHINY, 0x50e },  // shiny SPECIES_MASQUERAIN
    { OBJ_EVENT_GFX_PKMN_SHROOMISH_SHINY, 0x50f },  // shiny SPECIES_SHROOMISH
    { OBJ_EVENT_GFX_PKMN_BRELOOM_SHINY, 0x510 },  // shiny SPECIES_BRELOOM
    { OBJ_EVENT_GFX_PKMN_SLAKOTH_SHINY, 0x511 },  // shiny SPECIES_SLAKOTH
    { OBJ_EVENT_GFX_PKMN_VIGOROTH_SHINY, 0x512 },  // shiny SPECIES_VIGOROTH
    { OBJ_EVENT_GFX_PKMN_SLAKING_SHINY, 0x513 },  // shiny SPECIES_SLAKING
    { OBJ_EVENT_GFX_PKMN_NINCADA_SHINY, 0x514 },  // shiny SPECIES_NINCADA
    { OBJ_EVENT_GFX_PKMN_NINJASK_SHINY, 0x515 },  // shiny SPECIES_NINJASK
    { OBJ_EVENT_GFX_PKMN_SHEDINJA_SHINY, 0x516 },  // shiny SPECIES_SHEDINJA
    { OBJ_EVENT_GFX_PKMN_WHISMUR_SHINY, 0x517 },  // shiny SPECIES_WHISMUR
    { OBJ_EVENT_GFX_PKMN_LOUDRED_SHINY, 0x518 },  // shiny SPECIES_LOUDRED
    { OBJ_EVENT_GFX_PKMN_EXPLOUD_SHINY, 0x519 },  // shiny SPECIES_EXPLOUD
    { OBJ_EVENT_GFX_PKMN_MAKUHITA_SHINY, 0x51a },  // shiny SPECIES_MAKUHITA
    { OBJ_EVENT_GFX_PKMN_HARIYAMA_SHINY, 0x51b },  // shiny SPECIES_HARIYAMA
    { OBJ_EVENT_GFX_PKMN_AZURILL_SHINY, 0x51c },  // shiny SPECIES_AZURILL
    { OBJ_EVENT_GFX_PKMN_NOSEPASS_SHINY, 0x51d },  // shiny SPECIES_NOSEPASS
    { OBJ_EVENT_GFX_PKMN_SKITTY_SHINY, 0x51e },  // shiny SPECIES_SKITTY
    { OBJ_EVENT_GFX_PKMN_DELCATTY_SHINY, 0x51f },  // shiny SPECIES_DELCATTY
    { OBJ_EVENT_GFX_PKMN_SABLEYE_SHINY, 0x520 },  // shiny SPECIES_SABLEYE
    { OBJ_EVENT_GFX_PKMN_MAWILE_SHINY, 0x521 },  // shiny SPECIES_MAWILE
    { OBJ_EVENT_GFX_PKMN_ARON_SHINY, 0x522 },  // shiny SPECIES_ARON
    { OBJ_EVENT_GFX_PKMN_LAIRON_SHINY, 0x523 },  // shiny SPECIES_LAIRON
    { OBJ_EVENT_GFX_PKMN_AGGRON_SHINY, 0x524 },  // shiny SPECIES_AGGRON
    { OBJ_EVENT_GFX_PKMN_MEDITITE_SHINY, 0x525 },  // shiny SPECIES_MEDITITE
    { OBJ_EVENT_GFX_PKMN_MEDICHAM_SHINY, 0x526 },  // shiny SPECIES_MEDICHAM
    { OBJ_EVENT_GFX_PKMN_ELECTRIKE_SHINY, 0x527 },  // shiny SPECIES_ELECTRIKE
    { OBJ_EVENT_GFX_PKMN_MANECTRIC_SHINY, 0x528 },  // shiny SPECIES_MANECTRIC
    { OBJ_EVENT_GFX_PKMN_PLUSLE_SHINY, 0x529 },  // shiny SPECIES_PLUSLE
    { OBJ_EVENT_GFX_PKMN_MINUN_SHINY, 0x52a },  // shiny SPECIES_MINUN
    { OBJ_EVENT_GFX_PKMN_VOLBEAT_SHINY, 0x52b },  // shiny SPECIES_VOLBEAT
    { OBJ_EVENT_GFX_PKMN_ILLUMISE_SHINY, 0x52c },  // shiny SPECIES_ILLUMISE
    { OBJ_EVENT_GFX_PKMN_ROSELIA_SHINY, 0x52d },  // shiny SPECIES_ROSELIA
    { OBJ_EVENT_GFX_PKMN_GULPIN_SHINY, 0x52e },  // shiny SPECIES_GULPIN
    { OBJ_EVENT_GFX_PKMN_SWALOT_SHINY, 0x52f },  // shiny SPECIES_SWALOT
    { OBJ_EVENT_GFX_PKMN_CARVANHA_SHINY, 0x530 },  // shiny SPECIES_CARVANHA
    { OBJ_EVENT_GFX_PKMN_SHARPEDO_SHINY, 0x531 },  // shiny SPECIES_SHARPEDO
    { OBJ_EVENT_GFX_PKMN_WAILMER_SHINY, 0x532 },  // shiny SPECIES_WAILMER
    { OBJ_EVENT_GFX_PKMN_WAILORD_SHINY, 0x533 },  // shiny SPECIES_WAILORD
    { OBJ_EVENT_GFX_PKMN_NUMEL_SHINY, 0x534 },  // shiny SPECIES_NUMEL
    { OBJ_EVENT_GFX_PKMN_CAMERUPT_SHINY, 0x535 },  // shiny SPECIES_CAMERUPT
    { OBJ_EVENT_GFX_PKMN_TORKOAL_SHINY, 0x536 },  // shiny SPECIES_TORKOAL
    { OBJ_EVENT_GFX_PKMN_SPOINK_SHINY, 0x537 },  // shiny SPECIES_SPOINK
    { OBJ_EVENT_GFX_PKMN_GRUMPIG_SHINY, 0x538 },  // shiny SPECIES_GRUMPIG
    { OBJ_EVENT_GFX_PKMN_SPINDA_SHINY, 0x539 },  // shiny SPECIES_SPINDA
    { OBJ_EVENT_GFX_PKMN_TRAPINCH_SHINY, 0x53a },  // shiny SPECIES_TRAPINCH
    { OBJ_EVENT_GFX_PKMN_VIBRAVA_SHINY, 0x53b },  // shiny SPECIES_VIBRAVA
    { OBJ_EVENT_GFX_PKMN_FLYGON_SHINY, 0x53c },  // shiny SPECIES_FLYGON
    { OBJ_EVENT_GFX_PKMN_CACNEA_SHINY, 0x53d },  // shiny SPECIES_CACNEA
    { OBJ_EVENT_GFX_PKMN_CACTURNE_SHINY, 0x53e },  // shiny SPECIES_CACTURNE
    { OBJ_EVENT_GFX_PKMN_SWABLU_SHINY, 0x53f },  // shiny SPECIES_SWABLU
    { OBJ_EVENT_GFX_PKMN_ALTARIA_SHINY, 0x540 },  // shiny SPECIES_ALTARIA
    { OBJ_EVENT_GFX_PKMN_ZANGOOSE_SHINY, 0x541 },  // shiny SPECIES_ZANGOOSE
    { OBJ_EVENT_GFX_PKMN_SEVIPER_SHINY, 0x542 },  // shiny SPECIES_SEVIPER
    { OBJ_EVENT_GFX_PKMN_LUNATONE_SHINY, 0x543 },  // shiny SPECIES_LUNATONE
    { OBJ_EVENT_GFX_PKMN_SOLROCK_SHINY, 0x544 },  // shiny SPECIES_SOLROCK
    { OBJ_EVENT_GFX_PKMN_BARBOACH_SHINY, 0x545 },  // shiny SPECIES_BARBOACH
    { OBJ_EVENT_GFX_PKMN_WHISCASH_SHINY, 0x546 },  // shiny SPECIES_WHISCASH
    { OBJ_EVENT_GFX_PKMN_CORPHISH_SHINY, 0x547 },  // shiny SPECIES_CORPHISH
    { OBJ_EVENT_GFX_PKMN_CRAWDAUNT_SHINY, 0x548 },  // shiny SPECIES_CRAWDAUNT
    { OBJ_EVENT_GFX_PKMN_BALTOY_SHINY, 0x549 },  // shiny SPECIES_BALTOY
    { OBJ_EVENT_GFX_PKMN_CLAYDOL_SHINY, 0x54a },  // shiny SPECIES_CLAYDOL
    { OBJ_EVENT_GFX_PKMN_LILEEP_SHINY, 0x54b },  // shiny SPECIES_LILEEP
    { OBJ_EVENT_GFX_PKMN_CRADILY_SHINY, 0x54c },  // shiny SPECIES_CRADILY
    { OBJ_EVENT_GFX_PKMN_ANORITH_SHINY, 0x54d },  // shiny SPECIES_ANORITH
    { OBJ_EVENT_GFX_PKMN_ARMALDO_SHINY, 0x54e },  // shiny SPECIES_ARMALDO
    { OBJ_EVENT_GFX_PKMN_FEEBAS_SHINY, 0x54f },  // shiny SPECIES_FEEBAS
    { OBJ_EVENT_GFX_PKMN_MILOTIC_SHINY, 0x550 },  // shiny SPECIES_MILOTIC
    { OBJ_EVENT_GFX_PKMN_CASTFORM_SHINY, 0x551 },  // shiny SPECIES_CASTFORM
    { OBJ_EVENT_GFX_PKMN_KECLEON_SHINY, 0x552 },  // shiny SPECIES_KECLEON
    { OBJ_EVENT_GFX_PKMN_SHUPPET_SHINY, 0x553 },  // shiny SPECIES_SHUPPET
    { OBJ_EVENT_GFX_PKMN_BANETTE_SHINY, 0x554 },  // shiny SPECIES_BANETTE
    { OBJ_EVENT_GFX_PKMN_DUSKULL_SHINY, 0x555 },  // shiny SPECIES_DUSKULL
    { OBJ_EVENT_GFX_PKMN_DUSCLOPS_SHINY, 0x556 },  // shiny SPECIES_DUSCLOPS
    { OBJ_EVENT_GFX_PKMN_TROPIUS_SHINY, 0x557 },  // shiny SPECIES_TROPIUS
    { OBJ_EVENT_GFX_PKMN_CHIMECHO_SHINY, 0x558 },  // shiny SPECIES_CHIMECHO
    { OBJ_EVENT_GFX_PKMN_ABSOL_SHINY, 0x559 },  // shiny SPECIES_ABSOL
    { OBJ_EVENT_GFX_PKMN_WYNAUT_SHINY, 0x55a },  // shiny SPECIES_WYNAUT
    { OBJ_EVENT_GFX_PKMN_SNORUNT_SHINY, 0x55b },  // shiny SPECIES_SNORUNT
    { OBJ_EVENT_GFX_PKMN_GLALIE_SHINY, 0x55c },  // shiny SPECIES_GLALIE
    { OBJ_EVENT_GFX_PKMN_SPHEAL_SHINY, 0x55d },  // shiny SPECIES_SPHEAL
    { OBJ_EVENT_GFX_PKMN_SEALEO_SHINY, 0x55e },  // shiny SPECIES_SEALEO
    { OBJ_EVENT_GFX_PKMN_WALREIN_SHINY, 0x55f },  // shiny SPECIES_WALREIN
    { OBJ_EVENT_GFX_PKMN_CLAMPERL_SHINY, 0x560 },  // shiny SPECIES_CLAMPERL
    { OBJ_EVENT_GFX_PKMN_HUNTAIL_SHINY, 0x561 },  // shiny SPECIES_HUNTAIL
    { OBJ_EVENT_GFX_PKMN_GOREBYSS_SHINY, 0x562 },  // shiny SPECIES_GOREBYSS
    { OBJ_EVENT_GFX_PKMN_RELICANTH_SHINY, 0x563 },  // shiny SPECIES_RELICANTH
    { OBJ_EVENT_GFX_PKMN_LUVDISC_SHINY, 0x564 },  // shiny SPECIES_LUVDISC
    { OBJ_EVENT_GFX_PKMN_BAGON_SHINY, 0x565 },  // shiny SPECIES_BAGON
    { OBJ_EVENT_GFX_PKMN_SHELGON_SHINY, 0x566 },  // shiny SPECIES_SHELGON
    { OBJ_EVENT_GFX_PKMN_SALAMENCE_SHINY, 0x567 },  // shiny SPECIES_SALAMENCE
    { OBJ_EVENT_GFX_PKMN_BELDUM_SHINY, 0x568 },  // shiny SPECIES_BELDUM
    { OBJ_EVENT_GFX_PKMN_METANG_SHINY, 0x569 },  // shiny SPECIES_METANG
    { OBJ_EVENT_GFX_PKMN_METAGROSS_SHINY, 0x56a },  // shiny SPECIES_METAGROSS
    { OBJ_EVENT_GFX_PKMN_REGIROCK_SHINY, 0x56b },  // shiny SPECIES_REGIROCK
    { OBJ_EVENT_GFX_PKMN_REGICE_SHINY, 0x56c },  // shiny SPECIES_REGICE
    { OBJ_EVENT_GFX_PKMN_REGISTEEL_SHINY, 0x56d },  // shiny SPECIES_REGISTEEL
    { OBJ_EVENT_GFX_PKMN_LATIAS_SHINY, 0x56e },  // shiny SPECIES_LATIAS
    { OBJ_EVENT_GFX_PKMN_LATIOS_SHINY, 0x56f },  // shiny SPECIES_LATIOS
    { OBJ_EVENT_GFX_PKMN_KYOGRE_SHINY, 0x570 },  // shiny SPECIES_KYOGRE
    { OBJ_EVENT_GFX_PKMN_GROUDON_SHINY, 0x571 },  // shiny SPECIES_GROUDON
    { OBJ_EVENT_GFX_PKMN_RAYQUAZA_SHINY, 0x572 },  // shiny SPECIES_RAYQUAZA
    { OBJ_EVENT_GFX_PKMN_JIRACHI_SHINY, 0x573 },  // shiny SPECIES_JIRACHI
    { OBJ_EVENT_GFX_PKMN_DEOXYS_SHINY, 0x574 },  // shiny SPECIES_DEOXYS
    { OBJ_EVENT_GFX_PKMN_TURTWIG_SHINY, 0x575 },  // shiny SPECIES_TURTWIG
    { OBJ_EVENT_GFX_PKMN_GROTLE_SHINY, 0x576 },  // shiny SPECIES_GROTLE
    { OBJ_EVENT_GFX_PKMN_TORTERRA_SHINY, 0x577 },  // shiny SPECIES_TORTERRA
    { OBJ_EVENT_GFX_PKMN_CHIMCHAR_SHINY, 0x578 },  // shiny SPECIES_CHIMCHAR
    { OBJ_EVENT_GFX_PKMN_MONFERNO_SHINY, 0x579 },  // shiny SPECIES_MONFERNO
    { OBJ_EVENT_GFX_PKMN_INFERNAPE_SHINY, 0x57a },  // shiny SPECIES_INFERNAPE
    { OBJ_EVENT_GFX_PKMN_PIPLUP_SHINY, 0x57b },  // shiny SPECIES_PIPLUP
    { OBJ_EVENT_GFX_PKMN_PRINPLUP_SHINY, 0x57c },  // shiny SPECIES_PRINPLUP
    { OBJ_EVENT_GFX_PKMN_EMPOLEON_SHINY, 0x57d },  // shiny SPECIES_EMPOLEON
    { OBJ_EVENT_GFX_PKMN_STARLY_SHINY, 0x57e },  // shiny SPECIES_STARLY
    { OBJ_EVENT_GFX_PKMN_STARAVIA_SHINY, 0x57f },  // shiny SPECIES_STARAVIA
    { OBJ_EVENT_GFX_PKMN_STARAPTOR_SHINY, 0x580 },  // shiny SPECIES_STARAPTOR
    { OBJ_EVENT_GFX_PKMN_BIDOOF_SHINY, 0x581 },  // shiny SPECIES_BIDOOF
    { OBJ_EVENT_GFX_PKMN_BIBAREL_SHINY, 0x582 },  // shiny SPECIES_BIBAREL
    { OBJ_EVENT_GFX_PKMN_KRICKETOT_SHINY, 0x583 },  // shiny SPECIES_KRICKETOT
    { OBJ_EVENT_GFX_PKMN_KRICKETUNE_SHINY, 0x584 },  // shiny SPECIES_KRICKETUNE
    { OBJ_EVENT_GFX_PKMN_SHINX_SHINY, 0x585 },  // shiny SPECIES_SHINX
    { OBJ_EVENT_GFX_PKMN_LUXIO_SHINY, 0x586 },  // shiny SPECIES_LUXIO
    { OBJ_EVENT_GFX_PKMN_LUXRAY_SHINY, 0x587 },  // shiny SPECIES_LUXRAY
    { OBJ_EVENT_GFX_PKMN_BUDEW_SHINY, 0x588 },  // shiny SPECIES_BUDEW
    { OBJ_EVENT_GFX_PKMN_ROSERADE_SHINY, 0x589 },  // shiny SPECIES_ROSERADE
    { OBJ_EVENT_GFX_PKMN_CRANIDOS_SHINY, 0x58a },  // shiny SPECIES_CRANIDOS
    { OBJ_EVENT_GFX_PKMN_RAMPARDOS_SHINY, 0x58b },  // shiny SPECIES_RAMPARDOS
    { OBJ_EVENT_GFX_PKMN_SHIELDON_SHINY, 0x58c },  // shiny SPECIES_SHIELDON
    { OBJ_EVENT_GFX_PKMN_BASTIODON_SHINY, 0x58d },  // shiny SPECIES_BASTIODON
    { OBJ_EVENT_GFX_PKMN_BURMY_SHINY, 0x58e },  // shiny SPECIES_BURMY
    { OBJ_EVENT_GFX_PKMN_WORMADAM_SHINY, 0x58f },  // shiny SPECIES_WORMADAM
    { OBJ_EVENT_GFX_PKMN_MOTHIM_SHINY, 0x590 },  // shiny SPECIES_MOTHIM
    { OBJ_EVENT_GFX_PKMN_COMBEE_SHINY, 0x591 },  // shiny SPECIES_COMBEE
    { OBJ_EVENT_GFX_PKMN_COMBEE_F_SHINY, 0x592 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_VESPIQUEN_SHINY, 0x593 },  // shiny SPECIES_VESPIQUEN
    { OBJ_EVENT_GFX_PKMN_PACHIRISU_SHINY, 0x594 },  // shiny SPECIES_PACHIRISU
    { OBJ_EVENT_GFX_PKMN_BUIZEL_SHINY, 0x595 },  // shiny SPECIES_BUIZEL
    { OBJ_EVENT_GFX_PKMN_FLOATZEL_SHINY, 0x596 },  // shiny SPECIES_FLOATZEL
    { OBJ_EVENT_GFX_PKMN_CHERUBI_SHINY, 0x597 },  // shiny SPECIES_CHERUBI
    { OBJ_EVENT_GFX_PKMN_CHERRIM_SHINY, 0x598 },  // shiny SPECIES_CHERRIM
    { OBJ_EVENT_GFX_PKMN_SHELLOS_SHINY, 0x599 },  // shiny SPECIES_SHELLOS
    { OBJ_EVENT_GFX_PKMN_GASTRODON_SHINY, 0x59a },  // shiny SPECIES_GASTRODON
    { OBJ_EVENT_GFX_PKMN_AMBIPOM_SHINY, 0x59b },  // shiny SPECIES_AMBIPOM
    { OBJ_EVENT_GFX_PKMN_DRIFLOON_SHINY, 0x59c },  // shiny SPECIES_DRIFLOON
    { OBJ_EVENT_GFX_PKMN_DRIFBLIM_SHINY, 0x59d },  // shiny SPECIES_DRIFBLIM
    { OBJ_EVENT_GFX_PKMN_BUNEARY_SHINY, 0x59e },  // shiny SPECIES_BUNEARY
    { OBJ_EVENT_GFX_PKMN_LOPUNNY_SHINY, 0x59f },  // shiny SPECIES_LOPUNNY
    { OBJ_EVENT_GFX_PKMN_MISMAGIUS_SHINY, 0x5a0 },  // shiny SPECIES_MISMAGIUS
    { OBJ_EVENT_GFX_PKMN_HONCHKROW_SHINY, 0x5a1 },  // shiny SPECIES_HONCHKROW
    { OBJ_EVENT_GFX_PKMN_GLAMEOW_SHINY, 0x5a2 },  // shiny SPECIES_GLAMEOW
    { OBJ_EVENT_GFX_PKMN_PURUGLY_SHINY, 0x5a3 },  // shiny SPECIES_PURUGLY
    { OBJ_EVENT_GFX_PKMN_CHINGLING_SHINY, 0x5a4 },  // shiny SPECIES_CHINGLING
    { OBJ_EVENT_GFX_PKMN_STUNKY_SHINY, 0x5a5 },  // shiny SPECIES_STUNKY
    { OBJ_EVENT_GFX_PKMN_SKUNTANK_SHINY, 0x5a6 },  // shiny SPECIES_SKUNTANK
    { OBJ_EVENT_GFX_PKMN_BRONZOR_SHINY, 0x5a7 },  // shiny SPECIES_BRONZOR
    { OBJ_EVENT_GFX_PKMN_BRONZONG_SHINY, 0x5a8 },  // shiny SPECIES_BRONZONG
    { OBJ_EVENT_GFX_PKMN_BONSLY_SHINY, 0x5a9 },  // shiny SPECIES_BONSLY
    { OBJ_EVENT_GFX_PKMN_MIMEJR_SHINY, 0x5aa },  // shiny SPECIES_MIMEJR
    { OBJ_EVENT_GFX_PKMN_HAPPINY_SHINY, 0x5ab },  // shiny SPECIES_HAPPINY
    { OBJ_EVENT_GFX_PKMN_CHATOT_SHINY, 0x5ac },  // shiny SPECIES_CHATOT
    { OBJ_EVENT_GFX_PKMN_SPIRITOMB_SHINY, 0x5ad },  // shiny SPECIES_SPIRITOMB
    { OBJ_EVENT_GFX_PKMN_GIBLE_SHINY, 0x5ae },  // shiny SPECIES_GIBLE
    { OBJ_EVENT_GFX_PKMN_GABITE_SHINY, 0x5af },  // shiny SPECIES_GABITE
    { OBJ_EVENT_GFX_PKMN_GARCHOMP_SHINY, 0x5b0 },  // shiny SPECIES_GARCHOMP
    { OBJ_EVENT_GFX_PKMN_MUNCHLAX_SHINY, 0x5b1 },  // shiny SPECIES_MUNCHLAX
    { OBJ_EVENT_GFX_PKMN_RIOLU_SHINY, 0x5b2 },  // shiny SPECIES_RIOLU
    { OBJ_EVENT_GFX_PKMN_LUCARIO_SHINY, 0x5b3 },  // shiny SPECIES_LUCARIO
    { OBJ_EVENT_GFX_PKMN_HIPPOPOTAS_SHINY, 0x5b4 },  // shiny SPECIES_HIPPOPOTAS
    { OBJ_EVENT_GFX_PKMN_HIPPOPOTAS_F_SHINY, 0x5b5 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_HIPPOWDON_SHINY, 0x5b6 },  // shiny SPECIES_HIPPOWDON
    { OBJ_EVENT_GFX_PKMN_HIPPOWDON_F_SHINY, 0x5b7 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_SKORUPI_SHINY, 0x5b8 },  // shiny SPECIES_SKORUPI
    { OBJ_EVENT_GFX_PKMN_DRAPION_SHINY, 0x5b9 },  // shiny SPECIES_DRAPION
    { OBJ_EVENT_GFX_PKMN_CROAGUNK_SHINY, 0x5ba },  // shiny SPECIES_CROAGUNK
    { OBJ_EVENT_GFX_PKMN_TOXICROAK_SHINY, 0x5bb },  // shiny SPECIES_TOXICROAK
    { OBJ_EVENT_GFX_PKMN_CARNIVINE_SHINY, 0x5bc },  // shiny SPECIES_CARNIVINE
    { OBJ_EVENT_GFX_PKMN_FINNEON_SHINY, 0x5bd },  // shiny SPECIES_FINNEON
    { OBJ_EVENT_GFX_PKMN_LUMINEON_SHINY, 0x5be },  // shiny SPECIES_LUMINEON
    { OBJ_EVENT_GFX_PKMN_MANTYKE_SHINY, 0x5bf },  // shiny SPECIES_MANTYKE
    { OBJ_EVENT_GFX_PKMN_SNOVER_SHINY, 0x5c0 },  // shiny SPECIES_SNOVER
    { OBJ_EVENT_GFX_PKMN_ABOMASNOW_SHINY, 0x5c1 },  // shiny SPECIES_ABOMASNOW
    { OBJ_EVENT_GFX_PKMN_WEAVILE_SHINY, 0x5c2 },  // shiny SPECIES_WEAVILE
    { OBJ_EVENT_GFX_PKMN_MAGNEZONE_SHINY, 0x5c3 },  // shiny SPECIES_MAGNEZONE
    { OBJ_EVENT_GFX_PKMN_LICKILICKY_SHINY, 0x5c4 },  // shiny SPECIES_LICKILICKY
    { OBJ_EVENT_GFX_PKMN_RHYPERIOR_SHINY, 0x5c5 },  // shiny SPECIES_RHYPERIOR
    { OBJ_EVENT_GFX_PKMN_TANGROWTH_SHINY, 0x5c6 },  // shiny SPECIES_TANGROWTH
    { OBJ_EVENT_GFX_PKMN_ELECTIVIRE_SHINY, 0x5c7 },  // shiny SPECIES_ELECTIVIRE
    { OBJ_EVENT_GFX_PKMN_MAGMORTAR_SHINY, 0x5c8 },  // shiny SPECIES_MAGMORTAR
    { OBJ_EVENT_GFX_PKMN_TOGEKISS_SHINY, 0x5c9 },  // shiny SPECIES_TOGEKISS
    { OBJ_EVENT_GFX_PKMN_LEAFEON_SHINY, 0x5ca },  // shiny SPECIES_LEAFEON
    { OBJ_EVENT_GFX_PKMN_GLACEON_SHINY, 0x5cb },  // shiny SPECIES_GLACEON
    { OBJ_EVENT_GFX_PKMN_GLISCOR_SHINY, 0x5cc },  // shiny SPECIES_GLISCOR
    { OBJ_EVENT_GFX_PKMN_MAMOSWINE_SHINY, 0x5cd },  // shiny SPECIES_MAMOSWINE
    { OBJ_EVENT_GFX_PKMN_PORYGON_Z_SHINY, 0x5ce },  // shiny SPECIES_PORYGON_Z
    { OBJ_EVENT_GFX_PKMN_GALLADE_SHINY, 0x5cf },  // shiny SPECIES_GALLADE
    { OBJ_EVENT_GFX_PKMN_PROBOPASS_SHINY, 0x5d0 },  // shiny SPECIES_PROBOPASS
    { OBJ_EVENT_GFX_PKMN_DUSKNOIR_SHINY, 0x5d1 },  // shiny SPECIES_DUSKNOIR
    { OBJ_EVENT_GFX_PKMN_FROSLASS_SHINY, 0x5d2 },  // shiny SPECIES_FROSLASS
    { OBJ_EVENT_GFX_PKMN_ROTOM_SHINY, 0x5d3 },  // shiny SPECIES_ROTOM
    { OBJ_EVENT_GFX_PKMN_UXIE_SHINY, 0x5d4 },  // shiny SPECIES_UXIE
    { OBJ_EVENT_GFX_PKMN_MESPRIT_SHINY, 0x5d5 },  // shiny SPECIES_MESPRIT
    { OBJ_EVENT_GFX_PKMN_AZELF_SHINY, 0x5d6 },  // shiny SPECIES_AZELF
    { OBJ_EVENT_GFX_PKMN_DIALGA_SHINY, 0x5d7 },  // shiny SPECIES_DIALGA
    { OBJ_EVENT_GFX_PKMN_PALKIA_SHINY, 0x5d8 },  // shiny SPECIES_PALKIA
    { OBJ_EVENT_GFX_PKMN_HEATRAN_SHINY, 0x5d9 },  // shiny SPECIES_HEATRAN
    { OBJ_EVENT_GFX_PKMN_REGIGIGAS_SHINY, 0x5da },  // shiny SPECIES_REGIGIGAS
    { OBJ_EVENT_GFX_PKMN_GIRATINA_SHINY, 0x5db },  // shiny SPECIES_GIRATINA
    { OBJ_EVENT_GFX_PKMN_CRESSELIA_SHINY, 0x5dc },  // shiny SPECIES_CRESSELIA
    { OBJ_EVENT_GFX_PKMN_PHIONE_SHINY, 0x5dd },  // shiny SPECIES_PHIONE
    { OBJ_EVENT_GFX_PKMN_MANAPHY_SHINY, 0x5de },  // shiny SPECIES_MANAPHY
    { OBJ_EVENT_GFX_PKMN_DARKRAI_SHINY, 0x5df },  // shiny SPECIES_DARKRAI
    { OBJ_EVENT_GFX_PKMN_SHAYMIN_SHINY, 0x5e0 },  // shiny SPECIES_SHAYMIN
    { OBJ_EVENT_GFX_PKMN_ARCEUS_SHINY, 0x5e1 },  // shiny SPECIES_ARCEUS
    { OBJ_EVENT_GFX_PKMN_GIRATINA_O_SHINY, 0x5e2 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FIGHTING_SHINY, 0x5e3 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FLYING_SHINY, 0x5e4 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_POISON_SHINY, 0x5e5 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GROUND_SHINY, 0x5e6 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ROCK_SHINY, 0x5e7 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_BUG_SHINY, 0x5e8 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GHOST_SHINY, 0x5e9 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_STEEL_SHINY, 0x5ea },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FAIRY_SHINY, 0x5eb },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FIRE_SHINY, 0x5ec },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_WATER_SHINY, 0x5ed },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GRASS_SHINY, 0x5ee },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ELECTRIC_SHINY, 0x5ef },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_PSYCHIC_SHINY, 0x5f0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ICE_SHINY, 0x5f1 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_DRAGON_SHINY, 0x5f2 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_DARK_SHINY, 0x5f3 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_DEOXYS_ATTACK_SHINY, 0x5f4 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_DEOXYS_DEFENSE_SHINY, 0x5f5 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_DEOXYS_SPEED_SHINY, 0x5f6 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_BURMY_SANDY_SHINY, 0x5f7 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_BURMY_TRASH_SHINY, 0x5f8 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_WORMADAM_SANDY_SHINY, 0x5f9 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_WORMADAM_TRASH_SHINY, 0x5fa },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_SHELLOS_EAST_SHINY, 0x5fb },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_GASTRODON_EAST_SHINY, 0x5fc },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ROTOM_HEAT_SHINY, 0x5fd },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ROTOM_WASH_SHINY, 0x5fe },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ROTOM_FROST_SHINY, 0x5ff },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ROTOM_FAN_SHINY, 0x600 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ROTOM_MOW_SHINY, 0x601 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_SHAYMIN_SKY_SHINY, 0x602 },  // shiny alt form
    { 0xffff, 0x0 }
};

const UnkStruct_ov5_021ED2D0 Unk_ov5_021FB484[] = {
    { 0x0, 0x1A5 },
    { 0x1, 0x1A6 },
    { 0x2, 0x1A7 },
    { 0x3, 0x1A8 },
    { 0x4, 0x1A9 },
    { 0x5, 0x1AC },
    { 0x6, 0x1B3 },
    { 0x7, 0x1B4 },
    { 0x8, 0x1B5 },
    { 0x9, 0x1A5 },
    { 0xA, 0x1B6 },
    { 0xB, 0x1B8 },
    { 0xC, 0x1B9 },
    { 0xD, 0x1BA },
    { 0xE, 0x1BB },
    { 0xf, 0x1B7 },
    { 0x10, 0x1BC },
    { 0x11, 0x1A5 },
    { 0x12, 0x3DE },
    { 0xffff, 0x0 }
};

const UnkStruct_ov5_021ED2D0 Unk_ov5_021FB5BC[] = {
    { 0x0, 0x1BD },
    { 0x1, 0x1BE },
    { 0x2, 0x1BF },
    { 0x3, 0x1C0 },
    { 0x4, 0x1C1 },
    { 0x5, 0x1C2 },
    { 0x6, 0x1C3 },
    { 0x7, 0x1C4 },
    { 0x8, 0x1C5 },
    { 0x9, 0x1C6 },
    { 0xA, 0x1C7 },
    { 0xB, 0x1C8 },
    { 0xC, 0x1C9 },
    { 0xD, 0x1CA },
    { 0xE, 0x1CB },
    { 0xf, 0x1CC },
    { 0x10, 0x1CD },
    { 0x11, 0x1CE },
    { 0x12, 0x1CF },
    { 0x13, 0x1D0 },
    { 0x14, 0x1D1 },
    { 0x15, 0x1D2 },
    { 0x16, 0x1D3 },
    { 0x17, 0x1D7 },
    { 0xffff, 0x0 }
};

static const BillboardAnim Unk_ov5_021FB380[] = {
    { 0x0, 0xF, 0x0 },
    { 0x10, 0x1F, 0x0 },
    { 0x20, 0x2F, 0x0 },
    { 0x30, 0x3F, 0x0 },
    { 0x40, 0x4F, 0x0 },
    { 0x50, 0x5F, 0x0 },
    { 0x60, 0x6F, 0x0 },
    { 0x70, 0x7F, 0x0 },
    { 0x0, 0x0, 0x2 }
};

static const BillboardAnim Unk_ov5_021FB3EC[] = {
    { 0x0, 0xF, 0x0 },
    { 0x10, 0x1F, 0x0 },
    { 0x20, 0x2F, 0x0 },
    { 0x30, 0x3F, 0x0 },
    { 0x40, 0x47, 0x0 },
    { 0x48, 0x4F, 0x0 },
    { 0x50, 0x53, 0x1 },
    { 0x54, 0x57, 0x1 },
    { 0x58, 0x5B, 0x1 },
    { 0x5C, 0x5F, 0x1 },
    { 0x0, 0x0, 0x2 }
};

static const BillboardAnim Unk_ov5_021FB284[] = {
    { 0x0, 0x2, 0x0 },
    { 0x3, 0x5, 0x0 },
    { 0x6, 0x9, 0x0 },
    { 0xA, 0xB, 0x0 },
    { 0x0, 0x0, 0x2 }
};

static const BillboardAnim Unk_ov5_021FB134[] = {
    { 0x0, 0xA, 0x1 },
    { 0x0, 0x0, 0x2 }
};

static const BillboardAnim Unk_ov5_021FB200[] = {
    { 0x0, 0xF, 0x0 },
    { 0x10, 0x1C, 0x0 },
    { 0x0, 0x0, 0x2 }
};

static const BillboardAnim Unk_ov5_021FB2C0[] = {
    { 0x0, 0xF, 0x0 },
    { 0x10, 0x1F, 0x0 },
    { 0x20, 0x2F, 0x0 },
    { 0x30, 0x3F, 0x0 },
    { 0x0, 0x0, 0x2 }
};

static const BillboardAnim Unk_ov5_021FB338[] = {
    { 0x0, 0xF, 0x0 },
    { 0x10, 0x1F, 0x0 },
    { 0x20, 0x2F, 0x0 },
    { 0x30, 0x3F, 0x0 },
    { 0x40, 0x44, 0x1 },
    { 0x0, 0x0, 0x2 }
};

static const BillboardAnim Unk_ov5_021FB17C[] = {
    { 0x0, 0x3C, 0x0 },
    { 0x0, 0x0, 0x2 }
};

static const BillboardAnim Unk_ov5_021FB224[] = {
    { 0x0, 0x7, 0x0 },
    { 0x8, 0x10, 0x0 },
    { 0x0, 0x0, 0x2 }
};

static const BillboardAnim Unk_ov5_021FB1AC[] = {
    { 0x0, 0x10, 0x0 },
    { 0x0, 0x0, 0x2 }
};

static const BillboardAnim Unk_ov5_021FB1C4[] = {
    { 0x0, 0x10, 0x0 },
    { 0x0, 0x0, 0x2 }
};

static const BillboardAnim Unk_ov5_021FB2FC[] = {
    { 0x0, 0xF, 0x1 },
    { 0x10, 0x1F, 0x1 },
    { 0x20, 0x2F, 0x1 },
    { 0x30, 0x40, 0x1 },
    { 0x0, 0x0, 0x2 }
};

static const BillboardAnim Unk_ov5_021FB104[] = {
    { 0x0, 0x20, 0x0 },
    { 0x0, 0x0, 0x2 }
};

static const BillboardAnim Unk_ov5_021FB248[] = {
    { 0x0, 0xB, 0x1 },
    { 0xC, 0x17, 0x1 },
    { 0x18, 0x23, 0x1 },
    { 0x24, 0x30, 0x1 },
    { 0x0, 0x0, 0x2 }
};

static const BillboardAnim Unk_ov5_021FB11C[] = {
    { 0x0, 0x8, 0x1 },
    { 0x0, 0x0, 0x2 }
};

static const BillboardAnim Unk_ov5_021FB1DC[] = {
    { 0x0, 0x14, 0x1 },
    { 0x15, 0x29, 0x1 },
    { 0x0, 0x0, 0x2 }
};

static const BillboardAnim Unk_ov5_021FB14C[] = {
    { 0x0, 0x14, 0x0 },
    { 0x0, 0x0, 0x2 }
};

static const BillboardAnim Unk_ov5_021FB164[] = {
    { 0x0, 0x13, 0x0 },
    { 0x0, 0x0, 0x2 }
};

static const BillboardAnim Unk_ov5_021FB194[] = {
    { 0x0, 0x3B, 0x1 },
    { 0x0, 0x0, 0x2 }
};

const int dummy2[] = {
    0x1,
    0x2,
    0x3,
    0x4,
    0x5,
    0x6,
    0x7,
    0x8,
    0x9,
    0xa,
    0xb,
    0xc,
    0xd,
    0xe,
    0xf,
    0x10,
    0x11,
    0x12,
    0x13,
    0x14,
    0xffff
};

const int Unk_ov5_021FAF50[] = {
    0x0,
    0x1,
    0x2,
    0xffff
};

const int Unk_ov5_021FAF48[] = {
    0x0,
    0xffff
};

const UnkStruct_ov5_021EDD04 Unk_ov5_021FD77C[] = {
    { 0x0, 0x0, 0x1, Unk_ov5_021FB380 },
    { 0x1, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x2, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x3, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x4, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x5, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x6, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x7, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x8, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x9, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xA, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xB, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xC, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xD, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xE, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xf, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x10, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x11, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x12, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x13, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x14, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x15, 0x0, 0x3, Unk_ov5_021FB3EC },
    { 0x16, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x17, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x18, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x19, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x1A, 0x0, 0xB, Unk_ov5_021FB338 },
    { 0x1B, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x1C, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x1D, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x1E, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x1f, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x20, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x21, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x22, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x23, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x24, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x25, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x26, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x27, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x28, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x29, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x2A, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x2B, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x2C, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x2D, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x2E, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x2f, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x30, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x31, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x32, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x33, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x34, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x35, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x36, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x37, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x38, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x39, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x3A, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x3B, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x3C, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x3D, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x3E, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x3f, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x40, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x41, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x42, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x43, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x44, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x45, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x46, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x47, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x48, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x49, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x4A, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x4B, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x4C, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x4D, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x4E, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x4f, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x50, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x51, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x52, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x53, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x54, 0x1, 0x0, Unk_ov5_021FB2C0 },
    { 0x55, 0x2, 0x0, Unk_ov5_021FB2C0 },
    { 0x56, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x57, 0x1, 0x0, Unk_ov5_021FB2C0 },
    { 0x58, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x59, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x5A, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x61, 0x0, 0x1, Unk_ov5_021FB380 },
    { 0x62, 0x0, 0x3, Unk_ov5_021FB3EC },
    { 0x63, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x1000, 0x3, 0x2, Unk_ov5_021FB17C },
    { 0x1001, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1002, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1003, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x78, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x79, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x7A, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x7B, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x7C, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x7D, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x7E, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x7f, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x80, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x81, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x82, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x83, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x84, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x85, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x86, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x87, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x88, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x89, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x8A, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x8B, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x8C, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x8D, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x8E, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x8f, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x90, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x91, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x92, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x93, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x94, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x95, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x96, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x97, 0x0, 0x8, Unk_ov5_021FB1C4 },
    { 0x98, 0x0, 0x8, Unk_ov5_021FB1C4 },
    { 0x99, 0x0, 0x8, Unk_ov5_021FB1C4 },
    { 0x9A, 0x5, 0x8, Unk_ov5_021FB1AC },
    { 0x9B, 0x5, 0x8, Unk_ov5_021FB1AC },
    { 0x9C, 0x5, 0x10, Unk_ov5_021FB14C },
    { 0x9D, 0x0, 0x11, Unk_ov5_021FB14C },
    { 0x9E, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x9f, 0x0, 0x12, Unk_ov5_021FB14C },
    { 0xA0, 0x5, 0x13, Unk_ov5_021FB14C },
    { 0xA1, 0x0, 0x14, Unk_ov5_021FB14C },
    { 0xA2, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xA3, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xA4, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xA5, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xA6, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xA7, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xA8, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xA9, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xAA, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xAB, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xAC, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xAD, 0x0, 0x7, Unk_ov5_021FB224 },
    { 0xAE, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xaf, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xB0, 0x0, 0x4, Unk_ov5_021FB134 },
    { 0xB1, 0x0, 0x4, Unk_ov5_021FB134 },
    { 0xB2, 0x0, 0x6, Unk_ov5_021FB284 },
    { 0xB3, 0x0, 0x6, Unk_ov5_021FB284 },
    { 0xB4, 0x0, 0x5, Unk_ov5_021FB200 },
    { 0xB5, 0x0, 0x5, Unk_ov5_021FB200 },
    { 0xB6, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xB8, 0x5, 0x0, Unk_ov5_021FB2C0 },
    { 0xB9, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xBA, 0x0, 0x9, Unk_ov5_021FB380 },
    { 0xBB, 0x0, 0x9, Unk_ov5_021FB380 },
    { 0xBC, 0x6, 0xA, Unk_ov5_021FB2FC },
    { 0xBD, 0x6, 0xA, Unk_ov5_021FB2FC },
    { 0xBE, 0x1, 0x0, Unk_ov5_021FB2C0 },
    { 0xbf, 0x1, 0x0, Unk_ov5_021FB2C0 },
    { 0xC0, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0x1004, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1005, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1006, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1007, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1008, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1009, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x100A, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x100B, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x100C, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x100D, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x100E, 0x4, 0x2, Unk_ov5_021FB17C },
    { (0x1000 + 0xf), 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1010, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1011, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1012, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1013, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1014, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1015, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1016, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1017, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1018, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1019, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x101A, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x101B, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x101C, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x101D, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x101E, 0x4, 0x2, Unk_ov5_021FB17C },
    { (0x1000 + 0x1f), 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1020, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1021, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1022, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1023, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1024, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1025, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1026, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1027, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1028, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1029, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x102A, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x102B, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x102C, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x102D, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x102E, 0x4, 0x2, Unk_ov5_021FB17C },
    { (0x1000 + 0x2f), 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1030, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1031, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1032, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1033, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1034, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1035, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1036, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1037, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1038, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1039, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x103A, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x103B, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x103C, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x103D, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x103E, 0x4, 0x2, Unk_ov5_021FB17C },
    { (0x1000 + 0x3f), 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1040, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1041, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1042, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1043, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1044, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1045, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1046, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1047, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1048, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1049, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x104A, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x104B, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x104C, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x104D, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x104E, 0x4, 0x2, Unk_ov5_021FB17C },
    { (0x1000 + 0x4f), 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1050, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1051, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1052, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1053, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1054, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1055, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1056, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1057, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1058, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1059, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x105A, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x105B, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x105C, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x105D, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x105E, 0x4, 0x2, Unk_ov5_021FB17C },
    { (0x1000 + 0x5f), 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1060, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1061, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1062, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1063, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1064, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1065, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1066, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1067, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1068, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1069, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x106A, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x106B, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x106C, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x106D, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x106E, 0x4, 0x2, Unk_ov5_021FB17C },
    { (0x1000 + 0x6f), 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1070, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1071, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1072, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1073, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1074, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1075, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1076, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1077, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1078, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1079, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x107A, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x107B, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x107C, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x107D, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x107E, 0x4, 0x2, Unk_ov5_021FB17C },
    { (0x1000 + 0x7f), 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1080, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1081, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1082, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1083, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1084, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1085, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1086, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1087, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1088, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1089, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x108A, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x108B, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x108C, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x108D, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x108E, 0x4, 0x2, Unk_ov5_021FB17C },
    { (0x1000 + 0x8f), 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1090, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1091, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1092, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1093, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1094, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1095, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1096, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1097, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1098, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x1099, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x109A, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x109B, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x109C, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x109D, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x109E, 0x4, 0x2, Unk_ov5_021FB17C },
    { (0x1000 + 0x9f), 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10A0, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10A1, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10A2, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10A3, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10A4, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10A5, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10A6, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10A7, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10A8, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10A9, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10AA, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10AB, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10AC, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10AD, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10AE, 0x4, 0x2, Unk_ov5_021FB17C },
    { (0x1000 + 0xaf), 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10B0, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10B1, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10B2, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10B3, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10B4, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10B5, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10B6, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10B7, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10B8, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10B9, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10BA, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10BB, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10BC, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10BD, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10BE, 0x4, 0x2, Unk_ov5_021FB17C },
    { (0x1000 + 0xbf), 0x4, 0x2, Unk_ov5_021FB17C },
    { 0x10C0, 0x4, 0x2, Unk_ov5_021FB17C },
    { 0xC1, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xC2, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xC3, 0x0, 0xC, Unk_ov5_021FB104 },
    { 0xC4, 0x0, 0xD, Unk_ov5_021FB248 },
    { 0xC5, 0x0, 0xD, Unk_ov5_021FB248 },
    { 0xC6, 0x0, 0xE, Unk_ov5_021FB11C },
    { 0xC7, 0x0, 0xE, Unk_ov5_021FB11C },
    { 0xC8, 0x0, 0xf, Unk_ov5_021FB1DC },
    { 0xC9, 0x0, 0xf, Unk_ov5_021FB1DC },
    { 0xCA, 0x7, 0x0, Unk_ov5_021FB2C0 },
    { 0xCB, 0x8, 0x0, Unk_ov5_021FB2C0 },
    { 0xCC, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xCD, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xCE, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xcf, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xD0, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xD2, 0x9, 0x1, Unk_ov5_021FB380 },
    { 0xD3, 0x9, 0x1, Unk_ov5_021FB380 },
    { 0xD4, 0xf, 0x1, Unk_ov5_021FB380 },
    { 0xD5, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xD6, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xD7, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xD8, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xD9, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xDA, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xDB, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xDC, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xDD, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xDE, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xdf, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xE0, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xE1, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xE2, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xE3, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xE4, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xE5, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xE6, 0xB, 0x15, Unk_ov5_021FB164 },
    { 0xE7, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xE8, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xE9, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xEA, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xEB, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xEC, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xED, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xEE, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xef, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xf0, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xf1, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xf2, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xf3, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xf4, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xf5, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xf6, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xf7, 0x0, 0x0, Unk_ov5_021FB2C0 },
    { 0xf8, 0xC, 0x0, Unk_ov5_021FB2C0 },
    { 0xf9, 0x10, 0x0, Unk_ov5_021FB2C0 },
    { 0xfa, 0xD, 0x0, Unk_ov5_021FB2C0 },
    { 0xfb, 0xE, 0x0, Unk_ov5_021FB2C0 },
    { 0xfc, 0x0, 0x1, Unk_ov5_021FB380 },
    { 0xfd, 0x0, 0x1, Unk_ov5_021FB380 },
    { 0xfe, 0x0, 0x1, Unk_ov5_021FB380 },
    { 0xff, 0x0, 0x1, Unk_ov5_021FB380 },
    { 0x100, 0x0, 0x16, Unk_ov5_021FB194 },
    { 0x101, 0x0, 0x16, Unk_ov5_021FB194 },
    { 0x102, 0xf, 0x6, Unk_ov5_021FB284 },
    { 0x103, 0xf, 0x6, Unk_ov5_021FB284 },
    { 0x104, 0xf, 0x4, Unk_ov5_021FB134 },
    { 0x105, 0xf, 0x4, Unk_ov5_021FB134 },
    { 0x107, 0xf, 0x1, Unk_ov5_021FB380 },
    { 0x108, 0x11, 0x8, Unk_ov5_021FB1C4 },
    { 0x109, 0x0, 0x8, Unk_ov5_021FB1C4 },
    { 0x10A, 0x0, 0x8, Unk_ov5_021FB1C4 },
    { 0x10B, 0x0, 0x8, Unk_ov5_021FB1C4 },
    { 0x10C, 0xf, 0xE, Unk_ov5_021FB11C },
    { 0x10D, 0xf, 0xE, Unk_ov5_021FB11C },
    { 0x10E, 0xf, 0xD, Unk_ov5_021FB248 },
    { 0x10f, 0xf, 0xD, Unk_ov5_021FB248 },
    { 0x110, 0x9, 0xE, Unk_ov5_021FB11C },
    { 0x111, 0x9, 0xE, Unk_ov5_021FB11C },
    { 0x112, 0x9, 0xD, Unk_ov5_021FB248 },
    { 0x113, 0x9, 0xD, Unk_ov5_021FB248 },
    { OBJ_EVENT_GFX_PKMN_BULBASAUR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BULBASAUR
    { OBJ_EVENT_GFX_PKMN_IVYSAUR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_IVYSAUR
    { OBJ_EVENT_GFX_PKMN_VENUSAUR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_VENUSAUR
    { OBJ_EVENT_GFX_PKMN_VENUSAUR_F, 0x0, 0x17, Unk_ov5_021FB2C0 },  // female
    { OBJ_EVENT_GFX_PKMN_CHARMANDER, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CHARMANDER
    { OBJ_EVENT_GFX_PKMN_CHARMELEON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CHARMELEON
    { OBJ_EVENT_GFX_PKMN_CHARIZARD, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CHARIZARD
    { OBJ_EVENT_GFX_PKMN_SQUIRTLE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SQUIRTLE
    { OBJ_EVENT_GFX_PKMN_WARTORTLE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_WARTORTLE
    { OBJ_EVENT_GFX_PKMN_BLASTOISE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BLASTOISE
    { OBJ_EVENT_GFX_PKMN_CATERPIE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CATERPIE
    { OBJ_EVENT_GFX_PKMN_METAPOD, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_METAPOD
    { OBJ_EVENT_GFX_PKMN_BUTTERFREE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BUTTERFREE
    { OBJ_EVENT_GFX_PKMN_WEEDLE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_WEEDLE
    { OBJ_EVENT_GFX_PKMN_KAKUNA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_KAKUNA
    { OBJ_EVENT_GFX_PKMN_BEEDRILL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BEEDRILL
    { OBJ_EVENT_GFX_PKMN_PIDGEY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PIDGEY
    { OBJ_EVENT_GFX_PKMN_PIDGEOTTO, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PIDGEOTTO
    { OBJ_EVENT_GFX_PKMN_PIDGEOT, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PIDGEOT
    { OBJ_EVENT_GFX_PKMN_RATTATA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_RATTATA
    { OBJ_EVENT_GFX_PKMN_RATICATE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_RATICATE
    { OBJ_EVENT_GFX_PKMN_SPEAROW, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SPEAROW
    { OBJ_EVENT_GFX_PKMN_FEAROW, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_FEAROW
    { OBJ_EVENT_GFX_PKMN_EKANS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_EKANS
    { OBJ_EVENT_GFX_PKMN_ARBOK, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARBOK
    { OBJ_EVENT_GFX_PKMN_PIKACHU, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PIKACHU
    { OBJ_EVENT_GFX_PKMN_PIKACHU_F, 0x0, 0x17, Unk_ov5_021FB2C0 },  // female
    { OBJ_EVENT_GFX_PKMN_RAICHU, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_RAICHU
    { OBJ_EVENT_GFX_PKMN_SANDSHREW, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SANDSHREW
    { OBJ_EVENT_GFX_PKMN_SANDSLASH, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SANDSLASH
    { OBJ_EVENT_GFX_PKMN_NIDORAN_F, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_NIDORAN_F
    { OBJ_EVENT_GFX_PKMN_NIDORINA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_NIDORINA
    { OBJ_EVENT_GFX_PKMN_NIDOQUEEN, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_NIDOQUEEN
    { OBJ_EVENT_GFX_PKMN_NIDORAN_M, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_NIDORAN_M
    { OBJ_EVENT_GFX_PKMN_NIDORINO, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_NIDORINO
    { OBJ_EVENT_GFX_PKMN_NIDOKING, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_NIDOKING
    { OBJ_EVENT_GFX_PKMN_CLEFAIRY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CLEFAIRY
    { OBJ_EVENT_GFX_PKMN_CLEFABLE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CLEFABLE
    { OBJ_EVENT_GFX_PKMN_VULPIX, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_VULPIX
    { OBJ_EVENT_GFX_PKMN_NINETALES, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_NINETALES
    { OBJ_EVENT_GFX_PKMN_JIGGLYPUFF, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_JIGGLYPUFF
    { OBJ_EVENT_GFX_PKMN_WIGGLYTUFF, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_WIGGLYTUFF
    { OBJ_EVENT_GFX_PKMN_ZUBAT, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ZUBAT
    { OBJ_EVENT_GFX_PKMN_GOLBAT, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GOLBAT
    { OBJ_EVENT_GFX_PKMN_ODDISH, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ODDISH
    { OBJ_EVENT_GFX_PKMN_GLOOM, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GLOOM
    { OBJ_EVENT_GFX_PKMN_VILEPLUME, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_VILEPLUME
    { OBJ_EVENT_GFX_PKMN_PARAS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PARAS
    { OBJ_EVENT_GFX_PKMN_PARASECT, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PARASECT
    { OBJ_EVENT_GFX_PKMN_VENONAT, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_VENONAT
    { OBJ_EVENT_GFX_PKMN_VENOMOTH, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_VENOMOTH
    { OBJ_EVENT_GFX_PKMN_DIGLETT, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DIGLETT
    { OBJ_EVENT_GFX_PKMN_DUGTRIO, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DUGTRIO
    { OBJ_EVENT_GFX_PKMN_MEOWTH, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MEOWTH
    { OBJ_EVENT_GFX_PKMN_PERSIAN, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PERSIAN
    { OBJ_EVENT_GFX_PKMN_PSYDUCK, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PSYDUCK
    { OBJ_EVENT_GFX_PKMN_GOLDUCK, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GOLDUCK
    { OBJ_EVENT_GFX_PKMN_MANKEY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MANKEY
    { OBJ_EVENT_GFX_PKMN_PRIMEAPE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PRIMEAPE
    { OBJ_EVENT_GFX_PKMN_GROWLITHE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GROWLITHE
    { OBJ_EVENT_GFX_PKMN_ARCANINE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARCANINE
    { OBJ_EVENT_GFX_PKMN_POLIWAG, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_POLIWAG
    { OBJ_EVENT_GFX_PKMN_POLIWHIRL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_POLIWHIRL
    { OBJ_EVENT_GFX_PKMN_POLIWRATH, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_POLIWRATH
    { OBJ_EVENT_GFX_PKMN_ABRA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ABRA
    { OBJ_EVENT_GFX_PKMN_KADABRA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_KADABRA
    { OBJ_EVENT_GFX_PKMN_ALAKAZAM, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ALAKAZAM
    { OBJ_EVENT_GFX_PKMN_MACHOP, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MACHOP
    { OBJ_EVENT_GFX_PKMN_MACHOKE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MACHOKE
    { OBJ_EVENT_GFX_PKMN_MACHAMP, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MACHAMP
    { OBJ_EVENT_GFX_PKMN_BELLSPROUT, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BELLSPROUT
    { OBJ_EVENT_GFX_PKMN_WEEPINBELL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_WEEPINBELL
    { OBJ_EVENT_GFX_PKMN_VICTREEBEL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_VICTREEBEL
    { OBJ_EVENT_GFX_PKMN_TENTACOOL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_TENTACOOL
    { OBJ_EVENT_GFX_PKMN_TENTACRUEL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_TENTACRUEL
    { OBJ_EVENT_GFX_PKMN_GEODUDE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GEODUDE
    { OBJ_EVENT_GFX_PKMN_GRAVELER, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GRAVELER
    { OBJ_EVENT_GFX_PKMN_GOLEM, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GOLEM
    { OBJ_EVENT_GFX_PKMN_PONYTA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PONYTA
    { OBJ_EVENT_GFX_PKMN_RAPIDASH, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_RAPIDASH
    { OBJ_EVENT_GFX_PKMN_SLOWPOKE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SLOWPOKE
    { OBJ_EVENT_GFX_PKMN_SLOWBRO, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SLOWBRO
    { OBJ_EVENT_GFX_PKMN_MAGNEMITE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MAGNEMITE
    { OBJ_EVENT_GFX_PKMN_MAGNETON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MAGNETON
    { OBJ_EVENT_GFX_PKMN_FARFETCHD, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_FARFETCHD
    { OBJ_EVENT_GFX_PKMN_DODUO, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DODUO
    { OBJ_EVENT_GFX_PKMN_DODRIO, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DODRIO
    { OBJ_EVENT_GFX_PKMN_SEEL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SEEL
    { OBJ_EVENT_GFX_PKMN_DEWGONG, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DEWGONG
    { OBJ_EVENT_GFX_PKMN_GRIMER, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GRIMER
    { OBJ_EVENT_GFX_PKMN_MUK, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MUK
    { OBJ_EVENT_GFX_PKMN_SHELLDER, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SHELLDER
    { OBJ_EVENT_GFX_PKMN_CLOYSTER, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CLOYSTER
    { OBJ_EVENT_GFX_PKMN_GASTLY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GASTLY
    { OBJ_EVENT_GFX_PKMN_HAUNTER, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_HAUNTER
    { OBJ_EVENT_GFX_PKMN_GENGAR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GENGAR
    { OBJ_EVENT_GFX_PKMN_ONIX, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ONIX
    { OBJ_EVENT_GFX_PKMN_DROWZEE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DROWZEE
    { OBJ_EVENT_GFX_PKMN_HYPNO, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_HYPNO
    { OBJ_EVENT_GFX_PKMN_KRABBY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_KRABBY
    { OBJ_EVENT_GFX_PKMN_KINGLER, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_KINGLER
    { OBJ_EVENT_GFX_PKMN_VOLTORB, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_VOLTORB
    { OBJ_EVENT_GFX_PKMN_ELECTRODE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ELECTRODE
    { OBJ_EVENT_GFX_PKMN_EXEGGCUTE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_EXEGGCUTE
    { OBJ_EVENT_GFX_PKMN_EXEGGUTOR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_EXEGGUTOR
    { OBJ_EVENT_GFX_PKMN_CUBONE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CUBONE
    { OBJ_EVENT_GFX_PKMN_MAROWAK, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MAROWAK
    { OBJ_EVENT_GFX_PKMN_HITMONLEE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_HITMONLEE
    { OBJ_EVENT_GFX_PKMN_HITMONCHAN, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_HITMONCHAN
    { OBJ_EVENT_GFX_PKMN_LICKITUNG, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LICKITUNG
    { OBJ_EVENT_GFX_PKMN_KOFFING, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_KOFFING
    { OBJ_EVENT_GFX_PKMN_WEEZING, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_WEEZING
    { OBJ_EVENT_GFX_PKMN_RHYHORN, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_RHYHORN
    { OBJ_EVENT_GFX_PKMN_RHYDON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_RHYDON
    { OBJ_EVENT_GFX_PKMN_CHANSEY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CHANSEY
    { OBJ_EVENT_GFX_PKMN_TANGELA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_TANGELA
    { OBJ_EVENT_GFX_PKMN_KANGASKHAN, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_KANGASKHAN
    { OBJ_EVENT_GFX_PKMN_HORSEA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_HORSEA
    { OBJ_EVENT_GFX_PKMN_SEADRA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SEADRA
    { OBJ_EVENT_GFX_PKMN_GOLDEEN, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GOLDEEN
    { OBJ_EVENT_GFX_PKMN_SEAKING, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SEAKING
    { OBJ_EVENT_GFX_PKMN_STARYU, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_STARYU
    { OBJ_EVENT_GFX_PKMN_STARMIE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_STARMIE
    { OBJ_EVENT_GFX_PKMN_MR_MIME, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MR_MIME
    { OBJ_EVENT_GFX_PKMN_SCYTHER, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SCYTHER
    { OBJ_EVENT_GFX_PKMN_JYNX, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_JYNX
    { OBJ_EVENT_GFX_PKMN_ELECTABUZZ, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ELECTABUZZ
    { OBJ_EVENT_GFX_PKMN_MAGMAR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MAGMAR
    { OBJ_EVENT_GFX_PKMN_PINSIR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PINSIR
    { OBJ_EVENT_GFX_PKMN_TAUROS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_TAUROS
    { OBJ_EVENT_GFX_PKMN_MAGIKARP, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MAGIKARP
    { OBJ_EVENT_GFX_PKMN_GYARADOS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GYARADOS
    { OBJ_EVENT_GFX_PKMN_LAPRAS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LAPRAS
    { OBJ_EVENT_GFX_PKMN_DITTO, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DITTO
    { OBJ_EVENT_GFX_PKMN_EEVEE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_EEVEE
    { OBJ_EVENT_GFX_PKMN_VAPOREON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_VAPOREON
    { OBJ_EVENT_GFX_PKMN_JOLTEON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_JOLTEON
    { OBJ_EVENT_GFX_PKMN_FLAREON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_FLAREON
    { OBJ_EVENT_GFX_PKMN_PORYGON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PORYGON
    { OBJ_EVENT_GFX_PKMN_OMANYTE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_OMANYTE
    { OBJ_EVENT_GFX_PKMN_OMASTAR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_OMASTAR
    { OBJ_EVENT_GFX_PKMN_KABUTO, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_KABUTO
    { OBJ_EVENT_GFX_PKMN_KABUTOPS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_KABUTOPS
    { OBJ_EVENT_GFX_PKMN_AERODACTYL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_AERODACTYL
    { OBJ_EVENT_GFX_PKMN_SNORLAX, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SNORLAX
    { OBJ_EVENT_GFX_PKMN_ARTICUNO, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARTICUNO
    { OBJ_EVENT_GFX_PKMN_ZAPDOS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ZAPDOS
    { OBJ_EVENT_GFX_PKMN_MOLTRES, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MOLTRES
    { OBJ_EVENT_GFX_PKMN_DRATINI, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DRATINI
    { OBJ_EVENT_GFX_PKMN_DRAGONAIR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DRAGONAIR
    { OBJ_EVENT_GFX_PKMN_DRAGONITE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DRAGONITE
    { OBJ_EVENT_GFX_PKMN_MEWTWO, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MEWTWO
    { OBJ_EVENT_GFX_PKMN_MEW, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MEW
    { OBJ_EVENT_GFX_PKMN_CHIKORITA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CHIKORITA
    { OBJ_EVENT_GFX_PKMN_BAYLEEF, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BAYLEEF
    { OBJ_EVENT_GFX_PKMN_BAYLEEF_F, 0x0, 0x17, Unk_ov5_021FB2C0 },  // female
    { OBJ_EVENT_GFX_PKMN_CYNDAQUIL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CYNDAQUIL
    { OBJ_EVENT_GFX_PKMN_QUILAVA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_QUILAVA
    { OBJ_EVENT_GFX_PKMN_TYPHLOSION, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_TYPHLOSION
    { OBJ_EVENT_GFX_PKMN_TOTODILE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_TOTODILE
    { OBJ_EVENT_GFX_PKMN_CROCONAW, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CROCONAW
    { OBJ_EVENT_GFX_PKMN_FERALIGATR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_FERALIGATR
    { OBJ_EVENT_GFX_PKMN_SENTRET, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SENTRET
    { OBJ_EVENT_GFX_PKMN_FURRET, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_FURRET
    { OBJ_EVENT_GFX_PKMN_HOOTHOOT, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_HOOTHOOT
    { OBJ_EVENT_GFX_PKMN_NOCTOWL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_NOCTOWL
    { OBJ_EVENT_GFX_PKMN_LEDYBA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LEDYBA
    { OBJ_EVENT_GFX_PKMN_LEDIAN, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LEDIAN
    { OBJ_EVENT_GFX_PKMN_SPINARAK, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SPINARAK
    { OBJ_EVENT_GFX_PKMN_ARIADOS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARIADOS
    { OBJ_EVENT_GFX_PKMN_CROBAT, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CROBAT
    { OBJ_EVENT_GFX_PKMN_CHINCHOU, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CHINCHOU
    { OBJ_EVENT_GFX_PKMN_LANTURN, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LANTURN
    { OBJ_EVENT_GFX_PKMN_PICHU, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PICHU
    { OBJ_EVENT_GFX_PKMN_CLEFFA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CLEFFA
    { OBJ_EVENT_GFX_PKMN_IGGLYBUFF, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_IGGLYBUFF
    { OBJ_EVENT_GFX_PKMN_TOGEPI, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_TOGEPI
    { OBJ_EVENT_GFX_PKMN_TOGETIC, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_TOGETIC
    { OBJ_EVENT_GFX_PKMN_NATU, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_NATU
    { OBJ_EVENT_GFX_PKMN_XATU, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_XATU
    { OBJ_EVENT_GFX_PKMN_MAREEP, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MAREEP
    { OBJ_EVENT_GFX_PKMN_FLAAFFY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_FLAAFFY
    { OBJ_EVENT_GFX_PKMN_AMPHAROS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_AMPHAROS
    { OBJ_EVENT_GFX_PKMN_BELLOSSOM, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BELLOSSOM
    { OBJ_EVENT_GFX_PKMN_MARILL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MARILL
    { OBJ_EVENT_GFX_PKMN_AZUMARILL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_AZUMARILL
    { OBJ_EVENT_GFX_PKMN_SUDOWOODO, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SUDOWOODO
    { OBJ_EVENT_GFX_PKMN_POLITOED, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_POLITOED
    { OBJ_EVENT_GFX_PKMN_HOPPIP, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_HOPPIP
    { OBJ_EVENT_GFX_PKMN_SKIPLOOM, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SKIPLOOM
    { OBJ_EVENT_GFX_PKMN_JUMPLUFF, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_JUMPLUFF
    { OBJ_EVENT_GFX_PKMN_AIPOM, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_AIPOM
    { OBJ_EVENT_GFX_PKMN_SUNKERN, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SUNKERN
    { OBJ_EVENT_GFX_PKMN_SUNFLORA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SUNFLORA
    { OBJ_EVENT_GFX_PKMN_YANMA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_YANMA
    { OBJ_EVENT_GFX_PKMN_WOOPER, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_WOOPER
    { OBJ_EVENT_GFX_PKMN_QUAGSIRE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_QUAGSIRE
    { OBJ_EVENT_GFX_PKMN_ESPEON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ESPEON
    { OBJ_EVENT_GFX_PKMN_UMBREON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_UMBREON
    { OBJ_EVENT_GFX_PKMN_MURKROW, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MURKROW
    { OBJ_EVENT_GFX_PKMN_SLOWKING, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SLOWKING
    { OBJ_EVENT_GFX_PKMN_MISDREAVUS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MISDREAVUS
    { OBJ_EVENT_GFX_PKMN_UNOWN, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_UNOWN
    { OBJ_EVENT_GFX_PKMN_WOBBUFFET, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_WOBBUFFET
    { OBJ_EVENT_GFX_PKMN_WOBBUFFET_F, 0x0, 0x17, Unk_ov5_021FB2C0 },  // female
    { OBJ_EVENT_GFX_PKMN_GIRAFARIG, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GIRAFARIG
    { OBJ_EVENT_GFX_PKMN_PINECO, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PINECO
    { OBJ_EVENT_GFX_PKMN_FORRETRESS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_FORRETRESS
    { OBJ_EVENT_GFX_PKMN_DUNSPARCE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DUNSPARCE
    { OBJ_EVENT_GFX_PKMN_GLIGAR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GLIGAR
    { OBJ_EVENT_GFX_PKMN_STEELIX, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_STEELIX
    { OBJ_EVENT_GFX_PKMN_STEELIX_F, 0x12, 0x17, Unk_ov5_021FB2C0 },  // female
    { OBJ_EVENT_GFX_PKMN_SNUBBULL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SNUBBULL
    { OBJ_EVENT_GFX_PKMN_GRANBULL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GRANBULL
    { OBJ_EVENT_GFX_PKMN_QWILFISH, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_QWILFISH
    { OBJ_EVENT_GFX_PKMN_SCIZOR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SCIZOR
    { OBJ_EVENT_GFX_PKMN_SHUCKLE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SHUCKLE
    { OBJ_EVENT_GFX_PKMN_HERACROSS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_HERACROSS
    { OBJ_EVENT_GFX_PKMN_HERACROSS_F, 0x0, 0x17, Unk_ov5_021FB2C0 },  // female
    { OBJ_EVENT_GFX_PKMN_SNEASEL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SNEASEL
    { OBJ_EVENT_GFX_PKMN_TEDDIURSA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_TEDDIURSA
    { OBJ_EVENT_GFX_PKMN_URSARING, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_URSARING
    { OBJ_EVENT_GFX_PKMN_SLUGMA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SLUGMA
    { OBJ_EVENT_GFX_PKMN_MAGCARGO, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MAGCARGO
    { OBJ_EVENT_GFX_PKMN_SWINUB, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SWINUB
    { OBJ_EVENT_GFX_PKMN_PILOSWINE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PILOSWINE
    { OBJ_EVENT_GFX_PKMN_CORSOLA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CORSOLA
    { OBJ_EVENT_GFX_PKMN_REMORAID, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_REMORAID
    { OBJ_EVENT_GFX_PKMN_OCTILLERY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_OCTILLERY
    { OBJ_EVENT_GFX_PKMN_DELIBIRD, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DELIBIRD
    { OBJ_EVENT_GFX_PKMN_MANTINE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MANTINE
    { OBJ_EVENT_GFX_PKMN_SKARMORY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SKARMORY
    { OBJ_EVENT_GFX_PKMN_HOUNDOUR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_HOUNDOUR
    { OBJ_EVENT_GFX_PKMN_HOUNDOOM, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_HOUNDOOM
    { OBJ_EVENT_GFX_PKMN_KINGDRA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_KINGDRA
    { OBJ_EVENT_GFX_PKMN_PHANPY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PHANPY
    { OBJ_EVENT_GFX_PKMN_DONPHAN, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DONPHAN
    { OBJ_EVENT_GFX_PKMN_PORYGON2, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PORYGON2
    { OBJ_EVENT_GFX_PKMN_STANTLER, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_STANTLER
    { OBJ_EVENT_GFX_PKMN_SMEARGLE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SMEARGLE
    { OBJ_EVENT_GFX_PKMN_TYROGUE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_TYROGUE
    { OBJ_EVENT_GFX_PKMN_HITMONTOP, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_HITMONTOP
    { OBJ_EVENT_GFX_PKMN_SMOOCHUM, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SMOOCHUM
    { OBJ_EVENT_GFX_PKMN_ELEKID, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ELEKID
    { OBJ_EVENT_GFX_PKMN_MAGBY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MAGBY
    { OBJ_EVENT_GFX_PKMN_MILTANK, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MILTANK
    { OBJ_EVENT_GFX_PKMN_BLISSEY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BLISSEY
    { OBJ_EVENT_GFX_PKMN_RAIKOU, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_RAIKOU
    { OBJ_EVENT_GFX_PKMN_ENTEI, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ENTEI
    { OBJ_EVENT_GFX_PKMN_SUICUNE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SUICUNE
    { OBJ_EVENT_GFX_PKMN_LARVITAR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LARVITAR
    { OBJ_EVENT_GFX_PKMN_PUPITAR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PUPITAR
    { OBJ_EVENT_GFX_PKMN_TYRANITAR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_TYRANITAR
    { OBJ_EVENT_GFX_PKMN_LUGIA, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LUGIA
    { OBJ_EVENT_GFX_PKMN_HO_OH, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_HO_OH
    { OBJ_EVENT_GFX_PKMN_CELEBI, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CELEBI
    { OBJ_EVENT_GFX_PKMN_TREECKO, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_TREECKO
    { OBJ_EVENT_GFX_PKMN_GROVYLE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GROVYLE
    { OBJ_EVENT_GFX_PKMN_SCEPTILE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SCEPTILE
    { OBJ_EVENT_GFX_PKMN_TORCHIC, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_TORCHIC
    { OBJ_EVENT_GFX_PKMN_COMBUSKEN, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_COMBUSKEN
    { OBJ_EVENT_GFX_PKMN_BLAZIKEN, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BLAZIKEN
    { OBJ_EVENT_GFX_PKMN_MUDKIP, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MUDKIP
    { OBJ_EVENT_GFX_PKMN_MARSHTOMP, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MARSHTOMP
    { OBJ_EVENT_GFX_PKMN_SWAMPERT, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SWAMPERT
    { OBJ_EVENT_GFX_PKMN_POOCHYENA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_POOCHYENA
    { OBJ_EVENT_GFX_PKMN_MIGHTYENA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MIGHTYENA
    { OBJ_EVENT_GFX_PKMN_ZIGZAGOON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ZIGZAGOON
    { OBJ_EVENT_GFX_PKMN_LINOONE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LINOONE
    { OBJ_EVENT_GFX_PKMN_WURMPLE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_WURMPLE
    { OBJ_EVENT_GFX_PKMN_SILCOON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SILCOON
    { OBJ_EVENT_GFX_PKMN_BEAUTIFLY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BEAUTIFLY
    { OBJ_EVENT_GFX_PKMN_CASCOON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CASCOON
    { OBJ_EVENT_GFX_PKMN_DUSTOX, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DUSTOX
    { OBJ_EVENT_GFX_PKMN_LOTAD, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LOTAD
    { OBJ_EVENT_GFX_PKMN_LOMBRE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LOMBRE
    { OBJ_EVENT_GFX_PKMN_LUDICOLO, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LUDICOLO
    { OBJ_EVENT_GFX_PKMN_SEEDOT, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SEEDOT
    { OBJ_EVENT_GFX_PKMN_NUZLEAF, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_NUZLEAF
    { OBJ_EVENT_GFX_PKMN_SHIFTRY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SHIFTRY
    { OBJ_EVENT_GFX_PKMN_TAILLOW, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_TAILLOW
    { OBJ_EVENT_GFX_PKMN_SWELLOW, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SWELLOW
    { OBJ_EVENT_GFX_PKMN_WINGULL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_WINGULL
    { OBJ_EVENT_GFX_PKMN_PELIPPER, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PELIPPER
    { OBJ_EVENT_GFX_PKMN_RALTS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_RALTS
    { OBJ_EVENT_GFX_PKMN_KIRLIA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_KIRLIA
    { OBJ_EVENT_GFX_PKMN_GARDEVOIR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GARDEVOIR
    { OBJ_EVENT_GFX_PKMN_SURSKIT, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SURSKIT
    { OBJ_EVENT_GFX_PKMN_MASQUERAIN, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MASQUERAIN
    { OBJ_EVENT_GFX_PKMN_SHROOMISH, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SHROOMISH
    { OBJ_EVENT_GFX_PKMN_BRELOOM, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BRELOOM
    { OBJ_EVENT_GFX_PKMN_SLAKOTH, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SLAKOTH
    { OBJ_EVENT_GFX_PKMN_VIGOROTH, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_VIGOROTH
    { OBJ_EVENT_GFX_PKMN_SLAKING, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SLAKING
    { OBJ_EVENT_GFX_PKMN_NINCADA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_NINCADA
    { OBJ_EVENT_GFX_PKMN_NINJASK, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_NINJASK
    { OBJ_EVENT_GFX_PKMN_SHEDINJA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SHEDINJA
    { OBJ_EVENT_GFX_PKMN_WHISMUR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_WHISMUR
    { OBJ_EVENT_GFX_PKMN_LOUDRED, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LOUDRED
    { OBJ_EVENT_GFX_PKMN_EXPLOUD, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_EXPLOUD
    { OBJ_EVENT_GFX_PKMN_MAKUHITA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MAKUHITA
    { OBJ_EVENT_GFX_PKMN_HARIYAMA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_HARIYAMA
    { OBJ_EVENT_GFX_PKMN_AZURILL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_AZURILL
    { OBJ_EVENT_GFX_PKMN_NOSEPASS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_NOSEPASS
    { OBJ_EVENT_GFX_PKMN_SKITTY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SKITTY
    { OBJ_EVENT_GFX_PKMN_DELCATTY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DELCATTY
    { OBJ_EVENT_GFX_PKMN_SABLEYE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SABLEYE
    { OBJ_EVENT_GFX_PKMN_MAWILE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MAWILE
    { OBJ_EVENT_GFX_PKMN_ARON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARON
    { OBJ_EVENT_GFX_PKMN_LAIRON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LAIRON
    { OBJ_EVENT_GFX_PKMN_AGGRON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_AGGRON
    { OBJ_EVENT_GFX_PKMN_MEDITITE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MEDITITE
    { OBJ_EVENT_GFX_PKMN_MEDICHAM, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MEDICHAM
    { OBJ_EVENT_GFX_PKMN_ELECTRIKE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ELECTRIKE
    { OBJ_EVENT_GFX_PKMN_MANECTRIC, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MANECTRIC
    { OBJ_EVENT_GFX_PKMN_PLUSLE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PLUSLE
    { OBJ_EVENT_GFX_PKMN_MINUN, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MINUN
    { OBJ_EVENT_GFX_PKMN_VOLBEAT, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_VOLBEAT
    { OBJ_EVENT_GFX_PKMN_ILLUMISE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ILLUMISE
    { OBJ_EVENT_GFX_PKMN_ROSELIA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ROSELIA
    { OBJ_EVENT_GFX_PKMN_GULPIN, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GULPIN
    { OBJ_EVENT_GFX_PKMN_SWALOT, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SWALOT
    { OBJ_EVENT_GFX_PKMN_CARVANHA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CARVANHA
    { OBJ_EVENT_GFX_PKMN_SHARPEDO, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SHARPEDO
    { OBJ_EVENT_GFX_PKMN_WAILMER, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_WAILMER
    { OBJ_EVENT_GFX_PKMN_WAILORD, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_WAILORD
    { OBJ_EVENT_GFX_PKMN_NUMEL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_NUMEL
    { OBJ_EVENT_GFX_PKMN_CAMERUPT, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CAMERUPT
    { OBJ_EVENT_GFX_PKMN_TORKOAL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_TORKOAL
    { OBJ_EVENT_GFX_PKMN_SPOINK, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SPOINK
    { OBJ_EVENT_GFX_PKMN_GRUMPIG, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GRUMPIG
    { OBJ_EVENT_GFX_PKMN_SPINDA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SPINDA
    { OBJ_EVENT_GFX_PKMN_TRAPINCH, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_TRAPINCH
    { OBJ_EVENT_GFX_PKMN_VIBRAVA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_VIBRAVA
    { OBJ_EVENT_GFX_PKMN_FLYGON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_FLYGON
    { OBJ_EVENT_GFX_PKMN_CACNEA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CACNEA
    { OBJ_EVENT_GFX_PKMN_CACTURNE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CACTURNE
    { OBJ_EVENT_GFX_PKMN_SWABLU, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SWABLU
    { OBJ_EVENT_GFX_PKMN_ALTARIA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ALTARIA
    { OBJ_EVENT_GFX_PKMN_ZANGOOSE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ZANGOOSE
    { OBJ_EVENT_GFX_PKMN_SEVIPER, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SEVIPER
    { OBJ_EVENT_GFX_PKMN_LUNATONE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LUNATONE
    { OBJ_EVENT_GFX_PKMN_SOLROCK, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SOLROCK
    { OBJ_EVENT_GFX_PKMN_BARBOACH, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BARBOACH
    { OBJ_EVENT_GFX_PKMN_WHISCASH, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_WHISCASH
    { OBJ_EVENT_GFX_PKMN_CORPHISH, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CORPHISH
    { OBJ_EVENT_GFX_PKMN_CRAWDAUNT, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CRAWDAUNT
    { OBJ_EVENT_GFX_PKMN_BALTOY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BALTOY
    { OBJ_EVENT_GFX_PKMN_CLAYDOL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CLAYDOL
    { OBJ_EVENT_GFX_PKMN_LILEEP, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LILEEP
    { OBJ_EVENT_GFX_PKMN_CRADILY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CRADILY
    { OBJ_EVENT_GFX_PKMN_ANORITH, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ANORITH
    { OBJ_EVENT_GFX_PKMN_ARMALDO, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARMALDO
    { OBJ_EVENT_GFX_PKMN_FEEBAS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_FEEBAS
    { OBJ_EVENT_GFX_PKMN_MILOTIC, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MILOTIC
    { OBJ_EVENT_GFX_PKMN_CASTFORM, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CASTFORM
    { OBJ_EVENT_GFX_PKMN_KECLEON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_KECLEON
    { OBJ_EVENT_GFX_PKMN_SHUPPET, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SHUPPET
    { OBJ_EVENT_GFX_PKMN_BANETTE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BANETTE
    { OBJ_EVENT_GFX_PKMN_DUSKULL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DUSKULL
    { OBJ_EVENT_GFX_PKMN_DUSCLOPS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DUSCLOPS
    { OBJ_EVENT_GFX_PKMN_TROPIUS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_TROPIUS
    { OBJ_EVENT_GFX_PKMN_CHIMECHO, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CHIMECHO
    { OBJ_EVENT_GFX_PKMN_ABSOL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ABSOL
    { OBJ_EVENT_GFX_PKMN_WYNAUT, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_WYNAUT
    { OBJ_EVENT_GFX_PKMN_SNORUNT, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SNORUNT
    { OBJ_EVENT_GFX_PKMN_GLALIE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GLALIE
    { OBJ_EVENT_GFX_PKMN_SPHEAL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SPHEAL
    { OBJ_EVENT_GFX_PKMN_SEALEO, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SEALEO
    { OBJ_EVENT_GFX_PKMN_WALREIN, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_WALREIN
    { OBJ_EVENT_GFX_PKMN_CLAMPERL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CLAMPERL
    { OBJ_EVENT_GFX_PKMN_HUNTAIL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_HUNTAIL
    { OBJ_EVENT_GFX_PKMN_GOREBYSS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GOREBYSS
    { OBJ_EVENT_GFX_PKMN_RELICANTH, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_RELICANTH
    { OBJ_EVENT_GFX_PKMN_LUVDISC, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LUVDISC
    { OBJ_EVENT_GFX_PKMN_BAGON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BAGON
    { OBJ_EVENT_GFX_PKMN_SHELGON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SHELGON
    { OBJ_EVENT_GFX_PKMN_SALAMENCE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SALAMENCE
    { OBJ_EVENT_GFX_PKMN_BELDUM, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BELDUM
    { OBJ_EVENT_GFX_PKMN_METANG, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_METANG
    { OBJ_EVENT_GFX_PKMN_METAGROSS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_METAGROSS
    { OBJ_EVENT_GFX_PKMN_REGIROCK, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_REGIROCK
    { OBJ_EVENT_GFX_PKMN_REGICE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_REGICE
    { OBJ_EVENT_GFX_PKMN_REGISTEEL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_REGISTEEL
    { OBJ_EVENT_GFX_PKMN_LATIAS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LATIAS
    { OBJ_EVENT_GFX_PKMN_LATIOS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LATIOS
    { OBJ_EVENT_GFX_PKMN_KYOGRE, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_KYOGRE
    { OBJ_EVENT_GFX_PKMN_GROUDON, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GROUDON
    { OBJ_EVENT_GFX_PKMN_RAYQUAZA, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_RAYQUAZA
    { OBJ_EVENT_GFX_PKMN_JIRACHI, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_JIRACHI
    { OBJ_EVENT_GFX_PKMN_DEOXYS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DEOXYS
    { OBJ_EVENT_GFX_PKMN_TURTWIG, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_TURTWIG
    { OBJ_EVENT_GFX_PKMN_GROTLE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GROTLE
    { OBJ_EVENT_GFX_PKMN_TORTERRA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_TORTERRA
    { OBJ_EVENT_GFX_PKMN_CHIMCHAR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CHIMCHAR
    { OBJ_EVENT_GFX_PKMN_MONFERNO, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MONFERNO
    { OBJ_EVENT_GFX_PKMN_INFERNAPE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_INFERNAPE
    { OBJ_EVENT_GFX_PKMN_PIPLUP, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PIPLUP
    { OBJ_EVENT_GFX_PKMN_PRINPLUP, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PRINPLUP
    { OBJ_EVENT_GFX_PKMN_EMPOLEON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_EMPOLEON
    { OBJ_EVENT_GFX_PKMN_STARLY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_STARLY
    { OBJ_EVENT_GFX_PKMN_STARAVIA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_STARAVIA
    { OBJ_EVENT_GFX_PKMN_STARAPTOR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_STARAPTOR
    { OBJ_EVENT_GFX_PKMN_BIDOOF, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BIDOOF
    { OBJ_EVENT_GFX_PKMN_BIBAREL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BIBAREL
    { OBJ_EVENT_GFX_PKMN_KRICKETOT, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_KRICKETOT
    { OBJ_EVENT_GFX_PKMN_KRICKETUNE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_KRICKETUNE
    { OBJ_EVENT_GFX_PKMN_SHINX, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SHINX
    { OBJ_EVENT_GFX_PKMN_LUXIO, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LUXIO
    { OBJ_EVENT_GFX_PKMN_LUXRAY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LUXRAY
    { OBJ_EVENT_GFX_PKMN_BUDEW, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BUDEW
    { OBJ_EVENT_GFX_PKMN_ROSERADE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ROSERADE
    { OBJ_EVENT_GFX_PKMN_CRANIDOS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CRANIDOS
    { OBJ_EVENT_GFX_PKMN_RAMPARDOS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_RAMPARDOS
    { OBJ_EVENT_GFX_PKMN_SHIELDON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SHIELDON
    { OBJ_EVENT_GFX_PKMN_BASTIODON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BASTIODON
    { OBJ_EVENT_GFX_PKMN_BURMY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BURMY
    { OBJ_EVENT_GFX_PKMN_WORMADAM, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_WORMADAM
    { OBJ_EVENT_GFX_PKMN_MOTHIM, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MOTHIM
    { OBJ_EVENT_GFX_PKMN_COMBEE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_COMBEE
    { OBJ_EVENT_GFX_PKMN_COMBEE_F, 0x0, 0x17, Unk_ov5_021FB2C0 },  // female
    { OBJ_EVENT_GFX_PKMN_VESPIQUEN, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_VESPIQUEN
    { OBJ_EVENT_GFX_PKMN_PACHIRISU, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PACHIRISU
    { OBJ_EVENT_GFX_PKMN_BUIZEL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BUIZEL
    { OBJ_EVENT_GFX_PKMN_FLOATZEL, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_FLOATZEL
    { OBJ_EVENT_GFX_PKMN_CHERUBI, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CHERUBI
    { OBJ_EVENT_GFX_PKMN_CHERRIM, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CHERRIM
    { OBJ_EVENT_GFX_PKMN_SHELLOS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SHELLOS
    { OBJ_EVENT_GFX_PKMN_GASTRODON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GASTRODON
    { OBJ_EVENT_GFX_PKMN_AMBIPOM, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_AMBIPOM
    { OBJ_EVENT_GFX_PKMN_DRIFLOON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DRIFLOON
    { OBJ_EVENT_GFX_PKMN_DRIFBLIM, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DRIFBLIM
    { OBJ_EVENT_GFX_PKMN_BUNEARY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BUNEARY
    { OBJ_EVENT_GFX_PKMN_LOPUNNY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LOPUNNY
    { OBJ_EVENT_GFX_PKMN_MISMAGIUS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MISMAGIUS
    { OBJ_EVENT_GFX_PKMN_HONCHKROW, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_HONCHKROW
    { OBJ_EVENT_GFX_PKMN_GLAMEOW, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GLAMEOW
    { OBJ_EVENT_GFX_PKMN_PURUGLY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PURUGLY
    { OBJ_EVENT_GFX_PKMN_CHINGLING, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CHINGLING
    { OBJ_EVENT_GFX_PKMN_STUNKY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_STUNKY
    { OBJ_EVENT_GFX_PKMN_SKUNTANK, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SKUNTANK
    { OBJ_EVENT_GFX_PKMN_BRONZOR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BRONZOR
    { OBJ_EVENT_GFX_PKMN_BRONZONG, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BRONZONG
    { OBJ_EVENT_GFX_PKMN_BONSLY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BONSLY
    { OBJ_EVENT_GFX_PKMN_MIMEJR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MIMEJR
    { OBJ_EVENT_GFX_PKMN_HAPPINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_HAPPINY
    { OBJ_EVENT_GFX_PKMN_CHATOT, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CHATOT
    { OBJ_EVENT_GFX_PKMN_SPIRITOMB, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SPIRITOMB
    { OBJ_EVENT_GFX_PKMN_GIBLE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GIBLE
    { OBJ_EVENT_GFX_PKMN_GABITE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GABITE
    { OBJ_EVENT_GFX_PKMN_GARCHOMP, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GARCHOMP
    { OBJ_EVENT_GFX_PKMN_MUNCHLAX, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MUNCHLAX
    { OBJ_EVENT_GFX_PKMN_RIOLU, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_RIOLU
    { OBJ_EVENT_GFX_PKMN_LUCARIO, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LUCARIO
    { OBJ_EVENT_GFX_PKMN_HIPPOPOTAS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_HIPPOPOTAS
    { OBJ_EVENT_GFX_PKMN_HIPPOPOTAS_F, 0x0, 0x17, Unk_ov5_021FB2C0 },  // female
    { OBJ_EVENT_GFX_PKMN_HIPPOWDON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_HIPPOWDON
    { OBJ_EVENT_GFX_PKMN_HIPPOWDON_F, 0x0, 0x17, Unk_ov5_021FB2C0 },  // female
    { OBJ_EVENT_GFX_PKMN_SKORUPI, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SKORUPI
    { OBJ_EVENT_GFX_PKMN_DRAPION, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DRAPION
    { OBJ_EVENT_GFX_PKMN_CROAGUNK, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CROAGUNK
    { OBJ_EVENT_GFX_PKMN_TOXICROAK, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_TOXICROAK
    { OBJ_EVENT_GFX_PKMN_CARNIVINE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CARNIVINE
    { OBJ_EVENT_GFX_PKMN_FINNEON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_FINNEON
    { OBJ_EVENT_GFX_PKMN_LUMINEON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LUMINEON
    { OBJ_EVENT_GFX_PKMN_MANTYKE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MANTYKE
    { OBJ_EVENT_GFX_PKMN_SNOVER, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SNOVER
    { OBJ_EVENT_GFX_PKMN_ABOMASNOW, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ABOMASNOW
    { OBJ_EVENT_GFX_PKMN_WEAVILE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_WEAVILE
    { OBJ_EVENT_GFX_PKMN_MAGNEZONE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MAGNEZONE
    { OBJ_EVENT_GFX_PKMN_LICKILICKY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LICKILICKY
    { OBJ_EVENT_GFX_PKMN_RHYPERIOR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_RHYPERIOR
    { OBJ_EVENT_GFX_PKMN_TANGROWTH, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_TANGROWTH
    { OBJ_EVENT_GFX_PKMN_ELECTIVIRE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ELECTIVIRE
    { OBJ_EVENT_GFX_PKMN_MAGMORTAR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MAGMORTAR
    { OBJ_EVENT_GFX_PKMN_TOGEKISS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_TOGEKISS
    { OBJ_EVENT_GFX_PKMN_LEAFEON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_LEAFEON
    { OBJ_EVENT_GFX_PKMN_GLACEON, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GLACEON
    { OBJ_EVENT_GFX_PKMN_GLISCOR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GLISCOR
    { OBJ_EVENT_GFX_PKMN_MAMOSWINE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MAMOSWINE
    { OBJ_EVENT_GFX_PKMN_PORYGON_Z, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PORYGON_Z
    { OBJ_EVENT_GFX_PKMN_GALLADE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GALLADE
    { OBJ_EVENT_GFX_PKMN_PROBOPASS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PROBOPASS
    { OBJ_EVENT_GFX_PKMN_DUSKNOIR, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DUSKNOIR
    { OBJ_EVENT_GFX_PKMN_FROSLASS, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_FROSLASS
    { OBJ_EVENT_GFX_PKMN_ROTOM, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ROTOM
    { OBJ_EVENT_GFX_PKMN_UXIE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_UXIE
    { OBJ_EVENT_GFX_PKMN_MESPRIT, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MESPRIT
    { OBJ_EVENT_GFX_PKMN_AZELF, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_AZELF
    { OBJ_EVENT_GFX_PKMN_DIALGA, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DIALGA
    { OBJ_EVENT_GFX_PKMN_PALKIA, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PALKIA
    { OBJ_EVENT_GFX_PKMN_HEATRAN, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_HEATRAN
    { OBJ_EVENT_GFX_PKMN_REGIGIGAS, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_REGIGIGAS
    { OBJ_EVENT_GFX_PKMN_GIRATINA, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GIRATINA
    { OBJ_EVENT_GFX_PKMN_CRESSELIA, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_CRESSELIA
    { OBJ_EVENT_GFX_PKMN_PHIONE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_PHIONE
    { OBJ_EVENT_GFX_PKMN_MANAPHY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_MANAPHY
    { OBJ_EVENT_GFX_PKMN_DARKRAI, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DARKRAI
    { OBJ_EVENT_GFX_PKMN_SHAYMIN, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SHAYMIN
    { OBJ_EVENT_GFX_PKMN_ARCEUS, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARCEUS
    { OBJ_EVENT_GFX_PKMN_GIRATINA_O, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GIRATINA origin form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FIGHTING, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARCEUS fighting type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FLYING, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARCEUS flying type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_POISON, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARCEUS poison type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GROUND, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARCEUS ground type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ROCK, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARCEUS rock type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_BUG, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARCEUS bug type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GHOST, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARCEUS ghost type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_STEEL, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARCEUS steel type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FAIRY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARCEUS fairy type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FIRE, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARCEUS fire type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_WATER, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARCEUS water type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GRASS, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARCEUS grass type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ELECTRIC, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARCEUS electric type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_PSYCHIC, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARCEUS psychic type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ICE, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARCEUS ice type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_DRAGON, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARCEUS dragon type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_DARK, 0x12, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ARCEUS dark type
    { OBJ_EVENT_GFX_PKMN_DEOXYS_ATTACK, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DEOXYS attack form
    { OBJ_EVENT_GFX_PKMN_DEOXYS_DEFENSE, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DEOXYS defense form
    { OBJ_EVENT_GFX_PKMN_DEOXYS_SPEED, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_DEOXYS speed form
    { OBJ_EVENT_GFX_PKMN_BURMY_SANDY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BURMY sandy cloak
    { OBJ_EVENT_GFX_PKMN_BURMY_TRASH, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_BURMY trash cloak
    { OBJ_EVENT_GFX_PKMN_WORMADAM_SANDY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_WORMADAM sandy cloak
    { OBJ_EVENT_GFX_PKMN_WORMADAM_TRASH, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_WORMADAM trash cloak
    { OBJ_EVENT_GFX_PKMN_SHELLOS_EAST, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SHELLOS east sea
    { OBJ_EVENT_GFX_PKMN_GASTRODON_EAST, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_GASTRODON east sea
    { OBJ_EVENT_GFX_PKMN_ROTOM_HEAT, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ROTOM heat
    { OBJ_EVENT_GFX_PKMN_ROTOM_WASH, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ROTOM wash
    { OBJ_EVENT_GFX_PKMN_ROTOM_FROST, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ROTOM frost
    { OBJ_EVENT_GFX_PKMN_ROTOM_FAN, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ROTOM fan
    { OBJ_EVENT_GFX_PKMN_ROTOM_MOW, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_ROTOM mow
    { OBJ_EVENT_GFX_PKMN_SHAYMIN_SKY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // SPECIES_SHAYMIN sky form
    { OBJ_EVENT_GFX_PKMN_BULBASAUR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BULBASAUR
    { OBJ_EVENT_GFX_PKMN_IVYSAUR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_IVYSAUR
    { OBJ_EVENT_GFX_PKMN_VENUSAUR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_VENUSAUR
    { OBJ_EVENT_GFX_PKMN_VENUSAUR_F_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_CHARMANDER_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CHARMANDER
    { OBJ_EVENT_GFX_PKMN_CHARMELEON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CHARMELEON
    { OBJ_EVENT_GFX_PKMN_CHARIZARD_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CHARIZARD
    { OBJ_EVENT_GFX_PKMN_SQUIRTLE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SQUIRTLE
    { OBJ_EVENT_GFX_PKMN_WARTORTLE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_WARTORTLE
    { OBJ_EVENT_GFX_PKMN_BLASTOISE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BLASTOISE
    { OBJ_EVENT_GFX_PKMN_CATERPIE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CATERPIE
    { OBJ_EVENT_GFX_PKMN_METAPOD_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_METAPOD
    { OBJ_EVENT_GFX_PKMN_BUTTERFREE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BUTTERFREE
    { OBJ_EVENT_GFX_PKMN_WEEDLE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_WEEDLE
    { OBJ_EVENT_GFX_PKMN_KAKUNA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_KAKUNA
    { OBJ_EVENT_GFX_PKMN_BEEDRILL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BEEDRILL
    { OBJ_EVENT_GFX_PKMN_PIDGEY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PIDGEY
    { OBJ_EVENT_GFX_PKMN_PIDGEOTTO_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PIDGEOTTO
    { OBJ_EVENT_GFX_PKMN_PIDGEOT_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PIDGEOT
    { OBJ_EVENT_GFX_PKMN_RATTATA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_RATTATA
    { OBJ_EVENT_GFX_PKMN_RATICATE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_RATICATE
    { OBJ_EVENT_GFX_PKMN_SPEAROW_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SPEAROW
    { OBJ_EVENT_GFX_PKMN_FEAROW_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_FEAROW
    { OBJ_EVENT_GFX_PKMN_EKANS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_EKANS
    { OBJ_EVENT_GFX_PKMN_ARBOK_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ARBOK
    { OBJ_EVENT_GFX_PKMN_PIKACHU_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PIKACHU
    { OBJ_EVENT_GFX_PKMN_PIKACHU_F_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_RAICHU_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_RAICHU
    { OBJ_EVENT_GFX_PKMN_SANDSHREW_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SANDSHREW
    { OBJ_EVENT_GFX_PKMN_SANDSLASH_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SANDSLASH
    { OBJ_EVENT_GFX_PKMN_NIDORAN_F_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_NIDORAN_F
    { OBJ_EVENT_GFX_PKMN_NIDORINA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_NIDORINA
    { OBJ_EVENT_GFX_PKMN_NIDOQUEEN_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_NIDOQUEEN
    { OBJ_EVENT_GFX_PKMN_NIDORAN_M_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_NIDORAN_M
    { OBJ_EVENT_GFX_PKMN_NIDORINO_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_NIDORINO
    { OBJ_EVENT_GFX_PKMN_NIDOKING_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_NIDOKING
    { OBJ_EVENT_GFX_PKMN_CLEFAIRY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CLEFAIRY
    { OBJ_EVENT_GFX_PKMN_CLEFABLE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CLEFABLE
    { OBJ_EVENT_GFX_PKMN_VULPIX_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_VULPIX
    { OBJ_EVENT_GFX_PKMN_NINETALES_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_NINETALES
    { OBJ_EVENT_GFX_PKMN_JIGGLYPUFF_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_JIGGLYPUFF
    { OBJ_EVENT_GFX_PKMN_WIGGLYTUFF_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_WIGGLYTUFF
    { OBJ_EVENT_GFX_PKMN_ZUBAT_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ZUBAT
    { OBJ_EVENT_GFX_PKMN_GOLBAT_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GOLBAT
    { OBJ_EVENT_GFX_PKMN_ODDISH_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ODDISH
    { OBJ_EVENT_GFX_PKMN_GLOOM_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GLOOM
    { OBJ_EVENT_GFX_PKMN_VILEPLUME_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_VILEPLUME
    { OBJ_EVENT_GFX_PKMN_PARAS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PARAS
    { OBJ_EVENT_GFX_PKMN_PARASECT_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PARASECT
    { OBJ_EVENT_GFX_PKMN_VENONAT_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_VENONAT
    { OBJ_EVENT_GFX_PKMN_VENOMOTH_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_VENOMOTH
    { OBJ_EVENT_GFX_PKMN_DIGLETT_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DIGLETT
    { OBJ_EVENT_GFX_PKMN_DUGTRIO_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DUGTRIO
    { OBJ_EVENT_GFX_PKMN_MEOWTH_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MEOWTH
    { OBJ_EVENT_GFX_PKMN_PERSIAN_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PERSIAN
    { OBJ_EVENT_GFX_PKMN_PSYDUCK_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PSYDUCK
    { OBJ_EVENT_GFX_PKMN_GOLDUCK_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GOLDUCK
    { OBJ_EVENT_GFX_PKMN_MANKEY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MANKEY
    { OBJ_EVENT_GFX_PKMN_PRIMEAPE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PRIMEAPE
    { OBJ_EVENT_GFX_PKMN_GROWLITHE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GROWLITHE
    { OBJ_EVENT_GFX_PKMN_ARCANINE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ARCANINE
    { OBJ_EVENT_GFX_PKMN_POLIWAG_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_POLIWAG
    { OBJ_EVENT_GFX_PKMN_POLIWHIRL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_POLIWHIRL
    { OBJ_EVENT_GFX_PKMN_POLIWRATH_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_POLIWRATH
    { OBJ_EVENT_GFX_PKMN_ABRA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ABRA
    { OBJ_EVENT_GFX_PKMN_KADABRA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_KADABRA
    { OBJ_EVENT_GFX_PKMN_ALAKAZAM_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ALAKAZAM
    { OBJ_EVENT_GFX_PKMN_MACHOP_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MACHOP
    { OBJ_EVENT_GFX_PKMN_MACHOKE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MACHOKE
    { OBJ_EVENT_GFX_PKMN_MACHAMP_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MACHAMP
    { OBJ_EVENT_GFX_PKMN_BELLSPROUT_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BELLSPROUT
    { OBJ_EVENT_GFX_PKMN_WEEPINBELL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_WEEPINBELL
    { OBJ_EVENT_GFX_PKMN_VICTREEBEL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_VICTREEBEL
    { OBJ_EVENT_GFX_PKMN_TENTACOOL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_TENTACOOL
    { OBJ_EVENT_GFX_PKMN_TENTACRUEL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_TENTACRUEL
    { OBJ_EVENT_GFX_PKMN_GEODUDE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GEODUDE
    { OBJ_EVENT_GFX_PKMN_GRAVELER_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GRAVELER
    { OBJ_EVENT_GFX_PKMN_GOLEM_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GOLEM
    { OBJ_EVENT_GFX_PKMN_PONYTA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PONYTA
    { OBJ_EVENT_GFX_PKMN_RAPIDASH_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_RAPIDASH
    { OBJ_EVENT_GFX_PKMN_SLOWPOKE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SLOWPOKE
    { OBJ_EVENT_GFX_PKMN_SLOWBRO_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SLOWBRO
    { OBJ_EVENT_GFX_PKMN_MAGNEMITE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MAGNEMITE
    { OBJ_EVENT_GFX_PKMN_MAGNETON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MAGNETON
    { OBJ_EVENT_GFX_PKMN_FARFETCHD_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_FARFETCHD
    { OBJ_EVENT_GFX_PKMN_DODUO_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DODUO
    { OBJ_EVENT_GFX_PKMN_DODRIO_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DODRIO
    { OBJ_EVENT_GFX_PKMN_SEEL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SEEL
    { OBJ_EVENT_GFX_PKMN_DEWGONG_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DEWGONG
    { OBJ_EVENT_GFX_PKMN_GRIMER_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GRIMER
    { OBJ_EVENT_GFX_PKMN_MUK_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MUK
    { OBJ_EVENT_GFX_PKMN_SHELLDER_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SHELLDER
    { OBJ_EVENT_GFX_PKMN_CLOYSTER_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CLOYSTER
    { OBJ_EVENT_GFX_PKMN_GASTLY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GASTLY
    { OBJ_EVENT_GFX_PKMN_HAUNTER_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_HAUNTER
    { OBJ_EVENT_GFX_PKMN_GENGAR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GENGAR
    { OBJ_EVENT_GFX_PKMN_ONIX_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ONIX
    { OBJ_EVENT_GFX_PKMN_DROWZEE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DROWZEE
    { OBJ_EVENT_GFX_PKMN_HYPNO_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_HYPNO
    { OBJ_EVENT_GFX_PKMN_KRABBY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_KRABBY
    { OBJ_EVENT_GFX_PKMN_KINGLER_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_KINGLER
    { OBJ_EVENT_GFX_PKMN_VOLTORB_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_VOLTORB
    { OBJ_EVENT_GFX_PKMN_ELECTRODE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ELECTRODE
    { OBJ_EVENT_GFX_PKMN_EXEGGCUTE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_EXEGGCUTE
    { OBJ_EVENT_GFX_PKMN_EXEGGUTOR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_EXEGGUTOR
    { OBJ_EVENT_GFX_PKMN_CUBONE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CUBONE
    { OBJ_EVENT_GFX_PKMN_MAROWAK_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MAROWAK
    { OBJ_EVENT_GFX_PKMN_HITMONLEE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_HITMONLEE
    { OBJ_EVENT_GFX_PKMN_HITMONCHAN_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_HITMONCHAN
    { OBJ_EVENT_GFX_PKMN_LICKITUNG_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LICKITUNG
    { OBJ_EVENT_GFX_PKMN_KOFFING_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_KOFFING
    { OBJ_EVENT_GFX_PKMN_WEEZING_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_WEEZING
    { OBJ_EVENT_GFX_PKMN_RHYHORN_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_RHYHORN
    { OBJ_EVENT_GFX_PKMN_RHYDON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_RHYDON
    { OBJ_EVENT_GFX_PKMN_CHANSEY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CHANSEY
    { OBJ_EVENT_GFX_PKMN_TANGELA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_TANGELA
    { OBJ_EVENT_GFX_PKMN_KANGASKHAN_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_KANGASKHAN
    { OBJ_EVENT_GFX_PKMN_HORSEA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_HORSEA
    { OBJ_EVENT_GFX_PKMN_SEADRA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SEADRA
    { OBJ_EVENT_GFX_PKMN_GOLDEEN_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GOLDEEN
    { OBJ_EVENT_GFX_PKMN_SEAKING_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SEAKING
    { OBJ_EVENT_GFX_PKMN_STARYU_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_STARYU
    { OBJ_EVENT_GFX_PKMN_STARMIE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_STARMIE
    { OBJ_EVENT_GFX_PKMN_MR_MIME_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MR_MIME
    { OBJ_EVENT_GFX_PKMN_SCYTHER_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SCYTHER
    { OBJ_EVENT_GFX_PKMN_JYNX_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_JYNX
    { OBJ_EVENT_GFX_PKMN_ELECTABUZZ_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ELECTABUZZ
    { OBJ_EVENT_GFX_PKMN_MAGMAR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MAGMAR
    { OBJ_EVENT_GFX_PKMN_PINSIR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PINSIR
    { OBJ_EVENT_GFX_PKMN_TAUROS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_TAUROS
    { OBJ_EVENT_GFX_PKMN_MAGIKARP_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MAGIKARP
    { OBJ_EVENT_GFX_PKMN_GYARADOS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GYARADOS
    { OBJ_EVENT_GFX_PKMN_LAPRAS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LAPRAS
    { OBJ_EVENT_GFX_PKMN_DITTO_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DITTO
    { OBJ_EVENT_GFX_PKMN_EEVEE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_EEVEE
    { OBJ_EVENT_GFX_PKMN_VAPOREON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_VAPOREON
    { OBJ_EVENT_GFX_PKMN_JOLTEON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_JOLTEON
    { OBJ_EVENT_GFX_PKMN_FLAREON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_FLAREON
    { OBJ_EVENT_GFX_PKMN_PORYGON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PORYGON
    { OBJ_EVENT_GFX_PKMN_OMANYTE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_OMANYTE
    { OBJ_EVENT_GFX_PKMN_OMASTAR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_OMASTAR
    { OBJ_EVENT_GFX_PKMN_KABUTO_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_KABUTO
    { OBJ_EVENT_GFX_PKMN_KABUTOPS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_KABUTOPS
    { OBJ_EVENT_GFX_PKMN_AERODACTYL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_AERODACTYL
    { OBJ_EVENT_GFX_PKMN_SNORLAX_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SNORLAX
    { OBJ_EVENT_GFX_PKMN_ARTICUNO_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ARTICUNO
    { OBJ_EVENT_GFX_PKMN_ZAPDOS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ZAPDOS
    { OBJ_EVENT_GFX_PKMN_MOLTRES_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MOLTRES
    { OBJ_EVENT_GFX_PKMN_DRATINI_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DRATINI
    { OBJ_EVENT_GFX_PKMN_DRAGONAIR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DRAGONAIR
    { OBJ_EVENT_GFX_PKMN_DRAGONITE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DRAGONITE
    { OBJ_EVENT_GFX_PKMN_MEWTWO_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MEWTWO
    { OBJ_EVENT_GFX_PKMN_MEW_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MEW
    { OBJ_EVENT_GFX_PKMN_CHIKORITA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CHIKORITA
    { OBJ_EVENT_GFX_PKMN_BAYLEEF_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BAYLEEF
    { OBJ_EVENT_GFX_PKMN_BAYLEEF_F_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_CYNDAQUIL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CYNDAQUIL
    { OBJ_EVENT_GFX_PKMN_QUILAVA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_QUILAVA
    { OBJ_EVENT_GFX_PKMN_TYPHLOSION_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_TYPHLOSION
    { OBJ_EVENT_GFX_PKMN_TOTODILE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_TOTODILE
    { OBJ_EVENT_GFX_PKMN_CROCONAW_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CROCONAW
    { OBJ_EVENT_GFX_PKMN_FERALIGATR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_FERALIGATR
    { OBJ_EVENT_GFX_PKMN_SENTRET_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SENTRET
    { OBJ_EVENT_GFX_PKMN_FURRET_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_FURRET
    { OBJ_EVENT_GFX_PKMN_HOOTHOOT_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_HOOTHOOT
    { OBJ_EVENT_GFX_PKMN_NOCTOWL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_NOCTOWL
    { OBJ_EVENT_GFX_PKMN_LEDYBA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LEDYBA
    { OBJ_EVENT_GFX_PKMN_LEDIAN_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LEDIAN
    { OBJ_EVENT_GFX_PKMN_SPINARAK_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SPINARAK
    { OBJ_EVENT_GFX_PKMN_ARIADOS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ARIADOS
    { OBJ_EVENT_GFX_PKMN_CROBAT_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CROBAT
    { OBJ_EVENT_GFX_PKMN_CHINCHOU_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CHINCHOU
    { OBJ_EVENT_GFX_PKMN_LANTURN_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LANTURN
    { OBJ_EVENT_GFX_PKMN_PICHU_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PICHU
    { OBJ_EVENT_GFX_PKMN_CLEFFA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CLEFFA
    { OBJ_EVENT_GFX_PKMN_IGGLYBUFF_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_IGGLYBUFF
    { OBJ_EVENT_GFX_PKMN_TOGEPI_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_TOGEPI
    { OBJ_EVENT_GFX_PKMN_TOGETIC_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_TOGETIC
    { OBJ_EVENT_GFX_PKMN_NATU_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_NATU
    { OBJ_EVENT_GFX_PKMN_XATU_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_XATU
    { OBJ_EVENT_GFX_PKMN_MAREEP_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MAREEP
    { OBJ_EVENT_GFX_PKMN_FLAAFFY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_FLAAFFY
    { OBJ_EVENT_GFX_PKMN_AMPHAROS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_AMPHAROS
    { OBJ_EVENT_GFX_PKMN_BELLOSSOM_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BELLOSSOM
    { OBJ_EVENT_GFX_PKMN_MARILL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MARILL
    { OBJ_EVENT_GFX_PKMN_AZUMARILL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_AZUMARILL
    { OBJ_EVENT_GFX_PKMN_SUDOWOODO_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SUDOWOODO
    { OBJ_EVENT_GFX_PKMN_POLITOED_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_POLITOED
    { OBJ_EVENT_GFX_PKMN_HOPPIP_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_HOPPIP
    { OBJ_EVENT_GFX_PKMN_SKIPLOOM_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SKIPLOOM
    { OBJ_EVENT_GFX_PKMN_JUMPLUFF_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_JUMPLUFF
    { OBJ_EVENT_GFX_PKMN_AIPOM_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_AIPOM
    { OBJ_EVENT_GFX_PKMN_SUNKERN_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SUNKERN
    { OBJ_EVENT_GFX_PKMN_SUNFLORA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SUNFLORA
    { OBJ_EVENT_GFX_PKMN_YANMA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_YANMA
    { OBJ_EVENT_GFX_PKMN_WOOPER_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_WOOPER
    { OBJ_EVENT_GFX_PKMN_QUAGSIRE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_QUAGSIRE
    { OBJ_EVENT_GFX_PKMN_ESPEON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ESPEON
    { OBJ_EVENT_GFX_PKMN_UMBREON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_UMBREON
    { OBJ_EVENT_GFX_PKMN_MURKROW_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MURKROW
    { OBJ_EVENT_GFX_PKMN_SLOWKING_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SLOWKING
    { OBJ_EVENT_GFX_PKMN_MISDREAVUS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MISDREAVUS
    { OBJ_EVENT_GFX_PKMN_UNOWN_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_UNOWN
    { OBJ_EVENT_GFX_PKMN_WOBBUFFET_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_WOBBUFFET
    { OBJ_EVENT_GFX_PKMN_WOBBUFFET_F_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_GIRAFARIG_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GIRAFARIG
    { OBJ_EVENT_GFX_PKMN_PINECO_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PINECO
    { OBJ_EVENT_GFX_PKMN_FORRETRESS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_FORRETRESS
    { OBJ_EVENT_GFX_PKMN_DUNSPARCE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DUNSPARCE
    { OBJ_EVENT_GFX_PKMN_GLIGAR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GLIGAR
    { OBJ_EVENT_GFX_PKMN_STEELIX_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_STEELIX
    { OBJ_EVENT_GFX_PKMN_STEELIX_F_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_SNUBBULL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SNUBBULL
    { OBJ_EVENT_GFX_PKMN_GRANBULL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GRANBULL
    { OBJ_EVENT_GFX_PKMN_QWILFISH_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_QWILFISH
    { OBJ_EVENT_GFX_PKMN_SCIZOR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SCIZOR
    { OBJ_EVENT_GFX_PKMN_SHUCKLE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SHUCKLE
    { OBJ_EVENT_GFX_PKMN_HERACROSS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_HERACROSS
    { OBJ_EVENT_GFX_PKMN_HERACROSS_F_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_SNEASEL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SNEASEL
    { OBJ_EVENT_GFX_PKMN_TEDDIURSA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_TEDDIURSA
    { OBJ_EVENT_GFX_PKMN_URSARING_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_URSARING
    { OBJ_EVENT_GFX_PKMN_SLUGMA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SLUGMA
    { OBJ_EVENT_GFX_PKMN_MAGCARGO_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MAGCARGO
    { OBJ_EVENT_GFX_PKMN_SWINUB_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SWINUB
    { OBJ_EVENT_GFX_PKMN_PILOSWINE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PILOSWINE
    { OBJ_EVENT_GFX_PKMN_CORSOLA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CORSOLA
    { OBJ_EVENT_GFX_PKMN_REMORAID_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_REMORAID
    { OBJ_EVENT_GFX_PKMN_OCTILLERY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_OCTILLERY
    { OBJ_EVENT_GFX_PKMN_DELIBIRD_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DELIBIRD
    { OBJ_EVENT_GFX_PKMN_MANTINE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MANTINE
    { OBJ_EVENT_GFX_PKMN_SKARMORY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SKARMORY
    { OBJ_EVENT_GFX_PKMN_HOUNDOUR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_HOUNDOUR
    { OBJ_EVENT_GFX_PKMN_HOUNDOOM_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_HOUNDOOM
    { OBJ_EVENT_GFX_PKMN_KINGDRA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_KINGDRA
    { OBJ_EVENT_GFX_PKMN_PHANPY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PHANPY
    { OBJ_EVENT_GFX_PKMN_DONPHAN_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DONPHAN
    { OBJ_EVENT_GFX_PKMN_PORYGON2_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PORYGON2
    { OBJ_EVENT_GFX_PKMN_STANTLER_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_STANTLER
    { OBJ_EVENT_GFX_PKMN_SMEARGLE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SMEARGLE
    { OBJ_EVENT_GFX_PKMN_TYROGUE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_TYROGUE
    { OBJ_EVENT_GFX_PKMN_HITMONTOP_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_HITMONTOP
    { OBJ_EVENT_GFX_PKMN_SMOOCHUM_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SMOOCHUM
    { OBJ_EVENT_GFX_PKMN_ELEKID_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ELEKID
    { OBJ_EVENT_GFX_PKMN_MAGBY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MAGBY
    { OBJ_EVENT_GFX_PKMN_MILTANK_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MILTANK
    { OBJ_EVENT_GFX_PKMN_BLISSEY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BLISSEY
    { OBJ_EVENT_GFX_PKMN_RAIKOU_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_RAIKOU
    { OBJ_EVENT_GFX_PKMN_ENTEI_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ENTEI
    { OBJ_EVENT_GFX_PKMN_SUICUNE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SUICUNE
    { OBJ_EVENT_GFX_PKMN_LARVITAR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LARVITAR
    { OBJ_EVENT_GFX_PKMN_PUPITAR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PUPITAR
    { OBJ_EVENT_GFX_PKMN_TYRANITAR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_TYRANITAR
    { OBJ_EVENT_GFX_PKMN_LUGIA_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LUGIA
    { OBJ_EVENT_GFX_PKMN_HO_OH_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_HO_OH
    { OBJ_EVENT_GFX_PKMN_CELEBI_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CELEBI
    { OBJ_EVENT_GFX_PKMN_TREECKO_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_TREECKO
    { OBJ_EVENT_GFX_PKMN_GROVYLE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GROVYLE
    { OBJ_EVENT_GFX_PKMN_SCEPTILE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SCEPTILE
    { OBJ_EVENT_GFX_PKMN_TORCHIC_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_TORCHIC
    { OBJ_EVENT_GFX_PKMN_COMBUSKEN_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_COMBUSKEN
    { OBJ_EVENT_GFX_PKMN_BLAZIKEN_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BLAZIKEN
    { OBJ_EVENT_GFX_PKMN_MUDKIP_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MUDKIP
    { OBJ_EVENT_GFX_PKMN_MARSHTOMP_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MARSHTOMP
    { OBJ_EVENT_GFX_PKMN_SWAMPERT_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SWAMPERT
    { OBJ_EVENT_GFX_PKMN_POOCHYENA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_POOCHYENA
    { OBJ_EVENT_GFX_PKMN_MIGHTYENA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MIGHTYENA
    { OBJ_EVENT_GFX_PKMN_ZIGZAGOON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ZIGZAGOON
    { OBJ_EVENT_GFX_PKMN_LINOONE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LINOONE
    { OBJ_EVENT_GFX_PKMN_WURMPLE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_WURMPLE
    { OBJ_EVENT_GFX_PKMN_SILCOON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SILCOON
    { OBJ_EVENT_GFX_PKMN_BEAUTIFLY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BEAUTIFLY
    { OBJ_EVENT_GFX_PKMN_CASCOON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CASCOON
    { OBJ_EVENT_GFX_PKMN_DUSTOX_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DUSTOX
    { OBJ_EVENT_GFX_PKMN_LOTAD_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LOTAD
    { OBJ_EVENT_GFX_PKMN_LOMBRE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LOMBRE
    { OBJ_EVENT_GFX_PKMN_LUDICOLO_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LUDICOLO
    { OBJ_EVENT_GFX_PKMN_SEEDOT_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SEEDOT
    { OBJ_EVENT_GFX_PKMN_NUZLEAF_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_NUZLEAF
    { OBJ_EVENT_GFX_PKMN_SHIFTRY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SHIFTRY
    { OBJ_EVENT_GFX_PKMN_TAILLOW_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_TAILLOW
    { OBJ_EVENT_GFX_PKMN_SWELLOW_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SWELLOW
    { OBJ_EVENT_GFX_PKMN_WINGULL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_WINGULL
    { OBJ_EVENT_GFX_PKMN_PELIPPER_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PELIPPER
    { OBJ_EVENT_GFX_PKMN_RALTS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_RALTS
    { OBJ_EVENT_GFX_PKMN_KIRLIA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_KIRLIA
    { OBJ_EVENT_GFX_PKMN_GARDEVOIR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GARDEVOIR
    { OBJ_EVENT_GFX_PKMN_SURSKIT_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SURSKIT
    { OBJ_EVENT_GFX_PKMN_MASQUERAIN_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MASQUERAIN
    { OBJ_EVENT_GFX_PKMN_SHROOMISH_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SHROOMISH
    { OBJ_EVENT_GFX_PKMN_BRELOOM_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BRELOOM
    { OBJ_EVENT_GFX_PKMN_SLAKOTH_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SLAKOTH
    { OBJ_EVENT_GFX_PKMN_VIGOROTH_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_VIGOROTH
    { OBJ_EVENT_GFX_PKMN_SLAKING_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SLAKING
    { OBJ_EVENT_GFX_PKMN_NINCADA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_NINCADA
    { OBJ_EVENT_GFX_PKMN_NINJASK_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_NINJASK
    { OBJ_EVENT_GFX_PKMN_SHEDINJA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SHEDINJA
    { OBJ_EVENT_GFX_PKMN_WHISMUR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_WHISMUR
    { OBJ_EVENT_GFX_PKMN_LOUDRED_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LOUDRED
    { OBJ_EVENT_GFX_PKMN_EXPLOUD_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_EXPLOUD
    { OBJ_EVENT_GFX_PKMN_MAKUHITA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MAKUHITA
    { OBJ_EVENT_GFX_PKMN_HARIYAMA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_HARIYAMA
    { OBJ_EVENT_GFX_PKMN_AZURILL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_AZURILL
    { OBJ_EVENT_GFX_PKMN_NOSEPASS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_NOSEPASS
    { OBJ_EVENT_GFX_PKMN_SKITTY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SKITTY
    { OBJ_EVENT_GFX_PKMN_DELCATTY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DELCATTY
    { OBJ_EVENT_GFX_PKMN_SABLEYE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SABLEYE
    { OBJ_EVENT_GFX_PKMN_MAWILE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MAWILE
    { OBJ_EVENT_GFX_PKMN_ARON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ARON
    { OBJ_EVENT_GFX_PKMN_LAIRON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LAIRON
    { OBJ_EVENT_GFX_PKMN_AGGRON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_AGGRON
    { OBJ_EVENT_GFX_PKMN_MEDITITE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MEDITITE
    { OBJ_EVENT_GFX_PKMN_MEDICHAM_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MEDICHAM
    { OBJ_EVENT_GFX_PKMN_ELECTRIKE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ELECTRIKE
    { OBJ_EVENT_GFX_PKMN_MANECTRIC_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MANECTRIC
    { OBJ_EVENT_GFX_PKMN_PLUSLE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PLUSLE
    { OBJ_EVENT_GFX_PKMN_MINUN_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MINUN
    { OBJ_EVENT_GFX_PKMN_VOLBEAT_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_VOLBEAT
    { OBJ_EVENT_GFX_PKMN_ILLUMISE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ILLUMISE
    { OBJ_EVENT_GFX_PKMN_ROSELIA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ROSELIA
    { OBJ_EVENT_GFX_PKMN_GULPIN_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GULPIN
    { OBJ_EVENT_GFX_PKMN_SWALOT_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SWALOT
    { OBJ_EVENT_GFX_PKMN_CARVANHA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CARVANHA
    { OBJ_EVENT_GFX_PKMN_SHARPEDO_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SHARPEDO
    { OBJ_EVENT_GFX_PKMN_WAILMER_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_WAILMER
    { OBJ_EVENT_GFX_PKMN_WAILORD_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_WAILORD
    { OBJ_EVENT_GFX_PKMN_NUMEL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_NUMEL
    { OBJ_EVENT_GFX_PKMN_CAMERUPT_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CAMERUPT
    { OBJ_EVENT_GFX_PKMN_TORKOAL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_TORKOAL
    { OBJ_EVENT_GFX_PKMN_SPOINK_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SPOINK
    { OBJ_EVENT_GFX_PKMN_GRUMPIG_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GRUMPIG
    { OBJ_EVENT_GFX_PKMN_SPINDA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SPINDA
    { OBJ_EVENT_GFX_PKMN_TRAPINCH_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_TRAPINCH
    { OBJ_EVENT_GFX_PKMN_VIBRAVA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_VIBRAVA
    { OBJ_EVENT_GFX_PKMN_FLYGON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_FLYGON
    { OBJ_EVENT_GFX_PKMN_CACNEA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CACNEA
    { OBJ_EVENT_GFX_PKMN_CACTURNE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CACTURNE
    { OBJ_EVENT_GFX_PKMN_SWABLU_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SWABLU
    { OBJ_EVENT_GFX_PKMN_ALTARIA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ALTARIA
    { OBJ_EVENT_GFX_PKMN_ZANGOOSE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ZANGOOSE
    { OBJ_EVENT_GFX_PKMN_SEVIPER_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SEVIPER
    { OBJ_EVENT_GFX_PKMN_LUNATONE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LUNATONE
    { OBJ_EVENT_GFX_PKMN_SOLROCK_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SOLROCK
    { OBJ_EVENT_GFX_PKMN_BARBOACH_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BARBOACH
    { OBJ_EVENT_GFX_PKMN_WHISCASH_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_WHISCASH
    { OBJ_EVENT_GFX_PKMN_CORPHISH_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CORPHISH
    { OBJ_EVENT_GFX_PKMN_CRAWDAUNT_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CRAWDAUNT
    { OBJ_EVENT_GFX_PKMN_BALTOY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BALTOY
    { OBJ_EVENT_GFX_PKMN_CLAYDOL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CLAYDOL
    { OBJ_EVENT_GFX_PKMN_LILEEP_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LILEEP
    { OBJ_EVENT_GFX_PKMN_CRADILY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CRADILY
    { OBJ_EVENT_GFX_PKMN_ANORITH_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ANORITH
    { OBJ_EVENT_GFX_PKMN_ARMALDO_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ARMALDO
    { OBJ_EVENT_GFX_PKMN_FEEBAS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_FEEBAS
    { OBJ_EVENT_GFX_PKMN_MILOTIC_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MILOTIC
    { OBJ_EVENT_GFX_PKMN_CASTFORM_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CASTFORM
    { OBJ_EVENT_GFX_PKMN_KECLEON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_KECLEON
    { OBJ_EVENT_GFX_PKMN_SHUPPET_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SHUPPET
    { OBJ_EVENT_GFX_PKMN_BANETTE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BANETTE
    { OBJ_EVENT_GFX_PKMN_DUSKULL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DUSKULL
    { OBJ_EVENT_GFX_PKMN_DUSCLOPS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DUSCLOPS
    { OBJ_EVENT_GFX_PKMN_TROPIUS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_TROPIUS
    { OBJ_EVENT_GFX_PKMN_CHIMECHO_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CHIMECHO
    { OBJ_EVENT_GFX_PKMN_ABSOL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ABSOL
    { OBJ_EVENT_GFX_PKMN_WYNAUT_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_WYNAUT
    { OBJ_EVENT_GFX_PKMN_SNORUNT_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SNORUNT
    { OBJ_EVENT_GFX_PKMN_GLALIE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GLALIE
    { OBJ_EVENT_GFX_PKMN_SPHEAL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SPHEAL
    { OBJ_EVENT_GFX_PKMN_SEALEO_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SEALEO
    { OBJ_EVENT_GFX_PKMN_WALREIN_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_WALREIN
    { OBJ_EVENT_GFX_PKMN_CLAMPERL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CLAMPERL
    { OBJ_EVENT_GFX_PKMN_HUNTAIL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_HUNTAIL
    { OBJ_EVENT_GFX_PKMN_GOREBYSS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GOREBYSS
    { OBJ_EVENT_GFX_PKMN_RELICANTH_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_RELICANTH
    { OBJ_EVENT_GFX_PKMN_LUVDISC_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LUVDISC
    { OBJ_EVENT_GFX_PKMN_BAGON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BAGON
    { OBJ_EVENT_GFX_PKMN_SHELGON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SHELGON
    { OBJ_EVENT_GFX_PKMN_SALAMENCE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SALAMENCE
    { OBJ_EVENT_GFX_PKMN_BELDUM_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BELDUM
    { OBJ_EVENT_GFX_PKMN_METANG_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_METANG
    { OBJ_EVENT_GFX_PKMN_METAGROSS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_METAGROSS
    { OBJ_EVENT_GFX_PKMN_REGIROCK_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_REGIROCK
    { OBJ_EVENT_GFX_PKMN_REGICE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_REGICE
    { OBJ_EVENT_GFX_PKMN_REGISTEEL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_REGISTEEL
    { OBJ_EVENT_GFX_PKMN_LATIAS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LATIAS
    { OBJ_EVENT_GFX_PKMN_LATIOS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LATIOS
    { OBJ_EVENT_GFX_PKMN_KYOGRE_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_KYOGRE
    { OBJ_EVENT_GFX_PKMN_GROUDON_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GROUDON
    { OBJ_EVENT_GFX_PKMN_RAYQUAZA_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_RAYQUAZA
    { OBJ_EVENT_GFX_PKMN_JIRACHI_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_JIRACHI
    { OBJ_EVENT_GFX_PKMN_DEOXYS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DEOXYS
    { OBJ_EVENT_GFX_PKMN_TURTWIG_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_TURTWIG
    { OBJ_EVENT_GFX_PKMN_GROTLE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GROTLE
    { OBJ_EVENT_GFX_PKMN_TORTERRA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_TORTERRA
    { OBJ_EVENT_GFX_PKMN_CHIMCHAR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CHIMCHAR
    { OBJ_EVENT_GFX_PKMN_MONFERNO_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MONFERNO
    { OBJ_EVENT_GFX_PKMN_INFERNAPE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_INFERNAPE
    { OBJ_EVENT_GFX_PKMN_PIPLUP_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PIPLUP
    { OBJ_EVENT_GFX_PKMN_PRINPLUP_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PRINPLUP
    { OBJ_EVENT_GFX_PKMN_EMPOLEON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_EMPOLEON
    { OBJ_EVENT_GFX_PKMN_STARLY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_STARLY
    { OBJ_EVENT_GFX_PKMN_STARAVIA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_STARAVIA
    { OBJ_EVENT_GFX_PKMN_STARAPTOR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_STARAPTOR
    { OBJ_EVENT_GFX_PKMN_BIDOOF_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BIDOOF
    { OBJ_EVENT_GFX_PKMN_BIBAREL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BIBAREL
    { OBJ_EVENT_GFX_PKMN_KRICKETOT_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_KRICKETOT
    { OBJ_EVENT_GFX_PKMN_KRICKETUNE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_KRICKETUNE
    { OBJ_EVENT_GFX_PKMN_SHINX_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SHINX
    { OBJ_EVENT_GFX_PKMN_LUXIO_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LUXIO
    { OBJ_EVENT_GFX_PKMN_LUXRAY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LUXRAY
    { OBJ_EVENT_GFX_PKMN_BUDEW_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BUDEW
    { OBJ_EVENT_GFX_PKMN_ROSERADE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ROSERADE
    { OBJ_EVENT_GFX_PKMN_CRANIDOS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CRANIDOS
    { OBJ_EVENT_GFX_PKMN_RAMPARDOS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_RAMPARDOS
    { OBJ_EVENT_GFX_PKMN_SHIELDON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SHIELDON
    { OBJ_EVENT_GFX_PKMN_BASTIODON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BASTIODON
    { OBJ_EVENT_GFX_PKMN_BURMY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BURMY
    { OBJ_EVENT_GFX_PKMN_WORMADAM_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_WORMADAM
    { OBJ_EVENT_GFX_PKMN_MOTHIM_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MOTHIM
    { OBJ_EVENT_GFX_PKMN_COMBEE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_COMBEE
    { OBJ_EVENT_GFX_PKMN_COMBEE_F_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_VESPIQUEN_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_VESPIQUEN
    { OBJ_EVENT_GFX_PKMN_PACHIRISU_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PACHIRISU
    { OBJ_EVENT_GFX_PKMN_BUIZEL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BUIZEL
    { OBJ_EVENT_GFX_PKMN_FLOATZEL_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_FLOATZEL
    { OBJ_EVENT_GFX_PKMN_CHERUBI_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CHERUBI
    { OBJ_EVENT_GFX_PKMN_CHERRIM_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CHERRIM
    { OBJ_EVENT_GFX_PKMN_SHELLOS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SHELLOS
    { OBJ_EVENT_GFX_PKMN_GASTRODON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GASTRODON
    { OBJ_EVENT_GFX_PKMN_AMBIPOM_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_AMBIPOM
    { OBJ_EVENT_GFX_PKMN_DRIFLOON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DRIFLOON
    { OBJ_EVENT_GFX_PKMN_DRIFBLIM_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DRIFBLIM
    { OBJ_EVENT_GFX_PKMN_BUNEARY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BUNEARY
    { OBJ_EVENT_GFX_PKMN_LOPUNNY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LOPUNNY
    { OBJ_EVENT_GFX_PKMN_MISMAGIUS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MISMAGIUS
    { OBJ_EVENT_GFX_PKMN_HONCHKROW_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_HONCHKROW
    { OBJ_EVENT_GFX_PKMN_GLAMEOW_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GLAMEOW
    { OBJ_EVENT_GFX_PKMN_PURUGLY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PURUGLY
    { OBJ_EVENT_GFX_PKMN_CHINGLING_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CHINGLING
    { OBJ_EVENT_GFX_PKMN_STUNKY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_STUNKY
    { OBJ_EVENT_GFX_PKMN_SKUNTANK_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SKUNTANK
    { OBJ_EVENT_GFX_PKMN_BRONZOR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BRONZOR
    { OBJ_EVENT_GFX_PKMN_BRONZONG_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BRONZONG
    { OBJ_EVENT_GFX_PKMN_BONSLY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_BONSLY
    { OBJ_EVENT_GFX_PKMN_MIMEJR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MIMEJR
    { OBJ_EVENT_GFX_PKMN_HAPPINY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_HAPPINY
    { OBJ_EVENT_GFX_PKMN_CHATOT_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CHATOT
    { OBJ_EVENT_GFX_PKMN_SPIRITOMB_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SPIRITOMB
    { OBJ_EVENT_GFX_PKMN_GIBLE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GIBLE
    { OBJ_EVENT_GFX_PKMN_GABITE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GABITE
    { OBJ_EVENT_GFX_PKMN_GARCHOMP_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GARCHOMP
    { OBJ_EVENT_GFX_PKMN_MUNCHLAX_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MUNCHLAX
    { OBJ_EVENT_GFX_PKMN_RIOLU_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_RIOLU
    { OBJ_EVENT_GFX_PKMN_LUCARIO_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LUCARIO
    { OBJ_EVENT_GFX_PKMN_HIPPOPOTAS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_HIPPOPOTAS
    { OBJ_EVENT_GFX_PKMN_HIPPOPOTAS_F_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_HIPPOWDON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_HIPPOWDON
    { OBJ_EVENT_GFX_PKMN_HIPPOWDON_F_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_SKORUPI_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SKORUPI
    { OBJ_EVENT_GFX_PKMN_DRAPION_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DRAPION
    { OBJ_EVENT_GFX_PKMN_CROAGUNK_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CROAGUNK
    { OBJ_EVENT_GFX_PKMN_TOXICROAK_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_TOXICROAK
    { OBJ_EVENT_GFX_PKMN_CARNIVINE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CARNIVINE
    { OBJ_EVENT_GFX_PKMN_FINNEON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_FINNEON
    { OBJ_EVENT_GFX_PKMN_LUMINEON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LUMINEON
    { OBJ_EVENT_GFX_PKMN_MANTYKE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MANTYKE
    { OBJ_EVENT_GFX_PKMN_SNOVER_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SNOVER
    { OBJ_EVENT_GFX_PKMN_ABOMASNOW_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ABOMASNOW
    { OBJ_EVENT_GFX_PKMN_WEAVILE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_WEAVILE
    { OBJ_EVENT_GFX_PKMN_MAGNEZONE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MAGNEZONE
    { OBJ_EVENT_GFX_PKMN_LICKILICKY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LICKILICKY
    { OBJ_EVENT_GFX_PKMN_RHYPERIOR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_RHYPERIOR
    { OBJ_EVENT_GFX_PKMN_TANGROWTH_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_TANGROWTH
    { OBJ_EVENT_GFX_PKMN_ELECTIVIRE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ELECTIVIRE
    { OBJ_EVENT_GFX_PKMN_MAGMORTAR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MAGMORTAR
    { OBJ_EVENT_GFX_PKMN_TOGEKISS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_TOGEKISS
    { OBJ_EVENT_GFX_PKMN_LEAFEON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_LEAFEON
    { OBJ_EVENT_GFX_PKMN_GLACEON_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GLACEON
    { OBJ_EVENT_GFX_PKMN_GLISCOR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GLISCOR
    { OBJ_EVENT_GFX_PKMN_MAMOSWINE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MAMOSWINE
    { OBJ_EVENT_GFX_PKMN_PORYGON_Z_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PORYGON_Z
    { OBJ_EVENT_GFX_PKMN_GALLADE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GALLADE
    { OBJ_EVENT_GFX_PKMN_PROBOPASS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PROBOPASS
    { OBJ_EVENT_GFX_PKMN_DUSKNOIR_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DUSKNOIR
    { OBJ_EVENT_GFX_PKMN_FROSLASS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_FROSLASS
    { OBJ_EVENT_GFX_PKMN_ROTOM_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ROTOM
    { OBJ_EVENT_GFX_PKMN_UXIE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_UXIE
    { OBJ_EVENT_GFX_PKMN_MESPRIT_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MESPRIT
    { OBJ_EVENT_GFX_PKMN_AZELF_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_AZELF
    { OBJ_EVENT_GFX_PKMN_DIALGA_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DIALGA
    { OBJ_EVENT_GFX_PKMN_PALKIA_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PALKIA
    { OBJ_EVENT_GFX_PKMN_HEATRAN_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_HEATRAN
    { OBJ_EVENT_GFX_PKMN_REGIGIGAS_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_REGIGIGAS
    { OBJ_EVENT_GFX_PKMN_GIRATINA_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_GIRATINA
    { OBJ_EVENT_GFX_PKMN_CRESSELIA_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_CRESSELIA
    { OBJ_EVENT_GFX_PKMN_PHIONE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_PHIONE
    { OBJ_EVENT_GFX_PKMN_MANAPHY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_MANAPHY
    { OBJ_EVENT_GFX_PKMN_DARKRAI_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_DARKRAI
    { OBJ_EVENT_GFX_PKMN_SHAYMIN_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_SHAYMIN
    { OBJ_EVENT_GFX_PKMN_ARCEUS_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny SPECIES_ARCEUS
    { OBJ_EVENT_GFX_PKMN_GIRATINA_O_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FIGHTING_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FLYING_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_POISON_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GROUND_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ROCK_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_BUG_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GHOST_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_STEEL_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FAIRY_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FIRE_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_WATER_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GRASS_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ELECTRIC_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_PSYCHIC_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ICE_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_DRAGON_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_DARK_SHINY, 0x12, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_DEOXYS_ATTACK_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_DEOXYS_DEFENSE_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_DEOXYS_SPEED_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_BURMY_SANDY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_BURMY_TRASH_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_WORMADAM_SANDY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_WORMADAM_TRASH_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_SHELLOS_EAST_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_GASTRODON_EAST_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ROTOM_HEAT_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ROTOM_WASH_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ROTOM_FROST_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ROTOM_FAN_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ROTOM_MOW_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_SHAYMIN_SKY_SHINY, 0x0, 0x17, Unk_ov5_021FB2C0 },  // shiny alt form
    { 0xffff, 0xffff, 0xffff, NULL }
};

const int Unk_ov5_021FAF40[] = {
    0x9,
    0xffff
};

const UnkStruct_ov5_021ECD10 Unk_ov5_021FC194[] = {
    { 0x0, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x1, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x2, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x3, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x4, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x5, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x6, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x7, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x8, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x9, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xA, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xB, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xC, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xD, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xE, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xf, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x10, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x11, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x12, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x13, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x14, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x15, 0x1, 0x1, 0x2, 0x1, 0x0 },
    { 0x16, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x17, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x18, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x19, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x1A, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x1B, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x1C, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x1D, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x1E, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x1f, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x20, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x21, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x22, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x23, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x24, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x25, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x26, 0x1, 0x1, 0x2, 0x1, 0x0 },
    { 0x27, 0x1, 0x1, 0x2, 0x1, 0x0 },
    { 0x28, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x29, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x2A, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x2B, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x2C, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x2D, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x2E, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x2f, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x30, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x31, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x32, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x33, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x34, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x35, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x36, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x37, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x38, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x39, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x3A, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x3B, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x3C, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x3D, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x3E, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x3f, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x40, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x41, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x42, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x43, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x44, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x45, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x46, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x47, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x48, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x49, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x4A, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x4B, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x4C, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x4D, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x4E, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x4f, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x50, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x51, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x52, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x53, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x54, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x55, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x56, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x57, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x58, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x59, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x5A, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x5B, 0x2, 0x0, 0x0, 0x0, 0x0 },
    { 0x5C, 0x2, 0x0, 0x0, 0x0, 0x0 },
    { 0x5D, 0x2, 0x0, 0x0, 0x0, 0x0 },
    { 0x5E, 0x2, 0x0, 0x0, 0x0, 0x0 },
    { 0x5f, 0x2, 0x0, 0x0, 0x0, 0x0 },
    { 0x60, 0x2, 0x0, 0x0, 0x0, 0x0 },
    { 0x61, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x62, 0x1, 0x1, 0x2, 0x1, 0x0 },
    { 0x63, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x64, 0x1, 0x0, 0x0, 0x1, 0x0 },
    { 0x76, 0x2, 0x1, 0x0, 0x0, 0x0 },
    { 0x78, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x79, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x7A, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x7B, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x7C, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x7D, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x7E, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x7f, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x80, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x81, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x82, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x83, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x84, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x85, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x86, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x87, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x88, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x89, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x8A, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x8B, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x8C, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x8D, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x8E, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x8f, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x90, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x91, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x92, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x93, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x94, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x95, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x96, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x97, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x98, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x99, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x9A, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x9B, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x9C, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x9D, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x9E, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x9f, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xA0, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xA1, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xA2, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xA3, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xA4, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xA5, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xA6, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xA7, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xA8, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xA9, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xAA, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xAB, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xAC, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xAD, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xAE, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xaf, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xB0, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xB1, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xB2, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xB3, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xB4, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xB5, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xB6, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xB7, 0x2, 0x0, 0x0, 0x0, 0x0 },
    { 0xB8, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xB9, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xBA, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xBB, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xBC, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xBD, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xBE, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xbf, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xC0, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xC1, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xC2, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xC3, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x2000, 0x0, 0x0, 0x0, 0x0, 0x0 },
    { 0xC4, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xC5, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xC6, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xC7, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xC8, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xC9, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xCA, 0x1, 0x0, 0x0, 0x0, 0x0 },
    { 0xCB, 0x1, 0x1, 0x0, 0x1, 0x0 },
    { 0xCC, 0x1, 0x1, 0x2, 0x1, 0x0 },
    { 0xCD, 0x1, 0x1, 0x2, 0x1, 0x0 },
    { 0xCE, 0x1, 0x1, 0x2, 0x1, 0x0 },
    { 0xcf, 0x1, 0x1, 0x2, 0x1, 0x0 },
    { 0xD0, 0x1, 0x1, 0x2, 0x1, 0x0 },
    { 0xD1, 0x2, 0x0, 0x0, 0x0, 0x0 },
    { 0xD2, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xD3, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xD4, 0x1, 0x0, 0x1, 0x1, 0x0 },
    { 0xD5, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xD6, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xD7, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xD8, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xD9, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xDA, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xDB, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xDC, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xDD, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xDE, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xdf, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xE0, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xE1, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xE2, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xE3, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xE4, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xE5, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xE6, 0x1, 0x0, 0x1, 0x1, 0x0 },
    { 0xE7, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xE8, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xE9, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xEA, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xEB, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xEC, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xED, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xEE, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xef, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xf0, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xf1, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xf2, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xf3, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xf4, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xf5, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xf6, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xf7, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xf8, 0x1, 0x0, 0x1, 0x1, 0x0 },
    { 0xf9, 0x1, 0x0, 0x1, 0x1, 0x0 },
    { 0xfa, 0x1, 0x1, 0x0, 0x1, 0x0 },
    { 0xfb, 0x1, 0x1, 0x0, 0x1, 0x0 },
    { 0xfc, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xfd, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xfe, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0xff, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x100, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x101, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x102, 0x1, 0x0, 0x0, 0x0, 0x0 },
    { 0x103, 0x1, 0x0, 0x0, 0x0, 0x0 },
    { 0x104, 0x1, 0x0, 0x0, 0x0, 0x0 },
    { 0x105, 0x1, 0x0, 0x0, 0x0, 0x0 },
    { 0x106, 0x2, 0x0, 0x0, 0x0, 0x0 },
    { 0x107, 0x1, 0x0, 0x1, 0x1, 0x0 },
    { 0x108, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x109, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x10A, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x10B, 0x1, 0x1, 0x1, 0x1, 0x0 },
    { 0x10C, 0x1, 0x0, 0x1, 0x1, 0x0 },
    { 0x10D, 0x1, 0x0, 0x1, 0x1, 0x0 },
    { 0x10E, 0x1, 0x0, 0x1, 0x1, 0x0 },
    { 0x10f, 0x1, 0x0, 0x1, 0x1, 0x0 },
    { 0x110, 0x1, 0x0, 0x1, 0x1, 0x0 },
    { 0x111, 0x1, 0x0, 0x1, 0x1, 0x0 },
    { 0x112, 0x1, 0x0, 0x1, 0x1, 0x0 },
    { 0x113, 0x1, 0x0, 0x1, 0x1, 0x0 },
    { OBJ_EVENT_GFX_PKMN_BULBASAUR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BULBASAUR
    { OBJ_EVENT_GFX_PKMN_IVYSAUR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_IVYSAUR
    { OBJ_EVENT_GFX_PKMN_VENUSAUR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_VENUSAUR
    { OBJ_EVENT_GFX_PKMN_VENUSAUR_F, 0x1, 0x1, 0x1, 0x1, 0x0 },  // female
    { OBJ_EVENT_GFX_PKMN_CHARMANDER, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CHARMANDER
    { OBJ_EVENT_GFX_PKMN_CHARMELEON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CHARMELEON
    { OBJ_EVENT_GFX_PKMN_CHARIZARD, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CHARIZARD
    { OBJ_EVENT_GFX_PKMN_SQUIRTLE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SQUIRTLE
    { OBJ_EVENT_GFX_PKMN_WARTORTLE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_WARTORTLE
    { OBJ_EVENT_GFX_PKMN_BLASTOISE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BLASTOISE
    { OBJ_EVENT_GFX_PKMN_CATERPIE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CATERPIE
    { OBJ_EVENT_GFX_PKMN_METAPOD, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_METAPOD
    { OBJ_EVENT_GFX_PKMN_BUTTERFREE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BUTTERFREE
    { OBJ_EVENT_GFX_PKMN_WEEDLE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_WEEDLE
    { OBJ_EVENT_GFX_PKMN_KAKUNA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_KAKUNA
    { OBJ_EVENT_GFX_PKMN_BEEDRILL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BEEDRILL
    { OBJ_EVENT_GFX_PKMN_PIDGEY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PIDGEY
    { OBJ_EVENT_GFX_PKMN_PIDGEOTTO, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PIDGEOTTO
    { OBJ_EVENT_GFX_PKMN_PIDGEOT, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PIDGEOT
    { OBJ_EVENT_GFX_PKMN_RATTATA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_RATTATA
    { OBJ_EVENT_GFX_PKMN_RATICATE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_RATICATE
    { OBJ_EVENT_GFX_PKMN_SPEAROW, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SPEAROW
    { OBJ_EVENT_GFX_PKMN_FEAROW, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_FEAROW
    { OBJ_EVENT_GFX_PKMN_EKANS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_EKANS
    { OBJ_EVENT_GFX_PKMN_ARBOK, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARBOK
    { OBJ_EVENT_GFX_PKMN_PIKACHU, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PIKACHU
    { OBJ_EVENT_GFX_PKMN_PIKACHU_F, 0x1, 0x1, 0x1, 0x1, 0x0 },  // female
    { OBJ_EVENT_GFX_PKMN_RAICHU, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_RAICHU
    { OBJ_EVENT_GFX_PKMN_SANDSHREW, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SANDSHREW
    { OBJ_EVENT_GFX_PKMN_SANDSLASH, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SANDSLASH
    { OBJ_EVENT_GFX_PKMN_NIDORAN_F, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_NIDORAN_F
    { OBJ_EVENT_GFX_PKMN_NIDORINA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_NIDORINA
    { OBJ_EVENT_GFX_PKMN_NIDOQUEEN, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_NIDOQUEEN
    { OBJ_EVENT_GFX_PKMN_NIDORAN_M, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_NIDORAN_M
    { OBJ_EVENT_GFX_PKMN_NIDORINO, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_NIDORINO
    { OBJ_EVENT_GFX_PKMN_NIDOKING, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_NIDOKING
    { OBJ_EVENT_GFX_PKMN_CLEFAIRY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CLEFAIRY
    { OBJ_EVENT_GFX_PKMN_CLEFABLE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CLEFABLE
    { OBJ_EVENT_GFX_PKMN_VULPIX, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_VULPIX
    { OBJ_EVENT_GFX_PKMN_NINETALES, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_NINETALES
    { OBJ_EVENT_GFX_PKMN_JIGGLYPUFF, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_JIGGLYPUFF
    { OBJ_EVENT_GFX_PKMN_WIGGLYTUFF, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_WIGGLYTUFF
    { OBJ_EVENT_GFX_PKMN_ZUBAT, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ZUBAT
    { OBJ_EVENT_GFX_PKMN_GOLBAT, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GOLBAT
    { OBJ_EVENT_GFX_PKMN_ODDISH, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ODDISH
    { OBJ_EVENT_GFX_PKMN_GLOOM, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GLOOM
    { OBJ_EVENT_GFX_PKMN_VILEPLUME, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_VILEPLUME
    { OBJ_EVENT_GFX_PKMN_PARAS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PARAS
    { OBJ_EVENT_GFX_PKMN_PARASECT, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PARASECT
    { OBJ_EVENT_GFX_PKMN_VENONAT, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_VENONAT
    { OBJ_EVENT_GFX_PKMN_VENOMOTH, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_VENOMOTH
    { OBJ_EVENT_GFX_PKMN_DIGLETT, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DIGLETT
    { OBJ_EVENT_GFX_PKMN_DUGTRIO, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DUGTRIO
    { OBJ_EVENT_GFX_PKMN_MEOWTH, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MEOWTH
    { OBJ_EVENT_GFX_PKMN_PERSIAN, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PERSIAN
    { OBJ_EVENT_GFX_PKMN_PSYDUCK, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PSYDUCK
    { OBJ_EVENT_GFX_PKMN_GOLDUCK, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GOLDUCK
    { OBJ_EVENT_GFX_PKMN_MANKEY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MANKEY
    { OBJ_EVENT_GFX_PKMN_PRIMEAPE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PRIMEAPE
    { OBJ_EVENT_GFX_PKMN_GROWLITHE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GROWLITHE
    { OBJ_EVENT_GFX_PKMN_ARCANINE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARCANINE
    { OBJ_EVENT_GFX_PKMN_POLIWAG, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_POLIWAG
    { OBJ_EVENT_GFX_PKMN_POLIWHIRL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_POLIWHIRL
    { OBJ_EVENT_GFX_PKMN_POLIWRATH, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_POLIWRATH
    { OBJ_EVENT_GFX_PKMN_ABRA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ABRA
    { OBJ_EVENT_GFX_PKMN_KADABRA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_KADABRA
    { OBJ_EVENT_GFX_PKMN_ALAKAZAM, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ALAKAZAM
    { OBJ_EVENT_GFX_PKMN_MACHOP, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MACHOP
    { OBJ_EVENT_GFX_PKMN_MACHOKE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MACHOKE
    { OBJ_EVENT_GFX_PKMN_MACHAMP, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MACHAMP
    { OBJ_EVENT_GFX_PKMN_BELLSPROUT, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BELLSPROUT
    { OBJ_EVENT_GFX_PKMN_WEEPINBELL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_WEEPINBELL
    { OBJ_EVENT_GFX_PKMN_VICTREEBEL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_VICTREEBEL
    { OBJ_EVENT_GFX_PKMN_TENTACOOL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_TENTACOOL
    { OBJ_EVENT_GFX_PKMN_TENTACRUEL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_TENTACRUEL
    { OBJ_EVENT_GFX_PKMN_GEODUDE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GEODUDE
    { OBJ_EVENT_GFX_PKMN_GRAVELER, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GRAVELER
    { OBJ_EVENT_GFX_PKMN_GOLEM, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GOLEM
    { OBJ_EVENT_GFX_PKMN_PONYTA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PONYTA
    { OBJ_EVENT_GFX_PKMN_RAPIDASH, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_RAPIDASH
    { OBJ_EVENT_GFX_PKMN_SLOWPOKE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SLOWPOKE
    { OBJ_EVENT_GFX_PKMN_SLOWBRO, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SLOWBRO
    { OBJ_EVENT_GFX_PKMN_MAGNEMITE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MAGNEMITE
    { OBJ_EVENT_GFX_PKMN_MAGNETON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MAGNETON
    { OBJ_EVENT_GFX_PKMN_FARFETCHD, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_FARFETCHD
    { OBJ_EVENT_GFX_PKMN_DODUO, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DODUO
    { OBJ_EVENT_GFX_PKMN_DODRIO, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DODRIO
    { OBJ_EVENT_GFX_PKMN_SEEL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SEEL
    { OBJ_EVENT_GFX_PKMN_DEWGONG, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DEWGONG
    { OBJ_EVENT_GFX_PKMN_GRIMER, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GRIMER
    { OBJ_EVENT_GFX_PKMN_MUK, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MUK
    { OBJ_EVENT_GFX_PKMN_SHELLDER, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SHELLDER
    { OBJ_EVENT_GFX_PKMN_CLOYSTER, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CLOYSTER
    { OBJ_EVENT_GFX_PKMN_GASTLY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GASTLY
    { OBJ_EVENT_GFX_PKMN_HAUNTER, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_HAUNTER
    { OBJ_EVENT_GFX_PKMN_GENGAR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GENGAR
    { OBJ_EVENT_GFX_PKMN_ONIX, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ONIX
    { OBJ_EVENT_GFX_PKMN_DROWZEE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DROWZEE
    { OBJ_EVENT_GFX_PKMN_HYPNO, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_HYPNO
    { OBJ_EVENT_GFX_PKMN_KRABBY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_KRABBY
    { OBJ_EVENT_GFX_PKMN_KINGLER, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_KINGLER
    { OBJ_EVENT_GFX_PKMN_VOLTORB, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_VOLTORB
    { OBJ_EVENT_GFX_PKMN_ELECTRODE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ELECTRODE
    { OBJ_EVENT_GFX_PKMN_EXEGGCUTE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_EXEGGCUTE
    { OBJ_EVENT_GFX_PKMN_EXEGGUTOR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_EXEGGUTOR
    { OBJ_EVENT_GFX_PKMN_CUBONE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CUBONE
    { OBJ_EVENT_GFX_PKMN_MAROWAK, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MAROWAK
    { OBJ_EVENT_GFX_PKMN_HITMONLEE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_HITMONLEE
    { OBJ_EVENT_GFX_PKMN_HITMONCHAN, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_HITMONCHAN
    { OBJ_EVENT_GFX_PKMN_LICKITUNG, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LICKITUNG
    { OBJ_EVENT_GFX_PKMN_KOFFING, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_KOFFING
    { OBJ_EVENT_GFX_PKMN_WEEZING, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_WEEZING
    { OBJ_EVENT_GFX_PKMN_RHYHORN, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_RHYHORN
    { OBJ_EVENT_GFX_PKMN_RHYDON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_RHYDON
    { OBJ_EVENT_GFX_PKMN_CHANSEY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CHANSEY
    { OBJ_EVENT_GFX_PKMN_TANGELA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_TANGELA
    { OBJ_EVENT_GFX_PKMN_KANGASKHAN, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_KANGASKHAN
    { OBJ_EVENT_GFX_PKMN_HORSEA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_HORSEA
    { OBJ_EVENT_GFX_PKMN_SEADRA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SEADRA
    { OBJ_EVENT_GFX_PKMN_GOLDEEN, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GOLDEEN
    { OBJ_EVENT_GFX_PKMN_SEAKING, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SEAKING
    { OBJ_EVENT_GFX_PKMN_STARYU, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_STARYU
    { OBJ_EVENT_GFX_PKMN_STARMIE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_STARMIE
    { OBJ_EVENT_GFX_PKMN_MR_MIME, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MR_MIME
    { OBJ_EVENT_GFX_PKMN_SCYTHER, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SCYTHER
    { OBJ_EVENT_GFX_PKMN_JYNX, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_JYNX
    { OBJ_EVENT_GFX_PKMN_ELECTABUZZ, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ELECTABUZZ
    { OBJ_EVENT_GFX_PKMN_MAGMAR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MAGMAR
    { OBJ_EVENT_GFX_PKMN_PINSIR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PINSIR
    { OBJ_EVENT_GFX_PKMN_TAUROS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_TAUROS
    { OBJ_EVENT_GFX_PKMN_MAGIKARP, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MAGIKARP
    { OBJ_EVENT_GFX_PKMN_GYARADOS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GYARADOS
    { OBJ_EVENT_GFX_PKMN_LAPRAS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LAPRAS
    { OBJ_EVENT_GFX_PKMN_DITTO, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DITTO
    { OBJ_EVENT_GFX_PKMN_EEVEE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_EEVEE
    { OBJ_EVENT_GFX_PKMN_VAPOREON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_VAPOREON
    { OBJ_EVENT_GFX_PKMN_JOLTEON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_JOLTEON
    { OBJ_EVENT_GFX_PKMN_FLAREON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_FLAREON
    { OBJ_EVENT_GFX_PKMN_PORYGON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PORYGON
    { OBJ_EVENT_GFX_PKMN_OMANYTE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_OMANYTE
    { OBJ_EVENT_GFX_PKMN_OMASTAR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_OMASTAR
    { OBJ_EVENT_GFX_PKMN_KABUTO, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_KABUTO
    { OBJ_EVENT_GFX_PKMN_KABUTOPS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_KABUTOPS
    { OBJ_EVENT_GFX_PKMN_AERODACTYL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_AERODACTYL
    { OBJ_EVENT_GFX_PKMN_SNORLAX, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SNORLAX
    { OBJ_EVENT_GFX_PKMN_ARTICUNO, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARTICUNO
    { OBJ_EVENT_GFX_PKMN_ZAPDOS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ZAPDOS
    { OBJ_EVENT_GFX_PKMN_MOLTRES, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MOLTRES
    { OBJ_EVENT_GFX_PKMN_DRATINI, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DRATINI
    { OBJ_EVENT_GFX_PKMN_DRAGONAIR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DRAGONAIR
    { OBJ_EVENT_GFX_PKMN_DRAGONITE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DRAGONITE
    { OBJ_EVENT_GFX_PKMN_MEWTWO, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MEWTWO
    { OBJ_EVENT_GFX_PKMN_MEW, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MEW
    { OBJ_EVENT_GFX_PKMN_CHIKORITA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CHIKORITA
    { OBJ_EVENT_GFX_PKMN_BAYLEEF, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BAYLEEF
    { OBJ_EVENT_GFX_PKMN_BAYLEEF_F, 0x1, 0x1, 0x1, 0x1, 0x0 },  // female
    { OBJ_EVENT_GFX_PKMN_CYNDAQUIL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CYNDAQUIL
    { OBJ_EVENT_GFX_PKMN_QUILAVA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_QUILAVA
    { OBJ_EVENT_GFX_PKMN_TYPHLOSION, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_TYPHLOSION
    { OBJ_EVENT_GFX_PKMN_TOTODILE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_TOTODILE
    { OBJ_EVENT_GFX_PKMN_CROCONAW, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CROCONAW
    { OBJ_EVENT_GFX_PKMN_FERALIGATR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_FERALIGATR
    { OBJ_EVENT_GFX_PKMN_SENTRET, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SENTRET
    { OBJ_EVENT_GFX_PKMN_FURRET, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_FURRET
    { OBJ_EVENT_GFX_PKMN_HOOTHOOT, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_HOOTHOOT
    { OBJ_EVENT_GFX_PKMN_NOCTOWL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_NOCTOWL
    { OBJ_EVENT_GFX_PKMN_LEDYBA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LEDYBA
    { OBJ_EVENT_GFX_PKMN_LEDIAN, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LEDIAN
    { OBJ_EVENT_GFX_PKMN_SPINARAK, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SPINARAK
    { OBJ_EVENT_GFX_PKMN_ARIADOS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARIADOS
    { OBJ_EVENT_GFX_PKMN_CROBAT, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CROBAT
    { OBJ_EVENT_GFX_PKMN_CHINCHOU, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CHINCHOU
    { OBJ_EVENT_GFX_PKMN_LANTURN, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LANTURN
    { OBJ_EVENT_GFX_PKMN_PICHU, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PICHU
    { OBJ_EVENT_GFX_PKMN_CLEFFA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CLEFFA
    { OBJ_EVENT_GFX_PKMN_IGGLYBUFF, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_IGGLYBUFF
    { OBJ_EVENT_GFX_PKMN_TOGEPI, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_TOGEPI
    { OBJ_EVENT_GFX_PKMN_TOGETIC, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_TOGETIC
    { OBJ_EVENT_GFX_PKMN_NATU, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_NATU
    { OBJ_EVENT_GFX_PKMN_XATU, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_XATU
    { OBJ_EVENT_GFX_PKMN_MAREEP, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MAREEP
    { OBJ_EVENT_GFX_PKMN_FLAAFFY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_FLAAFFY
    { OBJ_EVENT_GFX_PKMN_AMPHAROS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_AMPHAROS
    { OBJ_EVENT_GFX_PKMN_BELLOSSOM, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BELLOSSOM
    { OBJ_EVENT_GFX_PKMN_MARILL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MARILL
    { OBJ_EVENT_GFX_PKMN_AZUMARILL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_AZUMARILL
    { OBJ_EVENT_GFX_PKMN_SUDOWOODO, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SUDOWOODO
    { OBJ_EVENT_GFX_PKMN_POLITOED, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_POLITOED
    { OBJ_EVENT_GFX_PKMN_HOPPIP, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_HOPPIP
    { OBJ_EVENT_GFX_PKMN_SKIPLOOM, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SKIPLOOM
    { OBJ_EVENT_GFX_PKMN_JUMPLUFF, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_JUMPLUFF
    { OBJ_EVENT_GFX_PKMN_AIPOM, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_AIPOM
    { OBJ_EVENT_GFX_PKMN_SUNKERN, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SUNKERN
    { OBJ_EVENT_GFX_PKMN_SUNFLORA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SUNFLORA
    { OBJ_EVENT_GFX_PKMN_YANMA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_YANMA
    { OBJ_EVENT_GFX_PKMN_WOOPER, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_WOOPER
    { OBJ_EVENT_GFX_PKMN_QUAGSIRE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_QUAGSIRE
    { OBJ_EVENT_GFX_PKMN_ESPEON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ESPEON
    { OBJ_EVENT_GFX_PKMN_UMBREON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_UMBREON
    { OBJ_EVENT_GFX_PKMN_MURKROW, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MURKROW
    { OBJ_EVENT_GFX_PKMN_SLOWKING, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SLOWKING
    { OBJ_EVENT_GFX_PKMN_MISDREAVUS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MISDREAVUS
    { OBJ_EVENT_GFX_PKMN_UNOWN, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_UNOWN
    { OBJ_EVENT_GFX_PKMN_WOBBUFFET, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_WOBBUFFET
    { OBJ_EVENT_GFX_PKMN_WOBBUFFET_F, 0x1, 0x1, 0x1, 0x1, 0x0 },  // female
    { OBJ_EVENT_GFX_PKMN_GIRAFARIG, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GIRAFARIG
    { OBJ_EVENT_GFX_PKMN_PINECO, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PINECO
    { OBJ_EVENT_GFX_PKMN_FORRETRESS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_FORRETRESS
    { OBJ_EVENT_GFX_PKMN_DUNSPARCE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DUNSPARCE
    { OBJ_EVENT_GFX_PKMN_GLIGAR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GLIGAR
    { OBJ_EVENT_GFX_PKMN_STEELIX, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_STEELIX
    { OBJ_EVENT_GFX_PKMN_STEELIX_F, 0x1, 0x1, 0x1, 0x1, 0x0 },  // female
    { OBJ_EVENT_GFX_PKMN_SNUBBULL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SNUBBULL
    { OBJ_EVENT_GFX_PKMN_GRANBULL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GRANBULL
    { OBJ_EVENT_GFX_PKMN_QWILFISH, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_QWILFISH
    { OBJ_EVENT_GFX_PKMN_SCIZOR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SCIZOR
    { OBJ_EVENT_GFX_PKMN_SHUCKLE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SHUCKLE
    { OBJ_EVENT_GFX_PKMN_HERACROSS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_HERACROSS
    { OBJ_EVENT_GFX_PKMN_HERACROSS_F, 0x1, 0x1, 0x1, 0x1, 0x0 },  // female
    { OBJ_EVENT_GFX_PKMN_SNEASEL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SNEASEL
    { OBJ_EVENT_GFX_PKMN_TEDDIURSA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_TEDDIURSA
    { OBJ_EVENT_GFX_PKMN_URSARING, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_URSARING
    { OBJ_EVENT_GFX_PKMN_SLUGMA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SLUGMA
    { OBJ_EVENT_GFX_PKMN_MAGCARGO, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MAGCARGO
    { OBJ_EVENT_GFX_PKMN_SWINUB, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SWINUB
    { OBJ_EVENT_GFX_PKMN_PILOSWINE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PILOSWINE
    { OBJ_EVENT_GFX_PKMN_CORSOLA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CORSOLA
    { OBJ_EVENT_GFX_PKMN_REMORAID, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_REMORAID
    { OBJ_EVENT_GFX_PKMN_OCTILLERY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_OCTILLERY
    { OBJ_EVENT_GFX_PKMN_DELIBIRD, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DELIBIRD
    { OBJ_EVENT_GFX_PKMN_MANTINE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MANTINE
    { OBJ_EVENT_GFX_PKMN_SKARMORY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SKARMORY
    { OBJ_EVENT_GFX_PKMN_HOUNDOUR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_HOUNDOUR
    { OBJ_EVENT_GFX_PKMN_HOUNDOOM, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_HOUNDOOM
    { OBJ_EVENT_GFX_PKMN_KINGDRA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_KINGDRA
    { OBJ_EVENT_GFX_PKMN_PHANPY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PHANPY
    { OBJ_EVENT_GFX_PKMN_DONPHAN, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DONPHAN
    { OBJ_EVENT_GFX_PKMN_PORYGON2, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PORYGON2
    { OBJ_EVENT_GFX_PKMN_STANTLER, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_STANTLER
    { OBJ_EVENT_GFX_PKMN_SMEARGLE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SMEARGLE
    { OBJ_EVENT_GFX_PKMN_TYROGUE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_TYROGUE
    { OBJ_EVENT_GFX_PKMN_HITMONTOP, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_HITMONTOP
    { OBJ_EVENT_GFX_PKMN_SMOOCHUM, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SMOOCHUM
    { OBJ_EVENT_GFX_PKMN_ELEKID, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ELEKID
    { OBJ_EVENT_GFX_PKMN_MAGBY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MAGBY
    { OBJ_EVENT_GFX_PKMN_MILTANK, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MILTANK
    { OBJ_EVENT_GFX_PKMN_BLISSEY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BLISSEY
    { OBJ_EVENT_GFX_PKMN_RAIKOU, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_RAIKOU
    { OBJ_EVENT_GFX_PKMN_ENTEI, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ENTEI
    { OBJ_EVENT_GFX_PKMN_SUICUNE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SUICUNE
    { OBJ_EVENT_GFX_PKMN_LARVITAR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LARVITAR
    { OBJ_EVENT_GFX_PKMN_PUPITAR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PUPITAR
    { OBJ_EVENT_GFX_PKMN_TYRANITAR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_TYRANITAR
    { OBJ_EVENT_GFX_PKMN_LUGIA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LUGIA
    { OBJ_EVENT_GFX_PKMN_HO_OH, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_HO_OH
    { OBJ_EVENT_GFX_PKMN_CELEBI, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CELEBI
    { OBJ_EVENT_GFX_PKMN_TREECKO, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_TREECKO
    { OBJ_EVENT_GFX_PKMN_GROVYLE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GROVYLE
    { OBJ_EVENT_GFX_PKMN_SCEPTILE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SCEPTILE
    { OBJ_EVENT_GFX_PKMN_TORCHIC, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_TORCHIC
    { OBJ_EVENT_GFX_PKMN_COMBUSKEN, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_COMBUSKEN
    { OBJ_EVENT_GFX_PKMN_BLAZIKEN, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BLAZIKEN
    { OBJ_EVENT_GFX_PKMN_MUDKIP, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MUDKIP
    { OBJ_EVENT_GFX_PKMN_MARSHTOMP, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MARSHTOMP
    { OBJ_EVENT_GFX_PKMN_SWAMPERT, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SWAMPERT
    { OBJ_EVENT_GFX_PKMN_POOCHYENA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_POOCHYENA
    { OBJ_EVENT_GFX_PKMN_MIGHTYENA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MIGHTYENA
    { OBJ_EVENT_GFX_PKMN_ZIGZAGOON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ZIGZAGOON
    { OBJ_EVENT_GFX_PKMN_LINOONE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LINOONE
    { OBJ_EVENT_GFX_PKMN_WURMPLE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_WURMPLE
    { OBJ_EVENT_GFX_PKMN_SILCOON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SILCOON
    { OBJ_EVENT_GFX_PKMN_BEAUTIFLY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BEAUTIFLY
    { OBJ_EVENT_GFX_PKMN_CASCOON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CASCOON
    { OBJ_EVENT_GFX_PKMN_DUSTOX, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DUSTOX
    { OBJ_EVENT_GFX_PKMN_LOTAD, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LOTAD
    { OBJ_EVENT_GFX_PKMN_LOMBRE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LOMBRE
    { OBJ_EVENT_GFX_PKMN_LUDICOLO, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LUDICOLO
    { OBJ_EVENT_GFX_PKMN_SEEDOT, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SEEDOT
    { OBJ_EVENT_GFX_PKMN_NUZLEAF, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_NUZLEAF
    { OBJ_EVENT_GFX_PKMN_SHIFTRY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SHIFTRY
    { OBJ_EVENT_GFX_PKMN_TAILLOW, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_TAILLOW
    { OBJ_EVENT_GFX_PKMN_SWELLOW, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SWELLOW
    { OBJ_EVENT_GFX_PKMN_WINGULL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_WINGULL
    { OBJ_EVENT_GFX_PKMN_PELIPPER, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PELIPPER
    { OBJ_EVENT_GFX_PKMN_RALTS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_RALTS
    { OBJ_EVENT_GFX_PKMN_KIRLIA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_KIRLIA
    { OBJ_EVENT_GFX_PKMN_GARDEVOIR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GARDEVOIR
    { OBJ_EVENT_GFX_PKMN_SURSKIT, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SURSKIT
    { OBJ_EVENT_GFX_PKMN_MASQUERAIN, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MASQUERAIN
    { OBJ_EVENT_GFX_PKMN_SHROOMISH, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SHROOMISH
    { OBJ_EVENT_GFX_PKMN_BRELOOM, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BRELOOM
    { OBJ_EVENT_GFX_PKMN_SLAKOTH, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SLAKOTH
    { OBJ_EVENT_GFX_PKMN_VIGOROTH, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_VIGOROTH
    { OBJ_EVENT_GFX_PKMN_SLAKING, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SLAKING
    { OBJ_EVENT_GFX_PKMN_NINCADA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_NINCADA
    { OBJ_EVENT_GFX_PKMN_NINJASK, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_NINJASK
    { OBJ_EVENT_GFX_PKMN_SHEDINJA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SHEDINJA
    { OBJ_EVENT_GFX_PKMN_WHISMUR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_WHISMUR
    { OBJ_EVENT_GFX_PKMN_LOUDRED, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LOUDRED
    { OBJ_EVENT_GFX_PKMN_EXPLOUD, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_EXPLOUD
    { OBJ_EVENT_GFX_PKMN_MAKUHITA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MAKUHITA
    { OBJ_EVENT_GFX_PKMN_HARIYAMA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_HARIYAMA
    { OBJ_EVENT_GFX_PKMN_AZURILL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_AZURILL
    { OBJ_EVENT_GFX_PKMN_NOSEPASS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_NOSEPASS
    { OBJ_EVENT_GFX_PKMN_SKITTY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SKITTY
    { OBJ_EVENT_GFX_PKMN_DELCATTY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DELCATTY
    { OBJ_EVENT_GFX_PKMN_SABLEYE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SABLEYE
    { OBJ_EVENT_GFX_PKMN_MAWILE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MAWILE
    { OBJ_EVENT_GFX_PKMN_ARON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARON
    { OBJ_EVENT_GFX_PKMN_LAIRON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LAIRON
    { OBJ_EVENT_GFX_PKMN_AGGRON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_AGGRON
    { OBJ_EVENT_GFX_PKMN_MEDITITE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MEDITITE
    { OBJ_EVENT_GFX_PKMN_MEDICHAM, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MEDICHAM
    { OBJ_EVENT_GFX_PKMN_ELECTRIKE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ELECTRIKE
    { OBJ_EVENT_GFX_PKMN_MANECTRIC, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MANECTRIC
    { OBJ_EVENT_GFX_PKMN_PLUSLE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PLUSLE
    { OBJ_EVENT_GFX_PKMN_MINUN, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MINUN
    { OBJ_EVENT_GFX_PKMN_VOLBEAT, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_VOLBEAT
    { OBJ_EVENT_GFX_PKMN_ILLUMISE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ILLUMISE
    { OBJ_EVENT_GFX_PKMN_ROSELIA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ROSELIA
    { OBJ_EVENT_GFX_PKMN_GULPIN, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GULPIN
    { OBJ_EVENT_GFX_PKMN_SWALOT, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SWALOT
    { OBJ_EVENT_GFX_PKMN_CARVANHA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CARVANHA
    { OBJ_EVENT_GFX_PKMN_SHARPEDO, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SHARPEDO
    { OBJ_EVENT_GFX_PKMN_WAILMER, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_WAILMER
    { OBJ_EVENT_GFX_PKMN_WAILORD, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_WAILORD
    { OBJ_EVENT_GFX_PKMN_NUMEL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_NUMEL
    { OBJ_EVENT_GFX_PKMN_CAMERUPT, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CAMERUPT
    { OBJ_EVENT_GFX_PKMN_TORKOAL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_TORKOAL
    { OBJ_EVENT_GFX_PKMN_SPOINK, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SPOINK
    { OBJ_EVENT_GFX_PKMN_GRUMPIG, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GRUMPIG
    { OBJ_EVENT_GFX_PKMN_SPINDA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SPINDA
    { OBJ_EVENT_GFX_PKMN_TRAPINCH, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_TRAPINCH
    { OBJ_EVENT_GFX_PKMN_VIBRAVA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_VIBRAVA
    { OBJ_EVENT_GFX_PKMN_FLYGON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_FLYGON
    { OBJ_EVENT_GFX_PKMN_CACNEA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CACNEA
    { OBJ_EVENT_GFX_PKMN_CACTURNE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CACTURNE
    { OBJ_EVENT_GFX_PKMN_SWABLU, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SWABLU
    { OBJ_EVENT_GFX_PKMN_ALTARIA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ALTARIA
    { OBJ_EVENT_GFX_PKMN_ZANGOOSE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ZANGOOSE
    { OBJ_EVENT_GFX_PKMN_SEVIPER, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SEVIPER
    { OBJ_EVENT_GFX_PKMN_LUNATONE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LUNATONE
    { OBJ_EVENT_GFX_PKMN_SOLROCK, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SOLROCK
    { OBJ_EVENT_GFX_PKMN_BARBOACH, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BARBOACH
    { OBJ_EVENT_GFX_PKMN_WHISCASH, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_WHISCASH
    { OBJ_EVENT_GFX_PKMN_CORPHISH, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CORPHISH
    { OBJ_EVENT_GFX_PKMN_CRAWDAUNT, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CRAWDAUNT
    { OBJ_EVENT_GFX_PKMN_BALTOY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BALTOY
    { OBJ_EVENT_GFX_PKMN_CLAYDOL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CLAYDOL
    { OBJ_EVENT_GFX_PKMN_LILEEP, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LILEEP
    { OBJ_EVENT_GFX_PKMN_CRADILY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CRADILY
    { OBJ_EVENT_GFX_PKMN_ANORITH, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ANORITH
    { OBJ_EVENT_GFX_PKMN_ARMALDO, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARMALDO
    { OBJ_EVENT_GFX_PKMN_FEEBAS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_FEEBAS
    { OBJ_EVENT_GFX_PKMN_MILOTIC, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MILOTIC
    { OBJ_EVENT_GFX_PKMN_CASTFORM, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CASTFORM
    { OBJ_EVENT_GFX_PKMN_KECLEON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_KECLEON
    { OBJ_EVENT_GFX_PKMN_SHUPPET, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SHUPPET
    { OBJ_EVENT_GFX_PKMN_BANETTE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BANETTE
    { OBJ_EVENT_GFX_PKMN_DUSKULL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DUSKULL
    { OBJ_EVENT_GFX_PKMN_DUSCLOPS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DUSCLOPS
    { OBJ_EVENT_GFX_PKMN_TROPIUS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_TROPIUS
    { OBJ_EVENT_GFX_PKMN_CHIMECHO, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CHIMECHO
    { OBJ_EVENT_GFX_PKMN_ABSOL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ABSOL
    { OBJ_EVENT_GFX_PKMN_WYNAUT, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_WYNAUT
    { OBJ_EVENT_GFX_PKMN_SNORUNT, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SNORUNT
    { OBJ_EVENT_GFX_PKMN_GLALIE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GLALIE
    { OBJ_EVENT_GFX_PKMN_SPHEAL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SPHEAL
    { OBJ_EVENT_GFX_PKMN_SEALEO, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SEALEO
    { OBJ_EVENT_GFX_PKMN_WALREIN, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_WALREIN
    { OBJ_EVENT_GFX_PKMN_CLAMPERL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CLAMPERL
    { OBJ_EVENT_GFX_PKMN_HUNTAIL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_HUNTAIL
    { OBJ_EVENT_GFX_PKMN_GOREBYSS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GOREBYSS
    { OBJ_EVENT_GFX_PKMN_RELICANTH, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_RELICANTH
    { OBJ_EVENT_GFX_PKMN_LUVDISC, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LUVDISC
    { OBJ_EVENT_GFX_PKMN_BAGON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BAGON
    { OBJ_EVENT_GFX_PKMN_SHELGON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SHELGON
    { OBJ_EVENT_GFX_PKMN_SALAMENCE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SALAMENCE
    { OBJ_EVENT_GFX_PKMN_BELDUM, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BELDUM
    { OBJ_EVENT_GFX_PKMN_METANG, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_METANG
    { OBJ_EVENT_GFX_PKMN_METAGROSS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_METAGROSS
    { OBJ_EVENT_GFX_PKMN_REGIROCK, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_REGIROCK
    { OBJ_EVENT_GFX_PKMN_REGICE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_REGICE
    { OBJ_EVENT_GFX_PKMN_REGISTEEL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_REGISTEEL
    { OBJ_EVENT_GFX_PKMN_LATIAS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LATIAS
    { OBJ_EVENT_GFX_PKMN_LATIOS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LATIOS
    { OBJ_EVENT_GFX_PKMN_KYOGRE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_KYOGRE
    { OBJ_EVENT_GFX_PKMN_GROUDON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GROUDON
    { OBJ_EVENT_GFX_PKMN_RAYQUAZA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_RAYQUAZA
    { OBJ_EVENT_GFX_PKMN_JIRACHI, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_JIRACHI
    { OBJ_EVENT_GFX_PKMN_DEOXYS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DEOXYS
    { OBJ_EVENT_GFX_PKMN_TURTWIG, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_TURTWIG
    { OBJ_EVENT_GFX_PKMN_GROTLE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GROTLE
    { OBJ_EVENT_GFX_PKMN_TORTERRA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_TORTERRA
    { OBJ_EVENT_GFX_PKMN_CHIMCHAR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CHIMCHAR
    { OBJ_EVENT_GFX_PKMN_MONFERNO, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MONFERNO
    { OBJ_EVENT_GFX_PKMN_INFERNAPE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_INFERNAPE
    { OBJ_EVENT_GFX_PKMN_PIPLUP, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PIPLUP
    { OBJ_EVENT_GFX_PKMN_PRINPLUP, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PRINPLUP
    { OBJ_EVENT_GFX_PKMN_EMPOLEON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_EMPOLEON
    { OBJ_EVENT_GFX_PKMN_STARLY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_STARLY
    { OBJ_EVENT_GFX_PKMN_STARAVIA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_STARAVIA
    { OBJ_EVENT_GFX_PKMN_STARAPTOR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_STARAPTOR
    { OBJ_EVENT_GFX_PKMN_BIDOOF, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BIDOOF
    { OBJ_EVENT_GFX_PKMN_BIBAREL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BIBAREL
    { OBJ_EVENT_GFX_PKMN_KRICKETOT, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_KRICKETOT
    { OBJ_EVENT_GFX_PKMN_KRICKETUNE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_KRICKETUNE
    { OBJ_EVENT_GFX_PKMN_SHINX, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SHINX
    { OBJ_EVENT_GFX_PKMN_LUXIO, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LUXIO
    { OBJ_EVENT_GFX_PKMN_LUXRAY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LUXRAY
    { OBJ_EVENT_GFX_PKMN_BUDEW, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BUDEW
    { OBJ_EVENT_GFX_PKMN_ROSERADE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ROSERADE
    { OBJ_EVENT_GFX_PKMN_CRANIDOS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CRANIDOS
    { OBJ_EVENT_GFX_PKMN_RAMPARDOS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_RAMPARDOS
    { OBJ_EVENT_GFX_PKMN_SHIELDON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SHIELDON
    { OBJ_EVENT_GFX_PKMN_BASTIODON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BASTIODON
    { OBJ_EVENT_GFX_PKMN_BURMY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BURMY
    { OBJ_EVENT_GFX_PKMN_WORMADAM, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_WORMADAM
    { OBJ_EVENT_GFX_PKMN_MOTHIM, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MOTHIM
    { OBJ_EVENT_GFX_PKMN_COMBEE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_COMBEE
    { OBJ_EVENT_GFX_PKMN_COMBEE_F, 0x1, 0x1, 0x1, 0x1, 0x0 },  // female
    { OBJ_EVENT_GFX_PKMN_VESPIQUEN, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_VESPIQUEN
    { OBJ_EVENT_GFX_PKMN_PACHIRISU, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PACHIRISU
    { OBJ_EVENT_GFX_PKMN_BUIZEL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BUIZEL
    { OBJ_EVENT_GFX_PKMN_FLOATZEL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_FLOATZEL
    { OBJ_EVENT_GFX_PKMN_CHERUBI, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CHERUBI
    { OBJ_EVENT_GFX_PKMN_CHERRIM, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CHERRIM
    { OBJ_EVENT_GFX_PKMN_SHELLOS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SHELLOS
    { OBJ_EVENT_GFX_PKMN_GASTRODON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GASTRODON
    { OBJ_EVENT_GFX_PKMN_AMBIPOM, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_AMBIPOM
    { OBJ_EVENT_GFX_PKMN_DRIFLOON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DRIFLOON
    { OBJ_EVENT_GFX_PKMN_DRIFBLIM, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DRIFBLIM
    { OBJ_EVENT_GFX_PKMN_BUNEARY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BUNEARY
    { OBJ_EVENT_GFX_PKMN_LOPUNNY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LOPUNNY
    { OBJ_EVENT_GFX_PKMN_MISMAGIUS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MISMAGIUS
    { OBJ_EVENT_GFX_PKMN_HONCHKROW, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_HONCHKROW
    { OBJ_EVENT_GFX_PKMN_GLAMEOW, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GLAMEOW
    { OBJ_EVENT_GFX_PKMN_PURUGLY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PURUGLY
    { OBJ_EVENT_GFX_PKMN_CHINGLING, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CHINGLING
    { OBJ_EVENT_GFX_PKMN_STUNKY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_STUNKY
    { OBJ_EVENT_GFX_PKMN_SKUNTANK, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SKUNTANK
    { OBJ_EVENT_GFX_PKMN_BRONZOR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BRONZOR
    { OBJ_EVENT_GFX_PKMN_BRONZONG, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BRONZONG
    { OBJ_EVENT_GFX_PKMN_BONSLY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BONSLY
    { OBJ_EVENT_GFX_PKMN_MIMEJR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MIMEJR
    { OBJ_EVENT_GFX_PKMN_HAPPINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_HAPPINY
    { OBJ_EVENT_GFX_PKMN_CHATOT, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CHATOT
    { OBJ_EVENT_GFX_PKMN_SPIRITOMB, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SPIRITOMB
    { OBJ_EVENT_GFX_PKMN_GIBLE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GIBLE
    { OBJ_EVENT_GFX_PKMN_GABITE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GABITE
    { OBJ_EVENT_GFX_PKMN_GARCHOMP, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GARCHOMP
    { OBJ_EVENT_GFX_PKMN_MUNCHLAX, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MUNCHLAX
    { OBJ_EVENT_GFX_PKMN_RIOLU, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_RIOLU
    { OBJ_EVENT_GFX_PKMN_LUCARIO, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LUCARIO
    { OBJ_EVENT_GFX_PKMN_HIPPOPOTAS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_HIPPOPOTAS
    { OBJ_EVENT_GFX_PKMN_HIPPOPOTAS_F, 0x1, 0x1, 0x1, 0x1, 0x0 },  // female
    { OBJ_EVENT_GFX_PKMN_HIPPOWDON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_HIPPOWDON
    { OBJ_EVENT_GFX_PKMN_HIPPOWDON_F, 0x1, 0x1, 0x1, 0x1, 0x0 },  // female
    { OBJ_EVENT_GFX_PKMN_SKORUPI, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SKORUPI
    { OBJ_EVENT_GFX_PKMN_DRAPION, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DRAPION
    { OBJ_EVENT_GFX_PKMN_CROAGUNK, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CROAGUNK
    { OBJ_EVENT_GFX_PKMN_TOXICROAK, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_TOXICROAK
    { OBJ_EVENT_GFX_PKMN_CARNIVINE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CARNIVINE
    { OBJ_EVENT_GFX_PKMN_FINNEON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_FINNEON
    { OBJ_EVENT_GFX_PKMN_LUMINEON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LUMINEON
    { OBJ_EVENT_GFX_PKMN_MANTYKE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MANTYKE
    { OBJ_EVENT_GFX_PKMN_SNOVER, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SNOVER
    { OBJ_EVENT_GFX_PKMN_ABOMASNOW, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ABOMASNOW
    { OBJ_EVENT_GFX_PKMN_WEAVILE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_WEAVILE
    { OBJ_EVENT_GFX_PKMN_MAGNEZONE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MAGNEZONE
    { OBJ_EVENT_GFX_PKMN_LICKILICKY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LICKILICKY
    { OBJ_EVENT_GFX_PKMN_RHYPERIOR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_RHYPERIOR
    { OBJ_EVENT_GFX_PKMN_TANGROWTH, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_TANGROWTH
    { OBJ_EVENT_GFX_PKMN_ELECTIVIRE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ELECTIVIRE
    { OBJ_EVENT_GFX_PKMN_MAGMORTAR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MAGMORTAR
    { OBJ_EVENT_GFX_PKMN_TOGEKISS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_TOGEKISS
    { OBJ_EVENT_GFX_PKMN_LEAFEON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_LEAFEON
    { OBJ_EVENT_GFX_PKMN_GLACEON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GLACEON
    { OBJ_EVENT_GFX_PKMN_GLISCOR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GLISCOR
    { OBJ_EVENT_GFX_PKMN_MAMOSWINE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MAMOSWINE
    { OBJ_EVENT_GFX_PKMN_PORYGON_Z, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PORYGON_Z
    { OBJ_EVENT_GFX_PKMN_GALLADE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GALLADE
    { OBJ_EVENT_GFX_PKMN_PROBOPASS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PROBOPASS
    { OBJ_EVENT_GFX_PKMN_DUSKNOIR, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DUSKNOIR
    { OBJ_EVENT_GFX_PKMN_FROSLASS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_FROSLASS
    { OBJ_EVENT_GFX_PKMN_ROTOM, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ROTOM
    { OBJ_EVENT_GFX_PKMN_UXIE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_UXIE
    { OBJ_EVENT_GFX_PKMN_MESPRIT, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MESPRIT
    { OBJ_EVENT_GFX_PKMN_AZELF, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_AZELF
    { OBJ_EVENT_GFX_PKMN_DIALGA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DIALGA
    { OBJ_EVENT_GFX_PKMN_PALKIA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PALKIA
    { OBJ_EVENT_GFX_PKMN_HEATRAN, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_HEATRAN
    { OBJ_EVENT_GFX_PKMN_REGIGIGAS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_REGIGIGAS
    { OBJ_EVENT_GFX_PKMN_GIRATINA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GIRATINA
    { OBJ_EVENT_GFX_PKMN_CRESSELIA, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_CRESSELIA
    { OBJ_EVENT_GFX_PKMN_PHIONE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_PHIONE
    { OBJ_EVENT_GFX_PKMN_MANAPHY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_MANAPHY
    { OBJ_EVENT_GFX_PKMN_DARKRAI, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DARKRAI
    { OBJ_EVENT_GFX_PKMN_SHAYMIN, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SHAYMIN
    { OBJ_EVENT_GFX_PKMN_ARCEUS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARCEUS
    { OBJ_EVENT_GFX_PKMN_GIRATINA_O, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GIRATINA origin form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FIGHTING, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARCEUS fighting type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FLYING, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARCEUS flying type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_POISON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARCEUS poison type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GROUND, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARCEUS ground type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ROCK, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARCEUS rock type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_BUG, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARCEUS bug type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GHOST, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARCEUS ghost type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_STEEL, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARCEUS steel type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FAIRY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARCEUS fairy type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FIRE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARCEUS fire type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_WATER, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARCEUS water type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GRASS, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARCEUS grass type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ELECTRIC, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARCEUS electric type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_PSYCHIC, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARCEUS psychic type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ICE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARCEUS ice type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_DRAGON, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARCEUS dragon type
    { OBJ_EVENT_GFX_PKMN_ARCEUS_DARK, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ARCEUS dark type
    { OBJ_EVENT_GFX_PKMN_DEOXYS_ATTACK, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DEOXYS attack form
    { OBJ_EVENT_GFX_PKMN_DEOXYS_DEFENSE, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DEOXYS defense form
    { OBJ_EVENT_GFX_PKMN_DEOXYS_SPEED, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_DEOXYS speed form
    { OBJ_EVENT_GFX_PKMN_BURMY_SANDY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BURMY sandy cloak
    { OBJ_EVENT_GFX_PKMN_BURMY_TRASH, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_BURMY trash cloak
    { OBJ_EVENT_GFX_PKMN_WORMADAM_SANDY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_WORMADAM sandy cloak
    { OBJ_EVENT_GFX_PKMN_WORMADAM_TRASH, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_WORMADAM trash cloak
    { OBJ_EVENT_GFX_PKMN_SHELLOS_EAST, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SHELLOS east sea
    { OBJ_EVENT_GFX_PKMN_GASTRODON_EAST, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_GASTRODON east sea
    { OBJ_EVENT_GFX_PKMN_ROTOM_HEAT, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ROTOM heat
    { OBJ_EVENT_GFX_PKMN_ROTOM_WASH, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ROTOM wash
    { OBJ_EVENT_GFX_PKMN_ROTOM_FROST, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ROTOM frost
    { OBJ_EVENT_GFX_PKMN_ROTOM_FAN, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ROTOM fan
    { OBJ_EVENT_GFX_PKMN_ROTOM_MOW, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_ROTOM mow
    { OBJ_EVENT_GFX_PKMN_SHAYMIN_SKY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // SPECIES_SHAYMIN sky form
    { OBJ_EVENT_GFX_PKMN_BULBASAUR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BULBASAUR
    { OBJ_EVENT_GFX_PKMN_IVYSAUR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_IVYSAUR
    { OBJ_EVENT_GFX_PKMN_VENUSAUR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_VENUSAUR
    { OBJ_EVENT_GFX_PKMN_VENUSAUR_F_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_CHARMANDER_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CHARMANDER
    { OBJ_EVENT_GFX_PKMN_CHARMELEON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CHARMELEON
    { OBJ_EVENT_GFX_PKMN_CHARIZARD_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CHARIZARD
    { OBJ_EVENT_GFX_PKMN_SQUIRTLE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SQUIRTLE
    { OBJ_EVENT_GFX_PKMN_WARTORTLE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_WARTORTLE
    { OBJ_EVENT_GFX_PKMN_BLASTOISE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BLASTOISE
    { OBJ_EVENT_GFX_PKMN_CATERPIE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CATERPIE
    { OBJ_EVENT_GFX_PKMN_METAPOD_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_METAPOD
    { OBJ_EVENT_GFX_PKMN_BUTTERFREE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BUTTERFREE
    { OBJ_EVENT_GFX_PKMN_WEEDLE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_WEEDLE
    { OBJ_EVENT_GFX_PKMN_KAKUNA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_KAKUNA
    { OBJ_EVENT_GFX_PKMN_BEEDRILL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BEEDRILL
    { OBJ_EVENT_GFX_PKMN_PIDGEY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PIDGEY
    { OBJ_EVENT_GFX_PKMN_PIDGEOTTO_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PIDGEOTTO
    { OBJ_EVENT_GFX_PKMN_PIDGEOT_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PIDGEOT
    { OBJ_EVENT_GFX_PKMN_RATTATA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_RATTATA
    { OBJ_EVENT_GFX_PKMN_RATICATE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_RATICATE
    { OBJ_EVENT_GFX_PKMN_SPEAROW_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SPEAROW
    { OBJ_EVENT_GFX_PKMN_FEAROW_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_FEAROW
    { OBJ_EVENT_GFX_PKMN_EKANS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_EKANS
    { OBJ_EVENT_GFX_PKMN_ARBOK_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ARBOK
    { OBJ_EVENT_GFX_PKMN_PIKACHU_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PIKACHU
    { OBJ_EVENT_GFX_PKMN_PIKACHU_F_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_RAICHU_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_RAICHU
    { OBJ_EVENT_GFX_PKMN_SANDSHREW_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SANDSHREW
    { OBJ_EVENT_GFX_PKMN_SANDSLASH_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SANDSLASH
    { OBJ_EVENT_GFX_PKMN_NIDORAN_F_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_NIDORAN_F
    { OBJ_EVENT_GFX_PKMN_NIDORINA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_NIDORINA
    { OBJ_EVENT_GFX_PKMN_NIDOQUEEN_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_NIDOQUEEN
    { OBJ_EVENT_GFX_PKMN_NIDORAN_M_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_NIDORAN_M
    { OBJ_EVENT_GFX_PKMN_NIDORINO_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_NIDORINO
    { OBJ_EVENT_GFX_PKMN_NIDOKING_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_NIDOKING
    { OBJ_EVENT_GFX_PKMN_CLEFAIRY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CLEFAIRY
    { OBJ_EVENT_GFX_PKMN_CLEFABLE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CLEFABLE
    { OBJ_EVENT_GFX_PKMN_VULPIX_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_VULPIX
    { OBJ_EVENT_GFX_PKMN_NINETALES_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_NINETALES
    { OBJ_EVENT_GFX_PKMN_JIGGLYPUFF_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_JIGGLYPUFF
    { OBJ_EVENT_GFX_PKMN_WIGGLYTUFF_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_WIGGLYTUFF
    { OBJ_EVENT_GFX_PKMN_ZUBAT_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ZUBAT
    { OBJ_EVENT_GFX_PKMN_GOLBAT_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GOLBAT
    { OBJ_EVENT_GFX_PKMN_ODDISH_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ODDISH
    { OBJ_EVENT_GFX_PKMN_GLOOM_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GLOOM
    { OBJ_EVENT_GFX_PKMN_VILEPLUME_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_VILEPLUME
    { OBJ_EVENT_GFX_PKMN_PARAS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PARAS
    { OBJ_EVENT_GFX_PKMN_PARASECT_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PARASECT
    { OBJ_EVENT_GFX_PKMN_VENONAT_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_VENONAT
    { OBJ_EVENT_GFX_PKMN_VENOMOTH_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_VENOMOTH
    { OBJ_EVENT_GFX_PKMN_DIGLETT_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DIGLETT
    { OBJ_EVENT_GFX_PKMN_DUGTRIO_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DUGTRIO
    { OBJ_EVENT_GFX_PKMN_MEOWTH_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MEOWTH
    { OBJ_EVENT_GFX_PKMN_PERSIAN_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PERSIAN
    { OBJ_EVENT_GFX_PKMN_PSYDUCK_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PSYDUCK
    { OBJ_EVENT_GFX_PKMN_GOLDUCK_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GOLDUCK
    { OBJ_EVENT_GFX_PKMN_MANKEY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MANKEY
    { OBJ_EVENT_GFX_PKMN_PRIMEAPE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PRIMEAPE
    { OBJ_EVENT_GFX_PKMN_GROWLITHE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GROWLITHE
    { OBJ_EVENT_GFX_PKMN_ARCANINE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ARCANINE
    { OBJ_EVENT_GFX_PKMN_POLIWAG_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_POLIWAG
    { OBJ_EVENT_GFX_PKMN_POLIWHIRL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_POLIWHIRL
    { OBJ_EVENT_GFX_PKMN_POLIWRATH_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_POLIWRATH
    { OBJ_EVENT_GFX_PKMN_ABRA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ABRA
    { OBJ_EVENT_GFX_PKMN_KADABRA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_KADABRA
    { OBJ_EVENT_GFX_PKMN_ALAKAZAM_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ALAKAZAM
    { OBJ_EVENT_GFX_PKMN_MACHOP_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MACHOP
    { OBJ_EVENT_GFX_PKMN_MACHOKE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MACHOKE
    { OBJ_EVENT_GFX_PKMN_MACHAMP_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MACHAMP
    { OBJ_EVENT_GFX_PKMN_BELLSPROUT_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BELLSPROUT
    { OBJ_EVENT_GFX_PKMN_WEEPINBELL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_WEEPINBELL
    { OBJ_EVENT_GFX_PKMN_VICTREEBEL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_VICTREEBEL
    { OBJ_EVENT_GFX_PKMN_TENTACOOL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_TENTACOOL
    { OBJ_EVENT_GFX_PKMN_TENTACRUEL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_TENTACRUEL
    { OBJ_EVENT_GFX_PKMN_GEODUDE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GEODUDE
    { OBJ_EVENT_GFX_PKMN_GRAVELER_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GRAVELER
    { OBJ_EVENT_GFX_PKMN_GOLEM_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GOLEM
    { OBJ_EVENT_GFX_PKMN_PONYTA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PONYTA
    { OBJ_EVENT_GFX_PKMN_RAPIDASH_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_RAPIDASH
    { OBJ_EVENT_GFX_PKMN_SLOWPOKE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SLOWPOKE
    { OBJ_EVENT_GFX_PKMN_SLOWBRO_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SLOWBRO
    { OBJ_EVENT_GFX_PKMN_MAGNEMITE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MAGNEMITE
    { OBJ_EVENT_GFX_PKMN_MAGNETON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MAGNETON
    { OBJ_EVENT_GFX_PKMN_FARFETCHD_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_FARFETCHD
    { OBJ_EVENT_GFX_PKMN_DODUO_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DODUO
    { OBJ_EVENT_GFX_PKMN_DODRIO_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DODRIO
    { OBJ_EVENT_GFX_PKMN_SEEL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SEEL
    { OBJ_EVENT_GFX_PKMN_DEWGONG_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DEWGONG
    { OBJ_EVENT_GFX_PKMN_GRIMER_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GRIMER
    { OBJ_EVENT_GFX_PKMN_MUK_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MUK
    { OBJ_EVENT_GFX_PKMN_SHELLDER_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SHELLDER
    { OBJ_EVENT_GFX_PKMN_CLOYSTER_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CLOYSTER
    { OBJ_EVENT_GFX_PKMN_GASTLY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GASTLY
    { OBJ_EVENT_GFX_PKMN_HAUNTER_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_HAUNTER
    { OBJ_EVENT_GFX_PKMN_GENGAR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GENGAR
    { OBJ_EVENT_GFX_PKMN_ONIX_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ONIX
    { OBJ_EVENT_GFX_PKMN_DROWZEE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DROWZEE
    { OBJ_EVENT_GFX_PKMN_HYPNO_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_HYPNO
    { OBJ_EVENT_GFX_PKMN_KRABBY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_KRABBY
    { OBJ_EVENT_GFX_PKMN_KINGLER_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_KINGLER
    { OBJ_EVENT_GFX_PKMN_VOLTORB_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_VOLTORB
    { OBJ_EVENT_GFX_PKMN_ELECTRODE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ELECTRODE
    { OBJ_EVENT_GFX_PKMN_EXEGGCUTE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_EXEGGCUTE
    { OBJ_EVENT_GFX_PKMN_EXEGGUTOR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_EXEGGUTOR
    { OBJ_EVENT_GFX_PKMN_CUBONE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CUBONE
    { OBJ_EVENT_GFX_PKMN_MAROWAK_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MAROWAK
    { OBJ_EVENT_GFX_PKMN_HITMONLEE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_HITMONLEE
    { OBJ_EVENT_GFX_PKMN_HITMONCHAN_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_HITMONCHAN
    { OBJ_EVENT_GFX_PKMN_LICKITUNG_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LICKITUNG
    { OBJ_EVENT_GFX_PKMN_KOFFING_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_KOFFING
    { OBJ_EVENT_GFX_PKMN_WEEZING_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_WEEZING
    { OBJ_EVENT_GFX_PKMN_RHYHORN_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_RHYHORN
    { OBJ_EVENT_GFX_PKMN_RHYDON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_RHYDON
    { OBJ_EVENT_GFX_PKMN_CHANSEY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CHANSEY
    { OBJ_EVENT_GFX_PKMN_TANGELA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_TANGELA
    { OBJ_EVENT_GFX_PKMN_KANGASKHAN_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_KANGASKHAN
    { OBJ_EVENT_GFX_PKMN_HORSEA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_HORSEA
    { OBJ_EVENT_GFX_PKMN_SEADRA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SEADRA
    { OBJ_EVENT_GFX_PKMN_GOLDEEN_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GOLDEEN
    { OBJ_EVENT_GFX_PKMN_SEAKING_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SEAKING
    { OBJ_EVENT_GFX_PKMN_STARYU_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_STARYU
    { OBJ_EVENT_GFX_PKMN_STARMIE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_STARMIE
    { OBJ_EVENT_GFX_PKMN_MR_MIME_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MR_MIME
    { OBJ_EVENT_GFX_PKMN_SCYTHER_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SCYTHER
    { OBJ_EVENT_GFX_PKMN_JYNX_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_JYNX
    { OBJ_EVENT_GFX_PKMN_ELECTABUZZ_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ELECTABUZZ
    { OBJ_EVENT_GFX_PKMN_MAGMAR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MAGMAR
    { OBJ_EVENT_GFX_PKMN_PINSIR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PINSIR
    { OBJ_EVENT_GFX_PKMN_TAUROS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_TAUROS
    { OBJ_EVENT_GFX_PKMN_MAGIKARP_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MAGIKARP
    { OBJ_EVENT_GFX_PKMN_GYARADOS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GYARADOS
    { OBJ_EVENT_GFX_PKMN_LAPRAS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LAPRAS
    { OBJ_EVENT_GFX_PKMN_DITTO_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DITTO
    { OBJ_EVENT_GFX_PKMN_EEVEE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_EEVEE
    { OBJ_EVENT_GFX_PKMN_VAPOREON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_VAPOREON
    { OBJ_EVENT_GFX_PKMN_JOLTEON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_JOLTEON
    { OBJ_EVENT_GFX_PKMN_FLAREON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_FLAREON
    { OBJ_EVENT_GFX_PKMN_PORYGON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PORYGON
    { OBJ_EVENT_GFX_PKMN_OMANYTE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_OMANYTE
    { OBJ_EVENT_GFX_PKMN_OMASTAR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_OMASTAR
    { OBJ_EVENT_GFX_PKMN_KABUTO_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_KABUTO
    { OBJ_EVENT_GFX_PKMN_KABUTOPS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_KABUTOPS
    { OBJ_EVENT_GFX_PKMN_AERODACTYL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_AERODACTYL
    { OBJ_EVENT_GFX_PKMN_SNORLAX_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SNORLAX
    { OBJ_EVENT_GFX_PKMN_ARTICUNO_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ARTICUNO
    { OBJ_EVENT_GFX_PKMN_ZAPDOS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ZAPDOS
    { OBJ_EVENT_GFX_PKMN_MOLTRES_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MOLTRES
    { OBJ_EVENT_GFX_PKMN_DRATINI_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DRATINI
    { OBJ_EVENT_GFX_PKMN_DRAGONAIR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DRAGONAIR
    { OBJ_EVENT_GFX_PKMN_DRAGONITE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DRAGONITE
    { OBJ_EVENT_GFX_PKMN_MEWTWO_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MEWTWO
    { OBJ_EVENT_GFX_PKMN_MEW_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MEW
    { OBJ_EVENT_GFX_PKMN_CHIKORITA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CHIKORITA
    { OBJ_EVENT_GFX_PKMN_BAYLEEF_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BAYLEEF
    { OBJ_EVENT_GFX_PKMN_BAYLEEF_F_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_CYNDAQUIL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CYNDAQUIL
    { OBJ_EVENT_GFX_PKMN_QUILAVA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_QUILAVA
    { OBJ_EVENT_GFX_PKMN_TYPHLOSION_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_TYPHLOSION
    { OBJ_EVENT_GFX_PKMN_TOTODILE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_TOTODILE
    { OBJ_EVENT_GFX_PKMN_CROCONAW_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CROCONAW
    { OBJ_EVENT_GFX_PKMN_FERALIGATR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_FERALIGATR
    { OBJ_EVENT_GFX_PKMN_SENTRET_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SENTRET
    { OBJ_EVENT_GFX_PKMN_FURRET_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_FURRET
    { OBJ_EVENT_GFX_PKMN_HOOTHOOT_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_HOOTHOOT
    { OBJ_EVENT_GFX_PKMN_NOCTOWL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_NOCTOWL
    { OBJ_EVENT_GFX_PKMN_LEDYBA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LEDYBA
    { OBJ_EVENT_GFX_PKMN_LEDIAN_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LEDIAN
    { OBJ_EVENT_GFX_PKMN_SPINARAK_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SPINARAK
    { OBJ_EVENT_GFX_PKMN_ARIADOS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ARIADOS
    { OBJ_EVENT_GFX_PKMN_CROBAT_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CROBAT
    { OBJ_EVENT_GFX_PKMN_CHINCHOU_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CHINCHOU
    { OBJ_EVENT_GFX_PKMN_LANTURN_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LANTURN
    { OBJ_EVENT_GFX_PKMN_PICHU_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PICHU
    { OBJ_EVENT_GFX_PKMN_CLEFFA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CLEFFA
    { OBJ_EVENT_GFX_PKMN_IGGLYBUFF_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_IGGLYBUFF
    { OBJ_EVENT_GFX_PKMN_TOGEPI_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_TOGEPI
    { OBJ_EVENT_GFX_PKMN_TOGETIC_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_TOGETIC
    { OBJ_EVENT_GFX_PKMN_NATU_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_NATU
    { OBJ_EVENT_GFX_PKMN_XATU_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_XATU
    { OBJ_EVENT_GFX_PKMN_MAREEP_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MAREEP
    { OBJ_EVENT_GFX_PKMN_FLAAFFY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_FLAAFFY
    { OBJ_EVENT_GFX_PKMN_AMPHAROS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_AMPHAROS
    { OBJ_EVENT_GFX_PKMN_BELLOSSOM_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BELLOSSOM
    { OBJ_EVENT_GFX_PKMN_MARILL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MARILL
    { OBJ_EVENT_GFX_PKMN_AZUMARILL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_AZUMARILL
    { OBJ_EVENT_GFX_PKMN_SUDOWOODO_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SUDOWOODO
    { OBJ_EVENT_GFX_PKMN_POLITOED_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_POLITOED
    { OBJ_EVENT_GFX_PKMN_HOPPIP_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_HOPPIP
    { OBJ_EVENT_GFX_PKMN_SKIPLOOM_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SKIPLOOM
    { OBJ_EVENT_GFX_PKMN_JUMPLUFF_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_JUMPLUFF
    { OBJ_EVENT_GFX_PKMN_AIPOM_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_AIPOM
    { OBJ_EVENT_GFX_PKMN_SUNKERN_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SUNKERN
    { OBJ_EVENT_GFX_PKMN_SUNFLORA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SUNFLORA
    { OBJ_EVENT_GFX_PKMN_YANMA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_YANMA
    { OBJ_EVENT_GFX_PKMN_WOOPER_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_WOOPER
    { OBJ_EVENT_GFX_PKMN_QUAGSIRE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_QUAGSIRE
    { OBJ_EVENT_GFX_PKMN_ESPEON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ESPEON
    { OBJ_EVENT_GFX_PKMN_UMBREON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_UMBREON
    { OBJ_EVENT_GFX_PKMN_MURKROW_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MURKROW
    { OBJ_EVENT_GFX_PKMN_SLOWKING_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SLOWKING
    { OBJ_EVENT_GFX_PKMN_MISDREAVUS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MISDREAVUS
    { OBJ_EVENT_GFX_PKMN_UNOWN_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_UNOWN
    { OBJ_EVENT_GFX_PKMN_WOBBUFFET_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_WOBBUFFET
    { OBJ_EVENT_GFX_PKMN_WOBBUFFET_F_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_GIRAFARIG_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GIRAFARIG
    { OBJ_EVENT_GFX_PKMN_PINECO_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PINECO
    { OBJ_EVENT_GFX_PKMN_FORRETRESS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_FORRETRESS
    { OBJ_EVENT_GFX_PKMN_DUNSPARCE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DUNSPARCE
    { OBJ_EVENT_GFX_PKMN_GLIGAR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GLIGAR
    { OBJ_EVENT_GFX_PKMN_STEELIX_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_STEELIX
    { OBJ_EVENT_GFX_PKMN_STEELIX_F_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_SNUBBULL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SNUBBULL
    { OBJ_EVENT_GFX_PKMN_GRANBULL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GRANBULL
    { OBJ_EVENT_GFX_PKMN_QWILFISH_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_QWILFISH
    { OBJ_EVENT_GFX_PKMN_SCIZOR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SCIZOR
    { OBJ_EVENT_GFX_PKMN_SHUCKLE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SHUCKLE
    { OBJ_EVENT_GFX_PKMN_HERACROSS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_HERACROSS
    { OBJ_EVENT_GFX_PKMN_HERACROSS_F_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_SNEASEL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SNEASEL
    { OBJ_EVENT_GFX_PKMN_TEDDIURSA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_TEDDIURSA
    { OBJ_EVENT_GFX_PKMN_URSARING_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_URSARING
    { OBJ_EVENT_GFX_PKMN_SLUGMA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SLUGMA
    { OBJ_EVENT_GFX_PKMN_MAGCARGO_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MAGCARGO
    { OBJ_EVENT_GFX_PKMN_SWINUB_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SWINUB
    { OBJ_EVENT_GFX_PKMN_PILOSWINE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PILOSWINE
    { OBJ_EVENT_GFX_PKMN_CORSOLA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CORSOLA
    { OBJ_EVENT_GFX_PKMN_REMORAID_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_REMORAID
    { OBJ_EVENT_GFX_PKMN_OCTILLERY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_OCTILLERY
    { OBJ_EVENT_GFX_PKMN_DELIBIRD_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DELIBIRD
    { OBJ_EVENT_GFX_PKMN_MANTINE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MANTINE
    { OBJ_EVENT_GFX_PKMN_SKARMORY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SKARMORY
    { OBJ_EVENT_GFX_PKMN_HOUNDOUR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_HOUNDOUR
    { OBJ_EVENT_GFX_PKMN_HOUNDOOM_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_HOUNDOOM
    { OBJ_EVENT_GFX_PKMN_KINGDRA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_KINGDRA
    { OBJ_EVENT_GFX_PKMN_PHANPY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PHANPY
    { OBJ_EVENT_GFX_PKMN_DONPHAN_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DONPHAN
    { OBJ_EVENT_GFX_PKMN_PORYGON2_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PORYGON2
    { OBJ_EVENT_GFX_PKMN_STANTLER_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_STANTLER
    { OBJ_EVENT_GFX_PKMN_SMEARGLE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SMEARGLE
    { OBJ_EVENT_GFX_PKMN_TYROGUE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_TYROGUE
    { OBJ_EVENT_GFX_PKMN_HITMONTOP_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_HITMONTOP
    { OBJ_EVENT_GFX_PKMN_SMOOCHUM_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SMOOCHUM
    { OBJ_EVENT_GFX_PKMN_ELEKID_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ELEKID
    { OBJ_EVENT_GFX_PKMN_MAGBY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MAGBY
    { OBJ_EVENT_GFX_PKMN_MILTANK_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MILTANK
    { OBJ_EVENT_GFX_PKMN_BLISSEY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BLISSEY
    { OBJ_EVENT_GFX_PKMN_RAIKOU_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_RAIKOU
    { OBJ_EVENT_GFX_PKMN_ENTEI_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ENTEI
    { OBJ_EVENT_GFX_PKMN_SUICUNE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SUICUNE
    { OBJ_EVENT_GFX_PKMN_LARVITAR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LARVITAR
    { OBJ_EVENT_GFX_PKMN_PUPITAR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PUPITAR
    { OBJ_EVENT_GFX_PKMN_TYRANITAR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_TYRANITAR
    { OBJ_EVENT_GFX_PKMN_LUGIA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LUGIA
    { OBJ_EVENT_GFX_PKMN_HO_OH_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_HO_OH
    { OBJ_EVENT_GFX_PKMN_CELEBI_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CELEBI
    { OBJ_EVENT_GFX_PKMN_TREECKO_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_TREECKO
    { OBJ_EVENT_GFX_PKMN_GROVYLE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GROVYLE
    { OBJ_EVENT_GFX_PKMN_SCEPTILE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SCEPTILE
    { OBJ_EVENT_GFX_PKMN_TORCHIC_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_TORCHIC
    { OBJ_EVENT_GFX_PKMN_COMBUSKEN_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_COMBUSKEN
    { OBJ_EVENT_GFX_PKMN_BLAZIKEN_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BLAZIKEN
    { OBJ_EVENT_GFX_PKMN_MUDKIP_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MUDKIP
    { OBJ_EVENT_GFX_PKMN_MARSHTOMP_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MARSHTOMP
    { OBJ_EVENT_GFX_PKMN_SWAMPERT_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SWAMPERT
    { OBJ_EVENT_GFX_PKMN_POOCHYENA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_POOCHYENA
    { OBJ_EVENT_GFX_PKMN_MIGHTYENA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MIGHTYENA
    { OBJ_EVENT_GFX_PKMN_ZIGZAGOON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ZIGZAGOON
    { OBJ_EVENT_GFX_PKMN_LINOONE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LINOONE
    { OBJ_EVENT_GFX_PKMN_WURMPLE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_WURMPLE
    { OBJ_EVENT_GFX_PKMN_SILCOON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SILCOON
    { OBJ_EVENT_GFX_PKMN_BEAUTIFLY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BEAUTIFLY
    { OBJ_EVENT_GFX_PKMN_CASCOON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CASCOON
    { OBJ_EVENT_GFX_PKMN_DUSTOX_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DUSTOX
    { OBJ_EVENT_GFX_PKMN_LOTAD_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LOTAD
    { OBJ_EVENT_GFX_PKMN_LOMBRE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LOMBRE
    { OBJ_EVENT_GFX_PKMN_LUDICOLO_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LUDICOLO
    { OBJ_EVENT_GFX_PKMN_SEEDOT_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SEEDOT
    { OBJ_EVENT_GFX_PKMN_NUZLEAF_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_NUZLEAF
    { OBJ_EVENT_GFX_PKMN_SHIFTRY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SHIFTRY
    { OBJ_EVENT_GFX_PKMN_TAILLOW_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_TAILLOW
    { OBJ_EVENT_GFX_PKMN_SWELLOW_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SWELLOW
    { OBJ_EVENT_GFX_PKMN_WINGULL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_WINGULL
    { OBJ_EVENT_GFX_PKMN_PELIPPER_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PELIPPER
    { OBJ_EVENT_GFX_PKMN_RALTS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_RALTS
    { OBJ_EVENT_GFX_PKMN_KIRLIA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_KIRLIA
    { OBJ_EVENT_GFX_PKMN_GARDEVOIR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GARDEVOIR
    { OBJ_EVENT_GFX_PKMN_SURSKIT_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SURSKIT
    { OBJ_EVENT_GFX_PKMN_MASQUERAIN_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MASQUERAIN
    { OBJ_EVENT_GFX_PKMN_SHROOMISH_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SHROOMISH
    { OBJ_EVENT_GFX_PKMN_BRELOOM_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BRELOOM
    { OBJ_EVENT_GFX_PKMN_SLAKOTH_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SLAKOTH
    { OBJ_EVENT_GFX_PKMN_VIGOROTH_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_VIGOROTH
    { OBJ_EVENT_GFX_PKMN_SLAKING_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SLAKING
    { OBJ_EVENT_GFX_PKMN_NINCADA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_NINCADA
    { OBJ_EVENT_GFX_PKMN_NINJASK_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_NINJASK
    { OBJ_EVENT_GFX_PKMN_SHEDINJA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SHEDINJA
    { OBJ_EVENT_GFX_PKMN_WHISMUR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_WHISMUR
    { OBJ_EVENT_GFX_PKMN_LOUDRED_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LOUDRED
    { OBJ_EVENT_GFX_PKMN_EXPLOUD_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_EXPLOUD
    { OBJ_EVENT_GFX_PKMN_MAKUHITA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MAKUHITA
    { OBJ_EVENT_GFX_PKMN_HARIYAMA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_HARIYAMA
    { OBJ_EVENT_GFX_PKMN_AZURILL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_AZURILL
    { OBJ_EVENT_GFX_PKMN_NOSEPASS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_NOSEPASS
    { OBJ_EVENT_GFX_PKMN_SKITTY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SKITTY
    { OBJ_EVENT_GFX_PKMN_DELCATTY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DELCATTY
    { OBJ_EVENT_GFX_PKMN_SABLEYE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SABLEYE
    { OBJ_EVENT_GFX_PKMN_MAWILE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MAWILE
    { OBJ_EVENT_GFX_PKMN_ARON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ARON
    { OBJ_EVENT_GFX_PKMN_LAIRON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LAIRON
    { OBJ_EVENT_GFX_PKMN_AGGRON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_AGGRON
    { OBJ_EVENT_GFX_PKMN_MEDITITE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MEDITITE
    { OBJ_EVENT_GFX_PKMN_MEDICHAM_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MEDICHAM
    { OBJ_EVENT_GFX_PKMN_ELECTRIKE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ELECTRIKE
    { OBJ_EVENT_GFX_PKMN_MANECTRIC_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MANECTRIC
    { OBJ_EVENT_GFX_PKMN_PLUSLE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PLUSLE
    { OBJ_EVENT_GFX_PKMN_MINUN_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MINUN
    { OBJ_EVENT_GFX_PKMN_VOLBEAT_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_VOLBEAT
    { OBJ_EVENT_GFX_PKMN_ILLUMISE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ILLUMISE
    { OBJ_EVENT_GFX_PKMN_ROSELIA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ROSELIA
    { OBJ_EVENT_GFX_PKMN_GULPIN_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GULPIN
    { OBJ_EVENT_GFX_PKMN_SWALOT_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SWALOT
    { OBJ_EVENT_GFX_PKMN_CARVANHA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CARVANHA
    { OBJ_EVENT_GFX_PKMN_SHARPEDO_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SHARPEDO
    { OBJ_EVENT_GFX_PKMN_WAILMER_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_WAILMER
    { OBJ_EVENT_GFX_PKMN_WAILORD_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_WAILORD
    { OBJ_EVENT_GFX_PKMN_NUMEL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_NUMEL
    { OBJ_EVENT_GFX_PKMN_CAMERUPT_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CAMERUPT
    { OBJ_EVENT_GFX_PKMN_TORKOAL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_TORKOAL
    { OBJ_EVENT_GFX_PKMN_SPOINK_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SPOINK
    { OBJ_EVENT_GFX_PKMN_GRUMPIG_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GRUMPIG
    { OBJ_EVENT_GFX_PKMN_SPINDA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SPINDA
    { OBJ_EVENT_GFX_PKMN_TRAPINCH_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_TRAPINCH
    { OBJ_EVENT_GFX_PKMN_VIBRAVA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_VIBRAVA
    { OBJ_EVENT_GFX_PKMN_FLYGON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_FLYGON
    { OBJ_EVENT_GFX_PKMN_CACNEA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CACNEA
    { OBJ_EVENT_GFX_PKMN_CACTURNE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CACTURNE
    { OBJ_EVENT_GFX_PKMN_SWABLU_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SWABLU
    { OBJ_EVENT_GFX_PKMN_ALTARIA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ALTARIA
    { OBJ_EVENT_GFX_PKMN_ZANGOOSE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ZANGOOSE
    { OBJ_EVENT_GFX_PKMN_SEVIPER_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SEVIPER
    { OBJ_EVENT_GFX_PKMN_LUNATONE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LUNATONE
    { OBJ_EVENT_GFX_PKMN_SOLROCK_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SOLROCK
    { OBJ_EVENT_GFX_PKMN_BARBOACH_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BARBOACH
    { OBJ_EVENT_GFX_PKMN_WHISCASH_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_WHISCASH
    { OBJ_EVENT_GFX_PKMN_CORPHISH_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CORPHISH
    { OBJ_EVENT_GFX_PKMN_CRAWDAUNT_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CRAWDAUNT
    { OBJ_EVENT_GFX_PKMN_BALTOY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BALTOY
    { OBJ_EVENT_GFX_PKMN_CLAYDOL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CLAYDOL
    { OBJ_EVENT_GFX_PKMN_LILEEP_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LILEEP
    { OBJ_EVENT_GFX_PKMN_CRADILY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CRADILY
    { OBJ_EVENT_GFX_PKMN_ANORITH_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ANORITH
    { OBJ_EVENT_GFX_PKMN_ARMALDO_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ARMALDO
    { OBJ_EVENT_GFX_PKMN_FEEBAS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_FEEBAS
    { OBJ_EVENT_GFX_PKMN_MILOTIC_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MILOTIC
    { OBJ_EVENT_GFX_PKMN_CASTFORM_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CASTFORM
    { OBJ_EVENT_GFX_PKMN_KECLEON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_KECLEON
    { OBJ_EVENT_GFX_PKMN_SHUPPET_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SHUPPET
    { OBJ_EVENT_GFX_PKMN_BANETTE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BANETTE
    { OBJ_EVENT_GFX_PKMN_DUSKULL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DUSKULL
    { OBJ_EVENT_GFX_PKMN_DUSCLOPS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DUSCLOPS
    { OBJ_EVENT_GFX_PKMN_TROPIUS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_TROPIUS
    { OBJ_EVENT_GFX_PKMN_CHIMECHO_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CHIMECHO
    { OBJ_EVENT_GFX_PKMN_ABSOL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ABSOL
    { OBJ_EVENT_GFX_PKMN_WYNAUT_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_WYNAUT
    { OBJ_EVENT_GFX_PKMN_SNORUNT_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SNORUNT
    { OBJ_EVENT_GFX_PKMN_GLALIE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GLALIE
    { OBJ_EVENT_GFX_PKMN_SPHEAL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SPHEAL
    { OBJ_EVENT_GFX_PKMN_SEALEO_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SEALEO
    { OBJ_EVENT_GFX_PKMN_WALREIN_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_WALREIN
    { OBJ_EVENT_GFX_PKMN_CLAMPERL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CLAMPERL
    { OBJ_EVENT_GFX_PKMN_HUNTAIL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_HUNTAIL
    { OBJ_EVENT_GFX_PKMN_GOREBYSS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GOREBYSS
    { OBJ_EVENT_GFX_PKMN_RELICANTH_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_RELICANTH
    { OBJ_EVENT_GFX_PKMN_LUVDISC_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LUVDISC
    { OBJ_EVENT_GFX_PKMN_BAGON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BAGON
    { OBJ_EVENT_GFX_PKMN_SHELGON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SHELGON
    { OBJ_EVENT_GFX_PKMN_SALAMENCE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SALAMENCE
    { OBJ_EVENT_GFX_PKMN_BELDUM_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BELDUM
    { OBJ_EVENT_GFX_PKMN_METANG_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_METANG
    { OBJ_EVENT_GFX_PKMN_METAGROSS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_METAGROSS
    { OBJ_EVENT_GFX_PKMN_REGIROCK_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_REGIROCK
    { OBJ_EVENT_GFX_PKMN_REGICE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_REGICE
    { OBJ_EVENT_GFX_PKMN_REGISTEEL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_REGISTEEL
    { OBJ_EVENT_GFX_PKMN_LATIAS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LATIAS
    { OBJ_EVENT_GFX_PKMN_LATIOS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LATIOS
    { OBJ_EVENT_GFX_PKMN_KYOGRE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_KYOGRE
    { OBJ_EVENT_GFX_PKMN_GROUDON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GROUDON
    { OBJ_EVENT_GFX_PKMN_RAYQUAZA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_RAYQUAZA
    { OBJ_EVENT_GFX_PKMN_JIRACHI_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_JIRACHI
    { OBJ_EVENT_GFX_PKMN_DEOXYS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DEOXYS
    { OBJ_EVENT_GFX_PKMN_TURTWIG_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_TURTWIG
    { OBJ_EVENT_GFX_PKMN_GROTLE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GROTLE
    { OBJ_EVENT_GFX_PKMN_TORTERRA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_TORTERRA
    { OBJ_EVENT_GFX_PKMN_CHIMCHAR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CHIMCHAR
    { OBJ_EVENT_GFX_PKMN_MONFERNO_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MONFERNO
    { OBJ_EVENT_GFX_PKMN_INFERNAPE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_INFERNAPE
    { OBJ_EVENT_GFX_PKMN_PIPLUP_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PIPLUP
    { OBJ_EVENT_GFX_PKMN_PRINPLUP_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PRINPLUP
    { OBJ_EVENT_GFX_PKMN_EMPOLEON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_EMPOLEON
    { OBJ_EVENT_GFX_PKMN_STARLY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_STARLY
    { OBJ_EVENT_GFX_PKMN_STARAVIA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_STARAVIA
    { OBJ_EVENT_GFX_PKMN_STARAPTOR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_STARAPTOR
    { OBJ_EVENT_GFX_PKMN_BIDOOF_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BIDOOF
    { OBJ_EVENT_GFX_PKMN_BIBAREL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BIBAREL
    { OBJ_EVENT_GFX_PKMN_KRICKETOT_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_KRICKETOT
    { OBJ_EVENT_GFX_PKMN_KRICKETUNE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_KRICKETUNE
    { OBJ_EVENT_GFX_PKMN_SHINX_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SHINX
    { OBJ_EVENT_GFX_PKMN_LUXIO_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LUXIO
    { OBJ_EVENT_GFX_PKMN_LUXRAY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LUXRAY
    { OBJ_EVENT_GFX_PKMN_BUDEW_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BUDEW
    { OBJ_EVENT_GFX_PKMN_ROSERADE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ROSERADE
    { OBJ_EVENT_GFX_PKMN_CRANIDOS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CRANIDOS
    { OBJ_EVENT_GFX_PKMN_RAMPARDOS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_RAMPARDOS
    { OBJ_EVENT_GFX_PKMN_SHIELDON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SHIELDON
    { OBJ_EVENT_GFX_PKMN_BASTIODON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BASTIODON
    { OBJ_EVENT_GFX_PKMN_BURMY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BURMY
    { OBJ_EVENT_GFX_PKMN_WORMADAM_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_WORMADAM
    { OBJ_EVENT_GFX_PKMN_MOTHIM_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MOTHIM
    { OBJ_EVENT_GFX_PKMN_COMBEE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_COMBEE
    { OBJ_EVENT_GFX_PKMN_COMBEE_F_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_VESPIQUEN_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_VESPIQUEN
    { OBJ_EVENT_GFX_PKMN_PACHIRISU_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PACHIRISU
    { OBJ_EVENT_GFX_PKMN_BUIZEL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BUIZEL
    { OBJ_EVENT_GFX_PKMN_FLOATZEL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_FLOATZEL
    { OBJ_EVENT_GFX_PKMN_CHERUBI_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CHERUBI
    { OBJ_EVENT_GFX_PKMN_CHERRIM_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CHERRIM
    { OBJ_EVENT_GFX_PKMN_SHELLOS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SHELLOS
    { OBJ_EVENT_GFX_PKMN_GASTRODON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GASTRODON
    { OBJ_EVENT_GFX_PKMN_AMBIPOM_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_AMBIPOM
    { OBJ_EVENT_GFX_PKMN_DRIFLOON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DRIFLOON
    { OBJ_EVENT_GFX_PKMN_DRIFBLIM_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DRIFBLIM
    { OBJ_EVENT_GFX_PKMN_BUNEARY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BUNEARY
    { OBJ_EVENT_GFX_PKMN_LOPUNNY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LOPUNNY
    { OBJ_EVENT_GFX_PKMN_MISMAGIUS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MISMAGIUS
    { OBJ_EVENT_GFX_PKMN_HONCHKROW_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_HONCHKROW
    { OBJ_EVENT_GFX_PKMN_GLAMEOW_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GLAMEOW
    { OBJ_EVENT_GFX_PKMN_PURUGLY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PURUGLY
    { OBJ_EVENT_GFX_PKMN_CHINGLING_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CHINGLING
    { OBJ_EVENT_GFX_PKMN_STUNKY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_STUNKY
    { OBJ_EVENT_GFX_PKMN_SKUNTANK_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SKUNTANK
    { OBJ_EVENT_GFX_PKMN_BRONZOR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BRONZOR
    { OBJ_EVENT_GFX_PKMN_BRONZONG_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BRONZONG
    { OBJ_EVENT_GFX_PKMN_BONSLY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_BONSLY
    { OBJ_EVENT_GFX_PKMN_MIMEJR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MIMEJR
    { OBJ_EVENT_GFX_PKMN_HAPPINY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_HAPPINY
    { OBJ_EVENT_GFX_PKMN_CHATOT_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CHATOT
    { OBJ_EVENT_GFX_PKMN_SPIRITOMB_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SPIRITOMB
    { OBJ_EVENT_GFX_PKMN_GIBLE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GIBLE
    { OBJ_EVENT_GFX_PKMN_GABITE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GABITE
    { OBJ_EVENT_GFX_PKMN_GARCHOMP_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GARCHOMP
    { OBJ_EVENT_GFX_PKMN_MUNCHLAX_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MUNCHLAX
    { OBJ_EVENT_GFX_PKMN_RIOLU_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_RIOLU
    { OBJ_EVENT_GFX_PKMN_LUCARIO_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LUCARIO
    { OBJ_EVENT_GFX_PKMN_HIPPOPOTAS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_HIPPOPOTAS
    { OBJ_EVENT_GFX_PKMN_HIPPOPOTAS_F_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_HIPPOWDON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_HIPPOWDON
    { OBJ_EVENT_GFX_PKMN_HIPPOWDON_F_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny female
    { OBJ_EVENT_GFX_PKMN_SKORUPI_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SKORUPI
    { OBJ_EVENT_GFX_PKMN_DRAPION_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DRAPION
    { OBJ_EVENT_GFX_PKMN_CROAGUNK_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CROAGUNK
    { OBJ_EVENT_GFX_PKMN_TOXICROAK_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_TOXICROAK
    { OBJ_EVENT_GFX_PKMN_CARNIVINE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CARNIVINE
    { OBJ_EVENT_GFX_PKMN_FINNEON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_FINNEON
    { OBJ_EVENT_GFX_PKMN_LUMINEON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LUMINEON
    { OBJ_EVENT_GFX_PKMN_MANTYKE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MANTYKE
    { OBJ_EVENT_GFX_PKMN_SNOVER_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SNOVER
    { OBJ_EVENT_GFX_PKMN_ABOMASNOW_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ABOMASNOW
    { OBJ_EVENT_GFX_PKMN_WEAVILE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_WEAVILE
    { OBJ_EVENT_GFX_PKMN_MAGNEZONE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MAGNEZONE
    { OBJ_EVENT_GFX_PKMN_LICKILICKY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LICKILICKY
    { OBJ_EVENT_GFX_PKMN_RHYPERIOR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_RHYPERIOR
    { OBJ_EVENT_GFX_PKMN_TANGROWTH_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_TANGROWTH
    { OBJ_EVENT_GFX_PKMN_ELECTIVIRE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ELECTIVIRE
    { OBJ_EVENT_GFX_PKMN_MAGMORTAR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MAGMORTAR
    { OBJ_EVENT_GFX_PKMN_TOGEKISS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_TOGEKISS
    { OBJ_EVENT_GFX_PKMN_LEAFEON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_LEAFEON
    { OBJ_EVENT_GFX_PKMN_GLACEON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GLACEON
    { OBJ_EVENT_GFX_PKMN_GLISCOR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GLISCOR
    { OBJ_EVENT_GFX_PKMN_MAMOSWINE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MAMOSWINE
    { OBJ_EVENT_GFX_PKMN_PORYGON_Z_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PORYGON_Z
    { OBJ_EVENT_GFX_PKMN_GALLADE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GALLADE
    { OBJ_EVENT_GFX_PKMN_PROBOPASS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PROBOPASS
    { OBJ_EVENT_GFX_PKMN_DUSKNOIR_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DUSKNOIR
    { OBJ_EVENT_GFX_PKMN_FROSLASS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_FROSLASS
    { OBJ_EVENT_GFX_PKMN_ROTOM_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ROTOM
    { OBJ_EVENT_GFX_PKMN_UXIE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_UXIE
    { OBJ_EVENT_GFX_PKMN_MESPRIT_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MESPRIT
    { OBJ_EVENT_GFX_PKMN_AZELF_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_AZELF
    { OBJ_EVENT_GFX_PKMN_DIALGA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DIALGA
    { OBJ_EVENT_GFX_PKMN_PALKIA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PALKIA
    { OBJ_EVENT_GFX_PKMN_HEATRAN_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_HEATRAN
    { OBJ_EVENT_GFX_PKMN_REGIGIGAS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_REGIGIGAS
    { OBJ_EVENT_GFX_PKMN_GIRATINA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_GIRATINA
    { OBJ_EVENT_GFX_PKMN_CRESSELIA_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_CRESSELIA
    { OBJ_EVENT_GFX_PKMN_PHIONE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_PHIONE
    { OBJ_EVENT_GFX_PKMN_MANAPHY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_MANAPHY
    { OBJ_EVENT_GFX_PKMN_DARKRAI_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_DARKRAI
    { OBJ_EVENT_GFX_PKMN_SHAYMIN_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_SHAYMIN
    { OBJ_EVENT_GFX_PKMN_ARCEUS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny SPECIES_ARCEUS
    { OBJ_EVENT_GFX_PKMN_GIRATINA_O_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FIGHTING_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FLYING_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_POISON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GROUND_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ROCK_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_BUG_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GHOST_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_STEEL_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FAIRY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_FIRE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_WATER_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_GRASS_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ELECTRIC_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_PSYCHIC_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_ICE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_DRAGON_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ARCEUS_DARK_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_DEOXYS_ATTACK_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_DEOXYS_DEFENSE_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_DEOXYS_SPEED_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_BURMY_SANDY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_BURMY_TRASH_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_WORMADAM_SANDY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_WORMADAM_TRASH_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_SHELLOS_EAST_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_GASTRODON_EAST_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ROTOM_HEAT_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ROTOM_WASH_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ROTOM_FROST_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ROTOM_FAN_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_ROTOM_MOW_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { OBJ_EVENT_GFX_PKMN_SHAYMIN_SKY_SHINY, 0x1, 0x1, 0x1, 0x1, 0x0 },  // shiny alt form
    { 0xffff, 0x0, 0x0, 0x0, 0x0, 0x0 }
};

const BerryGraphicsData gBerryGraphicsTable[] = {
    { 0x1001, 0x1002, 0x1003 },
    { 0x1004, 0x1005, 0x1006 },
    { 0x1007, 0x1008, 0x1009 },
    { 0x100A, 0x100B, 0x100C },
    { 0x100D, 0x100E, (0x1000 + 0xf) },
    { 0x1010, 0x1011, 0x1012 },
    { 0x1013, 0x1014, 0x1015 },
    { 0x1016, 0x1017, 0x1018 },
    { 0x1019, 0x101A, 0x101B },
    { 0x101C, 0x101D, 0x101E },
    { (0x1000 + 0x1f), 0x1020, 0x1021 },
    { 0x1022, 0x1023, 0x1024 },
    { 0x1025, 0x1026, 0x1027 },
    { 0x1028, 0x1029, 0x102A },
    { 0x102B, 0x102C, 0x102D },
    { 0x102E, 0x1000 + 0x2f, 0x1030 },
    { 0x1031, 0x1032, 0x1033 },
    { 0x1034, 0x1035, 0x1036 },
    { 0x1037, 0x1038, 0x1039 },
    { 0x103A, 0x103B, 0x103C },
    { 0x103D, 0x103E, (0x1000 + 0x3f) },
    { 0x1040, 0x1041, 0x1042 },
    { 0x1043, 0x1044, 0x1045 },
    { 0x1046, 0x1047, 0x1048 },
    { 0x1049, 0x104A, 0x104B },
    { 0x104C, 0x104D, 0x104E },
    { (0x1000 + 0x4f), 0x1050, 0x1051 },
    { 0x1052, 0x1053, 0x1054 },
    { 0x1055, 0x1056, 0x1057 },
    { 0x1058, 0x1059, 0x105A },
    { 0x105B, 0x105C, 0x105D },
    { 0x105E, 0x1000 + 0x5f, 0x1060 },
    { 0x1061, 0x1062, 0x1063 },
    { 0x1064, 0x1065, 0x1066 },
    { 0x1067, 0x1068, 0x1069 },
    { 0x106A, 0x106B, 0x106C },
    { 0x106D, 0x106E, (0x1000 + 0x6f) },
    { 0x1070, 0x1071, 0x1072 },
    { 0x1073, 0x1074, 0x1075 },
    { 0x1076, 0x1077, 0x1078 },
    { 0x1079, 0x107A, 0x107B },
    { 0x107C, 0x107D, 0x107E },
    { (0x1000 + 0x7f), 0x1080, 0x1081 },
    { 0x1082, 0x1083, 0x1084 },
    { 0x1085, 0x1086, 0x1087 },
    { 0x1088, 0x1089, 0x108A },
    { 0x108B, 0x108C, 0x108D },
    { 0x108E, 0x1000 + 0x8f, 0x1090 },
    { 0x1091, 0x1092, 0x1093 },
    { 0x1094, 0x1095, 0x1096 },
    { 0x1097, 0x1098, 0x1099 },
    { 0x109A, 0x109B, 0x109C },
    { 0x109D, 0x109E, (0x1000 + 0x9f) },
    { 0x10A0, 0x10A1, 0x10A2 },
    { 0x10A3, 0x10A4, 0x10A5 },
    { 0x10A6, 0x10A7, 0x10A8 },
    { 0x10A9, 0x10AA, 0x10AB },
    { 0x10AC, 0x10AD, 0x10AE },
    { (0x1000 + 0xaf), 0x10B0, 0x10B1 },
    { 0x10B2, 0x10B3, 0x10B4 },
    { 0x10B5, 0x10B6, 0x10B7 },
    { 0x10B8, 0x10B9, 0x10BA },
    { 0x10BB, 0x10BC, 0x10BD },
    { 0x10BE, 0x1000 + 0xbf, 0x10C0 }
};

const UnkStruct_ov5_021EC700 Unk_ov5_021FB51C[] = {
    {
        0x5B,
        {
            0x0,
            0x0,
            (FX32_ONE * 6) - (FX32_ONE * 6) - (FX32_ONE * 2),
        },
    },
    {
        0x5C,
        {
            0x0,
            0x0,
            (FX32_ONE * 6) - (FX32_ONE * 6) - (FX32_ONE * 2),
        },
    },
    {
        0x5D,
        {
            0x0,
            0x0,
            (FX32_ONE * 6) - (FX32_ONE * 6) - (FX32_ONE * 2),
        },
    },
    {
        0x5E,
        {
            0x0,
            0x0,
            (FX32_ONE * 6) - (FX32_ONE * 6) - (FX32_ONE * 2),
        },
    },
    {
        0x5f,
        {
            0x0,
            0x0,
            (FX32_ONE * 6) - (FX32_ONE * 6) - (FX32_ONE * 2),
        },
    },
    {
        0x60,
        {
            0x0,
            0x0,
            (FX32_ONE * 6) - (FX32_ONE * 6) - (FX32_ONE * 2),
        },
    },
    {
        0xB7,
        {
            0x0,
            0x0,
            (FX32_ONE * 6) - (FX32_ONE * 6),
        },
    },
    {
        0xD1,
        {
            0x0,
            0x0,
            (FX32_ONE * 6) - (FX32_ONE * 6),
        },
    },
    {
        0x106,
        {
            0x0,
            0x0,
            (FX32_ONE * 6) - (FX32_ONE * 6),
        },
    },
    {
        0xffff,
        {
            0x0,
            0x0,
            0x0,
        },
    }
};
