#pragma once
#include "types.h"
#include "CMP_STATUS_MODE.h"
#include "CMP_STATUS_SEQ_TYPE.h"
#include "CMP_STATUS_TYPE.h"
#include "GOH_KARTE_SORTMODE.h"
#include "GOH_RESULT_TYPE.h"
#include "ITM.h"
#include "SKLID.h"
#include "TreeType.h"
#include "UiParType.h"

typedef enum {
    SWORD_UPDOWN_NONE = 0,
    SWORD_UPDOWN_DOWN = 1,
    SWORD_UPDOWN_UP = 2,
} SWORD_UPDOWN;

typedef enum {
    GOHDRAW_COMBTYPE_NML = 1,
    GOHDRAW_COMBTYPE_CST = 2,
    GOHDRAW_COMBTYPE_SWD = 4,
    GOHDRAW_COMBTYPE_1ST = 8,
    GOHDRAW_COMBTYPE_2ND = 16,
} GOHDRAW_COMBTYPE;

typedef enum {
    GOH_KARTE_TYPE_REGIST = 0,
    GOH_KARTE_TYPE_RESTORE = 1,
} GOH_KARTE_TYPE;

typedef enum {
    GohTreeAnimType_None = 0,
    GohTreeAnimType_Create = 1,
    GohTreeAnimType_CreateSel = 2,
} GohTreeAnimType;

typedef enum {
    ScrollBarType_SWORD = 0,
    ScrollBarType_REGIST = 1,
    ScrollBarType_RESTORE = 2,
    ScrollBarType_RECOVER = 3,
    ScrollBarType_SEARCHI = 4,
    ScrollBarType_SEARCHI_SEL = 5,
    ScrollBarType_BACK = 6,
    ScrollBarType_COMBI = 7,
} ScrollBarType;

typedef struct TreeDetails TreeDetails;
typedef struct TreeIcon TreeIcon;
typedef struct TreeIconBase TreeIconBase;
typedef struct TreeIconCursor TreeIconCursor;
typedef struct gohData_t gohData_t;
typedef struct gohGeneralList_t gohGeneralList_t;
typedef struct gohRenkenSelMaterialItem_t gohRenkenSelMaterialItem_t;
typedef struct gohRenkenSword_t gohRenkenSword_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;
typedef struct sprHandle_t sprHandle_t;
typedef struct tagGOH_MENU_WORK tagGOH_MENU_WORK;

struct TreeDetails {
    ITM id;
    s16 branchNo;
    void *source;
    void *connected;
};

struct TreeIcon {
    TreeIconBase *iconBase;
    TreeIconCursor *iconCursor;
    TreeType type;
    s32 branch;
    s32 stage;
    void *data;
};

extern void *gohGuides;
extern char *gohCaption;
extern char *strBstName;

