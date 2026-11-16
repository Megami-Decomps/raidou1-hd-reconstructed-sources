#include "types.h"
#include "CMP_MENU_ID.h"
#include "cmpbook.h"
#include "cmpfile.h"
#include "cmpmain.h"
#include "dat.h"
#include "itf.h"
#include "sdat.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct itfSprList_t itfSprList_t;

typedef bool (*cmpBookFunc_t)(void);

dds3ProcessID_t *g_listPID;
dds3ProcessID_t *g_charPID;
u8 g_step;
s32 g_itemNo;
s32 g_charNo;
CMP_MENU_ID g_menuID;
u16 *g_arrItemID;
s32 g_itemNum;
static cmpBookFunc_t *cmpBookFunc;
itfSprList_t *cmpSprListItemPanel;
itfSprList_t *cmpSprListItemSelect;
itfSprList_t *cmpSprListItemPanelTop;
itfSprList_t *cmpSprListItemScroll;

// 0x1e571f0
void cmpDrawFunc(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate) {
  dds3ProcessID_t *p_g_listPID;
  dds3ProcessID_t *g_listPID_local;
  dds3ProcessID_t *v16;
  dds3ProcessID_t *v18;
  dds3ProcessID_t *v20;

  p_g_listPID = &g_listPID;
  g_listPID_local = p_g_listPID;
  if (itfMenuGetSelectID(g_listPID_local) != a_id)
  {
    goto LABEL_9;
  }
  v20 = g_listPID;
  itfMenuImgGetAlpha(v20, 2);
  itfDrawMiscHelp(0xA09DC380, (f32)a_alphaRate / 255.0, 1, g_arrItemID[a_id], 0);
LABEL_9:
  v16 = &g_listPID;
  v18 = v16;
  itfMenuChkMenuTop(v18, a_id);
}

// 0x1e574e0
void cmpSetup(CMP_MENU_ID a_id) {
  dds3ProcessID_t *ListPID;
  s64 i;
  u32 v11;
  s32 v12;
  dds3ProcessID_t *v15;
  char *v16;
  dds3ProcessID_t *v18;
  itfMenuDrawFunc_t v19;
  dds3ProcessID_t *v20;
  sprHandle_t *v25;
  dds3ProcessID_t *CharPID;

  g_menuID = a_id;
  ListPID = cmpGetListPID();
  g_listPID = ListPID;
  itfMenuClearMenuAll(g_listPID);
  itfMenuSetFlag(g_listPID, 8, 1);
  itfMenuSetFlag(g_listPID, 32, 0);
  itfMenuSetFlag(g_listPID, 256, 0);
  itfMenuSetFlag(g_listPID, 512, 0);
  itfMenuSetFlag(g_listPID, 2048, 0);
  itfMenuSetFlag(g_listPID, 4096, 0);
  itfMenuSetFlag(g_listPID, 0x2000, 0);
  itfMenuSetFlag(g_listPID, 1, 1);
  itfMenuSetSelectID(g_listPID, 0);
  for (i = 0; ; ++i)
  {
    if (i >= g_itemNum)
      break;
    v12 = g_arrItemID[i];
    if (g_menuID == 61504)
    {
LABEL_22:
      if (v11)
        goto LABEL_23;
      goto LABEL_37;
    }
    if (v11)
    {
      if (g_menuID == 65600)
        goto LABEL_22;
    }
    else
    {
      if (g_menuID == 65600)
        goto LABEL_22;
    }
    if (v11)
    {
      if (g_menuID == 131136)
        goto LABEL_22;
    }
    else
    {
      if (g_menuID == 131136)
        goto LABEL_22;
    }
    if (v11)
    {
      if (g_menuID != 196672)
        goto LABEL_27;
    }
    else
    {
      if (g_menuID != 196672)
        goto LABEL_27;
    }
LABEL_23:
    v15 = g_listPID;
    goto LABEL_24;
LABEL_37:
    v15 = g_listPID;
LABEL_24:
    v16 = sdatItemName(v12);
    itfMenuSetRootMenu(v15, i, v16, 0, "");
LABEL_27:
    v18 = g_listPID;
    v19 = Allocate(itfMenuDrawFunc_t);
    _ctor(v19, 0, Method_Project_cmpBook_DrawFunc__, 0);
    itfMenuSetDrawFunc(v18, i, v19, 0);
  }
  v20 = g_listPID;
  goto LABEL_41;
LABEL_42:
  goto LABEL_43;
LABEL_41:
  goto LABEL_42;
LABEL_43:
  v25 = g_hSpr[1];
  itfMenuLinkSprite(v20, v25);
  itfMenuSetFlag(g_listPID, 2, 0);
  itfMenuSetDrawParam(g_listPID, 8, 1);
  itfMenuStart(g_listPID);
  CharPID = cmpGetCharPID();
  g_charPID = CharPID;
  itfMenuSetFlag(g_charPID, 512, 0);
  itfMenuSetSelectID(g_charPID, 0);
  g_step = 0;
  *(u64 *)&g_itemNo = -1;
}

// 0x1e57b70
s32 cmpMakeList(CMP_MENU_ID a_id) {
  return g_itemNum;
}

// 0x1e57bf0
bool cmpUpdateKeyWord(void) {
  if (g_step)
    return 0;
  return itfMenuGetWaitType(g_listPID) == 4;
}

// 0x1e57d00
bool cmpUpdateItem(void) {
  if (g_step)
    return 0;
  return itfMenuGetWaitType(g_listPID) == 4;
}

// 0x1e57e10
bool cmpUpdateMushi(void) {
  if (g_step)
    return 0;
  return itfMenuGetWaitType(g_listPID) == 4;
}

// 0x1e57f20
bool cmpUpdateEvent(void) {
  if (g_step)
    return 0;
  return itfMenuGetWaitType(g_listPID) == 4;
}

// 0x1e58030
s32 cmpGetEventNo(void) {
  return g_arrItemID[0];
}

// 0x1e580c0
bool cmpUpdate(void) {
  cmpBookFunc_t v5;

  v5 = cmpBookFunc[CMP_MENU_ID_ROOT_MASK(g_menuID)];
  return (v5->invoke_impl)(v5->method_code, v5->method);
}

// 0x1e581a0
void cmpInitLuckPoint(s32 a_max, s32 a_max1st) {
  GBWK->LuckPoint = 0;
  GBWK->LuckPointMax = a_max;
  GBWK->LuckPointMax1st = a_max1st;
}

// 0x1e58220
void cmpDeleteMushi(s32 a_itemid) {
  ;
}

// 0x1e58230
s32 Command_INIT_LUCKPOINT(void) {
  dds3GlobalWork_t *GBWK_local;

  GBWK_local = GBWK;
  *(u64 *)&GBWK_local->LuckPoint = 0xF00000000LL;
  GBWK_local->LuckPointMax1st = 15;
  return 1;
}
