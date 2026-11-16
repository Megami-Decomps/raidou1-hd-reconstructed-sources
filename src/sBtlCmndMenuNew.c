#include "types.h"
#include "DEVIL_STATUS_TYPE.h"
#include "SKLID.h"
#include "cfg.h"
#include "cmpkuda.h"
#include "cmpstatus.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3kernelcore.h"
#include "itf.h"
#include "itfMenuDrawFunc_t.h"
#include "itfMenuFunc_t.h"
#include "kernel.h"
#include "localize.h"
#include "raijindlc.h"
#include "sbtl.h"
#include "sbtlactai.h"
#include "sbtlcalc.h"
#include "sbtlcamera.h"
#include "sbtlcmndmenunew.h"
#include "sbtlcommand.h"
#include "sbtldraw.h"
#include "sbtlmain.h"
#include "sbtlmenu.h"
#include "sbtlpanel.h"
#include "sbtlplayer.h"
#include "sbtlscene.h"
#include "sbtlskill.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sbtlweapon.h"
#include "sdat.h"

#define D_DVL_NAME_X 300
#define D_DVL_NAME_X2 365
#define D_DVL_NAME_X3 365
#define D_DVL_NAME_Y 90
#define D_DVL_NAME_Y2 110
#define D_DVL_NAME_STRETCH 96

typedef enum {
    E_CMNDMENU_STEP_INIT = 0,
    E_CMNDMENU_STEP_WAIT = 1,
    E_CMNDMENU_STEP_SKL = 2,
    E_CMNDMENU_STEP_TGT = 3,
    E_CMNDMENU_STEP_STOCK = 4,
    E_CMNDMENU_STEP_ENEMY = 5,
    E_CMNDMENU_STEP_END = 6,
} E_CMNDMENU_STEP;

typedef enum {
    SBTLCMNDMENUNEW_HELP_SKL_X = 350,
    SBTLCMNDMENUNEW_HELP_SKL_Y = 335,
} SBTLCMNDMENUNEW_HELP_SKL;

typedef enum {
    SBTLCMNDMENUNEW_SE_NAKAMA = 65567,
    SBTLCMNDMENUNEW_SE_REPEATON = 12,
    SBTLCMNDMENUNEW_SE_REPEATOFF = 13,
} SBTLCMNDMENUNEW_SE;

typedef enum {
    WAITFRAME = 0,
    TURNFRAME = 60,
    TOTALFRAME = 60,
} SBTLCMNDMENUNEW_REPEATICON;

typedef enum {
    SBTLCMNDMENUNEW_TYPE_NORMAL = 0,
    SBTLCMNDMENUNEW_TYPE_START = 1,
} SBTLCMNDMENUNEW_TYPE;

typedef enum {
    SBTLCMNDMENUNEW_USETYPE_USE = 0,
    SBTLCMNDMENUNEW_USETYPE_MAG = 1,
    SBTLCMNDMENUNEW_USETYPE_KTN = 2,
    SBTLCMNDMENUNEW_USETYPE_BST = 3,
    SBTLCMNDMENUNEW_USETYPE_TGT = 4,
    SBTLCMNDMENUNEW_USETYPE_CMB = 5,
} SBTLCMNDMENUNEW_USETYPE;

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct S_CmndMenuNew S_CmndMenuNew;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

struct S_CmndMenuNew {
    dds3ProcessID_t *drawPID;
    dds3ProcessID_t *sklPID;
    dds3ProcessID_t *tgtPID;
    dds3ProcessID_t *stockPID;
    u8 tab;
    u8 mode;
    E_CMNDMENU_STEP step;
    bool bTgtListIsStock;
    bool bSideMove;
    s32 tabStock;
    s32 RepeatIconTimer;
    f32 RepeatIconAngle;
    bool bDecide;
    bool bCallStopBattle;
    SBTLCMNDMENUNEW_TYPE type;
    s32 cntLoop;
    s32 maxLoop;
    s32 index[2];
    s32 sklNo[2];
    s32 tgtNo[2];
    DEVIL_STATUS_TYPE skilltype;
};

dds3ProcessID_t *g_mainPID;
char *g_strRepeat;

static SBTLCMNDMENUNEW_USETYPE ChkUseSklEx(SBTLUNIT_WORK *pBtlUnit, SKLID sklId, bool bCmbOut);
static void SetSklMenu(s32 a_selectNo, bool a_bAutoDecide);
static bool Start_Local(s32 mode);
static void DrawRepeatIconEx(s32 a_x, s32 a_y, s32 a_z, f32 a_angle, f32 a_alphaRate, DDS3_OT a_otNo, SBTLUNIT_WORK *a_pBtlUnit, SKLID a_sklId);
static S_CmndMenuNew *GetProcessData(void);
static void ResetBtlParam(void);
static bool SkillChkUseUnit(SBTLUNIT_WORK *a_pTgtBtlUnit, sdatUnitWork_t *a_pTgtUnit, sdatUnitWork_t *a_pUseUnit, SKLID a_sklId);
static s32 FuncDecideTgt(void);
static s32 FuncDecideStock(void);
static void DrawFuncTgt(s32 a_id, s32 x, s32 y, s32 z, u32 fontColor, u8 alphaRate);
static void DrawFuncStock(s32 a_id, s32 x, s32 y, s32 z, u32 fontColor, u8 alphaRate);
static void DrawFuncTgtEnemy(s32 a_id, s32 x, s32 y, s32 z, u32 fontColor, u8 alphaRate);
static void SetTgtMenu(s32 a_selectNo);
static void SetStockMenu(s32 a_selectNo);
static void SetTgtEnemy(s32 a_selectNo, SBTLUNIT_WORK *pNakama);
static void TgtEnemySel(void);
static s32 FuncDecideEnemyTgt(void);
static s32 FuncDecideSkl(void);
static void DrawFuncSkl(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate);
static SBTLCMNDMENUNEW_USETYPE ChkUseSkl(SBTLUNIT_WORK *pBtlUnit, SKLID sklId);
static s32 GetEnebleUseSkillNum(s32 a_nakamaNo, bool a_bCmbOut);
static s32 MakeSkillList(dds3ProcessID_t *a_sklPID, itfMenuFunc_t a_decideFunc, itfMenuDrawFunc_t a_drawFunc, s32 a_nakamaNo, bool a_bCmbOut);
static s32 GetTabLimit(s32 *a_pmin, s32 *a_pmax);
static dds3ProcessFunc_t Proc(dds3ProcessID_t *PID);
static void Shutdown(dds3ProcessID_t *PID);
static dds3ProcessFunc_t DrawProc(dds3ProcessID_t *PID);

// 0x1f09d00
static SBTLCMNDMENUNEW_USETYPE ChkUseSklEx(SBTLUNIT_WORK *pBtlUnit, SKLID sklId, bool bCmbOut) {
  s32 v7;
  SBTLSKILLP_TBL *Skilltbl;

  v7 = ChkUseSkl(pBtlUnit, sklId);
  if ((v7 | 4) == 4)
  {
    Skilltbl = sBtlGetSkilltbl(sklId);
    if (bCmbOut && (Skilltbl->type & 0x1000) != 0)
      return 5;
  }
  return v7;
}

// 0x1f0a600
static void SetSklMenu(s32 a_selectNo, bool a_bAutoDecide) {
  Il2CppObject *ProcessData;
  s32 monitor_high;
  dds3ProcessID_t *monitor;
  itfMenuFunc_t v11;
  itfMenuDrawFunc_t v12;
  itfMenuFunc_t v13;
  itfMenuDrawFunc_t v14;
  s32 v16;
  void *Instance;
  dds3ProcessID_t *v18;
  bool v19;
  dds3ProcessID_t *v20;
  dds3ProcessID_t *v21;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  monitor_high = HIDWORD(ProcessData[4].monitor);
  monitor = ProcessData[1].monitor;
  v11 = Allocate(itfMenuFunc_t);
  _ctor(v11, 0, Method_Project_sBtlCmndMenuNew_FuncDecideSkl__, 0);
  v12 = Allocate(itfMenuDrawFunc_t);
  _ctor(v12, 0, Method_Project_sBtlCmndMenuNew_DrawFuncSkl__, 0);
  v16 = BYTE1(ProcessData[3].klass);
  MakeSkillList(monitor, v13, v14, v16, monitor_high == 1);
  Instance = get_Instance(0);
  OpenSkillMenu(Instance, ProcessData[1].monitor, monitor_high == 1, BYTE1(ProcessData[3].klass), 0);
  v18 = ProcessData[1].monitor;
  v19 = a_bAutoDecide;
  itfMenuSetFlag(v18, 0x4000, v19);
  itfMenuSetFlag(ProcessData[1].monitor, 0x10000, v19);
  if ((a_selectNo & 0x80000000) == 0)
  {
    v20 = ProcessData[1].monitor;
    itfMenuSetInitSelectID(v20, a_selectNo);
  }
  v21 = ProcessData[1].monitor;
  itfMenuStart(v21);
  MenuCnt = 0;
  ProcessData[4].klass = 0;
  HIDWORD(ProcessData[3].klass) = 2;
}

// 0x1f0ad80
static bool Start_Local(s32 mode) {
  Il2CppObject *ProcessData;
  bool IsStart;
  s32 v10;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  IsStart = sBtlIsStart(mode);
  if (IsStart)
  {
    if (cfgGetConfigGAME(3, 0))
    {
      v10 = sBtlGetNakama(mode)->para->prevSkill - 1;
      BYTE1(ProcessData[3].klass) = mode;
LABEL_16:
      SetSklMenu(v10, 0);
      return IsStart;
    }
    v10 = -1;
    BYTE1(ProcessData[3].klass) = mode;
    goto LABEL_16;
  }
  return IsStart;
}

// 0x1f0b130
s32 sBtlGetSklRepeat(bool *a_pbRepeat, SBTLUNIT_WORK *a_pBtlUnit, SKLID a_sklId) {
  s32 v4;
  sdatUnitWork_t *para;
  s64 v6;
  SKLID *haveskill;

  v4 = -1;
  if (!a_pBtlUnit || a_sklId < 0)
    return v4;
  para = a_pBtlUnit->para;
  if (a_sklId == 149)
  {
    v6 = 0;
LABEL_35:
    v4 = 0;
    *a_pbRepeat = para->autoskill[v6] == 1;
    return v4;
  }
  haveskill = para->haveskill;
  if (haveskill[2] == a_sklId)
  {
    v6 = 2;
    goto LABEL_35;
  }
  if (haveskill[3] == a_sklId)
  {
    v6 = 3;
    goto LABEL_35;
  }
  if (haveskill[4] == a_sklId)
  {
    v6 = 4;
    goto LABEL_35;
  }
  if (haveskill[5] == a_sklId)
  {
    v6 = 5;
    goto LABEL_35;
  }
  if (haveskill[6] == a_sklId)
  {
    v6 = 6;
    goto LABEL_35;
  }
  if (haveskill[7] == a_sklId)
  {
    v6 = 7;
    goto LABEL_35;
  }
  if (haveskill[8] == a_sklId)
  {
    v6 = 8;
    goto LABEL_35;
  }
  if (haveskill[9] == a_sklId)
  {
    v6 = 9;
    goto LABEL_35;
  }
  if (haveskill[10] == a_sklId)
  {
    v6 = 10;
    goto LABEL_35;
  }
  if (haveskill[11] == a_sklId)
  {
    v6 = 11;
    goto LABEL_35;
  }
  if (haveskill[12] == a_sklId)
  {
    v6 = 12;
    goto LABEL_35;
  }
  if (haveskill[13] == a_sklId)
  {
    v6 = 13;
    goto LABEL_35;
  }
  if (haveskill[14] == a_sklId)
  {
    v6 = 14;
    goto LABEL_35;
  }
  if (haveskill[15] == a_sklId)
  {
    v6 = 15;
    goto LABEL_35;
  }
  if (haveskill[16] == a_sklId)
  {
    v6 = 16;
    goto LABEL_35;
  }
  return -2;
}

// 0x1f0b2b0
s32 sBtlSetSklRepeat(bool a_bRepeat, SBTLUNIT_WORK *a_pBtlUnit, SKLID a_sklId) {
  s32 result;
  sdatUnitWork_t *para;
  s8 *autoskill;
  SKLID *haveskill;
  s64 v11;
  s8 *v12;

  result = -1;
  if (a_pBtlUnit && (a_sklId & 0x80000000) == 0)
  {
    a_pBtlUnit->para->autoskill[0] = 0;
    a_pBtlUnit->para->autoskill[1] = 0;
    a_pBtlUnit->para->autoskill[2] = 0;
    a_pBtlUnit->para->autoskill[3] = 0;
    a_pBtlUnit->para->autoskill[4] = 0;
    a_pBtlUnit->para->autoskill[5] = 0;
    a_pBtlUnit->para->autoskill[6] = 0;
    a_pBtlUnit->para->autoskill[7] = 0;
    a_pBtlUnit->para->autoskill[8] = 0;
    a_pBtlUnit->para->autoskill[9] = 0;
    a_pBtlUnit->para->autoskill[10] = 0;
    a_pBtlUnit->para->autoskill[11] = 0;
    a_pBtlUnit->para->autoskill[12] = 0;
    a_pBtlUnit->para->autoskill[13] = 0;
    a_pBtlUnit->para->autoskill[14] = 0;
    a_pBtlUnit->para->autoskill[15] = 0;
    a_pBtlUnit->para->autoskill[16] = 0;
    para = a_pBtlUnit->para;
    if (a_sklId == 149)
    {
      autoskill = para->autoskill;
      autoskill[0] = ToSByte_54962192(a_bRepeat, 0);
      a_sklId = 149;
    }
    else
    {
      haveskill = para->haveskill;
      if (haveskill[2] == a_sklId)
      {
        v11 = 2;
      }
      else if (haveskill[3] == a_sklId)
      {
        v11 = 3;
      }
      else if (haveskill[4] == a_sklId)
      {
        v11 = 4;
      }
      else if (haveskill[5] == a_sklId)
      {
        v11 = 5;
      }
      else if (haveskill[6] == a_sklId)
      {
        v11 = 6;
      }
      else if (haveskill[7] == a_sklId)
      {
        v11 = 7;
      }
      else if (haveskill[8] == a_sklId)
      {
        v11 = 8;
      }
      else if (haveskill[9] == a_sklId)
      {
        v11 = 9;
      }
      else if (haveskill[10] == a_sklId)
      {
        v11 = 10;
      }
      else if (haveskill[11] == a_sklId)
      {
        v11 = 11;
      }
      else if (haveskill[12] == a_sklId)
      {
        v11 = 12;
      }
      else if (haveskill[13] == a_sklId)
      {
        v11 = 13;
      }
      else if (haveskill[14] == a_sklId)
      {
        v11 = 14;
      }
      else if (haveskill[15] == a_sklId)
      {
        v11 = 15;
      }
      else
      {
        if (haveskill[16] != a_sklId)
          return -2;
        v11 = 16;
      }
      v12 = para->autoskill;
      v12[v11] = ToSByte_54962192(a_bRepeat, 0);
    }
    result = 0;
    a_pBtlUnit->aiwk->RepeatOdrSkl = a_sklId;
  }
  return result;
}

// 0x1f0b5a0
static void DrawRepeatIconEx(s32 a_x, s32 a_y, s32 a_z, f32 a_angle, f32 a_alphaRate, DDS3_OT a_otNo, SBTLUNIT_WORK *a_pBtlUnit, SKLID a_sklId) {
  SBTLSKILLP_TBL *Skilltbl;
  u32 flg;

  Skilltbl = sBtlGetSkilltbl(a_sklId);
  if (!Skilltbl)
    return;
  if ((Skilltbl->type & 0x1000) == 0 && (Skilltbl->area & 0x100) == 0)
  {
    flg = Skilltbl->flg;
  }
}

// 0x1f0b740
static S_CmndMenuNew *GetProcessData(void) {
  bool exist;
  S_CmndMenuNew *result;

  exist = dds3ExistProcess(g_mainPID);
  result = 0;
  if (!exist)
    return result;
  result = (S_CmndMenuNew *)dds3GetProcessData(g_mainPID);
  if (!result)
    return result;
  return result;
}

// 0x1f0b890
void sBtlEnd(void) {
  Il2CppObject *ProcessData;
  void *Instance;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  HIDWORD(ProcessData[3].klass) = 1;
  if (shortcutFlag)
  {
    shortcutFlag = 0;
    MenuShortCutFarst = 0;
  }
  if (BYTE1(ProcessData[4].monitor))
  {
    BYTE1(ProcessData[4].monitor) = 0;
    if (wk->encountno == 43)
    {
      sBtlCancelMenuPara();
      if (HIDWORD(ProcessData[4].monitor) == 1)
        return;
      goto LABEL_26;
    }
    RestartBattle();
    sBtlCancelMenuPara();
    if (HIDWORD(ProcessData[4].monitor) != 1)
    {
LABEL_26:
      sBtlMenuClose();
      Instance = get_Instance(0);
      BattleMenuClose(Instance, 0, 0);
    }
  }
}

// 0x1f0bb20
static void ResetBtlParam(void) {
  SBTLUNIT_WORK *PChara;

  wk->status2 &= ~2u;
  RestartBattle();
  sBtlRestart_Scene();
  sBtlActiveAction();
  *(u32 *)wk->gstat = 0;
  PChara = sBtlGetPChara();
  PChara->vstatus &= ~0x8000000u;
  sBtlResetNSTOP();
  sBtlResetMidashiAnim(0);
  sBtlResetSelectAnim(0);
  wk->s_time = 0;
  wk->menutype = 0;
  *(u32 *)wk->sgstat = 0;
  sBtlResetColor(0x80808080);
}

