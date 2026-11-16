#pragma once
#include "types.h"
#include "PMD_FLAG.h"
#include "event.h"
#include "kernel.h"

typedef struct DepthOfFieldSetting DepthOfFieldSetting;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3Effect_Blur_t dds3Effect_Blur_t;
typedef struct dds3Effect_DistortionBlurParam_t dds3Effect_DistortionBlurParam_t;
typedef struct dds3Effect_Filter_t dds3Effect_Filter_t;
typedef struct dds3Effect_ParallelBlur_t dds3Effect_ParallelBlur_t;
typedef struct dds3Effect_PartialMultiBlurParam_t dds3Effect_PartialMultiBlurParam_t;
typedef struct dds3Effect_PartialMultiFilterParam_t dds3Effect_PartialMultiFilterParam_t;
typedef struct dds3Effect_RippleBlurParam_t dds3Effect_RippleBlurParam_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct pmdProcessWork_t pmdProcessWork_t;
typedef struct pmdSceneFogTable_t pmdSceneFogTable_t;
typedef struct pmdSceneLightTable_t pmdSceneLightTable_t;
typedef struct pmdSeqData_t pmdSeqData_t;

extern s32 PmvEventNo;

void evtCheckLoad(pmdProcessWork_t *wdata);
bool evtCheckRun(dds3ProcessID_t *id);
bool evtCheckSeqEnd(dds3ProcessID_t *id);
f32 evtHokanFloat(s32 hokan, f32 ratio, f32 f1, f32 f2);
s32 evtHokanInt(s32 hokan, f32 ratio, s32 i1, s32 i2);
void evtHokanSceneLight(s32 hokan, f32 ratio, pmdSceneLightTable_t *key1, pmdSceneLightTable_t *key2, pmdSceneLightTable_t *d);
void evtHokanSceneFog(s32 hokan, f32 ratio, pmdSceneFogTable_t *key1, pmdSceneFogTable_t *key2, pmdSceneFogTable_t *d);
void evtHokanBlur2(s32 hokan, f32 ratio, dds3Effect_Blur_t *key1, dds3Effect_Blur_t *key2, dds3Effect_Blur_t *d);
void evtHokanMultBlur(s32 hokan, f32 ratio, dds3Effect_PartialMultiBlurParam_t *key1, dds3Effect_PartialMultiBlurParam_t *key2, dds3Effect_PartialMultiBlurParam_t *d);
void evtHokanFilter(s32 hokan, f32 ratio, dds3Effect_Filter_t *key1, dds3Effect_Filter_t *key2, dds3Effect_Filter_t *d);
void evtHokanMultFilter(s32 hokan, f32 ratio, dds3Effect_PartialMultiFilterParam_t *key1, dds3Effect_PartialMultiFilterParam_t *key2, dds3Effect_PartialMultiFilterParam_t *d);
void evtHokanDistBlur(s32 hokan, f32 ratio, dds3Effect_DistortionBlurParam_t *key1, dds3Effect_DistortionBlurParam_t *key2, dds3Effect_DistortionBlurParam_t *d);
void evtHokanRipBlur(s32 hokan, f32 ratio, dds3Effect_RippleBlurParam_t *key1, dds3Effect_RippleBlurParam_t *key2, dds3Effect_RippleBlurParam_t *d);
void evtHokanHeikouBlur(s32 hokan, f32 ratio, dds3Effect_ParallelBlur_t *key1, dds3Effect_ParallelBlur_t *key2, dds3Effect_ParallelBlur_t *d);
void evtHokanDof(DepthOfFieldSetting *_hokanData);
void evtRunUnitMode(dds3Basic_t *unit, PMD_UNIT mode, u32 addflag, u32 downflag);
void evtSetFlag(dds3ProcessID_t *id, PMD_FLAG flag);
void evtResetFlag(dds3ProcessID_t *id, PMD_FLAG flag);
void evtStopMover(dds3Basic_t *mover, bool sw, s32 baseframe, s32 nowframe);
void evtMoverFrameSet(dds3Basic_t *mover, bool sw, s32 baseframe, s32 nowframe, s32 offset);
pmdProcessWork_t *evtGetWorkData2and3(pmdProcessWork_t *wdata, pmdSeqData_t *pm2dataParam, pmdSeqData_t *pm3dataParam);
void evtFreeWorkData1(pmdProcessWork_t *wdata);
void evtFreeWorkData2and3(pmdProcessWork_t *wdata);
void SetPMFileName(s32 eventno, s32 cutno, char **asset_name, char **pm1file, char **pm2file, char **pm3file);
void evtSetDofTblFileName(s32 eventno, s32 cutno, char **dofFile);
dds3ProcessID_t *evtStart2(DDS3_PRIORITY priority, s32 eventno, s32 cutno, s32 seqno);
char *evtGetProcessName(void);
bool evtIsExec(s32 major, s32 cutno);
