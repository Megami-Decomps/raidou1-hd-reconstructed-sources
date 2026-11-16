#include "types.h"
#include "GOH_MENU_ID.h"
#include "ITFMENU_CB_GF.h"
#include "dat.h"
#include "dds3kernelcore.h"
#include "evtbit.h"
#include "fcldrawback.h"
#include "fclmisc.h"
#include "gohcombunity.h"
#include "gohinit.h"
#include "gohmenu.h"
#include "itf.h"
#include "kernel.h"
#include "localize.h"
#include "raijindlc.h"

#define GOH_MENU_MAINPROC_NAME "goh_menu_main"
#define GOH_MENU_DRAWPROC_NAME "goh_menu_draw"

typedef enum {
    BACK0_FRAME = 10,
    BACK1_FRAME = 20,
} GOH_MENU_FADE;

typedef enum {
    GOH_MENU_PANEL_X = 45,
    GOH_MENU_PANEL_Y = 88,
    GOH_MENU_PANEL_W = 128,
    GOH_MENU_PANEL_H = 26,
    GOH_MENU_PANEL_FX = 10,
    GOH_MENU_PANEL_FY = 4,
    GOH_MENU_TITLE_X = 93,
    GOH_MENU_TITLE_Y = 27,
    GOH_MENU_TITLE_FX = -75,
    GOH_MENU_TITLE_FY = 16,
} GOH_MENU;

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct itfSprList_t itfSprList_t;
typedef struct tagGOH_MENU_WORK tagGOH_MENU_WORK;

dds3ProcessID_t *g_mainPID;
char *strGohMenu;
itfSprList_t *arrGohMenuPanel;
itfSprList_t *arrGohMenuSelect;
itfSprList_t *arrGohMenuTitle;
static u32 *s_uMenuFlag;
bool gohMenuActive;

// 0x1c05c90
s32 MenuAnimFunc(s32 mode) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *monitor;
  Il2CppClass *klass;
  s32 v11;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  monitor = ProcessData[1].monitor;
  itfMenuGetSelectID(monitor);
  if (mode == 1)
  {
    klass = _get_Instance()[18].klass;
    v11 = 3;
    goto LABEL_20;
  }
  if (mode)
    return 1;
  klass = _get_Instance()[18].klass;
  if (gohMenuActive)
  {
    v11 = 4;
LABEL_20:
    AnimSet(klass, v11, 0);
    return 1;
  }
  AnimSet(klass, 1, 0);
  gohMenuActive = 1;
  return 1;
}

// 0x1c05ea0
s32 gohCallFunc(void) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *monitor;
  s32 SelectID;
  Il2CppObject *Instance;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  monitor = ProcessData[1].monitor;
  SelectID = itfMenuGetSelectID(monitor);
  HIDWORD(ProcessData[3].klass) = SelectID;
  if ((SelectID | 0x10) == 0x16)
  {
    Instance = _get_Instance();
    TitleOff(Instance[17].monitor, 0);
  }
  return 1;
}

// 0x1c06020
s32 gohCheckOpen(GOH_MENU_ID MenuID) {
  s32 v4;

  v4 = s_uMenuFlag[MenuID];
  if (v4)
    return evtBitCheck(v4);
  return 1;
}