// 0x1f0bca0
static bool SkillChkUseUnit(SBTLUNIT_WORK *a_pTgtBtlUnit, sdatUnitWork_t *a_pTgtUnit, sdatUnitWork_t *a_pUseUnit, SKLID a_sklId) {
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v10;

  if (a_pTgtUnit)
  {
    Skilltbl = sBtlGetSkilltbl(a_sklId);
    if (!Skilltbl)
      return (char)Skilltbl;
    v10 = Skilltbl;
    if (!a_pTgtBtlUnit)
    {
      if ((Skilltbl->useflg & 2) == 0)
      {
        LOBYTE(Skilltbl) = 1;
        return (char)Skilltbl;
      }
      goto LABEL_15;
    }
    if (CheckLiveTarget(a_pTgtBtlUnit))
      goto LABEL_8;
  }
  LOBYTE(Skilltbl) = 0;
  return (char)Skilltbl;
LABEL_8:
  if ((v10->useflg & 2) == 0)
  {
    LOBYTE(Skilltbl) = sBtlCheckEnableUseSkill(a_pTgtBtlUnit, a_sklId) > 0;
    return (char)Skilltbl;
  }
LABEL_15:
  LOBYTE(Skilltbl) = cmpChkEnableUseSkill(a_pUseUnit, a_pTgtUnit, a_sklId);
  return (char)Skilltbl;
}

// 0x1f0b6a0
bool sBtlChkRepeat(SKLID a_sklId) {
  SBTLSKILLP_TBL *Skilltbl;
  u32 flg;

  Skilltbl = sBtlGetSkilltbl(a_sklId);
  if (Skilltbl)
  {
    if ((Skilltbl->type & 0x1000) != 0)
    {
      LOBYTE(Skilltbl) = 0;
    }
    else if ((Skilltbl->area & 0x100) != 0 || (flg = Skilltbl->flg, (flg & 0x20) != 0))
    {
      LOBYTE(Skilltbl) = 0;
    }
    else
    {
      LOBYTE(Skilltbl) = 0;
      if (a_sklId != 134 && a_sklId != 1124 && a_sklId != 1169)
        LOBYTE(Skilltbl) = (flg & 0x200) == 0;
    }
  }
  return (char)Skilltbl;
}

// 0x1f0be00
static s32 FuncDecideTgt(void) {
  Il2CppObject *ProcessData;
  u32 *monitor;
  s64 v6;
  dds3ProcessID_t *klass;
  SBTLUNIT_WORK *Nakama;
  s32 SelectID;
  s32 v11;
  SBTLSKILLP_TBL *Skilltbl;
  s32 v13;
  s32 area;
  s32 monitor_high;
  s32 v18;
  dds3ProcessID_t *v19;
  s32 v21;
  sdatUnitWork_t *StockUnitData;
  s64 v24;
  s32 ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  sdatUnitWork_t *para;
  s64 v32;
  SKLID *haveskill;
  SBTLAI_WORK *aiwk;
  s32 rsvSkl;
  s32 rsvTgt;
  SBTLAI_WORK *v38;
  s32 ConfigGAME;
  s32 v43;
  s64 v45;
  s32 v46;
  sdatUnitWork_t *v47;
  s32 klass_high;
  s32 v50;
  u32 mode;
  void *Instance;
  void *v59;
  void *v60;
  SBTLUNIT_WORK *v64;
  HpCallCtrl *hpCallCtrl;
  SBTLUNIT_WORK *v66;
  HpCallCtrl *v67;
  void *v71;
  void *v72;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  monitor = ProcessData[6].monitor;
  v6 = BYTE1(ProcessData[3].klass);
  klass = ProcessData[2].klass;
  monitor[v6 + 8] = itfMenuGetSelectID(klass);
  Nakama = sBtlGetNakama(BYTE1(ProcessData[3].klass));
  SelectID = itfMenuGetSelectID(ProcessData[1].monitor);
  v11 = wk->stock_useskill[SelectID];
  Skilltbl = sBtlGetSkilltbl(v11);
  v13 = itfMenuGetSelectID(ProcessData[2].klass);
  area = (s16)Skilltbl->area;
  if (v13 == 99 && (area & 0x80000000) == 0)
  {
    monitor_high = HIDWORD(ProcessData[3].monitor);
    if (monitor_high + 1 < 2)
      v18 = monitor_high + 1;
    else
      v18 = 0;
    HIDWORD(ProcessData[3].monitor) = v18;
    SetStockMenu(-1);
    sBtlPlaySE(0x1001Fu);
    return 1;
  }
  if ((area & 4) != 0)
  {
    ListID = 0;
    goto LABEL_48;
  }
  v19 = ProcessData[2].klass;
  if (!LOBYTE(ProcessData[3].monitor))
  {
    ListID = itfMenuGetSelectID(v19);
LABEL_48:
    v21 = -1;
    goto LABEL_50;
  }
  v21 = itfMenuGetSelectID(v19) - 1;
  StockUnitData = sBtlGetStockUnitData(v21);
  v24 = 0;
  ListID = -1;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v24 >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[v24]->pUnit;
    if (pUnit)
    {
      if ((pUnit->side & 1) != 0 && pUnit->para->devilid == StockUnitData->devilid)
      {
        ListID = pUnit->ListID;
        v21 = -1;
        goto LABEL_50;
      }
    }
    ++v24;
  }
LABEL_50:
  sBtlShugouKaijyo();
  if (HIDWORD(ProcessData[4].monitor) == 1)
  {
    goto LABEL_52;
  }
  ResetBtlParam();
LABEL_52:
  if (!Nakama)
    goto LABEL_95;
  if (v11 < 0)
    goto LABEL_95;
  para = Nakama->para;
  if (v11 == 149)
  {
    v32 = 0;
  }
  else
  {
    haveskill = para->haveskill;
    if (haveskill[2] == v11)
    {
      v32 = 2;
    }
    else if (haveskill[3] == v11)
    {
      v32 = 3;
    }
    else if (haveskill[4] == v11)
    {
      v32 = 4;
    }
    else if (haveskill[5] == v11)
    {
      v32 = 5;
    }
    else if (haveskill[6] == v11)
    {
      v32 = 6;
    }
    else if (haveskill[7] == v11)
    {
      v32 = 7;
    }
    else if (haveskill[8] == v11)
    {
      v32 = 8;
    }
    else if (haveskill[9] == v11)
    {
      v32 = 9;
    }
    else if (haveskill[10] == v11)
    {
      v32 = 10;
    }
    else if (haveskill[11] == v11)
    {
      v32 = 11;
    }
    else if (haveskill[12] == v11)
    {
      v32 = 12;
    }
    else if (haveskill[13] == v11)
    {
      v32 = 13;
    }
    else if (haveskill[14] == v11)
    {
      v32 = 14;
    }
    else if (haveskill[15] == v11)
    {
      v32 = 15;
    }
    else
    {
      if (haveskill[16] != v11)
        goto LABEL_95;
      v32 = 16;
    }
  }
  if (para->autoskill[v32] == 1)
  {
    aiwk = Nakama->aiwk;
    aiwk->dfltOdrSkl = v11;
    aiwk->dfltOdrTgt = ListID;
    rsvSkl = aiwk->rsvSkl;
    rsvTgt = aiwk->rsvTgt;
    aiwk->dfltOdrStk = v21;
    aiwk->rsvSkl = v11;
    aiwk->rsvTgt = ListID;
    aiwk->rsvStk = v21;
    aiwk->RepeatOdrSkl = v11;
    aiwk->RepeatOdrTgt = ListID;
    aiwk->RepeatOdrStk = v21;
  }
  else
  {
LABEL_95:
    v38 = Nakama->aiwk;
    rsvSkl = v38->rsvSkl;
    rsvTgt = v38->rsvTgt;
    v38->rsvSkl = v11;
    v38->rsvTgt = ListID;
    v38->rsvStk = v21;
  }
  ConfigGAME = cfgGetConfigGAME(3, 0);
  if (ConfigGAME)
  {
    v43 = SelectID + 1;
    v45 = BYTE1(ProcessData[3].klass);
    GBWK->sbtl_prevSkill[v45] = SelectID + 1;
    v46 = ListID;
  }
  else
  {
    v46 = 0;
    v43 = 0;
    v45 = BYTE1(ProcessData[3].klass);
    GBWK->sbtl_prevSkill[v45] = 0;
  }
  GBWK->sbtl_prevTarget[v45] = v46;
  v47 = Nakama->para;
  v47->prevSkill = v43;
  v47->prevTarget = v46;
  if ((rsvTgt != ListID || rsvSkl != v11) && Nakama->hpCallCtrl)
  {
    LODWORD(v45) = BYTE1(ProcessData[3].klass);
    wk->closedOkDisp[(u32)v45] = 1;
  }
  if (HIDWORD(ProcessData[4].monitor) != 1)
  {
    if ((Skilltbl->type & 0x1000) == 0)
    {
      mode = Nakama->actaiwk->mode;
      if (mode <= 0x10 && ((1 << mode) & 0x1D9FF) != 0)
      {
        sBtlResetAAI(Nakama);
        sBtlSetMotion(Nakama, 0, 4, 0, 0);
      }
    }
    Nakama->actcounter = Nakama->actcounter_max;
    Nakama->aiwk->usedSkl = 0;
    LOBYTE(ProcessData[4].monitor) = 1;
    sBtlEnd();
    sBtlMenuClose();
    Instance = get_Instance(0);
    BattleMenuClose(Instance, 0, 0);
    EndAnimInfo(instance, 0);
    v59 = get_Instance(0);
    MenuClose(v59->devil_info2, 0);
    v60 = get_Instance(0);
    CharIconCtr(v60, 0, 0);
    infotype = 0;
    devilInfo = 0;
    if (wk->closedOkDisp[BYTE1(ProcessData[3].klass)])
    {
      if (Nakama->hpCallCtrl)
      {
        OkSign(Nakama->hpCallCtrl, 0);
      }
      wk->closedOkDisp[BYTE1(ProcessData[3].klass)] = 0;
    }
    return 1;
  }
  klass_high = HIDWORD(ProcessData[5].klass);
  v50 = LODWORD(ProcessData[5].klass) + 1;
  LODWORD(ProcessData[5].klass) = v50;
  if (v50 >= klass_high)
  {
    LOBYTE(ProcessData[4].monitor) = 1;
    *(u16 *)wk->closedOkDisp = 0;
    v64 = sBtlGetNakama(0);
    if (v64)
    {
      hpCallCtrl = v64->hpCallCtrl;
      if (hpCallCtrl)
        OkSign(hpCallCtrl, 0);
    }
    v66 = sBtlGetNakama(1);
    if (v66)
    {
      v67 = v66->hpCallCtrl;
      if (v67)
        OkSign(v67, 0);
    }
    sBtlEnd();
    return 1;
  }
  BYTE1(ProcessData[3].klass) = *((u32 *)ProcessData[5].monitor + v50 + 8);
  SetSklMenu(-1, 0);
  if (infotype == 3)
  {
    EndAnimInfo(instance, 0);
    goto LABEL_167;
  }
  v71 = get_Instance(0);
  MenuClose(v71->devil_info2, 0);
  v72 = get_Instance(0);
  CharIconCtr(v72, 0, 0);
LABEL_167:
  infotype = 0;
  devilInfo = 0;
  return 1;
}

// 0x1f0d440
static s32 FuncDecideStock(void) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *monitor;
  s32 SelectID;
  u32 *v9;
  s64 v10;
  dds3ProcessID_t *v11;
  SBTLUNIT_WORK *Nakama;
  s32 v13;
  s32 v15;
  dds3ProcessID_t *v16;
  s32 v18;
  s32 v20;
  s32 v21;
  sdatUnitWork_t *v22;
  sdatUnitWork_t *StockUnitData;
  sdatUnitWork_t *para;
  s64 v29;
  SKLID *haveskill;
  SBTLAI_WORK *v31;
  s32 rsvTgt;
  s32 rsvSkl;
  SBTLAI_WORK *aiwk;
  s32 ConfigGAME;
  s32 v40;
  s64 v42;
  s32 v43;
  sdatUnitWork_t *v44;
  s32 klass_high;
  s32 v47;
  u32 mode;
  void *Instance;
  void *v56;
  void *v57;
  SBTLUNIT_WORK *v61;
  HpCallCtrl *hpCallCtrl;
  SBTLUNIT_WORK *v63;
  HpCallCtrl *v64;
  void *v68;
  void *v69;
  SBTLSKILLP_TBL *Skilltbl;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  monitor = ProcessData[2].monitor;
  SelectID = itfMenuGetSelectID(monitor);
  if (SelectID == wk->stock_num + 1)
  {
    HIDWORD(ProcessData[3].monitor) = 1;
    SetStockMenu(-1);
    sBtlPlaySE(0x1001Fu);
    return 1;
  }
  v9 = ProcessData[6].monitor;
  v10 = BYTE1(ProcessData[3].klass);
  v11 = ProcessData[2].monitor;
  v9[v10 + 8] = itfMenuGetSelectID(v11);
  Nakama = sBtlGetNakama(BYTE1(ProcessData[3].klass));
  v13 = itfMenuGetSelectID(ProcessData[1].monitor);
  v15 = wk->stock_useskill[v13];
  Skilltbl = sBtlGetSkilltbl(v15);
  if ((Skilltbl->area & 4) != 0)
  {
    v21 = 0;
  }
  else
  {
    v16 = ProcessData[2].monitor;
    if (LOBYTE(ProcessData[3].monitor))
    {
      v18 = itfMenuGetSelectID(v16);
      v20 = 0;
      v21 = -1;
      v22 = stockUnitTgt[v18];
      while (1)
      {
        if (v20 >= wk->stock_num)
          break;
        StockUnitData = sBtlGetStockUnitData(v20);
        if (StockUnitData && v22 == StockUnitData)
          goto LABEL_44;
        ++v20;
      }
      v20 = v18;
LABEL_45:
      sBtlShugouKaijyo();
      if (HIDWORD(ProcessData[4].monitor) != 1)
        goto LABEL_51;
      goto LABEL_47;
    }
    v21 = itfMenuGetSelectID(v16);
  }
  v20 = -1;
LABEL_44:
  goto LABEL_45;
LABEL_51:
  ResetBtlParam();
  if (!Nakama)
    goto LABEL_92;
  goto LABEL_56;
LABEL_47:
  if (!Nakama)
    goto LABEL_92;
LABEL_56:
  if (v15 < 0)
    goto LABEL_92;
  para = Nakama->para;
  if (v15 == 149)
  {
    v29 = 0;
  }
  else
  {
    haveskill = para->haveskill;
    if (haveskill[2] == v15)
    {
      v29 = 2;
    }
    else if (haveskill[3] == v15)
    {
      v29 = 3;
    }
    else if (haveskill[4] == v15)
    {
      v29 = 4;
    }
    else if (haveskill[5] == v15)
    {
      v29 = 5;
    }
    else if (haveskill[6] == v15)
    {
      v29 = 6;
    }
    else if (haveskill[7] == v15)
    {
      v29 = 7;
    }
    else if (haveskill[8] == v15)
    {
      v29 = 8;
    }
    else if (haveskill[9] == v15)
    {
      v29 = 9;
    }
    else if (haveskill[10] == v15)
    {
      v29 = 10;
    }
    else if (haveskill[11] == v15)
    {
      v29 = 11;
    }
    else if (haveskill[12] == v15)
    {
      v29 = 12;
    }
    else if (haveskill[13] == v15)
    {
      v29 = 13;
    }
    else if (haveskill[14] == v15)
    {
      v29 = 14;
    }
    else if (haveskill[15] == v15)
    {
      v29 = 15;
    }
    else
    {
      if (haveskill[16] != v15)
        goto LABEL_92;
      v29 = 16;
    }
  }
  if (para->autoskill[v29] != 1)
  {
LABEL_92:
    aiwk = Nakama->aiwk;
    rsvSkl = aiwk->rsvSkl;
    rsvTgt = aiwk->rsvTgt;
    aiwk->rsvSkl = v15;
    aiwk->rsvTgt = v21;
    aiwk->rsvStk = v20;
    goto LABEL_94;
  }
  v31 = Nakama->aiwk;
  v31->dfltOdrSkl = v15;
  v31->dfltOdrTgt = v21;
  rsvSkl = v31->rsvSkl;
  rsvTgt = v31->rsvTgt;
  v31->dfltOdrStk = v20;
  v31->rsvSkl = v15;
  v31->rsvTgt = v21;
  v31->rsvStk = v20;
  v31->RepeatOdrSkl = v15;
  v31->RepeatOdrTgt = v21;
  v31->RepeatOdrStk = v20;
