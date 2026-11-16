#include "types.h"
#include "buttonguide.h"
#include "cmpmain.h"
#include "dds3kernelcore.h"
#include "evtbit.h"
#include "fcldrawback.h"
#include "itf.h"
#include "jmscyousatable.h"
#include "jmsinit.h"
#include "jmsmain.h"
#include "jmsmenu.h"
#include "kernel.h"
#include "localize.h"
#include "raijindlc.h"

typedef enum {
    JMS_MENU_STEP_MAIN = 0,
    JMS_MENU_STEP_DRAW_OFF = 1,
    JMS_MENU_STEP_RELEASE = 2,
    JMS_MENU_STEP_END = 3,
} JMS_MENU_STEP;

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct itfSprList_t itfSprList_t;

dds3ProcessID_t *g_mainPID;
bool selectFlag;
static char *strJmsMenu;
static itfSprList_t *arrJmsMenuPanel;
static itfSprList_t *arrJmsMenuSelect;
static itfSprList_t *arrJmsMenuBekkenFilePanel;
static itfSprList_t *arrJmsMenuBekkenFileSelect;
static itfSprList_t *arrJmsMenuBekkenPanel;
static itfSprList_t *arrJmsMenuTitle;
u32 *MenuFlag;
bool MenuActive;
s32 TITLEMODE;
bool TITLEFADEOUT;
bool TITLEFADEIN;

static s32 CallFunc(void);
static void DrawTitle(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate);
static s32 CheckFlagTGS(s32 MenuID);
static void SetRootMenu(dds3ProcessID_t *PID, s32 MenuID, char *pStr);
static void SetMenu(dds3ProcessID_t *PID, s32 MenuID, s32 ParentMenuID, char *pStr);
static void SetFlagMenu(dds3ProcessID_t *PID, s32 MenuID, u32 Flag, bool Bool);
static s32 CheckCyousaFlag(s32 Type);
static void SetCommand(void *wk);
static void CallProcEnd(void *wk);
static u8 CheckProcEnd(void *wk);
static dds3ProcessFunc_t Process(dds3ProcessID_t *PID);
static void Release(void *wk);
static void Shutdown(dds3ProcessID_t *PID);
static dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *PID);

// 0x1cebfa0
static s32 CallFunc(void) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *klass;
  s32 SelectID;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  klass = ProcessData[1].klass;
  SelectID = itfMenuGetSelectID(klass);
  HIDWORD(ProcessData[3].klass) = SelectID;
  if ((u32)(SelectID - 12) <= 0xB)
  {
    SetTitleAnim(jmsUIctrlSub, 2, 0);
    SetBackAnim(jmsUIctrlSub, 2, 0);
  }
  return 1;
}

// 0x1cec140
s32 jmsAnimFunc(s32 mode) {
  s32 v8;

  if (jmsUiCampCheck)
    return 0;
  if (mode == 1)
  {
    v8 = 2;
    goto LABEL_12;
  }
  if (mode)
    return 1;
  if (MenuActive)
  {
    v8 = 3;
LABEL_12:
    AnimSet(jmsUIctrlSub, v8, 0);
    return 1;
  }
  AnimSet(jmsUIctrlSub, 0, 0);
  MenuActive = 1;
  return 1;
}

// 0x1cec260
static void DrawTitle(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *klass;
  u8 Alpha;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  klass = ProcessData[1].klass;
  Alpha = itfMenuImgGetAlpha(klass, 0);
  itfDrawMiscSpriteAlpha(29, 38, 0, Alpha, ProcessData[2].klass, 103, 109);
}

// 0x1cec3d0
static s32 CheckFlagTGS(s32 MenuID) {
  return ((u32)(MenuID - 3) < 2) & evtBitCheck(864);
}

// 0x1cec410
static void SetRootMenu(dds3ProcessID_t *PID, s32 MenuID, char *pStr) {
  s32 v8;
  bool v9;
  itfMenuFunc_t v10;

  v8 = MenuFlag[MenuID];
  v9 = evtBitCheck(864);
  if (((u32)(MenuID - 3) > 1 || !v9) && (!v8 || evtBitCheck(v8)))
  {
    v10 = Allocate(itfMenuFunc_t);
    _ctor(v10, 0, Method_Project_jmsMenu_CallFunc__, 0);
    itfMenuSetRootMenu(PID, MenuID, pStr, v10, "");
  }
}

