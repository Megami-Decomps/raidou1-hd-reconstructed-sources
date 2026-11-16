#include "types.h"
#include "cmpkeyword.h"
#include "dat.h"
#include "dds3kernelcore.h"
#include "evtbit.h"
#include "fclmsg.h"
#include "itf.h"
#include "kernel.h"
#include "keyword_inc.h"

#define KEYWORD_CATEGORY_NUM 24
#define KEYWORD_LIST_MAX 10
#define KEYWORD_LIST_NUM 56
#define KEYWORDMENU_MAINPROC_NAME "keyword_menu"

typedef enum {
    KEYWORDMENU_PANEL_X = 6,
    KEYWORDMENU_PANEL_Y = 87,
    KEYWORDMENU_PANEL_W = 128,
    KEYWORDMENU_PANEL_H = 23,
    KEYWORDMENU_PANEL_FX = 14,
    KEYWORDMENU_PANEL_FY = 3,
    KEYWORDMENU_PANEL_NX = 130,
    KEYWORDMENU_PANEL_NY = 8,
    KEYWORDMENU_PANEL_X2 = 152,
} KEYWORDMENU_PANEL;

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct itfSprList_t itfSprList_t;
typedef struct tagKEYWORD_MENU_WORK tagKEYWORD_MENU_WORK;

char *strkeywordcate;
char *strkeyword;
itfSprList_t *arrSprListTitle;
itfSprList_t *arrSprListPanel;
itfSprList_t *arrSprListSelect;
itfSprList_t *arrSprListScrollBar;
itfSprList_t *arrSprListPanel2;
itfSprList_t *arrSprListSelect2;
dds3ProcessID_t *g_mainPID;
s16 g_keywordNum;
s16 g_keywordctNum;
s16 *g_keywordctList;
s16 *g_keywordList;
KEYWORD_MENUTYPE g_KeyMenuType;

// 0x1e6bc40
void cmpMenuSetMenuImage(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  sprHandle_t *klass;
  s32 MenuNum;
  s16 v10;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  klass = ProcessData[1].klass;
  itfMenuLinkSprite(PID, klass);
  MenuNum = itfMenuGetMenuNum(PID);
  if (MenuNum <= 8)
    v10 = -18;
  else
    v10 = -6;
  arrSprListPanel[0]->ofsx = v10;
  itfMenuSetSubABGR(PID, 0x46145A6Eu);
}

// 0x1e6be10
bool cmpCateFlgChk(s32 cateno) {
  s64 v2;

  LODWORD(v2) = cateno;
  v2 = (s32)v2;
  if (SLODWORD(s_iKeywordflglist->max_length) <= (s64)(s32)v2)
    return 0;
  if (evtBitCheck(s_iKeywordflglist[v2]))
    return 1;
  return 0;
}

// 0x1e6bf10
bool cmpReadFlgChk(s64 cateno) {
  if (SLODWORD(s_iKeywordreadflglist->max_length) <= cateno)
    return 0;
  return evtBitCheck(s_iKeywordreadflglist[cateno]);
}

// 0x1e6bff0
void cmpReadFlgOn(s64 cateno) {
  u32 v5;
  s64 v7;

  if (SLODWORD(s_iKeywordreadflglist->max_length) <= cateno)
    return;
  v5 = s_iKeywordreadflglist[cateno];
  if (!v5)
    return;
  if (v5 - 2618 >= 0xFFFFFFC6)
    evtBitKityouItemAdd(v5);
  v7 = (s64)GBWK->EventBit + 4 * ((s32)((v5 + ((v5 >> 26) & 0x1F)) << 16) >> 21);
  *(u32 *)(v7 + 32) |= 1 << v5;
}