LABEL_94:
  ConfigGAME = cfgGetConfigGAME(3, 0);
  if (ConfigGAME)
  {
    v40 = v13 + 1;
    v42 = BYTE1(ProcessData[3].klass);
    GBWK->sbtl_prevSkill[v42] = v13 + 1;
    v43 = v21;
  }
  else
  {
    v43 = 0;
    v40 = 0;
    v42 = BYTE1(ProcessData[3].klass);
    GBWK->sbtl_prevSkill[v42] = 0;
  }
  GBWK->sbtl_prevTarget[v42] = v43;
  v44 = Nakama->para;
  v44->prevSkill = v40;
  v44->prevTarget = v43;
  if ((rsvTgt != v21 || rsvSkl != v15) && Nakama->hpCallCtrl)
  {
    LODWORD(v42) = BYTE1(ProcessData[3].klass);
    wk->closedOkDisp[(u32)v42] = 1;
  }
  if (HIDWORD(ProcessData[4].monitor) != 1)
  {
    if ((Skilltbl->type & 0x1000) == 0)
    {
      mode = Nakama->actaiwk->mode;
      if (mode <= 0x10 && ((1 << mode) & 0x1D9FF) != 0)
      {
        sBtlResetAAI(Nakama);
        sBtlSetMotion(Nakama, 0, 4, 0, 0);
      }
    }
    Nakama->actcounter = Nakama->actcounter_max;
    Nakama->aiwk->usedSkl = 0;
    LOBYTE(ProcessData[4].monitor) = 1;
    sBtlEnd();
    sBtlMenuClose();
    Instance = get_Instance(0);
    BattleMenuClose(Instance, 0, 0);
    EndAnimInfo(instance, 0);
    v56 = get_Instance(0);
    MenuClose(v56->devil_info2, 0);
    v57 = get_Instance(0);
    CharIconCtr(v57, 0, 0);
    infotype = 0;
    devilInfo = 0;
    if (wk->closedOkDisp[BYTE1(ProcessData[3].klass)])
    {
      if (Nakama->hpCallCtrl)
      {
        OkSign(Nakama->hpCallCtrl, 0);
      }
      wk->closedOkDisp[BYTE1(ProcessData[3].klass)] = 0;
    }
    return 1;
  }
  klass_high = HIDWORD(ProcessData[5].klass);
  v47 = LODWORD(ProcessData[5].klass) + 1;
  LODWORD(ProcessData[5].klass) = v47;
  if (v47 < klass_high)
  {
    BYTE1(ProcessData[3].klass) = *((u32 *)ProcessData[5].monitor + v47 + 8);
    SetSklMenu(-1, 0);
    if (infotype == 3)
    {
      EndAnimInfo(instance, 0);
LABEL_164:
      infotype = 0;
      devilInfo = 0;
      return 1;
    }
    v68 = get_Instance(0);
    MenuClose(v68->devil_info2, 0);
    v69 = get_Instance(0);
    CharIconCtr(v69, 0, 0);
    goto LABEL_164;
  }
  LOBYTE(ProcessData[4].monitor) = 1;
  *(u16 *)wk->closedOkDisp = 0;
  v61 = sBtlGetNakama(0);
  if (v61)
  {
    hpCallCtrl = v61->hpCallCtrl;
    if (hpCallCtrl)
      OkSign(hpCallCtrl, 0);
  }
  v63 = sBtlGetNakama(1);
  if (v63)
  {
    v64 = v63->hpCallCtrl;
    if (v64)
      OkSign(v64, 0);
  }
  sBtlEnd();
  return 1;
}

// 0x1f0e000
static void DrawFuncTgt(s32 a_id, s32 x, s32 y, s32 z, u32 fontColor, u8 alphaRate) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *klass;
  void *Instance;
  void *v16;
  void *v19;
  sdatUnitWork_t *v20;
  SBTLUNIT_WORK *v21;
  s32 PlayerID;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v24;
  sdatUnitWork_t *StockUnitData;
  sdatUnitWork_t *v26;
  SBTLUNIT_WORK *pUnit;
  s64 v30;
  void *devil_info2;
  SBTLUNIT_WORK *v33;
  sdatUnitWork_t *para;
  s32 v37;
  void *v38;
  s32 v40;
  void *v43;
  s32 v45;
  void *v47;
  void *v49;
  void *v51;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  klass = ProcessData[2].klass;
  if (itfMenuGetSelectID(ProcessData[2].klass) != a_id)
    return;
  if (HIDWORD(ProcessData[3].klass) == 3)
  {
    if (a_id == 99)
    {
      if (devilInfo)
      {
        Instance = get_Instance(0);
        MenuClose(Instance->devil_info2, 0);
        v16 = get_Instance(0);
        CharIconCtr(v16, 0, 0);
        infotype = 0;
        devilInfo = 0;
        v19 = get_Instance(0);
        GuideSet(v19, "BTL001", 0, 90, 0);
      }
      return;
    }
    if (!LOBYTE(ProcessData[3].monitor))
    {
LABEL_36:
      if (!LOBYTE(ProcessData[3].monitor))
      {
        pUnit = wk->UnitMng->pUnitL[a_id]->pUnit;
        v30 = a_id;
        sBtlSelectTargetCursorSub(pUnit, 0);
        if (a_id <= 0)
        {
          devil_info2 = get_Instance(0)->devil_info2;
          v33 = wk->UnitMng->pUnitL[v30]->pUnit;
          para = v33->para;
          SetDevilStatus(devil_info2, para, 0, 0, GBWK->player, 0, 0);
          v37 = 1;
          infotype = 1;
          v38 = get_Instance(0);
          GuideSet(v38, "BTL001", 0, 90, 0);
          v40 = 1;
LABEL_68:
          if (!devilInfo)
          {
            v47 = get_Instance(0);
            MenuOpne(v47->devil_info2, v37, v40 ^ 1, 0);
            devilInfo = 1;
            v49 = get_Instance(0);
            CharIconCtr(v49, 1, 0);
LABEL_86:
            if (!wk->modeSq)
            {
              sBtlHelp(3, 11, alphaRate);
            }
            return;
          }
          if ((v40 & 1) != 0)
          {
            v45 = 0;
            goto LABEL_84;
          }
          else
          {
            v45 = animChengeTbl[skilltype];
LABEL_84:
            v51 = get_Instance(0);
            MenuChange(v51->devil_info2, v45, 0);
            goto LABEL_86;
          }
          goto LABEL_84;
        }
        v26 = wk->UnitMng->pUnitL[a_id]->pUnit->para;
LABEL_63:
        unitCsr = v26;
        v43 = get_Instance(0);
        Status(v43, v26, skilltype, devilSkillcsr->statusSkillCsr, 0, 0, 0);
        v40 = 0;
        v37 = 2;
        infotype = 2;
        goto LABEL_68;
      }
      Nakama = sBtlGetNakama(0);
      v24 = sBtlGetNakama(1);
      StockUnitData = sBtlGetStockUnitData(a_id - 1);
      v26 = StockUnitData;
      if (!(Nakama && Nakama->para->devilid == StockUnitData->devilid))
      {
        if (!v24 || v24->para->devilid != StockUnitData->devilid)
          goto LABEL_63;
        Nakama = v24;
        goto LABEL_62;
      }
LABEL_62:
      sBtlSelectTargetCursorSub(Nakama, 0);
      goto LABEL_63;
    }
    if (a_id <= 0)
    {
      PlayerID = sBtlGetPlayerID();
      v20 = sBtlGetPlayerUnit(PlayerID)->para;
      v21 = sBtlGetNakama(0);
      if (!v21)
        goto LABEL_35;
    }
    else
    {
      v20 = sBtlGetStockUnitData(a_id - 1);
      v21 = sBtlGetNakama(0);
      if (!v21)
      {
LABEL_35:
        sBtlGetNakama(1);
        goto LABEL_36;
      }
    }
    if (v21->para->devilid == v20->devilid)
      goto LABEL_36;
    goto LABEL_35;
  }
}

// 0x1f0e7b0
static void DrawFuncStock(s32 a_id, s32 x, s32 y, s32 z, u32 fontColor, u8 alphaRate) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *monitor;
  void *Instance;
  void *v17;
  sdatUnitWork_t *StockUnitData;
  SBTLUNIT_WORK *Nakama;
  s32 PlayerID;
  sdatUnitWork_t *para;
  void *v26;
  s32 v28;
  s32 v29;
  s32 v31;
  SBTLUNIT_WORK *pUnit;
  s64 v35;
  s32 v36;
  void *v37;
  void *v39;
  void *v41;
  void *devil_info2;
  s64 v44;
  sdatUnitWork_t *v46;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  monitor = ProcessData[2].monitor;
  if (itfMenuGetSelectID(ProcessData[2].monitor) != a_id)
    return;
  if (HIDWORD(ProcessData[3].klass) == 4)
  {
    if (wk->stock_num + 1 == a_id)
    {
      if (devilInfo)
      {
        Instance = get_Instance(0);
        MenuClose(Instance->devil_info2, 0);
        v17 = get_Instance(0);
        CharIconCtr(v17, 0, 0);
        infotype = 0;
        devilInfo = 0;
      }
      return;
    }
    if (!LOBYTE(ProcessData[3].monitor))
    {
LABEL_38:
      if (LOBYTE(ProcessData[3].monitor))
      {
        para = stockUnitTgt[a_id];
      }
      else
      {
        pUnit = wk->UnitMng->pUnitL[a_id]->pUnit;
        v35 = a_id;
        sBtlSelectTargetCursorSub(pUnit, 0);
        if (a_id < 1)
        {
          devil_info2 = get_Instance(0)->devil_info2;
          v44 = (s64)wk->UnitMng->pUnitL + 8 * v35;
          v46 = *(sdatUnitWork_t *)(*(u64 *)(*(u64 *)(v44 + 32) + 24) + 376);
          SetDevilStatus(devil_info2, v46, 0, 0, GBWK->player, 0, 0);
          v29 = 1;
          v28 = 1;
          infotype = 1;
          goto LABEL_47;
        }
        para = wk->UnitMng->pUnitL[a_id]->pUnit->para;
      }
      unitCsr = para;
      v26 = get_Instance(0);
      Status(v26, para, skilltype, devilSkillcsr->statusSkillCsr, 0, 0, 0);
      v28 = 0;
      v29 = 2;
      infotype = 2;
LABEL_47:
      if (!devilInfo)
      {
        v36 = v28 ^ 1;
        v37 = get_Instance(0);
        MenuOpne(v37->devil_info2, v29, v36, 0);
        devilInfo = 1;
        v39 = get_Instance(0);
        CharIconCtr(v39, 1, 0);
LABEL_70:
        if (!wk->modeSq)
        {
          sBtlHelp(3, 11, alphaRate);
        }
        return;
      }
      if ((v28 & 1) != 0)
      {
        v31 = 0;
        goto LABEL_68;
      }
      else
      {
        v31 = animChengeTbl[skilltype];
LABEL_68:
        v41 = get_Instance(0);
        MenuChange(v41->devil_info2, v31, 0);
        goto LABEL_70;
      }
      goto LABEL_68;
    }
    if (a_id <= 0)
    {
      PlayerID = sBtlGetPlayerID();
      StockUnitData = sBtlGetPlayerUnit(PlayerID)->para;
      Nakama = sBtlGetNakama(0);
      if (!Nakama)
        goto LABEL_37;
    }
    else
    {
      StockUnitData = sBtlGetStockUnitData(a_id - 1);
      Nakama = sBtlGetNakama(0);
      if (!Nakama)
      {
LABEL_37:
        sBtlGetNakama(1);
        goto LABEL_38;
      }
    }
    if (Nakama->para->devilid == StockUnitData->devilid)
      goto LABEL_38;
    goto LABEL_37;
  }
}

// 0x1f0eec0
static void DrawFuncTgtEnemy(s32 a_id, s32 x, s32 y, s32 z, u32 fontColor, u8 alphaRate) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *klass;
  SBTLUNIT_WORK *pUnit;
  void *Instance;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  klass = ProcessData[2].klass;
  if (itfMenuGetSelectID(klass) != a_id)
    return;
  pUnit = wk->UnitMng->pUnitL[a_id]->pUnit;
  sBtlSelectTargetCursorSub(pUnit, 0);
  Instance = get_Instance(0);
  DrawEnemyInfo(Instance, wk->UnitMng->pUnitL[a_id]->pUnit, 0, 0);
  infotype = 3;
  if (!wk->modeSq)
  {
    sBtlHelp(3, 11, alphaRate);
  }
}

