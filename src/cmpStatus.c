#include "types.h"
#include "CMP_SPR.h"
#include "CMP_STATUS_MODE.h"
#include "CMP_STATUS_TYPE.h"
#include "SBTL_MENU_ID.h"
#include "SKLID.h"
#include "SkillIcon.h"
#include "UiParType.h"
#include "buttonguide.h"
#include "cmp.h"
#include "cmpfile.h"
#include "cmpitem.h"
#include "cmpmain.h"
#include "cmpmap.h"
#include "cmpmisc.h"
#include "cmpmodel.h"
#include "cmpomoide.h"
#include "cmpraidouskill.h"
#include "cmpstatus.h"
#include "cmpstatusitmsklset.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3effect_blend.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3padmanager.h"
#include "dds3vrf.h"
#include "ditectivebook.h"
#include "evtbit.h"
#include "evtmoon.h"
#include "fclmisc.h"
#include "fclmsg.h"
#include "fld.h"
#include "frname.h"
#include "gohcalc.h"
#include "gohcombunity.h"
#include "gohdraw.h"
#include "interface.h"
#include "itf.h"
#include "kernel.h"
#include "libsdf.h"
#include "localize.h"
#include "raijindlc.h"
#include "rstgrowth.h"
#include "rstresultdraw.h"
#include "sbtl.h"
#include "sbtlcalc.h"
#include "sbtlcmndmenunew.h"
#include "sbtldraw.h"
#include "sbtlmain.h"
#include "sbtlskill.h"
#include "sbtlsub.h"
#include "sbtlweapon.h"
#include "scr.h"
#include "sdat.h"
#include "sdf_vu0.h"
#include "sndat3.h"
#include "sndmanager.h"
#include "tips.h"

#define D_BTLSKLSETSE 1
#define D_BTLSKLRESETSE 1
#define D_TABMOVESE 24
#define SKL_DRAW_MAX_NUM 8
#define SOUSA_SKL_DRAW_MAX_NUM 2
#define MOVE_SWORD_WAIT 8
#define P_SYOUGOU_MAX 76
#define CMP_STATUS_MAINPROC_NAME "camp_status_main"
#define CMP_STATUS_DRAWPROC_NAME "camp_status_draw"
#define ANALOG_LIMEN 64
#define OMOIDEIPPAI_X 285
#define OMOIDEIPPAI_Y 265
#define CMPSTATUS_HELPTEXT_X 18
#define CMPSTATUS_HELPTEXT_Y 383
#define SUTEHELP_X 18
#define SUTEHELP_Y 344
#define D_MEMSKLLIST_X 1
#define D_MEMSKLLIST_Y 8
#define D_MEMSKLLIST_XY 8
#define CMP_STATUS_DEFAULT_OT 108
#define LIGHT_PAR_NO_DRAW_CNT 1.1
#define ADD_RANK_OFS 100
#define DLC_RANK_OFS 1000
#define DLC_REMOVE_SET 5
#define SKIP_SPEED 3

typedef enum {
    CMPSTATUS_ITM_SKL_STEP_WAIT = 0,
    CMPSTATUS_ITM_SKL_STEP_LOADING = 1,
    CMPSTATUS_ITM_SKL_STEP_OMO_CHG = 2,
    CMPSTATUS_ITM_SKL_STEP_OMO_CHG_WAIT = 3,
    CMPSTATUS_ITM_SKL_STEP_SKL_SET = 4,
    CMPSTATUS_ITM_SKL_STEP_CALL_MSG = 5,
    CMPSTATUS_ITM_SKL_STEP_WAIT_MSG = 6,
    CMPSTATUS_ITM_SKL_STEP_DONE_MSG = 7,
    CMPSTATUS_ITM_SKL_STEP_DONE_MSG_WAIT = 8,
    CMPSTATUS_ITM_SKL_STEP_ENDWAIT = 9,
    CMPSTATUS_ITM_SKL_STEP_END = 10,
} CMPSTATUS_ITM_SKL_STEP;

typedef enum {
    CMP_STATUS_PARAM_NUM = 4,
} CMP_STATUS_PARAM;

typedef enum {
    RaidouSklMenu_Katana = 0,
    RaidouSklMenu_Spirit = 1,
    RaidouSklMenu_Max = 2,
    RaidouSklMenu_None = 3,
} RaidouSklMenu;

typedef enum {
    CommandSet_DVL1_COMB1 = 0,
    CommandSet_DVL1_COMB2 = 1,
    CommandSet_DVL2_COMB1 = 2,
    CommandSet_DVL2_COMB2 = 3,
    CommandSet_MAX = 4,
} CommandSet;

typedef enum {
    CMPSTATUS_GOODBY_STEP_WAIT = 0,
    CMPSTATUS_GOODBY_STEP_LOADING = 1,
    CMPSTATUS_GOODBY_STEP_ENTER = 2,
    CMPSTATUS_GOODBY_STEP_MESSAGE = 3,
    CMPSTATUS_GOODBY_STEP_TURN = 4,
    CMPSTATUS_GOODBY_STEP_RUNAWAY = 5,
    CMPSTATUS_GOODBY_STEP_ENDWAIT = 6,
    CMPSTATUS_GOODBY_STEP_END = 7,
} CMPSTATUS_GOODBY_STEP;

typedef enum {
    CMPSTATUS_DVLREPORT_STEP_WAIT = 0,
    CMPSTATUS_DVLREPORT_STEP_LOADING = 1,
    CMPSTATUS_DVLREPORT_STEP_ENTER = 2,
    CMPSTATUS_DVLREPORT_STEP_MESSAGE = 3,
    CMPSTATUS_DVLREPORT_STEP_ENDWAIT = 4,
    CMPSTATUS_DVLREPORT_STEP_END = 5,
} CMPSTATUS_DVLREPORT_STEP;

typedef enum {
    CMP_STATUS_STEP2_START = 0,
    CMP_STATUS_STEP2_FADEIN = 1,
    CMP_STATUS_STEP2_CALL_MSG = 2,
    CMP_STATUS_STEP2_WAIT_MSG = 3,
    CMP_STATUS_STEP2_CALL_PARAM_IN = 4,
    CMP_STATUS_STEP2_SET_PARAM = 5,
    CMP_STATUS_STEP2_CONF = 6,
    CMP_STATUS_STEP2_CALL_PARAM_OUT = 7,
    CMP_STATUS_STEP2_SKILL_C_MSG_INIT = 8,
    CMP_STATUS_STEP2_SKILL_C_MSG_WAIT = 9,
    CMP_STATUS_STEP2_SKILL_A_MSG_INIT = 10,
    CMP_STATUS_STEP2_SKILL_A_MSG_WAIT = 11,
    CMP_STATUS_STEP2_SKILL_ITEM_NML_INIT = 12,
    CMP_STATUS_STEP2_SKILL_ITEM_NML_WAIT = 13,
    CMP_STATUS_STEP2_SKILL_ITEM_OMO_INIT = 14,
    CMP_STATUS_STEP2_SKILL_ITEM_OMO_WAIT = 15,
    CMP_STATUS_STEP2_RECOVER_CALL = 16,
    CMP_STATUS_STEP2_RECOVER_WAIT = 17,
    CMP_STATUS_STEP2_WAIT = 18,
    CMP_STATUS_STEP2_VIEWER = 19,
    CMP_STATUS_STEP2_CHANGE = 20,
    CMP_STATUS_STEP2_END = 21,
} CMP_STATUS_STEP2;

typedef struct CmpBasePartsSet CmpBasePartsSet;
typedef struct CmpStatusGaugeSet CmpStatusGaugeSet;
typedef struct CmpStatusPartsPassPar CmpStatusPartsPassPar;
typedef struct RankText RankText;
typedef struct SBTLSKILLP_TBL SBTLSKILLP_TBL;
typedef struct cmpStatusCur_t cmpStatusCur_t;
typedef struct cmpSummnerRankMng_t cmpSummnerRankMng_t;
typedef struct cmpSummnerRank_t cmpSummnerRank_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct itfSprList_t itfSprList_t;
typedef struct sdatPlayerUnitWork_t sdatPlayerUnitWork_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;
typedef struct sprHandle_t sprHandle_t;
typedef struct tagCMP_STATUS_WORK tagCMP_STATUS_WORK;
typedef struct tagOBJECT_WORK tagOBJECT_WORK;

s32 lastBasePar[4];
s32 *lastOrangePar;
CmpStatusPartsPassPar *passPar;
SBTL_MENU_ID *commandTbl;
char *cmdHelpText;
s32 *btlCommandSetParTbl;
char *rankText;
char *rankText2;
char *dlcRankText;
dds3ProcessID_t *g_mainPID;
dds3ProcessID_t *g_guidePID;
f32 *pos;
f32 *rot;
s32 aGoodbyCnt;
s32 aColorCnt;
f32 s_cmpRaidoFlushCntf;
s16 **arrSwordNameLv;
SDF_PADMAP *viewerNoPress;
s32 **arrPlayerRank;
s32 **arrPlayerRankDlc;

// 0x2098110
void StatusSceneActive(bool _active) {
  Il2CppObject *Instance;
  void *gameObject;
  Il2CppObject *v5;
  void *v6;
  bool StartStatusFlag;
  Il2CppObject *v9;

  Instance = _get_Instance();
  if (active)
  {
    gameObject = get_gameObject(Instance, 0);
    if (!get_activeSelf(gameObject, 0))
    {
      v5 = _get_Instance();
      UiLoad(v5, 0);
      ButtonLineHelpDispSet(0);
      v6 = *((void *)_get_Instance()[7].monitor + 2);
      if (get_activeSelf(v6, 0))
        SetActive(v6, 0, 0);
    }
    StartStatusFlag = cmpGetStartStatusFlag();
    v9 = _get_Instance();
    CallStart(v9, 1, !StartStatusFlag, 0);
  }
  else
  {
    CallEnd(Instance, 0);
  }
}

// 0x2098390
void cmpLastParClear(void) {
  s64 i;
  char *v3;
  s64 j;
  char *v6;

  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(lastOrangePar->max_length))
      break;
    v3 = (char *)lastOrangePar + 4 * i;
    *((u32 *)v3 + 8) = -1;
  }
  for (j = 0; ; ++j)
  {
    if (j >= SLODWORD(lastBasePar->max_length))
      break;
    v6 = (char *)lastBasePar + 4 * j;
    *((u32 *)v6 + 8) = -1;
  }
}

// 0x2098490
s32 StatusSkillCheck(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  s32 ModeSq;
  bool v12;
  f32 v21;
  unsigned __int128 v30;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (ProcessData)
  {
    v4 = ProcessData;
    v4[3].klass = &loc_11B0000;
    v30 = 0u;
    ModeSq = cmpGetModeSq();
    if (ModeSq != 2)
    {
      if (ModeSq != 1)
      {
        if (!ModeSq)
        {
          if (LOBYTE(v4[2].klass) != 19)
          {
            if (CHECK_TRIG(4104, 1))
            {
LABEL_15:
              cmpSklTypeSub();
              goto LABEL_77;
            }
            if (CHECK_TRIG(4107, 1))
              goto LABEL_44;
            if (CHECK_TRIG(45314, 1))
              goto LABEL_53;
            if (CHECK_TRIG(41741, 1))
            {
              if (!cmpGetModeSq() && (BYTE1(v4[1].monitor) & 0x40) != 0)
              {
                if (cmpCheckHandle())
                {
                  cmpGetPos(&v30);
                  v21 = *(f32 *)&v30;
                  *(void **)((char *)&v4[17].monitor + 4) = 0;
                  HIDWORD(v4[2].monitor) = 2;
                  LOBYTE(v4[2].klass) = 20;
                  *(f32 *)&v4[17].monitor = (f32)(0.0 - v21) / 10.0;
                }
              }
            }
          }
        }
        goto LABEL_77;
      }
      cmpCmpGuideSet(26, 0, 90);
      if (CHECK_TRIG(4, 1) || CHECK_REP(4100, 1))
      {
        cmpSklCsrU();
        goto LABEL_77;
      }
      if (CHECK_TRIG(4101, 1) || CHECK_REP(4101, 1))
      {
        cmpSklCsrD();
        goto LABEL_77;
      }
      if (CHECK_TRIG(4102, 1) || CHECK_REP(4102, 1))
      {
        cmpSklCsrL();
        goto LABEL_77;
      }
      if (CHECK_TRIG(4103, 1) || CHECK_REP(4103, 1))
      {
        cmpSklCsrR();
        goto LABEL_77;
      }
      if (cmpSetSkillNow())
        goto LABEL_77;
      if (cmpChgSkillNow())
      {
LABEL_77:
        if (cmpChgSkillNow())
        {
          cmpSklChangeUpdate(v4);
          return ModeSq;
        }
        return ModeSq;
      }
      if (CHECK_TRIG(4104, 1))
        goto LABEL_15;
      if (CHECK_TRIG(4107, 1))
      {
LABEL_44:
        cmpSklTypeAdd();
        goto LABEL_77;
      }
      if (CHECK_TRIG(4096, 1))
      {
        if (cmpSklSwapBaseCheck(v4))
        {
          cmpChgSkillMode(1);
        }
        goto LABEL_77;
      }
      if (CHECK_TRIG(45826, 1))
      {
        if (cmpOpenOmoedeLog())
        {
LABEL_53:
          cmpIncModeSq(0);
          goto LABEL_77;
        }
        goto LABEL_77;
      }
      if (!CHECK_TRIG(4097, 1))
        goto LABEL_77;
      goto LABEL_30;
    }
    cmpCmpGuideSet(26, 0, 90);
    v12 = CHECK_TRIG(4097, 1);
    if (!v12)
    {
      cmpMemSklCurUpdate();
      goto LABEL_77;
    }
LABEL_30:
    cmpDecModeSq(0);
    goto LABEL_77;
  }
  LogError("ステータス画面が起動していない", 0);
  return -1;
}

// 0x209ab00
SkillIcon cmpGetSkillIconType(SBTLSKILLP_TBL *_tbl, SKLID _skillID) {
  void *Instance;
  signed s32 attr;
  s32 v8;
  s32 v9;
  u32 v10;

  if (!tbl)
    return -1;
  if (RaidouSklCheck(skillID))
  {
    Instance = get_Instance(0);
    return GetSpSklIconType(Instance, skillID, 0);
  }
  if (cmpSpiritSklCheck(skillID))
    return 23;
  if ((tbl->type & 0x1000) != 0)
    return 3;
  if ((tbl->type & 0x6000) != 0)
    return 5;
  if (cmpChkSousaSkill(skillID))
    return 4;
  if (!sBtlChkRepeat(skillID))
  {
    if ((skillID & 0xFFFFFFFE) == 0x76)
      return 33;
    else
      return 0;
  }
  attr = tbl->attr;
  if (attr <= 32)
  {
    if (attr > 8)
    {
      if (attr == 32)
        v8 = 29;
      else
        v8 = 0;
      if (attr == 16)
        return 28;
      else
        return v8;
    }
    v10 = attr - 1;
    if (v10 < 8)
      return dword_3E60718[v10];
    return 0;
  }
  if ((u32)attr <= 0x80)
  {
    if (attr == 128)
      v9 = 31;
    else
      v9 = 0;
    if (attr == 64)
      return 30;
    else
      return v9;
  }
  if (attr == 256)
    return 32;
  if (attr != 512)
    return 0;
  return (LOBYTE(tbldata[skillID]->flg) << 29 >> 31) & 0x21;
}

// 0x209ae40
void cmpDrawSkillNameExUnity(SKLID a_id, s32 cnt, u32 a_rgba, bool _backChange, bool _raidou, bool _noSpCol) {
  Il2CppObject *Instance;
  s64 v14;
  Il2CppClass *klass;
  char *LocalizeText;
  char **v17;
  char *v18;
  bool v19;
  s64 v20;
  void (__fastcall *v21)(Il2CppClass *, u64, s64, s64);
  SBTLSKILLP_TBL *Skilltbl;
  u32 SkillIconType;

  Instance = _get_Instance();
  v14 = 10;
  if (raidou)
    v14 = 8;
  klass = Instance[v14].klass;
  if (a_id < 0)
  {
    v17 = &"CMP_STATUS_L0018";
  }
  else
  {
    if (a_id)
    {
      LocalizeText = sdatSkillName(a_id);
      if (!backChange)
        goto LABEL_24;
      goto LABEL_18;
    }
    v17 = &"CMP_STATUS_L0019";
  }
  LocalizeText = GetLocalizeText(*v17, 1);
  if (!backChange)
  {
LABEL_24:
    (*(klass->_1.image + 57))(klass, cnt, 0, *((u64 *)klass->_1.image + 58));
    goto LABEL_25;
  }
LABEL_18:
  v18 = GetLocalizeText("CMP_STATUS_L0018", 1);
  v19 = op_Equality(LocalizeText, v18, 0);
  if (a_rgba == 1 || v19)
    goto LABEL_24;
  v21 = *(klass->_1.image + 57);
  v20 = *((u64 *)klass->_1.image + 58);
  if (LocalizeText)
    v21(klass, cnt, 0, v20);
  else
    v21(klass, cnt, 2, v20);
LABEL_25:
  (*(klass->_1.image + 55))(klass, cnt, LocalizeText, a_rgba, noSpCol, *((u64 *)klass->_1.image + 56));
  Skilltbl = sBtlGetSkilltbl(a_id);
  SkillIconType = cmpGetSkillIconType(Skilltbl, a_id);
  (*(klass->_1.image + 59))(klass, SkillIconType, cnt, *((u64 *)klass->_1.image + 60));
}

// 0x209b0a0
void cmpDrawRsvSkillNameExUnity(SKLID a_id, s32 cnt, u32 a_rgba, bool _backChange, bool _noSpCol) {
  Il2CppClass *klass;
  u32 v12;
  char *LocalizeText;
  char **v14;
  char *v15;
  bool v16;
  s64 v17;
  void (__fastcall *v18)(Il2CppClass *, u64, s64, s64);
  SBTLSKILLP_TBL *Skilltbl;
  u32 SkillIconType;

  klass = _get_Instance()[10].klass;
  v12 = cnt + 8;
  if (a_id < 0)
  {
    v14 = &"CMP_STATUS_L0018";
  }
  else
  {
    if (a_id)
    {
      LocalizeText = sdatSkillName(a_id);
      if (!backChange)
        goto LABEL_22;
      goto LABEL_16;
    }
    v14 = &"CMP_STATUS_L0019";
  }
  LocalizeText = GetLocalizeText(*v14, 1);
  if (!backChange)
  {
LABEL_22:
    (*(klass->_1.image + 57))(klass, v12, 0, *((u64 *)klass->_1.image + 58));
    goto LABEL_23;
  }
LABEL_16:
  v15 = GetLocalizeText("CMP_STATUS_L0018", 1);
  v16 = op_Equality(LocalizeText, v15, 0);
  if (a_rgba == 1 || v16)
    goto LABEL_22;
  v18 = *(klass->_1.image + 57);
  v17 = *((u64 *)klass->_1.image + 58);
  if (LocalizeText)
    v18(klass, v12, 0, v17);
  else
    v18(klass, v12, 2, v17);
LABEL_23:
  (*(klass->_1.image + 55))(klass, v12, LocalizeText, a_rgba, noSpCol, *((u64 *)klass->_1.image + 56));
  Skilltbl = sBtlGetSkilltbl(a_id);
  SkillIconType = cmpGetSkillIconType(Skilltbl, a_id);
  (*(klass->_1.image + 59))(klass, SkillIconType, v12, *((u64 *)klass->_1.image + 60));
}

// 0x209b2f0
void cmpDrawSkillOmoideNameExUnity(SKLID a_id, s32 cnt, u32 a_rgba) {
  void *monitor;
  char *LocalizeText;
  char **v9;
  SBTLSKILLP_TBL *Skilltbl;
  u32 SkillIconType;

  monitor = _get_Instance()[10].monitor;
  if (a_id < 0)
  {
    v9 = &"CMP_STATUS_L0018";
    goto LABEL_14;
  }
  if (!a_id)
  {
    v9 = &"CMP_STATUS_L0019";
LABEL_14:
    LocalizeText = GetLocalizeText(*v9, 1);
    goto LABEL_15;
  }
  LocalizeText = sdatSkillName(a_id);
LABEL_15:
  (*(*(u64 *)monitor + 472))(monitor, cnt, LocalizeText, a_rgba, 0, 0, 0xFFFFFFFFLL, *(u64 *)(*(u64 *)monitor + 480));
  Skilltbl = sBtlGetSkilltbl(a_id);
  SkillIconType = cmpGetSkillIconType(Skilltbl, a_id);
  (*(*(u64 *)monitor + 520))(monitor, SkillIconType, cnt, *(u64 *)(*(u64 *)monitor + 528));
}

// 0x209b490
bool cmpCurInit(cmpStatusCur_t *a_wk) {
  if (a_wk)
  {
    a_wk->drwNo = 0;
    a_wk->drwMax = 0;
    *(u64 *)&a_wk->selNo = 0;
    *(u64 *)&a_wk->flags = 0;
  }
  return a_wk != 0;
}

// 0x209b4c0
bool cmpCurSetSelectMax(cmpStatusCur_t *a_wk, s32 a_max) {
  bool v3;
  _BOOL4 v4;

  if (a_wk)
    v3 = a_max <= 0;
  else
    v3 = 1;
  v4 = !v3;
  if (v4)
    a_wk->selMax = a_max;
  return v4;
}

// 0x209b4e0
bool cmpCurSetDrawMax(cmpStatusCur_t *a_wk, s32 a_max) {
  bool v3;
  _BOOL4 v4;

  if (a_wk)
    v3 = a_max <= 0;
  else
    v3 = 1;
  v4 = !v3;
  if (v4)
    a_wk->drwDefMax = a_max;
  return v4;
}

// 0x209b500
bool cmpCurStart(cmpStatusCur_t *a_wk, bool a_bFixDrawNum) {
  s32 selMax;
  s32 drwDefMax;

  if (!a_wk)
    return a_wk != 0;
  selMax = a_wk->selMax;
  *(u64 *)&a_wk->topNo = 0;
  a_wk->selNo = 0;
  drwDefMax = a_wk->drwDefMax;
  if (a_bFixDrawNum)
  {
    a_wk->drwDefNum = drwDefMax;
    if (selMax < drwDefMax)
    {
      a_wk->drwMax = selMax;
      return a_wk != 0;
    }
  }
  else
  {
    if (selMax < drwDefMax)
    {
      a_wk->drwMax = selMax;
      a_wk->drwDefNum = selMax;
      return a_wk != 0;
    }
    a_wk->drwDefNum = drwDefMax;
  }
  a_wk->drwMax = drwDefMax;
  return a_wk != 0;
}

// 0x209b560
bool cmpCurSetMoveType(cmpStatusCur_t *a_wk, CMPSTATUS_CUR a_MoveType) {
  s32 selMax;
  s32 v4;
  s32 drwMax;
  s32 drwNo;
  s32 topNo;
  s32 selNo;
  s32 v9;
  s32 v10;
  s32 v12;
  s32 v13;
  bool v14;

  selMax = a_wk->selMax;
  v4 = a_wk->flags & 0xFFFFFFFC;
  drwMax = a_wk->drwMax;
  topNo = a_wk->topNo;
  drwNo = a_wk->drwNo;
  selNo = a_wk->selNo;
  v9 = selMax - 1;
  v10 = drwMax - 1;
  a_wk->flags = v4;
  if ((a_MoveType & 1) == 0)
  {
    if ((a_MoveType & 2) == 0)
      return 0;
    if ((a_MoveType & 4) == 0)
    {
      if (drwNo == v10)
      {
        if (selMax > drwMax + topNo)
        {
          v12 = topNo + 1;
          a_wk->flags = v4 | 1;
          v9 = topNo + 1 + drwNo;
          v10 = drwNo;
LABEL_46:
          a_wk->selNo = v9;
          a_wk->topNo = v12;
          v14 = 1;
          a_wk->drwNo = v10;
          return v14;
        }
        v14 = 0;
        if ((a_MoveType & 8) == 0 || v9 != topNo + drwNo)
          return v14;
        goto LABEL_40;
      }
      if (v9 == topNo + drwNo)
      {
        v14 = 0;
        if ((a_MoveType & 8) == 0)
          return v14;
LABEL_40:
        if (selMax < 2)
          return v14;
        v12 = 0;
        v10 = 0;
        v9 = 0;
        goto LABEL_45;
      }
      if (selMax < 2)
        return 0;
      v13 = v4 | 1;
      v10 = drwNo + 1;
LABEL_27:
      a_wk->flags = v13;
      v9 = v10 + topNo;
      v12 = topNo;
      goto LABEL_46;
    }
    v12 = selMax - drwMax;
    if (selMax <= drwMax)
      return 0;
    if (drwMax + topNo < selMax && drwMax + topNo <= v12)
    {
      v9 = drwMax + selNo;
      v12 = drwMax + topNo;
      v10 = drwNo;
    }
    if (selNo == v9 && topNo == v12 && drwNo == v10)
      return 0;
    goto LABEL_45;
  }
  if ((a_MoveType & 4) != 0)
  {
    if (selMax <= drwMax)
      return 0;
    v9 = selNo - drwMax;
    if (selNo - drwMax < 0 || (v12 = topNo - drwMax, topNo - drwMax <= 0))
    {
      v12 = 0;
      v10 = 0;
      v9 = 0;
    }
    else
    {
      v10 = drwNo;
    }
    if (selNo == v9 && topNo == v12 && drwNo == v10)
      return 0;
    goto LABEL_45;
  }
  if (drwNo)
  {
    if (selMax < 2)
      return 0;
    v13 = v4 | 1;
    v10 = drwNo - 1;
    goto LABEL_27;
  }
  if (topNo)
  {
    v10 = 0;
    a_wk->flags = v4 | 1;
    v12 = topNo - 1;
    v9 = topNo - 1;
    goto LABEL_46;
  }
  if ((a_MoveType & 8) == 0)
    return 0;
  v12 = selMax - drwMax;
  if (selMax > drwMax)
  {
LABEL_45:
    a_wk->flags = v4 | 1;
    goto LABEL_46;
  }
  if (selMax >= 2)
  {
    v12 = 0;
    a_wk->flags = v4 | 1;
    v10 = selMax - 1;
    goto LABEL_46;
  }
  return 0;
}

// 0x209b760
s32 cmpGetSuteCsr(void) {
  s32 *ProcessData;

  if (!g_mainPID)
    return 0;
  if (!dds3ExistProcess(g_mainPID))
    return 0;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return ProcessData[57];
  return ProcessData[57];
}

// 0x209b910
void cmpOmoideGaIppai(SKLID sklid) {
  Il2CppObject *ProcessData;

  if (!g_mainPID)
    return;
  if (dds3ExistProcess(g_mainPID))
  {
    ProcessData = dds3GetProcessData(g_mainPID);
    if (!ProcessData)
      goto LABEL_21;
    goto LABEL_19;
    if (!ProcessData)
    {
LABEL_21:
      LODWORD(ProcessData[14].klass) = sklid;
      HIDWORD(ProcessData[14].klass) = -1;
      return;
    }
LABEL_19:
    goto LABEL_21;
  }
}

// 0x209bac0
sdatUnitWork_t *cmpGetUnit(void) {
  bool exist;
  sdatUnitWork_t *result;
  sdatUnitWork_t *ProcessData;
  s64 naturalAligment;

  if (!g_mainPID)
    return 0;
  exist = dds3ExistProcess(g_mainPID);
  result = 0;
  if (exist)
  {
    ProcessData = (sdatUnitWork_t *)dds3GetProcessData(g_mainPID);
    if (!ProcessData)
      return ProcessData[10];
    LOBYTE(ProcessData->prevTarget) < (u32)naturalAligment || *((tagCMP_STATUS_WORK **)(ProcessData)->aRsvSkl + naturalAligment - 1) != tagCMP_STATUS_WORK;
    return ProcessData[10];
  }
  return result;
}

// 0x209bc50
s32 cmpGetOmoideBlank(void) {
  s32 result;
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  s64 v8;
  s64 initializationExceptionGCHandle_low;
  s64 v10;

  if (!g_mainPID)
    return -1;
  if (!dds3ExistProcess(g_mainPID))
    return -1;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_21;
  goto LABEL_19;
  if (!ProcessData)
LABEL_19:
LABEL_21:
  klass = ProcessData[5].klass;
  if (SLOWORD(klass->_2.initializationExceptionGCHandle) < 1)
    return -1;
  v8 = 0;
  initializationExceptionGCHandle_low = LOWORD(klass->_2.initializationExceptionGCHandle);
  result = -1;
  v10 = &klass->rgctx_data[4];
  while (*(u32 *)(v10 + 4 * v8))
  {
    if (initializationExceptionGCHandle_low == ++v8)
      return result;
  }
  return v8;
}

// 0x209be50
s32 cmpGetLearnEffCnt(void) {
  s32 *ProcessData;

  if (!g_mainPID)
    return 0;
  if (!dds3ExistProcess(g_mainPID))
    return 0;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return ProcessData[53];
  return ProcessData[53];
}

// 0x209c000
void cmpLearnEff(s32 skltype, s32 index, bool ofc) {
  Il2CppObject *Instance;
  Il2CppObject *v9;
  Il2CppObject *ProcessData;
  s32 v13;

  if (!g_mainPID)
    return;
  if (!dds3ExistProcess(g_mainPID))
    return;
  Instance = _get_Instance();
  (*(Instance[8].klass->_1.image + 77))(Instance[8].klass, *((u64 *)Instance[8].klass->_1.image + 78));
  v9 = _get_Instance();
  (*(v9[10].klass->_1.image + 77))(v9[10].klass, *((u64 *)v9[10].klass->_1.image + 78));
  goto LABEL_15;
LABEL_19:
  goto LABEL_21;
LABEL_15:
  ProcessData = dds3GetProcessData(g_mainPID);
  if (ProcessData)
    goto LABEL_19;
LABEL_21:
  HIDWORD(ProcessData[13].klass) = 1;
  LOBYTE(ProcessData[24].klass) = ofc;
  if (index == -1)
  {
    HIDWORD(ProcessData[23].monitor) = 8;
    LODWORD(ProcessData[13].monitor) = 285;
    HIDWORD(ProcessData[13].monitor) = 265;
  }
  else
  {
    HIDWORD(ProcessData[23].monitor) = index;
    if (index >= 0)
      v13 = index;
    else
      v13 = index + 1;
    LODWORD(ProcessData[13].monitor) = 140 * (index - (v13 & 0xFFFFFFFE)) + 5;
    HIDWORD(ProcessData[13].monitor) = 25 * (v13 >> 1) + 265;
  }
}

// 0x209c280
void cmpAutoBattleSkl(sdatUnitWork_t *pUnit, SKLID sklid) {
  SKLID *battleskill;
  s64 max_length_low;
  s32 *i;

  battleskill = pUnit->battleskill;
  max_length_low = LODWORD(battleskill->max_length);
  if (LODWORD(battleskill->max_length))
  {
    for (i = battleskill; *i > 0; ++i)
    {
      if (!--max_length_low)
        return;
    }
    *i = sklid;
  }
}

// 0x209c2c0
void cmpLearnSkl(SKLID sklid, s32 skltype, s32 index, bool _ofs) {
  Il2CppObject *ProcessData;
  Il2CppObject *v13;
  Il2CppClass *v15;
  u32 *interopData;
  s64 v18;
  sdatUnitWork_t *klass;
  sdatUnitWork_t *stock_id;
  sdatUnitWork_t *v24;
  s32 *v25;
  sdatPlayerUnitWork_t *player;
  sdatUnitWork_t *para;
  s32 swordno;

  if (!g_mainPID)
    return;
  if (!dds3ExistProcess(g_mainPID))
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  v13 = ProcessData;
  if (skltype == 1)
  {
    klass = ProcessData[5].klass;
    if (klass->devilid)
    {
      klass->aOmoideSkill[index] = sklid;
      datCalcNowParam(klass, 0, 0);
      if (cmpSetSkillNow())
      {
        stock_id = GBWK->player->stock_id;
        v24 = stock_id[datGetStockDevilIndex(SHIWORD(v13[5].klass->_1.name), v13[5].klass->_2.token)];
        v24->aOmoideSkill[index] = sklid;
        datCalcNowParam(v24, 0, 0);
      }
    }
    else
    {
      player = GBWK->player;
      para = player->para;
      swordno = player->swordno;
      player->spiritSkill[index] = sklid;
      datCalcNowParam(para, swordno, 0);
      datDvlParaUpdate(0);
    }
  }
  else if (!skltype)
  {
    v15 = ProcessData[5].klass;
    *((u32 *)v15->_1.typeMetadataHandle + index + 9) = sklid;
    if (ofs)
    {
      goto LABEL_22;
    }
    else
    {
      *((u32 *)v15->_2.typeHierarchy + index + 8) = 0;
LABEL_22:
      interopData = v15->_1.interopData;
      v18 = interopData[6];
      if (!interopData[6])
        goto LABEL_46;
      goto LABEL_38;
    }
    interopData = v15->_1.interopData;
    v18 = interopData[6];
    if (!interopData[6])
    {
LABEL_46:
      CmpStatusSetOfficialSkl(v13[5].klass, sklid);
      return;
    }
LABEL_38:
    v25 = (interopData + 8);
    while (*v25 > 0)
    {
      --v18;
      ++v25;
      if (!v18)
        goto LABEL_46;
    }
    *v25 = sklid;
    goto LABEL_46;
  }
}

// 0x209c650
s32 cmpGetSklCsrMax_R(sdatUnitWork_t *pUnit, s32 arg) {
  dds3GetProcessData(g_mainPID);
  if (arg != 1)
    return 0;
  return GBWK->player->spiritCnt;
}

// 0x209c770
void cmpSetSklCsrMax(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  sdatUnitWork_t *klass;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  v4 = ProcessData;
  klass = ProcessData[5].klass;
  LODWORD(v4[21].monitor) = datSklDrawMaxCnt(klass);
}

// 0x209c8d0
s32 cmpGetSklCsrMax(sdatUnitWork_t *pUnit, s32 arg) {
  s32 *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  if (arg)
  {
    if (arg == 1)
    {
      return pUnit->iOmoideSkillCnt;
    }
    else if (arg == 2)
    {
      return 2;
    }
    else
    {
      return 0;
    }
  }
  else if (ProcessData[86] >= 8)
  {
    return 8;
  }
  else
  {
    return ProcessData[86];
  }
}

// 0x209ca50
SKLID cmpGetCsrSelSkl(void) {
  s32 *ProcessData;

  if (!g_mainPID)
    return 0;
  if (!dds3ExistProcess(g_mainPID))
    return 0;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return ProcessData[98];
  return ProcessData[98];
}

// 0x209cc00
s32 cmpGetSklCsr(void) {
  s32 *ProcessData;

  if (!g_mainPID)
    return 0;
  if (!dds3ExistProcess(g_mainPID))
    return 0;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return ProcessData[63];
  return ProcessData[63];
}

// 0x209cdb0
s32 cmpGetRsvCsr(void) {
  s32 *ProcessData;

  if (!g_mainPID)
    return 0;
  if (!dds3ExistProcess(g_mainPID))
    return 0;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return ProcessData[84];
  return ProcessData[84];
}

// 0x209cf60
void cmpSetSklCsr(s32 _no) {
  Il2CppObject *ProcessData;

  if (!g_mainPID)
    return;
  if (dds3ExistProcess(g_mainPID))
  {
    ProcessData = dds3GetProcessData(g_mainPID);
    if (!ProcessData)
      goto LABEL_21;
    goto LABEL_19;
    if (!ProcessData)
    {
LABEL_21:
      HIDWORD(ProcessData[15].monitor) = no;
      return;
    }
LABEL_19:
    goto LABEL_21;
  }
}

// 0x209d110
void cmpSetRsvCsr(s32 _no) {
  Il2CppObject *ProcessData;

  if (!g_mainPID)
    return;
  if (dds3ExistProcess(g_mainPID))
  {
    ProcessData = dds3GetProcessData(g_mainPID);
    if (!ProcessData)
      goto LABEL_21;
    goto LABEL_19;
    if (!ProcessData)
    {
LABEL_21:
      LODWORD(ProcessData[21].klass) = no;
      return;
    }
LABEL_19:
    goto LABEL_21;
  }
}

// 0x209d2c0
void cmpCurInitMemSkl(sdatUnitWork_t *a_pUnit, MemPanelType memPanelType) {
  Il2CppObject *ProcessData;
  Il2CppObject *v8;
  sdatUnitWork_t *klass;
  s32 namespaze;
  char *monitor;
  char *v13;
  s32 v14;

  ProcessData = dds3GetProcessData(g_mainPID);
  v8 = ProcessData;
  if (memPanelType == 2)
  {
    if (!a_pUnit->devilid)
    {
      namespaze = ProcessData[23].klass->_1.namespaze;
      goto LABEL_21;
    }
    LogError("悪魔ではこないはず", 0);
LABEL_20:
    namespaze = 0;
    goto LABEL_21;
  }
  if (memPanelType)
    goto LABEL_20;
  if (a_pUnit->devilid)
  {
    klass = ProcessData[5].klass;
    namespaze = datOmoideSkillGetCount(klass);
  }
  else
  {
    namespaze = datSpiritSkillGetCount(GBWK->player);
  }
LABEL_21:
  monitor = v8[19].monitor;
  if (monitor)
  {
    *((u32 *)monitor + 11) = 0;
    *((u32 *)monitor + 6) = 0;
    *(u64 *)(monitor + 36) = 0;
    *((u64 *)monitor + 2) = 0;
  }
  v13 = v8[19].monitor;
  if (namespaze >= 1 && v13)
  {
    *((u32 *)v13 + 5) = namespaze;
  }
  else
  {
    if (!v13)
      return;
    namespaze = *((u32 *)v13 + 5);
  }
  *((u32 *)v13 + 11) = 0;
  if (namespaze >= 8)
    v14 = 8;
  else
    v14 = namespaze;
  *((u32 *)v13 + 6) = v14;
  *(_OWORD *)(v13 + 28) = xmmword_3CFF770;
}

// 0x209d530
SKLID cmpCurGetSelectMemSklID(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  s64 v6;
  s32 v7;
  sdatUnitWork_t *klass;
  s32 v12;
  s32 v13;
  sdatPlayerUnitWork_t *player;
  SKLID **p_g_aOmoide;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  if (HIWORD(ProcessData[5].klass->_1.name))
  {
    v6 = 0;
    v7 = 0;
    while (1)
    {
      if (v6 >= SLODWORD(g_aOmoide->max_length))
        return 0;
      klass = v4[5].klass;
      v12 = g_aOmoide[v6];
      if (!!datOmoideSkillGetMaster(klass, v12))
      {
        if (v7 == *((u32 *)v4[19].monitor + 9))
        {
          p_g_aOmoide = &g_aOmoide;
          return (*p_g_aOmoide)[v6];
        }
        ++v7;
      }
      ++v6;
    }
  }
  v6 = 0;
  v13 = 0;
  while (1)
  {
    if (v6 >= SLODWORD(spiritList->max_length))
      return 0;
    player = GBWK->player;
    if (!!datSpiritSkillGetMaster(player, spiritList[v6]))
    {
      if (v13 == *((u32 *)v4[19].monitor + 9))
        break;
      ++v13;
    }
    ++v6;
  }
  p_g_aOmoide = &spiritList;
  return (*p_g_aOmoide)[v6];
}

// 0x209d870
void cmpGetSwordParam(s32 a_swordno, u8 *a_pParam) {
  s32 level;
  s32 SwordAisyo;
  u8 v8;

  *(u16 *)&a_pParam[2] = 0;
  if (!a_swordno)
    goto LABEL_14;
  if (datCheckStrongSwordAttack(a_swordno))
  {
    level = 0;
    goto LABEL_15;
  }
  if (a_swordno < 1)
  {
LABEL_14:
    level = 1;
    goto LABEL_15;
  }
  level = sBtlGetDevilData(a_swordno, -1)->level;
  a_pParam[0] = cmpGetSwordNameLevel(level);
  if (a_swordno < 1)
    goto LABEL_22;
  goto LABEL_16;
LABEL_15:
  a_pParam[0] = cmpGetSwordNameLevel(level);
  if (a_swordno < 1)
  {
LABEL_22:
    a_pParam[1] = 0;
    return;
  }
LABEL_16:
  SwordAisyo = datGetSwordAisyoEx(a_swordno);
  v8 = SwordAisyo - 32;
  if (SwordAisyo <= 543)
    v8 = 0;
  a_pParam[1] = v8;
}

// 0x209db10
ANALOG cmpGetAnalogPad(void) {
  f32 v2;
  f32 v4;
  u8 AnalogLX;
  u8 AnalogLY;
  s32 v7;
  s32 v8;
  s32 v9;
  s32 v10;
  s32 v11;
  s32 v12;
  s32 v13;
  s32 AnalogRX;
  u8 AnalogRY;
  s32 v16;
  s32 v17;
  s32 v18;

  v2 = fldGetAnalogSensitivity();
  v4 = v2;
  AnalogLX = dds3PadGetAnalogLX(1);
  AnalogLY = dds3PadGetAnalogLY(1);
  v7 = v4;
  v8 = AnalogLX;
  if (v4 == INFINITY)
    v7 = 0x80000000;
  v9 = v7 + 128;
  v10 = 128 - v7;
  v11 = 2 * (v7 + 128 < v8);
  if (v10 > v8)
    v11 = 1;
  v12 = v11 | 4;
  if (v9 < AnalogLY)
    v11 |= 8u;
  if (v10 <= AnalogLY)
    v13 = v11;
  else
    v13 = v12;
  AnalogRX = dds3PadGetAnalogRX(1);
  AnalogRY = dds3PadGetAnalogRY(1);
  v16 = v13 | 0x20;
  v17 = v13 | 0x10;
  if (v9 >= AnalogRX)
    v16 = v13;
  if (v10 <= AnalogRX)
    v17 = v16;
  v18 = v17 | 0x40;
  if (v9 < AnalogRY)
    v17 |= 0x80u;
  if (v10 <= AnalogRY)
    return v17;
  else
    return v18;
}

// 0x209dcb0
void cmpGetMotionParam(tagCMP_STATUS_WORK *wk) {
  wk->motionNum = cmpGetMotionNum();
  wk->motionCut = cmpGetMotionCut() - 1;
  wk->motionSpd = cmpGetMotionSpeed();
}

// 0x209dd40
void cmpSetModelLight(tagCMP_STATUS_WORK *wk) {
  s32 level;

  if (cmpGetBstNo(wk->unit->badstatus) == 17)
    goto LABEL_4;
  if ((~LODWORD(wk->type) & 0x10010100) == 0)
  {
    if (resultCheck)
      goto LABEL_15;
    level = wk->unit->level;
    if (level > GBWK->player->para->level)
    {
LABEL_4:
      cmpSetLightDark();
      return;
    }
  }
LABEL_15:
  cmpSetLightDef();
}

// 0x209dea0
void cmpUpdatemodel(tagCMP_STATUS_WORK *wk) {
  s32 stepModel;
  s64 flags;
  s64 v6;
  u32 BstNo;
  s32 callModelNo;
  s32 v13;
  s64 v14;

  stepModel = wk->stepModel;
  if (stepModel != 2)
  {
    if (stepModel != 1)
    {
      if (!wk->stepModel)
      {
        flags = wk->flags;
        if ((flags & 0x100) != 0)
        {
          flags &= ~0x100u;
          if ((wk->loadModelNo & 0x80000000) == 0)
            wk->loadModelNo = -1;
          wk->stepModel = 1;
        }
        wk->flags = flags & 0xFFFFFFFFFFFFFDFFLL;
      }
      return;
    }
    if (cmpChkStatusModelLoadStat())
      return;
    if ((wk->flags & 0x100) != 0)
    {
      wk->stepModel = 0;
      return;
    }
    cmpSetModelLight(wk);
    BstNo = cmpGetBstNo(wk->unit->badstatus);
    callModelNo = wk->callModelNo;
    g_bstID = BstNo;
    wk->loadModelNo = callModelNo;
    v13 = (u8)Setup(callModelNo, 0);
    if (v13 == 2)
    {
      v14 = wk->flags;
      wk->stepModel = 0;
      wk->flags = v14 | 0xA00;
      cmpGetMotionParam(wk);
    }
    else if (v13 == 1)
    {
      wk->flags &= ~0x800u;
      ++wk->stepModel;
    }
    return;
  }
  if (cmpChkStatusModelLoadStat())
    return;
  v6 = wk->flags;
  wk->stepModel = 0;
  if ((v6 & 0x100) == 0)
  {
    wk->flags = v6 | 0xA00;
    wk->motionNum = cmpGetMotionNum();
    wk->motionCut = cmpGetMotionCut() - 1;
    wk->motionSpd = cmpGetMotionSpeed();
    return;
  }
}

// 0x209e1c0
void cmpViewerModel(tagCMP_STATUS_WORK *wk) {
  f32 *v3;
  f32 *v4;
  f32 *v5;
  f32 v6;
  f32 v8;
  f32 v9;
  f32 v10;

  v3 = NewSpecific(f32, 3u);
  v4 = NewSpecific(f32, 3u);
  v3[8] = 0.0;
  v5 = v4;
  v4[8] = 0.0;
  v3[9] = 0.0;
  v4[9] = 0.0;
  v3[10] = 0.0;
  v4[10] = 0.0;
  if ((wk->flags & 0x20000000) != 0)
  {
    v6 = 0.0;
    if (CHECK_PRESS2(4104) || CHECK_PRESS2(4105))
      goto LABEL_24;
  }
  if (CHECK_PRESS(4102, 1))
  {
    v3[8] = -1.0;
    if (!CHECK_PRESS(4103, 1))
    {
LABEL_8:
      if ((wk->flags & 0x20000000) == 0)
        goto LABEL_9;
      goto LABEL_15;
    }
  }
  else if (!CHECK_PRESS(4103, 1))
  {
    goto LABEL_8;
  }
  v3[8] = 1.0;
  if ((wk->flags & 0x20000000) == 0)
  {
LABEL_9:
    if (CHECK_PRESS(4100, 1))
      v3[9] = -1.0;
    if (!CHECK_PRESS(4101, 1))
      goto LABEL_19;
LABEL_18:
    v3[9] = 1.0;
    goto LABEL_19;
  }
LABEL_15:
  if (CHECK_PRESS(4112, 1))
    v3[9] = -1.0;
  if (CHECK_PRESS(4113, 1))
    goto LABEL_18;
LABEL_19:
  if (CHECK_PRESS(4116, 1))
  {
    v3[10] = -1.0;
    if (!CHECK_PRESS(4117, 1))
    {
LABEL_21:
      if (!CHECK_PRESS(41750, 1))
        goto LABEL_22;
LABEL_29:
      v5[9] = 1.0;
      if (!CHECK_PRESS(41751, 1))
      {
LABEL_23:
        v6 = 0.0;
        if ((wk->flags & 0x20000000) == 0)
          goto LABEL_24;
LABEL_31:
        if (!CHECK_PRESS2(4100))
        {
          if (!CHECK_PRESS2(4101))
            goto LABEL_35;
          goto LABEL_34;
        }
        v5[8] = -1.0;
        if (!CHECK_PRESS2(4101))
        {
LABEL_35:
          if (CHECK_PRESS2(4107))
            v6 = -0.01;
          else
            v6 = 0.0;
          if (CHECK_PRESS2(4108))
            v6 = 0.01;
          v8 = v3[8];
          v9 = v3[9];
          v10 = v3[10];
          goto LABEL_26;
        }
LABEL_34:
        v5[8] = 1.0;
        goto LABEL_35;
      }
      goto LABEL_30;
    }
  }
  else if (!CHECK_PRESS(4117, 1))
  {
    goto LABEL_21;
  }
  v3[10] = 1.0;
  if (CHECK_PRESS(41750, 1))
    goto LABEL_29;
LABEL_22:
  if (!CHECK_PRESS(41751, 1))
    goto LABEL_23;
LABEL_30:
  v5[9] = -1.0;
  v6 = 0.0;
  if ((wk->flags & 0x20000000) != 0)
    goto LABEL_31;
LABEL_24:
  v8 = v3[8];
  v9 = v3[9];
  v10 = v3[10];
LABEL_26:
  cmpAddPos(v8, v9, v10);
  cmpAddRot(v5[8], v5[9], v5[10]);
  cmpAddScl(v6);
  cmpAddEffScl(0.0);
}

// 0x209e560
bool cmpDrawEquipIsSoubigo(tagCMP_STATUS_WORK *wk) {
  s64 type;

  type = wk->type;
  return type == 17039361 || type == 268697856 || type == 0x110040100LL;
}

// 0x209e5a0
s32 cmpCalcRestParamPly(tagCMP_STATUS_WORK *wk) {
  s32 *v3;
  sdatUnitWork_t *unit;
  u32 *v5;
  s32 str;
  sdatUnitWork_t *v7;
  s32 tec;
  sdatUnitWork_t *v9;
  s32 vit;
  sdatUnitWork_t *v11;
  s32 luck;
  s32 v13;
  s32 v15;
  s32 swordno;
  s32 Sword4Param;
  s32 v18;
  s32 v19;
  s32 v20;
  s32 v21;
  s32 v22;
  s32 v23;
  s32 v24;
  s32 v25;
  s32 v26;
  s32 v27;
  s32 v28;
  s32 v29;
  s32 v30;
  s32 v31;

  v3 = NewSpecific(s32, 4u);
  unit = wk->unit;
  v5 = v3;
  str = unit->backup->str;
  v3[0] = GETITEMPARA_LOW(unit->pitem->str) + str;
  v7 = wk->unit;
  tec = v7->backup->tec;
  v5[9] = GETITEMPARA_LOW(v7->pitem->tec) + tec;
  v9 = wk->unit;
  vit = v9->backup->vit;
  v5[10] = GETITEMPARA_LOW(v9->pitem->vit) + vit;
  v11 = wk->unit;
  luck = v11->backup->luck;
  v13 = GETITEMPARA_LOW(v11->pitem->luck) + luck;
  v5[11] = v13;
  v15 = v5[8];
  swordno = wk->swordno;
  Sword4Param = datGetSword4Param(swordno, 0);
  v18 = v5[9];
  v19 = wk->swordno;
  v20 = datGetSword4Param(v19, 1);
  v21 = v5[10];
  v22 = wk->swordno;
  v23 = datGetSword4Param(v22, 2);
  v24 = v5[11];
  v25 = wk->swordno;
  v26 = v18 - v20;
  v27 = v21 - v23;
  if (v15 - Sword4Param <= 39)
    v28 = 40 - (v15 - Sword4Param);
  else
    v28 = 0;
  if (v26 <= 39)
    v29 = v28 - v26 + 40;
  else
    v29 = v28;
  if (v27 <= 39)
    v30 = v29 - v27 + 40;
  else
    v30 = v29;
  v31 = datGetSword4Param(v25, 3);
  if (v24 - v31 <= 39)
    return v30 - (v24 - v31) + 40;
  else
    return v30;
}

// 0x209e7b0
s32 cmpCalcRestParamDvl(tagCMP_STATUS_WORK *wk) {
  s32 *v3;
  sdatUnitWork_t *unit;
  int32x4_t *v5;
  s32 str;
  s32 v7;
  s32 v8;
  s32 v9;
  sdatUnitWork_t *v10;
  s32 tec;
  s32 v12;
  s32 v13;
  s32 v14;
  sdatUnitWork_t *v15;
  s32 vit;
  s32 v17;
  s32 v18;
  s32 v19;
  sdatUnitWork_t *v20;
  s32 luck;
  s32 v22;
  s32 v23;
  s32 v24;
  u32 *v26;
  s32 devilid;
  s32 v28;
  s32 v29;
  s32 v30;
  s32 v31;
  s32 v32;
  int32x4_t v33;
  int32x4_t v34;
  int32x4_t v35;

  v3 = NewSpecific(s32, 4u);
  unit = wk->unit;
  v5 = v3;
  str = unit->backup->str;
  v7 = unit->pbtl->str;
  v8 = unit->huuma->str;
  v9 = GETITEMPARA_LOW(unit->pitem->str);
  v10 = wk->unit;
  v5[2].n128_u32[0] = v7 + str + v8 + v9;
  tec = v10->backup->tec;
  v12 = v10->pbtl->tec;
  v13 = v10->huuma->tec;
  v14 = GETITEMPARA_LOW(v10->pitem->tec);
  v15 = wk->unit;
  v5[2].n128_u32[1] = v12 + tec + v13 + v14;
  vit = v15->backup->vit;
  v17 = v15->pbtl->vit;
  v18 = v15->huuma->vit;
  v19 = GETITEMPARA_LOW(v15->pitem->vit);
  v20 = wk->unit;
  v5[2].n128_u32[2] = v17 + vit + v18 + v19;
  luck = v20->backup->luck;
  v22 = v20->pbtl->luck;
  v23 = v20->huuma->luck;
  v24 = v22 + luck + v23 + GETITEMPARA_LOW(v20->pitem->luck);
  v5[2].n128_u32[3] = v24;
  v26 = NewSpecific(s32, 4u);
  devilid = wk->unit->devilid;
  v28 = sBtlGetDevilData(devilid, -1)->str;
  v26[8] = GETITEMPARA_LOW(wk->unit->pitem->str) + v28;
  v29 = sBtlGetDevilData(wk->unit->devilid, -1)->tec;
  v26[9] = GETITEMPARA_LOW(wk->unit->pitem->tec) + v29;
  v30 = sBtlGetDevilData(wk->unit->devilid, -1)->vit;
  v26[10] = GETITEMPARA_LOW(wk->unit->pitem->vit) + v30;
  v31 = sBtlGetDevilData(wk->unit->devilid, -1)->luck;
  v32 = GETITEMPARA_LOW(wk->unit->pitem->luck);
  v33.n128_u64[0] = *((u64 *)v26 + 4);
  v34.n128_u64[0] = 0x2800000028LL;
  v34.n128_u64[1] = 0x2800000028LL;
  v26[11] = v32 + v31;
  v33.n128_u32[2] = v26[10];
  v33.n128_u32[3] = v32 + v31;
  v35 = vminq_s32(vaddq_s32(v33, v33), v34);
  return vaddvq_s32(vandq_s8(vsubq_s32(v35, v5[2]), vcgtq_s32(v35, v5[2])));
}

// 0x209ea30
s32 cmpCalcRestParam(tagCMP_STATUS_WORK *wk) {
  sdatUnitWork_t *unit;

  unit = wk->unit;
  if ((unit->flag & 2) != 0)
  {
    return cmpCalcRestParamPly(wk);
  }
  else if (unit->devilid < 1)
  {
    return 0;
  }
  else
  {
    return cmpCalcRestParamDvl(wk);
  }
}

// 0x209eaf0
bool cmpCalcParam(tagCMP_STATUS_WORK *wk, s8 a_mode, bool _noSe) {
  s32 *v7;
  sdatUnitWork_t *unit;
  u32 *v9;
  s32 str;
  sdatUnitWork_t *v11;
  s32 tec;
  sdatUnitWork_t *v13;
  s32 vit;
  sdatUnitWork_t *v15;
  s32 luck;
  s32 v17;
  sdatUnitWork_t *v19;
  s32 PlayerMaxHP;
  s32 v21;
  s32 v22;
  s32 swordno;
  s32 sel_param;
  s32 Sword4Param;
  s64 v26;
  _BOOL4 v27;
  s32 *m_Items;
  s64 v29;
  s32 *v30;
  s32 *param;
  s32 v32;
  s32 lvup_num;
  s32 v35;
  sdatUnitWork_t *v36;
  sdatParaWork_t *now;
  s32 v38;
  sdatUnitWork_t *v39;
  sdatParaWork_t *v40;
  s32 maxhp;
  sdatParaWork_t *v42;
  s32 v43;

  v7 = NewSpecific(s32, 4u);
  unit = wk->unit;
  v9 = v7;
  str = unit->backup->str;
  v7[0] = GETITEMPARA_LOW(unit->pitem->str) + str;
  v11 = wk->unit;
  tec = v11->backup->tec;
  v9[9] = GETITEMPARA_LOW(v11->pitem->tec) + tec;
  v13 = wk->unit;
  vit = v13->backup->vit;
  v9[10] = GETITEMPARA_LOW(v13->pitem->vit) + vit;
  v15 = wk->unit;
  luck = v15->backup->luck;
  v17 = GETITEMPARA_LOW(v15->pitem->luck) + luck;
  v9[11] = v17;
  v19 = wk->unit;
  PlayerMaxHP = datGetPlayerMaxHP(v19);
  v21 = datGetSwordParamHP(wk->swordno) + PlayerMaxHP;
  if (v21 >= 999)
    v22 = 999;
  else
    v22 = v21;
  if (a_mode >= 1)
  {
    swordno = wk->swordno;
    sel_param = wk->sel_param;
    Sword4Param = datGetSword4Param(swordno, sel_param);
    v26 = wk->sel_param;
    v27 = (u32)v26 == 3 && v9[11] - Sword4Param < 40;
    param = wk->param;
    if (v9[v26 + 8] - Sword4Param + param[v26] < 40)
      v27 = 1;
    if (!v27)
      goto LABEL_36;
    v32 = wk->sel_num + 1;
    lvup_num = wk->lvup_num;
    wk->sel_num = v32;
    if (v32 > lvup_num)
    {
      wk->sel_num = lvup_num;
      return 0;
    }
    ++param[v26];
    switch (wk->sel_param)
    {
      case 0:
        ++wk->unit->now->str;
        break;
      case 1:
        ++wk->unit->now->tec;
        break;
      case 2:
        ++wk->unit->now->vit;
        break;
      case 3:
        ++wk->unit->backup->luck;
        break;
      default:
        break;
    }
    if (noSe)
      goto LABEL_36;
    v35 = 0;
    goto LABEL_35;
  }
  m_Items = wk->param;
  --m_Items[wk->sel_param];
  v29 = wk->sel_param;
  v30 = &m_Items[v29];
  if (*v30 < 0)
  {
    *v30 = 0;
    return 0;
  }
  --wk->sel_num;
  switch ((s32)v29)
  {
    case 0:
      --wk->unit->now->str;
      break;
    case 1:
      --wk->unit->now->tec;
      break;
    case 2:
      --wk->unit->now->vit;
      break;
    case 3:
      --wk->unit->backup->luck;
      break;
    default:
      break;
  }
  if (!noSe)
  {
    v35 = 1;
LABEL_35:
    SE(v35);
  }
LABEL_36:
  v36 = wk->unit;
  now = v36->now;
  v38 = datGetPlayerMaxHP(v36);
  v39 = wk->unit;
  now->maxhp = v38;
  v40 = v39->now;
  maxhp = v40->maxhp;
  v40->maxhp = datGetSwordParamHP(wk->swordno) + maxhp;
  v42 = wk->unit->now;
  v43 = v42->maxhp;
  if (v43 >= 1000)
  {
    v43 = 999;
    v42->maxhp = 999;
  }
  v42->hp = v42->hp - v22 + v43;
  return 1;
}

// 0x209eef0
void cmpResetParam(tagCMP_STATUS_WORK *wk) {
  s32 *param;
  s32 sel_param;

  param = wk->param;
  sel_param = wk->sel_param;
  if (param[0] >= 1)
  {
    do
    {
      wk->sel_param = 0;
      cmpCalcParam(wk, 0, 1);
      param = wk->param;
    }
    while (param[0] > 0);
  }
  if (wk->sel_num)
  {
    if (param[1] < 1)
      goto LABEL_28;
    do
    {
      wk->sel_param = 1;
      cmpCalcParam(wk, 0, 1);
      param = wk->param;
    }
    while (param[1] > 0);
    if (wk->sel_num)
    {
LABEL_28:
      if (param[2] < 1)
        goto LABEL_20;
      do
      {
        wk->sel_param = 2;
        cmpCalcParam(wk, 0, 1);
        param = wk->param;
      }
      while (param[2] > 0);
      if (wk->sel_num)
      {
LABEL_20:
        if (param[3] >= 1)
        {
          do
          {
            wk->sel_param = 3;
            cmpCalcParam(wk, 0, 1);
          }
          while (wk->param[3] > 0);
        }
      }
    }
  }
  wk->sel_param = sel_param;
}

// 0x209f0a0
s32 cmpCtrlSetParam(tagCMP_STATUS_WORK *wk) {
  s32 sel_param;
  s32 v4;
  s32 v5;
  s32 v6;
  bool v7;
  s32 v8;
  s32 result;

  sel_param = wk->sel_param;
  if (CHECK_TRIG(4100, 1))
  {
    v4 = wk->sel_param - 1;
    if (v4 < 0)
      v4 = 3;
  }
  else
  {
    if (!CHECK_REP(4100, 1))
      goto LABEL_9;
    v4 = (wk->sel_param - 1) & ~((wk->sel_param - 1) >> 31);
  }
  wk->sel_param = v4;
LABEL_9:
  if (CHECK_TRIG(4101, 1))
  {
    v5 = wk->sel_param;
    if (v5 + 1 < 4)
      v6 = v5 + 1;
    else
      v6 = 0;
  }
  else
  {
    v7 = CHECK_REP(4101, 1);
    v8 = wk->sel_param;
    if (!v7)
    {
      if (v8 != sel_param)
        goto LABEL_24;
      goto LABEL_15;
    }
    if (v8 + 1 < 3)
      v6 = v8 + 1;
    else
      v6 = 3;
  }
  wk->sel_param = v6;
  if (v6 != sel_param)
  {
LABEL_24:
    SE(3);
    if (!CHECK_REP(4103, 1))
      goto LABEL_25;
LABEL_16:
    cmpCalcParam(wk, 1, 0);
    result = 0;
    if (wk->lvup_num != wk->sel_num)
      return -1;
    return result;
  }
LABEL_15:
  if (CHECK_REP(4103, 1))
    goto LABEL_16;
LABEL_25:
  if (CHECK_REP(4102, 1))
  {
    cmpCalcParam(wk, 0, 0);
    return -1;
  }
  if (!CHECK_TRIG(4097, 1) || wk->lvup_num == 1)
    return -1;
  cmpResetParam(wk);
  SE(1);
  return -1;
}

// 0x209f2b0
void cmpCallStart(tagCMP_STATUS_WORK *wk) {
  wk->flags &= 0xFFFFFFFFFBBFFFFFLL;
  cmpSetFlagDraw(1);
}

// 0x209f480
void cmpCallEnd(tagCMP_STATUS_WORK *wk) {
  wk->flags &= ~0x4000000u;
}

// 0x209f490
void cmpFuncEnd(tagCMP_STATUS_WORK *wk) {
  s64 flags;
  s64 v5;

  cmpWaitLoadModel();
  wk->callModelNo = -1;
  if (cmpFreeResource())
    wk->loadModelNo = -1;
  cmpSetFlagDraw(0);
  flags = wk->flags;
  LOBYTE(v5) = flags & 0x7F;
  wk->flags = flags & 0xFFFFFFFFFFFFF77FLL;
  if ((flags & 4) != 0)
  {
    cmpFreeSpriteHnd(0);
    v5 = wk->flags;
    if ((v5 & 0x10) != 0)
      goto LABEL_17;
LABEL_11:
    if ((v5 & 0x40) == 0)
      return;
    goto LABEL_19;
  }
  if ((flags & 0x10) == 0)
    goto LABEL_11;
LABEL_17:
  cmpFreeSpriteHnd(2);
  if ((wk->flags & 0x40) == 0)
    return;
LABEL_19:
  cmpFreeSpriteMem(1);
}

// 0x209f620
void cmpSequence(tagCMP_STATUS_WORK *wk) {
  s8 v3;
  u32 step;
  char *v5;
  Il2CppObject *v6;

  if ((wk->flags & 0x200) != 0)
  {
    if (wk->noCallVoice)
    {
      wk->noCallVoice = 0;
      v3 = (u8)wk + 32;
      step = wk->step;
      if (step > 0xA)
        goto LABEL_34;
    }
    else
    {
      ModelLoadInitAction();
      v3 = (u8)wk + 32;
      step = wk->step;
    }
    goto LABEL_12;
  }
  v3 = (u8)wk + 32;
  step = wk->step;
  if (step > 0xA)
  {
LABEL_34:
    v5 = ToString(v3, 0);
    v6 = Concat_54766928("有り得ない遷移::", v5, 0);
    LogError(v6, 0);
    wk->flags &= ~0x4000000u;
    return;
  }
LABEL_12:
  switch (step)
  {
    case 0u:
      cmpNmlSeqWaitStepUpdate(wk);
      return;
    case 1u:
      cmpNmlSeqStatusStepUpdate(wk);
      return;
    case 2u:
      cmpNmlSeqViewerStepUpdate(wk);
      cmpViewerModel(wk);
      return;
    case 3u:
      if (Update())
        return;
      wk->mode = 1;
      wk->step = 1;
      break;
    case 4u:
      cmpNmlSeqChangeStepUpdate(wk);
      return;
    case 5u:
      cmpNmlSeqSwordStepUpdate(wk);
      return;
    case 6u:
      cmpNmlSeqSwordMvStepUpdate(wk);
      return;
    case 9u:
      wk->noStatusDraw = 0;
      return;
    case 0xAu:
      cmpNmlSeqSwordSelStepUpdate(wk);
      return;
    default:
      goto LABEL_34;
  }
}

// 0x209f990
void cmpNmlSeqWaitStepUpdate(tagCMP_STATUS_WORK *wk) {
  s64 type;
  s32 v6;

  if ((wk->flags & 0x400000) != 0)
  {
    wk->flags &= 0xFFFFFFFFFBBFFFFFLL;
    cmpSetFlagDraw(1);
    cmpClearDat();
    wk->step = 4;
    type = wk->type;
    *(u64 *)&wk->sMov.x = 0;
    wk->sMov.z = 0.0;
    wk->mode = 1;
    wk->equipEnd = 0;
    if (type == 0x110040100LL || type == 17039361)
    {
      if ((wk->flags & 0x40000000) != 0)
        v6 = 32;
      else
        v6 = 16;
      wk->mode = v6;
    }
    return;
  }
}

// 0x209faf0
void cmpNmlSeqStatusStepUpdate(tagCMP_STATUS_WORK *wk) {
  s64 flags;
  s64 v5;
  f32 v7;
  s32 v8;
  s32 devilid;
  s32 v17;
  unsigned __int128 v18;

  v18 = 0u;
  if (tipsProcessCheck())
    return;
  if (wk->type == 17039361 && wk->statusGoSword && !wk->equipEnd && (wk->flags & 0x40000000) != 0)
  {
    wk->mode = 32;
    wk->step = 4;
    cmpClearDat();
    *(u64 *)&wk->sMov.x = 0;
    wk->sMov.z = 0.0;
  }
  if ((wk->flags & 0x4008000) == 0x8000 && CHECK_TRIG(4097, 1) && !wk->modeSq)
  {
    flags = wk->flags;
    if ((flags & 0x40000000) != 0)
    {
      wk->equipEnd = 0;
      wk->mode = 32;
      wk->step = 4;
    }
    else
    {
      wk->flags = flags | 0x4000000;
      SE(1);
    }
  }
  v5 = wk->flags;
  if ((v5 & 0x4000000) != 0)
  {
    v5 = wk->flags;
    *(u64 *)&wk->sMov.x = 0;
    wk->sMov.z = 0.0;
    wk->flags = v5 & 0xFFFFFFFFFBFFFFFFLL;
    v8 = 8;
    goto LABEL_36;
  }
  if ((v5 & 0x4000) != 0)
  {
    if (CHECK_TRIG(43021, 1))
    {
      if (!cmpGetModeSq() && (wk->flags & 0x100000000LL) == 0)
        goto LABEL_29;
    }
    if (CHECK_TRIG(41741, 1))
    {
      if (!cmpGetModeSq() && (wk->flags & 0x100000000LL) != 0 && !CHECK_PRESS(45059, 1) && !wk->statusGoSword)
      {
LABEL_29:
        if (cmpCheckHandle())
        {
          cmpGetPos(&v18);
          v7 = *(f32 *)&v18;
          *(u64 *)&wk->sMov.y = 0;
          v8 = 2;
          wk->sMov.x = (f32)(0.0 - v7) / 10.0;
LABEL_36:
          wk->mode = v8;
          wk->step = 4;
          return;
        }
      }
    }
    if (CHECK_TRIG(47363, 1) && (wk->flags & 0x100000000LL) == 0)
    {
      if (!cmpGetModeSq())
      {
        devilid = wk->unit->devilid;
        if (wk->unit->devilid && (devilid < 80 || (u32)(devilid - 337) < 0x40 || (u32)(devilid - 496) <= 5))
        {
          if (devilid >= 496)
          {
            v17 = devilid - 208;
          }
          else if (devilid >= 336)
          {
            v17 = devilid - 112;
          }
          else
          {
            v17 = devilid + 149;
          }
        }
        else
        {
          v17 = 149;
        }
        fclStart1(v17, 1);
        wk->mode = 4;
        wk->step = 3;
        return;
      }
    }
  }
  if (cmpSetSkillNow())
    goto LABEL_51;
LABEL_58:
  if (!cmpChgSkillNow())
    return;
  goto LABEL_59;
LABEL_51:
  cmpSkillSetUnity(wk);
  goto LABEL_58;
LABEL_59:
  cmpSklChangeUpdate(wk);
}

// 0x209ff30
void cmpNmlSeqViewerStepUpdate(tagCMP_STATUS_WORK *wk) {
  Il2CppObject *Instance;
  sdfVector4_t v5;
  f32 z;
  s32 v15;
  sdfVector4_t v16;
  sdfVector4_t a_pos;

  *(u64 *)&a_pos.x = 0;
  *(u64 *)&a_pos.z = 0;
  Instance = _get_Instance();
  StatusUiViewerOff(Instance, 0);
  if (CHECK_TRIG(4097, 1))
  {
    cmpClrRot();
    cmpGetPos(&a_pos);
    v16 = a_pos;
    vct_B = v16;
    cmpGetPosStatus(&a_pos);
    v5 = a_pos;
    vct_A = v5;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    _Q0 = vct_A;
    wk->mode = 1;
    wk->step = 4;
    a_pos = _Q0;
    __asm { FMOV            V0.2S, #10.0 }
    z = a_pos.z;
    *(float32x2_t *)&wk->sMov.x = vdiv_f32(*(float32x2_t *)&a_pos.x, *(float32x2_t *)&_Q0.x);
    wk->sMov.z = z / 10.0;
    v15 = 1;
    gPosLimit = 0;
    goto LABEL_22;
  }
  if (!CHECK_TRIG(41730, 1))
    return;
  cmpClearDat();
  cmpGetPosStatus(&a_pos);
  cmpAddPos(-a_pos.x, 0.0, 0.0);
  v15 = 0;
  wk->sMov.x = 0.0;
LABEL_22:
  SE(v15);
}

// 0x20a0270
void cmpNmlSeqGuideStepUpdate(tagCMP_STATUS_WORK *wk) {
  if (!Update())
  {
    wk->mode = 1;
    wk->step = 1;
  }
}

// 0x20a02b0
void cmpNmlSeqChangeStepUpdate(tagCMP_STATUS_WORK *wk) {
  f32 x;
  f32 y;
  f32 z;
  s32 count;
  s32 mode;
  s8 v11;

  x = wk->sMov.x;
  y = wk->sMov.y;
  z = wk->sMov.z;
  cmpAddPos(x, y, z);
  count = wk->count;
  if (count < 9)
  {
    wk->count = count + 1;
    return;
  }
  mode = wk->mode;
  wk->count = 0;
  if (mode <= 2)
  {
    if (mode != 1)
    {
      if (mode != 2)
        return;
      wk->step = 2;
      gPosLimit = 1;
      return;
    }
    wk->step = 1;
    gPosLimit = 0;
    return;
  }
  if (mode != 8)
  {
    if (mode != 16)
    {
      if (mode != 32)
        return;
      wk->iMoveCnt = 8;
      gPosLimit = 0;
      v11 = 10;
LABEL_35:
      wk->step = v11;
      wk->iDspCnt = 0;
      cmpSetEvent(0);
      return;
    }
    gPosLimit = 0;
    v11 = 5;
    goto LABEL_35;
  }
  cmpFuncEnd(wk);
  wk->step = 9;
}

// 0x20a0600
void cmpNmlSeqSwordStepUpdate(tagCMP_STATUS_WORK *wk) {
  s64 flags;
  s64 v4;
  s32 eEvent;

  if ((wk->flags & 0x4008000) == 0x8000 && CHECK_TRIG(4097, 1))
  {
    flags = wk->flags;
    if ((flags & 0x40000000) != 0)
    {
      cmpSetEvent(0);
      wk->step = 10;
      v4 = wk->flags;
      if ((v4 & 0x4000000) == 0)
        goto LABEL_8;
      goto LABEL_16;
    }
    wk->flags = flags | 0x4000000;
    SE(1);
  }
  v4 = wk->flags;
  if ((v4 & 0x4000000) == 0)
  {
LABEL_8:
    eEvent = wk->eEvent;
    switch (eEvent)
    {
      case 5:
        cmpSetEvent(0);
        wk->step = 10;
        break;
      case 3:
        wk->mode = 1;
        wk->step = 1;
        cmpSetEvent(0);
        break;
      case 2:
        wk->equipEnd = 1;
        wk->step = 6;
        wk->iMoveCnt = 8;
        break;
    }
    return;
  }
LABEL_16:
  v4 = wk->flags;
  *(u64 *)&wk->sMov.x = 0;
  wk->sMov.z = 0.0;
  wk->flags = v4 & 0xFFFFFFFFFBFFFFFFLL;
  wk->mode = 8;
  wk->step = 4;
}

// 0x20a07a0
void cmpNmlSeqSwordSelStepUpdate(tagCMP_STATUS_WORK *wk) {
  s64 flags;
  sdatUnitWork_t *para;
  s32 *param;
  s64 v11;
  s8 v13;

  wk->noStatusDraw = 1;
  flags = wk->flags;
  wk->equipEnd = 0;
  if ((flags & 0x4008000) != 0x8000)
    goto LABEL_20;
  if (itfMenuGetCtrlType(g_listPID) != 5)
    goto LABEL_20;
  if (!wk->statusGoSword)
  {
    v11 = wk->flags & 0xFFFFFFFFBBFFFFFFLL | 0x4000000;
    wk->flags = v11;
    if ((v11 & 0x4000000) == 0)
      goto LABEL_21;
LABEL_26:
    v11 = wk->flags;
    *(u64 *)&wk->sMov.x = 0;
    wk->flags = v11 & 0xFFFFFFFFFBFFFFFFLL;
    v13 = 4;
    wk->sMov.z = 0.0;
    wk->mode = 8;
    goto LABEL_29;
  }
  cmpRaidouBackChange(2);
  TitleChange(3);
  *(u16 *)&wk->noStatusDraw = 0;
  wk->flags &= ~0x40000000u;
  wk->mode = 1;
  wk->step = 4;
  para = GBWK->player->para;
  Start();
  SetType(0x1000000, GBWK->player->swordno, 0);
  param = wk->param;
  *(u64 *)param = 0;
  *(u64 *)&param[2] = 0;
  cmpClearDat();
  *(u64 *)&wk->sMov.x = 0;
  wk->sMov.z = 0.0;
LABEL_20:
  v11 = wk->flags;
  if ((v11 & 0x4000000) != 0)
    goto LABEL_26;
LABEL_21:
  if (wk->eEvent != 5)
    return;
  wk->noStatusDraw = 0;
  cmpSetEvent(0);
  v13 = 5;
LABEL_29:
  wk->step = v13;
}

// 0x20a0a40
void cmpNmlSeqSwordMvStepUpdate(tagCMP_STATUS_WORK *wk) {
  s32 v3;
  sdatPlayerUnitWork_t *player;
  s32 *param;
  u8 *sword_new;
  sdatPlayerUnitWork_t *v11;
  s32 swordno;
  Il2CppObject *Instance;

  v3 = wk->iMoveCnt - 4;
  wk->iMoveCnt = v3;
  if (!v3)
  {
    datSetPlayerSword(g_equipNo, 0);
    player = wk->player;
    wk->mode = 1;
    wk->step = 4;
    ClassCopy(player, GBWK->player, 0);
    param = wk->param;
    *(u64 *)param = 0;
    *(u64 *)&param[2] = 0;
    sword_new = wk->sword_new;
    v11 = GBWK->player;
    swordno = v11->swordno;
    LODWORD(v11) = v11->swordatk;
    wk->swordno = swordno;
    wk->swordatk = (s32)v11;
    cmpGetSwordParam(swordno, sword_new);
    ClassCopy(wk->unit, GBWK->player->para, 0);
    SE(57);
    cmpSetEvent(0);
    Instance = _get_Instance();
    AllGaugeOff(Instance[8].monitor, 0);
    cmpLastParClear();
    return;
  }
}

// 0x20a1ab0
void cmpSyougouSet(tagCMP_STATUS_WORK *wk) {
  s32 modeSq;

  modeSq = wk->modeSq;
  if (modeSq != 1)
  {
    if (modeSq != 2)
      return;
    if (CHECK_TRIG(4096, 1))
    {
      if (!cmpMemSet())
        return;
      SE(0);
      return;
    }
  }
  if (CHECK_TRIG(4097, 1))
  {
    wk->modeSq = 0;
    cmpSetSkillMode(0);
    SE(1);
  }
}

// 0x20a2410
void cmpSpiritSet(tagCMP_STATUS_WORK *wk) {
  s32 modeSq;
  s32 v4;

  modeSq = wk->modeSq;
  if (modeSq == 1)
  {
    if (CHECK_TRIG(4096, 1))
    {
      v4 = 2;
      goto LABEL_20;
    }
    if (CHECK_TRIG(4097, 1))
    {
      wk->modeSq = 0;
      cmpSetSkillMode(0);
      SE(1);
    }
  }
  else
  {
    if (modeSq != 2)
      return;
    if (CHECK_TRIG(4096, 1))
    {
      if (!cmpMemSet())
        return;
      v4 = 1;
LABEL_20:
      wk->modeSq = v4;
      SE(0);
      return;
    }
    if (CHECK_TRIG(4097, 1))
    {
      wk->modeSq = 1;
      SE(1);
    }
  }
}

// 0x20a2560
void cmpBtlCommandSet(tagCMP_STATUS_WORK *wk) {
  s32 commandCsr;
  s32 v5;
  s32 CombiSkillSetting;
  char *v7;
  Il2CppObject *Instance;

  if (!CHECK_TRIG(4097, 1))
  {
    if (wk->modeSq == 1)
      goto LABEL_4;
    return;
  }
  wk->modeSq = 0;
  cmpSetSkillMode(0);
  SE(1);
  if (wk->modeSq == 1)
  {
LABEL_4:
    commandCsr = wk->commandCsr;
    if (datGetCombiSkillSetting(commandCsr))
    {
      v5 = wk->commandCsr;
      CombiSkillSetting = datGetCombiSkillSetting(v5);
      v7 = sdatSkillHelp(CombiSkillSetting, 1);
      goto LABEL_18;
    }
    v7 = "SKILLHELP_L0000";
LABEL_18:
    Instance = _get_Instance();
    HelpTextDraw(Instance, v7, 1, 0xA09DC380, 0);
  }
}

// 0x20a0c30
void cmpSkillSetUnity(tagCMP_STATUS_WORK *wk) {
  s32 modeSq;
  s32 sklType_r;

  if (wk->unit->devilid)
  {
    modeSq = wk->modeSq;
    if (modeSq == 1)
    {
      if (CHECK_TRIG(4096, 1))
      {
        wk->modeSq = 2;
        SE(0);
      }
      else if (CHECK_TRIG(4097, 1))
      {
        wk->modeSq = 0;
        cmpSetSkillMode(0);
        SE(1);
      }
    }
    else
    {
      if (modeSq != 2)
        return;
      if (CHECK_TRIG(4096, 1))
      {
        if (!cmpMemSet())
          return;
        wk->modeSq = 1;
        SE(0);
        return;
      }
      if (CHECK_TRIG(4097, 1))
      {
        wk->modeSq = 1;
        SE(1);
      }
    }
  }
  else
  {
    sklType_r = wk->sklType_r;
    if (sklType_r == 1)
    {
      cmpSpiritSet(wk);
    }
    else if (!sklType_r)
    {
      cmpSyougouSet(wk);
    }
  }
}

// 0x209a970
void cmpSklChangeUpdate(tagCMP_STATUS_WORK *wk) {
  s32 sklChgSeq;

  if (wk->modeSq != 1)
  {
    LogError("来ないはず", 0);
    wk->baseSkl = 0;
    wk->noSklHelp = 0;
    wk->baseSklIndex = -1;
    wk->sklChgSeq = 2;
    return;
  }
  sklChgSeq = wk->sklChgSeq;
  switch (sklChgSeq)
  {
    case 2:
      wk->sklChgSeq = 0;
      cmpChgSkillMode(0);
      break;
    case 1:
      cmpSklChgUpdate(wk);
      break;
    case 0:
      wk->sklChgSeq = 1;
      wk->noSklHelp = 1;
      break;
  }
}

// 0x209a1e0
bool cmpSklSwapBaseCheck(tagCMP_STATUS_WORK *wk) {
  s32 selSkl;
  bool result;
  s32 sklCsr;
  sdatUnitWork_t *unit;
  s32 sklType;
  void **p_sousaSkill;
  s32 v10;

  selSkl = wk->selSkl;
  result = 0;
  wk->baseSklIndex = -1;
  sklCsr = wk->sklCsr;
  wk->baseSkl = selSkl;
  wk->baseSklCsr = sklCsr;
  if (selSkl != -1 && selSkl != 149 && selSkl != 255)
  {
    if (!wk->unit->devilid)
    {
      if (selSkl && wk->sklType_r == 1)
      {
        cmpSetChgSklBaseIndex(wk);
        if (wk->baseSklIndex != -1)
          goto LABEL_32;
      }
      return 0;
    }
    if (wk->sklType == 2)
    {
      if (selSkl == 1408)
        return 0;
    }
    else if (!selSkl)
    {
      return 0;
    }
    unit = wk->unit;
    if (unit->devilid)
    {
      sklType = wk->sklType;
      if (sklType)
      {
        if (sklType == 2)
          p_sousaSkill = &unit->sousaSkill;
        else
          p_sousaSkill = &unit->aOmoideSkill;
      }
      else
      {
        p_sousaSkill = &unit->haveskill;
      }
      goto LABEL_31;
    }
    p_sousaSkill = &GBWK->player->spiritSkill;
LABEL_31:
    v10 = IndexOf_Int32Enum_(*p_sousaSkill, wk->baseSkl);
    wk->baseSklIndex = v10;
    if (v10 != -1)
    {
LABEL_32:
      SE(0);
      return 1;
    }
    return 0;
  }
  return result;
}

// 0x20a2c70
void cmpSetChgSklBaseIndex(tagCMP_STATUS_WORK *wk) {
  sdatUnitWork_t *unit;
  s32 sklType;
  SKLID **p_haveskill;
  SKLID **p_aOmoideSkill;
  void **p_sousaSkill;

  unit = wk->unit;
  if (unit->devilid)
  {
    sklType = wk->sklType;
    p_haveskill = &unit->haveskill;
    p_aOmoideSkill = &unit->aOmoideSkill;
    p_sousaSkill = &unit->sousaSkill;
    if (sklType != 2)
      p_sousaSkill = p_aOmoideSkill;
    if (!sklType)
      p_sousaSkill = p_haveskill;
  }
  else
  {
    p_sousaSkill = &GBWK->player->spiritSkill;
  }
  wk->baseSklIndex = IndexOf_Int32Enum_(*p_sousaSkill, wk->baseSkl);
}

// 0x20a2720
void cmpSklChgUpdate(tagCMP_STATUS_WORK *wk) {
  s32 baseSkl;
  s32 selSkl;
  sdatUnitWork_t *unit;
  s32 sklType;
  s32 v7;
  sdatUnitWork_t *v8;
  s64 v9;
  s64 m_Items;
  s32 v11;
  sdatUnitWork_t *stock_id;
  sdatUnitWork_t *v14;
  SKLID *sousaSkill;
  void *aOmoideSkill;
  s32 v18;
  s32 v19;
  s64 v21;
  s64 v22;
  s32 v23;
  s32 v24;
  sdatUnitWork_t *v25;
  s64 v26;
  s64 v27;
  s32 v28;
  sdatUnitWork_t *v30;
  sdatUnitWork_t *v31;
  s32 v32;
  sdatUnitWork_t *v33;
  s64 v34;
  s64 v35;
  s32 v36;
  sdatUnitWork_t *v38;
  s32 StockDevilIndex;
  s32 v40;
  s32 v41;
  sdatUnitWork_t *v42;
  s64 v43;
  s64 v44;
  s64 v45;
  s32 v46;
  sdatUnitWork_t *v48;
  s32 v49;

  ButtonLineHelpDispSet(1);
  ButtonLineHelpTextSet("CMP_HELP_L0035", 0, 1, 0xA09DC380, 1);
  if (CHECK_TRIG(4097, 1))
  {
    wk->baseSkl = 0;
    wk->baseSklIndex = -1;
    wk->sklChgSeq = 2;
    wk->noSklHelp = 0;
    SE(1);
  }
  if (CHECK_TRIG(4096, 1))
  {
    baseSkl = wk->baseSkl;
    if (baseSkl != -1 && baseSkl != 149 && baseSkl != 1408)
    {
      selSkl = wk->selSkl;
      if (selSkl != -1 && selSkl != 149 && selSkl != 1408 && baseSkl != selSkl)
      {
        unit = wk->unit;
        if (unit->devilid)
        {
          sklType = wk->sklType;
          if (sklType == 2)
          {
            v7 = IndexOf_Int32Enum_(unit->sousaSkill, selSkl);
            if (v7 == -1)
              return;
            v8 = wk->unit;
            v9 = 4 * v7;
            m_Items = v8->sousaSkill;
            v11 = *(u32 *)(m_Items + v9);
            *(u32 *)(m_Items + v9) = *(u32 *)(m_Items + 4 * wk->baseSklIndex);
            *(u32 *)(m_Items + 4 * wk->baseSklIndex) = v11;
            v8 = wk->unit;
            stock_id = GBWK->player->stock_id;
            v14 = stock_id[datGetStockDevilIndex(v8->devilid, v8->uniq_code)];
            sousaSkill = wk->unit->sousaSkill;
            aOmoideSkill = v14->sousaSkill;
LABEL_37:
            Copy_56180528(sousaSkill, aOmoideSkill, sousaSkill->max_length, 0);
            goto LABEL_38;
          }
          if (!baseSkl || !selSkl)
            return;
          if (sklType)
          {
            v24 = IndexOf_Int32Enum_(unit->aOmoideSkill, selSkl);
            if (v24 == -1)
              return;
            v25 = wk->unit;
            v26 = 4 * v24;
            v27 = v25->aOmoideSkill;
            v28 = *(u32 *)(v27 + v26);
            *(u32 *)(v27 + v26) = *(u32 *)(v27 + 4 * wk->baseSklIndex);
            *(u32 *)(v27 + 4 * wk->baseSklIndex) = v28;
            v25 = wk->unit;
            v30 = GBWK->player->stock_id;
            v31 = v30[datGetStockDevilIndex(v25->devilid, v25->uniq_code)];
            sousaSkill = wk->unit->aOmoideSkill;
            aOmoideSkill = v31->aOmoideSkill;
            goto LABEL_37;
          }
          if (wk->rsvCsr != -1)
            return;
          v32 = IndexOf_Int32Enum_(unit->haveskill, selSkl);
          if (v32 != -1)
          {
            v33 = wk->unit;
            v34 = 4 * v32;
            v35 = v33->haveskill;
            v36 = *(u32 *)(v35 + v34);
            *(u32 *)(v35 + v34) = *(u32 *)(v35 + 4 * wk->baseSklIndex);
            *(u32 *)(v35 + 4 * wk->baseSklIndex) = v36;
            v33 = wk->unit;
            v38 = GBWK->player->stock_id;
            StockDevilIndex = datGetStockDevilIndex(v33->devilid, v33->uniq_code);
            Copy_56180528(wk->unit->haveskill, v38[StockDevilIndex]->haveskill, wk->unit->haveskill->max_length, 0);
          }
          v40 = IndexOf_Int32Enum_(wk->unit->battleskill, wk->selSkl);
          v41 = IndexOf_Int32Enum_(wk->unit->battleskill, wk->baseSkl);
          if (v40 != -1 && v41 != -1)
          {
            v42 = wk->unit;
            v43 = 4 * v40;
            v44 = 4 * v41;
            v45 = v42->battleskill;
            v46 = *(u32 *)(v45 + v43);
            *(u32 *)(v45 + v43) = *(u32 *)(v45 + v44);
            *(u32 *)(v45 + v44) = v46;
            v42 = wk->unit;
            v48 = GBWK->player->stock_id;
            v49 = datGetStockDevilIndex(v42->devilid, v42->uniq_code);
            Copy_56180528(wk->unit->battleskill, v48[v49]->battleskill, wk->unit->battleskill->max_length, 0);
          }
          if (v32 == -1)
            return;
        }
        else
        {
          selSkl = wk->selSkl;
          v18 = IndexOf_Int32Enum_(GBWK->player->spiritSkill, selSkl);
          if (v18 == -1)
            return;
          v19 = v18;
          v21 = 4 * v19;
          v22 = GBWK->player->spiritSkill;
          v23 = *(u32 *)(v22 + v21);
          *(u32 *)(v22 + v21) = *(u32 *)(v22 + 4 * wk->baseSklIndex);
          *(u32 *)(v22 + 4 * wk->baseSklIndex) = v23;
        }
LABEL_38:
        wk->baseSkl = 0;
        wk->baseSklIndex = -1;
        wk->sklChgSeq = 2;
        wk->noSklHelp = 0;
        SE(0);
      }
    }
  }
}

// 0x20a2c50
void cmpEndChgSklMode(tagCMP_STATUS_WORK *wk) {
  wk->baseSkl = 0;
  wk->noSklHelp = 0;
  wk->baseSklIndex = -1;
  wk->sklChgSeq = 2;
}

// 0x20a2d40
void cmpChangeWaitMode(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  HIDWORD(ProcessData[2].monitor) = 16;
  LOBYTE(ProcessData[2].klass) = 4;
  cmpClearDat();
}

// 0x20a2ea0
void cmpSeqMemSet(tagCMP_STATUS_WORK *wk) {
  _get_Instance();
  switch (wk->step)
  {
    case 0:
      cmpMemSetWaitStepUpdate(wk);
      break;
    case 1:
      cmpMemSetSeqStatusStepUpdate(wk);
      break;
    case 4:
      cmpMemSetChangeStepUpdate(wk);
      break;
    case 7:
      cmpMemSetMesWaitStepUpdate(wk);
      break;
    case 8:
      cmpMemSetMesEndStepUpdate(wk);
      break;
    case 9:
      wk->flags &= ~0x8000u;
      break;
    default:
      return;
  }
}

// 0x20a3070
void cmpMemSetWaitStepUpdate(tagCMP_STATUS_WORK *wk) {
  s64 type;

  if ((wk->flags & 0x400000) == 0)
    return;
  wk->flags &= 0xFFFFFFFFFBBFFFFFLL;
  cmpSetFlagDraw(1);
  cmpClearDat();
  wk->step = 4;
  type = wk->type;
  *(u64 *)&wk->sMov.x = 0;
  wk->sMov.z = 0.0;
  wk->mode = 1;
  if (type == 17039361)
  {
    wk->mode = 16;
    goto LABEL_12;
  }
  else
  {
LABEL_12:
    cmpSetEvent(0);
    return;
  }
  goto LABEL_12;
}

// 0x20a3200
void cmpMemSetMesWaitStepUpdate(tagCMP_STATUS_WORK *wk) {
  s32 eEvent;
  sdatUnitWork_t *unit;
  s32 iOmoideSkillCnt;
  s32 v6;
  sdatPlayerUnitWork_t *player;
  s32 v11;
  s32 v12;
  s32 v13;
  u32 v14;
  SKLID *spiritSkill;
  s32 v17;

  eEvent = wk->eEvent;
  if (!eEvent)
    return;
  if (eEvent == 3)
  {
    cmpSetEvent(0);
    wk->modeSq = 0;
    wk->type = 0;
    wk->step = 8;
    return;
  }
  cmpSetEvent(0);
  wk->modeSq = 2;
  wk->step = 1;
  wk->type = 0x8000000;
  unit = wk->unit;
  if (!unit->devilid)
  {
    player = GBWK->player;
    v11 = player->spiritCnt - 1;
    if (v11 >= 7)
      v12 = 7;
    else
      v12 = player->spiritCnt - 1;
    player = GBWK->player;
    v13 = IndexOf_Int32Enum__39255936(player->spiritSkill, 0, 0, v12);
    if (v13 != -1)
    {
      wk->sklCsr = v13;
      return;
    }
    if (v12 < 0)
      return;
    v14 = v12;
    spiritSkill = GBWK->player->spiritSkill;
    if (spiritSkill[v12])
      goto LABEL_49;
    if (v11 < 1)
      return;
    v14 = v12 - 1;
    if (spiritSkill[v12 - 1])
      goto LABEL_49;
    v14 = v12 - 2;
    if (v12 < 2)
      return;
    if (spiritSkill[v14])
      goto LABEL_49;
    v14 = v12 - 3;
    if (v12 < 3)
      return;
    if (spiritSkill[v14])
      goto LABEL_49;
    v14 = v12 - 4;
    if (v12 < 4)
      return;
    if (spiritSkill[v14])
      goto LABEL_49;
    v14 = v12 - 5;
    if (v12 < 5)
      return;
    if (spiritSkill[v14])
      goto LABEL_49;
    v14 = v12 - 6;
    if (v12 < 6)
      return;
    if (spiritSkill[v14])
      goto LABEL_49;
    v14 = v12 - 7;
    if (v12 < 7)
      return;
    if (!spiritSkill[v14])
      return;
LABEL_49:
    wk->sklCsr = v14;
    v17 = v14;
LABEL_47:
    cmpLearnSkl(0, 1, v17, 0);
    return;
  }
  iOmoideSkillCnt = unit->iOmoideSkillCnt;
  v6 = IndexOf_Int32Enum__39255936(unit->aOmoideSkill, 0, 0, iOmoideSkillCnt - 1);
  if (v6 != -1)
  {
    wk->sklCsr = v6;
    return;
  }
  if (iOmoideSkillCnt >= 1)
  {
    while (!wk->unit->aOmoideSkill[--iOmoideSkillCnt])
    {
      if (iOmoideSkillCnt <= 0)
        return;
    }
    wk->sklCsr = iOmoideSkillCnt;
    v17 = iOmoideSkillCnt;
    goto LABEL_47;
  }
}

// 0x20a36c0
void cmpMemSetSeqStatusStepUpdate(tagCMP_STATUS_WORK *wk) {
  s32 devilid;
  Il2CppObject *Instance;
  s64 v5;
  sdatUnitWork_t *unit;
  void *castClass;
  s32 iOmoideSkillCnt;
  s32 Count;
  sdatUnitWork_t *v10;
  SKLID **p_aOmoideSkill;
  SKLID *v12;
  s32 sklCsr;
  s32 v15;
  s32 v16;
  s32 max_length;
  s32 v18;
  s64 v19;
  s32 *v20;
  sdatPlayerUnitWork_t *player;
  s32 spiritCnt;
  s32 v25;
  bool v26;
  s32 modeSq;
  Il2CppObject *Item;
  s32 v31;
  s32 v37;
  s32 v38;
  s64 v39;
  s64 v40;
  s32 v41;
  s64 v42;
  int32x4_t v44;
  s64 v45;
  s64 v46;
  int32x4_t *v47;
  s64 v48;
  int32x4_t v49;
  int32x4_t v50;
  int32x4_t v51;
  int32x4_t v52;
  int32x4_t v53;
  int32x4_t v54;
  int32x4_t v55;
  s32 v56;
  s32 *v57;

  devilid = (u16)wk->unit->devilid;
  Instance = _get_Instance();
  v5 = 10;
  if (!devilid)
    v5 = 8;
  if ((wk->flags & 0x4008000) != 0x8000)
    goto LABEL_89;
  unit = wk->unit;
  castClass = Instance[v5].klass->_1.castClass;
  if (unit->devilid)
  {
    iOmoideSkillCnt = unit->iOmoideSkillCnt;
    Count = datOmoideSkillGetCount(unit);
    if (Count < iOmoideSkillCnt)
      iOmoideSkillCnt = Count;
    if (CHECK_TRIG(4096, 1))
      goto LABEL_12;
LABEL_34:
    v26 = CHECK_TRIG(4097, 1);
    modeSq = wk->modeSq;
    if (v26)
    {
      if (modeSq == 2)
      {
        cmpSklCsrL();
        cmpLearnSkl(0, 1, wk->sklCsr, 0);
        Item = _get_Item(castClass, wk->sklCsr);
        (*(*(u64 *)Item[2].monitor + 1368))(Item[2].monitor, 0, *(u64 *)(*(u64 *)Item[2].monitor + 1376));
        v31 = 1;
      }
      else
      {
        v31 = 1;
        wk->flags |= 0x4000000u;
      }
      goto LABEL_88;
    }
    if (modeSq == 2)
    {
      cmpMemSklCurUpdate();
    }
    else
    {
      if (CHECK_TRIG(4100, 1) || CHECK_REP(4100, 1))
      {
        cmpSklCsrU();
      }
      else if (CHECK_TRIG(4101, 1) || CHECK_REP(4101, 1))
      {
        cmpSklCsrD();
      }
      else if (CHECK_TRIG(4102, 1) || CHECK_REP(4102, 1))
      {
        cmpSklCsrL();
      }
      else if (CHECK_TRIG(4103, 1) || CHECK_REP(4103, 1))
      {
        cmpSklCsrR();
      }
    }
    goto LABEL_89;
  }
  player = GBWK->player;
  spiritCnt = player->spiritCnt;
  v25 = datSpiritSkillGetCount(player);
  if (spiritCnt >= v25)
    iOmoideSkillCnt = v25;
  else
    iOmoideSkillCnt = spiritCnt;
  if (!CHECK_TRIG(4096, 1))
    goto LABEL_34;
LABEL_12:
  v10 = wk->unit;
  if (v10->devilid)
  {
    p_aOmoideSkill = &v10->aOmoideSkill;
    if (wk->modeSq == 2)
      goto LABEL_14;
LABEL_46:
    wk->modeSq = 2;
    goto LABEL_89;
  }
  p_aOmoideSkill = &GBWK->player->spiritSkill;
  if (wk->modeSq != 2)
    goto LABEL_46;
LABEL_14:
  v12 = *p_aOmoideSkill;
  if (cmpMemSet())
  {
    sklCsr = wk->sklCsr;
    v15 = iOmoideSkillCnt - 1;
    if (sklCsr >= iOmoideSkillCnt - 1)
    {
      wk->flags |= 0x4000000u;
LABEL_87:
      v31 = 0;
LABEL_88:
      SE(v31);
      goto LABEL_89;
    }
    v16 = sklCsr + 1;
    if (v12[sklCsr + 1])
    {
      max_length = v12->max_length;
      if (sklCsr < max_length)
      {
        if (sklCsr <= v15)
          v18 = iOmoideSkillCnt - 1;
        else
          v18 = wk->sklCsr;
        v19 = v18 - (s64)sklCsr;
        v20 = &v12[sklCsr];
        while (1)
        {
          if (!*v20++)
          {
            wk->sklCsr = sklCsr;
            SE(3);
            goto LABEL_84;
          }
          if (!v19)
            break;
          ++sklCsr;
          --v19;
          if (max_length == sklCsr)
            goto LABEL_84;
        }
        wk->sklCsr = v15;
        wk->flags |= 0x4000000u;
      }
      goto LABEL_84;
    }
    v37 = v12->max_length;
    v38 = sklCsr + 2;
    if (sklCsr + 2 >= v37)
    {
      v41 = 0;
    }
    else
    {
      v39 = v38;
      v40 = (u32)(v37 - sklCsr - 3);
      if ((u32)v40 < 0xF)
      {
        v41 = 0;
        v42 = v38;
        goto LABEL_75;
      }
      v44 = 0u;
      v45 = v40 + 1;
      v46 = (v40 + 1) & 0x1FFFFFFF0LL;
      v42 = v46 + v39;
      v47 = &v12[v39 + 12];
      v48 = v46;
      v49 = 0u;
      v50 = 0u;
      v51 = 0u;
      do
      {
        v48 -= 16;
        v52 = vtstq_s32(v47[-2], v47[-2]);
        v53 = vtstq_s32(v47[-3], v47[-3]);
        v54 = vtstq_s32(v47[-1], v47[-1]);
        v55 = vtstq_s32(*v47, *v47);
        v47 += 4;
        v49 = vsubq_s32(v49, v52);
        v51 = vsubq_s32(v51, v55);
        v44 = vsubq_s32(v44, v53);
        v50 = vsubq_s32(v50, v54);
      }
      while (v48);
      v41 = vaddvq_s32(vaddq_s32(vaddq_s32(v51, v50), vaddq_s32(v49, v44)));
      if (v45 != v46)
      {
LABEL_75:
        v56 = v37 - v42;
        v57 = &v12[v42];
        do
        {
          if (*v57++)
            ++v41;
          --v56;
        }
        while (v56);
      }
    }
    if (v15 < v41 + v16)
    {
      wk->sklCsr = v15;
      wk->flags |= 0x4000000u;
    }
    cmpSklCsrR();
LABEL_84:
    cmpMemSklAutoCurNext();
    goto LABEL_87;
  }
LABEL_89:
  if ((wk->flags & 0x4000000) != 0)
  {
    ClassCopy(wk->pUnitDst, wk->unit, 0);
    wk->modeSq = 0;
    wk->type = 0;
    wk->step = 8;
  }
}

// 0x20a3c50
void cmpMemSetMesEndStepUpdate(tagCMP_STATUS_WORK *wk) {
  s32 devilid;
  Il2CppObject *Instance;
  s64 v7;
  s32 eEvent;
  s64 v9;
  s64 flags;
  void *castClass;
  s32 sklCsr;
  Il2CppObject *Item;

  devilid = (u16)wk->unit->devilid;
  Instance = _get_Instance();
  v7 = 10;
  if (!devilid)
    v7 = 8;
  eEvent = wk->eEvent;
  switch (eEvent)
  {
    case 5:
      cmpSetEvent(0);
      flags = wk->flags;
      wk->step = 0;
      wk->flags = flags & 0xFFFFFFFFFFFF7FFFLL;
      break;
    case 4:
      castClass = Instance[v7].klass->_1.castClass;
      sklCsr = wk->sklCsr;
      cmpLearnSkl(0, 1, sklCsr, 0);
      Item = _get_Item(castClass, wk->sklCsr);
      (*(*(u64 *)Item[2].monitor + 1368))(Item[2].monitor, 0, *(u64 *)(*(u64 *)Item[2].monitor + 1376));
      cmpSetEvent(0);
      wk->step = 1;
      wk->modeSq = 2;
      wk->type = 0x8000000;
      wk->flags &= ~0x4000000u;
      break;
    case 2:
      cmpSetEvent(0);
      v9 = wk->flags;
      *(u64 *)&wk->sMov.x = 0;
      wk->sMov.z = 0.0;
      wk->mode = 8;
      wk->flags = v9 & 0xFFFFFFFFFBFFFFFFLL;
      wk->step = 4;
      break;
  }
}

// 0x20a3e20
void cmpMemSetChangeStepUpdate(tagCMP_STATUS_WORK *wk) {
  f32 x;
  f32 y;
  f32 z;
  s32 count;
  s32 mode;

  x = wk->sMov.x;
  y = wk->sMov.y;
  z = wk->sMov.z;
  cmpAddPos(x, y, z);
  count = wk->count;
  if (count < 9)
  {
    wk->count = count + 1;
    return;
  }
  mode = wk->mode;
  wk->count = 0;
  if (mode == 8)
  {
    cmpFuncEnd(wk);
    wk->step = 9;
  }
  else if (mode == 1)
  {
    wk->modeSq = 0;
    wk->step = 7;
    gPosLimit = 0;
    return;
  }
}

// 0x20a41b0
void cmpSeqGoodby(tagCMP_STATUS_WORK *wk) {
  s32 v6;
  bool v7;
  s32 v11;
  s8 v12;
  s64 flags;
  f32 *v15;
  bool v16;
  f32 v18;
  f32 *v19;
  f32 v20;
  f32 v22;
  f32 v23;
  f32 *v27;
  f32 v28;
  s32 v29;
  s32 v30;
  f32 v32;
  f32 *v35;
  f32 v36;
  f32 v37;
  f32 v38;
  s32 v41;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 v50;
  f32 *v51;
  f32 v52;
  s64 v53;
  s32 v56;

  switch (wk->step)
  {
    case 0:
      if ((wk->flags & 0x400000) != 0)
      {
        wk->flags &= 0xFFFFFFFFFBBFFFFFLL;
        cmpSetFlagDraw(1);
        cmpClearDat();
        *(u64 *)&wk->sMov.x = 0;
        wk->sMov.z = 0.0;
        wk->step = 1;
      }
      return;
    case 1:
      if (cmpChkStatusModelLoadStat() == 1)
        return;
      if (cmpCheckHandle())
      {
        dds3FadeIn(0, 0, 0, 0xFu);
        aColorCnt = 0;
        cmpSetColor(0x80000000);
        (loc_20BD680)(1, 0);
        wk->mode = 1;
        wk->step = 4;
        aGoodbyCnt = 0;
        pos[0] = 0.0;
        v50 = cmpAdjustPosY_Gattai();
        v51 = pos;
        pos[1] = v50 + 0.0;
        v52 = v51[0];
        v53 = LODWORD(v51[1]);
        v51[2] = 150.0;
        cmpSetPos_GoodBy(v52, *(f32 *)&v53, 150.0);
        *(u64 *)rot = 0;
        rot[2] = 0.0;
        cmpSetRot_GoodBy(0.0, 0.0, 0.0);
        v12 = 2;
        goto LABEL_97;
      }
      return;
    case 2:
      v6 = aColorCnt + 4;
      v7 = aColorCnt - 125 < 0;
      aColorCnt = v6;
      if (v7 == __OFSUB__(v6, 129))
        aColorCnt = 128;
      cmpSetColor((aColorCnt << 16) | (aColorCnt << 8) | aColorCnt | 0x80000000);
      v11 = aGoodbyCnt + 1;
      v7 = aGoodbyCnt - 30 < 0;
      aGoodbyCnt = v11;
      if (v7 == __OFSUB__(v11, 31))
      {
        if (aColorCnt == 128)
        {
          v12 = 3;
          goto LABEL_97;
        }
      }
      return;
    case 3:
      flags = wk->flags;
      if ((flags & 0x4000000) != 0)
      {
        flags = wk->flags;
        wk->flags = flags & 0xFFFFFFFFFBFFFFFFLL;
        v12 = 4;
        goto LABEL_97;
      }
      return;
    case 4:
      v15 = rot;
      if (v15[1] >= 180.0)
      {
        v15 = rot;
        v43 = v15[0];
        v44 = v15[2];
        cmpSetRot_GoodBy(v43, 180.0, v44);
        cmpSetSmoothLoopMotion(1, 6.0, 6.0);
        cmpSetMotionSpeed(1.0);
        v12 = 5;
        goto LABEL_97;
      }
      v16 = !scrIsEventSkip(0);
      if (v16)
        v18 = 10.0;
      else
        v18 = 30.0;
      v19 = rot;
      v20 = v19[0];
      v22 = v19[2];
      v23 = v18 + v19[1];
      v19[1] = v23;
      cmpSetRot_GoodBy(v20, v23, v22);
      return;
    case 5:
      v27 = pos;
      v28 = v27[2];
      if (v28 >= 1000.0)
      {
        v27 = pos;
        v28 = v27[2];
        v45 = v27[0];
        cmpSetPos_GoodBy(v45, 1000.0, v28);
        aGoodbyCnt = 0;
        dds3FadeOut(0, 0, 0, 0xFu);
        v12 = 6;
        goto LABEL_97;
      }
      v29 = aColorCnt - 2;
      aColorCnt = v29;
      if (v29 >= 0)
        goto LABEL_50;
      goto LABEL_9000;
      if (v56 >= 0)
      {
LABEL_50:
        goto LABEL_52;
      }
LABEL_9000:
      aColorCnt = 0;
LABEL_52:
      v30 = aColorCnt;
      cmpSetColor((v30 << 8) | (v30 << 16) | v30 | 0x80000000);
      v16 = !scrIsEventSkip(0);
      if (v16)
        v32 = 15.0;
      else
        v32 = 45.0;
      v35 = pos;
      v36 = v35[9];
      v37 = v35[8];
      v38 = v32 + v35[10];
      v35[10] = v38;
      cmpSetPos_GoodBy(v37, v36, v38);
      return;
    case 6:
      v41 = aGoodbyCnt + 1;
      v7 = aGoodbyCnt - 15 < 0;
      aGoodbyCnt = v41;
      if (v7 == __OFSUB__(v41, 16))
      {
        cmpFuncEnd(wk);
        v12 = 7;
LABEL_97:
        wk->step = v12;
      }
      return;
    case 7:
      g_GoodByModeZahyou = 0;
      return;
    default:
      return;
  }
}

// 0x20a49e0
void cmpSeqDvlReport(tagCMP_STATUS_WORK *wk) {
  s64 flags;

  switch (wk->step)
  {
    case 0:
      if ((wk->flags & 0x400000) != 0)
      {
        wk->flags &= 0xFFFFFFFFFBBFFFFFLL;
        cmpSetFlagDraw(1);
        cmpClearDat();
        *(u64 *)&wk->sMov.x = 0;
        wk->sMov.z = 0.0;
        wk->step = 1;
      }
      return;
    case 1:
      if (cmpChkStatusModelLoadStat() == 1)
        return;
      if (!cmpCheckHandle())
        return;
      g_GoodByModeZahyou = 1;
      wk->step = 2;
      return;
    case 2:
      flags = wk->flags;
      if ((flags & 0x4000000) != 0)
      {
        flags = wk->flags;
        *(u64 *)&wk->sMov.x = 0;
        wk->sMov.z = 0.0;
        wk->flags = flags & 0xFFFFFFFFFBFFFFFFLL;
        wk->mode = 8;
        wk->step = 4;
      }
      return;
    case 4:
      cmpFuncEnd(wk);
      wk->step = 5;
      return;
    case 5:
      wk->step = 0;
      g_GoodByModeZahyou = 0;
      wk->seqtype = -1;
      return;
    default:
      return;
  }
}

// 0x20a4cd0
void cmpSeqLevelUp(tagCMP_STATUS_WORK *wk) {
  s32 loadModelNo;
  s32 v4;
  s32 v6;
  s64 flags;
  sdatUnitWork_t *unit;
  s64 v13;

  if ((wk->flags & 0x200) != 0)
  {
    loadModelNo = wk->loadModelNo;
    if (loadModelNo < 1)
    {
      if (!loadModelNo)
      {
        sndVoicePlayFile("PVA01A_20B_000", 0);
        cmpSetSmoothSingleMotion(193, 0.0, 0.0);
        wk->lvUpVoice = 1;
      }
    }
    else
    {
      ModelLoadInitAction();
    }
  }
  switch (wk->step)
  {
    case 0:
      cmpLvUpSeqStartStepUpdate(wk);
      return;
    case 1:
      cmpLvUpSeqFadeInStepUpdate(wk);
      return;
    case 2:
      cmpLvUpSeqCallMesStepUpdate(wk);
      return;
    case 3:
      cmpLvUpSeqWaitMesStepUpdate(wk);
      return;
    case 4:
      cmpLvUpSeqCallParInStepUpdate(wk);
      return;
    case 5:
      cmpLvUpSeqSetParStepUpdate(wk);
      return;
    case 6:
      v4 = Update();
      if (v4 != 1)
      {
        if (!v4)
        {
          wk->count2 = -1;
          wk->step = 7;
        }
        return;
      }
      cmpResetParam(wk);
      wk->flags |= 0x2000u;
      wk->step = 5;
      return;
    case 7:
      cmpLvUpSeqCallParOutStepUpdate(wk);
      return;
    case 8:
      v6 = wk->count++;
      if (v6 >= 30)
      {
        wk->count = 0;
        wk->step = 9;
        wk->sklSpeedUp = 1;
      }
      return;
    case 9:
    case 0xB:
      goto LABEL_74;
    case 0xA:
      wk->step = 11;
      return;
    case 0xC:
      cmpLvUpSeqNmlSklItemMsgInitStepUpdate(wk);
      return;
    case 0xD:
      goto LABEL_65;
    case 0xE:
      cmpLvUpSeqOmoSklItemMsgInitStepUpdate(wk);
      return;
    case 0xF:
LABEL_65:
      if (!Update())
      {
        wk->step = 18;
        fclEndMessage();
      }
      return;
    case 0x10:
      wk->step = 17;
      return;
    case 0x11:
      flags = wk->flags;
      if ((flags & 0x40000) == 0)
      {
        if ((flags & 0x80000) == 0)
          goto LABEL_74;
        goto LABEL_73;
      }
      unit = wk->unit;
      flags |= 0x40000u;
      wk->flags = flags;
      unit->now->hp = unit->now->maxhp;
      if ((flags & 0x80000) != 0)
      {
LABEL_73:
        wk->flags = flags | 0x80000;
        wk->unit->now->mp = wk->unit->now->maxmp;
      }
LABEL_74:
      wk->step = 18;
      return;
    case 0x12:
      cmpSetFlagCtrlMode(1);
      cmpSetFlagNoExplan(1);
      if (wk->count2)
      {
        wk->count2 = 0;
        cmpFuncEnd(wk);
        wk->step = 21;
      }
      else
      {
        v13 = wk->flags;
        if ((v13 & 0x4000000) != 0)
        {
          v13 = wk->flags;
          wk->flags = v13 & 0xFFFFFFFFFBFFFFFFLL;
          wk->count2 = 1;
        }
      }
      return;
    case 0x13:
      cmpRstSeqViewerStepUpdate(wk);
      cmpViewerModel(wk);
      return;
    case 0x14:
      cmpRstSeqChangeStepUpdate(wk);
      return;
    case 0x15:
      wk->step = 0;
      wk->seqtype = -1;
      return;
    default:
      return;
  }
}

// 0x20a5370
void cmpLvUpSeqStartStepUpdate(tagCMP_STATUS_WORK *wk) {
  if ((wk->flags & 0x400000) == 0)
    return;
  wk->flags &= 0xFFFFFFFFFBBFFFFFLL;
  cmpSetFlagDraw(1);
  cmpSetFlagDraw(1);
  dds3FadeOut(0, 0, 0, 1u);
  wk->count2 = 0;
  wk->step = 1;
}

// 0x20a54a0
void cmpLvUpSeqFadeInStepUpdate(tagCMP_STATUS_WORK *wk) {
  s32 count2;
  bool v4;

  count2 = (u16)wk->count2;
  if (count2 == 15)
  {
    wk->count2 = 0;
    v4 = rstChkFlagPlayBgm();
    if (v4)
    {
      sndBgmTop();
      wk->step = 2;
    }
    else
    {
      sndBgmPlay(0, 0);
      rstSetFlagPlayBgm();
      wk->step = 2;
    }
  }
  else
  {
    if (!wk->count2)
    {
      dds3FadeIn(0, 0, 0, 0xFu);
      LOWORD(count2) = wk->count2;
    }
    wk->count2 = count2 + 1;
  }
}

// 0x20a55f0
void cmpLvUpSeqCallMesStepUpdate(tagCMP_STATUS_WORK *wk) {
  s32 lvUpVoice;
  sdatUnitWork_t *unit;
  s32 devilid;
  char *PlayerName;
  Il2CppObject *v7;
  char *v8;
  char *v9;
  sdatUnitWork_t *v11;
  s32 v12;
  s8 v13;
  s32 data;

  lvUpVoice = wk->lvUpVoice;
  if (wk->loadModelNo | lvUpVoice)
  {
    if (lvUpVoice != 1)
      goto LABEL_8;
    if (!sndVoiceStatus(0))
    {
LABEL_8:
      ClassCopy(wk->unit, wk->unitDst, 0);
      unit = wk->unit;
      wk->lvup_num = wk->unitDst->level - wk->unitSrc->level;
      if ((unit->flag & 2) != 0)
      {
        PlayerName = sBtlGetPlayerName();
        if (wk->lvup_num)
          goto LABEL_12;
      }
      else
      {
        devilid = unit->devilid;
        PlayerName = sdatDevilName(devilid, 0);
        if (wk->lvup_num)
        {
LABEL_12:
          Reset(0);
          fclSetMessageVar(0, PlayerName);
          data = wk->lvup_num;
          v7 = Box(s32, &data);
          v8 = Format("{0:D}", v7, 0);
          v9 = Concat_54766928(0, v8, 0);
          fclSetMessageVar(1, v9);
          v11 = wk->unit;
          if ((v11->flag & 2) == 0)
          {
            if (v11->devilid < 1)
            {
              v12 = 0;
              if (wk->lvup_num <= 0)
                goto LABEL_31;
            }
            else
            {
              v12 = cmpCalcRestParamDvl(wk);
              if (wk->lvup_num <= v12)
                goto LABEL_31;
            }
LABEL_30:
            wk->lvup_num = v12;
LABEL_31:
            fclStart1(1, 1);
            v13 = 3;
            goto LABEL_32;
          }
          v12 = cmpCalcRestParamPly(wk);
          if (wk->lvup_num <= v12)
            goto LABEL_31;
          goto LABEL_30;
        }
      }
      v13 = 18;
LABEL_32:
      wk->count2 = 0;
      wk->step = v13;
      wk->lvUpVoice = 0;
    }
  }
}

// 0x20a6d70
void cmpCreateNakamaLvUpParMes(tagCMP_STATUS_WORK *wk) {
  wk->count2 = 0;
  wk->step = 18;
}

// 0x20a58e0
void cmpLvUpSeqWaitMesStepUpdate(tagCMP_STATUS_WORK *wk) {
  void *Instance;
  void *v6;
  sdatUnitWork_t *unit;
  s32 v8;

  if (wk->step2 == 1)
    goto LABEL_8;
  if (Update())
  {
LABEL_5:
    if (wk->step2 != 1)
      return;
LABEL_8:
    wk->step = 3;
    fclEndMessage();
    if (tipsProcessCheck())
      return;
    Instance = get_Instance(0);
    ItfButtonGuideActive(Instance, 0, 0);
    wk->count2 = 0;
    wk->step = 18;
    wk->step2 = 0;
    return;
  }
  if (wk->step2 == 1)
    goto LABEL_8;
  if ((wk->unit->flag & 2) != 0)
  {
    if (wk->count2)
    {
      wk->count2 = -1;
      wk->step = 4;
      v6 = get_Instance(0);
      ItfButtonGuideSet(v6, 1, 0);
      goto LABEL_5;
    }
    unit = wk->unit;
    if ((unit->flag & 2) == 0)
    {
      if (unit->devilid < 1)
      {
LABEL_44:
        wk->count2 = 0;
        wk->step = 18;
        goto LABEL_5;
      }
      v8 = cmpCalcRestParamDvl(wk);
LABEL_42:
      if (v8 >= 1)
      {
        fclSetClsMode(1);
        fclStart1(3, 1);
        ++wk->count2;
        goto LABEL_5;
      }
      goto LABEL_44;
    }
    v8 = cmpCalcRestParamPly(wk);
    goto LABEL_42;
  }
  if (evtBitCheck(10013))
  {
    goto LABEL_44;
  }
  tipsTIPSStart(29);
  wk->step2 = 1;
}

// 0x20a5be0
void cmpLvUpSeqCallParInStepUpdate(tagCMP_STATUS_WORK *wk) {
  s32 v3;
  itfMover_t *mover;
  s32 v6;
  itfMover_t *v7;
  s64 flags;

  v3 = (u16)wk->count2++ + 1;
  if ((v3 & 0x10000) == 0)
    goto LABEL_3;
  goto LABEL_9000;
  if ((v6 & 0x10000) == 0)
  {
LABEL_3:
    mover = wk->mover;
    goto LABEL_4;
  }
LABEL_9000:
  v7 = wk->mover;
  itfMoverInit(v7);
  itfMoverSetData(wk->mover, 181, 141, 211, 141, -1.0, 0, 0, 15);
  wk->flags |= 0x10000u;
  mover = wk->mover;
LABEL_4:
  if (itfMoverUpdate(mover) != 2)
    return;
  flags = wk->flags;
  wk->count2 = 0;
  wk->flags = flags | 0x2000;
  wk->step = 5;
  return;
}

// 0x20a5d30
void cmpLvUpSeqSetParStepUpdate(tagCMP_STATUS_WORK *wk) {
  s32 *EventBit;
  s32 v7;

  if (evtBitCheck(10003))
  {
    goto LABEL_4;
  }
  if (evtBitCheck(2104))
  {
    EventBit = GBWK->EventBit;
    EventBit[312] |= 0x80000u;
    goto LABEL_4;
  }
  tipsTIPSStart(19);
LABEL_4:
  if (tipsProcessCheck())
    return;
  v7 = cmpCtrlSetParam(wk);
  scrEventSkipEnd(0, 0);
  fclSkipNoEnd(g_mainPID, 0);
  if (!v7)
  {
    Reset(0);
    fclStart2(8, 1, 0);
    fclSetSelCancelPos(1);
    SetMessagePos(0);
    wk->flags &= ~0x2000u;
    wk->step = 6;
  }
}

// 0x20a5f90
void cmpLvUpSeqConfStepUpdate(tagCMP_STATUS_WORK *wk) {
  s32 v3;
  s8 v5;

  v3 = Update();
  if (v3 == 1)
  {
    cmpResetParam(wk);
    wk->flags |= 0x2000u;
    v5 = 5;
  }
  else
  {
    if (v3)
      return;
    wk->count2 = -1;
    v5 = 7;
  }
  wk->step = v5;
}

// 0x20a6030
void cmpLvUpSeqCallParOutStepUpdate(tagCMP_STATUS_WORK *wk) {
  s32 v3;
  itfMover_t *mover;
  s32 v6;
  itfMover_t *v7;
  s64 flags;

  v3 = (u16)wk->count2++ + 1;
  if ((v3 & 0x10000) == 0)
    goto LABEL_3;
  goto LABEL_9000;
  if ((v6 & 0x10000) == 0)
  {
LABEL_3:
    mover = wk->mover;
    goto LABEL_4;
  }
LABEL_9000:
  v7 = wk->mover;
  itfMoverInit(v7);
  itfMoverSetData(wk->mover, 211, 141, 181, 141, -1.0, 0, 0, 15);
  mover = wk->mover;
LABEL_4:
  if (itfMoverUpdate(mover) != 2)
    return;
  flags = wk->flags;
  wk->count2 = 0;
  wk->flags = flags & 0xFFFFFFFFFFFEFFFFLL;
  wk->step = 18;
  return;
}

// 0x20a6170
void cmpLvUpSeqSklCMsgInitStepUpdate(tagCMP_STATUS_WORK *wk) {
  s32 v2;

  v2 = wk->count++;
  if (v2 >= 30)
  {
    wk->count = 0;
    wk->step = 9;
    wk->sklSpeedUp = 1;
  }
}

// 0x20a61a0
void cmpLvUpSeqSklCMsgWaitStepUpdate(tagCMP_STATUS_WORK *wk) {
  wk->step = 18;
}

// 0x20a61d0
void cmpLvUpSeqNmlSklItemMsgInitStepUpdate(tagCMP_STATUS_WORK *wk) {
  s32 learnCombSkillID;
  char *v4;
  char *v5;

  Reset(0);
  learnCombSkillID = wk->learnCombSkillID;
  v4 = sdatSkillName(learnCombSkillID);
  fclSetMessageVar(0, v4);
  v5 = sdatDevilName(wk->unit->devilid, 0);
  fclSetMessageVar(1, v5);
  fclStart1(30, 1);
  wk->step = 13;
}

// 0x20a62c0
void cmpLvUpSeqNmlSklItemMsgWaitStepUpdate(tagCMP_STATUS_WORK *wk) {
  if (!Update())
  {
    wk->step = 18;
    fclEndMessage();
  }
}

// 0x20a61b0
void cmpLvUpSeqSklAMsgInitStepUpdate(tagCMP_STATUS_WORK *wk) {
  wk->step = 11;
}

// 0x20a61c0
void cmpLvUpSeqSklAMsgWaitStepUpdate(tagCMP_STATUS_WORK *wk) {
  wk->step = 18;
}

// 0x20a6350
void cmpLvUpSeqOmoSklItemMsgInitStepUpdate(tagCMP_STATUS_WORK *wk) {
  s32 learnAutoSkillID;
  char *v4;
  char *v5;

  Reset(0);
  learnAutoSkillID = wk->learnAutoSkillID;
  v4 = sdatSkillName(learnAutoSkillID);
  fclSetMessageVar(0, v4);
  v5 = sdatDevilName(wk->unit->devilid, 0);
  fclSetMessageVar(1, v5);
  fclStart1(30, 1);
  wk->step = 15;
}

// 0x20a6440
void cmpLvUpSeqOmoSklItemMsgWaitStepUpdate(tagCMP_STATUS_WORK *wk) {
  if (!Update())
  {
    wk->step = 18;
    fclEndMessage();
  }
}

// 0x20a64d0
void cmpLvUpSeqRecvWaitStepUpdate(tagCMP_STATUS_WORK *wk) {
  s64 flags;
  sdatUnitWork_t *unit;

  flags = wk->flags;
  if ((flags & 0x40000) != 0)
  {
    unit = wk->unit;
    flags |= 0x40000u;
    wk->flags = flags;
    unit->now->hp = unit->now->maxhp;
    if ((flags & 0x80000) == 0)
      goto LABEL_3;
  }
  else if ((flags & 0x80000) == 0)
  {
LABEL_3:
    wk->step = 18;
    return;
  }
  wk->flags = flags | 0x80000;
  wk->unit->now->mp = wk->unit->now->maxmp;
  wk->step = 18;
}

// 0x20a67b0
void cmpLvUpSeqWaitStepUpdate(tagCMP_STATUS_WORK *wk) {
  s64 flags;

  if (wk->count2)
  {
    wk->count2 = 0;
    cmpFuncEnd(wk);
    wk->step = 21;
  }
  else
  {
    flags = wk->flags;
    if ((flags & 0x4000000) != 0)
    {
      flags = wk->flags;
      wk->flags = flags & 0xFFFFFFFFFBFFFFFFLL;
      wk->count2 = 1;
    }
  }
}

// 0x20a6a30
void cmpRstSeqViewerStepUpdate(tagCMP_STATUS_WORK *wk) {
  Il2CppObject *Instance;
  sdfVector4_t v5;
  f32 z;
  s32 v15;
  sdfVector4_t v16;
  sdfVector4_t a_pos;

  *(u64 *)&a_pos.x = 0;
  *(u64 *)&a_pos.z = 0;
  Instance = _get_Instance();
  StatusUiViewerOff(Instance, 0);
  if (CHECK_TRIG(4097, 1))
  {
    cmpClrRot();
    cmpGetPos(&a_pos);
    v16 = a_pos;
    vct_B = v16;
    cmpGetPosStatus(&a_pos);
    v5 = a_pos;
    vct_A = v5;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    _Q0 = vct_A;
    wk->mode = 1;
    wk->step = 20;
    a_pos = _Q0;
    __asm { FMOV            V0.2S, #10.0 }
    z = a_pos.z;
    *(float32x2_t *)&wk->sMov.x = vdiv_f32(*(float32x2_t *)&a_pos.x, *(float32x2_t *)&_Q0.x);
    wk->sMov.z = z / 10.0;
    v15 = 1;
    gPosLimit = 0;
    goto LABEL_22;
  }
  if (!CHECK_TRIG(41730, 1))
    return;
  cmpClearDat();
  cmpGetPosStatus(&a_pos);
  cmpAddPos(-a_pos.x, 0.0, 0.0);
  v15 = 0;
  wk->sMov.x = 0.0;
LABEL_22:
  SE(v15);
}

// 0x20a6860
void cmpRstSeqChangeStepUpdate(tagCMP_STATUS_WORK *wk) {
  f32 x;
  f32 y;
  f32 z;
  s32 count;
  s32 mode;

  x = wk->sMov.x;
  y = wk->sMov.y;
  z = wk->sMov.z;
  cmpAddPos(x, y, z);
  count = wk->count;
  if (count < 9)
  {
    wk->count = count + 1;
    return;
  }
  mode = wk->mode;
  wk->count = 0;
  if (mode == 2)
  {
    wk->step = 19;
    gPosLimit = 1;
    return;
  }
  if (mode == 1)
  {
    wk->step = 18;
    gPosLimit = 0;
    return;
  }
}

// 0x20a6d80
void cmpSeqRankUp(tagCMP_STATUS_WORK *wk) {
  s32 step;
  s32 count2;
  bool v7;
  s64 flags;
  sdatUnitWork_t *unit;
  s64 v11;

  if ((wk->flags & 0x200) != 0 && wk->loadModelNo >= 1)
  {
    cmpSetSmoothSingleMotion(7, 0.0, 0.0);
  }
  step = (u8)wk->step;
  if (wk->step)
  {
    if (step == 1)
    {
      count2 = (u16)wk->count2;
      if (count2 == 15)
      {
        wk->count2 = 0;
        v7 = rstChkFlagPlayBgm();
        if (v7)
        {
          sndBgmTop();
LABEL_35:
          wk->step = 18;
        }
        else
        {
          sndBgmPlay(0, 0);
          rstSetFlagPlayBgm();
          wk->step = 18;
        }
      }
      else
      {
        if (!wk->count2)
        {
          dds3FadeIn(0, 0, 0, 0xFu);
          LOWORD(count2) = wk->count2;
        }
        wk->count2 = count2 + 1;
      }
    }
    else
    {
      switch ((char)step)
      {
        case 16:
          wk->step = 17;
          break;
        case 17:
          flags = wk->flags;
          if ((flags & 0x40000) != 0)
          {
            unit = wk->unit;
            flags |= 0x40000u;
            wk->flags = flags;
            unit->now->hp = unit->now->maxhp;
          }
          if ((flags & 0x80000) == 0)
            goto LABEL_35;
          wk->flags = flags | 0x80000;
          wk->unit->now->mp = wk->unit->now->maxmp;
          wk->step = 18;
          break;
        case 18:
          if (wk->count2)
          {
            wk->count2 = 0;
            cmpFuncEnd(wk);
            wk->step = 21;
          }
          else
          {
            v11 = wk->flags;
            if ((v11 & 0x4000000) != 0)
            {
              v11 = wk->flags;
              wk->flags = v11 & 0xFFFFFFFFFBFFFFFFLL;
              wk->count2 = 1;
            }
          }
          break;
        case 21:
          wk->step = 0;
          break;
        default:
          return;
      }
    }
  }
  else if ((wk->flags & 0x400000) != 0)
  {
    wk->flags &= 0xFFFFFFFFFBBFFFFFLL;
    cmpSetFlagDraw(1);
    cmpSetFlagDraw(1);
    dds3FadeOut(0, 0, 0, 1u);
    wk->count2 = 0;
    wk->step = 1;
  }
}

// 0x20a7130
void Release(tagCMP_STATUS_WORK *wk) {
  s64 flags;
  Il2CppObject *Instance;

  End();
  flags = wk->flags;
  if ((flags & 2) == 0)
  {
    if ((flags & 4) == 0)
      goto LABEL_5;
LABEL_17:
    wk->flags = flags & 0xFFFFFFFFFFFFFFFBLL;
    cmpFreeSpriteHnd(0);
    flags = wk->flags;
    if ((flags & 8) != 0)
      goto LABEL_21;
LABEL_6:
    if ((flags & 0x10) == 0)
      goto LABEL_7;
LABEL_25:
    wk->flags = flags & 0xFFFFFFFFFFFFFFEFLL;
    cmpFreeSpriteHnd(2);
    flags = wk->flags;
    if ((flags & 0x20) != 0)
      goto LABEL_29;
LABEL_8:
    if ((flags & 0x40) == 0)
      goto LABEL_9;
    goto LABEL_32;
  }
  wk->flags = flags & 0xFFFFFFFFFFFFFFFDLL;
  cmpFreeSpriteMem(0);
  flags = wk->flags;
  if ((flags & 4) != 0)
    goto LABEL_17;
LABEL_5:
  if ((flags & 8) == 0)
    goto LABEL_6;
LABEL_21:
  wk->flags = flags & 0xFFFFFFFFFFFFFFF7LL;
  cmpFreeSpriteMem(2);
  flags = wk->flags;
  if ((flags & 0x10) != 0)
    goto LABEL_25;
LABEL_7:
  if ((flags & 0x20) == 0)
    goto LABEL_8;
LABEL_29:
  wk->flags = flags & 0xFFFFFFFFFFFFFFDFLL;
  cmpFreeSpriteMem(1);
  flags = wk->flags;
  if ((flags & 0x40) == 0)
  {
LABEL_9:
    goto LABEL_10;
  }
LABEL_32:
  wk->flags = flags & 0xFFFFFFFFFFFFFFBFLL;
  cmpFreeSpriteHnd(1);
LABEL_10:
  passPar = 0;
  Instance = _get_Instance();
  UIDestroy(Instance, wk->noGcClear, 0);
  wk->noGcClear = 0;
}

// 0x20a73d0
void CallProcEnd(tagCMP_STATUS_WORK *wk) {
  ;
}

// 0x20a73e0
u8 CheckProcEnd(tagCMP_STATUS_WORK *wk) {
  return 0;
}

// 0x20a73f0
dds3ProcessFunc_t Process(dds3ProcessID_t *PID) {
  tagCMP_STATUS_WORK *ProcessData;
  s32 seqtype;
  u32 step;
  s8 v8;
  dds3ProcessFunc_t v9;
  s8 v10;
  dds3ProcessFunc_t result;
  s32 count;
  sdatUnitWork_t *unit;
  sdatParaWork_t *backup;
  sdatParaWork_t *now;
  sdatUnitWork_t *para;
  sdatParaWork_t *v17;
  sdatParaWork_t *v18;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  if (ProcessData->type == 268697601 || (ProcessData->unit->flag & 2) == 0 || ProcessData->setLuck)
  {
    seqtype = ProcessData->seqtype;
    if (seqtype == 3)
      goto LABEL_13;
  }
  else
  {
    datCalcLuckParam();
    unit = ProcessData->unit;
    now = unit->now;
    backup = unit->backup;
    para = GBWK->player->para;
    v18 = para->now;
    v17 = para->backup;
    now->luck = v18->luck;
    backup->luck = v17->luck;
    ProcessData->setLuck = 1;
    seqtype = ProcessData->seqtype;
    if (seqtype == 3)
    {
LABEL_13:
      step = ProcessData->step;
      v8 = ProcessData->step;
      if (step >= 2)
      {
        if (step != 2)
        {
          if (step != 3)
            return 0;
          v9 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
          _ctor(v9, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
          return v9;
        }
        count = ProcessData->count;
        if (ProcessData->count)
        {
          if (count >= 2)
          {
            v10 = v8 + 1;
LABEL_20:
            ProcessData->count = 0;
            ProcessData->step = v10;
            return 0;
          }
        }
        else
        {
          ProcessData->flags &= ~0x400u;
        }
        ProcessData->count = count + 1;
        return 0;
      }
      v8 = ProcessData->step;
      v10 = v8 + 2;
      goto LABEL_20;
    }
  }
  if ((ProcessData->flags & 0x80) != 0)
  {
    cmpUpdatemodel(ProcessData);
    seqtype = ProcessData->seqtype;
  }
  v9 = 0;
  switch (seqtype)
  {
    case 0:
      cmpSequence(ProcessData);
      result = 0;
      break;
    case 1:
      cmpSeqLevelUp(ProcessData);
      result = 0;
      break;
    case 2:
      cmpSeqRankUp(ProcessData);
      result = 0;
      break;
    case 4:
    case 6:
      cmpSeqMemSet(ProcessData);
      result = 0;
      break;
    case 5:
      cmpSeqGoodby(ProcessData);
      result = 0;
      break;
    case 7:
      CmpStatusSklItemSequence(ProcessData);
      result = 0;
      break;
    case 8:
      cmpSeqDvlReport(ProcessData);
      result = 0;
      break;
    default:
      return v9;
  }
  return result;
}

// 0x20a7850
void cmpDrawNumSmallFont(s32 a_x, s32 a_y, s32 a_space, u32 a_color, u8 a_alpha, char *a_str) {
  ;
}

// 0x20a7860
void cmpDrawNumOtSmallFont(s32 a_x, s32 a_y, s32 a_space, u32 a_color, u8 a_alpha, char *a_str, DDS3_OT a_ot) {
  ;
}

// 0x20a7870
void cmpDrawSprite(s32 a_x, s32 a_y, u8 a_alpha, CMP_SPR a_sprFileNo, s32 a_sprNo) {
  cmpGetSpriteHnd(a_sprFileNo);
}

// 0x20a7900
void cmpDrawSprList(s32 a_x, s32 a_y, u8 a_alpha, CMP_SPR a_sprFileNo, itfSprList_t *a_list) {
  cmpGetSpriteHnd(a_sprFileNo);
}

// 0x20a7990
void cmpDrawBlinkParam(s32 a_x, s32 a_y, s32 a_alphaRate, s32 a_cnt) {
  cmpGetSpriteHnd(2);
}

// 0x20a7a10
void cmpDrawLightPar(s32 cnt, UiParType _type, CmpStatusGaugeSet *statusGaugeSet, bool _noLight) {
  LightGaugeDrawUnity(statusGaugeSet, cnt, type, !noLight, 0);
}

// 0x20a7a30
void cmpDrawParam(tagCMP_STATUS_WORK *wk, s32 a_type, s32 a_x, s32 a_y, s32 a_alphaRate, bool a_bSel) {
  void *v9;
  void *v10;
  sdatUnitWork_t *v11;
  sdatParaWork_t *v12;
  f32 counter;
  bool v14;
  sdatUnitWork_t *unit;
  s32 str;
  s32 tec;
  s32 swordno;
  s32 Sword4Param;
  sdatUnitWork_t *v21;
  s32 devilid;
  s32 v23;
  s32 vit;
  sdatUnitWork_t *v25;
  s32 v26;
  s32 v27;
  sdatUnitWork_t *v28;
  s32 v29;
  s32 v30;
  sdatUnitWork_t *v31;
  s32 v32;
  s32 v33;
  sdatUnitWork_t *v34;
  s32 v35;
  s32 v36;
  s64 type;
  u32 v38;
  s32 v40;
  s32 v41;
  sdatUnitWork_t *v42;
  s32 v43;
  s32 v44;
  s32 v45;
  sdatUnitWork_t *v46;
  s32 v47;
  s32 v48;
  s32 v50;
  u32 v51;
  s32 v52;
  void *v53;
  void *v55;
  void *p_monitor;
  s64 v57;
  s32 v58;
  u32 v59;
  Il2CppObject *v60;
  char *v61;
  s32 v62;
  s32 v63;
  bool v64;
  s32 v65;
  s32 v66;
  s32 v67;
  s32 v68;
  s64 v74;
  _BOOL4 lightParNoDraw;
  s32 v84;
  void *v88;
  s32 v89;
  s32 v90;
  s32 v91;
  s32 v92;
  s32 v93;
  s32 v95;
  s32 v96;
  s32 v97;
  u32 flag;
  u32 v100;
  s32 v102;
  s32 v104;
  s32 v105;
  s32 v107;
  sdatUnitWork_t *v108;
  s32 v109;
  s32 v110;
  s32 v113;
  s32 v115;
  s32 lvup_cnt;
  s32 v117;
  s32 v118;
  s32 v119;
  s32 v120;
  s32 v121;
  s32 v122;
  s32 v123;
  s32 v124;
  s32 v126;
  s32 v127;
  s32 CorrectionParamLuck;
  s32 v132;
  s32 luck;
  u32 data;

  v9 = NewSpecific(s32, 4u);
  InitializeArray_55364416(v9, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__FA28B3393D1DFFA5076C205DA72753A55C4907068F0A9A0D2EE5AC24D8A27B22, 0);
  v10 = NewSpecific(s16, 7u);
  InitializeArray_55364416(v10, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__7E44AC55D5D1BC7927DAE60B7E7988BB21EEA5176694FA0C721070552C7FCEAB, 0);
  v11 = Allocate(sdatUnitWork_t);
  _ctor(v11, 0);
  v12 = Allocate(sdatParaWork_t);
  _ctor(v12, 0);
  counter = wk->counter;
  if (counter <= 0.0)
  {
    v14 = 0;
  }
  else
  {
    v14 = 1;
    wk->counter = counter - VRF_DeltaTime;
  }
  wk->lightParNoDraw = v14;
  v11->now->tec = wk->player_tec;
  sBtlGetPlayerTec_ParaUp(v11, v12);
  switch (a_type)
  {
    case 0:
      unit = wk->unit;
      str = unit->backup->str;
      tec = unit->now->str;
      swordno = wk->swordno;
      Sword4Param = datGetSword4Param(swordno, 0);
      v21 = wk->unit;
      v121 = Sword4Param;
      if ((v21->flag & 2) != 0)
      {
        str += GETITEMPARA_LOW(v21->pitem->str);
        CorrectionParamLuck = 0;
        vit = 0;
        v38 = 0;
        luck = GETITEMPARA_HIGH(wk->unit->pitem->str);
        v122 = luck + str;
        goto LABEL_73;
      }
      devilid = v21->devilid;
      if (devilid < 1)
      {
        v122 = 0;
        vit = 0;
        goto LABEL_60;
      }
      v23 = (u16)devilid;
      vit = sBtlGetDevilData(v23, -1)->str;
      if (wk->root)
      {
        v122 = 0;
LABEL_60:
        CorrectionParamLuck = 0;
        luck = 0;
        v38 = 0;
        goto LABEL_73;
      }
      v122 = 0;
      CorrectionParamLuck = 0;
      v38 = 0;
      vit += GETITEMPARA_LOW(wk->unit->pitem->str);
      luck = v12->str;
      goto LABEL_73;
    case 1:
      v25 = wk->unit;
      str = v25->backup->tec;
      tec = v25->now->tec;
      v26 = wk->swordno;
      v27 = datGetSword4Param(v26, 1);
      v28 = wk->unit;
      v121 = v27;
      if ((v28->flag & 2) != 0)
      {
        str += GETITEMPARA_LOW(v28->pitem->tec);
        CorrectionParamLuck = 0;
        vit = 0;
        luck = GETITEMPARA_HIGH(wk->unit->pitem->tec);
        v38 = 1;
        v122 = luck + str;
        goto LABEL_73;
      }
      v29 = v28->devilid;
      if (v29 < 1)
      {
        v122 = 0;
        vit = 0;
        goto LABEL_62;
      }
      v30 = (u16)v29;
      vit = sBtlGetDevilData(v30, -1)->tec;
      if (wk->root)
      {
        v122 = 0;
LABEL_62:
        CorrectionParamLuck = 0;
        luck = 0;
        v38 = 1;
        goto LABEL_73;
      }
      v122 = 0;
      CorrectionParamLuck = 0;
      vit += GETITEMPARA_LOW(wk->unit->pitem->tec);
      v38 = 1;
      luck = v12->tec;
      goto LABEL_73;
    case 2:
      v31 = wk->unit;
      str = v31->backup->vit;
      tec = v31->now->vit;
      v32 = wk->swordno;
      v33 = datGetSword4Param(v32, 2);
      v34 = wk->unit;
      v121 = v33;
      if ((v34->flag & 2) != 0)
      {
        str += GETITEMPARA_LOW(v34->pitem->vit);
        CorrectionParamLuck = 0;
        vit = 0;
        luck = GETITEMPARA_HIGH(wk->unit->pitem->vit);
        v38 = 2;
        v122 = luck + str;
        goto LABEL_73;
      }
      v35 = v34->devilid;
      if (v35 < 1)
      {
        v122 = 0;
        vit = 0;
        goto LABEL_64;
      }
      v36 = (u16)v35;
      vit = sBtlGetDevilData(v36, -1)->vit;
      if (wk->root)
      {
        v122 = 0;
LABEL_64:
        CorrectionParamLuck = 0;
        luck = 0;
        v38 = 2;
        goto LABEL_73;
      }
      v122 = 0;
      CorrectionParamLuck = 0;
      vit += GETITEMPARA_LOW(wk->unit->pitem->vit);
      v38 = 2;
      luck = v12->vit;
      goto LABEL_73;
    case 3:
      datCalcLuckParam();
      tec = wk->unit->now->luck;
      type = wk->type;
      if (type <= 268697855)
      {
        if (type != 17039361 && type != 268697601)
          goto LABEL_65;
LABEL_46:
        str = wk->unit->backup->luck;
        v40 = wk->swordno;
        goto LABEL_48;
      }
      if (type == 0x110040100LL || type == 268697856)
        goto LABEL_46;
LABEL_65:
      str = wk->unit->backup->luck - wk->param[3];
      v40 = wk->swordno;
LABEL_48:
      v41 = datGetSword4Param(v40, 3);
      v42 = wk->unit;
      v43 = v41;
      if (v42->devilid)
      {
        CorrectionParamLuck = 0;
        v121 = v41;
        if ((v42->flag & 2) == 0)
        {
LABEL_50:
          v44 = v42->devilid;
          if (v44 < 1)
          {
            v122 = 0;
            vit = 0;
            luck = 0;
          }
          else
          {
            v45 = (u16)v44;
            vit = sBtlGetDevilData(v45, -1)->luck;
            if (wk->root)
            {
              v122 = 0;
              luck = 0;
            }
            else
            {
              vit += GETITEMPARA_LOW(wk->unit->pitem->luck);
              v122 = 0;
              luck = v12->luck;
            }
          }
          goto LABEL_72;
        }
      }
      else
      {
        CorrectionParamLuck = sBtlGetCorrectionParamLuck();
        v46 = wk->unit;
        v47 = v46->backup->luck;
        v48 = GETITEMPARA(v46->pitem->luck);
        v42 = wk->unit;
        tec = v48 + v47 + v42->pbtl->luck + v42->huuma->luck;
        v121 = v43;
        if ((v42->flag & 2) == 0)
          goto LABEL_50;
      }
      str += GETITEMPARA_LOW(v42->pitem->luck);
      vit = 0;
      luck = GETITEMPARA_HIGH(wk->unit->pitem->luck);
      v122 = luck + str;
LABEL_72:
      v38 = 3;
LABEL_73:
      cmpGetSpriteHnd(2);
      v127 = str;
      if (a_type == 3 && CorrectionParamLuck)
      {
        v50 = *((s16 *)&v10[2].klass + sBtlGetPlayerLuckStep());
        itfIconDrawSprite(a_x - 18, a_y, 256, a_alphaRate, v50, 108);
      }
      if (a_bSel)
        v51 = 1692838528;
      else
        v51 = -1600273536;
      v52 = tec + luck;
      if ((wk->unit->flag & 2) != 0)
      {
        p_monitor = &_get_Instance()[8].monitor;
        v52 = tec;
        v55 = p_monitor;
        goto LABEL_91;
      }
      else
      {
        v53 = &_get_Instance()[9];
        v55 = v53;
        goto LABEL_91;
      }
LABEL_91:
      v57 = wk->type;
      if (v57 == 17039361 || v57 == 0x110040100LL || v57 == 268697856)
        v52 = wk->param[a_type] + v122;
      v58 = v52 + CorrectionParamLuck;
      if (v52 + CorrectionParamLuck <= 1)
        v58 = 1;
      if (a_type != 3)
        v58 = v52;
      if (v58 >= 40)
        v59 = 40;
      else
        v59 = v58;
      data = v59;
      v60 = Box(s32, &data);
      v61 = Format("{0,2:d}", v60, 0);
      Concat_54766928(0, v61, 0);
      (v55->klass->vtable._5_ParDrawNumUnity.methodPtr)(v55, v59, v51, v38, 1, v55->klass->vtable._5_ParDrawNumUnity.method);
      v62 = v127;
      cmpGetSpriteHnd(2);
      v63 = 0;
      v132 = 0;
      v123 = v127 - v121;
      v64 = a_type == 3 && CorrectionParamLuck < 0;
      v65 = tec + CorrectionParamLuck;
      v66 = !v64;
      v124 = tec + CorrectionParamLuck;
      if (v65 <= 1)
        v65 = 1;
      v126 = v65;
      v67 = v122;
      if (!v66)
        v67 = v127;
      v119 = v67;
      v120 = v66;
      do
      {
        if ((wk->unit->flag & 2) != 0)
          v68 = 40;
        else
          v68 = luck + 2 * vit;
        if (v63 < v68)
        {
          cmpGetSpriteHnd(2);
          if (v68 >= 40)
            v68 = 40;
          v62 = v127;
          if (v68 != lastBasePar[a_type])
          {
            lastBasePar[a_type] = v68;
            BaseGaugeDrawUnity(v55, v68, v38, 0);
          }
        }
        if (v63 < tec)
        {
          cmpGetSpriteHnd(2);
          GaugeChangeColor(v55, v63, v38, 1, 0);
          if (tec != lastOrangePar[a_type])
          {
            lastOrangePar[a_type] = tec;
            (v55->klass->vtable._6_OrangeGaugeDrawUnity.methodPtr)(v55, v63, v38, v55->klass->vtable._6_OrangeGaugeDrawUnity.method);
            LightGaugeAllOff(v55, 0);
            wk->counter = 1.1;
            wk->lightParNoDraw = 1;
          }
        }
        v74 = wk->type;
        if (v74 == 268566784)
        {
          if (v63 >= tec || tec - wk->param[a_type] > v63)
            goto LABEL_222;
          cmpGetSpriteHnd(2);
          cmpGetSpriteHnd(2);
          goto LABEL_164;
        }
        if (v74 == 268501248)
        {
          if (vit > v63 || v63 >= tec)
            goto LABEL_222;
          cmpGetSpriteHnd(2);
          cmpGetSpriteHnd(2);
          v132 = 1;
LABEL_164:
          GaugeChangeColor(v55, v63, v38, 1, 0);
          LightGaugeDrawUnity(v55, v63, v38, !wk->lightParNoDraw, 0);
          goto LABEL_222;
        }
        v74 = wk->type;
        if (v74 <= 268697855)
          goto LABEL_167;
        if (v74 == 0x110040100LL || v74 == 268697856)
          goto LABEL_192;
LABEL_273:
        v107 = wk->param[a_type];
        v108 = wk->unit;
        if (v107 >= 1)
        {
          if ((v108->flag & 2) != 0)
          {
            v118 = tec - (luck + v121);
            v109 = v118 - v107;
            if (luck >= 1)
              v110 = v62;
            else
              v110 = v118 - v107;
            if (v121 >= 1)
              v110 = v127 - v121;
            if (tec >= 41)
              v109 = v110;
            if (v63 >= v109 + v107)
              goto LABEL_310;
          }
          else
          {
            v109 = tec - v107;
            if (v63 >= tec)
              goto LABEL_310;
          }
          if (v109 <= v63)
          {
            cmpGetSpriteHnd(2);
            cmpGetSpriteHnd(2);
            LightGaugeDrawUnity(v55, v63, v38, !wk->lightParNoDraw, 0);
            v108 = wk->unit;
            goto LABEL_310;
          }
        }
LABEL_310:
        if ((v108->flag & 2) == 0 || !v121)
          goto LABEL_222;
        v113 = wk->param[a_type];
        if (v121 >= 1)
        {
          if (v123 + v113 > v63 || v63 >= v113 + v62)
            goto LABEL_222;
          cmpGetSpriteHnd(2);
          v88 = v55;
          v89 = v63;
          v90 = v38;
          v91 = 2;
          goto LABEL_221;
        }
        v115 = v113 + tec;
        if (v115 > v63 || v63 >= v115 - v121)
          goto LABEL_222;
LABEL_217:
        cmpGetSpriteHnd(2);
        v88 = v55;
        v89 = v63;
        v90 = v38;
        v91 = 4;
LABEL_221:
        GaugeChangeColor(v88, v89, v90, v91, 0);
        goto LABEL_222;
LABEL_167:
        if (v74 != 17039361)
        {
          if (v74 != 268697601)
            goto LABEL_273;
          if (v63 >= v62 || v62 - wk->param[a_type] > v63)
            goto LABEL_222;
          cmpGetSpriteHnd(2);
          cmpGetSpriteHnd(2);
          if (tec != lastOrangePar[a_type])
          {
            (v55->klass->vtable._6_OrangeGaugeDrawUnity.methodPtr)(v55, v63, v38, v55->klass->vtable._6_OrangeGaugeDrawUnity.method);
            lastOrangePar[a_type] = tec;
          }
          GaugeChangeColor(v55, v63, v38, 1, 0);
          lightParNoDraw = wk->lightParNoDraw;
          LightGaugeDrawUnity(v55, v63, v38, !lightParNoDraw, 0);
          goto LABEL_222;
        }
LABEL_192:
        if (v123 <= v63 && v63 < tec)
        {
          cmpGetSpriteHnd(2);
          GaugeChangeColor(v55, v63, v38, 2, 0);
          goto LABEL_198;
        }
LABEL_198:
        v84 = wk->param[a_type];
        if (v84 >= 1)
        {
          if (v62 > v63 || v63 >= v84 + v62)
            goto LABEL_222;
          cmpGetSpriteHnd(2);
          cmpGetSpriteHnd(2);
          LightGaugeDrawUnity(v55, v63, v38, !wk->lightParNoDraw, 0);
          if (tec != lastOrangePar[a_type])
          {
            (v55->klass->vtable._6_OrangeGaugeDrawUnity.methodPtr)(v55, v63, v38, v55->klass->vtable._6_OrangeGaugeDrawUnity.method);
            lastOrangePar[a_type] = tec;
          }
          v88 = v55;
          v89 = v63;
          v90 = v38;
          v91 = 1;
          goto LABEL_221;
        }
        v92 = v84 + v122;
        v93 = v124 + v84;
        if (v93 <= 1)
          v93 = 1;
        if (v120)
          v93 = v92;
        if (v93 <= v63 && v63 < v119)
          goto LABEL_217;
LABEL_222:
        if (CorrectionParamLuck <= 0)
        {
          v95 = v126;
          v96 = tec;
          if (wk->type == 268697601)
          {
            v97 = wk->param[a_type];
            v95 = v124 - v97;
            v96 = tec - v97;
            if (v95 <= 1)
              v95 = 1;
          }
          if (v95 <= (u32)v63 && v63 < v96)
          {
            cmpGetSpriteHnd(2);
            GaugeChangeColor(v55, v63, v38, 4, 0);
            goto LABEL_232;
          }
        }
LABEL_232:
        flag = wk->unit->flag;
        v100 = flag & 2;
        if (((v132 | (v100 >> 1)) & 1) == 0)
        {
          if (vit > v63 || v63 >= tec - wk->param[a_type])
            goto LABEL_255;
          cmpGetSpriteHnd(2);
          GaugeChangeColor(v55, v63, v38, 2, 0);
          flag = wk->unit->flag;
          v100 = flag & 2;
          goto LABEL_239;
        }
LABEL_239:
        if (!v100 || luck < 1)
          goto LABEL_255;
        v102 = wk->param[a_type];
        if (wk->type == 268697601)
        {
          if (v102 + luck < 1 || v102 > 0)
            v102 = 0;
          v104 = v62 - v102;
          v105 = v62;
          if (v104 > v63)
            goto LABEL_255;
LABEL_250:
          if (v63 >= v105 + luck)
            goto LABEL_255;
          cmpGetSpriteHnd(2);
          GaugeChangeColor(v55, v63, v38, 3, 0);
          flag = wk->unit->flag;
          goto LABEL_255;
        }
        v105 = v102 + v62;
        if (v105 <= v63)
          goto LABEL_250;
LABEL_255:
        if (!((flag & 2) != 0 || luck < 1 || v63 < tec || v63 >= tec + luck))
        {
          cmpGetSpriteHnd(2);
          GaugeChangeColor(v55, v63, v38, 3, 0);
        }
        ++v63;
      }
      while (v63 != 40);
      lvup_cnt = wk->lvup_cnt;
      if (lvup_cnt + 1 <= 119)
        v117 = lvup_cnt + 1;
      else
        v117 = 0;
      wk->lvup_cnt = v117;
      return;
    default:
      v122 = 0;
      vit = 0;
      str = 0;
      CorrectionParamLuck = 0;
      tec = 0;
      v38 = -1;
      v121 = 0;
      luck = 0;
      goto LABEL_73;
  }
}

// 0x20a93a0
void cmpDrawParamCursor(tagCMP_STATUS_WORK *wk) {
  Il2CppObject *Instance;

  Instance = _get_Instance();
  RaidouLvUpCursorDrawUnity(Instance[8].monitor, wk->sel_param, 0);
  cmpGetSpriteHnd(2);
}

// 0x20a94a0
void cmpDrawParameter(tagCMP_STATUS_WORK *wk, s32 a_alphaRate) {
  sdatUnitWork_t *unit;
  s32 v7;
  Il2CppObject *Instance;
  bool v17;
  bool v20;
  bool v23;
  s32 v26;
  bool v27;

  cmpGetSpriteHnd(2);
  unit = wk->unit;
  if ((unit->flag & 2) != 0)
  {
    v7 = 179;
    goto LABEL_11;
  }
  if (unit->devilid >= 1)
  {
    v7 = 155;
LABEL_11:
    cmpGetSpriteHnd(2);
    cmpGetSpriteHnd(2);
    cmpGetSpriteHnd(2);
    cmpGetSpriteHnd(2);
    if ((wk->flags & 0x2000) == 0)
    {
      Instance = _get_Instance();
      RaidouLvUpCursorOff(Instance[8].monitor, 0);
      if ((wk->flags & 0x2000) == 0)
        goto LABEL_36;
      goto LABEL_35;
    }
    cmpDrawParamCursor(wk);
    if ((wk->flags & 0x2000) == 0)
      goto LABEL_36;
LABEL_35:
    if (!wk->sel_param)
    {
      v17 = 1;
      goto LABEL_38;
    }
LABEL_36:
    v17 = 0;
LABEL_38:
    cmpDrawParam(wk, 0, 25, v7, a_alphaRate, v17);
    if ((wk->flags & 0x2000) != 0 && wk->sel_param == 1)
    {
      v20 = 1;
    }
    else
    {
      v20 = 0;
    }
    cmpDrawParam(wk, 1, 25, v7 + 23, a_alphaRate, v20);
    if ((wk->flags & 0x2000) != 0 && wk->sel_param == 2)
    {
      v23 = 1;
    }
    else
    {
      v23 = 0;
    }
    cmpDrawParam(wk, 2, 25, v7 + 46, a_alphaRate, v23);
    v26 = v7 + 69;
    if ((wk->flags & 0x2000) != 0 && wk->sel_param == 3)
    {
      v27 = 1;
    }
    else
    {
      v27 = 0;
    }
    cmpDrawParam(wk, 3, 25, v26, a_alphaRate, v27);
    return;
  }
}

// 0x20a98e0
s32 cmpGetNowSummonerRank(void) {
  s32 v1;
  s32 v3;

  v1 = 0;
  while (1)
  {
    v3 = arrPlayerRank[v1][0];
    if (v3 < 0)
      break;
    v3 = arrPlayerRank[v1][0];
    if (evtBitCheck(v3))
      break;
    ++v1;
  }
  return 29 - v1;
}

// 0x20a99c0
s32 cmpGetSummonerRank2SprNo(bool _cmp) {
  u32 *SetRank;
  s32 v4;
  s32 v6;
  s64 v7;

  if (cmp)
  {
    SetRank = cmpGetSetRank(-1);
    if (SetRank)
      LODWORD(SetRank) = SetRank[4];
  }
  else
  {
    v4 = 0;
    do
    {
      v6 = arrPlayerRank[v4][0];
      if (v6 < 0)
      {
        LODWORD(SetRank) = 0;
        return (s32)SetRank;
      }
      v7 = v4;
      v6 = arrPlayerRank[v4][0];
      ++v4;
    }
    while (!evtBitCheck(v6));
    LODWORD(SetRank) = *(u32 *)(*(u64 *)(*(u64 *)(*((u64 *)SetRank + 23) + 136) + 8 * v7 + 32) + 36);
  }
  return (s32)SetRank;
}

// 0x20a9e30
void cmpSummnerRankObjectInit(tagOBJECT_WORK *psSelf) {
}

// 0x20a9ed0
void cmpSummnerRankMngInit(cmpSummnerRankMng_t *psSelf) {
  cmpSummnerRankMng_t *v3;
  cmpSummnerRankMng_t *v4;
  cmpSummnerRankFunc_t v5;

  v3 = psSelf;
  cmpSummnerRankInit(&v3->sSummnerRank);
  v4 = psSelf;
  v5 = Allocate(cmpSummnerRankFunc_t);
  _ctor(v5, 0, Method_Project_cmpStatus_SummnerRankStateWait__, 0);
  v4->cbState = v5;
  v4 = ((char *)v4 + 16);
  *((u32 *)v4->monitor + 9) = 0;
}

// 0x20aa370
void cmpSummnerRankMngSetState(cmpSummnerRankMng_t *psSelf, cmpSummnerRankFunc_t cbFunc) {
  cmpSummnerRankMng_t *p_fields;

  psSelf->cbState = cbFunc;
  p_fields = &psSelf->fields;
  p_fields->sSummnerRank->iCounter = 0;
}

// 0x20aa3a0
void cmpSummnerRankMngExecute(cmpSummnerRankMng_t *psSelf, sdatUnitWork_t *psUnit, s32 iAlphaRate) {
  sprHandle_t *SpriteHnd;
  cmpSummnerRank_t *sSummnerRank;
  s64 v9;
  cmpSummnerRank_t *v11;
  cmpSummnerRankFunc_t v12;

  SpriteHnd = cmpGetSpriteHnd(2);
  sSummnerRank = psSelf->sSummnerRank;
  sSummnerRank->psUnit = psUnit;
  psSelf->sSummnerRank->iAlphaRate = iAlphaRate;
  v9 = (psSelf->cbState->invoke_impl)(psSelf->cbState->method_code);
  v11 = psSelf->sSummnerRank;
  ++v11->iCounter;
  if (v9)
  {
    v12 = v9;
    psSelf->cbState = v12;
    v11 = psSelf->sSummnerRank;
    v11->iCounter = 0;
  }
  cmpSummnerRankDraw(v11, SpriteHnd);
}

// 0x20aa730
void cmpSummnerRankChange(cmpSummnerRank_t *psSelf) {
  RankText *SetRank;
  s32 sprNo;

  goto LABEL_5;
LABEL_11:
  sprNo = 0;
  goto LABEL_12;
LABEL_5:
  SetRank = cmpGetSetRank(-1);
  if (!SetRank)
    goto LABEL_11;
  sprNo = SetRank->sprNo;
LABEL_12:
  psSelf->sObjBGSRank->iSprNo = sprNo;
  psSelf->sObjSRank->iSprNo = sprNo;
}

// 0x20a9fa0
void cmpSummnerRankInit(cmpSummnerRank_t *psSelf) {
  s32 SummonerRank2SprNo;
  cmpSummnerRank_t *v4;
  cmpSummnerRank_t *v5;
  tagOBJECT_WORK *sObjBG;
  char *v7;
  char *v8;
  char **p_szString;
  cmpSummnerRank_t *v10;
  tagOBJECT_WORK *sObjBGSRank;
  char *v12;
  char *v13;
  char **v14;
  tagOBJECT_WORK *sObjBGRaido;
  char v16;
  char *v17;
  char *v18;
  char **v19;
  tagOBJECT_WORK *sObjCyusei;
  char v21;
  char *v22;
  char *v23;
  char **v24;
  tagOBJECT_WORK *sObjSRank;
  char v26;
  char *v27;
  char *v28;
  char **v29;
  tagOBJECT_WORK *sObjRaido;
  char v31;
  char *v32;
  char *v33;
  char **v34;
  tagOBJECT_WORK *sObjBlur;
  char v36;
  char *v37;
  char *v38;
  char **v39;
  cmpSummnerRank_t *v40;
  tagOBJECT_WORK *v41;
  tagOBJECT_WORK *v42;
  tagOBJECT_WORK *v43;

  SummonerRank2SprNo = cmpGetSummonerRank2SprNo(0);
  v4 = Allocate(cmpSummnerRank_t);
  _ctor(v4, 0);
  psSelf = v4;
  v5 = psSelf;
  *(u16 *)&v5->bSummnerRankStart = 256;
  sObjBG = v5->sObjBG;
  v7 = "";
  sObjBG->bEnabled = 0;
  v8 = Copy(v7);
  sObjBG->szString = v8;
  p_szString = &sObjBG->szString;
  *(char **)((char *)p_szString + 44) = 0;
  *(char **)((char *)p_szString + 36) = 0;
  *((u32 *)p_szString + 13) = 0;
  v10 = psSelf;
  *((u32 *)p_szString + 3) = 108;
  sObjBGSRank = v10->sObjBGSRank;
  LOBYTE(v10) = byte_5758A2E;
  *((u32 *)p_szString + 8) = 255;
  p_szString[7] = 0xFFFFFFFFLL;
  *((_OWORD *)p_szString + 1) = xmmword_3D06BB0;
  v12 = "";
  sObjBGSRank->bEnabled = 0;
  v13 = Copy(v12);
  sObjBGSRank->szString = v13;
  v14 = &sObjBGSRank->szString;
  *(char **)((char *)v14 + 44) = 0;
  *(char **)((char *)v14 + 36) = 0;
  *((u32 *)v14 + 13) = 0;
  sObjBGRaido = psSelf->sObjBGRaido;
  v16 = byte_5758A2E;
  *((u32 *)v14 + 3) = 108;
  *((u32 *)v14 + 8) = 255;
  v14[7] = 0xFFFFFFFFLL;
  *((_OWORD *)v14 + 1) = xmmword_3D06BB0;
  v17 = "";
  sObjBGRaido->bEnabled = 0;
  v18 = Copy(v17);
  sObjBGRaido->szString = v18;
  v19 = &sObjBGRaido->szString;
  *(char **)((char *)v19 + 44) = 0;
  *(char **)((char *)v19 + 36) = 0;
  *((u32 *)v19 + 13) = 0;
  sObjCyusei = psSelf->sObjCyusei;
  v21 = byte_5758A2E;
  *((u32 *)v19 + 3) = 108;
  *((u32 *)v19 + 8) = 255;
  v19[7] = 0xFFFFFFFFLL;
  *((_OWORD *)v19 + 1) = xmmword_3D06BB0;
  v22 = "";
  sObjCyusei->bEnabled = 0;
  v23 = Copy(v22);
  sObjCyusei->szString = v23;
  v24 = &sObjCyusei->szString;
  *(char **)((char *)v24 + 44) = 0;
  *(char **)((char *)v24 + 36) = 0;
  *((u32 *)v24 + 13) = 0;
  sObjSRank = psSelf->sObjSRank;
  v26 = byte_5758A2E;
  *((u32 *)v24 + 3) = 108;
  *((u32 *)v24 + 8) = 255;
  v24[7] = 0xFFFFFFFFLL;
  *((_OWORD *)v24 + 1) = xmmword_3D06BB0;
  v27 = "";
  sObjSRank->bEnabled = 0;
  v28 = Copy(v27);
  sObjSRank->szString = v28;
  v29 = &sObjSRank->szString;
  *(char **)((char *)v29 + 44) = 0;
  *(char **)((char *)v29 + 36) = 0;
  *((u32 *)v29 + 13) = 0;
  sObjRaido = psSelf->sObjRaido;
  v31 = byte_5758A2E;
  *((u32 *)v29 + 3) = 108;
  *((u32 *)v29 + 8) = 255;
  v29[7] = 0xFFFFFFFFLL;
  *((_OWORD *)v29 + 1) = xmmword_3D06BB0;
  v32 = "";
  sObjRaido->bEnabled = 0;
  v33 = Copy(v32);
  sObjRaido->szString = v33;
  v34 = &sObjRaido->szString;
  *(char **)((char *)v34 + 44) = 0;
  *(char **)((char *)v34 + 36) = 0;
  *((u32 *)v34 + 13) = 0;
  sObjBlur = psSelf->sObjBlur;
  v36 = byte_5758A2E;
  *((u32 *)v34 + 3) = 108;
  *((u32 *)v34 + 8) = 255;
  v34[7] = 0xFFFFFFFFLL;
  *((_OWORD *)v34 + 1) = xmmword_3D06BB0;
  v37 = "";
  sObjBlur->bEnabled = 0;
  v38 = Copy(v37);
  sObjBlur->szString = v38;
  v39 = &sObjBlur->szString;
  *(char **)((char *)v39 + 44) = 0;
  *(char **)((char *)v39 + 36) = 0;
  *((u32 *)v39 + 13) = 0;
  v40 = psSelf;
  v39[7] = 0xFFFFFFFFLL;
  *((u32 *)v39 + 3) = 108;
  *((_OWORD *)v39 + 1) = xmmword_3D06BB0;
  v41 = v40->sObjBGSRank;
  v42 = v40->sObjBGRaido;
  v43 = v40->sObjSRank;
  v41->bEnabled = 1;
  v42->bEnabled = 1;
  v41->iSprNo = SummonerRank2SprNo;
  v43->iSprNo = SummonerRank2SprNo;
  *((u32 *)v39 + 8) = 255;
}

// 0x20aa820
cmpSummnerRankFunc_t cmpSummnerRankStateWait(cmpSummnerRank_t *psSelf) {
  tagOBJECT_WORK *sObjBG;
  sdatUnitWork_t *psUnit;
  s32 TotalCyuusei;
  tagOBJECT_WORK *sObjCyusei;
  s32 v8;
  char **p_szString;
  char *szString;
  Il2CppObject *v11;
  char *v12;
  char *v13;
  u32 SummonerRank2SprNo;
  Il2CppClass *klass;
  s32 v18;
  s32 syougou;
  RankText *SetRank;
  Il2CppClass **typeHierarchy;
  char *text;
  char *LocalizeText;
  tagOBJECT_WORK *v28;
  cmpSummnerRankFunc_t v29;
  s64 v32;
  s32 data;

  if (!psSelf->bSummnerRankStart)
    return 0;
  psSelf->bSummnerRankStart = 0;
  sObjBG = psSelf->sObjBG;
  sObjBG->bEnabled = 1;
  sObjBG->iOT = 109;
  sObjBG->iAlpha = 0;
  psUnit = psSelf->psUnit;
  TotalCyuusei = datGetTotalCyuusei(psUnit);
  sObjCyusei = psSelf->sObjCyusei;
  if (TotalCyuusei >= 99999)
    v8 = 99999;
  else
    v8 = TotalCyuusei;
  data = v8 & ~(v8 >> 31);
  szString = sObjCyusei->szString;
  p_szString = &sObjCyusei->szString;
  v11 = Box(s32, &data);
  v12 = Format("{0,5:d}", v11, 0);
  v13 = Concat_54766928(szString, v12, 0);
  *p_szString = v13;
  psSelf->sObjCyusei->bEnabled = 1;
  SummonerRank2SprNo = cmpGetSummonerRank2SprNo(0);
  klass = _get_Instance()[8].klass;
  if (SummonerRank2SprNo <= 1)
    v18 = 1;
  else
    v18 = SummonerRank2SprNo;
  if (!GBWK->syougouRemove)
  {
    typeHierarchy = klass->_2.typeHierarchy;
    v32 = (s64)rankText + 8 * v18;
    text = *(char **)(v32 + 32);
    goto LABEL_22;
  }
  syougou = GBWK->player->syougou;
  SetRank = cmpGetSetRank(syougou);
  typeHierarchy = klass->_2.typeHierarchy;
  text = SetRank->text;
LABEL_22:
  LocalizeText = GetLocalizeText(text, 1);
  ((*typeHierarchy)->vtable[66].methodPtr)(typeHierarchy, LocalizeText, (*typeHierarchy)->vtable[66].method);
  v28 = psSelf->sObjCyusei;
  psSelf->cnt = 0;
  v28->iOT = 109;
  v29 = (cmpSummnerRankFunc_t)Allocate(cmpSummnerRankFunc_t);
  _ctor(v29, 0, Method_Project_cmpStatus_SummnerRankStateBGHalf__, 0);
  return v29;
}

// 0x20aab20
cmpSummnerRankFunc_t cmpSummnerRankStateBGHalf(cmpSummnerRank_t *psSelf) {
  Il2CppObject *Instance;
  tagOBJECT_WORK *sObjBG;
  s32 v7;
  bool v8;
  cmpSummnerRankFunc_t v11;

  if (!cmpCheckHandle())
    return 0;
  Instance = _get_Instance();
  RaidouSyougouBrackAnim(Instance[8].klass, 0, 0);
  ++psSelf->cnt;
  sObjBG = psSelf->sObjBG;
  v7 = sObjBG->iAlpha + 2;
  v8 = sObjBG->iAlpha - 78 < 0;
  sObjBG->iAlpha = v7;
  if (v8 != __OFSUB__(v7, 80))
    return 0;
  psSelf->bSummnerRankWait = 0;
  sObjBG->iAlpha = 80;
  psSelf->cnt = 0;
  cmpInstanceTitleEff();
  v11 = (cmpSummnerRankFunc_t)Allocate(cmpSummnerRankFunc_t);
  _ctor(v11, 0, Method_Project_cmpStatus_SummnerRankStateCyuuseiMeimetsu__, 0);
  return v11;
}

// 0x20aac80
cmpSummnerRankFunc_t cmpSummnerRankStateCyuuseiMeimetsu(cmpSummnerRank_t *psSelf) {
  tagOBJECT_WORK *sObjSRank;
  const MethodInfo_32670E0 *v4;
  Il2CppClass *klass;
  cmpSummnerRankFunc_t v7;

  ++psSelf->cnt;
  if (!psSelf->bSummnerRankStart)
    return 0;
  *(u16 *)&psSelf->bSummnerRankStart = 256;
  sObjSRank = psSelf->sObjSRank;
  sObjSRank->bEnabled = 1;
  v4 = Method_Project_SingletonMonoBehaviour_CampManager__get_Instance__;
  *(u64 *)&sObjSRank->fDelta = 0;
  sObjSRank->fAlpha = 0.0;
  sObjSRank->iOT = 109;
  psSelf->cnt = 0;
  klass = _get_Instance(v4)[8].klass;
  CallSyougouAnim(klass, GBWK->player->setSyougou, 0);
  v7 = (cmpSummnerRankFunc_t)Allocate(cmpSummnerRankFunc_t);
  _ctor(v7, 0, Method_Project_cmpStatus_SummnerRankStateSummnerRankOldFadein__, 0);
  return v7;
}

// 0x20aadc0
cmpSummnerRankFunc_t cmpSummnerRankStateSummnerRankOldFadein(cmpSummnerRank_t *psSelf) {
  s32 iCounter;
  cmpSummnerRankFunc_t v5;
  f32 v7;
  s32 v8;
  tagOBJECT_WORK *sObjSRank;

  ++psSelf->cnt;
  iCounter = psSelf->iCounter;
  if (iCounter <= 10)
  {
    v7 = (f32)iCounter / 10.0;
    v8 = 255 * (s32)v7;
    if (v7 == INFINITY)
      v8 = 0x80000000;
    sObjSRank = psSelf->sObjSRank;
    sObjSRank->iAlpha = v8;
    sObjSRank->iMode = 1;
    return 0;
  }
  else
  {
    psSelf->sObjBGSRank->bEnabled = 0;
    psSelf->sObjSRank->iAlpha = 255;
    SE(21);
    psSelf->cnt = 0;
    v5 = (cmpSummnerRankFunc_t)Allocate(cmpSummnerRankFunc_t);
    _ctor(v5, 0, Method_Project_cmpStatus_SummnerRankStateSummnerRankOldBig__, 0);
    return v5;
  }
}

// 0x20aaed0
cmpSummnerRankFunc_t cmpSummnerRankStateSummnerRankOldBig(cmpSummnerRank_t *psSelf) {
  tagOBJECT_WORK *sObjSRank;
  f32 v4;
  f32 v5;
  cmpSummnerRankFunc_t v8;

  ++psSelf->cnt;
  sObjSRank = psSelf->sObjSRank;
  v4 = sObjSRank->fDelta + 0.002;
  v5 = v4 + sObjSRank->fSize;
  sObjSRank->fSizeH = v5;
  sObjSRank->fDelta = v4;
  sObjSRank->fSize = v5;
  sObjSRank->fSizeW = v5;
  if (v5 < 2.0)
    return 0;
  sObjSRank->fSizeH = 2.0;
  psSelf->cnt = 0;
  *(u64 *)&sObjSRank->fSize = 0x4000000040000000LL;
  psSelf->sObjBGRaido->bEnabled = 0;
  v8 = (cmpSummnerRankFunc_t)Allocate(cmpSummnerRankFunc_t);
  _ctor(v8, 0, Method_Project_cmpStatus_SummnerRankStateSummnerRankWait__, 0);
  return v8;
}

// 0x20aafc0
cmpSummnerRankFunc_t cmpSummnerRankStateSummnerRankWait(cmpSummnerRank_t *psSelf) {
  cmpSummnerRankFunc_t v4;

  ++psSelf->cnt;
  if (psSelf->iCounter < 20)
    return 0;
  psSelf->cnt = 0;
  v4 = (cmpSummnerRankFunc_t)Allocate(cmpSummnerRankFunc_t);
  _ctor(v4, 0, Method_Project_cmpStatus_SummnerRankStateSummnerRankFadeout__, 0);
  return v4;
}

// 0x20ab070
cmpSummnerRankFunc_t cmpSummnerRankStateSummnerRankFadeout(cmpSummnerRank_t *psSelf) {
  s32 SummonerRank2SprNo;
  tagOBJECT_WORK *sObjSRank;
  cmpSummnerRankFunc_t v7;
  tagOBJECT_WORK *v9;
  f32 fSizeH;
  f32 v11;

  ++psSelf->cnt;
  if (psSelf->iCounter > 10)
  {
    SummonerRank2SprNo = cmpGetSummonerRank2SprNo(0);
    psSelf->sObjBGSRank->iSprNo = SummonerRank2SprNo;
    sObjSRank = psSelf->sObjSRank;
    sObjSRank->iSprNo = SummonerRank2SprNo;
    sObjSRank->iAlpha = 255;
    sObjSRank->fSizeH = 0.0;
    sndSePlay(0);
    psSelf->cnt = 0;
    v7 = (cmpSummnerRankFunc_t)Allocate(cmpSummnerRankFunc_t);
    _ctor(v7, 0, Method_Project_cmpStatus_SummnerRankStateSummnerRankNewFadein__, 0);
    return v7;
  }
  v9 = psSelf->sObjSRank;
  v7 = 0;
  fSizeH = v9->fSizeH;
  v9->iAlpha -= 4;
  v11 = fSizeH + -0.2;
  v9->fSizeH = v11;
  if (v11 >= 0.0)
    return v7;
  v9->fSizeH = 0.0;
  return 0;
}

// 0x20ab1f0
cmpSummnerRankFunc_t cmpSummnerRankStateSummnerRankNewFadein(cmpSummnerRank_t *psSelf) {
  tagOBJECT_WORK *sObjSRank;
  f32 v4;
  RankText *SetRank;
  s32 SummonerRank2SprNo;
  void *unity_user_data;
  char *v12;
  char *LocalizeText;
  tagOBJECT_WORK *v15;
  tagOBJECT_WORK *sObjCyusei;
  tagOBJECT_WORK *sObjBlur;
  cmpSummnerRankFunc_t v18;

  ++psSelf->cnt;
  sObjSRank = psSelf->sObjSRank;
  v4 = sObjSRank->fSizeH + 0.2;
  sObjSRank->fSizeH = v4;
  if (v4 <= 2.0)
    return 0;
  if (!GBWK->player->setSyougou)
  {
    SummonerRank2SprNo = cmpGetSummonerRank2SprNo(0);
    unity_user_data = _get_Instance()[8].klass->_2.unity_user_data;
    v12 = rankText[SummonerRank2SprNo];
    LocalizeText = GetLocalizeText(v12, 1);
    (*(*(u64 *)unity_user_data + 1368))(unity_user_data, LocalizeText, *(u64 *)(*(u64 *)unity_user_data + 1376));
    goto LABEL_22;
  }
  goto LABEL_10;
LABEL_21:
  SummonerRank2SprNo = 0;
  goto LABEL_22;
LABEL_10:
  SetRank = cmpGetSetRank(-1);
  if (!SetRank)
    goto LABEL_21;
  SummonerRank2SprNo = SetRank->sprNo;
LABEL_22:
  sObjCyusei = psSelf->sObjCyusei;
  v15 = psSelf->sObjSRank;
  *(u64 *)&v15->fSize = 0x4000000040000000LL;
  v15->fSizeH = 2.0;
  sObjBlur = psSelf->sObjBlur;
  sObjCyusei->bEnabled = 0;
  sObjBlur->bEnabled = 1;
  sObjBlur->fSize = 2.0;
  sObjBlur->fDelta = 0.0;
  sObjBlur->iAlpha = 0;
  sObjBlur->fAlpha = 1.0;
  sObjBlur->iSprNo = SummonerRank2SprNo;
  sObjBlur->iOT = 109;
  psSelf->cnt = 0;
  v18 = (cmpSummnerRankFunc_t)Allocate(cmpSummnerRankFunc_t);
  _ctor(v18, 0, Method_Project_cmpStatus_SummnerRankStateSummnerRankNew__, 0);
  return v18;
}

// 0x20ab470
cmpSummnerRankFunc_t cmpSummnerRankStateSummnerRankNew(cmpSummnerRank_t *psSelf) {
  s32 v3;
  const MethodInfo_32670E0 *v4;
  s32 cnt;
  s32 iCounter;
  cmpSummnerRankFunc_t v7;
  Il2CppObject *Instance;
  s32 v10;
  f32 v11;
  s32 v12;
  tagOBJECT_WORK *sObjBlur;

  v3 = psSelf->cnt + 1;
  v4 = Method_Project_SingletonMonoBehaviour_CampManager__get_Instance__;
  psSelf->cnt = v3;
  if (v3 == LODWORD(_get_Instance(v4)[4].klass))
  {
    if (!GBWK->player->setSyougou)
      goto LABEL_10;
  }
  cnt = psSelf->cnt;
  if (cnt != HIDWORD(_get_Instance()[4].klass))
    goto LABEL_7;
LABEL_11:
  sndVoicePlayFile("PVA01A_25A_003", 0);
  iCounter = psSelf->iCounter;
  if (iCounter > 79)
    goto LABEL_8;
  goto LABEL_14;
LABEL_10:
  Instance = _get_Instance();
  TrigVignette(Instance[8].monitor, 0);
  v10 = psSelf->cnt;
  if (v10 == HIDWORD(_get_Instance()[4].klass))
    goto LABEL_11;
LABEL_7:
  iCounter = psSelf->iCounter;
  if (iCounter > 79)
  {
LABEL_8:
    psSelf->cnt = 0;
    psSelf->sObjBlur->bEnabled = 0;
    v7 = (cmpSummnerRankFunc_t)Allocate(cmpSummnerRankFunc_t);
    _ctor(v7, 0, Method_Project_cmpStatus_SummnerRankStateSummnerRankNewSmall__, 0);
    return v7;
  }
LABEL_14:
  v11 = (f32)(64 - iCounter) * 0.015625;
  if (v11 < 0.0)
    v11 = 0.0;
  v12 = (f32)(v11 * 255.0);
  if ((f32)(v11 * 255.0) == INFINITY)
    v12 = 0x80000000;
  sObjBlur = psSelf->sObjBlur;
  sObjBlur->fAlpha = v11;
  sObjBlur->iAlpha = v12;
  return 0;
}

// 0x20ab6b0
cmpSummnerRankFunc_t cmpSummnerRankStateSummnerRankNewSmall(cmpSummnerRank_t *psSelf) {
  tagOBJECT_WORK *sObjSRank;
  f32 fDelta;
  f32 v5;
  cmpSummnerRankFunc_t v14;

  ++psSelf->cnt;
  sObjSRank = psSelf->sObjSRank;
  fDelta = sObjSRank->fDelta;
  v5 = sObjSRank->fSize - fDelta;
  sObjSRank->fSizeH = v5;
  sObjSRank->fDelta = fDelta + -0.001;
  sObjSRank->fSize = v5;
  sObjSRank->fSizeW = v5;
  if (v5 >= 1.0)
    return 0;
  sObjSRank->iMode = 0;
  sObjSRank->iQ_frame = 14;
  *(_OWORD *)&sObjSRank->fSize = xmmword_3D06BB0;
  __asm { FMOV            V0.2S, #3.0 }
  *(u64 *)&sObjSRank->fQ_x_range = _D0;
  if (!GBWK->player->setSyougou)
    SE(8);
  psSelf->cnt = 0;
  psSelf->sObjCyusei->bEnabled = 0;
  GBWK->syougouRemove = 0;
  v14 = (cmpSummnerRankFunc_t)Allocate(cmpSummnerRankFunc_t);
  _ctor(v14, 0, Method_Project_cmpStatus_SummnerRankStateSummnerRankNewQuake__, 0);
  return v14;
}

// 0x20ab840
cmpSummnerRankFunc_t cmpSummnerRankStateSummnerRankNewQuake(cmpSummnerRank_t *psSelf) {
  tagOBJECT_WORK *sObjRaido;
  cmpSummnerRankFunc_t v6;

  ++psSelf->cnt;
  if (psSelf->iCounter < 11)
    return 0;
  psSelf->cnt = 0;
  sObjRaido = psSelf->sObjRaido;
  sObjRaido->bEnabled = 1;
  sObjRaido->iAlpha = 255;
  sObjRaido->iOT = 109;
  sObjRaido->iInX = -256;
  v6 = (cmpSummnerRankFunc_t)Allocate(cmpSummnerRankFunc_t);
  _ctor(v6, 0, Method_Project_cmpStatus_SummnerRankStateSummnerRankRaidoPika__, 0);
  return v6;
}

// 0x20ab910
cmpSummnerRankFunc_t cmpSummnerRankStateSummnerRankRaidoPika(cmpSummnerRank_t *psSelf) {
  tagOBJECT_WORK *sObjRaido;
  s32 v4;
  bool v5;
  tagOBJECT_WORK *sObjBGRaido;
  cmpSummnerRankFunc_t v8;

  ++psSelf->cnt;
  sObjRaido = psSelf->sObjRaido;
  v4 = sObjRaido->iInX + 12;
  v5 = sObjRaido->iInX + 11 < 0;
  sObjRaido->iInX = v4;
  if (v5 != __OFSUB__(v4, 1))
    return 0;
  *(u64 *)&sObjRaido->fQ_x_range = 0x3F80000040800000LL;
  *(u64 *)&sObjRaido->iQ_frame = 14;
  if (!GBWK->player->setSyougou)
    SE(8);
  sObjBGRaido = psSelf->sObjBGRaido;
  psSelf->cnt = 0;
  sObjBGRaido->bEnabled = 0;
  v8 = (cmpSummnerRankFunc_t)Allocate(cmpSummnerRankFunc_t);
  _ctor(v8, 0, Method_Project_cmpStatus_SummnerRankStateBGFukki__, 0);
  return v8;
}

// 0x20aba40
cmpSummnerRankFunc_t cmpSummnerRankStateBGFukki(cmpSummnerRank_t *psSelf) {
  void *klass;
  s32 SummonerRank2SprNo;
  void *animSyougouA;
  char *v7;
  char *LocalizeText;
  tagOBJECT_WORK *sObjBG;
  s32 v10;
  bool v11;
  tagOBJECT_WORK *sObjBGSRank;
  tagOBJECT_WORK *sObjBGRaido;
  tagOBJECT_WORK *sObjRaido;
  cmpSummnerRankFunc_t v16;

  klass = _get_Instance()[8].klass;
  SummonerRank2SprNo = cmpGetSummonerRank2SprNo(0);
  animSyougouA = klass->animSyougouA;
  v7 = rankText[SummonerRank2SprNo];
  LocalizeText = GetLocalizeText(v7, 1);
  (animSyougouA->klass->vtable._66_set_text.methodPtr)(animSyougouA, LocalizeText, animSyougouA->klass->vtable._66_set_text.method);
  RaidouSyougouBrackAnim(klass, 1, 0);
  ++psSelf->cnt;
  if (psSelf->iCounter < 70)
    return 0;
  sObjBG = psSelf->sObjBG;
  v10 = sObjBG->iAlpha - 2;
  v11 = sObjBG->iAlpha == 2;
  sObjBG->iAlpha = v10;
  if (v10 >= 0 && !v11)
    return 0;
  sObjBGSRank = psSelf->sObjBGSRank;
  sObjBGRaido = psSelf->sObjBGRaido;
  sObjBG->bEnabled = 0;
  sObjBG->iAlpha = 0;
  psSelf->bSummnerRankWait = 0;
  sObjBGSRank->bEnabled = 1;
  sObjBGRaido->bEnabled = 1;
  sObjRaido = psSelf->sObjRaido;
  psSelf->sObjSRank->bEnabled = 0;
  sObjRaido->bEnabled = 0;
  psSelf->cnt = 0;
  v16 = (cmpSummnerRankFunc_t)Allocate(cmpSummnerRankFunc_t);
  _ctor(v16, 0, Method_Project_cmpStatus_SummnerRankStateWait__, 0);
  return v16;
}

// 0x20abc10
void cmpSummnerRankDrawBg(tagOBJECT_WORK *psSelf, sprHandle_t *hSpr) {
  ;
}

// 0x20abc20
void cmpSummnerRankDrawCyusei(tagOBJECT_WORK *psSelf, sprHandle_t *hSpr) {
  if (psSelf->bEnabled)
  {
    psSelf->fCounter = psSelf->fCounter + 0.1;
  }
}

// 0x20abca0
void cmpSummnerRankDrawSummnerRank(tagOBJECT_WORK *psSelf, sprHandle_t *hSpr) {
  RankText *SetRank;
  char *text;
  s32 iSprNo;
  s32 syougouRemove;
  Il2CppObject *Instance;
  s64 v13;
  s64 v14;
  f32 v15;
  f32 v16;

  if (psSelf->bEnabled)
  {
    if (GBWK->player->setSyougou)
    {
      SetRank = cmpGetSetRank(-1);
      if (SetRank)
      {
        text = SetRank->text;
        goto LABEL_28;
      }
      text = 0;
LABEL_28:
      Instance = _get_Instance();
      RaidouRankDraw(Instance[8].klass, text, 0);
      if ((psSelf->iQ_frame & 0x80000000) == 0)
      {
        sub_1B34D00(0, v13);
        sub_1B34D00(0, v14);
        v15 = psSelf->fQ_x_range + -0.3;
        v16 = psSelf->fQ_y_range + -0.3;
        psSelf->fQ_x_range = v15;
        psSelf->fQ_y_range = v16;
        if (v15 < 0.0)
          psSelf->fQ_x_range = 0.0;
        if (v16 < 0.0)
          psSelf->fQ_y_range = 0.0;
        --psSelf->iQ_frame;
      }
      return;
    }
    if (psSelf->iSprNo <= 1u)
      iSprNo = 1;
    else
      iSprNo = psSelf->iSprNo;
    syougouRemove = GBWK->syougouRemove;
    if (syougouRemove)
    {
      syougouRemove = GBWK->syougouRemove;
      GBWK->player->syougou = syougouRemove;
      text = cmpGetSetRank(syougouRemove)->text;
      goto LABEL_28;
    }
    text = rankText[iSprNo];
    GBWK->player->syougou = iSprNo;
    goto LABEL_28;
  }
}

// 0x20abed0
void cmpSummnerRankDrawRaido(tagOBJECT_WORK *psSelf, sprHandle_t *hSpr) {
  s64 v4;
  f32 v5;
  f32 v6;

  if (psSelf->bEnabled && (psSelf->iQ_frame & 0x80000000) == 0)
  {
    sub_1B34D00(0, hSpr);
    sub_1B34D00(0, v4);
    v5 = psSelf->fQ_x_range + -0.3;
    v6 = psSelf->fQ_y_range + -0.3;
    psSelf->fQ_x_range = v5;
    psSelf->fQ_y_range = v6;
    if (v5 < 0.0)
      psSelf->fQ_x_range = 0.0;
    if (v6 < 0.0)
      psSelf->fQ_y_range = 0.0;
    --psSelf->iQ_frame;
  }
}

// 0x20abf50
void cmpSummnerRankDrawSummnerRankBlur(tagOBJECT_WORK *psSelf, sprHandle_t *hSpr) {
  if (psSelf->bEnabled)
    evtBitCheck(2079);
}

// 0x20aa4c0
void cmpSummnerRankDraw(cmpSummnerRank_t *psSelf, sprHandle_t *hSpr) {
  sprHandle_t *v5;
  s32 iAlphaRate;
  tagOBJECT_WORK *sObjBGRaido;
  tagOBJECT_WORK *sObjBGSRank;
  s64 v11;
  tagOBJECT_WORK *v12;
  s64 v13;
  f32 v14;
  f32 v15;
  sprHandle_t *v16;
  tagOBJECT_WORK *sObjCyusei;
  Il2CppObject *Instance;
  tagOBJECT_WORK *sObjRaido;
  s64 v24;
  f32 v25;
  f32 v26;

  if (!evtBitCheck(2079))
  {
    iAlphaRate = psSelf->iAlphaRate;
    sObjBGSRank = psSelf->sObjBGSRank;
    sObjBGRaido = psSelf->sObjBGRaido;
    sObjBGSRank->iAlpha = iAlphaRate;
    sObjBGRaido->iAlpha = iAlphaRate;
    cmpSummnerRankDrawSummnerRank(sObjBGSRank, v5);
    v12 = psSelf->sObjBGRaido;
    if (v12->bEnabled && (v12->iQ_frame & 0x80000000) == 0)
    {
      sub_1B34D00(0, v11);
      sub_1B34D00(0, v13);
      v14 = v12->fQ_x_range + -0.3;
      v15 = v12->fQ_y_range + -0.3;
      v12->fQ_x_range = v14;
      v12->fQ_y_range = v15;
      if (v14 < 0.0)
        v12->fQ_x_range = 0.0;
      if (v15 < 0.0)
        v12->fQ_y_range = 0.0;
      --v12->iQ_frame;
    }
  }
  if (evtBitCheck(42))
  {
    sObjCyusei = psSelf->sObjCyusei;
    goto LABEL_18;
  }
  else
  {
    Instance = _get_Instance();
    KouhoRankDraw(Instance[8].klass, 0);
    sObjCyusei = psSelf->sObjCyusei;
LABEL_18:
    goto LABEL_19;
  }
LABEL_19:
  if (sObjCyusei->bEnabled)
    sObjCyusei->fCounter = sObjCyusei->fCounter + 0.1;
  sObjRaido = psSelf->sObjRaido;
  if (sObjRaido->bEnabled && (sObjRaido->iQ_frame & 0x80000000) == 0)
  {
    sub_1B34D00(0, v16);
    sub_1B34D00(0, v24);
    v25 = sObjRaido->fQ_x_range + -0.3;
    v26 = sObjRaido->fQ_y_range + -0.3;
    sObjRaido->fQ_x_range = v25;
    sObjRaido->fQ_y_range = v26;
    if (v25 < 0.0)
      sObjRaido->fQ_x_range = 0.0;
    if (v26 < 0.0)
      sObjRaido->fQ_y_range = 0.0;
    --sObjRaido->iQ_frame;
  }
  cmpSummnerRankDrawSummnerRank(psSelf->sObjSRank, v16);
  if (psSelf->sObjBlur->bEnabled)
    evtBitCheck(2079);
}

// 0x20abf70
void cmpDrawPartsName(tagCMP_STATUS_WORK *wk, s32 a_alphaRate) {
  sdatUnitWork_t *unit;
  sdatUnitWork_t *v6;
  s32 devilid;
  Il2CppObject *Instance;
  s64 v9;
  void *klass;
  s64 type;
  s32 v13;
  void *v15;
  u32 v17;
  s32 v18;
  Il2CppObject *v19;
  char *v20;
  char *v21;
  s32 v23;
  s64 v24;
  s32 v25;
  s32 v27;
  u32 v28;
  s32 v29;
  u32 v30;
  s32 v31;
  s32 v32;
  s32 v34;
  u32 uniq_code;
  s32 StockDevilIndex;
  u32 level;
  u32 v38;
  Il2CppObject *v39;
  char *v40;
  char *v41;
  s64 v43;
  u32 v44;
  sdatParaWork_t *now;
  s32 maxhp;
  s32 hp;
  s32 v48;
  s32 v49;
  s32 v50;
  Il2CppObject *v51;
  char *v52;
  char *v53;
  s64 v55;
  s32 v56;
  u32 v57;
  s32 v58;
  s32 v59;
  Il2CppObject *v60;
  char *v61;
  char *v62;
  sprHandle_t *SpriteHnd;
  s32 chuusei;
  sprHandle_t *v66;
  s32 raceid;
  char *v68;
  CmpPassTextSet *sei;
  CmpPassTextSet *mei;
  char *v73;
  u32 BstNo;
  s32 vice;
  s32 ViceLevel;
  s32 v77;
  s32 v78;
  s32 v79;
  s32 v80;
  Il2CppObject *v81;
  char *v82;
  char *v83;
  s32 v85;
  s32 v86;
  s32 v88;
  bool v89;
  s32 v90;
  s64 v91;
  s32 v92;
  s32 v94;
  u32 v95;
  s32 v96;
  s32 v97;
  s32 v98;
  s32 v99;
  Il2CppObject *v100;
  char *v101;
  char *v102;
  s64 v105;
  s32 v106;
  u32 v107;
  sdatPlayerUnitWork_t *player;
  s32 mag;
  s32 v110;
  s32 v111;
  s32 v112;
  s32 v113;
  Il2CppObject *v114;
  char *v115;
  char *v116;
  s32 maxmag;
  s64 v120;
  u32 v121;
  sdatPlayerUnitWork_t *v123;
  s32 v125;
  s32 v126;
  s32 v127;
  s32 v128;
  Il2CppObject *v129;
  char *v130;
  s32 TotalCyuusei;
  s32 v133;
  Il2CppObject *v134;
  char *v135;
  char *v136;
  CmpPassTextSet *v138;
  char *v139;
  CmpPassTextSet *v140;
  char *v141;
  u32 v142;
  u32 v143;
  sdatUnitWork_t *mitamaCombDvl;
  sdatParaWork_t *v146;
  s32 v147;
  s32 v148;
  s32 v149;
  u32 data;

  unit = wk->unit;
  v6 = Allocate(sdatUnitWork_t);
  _ctor(v6, 0);
  devilid = unit->devilid;
  Instance = _get_Instance();
  v9 = (u32)unit->devilid;
  if (devilid > 0)
  {
    klass = Instance[10].klass;
    (klass->klass->vtable._23_AttributeUiDraw.methodPtr)(klass, v9, klass->klass->vtable._23_AttributeUiDraw.method);
    passPar->type = 2;
    type = wk->type;
    if (type != 268566784)
    {
      if (type == 268501248)
      {
        v13 = unit->devilid;
LABEL_10:
        datCreateDevilUnit(v13, v6);
LABEL_35:
        level = (u8)unit->level;
        if (level >= 0x63)
          level = 99;
        if (unit->level >= 0)
          v38 = level;
        else
          v38 = 0;
        data = v38;
        v39 = Box(s32, &data);
        v40 = Format("{0,2:d}", v39, 0);
        v41 = Concat_54766928(0, v40, 0);
        SetText(passPar->lv, v41, 0xA09DC380, 0);
        v43 = wk->type;
        if (v43 == 268566784 || v43 == 268501248)
        {
          v44 = -1600273536;
          if (unit->now->hp != v6->now->hp)
          {
            if (v6->devilid)
              v44 = 1692838528;
            else
              v44 = -1600273536;
          }
        }
        else
        {
          now = unit->now;
          v44 = 1967865216;
          maxhp = now->maxhp;
          if (maxhp >= 1)
          {
            hp = now->hp;
            if (!datCheckDying(unit))
            {
              if (100 * hp / maxhp <= 49)
                v44 = -1264556928;
              else
                v44 = -1600273536;
            }
          }
        }
        v48 = unit->now->hp;
        if ((u32)v48 >= 0x3E7)
          v49 = 999;
        else
          v49 = unit->now->hp;
        if (v48 >= 0)
          v50 = v49;
        else
          v50 = 0;
        data = v50;
        v51 = Box(s32, &data);
        v52 = Format("{0,3:d}", v51, 0);
        v53 = Concat_54766928(0, v52, 0);
        SetText(passPar->nowHp, v53, v44, 0);
        v55 = wk->type;
        if (v55 == 268501248 || v55 == 268566784)
        {
          v56 = unit->now->maxhp;
          if (v56 == v6->now->maxhp)
          {
            v57 = -1600273536;
          }
          else if (v6->devilid)
          {
            v57 = 1692838528;
          }
          else
          {
            v57 = -1600273536;
          }
        }
        else
        {
          v57 = -1600273536;
          v56 = unit->now->maxhp;
        }
        if ((u32)v56 >= 0x3E7)
          v58 = 999;
        else
          v58 = v56;
        if (v56 >= 0)
          v59 = v58;
        else
          v59 = 0;
        data = v59;
        v60 = Box(s32, &data);
        v61 = Format("{0,3:d}", v60, 0);
        v62 = Concat_54766928(0, v61, 0);
        SetText(passPar->maxHp, v62, v57, 0);
        SpriteHnd = cmpGetSpriteHnd(2);
        chuusei = unit->chuusei;
        v66 = SpriteHnd;
        itfCalcSpriteWidth(v66, 111, chuusei, 100);
        DrawPartsCyuuseiGaugeUnity(klass, unit->chuusei, 0);
        raceid = unit->raceid;
        v68 = sdatRaceName(raceid);
        sei = passPar->sei;
        passPar->kuda = unit->raceid;
        SetText(sei, v68, 0xA09DC380, 0);
        mei = passPar->mei;
        v73 = sdatDevilName(unit->devilid, 0);
        SetText(mei, v73, 0xA09DC380, 0);
        cmpGetBstNo(unit->badstatus);
        BstNo = cmpGetBstNo(unit->badstatus);
        BstIconDraw(klass, BstNo, 0);
        vice = unit->vice;
        ViceLevel = sBtlGetViceLevel(vice);
        ViceIconDraw(klass, ViceLevel, 0);
        DrawPartsUnity(klass, passPar, 0);
        return;
      }
      v34 = unit->devilid;
      uniq_code = unit->uniq_code;
      StockDevilIndex = datGetStockDevilIndex(v34, uniq_code);
      if (StockDevilIndex < 0)
        goto LABEL_35;
      v32 = StockDevilIndex;
LABEL_34:
      ClassCopy(v6, GBWK->player->stock_id[v32], 0);
      goto LABEL_35;
    }
    v29 = unit->devilid;
    v30 = unit->uniq_code;
    v31 = datGetStockDevilIndex(v29, v30);
    if ((v31 & 0x80000000) == 0)
    {
      v32 = v31;
      goto LABEL_34;
    }
    mitamaCombDvl = wk->mitamaCombDvl;
    if (mitamaCombDvl)
    {
      ClassCopy(v6, mitamaCombDvl, 0);
      goto LABEL_35;
    }
    v13 = unit->devilid;
    goto LABEL_10;
  }
  v15 = Instance[8].klass;
  (v15->klass->vtable._23_AttributeUiDraw.methodPtr)(v15, v9, v15->klass->vtable._23_AttributeUiDraw.method);
  passPar->type = 1;
  v17 = (u8)unit->level;
  v18 = (char)v17;
  if (v17 >= 0x63)
    v17 = 99;
  if (v18 < 0)
    v17 = 0;
  data = v17;
  v19 = Box(s32, &data);
  v20 = Format("{0,2:d}", v19, 0);
  v21 = Concat_54766928(0, v20, 0);
  v149 = a_alphaRate;
  v23 = 1853947776;
  SetText(passPar->lv, v21, 0xA09DC380, 0);
  v24 = wk->type;
  if (v24 == 268697601)
  {
    v25 = unit->now->hp;
    goto LABEL_22;
  }
  v24 = wk->type;
  if (v24 == 17039361 || v24 == 0x110040100LL || v24 == 268697856)
  {
    unit = wk->player->para;
    v25 = unit->now->hp;
LABEL_22:
    v27 = GBWK->player->para->now->hp;
    if (v25 <= v27)
    {
      v77 = unit->now->hp;
      v27 = GBWK->player->para->now->hp;
      if (v77 >= v27)
        v28 = -1600273536;
      else
        v28 = 1849704703;
    }
    else
    {
      v28 = 1853947776;
    }
    goto LABEL_102;
  }
  v146 = unit->now;
  v28 = 1967865216;
  v147 = v146->maxhp;
  if (v147 >= 1)
  {
    v148 = v146->hp;
    if (!datCheckDying(unit))
    {
      if (100 * v148 / v147 <= 49)
        v28 = -1264556928;
      else
        v28 = -1600273536;
    }
  }
LABEL_102:
  v78 = unit->now->hp;
  if ((u32)v78 >= 0x3E7)
    v79 = 999;
  else
    v79 = unit->now->hp;
  if (v78 >= 0)
    v80 = v79;
  else
    v80 = 0;
  data = v80;
  v81 = Box(s32, &data);
  v82 = Format("{0,3:d}", v81, 0);
  v83 = Concat_54766928(0, v82, 0);
  SetText(passPar->nowHp, v83, v28, 0);
  v85 = -1600273536;
  if (wk->type == 268697601)
  {
    v86 = unit->now->maxhp;
    v88 = GBWK->player->para->now->maxhp;
    v89 = v86 <= v88;
    v85 = 1853947776;
    if (v89)
    {
      v90 = unit->now->maxhp;
      v88 = GBWK->player->para->now->maxhp;
      if (v90 >= v88)
        v85 = -1600273536;
      else
        v85 = 1849704703;
    }
  }
  v91 = wk->type;
  if (v91 != 17039361)
  {
    if (v91 != 0x110040100LL && v91 != 268697856)
    {
      v95 = v85;
      goto LABEL_136;
    }
  }
  v92 = unit->now->maxhp;
  v94 = GBWK->player->para->now->maxhp;
  v89 = v92 <= v94;
  v95 = 1853947776;
  if (v89)
  {
    v96 = unit->now->maxhp;
    v94 = GBWK->player->para->now->maxhp;
    if (v96 >= v94)
      v95 = v85;
    else
      v95 = 1849704703;
  }
LABEL_136:
  v97 = unit->now->maxhp;
  if ((u32)v97 >= 0x3E7)
    v98 = 999;
  else
    v98 = unit->now->maxhp;
  if (v97 >= 0)
    v99 = v98;
  else
    v99 = 0;
  data = v99;
  v100 = Box(s32, &data);
  v101 = Format("{0,3:d}", v100, 0);
  v102 = Concat_54766928(0, v101, 0);
  SetText(passPar->maxHp, v102, v95, 0);
  v105 = wk->type;
  if (v105 == 17039361)
    goto LABEL_152;
  if (v105 == 0x110040100LL || v105 == 268697856)
  {
LABEL_152:
    player = wk->player;
    mag = player->mag;
    v110 = GBWK->player->mag;
    if (mag > v110)
    {
      v107 = 1853947776;
LABEL_161:
      v106 = player->mag;
      goto LABEL_162;
    }
    v111 = player->mag;
    v110 = GBWK->player->mag;
    player = wk->player;
    if (v111 >= v110)
      v107 = -1600273536;
    else
      v107 = 1849704703;
    goto LABEL_161;
  }
  v106 = GBWK->player->mag;
  if (v105 != 0x8000000)
  {
    v107 = -1600273536;
    if (v105 != 268697601)
      goto LABEL_162;
    goto LABEL_152;
  }
  v107 = -1600273536;
  v107 = -1600273536;
  player = GBWK->player;
  goto LABEL_161;
LABEL_162:
  if ((u32)v106 >= 0x12C)
    v112 = 300;
  else
    v112 = v106;
  if (v106 >= 0)
    v113 = v112;
  else
    v113 = 0;
  data = v113;
  v114 = Box(s32, &data);
  v115 = Format("{0,4:d}", v114, 0);
  v116 = Concat_54766928(0, v115, 0);
  SetText(passPar->mag, v116, v107, 0);
  maxmag = GBWK->player->maxmag;
  v120 = wk->type;
  if (v120 > 268697600)
    goto LABEL_174;
  if (v120 != 17039361)
  {
    v121 = -1600273536;
    if (v120 != 0x8000000)
      goto LABEL_193;
    v23 = -1600273536;
    v123 = GBWK->player;
LABEL_192:
    maxmag = v123->maxmag;
    v121 = v23;
    goto LABEL_193;
  }
LABEL_184:
  v123 = wk->player;
  v125 = v123->maxmag;
  v123 = wk->player;
  v126 = GBWK->player->maxmag;
  if (v125 <= v126)
  {
    v127 = v123->maxmag;
    v126 = GBWK->player->maxmag;
    v123 = wk->player;
    if (v127 >= v126)
      v23 = -1600273536;
    else
      v23 = 1849704703;
  }
  goto LABEL_192;
LABEL_174:
  if (v120 == 268697601)
    goto LABEL_184;
  if (v120 == 0x110040100LL)
    goto LABEL_184;
  v121 = -1600273536;
  if (v120 == 268697856)
    goto LABEL_184;
LABEL_193:
  if ((u32)maxmag >= 0x12C)
    v128 = 300;
  else
    v128 = maxmag;
  if (maxmag < 0)
    v128 = 0;
  data = v128;
  v129 = Box(s32, &data);
  v130 = Format("{0,3:d}", v129, 0);
  SetText(passPar->maxMag, v130, v121, 0);
  TotalCyuusei = datGetTotalCyuusei(unit);
  if ((u32)TotalCyuusei >= 0x1869F)
    v133 = 99999;
  else
    v133 = TotalCyuusei;
  if (TotalCyuusei < 0)
    v133 = 0;
  data = v133;
  v134 = Box(s32, &data);
  v135 = Format("{0,5:d}", v134, 0);
  v136 = Concat_54766928(0, v135, 0);
  SetText(passPar->allCyuusei, v136, 0xA09DC380, 0);
  v138 = passPar->sei;
  v139 = frGet1NString();
  SetText(v138, v139, 0xA09DC380, 0);
  v140 = passPar->mei;
  v141 = frGet2NString();
  SetText(v140, v141, 0xA09DC380, 0);
  v142 = cmpGetBstNo(unit->badstatus);
  itfIconDrawBadStatus(250, 64, 256, (u8)v149, v142, 108);
  v143 = cmpGetBstNo(unit->badstatus);
  BstIconDraw(v15, v143, 0);
  cmpSummnerRankMngExecute(wk->sSummnerRankMng, unit, v149);
  DrawPartsUnity(v15, passPar, 0);
}

// 0x20ad0e0
void cmpDrawPartsExp(sdatUnitWork_t *a_pUnit, s32 a_alphaRate) {
  s32 devilid;
  s32 v5;
  s32 PlayerExp;
  s32 DevilExp;
  s32 v8;
  s32 v9;
  s32 v10;
  s32 level;
  s32 v13;
  sprHandle_t *SpriteHnd;
  u32 flag;
  Il2CppObject *Instance;
  Il2CppObject *v18;
  char *v19;
  s32 data;

  if (a_pUnit)
  {
    if ((a_pUnit->flag & 2) != 0)
    {
      level = a_pUnit->level;
      PlayerExp = datGetPlayerExp(level);
      v13 = datGetPlayerExp(a_pUnit->level + 1);
      v8 = v13 - PlayerExp;
      if (v13 != PlayerExp)
        goto LABEL_9;
    }
    else
    {
      if (a_pUnit->devilid < 1)
        return;
      devilid = (u16)a_pUnit->devilid;
      v5 = a_pUnit->level;
      PlayerExp = datGetDevilExp(devilid, v5);
      DevilExp = datGetDevilExp(a_pUnit->devilid, a_pUnit->level + 1);
      v8 = DevilExp - PlayerExp;
      if (DevilExp != PlayerExp)
      {
LABEL_9:
        v9 = a_pUnit->exp - PlayerExp;
        v10 = v8 - v9;
LABEL_16:
        SpriteHnd = cmpGetSpriteHnd(2);
        itfCalcSpriteWidth(SpriteHnd, 110, v9, v8);
        cmpGetSpriteHnd(2);
        flag = a_pUnit->flag;
        Instance = _get_Instance();
        if ((flag & 2) != 0)
          DrawExpGaugeUnity(Instance[8].klass, v9, v8, v10, 0xA09DC380, 0);
        else
          DrawExpGaugeUnity(Instance[10].klass, v9, v8, v10, 0xA09DC380, 0);
        data = v10;
        v18 = Box(s32, &data);
        v19 = Format("{0,6:d}", v18, 0);
        Concat_54766928(0, v19, 0);
        return;
      }
    }
    v10 = 0;
    v9 = 1;
    v8 = 1;
    goto LABEL_16;
  }
}

// 0x209da00
s32 cmpGetSwordNameLevel(s32 a_lv) {
  s32 i;
  s32 v5;

  for (i = 0; ; ++i)
  {
    v5 = arrSwordNameLv[i][0];
    if (v5 < 0)
      break;
    if (a_lv < (s16)v5)
      continue;
    if (arrSwordNameLv[i][1] >= a_lv)
      return i;
  }
  return -1;
}

// 0x20ad3f0
char *cmpGetSwordName(u8 *a_pParam) {
  s32 swordno;

  swordno = GBWK->player->swordno;
  return sdatItemName(swordno + 112);
}

// 0x20ad4a0
char *cmpGetSwordNameEx(s32 a_devilID) {
  u8 *v4;
  s32 swordno;

  v4 = NewSpecific(byte, 4u);
  cmpGetSwordParam(a_devilID, v4);
  swordno = GBWK->player->swordno;
  return sdatItemName(swordno + 112);
}

// 0x20ad5c0
u32 GetValueColor(s32 iOldVal, s32 iNewVal) {
  u32 v3;

  if (iOldVal >= iNewVal)
    v3 = -1600273536;
  else
    v3 = 1853947776;
  if (iOldVal <= iNewVal)
    return v3;
  else
    return 1849704703;
}

// 0x20ad5f0
void cmpDrawEquip(tagCMP_STATUS_WORK *wk, s32 a_type, s32 a_x, s32 a_y, s32 a_alphaRate, bool _top) {
  u8 v7;
  s32 *v12;
  s32 *v13;
  sdatPlayerUnitWork_t *player;
  s16 swordno;
  s32 swordatk;
  char *v19;
  sdatPlayerUnitWork_t *v21;
  s32 v22;
  Il2CppObject *v24;
  u32 v25;
  Il2CppObject *v26;
  char *v27;
  Il2CppObject *v28;
  tagCMP_STATUS_WORK *v29;
  sdatPlayerUnitWork_t *v30;
  s64 v32;
  s32 hp;
  Il2CppObject *v34;
  Il2CppObject *v35;
  s32 str;
  Il2CppObject *v37;
  Il2CppObject *v38;
  s32 tec;
  Il2CppObject *v40;
  Il2CppObject *v41;
  s32 vit;
  Il2CppObject *v43;
  Il2CppObject *v44;
  s32 luck;
  Il2CppObject *v46;
  Il2CppObject *v47;
  s32 m_hojo;
  SBTLSKILLP_TBL *Skilltbl;
  s32 v50;
  s64 type;
  s32 m_atk;
  char *v56;
  Il2CppObject *v57;
  s32 v58;
  s32 v59;
  u32 v60;
  Il2CppObject *v61;
  Il2CppObject *v62;
  s32 v63;
  Il2CppObject *v64;
  s32 v65;
  Il2CppObject *v66;
  s32 v67;
  bool v68;
  s32 v69;
  u32 v70;
  Il2CppObject *v71;
  s32 v72;
  Il2CppObject *v73;
  s32 v74;
  bool v75;
  s32 v76;
  u32 v77;
  Il2CppObject *v78;
  s32 v79;
  Il2CppObject *v80;
  s32 v81;
  bool v82;
  s32 v83;
  u32 v84;
  Il2CppObject *v85;
  s32 v86;
  Il2CppObject *v87;
  s32 v88;
  bool v89;
  s32 v90;
  u32 v91;
  Il2CppObject *v92;
  s32 v93;
  Il2CppObject *v94;
  char *v95;
  s32 v96;
  bool v97;
  s32 v98;
  u32 v99;
  Il2CppObject *v100;
  s32 v101;
  SBTLSKILLP_TBL *v102;
  Il2CppObject *v106;
  char *v107;
  bool v108;
  Il2CppObject *v109;
  char *v110;
  sdatPlayerUnitWork_t *p_player;
  s32 m_type;
  Il2CppObject *Instance;
  Il2CppObject *v117;
  s32 v118;
  s32 v119;
  s32 v120;
  s32 v121;
  s32 iMoveCnt;
  u8 a_alphaRatea;
  s32 v124;
  s32 v125;
  s32 v126;
  s32 v127;
  s32 v128;
  s32 data;

  v7 = a_alphaRate;
  cmpGetSpriteHnd(2);
  v12 = NewSpecific(s32, 5u);
  if ((u32)(a_type - 1) >= 2)
  {
    v119 = a_y;
    v13 = v12;
    v120 = a_x;
    a_alphaRatea = v7;
    if (a_type != 3)
    {
      if (!a_type)
      {
        if (wk->type == 268697601)
        {
          player = wk->player;
          swordno = player->swordno;
          swordatk = player->swordatk;
LABEL_164:
          v110 = sdatItemName(swordno + 144);
          if (wk->type == 268697601)
          {
            p_player = &wk->player;
          }
          else
          {
            p_player = &GBWK->player;
          }
          m_type = tbl[p_player->swordno]->m_type;
          Instance = _get_Instance();
          DetailsSwordTypeIconDraw(Instance[9].monitor, m_type, 2, 0);
          v117 = _get_Instance();
          WeaponDetailsTextDraw(v117[9].monitor, v110, 1, 2, "", 1, 0);
          if (wk->type == 268697601)
          {
            if (wk->swordatk == wk->player->swordatk)
              v25 = -1600273536;
            else
              v25 = 1692838528;
            v121 = 1;
          }
          else
          {
            v121 = 1;
            v25 = -1600273536;
          }
LABEL_24:
          data = swordatk;
          v26 = Box(s32, &data);
          v27 = Format("{0,3:d}", v26, 0);
          v28 = _get_Instance();
          WeaponParaDraw(v28[9].monitor, 5, 1, swordatk, v25, 2, 0);
          if (!wk)
          {
LABEL_73:
            if (!v121)
              goto LABEL_155;
            goto LABEL_74;
          }
          if (wk->type == 268697601)
          {
            v29 = wk;
            v30 = &wk->player;
          }
          else
          {
            v29 = wk;
            v30 = &GBWK->player;
          }
          v32 = v30->swordno;
          hp = tbl[v32]->m_paraBns->hp;
          v13[8] = hp;
          data = hp;
          v34 = Box(s32, &data);
          Format("{0,2:d}", v34, 0);
          v35 = _get_Instance();
          WeaponParaDraw(v35[9].monitor, 4, 0, v13[8], 0xA09DC380, 2, 0);
          str = tbl[v32]->m_paraBns->str;
          v13[9] = str;
          v128 = str;
          v37 = Box(s32, &v128);
          Format("{0,1:d}", v37, 0);
          v38 = _get_Instance();
          WeaponParaDraw(v38[9].monitor, 0, 1, v13[9], 0xA09DC380, 2, 0);
          tec = tbl[v32]->m_paraBns->tec;
          v13[10] = tec;
          v127 = tec;
          v40 = Box(s32, &v127);
          Format("{0,1:d}", v40, 0);
          v41 = _get_Instance();
          WeaponParaDraw(v41[9].monitor, 1, 2, v13[10], 0xA09DC380, 2, 0);
          vit = tbl[v32]->m_paraBns->vit;
          v13[11] = vit;
          v126 = vit;
          v43 = Box(s32, &v126);
          Format("{0,1:d}", v43, 0);
          v44 = _get_Instance();
          WeaponParaDraw(v44[9].monitor, 2, 3, v13[11], 0xA09DC380, 2, 0);
          luck = tbl[v32]->m_paraBns->luck;
          v13[12] = luck;
          v125 = luck;
          v46 = Box(s32, &v125);
          v27 = Format("{0,1:d}", v46, 0);
          v47 = _get_Instance();
          WeaponParaDraw(v47[9].monitor, 3, 4, v13[12], 0xA09DC380, 2, 0);
          wk = v29;
          m_hojo = tbl[v32]->m_hojo;
          if (!m_hojo)
          {
            if (!v121)
              goto LABEL_155;
            goto LABEL_74;
          }
          Skilltbl = sBtlGetSkilltbl(m_hojo);
          if (Skilltbl)
          {
            if ((Skilltbl->type & 0x1000) != 0)
            {
              v50 = 66;
LABEL_72:
              itfIconDrawSprite(v120 + 2, a_y + 51, 4096, a_alphaRatea, v50, 108);
              goto LABEL_73;
            }
            else if ((Skilltbl->type & 0x2000) != 0)
            {
              v50 = 65;
              goto LABEL_72;
            }
            else
            {
              if (sBtlChkRepeat(m_hojo))
                v50 = 64;
              else
                v50 = 67;
              goto LABEL_72;
            }
            goto LABEL_72;
          }
          if (!v121)
            goto LABEL_155;
LABEL_74:
          type = wk->type;
          if ((type == 17039361 || type == 0x110040100LL || type == 268697856) && wk->iMoveCnt)
          {
            if ((type & 0x1000000) != 0)
            {
              goto LABEL_146;
            }
            m_atk = tbl[g_equipNo]->m_atk;
            v56 = sdatItemName((s32)g_equipNo + 144);
            iMoveCnt = wk->iMoveCnt;
            v57 = _get_Instance();
            WeaponDetailsTextDraw(v57[9].monitor, v56, 1, 3, "", 1, 0);
            v58 = wk->swordatk;
            data = m_atk;
            if (v58 >= m_atk)
              v59 = -1600273536;
            else
              v59 = 1853947776;
            if (v58 <= m_atk)
              v60 = v59;
            else
              v60 = 1849704703;
            v61 = Box(s32, &data);
            Format("{0,3:d}", v61, 0);
            v62 = _get_Instance();
            WeaponParaDraw(v62[9].monitor, 5, 1, m_atk, v60, 3, 0);
            v63 = tbl[g_equipNo]->m_type;
            v64 = _get_Instance();
            DetailsSwordTypeIconDraw(v64[9].monitor, v63, 3, 0);
            v128 = tbl[g_equipNo]->m_paraBns->hp;
            v65 = v128;
            v66 = Box(s32, &v128);
            Format("{0,2:d}", v66, 0);
            v67 = v13[8];
            v68 = v67 <= v65;
            if (v67 >= v65)
              v69 = -1600273536;
            else
              v69 = 1853947776;
            if (v68)
              v70 = v69;
            else
              v70 = 1849704703;
            v71 = _get_Instance();
            WeaponParaDraw(v71[9].monitor, 4, 0, v65, v70, 3, 0);
            v72 = tbl[g_equipNo]->m_paraBns->str;
            v127 = v72;
            v73 = Box(s32, &v127);
            Format("{0,1:d}", v73, 0);
            v74 = v13[9];
            v75 = v74 <= v72;
            if (v74 >= v72)
              v76 = -1600273536;
            else
              v76 = 1853947776;
            if (v75)
              v77 = v76;
            else
              v77 = 1849704703;
            v78 = _get_Instance();
            WeaponParaDraw(v78[9].monitor, 0, 1, v72, v77, 3, 0);
            v79 = tbl[g_equipNo]->m_paraBns->tec;
            v126 = v79;
            v80 = Box(s32, &v126);
            Format("{0,1:d}", v80, 0);
            v81 = v13[10];
            v82 = v81 <= v79;
            if (v81 >= v79)
              v83 = -1600273536;
            else
              v83 = 1853947776;
            if (v82)
              v84 = v83;
            else
              v84 = 1849704703;
            v85 = _get_Instance();
            WeaponParaDraw(v85[9].monitor, 1, 2, v79, v84, 3, 0);
            v86 = tbl[g_equipNo]->m_paraBns->vit;
            v125 = v86;
            v87 = Box(s32, &v125);
            Format("{0,1:d}", v87, 0);
            v88 = v13[11];
            v89 = v88 <= v86;
            if (v88 >= v86)
              v90 = -1600273536;
            else
              v90 = 1853947776;
            if (v89)
              v91 = v90;
            else
              v91 = 1849704703;
            v92 = _get_Instance();
            WeaponParaDraw(v92[9].monitor, 2, 3, v86, v91, 3, 0);
            v93 = tbl[g_equipNo]->m_paraBns->luck;
            v124 = v93;
            v94 = Box(s32, &v124);
            v95 = Format("{0,1:d}", v94, 0);
            v96 = v13[12];
            v27 = v95;
            v97 = v96 <= v93;
            if (v96 >= v93)
              v98 = -1600273536;
            else
              v98 = 1853947776;
            if (v97)
              v99 = v98;
            else
              v99 = 1849704703;
            v100 = _get_Instance();
            WeaponParaDraw(v100[9].monitor, 3, 4, v93, v99, 3, 0);
            v101 = tbl[g_equipNo]->m_hojo;
            if (!v101)
            {
              v108 = 1;
              goto LABEL_156;
            }
            v102 = sBtlGetSkilltbl(v101);
            if (!v102)
              goto LABEL_205;
            goto LABEL_193;
            if (!v102)
            {
LABEL_205:
              v108 = 1;
LABEL_156:
              v109 = _get_Instance();
              RaidouAffterWeapon(v109, v108, 0);
              cmpGetSpriteHnd(0);
              goto LABEL_149;
LABEL_148:
              cmpGetSpriteHnd(0);
LABEL_149:
              data = GBWK->player->hgunnum;
              v106 = Box(s32, &data);
              v107 = Format("{0,2:d}", v106, 0);
              Concat_54766928(v27, v107, 0);
              cmpGetSpriteHnd(0);
              return;
LABEL_147:
              goto LABEL_148;
LABEL_146:
              goto LABEL_147;
            }
LABEL_193:
            if ((v102->type & 0x1000) != 0)
            {
              v118 = 66;
            }
            else if ((v102->type & 0x2000) != 0)
            {
              v118 = 65;
            }
            else
            {
              if (sBtlChkRepeat(v101))
                v118 = 64;
              else
                v118 = 67;
            }
            itfIconDrawSprite(v120 + iMoveCnt + 2, v119 + 51, 4096, a_alphaRatea, v118, 108);
            goto LABEL_205;
          }
LABEL_155:
          v108 = 0;
          goto LABEL_156;
        }
        else
        {
          swordatk = wk->swordatk;
          swordno = GBWK->player->swordno;
          goto LABEL_164;
        }
        goto LABEL_164;
      }
      v19 = 0;
      swordatk = 0;
LABEL_23:
      v24 = _get_Instance();
      WeaponDetailsTextDraw(v24[9].monitor, v19, 1, 2, "", 1, 0);
      v25 = -1600273536;
      v121 = 0;
      goto LABEL_24;
    }
    v21 = GBWK->player;
    swordatk = v21->swordatk;
    v22 = v21->swordno;
    v19 = sdatItemName(v22 + 144);
    cmpGetSpriteHnd(0);
    goto LABEL_23;
  }
}

// 0x20ae9b0
void cmpDrawEquipSword(s32 a_x, s32 a_y, s32 a_alphaRate) {
  cmpDrawEquip(0, 3, a_x, a_y, a_alphaRate, 0);
}

// 0x20aea40
void cmpDrawEquipBullet(s32 a_x, s32 a_y, s32 a_alphaRate, bool _top) {
  cmpDrawEquip(0, 2, a_x, a_y, a_alphaRate, 0);
}

// 0x20aead0
void cmpDrawPartsEquip(tagCMP_STATUS_WORK *wk, s32 a_alphaRate) {
  cmpDrawEquip(wk, 0, 20, 291, a_alphaRate, 0);
}

// 0x20aeb50
void cmpDrawSkillNameEx(SKLID a_id, s32 a_x, s32 a_y, u32 a_rgba, s32 a_alphaRate) {
  SBTLSKILLP_TBL *Skilltbl;
  s32 v12;

  Skilltbl = sBtlGetSkilltbl(a_id);
  if (Skilltbl)
    goto LABEL_5;
  return;
  if (Skilltbl)
  {
LABEL_5:
    if ((Skilltbl->type & 0x1000) != 0)
    {
      v12 = 66;
LABEL_20:
      itfIconDrawSprite(a_x, a_y, 256, a_alphaRate, v12, 108);
      return;
    }
    else if ((Skilltbl->type & 0x2000) != 0)
    {
      v12 = 65;
      goto LABEL_20;
    }
    else
    {
      if (sBtlChkRepeat(a_id))
        v12 = 64;
      else
        v12 = 67;
      goto LABEL_20;
    }
    goto LABEL_20;
  }
}

// 0x20aece0
void drawMiscHelp(FRW_HELP HelpType, SKLID uSkillID) {
  u16 v3;

  v3 = uSkillID;
  itfDrawMiscHelp(0xA09DC380, 1.0, HelpType, v3, 0);
}

// 0x20aed60
void cmpDrawNoneSklHelp(NoSklHelpType _type) {
  char *v3;
  char *v4;
  char *v5;
  char *v6;
  char *v7;

  v3 = "CMP_HELP_L0029";
  v4 = "CMP_HELP_L0030";
  v5 = "SKILLHELP_L0000";
  if (type == 1)
    v6 = v4;
  else
    v6 = v5;
  if (type)
    v7 = v6;
  else
    v7 = v3;
  ButtonLineHelpDispSet(1);
  ButtonLineHelpTextSet(v7, 0, 0, 0xA09DC380, 1);
}

// 0x20aee50
void cmpDrawPartsOmoideSkillSub(s32 a_x, s32 a_y, u32 a_alphaRate, itfSprList_t *a_pList) {
  cmpGetSpriteHnd(1);
}

// 0x20aeed0
void cmpDrawPartsOmoideSkill(tagCMP_STATUS_WORK *wk, s32 a_alphaRate) {
  u64 **monitor;
  Il2CppObject *v5;
  sdatUnitWork_t *unit;
  s32 topNo;
  void *DrawOmoideSkill;
  void *v10;
  s64 v11;
  s32 *m_Items;
  s32 v13;
  s32 v14;
  sdatUnitWork_t *v15;
  bool HaveSkill;
  s64 v17;
  void (__fastcall *v18)(u64 **, u64, s64, s64);
  s32 v19;
  sdatUnitWork_t *v21;
  u32 v22;
  s32 v23;
  u32 v24;
  u32 NowBookCnt;
  u32 BookCnt;
  sprHandle_t *v32;
  s32 v33;
  s64 type;
  s64 v37;
  char *TitleText;
  Il2CppObject *Instance;

  monitor = _get_Instance()[10].monitor;
  NewSpecific(SKLID, 8u);
  if ((wk->type & 0x8000000) == 0 && wk->modeSq != 2)
  {
    if (cmpSetSkillNow())
      goto LABEL_7;
    if (GohGohNativeSq() == 1)
      return;
    Instance = _get_Instance();
    (*(*(u64 *)Instance[10].monitor + 536))(Instance[10].monitor, 0, *(u64 *)(*(u64 *)Instance[10].monitor + 544));
    return;
  }
LABEL_7:
  v5 = _get_Instance();
  (*(*(u64 *)v5[10].monitor + 536))(v5[10].monitor, 1, *(u64 *)(*(u64 *)v5[10].monitor + 544));
  ((*monitor)[55])(monitor, 0, (*monitor)[56]);
  unit = wk->unit;
  topNo = wk->wkMemSklCur->topNo;
  DrawOmoideSkill = cmpGetDrawOmoideSkill(unit, topNo, 8);
  v10 = _ToArray(DrawOmoideSkill);
  if (wk->modeSq != 1)
    goto LABEL_13;
  if (!cmpSetSkillNow())
    goto LABEL_13;
  goto LABEL_12;
  if (cmpSetSkillNow())
LABEL_12:
    ((*monitor)[53])(monitor, 0xFFFFFFFFLL, 1, (*monitor)[54]);
LABEL_13:
  v11 = 0;
  m_Items = v10;
  v13 = 181;
  do
  {
    if (v11 != wk->wkMemSklCur->drwNo)
    {
      v14 = m_Items[v11];
LABEL_25:
      v19 = 1;
      v21 = wk->unit;
      goto LABEL_26;
    }
    v14 = m_Items[v11];
    if (wk->modeSq != 2)
      goto LABEL_25;
    v15 = wk->unit;
    HaveSkill = datOmoideSkillHaveSkill(v15, v14);
    v18 = (*monitor)[53];
    v17 = (*monitor)[54];
    if (v14 && HaveSkill)
    {
      v18(monitor, (u32)v11, 2, v17);
      v19 = 0;
      v21 = wk->unit;
      goto LABEL_26;
    }
    else
    {
      v18(monitor, (u32)v11, 1, v17);
      v19 = 0;
      v21 = wk->unit;
LABEL_26:
      if (datOmoideSkillHaveSkill(v21, v14))
        goto LABEL_27;
      goto LABEL_30;
    }
    if (datOmoideSkillHaveSkill(v21, v14))
    {
LABEL_27:
      v22 = 1;
      goto LABEL_36;
    }
LABEL_30:
    if (v19)
      v23 = -1600273536;
    else
      v23 = 1692838528;
    if (wk->modeSq == 2)
      v22 = v23;
    else
      v22 = -1600273536;
LABEL_36:
    ((*monitor)[63])(monitor, (u32)v11, 1, (*monitor)[64]);
    if (v14)
    {
      cmpDrawSkillNameEx(v14, 316, v13, v24, 255);
      cmpDrawSkillOmoideNameExUnity(v14, v11, v22);
      NowBookCnt = CmpStatusGetNowBookCnt(wk->unit, v14);
      BookCnt = CmpStatusGetBookCnt(wk->unit, v14);
      ((*monitor)[69])(monitor, (u32)v11, NowBookCnt, BookCnt, (*monitor)[70]);
      if ((v19 & 1) == 0)
      {
        itfDrawMiscHelp(0xA09DC380, 1.0, 0, v14, 0);
      }
    }
    else
    {
      if (!cmpSetSkillNow())
        goto LABEL_15;
      ((*monitor)[63])(monitor, (u32)v11, 0, (*monitor)[64]);
    }
LABEL_15:
    ++v11;
    v13 += 23;
  }
  while (v11 != 8);
  (*(*monitor[8] + 376))(monitor[8], (u32)wk->wkMemSklCur->drwDefNum, (u32)wk->wkMemSklCur->selMax, (u32)wk->wkMemSklCur->topNo, *(u64 *)(*monitor[8] + 384));
  v32 = cmpGetSpriteHnd(0);
  v33 = 0;
  if (!cmpSetSkillNow())
  {
    if (wk->seqtype == 4 && wk->modeSq == 2)
    {
      v33 = 0;
    }
    else
    {
      type = wk->type;
      if (type == 268501248)
      {
        v33 = 2;
      }
      else if (type == 268566784)
      {
        v33 = 2;
      }
      else
      {
        v33 = 1;
      }
    }
  }
  v37 = *((u64 *)_get_Instance()[10].monitor + 4);
  TitleText = cmpGetTitleText(v33);
  (*(*(u64 *)v37 + 1368))(v37, TitleText, *(u64 *)(*(u64 *)v37 + 1376));
}

// 0x20af7e0
bool cmpCheckMitamaBarstSklSet(tagCMP_STATUS_WORK *_wk) {
  if (wk->type != 268566784)
    return 0;
  if (evtMoonGetAge() != 8)
    return 0;
  return nativeSkillStep != 3;
}

// 0x20af8b0
void cmpDrawPartsSpritSkill(tagCMP_STATUS_WORK *wk, s32 a_alphaRate) {
  u64 **monitor;
  s32 sklType_r;

  monitor = _get_Instance()[10].monitor;
  if ((wk->type & 0x8000000) == 0 && wk->modeSq != 2)
  {
    if (!cmpSetSkillNow())
      return;
  }
  sklType_r = wk->sklType_r;
  if (sklType_r == 1)
  {
    cmpDrawSpirtList(wk);
  }
  else if (!sklType_r)
  {
    cmpDrawSumnerRankList(wk);
  }
  (*(*monitor[8] + 376))(monitor[8], (u32)wk->wkMemSklCur->drwDefNum, (u32)wk->wkMemSklCur->selMax, (u32)wk->wkMemSklCur->topNo, *(u64 *)(*monitor[8] + 384));
}

// 0x20af9d0
void cmpDrawSumnerRankList(tagCMP_STATUS_WORK *wk) {
  u64 *monitor;
  s64 v4;
  char *TitleText;
  u32 i;
  char *LocalizeText;
  s32 topNo;
  void *rankTextList;
  s32 klass;
  s32 v12;
  sdatPlayerUnitWork_t *player;
  s32 v15;
  char *v17;
  char *v18;
  char *v19;
  s32 v21;
  char *v22;
  char *v23;
  Il2CppObject *v24;
  Il2CppObject *Item;
  char *v26;
  char *v27;

  monitor = _get_Instance()[10].monitor;
  (*(*monitor + 536))(monitor, 1, *(u64 *)(*monitor + 544));
  v4 = monitor[4];
  TitleText = cmpGetTitleText(4);
  (*(*(u64 *)v4 + 1368))(v4, TitleText, *(u64 *)(*(u64 *)v4 + 1376));
  for (i = 0; i != 8; ++i)
  {
    topNo = wk->wkMemSklCur->topNo;
    (*(*monitor + 504))(monitor, i, 1, *(u64 *)(*monitor + 512));
    rankTextList = wk->rankTextList;
    if ((signed s32)i >= rankTextList->_size)
    {
      v17 = rankText[0];
      LocalizeText = GetLocalizeText(v17, 1);
      (*(*monitor + 472))(monitor, i, LocalizeText, 2694693760LL, 0, 0, 0xFFFFFFFFLL, *(u64 *)(*monitor + 480));
      (*(*monitor + 504))(monitor, i, 2, *(u64 *)(*monitor + 512));
      (*(*monitor + 488))(monitor, i, 0, *(u64 *)(*monitor + 496));
      continue;
    }
    klass = _get_Item(rankTextList, i + wk->wkMemSklCur->topNo)[2].klass;
    v12 = i + topNo;
    player = GBWK->player;
    if (klass == player->syougou)
    {
      if (player->setSyougou)
        goto LABEL_14;
      goto LABEL_9001;
      if (GBWK->player->setSyougou)
      {
LABEL_14:
        if (i == wk->wkMemSklCur->drwNo)
        {
          (*(*monitor + 424))(monitor, i, 2, *(u64 *)(*monitor + 432));
          (*(*monitor + 488))(monitor, i, 0, *(u64 *)(*monitor + 496));
          v15 = _get_Item(wk->rankTextList, v12)[2].klass;
          cmpRankNewOff(v15);
        }
        else
        {
          Item = _get_Item(wk->rankTextList, v12);
          (*(*monitor + 488))(monitor, i, BYTE4(Item[2].klass) != 0, *(u64 *)(*monitor + 496));
        }
        v26 = _get_Item(wk->rankTextList, v12)[1].monitor;
        v27 = GetLocalizeText(v26, 1);
        (*(*monitor + 472))(monitor, i, v27, 1, 0, 0, 0xFFFFFFFFLL, *(u64 *)(*monitor + 480));
        continue;
      }
LABEL_9001:
    }
    if (i == wk->wkMemSklCur->drwNo)
    {
      (*(*monitor + 424))(monitor, i, 1, *(u64 *)(*monitor + 432));
      v18 = _get_Item(wk->rankTextList, v12)[1].monitor;
      v19 = GetLocalizeText(v18, 1);
      (*(*monitor + 472))(monitor, i, v19, 1692838528, 0, 0, 0xFFFFFFFFLL, *(u64 *)(*monitor + 480));
      (*(*monitor + 488))(monitor, i, 0, *(u64 *)(*monitor + 496));
      v21 = _get_Item(wk->rankTextList, v12)[2].klass;
      cmpRankNewOff(v21);
    }
    else
    {
      v22 = _get_Item(wk->rankTextList, v12)[1].monitor;
      v23 = GetLocalizeText(v22, 1);
      (*(*monitor + 472))(monitor, i, v23, 2694693760LL, 0, 0, 0xFFFFFFFFLL, *(u64 *)(*monitor + 480));
      v24 = _get_Item(wk->rankTextList, v12);
      (*(*monitor + 488))(monitor, i, BYTE4(v24[2].klass) != 0, *(u64 *)(*monitor + 496));
    }
  }
  (*(*monitor + 536))(monitor, 1, *(u64 *)(*monitor + 544));
  (*(*monitor + 440))(monitor, 0, *(u64 *)(*monitor + 448));
}

// 0x20aff20
void cmpDrawSpirtList(tagCMP_STATUS_WORK *wk) {
  u64 *monitor;
  s32 topNo;
  void *DrawSpiritSkill;
  void *v7;
  s64 v8;
  s32 *m_Items;
  u64 *v10;
  s64 v11;
  s64 v12;
  s32 v13;
  s64 drwNo;
  s64 v16;
  u32 v18;
  bool v21;
  void (__fastcall *v22)(u64 *, s64, s64);
  bool v25;
  s32 v26;
  s64 v27;
  char *TitleText;

  monitor = _get_Instance()[10].monitor;
  topNo = wk->wkMemSklCur->topNo;
  DrawSpiritSkill = cmpGetDrawSpiritSkill(topNo, 8, 1);
  v7 = _ToArray(DrawSpiritSkill);
  if (wk->modeSq != 1)
    goto LABEL_9;
  if (!cmpSetSkillNow())
    goto LABEL_9;
  goto LABEL_8;
  if (cmpSetSkillNow())
LABEL_8:
    (*(*monitor + 424))(monitor, 0xFFFFFFFFLL, 1, *(u64 *)(*monitor + 432));
LABEL_9:
  v8 = 0;
  m_Items = v7;
  do
  {
    v13 = m_Items[v8];
    drwNo = (u32)wk->wkMemSklCur->drwNo;
    if (v8 == drwNo && wk->modeSq == 2)
    {
      if (((v13 != 0) & datSpiritSkillHaveSkill(GBWK->player, v13)) != 0)
        v16 = 2;
      else
        v16 = 1;
      (*(*monitor + 424))(monitor, (u32)v8, v16, *(u64 *)(*monitor + 432));
    }
    if (datSpiritSkillHaveSkill(GBWK->player, v13))
    {
      v18 = 1;
    }
    else
    {
      v18 = 1692838528;
      if (wk->modeSq != 2 || v8 != drwNo)
        v18 = -1600273536;
    }
    if (!v13)
    {
      v21 = cmpSetSkillNow();
      v22 = *(*monitor + 504);
      if (v21)
        goto LABEL_45;
      goto LABEL_9000;
      if (v25)
      {
LABEL_45:
        v10 = monitor;
        v11 = (u32)v8;
        v12 = 0;
        goto LABEL_11;
      }
LABEL_9000:
      v10 = monitor;
      v11 = (u32)v8;
      v12 = 2;
LABEL_11:
      v22(v10, v11, v12);
      goto LABEL_12;
    }
    (*(*monitor + 504))(monitor, (u32)v8, 1, *(u64 *)(*monitor + 512));
    cmpDrawSkillOmoideNameExUnity(v13, v8, v18);
    if (v8 != drwNo)
      goto LABEL_12;
    if (wk->modeSq == 2)
    {
      ButtonLineHelpDispSet(1);
      itfDrawMiscHelp(0xA09DC380, 1.0, 0, v13, 0);
    }
LABEL_12:
    ++v8;
  }
  while (v8 != 8);
  v26 = 5;
  if (!cmpSetSkillNow())
  {
    if ((wk->type & 0x8000000) != 0)
      v26 = 5;
    else
      v26 = 6;
    v27 = monitor[4];
    goto LABEL_9001;
  }
  v27 = monitor[4];
LABEL_9001:
  TitleText = cmpGetTitleText(v26);
  (*(*(u64 *)v27 + 1368))(v27, TitleText, *(u64 *)(*(u64 *)v27 + 1376));
  (*(*monitor + 536))(monitor, 1, *(u64 *)(*monitor + 544));
  (*(*monitor + 440))(monitor, 0, *(u64 *)(*monitor + 448));
}

// 0x20af500
void *cmpGetDrawOmoideSkill(sdatUnitWork_t *unit, s32 _topNo, s32 _drwMax) {
  void *v7;
  s32 v8;
  s32 v9;
  s64 v10;
  s32 v11;
  s32 v13;
  s32 v15;
  s64 size;
  u64 *v17;
  void *items;
  SKLID *g_aOmoide_local;
  s32 v21;
  bool v22;
  s32 v23;
  u64 *v24;
  s64 v25;
  void *v26;

  v7 = Allocate(System_Collections_Generic_List_SKLID_);
  __ctor_47784064(v7, drwMax);
  v8 = 0;
  v9 = 0;
  v10 = 8;
  v11 = v7->_version + 1;
  v7->_size = 0;
  v7->_version = v11;
  while (1)
  {
    g_aOmoide_local = g_aOmoide;
    if (v10 - 8 >= SLODWORD(g_aOmoide_local->max_length))
      goto LABEL_23;
LABEL_6:
    v13 = *((u32 *)&g_aOmoide_local->obj.klass + v10);
    if (!!datOmoideSkillGetMaster(unit, v13))
    {
      if (v8 >= topNo)
      {
        v15 = *((u32 *)&g_aOmoide->obj.klass + v10);
        size = v7->_size;
        v17 = Method_System_Collections_Generic_List_SKLID__Add__;
        ++v7->_version;
        items = v7->_items;
        if ((u32)size >= LODWORD(items->max_length))
        {
          _AddWithResize(v7, v15, *(const MethodInfo_2D92A30 **)(*(u64 *)(v17[4] + 192) + 112));
          if (++v9 >= drwMax)
            goto LABEL_23;
        }
        else
        {
          v7->_size = size + 1;
          *((u32 *)items + size) = v15;
          if (++v9 >= drwMax)
            goto LABEL_23;
        }
      }
      ++v8;
    }
    ++v10;
  }
  g_aOmoide_local = g_aOmoide;
  if (v10 - 8 < SLODWORD(g_aOmoide_local->max_length))
    goto LABEL_6;
LABEL_23:
  v21 = v7->_size;
  v22 = __OFSUB__(drwMax, v21);
  v23 = drwMax - v21;
  if (!((v23 < 0) ^ v22 | (v23 == 0)))
  {
    v24 = Method_System_Collections_Generic_List_SKLID__Add__;
    do
    {
      while (1)
      {
        v25 = v7->_size;
        ++v7->_version;
        v26 = v7->_items;
        if ((u32)v25 < LODWORD(v26->max_length))
          break;
        _AddWithResize(v7, 0, *(const MethodInfo_2D92A30 **)(*(u64 *)(v24[4] + 192) + 112));
        v24 = Method_System_Collections_Generic_List_SKLID__Add__;
        if (!--v23)
          return v7;
      }
      v7->_size = v25 + 1;
      *((u32 *)v26 + v25) = 0;
      --v23;
    }
    while (v23);
  }
  return v7;
}

// 0x20b05e0
void *cmpGetDrawSpiritSkill(s32 _topNo, s32 _drwMax, bool _sort) {
  void *v6;
  s32 v7;
  void *v10;
  s32 v11;
  Il2CppObject *v13;
  void *Instance;
  void *v15;
  void *v16;
  void *v17;
  void *IndexList;
  __int128 v19;
  s64 size;
  s32 current;
  u64 *v22;
  void *items;
  s32 v24;
  s32 v25;
  s32 v26;
  sdatPlayerUnitWork_t *player;
  s32 Item;
  s32 v30;
  s64 v31;
  u64 *v32;
  void *v33;
  s32 v34;
  s32 v35;
  u64 *v36;
  s64 v37;
  void *v38;
  System_Collections_Generic_List_Enumerator_T__o v41;
  System_Collections_Generic_List_Enumerator_int__o v42;

  memset(&v42, 0, sizeof(v42));
  v6 = Allocate(System_Collections_Generic_List_SKLID_);
  __ctor(v6);
  v7 = v6->_version + 1;
  v6->_size = 0;
  v6->_version = v7;
  v10 = Allocate(System_Collections_Generic_List_SKLID_);
  __ctor_47784336(v10, spiritList);
  if (sort)
  {
    v11 = v10->_version + 1;
    v10->_size = 0;
    v10->_version = v11;
    v13 = cmpSortUseSpritList();
    Instance = get_Instance(0);
    SortSetting(Instance, 7, 0);
    v15 = get_Instance(0);
    ListSet_object_(v15, v13);
    v16 = get_Instance(0);
    ListSort(v16, 0);
    v17 = get_Instance(0);
    IndexList = GetIndexList(v17, 0);
    _GetEnumerator(&v41, IndexList);
    v19 = *(_OWORD *)&v41._list;
    v41._list = 0;
    *(u64 *)&v41._index = &v42;
    *(u64 *)&v42._current = v41._current;
    *(_OWORD *)&v42._list = v19;
    while (_MoveNext(&v42))
    {
      size = v10->_size;
      current = v42._current;
      v22 = Method_System_Collections_Generic_List_SKLID__Add__;
      ++v10->_version;
      items = v10->_items;
      if ((u32)size < LODWORD(items->max_length))
      {
        v10->_size = size + 1;
        *((u32 *)items + size) = current;
      }
      else
      {
        _AddWithResize(v10, current, *(const MethodInfo_2D92A30 **)(*(u64 *)(v22[4] + 192) + 112));
      }
    }
    _Dispose(&v42);
  }
  if (v10->_size >= 1)
  {
    v24 = 0;
    v25 = 0;
    v26 = 0;
    do
    {
      player = GBWK->player;
      Item = _get_Item(v10, v24);
      if (datSpiritSkillGetMaster(player, Item))
      {
        if (v26 >= topNo)
        {
          v30 = _get_Item(v10, v24);
          v31 = v6->_size;
          v32 = Method_System_Collections_Generic_List_SKLID__Add__;
          ++v6->_version;
          v33 = v6->_items;
          if ((u32)v31 >= LODWORD(v33->max_length))
          {
            _AddWithResize(v6, v30, *(const MethodInfo_2D92A30 **)(*(u64 *)(v32[4] + 192) + 112));
            if (++v25 >= drwMax)
              break;
          }
          else
          {
            v6->_size = v31 + 1;
            *((u32 *)v33 + v31) = v30;
            if (++v25 >= drwMax)
              break;
          }
        }
        ++v26;
      }
      ++v24;
    }
    while (v24 < v10->_size);
  }
  v34 = v6->_size;
  v35 = drwMax - v34;
  if (drwMax > v34)
  {
    v36 = Method_System_Collections_Generic_List_SKLID__Add__;
    do
    {
      while (1)
      {
        v37 = v6->_size;
        ++v6->_version;
        v38 = v6->_items;
        if ((u32)v37 < LODWORD(v38->max_length))
          break;
        _AddWithResize(v6, 0, *(const MethodInfo_2D92A30 **)(*(u64 *)(v36[4] + 192) + 112));
        v36 = Method_System_Collections_Generic_List_SKLID__Add__;
        if (!--v35)
          return v6;
      }
      v6->_size = v37 + 1;
      *((u32 *)v38 + v37) = 0;
      --v35;
    }
    while (v35);
  }
  return v6;
}

// 0x20b0aa0
void *cmpGetDrawRaidouSkill(s32 _topNo, s32 _drwMax, bool _sort) {
  void *v6;
  s32 v7;
  void *v10;
  s32 v11;
  Il2CppObject *v13;
  void *Instance;
  void *v15;
  void *v16;
  void *v17;
  void *IndexList;
  __int128 v19;
  s64 size;
  s32 current;
  u64 *v22;
  void *items;
  s32 v24;
  s32 v25;
  s32 v26;
  sdatPlayerUnitWork_t *player;
  s32 Item;
  s32 v30;
  s64 v31;
  u64 *v32;
  void *v33;
  s32 v34;
  s32 v35;
  u64 *v36;
  s64 v37;
  void *v38;
  System_Collections_Generic_List_Enumerator_T__o v41;
  System_Collections_Generic_List_Enumerator_int__o v42;

  memset(&v42, 0, sizeof(v42));
  v6 = Allocate(System_Collections_Generic_List_SKLID_);
  __ctor(v6);
  v7 = v6->_version + 1;
  v6->_size = 0;
  v6->_version = v7;
  v10 = Allocate(System_Collections_Generic_List_SKLID_);
  __ctor_47784336(v10, raidouSkillList);
  if (sort)
  {
    v11 = v10->_version + 1;
    v10->_size = 0;
    v10->_version = v11;
    v13 = cmpSortUseRaidouList();
    Instance = get_Instance(0);
    SortSetting(Instance, 6, 0);
    v15 = get_Instance(0);
    ListSet_object_(v15, v13);
    v16 = get_Instance(0);
    ListSort(v16, 0);
    v17 = get_Instance(0);
    IndexList = GetIndexList(v17, 0);
    _GetEnumerator(&v41, IndexList);
    v19 = *(_OWORD *)&v41._list;
    v41._list = 0;
    *(u64 *)&v41._index = &v42;
    *(u64 *)&v42._current = v41._current;
    *(_OWORD *)&v42._list = v19;
    while (_MoveNext(&v42))
    {
      size = v10->_size;
      current = v42._current;
      v22 = Method_System_Collections_Generic_List_SKLID__Add__;
      ++v10->_version;
      items = v10->_items;
      if ((u32)size < LODWORD(items->max_length))
      {
        v10->_size = size + 1;
        *((u32 *)items + size) = current;
      }
      else
      {
        _AddWithResize(v10, current, *(const MethodInfo_2D92A30 **)(*(u64 *)(v22[4] + 192) + 112));
      }
    }
    _Dispose(&v42);
  }
  if (v10->_size >= 1)
  {
    v24 = 0;
    v25 = 0;
    v26 = 0;
    do
    {
      player = GBWK->player;
      Item = _get_Item(v10, v24);
      if (datRaidouSkillGetMaster(player, Item))
      {
        if (v26 >= topNo)
        {
          v30 = _get_Item(v10, v24);
          v31 = v6->_size;
          v32 = Method_System_Collections_Generic_List_SKLID__Add__;
          ++v6->_version;
          v33 = v6->_items;
          if ((u32)v31 >= LODWORD(v33->max_length))
          {
            _AddWithResize(v6, v30, *(const MethodInfo_2D92A30 **)(*(u64 *)(v32[4] + 192) + 112));
            if (++v25 >= drwMax)
              break;
          }
          else
          {
            v6->_size = v31 + 1;
            *((u32 *)v33 + v31) = v30;
            if (++v25 >= drwMax)
              break;
          }
        }
        ++v26;
      }
      ++v24;
    }
    while (v24 < v10->_size);
  }
  v34 = v6->_size;
  v35 = drwMax - v34;
  if (drwMax > v34)
  {
    v36 = Method_System_Collections_Generic_List_SKLID__Add__;
    do
    {
      while (1)
      {
        v37 = v6->_size;
        ++v6->_version;
        v38 = v6->_items;
        if ((u32)v37 < LODWORD(v38->max_length))
          break;
        _AddWithResize(v6, 0, *(const MethodInfo_2D92A30 **)(*(u64 *)(v36[4] + 192) + 112));
        v36 = Method_System_Collections_Generic_List_SKLID__Add__;
        if (!--v35)
          return v6;
      }
      v6->_size = v37 + 1;
      *((u32 *)v38 + v37) = 0;
      --v35;
    }
    while (v35);
  }
  return v6;
}

// 0x20b0f60
void cmpRaidouSklSpiritDraw(tagCMP_STATUS_WORK *wk) {
  Il2CppObject *Instance;
  Il2CppClass *klass;
  u64 i;
  u32 v8;
  s32 v9;
  s32 modeSq;
  _BOOL4 noSklHelp;
  s64 v21;
  void (__fastcall **image)(Il2CppClass *, s64, s64, s64, s64, u64);
  Il2CppClass *v24;
  s64 v25;
  s64 baseSklCsr;
  s64 sklCsr;
  s64 type;

  Instance = _get_Instance();
  RaidouAffterWeapon(Instance, 0, 0);
  klass = _get_Instance()[8].klass;
  for (i = 0; i != 10; ++i)
  {
    while (i >= 8)
    {
      (*(klass->_1.image + 53))(klass, (u32)i++, 0, *((u64 *)klass->_1.image + 54));
      if (i == 10)
        goto LABEL_53;
    }
    (*(klass->_1.image + 53))(klass, (u32)i, (s64)i < GBWK->player->spiritCnt, *((u64 *)klass->_1.image + 54));
    v8 = -1600273536;
    if (GBWK->player->spiritSkill[i])
      v9 = GBWK->player->spiritSkill[i];
    else
      v9 = -1;
    if (i != wk->sklCsr || (modeSq = wk->modeSq, v8 = -1600273536, !modeSq))
    {
LABEL_27:
      goto LABEL_28;
    }
    if (modeSq == 2)
    {
      if (cmpSetSkillNow())
        v8 = 1;
      else
        v8 = -1600273536;
      goto LABEL_28;
    }
    noSklHelp = wk->noSklHelp;
    v8 = 1692838528;
    wk->selSkl = v9;
    if (noSklHelp)
      goto LABEL_27;
    if (v9 != -1)
    {
      itfDrawMiscHelp(0xA09DC380, 1.0, 0, v9, 0);
      v8 = 1692838528;
      goto LABEL_28;
    }
    if (cmpSetSkillNow())
    {
      cmpDrawNoneSklHelp(1);
      v8 = 1692838528;
      goto LABEL_28;
    }
    ButtonLineHelpDispSet(0);
    v8 = 1692838528;
    if (!cmpChgSkillNow())
      goto LABEL_23;
    goto LABEL_29;
LABEL_28:
    if (!cmpChgSkillNow())
    {
LABEL_23:
      goto LABEL_24;
    }
LABEL_29:
    if (i == wk->baseSklIndex)
      v8 = 1;
LABEL_24:
    cmpDrawSkillNameExUnity(v9, i, v8, 0, 1, 0);
  }
LABEL_53:
  if (cmpSetSkillNow())
    goto LABEL_55;
  if (!!cmpChgSkillNow())
  {
    image = klass->_1.image;
    v24 = klass;
    v25 = 2;
    baseSklCsr = (u32)wk->baseSklCsr;
    sklCsr = (u32)wk->sklCsr;
    goto LABEL_70;
  }
  type = wk->type;
  if ((type & 0x11B0000) != 0 && wk->modeSq == 1)
  {
    if (type != 0x8000000)
    {
      image = klass->_1.image;
      sklCsr = 0xFFFFFFFFLL;
      v24 = klass;
      baseSklCsr = (u32)wk->sklCsr;
      v25 = 1;
      goto LABEL_70;
    }
LABEL_69:
    image = klass->_1.image;
    sklCsr = 0xFFFFFFFFLL;
    v24 = klass;
    baseSklCsr = (u32)wk->sklCsr;
    v25 = 0;
LABEL_70:
    image[63](v24, baseSklCsr, v25, sklCsr, 1, image[64]);
  }
  else
  {
    if (type == 0x8000000)
      goto LABEL_69;
    (*(klass->_1.image + 65))(klass, *((u64 *)klass->_1.image + 66));
  }
  goto LABEL_9002;
LABEL_55:
  if (wk->modeSq == 1)
    v21 = 1;
  else
    v21 = 2;
  (*(klass->_1.image + 63))(klass, (u32)wk->sklCsr, v21, 0xFFFFFFFFLL, 1, *((u64 *)klass->_1.image + 64));
LABEL_9002:
  (*(klass->_1.image + 57))(klass, 0, 0, *((u64 *)klass->_1.image + 58));
  (*(klass->_1.image + 57))(klass, 1, 0, *((u64 *)klass->_1.image + 58));
  (*(klass->_1.image + 57))(klass, 2, 0, *((u64 *)klass->_1.image + 58));
  (*(klass->_1.image + 57))(klass, 3, 0, *((u64 *)klass->_1.image + 58));
  (*(klass->_1.image + 57))(klass, 4, 0, *((u64 *)klass->_1.image + 58));
  (*(klass->_1.image + 57))(klass, 5, 0, *((u64 *)klass->_1.image + 58));
  (*(klass->_1.image + 57))(klass, 6, 0, *((u64 *)klass->_1.image + 58));
  (*(klass->_1.image + 57))(klass, 7, 0, *((u64 *)klass->_1.image + 58));
}

// 0x20b14b0
void cmpDrawRaidouSkill(tagCMP_STATUS_WORK *wk) {
  _BOOL4 noStatusDraw;
  void *v4;
  bool activeSelf;
  Il2CppObject *Instance;
  Il2CppObject *v7;
  s32 sklType_r;
  Il2CppObject *v9;
  Il2CppObject *v12;

  noStatusDraw = wk->noStatusDraw;
  v4 = *(void *)(*(u64 *)&_get_Instance()[8].klass->_1.byval_arg.bits + 16);
  activeSelf = get_activeSelf(v4, 0);
  if (noStatusDraw)
  {
    if (!activeSelf)
      goto LABEL_6;
    goto LABEL_5;
  }
  if (!activeSelf)
LABEL_5:
    SetActive(v4, !noStatusDraw, 0);
LABEL_6:
  Instance = _get_Instance();
  RaidouTopDraw(Instance, wk->sklType_r, 0);
  if (wk->modeSq == 2)
    goto LABEL_10;
  if (cmpSetSkillNow())
    goto LABEL_10;
  goto LABEL_9;
  if (!cmpSetSkillNow())
  {
LABEL_9:
    v7 = _get_Instance();
    (*(*(u64 *)v7[10].monitor + 536))(v7[10].monitor, 0, *(u64 *)(*(u64 *)v7[10].monitor + 544));
  }
LABEL_10:
  sklType_r = wk->sklType_r;
  if (sklType_r == 1)
  {
    v12 = _get_Instance();
    SkillSelectDraw(*(CmpSelectSkillSet *)&v12[8].klass->_1.byval_arg.bits, 3, 0);
    cmpRaidouSklSpiritDraw(wk);
  }
  else if (!sklType_r)
  {
    v9 = _get_Instance();
    SkillSelectDraw(*(CmpSelectSkillSet *)&v9[8].klass->_1.byval_arg.bits, 4, 0);
    cmpDrawEquip(wk, 0, 20, 291, 0, 0);
    return;
  }
}

// 0x20b16d0
void cmpDrawPartsLRHelpDraw(tagCMP_STATUS_WORK *wk, CmpBasePartsSet *set) {
  s32 devilid;
  _BOOL4 v7;
  _BOOL4 v9;
  s32 modeSq;
  _BOOL4 v11;
  s64 v12;
  _BOOL4 v14;
  s64 type;

  devilid = (u16)wk->unit->devilid;
  v7 = cmpChgSkillNow();
  v9 = cmpSetSkillNow();
  modeSq = wk->modeSq;
  v11 = v9;
  if (devilid)
  {
    v12 = wk->type & 0x11B0000;
    v14 = GohGohNativeSq() != 1 && v12 != 0;
    goto LABEL_24;
  }
  type = wk->type;
  v14 = (type & 0x1A040001) == 0 && type != 0 && (wk->type & 0x8000101) == 0;
  if (modeSq == 1)
    v14 = 0;
LABEL_24:
  if (modeSq == 2)
    v14 = 0;
  (set->klass->vtable._18_LRHelpDraw.methodPtr)(set, v14 && !v11 && !v7, set->klass->vtable._18_LRHelpDraw.method);
}

// 0x20b1840
void cmpDrawPartsSkill(tagCMP_STATUS_WORK *wk, s32 a_alphaRate) {
  s32 lightUpCnt;
  s32 v6;
  bool v7;
  s32 v8;
  s32 sklType;

  _get_Instance();
  lightUpCnt = wk->lightUpCnt;
  if (wk->lightUpDir)
  {
    v6 = lightUpCnt + 6;
    wk->lightUpCnt = v6;
    if (v6 < 255)
      goto LABEL_9;
    v7 = 0;
  }
  else
  {
    v8 = lightUpCnt - 6;
    wk->lightUpCnt = v8;
    if (v8 > 128)
      goto LABEL_9;
    wk->lightUpCnt = 128;
    v7 = 1;
  }
  wk->lightUpDir = v7;
LABEL_9:
  sklType = wk->sklType;
  switch (sklType)
  {
    case 2:
      cmpSklDrawPartsSousa(wk);
      break;
    case 1:
      cmpSklDrawPartsOmoide(wk);
      break;
    case 0:
      cmpSklDrawPartsNormal(wk);
      break;
  }
}

// 0x20b34e0
bool cmpSklPartsNormalHelpOffChk(SKLID _sklID, tagCMP_STATUS_WORK *_wk) {
  _BOOL4 v7;

  if (nativeSkillStep)
  {
    v7 = nativeSkillStep == 3;
    if (sklID)
      return 0;
    return v7 && !wk->noSklHelp && wk->modeSq != 1;
  }
  v7 = 1;
  if (sklID)
    return 0;
  return v7 && !wk->noSklHelp && wk->modeSq != 1;
}

// 0x20b19c0
void cmpSklDrawPartsNormal(tagCMP_STATUS_WORK *wk) {
  CmpSelectSkillSet *klass;
  sdatUnitWork_t *unit;
  GohCombUnity **v5;
  s64 v6;
  s32 v7;
  s32 v8;
  sdatUnitWork_t *v9;
  u32 v10;
  void **v11;
  s32 v12;
  u32 NowBookCnt;
  u32 BookCnt;
  s32 v16;
  s32 v17;
  s32 v18;
  sdatUnitWork_t *v19;
  s32 v23;
  s32 v24;
  u32 v25;
  bool v26;
  bool v27;
  s32 modeSq;
  GohCombUnity *v30;
  s32 nativeSkillStep_local;
  _BOOL4 v32;
  s64 v33;
  s32 v34;
  s32 v35;
  s32 v36;
  s32 v37;
  s32 v39;
  CmpSelectSkillSet *v41;
  void *buttonR;
  _BOOL4 v43;
  s64 type;
  GohCombUnity *v45;
  s32 v46;
  s32 v47;
  s32 v48;
  s32 v49;
  GohCombUnity *v50;
  void *setNativeSkillList_local;
  s32 v53;
  GohCombUnity *v54;
  s32 Item;
  GohCombUnity *v57;
  u16 v58;
  s32 newSklCnt;
  s32 v60;
  s32 v61;
  u32 v62;
  s32 v63;
  s32 v64;
  Il2CppObject *Instance;
  Il2CppObject *v66;
  Il2CppObject *v67;
  Il2CppObject *v68;
  Il2CppObject *v69;
  Il2CppObject *v70;
  Il2CppObject *v71;
  Il2CppObject *v72;
  s32 v73;
  s32 v74;
  s32 v75;
  s32 v76;
  Il2CppObject *v77;
  s32 rsvCsr;
  u32 sklCsr;
  void *monitor;
  CmpSelectSkillSet *v83;
  s32 v84;
  char v85;

  klass = _get_Instance()[10].klass;
  unit = wk->unit;
  v5 = &GohCombUnity;
  datCheckHaveSkillCnt(unit);
  v6 = 0;
  v7 = 0;
  v8 = 0;
  do
  {
    v9 = wk->unit;
    v10 = v6 - v8;
    v11 = v5;
    v12 = v9->haveskill[v6];
    NowBookCnt = CmpStatusGetNowBookCnt(v9, v12);
    BookCnt = CmpStatusGetBookCnt(wk->unit, v12);
    (klass[9].obj)(klass, (u32)(v6 - v8), NowBookCnt, BookCnt, klass[9].arrow);
    if (!cmpChgSkillNow())
      goto LABEL_15;
    if (v6 != wk->baseSklIndex)
    {
LABEL_15:
      if (wk->rsvCsr != -1)
      {
        v17 = 0;
        v16 = -1600273536;
        goto LABEL_17;
      }
      v18 = -1600273536;
      if (v10 == wk->sklCsr)
      {
        v17 = v12;
        v16 = 1692838528;
        if (wk->modeSq == 1)
          goto LABEL_17;
      }
      goto LABEL_18;
    }
    v16 = 1;
    if (wk->rsvCsr != -1)
    {
      v17 = 0;
LABEL_17:
      v18 = v16;
      wk->selSkl = v17;
      goto LABEL_18;
    }
    v18 = 1;
LABEL_18:
    if (!v12)
    {
      ++v8;
      v5 = v11;
      goto LABEL_61;
    }
    if (wk->type == 268566784)
    {
      if (evtMoonGetAge() == 8)
      {
        v19 = wk->unit;
        if (!v19->newSklCnt)
          goto LABEL_33;
        goto LABEL_30;
      }
    }
    ++v7;
    v19 = wk->unit;
    if (!v19->newSklCnt)
      goto LABEL_33;
LABEL_30:
    if (IndexOf_Int32Enum_(v19->newSklDrwOff, v12) == -1)
    {
LABEL_33:
      if (*((u32 *)*v11 + 56))
      {
        if (GohGohNativeSq() == 1)
        {
LABEL_35:
          v23 = v12;
          v24 = v6 - v8;
          v25 = v18;
          v26 = 1;
          goto LABEL_48;
        }
      }
      else
      {
        if (GohGohNativeSq() == 1)
          goto LABEL_35;
      }
      if (wk->lrnEffCnt && v10 == wk->newSkillCnt && wk->ofcSkl)
      {
        v23 = v12;
        v24 = v6 - v8;
        v25 = 1692838528;
        v26 = 0;
        v27 = 1;
LABEL_49:
        cmpDrawSkillNameExUnity(v23, v24, v25, v26, 0, v27);
        v5 = v11;
        goto LABEL_51;
      }
      v23 = v12;
      v24 = v6 - v8;
      v25 = v18;
      v26 = 0;
LABEL_48:
      v27 = 0;
      goto LABEL_49;
    }
    (klass[6].arrow)(klass, v10, 0, klass[6].skillBattle);
    v5 = v11;
LABEL_51:
    cmpCombIconDraw(wk, v10, v12);
    modeSq = wk->modeSq;
    if ((modeSq == 1 || (wk->type & 0x8000000) != 0) && wk->rsvCsr == -1 && v10 == wk->sklCsr && modeSq == 1 && !wk->noSklHelp)
    {
      itfDrawMiscHelp(0xA09DC380, 1.0, 0, v12, 0);
      goto LABEL_61;
    }
LABEL_61:
    if (v10 != wk->sklCsr)
      goto LABEL_7;
    v30 = *v5;
    nativeSkillStep_local = nativeSkillStep;
    if (!nativeSkillStep_local)
    {
      v32 = 1;
      if (v12)
        goto LABEL_7;
LABEL_74:
      if (v32 && !wk->noSklHelp && wk->modeSq != 1)
      {
        ButtonLineHelpDispSet(0);
      }
      goto LABEL_7;
    }
    nativeSkillStep_local = (*v5)->static_fields->nativeSkillStep;
    v32 = nativeSkillStep_local == 3;
    if (!v12)
      goto LABEL_74;
LABEL_7:
    ++v6;
  }
  while (v6 != 8);
  v33 = 0;
  v34 = 0;
  v35 = 0;
  do
  {
    v36 = wk->unit->aRsvSkl[v33];
    if (!v36)
    {
      ++v35;
      goto LABEL_85;
    }
    v37 = v33 - v35;
    if (GohGohNativeSq() == 1)
    {
      cmpDrawRsvSkillNameExUnity(v36, v37, 0x4D4B4B4Du, 1, 0);
      v39 = wk->modeSq;
      ++v34;
      if (v39 == 1)
        goto LABEL_106;
      goto LABEL_105;
    }
    if (!wk->lrnEffCnt || v37 || wk->ofcSkl)
    {
      cmpDrawRsvSkillNameExUnity(v36, v37, 0x4D4B4B4Du, 0, 0);
      v39 = wk->modeSq;
      ++v34;
      if (v39 == 1)
        goto LABEL_106;
    }
    else
    {
      cmpDrawRsvSkillNameExUnity(v36, 0, 0x64E6AA80u, 0, 1);
      v37 = 0;
      v39 = wk->modeSq;
      ++v34;
      if (v39 == 1)
        goto LABEL_106;
    }
LABEL_105:
    if ((wk->type & 0x8000000) == 0)
      goto LABEL_84;
LABEL_106:
    if (wk->rsvCsr != v37 || v39 != 1 || wk->noSklHelp)
    {
LABEL_84:
      v5 = v11;
      goto LABEL_85;
    }
    v5 = v11;
    itfDrawMiscHelp(0xA09DC380, 1.0, 0, v36, 0);
LABEL_85:
    ++v33;
  }
  while (v33 != 3);
  buttonR = klass[5].buttonR;
  v41 = klass[6].klass;
  if (v34 <= 0)
  {
    (buttonR)(klass, 8, 0, v41);
    goto LABEL_121;
  }
  (buttonR)(klass, 8, 1, v41);
  if (v34 == 1)
  {
LABEL_121:
    (klass[5].buttonR)(klass, 9, 0, klass[6].klass);
    goto LABEL_122;
  }
  (klass[5].buttonR)(klass, 9, 1, klass[6].klass);
  if ((u32)v34 < 3)
  {
LABEL_122:
    (klass[5].buttonR)(klass, 10, 0, klass[6].klass);
    v43 = v34 != 0;
    goto LABEL_123;
  }
  v43 = 1;
  (klass[5].buttonR)(klass, 10, 1, klass[6].klass);
LABEL_123:
  (klass[9].klass)(klass, v43, klass[9].monitor);
  type = wk->type;
  if (type == 268566784 || type == 268501248)
  {
    v45 = *v5;
    if (resultCheck)
      goto LABEL_127;
    v47 = GohGohNativeSq();
    v85 = 0;
    v48 = 0;
    v49 = v7;
    while (2)
    {
      v50 = *v5;
      v50 = *v5;
      setNativeSkillList_local = setNativeSkillList;
      if (v48 >= setNativeSkillList_local->_size)
      {
        v7 = v49;
        v46 = v85 & 1;
        goto LABEL_165;
      }
      if (wk->unit->nativeSkillSetCnt > v48)
      {
        setNativeSkillList_local = (*v5)->static_fields->setNativeSkillList;
        v53 = v7 + v48;
        if (_get_Item(setNativeSkillList_local, v48))
        {
          v54 = *v5;
          v54 = *v5;
          Item = _get_Item(setNativeSkillList, v48);
          cmpDrawSkillNameExUnity(Item, v53, 1u, v47 == 1, 0, 0);
          v5 = v11;
        }
        else if (v53 <= 7)
        {
          cmpDrawSkillNameExUnity(-1, v53, 0x64E6AA80u, v47 == 1, 0, 0);
        }
        if (wk->rsvCsr == -1 && v53 == wk->sklCsr && wk->modeSq == 1 && !wk->noSklHelp)
        {
          v57 = *v5;
          v57 = *v5;
          v58 = _get_Item(setNativeSkillList, v48);
          itfDrawMiscHelp(0xA09DC380, 1.0, 0, v58, 0);
          v85 = 1;
        }
        ++v49;
      }
      ++v48;
      continue;
    }
  }
LABEL_127:
  v46 = 0;
LABEL_165:
  newSklCnt = wk->unit->newSklCnt;
  v60 = v34 - newSklCnt;
  v61 = newSklCnt & (SBYTE3(wk->type) >> 7);
  v62 = v60 & ~(v60 >> 31);
  v63 = 8 - v62;
  if (v62 <= 7)
  {
    v64 = v63 <= 1 ? 1 : 8 - v62;
    Instance = _get_Instance();
    (*(Instance[10].klass->_1.image + 53))(Instance[10].klass, 0, 1, *((u64 *)Instance[10].klass->_1.image + 54));
    if (v62 <= 6)
    {
      v66 = _get_Instance();
      (*(v66[10].klass->_1.image + 53))(v66[10].klass, 1, 1, *((u64 *)v66[10].klass->_1.image + 54));
      if (v64 != 2)
      {
        v67 = _get_Instance();
        (*(v67[10].klass->_1.image + 53))(v67[10].klass, 2, 1, *((u64 *)v67[10].klass->_1.image + 54));
        if (v64 != 3)
        {
          v68 = _get_Instance();
          (*(v68[10].klass->_1.image + 53))(v68[10].klass, 3, 1, *((u64 *)v68[10].klass->_1.image + 54));
          if (v64 != 4)
          {
            v69 = _get_Instance();
            (*(v69[10].klass->_1.image + 53))(v69[10].klass, 4, 1, *((u64 *)v69[10].klass->_1.image + 54));
            if (v64 != 5)
            {
              v70 = _get_Instance();
              (*(v70[10].klass->_1.image + 53))(v70[10].klass, 5, 1, *((u64 *)v70[10].klass->_1.image + 54));
              if (v64 != 6)
              {
                v71 = _get_Instance();
                (*(v71[10].klass->_1.image + 53))(v71[10].klass, 6, 1, *((u64 *)v71[10].klass->_1.image + 54));
                if (v64 != 7)
                {
                  v72 = _get_Instance();
                  (*(v72[10].klass->_1.image + 53))(v72[10].klass, 7, 1, *((u64 *)v72[10].klass->_1.image + 54));
                }
              }
            }
          }
        }
      }
    }
  }
  v73 = v7 + v61;
  if (v60 >= 1)
  {
    v74 = -v62;
    if (v63 <= 7)
      v75 = 7;
    else
      v75 = 8 - v62;
    v76 = v75 - 7;
    do
    {
      v77 = _get_Instance();
      (*(v77[10].klass->_1.image + 53))(v77[10].klass, (u32)(v74 + 8), 0, *((u64 *)v77[10].klass->_1.image + 54));
      ++v74;
    }
    while (v76 != v74);
  }
  SkillSelectDraw(klass[5], 0, 0);
  if (wk->modeSq != 1)
  {
    (klass[7].obj)(klass, klass[7].arrow);
    if (wk->modeSq != 1)
      goto LABEL_189;
  }
  rsvCsr = wk->rsvCsr;
  if (rsvCsr == -1)
  {
    sklCsr = wk->sklCsr;
LABEL_187:
    if (cmpChgSkillNow())
      goto LABEL_188;
    v83 = klass[7].klass;
    monitor = klass[7].monitor;
    if (v46)
    {
      (v83)(klass, sklCsr, 1, 0xFFFFFFFFLL, 1, monitor);
      wk->skillMax = v73;
      if (v73 >= v63)
        return;
    }
    else
    {
      (v83)(klass, sklCsr, 0, 0xFFFFFFFFLL, 1, monitor);
      wk->skillMax = v73;
      if (v73 >= v63)
        return;
    }
    goto LABEL_199;
  }
  sklCsr = rsvCsr + 8;
  goto LABEL_187;
LABEL_188:
  (klass[7].klass)(klass, (u32)wk->baseSklCsr, 2, sklCsr, 1, klass[7].monitor);
LABEL_189:
  wk->skillMax = v73;
  if (v73 < v63)
  {
    do
    {
LABEL_199:
      if (!*((u32 *)*v11 + 56))
      v84 = GohGohNativeSq();
      (klass[6].arrow)(klass, (u32)v73++, 2 * (u32)(v84 == 1), klass[6].skillBattle);
    }
    while (v63 != v73);
  }
}

// 0x20b35d0
void cmpCombIconDraw(tagCMP_STATUS_WORK *wk, s32 i, SKLID skillID) {
  Il2CppClass *klass;
  bool v8;

  klass = _get_Instance()[10].klass;
  if (wk->unit->combSkill[0] != skillID)
  {
    UseSkillIconDraw(klass, i, 1, 0, 0);
    v8 = 0;
    if (wk->unit->combSkill[1] != skillID)
    {
LABEL_8:
      UseSkillIconDraw(klass, i, 2, v8, 0);
      return;
    }
LABEL_7:
    v8 = 1;
    goto LABEL_8;
  }
  UseSkillIconDraw(klass, i, 1, 1, 0);
  if (wk->unit->combSkill[1] == skillID)
    goto LABEL_7;
}

// 0x20b28d0
void cmpSklDrawPartsOmoide(tagCMP_STATUS_WORK *wk) {
  CmpSelectSkillSet *klass;
  s32 v5;
  s32 iOmoideSkillCnt;
  sdatUnitWork_t *unit;
  s64 i;
  s32 v10;
  s32 v11;
  s32 modeSq;
  u32 v14;
  u32 NowBookCnt;
  u32 BookCnt;
  s64 type;
  s64 sklCsr;
  bool v24;
  bool v26;
  s64 v28;

  klass = _get_Instance()[10].klass;
  (klass[9].klass)(klass, 0, klass[9].monitor);
  v5 = 0;
  while (1)
  {
    cmpCombIconDraw(wk, v5, -1);
    iOmoideSkillCnt = wk->unit->iOmoideSkillCnt;
    if (v5 >= iOmoideSkillCnt)
      break;
    (klass[6].arrow)(klass, v5, 0, klass[6].skillBattle);
LABEL_5:
    (klass[5].buttonR)(klass, v5, v5 < iOmoideSkillCnt, klass[6].klass);
LABEL_6:
    if (++v5 == 13)
      goto LABEL_13;
  }
  if (v5 != 12)
  {
    if (wk->omoideEx)
      goto LABEL_6;
    goto LABEL_5;
  }
LABEL_13:
  unit = wk->unit;
  if (unit->iOmoideSkillCnt >= 1)
  {
    for (i = 0; i < unit->iOmoideSkillCnt; ++i)
    {
      v10 = unit->aOmoideSkill[i];
      if (v10)
        v11 = v10;
      else
        v11 = -1;
      if (i != wk->sklCsr || (modeSq = wk->modeSq) == 0)
      {
        if (!cmpChgSkillNow())
        {
LABEL_37:
          v14 = -1600273536;
          if (!wk->omoideEx)
            goto LABEL_53;
          v14 = -1600273536;
          if (i != wk->suteCsr)
            goto LABEL_53;
          (klass[7].klass)(klass, (u32)i, 1, 0xFFFFFFFFLL, 1, klass[7].monitor);
LABEL_40:
          v14 = 1692838528;
          goto LABEL_55;
        }
        if (i == wk->baseSklIndex)
        {
          v14 = 1;
          goto LABEL_55;
        }
        goto LABEL_37;
      }
      if (modeSq == 2)
      {
        if (cmpSetSkillNow())
          v14 = 1;
        else
          v14 = -1600273536;
        goto LABEL_55;
      }
      v14 = -1600273536;
      if (v11 == -1 && autoCsr)
        goto LABEL_53;
      if (cmpChgSkillNow())
      {
        if (i == wk->baseSklIndex)
        {
          v14 = 1;
LABEL_53:
          goto LABEL_55;
        }
      }
      if (wk->seqtype != 2)
      {
        wk->selSkl = v11;
        goto LABEL_40;
      }
      v14 = -2139062144;
LABEL_55:
      cmpDrawSkillNameExUnity(v11, i, v14, 0, 0, 0);
      NowBookCnt = CmpStatusGetNowBookCnt(wk->unit, v11);
      BookCnt = CmpStatusGetBookCnt(wk->unit, v11);
      (klass[9].obj)(klass, (u32)i, NowBookCnt, BookCnt, klass[9].arrow);
      if (wk->omoideEx)
        goto LABEL_16;
      type = wk->type;
      if ((type & 0x11B0000) != 0)
      {
        if ((type & 0x8000000) != 0 || wk->modeSq == 1)
          goto LABEL_65;
      }
      else if ((type & 0x8000000) != 0)
      {
        goto LABEL_65;
      }
      if (((type & 0x20000000) == 0 || wk->modeSq != 1) && ((type & 0x80000000) == 0 || wk->modeSq != 1))
      {
        if (cmpSetSkillNow())
        {
          if (wk->modeSq == 1)
            v28 = 1;
          else
            v28 = 2;
          (klass[7].klass)(klass, (u32)wk->sklCsr, v28, 0xFFFFFFFFLL, 1, klass[7].monitor);
          goto LABEL_16;
        }
        (klass[7].obj)(klass, klass[7].arrow);
        goto LABEL_16;
      }
LABEL_65:
      sklCsr = (u32)wk->sklCsr;
      if (i != sklCsr)
      {
        if ((u32)sklCsr == 12)
          (klass[7].klass)(klass, 12, 1, 0xFFFFFFFFLL, 1, klass[7].monitor);
        goto LABEL_16;
      }
      if (cmpChgSkillNow())
      {
        (klass[7].klass)(klass, (u32)wk->baseSklCsr, 2, (u32)wk->sklCsr, 1, klass[7].monitor);
        if (wk->modeSq != 1)
          goto LABEL_16;
        goto LABEL_80;
      }
      (klass[7].klass)(klass, (u32)i, 1, 0xFFFFFFFFLL, 1, klass[7].monitor);
      if (wk->modeSq != 1)
        goto LABEL_16;
LABEL_80:
      if (!wk->noSklHelp)
      {
        v24 = cmpSetSkillNow();
        v26 = v11 == -1;
        if (v24)
        {
          if (v26)
          {
            cmpDrawNoneSklHelp(0);
            goto LABEL_16;
          }
LABEL_96:
          itfDrawMiscHelp(0xA09DC380, 1.0, 0, v11, 0);
          goto LABEL_16;
        }
        if (v26)
        {
          ButtonLineHelpDispSet(0);
          goto LABEL_16;
        }
        goto LABEL_96;
      }
LABEL_16:
      unit = wk->unit;
    }
  }
  SkillSelectDraw(klass[5], 2, 0);
}

// 0x20b2ef0
void cmpSklDrawPartsSousa(tagCMP_STATUS_WORK *wk) {
  CmpSelectSkillSet *klass;
  s64 i;
  s32 v5;
  s32 v6;
  Il2CppObject *v7;
  char *LocalizeText;
  s32 v9;
  u32 v10;
  s32 v11;
  u16 v16;

  klass = _get_Instance()[10].klass;
  (klass[9].obj)(klass, 0xFFFFFFFFLL, 0, 0, klass[9].arrow);
  (klass[9].klass)(klass, 0, klass[9].monitor);
  (klass[5].buttonR)(klass, 0, 1, klass[6].klass);
  (klass[5].buttonR)(klass, 1, 1, klass[6].klass);
  (klass[5].buttonR)(klass, 2, 0, klass[6].klass);
  (klass[5].buttonR)(klass, 3, 0, klass[6].klass);
  (klass[5].buttonR)(klass, 4, 0, klass[6].klass);
  (klass[5].buttonR)(klass, 5, 0, klass[6].klass);
  (klass[5].buttonR)(klass, 6, 0, klass[6].klass);
  (klass[5].buttonR)(klass, 7, 0, klass[6].klass);
  (klass[5].buttonR)(klass, 8, 0, klass[6].klass);
  (klass[5].buttonR)(klass, 9, 0, klass[6].klass);
  (klass[5].buttonR)(klass, 10, 0, klass[6].klass);
  (klass[5].buttonR)(klass, 11, 0, klass[6].klass);
  (klass[5].buttonR)(klass, 12, 0, klass[6].klass);
  for (i = 0; i != 2; ++i)
  {
    v5 = wk->unit->sousaSkill[i];
    v6 = fldChangeFromSKLIDToMskGetNo(v5);
    v7 = cmpSousaSklName(v6, 0);
    if (v5 == 1408)
    {
      LocalizeText = GetLocalizeText("CMP_STATUS_L0018", 1);
      if (i == wk->sklCsr)
      {
        v9 = 1296780109;
        v10 = 1296780109;
        v11 = 1408;
        if (wk->modeSq == 1)
          goto LABEL_18;
      }
      else
      {
        v10 = 1296780109;
      }
LABEL_21:
      goto LABEL_22;
    }
    LocalizeText = Format("{0:s}", v7, 0);
    if (i == wk->sklCsr)
    {
      v9 = 1692838528;
      v10 = -1600273536;
      v11 = v5;
      if (wk->modeSq == 1)
      {
LABEL_18:
        v10 = v9;
        wk->selSkl = v11;
        goto LABEL_22;
      }
      goto LABEL_21;
    }
    v10 = -1600273536;
    if (!cmpChgSkillNow())
      goto LABEL_25;
    goto LABEL_23;
LABEL_22:
    if (!cmpChgSkillNow())
      goto LABEL_25;
LABEL_23:
    if (i == wk->baseSklIndex)
      v10 = 1;
LABEL_25:
    (klass[6].monitor)(klass, (u32)i, LocalizeText, v10, 0, klass[6].obj);
    (klass[6].arrow)(klass, (u32)i, 0, klass[6].skillBattle);
    (klass[6].r1Text)(klass, 4, (u32)i, klass[6].r2Text);
    if (wk->modeSq != 1)
    {
      (klass[7].obj)(klass, klass[7].arrow);
      continue;
    }
    if (i != wk->sklCsr)
      continue;
    if (cmpChgSkillNow())
    {
      (klass[7].klass)(klass, (u32)wk->baseSklCsr, 2, (u32)wk->sklCsr, 1, klass[7].monitor);
      if (v5 != 1408)
        goto LABEL_36;
      goto LABEL_37;
    }
    (klass[7].klass)(klass, (u32)i, 1, 0xFFFFFFFFLL, 1, klass[7].monitor);
    if (v5 != 1408)
    {
LABEL_36:
      if (!wk->noSklHelp)
      {
        v16 = fldChangeFromSKLIDToMskGetNo(v5);
        itfDrawMiscHelp(0xA09DC380, 1.0, 2, v16, 0);
        continue;
      }
    }
LABEL_37:
    if (cmpChgSkillNow())
      continue;
    ButtonLineHelpDispSet(0);
  }
  SkillSelectDraw(klass[5], 1, 0);
}

// 0x20b36d0
void DrawHelp(tagCMP_STATUS_WORK *wk, s8 a_alphaRate) {
  s64 type;
  Il2CppObject *Instance;
  void *gameObject;
  Il2CppClass *klass;
  Il2CppObject *v10;
  char *v11;
  s32 v12;
  s32 v13;
  Il2CppObject *v14;
  void *v15;
  s32 seqtype;
  s64 v17;
  s32 mode;
  s32 data;

  type = wk->type;
  if (type && type != 17039361 && type != 0x110040100LL)
  {
    if ((type & 0x11B0000) != 0)
    {
      if ((type & 0x10000000) != 0)
      {
        if ((type & 0x40100) == 0x100 && wk->unit->restoreMoney)
        {
          Instance = _get_Instance();
          gameObject = get_gameObject(Instance[11].klass, 0);
          sub_1BB07C0(gameObject, 1, 0);
          klass = _get_Instance()[11].klass;
          data = GBWK->player->gold;
          v10 = Box(s32, &data);
          v11 = Format("{0}", v10, 0);
          Draw(klass, v11, 1, 0);
        }
        else
        {
          v14 = _get_Instance();
          v15 = get_gameObject(v14[11].klass, 0);
          if (get_activeSelf(v15, 0))
            SetActive(v15, 0, 0);
        }
        seqtype = wk->seqtype;
        v17 = wk->type;
        mode = wk->mode;
        gohStatusHelp(seqtype, v17, mode, a_alphaRate);
      }
    }
    else if ((type & 0x8000000) == 0 && !wk->bEquipSwordNoHelp)
    {
      v12 = wk->seqtype;
      v13 = wk->mode;
      gohStatusHelp(v12, type, v13, a_alphaRate);
    }
  }
}

// 0x20b3920
void cmpDrawLevelUpPoint(tagCMP_STATUS_WORK *wk) {
  itfMover_t *mover;
  s32 v4;
  Il2CppObject *v8;
  char *v9;
  Il2CppObject *Instance;
  itfMover_t *v11;
  s32 data;
  f32 a_pPosY;
  f32 a_pPosX;

  a_pPosX = 0.0;
  a_pPosY = 0.0;
  mover = wk->mover;
  itfMoverGetPosition(mover, &a_pPosX, &a_pPosY);
  v4 = (f32)(itfMoverGetRatio(wk->mover) * 255.0);
  if (wk->step == 7)
  {
    v11 = wk->mover;
    if (itfMoverChkEnd(wk->mover))
      goto LABEL_18;
    goto LABEL_9000;
    if (itfMoverChkEnd(v11))
    {
LABEL_18:
      v4 = wk->count2 >> 15;
LABEL_7:
      goto LABEL_8;
    }
LABEL_9000:
    LOBYTE(v4) = ~(u8)v4;
    goto LABEL_7;
  }
  goto LABEL_7;
LABEL_8:
  cmpGetSpriteHnd(2);
  cmpGetSpriteHnd(2);
  cmpGetSpriteHnd(2);
  data = wk->lvup_num - wk->sel_num;
  v8 = Box(s32, &data);
  v9 = Format("{0,2:d}", v8, 0);
  Concat_54766928(0, v9, 0);
  Instance = _get_Instance();
  LevelUpPointDrawUnity(Instance[8].klass, wk->lvup_num - wk->sel_num, ((4210816 * (u32)(u8)v4) >> 23) | 0xA09DC300, 0);
}

// 0x20b3c20
void cmpDrawLearnSkillEffect(tagCMP_STATUS_WORK *wk) {
  if (wk->count <= 26)
  {
    cmpGetSpriteHnd(2);
    return;
  }
}

// 0x20b3d10
bool cmpDrawOutEffectCheck(void) {
  bool v2;

  if (!cmpProcessCheck())
  {
    v2 = 0;
    goto LABEL_10;
  }
  v2 = ProcessCheck();
LABEL_10:
  if (cmpProcessCheck())
    return v2;
  return ProcessCheck() != 0 || v2;
}

// 0x20b3e10
dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 klass_low;
  Il2CppObject *v7;
  s32 v8;
  Il2CppObject *Instance;
  s32 v12;
  s32 klass_high;
  u32 v14;
  s32 v15;
  Il2CppObject *v16;
  sdfModelOt_t *v20;
  s32 v21;
  s32 v24;
  s32 v25;
  Il2CppObject *v26;
  CmpBasePartsSet *klass;
  Il2CppObject *v29;
  s32 v30;
  s32 v32;
  void *v37;
  Il2CppObject *v39;
  s64 v40;
  u32 v43;
  s32 v45;
  Il2CppObject *v46;
  s32 v47;
  u32 v48;
  char *v49;
  s32 v52;
  u32 NowBookCnt;
  u32 BookCnt;
  s32 v55;
  s32 v56;
  Il2CppClass *v57;
  s64 v58;
  s64 v59;
  s64 v60;
  s32 v61;
  s32 v63;
  char *v64;
  s32 name_high;
  Il2CppObject *v67;
  s32 SelectMemSklID;
  u16 v70;
  f32 v71;
  u32 v72;
  u16 v73;
  s32 v74;
  s32 v75;
  void *v77;
  Il2CppObject *v78;
  s64 p_player;
  s64 v83;
  f32 v84;
  s32 v85;
  f32 v86;
  s32 monitor;
  s32 m_hojo;
  f32 v89;
  s32 monitor_high;
  Il2CppObject *v91;
  void *v92;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (!BYTE1(_get_Instance()[4].monitor))
    return 0;
  if ((BYTE1(ProcessData[1].monitor) & 4) == 0)
  {
    if (cmpGetStartStatusFlag())
    {
      goto LABEL_14;
    }
    Instance = _get_Instance();
    StatusUiOff(Instance, 0);
LABEL_14:
    if (!cmpDrawOutEffectCheck())
      return 0;
    cmpEffectSetRGBA(0x80808080);
    cmpDrawEffect();
    return 0;
  }
  klass_low = LOBYTE(ProcessData[2].klass);
  if (SHIWORD(ProcessData[5].klass->_1.name) <= 0)
  {
    if (klass_low == 2)
      goto LABEL_30;
    v12 = BYTE1(ProcessData[24].klass);
    v7 = _get_Instance();
    v8 = v12 == 0;
    goto LABEL_29;
  }
  if (klass_low != 2 && klass_low != 19 && HIDWORD(ProcessData[2].klass) != 5)
  {
    v7 = _get_Instance();
    v8 = 2;
LABEL_29:
    StatusUiDraw(v7, v8, 0);
  }
LABEL_30:
  klass_high = HIDWORD(ProcessData[2].klass);
  if (klass_high == 7)
  {
    CmpStatusDraw(ProcessData);
    klass_high = HIDWORD(ProcessData[2].klass);
  }
  if (klass_high == 8 || klass_high == 5)
  {
    v16 = _get_Instance();
    StatusUiGoobyOff(v16, 0);
    v15 = 0;
  }
  else
  {
    if (klass_high)
      goto LABEL_37;
    v14 = LOBYTE(ProcessData[2].klass);
    v15 = 0;
    if (v14 > 6)
      goto LABEL_39;
    if (((1 << v14) & 0x6A) != 0)
    {
LABEL_37:
      v15 = 255;
    }
    else if (v14 == 4)
    {
      v89 = (f32)((f32)SLOWORD(ProcessData[3].monitor) * 255.0) / 10.0;
      v15 = v89 == INFINITY ? 0x80000000 : (s32)v89;
      monitor_high = HIDWORD(ProcessData[2].monitor);
      if (monitor_high != 1 && monitor_high != 16)
        v15 = 255 - v15;
    }
  }
LABEL_39:
  cmpEffectSetRGBA(0x80808080);
  if (HIDWORD(ProcessData[2].monitor) == 2)
  {
    if ((BYTE1(ProcessData[1].monitor) & 8) == 0)
      goto LABEL_55;
    goto LABEL_47;
  }
  cmpDrawEffect();
  if ((BYTE1(ProcessData[1].monitor) & 8) != 0)
  {
LABEL_47:
    if (!cmpSwordSelFlagChk())
    {
      v20 = ModelOt[0];
      cmpDrawStatusModel(v20);
    }
  }
LABEL_55:
  cmpDrawPartsName(ProcessData, v15);
  cmpDrawPartsExp(ProcessData[5].klass, v21);
  cmpDrawParameter(ProcessData, v15);
  if (LOBYTE(ProcessData[2].klass) == 2)
  {
    v24 = HIDWORD(ProcessData[2].klass);
    if (v24 != 1 && v24 != 7)
    {
      name_high = SHIWORD(ProcessData[5].klass->_1.name);
      v67 = _get_Instance();
      if (name_high <= 0)
      {
        klass = v67[8].klass;
        v91 = _get_Instance();
        RaidouTopDraw(v91, 3, 0);
        goto LABEL_65;
      }
      else
      {
        klass = v67[10].klass;
        goto LABEL_65;
      }
      goto LABEL_65;
    }
  }
  v25 = SHIWORD(ProcessData[5].klass->_1.name);
  v26 = _get_Instance();
  if (v25 <= 0)
  {
    klass = v26[8].klass;
    cmpDrawRaidouSkill(ProcessData);
    cmpDrawPartsSpritSkill(ProcessData, v61);
  }
  else
  {
    klass = v26[10].klass;
    v29 = _get_Instance();
    RaidouTopDraw(v29, 3, 0);
    cmpDrawPartsSkill(ProcessData, v30);
    cmpDrawPartsOmoideSkill(ProcessData, v32);
  }
LABEL_65:
  cmpDrawPartsLRHelpDraw(ProcessData, klass);
  if (HIWORD(ProcessData[5].klass->_1.name))
    goto LABEL_66;
  v40 = ProcessData[3].klass;
  if (v40 <= 268697855)
    goto LABEL_85;
  if (v40 != 0x110040100LL && v40 != 268697856)
    goto LABEL_165;
LABEL_137:
  if (!HIDWORD(ProcessData[18].klass))
    goto LABEL_165;
  if (HIDWORD(ProcessData[12].monitor) == 2)
  {
    SelectMemSklID = cmpCurGetSelectMemSklID();
    if (!SelectMemSklID)
      goto LABEL_197;
    v70 = SelectMemSklID;
    v71 = (f32)v15 / 255.0;
    v72 = -1600273536;
    v73 = v70;
    v74 = 0;
  }
  else
  {
    m_hojo = tbl[SWORD1(ProcessData[7].klass->_1.declaringType)]->m_hojo;
    if (!m_hojo)
      goto LABEL_197;
    if (ProcessData[3].klass != 268697856)
    {
      v92 = get_Instance(0);
      if (!GetItfSortSysActive(v92, 0))
      {
        ButtonLineHelpDispSet(0);
      }
      goto LABEL_197;
    }
    v72 = 1692838528;
    v71 = (f32)v15 / 255.0;
    v73 = m_hojo;
    v74 = 1;
  }
  itfDrawMiscHelp(v72, v71, 0, v73, v74);
LABEL_197:
  LODWORD(ProcessData[18].monitor) = ((u8)LODWORD(ProcessData[18].monitor) + 1) & 0x7F;
  goto LABEL_66;
LABEL_85:
  if (v40 == 17039361)
    goto LABEL_137;
  if (v40 != 268697601)
  {
LABEL_165:
    p_player = &GBWK->player;
    goto LABEL_168;
  }
  p_player = &ProcessData[7];
LABEL_168:
  v83 = *(s16 *)(*(u64 *)p_player + 82);
  if (tbl[v83]->m_hojo)
  {
    if ((BYTE2(ProcessData[1].monitor) & 1) != 0)
    {
      v84 = v15;
      if (SLODWORD(ProcessData[10].monitor) > 1)
        v85 = 1;
      else
        v85 = 2;
      v86 = v84 / 255.0;
      rstResultResultGuideSet(v85, 0, 90);
      monitor = ProcessData[11].monitor;
      itfDrawMiscHelp(0xA09DC380, v86, 3, monitor, 0);
    }
    else if (!HIDWORD(ProcessData[12].monitor) && HIDWORD(ProcessData[2].klass) != 1)
    {
      ButtonLineHelpDispSet(0);
    }
  }
LABEL_66:
  if (!HIDWORD(ProcessData[12].monitor) && ProcessData[3].klass != 268697856)
  {
    if (GohGohNativeSq() != 1)
    {
      v37 = get_Instance(0);
      if (!GetItfSortSysActive(v37, 0) && (BYTE2(ProcessData[1].monitor) & 1) == 0 && !LODWORD(ProcessData[14].klass))
      {
        ButtonLineHelpDispSet(0);
      }
    }
  }
  DrawHelp(ProcessData, 255);
  if ((BYTE2(ProcessData[1].monitor) & 1) == 0)
  {
    if (SHIWORD(ProcessData[5].klass->_1.name) <= 0)
    {
      v39 = _get_Instance();
      LevelUpPointClose(v39[8].klass, 0);
    }
    goto LABEL_92;
  }
  cmpDrawLevelUpPoint(ProcessData);
LABEL_92:
  if (LODWORD(ProcessData[14].klass))
  {
    (klass->klass->vtable._14_OmoideOverSkillActive.methodPtr)(klass, 1, klass->klass->vtable._14_OmoideOverSkillActive.method);
    cmpGetSpriteHnd(2);
    cmpDrawSkillNameEx((s32)ProcessData[14].klass, 287, 268, v43, 255);
    v45 = HIDWORD(ProcessData[14].klass);
    v46 = _get_Instance();
    if (v45 != -1)
    {
      v47 = *((u32 *)&ProcessData[5].klass->rgctx_data[4].rgctxDataDummy + SHIDWORD(ProcessData[14].klass));
      v48 = -1600273536;
      v49 = sdatSkillHelp(v47, 1);
      HelpTextDraw(v46, v49, 1, 0xA09DC380, 0);
      v52 = ProcessData[14].klass;
LABEL_101:
      cmpDrawSkillNameExUnity(v52, 8, v48, 0, 0, 0);
      NowBookCnt = CmpStatusGetNowBookCnt(ProcessData[5].klass, (s32)ProcessData[14].klass);
      BookCnt = CmpStatusGetBookCnt(ProcessData[5].klass, (s32)ProcessData[14].klass);
      (klass->klass->vtable._22_GaugeUiDraw.methodPtr)(klass, 8, NowBookCnt, BookCnt, klass->klass->vtable._22_GaugeUiDraw.method);
      goto LABEL_104;
    }
    v63 = ProcessData[14].klass;
    v64 = sdatSkillHelp(v63, 1);
    HelpTextDraw(v46, v64, 1, 0xA09DC380, 0);
    v48 = 1692838528;
    cmpGetSpriteHnd(2);
    (klass->klass->vtable._12_SkillCursor.methodPtr)(klass, 8, 1, 0xFFFFFFFFLL, 1, klass->klass->vtable._12_SkillCursor.method);
    v52 = ProcessData[14].klass;
    goto LABEL_101;
  }
  if (LODWORD(ProcessData[13].klass))
    (klass->klass->vtable._14_OmoideOverSkillActive.methodPtr)(klass, 0, klass->klass->vtable._14_OmoideOverSkillActive.method);
LABEL_104:
  if (!HIDWORD(ProcessData[13].klass))
    goto LABEL_151;
  (klass->klass->vtable._16_SkillLvUpLightOn.methodPtr)(klass, HIDWORD(ProcessData[23].monitor), klass->klass->vtable._16_SkillLvUpLightOn.method);
  v55 = LOBYTE(ProcessData[26].klass) ? 3 : 2;
  v56 = HIDWORD(ProcessData[13].klass) + v55;
  HIDWORD(ProcessData[13].klass) = v56;
  if (v56 < 61)
    goto LABEL_151;
  v57 = ProcessData[5].klass;
  v58 = *(u64 *)&v57->_2.thread_static_fields_offset;
  v59 = *(u64 *)(v58 + 24);
  if ((s32)v59 < 1)
  {
LABEL_113:
    LODWORD(v60) = 0;
  }
  else
  {
    v60 = 0;
    while (!*(u32 *)(v58 + 32 + 4 * v60))
    {
      if ((u32)*(v58 + 24) == ++v60)
        goto LABEL_113;
    }
  }
  if (!LOBYTE(ProcessData[24].klass))
  {
    if ((s32)v60 < (s32)v59)
      *(u32 *)(v58 + 4 * (u32)v60 + 32) = 0;
    v75 = v57->_2.static_fields_size - 1;
    v57->_2.static_fields_size = v75;
    if ((v75 & 0x80000000) == 0)
      goto LABEL_150;
    goto LABEL_148;
  }
  if ((v57->_2.static_fields_size & 0x80000000) != 0)
  {
LABEL_148:
    v57->_2.static_fields_size = 0;
    if ((s32)v59 >= 1)
      sub_188E3B0(v58 + 32, 0, 4 * (u32)v59);
  }
LABEL_150:
  (klass->klass->vtable._17_SkillLvUpLightOff.methodPtr)(klass, HIDWORD(ProcessData[23].monitor), klass->klass->vtable._17_SkillLvUpLightOff.method);
  HIDWORD(ProcessData[13].klass) = 0;
LABEL_151:
  if (cmpGetStartStatusFlag())
  {
    v77 = ProcessData[20].monitor;
    if (v77)
      (*(v77 + 3))(*((u64 *)v77 + 8), *((u64 *)v77 + 5));
    v78 = _get_Instance();
    CampActive(v78, 1, 0);
    cmpSetStartStatusSetting(0, 0);
  }
  return 0;
}

// 0x20b4d70
void cmpSetStartStatusSetting(bool _flag, void *_func) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  ProcessData[20].monitor = func;
  BYTE2(ProcessData[20].klass) = flag;
}

// 0x2098240
bool cmpGetStartStatusFlag(void) {
  Il2CppObject *ProcessData;

  if (!g_mainPID)
  {
    LOBYTE(ProcessData) = 0;
    return (char)ProcessData;
  }
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return (char)ProcessData;
  LOBYTE(ProcessData) = BYTE2(ProcessData[20].klass) != 0;
  return (char)ProcessData;
}

// 0x20b4eb0
void cmpNoCallVoiceSet(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  LOBYTE(ProcessData[25].monitor) = 1;
}

// 0x20a0f50
void Start(sdatUnitWork_t *a_pUnit) {
  Il2CppObject *ProcessData;
  Il2CppObject *v6;
  Il2CppObject *v8;
  Il2CppClass *klass;
  Il2CppClass *v12;
  s32 klass_low;
  u64 monitor;
  u8 *v19;
  sdatPlayerUnitWork_t *player;
  s32 swordno;
  Il2CppClass *v22;
  sdatUnitWork_t *v23;
  s64 i;
  char *v27;
  s64 j;
  char *v30;
  Il2CppObject *Instance;
  Il2CppObject *v33;
  s32 monitor_high;

  ProcessData = dds3GetProcessData(g_mainPID);
  v6 = ProcessData;
  if (a_pUnit)
  {
    if (!HIDWORD(ProcessData[2].klass))
    {
      if ((cmpGetMode() & 0x10000) != 0)
        return;
      monitor_high = HIDWORD(v6[2].monitor);
      if (monitor_high != 1)
      {
        if (monitor_high != 8)
          return;
        HIDWORD(v6[2].monitor) = 1;
      }
    }
    if (a_pUnit->devilid <= 0)
    {
      HIDWORD(v6[3].monitor) = 0;
      v8 = _get_Instance()
         + 8;
    }
    else
    {
      HIDWORD(v6[3].monitor) = (u16)a_pUnit->devilid;
      v8 = _get_Instance()
         + 10;
    }
    klass = v8->klass;
    v6[1].monitor = ((u64)v6[1].monitor | 0x100);
    cmpClearDat();
    ClassCopy(v6[5].klass, a_pUnit, 0);
    v12 = v6[11].klass;
    v12->_1.byval_arg.data = 0;
    *(u64 *)&v12->_1.byval_arg.bits = 0;
    if (((s64)v6[8].monitor & 0x80000000) != 0)
    {
      LODWORD(v6[8].monitor) = GBWK->player->para->now->tec;
    }
    klass_low = LOBYTE(v6[2].klass);
    LODWORD(v6[3].monitor) = 0;
    HIDWORD(v6[2].klass) = 0;
    monitor = v6[1].monitor;
    v6[3].klass = 0;
    if (klass_low == 9)
      LOBYTE(v6[2].klass) = 0;
    *(void **)((char *)&v6[8].monitor + 4) = -1;
    v6[1].monitor = (monitor & 0xFFFFFFFFFF8FFF7FLL | 0x400080);
    v19 = v6[8].klass;
    player = GBWK->player;
    swordno = player->swordno;
    LODWORD(player) = player->swordatk;
    LODWORD(v6[10].klass) = swordno;
    HIDWORD(v6[10].klass) = (u32)player;
    cmpGetSwordParam(swordno, v19);
    LODWORD(v6[21].monitor) = 0;
    LOBYTE(v6[25].monitor) = 0;
    HIDWORD(v6[12].monitor) = 0;
    v6[21].klass = 0xFFFFFFFFLL;
    v6[14] = 0u;
    v6[15] = 0u;
    v22 = NewSpecific(bool, 0x11u);
    v6[16].klass = v22;
    v23 = v6[5].klass;
    BYTE5(v6[16].monitor) = 0;
    cmpCurInitMemSkl(v23, 0);
    for (i = 0; ; ++i)
    {
      if (i >= SLODWORD(lastOrangePar->max_length))
        break;
      v27 = (char *)lastOrangePar + 4 * i;
      *((u32 *)v27 + 8) = -1;
    }
    for (j = 0; ; ++j)
    {
      if (j >= SLODWORD(lastBasePar->max_length))
        break;
      v30 = (char *)lastBasePar + 4 * j;
      *((u32 *)v30 + 8) = -1;
    }
    Instance = _get_Instance();
    AllGaugeOff(Instance[8].monitor, 0);
    v33 = _get_Instance();
    AllGaugeOff(v33[9].klass, 0);
    cmpLastParClear();
    (*(klass->_1.image + 61))(klass, *((u64 *)klass->_1.image + 62));
  }
}

// 0x20b50f0
void End(void) {
  Il2CppObject *ProcessData;
  u64 monitor;
  s32 klass_low;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  monitor = ProcessData[1].monitor;
  if ((monitor & 0x4000000) == 0)
  {
    if (!HIDWORD(ProcessData[2].klass))
    {
      klass_low = LOBYTE(ProcessData[2].klass);
      if (klass_low != 1 && klass_low != 4)
      {
        HIDWORD(ProcessData[2].monitor) = 1;
        LOBYTE(ProcessData[2].klass) = 4;
      }
    }
    ProcessData[1].monitor = (monitor | 0x4000000);
  }
}

// 0x20b5240
bool cmpChkEnd(void) {
  Il2CppObject *ProcessData;
  s32 klass_high;
  s32 v6;
  s32 v7;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  klass_high = HIDWORD(ProcessData[2].klass);
  if (klass_high == 7)
    v6 = 10;
  else
    v6 = 9;
  if (klass_high == 5)
    v7 = 7;
  else
    v7 = v6;
  return LOBYTE(ProcessData[2].klass) == v7;
}

// 0x20b5380
void cmpStartLevelUp(sdatUnitWork_t *a_pUnitDst, sdatPlayerUnitWork_t *_newPlayerPar) {
  Il2CppObject *ProcessData;
  Il2CppObject *v8;
  Il2CppClass *klass;
  sdatParaWork_t *now;
  sdatParaWork_t *backup;
  u16 *data;
  s64 v14;
  sdatUnitWork_t *v15;
  s32 v16;
  sdatUnitWork_t *v17;
  int16x4_t *v18;
  int8x16_t v19;
  sdatUnitWork_t *v20;
  Il2CppClass *v21;
  sdatPlayerUnitWork_t *player;
  s32 maxmag;
  sdatPlayerUnitWork_t *v27;
  s32 v28;
  u64 monitor;
  Il2CppClass *v31;
  u32 v34;
  sdatUnitWork_t *v35;
  float32x2x2_t v36;

  ProcessData = dds3GetProcessData(g_mainPID);
  v8 = ProcessData;
  if (a_pUnitDst)
  {
    klass = ProcessData[5].klass;
    if ((u16)a_pUnitDst->devilid == HIWORD(klass->_1.name))
    {
      if (((s64)klass->_1.name & 2) != 0)
      {
        now = a_pUnitDst->now;
        backup = a_pUnitDst->backup;
        BYTE1(ProcessData[20].klass) = 1;
        v14 = *(u64 *)&klass->_1.byval_arg.bits;
        data = klass->_1.this_arg.data;
        now->luck = *(u16 *)(v14 + 38);
        backup->luck = data[19];
      }
      ProcessData[6].monitor = a_pUnitDst;
      ClassCopy(v8[6].klass, a_pUnitDst, 0);
      ClassCopy(v8[5].monitor, v8[5].klass, 0);
      v15 = v8[6].klass;
      v16 = v8[10].klass;
      datCalcNowParam(v15, v16, newPlayerPar);
      datCalcNowParam(v8[5].monitor, (s32)v8[10].klass, newPlayerPar);
      v17 = v8[6].klass;
      v18 = v17->now;
      v19 = vsubl_s16(v18[4], *(int16x4_t *)(*((u64 *)v8[5].monitor + 5) + 32));
      v36.val[0].n64_u64[0] = v19.n128_u64[0];
      v36.val[1].n64_u64[0] = vextq_s8(v19, v19, 8u).n128_u64[0];
      vst2_f32(&v8[11].klass->_1.byval_arg, v36);
      v20 = v8[5].klass;
      v17->backup->hp = v18[2].n64_i32[0];
      if ((v20->flag & 6) == 4)
      {
        HIDWORD(v8[8].monitor) = 0;
        LODWORD(v8[9].klass) = 0;
      }
      ClassCopy(v20, v17, 0);
      v21 = v8[5].klass;
      if (((s64)v21->_1.name & 2) != 0)
      {
        v21 = v8[5].klass;
        player = GBWK->player;
        maxmag = player->maxmag;
        player->para->level = (s8)v21->_1.namespaze;
        datCalcMagMax();
        v27 = GBWK->player;
        v28 = v27->maxmag;
        if (v28 >= maxmag)
        {
          v27 = GBWK->player;
          v28 = v27->maxmag;
          v28 += v27->mag - maxmag;
        }
        {
          v27 = GBWK->player;
          v28 = v27->maxmag;
        }
        v27->mag = v28;
        datDvlParaUpdate(0);
      }
      LOBYTE(v8[2].klass) = 0;
      HIDWORD(v8[2].klass) = 1;
      monitor = v8[1].monitor;
      HIDWORD(v8[12].monitor) = 0;
      LODWORD(v8[13].klass) = 0;
      v8[1].monitor = (monitor & 0xFFFFFFFFFFFFBFFFLL);
      v8[3].klass = &loc_2000000;
      v8[14] = 0u;
      v8[15] = 0u;
      v8[21] = (Il2CppObject)xmmword_3D00DF0;
      v31 = NewSpecific(bool, 0x11u);
      v8[16].klass = v31;
      BYTE5(v8[16].monitor) = 0;
      LOBYTE(v8[26].klass) = 0;
      HIDWORD(v8[11].monitor) = 0;
      LODWORD(v8[10].monitor) = 0;
      v35 = v8[6].monitor;
      if (!v34)
      cmpCurInitMemSkl(v35, 0);
    }
  }
}

// 0x20b5720
void cmpSpeedUpSklOff(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  LOBYTE(ProcessData[26].klass) = 0;
}

// 0x20b5830
void cmpStartRankUp(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  u64 v6;
  Il2CppClass *v8;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  LOBYTE(ProcessData[2].klass) = 0;
  HIDWORD(ProcessData[2].klass) = 2;
  v6 = (u64)ProcessData[1].monitor & 0xFFFFFFFFFFFFBFFFLL;
  ProcessData[14] = 0u;
  ProcessData[15] = 0u;
  v4[1].monitor = v6;
  *(void **)((char *)&v4[12].monitor + 4) = 0x100000001LL;
  v4[3].klass = &loc_2000000;
  v4[21] = (Il2CppObject)xmmword_3D00DF0;
  v8 = NewSpecific(bool, 0x11u);
  v4[16].klass = v8;
  BYTE5(v4[16].monitor) = 0;
}

// 0x20b59a0
bool cmpChkWait2(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return SHIDWORD(ProcessData[2].klass) >= 1 && LOBYTE(ProcessData[2].klass) == 18;
  return SHIDWORD(ProcessData[2].klass) >= 1 && LOBYTE(ProcessData[2].klass) == 18;
}

// 0x20b5ae0
bool cmpChkEnd2(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  s32 klass_high;
  Il2CppClass *klass;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  klass_high = HIDWORD(ProcessData[2].klass);
  if (klass_high < 1 || LOBYTE(ProcessData[2].klass) != 21)
    return 0;
  if (klass_high == 1)
  {
    ClassCopy(ProcessData[6].monitor, ProcessData[5].klass, 0);
    klass = v4[5].klass;
    if (((s64)klass->_1.name & 2) != 0)
      LODWORD(v4[8].monitor) = *(s16 *)(*(u64 *)&klass->_1.byval_arg.bits + 36);
  }
  return 1;
}

// 0x20b5c40
void cmpStartLearnSkillMessage(s32 a_type, SKLID a_skillID, bool _ofc) {
  Il2CppObject *ProcessData;
  bool v11;
  char v12;
  char v13;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  if (LOBYTE(ProcessData[2].klass) == 18)
  {
    if (a_type)
    {
      v11 = !ofc;
      v12 = 10;
      LODWORD(ProcessData[9].klass) = a_skillID;
      v13 = 14;
    }
    else
    {
      HIDWORD(ProcessData[8].monitor) = a_skillID;
      v11 = !ofc;
      v12 = 8;
      v13 = 12;
    }
    if (!v11)
      v12 = v13;
    LOBYTE(ProcessData[2].klass) = v12;
  }
}

// 0x20b5db0
void cmpSetRecover(s32 a_type) {
  Il2CppObject *ProcessData;
  s64 v7;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  if (LOBYTE(ProcessData[2].klass) == 18)
  {
    v7 = 0x80000;
    if (!a_type)
      v7 = 0x40000;
    ProcessData[1].monitor = ((s64)ProcessData[1].monitor | v7);
    LOBYTE(ProcessData[2].klass) = 16;
  }
}

// 0x209f340
void cmpSetFlagDraw(bool a_bDraw) {
  Il2CppObject *ProcessData;
  s64 v7;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  v7 = 1024;
  if (!a_bDraw)
    v7 = 0;
  ProcessData[1].monitor = ((u64)ProcessData[1].monitor & 0xFFFFFFFFFFFFFBFFLL | v7);
}

// 0x20b5f00
bool cmpChkDraw(void) {
  Il2CppObject *ProcessData;

  if (!g_mainPID)
    return 0;
  if (!dds3ExistProcess(g_mainPID))
    return 0;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return (BYTE1(ProcessData[1].monitor) & 4) != 0;
  return (BYTE1(ProcessData[1].monitor) & 4) != 0;
}

// 0x20a6530
void cmpSetFlagCtrlMode(bool a_bFlag) {
  Il2CppObject *ProcessData;
  s64 v7;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  v7 = 0x4000;
  if (!a_bFlag)
    v7 = 0;
  ProcessData[1].monitor = ((u64)ProcessData[1].monitor & 0xFFFFFFFFFFFFBFFFLL | v7);
}

// 0x20a6670
void cmpSetFlagNoExplan(bool a_bFlag) {
  Il2CppObject *ProcessData;
  s64 v7;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  v7 = 0x100000000LL;
  if (!a_bFlag)
    v7 = 0;
  ProcessData[1].monitor = ((u64)ProcessData[1].monitor & 0xFFFFFFFEFFFFFFFFLL | v7);
}

// 0x20b60b0
void cmpSetFlagCamp(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  ProcessData[1].monitor = ((u64)ProcessData[1].monitor & 0xFFFFFFFFFFFF3FFFLL | 0x8000);
}

// 0x20b61d0
bool StatusGoSword(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return (char)ProcessData;
  LOBYTE(ProcessData) = BYTE2(ProcessData[24].klass) != 0;
  return (char)ProcessData;
}

// 0x20a22d0
void cmpSetSkillMode(bool _flag) {
  Il2CppObject *ProcessData;
  s64 v7;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  v7 = 0x20000;
  if (!flag)
    v7 = 0;
  ProcessData[1].monitor = ((u64)ProcessData[1].monitor & 0xFFFFFFFFFFFDFFFFLL | v7);
}

// 0x2099fa0
bool cmpSetSkillNow(void) {
  u8 *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return (char)ProcessData;
  LODWORD(ProcessData) = (ProcessData[26] >> 1) & 1;
  return (char)ProcessData;
}

// 0x209a3f0
void cmpChgSkillMode(bool _flag) {
  Il2CppObject *ProcessData;
  s64 v7;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  v7 = 0x200000000LL;
  if (!flag)
    v7 = 0;
  ProcessData[1].monitor = ((u64)ProcessData[1].monitor & 0xFFFFFFFDFFFFFFFFLL | v7);
}

// 0x209a0c0
bool cmpChgSkillNow(void) {
  u8 *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return (char)ProcessData;
  LODWORD(ProcessData) = (ProcessData[28] >> 1) & 1;
  return (char)ProcessData;
}

// 0x20b62f0
bool cmpGetFlagCallDebug(void) {
  u8 *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return (ProcessData[27] >> 4) & 1;
  return (ProcessData[27] >> 4) & 1;
}

// 0x20b6410
bool cmpGetFlagDebug(void) {
  u8 *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return (ProcessData[27] >> 5) & 1;
  return (ProcessData[27] >> 5) & 1;
}

// 0x209e550
bool cmpGetFlagScreenShot(void) {
  return 0;
}

// 0x20b6530
s32 cmpGetSetMotionFrame(void) {
  return 0;
}

// 0x20b4fd0
CMP_STATUS_MODE cmpGetMode(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  if (LOBYTE(ProcessData[2].klass) == 4)
    return HIDWORD(ProcessData[2].monitor) | 0x10000;
  else
    return HIDWORD(ProcessData[2].monitor);
}

// 0x20b6540
s32 cmpGetSklType(bool _raidou) {
  Il2CppObject *ProcessData;
  s64 v7;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return (s32)ProcessData;
  v7 = 208;
  if (raidou)
    v7 = 348;
  LODWORD(ProcessData) = *(u32 *)((char *)&ProcessData->klass + v7);
  return (s32)ProcessData;
}

// 0x20a13b0
bool SetType(CMP_STATUS_TYPE a_type, s32 a_swordno, bool _root) {
  Il2CppObject *ProcessData;
  Il2CppObject *v10;
  Il2CppClass *klass;
  s32 name_high;
  u32 token;
  s32 StockDevilIndex;
  Il2CppObject *Instance;
  Il2CppObject *v17;
  sdatPlayerUnitWork_t *v19;
  s32 v21;
  Il2CppClass *v22;
  s32 Sword4Param;
  Il2CppClass *v24;
  s32 v25;
  Il2CppClass *v26;
  s32 v27;
  Il2CppClass *v28;
  s32 v29;
  s32 v30;
  Il2CppClass *v31;
  void *monitor;
  Il2CppObject *v34;
  Il2CppObject *v35;
  Il2CppObject *v36;
  sdatPlayerUnitWork_t *v38;
  Il2CppClass *v40;
  Il2CppClass *v41;
  Il2CppClass *v42;
  Il2CppClass *v43;
  char v47;
  Il2CppClass *v49;
  u16 *v50;
  s16 v51;
  Il2CppClass *v52;
  sdatUnitWork_t *v53;
  s16 *now;
  s32 v55;
  s32 v56;
  s32 v57;
  s32 v58;
  Il2CppClass *v59;

  ProcessData = dds3GetProcessData(g_mainPID);
  v10 = ProcessData;
  if (a_type <= 268566784)
  {
    if (a_type == 17039361)
      goto LABEL_22;
    if (a_type == 268566784)
    {
      klass = ProcessData[5].klass;
      name_high = SHIWORD(klass->_1.name);
      token = klass->_2.token;
      StockDevilIndex = datGetStockDevilIndex(name_high, token);
      Instance = _get_Instance();
      AllGaugeOff(Instance[9].klass, 0);
      cmpLastParClear();
      if (root)
        goto LABEL_43;
      if (StockDevilIndex == -1)
      {
        v53 = Allocate(sdatUnitWork_t);
        _ctor(v53, 0);
        if (!gohKarteCreateUnitUc(SHIWORD(v10[5].klass->_1.name), v10[5].klass->_2.token, v53, 0) && !gohKarteCreateUnitUc(SHIWORD(v10[5].klass->_1.name), v10[5].klass->_2.token, v53, 1))
        {
          LogError("指定悪魔が見つからない", 0);
        }
        v49 = v10[11].klass;
        v52 = v49;
        v50 = *(u16 **)&v10[5].klass->_1.byval_arg.bits;
        v51 = v50[16];
      }
      else
      {
        v49 = v10[11].klass;
        v50 = *(u16 **)&v10[5].klass->_1.byval_arg.bits;
        v51 = v50[16];
        v52 = v10[11].klass;
        v53 = GBWK->player->stock_id[StockDevilIndex];
      }
      now = v53->now;
      v55 = now[18];
      v56 = (s16)v50[18];
      LODWORD(v49->_1.byval_arg.data) = v51 - now[16];
      v57 = (s16)v50[17] - now[17];
      v58 = (s16)v50[19] - now[19];
      HIDWORD(v52->_1.byval_arg.data) = v56 - v55;
      v52->_1.byval_arg.bits = v57;
      *(&v52->_1.byval_arg.bits + 1) = v58;
      goto LABEL_56;
    }
  }
  else
  {
    if (a_type == 268697601)
    {
      if ((a_swordno & 0x80000000) == 0)
      {
        v36 = _get_Instance();
        AllGaugeOff(v36[8].monitor, 0);
        cmpLastParClear();
        v38 = v10[7].klass;
        ClassCopy(v38, GBWK->player, 0);
        ClassCopy(v10[7].klass->_1.castClass, v10[5].klass, 0);
        datSetPlayerUnitSword(v10[7].klass, a_swordno, 0);
        v40 = v10[11].klass;
        LODWORD(v40->_1.byval_arg.data) = datGetSword4Param(a_swordno, 0);
        v41 = v10[11].klass;
        HIDWORD(v41->_1.byval_arg.data) = datGetSword4Param(a_swordno, 1);
        v42 = v10[11].klass;
        v42->_1.byval_arg.bits = datGetSword4Param(a_swordno, 2);
        v43 = v10[11].klass;
        *(&v43->_1.byval_arg.bits + 1) = datGetSword4Param(a_swordno, 3);
        if (!root)
          goto LABEL_56;
        goto LABEL_43;
      }
      return 0;
    }
    if (a_type == 268697856 || a_type == 0x110040100LL)
    {
LABEL_22:
      if ((a_swordno & 0x80000000) == 0)
      {
        v17 = _get_Instance();
        AllGaugeOff(v17[8].monitor, 0);
        cmpLastParClear();
        v19 = v10[7].klass;
        ClassCopy(v19, GBWK->player, 0);
        datSetPlayerUnitSword(v10[7].klass, a_swordno, 0);
        v21 = v10[10].klass;
        v22 = v10[11].klass;
        Sword4Param = datGetSword4Param(a_swordno, 0);
        LODWORD(v22->_1.byval_arg.data) = Sword4Param - datGetSword4Param(v21, 0);
        v24 = v10[11].klass;
        v25 = datGetSword4Param(a_swordno, 1);
        HIDWORD(v24->_1.byval_arg.data) = v25 - datGetSword4Param(v21, 1);
        v26 = v10[11].klass;
        v27 = datGetSword4Param(a_swordno, 2);
        v26->_1.byval_arg.bits = v27 - datGetSword4Param(v21, 2);
        v28 = v10[11].klass;
        v29 = datGetSword4Param(a_swordno, 3);
        v30 = v29 - datGetSword4Param(v21, 3);
        monitor = v10[7].monitor;
        v31 = v10[8].klass;
        *(&v28->_1.byval_arg.bits + 1) = v30;
        Copy_56180528(v31, monitor, (s32)v31->_1.namespaze, 0);
        cmpGetSwordParam(a_swordno, v10[8].klass);
        if (!root)
          goto LABEL_56;
LABEL_43:
        v47 = 1;
        goto LABEL_57;
      }
      return 0;
    }
  }
  v34 = _get_Instance();
  AllGaugeOff(v34[8].monitor, 0);
  v35 = _get_Instance();
  AllGaugeOff(v35[9].klass, 0);
  cmpLastParClear();
  if (root)
    goto LABEL_43;
LABEL_56:
  v47 = 0;
LABEL_57:
  LOBYTE(v10[22].klass) = v47;
  v59 = v10[16].klass;
  v10[3].klass = a_type;
  LODWORD(v10[21].monitor) = 0;
  HIDWORD(v10[12].monitor) = 0;
  v10[21].klass = 0xFFFFFFFFLL;
  v10[14] = 0u;
  v10[15] = 0u;
  if ((s32)v59->_1.namespaze >= 1)
    sub_188E3B0(&v59->_1.byval_arg, 0, (u32)v59->_1.namespaze);
  BYTE5(v10[16].monitor) = 0;
  if (a_type <= 268697601)
  {
    if (a_type != 17039361 && a_type != 268697601)
      return 1;
  }
  else if ((a_type | 0x100000000LL) != 0x110040100LL)
  {
    return 1;
  }
  HIDWORD(v10[18].klass) = 8;
  return 1;
}

// 0x20b0350
void cmpRankNewOff(s32 _setNo) {
  void *v3;
  Il2CppObject *ProcessData;
  Il2CppObject *v7;
  s32 v10;
  void *klass;
  s32 v12;
  void *v13;

  v3 = Allocate(Project_cmpStatus___c__DisplayClass266_0);
  _c__DisplayClass266_0___ctor(v3, 0);
  v3->_setNo = setNo;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (ProcessData)
  {
    v7 = ProcessData;
    v10 = IndexOf_int_(GBWK->player->syougouNew, v3->_setNo);
    if (v10 != -1)
    {
      klass = v7[23].klass;
      v12 = v10;
      v13 = Allocate(System_Predicate_cmpStatus_RankText_);
      __ctor(v13, v3, Method_Project_cmpStatus___c__DisplayClass266_0__RankNewOff_b__0__, 0);
      BYTE4(_Find(klass, v13)[2].klass) = 0;
      GBWK->player->syougouNew[v12] = 0;
    }
    return;
  }
  LogWarning("呼出し不可タイミング", 0);
}

// 0x20b6680
void cmpRankNewOn(s32 _setNo) {
  s32 v5;
  void *syougouNew;
  void *v7;
  void *v8;
  s64 v9;
  s32 v10;
  s32 **arrPlayerRank_local;
  s64 v13;
  s64 size;
  s32 v15;
  u64 *v16;
  s32 *items;
  s64 v18;
  u64 *v19;
  s32 v20;
  s32 v21;
  s32 *v22;
  s64 i;
  s32 **arrPlayerRankDlc_local;
  s64 v26;
  u64 *v27;
  s32 v28;
  s32 v29;
  s32 *v30;
  s32 v31;
  sdatPlayerUnitWork_t *player;
  s32 *v33;
  s32 v34;
  s32 v35;
  s32 Item;

  v5 = s_aSummonerRankTbl[setNo];
  syougouNew = GBWK->player->syougouNew;
  v7 = Allocate(System_Collections_Generic_List_int_);
  __ctor_47770768(v7, syougouNew);
  v8 = Allocate(System_Collections_Generic_List_int_);
  __ctor_47770496(v8, 76);
  v9 = 4;
  v10 = v8->_version + 1;
  v8->_size = 0;
  v8->_version = v10;
  while (1)
  {
    arrPlayerRank_local = arrPlayerRank;
    if (v9 - 4 >= SLODWORD(arrPlayerRank_local->max_length))
      break;
    v13 = *((u64 *)&arrPlayerRank_local->obj.klass + v9);
    if (*(u32 *)(v13 + 32) == v5)
    {
      v13 = *((u64 *)&arrPlayerRank->obj.klass + v9);
      size = v8->_size;
      v15 = *(u32 *)(v13 + 36);
      v16 = Method_System_Collections_Generic_List_int__Add__;
      ++v8->_version;
      items = v8->_items;
      if ((u32)size >= LODWORD(items->max_length))
      {
        _AddWithResize(v8, v15, *(const MethodInfo_2D8F530 **)(*(u64 *)(v16[4] + 192) + 112));
      }
      else
      {
        v8->_size = size + 1;
        items[size] = v15;
      }
      if (rankText2[*(s32 *)(*((u64 *)&arrPlayerRank->obj.klass + v9) + 36)])
      {
        v18 = v8->_size;
        v19 = Method_System_Collections_Generic_List_int__Add__;
        v20 = *(u32 *)(*((u64 *)&arrPlayerRank->obj.klass + v9) + 36);
        ++v8->_version;
        v21 = v20 + 100;
        v22 = v8->_items;
        if ((u32)v18 >= LODWORD(v22->max_length))
        {
          _AddWithResize(v8, v21, *(const MethodInfo_2D8F530 **)(*(u64 *)(v19[4] + 192) + 112));
        }
        else
        {
          v8->_size = v18 + 1;
          v22[v18] = v21;
        }
      }
    }
    ++v9;
  }
  if (!Exists("new_title"))
    goto LABEL_43;
  goto LABEL_29;
  if (Exists("new_title"))
  {
LABEL_29:
    for (i = 4; ; ++i)
    {
      arrPlayerRankDlc_local = arrPlayerRankDlc;
      if (i - 4 >= SLODWORD(arrPlayerRankDlc_local->max_length))
        break;
      if (*(u32 *)(*((u64 *)&arrPlayerRankDlc_local->obj.klass + i) + 32) != v5)
        continue;
      v26 = v8->_size;
      v27 = Method_System_Collections_Generic_List_int__Add__;
      v28 = *(u32 *)(*((u64 *)&arrPlayerRankDlc->obj.klass + i) + 36);
      ++v8->_version;
      v29 = v28 + 1000;
      v30 = v8->_items;
      if ((u32)v26 >= LODWORD(v30->max_length))
      {
        _AddWithResize(v8, v29, *(const MethodInfo_2D8F530 **)(*(u64 *)(v27[4] + 192) + 112));
      }
      else
      {
        v8->_size = v26 + 1;
        v30[v26] = v29;
      }
    }
  }
LABEL_43:
  if (v8->_size >= 1)
  {
    v31 = 0;
    do
    {
      v34 = _IndexOf(v7, 0);
      if (v34 != -1)
      {
        v35 = v34;
        if (_get_Item(v8, v31))
        {
          Item = _get_Item(v8, v31);
          _set_Item(v7, v35, Item);
          player = GBWK->player;
          v33 = _ToArray(v7);
          player->syougouNew = v33;
        }
      }
      ++v31;
    }
    while (v31 < v8->_size);
  }
}

// 0x20b6bb0
void cmpCreateRankTextList(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  void *syougouNew;
  void *v8;
  s32 Length;
  s32 v10;
  void *v11;
  void *v12;
  Il2CppClass *klass;
  s32 namespaze;
  s32 v15;
  s32 v16;
  bool v17;
  s64 v20;
  char *v21;
  RankText *v22;
  void *v23;
  s64 size;
  u64 *v25;
  void *items;
  Il2CppClass **v27;
  s32 i;
  s32 v30;
  s32 v32;
  bool v33;
  s64 v36;
  char *v37;
  RankText *v38;
  void *v39;
  s64 v40;
  u64 *v41;
  void *v42;
  Il2CppClass **v43;
  s64 v46;
  s32 v47;
  bool v48;
  s64 v51;
  char *v52;
  RankText *v53;
  void *v54;
  s64 v55;
  u64 *v56;
  void *v57;
  Il2CppClass **v58;
  s32 v60;
  s32 v62;
  s32 v64;
  bool v65;
  s64 v68;
  char *v69;
  RankText *v70;
  void *v71;
  s64 v72;
  u64 *v73;
  void *v74;
  Il2CppClass **v75;
  sdatPlayerUnitWork_t *player;
  sdatPlayerUnitWork_t *v79;
  s32 *v80;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  syougouNew = GBWK->player->syougouNew;
  v8 = Allocate(System_Collections_Generic_List_int_);
  __ctor_47770768(v8, syougouNew);
  Length = GetLength(arrPlayerRank, 0, 0);
  v10 = Length - 1;
  v11 = Allocate(System_Collections_Generic_List_cmpStatus_RankText_);
  __ctor(v11);
  v12 = &v4[23];
  v4[23].klass = v11;
  klass = v4[23].klass;
  namespaze = klass->_1.namespaze;
  v15 = HIDWORD(klass->_1.namespaze) + 1;
  LODWORD(klass->_1.namespaze) = 0;
  HIDWORD(klass->_1.namespaze) = v15;
  if (namespaze >= 1)
    Clear(klass->_1.name, 0, namespaze, 0);
  v16 = arrPlayerRank[v10][1];
  v17 = _Contains(v8, v16);
  v20 = arrPlayerRank[v10][1];
  v21 = rankText[v20];
  v22 = Allocate(RankText);
  _ctor_35199088(v22, v20, v21, v16, v17, 0);
  v23 = v12;
  size = v12->_size;
  v25 = Method_System_Collections_Generic_List_cmpStatus_RankText__Add__;
  v23->_version = v12->_version + 1;
  items = v23->_items;
  if ((u32)size >= LODWORD(items->max_length))
  {
    _AddWithResize(v23, v22, *(const MethodInfo_2DFC660 **)(*(u64 *)(v25[4] + 192) + 112));
  }
  else
  {
    v23->_size = size + 1;
    v27 = &items->obj.klass + size;
    v27[4] = v22;
  }
  for (i = Length - 2; i != -1; --i)
  {
    v30 = arrPlayerRank[i][0];
    if (v30 < 0)
      break;
    if (evtBitCheck(v30))
      goto LABEL_29;
    goto LABEL_9000;
    if (evtBitCheck(arrPlayerRank[i][0]))
    {
LABEL_29:
      v32 = arrPlayerRank[i][1];
      v33 = _Contains(v8, v32);
      v36 = arrPlayerRank[i][1];
      v37 = rankText[v36];
      v38 = Allocate(RankText);
      _ctor_35199088(v38, v36, v37, v32, v33, 0);
      v39 = v12;
      v40 = v12->_size;
      v41 = Method_System_Collections_Generic_List_cmpStatus_RankText__Add__;
      v39->_version = v12->_version + 1;
      v42 = v39->_items;
      if ((u32)v40 >= LODWORD(v42->max_length))
      {
        _AddWithResize(v39, v38, *(const MethodInfo_2DFC660 **)(*(u64 *)(v41[4] + 192) + 112));
      }
      else
      {
        v39->_size = v40 + 1;
        v43 = &v42->obj.klass + v40;
        v43[4] = v38;
      }
      v46 = arrPlayerRank[i][1];
      if (rankText2[v46])
      {
        LODWORD(v46) = arrPlayerRank[i][1];
        v47 = v46 + 100;
        v48 = _Contains(v8, v46 + 100);
        v51 = arrPlayerRank[i][1];
        v52 = rankText2[v51];
        v53 = Allocate(RankText);
        _ctor_35199088(v53, v51, v52, v47, v48, 0);
        v54 = v12;
        v55 = v12->_size;
        v56 = Method_System_Collections_Generic_List_cmpStatus_RankText__Add__;
        v54->_version = v12->_version + 1;
        v57 = v54->_items;
        if ((u32)v55 >= LODWORD(v57->max_length))
        {
          _AddWithResize(v54, v53, *(const MethodInfo_2DFC660 **)(*(u64 *)(v56[4] + 192) + 112));
        }
        else
        {
          v54->_size = v55 + 1;
          v58 = &v57->obj.klass + v55;
          v58[4] = v53;
        }
      }
    }
LABEL_9000:
  }
  if (!Exists("new_title"))
    goto LABEL_66;
LABEL_45:
  v60 = GetLength(arrPlayerRankDlc, 0, 0) - 1;
  while (1)
  {
    v62 = arrPlayerRankDlc[v60][0];
    if (v62 < 0)
    {
LABEL_63:
      goto LABEL_73;
    }
    if (evtBitCheck(v62))
      goto LABEL_57;
    goto LABEL_9001;
    if (evtBitCheck(arrPlayerRankDlc[v60][0]))
    {
LABEL_57:
      v64 = arrPlayerRankDlc[v60][1] + 1000;
      v65 = _Contains(v8, v64);
      v68 = arrPlayerRankDlc[v60][1];
      v69 = dlcRankText[v68];
      v70 = Allocate(RankText);
      _ctor_35199088(v70, v68, v69, v64, v65, 0);
      v71 = v12;
      v72 = v12->_size;
      v73 = Method_System_Collections_Generic_List_cmpStatus_RankText__Add__;
      v71->_version = v12->_version + 1;
      v74 = v71->_items;
      if ((u32)v72 >= LODWORD(v74->max_length))
      {
        _AddWithResize(v71, v70, *(const MethodInfo_2DFC660 **)(*(u64 *)(v73[4] + 192) + 112));
      }
      else
      {
        v71->_size = v72 + 1;
        v75 = &v74->obj.klass + v72;
        v75[4] = v70;
      }
    }
LABEL_9001:
    if (--v60 == -1)
      goto LABEL_63;
  }
  if (Exists("new_title"))
    goto LABEL_45;
LABEL_66:
  player = GBWK->player;
  if (player->syougou < 1000)
  {
    goto LABEL_70;
LABEL_71:
    goto LABEL_73;
  }
  player->syougou = 5;
LABEL_70:
  if (GBWK->syougouRemove < 1000)
    goto LABEL_71;
  GBWK->syougouRemove = 0;
LABEL_73:
  v79 = GBWK->player;
  v80 = _ToArray(v8);
  v79->syougouNew = v80;
}

// 0x20b7540
void Init(tagCMP_STATUS_WORK *wk) {
  Il2CppObject *Instance;
  CmpStatusPartsPassPar *v6;
  cmpSummnerRankMng_t *p_sSummnerRankMng;

  Load(Dependent, "fld_all", "fld_all");
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Init();
  Instance = _get_Instance();
  UiLoad(Instance, 0);
  v6 = Allocate(CmpStatusPartsPassPar);
  _ctor(v6, 0);
  passPar = v6;
  wk->seqtype = -1;
  wk->player_tec = -1;
  wk->flags = 0;
  *(u64 *)&wk->callModelNo = -1;
  if (cmpGetSpriteHnd(0))
  {
    goto LABEL_15;
  }
  cmpLoadSpriteMem(0);
  wk->flags |= 6u;
LABEL_15:
  if (cmpGetSpriteHnd(2))
  {
    goto LABEL_17;
  }
  cmpLoadSpriteMem(2);
  wk->flags |= 0x18u;
LABEL_17:
  if (cmpGetSpriteHnd(1))
  {
    p_sSummnerRankMng = &wk->sSummnerRankMng;
    goto LABEL_19;
  }
  cmpLoadSpriteMem(1);
  wk->flags |= 0x60u;
  p_sSummnerRankMng = &wk->sSummnerRankMng;
LABEL_19:
  cmpSummnerRankMngInit(p_sSummnerRankMng);
  cmpLoadTitleEff();
  wk->sklType = 0;
  wk->sklType_r = 0;
  *(u16 *)&wk->lvlUp = 0;
  wk->root = 0;
  wk->noSklHelp = 0;
  wk->sceneOffFunc = 0;
  wk->counter = 0.0;
  *(u16 *)&wk->lightParNoDraw = 0;
  *(u16 *)&wk->noStatusDraw = 0;
  cmpCreateRankTextList();
  Unload(Dependent, "fld_all", 0);
}

// 0x20b78f0
void Shutdown(dds3ProcessID_t *PID) {
  tagCMP_STATUS_WORK *ProcessData;
  dds3ProcessID_t *p_drawPID;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  Release(ProcessData);
  p_drawPID = &ProcessData->drawPID;
  if (dds3ExistProcess(p_drawPID))
  {
    dds3KillProcess(p_drawPID, 0);
    p_drawPID = 0;
  }
  g_mainPID = 0;
}

// 0x20b7a60
dds3ProcessID_t *ProcessStart(void) {
  tagCMP_STATUS_WORK *v1;
  dds3ProcessFunc_t v2;
  shutdownfuncDelegate v3;
  dds3ProcessID_t *started;
  dds3ProcessFunc_t v7;
  dds3ProcessID_t *v8;

  v1 = Allocate(tagCMP_STATUS_WORK);
  _ctor(v1, 0);
  v2 = Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_cmpStatus_Process__, 0);
  v3 = Allocate(shutdownfuncDelegate);
  _ctor(v3, 0, Method_Project_cmpStatus_Shutdown__, 0);
  started = dds3StartProcess("camp_status_main", 1006, 0, 0, v2, v3, v1);
  g_mainPID = started;
  v7 = Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_cmpStatus_DrawProcess__, 0);
  v8 = dds3StartProcess("camp_status_draw", 11011, 0, 0, v7, 0, v1);
  v1->drawPID = v8;
  Init();
  return g_mainPID;
}

// 0x20b7c80
void ProcessEnd(bool _noGcClear) {
  Il2CppObject *ProcessData;
  Il2CppObject *v7;
  Il2CppObject *Instance;
  void *gameObject;
  Il2CppObject *v11;
  u64 monitor;

  if (!g_mainPID)
    return;
  if (!dds3ExistProcess(g_mainPID))
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  v7 = ProcessData;
  if (((s64)ProcessData[1].monitor & 1) == 0)
  {
    BYTE1(ProcessData[26].monitor) = noGcClear;
    Instance = _get_Instance();
    gameObject = get_gameObject(Instance, 0);
    if (get_activeSelf(gameObject, 0))
    {
      v11 = _get_Instance();
      CallEnd(v11, 0);
    }
    monitor = v7[1].monitor;
    LOWORD(v7[3].monitor) = 0;
    LOBYTE(v7[2].klass) = 0;
    v7[1].monitor = (monitor | 1);
    HIDWORD(v7[2].klass) = 3;
  }
}

// 0x20b7e90
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

// 0x20b8000
void cmpSetModeSq(s32 _sq) {
  Il2CppObject *ProcessData;
  Il2CppObject *v6;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  v6 = ProcessData;
  SE(SHIDWORD(ProcessData[12].monitor) > sq);
  HIDWORD(v6[12].monitor) = sq;
}

// 0x2098ab0
s32 cmpGetModeSq(void) {
  s32 *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return ProcessData[51];
  return ProcessData[51];
}

// 0x20b8150
void cmpDecideSuteSkl(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v6;
  s64 klass_high;
  s32 klass;
  sdatUnitWork_t *v11;

  if (!g_mainPID)
    return;
  if (!dds3ExistProcess(g_mainPID))
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  v6 = ProcessData;
  klass_high = SHIDWORD(ProcessData[14].klass);
  if ((u32)klass_high == -1)
  {
    LODWORD(ProcessData[14].monitor) = ProcessData[14].klass;
  }
  else
  {
    klass = v6[14].klass;
    LODWORD(v6[14].monitor) = *((u32 *)&v6[5].klass->rgctx_data[4].rgctxDataDummy + klass_high);
    cmpLearnSkl(klass, 1, klass_high, 0);
  }
  LODWORD(v6[14].klass) = 0;
  v11 = v6[5].klass;
  sBtlSetAutoSkill_GB(v11);
  sBtlCheckStockPara(v6[5].klass);
}

// 0x20b8380
bool cmpSlctSuteSkl(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v5;
  s32 klass_high;
  s32 v9;
  s32 v10;
  s32 v11;
  s32 v12;
  s32 v13;

  if (!g_mainPID)
    return 1;
  if (!dds3ExistProcess(g_mainPID))
    return 1;
  ProcessData = dds3GetProcessData(g_mainPID);
  v5 = ProcessData;
  if (CHECK_TRIG(4096, 1))
  {
    SE(0);
    return 1;
  }
  if (CHECK_TRIG(4100, 1))
  {
    klass_high = HIDWORD(v5[14].klass);
    if (klass_high == -1)
    {
      v10 = SLOWORD(v5[5].klass->_2.initializationExceptionGCHandle) - 2;
    }
    else
    {
      if (klass_high <= 1)
      {
        if (klass_high >= 0)
          v9 = HIDWORD(v5[14].klass) & 1;
        else
          v9 = -(HIDWORD(v5[14].klass) & 1);
        klass_high = v9 + SLOWORD(v5[5].klass->_2.initializationExceptionGCHandle);
      }
      v10 = klass_high - 2;
    }
    goto LABEL_51;
  }
  if (CHECK_TRIG(4101, 1))
  {
    v11 = HIDWORD(v5[14].klass);
    if (v11 != -1)
    {
      if (v11 >= SLOWORD(v5[5].klass->_2.initializationExceptionGCHandle) - 2)
      {
        if (v11 >= 0)
          v10 = HIDWORD(v5[14].klass) & 1;
        else
          v10 = -(HIDWORD(v5[14].klass) & 1);
      }
      else
      {
        v10 = v11 + 2;
      }
      goto LABEL_51;
    }
LABEL_46:
    v10 = 0;
LABEL_51:
    HIDWORD(v5[14].klass) = v10;
    SE(3);
    goto LABEL_52;
  }
  if (CHECK_TRIG(4102, 1))
  {
    v12 = HIDWORD(v5[14].klass);
    if (v12 == -1)
    {
      v10 = SLOWORD(v5[5].klass->_2.initializationExceptionGCHandle) > 1;
    }
    else if ((v12 & 1) != 0)
    {
      v10 = v12 - 1;
    }
    else
    {
      v10 = -1;
    }
    goto LABEL_51;
  }
  if (CHECK_TRIG(4103, 1))
  {
    v13 = HIDWORD(v5[14].klass);
    if (v13 != -1)
    {
      v10 = -1;
      if ((v13 & 0x80000001) != 1)
      {
        if (v13 == SLOWORD(v5[5].klass->_2.initializationExceptionGCHandle) - 1)
          v10 = -1;
        else
          v10 = v13 + 1;
      }
      goto LABEL_51;
    }
    goto LABEL_46;
  }
LABEL_52:
  rstResultResultGuideSet(8, 0, 90);
  return 0;
}

// 0x20b86d0
void cmpSuteKakuninMsg(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v5;
  s32 monitor;
  char *v8;

  if (!g_mainPID)
    return;
  if (!dds3ExistProcess(g_mainPID))
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  v5 = ProcessData;
  Reset(0);
  monitor = v5[14].monitor;
  v8 = sdatSkillName(monitor);
  fclSetMessageVar(0, v8);
  fclSetSelCancelPos(1);
  fclStart2(28, 1, 0);
  SetMessagePos(1u);
}

// 0x20b8900
void cmpOmoideModoshi(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v6;
  s64 klass_high;
  s32 monitor;
  sdatUnitWork_t *klass;

  if (!g_mainPID)
    return;
  if (!dds3ExistProcess(g_mainPID))
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  v6 = ProcessData;
  klass_high = SHIDWORD(ProcessData[14].klass);
  if ((u32)klass_high == -1)
  {
    LODWORD(ProcessData[14].klass) = ProcessData[14].monitor;
  }
  else
  {
    monitor = v6[14].monitor;
    LODWORD(v6[14].klass) = *((u32 *)&v6[5].klass->rgctx_data[4].rgctxDataDummy + klass_high);
    cmpLearnSkl(monitor, 1, klass_high, 0);
  }
  LODWORD(v6[14].monitor) = 0;
  klass = v6[5].klass;
  sBtlSetAutoSkill_GB(klass);
  sBtlCheckStockPara(v6[5].klass);
}

// 0x20b8b30
void cmpMemSklCurPrev(void) {
  Il2CppObject *ProcessData;
  u32 *monitor;
  u32 v7;
  s32 v8;
  s32 v9;
  s32 v10;
  s32 v11;

  if (!ProcessCheck())
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_15;
  goto LABEL_13;
  if (!ProcessData)
LABEL_13:
LABEL_15:
  monitor = ProcessData[19].monitor;
  v7 = monitor[4] & 0xFFFFFFFC;
  v8 = monitor[10];
  v9 = monitor[11];
  monitor[4] = v7;
  if (v9)
  {
    if ((s32)monitor[5] >= 2)
    {
      v10 = v9 - 1;
      monitor[4] = v7 | 1;
      v11 = v10 + v8;
LABEL_20:
      monitor[9] = v11;
      monitor[10] = v8;
      monitor[11] = v10;
      SE(3);
    }
  }
  else if (v8)
  {
    --v8;
    monitor[4] = v7 | 1;
    v10 = 0;
    v11 = v8;
    goto LABEL_20;
  }
}

// 0x20b8cd0
void cmpMemSklCurPrevLoop(void) {
  Il2CppObject *ProcessData;
  u32 *monitor;
  s32 v7;
  u32 v8;
  s32 v9;
  s32 v10;
  s32 v11;
  s32 v12;
  s32 v13;

  if (!ProcessCheck())
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_15;
  goto LABEL_13;
  if (!ProcessData)
LABEL_13:
LABEL_15:
  monitor = ProcessData[19].monitor;
  v7 = monitor[5];
  v8 = monitor[4] & 0xFFFFFFFC;
  v9 = monitor[10];
  v10 = monitor[11];
  monitor[4] = v8;
  if (v10)
  {
    if (v7 < 2)
      return;
    monitor[4] = v8 | 1;
    v11 = v10 - 1;
    v12 = v10 - 1 + v9;
LABEL_21:
    monitor[9] = v12;
    monitor[10] = v9;
    monitor[11] = v11;
    SE(3);
    return;
  }
  if (v9)
  {
    --v9;
    monitor[4] = v8 | 1;
    v11 = 0;
    v12 = v9;
    goto LABEL_21;
  }
  v13 = monitor[6];
  v12 = v7 - 1;
  v9 = v7 - v13;
  if (v7 > v13)
  {
    v11 = v13 - 1;
    monitor[4] = v8 | 1;
    goto LABEL_21;
  }
  if (v7 >= 2)
  {
    v9 = 0;
    monitor[4] = v8 | 1;
    v11 = v7 - 1;
    goto LABEL_21;
  }
}

// 0x20a3fb0
void cmpMemSklAutoCurNext(void) {
  Il2CppObject *ProcessData;
  u32 *monitor;
  s32 v7;
  s32 v8;
  u32 v9;
  s32 v10;
  s32 v11;
  s32 v12;
  s32 v13;
  s32 v14;
  s32 v16;

  if (!ProcessCheck())
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_15;
  goto LABEL_13;
  if (!ProcessData)
LABEL_13:
LABEL_15:
  monitor = ProcessData[19].monitor;
  v7 = monitor[5];
  v8 = monitor[6];
  v9 = monitor[4] & 0xFFFFFFFC;
  v11 = monitor[10];
  v10 = monitor[11];
  v12 = v7 - 1;
  monitor[4] = v9;
  if (v10 != v8 - 1)
  {
    if (v12 != v11 + v10)
    {
      if (v7 >= 2)
      {
        v16 = v10 + 1;
        monitor[4] = v9 | 1;
        monitor[9] = v16 + v11;
        monitor[10] = v11;
        monitor[11] = v16;
      }
      return;
    }
    if (v7 < 2)
      return;
LABEL_26:
    monitor[4] = v9 | 1;
    monitor[9] = 0;
    monitor[10] = 0;
    monitor[11] = 0;
    return;
  }
  if (v7 > v8 + v11)
  {
    v13 = v11 + 1;
    monitor[4] = v9 | 1;
    monitor[9] = v13 + v10;
    monitor[10] = v13;
    monitor[11] = v10;
    return;
  }
  v14 = v11 + v10;
  if (v7 >= 2 && v12 == v14)
    goto LABEL_26;
}

// 0x20b8eb0
void cmpMemSklCurNext(bool _noSe) {
  Il2CppObject *ProcessData;
  u32 *monitor;
  s32 v9;
  s32 v10;
  u32 v11;
  s32 v12;
  s32 v13;
  s32 v14;
  s32 v16;

  if (!ProcessCheck())
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_15;
  goto LABEL_13;
  if (!ProcessData)
LABEL_13:
LABEL_15:
  monitor = ProcessData[19].monitor;
  v9 = monitor[5];
  v10 = monitor[6];
  v11 = monitor[4] & 0xFFFFFFFC;
  v13 = monitor[10];
  v12 = monitor[11];
  monitor[4] = v11;
  if (v12 == v10 - 1)
  {
    if (v9 > v10 + v13)
    {
      v14 = v13 + 1;
      monitor[4] = v11 | 1;
      monitor[9] = v14 + v12;
      monitor[10] = v14;
      monitor[11] = v12;
      if (!noSe)
LABEL_25:
        SE(3);
    }
  }
  else if (v9 >= 2 && v9 - 1 != v13 + v12)
  {
    v16 = v12 + 1;
    monitor[4] = v11 | 1;
    monitor[9] = v16 + v13;
    monitor[10] = v13;
    monitor[11] = v16;
    if (!noSe)
      goto LABEL_25;
  }
}

// 0x20b9090
void cmpMemSklCurNextLoop(void) {
  Il2CppObject *ProcessData;
  u32 *monitor;
  s32 v7;
  s32 v8;
  u32 v9;
  s32 v10;
  s32 v11;
  s32 v12;
  s32 v13;
  s32 v14;

  if (!ProcessCheck())
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_15;
  goto LABEL_13;
  if (!ProcessData)
LABEL_13:
LABEL_15:
  monitor = ProcessData[19].monitor;
  v7 = monitor[5];
  v8 = monitor[6];
  v9 = monitor[4] & 0xFFFFFFFC;
  v11 = monitor[10];
  v10 = monitor[11];
  v12 = v7 - 1;
  monitor[4] = v9;
  if (v10 != v8 - 1)
  {
    if (v12 != v11 + v10)
    {
      if (v7 >= 2)
      {
        ++v10;
        monitor[4] = v9 | 1;
        v13 = v10 + v11;
        goto LABEL_30;
      }
      return;
    }
    if (v7 < 2)
      return;
LABEL_26:
    v11 = 0;
    monitor[4] = v9 | 1;
    v10 = 0;
    v13 = 0;
    goto LABEL_30;
  }
  if (v7 > v8 + v11)
  {
    ++v11;
    monitor[4] = v9 | 1;
    v13 = v11 + v10;
LABEL_30:
    monitor[9] = v13;
    monitor[10] = v11;
    monitor[11] = v10;
    SE(3);
    return;
  }
  v14 = v11 + v10;
  if (v7 >= 2 && v12 == v14)
    goto LABEL_26;
}

// 0x20b9280
void cmpMemSklCurPrevPage(void) {
  Il2CppObject *ProcessData;
  u32 *monitor;
  s32 v7;
  s32 v8;
  u32 v9;
  s32 v10;
  s32 v11;
  s32 v12;
  s32 v13;
  s32 v14;
  bool v17;

  if (!ProcessCheck())
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_15;
  goto LABEL_13;
  if (!ProcessData)
LABEL_13:
LABEL_15:
  monitor = ProcessData[19].monitor;
  v7 = monitor[5];
  v8 = monitor[6];
  v9 = monitor[4] & 0xFFFFFFFC;
  monitor[4] = v9;
  if (v7 > v8)
  {
    v10 = monitor[9];
    v11 = v10 - v8;
    v12 = monitor[10];
    if (v10 - v8 < 0 || (v13 = v12 - v8, v13 <= 0))
    {
      v13 = 0;
      v14 = 0;
      v11 = 0;
      if (v10)
        v17 = 0;
      else
        v17 = v12 == 0;
      if (!v17 || monitor[11] != 0)
        goto LABEL_34;
    }
    else
    {
      v14 = monitor[11];
      if (v10 != v11 || v12 != v13)
      {
LABEL_34:
        monitor[4] = v9 | 1;
        monitor[9] = v11;
        monitor[10] = v13;
        monitor[11] = v14;
        SE(3);
      }
    }
  }
}

// 0x20b9440
void cmpMemSklCurPrevPageLoop(void) {
  Il2CppObject *ProcessData;
  u32 *monitor;
  s32 v7;
  s32 v8;
  u32 v9;
  s32 v10;
  s32 v11;
  s32 v12;
  s32 v13;
  s32 v14;
  bool v17;

  if (!ProcessCheck())
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_15;
  goto LABEL_13;
  if (!ProcessData)
LABEL_13:
LABEL_15:
  monitor = ProcessData[19].monitor;
  v7 = monitor[5];
  v8 = monitor[6];
  v9 = monitor[4] & 0xFFFFFFFC;
  monitor[4] = v9;
  if (v7 > v8)
  {
    v10 = monitor[9];
    v11 = v10 - v8;
    v12 = monitor[10];
    if (v10 - v8 < 0 || (v13 = v12 - v8, v13 <= 0))
    {
      v13 = 0;
      v14 = 0;
      v11 = 0;
      if (v10)
        v17 = 0;
      else
        v17 = v12 == 0;
      if (!v17 || monitor[11] != 0)
        goto LABEL_34;
    }
    else
    {
      v14 = monitor[11];
      if (v10 != v11 || v12 != v13)
      {
LABEL_34:
        monitor[4] = v9 | 1;
        monitor[9] = v11;
        monitor[10] = v13;
        monitor[11] = v14;
        SE(3);
      }
    }
  }
}

// 0x20b9600
void cmpMemSklCurNextPage(void) {
  Il2CppObject *ProcessData;
  u32 *monitor;
  s32 v7;
  s32 v8;
  u32 v9;
  s32 v10;
  s32 v11;
  s32 v12;
  s32 v13;
  s32 v14;
  s32 v15;
  s32 v16;
  s32 v17;
  bool v18;
  s32 v19;
  s32 v20;

  if (!ProcessCheck())
    return;
  goto LABEL_9;
LABEL_13:
  goto LABEL_15;
LABEL_9:
  ProcessData = dds3GetProcessData(g_mainPID);
  if (ProcessData)
    goto LABEL_13;
LABEL_15:
  monitor = ProcessData[19].monitor;
  v7 = monitor[5];
  v8 = monitor[6];
  v9 = monitor[4] & 0xFFFFFFFC;
  v10 = v7 - v8;
  monitor[4] = v9;
  if (v7 > v8)
  {
    v11 = monitor[10];
    v12 = monitor[9];
    v13 = v8 - 1;
    v14 = v8 + v11;
    v15 = v8 + v12;
    if (v14 > v10)
      v16 = v10;
    else
      v16 = v14;
    if (v14 > v10)
      v17 = v13;
    else
      v17 = monitor[11];
    if (v14 > v10)
      v15 = v7 - 1;
    v18 = v14 < v7;
    if (v14 < v7)
    {
      v19 = v16;
    }
    else
    {
      v15 = v7 - 1;
      v19 = v10;
    }
    if (v18)
      v20 = v17;
    else
      v20 = v13;
    if (v12 != v15 || v11 != v19 || monitor[11] != v20)
    {
      monitor[4] = v9 | 1;
      monitor[9] = v15;
      monitor[10] = v19;
      monitor[11] = v20;
      SE(3);
    }
  }
}

// 0x20b97c0
void cmpMemSklCurNextPageLoop(void) {
  Il2CppObject *ProcessData;
  u32 *monitor;
  s32 v7;
  s32 v8;
  u32 v9;
  s32 v10;
  s32 v11;
  s32 v12;
  s32 v13;
  s32 v14;
  s32 v15;
  s32 v16;
  s32 v17;
  bool v18;
  s32 v19;
  s32 v20;

  if (!ProcessCheck())
    return;
  goto LABEL_9;
LABEL_13:
  goto LABEL_15;
LABEL_9:
  ProcessData = dds3GetProcessData(g_mainPID);
  if (ProcessData)
    goto LABEL_13;
LABEL_15:
  monitor = ProcessData[19].monitor;
  v7 = monitor[5];
  v8 = monitor[6];
  v9 = monitor[4] & 0xFFFFFFFC;
  v10 = v7 - v8;
  monitor[4] = v9;
  if (v7 > v8)
  {
    v11 = monitor[10];
    v12 = monitor[9];
    v13 = v8 - 1;
    v14 = v8 + v11;
    v15 = v8 + v12;
    if (v14 > v10)
      v16 = v10;
    else
      v16 = v14;
    if (v14 > v10)
      v17 = v13;
    else
      v17 = monitor[11];
    if (v14 > v10)
      v15 = v7 - 1;
    v18 = v14 < v7;
    if (v14 < v7)
    {
      v19 = v16;
    }
    else
    {
      v15 = v7 - 1;
      v19 = v10;
    }
    if (v18)
      v20 = v17;
    else
      v20 = v13;
    if (v12 != v15 || v11 != v19 || monitor[11] != v20)
    {
      monitor[4] = v9 | 1;
      monitor[9] = v15;
      monitor[10] = v19;
      monitor[11] = v20;
      SE(3);
    }
  }
}

// 0x20b9980
void cmpMemSklCurSelPage(void) {
  ;
}

// 0x20b9990
void cmpSetBtlSkl(s32 _index) {
  Il2CppObject *ProcessData;
  Il2CppObject *v7;
  Il2CppClass *klass;
  s16 name_high;
  sdatUnitWork_t *stock_id;
  Il2CppClass **v13;
  Il2CppClass *v15;
  s32 CsrSelSkl;
  s32 v18;
  Il2CppClass *v19;
  s64 v20;
  s32 v21;
  s32 *v22;
  s32 v23;
  s64 v24;
  s32 namespaze;

  if (!g_mainPID)
    return;
  if (!dds3ExistProcess(g_mainPID))
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  v7 = ProcessData;
  klass = ProcessData[5].klass;
  name_high = HIWORD(klass->_1.name);
  if (name_high && HIDWORD(ProcessData[15].monitor) != 8)
  {
    klass = v7[5].klass;
    name_high = HIWORD(klass->_1.name);
    stock_id = GBWK->player->stock_id;
    v13 = &stock_id->obj.klass + datGetStockDevilIndex(name_high, klass->_2.token);
    v15 = v13[4];
    if (cmpGetRsvCsr() == -1)
    {
      CsrSelSkl = cmpGetCsrSelSkl();
      if (CsrSelSkl)
      {
        v18 = CsrSelSkl;
        if (datCheckSkillType(v18) == 2)
        {
          v19 = v15->_1.klass;
          if (LODWORD(v19->_1.byval_arg.data))
          {
            if (HIDWORD(v19->_1.byval_arg.data))
            {
              v20 = (s64)v19 + 4 * index;
              v23 = *(u32 *)(v20 + 32);
              v22 = (v20 + 32);
              v21 = v23;
              if (v23 != v18)
              {
                *v22 = v18;
                v24 = 32;
                if (!index)
                  v24 = 36;
                namespaze = v19->_1.namespaze;
                *(u32 *)((char *)&v19->_1.image + v24) = v21;
                Copy_56180528(v19, v7[5].klass->_1.klass, namespaze, 0);
              }
            }
          }
        }
      }
    }
  }
}

// 0x209a530
bool cmpOpenOmoedeLog(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return (char)ProcessData;
  if (HIWORD(ProcessData[5].klass->_1.name))
    LOBYTE(ProcessData) = LODWORD(ProcessData[13].klass) == 1;
  else
    LOBYTE(ProcessData) = HIDWORD(ProcessData[21].monitor) == 1;
  return (char)ProcessData;
}

// 0x20b9d60
void cmpSetChuuseiMax(void) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  klass = ProcessData[5].klass;
  if (HIWORD(klass->_1.name))
    LOBYTE(klass->_2.cctor_thread) = 1;
}

// 0x20b9e80
void cmpSetOmoideLearned(s32 idx) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  klass = ProcessData[5].klass;
}

// 0x20b9fc0
void cmpSummnerRankStart(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  *((u8 *)ProcessData[17].klass->_1.namespaze + 16) = 1;
}

// 0x20ba0f0
bool cmpSummnerRankWait(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return (char)ProcessData;
  LOBYTE(ProcessData) = *((u8 *)ProcessData[17].klass->_1.namespaze + 17) != 0;
  return (char)ProcessData;
}

// 0x20ba220
void cmpRaidoFlushStart(void) {
  SetPara(MultiBlur, 0.0, 1.0, ADD, 0);
  _SetRGBA(MultiBlur, 0);
  SetArea(MultiBlur, 320, 128, -107, 0);
  _On(MultiBlur, 0);
  s_cmpRaidoFlushCntf = 3.0;
}

// 0x20ba380
s32 cmpRaidoFlushEndCheck(void) {
  f32 v4;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v22;
  f32 v23;
  u32 v26;

  if (s_cmpRaidoFlushCntf < 6.9)
  {
    v4 = s_cmpRaidoFlushCntf;
    v4 = s_cmpRaidoFlushCntf;
    s_cmpRaidoFlushCntf = v4 + 0.1;
    if (s_cmpRaidoFlushCntf >= 4.1 && s_cmpRaidoFlushCntf < 4.21)
    {
      dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 0xCu);
    }
    if (s_cmpRaidoFlushCntf >= 5.0 && s_cmpRaidoFlushCntf < 5.11)
    {
      dds3FadeIn2(8u);
    }
    if (s_cmpRaidoFlushCntf >= 3.5 && s_cmpRaidoFlushCntf < 3.61)
      SE(16);
    v8 = -1.0;
    v9 = (s32)(s_cmpRaidoFlushCntf * 0.15915494);
    if ((f32)(s_cmpRaidoFlushCntf * 0.15915494) == INFINITY)
      v9 = -2147500000.0;
    v10 = (f32)(s_cmpRaidoFlushCntf * 0.15915494) - v9;
    if (v10 <= 0.5)
    {
      v11 = (f32)(s_cmpRaidoFlushCntf * 0.15915494) - v9;
      if (v10 < -0.5)
        v11 = v10 + 1.0;
    }
    else
    {
      v11 = v10 + -1.0;
    }
    v14 = -0.5 - v11;
    if (v11 >= -0.25)
      v14 = v11;
    if (v11 > 0.25)
      v15 = 0.5 - v11;
    else
      v15 = v14;
    v16 = v15 * 4.0;
    v17 = v16 * v16;
    v18 = (f32)((f32)((f32)((f32)(v16 * 1.5707963) + (f32)((f32)(v16 * (f32)(v16 * v16)) * -0.6459637)) + (f32)((f32)((f32)(v16 * v16) * (f32)(v16 * (f32)(v16 * v16))) * 0.07968968)) + (f32)((f32)(v17 * (f32)(v17 * (f32)(v16 * (f32)(v16 * v16)))) * -0.0046737655))
        + (f32)((f32)(v17 * (f32)(v17 * (f32)(v17 * (f32)(v16 * (f32)(v16 * v16))))) * 0.00015148419);
    if (v10 <= 0.5)
    {
      if (v10 >= -0.5)
      {
LABEL_48:
        if (v10 <= 0.25)
        {
          if (v10 < -0.25)
            v10 = -0.5 - v10;
        }
        else
        {
          v10 = 0.5 - v10;
        }
        v19 = v10 * 4.0;
        v20 = (f32)(v18 * 0.04) + 0.04;
        v22 = (f32)((f32)((f32)((f32)((f32)(v19 * 1.5707963) + (f32)((f32)(v19 * (f32)(v19 * v19)) * -0.6459637)) + (f32)((f32)((f32)(v19 * v19) * (f32)(v19 * (f32)(v19 * v19))) * 0.07968968)) + (f32)((f32)((f32)(v19 * v19) * (f32)((f32)(v19 * v19) * (f32)(v19 * (f32)(v19 * v19)))) * -0.0046737655)) + (f32)((f32)((f32)(v19 * v19) * (f32)((f32)(v19 * v19) * (f32)((f32)(v19 * v19) * (f32)(v19 * (f32)(v19 * v19))))) * 0.00015148419))
            * -64.0;
        v23 = v20 + 0.92;
        SetPara(MultiBlur, (f32)((f32)(s_cmpRaidoFlushCntf + -3.0) / 50.0) + 0.0, v23, ADD, 0);
        if (v22 == INFINITY)
          v26 = 1086374080;
        else
          v26 = ((s32)v22 << 24) + 1086374080;
        _SetRGBA(MultiBlur, v26);
        _Swap(MultiBlur, 0);
        return 0;
      }
      v8 = 1.0;
    }
    v10 = v10 + v8;
    goto LABEL_48;
  }
  _Off(MultiBlur, 0);
  return 1;
}

// 0x20a1ba0
bool cmpMemSet(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  s32 SelectMemSklID;
  s32 v7;
  s32 v9;
  sdatUnitWork_t *klass;
  Il2CppRGCTXData *rgctx_data;
  s32 monitor_high;
  s32 v14;
  s32 v15;
  s32 v17;
  sdatPlayerUnitWork_t *player;
  s32 v21;
  SKLID *spiritSkill;
  const char *namespaze;
  RankText *SetRank;
  s32 sprNo;
  s32 v36;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  if (HIWORD(ProcessData[5].klass->_1.name))
  {
    SelectMemSklID = cmpCurGetSelectMemSklID();
    if (!SelectMemSklID)
      return 0;
    v9 = SelectMemSklID;
    klass = v4[5].klass;
    if (datOmoideSkillGetMaster(v4[5].klass, SelectMemSklID))
    {
      rgctx_data = v4[5].klass->rgctx_data;
      if (LODWORD(rgctx_data[4].rgctxDataDummy) == v9 || HIDWORD(rgctx_data[4].klass) == v9 || LODWORD(rgctx_data[5].rgctxDataDummy) == v9 || HIDWORD(rgctx_data[5].klass) == v9 || LODWORD(rgctx_data[6].rgctxDataDummy) == v9 || HIDWORD(rgctx_data[6].klass) == v9 || LODWORD(rgctx_data[7].rgctxDataDummy) == v9 || HIDWORD(rgctx_data[7].klass) == v9)
      {
        return 0;
      }
      monitor_high = HIDWORD(v4[15].monitor);
      v14 = v9;
      v15 = monitor_high;
      goto LABEL_112;
    }
    return 1;
  }
  if (!HIDWORD(ProcessData[21].monitor))
  {
    v17 = _get_Item(ProcessData[23].klass, *((u32 *)ProcessData[19].monitor + 9))[2].klass;
    player = GBWK->player;
    if (v17 == player->syougou)
      goto LABEL_55;
    player = GBWK->player;
    if (!player->setSyougou)
    {
      player = GBWK->player;
LABEL_66:
      player->setSyougou = 1;
      goto LABEL_93;
    }
LABEL_55:
    player = GBWK->player;
    if (player->setSyougou)
    {
      if (player->syougou == v17)
      {
        player = GBWK->player;
        GBWK->syougouRemove = v17;
        player->setSyougou = 0;
        goto LABEL_93;
      }
LABEL_93:
      namespaze = v4[17].klass->_1.namespaze;
      GBWK->player->syougou = v17;
      SetRank = cmpGetSetRank(-1);
      if (SetRank)
      {
        sprNo = SetRank->sprNo;
LABEL_106:
        *(u32 *)(*((u64 *)namespaze + 6) + 32) = sprNo;
        *(u32 *)(*((u64 *)namespaze + 9) + 32) = sprNo;
        return 1;
      }
      sprNo = 0;
      goto LABEL_106;
    }
    goto LABEL_66;
  }
  v7 = cmpCurGetSelectMemSklID();
  if (!v7)
    return 0;
  v21 = v7;
  if (!datSpiritSkillGetMaster(GBWK->player, v21))
    return 1;
  spiritSkill = GBWK->player->spiritSkill;
  if (spiritSkill[0] == v21 || spiritSkill[1] == v21 || spiritSkill[2] == v21 || spiritSkill[3] == v21 || spiritSkill[4] == v21 || spiritSkill[5] == v21 || spiritSkill[6] == v21)
  {
    return 0;
  }
  if (spiritSkill[7] == v21)
    return 0;
  v15 = HIDWORD(v4[15].monitor);
  v36 = HIDWORD(v4[15].monitor);
  v15 = v36;
  v14 = v21;
LABEL_112:
  cmpLearnSkl(v14, 1, v15, 0);
  return 1;
}

// 0x20ba840
void cmpInitModeSq(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  if (HIWORD(ProcessData[5].klass->_1.name))
    HIDWORD(ProcessData[12].monitor) = 0;
}

// 0x20ba960
bool cmpOmoideSkillIsFinish(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return 1;
  return LOBYTE(ProcessData[2].klass) != 1;
}

// 0x20a0e20
void cmpSetEvent(CMP_STATUS_EVENT eEvent) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  HIDWORD(ProcessData[18].monitor) = eEvent;
}

// 0x209a7b0
void cmpMemSklCurUpdate(void) {
  if (CHECK_TRIG(4102, 1))
  {
    cmpMemSklCurPrevPageLoop();
  }
  else if (CHECK_REP(43526, 1))
  {
    cmpMemSklCurPrevPage();
  }
  else if (CHECK_TRIG(43527, 1))
  {
    cmpMemSklCurNextPageLoop();
  }
  else if (CHECK_REP(4103, 1))
  {
    cmpMemSklCurNextPage();
  }
  else if (CHECK_TRIG(4100, 1))
  {
    cmpMemSklCurPrevLoop();
  }
  else if (CHECK_REP(4100, 1))
  {
    cmpMemSklCurPrev();
  }
  else if (CHECK_TRIG(4101, 1))
  {
    cmpMemSklCurNextLoop();
  }
  else if (CHECK_REP(4101, 1))
  {
    cmpMemSklCurNext(0);
  }
}

// 0x209a680
void cmpDecModeSq(bool _noSe) {
  Il2CppObject *ProcessData;
  Il2CppObject *v6;
  s32 monitor_high;

  ProcessData = dds3GetProcessData(g_mainPID);
  v6 = ProcessData;
  monitor_high = HIDWORD(ProcessData[12].monitor);
  if (monitor_high >= 1)
  {
    if (!noSe)
    {
      SE(1);
      monitor_high = HIDWORD(v6[12].monitor);
    }
    HIDWORD(v6[12].monitor) = monitor_high - 1;
  }
}

// 0x20baa90
bool cmpCheckSklSet(void) {
  Il2CppObject *ProcessData;

  if (!g_mainPID)
    return 0;
  if (!dds3ExistProcess(g_mainPID))
    return 0;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return SHIDWORD(ProcessData[15].monitor) > 0;
  return SHIDWORD(ProcessData[15].monitor) > 0;
}

// 0x20bac50
s32 cmpRNextRsvCsr(tagCMP_STATUS_WORK *wk, s32 _csrNo) {
  sdatUnitWork_t *unit;
  s32 v6;
  s32 v7;
  sdatUnitWork_t *v8;
  s32 sklType;
  s32 result;
  sdatUnitWork_t *v11;
  s32 v12;
  s32 v13;
  sdatUnitWork_t *v14;
  s32 v15;
  s32 v16;

  unit = wk->unit;
  v6 = datCheckRsvSkillCnt(unit);
  v7 = 0;
  switch (wk->sklCsr)
  {
    case 0:
      v8 = wk->unit;
      sklType = wk->sklType;
      if (cmpGetSklCsrMax(v8, sklType) == 1)
        v7 = 0;
      else
        v7 = -1;
      goto LABEL_11;
    case 1:
LABEL_11:
      if (v7 >= v6)
        result = -1;
      else
        result = v7;
      break;
    case 2:
      v11 = wk->unit;
      v12 = wk->sklType;
      if (cmpGetSklCsrMax(v11, v12) == 3)
        v13 = 1;
      else
        v13 = -1;
      if (v13 >= v6)
        result = -1;
      else
        result = v13;
      break;
    case 3:
      if (v6 <= 1)
        result = -1;
      else
        result = 1;
      break;
    case 4:
      v14 = wk->unit;
      v15 = wk->sklType;
      if (cmpGetSklCsrMax(v14, v15) == 5)
        v16 = 2;
      else
        v16 = -1;
      if (v16 >= v6)
        result = -1;
      else
        result = v16;
      break;
    case 5:
      if (v6 <= 2)
        result = -1;
      else
        result = 2;
      break;
    default:
      result = -1;
      break;
  }
  return result;
}

// 0x20bae30
s32 cmpLNextRsvCsr(tagCMP_STATUS_WORK *wk, s32 _csrNo) {
  sdatUnitWork_t *unit;
  s32 v5;
  u32 v6;
  s32 v7;

  unit = wk->unit;
  v5 = datCheckRsvSkillCnt(unit);
  v6 = wk->sklCsr - 2;
  if (v6 > 4)
    return -1;
  v7 = dword_3E64790[v6];
  if (v7 >= v5)
    return -1;
  else
    return v7;
}

// 0x20baee0
s32 cmpLNextNmlCsr(tagCMP_STATUS_WORK *wk) {
  sdatUnitWork_t *unit;
  s32 sklType;
  s32 SklCsrMax;
  s32 rsvCsr;
  s32 v11;

  unit = wk->unit;
  sklType = wk->sklType;
  SklCsrMax = cmpGetSklCsrMax(unit, sklType);
  if (SklCsrMax == 1)
  {
    rsvCsr = wk->rsvCsr;
    if (!rsvCsr)
      return 0;
    goto LABEL_15;
  }
  if (SklCsrMax == 3)
  {
    rsvCsr = wk->rsvCsr;
    if (rsvCsr == 1)
      return 2;
  }
  else if (SklCsrMax == 5)
  {
    rsvCsr = wk->rsvCsr;
    if (rsvCsr == 2)
      return 4;
  }
  else
  {
    rsvCsr = wk->rsvCsr;
  }
LABEL_15:
  if (rsvCsr)
    v11 = rsvCsr + 2;
  else
    v11 = 1;
  if (SklCsrMax > v11)
    return 0;
  else
    return -1;
}

// 0x2099870
void cmpSklCsrL(void) {
  Il2CppObject *ProcessData;
  tagCMP_STATUS_WORK *v7;
  s32 monitor_high;
  bool v10;
  s32 klass;
  sdatUnitWork_t *unit;
  s32 sklType;
  s32 SklCsrMax;
  s32 rsvCsr;
  s32 sklCsr;
  s32 v20;
  s32 v21;
  s32 v23;
  s32 v24;
  bool v25;
  s32 v26;
  sdatUnitWork_t *v27;
  s32 v28;
  s32 v29;
  char v30;
  s32 v31;

  if (!g_mainPID)
    return;
  if (!dds3ExistProcess(g_mainPID))
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  v7 = ProcessData;
  monitor_high = HIDWORD(ProcessData[15].monitor);
  if (!HIWORD(ProcessData[5].klass->_1.name) || LODWORD(ProcessData[13].klass))
  {
    if (monitor_high - 1 >= 0)
    {
      HIDWORD(ProcessData[15].monitor) = monitor_high - 1;
LABEL_70:
      SE(3);
      return;
    }
    v10 = 0;
    goto LABEL_66;
  }
  klass = ProcessData[21].klass;
  if (klass != -1)
  {
    unit = v7->unit;
    sklType = v7->sklType;
    SklCsrMax = cmpGetSklCsrMax(unit, sklType);
    if (SklCsrMax != 1)
    {
      if (SklCsrMax == 3)
      {
        rsvCsr = v7->rsvCsr;
        if (rsvCsr == 1)
        {
          sklCsr = 2;
          goto LABEL_57;
        }
      }
      else if (SklCsrMax == 5)
      {
        rsvCsr = v7->rsvCsr;
        if (rsvCsr == 2)
        {
          sklCsr = 4;
LABEL_57:
          v7->sklCsr = sklCsr;
LABEL_63:
          v7->rsvCsr = -1;
LABEL_64:
          v23 = sklCsr;
          goto LABEL_65;
        }
      }
      else
      {
        rsvCsr = v7->rsvCsr;
      }
      goto LABEL_47;
    }
    rsvCsr = v7->rsvCsr;
    if (!rsvCsr)
    {
      v23 = 2;
      goto LABEL_54;
    }
LABEL_47:
    v24 = rsvCsr + 2;
    v25 = rsvCsr == 0;
    v26 = rsvCsr + 3;
    if (v25)
      v24 = 1;
    if (v25)
      v23 = 2;
    else
      v23 = v26;
    if (SklCsrMax <= v24)
    {
      v30 = 1;
      goto LABEL_59;
    }
LABEL_54:
    v27 = v7->unit;
    v28 = v7->sklType;
    v29 = cmpGetSklCsrMax(v27, v28);
    v30 = 0;
    sklCsr = 0;
    if (v29 == 1)
      goto LABEL_57;
LABEL_59:
    sklCsr = v7->sklCsr;
    if (v23 == sklCsr)
    {
      sklCsr = v23 - 1;
      if (v23 - 1 < 0)
        goto LABEL_65;
      v7->sklCsr = sklCsr;
    }
    v23 = sklCsr;
    if ((v30 & 1) != 0)
    {
LABEL_65:
      v10 = klass != v7->rsvCsr;
      if (monitor_high != v23)
        goto LABEL_70;
      goto LABEL_66;
    }
    goto LABEL_63;
  }
  v20 = cmpLNextRsvCsr(v7, (s32)tagCMP_STATUS_WORK);
  if (v20 == -1)
  {
    sklCsr = v7->sklCsr;
    v31 = sklCsr - 1;
    if (sklCsr - 1 < 0)
      goto LABEL_64;
    v7->sklCsr = v31;
    v10 = v7->rsvCsr != -1;
    if (monitor_high != v31)
      goto LABEL_70;
  }
  else
  {
    v21 = v7->sklCsr;
    v7->rsvCsr = v20;
    v10 = v20 != -1;
    if (monitor_high != v21)
      goto LABEL_70;
  }
LABEL_66:
  if (v10)
    goto LABEL_70;
}

// 0x2099c50
void cmpSklCsrR(void) {
  Il2CppObject *ProcessData;
  tagCMP_STATUS_WORK *v7;
  sdatUnitWork_t *klass;
  s32 monitor_high;
  s32 v11;
  s32 SklCsrMax;
  s32 sklCsr;
  _BOOL4 v14;
  s32 v15;
  s32 v16;
  s32 SklCsrMax_R;
  s32 v18;
  s32 v19;
  s32 v21;
  s32 v25;
  s32 v26;
  s32 v27;
  sdatUnitWork_t *unit;
  s32 sklType;
  s32 v30;

  if (!g_mainPID)
    return;
  if (!dds3ExistProcess(g_mainPID))
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  v7 = ProcessData;
  klass = ProcessData[5].klass;
  monitor_high = HIDWORD(ProcessData[15].monitor);
  if (!klass->devilid)
  {
    v16 = HIDWORD(ProcessData[21].monitor);
    SklCsrMax_R = cmpGetSklCsrMax_R(cmpStatus, v16);
    sklCsr = v7->sklCsr;
    if (monitor_high + 1 < SklCsrMax_R)
      goto LABEL_23;
    goto LABEL_29;
  }
  v11 = ProcessData[13].klass;
  if (v11)
  {
    SklCsrMax = cmpGetSklCsrMax(klass, v11);
    sklCsr = v7->sklCsr;
    if (monitor_high + 1 < SklCsrMax)
    {
LABEL_23:
      v14 = 0;
      v15 = sklCsr + 1;
      v7->sklCsr = v15;
      if (monitor_high != v15)
        goto LABEL_50;
      goto LABEL_48;
    }
LABEL_29:
    v14 = 0;
    if (monitor_high != sklCsr)
      goto LABEL_50;
    goto LABEL_48;
  }
  v18 = ProcessData[21].klass;
  if (v18)
  {
    if (v18 == -1)
    {
      v19 = cmpRNextRsvCsr(v7, (s32)tagCMP_STATUS_WORK);
      if (v19 == -1)
      {
        v27 = v7->sklCsr;
        unit = v7->unit;
        sklType = v7->sklType;
        v30 = cmpGetSklCsrMax(unit, sklType);
        v21 = v7->sklCsr;
        if (v27 + 1 < v30)
          v7->sklCsr = ++v21;
      }
      else
      {
        v21 = v7->sklCsr;
        v7->rsvCsr = v19;
      }
      goto LABEL_47;
    }
    v25 = v18 + 3;
  }
  else
  {
    v25 = 2;
  }
  v26 = cmpGetSklCsrMax(klass, 0);
  v21 = v7->sklCsr;
  if (v25 < v26)
  {
    if (v21 < v25)
      v7->sklCsr = ++v21;
    v7->rsvCsr = -1;
  }
LABEL_47:
  v14 = v18 != v7->rsvCsr;
  if (monitor_high != v21)
  {
LABEL_50:
    SE(3);
    return;
  }
LABEL_48:
  if (v14)
    goto LABEL_50;
}

// 0x20991e0
void cmpSklCsrU(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v5;
  sdatUnitWork_t *klass;
  s32 monitor_high;
  bool v9;
  s32 v10;
  s32 v12;
  sdatUnitWork_t *v13;
  s32 v14;
  s32 SklCsrMax;
  sdatUnitWork_t *v16;
  s32 v17;
  s32 v18;
  s32 v19;
  s32 v20;

  if (!g_mainPID)
    return;
  if (!dds3ExistProcess(g_mainPID))
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  v5 = ProcessData;
  klass = ProcessData[5].klass;
  monitor_high = HIDWORD(ProcessData[15].monitor);
  if (!klass->devilid || LODWORD(ProcessData[13].klass))
  {
    if (monitor_high - 2 >= 0)
    {
      HIDWORD(ProcessData[15].monitor) = monitor_high - 2;
LABEL_50:
      SE(3);
      return;
    }
    v9 = 0;
    goto LABEL_48;
  }
  v10 = ProcessData[21].klass;
  datCheckRsvSkillCnt(klass);
  v12 = v5[21].klass;
  if (v12 == -1)
  {
    v19 = HIDWORD(v5[15].monitor) - 2;
    if (v19 >= 0)
      HIDWORD(v5[15].monitor) = v19;
    v12 = -1;
    goto LABEL_47;
  }
  if (v12 - 1 < 0)
    goto LABEL_47;
  if (v12 == 1)
  {
    v13 = v5[5].klass;
    v14 = v5[13].klass;
    SklCsrMax = cmpGetSklCsrMax(v13, v14);
    v12 = v5[21].klass;
    if (SklCsrMax > 3)
    {
      LODWORD(v5[21].klass) = --v12;
LABEL_44:
      v20 = HIDWORD(v5[15].monitor) - 2;
      if (v20 < 0)
        HIDWORD(v5[15].monitor) = 0;
      else
        HIDWORD(v5[15].monitor) = v20;
      goto LABEL_47;
    }
  }
  if (v12 != 2)
  {
    LODWORD(v5[21].klass) = --v12;
    goto LABEL_47;
  }
  v16 = v5[5].klass;
  v17 = v5[13].klass;
  v18 = cmpGetSklCsrMax(v16, v17);
  v12 = LODWORD(v5[21].klass) - 1;
  LODWORD(v5[21].klass) = v12;
  if (v18 >= 6)
    goto LABEL_44;
LABEL_47:
  v9 = v10 != v12;
  if (monitor_high != HIDWORD(v5[15].monitor))
    goto LABEL_50;
LABEL_48:
  if (v9)
    goto LABEL_50;
}

// 0x20994f0
void cmpSklCsrD(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v6;
  sdatUnitWork_t *klass;
  s32 monitor_high;
  s32 v10;
  s32 SklCsrMax;
  s32 v12;
  _BOOL4 v13;
  s32 v14;
  s32 v15;
  s32 SklCsrMax_R;
  s32 v17;
  s32 v18;
  s32 v20;
  s32 v21;
  s32 v22;
  sdatUnitWork_t *v24;
  s32 v25;
  s32 v30;
  sdatUnitWork_t *v31;
  s32 v32;
  s32 v33;
  s32 v34;
  sdatUnitWork_t *v35;
  s32 v36;

  if (!g_mainPID)
    return;
  if (!dds3ExistProcess(g_mainPID))
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  v6 = ProcessData;
  klass = ProcessData[5].klass;
  monitor_high = HIDWORD(ProcessData[15].monitor);
  if (!klass->devilid)
  {
    v15 = HIDWORD(ProcessData[21].monitor);
    SklCsrMax_R = cmpGetSklCsrMax_R(cmpStatus, v15);
    v12 = HIDWORD(v6[15].monitor);
    if (monitor_high + 2 < SklCsrMax_R)
      goto LABEL_23;
    goto LABEL_29;
  }
  v10 = ProcessData[13].klass;
  if (v10)
  {
    SklCsrMax = cmpGetSklCsrMax(klass, v10);
    v12 = HIDWORD(v6[15].monitor);
    if (monitor_high + 2 < SklCsrMax)
    {
LABEL_23:
      v13 = 0;
      v14 = v12 + 2;
      HIDWORD(v6[15].monitor) = v14;
      if (monitor_high != v14)
        goto LABEL_52;
      goto LABEL_50;
    }
LABEL_29:
    v13 = 0;
    if (monitor_high != v12)
      goto LABEL_52;
    goto LABEL_50;
  }
  v17 = ProcessData[21].klass;
  v18 = datCheckRsvSkillCnt(klass);
  v20 = v6[21].klass;
  if (v20 != -1)
  {
    v21 = HIDWORD(v6[15].monitor);
    v22 = v20 + 1;
    if (v22 >= v18)
      goto LABEL_49;
    LODWORD(v6[21].klass) = v22;
    v24 = v6[5].klass;
    v25 = v6[13].klass;
    if (v21 + 2 >= cmpGetSklCsrMax(v24, v25))
    {
      v35 = v6[5].klass;
      v36 = v6[13].klass;
      v21 = cmpGetSklCsrMax(v35, v36) - 1;
    }
    else
    {
      v21 = HIDWORD(v6[15].monitor) + 2;
    }
    goto LABEL_48;
  }
  v30 = HIDWORD(v6[15].monitor);
  v31 = v6[5].klass;
  v32 = v6[13].klass;
  v33 = cmpGetSklCsrMax(v31, v32);
  v34 = v30 + 2;
  v21 = HIDWORD(v6[15].monitor);
  if (v34 < v33)
  {
    v21 += 2;
LABEL_48:
    HIDWORD(v6[15].monitor) = v21;
  }
LABEL_49:
  v13 = v17 != LODWORD(v6[21].klass);
  if (monitor_high != v21)
  {
LABEL_52:
    SE(3);
    return;
  }
LABEL_50:
  if (v13)
    goto LABEL_52;
}

// 0x20991d0
void cmpSklCsrMouse(bool _item) {
  ;
}

// 0x2099090
void cmpIncModeSq(bool _noSe) {
  Il2CppObject *ProcessData;
  Il2CppObject *v6;
  s32 monitor_high;

  ProcessData = dds3GetProcessData(g_mainPID);
  v6 = ProcessData;
  if (HIDWORD(ProcessData[2].monitor) != 2)
  {
    monitor_high = HIDWORD(ProcessData[12].monitor);
    if (monitor_high <= 1)
    {
      if (!noSe)
      {
        SE(0);
        monitor_high = HIDWORD(v6[12].monitor);
      }
      HIDWORD(v6[12].monitor) = monitor_high + 1;
    }
  }
}

// 0x2098e30
void cmpSklTypeAdd(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v5;
  s32 name_high;
  Il2CppObject *Instance;
  s64 v9;
  s32 klass;
  s32 v11;
  s32 monitor_high;
  s32 v13;

  if (!g_mainPID)
    return;
  if (!dds3ExistProcess(g_mainPID))
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  v5 = ProcessData;
  name_high = HIWORD(ProcessData[5].klass->_1.name);
  Instance = _get_Instance();
  v9 = 10;
  if (!name_high)
    v9 = 8;
  (*(Instance[v9].klass->_1.image + 61))(Instance[v9].klass, *((u64 *)Instance[v9].klass->_1.image + 62));
  if (HIWORD(v5[5].klass->_1.name))
  {
    klass = v5[13].klass;
    HIDWORD(v5[15].monitor) = 0;
    LODWORD(v5[15].klass) = 255;
    if (klass + 1 < 3)
      v11 = klass + 1;
    else
      v11 = 0;
    LODWORD(v5[13].klass) = v11;
    LODWORD(v5[21].klass) = -1;
    LODWORD(v5[21].monitor) = 0;
    SE(24);
  }
  else if (HIDWORD(v5[12].monitor) != 1)
  {
    monitor_high = HIDWORD(v5[21].monitor);
    LODWORD(v5[15].klass) = 255;
    HIDWORD(v5[15].monitor) = 0;
    v5[21].klass = 0xFFFFFFFFLL;
    if (monitor_high + 1 < 2)
      v13 = monitor_high + 1;
    else
      v13 = 0;
    HIDWORD(v5[21].monitor) = v13;
    LODWORD(v5[21].monitor) = 0;
    SE(24);
  }
}

// 0x2098bd0
void cmpSklTypeSub(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v5;
  s32 name_high;
  Il2CppObject *Instance;
  s64 v9;
  s32 klass;
  s32 v11;
  s32 monitor_high;
  s32 v13;

  if (!g_mainPID)
    return;
  if (!dds3ExistProcess(g_mainPID))
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  v5 = ProcessData;
  name_high = HIWORD(ProcessData[5].klass->_1.name);
  Instance = _get_Instance();
  v9 = 10;
  if (!name_high)
    v9 = 8;
  (*(Instance[v9].klass->_1.image + 61))(Instance[v9].klass, *((u64 *)Instance[v9].klass->_1.image + 62));
  if (HIWORD(v5[5].klass->_1.name))
  {
    klass = v5[13].klass;
    HIDWORD(v5[15].monitor) = 0;
    HIDWORD(v5[14].monitor) = 255;
    v11 = klass - 1;
    if (v11 < 0)
      v11 = 2;
    LODWORD(v5[13].klass) = v11;
    LODWORD(v5[21].klass) = -1;
    LODWORD(v5[21].monitor) = 0;
    SE(24);
  }
  else if (HIDWORD(v5[12].monitor) != 1)
  {
    monitor_high = HIDWORD(v5[21].monitor);
    HIDWORD(v5[14].monitor) = 255;
    HIDWORD(v5[15].monitor) = 0;
    v13 = monitor_high - 1;
    v5[21].klass = 0xFFFFFFFFLL;
    if (v13 < 0)
      v13 = 1;
    HIDWORD(v5[21].monitor) = v13;
    LODWORD(v5[21].monitor) = 0;
    SE(24);
  }
}

// 0x20bb010
void cmpSklTypeSet(s32 sklType, bool _csrClear) {
  Il2CppObject *ProcessData;
  Il2CppObject *v9;
  s32 name_high;
  Il2CppObject *Instance;
  bool v14;
  Il2CppClass *klass;
  bool v16;

  if (!g_mainPID)
    return;
  if (!dds3ExistProcess(g_mainPID))
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  v9 = ProcessData;
  name_high = HIWORD(ProcessData[5].klass->_1.name);
  Instance = _get_Instance();
  if (name_high)
  {
    v14 = op_Inequality(Instance, 0, 0);
    klass = 0;
    if (v14)
      klass = _get_Instance()[10].klass;
    LODWORD(v9[13].klass) = sklType;
    if (!csrClear)
      goto LABEL_34;
    HIDWORD(v9[15].monitor) = 0;
    HIDWORD(v9[14].monitor) = 255;
    LODWORD(v9[21].klass) = -1;
  }
  else
  {
    v16 = op_Inequality(Instance, 0, 0);
    klass = 0;
    if (v16)
      klass = _get_Instance()[8].klass;
    HIDWORD(v9[21].monitor) = sklType;
    if (!csrClear)
      goto LABEL_34;
    HIDWORD(v9[15].monitor) = 0;
    HIDWORD(v9[14].monitor) = 255;
    v9[21].klass = 0xFFFFFFFFLL;
  }
  LODWORD(v9[21].monitor) = 0;
LABEL_34:
  if (klass)
    (*(klass->_1.image + 61))(klass, *((u64 *)klass->_1.image + 62));
}

// 0x2098bc0
void cmpMouseSetSklType(void) {
  ;
}

// 0x20bb2b0
void cmpSetLightUpSkl(s32 idx, bool b) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  *((u8 *)&ProcessData[16].klass->_1.byval_arg.data + idx) = b;
}

// 0x20bb3e0
void cmpUDHelpNon(bool b) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  BYTE5(ProcessData[16].monitor) = b;
}

// 0x20bb500
bool cmpCheckStepGoodbyMessage(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return (char)ProcessData;
  LOBYTE(ProcessData) = HIDWORD(ProcessData[2].klass) == 5 && LOBYTE(ProcessData[2].klass) == 3;
  return (char)ProcessData;
}

// 0x20bb640
void cmpStartMemSet(sdatUnitWork_t *a_pUnitDst, bool bKeyControl) {
  Il2CppObject *ProcessData;
  Il2CppObject *v8;
  s32 v10;
  Il2CppClass *v12;
  void **p_monitor;
  sdatUnitWork_t *v16;
  sdatUnitWork_t *v17;

  ProcessData = dds3GetProcessData(g_mainPID);
  v8 = ProcessData;
  LOBYTE(ProcessData[2].klass) = 0;
  if (bKeyControl)
  {
    if (a_pUnitDst->devilid)
      v10 = 4;
    else
      v10 = 6;
    HIDWORD(ProcessData[2].klass) = v10;
  }
  else
  {
    HIDWORD(ProcessData[2].klass) = 0;
  }
  v8[3].klass = 0;
  v8[14] = 0u;
  v8[15] = 0u;
  *(void **)((char *)&v8[12].monitor + 4) = 0x100000001LL;
  v8[21] = (Il2CppObject)xmmword_3CFC0A0;
  v12 = NewSpecific(bool, 0x11u);
  v8[16].klass = v12;
  v8[6].monitor = a_pUnitDst;
  p_monitor = &v8[6].monitor;
  *(p_monitor - 10) = ((u64)*(p_monitor - 10) & 0xFFFFFFFFFBFF7FFFLL | 0x8000);
  *((u8 *)p_monitor + 165) = 0;
  v16 = *p_monitor;
  v17 = *p_monitor;
  cmpCurInitMemSkl(v17, 0);
}

// 0x20bb820
void cmpStartGoodby(sdatUnitWork_t *a_pUnit) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  LOBYTE(ProcessData[2].klass) = 0;
  HIDWORD(ProcessData[2].klass) = 5;
}

// 0x20bb940
void cmpStartSklSet(sdatUnitWork_t *a_pUnit, CMP_ITM_SKLSET_TYPE _sklType) {
  Il2CppObject *ProcessData;
  Il2CppObject *v7;
  s32 v10;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  v7 = ProcessData;
  HIDWORD(ProcessData[2].klass) = 7;
  LOWORD(ProcessData[3].monitor) = 0;
  LOBYTE(v7[2].klass) = 0;
  if ((sklItmRst & 0x40) != 0)
    v10 = 2;
  else
    v10 = 1;
  HIDWORD(v7[12].monitor) = v10;
  if ((u32)sklType <= 1)
    LODWORD(v7[13].klass) = sklType;
}

// 0x20bbad0
void cmpStartDvlReport(sdatUnitWork_t *a_pUnit) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  LOBYTE(ProcessData[2].klass) = 0;
  HIDWORD(ProcessData[2].klass) = 8;
}

// 0x20bbbf0
void cmpEquipSwordNoHelp(bool bFlag) {
  Il2CppObject *ProcessData;

  if (!g_mainPID)
    return;
  if (dds3ExistProcess(g_mainPID))
  {
    ProcessData = dds3GetProcessData(g_mainPID);
    if (!ProcessData)
      goto LABEL_21;
    goto LABEL_19;
    if (!ProcessData)
    {
LABEL_21:
      LOBYTE(ProcessData[19].klass) = bFlag;
      return;
    }
LABEL_19:
    goto LABEL_21;
  }
}

// 0x20ae8f0
s32 cmpGetSkillIconSpriteNo(SKLID a_skillid) {
  SBTLSKILLP_TBL *Skilltbl;

  Skilltbl = sBtlGetSkilltbl(a_skillid);
  if (!Skilltbl)
    return -1;
  if ((Skilltbl->type & 0x1000) != 0)
    return 66;
  if ((Skilltbl->type & 0x2000) != 0)
    return 65;
  if (sBtlChkRepeat(a_skillid))
    return 64;
  else
    return 67;
}

// 0x20bbda0
void cmpSwordSelFlagOn(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  ProcessData[1].monitor = ((u64)ProcessData[1].monitor | 0x40000000);
  BYTE1(ProcessData[24].klass) = 1;
}

// 0x20b4c50
bool cmpSwordSelFlagChk(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return (char)ProcessData;
  LOBYTE(ProcessData) = BYTE1(ProcessData[24].klass) != 0;
  return (char)ProcessData;
}

// 0x20bbed0
CMP_STATUS_STEP cmpGetStatusStep(void) {
  char *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return (s32)ProcessData;
  LODWORD(ProcessData) = ProcessData[32];
  return (s32)ProcessData;
}

// 0x20a9b00
RankText *cmpGetSetRank(s32 _setNo) {
  void *ProcessData;
  s64 naturalAligment;
  __int128 v6;
  Il2CppObject *current;
  __int128 v8;
  s32 klass;
  System_Collections_Generic_List_Enumerator_T__o v12;
  System_Collections_Generic_List_Enumerator_T__o v13;

  memset(&v13, 0, sizeof(v13));
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return 0;
  LOBYTE(ProcessData[7]._size) < (u32)naturalAligment || *((tagCMP_STATUS_WORK **)(ProcessData)[5].klass + naturalAligment - 1) != tagCMP_STATUS_WORK;
  if (setNo == -1)
  {
    _GetEnumerator(&v12, ProcessData[46]);
    v8 = *(_OWORD *)&v12._list;
    v12._list = 0;
    *(u64 *)&v12._index = &v13;
    v13._current = v12._current;
    *(_OWORD *)&v13._list = v8;
    while (_MoveNext(&v13))
    {
      current = v13._current;
      klass = v13._current[2].klass;
      if (klass == GBWK->player->syougou)
        goto LABEL_23;
    }
  }
  else
  {
    _GetEnumerator(&v12, ProcessData[46]);
    v6 = *(_OWORD *)&v12._list;
    v12._list = 0;
    *(u64 *)&v12._index = &v13;
    v13._current = v12._current;
    *(_OWORD *)&v13._list = v6;
    while (_MoveNext(&v13))
    {
      current = v13._current;
      if (LODWORD(v13._current[2].klass) == setNo)
        goto LABEL_23;
    }
  }
  current = 0;
LABEL_23:
  _Dispose(&v13);
  return (RankText *)current;
}

// 0x20bbff0
void cmpSetMitamaCombDvl(sdatUnitWork_t *_unit) {
  tagCMP_STATUS_WORK *StatusWk;

  StatusWk = cmpGetStatusWk();
  if (!StatusWk)
    return;
  goto LABEL_4;
  if (StatusWk)
  {
LABEL_4:
    StatusWk->mitamaCombDvl = unit;
  }
}

// 0x20bc090
tagCMP_STATUS_WORK *cmpGetStatusWk(void) {
  tagCMP_STATUS_WORK *result;

  result = (tagCMP_STATUS_WORK *)dds3GetProcessData(g_mainPID);
  if (!result)
    goto LABEL_11;
  goto LABEL_9;
  if (!result)
LABEL_9:
LABEL_11:
  if (!g_mainPID)
    return 0;
  return result;
}
