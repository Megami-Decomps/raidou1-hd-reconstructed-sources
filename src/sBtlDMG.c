#include "types.h"
#include "SBTLUNIT_SIDE.h"
#include "SKLID.h"
#include "achievement.h"
#include "aw_enemyhitback.h"
#include "aw_hitbackwave.h"
#include "aw_mag.h"
#include "aw_magwait.h"
#include "aw_sbattle.h"
#include "aw_shields.h"
#include "cfg.h"
#include "configgame.h"
#include "dat.h"
#include "dds3kerneldraw.h"
#include "dds3objectbase.h"
#include "dds3scenebasic.h"
#include "dds3worldbasic.h"
#include "effpartslist.h"
#include "evtbit.h"
#include "file.h"
#include "fld.h"
#include "gohcalc.h"
#include "gohkilldevil.h"
#include "lmap.h"
#include "mdl.h"
#include "sbtl.h"
#include "sbtlactai.h"
#include "sbtlaction.h"
#include "sbtlcalc.h"
#include "sbtldmg.h"
#include "sbtldraw.h"
#include "sbtldvltk.h"
#include "sbtleff.h"
#include "sbtleffbo.h"
#include "sbtlencount.h"
#include "sbtlevent.h"
#include "sbtlexp.h"
#include "sbtlmain.h"
#include "sbtlplayer.h"
#include "sbtlplayer_common.h"
#include "sbtlplayer_sddash.h"
#include "sbtlplayer_spirit.h"
#include "sbtlplayertbl.h"
#include "sbtlscene.h"
#include "sbtlscript.h"
#include "sbtlskill.h"
#include "sbtlsm.h"
#include "sbtlsound.h"
#include "sbtlstp.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sbtlvisual.h"
#include "sdf_vu0.h"
#include "sdfmodel.h"
#include "sdfquat.h"
#include "slmain.h"
#include "smnr.h"

#define BOUDO_A_DAMAGE 1.5
#define BOUDO_S_DAMAGE 2
#define KOHUN_A_DAMAGE 2
#define KOHUN_S_DAMAGE 0.6
#define WINCE_TYPE_NONE 0
#define WINCE_TYPE_S 1
#define WINCE_TYPE_L 2
#define WINCE_0_TIME 60

typedef struct SBTLDMG_ANIMWORK SBTLDMG_ANIMWORK;
typedef struct SBTLDMG_HITLISTWORK SBTLDMG_HITLISTWORK;
typedef struct SBTLDMG_HITWORK SBTLDMG_HITWORK;
typedef struct SBTLDMG_LISTWORK SBTLDMG_LISTWORK;
typedef struct SBTLEFF_WORK SBTLEFF_WORK;
typedef struct SBTLSKILLHIT_POSWORK SBTLSKILLHIT_POSWORK;
typedef struct SBTLSKILLHIT_TBL SBTLSKILLHIT_TBL;
typedef struct SBTLSKILLP_TBL SBTLSKILLP_TBL;
typedef struct SBTLSKILL_TBL SBTLSKILL_TBL;
typedef struct SBTLSKLHIT_PACDATAWORK SBTLSKLHIT_PACDATAWORK;
typedef struct SBTLUNIT_LISTWORK SBTLUNIT_LISTWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

static f32 NOMARL_CRITICAL_RAITO;
static f32 WEAK_CRITICAL_RAITO;
static SBTLDMG_HITWORK *sbtl_dmgdummy;
SBTLUNIT_WORK *playerhit;
static bool is_setuma;
static bool setuma_next;
static s32 **damage_to_enemy_raito_tbl;
static s32 **damage_to_raido_raito_tbl;

static bool CreateAnim(s32 Atk_ListID, s32 Dmg_ListID, s32 dmg, const sdfVector4_t *pos, s32 rgbano, s16 time, s32 side, s32 minor, s32 uniq_code, bool firstDsp);
static u32 AlfDown(SBTLDMG_ANIMWORK *wk, u32 decval);
static void AlfSet(SBTLDMG_ANIMWORK *wk, u32 alp);
static bool SetAttackHitData_pData(SBTLUNIT_WORK *wk, s32 index);
static void UnsetKaraburiSub(SBTLDMG_HITLISTWORK *lwk, SBTLDMG_HITWORK *hwk);
static void BS_HITOK_Dmg(SBTLUNIT_WORK *wk, s32 id1, s32 id2, s32 hp_limit);
static bool IsWeakAfterMuteki(SBTLUNIT_WORK *wk);
static void HukaEffect(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, SBTLDMG_HITWORK *hwk);
static bool IsKabeOrKudan(SBTLUNIT_WORK *wklock);
static s32 SetCritical(SBTLUNIT_WORK *wk, s32 retpara, f32 raito);
static void SetHitLight(SBTLUNIT_WORK *wk1, SBTLUNIT_WORK *wk2, s32 _IsCritical);
static s32 GetKouchoku(SBTLUNIT_WORK *wk, SKLID sklid);
static s32 RD_SkillDamageChack(s32 damage);
static bool RD_SkillChack(void);
static bool IsDamageProc(SBTLUNIT_WORK *wk);
static bool IsAutoRec(SBTLUNIT_WORK *wk);

// macros
// 0x204f190: void PESTMEGIDORA(SBTLUNIT_WORK *wk)
static inline void PESTMEGIDORA(SBTLUNIT_WORK *wk) {
  s32 ListID;
  s32 i;

  ListID = wk->ListID;
  if (ListID != wk->playerID)
    return;
  for (i = 0; ; ++i)
  {
    if (i >= wk->UnitMng->number)
      break;
  }
}

// 0x2036700
void sBtlClearStaticPar(void) {
  SBTLDMG_HITWORK *v1;

  v1 = Allocate(SBTLDMG_HITWORK);
  _ctor(v1, 0);
  sbtl_dmgdummy = v1;
}

// 0x2036790
s32 sBtlGetAddMag(s32 baseVal) {
  if ((wk->status3 & 2) == 0)
    return baseVal;
  return 3 * baseVal / 2;
}

// 0x2036850
void sBtlSetAddMag(SBTLUNIT_WORK *a_pUnitTgt, s32 a_addMag) {
  s32 devilid;
  bool v7;
  f32 v8;
  f32 v9;
  s32 v10;
  evtUnitHandle_t *hEveUnit;
  dds3ModelHandle_t *Model;
  sdfModelRootNode_t *modelRoot;
  long f64 v15;
  struct sdfVector4_t SZ;

  if (a_pUnitTgt && a_addMag >= 1)
  {
    if ((wk->status3 & 2) == 0)
    {
      devilid = (u16)a_pUnitTgt->para->devilid;
      if (a_pUnitTgt->para->devilid > 260)
        goto LABEL_10;
      goto LABEL_17;
    }
    a_addMag = 3 * a_addMag / 2;
    devilid = (u16)a_pUnitTgt->para->devilid;
    if (a_pUnitTgt->para->devilid > 260)
    {
LABEL_10:
      if (devilid != 315)
      {
        if (devilid != 314)
        {
LABEL_25:
          sBtlGetUnitHelperPos(a_pUnitTgt, 0);
          hEveUnit = a_pUnitTgt->hEveUnit;
          SZ = vct_A;
          if (!hEveUnit)
            return;
          Model = hEveUnit->Model;
          if (Model)
          {
            modelRoot = Model->modelRoot;
            if (modelRoot)
            {
              if (!sdfModelGetMarkPos(modelRoot, 1))
                sdfModelGetMarkPos(a_pUnitTgt->hEveUnit->Model->modelRoot, 0);
              sub_1B335A0(&SZ, 0, v15);
              Add(a_pUnitTgt->criticalflg != 0, SZ.x, SZ.y, SZ.z, a_addMag, 0);
            }
          }
          return;
        }
        goto LABEL_20;
      }
      goto LABEL_19;
    }
LABEL_17:
    if (devilid == 258)
    {
LABEL_20:
      v7 = a_pUnitTgt->criticalflg == 0;
      v8 = -500.0;
      v9 = 1000.0;
      goto LABEL_21;
    }
    if (devilid != 260)
      goto LABEL_25;
LABEL_19:
    v7 = a_pUnitTgt->criticalflg == 0;
    v8 = -200.0;
    v9 = 900.0;
LABEL_21:
    v10 = !v7;
    Add(v10, 0.0, v8, v9, a_addMag, 0);
  }
}

// 0x2036b50
void sBtlSetAddMag_Setsuma(SBTLUNIT_WORK *a_pUnitTgt, s32 a_addMag) {
  evtUnitHandle_t *hEveUnit;
  dds3ModelHandle_t *Model;
  sdfModelRootNode_t *modelRoot;
  f32 *p_x;
  f32 v12;
  f32 v13;
  f32 v14;

  if (!a_pUnitTgt || a_addMag < 1)
    return;
  sBtlGetUnitHelperPos(a_pUnitTgt, 0);
  hEveUnit = a_pUnitTgt->hEveUnit;
  if (!hEveUnit)
    return;
  Model = hEveUnit->Model;
  if (Model)
  {
    modelRoot = Model->modelRoot;
    if (modelRoot)
    {
      if (sdfModelGetMarkPos(modelRoot, 1))
      {
        goto LABEL_19;
      }
      else
      {
        sdfModelGetMarkPos(a_pUnitTgt->hEveUnit->Model->modelRoot, 0);
LABEL_19:
        goto LABEL_20;
      }
LABEL_20:
      p_x = &vf00.x;
      v12 = p_x[4];
      v13 = p_x[5];
      v14 = p_x[6];
      if ((wk->status3 & 2) == 0)
      {
LABEL_26:
        Add(1, v12, v13, v14, a_addMag, 0);
        return;
      }
      a_addMag = 3 * a_addMag / 2;
      goto LABEL_26;
    }
  }
}

// 0x2036df0
void sBtlSetAddMag_Setsuma_D(SBTLUNIT_WORK *a_pUnitTgt) {
  evtUnitHandle_t *hEveUnit;
  dds3ModelHandle_t *Model;
  sdfModelRootNode_t *modelRoot;

  if (!a_pUnitTgt)
    return;
  sBtlGetUnitHelperPos(a_pUnitTgt, 0);
  hEveUnit = a_pUnitTgt->hEveUnit;
  if (!hEveUnit)
    return;
  Model = hEveUnit->Model;
  if (Model)
  {
    modelRoot = Model->modelRoot;
    if (modelRoot)
    {
      if (sdfModelGetMarkPos(modelRoot, 1))
      {
        goto LABEL_18;
      }
      else
      {
        sdfModelGetMarkPos(a_pUnitTgt->hEveUnit->Model->modelRoot, 0);
LABEL_18:
        goto LABEL_19;
      }
LABEL_19:
      Add(10, vct_A.x, vct_A.y, vct_A.z, 0, 0);
      return;
    }
  }
}

// 0x2036fb0
void sBtlSetAddMagAisyo(SBTLUNIT_WORK *a_pUnitTgt, s32 a_addMag) {
  f32 v5;
  s32 v6;
  sdatUnitWork_t *para;
  s32 v8;
  s64 v10;

  if (a_pUnitTgt && a_addMag >= 1 && (a_pUnitTgt->side & 1) != 0)
  {
    v5 = ConvLevelValue(6, (f32)a_addMag);
    v6 = v5;
    para = a_pUnitTgt->para;
    if ((s32)v5 <= 1)
      v6 = 1;
    if (v5 == INFINITY)
      v8 = 1;
    else
      v8 = v6;
    if (sBtlChkHaveMemSkl(para, 65))
    {
      v10 = 1374389535 * v8 * a_pUnitTgt->para->autost_cnt2;
      v8 += (v10 >> 37) + ((u64)v10 >> 63);
    }
    sBtlSetAddMag(a_pUnitTgt, v8);
  }
}

// 0x2037110
void sBtlSetAddMagWeakAttack(SBTLUNIT_WORK *a_pUnitAct, SBTLUNIT_WORK *a_pUnitTgt, s32 a_addMag, SKLID _skl) {
  sdatUnitWork_t *para;
  s32 HaveMemSkl;
  sdatUnitWork_t *v11;
  s64 v13;
  _BOOL4 v14;
  sdatUnitWork_t *v15;
  u32 BadStatus;

  if (a_pUnitAct && a_pUnitTgt && a_addMag >= 1 && (a_pUnitAct->side & 1) != 0 && (a_pUnitTgt->side & 2) != 0)
  {
    para = a_pUnitAct->para;
    HaveMemSkl = sBtlChkHaveMemSkl(para, 92);
    v11 = a_pUnitAct->para;
    if (HaveMemSkl)
      a_addMag += v11->autost_cnt;
    if (sBtlChkHaveMemSkl(v11, 65))
    {
      v13 = 1374389535 * a_addMag * a_pUnitAct->para->autost_cnt2;
      a_addMag += (v13 >> 37) + ((u64)v13 >> 63);
    }
    if ((a_pUnitAct->side & 0x80) != 0)
    {
      v14 = sbtlplayertblChkPlayerSordSkill(skl);
      if (sBtlGetSpiritSkillChk(1390) && v14)
      {
        v15 = a_pUnitAct->para;
        BadStatus = sBtlGetBadStatus(v15);
        if (BadStatus <= 0xB && ((1 << BadStatus) & 0xD00) != 0 || (f32)((f32)a_pUnitAct->para->now->hp / (f32)a_pUnitAct->para->now->maxhp) < 0.26)
        {
          a_addMag *= 2;
        }
      }
      if (sBtlGetSpiritSkillChk(1443) && v14)
      {
        a_addMag <<= wk->hitComboNum > 24;
      }
    }
    sBtlSetAddMag(a_pUnitTgt, a_addMag);
  }
}

// 0x20373b0
SBTLDMG_LISTWORK *sBtlCreateAnimList(void) {
  SBTLDMG_LISTWORK *v1;
  SBTLDMG_UNITWORK *v3;
  SBTLDMG_UNITWORK **p_unit;
  s64 i;
  s64 v6;
  SBTLDMG_UNITWORK *v7;
  SBTLDMG_UNITWORK *v8;

  v1 = (SBTLDMG_LISTWORK *)Allocate(SBTLDMG_LISTWORK);
  _ctor(v1, 0);
  v1->num = 0;
  v3 = NewSpecific(SBTLDMG_UNITWORK, 0x28u);
  v1->unit = v3;
  p_unit = &v1->unit;
  for (i = 32; i != 352; i += 8)
  {
    v7 = *p_unit;
    v8 = Allocate(SBTLDMG_UNITWORK);
    _ctor(v8, 0);
    *(Il2CppClass **)((char *)&v7->obj.klass + i) = v8;
    v6 = *(s64 *)((char *)&(*p_unit)->obj.klass + i);
    *(u64 *)(v6 + 16) = 0;
  }
  return v1;
}

// 0x20374e0
void sBtlCalcAnim_DmgNumPos(SBTLUNIT_WORK *wk, s32 mode, sdfVector4_t *pos) {
  SBTLVISUAL_DATA *v7;
  s32 v8;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 tdanhelper;
  SBTLUNIT_WORK *v15;
  evtUnitHandle_t *hEveUnit;
  dds3ModelHandle_t *Model;
  sdfModelRootNode_t *modelRoot;
  struct sdfVector4_t v22;
  struct sdfVector4_t v23;

  v7 = Allocate(SBTLVISUAL_DATA);
  *(u64 *)&pos->x = 0;
  pos->z = 0.0;
  if (!wk)
    return;
  v8 = wk->side & 0x83;
  if ((wk->status & 0x1000) == 0)
  {
LABEL_25:
    sBtlGetCylinderData(wk, v7);
    v23 = v7->center;
    vct_A = v23;
    goto LABEL_40;
  }
  if (mode == 2)
  {
    UnitMng = wk->UnitMng;
    tdanhelper = wk->tdanhelper;
  }
  else if (mode == 1)
  {
    UnitMng = wk->UnitMng;
    tdanhelper = wk->hitsliphelper;
  }
  else
  {
    UnitMng = wk->UnitMng;
    tdanhelper = wk->hithelperreqID;
  }
  v15 = sBtlSearchUnit_ID(UnitMng, tdanhelper);
  if (!v15)
    goto LABEL_25;
  v22 = v15->pos;
  vct_A = v22;
LABEL_40:
  *pos = vct_A;
  if (v8 != 1)
    return;
  hEveUnit = wk->hEveUnit;
  if (hEveUnit)
  {
    Model = hEveUnit->Model;
    if (Model)
    {
      modelRoot = Model->modelRoot;
      if (modelRoot)
      {
        if (sdfModelGetMarkPos(modelRoot, 1))
        {
          goto LABEL_49;
        }
        else
        {
          sdfModelGetMarkPos(wk->hEveUnit->Model->modelRoot, 0);
LABEL_49:
          goto LABEL_50;
        }
LABEL_50:
        *pos = vct_A;
        return;
      }
    }
  }
}

// 0x2037950
bool sBtlCreateAnim_Unit(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *atk_wk, s32 damage, s16 time, s32 mode, SKLID sklid) {
  SBTLVISUAL_DATA *v12;
  char firstDsp;
  s32 side;
  s32 v16;
  s32 v17;
  s32 v18;
  SBATTLE_WORK *v20;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  sdatUnitWork_t *para;
  s32 devilid;
  sdatParaWork_t *now;
  s32 maxhp;
  s32 uniq_code;
  s32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  s32 v33;
  s32 v35;
  s32 v36;
  f32 v37;
  f32 v38;
  s32 v39;
  f32 v40;
  f32 v41;
  s32 ListID;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  s32 minor;
  sdfVector4_t pos;
  sdfVector4_t v52;
  sdfVector4_t v53;
  sdfVector4_t v54;
  sdfVector4_t v55;

  *(u64 *)&pos.x = 0;
  *(u64 *)&pos.z = 0;
  v12 = Allocate(SBTLVISUAL_DATA);
  _ctor(v12, 0);
  if (sklid)
  {
    if (!wk)
      return 0;
    firstDsp = 1;
    if (!damage)
      return 0;
  }
  else
  {
    firstDsp = wk->slip_sklid != 0;
    if (!damage)
      return 0;
  }
  side = wk->side;
  v16 = side & 1;
  if ((side & 0x80) != 0)
    v16 = 0;
  if ((side & 2) != 0)
    v17 = 2;
  else
    v17 = v16;
  if (((u32)(sklid - 690) <= 0xB && ((1 << (sklid + 78)) & 0xA67) != 0 || sklid == 65) && ((v18 = (u16)wk->para->devilid, v18 == 314) || v18 == 258))
  {
    v20 = wk;
    UnitMng = v20->UnitMng;
    playerID = v20->playerID;
    pos.x = sBtlSearchUnit_ID(UnitMng, playerID)->pos.x;
    para = wk->para;
    *(u64 *)&pos.y = 0x44610000C37A0000LL;
  }
  else
  {
    sBtlCalcAnim_DmgNumPos(wk, mode, &pos);
    if (sBtlCheckSetsuma())
    {
      if (!sBtlCheckSetsumaEnd())
      {
        *(u64 *)&pos.x = *(u64 *)&wk->vDmgPosBfrCmb.x;
        pos.z = wk->vDmgPosBfrCmb.z;
      }
    }
    para = wk->para;
    devilid = (u16)para->devilid;
    if (devilid == 315 || devilid == 260)
      pos.y = pos.y + -100.0;
  }
  now = para->now;
  maxhp = now->maxhp;
  if (maxhp < 1)
    return 0;
  if ((wk->side & 1) != 0 && now->hp >= 1)
    wk->dmg_hpdraw_cnt = 60;
  uniq_code = para->uniq_code;
  if ((u32)mode < 3)
  {
    v35 = 100 * now->hp / maxhp;
    if (v35 <= 25)
    {
      ListID = wk->ListID;
      x = pos.x;
      y = pos.y;
      z = pos.z;
      w = pos.w;
      minor = wk->minor;
      v54.x = x;
      v54.y = y;
      v54.z = z;
      v54.w = w;
      CreateAnim(-1, ListID, damage, v54, 2, time, v17, minor, uniq_code, firstDsp);
    }
    else
    {
      v36 = wk->ListID;
      v38 = pos.x;
      v37 = pos.y;
      v39 = wk->minor;
      v41 = pos.z;
      v40 = pos.w;
      if ((u32)v35 <= 0x32)
      {
        v55.x = v38;
        v55.y = v37;
        v55.z = v41;
        v55.w = v40;
        CreateAnim(-1, v36, damage, v55, 1, time, v17, v39, uniq_code, firstDsp);
      }
      else
      {
        v53.x = v38;
        v53.y = v37;
        v53.z = v41;
        v53.w = v40;
        CreateAnim(-1, v36, damage, v53, 0, time, v17, v39, uniq_code, firstDsp);
      }
    }
    wk->BossDmgEffect_Hit = 1;
    return 1;
  }
  else if ((u32)(mode - 3) > 1)
  {
    return 1;
  }
  else
  {
    v28 = wk->ListID;
    v29 = pos.x;
    v30 = pos.y;
    v31 = pos.z;
    v32 = pos.w;
    v33 = wk->minor;
    v52.x = v29;
    v52.y = v30;
    v52.z = v31;
    v52.w = v32;
    CreateAnim(-1, v28, damage, v52, mode, time, v17, v33, uniq_code, 0);
    return 1;
  }
}

// 0x2037d90
static bool CreateAnim(s32 Atk_ListID, s32 Dmg_ListID, s32 dmg, const sdfVector4_t *pos, s32 rgbano, s16 time, s32 side, s32 minor, s32 uniq_code, bool firstDsp) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  u32 *v21;
  u32 status4;
  SBTLDMG_ANIMWORK *v24;
  f32 *p_x;
  sdfVector4_t *v27;
  bool v28;
  s32 v29;
  s64 v32;
  s32 v33;
  s32 v34;
  s64 i;
  s64 v36;
  s64 v37;
  f32 v38;
  f32 v39;
  int32x2_t v40;
  float32x2_t v41;
  f32 v42;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v45;
  SBTLUNIT_WORK *v46;
  s32 v48;
  SBTLDMG_LISTWORK *dmgList;
  s32 v51;
  const char *name;
  s32 v55;
  s32 v56;
  s32 v57;
  s32 v58;
  f32 *v59;
  f32 v61;
  f32 v63;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  v21 = NewSpecific(uint, 5u);
  InitializeArray_55364416(v21, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__6EE7F8B199D85FD5FE0CE540B0369B8586FF71DB65D4317CC22A2588AFCC4D0B, 0);
  status4 = wk->status4;
  if ((status4 & 0x4000) != 0)
    return 0;
  if ((status4 & 0x10000) != 0)
    return 0;
  v24 = Allocate(SBTLDMG_ANIMWORK);
  v24->st = 0;
  v24->time = 0;
  v24->cmptime = time;
  v24->counter = 0;
  v24->dmg = dmg;
  v24->dmg_anm = dmg;
  v24->dmg_anm_add = 0;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v27 = &v24->pos;
  v28 = firstDsp;
  *v27 = vct_A;
  if (!side)
  {
    v29 = 61568;
    goto LABEL_26;
  }
  if (side == 1)
    v29 = 15728768;
  else
    v29 = -268435328;
LABEL_26:
  v24->rgba2 = v29;
  v24->rgbano = 0;
  v24->Atk_ListID = Atk_ListID;
  v24->Dmg_ListID = Dmg_ListID;
  v24->side = side;
  v24->minor = minor;
  v24->uniq_code = uniq_code;
  v24->type = rgbano;
  if (rgbano <= 2)
  {
    if (side == 1)
      v33 = 15728768;
    else
      v33 = -268435328;
    if (side)
      v34 = v33;
    else
      v34 = 61568;
    for (i = 32; i != 352; i += 8)
    {
      name = (*(Il2CppClass **)((char *)&wk->dmgList->unit->obj.klass + i))->_1.name;
      if (!name || *((u32 *)name + 25) || *((u32 *)name + 20) != Dmg_ListID || *((s32 *)name + 24) > 2 || v24->st > 4)
      {
        continue;
      }
      v55 = *((u32 *)name + 13) + dmg;
      v56 = v55 - *((u32 *)name + 14);
      *((u32 *)name + 13) = v55;
      if (v56 <= 0)
      {
        *((u32 *)name + 14) = v55;
        *((u32 *)name + 15) = 0;
        if (*((s16 *)name + 17) >= 1)
          goto LABEL_77;
      }
      else
      {
        if ((u32)v56 <= 7)
          v57 = 1;
        else
          v57 = (u32)v56 >> 3;
        *((u32 *)name + 15) = v57;
        if (*((s16 *)name + 17) >= 1)
        {
LABEL_77:
          *((u32 *)name + 11) = 90;
          *((u16 *)name + 17) = 1;
        }
      }
      v58 = *((u32 *)name + 5);
      v59 = &vf00.x;
      v59[4] = x;
      v59[5] = y;
      v59[6] = z;
      v59[7] = w;
      v28 = 1;
      *((_OWORD *)name + 1) = vct_A;
      *((u32 *)name + 5) = v58;
      *((u32 *)name + 9) = v21[rgbano];
      *((u32 *)name + 10) = v34;
    }
  }
  if (!v28)
    goto LABEL_45;
  v24->dispmode = 1;
  if (!sBtlCheckSetsuma())
    goto LABEL_42;
  goto LABEL_9002;
  if (!sBtlCheckSetsuma())
  {
LABEL_42:
    v63 = sub_1B34D00(0, v32);
    v61 = sub_1B34D00(0, v36);
    v38 = sub_1B34D00(0, v37);
    v39 = -0.2;
    v40.n64_u64[0] = vdup_n_s32(0x42A00000u).n64_u64[0];
    v41.n64_u64[0] = vadd_f32((float32x2_t)__PAIR64__(LODWORD(v61), LODWORD(v63)), vbsl_s8(vcgt_f32((float32x2_t)0x3F0000003F000000LL, (float32x2_t)__PAIR64__(LODWORD(v61), LODWORD(v63))), vdup_n_s32(0xBE4CCCCD), vdup_n_s32(0x3E4CCCCDu))).n64_u64[0];
    if (v38 >= 0.5)
      v39 = 0.2;
    v42 = v24->pos.z + (f32)((f32)((f32)(v38 + v39) * 80.0) + -40.0);
    *(float32x2_t *)&v24->pos = vadd_f32(*(float32x2_t *)&v24->pos, vadd_f32(vmul_f32(v41, v40), vdup_n_s32(0xC2200000)));
    v24->pos.z = v42;
    goto LABEL_45;
  }
LABEL_9002:
  if (sBtlCheckSetsumaEnd())
    goto LABEL_42;
LABEL_45:
  UnitMng = wk->UnitMng;
  v45 = v24->Dmg_ListID;
  v46 = sBtlSearchUnit_ID(UnitMng, v45);
  if (!v24->dispmode)
  {
    v48 = v21[rgbano];
    goto LABEL_54;
  }
  v24->rgba = v21[0];
  if (v24->side != 2 || !v46->criticalcol)
    goto LABEL_55;
  v48 = v21[1];
LABEL_54:
  v24->rgba = v48;
LABEL_55:
  dmgList = wk->dmgList;
  v51 = sBtlRegistAnimList(dmgList, v24);
  if (v51 != 255)
    v24->ID = v51;
  return 1;
}

// 0x2038800
bool sBtlReleaseAnim_ID(SBTLDMG_LISTWORK *lwk, s32 id) {
  SBTLDMG_UNITWORK *v3;
  SBTLDMG_UNITWORK *p_fields;
  SBTLDMG_ANIMWORK *wk;

  v3 = lwk->unit[id];
  wk = v3->wk;
  p_fields = &v3->fields;
  if (wk)
  {
    p_fields->wk = 0;
  }
  return 1;
}

// 0x2038490
s32 sBtlRegistAnimList(SBTLDMG_LISTWORK *lwk, SBTLDMG_ANIMWORK *wk) {
  SBTLDMG_UNITWORK *unit;
  SBTLDMG_UNITWORK *v5;
  s32 v7;

  unit = lwk->unit;
  v5 = unit[0];
  if (v5->wk)
  {
    v5 = unit[1];
    if (v5->wk)
    {
      v5 = unit[2];
      if (v5->wk)
      {
        v5 = unit[3];
        if (v5->wk)
        {
          v5 = unit[4];
          if (v5->wk)
          {
            v5 = unit[5];
            if (v5->wk)
            {
              v5 = unit[6];
              if (v5->wk)
              {
                v5 = unit[7];
                if (v5->wk)
                {
                  v5 = unit[8];
                  if (v5->wk)
                  {
                    v5 = unit[9];
                    if (v5->wk)
                    {
                      v5 = unit[10];
                      if (v5->wk)
                      {
                        v5 = unit[11];
                        if (v5->wk)
                        {
                          v5 = unit[12];
                          if (v5->wk)
                          {
                            v5 = unit[13];
                            if (v5->wk)
                            {
                              v5 = unit[14];
                              if (v5->wk)
                              {
                                v5 = unit[15];
                                if (v5->wk)
                                {
                                  v5 = unit[16];
                                  if (v5->wk)
                                  {
                                    v5 = unit[17];
                                    if (v5->wk)
                                    {
                                      v5 = unit[18];
                                      if (v5->wk)
                                      {
                                        v5 = unit[19];
                                        if (v5->wk)
                                        {
                                          v5 = unit[20];
                                          if (v5->wk)
                                          {
                                            v5 = unit[21];
                                            if (v5->wk)
                                            {
                                              v5 = unit[22];
                                              if (v5->wk)
                                              {
                                                v5 = unit[23];
                                                if (v5->wk)
                                                {
                                                  v5 = unit[24];
                                                  if (v5->wk)
                                                  {
                                                    v5 = unit[25];
                                                    if (v5->wk)
                                                    {
                                                      v5 = unit[26];
                                                      if (v5->wk)
                                                      {
                                                        v5 = unit[27];
                                                        if (v5->wk)
                                                        {
                                                          v5 = unit[28];
                                                          if (v5->wk)
                                                          {
                                                            v5 = unit[29];
                                                            if (v5->wk)
                                                            {
                                                              v5 = unit[30];
                                                              if (v5->wk)
                                                              {
                                                                v5 = unit[31];
                                                                if (v5->wk)
                                                                {
                                                                  v5 = unit[32];
                                                                  if (v5->wk)
                                                                  {
                                                                    v5 = unit[33];
                                                                    if (v5->wk)
                                                                    {
                                                                      v5 = unit[34];
                                                                      if (v5->wk)
                                                                      {
                                                                        v5 = unit[35];
                                                                        if (v5->wk)
                                                                        {
                                                                          v5 = unit[36];
                                                                          if (v5->wk)
                                                                          {
                                                                            v5 = unit[37];
                                                                            if (v5->wk)
                                                                            {
                                                                              v5 = unit[38];
                                                                              if (v5->wk)
                                                                              {
                                                                                v5 = unit[39];
                                                                                if (v5->wk)
                                                                                  return 255;
                                                                                v7 = 39;
                                                                              }
                                                                              else
                                                                              {
                                                                                v7 = 38;
                                                                              }
                                                                            }
                                                                            else
                                                                            {
                                                                              v7 = 37;
                                                                            }
                                                                          }
                                                                          else
                                                                          {
                                                                            v7 = 36;
                                                                          }
                                                                        }
                                                                        else
                                                                        {
                                                                          v7 = 35;
                                                                        }
                                                                      }
                                                                      else
                                                                      {
                                                                        v7 = 34;
                                                                      }
                                                                    }
                                                                    else
                                                                    {
                                                                      v7 = 33;
                                                                    }
                                                                  }
                                                                  else
                                                                  {
                                                                    v7 = 32;
                                                                  }
                                                                }
                                                                else
                                                                {
                                                                  v7 = 31;
                                                                }
                                                              }
                                                              else
                                                              {
                                                                v7 = 30;
                                                              }
                                                            }
                                                            else
                                                            {
                                                              v7 = 29;
                                                            }
                                                          }
                                                          else
                                                          {
                                                            v7 = 28;
                                                          }
                                                        }
                                                        else
                                                        {
                                                          v7 = 27;
                                                        }
                                                      }
                                                      else
                                                      {
                                                        v7 = 26;
                                                      }
                                                    }
                                                    else
                                                    {
                                                      v7 = 25;
                                                    }
                                                  }
                                                  else
                                                  {
                                                    v7 = 24;
                                                  }
                                                }
                                                else
                                                {
                                                  v7 = 23;
                                                }
                                              }
                                              else
                                              {
                                                v7 = 22;
                                              }
                                            }
                                            else
                                            {
                                              v7 = 21;
                                            }
                                          }
                                          else
                                          {
                                            v7 = 20;
                                          }
                                        }
                                        else
                                        {
                                          v7 = 19;
                                        }
                                      }
                                      else
                                      {
                                        v7 = 18;
                                      }
                                    }
                                    else
                                    {
                                      v7 = 17;
                                    }
                                  }
                                  else
                                  {
                                    v7 = 16;
                                  }
                                }
                                else
                                {
                                  v7 = 15;
                                }
                              }
                              else
                              {
                                v7 = 14;
                              }
                            }
                            else
                            {
                              v7 = 13;
                            }
                          }
                          else
                          {
                            v7 = 12;
                          }
                        }
                        else
                        {
                          v7 = 11;
                        }
                      }
                      else
                      {
                        v7 = 10;
                      }
                    }
                    else
                    {
                      v7 = 9;
                    }
                  }
                  else
                  {
                    v7 = 8;
                  }
                }
                else
                {
                  v7 = 7;
                }
              }
              else
              {
                v7 = 6;
              }
            }
            else
            {
              v7 = 5;
            }
          }
          else
          {
            v7 = 4;
          }
        }
        else
        {
          v7 = 3;
        }
      }
      else
      {
        v7 = 2;
      }
    }
    else
    {
      v7 = 1;
    }
  }
  else
  {
    v7 = 0;
  }
  v5->wk = wk;
  ++lwk->num;
  return v7;
}

// 0x2038840
bool sBtlDeleteAnimList(SBTLDMG_LISTWORK *wk) {
  s64 i;
  SBTLDMG_LISTWORK *v4;
  SBTLDMG_UNITWORK *unit;
  const char *name;
  s64 v7;
  SBTLDMG_UNITWORK *p_fields;
  SBTLDMG_UNITWORK *v11;
  SBTLDMG_ANIMWORK *v12;

  for (i = 32; i != 352; i += 8)
  {
    v4 = wk;
    unit = wk->unit;
    name = (*(Il2CppClass **)((char *)&unit->obj.klass + i))->_1.name;
    if (!name)
      continue;
    v7 = *((s16 *)name + 16);
    v11 = v4->unit[v7];
    v12 = v11->wk;
    p_fields = &v11->fields;
    if (!v12)
      continue;
    p_fields->wk = 0;
    continue;
  }
  wk = 0;
  return 1;
}

// 0x2038930
bool sBtlAnimListClr(void) {
  s64 v2;
  SBTLDMG_UNITWORK *unit;
  const char *name;
  const char *v6;

  v2 = 32;
  unit = wk->dmgList->unit;
  do
  {
    name = (*(Il2CppClass **)((char *)&unit->obj.klass + v2))->_1.name;
    if (name)
      *((u16 *)name + 17) = 6;
    v2 += 8;
  }
  while (v2 != 352);
  return 1;
}

// 0x2038a20
bool sBtlAnimListProc(void) {
  s64 i;
  s16 v4;
  const char *name;
  s32 v8;
  s64 v11;
  SBTLDMG_LISTWORK *dmgList;
  SBTLDMG_UNITWORK *v13;
  SBTLDMG_UNITWORK *p_fields;
  SBTLDMG_ANIMWORK *v15;
  s32 v17;
  s32 v18;
  s32 v19;
  f32 v20;
  f32 v21;
  f32 v23;
  s32 v24;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v26;
  SBTLUNIT_WORK *v28;
  s32 v29;
  s64 v30;
  s32 v31;
  bool v32;
  f32 v33;
  s32 v34;
  s64 v35;
  u32 v36;
  u32 v37;
  bool v38;
  bool v39;
  u32 v40;
  s32 v41;
  s32 *v42;
  s64 v43;
  s32 v44;
  s64 v45;
  s64 v46;
  s64 v47;
  s64 v48;
  s64 v49;
  s64 v50;
  s64 v51;
  s64 v52;
  s64 v53;
  sdfVector4_t v55;

  *(u64 *)&v55.x = 0;
  *(u64 *)&v55.z = 0;
  if (!wk)
    return 0;
  if (!wk->dmgList)
    return 0;
  if ((wk->status & 0x8000000) != 0)
    return 0;
  if ((wk->status2 & 0x20) != 0)
    return 0;
  for (i = 32; i != 352; i += 8)
  {
    name = (*(Il2CppClass **)((char *)&wk->dmgList->unit->obj.klass + i))->_1.name;
    if (name)
    {
      ++*((u16 *)name + 34);
      LimitRange_2((s16 *)name + 34, 0, 60);
      switch (*((u16 *)name + 17))
      {
        case 0:
          if (*((s16 *)name + 34) >= *((s16 *)name + 35))
          {
            *(u64 *)(name + 44) = 0x5A0000005ALL;
            *((u16 *)name + 17) = 1;
            *((u32 *)name + 18) = 1065353216;
            v8 = *((u32 *)name + 25);
            if (v8 == 1)
            {
              *((u32 *)name + 11) = 0;
              *((u32 *)name + 12) = 0;
              *((u16 *)name + 17) = 2;
              v8 = 1;
              v53 = *(u64 *)(name + 36);
              *((u32 *)name + 18) = 1060320051;
              *(u64 *)(name + 36) = v53 & 0xFFFFFF00FFFFFFLL;
            }
            if (!v8)
              *((u32 *)name + 5) = 0;
          }
          continue;
        case 1:
          if ((wk->status2 & 2) == 0)
          {
            v17 = *((u32 *)name + 11);
            v18 = COUNT_UP_360(v17, 2);
            v19 = *((u32 *)name + 12);
            *((u32 *)name + 11) = v18;
            if (v19 <= 179)
            {
              v19 = COUNT_UP_360(v19, 2);
              *((u32 *)name + 12) = v19;
            }
            v20 = *((f32 *)name + 5);
            v21 = GET_360toSIN((f32)v19, 0.1, 5.0);
            v23 = v20 + (f32)(v21 * -0.8);
            if (!*((u32 *)name + 25))
              v23 = 0.0;
            *((f32 *)name + 5) = v23;
            v24 = *((u32 *)name + 20);
            UnitMng = wk->UnitMng;
            v26 = sBtlSearchUnit_ID(UnitMng, v24);
            if (v26)
            {
              v28 = v26;
              v29 = *((u32 *)name + 24);
              *(u64 *)&v55.x = 0;
              *(u64 *)&v55.z = 0;
              sBtlCalcAnim_DmgNumPos(v28, v29, &v55);
              *((u32 *)name + 4) = LODWORD(v55.x);
              *((u32 *)name + 6) = LODWORD(v55.z);
            }
            if (*((s32 *)name + 11) >= 180)
            {
              v4 = 5;
              *((u32 *)name + 11) = 0;
              goto LABEL_20;
            }
          }
          continue;
        case 2:
          if (!sBtlCheckSetsuma())
            goto LABEL_86;
          if (!sBtlCheckSetsumaEnd())
          {
            *((u32 *)name + 11) = -2;
            v42 = (name + 44);
LABEL_92:
            *(u64 *)(name + 36) &= 0xFFFFFF00FFFFFFuLL;
            if (*v42 >= 4)
              goto LABEL_126;
            continue;
          }
LABEL_86:
          v42 = (name + 44);
          v41 = *((u32 *)name + 11);
          *((u32 *)name + 11) = v41 + 1;
          switch (v41)
          {
            case -3:
            case -2:
              goto LABEL_92;
            case -1:
            case 0:
              v43 = *(u64 *)(name + 36);
              v44 = 1062333317;
              LODWORD(v45) = v43 & 0xFFFFFF | 0x40000000;
              HIDWORD(v45) = HIDWORD(v43) & 0xFFFFFF | 0x40000000;
              break;
            case 1:
              v51 = *(u64 *)(name + 36);
              v44 = 1060991140;
              LODWORD(v45) = v51 & 0xFFFFFF | 0x50000000;
              HIDWORD(v45) = HIDWORD(v51) & 0xFFFFFF | 0x50000000;
              break;
            case 2:
              v52 = *(u64 *)(name + 36);
              v44 = 1059648963;
              LODWORD(v45) = v52 & 0xFFFFFF | 0x60000000;
              HIDWORD(v45) = HIDWORD(v52) & 0xFFFFFF | 0x60000000;
              break;
            default:
              v50 = *(u64 *)(name + 36);
              v44 = 1058306785;
              LODWORD(v45) = v50 & 0xFFFFFF | 0x70000000;
              HIDWORD(v45) = HIDWORD(v50) & 0xFFFFFF | 0x70000000;
              break;
          }
          *(u64 *)(name + 36) = v45;
          *((u32 *)name + 18) = v44;
          if (*v42 >= 4)
          {
LABEL_126:
            v4 = 3;
            *((u32 *)name + 11) = 0;
            goto LABEL_20;
          }
          break;
        case 3:
          v30 = *(u64 *)(name + 36);
          *((u32 *)name + 18) = 1056964608;
          v31 = *((u32 *)name + 11) + 1;
          v32 = *((u32 *)name + 11) - 19 < 0;
          *((u32 *)name + 11) = v31;
          LODWORD(v30) = v30 & 0xFFFFFF | 0x80000000;
          HIDWORD(v30) = HIDWORD(v30) & 0xFFFFFF | 0x80000000;
          *(u64 *)(name + 36) = v30;
          if (v32 != __OFSUB__(v31, 20))
            continue;
          v4 = 4;
          *((u32 *)name + 11) = 0;
          goto LABEL_20;
        case 4:
          v33 = *((f32 *)name + 5) + -1.0;
          v34 = *((u32 *)name + 11);
          *((u32 *)name + 11) = v34 + 1;
          *((f32 *)name + 5) = v33;
          switch (v34)
          {
            case 12:
              v35 = *(u64 *)(name + 36);
              LODWORD(v35) = v35 & 0xFFFFFF | 0x60000000;
              HIDWORD(v35) = HIDWORD(v35) & 0xFFFFFF | 0x60000000;
              *(u64 *)(name + 36) = v35;
              if (*((s32 *)name + 11) >= 17)
                goto LABEL_18;
              break;
            case 13:
              v47 = *(u64 *)(name + 36);
              LODWORD(v47) = v47 & 0xFFFFFF | 0x40000000;
              HIDWORD(v47) = HIDWORD(v47) & 0xFFFFFF | 0x40000000;
              *(u64 *)(name + 36) = v47;
              if (*((s32 *)name + 11) >= 17)
                goto LABEL_18;
              break;
            case 14:
              v48 = *(u64 *)(name + 36);
              LODWORD(v48) = v48 & 0xFFFFFF | 0x20000000;
              HIDWORD(v48) = HIDWORD(v48) & 0xFFFFFF | 0x20000000;
              *(u64 *)(name + 36) = v48;
              if (*((s32 *)name + 11) >= 17)
                goto LABEL_18;
              break;
            case 15:
              v49 = *(u64 *)(name + 36);
              LODWORD(v49) = v49 & 0xFFFFFF | 0x10000000;
              HIDWORD(v49) = HIDWORD(v49) & 0xFFFFFF | 0x10000000;
              *(u64 *)(name + 36) = v49;
              if (*((s32 *)name + 11) >= 17)
                goto LABEL_18;
              break;
            case 16:
              *(u64 *)(name + 36) &= 0xFFFFFF00FFFFFFuLL;
              if (*((s32 *)name + 11) >= 17)
                goto LABEL_18;
              break;
            default:
              v46 = *(u64 *)(name + 36);
              *((u32 *)name + 18) = 1056964608;
              LODWORD(v46) = v46 & 0xFFFFFF | 0x80000000;
              HIDWORD(v46) = HIDWORD(v46) & 0xFFFFFF | 0x80000000;
              *(u64 *)(name + 36) = v46;
              if (*((s32 *)name + 11) >= 17)
              {
LABEL_18:
                *((u32 *)name + 11) = 0;
                goto LABEL_19;
              }
              break;
          }
          continue;
        case 5:
          if (*((u32 *)name + 25))
            v36 = 0x8000000;
          else
            v36 = 0x10000000;
          v37 = *(u64 *)(name + 36) & 0xFF000000;
          v38 = v37 >= v36;
          v40 = v37 - v36;
          v39 = v40 != 0 && v38;
          if (!v38)
            v40 = 0;
          *(int8x8_t *)(name + 36) = vorr_s8(vdup_n_s32(v40), (int8x8_t)(*(u64 *)(name + 36) & 0xFFFFFF00FFFFFFLL));
          if (v39)
            continue;
LABEL_19:
          v4 = 6;
LABEL_20:
          *((u16 *)name + 17) = v4;
          continue;
        default:
          v11 = *((s16 *)name + 16);
          dmgList = wk->dmgList;
          v13 = dmgList->unit[v11];
          v15 = v13->wk;
          p_fields = &v13->fields;
          if (v15)
          {
            p_fields->wk = 0;
          }
          continue;
      }
    }
  }
  return 1;
}

// 0x2039260
static u32 AlfDown(SBTLDMG_ANIMWORK *wk, u32 decval) {
  u32 v3;
  bool v4;
  u32 v5;

  v3 = *(u64 *)&wk->rgba & 0xFF000000;
  v4 = v3 >= decval;
  v5 = v3 - decval;
  if (!v4)
    v5 = 0;
  *(int8x8_t *)&wk->rgba = vorr_s8(vdup_n_s32(v5), (int8x8_t)(*(u64 *)&wk->rgba & 0xFFFFFF00FFFFFFLL));
  return v5;
}

// 0x2039240
static void AlfSet(SBTLDMG_ANIMWORK *wk, u32 alp) {
  *(int8x8_t *)&wk->rgba = vorr_s8((int8x8_t)(*(u64 *)&wk->rgba & 0xFFFFFF00FFFFFFLL), vdup_n_s32(alp));
}

// 0x2039290
bool sBtlDrawAnimList(void) {
  s64 v3;
  f32 v4;
  f32 v5;
  f32 v6;
  f32 v7;
  f32 v8;
  s32 v9;
  s32 v10;
  const char *name;
  s32 v13;
  s32 v14;
  s32 v15;
  s32 v16;
  u32 v17;
  u32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  s32 v29;
  s32 v32;
  u32 v35;
  f32 v36;
  u32 v37;
  s32 v38;
  sdfVector4_t v40;
  sdfVector4_t v41;
  sdfVector4_t v42;

  if (!wk)
    return 0;
  if (!wk->dmgList)
    return 0;
  if ((wk->status2 & 0x20) == 0)
  {
    v3 = 32;
    while (1)
    {
      name = (*(Il2CppClass **)((char *)&wk->dmgList->unit->obj.klass + v3))->_1.name;
      if (!name || (u32)(*((s16 *)name + 17) - 1) > 4)
        goto LABEL_17;
      v13 = *((u32 *)name + 15);
      if (v13 < 1 || *((u32 *)name + 25))
        break;
      *((u32 *)name + 14) += v13;
      v14 = *((u32 *)name + 13);
      v15 = *((u32 *)name + 14);
      if (v14 <= v15)
        goto LABEL_25;
LABEL_26:
      v16 = *((u32 *)name + 21);
      v18 = *((u32 *)name + 9);
      v17 = *((u32 *)name + 10);
      if (v16 == 1)
      {
        v4 = *((f32 *)name + 4);
        v5 = *((f32 *)name + 5);
        v6 = *((f32 *)name + 6);
        v7 = *((f32 *)name + 7);
        v8 = *((f32 *)name + 18);
        v9 = *((u32 *)name + 22);
        v10 = *((u32 *)name + 23);
        v40.x = v4;
        v40.y = v5;
        v40.z = v6;
        v40.w = v7;
        sBtlDamagePanelN(v40, v15, v18, v17, v9, v10, v8);
      }
      else if (v16)
      {
        v25 = *((f32 *)name + 4);
        v24 = *((f32 *)name + 5);
        v27 = *((f32 *)name + 6);
        v26 = *((f32 *)name + 7);
        v28 = *((f32 *)name + 18);
        v29 = *((u32 *)name + 25);
        if (v29)
        {
          v42.x = v25;
          v42.y = v24;
          v32 = v15;
          v42.z = v27;
          v42.w = v26;
          v35 = v18;
          v36 = v28;
          v37 = v17;
          v38 = v29;
        }
        else
        {
          v42.x = v25;
          v42.y = v24;
          v32 = v15;
          v42.z = v27;
          v42.w = v26;
          v35 = v18;
          v37 = v17;
          v36 = v28;
          v38 = 0;
        }
        sBtlDamagePanelE(v42, v32, v35, v37, v36, v38, 0);
      }
      else
      {
        v19 = *((f32 *)name + 4);
        v20 = *((f32 *)name + 5);
        v21 = *((f32 *)name + 6);
        v22 = *((f32 *)name + 7);
        v23 = *((f32 *)name + 18);
        v41.x = v19;
        v41.y = v20;
        v41.z = v21;
        v41.w = v22;
        sBtlDamagePanelR(v41, v15, v18, v17, v23);
      }
LABEL_17:
      v3 += 8;
      if (v3 == 352)
        return 1;
    }
    v14 = *((u32 *)name + 13);
    v15 = *((u32 *)name + 14);
    if (v14 > v15)
      goto LABEL_26;
LABEL_25:
    v15 = v14;
    *((u32 *)name + 14) = v14;
    *((u32 *)name + 15) = 0;
    goto LABEL_26;
  }
  return 0;
}

// 0x2039590
void sBtlChangePosToDevil(s32 devilid) {
  s64 v3;
  SBATTLE_WORK *wk_local;
  const char *name;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v9;
  SBTLUNIT_WORK *v10;
  sdatUnitWork_t *para;
  SBTLVISUAL_DATA *v12;
  f32 z;
  struct sdfVector4_t v16;

  v3 = 32;
  while (1)
  {
    wk_local = wk;
    name = (*(Il2CppClass **)((char *)&wk_local->dmgList->unit->obj.klass + v3))->_1.name;
    if (name)
    {
      UnitMng = wk_local->UnitMng;
      v9 = *((u32 *)name + 20);
      v10 = sBtlSearchUnit_ID(UnitMng, v9);
      if (v10)
      {
        para = v10->para;
        if (para)
        {
          if (para->devilid == devilid)
            break;
        }
      }
    }
    v3 += 8;
    if (v3 == 352)
      return;
  }
  v12 = Allocate(SBTLVISUAL_DATA);
  sBtlGetCylinderData(v10, v12);
  v16 = v12->center;
  goto LABEL_20;
LABEL_21:
  vct_A = v16;
  goto LABEL_22;
LABEL_20:
  goto LABEL_21;
LABEL_22:
  z = vct_A.z;
  *((u64 *)name + 2) = *(u64 *)&vct_A.x;
  *((f32 *)name + 6) = z;
}

// 0x2039820
SBTLDMG_HITLISTWORK *sBtlCreateHitList(void) {
  SBTLDMG_HITLISTWORK *v1;

  v1 = (SBTLDMG_HITLISTWORK *)Allocate(SBTLDMG_HITLISTWORK);
  _ctor(v1, 0);
  v1->num = 0;
  v1->wk = 0;
  v1->serialID = 1;
  return v1;
}

// 0x20398a0
bool sBtlLoadAttackHitData_Decode(SBTLUNIT_WORK *wk) {
  s64 i;
  SBATTLE_WORK *v7;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  SBTLUNIT_WORK *pUnit;
  s32 battlemode;
  s32 v13;
  SBTLSKLHIT_PACLIST *hitwk;

  for (i = 0; ; ++i)
  {
    v7 = wk;
    UnitMng = v7->UnitMng;
    number = UnitMng->number;
    if (i >= number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((u32)(pUnit->mode - 1) >= 2 && (!wk || wk->ListID == pUnit->ListID))
    {
      if ((pUnit->side & 0x80) != 0)
      {
        battlemode = (u16)v7->battlemode;
        if (!battlemode)
          goto LABEL_24;
        goto LABEL_9000;
        if (!wk->battlemode)
        {
LABEL_24:
          if ((pUnit->status & 0x800) != 0)
            continue;
          hitwk = pUnit->hitwk;
          if ((hitwk->status & 1) == 0)
          {
            ClassCopy(hitwk, playerhit->hitwk, 0);
            pUnit->hitwk->status |= 2u;
          }
          continue;
        }
LABEL_9000:
LABEL_5:
        if (!sBtlLoadAttackHitData(pUnit, (s32)0))
          return i >= number;
        continue;
      }
      else
      {
        goto LABEL_5;
      }
      if (!sBtlLoadAttackHitData(pUnit, v13, 0))
        return i >= number;
    }
  }
  return i >= number;
}

// 0x203a050
bool sBtlSearchAttackHitData_Copy(SBTLUNIT_WORK *wk) {
  u32 v3;
  SBTLSKLHIT_PACLIST *hitwk;
  SBTLSKLHIT_PACLIST *v6;
  s64 v7;
  s64 v8;
  SBTLSKILLHIT_TBL *v9;
  SBTLSKLHIT_PACDATAWORK *pwk;
  SBTLSKLHIT_PACDATAWORK *v11;
  s64 v12;
  SBTLPACDATA_WORK *v14;
  SBTLSKLHIT_PACLIST *v15;
  s64 v16;
  SBTLSKILLHIT_TBL *v17;

  v3 = sBtlSearchPacData(wk->major, wk->minor, wk->para->devilid);
  if ((v3 & 0x80000000) == 0)
  {
    hitwk = wk->hitwk;
    v6 = wk->hitwk;
    hitwk->num = wk3->pacdata[v3]->hitwk->num;
    if (v6->num >= 1)
    {
      v7 = 0;
      v8 = 32;
      do
      {
        pwk = v6->pwk;
        v11 = Allocate(SBTLSKLHIT_PACDATAWORK);
        _ctor(v11, 0);
        *(Il2CppClass **)((char *)&pwk->obj.klass + v8) = v11;
        v12 = *(s64 *)((char *)&wk->hitwk->pwk->obj.klass + v8);
        if (wk3)
        {
          v14 = wk3->pacdata[v3];
          if (v14)
          {
            v15 = v14->hitwk;
            if (v15)
            {
              v16 = *(s64 *)((char *)&v15->pwk->obj.klass + v8);
              if (v16)
              {
                v17 = *(SBTLSKILLHIT_TBL *)(v16 + 40);
                if (v17)
                {
                  v9 = Clone(v17, 0);
                  goto LABEL_9;
                }
              }
            }
          }
        }
        v9 = 0;
LABEL_9:
        *(u64 *)(v12 + 40) = v9;
        v6 = wk->hitwk;
        ++v7;
        v8 += 8;
      }
      while (v7 < v6->num);
    }
    v6->status |= 1u;
  }
  return (v3 & 0x80000000) == 0;
}

// 0x203a250
s32 sBtlSearchAttackHitData_Num(SBTLUNIT_WORK *wk) {
  s32 v3;
  s32 v4;

  v3 = sBtlSearchPacData(wk->major, wk->minor, wk->para->devilid);
  if (v3 < 0)
    return 0;
  v4 = v3;
  return wk3->pacdata[v4]->hitwk->num;
}

// 0x203a300
bool sBtlLoadAttackHitData_pData(s32 index, void *pData) {
  do
  {
  }
  while (!sBtlLoadAttackHitData(playerhit, (s32)pData, pData));
  return 1;
}

// 0x203a380
bool sBtlInitLoadAttackHitData_pData(void) {
  SBTLUNIT_WORK *v1;

  v1 = Allocate(SBTLUNIT_WORK);
  _ctor(v1, 0);
  playerhit = v1;
  return 1;
}

// 0x203a420
bool sBtlForceDelete_AttackHitData(void) {
  SBTLUNIT_WORK *playerhit_local;
  SBTLSKLHIT_PACLIST *hitwk;
  s64 v4;
  s64 v5;
  s64 v6;
  s64 v7;
  s64 v8;

  playerhit_local = playerhit;
  hitwk = playerhit_local->hitwk;
  if ((hitwk->status & 3) == 1)
  {
    if (hitwk->num >= 1)
    {
      v4 = 4;
      do
      {
        v5 = *((u64 *)&hitwk->pwk->obj.klass + v4);
        *(u64 *)(v5 + 16) = 0;
        v6 = *((u64 *)&playerhit_local->hitwk->pwk->obj.klass + v4);
        *(u64 *)(v6 + 32) = 0;
        v7 = *((u64 *)&playerhit_local->hitwk->pwk->obj.klass + v4);
        *(u64 *)(v7 + 40) = 0;
        hitwk = playerhit_local->hitwk;
        v8 = v4 - 3;
        ++v4;
      }
      while (v8 < hitwk->num);
    }
    hitwk->status = 0;
  }
  return 1;
}

// 0x2039ac0
static bool SetAttackHitData_pData(SBTLUNIT_WORK *wk, s32 index) {
  SBTLSKLHIT_PACLIST *hitwk;

  if ((wk->status & 0x800) == 0)
  {
    hitwk = wk->hitwk;
    if ((hitwk->status & 1) == 0)
    {
      ClassCopy(hitwk, playerhit->hitwk, 0);
      wk->hitwk->status |= 2u;
    }
  }
  return 1;
}

// 0x2039b60
bool sBtlLoadAttackHitData(SBTLUNIT_WORK *wk, s32 id, void *ppData) {
  SBTLSKLHIT_PACLIST *hitwk;
  u32 status;
  s32 gstat;
  s32 max_length;
  s64 v10;
  s64 v11;
  SBTLSKLHIT_PACDATAWORK *v12;
  void *v13;
  SBTLSKLHIT_PACDATAWORK *v14;
  SBTLSKLHIT_PACDATAWORK *v15;
  Il2CppObject *v19;
  char *v20;
  void *Ctrl_k__BackingField;
  char *v25;
  void *Asset;
  sdfBinary *v27;
  SBTLSKLHIT_PACLIST *v28;
  s32 S32;
  s64 v30;
  s64 v31;
  s64 v32;
  SBTLSKILLHIT_TBL *v33;
  SBTLSKLHIT_PACDATAWORK *pwk;
  SBTLSKLHIT_PACDATAWORK *v35;
  fileHandle_t *hFile;
  long f64 v37;
  fileHandle_t *v38;
  SBTLSKLHIT_PACLIST *v39;
  s32 data;

  if ((wk->status & 0x800) != 0)
    return 1;
  hitwk = wk->hitwk;
  status = hitwk->status;
  if ((status & 1) != 0)
    return 1;
  if ((wk->side & 0x80) != 0)
  {
LABEL_36:
    hitwk->status = status | 1;
    return 1;
  }
  gstat = (u16)hitwk->gstat;
  if (ppData && !hitwk->gstat)
  {
    hitwk->gstat = 1;
    goto LABEL_9;
  }
  if (gstat == 100)
  {
    data = wk->minor;
    v19 = Box(s32, &data);
    v20 = Format("p{0:x3}", v19, 0);
    Load(Dependent, v20, v20);
    LoadSyncAll(_Ctrl_k__BackingField, 0);
    Ctrl_k__BackingField = _Ctrl_k__BackingField;
    v25 = Concat_54766928(v20, ".MHT", 0);
    Asset = LoadAsset(Ctrl_k__BackingField, v20, v25, 0);
    v27 = Allocate(sdfBinary);
    _ctor(v27, Asset, 0);
    v28 = wk->hitwk;
    S32 = ReadS32(v27, 0);
    hitwk = wk->hitwk;
    v28->num = S32;
    if (hitwk->num >= 1)
    {
      v30 = 0;
      v31 = 32;
      while (1)
      {
        pwk = hitwk->pwk;
        v35 = Allocate(SBTLSKLHIT_PACDATAWORK);
        _ctor(v35, 0);
        if (v35)
        {
            break;
        }
        *(Il2CppClass **)((char *)&pwk->obj.klass + v31) = v35;
        v32 = *(s64 *)((char *)&wk->hitwk->pwk->obj.klass + v31);
        v33 = Allocate(SBTLSKILLHIT_TBL);
        _ctor_32244496(v33, v27, 0);
        *(u64 *)(v32 + 40) = v33;
        hitwk = wk->hitwk;
        ++v30;
        v31 += 8;
        if (v30 >= hitwk->num)
          goto LABEL_35;
      }
    }
    goto LABEL_35;
  }
  if (gstat == 1)
  {
    if (!ppData)
    {
      hFile = hitwk->hFile;
      if (!fileCheckEnd(hFile))
        return 0;
      v38 = wk->hitwk->hFile;
      ppData = *(void **)(sub_83F0(v38->topPtr, Project_libsdf_sdfResourcePack, v37) + 24);
      fileHandleFree(wk->hitwk->hFile);
      v39 = wk->hitwk;
      v39->hFile = 0;
      hitwk = wk->hitwk;
    }
LABEL_9:
    max_length = ppData->max_length;
    hitwk->num = max_length;
    if (max_length >= 1)
    {
      v10 = 0;
      v11 = 32;
      do
      {
        v12 = hitwk->pwk;
        v13 = *(void *)((char *)&ppData->obj.klass + v11);
        v14 = Allocate(SBTLSKLHIT_PACDATAWORK);
        v15 = v14;
        _ctor_32245808(v14, v13, 0);
        *(Il2CppClass **)((char *)&v12->obj.klass + v11) = v15;
        hitwk = wk->hitwk;
        ++v10;
        v11 += 8;
      }
      while (v10 < hitwk->num);
    }
LABEL_35:
    status = hitwk->status;
    goto LABEL_36;
  }
  if (!hitwk->gstat)
  {
    if (!wk->major)
    {
      hitwk->gstat = 100;
      return 0;
    }
    goto LABEL_36;
  }
  return 0;
}

// 0x203a520
bool sBtlDeleteAttackHitData(SBTLUNIT_WORK *wk) {
  SBTLSKLHIT_PACLIST *hitwk;
  s64 v4;
  s64 v5;
  s64 v6;
  s64 v7;
  s64 v8;

  hitwk = wk->hitwk;
  if ((hitwk->status & 3) == 1)
  {
    if (hitwk->num >= 1)
    {
      v4 = 4;
      do
      {
        v5 = *((u64 *)&hitwk->pwk->obj.klass + v4);
        *(u64 *)(v5 + 16) = 0;
        v6 = *((u64 *)&wk->hitwk->pwk->obj.klass + v4);
        *(u64 *)(v6 + 32) = 0;
        v7 = *((u64 *)&wk->hitwk->pwk->obj.klass + v4);
        *(u64 *)(v7 + 40) = 0;
        hitwk = wk->hitwk;
        v8 = v4 - 3;
        ++v4;
      }
      while (v8 < hitwk->num);
    }
    hitwk->status = 0;
  }
  return 1;
}

// 0x203a5e0
void sBtlDltHit_by_UnitSkl(SBTLDMG_HITLISTWORK *lwk, s32 unitID, SKLID sklID) {
  SBTLDMG_HITWORK *wk;

  wk = lwk->wk;
  if (wk && lwk->num)
  {
    do
    {
      if (wk->acterID == unitID && wk->skillid == sklID)
        wk->st = 2;
      wk = wk->next;
    }
    while (wk);
  }
}

// 0x203a630
s32 sBtlCreateHitC_New(SBTLDMG_HITLISTWORK *lwk, SBTLUNIT_WORK *wk, SBTLEFF_WORK *ewk, s32 acterID, SKLID skillid, SBTLSKILLP_TBL *tbl, SBTLSKILLHIT_TBL *hittbl, SBTLSKLHIT_PACDATAWORK *pwk, SBTLUNIT_SIDE acterside, s32 serialID2) {
  SBTLDMG_HITWORK *v17;
  s32 ListID;
  f32 dir;
  SBTLEFF_WORK *v21;
  SBTLDMG_HITWORK *huka2hwk;
  SBTLCALC_DMGWORK_A *v23;
  SBTLUNIT_LISTWORK *UnitList;
  s32 v26;
  SBTLCALC_DMGWORK_A *v27;
  sdatUnitWork_t *para;
  s16 devilid;
  int32x2_t *now;
  f32 x;
  f32 y;
  f32 z;
  s32 workID;
  char BEDtype;
  SBTLUNIT_WORK *v36;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v39;
  u32 *v41;
  SBTLDMG_HITWORK *next;
  SBTLDMG_HITWORK *v43;
  s32 v45;
  f32 rad;
  u8 *v49;
  u16 area;
  s64 v51;
  SBTLDMG_CYLINDERWORK *v52;
  SBTLDMG_CYLINDERWORK *cy;
  f32 height;
  s64 v55;
  f32 v56;
  f32 v57;
  sdfVector4_t *v58;
  SBTLSKILLHIT_POSWORK *start;
  u16 type;
  f32 v61;
  f32 v62;
  f32 v63;
  s32 minor;
  SBTLDMG_CYLINDERWORK *v65;
  float32x2_t v70;
  f32 v71;
  float32x2_t v75;
  f32 v76;
  float32x2_t *static_fields;
  float32x2_t *v79;
  f32 v80;
  f32 v81;
  u64 v82;
  s32 v83;
  u32 flg;
  plistHandle_t *v85;
  SBTLEFF_EFFTIME *time;
  f32 life;
  float32x2_t v88;
  s32 v89;
  s32 result;
  SBTLSKILLHIT_POSWORK *v91;
  SBTLSKILLHIT_POSWORK *end;
  u16 v93;
  sdfVector4_t *v94;
  sdfVector4_t *v95;
  sbtldmg_idouwork_tag *v98;
  s64 v99;
  struct sdfVector4_t v101;
  sdfVector4_t *v102;
  sdfVector4_t *v103;
  sbtldmg_idouwork_tag *v105;
  f32 v106;
  f32 v107;
  f32 v108;
  f32 v109;
  f32 v110;
  f32 v111;
  f32 v112;
  f32 v113;
  s32 hitmdl_serialID;
  dds3ModelResrc_t *v119;
  s32 v121;
  void *BpData;
  s32 v123;
  u32 v124;
  dds3Basic_t *v125;
  u64 *v126;
  void *v128;
  dds3ModelHandle_t *v129;
  sdfVector4_t *v133;
  sdfVector4_t *v134;
  sdfVector4_t *v135;
  sdfVector4_t v136;
  sdfVector4_t *v137;
  sdfVector4_t *v138;
  s32 v139;
  struct sdfVector4_t v140;
  sdfVector4_t *v141;
  sdfVector4_t *v142;
  dds3ModelHandle_t *v143;
  __int128 v145;
  sdfVector4_t *v147;
  sdfVector4_t *v148;
  void *v153;
  void *v154;
  dds3ModelHandle_t *v155;
  sdfVector4_t *v157;
  sdfVector4_t v158;
  struct sdfVector4_t rot;
  SBTLDMG_HITLISTWORK *v162;
  s32 IDa[4];
  sdfVector4_t *IDb;
  s32 IDf[4];
  s32 IDc[4];
  dds3Basic_t *pBasic;
  sdfVector4_t rott;
  sdfMatrix4_t v173;
  sdfMatrix4_t v174;
  sdfVector4_t v175;
  sdfVector4_t v176;
  sdfVector4_t v178;
  sdfVector4_t v179;

  pBasic = 0;
  *(u64 *)&rott.x = 0;
  *(u64 *)&rott.z = 0;
  v17 = Allocate(SBTLDMG_HITWORK);
  _ctor(v17, 0);
  ListID = wk->ListID;
  v17->skillid = skillid;
  v17->acterID = ListID;
  v17->actID = acterID;
  *(u64 *)&v17->starttime = *(u64 *)&hittbl->starttime;
  v17->targetflg = hittbl->targetflg;
  v17->shatei = hittbl->shatei;
  dir = hittbl->dir;
  *(u16 *)&v17->fKaraburi = 257;
  v17->dir = dir;
  v17->actioncnt = tbl->count;
  v17->targetID = wk->actaiwk->targetID;
  if (serialID2 == -1)
  {
    v27 = v17->awk;
    v27->aside = acterside;
    v21 = ewk;
    para = wk->para;
    devilid = para->devilid;
    v27->aListID = ListID;
    v27->adevilid = devilid;
    v27->alevel = para->level;
    now = para->now;
    v27->aatk = now[4].n64_i16[0];
    v27->atec = now[4].n64_i16[2];
    *(float32x2_t *)&v27->ahp = vcvt_f32_s32(now[2]);
    goto LABEL_11;
  }
  v21 = ewk;
  huka2hwk = wk->huka2hwk;
  if (huka2hwk)
  {
    v23 = v17->awk;
    huka2hwk = wk->huka2hwk;
    ClassCopy(v23, huka2hwk->awk, 0);
  }
LABEL_11:
  UnitList = sBtlCreateUnitList(24);
  v17->hitlwk = UnitList;
  if (v17->actioncnt < 1)
    v26 = 0;
  else
    v26 = v17->life / (s32)v17->actioncnt;
  v17->actionf = v26;
  ClassCopy(v17->start, hittbl->start, 0);
  ClassCopy(v17->end, hittbl->end, 0);
  v17->hittbl = hittbl;
  x = hittbl->x;
  v17->x = x;
  y = hittbl->y;
  v17->y = y;
  z = hittbl->z;
  v17->z = z;
  sBtlDrawLineX_PS2(x, y, z, 100.0, 0x80FF0000);
  v162 = lwk;
  v17->hitbk_cnt = (f32)tbl->hitbk_cnt;
  v17->hitbk_rate = tbl->hitbk_rate;
  if (v21)
  {
    workID = v21->workID;
    BEDtype = v21->BEDtype;
  }
  else
  {
    workID = 0;
    BEDtype = 1;
  }
  v17->workID = workID;
  v17->BEDtype = BEDtype;
  v17->lwk = 0;
  v17->prev = 0;
  v17->next = 0;
  v17->hModel = 0;
  v155 = &v17->hModel;
  v17->pBasic = 0;
  v154 = &v17->pBasic;
  v17->hEveUnit = 0;
  v153 = &v17->hEveUnit;
  v17->hPartsList = 0;
  v36 = wk;
  if (skillid == 285)
  {
    UnitMng = wk->UnitMng;
    v39 = sBtlSearchUnit_ID(UnitMng, acterID);
    if (v39)
      v36 = v39;
    else
      v36 = wk;
  }
  *(sdfVector4_t *)IDa = v36->rot;
  vct_A = *(sdfVector4_t *)IDa;
  IDb = &v17->rot;
  *IDb = vct_A;
  v41 = v17->acterpos;
  v41[8] = LODWORD(v36->pos.x);
  v41[9] = LODWORD(v36->pos.y);
  v41[10] = LODWORD(v36->pos.z);
  next = v162->wk;
  if (next)
  {
    do
    {
      v43 = next;
      next = next->next;
    }
    while (next);
    v43->next = v17;
    v17->prev = v43;
    v45 = v162->num + 1;
  }
  else
  {
    v162->wk = v17;
    v45 = 1;
  }
  v162->num = v45;
  v17->skillflg = tbl->flg;
  *(u32 *)&v17->type = *(u32 *)&tbl->type;
  v17->attr_flg = tbl->attr;
  v17->atype = hittbl->area_type;
  rad = hittbl->rad;
  if (wk->para->devilid == 25 && skillid == 154)
    rad = -1.01;
  v17->rad = rad;
  v17->rad_area = hittbl->rad_area;
  *(int32x2_t *)&v17->area_r = vrev64_s32(*(int32x2_t *)&hittbl->area_r2);
  if (wk->encountno == 22)
  {
    if (v17->skillid == 152 && wk->para->devilid == 164)
      *(float32x2_t *)&v17->area_r = vadd_f32(*(float32x2_t *)&v17->area_r, *(float32x2_t *)&v17->area_r);
  }
  if (!v21)
  {
    v17->eListID = -1;
    v17->acterside = acterside;
    v49 = &v17->tchangeflg;
    area = tbl->area;
    goto LABEL_59;
  }
  v17->eListID = v21->eListID;
  if ((v21->flg & 0x100) != 0)
    v17->flg |= 0x40u;
  v17->acterside = acterside;
  v49 = &v17->tchangeflg;
  area = tbl->area;
LABEL_59:
  v17->side = sBtlGetSide(wk, area, acterside, v49);
  v17->flg |= hittbl->flg;
  v51 = *(u64 *)&hittbl->sokudo;
  *(u64 *)&v17->sokudo = v51;
  *(u32 *)&v17->spd = v51;
  v17->hittype = hittbl->type;
  v52 = v17->cy;
  cy = hittbl->cy;
  v52->scale = cy->scale;
  height = cy->height;
  v52->height = height;
  v55 = *(u64 *)&cy->area_r;
  *(u64 *)&v52->area_r = v55;
  if (skillid == 64)
  {
    v57 = 4.0;
  }
  else
  {
    if (skillid == 157)
    {
      v56 = 15.0;
    }
    else
    {
      if (skillid != 163)
        goto LABEL_69;
      v56 = 2.0;
    }
    v52->area_r = v56 * *(f32 *)&v55;
    v57 = 6.0;
  }
  v52->height = height * v57;
LABEL_69:
  v58 = &v17->pos;
  start = hittbl->start;
  type = tbl->type;
  v58 = &v17->pos;
  v157 = v58;
  sBtlSetHitPos(wk, v17, v21, start, v58, IDb, &rott, type);
  v62 = v17->pos.x;
  v61 = v17->pos.y;
  v63 = v17->pos.z;
  sBtlDrawLineX_PS2(v62, v61, v63, 100.0, 0x8000FF00);
  if (wk->major == 1)
  {
    minor = wk->minor;
    if (skillid == 149 && minor == 474)
      goto LABEL_79;
    if (skillid == 149 && minor == 475)
    {
      v65 = v17->cy;
      __asm { FMOV            V1.2S, #3.0 }
      v17->area_r = v17->area_r * 3.0;
      *(float32x2_t *)&v65->height = vmul_f32(*(float32x2_t *)&v65->height, _D1);
LABEL_79:
      v17->starttime *= 2;
      goto LABEL_84;
    }
  }
  if (skillid == 464)
  {
    *(f32 *)((u64)v17->cy + 20) = *(f32 *)((u64)v17->cy + 20) * 1.5;
  }
  else if (skillid == 463)
  {
    *(u32 *)((u64)v17->cy + 24) = 1140457472;
  }
LABEL_84:
  v70.n64_u64[0] = *(u64 *)&v17->x;
  v71 = v17->z;
  if ((*(u8 *)((char *)v17 + 105) & 0x10) != 0)
  {
    v158 = *IDb;
    goto LABEL_89;
  }
  else
  {
    v158 = rott;
    goto LABEL_89;
  }
LABEL_89:
  vct_A = v158;
  ToMatrix();
  v75.n64_u64[0] = vadd_f32(v70, 0).n64_u64[0];
  v76 = v71 + 0.0;
  static_fields[2].n64_u64[0] = v75.n64_u64[0];
  static_fields[3].n64_f32[0] = v76;
  static_fields[3].n64_u32[1] = 1065353216;
  get_transpose(&v174, &mtx_A, 0);
  v173 = v174;
  v176 = op_Multiply_60923920(&v173, vct_A, 0);
  vct_A = v176;
  v80 = v17->pos.z;
  v81 = v79[3].n64_f32[0];
  v82 = vadd_f32(v79[2], *(float32x2_t *)&v17->pos).n64_u64[0];
  v83 = v17->flg;
  *(u64 *)&v17->pos = v82;
  v17->pos.z = v81 + v80;
  if ((v83 & 0x80000) == 0)
  {
    flg = hittbl->flg;
    if ((flg & 0x400) == 0)
      goto LABEL_100;
LABEL_107:
    v17->homingpara = hittbl->homingpara;
    if ((flg & 0x100) == 0)
    {
LABEL_101:
      if ((*(u8 *)((char *)v17 + 105) & 0x20) == 0)
        goto LABEL_103;
      goto LABEL_102;
    }
    goto LABEL_108;
  }
  *(u64 *)&v17->pos = *(u64 *)&hittbl->x;
  v17->pos.z = hittbl->z;
  flg = hittbl->flg;
  if ((flg & 0x400) != 0)
    goto LABEL_107;
LABEL_100:
  if ((flg & 0x100) == 0)
    goto LABEL_101;
LABEL_108:
  if ((v83 & 0x1000) == 0)
  {
    v91 = v17->start;
    end = hittbl->end;
    v93 = tbl->type;
    sBtlSetHitEndPos(wk, v17, v21, hittbl, v91, end, &v17->endpos, v93);
    v99 = &v17->iwk;
    v98 = v17->iwk;
    v17->targetID = wk->actaiwk->targetID;
    v98->apos0_per = hittbl->apos1->per;
    v98->apos1_per = hittbl->apos2->per;
    rot = wk->rot;
    vct_A = rot;
    *IDb = vct_A;
    v101 = v17->pos;
    vct_A = v101;
    v102 = *(sdfVector4_t *)v99;
    v103 = v102 + 3;
    *(u64 *)&v175.x = hittbl;
    *v103 = vct_A;
    v105 = v17->iwk;
    *(u64 *)&v175.z = &v105->apos0;
    sBtlSetApos12(v17->pos, v17->endpos, v175, &v105->apos1, v94, v95);
    *(u32 *)&v17->spd = *(u32 *)&v17->sokudo;
    v106 = v17->pos.x;
    v107 = v17->pos.y;
    v108 = v17->pos.z;
    v109 = v17->pos.w;
    v110 = v17->endpos.x;
    v111 = v17->endpos.y;
    v112 = v17->endpos.z;
    v113 = v17->endpos.w;
    v178.x = v106;
    v178.y = v107;
    v178.z = v108;
    v178.w = v109;
    v179.x = v110;
    v179.y = v111;
    v179.z = v112;
    v179.w = v113;
    sBtlGetQuat(v178, v179);
    *IDb = vct_A;
    *(u32 *)(*(u64 *)v99 + 92) = 0;
    if ((*(u8 *)((char *)v17 + 105) & 0x20) == 0)
      goto LABEL_103;
LABEL_102:
    v85 = Create(pwk->EpData, 0);
    v17->hPartsList = v85;
    effPartsRotateSet(v17->hPartsList, v17->rot);
    effPartsPositionSet(v17->hPartsList, v17->pos);
    *(u32 *)&v17->EPL_counter = 0;
    time = pwk->time;
    v17->EPL_st_time = time->st_time;
    life = time->life;
    *(u32 *)&v17->EPL_alpha = 1124073472;
    v17->EPL_life = life;
    v88.n64_u64[0] = *(u64 *)&time->fin_time;
    *(u32 *)&v17->EPL_fout_time = v88.n64_u32[1];
    *(u32 *)&v17->EPL_fin_time = v88.n64_u32[0];
    *(int8x8_t *)&v17->EPL_in_alpha = vbsl_s8(vceqz_f32(v88), (int8x8_t)0x4300000043000000LL, vdiv_f32((float32x2_t)0x4300000043000000LL, v88));
    goto LABEL_103;
  }
  {
    hitmdl_serialID = wk->hitmdl_serialID;
    v119 = mdlSearchResrc(7u, hitmdl_serialID);
    if (!v119)
      break;
  }
  v121 = wk->hitmdl_serialID;
  BpData = pwk->BpData;
  mdlPackDecode(7u, v121, 257, BpData, 0);
  v123 = wk->hitmdl_serialID;
  v124 = UnitRegist(7u, v123);
  pBasic = dds3GetActiveScene();
  v125 = dds3SceneBasicSearch(pBasic, v124, 5u);
  *(u64 *)v154 = v125;
  v126 = *(u64 **)(*(u64 *)v154 + 48);
  v128 = v126[4];
  *(u64 *)v153 = v128;
  v129 = *(dds3ModelHandle_t *)(*(u64 *)v153 + 376);
  v155 = v129;
  *(u32 *)(*(u64 *)v153 + 420) |= 0x200000u;
  __asm { FMOV            V0.4S, #1.0 }
  v133 = v157;
  vct_A = _Q0;
  v134 = *(sdfVector4_t *)(*(u64 *)v154 + 56);
  v135 = v134 + 7;
  *v135 = vct_A;
  v136 = *IDb;
  goto LABEL_164;
LABEL_165:
  v138 = v137 + 6;
  goto LABEL_166;
LABEL_167:
  goto LABEL_168;
LABEL_169:
  v142 = v141 + 5;
  goto LABEL_170;
LABEL_164:
  vct_A = v136;
  v137 = *(sdfVector4_t *)(*(u64 *)v154 + 56);
  goto LABEL_165;
LABEL_166:
  v139 = (u8)byte_5755EF5;
  *v138 = vct_A;
  v140 = *v133;
  if (v139)
    goto LABEL_167;
  *(sdfVector4_t *)IDf = v140;
  v140 = *(sdfVector4_t *)IDf;
LABEL_168:
  vct_A = v140;
  v141 = *(sdfVector4_t *)(*(u64 *)v154 + 56);
  goto LABEL_169;
LABEL_170:
  *v142 = vct_A;
  v143 = v155;
  if (v155)
  {
    mdlHide(v143);
    mdlSetMotionSpeed(v155, 1.0);
  }
  v145 = *(_OWORD *)&v17->pos;
  v17->flg |= 0x1000u;
  *(_OWORD *)IDc = v145;
  vct_A = *(sdfVector4_t *)IDc;
  v147 = v17->iwk;
  v148 = v147 + 3;
  *v148 = vct_A;
  ++wk->hitmdl_serialID;
  *(f32 *)((u64)v17->iwk + 92) = 1.0 / (f32)v17->life;
  if ((*(u8 *)((char *)v17 + 105) & 0x20) != 0)
    goto LABEL_102;
LABEL_103:
  v89 = serialID2;
  result = v162->serialID;
  v17->serialID = result;
  if (serialID2 == -1)
    v89 = v162->serialID2;
  v17->serialID2 = v89;
  v17->st = 1;
  v162->serialID = result + 1;
  return result;
}

// 0x203ff60
bool sBtlCreateHitC_None(SBTLDMG_HITLISTWORK *lwk, SBTLUNIT_WORK *wk, SBTLUNIT_WORK *acter, SBTLDMG_HITWORK *twk, SKLID skillid, SBTLSKILLP_TBL *tbl, const sdfVector4_t *pos, s32 serialID2) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  s32 ListID;
  SBTLUNIT_LISTWORK *UnitList;
  SBTLDMG_HITWORK *huka2hwk;
  SBTLCALC_DMGWORK_A *v27;
  s32 actioncnt;
  s32 v29;
  SBTLCALC_DMGWORK_A *awk;
  sdatUnitWork_t *para;
  s16 level;
  int32x2_t *now;
  s32 v34;
  s32 hitbk_cnt;
  f32 v37;
  u32 v38;
  f32 *p_x;
  SBTLDMG_HITWORK *p_fields;
  s32 v42;
  struct sdfVector4_t rot;
  sdfVector4_t *p_rot;
  struct SDF_VU0 *v45;
  u16 type;
  u16 area;
  s32 side;
  s32 v50;
  s32 v53;
  struct sdfVector4_t v54;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  if (lwk)
  {
    ListID = acter->ListID;
    twk->skillid = skillid;
    twk->acterID = ListID;
    twk->actID = ListID;
    twk->actioncnt = tbl->count;
    UnitList = sBtlCreateUnitList(24);
    twk->hitlwk = UnitList;
    twk->targetID = wk->actaiwk->targetID;
    if (serialID2 == -1)
    {
      awk = twk->awk;
      awk->aside = acter->side;
      para = wk->para;
      awk->adevilid = para->devilid;
      awk->aListID = wk->ListID;
      level = para->level;
      now = para->now;
      awk->alevel = level;
      v34 = now[4].n64_i16[2];
      awk->aatk = now[4].n64_i16[0];
      awk->atec = v34;
      *(float32x2_t *)&awk->ahp = vcvt_f32_s32(now[2]);
      actioncnt = twk->actioncnt;
      if (actioncnt >= 1)
      {
LABEL_14:
        v29 = twk->life / (u16)actioncnt;
        goto LABEL_17;
      }
    }
    else
    {
      huka2hwk = wk->huka2hwk;
      if (huka2hwk)
      {
        huka2hwk = wk->huka2hwk;
        v27 = huka2hwk->awk;
        twk->awk = v27;
      }
      actioncnt = twk->actioncnt;
      if (actioncnt >= 1)
        goto LABEL_14;
    }
    v29 = 0;
LABEL_17:
    twk->actionf = v29;
    hitbk_cnt = tbl->hitbk_cnt;
    twk->hitbk_rate = tbl->hitbk_rate;
    v37 = hitbk_cnt;
    twk->hitbk_cnt = v37;
    if (v38)
    {
      goto LABEL_19;
    }
    else
    {
LABEL_19:
      goto LABEL_20;
    }
LABEL_20:
    p_x = &vf00.x;
    p_x[4] = x;
    p_x[5] = y;
    p_x[6] = z;
    p_x[7] = w;
    p_fields = &twk->fields;
    v42 = (u8)byte_5755EF5;
    p_fields->pos = vct_A;
    rot = wk->rot;
    if (v42)
      goto LABEL_23;
    goto LABEL_36;
    if (v53)
    {
LABEL_23:
      goto LABEL_24;
    }
LABEL_36:
    v54 = rot;
    rot = v54;
LABEL_24:
    vct_A = rot;
    p_rot = &twk->rot;
    *p_rot = vct_A;
    type = tbl->type;
    area = tbl->area;
    twk->skillflg = tbl->flg;
    LODWORD(v45) = tbl->attr;
    side = acter->side;
    twk->type = type;
    twk->area = area;
    twk->attr_flg = (u32)v45;
    twk->acterside = side;
    if (!(u32)v45)
    twk->side = sBtlGetSide(wk, area, side, &twk->tchangeflg);
    v50 = *(u64 *)&lwk->serialID;
    *(u64 *)&twk->serialID = *(u64 *)&lwk->serialID;
    lwk->serialID = v50 + 1;
    return lwk != 0;
  }
  return lwk != 0;
}

// 0x2040380
void sBtlAddSerialID2(void) {
  SBTLDMG_HITLISTWORK *hitList;
  s32 v3;

  hitList = wk->hitList;
  v3 = hitList->serialID2 + 1;
  hitList->serialID2 = v3;
  if (v3 >= 0x7FFF)
  {
    hitList = wk->hitList;
    hitList->serialID2 = 0;
  }
}

// 0x203edf0
bool sBtlSetApos12(const sdfVector4_t *startpos, const sdfVector4_t *endpos, const sdfVector4_t *rot, SBTLSKILLHIT_TBL *hittbl, sdfVector4_t *apos1, sdfVector4_t *apos2) {
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  sdfVector4_t *v12;
  s64 v13;
  s64 v16;
  s64 v17;
  f32 *p_x;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 *v23;
  f32 *v24;
  f32 *v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v30;
  f32 v32;
  f32 v33;
  f32 v34;
  u32 *v39;
  f32 v40;
  f32 v41;
  s32 v42;
  s32 v43;
  s32 v44;
  f32 v45;
  f32 v46;
  u32 *v47;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 *v53;
  f32 v54;
  f32 v55;
  s32 v59;
  f32 v61;
  u32 *v62;
  f32 v63;
  f32 v64;
  f32 *v65;
  f32 v66;
  f32 v69;
  s32 v70;
  s32 v73;
  f32 v79;
  struct sdfVector4_t v81;
  struct sdfVector4_t v82;
  s32 v83;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  struct sdfVector4_t v93;
  struct sdfVector4_t v94;
  struct sdfVector4_t v95;
  sdfMatrix4_t v96;
  sdfMatrix4_t v97;
  s64 v98;
  s64 v99;
  sdfVector4_t v100;
  sdfVector4_t v101;
  sdfVector4_t v102;
  sdfVector4_t v103;
  sdfVector4_t v104;
  sdfVector4_t v105;

  w = startpos->w;
  y = startpos->y;
  z = startpos->z;
  v7 = endpos->w;
  x = startpos->x;
  v8 = endpos->z;
  v9 = endpos->y;
  v10 = endpos->x;
  v12 = *(sdfVector4_t *)&rot->z;
  v13 = *(u64 *)&rot->x;
  v16 = v99;
  v17 = v98;
  *(u64 *)&vct_A.x = v17;
  *(u64 *)&vct_A.z = v16;
  p_x = &vf00.x;
  v21 = p_x[4];
  v20 = p_x[5];
  v22 = p_x[6];
  v79 = p_x[7];
  v23 = &vf00.x;
  v23[4] = v10;
  v23[5] = v9;
  v23[6] = v8;
  v23[7] = v7;
  v24 = &vf00.x;
  v24[8] = x;
  v24[9] = y;
  v24[10] = z;
  v24[11] = w;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v25 = &vf00.x;
  v26 = v25[6];
  v27 = v25[4];
  v28 = v25[5];
  v30 = v20;
  sub_1949110(0);
  v32 = v27 * v27;
  v33 = v28 * v28;
  v34 = v22;
  v39 = &vf00.x;
  v40 = v32 + v33;
  v41 = v26 * v26;
  v42 = v39[4];
  v43 = v39[5];
  v44 = v39[6];
  v83 = v39[7];
  v45 = v40 + v41;
  v46 = sqrtf(v45);
  v47 = &vf00.x;
  v47[4] = v42;
  v47[5] = v43;
  v47[6] = v44;
  v47[7] = v83;
  v48 = *(f32 *)(*(u64 *)(v13 + 96) + 16);
  v49 = v46 * v48;
  v50 = v34;
  v51 = v21;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v49);
  v52 = v30;
  v53 = &vf00.x;
  v53[8] = x;
  v53[9] = y;
  v54 = v79;
  v53[10] = z;
  v53[11] = w;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  vct_A = (struct sdfVector4_t)xmmword_3D004E0;
  v55 = *(f32 *)(*(u64 *)(v13 + 96) + 24);
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v55);
  vct_B = vct_A;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v81 = vct_A;
  v102.x = v51;
  v102.y = v52;
  v102.z = v50;
  v102.w = v54;
  sBtlGetRotateDeg(v102, 90.0);
  ToMatrix();
  v59 = (u8)byte_5756085;
  vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
  if (v59)
  {
    goto LABEL_63;
  }
  else
  {
    goto LABEL_63;
  }
LABEL_63:
  get_transpose(&v97, &mtx_A, 0);
  v103 = vct_A;
  v96 = v97;
  v100 = op_Multiply_60923920(&v96, v103, 0);
  vct_A = v100;
  v61 = *(f32 *)(*(u64 *)(v13 + 96) + 20);
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v61);
  vct_B = v81;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v82 = vct_A;
  v62 = &vf00.x;
  v62[4] = v42;
  v62[5] = v43;
  v62[6] = v44;
  v62[7] = v83;
  v63 = *(f32 *)(*(u64 *)(v13 + 104) + 16);
  v64 = v46 * v63;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v64);
  v65 = &vf00.x;
  v65[8] = x;
  v65[9] = y;
  v65[10] = z;
  v65[11] = w;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v93 = vct_A;
  vct_A = (struct sdfVector4_t)xmmword_3D004E0;
  v66 = *(f32 *)(*(u64 *)(v13 + 104) + 24);
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v66);
  vct_B = v93;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v104.y = v52;
  v104.z = v50;
  v104.w = v54;
  v94 = vct_A;
  v104.x = v51;
  sBtlGetRotateDeg(v104, 90.0);
  ToMatrix();
  vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
  get_transpose(&v97, &mtx_A, 0);
  v105 = vct_A;
  v96 = v97;
  v101 = op_Multiply_60923920(&v96, v105, 0);
  vct_A = v101;
  v69 = *(f32 *)(*(u64 *)(v13 + 104) + 20);
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v69);
  vct_B = v94;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v95 = vct_A;
  vct_A = v82;
  v70 = (u8)byte_5755EF5;
  *v12 = vct_A;
  if (v70)
    goto LABEL_108;
  goto LABEL_181;
  if (v73)
  {
LABEL_108:
    goto LABEL_109;
  }
LABEL_181:
LABEL_109:
  vct_A = v95;
  *(sdfVector4_t *)&hittbl->klass = vct_A;
  return 1;
}

// 0x2040420
bool sBtlResetHitPos_XYZ(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *twk, SBTLEFF_WORK *ewk, SBTLSKILLHIT_POSWORK *pwk, sdfVector4_t *pos, sdfVector4_t *rot, u16 tbltype) {
  sdfVector4_t *v15;
  sdfVector4_t *v16;
  u32 flg;
  sdfVector4_t *p_rot;
  s32 v21;
  struct sdfVector4_t v22;
  sbtldmg_idouwork_tag *iwk;
  sbtldmg_idouwork_tag *p_iwk;
  sdfVector4_t *p_apos;
  sbtldmg_idouwork_tag *v28;
  SBTLSKILLHIT_TBL *hittbl;
  f32 x;
  f32 y;
  sbtldmg_idouwork_tag *p_fields;
  f32 z;
  f32 w;
  SBTLSKILLHIT_TBL *p_apos1;
  f32 v39;
  dds3PoseSet_t *poseset;
  sdfVector4_t *p_scl;
  s32 v48;
  struct sdfVector4_t v49;
  dds3PoseSet_t *v50;
  sdfVector4_t *v51;
  s32 v52;
  struct sdfVector4_t v53;
  dds3PoseSet_t *v54;
  sdfVector4_t *p_pos;
  s32 v56;
  struct sdfVector4_t v57;
  sbtldmg_idouwork_tag *v58;
  sdfVector4_t *v59;
  s32 v62;
  s32 v63;
  s32 v64;
  s32 v65;
  f32 v66;
  f32 v67;
  f32 v68;
  struct sdfVector4_t v69;
  f32 v70;
  struct sdfVector4_t v71;
  struct sdfVector4_t v73;
  struct sdfVector4_t v75;
  struct sdfVector4_t v77;
  sdfVector4_t v79;
  sdfVector4_t v80;
  sdfVector4_t v81;

  if (twk->skillid != 450)
  {
    sBtlSetHitPos_XYZ(wk, twk, ewk, pwk, pos, rot, tbltype);
    flg = twk->flg;
    if ((flg & 0x100) != 0)
    {
      if ((flg & 0x1000) == 0)
      {
        twk->targetID = wk->actaiwk->targetID;
        v69 = wk->rot;
        vct_A = v69;
        p_rot = &twk->rot;
        v21 = (u8)byte_5755EF5;
        *p_rot = vct_A;
        v22 = twk->pos;
        if (v21)
          goto LABEL_14;
        goto LABEL_47;
        if (v62)
        {
LABEL_14:
          goto LABEL_15;
        }
LABEL_47:
        v71 = v22;
        v22 = v71;
LABEL_15:
        vct_A = v22;
        p_iwk = &twk->iwk;
        iwk = twk->iwk;
        p_apos = &iwk->apos;
        *p_apos = vct_A;
        v28 = twk->iwk;
        v80 = twk->pos;
        hittbl = twk->hittbl;
        x = twk->endpos.x;
        y = twk->endpos.y;
        p_fields = &v28->fields;
        z = twk->endpos.z;
        w = twk->endpos.w;
        p_apos1 = &v28->apos1;
        v68 = twk->pos.y;
        v70 = twk->pos.x;
        v66 = twk->pos.w;
        v67 = twk->pos.z;
        v80.w = v66;
        v80.z = v67;
        v80.y = v68;
        v80.x = v70;
        v81.x = x;
        v81.y = y;
        *(u64 *)&v79.x = hittbl;
        v81.z = z;
        v81.w = w;
        *(u64 *)&v79.z = p_fields;
        sBtlSetApos12(v80, v81, v79, p_apos1, v15, v16);
        twk->spd = twk->sokudo;
        v39 = 0.0;
LABEL_40:
        p_iwk->addtime = v39;
        return 1;
      }
      __asm { FMOV            V0.4S, #1.0 }
      vct_A = _Q0;
      poseset = twk->pBasic->poseset;
      p_scl = &poseset->scl;
      v48 = (u8)byte_5755EF5;
      *p_scl = vct_A;
      v49 = twk->rot;
      if (v48)
        goto LABEL_26;
      goto LABEL_56;
      if (v63)
      {
LABEL_26:
        goto LABEL_27;
      }
LABEL_56:
      v73 = v49;
      v49 = v73;
LABEL_27:
      vct_A = v49;
      v50 = twk->pBasic->poseset;
      v51 = &v50->rot;
      v52 = (u8)byte_5755EF5;
      *v51 = vct_A;
      v53 = twk->pos;
      if (v52)
        goto LABEL_30;
      goto LABEL_60;
      if (v64)
      {
LABEL_30:
        goto LABEL_31;
      }
LABEL_60:
      v75 = v53;
      v53 = v75;
LABEL_31:
      vct_A = v53;
      v54 = twk->pBasic->poseset;
      p_pos = &v54->pos;
      v56 = (u8)byte_5755EF5;
      *p_pos = vct_A;
      v57 = twk->pos;
      if (v56)
        goto LABEL_34;
      goto LABEL_64;
      if (v65)
      {
LABEL_34:
        goto LABEL_35;
      }
LABEL_64:
      v77 = v57;
      v57 = v77;
LABEL_35:
      vct_A = v57;
      p_iwk = &twk->iwk;
      v58 = twk->iwk;
      v59 = &v58->apos;
      *v59 = vct_A;
      ++wk->hitmdl_serialID;
      v39 = 1.0 / (f32)twk->life;
      goto LABEL_40;
    }
  }
  return 1;
}

// 0x2040ad0
bool sBtlSetHitPos_XYZ(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *twk, SBTLEFF_WORK *ewk, SBTLSKILLHIT_POSWORK *pwk, sdfVector4_t *pos, sdfVector4_t *rot, u16 tbltype) {
  sdfVector4_t v14;
  sdfVector4_t v17;
  struct SDF_VU0 *static_fields;
  float32x2_t v21;
  f32 z;
  u32 v23;
  float32x2_t v26;
  f32 v27;
  float32x2_t *v28;
  float32x2_t *v30;
  f32 w;
  float32x2_t v32;
  f32 v33;
  float32x2_t *v34;
  s32 v35;
  sdfVector4_t v36;
  u32 v39;
  s32 v41;
  struct sdfVector4_t v43;
  sdfVector4_t v44;
  sdfVector4_t v47;
  sdfVector4_t rott;
  sdfVector4_t rota;
  sdfVector4_t posa;
  sdfMatrix4_t v53;
  sdfMatrix4_t v54;
  sdfVector4_t v55;
  sdfVector4_t v56;

  *(u64 *)&posa.x = 0;
  *(u64 *)&posa.z = 0;
  v14 = *pos;
  *(u64 *)&rota.x = 0;
  *(u64 *)&rota.z = 0;
  *(u64 *)&rott.x = 0;
  *(u64 *)&rott.z = 0;
  v43 = v14;
  vct_A = v43;
  posa = vct_A;
  v17 = *rot;
  vct_A = v17;
  rota = vct_A;
  if ((u32)static_fields)
    goto LABEL_15;
  goto LABEL_14;
  if (!v39)
LABEL_14:
LABEL_15:
  sBtlSetHitPos(wk, twk, ewk, pwk, &posa, &rota, &rott, tbltype);
  v21.n64_u64[0] = *(u64 *)&twk->x;
  z = twk->z;
  if ((twk->flg & 0x1000) != 0)
  {
    v44 = rota;
    if (!v23)
      goto LABEL_51;
LABEL_19:
    goto LABEL_20;
  }
  v44 = rott;
  if (v23)
    goto LABEL_19;
LABEL_51:
LABEL_20:
  vct_A = v44;
  ToMatrix();
  v26.n64_u64[0] = vadd_f32(v21, 0).n64_u64[0];
  v27 = z + 0.0;
  v28[2].n64_u64[0] = v26.n64_u64[0];
  v28[3].n64_f32[0] = v27;
  v28[3].n64_u32[1] = 1065353216;
  get_transpose(&v54, &mtx_A, 0);
  v56 = vct_A;
  v53 = v54;
  v55 = op_Multiply_60923920(&v53, v56, 0);
  vct_A = v55;
  w = posa.w;
  v32.n64_u64[0] = vadd_f32(v30[2], *(float32x2_t *)&posa.x).n64_u64[0];
  v33 = v30[3].n64_f32[0] + posa.z;
  *(float32x2_t *)&posa.x = v32;
  posa.z = v33;
  v34[2].n64_u64[0] = v32.n64_u64[0];
  v34[3].n64_f32[0] = v33;
  v34[3].n64_f32[1] = w;
  v35 = (u8)byte_5755EF5;
  *pos = vct_A;
  v36 = rota;
  if (v35)
    goto LABEL_36;
  goto LABEL_65;
  if (v41)
  {
LABEL_36:
    goto LABEL_37;
  }
LABEL_65:
  v47 = v36;
  v36 = v47;
LABEL_37:
  vct_A = v36;
  *rot = vct_A;
  return 1;
}

// 0x203bce0
bool sBtlSetHitPos(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *twk, SBTLEFF_WORK *ewk, SBTLSKILLHIT_POSWORK *pwk, sdfVector4_t *pos, sdfVector4_t *rot, sdfVector4_t *rott, u16 tbltype) {
  SBTLVISUAL_DATA *v14;
  void *v15;
  SBATTLE_WORK *v18;
  s32 *stack_id;
  s32 v20;
  s32 *m_Items;
  f32 v23;
  f32 v24;
  u32 iti;
  SBTLUNIT_WORK *v26;
  SBTLDMG_HITWORK *v27;
  char v28;
  f32 v29;
  f32 v30;
  struct sdfVector4_t v32;
  f32 *v33;
  char v34;
  f32 v36;
  f32 v37;
  s32 BEDtype;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 targetID;
  SBTLUNIT_WORK *v42;
  SBATTLE_WORK *v45;
  SBTLUNIT_WORK *Nakama;
  s64 v47;
  SBATTLE_WORK *v48;
  SBTLUNIT_LISTWORK *v49;
  s32 v50;
  SBTLUNIT_WORK *v51;
  f32 GroundPos;
  f32 x;
  f32 z;
  f32 dir;
  f32 *v61;
  s64 muki;
  f32 v63;
  f32 v64;
  f32 v65;
  f32 v66;
  f32 v67;
  s32 v69;
  f32 v71;
  f32 v72;
  f32 v73;
  sdfVector4_t v74;
  s32 v76;
  f32 *v78;
  s32 v79;
  struct sdfVector4_t v80;
  sdfVector4_t *v82;
  s32 v84;
  s32 v86;
  SBTLUNIT_LISTWORK *v88;
  s32 playerID;
  SBTLUNIT_WORK *v90;
  s32 iti_no;
  char v93;
  char v94;
  s32 v95;
  _OWORD *p_x;
  __int128 v98;
  __int128 v99;
  struct sdfVector4_t v100;
  struct sdfVector4_t v101;
  struct sdfVector4_t v102;
  void *v103;
  sdfVector4_t *v104;
  struct sdfVector4_t v106;
  struct sdfVector4_t v107;
  struct sdfVector4_t v108;
  struct sdfVector4_t v109;
  struct sdfVector4_t v110;
  struct sdfVector4_t wkb;
  SBTLUNIT_WORK *wkc[2];
  sdfMatrix4_t v121;
  sdfVector4_t p;
  sdfMatrix4_t v123;
  sdfMatrix4_t v124;
  sdfVector4_t v125;
  sdfVector4_t v126;
  sdfVector4_t v127;
  sdfVector4_t v128;

  p = (sdfVector4_t)xmmword_3CFD5C0;
  v14 = Allocate(SBTLVISUAL_DATA);
  v15 = NewSpecific(f32, 9u);
  InitializeArray_55364416(v15, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__FE046ABF1860E112E18084987A376D4F2FDA884C8110D892D868B4A9174C19D7, 0);
  v103 = v15;
  v18 = wk;
  stack_id = wk->stack_id;
  v20 = v18->summonindex[0];
  if (stack_id[0] == v20)
  {
    stack_id = wk->stack_id;
    m_Items = &stack_id[1];
  }
  else
  {
    stack_id = wk->stack_id;
    m_Items = stack_id;
  }
  v23 = 1.0;
  v24 = 0.0;
  iti = pwk->iti;
  v104 = rott;
  v26 = wk;
  switch (iti & 0xF)
  {
    case 0u:
    case 1u:
    case 4u:
    case 5u:
    case 8u:
      if (iti >= 0x10)
        goto LABEL_186;
      goto LABEL_14;
    case 2u:
      if (!ewk || (v26 = wk, BEDtype = ewk->BEDtype, BEDtype != 2) && (v26 = wk, BEDtype != 5))
      {
        UnitMng = wk->UnitMng;
        targetID = twk->targetID;
        v42 = sBtlSearchUnit_ID(UnitMng, targetID);
        if (v42)
          v26 = v42;
        else
          v26 = wk;
      }
      goto LABEL_185;
    case 3u:
      v101 = ewk->pos;
      v27 = twk;
      vct_A = v101;
      v28 = 1;
      v29 = 0.0;
      v26 = wk;
      v30 = 0.0;
      p = vct_A;
      goto LABEL_26;
    case 6u:
      if ((tbltype & 0x1000) != 0)
      {
        goto LABEL_176;
      }
      v45 = wk;
      if (v45->member_num >= 1)
      {
        Nakama = sBtlGetNakama(0);
        goto LABEL_180;
      }
LABEL_176:
      v45 = wk;
      v88 = v45->UnitMng;
      playerID = v45->playerID;
      Nakama = sBtlSearchUnit_ID(v88, playerID);
LABEL_180:
      v26 = wk;
      v90 = Nakama;
      if (Nakama)
      {
        v26 = v90;
        if (!sBtlCheckDamageTarget(v90))
LABEL_184:
          v26 = wk;
      }
LABEL_185:
      iti = pwk->iti;
      if (iti >= 0x10)
      {
LABEL_186:
        iti_no = pwk->iti_no;
        sBtlGetUnitHelperPos(v26, iti_no);
        v27 = twk;
        v93 = BYTE1(v27->flg);
        p = vct_A;
        if ((v93 & 0x80) == 0)
          goto LABEL_192;
        goto LABEL_200;
        if ((v94 & 0x80) == 0)
        {
LABEL_192:
          v102 = v26->rot;
          vct_A = v102;
LABEL_24:
          goto LABEL_25;
        }
LABEL_200:
        v95 = pwk->iti_no;
        sBtlGetUnitHelperMatrix(v26, v95);
        p_x = &vf00.x;
        v98 = p_x[5];
        *(_OWORD *)&v121.m00 = p_x[4];
        *(_OWORD *)&v121.m01 = v98;
        v99 = p_x[7];
        *(_OWORD *)&v121.m02 = p_x[6];
        *(_OWORD *)&v121.m03 = v99;
        sBtlGetQuatFromMatrix(&v121);
        goto LABEL_207;
      }
LABEL_14:
      if (iti == 3)
      {
        v27 = twk;
        v28 = 0;
        v29 = 0.0;
        v30 = 0.0;
        goto LABEL_26;
      }
      v100 = v26->pos;
      v27 = twk;
      vct_A = v100;
      p = vct_A;
      v32 = v26->rot;
      vct_A = v32;
      goto LABEL_24;
LABEL_207:
LABEL_25:
      v33 = &vf00.x;
      v28 = 0;
      v24 = v33[4];
      v29 = v33[5];
      v30 = v33[6];
      v23 = v33[7];
LABEL_26:
      sBtlGetCylinderData(v26, v14);
      if (pwk->iti > 0xFu)
        v34 = 1;
      else
        v34 = v28;
      if ((v34 & 1) == 0)
      {
        switch (pwk->takasa)
        {
          case 0:
            v106 = v14->center;
            vct_A = v106;
            v36 = 0.5;
            v37 = v14->e_height;
            goto LABEL_88;
          case 1:
            v107 = v14->center;
            vct_A = v107;
            p = vct_A;
            break;
          case 2:
            v108 = v14->center;
            vct_A = v108;
            v36 = -0.5;
            v37 = v14->e_height;
            goto LABEL_88;
          case 3:
            v109 = v14->center;
            vct_A = v109;
            v37 = v14->e_height;
            v36 = -0.8;
LABEL_88:
            p = vct_A;
            GroundPos = vct_A.y + (f32)(v37 * v36);
            goto LABEL_97;
          case 5:
            v110 = v14->center;
            vct_A = v110;
            p = vct_A;
            x = p.x;
            z = p.z;
            GroundPos = sBtlGetGroundPos(x, z);
LABEL_97:
            p.y = GroundPos;
            break;
          default:
            break;
        }
      }
      dir = v27->dir;
      v126.x = v24;
      v126.y = v29;
      v126.z = v30;
      v126.w = v23;
      sBtlGetRotateDeg(v126, dir);
      v61 = &vf00.x;
      muki = pwk->muki;
      v63 = v61[4];
      v64 = v61[5];
      v66 = v61[6];
      v65 = v61[7];
      if (muki == 8)
        goto LABEL_120;
      v67 = *((f32 *)&v103[2].klass + muki);
      v127.x = v63;
      v127.y = v64;
      v127.z = v66;
      v127.w = v65;
      sBtlGetRotateDeg(v127, v67);
      ToMatrix();
      v69 = (u8)byte_5756085;
      vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
      if (v69)
      {
        goto LABEL_111;
      }
      else
      {
        goto LABEL_111;
      }
LABEL_111:
      get_transpose(&v124, &mtx_A, 0);
      v128 = vct_A;
      v123 = v124;
      v125 = op_Multiply_60923920(&v123, v128, 0);
      vct_A = v125;
      v71 = v14->width;
      v72 = wk->scale.x;
      v73 = v71 * v72;
      vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v73);
      v74 = p;
      vct_B = v74;
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      p = vct_A;
LABEL_120:
      sBtlBS14_CLEAR_Pos(wk, ewk, &p);
      wkb = p;
      vct_A = wkb;
      v76 = (u8)byte_5755EF5;
      *pos = vct_A;
      if (v76)
        goto LABEL_128;
      goto LABEL_144;
      if (v84)
      {
LABEL_128:
        goto LABEL_129;
      }
LABEL_144:
LABEL_129:
      v78 = &vf00.x;
      v78[4] = v63;
      v78[5] = v64;
      v78[6] = v66;
      v78[7] = v65;
      v79 = (u8)byte_5755EF5;
      *rot = vct_A;
      v80 = v26->rot;
      if (v79)
        goto LABEL_132;
      goto LABEL_148;
      if (v86)
      {
LABEL_132:
        v82 = v104;
        goto LABEL_133;
      }
LABEL_148:
      *(sdfVector4_t *)wkc = v80;
      v80 = *(sdfVector4_t *)wkc;
      v82 = v104;
LABEL_133:
      vct_A = v80;
      *v82 = vct_A;
      return 1;
    case 7u:
      v47 = *m_Items;
      v48 = wk;
      v49 = v48->UnitMng;
      v50 = v48->summonID[v47];
      v51 = sBtlSearchUnit_ID(v49, v50);
      if (v51)
      {
        v26 = v51;
        if (sBtlCheckDamageTarget(v26))
          goto LABEL_185;
      }
      goto LABEL_184;
    default:
      v26 = wk;
      v28 = 1;
      v27 = twk;
      v29 = 0.0;
      v30 = 0.0;
      goto LABEL_26;
  }
}

// 0x20410c0
bool sBtlGetHit_OnlyEndPos(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *twk, SBTLEFF_WORK *ewk, SBTLSKILLHIT_TBL *hittbl, SBTLSKILLHIT_POSWORK *pwk_st, SBTLSKILLHIT_POSWORK *pwk, sdfVector4_t *pos, u16 tbltype) {
  SBTLVISUAL_DATA *v15;
  void *v16;
  SBATTLE_WORK *v18;
  s32 *stack_id;
  s32 v20;
  s32 *m_Items;
  u32 iti;
  f32 x;
  f32 y;
  struct sdfVector4_t rot;
  f32 v31;
  s64 v32;
  f32 v33;
  s32 BEDtype;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 targetID;
  SBTLUNIT_WORK *v37;
  SBTLUNIT_WORK *v38;
  s32 BEDsklid;
  bool v40;
  u32 v43;
  SBATTLE_WORK *v44;
  SBTLUNIT_LISTWORK *v45;
  s32 playerID;
  s64 v47;
  SBATTLE_WORK *v48;
  SBTLUNIT_LISTWORK *v49;
  s32 v50;
  SBTLUNIT_WORK *v51;
  s64 v60;
  f32 v61;
  f32 v62;
  f32 v63;
  f32 v64;
  f32 w;
  s32 v67;
  struct sdfVector4_t v69;
  f32 v70;
  f32 v71;
  struct sdfVector4_t v73;
  s32 iti_no;
  s64 z;
  struct sdfVector4_t za;
  struct sdfVector4_t zb;
  struct sdfVector4_t zc;
  struct sdfVector4_t zd;
  struct sdfVector4_t ze;
  struct sdfVector4_t zf;
  struct sdfVector4_t zg;
  sdfMatrix4_t v92;
  sdfMatrix4_t v93;
  sdfVector4_t v94;
  sdfVector4_t v95;

  v15 = Allocate(SBTLVISUAL_DATA);
  v16 = NewSpecific(f32, 9u);
  InitializeArray_55364416(v16, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__FE046ABF1860E112E18084987A376D4F2FDA884C8110D892D868B4A9174C19D7, 0);
  if (wk)
  {
    v18 = wk;
    stack_id = v18->stack_id;
    v20 = v18->summonindex[0];
    if (stack_id[0] == v20)
    {
      stack_id = wk->stack_id;
      m_Items = &stack_id[1];
    }
    else
    {
      stack_id = wk->stack_id;
      m_Items = stack_id;
    }
    iti = pwk->iti;
    switch (iti & 0xF)
    {
      case 1u:
      case 4u:
      case 5u:
      case 8u:
        if (iti < 0x10)
          goto LABEL_15;
        goto LABEL_169;
      case 2u:
        if (ewk)
        {
          BEDtype = ewk->BEDtype;
          if (BEDtype == 2 || BEDtype == 5)
            goto LABEL_167;
        }
        UnitMng = wk->UnitMng;
        targetID = twk->targetID;
        v37 = sBtlSearchUnit_ID(UnitMng, targetID);
        if (v37)
          v38 = v37;
        else
          v38 = wk;
        if (!ewk || v37)
          goto LABEL_168;
        BEDsklid = ewk->BEDsklid;
        if (BEDsklid <= 1130)
        {
          if (BEDsklid == 443)
            return 1;
          v40 = BEDsklid == 903;
          goto LABEL_209;
        }
        if (BEDsklid != 1131 && BEDsklid != 1236)
        {
          v40 = BEDsklid == 1250;
LABEL_209:
          v38 = wk;
          if (v40)
            return 1;
LABEL_168:
          iti = pwk->iti;
          wk = v38;
          if (iti >= 0x10)
          {
LABEL_169:
            iti_no = pwk->iti_no;
            sBtlGetUnitHelperPos(wk, iti_no);
            goto LABEL_23;
          }
LABEL_15:
          if (iti == 3)
          {
            x = 0.0;
            y = 0.0;
            z = 0x3F80000000000000LL;
            if (pwk->iti > 0xFu)
              goto LABEL_110;
            goto LABEL_33;
          }
          za = wk->pos;
          vct_A = za;
LABEL_23:
          x = vct_A.x;
          y = vct_A.y;
          z = *(u64 *)&vct_A.z;
          rot = wk->rot;
          vct_A = rot;
          goto LABEL_27;
LABEL_33:
          sBtlGetCylinderData(wk, v15);
          switch (pwk->takasa)
          {
            case 0:
              zb = v15->center;
              vct_A = zb;
              v31 = 0.5;
              v32 = *(u64 *)&vct_A.z;
              x = vct_A.x;
              v33 = vct_A.y;
              goto LABEL_101;
            case 1:
              zd = v15->center;
              goto LABEL_85;
LABEL_86:
              x = vct_A.x;
              y = vct_A.y;
              z = *(u64 *)&vct_A.z;
              goto LABEL_110;
LABEL_85:
              vct_A = zd;
              goto LABEL_86;
            case 2:
              ze = v15->center;
              vct_A = ze;
              goto LABEL_93;
LABEL_94:
              v31 = -0.5;
              v32 = *(u64 *)&vct_A.z;
              x = vct_A.x;
              v33 = vct_A.y;
LABEL_101:
              z = v32;
              y = v33 + (f32)(v15->e_height * v31);
              goto LABEL_110;
LABEL_93:
              goto LABEL_94;
            case 3:
              zf = v15->center;
              vct_A = zf;
              v32 = *(u64 *)&vct_A.z;
              x = vct_A.x;
              v33 = vct_A.y;
              v31 = -0.8;
              goto LABEL_101;
            case 5:
              zg = v15->center;
              vct_A = zg;
              x = vct_A.x;
              v60 = *(u64 *)&vct_A.z;
              z = v60;
              LODWORD(v60) = z;
              y = sBtlGetGroundPos(x, *(f32 *)&v60);
LABEL_110:
              v61 = wk->rot.x;
              v62 = wk->rot.y;
              v63 = *((f32 *)&v16[2].klass + pwk->muki);
              v64 = wk->rot.z;
              w = wk->rot.w;
              v95.x = v61;
              v95.y = v62;
              v95.z = v64;
              v95.w = w;
              sBtlGetRotateDeg(v95, v63);
              ToMatrix();
              v67 = (u8)byte_5756085;
              vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
              if (v67)
              {
                goto LABEL_117;
              }
              else
              {
                goto LABEL_117;
              }
LABEL_117:
              get_transpose(&v93, &mtx_A, 0);
              v92 = v93;
              v94 = op_Multiply_60923920(&v92, vct_A, 0);
              vct_A = v94;
              v69 = vct_A;
              vct_A = v69;
              v70 = wk->scale.x;
              v71 = v70 * 0.0;
              vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v71);
              vct_B.x = x;
              vct_B.y = y;
              *(u64 *)&vct_B.z = z;
              vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
              v73 = vct_A;
              vct_A = v73;
              *pos = vct_A;
              return 1;
            default:
              goto LABEL_110;
          }
LABEL_27:
          if (pwk->iti > 0xFu)
            goto LABEL_110;
          goto LABEL_33;
        }
        return 1;
      case 3u:
        zc = ewk->pos;
        vct_A = zc;
        goto LABEL_86;
      case 6u:
        if ((tbltype & 0x1000) == 0)
        {
          v44 = wk;
          if (v44->member_num >= 1)
          {
            if (!v43)
            {
              v44 = wk;
            }
            v45 = v44->UnitMng;
            playerID = v44->summonID[v44->summonindex[0]];
LABEL_161:
            v38 = sBtlSearchUnit_ID(v45, playerID);
            if (!v38)
              goto LABEL_167;
LABEL_166:
            if (!sBtlCheckDamageTarget(v38))
LABEL_167:
              v38 = wk;
            goto LABEL_168;
          }
          if (v43)
          {
LABEL_160:
            v45 = v44->UnitMng;
            playerID = v44->playerID;
            goto LABEL_161;
          }
        }
        v44 = wk;
        goto LABEL_160;
      case 7u:
        v47 = *m_Items;
        v48 = wk;
        v49 = v48->UnitMng;
        v50 = v48->summonID[v47];
        v51 = sBtlSearchUnit_ID(v49, v50);
        if (!v51)
          goto LABEL_167;
        v38 = v51;
        goto LABEL_166;
      default:
        x = 0.0;
        y = 0.0;
        z = 0x3F80000000000000LL;
        goto LABEL_110;
    }
  }
  return 1;
}

// 0x203cfd0
bool sBtlSetHitEndPos(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *twk, SBTLEFF_WORK *ewk, SBTLSKILLHIT_TBL *hittbl, SBTLSKILLHIT_POSWORK *pwk_st, SBTLSKILLHIT_POSWORK *pwk, sdfVector4_t *pos, u16 tbltype) {
  SBTLVISUAL_DATA *v14;
  void *v15;
  SBATTLE_WORK *v17;
  s32 *stack_id;
  s32 v19;
  s32 *m_Items;
  u32 iti;
  SBTLUNIT_WORK *v23;
  struct sdfVector4_t v25;
  s32 BEDtype;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 targetID;
  SBTLUNIT_WORK *v29;
  s32 PointLast;
  struct sdfVector4_t v32;
  f32 shatei;
  struct sdfVector4_t v35;
  sdfVector4_t v36;
  sdfVector4_t *v37;
  u32 v38;
  SBATTLE_WORK *v39;
  SBTLUNIT_WORK *Nakama;
  SBATTLE_WORK *v41;
  SBTLUNIT_LISTWORK *v42;
  s32 v43;
  SBTLUNIT_WORK *v44;
  SBTLUNIT_LISTWORK *v47;
  s32 playerID;
  SBTLUNIT_WORK *v49;
  s32 iti_no;
  f32 v52;
  f32 v53;
  sdfVector4_t v54;
  f32 GroundPos;
  f32 v60;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  s32 v66;
  SBTLUNIT_WORK *v68;
  s32 v69;
  SBTLUNIT_LISTWORK *v71;
  s32 v72;
  SBTLUNIT_WORK *v73;
  SBATTLE_WORK *v77;
  SBATTLE_WORK *v79;
  SBTLUNIT_LISTWORK *v80;
  s32 v81;
  SBTLUNIT_WORK *v82;
  SBTLUNIT_LISTWORK *v85;
  s32 v86;
  f32 v88;
  sdfVector4_t v89;
  f32 v90;
  f32 v91;
  f32 v92;
  f32 v93;
  f32 dir;
  f32 v97;
  struct sdfVector4_t v98;
  sdfVector4_t v100;
  f32 v101;
  s64 v102;
  struct sdfVector4_t v103;
  f32 v104;
  struct sdfVector4_t v106;
  f32 v107;
  struct sdfVector4_t v109;
  f32 v110;
  struct sdfVector4_t v111;
  sdfVector4_t v112;
  s64 v116;
  struct sdfVector4_t v117;
  struct sdfVector4_t v118;
  struct sdfVector4_t v119;
  struct sdfVector4_t v122;
  struct sdfVector4_t v123;
  struct sdfVector4_t v124;
  struct sdfVector4_t v125;
  struct sdfVector4_t v126;
  sdfVector4_t v128;
  f32 v129;
  f32 v130;
  struct sdfVector4_t v131;
  sdfVector4_t rot;
  sdfVector4_t posa;
  sdfMatrix4_t v164;
  sdfMatrix4_t v165;
  SBTLEFF_WORK *v166;
  sdfVector4_t v167;
  sdfVector4_t v168;
  sdfVector4_t v169;
  sdfVector4_t v171;
  sdfVector4_t v172;

  v166 = ewk;
  posa = (sdfVector4_t)xmmword_3CFD5C0;
  v14 = Allocate(SBTLVISUAL_DATA);
  *(u64 *)&rot.x = 0;
  *(u64 *)&rot.z = 0;
  v15 = NewSpecific(f32, 9u);
  InitializeArray_55364416(v15, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__FE046ABF1860E112E18084987A376D4F2FDA884C8110D892D868B4A9174C19D7, 0);
  v17 = wk;
  stack_id = v17->stack_id;
  v19 = v17->summonindex[0];
  if (stack_id[0] == v19)
  {
    stack_id = wk->stack_id;
    m_Items = &stack_id[1];
  }
  else
  {
    stack_id = wk->stack_id;
    m_Items = stack_id;
  }
  v116 = *m_Items;
  iti = pwk->iti;
  v23 = wk;
  switch (iti & 0xF)
  {
    case 1u:
    case 4u:
    case 5u:
    case 8u:
      if (iti < 0x10)
        goto LABEL_14;
      goto LABEL_92;
    case 2u:
      if (!v166 || (v23 = wk, BEDtype = v166->BEDtype, BEDtype != 2) && (v23 = wk, BEDtype != 5))
      {
        UnitMng = wk->UnitMng;
        targetID = twk->targetID;
        v29 = sBtlSearchUnit_ID(UnitMng, targetID);
        if (v29)
          v23 = v29;
        else
          v23 = wk;
      }
      goto LABEL_91;
    case 3u:
      if (twk->skillid != 73)
      {
        v119 = v166->pos;
        vct_A = v119;
        v23 = wk;
        posa = vct_A;
        goto LABEL_152;
      }
      PointLast = sBtlGetPointLast(wk, v166->BEDsklid);
      sBtlGetPointData(PointLast, &posa, &rot);
      v128 = posa;
      vct_A = v128;
      v32 = twk->pos;
      vct_B = v32;
      vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      sub_1949110(0);
      shatei = hittbl->shatei;
      v129 = hittbl->shatei;
      shatei = v129;
      v130 = shatei;
      shatei = v130;
      vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, shatei);
      v35 = twk->pos;
      vct_B = v35;
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      posa = vct_A;
      v36 = posa;
      v37 = pos;
      vct_A = v36;
LABEL_322:
      *v37 = vct_A;
      return 1;
    case 6u:
      if ((tbltype & 0x1000) == 0)
      {
        if (v38)
        {
          v39 = wk;
          if (v39->member_num >= 1)
          {
LABEL_63:
            Nakama = sBtlGetNakama(0);
            goto LABEL_86;
          }
        }
        else
        {
          v39 = wk;
          if (v39->member_num >= 1)
            goto LABEL_63;
        }
LABEL_83:
        v47 = v39->UnitMng;
        playerID = v39->playerID;
        Nakama = sBtlSearchUnit_ID(v47, playerID);
LABEL_86:
        v49 = Nakama;
        v23 = wk;
        if (Nakama)
        {
          v23 = v49;
          if (!sBtlCheckDamageTarget(v49))
LABEL_90:
            v23 = wk;
        }
LABEL_91:
        if (pwk->iti >= 0x10u)
        {
LABEL_92:
          iti_no = pwk->iti_no;
          sBtlGetUnitHelperPos(v23, iti_no);
LABEL_97:
          posa = vct_A;
          v25 = v23->rot;
LABEL_98:
          vct_A = v25;
          if (pwk->iti > 0xFu)
          {
LABEL_152:
            v60 = *((f32 *)&v15[2].klass + pwk->muki);
            x = v23->rot.x;
            y = v23->rot.y;
            z = v23->rot.z;
            w = v23->rot.w;
            v169.x = x;
            v169.y = y;
            v169.z = z;
            v169.w = w;
            sBtlGetRotateDeg(v169, v60);
            ToMatrix();
            v66 = (u8)byte_5756085;
            vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
            if (v66)
            {
              goto LABEL_159;
            }
            else
            {
              goto LABEL_159;
            }
LABEL_159:
            get_transpose(&v165, &mtx_A, 0);
            v164 = v165;
            v167 = op_Multiply_60923920(&v164, vct_A, 0);
            vct_A = v167;
LABEL_161:
            v117 = vct_A;
            v68 = wk;
            switch (pwk_st->iti & 0xF)
            {
              case 0:
              case 1:
              case 4:
              case 5:
              case 8:
                goto LABEL_210;
              case 2:
                if (v166)
                {
                  v69 = v166->BEDtype;
                  if (v69 == 2 || v69 == 5)
                    goto LABEL_209;
                }
                v71 = wk->UnitMng;
                v72 = twk->targetID;
                v73 = sBtlSearchUnit_ID(v71, v72);
                if (v73)
                  v68 = v73;
                else
                  v68 = wk;
                goto LABEL_210;
              case 3:
                v131 = v166->pos;
                vct_A = v131;
                posa = vct_A;
                goto LABEL_209;
              case 6:
                if ((tbltype & 0x1000) == 0)
                {
                  v77 = wk;
                  if (v77->member_num >= 1)
                  {
                    v68 = sBtlGetNakama(0);
                    if (!v68)
                    {
LABEL_209:
                      v68 = wk;
                      goto LABEL_210;
                    }
LABEL_206:
LABEL_208:
                    if (!sBtlCheckDamageTarget(v68))
                      goto LABEL_209;
LABEL_210:
                    vct_A = v117;
                    v88 = v68->scale.x;
                    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v88);
                    v89 = posa;
                    vct_B = v89;
                    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
                    v90 = v68->rot.x;
                    v91 = v68->rot.y;
                    v92 = v68->rot.z;
                    v93 = v68->rot.w;
                    dir = twk->dir;
                    posa = vct_A;
                    v171.x = v90;
                    v171.y = v91;
                    v171.z = v92;
                    v171.w = v93;
                    sBtlGetRotateDeg(v171, dir);
                    ToMatrix();
                    vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
                    get_transpose(&v165, &mtx_A, 0);
                    v172 = vct_A;
                    v164 = v165;
                    v168 = op_Multiply_60923920(&v164, v172, 0);
                    vct_A = v168;
                    v97 = hittbl->shatei;
                    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v97);
                    v98 = twk->pos;
                    vct_B = v98;
                    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
                    v100 = posa;
                    v101 = vct_A.x;
                    v102 = *(u64 *)&vct_A.z;
                    vct_A = v100;
                    v103 = twk->pos;
                    vct_B = v103;
                    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
                    sub_1949110(0);
                    v104 = hittbl->shatei;
                    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v104);
                    v106 = twk->pos;
                    vct_B = v106;
                    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
                    posa = vct_A;
                    v107 = posa.y;
                    vct_A.x = v101;
                    vct_A.y = v107;
                    *(u64 *)&vct_A.z = v102;
                    v109 = twk->pos;
                    vct_B = v109;
                    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
                    sub_1949110(0);
                    v110 = hittbl->shatei;
                    v37 = pos;
                    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v110);
                    v111 = twk->pos;
                    vct_B = v111;
                    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
                    posa = vct_A;
                    v112 = posa;
                    vct_A = v112;
                    goto LABEL_322;
                  }
LABEL_203:
                  v85 = v77->UnitMng;
                  v86 = v77->playerID;
                  v68 = sBtlSearchUnit_ID(v85, v86);
                  if (!v68)
                    goto LABEL_209;
                  goto LABEL_206;
                }
                v77 = wk;
                goto LABEL_203;
              case 7:
                v79 = wk;
                v80 = v79->UnitMng;
                v81 = v79->summonID[v116];
                v82 = sBtlSearchUnit_ID(v80, v81);
                if (!v82)
                  goto LABEL_209;
                v68 = v82;
                goto LABEL_208;
              default:
                v68 = 0;
                goto LABEL_210;
            }
            goto LABEL_161;
          }
          sBtlGetCylinderData(v23, v14);
          switch (pwk->takasa)
          {
            case 0:
              v122 = v14->center;
              vct_A = v122;
              v52 = 0.5;
              v53 = v14->e_height;
              v54 = vct_A;
              goto LABEL_141;
            case 1:
              v123 = v14->center;
              vct_A = v123;
              posa = vct_A;
              goto LABEL_152;
            case 2:
              v124 = v14->center;
              vct_A = v124;
              goto LABEL_131;
LABEL_133:
              v52 = -0.5;
              v53 = v14->e_height;
              v54 = vct_A;
              goto LABEL_141;
LABEL_131:
              goto LABEL_133;
            case 3:
              v125 = v14->center;
              vct_A = v125;
              v53 = v14->e_height;
              v54 = vct_A;
              v52 = -0.8;
LABEL_141:
              posa = v54;
              GroundPos = v54.y + (f32)(v53 * v52);
LABEL_151:
              posa.y = GroundPos;
              goto LABEL_152;
            case 5:
              v126 = v14->center;
              vct_A = v126;
              posa = vct_A;
              GroundPos = sBtlGetGroundPos(posa.x, posa.z);
              goto LABEL_151;
            default:
              goto LABEL_152;
          }
          goto LABEL_97;
        }
LABEL_14:
        v118 = v23->pos;
        vct_A = v118;
        posa = vct_A;
        v25 = v23->rot;
        goto LABEL_98;
      }
      v39 = wk;
      goto LABEL_83;
    case 7u:
      v41 = wk;
      v42 = v41->UnitMng;
      v43 = v41->summonID[v116];
      v44 = sBtlSearchUnit_ID(v42, v43);
      if (v44)
      {
        v23 = v44;
        if (sBtlCheckDamageTarget(v23))
          goto LABEL_91;
      }
      goto LABEL_90;
    default:
      v23 = wk;
      goto LABEL_152;
  }
}

// 0x2042000
SBTLDMG_HITWORK *sBtlSearchHit_SerialID(SBTLDMG_HITLISTWORK *lwk, s32 serialID) {
  SBTLDMG_HITWORK *result;

  result = lwk->wk;
  if (result)
  {
    if (lwk->num)
    {
      do
      {
        if (result->serialID == serialID)
          break;
        result = result->next;
      }
      while (result);
    }
    else
    {
      return 0;
    }
  }
  return result;
}

// 0x2042040
s32 sBtlGetKaraburiNum(SBTLDMG_HITLISTWORK *lwk, SBTLDMG_HITWORK *hwk) {
  SBTLDMG_HITWORK *wk;
  s32 result;

  wk = lwk->wk;
  if (!wk || !lwk->num)
    return 0;
  result = 0;
  do
  {
    if (wk->skillid == hwk->skillid && wk->st == 1 && wk->fKaraburi && wk->acterID == hwk->acterID)
    {
      ++result;
    }
    wk = wk->next;
  }
  while (wk);
  return result;
}

// 0x20420a0
static void UnsetKaraburiSub(SBTLDMG_HITLISTWORK *lwk, SBTLDMG_HITWORK *hwk) {
  SBTLDMG_HITWORK *wk;
  s32 skillid;
  s32 acterID;

  wk = lwk->wk;
  if (wk && lwk->num)
  {
    skillid = hwk->skillid;
    acterID = hwk->acterID;
    do
    {
      if (wk->skillid == skillid && wk->acterID == acterID)
        wk->fKaraburi = 0;
      wk = wk->next;
    }
    while (wk);
  }
}

// 0x20420f0
void sBtlUnsetKaraburi(SBTLDMG_HITLISTWORK *lwk, SBTLDMG_HITWORK *hwk) {
  s32 skillid;
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v9;
  SBTLSKILLP_TBL *Skilltbl;
  s32 devilid;
  SBTLDMG_HITWORK *next;
  s32 v13;
  s32 v14;
  SBTLDMG_HITWORK *wk_local;
  s32 v16;
  s32 v17;

  skillid = hwk->skillid;
  acterID = hwk->acterID;
  UnitMng = wk->UnitMng;
  v9 = sBtlSearchUnit_ID(UnitMng, acterID);
  Skilltbl = sBtlGetSkilltbl(skillid);
  if (v9)
  {
    if ((Skilltbl->flg2 & 0x10) != 0)
    {
      wk_local = lwk->wk;
      if (wk_local && lwk->num)
      {
        v16 = hwk->skillid;
        v17 = hwk->acterID;
        do
        {
          if (wk_local->skillid == v16 && wk_local->acterID == v17)
            wk_local->fKaraburi = 0;
          wk_local = wk_local->next;
        }
        while (wk_local);
      }
    }
    else
    {
      if (skillid != 149)
        return;
      devilid = (u16)v9->para->devilid;
      if (v9->para->devilid > 119)
      {
        if (devilid != 140 && devilid != 229 && devilid != 166)
          return;
LABEL_36:
        hwk->fKaraburi = 0;
        return;
      }
      if (devilid == 39 || devilid == 60 || devilid == 119)
        goto LABEL_36;
    }
  }
  else
  {
    next = lwk->wk;
    if (next && lwk->num)
    {
      v13 = hwk->skillid;
      v14 = hwk->acterID;
      do
      {
        if (next->skillid == v13 && next->acterID == v14)
          next->fKaraburi = 0;
        next = next->next;
      }
      while (next);
    }
  }
}

// 0x20422e0
bool sBtlClearHitC(SBTLDMG_HITLISTWORK *lwk, SBTLUNIT_WORK *wk) {
  s32 num;
  s32 v6;
  SBTLDMG_HITWORK *p_wk;
  SBTLDMG_HITWORK *v8;
  s32 serialID;
  SBTLEFF_LISTWORK *effList;

  num = lwk->num;
  if (num >= 1)
  {
    v6 = 0;
    p_wk = &lwk->wk;
    do
    {
      v8 = p_wk;
      if (wk->ListID == p_wk->acterID && (v8->flg & 1) != 0)
      {
        v8->st = 2;
        serialID = v8->serialID;
        effList = wk->effList;
        sBtlForceDelete_SerialID(effList, serialID);
        num = lwk->num;
      }
      ++v6;
      p_wk = &v8->next;
    }
    while (v6 < num);
  }
  return 1;
}

// 0x2042400
void sBtlResetIdouPara(SBTLDMG_HITWORK *hwk) {
  u32 flg;
  sbtldmg_idouwork_tag *iwk;
  SBTLDMG_HITWORK *p_fields;
  s32 v9;
  sdfVector4_t *v10;
  sdfVector4_t *v11;
  f32 shatei;
  struct sdfVector4_t pos;
  sdfVector4_t *p_endpos;
  s32 v17;
  struct sdfVector4_t v18;
  sbtldmg_idouwork_tag *v19;
  sdfVector4_t *p_apos;
  sbtldmg_idouwork_tag *v21;
  sbtldmg_idouwork_tag *v22;
  SBTLSKILLHIT_TBL *p_apos1;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  SBTLSKILLHIT_TBL *hittbl;
  s32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  struct sdfVector4_t apos;
  struct sdfVector4_t rot;
  f32 v38;
  struct sdfVector4_t v43;
  sdfMatrix4_t v45;
  sdfMatrix4_t v46;
  sdfVector4_t v47;
  sdfVector4_t v48;
  sdfVector4_t v50;
  sdfVector4_t v51;

  flg = hwk->flg;
  if ((flg & 0x40000) != 0)
  {
    iwk = hwk->iwk;
    iwk->time = 0.0;
    hwk->counter = hwk->starttime + 2;
    apos = iwk->apos;
    vct_A = apos;
    p_fields = &hwk->fields;
    p_fields->pos = vct_A;
    return;
  }
  if ((flg & 0x100) == 0)
  {
    if ((flg & 0x800) != 0)
      hwk->counter = hwk->starttime;
    return;
  }
  hwk->counter = hwk->starttime + 2;
  rot = hwk->rot;
  vct_A = rot;
  ToMatrix();
  v9 = (u8)byte_5756085;
  vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
  if (v9)
  {
    goto LABEL_20;
  }
  else
  {
    goto LABEL_20;
  }
LABEL_20:
  get_transpose(&v46, &mtx_A, 0);
  v45 = v46;
  v48 = op_Multiply_60923920(&v45, vct_A, 0);
  vct_A = v48;
  shatei = hwk->shatei;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, shatei);
  pos = hwk->pos;
  vct_B = pos;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  p_endpos = &hwk->endpos;
  v17 = (u8)byte_5755EF5;
  *p_endpos = vct_A;
  v18 = hwk->pos;
  if (v17)
    goto LABEL_29;
  goto LABEL_56;
  if (v32)
  {
LABEL_29:
    goto LABEL_30;
  }
LABEL_56:
  v43 = v18;
  v18 = v43;
LABEL_30:
  vct_A = v18;
  v19 = hwk->iwk;
  p_apos = &v19->apos;
  *p_apos = vct_A;
  v21 = hwk->iwk;
  v21->time = 0.0;
  v22 = &v21->fields;
  p_apos1 = &v21->apos1;
  v50 = hwk->pos;
  x = hwk->endpos.x;
  y = hwk->endpos.y;
  z = hwk->endpos.z;
  w = hwk->endpos.w;
  hittbl = hwk->hittbl;
  v35 = v50.y;
  v38 = v50.x;
  v33 = v50.w;
  v34 = v50.z;
  v50.w = v33;
  v50.z = v34;
  v50.y = v35;
  v50.x = v38;
  v51.x = x;
  v51.y = y;
  *(u64 *)&v47.x = hittbl;
  v51.z = z;
  v51.w = w;
  *(u64 *)&v47.z = v22;
  sBtlSetApos12(v50, v51, v47, p_apos1, v10, v11);
}

// 0x20429b0
bool sBtlHitCProc_Idou(SBTLDMG_HITLISTWORK *lwk) {
  SBTLDMG_HITWORK *next;
  f32 v7;
  f32 v8;
  f32 v9;
  bool IsSceanStop;
  u32 flg;
  dds3ModelHandle_t *hModel;
  s32 eListID;
  SBTLEFF_LISTWORK *effList;
  SBTLEFF_WORK *EffectWork_ID;
  u32 v20;
  SBTLEFF_WORK *v21;
  s32 v22;
  s32 st;
  s32 v24;
  s32 starttime;
  dds3ModelHandle_t *v26;
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v30;
  SBTLUNIT_WORK *v31;
  SBTLSKILLHIT_POSWORK *start;
  u16 type;
  u32 v35;
  s32 counter;
  s32 v37;
  s32 skillid;
  s32 v39;
  s32 v40;
  s32 v41;
  dds3ModelHandle_t *v42;
  s32 v44;
  SBTLUNIT_LISTWORK *v45;
  SBTLUNIT_WORK *v46;
  SBTLUNIT_WORK *v47;
  s32 v49;
  SBTLEFF_LISTWORK *v50;
  SBTLEFF_WORK *v51;
  SBTLSKILLHIT_POSWORK *v53;
  SBTLEFF_WORK *v54;
  u16 v55;
  u32 v56;
  SBTLUNIT_WORK *v57;
  SBTLDMG_HITWORK *v58;
  SBTLEFF_WORK *v59;
  f32 v60;
  sdfVector4_t *p_pos;
  sdfVector4_t *p_oldpos;
  s32 v67;
  SBTLEFF_LISTWORK *v68;
  SBTLEFF_WORK *v69;
  SBTLEFF_WORK *v70;
  s32 v72;
  SBTLUNIT_LISTWORK *v73;
  SBTLUNIT_WORK *v74;
  SBTLUNIT_WORK *v75;
  s32 v77;
  SBTLUNIT_LISTWORK *v78;
  SBTLUNIT_WORK *v79;
  SBTLSKILLHIT_TBL *v80;
  SBTLSKILLHIT_POSWORK *v81;
  SBTLUNIT_WORK *v82;
  u16 v83;
  SBTLSKILLHIT_POSWORK *end;
  f32 v85;
  f32 v86;
  u32 v87;
  s32 cmpcounter;
  dds3ModelHandle_t *v89;
  f32 kasokudo;
  f32 sokudo;
  sbtldmg_idouwork_tag *iwk;
  f32 v93;
  s32 v95;
  SBTLUNIT_LISTWORK *v96;
  SBTLUNIT_WORK *v97;
  SBTLUNIT_WORK *v98;
  s32 v100;
  SBTLEFF_LISTWORK *v101;
  SBTLEFF_WORK *v102;
  SBTLSKILLHIT_POSWORK *v104;
  SBTLEFF_WORK *v105;
  u16 v106;
  u32 v107;
  SBTLUNIT_WORK *v108;
  SBTLDMG_HITWORK *v109;
  SBTLEFF_WORK *v110;
  f32 v111;
  dds3ModelHandle_t *v112;
  f32 v113;
  f32 v114;
  f32 v115;
  f32 v116;
  long f64 v117;
  long f64 v118;
  dds3ModelHandle_t *v119;
  long f64 v120;
  long f64 v121;
  long f64 v122;
  long f64 v123;
  f32 *v124;
  f32 v125;
  SBATTLE_WORK *v127;
  SBTLUNIT_LISTWORK *v128;
  s32 playerID;
  struct sdfVector4_t v131;
  struct sdfVector4_t v133;
  f32 v134;
  f32 v135;
  f32 v136;
  f32 v137;
  f32 v138;
  f32 v139;
  f32 v140;
  f32 v141;
  struct sdfVector4_t v143;
  struct sdfVector4_t v144;
  f32 *p_x;
  f32 v146;
  f32 v147;
  f32 v148;
  s32 v150;
  u16 v151;
  SBTLSKILLHIT_POSWORK *v152;
  f32 v153;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  long f64 v158;
  long f64 v159;
  long f64 v160;
  s32 targetID;
  SBTLUNIT_LISTWORK *v163;
  SBTLUNIT_WORK *v164;
  sdfVector4_t *v165;
  sdfVector4_t *v166;
  f32 *v168;
  f32 v171;
  SBTLSKILLHIT_TBL *hittbl;
  f32 v173;
  f32 v174;
  sbtldmg_idouwork_tag *v175;
  f32 v176;
  f32 v177;
  f32 v178;
  f32 v179;
  f32 v180;
  f32 v181;
  f32 v182;
  f32 v183;
  long f64 v184;
  f32 v185;
  long f64 v186;
  s32 v188;
  SBTLUNIT_LISTWORK *v189;
  SBTLUNIT_WORK *v190;
  s32 v191;
  SBTLEFF_LISTWORK *v192;
  SBTLEFF_WORK *v193;
  SBTLEFF_WORK *v194;
  SBTLSKILLHIT_TBL *v196;
  SBTLSKILLHIT_POSWORK *v197;
  u32 v198;
  f32 v199;
  f32 v200;
  f32 v201;
  f32 v202;
  f32 v203;
  f32 v204;
  f32 v205;
  f32 v206;
  f32 namatuba_1st_spdnml;
  s32 v211;
  f32 v212;
  u16 v213;
  SBTLSKILLHIT_POSWORK *v214;
  u16 v216;
  SBTLSKILLHIT_POSWORK *v217;
  f32 v218;
  f32 v219;
  f32 v220;
  f32 v221;
  f32 v222;
  f32 LenXZ;
  f32 LenXYZ;
  f32 v225;
  sdfVector4_t v227;
  struct sdfVector4_t v228;
  struct sdfVector4_t v230;
  f32 v231;
  f32 v232;
  f32 v233;
  f32 v234;
  f32 v235;
  f32 v236;
  f32 v237;
  f32 v238;
  f32 *v239;
  f32 v240;
  f32 v241;
  f32 v242;
  f32 v243;
  f32 v244;
  f32 v245;
  f32 *v246;
  f32 v247;
  f32 *v248;
  f32 v249;
  f32 v250;
  f32 v251;
  f32 v252;
  f32 v253;
  long f64 v254;
  f32 v255;
  f32 v256;
  f32 v257;
  f32 v258;
  f32 v259;
  long f64 v260;
  sbtldmg_idouwork_tag *v261;
  f32 v262;
  f32 v263;
  f32 v264;
  f32 v265;
  f32 time;
  f32 Bezier;
  sbtldmg_idouwork_tag *v268;
  f32 v269;
  sbtldmg_idouwork_tag *v270;
  f32 v271;
  s64 v272;
  long f64 v273;
  long f64 v274;
  f32 v275;
  long f64 v276;
  s64 v277;
  s64 v278;
  long f64 v279;
  MethodInfo *methoda;
  f32 v281;
  f32 v282;
  f32 v283;
  f32 v284;
  struct sdfVector4_t v285;
  struct sdfVector4_t startpos;
  sdfVector4_t startposa;
  f32 startposd;
  struct sdfVector4_t startposb;
  f32 startposc;
  sdfVector4_t pos;
  s64 x2;
  s64 v307;
  s64 x1;
  s64 v309;
  s64 v310;
  s64 v311;
  u64 v312[2];
  __int128 v313;
  u64 v314[3];
  sdfVector4_t v315;
  sdfVector4_t v316;
  sdfVector4_t v317;
  sdfVector4_t v318;
  sdfVector4_t v319;
  sdfVector4_t v320;
  sdfVector4_t v321;
  sdfVector4_t v322;
  sdfVector4_t v323;

  v314[0] = 0;
  v314[1] = 0;
  v312[0] = 0;
  v312[1] = 0;
  v310 = 0;
  v311 = 0;
  x1 = 0;
  v309 = 0;
  x2 = 0;
  v307 = 0;
  *(u64 *)&pos.x = 0;
  *(u64 *)&pos.z = 0;
  v313 = xmmword_3CFD5C0;
  if (!wk->hitList)
    return 0;
  if (wk->bEffStop)
    return 0;
  next = lwk->wk;
  if (!next || !lwk->num)
    return 0;
  v7 = 1.0;
  v8 = 5.0;
  v9 = 4.0;
  do
  {
    IsSceanStop = IsSceanStop();
    flg = next->flg;
    if (IsSceanStop)
    {
      if ((flg & 0x80) == 0)
      {
        if ((flg & 0x1000) != 0)
        {
          hModel = next->hModel;
          if (hModel)
          {
            mdlSetMotionSpeed(hModel, 0.0);
          }
        }
        goto LABEL_16;
      }
    }
    if ((flg & 0x900) == 0 || next->st != 1)
      goto LABEL_16;
    if (next->pathflg == 2)
      next->pathflg = 1;
    if ((flg & 0x40) != 0)
    {
      eListID = next->eListID;
      if (eListID != -1)
      {
        eListID = next->eListID;
        effList = wk->effList;
        EffectWork_ID = sBtlGetEffectWork_ID(effList, eListID);
        if (!EffectWork_ID)
          goto LABEL_16;
        v20 = next->flg;
        v21 = EffectWork_ID;
        if ((v20 & 0x1000) != 0 && next->skillid == 444)
        {
          v22 = 2;
          st = EffectWork_ID->st;
          if (st != 2)
            goto LABEL_40;
        }
        else
        {
          v22 = 1;
          st = EffectWork_ID->st;
          if (st != 2)
          {
LABEL_40:
            if ((u32)(st - 5) < 0xFFFFFFFD)
              goto LABEL_16;
            goto LABEL_62;
          }
        }
        v24 = EffectWork_ID->counter + v22;
        starttime = EffectWork_ID->starttime;
        if (starttime > v24)
          goto LABEL_16;
        if (starttime == v24)
        {
          if ((v20 & 0x1000) != 0)
          {
            v26 = next->hModel;
            if (v26)
            {
              mdlSmoothSingleMotion(v26, 0, 0, 0.0, 0.0, 0.0);
            }
            next->pathflg = 2;
          }
          acterID = next->acterID;
          UnitMng = wk->UnitMng;
          v30 = sBtlSearchUnit_ID(UnitMng, acterID);
          if (v30)
          {
            v31 = v30;
            if (sBtlCheckDamageTarget(v31))
            {
              start = next->start;
              type = next->type;
              sBtlResetHitPos_XYZ(v31, next, v21, start, &next->pos, &next->rot, type);
            }
          }
        }
      }
    }
LABEL_62:
    v35 = next->flg;
    counter = next->counter;
    v37 = next->life + next->starttime;
    if ((v35 & 0x60000) != 0)
    {
      if (v37 != counter)
        goto LABEL_76;
      skillid = next->skillid;
      if (skillid <= 1130)
      {
        if (skillid == 443 || skillid == 903)
          goto LABEL_76;
      }
      else if (skillid == 1131 || skillid == 1236 || skillid == 1250)
      {
        goto LABEL_76;
      }
      sBtlResetIdouPara(next);
      v35 = next->flg;
    }
    else if (v37 <= counter)
    {
      goto LABEL_16;
    }
LABEL_76:
    if ((v35 & 0x10000) != 0)
    {
      v40 = next->counter;
      v41 = next->starttime;
      if (v41 > v40)
        goto LABEL_16;
      if (v41 == v40 || v41 <= 0 && v40 == 1)
      {
        if ((v35 & 0x1000) != 0)
        {
          v42 = next->hModel;
          if (v42)
          {
            mdlSmoothSingleMotion(v42, 0, 0, 0.0, 0.0, 0.0);
          }
          next->pathflg = 2;
        }
        v44 = next->acterID;
        v45 = wk->UnitMng;
        v46 = sBtlSearchUnit_ID(v45, v44);
        if (v46)
        {
          v47 = v46;
          if (sBtlCheckDamageTarget(v47))
          {
            v49 = next->eListID;
            v50 = wk->effList;
            v51 = sBtlGetEffectWork_ID(v50, v49);
            v53 = next->start;
            v54 = v51;
            v55 = next->type;
            if (v51)
            {
              if (!v56)
              v57 = v47;
              v58 = next;
              v59 = v54;
            }
            else
            {
              if (!v56)
              v57 = v47;
              v58 = next;
              v59 = 0;
            }
            sBtlResetHitPos_XYZ(v57, v58, v59, v53, &next->pos, &next->rot, v55);
          }
        }
      }
    }
    v39 = next->skillid;
    if (v39 > 1130)
    {
      if (v39 != 1131 && v39 != 1250 && v39 != 1236)
      {
LABEL_156:
        v87 = next->flg;
        if ((v87 & 0x11040) == 0x1000)
        {
LABEL_159:
          if (next->starttime == next->counter)
          {
            v89 = next->hModel;
            if (v89)
            {
              mdlSmoothSingleMotion(v89, 0, 0, 0.0, 0.0, 0.0);
              v87 = next->flg;
            }
            next->pathflg = 2;
          }
        }
LABEL_165:
        if ((v87 & 0x800) != 0 || next->starttime == next->counter && !next->pathflg)
        {
          v95 = next->acterID;
          v96 = wk->UnitMng;
          v97 = sBtlSearchUnit_ID(v96, v95);
          if (v97)
          {
            v98 = v97;
            if (v97->hModel)
            {
              v100 = next->eListID;
              v101 = wk->effList;
              v102 = sBtlGetEffectWork_ID(v101, v100);
              v104 = next->start;
              v105 = v102;
              v106 = next->type;
              if (v102)
              {
                if (!v107)
                v108 = v98;
                v109 = next;
                v110 = v105;
              }
              else
              {
                if (!v107)
                v108 = v98;
                v109 = next;
                v110 = 0;
              }
              sBtlResetHitPos_XYZ(v108, v109, v110, v104, &next->pos, &next->rot, v106);
            }
          }
        }
        else
        {
          if ((v87 & 0x1000) == 0)
          {
            kasokudo = next->kasokudo;
            if (kasokudo < 0.1 && kasokudo > -0.1)
            {
              sokudo = next->sokudo;
              next->spd = sokudo;
              goto LABEL_172;
            }
            sokudo = kasokudo + next->spd;
            next->spd = sokudo;
            if (kasokudo > -0.1 || sokudo >= 0.0)
            {
LABEL_172:
              if (sokudo <= 0.0)
                goto LABEL_245;
              iwk = next->iwk;
              v93 = v7 / (f32)(next->shatei / sokudo);
              iwk->addtime = v93;
            }
            else
            {
              next->spd = 0.0;
LABEL_245:
              iwk = next->iwk;
              v93 = 0.0;
              iwk->addtime = 0.0;
            }
            v153 = iwk->time + v93;
            iwk->time = v153;
            if (v153 < v7)
            {
              x = next->pos.x;
              y = next->pos.y;
              z = next->pos.z;
              w = next->pos.w;
              *(__n128 *)&v158 = sub_1B332C0(0, x, y, z, w);
              *(__n128 *)&v159 = sub_1B335A0(v312, 0, v158);
              *(__n128 *)&v160 = sub_1B335A0(&v313, 0, v159);
              sub_1B335A0(&next->oldpos, 0, v160);
              targetID = next->targetID;
              v163 = wk->UnitMng;
              v164 = sBtlSearchUnit_ID(v163, targetID);
              if ((next->flg & 0x400) != 0 && (v168 = (f32 *)v164) != 0)
              {
                v317.x = next->pos.x;
                v317.y = next->pos.y;
                v317.z = next->pos.z;
                v171 = next->pos.w;
                hittbl = next->hittbl;
                v173 = next->endpos.x;
                v174 = next->endpos.y;
                v175 = next->iwk;
                v176 = next->endpos.z;
                v321.w = next->endpos.w;
                v177 = next->rot.x;
                v178 = next->rot.y;
                startposd = next->pos.x;
                v282 = next->pos.z;
                v284 = next->pos.y;
                v281 = next->endpos.w;
                v321.w = v281;
                v317.z = v282;
                v317.y = v284;
                v317.x = startposd;
                v317.w = v171;
                v321.x = v173;
                *(u64 *)&v315.z = &v175->fields;
                v321.y = v174;
                v321.z = v176;
                *(u64 *)&v315.x = hittbl;
                methoda = __PAIR64__(LODWORD(v178), LODWORD(v177));
                sBtlSetApos12(v317, v321, v315, &v175->apos1, v165, v166);
                v179 = v168[41];
                v180 = v168[42];
                v181 = v168[43];
                v182 = v168[44];
                sub_1B332C0(0, v179, v180, v181, v182);
                sub_1B33360(0, next->iwk->apos0.x, next->iwk->apos0.y, next->iwk->apos0.z, next->iwk->apos0.w);
                sub_1B33400(0);
                v183 = (loc_1CDE880)(0);
                sub_1949110(0);
                sub_1B33480(0, (f32)(v183 * next->iwk->apos0_per) * next->homingpara);
                sub_1B33360(0, next->iwk->apos0.x, next->iwk->apos0.y, next->iwk->apos0.z, next->iwk->apos0.w);
                *(__n128 *)&v184 = sub_1B33520(0);
                sub_1B335A0(&x1, 0, v184);
                sub_1B332C0(0, v168[41], v168[42], v168[43], v168[44]);
                sub_1B33360(0, next->iwk->apos1.x, next->iwk->apos1.y, next->iwk->apos1.z, next->iwk->apos1.w);
                sub_1B33400(0);
                v185 = (loc_1CDE880)(0);
                sub_1949110(0);
                sub_1B33480(0, (f32)(v185 * next->iwk->apos1_per) * next->homingpara);
                sub_1B33360(0, next->iwk->apos1.x, next->iwk->apos1.y, next->iwk->apos1.z, next->iwk->apos1.w);
                *(__n128 *)&v186 = sub_1B33520(0);
                sub_1B335A0(&x2, 0, v186);
                v7 = 1.0;
                v8 = 5.0;
                v9 = 4.0;
                v188 = next->acterID;
                v189 = wk->UnitMng;
                v190 = sBtlSearchUnit_ID(v189, v188);
                v191 = next->eListID;
                v192 = wk->effList;
                v193 = sBtlGetEffectWork_ID(v192, v191);
                if (v190 && (v194 = v193) != 0)
                {
                  ClassCopy(sbtl_dmgdummy, next, 0);
                  sBtlGetHit_OnlyEndPos(v190, next, v194, v196, v197, next->hittbl->end, &pos, next->type);
                }
                else
                {
                  v250 = v168[41];
                  v251 = v168[42];
                  v252 = v168[43];
                  v253 = v168[44];
                  *(__n128 *)&v254 = sub_1B332C0(0, v250, v251, v252, v253);
                  sub_1B335A0(&pos, 0, v254);
                }
                v255 = pos.x;
                v256 = pos.y;
                v257 = pos.z;
                v258 = pos.w;
                sub_1B332C0(0, v255, v256, v257, v258);
                sub_1B33360(0, next->endpos.x, next->endpos.y, next->endpos.z, next->endpos.w);
                sub_1B33400(0);
                v259 = (loc_1CDE880)(0);
                sub_1949110(0);
                sub_1B33480(0, v259 * next->homingpara);
                sub_1B33360(0, next->endpos.x, next->endpos.y, next->endpos.z, next->endpos.w);
                *(__n128 *)&v260 = sub_1B33520(0);
                sub_1B335A0(&pos, 0, v260);
                v261 = next->iwk;
                v262 = *(f32 *)&x1;
                v263 = *(f32 *)&x2;
                v264 = pos.x;
                v265 = v261->apos.x;
                time = v261->time;
                Bezier = sBtlGetBezier(v265, v262, v263, v264, time);
                v268 = next->iwk;
                *(f32 *)&v313 = Bezier;
                v269 = sBtlGetBezier(v268->apos.y, *((f32 *)&x1 + 1), *((f32 *)&x2 + 1), pos.y, v268->time);
                v270 = next->iwk;
                *((f32 *)&v313 + 1) = v269;
                v249 = sBtlGetBezier(v270->apos.z, *(f32 *)&v309, *(f32 *)&v307, pos.z, v270->time);
              }
              else
              {
                v239 = next->iwk;
                v240 = next->endpos.x;
                v241 = v239[12];
                v242 = v239[4];
                v243 = v239[8];
                v244 = v239[22];
                v245 = sBtlGetBezier(v241, v242, v243, v240, v244);
                v246 = next->iwk;
                *(f32 *)&v313 = v245;
                v247 = sBtlGetBezier(v246[13], v246[5], v246[9], next->endpos.y, v246[22]);
                v248 = next->iwk;
                *((f32 *)&v313 + 1) = v247;
                v249 = sBtlGetBezier(v248[14], v248[6], v248[10], next->endpos.z, v248[22]);
              }
              *((f32 *)&v313 + 2) = v249;
              v271 = *((f32 *)&v313 + 3);
              v272 = v313;
              *(__n128 *)&v273 = sub_1B332C0(0, *(f32 *)&v272, *((f32 *)&v272 + 1), v249, v271);
              *(__n128 *)&v274 = sub_1B335A0(&next->fields, 0, v273);
              sub_1B335A0(&next->fields, 0, v274);
              sub_1B33360(0, next->oldpos.x, next->oldpos.y, next->oldpos.z, next->oldpos.w);
              sub_1B33400(0);
              v275 = (loc_1CDE880)(0);
              sub_1949110(0);
              sub_1B335A0(&v310, 0, v276);
              if (v275 >= next->spd)
              {
                v277 = v310;
                v278 = v311;
                sub_1B332C0(0, *(f32 *)&v277, *((f32 *)&v277 + 1), *(f32 *)&v278, *((f32 *)&v278 + 1));
                sub_1B33480(0, next->spd);
                sub_1B33360(0, next->oldpos.x, next->oldpos.y, next->oldpos.z, next->oldpos.w);
                *(__n128 *)&v279 = sub_1B33520(0);
                sub_1B335A0(&next->fields, 0, v279);
              }
              goto LABEL_275;
            }
LABEL_270:
            iwk->time = 1.0;
            goto LABEL_275;
          }
          iwk = next->iwk;
          v111 = iwk->time + iwk->addtime;
          iwk->time = v111;
          if (v111 >= v7)
            goto LABEL_270;
          v112 = next->hModel;
          if (v112)
          {
            if (!mdlChkMotionEnd(v112))
            {
              v113 = next->pos.x;
              v114 = next->pos.y;
              v115 = next->pos.z;
              v116 = next->pos.w;
              *(__n128 *)&v117 = sub_1B332C0(0, v113, v114, v115, v116);
              *(__n128 *)&v118 = sub_1B335A0(v312, 0, v117);
              sub_1B335A0(&next->oldpos, 0, v118);
              v119 = next->hModel;
              mdlSetMotionSpeed(v119, v7);
              sdfModelGetMarkPos(next->hModel->modelRoot, 0);
              *(__n128 *)&v121 = sub_1B335A0(v314, 0, v120);
              sub_1B335A0(&next->fields, 0, v121);
              sub_1B332C0(0, next->rot.x, next->rot.y, next->rot.z, next->rot.w);
              ToMatrix();
              *(__n128 *)&v122 = sub_1B332C0(0, next->pos.x, next->pos.y, next->pos.z, next->pos.w);
              v123 = (loc_1EA2510)(0, v122);
              sub_1B335A0(&next->fields, 0, v123);
              v124 = next->iwk;
              v125 = next->pos.y;
              next->pos.x = next->pos.x + v124[12];
              next->pos.y = v125 + v124[13];
              next->pos.z = next->pos.z + v124[14];
            }
          }
        }
LABEL_275:
        v198 = next->flg;
        if ((v198 & 0x100) != 0)
        {
          v199 = next->pos.x;
          v200 = next->pos.y;
          v201 = next->pos.z;
          v202 = next->pos.w;
          v203 = next->oldpos.x;
          v204 = next->oldpos.y;
          v205 = next->oldpos.z;
          v206 = next->oldpos.w;
          v318.x = v199;
          v318.y = v200;
          v318.z = v201;
          v318.w = v202;
          v322.x = v203;
          v322.y = v204;
          v322.z = v205;
          v322.w = v206;
          sBtlGetQuat(v318, v322);
          v7 = 1.0;
          v8 = 5.0;
          v9 = 4.0;
          next->rot = vct_A;
          v198 = next->flg;
        }
        if ((v198 & 0x1000) == 0)
          goto LABEL_16;
        startposb = next->pBasic->poseset->rot;
        goto LABEL_285;
LABEL_286:
        vct_A = startposb;
LABEL_295:
        next->rot = vct_A;
        goto LABEL_16;
LABEL_285:
        goto LABEL_286;
LABEL_382:
        goto LABEL_295;
      }
LABEL_113:
      v60 = next->sokudo;
      goto LABEL_114;
    }
    if (v39 == 443)
      goto LABEL_113;
    if (v39 != 903)
      goto LABEL_156;
    v60 = 3.0;
    if (next->counter < 50)
      v60 = v7;
LABEL_114:
    if (v39 == 1131)
      v60 = v8;
    p_pos = &next->pos;
    if (v39 == 1236 || v39 == 1250)
      v60 = v9;
    v283 = v60;
    startpos = next->pos;
    vct_A = startpos;
    p_oldpos = &next->oldpos;
    next->oldpos = vct_A;
    v67 = next->eListID;
    v68 = wk->effList;
    v69 = sBtlGetEffectWork_ID(v68, v67);
    if (!v69)
      goto LABEL_156;
    v70 = v69;
    v72 = next->acterID;
    v73 = wk->UnitMng;
    v74 = sBtlSearchUnit_ID(v73, v72);
    if (!v74)
    {
      cmpcounter = v70->cmpcounter;
      v70->counter = cmpcounter;
      next->counter = cmpcounter;
      v87 = next->flg;
      if ((v87 & 0x11040) == 0x1000)
        goto LABEL_159;
      goto LABEL_165;
    }
    v75 = v74;
    v77 = next->targetID;
    v78 = wk->UnitMng;
    v79 = sBtlSearchUnit_ID(v78, v77);
    if (!v79)
    {
      v127 = wk;
      v128 = v127->UnitMng;
      playerID = v127->playerID;
      sBtlSearchUnit_ID(v128, playerID);
      startposa = v75->namatuba_goal_pos;
      vct_A = startposa;
      v131 = *p_pos;
      goto LABEL_207;
LABEL_208:
      goto LABEL_209;
LABEL_207:
      vct_B = v131;
      goto LABEL_208;
LABEL_209:
      vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      sub_1949110(0);
      vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v283);
      v133 = *p_pos;
      goto LABEL_215;
LABEL_216:
      goto LABEL_217;
LABEL_215:
      vct_B = v133;
      goto LABEL_216;
LABEL_217:
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v134 = next->oldpos.x;
      v135 = next->oldpos.y;
      v136 = next->oldpos.z;
      v137 = next->oldpos.w;
      *p_pos = vct_A;
      v138 = next->pos.x;
      v139 = next->pos.y;
      v140 = next->pos.z;
      v141 = next->pos.w;
      v316.x = v138;
      v316.y = v139;
      v316.z = v140;
      v316.w = v141;
      v320.x = v134;
      v320.y = v135;
      v320.z = v136;
      v320.w = v137;
      sBtlGetQuat(v316, v320);
      v7 = 1.0;
      v8 = 5.0;
      v9 = 4.0;
      next->rot = vct_A;
      v143 = *p_pos;
      goto LABEL_229;
LABEL_230:
      goto LABEL_231;
LABEL_232:
      goto LABEL_233;
LABEL_229:
      vct_A = v143;
      v144 = *p_oldpos;
      goto LABEL_230;
LABEL_231:
      vct_B = v144;
      goto LABEL_232;
LABEL_233:
      vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      goto LABEL_235;
LABEL_236:
      goto LABEL_237;
LABEL_235:
      p_x = &vf00.x;
      v146 = p_x[4];
      v147 = p_x[5];
      v148 = p_x[6];
      goto LABEL_236;
LABEL_237:
      if (sqrtf((f32)((f32)(v146 * v146) + (f32)(v147 * v147)) + (f32)(v148 * v148)) < 10.0)
      {
        v150 = v70->cmpcounter;
        v70->counter = v150;
        next->counter = v150;
      }
      goto LABEL_16;
    }
    if (next->skillid == 443)
    {
      if (v75->namatuba_homing_on)
      {
        v82 = v79;
        v83 = next->type;
        end = next->hittbl->end;
        sBtlGetHit_OnlyEndPos(v75, next, v70, v80, v81, end, &pos, v83);
        if ((v82->side & 0x80) != 0)
        {
          v85 = pos.y;
          pos.y = v85 + sBtlGetJumpY(v82);
        }
        v86 = v75->namatuba_1st_spdnml + 0.033333335;
        v75->namatuba_1st_spdnml = v86;
        if (v86 > v7)
          v75->namatuba_1st_spdnml = 1.0;
      }
      else
      {
        namatuba_1st_spdnml = v75->namatuba_1st_spdnml;
        v211 = v75->namatuba_cnt + 1;
        v75->namatuba_cnt = v211;
        v212 = namatuba_1st_spdnml + -0.011666667;
        if (v212 < 0.1)
          v212 = 0.1;
        v75->namatuba_1st_spdnml = v212;
        if (v211 >= 60)
        {
          v75->namatuba_homing_on = 1;
          v216 = next->type;
          v217 = next->hittbl->end;
          sBtlGetHit_OnlyEndPos(v75, next, v70, v80, v81, v217, &pos, v216);
        }
        else
        {
          v213 = next->type;
          v214 = next->hittbl->end;
          sBtlGetHit_OnlyEndPos(v75, next, v70, v80, v81, v214, &pos, v213);
          pos.x = v75->namatuba_1st_pos.x;
          pos.z = v75->namatuba_1st_pos.z;
        }
      }
      v218 = v75->namatuba_1st_spdnml;
      pos.w = 0.0;
      v283 = v283 * v218;
    }
    else
    {
      v151 = next->type;
      v152 = next->hittbl->end;
      sBtlGetHit_OnlyEndPos(v75, next, v70, v80, v81, v152, &pos, v151);
    }
    v219 = next->pos.x;
    v220 = next->pos.z;
    v221 = pos.x;
    v222 = pos.z;
    LenXZ = sBtlGetLenXZ(v219, v220, v221, v222);
    LenXYZ = sBtlGetLenXYZ(next->pos.x, next->pos.y, next->pos.z, pos.x, pos.y, pos.z);
    if (v283 <= LenXYZ)
      v225 = v283;
    else
      v225 = LenXYZ;
    v285 = pos;
    startposc = v225;
    vct_A = v285;
    v75->namatuba_goal_pos = vct_A;
    v227 = pos;
    vct_A = v227;
    v228 = *p_pos;
    vct_B = v228;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    sub_1949110(0);
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, startposc);
    v230 = *p_pos;
    vct_B = v230;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    *p_pos = vct_A;
    if (LenXZ > v7)
    {
      v231 = next->pos.x;
      v232 = next->pos.y;
      v233 = next->pos.z;
      v234 = next->pos.w;
      v235 = next->oldpos.x;
      v236 = next->oldpos.y;
      v237 = next->oldpos.z;
      v238 = next->oldpos.w;
      v319.x = v231;
      v319.y = v232;
      v319.z = v233;
      v319.w = v234;
      v323.x = v235;
      v323.y = v236;
      v323.z = v237;
      v323.w = v238;
      sBtlGetQuat(v319, v323);
      v7 = 1.0;
      v8 = 5.0;
      v9 = 4.0;
      goto LABEL_382;
    }
LABEL_16:
    next = next->next;
  }
  while (next);
  return 1;
}

// 0x2044a40
bool sBtlHitCProc(SBTLDMG_HITLISTWORK *lwk) {
  SBTLDMG_HITWORK *next;
  bool result;
  s32 eListID;
  SBTLEFF_LISTWORK *effList;
  s32 EffectStat_ID;
  u32 flg;
  s32 v18;
  SBTLEFF_LISTWORK *v19;
  SBTLEFF_WORK *EffectWork_ID;
  u32 v21;
  s32 counter;
  s32 starttime;
  s32 skillid;
  s32 v25;
  SBTLUNIT_LISTWORK *p_lwk;
  SBTLUNIT_LISTWORK *v27;
  s64 v28;
  bool v29;
  SBTLUNIT_WORK *pUnit;
  SBTLUNIT_WORK *v33;
  s32 v34;
  SBTLUNIT_WORK *v37;
  bool v38;
  SBTLUNIT_LISTWORK *v40;
  s32 serialID;
  SBTLEFF_LISTWORK *v43;
  s32 hitflg;

  if (!wk->hitList)
    return 0;
  if (wk->bEffStop)
    return 0;
  next = lwk->wk;
  if (!next || !lwk->num)
    return 0;
  if (sBtlHDloadChk(114))
  {
    if (IsSceanStop())
    {
      if (wk->mode == 2)
        return 0;
    }
    if (sBtlPlayerCheckRSpirit_Start())
      return 0;
    while (1)
    {
      if (!!IsSceanStop())
      {
        if ((next->flg & 0x80) == 0)
        {
          if ((wk->scrFlag & 0x80000) == 0)
            goto LABEL_30;
        }
      }
      ++next->counter;
      LimitRange(&next->counter, 0, 0x7FFF);
      if (next->st != 1)
        goto LABEL_30;
      eListID = next->eListID;
      hitflg = 0;
      if (eListID == -1)
        goto LABEL_57;
      eListID = next->eListID;
      effList = wk->effList;
      EffectStat_ID = sBtlGetEffectStat_ID(effList, eListID);
      flg = next->flg;
      if (EffectStat_ID != -1)
      {
        if ((flg & 0x40) != 0)
        {
          v18 = next->eListID;
          v19 = wk->effList;
          EffectWork_ID = sBtlGetEffectWork_ID(v19, v18);
          if (EffectWork_ID)
          {
            if (EffectWork_ID->st <= 2)
            {
              next->counter = 0;
              goto LABEL_30;
            }
          }
        }
LABEL_57:
        v21 = next->flg;
        if ((v21 & 0x1000) != 0 && next->pathflg != 1)
          goto LABEL_30;
        counter = next->counter;
        starttime = next->starttime;
        if (starttime > counter)
          goto LABEL_30;
        if ((v21 & 0x60000) != 0 || next->life + starttime > counter)
        {
          skillid = next->skillid;
          if (skillid <= 902)
          {
            if (skillid == 72)
            {
              v25 = starttime + 900;
              goto LABEL_76;
            }
            if (skillid != 443)
            {
              if (skillid == 465)
              {
                v25 = starttime + 600;
LABEL_76:
                if (v25 <= counter)
                {
                  next->st = 2;
                  serialID = next->serialID;
                  v43 = wk->effList;
                  sBtlSetDecAlpha_SerialID(v43, serialID, 4);
                  sBtlForceDelete_SerialID(wk->effList, next->serialID);
                  goto LABEL_30;
                }
              }
LABEL_77:
              if (!next->lwk)
              {
                CreateTargetList(next, skillid);
              }
              p_lwk = &next->lwk;
              if ((next->area & 1) != 0)
              {
                v33 = sBtlCheckHitArea_Single(next);
                if (v33)
                {
                  v37 = v33;
                  v38 = sBtlSetHit(next, v37, &hitflg);
                  sBtlUnsetKaraburi(lwk, next);
                  if (!v38)
                    goto LABEL_102;
                }
                if ((next->flg & 0x4000) != 0)
                {
                  if (!sBtlCheckGround(next, v34))
LABEL_102:
                    next->st = 2;
                }
              }
              else
              {
                v27 = p_lwk;
                if (p_lwk->count >= 1)
                {
                  v28 = 0;
                  do
                  {
                    pUnit = v27->pUnitL[v28]->pUnit;
                    if (pUnit)
                    {
                      if (sBtlCheckHitArea(next, pUnit))
                      {
                        v29 = sBtlSetHit(next, pUnit, &hitflg);
                        sBtlUnsetKaraburi(lwk, next);
                        if (!v29)
                          break;
                      }
                    }
                    v27 = p_lwk;
                    ++v28;
                  }
                  while (v28 < p_lwk->count);
                }
                if ((next->flg & 0x4000) != 0)
                {
                  sBtlCheckGround(next, (s32)v11);
                }
              }
              v40 = p_lwk;
              if (p_lwk)
              {
                sBtlDeleteUnitList(v40, 0);
                p_lwk = 0;
              }
              goto LABEL_30;
            }
          }
          else if (skillid > 1235)
          {
            if (skillid != 1236 && skillid != 1250)
              goto LABEL_77;
          }
          else if (skillid != 903 && skillid != 1131)
          {
            goto LABEL_77;
          }
          if (starttime + 900 > counter)
            goto LABEL_77;
        }
        goto LABEL_29;
      }
      if ((flg & 0x200) != 0)
        goto LABEL_57;
LABEL_29:
      next->st = 2;
LABEL_30:
      next = next->next;
      result = 1;
      if (!next)
        return result;
    }
  }
  return 0;
}

// 0x2046830
bool sBtlCheckActDamage(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, SKLID skillid) {
  SBTLDMG_HITWORK *v7;
  s32 side;
  s32 v9;
  SBTLUNIT_WORK *v10;
  bool result;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v13;
  s32 weak_attrinvtime_max;
  s32 flg;
  u32 status;
  u32 flg2;
  SBATTLE_WORK *v19;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  long f64 v26;
  s32 hitbk_cnt;
  s32 max_damage;
  SBTLUNIT_WORK *v33;
  s32 v35;
  u16 v36;
  f32 v40;
  f32 v41;
  f32 v42;
  f32 v43;
  sdfVector4_t pos;

  v7 = Allocate(SBTLDMG_HITWORK);
  _ctor(v7, 0);
  if (!!IsSceanStop())
  {
    if (wk->mode == 2)
      return 0;
  }
  side = wk->side;
  v9 = wklock->side;
  if ((side & 0x80) != 0 && (v9 & 2) != 0)
  {
    v10 = wklock;
    wklock = wk;
  }
  else
  {
    result = 0;
    if ((side & 2) == 0)
      return result;
    v10 = wk;
    if ((v9 & 0x80) == 0)
      return result;
  }
  if ((v10->status & 0x200) == 0)
    return 0;
  Skilltbl = sBtlGetSkilltbl(skillid);
  if (wklock->damagecnt > 0 || (wk->flg & 2) != 0)
    return 0;
  v13 = Skilltbl;
  weak_attrinvtime_max = wk->weak_attrinvtime_max;
  if (weak_attrinvtime_max)
  {
    if ((wk->hstatus & 0x10) == 0 && wk->WeakReceiveFlg && !wk->weak_shild && wk->weak_attrinvtime_cnt < weak_attrinvtime_max)
    {
      return 0;
    }
  }
  flg = wk->flg;
  if ((flg & 0x800) != 0)
  {
    result = 0;
    if ((flg & 0x40000) != 0 || (v13->flg2 & 0x1000000) == 0)
      return result;
  }
  else if ((flg & 0x40000) != 0)
  {
    return 0;
  }
  if ((flg & 0x380000) != 0)
    return 0;
  result = 0;
  status = v10->actwk->status;
  if (status != 7 && status != 9)
  {
    if ((wk->side & 0x80) != 0)
    {
      flg2 = v13->flg2;
      if ((flg2 & 0x2000000) != 0)
      {
        if (sBtlChkNowJumpOver(wk, -100.0))
          return 0;
      }
      else if ((flg2 & 0x4000000) != 0)
      {
        if (sBtlChkNowJumpOver(wk, -50.0))
          return 0;
      }
    }
    v19 = wk;
    if ((v19->status4 & 0x800000) == 0)
    {
      v19 = wk;
      if (!v19->enemy_zenmetu || (wk->side & 0x81) == 0 || (v13->flg & 4) != 0)
      {
        if (!sBtlCheckPlayerDead())
        {
          if ((wk->side & 0x81) == 0 || (v13->flg & 4) != 0)
            goto LABEL_62;
          if (!wk->cmbSkl->bRun)
          {
LABEL_62:
            wklock->damagecnt = v13->muteki_time;
            x = v10->pos.x;
            y = v10->pos.y;
            z = v10->pos.z;
            w = v10->pos.w;
            *(__n128 *)&v26 = sub_1B332C0(0, x, y, z, w);
            sub_1B335A0(&v7->pos, 0, v26);
            hitbk_cnt = v13->hitbk_cnt;
            v7->flg = 0;
            max_damage = v13->max_damage;
            v7->acterID = v10->ListID;
            v7->hitbk_cnt = (f32)hitbk_cnt;
            v7->hitbk_rate = v13->hitbk_rate;
            if ((wklock->status & 0x100) != 0 && (v13->flg2 & 0x1020000) == 0)
            {
              sBtlSetMukouDamage(wklock, 0);
              sBtlSetHitback(wklock, v7, 0x1000u);
            }
            else
            {
              sBtlDecHp(wklock, max_damage, 0);
              sBtlSetNormalDamage(wklock, max_damage, 0, 0);
              sBtlSetHitback(wklock, v7, 0);
              sBtlCreateAnim_Unit(wklock, v33, max_damage, 0, 0, 0);
              v35 = v7->skillid;
              v36 = v7->type;
              pos = wklock->pos;
              v40 = wklock->pos.x;
              v41 = wklock->pos.y;
              v42 = wklock->pos.w;
              v43 = wklock->pos.z;
              pos.z = v43;
              pos.w = v42;
              pos.y = v41;
              pos.x = v40;
              sBtlCheckYukaDamageEffect(wklock, v35, v36, 0, 0, pos, v10);
            }
            return 1;
          }
        }
      }
    }
    return 0;
  }
  return result;
}

// 0x2047ad0
void sBtlDecHp(SBTLUNIT_WORK *wk, s32 damage, SKLID skillid) {
  s32 side;
  sdatParaWork_t *now;
  s32 hp;
  s32 v10;
  s32 v11;
  SBTLDVLTK_LISTWORK *dvltkList;
  SBTLUNIT_WORK *PChara;
  s32 v15;
  s32 v16;
  SBTLDVLTK_LISTWORK *v17;
  SBTLUNIT_WORK *v18;
  SBTLDVLTK_LISTWORK *v20;
  SBTLUNIT_WORK *v21;
  SBTLACTAI_WORK *actaiwk;
  SBTLACTION_WORK *actwk;
  s32 targetID;
  s32 order_stockID;
  s32 v26;
  SBTLDVLTK_LISTWORK *v30;
  sdatParaWork_t *v31;
  s32 *p_hp;
  s32 maxhp;
  sdatUnitWork_t *para;
  s32 devilid;
  sdatParaWork_t *v36;
  u32 v37;
  sdatParaWork_t *v38;
  s32 v39;
  s32 v40;
  s32 v41;
  s32 v42;
  s32 v43;

  if (wk)
  {
    side = wk->side;
    now = wk->para->now;
    hp = now->hp;
    v10 = hp - damage;
    now->hp = hp - damage;
    if ((side & 1) == 0)
      goto LABEL_38;
    v11 = now->maxhp / 2;
    if (hp <= v11)
    {
      if (v10 > 0)
        goto LABEL_38;
    }
    else if (v10 >= 1)
    {
      if ((side & 0x80) == 0 || v10 > v11)
      {
LABEL_38:
        v31 = wk->para->now;
        p_hp = &v31->hp;
        maxhp = v31->maxhp;
        LimitRange(p_hp, 0, maxhp);
        para = wk->para;
        devilid = (u16)para->devilid;
        if (devilid == 316 && (u32)(skillid - 1299) >= 4)
        {
          v36 = para->now;
          if (v36->hp <= 0)
            v36->hp = 1;
        }
        para = wk->para;
        LOWORD(devilid) = para->devilid;
        v37 = (s16)devilid - 285;
        if (v37 > 0x17)
          goto LABEL_62;
        if (((1 << v37) & 0x200010) != 0)
        {
          v38 = para->now;
          v41 = v38->hp;
          if (v41 <= 0)
          {
            v41 = 1;
            v38->hp = 1;
          }
          v42 = v38->maxhp;
          v43 = 51;
        }
        else
        {
          if (((1 << v37) & 0x400002) == 0)
          {
            if (((1 << v37) & 0x800001) == 0)
              goto LABEL_62;
            v38 = para->now;
            v39 = v38->hp;
            if (v39 <= 0)
            {
              v39 = 1;
              v38->hp = 1;
            }
            v40 = v38->maxhp / 100;
            if (v39 > v40)
              goto LABEL_62;
LABEL_61:
            v38->hp = v40;
LABEL_62:
            if ((wk->hstatus & 0x10) != 0 && para->now->hp <= 0)
              wk->actwk->cmpframecnt = 0;
            return;
          }
          v38 = para->now;
          v41 = v38->hp;
          if (v41 <= 0)
          {
            v41 = 1;
            v38->hp = 1;
          }
          v42 = v38->maxhp;
          v43 = 21;
        }
        v40 = v42 * v43 / 100;
        if (v41 > v40)
          goto LABEL_62;
        goto LABEL_61;
      }
      dvltkList = wk->dvltkList;
      PChara = sBtlGetPChara();
      v15 = 284;
      v16 = 5;
      v17 = dvltkList;
      v18 = PChara;
LABEL_37:
      sBtlCreateDvltk_Gouto(v17, v18, v15, v16);
      goto LABEL_38;
    }
    if (cfgGetConfigGAME(1, 0))
    {
      if ((wk->side & 0x80) == 0)
        goto LABEL_38;
      v20 = wk->dvltkList;
      v21 = sBtlGetPChara();
      v15 = 289;
      v17 = v20;
      v18 = v21;
      v16 = 2;
    }
    else
    {
      actaiwk = wk->actaiwk;
      wk->revival = 1;
      actwk = wk->actwk;
      targetID = actaiwk->targetID;
      actaiwk->targetID = wk->ListID;
      order_stockID = actwk->order_stockID;
      actwk->order_stockID = -1;
      v26 = wk->side;
      sBtlCheckEffectData(wk, 114, 1u, 0, v26, -1, 0);
      wk->actaiwk->targetID = targetID;
      wk->actwk->order_stockID = order_stockID;
      sBtlDeleteBuffAll(wk);
      sBtlResetBadStatus(wk, 196607);
      sBtlResetBadStatus_GB(wk->para, 196607);
      wk->para->now->hp = wk->para->now->maxhp;
      v30 = wk->dvltkList;
      v15 = 292;
      v17 = v30;
      v18 = wk;
      v16 = 1;
    }
    goto LABEL_37;
  }
}

// 0x2048850
static void BS_HITOK_Dmg(SBTLUNIT_WORK *wk, s32 id1, s32 id2, s32 hp_limit) {
  sdatUnitWork_t *para;
  s32 devilid;
  sdatParaWork_t *now;
  s32 hp;
  s64 v10;
  s32 v11;

  para = wk->para;
  devilid = para->devilid;
  if (devilid == id1 || devilid == id2)
  {
    now = para->now;
    hp = now->hp;
    if (hp <= 0)
    {
      hp = 1;
      now->hp = 1;
    }
    v10 = 1374389535 * now->maxhp * hp_limit;
    v11 = (v10 >> 37) + ((u64)v10 >> 63);
    if (hp <= v11)
      now->hp = v11;
  }
}

// 0x2046d10
static bool IsWeakAfterMuteki(SBTLUNIT_WORK *wk) {
  s32 weak_attrinvtime_max;

  weak_attrinvtime_max = wk->weak_attrinvtime_max;
  return weak_attrinvtime_max
      && (wk->hstatus & 0x10) == 0
      && wk->WeakReceiveFlg
      && !wk->weak_shild
      && wk->weak_attrinvtime_cnt < weak_attrinvtime_max;
}

// 0x20452d0
SBTLUNIT_WORK *sBtlCheckHitArea_Single(SBTLDMG_HITWORK *wk) {
  SBTLUNIT_LISTWORK *lwk;
  f32 v5;
  s64 v6;
  SBTLUNIT_WORK *v7;
  SBTLUNIT_WORK *pUnit;
  s32 devilid;
  SBATTLE_WORK *v11;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v14;
  SBTLUNIT_WORK *v15;
  SBTLUNIT_LISTWORK *v17;
  s32 targetID;
  SBTLUNIT_WORK *v19;
  s32 v20;
  struct sdfVector4_t v23;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  f32 v29;
  struct sdfVector4_t pos;

  lwk = wk->lwk;
  if (lwk->count >= 1)
  {
    v5 = 9999.0;
    v6 = 0;
    v7 = 0;
    while (1)
    {
      pUnit = lwk->pUnitL[v6]->pUnit;
      if (!pUnit)
        goto LABEL_5;
      if ((u32)(wk->skillid - 1299) <= 2)
      {
        devilid = (u16)pUnit->para->devilid;
        if (devilid == 297 || devilid == 290)
        {
          v11 = wk;
          UnitMng = v11->UnitMng;
          playerID = v11->playerID;
          v14 = sBtlSearchUnit_ID(UnitMng, playerID);
          if (!v14)
            goto LABEL_24;
          v15 = v14;
          v17 = wk->UnitMng;
          targetID = v15->actaiwk->targetID;
          v19 = sBtlSearchUnit_ID(v17, targetID);
          if (v19)
          {
            v20 = (u16)v19->para->devilid;
            if (v20 != 297 && v20 != 290)
              goto LABEL_5;
          }
        }
      }
LABEL_24:
      if (sBtlCheckHitArea(wk, pUnit))
      {
        pos = wk->pos;
        vct_A = pos;
        v23 = pUnit->pos;
        goto LABEL_33;
LABEL_34:
        goto LABEL_35;
LABEL_33:
        vct_B = v23;
        goto LABEL_34;
LABEL_35:
        vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
        goto LABEL_37;
LABEL_38:
        goto LABEL_39;
LABEL_37:
        p_x = &vf00.x;
        x = p_x[4];
        y = p_x[5];
        z = p_x[6];
        goto LABEL_38;
LABEL_39:
        v29 = sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z));
        if (v29 < v5)
        {
          v5 = v29;
          v7 = pUnit;
        }
        goto LABEL_5;
      }
LABEL_5:
      lwk = wk->lwk;
      if (++v6 >= lwk->count)
        return v7;
    }
  }
  return 0;
}

// 0x2045b10
bool sBtlCheckGround(SBTLDMG_HITWORK *hwk, s32 hitflg) {
  SBTLUNIT_WORK *v4;
  f32 x;
  f32 z;
  f32 GroundPos;
  f32 y;
  f32 v9;
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v13;
  SBTLUNIT_LISTWORK *v16;
  s32 playerID;
  f32 v18;
  f32 v19;
  sdfVector4_t *p_pos;
  s32 v23;
  struct sdfVector4_t rot;
  sdfVector4_t *p_rot;
  s32 acterside;
  s32 serialID;
  SBTLEFF_LISTWORK *effList;
  s32 v30;
  SBTLDMG_HITWORK *p_huka2hwk;
  s32 skillid;
  s32 v34;
  s32 serialID2;
  u32 flg;
  s32 v38;
  SBTLEFF_LISTWORK *v39;
  struct sdfVector4_t v41;

  v4 = Allocate(SBTLUNIT_WORK);
  _ctor(v4, 0);
  x = hwk->pos.x;
  z = hwk->pos.z;
  GroundPos = sBtlGetGroundPos(x, z);
  y = hwk->pos.y;
  v9 = GroundPos;
  if (GroundPos > y)
    return v9 > y;
  acterID = hwk->acterID;
  UnitMng = wk->UnitMng;
  v13 = sBtlSearchUnit_ID(UnitMng, acterID);
  if (v13)
    goto LABEL_16;
  v16 = wk->UnitMng;
  playerID = wk->playerID;
  v13 = sBtlSearchUnit_ID(v16, playerID);
  if (v13)
LABEL_16:
    ClassCopy(v4, v13, 0);
  v18 = hwk->pos.x;
  v19 = hwk->pos.z;
  vct_A.x = v18;
  vct_A.y = v9;
  vct_A.z = v19;
  vct_A.w = 1.0;
  p_pos = &v4->pos;
  v23 = (u8)byte_5755EF5;
  *p_pos = vct_A;
  rot = hwk->rot;
  if (v23)
    goto LABEL_23;
  goto LABEL_43;
  if (v30)
  {
LABEL_23:
    goto LABEL_24;
  }
LABEL_43:
  v41 = rot;
  rot = v41;
LABEL_24:
  vct_A = rot;
  p_rot = &v4->rot;
  *p_rot = vct_A;
  if (hwk->skillid == 73)
  {
    if (sBtlSearchEffectData(72) != -1)
    {
      acterside = hwk->acterside;
      sBtlCheckEffectData(v4, 72, 1u, 0, acterside, -1, 0);
    }
    serialID = hwk->serialID;
    effList = wk->effList;
    sBtlForceDelete_SerialID(effList, serialID);
LABEL_58:
    hwk->st = 2;
    return v9 > y;
  }
  p_huka2hwk = &wk->huka2hwk;
  p_huka2hwk = hwk;
  skillid = hwk->skillid;
  v34 = hwk->acterside;
  serialID2 = hwk->serialID2;
  sBtlCheckEffectData(v4, skillid, 2u, 0, v34, serialID2, 0);
  flg = hwk->flg;
  if ((flg & 0x200) != 0)
  {
    v38 = hwk->serialID;
    v39 = wk->effList;
    sBtlForceDelete_SerialID(v39, v38);
    flg = hwk->flg;
  }
  if ((flg & 2) != 0)
    goto LABEL_58;
  return v9 > y;
}

// 0x2045730
bool sBtlSetHit(SBTLDMG_HITWORK *wk, SBTLUNIT_WORK *wklock, s32 *hitflg) {
  s32 devilid;
  s32 skillid;
  s8 v10;
  bool v12;
  u32 flg2;
  s32 serialID;
  s32 v15;
  u32 flg;
  SBTLEFF_LISTWORK *effList;
  s32 v19;

  if (wklock)
  {
    if (!sBtlCheckSetsuma())
      goto LABEL_16;
    if (sBtlCheckSetsumaEnd())
      goto LABEL_16;
    devilid = (u16)wklock->para->devilid;
    if ((devilid == 297 || devilid == 290) && wklock->Itimoku_CloseEye)
      return 0;
  }
LABEL_16:
  skillid = wk->skillid;
  v12 = sbtlplayertblChkPlayerSordSkill(skillid);
  if (wk->f1St)
  {
    wk->f1St = 0;
    if (v12)
    {
      wklock->katana_hit_cnt = 0;
      goto LABEL_28;
    }
    goto LABEL_22;
  }
  if (v12)
    goto LABEL_28;
LABEL_22:
  if ((wklock->side & 0x80) == 0)
    goto LABEL_28;
  flg2 = sBtlGetSkilltbl(wk->skillid)->flg2;
  if ((flg2 & 0x2000000) == 0)
  {
    if ((flg2 & 0x4000000) == 0)
      goto LABEL_28;
    if (!sBtlChkNowJumpOver(wklock, -50.0))
      goto LABEL_28;
LABEL_57:
    *hitflg = 0;
    return 1;
  }
  if (sBtlChkNowJumpOver(wklock, -100.0))
    goto LABEL_57;
LABEL_28:
  if (wk->skillid == 156)
  {
    serialID = wk->serialID;
    if (sBtlPlayerRSdDash_ChkHit(wklock, serialID))
      goto LABEL_31;
    return 0;
  }
LABEL_31:
  if (wklock->katana_hit_cnt != 0 && v12)
  {
    *hitflg = 0;
  }
  else
  {
    sBtlDamageProc(wklock, wk, v10);
    *hitflg = 1;
    if (wk->skillid == 156)
    {
      v15 = wk->serialID;
      sBtlPlayerRSdDash_Hit(wklock, v15);
    }
  }
  if (v12)
  {
    if (wklock->katana_hit_cnt)
    {
      return 0;
    }
    else
    {
      wklock->katana_hit_cnt = 4;
      return 1;
    }
  }
  else
  {
    flg = wk->flg;
    if ((flg & 0x200) != 0)
    {
      effList = wk->effList;
      v19 = wk->serialID;
      sBtlForceDelete_SerialID(effList, v19);
      flg = wk->flg;
    }
    if ((flg & 2) != 0)
    {
      wk->st = 2;
      return 0;
    }
    else
    {
      return (wk->area & 1) == 0;
    }
  }
}

// 0x204c050
bool SetColor_PNL(u32 abgr) {
  SBTLDMG_HITLISTWORK *hitList;
  SBTLDMG_HITWORK *wk_local;

  hitList = wk->hitList;
  if (!hitList)
    return 0;
  wk_local = hitList->wk;
  if (!wk_local)
    return 0;
  if (!hitList->num)
    return 0;
  do
  {
    if ((wk_local->flg & 0x2000) != 0 && wk_local->st == 1)
      wk_local->abgr = wk_local->hPartsList->pose->abgr;
    wk_local = wk_local->next;
  }
  while (wk_local);
  return 1;
}

// 0x204c190
bool ResetColor_PNL(u32 abgr) {
  SBTLDMG_HITLISTWORK *hitList;
  SBTLDMG_HITWORK *wk_local;

  hitList = wk->hitList;
  if (!hitList)
    return 0;
  wk_local = hitList->wk;
  if (!wk_local)
    return 0;
  if (wk->hitList->num)
    goto LABEL_15;
  return 0;
  do
LABEL_15:
    wk_local = wk_local->next;
  while (wk_local);
  return 1;
}

// 0x204c2a0
bool sBtlDrawAttachEPL(SBTLDMG_HITLISTWORK *lwk) {
  SBTLDMG_HITWORK *wk_local;
  bool IsSceanStop;
  u32 flg;
  f32 v8;
  s32 v10;
  s32 st;
  f32 v12;
  f32 EPL_st_time;
  f32 EPL_life;
  f32 v15;
  f32 v16;
  f32 v17;
  s32 x;

  x = 0;
  if (!wk->hitList)
    return 0;
  wk_local = lwk->wk;
  if (!wk_local || !lwk->num)
    return 0;
  do
  {
    IsSceanStop = IsSceanStop();
    flg = wk_local->flg;
    if ((!IsSceanStop || (flg & 0x80) != 0) && (flg & 0x2000) != 0)
    {
      v8 = wk_local->EPL_counter + 1.0;
      v10 = v8;
      wk_local->EPL_counter = v8;
      if (v8 == INFINITY)
        v10 = 0x80000000;
      x = v10;
      LimitRange(&x, 0, 0x7FFF);
      st = wk_local->st;
      v12 = x;
      wk_local->EPL_counter = (f32)x;
      if (st == 1)
      {
        EPL_st_time = wk_local->EPL_st_time;
        if (EPL_st_time <= v12)
        {
          EPL_life = wk_local->EPL_life;
          if (EPL_life == 0.0 || (f32)(EPL_st_time + EPL_life) >= v12)
          {
            v15 = v12 - EPL_st_time;
            if (v15 >= 0.0 && v15 <= wk_local->EPL_fin_time)
            {
              v16 = wk_local->EPL_alpha + wk_local->EPL_in_alpha;
              wk_local->EPL_alpha = v16;
              if (v16 >= 80.0)
                wk_local->EPL_alpha = 80.0;
            }
            if (EPL_life != 0.0 && (f32)(EPL_life - wk_local->EPL_fout_time) <= v12)
            {
              v17 = wk_local->EPL_alpha - wk_local->EPL_out_alpha;
              wk_local->EPL_alpha = v17;
              if (v17 <= 0.0)
                wk_local->EPL_alpha = 0.0;
            }
            effPartsRotateSet(wk_local->hPartsList, wk_local->rot);
            effPartsPositionSet(wk_local->hPartsList, wk_local->pos);
            effPartsDraw(wk_local->hPartsList);
          }
        }
      }
    }
    wk_local = wk_local->next;
  }
  while (wk_local);
  return 1;
}

// 0x204c500
bool sBtlReleaseHitC_List(SBTLDMG_HITLISTWORK *lwk, u8 flg) {
  SBTLDMG_HITWORK *p_wk;
  SBTLDMG_HITWORK *wk_local;
  SBTLDMG_HITWORK *prev;
  SBTLDMG_HITWORK *v10;
  SBTLDMG_HITWORK *v11;
  SBTLDMG_HITWORK *v12;
  SBTLDMG_HITWORK *next;
  SBTLDMG_HITWORK *v14;
  SBTLDMG_HITWORK *v15;
  SBTLUNIT_LISTWORK *v16;
  dds3Basic_t *pBasic;
  void *hPartsList;
  SBTLUNIT_LISTWORK *hitlwk;

  if (!wk->hitList)
    return 0;
  p_wk = &lwk->wk;
  wk_local = lwk->wk;
  if (!wk_local || !lwk->num)
    return 0;
  do
  {
    if (flg)
    {
      wk_local->st = 2;
    }
    else
    {
      while (wk_local->st != 2)
      {
        wk_local = wk_local->next;
        if (!wk_local)
          return 1;
      }
    }
    prev = wk_local->prev;
    v10 = wk_local;
    if (!prev)
    {
      v12 = 0;
      next = wk_local->next;
      if (!next)
        goto LABEL_19;
LABEL_18:
      next->prev = v12;
      v12 = wk_local->prev;
      goto LABEL_19;
    }
    v11 = wk_local->next;
    prev->next = v11;
    v12 = wk_local->prev;
    next = wk_local->next;
    if (next)
      goto LABEL_18;
LABEL_19:
    if (!v12)
    {
      v14 = wk_local->next;
      p_wk = v14;
      v15 = p_wk;
      if (p_wk)
      {
        v15->prev = 0;
      }
    }
    wk_local = wk_local->next;
    v16 = v10->lwk;
    if (v16)
    {
      sBtlDeleteUnitList(v16, 0);
      v10->lwk = 0;
    }
    pBasic = v10->pBasic;
    if (pBasic)
    {
      dds3SceneBasicDelete(pBasic);
      v10->pBasic = 0;
      v10->hEveUnit = 0;
    }
    hPartsList = v10->hPartsList;
    if (hPartsList)
    {
      effPartsDelete(hPartsList);
      v10->hPartsList = 0;
    }
    hitlwk = v10->hitlwk;
    if (hitlwk)
    {
      sBtlDeleteUnitList(hitlwk, 0);
      v10->hitlwk = 0;
    }
    --lwk->num;
  }
  while (wk_local);
  return 1;
}

// 0x204c790
bool sBtlDeleteHitList(SBTLDMG_HITLISTWORK *wk) {
  sBtlReleaseHitC_List(wk, 1u);
  return 1;
}

// 0x204c800
SBTLUNIT_LISTWORK *sBtlCreateTargetList_Normal(SBTLUNIT_WORK *wk, SKLID skillid) {
  SBTLSKILLP_TBL *Skilltbl;
  u16 area;
  s32 side;
  char v9;
  s32 v10;
  SBTLUNIT_LISTWORK *UnitList;
  s64 v13;
  s32 v14;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 ListID;
  u8 flg[4];

  Skilltbl = sBtlGetSkilltbl(skillid);
  area = Skilltbl->area;
  flg[0] = 0;
  side = wk->side;
  v9 = sBtlGetSide(wk, area, side, flg);
  UnitList = sBtlCreateUnitList(48);
  v13 = 0;
  v14 = v9 & 0x3F;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v13 >= UnitMng->number)
      return UnitList;
    pUnit = UnitMng->pUnitL[v13]->pUnit;
    if (!pUnit)
      goto LABEL_9;
    if ((v14 & pUnit->side) == 0)
      goto LABEL_9;
    if (!sBtlCheckDamageTarget_Skilltbl(wk, pUnit, Skilltbl, v10, 0))
      goto LABEL_9;
    if ((Skilltbl->area & 0x1000) != 0)
    {
      ListID = wk->ListID;
      if (pUnit->ListID == ListID || (pUnit->status & 0x800) != 0 && ListID == pUnit->hithelperID)
        goto LABEL_9;
    }
    else if ((pUnit->vstatus & 0x10000) != 0)
    {
      goto LABEL_9;
    }
    sBtlEntryUnitList(UnitList, pUnit);
LABEL_9:
    ++v13;
  }
}

// 0x204cd10
bool sBtlCheckTargetList_csr(SBTLUNIT_WORK *wk, SKLID skillid) {
  SBTLSKILLP_TBL *Skilltbl;
  u16 area;
  s32 side;
  char v9;
  s32 v10;
  SBTLUNIT_LISTWORK *UnitList;
  s64 v13;
  s32 v14;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 ListID;
  s32 count;
  u8 flg[4];

  Skilltbl = sBtlGetSkilltbl(skillid);
  area = Skilltbl->area;
  flg[0] = 0;
  side = wk->side;
  v9 = sBtlGetSide(wk, area, side, flg);
  UnitList = sBtlCreateUnitList(48);
  v13 = 0;
  v14 = v9 & 0x3F;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v13 >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[v13]->pUnit;
    if (!pUnit)
      goto LABEL_9;
    if ((v14 & pUnit->side) == 0)
      goto LABEL_9;
    if (!sBtlCheckDamageTarget_Skilltbl(wk, pUnit, Skilltbl, v10, 1))
      goto LABEL_9;
    if ((Skilltbl->area & 0x1000) != 0)
    {
      ListID = wk->ListID;
      if (pUnit->ListID == ListID || (pUnit->status & 0x800) != 0 && ListID == pUnit->hithelperID)
        goto LABEL_9;
    }
    else if ((pUnit->vstatus & 0x10000) != 0)
    {
      goto LABEL_9;
    }
    sBtlEntryUnitList(UnitList, pUnit);
LABEL_9:
    ++v13;
  }
  count = UnitList->count;
  sBtlDeleteUnitList(UnitList, 0);
  return count != 0;
}

// 0x204cf70
bool sBtlCreateTargetList_csr(SBTLUNIT_WORK *wk, SKLID skillid) {
  SBTLSKILLP_TBL *Skilltbl;
  u16 area;
  s32 side;
  char v9;
  s32 v10;
  SBTLUNIT_LISTWORK *UnitList;
  s64 v13;
  s32 v14;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 ListID;
  s32 count;
  s32 v22;
  f32 v23;
  s64 v24;
  SBTLUNIT_WORK *v25;
  SBTLUNIT_WORK *v26;
  f32 x;
  SBTLUNIT_LISTWORK *v30;
  SBTLUNIT_LISTWORK *tgtList;
  s32 v35;
  struct sdfVector4_t pos;
  s32 v37;
  u8 flg[4];

  Skilltbl = sBtlGetSkilltbl(skillid);
  area = Skilltbl->area;
  flg[0] = 0;
  side = wk->side;
  v9 = sBtlGetSide(wk, area, side, flg);
  UnitList = sBtlCreateUnitList(48);
  v13 = 0;
  v14 = v9 & 0x3F;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v13 >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[v13]->pUnit;
    if (!pUnit)
      goto LABEL_9;
    if ((v14 & pUnit->side) == 0)
      goto LABEL_9;
    if (!sBtlCheckDamageTarget_Skilltbl(wk, pUnit, Skilltbl, v10, 1))
      goto LABEL_9;
    if ((Skilltbl->area & 0x1000) != 0)
    {
      ListID = wk->ListID;
      if (pUnit->ListID == ListID || (pUnit->status & 0x800) != 0 && ListID == pUnit->hithelperID)
        goto LABEL_9;
    }
    else if ((pUnit->vstatus & 0x10000) != 0)
    {
      goto LABEL_9;
    }
    sBtlEntryUnitList(UnitList, pUnit);
LABEL_9:
    ++v13;
  }
  count = UnitList->count;
  if (!count)
  {
    goto LABEL_70;
  }
  v35 = UnitList->count;
  if (count >= 1)
  {
    v37 = 0;
    v22 = 0;
    do
    {
      if (UnitList->number < 1)
        continue;
      v23 = -10000.0;
      v24 = 0;
      v25 = 0;
      do
      {
        v26 = UnitList->pUnitL[v24]->pUnit;
        if (!v26)
          goto LABEL_38;
        if (!CheckLiveTarget(v26))
          goto LABEL_38;
        pos = v26->pos;
        vct_A = pos;
        x = v26->pos.x;
        if (v23 > x)
          goto LABEL_38;
        v23 = x;
        v25 = v26;
        v22 = v24;
LABEL_38:
        ++v24;
      }
      while (v24 < UnitList->number);
      if (!v25)
        continue;
      if ((~v25->status & 0x8800) != 0)
      {
        tgtList = wk->tgtList;
        sBtlEntryUnitList(tgtList, v25);
        goto LABEL_34;
      }
      if (v37 == 5)
      {
        v30 = wk->tgtList;
        sBtlEntryUnitList(v30, v25);
        v37 = 6;
      }
      else
      {
        ++v37;
      }
LABEL_34:
      sBtlReleaseUnitList_ID(UnitList, v22);
    }
    while (UnitList->count >= 1);
  }
  count = v35;
LABEL_70:
  sBtlDeleteUnitList(UnitList, 0);
  return count != 0;
}

// 0x2045070
bool CreateTargetList(SBTLDMG_HITWORK *twk, SKLID skillid) {
  SBTLUNIT_LISTWORK *UnitList;
  s32 v5;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  sdatUnitWork_t *para;
  u32 BadStatus;
  s32 ListID;
  s32 actID;
  SBTLUNIT_LISTWORK *lwk;

  UnitList = sBtlCreateUnitList(48);
  twk->lwk = UnitList;
  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & twk->side & 0x3F) == 0)
      continue;
    if (!CheckDamageTarget(pUnit, twk, v5))
      continue;
    para = pUnit->para;
    BadStatus = sBtlGetBadStatus(pUnit->para);
    if ((twk->area & 0x1000) != 0)
      goto LABEL_26;
    if (BadStatus - 7 < 2 || twk->tchangeflg == 1)
    {
LABEL_26:
      ListID = pUnit->ListID;
      if (twk->acterID == ListID)
        continue;
      actID = twk->actID;
      if (actID == ListID || (pUnit->status & 0x800) != 0 && actID == pUnit->hithelperID)
        continue;
      goto LABEL_32;
    }
    if ((pUnit->vstatus & 0x10000) != 0)
      continue;
LABEL_32:
    lwk = twk->lwk;
    sBtlEntryUnitList(lwk, pUnit);
  }
  return 1;
}

// 0x204d6e0
bool sBtlCheckMutekiTime(SBTLUNIT_WORK *wk, SKLID skillid, u32 flg) {
  s32 muteki_time;
  bool result;

  muteki_time = sBtlGetSkilltbl(skillid)->muteki_time;
  result = 1;
  if (((muteki_time < 1) & (flg >> 3)) != 0)
    LOWORD(muteki_time) = 1;
  wk->damagecnt = muteki_time;
  return result;
}

// 0x2046000
bool sBtlCheckHitArea(SBTLDMG_HITWORK *wk, SBTLUNIT_WORK *wklock) {
  SBTLVISUAL_DATA *v5;
  u32 status;
  struct sdfVector4_t pos;
  f32 *p_x;
  f32 w;
  f32 z;
  f32 y;
  f32 area;
  s32 hittype;
  f32 v18;
  f32 v19;
  SBTLDMG_CYLINDERWORK *v24;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  long f64 v32;
  SBTLDMG_CYLINDERWORK *cy;
  f32 x;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 v41;
  SBTLDMG_CYLINDERWORK *v42;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 v51;
  f32 v52;
  f32 v53;
  f32 v54;
  f32 v55;
  f32 v56;
  SBTLDMG_CYLINDERWORK *v57;
  f32 v58;
  f32 v59;
  f32 v60;
  f32 v61;
  f32 v62;
  f32 v63;
  long f64 v64;
  SBTLDMG_CYLINDERWORK *v65;
  f32 v66;
  f32 v67;
  f32 v68;
  f32 v69;
  long f64 v70;
  long f64 v71;
  long f64 v72;
  long f64 v73;
  long f64 v75;
  long f64 v76;
  s32 skillid;
  f32 v78;
  f32 area_r;
  f32 r2;
  u64 v81;
  f32 v82;
  u64 v83;
  s64 v84;
  f32 v85;
  f32 v87;
  f32 height;
  f32 v90;
  f32 v91;
  f32 v92;
  f32 v94;
  f32 v95;
  f32 v96;
  f32 v97;
  f32 v98;
  f32 v99;
  f32 v100;
  f32 v101;
  f32 v102;
  f32 v103;
  f32 v104;
  u32 v105;
  f32 v106;
  f32 v107;
  f32 v108;
  f32 v109;
  f32 v110;
  u32 v111;
  f32 v112;
  u32 vector1;
  f32 vector1a;
  struct sdfVector4_t v115;
  f32 v116;
  s64 v117;
  s64 v118;
  s64 v119;
  s64 v120;
  s64 v121;
  s64 v122;
  s64 v123;
  s64 v124;
  u64 v125;
  s64 v126;
  s64 v127;
  s64 v128;
  f32 v129;
  f32 v130;
  sdfVector4_t v131;
  sdfVector4_t v132;
  sdfVector4_t v133;
  sdfVector4_t v134;
  sdfVector4_t v135;
  sdfVector4_t v136;
  sdfVector4_t v139;
  sdfVector4_t v140;
  sdfVector4_t v141;
  sdfVector4_t v142;
  sdfVector4_t v143;
  sdfVector4_t rot;
  sdfVector4_t v145;
  sdfVector4_t v146;
  sdfVector4_t v147;
  sdfVector4_t v148;

  v127 = 0;
  v128 = 0;
  v125 = 0;
  v126 = 0;
  v123 = 0;
  v124 = 0;
  v121 = 0;
  v122 = 0;
  v119 = 0;
  v120 = 0;
  v117 = 0;
  v118 = 0;
  v5 = Allocate(SBTLVISUAL_DATA);
  if (wklock->L2_muteki)
    return 0;
  status = wk->status;
  if ((status & 0x1000000) != 0)
    return 0;
  if ((status & 0x2000000) != 0)
    return 0;
  if (sBtlCheckPlayerDead())
    return 0;
  if ((wklock->status & 0x800) != 0)
  {
    pos = wklock->pos;
  }
  else
  {
    sBtlGetCylinderData(wklock, v5);
    pos = v5->center;
  }
  v115 = pos;
  vct_A = v115;
  p_x = &vf00.x;
  z = p_x[6];
  w = p_x[7];
  area = p_x[4];
  y = p_x[5];
  hittype = wk->hittype;
  if (wk->hittype)
  {
    if (hittype == 2)
    {
      v130 = area;
      if (wk->encountno != 60 || wk->area_r2 != 0.0)
        goto LABEL_82;
      cy = wk->cy;
      x = wk->pos.x;
      v140.y = wk->pos.y;
      v140.z = wk->pos.z;
      v140.w = wk->pos.w;
      v38 = wk->rot.x;
      v39 = wk->rot.y;
      v40 = wk->rot.z;
      v41 = wk->rot.w;
      v103 = wk->pos.y;
      v108 = wk->pos.x;
      v97 = wk->pos.w;
      v100 = wk->pos.z;
      v140.w = v97;
      v140.z = v100;
      v140.y = v103;
      x = v108;
      v145.y = v39;
      v145.z = v40;
      v145.w = v41;
      *(u64 *)&v133.x = 0;
      v140.x = x;
      v145.x = v38;
      if (!sBtlCheckCrossCylinder_Circle(v140, v145, cy, v133, v130))
      {
LABEL_82:
        v42 = wk->cy;
        v129 = w;
        v43 = wk->pos.x;
        v141.y = wk->pos.y;
        v44 = wk->pos.z;
        v45 = wk->pos.w;
        v46 = wk->rot.x;
        v47 = wk->rot.y;
        v48 = wk->rot.z;
        v49 = wk->rot.w;
        v104 = wk->pos.y;
        v109 = wk->pos.x;
        v141.y = v104;
        v43 = v109;
        v146.x = v46;
        v146.y = v47;
        v146.z = v48;
        v146.w = v49;
        *(u64 *)&v133.x = 0;
        v141.w = v45;
        v141.x = v43;
        v141.z = v44;
        if (!sBtlCheckCrossCylinder_Circle(v141, v146, v42, v133, v130))
          return 0;
        v51 = wk->pos.x;
        v52 = wk->pos.y;
        v53 = wk->pos.z;
        v54 = wk->pos.w;
        v55 = wk->rot.x;
        v56 = wk->rot.y;
        v57 = wk->cy;
        v58 = wk->rot.z;
        v59 = wk->rot.w;
        v110 = wk->pos.x;
        v51 = v110;
        v142.z = v53;
        v142.w = v54;
        v147.x = v55;
        v147.y = v56;
        v147.z = v58;
        v147.w = v59;
        *(u64 *)&v134.x = 0;
        v142.x = v51;
        v142.y = v52;
        if (sBtlCheckCrossCylinder_Circle(v142, v147, v57, v134, v130))
          return 0;
      }
    }
    else
    {
      if (hittype != 1)
        return 0;
      v18 = wk->pos.x;
      v19 = wk->pos.y;
      v139.z = wk->pos.z;
      v139.w = wk->pos.w;
      rot = wk->rot;
      v24 = wk->cy;
      v102 = v139.w;
      v107 = v139.z;
      v96 = rot.y;
      v99 = rot.x;
      v94 = rot.w;
      v95 = rot.z;
      rot.w = v94;
      rot.z = v95;
      rot.y = v96;
      rot.x = v99;
      v139.w = v102;
      v139.z = v107;
      v139.y = v19;
      *(u64 *)&v133.x = 0;
      v139.x = v18;
      if (!sBtlCheckCrossCylinder_Circle(v139, rot, v24, v133, area))
        return 0;
    }
    return 1;
  }
  if ((wk->flg & 8) != 0)
  {
    v26 = z;
    v27 = w;
    sBtlGetUnitHelperPos(wklock, 0);
  }
  else
  {
    v26 = z;
    v27 = w;
    v28 = v5->center.x;
    v29 = v5->center.y;
    v30 = v5->center.z;
    v31 = v5->center.w;
    *(__n128 *)&v32 = sub_1B332C0(0, v28, v29, v30, v31);
  }
  sub_1B335A0(&v127, 0, v32);
  v60 = wk->rot.x;
  v61 = wk->rot.y;
  v63 = wk->rot.z;
  v62 = wk->rot.w;
  *(__n128 *)&v64 = sub_1B332C0(0, v60, v61, v63, v62);
  sub_1B335A0(&v125, 0, v64);
  v65 = wk->cy;
  if (v65->height <= 0.0)
    v65->height = wk->area_r;
  v66 = wk->pos.x;
  v67 = wk->pos.y;
  v68 = wk->pos.z;
  v69 = wk->pos.w;
  *(__n128 *)&v70 = sub_1B332C0(0, v66, v67, v68, v69);
  *(__n128 *)&v71 = sub_1B335A0(&v123, 0, v70);
  sub_1B335A0(&v119, 0, v71);
  *(__n128 *)&v72 = sub_1B332C0(0, *(f32 *)&v127, *((f32 *)&v127 + 1), *(f32 *)&v128, *((f32 *)&v128 + 1));
  *(__n128 *)&v73 = sub_1B335A0(&v121, 0, v72);
  sub_1B335A0(&v117, 0, v73);
  if ((wklock->status & 0x800) != 0)
  {
    *(__n128 *)&v75 = sub_1B332C0(0, area, y, v26, v27);
    *(__n128 *)&v76 = sub_1B335A0(&v121, 0, v75);
    sub_1B335A0(&v117, 0, v76);
  }
  skillid = wk->skillid;
  HIDWORD(v123) = 0;
  HIDWORD(v121) = 0;
  v78 = *(f32 *)&v123;
  area_r = wk->area_r;
  LODWORD(v120) = 0;
  LODWORD(v118) = 0;
  r2 = *(f32 *)&v121;
  v81 = v124;
  v82 = 1.0;
  if (skillid == 167)
    v82 = 2.0;
  v83 = v125;
  v84 = v126;
  v85 = *(f32 *)&v122;
  v116 = v82;
  LODWORD(v129) = v124;
  v130 = *(f32 *)&v123;
  v111 = v125;
  vector1 = HIDWORD(v124);
  v105 = HIDWORD(v125);
  v82 = v116;
  v78 = v130;
  v81 = __PAIR64__(vector1, LODWORD(v129));
  v83 = __PAIR64__(v105, v111);
  *(u64 *)&v131.x = 0;
  v135.x = v78;
  v135.y = 0.0;
  *(u64 *)&v135.z = v81;
  *(u64 *)&v136.x = v83;
  *(u64 *)&v136.z = v84;
  if (!sBtlCheckCrossCircle_Rot(v135, v136, v82 * area_r, v131, r2, v85))
    return 0;
  v143.y = *((f32 *)&v119 + 1);
  v87 = *(f32 *)&v119;
  height = wk->cy->height;
  *(u64 *)&v143.z = v120;
  *(u64 *)&v148.x = v125;
  v148.w = *((f32 *)&v126 + 1);
  v90 = *(f32 *)&v126;
  v91 = *(f32 *)&v117;
  v92 = *(f32 *)&v118;
  v129 = *((f32 *)&v119 + 1);
  v130 = *(f32 *)&v119;
  v112 = *((f32 *)&v120 + 1);
  vector1a = *(f32 *)&v120;
  v101 = *((f32 *)&v125 + 1);
  v106 = *(f32 *)&v125;
  v98 = *((f32 *)&v126 + 1);
  v148.w = v98;
  v148.y = v101;
  v143.z = vector1a;
  v148.x = v106;
  v143.w = v112;
  v143.y = v129;
  v87 = v130;
  *(u64 *)&v132.x = 0;
  v143.x = v87;
  v148.z = v90;
  return sBtlCheckCrossCircle_Rot(v143, v148, v116 * height, v132, v91, v92);
}

// 0x204d730
bool sBtlCHitFunc_ATTACK(SBTLUNIT_WORK *wk, SBTLEFF_WORK *ewk, SBTLDMG_HITWORK *twk, SBTLSKILL_TBL *tbl) {
  f32 dis;
  f32 area_r;
  SBTLDMG_HITWORK *p_fields;
  s32 acterside;
  u16 area;
  s32 Side;
  u32 flg;

  dis = tbl->dis;
  area_r = tbl->area_r;
  sBtlGetPosforDistance(wk, dis);
  p_fields = &twk->fields;
  acterside = twk->acterside;
  twk->area_r = area_r;
  p_fields->pos = vct_A;
  area = tbl->area;
  Side = sBtlGetSide(wk, area, acterside, &twk->tchangeflg);
  flg = twk->flg;
  twk->side = Side;
  twk->flg = flg | 1;
  return 1;
}

// 0x203bb00
SBTLUNIT_SIDE sBtlGetSide(SBTLUNIT_WORK *wk, u16 area, SBTLUNIT_SIDE acterside, u8 *flg) {
  sdatUnitWork_t *para;
  u32 BadStatus;
  s32 battlemode;
  u32 v13;

  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  battlemode = (u16)wk->battlemode;
  if (battlemode != 3)
  {
    v13 = 0;
    goto LABEL_12;
  }
  v13 = ((u32)wk->side >> 1) & 1;
LABEL_12:
  if (battlemode == 3)
  {
    if (!v13)
      goto LABEL_26;
  }
  else
  {
    if ((wk->side & 0x80) == 0)
      v13 = 1;
    if (!v13)
    {
LABEL_26:
      if ((area & 0x8000) == 0)
        goto LABEL_27;
      goto LABEL_35;
    }
  }
  if (BadStatus - 7 > 1)
    goto LABEL_26;
  if (*flg)
    *flg = 1;
  if ((acterside & 1) == 0)
  {
    acterside = 1;
    if ((area & 0x8000) == 0)
      goto LABEL_27;
    goto LABEL_35;
  }
  if ((wk->aiwk->bstside & 1) == 0)
  {
    acterside = 2;
    goto LABEL_26;
  }
  *flg = 0;
  if ((area & 0x8000) == 0)
  {
LABEL_27:
    if ((area & 0x4000) != 0)
    {
      if ((acterside & 1) != 0)
        return 1;
      else
        return 2;
    }
    else if (area >> 14)
    {
      return 35;
    }
    else
    {
      return acterside;
    }
  }
LABEL_35:
  if ((acterside & 1) != 0)
    return 34;
  else
    return 1;
}

// 0x204d470
bool CheckDamageTarget(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *hwk, SKLID skillid) {
  bool result;
  u32 status;
  s32 motionno;
  u32 v11;

  if (wk->L2_muteki || hwk && (hwk->area & 0x1000) != 0 && hwk->acterID == wk->ListID)
    return 0;
  status = wk->status;
  if ((status & 0x1000000) != 0)
    return 0;
  status = wk->status;
  if ((status & 0x2000000) != 0)
    return 0;
  if (sBtlCheckPlayerDead())
    return 0;
  if ((~wk->side & 0x81) != 0 || wk->actwk->status != 8)
    goto LABEL_46;
  if (sBtlCheckMove(wk) || (motionno = wk->motionno, result = 0, motionno != 5) && motionno != 131)
  {
LABEL_46:
    result = 0;
    v11 = hwk->type & 0xFFF;
    if (v11 <= 0xF)
    {
      if (((1 << LOBYTE(hwk->type)) & 0xF03E) != 0)
      {
        if (sBtlCheckDamageTarget(wk))
        {
          if (sBtlCheckExist(wk) && (wk->status & 0x4001000) == 0)
            return 1;
        }
        return 0;
      }
      if (v11 == 9)
      {
        if (sBtlCheckDamageTarget(wk))
        {
          if (sBtlCheckExist(wk) && (wk->status & 0x4001000) == 0)
            return 1;
        }
        return 0;
      }
    }
  }
  return result;
}

// 0x2046d50
bool sBtlCheckPlayerDead(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v5;
  u32 status;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v5 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (v5)
  {
    status = v5->actwk->status;
    if (status > 0x28)
      LOBYTE(v5) = 0;
    else
      return (0x10400000400uLL >> status) & 1;
  }
  return (char)v5;
}

// 0x204ca30
bool sBtlCheckDamageTarget_Skilltbl(SBTLUNIT_WORK *acter, SBTLUNIT_WORK *wk, SBTLSKILLP_TBL *ptbl, SKLID skillid, s32 flg) {
  bool result;
  u32 status;
  s32 side;
  u32 v16;

  if (wk->L2_muteki || (ptbl->area & 0x1000) != 0 && acter->ListID == wk->ListID)
    return 0;
  status = wk->status;
  if ((status & 0x1000000) != 0)
    return 0;
  status = wk->status;
  if ((status & 0x2000000) != 0)
    return 0;
  if (sBtlCheckPlayerDead())
    return 0;
  side = wk->side;
  if (wk->enemy_zenmetu && (side & 0x81) != 0 && (ptbl->flg & 4) == 0)
    return 0;
  if ((~side & 0x81) == 0 && wk->actwk->status == 8)
    return 0;
  result = 0;
  v16 = ptbl->type & 0xFFF;
  if (v16 <= 0xF)
  {
    if (((1 << LOBYTE(ptbl->type)) & 0xF03E) != 0)
    {
      if (flg)
      {
        if (CheckLiveTarget(wk))
        {
          if (sBtlCheckExist(wk) && (wk->status & 0x4001000) == 0)
            return 1;
        }
      }
      else
      {
        if (sBtlCheckDamageTarget(wk))
        {
          if (sBtlCheckExist(wk) && (wk->status & 0x4001000) == 0)
            return 1;
        }
      }
      return 0;
    }
    if (v16 == 9)
    {
      if (sBtlCheckDamageTarget(wk))
      {
        if (sBtlCheckExist(wk) && (wk->status & 0x4001000) == 0)
          return 1;
      }
      return 0;
    }
  }
  return result;
}

// 0x204d8a0
bool sBtlSearchDMG_Unit(SBTLDMG_HITWORK *hwk, SBTLUNIT_WORK *wk) {
  SBTLUNIT_LISTWORK *hitlwk;
  SBTLUNIT_LISTWK *pUnitL;
  SBTLUNIT_WORK *pUnit;
  SBTLUNIT_WORK *v6;
  SBTLUNIT_WORK *v7;
  SBTLUNIT_WORK *v8;
  SBTLUNIT_WORK *v9;
  SBTLUNIT_WORK *v10;
  SBTLUNIT_WORK *v11;
  SBTLUNIT_WORK *v12;
  SBTLUNIT_WORK *v13;
  SBTLUNIT_WORK *v14;
  SBTLUNIT_WORK *v15;
  SBTLUNIT_WORK *v16;
  SBTLUNIT_WORK *v17;
  SBTLUNIT_WORK *v18;
  SBTLUNIT_WORK *v19;
  SBTLUNIT_WORK *v20;
  SBTLUNIT_WORK *v21;
  SBTLUNIT_WORK *v22;
  SBTLUNIT_WORK *v23;
  SBTLUNIT_WORK *v24;
  SBTLUNIT_WORK *v25;
  SBTLUNIT_WORK *v26;
  SBTLUNIT_WORK *v27;
  SBTLUNIT_WORK *v28;

  hitlwk = hwk->hitlwk;
  if (!hitlwk)
    return 0;
  pUnitL = hitlwk->pUnitL;
  pUnit = pUnitL[0]->pUnit;
  if (pUnit)
  {
    if (pUnit->ListID == wk->ListID)
      return 0;
  }
  v6 = pUnitL[1]->pUnit;
  if (v6)
  {
    if (v6->ListID == wk->ListID)
      return 0;
  }
  v7 = pUnitL[2]->pUnit;
  if (v7)
  {
    if (v7->ListID == wk->ListID)
      return 0;
  }
  v8 = pUnitL[3]->pUnit;
  if (v8)
  {
    if (v8->ListID == wk->ListID)
      return 0;
  }
  v9 = pUnitL[4]->pUnit;
  if (v9)
  {
    if (v9->ListID == wk->ListID)
      return 0;
  }
  v10 = pUnitL[5]->pUnit;
  if (v10)
  {
    if (v10->ListID == wk->ListID)
      return 0;
  }
  v11 = pUnitL[6]->pUnit;
  if (v11)
  {
    if (v11->ListID == wk->ListID)
      return 0;
  }
  v12 = pUnitL[7]->pUnit;
  if (v12)
  {
    if (v12->ListID == wk->ListID)
      return 0;
  }
  v13 = pUnitL[8]->pUnit;
  if (v13)
  {
    if (v13->ListID == wk->ListID)
      return 0;
  }
  v14 = pUnitL[9]->pUnit;
  if (v14)
  {
    if (v14->ListID == wk->ListID)
      return 0;
  }
  v15 = pUnitL[10]->pUnit;
  if (v15)
  {
    if (v15->ListID == wk->ListID)
      return 0;
  }
  v16 = pUnitL[11]->pUnit;
  if (v16)
  {
    if (v16->ListID == wk->ListID)
      return 0;
  }
  v17 = pUnitL[12]->pUnit;
  if (v17)
  {
    if (v17->ListID == wk->ListID)
      return 0;
  }
  v18 = pUnitL[13]->pUnit;
  if (v18)
  {
    if (v18->ListID == wk->ListID)
      return 0;
  }
  v19 = pUnitL[14]->pUnit;
  if (v19)
  {
    if (v19->ListID == wk->ListID)
      return 0;
  }
  v20 = pUnitL[15]->pUnit;
  if (v20)
  {
    if (v20->ListID == wk->ListID)
      return 0;
  }
  v21 = pUnitL[16]->pUnit;
  if (v21)
  {
    if (v21->ListID == wk->ListID)
      return 0;
  }
  v22 = pUnitL[17]->pUnit;
  if (v22)
  {
    if (v22->ListID == wk->ListID)
      return 0;
  }
  v23 = pUnitL[18]->pUnit;
  if (v23)
  {
    if (v23->ListID == wk->ListID)
      return 0;
  }
  v24 = pUnitL[19]->pUnit;
  if (v24)
  {
    if (v24->ListID == wk->ListID)
      return 0;
  }
  v25 = pUnitL[20]->pUnit;
  if (v25)
  {
    if (v25->ListID == wk->ListID)
      return 0;
  }
  v26 = pUnitL[21]->pUnit;
  if (v26)
  {
    if (v26->ListID == wk->ListID)
      return 0;
  }
  v27 = pUnitL[22]->pUnit;
  if (v27)
  {
    if (v27->ListID == wk->ListID)
      return 0;
  }
  v28 = pUnitL[23]->pUnit;
  return !v28 || v28->ListID != wk->ListID;
}

// 0x204db60
bool sBtlSetEntryUnitList_Hit(SBTLDMG_HITWORK *hwk, SBTLUNIT_WORK *wklock) {
  SBTLDMG_HITLISTWORK *hitList;
  SBTLDMG_HITWORK *wk_local;
  SBTLUNIT_LISTWORK *hitlwk;

  hitList = wk->hitList;
  if (!hitList)
    return 0;
  hitList = wk->hitList;
  wk_local = hitList->wk;
  if (!wk_local)
    return 0;
  if (!hitList->num)
    return 0;
  do
  {
    if (wk_local->st == 1 && hwk->serialID != wk_local->serialID && hwk->serialID2 == wk_local->serialID2)
    {
      hitlwk = wk_local->hitlwk;
      sBtlEntryUnitList(hitlwk, wklock);
    }
    wk_local = wk_local->next;
  }
  while (wk_local);
  return 1;
}

// 0x204dcd0
SBTLUNIT_WORK *sBtlCheckALLSkill(SBTLUNIT_WORK *wk, SKLID sklid) {
  s32 TargetList_ALLHIT;
  s32 hithelperID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *result;
  s32 v11;
  SBTLUNIT_LISTWORK *v12;

  if (!(sklid != 64 || (~wk->status & 0x8800) != 0))
  {
    TargetList_ALLHIT = sBtlCreateTargetList_ALLHIT();
    if (TargetList_ALLHIT != -1)
    {
      hithelperID = wk->hithelperID;
      UnitMng = wk->UnitMng;
      result = sBtlSearchUnit_ID(UnitMng, hithelperID);
      result->hithelperreqID = TargetList_ALLHIT;
      return result;
    }
  }
  v11 = wk->hithelperID;
  v12 = wk->UnitMng;
  result = sBtlSearchUnit_ID(v12, v11);
  result->hithelperreqID = wk->ListID;
  return result;
}

// 0x204de20
bool sBtlCheckHitHelp(SBTLDMG_HITWORK *hwk, SBTLUNIT_WORK *wklock) {
  u32 status;
  SBTLUNIT_LISTWORK *v8;
  s32 v9;
  SBTLUNIT_WORK *v10;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 acterID;
  SBTLUNIT_WORK *v14;

  status = wklock->status;
  if ((status & 0x800) == 0)
  {
    if ((status & 0x1000) == 0)
      return hwk->acterID == wklock->ListID;
    goto LABEL_9;
  }
  if ((status & 0x8000) != 0)
  {
    UnitMng = wk->UnitMng;
    acterID = hwk->acterID;
    v14 = sBtlSearchUnit_ID(UnitMng, acterID);
    if (!v14)
      return hwk->acterID == wklock->hithelperID;
    if ((~v14->status & 0x8800) == 0)
      return 1;
    return hwk->acterID == wklock->hithelperID;
  }
  if ((status & 0x1000) == 0)
    return hwk->acterID == wklock->ListID;
LABEL_9:
  v8 = wk->UnitMng;
  v9 = hwk->acterID;
  v10 = sBtlSearchUnit_ID(v8, v9);
  if (!v10)
    return hwk->acterID == wklock->ListID;
  if ((~v10->status & 0x8800) == 0)
    return 1;
  return hwk->acterID == wklock->ListID;
}

// 0x204e010
bool sBtlSetDeadDamageEx(SBTLUNIT_WORK *wklock, SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *hwk, s32 damage, u32 attr, bool *a_pbDamage, f32 *a_pRate) {
  s32 side;
  s32 devilid;
  SBTLUNIT_WORK *v18;
  bool v21;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v23;
  s32 skillid;
  SBTLEXP_LISTWORK *expList;
  s32 acterID;
  SBTLUNIT_WORK *v28;
  SBTLUNIT_WORK *v29;
  s32 v31;
  SBTLEXP_LISTWORK *v32;
  s32 v33;
  s32 v35;
  SBTLEXP_LISTWORK *v36;
  s32 v37;
  f32 m_rate;
  bool v39;
  bool v41;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  s32 v47;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v49;
  s64 v50;
  SBTLUNIT_WORK *v51;
  s64 v53;
  sdfVector4_t v54;

  if (!wklock)
    return 0;
  if (!CheckLiveTarget(wklock))
    return 0;
  if (!sBtlIsDeadBgn_2(wklock))
    return 0;
  sBtlResetBtlMagicStatus(wklock);
  side = wklock->side;
  if ((side & 1) != 0)
  {
    if ((side & 0x80) != 0)
    {
      v39 = sBtlSetDeadDamageProc(wk, wklock, hwk, damage, attr);
      m_rate = wklock->m_rate;
      v21 = v39;
    }
    else
    {
      v21 = sBtlSetDeadDamageProc(wk, wklock, hwk, damage, attr);
      Nakama = sBtlGetNakama(0);
      if (Nakama)
      {
        v23 = Nakama;
        if (Nakama != wklock)
        {
          skillid = hwk->skillid;
          expList = wk->expList;
          acterID = hwk->acterID;
          sBtlSetRirituNakamaHD(expList, v23, skillid, acterID, 0x11u);
        }
      }
      v28 = sBtlGetNakama(1);
      if (v28)
      {
        v29 = v28;
        if (v28 != wklock)
        {
          v31 = hwk->skillid;
          v32 = wk->expList;
          v33 = hwk->acterID;
          sBtlSetRirituNakamaHD(v32, v29, v31, v33, 0x11u);
        }
      }
      v35 = hwk->skillid;
      v36 = wk->expList;
      v37 = hwk->acterID;
      sBtlSetRirituEnemyHD(v36, wklock, v35, v37, 8);
      m_rate = 0.0;
    }
    goto LABEL_72;
  }
  devilid = (u16)wklock->para->devilid;
  if (devilid == 260 || devilid == 258)
  {
    v18 = wklock;
  }
  else
  {
    if (sBtlCheckLastEnemyDead(wk))
    {
      wk->hstatus |= 0x8000000u;
      wk->enemy_zenmetu = 1;
    }
    v18 = wk;
  }
  v41 = sBtlSetDeadDamageProc(v18, wklock, hwk, damage, attr);
  m_rate = wklock->m_rate;
  v21 = v41;
  x = wk->pos.x;
  y = wk->pos.y;
  z = wk->pos.z;
  w = wk->pos.w;
  v54.x = x;
  v54.y = y;
  v54.z = z;
  v54.w = w;
  sBtlPlay3DSE_BaseVol(0x10021u, 159, v54);
  v47 = hwk->acterID;
  UnitMng = wk->UnitMng;
  v49 = sBtlSearchUnit_ID(UnitMng, v47);
  v51 = v49;
  if ((wklock->status & 0x100000) != 0)
  {
    if ((v49->side & 0x80) != 0)
      goto LABEL_62;
LABEL_68:
LABEL_69:
    if (wk->encountno == 514)
      goto LABEL_70;
    goto LABEL_72;
  }
  sBtlSpiritAddDirect(v51, 9);
  if ((v51->side & 0x80) == 0)
    goto LABEL_68;
LABEL_62:
  sBtlDeadDevilTalkSet();
  goto LABEL_69;
  if (wk->encountno == 514)
  {
LABEL_70:
    if (wklock->para->devilid == 476)
    {
      sub_1A21FE0(681, 0, v50);
      sub_1A21FE0(689, 0, v53);
    }
  }
LABEL_72:
  if (*a_pbDamage)
    *a_pbDamage = v21;
  if (*a_pRate != 0.0)
    *a_pRate = m_rate;
  return 1;
}

// 0x204ed50
void sBtlSetDeleteKaja(SBTLUNIT_WORK *wklock, SKLID skillid) {
  SBTLSKL_KAJA_WORK **wkKaja;
  SBTLSKL_KAJA_WORK *v6;
  SBTLSKL_KAJA_WORK *v7;
  s32 v8;
  SBTLSKL_KAJA_WORK *v9;
  SBTLSKL_KAJA_WORK *v10;
  SBTLSKL_KAJA_WORK *v11;
  SBTLSKL_KAJA_WORK *v12;
  SBTLSKL_KAJA_WORK *v13;
  SBTLSKL_KAJA_WORK *v14;
  SBTLSKL_KAJA_WORK *v15;
  tagSBTLSKL_KARN_WORK *v16;
  tagSBTLSKL_AURA_WORK *wkAura;
  u32 aurakind;
  void *wkBarrier;
  tagSBTLSKL_AURA_WORK *v20;
  tagSBTLSKL_AURA_WORK *v21;
  tagSBTLSKL_AURA_WORK *v22;
  s32 v23;
  s32 size;
  s32 v25;
  SBTLSM_LISTWORK *sysmsgList;
  s32 v29;
  s32 v30;

  wkKaja = wklock->wkKaja;
  v6 = wkKaja[0];
  v7 = v6[0];
  if (v7->m_cnt)
  {
    v8 = 1;
    v7->fields = 0;
    v9 = v6[1];
    if (!v9->m_cnt)
      goto LABEL_6;
    goto LABEL_5;
  }
  v8 = 0;
  v9 = v6[1];
  if (v9->m_cnt)
  {
LABEL_5:
    ++v8;
    v9->fields = 0;
  }
LABEL_6:
  v10 = wkKaja[1];
  v11 = v10[0];
  if (v11->m_cnt)
  {
    ++v8;
    v11->fields = 0;
  }
  v12 = v10[1];
  if (v12->m_cnt)
  {
    ++v8;
    v12->fields = 0;
  }
  v13 = wkKaja[2];
  v14 = v13[0];
  if (v14->m_cnt)
  {
    ++v8;
    v14->fields = 0;
  }
  v15 = v13[1];
  if (v15->m_cnt)
  {
    ++v8;
    v15->fields = 0;
  }
  v16 = wklock->wkKarn[0];
  if (v16->m_cnt)
  {
    ++v8;
    v16->fields = 0;
  }
  wkAura = wklock->wkAura;
  aurakind = wklock->aurakind;
  wkBarrier = wklock->wkBarrier;
  v20 = wkAura[0];
  v21 = wkAura[1];
  v22 = wkAura[2];
  *(u64 *)&v20->auraskl = 0;
  v20->aurapara = 0;
  *(u64 *)&v21->auraskl = 0;
  v21->aurapara = 0;
  *(u64 *)&v22->auraskl = 0;
  v22->aurapara = 0;
  wklock->aurakind = aurakind & 0xF8FFFFFF;
  if (wkBarrier->_size < 1)
  {
    v30 = wkBarrier->_version + 1;
    wkBarrier->_size = 0;
    wkBarrier->_version = v30;
    if (v8 < 1)
      return;
    goto LABEL_24;
  }
  v23 = 0;
  do
  {
    if (HIDWORD(_get_Item(wkBarrier, v23)[1].klass))
    {
      ++v8;
      HIDWORD(_get_Item(wklock->wkBarrier, v23)[1].klass) = 0;
    }
    wkBarrier = wklock->wkBarrier;
    ++v23;
    size = wkBarrier->_size;
  }
  while (v23 < size);
  v25 = wkBarrier->_version + 1;
  wkBarrier->_size = 0;
  wkBarrier->_version = v25;
  if (size >= 1)
    Clear(wkBarrier->_items, 0, size, 0);
  if (v8 >= 1)
  {
LABEL_24:
    if ((wklock->side & 1) != 0)
    {
      sysmsgList = wk->sysmsgList;
      v29 = 148;
    }
    else
    {
      sysmsgList = wk->sysmsgList;
      v29 = 149;
    }
    sBtlCreateSM(sysmsgList, wklock, v29, skillid, 0, 120);
  }
}

// 0x2048600
void sBtlDeleteBuffAll(SBTLUNIT_WORK *wklock) {
  SBTLSKL_KAJA_WORK **wkKaja;
  SBTLSKL_KAJA_WORK *v4;
  SBTLSKL_KAJA_WORK *v5;
  SBTLSKL_KAJA_WORK *v6;
  SBTLSKL_KAJA_WORK *v7;
  SBTLSKL_KAJA_WORK *v8;
  SBTLSKL_KAJA_WORK *v9;
  SBTLSKL_KAJA_WORK *v10;
  SBTLSKL_KAJA_WORK *v11;
  SBTLSKL_KAJA_WORK *v12;
  tagSBTLSKL_KARN_WORK *v13;
  tagSBTLSKL_AURA_WORK *wkAura;
  u32 aurakind;
  void *wkBarrier;
  tagSBTLSKL_AURA_WORK *v17;
  tagSBTLSKL_AURA_WORK *v18;
  tagSBTLSKL_AURA_WORK *v19;
  s32 v20;
  s32 size;
  s32 v22;
  s32 v23;

  wkKaja = wklock->wkKaja;
  v4 = wkKaja[0];
  v5 = v4[0];
  if (v5->m_cnt)
    v5->fields = 0;
  v6 = v4[1];
  if (v6->m_cnt)
    v6->fields = 0;
  v7 = wkKaja[1];
  v8 = v7[0];
  if (v8->m_cnt)
    v8->fields = 0;
  v9 = v7[1];
  if (v9->m_cnt)
    v9->fields = 0;
  v10 = wkKaja[2];
  v11 = v10[0];
  if (v11->m_cnt)
    v11->fields = 0;
  v12 = v10[1];
  if (v12->m_cnt)
    v12->fields = 0;
  v13 = wklock->wkKarn[0];
  if (v13->m_cnt)
    v13->fields = 0;
  wkAura = wklock->wkAura;
  aurakind = wklock->aurakind;
  wkBarrier = wklock->wkBarrier;
  v17 = wkAura[0];
  v18 = wkAura[1];
  v19 = wkAura[2];
  *(u64 *)&v17->auraskl = 0;
  v17->aurapara = 0;
  *(u64 *)&v18->auraskl = 0;
  v18->aurapara = 0;
  *(u64 *)&v19->auraskl = 0;
  v19->aurapara = 0;
  *(u64 *)&wklock->rejyenecnt = 0;
  wklock->rejyenecounter = 0;
  wklock->rejyenepara = 0;
  wklock->aurakind = aurakind & 0xF8FFFFFF;
  if (wkBarrier->_size < 1)
  {
    v23 = wkBarrier->_version + 1;
    wkBarrier->_size = 0;
    wkBarrier->_version = v23;
    *(u64 *)&wklock->bulletcnt = 0;
  }
  else
  {
    v20 = 0;
    do
    {
      if (HIDWORD(_get_Item(wkBarrier, v20)[1].klass))
        HIDWORD(_get_Item(wklock->wkBarrier, v20)[1].klass) = 0;
      wkBarrier = wklock->wkBarrier;
      ++v20;
      size = wkBarrier->_size;
    }
    while (v20 < size);
    v22 = wkBarrier->_version + 1;
    wkBarrier->_size = 0;
    wkBarrier->_version = v22;
    if (size >= 1)
      Clear(wkBarrier->_items, 0, size, 0);
    *(u64 *)&wklock->bulletcnt = 0;
  }
}

// 0x20487d0
void sBtlDeleteDeBuffAll(SBTLUNIT_WORK *wklock) {
  sBtlResetBadStatus(wklock, 196607);
  sBtlResetBadStatus_GB(wklock->para, 196607);
}

// 0x204f010
void sBtlSetKudaDamage(s32 Damage) {
  s32 v3;
  sdatUnitWork_t *StockUnitData;
  sdatUnitWork_t *v5;
  u32 BadStatus;
  sdatParaWork_t *now;
  s32 v8;
  bool v9;
  s32 i;
  sdatUnitWork_t *v11;
  sdatUnitWork_t *v12;
  u32 v13;
  sdatParaWork_t *v14;

  if ((Damage & 0x80000000) == 0)
  {
    v3 = 0;
    while (1)
    {
      StockUnitData = sBtlGetStockUnitData(v3);
      if (StockUnitData)
      {
        v5 = StockUnitData;
        BadStatus = sBtlGetBadStatus(StockUnitData);
        if (BadStatus != 17)
        {
          if (BadStatus != 20)
          {
            now = v5->now;
            v8 = now->hp - Damage;
            v9 = now->hp == Damage;
            now->hp = v8;
            if (v8 < 0 || v9)
            {
              now->hp = 0;
              *(u64 *)&v5->badstatus = 0x20000;
              v5->badst_cnt3 = 0;
            }
          }
        }
      }
      if (++v3 == 32)
        return;
    }
  }
  for (i = 0; i != 32; ++i)
  {
    v11 = sBtlGetStockUnitData(i);
    if (!v11)
      continue;
    v12 = v11;
    v13 = sBtlGetBadStatus(v11);
    if (v13 == 17)
      continue;
    if (v13 != 20)
    {
      v14 = v12->now;
      v12->badst_cnt3 = 0;
      v14->hp = 0;
      *(u64 *)&v12->badstatus = 0x20000;
    }
  }
}

// 0x20488b0
bool sBtlDamageProc(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *hwk, s8 guardflg) {
  tagSBTLSKL_BARRIER_WORK *v6;
  SBTLSKILLP_TBL *Skilltbl;
  SBATTLE_WORK *v9;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 acterID;
  SBTLUNIT_WORK *v13;
  s32 flg;
  SBTLUNIT_WORK *v16;
  s32 v17;
  s32 v18;
  s32 v19;
  s32 v20;
  bool v21;
  SBATTLE_WORK *v23;
  s32 ListID;
  s64 v26;
  s32 v27;
  SBTLUNIT_WORK *v33;
  s32 v34;
  s32 v35;
  u32 flg2;
  s32 weak_attrinvtime_max;
  u32 attrtime;
  sdatUnitWork_t *v41;
  s32 j;
  SBTLUNIT_LISTWORK *v44;
  SBTLUNIT_WORK *v46;
  SBTLUNIT_WORK *v47;
  u32 attr;
  u32 badst;
  void *wkBarrier;
  void *v51;
  u32 v52;
  void *v53;
  SBTLAI_WORK *aiwk;
  u32 skillflg;
  s32 serialID;
  s32 actioncnt;
  SBTLUNIT_WORK *v60;
  s32 damage_actionf_cnt;
  SBTLUNIT_LISTWORK *v62;
  SBTLUNIT_LISTWORK *v63;
  SBTLUNIT_WORK *v64;
  s32 v66;
  sdatUnitWork_t *v67;
  tagSBTLSKL_KARN_WORK *wkKarn;
  tagSBTLSKL_KARN_WORK *v69;
  s32 v70;
  SBTLAI_WORK *v71;
  sdatUnitWork_t *para;
  s32 v75;
  SBTLUNIT_LISTWORK *v76;
  SBTLUNIT_WORK *v77;
  SBTLUNIT_WORK *v78;
  u32 i;
  SBTLUNIT_WORK *v80;
  u32 badstatus;
  bool v82;
  s32 v83;
  s64 v84;
  SBTLUNIT_LISTWORK *hitlwk;
  s32 v87;
  s32 v89;
  SBTLUNIT_LISTWORK *v90;
  SBTLUNIT_WORK *v91;
  s32 playerID;
  SBATTLE_WORK *v94;
  s32 v95;
  s32 devilid;
  s32 v99;
  u32 v100;
  u32 v101;
  u32 v105;
  s32 v106;
  u32 v107;
  u32 v108;
  s32 v110;
  char v111;
  u32 v112;
  s32 v113;
  s32 v114;
  SBTLUNIT_WORK *v115;
  sdatUnitWork_t *v116;
  SBTLUNIT_WORK *v118;
  u32 v119;
  SBATTLE_WORK *v120;
  SBTLSKILLP_TBL *v122;
  u32 v123;
  s32 v124;
  sdatUnitWork_t *v125;
  s32 v126;
  s32 v127;
  sdatUnitWork_t *v128;
  s32 v129;
  sdatUnitWork_t *v130;
  s32 v131;
  s32 v132;
  s32 damage_workID;
  s32 v134;
  s32 v135;
  s32 actionf;
  SBTLUNIT_LISTWORK *v137;
  s32 v139;
  s32 v140;
  s32 v142;
  SBTLUNIT_WORK *v143;
  SBTLACTION_WORK *actwk;
  u32 status;
  s32 v147;
  u32 v149;
  s32 motionID;
  _BOOL4 v153;
  s32 v154;
  u32 v156;
  s32 v157;
  u32 v158;
  s32 v159;
  u32 v162;
  s32 v163;
  u32 v164;
  char v165;
  s32 v167;
  s32 v169;
  sdatUnitWork_t *v170;
  u32 v171;
  u32 v172;
  sdatUnitWork_t *v173;
  s32 HaveMemSkl;
  sdatUnitWork_t *v175;
  s32 v176;
  u32 v177;
  SBTLACTION_WORK *v178;
  u32 v179;
  s32 use_skillid;
  sdatUnitWork_t *v181;
  u16 s_type;
  SBATTLE_WORK *v184;
  sdatUnitWork_t *v185;
  SBTLUNIT_WORK *v186;
  s32 v189;
  sdatUnitWork_t *v190;
  s32 v191;
  u32 v192;
  s32 v193;
  s32 v194;
  u32 v196;
  s32 v197;
  s32 aListID;
  s32 v201;
  s32 v202;
  SBTLUNIT_WORK *PChara;
  u32 v204;
  s32 Damage;
  s32 v207;
  s32 side;
  s32 v210;
  SBTLEXP_LISTWORK *v211;
  s32 v212;
  s32 v214;
  SBTLEXP_LISTWORK *expList;
  s32 v216;
  s32 v217;
  SBTLUNIT_LISTWORK *v218;
  SBTLUNIT_WORK *v219;
  s32 v221;
  SBTLEXP_LISTWORK *v222;
  s32 v223;
  s32 v224;
  SBTLUNIT_LISTWORK *v225;
  SBTLUNIT_WORK *v226;
  s32 v227;
  bool v228;
  bool v229;
  SBATTLE_WORK *v231;
  f32 v232;
  f32 v233;
  f32 v234;
  f32 v235;
  SBTLDVLTK_LISTWORK *v237;
  s32 v238;
  SBTLUNIT_WORK *v240;
  s32 v241;
  s32 v242;
  s32 v244;
  SBTLEXP_LISTWORK *v245;
  s32 v246;
  char v247;
  s32 maxhp;
  s32 v251;
  s32 v254;
  SBTLEXP_LISTWORK *v255;
  s32 v256;
  s32 v258;
  s32 v259;
  s32 v260;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  SBTLAI_WORK *v268;
  SBTLEFF_LISTWORK *effList;
  SBTLDMG_HITLISTWORK *hitList;
  bool v273;
  s32 v274;
  s32 v275;
  u32 exsts;
  s32 v277;
  s32 v278;
  u32 v281;
  u32 v282;
  bool v283;
  u32 v284;
  u32 v285;
  u32 v286;
  s32 v287;
  s32 v288;
  s32 v290;
  SBATTLE_WORK *v292;
  SBTLUNIT_LISTWORK *v293;
  s32 v294;
  s32 v296;
  sdatUnitWork_t *v297;
  s32 hp;
  s32 v299;
  s32 v301;
  s32 v302;
  s32 v303;
  sdatUnitWork_t *v304;
  s32 level;
  s16 v306;
  s32 v307;
  s32 v308;
  s32 v309;
  s32 v310;
  u32 v311;
  SBTLUNIT_WORK *UnitFromDevilID;
  s32 v313;
  s32 v314;
  s32 v315;
  char v316;
  u32 v317;
  SBTLACTAI_WORK *v319;
  SBTLACTION_WORK *v320;
  s32 targetID;
  s32 order_stockID;
  s32 v323;
  sdatUnitWork_t *v326;
  s32 v329;
  u32 v330;
  u32 v331;
  s32 v333;
  s32 v337;
  void *Instance;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v340;
  s32 v342;
  SBTLEXP_LISTWORK *v343;
  s32 v344;
  SBTLUNIT_WORK *v345;
  SBTLUNIT_WORK *v346;
  s32 v348;
  SBTLEXP_LISTWORK *v349;
  s32 v350;
  s32 v351;
  s32 muteki_time;
  SBTLDVLTK_LISTWORK *dvltkList;
  s32 v354;
  SBTLACTAI_WORK *actaiwk;
  s32 v358;
  s32 v360;
  f32 v361;
  s32 v363;
  u32 v366;
  SBTLUNIT_WORK *v368;
  u16 Percentage;
  s32 skillid[2];
  s32 skillida;
  s32 skillidb;
  SBTLUNIT_WORK *skillidc;
  s32 Frame;
  s32 a_pHanshaType;
  bool a_pbDamage[4];
  f32 a_pRate;
  sdfVector4_t v384;
  sdfVector4_t v385;

  Frame = 0;
  a_pRate = 0.0;
  a_pbDamage[0] = 0;
  v6 = Allocate(tagSBTLSKL_BARRIER_WORK);
  Skilltbl = sBtlGetSkilltbl(hwk->skillid);
  a_pHanshaType = 0;
  v9 = wk;
  if ((v9->scrFlag & 0x100000) != 0)
    return 1;
  UnitMng = v9->UnitMng;
  acterID = hwk->acterID;
  v13 = sBtlSearchUnit_ID(UnitMng, acterID);
  if (!v13)
    return 1;
  flg = wk->flg;
  v16 = v13;
  if ((flg & 0x800) == 0 || (Skilltbl->flg2 & 0x1000000) != 0)
  {
    v18 = wk->flg & 0x800;
    if ((v13->side & 2) == 0)
    {
LABEL_17:
      v17 = 0;
      goto LABEL_18;
    }
    v17 = 0;
    if ((wk->side & 0x80) != 0 && Skilltbl)
    {
      if ((Skilltbl->flg2 & 0x8000000) == 0)
        goto LABEL_17;
      v20 = hwk->skillid;
      v21 = sBtlChkSetsuma_Just(&Frame, v20);
      flg = wk->flg;
      v17 = v21;
      v18 = flg & 0x800;
    }
LABEL_18:
    if (!v18)
      goto LABEL_20;
    goto LABEL_19;
  }
  v17 = 0;
LABEL_19:
  v18 = (Skilltbl->flg2 & 0x1000000) == 0;
LABEL_20:
  if (v18 | v17)
  {
    v19 = hwk->skillid;
    if (v19 <= 467)
    {
      if (v19 <= 229)
      {
        if ((u32)(v19 - 72) < 2 || (u32)(v19 - 228) < 2)
          goto LABEL_48;
      }
      else if ((u32)(v19 - 462) <= 5 && ((1 << (v19 + 50)) & 0x2B) != 0 || v19 == 235)
      {
        goto LABEL_48;
      }
    }
    else if ((u32)v19 <= 0x605)
    {
      if (v19 == 474 || v19 == 1541)
        goto LABEL_61;
    }
    else if ((u32)(v19 - 1548) <= 0xC && ((1 << (v19 - 12)) & 0x1843) != 0)
    {
      goto LABEL_48;
    }
    if ((v16->side & 2) != 0)
    {
      v23 = wk;
      if (!v23->KaihiSetsuma && wk->damage_workID != hwk->serialID2)
      {
        wk->flg |= 0x2000u;
        v23 = wk;
        v23->KaihiSetsuma_SkillId = hwk->skillid;
        return 1;
      }
    }
  }
  v19 = hwk->skillid;
LABEL_48:
  if (v19 == 312)
  {
    if (v16->ListID == hwk->acterID)
    {
      v26 = 68719476750LL * wk->magMax;
      v27 = (v26 >> 37) + ((u64)v26 >> 63);
      sBtlSetAddMag(v16, v27);
    }
    return 1;
  }
  if (v19 == 313)
  {
    ListID = v16->ListID;
    if (ListID == hwk->acterID)
    {
      sBtlSetBadStatus_No(v16, 313, 5u, 0, ListID);
    }
    return 1;
  }
  flg = wk->flg;
LABEL_61:
  if ((flg & 2) != 0)
    goto LABEL_68;
  if ((flg & 0x800) == 0)
  {
    if ((flg & 0x40000) != 0)
      goto LABEL_68;
LABEL_67:
    if ((flg & 0x380000) == 0)
    {
      weak_attrinvtime_max = wk->weak_attrinvtime_max;
      if (!weak_attrinvtime_max || (wk->hstatus & 0x10) != 0 || !wk->WeakReceiveFlg || wk->weak_shild || wk->weak_attrinvtime_cnt >= weak_attrinvtime_max)
      {
        goto LABEL_69;
      }
    }
    goto LABEL_68;
  }
  if ((flg & 0x40000) == 0 && (Skilltbl->flg2 & 0x1000000) != 0)
    goto LABEL_67;
LABEL_68:
  if ((Skilltbl->flg & 1) != 0)
    return 1;
LABEL_69:
  if ((wk->side & 0x80) != 0)
  {
    flg2 = Skilltbl->flg2;
    if ((flg2 & 0x2000000) != 0)
    {
      if (sBtlChkNowJumpOver(wk, -100.0))
        return 0;
    }
    else if ((flg2 & 0x4000000) != 0)
    {
      if (sBtlChkNowJumpOver(wk, -50.0))
        return 0;
    }
  }
  if (wk->enemy_zenmetu && (wk->side & 0x81) != 0 && (Skilltbl->flg & 4) == 0)
    return 0;
  if (sBtlPlayerCheckRSpirit_Start())
    return 0;
  if (sBtlCheckPlayerDead())
    return 0;
  if ((wk->side & 0x81) != 0 && (Skilltbl->flg & 4) == 0)
  {
    if (wk->cmbSkl->bRun)
      return 0;
  }
  v33 = wk;
  a_pRate = 0.0;
  a_pbDamage[0] = 1;
  if ((wk->status & 0x800) != 0)
  {
    v34 = hwk->skillid;
    v33 = sBtlCheckALLSkill(wk, v34);
  }
  v35 = hwk->skillid;
  if (v35 <= 1010)
  {
    if (v35 > 661)
    {
      if (v35 != 920 && v35 != 1006 && v35 != 1010)
        goto LABEL_142;
      goto LABEL_126;
    }
    if (v35 == 134)
    {
LABEL_132:
      sBtlSetDeleteKaja(v33, v35);
      return 1;
    }
    if (v35 == 149)
    {
      para = v33->para;
      skillida = sBtlChkHaveMemSkl(para, 32);
      if (skillida && 2 * v33->para->now->luck > GetPercentage())
      {
        v75 = hwk->acterID;
        v76 = wk->UnitMng;
        v77 = sBtlSearchUnit_ID(v76, v75);
        if (v77)
        {
          v78 = v77;
          if ((v77->para->aisyo->para[7] & 0x1000) == 0)
          {
            for (i = 0; i != 21; ++i)
            {
              if (sBtlGetSkilltbl(skillida)->badst == (s64)(1 << i))
              {
                v80 = v33;
                badstatus = v78->para->badstatus;
                v82 = sBtlCheckBadStatus_Number(badstatus, i, v78);
                v33 = v80;
                if (v82 && (v78->para->badstatus & (1 << i)) == 0)
                {
                  v83 = hwk->acterID;
                  sBtlSetBadStatus_No(v78, 0, i, 0, v83);
                  v33 = v80;
                }
              }
            }
          }
        }
      }
      goto LABEL_167;
    }
    if (v35 != 661)
    {
LABEL_142:
      if (v16 != wk || (Skilltbl->flg & 0x200) == 0)
        goto LABEL_167;
      *(u64 *)skillid = v33;
      attrtime = Skilltbl->attrtime;
      v41 = wk->para;
      if (sBtlChkHaveMemSkl(v41, 43))
        attrtime += wk->para->autost_cnt;
      for (j = 0; ; ++j)
      {
        v44 = wk->UnitMng;
        if (j >= v44->number)
        {
          v52 = hwk->skillid;
          *(u64 *)&v6->m_barrierstatus = 0;
          v53 = Method_System_Collections_Generic_List_tagSBTLSKL_BARRIER_WORK__Add__;
          v6->m_EndSM = 1;
          *(u64 *)&v6->m_skillid = v52;
          sub_34C90(wk->wkBarrier, v6, v53);
          aiwk = wk->aiwk;
          wk->drawgaugetype = 1;
          aiwk->cmndFrm = 0;
          aiwk->cmndFrmMax = attrtime;
          v33 = *(SBTLUNIT_WORK *)skillid;
          goto LABEL_167;
        }
        v46 = sBtlSearchUnit_ID(v44, j);
        if (!v46)
          continue;
        v47 = v46;
        if (CheckLiveTarget(v47) && (v47->side & 1) != 0)
        {
          attr = Skilltbl->attr;
          v6->m_skillid = 0;
          v6->m_cnt = attrtime;
          badst = Skilltbl->badst;
          v6->m_barrierstatus = attr;
          v6->m_barrieradv = badst;
          wkBarrier = v47->wkBarrier;
          v51 = Method_System_Collections_Generic_List_tagSBTLSKL_BARRIER_WORK__Add__;
          v6->m_EndSM = 1;
          sub_34C90(wkBarrier, v6, v51);
          CalcAisyo(v47);
        }
      }
    }
    goto LABEL_192;
  }
  if ((u32)v35 > 0x464)
  {
    if ((u32)v35 > 0x47A)
    {
      if (v35 != 1169)
      {
        if (v35 != 1157)
          goto LABEL_142;
LABEL_126:
        if ((v33->para->badstatus & 0x800) != 0)
          goto LABEL_167;
        return 1;
      }
      goto LABEL_132;
    }
    if (v35 != 1129)
    {
      if (v35 != 1146)
        goto LABEL_142;
      sBtlSetDeleteKaja(v33, 1146);
      wk->status3 &= 0x80008F00;
      goto LABEL_167;
    }
LABEL_192:
    v66 = Skilltbl->attrtime;
    v67 = v16->para;
    v33->wkKarn[0]->m_skillid = 0;
    if (sBtlChkHaveMemSkl(v67, 43))
      v66 += v16->para->autost_cnt;
    wkKarn = v33->wkKarn;
    v69 = v16->wkKarn;
    v70 = hwk->skillid;
    v71 = v16->aiwk;
    v71->cmndFrm = 0;
    v71->cmndFrmMax = v66;
    wkKarn[0]->m_cnt = v66;
    v69[0]->m_skillid = v70;
    v16->drawgaugetype = 5;
    return 1;
  }
  if (v35 == 1102)
    goto LABEL_126;
  if (v35 != 1114)
  {
    if (v35 != 1124)
      goto LABEL_142;
    goto LABEL_132;
  }
  if ((wk->status3 & 0x10FF) != 0)
  {
    PESTMEGIDORA(wk);
    return 1;
  }
LABEL_167:
  if ((u32)(wk->actwk->use_skillid - 1177) <= 0x20 && ((1 << (LOBYTE(wk->actwk->use_skillid) + 103)) & 0x100040001LL) != 0)
  {
    return 1;
  }
  if ((hwk->skillflg & 1) != 0 && v33->damagecnt >= 1 && (u32)(hwk->skillid - 1299) > 3)
    return 0;
  if ((Skilltbl->flg2 & 0x800) == 0)
  {
    if (!wk->cmbSkl->tateLv)
    {
      skillflg = hwk->skillflg;
      if ((skillflg & 0x800) != 0)
      {
        v84 = *(u64 *)&hwk->serialID;
        v33->damage_actionf_cnt = 1;
        *(u64 *)&v33->damage_serialID = v84;
        hitlwk = hwk->hitlwk;
        v33->damage_actionf = hwk->actionf;
        v63 = hitlwk;
        v64 = v33;
        goto LABEL_226;
      }
      if ((skillflg & 1) != 0)
        sBtlGetPChara();
      serialID = hwk->serialID;
      if (v33->damage_serialID == serialID)
      {
        if (v33->damage_workID == hwk->serialID2)
        {
          actioncnt = hwk->actioncnt;
          if (actioncnt >= 2 && (hwk->skillflg & 0x20000000) == 0)
          {
            v60 = v33;
            if (v33->damage_actionf <= 0 && actioncnt > v33->damage_actionf_cnt)
            {
              damage_actionf_cnt = (u16)v33->damage_actionf_cnt;
              v33->damage_actionf = hwk->actionf;
              v33->damage_actionf_cnt = damage_actionf_cnt + 1;
              if (damage_actionf_cnt)
                goto LABEL_227;
              goto LABEL_189;
            }
          }
        }
        return 0;
      }
      v132 = hwk->skillid;
      v60 = v33;
      if (v132 == 149 || v132 == 176 || (hwk->area & 0x800) != 0)
      {
        v33->damage_serialID = serialID;
        v33->damage_workID = hwk->serialID2;
      }
      else
      {
        damage_workID = v33->damage_workID;
        if (damage_workID == hwk->serialID2)
        {
          v134 = hwk->actioncnt;
          if (v134 < 2)
            return 0;
          if ((hwk->skillflg & 0x20000000) != 0)
            return 0;
          if (v33->damage_actionf > 0)
            return 0;
          v135 = v33->damage_actionf_cnt;
          if (v134 <= v135)
            return 0;
          actionf = hwk->actionf;
          v33->damage_serialID = serialID;
          v33->damage_workID = damage_workID;
          v33->damage_actionf = actionf;
          v33->damage_actionf_cnt = v135 + 1;
          if (!(u16)v135)
          {
LABEL_189:
            v62 = hwk->hitlwk;
            v63 = v62;
            v33 = v60;
            v64 = v60;
LABEL_226:
            sBtlEntryUnitList(v63, v64);
            goto LABEL_227;
          }
          goto LABEL_227;
        }
        if (hwk->BEDtype == 2)
        {
          if (sBtlCheckHitHelp(hwk, v33))
            return 0;
        }
        if (!sBtlSearchDMG_Unit(hwk, v33))
          return 0;
        if ((hwk->area & 0x4000) != 0)
        {
LABEL_346:
          v137 = hwk->hitlwk;
          sBtlEntryUnitList(v137, v33);
          if (hwk->actioncnt == 1)
          {
            sBtlSetEntryUnitList_Hit(hwk, v33);
          }
          goto LABEL_227;
        }
        *(u64 *)&v33->damage_serialID = *(u64 *)&hwk->serialID;
      }
      v33->damage_actionf = hwk->actionf;
      v33->damage_actionf_cnt = 1;
      goto LABEL_346;
    }
  }
LABEL_227:
  v87 = hwk->skillid;
  SetChkskl(wk, v87);
  v89 = hwk->acterID;
  v90 = wk->UnitMng;
  v91 = sBtlSearchUnit_ID(v90, v89);
  if (v91)
  {
    playerID = v91->ListID;
    v94 = wk;
    if (playerID == v94->playerID)
    {
      v95 = wk->ListID;
      v94 = wk;
      playerID = v94->playerID;
      if (v95 != playerID && (wk->side & 2) != 0 && (wk->status & 0x800) == 0)
      {
        v94 = wk;
        v94->hittargetID = wk->ListID;
      }
    }
  }
  devilid = v33->para->devilid;
  sBtlGetDevilData(devilid, -1);
  if (v91)
  {
    if (sBtlCheckDamageTarget(v91) && (hwk->skillflg & 1) != 0 && (v91->side & v33->side) == 0)
    {
      v33->actaiwk->aborttargetID = v91->ListID;
    }
  }
  v99 = hwk->skillid;
  if (v99 != 82 && v99 != 610)
  {
    if (v99 == 1166)
    {
      if ((v33->para->badstatus & 0x1000) == 0)
        return 1;
      v100 = Skilltbl->attr;
      v101 = sBtlCheckAisyoEx(v33, v100, &a_pHanshaType);
      v105 = v101;
      if ((u32)(a_pHanshaType - 1) > 1)
      {
        v106 = v101 & 0x2000;
        if ((v101 & 0x2000) == 0 && a_pHanshaType == 3)
        {
          v124 = Skilltbl->para;
          sBtlSetAddMagAisyo(v33, v124);
          goto LABEL_317;
        }
      }
      else
      {
        sBtlSetReflectDamage(v33, hwk);
        v106 = v105 & 0x2000;
      }
      if (v106)
      {
        v114 = Skilltbl->para;
        v115 = v33;
LABEL_316:
        sBtlSetAbsorbDamage(v115, 0, v114);
        return 1;
      }
LABEL_317:
      if ((v105 & 0x1000) != 0)
        goto LABEL_321;
      v125 = v33->para;
      if (sBtlChkHaveMemSkl(v125, 52))
        goto LABEL_321;
      v173 = v33->para;
      HaveMemSkl = sBtlChkHaveMemSkl(v173, 28);
      v175 = v33->para;
      if (HaveMemSkl)
      {
        if (!v175->autost_cnt2)
        {
LABEL_321:
LABEL_502:
          sBtlSetInvalidDamage(v33);
          return 1;
        }
        v176 = 80 * v175->autost_cnt2 / 100;
      }
      else
      {
        LOWORD(v176) = 80;
      }
      v247 = sBtlChkHaveMemSkl(v175, 87) != 0;
      if ((u16)v176 >> v247 > (u32)GetPercentage())
      {
        maxhp = v33->para->now->maxhp;
        if ((Skilltbl->flg2 & 0x1020000) == 0 && (wk->status & 0x100) != 0 && (hwk->attr_flg & 0x300) == 0)
        {
          if ((v33->side & 0x80) == 0)
            goto LABEL_660;
          if (wk->battlemode != 3)
          {
            maxhp = RD_SkillDamageChack(maxhp);
          }
          else
          {
LABEL_660:
            if (maxhp >= 0)
              v251 = maxhp;
            else
              v251 = maxhp + 1;
            maxhp = v251 >> 1;
          }
          if (v33 == sBtlGetPChara())
          {
            sBtlGuardHit(v33, 1);
          }
        }
        v363 = sBtlCheckKuishibari(v33, maxhp);
        sBtlDecHp(v33, v363, 0);
        if ((v33->status & 0x40000000) != 0)
        {
          sBtlSetNormalDamage(v33, v363, 0, 0);
          sBtlSetSpecialDamage_DamageOnly(v33);
          return 1;
        }
        if (!sBtlSetDeadDamageEx(v33, wk, hwk, v363, v105, a_pbDamage, &a_pRate))
        {
          v368 = v33;
LABEL_1020:
          sBtlSetDamageProc(v368, wk, hwk, v363, v105);
          return 1;
        }
        return 1;
      }
      goto LABEL_664;
    }
    v111 = hwk->skillflg;
    a_pHanshaType = 0;
    if ((v111 & 1) != 0)
    {
      v118 = v33;
      v119 = Skilltbl->attr;
      v120 = wk;
      if (v120->sword_eff_step < 1)
        goto LABEL_300;
      v120 = wk;
      if (!v120->sword_eff_skl || !sBtlGetPChara() || (Skilltbl->flg2 & 0x10) == 0)
        goto LABEL_300;
      v122 = sBtlGetSkilltbl(wk->sword_eff_skl);
      if (v122)
      {
        v119 = v122->attr;
        skillidb = 1;
      }
      else
      {
LABEL_300:
        skillidb = 0;
      }
      v123 = sBtlCheckAisyoEx(v33, v119, &a_pHanshaType);
      v112 = v123;
      if ((u32)(a_pHanshaType - 1) > 1)
      {
        if ((v123 & 0x2000) == 0 && a_pHanshaType == 3)
        {
          v126 = Skilltbl->para;
          v127 = v126;
          v33 = v118;
          sBtlSetAddMagAisyo(v118, v127);
        }
      }
      else
      {
        sBtlSetReflectDamage(v33, hwk);
      }
    }
    else
    {
      skillidb = 0;
      v112 = 0;
    }
    v139 = (u16)wk->para->devilid;
    if ((v139 != 297 && v139 != 290 || !wk->Itimoku_CloseEye) && (hwk->skillflg & 0x10000) != 0)
    {
      v139 = (u16)wk->para->devilid;
      v140 = v33->para->devilid;
      if ((u32)(v140 - 188) >= 0x19 && v140 != 145)
        v112 &= 0xFFF7CFFF;
    }
    if (v139 == 521)
      v142 = v112 | 0x148000;
    else
      v142 = v112;
    if ((wk->side & 2) != 0)
    {
      actwk = wk->actwk;
      v143 = v33;
      status = actwk->status;
      if ((status == 53 || status == 6) && actwk->use_skillid == 1472)
        v142 = v112 | 0x148000;
    }
    else
    {
      v143 = v33;
    }
    if ((hwk->attr_flg & 2) == 0 || (v142 & 0x20000) == 0)
      v147 = v142;
    else
      v147 = v142 | 0x148000;
    if ((v147 & 0x1000) != 0 && ((Skilltbl->flg2 & 0x10) != 0 || hwk->skillid == 149) && wk->actwk->status == 9 && (wk->hstatus & 0x10) != 0)
    {
      v147 &= ~0x1000u;
    }
    if ((hwk->area & 0x4000) != 0 && (v147 == 0x2000 || v147 == 4096))
      v147 = 0;
    if ((v143->side & 1) != 0 && v143->actaiwk->mode == 15 && v147 == 0)
      v147 |= 0x8000u;
    if ((Skilltbl->flg2 & 0x1020000) != 0)
    {
LABEL_411:
      if (!v147 && (v143->side & 2) != 0)
      {
        if (sBtlCheckMotionTiming(v143))
        {
          motionID = wk->motionID;
          if (motionID == 14 || motionID == 1)
          {
            ++v143->damage_hitcnt;
            LimitRange_2(&v143->damage_hitcnt, 0, 999);
            v147 = 0;
          }
          else
          {
            v147 = 0;
            v143->damage_hitcnt = 1;
          }
        }
        else
        {
          v147 = 0x8000;
        }
      }
      if ((v147 & 0x4000) != 0)
      {
        v154 = hwk->skillid;
        v153 = v154 == 149 || (u32)(v154 - 164) < 3;
      }
      else
      {
        v153 = 0;
      }
      v156 = v147 & 0xFFFFBFFF;
      v157 = v153 | ((u16)(hwk->area & 0x400) >> 10);
      if (skillidb)
        v158 = v147;
      else
        v158 = v147 & 0xFFFFBFFF;
      if (v157)
        v159 = v158;
      else
        v159 = v147;
      if ((v143->status & 0x100000) != 0 && !CheckBadStatus(v143, 0) && (v159 & 0x4000) != 0)
      {
        if ((v143->aiwk->scrflag & 0x10000) != 0)
        {
          v156 = v159;
          if (v143->weak_shild)
            v156 = v159 & 0xFFFF3FFF | 0x8000;
        }
        v159 = v156 | 0x200000;
      }
      if ((v159 & 0x4000) == 0 || !wk->bTateNoDmg)
        v162 = v159;
      else
        v162 = v159 & 0xFFFFBFFF;
      if ((v143->side & 2) == 0 || (v162 & 0xFFFF7FFF) != 0)
      {
LABEL_509:
        if ((v143->side & 0x80) != 0 && (v162 & 0xFFFF7FFF) == 0 && (v162 & 0x4000) == 0)
        {
          v178 = v143->actwk;
          v179 = v178->status;
          if (v179 == 56)
            goto LABEL_517;
          if (v179 == 12)
          {
            use_skillid = v178->use_skillid;
            if (sbtlplayertblChkPlayerMagSkill(use_skillid))
            {
LABEL_517:
              v162 |= 0x148000u;
              v143->hstatus |= 0x420u;
            }
          }
        }
        if ((hwk->skillflg & 1) != 0)
        {
          v181 = v143->para;
          if (sBtlChkHaveMemSkl(v181, 49) && v143->para->now->luck > (s32)GetPercentage())
          {
            v162 = 4096;
            v143->damagecnt = 30;
          }
        }
        s_type = Skilltbl->s_type;
        v143->criticalflg = 0;
        if ((s_type & 8) != 0)
        {
LABEL_538:
          if ((v162 & 0x2000) != 0)
          {
            if ((hwk->skillflg & 1) != 0)
            {
              v197 = hwk->skillid;
              if (hwk->BEDtype == 2)
                aListID = hwk->awk->aListID;
              else
                aListID = hwk->acterID;
              Damage = GetDamage(wk, v197, aListID, hwk, 0x2000, 1);
              v207 = sBtlGetSkilltbl(hwk->skillid)->para;
              sBtlSetAbsorbDamage(wk, Damage, v207);
            }
            side = wk->side;
            if ((side & 2) != 0)
            {
              v214 = hwk->skillid;
              expList = wk->expList;
              v216 = hwk->acterID;
              sBtlSetRirituNakamaHD(expList, wk, v214, v216, 0x13u);
              sBtlSetRirituEnemyHD(wk->expList, wk, hwk->skillid, hwk->acterID, 7);
              v217 = hwk->acterID;
              v218 = wk->UnitMng;
              v219 = sBtlSearchUnit_ID(v218, v217);
              CallSign(v219->hpCallCtrl, 1, 4, 0);
            }
            else if ((side & 1) != 0)
            {
              v210 = hwk->skillid;
              v211 = wk->expList;
              v212 = hwk->acterID;
              sBtlSetRirituNakamaHD(v211, wk, v210, v212, 7u);
              sBtlSetRirituEnemyHD(wk->expList, wk, hwk->skillid, hwk->acterID, 15);
            }
            goto LABEL_626;
          }
          if ((wk->side & 0x81) == 1)
          {
            v186 = v143;
            if (!fldGb->nakamaMode && (wk->status & 0x100) != 0 && (Skilltbl->flg2 & 0x1020000) == 0)
            {
              if (!wk->eff_wait_guard)
              {
                v254 = hwk->skillid;
                v255 = wk->expList;
                v256 = hwk->acterID;
                sBtlSetRirituNakamaHD(v255, wk, v254, v256, 2u);
                v258 = hwk->skillid;
                v259 = hwk->acterID;
                v260 = GetDamage(v186, v258, v259, hwk, v162, 0);
                if (!sBtlSetDeadDamageEx(v186, wk, hwk, v260, v162, a_pbDamage, &a_pRate))
                {
                  sBtlSetDamageProc(v186, wk, hwk, v260, v162);
                  if ((wk->side & 1) != 0)
                    wk->hpGageDamageFlag = 1;
                }
                x = wk->pos.x;
                y = wk->pos.y;
                z = wk->pos.z;
                w = wk->pos.w;
                v385.x = x;
                v385.y = y;
                v385.z = z;
                v385.w = w;
                sBtlPlayDamageSE(v385, 1);
                wk->eff_wait_guard = 30;
                if ((v186->status & 0x100) != 0)
                {
                  sBtlSetHitback(v186, hwk, v162);
                }
              }
              ResetAction(wk, 0, 0);
              sBtlResetAAI(wk);
              v268 = wk->aiwk;
              wk->damage_hitcnt = 0;
              v268->mode = 0;
              wk->actcounter = wk->actcounter_max;
              if (wk->motionID != 29)
              {
                sBtlSetMotion(wk, 29, 6, 0, 0);
              }
              sBtlSetAction(wk, 59, 0);
              effList = wk->effList;
              sBtlForceDelete_ID_Summon(effList, wk);
              sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
              hitList = wk->hitList;
              sBtlClearHitC(hitList, wk);
              return 1;
            }
          }
          skillidc = v143;
          if ((v143->side & 2) != 0)
          {
            if ((wk->status3 & 0x20000000) != 0 && (hwk->attr_flg & 0x100) == 0 && hwk->skillid != 114)
            {
              v162 = 4096;
            }
          }
          if ((v162 & 0x1000) == 0)
          {
            v189 = (v143->hstatus << 10) & 0x8000
                 | ((((u32)v143->hstatus >> 10) & 1) << 18)
                 | v162;
            if (!((v143->hstatus << 10) & 0x8000 | v162 & 0x8000))
            {
              v190 = v143->para;
              if (sBtlGetBadStatus(v190) == 9)
                v189 |= 0x8000u;
            }
            v191 = (8 * hwk->skillflg) & 0x8000 | v189;
            if ((8 * hwk->skillflg) & 0x8000 | v189 & 0x8000 || (skillidc->side & 2) == 0 || (v192 = skillidc->exsts, (v192 & 1) == 0) || (skillidc->aiwk->scrflag & 0x10000) == 0)
            {
LABEL_727:
              if ((v191 & 0x8000) != 0)
                goto LABEL_777;
              if ((skillidc->side & 2) == 0)
                goto LABEL_773;
              exsts = skillidc->exsts;
              if ((exsts & 1) == 0 || wk->actwk->status - 7 > 1)
                goto LABEL_773;
              v277 = skillidc->para->level - v91->para->level;
              v278 = hwk->skillid;
              if (v278 == 149)
              {
                if ((exsts & 4) == 0)
                {
                  if (fldGb->nakamaMode)
                  {
                    if (v277 > 4)
                      goto LABEL_737;
                    goto LABEL_768;
                  }
LABEL_756:
                  if (GetPercentage() >= 0x64u)
                    goto LABEL_773;
                  goto LABEL_772;
                }
                if (v277 > 4)
                  goto LABEL_756;
LABEL_749:
                if (v277 <= -5)
                  v282 = 40;
                else
                  v282 = 60;
                if (v282 > GetPercentage())
                  goto LABEL_772;
                goto LABEL_773;
              }
              if ((u32)(v278 - 1316) > 0xFFFFFFF9)
              {
                v283 = v277 <= 4;
                if ((exsts & 4) != 0)
                {
                  if (v277 > 4)
                    goto LABEL_756;
                  goto LABEL_749;
                }
              }
              else
              {
                if (v278 == 1334)
                {
                  if (wk->sword_chaincnt)
                    v281 = 100;
                  else
                    v281 = 0;
                  if (v281 > GetPercentage())
                    goto LABEL_772;
                  goto LABEL_773;
                }
                v283 = v277 <= 4;
                if ((exsts & 4) == 0)
                {
                  if (v277 <= 4)
                  {
                    if (v277 <= -5)
                      v284 = 10;
                    else
                      v284 = 15;
                    if (v284 > GetPercentage())
                      goto LABEL_772;
                  }
                  else
                  {
                    Percentage = GetPercentage();
                    if (Percentage < 0x1Eu)
LABEL_772:
                      v191 = sBtlSetAttr(skillidc, v191);
                  }
LABEL_773:
                  if (v191)
                    goto LABEL_777;
                  if ((v91->side & 0x80) == 0 || (skillidc->side & 2) == 0)
                  {
                    v191 = 0;
                    goto LABEL_777;
                  }
                  v191 = 0;
                  v303 = skillidc->motionID;
                  if (v303 == 1 || v303 == 14)
                  {
LABEL_777:
                    if (!wk->hangeki_on)
                    {
                      skillidc->damage_1stmotcnt = 0;
                      skillidc->damage_1stmotnum = 0;
                    }
                    if ((wk->status & 0x800) == 0)
                    {
LABEL_784:
                      v287 = hwk->skillid;
                      if (v287 == 117)
                        skillidc->rejyenehelper = wk->ListID;
                      if (hwk->BEDtype == 2)
                        v288 = hwk->awk->aListID;
                      else
                        v288 = hwk->acterID;
                      v290 = GetDamage(skillidc, v287, v288, hwk, v191, 1);
                      if ((wk->status & 0x40000000) != 0)
                      {
                        v302 = hwk->skillid;
                        sBtlSetSpecialDamage(skillidc, hwk, v302, v290);
                        return 1;
                      }
                      if ((skillidc->side & 2) != 0)
                      {
                        v292 = wk;
                        if ((v292->status3 & 0x4000) != 0)
                        {
                          v292 = wk;
                          v293 = v292->UnitMng;
                          v294 = hwk->acterID;
                          wk = sBtlSearchUnit_ID(v293, v294);
                          skillidc = wk;
                          if (!wk)
                            return 1;
                        }
                      }
                      if ((skillidc->side & 2) != 0)
                      {
                        if ((wk->status3 & 0x4000000) != 0 && hwk->skillid != 114)
                        {
                          if (v290 >= 0)
                            v296 = v290;
                          else
                            v296 = v290 + 1;
                          v290 = v296 >> 1;
                        }
                      }
                      v297 = skillidc->para;
                      hp = v297->now->hp;
                      if (hp < 1 || v290 < hp)
                      {
LABEL_849:
                        v313 = v297->now->hp;
                        if (v313 >= 1)
                        {
                          if (v290 >= v313 && v297->devilid == 257)
                            v290 = v313 - 1;
                          if (v290 >= v313 && v297->devilid == 293)
                          {
                            if (!lmapSetBattleDestFlagCheck(4))
                              v290 = skillidc->para->now->hp - 1;
                          }
                        }
                        v314 = hwk->skillid;
                        v315 = hwk->acterID;
                        v316 = sBtlSetDamage(skillidc, v314, v290, v315);
                        if (v290 != -1)
                        {
                          if ((wk->status & 0x8000) != 0)
                          {
                            if ((v316 & 4) != 0)
                            {
                              v351 = hwk->skillid;
                              sBtlCheckBadStatus(v91, skillidc, v351, 0);
                              return 1;
                            }
                          }
                          else if ((v316 & 4) != 0)
                          {
                            return 1;
                          }
                          v329 = hwk->skillid;
                          v330 = hwk->skillflg;
                          if ((skillidc->side & 1) != 0)
                          {
                            if (!v331)
                            muteki_time = sBtlGetSkilltbl(v329)->muteki_time;
                            if (((muteki_time < 1) & (v330 >> 3)) != 0)
                              LOWORD(muteki_time) = 1;
                            skillidc->damagecnt = muteki_time;
                            if (v191 || (u16)muteki_time || (skillidc->status & 0x100) != 0)
                              goto LABEL_886;
                            LOWORD(v333) = 120;
                          }
                          else
                          {
                            if (!v331)
                            v333 = sBtlGetSkilltbl(v329)->muteki_time;
                            if (((v333 < 1) & (v330 >> 3)) != 0)
                              LOWORD(v333) = 1;
                          }
                          skillidc->damagecnt = v333;
LABEL_886:
                          if (sBtlSetDeadDamageEx(skillidc, wk, hwk, v290, v191, a_pbDamage, &a_pRate))
                          {
                            v337 = hwk->acterID;
                            if (v337 == wk->playerID && (wk->side & 2) != 0)
                            {
                              Instance = get_Instance(0);
                              HitCountAdd(Instance, 1, hwk->skillid, 0);
                            }
                          }
                          else
                          {
                            a_pbDamage[0] = sBtlSetDamageProc(skillidc, wk, hwk, v290, v191);
                            if ((wk->side & 1) != 0)
                              wk->hpGageDamageFlag = 1;
                          }
                          goto LABEL_938;
                        }
                        if (cfgGetConfigGAME(1, 0) || (skillidc->side & 2) != 0)
                        {
                          sBtlSetStoneDeadDamageProc(skillidc, wk, hwk, -1, v317);
                          a_pbDamage[0] = 1;
                          if ((skillidc->side & 0x81) == 1)
                          {
                            Nakama = sBtlGetNakama(0);
                            if (Nakama)
                            {
                              v340 = Nakama;
                              if (Nakama != skillidc)
                              {
                                v342 = hwk->skillid;
                                v343 = wk->expList;
                                v344 = hwk->acterID;
                                sBtlSetRirituNakamaHD(v343, v340, v342, v344, 0x11u);
                              }
                            }
                            v345 = sBtlGetNakama(1);
                            if (v345)
                            {
                              v346 = v345;
                              if (v345 != skillidc)
                              {
                                v348 = hwk->skillid;
                                v349 = wk->expList;
                                v350 = hwk->acterID;
                                sBtlSetRirituNakamaHD(v349, v346, v348, v350, 0x11u);
                              }
                            }
                          }
LABEL_938:
                          if (hwk->skillid != 1114)
                          {
LABEL_948:
                            actaiwk = skillidc->actaiwk;
                            if (actaiwk->mode == 10)
                            {
                              actaiwk->status = actaiwk->status & 0xFFFFFF9F | 0x40;
                              v358 = skillidc->ListID;
                              if (v358 != wk->playerID)
                              {
                                ResetAction(skillidc, 0, 0);
                              }
                            }
                            if (a_pbDamage[0])
                            {
                              v360 = wk->ListID;
                              if (v360 == wk->playerID)
                              {
                                if (!sBtlCheckSetsuma())
                                {
                                  sBtlResetAction(skillidc);
                                }
                              }
                              if (a_pRate != 0.0)
                                skillidc->m_rate = a_pRate;
                            }
                            return 1;
                          }
                          v354 = wk->ListID;
                          if (v354 == wk->playerID)
                          {
                            sBtlSetKudaDamage(300);
LABEL_947:
                            PESTMEGIDORA(wk);
                            goto LABEL_948;
                          }
                          goto LABEL_947;
                        }
                        skillidc->revival = 1;
                        v319 = skillidc->actaiwk;
                        v320 = skillidc->actwk;
                        targetID = v319->targetID;
                        v319->targetID = wk->ListID;
                        order_stockID = v320->order_stockID;
                        v320->order_stockID = -1;
                        skillidc->para->now->hp = 0;
                        v323 = wk->side;
                        sBtlCheckEffectData(wk, 114, 1u, 0, v323, -1, 0);
                        skillidc->actaiwk->targetID = targetID;
                        skillidc->actwk->order_stockID = order_stockID;
                        sBtlDeleteBuffAll(skillidc);
                        sBtlDeleteDeBuffAll(skillidc);
                        v326 = skillidc->para;
                        v326->now->hp = v326->now->maxhp;
                        if (sBtlGetBadStatus(v326) == 6)
                        {
                          sBtlResetBadStatus(skillidc, 64);
LABEL_935:
                          dvltkList = wk->dvltkList;
                          sBtlCreateDvltk_Gouto(dvltkList, skillidc, 292, 1);
                          goto LABEL_938;
                        }
                        goto LABEL_935;
                      }
                      v299 = (u16)v297->devilid;
                      if (v297->devilid <= 304)
                      {
                        switch (v299)
                        {
                          case 268:
                            v301 = 269;
                            goto LABEL_845;
                          case 269:
                            v301 = 268;
LABEL_845:
                            UnitFromDevilID = sBtlGetUnitFromDevilID(v301);
                            if (UnitFromDevilID)
                            {
                              v297 = skillidc->para;
                              if (UnitFromDevilID->para->now->hp <= 0)
                                v290 = v297->now->hp - 1;
                            }
                            else
                            {
                              v297 = skillidc->para;
                            }
                            goto LABEL_849;
                          case 304:
                            v301 = 305;
                            goto LABEL_845;
                          default:
                            goto LABEL_849;
                        }
                      }
                      else
                      {
                        switch (v299)
                        {
                          case 305:
                            v301 = 304;
                            goto LABEL_845;
                          case 312:
                            v301 = 313;
                            goto LABEL_845;
                          case 313:
                            v301 = 312;
                            goto LABEL_845;
                          default:
                            goto LABEL_849;
                        }
                      }
                      goto LABEL_845;
                    }
LABEL_780:
                    v286 = hwk->skillflg;
                    if ((v286 & 0x8000000) != 0)
                      skillidc->hitsliphelper = wk->ListID;
                    if ((v286 & 0x20000000) != 0)
                      skillidc->tdanhelper = wk->ListID;
                    goto LABEL_784;
                  }
                  skillidc->damage_1stmotcnt = 60;
                  v304 = skillidc->para;
                  level = v91->para->level;
                  v306 = skillidc->damage_1stmotnum + 1;
                  v307 = v304->level;
                  skillidc->damage_1stmotnum = v306;
                  v308 = v307 - level;
                  if (v308 <= -5)
                    v309 = 0;
                  else
                    v309 = 3;
                  if (v308 >= 5)
                    v310 = 6;
                  else
                    v310 = v309;
                  v311 = skillidc->actwk->status;
                  if (v311 == 53 || v311 == 6)
                  {
                    v310 += 2;
                    if ((skillidc->exsts & 4) != 0)
                      goto LABEL_968;
                  }
                  else if (v311 == 3)
                  {
                    v310 += 3;
                    if ((skillidc->exsts & 4) != 0)
                    {
LABEL_968:
                      if ((u32)v310 <= 3)
                        v310 = 3;
                      v361 = (f32)v310 + (f32)v310;
                      v310 = v361;
                      if (v361 == INFINITY)
                        v310 = 0x80000000;
                      if ((u32)(hwk->skillid - 1316) < 0xFFFFFFFA)
                        v310 = 0;
                      if ((wk->status & 0x100000) == 0)
                      {
LABEL_975:
                        if ((f32)((f32)v304->now->hp / (f32)v304->now->maxhp) < 0.26)
                          v310 = 0;
                      }
LABEL_977:
                      v191 = (v310 > v306) << 15;
                      if ((wk->status & 0x800) == 0)
                        goto LABEL_784;
                      goto LABEL_780;
                    }
                  }
                  else if ((skillidc->exsts & 4) != 0)
                  {
                    goto LABEL_968;
                  }
                  if ((u32)(hwk->skillid - 1316) < 0xFFFFFFFA)
                    v310 = 0;
                  if ((wk->status & 0x100000) == 0)
                    goto LABEL_975;
                  goto LABEL_977;
                }
              }
              if (!v283)
              {
LABEL_737:
                if (GetPercentage() >= 0x3Cu)
                  goto LABEL_773;
                goto LABEL_772;
              }
LABEL_768:
              if (v277 <= -5)
                v285 = 20;
              else
                v285 = 30;
              if (v285 > GetPercentage())
                goto LABEL_772;
              goto LABEL_773;
            }
            v193 = skillidc->para->level - v91->para->level;
            v194 = hwk->skillid;
            if (v194 == 149)
            {
              if (fldGb->nakamaMode)
              {
                v196 = 100;
                if (v193 > 4 || (skillidc->exsts & 4) != 0)
                  goto LABEL_725;
                goto LABEL_720;
              }
            }
            else
            {
              if ((u32)(v194 - 1310) <= 5)
              {
                v196 = 100;
                if ((v192 & 4) != 0 || v193 > 4)
                {
LABEL_725:
                  if (v196 > GetPercentage())
                    v191 = sBtlSetAttr(skillidc, v191);
                  goto LABEL_727;
                }
                goto LABEL_720;
              }
              if ((v192 & 4) != 0)
              {
                if (v193 <= 4)
                {
LABEL_720:
                  v273 = v193 <= -5;
                  v274 = 50;
                  v275 = 80;
LABEL_721:
                  if (v273)
                    v196 = v274;
                  else
                    v196 = v275;
                  goto LABEL_725;
                }
              }
              else if (v193 <= 4)
              {
                v273 = v193 <= -5;
                v274 = 25;
                v275 = 40;
                goto LABEL_721;
              }
            }
            v196 = 100;
            goto LABEL_725;
          }
          sBtlSetMukouDamage(wk, v162);
          v201 = wk->side;
          if ((v201 & 2) != 0)
          {
            v221 = hwk->skillid;
            v222 = wk->expList;
            v223 = hwk->acterID;
            sBtlSetRirituNakamaHD(v222, wk, v221, v223, 0x12u);
            sBtlSetRirituEnemyHD(wk->expList, wk, hwk->skillid, hwk->acterID, 6);
            v224 = hwk->acterID;
            v225 = wk->UnitMng;
            v226 = sBtlSearchUnit_ID(v225, v224);
            CallSign(v226->hpCallCtrl, 1, 4, 0);
            if ((skillidc->status & 0x100) != 0)
              goto LABEL_612;
          }
          else
          {
            if ((v201 & 1) == 0)
            {
              if ((v143->status & 0x100) == 0)
                goto LABEL_577;
LABEL_612:
              sBtlSetHitback(skillidc, hwk, v162);
              v202 = a_pHanshaType;
              if (a_pHanshaType == 3)
                goto LABEL_616;
              goto LABEL_615;
            }
            v244 = hwk->skillid;
            v245 = wk->expList;
            v246 = hwk->acterID;
            sBtlSetRirituNakamaHD(v245, wk, v244, v246, 6u);
            sBtlSetRirituEnemyHD(wk->expList, wk, hwk->skillid, hwk->acterID, 14);
            if ((skillidc->status & 0x100) != 0)
              goto LABEL_612;
          }
LABEL_577:
          v202 = a_pHanshaType;
          if (a_pHanshaType == 3)
            goto LABEL_616;
LABEL_615:
          if (v202)
          {
LABEL_626:
            v237 = wk->dvltkList;
            sBtlCreateDvltk_Priority(v237, v91, 5);
            return 1;
          }
LABEL_616:
          v227 = hwk->skillid;
          v228 = sBtlContinuousSe(wk, v227);
          if (wk->eff_wait_mukou)
            goto LABEL_626;
          v229 = v228;
          v231 = wk;
          if (v231->bTateNoDmg)
          {
LABEL_622:
            sBtlCreateSTP_Unit(v231->stpList, wk, 3, 0, 0, 0);
            if (!v229)
            {
              v232 = skillidc->pos.x;
              v233 = skillidc->pos.y;
              v235 = skillidc->pos.z;
              v234 = skillidc->pos.w;
              v384.x = v232;
              v384.y = v233;
              v384.z = v235;
              v384.w = v234;
              sBtlPlayDamageSE(v384, 4);
            }
            goto LABEL_626;
          }
          wk->eff_wait_mukou = 20;
          goto LABEL_622;
        }
        if (v91 == sBtlGetPChara())
        {
          PChara = sBtlGetPChara();
          if (PChara)
          {
            if ((wk->status3 & 0x10000) != 0)
            {
              v204 = GetPercentage();
              if (v204 <= 0x1D)
                goto LABEL_637;
            }
          }
        }
        else
        {
        }
        v184 = wk;
        if ((v184->scrFlag & 0x10000000) == 0 || (v143->side & 2) == 0 || (v143->status & 0x100000) == 0)
        {
          if (!v91)
            goto LABEL_538;
          v185 = v91->para;
          if (!sBtlChkHaveMemSkl(v185, 91) || hwk->skillid != 149 || GetPercentage() > 9u)
          {
            goto LABEL_538;
          }
LABEL_664:
          v240 = wk;
          v241 = 8;
          v242 = 0;
LABEL_667:
          sBtlCreateSTP_Unit(wk->stpList, v240, v241, v242, 0, 0);
          return 1;
        }
        v184 = wk;
        v238 = ++v184->sukacnt;
        if (v238 >= 20)
        {
          v184 = wk;
          v184->status4 |= 1u;
        }
LABEL_637:
        v240 = wk;
        v241 = 7;
        v242 = 60;
        goto LABEL_667;
      }
      if (wk->hangeki_on || wk->hangeki_nokezoranai >= 1)
      {
        v163 = hwk->skillid;
        if (!sbtlplayertblChkPlayerMagSkill(v163))
        {
          v164 = hwk->skillflg;
          if ((v164 & 0x2000) == 0 && (v164 & 2) == 0)
            v162 |= 0x148000u;
        }
        goto LABEL_506;
      }
      v172 = v143->actwk->status;
      if (v172 > 0x1F)
      {
        if (v172 != 67 && v172 != 54)
        {
LABEL_506:
          v177 = v143->actwk->status;
          if (v177 == 31 || v177 == 3)
            v162 |= 0x400000u;
          goto LABEL_509;
        }
      }
      else if (v172 != 31)
      {
        goto LABEL_506;
      }
      v162 |= 0x148000u;
      goto LABEL_506;
    }
    if (!wk->nguard_dmgcnt && !(u32)sub_1905740(10, 0) && (hwk->attr_flg & 0x300) == 0)
      wk->nguard_dmgcnt = 30;
    v149 = wk->actwk->status;
    if (v149 > 0xA)
    {
      if (v149 > 0x3A || ((1 << v149) & 0x6000000000C0000LL) == 0)
      {
LABEL_407:
        if ((wk->side & 0x81) == 1)
        {
          if (!fldGb->nakamaMode && (wk->flg & 2) == 0 && !a_pHanshaType && (v147 & 0x1000) == 0 && (v147 & 0x2000) == 0 && (v147 & 0x4000) == 0)
          {
            v170 = wk->para;
            v171 = sBtlGetBadStatus(v170);
            if ((wk->hstatus & 0x10) == 0 && (v171 > 0xD || ((1 << v171) & 0x39C0) == 0) && (u32)(u16)wk->nguard_dmgcnt - 50 >= 0xFFFFFFCF)
            {
              wk->status |= 0x100u;
            }
          }
        }
        goto LABEL_411;
      }
    }
    else if (v149 != 6 && v149 != 10)
    {
      goto LABEL_407;
    }
    wk->nguard_dmgcnt = 0;
    goto LABEL_407;
  }
  v107 = Skilltbl->attr;
  v108 = sBtlCheckAisyoEx(v33, v107, &a_pHanshaType);
  v105 = v108;
  if ((u32)(a_pHanshaType - 1) > 1)
  {
    v110 = v108 & 0x2000;
    if ((v108 & 0x2000) == 0 && a_pHanshaType == 3)
    {
      v113 = Skilltbl->para;
      sBtlSetAddMagAisyo(v33, v113);
      goto LABEL_281;
    }
  }
  else
  {
    sBtlSetReflectDamage(v33, hwk);
    v110 = v105 & 0x2000;
  }
  if (v110)
  {
    v114 = Skilltbl->para;
    v115 = v33;
    goto LABEL_316;
  }
LABEL_281:
  if ((v105 & 0x1000) != 0)
    goto LABEL_1027;
  v116 = v33->para;
  if (sBtlChkHaveMemSkl(v116, 52))
  {
LABEL_1027:
    goto LABEL_502;
  }
  v128 = v33->para;
  v129 = sBtlChkHaveMemSkl(v128, 28);
  v130 = v33->para;
  if (v129)
  {
    if (!v130->autost_cnt2)
    {
      goto LABEL_502;
    }
    v131 = 60 * v130->autost_cnt2 / 100;
  }
  else
  {
    LOWORD(v131) = 60;
  }
  v165 = sBtlChkHaveMemSkl(v130, 87) != 0;
  if ((u16)v131 >> v165 <= (u32)GetPercentage())
    goto LABEL_664;
  v167 = v33->para->now->maxhp;
  if ((Skilltbl->flg2 & 0x1020000) == 0 && (wk->status & 0x100) != 0 && (hwk->attr_flg & 0x300) == 0)
  {
    if ((v33->side & 0x80) == 0)
      goto LABEL_476;
    if (wk->battlemode != 3)
    {
      v167 = RD_SkillDamageChack(v167);
    }
    else
    {
LABEL_476:
      if (v167 >= 0)
        v169 = v167;
      else
        v169 = v167 + 1;
      v167 = v169 >> 1;
    }
    if (v33 == sBtlGetPChara())
    {
      sBtlGuardHit(v33, 1);
    }
  }
  v363 = sBtlCheckKuishibari(v33, v167);
  sBtlDecHp(v33, v363, 0);
  if ((v33->status & 0x40000000) != 0)
  {
    if (!v366)
    sBtlSetNormalDamage(v33, v363, v105, 0);
    sBtlSetSpecialDamage_DamageOnly(v33);
    return 1;
  }
  if (!v366)
  if (!sBtlSetDeadDamageEx(v33, wk, hwk, v363, v105, a_pbDamage, &a_pRate))
  {
    v368 = v33;
    goto LABEL_1020;
  }
  return 1;
}

// 0x2053a40
bool sBtlContinuousSe(SBTLUNIT_WORK *_wk, SKLID _sklID) {
  if (wk->encountno != 58)
    return 0;
  return (sklID & 0xFFFFFFFE) == 0x510 && wk->para->devilid == 257;
}

// 0x20518e0
bool sBtlCheckAttr_ATK(SBTLDMG_HITWORK *hwk, s32 attr) {
  s32 skillid;
  _BOOL4 v6;

  if ((attr & 0x4000) != 0)
  {
    skillid = hwk->skillid;
    v6 = skillid == 149 || (u32)(skillid - 164) < 3;
    return v6 | ((u16)(hwk->area & 0x400) >> 10);
  }
  else
  {
    return (u16)(hwk->area & 0x400) >> 10;
  }
}

// 0x2055340
s32 sBtlIsAura(SBTLUNIT_WORK *pBtlUnit, s32 kindFlg) {
  tagSBTLSKL_AURA_WORK *v3;

  if (kindFlg == 0x4000000)
  {
    v3 = pBtlUnit->wkAura[1];
    if (!v3->auracnt || (pBtlUnit->aurakind & 0x4000000) == 0)
      return -1;
  }
  else
  {
    if (kindFlg != 0x2000000)
    {
      if (kindFlg == 0x1000000)
      {
        v3 = pBtlUnit->wkAura[0];
        if (v3->auracnt)
        {
          if ((pBtlUnit->aurakind & 0x1000000) == 0)
            return -1;
          return v3->aurapara;
        }
      }
      return -1;
    }
    v3 = pBtlUnit->wkAura[2];
    if (!v3->auracnt || (pBtlUnit->aurakind & 0x2000000) == 0)
      return -1;
  }
  return v3->aurapara;
}

// 0x20553d0
s32 sBtlUpdateDamageKaja(SBTLUNIT_WORK *acter, SBTLUNIT_WORK *target, SKLID skillid, s32 damage) {
  SBTLSKILLP_TBL *Skilltbl;
  bool v10;
  bool v11;
  f32 KajaParam;
  s32 v13;
  tagSBTLSKL_AURA_WORK *v14;
  s32 aurapara;
  f32 v16;
  s32 v17;
  f32 v18;
  s32 v19;
  tagSBTLSKL_AURA_WORK *v20;
  s32 v21;
  tagSBTLSKL_AURA_WORK *v22;
  s32 v23;
  s32 devilid;
  f32 v25;
  s64 v26;
  s64 v27;

  Skilltbl = sBtlGetSkilltbl(skillid);
  if (Skilltbl && (Skilltbl->flg & 0x200001) == 1)
  {
    v10 = datCheckSkillPhysicDamage(skillid);
    v11 = datCheckSkillMagicDamage(skillid);
    if (acter)
    {
      if (v10)
      {
        KajaParam = sBtlGetKajaParam(acter, 0);
        v13 = KajaParam;
        if (KajaParam == INFINITY)
          v13 = 0x80000000;
        if (v13 >= 1)
          damage += v13 * damage / 100;
        v14 = acter->wkAura[0];
        if (v14->auracnt)
        {
          if ((acter->aurakind & 0x1000000) != 0)
          {
            aurapara = v14->aurapara;
            if (aurapara >= 1)
              damage += aurapara * damage / 100;
          }
        }
      }
      if (v11)
      {
        v16 = sBtlGetKajaParam(acter, 1);
        v17 = v16;
        if (v16 == INFINITY)
          v17 = 0x80000000;
        if (v17 >= 1)
          damage += v17 * damage / 100;
      }
    }
    v18 = sBtlGetKajaParam(target, 2);
    v19 = v18;
    if (v18 == INFINITY)
      v19 = 0x80000000;
    if (v19 >= 1)
      damage += v19 * damage / -100;
    if (v10)
    {
      v20 = target->wkAura[1];
      if (v20->auracnt)
      {
        if ((target->aurakind & 0x4000000) != 0)
        {
          v21 = v20->aurapara;
          if (v21 >= 1)
            damage += v21 * damage / -100;
        }
      }
    }
    if (v11)
    {
      v22 = target->wkAura[2];
      if (v22->auracnt)
      {
        if ((target->aurakind & 0x2000000) != 0)
        {
          v23 = v22->aurapara;
          if (v23 >= 1)
            damage += v23 * damage / -100;
        }
      }
    }
    devilid = (u16)target->para->devilid;
    if (devilid == 300 || devilid == 262)
    {
      v25 = sBtlGetKajaParam(target, 0);
      if (v25 == INFINITY || (s32)v25)
        damage += 40 * damage / 100;
    }
    if (target->o_def_dn_time >= 1)
    {
      v26 = 1374389535 * target->o_def_dn_rate * damage;
      damage += (v26 >> 37) + ((u64)v26 >> 63);
    }
    if (acter && acter->o_atk_up_time >= 1)
    {
      v27 = 1374389535 * acter->o_atk_up_rate * damage;
      damage += (v27 >> 37) + ((u64)v27 >> 63);
    }
  }
  return damage;
}

// 0x20557e0
s32 sBtlGetCalcDamageEx(SBTLUNIT_WORK *wklock, SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *hwk, SKLID skillid, s32 attr, s32 damage, bool *a_pbGuard, bool *a_pbCritical) {
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v18;
  SBTLDMG_HITWORK *v19;
  SBTLUNIT_WORK *v20;
  bool v21;
  sdatUnitWork_t *para;
  u32 flg;
  char v25;
  sdatUnitWork_t *v26;
  f32 v27;
  sdatUnitWork_t *v28;
  sdatUnitWork_t *v29;
  f32 v30;
  sdatUnitWork_t *v31;
  SBTLUNIT_WORK *v32;
  sdatUnitWork_t *v33;
  f32 v34;
  sdatUnitWork_t *v35;
  bool *v36;
  f32 v37;
  bool SpiritSkillChk;
  f32 v39;
  s32 v40;
  bool v41;
  f32 v42;
  SBATTLE_WORK *v44;
  SBTLSKILLP_TBL *v46;
  s32 sword_eff_skl;
  s32 v48;
  SBTLSKILLP_TBL *v50;
  SBTLSKILLP_TBL *v52;
  s32 updated;
  s32 devilid;
  s64 bunriid;
  f32 v58;
  f32 v59;
  s32 v60;
  s64 v61;
  f32 v62;
  u32 flg2;
  char v64;
  s32 max_damage;
  f32 v66;
  f32 v68;
  s32 hp;
  f32 v72;
  s32 v73;
  bool *v75;
  bool *v76;
  u32 v77;
  s32 x;

  Skilltbl = sBtlGetSkilltbl(skillid);
  if (Skilltbl)
  {
    v75 = a_pbCritical;
    v18 = Skilltbl;
    v77 = attr;
    v19 = hwk;
    v20 = wklock;
    v21 = datCheckSkillPhysicDamage(skillid);
    datCheckSkillMagicDamage(skillid);
    datCheckSkillGunDamage(skillid);
    para = wk->para;
    sBtlGetBadStatus(wk->para);
    flg = v18->flg;
    if ((flg & 1) == 0)
    {
      v25 = v21;
      goto LABEL_38;
    }
    v25 = v21;
    if ((flg & 0x200000) != 0 || damage < 1)
      goto LABEL_38;
    if (!v20)
    {
LABEL_27:
      v29 = wk->para;
      if (sBtlGetBadStatus(wk->para) == 9)
      {
        v30 = (f32)damage + (f32)damage;
        goto LABEL_35;
      }
      v31 = wk->para;
      if (sBtlIsKoufun(v31))
      {
        v30 = (f32)damage * 0.6;
LABEL_35:
        if (v30 == INFINITY)
          damage = 0x80000000;
        else
          damage = v30;
      }
LABEL_38:
      v76 = a_pbGuard;
      if ((v18->flg & 0x200001) != 1)
      {
        v36 = v75;
        v32 = v20;
        if ((wk->para->badstatus & 0x1000) == 0)
          goto LABEL_52;
        goto LABEL_66;
      }
      v32 = v20;
      if ((v18->flg2 & 0x80) != 0)
      {
        v36 = v75;
        if ((wk->para->badstatus & 0x1000) == 0)
          goto LABEL_52;
        goto LABEL_66;
      }
      if (damage < 1)
      {
        v36 = v75;
        if ((wk->para->badstatus & 0x1000) == 0)
          goto LABEL_52;
        goto LABEL_66;
      }
      if (v20)
      {
        v33 = v20->para;
        if (sBtlChkHaveMemSkl(v33, 60))
        {
          v34 = (f32)damage + (f32)damage;
          if (v34 == INFINITY)
            damage = 0x80000000;
          else
            damage = v34;
          x = damage;
        }
      }
      v35 = wk->para;
      v36 = v75;
      if (!sBtlChkHaveMemSkl(wk->para, 60))
        goto LABEL_51;
      goto LABEL_9000;
      if (!sBtlChkHaveMemSkl(v35, 60))
      {
LABEL_51:
        if ((wk->para->badstatus & 0x1000) == 0)
          goto LABEL_52;
        goto LABEL_66;
      }
LABEL_9000:
      v59 = (f32)damage * 1.5;
      if (v59 == INFINITY)
        damage = 0x80000000;
      else
        damage = v59;
      if ((wk->para->badstatus & 0x1000) == 0)
      {
LABEL_52:
        if (wk->actwk->status == 9 && (wk->hstatus & 0x10) != 0)
        {
          if ((v25 & 1) != 0 && (v18->flg2 & 0x10) != 0)
          {
            v37 = (f32)damage * 1.5;
            if (v37 == INFINITY)
              damage = 0x80000000;
            else
              damage = v37;
          }
          SpiritSkillChk = sBtlGetSpiritSkillChk(1449);
          if (!v32 || !SpiritSkillChk || (v32->side & 1) == 0)
          {
LABEL_72:
            goto LABEL_73;
          }
          v39 = (f32)damage * 1.2;
          v40 = v39;
          v41 = v39 == INFINITY;
LABEL_68:
          if (v41)
            damage = 0x80000000;
          else
            damage = v40;
          x = damage;
          goto LABEL_72;
        }
        goto LABEL_75;
      }
LABEL_66:
      if ((v25 & 1) != 0)
      {
        v25 = 1;
        v42 = (f32)damage * 1.5;
        v41 = v42 == INFINITY;
        v40 = v42;
        goto LABEL_68;
      }
LABEL_75:
      v25 = 0;
LABEL_73:
      v44 = wk;
      if (v44->sword_eff_step)
      {
        v44 = wk;
        if (v44->sword_eff_skl && sBtlGetPChara() && (v18->flg2 & 0x10) != 0)
        {
          sBtlGetSkilltbl(wk->sword_eff_skl)->max_damage = 9999;
          v46 = sBtlGetSkilltbl(wk->sword_eff_skl);
          v46->flg |= 1u;
          sword_eff_skl = wk->sword_eff_skl;
          v48 = sBtlGetDamage(v32, wk, v19, sword_eff_skl, v77, 0) + damage;
          damage = v48 & ~(v48 >> 31);
          x = damage;
          v50 = sBtlGetSkilltbl(wk->sword_eff_skl);
          v50->max_damage = 0;
          v52 = sBtlGetSkilltbl(wk->sword_eff_skl);
          v52->flg &= ~1u;
        }
      }
      updated = sBtlUpdateDamageKaja(v32, wk, skillid, damage);
      x = updated;
      if ((wk->status3 & 0x80) == 0)
        goto LABEL_136;
      if (!v32)
        goto LABEL_123;
      if (!CheckLiveTarget(v32))
        goto LABEL_123;
      if ((v32->side & 0x81) == 1)
      {
        devilid = v32->para->devilid;
        bunriid = sBtlGetDevilData(devilid, -1)->bunriid;
        if (bunriid == wk->status3_param)
        {
          if ((v18->flg & 1) == 0)
          {
            if ((wk->side & 0x81) != 1)
              goto LABEL_136;
            goto LABEL_124;
          }
          if (updated != -1)
          {
            v58 = (f32)updated * 1.5;
            if (v58 == INFINITY)
              updated = 0x80000000;
            else
              updated = v58;
            x = updated;
            if ((wk->side & 0x81) != 1)
              goto LABEL_136;
            goto LABEL_124;
          }
        }
      }
LABEL_123:
      if ((wk->side & 0x81) != 1)
        goto LABEL_136;
LABEL_124:
      v60 = wk->para->devilid;
      v61 = sBtlGetDevilData(v60, -1)->bunriid;
      if (v61 != wk->status3_param)
        goto LABEL_136;
      if ((v18->flg & 1) != 0 && updated != -1)
      {
        v62 = (f32)updated * 0.5;
        if (v62 == INFINITY)
          updated = 0x80000000;
        else
          updated = v62;
        x = updated;
      }
LABEL_136:
      flg2 = v18->flg2;
      if ((flg2 & 0x1020000) != 0)
      {
LABEL_137:
        v64 = 0;
        goto LABEL_138;
      }
      v64 = 0;
      if (v77 == 0x2000 || (v18->flg & 1) == 0 || updated == -1)
      {
LABEL_138:
        max_damage = v18->max_damage;
        LimitRange(&x, 0, max_damage);
        if (x)
        {
          if (x >= 9999)
            LODWORD(Skilltbl) = 9999;
          else
            LODWORD(Skilltbl) = x;
          goto LABEL_168;
        }
        if (!!sBtlGetSpiritSkillChk(1384))
        {
          if (sBtlGetSpiritSkillChk(1385))
          {
            LODWORD(Skilltbl) = 0;
            goto LABEL_168;
          }
        }
        LODWORD(Skilltbl) = 1;
LABEL_168:
        if (v19->skillid == 1247)
        {
          hp = wk->para->now->hp;
          if (hp > (s32)Skilltbl)
            LODWORD(Skilltbl) = hp - 1;
        }
        *v76 = v64;
        *v36 = v25 & 1;
        return (s32)Skilltbl;
      }
      if ((wk->status & 0x100) == 0)
        goto LABEL_137;
      if ((flg2 & 0x80) != 0)
      {
        v66 = updated;
        if ((wk->side & 0x80) == 0)
          goto LABEL_177;
        if (wk->battlemode == 3)
        {
LABEL_177:
          v68 = 0.5;
          goto LABEL_178;
        }
      }
      else
      {
        if ((v19->attr_flg & 0x300) != 0)
          goto LABEL_137;
        v66 = updated;
        if ((wk->side & 0x80) == 0)
          goto LABEL_154;
        if (wk->battlemode == 3)
        {
LABEL_154:
          v68 = 0.1;
LABEL_178:
          v72 = v66 * v68;
LABEL_182:
          v73 = v72;
          v64 = 1;
          if (v72 == INFINITY)
            v73 = 0x80000000;
          x = v73;
          goto LABEL_138;
        }
      }
      v72 = RD_SkillDamageChack((s32)v66);
      goto LABEL_182;
    }
    v26 = v20->para;
    if (sBtlGetBadStatus(v20->para) != 9)
      goto LABEL_19;
    if ((v18->flg2 & 0x80) == 0)
    {
      v27 = (f32)damage * 1.5;
LABEL_23:
      if (v27 == INFINITY)
        damage = 0x80000000;
      else
        damage = v27;
      x = damage;
      goto LABEL_27;
    }
LABEL_19:
    v28 = v20->para;
    if (!sBtlIsKoufun(v28))
      goto LABEL_27;
    v27 = (f32)damage + (f32)damage;
    goto LABEL_23;
  }
  return (s32)Skilltbl;
}

// 0x2056440
s32 sBtlGetCalcDamage(SBTLUNIT_WORK *wk, SKLID skillid, s32 acterID, SBTLDMG_HITWORK *hwk, s32 attr) {
  SBATTLE_WORK *v12;
  u32 status4;
  s32 Damage;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v16;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v19;
  bool a_pbCritical;
  bool a_pbGuard;

  v12 = wk;
  status4 = v12->status4;
  if ((status4 & 0x4000) != 0)
    return 0;
  v12 = wk;
  status4 = v12->status4;
  Damage = 0;
  if (!wk || (status4 & 0x10000) != 0)
    return Damage;
  if (v12->bTateNoDmg)
    return 0;
  Skilltbl = sBtlGetSkilltbl(skillid);
  if (!Skilltbl)
    return 0;
  v16 = Skilltbl;
  if ((wk->flg & 0x10) != 0 && (Skilltbl->flg & 1) != 0)
    return 0;
  if ((Skilltbl->type & 0xFFF) == 0)
  {
    Damage = 0;
    v19 = 0;
    if ((Skilltbl->flg & 1) == 0)
      return Damage;
    goto LABEL_42;
  }
  UnitMng = wk->UnitMng;
  v19 = sBtlSearchUnit_ID(UnitMng, acterID);
  if (!v19)
  {
    Damage = 0;
    if ((v16->flg & 1) == 0)
      return Damage;
    goto LABEL_42;
  }
  Damage = sBtlGetDamage(v19, wk, hwk, skillid, attr, 0);
  if (!sbtlplayertblChkPlayerMagSkill(skillid))
  {
    if ((v16->flg & 1) == 0)
      return Damage;
    goto LABEL_42;
  }
  if (wk->raido_magwaza_costnot)
    Damage = 1;
  if ((v16->flg & 1) != 0)
  {
LABEL_42:
    return sBtlGetCalcDamageEx(v19, wk, hwk, skillid, attr, Damage, &a_pbGuard, &a_pbCritical);
  }
  return Damage;
}

// 0x204f280
bool sBtlSetReflectDamage(SBTLUNIT_WORK *target, SBTLDMG_HITWORK *hwk) {
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v8;
  SBTLUNIT_WORK *v9;
  SBTLUNIT_WORK *v13;
  s32 skillid;
  _BOOL4 v15;
  _BOOL4 v16;
  s32 v18;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  s32 v29;
  s32 aListID;
  s32 CalcDamage;
  SBTLSKILLP_TBL *Skilltbl;
  u32 attr;
  u32 v35;
  u32 v38;
  s32 v39;
  s32 v40;
  _BOOL4 v41;
  s32 para;
  s32 v43;
  u32 v45;
  s32 hp;
  s32 v48;
  SBTLUNIT_WORK *v49;
  s32 v53;
  f32 a_pRate;
  bool a_pbDamage;
  s32 a_pHanshaType;
  sdfVector4_t v60;
  sdfVector4_t v61;

  a_pbDamage = 0;
  a_pRate = 0.0;
  a_pHanshaType = 0;
  acterID = hwk->acterID;
  UnitMng = wk->UnitMng;
  v8 = sBtlSearchUnit_ID(UnitMng, acterID);
  if (!v8)
    return (char)v8;
  v9 = v8;
  if (target)
  {
    if (wk->enemy_zenmetu && (target->side & 0x81) != 0)
      goto LABEL_16;
  }
  if (sBtlCheckPlayerDead())
  {
LABEL_16:
    LOBYTE(v8) = 0;
    return (char)v8;
  }
  v13 = v9;
  if ((v9->status & 0x800) != 0)
  {
    skillid = hwk->skillid;
    v13 = sBtlCheckALLSkill(v9, skillid);
  }
  v15 = CheckLiveTarget(v13);
  v16 = sBtlCheckDamageTarget(v13);
  v18 = sBtlCheckDamageTargetTemp(v13) && v16 && v15;
  if ((v13->flg & 2) != 0)
    LOBYTE(v18) = ((v13->side & 2) == 0) & v18;
  if ((v18 & 1) != 0)
  {
    x = v13->pos.x;
    y = v13->pos.y;
    z = v13->pos.z;
    w = v13->pos.w;
    v60.x = x;
    v60.y = y;
    v60.z = z;
    v60.w = w;
    sBtlCheckYukaDamageEffect(v13, 149, 1u, 0, 0, v60, 0);
    sBtlCreateSTP_Unit(wk->stpList, target, 6, 0, 0, 0);
    v24 = target->pos.x;
    v25 = target->pos.y;
    v27 = target->pos.z;
    v26 = target->pos.w;
    v61.x = v24;
    v61.y = v25;
    v61.z = v27;
    v61.w = v26;
    sBtlPlayDamageSE(v61, 4);
    v29 = hwk->skillid;
    if (hwk->BEDtype == 2)
    {
      aListID = hwk->awk->aListID;
      goto LABEL_45;
    }
    else
    {
      aListID = hwk->acterID;
      goto LABEL_45;
    }
LABEL_45:
    CalcDamage = sBtlGetCalcDamage(target, v29, aListID, hwk, 0);
    Skilltbl = sBtlGetSkilltbl(hwk->skillid);
    attr = Skilltbl->attr;
    v35 = sBtlCheckAisyoEx(v13, attr, &a_pHanshaType);
    if ((v35 & 0x2000) == 0)
    {
      v38 = v35;
      if ((v35 & 0x1000) != 0)
      {
        sBtlSetInvalidDamage(v13);
      }
      else
      {
        v39 = (v35 >> 19) & 1;
        v40 = CalcDamage >> v39;
        if ((v38 & 0x4000) != 0)
        {
          v43 = hwk->skillid;
          v41 = v43 == 149 || (u32)(v43 - 164) < 3;
        }
        else
        {
          v41 = 0;
        }
        if (v41 | ((u16)(hwk->area & 0x400) >> 10))
          v45 = v38 & 0xFFFFBFFF;
        else
          v45 = v38;
        if ((Skilltbl->type & 0x1000) != 0)
        {
          hp = v13->para->now->hp;
          if (v40 >= hp)
            v40 = hp - 1;
        }
        v48 = sBtlCheckKuishibari(v13, v40);
        sBtlDecHp(v13, v48, 0);
        if ((v13->status & 0x40000000) != 0)
        {
          v53 = hwk->skillid;
          sBtlCreateAnim_Unit(v13, v49, v48, 0, 0, v53);
          sBtlSetSpecialDamage_DamageOnly(v13);
          HukaEffect(v13, v9, hwk);
        }
        else
        {
          a_pbDamage = 0;
          a_pRate = 0.0;
          if (!sBtlSetDeadDamageEx(v13, v9, hwk, v48, v45, &a_pbDamage, &a_pRate))
          {
            sBtlSetDamageProc(v13, v9, hwk, v48, v45);
          }
        }
      }
LABEL_85:
      LOBYTE(v8) = 1;
      return (char)v8;
    }
    para = Skilltbl->para;
    sBtlSetAbsorbDamage(v13, CalcDamage, para);
    goto LABEL_85;
  }
  sBtlSetInvalidDamage(target);
  LOBYTE(v8) = 0;
  return (char)v8;
}

// 0x2056720
static void HukaEffect(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, SBTLDMG_HITWORK *hwk) {
  s16 StartTime_Damage;
  s32 skillid;
  s32 acterside;
  s32 serialID2;
  SBTLUNIT_WORK *v11;
  s32 v12;
  SBTLDMG_HITWORK *p_huka2hwk;
  s32 v15;
  s32 v16;
  s32 v17;

  StartTime_Damage = sBtlGetStartTime_Damage();
  if ((sBtlGetSklVisualTbl(hwk->skillid)->flg & 0x200) == 0 && (hwk->type & 0xFFFu) <= 0xF && ((1 << LOBYTE(hwk->type)) & 0xFE3E) != 0)
  {
    if (wklock->damage_fuka_tgt_cnt)
    {
      skillid = hwk->skillid;
      acterside = hwk->acterside;
      serialID2 = hwk->serialID2;
      v11 = wklock;
      v12 = skillid;
LABEL_28:
      sBtlCheckEffectData_SeOnly(v11, v12, 2u, 0, acterside, serialID2, StartTime_Damage);
      return;
    }
    p_huka2hwk = &wk->huka2hwk;
    p_huka2hwk = hwk;
    if (wk->encountno == 50 && (wk->side & 0x80) != 0)
    {
      v15 = hwk->skillid;
      if (v15 != 151)
      {
        if (v15 == 451)
        {
LABEL_20:
          wklock->damage_fuka_tgt_cnt = 15;
          return;
        }
LABEL_17:
        v16 = hwk->acterside;
        v17 = hwk->serialID2;
        sBtlCheckEffectData(wklock, v15, 2u, 0, v16, v17, StartTime_Damage);
        goto LABEL_20;
      }
    }
    else
    {
      v15 = hwk->skillid;
      if (v15 != 151)
        goto LABEL_17;
    }
    acterside = hwk->acterside;
    serialID2 = hwk->serialID2;
    v12 = 151;
    v11 = wklock;
    goto LABEL_28;
  }
}

// 0x20518b0
static bool IsKabeOrKudan(SBTLUNIT_WORK *wklock) {
  s32 devilid;
  bool result;

  result = false;
  if (wklock)
  {
    devilid = wklock->para->devilid;
    if (devilid == 145 || (u32)(devilid - 188) < 0x19)
      return true;
  }
  return result;
}

// 0x2051920
s32 GetDamage(SBTLUNIT_WORK *wk, SKLID skillid, s32 acterID, SBTLDMG_HITWORK *hwk, s32 attr, bool _SE_PLAY) {
  s32 v13;
  SBTLSKILLP_TBL *Skilltbl;
  SBATTLE_WORK *v17;
  u32 status4;
  s32 v20;
  SBTLSKILLP_TBL *v21;
  _BOOL4 v22;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v25;
  s32 Damage;
  sdatUnitWork_t *para;
  sdatUnitWork_t *v31;
  f32 v32;
  u32 v33;
  u32 v34;
  s32 v35;
  sdatUnitWork_t *v36;
  u32 flg;
  sdatUnitWork_t *v39;
  f32 v40;
  f32 v41;
  sdatUnitWork_t *v42;
  f32 v43;
  sdatUnitWork_t *v44;
  f32 v45;
  sdatUnitWork_t *v46;
  sdatUnitWork_t *v47;
  f32 v48;
  sdatUnitWork_t *v49;
  f32 v50;
  s32 side;
  f32 v53;
  SBTLSKILLP_TBL *v54;
  s32 Mag;
  u32 v57;
  s32 v59;
  s32 v60;
  signed s16 Percentage;
  f32 v62;
  s32 v63;
  SBATTLE_WORK *v65;
  SBTLSKILLP_TBL *v67;
  s32 sword_eff_skl;
  s32 v69;
  SBTLSKILLP_TBL *v71;
  SBTLSKILLP_TBL *v73;
  u32 v74;
  s32 v75;
  u32 v76;
  SBTLUNIT_WORK *PChara;
  sdatUnitWork_t *v78;
  s32 HaveMemSkl;
  sdatUnitWork_t *v80;
  bool v81;
  s32 v82;
  bool v83;
  f32 v84;
  s32 v85;
  f32 v86;
  s32 v87;
  bool IsDamageCorrection;
  s32 v89;
  signed s16 v90;
  f32 v92;
  f32 v93;
  f32 v94;
  f32 v95;
  f32 per;
  f32 Radian;
  f32 v100;
  s32 v101;
  s32 v102;
  s32 updated;
  SBTLUNIT_LISTWORK *v105;
  SBTLUNIT_WORK *v106;
  SBTLUNIT_WORK *v108;
  s32 battlemode;
  s32 vice;
  s32 v113;
  s32 v114;
  SBATTLE_WORK *v116;
  SBTLUNIT_LISTWORK *v117;
  SBTLUNIT_WORK *v119;
  SBTLUNIT_WORK *v120;
  s32 v121;
  s64 bunriid;
  f32 v124;
  s32 v125;
  s64 v126;
  f32 v128;
  s32 v129;
  s32 max_damage;
  f32 v131;
  f32 v133;
  s32 hp;
  SBTLUNIT_LISTWORK *v137;
  SBTLUNIT_WORK *v138;
  SBTLUNIT_WORK *v139;
  sdatUnitWork_t *v140;
  s32 AutoSkill_ID;
  sdatUnitWork_t *v142;
  s32 v143;
  sdatUnitWork_t *v144;
  s32 v145;
  sdatUnitWork_t *v146;
  s32 v147;
  sdatUnitWork_t *v148;
  s32 v149;
  sdatUnitWork_t *v150;
  s32 v151;
  sdatUnitWork_t *v152;
  s32 v153;
  sdatUnitWork_t *v154;
  s32 v155;
  sdatUnitWork_t *v156;
  u32 BadStatus;
  bool v158;
  sdatUnitWork_t *v159;
  sdatUnitWork_t *v160;
  s32 v161;
  s32 autost_cnt;
  s32 autost_cnt2;
  s32 v164;
  s32 v165;
  s32 v167;
  f32 v168;
  f32 y;
  f32 w;
  f32 z;
  SBTLUNIT_WORK *v172;
  s32 v176;
  f32 v178;
  s32 v179;
  s32 v180;
  u32 v181;
  f32 v182;
  f32 v183;
  f32 v184;
  s32 devilid;
  s32 v187;
  u32 v190;
  u32 v191;
  s32 v192;
  u32 v193;
  f32 v194;
  f32 v195;
  f32 v196;
  s32 v197;
  f32 v198;
  s32 v199;
  s32 v200;
  bool v201;
  s32 retpara;
  s32 retparaa;
  _BOOL4 v204;
  SBTLSKILLP_TBL *v205;
  SBTLUNIT_WORK *acter;
  s32 x;
  sdfVector4_t v208;
  sdfVector4_t v209;
  sdfVector4_t v210;
  sdfVector4_t v211;
  sdfVector4_t v212;
  sdfVector4_t v213;

  v13 = hwk->skillid;
  x = 0;
  Skilltbl = sBtlGetSkilltbl(v13);
  v17 = wk;
  status4 = wk->status4;
  if ((status4 & 0x4000) != 0)
    return 0;
  v20 = 0;
  if (!wk)
    return v20;
  if ((status4 & 0x10000) != 0)
    return v20;
  if (wk->bTateNoDmg)
    return 0;
  v21 = sBtlGetSkilltbl(skillid);
  v22 = datCheckSkillPhysicDamage(skillid);
  datCheckSkillMagicDamage(skillid);
  v204 = datCheckSkillGunDamage(skillid);
  if ((wk->flg & 0x10) != 0 && (v21->flg & 1) != 0 || (v21->s_type & 8) != 0 && (v21->attr & 0x400) != 0)
  {
    return 0;
  }
  v201 = SE_PLAY;
  UnitMng = wk->UnitMng;
  v25 = sBtlSearchUnit_ID(UnitMng, acterID);
  Damage = 0;
  acter = v25;
  if ((v21->type & 0xFFF) != 0 && v25)
  {
    Damage = sBtlGetDamage(acter, wk, hwk, skillid, attr, 0);
    x = Damage;
    if (sbtlplayertblChkPlayerMagSkill(skillid))
    {
      if (wk->raido_magwaza_costnot)
      {
        Damage = 1;
        x = 1;
      }
    }
  }
  v205 = v21;
  para = wk->para;
  if (sBtlGetBadStatus(para) != 6 || !v22 && !v204)
    goto LABEL_60;
  v31 = wk->para;
  v32 = (f32)(10 - v31->now->luck) * 0.7;
  v33 = (s32)v32 + 25;
  v34 = v33 >> 1;
  if (v32 == INFINITY)
  {
    LOWORD(v34) = 12;
    LOWORD(v33) = 25;
  }
  if ((wk->side & 2) != 0)
    LOWORD(v35) = v33;
  else
    LOWORD(v35) = v34;
  if (sBtlChkHaveMemSkl(v31, 52))
    LOWORD(v35) = 0;
  v36 = wk->para;
  if (sBtlChkHaveMemSkl(v36, 28))
    v35 = wk->para->autost_cnt2 * (s16)v35 / 100;
  if ((s16)GetPercentage() >= (s16)v35)
  {
LABEL_60:
    flg = v205->flg;
    if ((flg & 1) == 0 || (flg & 0x200000) != 0 || Damage < 1)
      goto LABEL_92;
    if (!acter)
    {
LABEL_80:
      v44 = wk->para;
      if (sBtlGetBadStatus(v44) == 9)
      {
        v45 = (f32)Damage + (f32)Damage;
      }
      else
      {
        v46 = wk->para;
        if (!sBtlIsKoufun(v46))
          goto LABEL_92;
        v45 = (f32)Damage * 0.6;
      }
      if (v45 == INFINITY)
        Damage = 0x80000000;
      else
        Damage = v45;
      x = Damage;
LABEL_92:
      if ((v205->flg & 0x200001) == 1 && (v205->flg2 & 0x80) == 0 && Damage >= 1)
      {
        if (acter)
        {
          v47 = acter->para;
          if (sBtlChkHaveMemSkl(v47, 60))
          {
            v48 = (f32)Damage + (f32)Damage;
            if (v48 == INFINITY)
              Damage = 0x80000000;
            else
              Damage = v48;
            x = Damage;
          }
        }
        v49 = wk->para;
        if (sBtlChkHaveMemSkl(v49, 60))
        {
          v50 = (f32)Damage * 1.5;
          if (v50 == INFINITY)
            Damage = 0x80000000;
          else
            Damage = v50;
          x = Damage;
        }
      }
      if (wk->battlemode != 3)
      {
        if (sBtlGetSpiritSkillChk(1450) && (v205->flg & 0x200001) == 1 && skillid != 149 && (v205->flg2 & 0x80) == 0 && Damage >= 1 && acter)
        {
          side = acter->side;
          if ((side & 0x81) == 1)
          {
            v53 = (f32)Damage * 2.5;
            if (v53 == INFINITY)
              Damage = 0x80000000;
            else
              Damage = v53;
            x = Damage;
          }
LABEL_128:
          v54 = v205;
          if ((side & 2) != 0)
            goto LABEL_133;
          if (wk->bTateNoDmg || (wk->side & 2) == 0)
          {
LABEL_133:
            Mag = 0;
          }
          else if (sBtlGetPChara() && ((v205->flg2 & 0x10) != 0 || (u32)(skillid - 1296) < 2 || skillid == 674))
          {
            PChara = sBtlGetPChara();
            Mag = sbtlplayertblPlayerSkill_GetMag(PChara, skillid, wk);
          }
          else
          {
            Mag = (skillid == 149) & acter->side;
          }
          v199 = Mag;
          if ((wk->para->badstatus & 0x1000) == 0 || Damage == -1)
          {
            retpara = Damage;
            if (wk->actwk->status == 9 && (wk->hstatus & 0x10) != 0)
            {
              v76 = v205->flg;
              if ((v76 & 1) != 0)
              {
                v60 = 0;
                if ((v76 & 0x200000) == 0 && retpara != -1)
                {
                  v54 = v205;
                  v60 = 1;
                  retpara = SetCritical(wk, retpara, WEAK_CRITICAL_RAITO);
                }
              }
              else
              {
                v60 = 0;
              }
              if (sBtlGetSpiritSkillChk(1449) && (acter->side & 0x80) != 0)
              {
                v100 = (f32)retpara * 1.2;
                v101 = v100;
                if (v100 == INFINITY)
                  v101 = 0x80000000;
                retpara = v101;
                x = v101;
              }
            }
            else
            {
              v60 = 0;
            }
          }
          else
          {
            v57 = v205->flg;
            if ((v205->attr & 0x401) != 0)
            {
              if ((v57 & 0x200000) != 0)
              {
                retpara = Damage;
                v60 = 0;
              }
              else
              {
                v59 = SetCritical(wk, Damage, NOMARL_CRITICAL_RAITO);
                v54 = v205;
                v60 = 1;
                retpara = v59;
                x = v59;
              }
            }
            else
            {
              retpara = Damage;
              v60 = 0;
              if ((v57 & 1) == 0)
                goto LABEL_155;
            }
            Percentage = GetPercentage();
            v62 = (f32)((f32)(13 - wk->para->now->luck) * -0.7) + 80.0;
            if ((wk->side & 2) != 0)
              v62 = v62 * 0.81;
            v63 = v62;
            if (v62 == INFINITY)
              v63 = 0;
            if (v63 > Percentage)
            {
              sBtlResetBadStatus(wk, 4096);
            }
          }
LABEL_155:
          v65 = wk;
          if (v65->sword_eff_step)
          {
            v65 = wk;
            if (v65->sword_eff_skl && sBtlGetPChara() && (v54->flg2 & 0x10) != 0)
            {
              sBtlGetSkilltbl(wk->sword_eff_skl)->max_damage = 9999;
              v67 = sBtlGetSkilltbl(wk->sword_eff_skl);
              v67->flg |= 1u;
              sword_eff_skl = wk->sword_eff_skl;
              v69 = retpara + sBtlGetDamage(acter, wk, hwk, sword_eff_skl, attr, 0);
              retpara = v69 & ~(v69 >> 31);
              x = retpara;
              v71 = sBtlGetSkilltbl(wk->sword_eff_skl);
              v71->max_damage = 0;
              v73 = sBtlGetSkilltbl(wk->sword_eff_skl);
              v73->flg &= ~1u;
            }
          }
          v74 = v54->flg;
          if ((v74 & 1) == 0)
          {
            v75 = 0;
            goto LABEL_215;
          }
          v75 = 0;
          if ((v74 & 0x200000) != 0 || retpara == -1)
            goto LABEL_215;
          if (v60)
          {
            v75 = 0;
          }
          else
          {
            v78 = acter->para;
            HaveMemSkl = sBtlChkHaveMemSkl(v78, 91);
            v80 = acter->para;
            if (HaveMemSkl)
              v81 = skillid == 149;
            else
              v81 = 0;
            if (v81)
              v82 = 30;
            else
              v82 = 0;
            v197 = v82;
            v54 = v205;
            v83 = sBtlChkHaveMemSkl(v80, 90) && skillid == 149;
            v75 = v83 ? 15 : v197;
          }
          if ((u32)(skillid - 690) > 0xB || ((1 << (skillid + 78)) & 0xA67) == 0)
          {
LABEL_215:
            if ((v54->flg & 1) == 0)
              goto LABEL_260;
            IsDamageCorrection = sBtlIsDamageCorrection(wk);
            if (skillid == 72 || !IsDamageCorrection)
            {
LABEL_260:
              v200 = v60;
              updated = sBtlUpdateDamageKaja(acter, wk, skillid, retpara);
              x = updated;
              v105 = wk->UnitMng;
              v106 = sBtlSearchUnit_ID(v105, acterID);
              if (v106)
              {
                v108 = v106;
                if (CheckLiveTarget(v108))
                {
                  battlemode = (u16)wk->battlemode;
                  if (battlemode == 3 && (v108->side & 1) != 0)
                    goto LABEL_278;
                  battlemode = (u16)wk->battlemode;
                  if (battlemode != 3 && (v108->side & 0x81) == 1)
                  {
LABEL_278:
                    vice = v108->para->vice;
                    if (sBtlGetViceLevel(vice) >= 2 && (v54->flg & 1) != 0 && updated != -1)
                    {
                      updated = (f32)updated;
                      x = updated;
                    }
                  }
                }
              }
              v113 = (u16)wk->battlemode;
              if (v113 == 3 && (wk->side & 1) != 0)
                goto LABEL_289;
              v113 = (u16)wk->battlemode;
              if (v113 != 3 && (wk->side & 0x81) == 1)
              {
LABEL_289:
                v114 = wk->para->vice;
                if (sBtlGetViceLevel(v114) >= 2 && (v54->flg & 1) != 0 && updated != -1)
                {
                  updated = (f32)updated;
                  x = updated;
                }
              }
              v116 = wk;
              if ((v116->status3 & 0x80) == 0)
              {
LABEL_333:
                if ((Skilltbl->flg2 & 0x1020000) != 0)
                {
LABEL_334:
                  v129 = 0;
                  goto LABEL_335;
                }
                v129 = 0;
                if (attr == 0x2000 || (v54->flg & 1) == 0 || updated == -1)
                {
LABEL_335:
                  max_damage = v54->max_damage;
                  LimitRange(&x, -1, max_damage);
                  if ((v54->flg & 1) != 0)
                  {
                    if (x)
                    {
                      if (x >= 9999)
                        x = 9999;
                    }
                    else
                    {
                      x = !RD_SkillChack();
                    }
                  }
                  if (hwk->skillid == 1247)
                  {
                    hp = wk->para->now->hp;
                    if (hp > x)
                      x = hp - 1;
                  }
                  if ((v54->flg & 1) == 0)
                    goto LABEL_469;
                  v137 = wk->UnitMng;
                  v138 = sBtlSearchUnit_ID(v137, acterID);
                  if (!v138)
                    goto LABEL_469;
                  v139 = v138;
                  if (sBtlCheckDamageTarget(v139))
                  {
                    if (sBtlCheckDamageTargetTemp(v139) && wk->para->now->hp - x >= 2)
                    {
                      if (!sBtlCheckSpecialDamage_Stop(v139))
                      {
                        v140 = wk->para;
                        AutoSkill_ID = sBtlGetAutoSkill_ID(v140, 0);
                        if (sBtlGetAutoSkillPara(AutoSkill_ID, &wk->para->autost_cnt, &wk->para->autost_cnt2) == 4)
                        {
                          if (sBtlCheckAutoSkill_TargetDamage(4))
                            goto LABEL_431;
                        }
                        v142 = wk->para;
                        v143 = sBtlGetAutoSkill_ID(v142, 1);
                        if (sBtlGetAutoSkillPara(v143, &wk->para->autost_cnt, &wk->para->autost_cnt2) == 4)
                        {
                          if (sBtlCheckAutoSkill_TargetDamage(4))
                            goto LABEL_431;
                        }
                        v144 = wk->para;
                        v145 = sBtlGetAutoSkill_ID(v144, 2);
                        if (sBtlGetAutoSkillPara(v145, &wk->para->autost_cnt, &wk->para->autost_cnt2) == 4)
                        {
                          if (sBtlCheckAutoSkill_TargetDamage(4))
                            goto LABEL_431;
                        }
                        v146 = wk->para;
                        v147 = sBtlGetAutoSkill_ID(v146, 3);
                        if (sBtlGetAutoSkillPara(v147, &wk->para->autost_cnt, &wk->para->autost_cnt2) == 4)
                        {
                          if (sBtlCheckAutoSkill_TargetDamage(4))
                            goto LABEL_431;
                        }
                        v148 = wk->para;
                        v149 = sBtlGetAutoSkill_ID(v148, 4);
                        if (sBtlGetAutoSkillPara(v149, &wk->para->autost_cnt, &wk->para->autost_cnt2) == 4)
                        {
                          if (sBtlCheckAutoSkill_TargetDamage(4))
                            goto LABEL_431;
                        }
                        v150 = wk->para;
                        v151 = sBtlGetAutoSkill_ID(v150, 5);
                        if (sBtlGetAutoSkillPara(v151, &wk->para->autost_cnt, &wk->para->autost_cnt2) == 4)
                        {
                          v54 = v205;
                          if (sBtlCheckAutoSkill_TargetDamage(4))
                            goto LABEL_431;
                        }
                        v152 = wk->para;
                        v153 = sBtlGetAutoSkill_ID(v152, 6);
                        if (sBtlGetAutoSkillPara(v153, &wk->para->autost_cnt, &wk->para->autost_cnt2) == 4)
                        {
                          v54 = v205;
                          if (sBtlCheckAutoSkill_TargetDamage(4))
                            goto LABEL_431;
                        }
                        v154 = wk->para;
                        v155 = sBtlGetAutoSkill_ID(v154, 7);
                        if (sBtlGetAutoSkillPara(v155, &wk->para->autost_cnt, &wk->para->autost_cnt2) == 4)
                        {
                          v54 = v205;
                          if (sBtlCheckAutoSkill_TargetDamage(4))
                          {
LABEL_431:
                            v156 = wk->para;
                            BadStatus = sBtlGetBadStatus(v156);
                            if (BadStatus <= 0x16 && ((1 << BadStatus) & 0x600E00) != 0 && (s16)GetPercentage() <= 79)
                            {
                              v158 = sBtlCheckAutoSkill_Action(wk, hwk, attr);
                              if (!v200 && v158)
                              {
                                v159 = wk->para;
                                retparaa = attr;
                                v160 = v139->para;
                                v161 = x;
                                autost_cnt = v159->autost_cnt;
                                autost_cnt2 = v159->autost_cnt2;
                                v164 = CalcAutoSkill(v160, 4, v161, skillid, autost_cnt, autost_cnt2);
                                if (v164 <= 1)
                                  v165 = 1;
                                else
                                  v165 = v164;
                                v167 = sBtlCheckKuishibari(v139, v165);
                                sBtlDecHp(v139, v167, 0);
                                v168 = v139->pos.x;
                                y = v139->pos.y;
                                z = v139->pos.z;
                                w = v139->pos.w;
                                v210.x = v168;
                                v210.y = y;
                                v210.z = z;
                                v210.w = w;
                                sBtlCheckYukaDamageEffect(v139, 149, 1u, 0, 0, v210, 0);
                                sBtlCreateAnim_Unit(v139, v172, v167, 0, 0, 0);
                                if ((v139->status & 0x40000000) != 0)
                                {
                                  sBtlSetSpecialDamage_DamageOnly(v139);
                                  goto LABEL_468;
                                }
                                v54 = v205;
                                attr = retparaa;
                                if (v139->para->now->hp <= 0)
                                {
                                  v176 = hwk->skillid;
                                  sBtlSetDeadDamage(v139, 0, v176);
LABEL_468:
                                  v54 = v205;
                                  attr = retparaa;
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
LABEL_469:
                  if (attr != 0x2000 && (v54->flg & 1) != 0)
                  {
                    v180 = x;
                    x = sBtlCheckKuishibari(wk, v180);
                  }
                  if (!v201)
                    return x;
                  v181 = v54->flg;
                  if ((v181 & 0x400204) != 0 || attr == 0x2000 || attr == 4096 || ((v129 | ((v181 & 0x1000000) >> 24)) & 1) != 0)
                  {
                    return x;
                  }
                  v183 = wk->pos.x;
                  v182 = wk->pos.y;
                  v184 = wk->pos.z;
                  devilid = (u16)wk->para->devilid;
                  if (devilid == 258)
                  {
                    v183 = acter->pos.x;
                    v182 = acter->pos.y;
                    v184 = 1000.0;
                    if (!v200)
                      goto LABEL_491;
                  }
                  else if (!v200)
                  {
                    if ((devilid == 302 || devilid == 263) && wk->actwk->status == 7)
                      return x;
LABEL_491:
                    if (v204)
                    {
                      if (hwk->skillid == 191)
                      {
                        v190 = 129957892;
LABEL_496:
                        v212.w = 0.0;
                        v212.x = v183;
                        v212.y = v182;
                        v212.z = v184;
                        sBtlPlayDamageSE_SEID(v212, v190);
                        return x;
                      }
                      goto LABEL_507;
                    }
                    else
                    {
                      v191 = v54->attr;
                      if ((v191 & 0x400) != 0)
                      {
                        if ((v54->flg2 & 0x800000) != 0)
                        {
                          if (!v193)
                          v187 = 9;
                          v211.w = 0.0;
                          v211.x = v183;
                        }
                        else
                        {
                          if (!v193)
                          v211.w = 0.0;
                          v211.x = v183;
                          v187 = 8;
                        }
                        goto LABEL_487;
                      }
                      if ((v191 & 2) == 0)
                      {
                        v192 = hwk->skillid;
                        if (v192 <= 156)
                        {
                          if (v192 <= 23)
                          {
                            if (v192 == 8)
                            {
LABEL_539:
                              v190 = 117964804;
                              goto LABEL_496;
                            }
                            if (v192 == 23)
                            {
LABEL_528:
                              v190 = 118947844;
                              goto LABEL_496;
                            }
                          }
                          else
                          {
                            switch (v192)
                            {
                              case 39:
LABEL_532:
                                v190 = 119996420;
                                goto LABEL_496;
                              case 55:
LABEL_542:
                                v190 = 121044996;
                                goto LABEL_496;
                              case 156:
                                v190 = 127664132;
                                goto LABEL_496;
                            }
                          }
                        }
                        else
                        {
                          if ((u32)v192 > 0xA6)
                          {
                            if ((v192 & 0xFFFFFFFE) != 0x1A6)
                            {
                              switch (v192)
                              {
                                case 690:
                                  goto LABEL_539;
                                case 691:
                                case 695:
                                case 699:
                                  goto LABEL_532;
                                case 692:
                                  goto LABEL_542;
                                case 693:
                                case 694:
                                case 697:
                                case 698:
                                case 700:
                                  goto LABEL_536;
                                case 696:
                                  goto LABEL_528;
                                case 701:
                                  v190 = 65808;
                                  goto LABEL_496;
                                default:
                                  if (v192 == 1300)
                                    goto LABEL_546;
                                  goto LABEL_536;
                              }
                            }
                            v190 = 128188417;
                            goto LABEL_496;
                          }
                          if (v192 == 163)
                          {
                            v190 = 128122885;
                            goto LABEL_496;
                          }
                          if ((u32)v192 >= 0xA4)
                            return x;
                        }
LABEL_536:
                        v211.w = 0.0;
                        v211.x = v183;
                        v187 = 2;
LABEL_487:
                        v211.y = v182;
                        v211.z = v184;
                        sBtlPlayDamageSE(v211, v187);
                        return x;
                      }
LABEL_546:
LABEL_507:
                      v211.w = 0.0;
                      v211.x = v183;
                      v187 = 6;
                      goto LABEL_487;
                    }
                    goto LABEL_507;
                  }
                  v211.w = 0.0;
                  v211.x = v183;
                  v187 = 3;
                  goto LABEL_487;
                }
                if ((wk->status & 0x100) == 0)
                  goto LABEL_334;
                if ((v54->flg2 & 0x80) != 0)
                {
                  v131 = updated;
                  if ((wk->side & 0x80) == 0)
                    goto LABEL_455;
                  if (wk->battlemode == 3)
                  {
LABEL_455:
                    v133 = 0.5;
                    goto LABEL_456;
                  }
                }
                else
                {
                  if ((hwk->attr_flg & 0x300) != 0)
                    goto LABEL_334;
                  v131 = updated;
                  if ((wk->side & 0x80) == 0)
                    goto LABEL_351;
                  if (wk->battlemode == 3)
                  {
LABEL_351:
                    v133 = 0.1;
LABEL_456:
                    v178 = v131 * v133;
LABEL_462:
                    v179 = v178;
                    v129 = 1;
                    if (v178 == INFINITY)
                      v179 = 0x80000000;
                    x = v179;
                    goto LABEL_335;
                  }
                }
                v178 = RD_SkillDamageChack((s32)v131);
                goto LABEL_462;
              }
              v117 = v116->UnitMng;
              v119 = sBtlSearchUnit_ID(v117, acterID);
              if (v119)
              {
                v120 = v119;
                if (CheckLiveTarget(v120) && (v120->side & 0x81) == 1)
                {
                  v121 = v120->para->devilid;
                  bunriid = sBtlGetDevilData(v121, -1)->bunriid;
                  if (bunriid != wk->status3_param)
                  {
                    v54 = v205;
                    if ((wk->side & 0x81) != 1)
                      goto LABEL_333;
                    goto LABEL_321;
                  }
                  v54 = v205;
                  if ((v205->flg & 1) != 0 && updated != -1)
                  {
                    v124 = (f32)updated * 1.5;
                    if (v124 == INFINITY)
                      updated = 0x80000000;
                    else
                      updated = v124;
                    x = updated;
                    if ((wk->side & 0x81) != 1)
                      goto LABEL_333;
                    goto LABEL_321;
                  }
                }
              }
              if ((wk->side & 0x81) != 1)
                goto LABEL_333;
LABEL_321:
              v125 = wk->para->devilid;
              v126 = sBtlGetDevilData(v125, -1)->bunriid;
              if (v126 == wk->status3_param)
              {
                v54 = v205;
                if ((v205->flg & 1) != 0 && updated != -1)
                {
                  v128 = (f32)updated * 0.5;
                  if (v128 == INFINITY)
                    updated = 0x80000000;
                  else
                    updated = v128;
                  x = updated;
                }
              }
              else
              {
                v54 = v205;
              }
              goto LABEL_333;
            }
            if (!v60)
            {
              v60 = 0;
              v89 = v199;
              if ((acter->side & 1) == 0 || (u32)(skillid - 1296) < 2 || skillid == 176)
              {
LABEL_255:
                wk->getMag += v89;
                if ((skillid & 0xFFFFFFFE) != 0x510 || attr != 0x2000)
                {
                  v102 = v89;
                  v89 = v102;
                  sBtlSetAddMagWeakAttack(acter, wk, v89, skillid);
                }
                goto LABEL_260;
              }
              if ((v54->flg & 0x200000) != 0)
              {
                v60 = 0;
                goto LABEL_255;
              }
              v90 = GetPercentage();
              if (sBtlGetSpiritSkillChk(1442))
              {
                v196 = wk->pos.y;
                v198 = wk->pos.x;
                v92 = wk->rot.x;
                v93 = wk->rot.w;
                v194 = wk->pos.w;
                v195 = wk->pos.z;
                v94 = wk->rot.y;
                v95 = wk->rot.z;
                per = acter->pos.x;
                v209.y = v196;
                v209.x = v198;
                v213.x = v92;
                v209.w = v194;
                v209.z = v195;
                v213.y = v94;
                v213.z = v95;
                v213.w = v93;
                *(u64 *)&v208.x = 0;
                Radian = sBtlGetRadian(v209, v213, v208, per);
                if (Radian >= 135.0 && Radian <= 179.0 || Radian >= -179.0 && Radian <= -135.0)
                  v75 += 30;
              }
              if (acter->para->now->luck + v75 <= v90)
              {
                v54 = v205;
                v60 = 0;
                v89 = v199;
                goto LABEL_255;
              }
              v54 = v205;
              retpara = SetCritical(wk, retpara, NOMARL_CRITICAL_RAITO);
              x = retpara;
            }
            v60 = 1;
            v89 = 2 * v199;
            goto LABEL_255;
          }
          if (sBtlGetSpiritSkillChk(1441))
          {
            v84 = (f32)retpara * 1.2;
            v85 = v84;
            if (v84 == INFINITY)
              v85 = 0x80000000;
            retpara = v85;
            if (!sBtlGetNakama(0))
            {
LABEL_211:
              if (!sBtlGetNakama(1))
                goto LABEL_215;
            }
LABEL_212:
            v86 = (f32)retpara * 1.2;
            v87 = v86;
            if (v86 == INFINITY)
              v87 = 0x80000000;
            retpara = v87;
            x = v87;
            goto LABEL_215;
          }
          if (!sBtlGetNakama(0))
            goto LABEL_211;
          goto LABEL_212;
        }
      }
      v20 = (s32)acter;
      if (acter)
      {
        side = acter->side;
        goto LABEL_128;
      }
      return v20;
    }
    v39 = acter->para;
    if (sBtlGetBadStatus(v39) != 9 || (v205->flg2 & 0x80) != 0)
    {
      v42 = acter->para;
      if (!sBtlIsKoufun(v42))
        goto LABEL_80;
      v40 = Damage;
      if ((acter->side & 0x80) == 0)
      {
        v43 = v40 + v40;
LABEL_76:
        if (v43 == INFINITY)
          Damage = 0x80000000;
        else
          Damage = v43;
        x = Damage;
        goto LABEL_80;
      }
      v41 = 1.2;
    }
    else
    {
      v40 = Damage;
      v41 = 1.5;
    }
    v43 = v40 * v41;
    goto LABEL_76;
  }
  return sBtlCheckKuishibari(wk, -1);
}

// 0x2056920
static s32 SetCritical(SBTLUNIT_WORK *wk, s32 retpara, f32 raito) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 v12;
  sdfVector4_t v14;

  sBtlCreateSTP_Unit(wk->stpList, wk, 2, 0, 0, 0);
  *(u32 *)&wk->criticalflg = 327681;
  x = wk->pos.x;
  y = wk->pos.y;
  z = wk->pos.z;
  w = wk->pos.w;
  v14.x = x;
  v14.y = y;
  v14.z = z;
  v14.w = w;
  sBtlPlay3DSE(0x1006Bu, v14);
  v12 = (f32)retpara * raito;
  if (v12 == INFINITY)
    return 0x80000000;
  else
    return (s32)v12;
}

// 0x2054210
u16 sBtlSetDamage(SBTLUNIT_WORK *wk, SKLID skillid, s32 damage, s32 acterID) {
  sdatParaWork_t *now;
  s32 hp;
  s32 maxhp;
  SBTLSKILLP_TBL *Skilltbl;
  u32 flg;
  u16 result;
  s32 badst;
  SBTLACTION_WORK *actwk;
  u32 v19;
  sdatUnitWork_t *para;
  _BOOL4 revival;
  s32 v23;
  sdatParaWork_t *v24;
  s32 v26;
  s32 v27;
  s32 *p_hp;
  SBTLUNIT_WORK *v29;
  sdatUnitWork_t *v31;
  s32 v32;
  SBATTLE_WORK *v34;
  s32 magMax;
  s32 *p_mag;
  SBTLUNIT_WORK *v39;
  s32 side;
  SBTLEXP_LISTWORK *v43;
  SBTLEXP_LISTWORK *v44;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v47;
  SBTLEXP_LISTWORK *expList;
  s32 v49;
  SBTLEXP_LISTWORK *v51;
  s32 v52;
  SBTLEXP_LISTWORK *v54;
  SBTLUNIT_WORK *v55;
  s32 v56;
  s32 v57;
  s32 v59;
  SBTLDVLTK_LISTWORK *dvltkList;
  SBTLUNIT_WORK *PChara;
  s64 v65;
  s32 v66;
  sdatParaWork_t *v67;
  s32 *v68;
  s32 v69;
  signed s64 v70;
  u64 v71;
  s64 v72;
  SBTLSM_LISTWORK *sysmsgList;
  s32 v75;
  SBATTLE_WORK *v77;
  s32 v78;
  SBATTLE_WORK *v82;
  s32 *v83;
  s32 v84;
  SBTLSM_LISTWORK *v85;
  s32 v86;
  SBTLDVLTK_LISTWORK *v89;
  u16 Rand;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v92;
  SBTLUNIT_WORK *v93;
  SBTLDVLTK_LISTWORK *v95;
  SBTLDVLTK_LISTWORK *v96;
  SBTLUNIT_WORK *v97;
  bool v98;
  SBTLDVLTK_LISTWORK *v100;
  SBTLDVLTK_LISTWORK *v101;
  SBTLUNIT_WORK *v102;
  SBTLDVLTK_LISTWORK *v104;
  _BOOL4 fast_dying;
  u32 Percentage;
  SBTLUNIT_WORK *v108;
  SBTLEXP_LISTWORK *v110;
  SBTLEXP_LISTWORK *v112;
  SBTLEXP_LISTWORK *v113;
  SBTLUNIT_WORK *v114;
  u32 v115;
  SBTLDVLTK_LISTWORK *v120;
  SBATTLE_WORK *v122;
  SBTLEXP_LISTWORK *v124;
  SBTLEXP_LISTWORK *v127;
  SBTLEXP_LISTWORK *v129;
  SBTLEXP_LISTWORK *v130;
  SBTLUNIT_WORK *v131;
  SBTLEXP_LISTWORK *v132;

  now = wk->para->now;
  hp = now->hp;
  maxhp = now->maxhp;
  Skilltbl = sBtlGetSkilltbl(skillid);
  sBtlDamage(wk, skillid, damage);
  flg = Skilltbl->flg;
  if ((flg & 0x24) != 0 || (Skilltbl->flg2 & 0x40) != 0)
  {
    if ((flg & 0x10000) == 0)
      goto LABEL_16;
    if (skillid == 116)
    {
      badst = 16320;
      goto LABEL_14;
    }
    else
    {
      badst = Skilltbl->badst;
LABEL_14:
      sBtlResetBadStatus(wk, badst);
      actwk = wk->actwk;
      if (actwk->status == 9)
        actwk->cmpframecnt = 0;
LABEL_16:
      v19 = Skilltbl->flg;
      if ((Skilltbl->s_type & 8) == 0)
      {
        if ((v19 & 0x3000) != 0)
        {
          para = wk->para;
          revival = wk->revival;
          damage = sBtlCheckRecoverData(para, damage, 0, revival);
          if ((wk->side & 1) != 0)
          {
            if ((wk->status3 & 0x8000000) != 0)
            {
              if (damage >= 0)
                v23 = damage;
              else
                v23 = damage + 1;
              damage = v23 >> 1;
            }
          }
          v24 = wk->para->now;
          v26 = v24->hp;
          v27 = v24->maxhp;
          p_hp = &v24->hp;
          *p_hp = v26 + damage;
          LimitRange(p_hp, 0, v27);
          sBtlCreateAnim_Unit(wk, v29, damage, 0, 3, 0);
          wk->total_recover += damage;
          v19 = Skilltbl->flg;
        }
        if ((v19 & 0xC000) != 0)
        {
          v31 = wk->para;
          v32 = sBtlCheckRecoverData(v31, damage, 1, 0);
          v34 = wk;
          magMax = v34->magMax;
          p_mag = &v34->mag;
          v34->mag += v32;
          LimitRange(p_mag, 0, magMax);
          sBtlCreateAnim_Unit(wk, v39, v32, 0, 4, 0);
          v19 = Skilltbl->flg;
        }
      }
      if ((v19 & 0x1E0000) == 0)
        return 4;
      goto LABEL_44;
    }
    goto LABEL_14;
  }
  if ((flg & 0x40) != 0 || (flg & 0x80) != 0)
  {
LABEL_44:
    sBtlCheckBattlePara(wk);
    return 4;
  }
  if ((flg & 0x200) != 0)
    return 4;
  if ((flg & 1) == 0)
    return 0;
  wk->nguard_dmgcnt = 60;
  sBtlDecHp(wk, damage, skillid);
  side = wk->side;
  if ((side & 2) != 0)
  {
    UnitMng = wk->UnitMng;
    v47 = sBtlSearchUnit_ID(UnitMng, acterID);
    expList = wk->expList;
    sBtlSetRirituNakamaHD(expList, wk, skillid, acterID, 1u);
    v49 = v47->side;
    if ((v49 & 0x80) != 0)
    {
      v51 = wk->expList;
      v52 = 9;
    }
    else
    {
      if ((v49 & 1) == 0)
        goto LABEL_87;
      v51 = wk->expList;
      v52 = 10;
    }
    v44 = v51;
    v55 = wk;
    v56 = skillid;
    v57 = acterID;
  }
  else
  {
    if ((side & 0x80) != 0)
    {
      v54 = wk->expList;
      v44 = v54;
    }
    else
    {
      if ((side & 1) == 0)
        goto LABEL_87;
      v43 = wk->expList;
      sBtlSetRirituNakamaHD(v43, wk, skillid, acterID, 0xFu);
      v44 = wk->expList;
    }
    v55 = wk;
    v56 = skillid;
    v57 = acterID;
    v52 = 0;
  }
  sBtlSetRirituEnemyHD(v44, v55, v56, v57, v52);
LABEL_87:
  if ((u32)(skillid - 1299) <= 3)
  {
    if ((wk->status & 0x100000) != 0)
      v59 = 10;
    else
      v59 = 8;
    sBtlSetumaSpiritAdd(v59);
    if (wk->para->now->hp <= 0)
    {
      dvltkList = wk->dvltkList;
      PChara = sBtlGetPChara();
      sBtlCreateDvltk_Gouto(dvltkList, PChara, 279, 2);
    }
    v65 = 68719476750LL * wk->magMax;
    v66 = (v65 >> 37) + ((u64)v65 >> 63);
    sBtlSetAddMag_Setsuma(wk, v66);
  }
  v67 = wk->para->now;
  v68 = &v67->hp;
  v69 = v67->maxhp;
  LimitRange(v68, 0, v69);
  wk->total_damage += damage;
  if (skillid == 1130)
  {
    if (10 * damage >= 100)
    {
      v70 = 0xFFFFFFFCCCCCCCCALL * damage;
      v71 = (u64)v70 >> 63;
      v72 = v70 >> 37;
      sysmsgList = wk->sysmsgList;
      v75 = v72 + v71;
      sBtlCreateSM(sysmsgList, 0, 153, 0, 0, 120);
      dds3FadeIn(0x80u, 0xC0u, 0x80u, 0xAu);
      v77 = wk;
      v78 = v77->mag + v75;
      v77->mag = v78;
      if (v78 < 0)
      {
        v77 = wk;
        v77->mag = 0;
      }
    }
  }
  else if (skillid == 509 && (wk->side & 0x80) != 0)
  {
    v82 = wk;
    v83 = &v82->mag;
    v84 = v82->magMax;
    v82->mag /= 2;
    LimitRange(v83, 0, v84);
    v85 = wk->sysmsgList;
    sBtlCreateSM(v85, 0, 79, 0, 0, 120);
  }
  v86 = wk->side;
  result = 1;
  if ((v86 & 1) != 0 && (f32)((f32)hp / (f32)maxhp) >= 0.25 && (f32)((f32)wk->para->now->hp / (f32)maxhp) < 0.25)
  {
    if ((v86 & 0x80) == 0)
    {
      v89 = wk->dvltkList;
      sBtlCreateDvltk_Priority(v89, wk, 6);
      return 1;
    }
    if (wk->member_num < 1)
      return 1;
    Rand = GetRand(2u);
    Nakama = sBtlGetNakama(0);
    v92 = sBtlGetNakama(1);
    v93 = v92;
    if (Nakama && v92)
    {
      if (Rand == 1)
      {
        v104 = wk->dvltkList;
        v96 = v104;
        v97 = v93;
      }
      else
      {
        if (Rand)
        {
LABEL_166:
          fast_dying = wk->fast_dying;
          Percentage = GetPercentage();
          if (fast_dying)
          {
            if (Percentage <= 0x20)
            {
              v108 = sBtlGetNakama(0);
              v110 = wk->expList;
              sBtlSetRirituNakamaHD(v110, v108, skillid, 0, 0xEu);
            }
            if (GetPercentage() > 0x20u)
              return 1;
            v93 = sBtlGetNakama(1);
            goto LABEL_177;
          }
          if (Percentage <= 0x31)
          {
            v127 = wk->expList;
            sBtlSetRirituNakamaHD(v127, Nakama, skillid, 0, 0xEu);
            sBtlSetRirituNakamaHD(wk->expList, v93, skillid, 0, 0xEu);
            goto LABEL_233;
          }
          v115 = GetPercentage();
          if (v115 > 0x31)
          {
            goto LABEL_216;
          }
          goto LABEL_225;
        }
        v95 = wk->dvltkList;
        v96 = v95;
        v97 = Nakama;
      }
      sBtlCreateDvltk_Priority(v96, v97, 24);
      goto LABEL_166;
    }
    v98 = Nakama != 0;
    if (!Nakama || v92)
    {
      if (!v92)
        v98 = 1;
      if (v98)
      {
        if (!((u64)Nakama | (u64)v92))
          return 1;
        goto LABEL_193;
      }
      v120 = wk->dvltkList;
      v101 = v120;
      v102 = v93;
    }
    else
    {
      v100 = wk->dvltkList;
      v101 = v100;
      v102 = Nakama;
    }
    sBtlCreateDvltk_Priority(v101, v102, 24);
LABEL_193:
    v122 = wk;
    if (v122->fast_dying)
    {
      if (GetPercentage() > 0x31u)
        return 1;
      if (Nakama)
      {
        v124 = wk->expList;
        v113 = v124;
        v114 = Nakama;
        goto LABEL_203;
      }
      if (!v93)
        return 1;
LABEL_177:
      v112 = wk->expList;
      v113 = v112;
      v114 = v93;
LABEL_203:
      sBtlSetRirituNakamaHD(v113, v114, skillid, 0, 0xEu);
      return 1;
    }
    if (!Nakama)
    {
      if (!v93)
      {
LABEL_230:
LABEL_233:
        wk->fast_dying = 1;
        return 1;
      }
      goto LABEL_217;
LABEL_216:
      v122 = wk;
LABEL_217:
      v129 = v122->expList;
      v130 = v129;
      v131 = v93;
LABEL_229:
      sBtlSetRirituNakamaHD(v130, v131, skillid, 0, 0xEu);
      goto LABEL_230;
    }
LABEL_226:
    v132 = v122->expList;
    v130 = v132;
    v131 = Nakama;
    goto LABEL_229;
LABEL_225:
    v122 = wk;
    goto LABEL_226;
  }
  return result;
}

// 0x20500b0
bool sBtlSetDamageProc(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, SBTLDMG_HITWORK *hwk, s32 damage, u32 attr) {
  u32 v6;
  SBTLSKILLP_TBL *Skilltbl;
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v19;
  sdfVector4_t *p_rot;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 per;
  f32 Radian;
  f32 v30;
  s32 hstatus;
  bool v35;
  char v36;
  sdatUnitWork_t *v37;
  SBTLDVLTK_LISTWORK *v41;
  s32 v42;
  s32 v43;
  char v44;
  u32 v47;
  SBTLUNIT_WORK *v50;
  s32 v52;
  SBTLDVLTK_LISTWORK *v56;
  s32 v57;
  s32 v59;
  s32 v63;
  s32 devilid;
  u32 DevilSESub;
  u32 v66;
  sdatUnitWork_t *v67;
  char v68;
  s32 v69;
  s32 v70;
  s32 v74;
  sdatUnitWork_t *para;
  sdatUnitWork_t *v76;
  s32 v78;
  s32 v79;
  SBTLUNIT_WORK *v85;
  s32 v87;
  s32 v88;
  s32 v90;
  s32 v91;
  s16 StartTime_Damage;
  s32 v94;
  s32 v95;
  HITSTOP_TABLE_t *HitStopTable_SKLID;
  HITSTOP_TABLE_t *v97;
  f32 MotTime;
  f32 MotSpeed;
  f32 MotSt;
  f32 EffTime;
  f32 EffSpeed;
  f32 EffSt;
  s32 v104;
  s32 criticalflg;
  s32 v107;
  s16 v108;
  s32 v109;
  s32 v111;
  s32 v112;
  s32 v113;
  s32 v115;
  void *Instance;
  SBTLDMG_HITWORK *p_huka2hwk;
  s32 v119;
  s32 acterside;
  s32 serialID2;
  s32 damage_eff_tgt_cnt;
  s32 v123;
  s32 *p_damage_eff_tgt_cnt;
  s32 v126;
  u16 type;
  u32 v129;
  SBTLUNIT_WORK *v130;
  s32 skillid;
  SBTLDVLTK_LISTWORK *dvltkList;
  s32 side;
  u32 v139;
  s64 v143;
  s64 v144;
  s32 v145;
  s32 v148;
  s32 v149;
  s32 v150;
  SBTLUNIT_WORK *v151;
  s32 v152;
  SBTLDMG_HITWORK *v154;
  s32 v155;
  s32 v156;
  s32 v157;
  s32 v159;
  s32 v160;
  f32 v161;
  f32 v162;
  f32 v163;
  f32 rot;
  u32 attra;
  sdfVector4_t v168;
  sdfVector4_t v169;
  sdfVector4_t HitEffectPos;
  sdfVector4_t v171;
  sdfVector4_t v172;
  sdfVector4_t v173;

  attra = attr;
  v6 = attr;
  Skilltbl = sBtlGetSkilltbl(hwk->skillid);
  acterID = hwk->acterID;
  UnitMng = wk->UnitMng;
  v19 = sBtlSearchUnit_ID(UnitMng, acterID);
  if ((wk->status & 0x100) == 0 || (hwk->attr_flg & 0x100) != 0)
  {
    sBtlWinceDamage(v19, wk, hwk);
  }
  if (hwk->skillid == 285)
  {
    if (wk->actwk->status == 9 || (wk->flg & 0x80) != 0)
      goto LABEL_192;
    p_rot = &wk->rot;
    v173 = wk->rot;
    x = wk->pos.x;
    y = wk->pos.y;
    z = wk->pos.z;
    w = wk->pos.w;
    per = hwk->pos.x;
    rot = wk->rot.x;
    v162 = wk->rot.z;
    v163 = wk->rot.y;
    v161 = wk->rot.w;
    v173.w = v161;
    v173.z = v162;
    v173.y = v163;
    v173.x = rot;
    v172.x = x;
    v172.y = y;
    v172.z = z;
    v172.w = w;
    *(u64 *)&v168.x = 0;
    Radian = sBtlGetRadian(v172, v173, v168, per);
    if (Radian < -45.0)
      Radian = -45.0;
    if (Radian <= 45.0)
    {
      v30 = Radian / 6.0;
      goto LABEL_188;
    }
    else
    {
      v30 = 7.5;
      goto LABEL_188;
    }
LABEL_188:
    *p_rot = vct_A;
    sBtlAddUnitDeg(wk, v30);
LABEL_192:
    sBtlSetNormalDamage(wk, 0, v6, hwk);
    return 1;
  }
  if (v6 != 0x2000 && (wk->status & 0x100) != 0)
  {
    if ((Skilltbl->flg2 & 0x1020000) == 0)
      goto LABEL_29;
    if (wk->sklProc->bRun)
    {
LABEL_29:
      if ((hwk->attr_flg & 0x300) == 0 || (wk->flg & 0x10) != 0)
      {
        if (!wk->cmbSkl->bRun)
        {
          sBtlCheckGuardMotion(wk);
          skillid = hwk->skillid;
          sBtlCreateAnim_Unit(wk, v130, damage, 0, 0, skillid);
          sBtlSetHitback(wklock, hwk, v6);
          if ((wk->status & 0x2000) == 0)
          {
            sBtlGetHitUnit_Muki(wklock, hwk, v19);
          }
          dvltkList = wk->dvltkList;
          sBtlCreateDvltk_Priority(dvltkList, v19, 5);
          side = wklock->side;
          if ((side & 0x80) != 0)
            goto LABEL_393;
          if ((side & 1) != 0)
          {
            if (wk->battlemode == 3)
            {
LABEL_393:
              sBtlSetVibe(4);
            }
          }
          v59 = wklock->side;
          if ((v59 & 0x80) == 0)
            goto LABEL_327;
          if (wk->battlemode == 3)
          {
LABEL_116:
            v59 = wklock->side;
LABEL_327:
            goto LABEL_344;
          }
LABEL_340:
          if ((hwk->skillflg & 2) != 0)
          {
            sBtlGuardHit(wk, 1);
            v143 = *(u64 *)&wklock->pos.x;
            v144 = *(u64 *)&wklock->pos.z;
            v145 = 7;
            goto LABEL_346;
          }
          sBtlGuardHit(wk, 0);
LABEL_344:
          v143 = *(u64 *)&wklock->pos.x;
          v144 = *(u64 *)&wklock->pos.z;
          v145 = 1;
LABEL_346:
          *(u64 *)&v171.x = v143;
          *(u64 *)&v171.z = v144;
          sBtlPlayDamageSE(v171, v145);
          sBtlSetMukouDamage(wk, 0);
          return 0;
        }
      }
    }
  }
  if ((hwk->skillflg & 2) == 0)
    goto LABEL_34;
  if ((wk->status & 0x100) != 0)
  {
    if (!wk->sklProc->bRun)
    {
      if ((hwk->skillflg & 2) == 0)
        goto LABEL_34;
      goto LABEL_86;
    }
    sBtlCheckGuardMotion(wk);
    v52 = hwk->skillid;
    sBtlCreateAnim_Unit(wk, v50, damage, 0, 0, v52);
    sBtlSetHitback(wklock, hwk, v6);
    if ((wk->status & 0x2000) == 0)
    {
      sBtlGetHitUnit_Muki(wklock, hwk, v19);
    }
    v56 = wk->dvltkList;
    sBtlCreateDvltk_Priority(v56, v19, 5);
    v57 = wklock->side;
    if ((v57 & 0x80) != 0)
      goto LABEL_394;
    if ((v57 & 1) != 0)
    {
      if (wk->battlemode == 3)
      {
LABEL_394:
        sBtlSetVibe(4);
      }
    }
    v59 = wklock->side;
    if ((v59 & 0x80) == 0)
      goto LABEL_327;
    if (wk->battlemode == 3)
      goto LABEL_116;
    goto LABEL_340;
  }
LABEL_86:
  if ((wk->status & 0x100000) != 0)
  {
    v74 = sBtlCheckHuttobi(wk);
    if ((v6 & 0x100000) != 0 || !v74)
      goto LABEL_34;
  }
  else if ((v6 & 0x100000) != 0)
  {
    goto LABEL_34;
  }
  para = wk->para;
  if (sBtlGetBadStatus(para) != 9)
    goto LABEL_169;
  if (sBtlCheckSetsuma())
  {
    if (!sBtlCheckSetsumaEnd())
    {
LABEL_169:
      v76 = wk->para;
      if (!sBtlIsKoufun(v76))
      {
        if (!sBtlCheckSetsuma())
          goto LABEL_171;
        if (sBtlCheckSetsuma())
        {
          if (!sBtlCheckSetsumaEnd() && (wklock->side & 2) != 0)
          {
LABEL_171:
            if (wk->actwk->status != 9 && (wk->status & 0x2000) == 0)
            {
              sBtlGetHitUnit_Muki(wk, hwk, v19);
            }
            if (wk->weak_shild)
            {
              v78 = hwk->acterID;
              v79 = hwk->skillid;
              sBtlWeakShildActive(wk, v6, v78, v79);
            }
            if ((v6 & 0x4000) != 0 && !wk->weak_shild)
            {
              v159 = hwk->skillid;
              v160 = hwk->acterID;
              sBtlSetDyingDamage(wk, v159, damage, v6, v160);
              goto LABEL_185;
            }
            else
            {
              sBtlSetHuttobiDamage(wk, hwk, damage, v6);
              goto LABEL_185;
            }
LABEL_185:
            sBtlSetHitback(wk, hwk, v6);
            v36 = wk->actwk->status != 9;
            goto LABEL_205;
          }
        }
      }
    }
  }
LABEL_34:
  if ((v6 & 0x4000) != 0 || wk->actwk->status == 9)
  {
    hstatus = wk->hstatus;
    if ((hstatus & 0x40) == 0)
    {
      v35 = (hstatus & 0x10) != 0 && wk->actwk->status == 9;
      v36 = !v35;
      if (!v35)
      {
        if ((wk->status & 0x2000) == 0)
        {
          v37 = wk->para;
          if (sBtlGetBadStatus(v37) != 6)
          {
            sBtlGetHitUnit_Muki(wk, hwk, v19);
          }
        }
        sBtlGetUnitHelperPos(wk, 2);
        v41 = wk->dvltkList;
        sBtlCreateDvltk_Priority(v41, wk, 14);
      }
      if ((v6 & 0x4000) != 0 && wk->weak_shild)
      {
        v42 = hwk->acterID;
        v43 = hwk->skillid;
        sBtlWeakShildActive(wk, v6, v42, v43);
        v44 = 1;
        if (!wk->weak_shild)
          goto LABEL_202;
      }
      else
      {
        v44 = 0;
        if (!wk->weak_shild)
          goto LABEL_202;
      }
      if (!sBtlIsNoke(wk, *(SBTLUNIT_WORK *)&v168.z, &attra))
        goto LABEL_120;
      goto LABEL_9003;
      if (!sBtlIsNoke(wk, v85, &attra))
      {
LABEL_120:
        if ((wk->side & 0x81) != 1)
          goto LABEL_131;
LABEL_124:
        if ((u32)sub_1905740(2, 0))
        {
          if ((u32)sub_1905740(2, 0))
            v63 = 4;
          else
            v63 = 5;
          devilid = wk->para->devilid;
          DevilSESub = sBtlGetDevilSESub(devilid, v63);
          sBtlPlay3DSE(DevilSESub, wk->pos);
        }
LABEL_131:
        v66 = attra;
        if ((attra & 0x200000) == 0)
          goto LABEL_134;
        v67 = wk->para;
        if (sBtlIsKoufun(wk->para))
          goto LABEL_134;
        goto LABEL_9002;
        if (sBtlIsKoufun(v67))
        {
LABEL_134:
          if (sBtlGetSkilltbl(hwk->skillid)->shild_dmg)
            v68 = v44;
          else
            v68 = 1;
          if ((v68 & 1) != 0)
            goto LABEL_141;
          v69 = hwk->acterID;
          v70 = hwk->skillid;
          goto LABEL_140;
        }
LABEL_9002:
        if (!wk->weak_shild)
        {
          v139 = wk->para->devilid - 268;
          if (v139 > 0x25 || ((1 << v139) & 0x3000000003LL) == 0 || (v66 & 0x4000) != 0)
          {
            sBtlCreateSTP_Unit(wk->stpList, wk, 1, 30, Skilltbl->badst, Skilltbl->attr);
          }
          goto LABEL_141;
        }
        if ((v44 & 1) != 0)
        {
LABEL_141:
          sBtlSetHangekiFlag(wk);
          sBtlSetOnlyDamage(wk, damage, hwk);
          sBtlSetHitback(wklock, hwk, v66);
          v36 = 0;
          goto LABEL_205;
        }
        v69 = hwk->acterID;
        v70 = hwk->skillid;
LABEL_140:
        sBtlWeakShildActive(wk, v66, v69, v70);
        goto LABEL_141;
      }
LABEL_9003:
      v6 = attra;
LABEL_202:
      v87 = hwk->skillid;
      v88 = hwk->acterID;
      sBtlSetDyingDamage(wk, v87, damage, v6, v88);
      sBtlSetHitback(wklock, hwk, v6);
      goto LABEL_205;
    }
  }
  if (!sBtlIsNoke(wk, *(SBTLUNIT_WORK *)&v168.z, &attra))
  {
    v44 = 0;
    if ((wk->side & 0x81) != 1)
      goto LABEL_131;
    goto LABEL_124;
  }
  if (wk->actwk->status != 9 && (wk->status & 0x2000) == 0 && ((wk->side & 1) == 0 || (v19->side & 1) == 0))
  {
    sBtlGetHitUnit_Muki(wk, hwk, v19);
  }
  v47 = attra;
  sBtlSetNormalDamage(wk, damage, v47, hwk);
  if ((wk->side & 2) != 0 && wk->BossXAtk)
  {
    DeleteAll_BossDYING(wk);
    wk->BossXAtk = 0;
  }
  sBtlSetHitback(wklock, hwk, v47);
  v36 = 1;
LABEL_205:
  v90 = hwk->acterID;
  if (v90 == wk->playerID)
  {
    if ((wklock->side & 0x80) != 0 && (Skilltbl->type & 0x1000) != 0)
      goto LABEL_214;
  }
  v91 = hwk->skillid;
  sBtlCheckBadStatus(v19, wk, v91, 0);
LABEL_214:
  StartTime_Damage = sBtlGetStartTime_Damage();
  v94 = hwk->acterID;
  if (v94 == wk->playerID)
  {
    v95 = hwk->skillid;
    HitStopTable_SKLID = sbtlplayertblGetHitStopTable_SKLID(v95);
    if (HitStopTable_SKLID)
    {
      v97 = HitStopTable_SKLID;
      if (HitStopTable_SKLID->MotUse)
      {
        MotSpeed = HitStopTable_SKLID->MotSpeed;
        MotTime = HitStopTable_SKLID->MotTime;
        MotSt = HitStopTable_SKLID->MotSt;
        sBtlSetMotionHitStop(v19, MotSpeed, MotTime, MotSt);
      }
      if (v97->EffUse)
      {
        EffSpeed = v97->EffSpeed;
        EffTime = v97->EffTime;
        EffSt = v97->EffSt;
        sBtlSetEffectHitStop(v19, EffSpeed, EffTime, EffSt);
      }
    }
  }
  v104 = wklock->side;
  if ((v104 & 0x80) != 0)
  {
LABEL_235:
    if (!sBtlCheckSetsuma())
    {
      dds3SetQuake(30, 0x3Cu);
      criticalflg = wklock->criticalflg;
      SetHitLight(wk, v19, criticalflg);
      wk->yure = 1;
    }
    goto LABEL_253;
  }
  if ((v104 & 1) != 0)
  {
    if (wk->battlemode == 3)
      goto LABEL_235;
  }
  if (hwk->skillid != 1319)
  {
    v107 = wklock->criticalflg;
    SetHitLight(wk, v19, v107);
    if ((wk->hstatus & 0x10) != 0)
      v108 = 2;
    else
      v108 = 1;
    wk->yure = v108;
    v109 = wk->para->devilid;
    if ((u32)(v109 - 258) < 3 || (v109 & 0xFFFFFFFC) == 0x138)
      wk->yure = 0;
  }
LABEL_253:
  v111 = hwk->acterID;
  v112 = wklock->side;
  if (v111 == wk->playerID && (v112 & 2) != 0)
  {
    v113 = hwk->skillid;
    sBtlSetSetsuma_SkillHit(v19, v113);
    sBtlSetAutoTagetDamage(v19, wklock);
    sBtlPlayerSetDamage(v19, wklock);
    v112 = wklock->side;
  }
  if ((v112 & 0x80) != 0)
    goto LABEL_395;
  if ((v112 & 1) != 0)
  {
    if (wk->battlemode == 3)
    {
LABEL_395:
      sBtlSetSetsuma_PlayerDamage(wklock);
    }
  }
  v115 = hwk->acterID;
  if (v115 == wk->playerID)
  {
    if ((wklock->side & 2) != 0)
    {
      Instance = get_Instance(0);
      HitCountAdd(Instance, 1, hwk->skillid, 0);
    }
  }
  if (hwk->workID == -1)
    hwk->skillid = -1;
  if ((wklock->side & 7) != 0)
  {
    if (hwk->BEDtype == 2)
    {
      p_huka2hwk = &wk->huka2hwk;
      p_huka2hwk = hwk;
      v119 = hwk->skillid;
      acterside = hwk->acterside;
      serialID2 = hwk->serialID2;
      sBtlCheckEffectData(wklock, v119, 5u, 0, acterside, serialID2, StartTime_Damage);
      return v36;
    }
    if (wklock->criticalflg == 1)
    {
      damage_eff_tgt_cnt = wklock->damage_eff_tgt_cnt;
      wklock->criticalflg = 0;
      if (!damage_eff_tgt_cnt)
      {
        v123 = hwk->acterID;
        p_damage_eff_tgt_cnt = &wklock->damage_eff_tgt_cnt;
        if (v123 == wk->playerID)
        {
          v126 = hwk->skillid;
          type = hwk->type;
          if (!v19->damage_eff_rai_cnt)
          {
            if (!v129)
            HitEffectPos = sBtlGetHitEffectPos(v126, wklock, v19);
            sBtlCheckYukaDamageEffect(wklock, v126, type, StartTime_Damage, 1, HitEffectPos, v19);
            v19->damage_eff_rai_cnt = 15;
            goto LABEL_358;
          }
          if (!v129)
            goto LABEL_354;
        }
        else
        {
          v126 = hwk->skillid;
          type = hwk->type;
LABEL_354:
        }
LABEL_355:
        v169 = sBtlGetHitEffectPos(v126, wklock, v19);
        sBtlCheckYukaDamageEffect(wklock, v126, type, StartTime_Damage, 0, v169, v19);
LABEL_358:
        *p_damage_eff_tgt_cnt = 4;
      }
    }
    else if (!wklock->damage_eff_tgt_cnt)
    {
      v126 = hwk->skillid;
      type = hwk->type;
      p_damage_eff_tgt_cnt = &wklock->damage_eff_tgt_cnt;
      goto LABEL_355;
    }
    if ((sBtlGetSklVisualTbl(hwk->skillid)->flg & 0x200) != 0 || (hwk->type & 0xFFFu) > 0xF || ((1 << LOBYTE(hwk->type)) & 0xFE3E) == 0)
    {
      return v36;
    }
    if (wklock->damage_fuka_tgt_cnt)
    {
      v148 = hwk->skillid;
      v149 = hwk->acterside;
      v150 = hwk->serialID2;
      v151 = wklock;
      v152 = v148;
LABEL_374:
      sBtlCheckEffectData_SeOnly(v151, v152, 2u, 0, v149, v150, StartTime_Damage);
      return v36;
    }
    v154 = &wk->huka2hwk;
    v154 = hwk;
    if (wk->encountno == 50 && (wk->side & 0x80) != 0)
    {
      v155 = hwk->skillid;
      if (v155 == 151)
        goto LABEL_371;
      if (v155 == 451)
      {
LABEL_380:
        wklock->damage_fuka_tgt_cnt = 15;
        return v36;
      }
    }
    else
    {
      v155 = hwk->skillid;
      if (v155 == 151)
      {
LABEL_371:
        v149 = hwk->acterside;
        v150 = hwk->serialID2;
        v152 = 151;
        v151 = wklock;
        goto LABEL_374;
      }
    }
    v156 = hwk->acterside;
    v157 = hwk->serialID2;
    sBtlCheckEffectData(wklock, v155, 2u, 0, v156, v157, StartTime_Damage);
    goto LABEL_380;
  }
  return v36;
}

// 0x205a0b0
sdfVector4_t sBtlGetHitEffectPos(SKLID sklid, SBTLUNIT_WORK *wklock, SBTLUNIT_WORK *acter) {
  s32 side;
  f32 v11;
  u32 v12;
  f32 v13;
  s32 v14;
  f32 y;
  f32 v18;
  f32 v19;
  u16 major;
  s32 minor;
  f32 cylinder;
  f32 v23;
  SBTLSKILLP_TBL *Skilltbl;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  u32 v30;
  f32 x;
  f32 v32;
  f32 z;
  f32 w;
  f32 RotToDir;
  s32 v36;
  SBTLCAMERA_WORK *camera;
  f32 v39;
  f32 v40;
  SBTLUNIT_WORK *v45;
  u32 v46;
  long f64 v47;
  s32 devilid;
  f32 v49;
  f32 v50;
  f32 LenXZ;
  s64 v52;
  SBTLUNIT_WORK *v54;
  u32 v55;
  long f64 v56;
  s64 v57;
  s64 v58;
  s64 v59;
  s64 v60;
  struct sdfVector4_t ToX;
  sdfVector4_t v62;
  sdfVector4_t v63;
  sdfVector4_t result;

  ToX = (struct sdfVector4_t)0;
  v59 = 0;
  v60 = 0;
  v57 = 0;
  v58 = 0;
  sBtlGetUnitHelperPos(wklock, 1);
  ToX = vct_A;
  sBtlGetUnitHelperPos(acter, 1);
  goto LABEL_10;
LABEL_21:
  if ((side & 0x80) == 0)
    goto LABEL_25;
  y = wklock->pos.y;
  ToX.y = ToX.y + -20.0;
  if ((f32)(ToX.y - y) >= -200.0)
    goto LABEL_25;
  v18 = y + -200.0;
  goto LABEL_24;
LABEL_10:
  side = wklock->side;
  if ((side & 1) != 0)
    goto LABEL_21;
  v11 = vct_A.y;
  v12 = sklid - 690;
  if ((u32)(sklid - 690) > 0xB || ((1 << (sklid + 78)) & 0xA67) == 0)
  {
    if (sklid != 65)
    {
      if (sklid == 1300)
      {
        v30 = wklock->para->devilid - 258;
        if (v30 <= 0x39)
        {
          if (((1 << v30) & 0x300000000000005LL) != 0)
          {
            result.z = -1300.0;
            v13 = -400.0;
            result.x = 350.0;
            goto LABEL_54;
          }
          if (((1 << v30) & 0xC0000000000002LL) != 0)
          {
            result.x = 0.0;
            result.z = -1300.0;
            v13 = -500.0;
            goto LABEL_54;
          }
        }
        goto LABEL_25;
      }
      v18 = v11 + acter->damage_ActerOfsY;
      if (sklid <= 55)
      {
        if (sklid <= 23)
        {
          if (sklid != 8 && sklid != 23)
            goto LABEL_103;
        }
        else if ((sklid | 0x10) != 0x37)
        {
          goto LABEL_103;
        }
      }
      else
      {
        if ((u32)sklid <= 0xBF)
        {
          if (sklid != 156 && sklid != 191)
            goto LABEL_103;
          goto LABEL_24;
        }
LABEL_86:
        v52 = (u32)(sklid - 1299);
        if ((u32)v52 > 0x2F)
          goto LABEL_109;
        if (((1 << ((u8)sklid - 19)) & 0xFF3FFFA0F800LL) == 0)
        {
          if (((1 << ((u8)sklid - 19)) & 0x4000400007LL) != 0)
            goto LABEL_25;
          if (v52 == 20)
          {
            result.z = 64.0;
            v13 = -56.0;
            result.x = -59.0;
            goto LABEL_54;
          }
LABEL_109:
          if (v12 <= 0xB && ((1 << v12) & 0xA67) != 0)
            goto LABEL_25;
LABEL_103:
          ToX.y = sBtlGetRandomRange(ToX.y, v18);
          goto LABEL_25;
        }
      }
LABEL_24:
      ToX.y = v18;
LABEL_25:
      v19 = sBtlGetGroundPos(ToX.x, ToX.z) + -60.0;
      if (ToX.y > v19)
        ToX.y = v19;
      major = wklock->major;
      minor = wklock->minor;
      cylinder = sBtlGetVisualData(major, minor)->nml->cylinder;
      v23 = sBtlGetVisualData(acter->major, acter->minor)->nml->cylinder;
      Skilltbl = sBtlGetSkilltbl(sklid);
      switch (sklid)
      {
        case 1301:
          goto LABEL_34;
        case 1300:
          x = wklock->rot.x;
          v32 = wklock->rot.y;
          z = wklock->rot.z;
          w = wklock->rot.w;
          v63.x = x;
          v63.y = v32;
          v63.z = z;
          v63.w = w;
          RotToDir = sBtlGetRotToDir(v63);
          v29 = sBtlGet360(RotToDir + 180.0);
          goto LABEL_45;
        case 1299:
LABEL_34:
          v25 = wklock->rot.x;
          v26 = wklock->rot.y;
          v27 = wklock->rot.z;
          v28 = wklock->rot.w;
          v62.x = v25;
          v62.y = v26;
          v62.z = v27;
          v62.w = v28;
          v29 = sBtlGetRotToDir(v62);
LABEL_45:
          sBtlGetMoveXZ(ToX.x, ToX.z, v29, cylinder, &ToX.x, &ToX.z);
LABEL_53:
          v13 = ToX.y;
          result.x = ToX.x;
          result.z = ToX.z;
          goto LABEL_54;
      }
      v36 = Skilltbl->type & 0xFFF;
      if (v36 == 5 || v36 == 3)
      {
        camera = wk->scene->camera;
        v39 = camera->camerapos.x;
        v40 = camera->camerapos.z;
        goto LABEL_52;
      }
      else
      {
        v49 = acter->pos.x;
        v50 = acter->pos.z;
        LenXZ = sBtlGetLenXZ(ToX.x, ToX.z, v49, v50);
        if (LenXZ < (f32)(cylinder + v23))
        {
          cylinder = LenXZ - v23;
          if ((f32)(LenXZ - v23) < 1.0)
            cylinder = 1.0;
        }
        v39 = acter->pos.x;
        v40 = acter->pos.z;
        goto LABEL_52;
      }
LABEL_52:
      sBtlGetMovePosToPos(ToX.x, ToX.z, v39, v40, cylinder, &ToX.x, &ToX.z);
      goto LABEL_53;
    }
    devilid = (u16)wklock->para->devilid;
    if (wklock->para->devilid <= 260)
    {
      if (devilid == 258)
      {
LABEL_100:
        result.x = acter->pos.x;
        goto LABEL_101;
      }
      if (devilid != 260)
      {
LABEL_102:
        v18 = v11 + acter->damage_ActerOfsY;
        goto LABEL_103;
      }
    }
    else if (devilid != 315)
    {
      if (devilid != 314)
        goto LABEL_102;
      goto LABEL_100;
    }
    result.x = 0.0;
LABEL_101:
    result.z = 950.0;
    v13 = -300.0;
    goto LABEL_54;
  }
  v13 = 0.0;
  v14 = (u16)wklock->para->devilid;
  if (v14 == 258)
  {
LABEL_63:
    result.x = acter->pos.x;
    result.z = 800.0;
  }
  else if (v14 == 260)
  {
    result.x = 0.0;
    result.z = 900.0;
  }
  else
  {
    result.z = 900.0;
    result.x = 0.0;
    switch ((s16)v14)
    {
      case 312:
        v45 = wk->scrUnitList[0];
        v59 = 0;
        v60 = 0;
        if (!v46)
        sBtlGetUnitHelperPos(v45, 101);
        sub_1B335A0(&v59, 0, v47);
        LODWORD(result.x) = v59;
        LODWORD(result.z) = v60;
        break;
      case 313:
        v54 = wk->scrUnitList[0];
        v57 = 0;
        v58 = 0;
        if (!v55)
        sBtlGetUnitHelperPos(v54, 102);
        sub_1B335A0(&v57, 0, v56);
        LODWORD(result.x) = v57;
        LODWORD(result.z) = v58;
        break;
      case 314:
        goto LABEL_63;
      case 315:
        break;
      default:
        v12 = sklid - 690;
        v18 = vct_A.y + acter->damage_ActerOfsY;
        goto LABEL_86;
    }
  }
LABEL_54:
  result.w = ToX.w;
  result.y = v13;
  return result;
}

// 0x2059f40
static void SetHitLight(SBTLUNIT_WORK *wk1, SBTLUNIT_WORK *wk2, s32 _IsCritical) {
  f32 x;
  s32 major;
  f32 z;
  s32 minor;
  SBTLEFFDMG_TBL *EffDamagetbl;
  f32 v14;
  u32 dr;
  u32 dg;
  s32 v17;
  u32 db;
  u32 v19;
  u32 v20;
  u32 v21;

  if (wk1 && wk2)
  {
    x = wk2->pos.x;
    wk1->hitlight_cnt = 48;
    major = wk1->major;
    wk1->hitlight_x = x;
    z = wk2->pos.z;
    wk1->hitlight_Critical = IsCritical != 0;
    minor = wk1->minor;
    wk1->hitlight_z = z;
    EffDamagetbl = sBtlGetEffDamagetbl(major, minor);
    if ((EffDamagetbl->flg & 4) == 0)
    {
      if (wk1 == wk2)
        return;
      goto LABEL_8;
    }
    dr = EffDamagetbl->dr;
    dg = EffDamagetbl->dg;
    if (IsCritical)
      v17 = 192;
    else
      v17 = 128;
    db = EffDamagetbl->db;
    v19 = v17 * dr;
    if (dg > dr)
      dr = EffDamagetbl->dg;
    v20 = v17 * dg;
    v21 = v17 * db;
    if (db > dr)
      dr = EffDamagetbl->db;
    wk1->hitlight_r = v19 / dr;
    wk1->hitlight_g = v20 / dr;
    wk1->hitlight_b = v21 / dr;
    if (wk1 != wk2)
    {
LABEL_8:
      wk2->hitlight_x = wk1->pos.x;
      v14 = wk1->pos.z;
      wk2->hitlight_cnt = wk1->hitlight_cnt;
      wk2->hitlight_Critical = wk1->hitlight_Critical;
      wk2->hitlight_z = v14;
      *(u64 *)&wk2->hitlight_r = *(u64 *)&wk1->hitlight_r;
      wk2->hitlight_b = wk1->hitlight_b;
    }
  }
}

// 0x20581d0
bool sBtlGetHitUnit_Muki(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *hwk, SBTLUNIT_WORK *acter) {
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v11;
  SBTLDMG_HITWORK *p_fields;
  bool result;
  s32 devilid;
  s32 v16;
  SBTLUNIT_LISTWORK *v17;
  SBTLUNIT_WORK *v18;
  SBTLUNIT_WORK *v19;
  sdfVector4_t *p_rot;
  f32 per;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 Radian;
  f32 v31;
  struct sdfVector4_t rot;
  f32 rota;
  sdfVector4_t v38;
  sdfVector4_t v39;
  sdfVector4_t v40;

  acterID = hwk->acterID;
  UnitMng = wk->UnitMng;
  if (sBtlSearchUnit_ID(UnitMng, acterID) == wk)
    return 0;
  if (!acter || (wk->side & 1) == 0)
    goto LABEL_11;
  if ((acter->side & 1) != 0)
    return 0;
  result = 0;
  devilid = acter->para->devilid;
  if ((u32)(devilid - 258) >= 3 && (devilid & 0xFFFFFFFC) != 0x138)
  {
LABEL_11:
    v11 = hwk->type & 0xFFF;
    if (v11 != 14 && v11 != 2 || (hwk->area & 0x10) == 0)
    {
      if (hwk->skillid == 287)
      {
        p_fields = &hwk->fields;
        if ((wk->flg & 0x80) != 0)
          return 1;
LABEL_37:
        p_rot = &wk->rot;
        v40.x = wk->rot.x;
        per = p_fields->pos.x;
        x = wk->pos.x;
        y = wk->pos.y;
        z = wk->pos.z;
        w = wk->pos.w;
        v27 = wk->rot.y;
        v28 = wk->rot.z;
        v29 = wk->rot.w;
        rota = wk->rot.x;
        v40.x = rota;
        v39.x = x;
        v39.y = y;
        v39.z = z;
        v39.w = w;
        v40.y = v27;
        v40.z = v28;
        *(u64 *)&v38.x = 0;
        v40.w = v29;
        Radian = sBtlGetRadian(v39, v40, v38, per);
        if (Radian < -45.0)
          Radian = -45.0;
        if (Radian <= 45.0)
        {
          v31 = Radian / 6.0;
          goto LABEL_46;
        }
        else
        {
          v31 = 7.5;
          goto LABEL_46;
        }
LABEL_46:
        *p_rot = vct_A;
        sBtlAddUnitDeg(wk, v31);
        return 1;
      }
      p_fields = hwk->acterpos;
      if ((wk->flg & 0x80) == 0)
        goto LABEL_37;
      return 1;
    }
    v16 = hwk->acterID;
    v17 = wk->UnitMng;
    v18 = sBtlSearchUnit_ID(v17, v16);
    if (!v18)
      return 1;
    v19 = v18;
    if (!sBtlCheckDamageTarget(v19))
      return 1;
    rot = v19->pos;
    vct_A = rot;
    return 1;
  }
  return result;
}

// 0x2047010
bool sBtlSetHitback(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *hwk, u32 attr) {
  s32 wince_SuperArmor;
  bool result;
  sdatUnitWork_t *para;
  u32 BadStatus;
  s32 side;
  u32 v12;
  sdatUnitWork_t *v13;
  f32 hitbk_rate;
  sdatUnitWork_t *v15;
  s32 devilid;
  SBTLACTAI_WORK *actaiwk;
  f32 v18;
  f32 hitbk_cnt;
  s32 vstatus;
  f32 z;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 acterID;
  SBTLUNIT_WORK *v25;
  SBTLUNIT_WORK *v26;
  SBTLACTAI_WORK *v28;
  s32 v29;
  f32 v30;
  f32 *p_y;
  f32 *p_z;
  f32 x;
  f32 y;
  f32 w;
  f32 v36;
  long f64 v37;
  s64 v38;
  f32 v39;
  f32 *acterpos;
  f32 v41;
  f32 v42;
  long f64 v43;
  long f64 v44;
  u32 v45;
  s32 skillid;
  s32 v49;
  SBTLUNIT_LISTWORK *v50;
  SBTLUNIT_WORK *v51;
  f32 v52;
  f32 v53;
  SBTLUNIT_WORK *v54;
  f32 v55;
  f32 v56;
  f32 RotToDir;
  f32 v58;
  f32 v59;
  f32 v60;
  long f64 v61;
  long f64 v62;
  SBTLACTAI_WORK *v63;
  f32 v64;
  f32 v65;
  f32 VecToDir;
  s32 v68;
  SBTLUNIT_LISTWORK *v69;
  SBTLUNIT_WORK *v70;
  SBTLUNIT_WORK *v71;
  SBTLACTAI_WORK *v72;
  f32 v73;
  f32 v74;
  f32 v75;
  f32 PosToDir;
  f32 AtoB_LR;
  f32 v78;
  SBTLACTAI_WORK *v79;
  f32 *p_x;
  f32 *v81;
  f32 v82;
  SBTLACTAI_WORK *v84;
  f32 v85;
  f32 v86;
  f32 v87;
  SBTLACTAI_WORK *v88;
  f32 v89;
  u32 v90;
  SBTLACTAI_WORK *v91;
  u32 v92;
  f32 *v93;
  f32 *v94;
  SBTLACTAI_WORK *v95;
  SBTLACTAI_WORK *v96;
  f32 v97;
  f32 v98;
  f32 v99;
  long f64 v100;
  long f64 v101;
  __int128 v102;
  s64 v103;
  s64 v104;
  sdfVector4_t v105;

  v103 = 0;
  v104 = 0;
  wince_SuperArmor = wk->wince_SuperArmor;
  v102 = xmmword_3CFD5C0;
  if (wince_SuperArmor)
    return 0;
  if ((wk->side & 0x80) != 0)
  {
    if (sBtlChkNowJump_OrAtk(wk))
      return 0;
  }
  para = wk->para;
  BadStatus = sBtlGetBadStatus(wk->para);
  side = wk->side;
  if ((side & 7) == 0)
    return 0;
  v12 = BadStatus;
  if ((side & 0x80) != 0)
  {
    if (attr & 0x1000 | wk->hstatus & 0x400)
      return 0;
  }
  else if ((attr & 0x1000) != 0)
  {
    return 0;
  }
  result = 0;
  if ((attr & 0x2000) == 0 && (wk->flg & 0x40) == 0 && v12 != 9)
  {
    v13 = wk->para;
    if (sBtlIsKoufun(v13))
      return 0;
    hitbk_rate = hwk->hitbk_rate;
    if (hitbk_rate <= 0.0)
      return 0;
    v15 = wk->para;
    devilid = v15->devilid;
    if (devilid <= 290)
    {
      if ((u32)(devilid - 261) > 0xFFFFFFFC)
        return 0;
      if (devilid != 290)
        goto LABEL_36;
    }
    else
    {
      if (devilid == 291)
      {
        if (wk->actwk->use_skillid != 1549)
          goto LABEL_36;
        return 0;
      }
      if (v15->devilid != 297)
      {
        if ((devilid & 0xFFFFFFFC) != 0x138)
          goto LABEL_36;
        return 0;
      }
    }
    if ((v15->aisyo->para[0] & 0x1000) == 0)
    {
LABEL_36:
      actaiwk = wk->actaiwk;
      v18 = 1.0;
      actaiwk->hitbk_cnt = 0.0;
      hitbk_cnt = hwk->hitbk_cnt;
      actaiwk->hitbk_rate = hitbk_rate;
      actaiwk->hitbk_cmpcnt = 1.0 / hitbk_cnt;
      vstatus = wk->vstatus;
      if ((vstatus & 0x800) == 0)
        actaiwk->hitbk_start_wait_cnt = 9.0;
      actaiwk->hitbk_eff_len = 0.0;
      actaiwk->hitbk_eff_len_oldx = wk->pos.x;
      z = wk->pos.z;
      actaiwk->hitbk_size_ignore = 0;
      actaiwk->hitbk_eff_len_oldz = z;
      wk->vstatus = vstatus | 0x800;
      if ((attr & 0x400000) != 0)
        actaiwk->hitbk_rate = hitbk_rate * 0.5;
      UnitMng = wk->UnitMng;
      acterID = hwk->acterID;
      v25 = sBtlSearchUnit_ID(UnitMng, acterID);
      v26 = v25;
      if (v25 && (wk->side & 2) != 0 && (~v25->side & 0x81) == 0)
      {
        if (wk->battlemode != 3)
        {
          v28 = wk->actaiwk;
          if (v28->hitbk_rate > 20.0 && v28->hitbk_cmpcnt < 0.2)
            Add(wk->ListID, 0);
        }
      }
      v29 = hwk->type & 0xFFF;
      if ((v29 == 14 || v29 == 2) && (hwk->area & 0x10) != 0)
      {
        if (!v26)
          goto LABEL_83;
        if (sBtlCheckDamageTarget(v26))
        {
          x = v26->pos.x;
          y = v26->pos.y;
          v36 = v26->pos.z;
          w = v26->pos.w;
          *(__n128 *)&v37 = sub_1B332C0(0, x, y, v36, w);
          sub_1B335A0(&v102, 0, v37);
          v38 = v102;
          v18 = *((f32 *)&v102 + 3);
          v39 = *((f32 *)&v102 + 2);
        }
        else
        {
LABEL_83:
          v60 = hwk->pos.x;
          *(u64 *)&v102 = __PAIR64__(LODWORD(hwk->pos.y), LODWORD(v60));
          v39 = hwk->pos.z;
          *((f32 *)&v102 + 2) = v39;
          v38 = v102;
        }
        sub_1B332C0(0, *(f32 *)&v38, *((f32 *)&v38 + 1), v39, v18);
        v61 = sub_205D9C0(0, 0.0);
        sub_1B335A0(&v103, 0, v61);
        sub_1B332C0(0, wk->pos.x, wk->pos.y, wk->pos.z, wk->pos.w);
        sub_205D9C0(0, 0.0);
        sub_1B33360(0, *(f32 *)&v103, *((f32 *)&v103 + 1), *(f32 *)&v104, *((f32 *)&v104 + 1));
        sub_1B33400(0);
        sub_1949110(0);
        sub_1B335A0(&wk->actaiwk->hitbk_dir, 0, v62);
        v63 = wk->actaiwk;
        if (v63->hitbk_rate > 10.0 && v63->hitbk_cmpcnt < 0.2)
        {
          v64 = v63->hitbk_dir.x;
          v65 = v63->hitbk_dir.z;
          VecToDir = sBtlGetVecToDir(v64, v65);
          Add(wk->ListID, VecToDir, 1.0, 0);
        }
        return 1;
      }
      if (hwk->skillid == 287)
      {
        v30 = hwk->pos.x;
        p_y = &hwk->pos.y;
        p_z = &hwk->pos.z;
      }
      else
      {
        acterpos = hwk->acterpos;
        p_y = &acterpos[1];
        v30 = acterpos[0];
        p_z = &acterpos[2];
      }
      *(f32 *)&v102 = v30;
      v41 = *p_y;
      *((f32 *)&v102 + 1) = *p_y;
      v42 = *p_z;
      *((f32 *)&v102 + 2) = *p_z;
      sub_1B332C0(0, v30, v41, v42, 1.0);
      v43 = sub_205D9C0(0, 0.0);
      sub_1B335A0(&v103, 0, v43);
      sub_1B332C0(0, wk->pos.x, wk->pos.y, wk->pos.z, wk->pos.w);
      sub_205D9C0(0, 0.0);
      sub_1B33360(0, *(f32 *)&v103, *((f32 *)&v103 + 1), *(f32 *)&v104, *((f32 *)&v104 + 1));
      sub_1B33400(0);
      sub_1949110(0);
      sub_1B335A0(&wk->actaiwk->hitbk_dir, 0, v44);
      skillid = hwk->skillid;
      if (skillid > 1319)
      {
        if (skillid != 1320)
        {
          if (skillid == 1321)
          {
            v68 = hwk->acterID;
            v69 = wk->UnitMng;
            v70 = sBtlSearchUnit_ID(v69, v68);
            if (v70)
            {
              v71 = v70;
              if (v70->actaiwk->targetID == wk->ListID)
              {
                v72 = wk->actaiwk;
                v73 = v72->hitbk_dir.x;
                v74 = v72->hitbk_dir.z;
                v75 = sBtlGetVecToDir(v73, v74);
                PosToDir = sBtlGetPosToDir(v71->pos.x, v71->pos.z, wk->pos.x, wk->pos.z);
                AtoB_LR = sBtlGetAtoB_LR(PosToDir, v75);
                if (sBtlGetABS(AtoB_LR) < 10.0)
                {
                  v78 = 45.0;
                  if (AtoB_LR < 0.0)
                    v78 = -45.0;
                  v79 = wk->actaiwk;
                  p_x = &v79->hitbk_dir.x;
                  v81 = &v79->hitbk_dir.z;
                  v82 = v75 + v78;
                  sBtlGetDirToVec(v82, p_x, v81);
                }
              }
            }
          }
          else if (skillid != 1322)
          {
            goto LABEL_106;
          }
        }
        wk->actaiwk->hitbk_size_ignore = 1;
        goto LABEL_106;
      }
      if (skillid != 157)
      {
        if (skillid == 163)
        {
          v49 = hwk->acterID;
          v50 = wk->UnitMng;
          v51 = sBtlSearchUnit_ID(v50, v49);
          if (v51)
          {
            v52 = v51->rot.x;
            v53 = v51->rot.y;
            v54 = v51;
            v56 = v51->rot.z;
            v55 = v51->rot.w;
            v105.x = v52;
            v105.y = v53;
            v105.z = v56;
            v105.w = v55;
            RotToDir = sBtlGetRotToDir(v105);
            v58 = sBtlGetPosToDir(v54->pos.x, v54->pos.z, wk->pos.x, wk->pos.z);
            v59 = sBtlGetAtoB_LR(RotToDir, v58);
            sBtlGetDirToVec(RotToDir + (f32)(v59 * 1.5), &wk->actaiwk->hitbk_dir.x, &wk->actaiwk->hitbk_dir.z);
            wk->actaiwk->hitbk_start_wait_cnt = 0.0;
          }
        }
        goto LABEL_106;
      }
      if ((u32)sub_1E446B0(0))
      {
        if ((u32)sub_1E446B0(0) != 1)
        {
          if ((attr & 0x400000) == 0)
          {
            v95 = wk->actaiwk;
            v95->hitbk_start_wait_cnt = (f32)(u32)sub_1905740(3, 0);
            v96 = wk->actaiwk;
            v97 = v96->hitbk_dir.x;
            v98 = v96->hitbk_dir.z;
            v99 = sBtlGetVecToDir(v97, v98);
            wk->mv_rotbk = v99;
            FromEuler(0.0, v99 * 0.017453292, 0.0);
            *(__n128 *)&v101 = sub_1B335A0(&wk->rot, 0, v100);
            sub_1B335A0(&wk->rotbk, 0, v101);
          }
          goto LABEL_106;
        }
        if ((attr & 0x400000) != 0)
        {
LABEL_106:
          if ((wk->side & 2) != 0 && (~v26->side & 0x81) == 0)
          {
            if (wk->battlemode != 3)
            {
              v84 = wk->actaiwk;
              if (v84->hitbk_rate > 20.0 && v84->hitbk_cmpcnt < 0.2)
              {
                v85 = v84->hitbk_dir.x;
                v86 = v84->hitbk_dir.z;
                v87 = sBtlGetVecToDir(v85, v86);
                Add(wk->ListID, v87, 1.0, 0);
              }
            }
          }
          sBtlSetDamageBounce(wk, hwk, v45);
          return 1;
        }
        v88 = wk->actaiwk;
        *(float32x2_t *)&v88->hitbk_cmpcnt = vmul_f32(*(float32x2_t *)&v88->hitbk_cmpcnt, (float32x2_t)0x3DCCCCCD3E99999ALL);
        v89 = (u32)sub_1905740(3, 0);
      }
      else
      {
        if ((attr & 0x400000) != 0)
          goto LABEL_106;
        v88 = wk->actaiwk;
        *(float32x2_t *)&v88->hitbk_cmpcnt = vmul_f32(*(float32x2_t *)&v88->hitbk_cmpcnt, (float32x2_t)0x3DCCCCCD3E99999ALL);
        v89 = ((u32)sub_1905740(6, 0) + 3);
      }
      v88->hitbk_start_wait_cnt = v89;
      v90 = sub_1905740(360, 0);
      v91 = wk->actaiwk;
      v92 = v90;
      v93 = &v91->hitbk_dir.x;
      v94 = &v91->hitbk_dir.z;
      sBtlGetDirToVec((f32)v92, v93, v94);
      goto LABEL_106;
    }
    return 0;
  }
  return result;
}

// 0x205a890
bool sBtlSetDamageBounce(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *hwk, u32 attr) {
  char side;
  bool result;
  s32 skillid;
  f32 v10;
  s32 v11;
  s32 Rebound[2];

  side = wk->side;
  result = 0;
  *(u64 *)Rebound = 0;
  if ((side & 2) == 0)
    return result;
  if ((hwk->acterside & 0x80) == 0)
    return 0;
  skillid = hwk->skillid;
  if (sbtlplayertblChkPlayerSordSkill(skillid) && (wk->hstatus & 0x10) != 0)
  {
    sBtlGetBouncePow(wk, &Rebound[1], Rebound);
    v10 = *(f32 *)&Rebound[1];
    if (*(f32 *)&Rebound[1] > 1.0)
    {
      v11 = Rebound[0];
      sBtlSetBounce(wk, -v10, 0.1, v11);
      sBtlSetBounceHitStop(wk, 2, 8);
    }
  }
  return 1;
}

// 0x2055090
bool sBtlSetStoneDeadDamageProc(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, SBTLDMG_HITWORK *hwk, s32 damage, u32 attr) {
  s16 StartTime_Damage;
  s32 acterID;
  s32 workID;
  SBTLDMG_HITWORK *p_huka2hwk;
  s32 skillid;
  s32 acterside;
  s32 serialID2;
  u8 v18;
  SBTLUNIT_WORK *v19;
  s32 v20;
  u32 v21;
  SBTLDMG_HITWORK *v23;
  s32 v24;

  sBtlSetStoneDeadDamage(wk, (s32)wklock);
  StartTime_Damage = sBtlGetStartTime_Damage();
  acterID = hwk->acterID;
  if (acterID != wk->playerID)
  {
    workID = hwk->workID;
    if (workID != -1)
      goto LABEL_10;
LABEL_14:
    hwk->skillid = workID;
    if ((wklock->side & 7) == 0)
      return 1;
    goto LABEL_15;
  }
  sBtlSetHitStop(10, 3);
  workID = hwk->workID;
  if (workID == -1)
    goto LABEL_14;
LABEL_10:
  if ((wklock->side & 7) == 0)
    return 1;
LABEL_15:
  if (hwk->BEDtype == 2)
  {
    p_huka2hwk = &wk->huka2hwk;
    p_huka2hwk = hwk;
    skillid = hwk->skillid;
    acterside = hwk->acterside;
    serialID2 = hwk->serialID2;
    v18 = 5;
    v19 = wklock;
    v20 = skillid;
LABEL_33:
    sBtlCheckEffectData(v19, v20, v18, 0, acterside, serialID2, StartTime_Damage);
    return 1;
  }
  v21 = hwk->type & 0xFFF;
  if (v21 != 4 && (v21 > 0xE || ((1 << LOBYTE(hwk->type)) & 0x7006) == 0))
    return 1;
  v23 = &wk->huka2hwk;
  v23 = hwk;
  v24 = hwk->skillid;
  acterside = hwk->acterside;
  serialID2 = hwk->serialID2;
  if (v24 != 151)
  {
    v19 = wklock;
    v20 = v24;
    v18 = 2;
    goto LABEL_33;
  }
  sBtlCheckEffectData_SeOnly(wklock, 151, 2u, 0, acterside, serialID2, StartTime_Damage);
  return 1;
}

// 0x205b320
void sBtlSetDeadWeak(SBTLUNIT_WORK *wk, SBTLSKILLP_TBL *ptbl, u32 attr) {
  s16 v4;
  s32 devilid;
  sdatUnitWork_t *para;

  v4 = attr;
  devilid = wk->para->devilid;
  sBtlSetWeakBit(devilid);
  sBtlSetHstatusWeakOld(wk);
  if (wk->actwk->status != 9 && (v4 & 0x4000) != 0 && (wk->side & 2) != 0)
  {
    para = wk->para;
    if (!sBtlIsKoufun(para))
    {
      sBtlSetHstatusWeak(wk);
      wk->aiwk->scrflag |= 0x400000u;
      sBtlSetWeakBit(wk->para->devilid);
      sBtlCreateSTP_Unit(wk->stpList, wk, 1, ptbl->attrtime, ptbl->badst, ptbl->attr);
    }
  }
}

// 0x204e5a0
bool sBtlSetDeadDamageProc(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, SBTLDMG_HITWORK *hwk, s32 damage, u32 attr) {
  SBTLSKILLP_TBL *Skilltbl;
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v16;
  s32 *EventBit;
  u32 status;
  SBTLDVLTK_LISTWORK *dvltkList;
  sdatUnitWork_t *para;
  s32 skillid;
  bool v29;
  s16 StartTime_Damage;
  s32 workID;
  s32 v34;
  SBTLDMG_HITWORK *p_huka2hwk;
  s32 v37;
  s32 acterside;
  s32 serialID2;
  u8 v40;
  SBTLUNIT_WORK *v41;
  s32 v42;
  s32 v43;
  u16 type;
  SBTLDMG_HITWORK *v46;
  s32 v47;
  sdfVector4_t HitEffectPos;

  Skilltbl = sBtlGetSkilltbl(hwk->skillid);
  acterID = hwk->acterID;
  UnitMng = wk->UnitMng;
  v16 = sBtlSearchUnit_ID(UnitMng, acterID);
  if (wk->encountno == 514 && !evtBitCheck(681) && wk->para->devilid == 476)
  {
    EventBit = GBWK->EventBit;
    EventBit[21] |= 0x200u;
    lmapSetBattleDestFlag(2);
  }
  status = wk->actwk->status;
  if ((attr & 0x4000) == 0)
  {
    if (status != 9)
    {
LABEL_30:
      goto LABEL_32;
    }
LABEL_21:
    dvltkList = wk->dvltkList;
    sBtlCreateDvltk_Priority(dvltkList, wk, 4);
    goto LABEL_32;
  }
  if (status == 9)
    goto LABEL_21;
  sBtlGetUnitHelperPos(wk, 2);
  goto LABEL_30;
LABEL_32:
  sBtlSetDeadWeak(wk, Skilltbl, attr);
  sBtlSetHstatusWeakOld(wk);
  if ((u32)sBtlCheckBadStatus(v16, wk, hwk->skillid, 1) <= 4 && wk->actwk->status != 9 && (wk->side & 2) != 0 && (wk->hstatus & 0x10) == 0)
  {
    para = wk->para;
    if (!sBtlIsKoufun(para))
    {
      sBtlSetHstatusWeak(wk);
      wk->aiwk->scrflag |= 0x400000u;
      sBtlSetWeakBit(wk->para->devilid);
      sBtlCreateSTP_Unit(wk->stpList, wk, 1, Skilltbl->attrtime, Skilltbl->badst, Skilltbl->attr);
    }
  }
  skillid = hwk->skillid;
  v29 = sBtlSetDeadDamage(wk, damage, skillid);
  sBtlSetHitback(wk, hwk, attr);
  StartTime_Damage = sBtlGetStartTime_Damage();
  workID = hwk->workID;
  if (workID != -1)
  {
    if ((wklock->side & 7) == 0)
      return v29;
    goto LABEL_54;
  }
  hwk->skillid = workID;
  if ((wklock->side & 7) == 0)
    return v29;
LABEL_54:
  v34 = StartTime_Damage;
  if (hwk->BEDtype == 2)
  {
    p_huka2hwk = &wk->huka2hwk;
    p_huka2hwk = hwk;
    v37 = hwk->skillid;
    acterside = hwk->acterside;
    serialID2 = hwk->serialID2;
    v40 = 5;
    v41 = wklock;
    v42 = v37;
    goto LABEL_79;
  }
  v43 = hwk->skillid;
  type = hwk->type;
  HitEffectPos = sBtlGetHitEffectPos(v43, wklock, v16);
  sBtlCheckYukaDamageEffect(wklock, v43, type, v34 + 1, 1, HitEffectPos, v16);
  if ((hwk->type & 0xFFFu) > 0xF || ((1 << LOBYTE(hwk->type)) & 0xFE3E) == 0)
  {
LABEL_72:
    if ((wk->side & 2) == 0)
      return v29;
    goto LABEL_80;
  }
  v46 = &wk->huka2hwk;
  v46 = hwk;
  v47 = hwk->skillid;
  acterside = hwk->acterside;
  serialID2 = hwk->serialID2;
  if (v47 == 151)
  {
    sBtlCheckEffectData_SeOnly(wklock, 151, 2u, 0, acterside, serialID2, v34);
    goto LABEL_72;
  }
  v41 = wklock;
  v42 = v47;
  v40 = 2;
LABEL_79:
  sBtlCheckEffectData(v41, v42, v40, 0, acterside, serialID2, v34);
  if ((wk->side & 2) == 0)
    return v29;
LABEL_80:
  if (!sBtlCheckLastEnemyDead(wk))
  {
    goto LABEL_82;
  }
  wk->hstatus |= 0x8000000u;
  wk->enemy_zenmetu = 1;
LABEL_82:
  if (!sBtlCheckSetsuma())
    return v29;
  wk->hstatus |= 0x10000000u;
  if ((wk->status & 0x40) == 0)
  {
    sBtlStatusBitOn(wk, 0x10u);
  }
  return v29;
}

// 0x204fad0
void sBtlSetInvalidDamage(SBTLUNIT_WORK *wk) {
  s32 StartTime_Damage;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  sdfVector4_t v10;

  if (!wk->eff_wait_mukou)
  {
    if (wk->bTateNoDmg)
    {
      goto LABEL_7;
    }
    wk->eff_wait_mukou = 20;
LABEL_7:
    StartTime_Damage = sBtlGetStartTime_Damage();
    sBtlCreateEff(wk->effList, wk, 20, StartTime_Damage, wk->pos, 0x80808080, 0, 1.0, 0);
    sBtlCreateSTP_Unit(wk->stpList, wk, 3, 0, 0, 0);
    x = wk->pos.x;
    y = wk->pos.y;
    z = wk->pos.z;
    w = wk->pos.w;
    v10.x = x;
    v10.y = y;
    v10.z = z;
    v10.w = w;
    sBtlPlayDamageSE(v10, 4);
    goto LABEL_11;
  }
LABEL_11:
  ++wk->mukou_damage_cnt;
}

// 0x2046e30
bool sBtlSetMukouDamage(SBTLUNIT_WORK *wk, u32 attr) {
  s32 StartTime_Damage;
  f32 v8;
  f32 v9;
  SBTLEFF_LISTWORK *v10;
  f32 v11;
  f32 v12;
  f32 x;
  f32 y;
  SBTLEFF_LISTWORK *effList;
  f32 z;
  f32 w;
  sdfVector4_t v20;
  sdfVector4_t v21;

  StartTime_Damage = sBtlGetStartTime_Damage();
  if (attr != 4096)
  {
    x = wk->pos.x;
    y = wk->pos.y;
    effList = wk->effList;
    z = wk->pos.z;
    w = wk->pos.w;
    v21.x = x;
    v21.y = y;
    v21.z = z;
    v21.w = w;
    sBtlCreateEff(effList, wk, 8, StartTime_Damage, v21, 0x80808080, 0, 1.0, 0);
    return 0;
  }
  if (wk->eff_wait_mukou)
    return 0;
  v8 = wk->pos.x;
  v9 = wk->pos.y;
  v10 = wk->effList;
  v11 = wk->pos.z;
  v12 = wk->pos.w;
  v20.x = v8;
  v20.y = v9;
  v20.z = v11;
  v20.w = v12;
  sBtlCreateEff(v10, wk, 20, StartTime_Damage, v20, 0x80808080, 0, 1.0, 0);
  ++wk->mukou_damage_cnt;
  return 1;
}

// 0x204f810
void sBtlSetAbsorbDamage(SBTLUNIT_WORK *wk, s32 damage, s32 addMag) {
  sdatParaWork_t *now;
  s32 hp;
  s32 *p_hp;
  s32 maxhp;
  SBTLUNIT_WORK *v13;
  s16 StartTime_Damage;
  s32 v18;
  SBATTLE_WORK *v20;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  SBTLEFF_LISTWORK *effList;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v30;
  sdfVector4_t v31;
  sdfVector4_t v32;

  if (damage >= 1)
  {
    now = wk->para->now;
    hp = now->hp;
    maxhp = now->maxhp;
    p_hp = &now->hp;
    *p_hp = hp + damage;
    LimitRange(p_hp, 0, maxhp);
    sBtlCreateAnim_Unit(wk, v13, damage, 0, 3, 0);
  }
  StartTime_Damage = sBtlGetStartTime_Damage();
  if (wk->eff_wait_kyushu)
    goto LABEL_11;
  LOWORD(v18) = StartTime_Damage;
  v20 = wk;
  if (v20->bTateNoDmg)
  {
    v18 = (s16)v18;
    goto LABEL_18;
  }
  wk->eff_wait_kyushu = 20;
  v18 = (s16)v18;
LABEL_18:
  x = wk->pos.x;
  y = wk->pos.y;
  z = wk->pos.z;
  w = wk->pos.w;
  effList = v20->effList;
  v31.x = x;
  v31.y = y;
  v31.z = z;
  v31.w = w;
  sBtlCreateEff(effList, wk, 21, v18, v31, 0x80808080, 0, 1.0, 0);
  sBtlCreateSTP_Unit(wk->stpList, wk, 4, 0, 0, 0);
  v27 = wk->pos.x;
  v28 = wk->pos.y;
  v30 = wk->pos.z;
  v29 = wk->pos.w;
  v32.x = v27;
  v32.y = v28;
  v32.z = v30;
  v32.w = v29;
  sBtlPlayDamageSE(v32, 5);
LABEL_11:
  sBtlSetAddMagAisyo(wk, addMag);
}

// 0x2059d30
void sBtlSetOnlyDamage(SBTLUNIT_WORK *wk, s32 damage, SBTLDMG_HITWORK *hwk) {
  s32 skillid;
  s32 side;
  s32 v11;

  skillid = hwk->skillid;
  sBtlCreateAnim_Unit(wk, *(SBTLUNIT_WORK *)&damage, damage, 0, 0, skillid);
  side = wk->side;
  if ((side & 0x80) != 0)
    goto LABEL_32;
  if ((side & 1) != 0)
  {
    if (wk->battlemode == 3)
    {
LABEL_32:
      sBtlSetVibe(5);
    }
  }
  v11 = wk->side;
  if ((v11 & 0x80) == 0)
  {
    if ((v11 & 1) == 0)
      return;
    if (wk->battlemode != 3)
      return;
  }
  if (QuakeFlag)
    return;
  dds3SetQuake(20, 0x28u);
}

// 0x2047fd0
void sBtlSetNormalDamage(SBTLUNIT_WORK *wk, s32 damage, u32 attr, SBTLDMG_HITWORK *hwk) {
  s32 skillid;
  s32 v12;
  s32 acterID;
  s32 v14;
  SBTLDMG_HITLISTWORK *hitList;
  SBTLEFF_LISTWORK *effList;
  SBTLACTAI_WORK *actaiwk;
  s32 v19;
  s32 v20;
  s32 side;
  s32 v23;
  dds3ModelHandle_t *hModel;
  s32 MotionFrame;
  s32 motionID;
  f32 v30;
  s32 v31;
  s32 v32;
  u32 v33;
  s32 v34;
  u32 status;
  s32 devilid;
  s32 v37;
  s32 v38;

  if (hwk)
  {
    skillid = hwk->skillid;
    sBtlCreateAnim_Unit(wk, *(SBTLUNIT_WORK *)&damage, damage, 0, 0, skillid);
    if (damage)
    {
      if ((attr & 0x3000) == 0)
      {
        v12 = hwk->skillid;
        if (v12)
        {
          if (sBtlGetSkilltbl(v12)->shild_dmg)
          {
            acterID = hwk->acterID;
            v14 = hwk->skillid;
            sBtlWeakShildActive(wk, attr, acterID, v14);
          }
        }
      }
    }
  }
  else
  {
    sBtlCreateAnim_Unit(wk, *(SBTLUNIT_WORK *)&damage, damage, 0, 0, 0);
  }
  if ((attr & 0x108000) == 0)
  {
    hModel = wk->hModel;
    MotionFrame = mdlGetMotionFrame(hModel);
    motionID = wk->motionID;
    v30 = 0.0;
    v31 = MotionFrame;
    if (motionID == 14)
    {
      if (!(u32)sub_1905740(2, 0))
      {
        v32 = sub_1905740(3, 0);
        if (v31 >= 10)
          goto LABEL_66;
        goto LABEL_92;
      }
    }
    else
    {
      if (motionID != 1)
      {
        v34 = 3;
        status = wk->actwk->status;
        if (status == 53)
          goto LABEL_68;
LABEL_67:
        if (status != 6)
        {
LABEL_71:
          if ((wk->side & 0x80) == 0)
            goto LABEL_76;
          if (!sBtlCheckSetsuma())
          {
LABEL_76:
            if (!hwk || hwk->skillid != 1319)
            {
              devilid = (u16)wk->para->devilid;
              if ((u32)(devilid - 263) > 0x27 || ((1 << ((u8)devilid - 7)) & 0x8080000001LL) == 0)
              {
                v37 = (s16)devilid;
                if ((u32)(v37 - 258) > 0x37 || ((1 << ((u8)v37 - 2)) & 0xC0000000000007LL) == 0)
                {
                  sBtlNewHirumiMotion(wk, v34);
                }
              }
              if (wk->motionID == 1)
                v38 = 7;
              else
                v38 = 8;
              sBtlSetAction(wk, v38, 0);
              if (v30 > 0.0)
              {
                sBtlCutMotion(wk, v30);
              }
            }
          }
          goto LABEL_17;
        }
LABEL_68:
        sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
        goto LABEL_71;
      }
      if (!(u32)sub_1905740(2, 0))
      {
        v32 = sub_1905740(3, 0);
        if (v31 <= 9)
          goto LABEL_92;
LABEL_66:
        v34 = v32;
        status = wk->actwk->status;
        if (status == 53)
          goto LABEL_68;
        goto LABEL_67;
      }
    }
    v33 = sub_1905740(8, 0);
    if (v31 > 9)
    {
      v34 = 0;
      v30 = v33;
      status = wk->actwk->status;
      if (status == 53)
        goto LABEL_68;
      goto LABEL_67;
    }
LABEL_92:
    sBtlSetHangekiFlag(wk);
  }
LABEL_17:
  hitList = wk->hitList;
  sBtlClearHitC(hitList, wk);
  effList = wk->effList;
  sBtlForceReset(effList, wk);
  actaiwk = wk->actaiwk;
  v19 = actaiwk->status;
  v20 = wk->vstatus | 0x80;
  wk->status |= 0x20u;
  wk->vstatus = v20;
  actaiwk->status = v19 & 0xFFFFFFDF;
  wk->actwk->gravcnt = 0;
  side = wk->side;
  if ((side & 0x80) != 0)
    goto LABEL_100;
  if ((side & 1) != 0)
  {
    if (wk->battlemode == 3)
    {
LABEL_100:
      sBtlSetVibe(6);
    }
  }
  v23 = wk->side;
  if ((v23 & 0x80) != 0)
    goto LABEL_101;
  if ((v23 & 1) != 0)
  {
    if (wk->battlemode == 3)
    {
LABEL_101:
      if (QuakeFlag)
      {
LABEL_39:
        sBtlResetJump(wk);
        goto LABEL_40;
      }
      dds3SetQuake(20, 0x28u);
      goto LABEL_39;
    }
  }
LABEL_40:
  if ((wk->side & 1) != 0)
    wk->hpGageDamageFlag = 1;
}

// 0x2059370
void sBtlSetHuttobiDamage(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *hwk, s32 damage, u32 attr) {
  sdatUnitWork_t *v10;
  sdatUnitWork_t *v11;
  bool v12;
  sdatUnitWork_t *v13;
  sdatUnitWork_t *v14;
  u32 v15;
  sdatUnitWork_t *v16;
  u32 status;
  sdatParaWork_t *now;
  signed s32 hp;
  s64 v20;
  s32 v21;
  sdatUnitWork_t *para;
  sdatUnitWork_t *v24;
  sdatUnitWork_t *v25;
  SBTLDMG_HITLISTWORK *hitList;
  SBTLEFF_LISTWORK *effList;
  s32 skillid;
  SBTLUNIT_WORK *v31;
  sdfVector4_t *p_mv_spd;
  SBTLACTION_WORK *actwk;
  s32 side;
  s32 v40;

  if (wk->actwk->status != 9)
  {
    if ((attr & 0x4000) == 0)
    {
      if ((attr & 0x40000) != 0)
      {
LABEL_55:
        para = wk->para;
        if (sBtlGetBadStatus(wk->para) == 9)
          goto LABEL_77;
        v24 = wk->para;
        if (!sBtlIsKoufun(v24))
        {
          sBtlSetAction(wk, 8, 0);
        }
        goto LABEL_77;
      }
      v10 = wk->para;
      if (sBtlGetBadStatus(wk->para) == 9)
      {
        v16 = wk->para;
        if (sBtlIsKoufun(v16))
          goto LABEL_55;
      }
      status = wk->actwk->status;
      if (status == 53 || status == 6)
      {
        sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
      }
      if (hwk->skillid == 1319)
        goto LABEL_55;
LABEL_42:
      if (wk->battlemode != 3)
      {
        if ((~wk->side & 0x81) == 0)
        {
          now = wk->para->now;
          hp = now->hp;
          v20 = 68719476750LL * now->maxhp;
          if (hp <= (s32)((v20 >> 37) + ((u64)v20 >> 63)))
            v21 = 14;
          else
            v21 = 131;
          goto LABEL_54;
        }
      }
      v21 = 14;
LABEL_54:
      sBtlSetMotion(wk, v21, 0, 0, 0);
      goto LABEL_55;
    }
    v11 = wk->para;
    if (sBtlGetBadStatus(wk->para) != 9)
      goto LABEL_27;
    goto LABEL_9000;
    if (sBtlGetBadStatus(v11) != 9)
    {
LABEL_27:
      v15 = wk->actwk->status;
      if (v15 == 53 || v15 == 6)
      {
        sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
      }
      goto LABEL_42;
    }
LABEL_9000:
    v14 = wk->para;
    if (sBtlIsKoufun(v14))
      goto LABEL_55;
    goto LABEL_27;
  }
  if (!sBtlCheckSetsuma())
    goto LABEL_77;
  v12 = sBtlCheckSetsumaEnd();
  if ((attr & 0x40000) == 0 && !v12)
  {
    v13 = wk->para;
    if (sBtlGetBadStatus(wk->para) != 9)
    {
LABEL_69:
      if (hwk->skillid != 1319)
      {
        if (wk->battlemode == 3 || (~wk->side & 0x81) != 0)
        {
          sBtlSetMotion(wk, 14, 0, 0, 0);
        }
      }
      goto LABEL_77;
    }
    v25 = wk->para;
    if (!sBtlIsKoufun(v25))
      goto LABEL_69;
  }
LABEL_77:
  hitList = wk->hitList;
  sBtlClearHitC(hitList, wk);
  effList = wk->effList;
  sBtlForceReset(effList, wk);
  skillid = hwk->skillid;
  wk->huttobiID = hwk->acterID;
  sBtlCreateAnim_Unit(wk, v31, damage, 0, 0, skillid);
  wk->status |= 0x20u;
  wk->vstatus |= 0x80u;
  wk->actwk->gravcnt = 0;
  *(u64 *)&vct_A.x = 0;
  *(u64 *)&vct_A.z = 0;
  p_mv_spd = &wk->mv_spd;
  actwk = wk->actwk;
  *p_mv_spd = vct_A;
  actwk->counter = 0;
  side = wk->side;
  if ((side & 0x80) != 0)
    goto LABEL_121;
  if ((side & 1) != 0)
  {
    if (wk->battlemode == 3)
    {
LABEL_121:
      sBtlSetVibe(7);
    }
  }
  v40 = wk->side;
  if ((v40 & 0x80) == 0)
  {
    if ((v40 & 1) == 0)
      return;
    if (wk->battlemode != 3)
      return;
  }
  if (QuakeFlag)
  {
LABEL_103:
    sBtlResetJump(wk);
    return;
  }
  dds3SetQuake(25, 0x41u);
  goto LABEL_103;
}

// 0x205b660
void sBtlSetBomDamage(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *hwk, s32 damage, u32 attr) {
  sdatUnitWork_t *v9;
  sdatUnitWork_t *para;
  sdatUnitWork_t *v11;
  sdatUnitWork_t *v12;
  u32 status;
  sdatUnitWork_t *v14;
  sdatUnitWork_t *v15;
  SBTLDMG_HITLISTWORK *hitList;
  SBTLEFF_LISTWORK *effList;
  s32 skillid;
  SBTLUNIT_WORK *v20;
  sdfVector4_t *p_mv_spd;
  SBTLACTION_WORK *actwk;
  s32 side;
  s32 v29;

  if (wk->actwk->status == 9)
    goto LABEL_44;
  if ((attr & 0x4000) != 0)
  {
    para = wk->para;
    if (sBtlGetBadStatus(wk->para) != 9)
      goto LABEL_21;
    v11 = wk->para;
    if (sBtlIsKoufun(v11))
      goto LABEL_34;
    goto LABEL_21;
  }
  if ((attr & 0x40000) != 0)
    goto LABEL_34;
  v9 = wk->para;
  if (sBtlGetBadStatus(wk->para) != 9)
    goto LABEL_21;
  v12 = wk->para;
  if (sBtlIsKoufun(v12))
    goto LABEL_26;
LABEL_21:
  status = wk->actwk->status;
  if (status == 53 || status == 6)
  {
    sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
  }
LABEL_26:
  if (wk->battlemode == 3)
    goto LABEL_34;
  if ((~wk->side & 0x81) == 0)
  {
    sBtlSetMotion(wk, 14, 0, 0, 0);
  }
LABEL_34:
  v14 = wk->para;
  if (sBtlGetBadStatus(wk->para) != 9)
    goto LABEL_41;
  goto LABEL_9000;
  if (sBtlGetBadStatus(v14) != 9)
  {
LABEL_41:
    sBtlSetAction(wk, 8, 0);
    goto LABEL_44;
  }
LABEL_9000:
  v15 = wk->para;
  if (!sBtlIsKoufun(v15))
    goto LABEL_41;
LABEL_44:
  hitList = wk->hitList;
  sBtlClearHitC(hitList, wk);
  effList = wk->effList;
  sBtlForceReset(effList, wk);
  skillid = hwk->skillid;
  wk->huttobiID = hwk->acterID;
  sBtlCreateAnim_Unit(wk, v20, damage, 0, 0, skillid);
  wk->status |= 0x20u;
  wk->vstatus |= 0x80u;
  wk->actwk->gravcnt = 0;
  *(u64 *)&vct_A.x = 0;
  *(u64 *)&vct_A.z = 0;
  p_mv_spd = &wk->mv_spd;
  actwk = wk->actwk;
  *p_mv_spd = vct_A;
  actwk->counter = 0;
  side = wk->side;
  if ((side & 0x80) != 0)
    goto LABEL_88;
  if ((side & 1) != 0)
  {
    if (wk->battlemode == 3)
    {
LABEL_88:
      sBtlSetVibe(7);
    }
  }
  v29 = wk->side;
  if ((v29 & 0x80) == 0)
  {
    if ((v29 & 1) == 0)
      return;
    if (wk->battlemode != 3)
      return;
  }
  if (QuakeFlag)
  {
LABEL_70:
    sBtlResetJump(wk);
    return;
  }
  dds3SetQuake(25, 0x41u);
  goto LABEL_70;
}

// 0x205bca0
static s32 GetKouchoku(SBTLUNIT_WORK *wk, SKLID sklid) {
  s32 attrtime;
  s32 v6;
  s32 HaveMemSklParty;
  s32 v8;
  f32 v9;
  s16 para2[2];
  s16 para1;

  attrtime = sBtlGetSkilltbl(sklid)->attrtime;
  para1 = 0;
  para2[0] = 0;
  if ((wk->side & 2) != 0)
  {
    v6 = 3 * attrtime;
    attrtime = v6 >> 1;
    HaveMemSklParty = sBtlChkHaveMemSklParty(30);
    if (HaveMemSklParty)
    {
      v8 = HaveMemSklParty;
      sBtlGetAutoSkillPara(v8, &para1, para2);
      v9 = (f32)((f32)para2[0] / 100.0) * (f32)attrtime;
      if (v9 == INFINITY)
        attrtime = 0x80000000;
      else
        attrtime = v9;
    }
  }
  return sBtlCalcWeakTime(wk, attrtime);
}

// 0x2058630
void sBtlSetDyingDamage(SBTLUNIT_WORK *wk, SKLID sklid, s32 damage, u32 attr, s32 acterID) {
  s16 v7;
  SBTLSKILLP_TBL *Skilltbl;
  s32 Kouchoku;
  SBTLUNIT_WORK *v14;
  s32 side;
  s32 attrtime;
  SBTLEXP_LISTWORK *expList;
  SBTLEXP_LISTWORK *v20;
  SBTLUNIT_WORK *v21;
  s32 v22;
  s32 v23;
  s32 v24;
  sdatUnitWork_t *v25;
  u32 BadStatus;
  sdatUnitWork_t *v27;
  SBTLUNIT_WORK *PChara;
  SBTLUNIT_WORK *v30;
  sdatUnitWork_t *v31;
  u32 v32;
  SBTLACTION_WORK *actwk;
  s32 devilid;
  u16 major;
  s32 minor;
  MOTIONDATA_WORK *mwk;
  MOTIONDATA_WORK *v38;
  s32 v39;
  u32 v40;
  f32 v41;
  s32 v42;
  s16 v43;
  sdatUnitWork_t *para;
  sdatUnitWork_t *v45;
  sdatUnitWork_t *v49;
  s32 v50;
  SBTLUNIT_WORK *v52;
  s32 v53;
  sdatUnitWork_t *v54;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v58;
  SBTLDVLTK_LISTWORK *dvltkList;
  s32 magMax;
  SBTLUNIT_LISTWORK *v63;
  SBTLUNIT_WORK *v64;
  HpCallCtrl *hpCallCtrl;
  s64 v66;
  s32 *EventBit;
  SBTLEFF_LISTWORK *effList;
  SBTLACTAI_WORK *actaiwk;
  s32 status;
  s32 v75;
  SBTLEXP_LISTWORK *v77;

  v7 = attr;
  Skilltbl = sBtlGetSkilltbl(sklid);
  Kouchoku = GetKouchoku(wk, sklid);
  side = wk->side;
  attrtime = Kouchoku;
  if ((side & 2) == 0)
  {
    if ((side & 0x80) == 0)
    {
      sBtlSetHstatusWeakOld(wk);
      if (wk->actwk->status == 9)
      {
        if ((wk->side & 1) != 0)
        {
          expList = wk->expList;
          v20 = expList;
          v21 = wk;
          v22 = sklid;
          v23 = acterID;
          v24 = 4;
LABEL_16:
          sBtlSetRirituEnemyHD(v20, v21, v22, v23, v24);
        }
      }
      else
      {
        sBtlSetMotion(wk, 1, 0, 0, 0);
        para = wk->para;
        if (!sBtlIsKoufun(para))
        {
          sBtlSetAction(wk, 9, attrtime);
        }
        if ((v7 & 0x4000) != 0)
        {
          v45 = wk->para;
          if (!sBtlIsKoufun(v45))
          {
            sBtlSetHstatusWeak(wk);
            wk->weak_shild_next = 1;
            sBtlCreateSTP_Unit(wk->stpList, wk, 1, attrtime, Skilltbl->badst, Skilltbl->attr);
            if ((wk->side & 1) != 0)
            {
              v77 = wk->expList;
              sBtlSetRirituNakamaHD(v77, wk, sklid, acterID, 0x14u);
              v24 = 5;
              v21 = wk;
              v22 = sklid;
              v23 = acterID;
              v20 = wk->expList;
              goto LABEL_16;
            }
          }
        }
      }
      if ((wk->side & 1) == 0)
        goto LABEL_180;
      if (wk->battlemode != 3)
        goto LABEL_180;
LABEL_110:
      sBtlSetVibe(8);
      if (QuakeFlag)
        goto LABEL_180;
      dds3SetQuake(25, 0x41u);
      goto LABEL_180;
    }
    if (!Kouchoku)
      goto LABEL_180;
    v27 = wk->para;
    if (sBtlGetBadStatus(wk->para) == 6)
      goto LABEL_23;
    goto LABEL_9001;
    if (sBtlGetBadStatus(v27) == 6)
    {
LABEL_23:
      if (wk->actwk->status == 9)
        goto LABEL_110;
      goto LABEL_104;
    }
LABEL_9001:
    sBtlSetMotion(wk, 1, 0, 0, 0);
    sBtlResetJump(wk);
    if (wk->actwk->status == 9)
      goto LABEL_110;
LABEL_104:
    v54 = wk->para;
    if (!sBtlIsKoufun(v54))
    {
      sBtlSetAction(wk, 9, attrtime);
    }
    goto LABEL_110;
  }
  v25 = wk->para;
  BadStatus = sBtlGetBadStatus(wk->para);
  if ((v7 & 0x4000) != 0)
  {
    if (BadStatus == 14 && !wk->weak_shild)
    {
      sBtlResetBadStatus(wk, 0x4000);
      sBtlSetHstatusWeakOld(wk);
      goto LABEL_85;
    }
  }
  sBtlSetHstatusWeakOld(wk);
  if (wk->actwk->status == 9)
  {
    if ((v7 & 0x4000) != 0)
    {
      PChara = sBtlGetPChara();
      sBtlSpiritAddDirect(PChara, 11);
    }
    v30 = sBtlGetPChara();
    sBtlSpiritAddDirect(v30, 5);
    v31 = wk->para;
    v32 = sBtlGetBadStatus(v31);
    actwk = wk->actwk;
    if (actwk->status != 9 || actwk->action_flg || v32 == 6)
    {
      wk->motion_WeakDmg2 = 0;
    }
    else if (sklid != 1319)
    {
      devilid = wk->para->devilid;
      if (devilid != 294)
      {
        if ((u32)(devilid - 258) > 0x37 || ((1 << ((u8)devilid - 2)) & 0xC0000000000007LL) == 0)
        {
          major = wk->major;
          minor = wk->minor;
          mwk = sBtlGetVisualData(major, minor)->mwk;
          wk->actwk->framecntB = 0;
          v38 = mwk[4];
          wk->m_rate = 0.5;
          wk->next_motion_not_hokan = 1;
          wk->motion_SeSkep = 1;
          v39 = sub_1905740(5, 0);
          v40 = ~(u32)sub_1905740(2, 0);
          v41 = v38->m_stoprate + (f32)v39;
          v42 = v41;
          if (v41 == INFINITY)
            LOWORD(v42) = 0;
          wk->motion_WeakStopF = v42;
          v43 = v40 + v42;
          if (v43 < 0)
            v43 = 0;
          wk->motion_FrameSkip = v43;
          sBtlSetMotion(wk, 1, 0, 0, 0);
          ++wk->motion_WeakDmg2;
        }
      }
    }
    goto LABEL_180;
  }
LABEL_85:
  sBtlNewHirumiMotion(wk, 3);
  if (wk->weak_shild)
    goto LABEL_91;
  v49 = wk->para;
  if (sBtlIsKoufun(wk->para))
    goto LABEL_91;
  if ((wk->side & 2) == 0)
  {
LABEL_138:
    if ((v7 & 0x4000) != 0 && (wk->side & 2) != 0)
      attrtime = Skilltbl->attrtime;
    sBtlSetAction(wk, 9, attrtime);
    if ((v7 & 0x4000) != 0)
    {
      sBtlSetHstatusWeak(wk);
      wk->weak_shild_next = 1;
      wk->aiwk->scrflag |= 0x400000u;
      sBtlCreateSTP_Unit(wk->stpList, wk, 1, attrtime, Skilltbl->badst, Skilltbl->attr);
      UnitMng = wk->UnitMng;
      v58 = sBtlSearchUnit_ID(UnitMng, acterID);
      dvltkList = wk->dvltkList;
      sBtlCreateDvltk_Priority(dvltkList, v58, 4);
      if (sBtlGetSpiritSkillChk(1451))
      {
        magMax = wk->magMax;
        sBtlAddMag(magMax / 10);
      }
      if ((wk->side & 2) != 0)
      {
        sBtlSpiritAddDirect(v58, 11);
        v63 = wk->UnitMng;
        v64 = sBtlSearchUnit_ID(v63, acterID);
        CallSign(v64->hpCallCtrl, 1, 1, 0);
        hpCallCtrl = v64->hpCallCtrl;
        wk->weekAct = hpCallCtrl;
        if (wk->encountno == 514 && sklid == 8 && wk->para->devilid == 476)
        {
          sub_1A21FE0(681, 0, v66);
        }
      }
    }
    goto LABEL_169;
  }
  if (wk->BossXAtk)
  {
    DeleteAll_BossDYING(wk);
    wk->BossXAtk = 0;
  }
  goto LABEL_138;
LABEL_91:
  v50 = (u16)wk->para->devilid;
  if ((v50 == 310 || v50 == 267) && wk->actwk->status == 2)
  {
    if (wk->motionID == 1)
    {
      v52 = wk;
      v53 = 7;
    }
    else
    {
      v52 = wk;
      v53 = 8;
    }
    sBtlSetAction(v52, v53, 0);
  }
LABEL_169:
  if ((v7 & 0x4000) != 0 && wk->encountno == 517 && (wk->side & 2) != 0 && wk->para->devilid == 475)
  {
    EventBit = GBWK->EventBit;
    EventBit[21] |= 0x20u;
  }
LABEL_180:
  sBtlCreateAnim_Unit(wk, v14, damage, 0, 0, sklid);
  sBtlClearHitC(wk->hitList, wk);
  effList = wk->effList;
  sBtlForceReset(effList, wk);
  actaiwk = wk->actaiwk;
  status = actaiwk->status;
  v75 = wk->vstatus | 0x80;
  wk->status |= 0x20u;
  wk->vstatus = v75;
  actaiwk->status = status & 0xFFFFFFDF;
  wk->actwk->gravcnt = 0;
}

// 0x2059cb0
void sBtlDmg_BossDYING(SBTLUNIT_WORK *wk) {
  if (wk && (wk->side & 2) != 0 && wk->BossXAtk)
  {
    DeleteAll_BossDYING(wk);
    wk->BossXAtk = 0;
  }
}

// 0x205aa20
void sBtlSetStoneDeadDamage(SBTLUNIT_WORK *wk, s32 damage) {
  s32 devilid;
  void *Instance;
  SBATTLE_WORK *v11;
  SBTLSM_LISTWORK *sysmsgList;
  s32 v14;
  bool v15;
  SBTLSM_LISTWORK *v18;
  SBTLUNIT_WORK *v19;
  SBTLSM_LISTWORK *v21;
  sdatUnitWork_t *para;
  f32 x;
  f32 y;
  SBTLEFF_LISTWORK *effList;
  f32 z;
  f32 w;
  SBTLDMG_HITLISTWORK *hitList;
  SBTLEFF_LISTWORK *v36;
  SBTLACTION_WORK *actwk;
  SBTLDVLTK_LISTWORK *dvltkList;
  f32 v40;
  f32 v41;
  f32 v42;
  f32 v43;
  sdatUnitWork_t *v44;
  SBTLSM_LISTWORK *v47;
  u32 level;
  s32 v50;
  sdfVector4_t v51;
  sdfVector4_t v52;

  sBtlDeath(wk);
  devilid = wk->para->devilid;
  sBtlSetWeakBit(devilid);
  sBtlGetStartTime_Damage();
  if ((wk->side & 0x80) != 0)
  {
    sBtlResetAction(wk);
    sBtlSetMotion(wk, 13, 0, 0, 0);
    sBtlSetAction(wk, 34, 0);
    sBtlResetJump(wk);
    Instance = get_Instance(0);
    ClrCallMark(Instance, 0);
    v11 = wk;
    if (v11->battlemode == 3)
    {
      sysmsgList = v11->sysmsgList;
      v14 = 71;
LABEL_39:
      v18 = sysmsgList;
      v19 = wk;
      goto LABEL_48;
    }
    v15 = sBtlCheckTutorialBattle();
    if (v15)
    {
      sysmsgList = wk->sysmsgList;
      v14 = 73;
      goto LABEL_39;
    }
    v21 = wk->sysmsgList;
    v18 = v21;
    v19 = wk;
    v14 = 4;
LABEL_48:
    sBtlCreateSM(v18, v19, v14, 0, 0, 120);
    goto LABEL_50;
  }
  sBtlSetMotion(wk, 13, 0, 0, 0);
  sBtlSetAction(wk, 10, 0);
  if ((wk->side & 1) != 0)
  {
    if (wk->battlemode == 3)
    {
LABEL_50:
      sBtlSetVibe(9);
      if (QuakeFlag)
        goto LABEL_61;
      dds3SetQuake(25, 0x41u);
      goto LABEL_61;
    }
  }
LABEL_61:
  para = wk->para;
  wk->actwk->action_flg = 0;
  para->now->hp = 0;
  sBtlSetFade(wk, 1026, 0, 0, 128);
  wk->color = 0;
  x = wk->pos.x;
  y = wk->pos.y;
  effList = wk->effList;
  z = wk->pos.z;
  w = wk->pos.w;
  v51.x = x;
  v51.y = y;
  v51.z = z;
  v51.w = w;
  sBtlCreateEff(effList, wk, 12, 0, v51, 0x80808080, 0, 1.0, 0);
  if ((wk->side & 0x81) != 1)
  {
    goto LABEL_69;
  }
  v47 = wk->sysmsgList;
  sBtlCreateSM(v47, wk, 71, 0, 0, 120);
LABEL_69:
  hitList = wk->hitList;
  sBtlClearHitC(hitList, wk);
  v36 = wk->effList;
  sBtlForceReset(v36, wk);
  wk->status |= 0x21u;
  actwk = wk->actwk;
  actwk->gravcnt = 0;
  actwk->action_flg = 0;
  *(int8x8_t *)&wk->vstatus = vorr_s8(*(int8x8_t *)&wk->vstatus, (int8x8_t)0x10000000080LL);
  sBtlCheckResetBadStatus(wk);
  sBtlSetBadStatus_No(wk, 0, 0x11u, 0, -1);
  dds3ObjectBaseOffFlag(&wk->pBasic, 0x400u);
  dvltkList = wk->dvltkList;
  sBtlCreateDvltk_Priority(dvltkList, wk, 15);
  v40 = wk->pos.x;
  v41 = wk->pos.y;
  v42 = wk->pos.z;
  v43 = wk->pos.w;
  v52.x = v40;
  v52.y = v41;
  v52.z = v42;
  v52.w = v43;
  sBtlPlay3DSE(0x10073u, v52);
  sBtlForceDelete_ID_Acter(wk->effList, wk, 55);
  if ((wk->side & 2) != 0)
  {
    datSetKillDevil(wk->para->devilid);
    v44 = wk->para;
    gohKarteRegistDevilBtl(v44, GBWK->karte_list, 1, 0);
    sBtlDeadFlagOn(wk);
    if ((wk->side & 2) == 0)
      return;
    if ((wk->status & 0x100000) == 0 && sBtlGetPChara())
    {
      level = (u8)wk->para->level;
      if (level < 4)
        v50 = 1;
      else
        v50 = (char)level >> 2;
      sBtlSetAddMag(wk, v50);
    }
  }
}

// 0x205bdf0
bool CheckAutoSkill(SBTLUNIT_WORK *wk) {
  sdatUnitWork_t *para;
  s32 AutoSkill_ID;
  sdatUnitWork_t *v5;
  sdatUnitWork_t *v6;
  sdatUnitWork_t *v7;
  sdatUnitWork_t *v8;
  sdatUnitWork_t *v9;
  sdatUnitWork_t *v10;
  sdatUnitWork_t *v11;
  signed s16 Percentage;
  SBATTLE_WORK *v14;
  s32 hstatus;
  s32 side;
  s16 *summonindex;
  s32 v19;
  s32 v21;
  u32 *p_deadbombBit;
  s32 badstatus;
  SBTLACTAI_WORK *actaiwk;

  para = wk->para;
  AutoSkill_ID = sBtlGetAutoSkill_ID(para, 0);
  if (sBtlGetAutoSkillPara(AutoSkill_ID, &wk->para->autost_cnt, &wk->para->autost_cnt2) != 1)
  {
    v5 = wk->para;
    AutoSkill_ID = sBtlGetAutoSkill_ID(v5, 1);
    if (sBtlGetAutoSkillPara(AutoSkill_ID, &wk->para->autost_cnt, &wk->para->autost_cnt2) != 1)
    {
      v6 = wk->para;
      AutoSkill_ID = sBtlGetAutoSkill_ID(v6, 2);
      if (sBtlGetAutoSkillPara(AutoSkill_ID, &wk->para->autost_cnt, &wk->para->autost_cnt2) != 1)
      {
        v7 = wk->para;
        AutoSkill_ID = sBtlGetAutoSkill_ID(v7, 3);
        if (sBtlGetAutoSkillPara(AutoSkill_ID, &wk->para->autost_cnt, &wk->para->autost_cnt2) != 1)
        {
          v8 = wk->para;
          AutoSkill_ID = sBtlGetAutoSkill_ID(v8, 4);
          if (sBtlGetAutoSkillPara(AutoSkill_ID, &wk->para->autost_cnt, &wk->para->autost_cnt2) != 1)
          {
            v9 = wk->para;
            AutoSkill_ID = sBtlGetAutoSkill_ID(v9, 5);
            if (sBtlGetAutoSkillPara(AutoSkill_ID, &wk->para->autost_cnt, &wk->para->autost_cnt2) != 1)
            {
              v10 = wk->para;
              AutoSkill_ID = sBtlGetAutoSkill_ID(v10, 6);
              if (sBtlGetAutoSkillPara(AutoSkill_ID, &wk->para->autost_cnt, &wk->para->autost_cnt2) != 1)
              {
                v11 = wk->para;
                AutoSkill_ID = sBtlGetAutoSkill_ID(v11, 7);
                if (sBtlGetAutoSkillPara(AutoSkill_ID, &wk->para->autost_cnt, &wk->para->autost_cnt2) != 1)
                  return 1;
              }
            }
          }
        }
      }
    }
  }
  Percentage = GetPercentage();
  v14 = wk;
  if (v14->NotSinaba_Cnt)
    return 1;
  v14 = wk;
  if ((v14->status3 & 0x4000) != 0 || Percentage > 79)
    return 1;
  v14->NotSinaba_Cnt = 30;
  hstatus = wk->hstatus;
  if ((hstatus & 0x800) == 0)
    return 1;
  wk->hstatus = hstatus & 0xFFFFF7FF;
  side = wk->side;
  if ((side & 0x81) == 1)
  {
    summonindex = v14->summonindex;
    v19 = summonindex[0] & ~(summonindex[0] >> 31);
    v21 = summonindex[wk->ListID != v14->summonID[(u16)v19]];
    v14 = wk;
    p_deadbombBit = &v14->deadbombBit;
    sBtlSetBit(p_deadbombBit, v21);
    side = wk->side;
  }
  if ((side & 2) != 0)
  {
    sBtlSetUseSkill(wk, AutoSkill_ID, 0);
    actaiwk = wk->actaiwk;
    actaiwk->stat = 1;
    wk->aiwk->stat = 2;
    actaiwk->mode = 14;
    return 0;
  }
  else
  {
    badstatus = wk->para->badstatus;
    sBtlResetBadStatus(wk, badstatus);
    ResetAction(wk, 0, 0);
    sBtlSetSkillData_AI(wk, AutoSkill_ID);
    sBtlSetUseSkill(wk, AutoSkill_ID, 0);
    return 0;
  }
}

// 0x205c360
bool sBtlIsEnemyLastOne(SBTLUNIT_WORK *wk) {
  bool v4;
  s64 v6;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  SBTLUNIT_WORK *pUnit;
  bool v11;

  if (sBtlCheckGeneratorAll())
    return 0;
  if (sBtlCheckGenerator_ND())
    return 0;
  v6 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    number = UnitMng->number;
    v4 = v6 >= number;
    if (v6 >= number)
      break;
    UnitMng = wk->UnitMng;
    pUnit = UnitMng->pUnitL[v6]->pUnit;
    v11 = !pUnit || pUnit == wk;
    if (!v11 && (pUnit->side & 2) != 0 && pUnit->para->now->hp > 0)
      break;
    ++v6;
  }
  return v4;
}

// 0x2056a70
bool sBtlSetDeadDamage(SBTLUNIT_WORK *wk, s32 damage, SKLID _SklId) {
  s32 devilid;
  s32 side;
  s32 hstatus;
  bool v10;
  u32 v12;
  SBTLUNIT_WORK *v14;
  bool v16;
  SBATTLE_WORK *v18;
  SBTLSM_LISTWORK *sysmsgList;
  s32 v21;
  u32 v23;
  void *Instance;
  bool v25;
  SBTLSM_LISTWORK *v28;
  SBTLUNIT_WORK *v29;
  SBTLACTION_WORK *actwk;
  _BOOL4 v32;
  SBTLSM_LISTWORK *v35;
  SBTLACTION_WORK *v42;
  SBTLSM_LISTWORK *v44;
  SBTLEFF_LISTWORK *effList;
  SBTLACTION_WORK *v48;
  u32 v49;
  _BOOL4 v51;
  u32 status;
  s32 v54;
  u32 v55;
  SBTLDVLTK_LISTWORK *dvltkList;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  SBTLEFF_LISTWORK *v62;
  sdatUnitWork_t *para;
  u32 setumaCnt;
  dds3SystemWork_t *v68;
  u32 devilKillCnt;
  void *v71;
  Project_DefineAchievementID_string__c *v72;
  s64 v73;
  Project_DefineAchievementID_string__c **v74;
  s64 v75;
  void *achievementTbl_k__BackingField;
  Project_DefineAchievementID_string__c *klass;
  s64 v79;
  Project_DefineAchievementID_string__c **p_offset;
  s64 v81;
  char *v82;
  s32 level;
  s32 v86;
  u32 v87;
  char *v89;
  void *v91;
  Project_DefineAchievementID_string__c *v92;
  s64 v93;
  Project_DefineAchievementID_string__c **v94;
  s64 v95;
  char *v96;
  void *v98;
  Project_DefineAchievementID_string__c *v99;
  s64 v100;
  Project_DefineAchievementID_string__c **v101;
  s64 v102;
  char *v103;
  s32 v104;
  sdfVector4_t v105;

  devilid = wk->para->devilid;
  sBtlSetWeakBit(devilid);
  sBtlDeath(wk);
  sBtlGetStartTime_Damage();
  side = wk->side;
  if ((side & 0x80) != 0)
  {
    if (sBtlCheckSetsuma())
    {
      goto LABEL_34;
    }
    sBtlResetAction(wk);
    sBtlSetMotion(wk, 13, 0, 0, 0);
    sBtlSetAction(wk, 34, 0);
    sBtlResetJump(wk);
    Instance = get_Instance(0);
    ClrCallMark(Instance, 0);
LABEL_34:
    v18 = wk;
    if (v18->battlemode == 3)
    {
      sysmsgList = v18->sysmsgList;
      v21 = 71;
LABEL_65:
      v28 = sysmsgList;
      v29 = wk;
      goto LABEL_88;
    }
    v25 = sBtlCheckTutorialBattle();
    if (v25)
    {
      sysmsgList = wk->sysmsgList;
      v21 = 73;
      goto LABEL_65;
    }
    v35 = wk->sysmsgList;
    v28 = v35;
    v29 = wk;
    v21 = 4;
LABEL_88:
    sBtlCreateSM(v28, v29, v21, 0, 0, 120);
    sBtlSetVibe(10);
    if (!QuakeFlag)
      dds3SetQuake(25, 0x41u);
    v32 = 0;
    v16 = 1;
    if ((wk->side & 0x81) != 1)
      goto LABEL_124;
    goto LABEL_117;
  }
  if ((side & 1) != 0)
  {
    sBtlSetMotion(wk, 13, 0, 0, 0);
    if (fldGb->nakamaMode)
    {
      if (!v23)
      sBtlSetAction(wk, 34, 0);
      v16 = 1;
      if ((wk->side & 1) == 0)
        goto LABEL_116;
    }
    else
    {
      if (!v23)
      sBtlSetAction(wk, 10, 0);
      v16 = CheckAutoSkill(wk);
      if ((wk->side & 1) == 0)
        goto LABEL_116;
    }
    if (wk->battlemode != 3)
      goto LABEL_116;
    sBtlSetVibe(10);
    if (QuakeFlag)
      goto LABEL_116;
    dds3SetQuake(25, 0x41u);
    v32 = 0;
    if ((wk->side & 0x81) == 1)
      goto LABEL_117;
    goto LABEL_124;
  }
  if ((wk->aiwk->scrflag & 0x20000) == 0)
  {
    if ((side & 2) != 0)
    {
      hstatus = wk->hstatus;
      if ((hstatus & 0x8000000) == 0)
      {
        v10 = sBtlCheckLastEnemyDead(wk);
        hstatus = wk->hstatus;
        if (v10)
        {
          hstatus |= 0x8000000u;
          wk->hstatus = hstatus;
          hstatus = wk->hstatus;
          wk->enemy_zenmetu = 1;
        }
      }
      if ((hstatus & 0x10000000) == 0)
      {
        if (sBtlCheckSetsuma())
        {
          wk->hstatus |= 0x10000000u;
          if ((wk->status & 0x40) == 0)
          {
            sBtlStatusBitOn(wk, 0x10u);
          }
        }
      }
    }
    v12 = ((u32)wk->hstatus >> 27) & 1;
    sBtlSetMotion(wk, 13, 1, 0, v12);
    wk->actwk->action_flg = 0;
    sBtlSetAction(wk, 10, 0);
    v16 = CheckAutoSkill(wk);
    if ((wk->side & 2) != 0)
    {
      v32 = (wk->status & 0x100000) == 0;
      if ((wk->side & 0x81) != 1)
        goto LABEL_124;
      goto LABEL_117;
    }
LABEL_116:
    v32 = 0;
    if ((wk->side & 0x81) != 1)
      goto LABEL_124;
    goto LABEL_117;
  }
  if ((wk->hstatus & 0x8000000) == 0)
  {
    if (!sBtlCheckLastEnemyDead(wk))
    {
      v104 = (u16)wk->para->devilid;
      if (wk->para->devilid <= 273)
      {
        if (v104 != 267 && v104 != 273)
          goto LABEL_71;
      }
      else if (v104 != 310 && v104 != 299)
      {
        goto LABEL_71;
      }
    }
    wk->hstatus |= 0x8000000u;
    wk->enemy_zenmetu = 1;
  }
LABEL_71:
  sBtlSetAction(wk, 10, 0);
  actwk = wk->actwk;
  v32 = 0;
  v16 = 1;
  actwk->action_flg = 0;
  actwk->framecnt = 0;
  actwk->total_homing = 0.0;
  actwk->no_homing = 0;
  if ((wk->side & 0x81) == 1)
  {
LABEL_117:
    v42 = wk->actwk;
    if (v42->status != 40 && v42->use_skillid != 240)
    {
      v44 = wk->sysmsgList;
      sBtlCreateSM(v44, wk, 71, 0, 0, 120);
    }
  }
LABEL_124:
  if ((wk->status & 0x20000) != 0)
    wk->GroupID = -1;
  sBtlCreateAnim_Unit(wk, v14, damage, 0, 0, SklId);
  sBtlClearHitC(wk->hitList, wk);
  effList = wk->effList;
  sBtlForceReset(effList, wk);
  if ((wk->aiwk->scrflag & 0x20000) != 0)
  {
    status = wk->status;
    v48 = wk->actwk;
  }
  else
  {
    v48 = wk->actwk;
    v49 = wk->status;
    v51 = (v49 & 0x100000) == 0 && v48->status != 40;
    status = v49 | v51;
  }
  v48->gravcnt = 0;
  wk->status = status | 0x20;
  v54 = wk->vstatus | 0x80;
  v48->action_flg = 0;
  wk->vstatus = v54;
  if (!v55)
  sBtlCheckResetBadStatus(wk);
  sBtlSetBadStatus_No(wk, 0, 0x11u, 0, -1);
  wk->para->now->hp = 0;
  dds3ObjectBaseOffFlag(&wk->pBasic, 0x400u);
  dvltkList = wk->dvltkList;
  sBtlCreateDvltk_Priority(dvltkList, wk, 15);
  x = wk->pos.x;
  y = wk->pos.y;
  z = wk->pos.z;
  w = wk->pos.w;
  v105.x = x;
  v105.y = y;
  v105.z = z;
  v105.w = w;
  sBtlPlay3DSE(0x10073u, v105);
  v62 = wk->effList;
  sBtlForceDelete_ID_Acter(v62, wk, 55);
  if ((wk->side & 2) != 0)
  {
    datSetKillDevil(wk->para->devilid);
    para = wk->para;
    gohKarteRegistDevilBtl(para, GBWK->karte_list, 1, 0);
    if ((u32)(SklId - 1299) > 2)
      goto LABEL_159;
    setumaCnt = SystemWork->setumaCnt;
    if (setumaCnt > 0xFD)
    {
      goto LABEL_158;
LABEL_159:
      goto LABEL_160;
    }
    LOBYTE(setumaCnt) = SystemWork->setumaCnt;
    SystemWork->setumaCnt = setumaCnt + 1;
    achievementTbl_k__BackingField = _achievementTbl_k__BackingField;
    klass = achievementTbl_k__BackingField->klass;
    v79 = *(u16 *)&achievementTbl_k__BackingField->klass->_2.rank;
    if (*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
    {
      p_offset = &klass->_1.interfaceOffsets->offset;
      while (*(p_offset - 1) != Project_DefineAchievementID_string_)
      {
        p_offset += 2;
        if (!--v79)
          goto LABEL_181;
      }
      v81 = &klass->vtable[*(u32 *)p_offset + 23];
    }
    else
    {
LABEL_181:
      v81 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0x17u);
    }
    v89 = (*v81)(achievementTbl_k__BackingField, *(u64 *)(v81 + 8));
    ProgressUnlock_3(v89, SystemWork->setumaCnt, 50);
LABEL_158:
    if (SystemWork->setumaCnt < 0x32u)
      goto LABEL_159;
    v91 = _achievementTbl_k__BackingField;
    v92 = v91->klass;
    v93 = *(u16 *)&v91->klass->_2.rank;
    if (*(u16 *)&v91->klass->_2.rank)
    {
      v94 = &v92->_1.interfaceOffsets->offset;
      while (*(v94 - 1) != Project_DefineAchievementID_string_)
      {
        v94 += 2;
        if (!--v93)
          goto LABEL_215;
      }
      v95 = &v92->vtable[*(u32 *)v94 + 23];
    }
    else
    {
LABEL_215:
      v95 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0x17u);
    }
    v96 = (*v95)(v91, *(u64 *)(v95 + 8));
    Unlock_2(v96);
LABEL_160:
    v68 = SystemWork;
    devilKillCnt = v68->devilKillCnt;
    if (devilKillCnt > 0x7CF)
    {
      goto LABEL_162;
    }
    v68 = SystemWork;
    LOWORD(devilKillCnt) = v68->devilKillCnt;
    v68->devilKillCnt = devilKillCnt + 1;
    v98 = _achievementTbl_k__BackingField;
    v99 = v98->klass;
    v100 = *(u16 *)&v98->klass->_2.rank;
    if (*(u16 *)&v98->klass->_2.rank)
    {
      v101 = &v99->_1.interfaceOffsets->offset;
      while (*(v101 - 1) != Project_DefineAchievementID_string_)
      {
        v101 += 2;
        if (!--v100)
          goto LABEL_231;
      }
      v102 = &v99->vtable[*(u32 *)v101 + 24];
    }
    else
    {
LABEL_231:
      v102 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0x18u);
    }
    v103 = (*v102)(v98, *(u64 *)(v102 + 8));
    ProgressUnlock_3(v103, SystemWork->devilKillCnt, 1000);
LABEL_162:
    if (SystemWork->devilKillCnt < 0x3E8u)
    {
LABEL_187:
      sBtlDeadFlagOn(wk);
      goto LABEL_190;
    }
    v71 = _achievementTbl_k__BackingField;
    v72 = v71->klass;
    v73 = *(u16 *)&v71->klass->_2.rank;
    if (*(u16 *)&v71->klass->_2.rank)
    {
      v74 = &v72->_1.interfaceOffsets->offset;
      while (*(v74 - 1) != Project_DefineAchievementID_string_)
      {
        v74 += 2;
        if (!--v73)
          goto LABEL_170;
      }
      v75 = &v72->vtable[*(u32 *)v74 + 24];
    }
    else
    {
LABEL_170:
      v75 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0x18u);
    }
    v82 = (*v75)(v71, *(u64 *)(v75 + 8));
    Unlock_2(v82);
    goto LABEL_187;
  }
LABEL_190:
  if (!v32 || !sBtlGetPChara())
    return v16;
  level = wk->para->level;
  if (level < 3)
  {
    v86 = 1;
    if ((u32)(SklId - 1299) > 2)
      goto LABEL_194;
  }
  else
  {
    v86 = (char)((((86 * (char)level) & 0x8000) != 0) + ((u16)(86 * (char)level) >> 8));
    if ((u32)(SklId - 1299) > 2)
    {
LABEL_194:
      if (!v87)
      sBtlSetAddMag(wk, v86);
      return v16;
    }
  }
  if (!v87)
  sBtlSetAddMag_Setsuma(wk, v86);
  return v16;
}

// 0x2053b10
void sBtlSetSpecialDamage(SBTLUNIT_WORK *wk, SBTLDMG_HITWORK *hwk, SKLID skillid, s32 damage) {
  s32 devilid;
  SBATTLE_WORK *v11;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 acterID;
  s32 v15;
  s32 v16;
  s32 StartTime_Damage;
  SBTLUNIT_WORK *v18;
  SBTLDMG_HITWORK *p_huka2hwk;
  s32 v23;
  s32 acterside;
  s32 serialID2;
  u8 v26;
  SBTLUNIT_WORK *v27;
  s32 v28;
  s32 v29;
  s32 v30;
  s32 v32;
  f32 x;
  f32 y;
  u16 type;
  f32 z;
  f32 w;
  s32 v38;
  SBTLUNIT_WORK *v39;
  s32 v40;
  u16 v41;
  s8 v42;
  s32 v43;
  u16 v44;
  SBTLDMG_HITWORK *v46;
  s32 v47;
  s32 v48;
  s32 v49;
  s32 v54;
  SBTLDMG_HITLISTWORK *hitList;
  SBTLEFF_LISTWORK *effList;
  s32 scrStep;
  s32 v59;
  SBTLACTAI_WORK *actaiwk;
  u32 v61;
  s32 status;
  s32 v63;
  void *Instance;
  sdfVector4_t v65;

  devilid = (u16)wk->para->devilid;
  if (devilid != 302 && devilid != 263)
    goto LABEL_51;
  if (wk->actwk->status == 7)
    return;
  if ((wk->side & 2) == 0)
    goto LABEL_16;
  v11 = wk;
  if ((v11->status3 & 0x4000) == 0)
    goto LABEL_16;
  v11 = wk;
  UnitMng = v11->UnitMng;
  acterID = hwk->acterID;
  wk = sBtlSearchUnit_ID(UnitMng, acterID);
  if (wk)
  {
LABEL_16:
    if ((wk->side & 2) != 0)
    {
      if ((wk->status3 & 0x4000000) != 0)
      {
        if (damage >= 0)
          v15 = damage;
        else
          v15 = damage + 1;
        damage = v15 >> 1;
      }
    }
    v16 = hwk->acterID;
    sBtlSetDamage(wk, skillid, damage, v16);
    StartTime_Damage = sBtlGetStartTime_Damage();
    sBtlCreateAnim_Unit(wk, v18, damage, 0, 0, skillid);
    sBtlSetHitback(wk, hwk, 0);
    if (hwk->BEDtype == 2)
    {
      p_huka2hwk = &wk->huka2hwk;
      p_huka2hwk = hwk;
      v23 = hwk->skillid;
      acterside = hwk->acterside;
      serialID2 = hwk->serialID2;
      v26 = 5;
      v27 = wk;
      v28 = v23;
      v29 = acterside;
      v30 = serialID2;
      goto LABEL_57;
    }
    sBtlEffSetTarget(wk->ListID);
    if (wk->criticalflg == 1)
    {
      wk->criticalflg = 0;
      v32 = hwk->skillid;
      x = wk->pos.x;
      y = wk->pos.y;
      type = hwk->type;
      z = wk->pos.z;
      w = wk->pos.w;
      v38 = StartTime_Damage + 1;
      v39 = wk;
      v40 = v32;
      v41 = type;
      v42 = 1;
    }
    else
    {
      x = wk->pos.x;
      y = wk->pos.y;
      z = wk->pos.z;
      w = wk->pos.w;
      v43 = hwk->skillid;
      v44 = hwk->type;
      v38 = StartTime_Damage + 1;
      v39 = wk;
      v40 = v43;
      v41 = v44;
      v42 = 0;
    }
    v65.x = x;
    v65.y = y;
    v65.z = z;
    v65.w = w;
    sBtlCheckYukaDamageEffect(v39, v40, v41, v38, v42, v65, 0);
    if ((hwk->type & 0xFFFu) <= 0xF && ((1 << LOBYTE(hwk->type)) & 0xFE3E) != 0)
    {
      v46 = &wk->huka2hwk;
      v46 = hwk;
      v47 = hwk->skillid;
      v48 = hwk->acterside;
      v49 = hwk->serialID2;
      if (v47 != 151)
      {
        v27 = wk;
        v28 = v47;
        v26 = 2;
        v29 = v48;
        v30 = v49;
LABEL_57:
        sBtlCheckEffectData(v27, v28, v26, 0, v29, v30, StartTime_Damage);
        if (sBtlIsDeadBgn(wk))
        {
LABEL_59:
          hitList = wk->hitList;
          sBtlClearHitC(hitList, wk);
          effList = wk->effList;
          sBtlForceReset(effList, wk);
          sBtlResetAAI(wk);
          wk->actaiwk->dataflg = 0;
          sBtlResetMode(wk);
          wk->aiwk->mode = 0;
          ResetAction(wk, 0, 0);
          sBtlSetAction(wk, 7, 0);
          scrStep = wk->aiwk->scrStep;
          if (scrStep == 1)
          {
            sBtlSetMotion(wk, 1, 4, 0, 0);
            v59 = 2;
            wk->motion_setno = 11;
            wk->para->now->hp = wk->para->now->maxhp;
          }
          else if (scrStep)
          {
            sBtlSetMotion(wk, 13, 4, 0, 0);
            v59 = 3;
            wk->status |= 0x4000u;
          }
          else
          {
            v59 = 1;
            sBtlSetMotion(wk, 1, 4, 0, 0);
            wk->motion_setno = 10;
            wk->para->now->hp = wk->para->now->maxhp;
          }
          actaiwk = wk->actaiwk;
          v61 = wk->status | 0x20;
          status = actaiwk->status;
          v63 = wk->vstatus | 0x80;
          wk->aiwk->scrStep = v59;
          wk->status = v61;
          wk->vstatus = v63;
          actaiwk->status = status & 0xFFFFFFDF;
          wk->actwk->gravcnt = 0;
          v54 = hwk->acterID;
          if (v54 != wk->playerID)
            return;
          goto LABEL_84;
LABEL_52:
          if (v54 != wk->playerID)
            return;
LABEL_84:
          if ((wk->side & 2) != 0)
          {
            Instance = get_Instance(0);
            HitCountAdd(Instance, 1, hwk->skillid, 0);
          }
          return;
        }
LABEL_51:
        v54 = hwk->acterID;
        goto LABEL_52;
LABEL_50:
        if (sBtlIsDeadBgn(wk))
          goto LABEL_59;
        goto LABEL_51;
      }
      sBtlCheckEffectData_SeOnly(wk, 151, 2u, 0, v48, v49, StartTime_Damage);
    }
    goto LABEL_50;
  }
}

// 0x204fe00
void sBtlSetSpecialDamage_DamageOnly(SBTLUNIT_WORK *wk) {
  s32 devilid;
  s32 scrStep;
  s32 v5;
  SBTLDMG_HITLISTWORK *hitList;
  SBTLEFF_LISTWORK *effList;
  SBTLACTAI_WORK *actaiwk;
  s32 status;
  s32 v12;

  devilid = (u16)wk->para->devilid;
  if (devilid == 302 || devilid == 263)
  {
    if (!sBtlIsDeadBgn(wk))
      return;
    sBtlSetAction(wk, 7, 0);
    scrStep = wk->aiwk->scrStep;
    if (scrStep == 1)
    {
      sBtlSetMotion(wk, 1, 4, 0, 0);
      v5 = 2;
      wk->motion_setno = 11;
      wk->para->now->hp = wk->para->now->maxhp;
    }
    else if (scrStep)
    {
      sBtlSetMotion(wk, 13, 4, 0, 0);
      v5 = 3;
      wk->status |= 0x4000u;
    }
    else
    {
      v5 = 1;
      sBtlSetMotion(wk, 1, 4, 0, 0);
      wk->motion_setno = 10;
      wk->para->now->hp = wk->para->now->maxhp;
    }
    wk->aiwk->scrStep = v5;
    hitList = wk->hitList;
    sBtlClearHitC(hitList, wk);
    effList = wk->effList;
    sBtlForceReset(effList, wk);
    actaiwk = wk->actaiwk;
    status = actaiwk->status;
    v12 = wk->vstatus | 0x80;
    wk->status |= 0x20u;
    wk->vstatus = v12;
    actaiwk->status = status & 0xFFFFFFDF;
    wk->actwk->gravcnt = 0;
  }
}

// 0x205c4e0
void sBtlSetDamage_L_EnemyAll(void) {
  SBTLUNIT_WORK *v1;
  SBTLUNIT_LISTWORK *SideList;
  s64 v4;
  SBTLUNIT_WORK *pUnit;
  sdatUnitWork_t *para;
  sdatParaWork_t *now;
  s32 hp;
  s32 v10;
  s32 v11;
  s32 v12;

  SideList = sBtlCreateSideList(2, 0);
  if (SideList->count >= 1)
  {
    v4 = 0;
    do
    {
      pUnit = SideList->pUnitL[v4]->pUnit;
      para = pUnit->para;
      pUnit->yure = 2;
      now = para->now;
      hp = now->hp;
      if (hp >= 0)
        v10 = now->hp;
      else
        v10 = hp + 1;
      v11 = v10 >> 1;
      if (hp >= 2)
        v12 = v11;
      else
        v12 = 1;
      now->hp = v12;
      sBtlCreateAnim_Unit(pUnit, v1, hp - v12, 0, 0, 0);
      sBtlSetMotion(pUnit, 1, 4, 0, 0);
      ++v4;
    }
    while (v4 < SideList->count);
  }
  sBtlDeleteUnitList(SideList, 0);
}

// 0x204fca0
static s32 RD_SkillDamageChack(s32 damage) {
  s32 v5;

  goto LABEL_3;
LABEL_7:
  if (!sBtlGetSpiritSkillChk(1385))
    goto LABEL_11;
  return 0;
LABEL_3:
  if (sBtlGetSpiritSkillChk(1384))
    goto LABEL_7;
LABEL_11:
  if (sBtlGetSpiritSkillChk(1384))
    goto LABEL_17;
  if (sBtlGetSpiritSkillChk(1385))
    goto LABEL_17;
  v5 = 30 * damage;
  return v5 / 100;
LABEL_17:
  v5 = 15 * damage;
  return v5 / 100;
}

// 0x2056370
static bool RD_SkillChack(void) {
  if (!sBtlGetSpiritSkillChk(1384))
    return 0;
  if (sBtlGetSpiritSkillChk(1385))
    return 1;
  return 0;
}

// 0x205b490
bool sBtlDevilCheck_YASO(s32 id) {
  return ((u32)(id - 258) < 0x38) & (0xC0000000000007uLL >> ((u8)id - 2));
}

// 0x205c660
void sBtlWeakShildProc(SBTLUNIT_WORK *wk) {
  s32 weak_shild_config;
  s32 v4;
  s32 weak_shild_max;
  s32 ListID;

  if (wk->para->now->hp >= 1)
  {
    weak_shild_config = wk->weak_shild_config;
    if ((weak_shild_config & 0x1000000) != 0 && !wk->weak_shild && (wk->hstatus & 0x10) == 0)
    {
      if (wk->weak_shild_next)
      {
        v4 = wk->weak_shild_timer + 1;
        wk->weak_shild_timer = v4;
        if (v4 >= (weak_shild_config & 0xFFFFFF))
        {
          weak_shild_max = wk->weak_shild_max;
          ListID = wk->ListID;
          *(u64 *)&wk->weak_shild_next = 0;
          wk->weak_shild = weak_shild_max;
          Add(ListID, 0);
          if ((wk->side & 2) != 0 && (wk->exsts & 1) != 0)
          {
            wk->hangeki_st_done = 0;
            wk->hangeki_nokezoranai = 180;
            wk->hangeki_on = 2;
            wk->hangeki_endcnt = 180;
            wk->damage_1stmotcnt = 0;
            wk->damage_1stmotnum = 0;
          }
        }
      }
    }
  }
}

// 0x2059b60
bool sBtlIsNoke(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *atkWk, u32 *attr) {
  if (wk->l_wince_now)
    goto LABEL_4;
  if ((wk->side & 0x80) != 0)
  {
    if ((wk->status & 0x20) != 0)
    {
      if (wk->actwk->status - 7 < 2)
        goto LABEL_24;
    }
    if (wk->wince_type != 1)
    {
      if (wk->l_wince_old)
        goto LABEL_24;
      goto LABEL_4;
    }
LABEL_22:
    wk->s_wince_now = wk->s_wince_max;
    goto LABEL_24;
  }
  if ((wk->status & 0x20) == 0)
    goto LABEL_24;
  if (wk->wince_type == 1)
    goto LABEL_22;
LABEL_4:
  if (wk->s_wince_now)
    return 0;
  if ((wk->status & 0x20) == 0)
    goto LABEL_24;
  if (wk->actwk->status - 7 < 2)
    return 0;
LABEL_24:
  *attr &= 0xFFEF7FFF;
  return 1;
}

// 0x205c750
bool sBtlIsSetuma(void) {
  return is_setuma;
}

// 0x205c7d0
void sBtlSetumaClear(void) {
  is_setuma = 0;
  return;
}

// 0x205c850
bool sBtlIsSetumaActive(void) {
  return evtBitCheck(10023);
}

// 0x205b4b0
void sBtlNewHirumiMotion(SBTLUNIT_WORK *wk, s32 bframe) {
  s32 v5;
  sdatParaWork_t *now;
  signed s32 hp;
  s64 v9;

  if (wk->l_wince_now)
  {
    v5 = 1;
    wk->wince_type = 1;
    goto LABEL_13;
  }
  wk->wince_type = 2;
  if ((wk->side & 0x80) == 0)
  {
    v5 = 14;
    goto LABEL_13;
  }
  v5 = 14;
  if (wk->battlemode == 1)
  {
    goto LABEL_13;
  }
  now = wk->para->now;
  hp = now->hp;
  v9 = 68719476750LL * now->maxhp;
  if (hp <= (s32)((v9 >> 37) + ((u64)v9 >> 63)))
    v5 = 14;
  else
    v5 = 131;
LABEL_13:
  sBtlSetMotion(wk, v5, bframe, 0, 0);
  sBtlBS_MISHAK_Action_Hiru_DamageMotion(wk);
}

// 0x205c860
void sBtlWinceProc(SBTLUNIT_WORK *wk) {
  s32 wince_type;
  s32 l_wince_max;
  s32 s_wince_0;
  s32 *p_s_wince_0;
  s32 v9;
  s32 s_wince_max;
  s32 l_wince_0;
  s32 l_wince_now;
  s32 v13;
  s32 v16;
  s32 v17;
  s32 v18;
  bool v19;
  s32 wince_SuperArmor;

  if (wk->cmbSkl->bRun)
    return;
  wince_type = wk->wince_type;
  if (wince_type == 1)
  {
    if (wk->s_wince_now)
      goto LABEL_27;
    if ((wk->status & 0x20) == 0 || wk->actwk->status - 7 > 1 || wk->damagecnt < 6)
    {
      s_wince_max = wk->s_wince_max;
      wk->wince_type = 0;
      wk->s_wince_0 = 0;
      wk->s_wince_now = s_wince_max;
      p_s_wince_0 = &wk->s_wince_0;
LABEL_33:
      if (!wk->s_wince_now)
        *p_s_wince_0 = 59;
      goto LABEL_35;
    }
    wince_type = wk->wince_type;
  }
  if (wince_type == 2 && !wk->l_wince_now)
  {
    if ((wk->status & 0x20) == 0 || wk->actwk->status - 7 > 1 || wk->damagecnt <= 5)
    {
      l_wince_max = wk->l_wince_max;
      wk->wince_type = 0;
      wk->l_wince_now = l_wince_max;
      setuma_next = 0;
      if (!wk->s_wince_now)
        wk->s_wince_now = wk->s_wince_max;
      *(u64 *)&wk->s_wince_0 = 0;
    }
  }
LABEL_27:
  if (wk->wince_type)
    goto LABEL_43;
  s_wince_0 = wk->s_wince_0;
  p_s_wince_0 = &wk->s_wince_0;
  if (!s_wince_0)
    goto LABEL_33;
  if (!wk->s_wince_now)
  {
    v9 = s_wince_0 - 1;
    *p_s_wince_0 = v9;
    if (v9 <= 0)
      wk->s_wince_now = wk->s_wince_max;
  }
LABEL_35:
  l_wince_0 = wk->l_wince_0;
  l_wince_now = wk->l_wince_now;
  if (l_wince_0)
  {
    if (!l_wince_now)
    {
      v13 = l_wince_0 - 1;
      wk->l_wince_0 = v13;
      if (v13 <= 0)
      {
        wk->l_wince_now = wk->l_wince_max;
        setuma_next = 0;
      }
    }
  }
  else if (!l_wince_now)
  {
    wk->l_wince_0 = 59;
  }
LABEL_43:
  if ((wk->status & 0x20) != 0)
  {
    if (wk->actwk->status - 7 < 2)
      goto LABEL_56;
  }
  if (IsAutoRec(sBtlDMG))
  {
    v16 = wk->l_wince_now;
    v17 = wk->l_wince_max;
    if (v16 < v17)
    {
      v18 = wk->l_wince_time + 1;
      v19 = wk->l_wince_time - 119 < 0;
      wk->l_wince_time = v18;
      if (v19 == __OFSUB__(v18, 120))
      {
        wk->l_wince_now = 10 * v17 / 100 + v16;
        LimitRange(&wk->l_wince_now, 0, v17);
        wk->l_wince_time = 0;
      }
    }
  }
LABEL_56:
  if (!IsAutoRec(sBtlDMG))
    return;
  wince_SuperArmor = wk->wince_SuperArmor;
  if ((u32)(wince_SuperArmor + 1) >= 2)
  {
    if (wince_SuperArmor == -2)
    {
      if (wk->actwk->status != wk->wince_SuperArmorStatus)
        wk->wince_SuperArmor = 0;
    }
    else
    {
      wk->wince_SuperArmor = wince_SuperArmor - 1;
    }
  }
}

// 0x205c720
static bool IsDamageProc(SBTLUNIT_WORK *wk) {
  return (wk->status & 0x20) != 0 && wk->actwk->status - 7 < 2;
}

// 0x205cc10
static bool IsAutoRec(SBTLUNIT_WORK *wk) {
  if (!wk)
    return 0;
  if (!!IsSceanStop())
    return 0;
  if (wk->cmbSkl->bRun)
    return 0;
  return 1;
}

// 0x2057c90
void sBtlWinceDamage(SBTLUNIT_WORK *atkWk, SBTLUNIT_WORK *defWk, SBTLDMG_HITWORK *hwk) {
  SBTLSKILLP_TBL *Skilltbl;
  sdatUnitWork_t *para;
  u32 BadStatus;
  s32 devilid;
  SBTLACTION_WORK *actwk;
  u32 status;
  s32 *p_s_wince_now;
  s32 ConfigGAME;
  s32 wincePow;
  s32 ***p_damage_to_enemy_raito_tbl;
  s32 v20;
  s32 v21;
  s32 v22;
  u32 skillflg;
  s32 *p_l_wince_now;
  s32 l_wince_max;
  s32 s_wince_max;
  s32 x;

  Skilltbl = sBtlGetSkilltbl(hwk->skillid);
  para = defWk->para;
  BadStatus = sBtlGetBadStatus(para);
  if ((defWk->hstatus & 0x10) == 0 && BadStatus != 6 && !defWk->wince_stop)
  {
    if ((defWk->side & 0x80) == 0)
      goto LABEL_16;
    if (!sBtlChkNowJump_OrAtk(defWk) && ((defWk->side & 0x80) == 0 || !defWk->wince_SuperArmor || !sBtlPlayerIsRSkillCancel()))
    {
LABEL_16:
      devilid = defWk->para->devilid;
      if (devilid <= 274)
      {
        if (devilid <= 258)
        {
          if (devilid == 257)
          {
            if ((u32)(hwk->skillid - 1307) > 0xFFFFFFFB)
              return;
          }
          else if (defWk->para->devilid == 258)
          {
            return;
          }
          goto LABEL_46;
        }
        if (devilid == 262)
          goto LABEL_30;
        if ((u32)(devilid - 275) < 0xFFFFFFFD)
          goto LABEL_46;
        goto LABEL_42;
      }
      if ((u32)devilid > 0x12C)
      {
        if (devilid == 314 || defWk->para->devilid == 521 && (u32)(hwk->skillid - 1299) >= 4)
        {
          return;
        }
        goto LABEL_46;
      }
      if (devilid != 290 && devilid != 297)
      {
        if (devilid != 299)
        {
          if (devilid != 300)
            goto LABEL_46;
LABEL_30:
          if ((u32)(hwk->skillid - 1303) <= 0xFFFFFFFB && atkWk->actwk->status == 64 && defWk->actwk->use_skillid == 1542)
          {
            return;
          }
          goto LABEL_46;
        }
LABEL_42:
        if ((u32)(hwk->skillid - 1303) <= 0xFFFFFFFB && defWk->actwk->status == 63)
          return;
LABEL_46:
        actwk = defWk->actwk;
        status = actwk->status;
        if ((status == 53 || status == 6) && actwk->use_skillid == 1472)
          return;
        x = atkWk->para->level - defWk->para->level;
        LimitRange(&x, -10, 10);
        p_s_wince_now = &defWk->s_wince_now;
        ConfigGAME = cfgGetConfigGAME(1, 0);
        if ((atkWk->side & 2) != 0)
        {
          wincePow = Skilltbl->wincePow;
        }
        else
        {
          wincePow = Skilltbl->wincePow;
          if ((defWk->side & 2) != 0)
          {
            p_damage_to_enemy_raito_tbl = &damage_to_enemy_raito_tbl;
LABEL_63:
            v20 = (*p_damage_to_enemy_raito_tbl)[x + 10][ConfigGAME];
            *(u64 *)&defWk->s_wince_old = *(u64 *)&defWk->s_wince_now;
            v21 = v20 * wincePow / 100;
            if (!defWk->wince_SuperArmor)
            {
              v22 = defWk->para->devilid;
              if ((u32)(v22 - 258) > 0x37 || ((1 << ((u8)v22 - 2)) & 0xC0000000000007LL) == 0)
              {
                if ((hwk->skillflg & 0x2000) != 0)
                {
                  *p_s_wince_now = 0;
                }
                else
                {
                  s_wince_max = defWk->s_wince_max;
                  defWk->s_wince_now -= v21;
                  LimitRange(&defWk->s_wince_now, 0, s_wince_max);
                }
              }
            }
            skillflg = hwk->skillflg;
            p_l_wince_now = &defWk->l_wince_now;
            if ((skillflg & 2) != 0)
            {
              *p_l_wince_now = 0;
              if (!*p_s_wince_now)
                goto LABEL_78;
            }
            else
            {
              if (defWk->wince_SuperArmor)
              {
                if (*p_s_wince_now)
                  goto LABEL_71;
LABEL_78:
                defWk->s_wince_0 = 60;
                if (*p_l_wince_now)
                  return;
                goto LABEL_79;
              }
              l_wince_max = defWk->l_wince_max;
              defWk->l_wince_now -= v21;
              LimitRange(&defWk->l_wince_now, 0, l_wince_max);
              if (!*p_s_wince_now)
                goto LABEL_78;
            }
LABEL_71:
            if (*p_l_wince_now)
              return;
LABEL_79:
            defWk->l_wince_0 = 60;
            if ((atkWk->side & 0x80) != 0 && (defWk->side & 2) != 0 && (skillflg & 2) == 0 && defWk->l_wince_old)
            {
              if (evtBitCheck(10023))
              {
                is_setuma = 1;
              }
            }
            return;
          }
        }
        p_damage_to_enemy_raito_tbl = &damage_to_raido_raito_tbl;
        goto LABEL_63;
      }
      if ((u32)(hwk->skillid - 1303) > 0xFFFFFFFB)
        goto LABEL_46;
      if (!wk->SUMMONSKILL_Start)
        goto LABEL_46;
    }
  }
}

// 0x205cd60
void sBtlSetWinceStop(SBTLUNIT_WORK *wk, bool flag) {
  if (wk)
    wk->wince_stop = flag;
}

// 0x205cd70
void sBtlSetWince_Full(SBTLUNIT_WORK *wk) {
  s32 s_wince_max;

  if (wk)
  {
    s_wince_max = wk->s_wince_max;
    wk->wince_type = 0;
    wk->s_wince_now = s_wince_max;
    wk->l_wince_now = wk->l_wince_max;
    *(u64 *)&wk->s_wince_0 = 0;
  }
}

// 0x205cda0
bool sBtlSetSuperArmor(SBTLUNIT_WORK *wk, SKLID skillid, s32 val) {
  SBTLUNIT_WORK *v5;
  SBTLSKILLP_TBL *Skilltbl;
  s32 v8;
  SBTLACTION_WORK *actwk;

  if (wk)
  {
    v5 = wk;
    Skilltbl = sBtlGetSkilltbl(skillid);
    v8 = skillid - 1339;
    if ((u32)(skillid - 1339) <= 6 && ((0x63u >> v8) & 1) != 0)
      val = dword_3E645B8[v8];
    if ((Skilltbl->flg & 0x4000) != 0 && v5->wince_SuperArmor <= 8)
    {
      actwk = v5->actwk;
      v5->wince_SuperArmor = val;
      v5->wince_SuperArmorStatus = actwk->status;
      LOBYTE(wk) = 1;
    }
    else
    {
      LOBYTE(wk) = 0;
    }
  }
  return (char)wk;
}

// 0x205ce30
void sBtlClrSuperArmor(SBTLUNIT_WORK *wk) {
  s32 wince_SuperArmor;
  bool v3;
  s32 v4;

  if (wk)
  {
    wince_SuperArmor = wk->wince_SuperArmor;
    v3 = __OFSUB__(wince_SuperArmor, 1);
    v4 = wince_SuperArmor - 1;
    if (v4 < 0 == v3)
      wk->wince_SuperArmor = v4;
  }
}

// 0x205ce50
void sBtlClrSuperArmor2(SBTLUNIT_WORK *wk) {
  if (wk)
  {
    if (wk->wince_SuperArmor >= 1)
      wk->wince_SuperArmor = 0;
  }
}

// 0x205cd20
void sBtlProcSuperArmor(SBTLUNIT_WORK *wk) {
  s32 wince_SuperArmor;
  s32 v3;

  wince_SuperArmor = wk->wince_SuperArmor;
  if ((u32)(wince_SuperArmor + 1) >= 2)
  {
    if (wince_SuperArmor == -2)
    {
      if (wk->actwk->status == wk->wince_SuperArmorStatus)
        return;
      v3 = 0;
    }
    else
    {
      v3 = wince_SuperArmor - 1;
    }
    wk->wince_SuperArmor = v3;
  }
}