// 0x1cec570
static void SetMenu(dds3ProcessID_t *PID, s32 MenuID, s32 ParentMenuID, char *pStr) {
  s32 v10;
  bool v11;
  itfMenuFunc_t v12;

  v10 = MenuFlag[MenuID];
  v11 = evtBitCheck(864);
  if (((u32)(MenuID - 3) > 1 || !v11) && (!v10 || evtBitCheck(v10)))
  {
    v12 = Allocate(itfMenuFunc_t);
    _ctor(v12, 0, Method_Project_jmsMenu_CallFunc__, 0);
    itfMenuSetMenu(PID, MenuID, ParentMenuID, pStr, v12, "");
  }
}

// 0x1cec6d0
static void SetFlagMenu(dds3ProcessID_t *PID, s32 MenuID, u32 Flag, bool Bool) {
  s32 v10;
  bool v11;

  v10 = MenuFlag[MenuID];
  v11 = evtBitCheck(864);
  if (((u32)(MenuID - 3) > 1 || !v11) && (!v10 || evtBitCheck(v10)))
  {
    itfMenuSetFlagMenu(PID, MenuID, Flag, Bool);
  }
}

// 0x1cec7d0
static s32 CheckCyousaFlag(s32 Type) {
  s32 *v3;
  s64 v4;
  u32 *v5;

  v3 = NewSpecific(s32, 3u);
  v3[2] = 0;
  v4 = v3;
  *(u64 *)&v3[0] = 0;
  v5 = &v3[0];
  if (evtBitCheck(jmsCyousaRootTable[0]->pData[0]))
    *v5 = 1;
  if (evtBitCheck(jmsCyousaRootTable[0]->pData[1]))
    *v5 = 1;
  if (evtBitCheck(jmsCyousaRootTable[0]->pData[2]))
    *v5 = 1;
  if (evtBitCheck(jmsCyousaRootTable[0]->pData[3]))
    *v5 = 1;
  *(u32 *)(v4 + 36) = 0;
  if (evtBitCheck(jmsCyousaRootTable[1]->pData[0]))
    *(u32 *)(v4 + 36) = 1;
  if (evtBitCheck(jmsCyousaRootTable[1]->pData[1]))
    *(u32 *)(v4 + 36) = 1;
  if (evtBitCheck(jmsCyousaRootTable[1]->pData[2]))
    *(u32 *)(v4 + 36) = 1;
  if (evtBitCheck(jmsCyousaRootTable[1]->pData[3]))
    *(u32 *)(v4 + 36) = 1;
  *(u32 *)(v4 + 40) = 0;
  if (evtBitCheck(jmsCyousaRootTable[2]->pData[0]))
    *(u32 *)(v4 + 40) = 1;
  if (evtBitCheck(jmsCyousaRootTable[2]->pData[1]))
    *(u32 *)(v4 + 40) = 1;
  if (evtBitCheck(jmsCyousaRootTable[2]->pData[2]))
    *(u32 *)(v4 + 40) = 1;
  if (evtBitCheck(jmsCyousaRootTable[2]->pData[3]))
    *(u32 *)(v4 + 40) = 1;
  if (Type)
  {
    if ((u32)(Type - 1) <= 2 && *(u32 *)(v4 + 4 * (u32)(Type - 1) + 32))
      return 1;
  }
  else
  {
    if (*v5)
      return 1;
    if (*(u32 *)(v4 + 36))
      return 1;
    if (*(u32 *)(v4 + 40))
      return 1;
  }
  return 0;
}