void gohGohGuideSet(char *_name, bool _timer, s32 _waitTimer);
void gohAllDrawCalc(void);
void gohUnityDraw(bool _csr);
void gohMainMenuDraw(tagGOH_MENU_WORK *_wk);
void gohMenuCursorMove(tagGOH_MENU_WORK *_wk);
void gohNativeSkillListDraw(sdatUnitWork_t *_barthDevil);
void gohSearchiListDraw(void);
void gohConditionListDraw(void);
void gohResultDevilDraw(bool _back);
void gohCombiListDraw(void);
void DrawTree(gohData_t *_gohDate);
void DrawTreeIcon(gohData_t *_gohData, TreeDetails *_treeDetails, TreeIcon *_icon, bool _enable, GohTreeAnimType _type);
void DrawSwordDetails(gohData_t *_gohDate);
SWORD_UPDOWN gohGetSwordEquipPar(UiParType _para, s32 _newPar);
void DrawSwordPar(UiParType _para, s32 _parNum, SWORD_UPDOWN _upDown, bool _details);
void gohTreeMaterialDraw(gohData_t *_gohDate);
void gohTreeBattleDraw(gohData_t *_gohDate);
void gohTreeSpiritDraw(gohData_t *_gohDate);
void DrawSpiritSkillName(SKLID a_id, s32 cnt, u32 a_rgba, bool raidou);
void gohScrollBar(s32 a_x, s32 a_y, s32 a_w, s32 a_h, s32 a_topNo, s32 a_drawNum, s32 a_listNum, ScrollBarType _barType);
void gohKarteParts(GOH_KARTE_TYPE a_type, GOH_KARTE_SORTMODE a_sort);
void gohKarteList(sdatUnitWork_t *pUnit, s32 UnitNums, s32 TopIndex, s32 CurrentIndex, GOH_KARTE_TYPE Type, GOH_KARTE_SORTMODE SortMode, bool _pro);
void gohModel(gohData_t *pData);
char *gohRaceName(s32 a_raceID);
void gohCaption(s32 X, s32 Y, s32 No, bool _nonIconHelp);
void gohMagCost(s32 cost, f32 a_ratio);
void gohSelDevilName(s32 X, s32 Y, s32 No, f32 Ratio, gohData_t *pData);
void gohCalcWidth(sprHandle_t *a_hSpr, s32 a_sprNo, s32 a_num, s32 a_max);
bool gohCheckEnableCombine(GOHDRAW_COMBTYPE a_combtype, sdatUnitWork_t *pUnit);
void gohDevilParamSimple(s32 X, s32 Y, sdatUnitWork_t *pUnit, s32 Mode, bool bSelect, bool bEnable, GOHDRAW_COMBTYPE _combType);
void gohSwordParamSimple(gohRenkenSword_t *psSword, s32 X, s32 Y, bool bSelect, bool bEnable);
void gohSwordParamSimpleMake(gohData_t *pData, gohRenkenSword_t *psSword, s32 X, s32 Y, bool bSelect, bool bEnable);
void gohBaseItemParamSimple(gohRenkenSelMaterialItem_t *psItem, s32 X, s32 Y);
void gohResultIcon(GOH_RESULT_TYPE a_type, s32 a_x, s32 a_y, bool a_bEnable);
void gohCombineListFrameNormalANumber(sprHandle_t *hSpr, s32 iX, s32 iY, s32 iValue);
void gohCombineListFrameNormalA(s32 TopIndex, s32 SelIndex, gohData_t *pData);
void gohCombineListFrameNormalB(s32 SelIndex1, s32 TopIndex2, s32 SelIndex2, gohData_t *pData);
void gohHelpKeyAssign(sprHandle_t *hSpr, s32 iSX, s32 iSY, s32 iIconNo, s32 iMesNo);
void gohCombineListFrameSword(s32 UnitNums, s32 TopIndex, s32 SelIndex, gohData_t *pData);
void gohCombineListSwordMaterial(gohData_t *pData, s32 UnitNums, s32 SelIndex);
void gohCombineListFrameA(s32 Y, s32 TopIndex, s32 SelIndex, gohData_t *pData);
void gohCombineListFrameB(s32 Y, s32 SelIndex1, s32 TopIndex2, s32 SelIndex2, gohData_t *pData);
void gohKarteDevilParam(s32 X, s32 Y, sdatUnitWork_t *pUnit, GOH_KARTE_TYPE Type, bool bSelect, bool _pro);
void gohRecoverParam(sdatUnitWork_t *unit, s32 X, s32 Y, bool bSelect);
void gohRecoverList(gohGeneralList_t *pGeneralList, s32 ListNums, s32 TopIndex, s32 CurrentIndex);
void gohCombineIconHelpHatena(sprHandle_t *hSpr, s32 x, s32 y);
void gohCombineIconHelp(void);
void gohStatusHelp(CMP_STATUS_SEQ_TYPE a_seqtype, CMP_STATUS_TYPE a_type, CMP_STATUS_MODE a_mode, u8 a_alphaRate);