// 0x1e6c170
s32 cmpMakeCateChk(void) {
  s64 v1;
  s32 v3;
  s64 v4;
  s32 v5;
  s64 v6;

  v1 = 0;
  v3 = 0;
  v4 = 32;
  goto LABEL_9;
  while (1)
  {
LABEL_9:
    while (1)
    {
      LODWORD(v6) = *(u32 *)((char *)&s_sKeywordcd[v1]->listno->obj.klass + v4);
      if ((u32)v6 == -1)
        break;
      v6 = (s32)v6;
      if (SLODWORD(s_iKeywordflglist->max_length) > (s64)(s32)v6)
      {
        v5 = evtBitCheck(s_iKeywordflglist[v6]);
        v3 += v5;
      }
      v4 += 4;
      if (v4 == 72)
        break;
    }
    if (++v1 == 24)
      return v3;
    v4 = 32;
  }
}

// 0x1e6c360
void cmpMakekeywordctlist(void) {
  s64 v3;
  s64 v5;
  bool v6;
  s64 v7;

  v3 = 0;
  v5 = 32;
  g_keywordctNum = 0;
  goto LABEL_11;
  while (1)
  {
    while (1)
    {
LABEL_11:
      LODWORD(v7) = *(u32 *)((char *)&s_sKeywordcd[v3]->listno->obj.klass + v5);
      if ((u32)v7 == -1)
        goto LABEL_27;
      v7 = (s32)v7;
      if (SLODWORD(s_iKeywordflglist->max_length) > (s64)(s32)v7)
      {
        v6 = evtBitCheck(s_iKeywordflglist[v7]);
        if (v6)
          break;
      }
      v5 += 4;
      if (v5 == 72)
        goto LABEL_27;
    }
    g_keywordctNum = g_keywordctNum + 1;
    g_keywordctList[g_keywordctNum] = v3;
LABEL_27:
    if (++v3 == 24)
      break;
    v5 = 32;
  }
}

// 0x1e6c590
void cmpMakekeywordlist(s32 cateno) {
  s64 v5;
  s64 v7;
  bool v10;

  v5 = 32;
  g_keywordNum = 0;
  do
  {
    LODWORD(v7) = *(u32 *)((char *)&s_sKeywordcd[cateno]->listno->obj.klass + v5);
    if ((u32)v7 == -1)
      break;
    v7 = (s32)v7;
    if (SLODWORD(s_iKeywordflglist->max_length) > (s64)(s32)v7)
    {
      v10 = evtBitCheck(s_iKeywordflglist[v7]);
      if (v10)
      {
        g_keywordNum = g_keywordNum + 1;
        g_keywordList[g_keywordNum] = *(u32 *)((char *)&s_sKeywordcd[cateno]->listno->obj.klass + v5);
      }
    }
    v5 += 4;
  }
  while (v5 != 72);
}

// 0x1e6c7c0
s32 cmpMenuDecideFunc2(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  dds3ProcessID_t *klass;
  s32 SelectID;
  s64 v8;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  klass = ProcessData[2].klass;
  SelectID = itfMenuGetSelectID(klass);
  v8 = g_keywordList[SelectID];
  LODWORD(v4[4].klass) = SelectID;
  HIDWORD(v4[4].klass) = v8;
  cmpReadFlgOn(v8);
  itfMenuSetFlag(v4[2].klass, 8, 0);
  itfMenuSetFlagMenu(v4[2].klass, -1, 1, 0);
  itfMenuSetFlagMenu(v4[2].klass, (s32)v4[4].klass, 1, 1);
  itfMenuSetFlagMenu(v4[2].klass, (s32)v4[4].klass, 8, 1);
  LODWORD(v4[3].klass) = 4;
  return 1;
}