// 0x1cecbb0
static void SetCommand(void *wk) {
  dds3ProcessID_t *menuPID;
  char *v6;
  char *LocalizeText;
  char *v10;
  char *v13;
  char *v16;
  char *v19;
  char *v22;
  u32 *v45;
  char *v47;
  char *v48;
  char *v53;
  char *v54;
  char *v58;
  char *v59;
  char *v63;
  char *v64;
  char *v72;
  char *v73;
  char *v76;
  char *v79;
  char *v82;
  char *v85;
  char *v88;
  char *v91;
  char *v94;
  char *v97;
  char *v100;
  char *v103;
  char *v106;
  itfMenuDrawFunc_t v121;
  itfMoverFunc_t v122;

  menuPID = wk->menuPID;
  itfMenuSetMenuTitle(menuPID, "", "");
  v6 = strJmsMenu[0];
  LocalizeText = GetLocalizeText(v6, 0);
  SetRootMenu(menuPID, 1, LocalizeText);
  v10 = GetLocalizeText(strJmsMenu[2], 0);
  SetRootMenu(menuPID, 3, v10);
  v13 = GetLocalizeText(strJmsMenu[3], 0);
  SetRootMenu(menuPID, 4, v13);
  v16 = GetLocalizeText(strJmsMenu[4], 0);
  SetRootMenu(menuPID, 5, v16);
  v19 = GetLocalizeText(strJmsMenu[5], 0);
  SetRootMenu(menuPID, 6, v19);
  v22 = GetLocalizeText(strJmsMenu[23], 0);
  SetRootMenu(menuPID, 7, v22);
  if (!!IsBuyItem())
  {
    v47 = strJmsMenu[24];
    v48 = GetLocalizeText(v47, 0);
    SetRootMenu(menuPID, 8, v48);
  }
  SetFlagMenu(menuPID, 3, 0x40u, 0);
  SetFlagMenu(menuPID, 5, 0x40u, 0);
  SetFlagMenu(menuPID, 6, 0x40u, 0);
  SetFlagMenu(menuPID, 7, 0x40u, 0);
  SetFlagMenu(menuPID, 8, 0x40u, 0);
  if (!CheckCyousaFlag())
  {
    jmsDisableSelect(4);
LABEL_14:
    if (!CheckCyousaFlag(1))
      goto LABEL_15;
    goto LABEL_35;
  }
  goto LABEL_14;
  if (!CheckCyousaFlag(1))
  {
LABEL_15:
    goto LABEL_16;
  }
LABEL_35:
  v53 = strJmsMenu[6];
  v54 = GetLocalizeText(v53, 0);
  SetMenu(menuPID, 9, 4, v54);
LABEL_16:
  if (!CheckCyousaFlag(2))
  {
    goto LABEL_18;
  }
  v58 = strJmsMenu[7];
  v59 = GetLocalizeText(v58, 0);
  SetMenu(menuPID, 10, 4, v59);
LABEL_18:
  if (!CheckCyousaFlag(3))
  {
    goto LABEL_20;
  }
  v63 = strJmsMenu[8];
  v64 = GetLocalizeText(v63, 0);
  SetMenu(menuPID, 11, 4, v64);
LABEL_20:
  v45 = MenuFlag;
  MenuFlag[12] = jmsCyousaTable1[0];
  v72 = strJmsMenu[9];
  v45[13] = jmsCyousaTable1[1];
  v45[14] = jmsCyousaTable1[2];
  v45[15] = jmsCyousaTable1[3];
  v45[16] = jmsCyousaTable2[0];
  v45[17] = jmsCyousaTable2[1];
  v45[18] = jmsCyousaTable2[2];
  v45[19] = jmsCyousaTable2[3];
  v45[20] = jmsCyousaTable3[0];
  v45[21] = jmsCyousaTable3[1];
  v45[22] = jmsCyousaTable3[2];
  v45[23] = jmsCyousaTable3[3];
  v73 = GetLocalizeText(v72, 0);
  SetMenu(menuPID, 12, 9, v73);
  v76 = GetLocalizeText(strJmsMenu[10], 0);
  SetMenu(menuPID, 13, 9, v76);
  v79 = GetLocalizeText(strJmsMenu[11], 0);
  SetMenu(menuPID, 14, 9, v79);
  v82 = GetLocalizeText(strJmsMenu[12], 0);
  SetMenu(menuPID, 15, 9, v82);
  v85 = GetLocalizeText(strJmsMenu[13], 0);
  SetMenu(menuPID, 16, 10, v85);
  v88 = GetLocalizeText(strJmsMenu[14], 0);
  SetMenu(menuPID, 17, 10, v88);
  v91 = GetLocalizeText(strJmsMenu[15], 0);
  SetMenu(menuPID, 18, 10, v91);
  v94 = GetLocalizeText(strJmsMenu[16], 0);
  SetMenu(menuPID, 19, 10, v94);
  v97 = GetLocalizeText(strJmsMenu[17], 0);
  SetMenu(menuPID, 20, 11, v97);
  v100 = GetLocalizeText(strJmsMenu[18], 0);
  SetMenu(menuPID, 21, 11, v100);
  v103 = GetLocalizeText(strJmsMenu[19], 0);
  SetMenu(menuPID, 22, 11, v103);
  v106 = GetLocalizeText(strJmsMenu[20], 0);
  SetMenu(menuPID, 23, 11, v106);
  SetFlagMenu(menuPID, 12, 0x40u, 0);
  SetFlagMenu(menuPID, 13, 0x40u, 0);
  SetFlagMenu(menuPID, 14, 0x40u, 0);
  SetFlagMenu(menuPID, 15, 0x40u, 0);
  SetFlagMenu(menuPID, 16, 0x40u, 0);
  SetFlagMenu(menuPID, 17, 0x40u, 0);
  SetFlagMenu(menuPID, 18, 0x40u, 0);
  SetFlagMenu(menuPID, 19, 0x40u, 0);
  SetFlagMenu(menuPID, 20, 0x40u, 0);
  SetFlagMenu(menuPID, 21, 0x40u, 0);
  SetFlagMenu(menuPID, 22, 0x40u, 0);
  SetFlagMenu(menuPID, 23, 0x40u, 0);
  SetFlagMenu(menuPID, 6, 0x20u, 1);
  v121 = Allocate(itfMenuDrawFunc_t);
  _ctor(v121, 0, Method_Project_jmsMenu_DrawTitle__, 0);
  itfMenuSetDrawFunc(menuPID, 1, v121, 0);
  itfMenuSetSpriteData(menuPID, 0, 93, 27, 0, 0, -75, 16, 0, arrJmsMenuTitle);
  itfMenuSetSpriteData(menuPID, 1, 45, 88, 128, 26, 10, 4, 0, arrJmsMenuPanel);
  itfMenuSetSpriteData(menuPID, 2, 45, 88, 128, 26, 10, 4, 0, arrJmsMenuSelect);
  v122 = Allocate(itfMoverFunc_t);
  _ctor(v122, 0, Method_Project_jmsMenu_AnimFunc__, 0);
  itfMoverSetMenu(menuPID, v122);
  itfMenuSetMoveAppear(menuPID, 1);
  itfMenuSetMoveDisappear(menuPID, 1);
}