// 0x1f0f180
static void SetTgtMenu(s32 a_selectNo) {
  Il2CppObject *ProcessData;
  SBTLUNIT_WORK *Nakama;
  s32 stock_num;
  dds3ProcessID_t *monitor;
  SKLID *stock_useskill;
  s32 v12;
  SBTLSKILLP_TBL *Skilltbl;
  dds3ProcessID_t *klass;
  dds3ProcessID_t *v18;
  u16 area;
  dds3ProcessID_t *v21;
  dds3ProcessID_t *v23;
  s32 i;
  s32 devilid;
  dds3ProcessID_t *v27;
  s32 playerID;
  char *PlayerName;
  itfMenuFunc_t v30;
  dds3ProcessID_t *v31;
  s32 v32;
  itfMenuDrawFunc_t v33;
  dds3ProcessID_t *v34;
  s32 v35;
  s32 *IdList;
  f32 v37;
  f32 v38;
  s32 *v39;
  s64 v40;
  s32 *m_Items;
  s32 v42;
  s32 v43;
  dds3ProcessID_t *v44;
  bool FlagMenu;
  SBTLUNIT_WORK *v47;
  sdatUnitWork_t *v48;
  u32 flg;
  SBTLAISYO_DATAWORK *aisyo;
  u32 attr;
  s16 v52;
  s32 hp;
  s64 v55;
  SBTLUNIT_LISTWORK *UnitMng;
  dds3ProcessID_t *v57;
  dds3ProcessID_t *v58;
  void *v60;
  dds3ProcessID_t *v61;
  s32 v62;
  char *v63;
  itfMenuFunc_t v64;
  dds3ProcessID_t *v65;
  itfMenuDrawFunc_t v66;
  s64 j;
  SBTLUNIT_LISTWORK *v69;
  SBTLUNIT_WORK *pUnit;
  s32 v71;
  dds3ProcessID_t *v73;
  s32 v74;
  char *v75;
  itfMenuFunc_t v76;
  dds3ProcessID_t *v77;
  itfMenuDrawFunc_t v78;
  sdatUnitWork_t *para;
  bool v81;
  dds3ProcessID_t *v83;
  void *Instance;
  s32 monitor_high;
  s32 v87;
  s32 v88;
  sdatUnitWork_t *v90;
  sdatUnitWork_t *v91;
  SBTLUNIT_WORK *NakamaUnit;
  SBTLUNIT_WORK *v93;
  dds3ProcessID_t *v94;
  s32 v95;
  char *v96;
  itfMenuFunc_t v97;
  dds3ProcessID_t *v98;
  itfMenuDrawFunc_t v99;
  bool v101;
  SBTLUNIT_WORK *PChara;
  dds3ProcessID_t *v104;
  s32 v105;
  char *v106;
  itfMenuFunc_t v107;
  dds3ProcessID_t *v108;
  s32 v109;
  itfMenuDrawFunc_t v110;
  SBTLSKILLP_TBL *v112;
  sdatUnitWork_t *v113;
  bool v114;
  dds3ProcessID_t *v116;
  s32 v117;
  s32 k;
  bool v119;
  dds3ProcessID_t *v120;
  s32 v121;
  SBTLUNIT_WORK *v122;
  sdatUnitWork_t *v123;
  SBTLUNIT_WORK *v124;
  s32 m;
  s32 v126;
  dds3ProcessID_t *v127;
  itfMenuDrawFunc_t v128;
  sdatUnitWork_t *StockUnitData;
  s32 ListID;
  dds3ProcessID_t *v132;
  s32 v133;
  char *v134;
  itfMenuFunc_t v135;
  sdatUnitWork_t *v136;
  dds3ProcessID_t *v138;
  s32 v139;
  sdatUnitWork_t *v140;
  bool v141;
  dds3ProcessID_t *v142;
  s32 v143;
  _BOOL4 v144;
  s32 v145;
  dds3ProcessID_t *v146;
  char *LocalizeText;
  itfMenuFunc_t v148;
  dds3ProcessID_t *v149;
  itfMenuDrawFunc_t v150;
  dds3ProcessID_t *v151;
  Il2CppObject *v152;
  s32 a_sklId;
  sdatUnitWork_t *a_pUseUnit;
  s32 a_pUseUnita;
  SBTLSKILLP_TBL *v157;
  dds3ProcessID_t *v158;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  Nakama = sBtlGetNakama(BYTE1(ProcessData[3].klass));
  a_pUseUnit = Nakama->para;
  stock_num = wk->stock_num;
  if (Exists("new_devil"))
  {
    goto LABEL_16;
  }
  for (i = 0; ; ++i)
  {
    if (i >= wk->stock_num)
      break;
    devilid = sBtlGetStockUnitData(i)->devilid;
    stock_num -= sBtlIsDLCDevil(devilid);
  }
LABEL_16:
  monitor = ProcessData[1].monitor;
  stock_useskill = wk->stock_useskill;
  v12 = stock_useskill[itfMenuGetSelectID(monitor)];
  if ((v12 & 0xFFFFFFFE) == 0x76)
  {
    bRikamu = 1;
    SetStockMenu(-1);
    return;
  }
  a_sklId = v12;
  Skilltbl = sBtlGetSkilltbl(v12);
  sBtlGetNakama(0);
  sBtlGetNakama(1);
  v18 = &ProcessData[2];
  klass = ProcessData[2].klass;
  LOWORD(ProcessData[3].monitor) = 0;
  itfMenuClearMenuAll(klass);
  area = Skilltbl->area;
  v152 = ProcessData;
  v158 = &ProcessData[2];
  v157 = Skilltbl;
  if ((area & 8) != 0)
  {
    v27 = v18;
    playerID = wk->playerID;
    PlayerName = sBtlGetPlayerName();
    v30 = Allocate(itfMenuFunc_t);
    _ctor(v30, 0, Method_Project_sBtlCmndMenuNew_FuncDecideTgt__, 0);
    itfMenuSetRootMenu(v27, playerID, PlayerName, v30, "");
    v31 = v18;
    v32 = wk->playerID;
    v33 = Allocate(itfMenuDrawFunc_t);
    _ctor(v33, 0, Method_Project_sBtlCmndMenuNew_DrawFuncTgt__, 0);
    itfMenuSetDrawFunc(v31, v32, v33, 0);
    v34 = v18;
    v35 = wk->playerID;
LABEL_49:
    itfMenuSetFlagMenu(v34, v35, 2, 1);
    a_pUseUnita = 0;
    v23 = v18;
    goto LABEL_51;
  }
  if ((Skilltbl->area & 0x2000) != 0)
  {
    v55 = 0;
    while (1)
    {
      UnitMng = wk->UnitMng;
      if (v55 >= UnitMng->number)
        break;
      UnitMng = wk->UnitMng;
      if (Nakama == UnitMng->pUnitL[v55]->pUnit)
      {
        v61 = v18;
        v62 = Nakama->para->devilid;
        v63 = sdatDevilName(v62, 0);
        v64 = Allocate(itfMenuFunc_t);
        _ctor(v64, 0, Method_Project_sBtlCmndMenuNew_FuncDecideTgt__, 0);
        itfMenuSetRootMenu(v61, v55, v63, v64, "");
        v65 = v18;
        v66 = Allocate(itfMenuDrawFunc_t);
        _ctor(v66, 0, Method_Project_sBtlCmndMenuNew_DrawFuncTgt__, 0);
        itfMenuSetDrawFunc(v65, v55, v66, 0);
        v34 = v18;
        v35 = v55;
        goto LABEL_49;
      }
      ++v55;
    }
    a_pUseUnita = 0;
    v23 = v18;
    goto LABEL_51;
  }
  if ((Skilltbl->area & 0x8000) != 0)
  {
    for (j = 0; ; ++j)
    {
      v69 = wk->UnitMng;
      if (j >= v69->number)
      {
        Instance = get_Instance(0);
        OpenHuumaInfo(Instance, 0);
        a_pUseUnita = 0;
        v21 = v18;
        goto LABEL_32;
      }
      pUnit = v69->pUnitL[j]->pUnit;
      if (!pUnit)
        continue;
      if ((pUnit->side & 2) == 0)
        continue;
      if (!CheckLiveTarget(pUnit))
        continue;
      v71 = (u16)pUnit->para->devilid;
      if (v71 != 314 && v71 != 311)
      {
        if (v71 != 258)
          goto LABEL_135;
        if (BS_LASTB2_pos_type)
        {
LABEL_135:
          if ((pUnit->flg & 0x200) == 0)
          {
            v73 = v18;
            v74 = pUnit->para->devilid;
            v75 = sdatDevilName(v74, 0);
            v76 = Allocate(itfMenuFunc_t);
            _ctor(v76, 0, Method_Project_sBtlCmndMenuNew_FuncDecideTgt__, 0);
            itfMenuSetRootMenu(v73, j, v75, v76, "");
            v77 = v18;
            v78 = Allocate(itfMenuDrawFunc_t);
            _ctor(v78, 0, Method_Project_sBtlCmndMenuNew_DrawFuncTgtEnemy__, 0);
            itfMenuSetDrawFunc(v77, j, v78, 0);
            para = pUnit->para;
            v81 = SkillChkUseUnit(pUnit, para, a_pUseUnit, a_sklId);
            v83 = v18;
            itfMenuSetFlagMenu(v83, wk->playerID, 2, v81);
          }
        }
      }
    }
  }
  if ((Skilltbl->area & 0x4000) == 0)
    goto LABEL_30;
  BYTE1(ProcessData[3].monitor) = (area & 0x20) == 0;
  monitor_high = HIDWORD(ProcessData[3].monitor);
  if (!monitor_high)
  {
    PChara = sBtlGetPChara();
    v104 = v18;
    v105 = wk->playerID;
    v106 = sBtlGetPlayerName();
    v107 = Allocate(itfMenuFunc_t);
    _ctor(v107, 0, Method_Project_sBtlCmndMenuNew_FuncDecideTgt__, 0);
    itfMenuSetRootMenu(v104, v105, v106, v107, "");
    v108 = v18;
    v109 = wk->playerID;
    v110 = Allocate(itfMenuDrawFunc_t);
    _ctor(v110, 0, Method_Project_sBtlCmndMenuNew_DrawFuncTgt__, 0);
    itfMenuSetDrawFunc(v108, v109, v110, 0);
    v112 = v157;
    if ((v157->area & 4) != 0)
    {
      v114 = 1;
    }
    else
    {
      v113 = PChara->para;
      v114 = SkillChkUseUnit(PChara, v113, a_pUseUnit, a_sklId);
    }
    v116 = v18;
    v117 = wk->playerID;
    itfMenuSetFlagMenu(v116, v117, 2, v114);
    for (k = 0; k != 2; ++k)
    {
      v122 = sBtlGetNakama(k);
      if (v122)
      {
        v123 = v122->para;
        v124 = v122;
        for (m = 0; ; ++m)
        {
          if (m >= wk->stock_num)
            break;
          StockUnitData = sBtlGetStockUnitData(m);
          if (v123->devilid == StockUnitData->devilid && v123->uniq_code == StockUnitData->uniq_code)
          {
            ListID = v124->ListID;
            v132 = v158;
            v133 = v124->para->devilid;
            v134 = sdatDevilName(v133, 0);
            v135 = Allocate(itfMenuFunc_t);
            _ctor(v135, 0, Method_Project_sBtlCmndMenuNew_FuncDecideTgt__, 0);
            itfMenuSetRootMenu(v132, ListID, v134, v135, "");
            v126 = v124->ListID;
            v127 = v158;
            v128 = Allocate(itfMenuDrawFunc_t);
            _ctor(v128, 0, Method_Project_sBtlCmndMenuNew_DrawFuncTgt__, 0);
            itfMenuSetDrawFunc(v127, v126, v128, 0);
          }
        }
        v136 = v124->para;
        v18 = v158;
        v112 = v157;
        if (sBtlGetBadStatus(v136) == 17)
        {
          v138 = v158;
          v139 = v124->ListID;
          v120 = v138;
          v121 = v139;
          v119 = 0;
        }
        else
        {
          if ((v157->area & 4) != 0)
          {
            v141 = 1;
          }
          else
          {
            v140 = v124->para;
            v141 = SkillChkUseUnit(v124, v140, a_pUseUnit, a_sklId);
          }
          v142 = v158;
          v143 = v124->ListID;
          v119 = v141;
          v120 = v142;
          v121 = v143;
        }
        itfMenuSetFlagMenu(v120, v121, 2, v119);
      }
    }
    if ((v112->area & 0x20) != 0 || (v112->flg & 0x200) != 0)
    {
      a_pUseUnita = 0;
      v21 = v18;
      goto LABEL_32;
    }
    v144 = sBtlGetNakama(0) != 0;
    if (sBtlGetNakama(1))
      v145 = -1;
    else
      v145 = 0;
    if (v145 - v144 + stock_num >= 1)
    {
      v146 = v18;
      LocalizeText = GetLocalizeText("SBTL_MENU_L0021", 1);
      v148 = Allocate(itfMenuFunc_t);
      _ctor(v148, 0, Method_Project_sBtlCmndMenuNew_FuncDecideTgt__, 0);
      itfMenuSetRootMenu(v146, 99, LocalizeText, v148, "");
      v149 = v18;
      v150 = Allocate(itfMenuDrawFunc_t);
      _ctor(v150, 0, Method_Project_sBtlCmndMenuNew_DrawFuncTgt__, 0);
      itfMenuSetDrawFunc(v149, 99, v150, 0);
      v151 = v18;
      itfMenuSetFlagMenu(v151, 99, 2, 1);
      a_pUseUnita = 0;
      v21 = v18;
      goto LABEL_32;
    }
LABEL_30:
    a_pUseUnita = 0;
    v21 = v18;
    goto LABEL_32;
  }
  if (monitor_high < 1)
    goto LABEL_30;
  v87 = 8 * monitor_high;
  LOBYTE(ProcessData[3].monitor) = 1;
  v88 = 0;
  while (v88 < wk->stock_num)
  {
    v90 = sBtlGetStockUnitData(v88);
    if (v90)
    {
      v91 = v90;
      NakamaUnit = sBtlGetNakamaUnit(v91);
      v93 = NakamaUnit;
      if (NakamaUnit)
        v91 = NakamaUnit->para;
      v94 = v18;
      v95 = v91->devilid;
      v96 = sdatDevilName(v95, 0);
      v97 = Allocate(itfMenuFunc_t);
      _ctor(v97, 0, Method_Project_sBtlCmndMenuNew_FuncDecideTgt__, 0);
      itfMenuSetRootMenu(v94, ++v88, v96, v97, "");
      v98 = v18;
      v99 = Allocate(itfMenuDrawFunc_t);
      _ctor(v99, 0, Method_Project_sBtlCmndMenuNew_DrawFuncTgt__, 0);
      itfMenuSetDrawFunc(v98, v88, v99, 0);
      v101 = SkillChkUseUnit(v93, v91, a_pUseUnit, a_sklId);
      itfMenuSetFlagMenu(v18, v88, 2, v101);
    }
    else
    {
      ++v88;
    }
  }
  a_pUseUnita = 1;
  v21 = v18;
LABEL_32:
  itfMenuSetFlag(v21, 512, 0);
  v23 = v18;
LABEL_51:
  itfMenuSetFlag(v23, 1024, 0);
  dds3GetProcessData(v18);
  IdList = itfMenuGetIdList(v18);
  if (SLODWORD(IdList->max_length) >= 1)
  {
    v37 = -1.0;
    v38 = 9999.0;
    v39 = IdList;
    v40 = 0;
    m_Items = IdList;
    v42 = -1;
    while (1)
    {
      v43 = m_Items[v40];
      v44 = v18;
      FlagMenu = itfMenuGetFlagMenu(v44, v43, 2u);
      if (v43 != 99 && FlagMenu)
      {
        v47 = wk->UnitMng->pUnitL[v43]->pUnit;
        v48 = sBtlGetStockUnitData(v43 - 1);
        if (!v47)
          goto LABEL_78;
        flg = v157->flg;
        if ((flg & 0x220) != 0)
        {
          v18 = v158;
          v43 = v42;
LABEL_96:
          if ((v43 & 0x80000000) == 0)
            goto LABEL_98;
          break;
        }
        if ((flg & 0x3000) == 0)
        {
          if ((flg & 0x10000) != 0)
            goto LABEL_174;
          aisyo = v47->para->aisyo;
          attr = v157->attr;
          v52 = sBtlCheckAisyo_Old(aisyo, attr);
          if (a_sklId != 149 && (v52 & 0x4000) != 0)
          {
LABEL_174:
            v18 = v158;
            if ((v43 & 0x80000000) == 0)
              goto LABEL_98;
            break;
          }
          if (a_selectNo == -1 && (hp = v47->para->now->hp, v37 = (f32)hp, v38 > (f32)hp))
            v38 = hp;
          else
LABEL_78:
            v43 = v42;
          v18 = v158;
          goto LABEL_56;
        }
        if (!a_pUseUnita)
        {
          v48 = v47->para;
          v18 = v158;
LABEL_81:
          v37 = v48->now->hp;
          if (v37 < v38)
          {
LABEL_82:
            v38 = v37;
            goto LABEL_56;
          }
          goto LABEL_55;
        }
        v18 = v158;
        if (v48)
          goto LABEL_81;
        if (v37 < v38)
          goto LABEL_82;
      }
LABEL_55:
      v43 = v42;
LABEL_56:
      ++v40;
      v42 = v43;
      if (v40 >= SLODWORD(v39->max_length))
        goto LABEL_96;
    }
  }
  v43 = a_selectNo;
LABEL_98:
  if ((v43 & 0x80000000) == 0)
  {
    v57 = v18;
    itfMenuSetInitSelectID(v57, v43);
  }
  v58 = v18;
  itfMenuStart(v58);
  MenuCnt = 0;
  HIDWORD(v152[3].klass) = 3;
  v60 = get_Instance(0);
  OpenTargetMenu(v60, v18, 0);
}

// 0x1f0c9d0
static void SetStockMenu(s32 a_selectNo) {
  Il2CppObject *ProcessData;
  Il2CppObject *v5;
  dds3ProcessID_t *monitor;
  SKLID *stock_useskill;
  s32 v10;
  SBTLSKILLP_TBL *Skilltbl;
  dds3ProcessID_t *v12;
  dds3ProcessID_t *p_monitor;
  dds3ProcessID_t *v14;
  s32 *IdList;
  f32 hp;
  f32 v17;
  s32 *v18;
  s64 v19;
  s32 *m_Items;
  s32 v21;
  s32 v22;
  dds3ProcessID_t *v23;
  SBTLUNIT_WORK *pUnit;
  sdatUnitWork_t *v26;
  u32 flg;
  dds3ProcessID_t *v28;
  dds3ProcessID_t *v29;
  void *Instance;
  s64 v33;
  s32 v34;
  s32 v35;
  SBTLUNIT_WORK *v36;
  sdatUnitWork_t *StockUnitData;
  sdatUnitWork_t *v39;
  SBTLUNIT_WORK *NakamaUnit;
  s64 v42;
  s64 v43;
  void **v44;
  Il2CppClass *v45;
  sdatUnitWork_t *stockUnitTgt_local;
  Il2CppClass **v48;
  s32 i;
  sdatUnitWork_t *v50;
  sdatUnitWork_t *v51;
  SBTLUNIT_WORK *v52;
  s64 v55;
  s64 v56;
  void **v57;
  Il2CppClass *v58;
  sdatUnitWork_t *v59;
  Il2CppClass **v60;
  s64 v61;
  s64 v62;
  s32 v63;
  dds3ProcessID_t *v64;
  s32 v65;
  char *v66;
  itfMenuFunc_t v67;
  dds3ProcessID_t *v68;
  itfMenuDrawFunc_t v69;
  sdatUnitWork_t *v71;
  bool v72;
  dds3ProcessID_t *v73;
  s32 v76;
  Il2CppObject *v77;
  s64 v78;
  sdatUnitWork_t *v79;
  u16 area;
  sdatUnitWork_t *para;

  ProcessData = dds3GetProcessData(g_mainPID);
  v5 = ProcessData;
  v79 = NewSpecific(sdatUnitWork_t, 0x18u);
  para = sBtlGetNakama(BYTE1(v5[3].klass))->para;
  v76 = a_selectNo;
  monitor = v5[1].monitor;
  stock_useskill = wk->stock_useskill;
  v10 = stock_useskill[itfMenuGetSelectID(monitor)];
  Skilltbl = sBtlGetSkilltbl(v10);
  v77 = v5;
  p_monitor = &v5[2].monitor;
  v12 = v5[2].monitor;
  LOWORD(v5[3].monitor) = 0;
  itfMenuClearMenuAll(v12);
  area = Skilltbl->area;
  if ((area & 0x4000) != 0)
  {
    v33 = v79;
    v34 = 0;
    v35 = 0;
    v36 = 0;
    LOBYTE(v5[3].monitor) = 1;
    v78 = &v79[0];
    while (1)
    {
      if (v35 >= wk->stock_num)
        break;
      StockUnitData = sBtlGetStockUnitData(v35);
      if (!StockUnitData)
        goto LABEL_50;
      v39 = StockUnitData;
      NakamaUnit = sBtlGetNakamaUnit(StockUnitData);
      if (NakamaUnit)
      {
        v36 = NakamaUnit;
        goto LABEL_50;
      }
      if (!SkillChkUseUnit(0, v39, para, v10))
      {
        v36 = 0;
        goto LABEL_50;
      }
      if (!QueryInterface(v39, *(void **)(*(u64 *)v33 + 64)))
        goto LABEL_120;
      v42 = 8 * v34;
      v43 = v33 + v42;
      *(u64 *)(v43 + 32) = v39;
      v44 = (v43 + 32);
      v45 = *v44;
      stockUnitTgt_local = stockUnitTgt;
      if (v45)
      {
        {
LABEL_120:
        }
      }
      v48 = &stockUnitTgt_local->obj.klass + v34;
      v48[4] = v45;
      v33 = v79;
      v36 = 0;
      ++v34;
LABEL_50:
      ++v35;
    }
    for (i = 0; ; ++i)
    {
      if (i >= wk->stock_num)
        break;
      v50 = sBtlGetStockUnitData(i);
      if (!v50)
        goto LABEL_72;
      v51 = v50;
      v52 = sBtlGetNakamaUnit(v50);
      if (v52)
      {
        v36 = v52;
        goto LABEL_72;
      }
      if (SkillChkUseUnit(0, v51, para, v10))
      {
        v36 = 0;
        goto LABEL_72;
      }
      if (!QueryInterface(v51, *(void **)(*(u64 *)v33 + 64)))
        goto LABEL_120;
      v55 = 8 * v34;
      v56 = v33 + v55;
      *(u64 *)(v56 + 32) = v51;
      v57 = (v56 + 32);
      v58 = *v57;
      v59 = stockUnitTgt;
      v60 = &v59->obj.klass + v34;
      v60[4] = v58;
      v33 = v79;
      v36 = 0;
      ++v34;
LABEL_72:
    }
    v61 = 0;
    v62 = v33 + 32;
    while (1)
    {
      if (v61 >= wk->stock_num)
        break;
      if (*(u64 *)(v62 + 8 * v61))
      {
        if (Exists("new_devil"))
          goto LABEL_107;
        v63 = *(s16 *)(*(u64 *)(v62 + 8 * v61) + 22);
        if (!sBtlIsDLCDevil(v63))
          goto LABEL_107;
        goto LABEL_9006;
        if (!sBtlIsDLCDevil(v63))
        {
LABEL_107:
          v64 = p_monitor;
          v65 = *(s16 *)(*(u64 *)(v62 + 8 * v61) + 22);
          v66 = sdatDevilName(v65, 0);
          v67 = Allocate(itfMenuFunc_t);
          _ctor(v67, 0, Method_Project_sBtlCmndMenuNew_FuncDecideStock__, 0);
          itfMenuSetRootMenu(v64, v61, v66, v67, "");
          v68 = p_monitor;
          v69 = Allocate(itfMenuDrawFunc_t);
          _ctor(v69, 0, Method_Project_sBtlCmndMenuNew_DrawFuncStock__, 0);
          itfMenuSetDrawFunc(v68, v61, v69, 0);
          if ((Skilltbl->area & 4) != 0)
          {
            v72 = 1;
            v73 = p_monitor;
          }
          else
          {
            v71 = *(sdatUnitWork_t *)(v62 + 8 * v61);
            v72 = SkillChkUseUnit(v36, v71, para, v10);
            v73 = p_monitor;
          }
          itfMenuSetFlagMenu(v73, v61, 2, v72);
        }
LABEL_9006:
      }
      ++v61;
    }
  }
  v14 = p_monitor;
  itfMenuSetFlag(v14, 512, 0);
  itfMenuSetFlag(p_monitor, 1024, 0);
  dds3GetProcessData(p_monitor);
  IdList = itfMenuGetIdList(p_monitor);
  if (SLODWORD(IdList->max_length) < 1)
  {
LABEL_36:
    v22 = v76;
    goto LABEL_37;
  }
  hp = -1.0;
  v17 = 9999.0;
  v18 = IdList;
  v19 = 0;
  m_Items = IdList;
  v21 = -1;
  do
  {
    v22 = m_Items[v19];
    v23 = p_monitor;
    if (!itfMenuGetFlagMenu(p_monitor, v22, 2u))
      goto LABEL_20;
    pUnit = wk->UnitMng->pUnitL[v22]->pUnit;
    v26 = sBtlGetStockUnitData(v22 - 1);
    flg = Skilltbl->flg;
    if ((flg & 0x3000) != 0)
    {
      if ((area & 0x4000) != 0)
      {
        if (!v26)
          goto LABEL_33;
      }
      else
      {
        if (!pUnit)
          goto LABEL_33;
        v26 = pUnit->para;
      }
      hp = v26->now->hp;
LABEL_33:
      if (hp < v17)
      {
        v17 = hp;
        v21 = v22;
      }
      goto LABEL_20;
    }
    if ((flg & 0x10000) != 0)
      break;
LABEL_20:
    ++v19;
    v22 = v21;
  }
  while (v19 < SLODWORD(v18->max_length));
  if (v22 < 0)
    goto LABEL_36;
LABEL_37:
  if ((v22 & 0x80000000) == 0)
  {
    v28 = p_monitor;
    itfMenuSetInitSelectID(v28, v22);
  }
  v29 = p_monitor;
  itfMenuStart(v29);
  MenuCnt = 0;
  HIDWORD(v77[3].klass) = 4;
  Instance = get_Instance(0);
  OpenStockMenu(Instance, p_monitor, 0);
}

