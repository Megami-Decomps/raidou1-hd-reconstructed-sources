#pragma once
#include "types.h"
#include "SKLID.h"
#include "SklItmRst.h"

typedef enum {
    ResultMesType_NEW = 0,
    ResultMesType_ADD = 1,
    ResultMesType_OFC = 2,
} ResultMesType;

typedef struct sdatUnitWork_t sdatUnitWork_t;
typedef struct tagCMP_STATUS_WORK tagCMP_STATUS_WORK;

extern s32 sklType;
extern s32 oldSklCsr;
extern s32 setIndex;
extern SKLID setSkill;
extern SKLID oldSkill;
extern bool gaugeUp;
extern bool autoCsr;
extern ResultMesType rstMesType;

SklItmRst CmpStatusChkUseSklItem(sdatUnitWork_t *_unit, SKLID _skl);
SklItmRst CmpStatusChkOmoideUseSklItem(sdatUnitWork_t *_unit, SKLID _skl);
SklItmRst CmpStatusChkNmlUseSklItem(sdatUnitWork_t *_unit, SKLID _skl);
void CmpStatusAutoNmlSklSet(tagCMP_STATUS_WORK *wk);
void CmpStatusAutoOmoideSklSet(tagCMP_STATUS_WORK *wk);
void CmpStatusAutoSklSet(tagCMP_STATUS_WORK *wk);
void CmpStatusSklSet(tagCMP_STATUS_WORK *wk);
bool CmpStatusCheckSklSet(tagCMP_STATUS_WORK *wk);
void CmpStatusChangeSkill(tagCMP_STATUS_WORK *wk);
bool CmpStatusTempLicenseUpdate(sdatUnitWork_t *_unit);
bool CmpStatusOfficielLicenseCheck(void *_list, sdatUnitWork_t *_unit);
bool CmpStatusSetOfficialSkl(sdatUnitWork_t *_unit, SKLID _sklID);
s32 CmpStatusGetBookCnt(sdatUnitWork_t *_unit, SKLID _sklID);
bool CmpStatusChkUseAutoCsr(void);
s32 CmpStatusGetNowBookCnt(sdatUnitWork_t *_unit, SKLID _sklID);
void CmpStatusSklItemSequence(tagCMP_STATUS_WORK *wk);
void CmpStatusDraw(tagCMP_STATUS_WORK *_wk);