// 0x1c060e0
void gohSetCommand(tagGOH_MENU_WORK *wk) {
  dds3ProcessID_t *menuPID;
  itfMoverFunc_t v4;
  s32 v36;
  bool v37;
  itfMenuDrawFunc_t v46;

  menuPID = wk->menuPID;
  v4 = Allocate(itfMoverFunc_t);
  _ctor(v4, 0, Method_Project_gohMenu_MenuAnimFunc__, 0);
  itfMoverSetMenu(menuPID, v4);
  itfMenuSetMenuTitle(menuPID, "", "");
  gohSetRootMenu(menuPID, 1, strGohMenu);
  gohSetRootMenu(menuPID, 7, strGohMenu);
  gohSetRootMenu(menuPID, 2, strGohMenu);
  gohSetRootMenu(menuPID, 3, strGohMenu);
  gohSetRootMenu(menuPID, 24, strGohMenu);
  gohSetRootMenu(menuPID, 4, strGohMenu);
  gohSetRootMenu(menuPID, 28, strGohMenu);
  gohSetRootMenu(menuPID, 5, strGohMenu);
  gohSetRootMenu(menuPID, 23, strGohMenu);
  gohSetMenu(menuPID, 8, 3, strGohMenu);
  gohSetMenu(menuPID, 9, 3, strGohMenu);
  gohSetMenu(menuPID, 25, 24, strGohMenu);
  gohSetMenu(menuPID, 26, 24, strGohMenu);
  gohSetMenu(menuPID, 27, 24, strGohMenu);
  gohSetMenu(menuPID, 10, 4, strGohMenu);
  gohSetMenu(menuPID, 11, 4, strGohMenu);
  gohSetMenu(menuPID, 12, 4, strGohMenu);
  gohSetMenu(menuPID, 13, 11, strGohMenu);
  gohSetMenu(menuPID, 14, 11, strGohMenu);
  gohSetMenu(menuPID, 15, 11, strGohMenu);
  gohSetMenu(menuPID, 16, 11, strGohMenu);
  gohSetMenu(menuPID, 19, 11, strGohMenu);
  gohSetMenu(menuPID, 20, 11, strGohMenu);
  gohSetMenu(menuPID, 17, 11, strGohMenu);
  gohSetMenu(menuPID, 18, 11, strGohMenu);
  gohSetMenu(menuPID, 6, 1, strGohMenu);
  gohSetMenu(menuPID, 21, 1, strGohMenu);
  gohSetMenu(menuPID, 22, 1, strGohMenu);
  v36 = s_uMenuFlag[6];
  if (v36)
  {
    v37 = evtBitCheck(v36);
    if (!v37)
    {
      gohSetFlagMenu(menuPID, 1, 64, 0);
    }
  }
  gohSetFlagMenu(menuPID, 5, 64, 0);
  gohSetFlagMenu(menuPID, 6, 64, 0);
  gohSetFlagMenu(menuPID, 21, 64, 0);
  gohSetFlagMenu(menuPID, 22, 64, 0);
  gohSetFlagMenu(menuPID, 23, 64, 0);
  gohSetFlagMenu(menuPID, 7, 64, 0);
  gohSetFlagMenu(menuPID, 28, 64, 0);
  gohSetFlagMenu(menuPID, 5, 32, 1);
  gohSetFlagMenu(menuPID, 28, 32, 1);
  v46 = Allocate(itfMenuDrawFunc_t);
  _ctor(v46, 0, Method_Project_gohMenu_DrawTitle__, 0);
  itfMenuSetDrawFunc(menuPID, 1, v46, 0);
  gohChkEnableSelect(wk);
  itfMenuSetSpriteData(menuPID, 0, 93, 27, 0, 0, -75, 16, 0, arrGohMenuTitle);
  itfMenuSetSpriteData(menuPID, 1, 45, 88, 128, 26, 10, 4, 0, arrGohMenuPanel);
  itfMenuSetSpriteData(menuPID, 2, 45, 88, 128, 26, 10, 4, 0, arrGohMenuSelect);
  itfMenuSetMoveAppear(menuPID, 1);
  itfMenuSetMoveDisappear(menuPID, 1);
}