// 0x1f106a0
static void SetTgtEnemy(s32 a_selectNo, SBTLUNIT_WORK *pNakama) {
  Il2CppObject *ProcessData;
  SBTLUNIT_LISTWORK *UnitList;
  dds3ProcessID_t *monitor;
  SKLID *stock_useskill;
  s32 v12;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLUNIT_WORK *v15;
  s64 i;
  SBATTLE_WORK *wk_local;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 devilid;
  sdatUnitWork_t *para;
  SBTLUNIT_WORK *EnemyUnitTgt_local;
  u64 v29;
  SBTLUNIT_WORK *v30;
  void *Instance;
  s32 v33;
  SBTLUNIT_LISTWORK *tgtList;
  SBTLUNIT_WORK *prevTgtUnit;
  dds3ProcessID_t *v37;
  s64 v39;
  s32 v40;
  f32 v41;
  f32 hp;
  SBTLUNIT_LISTWORK *v43;
  SBTLUNIT_WORK *v44;
  u32 attr;
  SBTLAISYO_DATAWORK *aisyo;
  s16 v47;
  s32 v48;
  void *v50;
  s32 v52;
  SBTLUNIT_LISTWORK *lwk;
  sdatUnitWork_t *a_pUseUnit;
  Il2CppObject *v55;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  UnitList = sBtlCreateUnitList(48);
  a_pUseUnit = sBtlGetNakama(BYTE1(ProcessData[3].klass))->para;
  monitor = ProcessData[1].monitor;
  stock_useskill = wk->stock_useskill;
  v12 = stock_useskill[itfMenuGetSelectID(monitor)];
  Skilltbl = sBtlGetSkilltbl(v12);
  LOWORD(ProcessData[3].monitor) = 0;
  enemyNumCount = -1;
  v15 = NewSpecific(SBTLUNIT_WORK, 0x20u);
  EnemyUnitTgt = v15;
  v55 = ProcessData;
  MenuCnt = 0;
  if ((s16)Skilltbl->area < 0)
  {
    v52 = 0;
    lwk = UnitList;
    for (i = 0; ; ++i)
    {
      wk_local = wk;
      UnitMng = wk_local->UnitMng;
      if (i >= UnitMng->number)
      {
        wk_local = wk;
        wk_local->tgtList = lwk;
        Instance = get_Instance(0);
        OpenHuumaInfo(Instance, 0);
        wk->status |= 0x80000u;
        enemyNowCsr = 0;
        break;
      }
      pUnit = UnitMng->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if ((pUnit->side & 2) == 0)
        continue;
      if (!CheckLiveTarget(pUnit))
        continue;
      if ((pUnit->status & 0x4000000) == 0)
      {
        devilid = (u16)pUnit->para->devilid;
        switch (pUnit->para->devilid)
        {
          case 0x137:
          case 0x13B:
          case 0x143:
            continue;
          case 0x138:
          case 0x139:
          case 0x13C:
          case 0x13D:
          case 0x13E:
          case 0x13F:
          case 0x140:
          case 0x141:
          case 0x142:
            goto LABEL_45;
          case 0x13A:
            if (pUnit->ListID == 6)
              goto LABEL_45;
            continue;
          default:
            if (devilid != 258)
            {
              if (devilid == 259)
                continue;
LABEL_45:
              if ((pUnit->flg & 0x200) == 0)
              {
                para = pUnit->para;
                SkillChkUseUnit(pUnit, para, a_pUseUnit, v12);
                EnemyUnitTgt_local = EnemyUnitTgt;
                sub_C80(EnemyUnitTgt_local, pUnit);
                v29 = v52;
                EnemyUnitTgt_local[v29] = pUnit;
                v30 = EnemyUnitTgt[v29];
                sBtlEntryUnitList(lwk, v30);
                ++v52;
                ++enemyNumCount;
              }
              continue;
            }
            if (BS_LASTB2_pos_type)
              goto LABEL_45;
            break;
        }
      }
    }
  }
  v33 = 0;
  while (1)
  {
    tgtList = wk->tgtList;
    if (v33 >= tgtList->count)
      break;
    prevTgtUnit = pNakama->para->prevTgtUnit;
    if (!prevTgtUnit)
      break;
    tgtList = wk->tgtList;
    if (prevTgtUnit == tgtList->pUnitL[v33]->pUnit)
      goto LABEL_69;
    ++v33;
  }
  v33 = -1;
LABEL_69:
  dds3GetProcessData(&ProcessData[2]);
  v37 = ProcessData[2].monitor;
  itfMenuGetIdList(v37);
  v39 = 0;
  v40 = -1;
  v41 = 9999.0;
  while (1)
  {
    v43 = wk->tgtList;
    if (v39 >= v43->count)
      break;
    v44 = v43->pUnitL[v39]->pUnit;
    if (!v44)
      goto LABEL_75;
    attr = Skilltbl->attr;
    aisyo = v44->para->aisyo;
    v47 = sBtlCheckAisyo_Old(aisyo, attr);
    if (v12 != 149 && (v47 & 0x4000) != 0)
    {
      v40 = v39;
      break;
    }
    if (v33 != -1 || (hp = (f32)v44->para->now->hp, v41 <= hp))
    {
LABEL_75:
      hp = v41;
      goto LABEL_76;
    }
    v40 = v39;
LABEL_76:
    v41 = hp;
    ++v39;
  }
  if (v40 >= 0)
    v48 = v40;
  else
    v48 = v33;
  if ((v48 & 0x80000000) == 0)
  {
    enemyNowCsr = v48;
  }
  v50 = get_Instance(0);
  BattleMenuClose(v50, 1, 0);
  MenuCnt = 0;
  HIDWORD(v55[3].klass) = 5;
}

// 0x1f10eb0
static void TgtEnemySel(void) {
  s32 v5;
  s32 enemyNumCount_local;
  u32 v12;
  s32 v13;
  SBATTLE_WORK *v15;
  SBATTLE_WORK *v17;
  SBTLUNIT_WORK *pUnit;
  s64 i;
  SBTLUNIT_LISTWK *pUnitL;
  void *Instance;

  if (!wk->tgtList)
    return;
  if (wk->modeSq)
    goto LABEL_43;
  if (MenuCnt >= 15)
  {
    if (CHECK_TRIG(4096, 1))
    {
      FuncDecideEnemyTgt();
      v5 = 0;
      goto LABEL_42;
    }
    if (CHECK_TRIG(4100, 1) || CHECK_TRIG(4103, 1))
    {
      if (enemyNowCsr >= enemyNumCount)
      {
        enemyNowCsr = 0;
        goto LABEL_41;
      }
      enemyNumCount_local = enemyNowCsr + 1;
LABEL_40:
      enemyNowCsr = enemyNumCount_local;
LABEL_41:
      v5 = 3;
LABEL_42:
      SE(v5);
      goto LABEL_43;
    }
    if (CHECK_TRIG(4101, 1) || CHECK_TRIG(4102, 1))
    {
      v13 = enemyNowCsr;
      if (v13 < 1)
      {
        enemyNumCount_local = enemyNumCount;
      }
      else
      {
        if (!v12)
        {
          v13 = enemyNowCsr;
        }
        enemyNumCount_local = v13 - 1;
      }
      goto LABEL_40;
    }
  }
LABEL_43:
  v15 = wk;
  v17 = v15;
  v15->tgt_csr = enemyNowCsr;
  pUnit = v17->tgtList->pUnitL[v17->tgt_csr]->pUnit;
  if (pUnit->para->devilid == 314)
  {
    for (i = 4; ; ++i)
    {
      pUnitL = wk->UnitMng->pUnitL;
      if (i - 4 >= SLODWORD(pUnitL->max_length))
        break;
      if (!*(u64 *)(*((u64 *)&pUnitL->obj.klass + i) + 24))
        continue;
      if (*(u16 *)(*(u64 *)(*(u64 *)(*((u64 *)&wk->UnitMng->pUnitL->obj.klass + i) + 24) + 376) + 22) == 258)
      {
        pUnit = *(SBTLUNIT_WORK *)(*((u64 *)&wk->UnitMng->pUnitL->obj.klass + i) + 24);
        pUnit = *(SBTLUNIT_WORK *)(*((u64 *)&wk->UnitMng->pUnitL->obj.klass + i) + 24);
        break;
      }
    }
  }
  sBtlDrawTargetCursorEnemy();
  Instance = get_Instance(0);
  DrawEnemyInfo(Instance, pUnit, 1, 0);
  infotype = 3;
  return;
}

// 0x1f11300
static s32 FuncDecideEnemyTgt(void) {
  Il2CppObject *ProcessData;
  SBTLUNIT_WORK *Nakama;
  dds3ProcessID_t *monitor;
  s32 SelectID;
  s32 v9;
  dds3ProcessID_t *klass;
  s32 v11;
  sdatUnitWork_t *StockUnitData;
  s64 v14;
  s32 ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  SBTLUNIT_WORK *v20;
  s64 v21;
  SBTLUNIT_LISTWORK *v22;
  SBTLUNIT_WORK *v23;
  s64 v24;
  SBTLUNIT_LISTWORK *v25;
  SBTLUNIT_WORK *v26;
  sdatUnitWork_t *para;
  s64 v30;
  SKLID *haveskill;
  SBTLAI_WORK *v32;
  s32 rsvSkl;
  s32 rsvTgt;
  SBTLAI_WORK *aiwk;
  s32 ConfigGAME;
  s64 v40;
  dds3GlobalWork_t *v41;
  sdatUnitWork_t *v43;
  s64 v44;
  s64 v45;
  SBTLUNIT_LISTWK *pUnitL;
  SBTLUNIT_WORK *v49;
  s64 v51;
  s64 v53;
  s64 v54;
  sdatUnitWork_t *v55;
  s32 klass_high;
  s32 v58;
  u32 mode;
  void *Instance;
  SBTLUNIT_WORK *v70;
  HpCallCtrl *hpCallCtrl;
  SBTLUNIT_WORK *v72;
  HpCallCtrl *v73;
  void *v76;
  void *v77;
  void *v82;
  void *v83;
  SBTLSKILLP_TBL *Skilltbl;
  s32 v86;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  Nakama = sBtlGetNakama(BYTE1(ProcessData[3].klass));
  monitor = ProcessData[1].monitor;
  SelectID = itfMenuGetSelectID(monitor);
  v9 = wk->stock_useskill[SelectID];
  Skilltbl = sBtlGetSkilltbl(v9);
  v86 = SelectID;
  if ((Skilltbl->area & 4) == 0)
  {
    if (LOBYTE(ProcessData[3].monitor))
    {
      klass = ProcessData[2].klass;
      v11 = itfMenuGetSelectID(klass) - 1;
      StockUnitData = sBtlGetStockUnitData(v11);
      v14 = 0;
      ListID = -1;
      while (1)
      {
        UnitMng = wk->UnitMng;
        if (v14 >= UnitMng->number)
          goto LABEL_57;
        pUnit = UnitMng->pUnitL[v14]->pUnit;
        if (pUnit)
        {
          if ((pUnit->side & 1) != 0 && pUnit->para->devilid == StockUnitData->devilid)
          {
            ListID = pUnit->ListID;
            v11 = -1;
            goto LABEL_57;
          }
        }
        ++v14;
      }
    }
    ListID = enemyNowCsr + 1;
LABEL_34:
    v20 = wk->tgtList->pUnitL[enemyNowCsr]->pUnit;
    if (v20->para->devilid == 260)
    {
      v21 = 0;
      v11 = -1;
      while (1)
      {
        v22 = wk->UnitMng;
        if (v21 >= v22->number)
          goto LABEL_57;
        v23 = v22->pUnitL[v21]->pUnit;
        if (v23)
        {
          if (v23->para->devilid == 315)
          {
            v11 = -1;
            ListID = v21;
            goto LABEL_57;
          }
        }
        ++v21;
      }
    }
    v24 = 0;
    v11 = -1;
    while (1)
    {
      v25 = wk->UnitMng;
      if (v24 >= v25->number)
        goto LABEL_57;
      v26 = v25->pUnitL[v24]->pUnit;
      if (v26)
      {
        if (v20->ListID == v26->ListID)
        {
          v11 = -1;
          ListID = v24;
          goto LABEL_57;
        }
      }
      ++v24;
    }
    goto LABEL_34;
  }
  ListID = -1;
  v11 = -1;
LABEL_57:
  sBtlShugouKaijyo();
  if (HIDWORD(ProcessData[4].monitor) == 1)
  {
    goto LABEL_60;
  }
  ResetBtlParam();
LABEL_60:
  if (!Nakama)
    goto LABEL_106;
  if (v9 < 0)
    goto LABEL_106;
  para = Nakama->para;
  if (v9 == 149)
  {
    v30 = 0;
  }
  else
  {
    haveskill = para->haveskill;
    if (haveskill[2] == v9)
    {
      v30 = 2;
    }
    else if (haveskill[3] == v9)
    {
      v30 = 3;
    }
    else if (haveskill[4] == v9)
    {
      v30 = 4;
    }
    else if (haveskill[5] == v9)
    {
      v30 = 5;
    }
    else if (haveskill[6] == v9)
    {
      v30 = 6;
    }
    else if (haveskill[7] == v9)
    {
      v30 = 7;
    }
    else if (haveskill[8] == v9)
    {
      v30 = 8;
    }
    else if (haveskill[9] == v9)
    {
      v30 = 9;
    }
    else if (haveskill[10] == v9)
    {
      v30 = 10;
    }
    else if (haveskill[11] == v9)
    {
      v30 = 11;
    }
    else if (haveskill[12] == v9)
    {
      v30 = 12;
    }
    else if (haveskill[13] == v9)
    {
      v30 = 13;
    }
    else if (haveskill[14] == v9)
    {
      v30 = 14;
    }
    else if (haveskill[15] == v9)
    {
      v30 = 15;
    }
    else
    {
      if (haveskill[16] != v9)
        goto LABEL_106;
      v30 = 16;
    }
  }
  if (para->autoskill[v30] != 1)
  {
LABEL_106:
    aiwk = Nakama->aiwk;
    rsvSkl = aiwk->rsvSkl;
    rsvTgt = aiwk->rsvTgt;
    aiwk->rsvSkl = v9;
    aiwk->rsvTgt = ListID;
    aiwk->rsvStk = v11;
    goto LABEL_108;
  }
  v32 = Nakama->aiwk;
  v32->dfltOdrSkl = v9;
  v32->dfltOdrTgt = ListID;
  rsvSkl = v32->rsvSkl;
  rsvTgt = v32->rsvTgt;
  v32->dfltOdrStk = v11;
  v32->rsvSkl = v9;
  v32->rsvTgt = ListID;
  v32->rsvStk = v11;
  v32->RepeatOdrSkl = v9;
  v32->RepeatOdrTgt = ListID;
  v32->RepeatOdrStk = v11;
LABEL_108:
  ConfigGAME = cfgGetConfigGAME(3, 0);
  if (!ConfigGAME)
  {
    v51 = 4 * BYTE1(ProcessData[3].klass);
    v53 = (s64)GBWK->sbtl_prevSkill + v51;
    v54 = (s64)GBWK->sbtl_prevTarget + v51;
    *(u32 *)(v53 + 32) = 0;
    *(u32 *)(v54 + 32) = 0;
    v55 = Nakama->para;
    v55->prevTgtUnit = 0;
    *(u64 *)&v55->prevSkill = 0;
    if (rsvTgt != ListID)
      goto LABEL_121;
LABEL_120:
    if (rsvSkl == v9)
      goto LABEL_125;
    goto LABEL_121;
  }
  v40 = 4 * BYTE1(ProcessData[3].klass);
  v41 = GBWK;
  v43 = Nakama->para;
  v44 = (s64)v41->sbtl_prevSkill + v40;
  v45 = (s64)v41->sbtl_prevTarget + v40;
  *(u32 *)(v44 + 32) = v86 + 1;
  *(u32 *)(v45 + 32) = ListID;
  v43->prevSkill = v86 + 1;
  v43->prevTarget = ListID;
  pUnitL = wk->tgtList->pUnitL;
  v49 = pUnitL[enemyNowCsr]->pUnit;
  v43->prevTgtUnit = v49;
  if (rsvTgt == ListID)
    goto LABEL_120;
LABEL_121:
  if (Nakama->hpCallCtrl)
  {
    wk->closedOkDisp[BYTE1(ProcessData[3].klass)] = 1;
  }
LABEL_125:
  if (HIDWORD(ProcessData[4].monitor) != 1)
  {
    if ((Skilltbl->type & 0x1000) == 0)
    {
      mode = Nakama->actaiwk->mode;
      if (mode <= 0x10 && ((1 << mode) & 0x1D9FF) != 0)
      {
        sBtlResetAAI(Nakama);
        sBtlSetMotion(Nakama, 0, 4, 0, 0);
      }
    }
    Nakama->actcounter = Nakama->actcounter_max;
    Nakama->aiwk->usedSkl = 0;
    LOBYTE(ProcessData[4].monitor) = 1;
    sBtlEnd();
    sBtlMenuClose();
    Instance = get_Instance(0);
    BattleMenuClose(Instance, 0, 0);
    if (infotype == 3)
    {
      EndAnimInfo(instance, 0);
      goto LABEL_172;
    }
    v76 = get_Instance(0);
    MenuClose(v76->devil_info2, 0);
LABEL_172:
    v77 = get_Instance(0);
    CharIconCtr(v77, 0, 0);
    infotype = 0;
    devilInfo = 0;
    if (wk->closedOkDisp[BYTE1(ProcessData[3].klass)])
    {
      if (Nakama->hpCallCtrl)
      {
        OkSign(Nakama->hpCallCtrl, 0);
      }
      wk->closedOkDisp[BYTE1(ProcessData[3].klass)] = 0;
    }
    return 1;
  }
  klass_high = HIDWORD(ProcessData[5].klass);
  v58 = LODWORD(ProcessData[5].klass) + 1;
  LODWORD(ProcessData[5].klass) = v58;
  if (v58 < klass_high)
  {
    BYTE1(ProcessData[3].klass) = *((u32 *)ProcessData[5].monitor + v58 + 8);
    SetSklMenu(-1, 0);
    if (infotype == 3)
    {
      EndAnimInfo(instance, 0);
LABEL_188:
      infotype = 0;
      devilInfo = 0;
      return 1;
    }
    v82 = get_Instance(0);
    MenuClose(v82->devil_info2, 0);
    v83 = get_Instance(0);
    CharIconCtr(v83, 0, 0);
    goto LABEL_188;
  }
  LOBYTE(ProcessData[4].monitor) = 1;
  *(u16 *)wk->closedOkDisp = 0;
  v70 = sBtlGetNakama(0);
  if (v70)
  {
    hpCallCtrl = v70->hpCallCtrl;
    if (hpCallCtrl)
      OkSign(hpCallCtrl, 0);
  }
  v72 = sBtlGetNakama(1);
  if (v72)
  {
    v73 = v72->hpCallCtrl;
    if (v73)
      OkSign(v73, 0);
  }
  sBtlEnd();
  return 1;
}

