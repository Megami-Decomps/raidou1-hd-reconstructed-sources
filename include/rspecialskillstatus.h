#pragma once
#include "types.h"
#include "RSkillTab.h"
#include "kernel.h"

typedef enum {
    RSkillCsrType_SwordNormalSet = 0,
    RSkillCsrType_SwordNormalPossession = 1,
    RSkillCsrType_SwordSelectSet = 2,
    RSkillCsrType_SwordSelectPossession = 3,
    RSkillCsrType_BattleNormalSet = 4,
    RSkillCsrType_BattleNormalPossession = 5,
    RSkillCsrType_BattleSelectSet = 6,
    RSkillCsrType_BattleSelectPossession = 7,
    RSkillCsrType_Max = 8,
} RSkillCsrType;

typedef enum {
    LIST_SELECT_NOEN = -1,
    LIST_SELECT_SET = 0,
    LIST_SELECT_POSSESSION = 1,
    LIST_SELECT_Max = 2,
} LIST_SELECT;

typedef struct MenuCsrUnity MenuCsrUnity;
typedef struct MenuCsrUnity SpecialSkillCsr;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct tagSPECIAL_SKILL_STATUS_WORK tagSPECIAL_SKILL_STATUS_WORK;

struct tagSPECIAL_SKILL_STATUS_WORK {
    dds3ProcessID_t *drawPID;
    LIST_SELECT select_state;
    RSkillTab tab;
    bool goh;
    s32 possSkillCsr;
    s32 sklCsr;
    SpecialSkillCsr *csr;
    SpecialSkillCsr *skillCsr;
};

extern dds3ProcessID_t *g_mainPID;
extern void *skillListSelect;
extern s32 m_change_listTop;

void RSpecialSkillInit(tagSPECIAL_SKILL_STATUS_WORK *wk);
void Exit(tagSPECIAL_SKILL_STATUS_WORK *wk);
dds3ProcessID_t *RSpecialSkillProcessStart(bool goh);
dds3ProcessFunc_t RSpecialSkillProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t RSpecialSkillDrawProcess(dds3ProcessID_t *PID);
void RSpecialSkillShutdown(dds3ProcessID_t *PID);
void RSpecialSkillResetCoolTime(void);
void RSpecialSkillLoadCsr(void);
void RSpecialSkillSaveRSkillCsr(void);
void RSpecialSkillGetRskillCsrData(RSkillCsrType saveType);
void RSpecialSkillRememberRskillCsr(RSkillCsrType saveType);
void RSpecialSkillGetCsrData(void);
void RSpecialSkillSelectGetCsrData(void);
void RSpecialSkillSelectRememberCsr(void);
void RSpecialSkillSaveRSkillTab(void);
RSkillTab RSpecialSkillLoadTab(void);
void RSpecialSkillSaveRSkillListSide(RSkillTab tab);
void RSpecialSkillLosdListSide(RSkillTab tab);
void RSpecialSkillSetTab(RSkillTab tab);
RSkillTab RSpecialSkillGetTab(void);
LIST_SELECT RSpecialSkillGetSelectListState(void);
void RSpecialSkillCsrUpdate(void);
void subCsrUpdate(void);
void RSpecialSkillInitChangeSource(void);
void RSpecialSkillGetChangeSource(void);
void RSpecialSkillSetChangeSource(void);
s32 RSpecialSkillGetOriginalPos(void);
LIST_SELECT RSpecialSkillGetOriginalSide(void);
void RSpecialSkillSelectStateChaneg(void);
void RSpecialSkillSelectChange(LIST_SELECT celect);
void RSpecialSkillSetSwordSkill(void);
void RSpecialSkillSetBattleSkill(void);
bool RSpecialSkillConfigurable(void);
bool RSpecialSkillIsHaveSKill(RSkillTab tab, LIST_SELECT selectState);
void RSpecialSkillDrawHelpText(void);
void RSpecialSkillButtonGuideDraw(void);
SpecialSkillCsr *RSpecialSkillGetNowSkillCsr(void);
void RSpecialSkillSetListDisplayLeft(void);
void RSpecialSkillSkillCsrColorReset(void);
void RSpecialSkillSwordListAutoArrange(void);
void RSpecialSkillCancelSetting(void);
void RSpecialSkillSKillCsrReset(void);
SpecialSkillCsr *RSpecialSkillGetNowPossSkilCsr(void);
void RSpecialSkillInitListDisp(void);
bool RSpecialSkillDragCheck(void);
s32 RSpecialSkillGetSelectSourceCsrPos(void);
void RSpecialSkillSetBarLength(void);
void RSpecialSkillDrawScrollBar(void);
void RSpecialSkillGetHaveBattleSkill(void);
void RSpecialSkillGetHaveSwordSkill(void);
s32 RSpecialSkillGetBattleSkillCount(void);
s32 RSpecialSkillGetSwordSkillCount(void);
void RSpecialSkillSetListDisplayRight(void);
void RSpecialSkillSetInfo(void);
void RSpecialSkillIsBtlSkillSort(void);
void RSpecialSkillIsSwordSkillSort(void);
void RSpecialSkillSwordSkillSortFunc(void);
void RSpecialSkillEndSwordSkillSortFunc(void);
void RSpecialSkillBattleSkillSortFunc(void);
void RSpecialSkillEndBattleSkillSortFunc(void);
void RSpecialSkillSetBeforeIdx(LIST_SELECT listSide);