// 0x1e6c980
s32 cmpMenuDecideFunc(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  dds3ProcessID_t *monitor;
  s32 SelectID;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  monitor = ProcessData[1].monitor;
  SelectID = itfMenuGetSelectID(monitor);
  HIDWORD(v4[3].monitor) = SelectID;
  cmpMakekeywordlist(g_keywordctList[SelectID]);
  itfMenuSetFlag(v4[1].monitor, 8, 0);
  itfMenuSetFlagMenu(v4[1].monitor, -1, 1, 0);
  itfMenuSetFlagMenu(v4[1].monitor, HIDWORD(v4[3].monitor), 1, 1);
  itfMenuSetFlagMenu(v4[1].monitor, HIDWORD(v4[3].monitor), 8, 1);
  LODWORD(v4[3].klass) = 1;
  return 1;
}

// 0x1e6cb40
void cmpListDrawFunc(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate) {
  s64 i;
  s64 v12;
  s64 v13;
  Il2CppObject *ProcessData;

  for (i = 32; i != 72; i += 4)
  {
    v12 = g_keywordctList[a_id];
    v13 = *(s32 *)((char *)&s_sKeywordcd[v12]->listno->obj.klass + i);
    if ((u32)v13 == -1)
      break;
    if (SLODWORD(s_iKeywordflglist->max_length) <= v13)
      continue;
    if (!evtBitCheck(s_iKeywordflglist[v13]))
      continue;
    if (!cmpReadFlgChk(v13))
    {
      ProcessData = dds3GetProcessData(g_mainPID);
      if (!ProcessData)
        return;
      return;
    }
  }
}

// 0x1e6cdd0
void cmpMenuDrawFunc(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate) {
  Il2CppObject *ProcessData;

  if (cmpReadFlgChk(g_keywordList[a_id]))
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
}

// 0x1e6cf30
void cmpMenuSetMenuImage2(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  sprHandle_t *klass;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  klass = ProcessData[1].klass;
  itfMenuLinkSprite(PID, klass);
  itfMenuSetSubABGR(PID, 0x46145A6Eu);
}

// 0x1e6d0a0
dds3ProcessID_t *cmpMenuCreateListPID(void) {
  dds3ProcessID_t *v1;
  dds3ProcessID_t *v2;
  s64 i;
  itfMenuDrawFunc_t v4;
  char *v7;
  itfMenuFunc_t v8;

  v1 = Allocate(dds3ProcessID_t);
  _ctor(v1, 0);
  v2 = itfMenuProcessStart();
  for (i = 0; ; ++i)
  {
    if (i >= g_keywordNum)
      break;
    v7 = strkeyword[g_keywordList[i]];
    v8 = Allocate(itfMenuFunc_t);
    _ctor(v8, 0, Method_Project_cmpKeyword_MenuDecideFunc2__, 0);
    itfMenuSetRootMenu(v2, i, v7, v8, "");
    itfMenuSetFlagMenu(v2, i, 128, 1);
    itfMenuSetFlagMenu(v2, i, 512, 1);
    v4 = Allocate(itfMenuDrawFunc_t);
    _ctor(v4, 0, Method_Project_cmpKeyword_MenuDrawFunc__, 0);
    itfMenuSetDrawFunc(v2, i, v4, 0);
  }
  itfMenuSetFlag(v2, 8, 1);
  itfMenuSetMoveAppear(v2, 1);
  itfMenuSetMoveDisappear(v2, 1);
  itfMenuSetFlag(v2, 2, 0);
  cmpMenuSetMenuImage2(v2);
  itfMenuUpdateLink(v2);
  return v2;
}

