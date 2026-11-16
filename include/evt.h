#pragma once
#include "types.h"
#include "ActionDelegate.h"
#include "EVT_UNIT_MOVE_TYPE.h"
#include "MODELTYPE.h"
#include "event.h"
#include "kernel.h"

#define EVENTBIT_MAX 16384
#define CUTRESULT_POSOFFSET 200
#define CUTRESULT_NO 10
#define SUPPORT_MOTION_GRPMAX 4
#define DEBUGDISP_MENU_MAXLINE 2
#define RAIN_SPRITE_NO 3
#define CALLBGM_MAX 20
#define VIEWER_NAMETABLE_MAX 256
#define EDIT_MAX_FRAME 20000
#define MIDI_OFFSET 256
#define SE_OFFSET 32
#define CUSTOM_SLIGHTNO 7
#define MOTION_SPEED_BASE 2
#define EXMOT_MAX 12

typedef enum {
    SCENELIGHT_DISABLE = 0,
    SCENELIGHT_SCENEALL = 1,
    SCENELIGHT_UNITALL = 2,
    SCENELIGHT_ONEUNIT = 3,
} SCENELIGHT;

typedef struct BUSTUP_POS_TBL_t BUSTUP_POS_TBL_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct dds3PoseSet_t dds3PoseSet_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct evtBustupLight_t evtBustupLight_t;
typedef struct evtFrameInfo_t evtFrameInfo_t;
typedef struct evtUnitHandle_t evtUnitHandle_t;
typedef struct evtViewerInfo_t evtViewerInfo_t;
typedef struct evtViewerObject_t evtViewerObject_t;
typedef struct pmdObjectTable_t pmdObjectTable_t;
typedef struct pmdProcessWork_t pmdProcessWork_t;
typedef struct pmdSceneLightTable_t pmdSceneLightTable_t;
typedef struct pmdTmxData_t pmdTmxData_t;
typedef struct sdf3DLightParallelPacket_t sdf3DLightParallelPacket_t;
typedef struct sdfBinary sdfBinary;
typedef struct sdfIVector2_t sdfIVector2_t;

struct pmdTmxData_t {
    s32 x;
    s32 y;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    f32 scaleh;
    f32 scalew;
    s32 hokan;
    s32 transmode;
    s32 priority;
};

struct evtBustupLight_t {
    sdfVector4_t DirR1;
    sdfVector4_t DirR2;
    sdfVector4_t DirR3;
    sdfVector4_t DirL1;
    sdfVector4_t DirL2;
    sdfVector4_t DirL3;
    sdfVector4_t Col1;
    sdfVector4_t Col2;
    sdfVector4_t Col3;
    sdfVector4_t Amb;
};

struct BUSTUP_POS_TBL_t {
    f32 PosLX;
    f32 PosRX;
    f32 PosY;
    f32 Scale;
    f32 AngL;
    f32 AngR;
};

extern s32 NextEventNo;
extern BUSTUP_POS_TBL_t *bustup_pos_tbl;
extern evtBustupLight_t *bustup_light_tbl;
extern s32 *bustup_lightno;
extern s32 bustup_sid0;
extern s32 bustup_sid1;
extern bool IsEvtMoveCollisionCheck;

