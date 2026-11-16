#pragma once
#include "types.h"
#include "BSTF.h"
#include "CMP_MENU_ID.h"
#include "PanelFocus.h"
#include "SKLID.h"
#include "ecmpKudaCMU.h"
#include "ecmpKudaDecideFilter.h"
#include "ecmpKudaSelectMode.h"

typedef struct SelectStockID SelectStockID;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct itfMover_t itfMover_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;
typedef struct tagCMP_WORK tagCMP_WORK;

struct SelectStockID {
    PanelFocus stock;
    s32 stockID;
    s32 menuID;
};

extern dds3ProcessID_t *g_listPID;
extern s8 g_step;
extern s8 g_count;
extern bool g_setSaveCsr;
extern void *sklMenus;
extern SKLID *g_skillID;
extern SKLID *g_batskillID;
extern s8 *g_autoskillID;
extern CMP_MENU_ID g_menuID;
extern s16 g_stockID1;
extern s16 g_stockID2;
extern s32 g_stockSelID;
extern SelectStockID *selStockID1;
extern SelectStockID *selStockID2;
extern s32 g_stockSelTab;
extern s32 g_summonID;
extern s32 g_statusID;
extern PanelFocus g_panel;
extern PanelFocus g_panel2;
extern itfMover_t *particle;

s32 cmpGetSkillStep(void);
s32 cmpGetSelectStockIndex(void);
sdatUnitWork_t *cmpGetStockUnitWork(s32 a_stockidx);
void cmpSetStatus(s32 a_no);
void cmpSetStatusSkill(s32 a_no);
void cmpSwapUnitWork(s32 a_stockNo0, s32 a_stockNo1);
bool cmpMenuFilterUnit(sdatUnitWork_t *psUnit, sdatUnitWork_t *psUnitChk, ecmpKudaCMU iAttrId, BSTF iBadStatus);
bool cmpMenuDecFilter(s32 _menuID, ecmpKudaDecideFilter _fiter, bool _party, bool _empty);
bool cmpMenuEmptyFilter(ecmpKudaDecideFilter _fiter);
s32 cmpMenuFilter(tagCMP_WORK *wk);
s32 cmpUpdateEnable(void);
void cmpSetFilterEx(sdatUnitWork_t *psUse, ecmpKudaSelectMode eSelMode, ecmpKudaCMU iSelectAttrId, ecmpKudaCMU iDecideAttrId, ecmpKudaDecideFilter eDecFilter);
void cmpSetFilter(sdatUnitWork_t *psUse, ecmpKudaSelectMode eSelMode, ecmpKudaCMU iAttrId);
void cmpSetFilterBadStatus(BSTF iBadStatus);
void cmpClearFilter(void);
bool cmpChkEnableUseSkill(sdatUnitWork_t *use, sdatUnitWork_t *tgt, SKLID id);
void cmpChkSkillSelectHd(void);
void cmpChkSkillSelect(sdatUnitWork_t *a_pUseUnit);
s32 cmpUpdateEnableUseSkillUnit(SKLID a_skillID);
s32 cmpNakamaView(void);
void cmpSetSavePanel(bool _second, PanelFocus _focus);
s32 cmpCallFuncOraganize(void);
s32 cmpCallFuncSummon2(void);
bool cmpSklMenuUseCheck(sdatUnitWork_t *_useUnit, SKLID _sklID);
void cmpAddSklMenu(sdatUnitWork_t *_unit, SKLID _sklID);
void cmpCreateSklMenus(void);
void cmpUpdateSkillListHd(void);
void cmpUpdateSkillList(void);
void cmpSetSkillListHd(void);
void cmpSetFilterSkillUse(void);
void cmpSetFilterSkillBt(void);
void cmpSetFilterSummon(void);
void cmpSetFilterSwap(void);
void cmpSetFilterPart(void);
void cmpSetFilterOrganize(void);
void SortActiveOnFunc(void);
void SortActiveOffFunc(void);
void SortFunc(void);
void SortSetting(CMP_MENU_ID _id);
void cmpSetupDvlSkl(CMP_MENU_ID a_id);
void Setup(CMP_MENU_ID a_id);
PanelFocus cmpSetFocusPanel(PanelFocus _priority);
s32 cmpGetSelectCharPIDSelMaxCnt(bool _max);
void cmpUpdateSelectPosCharPIDSelMax(bool _max);
s32 cmpGetSelectStockPIDSelMaxCnt(bool _max, bool _dlc);
void cmpUpdateSelectPosStockPIDSelMax(bool _max);
void cmpUpdateSelectPosCharPID(void);
void cmpUpdateSelectNextPosCharPID(void);
void cmpUpdateSelectNextPosCharPID2(void);
void cmpUpdateSelectNextPosStockPID(void);
s32 cmpUpdateFontCharPID(void);
bool cmpChangeChkTabPage(CMP_MENU_ID a_id);
void cmpChangeTabPage(dds3ProcessID_t *PID);
void cmpButtonGuideStatus(void);
s32 cmpGetPartyPanelSummonSetIndex(s32 _index, bool _ascending);
void cmpCtrlStatus(dds3ProcessID_t *PID);
bool cmpUpdateSkillHD(void);
bool cmpUpdateSkill(void);
void cmpDrawSkillSet(void);
void cmpBattleSkillSet(sdatUnitWork_t *unit);
void cmpKuzunohaDirectGuideDraw(void);
bool cmpUpdateOrganize(void);
bool cmpChkStatusJump(void);
bool cmpPartyPanelSelBlankCheck(void);
bool cmpUpdateStatus(void);
void cmpPartSetParticle(s32 a_x, s32 a_y, s32 a_w, s32 a_h);
void cmpDrawParticle(void);
void cmpCharSelectSetDefault(void);
bool Update(CMP_MENU_ID a_id);