// 0x1e6d360
dds3ProcessID_t *cmpMenuCreateMenuPID(void) {
  dds3ProcessID_t *v1;
  dds3ProcessID_t *v2;
  s64 i;
  itfMenuDrawFunc_t v4;
  char *v7;
  itfMenuFunc_t v8;

  v1 = Allocate(dds3ProcessID_t);
  _ctor(v1, 0);
  v2 = itfMenuProcessStart();
  for (i = 0; ; ++i)
  {
    if (i >= g_keywordctNum)
      break;
    v7 = strkeywordcate[g_keywordctList[i]];
    v8 = Allocate(itfMenuFunc_t);
    _ctor(v8, 0, Method_Project_cmpKeyword_MenuDecideFunc__, 0);
    itfMenuSetRootMenu(v2, i, v7, v8, "");
    itfMenuSetFlagMenu(v2, i, 128, 1);
    itfMenuSetFlagMenu(v2, i, 512, 1);
    v4 = Allocate(itfMenuDrawFunc_t);
    _ctor(v4, 0, Method_Project_cmpKeyword_ListDrawFunc__, 0);
    itfMenuSetDrawFunc(v2, i, v4, 0);
  }
  itfMenuSetFlag(v2, 8, 1);
  itfMenuSetMoveAppear(v2, 1);
  itfMenuSetMoveDisappear(v2, 1);
  itfMenuSetFlag(v2, 2, 0);
  cmpMenuSetMenuImage(v2);
  itfMenuUpdateLink(v2);
  return v2;
}

// 0x1e6d620
void cmpMenuCallProcEnd(tagKEYWORD_MENU_WORK *wk) {
  dds3ProcessID_t *menuPID;

  menuPID = wk->menuPID;
  itfMenuProcessEnd(menuPID);
  itfMenuProcessEnd(wk->listPID);
}

// 0x1e6d6a0
s8 cmpMenuCheckProcEnd(tagKEYWORD_MENU_WORK *wk) {
  dds3ProcessID_t *p_menuPID;
  dds3ProcessID_t *menuPID;
  s8 v6;
  dds3ProcessID_t *p_listPID;
  dds3ProcessID_t *v9;
  dds3ProcessID_t *v10;
  dds3ProcessID_t *listPID;

  p_menuPID = &wk->menuPID;
  menuPID = wk->menuPID;
  if (!itfMenuProcessCheck(menuPID))
  {
    p_menuPID = 0;
    v6 = 0;
    listPID = wk->listPID;
    p_listPID = &wk->listPID;
    v9 = listPID;
    goto LABEL_9;
  }
  v6 = 1;
  v10 = wk->listPID;
  p_listPID = &wk->listPID;
  v9 = v10;
  if (!itfMenuProcessCheck(v9))
    goto LABEL_12;
  return v6 + 1;
LABEL_9:
  if (itfMenuProcessCheck(v9))
    return v6 + 1;
LABEL_12:
  p_listPID = 0;
  return v6;
}