// 0x1c06da0
dds3ProcessFunc_t gohProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *monitor;
  dds3ProcessID_t *v7;
  s32 klass_low;
  s32 v10;
  dds3ProcessID_t *v12;
  dds3ProcessFunc_t v13;
  dds3ProcessID_t *v14;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  switch (LODWORD(ProcessData[2].monitor))
  {
    case 0:
      gohSetSelectIndex(-1);
      monitor = ProcessData[1].monitor;
      if (!itfMenuProcessCheck(monitor))
      {
        v10 = 1;
        goto LABEL_41;
      }
      v7 = ProcessData[1].monitor;
      if (itfMenuGetCtrlType(ProcessData[1].monitor) == 5)
      {
        HIDWORD(ProcessData[2].monitor) |= 8u;
        return 0;
      }
      return 0;
    case 1:
      klass_low = SLOWORD(ProcessData[3].klass);
      if (!LOWORD(ProcessData[3].klass))
      {
        HIDWORD(ProcessData[2].monitor) &= ~4u;
        goto LABEL_32;
      }
      if (klass_low < 2)
        goto LABEL_32;
      v10 = 2;
      goto LABEL_41;
    case 2:
      if (LOWORD(ProcessData[3].klass))
      {
        goto LABEL_23;
      }
      v14 = ProcessData[1].monitor;
      itfMenuProcessEnd(v14);
LABEL_23:
      v12 = ProcessData[1].monitor;
      if (itfMenuProcessCheck(ProcessData[1].monitor))
        goto LABEL_27;
      goto LABEL_9001;
      if (itfMenuProcessCheck(v12))
      {
LABEL_27:
        LOWORD(klass_low) = ProcessData[3].klass;
LABEL_32:
        LOWORD(ProcessData[3].klass) = klass_low + 1;
        return 0;
      }
LABEL_9001:
      ProcessData[1].monitor = 0;
      v10 = 3;
LABEL_41:
      LOWORD(ProcessData[3].klass) = 0;
      LODWORD(ProcessData[2].monitor) = v10;
      return 0;
    case 3:
      v13 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v13, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v13;
    default:
      return 0;
  }
}

// 0x1c07420
GOH_MENU_ID gohGetSelectIndex(void) {
  s32 *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return ProcessData[13];
  return ProcessData[13];
}

// 0x1c07530
void gohDrawTitle(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *monitor;
  u8 Alpha;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  monitor = ProcessData[1].monitor;
  Alpha = itfMenuImgGetAlpha(monitor, 0);
  itfDrawMiscSpriteAlpha(29, 38, 0, Alpha, ProcessData[2].klass, 202, 109);
}

// 0x1c076a0
bool gohBackCombMenuCheck(void) {
  gohData_t *GohData;
  gohData_t *v3;
  s64 v4;
  s32 Length;
  s64 v6;
  void *Result2;
  s64 v8;
  s32 v9;

  GohData = GohGetGohData();
  if (!GohData)
    return (char)GohData;
  v3 = GohData;
  if (datGetStockAliveDevilNum() < 2)
    goto LABEL_14;
  if (get_IsCompleted(v3->result2Task, 0) && GetLength(v3->Result2, 0, 0) >= 1)
  {
    v4 = 0;
    while (GetLength(v3->Result2, 1, 0) < 1)
    {
LABEL_15:
      ++v4;
      Length = GetLength(v3->Result2, 0, 0);
      LOBYTE(GohData) = 0;
      if (v4 >= Length)
        return (char)GohData;
    }
    v6 = 0;
    while (1)
    {
      Result2 = v3->Result2;
      v8 = *(u64 *)(*((u64 *)&Result2[2].klass + v6 + v4 * (s64)Result2[1].klass->_1.name) + 32);
      v9 = *(s16 *)(v8 + 22);
      if (*(u16 *)(v8 + 22))
      {
        if (DlcDevilSelCheck(v9))
        {
          LOBYTE(GohData) = 1;
          return (char)GohData;
        }
        Result2 = v3->Result2;
      }
      if (++v6 >= GetLength(Result2, 1, 0))
        goto LABEL_15;
    }
  }
LABEL_14:
  LOBYTE(GohData) = 0;
  return (char)GohData;
}

// 0x1c06cd0
void gohChkEnableSelect(tagGOH_MENU_WORK *wk) {
  dds3ProcessID_t *menuPID;
  bool v5;

  menuPID = wk->menuPID;
  v5 = gohBackCombMenuCheck();
  itfMenuSetFlagMenu(menuPID, 22, 2, v5);
}

// 0x1c067a0
void gohSetRootMenu(dds3ProcessID_t *PID, GOH_MENU_ID MenuID, char *pStr) {
  s32 v9;
  Il2CppClass **v10;
  char *v11;
  char **v12;
  char *v13;
  char *LocalizeText;
  itfMenuFunc_t v15;
  char *v16;

  v9 = s_uMenuFlag[MenuID];
  if (v9)
  {
    if (!evtBitCheck(v9))
      return;
  }
  v10 = &pStr->obj.klass + MenuID;
  v13 = v10[4];
  v12 = (v10 + 4);
  v11 = v13;
  LocalizeText = GetLocalizeText(v11, 0);
  v15 = Allocate(itfMenuFunc_t);
  _ctor(v15, 0, Method_Project_gohMenu_CallFunc__, 0);
  v16 = *v12;
  itfMenuSetRootMenu(PID, MenuID, LocalizeText, v15, v16);
}