// 0x1f120e0
static s32 FuncDecideSkl(void) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *monitor;
  bool Flag;
  s64 v7;
  SBTLUNIT_WORK *Nakama;
  dds3ProcessID_t *v9;
  sdatUnitWork_t *para;
  dds3ProcessID_t *v13;
  SKLID *stock_useskill;
  s32 SelectID;
  s32 area;
  s32 v21;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  monitor = ProcessData[1].monitor;
  *((u32 *)&ProcessData[6].klass->_1.byval_arg.data + BYTE1(ProcessData[3].klass)) = itfMenuGetSelectID(monitor);
  Flag = itfMenuGetFlag(ProcessData[1].monitor, 0x10000u);
  v7 = BYTE1(ProcessData[3].klass);
  if (!Flag)
    *((u32 *)ProcessData[6].monitor + v7 + 8) = -1;
  Nakama = sBtlGetNakama(v7);
  if (cfgGetConfigGAME(3, 0))
  {
    v9 = ProcessData[1].monitor;
    itfMenuGetSelectID(v9);
    para = Nakama->para;
    if (para->prevSkill)
      *((u32 *)ProcessData[6].monitor + BYTE1(ProcessData[3].klass) + 8) = para->prevTarget;
  }
  HIDWORD(ProcessData[3].monitor) = 0;
  bRikamu = 0;
  v13 = ProcessData[1].monitor;
  stock_useskill = wk->stock_useskill;
  SelectID = itfMenuGetSelectID(v13);
  area = (s16)sBtlGetSkilltbl(stock_useskill[SelectID])->area;
  if (area < 0)
  {
    SetTgtEnemy((s32)sBtlCmndMenuNew, Nakama);
    return 1;
  }
  else
  {
    v21 = *((u32 *)ProcessData[6].monitor + BYTE1(ProcessData[3].klass) + 8);
    SetTgtMenu(v21);
    return 1;
  }
}

// 0x1f12410
static void DrawFuncSkl(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *monitor;
  s32 v15;
  Il2CppObject *v16;
  s64 v18;
  sdatUnitWork_t *para;
  s32 SkillCost;
  s64 v21;
  u32 klass;
  MenuMover_t *v23;
  SBTLSKILLP_TBL *Skilltbl;
  s32 *IdList;
  s32 v26;
  bool v27;
  s64 v28;
  SBTLUNIT_WORK *pUnit;
  u32 attr;
  SBTLAISYO_DATAWORK *aisyo;
  s32 SkillIconType;
  void *Instance;
  void *spr;
  void *v37;
  void *v38;
  dds3ProcessID_t *v39;
  s32 monitor_high;
  SBTLUNIT_WORK *v43;
  u32 v44;
  u32 v46;
  s32 v47;
  s32 v48;
  SBTLSKILLP_TBL *v49;
  SBTLSKILLP_TBL *v50;
  u64 *v52;
  SBTLUNIT_WORK *v53;
  SBTLUNIT_WORK *v54;
  u64 *v55;
  SBTLUNIT_WORK *v57;
  u64 *v58;
  SBTLSKILLP_TBL *v59;
  u32 flg;
  char **v62;
  dds3ProcessID_t *v63;
  void *v64;
  u32 v66;
  u32 color;
  s32 v68;
  s32 RepeatOdrSkl;
  s32 v70;
  char *v71;
  u8 v72;
  s32 v73;
  SBTLUNIT_WORK *Nakama;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  Nakama = sBtlGetNakama(BYTE1(ProcessData[3].klass));
  monitor = ProcessData[1].monitor;
  v15 = wk->stock_useskill[a_id];
  if (itfMenuGetFlag(ProcessData[1].monitor, 0x4000u))
    return;
  v16 = dds3GetProcessData(&ProcessData[1].monitor);
  if (!v16)
  if ((wk->status2 & 2) == 0)
    return;
  v18 = a_id - *((u32 *)v16[9].monitor + 8);
  v71 = *(char **)(*(u64 *)(*((u64 *)&v16[5].klass->_1.byval_arg.data + v18) + 24) + 48);
  para = Nakama->para;
  v72 = a_alphaRate;
  SkillCost = sBtlGetSkillCost(para, v15);
  v73 = v18;
  RepeatOdrSkl = Nakama->aiwk->RepeatOdrSkl;
  v70 = SkillCost;
  v68 = *((u32 *)&v16[9].klass->_1.byval_arg.data + SBYTE4(v16[5].monitor));
  v21 = (s64)v16[5].klass + 8 * v18;
  klass = v16[13].klass;
  v23 = *(MenuMover_t *)(v21 + 32);
  color = itfGetTextColor(v23, klass);
  Skilltbl = sBtlGetSkilltbl(v15);
  IdList = itfMenuGetIdList(ProcessData[2].klass);
  v26 = datCheckSkillType(v15);
  v27 = 0;
  if (!v15 || v15 == 149)
  {
LABEL_52:
    goto LABEL_54;
  }
  if ((Skilltbl->flg & 0x200) != 0 || SLODWORD(IdList->max_length) < 1)
  {
LABEL_51:
    v27 = 0;
    goto LABEL_52;
  }
  v28 = 0;
  while (1)
  {
    pUnit = wk->UnitMng->pUnitL[v28]->pUnit;
    if (pUnit && pUnit->para->devilid != 311)
    {
      if (CheckLiveTarget(pUnit) && (pUnit->status & 0x4000000) == 0 && (pUnit->side & 2) != 0)
      {
        attr = Skilltbl->attr;
        aisyo = pUnit->para->aisyo;
        v66 = Skilltbl->attr;
        attr = v66;
        if ((sBtlCheckAisyo_Old(aisyo, attr) & 0x4000) != 0)
          break;
      }
    }
    if (++v28 >= SLODWORD(IdList->max_length))
      goto LABEL_51;
  }
  v27 = 1;
LABEL_54:
  SkillIconType = cmpGetSkillIconType(Skilltbl, v15);
  Instance = get_Instance(0);
  spr = GetSklIconSpr(Instance, SkillIconType, 0);
  v37 = get_Instance(0);
  SkillMenuDrawOne(v37, v73, v71, v70, color, v68 == a_id, v15 == RepeatOdrSkl, v27, v26 == 2, spr, BYTE1(ProcessData[3].klass), 0);
  v38 = get_Instance(0);
  MenuCusorBarCtrl(v38, HIDWORD(v16[7].monitor), *((u32 *)v16[9].monitor + 8), 0);
  v39 = ProcessData[1].monitor;
  if (itfMenuGetSelectID(v39) == a_id)
  {
    monitor_high = HIDWORD(ProcessData[4].monitor);
    v43 = Nakama;
    v44 = ChkUseSkl(v43, v15);
    if (v44 > 5)
      goto LABEL_92;
    v46 = v44;
    switch (v44)
    {
      case 0u:
      case 4u:
        v49 = sBtlGetSkilltbl(v15);
        if (monitor_high == 1 && (v49->type & 0x1000) != 0)
          goto LABEL_87;
        if (v46 - 1 < 3)
          goto LABEL_71;
        if (v46 == 4 || !v46)
        {
          v50 = sBtlGetSkilltbl(v15);
          if (v50 && (v50->type & 0x1000) != 0)
          {
            if (wk->NotCmbSkl_Cnt)
            {
              v47 = 20;
              goto LABEL_90;
            }
          }
          sBtlHelp(1, v15, v72);
        }
        break;
      case 1u:
      case 2u:
      case 3u:
LABEL_71:
        v47 = v46 - 1;
        v48 = 7;
        goto LABEL_91;
      case 5u:
LABEL_87:
        v47 = 18;
LABEL_90:
        v48 = 3;
LABEL_91:
        sBtlHelpCantUse(v48, v47, v72);
        break;
      default:
        break;
    }
LABEL_92:
    v52 = NewSpecific(SBTLUNIT_WORK, 2u);
    v53 = sBtlGetNakama(0);
    v54 = v53;
    v52[5] = v57;
    v58 = v52 + 5;
    v59 = sBtlGetSkilltbl(v15);
    if (!v59 || (v59->type & 0x1000) != 0 || (v59->area & 0x100) != 0 || (flg = v59->flg, (flg & 0x20) != 0) || v15 == 134 || v15 == 1124 || v15 == 1169 || (flg & 0x200) != 0)
    {
      v63 = ProcessData[1].monitor;
      itfMenuGetFlagMenu(v63, v73, 2u);
      if (HIDWORD(ProcessData[4].monitor) == 1 || !*v55 || !*v58)
      {
        v62 = &"BTL001";
LABEL_122:
        v64 = get_Instance(0);
        GuideSet(v64, *v62, 0, 90, 0);
        return;
      }
    }
    else
    {
      if (HIDWORD(ProcessData[4].monitor) == 1 || !*v55 || !*v58)
      {
        v62 = &"BTL020";
        goto LABEL_122;
      }
    }
    v62 = &"BTL012";
    goto LABEL_122;
  }
}

// 0x1f09db0
static SBTLCMNDMENUNEW_USETYPE ChkUseSkl(SBTLUNIT_WORK *pBtlUnit, SKLID sklId) {
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v6;
  s32 weapontype;
  sdatUnitWork_t *para;
  s32 SkillCost;
  s32 v10;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  sdatUnitWork_t *v16;
  u32 BadStatus;
  sdatUnitWork_t *v18;
  u32 v19;
  s64 k;
  SBTLUNIT_LISTWORK *v23;
  SBTLUNIT_WORK *v24;
  u16 area;
  sdatUnitWork_t *v27;
  sdatUnitWork_t *v28;
  sdatUnitWork_t *v29;
  sdatUnitWork_t *v31;
  sdatUnitWork_t *v32;
  SBATTLE_WORK *v34;
  s64 i;
  SBTLUNIT_LISTWORK *v37;
  SBTLUNIT_WORK *pUnit;
  bool v39;
  sdatUnitWork_t *v40;
  sdatUnitWork_t *v41;
  s32 v42;
  s32 v43;
  sdatUnitWork_t *StockUnitData;
  sdatUnitWork_t *v45;
  s32 devilid;
  SBTLUNIT_WORK *NakamaUnit;
  SBTLUNIT_WORK *v49;
  sdatUnitWork_t *v50;
  char v52;
  s64 j;
  SBTLUNIT_LISTWORK *v55;
  SBTLUNIT_WORK *v56;
  sdatUnitWork_t *v57;

  Skilltbl = sBtlGetSkilltbl(sklId);
  if (!Skilltbl)
    return 4;
  v6 = Skilltbl;
  if ((Skilltbl->flg2 & 0x8000000) == 0)
  {
    weapontype = Skilltbl->weapontype;
    if (weapontype)
    {
      if (weapontype != sBtlDat()->m_type)
        return 2;
    }
  }
  para = pBtlUnit->para;
  SkillCost = sBtlGetSkillCost(para, sklId);
  if ((v6->s_type & 0x20) != 0)
  {
    if (!sBtlIsUseVice(pBtlUnit, sklId))
      return 4;
    goto LABEL_19;
  }
  v10 = SkillCost;
  if (SkillCost <= wk->mag)
    goto LABEL_19;
  return 1;
LABEL_19:
  if (pBtlUnit->byctCnt > 0)
    return 3;
  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v16 = sBtlSearchUnit_ID(UnitMng, playerID)->para;
  BadStatus = sBtlGetBadStatus(v16);
  if (BadStatus <= 0xD && ((1 << BadStatus) & 0x35C0) != 0 && sklId != 116)
    return 3;
  v18 = pBtlUnit->para;
  v19 = sBtlGetBadStatus(v18);
  if (v19 <= 0x11 && (((1 << v19) & 0x371DF) != 0 || v19 == 10 && sklId != 149))
    return 3;
  if ((v6->type & 0x1000) != 0)
  {
    v34 = wk;
    if (!v34->NotCmbSkl_Cnt)
    {
      v34 = wk;
      if (!v34->NotCmbSkl_Cnt2)
      {
        v34 = wk;
        if (!v34->NotCmbSkl_Ex)
        {
          if ((v6->type & 0x1000) != 0)
          {
            for (i = 0; ; ++i)
            {
              v37 = wk->UnitMng;
              if (i >= v37->number)
                break;
              v37 = wk->UnitMng;
              pUnit = v37->pUnitL[i]->pUnit;
              if (pUnit && (pUnit->side & 2) != 0)
              {
                v39 = sBtlCheckDamageTarget(pUnit);
                if (v39 && pUnit->bYobidousa)
                  return 4;
              }
            }
            if ((v6->type & 0x1000) != 0)
            {
              for (j = 0; ; ++j)
              {
                v55 = wk->UnitMng;
                if (j >= v55->number)
                  break;
                v55 = wk->UnitMng;
                v56 = v55->pUnitL[j]->pUnit;
                if (v56 && (v56->side & 1) != 0)
                {
                  v57 = v56->para;
                  if ((sBtlGetBadStatus(v57) & 0xFFFFFFFE) == 0x10)
                    return 4;
                }
              }
            }
          }
          goto LABEL_38;
        }
      }
    }
    return 4;
  }
LABEL_38:
  for (k = 0; ; ++k)
  {
    v23 = wk->UnitMng;
    if (k >= v23->number)
      goto LABEL_122;
    v23 = wk->UnitMng;
    v24 = v23->pUnitL[k]->pUnit;
    if (!v24)
      continue;
    area = v6->area;
    if ((area & 8) != 0)
    {
      if ((~v24->side & 0x81) == 0)
      {
        v29 = v24->para;
        if (!v29->devilid)
        {
          v41 = pBtlUnit->para;
          if (SkillChkUseUnit(v24, v29, v41, sklId))
            goto LABEL_121;
          goto LABEL_122;
        }
      }
      continue;
    }
    if ((v6->area & 0x2000) != 0)
      break;
    if (v24 == pBtlUnit && (area & 0x1000) != 0)
      continue;
    if ((v6->area & 0x8000) == 0)
    {
      if ((v6->area & 0x4000) == 0)
        continue;
LABEL_56:
      if ((v24->side & 1) == 0)
        continue;
      v27 = v24->para;
      if ((v27->flag & 2) == 0)
      {
        if (v24 != sBtlGetNakama(0) && v24 != sBtlGetNakama(1))
          continue;
        v27 = v24->para;
      }
      v28 = pBtlUnit->para;
      if (SkillChkUseUnit(v24, v27, v28, sklId))
        goto LABEL_121;
      continue;
    }
    if ((v24->side & 2) != 0 && (v24->flg & 0x200) == 0)
    {
      if (CheckLiveTarget(v24))
      {
        if ((v6->flg2 & 0x1000) != 0)
        {
          if (!sBtlCheckTateSkillSelectTarget(v24))
            continue;
        }
        else
        {
          if (!sBtlCheckDamageTargetTemp(v24))
            continue;
          if (!sBtlCheckDamageTarget(v24) || (v24->flg & 2) != 0)
            continue;
        }
        v31 = v24->para;
        v32 = pBtlUnit->para;
        if (SkillChkUseUnit(v24, v31, v32, sklId))
          goto LABEL_121;
        if ((v6->area & 0x4000) != 0)
          goto LABEL_56;
      }
    }
LABEL_40:
    ;
  }
  if (v24 != pBtlUnit)
    goto LABEL_40;
  v40 = pBtlUnit->para;
  if (SkillChkUseUnit(pBtlUnit, v40, v40, sklId))
  {
LABEL_121:
    v42 = 1;
    goto LABEL_140;
  }
LABEL_122:
  if ((v6->area & 0x4020) == 0x4000)
  {
    v43 = 0;
    do
    {
      StockUnitData = sBtlGetStockUnitData(v43);
      if (StockUnitData)
      {
        v45 = StockUnitData;
        if (Exists("new_devil"))
          goto LABEL_124;
        devilid = v45->devilid;
        if (!sBtlIsDLCDevil(devilid))
        {
LABEL_124:
          NakamaUnit = sBtlGetNakamaUnit(v45);
          v49 = NakamaUnit;
          if (NakamaUnit)
            v45 = NakamaUnit->para;
          v50 = pBtlUnit->para;
          if (SkillChkUseUnit(v49, v45, v50, sklId))
            goto LABEL_121;
        }
      }
    }
    while (++v43 != 32);
  }
  v42 = 0;
LABEL_140:
  if ((v6->flg2 & 0x1000) != 0)
  {
    if (wk->tateHitCnt)
      v52 = v42;
    else
      v52 = 0;
    if ((v52 & 1) != 0)
      return 0;
    return 4;
  }
  if (!v42)
    return 4;
  return 0;
}