// 0x1ced6b0
static void CallProcEnd(void *wk) {
  dds3ProcessID_t *menuPID;

  menuPID = wk->menuPID;
  itfMenuProcessEnd(menuPID);
}

// 0x1ced740
static u8 CheckProcEnd(void *wk) {
  tagJMS_MENU_WORK_Fields *p_fields;
  dds3ProcessID_t *v5;
  dds3ProcessID_t *menuPID;

  menuPID = wk->menuPID;
  p_fields = &wk->fields;
  v5 = menuPID;
  if (itfMenuProcessCheck(v5))
    return 1;
  p_fields->menuPID = 0;
  return 0;
}

// 0x1ced800
static dds3ProcessFunc_t Process(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *klass;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *v8;
  s32 klass_low;
  char v11;
  dds3ProcessID_t *v13;
  dds3ProcessFunc_t v14;
  dds3ProcessID_t *v15;
  s32 monitor_high;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  switch (LOBYTE(ProcessData[2].monitor))
  {
    case 0:
      HIDWORD(ProcessData[3].klass) = -1;
      klass = ProcessData[1].klass;
      if (itfMenuProcessCheck(ProcessData[1].klass))
        goto LABEL_12;
      goto LABEL_9002;
      if (itfMenuProcessCheck(klass))
      {
LABEL_12:
        v6 = ProcessData[1].klass;
        if (itfMenuGetCtrlType(ProcessData[1].klass) == 3)
          goto LABEL_14;
        goto LABEL_9001;
        if (itfMenuGetCtrlType(v6) == 3)
        {
LABEL_14:
          HIDWORD(ProcessData[3].klass) = -1;
          v8 = ProcessData[1].klass;
          goto LABEL_44;
        }
LABEL_9001:
        v8 = ProcessData[1].klass;
        if (itfMenuGetCtrlType(v8) != 5)
          return 0;
        goto LABEL_45;
LABEL_44:
        if (itfMenuGetCtrlType(v8) != 5)
          return 0;
LABEL_45:
        monitor_high = HIDWORD(ProcessData[2].monitor);
        HIDWORD(ProcessData[3].klass) = -1;
        HIDWORD(ProcessData[2].monitor) = monitor_high | 8;
        return 0;
      }
LABEL_9002:
      v11 = 1;
      goto LABEL_41;
    case 1:
      klass_low = SLOWORD(ProcessData[3].klass);
      if (!LOWORD(ProcessData[3].klass))
      {
        HIDWORD(ProcessData[2].monitor) &= ~4u;
        goto LABEL_32;
      }
      if (klass_low < 2)
        goto LABEL_32;
      v11 = 2;
      goto LABEL_41;
    case 2:
      if (LOWORD(ProcessData[3].klass))
      {
        goto LABEL_23;
      }
      v15 = ProcessData[1].klass;
      itfMenuProcessEnd(v15);
LABEL_23:
      v13 = ProcessData[1].klass;
      if (itfMenuProcessCheck(ProcessData[1].klass))
        goto LABEL_27;
      goto LABEL_9004;
      if (itfMenuProcessCheck(v13))
      {
LABEL_27:
        LOWORD(klass_low) = ProcessData[3].klass;
LABEL_32:
        LOWORD(ProcessData[3].klass) = klass_low + 1;
        return 0;
      }
LABEL_9004:
      ProcessData[1].klass = 0;
      v11 = 3;
LABEL_41:
      LOWORD(ProcessData[3].klass) = 0;
      LOBYTE(ProcessData[2].monitor) = v11;
      return 0;
    case 3:
      v14 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v14, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v14;
    default:
      return 0;
  }
}

