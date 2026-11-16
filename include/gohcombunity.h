#pragma once
#include "types.h"
#include "CmbBackStatus.h"
#include "CombStSeq.h"
#include "SKLID.h"
#include "itf.h"

typedef enum {
    SearchiType_Nkm = 0,
    SearchiType_NoSearch = 1,
    SearchiType_CmbNew = 2,
    SearchiType_LvLess = 3,
    SearchiType_LvMore = 4,
    SearchiType_Group = 5,
    SearchiType_Name = 6,
    SearchiType_SklGroup = 7,
    SearchiType_SklName = 8,
    SearchiType_Endure = 9,
    SearchiType_karte = 10,
    SearchiType_Seirei = 11,
    SearchiType_Mitama = 12,
    SearchiType_TypeMax = 13,
} SearchiType;

typedef enum {
    NativeSkillStep_Init = 0,
    NativeSkillStep_Select = 1,
    NativeSkillStep_Set = 2,
    NativeSkillStep_End = 3,
} NativeSkillStep;

typedef enum {
    devil1 = 0,
    devil2 = 1,
    result = 2,
} GohStatusType;

typedef enum {
    SearchiDrawSet_Check = 0,
    SearchiDrawSet_Text = 1,
} SearchiDrawSet;

typedef struct ResultCsr CombiCsr;
typedef struct MenuCsrUnity MenuCsrUnity;
typedef struct MenuCsrUnity MenuCsrUnitySp;
typedef struct NativeSkillCsr NativeSkillCsr;
typedef struct ResultCsr ResultCsr;
typedef struct gohData_t gohData_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

struct NativeSkillCsr {
    s32 csrNo;
    s32 listTop;
    s32 listDrwNo;
    s32 nowMax;
    s32 listMax;
    CsrUnityMoveFunc moveFunc;
    bool endCursorOn;
    bool seOff;
};

struct ResultCsr {
    s32 csrNo;
    s32 listTop;
    s32 listDrwNo;
    s32 nowMax;
    s32 listMax;
    CsrUnityMoveFunc moveFunc;
    bool statusCsr;
    s32 widthMax;
    s32 widthOfs;
};

extern bool resultCheck;
extern NativeSkillStep nativeSkillStep;
extern SKLID setNativeSkill;
extern void *setNativeSkillList;
extern SKLID *rndChangeSkill;
extern s32 setNativeSkillEndCnt;
extern s32 nativeSkillInit;
extern NativeSkillCsr *nativeSkillCsr;
extern void *gohCombSearchCtrl;
extern MenuCsrUnitySp *searchiCsr;
extern MenuCsrUnitySp *conditionCsr;
extern void *allUnit_t;
extern bool allUnitTblCreated;
extern void *resultUnit_t;
extern void *combiTbl;
extern void *combiDrawTbl;
extern ResultCsr *resultCsr;
extern MenuCsrUnity *resultStatusCsr;
extern CombiCsr *combiCsr;
extern bool *sortSets;
extern MenuCsrUnity *sortCsr;
extern bool resultSort;
extern bool condition;
extern SearchiType decisionType;
extern void *conditionList;
extern void *conditionLvList;
extern void *conditionKudaList;
extern void *conditionSklTypeList;
extern void *conditionEndraceList;
extern char *searchiText;
extern char *searchiHelpText;
extern char *conditionText;
extern char *endureText;
extern char *sortText;
extern SearchiDrawSet *searchiDrawSet;
extern SKLID **searchiSklTbl;

gohData_t *GohGetGohData(void);
CombStSeq GohGohNativeSq(void);
void CombGuideDraw(gohData_t *_pData);
void GohRndChangeListClear(void);
void GohRndNativeSkillSet(sdatUnitWork_t *_barthDevil);
bool GohNativeSkillListUpdate(sdatUnitWork_t *_barthDevil);
void GohNativeSkillSetAllClear(gohData_t *_pData);
void GohInitSkillChange(gohData_t *_pData, bool _allReset);
void GohReturnNativeSklSet(gohData_t *_pData);
bool GohNaitiveSklMove(gohData_t *_pData);
bool GohMitamaNativeSklNone(gohData_t *_pData);
bool GohMitamaBurstChk(gohData_t *_pData);
bool GohNaitiveSklSetting(gohData_t *_pData);
void GohSkl1SlotDel(gohData_t *_pData);
void GohSkillChangeSettingDestroy(void);
void GohSetNativeSkill(gohData_t *_pData);
bool GohSkillChangeUpdate(gohData_t *_pData);
void CombBackGuideSet(CmbBackStatus _type, bool _back);
void GohCombiGuideSet(CmbBackStatus _type, bool _back, GohStatusType _statusType);
void *GohGetUnitList(SearchiType _type);
void GohCreateSklTextTbl(void *_tbl);
void *GohGetTextList(SearchiType _type);
void GohLoadConditionTbl(void);
bool CombCheck(bool *_type);
bool GohCreateResultTbl(bool _serchi);
bool GohCreateAllUnitSortTbl(gohData_t *pData);
void GohAllUnitSortTbl(void);
void GohCreateAllTbl(void);
void GohResultSortFunc(void);
void GohCmbSortFunc(void);
void GohSortOnFunc(void);
void GohSortOffFunc(void);
void GohResultCalcSortSetting(gohData_t *_pData);
void GohCmbCalcSortSetting(gohData_t *_pData);
void GohResultGetStatusCsrCnt(gohData_t *_pData, s32 *_cursorMax, s32 *_listMaxCnt);
void GohSetStatusCsrCollider(CmbBackStatus _status, MenuCsrUnity *_csr);
sdatUnitWork_t *GohCreateDevilFormatDevil(s32 _devilID);
void GohCreateCombiTbl(gohData_t *_pData);
void CombStatusCheck(gohData_t *_pData, GohStatusType _type);
void GohDisableComb(gohData_t *_pData, sdatUnitWork_t *_devil1, sdatUnitWork_t *_devil2, sdatUnitWork_t *_barthDevil);
void GohCombiGetStatusCsrCnt(gohData_t *_pData, s32 _curType, s32 _hightNum, s32 *_cursorMax, s32 *_listMaxCnt);
void GohNativeSkillSet(gohData_t *_pData, u32 _pad);