// 0x1f12e40
static s32 GetEnebleUseSkillNum(s32 a_nakamaNo, bool a_bCmbOut) {
  s8 v4;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v6;
  s64 v8;
  s32 v9;
  s32 v13;
  s32 v15;
  s32 v17;
  SBTLSKILLP_TBL *Skilltbl;

  v4 = a_nakamaNo;
  Nakama = sBtlGetNakama(v4);
  if (Nakama)
  {
    v6 = Nakama;
    sBtlGetSkillMenu(v6, 0x2000u);
    v8 = 0;
    v9 = 0;
    while (1)
    {
      if (v8 >= wk->stock_skillnum)
        return v9;
      v13 = wk->stock_useskill[v8];
      v15 = ChkUseSkl(v6, v13);
      if ((v15 | 4) != 4)
        goto LABEL_8;
      v17 = v15;
      Skilltbl = sBtlGetSkilltbl(v13);
      if (a_bCmbOut)
      {
        if (!(v17 | Skilltbl->type & 0x1000))
          goto LABEL_7;
      }
      else if (!v17)
      {
LABEL_7:
        ++v9;
      }
LABEL_8:
      ++v8;
    }
  }
  return 0;
}

// 0x1f0a930
static s32 MakeSkillList(dds3ProcessID_t *a_sklPID, itfMenuFunc_t a_decideFunc, itfMenuDrawFunc_t a_drawFunc, s32 a_nakamaNo, bool a_bCmbOut) {
  s8 v6;
  SBTLUNIT_WORK *Nakama;
  s64 i;
  s32 v13;
  char *v14;
  itfMenuFunc_t v15;
  itfMenuDrawFunc_t v16;
  s32 v18;
  s32 v20;
  SBTLSKILLP_TBL *Skilltbl;

  v6 = a_nakamaNo;
  Nakama = sBtlGetNakama(v6);
  itfMenuClearMenuAll(a_sklPID);
  sBtlGetSkillMenu(Nakama, 0x2000u);
  for (i = 0; ; ++i)
  {
    if (i >= wk->stock_skillnum)
      break;
    v13 = wk->stock_useskill[i];
    v14 = sdatSkillName(v13);
    v15 = Allocate(itfMenuFunc_t);
    _ctor(v15, 0, Method_Project_sBtlCmndMenuNew_FuncDecideSkl__, 0);
    itfMenuSetRootMenu(a_sklPID, i, v14, v15, "");
    v16 = Allocate(itfMenuDrawFunc_t);
    _ctor(v16, 0, Method_Project_sBtlCmndMenuNew_DrawFuncSkl__, 0);
    itfMenuSetDrawFunc(a_sklPID, i, v16, 0);
    v18 = wk->stock_useskill[i];
    v20 = ChkUseSkl(Nakama, v18);
    if ((v20 | 4) == 4)
    {
      Skilltbl = sBtlGetSkilltbl(v18);
      if (a_bCmbOut && (Skilltbl->type & 0x1000) != 0)
        v20 = 5;
    }
    itfMenuSetFlagMenu(a_sklPID, i, 2, v20 == 0);
  }
  if ((u32)i <= 4)
  {
    do
    {
      itfMenuSetRootMenu(a_sklPID, i, "", 0, "");
      itfMenuSetFlagMenu(a_sklPID, i, 1, 0);
      LODWORD(i) = i + 1;
    }
    while ((u32)i != 5);
  }
  itfMenuSetFlag(a_sklPID, 1024, 0);
  if (wk->stock_skillnum < 9)
    return 0;
  itfMenuSetDrawParam(a_sklPID, 8, 1);
  return 0;
}

// 0x1f13040
static s32 GetTabLimit(s32 *a_pmin, s32 *a_pmax) {
  s32 v6;

  if (sBtlGetStockUnitData(16))
  {
    *a_pmin = 0;
    *a_pmax = 3;
    return 0;
  }
  else
  {
    if (sBtlGetStockUnitData(8))
      v6 = 2;
    else
      v6 = 1;
    *a_pmin = 0;
    *a_pmax = v6;
    return 0;
  }
}

// 0x1f130b0
static dds3ProcessFunc_t Proc(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessFunc_t v5;
  dds3ProcessID_t *inited;
  dds3ProcessID_t *v7;
  dds3ProcessID_t *v8;
  void **p_monitor;
  dds3ProcessID_t *monitor;
  s32 SelectID;
  s32 v12;
  dds3ProcessID_t *v15;
  dds3ProcessID_t *v17;
  s32 v18;
  dds3ProcessID_t *v19;
  dds3ProcessID_t *v21;
  void *v24;
  void *v25;
  dds3ProcessID_t *v28;
  dds3ProcessID_t *v29;
  s32 v30;
  dds3ProcessID_t *v31;
  dds3ProcessID_t *v33;
  s32 v37;
  void *v38;
  void *v39;
  dds3ProcessID_t *v41;
  s32 v44;
  dds3ProcessID_t *v48;
  dds3ProcessID_t *v49;
  dds3ProcessID_t *v53;
  s32 v55;
  void *v59;
  void *Instance;
  dds3ProcessID_t *v63;
  s32 CtrlType;
  dds3ProcessID_t *v65;
  s32 klass;
  u32 *v69;
  Il2CppClass *v70;
  u32 v71;
  s32 v72;
  void *v73;
  s32 v75;
  s32 v78;
  s32 v79;
  s32 v80;
  void *v82;
  void *v83;
  s32 v84;
  s32 v86;
  void *v87;
  void *v88;
  s32 v89;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  v5 = 0;
  switch (HIDWORD(ProcessData[3].klass))
  {
    case 0:
      if (!sBtlCheckLoadFlg())
        goto LABEL_163;
      inited = sBtlInitMenuPID(5u);
      ProcessData[1].monitor = inited;
      v7 = sBtlInitMenuPID(0x20u);
      ProcessData[2].klass = v7;
      v8 = sBtlInitMenuPID(0x20u);
      ProcessData[2].monitor = v8;
      p_monitor = &ProcessData[2].monitor;
      v5 = 0;
      *((u32 *)p_monitor + 3) = 1;
      return v5;
    case 2:
      monitor = ProcessData[1].monitor;
      SelectID = itfMenuGetSelectID(monitor);
      if (SelectID == -1)
        goto LABEL_163;
      v12 = SelectID;
      if (MenuCnt < 20)
      {
        goto LABEL_21;
      }
      Instance = get_Instance(0);
      if (!MenuMoveChack(Instance, 0))
      {
        v63 = ProcessData[1].monitor;
        itfMenuSetFlag(v63, 8, 1);
        itfMenuGetFlagMenu(ProcessData[1].monitor, v12, 2u);
        CtrlType = itfMenuGetCtrlType(ProcessData[1].monitor);
        v65 = ProcessData[1].monitor;
        if (HIDWORD(ProcessData[4].monitor) == 1)
        {
          if (itfMenuGetWaitType(v65) != 4)
            goto LABEL_163;
          klass = ProcessData[5].klass;
          if (klass > 0)
          {
            v69 = ProcessData[5].monitor;
            v70 = ProcessData[6].klass;
            v71 = klass - 1;
            LODWORD(ProcessData[5].klass) = v71;
            LOBYTE(v71) = v69[v71 + 8];
            BYTE1(ProcessData[3].klass) = v71;
            v72 = *((u32 *)&v70->_1.byval_arg.data + (u8)v71);
            SetSklMenu(v72, 0);
            goto LABEL_163;
          }
          v87 = get_Instance(0);
          CloseSkillMenu(v87, ProcessData[1].monitor, 1, BYTE1(ProcessData[3].klass), 0);
          if (sBtlGetShortCutFlg())
          {
LABEL_199:
LABEL_200:
            sBtlEnd();
            goto LABEL_163;
          }
          v88 = get_Instance(0);
          v89 = 1;
        }
        else
        {
          if (itfMenuGetWaitType(v65) != 4)
          {
            if (CtrlType == 1)
            {
              if (CHECK_TRIG(4102, 1))
              {
                v82 = get_Instance(0);
                if (!MenuMoveChack(v82, 0))
                  goto LABEL_181;
              }
              if (CHECK_TRIG(4103, 1))
              {
                v83 = get_Instance(0);
                if (!MenuMoveChack(v83, 0))
                {
LABEL_181:
                  v84 = BYTE1(ProcessData[3].klass);
                  v86 = ToInt32_54962832(v84 == 0, 0);
                  if (Start_Local(v86))
                  {
                    sBtlPlaySE(0x1001Fu);
                  }
                }
              }
            }
            goto LABEL_163;
          }
          v73 = get_Instance(0);
          CloseSkillMenu(v73, ProcessData[1].monitor, 0, BYTE1(ProcessData[3].klass), 0);
          if (sBtlGetShortCutFlg())
            goto LABEL_199;
          v88 = get_Instance(0);
          v89 = 0;
        }
        BattleMenuOpen(v88, v89, 0);
        goto LABEL_200;
      }
LABEL_21:
      v15 = ProcessData[1].monitor;
      ++MenuCnt;
LABEL_23:
      itfMenuSetFlag(v15, 8, 0);
LABEL_163:
      if ((HIDWORD(ProcessData[3].klass) & 0xFFFFFFFE) != 2)
        return 0;
      v79 = ProcessData[4].klass;
      v5 = 0;
      if (v79 + 1 < 60)
        v80 = v79 + 1;
      else
        v80 = 0;
      LODWORD(ProcessData[4].klass) = v80;
      if (v80 < 0)
        HIDWORD(ProcessData[4].klass) = 0;
      else
        *((f32 *)&ProcessData[4].klass + 1) = (f32)((f32)((f32)v80 * 360.0) / -60.0) + 360.0;
      return v5;
    case 3:
      v17 = ProcessData[2].klass;
      v18 = itfMenuGetSelectID(v17);
      itfMenuGetFlagMenu(ProcessData[2].klass, v18, 2u);
      itfMenuGetCtrlType(ProcessData[2].klass);
      if (wk->modeSq)
      {
        v19 = ProcessData[2].klass;
        itfMenuSetFlag(v19, 8, 0);
        itfMenuSetFlagMenu(ProcessData[2].klass, v18, 8, 1);
        v21 = ProcessData[2].klass;
LABEL_32:
        if (itfMenuGetWaitType(v21) != 4)
          goto LABEL_163;
        if (infotype != 2)
        {
          if (infotype == 1)
            goto LABEL_38;
          v28 = ProcessData[1].monitor;
          goto LABEL_152;
        }
LABEL_38:
        v24 = get_Instance(0);
        MenuClose(v24->devil_info2, 0);
        v25 = get_Instance(0);
        CharIconCtr(v25, 0, 0);
        infotype = 0;
        v28 = ProcessData[1].monitor;
LABEL_152:
        v75 = itfMenuGetSelectID(v28);
        SetSklMenu(v75, 0);
        devilInfo = 0;
        goto LABEL_163;
      }
      if (MenuCnt > 14)
      {
        v48 = ProcessData[2].klass;
        itfMenuSetFlag(v48, 8, 1);
        itfMenuSetFlagMenu(ProcessData[2].klass, -1, 8, 0);
        v21 = ProcessData[2].klass;
        goto LABEL_32;
      }
      goto LABEL_117;
    case 4:
      v29 = ProcessData[2].monitor;
      v30 = itfMenuGetSelectID(v29);
      itfMenuGetFlagMenu(ProcessData[2].monitor, v30, 2u);
      itfMenuGetCtrlType(ProcessData[2].monitor);
      if (wk->modeSq)
      {
        v31 = ProcessData[2].monitor;
        itfMenuSetFlag(v31, 8, 0);
        itfMenuSetFlagMenu(ProcessData[2].monitor, v30, 8, 1);
        v33 = ProcessData[2].monitor;
LABEL_52:
        if (itfMenuGetWaitType(v33) != 4)
          goto LABEL_163;
        HIDWORD(ProcessData[3].monitor) = 0;
        if (!bRikamu)
        {
          SetTgtMenu(-1);
          goto LABEL_163;
        }
        v37 = infotype;
        if (v37 != 2)
        {
          if (v37 == 1)
            goto LABEL_61;
          goto LABEL_159;
        }
LABEL_61:
        v38 = get_Instance(0);
        MenuClose(v38->devil_info2, 0);
        v39 = get_Instance(0);
        CharIconCtr(v39, 0, 0);
        infotype = 0;
        bRikamu = 0;
        v41 = ProcessData[1].monitor;
LABEL_160:
        v78 = itfMenuGetSelectID(v41);
        SetSklMenu(v78, 0);
        devilInfo = 0;
        goto LABEL_163;
LABEL_159:
        bRikamu = 0;
        v41 = ProcessData[1].monitor;
        goto LABEL_160;
      }
      if (MenuCnt <= 14)
      {
LABEL_117:
        v15 = ProcessData[2].klass;
        MenuCnt = MenuCnt + 1;
        goto LABEL_23;
      }
      v49 = ProcessData[2].monitor;
      itfMenuSetFlag(v49, 8, 1);
      itfMenuSetFlagMenu(ProcessData[2].monitor, -1, 8, 0);
      v33 = ProcessData[2].monitor;
      goto LABEL_52;
    case 5:
      v44 = MenuCnt;
      if (v44 > 14)
      {
        if (!CHECK_TRIG(4097, 1))
          goto LABEL_111;
        goto LABEL_93;
      }
      v44 = MenuCnt;
      MenuCnt = v44 + 1;
      if (!CHECK_TRIG(4097, 1))
      {
LABEL_111:
        if ((wk->status & 0x80000) != 0)
        {
          TgtEnemySel();
        }
        goto LABEL_163;
      }
LABEL_93:
      if (!wk->modeSq)
      {
        if (MenuCnt >= 10)
        {
          if (!orderMenuCtrl)
          {
            SE(1);
            v53 = ProcessData[1].monitor;
            v55 = itfMenuGetSelectID(v53);
            SetSklMenu(v55, 0);
            wk->status &= ~0x80000u;
            v59 = get_Instance(0);
            CloseHuumaInfo(v59, 0);
          }
        }
      }
      goto LABEL_111;
    case 6:
      v5 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v5, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v5;
    default:
      return v5;
  }
}

// 0x1f13f20
static void Shutdown(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *v5;
  Il2CppClass *klass;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass = ProcessData[1].klass;
  v5 = &ProcessData[1];
  if (klass)
  {
    dds3KillProcess(v5, 0);
    v5 = 0;
  }
}