// 0x1cedc60
static void Release(void *wk) {
  s32 flag;
  sprHandle_t *p_hSpr;
  sprHandle_t *hSpr;

  flag = wk->flag;
  if ((flag & 2) != 0)
  {
    hSpr = wk->hSpr;
    p_hSpr = &wk->hSpr;
    if (hSpr)
    {
      wk->hSpr = 0;
      flag = wk->flag;
    }
    wk->flag = flag & 0xFFFFFFFD;
  }
}

// 0x1cedcb0
static void Shutdown(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 monitor_high;
  dds3ProcessID_t *p_monitor;
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
  if ((monitor_high & 2) == 0)
  {
    p_monitor = &ProcessData[1].monitor;
    if (!dds3ExistProcess(p_monitor))
      goto LABEL_20;
    goto LABEL_17;
  }
  if (ProcessData[2].klass)
  {
    ProcessData[2].klass = 0;
    monitor_high = HIDWORD(ProcessData[2].monitor);
  }
  HIDWORD(ProcessData[2].monitor) = monitor_high & 0xFFFFFFFD;
  p_monitor = &ProcessData[1].monitor;
  if (dds3ExistProcess(p_monitor))
  {
LABEL_17:
    dds3KillProcess(p_monitor, 0);
  }
LABEL_20:
  p_monitor = 0;
  g_mainPID = 0;
}

// 0x1cede70
static dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *klass;
  s32 Alpha;
  dds3ProcessID_t *v13;
  dds3ProcessID_t *v17;
  dds3ProcessID_t *v18;
  dds3ProcessID_t *v19;
  u32 v20;
  dds3ProcessID_t *v21;
  s32 SelectID;
  s32 v23;
  sprHandle_t *v24;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if ((BYTE4(ProcessData[2].monitor) & 4) == 0)
  {
    UIDISP(0);
    return 0;
  }
  v6 = &ProcessData[1];
  klass = ProcessData[1].klass;
  Alpha = itfMenuImgGetAlpha(klass, 0);
  if (Alpha)
  {
    if (Alpha == 255)
    {
      TITLEMODE = 2;
    }
    else
    {
      switch (TITLEMODE)
      {
        case 0:
          TITLEFADEIN = 1;
          TITLEMODE = 1;
          break;
        case 1:
          TITLEFADEIN = 0;
          break;
        case 2:
          TITLEFADEOUT = 1;
          TITLEMODE = 3;
          break;
        case 3:
          TITLEFADEOUT = 0;
          break;
        default:
          break;
      }
    }
  }
  else
  {
    TITLEMODE = 0;
  }
  if (!jmsGetUI())
  {
    goto LABEL_27;
  }
  v13 = id;
  jmsUniDrawMenu(id);