// 0x1c06990
void gohSetMenu(dds3ProcessID_t *PID, GOH_MENU_ID MenuID, GOH_MENU_ID ParentMenuID, char *pStr) {
  s32 v11;
  Il2CppClass **v12;
  char *v13;
  char **v14;
  char *v15;
  char *LocalizeText;
  itfMenuFunc_t v17;
  char *v18;

  v11 = s_uMenuFlag[MenuID];
  if (v11)
  {
    if (!evtBitCheck(v11))
      return;
  }
  v12 = &pStr->obj.klass + MenuID;
  v15 = v12[4];
  v14 = (v12 + 4);
  v13 = v15;
  LocalizeText = GetLocalizeText(v13, 1);
  v17 = Allocate(itfMenuFunc_t);
  _ctor(v17, 0, Method_Project_gohMenu_CallFunc__, 0);
  v18 = *v14;
  itfMenuSetMenu(PID, MenuID, ParentMenuID, LocalizeText, v17, v18);
}

// 0x1c06b80
void gohSetFlagMenu(dds3ProcessID_t *PID, GOH_MENU_ID MenuID, ITFMENU_CB_GF Flag, bool Bool) {
  s32 v11;

  v11 = s_uMenuFlag[MenuID];
  if (v11)
  {
    if (!evtBitCheck(v11))
      return;
  }
  itfMenuSetFlagMenu(PID, MenuID, Flag, Bool);
}

// 0x1c072d0
void gohCallProcEnd(tagGOH_MENU_WORK *wk) {
  dds3ProcessID_t *menuPID;

  menuPID = wk->menuPID;
  itfMenuProcessEnd(menuPID);
}

// 0x1c07360
u8 gohCheckProcEnd(tagGOH_MENU_WORK *wk) {
  dds3ProcessID_t *p_menuPID;
  dds3ProcessID_t *v5;
  dds3ProcessID_t *menuPID;

  menuPID = wk->menuPID;
  p_menuPID = &wk->menuPID;
  v5 = menuPID;
  if (itfMenuProcessCheck(v5))
    return 1;
  p_menuPID = 0;
  return 0;
}

// 0x1c07890
void gohShutdown(dds3ProcessID_t *PID) {
  dds3ProcessID_t *ProcessData;
  s64 naturalAligment;
  dds3ProcessID_t *v5;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (ProcessData)
    LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((tagGOH_MENU_WORK **)(ProcessData)[1].next + naturalAligment - 1) != tagGOH_MENU_WORK;
  v5 = ProcessData + 2;
  if (dds3ExistProcess(ProcessData + 2))
  {
    dds3KillProcess(v5, 0);
  }
  v5 = 0;
  g_mainPID = 0;
}

