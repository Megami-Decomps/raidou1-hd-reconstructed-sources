#pragma once
#include "types.h"
#include "CMP_MENU_ID.h"
#include "ITM.h"
#include "PanelFocus.h"
#include "SklItmRst.h"

typedef enum {
    ItemTab_None = -1,
    ItemTab_Use = 0,
    ItemTab_Check = 1,
    ItemTab_Material = 2,
    ItemTab_Max = 3,
} ItemTab;

typedef struct EvtItemCutInSpr EvtItemCutInSpr;
typedef struct ItemMenuData ItemMenuData;
typedef struct ItemUpdateManager ItemUpdateManager;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sdatPlayerUnitWork_t sdatPlayerUnitWork_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;
typedef struct sprHandle_t sprHandle_t;

struct ItemMenuData {
    ItemTab oldTab;
    ItemTab tab;
    void *menuBuff;
};

struct EvtItemCutInSpr {
    ITM item;
    s32 sprNo;
};

struct ItemUpdateManager {
    sdatPlayerUnitWork_t *updateDrawPlayer;
    void *updateDrawDevil;
    sdatPlayerUnitWork_t *rstPassUnit;
    bool rstJump;
};

extern EvtItemCutInSpr *cutInOnTbl[21];
extern dds3ProcessID_t *g_listPID;
extern dds3ProcessID_t *g_charPID;
extern dds3ProcessID_t *g_stockPID;
extern dds3ProcessID_t *g_activePID;
extern s8 g_step;
extern s8 g_count;
extern bool g_setSaveCsr;
extern s32 g_itemNo;
extern s32 g_charNo;
extern PanelFocus g_panel;
extern CMP_MENU_ID g_menuID;
extern u16 *g_arrItemID;
extern s32 g_itemNum;
extern s32 g_equipNo;
extern u8 *g_pDatScr;
extern s32 g_scrReq;
extern dds3ProcessID_t *g_scrPID;
extern bool g_bEnd;
extern sprHandle_t *g_hSpr;
extern sdatPlayerUnitWork_t *selDrawPlayer;
extern sdatUnitWork_t *selDrawDevil;
extern ItemUpdateManager *itmUpdateMg;
extern bool openInfo;
extern void *sklItemConvTbl;
extern void *sklItemCntTbl;
extern void *sklItmCoefficientTbl;
extern SklItmRst sklItmRst;
extern s32 g_oldSwordSelNo;
extern ItemMenuData *itmMenuData;
extern bool useNekozyar;
extern bool useSpItem;
extern s32 *s_arrSortItemID;

bool cmpDrawHelp(void);
void cmpSetEquipSwordNo(s32 iSwordNo);
s8 cmpGetStep(void);
s8 cmpGetCount(void);
s32 cmpGetEquipSwordNo(void);
void cmpResetUseNekozyar(void);
bool cmpChkUseNekozyar(void);
u8 cmpChkUseTETYOU(void);
u8 cmpCheckMegane(void);
u8 cmpCheckSeikatu(void);
char *cmpGetNoneItemText(void);
u64 cmpChkEnableUseUnit(sdatUnitWork_t *a_pUnit, s32 a_itemId);
u64 cmpChkEnableUseChar(sdatUnitWork_t *a_pUnit, s32 a_itemId);
u32 cmpChkUseUnit(sdatUnitWork_t *unit, s32 a_itemID);
bool cmpChkUse(s32 a_itemID);
void cmpUpdateUseItemEnebleDecide(void);
s32 cmpUpdateEnableUseCharUnitPC(void);
s32 cmpUpdateEnableUseCharUnit(s32 a_useItemID);
s32 cmpCheckUseCharEnableSelect(s32 a_useItemID);
s32 cmpCallFuncUse2(void);
bool cmpItmRnkUpCheck(sdatUnitWork_t *_unit);
void ItemUnitUpdate(s32 _id);
s32 cmpCallFuncUse(void);
s32 cmpCallFuncBullet(void);
s32 cmpCallFuncSword(void);
u32 cmpGetValueColor(s32 iNewVal, s32 iOldVal);
void cmpDrawSwordParam(s32 a_x, s32 a_y, s32 a_z, u8 a_alphaRate, s32 a_swordno, s32 a_swordno_chk, u32 a_swordnameColor);
void DrawFunc(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate);
s32 cmpGetEvtItemSprNo(ITM _itemNo);
void cmpSortMenu(void);
s32 MakeList(CMP_MENU_ID a_id);
void cmpSwordSelStatusDraw(void);
void cmpSklItemSetStatusDraw(void);
void cmpSortActiveOnFunc(void);
void cmpSortActiveOffFunc(void);
void cmpSortFunc(void);
void cmpSortSetting(CMP_MENU_ID _id);
void Setup(CMP_MENU_ID a_id, bool _none);
void FreeSpriteHnd(void);
void cmpOpenItemInfo(void);
void cmpCloseItemInfo(void);
void cmpSearchiSelDevil(void);
void cmpItmUseButtonGuideSet(void);
void cmpTabChange(void);
bool cmpTabChangeMouse(void);
void cmpMenuChange(void);
void cmpCsrUseSave(void);
void cmpCsrUseLoad(void);
void cmpTipsOffCallBack(void);
bool cmpUpdateUse(void);
bool cmpUpdateBullet(void);
bool cmpUpdateThrow(void);
bool UpdateEvent(void);
bool cmpUpdateSword(void);
bool cmpUpdateJewel(void);
bool cmpUpdateMaterial(void);
bool Update(void);
void cmpLoadScript(void);
void cmpFreeScript(void);
void cmpStart(void);
void End(void);
s32 cmpChkMessageDraw(void);
s32 cmpGetItemIDFromSortNo(s32 a_sortNo);
s32 cmpCommand_CHECK_USE_TETYOU(void);
s32 cmpCommand_CHECK_MEGANE(void);
s32 cmpCommand_CHECK_SEIKATU(void);
s32 cmpCommand_SEIKATU_SET(void);
s32 cmpCommand_MEGANE_SET(void);
