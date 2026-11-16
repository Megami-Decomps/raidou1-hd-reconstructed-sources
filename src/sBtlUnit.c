#include "types.h"
#include "AUTO.h"
#include "MODELTYPE.h"
#include "SBTLUNIT_MODE.h"
#include "SBTLUNIT_MOTION.h"
#include "SBTLUNIT_SIDE.h"
#include "SBTLUNIT_ST.h"
#include "SBTLUNIT_VST.h"
#include "SBTL_MODE.h"
#include "SBWEAPON_TYPE.h"
#include "SKLID.h"
#include "achievement.h"
#include "bsflow.h"
#include "configgame.h"
#include "dat.h"
#include "dds3basic.h"
#include "dds3kernelcore.h"
#include "dds3objectbase.h"
#include "dds3scenebasic.h"
#include "dds3unitobjectbasic.h"
#include "dds3vrf.h"
#include "dds3worldbasic.h"
#include "dvl.h"
#include "evt.h"
#include "file.h"
#include "fld.h"
#include "gohcalc.h"
#include "kernel.h"
#include "mdl.h"
#include "mdl_check.h"
#include "raijindlc.h"
#include "sbtl.h"
#include "sbtlactai.h"
#include "sbtlaction.h"
#include "sbtlai.h"
#include "sbtlbossevent.h"
#include "sbtlcalc.h"
#include "sbtlcommand.h"
#include "sbtldmg.h"
#include "sbtldraw.h"
#include "sbtldvltk.h"
#include "sbtleff.h"
#include "sbtlencount.h"
#include "sbtlevent.h"
#include "sbtlexp.h"
#include "sbtlitem.h"
#include "sbtlmain.h"
#include "sbtlmenu.h"
#include "sbtlplayer.h"
#include "sbtlplayer_spirit.h"
#include "sbtlplayerex.h"
#include "sbtlplayertbl.h"
#include "sbtlscene.h"
#include "sbtlscript.h"
#include "sbtlshadow.h"
#include "sbtlskill.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtltime.h"
#include "sbtlunit.h"
#include "sbtlunitex.h"
#include "sbtlvisual.h"
#include "sbtlweapon.h"
#include "sdat.h"
#include "sdf_vu0.h"
#include "sdfmodel.h"
#include "sdfquat.h"
#include "smnr.h"

typedef struct DEVILDATA_WORK DEVILDATA_WORK;
typedef struct SBTLITEM_WORK SBTLITEM_WORK;
typedef struct SBTLUNIT_LISTWORK SBTLUNIT_LISTWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

s32 *sbtlmotion_tbl[32];
static s32 S_WINCE_RAIDOU;
static s32 L_WINCE_RAIDOU;
static s32 gUID;
static sdfVector4_t *sbtlunit_debugrot;
static s32 *mdlfileindextbl_p;
static f32 distance_x;
static f32 distance_z;
f32 distance_r;
static SKLID *aSklDflt;
static SKLID *aSklFuko;
static SKLID *aSklJiro;
static SKLID *aSklTaro;
static SKLID *aSklDan;
static SKLID *aSklKag1;
static SKLID *aSklKag2;
static SKLID *aSklKag3;
static SKLID *aSklTens;
static SKLID *aSklTen;
static SKLID *aSklAma;
static SKLID *aSklApo;
static SKLID *aSklApos;
static SKLID *aSklGei;
static SKLID *aSklGeir;
static SKLID *aSklBdan;
static SKLID *aSklBaka;
static SKLID *aSklSin1;
static SKLID *aSklSin2;
static SKLID *aSklMotoFuko;
s32 g_DbgCnt;
s32 step;
s32 stepcnt;
s32 player_theworld_cng;
s32 nakama0_theworld_cng;
s32 nakama1_theworld_cng;

static void Shutdown(dds3ProcessID_t *id);
static bool RGBFade(SBTLUNIT_WORK *wk);
static void CheckHuumaParaUP(sdatUnitWork_t *unit);
static bool SetMotion_Core(SBTLUNIT_WORK *wk);
static void ProcMotionHitStop(SBTLUNIT_WORK *wk);
static void ProcEffectHitStop(SBTLUNIT_WORK *wk);
static bool AllDeleteEnemy(SBTLUNIT_WORK *wk);
static bool ChkBossBtlStart(void);
static bool CheckLoadData(SBTLUNIT_WORK *wk);
static bool MotinProc(SBTLUNIT_WORK *wk);

// 0x2004d30
bool sBtlDeleteEnemy(SBTLUNIT_WORK *wk) {
  s64 v3;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  SBTLAI_WORK *aiwk;
  s32 badstatus;

  v3 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v3 >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[v3]->pUnit;
    if (pUnit)
    {
      aiwk = pUnit->aiwk;
      if (wk->ListID == aiwk->dfltOdrTgt)
        aiwk->dfltOdrTgt = -1;
    }
    ++v3;
  }
  Delete(wk);
  if ((wk->status & 0x1000) != 0)
  {
    sBtlDeleteHitHelper(wk);
  }
  sBtlDeleteHaveSkill_EffectWork(wk);
  badstatus = wk->para->badstatus;
  sBtlResetBadStatus(wk, badstatus);
  sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
  return 1;
}

// 0x2004ff0
bool sBtlDeletePlayer(SBTLUNIT_WORK *wk) {
  void *v3;
  Project_sBtlUnit___c__DisplayClass1_0_Fields *p_fields;
  u64 v5;
  bool v6;
  u32 stock_mask;
  SBATTLE_WORK *v13;
  s32 v15;
  u32 *p_stock_mask;
  SBATTLE_WORK *v21;
  void *deadUnit;
  void *v23;
  SBATTLE_WORK *v25;
  u32 status;
  void *v28;

  v3 = Allocate(Project_sBtlUnit___c__DisplayClass1_0);
  _c__DisplayClass1_0___ctor(v3, 0);
  v3->wk = wk;
  p_fields = &v3->fields;
  v5 = 0;
  v6 = 1;
  v3->wk->m_rate = 0.5;
  {
    stock_mask = wk->stock_mask;
LABEL_11:
    if (sBtlCheckBit(stock_mask, v5))
      goto LABEL_15;
LABEL_5:
    v6 = v5++ < 0x1F;
    if (v5 == 32)
      goto LABEL_17;
  }
  stock_mask = wk->stock_mask;
  goto LABEL_11;
LABEL_15:
  if (wk->summonID[v5] != p_fields->wk->ListID)
    goto LABEL_5;
LABEL_17:
  sBtlResetCombine();
  if (!v6)
    return 0;
  v13 = wk;
  if (v13->summonflg[(u32)v5] != 2)
    return 0;
  if (p_fields->wk->para->badstatus != 0x20000)
    return 1;
  if (v13->battlemode == 3)
    return 1;
  v15 = ((u32)p_fields->wk->hstatus >> 8) & 1;
  SetReturn(v5, v15);
  p_stock_mask = &wk->stock_mask;
  sBtlResetBit(p_stock_mask, v5);
  if (!sBtlCheckTutorialBattle())
    return 1;
  v21 = wk;
  if (!v21->deadUnit)
  {
    v21 = wk;
    v28 = Allocate(System_Collections_Generic_List_SBTLUNIT_WORK_);
    __ctor(v28);
    v21->deadUnit = v28;
  }
  deadUnit = wk->deadUnit;
  v23 = Allocate(System_Predicate_SBTLUNIT_WORK_);
  __ctor(v23, v3, Method_Project_sBtlUnit___c__DisplayClass1_0__DeletePlayer_b__0__, 0);
  if (_Find(deadUnit, v23))
  {
LABEL_42:
    v25 = wk;
    status = v25->status;
    if ((status & 0x400) != 0)
      return 1;
    goto LABEL_43;
  }
  else
  {
    sub_34940(wk->deadUnit, p_fields->wk);
    goto LABEL_42;
  }
  v25 = wk;
  status = v25->status;
  if ((status & 0x400) != 0)
    return 1;
LABEL_43:
  v25 = wk;
  status = v25->status;
  v25->eventgstat = 0;
  *(u32 *)&v25->eventno = 13;
  v25->status = status | 0x400;
  return 1;
}

// 0x2005e00
bool sBtlSetSummon_Unit(SBTLUNIT_WORK *wklock, s32 point, u32 addst, s8 flg, const sdfVector4_t *pos, s8 stflg, bool theworld_on) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  s64 v18;
  s32 v19;
  DEVILDATA_WORK *DevilData;
  s32 v21;
  VISUALDATA_WORK *VisualData;
  s32 minorno;
  SBTLUNIT_WORK *v25;
  f32 *p_x;
  sdfVector4_t *p_pos;
  sdatUnitWork_t *para;
  s32 v33;
  s32 *stock_id;
  s8 size;
  f32 scale;
  s32 v38;
  s32 bunriid;
  f32 v40;
  SBTLACTAI_WORK *actaiwk;
  sdfVector4_t *p_searchpos;
  SBTLACTAI_WORK *v46;
  f32 m_mv_area_r;
  f32 mv_spd;
  s32 PlayerID;
  SBTLUNIT_WORK *PlayerUnit;
  sdfVector4_t *v55;
  struct sdfVector4_t rot;
  sdfVector4_t *p_rot;
  struct sdfVector4_t v60;
  MOTIONDATA_WORK *MotionVisualData;
  u32 v64;
  struct sdfVector4_t v65;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  v64 = addst;
  v18 = point;
  v19 = wk->stock_id[point];
  DevilData = sBtlGetDevilData(v19, -1);
  v21 = wk->stock_buffer[point];
  VisualData = sBtlGetVisualData(2u, v21);
  MotionVisualData = sBtlGetMotionVisualData(2u, wk->stock_buffer[point], 0);
  minorno = DevilData->minorno;
  v25 = sBtlSetSummon(1u, minorno, point, stflg);
  if (theworld_on)
  {
    if (v25)
      v25->status |= 0x10u;
  }
  if (!flg)
    goto LABEL_23;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  p_pos = &v25->pos;
  goto LABEL_22;
LABEL_23:
  goto LABEL_24;
LABEL_22:
  *p_pos = vct_A;
  if (stflg == 3)
    goto LABEL_23;
  PlayerID = sBtlGetPlayerID();
  PlayerUnit = sBtlGetPlayerUnit(PlayerID);
  v25->rot = PlayerUnit->rot;
  v25->rotbk = PlayerUnit->rot;
LABEL_24:
  if (wk->battlemode == 3)
  {
    v60 = main_data->pos;
    vct_A = v60;
    v55 = &v25->pos;
    *v55 = vct_A;
    rot = main_data->rot;
    vct_A = rot;
    p_rot = &v25->rot;
    *p_rot = vct_A;
    para = v25->para;
    goto LABEL_26;
  }
  para = v25->para;
LABEL_26:
  v25->scale.x = VisualData->scale;
  v25->aisyoid = DevilData->aishou;
  v33 = v64 | DevilData->stflg;
  stock_id = wk->stock_id;
  size = VisualData->size;
  v25->scale.y = VisualData->scale;
  scale = VisualData->scale;
  v25->size = size;
  LOWORD(stock_id) = stock_id[v18];
  v38 = v25->status | v33;
  bunriid = DevilData->bunriid;
  v25->scale.z = scale;
  v25->status = v38;
  v40 = VisualData->scale;
  para->devilid = (s16)stock_id;
  v25->bunriid = bunriid;
  v25->scale.w = v40;
  v65 = v25->pos;
  if ((u32)stock_id)
  {
    goto LABEL_28;
  }
  else
  {
LABEL_28:
    goto LABEL_29;
  }
LABEL_29:
  vct_A = v65;
  actaiwk = v25->actaiwk;
  p_searchpos = &actaiwk->searchpos;
  *p_searchpos = vct_A;
  v46 = v25->actaiwk;
  v46->hit_area_r = VisualData->hit_area_r;
  m_mv_area_r = MotionVisualData->m_mv_area_r;
  v46->search_area_r = 1000.0;
  v46->priv_area_r = m_mv_area_r;
  *(u64 *)&v46->frid_area_r = *(u64 *)&DevilData->frid_area_r;
  v25->mv_spd.z = 0.0;
  LOWORD(v46) = DevilData->actcounter;
  v25->mv_rot = 0.0;
  mv_spd = VisualData->mv_spd;
  v25->actcounter_max = (s16)v46;
  v25->max_mvspd.z = mv_spd;
  v25->max_mvrot = VisualData->rot_spd;
  if (!(u32)v46)
  sBtlSetactcounter(v25);
  v25->actcounter = v25->actcounter_max;
  if ((u8)stflg <= 3u && stflg != 1)
  {
    sBtlSetSummonEffect_Nakama(v25, 0);
  }
  sBtlCheckBattlePara(v25);
  *(u64 *)&v25->aiwk->dfltOdrSkl = -4294967147LL;
  return 1;
}

// 0x2007b10
void sBtlStatusBitOn(SBTLUNIT_WORK *wk, SBTLUNIT_ST st) {
  if (wk)
    wk->status |= st;
}

// 0x2007b30
void sBtlStatusBitOff(SBTLUNIT_WORK *wk, SBTLUNIT_ST st) {
  if (wk)
    wk->status &= st;
}

// 0x2007b50
static void Shutdown(dds3ProcessID_t *id) {
  delPlayerFootEffect();
}

// 0x2007bc0
bool sBtlCheckModelDataLoadEnd(SBTLUNIT_WORK *wk) {
  pacFileHandle_t *pacHandle;
  pacFileHandle_t *p_pacHandle;
  s64 v6;
  s32 v7;
  pacFileHandle_t *v8;
  sdfPacDecodeResrcHandle_t *Resrc;
  sdfPacDecodeResrcHandle_t *next;
  sbtldvltk_unitworktag *v11;
  void *v12;
  u16 major;
  s32 minor;
  void *v15;
  bool v16;
  s32 v17;
  SBTLSOUND_DEVILWORK *sewk;
  SBTLPACDATA_AT3 *at3;
  void *pData;
  void *v23;
  s32 devilid;
  void *v25;
  sbtldvltk_unitworktag *dvltkwk;
  void *v27;
  pacFileHandle_t *v28;
  u16 v29;
  s32 v30;
  dds3ModelResrc_t *v31;
  SBATTLE_WORK *v33;
  s32 v34;
  char *DevilModelName;
  void *readdvl;
  s32 v38;
  s64 size;
  u64 *v40;
  s32 *items;
  pacFileHandle_t *_28877184;
  s64 v44;
  Il2CppObject *v46;
  s32 data;

  if ((wk->hstatus & 0x200) != 0)
    return 1;
  pacHandle = wk->pacHandle;
  p_pacHandle = &wk->pacHandle;
  if (pacHandle)
  {
    if (pacCheckEnd(wk->pacHandle))
      goto LABEL_13;
    goto LABEL_9000;
    if (pacCheckEnd(pacHandle))
    {
LABEL_13:
      v8 = p_pacHandle;
      Resrc = pacGetResrc(v8);
      if (Resrc)
      {
        next = Resrc;
        do
        {
          switch (next->header->userId)
          {
            case 0u:
              major = wk->major;
              minor = wk->minor;
              PackDecode(major, minor, 257, next);
              break;
            case 1u:
              v15 = (next->unit->klass->vtable._8_GetAudioData.methodPtr)(next->unit, next->unit->klass->vtable._8_GetAudioData.method);
              v16 = op_Inequality(v15, 0, 0);
              sBtlSetPacData_AT3(wk->major, wk->minor, wk->para->devilid, v15, v16);
              v17 = sBtlSearchPacData(wk->major, wk->minor, wk->para->devilid);
              sewk = wk->sewk;
              at3 = wk3->pacdata[v17]->at3;
              pData = at3->pData;
              LODWORD(at3) = at3->size;
              sewk->pAt3Data = pData;
              sewk = ((char *)sewk + 32);
              HIDWORD(sewk->monitor) = (u32)at3;
              wk->sewk->at3gstat = 2;
              break;
            case 2u:
              v23 = (next->unit->klass->vtable._5_GetExtUnits.methodPtr)(next->unit, next->unit->klass->vtable._5_GetExtUnits.method);
              do
              {
                devilid = wk->para->devilid;
              }
              while (!sBtlLoadAttackHitData(wk, devilid, v23));
              sBtlSetPacData_MHT(wk->major, wk->minor, wk->para->devilid, v23, 0);
              break;
            case 3u:
              v25 = (next->unit->klass->vtable._8_GetAudioData.methodPtr)(next->unit, next->unit->klass->vtable._8_GetAudioData.method);
              sBtlSetPacData_motionSE(wk->major, wk->minor, wk->para->devilid, v25, 0);
              break;
            case 4u:
              dvltkwk = wk->dvltkwk;
              v27 = (next->unit->klass->vtable._7_GetTexture.methodPtr)(next->unit, next->unit->klass->vtable._7_GetTexture.method);
              dvltkwk->CachepData = v27;
              wk->dvltkwk->LB_Load = 1;
              break;
            case 5u:
              v11 = wk->dvltkwk;
              v12 = (next->unit->klass->vtable._7_GetTexture.methodPtr)(next->unit, next->unit->klass->vtable._7_GetTexture.method);
              v11->CachepDataIcon = v12;
              wk->dvltkwk->LB_Load2 = 1;
              break;
            default:
              break;
          }
          next = next->next;
        }
        while (next);
      }
      v28 = p_pacHandle;
      pacHandleFree(v28);
      wk->pacHandle = 0;
      wk->hstatus |= 0x200u;
      return 0;
    }
LABEL_9000:
    return 0;
  }
  v6 = wk->major;
  v7 = wk->minor;
  if (!mdlSearchResrc(v6, v7))
  {
LABEL_48:
    v33 = wk;
    if (v33->battlemode != 3)
    {
      if ((wk->side & 0x80) != 0)
      {
        v33 = wk;
        if (v33->is_jyuso)
          v44 = 3;
        else
          v44 = wk->minor;
        data = mdlfileindextbl_p[v44];
        v46 = Box(s32, &data);
        DevilModelName = Format("mdl_btl_000_{0}", v46, 0);
        goto LABEL_60;
      }
    }
    v34 = wk->minor;
    DevilModelName = mdlGetDevilModelName(v34);
    readdvl = wk->readdvl;
    v38 = wk->minor;
    size = readdvl->_size;
    v40 = Method_System_Collections_Generic_List_int__Add__;
    ++readdvl->_version;
    items = readdvl->_items;
    if ((u32)size >= LODWORD(items->max_length))
    {
      _AddWithResize(readdvl, v38, *(const MethodInfo_2D8F530 **)(*(u64 *)(v40[4] + 192) + 112));
      goto LABEL_60;
    }
    else
    {
      readdvl->_size = size + 1;
      items[size] = v38;
LABEL_60:
      _28877184 = pacLoad_2(DevilModelName);
      p_pacHandle = _28877184;
      return 0;
    }
    goto LABEL_60;
  }
  if (sBtlSearchPacData2(wk->major, wk->minor, wk->para->devilid) < 0)
    goto LABEL_48;
  v29 = wk->major;
  v30 = wk->minor;
  v31 = mdlPrepare(v29, v30, 0);
  if (!READY(v31))
    return 0;
  sBtlSearchAttackHitData_Copy(wk);
  return 1;
}

// 0x2008270
bool Init(s8 flg) {
  dds3ProcessID_t *v2;
  SBATTLE_WORK *wk_local;
  SBTLUNIT_LISTWORK *UnitList;
  dds3ProcessFunc_t v7;
  shutdownfuncDelegate v8;
  s8 v9;
  dds3ProcessID_t *target;

  v2 = Allocate(dds3ProcessID_t);
  _ctor(v2, 0);
  target = v2;
  wk_local = wk;
  UnitList = sBtlCreateUnitList(48);
  wk_local->UnitMng = UnitList;
  v7 = Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_sBtlUnit_Proc__, 0);
  v8 = Allocate(shutdownfuncDelegate);
  _ctor(v8, 0, Method_Project_sBtlUnit_Shutdown__, 0);
  target = dds3StartProcess("sbtlunit_proc", 1016, 1, 1, v7, v8, 0);
  dds3LinkProcess(&wk->MProc_ID, target);
  sBtlSetPlayerData(v9);
  return 1;
}

// 0x20094b0
void sBtlSetEndBadStatus(void) {
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v3;
  u32 status;
  SBTLUNIT_WORK *v5;
  SBTLUNIT_WORK *v6;
  u32 v7;
  sdatUnitWork_t *para;
  SBTLEFF_LISTWORK *effList;
  sdatUnitWork_t *v11;
  SBTLEFF_LISTWORK *v13;

  if (wk->member_num < 1)
    return;
  Nakama = sBtlGetNakama(0);
  if (Nakama)
  {
    v3 = Nakama;
    status = v3->actwk->status;
    if ((status > 0xE || ((1 << status) & 0x4C00) == 0) && v3->actaiwk->mode != 9 && status != 40 && v3->mode >= 5)
    {
      para = v3->para;
      if (sBtlGetBadStatus(v3->para) - 21 < 2)
        goto LABEL_23;
      goto LABEL_9001;
      if (sBtlGetBadStatus(para) - 21 < 2)
      {
LABEL_23:
LABEL_24:
        effList = wk->effList;
        sBtlForceDelete_ID_Acter(effList, v3, 55);
        goto LABEL_12;
      }
LABEL_9001:
      sBtlResetBadStatus(v3, 98303);
      goto LABEL_24;
    }
  }
LABEL_12:
  v5 = sBtlGetNakama(1);
  if (v5)
  {
    v6 = v5;
    v7 = v6->actwk->status;
    if ((v7 > 0xE || ((1 << v7) & 0x4C00) == 0) && v6->actaiwk->mode != 9 && v7 != 40 && v6->mode >= 5)
    {
      v11 = v6->para;
      if (sBtlGetBadStatus(v6->para) - 21 < 2)
        goto LABEL_32;
      goto LABEL_9002;
      if (sBtlGetBadStatus(v11) - 21 < 2)
      {
LABEL_32:
LABEL_33:
        v13 = wk->effList;
        sBtlForceDelete_ID_Acter(v13, v6, 55);
        return;
      }
LABEL_9002:
      sBtlResetBadStatus(v6, 98303);
      goto LABEL_33;
    }
  }
}

// 0x2009860
bool sBtlSetEndData(void) {
  sdatPlayerUnitWork_t *player;
  SBTLUNIT_LISTWORK *v6;
  s64 playerID;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  sdatUnitWork_t *para;
  sdatUnitWork_t *v14;
  sdatUnitWork_t *v17;
  s32 HaveMemSkl;
  sdatUnitWork_t *v20;
  sdatParaWork_t *now;
  s32 hp;
  s32 *p_hp;
  s32 maxhp;
  s64 v26;
  sdatParaWork_t *v29;
  s32 v30;
  sdatParaWork_t *p_fields;
  s32 v32;
  s64 v33;
  s32 magMax;
  s32 autost_cnt2;
  SBATTLE_WORK *v39;
  SBTLUNIT_WORK *v40;
  SBTLMAIN_DATA *main_data_local;
  sdfVector4_t *p_pos;
  s32 v47;
  struct sdfVector4_t rot;
  SBTLMAIN_DATA *v49;
  sdfVector4_t *p_rot;
  sdatUnitWork_t *v51;
  sdatUnitWork_t *v55;
  SBATTLE_WORK *v56;
  s32 equipgun;
  s16 equipsord;
  SBTLEFF_LISTWORK *effList;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v64;
  s32 v66;
  sdatUnitWork_t *v67;
  SBTLEFF_LISTWORK *v71;
  SBTLUNIT_WORK *v72;
  SBTLUNIT_WORK *v73;
  s32 v75;
  sdatUnitWork_t *v76;
  SBTLEFF_LISTWORK *v80;
  sdatPlayerUnitWork_t *PlayerData;
  sdatPlayerUnitWork_t *v85;
  s32 v86;
  sdatUnitWork_t *StockUnitData;
  sdatPlayerUnitWork_t *v88;
  sdatPlayerUnitWork_t *v89;
  s32 v90;
  sdatUnitWork_t *v91;
  sdatPlayerUnitWork_t *v92;
  sdatPlayerUnitWork_t *v93;
  s32 v94;
  sdatUnitWork_t *v95;
  sdatUnitWork_t *v97;
  s32 v98;
  struct sdfVector4_t pos;
  struct sdfVector4_t v100;

  if ((wk->status2 & 0x10000000) == 0)
  {
LABEL_7:
    player = GBWK->player;
    goto LABEL_8;
  }
  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 1) == 0)
      continue;
    para = pUnit->para;
    if (!sBtlChkHaveMemSkl(pUnit->para, 2))
      goto LABEL_25;
    goto LABEL_9000;
    if (!sBtlChkHaveMemSkl(para, 2))
    {
LABEL_25:
      v14 = pUnit->para;
      goto LABEL_26;
    }
LABEL_9000:
    v20 = pUnit->para;
    now = v20->now;
    hp = now->hp;
    maxhp = now->maxhp;
    p_hp = &now->hp;
    v26 = 1374389535 * maxhp * v20->autost_cnt2;
    *p_hp = (v26 >> 37) + ((u64)v26 >> 63) + hp;
    LimitRange(p_hp, 0, maxhp);
    v14 = pUnit->para;
LABEL_26:
    if (!sBtlChkHaveMemSkl(v14, 33))
    {
      v17 = pUnit->para;
      goto LABEL_28;
    }
    v29 = pUnit->para->now;
    v30 = v29->hp;
    v32 = v29->maxhp;
    p_fields = &v29->fields;
    v33 = 1374389535 * v32 * p_fields->luck;
    p_fields->hp = (v33 >> 37) + ((u64)v33 >> 63) + v30;
    LimitRange(&p_fields->hp, 0, v32);
    v17 = pUnit->para;
LABEL_28:
    HaveMemSkl = sBtlChkHaveMemSkl(v17, 73);
    if (!HaveMemSkl)
      continue;
    magMax = wk->magMax;
    autost_cnt2 = pUnit->para->autost_cnt2;
    sBtlAddMag(magMax * autost_cnt2 / 100);
  }
  goto LABEL_7;
LABEL_8:
  v6 = wk->UnitMng;
  playerID = (u32)wk->playerID;
  if ((playerID & 0x80000000) != 0)
    goto LABEL_77;
  v39 = wk;
  if (!v39)
    goto LABEL_77;
  v39 = wk;
  if (!v39->UnitMng)
    goto LABEL_77;
  if (v6->number <= (s32)playerID)
    goto LABEL_77;
  v40 = v6->pUnitL[playerID]->pUnit;
  if (!v40)
    goto LABEL_77;
  pos = v40->pos;
  vct_A = pos;
  main_data_local = main_data;
  p_pos = &main_data_local->pos;
  v47 = (u8)byte_5755EF5;
  *p_pos = vct_A;
  rot = v40->rot;
  if (v47)
    goto LABEL_63;
  goto LABEL_144;
  if (v98)
  {
LABEL_63:
LABEL_64:
    vct_A = rot;
    v49 = main_data;
    p_rot = &v49->rot;
    *p_rot = vct_A;
    v51 = v40->para;
    sBtlResetItemFlg(v51);
    sBtlResetBattlePara(v40, -1);
    if (wk->battlemode == 3)
    {
      goto LABEL_72;
    }
    else
    {
      v97 = Clone(v40->para, 0);
      player->para = v97;
LABEL_72:
      player->hgunnum = sBtlGetGun_Num();
LABEL_73:
      v55 = v40->para;
      v56 = wk;
      equipgun = v56->equipgun;
      equipsord = v56->equipsord;
      LODWORD(v56) = v56->equipbullet;
      player->gunno = equipgun;
      player->swordno = equipsord;
      player->bulletno = (s32)v56;
      if (sBtlGetBadStatus(v55) - 21 >= 2)
      {
        sBtlResetBadStatus(v40, 98303);
LABEL_75:
        effList = wk->effList;
LABEL_76:
        sBtlForceDelete_ID_Acter(effList, v40, 55);
        goto LABEL_77;
      }
      else
      {
        goto LABEL_75;
      }
      effList = wk->effList;
      goto LABEL_76;
    }
    player->hgunnum = sBtlGetGun_Num();
    goto LABEL_73;
  }
LABEL_144:
  v100 = rot;
  rot = v100;
  goto LABEL_64;
LABEL_77:
  Nakama = sBtlGetNakama(0);
  if (Nakama)
  {
    v64 = Nakama;
    v66 = wk->summonindex[0];
    sBtlResetBattlePara(v64, v66);
    if (sBtlGetBadStatus(v64->para) - 21 >= 2)
    {
      sBtlResetBadStatus(v64, 98303);
    }
    v67 = v64->para;
    if (v67->geturei_vice_flag)
      v67->geturei_vice_flag = 0;
    v64->vice_kaisin_cnt = 0;
    v64->vice_kaisin_flg = 0;
    v71 = wk->effList;
    sBtlForceDelete_ID_Acter(v71, v64, 55);
  }
  v72 = sBtlGetNakama(1);
  if (v72)
  {
    v73 = v72;
    v75 = wk->summonindex[1];
    sBtlResetBattlePara(v73, v75);
    if (sBtlGetBadStatus(v73->para) - 21 >= 2)
    {
      sBtlResetBadStatus(v73, 98303);
    }
    v76 = v73->para;
    if (v76->geturei_vice_flag)
      v76->geturei_vice_flag = 0;
    v73->vice_kaisin_cnt = 0;
    v73->vice_kaisin_flg = 0;
    v80 = wk->effList;
    sBtlForceDelete_ID_Acter(v80, v73, 55);
  }
  player->mag = wk->mag;
  PlayerData = sBtlGetPlayerData();
  PlayerData->para->badstatus &= 0xFFFE8000;
  if (PlayerData->stock_max >= 1)
  {
    v85 = PlayerData;
    v86 = 0;
    do
    {
      StockUnitData = sBtlGetStockUnitData(v86);
      if (StockUnitData)
        StockUnitData->badstatus &= 0xFFFE8000;
      ++v86;
    }
    while (v86 < v85->stock_max);
  }
  v88 = sBtlGetPlayerData();
  if (v88->stock_max >= 1)
  {
    v89 = v88;
    v90 = 0;
    do
    {
      v91 = sBtlGetStockUnitData(v90);
      if (v91 && v91->geturei_vice_flag)
        v91->geturei_vice_flag = 0;
      ++v90;
    }
    while (v90 < v89->stock_max);
  }
  v92 = sBtlGetPlayerData();
  if (v92->stock_max >= 1)
  {
    v93 = v92;
    v94 = 0;
    do
    {
      v95 = sBtlGetStockUnitData(v94);
      if (v95)
      {
        v95->prevTgtUnit = 0;
        *(u64 *)&v95->prevSkill = 0;
      }
      ++v94;
    }
    while (v94 < v93->stock_max);
  }
  return 1;
}

// 0x200aaa0
bool Exit(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  u64 v4;
  s32 v5;
  s64 v6;
  SBTLUNIT_WORK *pUnit;
  void *gageUI;
  SBTLUNIT_LISTWORK *v13;
  s32 v15;
  s64 v16;
  s64 v17;
  SBTLUNIT_WORK *v18;
  s64 v19;
  SBTLUNIT_LISTWORK *p_UnitMng;

  UnitMng = wk->UnitMng;
  if (!UnitMng)
    return 1;
  number = (u32)UnitMng->number;
  if ((s32)number < 1)
    goto LABEL_28;
  v4 = 0;
  v5 = 0;
  v6 = 8 * number;
  do
  {
    pUnit = wk->UnitMng->pUnitL[v4 / 8]->pUnit;
    if (pUnit)
    {
      gageUI = pUnit->gageUI;
      if (!op_Inequality(pUnit->gageUI, 0, 0))
        goto LABEL_19;
      goto LABEL_9000;
      if (!op_Inequality(gageUI, 0, 0))
      {
LABEL_19:
        if ((u32)(pUnit->mode - 1) < 2)
          goto LABEL_12;
LABEL_23:
        sBtlDeleteUnit(pUnit);
        goto LABEL_13;
      }
LABEL_9000:
      WeakGageOff(pUnit->gageUI, 0);
      if ((u32)(pUnit->mode - 1) < 2)
      {
LABEL_12:
        v5 = 1;
        goto LABEL_13;
      }
      goto LABEL_23;
    }
LABEL_13:
    v4 += 8;
  }
  while (v6 != v4);
  if (v5 == 1)
    return 0;
LABEL_28:
  v13 = wk->UnitMng;
  if (v13)
  {
    if (v13)
    {
      v15 = v13->number;
      if (v15 >= 1)
      {
        v16 = 4;
        do
        {
          v18 = *(SBTLUNIT_WORK *)(*((u64 *)&v13->pUnitL->obj.klass + v16) + 24);
          if (v18)
          {
            ClassMemAlloc(v18, 0);
            v19 = *((u64 *)&v13->pUnitL->obj.klass + v16);
            *(u64 *)(v19 + 24) = 0;
            v15 = v13->number;
          }
          v17 = v16 - 3;
          ++v16;
        }
        while (v17 < v15);
      }
    }
    p_UnitMng = &wk->UnitMng;
    p_UnitMng = 0;
  }
  return 1;
}

// 0x200a920
void sBtlResetBadStatus_Stock(void) {
  sdatPlayerUnitWork_t *PlayerData;
  sdatPlayerUnitWork_t *v2;
  s32 v3;
  sdatUnitWork_t *StockUnitData;

  PlayerData = sBtlGetPlayerData();
  PlayerData->para->badstatus &= 0xFFFE8000;
  if (PlayerData->stock_max >= 1)
  {
    v2 = PlayerData;
    v3 = 0;
    do
    {
      StockUnitData = sBtlGetStockUnitData(v3);
      if (StockUnitData)
        StockUnitData->badstatus &= 0xFFFE8000;
      ++v3;
    }
    while (v3 < v2->stock_max);
  }
}

// 0x200a9b0
void sBtlResetGetureiViceFlag_Stock(void) {
  sdatPlayerUnitWork_t *PlayerData;
  sdatPlayerUnitWork_t *v2;
  s32 v3;
  sdatUnitWork_t *StockUnitData;

  PlayerData = sBtlGetPlayerData();
  if (PlayerData->stock_max >= 1)
  {
    v2 = PlayerData;
    v3 = 0;
    do
    {
      StockUnitData = sBtlGetStockUnitData(v3);
      if (StockUnitData)
      {
        if (StockUnitData->geturei_vice_flag)
          StockUnitData->geturei_vice_flag = 0;
      }
      ++v3;
    }
    while (v3 < v2->stock_max);
  }
}

// 0x200aa20
void sBtlResetMenuCursor_Stock(void) {
  sdatPlayerUnitWork_t *PlayerData;
  sdatPlayerUnitWork_t *v2;
  s32 v3;
  sdatUnitWork_t *StockUnitData;

  PlayerData = sBtlGetPlayerData();
  if (PlayerData->stock_max >= 1)
  {
    v2 = PlayerData;
    v3 = 0;
    do
    {
      StockUnitData = sBtlGetStockUnitData(v3);
      if (StockUnitData)
      {
        StockUnitData->prevTgtUnit = 0;
        *(u64 *)&StockUnitData->prevSkill = 0;
      }
      ++v3;
    }
    while (v3 < v2->stock_max);
  }
}

// 0x200b330
bool sBtlSetDisp(SBTLUNIT_WORK *wk, s8 flg) {
  SBATTLE_WORK *v6;
  s64 i;
  s32 vstatus;
  u32 v9;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 mode;

  v6 = wk;
  if (!v6)
    return 0;
  if (v6->UnitMng)
  {
    for (i = 0; ; ++i)
    {
      UnitMng = wk->UnitMng;
      if (i >= UnitMng->number)
        return 1;
      pUnit = UnitMng->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      mode = pUnit->mode;
      if ((u32)(mode - 5) < 4 || mode == 10)
      {
        if (flg == 2)
        {
          vstatus = pUnit->vstatus;
        }
        else
        {
          if (!flg)
          {
            vstatus = pUnit->vstatus;
            goto LABEL_27;
          }
          vstatus = pUnit->vstatus;
          if (wk->ListID == pUnit->ListID)
          {
LABEL_27:
            v9 = vstatus & 0xFFFFEFFF;
            goto LABEL_9;
          }
        }
        v9 = vstatus | 0x1000;
LABEL_9:
        pUnit->vstatus = v9;
        continue;
      }
    }
  }
  return 0;
}

// 0x200b4f0
bool Draw(void) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 mode;
  dds3ModelHandle_t *hModel;
  dds3ModelHandle_t *v11;
  s32 vstatus;
  dds3ModelHandle_t *v14;
  dds3ModelHandle_t *v18;
  SBTLUNIT_WORK *Player_HitTarget;
  struct sdfVector4_t scale;
  struct sdfVector4_t v24;

  if (!wk)
    return 0;
  if (wk->UnitMng)
  {
    wk->bosshpdrawnum = 0;
    for (i = 0; ; ++i)
    {
      UnitMng = wk->UnitMng;
      if (i >= UnitMng->number)
        return 1;
      pUnit = UnitMng->pUnitL[i]->pUnit;
      if (!pUnit)
        goto LABEL_13;
      if ((pUnit->vstatus & 0x2000) != 0)
        goto LABEL_13;
      mode = pUnit->mode;
      if ((u32)(mode - 5) < 4)
        goto LABEL_25;
      if (mode != 4)
      {
        if (mode != 10)
          goto LABEL_13;
LABEL_25:
        scale = pUnit->scale;
        vct_A = scale;
        hModel = pUnit->hModel;
        mdlSetScale(hModel);
        v11 = pUnit->hModel;
        if ((pUnit->vstatus & 0x1000) != 0)
        {
          mdlHide(v11);
          vstatus = pUnit->vstatus;
          v14 = pUnit->hModel;
          mdlHideUpdatePos(v14, vstatus & 0x1000000);
        }
        else
        {
          mdlShow(v11);
          mdlHideUpdatePos(pUnit->hModel, 0);
          if ((pUnit->actwk->status & 0xFFFFFFFE) != 0xA)
          {
            sBtlDrawShadow(pUnit);
            if ((pUnit->status & 0x80000000) == 0)
              goto LABEL_13;
            goto LABEL_42;
          }
        }
        dds3ObjectBaseOffFlag(&pUnit->pBasic, 0x400u);
        if ((pUnit->status & 0x80000000) == 0)
          goto LABEL_13;
LABEL_42:
        if (wk->maigoEnc)
          goto LABEL_13;
        Player_HitTarget = sBtlGetPlayer_HitTarget();
        if (Player_HitTarget)
        {
          if (Player_HitTarget != pUnit)
            goto LABEL_13;
        }
        sBtlDrawBossHP(pUnit);
        ++wk->bosshpdrawnum;
        goto LABEL_13;
      }
      v24 = pUnit->scale;
      vct_A = v24;
      v18 = pUnit->hModel;
      mdlSetScale(v18);
      mdlHide(pUnit->hModel);
      dds3ObjectBaseOffFlag(&pUnit->pBasic, 0x400u);
LABEL_13:
    }
  }
  return 0;
}

// 0x2008460
SBTLUNIT_LISTWORK *sBtlCreateUnitList(s32 number) {
  SBTLUNIT_LISTWORK *v3;
  SBTLUNIT_LISTWK *v5;
  SBTLUNIT_LISTWK **p_pUnitL;
  u64 v7;
  s64 v8;
  SBTLUNIT_LISTWK *v9;
  SBTLUNIT_LISTWK *v10;
  SBTLUNIT_LISTWK *v11;

  v3 = (SBTLUNIT_LISTWORK *)Allocate(SBTLUNIT_LISTWORK);
  _ctor(v3, 0);
  v3->number = number;
  v3->count = 0;
  v5 = NewSpecific(SBTLUNIT_LISTWK, number);
  v3->pUnitL = v5;
  p_pUnitL = &v3->pUnitL;
  if (number >= 1)
  {
    v7 = 0;
    v8 = 8 * (u32)number;
    do
    {
      v10 = *p_pUnitL;
      v11 = Allocate(SBTLUNIT_LISTWK);
      _ctor(v11, 0);
      v10[v7 / 8] = v11;
      v9 = (*p_pUnitL)[v7 / 8];
      v9->pUnit = 0;
      v9 = ((char *)v9 + 24);
      LODWORD(v9[-1].pUnit) = 0;
      v7 += 8;
    }
    while (v8 != v7);
  }
  return v3;
}

// 0x200a840
SBTLUNIT_WORK *sBtlSearchUnit_ID(SBTLUNIT_LISTWORK *lwk, s32 ID) {
  if (ID < 0)
    return 0;
  if (!wk)
    return 0;
  if (!wk->UnitMng)
    return 0;
  if (lwk->number > ID)
    return lwk->pUnitL[ID]->pUnit;
  return 0;
}

// 0x200bc50
SBTLUNIT_WORK *sBtlSearchUnit_GroupID(SBTLUNIT_LISTWORK *lwk, s32 serialID) {
  s64 number;
  SBTLUNIT_LISTWK *i;
  SBTLUNIT_WORK *result;

  number = (u32)lwk->number;
  if ((s32)number < 1)
    return 0;
  for (i = lwk->pUnitL; ; ++i)
  {
    result = i->pUnit;
    if (result)
    {
      if ((result->side & 0x18) == 0 && result->GroupID == serialID)
        break;
    }
    if (!--number)
      return 0;
  }
  return result;
}

// 0x200bcb0
bool sBtlSearchUnit_Nakama(SBTLUNIT_WORK *wk) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  SBTLUNIT_WORK *pUnit;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    number = UnitMng->number;
    if (i >= number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if (pUnit->ListID != wk->ListID && (pUnit->side & 0x81) == 1)
      return i < number;
  }
  return i < number;
}

// 0x200bdc0
s32 sBtlGetNumUnit_GroupID(SBTLUNIT_LISTWORK *lwk, s32 serialID) {
  s64 v5;
  s32 v6;
  SBTLEFF_DELLISTWORK *effdelList;
  SBTLUNIT_WORK *pUnit;

  if (lwk && lwk->number >= 1)
  {
    v5 = 0;
    v6 = 0;
    while (1)
    {
      pUnit = lwk->pUnitL[v5]->pUnit;
      if (pUnit && (pUnit->side & 0x18) == 0)
      {
        if (pUnit->GroupID == serialID)
          ++v6;
        effdelList = wk->effdelList;
        goto LABEL_7;
      }
      else
      {
      }
      effdelList = wk->effdelList;
LABEL_7:
      ++v5;
      v6 += sBtlCheckDelWork_Request(effdelList, serialID);
      if (v5 >= lwk->number)
        return v6;
    }
  }
  return 0;
}

// 0x200bf10
s32 sBtlGetNumUnit_GroupID2(SBTLUNIT_LISTWORK *lwk, s32 serialID, s32 flg) {
  s64 number;
  SBTLUNIT_LISTWK *pUnitL;
  SBTLUNIT_LISTWK *m_Items;
  SBTLUNIT_WORK *pUnit;
  SBTLUNIT_LISTWK *v8;
  SBTLUNIT_WORK *v9;

  if (!lwk)
    return (s32)lwk;
  number = (u32)lwk->number;
  if ((s32)number < 1)
    goto LABEL_13;
  pUnitL = lwk->pUnitL;
  if (flg)
  {
    if (flg == 1)
    {
      LODWORD(lwk) = 0;
      m_Items = pUnitL;
      do
      {
        pUnit = m_Items->pUnit;
        if (pUnit && (pUnit->side & 0x18) == 0 && pUnit->GroupID == serialID && pUnit->mode > 4)
          LODWORD(lwk) = (u32)lwk + 1;
        ++m_Items;
        --number;
      }
      while (number);
      return (s32)lwk;
    }
LABEL_13:
    LODWORD(lwk) = 0;
    return (s32)lwk;
  }
  LODWORD(lwk) = 0;
  v8 = pUnitL;
  do
  {
    v9 = v8->pUnit;
    if (v9 && (v9->side & 0x18) == 0 && v9->GroupID == serialID && v9->mode > 3)
      LODWORD(lwk) = (u32)lwk + 1;
    ++v8;
    --number;
  }
  while (number);
  return (s32)lwk;
}

// 0x200bfe0
bool sBtlClearUnitList(SBTLUNIT_LISTWORK *wk) {
  s32 number;
  s64 i;
  SBTLUNIT_LISTWK *v5;
  SBTLUNIT_WORK *p_pUnit;
  SBTLUNIT_WORK *pUnit;

  if (wk)
  {
    number = wk->number;
    if (number >= 1)
    {
      for (i = 0; i < number; ++i)
      {
        v5 = wk->pUnitL[i];
        pUnit = v5->pUnit;
        p_pUnit = &v5->pUnit;
        if (pUnit)
        {
          p_pUnit = 0;
          number = wk->number;
        }
      }
    }
    wk->count = 0;
  }
  return wk != 0;
}

// 0x200b260
bool sBtlDeleteUnitList(SBTLUNIT_LISTWORK *wk, bool _destroy) {
  s32 number;
  s64 v5;
  s64 v6;
  SBTLUNIT_WORK *v7;
  s64 v8;
  s64 i;
  SBTLUNIT_LISTWK *v10;
  SBTLUNIT_WORK *p_pUnit;
  SBTLUNIT_WORK *pUnit;

  if (wk)
  {
    number = wk->number;
    if (number >= 1)
    {
      if (destroy)
      {
        v5 = 4;
        do
        {
          v7 = *(SBTLUNIT_WORK *)(*((u64 *)&wk->pUnitL->obj.klass + v5) + 24);
          if (v7)
          {
            ClassMemAlloc(v7, 0);
            v8 = *((u64 *)&wk->pUnitL->obj.klass + v5);
            *(u64 *)(v8 + 24) = 0;
            number = wk->number;
          }
          v6 = v5 - 3;
          ++v5;
        }
        while (v6 < number);
      }
      else
      {
        for (i = 0; i < number; ++i)
        {
          v10 = wk->pUnitL[i];
          pUnit = v10->pUnit;
          p_pUnit = &v10->pUnit;
          if (pUnit)
          {
            p_pUnit = 0;
            number = wk->number;
          }
        }
      }
    }
  }
  return wk != 0;
}

// 0x200c060
s32 sBtlEntryUnitList(SBTLUNIT_LISTWORK *lwk, SBTLUNIT_WORK *wk) {
  s64 number;
  SBTLUNIT_LISTWK *pUnitL;
  s64 v6;
  s64 v8;
  SBTLUNIT_LISTWK *v9;

  number = (u32)lwk->number;
  if ((s32)number < 1)
    return 0;
  pUnitL = lwk->pUnitL;
  v6 = 0;
  while (pUnitL[v6]->pUnit)
  {
    if (number == ++v6)
      return 0;
  }
  v8 = v6;
  v9 = pUnitL[v6];
  v9->pUnit = wk;
  v9 = ((char *)v9 + 24);
  LODWORD(v9[-1].pUnit) = v6;
  ++lwk->count;
  return lwk->pUnitL[v8]->ID;
}

// 0x200c100
s32 sBtlReleaseUnitList(SBTLUNIT_LISTWORK *lwk, SBTLUNIT_WORK *wk) {
  s64 number;
  SBTLUNIT_LISTWK *pUnitL;
  s64 v6;
  SBTLUNIT_LISTWK *v7;
  s64 v8;
  SBTLUNIT_LISTWK *v9;
  s32 v10;

  number = (u32)lwk->number;
  pUnitL = lwk->pUnitL;
  if ((s32)number < 1)
  {
    LODWORD(number) = 0;
  }
  else
  {
    v6 = 0;
    while (1)
    {
      v7 = pUnitL[v6];
      if (v7->pUnit)
      {
        if (v7->ID == wk->ListID)
          break;
      }
      if (number == ++v6)
        goto LABEL_8;
    }
    LODWORD(number) = v6;
  }
LABEL_8:
  v8 = (u32)number;
  v9 = pUnitL[v8];
  v10 = lwk->count - 1;
  v9->pUnit = 0;
  v9 = ((char *)v9 + 24);
  LODWORD(v9[-1].pUnit) = 0;
  lwk->count = v10;
  return lwk->pUnitL[v8]->ID;
}

// 0x200c1b0
SBTLUNIT_WORK *sBtlCreateUnit(MODELTYPE major, s32 minor, SBTLUNIT_MODE mode) {
  SBTLUNIT_WORK *v7;
  sbtldvltk_unitworktag *v8;
  u16 v10;
  s32 v11;
  VISUALDATA_WORK *VisualData;
  MOTIONDATA_WORK *MotionVisualData;
  u32 *p_m_speed;
  SBTLACTAI_WORK *v17;
  SBTLAI_WORK *v18;
  sdatUnitWork_t *v19;
  s64 v20;
  DEVILDATA_WORK *DevilData;
  s32 weak_shild_count;
  f32 v23;
  s32 weak_shild_config;
  s32 atk_raito;
  s32 v26;
  s32 attrinvtime;
  s32 s_wince;
  s32 *p_l_wince;
  s32 v33;
  u32 v34;
  VISUALDATA_WORK *v35;
  struct sdfVector2_t shild_pos;
  SBTLACTAI_WORK *v37;
  s64 v38;
  s64 v39;
  s64 v40;
  s64 v41;
  s64 v42;
  s64 v43;
  s64 v44;
  s64 v45;
  u8 *v46;
  u32 *v47;
  u32 *v48;
  u32 *v49;
  _OWORD *v55;
  _OWORD *v56;
  _OWORD *v57;
  _OWORD *v58;
  s64 v59;
  s64 v60;
  s64 v61;
  s64 v62;
  u64 *v63;
  _OWORD *v64;
  _OWORD *v65;
  _OWORD *v66;
  s64 v67;

  v7 = Allocate(SBTLUNIT_WORK);
  _ctor(v7, 0);
  v7->major = major;
  v7->minor = minor;
  v7->pBasic = 0;
  v7->hEveUnit = 0;
  v7->hModel = 0;
  v7->pBasic_d = 0;
  v7->hEveUnit_d = 0;
  v7->hModel_d = 0;
  v7->pacHandle = 0;
  v8 = v7->dvltkwk;
  v7->cmstatus = 0;
  *(u32 *)&v7->front_time = 0;
  v8->pData = 0;
  v7->motionno = 0;
  if ((*(u8 *)&v7->vstatus & 0x10) == 0)
  {
    v10 = v7->major;
    v11 = v7->minor;
    VisualData = sBtlGetVisualData(v10, v11);
    MotionVisualData = sBtlGetMotionVisualData(v7->major, v7->minor, v7->next_motionno);
    if ((MotionVisualData->flg & 1) != 0)
      p_m_speed = &MotionVisualData->m_speed;
    else
      p_m_speed = &VisualData->m_speed;
    *(u32 *)&v7->m_rate = *p_m_speed;
  }
  v7->bst_effserialID2 = -1;
  v7->color = 8421504;
  v7->fadergb = 8;
  *(u64 *)&v7->damage_serialID = -1;
  *(u64 *)&v7->dissolveAlpha = 0x808080803F800000LL;
  v7->light_sw = 1;
  v7->ditherAlpha = 1;
  *(u32 *)&v7->damage_ActerOfsY = 0;
  v7->stoneUse = 0;
  v17 = sBtlCreate();
  v7->actaiwk = v17;
  v18 = Create(0);
  v7->aiwk = v18;
  v19 = v7->para;
  v20 = v7->haveskill;
  v7->mode = mode;
  v7->damage_1stmotnum = 0;
  v7->namatuba_homing_on = 0;
  v7->MantObj = 0;
  *(u64 *)((u64)v19->haveskill + 32) = 0x12000000095LL;
  *(u64 *)(v20 + 32) = 0x12000000095LL;
  v7->damage_1stmotcnt = 0;
  v7->kaifuku_skl_cnt = 0;
  v7->hangeki_st_done = 0;
  v7->no_dead_se = 0;
  v7->not_hitmode = 0;
  v7->katana_hit_cnt = 0;
  v7->warp_bk_color = 0;
  v7->Bounce_HitStopCnt = 0;
  *(u64 *)&v7->nguard_dmgcnt = 0;
  *(u64 *)&v7->miusinai = 0;
  *(_OWORD *)&v7->asimoto_pos_x4 = 0u;
  *(_OWORD *)&v7->JumpAfterCnt = 0u;
  *(_OWORD *)&v7->h_attack_move_len = 0u;
  *(_OWORD *)&v7->hangeki_renzokudmg = 0u;
  *(u64 *)&v7->mag_on3 = -1;
  *(u64 *)&v7->mag_on1 = -1;
  *(u32 *)&v7->lu_start_y = -981860352;
  *(u64 *)&v7->namatuba_cnt = 0x3F80000000000000LL;
  *(_OWORD *)&v7->eff_wait_mukou = 0u;
  *(_OWORD *)&v7->JumpOfsPos = xmmword_3CFD5C0;
  *(_OWORD *)&v7->asimoto_mode = 0u;
  *(_OWORD *)&v7->asimoto_pos_z2 = 0u;
  *(u64 *)&v7->damage_eff_rai_cnt = 0;
  *(_OWORD *)&v7->not_tatezan = 0u;
  *(_OWORD *)&v7->namatuba_goal_pos = xmmword_3CFD5C0;
  *(_OWORD *)&v7->namatuba_1st_pos = xmmword_3CFD5C0;
  v7->MantObj2 = 0;
  v7->KudaObj = 0;
  v7->KudaOpenMesh = 0;
  v7->MagSdObj = 0;
  v7->MagSdMesh = 0;
  v7->MagLcObj = 0;
  v7->MagLcMesh = 0;
  v7->MagAxObj = 0;
  v7->MagAxMesh = 0;
  v7->KudaSupportObj = 0;
  v7->JyusoEffObj = 0;
  v7->JumpKickObj = 0;
  v7->WeakAtkCnt = 0;
  Init(v7, 0);
  sBtlInitUnitSE(v7);
  DevilData = sBtlGetDevilData(minor, -1);
  *(u64 *)&v7->stpflg = 0;
  weak_shild_count = DevilData->weak_shild_count;
  v23 = ConvLevelValue(31, (f32)weak_shild_count);
  weak_shild_config = DevilData->weak_shild_config;
  atk_raito = DevilData->atk_raito;
  v7->weak_shild_timer = 0;
  v26 = v23;
  v7->weak_attrinvtime_cnt = 0;
  v7->weak_shild_config = weak_shild_config;
  attrinvtime = DevilData->attrinvtime;
  v7->atk_raito = atk_raito;
  v7->weak_attrinvtime_max = attrinvtime;
  if (v23 == INFINITY)
    v26 = 0x80000000;
  v7->weak_shild_max = v26;
  v7->weak_shild = v26;
  if (v7->major)
  {
    s_wince = DevilData->s_wince;
    p_l_wince = &DevilData->l_wince;
  }
  else
  {
    s_wince = S_WINCE_RAIDOU;
    p_l_wince = &L_WINCE_RAIDOU;
  }
  v7->s_wince_now = s_wince;
  v33 = *p_l_wince;
  v7->s_wince_max = s_wince;
  v7->s_wince_old = s_wince;
  v7->l_wince_now = v33;
  v7->l_wince_max = v33;
  v7->l_wince_old = v33;
  if (!v34)
  v35 = sBtlGetVisualData(major, minor);
  v7->hpPosition = v35->hp_pos;
  shild_pos = v35->shild_pos;
  *(u64 *)&v7->motion_NoUseMSE_motionID = 0xFFFFFFFF00000000LL;
  *(u32 *)&v7->motion_EndNoCng = 0;
  v7->motion_SeSkep = 0;
  *(u16 *)&v7->DeadEventDone = 0;
  *(u16 *)&v7->DoneCameraTgtSelect1 = 0;
  v7->vice_kaisin_cnt = 0;
  v7->vice_kaisin_flg = 0;
  v7->initHuuma = 0;
  v7->motion_serialno = 0;
  v7->motion_UseWait2 = 0;
  *(u32 *)&v7->motion_WeakDmg2 = 327680;
  *(u64 *)&v7->UnitHitPushDir = 0;
  v7->IsMagAtk = 0;
  v7->YukaDamageSkipCnt = 0;
  v7->GunMotionEnd = 0;
  v7->UnitHitPushUse = 0;
  v7->TgtCngDead_Cnt = 0;
  v7->weak_shild_pos = shild_pos;
  v37 = v7->actaiwk;
  *(_OWORD *)&v7->AutoTgtDmgCnt = 0u;
  v38 = v7->SubCylinder_Use;
  v39 = *(u64 *)(v38 + 24);
  v37->targetID_Mawari = -1;
  if ((s32)v39 >= 1)
  {
    v40 = v7->SubCylinder_PosDir;
    v41 = 0;
    v42 = v7->SubCylinder_PosLen;
    v43 = v7->SubCylinder_Size;
    if ((u32)v39 < 8u || (u64)(v42 - v40) < 0x100 || (u64)(v43 - v40) < 0x100 || (u64)(v43 - v42) < 0x100)
    {
      goto LABEL_36;
    }
    if ((u32)v39 < 0x40u)
    {
      v41 = 0;
LABEL_55:
      v60 = v41 + v38;
      v61 = v41 + (v39 & 7);
      v62 = 4 * v41 + 32;
      v41 = (u32)v39 & 0xFFFFFFF8;
      v63 = (v60 + 32);
      v64 = (v40 + v62);
      v65 = (v42 + v62);
      v66 = (v43 + v62);
      v67 = v61 - (u32)v39;
      do
      {
        *v64 = 0u;
        v64[1] = 0u;
        v64 += 2;
        v67 += 8;
        *v63++ = 0;
        *v65 = 0u;
        v65[1] = 0u;
        v65 += 2;
        *v66 = 0u;
        v66[1] = 0u;
        v66 += 2;
      }
      while (v67);
      if ((v39 & 7) == 0)
        goto LABEL_38;
LABEL_36:
      v44 = (u32)v39 - v41;
      v45 = 4 * v41 + 32;
      v46 = (v41 + v38 + 32);
      v47 = (v43 + v45);
      v48 = (v42 + v45);
      v49 = (v40 + v45);
      do
      {
        --v44;
        *v46++ = 0;
        *v49++ = 0;
        *v48++ = 0;
        *v47++ = 0;
      }
      while (v44);
      goto LABEL_38;
    }
    v41 = v39 & 0x7FFFFFC0;
    v55 = (v43 + 160);
    v56 = (v42 + 160);
    v57 = (v38 + 48);
    v58 = (v40 + 160);
    v59 = (u32)v39 & 0xFFFFFFC0;
    do
    {
      *(v57 - 1) = 0u;
      v59 -= 64;
      v57[2] = 0u;
      *(v58 - 8) = 0u;
      *(v58 - 7) = 0u;
      *(v58 - 6) = 0u;
      *(v58 - 5) = 0u;
      *(v58 - 4) = 0u;
      *(v58 - 3) = 0u;
      *(v58 - 2) = 0u;
      *(v58 - 1) = 0u;
      *v58 = 0u;
      v58[1] = 0u;
      v58[2] = 0u;
      v58[3] = 0u;
      v58[4] = 0u;
      v58[5] = 0u;
      v58[6] = 0u;
      v58[7] = 0u;
      v58 += 16;
      *(v56 - 8) = 0u;
      *(v56 - 7) = 0u;
      *(v56 - 6) = 0u;
      *(v56 - 5) = 0u;
      *(v56 - 4) = 0u;
      *(v56 - 3) = 0u;
      *(v56 - 2) = 0u;
      *(v56 - 1) = 0u;
      *v56 = 0u;
      v56[1] = 0u;
      v56[2] = 0u;
      v56[3] = 0u;
      v56[4] = 0u;
      v56[5] = 0u;
      v56[6] = 0u;
      v56[7] = 0u;
      v56 += 16;
      *(v55 - 8) = 0u;
      *(v55 - 7) = 0u;
      *(v55 - 6) = 0u;
      *(v55 - 5) = 0u;
      *(v55 - 4) = 0u;
      *(v55 - 3) = 0u;
      *(v55 - 2) = 0u;
      *(v55 - 1) = 0u;
      *v55 = 0u;
      v55[1] = 0u;
      v55[2] = 0u;
      v55[3] = 0u;
      v55[4] = 0u;
      v55[5] = 0u;
      v55[6] = 0u;
      v55[7] = 0u;
      v55 += 16;
      *v57 = 0u;
      v57[1] = 0u;
      v57 += 4;
    }
    while (v59);
    if ((v39 & 0x3F) != 0)
    {
      if (((u8)v39 & 0x3Fu) < 8u)
        goto LABEL_36;
      goto LABEL_55;
    }
  }
LABEL_38:
  if (v7->major == 1 && v7->minor == 323)
    v7->status |= 0x4000000u;
  v7->UID = gUID;
  gUID = (gUID + 1) % 10000;
  sBtlUnitInit(v7);
  return v7;
}

// 0x200caf0
bool sBtlDeleteUnit_UnWork(SBTLUNIT_WORK *wk) {
  dds3Basic_t *pBasic_d;
  sbtldvltk_unitworktag *dvltkwk;
  sbtldvltk_unitworktag *v7;
  SBTLSKLHIT_PACLIST *hitwk;
  s32 badstatus;
  u32 status;

  DeleteHpGage(wk->bsc, wk, 0);
  if (wk->changeflg)
  {
    sBtlChangeModelData(wk);
  }
  pBasic_d = wk->pBasic_d;
  if (pBasic_d)
  {
    dds3SceneBasicDelete(pBasic_d);
    wk->pBasic_d = 0;
    wk->hEveUnit_d = 0;
  }
  dvltkwk = wk->dvltkwk;
  dvltkwk->CachepData = 0;
  v7 = wk->dvltkwk;
  v7->CachepDataIcon = 0;
  if ((wk->hitwk->status & 1) != 0)
  {
    sBtlDeleteAttackHitData(wk);
    hitwk = wk->hitwk;
    hitwk->gstat = 0;
    hitwk->status &= ~1u;
  }
  sBtlDeleteUnitSE(wk);
  Delete(wk);
  sBtlDeleteHaveSkill_EffectWork(wk);
  badstatus = wk->para->badstatus;
  sBtlResetBadStatus(wk, badstatus);
  sBtlForceDelete_ID_Acter(wk->effList, wk, 55);
  status = wk->status;
  if ((wk->side & 2) == 0)
  {
    if ((status & 0x800) != 0)
      goto LABEL_32;
    goto LABEL_31;
  }
  if ((status & 0x800) == 0)
  {
    if (sBtlCheckSearchUnit_MMD(wk))
      goto LABEL_32;
    goto LABEL_31;
    if (!sBtlCheckSearchUnit_MMD(wk))
LABEL_31:
      sBtlPacData_FreeIndex(wk->major, wk->minor, wk->para->devilid);
  }
LABEL_32:
  wk->hstatus &= ~0x200u;
  return 1;
}

// 0x200d010
bool sBtlCheckReturn_Unit(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  s32 v5;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 v7;
  SBATTLE_WORK *v9;
  SBTLUNIT_WORK *pUnit;

  v4 = wk;
  if ((v4->status2 & 0x100) == 0)
    return 0;
  v5 = (u16)v4->returnindex[0];
  if (v5 == 0xFFFF)
    return 0;
  v4 = wk;
  LOWORD(v5) = v4->returnindex[0];
  UnitMng = v4->UnitMng;
  v7 = (u32)v4->summonID[(s16)v5];
  if ((v7 & 0x80000000) != 0)
    return 0;
  v9 = wk;
  if (!v9)
    return 0;
  v9 = wk;
  if (v9->UnitMng)
  {
    if (UnitMng->number > (s32)v7)
    {
      pUnit = UnitMng->pUnitL[v7]->pUnit;
      if (pUnit)
      {
        if (wk->ListID == pUnit->ListID)
          return 1;
      }
    }
  }
  return 0;
}

// 0x200d220
bool sBtlSearchReturn_Unit(SBTLUNIT_WORK *wklock) {
  bool v4;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  SBTLUNIT_WORK *pUnit;

  if (wk->battlemode == 3)
    return 0;
  goto LABEL_8;
  if (wk->battlemode != 3)
  {
LABEL_8:
    if ((wklock->side & 0x81) != 1)
      return 0;
    for (i = 0; ; ++i)
    {
      UnitMng = wk->UnitMng;
      number = UnitMng->number;
      v4 = i < number;
      if (i >= number)
        return v4;
      pUnit = UnitMng->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if (sBtlCheckReturn_Unit(pUnit))
        return v4;
    }
  }
  return 0;
}

// 0x200ad90
bool sBtlDeleteUnit(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  SBTLDVLTK_LISTWORK *dvltkList;
  s64 ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_LISTWK *v8;
  s32 count;
  dds3Basic_t *pBasic;
  dds3Basic_t *pBasic_d;
  sbtldvltk_unitworktag *dvltkwk;
  sbtldvltk_unitworktag *v13;
  SBTLSKLHIT_PACLIST *hitwk;
  SBTLACTAI_WORK *actaiwk;
  SBTLAI_WORK *aiwk;
  u32 status;
  s64 v21;
  char v22;
  SBTLUNIT_LISTWORK *v23;
  SBTLUNIT_WORK *pUnit;
  sdatUnitWork_t *para;

  v4 = wk;
  if (v4->battlemode != 3)
  {
    if ((wk->side & 0x81) == 1)
    {
      v4 = wk;
      v4->status2 &= ~0x100u;
      v4->returnindex[0] = -1;
      dvltkList = v4->dvltkList;
      sBtlReleaseDvltk_List(dvltkList, 0);
    }
  }
  ListID = wk->ListID;
  UnitMng = wk->UnitMng;
  v8 = UnitMng->pUnitL[ListID];
  v8->pUnit = 0;
  v8 = ((char *)v8 + 24);
  count = UnitMng->count;
  LODWORD(v8[-1].pUnit) = 0;
  UnitMng->count = count - 1;
  pBasic = wk->pBasic;
  if (pBasic)
  {
    dds3SceneBasicDelete(pBasic);
    wk->pBasic = 0;
    wk->hEveUnit = 0;
  }
  pBasic_d = wk->pBasic_d;
  if (pBasic_d)
  {
    dds3SceneBasicDelete(pBasic_d);
    wk->pBasic_d = 0;
    wk->hEveUnit_d = 0;
  }
  dvltkwk = wk->dvltkwk;
  if (dvltkwk)
  {
    dvltkwk->CachepData = 0;
    v13 = wk->dvltkwk;
    v13->CachepDataIcon = 0;
  }
  hitwk = wk->hitwk;
  if (hitwk && (hitwk->status & 1) != 0)
  {
    sBtlDeleteAttackHitData(wk);
  }
  sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
  sBtlForceDelete_ID_Acter(wk->effList, wk, 55);
  if ((wk->status & 0x800) == 0)
  {
    sBtlDeleteUnitSE(wk);
  }
  actaiwk = wk->actaiwk;
  sBtlDelete(actaiwk);
  aiwk = wk->aiwk;
  Delete(wk->aiwk);
  status = wk->status;
  if ((wk->side & 2) != 0)
  {
    if ((status & 0x800) == 0 && wk->para)
    {
      if (!sBtlCheckSearchUnit_MMD(wk))
        goto LABEL_64;
    }
    return 1;
  }
  if ((status & 0x800) != 0 || !wk->para)
    return 1;
  v21 = 0;
  v22 = 1;
  while (1)
  {
    v23 = wk->UnitMng;
    if (v21 >= v23->number)
      break;
    pUnit = v23->pUnitL[v21]->pUnit;
    if (pUnit)
    {
      para = pUnit->para;
      if (para)
      {
        if ((pUnit->side & 2) == 0)
          v22 &= para->devilid != wk->para->devilid;
      }
    }
    ++v21;
  }
  if ((v22 & 1) == 0)
    return 1;
LABEL_64:
  sBtlPacData_FreeIndex(wk->major, wk->minor, wk->para->devilid);
  return 1;
}

// 0x200cee0
bool sBtlCheckSearchUnit_MMD(SBTLUNIT_WORK *wk) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  SBTLUNIT_WORK *pUnit;
  sdatUnitWork_t *para;
  sdatUnitWork_t *v9;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    number = UnitMng->number;
    if (i >= number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    para = pUnit->para;
    if (para)
    {
      v9 = wk->para;
      if (v9)
      {
        if (wk->ListID != pUnit->ListID && pUnit->major == wk->major && pUnit->minor == wk->minor && para->devilid == v9->devilid)
        {
          return i < number;
        }
      }
    }
  }
  return i < number;
}

// 0x200d410
bool sBtlMutekiProc(SBTLUNIT_WORK *wk) {
  s32 damagecnt;
  s32 tenmetu_cnt;
  u32 v5;
  s32 v6;
  u32 dstcolor;
  s32 v8;
  u32 v9;
  f32 v10;
  s32 v11;
  s32 v12;
  f32 v13;
  s32 v14;
  f32 v15;
  s32 v16;
  f32 v17;
  s32 v18;
  s32 v19;
  s32 v20;
  u32 v21;
  s32 v23;
  f32 v24;
  s32 v25;
  s32 x;

  damagecnt = wk->damagecnt;
  x = 0;
  tenmetu_cnt = wk->tenmetu_cnt;
  if (damagecnt <= 64)
    v5 = 64 - damagecnt;
  else
    v5 = 0;
  v6 = COUNT_UP_360(tenmetu_cnt, (v5 >> 2) + 32);
  dstcolor = wk->dstcolor;
  wk->tenmetu_cnt = v6;
  if (dstcolor)
  {
    v8 = (u8)dstcolor;
    v9 = 64 - v5;
    x = (u8)dstcolor - (64 - v5);
    LimitRange(&x, 0, 255);
    v10 = GET_360toSIN((f32)wk->tenmetu_cnt, (f32)x, (f32)v8);
    v11 = BYTE1(wk->dstcolor);
    if (v10 == INFINITY)
      v12 = 0x80000000;
    else
      v12 = v10;
    x = v11 - v9;
    LimitRange(&x, 0, 255);
    v13 = GET_360toSIN((f32)wk->tenmetu_cnt, (f32)x, (f32)v11);
    v14 = BYTE2(wk->dstcolor);
    v15 = v13;
    v16 = (s32)v13 << 8;
    x = v14 - v9;
    LimitRange(&x, 0, 255);
    v17 = GET_360toSIN((f32)wk->tenmetu_cnt, (f32)x, (f32)v14);
    v18 = (s32)v17 << 16;
    if (v17 == INFINITY)
      v18 = 0;
    if (v15 == INFINITY)
      v19 = 0;
    else
      v19 = v16;
    v20 = v19 | v12 | v18;
    if (wk->damagecnt > 1)
      goto LABEL_20;
LABEL_27:
    if (wk->dstcolor)
      v21 = wk->dstcolor;
    else
      v21 = -2139062144;
    goto LABEL_32;
  }
  v23 = v6;
  v24 = GET_360toSIN((f32)v23, (f32)(s32)(v5 + 96), 255.0);
  v25 = v24;
  if (v24 == INFINITY)
    v25 = 0x80000000;
  wk->tenmetu_color = v25;
  v20 = (v25 << 8) | (v25 << 16) | v25;
  if (wk->damagecnt <= 1)
    goto LABEL_27;
LABEL_20:
  v21 = v20 | 0x80000000;
LABEL_32:
  wk->chgcolor = v21;
  wk->color = v21;
  return 1;
}

// 0x200d6c0
void sBtlResetMutekiColor(SBTLUNIT_WORK *wk) {
  SBTLUNIT_WORK *v4;

  wk->damagecnt = 0;
  v4 = wk;
  sBtlMutekiProc(v4);
}

// 0x200d750
bool sBtlResetColor_Select(void) {
  return 1;
}

// 0x200d760
bool sBtlSetColor_Select(SBTLUNIT_WORK *wk, u32 abgr) {
  return 1;
}

// 0x200d770
bool sBtlSetColor_PNL(u32 abgr) {
  return 1;
}

// 0x200d780
bool sBtlResetColor_PNL(u32 abgr) {
  return 1;
}

// 0x200d790
void sBtlResetModelColor(SBTLUNIT_WORK *wk) {
  *(u64 *)&wk->color = 2155905152LL;
}

// 0x200d7a0
void sBtlSetChangeModelColor(SBTLUNIT_WORK *wk, u32 rgba) {
  wk->chgcolor = rgba;
}

// 0x200d7b0
void sBtlSetChangeModelColor_DST(SBTLUNIT_WORK *wk, u32 src, u32 dst, f32 ratio) {
  u32 *v9;
  u32 *v10;
  s32 v11;
  f32 v12;
  s32 v13;
  u32 v14;
  s32 v15;
  f32 v16;
  s32 v17;
  u32 v18;
  s32 v19;
  f32 v20;
  s32 v21;
  u32 v22;
  u32 v23;

  v9 = NewSpecific(uint, 3u);
  v10 = NewSpecific(uint, 3u);
  v10[0] = (u8)src;
  *(int8x8_t *)&v10[1] = vand_s8(vshl_u32(vdup_n_s32(src), (uint32x2_t)0xFFFFFFF0FFFFFFF8LL), (int8x8_t)0xFF000000FFLL);
  v9[8] = (u8)dst;
  v9[9] = BYTE1(dst);
  v9[10] = BYTE2(dst);
  v11 = v10[0];
  v12 = (f32)((u32)(u8)dst - v11) * ratio;
  v13 = v12;
  if (v12 >= 0.0)
    v13 = (u32)v12;
  v14 = v13 + v11;
  if (v14 >= 0xFF)
    v14 = 255;
  v9[8] = v14;
  v15 = v10[1];
  v16 = (f32)((u32)BYTE1(dst) - v15) * ratio;
  v17 = v16;
  if (v16 >= 0.0)
    v17 = (u32)v16;
  v18 = v17 + v15;
  if (v18 >= 0xFF)
    v18 = 255;
  v9[9] = v18;
  v19 = v10[2];
  v20 = (f32)((u32)BYTE2(dst) - v19) * ratio;
  v21 = v20;
  if (v20 >= 0.0)
    v21 = (u32)v20;
  v22 = v21 + v19;
  if (v22 >= 0xFF)
    v22 = 255;
  v9[10] = v22;
  v23 = (v22 << 16) | (v18 << 8) | v14 | 0x80000000;
  wk->dstcolor = v23;
  wk->abgr = v23;
}

// 0x200d6a0
bool sBtlChangeModelColor(SBTLUNIT_WORK *wk) {
  u32 chgcolor;

  chgcolor = wk->chgcolor;
  if (chgcolor)
    wk->color = chgcolor;
  return chgcolor != 0;
}

// 0x200d920
bool sBtlChangeModelColor_DST(SBTLUNIT_WORK *wk) {
  u32 dstcolor;

  dstcolor = wk->dstcolor;
  if (dstcolor)
    wk->color = dstcolor;
  return dstcolor != 0;
}

// 0x200d940
void sBtlResetModelColor_DST(SBTLUNIT_WORK *wk) {
  wk->dstcolor = 0;
  wk->color = -2139062144;
  wk->abgr = -2139062144;
}

// 0x200d960
void sBtlSetModelColorChroma(SBTLUNIT_WORK *wk, u32 rgba) {
  wk->color_chroma = rgba;
}

// 0x200cdc0
bool sBtlChangeModelData(SBTLUNIT_WORK *wk) {
  evtUnitHandle_t *v3;
  dds3ModelHandle_t *v4;
  dds3Basic_t *pBasic_d;
  dds3Basic_t *pBasic;
  evtUnitHandle_t *hEveUnit;
  dds3ModelHandle_t *hModel;
  evtUnitHandle_t *hEveUnit_d;
  dds3ModelHandle_t *hModel_d;

  v3 = Allocate(evtUnitHandle_t);
  _ctor(v3, 0);
  v4 = Allocate(dds3ModelHandle_t);
  _ctor(v4, 0);
  pBasic_d = wk->pBasic_d;
  pBasic = wk->pBasic;
  hEveUnit = wk->hEveUnit;
  wk->pBasic = pBasic_d;
  hModel = wk->hModel;
  hEveUnit_d = wk->hEveUnit_d;
  wk->hEveUnit = hEveUnit_d;
  hModel_d = wk->hModel_d;
  wk->hModel = hModel_d;
  wk->pBasic_d = pBasic;
  wk->hEveUnit_d = hEveUnit;
  wk->hModel_d = hModel;
  return 1;
}

// 0x200d970
bool CheckMapHit(SBTLUNIT_WORK *wk, const sdfVector4_t *oldpos) {
  f32 z;
  f32 x;
  char status;
  s32 v8;
  SBTLSCENE_WORK *scene;
  f32 v11;
  f32 v12;
  SBATTLE_WORK *v15;
  SBTLSCENE_WORK *v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  s64 pz;

  z = oldpos->z;
  x = oldpos->x;
  status = wk->status;
  LOBYTE(v8) = 0;
  pz = 0;
  if (status < 0)
    return v8;
  scene = wk->scene;
  if (scene->major == 13)
  {
    scene = wk->scene;
    if (scene->minor == 25 && (wk->side & 1) != 0)
    {
      if (z > 890.0)
        z = 890.0;
      if (wk->pos.z > 890.0)
        wk->pos.z = 890.0;
    }
  }
  v11 = wk->pos.x;
  v12 = wk->pos.z;
  v8 = sBtlCheckMapHit_Data(x, z, v11, v12, (f32 *)&pz + 1, &pz);
  if (v8)
  {
    if (v8 == -1)
    {
      wk->pos.x = x;
      wk->pos.z = z;
      v15 = wk;
      v16 = v15->scene;
      if (v16->major != 23)
        goto LABEL_36;
      v15 = wk;
      v16 = v15->scene;
      if (v16->minor != 4 || (wk->side & 1) == 0)
        goto LABEL_36;
      v17 = wk->pos.z;
      v15 = wk;
      if (v17 <= v15->PlayerBtlStartPosZ)
        goto LABEL_36;
      v18 = wk->pos.x;
      v19 = wk->pos.z;
      if (sBtlCheckMapHit_Data(x, z, v18, v19, (f32 *)&pz + 1, &pz) != -1)
        goto LABEL_36;
      v20 = wk->pos.z + -1.0;
    }
    else
    {
      wk->pos.x = *((f32 *)&pz + 1);
      v20 = *(f32 *)&pz;
    }
    wk->pos.z = v20;
LABEL_36:
    LOBYTE(v8) = 1;
  }
  return v8;
}

// 0x200dbc0
s32 sBtlCheckMapHit_Data(f32 _OldX, f32 _OldZ, f32 posx, f32 posz, f32 *px, f32 *pz) {
  s32 encountno;
  f32 LenXZ;
  s32 CeilToInt;
  s32 v19;
  s32 v20;
  s32 v21;
  s32 v22;
  u64 v23;
  u64 v24;
  s32 v25;
  s32 collider_type;
  f32 collider_center_x;
  f32 collider_center_z;
  f32 v29;
  f32 v32;
  s32 v33;
  s32 v34;
  s32 v35;
  s32 v36;
  u64 v37;
  s32 v38;
  f32 v39;
  f32 v40;
  f32 v42;
  u32 v46;
  f32 v47;
  u32 v49;
  f32 v50;
  f32 *v51;
  u64 cz;
  u64 v53;
  u64 GetZ;
  u64 getz;

  v53 = 0;
  GetZ = 0;
  HIDWORD(cz) = 0;
  getz = 0;
  v51 = pz;
  if (wk->collider_type == 1)
  {
LABEL_12:
    LenXZ = sBtlGetLenXZ(OldX, OldZ, posx, posz);
    CeilToInt = sBtlGetCeilToInt(LenXZ, 38.0);
    v19 = CeilToInt - 1;
    GetZ = __PAIR64__(LODWORD(OldX), LODWORD(OldZ));
    if (CeilToInt >= 1)
    {
      v20 = CeilToInt;
      v21 = 0;
      while (1)
      {
        if (v21 >= v19)
        {
          v22 = mapHitCalc(1, posx, posz, 40.0, (f32 *)&getz + 1, &getz, -1, 0);
        }
        else
        {
          v23 = GetZ;
          sBtlGetMovePosToPos(*((f32 *)&v23 + 1), *(f32 *)&v23, posx, posz, 38.0, (f32 *)&GetZ + 1, &GetZ);
          v24 = GetZ;
          v25 = mapHitCalc(1, *((f32 *)&v24 + 1), *(f32 *)&v24, 40.0, (f32 *)&getz + 1, &getz, -1, 0);
          v22 = 0;
          if (v25)
          {
            v22 = v25;
            goto LABEL_71;
          }
        }
        if (v20 == ++v21)
          goto LABEL_71;
      }
    }
    goto LABEL_70;
  }
  encountno = wk->encountno;
  if (encountno == 31)
    goto LABEL_12;
  if (encountno == 51)
    goto LABEL_12;
  collider_type = (u16)wk->collider_type;
  if (!wk->collider_type)
  {
    v32 = sBtlGetLenXZ(OldX, OldZ, posx, posz);
    v33 = sBtlGetCeilToInt(v32, 38.0);
    v34 = v33 - 1;
    v53 = __PAIR64__(LODWORD(OldX), LODWORD(OldZ));
    cz = __PAIR64__(LODWORD(posx), LODWORD(posz));
    if (v33 >= 1)
    {
      v35 = v33;
      v22 = 0;
      v36 = 0;
      while (1)
      {
        if (v36 >= v34)
        {
          if (mapHamidasiWHitSub((f32 *)&cz + 1, &cz, 40.0, 0))
          {
            v22 |= 0x10u;
            posx = *((f32 *)&cz + 1);
            posz = *(f32 *)&cz;
          }
          getz = cz;
        }
        else
        {
          v37 = v53;
          sBtlGetMovePosToPos(*((f32 *)&v37 + 1), *(f32 *)&v37, posx, posz, 38.0, (f32 *)&v53 + 1, &v53);
          cz = v53;
          v38 = mapHamidasiWHitSub((f32 *)&cz + 1, &cz, 40.0, 0);
          getz = cz;
          if (v38)
          {
            posx = *((f32 *)&cz + 1);
            LODWORD(posz) = cz;
            v22 |= 0x10u;
            goto LABEL_74;
          }
        }
        if (v35 == ++v36)
          goto LABEL_74;
      }
    }
    v22 = 0;
LABEL_74:
    getz = __PAIR64__(LODWORD(posx), LODWORD(posz));
    v47 = -distance_x;
    if (posx < (f32)-distance_x)
    {
      if (!v46)
      {
        v47 = -distance_x;
      }
      *((f32 *)&getz + 1) = v47;
      v22 |= 1u;
      goto LABEL_95;
    }
    if (v46)
    {
      if (posx > distance_x)
        goto LABEL_89;
    }
    else
    {
      if (posx > distance_x)
      {
LABEL_89:
        v22 |= 2u;
        *((f32 *)&getz + 1) = distance_x;
        v50 = -distance_z;
        if (posz >= (f32)-distance_z)
        {
LABEL_81:
          if (posz > distance_z)
          {
            *(f32 *)&getz = distance_z;
            v22 |= 8u;
          }
          goto LABEL_71;
        }
LABEL_96:
        if (!v49)
        {
          v50 = -distance_z;
        }
        *(f32 *)&getz = v50;
        v22 |= 4u;
        goto LABEL_71;
LABEL_95:
        v50 = -distance_z;
        if (posz >= (f32)-distance_z)
          goto LABEL_81;
        goto LABEL_96;
      }
    }
    goto LABEL_95;
  }
  collider_type = (u16)wk->collider_type;
  if (collider_type != 100)
  {
    v39 = -posx;
    v40 = -posz;
    if (posx >= 0.0)
      v39 = posx;
    if (posz >= 0.0)
      v40 = posz;
    v42 = sqrtf((f32)(v39 * v39) + (f32)(v40 * v40));
    if (v42 >= distance_x)
    {
      v22 = -1;
      getz = 0;
      goto LABEL_71;
    }
    goto LABEL_70;
  }
  collider_center_x = wk->collider_center_x;
  collider_center_z = wk->collider_center_z;
  v29 = sBtlGetLenXZ(collider_center_x, collider_center_z, posx, posz);
  if ((f32)(v29 + 40.0) < distance_r)
  {
LABEL_70:
    v22 = 0;
    goto LABEL_71;
  }
  sBtlGetMovePosToPos(collider_center_x, collider_center_z, posx, posz, distance_r + -40.0, (f32 *)&getz + 1, &getz);
  v22 = 256;
LABEL_71:
  *px = *((f32 *)&getz + 1);
  *(u32 *)v51 = getz;
  return v22;
}

// 0x200e2b0
void sBtlSetMapDistacne(f32 x, f32 z) {
  distance_x = x;
  distance_z = z;
  return;
}

// 0x200e340
void sBtlSetMapDistacneR(f32 r) {
  distance_r = r;
  return;
}

// 0x200e3d0
bool sBtlCheckMapHit_Cross(const sdfVector4_t *pos0, const sdfVector4_t *ppos, f32 dis) {
  f32 z;
  f32 x;
  f32 v7;
  f32 v8;
  f32 pz;
  f32 px;

  z = ppos->z;
  x = ppos->x;
  v7 = pos0->z;
  v8 = pos0->x;
  return sBtlCheckMapHit_Data(v8, v7, x, z, &px, &pz) == 0;
}

// 0x200e470
bool sBtlGetHitPos(const sdfVector4_t *pos0, const sdfVector4_t *ppos, f32 *posX, f32 *posZ) {
  f32 z;
  f32 x;
  f32 v7;
  f32 v8;
  s32 v12;
  s64 pz;

  z = ppos->z;
  x = ppos->x;
  v7 = pos0->z;
  v8 = pos0->x;
  pz = 0;
  *posX = -1.0;
  *posZ = -1.0;
  v12 = sBtlCheckMapHit_Data(v8, v7, x, z, (f32 *)&pz + 1, &pz);
  if (v12)
  {
    *posX = *((f32 *)&pz + 1);
    *(u32 *)posZ = pz;
  }
  return v12 != 0;
}

// 0x200e540
void sBtlGetRotate(SBTLUNIT_WORK *wk, const sdfVector4_t *pos) {
  u16 major;
  s32 minor;
  VISUALDATA_WORK *VisualData;
  sdfVector4_t *p_rot;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 Radian;
  sdfVector4_t *p_rotbk;
  f32 rot_spd;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  s32 v29;
  f32 v31;
  s32 v32;
  f32 v33;
  f32 per;
  sdfVector4_t v35;
  sdfVector4_t v36;
  sdfVector4_t v37;

  per = pos->x;
  major = wk->major;
  minor = wk->minor;
  VisualData = sBtlGetVisualData(major, minor);
  FromEuler(0.0, wk->mv_rotbk * 0.017453292, 0.0);
  p_rot = &wk->rot;
  x = wk->pos.x;
  y = wk->pos.y;
  z = wk->pos.z;
  w = wk->pos.w;
  *p_rot = vct_A;
  v16 = wk->rot.x;
  v17 = wk->rot.y;
  v18 = wk->rot.z;
  v19 = wk->rot.w;
  v36.y = y;
  v36.z = z;
  v36.w = w;
  v37.x = v16;
  v37.y = v17;
  v37.z = v18;
  *(u64 *)&v35.x = 0;
  v37.w = v19;
  v36.x = x;
  Radian = sBtlGetRadian(v36, v37, v35, per);
  p_rotbk = &wk->rotbk;
  *p_rotbk = vct_A;
  rot_spd = VisualData->rot_spd;
  v24 = Radian + 360.0;
  v25 = rot_spd * 57.29578;
  v26 = -(f32)(rot_spd * 57.29578);
  if (Radian > -180.0)
    v24 = Radian;
  if (v24 <= 180.0)
    v27 = v24;
  else
    v27 = 360.0 - v24;
  if (v27 <= 0.0)
    v28 = -(f32)(rot_spd * 57.29578);
  else
    v28 = rot_spd * 57.29578;
  if ((f32)(v27 / v28) == INFINITY)
    v29 = 0x80000000;
  else
    v29 = (f32)(v27 / v28);
  v31 = VisualData->rot_spd;
  if (v29 >= 0)
    LOWORD(v32) = v29;
  else
    v32 = -v29;
  wk->degcnt = v32;
  v33 = v27 * v31;
  if (v28 > 0.0)
  {
    if (v28 > v33)
      goto LABEL_31;
    goto LABEL_30;
  }
  if (v28 >= v33)
LABEL_30:
    v33 = v28;
LABEL_31:
  wk->deg = v33;
  if (v27 >= -120.0 && v27 <= 0.0 || v27 <= 120.0 && v27 >= 0.0)
    wk->degcnt = 0;
  if (v27 <= 0.0)
  {
    if (v27 < v26)
      return;
  }
  else if (v27 > v25)
  {
    return;
  }
  wk->deg = v27;
}

// 0x200e8d0
void sBtlGetRotate_Kaihi(SBTLUNIT_WORK *wk, const sdfVector4_t *pos) {
  u16 major;
  s32 minor;
  VISUALDATA_WORK *VisualData_P;
  sdfVector4_t *p_rot;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 Radian;
  f32 v21;
  f32 v23;
  f32 v24;
  sdfVector4_t *p_rotbk;
  f32 rot_spd;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  s32 v33;
  f32 v35;
  s32 v36;
  f32 v37;
  f32 per;
  sdfVector4_t v39;
  sdfVector4_t v40;
  sdfVector4_t v41;

  per = pos->x;
  major = wk->major;
  minor = wk->minor;
  VisualData_P = sBtlGetVisualData_P(major, minor);
  FromEuler(0.0, wk->mv_rotbk * 0.017453292, 0.0);
  p_rot = &wk->rot;
  x = wk->pos.x;
  y = wk->pos.y;
  z = wk->pos.z;
  w = wk->pos.w;
  *p_rot = vct_A;
  v16 = wk->rot.x;
  v17 = wk->rot.y;
  v18 = wk->rot.z;
  v19 = wk->rot.w;
  v40.y = y;
  v40.z = z;
  v40.w = w;
  v41.x = v16;
  v41.y = v17;
  v41.z = v18;
  *(u64 *)&v39.x = 0;
  v41.w = v19;
  v40.x = x;
  Radian = sBtlGetRadian(v40, v41, v39, per);
  v21 = 0.0;
  if (Radian >= -100.0 && Radian <= 100.0)
  {
    v21 = -60.0;
    if (Radian >= -60.0)
    {
      v21 = 60.0;
      if (Radian <= 60.0)
      {
        if (Radian >= 0.0 || (v21 = 0.0, Radian <= -15.0))
        {
          if (Radian >= 15.0 || Radian <= 0.0)
            v21 = Radian;
          else
            v21 = 0.0;
        }
      }
    }
  }
  v23 = 20.0;
  v24 = v21 / v23;
  p_rotbk = &wk->rotbk;
  *p_rotbk = vct_A;
  rot_spd = VisualData_P->rot_spd;
  v28 = v24 + 360.0;
  v29 = rot_spd * 57.29578;
  v30 = -(f32)(rot_spd * 57.29578);
  if (v24 > -180.0)
    v28 = v24;
  if (v28 <= 180.0)
    v31 = v28;
  else
    v31 = 360.0 - v28;
  if (v31 <= 0.0)
    v32 = -(f32)(rot_spd * 57.29578);
  else
    v32 = rot_spd * 57.29578;
  if ((f32)(v31 / v32) == INFINITY)
    v33 = 0x80000000;
  else
    v33 = (f32)(v31 / v32);
  v35 = VisualData_P->rot_spd;
  if (v33 >= 0)
    LOWORD(v36) = v33;
  else
    v36 = -v33;
  wk->degcnt = v36;
  v37 = v31 * v35;
  if (v32 > 0.0)
  {
    if (v32 > v37)
      goto LABEL_44;
    goto LABEL_43;
  }
  if (v32 >= v37)
LABEL_43:
    v37 = v32;
LABEL_44:
  wk->deg = v37;
  if (v31 >= -120.0 && v31 <= 0.0 || v31 <= 120.0 && v31 >= 0.0)
    wk->degcnt = 0;
  if (v31 <= 0.0)
  {
    if (v31 < v30)
      return;
  }
  else if (v31 > v29)
  {
    return;
  }
  wk->deg = v31;
}

// 0x200ecf0
void sBtlCheckRotSpd(SBTLUNIT_WORK *wk, const sdfVector4_t *pos) {
  f32 deg;
  sdfVector4_t *p_rot;
  s32 degcnt;

  deg = wk->deg;
  sBtlAddUnitDeg(wk, deg);
  FromEuler(0.0, wk->mv_rotbk * 0.017453292, 0.0);
  p_rot = &wk->rot;
  degcnt = (u16)wk->degcnt;
  wk->degcnt = degcnt - 1;
  *p_rot = vct_A;
  if ((degcnt - 1) << 16 <= 0)
    wk->degcnt = 0;
  else
    wk->mv_spd.z = wk->mv_spd.z * 0.5;
}

// 0x200ee60
bool sBtlCheckNoDmgYure(SBTLUNIT_WORK *wk) {
  return wk->para->devilid == 294;
}

// 0x200ee80
bool UnitMV(SBTLUNIT_WORK *wk) {
  s32 devilid;
  f32 v6;
  s64 v8;
  f32 v9;
  f32 v11;
  sdfVector4_t *p_rot;
  sdfVector4_t *p_rotbk;
  s32 v15;
  sdfVector4_t *p_pos;
  f32 v20;
  f32 v21;
  s32 battlemode;
  f32 front_deg;
  f32 Dir180;
  f32 v28;
  f32 v29;
  sdfVector4_t *v33;
  struct sdfVector4_t pos;
  f32 mv_rot;
  sdfVector4_t *v38;
  struct sdfVector4_t v39;
  s32 yure;
  dds3Basic_t *v42;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 v46;
  dds3Basic_t *v47;
  sdfVector4_t *v52;
  f32 x;
  f32 y;
  f32 z;
  dds3Basic_t *pBasic;
  struct sdfVector4_t koteipos;
  struct sdfVector4_t v62;
  struct sdfVector4_t rot;
  sdfMatrix4_t v68;
  sdfMatrix4_t v69;
  sdfVector4_t v70;

  devilid = (u16)wk->para->devilid;
  if (devilid != 258)
  {
    if (devilid != 260)
    {
      if (devilid != 259)
      {
        goto LABEL_10;
      }
      wk->pos = (struct sdfVector4_t)xmmword_3CFA8E0;
      if (!sBtlCheckSetsuma())
        goto LABEL_33;
      goto LABEL_9000;
      if (!sBtlCheckSetsuma())
      {
LABEL_33:
        if (!sBtlPlayerCheckRSpirit())
          goto LABEL_68;
        if (sBtlPlayerCheckRSpiritEnd())
          goto LABEL_68;
        v11 = -500.0;
        *(u64 *)&wk->pos.x = 0x4416000000000000LL;
        goto LABEL_66;
      }
LABEL_9000:
      if (sBtlCheckSetsumaEnd())
        goto LABEL_33;
      v8 = 0x4416000000000000LL;
      v9 = -700.0;
LABEL_60:
      *(u64 *)&wk->pos.x = v8;
      wk->pos.z = v9;
      wk->mv_rotbk = 180.0;
      FromEuler(0.0, 3.1415927, 0.0);
      goto LABEL_69;
    }
    wk->pos.z = 1500.0;
    *(u64 *)&wk->pos.x = 0x4489800000000000LL;
    if (IsAction(19))
    {
      wk->pos.y = 800.0;
    }
    else
    {
      if (!sBtlCheckSetsuma())
        goto LABEL_27;
      goto LABEL_25;
    }
    if (!sBtlCheckSetsuma())
      goto LABEL_27;
LABEL_25:
    if (sBtlCheckSetsumaEnd())
      goto LABEL_27;
    goto LABEL_9001;
    if (sBtlCheckSetsumaEnd())
    {
LABEL_27:
      if (!sBtlPlayerCheckRSpirit())
        goto LABEL_68;
      if (sBtlPlayerCheckRSpiritEnd())
        goto LABEL_68;
      *(u64 *)&wk->pos.x = 0x4489800000000000LL;
      v11 = -1500.0;
LABEL_66:
      wk->pos.z = v11;
      goto LABEL_208;
    }
LABEL_9001:
    v8 = 0x447A000043C80000LL;
    v9 = -2000.0;
    goto LABEL_60;
  }
  *(int32x2_t *)&wk->pos.x = vdup_n_s32(0x42480000u);
  v6 = -200.0;
  if (!BS_LASTB2_pos_type)
    v6 = -50.0;
  wk->pos.z = v6;
  wk->pos.w = 1.0;
  if (!sBtlCheckSetsuma())
    goto LABEL_39;
  if (sBtlCheckSetsumaEnd())
    goto LABEL_39;
  v8 = 0x42480000C4160000LL;
  v9 = -800.0;
  goto LABEL_60;
LABEL_39:
  if (!sBtlPlayerCheckRSpirit())
    goto LABEL_68;
  if (sBtlPlayerCheckRSpiritEnd())
  {
LABEL_68:
    wk->mv_rotbk = 0.0;
    FromEuler(0.0, 0.0, 0.0);
LABEL_69:
    p_rot = &wk->rot;
    *p_rot = vct_A;
    p_rotbk = &wk->rotbk;
    goto LABEL_77;
    if (v15)
    {
      p_rotbk = &wk->rotbk;
      goto LABEL_77;
    }
    else
    {
      p_rotbk = &wk->rotbk;
LABEL_77:
      *p_rotbk = vct_A;
LABEL_10:
      if (IsSceanStop())
        goto LABEL_79;
      goto LABEL_83;
    }
    goto LABEL_77;
  }
  wk->pos.x = 0.0;
  *(int8x8_t *)&wk->pos.y = vbsl_s8(vcltz_s32(vshl_n_s32(vdup_n_s32(BS_LASTB2_pos_type == 0), 0x1Fu)), (int8x8_t)0x447A0000C2480000LL, (int8x8_t)3276275712LL);
LABEL_208:
  wk->mv_rotbk = 180.0;
  FromEuler(0.0, 3.1415927, 0.0);
  v52 = &wk->rot;
  *v52 = vct_A;
  wk->JumpOfsPos.y = 0.0;
  wk->rotbk = vct_A;
  x = wk->JumpOfsPos.x;
  y = wk->JumpOfsPos.y;
  z = wk->JumpOfsPos.z;
  pBasic = wk->pBasic;
  dds3UnitObjectBasicSetJumpOfsPos(pBasic, x, y, z);
  goto LABEL_10;
  if (IsSceanStop())
  {
LABEL_79:
    if ((wk->status & 0x10) == 0 && ((wk->side & 0x80) == 0 || !sBtlIsSetsumaPadStop()) && !sBtlIsEnemyLastDeadStop())
    {
      return 0;
    }
  }
LABEL_83:
  if ((wk->status & 0x80000) == 0)
    goto LABEL_101;
  if (wk->actwk->status != 10)
    goto LABEL_95;
  if (!sBtlCheckSetsuma())
    goto LABEL_95;
  if (sBtlCheckSetsumaEnd())
  {
LABEL_95:
    wk->actaiwk->status = wk->actaiwk->status & 0xFFFFFF9F | 0x20;
    koteipos = wk->koteipos;
    vct_A = koteipos;
    p_pos = &wk->pos;
    *p_pos = vct_A;
    goto LABEL_101;
  }
LABEL_101:
  v20 = wk->mv_spd.x;
  v21 = wk->mv_spd.z;
  if ((wk->hstatus & 0x1000) != 0)
  {
    front_deg = wk->front_deg;
    Dir180 = sBtlGetDir180(front_deg);
    FromEuler(0.0, Dir180 * 0.017453292, 0.0);
    v62 = vct_A;
    if ((wk->side & 2) == 0)
    {
      goto LABEL_112;
    }
    wk->hstatus &= ~0x1000u;
    goto LABEL_112;
  }
  battlemode = (u16)wk->battlemode;
  if (battlemode == 3)
  {
    if ((wk->side & 1) != 0)
      goto LABEL_198;
  }
  if (battlemode == 3)
  {
LABEL_188:
    rot = wk->rot;
    goto LABEL_190;
  }
  if ((wk->side & 0x80) == 0)
    goto LABEL_188;
LABEL_198:
  rot = wk->rotbk;
LABEL_190:
  vct_A = rot;
  goto LABEL_193;
LABEL_194:
  v62 = vct_A;
LABEL_112:
  goto LABEL_113;
LABEL_193:
  goto LABEL_194;
LABEL_113:
  v28 = -v20;
  v29 = -v21;
  vct_B.x = v28;
  vct_B.y = 0.0;
  vct_B.z = v29;
  vct_B.w = 0.0;
  vct_A = v62;
  ToMatrix();
  get_transpose(&v69, &mtx_A, 0);
  *(_OWORD *)&v68.m00 = *(_OWORD *)&v69.m00;
  *(_OWORD *)&v68.m01 = *(_OWORD *)&v69.m01;
  *(_OWORD *)&v68.m02 = *(_OWORD *)&v69.m02;
  *(_OWORD *)&v68.m03 = *(_OWORD *)&v69.m03;
  v70 = op_Multiply_60923920(&v68, vct_B, 0);
  vct_B = v70;
  v33 = &wk->pos;
  pos = wk->pos;
  vct_A = pos;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  vct_A.w = 1.0;
  *v33 = vct_A;
  mv_rot = wk->mv_rot;
  if (mv_rot == 0.0)
  {
    goto LABEL_128;
  }
  FromRotation(mv_rot * -0.017453292);
  vct_B = vct_A;
  v38 = &wk->rot;
  v39 = wk->rot;
  vct_A = v39;
  Mult();
  *v38 = vct_A;
LABEL_128:
  if (wk->para->devilid == 294)
    goto LABEL_170;
  yure = (u16)wk->yure;
  if (yure == 2)
  {
    v42 = wk->pBasic;
    v43 = 12.0;
    goto LABEL_169;
  }
  if (yure == 1)
  {
    v42 = wk->pBasic;
    v43 = 8.0;
LABEL_169:
    dds3UnitObjectBasicSetDamageYure(v42, v43);
    wk->yure = 0;
  }
LABEL_170:
  v44 = wk->JumpOfsPos.x;
  v45 = wk->JumpOfsPos.y;
  v46 = wk->JumpOfsPos.z;
  v47 = wk->pBasic;
  dds3UnitObjectBasicSetJumpOfsPos(v47, v44, v45, v46);
  return 1;
}

// 0x200ff30
void UnitMV_To_Basic(SBTLUNIT_WORK *wk) {
  f32 z;
  f32 w;
  f32 x;
  f32 v6;
  f32 v7;
  f32 y;
  f32 v9;
  f32 v10;
  sdfVector4_t v11;
  sdfVector4_t v12;

  if ((wk->vstatus & 0x2000) == 0 && wk->pBasic)
  {
    z = wk->pos.z;
    w = wk->pos.w;
    x = wk->pos.x;
    v6 = wk->pos.y + wk->disp_offy;
    v11.x = x;
    v11.y = v6;
    v11.z = z;
    v11.w = w;
    dds3SetPosPoseSet(&wk->pBasic, v11);
    if ((wk->vstatus & 8) == 0)
    {
      v7 = wk->rot.x;
      y = wk->rot.y;
      v9 = wk->rot.z;
      v10 = wk->rot.w;
      v12.x = v7;
      v12.y = y;
      v12.z = v9;
      v12.w = v10;
      dds3SetRotPoseSet(&wk->pBasic, v12);
    }
  }
}

// 0x200fea0
void sBtlUpdateUnitJumpOfsPos(SBTLUNIT_WORK *wk) {
  f32 x;
  f32 y;
  f32 z;
  dds3Basic_t *pBasic;

  x = wk->JumpOfsPos.x;
  y = wk->JumpOfsPos.y;
  z = wk->JumpOfsPos.z;
  pBasic = wk->pBasic;
  dds3UnitObjectBasicSetJumpOfsPos(pBasic, x, y, z);
}

// 0x2010030
bool sBtlCheckMotionNo(SBTLUNIT_WORK *wk, SBTLUNIT_MOTION no) {
  s32 side;

  side = wk->side;
  return wk->motionno == (u64)(u32)sBtlGetMotionNo(wk, side, no);
}

// 0x2010210
bool sBtlCheckMotionEnd(SBTLUNIT_WORK *wk) {
  s32 motionID;
  dds3ModelHandle_t *hModel;

  if (!wk->hModel)
    return 1;
  motionID = wk->motionID;
  if (sBtlCheckLoopMotion(wk, motionID))
    return 0;
  hModel = wk->hModel;
  return mdlChkMotionEnd(hModel);
}

// 0x20104a0
bool sBtlCheckMotionEnd_AnimatorNormal(SBTLUNIT_WORK *wk) {
  dds3ModelHandle_t *hModel;
  f32 MotionFrameF;

  if (sBtlCheckMotionEnd(wk))
    return 1;
  hModel = wk->hModel;
  MotionFrameF = mdlGetMotionFrameF(hModel);
  return mdlGetMotionNormalAnimator(wk->hModel) >= 1.0 && MotionFrameF > 5.0;
}

// 0x20105a0
void sBtlCheckGuardMotion(SBTLUNIT_WORK *wk) {
  s32 v3;
  dds3ModelHandle_t *hModel;

  if (!wk->hModel)
    return;
  if ((~wk->side & 0x81) != 0)
    goto LABEL_7;
  if (wk->battlemode)
  {
LABEL_7:
    v3 = 29;
    goto LABEL_8;
  }
  v3 = 29;
  if (sBtlDat()->m_type != 1)
  {
    if (sBtlDat()->m_type == 2)
    {
      v3 = 40;
    }
    else if (sBtlDat()->m_type == 3)
    {
      v3 = 41;
    }
    else
    {
      v3 = 29;
    }
  }
LABEL_8:
  if ((wk->status & 0x800) == 0 && wk->next_motionID == v3)
  {
    hModel = wk->hModel;
    if ((mdlGetMotionFrame(wk->hModel) & 0x80000000) == 0)
      return;
    sBtlSetMotion(wk, v3, 0, 0, 1);
    wk->motionno = 0;
  }
}

// 0x200ca10
bool sBtlRestartMotion(SBTLUNIT_WORK *wk) {
  s32 vstatus;
  u16 major;
  s32 minor;
  VISUALDATA_WORK *VisualData;
  MOTIONDATA_WORK *MotionVisualData;
  f32 *p_m_speed;

  vstatus = wk->vstatus;
  if ((vstatus & 0x10) != 0)
    return (vstatus & 0x10) == 0;
  major = wk->major;
  minor = wk->minor;
  VisualData = sBtlGetVisualData(major, minor);
  MotionVisualData = sBtlGetMotionVisualData(wk->major, wk->minor, wk->next_motionno);
  if ((MotionVisualData->flg & 1) != 0)
    p_m_speed = &MotionVisualData->m_speed;
  else
    p_m_speed = &VisualData->m_speed;
  wk->m_rate = *p_m_speed;
  return (vstatus & 0x10) == 0;
}

// 0x2010fe0
bool sBtlCheckMotionID(SBTLUNIT_WORK *wk, SBTLUNIT_MOTION motionno) {
  return wk->next_motionID != motionno && wk->motionID != motionno;
}

// 0x2011010
bool sBtlSetMotion_ID(SBTLUNIT_WORK *wk, s32 id, s32 bframe, s32 aframe, s8 flg) {
  s16 v7;
  s16 v8;
  u16 major;
  s32 minor;
  MOTIONDATA_WORK *MotionVisualData;
  MOTIONDATA_WORK *v15;
  u16 v16;
  s32 v17;
  f32 m_speed;
  MOTIONDATA_WORK *v19;
  u16 v20;
  s32 v21;
  VISUALDATA_WORK *VisualData;
  f32 *p_m_speed;
  s32 battlemode;
  f32 m_hokanrate;
  s32 v27;
  f32 m_mv_area_r;
  SBTLACTAI_WORK *actaiwk;
  f32 v31;
  s32 v32;
  s32 next_motion_not_hokan;

  v7 = aframe;
  v8 = bframe;
  wk->next_motionno = id;
  wk->next_motionID = 48;
  major = wk->major;
  minor = wk->minor;
  MotionVisualData = sBtlGetMotionVisualData(major, minor, id);
  v15 = sBtlGetMotionVisualData(wk->major, wk->minor, wk->motionno);
  if (flg)
  {
    wk->beforeframe = v8;
    if ((MotionVisualData->flg & 1) != 0)
    {
      m_speed = MotionVisualData->m_speed;
    }
    else
    {
      v16 = wk->major;
      v17 = wk->minor;
      m_speed = sBtlGetVisualData(v16, v17)->m_speed;
    }
    wk->m_rate = m_speed;
    goto LABEL_30;
  }
  v19 = v15;
  v20 = wk->major;
  v21 = wk->minor;
  VisualData = sBtlGetVisualData(v20, v21);
  if ((MotionVisualData->flg & 1) != 0)
    p_m_speed = &MotionVisualData->m_speed;
  else
    p_m_speed = &VisualData->m_speed;
  wk->m_rate = *p_m_speed;
  battlemode = (u16)wk->battlemode;
  if (battlemode == 3)
    goto LABEL_26;
  if (battlemode == 1)
  {
LABEL_26:
    m_hokanrate = v19->m_hokanrate;
    v27 = m_hokanrate;
    if (m_hokanrate == INFINITY)
      LOWORD(v27) = 0;
    wk->beforeframe = v27;
    if (wk->next_motion_not_hokan)
    {
LABEL_29:
      wk->beforeframe = 0;
      wk->next_motion_not_hokan = 0;
      goto LABEL_30;
    }
    goto LABEL_30;
  }
  if ((wk->side & 0x80) == 0)
    goto LABEL_26;
  v31 = v19->m_hokanrate;
  v32 = v31;
  if (v31 == INFINITY)
    LOWORD(v32) = 0;
  wk->beforeframe = v32;
  next_motion_not_hokan = wk->next_motion_not_hokan;
  if (next_motion_not_hokan)
  {
    if (next_motion_not_hokan == 2)
    {
      wk->next_motion_not_hokan = 0;
      wk->beforeframe = 5;
      goto LABEL_30;
    }
    goto LABEL_29;
  }
  sbtlplayertblSetPlayerMotionData_Hokan(wk);
LABEL_30:
  m_mv_area_r = MotionVisualData->m_mv_area_r;
  wk->afterframe = v7;
  wk->framecnt = 0;
  actaiwk = wk->actaiwk;
  wk->motionst = 0;
  actaiwk->priv_area_r = m_mv_area_r;
  return 1;
}

// 0x20100b0
s32 sBtlGetMotionNo(SBTLUNIT_WORK *wk, SBTLUNIT_SIDE side, SBTLUNIT_MOTION motionno) {
  char v5;
  s32 waitwalkMot;
  s32 **v9;
  s64 sbtlmotion_tbl_local;

  v5 = side;
  if ((u32)motionno <= 2)
  {
    waitwalkMot = wk->waitwalkMot;
    if (waitwalkMot)
    {
      waitwalkMot = wk->waitwalkMot;
      motionno = waitwalkMot;
      v9 = &sbtlmotion_tbl[wk->motion_setno];
      return (*v9)[motionno];
    }
  }
  if ((wk->status & 0x8000000) != 0)
  {
    sbtlmotion_tbl_local = (s64)sbtlmotion_tbl + 8 * wk->motion_setno;
    goto LABEL_17;
  }
  if ((v5 & 0x80) == 0)
  {
    if (wk->minor >= 1)
    {
      v9 = &sbtlmotion_tbl[3];
      return (*v9)[motionno];
    }
    sbtlmotion_tbl_local = sbtlmotion_tbl;
LABEL_17:
    v9 = (sbtlmotion_tbl_local + 32);
    return (*v9)[motionno];
  }
  v9 = &sbtlmotion_tbl[1];
  return (*v9)[motionno];
}

// 0x20112b0
void sBtlResetAtkSklEff(SBTLUNIT_WORK *wk) {
  s32 v5;
  s32 *m_Items;
  s32 v7;
  char *v8;
  s32 v9;
  s32 ListID;
  SBTLEFF_LISTWORK *effList;
  s32 v13;
  s32 v14;
  SBTLDMG_HITLISTWORK *hitList;

  m_Items = aSklDflt;
  v5 = aSklDflt[0];
  if (!v5)
    return;
  v7 = 1;
  do
  {
    v5 = *m_Items;
    ListID = wk->ListID;
    effList = wk->effList;
    sBtlDeleteEffectData_SkillIDTypeUnit(effList, v5, 1u, ListID);
    v13 = wk->ListID;
    v14 = *m_Items;
    hitList = wk->hitList;
    sBtlDltHit_by_UnitSkl(hitList, v13, v14);
    v8 = (char *)aSklDflt + 4 * v7++;
    v9 = *((u32 *)v8 + 8);
    m_Items = (v8 + 32);
    v5 = v9;
  }
  while (v9);
}

// 0x2010740
bool sBtlSetMotion(SBTLUNIT_WORK *wk, SBTLUNIT_MOTION setmotionno, s32 bframe, s32 aframe, s8 flg) {
  s32 devilid;
  bool v13;
  _BOOL4 v15;
  s32 battlemode;
  s32 v21;
  sdatUnitWork_t *para;
  u32 BadStatus;
  s32 waitwalkMot;
  sdatUnitWork_t *v26;
  s32 v27;
  s32 next_motionID;
  dds3ModelHandle_t *hModel;
  SBTLUNIT_WORK *v31;
  bool v32;
  s32 v33;
  s32 cmstatus;
  s32 v35;
  s32 side;
  s32 MotionNo;
  u16 major;
  s32 v40;
  s32 minor;
  MOTIONDATA_WORK *MotionVisualData;
  MOTIONDATA_WORK *v43;
  s16 v44;
  u16 v45;
  s32 v46;
  f32 m_speed;
  u16 v48;
  s32 v49;
  f32 *p_m_speed;
  f32 *v52;
  f32 v53;
  s32 v54;
  f32 m_mv_area_r;
  SBTLACTAI_WORK *actaiwk;
  f32 m_hokanrate;
  s32 v59;
  s32 next_motion_not_hokan;
  sdatUnitWork_t *v61;
  SBTLUNIT_WORK *v63;
  bool v64;
  sdatUnitWork_t *v65;

  devilid = (u16)wk->para->devilid;
  v13 = devilid != 257 || (u32)setmotionno > 0x10 || ((1 << setmotionno) & 0x1055C) == 0;
  if (v13)
  {
    if (wk->bk_cmbret_mot_Locked)
    {
      if (devilid == 530)
        goto LABEL_13;
    }
    else
    {
      wk->bk_cmbret_mot_setmotionno = setmotionno;
      wk->bk_cmbret_mot_bframe = bframe;
      wk->bk_cmbret_mot_aframe = aframe;
      wk->bk_cmbret_mot_flg = flg;
      if (devilid == 530)
      {
LABEL_13:
        if (setmotionno != 14)
          goto LABEL_19;
        goto LABEL_18;
      }
    }
    if (setmotionno != 14 || devilid != 532)
    {
LABEL_19:
      if (wk->motion_SetSkip)
      {
        wk->motion_SetSkip = 0;
        return 1;
      }
      if (sBtlGetPChara() != wk)
      {
        v15 = 0;
        goto LABEL_24;
      }
      if ((~wk->side & 0x81) != 0)
        goto LABEL_32;
      battlemode = (u16)wk->battlemode;
      if (battlemode == 3)
      {
LABEL_32:
        v15 = 0;
        goto LABEL_34;
      }
      else
      {
        battlemode = (u16)wk->battlemode;
        v15 = battlemode != 1;
LABEL_34:
        sBtlResetATKEffect();
LABEL_24:
        sBtlResetAtkSklEff(wk);
        if (setmotionno == 75)
        {
          if (sBtlGetPChara() == wk)
            return 1;
        }
        else if (!setmotionno && (wk->flg & 0x20) != 0)
        {
          return 1;
        }
        if ((wk->status & 0x400000) != 0)
          v21 = 0;
        else
          v21 = setmotionno;
        if (!(wk->status & 0x400000 | setmotionno))
        {
          if ((wk->hstatus & 0x3800000) == 0 && (wk->vstatus & 0x8000) == 0)
          {
            if (wk->battlemode != 1 || (wk->side & 1) == 0)
            {
              para = wk->para;
              BadStatus = sBtlGetBadStatus(para);
              if ((wk->side & 0x80) == 0)
                goto LABEL_180;
              if (!sBtlIsHuuma())
              {
LABEL_180:
                if (BadStatus > 0x16 || ((1 << BadStatus) & 0x600200) == 0)
                {
                  v65 = wk->para;
                  if (!sBtlIsKoufun(v65) && BadStatus != 16)
                    goto LABEL_56;
                }
                if (wk->byctCnt)
                {
LABEL_56:
                  v21 = 2;
                  waitwalkMot = wk->waitwalkMot;
                  if (!waitwalkMot)
                    goto LABEL_72;
                  goto LABEL_69;
                }
                if ((wk->status & 0x100000) == 0)
                {
                  v26 = wk->para;
                  if ((f32)((f32)v26->now->hp / (f32)v26->now->maxhp) < 0.26)
                  {
                    v27 = (u16)v26->devilid;
                    if (v27 != 263)
                    {
                      if (v27 == 302)
                        v21 = setmotionno;
                      else
                        v21 = 2;
                      waitwalkMot = wk->waitwalkMot;
                      if (!waitwalkMot)
                        goto LABEL_72;
                      goto LABEL_69;
                    }
                  }
                }
              }
            }
          }
          v21 = 0;
        }
        waitwalkMot = wk->waitwalkMot;
        if (!waitwalkMot)
          goto LABEL_72;
LABEL_69:
        if ((u32)v21 <= 5 && ((1 << v21) & 0x25) != 0)
          v21 = waitwalkMot;
LABEL_72:
        if (!v15)
          goto LABEL_116;
        next_motionID = wk->next_motionID;
        if (next_motionID != 2)
        {
          if (next_motionID == 128)
          {
            if (v21 == 2)
            {
              if (wk->motionno == 128)
              {
                hModel = wk->hModel;
                if (mdlGetMotionFrameF(hModel) >= 15.0)
                  goto LABEL_83;
                if (sBtlCheckMotionEnd(wk))
                {
LABEL_83:
                  v21 = 2;
                  goto LABEL_108;
                }
              }
              goto LABEL_86;
            }
          }
          else if (v21 == 2 && next_motionID != 129)
          {
LABEL_86:
            v21 = 128;
            goto LABEL_108;
          }
        }
        if (v21 <= 57)
        {
          if (v21 == 2 || v21 == 12)
            goto LABEL_108;
          if ((u32)(v21 - 58) < 0xFFFFFFFC)
            goto LABEL_95;
        }
        else
        {
          if ((u32)v21 <= 0x84)
          {
            if ((u32)(v21 - 83) <= 0xFFFFFFFB)
            {
              switch (v21)
              {
                case 126:
                case 127:
                  goto LABEL_100;
                case 128:
                  goto LABEL_108;
                case 130:
                case 132:
                  goto LABEL_104;
                default:
                  goto LABEL_95;
              }
              goto LABEL_108;
            }
LABEL_100:
            v31 = wk;
            v32 = 0;
            goto LABEL_103;
          }
          if (v21 == 139)
          {
            v61 = wk->para;
            v13 = sBtlGetBadStatus(v61) == 6;
            if (v13)
            {
              v63 = wk;
              v64 = 0;
            }
            else
            {
              v63 = wk;
              v64 = 1;
            }
            sBtlPlayerSetMantOnOff(v63, v64, 0);
            v21 = 139;
            goto LABEL_108;
          }
          if (v21 != 137)
          {
LABEL_95:
            v31 = wk;
            v32 = 1;
LABEL_103:
            v33 = 0;
LABEL_107:
            sBtlPlayerSetMantOnOff(v31, v32, v33);
LABEL_108:
            cmstatus = wk->cmstatus;
            if ((cmstatus & 0x10) != 0)
              v35 = 104;
            else
              v35 = v21;
            if ((cmstatus & 0x8000) != 0)
              v21 = 78;
            else
              v21 = v35;
            if ((cmstatus & 0x8010) != 0)
              wk->cmstatus &= wk->cmstatus & 0x8000 ^ 0xFFFFFFEF;
LABEL_116:
            wk->next_motionID = v21;
            side = wk->side;
            MotionNo = sBtlGetMotionNo(wk, side, v21);
            wk->next_motionno = MotionNo;
            major = wk->major;
            v40 = MotionNo;
            minor = wk->minor;
            MotionVisualData = sBtlGetMotionVisualData(major, minor, v40);
            v43 = sBtlGetMotionVisualData(wk->major, wk->minor, wk->motionno);
            if (wk->battlemode == 3)
            {
              if ((wk->side & 1) != 0)
              {
                v44 = 1;
                if (v21 == 3 || v21 == 29)
                  goto LABEL_128;
              }
            }
            v44 = bframe;
            if (flg)
            {
LABEL_128:
              wk->beforeframe = v44;
              if ((MotionVisualData->flg & 1) != 0)
              {
                m_speed = MotionVisualData->m_speed;
              }
              else
              {
                v45 = wk->major;
                v46 = wk->minor;
                m_speed = sBtlGetVisualData(v45, v46)->m_speed;
              }
              wk->m_rate = m_speed;
              goto LABEL_147;
            }
            v48 = wk->major;
            v49 = wk->minor;
            p_m_speed = &sBtlGetVisualData(v48, v49)->m_speed;
            if ((MotionVisualData->flg & 1) != 0)
              v52 = &MotionVisualData->m_speed;
            else
              v52 = p_m_speed;
            wk->m_rate = *v52;
            if (wk->battlemode != 3 && (wk->side & 0x80) != 0)
            {
              m_hokanrate = v43->m_hokanrate;
              v59 = m_hokanrate;
              if (m_hokanrate == INFINITY)
                LOWORD(v59) = 0;
              wk->beforeframe = v59;
              next_motion_not_hokan = wk->next_motion_not_hokan;
              if (!next_motion_not_hokan)
              {
                sbtlplayertblSetPlayerMotionData_Hokan(wk);
                goto LABEL_147;
              }
              if (next_motion_not_hokan == 2)
              {
                wk->next_motion_not_hokan = 0;
                wk->beforeframe = 5;
                goto LABEL_147;
              }
            }
            else
            {
              v53 = v43->m_hokanrate;
              v54 = v53;
              if (v53 == INFINITY)
                LOWORD(v54) = 0;
              wk->beforeframe = v54;
              if (!wk->next_motion_not_hokan)
                goto LABEL_147;
            }
            wk->beforeframe = 0;
            wk->next_motion_not_hokan = 0;
LABEL_147:
            m_mv_area_r = MotionVisualData->m_mv_area_r;
            wk->afterframe = aframe;
            wk->framecnt = 0;
            actaiwk = wk->actaiwk;
            wk->motionst = 0;
            actaiwk->priv_area_r = m_mv_area_r;
            return 1;
          }
        }
LABEL_104:
        v31 = wk;
        v32 = 1;
        v33 = 1;
        goto LABEL_107;
      }
      goto LABEL_34;
    }
LABEL_18:
    setmotionno = 1;
    goto LABEL_19;
  }
  return 1;
}

// 0x2011450
bool sBtlIsDying(SBTLUNIT_WORK *wk) {
  return (f32)((f32)wk->para->now->hp / (f32)wk->para->now->maxhp) < 0.26;
}

// 0x2011480
bool sBtlCutMotion(SBTLUNIT_WORK *wk, f32 m_rate) {
  dds3ModelHandle_t *hModel;
  f32 MotionFrame;

  hModel = wk->hModel;
  if (hModel)
  {
    MotionFrame = mdlGetMotionFrame(wk->hModel);
    if (MotionFrame < m_rate)
    {
      wk->m_rate = m_rate - MotionFrame;
      return 1;
    }
  }
  return 0;
}

// 0x2011540
bool sBtlSetFade(SBTLUNIT_WORK *wk, SBTLUNIT_VST flg, s32 start, s32 count, s32 para) {
  s32 vstatus;

  vstatus = wk->vstatus;
  if ((flg & vstatus & 2) != 0)
    return 1;
  wk->fadecnt = 0;
  wk->vstatus = vstatus | flg;
  wk->fade_sttime = start;
  wk->cmpfade = count;
  wk->fadepara = para;
  if (flg != 1 || wk->dissolveAlpha != 0.0)
    return 1;
  wk->dissolveAlpha = 1.0;
  return 1;
}

// 0x2011590
bool sBtlFadeProc(SBTLUNIT_WORK *wk) {
  bool result;
  s16 v5;
  s32 fade_sttime;
  s32 cmpfade;
  s32 vstatus;
  s32 v9;
  s32 v10;
  s32 v11;
  s32 v12;
  u32 dstcolor;
  u32 color_high;
  u32 color;
  s32 v16;
  s32 fadepara;
  s32 v18;
  s32 v19;
  s32 x;

  if (wk->kaiwaflg)
    goto LABEL_19;
  if (!!IsSceanStop())
  {
    if ((wk->status & 0x10) == 0 && !sBtlCheckEnshutuSummonUnit(wk))
      return 0;
  }
  if ((wk->status & 0x8000000) == 0)
    goto LABEL_19;
  if ((wk->status & 0x10) == 0)
    return 0;
LABEL_19:
  v5 = wk->fadecnt + 1;
  fade_sttime = wk->fade_sttime;
  wk->fadecnt = v5;
  if (v5 < fade_sttime)
    return 0;
  cmpfade = wk->cmpfade;
  if (cmpfade)
  {
    if (cmpfade < 1)
    {
      if (cmpfade == -2)
      {
        if ((u16)(-21845 * v5 + 10922) <= 0x5554u)
          goto LABEL_28;
      }
      else if (cmpfade != -1 || (v5 & 1) != 0)
      {
        goto LABEL_28;
      }
      return 1;
    }
    if (cmpfade + fade_sttime <= v5)
      wk->vstatus &= 0xFFFFFBFC;
  }
LABEL_28:
  vstatus = wk->vstatus;
  wk->ditherAlpha = (vstatus & 0x400) == 0;
  if ((wk->status & 0x100000) != 0 && (wk->para->badstatus & 0x200) != 0)
  {
    dstcolor = wk->dstcolor;
    color_high = HIBYTE(wk->color);
    if (dstcolor)
      color = wk->dstcolor;
    else
      color = wk->color;
    if (dstcolor)
      v16 = HIBYTE(dstcolor);
    else
      v16 = 128;
    fadepara = wk->fadepara;
    if ((vstatus & 1) == 0)
    {
      v19 = color_high - fadepara;
      LimitRange(&v19, 0, v16);
      v11 = v19;
      wk->color = color & 0xFFFFFF | ((u8)v19 << 24);
      if ((vstatus & 0x400) == 0)
        goto LABEL_35;
LABEL_34:
      wk->dissolveAlpha = (f32)v11 * 0.0078125;
LABEL_35:
      result = 1;
      if (v11 <= 0)
      {
        wk->ditherAlpha = 1;
        wk->dissolveAlpha = 1.0;
        wk->vstatus &= 0xFFFFFBFD;
        if ((wk->flg & 1) != 0)
          wk->mode = 9;
      }
      return result;
    }
    v19 = fadepara + color_high;
    LimitRange(&v19, 0, v16);
    v18 = v19;
    wk->color = color & 0xFFFFFF | ((u8)v19 << 24);
    if ((vstatus & 0x400) != 0)
      wk->dissolveAlpha = (f32)v18 * 0.0078125;
    result = 1;
    if (v18 >= v16)
    {
LABEL_61:
      wk->ditherAlpha = 1;
      wk->dissolveAlpha = 1.0;
      wk->vstatus &= 0xFFFFFBFE;
    }
  }
  else
  {
    v9 = HIBYTE(wk->color);
    v10 = wk->fadepara;
    if ((vstatus & 1) == 0)
    {
      x = v9 - v10;
      LimitRange(&x, 0, 128);
      v11 = x;
      HIBYTE(wk->color) = x;
      if ((vstatus & 0x400) == 0)
        goto LABEL_35;
      goto LABEL_34;
    }
    x = v10 + v9;
    LimitRange(&x, 0, 128);
    v12 = x;
    HIBYTE(wk->color) = x;
    if ((vstatus & 0x400) != 0)
      wk->dissolveAlpha = (f32)v12 * 0.0078125;
    result = 1;
    if (v12 >= 128)
      goto LABEL_61;
  }
  return result;
}

// 0x20119b0
static bool RGBFade(SBTLUNIT_WORK *wk) {
  s32 fadergb;
  u32 color;
  s32 v7;
  s32 v8;
  s32 v9;
  s32 v10;
  s32 v11;
  s32 x;

  if (!!IsSceanStop())
  {
    if ((wk->status & 0x10) == 0)
      return 0;
  }
  if ((wk->status & 0x8000000) != 0)
  {
    if ((wk->status & 0x10) == 0)
      return 0;
  }
  if (wk->fadergb)
    fadergb = wk->fadergb;
  else
    fadergb = 8;
  color = wk->color;
  v7 = BYTE1(color);
  v8 = BYTE2(color);
  x = fadergb + (u8)color;
  LimitRange(&x, 0, 128);
  v11 = v7 + fadergb;
  LimitRange(&v11, 0, 128);
  v10 = v8 + fadergb;
  LimitRange(&v10, 0, 128);
  v9 = x;
  wk->color = (v10 << 16) | (HIBYTE(wk->color) << 24) | (v11 << 8) | x;
  if (v9 >= 128)
    wk->vstatus &= ~0x200000u;
  return 1;
}

// 0x2011b80
SBTLUNIT_LISTWORK *sBtlCreateTargetList_MASK(SBTLUNIT_SIDE side, SBTLUNIT_ST mask, SBTLUNIT_VST mask_v) {
  SBTLUNIT_LISTWORK *UnitList;
  s64 i;
  SBTLUNIT_LISTWK *v9;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  u32 status;
  u32 v14;
  bool v15;
  bool v16;
  u32 v18;
  _BOOL4 v19;
  s64 number;
  SBTLUNIT_LISTWK *pUnitL;
  s64 v22;

  UnitList = sBtlCreateUnitList(48);
  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 0x3F) != side)
      continue;
    status = pUnit->actwk->status;
    if (status == 10)
      continue;
    if (pUnit->para->devilid != 311)
    {
      v14 = pUnit->status;
      if ((v14 & 0x1000) == 0)
      {
        v15 = (pUnit->status & 0x4800) == 0x4800 || status == 11;
        v16 = v15 || status == 14;
        if (!v16 && pUnit->actaiwk->mode != 9 && status != 40 && pUnit->mode >= 5)
        {
          if (mask)
          {
            v18 = v14 & mask;
            v19 = v18 != 0;
            if (!mask_v)
            {
              if (v18)
                continue;
              goto LABEL_41;
            }
          }
          else
          {
            if (!mask_v)
            {
LABEL_41:
              number = (u32)UnitList->number;
              if ((s32)number >= 1)
              {
                pUnitL = UnitList->pUnitL;
                v22 = 0;
                while (pUnitL[v22]->pUnit)
                {
                  if (number == ++v22)
                    goto LABEL_7;
                }
                v9 = pUnitL[v22];
                ++UnitList->count;
                v9->pUnit = pUnit;
                v9 = ((char *)v9 + 24);
                LODWORD(v9[-1].pUnit) = v22;
              }
              continue;
            }
            v19 = 0;
          }
          if (pUnit->vstatus & mask_v | v19)
            continue;
          goto LABEL_41;
        }
      }
    }
LABEL_7:
    ;
  }
  return UnitList;
}

// 0x2011e50
SBTLUNIT_LISTWORK *sBtlCreateTargetList_AI(SBTLUNIT_SIDE side) {
  SBTLUNIT_LISTWORK *UnitList;
  s64 i;
  SBTLUNIT_LISTWK *v5;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  u32 status;
  bool v10;
  bool v11;
  s64 number;
  SBTLUNIT_LISTWK *pUnitL;
  s64 v15;

  UnitList = sBtlCreateUnitList(48);
  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 0x3F) == side)
    {
      status = pUnit->actwk->status;
      if (status != 35)
      {
        if (status == 10)
          continue;
        if (pUnit->para->devilid != 311 && (pUnit->status & 0x1000) == 0)
        {
          v10 = (pUnit->status & 0x4800) == 0x4800 || status == 11;
          v11 = v10 || status == 14;
          if (!v11 && pUnit->actaiwk->mode != 9 && status != 40 && pUnit->mode >= 5)
          {
            number = (u32)UnitList->number;
            if ((s32)number >= 1)
            {
              pUnitL = UnitList->pUnitL;
              v15 = 0;
              while (pUnitL[v15]->pUnit)
              {
                if (number == ++v15)
                  goto LABEL_7;
              }
              v5 = pUnitL[v15];
              ++UnitList->count;
              v5->pUnit = pUnit;
              v5 = ((char *)v5 + 24);
              LODWORD(v5[-1].pUnit) = v15;
            }
          }
        }
      }
    }
LABEL_7:
    ;
  }
  return UnitList;
}

// 0x2012070
SBTLUNIT_LISTWORK *sBtlCreateTargetList(SBTLUNIT_SIDE side) {
  SBTLUNIT_LISTWORK *UnitList;
  s64 i;
  SBTLUNIT_LISTWK *v5;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  SBTLACTION_WORK *actwk;
  SBTLACTAI_WORK *actaiwk;
  u32 status;
  bool v12;
  s32 mode;
  s64 number;
  SBTLUNIT_LISTWK *pUnitL;
  s64 v19;

  UnitList = sBtlCreateUnitList(48);
  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 0x3F) == side)
    {
      actwk = pUnit->actwk;
      if (actwk->status != 35)
      {
        {
          actaiwk = pUnit->actaiwk;
          if (actaiwk)
          {
            status = actwk->status;
            if (status != 10)
            {
              v12 = (pUnit->status & 0x5000) != 0 || status == 11;
              if (!v12 && status != 14)
              {
                mode = actaiwk->mode;
                if (status != 30 && mode != 9 && status != 40 && pUnit->mode >= 5)
                {
                  number = (u32)UnitList->number;
                  if ((s32)number >= 1)
                  {
                    pUnitL = UnitList->pUnitL;
                    v19 = 0;
                    while (pUnitL[v19]->pUnit)
                    {
                      if (number == ++v19)
                        goto LABEL_7;
                    }
                    v5 = pUnitL[v19];
                    ++UnitList->count;
                    v5->pUnit = pUnit;
                    v5 = ((char *)v5 + 24);
                    LODWORD(v5[-1].pUnit) = v19;
                  }
                }
              }
            }
          }
        }
      }
    }
LABEL_7:
    ;
  }
  return UnitList;
}

// 0x2012300
SBTLUNIT_LISTWORK *sBtlCreateTargetList_DeadOn(SBTLUNIT_SIDE side) {
  SBTLUNIT_LISTWORK *UnitList;
  s64 i;
  SBTLUNIT_LISTWK *v5;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s64 number;
  SBTLUNIT_LISTWK *pUnitL;
  s64 v11;

  UnitList = sBtlCreateUnitList(48);
  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 0x3F) == side && pUnit->actwk->status != 35)
    {
      number = (u32)UnitList->number;
      if ((s32)number < 1)
        continue;
      pUnitL = UnitList->pUnitL;
      v11 = 0;
      while (pUnitL[v11]->pUnit)
      {
        if (number == ++v11)
          goto LABEL_7;
      }
      v5 = pUnitL[v11];
      ++UnitList->count;
      v5->pUnit = pUnit;
      v5 = ((char *)v5 + 24);
      LODWORD(v5[-1].pUnit) = v11;
    }
LABEL_7:
    ;
  }
  return UnitList;
}

// 0x20124b0
s32 sBtlCreateTargetList_ALLHIT(void) {
  SBTLUNIT_LISTWORK *UnitList;
  SBTLUNIT_LISTWORK *v4;
  s64 i;
  SBTLUNIT_LISTWK *v6;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s64 number;
  SBTLUNIT_LISTWK *pUnitL;
  s64 v12;
  s32 v13;
  SBTLUNIT_LISTWK *v14;
  SBTLUNIT_LISTWK *v15;
  f32 v16;
  s64 v17;
  SBTLUNIT_WORK *v18;
  u32 status;
  bool v20;
  SBTLUNIT_WORK *v21;
  f32 x;
  s64 v25;
  SBTLUNIT_LISTWK *v26;
  s64 v27;
  s64 j;
  u32 v29;
  bool v30;
  SBTLUNIT_WORK *v31;
  s32 ListID;
  s32 v37;
  s64 k;
  s32 v39;
  s64 ii;
  SBTLUNIT_LISTWK *v41;
  SBTLUNIT_WORK *v42;
  SBTLUNIT_WORK *v43;
  s32 v44;
  s64 v45;
  SBTLUNIT_LISTWK *v46;
  SBTLUNIT_WORK *v47;
  SBTLUNIT_WORK *v48;
  s32 v49;
  s64 n;
  SBTLUNIT_LISTWK *v51;
  SBTLUNIT_WORK *v52;
  SBTLUNIT_WORK *v53;
  s32 v54;
  s64 v55;
  SBTLUNIT_LISTWK *v56;
  SBTLUNIT_WORK *v57;
  SBTLUNIT_WORK *v58;
  SBTLUNIT_LISTWK *v60;
  SBTLUNIT_WORK *p_pUnit;
  SBTLUNIT_WORK *v62;
  s32 v63;
  s64 m;
  SBTLUNIT_LISTWK *v65;
  SBTLUNIT_WORK *v66;
  SBTLUNIT_WORK *v67;
  struct sdfVector4_t pos;
  struct sdfVector4_t v69;
  sdfVector4_t ppos;

  *(u64 *)&ppos.x = 0;
  *(u64 *)&ppos.z = 0;
  UnitList = sBtlCreateUnitList(48);
  v4 = sBtlCreateUnitList(48);
  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((~pUnit->status & 0x8800) != 0)
      continue;
    number = (u32)UnitList->number;
    if ((s32)number < 1)
      continue;
    pUnitL = UnitList->pUnitL;
    v12 = 0;
    while (pUnitL[v12]->pUnit)
    {
      if (number == ++v12)
        goto LABEL_7;
    }
    v6 = pUnitL[v12];
    v6->pUnit = pUnit;
    v6 = ((char *)v6 + 24);
    LODWORD(v6[-1].pUnit) = v12;
    ++UnitList->count;
LABEL_7:
    ;
  }
  if (UnitList->count >= 1)
  {
    v13 = 0;
    while (2)
    {
      if (UnitList->number < 1)
        goto LABEL_28;
      v16 = -10000.0;
      v17 = 0;
      v18 = 0;
      while (2)
      {
        v21 = UnitList->pUnitL[v17]->pUnit;
        if (v21)
        {
          status = v21->actwk->status;
          v20 = status > 0xE || ((1 << status) & 0x4C00) == 0;
          if (v20 && v21->actaiwk->mode != 9 && status != 40 && v21->mode >= 5)
          {
            pos = v21->pos;
            goto LABEL_46;
LABEL_47:
            vct_A = pos;
            x = v21->pos.x;
            if (v16 <= x)
              goto LABEL_52;
            goto LABEL_9000;
LABEL_46:
            goto LABEL_47;
            if (v16 <= x)
            {
LABEL_52:
              v16 = x;
              v13 = v17;
              v18 = v21;
            }
LABEL_9000:
          }
        }
        if (++v17 < UnitList->number)
          continue;
        break;
      }
      if (v18)
      {
        v25 = (u32)v4->number;
        if ((s32)v25 < 1)
          goto LABEL_27;
        v26 = v4->pUnitL;
        v27 = 0;
        while (v26[v27]->pUnit)
        {
          if (v25 == ++v27)
            goto LABEL_27;
        }
        v14 = v26[v27];
        v14->pUnit = v18;
        v14 = ((char *)v14 + 24);
        LODWORD(v14[-1].pUnit) = v27;
        ++v4->count;
LABEL_27:
        v15 = UnitList->pUnitL[v13];
        v15->pUnit = 0;
        v15 = ((char *)v15 + 24);
        LODWORD(v15[-1].pUnit) = 0;
        --UnitList->count;
      }
LABEL_28:
      if (UnitList->count >= 1)
        continue;
      break;
    }
    if (v4->number >= 1)
    {
      for (j = 0; j < v4->number; ++j)
      {
        v31 = v4->pUnitL[j]->pUnit;
        if (!v31)
          continue;
        v29 = v31->actwk->status;
        v30 = v29 > 0xE || ((1 << v29) & 0x4C00) == 0;
        if (!v30 || v31->actaiwk->mode == 9)
          continue;
        if (v29 == 40 || v31->mode < 5)
          continue;
        v69 = v31->pos;
        vct_A = v69;
        if (!sBtlChangeWorldtoScreen(&ppos))
          continue;
        if (ppos.x >= 224.0 && ppos.x <= 352.0)
        {
          ListID = v31->ListID;
          if (!UnitList)
            goto LABEL_128;
          v37 = UnitList->number;
          if (v37 < 1)
            goto LABEL_128;
          for (k = 0; k < v37; ++k)
          {
            v60 = UnitList->pUnitL[k];
            v62 = v60->pUnit;
            p_pUnit = &v60->pUnit;
            if (v62)
            {
              p_pUnit = 0;
              v37 = UnitList->number;
            }
          }
          if (v4)
          {
LABEL_128:
            v63 = v4->number;
            if (v63 >= 1)
            {
              for (m = 0; m < v63; ++m)
              {
                v65 = v4->pUnitL[m];
                v67 = v65->pUnit;
                v66 = &v65->pUnit;
                if (v67)
                {
                  v66 = 0;
                  v63 = v4->number;
                }
              }
            }
          }
          return ListID;
        }
      }
    }
    if (!UnitList)
    {
LABEL_117:
      v54 = v4->number;
      if (v54 >= 1)
      {
        v55 = 0;
        ListID = -1;
        do
        {
          v56 = v4->pUnitL[v55];
          v58 = v56->pUnit;
          v57 = &v56->pUnit;
          if (v58)
          {
            v57 = 0;
            v54 = v4->number;
          }
          ++v55;
        }
        while (v55 < v54);
        return ListID;
      }
      return -1;
    }
    v49 = UnitList->number;
    if (v49 >= 1)
    {
      for (n = 0; n < v49; ++n)
      {
        v51 = UnitList->pUnitL[n];
        v53 = v51->pUnit;
        v52 = &v51->pUnit;
        if (v53)
        {
          v52 = 0;
          v49 = UnitList->number;
        }
      }
      if (!v4)
        return -1;
    }
    goto LABEL_117;
  }
  v39 = UnitList->number;
  if (v39 >= 1)
  {
    for (ii = 0; ii < v39; ++ii)
    {
      v41 = UnitList->pUnitL[ii];
      v43 = v41->pUnit;
      v42 = &v41->pUnit;
      if (v43)
      {
        v42 = 0;
        v39 = UnitList->number;
      }
    }
  }
  if (!v4)
    return -1;
  v44 = v4->number;
  if (v44 < 1)
    return -1;
  v45 = 0;
  ListID = -1;
  do
  {
    v46 = v4->pUnitL[v45];
    v48 = v46->pUnit;
    v47 = &v46->pUnit;
    if (v48)
    {
      v47 = 0;
      v44 = v4->number;
    }
    ++v45;
  }
  while (v45 < v44);
  return ListID;
}

// 0x2012c20
SBTLUNIT_LISTWORK *sBtlCreateTargetList_Talk(SBTLUNIT_SIDE side) {
  SBTLUNIT_LISTWORK *UnitList;
  s64 i;
  SBTLUNIT_LISTWK *v6;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  SBTLACTION_WORK *actwk;
  SBTLACTAI_WORK *actaiwk;
  u32 status;
  bool v13;
  s32 mode;
  s64 number;
  SBTLUNIT_LISTWK *pUnitL;
  s64 v20;
  s32 v21;
  s32 v22;
  SBTLUNIT_LISTWK *v23;
  s32 v24;
  f32 v25;
  s64 v26;
  SBTLUNIT_WORK *v27;
  u32 v28;
  bool v29;
  SBTLUNIT_WORK *v30;
  f32 x;
  SBTLUNIT_LISTWORK *v35;
  s64 v36;
  SBTLUNIT_LISTWORK *v37;
  s64 v38;
  SBTLUNIT_LISTWK *v39;
  s64 v40;
  SBTLUNIT_LISTWK *v41;
  SBTLUNIT_LISTWK *v42;
  s64 v43;
  SBTLUNIT_LISTWK *v44;
  s32 v45;
  s64 k;
  SBTLUNIT_LISTWK *v47;
  SBTLUNIT_WORK *v48;
  SBTLUNIT_WORK *v49;
  s32 v50;
  s64 j;
  SBTLUNIT_LISTWK *v52;
  SBTLUNIT_WORK *p_pUnit;
  SBTLUNIT_WORK *v54;
  struct sdfVector4_t pos;
  SBTLUNIT_LISTWORK *v57;

  UnitList = sBtlCreateUnitList(48);
  v57 = sBtlCreateUnitList(48);
  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 0x3F) == side && (pUnit->status & 0x1000) == 0)
    {
      actwk = pUnit->actwk;
      if (actwk->status != 35)
      {
        {
          actaiwk = pUnit->actaiwk;
          if (actaiwk)
          {
            status = actwk->status;
            if (status != 10)
            {
              v13 = (pUnit->status & 0x5000) != 0 || status == 11;
              if (!v13 && status != 14)
              {
                mode = actaiwk->mode;
                if (status != 30 && mode != 9 && status != 40 && pUnit->mode >= 5)
                {
                  number = (u32)UnitList->number;
                  if ((s32)number >= 1)
                  {
                    pUnitL = UnitList->pUnitL;
                    v20 = 0;
                    while (pUnitL[v20]->pUnit)
                    {
                      if (number == ++v20)
                        goto LABEL_7;
                    }
                    v6 = pUnitL[v20];
                    ++UnitList->count;
                    v6->pUnit = pUnit;
                    v6 = ((char *)v6 + 24);
                    LODWORD(v6[-1].pUnit) = v20;
                  }
                }
              }
            }
          }
        }
      }
    }
LABEL_7:
    ;
  }
  if (UnitList->count < 1)
  {
    v50 = UnitList->number;
    if (v50 >= 1)
    {
      for (j = 0; j < v50; ++j)
      {
        v52 = UnitList->pUnitL[j];
        v54 = v52->pUnit;
        p_pUnit = &v52->pUnit;
        if (v54)
        {
          p_pUnit = 0;
          v50 = UnitList->number;
        }
      }
    }
    return v57;
  }
  v21 = 0;
  v22 = 0;
  while (2)
  {
    if (UnitList->number < 1)
      goto LABEL_48;
    v25 = -10000.0;
    v26 = 0;
    v27 = 0;
    while (2)
    {
      v30 = UnitList->pUnitL[v26]->pUnit;
      if (v30)
      {
        v28 = v30->actwk->status;
        v29 = v28 > 0xE || ((1 << v28) & 0x4C00) == 0;
        if (v29 && v30->actaiwk->mode != 9 && v28 != 40 && v30->mode >= 5)
        {
          pos = v30->pos;
          goto LABEL_66;
LABEL_67:
          vct_A = pos;
          x = v30->pos.x;
          if (v25 <= x)
            goto LABEL_72;
          goto LABEL_9000;
LABEL_66:
          goto LABEL_67;
          if (v25 <= x)
          {
LABEL_72:
            v25 = x;
            v22 = v26;
            v27 = v30;
          }
LABEL_9000:
        }
      }
      if (++v26 < UnitList->number)
        continue;
      break;
    }
    if (v27)
    {
      if ((~v27->status & 0x8800) != 0)
      {
        v37 = v57;
        v38 = (u32)v57->number;
        if ((s32)v38 < 1)
          goto LABEL_47;
        v39 = v37->pUnitL;
        v40 = 0;
        while (v39[v40]->pUnit)
        {
          if (v38 == ++v40)
            goto LABEL_47;
        }
        v41 = v39[v40];
        v41->pUnit = v27;
        v41 = ((char *)v41 + 24);
        LODWORD(v41[-1].pUnit) = v40;
        ++v37->count;
      }
      else
      {
        ++v21;
        if (v21 == 6)
        {
          v35 = v57;
          v36 = (u32)v57->number;
          if ((s32)v36 < 1)
          {
LABEL_46:
            v21 = 6;
            goto LABEL_47;
          }
          v42 = v35->pUnitL;
          v43 = 0;
          while (v42[v43]->pUnit)
          {
            if (v36 == ++v43)
              goto LABEL_46;
          }
          v44 = v42[v43];
          v44->pUnit = v27;
          v44 = ((char *)v44 + 24);
          LODWORD(v44[-1].pUnit) = v43;
          ++v35->count;
          v21 = 6;
        }
      }
LABEL_47:
      v23 = UnitList->pUnitL[v22];
      v24 = UnitList->count - 1;
      v23->pUnit = 0;
      v23 = ((char *)v23 + 24);
      LODWORD(v23[-1].pUnit) = 0;
      UnitList->count = v24;
    }
LABEL_48:
    if (UnitList->count >= 1)
      continue;
    break;
  }
  v45 = UnitList->number;
  if (v45 >= 1)
  {
    for (k = 0; k < v45; ++k)
    {
      v47 = UnitList->pUnitL[k];
      v49 = v47->pUnit;
      v48 = &v47->pUnit;
      if (v49)
      {
        v48 = 0;
        v45 = UnitList->number;
      }
    }
  }
  return v57;
}

// 0x2013200
SBTLUNIT_LISTWORK *sBtlCreateTargetList_Analyze(SBTLUNIT_SIDE side) {
  SBTLUNIT_LISTWORK *UnitList;
  s64 i;
  SBTLUNIT_LISTWK *v6;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  SBTLACTION_WORK *actwk;
  SBTLACTAI_WORK *actaiwk;
  u32 status;
  bool v13;
  s32 mode;
  s64 number;
  SBTLUNIT_LISTWK *pUnitL;
  s64 v20;
  s32 v21;
  s32 v22;
  SBTLUNIT_LISTWK *v23;
  s32 v24;
  f32 v25;
  s64 v26;
  SBTLUNIT_WORK *v27;
  u32 v28;
  bool v29;
  SBTLUNIT_WORK *v30;
  f32 x;
  SBTLUNIT_LISTWORK *v35;
  s64 v36;
  SBTLUNIT_LISTWORK *v37;
  s64 v38;
  SBTLUNIT_LISTWK *v39;
  s64 v40;
  SBTLUNIT_LISTWK *v41;
  SBTLUNIT_LISTWK *v42;
  s64 v43;
  SBTLUNIT_LISTWK *v44;
  s32 v45;
  s64 k;
  SBTLUNIT_LISTWK *v47;
  SBTLUNIT_WORK *v48;
  SBTLUNIT_WORK *v49;
  s32 v50;
  s64 j;
  SBTLUNIT_LISTWK *v52;
  SBTLUNIT_WORK *p_pUnit;
  SBTLUNIT_WORK *v54;
  struct sdfVector4_t pos;
  SBTLUNIT_LISTWORK *v57;

  UnitList = sBtlCreateUnitList(48);
  v57 = sBtlCreateUnitList(48);
  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 0x3F) == side && (pUnit->status & 0x1000) == 0)
    {
      actwk = pUnit->actwk;
      if (actwk->status != 35)
      {
        {
          actaiwk = pUnit->actaiwk;
          if (actaiwk)
          {
            status = actwk->status;
            if (status != 10)
            {
              v13 = (pUnit->status & 0x5000) != 0 || status == 11;
              if (!v13 && status != 14)
              {
                mode = actaiwk->mode;
                if (status != 30 && mode != 9 && status != 40 && pUnit->mode >= 5)
                {
                  number = (u32)UnitList->number;
                  if ((s32)number >= 1)
                  {
                    pUnitL = UnitList->pUnitL;
                    v20 = 0;
                    while (pUnitL[v20]->pUnit)
                    {
                      if (number == ++v20)
                        goto LABEL_7;
                    }
                    v6 = pUnitL[v20];
                    ++UnitList->count;
                    v6->pUnit = pUnit;
                    v6 = ((char *)v6 + 24);
                    LODWORD(v6[-1].pUnit) = v20;
                  }
                }
              }
            }
          }
        }
      }
    }
LABEL_7:
    ;
  }
  if (UnitList->count < 1)
  {
    v50 = UnitList->number;
    if (v50 >= 1)
    {
      for (j = 0; j < v50; ++j)
      {
        v52 = UnitList->pUnitL[j];
        v54 = v52->pUnit;
        p_pUnit = &v52->pUnit;
        if (v54)
        {
          p_pUnit = 0;
          v50 = UnitList->number;
        }
      }
    }
    return v57;
  }
  v21 = 0;
  v22 = 0;
  while (2)
  {
    if (UnitList->number < 1)
      goto LABEL_48;
    v25 = -10000.0;
    v26 = 0;
    v27 = 0;
    while (2)
    {
      v30 = UnitList->pUnitL[v26]->pUnit;
      if (v30)
      {
        v28 = v30->actwk->status;
        v29 = v28 > 0xE || ((1 << v28) & 0x4C00) == 0;
        if (v29 && v30->actaiwk->mode != 9 && v28 != 40 && v30->mode >= 5)
        {
          pos = v30->pos;
          goto LABEL_66;
LABEL_67:
          vct_A = pos;
          x = v30->pos.x;
          if (v25 <= x)
            goto LABEL_72;
          goto LABEL_9000;
LABEL_66:
          goto LABEL_67;
          if (v25 <= x)
          {
LABEL_72:
            v25 = x;
            v22 = v26;
            v27 = v30;
          }
LABEL_9000:
        }
      }
      if (++v26 < UnitList->number)
        continue;
      break;
    }
    if (v27)
    {
      if ((~v27->status & 0x8800) != 0)
      {
        v37 = v57;
        v38 = (u32)v57->number;
        if ((s32)v38 < 1)
          goto LABEL_47;
        v39 = v37->pUnitL;
        v40 = 0;
        while (v39[v40]->pUnit)
        {
          if (v38 == ++v40)
            goto LABEL_47;
        }
        v41 = v39[v40];
        v41->pUnit = v27;
        v41 = ((char *)v41 + 24);
        LODWORD(v41[-1].pUnit) = v40;
        ++v37->count;
      }
      else
      {
        ++v21;
        if (v21 == 6)
        {
          v35 = v57;
          v36 = (u32)v57->number;
          if ((s32)v36 < 1)
          {
LABEL_46:
            v21 = 6;
            goto LABEL_47;
          }
          v42 = v35->pUnitL;
          v43 = 0;
          while (v42[v43]->pUnit)
          {
            if (v36 == ++v43)
              goto LABEL_46;
          }
          v44 = v42[v43];
          v44->pUnit = v27;
          v44 = ((char *)v44 + 24);
          LODWORD(v44[-1].pUnit) = v43;
          ++v35->count;
          v21 = 6;
        }
      }
LABEL_47:
      v23 = UnitList->pUnitL[v22];
      v24 = UnitList->count - 1;
      v23->pUnit = 0;
      v23 = ((char *)v23 + 24);
      LODWORD(v23[-1].pUnit) = 0;
      UnitList->count = v24;
    }
LABEL_48:
    if (UnitList->count >= 1)
      continue;
    break;
  }
  v45 = UnitList->number;
  if (v45 >= 1)
  {
    for (k = 0; k < v45; ++k)
    {
      v47 = UnitList->pUnitL[k];
      v49 = v47->pUnit;
      v48 = &v47->pUnit;
      if (v49)
      {
        v48 = 0;
        v45 = UnitList->number;
      }
    }
  }
  return v57;
}

// 0x20137e0
SBTLUNIT_LISTWORK *sBtlCreateTargetList_Group(SBTLUNIT_SIDE side, s32 GroupID) {
  SBTLUNIT_LISTWORK *UnitList;
  s64 i;
  SBTLUNIT_LISTWK *v7;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  SBTLACTION_WORK *actwk;
  SBTLACTAI_WORK *actaiwk;
  u32 status;
  bool v14;
  s32 mode;
  bool v17;
  s64 number;
  SBTLUNIT_LISTWK *pUnitL;
  s64 v20;

  UnitList = sBtlCreateUnitList(48);
  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 0x3F) != side)
      continue;
    actwk = pUnit->actwk;
    if (!actwk)
      continue;
    actaiwk = pUnit->actaiwk;
    if (actaiwk)
    {
      status = actwk->status;
      if (status != 10)
      {
        v14 = (pUnit->status & 0x5000) != 0 || status == 11;
        if (!v14 && status != 14)
        {
          mode = actaiwk->mode;
          v17 = status == 30 || mode == 9;
          if (!v17 && pUnit->mode >= 5 && status != 35 && status != 40 && pUnit->GroupID == GroupID)
          {
            number = (u32)UnitList->number;
            if ((s32)number >= 1)
            {
              pUnitL = UnitList->pUnitL;
              v20 = 0;
              while (pUnitL[v20]->pUnit)
              {
                if (number == ++v20)
                  goto LABEL_7;
              }
              v7 = pUnitL[v20];
              ++UnitList->count;
              v7->pUnit = pUnit;
              v7 = ((char *)v7 + 24);
              LODWORD(v7[-1].pUnit) = v20;
            }
          }
        }
      }
    }
LABEL_7:
    ;
  }
  return UnitList;
}

// 0x2013a00
SBTLUNIT_LISTWORK *sBtlCreateTargetList_PForward(SBTLUNIT_SIDE side) {
  s64 v4;
  SBTLUNIT_LISTWORK *UnitList;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 playerID;
  SBATTLE_WORK *v12;
  f32 *pUnit;
  s64 i;
  SBTLUNIT_LISTWK *v16;
  SBTLUNIT_LISTWORK *v18;
  SBTLUNIT_WORK *v19;
  SBTLACTION_WORK *actwk;
  SBTLACTAI_WORK *actaiwk;
  u32 status;
  bool v23;
  bool v26;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 r2;
  f32 z;
  s64 number;
  SBTLUNIT_LISTWK *pUnitL;
  s64 v38;
  f32 v40;
  f32 v41;
  f32 v42;
  f32 v43;
  f32 vector1;
  sdfVector4_t v45;
  sdfVector4_t v46;
  sdfVector4_t v47;

  UnitList = sBtlCreateUnitList(48);
  UnitMng = wk->UnitMng;
  playerID = (u32)wk->playerID;
  if ((playerID & 0x80000000) != 0)
    goto LABEL_20;
  v12 = wk;
  if (!v12)
    goto LABEL_20;
  if (wk->UnitMng)
    goto LABEL_18;
LABEL_20:
  pUnit = 0;
  goto LABEL_21;
LABEL_18:
  if (UnitMng->number <= (s32)playerID)
    goto LABEL_20;
  pUnit = UnitMng->pUnitL[playerID]->pUnit;
LABEL_21:
  for (i = 0; ; ++i)
  {
    v18 = wk->UnitMng;
    if (i >= v18->number)
      break;
    v19 = v18->pUnitL[i]->pUnit;
    if (!v19)
      continue;
    if ((v19->side & 0x3F) == side)
    {
      actwk = v19->actwk;
      if (actwk->status != 35)
      {
        {
          actaiwk = v19->actaiwk;
          if (actaiwk)
          {
            status = actwk->status;
            if (status != 10)
            {
              v23 = (v19->status & 0x5000) != 0 || status == 11;
              if (!v23 && status != 14 && status != 30 && actaiwk->mode != 9)
              {
                v26 = status == 40 || v19->mode < 5;
                if (!v26 && pUnit != 0)
                {
                  v46 = *(sdfVector4_t *)(pUnit + 41);
                  v47.x = pUnit[45];
                  v31 = pUnit[46];
                  v32 = pUnit[47];
                  v33 = pUnit[48];
                  r2 = v19->pos.x;
                  z = v19->pos.z;
                  v43 = pUnit[42];
                  vector1 = pUnit[41];
                  v41 = pUnit[44];
                  v42 = pUnit[43];
                  v40 = pUnit[45];
                  v47.x = v40;
                  v46.w = v41;
                  v46.x = vector1;
                  v46.z = v42;
                  v46.y = v43;
                  v47.y = v31;
                  v47.z = v32;
                  v47.w = v33;
                  *(u64 *)&v45.x = 0;
                  *(u64 *)&v45.z = v4;
                  if (sBtlCheckCrossCircle_Rot(v46, v47, 1000.0, v45, r2, z))
                  {
                    number = (u32)UnitList->number;
                    if ((s32)number >= 1)
                    {
                      pUnitL = UnitList->pUnitL;
                      v38 = 0;
                      while (pUnitL[v38]->pUnit)
                      {
                        if (number == ++v38)
                          goto LABEL_23;
                      }
                      v16 = pUnitL[v38];
                      ++UnitList->count;
                      v16->pUnit = v19;
                      v16 = ((char *)v16 + 24);
                      LODWORD(v16[-1].pUnit) = v38;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
LABEL_23:
    ;
  }
  return UnitList;
}

// 0x2013dc0
void sBtlUpdateMiusinai(SBTLUNIT_WORK *wk) {
  SBTLUNIT_LISTWORK *UnitMng;
  s64 targetID;
  SBATTLE_WORK *v7;
  SBTLUNIT_WORK *pUnit;
  SBTLACTION_WORK *actwk;
  SBTLACTAI_WORK *actaiwk;
  u32 status;
  s32 mode;
  s32 v16;
  s32 encountno;

  UnitMng = wk->UnitMng;
  targetID = (u32)wk->actaiwk->targetID;
  if ((targetID & 0x80000000) != 0)
    goto LABEL_45;
  v7 = wk;
  if (!v7)
    goto LABEL_45;
  if (!v7->UnitMng)
    goto LABEL_45;
  if (UnitMng->number <= (s32)targetID || (pUnit = UnitMng->pUnitL[targetID]->pUnit) == 0)
  {
LABEL_45:
    encountno = wk->encountno;
    if (encountno == 46)
      goto LABEL_53;
    if (encountno != 55)
      goto LABEL_56;
    goto LABEL_9000;
    if (wk->encountno != 55)
    {
LABEL_56:
      wk->miusinai = 0;
      return;
    }
LABEL_9000:
LABEL_53:
    if ((wk->side & 1) != 0 && IsAction(5))
    {
LABEL_55:
      wk->miusinai = 1;
      return;
    }
    goto LABEL_56;
  }
  if (pUnit->kuramasi)
    goto LABEL_55;
  actwk = pUnit->actwk;
  if (!actwk)
    goto LABEL_55;
  actaiwk = pUnit->actaiwk;
  if (!actaiwk)
    goto LABEL_55;
  status = actwk->status;
  if (status == 10 || (pUnit->status & 0x5000) != 0)
    goto LABEL_55;
  if (status == 11 || status == 14)
    goto LABEL_55;
  mode = actaiwk->mode;
  if (status == 30 || mode == 9)
    goto LABEL_55;
  v16 = status == 40 || pUnit->mode < 5;
  wk->miusinai = v16;
}

// 0x2014060
bool sBtlCheckDamageTargetTemp(SBTLUNIT_WORK *wk) {
  if (wk)
    LOBYTE(wk) = wk->kuramasi == 0;
  return (char)wk;
}

// 0x2012280
bool sBtlCheckDamageTarget(SBTLUNIT_WORK *wk) {
  SBTLACTION_WORK *actwk;
  SBTLACTAI_WORK *actaiwk;
  u32 status;

  if (!wk)
    goto LABEL_6;
  actwk = wk->actwk;
  if (!actwk)
    return (char)actwk;
  actaiwk = wk->actaiwk;
  if (!actaiwk || (status = actwk->status, status == 10) || (wk->status & 0x5000) != 0)
  {
LABEL_6:
    LOBYTE(actwk) = 0;
    return (char)actwk;
  }
  LOBYTE(actwk) = 0;
  if (status == 11)
    return (char)actwk;
  if (status == 14)
    return (char)actwk;
  LOBYTE(actwk) = 0;
  if (status == 30 || actaiwk->mode == 9)
    return (char)actwk;
  return wk->mode > 4 && status != 40;
}

// 0x2014080
bool sBtlCheckDamageTarget_FastLoadNakama(SBTLUNIT_WORK *wk) {
  SBTLACTION_WORK *actwk;
  SBTLACTAI_WORK *actaiwk;
  u32 status;
  s32 mode;

  if (wk)
  {
    actwk = wk->actwk;
    if (actwk && (actaiwk = wk->actaiwk) != 0 && (status = actwk->status, status != 10) && (wk->status & 0x5000) == 0)
    {
      LOBYTE(wk) = 0;
      if (status != 11 && status != 14)
      {
        mode = actaiwk->mode;
        LOBYTE(wk) = status != 30 && mode != 9 && status != 40;
      }
    }
    else
    {
      LOBYTE(wk) = 0;
    }
  }
  return (char)wk;
}

// 0x20140f0
bool sBtlCheckDamageTargetUseItem(SBTLUNIT_WORK *wk) {
  u32 status;

  if (wk)
  {
    status = wk->actwk->status;
    LOBYTE(wk) = status != 10
              && (wk->status & 0x4000) == 0
              && status != 11
              && status != 14
              && status != 30
              && wk->actaiwk->mode != 9
              && status != 40
              && wk->mode > 4;
  }
  return (char)wk;
}

// 0x2009800
bool CheckLiveTarget(SBTLUNIT_WORK *wk) {
  u32 status;
  bool v3;
  bool result;

  status = wk->actwk->status;
  v3 = status > 0xE || ((1 << status) & 0x4C00) == 0;
  result = false;
  if (v3 && wk->actaiwk->mode != 9 && status != 40 && wk->mode > 4)
    return true;
  return result;
}

// 0x2011dd0
bool sBtlCheckLiveTarget_NotHitDmg(SBTLUNIT_WORK *wk) {
  u32 status;

  status = wk->actwk->status;
  return status != 10
      && wk->para->devilid != 311
      && (wk->status & 0x1000) == 0
      && (wk->status & 0x4800) != 0x4800
      && status != 11
      && status != 14
      && wk->actaiwk->mode != 9
      && status != 40
      && wk->mode > 4;
}

// 0x2014160
bool sBtlCheckLiveTarget_NotHitDmg_Kakusi(SBTLUNIT_WORK *wk) {
  u32 status;

  status = wk->actwk->status;
  return status != 10
      && wk->para->devilid != 311
      && (~wk->status & 0x4800) != 0
      && status != 11
      && status != 14
      && wk->actaiwk->mode != 9
      && status != 40
      && wk->mode > 4;
}

// 0x20141e0
bool sBtlCheckLiveTarget2(SBTLUNIT_WORK *wk) {
  u32 status;

  status = wk->actwk->status;
  return status != 10 && status != 40;
}

// 0x2014200
bool sBtlCheckTalkSelectTarget(SBTLUNIT_WORK *wk) {
  u32 status;
  bool v4;

  if ((wk->status & 0x100000) != 0)
    return 0;
  status = wk->actwk->status;
  v4 = status == 10 || status == 19;
  if (v4 || status == 54 && (wk->flg & 2) != 0 || wk->mode != 8 || (wk->vstatus & 0x1001) != 0 || wk->bYobidousa)
  {
    return 0;
  }
  if (wk->kuramasi)
    return 0;
  return sBtlCheckDamageTarget(wk);
}

// 0x20142d0
bool sBtlCheckTateSkillSelectTarget(SBTLUNIT_WORK *wk) {
  signed s32 status;
  bool result;
  SBTLUNIT_LISTWORK *TargetList;
  s64 count;
  SBTLUNIT_LISTWORK *v8;
  s64 m_Items;
  s64 v10;

  if ((wk->flg & 2) != 0)
    return 0;
  status = wk->actwk->status;
  if (status <= 19)
  {
    result = 0;
    if (status == 10 || status == 19)
      return result;
  }
  else if (status == 40)
  {
    return 0;
  }
  if (wk->mode != 8 || (wk->vstatus & 0x1001) != 0 || wk->bYobidousa)
    return 0;
  TargetList = sBtlCreateTargetList(2);
  count = (u32)TargetList->count;
  v8 = TargetList;
  if ((s32)count < 1)
  {
LABEL_24:
    sBtlDeleteUnitList(v8, 0);
    if (!wk || wk->kuramasi)
      return 0;
    if (!sBtlCheckDamageTarget(wk))
      return 0;
    return wk->not_tatezan == 0;
  }
  else
  {
    m_Items = TargetList->pUnitL;
    while (1)
    {
      v10 = *(u64 *)(*(u64 *)m_Items + 24);
      if (v10)
      {
        if (*(u8 *)(v10 + 1196))
          break;
      }
      m_Items += 8;
      if (!--count)
        goto LABEL_24;
    }
    sBtlDeleteUnitList(v8, 0);
    return 0;
  }
}

// 0x2014480
bool sBtlCheckExist(SBTLUNIT_WORK *wk) {
  u32 status;
  bool result;

  status = wk->actwk->status;
  result = false;
  if ((status & 0xFFFFFFFE) != 0xA && status != 14 && (wk->side & 0x18) == 0)
    return true;
  return result;
}

// 0x20144c0
bool sBtlCheckExist2(SBTLUNIT_WORK *wk) {
  return (wk->actwk->status & 0xFFFFFFFE) != 0xA && (wk->side & 0x18) == 0 && wk->mode > 4;
}

// 0x2014500
SBTLUNIT_WORK *sBtlSearchHitHelper_ID(SBTLUNIT_WORK *wk, s32 id, s32 max) {
  s32 v6;
  s32 v7;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;

  v6 = max + 301;
  if (v6 >= 302)
  {
    v7 = 301;
LABEL_6:
    for (i = 0; ; ++i)
    {
      UnitMng = wk->UnitMng;
      if (i >= UnitMng->number)
      {
        if (++v7 == v6)
          return 0;
        goto LABEL_6;
      }
      pUnit = UnitMng->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if (wk->ListID == pUnit->hithelperID && v7 == pUnit->hithelperno && (pUnit->status & 0x800) != 0)
      {
        return pUnit;
      }
    }
  }
  return 0;
}

// 0x2014640
bool sBtlCreateHitHelper(SBTLUNIT_WORK *wk, s32 devilid, s32 count) {
  DEVILDATA_WORK *DevilData;
  DEVILDATA_WORK *v10;
  s32 i;
  s32 minorno;
  SBTLUNIT_WORK *Unit;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  SBTLUNIT_LISTWK *pUnitL;
  s64 v18;
  s32 ID;
  s64 v20;
  SBTLUNIT_LISTWK *v21;
  u16 major;
  s32 minor;
  VISUALDATA_WORK *VisualData;
  SBTLACTAI_WORK *actaiwk;
  VISUALDATA_WORK *v27;
  s32 aishou;
  SBATTLE_WORK *v29;
  SBTLACTION_WORK *actwk;
  sdatUnitWork_t *para;
  SBTLAISYO_DATAWORK *Aisyotbl;
  u32 exsts;
  u32 v34;
  s32 v35;
  sdatUnitWork_t *v36;
  __int128 v37;
  sdatParaWork_t *now;
  sdatParaWork_t *backup;
  int32x2_t v40;
  SBTLACTAI_WORK *v41;
  s32 v42;
  s16 v44;
  struct sdfVector4_t pos;

  DevilData = sBtlGetDevilData(devilid, -1);
  if (count < 1)
    goto LABEL_40;
  goto LABEL_7;
  if (count >= 1)
  {
LABEL_7:
    v10 = DevilData;
    for (i = 0; i != count; ++i)
    {
      minorno = v10->minorno;
      Unit = sBtlCreateUnit(1u, minorno, 12);
      UnitMng = wk->UnitMng;
      number = (u32)UnitMng->number;
      if ((s32)number < 1)
        goto LABEL_19;
      goto LABEL_9001;
      if ((s32)number < 1)
      {
LABEL_19:
        ID = 0;
        goto LABEL_21;
      }
LABEL_9001:
      pUnitL = UnitMng->pUnitL;
      v18 = 0;
      while (pUnitL[v18]->pUnit)
      {
        if (number == ++v18)
          goto LABEL_19;
      }
      v20 = v18;
      v21 = pUnitL[v18];
      v21->pUnit = Unit;
      v21 = ((char *)v21 + 24);
      LODWORD(v21[-1].pUnit) = v18;
      ++UnitMng->count;
      ID = UnitMng->pUnitL[v20]->ID;
LABEL_21:
      Unit->ListID = ID;
      major = Unit->major;
      minor = Unit->minor;
      VisualData = sBtlGetVisualData(major, minor);
      actaiwk = Unit->actaiwk;
      Unit->hithelperno = i;
      v27 = VisualData;
      aishou = v10->aishou;
      Unit->aisyoid = v10->aishou;
      v29 = wk;
      actaiwk->status = actaiwk->status & 0xFFFFFF9F | 0x40;
      actwk = Unit->actwk;
      Unit->side = wk->side;
      LOWORD(actaiwk) = wk->ListID;
      actwk->status = 20;
      para = Unit->para;
      Unit->hithelperID = (s16)actaiwk;
      LOBYTE(actaiwk) = v10->level;
      para->devilid = devilid;
      para->level = (char)actaiwk;
      para->raceid = v10->kuda_id;
      Unit->bunriid = v10->bunriid;
      ++v29->enemy_num;
      Aisyotbl = sBtlGetAisyotbl(aishou);
      ClassCopy(Unit->para->aisyo, Aisyotbl, 0);
      ClassCopy(Unit->aisyo_bkup, Unit->para->aisyo, 0);
      exsts = v10->exsts;
      v34 = Unit->exsts;
      Unit->status |= v10->stflg | 0x800;
      v35 = exsts | v34;
      v36 = Unit->para;
      Unit->exsts = v35;
      v37 = *(_OWORD *)&v10->hp;
      now = v36->now;
      backup = v36->backup;
      now->hp = v37;
      now->mp = DWORD2(v37);
      *(_OWORD *)&backup->hp = v37;
      *(u64 *)&backup->str = *(u64 *)&v10->str;
      sBtlCheckAutoSkill_Enemy(wk);
      sBtlCheckBattlePara(wk);
      Unit->para->seikaku = v10->seikaku;
      v40.n64_u64[0] = *(u64 *)&v10->frid_area_r;
      v41 = Unit->actaiwk;
      Unit->size = v27->size;
      *(int32x2_t *)&v41->search_area_r = vrev64_s32(v40);
      Unit->scale.x = v27->scale;
      Unit->scale.y = v27->scale;
      Unit->scale.z = v27->scale;
      Unit->scale.w = v27->scale;
      Unit->disp_offy = v27->disp_offy;
      v40.n64_u32[0] = LODWORD(v27->hit_area_r);
      LODWORD(v41->hit_area_r) = v40.n64_u32[0];
      v41->priv_area_r = v40.n64_f32[0] + 1.0;
      v42 = wk->para->devilid;
      *(u64 *)&v41->frid_area_r = *(u64 *)&v10->frid_area_r;
      sBtlGetHelperPos(Unit, wk, v42);
      if ((~Unit->status & 0x8800) != 0)
      {
        pos = Unit->pos;
      }
      else
      {
        if (i == 6)
          v44 = -1;
        else
          v44 = 0;
        Unit->hithelpercsrno = v44;
        pos = Unit->pos;
        goto LABEL_36;
      }
      goto LABEL_37;
LABEL_36:
      vct_A = pos;
      goto LABEL_38;
LABEL_37:
      vct_A = pos;
LABEL_38:
      Unit->effpos = vct_A;
    }
  }
LABEL_40:
  wk->hithelperreqID = -1;
  return 1;
}

// 0x2014f40
void sBtlResetHelperHit(SBTLUNIT_WORK *wk) {
  s64 v3;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  u32 status;

  v3 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v3 >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[v3]->pUnit;
    if (pUnit)
    {
      status = pUnit->status;
      if ((status & 0x800) != 0 && wk->ListID == pUnit->hithelperID)
      {
        status = pUnit->status;
        pUnit->status = status | 0x4004000;
      }
    }
    ++v3;
  }
}

// 0x2015080
void sBtlSetHelperHit(SBTLUNIT_WORK *wk) {
  s64 v3;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  u32 status;

  v3 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v3 >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[v3]->pUnit;
    if (pUnit)
    {
      status = pUnit->status;
      if ((status & 0x800) != 0 && wk->ListID == pUnit->hithelperID)
      {
        status = pUnit->status;
        pUnit->status = status & 0xFBFFBFFF;
      }
    }
    ++v3;
  }
}

// 0x2014b50
bool sBtlGetHelperPos(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, s32 devilid) {
  void *v7;
  int32x2_t v8;
  sdfVector4_t *p_pos;
  s32 *v12;
  f32 z;
  float32x2_t v14;
  sdfVector4_t *p_rot;
  sdfVector4_t *v16;
  s32 v17;
  struct sdfVector4_t pos;
  struct sdfVector4_t v20;

  v7 = NewSpecific(s32, 0x10u);
  InitializeArray_55364416(v7, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__968B12E67313C000A867BAD4093827F888208635360B1060B9407FC436C96CF1, 0);
  if (devilid != 260)
  {
    if (devilid != 258)
      return 1;
    BS_LASTB2_pos_type = 0;
    pos = wklock->pos;
    vct_A = pos;
    p_pos = &wk->pos;
    v12 = (s32 *)v7 + wk->hithelperno;
    *p_pos = vct_A;
    z = wk->pos.z;
    v8.n64_u32[0] = -1024458752;
    v14.n64_u32[1] = vdup_lane_s32(v8, 0).n64_u32[1];
    v14.n64_f32[0] = (f32)v12[8];
    LODWORD(v12) = (u8)byte_5755EF5;
    *(float32x2_t *)&wk->pos.x = vadd_f32(*(float32x2_t *)&wk->pos.x, v14);
    wk->pos.z = z + 908.0;
    if ((u32)v12)
    {
      goto LABEL_14;
    }
    else
    {
      goto LABEL_14;
    }
LABEL_14:
    p_rot = &wk->rot;
    vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
    goto LABEL_25;
  }
  v20 = wklock->pos;
  vct_A = v20;
  v16 = &wk->pos;
  v17 = (u8)byte_5755EF5;
  *v16 = vct_A;
  *(float32x2_t *)&wk->pos.y = vadd_f32(*(float32x2_t *)&wk->pos.y, (float32x2_t)0xC47A0000C4228000LL);
  if (v17)
  {
    goto LABEL_23;
  }
  else
  {
    goto LABEL_23;
  }
LABEL_23:
  p_rot = &wk->rot;
  vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
LABEL_25:
  *p_rot = vct_A;
  return 1;
}

// 0x2004ef0
bool sBtlDeleteHitHelper(SBTLUNIT_WORK *wk) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->status & 0x800) != 0 && wk->ListID == pUnit->hithelperID)
      pUnit->mode = 9;
  }
  return 1;
}

// 0x20151c0
bool sBtlSetItem(SBTLUNIT_WORK *wk) {
  s32 devilid;
  DEVILDATA_WORK *DevilData;
  SB_ENCOUNTPAC *EncountPac;
  u32 flag;
  s32 v10;
  s32 v11;
  SBTLITEM_WORK *v15;
  SBTLITEM_WORK *v17;
  SBTLITEM_WORK *v19;
  SBTLITEM_WORK *v21;
  sdfVector4_t v22;
  sdfVector4_t v23;
  sdfVector4_t v24;
  sdfVector4_t v25;

  devilid = wk->para->devilid;
  DevilData = sBtlGetDevilData(devilid, -1);
  EncountPac = sBtlGetEncountPac(-1);
  flag = EncountPac[wk->encountno]->flag;
  v10 = HIWORD(flag) & 1;
  if ((flag & 0x20000) != 0)
    v10 = 2;
  if ((flag & 0x40000) != 0)
    v10 = 3;
  if ((flag & 0x80000) != 0)
    v10 = 4;
  if ((flag & 0x100000) != 0)
    v11 = 5;
  else
    v11 = v10;
  if ((u32)(v11 - 1) < 3)
  {
    sBtlDlcBtl_SetItemu((s32)sBtlUnit, DevilData);
    return 1;
  }
  if ((u32)(v11 - 4) >= 2)
  {
    if ((wk->hstatus & 4) != 0)
      return 1;
    v15 = DevilData->item[0];
    sBtlItem_CheckSetItem(v15, v22);
    v17 = DevilData->item[1];
    sBtlItem_CheckSetItem(v17, v23);
    v19 = DevilData->item[2];
    sBtlItem_CheckSetItem(v19, v24);
    v21 = DevilData->item[3];
    sBtlItem_CheckSetItem(v21, v25);
    return 1;
  }
  else
  {
    sBtlDlcZakuroBtl_SetItem();
    return 1;
  }
}

// 0x20157b0
bool sBtlItem_CheckSetItem(SBTLITEM_WORK *item, const sdfVector4_t *pos) {
  s32 itemid;
  s8 *p_per;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 playerID;
  SBATTLE_WORK *v12;
  SBTLUNIT_WORK *pUnit;
  SBATTLE_WORK *v14;
  s32 AutoSkillPara;
  s32 v16;
  SBTLUNIT_LISTWORK *v17;
  s64 v18;
  SBATTLE_WORK *v20;
  SBTLUNIT_WORK *v21;
  SBTLACTION_WORK *actwk;
  SBTLACTAI_WORK *actaiwk;
  u32 status;
  SBATTLE_WORK *v26;
  s32 v27;
  SBTLUNIT_LISTWORK *v28;
  s64 v29;
  SBATTLE_WORK *v31;
  SBTLUNIT_WORK *v32;
  SBTLACTION_WORK *v33;
  SBTLACTAI_WORK *v34;
  u32 v35;
  sdatUnitWork_t *v36;
  sdatParaWork_t *now;
  char v38;
  f32 v39;
  s16 v40;
  f32 v41;
  u32 status3;
  s16 v45;
  s32 v47;
  SBTLDROP_WORK *drop;
  char *v49;
  char **p_log;
  char *log;
  char *v52;
  s32 v53;
  char *v54;
  char *v55;
  char *v56;
  char *v57;
  char *v58;
  char *v59;
  char *v60;
  char *v61;
  char *v62;
  char *v63;
  char *v64;
  sdatUnitWork_t *para;
  s32 AutoSkill_ID;
  sdatUnitWork_t *v67;
  s32 v68;
  char v69;
  s16 v70;
  s16 v71;

  itemid = item->itemid;
  v71 = 0;
  v70 = 0;
  v69 = 0;
  if (itemid < 1)
    return 0;
  p_per = &item->per;
  if (!item->per)
    return 0;
  UnitMng = wk->UnitMng;
  playerID = (u32)wk->playerID;
  if ((playerID & 0x80000000) != 0)
    goto LABEL_25;
  v12 = wk;
  if (!v12)
    goto LABEL_25;
  if (!v12->UnitMng)
    goto LABEL_25;
  if (UnitMng->number > (s32)playerID)
  {
    pUnit = UnitMng->pUnitL[playerID]->pUnit;
    v14 = wk;
    if (v14->member_num >= 1)
      goto LABEL_26;
LABEL_24:
    AutoSkillPara = 106;
    goto LABEL_79;
  }
LABEL_25:
  pUnit = 0;
  v14 = wk;
  if (v14->member_num < 1)
    goto LABEL_24;
LABEL_26:
  v16 = (u16)v14->summonindex[0];
  if (v16 == 0xFFFF)
    goto LABEL_52;
  v14 = wk;
  LOWORD(v16) = v14->summonindex[0];
  v17 = v14->UnitMng;
  v18 = (u32)v14->summonID[(s16)v16];
  if ((v18 & 0x80000000) != 0)
    goto LABEL_52;
  v20 = wk;
  if (v20)
  {
    v20 = wk;
    if (v20->UnitMng)
    {
      if (v17->number > (s32)v18)
      {
        v21 = v17->pUnitL[v18]->pUnit;
        if (v21)
        {
          if (v21->para)
          {
            actwk = v21->actwk;
            if (actwk)
            {
              actaiwk = v21->actaiwk;
              if (actaiwk)
              {
                status = actwk->status;
                if (status != 10)
                {
                  AutoSkillPara = 106;
                  if ((v21->status & 0x5000) == 0 && status != 11 && status != 14 && status != 30 && actaiwk->mode != 9 && status != 40 && v21->mode >= 5)
                  {
                    para = v21->para;
                    AutoSkill_ID = sBtlGetAutoSkill_ID(para, 0);
                    AutoSkillPara = sBtlGetAutoSkillPara(AutoSkill_ID, &v21->para->autost_cnt, &v21->para->autost_cnt2);
                    if (AutoSkillPara == 8)
                      goto LABEL_79;
                  }
                  goto LABEL_53;
                }
              }
            }
          }
        }
      }
    }
  }
LABEL_52:
  AutoSkillPara = 106;
LABEL_53:
  v26 = wk;
  v27 = (u16)v26->summonindex[1];
  if (v27 != 0xFFFF)
  {
    v26 = wk;
    LOWORD(v27) = v26->summonindex[1];
    v28 = v26->UnitMng;
    v29 = (u32)v26->summonID[(s16)v27];
    if ((v29 & 0x80000000) != 0)
      goto LABEL_79;
    v31 = wk;
    if (v31)
    {
      v31 = wk;
      if (v31->UnitMng)
      {
        if (v28->number > (s32)v29)
        {
          v32 = v28->pUnitL[v29]->pUnit;
          if (v32)
          {
            if (v32->para)
            {
              v33 = v32->actwk;
              if (v33)
              {
                v34 = v32->actaiwk;
                if (v34)
                {
                  v35 = v33->status;
                  if (v35 != 10 && (v32->status & 0x5000) == 0 && v35 != 11 && v35 != 14 && v35 != 30 && v34->mode != 9 && v35 != 40 && v32->mode >= 5)
                  {
                    v67 = v32->para;
                    v68 = sBtlGetAutoSkill_ID(v67, 0);
                    AutoSkillPara = sBtlGetAutoSkillPara(v68, &v32->para->autost_cnt, &v32->para->autost_cnt2);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
LABEL_79:
  v36 = pUnit->para;
  now = v36->now;
  v38 = BYTE1(v36->itemstatus);
  v39 = (f32)((f32)((f32)((f32)now->luck * 1.5) + 100.0) * (f32)*p_per) / 100.0;
  if (v39 == INFINITY)
    v40 = 0;
  else
    v40 = (s32)v39;
  v70 = v40;
  if ((v38 & 2) != 0)
  {
    v40 += 10;
    v70 = v40;
    if (AutoSkillPara == 8)
    {
LABEL_84:
      v41 = (f32)v40 * 1.5;
      if (v41 == INFINITY)
        v40 = 0;
      else
        v40 = (s32)v41;
      v70 = v40;
      goto LABEL_91;
    }
  }
  else if (AutoSkillPara == 8)
  {
    goto LABEL_84;
  }
LABEL_91:
  v69 = 0;
  status3 = wk->status3;
  v45 = GetPercentage() + 1;
  if (v45 <= v40)
  {
    v47 = 0;
    v71 = v45;
    v69 = 1;
    if (v40 > 0)
      goto LABEL_98;
    goto LABEL_97;
  }
  if ((status3 & 0x20) == 0 || (v45 = GetPercentage() + 1, v40 < v45))
  {
    v71 = v45;
    goto LABEL_100;
  }
  v47 = 1;
  v71 = v45;
  v69 = 1;
  if (v40 <= 0)
  {
LABEL_97:
    v40 = 1;
    v70 = 1;
  }
LABEL_98:
  sBtlSetDropItem(item->itemid, item->para, v40, v47);
LABEL_100:
  drop = wk->drop;
  v49 = NewSpecific(string, 0xBu);
  log = drop->log;
  p_log = &drop->log;
  v52 = v49;
  v49[0] = log;
  v53 = item->itemid;
  v54 = sdatItemName(v53);
  v52[1] = v54;
  v55 = " Get:";
  v52[2] = " Get:";
  v56 = ToString((bool)&v69, 0);
  v52[3] = v56;
  v57 = " rootPar:";
  v52[4] = " rootPar:";
  v58 = ToString((s8)p_per, 0);
  v52[5] = v58;
  v59 = " luckPar:";
  v52[6] = " luckPar:";
  v60 = ToString((s16)&v70, 0);
  v52[7] = v60;
  v61 = " Rnd: ";
  v52[8] = " Rnd: ";
  v62 = ToString((s16)&v71, 0);
  v52[9] = v62;
  v63 = "\n";
  v52[10] = "\n";
  v64 = Concat_54832608(v52, 0);
  *p_log = v64;
  return 1;
}

// 0x2015410
void sBtlDlcBtl_SetItemu(s32 _dlcNum, DEVILDATA_WORK *_data) {
  SBTLITEM_WORK *v4;
  SBTLITEM_WORK *v7;
  SBTLITEM_WORK *v10;
  SBTLITEM_WORK *v13;
  SBTLITEM_WORK *v15;
  sdfVector4_t v19;
  sdfVector4_t v20;
  sdfVector4_t v21;
  sdfVector4_t v22;

  if (data)
  {
    v4 = data->item[0];
    sBtlItem_CheckSetItem(v4, v19);
    v7 = data->item[1];
    sBtlItem_CheckSetItem(v7, v20);
    v10 = data->item[2];
    sBtlItem_CheckSetItem(v10, v21);
    v13 = data->item[3];
    v15 = v13;
    sBtlItem_CheckSetItem(v15, v22);
    return;
  }
}

// 0x20155f0
bool sBtlDlcZakuroBtl_SetItem(void) {
  s32 nowKiretsuIdx;
  s32 v5;

  if (wk->dlcItemGet)
    return 1;
  nowKiretsuIdx = fldGb->nowKiretsuIdx;
  if (nowKiretsuIdx == 50)
  {
    v5 = 736;
    goto LABEL_23;
  }
  if (nowKiretsuIdx == 51)
  {
    v5 = 738;
    goto LABEL_23;
  }
  if (nowKiretsuIdx == 52)
  {
    v5 = 737;
    goto LABEL_23;
  }
  nowKiretsuIdx = fldGb->nowKiretsuIdx;
  if (nowKiretsuIdx != 53)
    return 0;
  v5 = 739;
LABEL_23:
  sBtlSetDropItem(v5, 1, 100, 1);
  wk->dlcItemGet = 1;
  return 1;
}

// 0x20160a0
s32 sBtlCheckSummonUnit_Exist2(s32 idx) {
  s8 v2;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v5;
  u32 status;
  s32 result;

  v2 = idx;
  if (wk->member_num < 1)
    return 2;
  Nakama = sBtlGetNakama(v2);
  if (!Nakama)
    return 2;
  v5 = Nakama;
  status = v5->actwk->status;
  if (status > 0xE || (result = 1, ((1 << status) & 0x4C00) == 0))
  {
    result = 1;
    if (v5->actaiwk->mode != 9 && status != 40 && v5->mode > 4)
      return 0;
  }
  return result;
}

// 0x20161f0
s32 sBtlCheckSummonUnit_Dead_or_ALive(s32 idx) {
  s8 v2;
  SBTLUNIT_WORK *Nakama;
  s32 result;
  u32 status;

  v2 = idx;
  if (wk->member_num < 1)
    return 2;
  Nakama = sBtlGetNakama(v2);
  result = 2;
  if (Nakama)
  {
    status = Nakama->actwk->status;
    if (status == 40 || status == 10)
      return 0;
    else
      return 2;
  }
  return result;
}

// 0x20162d0
s32 sBtlCheckSummonUnit_Exist(s32 idx) {
  s8 v2;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v5;
  SBTLACTION_WORK *actwk;
  s32 result;
  SBTLACTAI_WORK *actaiwk;
  u32 status;

  v2 = idx;
  if (wk->member_num < 1)
    return 2;
  Nakama = sBtlGetNakama(v2);
  if (!Nakama)
    return 2;
  v5 = Nakama;
  actwk = Nakama->actwk;
  if (!actwk)
    return 1;
  actaiwk = v5->actaiwk;
  if (!actaiwk)
    return 1;
  status = actwk->status;
  if (status == 10)
    return 1;
  result = 1;
  if ((v5->status & 0x5000) == 0 && status != 11 && status != 14 && status != 30 && actaiwk->mode != 9 && v5->mode > 4 && status != 40)
  {
    return 0;
  }
  return result;
}

// 0x2016470
s32 sBtlCheckSummonUnit(void) {
  s32 v2;
  s32 v5;
  _BOOL4 v6;
  SBATTLE_WORK *v7;
  s32 v8;
  SBATTLE_WORK *v9;
  s32 v10;
  _BOOL4 v11;
  SBATTLE_WORK *v12;
  s32 v13;
  _BOOL4 v14;
  int8x16_t *summonflg;
  int8x16_t v16;
  int8x16_t v17;
  int8x8_t v18;
  int8x8_t v19;
  bool v20;
  s32 v21;
  s32 v22;
  s32 i;
  s32 stock_num;
  s32 devilid;

  if (wk->stock_num < 1)
  {
    v2 = 1;
    goto LABEL_12;
  }
  if (Exists("new_devil"))
  {
    v2 = 0;
    goto LABEL_12;
  }
  v22 = 0;
  for (i = 0; ; ++i)
  {
    stock_num = wk->stock_num;
    if (i >= stock_num)
      break;
    devilid = sBtlGetStockUnitData(i)->devilid;
    v22 += sBtlIsDLCDevil(devilid);
  }
  v2 = stock_num - v22 < 1;
LABEL_12:
  if (wk->member_num > 0)
  {
    v5 = (u16)wk->summonindex[0];
    if (v5 != 0xFFFF)
    {
      LOWORD(v5) = wk->summonindex[0];
      v6 = wk->summonflg[(s16)v5] == 1;
      goto LABEL_19;
    }
    v6 = 0;
LABEL_19:
    v7 = wk;
    v8 = (u16)v7->summonindex[1];
    if (v8 == 0xFFFF)
    {
      if (v6)
        v2 = 3;
    }
    else
    {
      v7 = wk;
      LOWORD(v8) = v7->summonindex[1];
      if (v7->summonflg[(s16)v8] == 1 || v6)
        v2 = 3;
    }
    v9 = wk;
    v10 = (u16)v9->summonindex[0];
    if (v10 == 0xFFFF)
    {
      v11 = 0;
      goto LABEL_31;
    }
    else
    {
      v9 = wk;
      LOWORD(v10) = v9->summonindex[0];
      v11 = v9->summonflg[(s16)v10] == 2;
      goto LABEL_31;
    }
LABEL_31:
    v12 = wk;
    v13 = (u16)v12->summonindex[1];
    if (v13 == 0xFFFF)
    {
      v14 = 0;
    }
    else
    {
      v12 = wk;
      LOWORD(v13) = v12->summonindex[1];
      v14 = v12->summonflg[(s16)v13] == 2;
    }
    v20 = !v14 || !v11;
    v21 = 2;
    goto LABEL_58;
  }
  summonflg = wk->summonflg;
  v16 = vbicq_s8((int8x16_t)xmmword_3D06630, vceqzq_s8(summonflg[3]));
  v17 = vbicq_s8((int8x16_t)xmmword_3D06630, vceqzq_s8(summonflg[2]));
  v18.n64_u64[0] = vextq_s8(v16, v16, 8u).n128_u64[0];
  v16.n128_u8[0] = vaddv_s8((int8x8_t)v16.n128_u64[0]);
  v19.n64_u64[0] = vextq_s8(v17, v17, 8u).n128_u64[0];
  v17.n128_u8[0] = vaddv_s8((int8x8_t)v17.n128_u64[0]);
  v18.n64_u8[0] = vaddv_s8(v18);
  v19.n64_u8[0] = vaddv_s8(v19);
  v20 = (u16)(v17.n128_u16[0] | ((v19.n64_u16[0] | v18.n64_u16[0]) << 8) | v16.n128_u16[0]) == 0;
  v21 = 3;
LABEL_58:
  if (!v20)
    return v21;
  return v2;
}

// 0x2016920
s32 sBtlGetStockPoint(void) {
  s32 stock_num;

  stock_num = wk->stock_num;
  if (stock_num > 31)
    return -1;
  return stock_num;
}

// 0x20169f0
bool sBtlEntryStockData_Huuma(void) {
  s64 v3;
  sdatPlayerUnitWork_t *player;
  s64 v8;
  s64 v9;
  s32 v10;
  s32 v12;
  sdatUnitWork_t *v13;
  s32 devilid;
  DEVILDATA_WORK *DevilData;

  v3 = 0;
  player = GBWK->player;
  do
  {
    v10 = wk->huuma_devilID[v3 + 11];
    if (v10 != -1)
    {
      v12 = sBtlEntryStockData(v10);
      wk->huuma_devilID[v3 + 11] = -1;
      if (v12 != -1)
      {
        v13 = player->stock_id[v3 + 11];
        devilid = v13->devilid;
        if (v13->devilid)
        {
          if ((v13->flag & 1) != 0)
          {
            DevilData = sBtlGetDevilData(devilid, -1);
            v8 = (s64)wk->stock_id + 4 * v3;
            v9 = (s64)wk->stock_buffer + 4 * v3;
            *(u32 *)(v8 + 76) = player->stock_id[v3 + 11]->devilid;
            *(u32 *)(v9 + 76) = DevilData->minorno;
          }
        }
      }
      goto LABEL_7;
    }
LABEL_7:
    --v3;
  }
  while (v3 != -12);
  return 1;
}

// 0x2016bf0
s32 sBtlEntryStockData(s32 devilid) {
  s32 v4;
  s32 *v5;
  DEVILDATA_WORK *DevilData;
  s32 stock_num;
  sdatUnitWork_t *v14;
  DEVILDATA_WORK *v16;
  s32 v17;
  s8 kuda_id;
  sdatParaWork_t *backup;
  s32 maxhp;
  s16 str;
  s32 maxmp;
  sdatParaWork_t *v25;
  s32 *huuma_status_up;
  s16 v29;
  s16 v30;
  s16 v31;
  s16 tec;
  s16 v33;
  s16 luck;
  sdatParaWork_t *now;
  s32 v37;
  SKLID *v38;
  SKLID *sousaSkill;
  SKLID *v40;
  s32 v41;
  SKLID *haveskill;
  s32 v43;
  s32 v44;
  s32 v45;
  s32 v46;
  SBTLAISYO_DATAWORK *Aisyotbl;
  SBATTLE_WORK *wk_local;
  gohKarteList_t *karte_list;
  s32 v55;
  s32 KarteTrophChkCnt;
  void *achievementTbl_k__BackingField;
  Project_DefineAchievementID_string__c *klass;
  s64 v60;
  Project_DefineAchievementID_string__c **p_offset;
  s64 v62;
  char *v63;
  sdatUnitWork_t *p_huuma_getUnit;
  s32 skill2[2];

  *(u64 *)skill2 = 0;
  if (devilid > 62)
  {
    if (devilid != 63)
    {
      if (devilid != 68)
        goto LABEL_26;
      v4 = 256;
LABEL_24:
      v5 = &GBWK->EventBit[73];
      goto LABEL_25;
    }
    v4 = 128;
    goto LABEL_24;
  }
  if (devilid == 7)
  {
    v4 = 0x40000000;
    v5 = &GBWK->EventBit[72];
    goto LABEL_25;
  }
  if (devilid != 25)
    goto LABEL_26;
  v4 = 0x4000000;
  v5 = &GBWK->EventBit[72];
LABEL_25:
  *v5 |= v4;
LABEL_26:
  DevilData = sBtlGetDevilData(devilid, -1);
  stock_num = wk->stock_num;
  if (stock_num > 31)
    return -1;
  if (stock_num == -1)
    return -1;
  v14 = GBWK->player->stock_id[stock_num];
  ClassClear(v14, 0);
  v14->devilid = devilid;
  v14->flag = 5;
  v16 = sBtlGetDevilData(devilid, -1);
  v14->seikaku = DevilData->seikaku;
  v17 = (u8)byte_5755FAE;
  v14->level = v16->level;
  if (v17)
  {
    goto LABEL_44;
  }
  else
  {
    goto LABEL_44;
  }
LABEL_44:
  kuda_id = sBtlGetDevilData(devilid, -1)->kuda_id;
  v14->chuusei = 0;
  v14->exp = 0;
  backup = v14->backup;
  v14->raceid = kuda_id;
  maxhp = DevilData->maxhp;
  str = DevilData->str;
  backup->hp = maxhp;
  backup->maxhp = maxhp;
  maxmp = DevilData->maxmp;
  backup->mp = maxmp;
  backup->maxmp = maxmp;
  v25 = backup;
  v14->vice = 0;
  huuma_status_up = wk->huuma_status_up;
  v29 = str + LOWORD(huuma_status_up[0]);
  v30 = DevilData->vit + LOWORD(huuma_status_up[2]);
  v31 = huuma_status_up[1];
  LOWORD(huuma_status_up) = huuma_status_up[3];
  backup->str = v29;
  tec = DevilData->tec;
  v25->vit = v30;
  v33 = tec + v31;
  luck = DevilData->luck;
  v25->tec = v33;
  v25->luck = luck + (u16)huuma_status_up;
  datCalcNowParam(v14, 0, 0);
  now = v14->now;
  v37 = now->maxmp;
  now->hp = now->maxhp;
  now->mp = v37;
  v38 = NewSpecific(SKLID, 0x11u);
  v14->haveskill = v38;
  skill2[1] = 255;
  skill2[0] = 255;
  mskGetNo(devilid, &skill2[1], skill2);
  sousaSkill = v14->sousaSkill;
  sousaSkill[0] = fldChangeFromMskGetNoToSKLID(skill2[1]);
  v40 = v14->sousaSkill;
  v41 = fldChangeFromMskGetNoToSKLID(skill2[0]);
  haveskill = DevilData->haveskill;
  v40[1] = v41;
  v14->haveskill[0] = haveskill[0];
  v43 = haveskill[1];
  if (v43)
  {
    v44 = 0;
    v14->aRsvSkl[0] = v43;
    v45 = haveskill[2];
    if (v45)
      goto LABEL_58;
  }
  else
  {
    v44 = 1;
    v45 = haveskill[2];
    if (v45)
    {
LABEL_58:
      v14->aRsvSkl[v44 ^ 1] = v45;
      v46 = haveskill[3];
      if (!v46)
        goto LABEL_60;
      goto LABEL_59;
    }
  }
  ++v44;
  v46 = haveskill[3];
  if (v46)
LABEL_59:
    v14->aRsvSkl[2 - v44] = v46;
LABEL_60:
  v14->battleskill[0] = v14->haveskill[0];
  sBtlCheckAutoSkill(v14, 0);
  sBtlSetAutoSkill_GB(v14);
  sBtlCheckStockPara(v14);
  Aisyotbl = sBtlGetAisyotbl(DevilData->aishou);
  ClassCopy(v14->aisyo, Aisyotbl, 0);
  v14->talkskill = DevilData->talkskill;
  v14->iOmoideSkillCnt = 1;
  wk_local = wk;
  wk_local->stock_id[stock_num] = v14->devilid;
  wk_local->stock_buffer[stock_num] = devilid;
  ++wk_local->stock_num;
  karte_list = GBWK->karte_list;
  v55 = GBWK->nakama_uniq_cnt + 1;
  GBWK->nakama_uniq_cnt = v55;
  v14->uniq_code = v55;
  gohKarteRegistDevil(v14, karte_list, 1, 1, 0, 0);
  AddGetDevilList(GBWK->sortSave, v14->devilid, v14->uniq_code, 0, 0);
  KarteTrophChkCnt = GetKarteTrophChkCnt(GBWK->karte_list, 0);
  if (KarteTrophChkCnt >= GetNakamaCount())
  {
    achievementTbl_k__BackingField = _achievementTbl_k__BackingField;
    klass = achievementTbl_k__BackingField->klass;
    v60 = *(u16 *)&achievementTbl_k__BackingField->klass->_2.rank;
    if (*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
    {
      p_offset = &klass->_1.interfaceOffsets->offset;
      while (*(p_offset - 1) != Project_DefineAchievementID_string_)
      {
        p_offset += 2;
        if (!--v60)
          goto LABEL_75;
      }
      v62 = (&klass[1]._1.byval_arg + *(u32 *)p_offset);
    }
    else
    {
LABEL_75:
      v62 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0x22u);
    }
    v63 = (*v62)(achievementTbl_k__BackingField, *(u64 *)(v62 + 8));
    Unlock_2(v63);
    goto LABEL_95;
  }
LABEL_95:
  p_huuma_getUnit = &wk->huuma_getUnit;
  p_huuma_getUnit = v14;
  return stock_num;
}

// 0x20174d0
static void CheckHuumaParaUP(sdatUnitWork_t *unit) {
  datCalcNowParam(unit, 0, 0);
}

// 0x2017540
SBTLUNIT_WORK *sBtlSetSummon_E(MODELTYPE major, s32 minor, s32 groupid, s32 id) {
  SBTLUNIT_WORK *Unit;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  SBTLUNIT_LISTWK *pUnitL;
  s64 v13;
  s32 v14;
  s64 v15;
  SBTLUNIT_LISTWK *v16;
  SBTLACTION_WORK *actwk;
  SBTLACTAI_WORK *actaiwk;

  Unit = sBtlCreateUnit(major, minor, 2);
  UnitMng = wk->UnitMng;
  number = (u32)UnitMng->number;
  if ((s32)number < 1)
  {
LABEL_11:
    v14 = 0;
  }
  else
  {
    pUnitL = UnitMng->pUnitL;
    v13 = 0;
    while (pUnitL[v13]->pUnit)
    {
      if (number == ++v13)
        goto LABEL_11;
    }
    v15 = v13;
    v16 = pUnitL[v13];
    v16->pUnit = Unit;
    v16 = ((char *)v16 + 24);
    LODWORD(v16[-1].pUnit) = v13;
    ++UnitMng->count;
    v14 = UnitMng->pUnitL[v15]->ID;
  }
  Unit->ListID = v14;
  actwk = Unit->actwk;
  Unit->GroupID = groupid;
  actwk->status = 0;
  actaiwk = Unit->actaiwk;
  actaiwk->mode = 9;
  actaiwk->stat = 1;
  sBtlResetAIPattern(Unit, 0);
  Unit->color = 8421504;
  ++wk->enemy_num;
  return Unit;
}

// 0x20176f0
SBTLUNIT_WORK *sBtlResetSummon(s32 index, s32 flg) {
  SBTLUNIT_LISTWORK *UnitMng;
  s64 v8;
  SBTLUNIT_WORK *pUnit;
  SBTLACTAI_WORK *actaiwk;
  s32 status;
  void *wkBarrier;
  SBATTLE_WORK *v15;
  SBATTLE_WORK *v16;
  SBTLUNIT_LISTWORK *v17;
  s64 playerID;
  SBATTLE_WORK *v20;
  SBTLUNIT_WORK *v21;
  f32 v22;
  f32 hit_area_r;
  f32 v24;
  f32 v25;
  sdfVector4_t *p_pos;
  struct sdfVector4_t rot;
  sdfVector4_t *p_rot;
  f32 v33;
  f32 v34;
  bool MovePos_MapHit;
  s32 v36;
  struct sdfVector4_t v40;
  struct sdfVector4_t v41;
  struct sdfVector4_t v42;
  struct sdfVector4_t v43;
  sdfVector4_t pos;

  *(u64 *)&pos.x = 0;
  *(u64 *)&pos.z = 0;
  UnitMng = wk->UnitMng;
  v8 = (u32)wk->summonID[index];
  pUnit = UnitMng->pUnitL[v8]->pUnit;
  *(u32 *)&pUnit->aiwk->stat = 262147;
  actaiwk = pUnit->actaiwk;
  status = actaiwk->status;
  actaiwk->stat = 1;
  actaiwk->status = status & 0xFFFFFFFE;
  pUnit->mode = 4;
  pUnit->color = 8421504;
  pUnit->actwk->status = 0;
  wkBarrier = pUnit->wkBarrier;
  sBtlResetBattlePara(pUnit, index);
  pUnit->wkBarrier = wkBarrier;
  sBtlCheckBattlePara(pUnit);
  wk->summon[index] = 1;
  v15 = wk;
  v15->summonID[index] = pUnit->ListID;
  v15->summonflg[index] = 1;
  v16 = wk;
  v17 = v16->UnitMng;
  playerID = (u32)v16->playerID;
  if ((playerID & 0x80000000) != 0)
    goto LABEL_28;
  v20 = wk;
  if (!v20)
    goto LABEL_28;
  if (!v20->UnitMng)
    goto LABEL_28;
  if (v17->number > (s32)playerID)
  {
    v21 = v17->pUnitL[playerID]->pUnit;
    goto LABEL_29;
  }
LABEL_28:
  v21 = 0;
LABEL_29:
  v22 = 60.0;
  if (flg != 5)
    v22 = 0.0;
  hit_area_r = v21->actaiwk->hit_area_r;
  if (flg == 4)
    v24 = -60.0;
  else
    v24 = v22;
  v25 = pUnit->actaiwk->hit_area_r;
  if (!sBtlGetMovePos_MapHit(v21, pUnit, &pos, hit_area_r + v25, v24, 1))
  {
    v33 = v21->actaiwk->hit_area_r;
    v34 = pUnit->actaiwk->hit_area_r;
    MovePos_MapHit = sBtlGetMovePos_MapHit(v21, pUnit, &pos, v34 + (f32)(v33 + v34), v24, 1);
    if (MovePos_MapHit)
    {
      v40 = pos;
      goto LABEL_51;
    }
    v43 = pUnit->pos;
    vct_A = v43;
    pos = vct_A;
    v40 = pos;
    goto LABEL_51;
  }
  v40 = pos;
LABEL_51:
  vct_A = v40;
  p_pos = &pUnit->pos;
  v36 = (u8)byte_5755EF5;
  *p_pos = vct_A;
  rot = v21->rot;
  if (!v36)
  {
    v41 = rot;
    rot = v41;
    goto LABEL_57;
  }
  v42 = rot;
  vct_A = v42;
  goto LABEL_58;
LABEL_57:
  vct_A = rot;
  p_rot = &pUnit->rot;
  goto LABEL_59;
LABEL_58:
  p_rot = &pUnit->rot;
LABEL_59:
  *p_rot = vct_A;
  pUnit->mv_rotbk = v21->mv_rotbk;
  sBtlSetMotion(pUnit, 9, 0, 0, 0);
  return pUnit;
}

// 0x20065a0
SBTLUNIT_WORK *sBtlSetSummon(MODELTYPE major, s32 minor, s32 index, s32 flg) {
  s64 v10;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 v13;
  s32 v16;
  SBTLUNIT_WORK *pUnit;
  SBTLUNIT_LISTWORK *v19;
  s64 number;
  SBATTLE_WORK *v21;
  SBATTLE_WORK *v22;
  SBTLUNIT_LISTWORK *v23;
  u32 PlayerID;
  SBTLUNIT_LISTWK *pUnitL;
  s64 v27;
  s32 ID;
  SBTLUNIT_WORK *v29;
  f32 w;
  f32 v32;
  struct sdfVector4_t v37;
  sdfVector4_t *p_pos;
  struct sdfVector4_t v40;
  sdfVector4_t *p_rot;
  sdfVector4_t *p_rot_p;
  SBTLUNIT_WORK *v46;
  s32 v47;
  s32 v48;
  s64 v49;
  SBTLUNIT_LISTWK *v50;
  SBTLAI_WORK *aiwk;
  SBTLACTAI_WORK *actaiwk;
  s32 v54;
  SBATTLE_WORK *v56;
  SBTLUNIT_LISTWORK *v57;
  s32 v58;
  SBATTLE_WORK *v61;
  SBTLUNIT_WORK *v62;
  s32 v63;
  VISUALDATA_WORK *VisualData;
  f32 hit_area_r;
  f32 v66;
  f32 v67;
  f32 v68;
  f32 v69;
  f32 v70;
  f32 x;
  f32 y;
  f32 z;
  f32 v74;
  long f64 v75;
  sdfVector4_t *v77;
  s32 v78;
  struct sdfVector4_t v79;
  sdfVector4_t *v80;
  sdatUnitWork_t *para;
  SKLID *battleskill;
  s32 v83;
  u32 v84;
  s32 v85;
  s64 v86;
  s32 v87;
  s64 v88;
  s32 v89;
  s64 v90;
  s32 v91;
  s64 v92;
  s32 v93;
  s64 v94;
  s32 v95;
  s64 v96;
  s32 v97;
  SKLID *haveskill;
  char *v99;
  SKLID *aOmoideSkill;
  u32 *v101;
  SBTLEXP_LISTWORK *expList;
  s32 vice;
  SBATTLE_WORK *v105;
  int32x2_t *p_member_num;
  s32 v109;
  sdfVector4_t *v112;
  sdfVector4_t v113;
  sdfVector4_t *v115;
  f32 v122;
  f32 v123;
  f32 v124;
  f32 v125;
  s32 encountno;
  u32 devilid;
  f32 v130;
  f32 v131;
  struct sdfVector4_t rot;
  struct sdfVector4_t v138;
  struct sdfVector4_t v139;
  sdfVector4_t pos;
  sdfMatrix4_t v146;
  sdfMatrix4_t v147;
  sdfVector4_t v148;
  sdfVector4_t v150;

  *(u64 *)&pos.x = 0;
  *(u64 *)&pos.z = 0;
  v10 = index;
  if (wk->summonflg[index] == 3)
  {
    UnitMng = wk->UnitMng;
    v13 = (u32)wk->summonID[index];
    v21 = wk;
    pUnit = UnitMng->pUnitL[v13]->pUnit;
    *(u32 *)&pUnit->aiwk->stat = 262147;
    pUnit->actaiwk->stat = 1;
    pUnit->color = 8421504;
    pUnit->mode = 4;
    pUnit->actwk->status = 0;
    v21->summon[index] = 1;
    v22 = wk;
    v22->summonID[index] = pUnit->ListID;
    v22->summonflg[index] = 1;
    v23 = wk->UnitMng;
    PlayerID = sBtlGetPlayerID();
    v29 = v23->pUnitL[PlayerID]->pUnit;
    rot = v29->rot;
    vct_A = rot;
    w = pos.w;
    v32 = -(f32)(v29->actaiwk->hit_area_r + pUnit->actaiwk->hit_area_r);
    pos.z = v32;
    *(u64 *)&vct_B.x = *(u64 *)&pos.x;
    vct_B.z = v32;
    vct_B.w = w;
    ToMatrix();
    get_transpose(&v147, &mtx_A, 0);
    *(_OWORD *)&v146.m00 = *(_OWORD *)&v147.m00;
    *(_OWORD *)&v146.m01 = *(_OWORD *)&v147.m01;
    *(_OWORD *)&v146.m02 = *(_OWORD *)&v147.m02;
    *(_OWORD *)&v146.m03 = *(_OWORD *)&v147.m03;
    v148 = op_Multiply_60923920(&v146, vct_B, 0);
    vct_B = v148;
    v37 = v29->pos;
    vct_A = v37;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    p_pos = &pUnit->pos;
    *p_pos = vct_A;
    v40 = sbtlunit_debugrot[0];
    vct_A = v40;
    p_rot = &pUnit->rot;
    *p_rot = vct_A;
    p_rot_p = &pUnit->rot_p;
    v46 = pUnit;
    v47 = 0;
    v48 = 4;
    *p_rot_p = vct_A;
    goto LABEL_168;
  }
  if ((u32)flg <= 3 && flg != 1)
  {
    v16 = 2;
    goto LABEL_16;
  }
  v16 = 0;
LABEL_16:
  pUnit = sBtlCreateUnit(major, minor, v16);
  v19 = wk->UnitMng;
  number = (u32)v19->number;
  if ((s32)number < 1)
    goto LABEL_33;
  goto LABEL_9006;
  if ((s32)number < 1)
  {
LABEL_33:
    ID = 0;
    goto LABEL_85;
  }
LABEL_9006:
  pUnitL = v19->pUnitL;
  v27 = 0;
  while (pUnitL[v27]->pUnit)
  {
    if (number == ++v27)
      goto LABEL_33;
  }
  v49 = v27;
  v50 = pUnitL[v27];
  v50->pUnit = pUnit;
  v50 = ((char *)v50 + 24);
  LODWORD(v50[-1].pUnit) = v27;
  ++v19->count;
  ID = v19->pUnitL[v49]->ID;
LABEL_85:
  pUnit->ListID = ID;
  pUnit->status |= 6u;
  aiwk = pUnit->aiwk;
  *(u32 *)&aiwk->stat = 262147;
  aiwk->meirei_nobk = 7;
  actaiwk = pUnit->actaiwk;
  actaiwk->stat = 1;
  aiwk->skillAct = 0;
  pUnit->color = 8421504;
  pUnit->side = 1;
  v54 = wk->playerID;
  actaiwk->LeaderID = v54;
  sBtlSetLockID(pUnit, v54);
  sBtlGetData_Stock_Unit(pUnit, index);
  if ((flg & 0xFFFFFFFE) == 2)
  {
    v56 = wk;
    if (v56->battlemode == 3)
      goto LABEL_139;
    if ((wk->scene->status & 0x20) != 0)
      goto LABEL_181;
  }
  v57 = wk->UnitMng;
  v58 = sBtlGetPlayerID();
  if (v58 < 0)
    goto LABEL_114;
  v61 = wk;
  if (!v61)
    goto LABEL_114;
  v61 = wk;
  if (v61->UnitMng && v57->number > v58)
  {
    v62 = v57->pUnitL[v58]->pUnit;
    goto LABEL_115;
  }
LABEL_114:
  v62 = 0;
LABEL_115:
  v63 = wk->stock_buffer[v10];
  VisualData = sBtlGetVisualData(2u, v63);
  hit_area_r = VisualData->hit_area_r;
  v66 = v62->actaiwk->hit_area_r;
  if (!sBtlGetMovePos_MapHit(v62, pUnit, &pos, v66 + hit_area_r, 0.0, 1))
  {
    v67 = VisualData->hit_area_r;
    v68 = v62->actaiwk->hit_area_r;
    if (!sBtlGetMovePos_MapHit(v62, pUnit, &pos, v67 + (f32)(v68 + v67), 0.0, 1))
    {
      v69 = VisualData->hit_area_r;
      v70 = v62->actaiwk->hit_area_r;
      if (!sBtlGetMovePos_MapHit(v62, pUnit, &pos, v70 + (f32)(v69 * 3.0), 0.0, 1))
      {
        x = v62->pos.x;
        y = v62->pos.y;
        z = v62->pos.z;
        v74 = v62->pos.w;
        *(__n128 *)&v75 = sub_1B332C0(0, x, y, z, v74);
        sub_1B335A0(&pos, 0, v75);
      }
    }
  }
  v138 = pos;
  vct_A = v138;
  v77 = &pUnit->pos;
  v78 = (u8)byte_5755EF5;
  *v77 = vct_A;
  v79 = v62->rot;
  if (v78)
    goto LABEL_135;
  goto LABEL_174;
  if (v109)
  {
LABEL_135:
    goto LABEL_136;
  }
LABEL_174:
  v139 = v79;
  v79 = v139;
LABEL_136:
  vct_A = v79;
  v80 = &pUnit->rot;
  *v80 = vct_A;
  pUnit->mv_rotbk = v62->mv_rotbk;
  goto LABEL_139;
LABEL_181:
  vct_A = nakama_pos;
  v112 = &pUnit->pos;
  *v112 = vct_A;
  v113 = sbtlunit_debugrot[0];
  vct_A = v113;
  v115 = &pUnit->rot;
  *v115 = vct_A;
  pUnit->rot_p = vct_A;
  pUnit->mv_rotbk = nakama_mv_rotbk;
  if (flg == 3)
  {
    vct_A = nakama_rot;
    *v115 = vct_A;
    LODWORD(sBtlScene) = pUnit->status | 0x10;
    pUnit->mv_rotbk = nakama_mv_rotbk;
    pUnit->status = (u32)sBtlScene;
    goto LABEL_226;
  }
  v122 = pUnit->rot.x;
  v123 = pUnit->rot.y;
  v125 = pUnit->rot.z;
  v124 = pUnit->rot.w;
  v150.x = v122;
  v150.y = v123;
  v150.z = v125;
  v150.w = v124;
  sBtlGetRotateDeg(v150, 180.0);
  *v115 = vct_A;
  sBtlAddUnitDeg(pUnit, 180.0);
LABEL_226:
  encountno = wk->encountno;
  if (encountno != 43)
  {
    encountno = wk->encountno;
    if (encountno != 54)
    {
      v130 = pUnit->pos.z;
      v131 = -50.0;
      goto LABEL_236;
    }
  }
  devilid = (u16)pUnit->para->devilid;
  if (devilid <= 0x16 && ((1 << devilid) & 0x501000) != 0)
  {
    v130 = pUnit->pos.z;
    v131 = -200.0;
LABEL_236:
    pUnit->pos.z = v130 + v131;
  }
LABEL_139:
  para = pUnit->para;
  battleskill = para->battleskill;
  v83 = battleskill[0];
  if (!v83)
  {
    v84 = 2;
    v85 = battleskill[1];
    if (!v85)
      goto LABEL_142;
    goto LABEL_141;
  }
  sBtlGetSkilltbl(v83);
  para = pUnit->para;
  v84 = 3;
  battleskill = para->battleskill;
  pUnit->haveskill[2] = battleskill[0];
  v85 = battleskill[1];
  if (v85)
  {
LABEL_141:
    sBtlGetSkilltbl(v85);
    para = pUnit->para;
    v86 = (s64)pUnit->haveskill + 4 * v84;
    battleskill = para->battleskill;
    ++v84;
    *(u32 *)(v86 + 32) = battleskill[1];
  }
LABEL_142:
  v87 = battleskill[2];
  if (v87)
  {
    sBtlGetSkilltbl(v87);
    para = pUnit->para;
    v88 = (s64)pUnit->haveskill + 4 * v84;
    battleskill = para->battleskill;
    ++v84;
    *(u32 *)(v88 + 32) = battleskill[2];
  }
  v89 = battleskill[3];
  if (v89)
  {
    sBtlGetSkilltbl(v89);
    para = pUnit->para;
    v90 = (s64)pUnit->haveskill + 4 * v84;
    battleskill = para->battleskill;
    ++v84;
    *(u32 *)(v90 + 32) = battleskill[3];
  }
  v91 = battleskill[4];
  if (v91)
  {
    sBtlGetSkilltbl(v91);
    para = pUnit->para;
    v92 = (s64)pUnit->haveskill + 4 * v84;
    battleskill = para->battleskill;
    ++v84;
    *(u32 *)(v92 + 32) = battleskill[4];
  }
  v93 = battleskill[5];
  if (v93)
  {
    sBtlGetSkilltbl(v93);
    para = pUnit->para;
    v94 = (s64)pUnit->haveskill + 4 * v84;
    battleskill = para->battleskill;
    ++v84;
    *(u32 *)(v94 + 32) = battleskill[5];
  }
  v95 = battleskill[6];
  if (v95)
  {
    sBtlGetSkilltbl(v95);
    para = pUnit->para;
    v96 = (s64)pUnit->haveskill + 4 * v84;
    battleskill = para->battleskill;
    ++v84;
    *(u32 *)(v96 + 32) = battleskill[6];
  }
  v97 = battleskill[7];
  if (v97)
  {
    sBtlGetSkilltbl(v97);
    para = pUnit->para;
    haveskill = pUnit->haveskill;
    v99 = (char *)haveskill + 4 * v84++;
    *((u32 *)v99 + 8) = para->battleskill[7];
  }
  else
  {
    haveskill = pUnit->haveskill;
  }
  aOmoideSkill = para->aOmoideSkill;
  v101 = ((char *)haveskill + 4 * v84);
  v101[8] = aOmoideSkill[0];
  v101[9] = aOmoideSkill[1];
  v101[10] = aOmoideSkill[2];
  v101[11] = aOmoideSkill[3];
  v101[12] = aOmoideSkill[4];
  v101[13] = aOmoideSkill[5];
  v101[14] = aOmoideSkill[6];
  v101[15] = aOmoideSkill[7];
  sBtlCheckBattlePara(pUnit);
  expList = wk->expList;
  vice = pUnit->para->vice;
  sBtlSetVicePara(expList, vice);
  sBtlNakamaViceInit(pUnit);
  wk->summon[v10] = 1;
  v105 = wk;
  v105->summonID[v10] = pUnit->ListID;
  v105->summonflg[v10] = 1;
  p_member_num = &wk->member_num;
  p_member_num->n64_u64[0] = vadd_s32((int32x2_t)p_member_num->n64_u64[0], (int32x2_t)0x100000001LL).n64_u64[0];
  LimitRange(p_member_num, 0, 3);
  v47 = 9;
  v46 = pUnit;
  v48 = 0;
LABEL_168:
  sBtlSetMotion(v46, v47, v48, 0, 0);
  return pUnit;
}

// 0x2005520
bool SetReturn(s32 index, s32 flg) {
  SBTLUNIT_LISTWORK *UnitMng;
  s64 v8;
  SBATTLE_WORK *v10;
  SBTLUNIT_WORK *pUnit;
  SBTLDMG_HITLISTWORK *hitList;
  SBTLEFF_LISTWORK *effList;
  sdatUnitWork_t *para;
  u32 BadStatus;
  SBTLEXP_LISTWORK *expList;
  SBATTLE_WORK *v20;
  int32x2_t *p_member_num;
  s32 v23;
  SBTLEFF_LISTWORK *v25;
  s32 v26;
  s32 v27;
  SBTLEFF_LISTWORK *v29;
  s32 v30;
  s32 v31;
  SBTLEFF_LISTWORK *v33;
  s32 v34;
  s32 v35;
  SBTLEFF_LISTWORK *v37;
  s32 v38;
  f32 v42;
  f32 v43;
  SBTLEFF_LISTWORK *v44;
  f32 v45;
  f32 v46;
  s32 v47;
  f32 v48;
  SBTLEFF_LISTWORK *v49;
  SBTLUNIT_WORK *v50;
  f32 x;
  f32 y;
  SBTLEFF_LISTWORK *v54;
  f32 z;
  f32 w;
  SBTLEFF_LISTWORK *v58;
  s32 *summonindex_menu;
  s32 *v62;
  sdfVector4_t v64;
  sdfVector4_t v65;

  UnitMng = wk->UnitMng;
  v8 = (u32)wk->summonID[index];
  if ((v8 & 0x80000000) != 0)
    goto LABEL_102;
  v10 = wk;
  if (!v10)
    goto LABEL_102;
  v10 = wk;
  if (!v10->UnitMng || UnitMng->number <= (s32)v8 || (pUnit = UnitMng->pUnitL[v8]->pUnit) == 0)
  {
LABEL_102:
    goto LABEL_103;
  }
  sBtlResetBtlMagicStatus(pUnit);
  pUnit->status |= 0x10u;
  *(u32 *)&pUnit->aiwk->stat = 327683;
  pUnit->actaiwk->stat = 1;
  pUnit->nakama_skill_name = 0;
  sBtlDrawSkillNameOff(pUnit);
  hitList = wk->hitList;
  sBtlClearHitC(hitList, pUnit);
  effList = wk->effList;
  sBtlForceReset(effList, pUnit);
  sBtlForceReset_Tatari(wk->effList, pUnit);
  sBtlDeleteHaveSkill_EffectWork(pUnit);
  para = pUnit->para;
  BadStatus = sBtlGetBadStatus(para);
  expList = wk->expList;
  sBtlResetVicePara(expList);
  sBtlResetBattlePara(pUnit, index);
  sBtlResetBadStatus(pUnit, pUnit->para->badstatus);
  v20 = wk;
  v20->returnindex[0] = index;
  v20->status2 |= 0x100u;
  v20->summon[index] = 0;
  p_member_num = &wk->member_num;
  p_member_num->n64_u64[0] = vadd_s32((int32x2_t)p_member_num->n64_u64[0], (int32x2_t)-1).n64_u64[0];
  LimitRange(p_member_num, 0, 3);
  v23 = pUnit->haveskill[2];
  if (v23 >= 1 && (sBtlGetSkilltbl(v23)->area & 8) != 0)
  {
    v25 = wk->effList;
    v26 = pUnit->haveskill[2];
    sBtlDeleteEffectData_SkillIDType(v25, v26, 1u);
  }
  v27 = pUnit->haveskill[3];
  if (v27 >= 1 && (sBtlGetSkilltbl(v27)->area & 8) != 0)
  {
    v29 = wk->effList;
    v30 = pUnit->haveskill[3];
    sBtlDeleteEffectData_SkillIDType(v29, v30, 1u);
  }
  v31 = pUnit->haveskill[4];
  if (v31 >= 1 && (sBtlGetSkilltbl(v31)->area & 8) != 0)
  {
    v33 = wk->effList;
    v34 = pUnit->haveskill[4];
    sBtlDeleteEffectData_SkillIDType(v33, v34, 1u);
  }
  v35 = pUnit->haveskill[5];
  if (v35 >= 1 && (sBtlGetSkilltbl(v35)->area & 8) != 0)
  {
    v37 = wk->effList;
    v38 = pUnit->haveskill[5];
    sBtlDeleteEffectData_SkillIDType(v37, v38, 1u);
  }
  sBtlForceDelete_SkillFlag_Acter(pUnit, 0x400u);
  sBtlForceDelete_ID_Acter(wk->effList, pUnit, 55);
  if ((pUnit->hstatus & 0x100) != 0)
  {
    x = pUnit->pos.x;
    y = pUnit->pos.y;
    v54 = wk->effList;
    z = pUnit->pos.z;
    w = pUnit->pos.w;
    v64.x = x;
    v64.y = y;
    v64.z = z;
    v64.w = w;
    sBtlCreateEff(v54, pUnit, 18, 0, v64, 0, 0, 1.0, 0);
    pUnit->color = 0;
  }
  else
  {
    if (flg)
    {
      v42 = pUnit->pos.x;
      v43 = pUnit->pos.y;
      v44 = wk->effList;
      v45 = pUnit->pos.z;
      v46 = pUnit->pos.w;
      v47 = 18;
      v48 = 1.0;
      v49 = v44;
      v50 = pUnit;
    }
    else
    {
      v42 = pUnit->pos.x;
      v43 = pUnit->pos.y;
      v58 = wk->effList;
      v45 = pUnit->pos.z;
      v46 = pUnit->pos.w;
      v48 = 1.0;
      v49 = v58;
      v50 = pUnit;
      v47 = 4;
    }
    v65.x = v42;
    v65.y = v43;
    v65.z = v45;
    v65.w = v46;
    sBtlCreateEff(v49, v50, v47, 0, v65, 0x80808080, 0, v48, 0);
  }
  pUnit->status |= 0x4000u;
  if (BadStatus != 17)
  {
    sBtlSetAction(pUnit, 1, 0);
    sBtlSetMotion(pUnit, 7, 0, 0, 0);
    goto LABEL_102;
  }
  if (flg == 1)
  {
    pUnit->m_rate = 0.0;
    goto LABEL_103;
  }
  else
  {
    pUnit->m_rate = 0.5;
LABEL_103:
    summonindex_menu = wk->summonindex_menu;
    if (summonindex_menu[0] != index)
      goto LABEL_104;
    goto LABEL_109;
  }
  summonindex_menu = wk->summonindex_menu;
  if (summonindex_menu[0] != index)
  {
LABEL_104:
    goto LABEL_105;
  }
LABEL_109:
  summonindex_menu[0] = -1;
LABEL_105:
  v62 = wk->summonindex_menu;
  if (v62[1] != index)
    return 1;
  v62 = wk->summonindex_menu;
  v62[1] = -1;
  return 1;
}

// 0x2017f10
bool sBtlResetSummon_E(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  f32 x;
  f32 y;
  SBTLEFF_LISTWORK *effList;
  f32 z;
  f32 w;
  sdfVector4_t v11;

  wk->mode = 4;
  wk->actwk->status = 0;
  actaiwk = wk->actaiwk;
  actaiwk->mode = 9;
  actaiwk->stat = 1;
  wk->color = 8421504;
  x = wk->pos.x;
  y = wk->pos.y;
  effList = wk->effList;
  z = wk->pos.z;
  w = wk->pos.w;
  v11.x = x;
  v11.y = y;
  v11.z = z;
  v11.w = w;
  sBtlCreateEff(effList, wk, 5, 0, v11, 0x80808080, 0, 1.0, 0);
  return 1;
}

// 0x2018030
void sBtlResetAction_Flag(SBTLUNIT_WORK *wk) {
  s32 side;

  if (wk->battlemode == 3)
    return;
  side = wk->side;
  if ((side & 0x80) != 0 || (side & 1) != 0)
  {
    wk->actaiwk->status &= ~0x4000u;
    wk->status &= ~0x4000u;
  }
}

// 0x2018120
bool ResetAction(SBTLUNIT_WORK *wk, s8 flg) {
  sdfVector4_t *p_mv_spdbk;
  SBTLACTAI_WORK *actaiwk;
  s32 vstatus;
  u16 major;
  s32 minor;
  VISUALDATA_WORK *VisualData;
  MOTIONDATA_WORK *MotionVisualData;
  f32 *p_m_speed;
  f32 v19;

  wk->actaiwk->status = wk->actaiwk->status & 0xFFFFDD80 | 0x44;
  *(u64 *)&vct_A.x = 0;
  *(u64 *)&vct_A.z = 0;
  p_mv_spdbk = &wk->mv_spdbk;
  actaiwk = wk->actaiwk;
  wk->mv_rot = 0.0;
  *p_mv_spdbk = vct_A;
  if (flg == 1)
  {
    actaiwk->searchflg = 1;
    sBtlSetGroupAction(wk, -1, 0xCu, 0);
    actaiwk = wk->actaiwk;
  }
  else
  {
    actaiwk->mode = 12;
  }
  actaiwk->target_frame = 0;
  actaiwk->stat = 1;
  *(u64 *)&actaiwk->frame = 0x3C00000000LL;
  vstatus = wk->vstatus;
  if ((vstatus & 0x10) == 0)
  {
    major = wk->major;
    minor = wk->minor;
    VisualData = sBtlGetVisualData(major, minor);
    MotionVisualData = sBtlGetMotionVisualData(wk->major, wk->minor, wk->next_motionno);
    if ((MotionVisualData->flg & 1) != 0)
      p_m_speed = &MotionVisualData->m_speed;
    else
      p_m_speed = &VisualData->m_speed;
    v19 = *p_m_speed;
    vstatus = wk->vstatus;
    wk->m_rate = v19;
  }
  wk->status &= ~0x100u;
  wk->vstatus = vstatus & 0xF7FDFFFF;
  wk->actaiwk->status &= ~0x4000u;
  sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
  return 1;
}

// 0x2018410
bool sBtlCreateEnemyList(void) {
  SBTLUNIT_LISTWORK *enemyList;
  s32 number;
  s64 i;
  SBTLUNIT_LISTWK *v7;
  SBTLUNIT_WORK *p_pUnit;
  SBTLUNIT_WORK *pUnit;
  s64 j;
  SBTLUNIT_LISTWK *v11;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v14;
  SBTLACTION_WORK *actwk;
  SBTLACTAI_WORK *actaiwk;
  u32 status;
  bool v18;
  s32 mode;
  SBTLUNIT_LISTWORK *v24;
  s64 v25;
  SBTLUNIT_LISTWK *pUnitL;
  s64 v27;

  enemyList = wk->enemyList;
  if (enemyList)
  {
    number = enemyList->number;
    if (number >= 1)
    {
      for (i = 0; i < number; ++i)
      {
        v7 = enemyList->pUnitL[i];
        pUnit = v7->pUnit;
        p_pUnit = &v7->pUnit;
        if (pUnit)
        {
          p_pUnit = 0;
          number = enemyList->number;
        }
      }
    }
    enemyList->count = 0;
  }
  for (j = 0; ; ++j)
  {
    UnitMng = wk->UnitMng;
    if (j >= UnitMng->number)
      break;
    v14 = UnitMng->pUnitL[j]->pUnit;
    if (!v14)
      continue;
    if ((v14->side & 2) == 0)
      continue;
    actwk = v14->actwk;
    if (!actwk)
      continue;
    actaiwk = v14->actaiwk;
    if (actaiwk)
    {
      status = actwk->status;
      if (status != 10)
      {
        v18 = (v14->status & 0x5000) != 0 || status == 11;
        if (!v18 && status != 14)
        {
          mode = actaiwk->mode;
          if (status != 30 && mode != 9 && status != 40 && v14->mode >= 5)
          {
            v24 = wk->enemyList;
            v25 = (u32)v24->number;
            if ((s32)v25 < 1)
              continue;
            pUnitL = v24->pUnitL;
            v27 = 0;
            while (pUnitL[v27]->pUnit)
            {
              if (v25 == ++v27)
                goto LABEL_17;
            }
            v11 = pUnitL[v27];
            ++v24->count;
            v11->pUnit = v14;
            v11 = ((char *)v11 + 24);
            LODWORD(v11[-1].pUnit) = v27;
            continue;
          }
        }
      }
    }
LABEL_17:
    ;
  }
  return 1;
}

// 0x20186f0
SBTLUNIT_LISTWORK *sBtlCreateSideList_AI(SBTLUNIT_SIDE side, s32 flg) {
  char v4;
  SBTLUNIT_LISTWORK *UnitList;
  s32 v6;
  s64 i;
  u32 status;
  bool v9;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 vstatus;
  s64 number;
  SBTLUNIT_LISTWK *pUnitL;
  s64 v18;
  SBTLUNIT_LISTWK *v19;
  s64 j;
  u32 v21;
  bool v22;
  SBTLUNIT_LISTWORK *v24;
  SBTLUNIT_WORK *v25;
  bool v26;
  s64 v27;
  SBTLUNIT_LISTWK *v28;
  s64 v29;
  SBTLUNIT_LISTWK *v30;

  v4 = side;
  UnitList = sBtlCreateUnitList(48);
  if (flg != 2)
  {
    if (flg == 1)
    {
      if ((v4 & 2) != 0)
        v6 = 1;
      else
        v6 = 2;
    }
    else if (flg)
    {
      v6 = 0;
    }
    else
    {
      v6 = v4 & 7;
    }
    goto LABEL_15;
  }
  if ((v4 & 2) == 0)
  {
    v6 = 2;
LABEL_15:
    for (i = 0; ; ++i)
    {
      UnitMng = wk->UnitMng;
      if (i >= UnitMng->number)
        return UnitList;
      pUnit = UnitMng->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if ((v6 & pUnit->side) != 0)
      {
        status = pUnit->actwk->status;
        v9 = status > 0xE || ((1 << status) & 0x4C00) == 0;
        if (v9 && pUnit->actaiwk->mode != 9 && status != 40 && pUnit->mode >= 5)
        {
          vstatus = pUnit->vstatus;
          if ((pUnit->side & 0x81) != 1)
            goto LABEL_82;
          if (!wk->NakamaShugouOn)
          {
LABEL_82:
            if ((vstatus & 0x10000) == 0)
            {
              number = (u32)UnitList->number;
              if ((s32)number >= 1)
              {
                pUnitL = UnitList->pUnitL;
                v18 = 0;
                while (pUnitL[v18]->pUnit)
                {
                  if (number == ++v18)
                    goto LABEL_20;
                }
                v19 = pUnitL[v18];
                ++UnitList->count;
                v19->pUnit = pUnit;
                v19 = ((char *)v19 + 24);
                LODWORD(v19[-1].pUnit) = v18;
              }
            }
          }
        }
      }
LABEL_20:
      ;
    }
  }
  for (j = 0; ; ++j)
  {
    v24 = wk->UnitMng;
    if (j >= v24->number)
      break;
    v25 = v24->pUnitL[j]->pUnit;
    if (!v25)
      continue;
    if (!v25->major)
    {
      v21 = v25->actwk->status;
      v22 = v21 > 0xE || ((1 << v21) & 0x4C00) == 0;
      if (v22 && v25->actaiwk->mode != 9)
      {
        v26 = v21 == 40 || v25->mode < 5;
        if (!v26 && (v25->vstatus & 0x10000) == 0)
        {
          v27 = (u32)UnitList->number;
          if ((s32)v27 >= 1)
          {
            v28 = UnitList->pUnitL;
            v29 = 0;
            while (v28[v29]->pUnit)
            {
              if (v27 == ++v29)
                goto LABEL_54;
            }
            v30 = v28[v29];
            ++UnitList->count;
            v30->pUnit = v25;
            v30 = ((char *)v30 + 24);
            LODWORD(v30[-1].pUnit) = v29;
          }
        }
      }
    }
LABEL_54:
    ;
  }
  return UnitList;
}

// 0x2018ac0
SBTLUNIT_LISTWORK *sBtlCreateSideList(SBTLUNIT_SIDE side, s32 flg) {
  char v4;
  SBTLUNIT_LISTWORK *UnitList;
  s32 v7;
  s64 i;
  SBTLUNIT_LISTWK *v10;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  SBTLACTION_WORK *actwk;
  SBTLACTAI_WORK *actaiwk;
  u32 status;
  bool v17;
  s32 mode;
  bool v21;
  s64 number;
  SBTLUNIT_LISTWK *pUnitL;
  s64 v24;

  v4 = side;
  UnitList = sBtlCreateUnitList(48);
  if (flg == 1)
  {
    if ((v4 & 2) != 0)
      v7 = 1;
    else
      v7 = 2;
    goto LABEL_12;
  }
  if (flg)
    v7 = 0;
  else
    v7 = v4 & 7;
LABEL_12:
  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & v7) == 0)
      continue;
    actwk = pUnit->actwk;
    if (!actwk)
      continue;
    actaiwk = pUnit->actaiwk;
    if (actaiwk)
    {
      status = actwk->status;
      if (status != 10)
      {
        v17 = (pUnit->status & 0x5000) != 0 || status == 11;
        if (!v17 && status != 14)
        {
          mode = actaiwk->mode;
          if (status != 30 && mode != 9)
          {
            v21 = status == 40 || pUnit->mode < 5;
            if (!v21 && (pUnit->vstatus & 0x10000) == 0)
            {
              number = (u32)UnitList->number;
              if ((s32)number >= 1)
              {
                pUnitL = UnitList->pUnitL;
                v24 = 0;
                while (pUnitL[v24]->pUnit)
                {
                  if (number == ++v24)
                    goto LABEL_14;
                }
                v10 = pUnitL[v24];
                ++UnitList->count;
                v10->pUnit = pUnit;
                v10 = ((char *)v10 + 24);
                LODWORD(v10[-1].pUnit) = v24;
              }
            }
          }
        }
      }
    }
LABEL_14:
    ;
  }
  return UnitList;
}

// 0x2018d10
static bool SetMotion_Core(SBTLUNIT_WORK *wk) {
  s32 next_motionno;
  s32 motionID;
  dds3ModelHandle_t *hModel;
  f32 m_BlendTree1D;
  f32 m_BlendTree2DX;
  f32 m_BlendTree2DY;
  f32 m_rate;
  dds3ModelHandle_t *v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  s32 motionno;
  s32 beforeframe;
  s32 v20;
  s32 v21;
  bool v22;
  s32 motion_FrameSkip;
  dds3ModelHandle_t *v24;
  s16 v25;

  next_motionno = wk->next_motionno;
  if (wk->motionno == next_motionno)
  {
    motionID = wk->motionID;
    if (sBtlCheckLoopMotion(wk, motionID))
    {
      hModel = wk->hModel;
      if (hModel)
      {
        if (wk->m_BlendTree1DFlg)
        {
          m_BlendTree1D = wk->m_BlendTree1D;
          mdlSetMotionBlendTree1D(hModel, m_BlendTree1D);
          hModel = wk->hModel;
          wk->m_BlendTree1DFlg = 0;
        }
        if (wk->m_BlendTree2DFlg)
        {
          m_BlendTree2DX = wk->m_BlendTree2DX;
          m_BlendTree2DY = wk->m_BlendTree2DY;
          mdlSetMotionBlendTree2D(hModel, m_BlendTree2DX, m_BlendTree2DY);
          hModel = wk->hModel;
          wk->m_BlendTree2DFlg = 0;
        }
        m_rate = wk->m_rate;
        mdlSetMotionSpeed(hModel, m_rate);
      }
      return 1;
    }
    next_motionno = wk->next_motionno;
  }
  wk->motionno = next_motionno;
  v12 = wk->hModel;
  wk->motionID = wk->next_motionID;
  wk->motion_serialno = (u16)(wk->motion_serialno + 1);
  if (v12)
  {
    if (wk->m_BlendTree1DFlg)
    {
      v13 = wk->m_BlendTree1D;
      mdlSetMotionBlendTree1D(v12, v13);
      v12 = wk->hModel;
      wk->m_BlendTree1DFlg = 0;
    }
    if (wk->m_BlendTree2DFlg)
    {
      v14 = wk->m_BlendTree2DX;
      v15 = wk->m_BlendTree2DY;
      mdlSetMotionBlendTree2D(v12, v14, v15);
      v12 = wk->hModel;
      wk->m_BlendTree2DFlg = 0;
    }
    v16 = wk->m_rate;
    mdlSetMotionSpeed(v12, v16);
    if (wk->motionID != wk->motion_NoUseMSE_motionID)
    {
      if (wk->motion_SeSkep)
      {
        wk->motion_SeSkep = 0;
      }
      else
      {
        if (!sBtlUnitChkOverMotionSe(wk))
        {
          motionno = wk->motionno;
          beforeframe = wk->beforeframe;
          sBtlPlayMotionSE(wk, motionno, beforeframe);
        }
      }
    }
    v20 = wk->motionno;
    v21 = wk->motionID;
    v22 = sBtlCheckLoopMotion(wk, v21);
    motion_FrameSkip = wk->motion_FrameSkip;
    v24 = wk->hModel;
    v25 = wk->beforeframe;
    if (v22)
    {
      if (motion_FrameSkip < 1)
      {
        mdlSmoothLoopMotion(v24, 0, v20, (f32)v25, (f32)v25, 0.0);
      }
      else
      {
        mdlSmoothLoopMotion(v24, 0, v20, (f32)v25, (f32)v25, (f32)motion_FrameSkip);
        wk->motion_FrameSkip = 0;
      }
    }
    else if (motion_FrameSkip < 1)
    {
      mdlSmoothSingleMotion(v24, 0, v20, (f32)v25, (f32)v25, 0.0);
    }
    else
    {
      mdlSmoothSingleMotion(v24, 0, v20, (f32)v25, (f32)v25, (f32)motion_FrameSkip);
      wk->motion_FrameSkip = 0;
    }
  }
  return 1;
}

// 0x2010300
bool sBtlCheckLoopMotion(SBTLUNIT_WORK *wk, SBTLUNIT_MOTION no) {
  u16 major;
  s32 minor;
  s32 next_motionno;
  s32 end_motionno;
  _BOOL4 v9;

  if ((wk->status & 0x40) != 0 && wk->changeflg)
    goto LABEL_17;
  major = wk->major;
  minor = wk->minor;
  next_motionno = wk->next_motionno;
  end_motionno = (u16)sBtlGetMotionVisualData(major, minor, next_motionno)->end_motionno;
  if (end_motionno == 1)
  {
LABEL_17:
    LOBYTE(v9) = 0;
    return v9;
  }
  if (end_motionno == 3)
  {
LABEL_20:
    LOBYTE(v9) = 1;
    return v9;
  }
  if (wk->cmbSkl->pNakama0 == wk)
  {
    if ((u32)no <= 0x29 && ((1 << no) & 0x30020000000LL) != 0)
      goto LABEL_20;
  }
  if (no <= 2)
  {
    LOBYTE(v9) = (no & 0xFFFFFFFD) == 0;
    return v9;
  }
  if (no == 5)
    goto LABEL_20;
  if (no != 35)
    goto LABEL_17;
  return LOBYTE(wk->side) >> 7;
}

// 0x2019100
void sBtlStartSlowMotion(SBTLUNIT_WORK *wk, f32 _Spd) {
  s32 hstatus;

  hstatus = wk->hstatus;
  wk->MSlow_Speed = Spd;
  wk->hstatus = hstatus | 0x20000000;
}

// 0x2019120
void sBtlEndSlowMotion(SBTLUNIT_WORK *wk) {
  wk->hstatus &= ~0x20000000u;
  wk->MSlow_Speed = 1.0;
}

// 0x2019140
bool sBtlChkSlowMotion(SBTLUNIT_WORK *wk, f32 *_MSlow_Speed) {
  *MSlow_Speed = wk->MSlow_Speed;
  return (HIBYTE(wk->hstatus) >> 5) & 1;
}

// 0x2019160
void sBtlSetMotionHitStop(SBTLUNIT_WORK *wk, f32 _Spd, f32 _Time, f32 _StFrame) {
  s32 hstatus;

  hstatus = wk->hstatus;
  if ((hstatus & 0x20000000) == 0)
  {
    wk->MHitStop_Speed = Spd;
    wk->MHitStop_Time = Time;
    wk->hstatus = hstatus | 0x2000;
    wk->MHitStop_TimeLeft = Time;
    wk->MHitStop_StFrame = StFrame;
  }
}

// 0x2019190
static void ProcMotionHitStop(SBTLUNIT_WORK *wk) {
  s32 hstatus;
  dds3ModelHandle_t *hModel;
  f32 MotionFrameF;
  f32 v6;
  f32 *p_MHitStop_TimeLeft;
  s32 v8;

  hstatus = wk->hstatus;
  if ((hstatus & 0x2000) != 0)
  {
    hModel = wk->hModel;
    MotionFrameF = mdlGetMotionFrameF(hModel);
    hstatus = wk->hstatus;
    if (MotionFrameF >= wk->MHitStop_StFrame)
    {
      hstatus = hstatus & 0xFFFF9FFF | 0x4000;
      wk->hstatus = hstatus;
    }
  }
  if ((hstatus & 0x20000000) != 0)
  {
    v8 = hstatus & 0xFFFFBFFF;
    p_MHitStop_TimeLeft = &wk->MHitStop_TimeLeft;
    goto LABEL_13;
  }
  if ((hstatus & 0x4000) != 0)
  {
    v6 = wk->MHitStop_TimeLeft - VRF_DeltaTime;
    wk->MHitStop_TimeLeft = v6;
    if (v6 <= 0.0)
    {
      p_MHitStop_TimeLeft = &wk->MHitStop_TimeLeft;
      v8 = hstatus & 0xFFFFBFFF;
LABEL_13:
      wk->hstatus = v8;
      *(u64 *)&wk->MHitStop_Speed = 0;
      *p_MHitStop_TimeLeft = 0.0;
    }
  }
}

// 0x2019280
void sBtlSetEffectHitStop(SBTLUNIT_WORK *wk, f32 _Spd, f32 _Time, f32 _StTime) {
  s32 hstatus;

  hstatus = wk->hstatus;
  wk->EHitStop_Speed = Spd;
  wk->EHitStop_Time = Time;
  wk->EHitStop_TimeLeft = Time;
  wk->EHitStop_StTime = StTime;
  wk->EHitStop_StTimeLeft = StTime;
  wk->hstatus = hstatus | 0x8000;
}

// 0x20192b0
static void ProcEffectHitStop(SBTLUNIT_WORK *wk) {
  s32 hstatus;
  f32 v4;
  f32 v5;

  hstatus = wk->hstatus;
  if ((hstatus & 0x8000) != 0)
  {
    v4 = wk->EHitStop_StTimeLeft - VRF_DeltaTime;
    wk->EHitStop_StTimeLeft = v4;
    if (v4 <= 0.0)
    {
      hstatus = hstatus & 0xFFFE7FFF | 0x10000;
      wk->hstatus = hstatus;
    }
  }
  if ((hstatus & 0x10000) != 0)
  {
    v5 = wk->EHitStop_TimeLeft - VRF_DeltaTime;
    wk->EHitStop_TimeLeft = v5;
    if (v5 <= 0.0)
    {
      wk->EHitStop_TimeLeft = 0.0;
      wk->hstatus = hstatus & 0xFFFEFFFF;
      *(u64 *)&wk->EHitStop_Speed = 0;
    }
  }
}

// 0x2019360
void sBtlClrCtrl(s32 pRes, s32 tgt, s32 bgn, s32 frm) {
  if (pRes != tgt)
  {
    if (wk->dbgptr)
    {
      if (g_DbgCnt > 9)
        return;
      g_DbgCnt = g_DbgCnt + 1;
    }
  }
}

// 0x2019470
dds3ProcessFunc_t Proc(dds3ProcessID_t *id) {
  SBTLPANEL_WORK *panelwk;
  u32 status;
  SBATTLE_WORK *v7;
  s32 aiBgnCnt;
  s64 v11;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 vstatus;
  dds3ModelHandle_t *hModel;
  u32 color;
  dds3ModelHandle_t *v18;
  _BOOL4 ditherAlpha;
  s32 v20;
  s32 v21;
  s32 mdlEffClr;
  s32 mdlEffClrTgt;
  dds3ModelHandle_t *v25;
  u32 v26;
  SBATTLE_WORK *v29;
  s32 devilid;
  s32 side;
  SBTLDVLTK_LISTWORK *dvltkList;
  SBATTLE_WORK *v42;
  SBATTLE_WORK *v43;
  s32 v44;
  s64 v45;
  dds3ModelHandle_t *v48;
  SBTLUNIT_WORK *p_pLoadingUnit;
  f32 dissolveAlpha;
  s32 encountno;
  s32 v54;

  wk->nakamaAtkPos = wk->nakamaAtkPos1 + wk->nakamaAtkPos0;
  if (!wk->UnitMng)
    return 0;
  if ((wk->status & 1) == 0)
    return 0;
  panelwk = wk->panelwk;
  if (panelwk)
  {
    panelwk = wk->panelwk;
    if ((panelwk->status & 2) == 0)
      return 0;
  }
  status = wk->status;
  if ((status & 4) != 0)
  {
    status = wk->status;
    if ((status & 8) == 0)
    {
      sBtlCreateEnemyList();
      v7 = wk;
      if (!v7->bBfrBtlEnd)
        goto LABEL_37;
      goto LABEL_31;
      if (!v7->bBfrBtlEnd)
      {
LABEL_37:
        sBtlKudaHuuinCheck();
        v11 = 0;
        while (1)
        {
          UnitMng = wk->UnitMng;
          if (v11 >= UnitMng->number)
            return 0;
          pUnit = UnitMng->pUnitL[v11]->pUnit;
          if (!pUnit)
            goto LABEL_46;
          vstatus = pUnit->vstatus;
          if ((vstatus & 0x403) != 0)
          {
            sBtlFadeProc(pUnit);
            vstatus = pUnit->vstatus;
          }
          if ((vstatus & 0x200000) != 0)
          {
            RGBFade(pUnit);
          }
          hModel = pUnit->hModel;
          if (hModel && (pUnit->vstatus & 0x100) == 0)
          {
            color = pUnit->color;
            if (!pUnit->ditherAlpha || (color & 0x80000000) != 0)
            {
              mdlSetColor(hModel, color);
            }
            else
            {
              mdlSetColor_And_EffAlp(hModel, color, (f32)((f32)HIBYTE(color) / 127.0) * 0.1);
            }
            v18 = pUnit->hModel;
            ditherAlpha = pUnit->ditherAlpha;
            mdlSetDitherAlphaUse(v18, ditherAlpha);
            mdlSetDissolveAlpha(pUnit->hModel, pUnit->dissolveAlpha);
            mdlSetColorChroma(pUnit->hModel, pUnit->color_chroma);
            mdlSetStoneUse(pUnit->hModel, pUnit->stoneUse);
            if (pUnit->bMdlEffClr)
            {
              mdlEffClr = pUnit->mdlEffClr;
              mdlEffClrTgt = pUnit->mdlEffClrTgt;
              sBtlClrCtrl(mdlEffClr, mdlEffClrTgt, v20, v21);
              v25 = pUnit->hModel;
              v26 = pUnit->mdlEffClr;
              mdlSetEffectColor(v25, v26);
            }
          }
          sBtlWeakShildProc(pUnit);
          sBtlWinceProc(pUnit);
          if (pUnit->criticalcol)
            --pUnit->criticalcol;
          switch (pUnit->mode)
          {
            case 1:
            case 2:
              v29 = wk;
              if ((v29->status & 0x100000) == 0)
                goto LABEL_135;
              {
                v29 = wk;
                if (v29->loadListID == pUnit->ListID)
                {
LABEL_135:
                  if (!sBtlSearchReturn_Unit(pUnit))
                  {
                    v42 = wk;
                    if ((v42->status2 & 0x200) == 0)
                    {
                      if (v42->pLoadingUnit)
                        goto LABEL_143;
                      v42 = wk;
                      v42->pLoadingUnit = pUnit;
LABEL_144:
                      v43 = wk;
                      if (v43->pLoadingUnit != pUnit)
                        goto LABEL_43;
                      goto LABEL_9001;
LABEL_143:
                      goto LABEL_144;
LABEL_9001:
                      v43 = wk;
                      v43->status |= 0x100000u;
                      v43->loadListID = pUnit->ListID;
                      if (sBtlModelDataLoad(pUnit))
                      {
                        if ((pUnit->side & 0x80) != 0)
                          goto LABEL_165;
                        if (wk->battlemode == 3 && (pUnit->side & 1) != 0)
                        {
LABEL_165:
                          v48 = pUnit->hModel;
                          setPlayerFootEffect(v48);
                        }
                        p_pLoadingUnit = &wk->pLoadingUnit;
                        p_pLoadingUnit = 0;
                      }
                    }
                  }
                }
              }
LABEL_43:
              sBtlUnitUpdate(pUnit);
LABEL_46:
              ++v11;
              break;
            case 4:
            case 0xC:
              Proc(pUnit);
              goto LABEL_43;
            case 5:
              if (sBtlGetNode())
                goto LABEL_43;
              devilid = pUnit->para->devilid;
              if (devilid <= 290)
              {
                if ((devilid & 0xFFFFFFFE) != 0x102)
                {
                  if ((u32)(devilid - 285) < 2 || devilid == 288)
                  {
LABEL_177:
                    v44 = pUnit->vstatus;
                    v45 = 1;
                    goto LABEL_180;
                  }
                  if (devilid != 290)
                    goto LABEL_174;
                }
              }
              else if (devilid != 297)
              {
                if ((u32)(devilid - 307) <= 2)
                  goto LABEL_177;
LABEL_174:
                v44 = pUnit->vstatus;
                v45 = 16;
                goto LABEL_180;
              }
              v44 = pUnit->vstatus;
              v45 = 32;
LABEL_180:
              pUnit->vstatus = v44 | 1;
              *(u32 *)&pUnit->fade_sttime = 0;
              dissolveAlpha = pUnit->dissolveAlpha;
              *(u64 *)&pUnit->fadepara = v45;
              if (dissolveAlpha == 0.0)
                pUnit->dissolveAlpha = 1.0;
              pUnit->mode = 8;
              encountno = wk->encountno;
              v54 = pUnit->para->devilid;
              Start(encountno, v54, 0);
              goto LABEL_43;
            case 6:
              pUnit->vstatus |= 2u;
              pUnit->mode = 7;
              goto LABEL_98;
            case 7:
              if ((pUnit->vstatus & 2) == 0)
              {
                pUnit->mode = 4;
                pUnit->actwk->status = pUnit->actwk->next_st;
              }
LABEL_98:
              MotinProc(pUnit);
              goto LABEL_43;
            case 8:
              Proc(pUnit);
              MotinProc(pUnit);
              sBtlSetLight_Map(pUnit, 10, 0);
              goto LABEL_43;
            case 9:
              if ((pUnit->status & 0x20000) == 0)
                goto LABEL_110;
              if (AllDeleteEnemy(pUnit))
              {
LABEL_110:
                side = pUnit->side;
                if ((side & 2) != 0)
                {
                  --wk->enemy_num;
                  sBtlDeleteEnemy(pUnit);
                  sBtlCheckDrop_Normal(pUnit);
                  side = pUnit->side;
                }
                if ((side & 1) == 0)
                  goto LABEL_190;
                dvltkList = wk->dvltkList;
                if (!sBtlSearchDvltk(dvltkList, pUnit))
                {
LABEL_190:
                  sBtlDeleteUnit(pUnit);
                  DeleteHpGage(wk->bsc, pUnit, 0);
                }
              }
              goto LABEL_43;
            default:
              goto LABEL_43;
          }
        }
      }
LABEL_31:
      v7 = wk;
      aiBgnCnt = v7->aiBgnCnt;
      if (aiBgnCnt <= 119)
      {
        v7 = wk;
        aiBgnCnt = v7->aiBgnCnt;
        v7->aiBgnCnt = aiBgnCnt + 1;
      }
      goto LABEL_37;
    }
  }
  return 0;
}

// 0x201b8c0
static bool AllDeleteEnemy(SBTLUNIT_WORK *wk) {
  s64 v3;
  char v4;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  SBTLACTION_WORK *actwk;
  SBTLACTAI_WORK *actaiwk;
  u32 status;
  bool v12;
  s32 mode;
  bool v16;

  v3 = 0;
  v4 = 1;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v3 >= UnitMng->number)
      return v4 & 1;
    pUnit = UnitMng->pUnitL[v3]->pUnit;
    if (!pUnit)
      goto LABEL_7;
    actwk = pUnit->actwk;
    if (!actwk)
      goto LABEL_29;
    actaiwk = pUnit->actaiwk;
    if (!actaiwk)
      goto LABEL_29;
    status = actwk->status;
    if (status == 10)
      goto LABEL_29;
    v12 = (pUnit->status & 0x5000) != 0 || status == 11;
    if (v12 || status == 14)
      goto LABEL_29;
    mode = actaiwk->mode;
    if (status == 30 || mode == 9)
      goto LABEL_29;
    v16 = status == 40 || pUnit->mode < 5;
    if (v16 || (pUnit->side & 2) == 0 || wk->ListID == pUnit->ListID)
      goto LABEL_29;
    if ((wk->status & 0x2000000) != 0 || pUnit->mode == 9)
    {
LABEL_29:
      if ((pUnit->side & 2) != 0)
        v4 &= wk->ListID == pUnit->ListID;
      goto LABEL_7;
    }
    pUnit->actaiwk->status = pUnit->actaiwk->status & 0xFFFFFF9F | 0x40;
    sBtlSetDeadDamage(pUnit, 0, 0);
    v4 = 0;
LABEL_7:
    ++v3;
  }
}

// 0x201baf0
bool sBtlCheckUnit_Exec_R(void) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  bool v7;
  SBTLUNIT_WORK *pUnit;
  s32 side;

  if (!wk->UnitMng)
    return 1;
  if ((wk->status2 & 0x200) == 0)
  {
    for (i = 0; ; ++i)
    {
      UnitMng = wk->UnitMng;
      number = UnitMng->number;
      v7 = i >= number;
      if (i >= number)
        return v7;
      pUnit = UnitMng->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if ((u32)(pUnit->mode - 1) <= 1 && pUnit->gstat != 5)
      {
        side = pUnit->side;
        if ((side & 2) != 0)
          return v7;
        if ((side & 1) != 0)
        {
          if (!sBtlSearchReturn_Unit(pUnit))
            return v7;
        }
      }
    }
  }
  return 0;
}

// 0x201bcb0
bool sBtlCheckUnit_Exec(void) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  bool v5;
  SBTLUNIT_WORK *pUnit;

  if (wk->UnitMng)
  {
    for (i = 0; ; ++i)
    {
      UnitMng = wk->UnitMng;
      number = UnitMng->number;
      v5 = i >= number;
      if (i >= number)
        return v5;
      pUnit = UnitMng->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if ((u32)(pUnit->mode - 1) < 2)
        return v5;
    }
  }
  return 1;
}

// 0x2019f60
bool sBtlModelDataLoad(SBTLUNIT_WORK *wk) {
  s32 gstat;
  u16 v5;
  s32 minor_d;
  dds3ModelResrc_t *v7;
  u16 major;
  s32 minor;
  u16 v16;
  dds3Basic_t *v17;
  dds3Basic_t *p_pBasic;
  void *workdata;
  s64 naturalAligment;
  evtUnitHandle_t *klass;
  dds3ModelHandle_t *Model;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  sdfVector4_t *p_nextpos;
  dds3ModelHandle_t *hModel;
  struct sdfVector4_t scale;
  dds3PoseSet_t *poseset;
  sdfVector4_t *p_scl;
  evtUnitHandle_t *hEveUnit;
  s32 side;
  u16 v38;
  s32 v39;
  u32 v40;
  dds3Basic_t *v41;
  s64 v42;
  evtUnitHandle_t *v43;
  dds3ModelHandle_t *v44;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  dds3PoseSet_t *v50;
  sdfVector4_t *v51;
  dds3ModelHandle_t *hModel_d;
  SBATTLE_WORK *v56;
  SBATTLE_WORK *v58;
  u32 v59;
  s32 v61;
  struct sdfVector4_t pos;
  struct sdfVector4_t v65;
  dds3Basic_t *ActiveScene;
  dds3Basic_t *pBasic;
  sdfVector4_t v70;
  sdfVector4_t v71;

  gstat = wk->gstat;
  pBasic = 0;
  ActiveScene = 0;
  switch (gstat)
  {
    case 0:
      if (!sBtlCheckModelDataLoadEnd(wk))
        return (u32)(wk->mode - 3) < 0xFFFFFFFE;
      major = wk->major;
      minor = wk->minor;
      v16 = UnitRegist(major, minor);
      pBasic = dds3GetActiveScene();
      v17 = dds3SceneBasicSearch(pBasic, v16, 5u);
      p_pBasic = &wk->pBasic;
      wk->pBasic = v17;
      workdata = wk->pBasic->workdata;
      if (workdata)
      {
        if (workdata->klass->_2.naturalAligment < (u32)naturalAligment || workdata->klass->_2.typeHierarchy[naturalAligment - 1] != Project_Basic_dds3UnitObjectBasicWorkData_t)
        {
LABEL_126:
        }
      }
      klass = workdata[2].klass;
      wk->hEveUnit = klass;
      Model = wk->hEveUnit->Model;
      wk->hModel = Model;
      wk->hEveUnit->Flag |= 0x200000u;
      x = wk->pos.x;
      y = wk->pos.y;
      z = wk->pos.z;
      w = wk->pos.w;
      v70.x = x;
      v70.y = y;
      v70.z = z;
      v70.w = w;
      dds3SetPosPoseSet(&wk->pBasic, v70);
      dds3SetRotPoseSet(&wk->pBasic, wk->rot);
      pos = wk->pos;
      vct_A = pos;
      p_nextpos = &wk->nextpos;
      *p_nextpos = vct_A;
      hModel = wk->hModel;
      mdlHide(wk->hModel);
      scale = wk->scale;
      vct_A = scale;
      poseset = p_pBasic->poseset;
      p_scl = &poseset->scl;
      *p_scl = vct_A;
      sBtlSetLight_Map(wk, 0, 0);
      hEveUnit = wk->hEveUnit;
      evtUnitLightOn(hEveUnit);
      if ((wk->status & 0x40) != 0)
      {
        wk->gstat = 1;
        return (u32)(wk->mode - 3) < 0xFFFFFFFE;
      }
      side = wk->side;
      if ((side & 3) == 0)
        goto LABEL_111;
      wk->gstat = 2;
      if ((side & 0x80) != 0)
      {
        wk->gstat = 5;
LABEL_118:
        sBtlSetModelDataLoadEnd(wk);
LABEL_121:
        v58 = wk;
        v59 = v58->status & 0xDFFFFFFF;
        goto LABEL_124;
      }
      return (u32)(wk->mode - 3) < 0xFFFFFFFE;
    case 1:
      v5 = wk->major;
      minor_d = wk->minor_d;
      v7 = mdlPrepare(v5, minor_d, 0);
      if (!READY(v7))
        return (u32)(wk->mode - 3) < 0xFFFFFFFE;
      v38 = wk->major;
      v39 = wk->minor_d;
      v40 = UnitRegist(v38, v39);
      ActiveScene = dds3GetActiveScene();
      v41 = dds3SceneBasicSearch(ActiveScene, v40, 5u);
      wk->pBasic_d = v41;
      workdata = wk->pBasic_d->workdata;
      if (workdata)
      {
        if (workdata->klass->_2.naturalAligment < (u32)v42 || workdata->klass->_2.typeHierarchy[v42 - 1] != Project_Basic_dds3UnitObjectBasicWorkData_t)
        {
          goto LABEL_126;
        }
      }
      v43 = workdata[2].klass;
      wk->hEveUnit_d = v43;
      v44 = wk->hEveUnit_d->Model;
      wk->hModel_d = v44;
      wk->hEveUnit_d->Flag |= 0x200000u;
      v45 = wk->pos.x;
      v46 = wk->pos.y;
      v48 = wk->pos.z;
      v47 = wk->pos.w;
      v71.x = v45;
      v71.y = v46;
      v71.z = v48;
      v71.w = v47;
      dds3SetPosPoseSet(&wk->pBasic_d, v71);
      dds3SetRotPoseSet(&wk->pBasic_d, wk->rot);
      v65 = wk->scale;
      vct_A = v65;
      v50 = wk->pBasic_d->poseset;
      v51 = &v50->scl;
      *v51 = vct_A;
      hModel_d = wk->hModel_d;
      mdlHide(hModel_d);
      if ((wk->side & 3) != 0)
      {
        wk->gstat = 2;
        return (u32)(wk->mode - 3) < 0xFFFFFFFE;
      }
      wk->gstat = 0;
LABEL_111:
      if (wk->mode == 1)
        v61 = 8;
      else
        v61 = 4;
      wk->mode = v61;
      v58 = wk;
      v59 = v58->status & 0xFFEFFFFF;
LABEL_124:
      v58->status = v59;
      return (u32)(wk->mode - 3) < 0xFFFFFFFE;
    case 2:
      if ((wk->side & 0x81) == 1)
      {
        if (sBtlLoadDevilSE(wk))
          goto LABEL_85;
        goto LABEL_93;
      }
      if (!sBtlLoadDevilSE(wk))
        goto LABEL_93;
      if ((wk->side & 0x80) != 0)
      {
        wk->gstat = 5;
        goto LABEL_118;
      }
      sBtlCheckBossSE(wk);
      goto LABEL_121;
    case 3:
      if (!sBtlLoadDeadVoice(wk))
        goto LABEL_93;
LABEL_85:
      sBtlCheckBossSE(wk);
      return (u32)(wk->mode - 3) < 0xFFFFFFFE;
    case 4:
      if (!sBtlLoadBossAtrac3(wk))
        goto LABEL_93;
      goto LABEL_9003;
      if (!sBtlLoadBossAtrac3(wk))
      {
LABEL_93:
        v58 = wk;
        v59 = v58->status | 0x20000000;
        goto LABEL_124;
      }
LABEL_9003:
      wk->gstat = 5;
      v56 = wk;
      v56->status &= ~0x20000000u;
LABEL_25:
      sBtlSetModelDataLoadEnd(wk);
      return (u32)(wk->mode - 3) < 0xFFFFFFFE;
    case 5:
      goto LABEL_25;
    default:
      return (u32)(wk->mode - 3) < 0xFFFFFFFE;
  }
}

// 0x201c5f0
void sBtlCheckBossSE(SBTLUNIT_WORK *wk) {
  s32 devilid;
  bool v4;
  u32 v5;
  bool v6;
  s32 v7;
  bool v8;

  devilid = wk->para->devilid;
  if (devilid <= 269)
  {
    if (devilid == 262 || (devilid & 0xFFFFFFFE) == 0x10C)
      goto LABEL_21;
  }
  else
  {
    v4 = devilid != 288 && (u32)(devilid - 285) >= 2;
    if (!v4 || ((v5 = devilid - 300, v6 = v5 > 9, v7 = (1 << v5) & 0x3B1, !v6) ? (v8 = v7 == 0) : (v8 = 1), !v8))
    {
LABEL_21:
      wk->gstat = 4;
      goto LABEL_20;
    }
  }
  wk->gstat = 5;
  if ((wk->status & 0x10000) == 0)
    sBtlSetModelDataLoadEnd(wk);
LABEL_20:
  wk->status &= ~0x20000000u;
}

// 0x201c080
bool sBtlSetModelDataLoadEnd(SBTLUNIT_WORK *wk) {
  s32 side;
  s32 v4;
  s32 v5;
  s32 v6;
  sdatUnitWork_t *v7;
  u32 v8;
  s32 v11;
  s32 v13;
  sdatUnitWork_t *para;
  u32 BadStatus;
  u32 v16;
  s32 devilid;
  s32 mode;
  s32 v20;
  sdatUnitWork_t *v21;
  u32 v22;
  u32 v23;
  u32 v24;
  s32 bst_effserialID2;
  SBTLEFF_LISTWORK *effList;
  SBTLDVLTK_LISTWORK *dvltkList;

  side = wk->side;
  if ((side & 0x80) != 0)
  {
    wk->gstat = 0;
    if (wk->mode == 1)
      v11 = 8;
    else
      v11 = 4;
    wk->mode = v11;
    goto LABEL_90;
  }
  if ((side & 2) != 0)
  {
    if (!CheckLoadData(wk))
      return 1;
    wk->gstat = 0;
    if (wk->mode == 1)
      v13 = 8;
    else
      v13 = 4;
    wk->mode = v13;
    if ((wk->status & 0x10000) != 0)
    {
      para = wk->para;
      BadStatus = sBtlGetBadStatus(para);
      if (BadStatus != 22)
      {
        v16 = BadStatus;
        sBtlSetBadStatus_No(wk, 0, v16, 1, -1);
      }
    }
    goto LABEL_90;
  }
  if ((wk->status & 0x10000) != 0)
  {
    if (sBtlLoadEffectData_Nakama(wk))
    {
      if (sBtlCreateWork(wk))
      {
        devilid = wk->para->devilid;
        if (sBtlLoadAttackHitData(wk, devilid, 0))
        {
          mode = wk->mode;
          wk->gstat = 0;
          if (mode == 1)
            v20 = 8;
          else
            v20 = 4;
          wk->mode = v20;
          if ((wk->status & 0x10000) != 0)
          {
            v21 = wk->para;
            v22 = sBtlGetBadStatus(v21);
            if (v22 == 5)
            {
              sBtlResetBadStatus(wk, 32);
              bst_effserialID2 = wk->bst_effserialID2;
              if (bst_effserialID2 != -1)
              {
                bst_effserialID2 = wk->bst_effserialID2;
                effList = wk->effList;
                sBtlDeleteEffectData_SerialID2(effList, bst_effserialID2);
                wk->bst_effserialID2 = -1;
              }
            }
            else
            {
              v23 = v22;
              if (v22 != 22)
              {
                sBtlSetBadStatus_No(wk, 0, v23, 1, -1);
              }
            }
          }
          dvltkList = wk->dvltkList;
          sBtlCreateDvltk_Priority(dvltkList, wk, 18);
          goto LABEL_89;
        }
      }
    }
    return 1;
  }
  if (sBtlCreateWork(wk))
  {
    v4 = wk->para->devilid;
    if (sBtlLoadAttackHitData(wk, v4, 0))
    {
      v5 = wk->mode;
      wk->gstat = 0;
      if (v5 == 1)
        v6 = 8;
      else
        v6 = 4;
      wk->mode = v6;
      v7 = wk->para;
      v8 = sBtlGetBadStatus(wk->para);
      if (v8 == 22)
      {
        goto LABEL_19;
      }
      v24 = v8;
      sBtlSetBadStatus_No(wk, 0, v24, 1, -1);
LABEL_19:
      if (ChkBossBtlStart())
      {
LABEL_89:
LABEL_90:
        wk->status &= ~0x100000u;
        return 1;
      }
      sBtlFirstSummonTextSet(wk);
      goto LABEL_90;
    }
  }
  return 1;
}

// 0x201c8f0
static bool ChkBossBtlStart(void) {
  SB_ENCOUNTPAC *EncountPac;
  bool v3;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  SBTLUNIT_WORK *pUnit;

  EncountPac = sBtlGetEncountPac(-1);
  if ((EncountPac[wk->encountno]->flag & 6) == 0)
  {
    for (i = 0; ; ++i)
    {
      UnitMng = wk->UnitMng;
      number = UnitMng->number;
      v3 = i < number;
      if (i >= number)
        return v3;
      pUnit = UnitMng->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if ((pUnit->side & 0x3F) == 2)
      {
        if ((sBtlCheck(pUnit, 0, 0) & 0x80000000) == 0)
          return v3;
      }
    }
  }
  return 1;
}

// 0x201c760
static bool CheckLoadData(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v5;
  s32 devilid;

  if ((wk->side & 2) == 0)
    return 1;
  v5 = wk;
  if ((v5->status & 0x10000) != 0)
    goto LABEL_11;
  if (v5->bosseveloadflg)
    goto LABEL_11;
  return 1;
LABEL_11:
  if (!sBtlLoadEffectData(wk))
    return 0;
  devilid = wk->para->devilid;
  if (sBtlLoadAttackHitData(wk, devilid, 0))
    return 1;
  return 0;
}

// 0x201ca90
s32 sBtlGetLight_SetPos(SBTLUNIT_WORK *wk, s8 lightno) {
  s8 *light_buff;

  light_buff = wk->light_buff;
  if (light_buff[0] == lightno)
    return 1;
  if (light_buff[1] == lightno)
    return 2;
  return 3;
}

// 0x201cac0
s32 sBtlSetLight_SetPos(SBTLUNIT_WORK *wk, s8 lightno) {
  s32 v3;
  s8 *light_buff;
  s32 result;
  s8 v8;

  LOBYTE(v3) = lightno;
  v3 = lightno;
  light_buff = wk->light_buff;
  if ((u8)light_buff[0] == v3)
  {
    light_buff[0] = v3;
    return 1;
  }
  if ((u8)light_buff[1] == v3)
  {
    light_buff[1] = v3;
    return 2;
  }
  else
  {
    result = wk->light_sw;
    if ((result + 1) << 24 < 50331648)
      v8 = result + 1;
    else
      v8 = 1;
    wk->light_sw = v8;
    *((u8 *)&light_buff->max_length + result + 7) = v3;
  }
  return result;
}

// 0x201cbc0
bool sBtlSetUnitLight_Dir(SBTLUNIT_WORK *wk, const sdfVector4_t *dir, s32 flg) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  u32 vstatus;
  f32 *p_x;
  mapLightParam_t *light;
  sdfVector4_t *p_dir0;
  evtUnitHandle_t *hEveUnit;
  bool v16;
  f32 *v18;
  mapLightParam_t *v19;
  sdfVector4_t *p_dir1;
  evtUnitHandle_t *v21;
  f32 *v23;
  mapLightParam_t *v24;
  sdfVector4_t *p_dir2;
  evtUnitHandle_t *v26;

  w = dir->w;
  z = dir->z;
  y = dir->y;
  x = dir->x;
  if (flg == 4)
  {
    vstatus = wk->vstatus;
    if ((vstatus & 0x40000) != 0)
      flg = ~(vstatus >> 18) & 2;
    else
      flg = 1;
  }
  else if (flg > 3)
  {
    return 0;
  }
  if ((wk->status & 0x800) != 0)
    return 0;
  if (flg != 2)
  {
    if (flg == 1)
    {
      p_x = &vf00.x;
      p_x[4] = x;
      p_x[5] = y;
      p_x[6] = z;
      p_x[7] = w;
      light = wk->light;
      p_dir0 = &light->dir0;
      *p_dir0 = vct_A;
      hEveUnit = wk->hEveUnit;
      evtSetUnitLightDir(hEveUnit, 0);
      return 1;
    }
    v23 = &vf00.x;
    v23[4] = x;
    v23[5] = y;
    v23[6] = z;
    v23[7] = w;
    v24 = wk->light;
    p_dir2 = &v24->dir2;
    *p_dir2 = vct_A;
    v26 = wk->hEveUnit;
    evtSetUnitLightDir2(v26, 2);
    return 1;
  }
  v18 = &vf00.x;
  v18[4] = x;
  v18[5] = y;
  v18[6] = z;
  v18[7] = w;
  v19 = wk->light;
  p_dir1 = &v19->dir1;
  *p_dir1 = vct_A;
  v21 = wk->hEveUnit;
  v16 = 1;
  evtSetUnitLightDir1(v21, 1);
  return v16;
}

// 0x201cf50
bool sBtlSetUnitLight(SBTLUNIT_WORK *wk, s32 time, u32 diffuse, u32 ambient, s32 flg, s32 flg2) {
  u32 vstatus;
  mapLightParam_t *light;
  s32 v15;
  s32 v17;
  u32 v18;
  u32 rgb0;
  u32 rgb1;
  evtUnitHandle_t *hEveUnit;
  u32 rgb2;

  if (flg == 4)
  {
    vstatus = wk->vstatus;
    if ((vstatus & 0x40000) != 0)
      flg = ~(vstatus >> 18) & 2;
    else
      flg = 1;
  }
  else if (flg > 3)
  {
    return 0;
  }
  if (flg2 == 1)
  {
    wk->lightcnt = time;
    goto LABEL_11;
  }
  if (wk->lightcnt > 0)
    return 0;
LABEL_11:
  if ((wk->status & 0x800) != 0)
    return 0;
  if (flg == 2)
  {
    light = wk->light;
    light->rgb1 = diffuse & 0xFFFFFF | 0x80000000;
    v15 = 0x80000;
  }
  else
  {
    light = wk->light;
    if (flg == 1)
    {
      light->rgb0 = diffuse & 0xFFFFFF | 0x80000000;
      v15 = 0x40000;
    }
    else
    {
      light->rgb2 = diffuse & 0xFFFFFF | 0x80000000;
      v15 = 0x100000;
    }
  }
  v17 = wk->vstatus;
  v18 = ambient & 0xFFFFFF | 0x80000000;
  rgb0 = light->rgb0;
  light->rgba = v18;
  rgb1 = light->rgb1;
  wk->vstatus = v17 | v15;
  hEveUnit = wk->hEveUnit;
  rgb2 = light->rgb2;
  evtSetUnitLightAndAmbient3(hEveUnit, time, rgb0, rgb1, rgb2, v18);
  return 1;
}

// 0x201af90
bool sBtlSetLight_Map(SBTLUNIT_WORK *wk, s32 time, s32 flg) {
  char vstatus_high;
  mapLightParam_t *v8;
  s32 major;
  s32 minor;
  f32 x;
  f32 y;
  f32 z;
  s32 v14;
  bool v15;
  s32 hitlight_cnt;
  bool v17;
  s32 v18;
  s32 vstatus;
  mapLightParam_t *light;
  sdfVector4_t *p_dir0;
  mapLightParam_t *v23;
  f32 *col0;
  u32 *v25;
  mapLightParam_t *v28;
  sdfVector4_t *p_dir1;
  mapLightParam_t *v30;
  f32 *col1;
  u32 *v32;
  mapLightParam_t *v34;
  sdfVector4_t *p_dir2;
  SBTLACTION_WORK *actwk;
  s32 use_skillid;
  f32 v38;
  f32 v39;
  f32 w;
  f32 v41;
  f32 v42;
  f32 v43;
  mapLightParam_t *v44;
  s32 v45;
  f32 v46;
  f32 hitlight_x;
  f32 v48;
  f32 v49;
  long f64 v51;
  s64 v52;
  mapLightParam_t *v53;
  f32 *col2;
  u32 *v55;
  s32 v56;
  s32 v57;
  s32 v58;
  u32 v59;
  s32 v60;
  u32 v61;
  u32 v62;
  u32 v63;
  s64 v64;
  u32 v65;
  u32 v66;
  s32 v67;
  u32 v68;
  u32 v69;
  mapLightParam_t *v70;
  u32 rgba;
  evtUnitHandle_t *hEveUnit;
  u32 rgb0;
  u32 rgb1;
  u32 rgb2;
  struct sdfVector4_t dir1;
  struct sdfVector4_t dir2;
  struct sdfVector4_t v81;
  struct sdfVector4_t v82;
  struct sdfVector4_t v83;
  struct sdfVector4_t dir0;
  struct sdfVector4_t v85;
  struct sdfVector4_t v86;
  struct sdfVector4_t v87;
  struct sdfVector4_t v88;
  sdfVector4_t Vec;
  sdfVector4_t v90;

  vstatus_high = HIBYTE(wk->vstatus);
  *(u64 *)&Vec.x = 0;
  *(u64 *)&Vec.z = 0;
  if ((vstatus_high & 0x10) != 0)
    return 0;
  if ((wk->status & 0x8000000) != 0)
    return 0;
  v8 = Allocate(mapLightParam_t);
  _ctor(v8, 0);
  major = wk->major;
  minor = wk->minor;
  x = wk->pos.x;
  y = wk->pos.y;
  z = wk->pos.z;
  mapGetLightParam(major, minor, x, y, z, v8);
  if (wk->para->devilid == 259)
    time *= 4;
  if (flg != 1)
  {
    v14 = wk->lightcnt - 1;
    v15 = wk->lightcnt == 1;
    wk->lightcnt = v14;
    if (v14 < 0 || v15)
      goto LABEL_16;
    return 0;
  }
  wk->lightcnt = time;
LABEL_16:
  if (!sBtlIsSetsumaPadStop() && !sBtlIsEnemyLastDeadStop())
  {
    hitlight_cnt = wk->hitlight_cnt;
    v17 = __OFSUB__(hitlight_cnt, 1);
    v18 = hitlight_cnt - 1;
    if (v18 < 0 == v17)
      wk->hitlight_cnt = v18;
  }
  if ((wk->status & 0x800) != 0)
    return 0;
  vstatus = wk->vstatus;
  if ((vstatus & 0x40000) == 0)
  {
    v81 = v8->dir0;
    vct_A = v81;
    light = wk->light;
    p_dir0 = &light->dir0;
    *p_dir0 = vct_A;
    v23 = wk->light;
    v23->rgb0 = v8->rgb0;
    col0 = v23->col0;
    v25 = v8->col0;
    col0[0] = (f32)v25[8];
    col0[1] = (f32)v25[9];
    col0[2] = (f32)v25[10];
    vstatus = wk->vstatus;
    if ((vstatus & 0x80000) != 0)
      goto LABEL_28;
LABEL_32:
    v82 = v8->dir1;
    vct_A = v82;
    v28 = wk->light;
    p_dir1 = &v28->dir1;
    *p_dir1 = vct_A;
    v30 = wk->light;
    v30->rgb1 = v8->rgb1;
    col1 = v30->col1;
    v32 = v8->col1;
    col1[0] = (f32)v32[8];
    col1[1] = (f32)v32[9];
    col1[2] = (f32)v32[10];
    if ((wk->vstatus & 0x100000) != 0)
      goto LABEL_88;
LABEL_38:
    v83 = v8->dir2;
    vct_A = v83;
    v34 = wk->light;
    p_dir2 = &v34->dir2;
    *p_dir2 = vct_A;
    wk->light->rgb2 = v8->rgb2;
    actwk = wk->actwk;
    if (actwk->status != 12)
      goto LABEL_72;
    use_skillid = actwk->use_skillid;
    if (use_skillid <= 669)
    {
      if (use_skillid == 176)
      {
        if ((u32)(actwk->framecnt - 3) < 9)
          goto LABEL_68;
        goto LABEL_72;
      }
      if (use_skillid != 669)
        goto LABEL_72;
    }
    else if (use_skillid != 670 && use_skillid != 1296)
    {
      if (use_skillid != 1297 || (u32)(actwk->framecnt - 18) < 0xFFFFFFF6)
        goto LABEL_72;
LABEL_68:
      v38 = wk->rot.x;
      v39 = wk->rot.y;
      v41 = wk->rot.z;
      w = wk->rot.w;
      v90.x = v38;
      v90.y = v39;
      v90.z = v41;
      v90.w = w;
      sBtlGetRotToVector(v90, &Vec);
      v42 = Vec.x;
      time = 2;
      v43 = Vec.z;
      v44 = wk->light;
      v44->dir2.y = 0.0;
      v44->dir2.w = 1.0;
      v45 = -2140106592;
      v44->dir2.x = v42;
      v44->dir2.z = v43;
LABEL_87:
      v44->rgb2 = v45;
      goto LABEL_88;
    }
    if ((u32)(actwk->framecnt - 8) < 0xA)
      goto LABEL_68;
LABEL_72:
    if ((u32)(wk->hitlight_cnt - 48) < 0xFFFFFFD1)
      goto LABEL_88;
    v46 = wk->pos.x;
    hitlight_x = wk->hitlight_x;
    Vec.y = -0.3;
    v48 = v46 - hitlight_x;
    v49 = wk->pos.z - wk->hitlight_z;
    Vec.x = v46 - hitlight_x;
    Vec.z = v49;
    sub_1B332C0(0, v48, -0.3, v49, Vec.w);
    sub_1949110(0);
    sub_1B335A0(&Vec, 0, v51);
    v52 = *(u64 *)&Vec.x;
    v53 = wk->light;
    v53->dir2.w = 1.0;
    *(u64 *)&v53->dir2.x = v52;
    *(f32 *)&v52 = Vec.z;
    v53->rgb2 = 0x80000000;
    LODWORD(v53->dir2.z) = v52;
    col2 = v53->col2;
    *(u64 *)col2 = 0;
    col2[2] = 0.0;
    v55 = NewSpecific(uint, 0x32u);
    InitializeArray_55364416(v55, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__A6B668FD7D28B4AFC06E47F7C82EC18F3BA5892ADF31A80F58C2ACF699628D97, 0);
    v56 = *(u32 *)((char *)v55 + 24);
    time = 0;
    v57 = v56 - wk->hitlight_cnt;
    v58 = v56 - 1;
    v59 = wk->hitlight_r + 32;
    if (v57 >= v58)
      v57 = v58;
    v60 = v55[v57];
    v61 = (wk->hitlight_g + 32) * v60;
    v62 = (wk->hitlight_b + 32) * v60;
    v63 = v59 * v60;
    v64 = 2155905153LL * v61;
    v65 = v61 >> 8;
    v66 = (v59 * v60) >> 8;
    if (v62 >> 8 <= 0xFE)
      v67 = ((2155905153u * (u64)v62) >> 32 << 9) & 0xFFFF0000;
    else
      v67 = 16711680;
    v44 = wk->light;
    if (v65 >= 0xFF)
      v68 = 65280;
    else
      v68 = (2 * HIDWORD(v64)) & 0xFFFFFF00;
    if (v66 <= 0xFE)
      v69 = (v63 / 0xFF) | 0x80000000;
    else
      v69 = -2147483393;
    v45 = v69 | v68 | v67;
    goto LABEL_87;
  }
  if ((vstatus & 0x80000) == 0)
    goto LABEL_32;
LABEL_28:
  if ((vstatus & 0x100000) == 0)
    goto LABEL_38;
LABEL_88:
  v70 = wk->light;
  if ((wk->vstatus & 0x1C0000) != 0)
  {
    rgba = v70->rgba;
  }
  else
  {
    rgba = v8->rgba;
    v70->rgba = rgba;
  }
  hEveUnit = wk->hEveUnit;
  rgb0 = v70->rgb0;
  rgb1 = v70->rgb1;
  rgb2 = v70->rgb2;
  evtSetUnitLightAndAmbient3(hEveUnit, time, rgb0, rgb1, rgb2, rgba);
  dir0 = wk->light->dir0;
  vct_A = dir0;
  evtSetUnitLightDir(wk->hEveUnit, 0);
  dir1 = wk->light->dir1;
  v85 = wk->light->dir1;
  dir1 = v85;
  v86 = dir1;
  dir1 = v86;
  vct_A = dir1;
  evtSetUnitLightDir1(wk->hEveUnit, 1);
  dir2 = wk->light->dir2;
  v87 = wk->light->dir2;
  dir2 = v87;
  v88 = dir2;
  dir2 = v88;
  vct_A = dir2;
  evtSetUnitLightDir2(wk->hEveUnit, 0);
  return 1;
}

// 0x201d0e0
bool sBtlCheckMotionMove(SBTLUNIT_WORK *wk) {
  dds3ModelHandle_t *hModel;
  f32 MotionFrame;
  f32 MotionMove;
  s32 targetID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBATTLE_WORK *v11;
  SBTLUNIT_WORK *pUnit;
  f32 x;
  f32 z;
  f32 v15;
  f32 v16;
  f32 v17;
  s32 v20;
  struct sdfVector4_t pos;
  f32 v26;
  f32 v27;
  struct sdfVector4_t v30;
  struct sdfVector4_t rot;
  f32 posx;
  f32 posxa;
  struct sdfVector4_t posxb;
  sdfMatrix4_t pz;
  sdfMatrix4_t px;
  sdfVector4_t v39;

  if (wk->cmbSkl->bRun)
  {
    if (sBtlGetPChara() == wk)
      return 0;
  }
  if ((wk->status & 0x800) != 0)
    return 0;
  hModel = wk->hModel;
  if (!hModel)
    return 0;
  MotionFrame = mdlGetMotionFrame(hModel);
  wk->mvflg = 0;
  MotionMove = sBtlGetMotionMove(wk, MotionFrame);
  if ((wk->side & 2) == 0)
    goto LABEL_39;
  if (MotionMove <= 0.0)
    goto LABEL_39;
  if (wk->actwk->status != 3)
    goto LABEL_39;
  targetID = wk->actaiwk->targetID;
  if (targetID == -1)
    goto LABEL_39;
  posx = MotionMove;
  MotionMove = posx;
  targetID = wk->actaiwk->targetID;
  UnitMng = wk->UnitMng;
  if (targetID < 0)
    goto LABEL_39;
  MotionMove = posx;
  v11 = wk;
  if (v11)
  {
    MotionMove = posx;
    v11 = wk;
    if (v11->UnitMng)
    {
      if (UnitMng->number > targetID)
      {
        pUnit = UnitMng->pUnitL[targetID]->pUnit;
        if (pUnit)
        {
          if (pUnit != wk)
          {
            x = wk->pos.x;
            z = wk->pos.z;
            v15 = pUnit->pos.x;
            v16 = pUnit->pos.z;
            v17 = (f32)(sBtlGetLenXZ(x, z, v15, v16) - wk->actaiwk->hit_area_r)
                - pUnit->actaiwk->hit_area_r;
            MotionMove = posx;
            if (posx > v17)
            {
              MotionMove = v17;
              if (v17 < 0.0)
                return 1;
            }
          }
        }
      }
    }
  }
LABEL_39:
  if (MotionMove == 0.0)
    return 1;
  rot = wk->rot;
  posxa = MotionMove;
  vct_A = rot;
  ToMatrix();
  v20 = (u8)byte_5756085;
  vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
  get_transpose(&px, &mtx_A, 0);
  pz = px;
  v39 = op_Multiply_60923920(&pz, vct_A, 0);
  vct_A = v39;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, posxa);
  pos = wk->pos;
  vct_B = pos;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  posxb = vct_A;
  if ((wk->status & 0x80) != 0)
    goto LABEL_83;
  if ((wk->side & 0x80) != 0)
  {
    if (wk->battlemode != 3)
      goto LABEL_83;
  }
  v26 = wk->pos.x;
  v27 = wk->pos.z;
  if (sBtlCheckMapHit_Data(v26, v27, posxb.x, posxb.z, &px.m00, &pz.m00) && wk->para->devilid)
  {
    return 0;
  }
LABEL_83:
  vct_A = posxb;
  v30 = vct_A;
  wk->mvflg = 1;
  wk->pos = v30;
  return 1;
}

// 0x201a9a0
static bool MotinProc(SBTLUNIT_WORK *wk) {
  s32 vstatus;
  s32 hstatus;
  f32 v6;
  f32 v7;
  s32 v8;
  f32 m_rate;
  s32 motStopCnt;
  u16 major;
  s32 minor;
  s32 motionno;
  MOTIONDATA_WORK *MotionVisualData;
  dds3ModelHandle_t *hModel;
  MOTIONDATA_WORK *v18;
  dds3ModelHandle_t *v19;
  s32 v21;
  s32 beforeframe;
  SBTLUNIT_WORK *v25;
  s32 v26;
  s32 v27;
  dds3ModelHandle_t *v28;
  dds3ModelHandle_t *v30;
  dds3ModelHandle_t *v31;
  f32 MotionFrameF;
  s32 v34;
  s32 scrMotion;
  s32 v36;
  SBTLUNIT_WORK *v37;
  s32 v38;

  vstatus = wk->vstatus;
  if ((vstatus & 0x10) != 0)
    return (vstatus & 0x10) == 0;
  ProcMotionHitStop(wk);
  hstatus = wk->hstatus;
  if ((hstatus & 0x8000) != 0)
  {
    v6 = wk->EHitStop_StTimeLeft - VRF_DeltaTime;
    wk->EHitStop_StTimeLeft = v6;
    if (v6 <= 0.0)
    {
      hstatus = hstatus & 0xFFFE7FFF | 0x10000;
      wk->hstatus = hstatus;
    }
  }
  if ((hstatus & 0x10000) != 0)
  {
    v7 = wk->EHitStop_TimeLeft - VRF_DeltaTime;
    wk->EHitStop_TimeLeft = v7;
    if (v7 <= 0.0)
    {
      wk->EHitStop_TimeLeft = 0.0;
      wk->hstatus = hstatus & 0xFFFEFFFF;
      *(u64 *)&wk->EHitStop_Speed = 0;
    }
  }
  if (IsSceanStop())
    goto LABEL_17;
  motStopCnt = wk->motStopCnt;
  if (motStopCnt)
  {
    m_rate = 0.0;
    wk->motStopCnt = motStopCnt - 1;
    goto LABEL_30;
  }
  v8 = wk->hstatus;
  if ((v8 & 0x20000000) == 0)
    goto LABEL_26;
LABEL_28:
  m_rate = wk->m_rate * wk->MSlow_Speed;
  goto LABEL_30;
LABEL_17:
  v8 = wk->hstatus;
  if ((v8 & 0x20000000) != 0)
    goto LABEL_28;
  if ((wk->status & 0x10) == 0)
  {
    if ((wk->vstatus & 0x2000000) != 0)
      goto LABEL_27;
    m_rate = 0.0;
    if (sBtlCheckEnshutuSummonUnit(wk))
      goto LABEL_27;
    goto LABEL_30;
  }
LABEL_26:
  if ((v8 & 0x4000) == 0)
  {
LABEL_27:
    m_rate = wk->m_rate;
    goto LABEL_30;
  }
  m_rate = wk->MHitStop_Speed;
LABEL_30:
  major = wk->major;
  minor = wk->minor;
  motionno = wk->motionno;
  MotionVisualData = sBtlGetMotionVisualData(major, minor, motionno);
  switch (wk->motionst)
  {
    case 0:
      SetMotion_Core(wk);
      wk->framecnt = 0;
      wk->motionst = 1;
      goto LABEL_64;
    case 1:
      hModel = wk->hModel;
      v18 = MotionVisualData;
      if (!hModel)
        goto LABEL_72;
      mdlSetMotionSpeed(hModel, m_rate);
      if (m_rate != 0.0)
        goto LABEL_72;
      v19 = wk->hModel;
      v19->IsMdlEffect_NonStop = 0;
      if (IsSceanStop())
        goto LABEL_72;
      if (wk->actwk->status == 9)
      {
        v30 = wk->hModel;
        v30->IsMdlEffect_NonStop = 1;
      }
LABEL_72:
      if ((wk->side & 0x80) == 0)
        goto LABEL_81;
      v31 = wk->hModel;
      MotionFrameF = mdlGetMotionFrameF(v31);
      if (MotionFrameF > 0.0)
        goto LABEL_81;
      ++wk->UnitMotBugfix_Timeout;
      if (wk->UnitMotBugfix_RetryUse)
        goto LABEL_77;
      if (wk->UnitMotBugfix_OldFrame != MotionFrameF)
      {
        wk->UnitMotBugfix_OldFrame = MotionFrameF;
        goto LABEL_77;
      }
      v36 = wk->UnitMotBugfix_RetryCnt + 1;
      wk->UnitMotBugfix_RetryCnt = v36;
      if (v36 != 3)
      {
LABEL_77:
        v34 = wk->motionno;
        goto LABEL_78;
      }
      wk->UnitMotBugfix_RetryUse = 1;
      v34 = wk->motionno;
      switch (v34)
      {
        case 4:
          v37 = wk;
          v38 = 1;
          goto LABEL_107;
        case 131:
          v38 = 131;
          v37 = wk;
          goto LABEL_107;
        case 5:
          v37 = wk;
          v38 = 14;
LABEL_107:
          sBtlSetMotion(v37, v38, 0, 0, 0);
          goto LABEL_77;
      }
LABEL_78:
      if ((u32)(v34 - 4) >= 2 && v34 != 131 || wk->UnitMotBugfix_Timeout >= 20)
      {
LABEL_81:
        if (sBtlCheckMotionEnd(wk) && v18->end_motionno != 1 && (wk->vstatus & 0x8000000) == 0)
        {
          wk->framecnt = 0;
          wk->motionst = 2;
        }
      }
      return (vstatus & 0x10) == 0;
    case 2:
      v21 = wk->vstatus;
      if ((v21 & 0x8000000) != 0)
        return (vstatus & 0x10) == 0;
      if (wk->afterframe > ++wk->framecnt)
        return (vstatus & 0x10) == 0;
      if ((v21 & 0x2000000) != 0)
      {
        if (wk->motion_EndNoCng)
          return (vstatus & 0x10) == 0;
        scrMotion = wk->actaiwk->scrMotion;
        v25 = wk;
        v26 = scrMotion;
        v27 = 0;
        goto LABEL_91;
      }
      if (wk->changeflg || wk->motion_EndNoCng)
        return (vstatus & 0x10) == 0;
      if ((wk->side & 0x20) != 0)
        goto LABEL_55;
      if (sBtlIsDeadBgn(wk))
        return (vstatus & 0x10) == 0;
      if ((wk->side & 0x80) != 0)
      {
        beforeframe = wk->beforeframe;
        if (wk->motion_UseWait2)
        {
          v26 = 130;
          v25 = wk;
          goto LABEL_58;
        }
      }
      else
      {
LABEL_55:
        beforeframe = wk->beforeframe;
      }
      v25 = wk;
      v26 = 0;
LABEL_58:
      v27 = beforeframe;
LABEL_91:
      sBtlSetMotion(v25, v26, v27, 0, 0);
      return (vstatus & 0x10) == 0;
    case 4:
      SetMotion_Core(wk);
      wk->motionst = 1;
      v28 = wk->hModel;
      if (v28)
        v28->motionCtrlr->frame = wk->fMotStart;
      wk->framecnt = 0;
LABEL_64:
      wk->UnitMotBugfix_RetryUse = 0;
      wk->UnitMotBugfix_Timeout = 0;
      *(u64 *)&wk->UnitMotBugfix_RetryCnt = 0xC479C00000000000LL;
      return (vstatus & 0x10) == 0;
    default:
      return (vstatus & 0x10) == 0;
  }
}

// 0x200d3b0
s32 sBtlReleaseUnitList_ID(SBTLUNIT_LISTWORK *lwk, s32 id) {
  s64 v3;
  SBTLUNIT_LISTWK *v5;

  v3 = id;
  v5 = lwk->pUnitL[v3];
  --lwk->count;
  v5->pUnit = 0;
  v5 = ((char *)v5 + 24);
  LODWORD(v5[-1].pUnit) = 0;
  return lwk->pUnitL[v3]->ID;
}

// 0x201bdf0
s32 UnitRegist(MODELTYPE major, s32 minor) {
  u32 v5;
  dds3Basic_t *ControlScene;
  dds3Basic_t *v7;
  Il2CppObject *ModelHandle;
  s64 naturalAligment;
  s64 v10;
  dds3Basic_t *pObjectBasic;
  sdfVector4_t v13;
  sdfVector4_t v14;

  v5 = dds3SerializeID();
  v13.w = 1.0;
  v13.x = 0.0;
  v13.y = 0.0;
  v13.z = 0.0;
  v14.x = 0.0;
  v14.y = 0.0;
  v14.z = 0.0;
  v14.w = 1.0;
  pObjectBasic = dds3UnitObjectBasicAdd(v5, v13, v14);
  dds3ObjectBaseOnFlag(pObjectBasic, 0x20u);
  dds3SetRadiusPoseSet(pObjectBasic, 10.0);
  ControlScene = dds3GetControlScene();
  v7 = pObjectBasic;
  dds3SceneBasicSetActiveUnit(ControlScene, v7);
  dds3ObjectBaseMakeUnit(pObjectBasic, major, minor);
  ModelHandle = dds3ObjectBaseGetModelHandle(pObjectBasic);
  if (ModelHandle)
  {
    if (ModelHandle->klass->_2.naturalAligment < (u32)naturalAligment || ModelHandle->klass->_2.typeHierarchy[naturalAligment - 1] != dds3ModelHandle_t)
    {
      goto LABEL_26;
    }
  }
  if (mdlHasMotion(ModelHandle))
  {
    ModelHandle = dds3ObjectBaseGetModelHandle(pObjectBasic);
    if (!ModelHandle)
      goto LABEL_24;
    goto LABEL_9000;
    if (!ModelHandle)
    {
LABEL_24:
      mdlLoopMotion(ModelHandle, 0, 0);
      goto LABEL_25;
    }
LABEL_9000:
    if (ModelHandle->klass->_2.naturalAligment >= (u32)v10 && (dds3ModelHandle_t *)ModelHandle->klass->_2.typeHierarchy[v10 - 1] == dds3ModelHandle_t)
    {
      goto LABEL_24;
    }
LABEL_26:
  }
LABEL_25:
  dds3ObjectBaseSetPadControl(pObjectBasic, 0);
  return v5;
}

// 0x201d880
s32 sBtlGetPlayerMinor(SBTL_MODE btlMode, SBWEAPON_TYPE weaponType) {
  void *v5;
  void *v6;
  s64 v7;
  s64 v8;
  s32 *v9;

  v5 = NewSpecific(s32, 4u);
  InitializeArray_55364416(v5, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__31E605767C1BE0ADD9C4CA26175AD5AB3EBBB006198E6F342C7AAAB9D68396B1, 0);
  v6 = NewSpecific(s32, 4u);
  InitializeArray_55364416(v6, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__1784871EE39353A1B8F47F65A9C308CA7F210233DDFBBAA1F90274B47EADB33A, 0);
  v7 = 4 * weaponType;
  v8 = (s64)&v5[2] + v7;
  v9 = ((char *)&v6[2] + v7);
  if (btlMode)
    v9 = v8;
  return *v9;
}

// 0x20085b0
bool sBtlSetPlayerData(s8 flg) {
  sdatPlayerUnitWork_t *player;
  s32 battlemode;
  s32 m_type;
  s32 PlayerMinor;
  SBTLUNIT_WORK *Unit;
  SBTLUNIT_WORK *v13;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  SBTLUNIT_LISTWK *pUnitL;
  s64 v17;
  u16 major;
  s32 minor;
  VISUALDATA_WORK *VisualData_P;
  MOTIONDATA_WORK *MotionVisualData;
  sdfVector4_t *p_rot;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  SBTLACTAI_WORK *actaiwk;
  sdatUnitWork_t *para;
  sdatUnitWork_t *v36;
  sdatUnitWork_t *p_para;
  sdatParaWork_t *now;
  sdatUnitWork_t *v40;
  s32 maxhp;
  sdatParaWork_t *v42;
  SBTLACTAI_WORK *v43;
  sdfVector4_t *p_pos;
  struct sdfVector4_t rot;
  u16 v48;
  s32 v49;
  VISUALDATA_WORK *VisualData;
  MOTIONDATA_WORK *v51;
  f32 *p_m_speed;
  f32 scale;
  SBTLACTAI_WORK *v54;
  SBTLAISYO_DATAWORK *aisyo_bkup;
  SBTLAISYO_DATAWORK *aisyo;
  sdatPlayerUnitWork_t *v58;
  SKLID *aOmoideSkill;
  struct sbtl *v60;
  s32 bulletno;
  SBATTLE_WORK *v65;
  SBATTLE_WORK *v67;
  s64 v69;
  sdatPlayerUnitWork_t *v70;
  s32 mag;
  s32 maxmag;
  sdatUnitWork_t *stock_id;
  DEVILDATA_WORK *DevilData;
  SBATTLE_WORK *v75;
  s64 v76;
  s64 v77;
  sdatUnitWork_t *v78;
  s16 devilid;
  SBATTLE_WORK *v82;
  s32 *huuma_devilID;
  SBATTLE_WORK *v88;
  s16 *stack_p;
  s16 *summonindex;
  s32 *summonindex_menu;
  s32 v92;
  s64 m_Items;
  s64 v94;
  SBTLUNIT_WORK *v95;
  SBTLUNIT_LISTWK *v96;
  SBATTLE_WORK *v97;
  SBATTLE_WORK *v100;
  s16 *v101;
  s32 *v102;
  s32 v103;
  sdatUnitWork_t *v104;
  s16 v105;
  SBATTLE_WORK *v107;
  u32 *p_stock_mask;
  s32 v109;
  SBATTLE_WORK *v111;
  SBTLUNIT_LISTWORK *v112;
  RED_GUAGE *v113;
  s64 v114;
  SBTLUNIT_WORK *Nakama;
  s32 ListID;
  SBATTLE_WORK *v119;
  u32 status;
  struct sdfVector4_t pos;
  sdfVector4_t v125;
  sdfVector4_t v126;

  player = GBWK->player;
  battlemode = (u16)wk->battlemode;
  if (battlemode == 3)
    goto LABEL_69;
  m_type = sBtlDat()->m_type;
  PlayerMinor = sBtlGetPlayerMinor(battlemode, m_type);
  Unit = sBtlCreateUnit(0, PlayerMinor, 0);
  v13 = Unit;
  UnitMng = wk->UnitMng;
  number = (u32)UnitMng->number;
  if ((s32)number < 1)
  {
LABEL_11:
    v13->ListID = 0;
    major = v13->major;
    minor = v13->minor;
    goto LABEL_13;
  }
  pUnitL = UnitMng->pUnitL;
  v17 = 0;
  while (pUnitL[v17]->pUnit)
  {
    if (number == ++v17)
      goto LABEL_11;
  }
  v94 = v17;
  v95 = Unit;
  v96 = pUnitL[v17];
  v96->pUnit = v13;
  v96 = ((char *)v96 + 24);
  LODWORD(v96[-1].pUnit) = v17;
  ++UnitMng->count;
  v13->ListID = UnitMng->pUnitL[v94]->ID;
  major = v13->major;
  minor = v13->minor;
LABEL_13:
  VisualData_P = sBtlGetVisualData_P(major, minor);
  MotionVisualData = sBtlGetMotionVisualData(v13->major, v13->minor, 0);
  p_rot = &v13->rot;
  x = v13->rot.x;
  v13->mv_spd.z = 0.0;
  y = v13->rot.y;
  z = v13->rot.z;
  w = v13->rot.w;
  v13->side = 129;
  v13->minor_d = 0;
  v13->mv_rot = 0.0;
  v13->max_mvspd.z = VisualData_P->mv_spd;
  v13->max_mvrot = VisualData_P->rot_spd;
  v125.x = x;
  v125.y = y;
  v125.z = z;
  v125.w = w;
  sBtlGetRotateDeg(v125, 180.0);
  actaiwk = v13->actaiwk;
  v13->mv_rotbk = 0.0;
  *p_rot = vct_A;
  *(u64 *)&actaiwk->status = actaiwk->status & 0xFFFFFE1E | 0xC0;
  sBtlSetLockID(v13, 0);
  para = player->para;
  wk->playerID = v13->ListID;
  v36 = Clone(para, 0);
  p_para = &v13->para;
  v13->para = v36;
  now = player->para->now;
  if (!now->hp)
  {
    v40 = v13->para;
    v40->badstatus = 0;
    maxhp = now->maxhp;
    v42 = v40->now;
    v13->actwk->status = 0;
    v42->hp = maxhp;
    wk->status &= ~8u;
  }
  v43 = v13->actaiwk;
  v43->hit_area_r = VisualData_P->hit_area_r;
  v43->priv_area_r = MotionVisualData->m_mv_area_r;
  pos = main_data->pos;
  vct_A = pos;
  p_pos = &v13->pos;
  *p_pos = vct_A;
  rot = main_data->rot;
  vct_A = rot;
  *p_rot = vct_A;
  if ((v13->vstatus & 0x10) == 0)
  {
    v48 = v13->major;
    v49 = v13->minor;
    VisualData = sBtlGetVisualData(v48, v49);
    v51 = sBtlGetMotionVisualData(v13->major, v13->minor, v13->next_motionno);
    if ((v51->flg & 1) != 0)
      p_m_speed = &v51->m_speed;
    else
      p_m_speed = &VisualData->m_speed;
    v13->m_rate = *p_m_speed;
  }
  scale = VisualData_P->scale;
  v13->color = -2139062144;
  v54 = v13->actaiwk;
  v13->scale.x = scale;
  v54->targetID_Last = -1;
  aisyo_bkup = v13->aisyo_bkup;
  aisyo = v13->para->aisyo;
  v13->scale.y = VisualData_P->scale;
  v13->scale.z = VisualData_P->scale;
  v13->scale.w = VisualData_P->scale;
  v13->disp_offy = VisualData_P->disp_offy;
  ClassCopy(aisyo_bkup, aisyo, 0);
  v58 = GBWK->player;
  aOmoideSkill = p_para->aOmoideSkill;
  p_para->iOmoideSkillCnt = 0;
  *(_OWORD *)aOmoideSkill = 0u;
  *(_OWORD *)&aOmoideSkill[4] = 0u;
  Copy_56180528(v58->spiritSkill, aOmoideSkill, v58->spiritSkill->max_length, 0);
  p_para->iOmoideSkillCnt = v58->spiritCnt;
LABEL_69:
  bulletno = player->bulletno;
  wk->hittargetID = -1;
  wk->equipbullet = bulletno;
  wk->equipbulletbk = bulletno;
  if (!(u32)v60)
  wk->hgun_num = sBtlGetGun_Num();
  v65 = wk;
  v67 = wk;
  v67->menutype = 0;
  v67->stock_num = 0;
  v69 = 0;
  v70 = GBWK->player;
  mag = v70->mag;
  maxmag = v70->maxmag;
  LOWORD(v70) = v70->swordno;
  v65->mag = mag;
  v67->magMax = maxmag;
  v67->equipsord = (s16)v70;
  v67->equipgun = 1;
  stock_id = player->stock_id;
  do
  {
    v78 = stock_id[v69];
    devilid = v78->devilid;
    if (devilid && (v78->flag & 1) != 0)
    {
      devilid = player->stock_id[v69]->devilid;
      ++wk->stock_num;
      DevilData = sBtlGetDevilData(devilid, -1);
      stock_id = player->stock_id;
      LODWORD(DevilData) = DevilData->minorno;
      v75 = wk;
      v76 = (s64)v75->stock_id + 4 * v69;
      v77 = (s64)v75->stock_buffer + 4 * v69;
      *(u32 *)(v76 + 32) = stock_id[v69]->devilid;
      *(u32 *)(v77 + 32) = (u32)DevilData;
    }
    ++v69;
  }
  while (v69 != 32);
  v82 = wk;
  huuma_devilID = v82->huuma_devilID;
  huuma_devilID[0] = -1;
  huuma_devilID[1] = -1;
  huuma_devilID[2] = -1;
  huuma_devilID[3] = -1;
  huuma_devilID[4] = -1;
  huuma_devilID[5] = -1;
  huuma_devilID[6] = -1;
  huuma_devilID[7] = -1;
  huuma_devilID[8] = -1;
  huuma_devilID[9] = -1;
  huuma_devilID[10] = -1;
  huuma_devilID[11] = -1;
  v82->huuma_getUnit = 0;
  wk->member_num = 0;
  datDlcNoneCheck();
  v88 = wk;
  if (wk->battlemode != 3)
  {
    if (!wk->battlemode)
    {
      v88 = wk;
      stack_p = player->stack_p;
      summonindex = v88->summonindex;
      summonindex_menu = v88->summonindex_menu;
      v92 = stack_p[0];
      summonindex[0] = stack_p[0];
      LODWORD(stack_p) = stack_p[1];
      summonindex[1] = (s16)stack_p;
      summonindex_menu[0] = v92;
      summonindex_menu[1] = (s32)stack_p;
    }
    return 1;
  }
  LODWORD(m_Items) = main_data->stock_id;
  if ((m_Items & 0x80000000) == 0)
  {
    LOWORD(m_Items) = main_data->stock_id;
    v97 = wk;
    if (v97->stock_num > (s16)m_Items)
      goto LABEL_125;
  }
  m_Items = player->stack_p;
  goto LABEL_131;
LABEL_125:
  goto LABEL_132;
LABEL_131:
  v97 = wk;
  LOWORD(m_Items) = *(u16 *)m_Items;
LABEL_132:
  v97->summonindex[0] = m_Items;
  v100 = wk;
  v101 = v100->summonindex;
  v101[1] = -1;
  v102 = v100->summonindex_menu;
  v103 = v101[0];
  v102[0] = v103;
  v102[1] = -1;
  if (v100->stock_num >= 1)
  {
    v104 = player->stock_id;
    v105 = v103;
    if ((v104[(s16)v103]->flag & 1) == 0)
      return 1;
    v105 = wk->summonindex[0];
    v126.x = 0.0;
    v126.y = 0.0;
    v126.z = 0.0;
    v126.w = 0.0;
    sBtlSetSummon_Unit(sBtlUnit, v105, 0, 0, v126, 1, 0);
    v107 = wk;
    p_stock_mask = &v107->stock_mask;
    v109 = v107->summonindex[0];
    sBtlSetBit(p_stock_mask, v109);
    v111 = wk;
    v112 = v111->UnitMng;
    v113 = v111->aRedGuage[1];
    v114 = (u32)v111->summonID[v111->summonindex[0]];
    sBtlInitRedGg(v113, v112->pUnitL[v114]->pUnit->para->now->hp);
    wk->talkwk->mode = 1;
    Nakama = sBtlGetNakama(0);
    Nakama->actaiwk->status = Nakama->actaiwk->status & 0xFFFFFE1E | 0xC0;
    Nakama->status &= 0xFFFFFFF9;
    ListID = Nakama->ListID;
    v119 = wk;
    status = v119->status;
    v119->unitpadID = ListID;
    v119->playerID = ListID;
    v119->status = status & 0xFBFFFFFD | 0x4000000;
    Nakama->vstatus |= 0x4000u;
  }
  return 1;
}

// 0x201d960
void UnitSetPlayerSprit(SBTLUNIT_WORK *_playerUnit) {
  sdatPlayerUnitWork_t *player;
  sdatUnitWork_t *para;
  SKLID *aOmoideSkill;

  player = GBWK->player;
  para = playerUnit->para;
  aOmoideSkill = para->aOmoideSkill;
  para->iOmoideSkillCnt = 0;
  *(_OWORD *)aOmoideSkill = 0u;
  *(_OWORD *)&aOmoideSkill[4] = 0u;
  Copy_56180528(player->spiritSkill, aOmoideSkill, player->spiritSkill->max_length, 0);
  playerUnit->para->iOmoideSkillCnt = player->spiritCnt;
}

// 0x200b990
SBTLUNIT_WORK *sBtlGetPlayer_HitTarget(void) {
  s32 hittargetID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  SBATTLE_WORK *v10;
  SBTLACTION_WORK *actwk;
  SBTLACTAI_WORK *actaiwk;
  u32 status;
  s32 mode;
  SBATTLE_WORK *v19;
  u32 v20;

  hittargetID = wk->hittargetID;
  if (hittargetID == -1)
    return 0;
  UnitMng = wk->UnitMng;
  if (hittargetID < 0)
    return 0;
  v10 = wk;
  if (!v10)
    return 0;
  if (!wk->UnitMng)
    return 0;
  if (UnitMng->number <= hittargetID)
    return 0;
  pUnit = UnitMng->pUnitL[hittargetID]->pUnit;
  if (!pUnit)
    return pUnit;
  actwk = pUnit->actwk;
  if (!actwk)
    return 0;
  actaiwk = pUnit->actaiwk;
  if (!actaiwk)
    return 0;
  status = actwk->status;
  if (status == 10 || (pUnit->status & 0x5000) != 0)
    return 0;
  if (status == 11 || status == 14)
    return 0;
  mode = actaiwk->mode;
  if (status == 30 || mode == 9)
    return 0;
  if (status == 40 || pUnit->mode < 5)
    return 0;
  v19 = wk;
  v19->hittargetID = pUnit->ListID;
  if ((pUnit->side & 2) == 0)
  {
    v19 = wk;
    v19->hittargetID = -1;
    return 0;
  }
  v20 = pUnit->status;
  if ((v20 & 0x800) == 0)
    return pUnit;
  if ((v20 & 0x8000) != 0)
    return 0;
  return pUnit;
}

// 0x201d830
bool sBtlIsDeadBgn(SBTLUNIT_WORK *wk) {
  u32 status;

  status = wk->actwk->status;
  if ((wk->side & 2) != 0 && status == 9)
  {
    if ((wk->hstatus & 0x10) != 0)
      return 0;
  }
  else if (status == 10)
  {
    return 1;
  }
  return wk->para->now->hp < 1;
}

// 0x201da00
bool sBtlIsDeadBgn_2(SBTLUNIT_WORK *wk) {
  if ((wk->side & 2) != 0 && wk->actwk->status == 9 && (wk->hstatus & 0x10) != 0)
  {
    if (sBtlCheckSetsuma())
    {
      if (sBtlCheckSetsumaEnd())
        return 0;
      return wk->actwk->status == 10 || wk->para->now->hp < 1;
    }
    return 0;
  }
  return wk->actwk->status == 10 || wk->para->now->hp < 1;
}

// 0x201db00
void sBtlSetRunAway(SBTLUNIT_WORK *wk) {
  s32 vstatus;

  sBtlSetMotion(wk, 7, 0, 0, 0);
  vstatus = wk->vstatus;
  if ((vstatus & 2) == 0)
  {
    wk->vstatus = vstatus | 2;
    *(u32 *)&wk->fade_sttime = 0;
    *(u64 *)&wk->fadepara = 4;
  }
  wk->flg |= 1u;
  wk->hstatus |= 8u;
}

// 0x201dbb0
bool sBtlSetReturnStock_Enemy(SBTLUNIT_WORK *wk) {
  bool v5;
  f32 x;
  f32 y;
  SBTLEFF_LISTWORK *effList;
  f32 w;
  f32 z;
  int8x8_t v13;
  sdfVector4_t v15;

  v5 = sBtlCheckUnit_Exec();
  if (!v5)
    return v5;
  if (wk->actwk->status != 10 && (wk->vstatus & 0x40000000) == 0)
  {
    sBtlSetMotion(wk, 7, 0, 0, 0);
    x = wk->pos.x;
    y = wk->pos.y;
    effList = wk->effList;
    z = wk->pos.z;
    w = wk->pos.w;
    v15.x = x;
    v15.y = y;
    v15.z = z;
    v15.w = w;
    sBtlCreateEff(effList, wk, 4, 0, v15, 0x80808080, 0, 1.0, 0);
    v13.n64_u64[0] = *(u64 *)&wk->vstatus;
    wk->status |= 0x4001u;
    wk->flg |= 2u;
    *(int8x8_t *)&wk->vstatus = vorr_s8(v13, (int8x8_t)0x840000000LL);
  }
  return v5;
}

// 0x201dd50
void sBtlBgnWait(SBTLUNIT_WORK *wk) {
  SBTLEFF_LISTWORK *effList;
  SBTLDMG_HITLISTWORK *hitList;
  SBATTLE_WORK *v8;

  effList = wk->effList;
  sBtlForceReset(effList, wk);
  hitList = wk->hitList;
  sBtlClearHitC(hitList, wk);
  sBtlResetAAI(wk);
  sBtlResetMode(wk);
  wk->aiwk->mode = 12;
  ResetAction(wk);
  wk->aiwk->bWait = 1;
  if (sBtlGetPChara() == wk)
  {
    v8 = wk;
    v8->mode = 1;
    wk->actwk->status = 15;
    v8->sord_st = 4;
    wk->getMag = 0;
  }
  else
  {
    wk->getMag = 0;
  }
}

// 0x201df30
void sBtlEndWait(SBTLUNIT_WORK *wk) {
  SBTLAI_WORK *aiwk;

  aiwk = wk->aiwk;
  if (aiwk)
    aiwk->bWait = 0;
}

// 0x201df40
void sBtlBgnWaitALL(SBTLUNIT_WORK *wk) {
  s64 v3;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  bool v7;

  v3 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v3 >= UnitMng->number)
      break;
    UnitMng = wk->UnitMng;
    pUnit = UnitMng->pUnitL[v3]->pUnit;
    if (pUnit)
      v7 = pUnit == wk;
    else
      v7 = 1;
    if (!v7)
    {
      sBtlBgnWait(pUnit);
    }
    ++v3;
  }
}

// 0x201e040
void sBtlBgnWait_TimeStopSkill(SBTLUNIT_WORK *wk, s32 flg) {
  SBTLEFF_LISTWORK *effList;
  SBTLDMG_HITLISTWORK *hitList;
  u32 status;
  sdatUnitWork_t *para;
  SBATTLE_WORK *v14;

  effList = wk->effList;
  sBtlForceReset(effList, wk);
  hitList = wk->hitList;
  sBtlClearHitC(hitList, wk);
  sBtlResetAAI(wk);
  sBtlResetMode(wk);
  wk->aiwk->mode = 12;
  if ((~wk->side & 0x81) == 0)
  {
    status = wk->status;
    ResetAction(wk);
    if ((status & 0x100) == 0)
    {
      wk->aiwk->bWait = 1;
      if (flg)
        goto LABEL_22;
      goto LABEL_19;
    }
    wk->status |= 0x100u;
    wk->aiwk->bWait = 1;
    if (sBtlGetPChara() != wk)
      goto LABEL_23;
    goto LABEL_26;
  }
  ResetAction(wk);
  wk->aiwk->bWait = 1;
  if (!flg)
  {
LABEL_19:
    sBtlSetMotion(wk, 0, 0, 0, 0);
  }
LABEL_22:
  if (sBtlGetPChara() != wk)
  {
LABEL_23:
    wk->getMag = 0;
    return;
  }
LABEL_26:
  para = wk->para;
  if (sBtlGetBadStatus(wk->para) == 12)
    goto LABEL_23;
  v14 = wk;
  v14->mode = 1;
  wk->actwk->status = 15;
  v14->sord_st = 4;
  wk->getMag = 0;
}

// 0x201e330
void sBtlBgnWaitALL_TimeStopSkill(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wk2) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  bool v9;
  sdatUnitWork_t *para;
  u32 BadStatus;
  SBTLACTION_WORK *actwk;
  SBTLACTAI_WORK *actaiwk;
  u32 status;
  bool v16;
  s32 mode;
  bool v21;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    v9 = pUnit == wk || pUnit == wk2;
    if (v9)
    {
      sBtlBgnWait_TimeStopSkill(pUnit, 1);
      pUnit->damagecnt = 0;
    }
    else
    {
      sBtlBgnWait_TimeStopSkill(pUnit, 0);
      pUnit->damagecnt = 0;
      if (pUnit != sBtlGetPChara())
      {
        para = pUnit->para;
        BadStatus = sBtlGetBadStatus(para);
        actwk = pUnit->actwk;
        if (!actwk)
          continue;
        actaiwk = pUnit->actaiwk;
        if (actaiwk)
        {
          status = actwk->status;
          if (status != 10)
          {
            v16 = (pUnit->status & 0x5000) != 0 || status == 11;
            if (!v16 && status != 14)
            {
              mode = actaiwk->mode;
              if (status != 30 && mode != 9 && pUnit->mode >= 5 && status != 40)
              {
                v21 = BadStatus > 0x11 || ((1 << BadStatus) & 0x21040) == 0;
                if (v21 && (pUnit->hstatus & 0x10) == 0 && pUnit->para->now->hp >= 1)
                {
                  if ((pUnit->side & 2) != 0)
                  {
                    sBtlZakoWarpReset(pUnit);
                  }
                  sBtlSetAction(pUnit, 1, 0);
                  pUnit->actwk->use_skillid = 0;
                  pUnit->aiwk->mode = 12;
                  pUnit->actaiwk->stat = 1;
                }
              }
            }
          }
        }
      }
    }
  }
}

// 0x201e600
void sBtlEndWaitALL(SBTLUNIT_WORK *wk, s32 after_waza) {
  s64 v6;
  sBtlAction **v7;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  bool v11;
  SBTLAI_WORK *aiwk;
  SBATTLE_WORK *v14;
  SBTLACTION_WORK *actwk;
  SBTLACTAI_WORK *actaiwk;
  sBtlAction **v17;
  s32 bk_action_actaiwk_cmpframe;
  SBTLAI_WORK *v19;
  s32 bk_cmbret_mot_setmotionno;
  s32 bk_cmbret_mot_bframe;
  s32 bk_cmbret_mot_aframe;
  s32 bk_cmbret_mot_flg;
  sBtlAction *v25;
  bool v26;
  s32 v27;

  v6 = 0;
  v7 = &sBtlAction;
  v27 = after_waza;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v6 >= UnitMng->number)
      break;
    UnitMng = wk->UnitMng;
    pUnit = UnitMng->pUnitL[v6]->pUnit;
    if (pUnit)
      v11 = pUnit == wk;
    else
      v11 = 1;
    if (v11)
      goto LABEL_6;
    aiwk = pUnit->aiwk;
    if (aiwk)
      aiwk->bWait = 0;
    v14 = wk;
    if (v14->sklProc->bRun)
      goto LABEL_30;
    if (v14->cmbSkl->bRun)
      goto LABEL_30;
    goto LABEL_9000;
    if (wk->cmbSkl->bRun)
    {
LABEL_30:
      pUnit->status &= ~0x10u;
      if ((pUnit->side & 2) == 0)
        goto LABEL_6;
      goto LABEL_34;
    }
LABEL_9000:
    if ((pUnit->side & 2) == 0)
      goto LABEL_6;
LABEL_34:
    if (pUnit->bk_action_use)
    {
      actwk = pUnit->actwk;
      pUnit->bk_action_use = 0;
      if (actwk->status != 10)
      {
        actaiwk = pUnit->actaiwk;
        v17 = v7;
        actaiwk->stat = pUnit->bk_action_actaiwk_stat;
        bk_action_actaiwk_cmpframe = pUnit->bk_action_actaiwk_cmpframe;
        v19 = pUnit->aiwk;
        actaiwk->mode = pUnit->bk_action_actaiwk_mode;
        actaiwk->cmpframe = bk_action_actaiwk_cmpframe;
        v19->stat = pUnit->bk_action_aiwk_stat;
        LODWORD(actaiwk) = pUnit->bk_action_status;
        v19->mode = pUnit->bk_action_aiwk_mode;
        actwk->status = (u32)actaiwk;
        actwk->framecnt = 0;
        *(u64 *)&actwk->framecntB = 0;
        pUnit->next_motion_not_hokan = 0;
        actwk->use_skillid = pUnit->bk_action_actwk_use_skillid;
        bk_cmbret_mot_setmotionno = pUnit->bk_cmbret_mot_setmotionno;
        bk_cmbret_mot_bframe = pUnit->bk_cmbret_mot_bframe;
        bk_cmbret_mot_aframe = pUnit->bk_cmbret_mot_aframe;
        bk_cmbret_mot_flg = pUnit->bk_cmbret_mot_flg;
        sBtlSetMotion(pUnit, bk_cmbret_mot_setmotionno, bk_cmbret_mot_bframe, bk_cmbret_mot_aframe, bk_cmbret_mot_flg);
        v7 = v17;
        after_waza = v27;
        pUnit->bk_cmbret_mot_Locked = 0;
      }
      pUnit->status &= ~0x20u;
    }
    if (after_waza == 2)
    {
      v25 = *v7;
      v26 = 1;
LABEL_5:
      sBtlEnemyPop(pUnit, v26);
      goto LABEL_6;
    }
    if (after_waza == 1)
    {
      v25 = *v7;
      v26 = 0;
      goto LABEL_5;
    }
LABEL_6:
    ++v6;
  }
}

// 0x200a3e0
SKLID sBtlChkHaveMemSkl(sdatUnitWork_t *pUnit, AUTO arg) {
  s32 AutoSkill_ID;
  s16 autost_cnt2;
  s32 v8;
  s32 v9;
  s16 v10;
  s16 v11;
  s32 v12;
  s32 v13;
  s16 v14;
  s16 v15;
  s32 v16;
  s32 v17;
  s16 v18;
  s16 v19;
  s32 v20;
  s32 v21;
  s16 v22;
  s16 v23;
  s32 v24;
  s32 v25;
  s16 v26;
  s16 v27;
  s32 v28;
  s32 v29;
  s16 v30;
  s16 v31;
  s32 v32;
  s32 v33;
  s16 v34;
  s16 v35;
  s16 para2[2];
  s16 para1[2];

  para1[0] = 0;
  para2[0] = 0;
  if (!pUnit)
    return 0;
  *(u32 *)&pUnit->autost_cnt = 0;
  AutoSkill_ID = sBtlGetAutoSkill_ID(pUnit, 0);
  if (AutoSkill_ID)
  {
    if (sBtlGetAutoSkillPara(AutoSkill_ID, para1, para2) != arg)
    {
      AutoSkill_ID = 0;
      goto LABEL_13;
    }
    autost_cnt2 = pUnit->autost_cnt2;
    pUnit->autost_cnt += para1[0];
    pUnit->autost_cnt2 = para2[0] + autost_cnt2;
  }
LABEL_13:
  v8 = sBtlGetAutoSkill_ID(pUnit, 1);
  if (v8)
  {
    v9 = v8;
    if (sBtlGetAutoSkillPara(v9, para1, para2) == arg)
    {
      AutoSkill_ID = v9;
      v10 = pUnit->autost_cnt2;
      v11 = para2[0];
      pUnit->autost_cnt += para1[0];
      pUnit->autost_cnt2 = v11 + v10;
    }
  }
  v12 = sBtlGetAutoSkill_ID(pUnit, 2);
  if (v12)
  {
    v13 = v12;
    if (sBtlGetAutoSkillPara(v13, para1, para2) == arg)
    {
      AutoSkill_ID = v13;
      v14 = pUnit->autost_cnt2;
      v15 = para2[0];
      pUnit->autost_cnt += para1[0];
      pUnit->autost_cnt2 = v15 + v14;
    }
  }
  v16 = sBtlGetAutoSkill_ID(pUnit, 3);
  if (v16)
  {
    v17 = v16;
    if (sBtlGetAutoSkillPara(v17, para1, para2) == arg)
    {
      AutoSkill_ID = v17;
      v18 = pUnit->autost_cnt2;
      v19 = para2[0];
      pUnit->autost_cnt += para1[0];
      pUnit->autost_cnt2 = v19 + v18;
    }
  }
  v20 = sBtlGetAutoSkill_ID(pUnit, 4);
  if (v20)
  {
    v21 = v20;
    if (sBtlGetAutoSkillPara(v21, para1, para2) == arg)
    {
      AutoSkill_ID = v21;
      v22 = pUnit->autost_cnt2;
      v23 = para2[0];
      pUnit->autost_cnt += para1[0];
      pUnit->autost_cnt2 = v23 + v22;
    }
  }
  v24 = sBtlGetAutoSkill_ID(pUnit, 5);
  if (v24)
  {
    v25 = v24;
    if (sBtlGetAutoSkillPara(v25, para1, para2) == arg)
    {
      AutoSkill_ID = v25;
      v26 = pUnit->autost_cnt2;
      v27 = para2[0];
      pUnit->autost_cnt += para1[0];
      pUnit->autost_cnt2 = v27 + v26;
    }
  }
  v28 = sBtlGetAutoSkill_ID(pUnit, 6);
  if (v28)
  {
    v29 = v28;
    if (sBtlGetAutoSkillPara(v29, para1, para2) == arg)
    {
      AutoSkill_ID = v29;
      v30 = pUnit->autost_cnt2;
      v31 = para2[0];
      pUnit->autost_cnt += para1[0];
      pUnit->autost_cnt2 = v31 + v30;
    }
  }
  v32 = sBtlGetAutoSkill_ID(pUnit, 7);
  if (v32)
  {
    v33 = v32;
    if (sBtlGetAutoSkillPara(v33, para1, para2) == arg)
    {
      AutoSkill_ID = v33;
      v34 = pUnit->autost_cnt2;
      v35 = para2[0];
      pUnit->autost_cnt += para1[0];
      pUnit->autost_cnt2 = v35 + v34;
    }
  }
  return AutoSkill_ID;
}

// 0x201e900
s32 sBtlChkHaveMemSklParty(s32 arg) {
  s64 v4;
  s32 v5;
  bool v6;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  sdatUnitWork_t *para;
  s16 *p_autost_cnt;
  s32 v12;
  s32 AutoSkillPara;
  sdatUnitWork_t *v14;
  s32 v15;
  s32 v16;
  sdatUnitWork_t *v17;
  s32 v18;
  s32 v19;
  sdatUnitWork_t *v20;
  s32 v21;
  s32 v22;
  sdatUnitWork_t *v23;
  s32 v24;
  s32 v25;
  sdatUnitWork_t *v26;
  s32 v27;
  s32 v28;
  sdatUnitWork_t *v29;
  s32 v30;
  s32 v31;
  sdatUnitWork_t *v32;

  v4 = 0;
  v5 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v4 >= UnitMng->number)
      return v5;
    pUnit = UnitMng->pUnitL[v4]->pUnit;
    if (pUnit)
    {
      if ((pUnit->side & 1) != 0)
      {
        para = pUnit->para;
        *(u32 *)&para->autost_cnt = 0;
        p_autost_cnt = &para->autost_cnt;
        v12 = *(u32 *)(*(u64 *)(p_autost_cnt + 15) + 32);
        AutoSkillPara = sBtlGetAutoSkillPara(v12, p_autost_cnt, p_autost_cnt + 1);
        v14 = pUnit->para;
        if (AutoSkillPara != arg)
          v12 = v5;
        v15 = v14->aOmoideSkill[1];
        v16 = sBtlGetAutoSkillPara(v15, &v14->autost_cnt, &v14->autost_cnt2);
        v17 = pUnit->para;
        if (v16 == arg)
          v12 = v15;
        v18 = v17->aOmoideSkill[2];
        v19 = sBtlGetAutoSkillPara(v18, &v17->autost_cnt, &v17->autost_cnt2);
        v20 = pUnit->para;
        if (v19 == arg)
          v12 = v18;
        v21 = v20->aOmoideSkill[3];
        v22 = sBtlGetAutoSkillPara(v21, &v20->autost_cnt, &v20->autost_cnt2);
        v23 = pUnit->para;
        if (v22 == arg)
          v12 = v21;
        v24 = v23->aOmoideSkill[4];
        v25 = sBtlGetAutoSkillPara(v24, &v23->autost_cnt, &v23->autost_cnt2);
        v26 = pUnit->para;
        if (v25 == arg)
          v12 = v24;
        v27 = v26->aOmoideSkill[5];
        v28 = sBtlGetAutoSkillPara(v27, &v26->autost_cnt, &v26->autost_cnt2);
        v29 = pUnit->para;
        if (v28 == arg)
          v12 = v27;
        v30 = v29->aOmoideSkill[6];
        v31 = sBtlGetAutoSkillPara(v30, &v29->autost_cnt, &v29->autost_cnt2);
        v32 = pUnit->para;
        if (v31 == arg)
          v12 = v30;
        v5 = v32->aOmoideSkill[7];
        v6 = sBtlGetAutoSkillPara(v5, &v32->autost_cnt, &v32->autost_cnt2) == arg;
        if (!v6)
          v5 = v12;
      }
    }
    ++v4;
  }
}

// 0x201ebe0
f32 sBtlGetKajaParamEx(SBTLUNIT_WORK *wk, SBTLSKL_KAJA kajatype, s32 *pCount) {
  f32 result;
  SBTLSKL_KAJA_WORK *v5;
  SBTLSKL_KAJA_WORK *v6;
  f32 m_fPara;
  s32 v8;
  SBTLSKL_KAJA_WORK *v9;

  result = 0.0;
  *pCount = 0;
  if (wk && (u32)kajatype <= 2)
  {
    v5 = wk->wkKaja[kajatype];
    v6 = v5[0];
    if (v6->m_cnt)
    {
      m_fPara = v6->m_fPara;
      v8 = 1;
      result = m_fPara + 0.0;
      v9 = v5[1];
      if (!v9->m_cnt)
      {
LABEL_6:
        *pCount = v8;
        return result;
      }
    }
    else
    {
      v8 = 0;
      v9 = v5[1];
      if (!v9->m_cnt)
        goto LABEL_6;
    }
    ++v8;
    result = result + v9->m_fPara;
    goto LABEL_6;
  }
  return result;
}

// 0x201ec50
f32 sBtlGetKajaParam(SBTLUNIT_WORK *wk, SBTLSKL_KAJA kajatype) {
  f32 result;
  SBTLSKL_KAJA_WORK *v7;
  SBTLSKL_KAJA_WORK *v8;
  SBTLSKL_KAJA_WORK *v9;

  result = 0.0;
  if (!wk)
    return result;
  if ((u32)kajatype <= 2)
  {
    v7 = wk->wkKaja[kajatype];
    v8 = v7[0];
    if (v8->m_cnt)
      result = v8->m_fPara + 0.0;
    v9 = v7[1];
    if (v9->m_cnt)
      return result + v9->m_fPara;
  }
  return result;
}

// 0x201ed20
u32 sBtlCheckKajaAnyEx(SBTLUNIT_WORK *wk, s32 *pCount) {
  SBTLSKL_KAJA_WORK *v6;
  SBTLSKL_KAJA_WORK *v7;
  f32 m_fPara;
  s32 v9;
  f32 v10;
  SBTLSKL_KAJA_WORK *v11;
  _BOOL4 v12;
  SBTLSKL_KAJA_WORK *v13;
  SBTLSKL_KAJA_WORK *v14;
  f32 v15;
  s32 v16;
  f32 v17;
  SBTLSKL_KAJA_WORK *v18;
  u32 v19;
  SBTLSKL_KAJA_WORK *v20;
  SBTLSKL_KAJA_WORK *v21;
  f32 v22;
  s32 v23;
  f32 v24;
  SBTLSKL_KAJA_WORK *v25;
  s32 v26;
  f32 v44;

  if (!wk)
  {
    v26 = 0;
    v19 = 0;
    goto LABEL_49;
  }
  v6 = wk->wkKaja[0];
  v7 = v6[0];
  if (v7->m_cnt)
  {
    m_fPara = v7->m_fPara;
    v9 = 1;
    v10 = m_fPara + 0.0;
    v11 = v6[1];
    if (!v11->m_cnt)
      goto LABEL_8;
  }
  else
  {
    v9 = 0;
    v10 = 0.0;
    v11 = v6[1];
    if (!v11->m_cnt)
    {
LABEL_8:
      v12 = v10 > 0.0;
      if (v10 <= 0.0)
        v9 = 0;
      v13 = wk->wkKaja[1];
      v14 = v13[0];
      if (v14->m_cnt)
      {
        v15 = v14->m_fPara;
        v16 = 1;
        v17 = v15 + 0.0;
        v18 = v13[1];
        if (!v18->m_cnt)
          goto LABEL_13;
      }
      else
      {
        v16 = 0;
        v17 = 0.0;
        v18 = v13[1];
        if (!v18->m_cnt)
        {
LABEL_13:
          if (v17 <= 0.0)
            v19 = v12;
          else
            v19 = v12 | 2;
          if (v17 <= 0.0)
            v16 = 0;
          v20 = wk->wkKaja[2];
          v21 = v20[0];
          if (v21->m_cnt)
          {
            v22 = v21->m_fPara;
            v23 = 1;
            v24 = v22 + 0.0;
            v25 = v20[1];
            if (!v25->m_cnt)
              goto LABEL_21;
          }
          else
          {
            v23 = 0;
            v24 = 0.0;
            v25 = v20[1];
            if (!v25->m_cnt)
            {
LABEL_21:
              v26 = v9 + v16;
              if (v24 <= 0.0)
                goto LABEL_49;
              goto LABEL_48;
            }
          }
          ++v23;
          v24 = v24 + v25->m_fPara;
          goto LABEL_21;
        }
      }
      ++v16;
      v17 = v17 + v18->m_fPara;
      goto LABEL_13;
    }
  }
  ++v9;
  v10 = v10 + v11->m_fPara;
  goto LABEL_8;
  if (v44 > 0.0)
  {
LABEL_48:
    v19 |= 4u;
    v26 += v23;
  }
LABEL_49:
  *pCount = v26;
  return v19;
}

// 0x201f070
u32 sBtlCheckKajaAny(SBTLUNIT_WORK *wk) {
  s32 pCount;

  return sBtlCheckKajaAnyEx(wk, &pCount);
}

// 0x201f0e0
s32 sBtlCheckEnableUseKaja(SBTLUNIT_WORK *wk, SKLID skillid) {
  SBTLSKILLP_TBL *Skilltbl;
  tagSBTLSKL_AURA_WORK *wkAura;
  void *wkBarrier;
  s32 auracnt;
  s32 v10;
  s32 v11;
  bool v12;
  s32 v13;
  s32 v14;
  s32 v15;
  Il2CppObject *Item;
  s32 v17;
  u32 flg;
  SBTLSKILLP_TBL *v20;
  s32 v21;
  SBTLSKL_KAJA_WORK *v22;
  SBTLSKL_KAJA_WORK *v23;
  SBTLSKL_KAJA_WORK *v24;
  s32 pCount;

  Skilltbl = sBtlGetSkilltbl(skillid);
  if (!Skilltbl)
    return -1;
  pCount = 0;
  if (skillid == 134 || skillid == 1169 || skillid == 1124)
  {
    sBtlCheckKajaAnyEx(wk, &pCount);
    wkAura = wk->wkAura;
    wkBarrier = wk->wkBarrier;
    auracnt = wkAura[0]->auracnt;
    v10 = wkAura[1]->auracnt;
    v11 = wkAura[2]->auracnt;
    v12 = auracnt == 0;
    v13 = pCount;
    if (!v12)
      v13 = pCount + 1;
    if (v10)
      ++v13;
    if (v11)
      v14 = v13 + 1;
    else
      v14 = v13;
    if (wkBarrier->_size >= 1)
    {
      v15 = 0;
      do
      {
        Item = _get_Item(wkBarrier, v15++);
        v12 = HIDWORD(Item[1].klass) == 0;
        wkBarrier = wk->wkBarrier;
        if (!v12)
          ++v14;
      }
      while (v15 < wkBarrier->_size);
    }
    if (wk->wkKarn[0]->m_cnt)
      v17 = v14 + 1;
    else
      v17 = v14;
    return v17 > 0;
  }
  flg = Skilltbl->flg;
  v20 = Skilltbl;
  if ((flg & 0x400000) == 0)
    return -1;
  if ((flg & 0x1000000) != 0)
  {
    v22 = wk->wkKaja[0];
    v21 = sBtlCheckRegistKaja(v22, v20) >= 0;
    if ((v20->flg & 0x2000000) == 0)
      goto LABEL_36;
    goto LABEL_33;
  }
  v21 = 0;
  if ((Skilltbl->flg & 0x2000000) != 0)
  {
LABEL_33:
    v23 = wk->wkKaja[1];
    v21 += sBtlCheckRegistKaja(v23, v20) >= 0;
  }
LABEL_36:
  if ((v20->flg & 0x4000000) != 0)
  {
    v24 = wk->wkKaja[2];
    v21 += sBtlCheckRegistKaja(v24, v20) >= 0;
  }
  return v21 != 0;
}

// 0x201f350
s32 sBtlCheckEnableUseKajaNewAI(SBTLUNIT_WORK *wk, SKLID skillid) {
  SBTLSKILLP_TBL *Skilltbl;
  tagSBTLSKL_AURA_WORK *wkAura;
  void *wkBarrier;
  s32 auracnt;
  s32 v10;
  s32 v11;
  bool v12;
  s32 v13;
  s32 v14;
  s32 v15;
  Il2CppObject *Item;
  s32 v17;
  u32 flg;
  SBTLSKILLP_TBL *v20;
  s32 v21;
  SBTLSKL_KAJA_WORK *v22;
  SBTLSKL_KAJA_WORK *v23;
  SBTLSKL_KAJA_WORK *v24;
  s32 pCount;

  Skilltbl = sBtlGetSkilltbl(skillid);
  if (!Skilltbl)
    return -1;
  pCount = 0;
  if (skillid == 134 || skillid == 1169 || skillid == 1124)
  {
    sBtlCheckKajaAnyEx(wk, &pCount);
    wkAura = wk->wkAura;
    wkBarrier = wk->wkBarrier;
    auracnt = wkAura[0]->auracnt;
    v10 = wkAura[1]->auracnt;
    v11 = wkAura[2]->auracnt;
    v12 = auracnt == 0;
    v13 = pCount;
    if (!v12)
      v13 = pCount + 1;
    if (v10)
      ++v13;
    if (v11)
      v14 = v13 + 1;
    else
      v14 = v13;
    if (wkBarrier->_size >= 1)
    {
      v15 = 0;
      do
      {
        Item = _get_Item(wkBarrier, v15++);
        v12 = HIDWORD(Item[1].klass) == 0;
        wkBarrier = wk->wkBarrier;
        if (!v12)
          ++v14;
      }
      while (v15 < wkBarrier->_size);
    }
    if (wk->wkKarn[0]->m_cnt)
      v17 = v14 + 1;
    else
      v17 = v14;
    return v17 > 0;
  }
  flg = Skilltbl->flg;
  v20 = Skilltbl;
  if ((flg & 0x400000) == 0)
    return -1;
  if ((flg & 0x1000000) != 0)
  {
    v22 = wk->wkKaja[0];
    v21 = sBtlCheckRegistKajaMaxNewAI(v22, v20);
    if ((v20->flg & 0x2000000) == 0)
      goto LABEL_36;
    goto LABEL_33;
  }
  v21 = 0;
  if ((Skilltbl->flg & 0x2000000) != 0)
  {
LABEL_33:
    v23 = wk->wkKaja[1];
    v21 += sBtlCheckRegistKajaMaxNewAI(v23, v20);
  }
LABEL_36:
  if ((v20->flg & 0x4000000) != 0)
  {
    v24 = wk->wkKaja[2];
    v21 += sBtlCheckRegistKajaMaxNewAI(v24, v20);
  }
  return v21 != 0;
}

// 0x201f5c0
s32 sBtlCheckEnableUseKarn(SBTLUNIT_WORK *wk, SKLID skillid) {
  if (skillid == 1129 || skillid == 661)
    return wk->wkKarn[0]->m_cnt == 0;
  else
    return -1;
}

// 0x201f5f0
s32 sBtlCheckEnableUseAura(SBTLUNIT_WORK *wk, SKLID skillid) {
  if ((u32)(skillid - 131) > 2)
    return -1;
  else
    return wk->wkAura[qword_3E64520[skillid - 131]]->auracnt < 1;
}

// 0x201f630
s32 sBtlGetAuraIdx(SKLID skillid) {
  if ((u32)(skillid - 131) > 2)
    return -1;
  else
    return dword_3E64538[skillid - 131];
}

// 0x201f660
s32 sBtlCheckEnableUseSkill(SBTLUNIT_WORK *wk, SKLID skillid) {
  u32 status;
  s32 result;
  s32 v9;
  s32 m_cnt;
  bool v11;

  if (!wk)
    return -1;
  status = wk->actwk->status;
  if (status <= 0xE && ((1 << status) & 0x4C00) != 0)
    return 0;
  if (wk->actaiwk->mode == 9)
    return 0;
  result = 0;
  if (status != 40 && wk->mode >= 5)
  {
    if (sBtlCheckReturn_Unit(wk))
    {
      return 0;
    }
    else
    {
      v9 = sBtlCheckEnableUseKaja(wk, skillid);
      if (skillid == 661 || skillid == 1129)
      {
        m_cnt = wk->wkKarn[0]->m_cnt;
        if (v9)
          v11 = 1;
        else
          v11 = m_cnt == 0;
        result = v11;
        if (m_cnt)
        {
          if (v9 <= 0)
            return 0;
        }
      }
      else
      {
        return v9 != 0;
      }
    }
  }
  return result;
}

// 0x2017d60
void sBtlResetBtlMagicStatus(SBTLUNIT_WORK *wk) {
  void *wkBarrier;
  s32 v4;
  s32 size;
  s32 v6;
  SBTLSKL_KAJA_WORK **wkKaja;
  tagSBTLSKL_KARN_WORK *wkKarn;
  SBTLSKL_KAJA_WORK *v10;
  SBTLSKL_KAJA_WORK *v11;
  SBTLSKL_KAJA_WORK *v12;
  SBTLSKL_KAJA_WORK *v13;
  SBTLSKL_KAJA_WORK *v14;
  SBTLSKL_KAJA_WORK *v15;
  SBTLSKL_KAJA_WORK *v16;
  SBTLSKL_KAJA_WORK *v17;
  SBTLSKL_KAJA_WORK *v18;
  s32 v19;

  if (wk)
  {
    wkBarrier = wk->wkBarrier;
    if (wkBarrier->_size < 1)
    {
      v19 = wkBarrier->_version + 1;
      wkBarrier->_size = 0;
      wkBarrier->_version = v19;
LABEL_12:
      sBtlCheckBattlePara(wk);
      wkKaja = wk->wkKaja;
      wkKarn = wk->wkKarn;
      v10 = wkKaja[0];
      v11 = wkKaja[1];
      v12 = wkKaja[2];
      v14 = v10[0];
      v13 = v10[1];
      v14->m_cnt = 0;
      v13->m_cnt = 0;
      v15 = v11[0];
      v16 = v11[1];
      v15->m_cnt = 0;
      v18 = v12[0];
      v17 = v12[1];
      v16->m_cnt = 0;
      v18->m_cnt = 0;
      v17->m_cnt = 0;
      wkKarn[0]->m_cnt = 0;
      return;
    }
    else
    {
      v4 = 0;
      do
      {
        if (HIDWORD(_get_Item(wkBarrier, v4)[1].klass))
        {
          HIDWORD(_get_Item(wk->wkBarrier, v4)[1].klass) = 0;
          LODWORD(_get_Item(wk->wkBarrier, v4)[1].monitor) = 0;
          HIDWORD(_get_Item(wk->wkBarrier, v4)[1].monitor) = 0;
          LODWORD(_get_Item(wk->wkBarrier, v4)[1].klass) = 0;
        }
        wkBarrier = wk->wkBarrier;
        ++v4;
        size = wkBarrier->_size;
      }
      while (v4 < size);
      v6 = wkBarrier->_version + 1;
      wkBarrier->_size = 0;
      wkBarrier->_version = v6;
      if (size >= 1)
        Clear(wkBarrier->_items, 0, size, 0);
      goto LABEL_12;
    }
    goto LABEL_12;
  }
}

// 0x201f7f0
SBTLUNIT_SIDE sBtlGetBothSide(SBTLUNIT_WORK *wk, SBTLUNIT_SIDE side) {
  sdatUnitWork_t *para;

  if (!wk)
    return 0;
  para = wk->para;
  if (sBtlGetBadStatus(para) == 7)
  {
    if ((side & 1) != 0)
      return 2;
    else
      return ((u32)side >> 1) & 1;
  }
  if ((side & 1) != 0)
    return 1;
  else
    return side & 2;
}

// 0x201f8d0
bool sBtlUnit_CheckSummon_LoadExecOk_sub(void) {
  s64 v2;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  SBTLUNIT_WORK *pUnit;

  v2 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    number = UnitMng->number;
    if (v2 >= number)
      return v2 >= number;
    pUnit = UnitMng->pUnitL[v2]->pUnit;
    if (pUnit)
    {
      if ((pUnit->side & 0x81) == 1)
      {
        if (sBtlSearchReturn_Unit(pUnit))
        {
          pUnit->status |= 0x10u;
          return v2 >= number;
        }
      }
    }
    ++v2;
  }
}

// 0x201fa20
bool sBtlCheckSummon_LoadExecOk(s32 mode) {
  SBTLUNIT_LISTWORK *TargetList_DeadOn;
  s64 count;
  SBTLUNIT_LISTWORK *v5;
  s64 m_Items;
  s64 v9;
  s32 v11;
  s64 j;
  SBTLUNIT_LISTWK *v13;
  SBTLUNIT_WORK *v14;
  SBTLUNIT_WORK *v15;
  s32 number;
  s64 i;
  SBTLUNIT_LISTWK *v18;
  SBTLUNIT_WORK *p_pUnit;
  SBTLUNIT_WORK *pUnit;
  s64 v22;
  SBTLUNIT_LISTWORK *v23;
  SBTLUNIT_LISTWORK *v25;
  s64 v26;
  s64 v27;
  s32 v28;
  s32 v29;
  s64 m;
  SBTLUNIT_LISTWK *v31;
  SBTLUNIT_WORK *v32;
  SBTLUNIT_WORK *v33;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 playerID;
  SBATTLE_WORK *v41;
  SBATTLE_WORK *v44;
  SBTLUNIT_LISTWORK *v45;
  s64 v46;
  s64 k;
  SBTLUNIT_LISTWK *v48;
  SBTLUNIT_WORK *v49;
  SBTLUNIT_WORK *v50;
  SBTLDVLTK_LISTWORK *dvltkList;
  SBATTLE_WORK *v56;
  SBTLUNIT_LISTWORK *v57;
  s64 v58;
  SBTLUNIT_WORK *v59;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v63;
  SBTLUNIT_WORK *v65;
  SBTLUNIT_WORK *v66;
  SBTLEFF_LISTWORK *effList;
  SBTLUNIT_WORK *v69;
  SBTLUNIT_WORK *v70;
  SBTLEFF_LISTWORK *v72;
  bool result;
  SBATTLE_WORK *v78;
  u32 v79;
  SBATTLE_WORK *v81;
  SBTLUNIT_WORK *v82;
  u32 status;
  s64 n;
  SBATTLE_WORK *v87;
  SBTLUNIT_LISTWORK *v88;
  SBTLUNIT_WORK *v89;
  u32 v90;
  bool v91;
  s32 v92;
  SBTLEFF_LISTWORK *v95;
  SBATTLE_WORK *v97;
  SBTLUNIT_WORK *v98;
  s64 v99;
  u32 stock_mask;
  s32 v103;
  SBTLUNIT_WORK *v104;
  SBTLUNIT_WORK *v105;
  u32 v106;
  SBTLUNIT_WORK *v108;
  SBTLUNIT_WORK *v109;
  u32 v115;
  SBTLUNIT_WORK *v118;
  SBTLUNIT_WORK *v119;
  SBTLUNIT_WORK *v121;
  SBTLUNIT_WORK *v122;
  SBTLEFF_LISTWORK *v124;
  SBTLUNIT_WORK *v125;
  SBTLUNIT_WORK *v126;
  SBTLEFF_LISTWORK *v128;

  if (mode == 1)
  {
    TargetList_DeadOn = sBtlCreateTargetList_DeadOn(2);
    count = (u32)TargetList_DeadOn->count;
    v5 = TargetList_DeadOn;
    if ((s32)count < 1)
      goto LABEL_21;
    goto LABEL_9000;
    if ((s32)count < 1)
    {
LABEL_21:
      number = v5->number;
      if (number >= 1)
      {
        for (i = 0; i < number; ++i)
        {
          v18 = v5->pUnitL[i];
          pUnit = v18->pUnit;
          p_pUnit = &v18->pUnit;
          if (pUnit)
          {
            p_pUnit = 0;
            number = v5->number;
          }
        }
      }
      goto LABEL_28;
    }
LABEL_9000:
    m_Items = v5->pUnitL;
    while (1)
    {
      v9 = *(u64 *)(*(u64 *)m_Items + 24);
      if (v9)
      {
        if (*(u32 *)(*(u64 *)(v9 + 904) + 16) == 10)
          break;
      }
      m_Items += 8;
      if (!--count)
        goto LABEL_21;
    }
    *(u32 *)(v9 + 840) |= 0x10u;
    wk->status4 |= 0x700u;
    v11 = v5->number;
    if (v11 >= 1)
    {
      for (j = 0; j < v11; ++j)
      {
        v13 = v5->pUnitL[j];
        v15 = v13->pUnit;
        v14 = &v13->pUnit;
        if (v15)
        {
          v14 = 0;
          v11 = v5->number;
        }
      }
    }
    return 0;
  }
LABEL_28:
  v25 = sBtlCreateTargetList_DeadOn(2);
  v22 = (u32)v25->count;
  v23 = v25;
  if ((s32)v22 < 1)
    goto LABEL_39;
  v26 = v23->pUnitL;
  while (1)
  {
    v27 = *(u64 *)(*(u64 *)v26 + 24);
    if (v27)
    {
      if (*(u32 *)(*(u64 *)(v27 + 904) + 16) == 41)
        break;
    }
    v26 += 8;
    if (!--v22)
      goto LABEL_39;
  }
  v28 = v23->number;
  if (v28 < 1)
    return 0;
  for (k = 0; k < v28; ++k)
  {
    v48 = v23->pUnitL[k];
    v50 = v48->pUnit;
    v49 = &v48->pUnit;
    if (v50)
    {
      v49 = 0;
      v28 = v23->number;
    }
  }
  return 0;
LABEL_39:
  v29 = v23->number;
  if (v29 >= 1)
  {
    for (m = 0; m < v29; ++m)
    {
      v31 = v23->pUnitL[m];
      v33 = v31->pUnit;
      v32 = &v31->pUnit;
      if (v33)
      {
        v32 = 0;
        v29 = v23->number;
      }
    }
  }
  if (step == 1)
  {
    --stepcnt;
    UnitMng = wk->UnitMng;
    playerID = (u32)wk->playerID;
    if ((playerID & 0x80000000) != 0)
    {
LABEL_143:
      v59 = 0;
      if (stepcnt > 0)
        return 0;
      goto LABEL_97;
    }
    v41 = wk;
    if (!v41)
      goto LABEL_143;
    if (!v41->UnitMng)
      goto LABEL_143;
    if (UnitMng->number <= (s32)playerID)
      goto LABEL_143;
    v59 = UnitMng->pUnitL[playerID]->pUnit;
    if (stepcnt <= 0)
    {
LABEL_97:
      if (player_theworld_cng)
      {
        if (v59)
          v59->status &= ~0x10u;
        player_theworld_cng = 0;
      }
      if (nakama0_theworld_cng)
      {
        Nakama = sBtlGetNakama(0);
        if (Nakama)
        {
          Nakama->status &= ~0x10u;
        }
        nakama0_theworld_cng = 0;
      }
      if (nakama1_theworld_cng)
      {
        v63 = sBtlGetNakama(1);
        if (v63)
        {
          v63->status &= ~0x10u;
        }
        nakama1_theworld_cng = 0;
      }
      v65 = sBtlGetNakama(0);
      if (v65)
      {
        v66 = v65;
        effList = wk->effList;
        sBtlForceDelete_ID_SummonFR(effList, v66);
      }
      v69 = sBtlGetNakama(1);
      if (v69)
      {
        v70 = v69;
        v72 = wk->effList;
        sBtlForceDelete_ID_SummonFR(v72, v70);
      }
      step = 0;
      stepcnt = 0;
LABEL_140:
      result = 1;
      v78 = wk;
      v79 = v78->status4 & 0xFFFFFBFF;
LABEL_237:
      v78->status4 = v79;
      return result;
    }
    return 0;
  }
  if (!sBtlCheckUnit_Exec())
  {
LABEL_79:
    stepcnt = 30;
    dvltkList = wk->dvltkList;
    sBtlReleaseDvltk_List(dvltkList, 1u);
    if (IsSceanStop())
    {
      v56 = wk;
      v57 = v56->UnitMng;
      v58 = (u32)v56->playerID;
      if ((v58 & 0x80000000) != 0)
        goto LABEL_155;
      v81 = wk;
      if (v81)
      {
        v81 = wk;
        if (v81->UnitMng && v57->number > (s32)v58)
        {
          v82 = v57->pUnitL[v58]->pUnit;
LABEL_156:
          status = v82->status;
          if ((status & 0x10) == 0)
          {
            status = v82->status;
            v82->status = status | 0x10;
            player_theworld_cng = 1;
          }
          for (n = 0; ; ++n)
          {
            v87 = wk;
            v88 = v87->UnitMng;
            if (n >= v88->number)
              goto LABEL_234;
            v89 = v88->pUnitL[n]->pUnit;
            if (!v89)
              continue;
            v90 = v89->mode;
            v91 = v90 > 9;
            v92 = (1 << v90) & 0x290;
            if (!v91 && v92 != 0)
              break;
LABEL_162:
            ;
          }
          v95 = v87->effList;
          sBtlForceDelete_ID_Return(v95, v89);
          v89->status |= 0x10u;
          goto LABEL_162;
        }
      }
LABEL_155:
      v82 = 0;
      goto LABEL_156;
    }
    goto LABEL_234;
  }
  if (!sBtlUnit_CheckSummon_LoadExecOk_sub())
    goto LABEL_79;
  v44 = wk;
  v45 = v44->UnitMng;
  v46 = (u32)v44->playerID;
  if ((v46 & 0x80000000) != 0)
    goto LABEL_190;
  goto LABEL_182;
  if ((v46 & 0x80000000) != 0)
  {
LABEL_190:
    v98 = 0;
    goto LABEL_191;
  }
LABEL_182:
  v97 = wk;
  if (!v97)
    goto LABEL_190;
  v97 = wk;
  if (!v97->UnitMng || v45->number <= (s32)v46)
    goto LABEL_190;
  v98 = v45->pUnitL[v46]->pUnit;
LABEL_191:
  v99 = 0;
  {
    stock_mask = wk->stock_mask;
LABEL_196:
    if (sBtlCheckBit(stock_mask, v99))
      goto LABEL_200;
LABEL_193:
    if (++v99 == 32)
    {
      v103 = 1;
      v104 = sBtlGetNakama(0);
      if (!v104)
        goto LABEL_215;
      goto LABEL_205;
    }
  }
  stock_mask = wk->stock_mask;
  goto LABEL_196;
LABEL_200:
  if (wk->summonflg[v99] == 2)
    goto LABEL_193;
  v103 = 0;
  v104 = sBtlGetNakama(0);
  if (!v104)
    goto LABEL_215;
LABEL_205:
  v105 = v104;
  if (v104->mode == 5 || (v104->vstatus & 1) != 0)
  {
    if (!IsSceanStop() || (v106 = v105->status, (v106 & 0x10) != 0))
    {
      v103 = 0;
    }
    else
    {
      v106 = v105->status;
      v103 = 0;
      v105->status = v106 | 0x10;
      nakama0_theworld_cng = 1;
    }
  }
LABEL_215:
  v108 = sBtlGetNakama(1);
  if (v108)
  {
    v109 = v108;
    if (v108->mode == 5 || (v108->vstatus & 1) != 0)
    {
      if (IsSceanStop())
      {
        v115 = v109->status;
        if ((v115 & 0x10) == 0)
        {
          v115 = v109->status;
          v109->status = v115 | 0x10;
          nakama1_theworld_cng = 1;
        }
      }
      goto LABEL_234;
    }
  }
  if (!v103)
  {
LABEL_234:
    result = 0;
    v78 = wk;
    v79 = v78->status4 | 0x700;
    goto LABEL_237;
  }
  wk->status4 &= 0xFFFFFCFF;
  if (!stepcnt)
  {
    if (player_theworld_cng)
    {
      if (v98)
        v98->status &= ~0x10u;
      player_theworld_cng = 0;
    }
    if (nakama0_theworld_cng)
    {
      v118 = sBtlGetNakama(0);
      if (v118)
      {
        v118->status &= ~0x10u;
      }
      nakama0_theworld_cng = 0;
    }
    if (nakama1_theworld_cng)
    {
      v119 = sBtlGetNakama(1);
      if (v119)
      {
        v119->status &= ~0x10u;
      }
      nakama1_theworld_cng = 0;
    }
    v121 = sBtlGetNakama(0);
    if (v121)
    {
      v122 = v121;
      v124 = wk->effList;
      sBtlForceDelete_ID_SummonFR(v124, v122);
    }
    v125 = sBtlGetNakama(1);
    if (v125)
    {
      v126 = v125;
      v128 = wk->effList;
      sBtlForceDelete_ID_SummonFR(v128, v126);
    }
    goto LABEL_140;
  }
  step = 1;
  return 0;
}

// 0x2020920
SBTLUNIT_WORK *sBtlGetNakamaUnit(sdatUnitWork_t *a_pUnit) {
  s64 v3;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  sdatUnitWork_t *para;

  if (a_pUnit)
  {
    v3 = 0;
    while (1)
    {
      UnitMng = wk->UnitMng;
      if (v3 >= UnitMng->number)
        return 0;
      pUnit = UnitMng->pUnitL[v3]->pUnit;
      if (pUnit)
      {
        if ((pUnit->side & 1) != 0)
        {
          para = pUnit->para;
          if (para->devilid == a_pUnit->devilid && para->uniq_code == a_pUnit->uniq_code)
          {
            if (pUnit != sBtlGetNakama(0) && pUnit != sBtlGetNakama(1))
              return 0;
            return pUnit;
          }
        }
      }
      ++v3;
    }
  }
  return 0;
}

// 0x2020a70
void GetUnitHelperPos(SBTLUNIT_WORK *wk, sdfVector4_t *_HelperPos) {
  sBtlGetUnitHelperPosSub(wk, HelperPos, 0);
}

// 0x2020ae0
void sBtlGetUnitHelperPosSub(SBTLUNIT_WORK *wk, sdfVector4_t *_HelperPos, s32 markpos_no) {
  evtUnitHandle_t *hEveUnit;
  struct sdfVector4_t pos;

  if ((wk->status & 0x800) == 0)
  {
    hEveUnit = wk->hEveUnit;
    if (hEveUnit)
    {
      if (markpos_no == 1)
      {
        sBtlGetChestPos(wk);
LABEL_22:
        goto LABEL_24;
      }
      else
      {
        sdfModelGetMarkPos(hEveUnit->Model->modelRoot, markpos_no);
        goto LABEL_22;
      }
      goto LABEL_22;
    }
  }
  pos = wk->pos;
  vct_A = pos;
LABEL_24:
  *HelperPos = vct_A;
}

// 0x2020ca0
void sBtlGetUnitTargetPos(SBTLUNIT_WORK *wk, sdfVector4_t *_HelperPos) {
  bool MarkPos;

  MarkPos = sdfModelGetMarkPos(wk->hEveUnit->Model->modelRoot, 1);
  sBtlGetUnitHelperPosSub(wk, HelperPos, MarkPos);
}

// 0x2020d30
void sBtlGetUnitDamagePos(SBTLUNIT_WORK *wk, sdfVector4_t *_HelperPos) {
  bool MarkPos;

  MarkPos = sdfModelGetMarkPos(wk->hEveUnit->Model->modelRoot, 1);
  sBtlGetUnitHelperPosSub(wk, HelperPos, MarkPos);
}

// 0x2020dc0
bool sBtlChkEnemyID(s32 _DevilID) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  SBTLUNIT_WORK *pUnit;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    number = UnitMng->number;
    if (i >= number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 2) != 0 && pUnit->para->devilid == DevilID)
      return i < number;
  }
  return i < number;
}

// 0x2020ec0
SBTLUNIT_WORK *sBtlGetUnitFromDevilID(s32 _DevilID) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 2) != 0 && pUnit->para->devilid == DevilID)
      return pUnit;
  }
  return 0;
}

// 0x2020fd0
SBTLUNIT_WORK *sBtlGetUnitEnemy1_Live(void) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  u32 status;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 2) != 0)
    {
      status = pUnit->actwk->status;
      if (status != 40 && status != 10)
        return pUnit;
    }
  }
  return 0;
}

// 0x20210d0
SBTLUNIT_WORK *sBtlGetUnitEnemy1(void) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 2) != 0)
      return pUnit;
  }
  return 0;
}

// 0x20211c0
void sBtlResetJump_FO_Eve(SBTLUNIT_WORK *wk) {
  dds3Basic_t *pBasic;

  wk->JumpOfsPos.z = 0.0;
  wk->JumpAfterCnt = 0;
  *(u64 *)&wk->JumpOfsPos.x = 0;
  pBasic = wk->pBasic;
  dds3UnitObjectBasicSetJumpOfsPos(pBasic, 0.0, 0.0, 0.0);
}

// 0x2021250
bool sBtlChkBounceUnit(SBTLUNIT_WORK *wk) {
  return (wk->para->devilid & 0xFFFE) != 312;
}

// 0x2021270
void sBtlSetBounce(SBTLUNIT_WORK *wk, f32 _Pow, f32 _AddRndNml, s32 _ReBound) {
  f32 v10;
  f32 ABS;
  u32 v12;
  f32 v13;

  if ((wk->para->devilid & 0xFFFE) == 0x138)
    return;
  wk->Bounce_Spd = Pow;
  wk->Bounce_Cnt = 0;
  wk->Bounce_ReBound = ReBound;
  v10 = (f32)(u32)sub_1905740(100, 0) / 100.0;
  ABS = sBtlGetABS((f32)(Pow * AddRndNml) * v10);
  v12 = sub_1905740(100, 0);
  v13 = -ABS;
  if (v12 >= 0x32)
    v13 = ABS;
  wk->Bounce_Spd = wk->Bounce_Spd + v13;
}

// 0x20213c0
void sBtlSetBounceHitStop(SBTLUNIT_WORK *wk, s32 _WaitFrame, s32 _StopFrame) {
  wk->Bounce_HitStopWait = WaitFrame;
  wk->Bounce_HitStopCnt = StopFrame;
}

// 0x20213d0
bool sBtlChkSceneEnemyLive(void) {
  SBTLUNIT_WORK *Nakama;
  SBTLACTION_WORK *v2;
  SBTLUNIT_WORK *v3;
  SBTLACTION_WORK *v4;
  s64 v5;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v8;
  char v9;
  s64 v10;
  s32 v11;
  SBTLUNIT_LISTWORK *v13;
  SBTLUNIT_WORK *pUnit;
  s32 aiBgnCnt;
  SBTLACTION_WORK *actwk;
  u32 status;
  bool v18;
  s32 v19;
  s32 devilid;
  SBTLACTAI_WORK *actaiwk;
  u32 v22;
  u32 v23;
  s32 v24;
  s64 i;
  SBTLUNIT_LISTWORK *v27;
  SBTLUNIT_WORK *v28;
  u32 v29;

  Nakama = sBtlGetNakama(0);
  if (!Nakama || (Nakama->side & 0x80) != 0 || (v2 = Nakama->actwk, v2->status != 40) || v2->use_skillid != 240)
  {
    v3 = sBtlGetNakama(1);
    if (!v3 || (v3->side & 0x80) != 0 || (v4 = v3->actwk, v4->status != 40) || v4->use_skillid != 240)
    {
      v5 = 0;
      while (1)
      {
        UnitMng = wk->UnitMng;
        if (v5 >= UnitMng->number)
        {
          v10 = 0;
          v9 = 0;
          v11 = 0;
LABEL_26:
          v13 = wk->UnitMng;
          if (v10 >= v13->number)
          {
            v9 &= v11;
            return v9 & 1;
          }
          pUnit = v13->pUnitL[v10]->pUnit;
          if (!pUnit)
            goto LABEL_43;
          if ((pUnit->side & 2) == 0)
            goto LABEL_43;
          aiBgnCnt = wk->aiBgnCnt;
          actwk = pUnit->actwk;
          status = actwk->status;
          if (aiBgnCnt >= 120)
          {
            if (!status)
              goto LABEL_43;
          }
          v18 = status == 11 || status == 14;
          if (v18 || pUnit->actaiwk->mode == 9 || pUnit->mode < 5)
          {
LABEL_43:
            v19 = v11;
            goto LABEL_44;
          }
          devilid = pUnit->para->devilid;
          if (devilid <= 260)
          {
            if (devilid != 137)
            {
              if ((devilid & 0xFFFFFFFE) != 0xA8)
              {
                if ((u32)(devilid - 261) >= 0xFFFFFFFD)
                  goto LABEL_43;
                goto LABEL_74;
              }
              if (status == 10)
                break;
              v11 = 1;
              if ((pUnit->status & 0x4000) == 0)
                goto LABEL_74;
              v19 = 1;
              goto LABEL_44;
            }
          }
          else
          {
            if ((u32)devilid > 0x123)
            {
              if (devilid == 311)
                goto LABEL_43;
              if (pUnit->para->devilid == 314)
              {
                actwk = pUnit->actwk;
                if (!actwk)
                  goto LABEL_43;
                actaiwk = pUnit->actaiwk;
                if (!actaiwk)
                  goto LABEL_43;
                v22 = actwk->status;
                if (v22 == 10 || (pUnit->status & 0x5000) != 0 || v22 == 11 || v22 == 14 || v22 == 30 || actaiwk->mode == 9 || v22 == 40 || pUnit->mode <= 4)
                {
                  goto LABEL_43;
                }
              }
              goto LABEL_74;
            }
            if (devilid != 264)
            {
              if (pUnit->para->devilid == 291)
              {
                if (sBtlChk_BS_MUNAKA_SetsumaNG())
                  goto LABEL_43;
              }
LABEL_74:
              v23 = pUnit->actwk->status;
              if (v23 == 10)
                goto LABEL_43;
              if (v23 == 40)
                goto LABEL_43;
              v24 = (u16)pUnit->para->devilid;
              if ((v24 & 0xFFFE) != 0xA8 && v24 == 314)
              {
                for (i = 0; ; ++i)
                {
                  v27 = wk->UnitMng;
                  if (i >= v27->number)
                    break;
                  v27 = wk->UnitMng;
                  v28 = v27->pUnitL[i]->pUnit;
                  if (v28 && (v28->side & 2) != 0 && v28->para->devilid == 258)
                  {
                    v9 = 0;
                    v29 = v28->actwk->status;
                    if (v29 == 10 || v29 == 40)
                      return v9 & 1;
                    break;
                  }
                }
              }
              v9 = 1;
              v19 = 1;
              if ((v11 & 1) == 0)
                return v9 & 1;
LABEL_44:
              ++v10;
              v11 = v19;
              goto LABEL_26;
            }
          }
          if ((pUnit->status & 0x4004000) != 0)
            break;
          goto LABEL_74;
        }
        v8 = UnitMng->pUnitL[v5]->pUnit;
        if (v8)
        {
          if ((v8->side & 0x83) == 1 && v8->actwk->status == 10 && v8->mode != 6)
            break;
        }
        ++v5;
      }
    }
  }
  v9 = 0;
  return v9 & 1;
}

// 0x2021900
bool sBtlChkNakama_SkillUse_SHINEBA(void) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  SBTLUNIT_WORK *pUnit;
  SBTLACTION_WORK *actwk;
  u32 status;
  bool v8;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    number = UnitMng->number;
    if (i >= number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 0x81) == 1)
    {
      actwk = pUnit->actwk;
      status = actwk->status;
      v8 = status == 40 || status == 18;
      if (v8 && actwk->use_skillid == 240)
        return i < number;
    }
  }
  return i < number;
}