// 0x1e6d7d0
dds3ProcessFunc_t cmpMenuProcess(dds3ProcessID_t *PID) {
  tagKEYWORD_MENU_WORK *ProcessData;
  f32 v6;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  s32 step;
  s32 flag;
  dds3ProcessID_t *ListPID;
  dds3ProcessID_t *v18;
  dds3ProcessID_t *v19;
  dds3ProcessID_t *v20;
  dds3ProcessID_t *v21;
  s32 v22;
  dds3ProcessID_t *v23;
  dds3ProcessFunc_t v25;
  dds3ProcessID_t *MenuPID;
  dds3ProcessID_t *v28;
  dds3ProcessID_t *v29;
  dds3ProcessID_t *keywordPID;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v6 = ProcessData->fNewAAnm + 0.1;
  v7 = v6 * 0.15915494;
  ProcessData->fNewAAnm = v6;
  v8 = -2147500000.0;
  if (v7 != INFINITY)
    v8 = (s32)v7;
  v9 = v7 - v8;
  v10 = 0.5;
  if (v9 <= 0.5)
  {
    if (v9 >= -0.5)
      goto LABEL_16;
    v11 = 1.0;
  }
  else
  {
    v11 = -1.0;
  }
  v9 = v9 + v11;
LABEL_16:
  if (v9 > 0.25)
  {
LABEL_19:
    v9 = v10 - v9;
    goto LABEL_20;
  }
  if (v9 < -0.25)
  {
    v10 = -0.5;
    goto LABEL_19;
  }
LABEL_20:
  v12 = v9 * 4.0;
  step = ProcessData->step;
  ProcessData->fNewAlpha = (f32)((f32)((f32)((f32)((f32)((f32)(v12 * 1.5707963) + (f32)((f32)(v12 * (f32)(v12 * v12)) * -0.6459637)) + (f32)((f32)((f32)(v12 * v12) * (f32)(v12 * (f32)(v12 * v12))) * 0.07968968)) + (f32)((f32)((f32)(v12 * v12) * (f32)((f32)(v12 * v12) * (f32)(v12 * (f32)(v12 * v12)))) * -0.0046737655)) + (f32)((f32)((f32)(v12 * v12) * (f32)((f32)(v12 * v12) * (f32)((f32)(v12 * v12) * (f32)(v12 * (f32)(v12 * v12))))) * 0.00015148419)) * 0.375)
                                + 0.75;
  switch (step)
  {
    case 0:
      flag = ProcessData->flag;
      if ((flag & 0x10) != 0)
      {
        ProcessData->flag = flag & 0xFFFFFFEF;
        MenuPID = cmpMenuCreateMenuPID();
        ProcessData->menuPID = MenuPID;
        v28 = ProcessData->menuPID;
        itfMenuStart(v28);
        ProcessData->selectID = 0xFFFFFFF;
        goto LABEL_53;
      }
      return 0;
    case 1:
      ListPID = cmpMenuCreateListPID();
      ProcessData->listPID = ListPID;
      v18 = ProcessData->listPID;
      itfMenuStart(v18);
      goto LABEL_42;
    case 2:
      v19 = ProcessData->menuPID;
      if (itfMenuProcessCheck(ProcessData->menuPID))
        return 0;
      ProcessData->menuPID = 0;
      v22 = 6;
LABEL_56:
      ProcessData->step = v22;
      return 0;
    case 3:
      v20 = ProcessData->listPID;
      if (itfMenuProcessCheck(v20))
        return 0;
      v21 = ProcessData->menuPID;
      itfMenuSetFlagMenu(v21, -1, 8, 0);
      itfMenuSetFlagMenu(ProcessData->menuPID, -1, 1, 1);
      itfMenuSetFlag(ProcessData->menuPID, 8, 1);
      ProcessData->listPID = 0;
LABEL_53:
      v22 = 2;
      goto LABEL_56;
    case 4:
      fclResetEx(ProcessData->keywordPID);
      fclStart(ProcessData->keywordPID, 1, ProcessData->msgno, 0);
      v22 = 5;
      goto LABEL_56;
    case 5:
      if (fclUpdateEx(ProcessData->keywordPID))
        return 0;
      v23 = ProcessData->listPID;
      itfMenuSetFlagMenu(v23, -1, 8, 0);
      itfMenuSetFlagMenu(ProcessData->listPID, -1, 1, 1);
      itfMenuSetSelectID(ProcessData->listPID, ProcessData->selectID2);
      itfMenuSetFlag(ProcessData->listPID, 8, 1);
LABEL_42:
      v22 = 3;
      goto LABEL_56;
    case 6:
      if (ProcessData->count)
      {
        goto LABEL_45;
      }
      v29 = ProcessData->menuPID;
      itfMenuProcessEnd(v29);
      itfMenuProcessEnd(ProcessData->listPID);
LABEL_45:
      if (cmpMenuCheckProcEnd(ProcessData))
      {
        ++ProcessData->count;
        return 0;
      }
      keywordPID = ProcessData->keywordPID;
      ProcessData->count = 0;
      ProcessData->step = 8;
      fclProcessEnd(keywordPID);
      return 0;
    case 8:
      v25 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v25, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v25;
    default:
      return 0;
  }
}

// 0x1e6de90
bool cmpMenuCheckWait(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return !LODWORD(ProcessData[3].klass) && (BYTE4(ProcessData[3].klass) & 0x10) == 0;
  return !LODWORD(ProcessData[3].klass) && (BYTE4(ProcessData[3].klass) & 0x10) == 0;
}