// 0x1c079f0
dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 monitor_high;
  Il2CppClass *klass;
  u32 v7;
  Il2CppClass *v8;
  u32 v9;
  u8 *monitor;
  u8 v11;
  u8 v12;
  sprHandle_t *v13;
  s32 v14;
  u8 *v15;
  s16 v16;
  u8 *v17;
  dds3ProcessID_t *p_monitor;
  dds3ProcessID_t *v19;
  dds3ProcessID_t *v20;
  dds3ProcessID_t *v21;
  u32 Alpha;
  dds3ProcessID_t *v23;
  u32 v24;
  s32 v25;
  sprHandle_t *v26;
  Il2CppObject *Instance;
  bool v28;
  s32 BackStat;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor_high = HIDWORD(ProcessData[2].monitor);
  if ((monitor_high & 4) != 0)
  {
    if ((monitor_high & 8) != 0)
    {
      HIDWORD(ProcessData[2].monitor) = monitor_high & 0xFFFFFFF7;
      klass = ProcessData[4].klass;
      if ((monitor_high & 0x20) != 0)
      {
        LOBYTE(klass->_1.byval_arg.data) = -1;
        *((u8 *)ProcessData[3].monitor + 32) = -1;
        v7 = HIDWORD(ProcessData[2].monitor) & 0xFFFFFFDF;
      }
      else
      {
        LOBYTE(klass->_1.byval_arg.data) = 1;
        *((u8 *)ProcessData[3].monitor + 32) = 0;
        v7 = HIDWORD(ProcessData[2].monitor) | 0x20;
      }
      HIDWORD(ProcessData[2].monitor) = v7;
      *((u8 *)ProcessData[4].monitor + 32) = 0;
      monitor_high = HIDWORD(ProcessData[2].monitor);
    }
    if ((monitor_high & 0x10) != 0)
    {
      HIDWORD(ProcessData[2].monitor) = monitor_high & 0xFFFFFFEF;
      v8 = ProcessData[4].klass;
      if ((monitor_high & 0x40) != 0)
      {
        BYTE1(v8->_1.byval_arg.data) = -1;
        *((u8 *)ProcessData[3].monitor + 33) = -1;
        v9 = HIDWORD(ProcessData[2].monitor) & 0xFFFFFFBF;
      }
      else
      {
        BYTE1(v8->_1.byval_arg.data) = 1;
        *((u8 *)ProcessData[3].monitor + 33) = 0;
        v9 = HIDWORD(ProcessData[2].monitor) | 0x40;
      }
      HIDWORD(ProcessData[2].monitor) = v9;
      *((u8 *)ProcessData[4].monitor + 33) = 0;
    }
    monitor = ProcessData[3].monitor;
    v11 = monitor[32];
    v12 = monitor[33];
    v13 = ProcessData[2].klass;
    fclBackSprite(3, v11, v12, v13);
    if (LOBYTE(ProcessData[4].klass->_1.byval_arg.data))
    {
      v14 = 26215 * (s16)(255 * (char)++*((u8 *)ProcessData[4].monitor + 32));
      *((u8 *)ProcessData[3].monitor + 32) = ((u32)v14 >> 18) + (v14 < 0);
      if (SLOBYTE(ProcessData[4].klass->_1.byval_arg.data) < 0)
        *((u8 *)ProcessData[3].monitor + 32) = ~*((u8 *)ProcessData[3].monitor + 32);
      v15 = ProcessData[4].monitor;
      if ((char)v15[32] >= 10)
      {
        v15[32] = 0;
        LOBYTE(ProcessData[4].klass->_1.byval_arg.data) = 0;
      }
    }
    if (BYTE1(ProcessData[4].klass->_1.byval_arg.data))
    {
      v16 = (char)++*((u8 *)ProcessData[4].monitor + 33);
      *((u8 *)ProcessData[3].monitor + 33) = ((u32)(26215 * (s16)(255 * v16)) >> 19)
                                              + (26215 * (s16)(255 * v16) < 0);
      if (SBYTE1(ProcessData[4].klass->_1.byval_arg.data) < 0)
        *((u8 *)ProcessData[3].monitor + 33) = ~*((u8 *)ProcessData[3].monitor + 33);
      v17 = ProcessData[4].monitor;
      if ((char)v17[33] >= 20)
      {
        v17[33] = 0;
        BYTE1(ProcessData[4].klass->_1.byval_arg.data) = 0;
      }
    }
    p_monitor = &ProcessData[1].monitor;
    if (!!dds3ExistProcess(&ProcessData[1].monitor))
    {
      v19 = p_monitor;
      if (itfMenuGetFlag(v19, 8u))
      {
        v20 = p_monitor;
        if (!itfMenuGetWaitType(v20))
        {
          v21 = p_monitor;
          Alpha = itfMenuImgGetAlpha(v21, 1);
          if (Alpha)
          {
            v23 = p_monitor;
            v24 = itfMenuGetSelectID(v23) - 1;
            if (v24 <= 0x1B && ((0xFF00FFFu >> v24) & 1) != 0)
            {
              v25 = dword_3E62548[v24];
              v26 = ProcessData[2].klass;
              itfDrawMiscSpriteAlpha(0, 379, 0, Alpha, v26, 99, 109);
              itfDrawMiscSpriteAlpha(-10, 381, 0, Alpha, ProcessData[2].klass, 101, 109);
              itfDrawMiscSpriteAlpha(332, 381, 0, Alpha, ProcessData[2].klass, 102, 109);
              itfDrawMiscSpriteAlpha(16, 385, 0, Alpha, ProcessData[2].klass, 100, 109);
              fclCommandHelp(v25, Alpha);
            }
            fclChkMessageDraw();
          }
        }
      }
    }
    if (gohGetBackStat() == 1)
    {
      Instance = _get_Instance();
LABEL_60:
      v28 = 1;
LABEL_70:
      BgActive(Instance, v28, 0);
      return 0;
    }
    if (gohGetBackStat() == 3)
    {
      Instance = _get_Instance();
      goto LABEL_69;
    }
    BackStat = (u8)gohGetBackStat();
    Instance = _get_Instance();
    if (BackStat == 2)
      goto LABEL_60;
LABEL_69:
    v28 = 0;
    goto LABEL_70;
  }
  return 0;
}