// 0x1f14040
static dds3ProcessFunc_t DrawProc(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 klass_high;
  s32 v6;
  s32 v8;
  s32 v9;
  s8 v10;
  SBTLUNIT_WORK *v11;
  SBTLUNIT_WORK *v12;
  sprHandle_t *hPanelSpr3;
  s32 v15;
  char *a_str;
  void *v17;
  char *v18;
  void *v20;
  u8 v21;
  s8 v22;
  SBTLUNIT_WORK *Nakama;
  SKLID *stock_useskill;
  dds3ProcessID_t *monitor;
  s32 v27;
  s32 devilid;
  char *v29;
  void *Instance;
  SBTLUNIT_WORK *v31;
  char *v32;
  char *v33;
  void *v34;
  char *v35;
  s32 v36;
  s32 v37;
  s32 v38;
  f32 v40;
  f32 v41;
  s32 v43;
  dds3ProcessID_t *p_monitor;
  dds3ProcessID_t *v46;
  dds3ProcessID_t *v47;
  void *v49;
  u8 v50;
  s8 v51;
  SBTLUNIT_WORK *v52;
  SKLID *v54;
  dds3ProcessID_t *v55;
  s32 v56;
  s32 v57;
  char *v58;
  void *v59;
  SBTLUNIT_WORK *v60;
  char *v61;
  char *v62;
  void *v63;
  char *v64;
  s32 v65;
  s32 v66;
  s32 v67;
  f32 v69;
  f32 v70;
  s32 v72;
  dds3ProcessID_t *v74;
  dds3ProcessID_t *v75;
  Il2CppClass *klass;
  void *v78;
  s32 monitor_high;
  dds3ProcessID_t *v80;
  s32 v81;
  Il2CppClass *v82;
  SBTLUNIT_WORK *v84;
  SBTLUNIT_WORK *v85;
  sprHandle_t *v87;
  s32 v88;
  char *v89;
  void *v90;
  char *v91;
  dds3ProcessID_t *id;
  sdfColor_t v94;
  sdfColor_t v95;
  sdfColor_t v96;
  sdfColor_t v97;
  sdfColor_t v98;
  sdfColor_t v99;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass_high = HIDWORD(ProcessData[3].klass);
  if (klass_high == 4)
  {
    v21 = BYTE1(ProcessData[3].klass);
    v22 = ToSByte_54969888(v21, 0);
    Nakama = sBtlGetNakama(v22);
    stock_useskill = wk->stock_useskill;
    monitor = ProcessData[1].monitor;
    v27 = stock_useskill[itfMenuGetSelectID(monitor)];
    itfDrawMiscSpriteAlpha(300, 90, 0, 0xFFu, wk->panelwk->hPanelSpr3, 11, 108);
    itfDrawMiscSpriteAlpha(420, 91, 0, 0xFFu, wk->panelwk->hPanelSpr3, 15, 108);
    devilid = sBtlGetNakama(BYTE1(ProcessData[3].klass))->para->devilid;
    v29 = sdatDevilName(devilid, 0);
    itfDrawFont(0, 320, 98, 0x100000, 0, 0, 0xA0A0A0A0, 1.0, 109, v29);
    Instance = get_Instance(0);
    v31 = sBtlGetNakama(BYTE1(ProcessData[3].klass));
    v32 = sdatDevilName(v31->para->devilid, 0);
    v95.r = 1.0;
    v95.g = 1.0;
    v95.b = 1.0;
    v95.a = 1.0;
    DevilSelectText(Instance, v32, v95, 0);
    itfDrawMiscSpriteAlpha(341, 110, 0, 0xFFu, wk->panelwk->hPanelSpr3, 11, 108);
    itfDrawMiscSpriteAlpha(485, 111, 0, 0xFFu, wk->panelwk->hPanelSpr3, 15, 108);
    v33 = sdatSkillName(v27);
    itfDrawFont(0, 361, 118, 0x100000, 0, 0, 0xA0A0A0A0, 1.0, 109, v33);
    v34 = get_Instance(0);
    v35 = sdatSkillName(v27);
    v96.r = 1.0;
    v96.g = 1.0;
    v96.b = 1.0;
    v96.a = 1.0;
    SkillSelectText(v34, v35, v96, 0);
    DrawRepeatIconEx((s32)sBtlCmndMenuNew, v36, v37, v40, v41, v38, Nakama, v27);
    if (sBtlGetStockUnitData(16))
    {
      v43 = 3;
      if (!BYTE1(ProcessData[3].monitor))
        goto LABEL_43;
    }
    else
    {
      if (sBtlGetStockUnitData(8))
        v43 = 2;
      else
        v43 = 1;
      if (!BYTE1(ProcessData[3].monitor))
      {
LABEL_43:
        v47 = ProcessData[2].monitor;
        p_monitor = &ProcessData[2].monitor;
        v46 = v47;
        goto LABEL_44;
      }
    }
    monitor_high = HIDWORD(ProcessData[3].monitor);
    sBtlDrawTabPanelCharList(0, v43, monitor_high, 0, 1.0);
    v80 = ProcessData[2].monitor;
    p_monitor = &ProcessData[2].monitor;
    v46 = v80;
LABEL_44:
    itfMenuSetDrawParam(v46, 8, 1);
    dds3GetProcessData(p_monitor);
    v49 = get_Instance(0);
    StockMenuDraw(v49, p_monitor, v27, 0);
    return 0;
  }
  if (klass_high == 3)
  {
    v50 = BYTE1(ProcessData[3].klass);
    v51 = ToSByte_54969888(v50, 0);
    v52 = sBtlGetNakama(v51);
    v54 = wk->stock_useskill;
    v55 = ProcessData[1].monitor;
    v56 = v54[itfMenuGetSelectID(v55)];
    itfDrawMiscSpriteAlpha(300, 90, 0, 0xFFu, wk->panelwk->hPanelSpr3, 11, 108);
    itfDrawMiscSpriteAlpha(420, 91, 0, 0xFFu, wk->panelwk->hPanelSpr3, 15, 108);
    v57 = sBtlGetNakama(BYTE1(ProcessData[3].klass))->para->devilid;
    v58 = sdatDevilName(v57, 0);
    itfDrawFont(0, 320, 98, 0x100000, 0, 0, 0xA0A0A0A0, 1.0, 109, v58);
    v59 = get_Instance(0);
    v60 = sBtlGetNakama(BYTE1(ProcessData[3].klass));
    v61 = sdatDevilName(v60->para->devilid, 0);
    v97.r = 1.0;
    v97.g = 1.0;
    v97.b = 1.0;
    v97.a = 1.0;
    DevilSelectText(v59, v61, v97, 0);
    itfDrawMiscSpriteAlpha(341, 110, 0, 0xFFu, wk->panelwk->hPanelSpr3, 11, 108);
    itfDrawMiscSpriteAlpha(485, 111, 0, 0xFFu, wk->panelwk->hPanelSpr3, 15, 108);
    v62 = sdatSkillName(v56);
    itfDrawFont(0, 361, 118, 0x100000, 0, 0, 0xA0A0A0A0, 1.0, 109, v62);
    v63 = get_Instance(0);
    v64 = sdatSkillName(v56);
    v98.r = 1.0;
    v98.g = 1.0;
    v98.b = 1.0;
    v98.a = 1.0;
    SkillSelectText(v63, v64, v98, 0);
    DrawRepeatIconEx((s32)sBtlCmndMenuNew, v65, v66, v69, v70, v67, v52, v56);
    if (sBtlGetStockUnitData(16))
    {
      v72 = 3;
      if (!BYTE1(ProcessData[3].monitor))
        goto LABEL_61;
    }
    else
    {
      if (sBtlGetStockUnitData(8))
        v72 = 2;
      else
        v72 = 1;
      if (!BYTE1(ProcessData[3].monitor))
      {
LABEL_61:
        klass = ProcessData[2].klass;
        v74 = &ProcessData[2];
        v75 = klass;
        goto LABEL_62;
      }
    }
    v81 = HIDWORD(ProcessData[3].monitor);
    sBtlDrawTabPanelCharList(0, v72, v81, 0, 1.0);
    v82 = ProcessData[2].klass;
    v74 = &ProcessData[2];
    v75 = v82;
LABEL_62:
    itfMenuSetDrawParam(v75, 8, 1);
    dds3GetProcessData(v74);
    v78 = get_Instance(0);
    TargetMenuDraw(v78, v74, v56, 0);
    return 0;
  }
  if (klass_high != 2)
    return 0;
  if (HIDWORD(ProcessData[4].monitor) != 1)
  {
    v6 = BYTE1(ProcessData[3].klass);
    v8 = ToInt32_54962832(v6 == 0, 0);
    if (sBtlIsStart(v8))
    {
      v9 = BYTE1(ProcessData[3].klass);
      v10 = ToSByte_54962192(v9 == 0, 0);
      v11 = sBtlGetNakama(v10);
      if (!v11)
        goto LABEL_90;
      v12 = v11;
      hPanelSpr3 = wk->panelwk->hPanelSpr3;
      itfDrawMiscSpriteAlpha(365, 110, 0, 0xFFu, hPanelSpr3, 11, 108);
      itfDrawMiscSpriteAlpha(485, 111, 0, 0xFFu, wk->panelwk->hPanelSpr3, 15, 108);
      v15 = v12->para->devilid;
      a_str = sdatDevilName(v15, 0);
      itfDrawFont(0, 385, 118, 0x100000, 0, 0, 0x80808080, 1.0, 109, a_str);
      v17 = get_Instance(0);
      v18 = sdatDevilName(v12->para->devilid, 0);
      v94.r = 0.5;
      v94.a = 1.0;
      v20 = v17;
      goto LABEL_89;
    }
    v20 = get_Instance(0);
    v94.r = 0.5;
    v94.a = 1.0;
    v18 = 0;
LABEL_89:
    v94.g = v94.r;
    v94.b = v94.r;
    DevilUnSelectText(v20, v18, v94, 0);
  }
LABEL_90:
  v84 = sBtlGetNakama(BYTE1(ProcessData[3].klass));
  if (v84)
  {
    v85 = v84;
    v87 = wk->panelwk->hPanelSpr3;
    itfDrawMiscSpriteAlpha(300, 90, 0, 0xFFu, v87, 11, 108);
    itfDrawMiscSpriteAlpha(420, 91, 0, 0xFFu, wk->panelwk->hPanelSpr3, 15, 108);
    v88 = v85->para->devilid;
    v89 = sdatDevilName(v88, 0);
    itfDrawFont(0, 320, 98, 0x100000, 0, 0, 0xA0A0A0A0, 1.0, 109, v89);
    v90 = get_Instance(0);
    v91 = sdatDevilName(v85->para->devilid, 0);
    v99.r = 1.0;
    v99.g = 1.0;
    v99.b = 1.0;
    v99.a = 1.0;
    DevilSelectText(v90, v91, v99, 0);
  }
  return 0;
}

// 0x1f14d20
void sBtlInit(void) {
  S_CmndMenuNew *v1;
  dds3ProcessFunc_t v3;
  shutdownfuncDelegate v4;
  dds3ProcessID_t *started;
  dds3ProcessFunc_t v7;
  dds3ProcessID_t *v8;
  s64 i;
  char *v11;
  s32 *sbtl_prevTarget;

  v1 = Allocate(S_CmndMenuNew);
  _ctor(v1);
  v3 = Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_sBtlCmndMenuNew_Proc__, 0);
  v4 = Allocate(shutdownfuncDelegate);
  _ctor(v4, 0, Method_Project_sBtlCmndMenuNew_Shutdown__, 0);
  started = dds3StartProcess("CmndMenu", 1023, 0, 0, v3, v4, v1);
  g_mainPID = started;
  v7 = Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_sBtlCmndMenuNew_DrawProc__, 0);
  v8 = dds3StartProcess("CmndMenuDraw", 11029, 0, 0, v7, 0, v1);
  v1->drawPID = v8;
  for (i = 0; ; ++i)
  {
    sbtl_prevTarget = GBWK->sbtl_prevTarget;
    if (i >= SLODWORD(sbtl_prevTarget->max_length))
      break;
    sbtl_prevTarget = GBWK->sbtl_prevTarget;
    v11 = (char *)sbtl_prevTarget + 4 * i;
    *((u32 *)v11 + 8) = 0;
  }
  v1->step = 0;
}

// 0x1f15060
void Delete(void) {
  Il2CppObject *ProcessData;
  void **p_monitor;
  dds3ProcessID_t *monitor;
  Il2CppObject *v8;
  void **v9;
  dds3ProcessID_t *v10;

  if (!dds3ExistProcess(g_mainPID))
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  p_monitor = &ProcessData[1].monitor;
  monitor = ProcessData[1].monitor;
  HIDWORD(ProcessData[3].klass) = 6;
  itfMenuProcessEnd(monitor);
  v8 = ProcessData + 2;
  itfMenuProcessEnd(ProcessData[2].klass);
  v10 = ProcessData[2].monitor;
  v9 = &ProcessData[2].monitor;
  itfMenuProcessEnd(v10);
  *(v9 - 2) = 0;
  v8->klass = 0;
  *v9 = 0;
}

// 0x1f0af60
bool sBtlIsStart(s32 mode) {
  s8 v2;
  SBTLUNIT_WORK *Nakama;
  Il2CppObject *ProcessData;

  v2 = mode;
  Nakama = sBtlGetNakama(v2);
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  if (!Nakama)
    return 0;
  if (!CheckLiveTarget(Nakama))
    return 0;
  if (sBtlCheckReturn_Unit(Nakama))
    return 0;
  return (u32)(HIDWORD(ProcessData[3].klass) - 1) < 2;
}

// 0x1f15270
bool sBtlStart(s32 com_smn_idx) {
  S_CmndMenuNew *ProcessData;
  s32 *sklNo;
  s32 *tgtNo;
  S_CmndMenuNew *v9;

  ProcessData = GetProcessData();
  if (!ProcessData)
    return (char)ProcessData;
  sklNo = ProcessData->sklNo;
  tgtNo = ProcessData->tgtNo;
  ProcessData->type = 0;
  v9 = ProcessData;
  sklNo[0] = -1;
  tgtNo[0] = -1;
  sklNo[1] = -1;
  tgtNo[1] = -1;
  *(u64 *)&ProcessData->cntLoop = 0x100000000LL;
  if (com_smn_idx == -1)
  {
    if (Start_Local(0))
      goto LABEL_19;
    if (Start_Local(1))
      goto LABEL_19;
    LOBYTE(ProcessData) = 0;
    return (char)ProcessData;
  }
  if (Start_Local(com_smn_idx))
    goto LABEL_19;
  LOBYTE(ProcessData) = 0;
  return (char)ProcessData;
LABEL_19:
  v9->bDecide = 0;
  if (IsSceanStop())
  {
    v9->bCallStopBattle = 0;
    LOBYTE(ProcessData) = 1;
    return (char)ProcessData;
  }
  StopBattle();
  v9->bCallStopBattle = 1;
  sBtlMenuOpen();
  LOBYTE(ProcessData) = 1;
  return (char)ProcessData;
}

// 0x1f15480
bool sBtlStartBattle1st(void) {
  S_CmndMenuNew *ProcessData;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v4;
  char v6;
  u32 v7;
  SBTLUNIT_WORK *v8;
  SBTLUNIT_WORK *v11;
  s32 v13;
  s32 *tgtNo;
  s32 *sklNo;
  s32 *index;
  s32 v20;
  char v22;

  ProcessData = GetProcessData();
  ProcessData->index[0] = -1;
  Nakama = sBtlGetNakama(0);
  if (!Nakama)
  {
LABEL_15:
    v7 = 0;
    v6 = 1;
    ProcessData->index[1] = -1;
    v8 = sBtlGetNakama(1);
    if (!v8)
      goto LABEL_24;
    goto LABEL_16;
  }
  v4 = Nakama;
  if (!CheckLiveTarget(Nakama))
    goto LABEL_15;
  if (!GetEnebleUseSkillNum(0, 0))
    goto LABEL_15;
  v6 = 0;
  v7 = 1;
  ProcessData->index[0] = 0;
  ProcessData->index[1] = -1;
  v8 = sBtlGetNakama(1);
  if (!v8)
    goto LABEL_24;
LABEL_16:
  v11 = v8;
  if (!CheckLiveTarget(v8))
    goto LABEL_24;
  if (GetEnebleUseSkillNum(1, 0))
  {
    ProcessData->index[v7] = 1;
    v13 = v7 + 1;
    goto LABEL_27;
  }
LABEL_24:
  if ((v6 & 1) != 0)
    return 0;
  v13 = 1;
LABEL_27:
  ProcessData->type = 1;
  sklNo = ProcessData->sklNo;
  tgtNo = ProcessData->tgtNo;
  index = ProcessData->index;
  sklNo[0] = -1;
  tgtNo[0] = -1;
  sklNo[1] = -1;
  tgtNo[1] = -1;
  ProcessData->cntLoop = 0;
  ProcessData->maxLoop = v13;
  v20 = index[0];
  Start_Local(v20);
  ProcessData->bDecide = 0;
  goto LABEL_29;
LABEL_33:
  StopBattle();
  v22 = 1;
  goto LABEL_36;
LABEL_29:
  if (!IsSceanStop())
    goto LABEL_33;
  v22 = 0;
LABEL_36:
  ProcessData->bCallStopBattle = v22;
  return 1;
}

// 0x1f15740
s32 sBtlGetStat(void) {
  S_CmndMenuNew *ProcessData;
  s32 step;

  ProcessData = GetProcessData();
  if (!ProcessData)
    return (s32)ProcessData;
  step = ProcessData->step;
  if (step == 1)
  {
    LODWORD(ProcessData) = 1;
  }
  else if (step == 6)
  {
    LODWORD(ProcessData) = 3;
  }
  else
  {
    LODWORD(ProcessData) = 2;
  }
  return (s32)ProcessData;
}

// 0x1f157e0
bool sBtlChkDecide(void) {
  S_CmndMenuNew *ProcessData;

  ProcessData = GetProcessData();
  if (ProcessData)
    LOBYTE(ProcessData) = ProcessData->bDecide;
  return (char)ProcessData;
}

// 0x1f0b730
void sBtlDrawRepeatIcon(s32 a_x, s32 a_y, s32 a_z, f32 a_angle, f32 a_alphaRate, DDS3_OT a_otNo, bool a_bRepeat, bool a_bRepeatOrder) {
  ;
}

// 0x1f15860
SBTLUNIT_WORK *sBtlGetActionUnit(void) {
  S_CmndMenuNew *ProcessData;
  u32 mode;

  ProcessData = GetProcessData();
  if (!ProcessData)
    return 0;
  mode = ProcessData->mode;
  if (mode <= 1)
    return sBtlGetNakama(mode);
  return 0;
}

// 0x1f158f0
SBTLUNIT_WORK *GetTargetUnit(void) {
  SBTLUNIT_WORK *result;
  SBTLUNIT_WORK *v4;
  dds3ProcessID_t *v5;
  bool v6;
  f32 y;
  u32 enemyNowCsr_local;
  SBTLUNIT_LISTWORK *tgtList;
  SBTLUNIT_LISTWORK *p_tgtList;
  dds3ProcessID_t *v14;

  result = (SBTLUNIT_WORK *)GetProcessData();
  if (!result)
    return result;
  v4 = result;
  if (LOBYTE(result->vPosBfrCmb.z))
    return 0;
  v5 = *(dds3ProcessID_t *)&result->vPosCmbMov1.x;
  v6 = itfMenuProcessCheck(*(dds3ProcessID_t *)&result->vPosCmbMov1.x);
  result = 0;
  if (!v6)
    return result;
  y = v4->vPosBfrCmb.y;
  if (LODWORD(y) != 3)
  {
    if (LODWORD(y) != 5)
      return 0;
    enemyNowCsr_local = enemyNowCsr;
    if ((enemyNowCsr_local & 0x80000000) != 0)
      return 0;
    tgtList = wk->tgtList;
    if (!tgtList)
      return 0;
    return tgtList->pUnitL[enemyNowCsr_local]->pUnit;
LABEL_30:
    tgtList = p_tgtList;
    return tgtList->pUnitL[enemyNowCsr_local]->pUnit;
  }
  v14 = *(dds3ProcessID_t *)&v4->vPosCmbMov1.x;
  enemyNowCsr_local = itfMenuGetSelectID(v14);
  result = 0;
  if ((enemyNowCsr_local & 0x80000000) == 0 && enemyNowCsr_local != 99)
  {
    p_tgtList = &wk->UnitMng;
    goto LABEL_30;
  }
  return result;
}