LABEL_27:
  if (!dds3ExistProcess(&ProcessData[1]))
    return 0;
  v17 = v6;
  if (!itfMenuGetFlag(v17, 8u))
    return 0;
  v18 = v6;
  if (itfMenuGetWaitType(v18))
    return 0;
  v19 = v6;
  v20 = itfMenuImgGetAlpha(v19, 1);
  if (!v20)
    return 0;
  v21 = v6;
  SelectID = itfMenuGetSelectID(v21);
  if ((u32)(SelectID - 1) < 8)
  {
    v23 = dword_3E603B8[SelectID - 1];
    goto LABEL_65;
  }
  if (SelectID < 24)
    return 0;
  v23 = 38;
LABEL_65:
  v24 = ProcessData[2].klass;
  itfDrawMiscSpriteAlpha(0, 379, 0, v20, v24, 99, 109);
  itfDrawMiscSpriteAlpha(-10, 381, 0, v20, ProcessData[2].klass, 101, 109);
  itfDrawMiscSpriteAlpha(332, 381, 0, v20, ProcessData[2].klass, 102, 109);
  itfDrawMiscSpriteAlpha(16, 385, 0, v20, ProcessData[2].klass, 100, 109);
  if (cmpProcessCheck())
    return 0;
  fclCommandHelp(v23, v20);
  return 0;
}

