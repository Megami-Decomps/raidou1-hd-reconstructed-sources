#pragma once
#include "types.h"

typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct tagTITLE_TEST_WORK tagTITLE_TEST_WORK;
typedef struct tagTITLE_T_EFF_CB tagTITLE_T_EFF_CB;
typedef struct tagTITLE_T_EFF_PRT_CB tagTITLE_T_EFF_PRT_CB;
typedef struct tagTITLE_T_EFF_PRT_WORK tagTITLE_T_EFF_PRT_WORK;
typedef struct tagTITLE_T_EFF_WORK tagTITLE_T_EFF_WORK;
typedef struct tagTITLE_WORK tagTITLE_WORK;

struct tagTITLE_T_EFF_CB {
    sdfVector4_t pos[2];
    u32 stat;
    s32 count;
    s32 max;
    s32 dummy32[1];
};

struct tagTITLE_T_EFF_WORK {
    tagTITLE_T_EFF_CB *cb[1024];
    sdfVector4_t pos;
    s32 stat;
};

struct tagTITLE_T_EFF_PRT_CB {
    sdfVector4_t pos;
    sdfVector4_t vec;
    s32 stat;
    s32 count;
    s32 maxCount;
    s32 dummy[1];
};

struct tagTITLE_T_EFF_PRT_WORK {
    tagTITLE_T_EFF_PRT_CB *cb[1024];
    sdfVector4_t pos;
    sdfVector4_t vec;
    s32 stat;
};

struct tagTITLE_TEST_WORK {
    u8 step;
    u8 stat;
    s16 count;
    dds3Basic_t *scene;
    dds3Basic_t *camera;
    sdfVector4_t camEyePos;
    sdfVector4_t camTgtPos;
    sdfVector4_t pad;
    f32 length;
    f32 degree;
    dds3Basic_t *unit_s;
    dds3Basic_t *unit;
    sdfVector4_t rot;
    sdfVector4_t scl;
    sdfVector4_t pos;
    u8 modelStat;
    u8 modelActId;
    dds3ModelHandle_t *hModel;
    dds3ModelHandle_t *hModel_s;
    tagTITLE_T_EFF_WORK *eff;
    tagTITLE_T_EFF_PRT_WORK *effPrt;
};

struct tagTITLE_WORK {
    dds3ProcessID_t *procDraw;
    dds3ProcessID_t *procNameEntry;
    u8 step;
    u8 stat;
    s16 count;
    s8 drawBgId;
    s8 selectNo;
    s8 selectNo_save;
    s16 selectCount;
    tagTITLE_TEST_WORK *test_wk;
};
