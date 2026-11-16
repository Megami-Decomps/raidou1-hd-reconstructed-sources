#pragma once
#include "types.h"
#include "BST.h"
#include "MODELTYPE.h"

typedef enum {
    CMPMODEL_BST_NONE = -1,
    CMPMODEL_BST_MOUDOKU = 0,
    CMPMODEL_BST_MAHUU = 1,
    CMPMODEL_BST_MAX = 2,
} CMPMODEL_BST;

typedef struct StatusGattaiPosY_t StatusGattaiPosY_t;
typedef struct cmpStatusLight_t cmpStatusLight_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct effHandle_t effHandle_t;
typedef struct sdf3DLightParallelPacket_t sdf3DLightParallelPacket_t;
typedef struct sdfModelOt_t sdfModelOt_t;

struct cmpStatusLight_t {
    sdfVector4_t col[3];
    sdfVector4_t dir[3];
    sdfVector4_t amb;
};

struct StatusGattaiPosY_t {
    s32 devilId;
    f32 y;
};

extern s32 playerScModelId[11];
extern s32 *playerFieldID;
extern dds3ModelHandle_t *cmpModelHandle;
extern void *g_pDatBst;
extern effHandle_t *g_hEffBst;
extern effHandle_t *g_hEffBst2;
extern void *cmpModelBuffer;
extern bool mdlEffSclSet;
extern s32 dummyModelId;
extern s8 gLoadStat;
extern MODELTYPE gMajorNo;
extern u16 gMinorNo;
extern bool gBlockMode;
extern s8 gViewerLimit;
extern s8 gPosLimit;
extern BST g_bstID;
extern void *cmpStatusModelTbl;
extern void *cmpStatusViewerModelTbl;
extern void *cmpStatusLightTbl;
extern f32 cmpModelScl;
extern f32 cmpModelEffScl;
extern s32 g_defMotNo;
extern f32 g_beforeLeng;
extern f32 g_smoothLeng;
extern sdf3DLightParallelPacket_t *g_pLightPacket;
extern s32 g_lightNo;
extern void *g_addr;
extern effHandle_t *g_hEff;
extern bool backHDrawSync;
extern s32 g_GoodByMode;
extern s32 g_GoodByModeZahyou;
extern StatusGattaiPosY_t *gGattaiPosOffsetY;

void datLoadCampStausTable(void);
void cmpDynamicBoneSet(dds3ModelHandle_t *_a_hModel, bool _OnOff);
void cmpSetModelMotion(dds3ModelHandle_t *a_hModel);
bool cmpCheckHandle(void);
bool cmpCheckCurse(void);
void ModelLoadBuffStart(void);
void cmpInitCore(void);
void cmpSetLight(void);
void cmpInitCore2(void);
void cmpSetLightUnit(s32 a_modelID, s32 a_lightNo);
void cmpInitDstEff2(CMPMODEL_BST type);
void cmpInitDstEff(void);
CMPMODEL_BST cmpCreateBstEff(void);
void cmpDeleteBstEff(void);
void cmpDrawBstEff(void);
void Init(void);
void End(void);
void ModelLoadBuffEnd(void);
void ModelLoadBuffClear(void);
void cmpMemCheckRelease(void);
bool cmpFreeResource(void);
s8 Setup(u16 DevilID, bool BlockMode);
s8 cmpChkStatusModelLoadStat(void);
void ModelLoadInitAction(void);
void ModelLoadBuff(void);
bool cmpWaitLoadModel(void);
void cmpSetMotion(s32 a_motNo, f32 a_motSpd);
void cmpSetSmoothSingleMotion(s32 a_motNo, f32 a_beforeLeng, f32 a_smoothLeng);
void cmpSetSmoothLoopMotion(s32 a_motNo, f32 a_beforeLeng, f32 a_smoothLeng);
void cmpSetLoopMotion(s32 a_motNo);
void cmpSetMotionSpeed(f32 a_motSpd);
void cmpSetColor(s32 rgba);
s32 cmpGetMotionNum(void);
s32 cmpGetMotionCut(void);
f32 cmpGetMotionSpeed(void);
f32 cmpSetModelScale(dds3ModelHandle_t *Handle, s32 Mode);
void cmpSetModelPosition(dds3ModelHandle_t *Handle);
void cmpSetModelRotate(dds3ModelHandle_t *Handle);
void cmpSetStatusModelParam(void);
void cmpGetPos(sdfVector4_t *a_pos);
void cmpGetPosStatus(sdfVector4_t *a_pos);
void cmpGetRot(sdfVector4_t *a_rot);
void cmpGetScl(sdfVector4_t *a_scl);
void cmpGetEffScl(f32 *a_scl, bool _screenShot);
void cmpSetPos(const sdfVector4_t *a_pos);
void cmpSetRot(const sdfVector4_t *_rot);
void cmpSetScl(f32 _scl);
void cmpSetEffScl(f32 _scl);
void cmpAddPos(f32 a_x, f32 a_y, f32 a_z);
void cmpSetPos_GoodBy(f32 a_x, f32 a_y, f32 a_z);
f32 cmpAdjustPosY_Gattai(void);
void cmpAddRot(f32 a_x, f32 a_y, f32 a_z);
void cmpSetRot_GoodBy(f32 a_x, f32 a_y, f32 a_z);
void cmpAddScl(f32 a_scl);
void cmpAddEffScl(f32 a_scl);
void cmpClrRot(void);
void cmpClearDat(void);
void cmpSetBstID(BST a_bstID);
s8 cmpDrawStatusModel(sdfModelOt_t *pModelOt);
s8 cmpGetViewerLimit(void);
void cmpSetViewerLimit(s8 a_bool);
s8 cmpGetPosLimit(void);
void cmpSetPosLimit(s8 a_bool);
void cmpSetLightDef(void);
void cmpSetLightDark(void);
void cmpLoadTitleEff(void);
void cmpInstanceTitleEff(void);
void cmpDestroyTitleEff(void);
void cmpLoadEffect(void);
void cmpDeleteEffect(void);
void cmpEffectSetRGBA(u32 a_rgba);
void cmpDrawEffect(void);
void cmpSetGoodByZahyouMode(s32 mode);
void cmpSetGoodByMode(s32 mode);