// 0x1cee390
void jmsUniDrawMenu(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *v5;
  Il2CppObject *v6;
  Il2CppObject *v7;
  dds3ProcessID_t *v9;
  bool v10;
  s64 v12;
  void *v13;
  s32 v14;
  bool v15;
  s64 v16;
  dds3ProcessID_t *v17;
  s32 v18;
  bool v19;
  s64 v21;
  s32 v22;
  s32 v23;
  _BOOL4 READ_FLAG;
  void *klass;
  s32 v28;
  s64 v29;
  char *v30;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  v5 = &ProcessData[1];
  v6 = dds3GetProcessData(&ProcessData[1]);
  v7 = v6;
  v9 = v5;
  if (itfMenuGetCtrlType(v9) == 1)
  {
    v10 = HIDWORD(ProcessData[4].klass) == 4;
  }
  else
  {
    v10 = 1;
  }
  selectFlag = v10;
  HIDWORD(ProcessData[4].klass) = v7[5].monitor;
  if (!LOBYTE(ProcessData[2].monitor) && (BYTE5(v7[13].klass) & 8) != 0)
  {
    UIDISP(1);
    if (SHIDWORD(v7[8].klass) >= 1)
    {
      v12 = 0;
      while (1)
      {
        v16 = *((u64 *)&v7[5].klass->_1.byval_arg.data + v12);
        if (!*(u64 *)(v16 + 24))
          goto LABEL_28;
        SetActive(jmsUIctrlSub->MenuObj, 1, 0);
        MenuListState(jmsUIctrlSub, v12, 1, 0);
        TextTextChange(jmsUIctrlSub, v12, *(char **)(*(u64 *)(v16 + 24) + 48), 0);
        v17 = v5;
        v18 = *(u32 *)(*(u64 *)(v16 + 24) + 16);
        v19 = v18 == itfMenuGetSelectID(v17);
        if (v19)
        {
          v22 = 1;
          CursorPanelState(jmsUIctrlSub, v12, 1, 0);
          if ((*(u8 *)(*(u64 *)(v16 + 24) + 28) & 3) == 0)
          {
            v21 = *(u64 *)(v16 + 24);
            if ((~*(u32 *)(v21 + 28) & 3) != 0)
              goto LABEL_24;
            goto LABEL_38;
          }
        }
        else
        {
          CursorPanelState(jmsUIctrlSub, v12, 0, 0);
          v22 = 0;
        }
        TextMode(jmsUIctrlSub, v12, v22, 0);
        v21 = *(u64 *)(v16 + 24);
        if ((~*(u32 *)(v21 + 28) & 3) != 0)
        {
LABEL_24:
          TextMode(jmsUIctrlSub, v12, 2, 0);
LABEL_25:
          v13 = jmsUIctrlSub;
          goto LABEL_26;
        }
LABEL_38:
        if (*(u8 *)(v21 + 24) != 2)
          goto LABEL_25;
        v23 = *(u32 *)(v21 + 16);
        READ_FLAG = REPORT_READ_FLAG[v23 - 12]->READ_FLAG;
        v13 = jmsUIctrlSub;
        if (!READ_FLAG)
        {
          v14 = v12;
          v15 = 1;
          goto LABEL_27;
        }
LABEL_26:
        v14 = v12;
        v15 = 0;
LABEL_27:
        MenuNewIconCtrl(v13, v14, v15, 0);
LABEL_28:
        if (++v12 >= SHIDWORD(v7[8].klass))
          goto LABEL_49;
      }
    }
    LODWORD(v12) = 0;
LABEL_49:
    if ((s32)v12 < MenuListCount(jmsUIctrlSub, 0))
    {
      while ((s32)v12 < MenuListCount(jmsUIctrlSub, 0))
      {
        MenuListState(jmsUIctrlSub, v12, 0, 0);
        LODWORD(v12) = v12 + 1;
      }
    }
  }
  if (TITLEFADEOUT)
  {
    SetTitleAnim(jmsUIctrlSub, 2, 0);
    SetBackAnim(jmsUIctrlSub, 2, 0);
  }
  if (TITLEFADEIN)
  {
    SetTitleAnim(jmsUIctrlSub, 1, 0);
    SetBackAnim(jmsUIctrlSub, 1, 0);
  }
  if (((s64)v7[13].klass & 2) != 0 && (BYTE5(v7[13].klass) & 4) != 0)
  {
    klass = v7[3].klass;
    LOBYTE(v7[15].monitor) = 0;
    v28 = *((u32 *)klass + 7);
    if ((v28 & 0x200) != 0 || LODWORD(v7[5].monitor) != 6)
    {
      v29 = *((u64 *)klass + 8);
      if (v29)
      {
        v30 = *(char **)(v29 + 48);
        LOBYTE(v7[15].monitor) = 1;
LABEL_70:
        SetTitle(jmsUIctrlSub, v30, 0);
        return;
      }
      klass = v7[3].monitor;
    }
    else if ((v28 & 0x40) == 0)
    {
      return;
    }
    v30 = *((char **)klass + 6);
    goto LABEL_70;
  }
}

// 0x1cdfee0
s32 jmsGetSelectIndex(bool root_calc) {
  s32 *ProcessData;

  if (root_calc)
  {
    if (!g_mainPID)
      return 6;
  }
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return ProcessData[13];
  return ProcessData[13];
}

// 0x1cdedd0
void jmsStart(void) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *klass;
  s32 monitor_high;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  klass = ProcessData[1].klass;
  itfMenuStart(ProcessData[1].klass);
  monitor_high = HIDWORD(ProcessData[2].monitor);
  HIDWORD(ProcessData[3].klass) = 0;
  if ((monitor_high & 0x20) != 0)
    return;
  HIDWORD(ProcessData[2].monitor) = monitor_high | 8;
  return;
}

// 0x1cdef50
void jmsSetFocus(bool a_bFocus) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *klass;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  klass = ProcessData[1].klass;
  itfMenuSetFlag(klass, 8, a_bFocus);
  if (a_bFocus)
  {
    if (op_Inequality(jmsUIctrlSub, 0, 0))
    {
      SetTitleAnim(jmsUIctrlSub, 1, 0);
      SetBackAnim(jmsUIctrlSub, 1, 0);
    }
  }
  else
  {
    op_Inequality(jmsUIctrlSub, 0, 0);
  }
}

// 0x1ce4550
void jmsCallDrawBack(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  HIDWORD(ProcessData[2].monitor) |= 0x10u;
}

