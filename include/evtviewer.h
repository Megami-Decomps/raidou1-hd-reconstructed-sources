#pragma once
#include "types.h"
#include "event.h"
#include "kernel.h"

typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct evtFrameInfo_t evtFrameInfo_t;
typedef struct evtViewerInfo_t evtViewerInfo_t;
typedef struct evtViewerObject_t evtViewerObject_t;
typedef struct pmdLoadScene pmdLoadScene;

extern u16 file_major;
extern u16 file_minor;
extern u16 file_seq;
extern s32 gAns;
extern bool start;
extern bool play;
extern bool skyFilterSet;
extern bool ButtonGuideFlag;

void evtSetPause(bool isPause);
bool evtIsPause(void);
evtFrameInfo_t *evtAddFrameInfo(evtViewerObject_t *parent, s32 frame, evtViewerInfo_t *pInfo);
evtViewerObject_t *evtAddObject(PMD_OBJTYPE type, evtViewerInfo_t *pInfo);
s32 evtGetObjectTypeCount(PMD_OBJTYPE type, evtViewerInfo_t *pInfo);
s32 evtGetObjectNoCount(evtViewerInfo_t *pInfo);
s32 evtGetAllFrameInfoCount(s32 no, evtViewerInfo_t *pInfo);
void evtUnRegistUnit(evtViewerInfo_t *pInfo);
s32 evtAddNameTable(char *name, evtViewerInfo_t *pInfo);
void evtRunFrame(s32 nowframe, evtViewerInfo_t *pInfo);
void evtUnitMotionChange(s32 nowframe, dds3Basic_t *b, evtViewerObject_t *obj, evtViewerInfo_t *pInfo, s32 mode);
void evtMessageDelete(evtViewerInfo_t *pInfo, bool Mode);
void evtViewerStopFrame(bool sw, u32 nowframe, evtViewerInfo_t *pInfo);
void evtStopFrame(evtViewerInfo_t *pInfo);
bool evtCompareCutResultValue(s16 res_data);
bool evtIsPMVGuideDraw(void);
void evtGuideCtrl(void);
dds3ProcessFunc_t evtProcess2_RealPlay(dds3ProcessID_t *id);
bool evtFilterTempSetting(void *_bgStatus);
void evtFilterTempSettingClear(pmdLoadScene *_loadScene);
dds3ProcessFunc_t evtProcess1_RealPlay(dds3ProcessID_t *id);
void evtShutdown_RealPlayMode(dds3ProcessID_t *id);
void evtInitZikkiEvent(evtViewerInfo_t *pInfo);
void evtEnd(dds3ProcessID_t *id);
void evtChgSeq(dds3ProcessID_t *id, s32 no, s32 ignoreNum);
void evtIgnoreFade(dds3ProcessID_t *id);
void evtNoSkipMes(dds3ProcessID_t *id);
s32 evtCheckProcess(void);
s32 evtCheckLastSkipStat(void);
void evtSkipStart(dds3ProcessID_t *id);
s32 evtSetFrame(dds3ProcessID_t *id, s32 Frame);
void evtIgnoreAtracPlay(dds3ProcessID_t *id);