// 0x1c071b0
void gohSetSelectIndex(GOH_MENU_ID idx) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  HIDWORD(ProcessData[3].klass) = idx;
}

// 0x1c08130
void gohStart(void) {
  tagGOH_MENU_WORK *ProcessData;
  dds3ProcessID_t *menuPID;
  s32 flag;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  gohChkEnableSelect(ProcessData);
  menuPID = ProcessData->menuPID;
  itfMenuStart(menuPID);
  gohSetSelectIndex(-1);
  flag = ProcessData->flag;
  if ((flag & 0x20) == 0)
    ProcessData->flag = flag | 8;
}

// 0x1c082a0
void gohSetLock(bool a_bLock) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *monitor;

  if (!g_mainPID)
    return;
  goto LABEL_9;
LABEL_13:
  goto LABEL_15;
LABEL_9:
  ProcessData = dds3GetProcessData(g_mainPID);
  if (ProcessData)
    goto LABEL_13;
LABEL_15:
  monitor = ProcessData[1].monitor;
  if (monitor)
  {
    itfMenuSetFlag(monitor, 256, a_bLock);
  }
}

// 0x1c08420
void gohSetFocus(bool a_bFocus) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *monitor;

  if (!g_mainPID)
    return;
  goto LABEL_9;
LABEL_13:
  goto LABEL_15;
LABEL_9:
  ProcessData = dds3GetProcessData(g_mainPID);
  if (ProcessData)
    goto LABEL_13;
LABEL_15:
  monitor = ProcessData[1].monitor;
  if (monitor)
  {
    itfMenuSetFlag(monitor, 8, a_bFocus);
  }
}

// 0x1c085a0
bool gohGetFocus(void) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *monitor;

  if (!g_mainPID)
    return 0;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_15;
  goto LABEL_13;
  if (!ProcessData)
LABEL_13:
LABEL_15:
  monitor = ProcessData[1].monitor;
  if (!monitor)
    return 0;
  return itfMenuGetFlag(monitor, 8u);
}

// 0x1c08730
void gohCallDrawBack(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  HIDWORD(ProcessData[2].monitor) |= 0x10u;
}

// 0x1c08840
void gohSetDrawBack(bool a_bDraw, bool a_bFade) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  char v10;
  char v11;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  klass = ProcessData[4].klass;
  if (a_bDraw)
  {
    if (a_bFade)
    {
      if (BYTE1(klass->_1.byval_arg.data) == 1)
        return;
      v10 = 0;
      v11 = 1;
      goto LABEL_21;
    }
    v11 = 0;
  }
  else
  {
    if (!a_bFade)
    {
      v11 = 0;
      v10 = 0;
      goto LABEL_21;
    }
    if (BYTE1(klass->_1.byval_arg.data) == 255)
      return;
    v11 = -1;
  }
  v10 = -1;
LABEL_21:
  BYTE1(klass->_1.byval_arg.data) = v11;
  *((u8 *)ProcessData[3].monitor + 33) = v10;
  *((u8 *)ProcessData[4].monitor + 33) = 0;
}