// 0x1ce28c0
void ProcessStart(void) {
  void *v1;
  dds3ProcessFunc_t v2;
  shutdownfuncDelegate v3;
  dds3ProcessID_t *started;
  dds3ProcessFunc_t v6;
  dds3ProcessID_t *v7;
  dds3ProcessID_t *v8;
  sprHandle_t *SpriteHandle;
  s32 flag;

  v1 = Allocate(tagJMS_MENU_WORK);
  _ctor(v1, 0);
  v2 = Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_jmsMenu_Process__, 0);
  v3 = Allocate(shutdownfuncDelegate);
  _ctor(v3, 0, Method_Project_jmsMenu_Shutdown__, 0);
  started = dds3StartProcess("jms_menu_main", 1023, 0, 0, v2, v3, v1);
  g_mainPID = started;
  v6 = Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_jmsMenu_DrawProcess__, 0);
  v7 = dds3StartProcess("jms_menu_draw", 11029, 0, 0, v6, 0, v1);
  v1->drawPID = v7;
  v8 = itfMenuProcessStart();
  v1->menuPID = v8;
  SpriteHandle = jmsGetSpriteHandle();
  v1->hSpr = SpriteHandle;
  itfMenuLinkSprite(v1->menuPID, v1->hSpr);
  SetCommand(v1);
  ButtonLineHelpTextSet("SHP_CMDHELP_0025", 0, 1, 0xA09DC380, 1);
  flag = v1->flag;
  v1->index = 0;
  v1->flag = flag | 4;
}

// 0x1ce2700
void ProcessEnd(void) {
  Il2CppObject *ProcessData;
  s32 monitor_high;

  if (!g_mainPID)
    return;
  selectFlag = 0;
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
    HIDWORD(ProcessData[2].monitor) = monitor_high | 1;
    LOBYTE(ProcessData[2].monitor) = 1;
  }
}

// 0x1cee9a0
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

// 0x1cdfd30
void MenuProcessStop(void) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *klass;

  if (!g_mainPID)
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  klass = ProcessData[1].klass;
  itfMenuSetFlag(klass, 256, 1);
}

// 0x1ce82d0
void MenuProcessRestart(void) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *klass;

  if (!g_mainPID)
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  klass = ProcessData[1].klass;
  itfMenuSetFlag(klass, 256, 0);
}

// 0x1cdf170
void jmsDisableSelect(s32 MenuID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *klass;

  if (!g_mainPID)
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  klass = ProcessData[1].klass;
  itfMenuSetFlagMenu(klass, MenuID, 2, 0);
}

// 0x1ceeb20
void jmsAddTalkTarget(s32 No, char *pStr) {
  dds3ProcessID_t *v5;
  Il2CppObject *ProcessData;
  dds3ProcessID_t *klass;
  itfMenuFunc_t v11;

  v5 = Allocate(dds3ProcessID_t);
  _ctor(v5, 0);
  if (!g_mainPID)
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  klass = ProcessData[1].klass;
  v11 = Allocate(itfMenuFunc_t);
  _ctor(v11, 0, Method_Project_jmsMenu_CallFunc__, 0);
  itfMenuSetMenu(klass, No + 24, 1, pStr, v11, "");
}

// 0x1cea390
s32 jmsCheckCyousaFileEnable(s32 CyousaFileIndex) {
  s32 v4;

  v4 = MenuFlag[CyousaFileIndex + 12];
  if (v4)
    return evtBitCheck(v4);
  return 1;
}

// 0x1ce0020
s32 jmsCheckMovePrev(void) {
  dds3ProcessID_t *ProcessData;
  s64 naturalAligment;
  dds3ProcessID_t *v5;
  dds3ProcessID_t *v7;

  if (!g_mainPID)
    return 0;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (ProcessData)
    LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((tagJMS_MENU_WORK_c **)(ProcessData)[1].next + naturalAligment - 1) != tagJMS_MENU_WORK;
  v5 = ProcessData[2];
  if (!v5)
    return 0;
  if (itfMenuGetCtrlType(ProcessData[2]) == 3)
    return 1;
  v7 = ProcessData[2];
  return itfMenuGetCtrlType(v7) == 5;
}

// 0x1ce1490
s32 jmsGetCursorPosID(void) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *klass;

  if (!g_mainPID)
    return -1;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  klass = ProcessData[1].klass;
  return itfMenuGetSelectID(klass);
}