void evtAllObjectAdjustFrame(evtViewerInfo_t *pInfo, s32 addvalue, s32 nowframe);
void evtGetValueNewSLightFrame(evtViewerInfo_t *pInfo, evtViewerObject_t *obj, s32 nowframe, pmdSceneLightTable_t *sl, f32 *out_soften, f32 *out_bias);
void evtGetValueNewTMXFrame(evtViewerInfo_t *pInfo, evtViewerObject_t *obj, s32 nowframe, pmdTmxData_t *out_tmxdata);
void evtHokanTmx(f32 ratio, evtFrameInfo_t *nearframe, evtFrameInfo_t *frame, pmdTmxData_t *out_tmxdata);
bool evtFindInputBranchMessage(evtViewerInfo_t *pInfo);
void evtGetMessageDataAndTypeFromFrame(evtFrameInfo_t *frame, s32 *pMesNo, s32 *pMesType);
s32 evtFindNameTableIdxFromPM2NameTableIdx(pmdProcessWork_t *wdata, evtViewerInfo_t *pInfo, s32 pm2nametable_idx);
evtViewerObject_t *evtFindObjectFromName(evtViewerInfo_t *pInfo, char *objname);
void evtDrawTexture(void *tex, pmdTmxData_t *tmxdata, bool mask, sdfIVector2_t maskofs, void *mesh);
void evtCreateZikkiEventMes(evtViewerInfo_t *pInfo);
void evtDeleteZikkiEventMes(evtViewerInfo_t *pInfo);
void evtRenderTexStart(evtViewerInfo_t *pInfo);
void evtRenderTexManager(evtViewerInfo_t *pInfo);
void evtSetBistaMode(evtViewerInfo_t *pInfo, s32 bistamode);
s32 evtGetBistaMode(evtViewerInfo_t *pInfo);
void evtSetSkipMode(evtViewerInfo_t *pInfo, s32 skipmode);
s32 evtGetSkipMode(evtViewerInfo_t *pInfo);
void evtEventRegistBGM(evtViewerInfo_t *pInfo, s32 regbgm_no);
void evtEventFadeOutAllBgm(evtViewerInfo_t *pInfo);
void evtBezierGetPoint(f32 T, s32 *pCX, s32 *pCY, s32 *pX, s32 *pY);
s32 evtBezierGetPointY(s32 TargetX, s32 *pCX, s32 *pCY);
dds3ProcessID_t *evtStartScreenBreak(dds3ProcessID_t *ParentPID, DDS3_PRIORITY Priority, s32 Type);
dds3ProcessID_t *evtStartCrossFade(dds3ProcessID_t *ParentPID, DDS3_PRIORITY Priority, s32 Length);
s32 evtCrossFadeGetStat(void);
void evtStartRain(s32 Type);
void evtEndRain(void);
s32 evtCheckRain(void);
void evtModifySLightLinkObjIndex(pmdProcessWork_t *wdata, evtViewerInfo_t *pInfo, pmdObjectTable_t *pObjData);
s32 evtSetGameData1(pmdProcessWork_t *wdata, evtViewerInfo_t *pInfo);
void *oldEventSceneUnload(char *sName);
s32 evtSetGameData2and3(pmdProcessWork_t *wdata, evtViewerInfo_t *pInfo, s32 mode);
void evtSetTestCamera(void);
s32 evtSetRegistUnit(MODELTYPE major, s32 minor);
s32 evtLoadUnit(MODELTYPE major, s32 minor);
evtBustupLight_t *evtGetBustupLightTable(void);
f32 evtEuclid(f32 variable1, f32 variable2);
f32 evtGetWidthDiv(void);
s32 evtGetDefaultPosBustUp(MODELTYPE major, BUSTUP_POS_TBL_t *tbl, s32 type, sdfVector4_t *pos, sdfVector4_t *rot, sdfVector4_t *defpos);
s32 evtLoadUnitBustUp(MODELTYPE major, s32 minor, s32 type);
void evtSetLightBustup(s32 unitID, s32 frame, s32 lightNo, evtBustupLight_t *org_tbl);
s32 evtGetDrawBustupNums(void);
void evtSetUnitPos(s32 unitID, s32 posID);
void evtSetUnitPosCustom(s32 unitID, s32 posID, f32 posX, f32 posY, f32 posZ);
void evtFreeStage(void);
void evtFreeAllUnit(void);
s32 evtLoadMap(s32 fld, s32 flor);
s32 evtLoadArea_FromMemory(s32 fld, s32 area, void *pF1, void *pF2, sdfBinary *pTB, sdfBinary *pBF);
void evtStartEvent(s32 no);
void evtKillFieldScript(void);
void evtPathStop(dds3Basic_t *basic);
void evtPathStart(dds3Basic_t *basic);
void evtPathRate(dds3Basic_t *basic, f32 rate);
void evtPathDir(dds3Basic_t *basic, s32 dir);
bool evtPathLinkAndMake(dds3Basic_t *path, dds3Basic_t *obj);
s32 evtCheckPathStat(dds3Basic_t *obj);
void evtPathLoop(dds3Basic_t *basic, bool sw);
dds3Basic_t *evtAddCamera(const sdfVector4_t *eye, const sdfVector4_t *rot);
void evtEffectLoopControl(dds3Basic_t *eff, bool sw);
s32 evtStageAnimeControl(s32 type, s32 mode);
void UnitAnime(evtUnitHandle_t *h);
void evtLinkLightObjectBasic(evtUnitHandle_t *h, dds3Basic_t *light, s32 frame);
void evtUnlinkLightObjectBasic(evtUnitHandle_t *h, s32 frame);
void evtLinkExternalLightPacket(evtUnitHandle_t *h, sdf3DLightParallelPacket_t *packet);
void evtUnlinkExternalLightPacket(evtUnitHandle_t *h);
void evtSetUnitLightAndAmbient(evtUnitHandle_t *h, u32 frame, u32 lrgb, u32 argb);
void evtSetUnitLightAndAmbient3(evtUnitHandle_t *h, u32 frame, u32 lrgb0, u32 lrgb1, u32 lrgb2, u32 argb);
void evtSetUnitRim(evtUnitHandle_t *h, f32 _R, f32 _G, f32 _B, f32 _Pow);
void evtSetUnitLightDir(evtUnitHandle_t *h, s32 frame);
void evtSetUnitLightDir1(evtUnitHandle_t *h, s32 frame);
void evtSetUnitLightDir2(evtUnitHandle_t *h, s32 frame);
void evtSetUnitColorRGB(evtUnitHandle_t *h, u32 frame, u32 rgb);
void SetUnitColorRGB(evtUnitHandle_t *h, u32 frame, const sdfVector4_t *rgb);
void evtSetUnitColorA(evtUnitHandle_t *h, u32 frame, u32 a);
void SetUnitColorA(evtUnitHandle_t *h, u32 frame, f32 a);
bool evtUnitLightAnimeStat(evtUnitHandle_t *h);
void evtUnitLightOn(evtUnitHandle_t *h);
void evtUnitLightOff(evtUnitHandle_t *h, s32 frame);
evtUnitHandle_t *evtGetUnitHandle(s32 serialID);
evtUnitHandle_t *evtGetUnitHandle2(dds3Basic_t *unit);
evtUnitHandle_t *evtCreateUnitHandle(dds3Basic_t *owner, dds3ModelHandle_t *model);
bool evtDeleteUnitHandle(evtUnitHandle_t *h);
EVT_UNIT_STAT evtGetUnitStat(evtUnitHandle_t *h);
EVT_UNIT_STAT evtSetUnitStat(evtUnitHandle_t *h, EVT_UNIT_STAT stat);
void evtSetWaitMotion(evtUnitHandle_t *h, s32 motion);
void evtSetWaitMotionSpeed(evtUnitHandle_t *h, f32 sp);
void evtSetWaitHokanFrame(evtUnitHandle_t *h, s32 before, s32 smooth);
bool evtCheckUnitWait(evtUnitHandle_t *h);
void evtSetUnitKutiMotion(evtUnitHandle_t *h, s32 group, s32 motion);
void evtRunUnitKutiMotion(evtUnitHandle_t *h);
void evtSetUnitExMotion(evtUnitHandle_t *h, s32 group, s32 motion, s32 before, s32 smooth, EVT_MOT mode, s32 frameLimit);
void evtSetUnitMotion(evtUnitHandle_t *h, s32 motion, s32 before, s32 smooth, EVT_MOT mode, s32 frameLimit);
bool evtUnitRotationTarget(evtUnitHandle_t *h, const sdfVector4_t *pos, f32 radio);
bool evtUnitRotationQuat(evtUnitHandle_t *h, const sdfVector4_t *rot, f32 radio);
bool evtUnitMoveType0(evtUnitHandle_t *h);
void evtUnitHeightCorrection(evtUnitHandle_t *h);
s32 evtCalcFrame_UnitMoveType0(evtUnitHandle_t *org_h);
bool evtUnitMoveTypePathTrace(evtUnitHandle_t *h);
void evtSetUnitMovePos(evtUnitHandle_t *h, const sdfVector4_t *pos);
void evtSetUnitRot1(evtUnitHandle_t *h, const sdfVector4_t *rot, s32 para1);
void evtSetUnitRot2(evtUnitHandle_t *h, s32 posID, s32 para1);
void evtSetUnitMove1(evtUnitHandle_t *h, EVT_UNIT_MOVE_TYPE movetype, const sdfVector4_t *pos, s32 motion, s32 para1, s32 para2, ActionDelegate func, void *data);
void evtSetUnitMove2(evtUnitHandle_t *h, EVT_UNIT_MOVE_TYPE movetype, s32 posID, s32 motion, s32 para1, s32 para2, ActionDelegate func, void *data);
void evtSetUnitMove3(evtUnitHandle_t *h, s32 pathID, s32 para1, s32 para2, s32 movesys, s32 movedir, s32 rotsys);
void evtSetUnitMoveBustup(evtUnitHandle_t *h, const sdfVector4_t *start_pos, const sdfVector4_t *pos, f32 rate, s32 motion, s32 frame, s32 outmode);
bool evtSetUnitAction(evtUnitHandle_t *h, ActionDelegate func, void *data);
bool evtUnitManagerPrimaryFunc(dds3PoseSet_t *pose, dds3Basic_t *basic);
void evtInitCustomSceneLight(void);
void evtSetCustomSceneLightData(s32 index, SCENELIGHT LightType, evtUnitHandle_t *h, sdfVector4_t *Color, sdfVector4_t *Dir, const sdfVector4_t *Ambient);
void evtSetCustomSceneLightData_SoftenAndBias(s32 index, f32 soften, f32 bias);
bool evtGetCustomSLightData(evtUnitHandle_t *h, sdfVector4_t *lightv);
void evtMakeCustomSLightPacket(evtUnitHandle_t *h);
bool evtGetCustomSLight_SoftenAndBias(evtUnitHandle_t *h, f32 *pSoften, f32 *pBias);