// 0x1c07fd0
s8 gohGetBackStat(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  if ((BYTE4(ProcessData[2].monitor) & 4) == 0)
    return 0;
  if (BYTE1(ProcessData[4].klass->_1.byval_arg.data))
  {
    if (SBYTE1(ProcessData[4].klass->_1.byval_arg.data) >= 1)
      return 1;
    else
      return 3;
  }
  else
  {
    if (!*((u8 *)ProcessData[3].monitor + 33))
      return 0;
    if (*((u8 *)ProcessData[3].monitor + 33) == 255)
      return 2;
    else
      return -1;
  }
}

// 0x1c089c0
void ProcessStart(void) {
  tagGOH_MENU_WORK *v1;
  dds3ProcessFunc_t v2;
  shutdownfuncDelegate v3;
  dds3ProcessID_t *started;
  dds3ProcessFunc_t v6;
  dds3ProcessID_t *v7;
  dds3ProcessID_t *v8;
  sprHandle_t *SpriteHandle;

  v1 = Allocate(tagGOH_MENU_WORK);
  _ctor(v1, 0);
  v2 = Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_gohMenu_Process__, 0);
  v3 = Allocate(shutdownfuncDelegate);
  _ctor(v3, 0, Method_Project_gohMenu_Shutdown__, 0);
  started = dds3StartProcess("goh_menu_main", 1023, 0, 0, v2, v3, v1);
  g_mainPID = started;
  v6 = Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_gohMenu_DrawProcess__, 0);
  v7 = dds3StartProcess("goh_menu_draw", 11029, 0, 0, v6, 0, v1);
  v1->drawPID = v7;
  v8 = itfMenuProcessStart();
  v1->menuPID = v8;
  SpriteHandle = gohGetSpriteHandle();
  v1->hSpr = SpriteHandle;
  itfMenuLinkSprite(v1->menuPID, v1->hSpr);
  gohSetCommand(v1);
  v1->flag |= 4u;
  gohSetSelectIndex(0);
}

// 0x1c08c80
void ProcessEnd(void) {
  Il2CppObject *ProcessData;
  s32 monitor_high;

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
  monitor_high = HIDWORD(ProcessData[2].monitor);
  if ((monitor_high & 1) == 0)
  {
    LOWORD(ProcessData[3].klass) = 0;
    LODWORD(ProcessData[2].monitor) = 1;
    HIDWORD(ProcessData[2].monitor) = monitor_high | 1;
  }
}

// 0x1c08e20
bool ProcessCheck(void) {
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

// 0x1c08fa0
void gohSetEnableSelect(GOH_MENU_ID MenuID, bool Bool) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *monitor;

  if (!g_mainPID)
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  monitor = ProcessData[1].monitor;
  itfMenuSetFlagMenu(monitor, MenuID, 2, Bool);
}

// 0x1c09120
s32 gohCheckMovePrev(void) {
  dds3ProcessID_t *ProcessData;
  s64 naturalAligment;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *v7;

  if (!g_mainPID)
    return 0;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (ProcessData)
    LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((tagGOH_MENU_WORK **)(ProcessData)[1].next + naturalAligment - 1) != tagGOH_MENU_WORK;
  v6 = ProcessData[3];
  if (!v6)
    return 1;
  if (itfMenuGetCtrlType(ProcessData[3]) == 3)
    return 1;
  v7 = ProcessData[3];
  return itfMenuGetCtrlType(v7) == 5;
}

// 0x1c09300
void gohSetDraw(bool a_bDraw) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *monitor;
  bool v8;
  s32 v9;

  if (!g_mainPID)
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  monitor = ProcessData[1].monitor;
  v8 = a_bDraw;
  if (a_bDraw)
    v9 = 4;
  else
    v9 = 0;
  itfMenuSetFlag(monitor, 1, v8);
  HIDWORD(ProcessData[2].monitor) = HIDWORD(ProcessData[2].monitor) & 0xFFFFFFFB | v9;
}

// 0x1c094a0
dds3ProcessID_t *gohGetMenuPID(void) {
  dds3ProcessID_t *ProcessData;
  s64 naturalAligment;

  if (!g_mainPID)
    return 0;
  ProcessData = (dds3ProcessID_t *)dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return ProcessData[3];
  LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((tagGOH_MENU_WORK **)(ProcessData)[1].next + naturalAligment - 1) != tagGOH_MENU_WORK;
  return ProcessData[3];
}