// 0x1e6dfc0
bool cmpMenuStart(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  if (LODWORD(ProcessData[3].klass))
    return 0;
  HIDWORD(ProcessData[3].klass) |= 0x10u;
  return 1;
}

// 0x1e6e100
s32 cmpMenuGetSelectID(void) {
  s32 *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return ProcessData[15];
  return ProcessData[15];
}

// 0x1e6e210
void cmpMenuRelease(tagKEYWORD_MENU_WORK *wk) {
  itfGeneralMenuFreeSpriteHnd();
  wk->hSpr = 0;
}

// 0x1e6e280
void cmpMenuShutdown(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  itfGeneralMenuFreeSpriteHnd();
  ProcessData[1].klass = 0;
  g_mainPID = 0;
}

// 0x1e6e3d0
void cmpProcStart(KEYWORD_MENUTYPE type) {
  *((u32 *)*((const MethodInfo *)cmpKeyword + 2).virtualMethodPointer + 24) = type;
  cmpMenuProcessStart();
  cmpMenuStart();
}

// 0x1e6e440
void cmpMenuProcessStart(void) {
  tagKEYWORD_MENU_WORK *v1;
  dds3ProcessFunc_t v3;
  shutdownfuncDelegate v4;
  dds3ProcessID_t *started;
  sprHandle_t *v11;
  dds3ProcessID_t *v13;
  dds3ProcessID_t *v14;

  v1 = Allocate(tagKEYWORD_MENU_WORK);
  _ctor(v1);
  v3 = Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_cmpKeyword_MenuProcess__, 0);
  v4 = Allocate(shutdownfuncDelegate);
  _ctor(v4, 0, Method_Project_cmpKeyword_MenuShutdown__, 0);
  started = dds3StartProcess("keyword_menu", 1023, 0, 0, v3, v4, v1);
  g_mainPID = started;
  v1->hSpr = generalMenu_g_hSpr;
  if (!(u64)v1->hSpr)
  {
    itfGeneralMenuLoadSpriteHnd();
    v11 = generalMenu_g_hSpr;
    v1->hSpr = v11;
  }
  *(u64 *)&v1->selectID = -1;
  cmpMakekeywordctlist();
  v13 = fclProcessStart();
  v1->keywordPID = v13;
  v14 = &v1->keywordPID;
  fclLoadDataEx(v14, "keyword.bmd", "", 1);
}

// 0x1e6e810
void cmpMenuProcessEnd(void) {
  Il2CppObject *ProcessData;
  s32 klass_high;

  if (!g_mainPID)
    return;
  if (!dds3ExistProcess(g_mainPID))
    return;
  goto LABEL_15;
LABEL_19:
  goto LABEL_21;
LABEL_15:
  ProcessData = dds3GetProcessData(g_mainPID);
  if (ProcessData)
    goto LABEL_19;
LABEL_21:
  klass_high = HIDWORD(ProcessData[3].klass);
  if ((klass_high & 1) == 0)
  {
    LOWORD(ProcessData[3].monitor) = 0;
    LODWORD(ProcessData[3].klass) = 6;
    HIDWORD(ProcessData[3].klass) = klass_high | 1;
  }
}

// 0x1e6e9c0
bool cmpMenuProcessCheck(void) {
  if (!g_mainPID)
    return 0;
  if (dds3GetProcessStat(g_mainPID) != 3)
  {
    if (dds3GetProcessStat(g_mainPID))
    {
      return 1;
    }
  }
  g_mainPID = 0;
  return 0;
}

// 0x1e6eb30
bool Update(void) {
  if (!g_mainPID)
    return 1;
  if (dds3GetProcessStat(g_mainPID) != 3)
  {
    if (dds3GetProcessStat(g_mainPID))
    {
      return 0;
    }
  }
  g_mainPID = 0;
  return 1;
}
