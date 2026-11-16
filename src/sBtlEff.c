#include "types.h"
#include "ATR.h"
#include "ATRB.h"
#include "BSTF.h"
#include "EFFID.h"
#include "EFFPAC_ST.h"
#include "SBTLEFF_BEDTYPE.h"
#include "SBTLEFF_FLG.h"
#include "SBTLUNIT_SIDE.h"
#include "SKLID.h"
#include "aw_hitlight.h"
#include "aw_hits.h"
#include "aw_summone.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3objectbase.h"
#include "efffilter.h"
#include "effpartslist.h"
#include "effstat.h"
#include "egl.h"
#include "file.h"
#include "kernel.h"
#include "mdl.h"
#include "sbtl.h"
#include "sbtlactai.h"
#include "sbtlcalc.h"
#include "sbtlcamera.h"
#include "sbtlcommand.h"
#include "sbtldmg.h"
#include "sbtleff.h"
#include "sbtleffbo.h"
#include "sbtlencount.h"
#include "sbtlitem.h"
#include "sbtlmain.h"
#include "sbtlplayer.h"
#include "sbtlplayertbl.h"
#include "sbtlscene.h"
#include "sbtlscript.h"
#include "sbtlskill.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sbtlvisual.h"
#include "sdf_vu0.h"
#include "sdfmodel.h"
#include "sdfquat.h"

typedef enum {
    SBTLEFF_TFLG_NORMAL = 0,
    SBTLEFF_TFLG_ALL = 1,
    SBTLEFF_TFLG_IPARTY = 2,
    SBTLEFF_TFLG_TPARTY = 3,
    SBTLEFF_TFLG_IxT = 4,
    SBTLEFF_TFLG_SPECIAL = 5,
    SBTLEFF_TFLG_TTARGET = 6,
} SBTLEFF_TFLG;

typedef struct EFFPDATA_WORK EFFPDATA_WORK;
typedef struct RESIDENT_DATA RESIDENT_DATA;
typedef struct SBTLEFFDMG_TBL SBTLEFFDMG_TBL;
typedef struct SBTLEFF_DELLISTWORK SBTLEFF_DELLISTWORK;
typedef struct SBTLEFF_LISTWORK SBTLEFF_LISTWORK;
typedef struct SBTLEFF_PACDATAWORK SBTLEFF_PACDATAWORK;
typedef struct SBTLEFF_PACLIST SBTLEFF_PACLIST;
typedef struct SBTLEFF_WORK SBTLEFF_WORK;
typedef struct SBTLUNIT_LISTWORK SBTLUNIT_LISTWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct SBTL_HITEFF SBTL_HITEFF;
typedef struct dds3ProcessID_t dds3ProcessID_t;

typedef bool (*EffFuncDelegate)(SBTLEFF_WORK *UnnamedParameter);

struct RESIDENT_DATA {
    s32 onmem;
    SBTLEFF_FLG flg;
    s32 life;
    EffFuncDelegate func;
};

SBTLEFFDMG_TBL *dmg_tbldata_p;
SBTLEFFDMG_TBL *dmg_tbldata;
ATR *swordAtrTbl;
ATRB *swordAtrbTbl;
BSTF *swordBstTbl;
EFFID *swordEffIdTbl;
sdfVector4_t *swordEffClrTbl;
sdfVector4_t swordEffDefaultClr;
static f32 *effdeg;
static sdfVector4_t effdir;
static SKLID *skltbl;
static sdfVector4_t _defrot;
static EFFID *efftbl_d;
static EFFID *efftbl_y;
static EFFID *efftbl_dd;
static s8 *sbtl_effonfilecheck;
static RESIDENT_DATA *resident;
static SKLID *aDirectEff;

static bool SetEffectPos(SBTLEFF_WORK *ewk, SBTLUNIT_WORK *wk);
static dds3ProcessFunc_t OnDataLoadProc(dds3ProcessID_t *id);
static void OnDataLoadShutdown(dds3ProcessID_t *id);
static void LoadOnMemoryData(SBTLEFF_WORK *wk, SBTLUNIT_WORK *wklock, u16 no);
static bool IsSceanStop(void);
static void LoadOnMemoryData_BED(SBTLEFF_WORK *wk, SBTLUNIT_WORK *wklock, u16 no);
static bool LoadEffectData_IDMask_pData(SKLID id, EFFPAC_ST flg, void *pData);
static bool CheckEffectData_Core(SBTLUNIT_WORK *wk, SKLID sklid, u8 type, s32 index, s32 id, SBTLUNIT_SIDE acterside, s32 serialID2, SBTLEFF_TFLG tflg, s32 sttime, s32 count);
static f32 GetDataScale(SBTLUNIT_WORK *wk, SKLID sklid);
static bool CheckFriend_HelperData(SBTLUNIT_LISTWORK *lwk, SBTLUNIT_WORK *wk, SKLID sklid);
static bool CheckLoadEffectData(SBTLEFF_PACLIST *pac, SKLID skillid, EFFPAC_ST pacflg, void *ppData);
static bool EffFunc_RETURN(SBTLEFF_WORK *wk);
static void NakamaReturnSet(SBTLUNIT_WORK *wklock);
static bool EffFunc_RETURN_D(SBTLEFF_WORK *wk);
static bool EffFunc_RETURN_E(SBTLEFF_WORK *wk);
static bool EffFunc_NMLDAMAGE(SBTLEFF_WORK *wk);
static bool EffFunc_DEADDAMAGE(SBTLEFF_WORK *wk);
static bool EffFunc_SUMMON_ED(SBTLEFF_WORK *wk);
static bool EffFunc_Slip_G(SBTLEFF_WORK *wk);
static bool EffFunc_Hanyou_BED(SBTLEFF_WORK *wk);
static bool IsBstEffect(SBTLEFF_WORK *wk);
static bool EffFunc_SUMMON_ND(SBTLEFF_WORK *wk);
static bool EffFunc_GuardC(SBTLEFF_WORK *wk);
static bool EffFunc_Sword(SBTLEFF_WORK *wk);
static bool EffFunc_GunL(SBTLEFF_WORK *wk);
static bool EffFunc_GunR(SBTLEFF_WORK *wk);
static bool LoadEffectData_BadStatus_pData(void);
static dds3ProcessFunc_t LoadEffectData_BadStatusProc(dds3ProcessID_t *id);
static u32 colup(u32 col, u32 up_raito);

// 0x2072d60
void sBtlAddHitEff(SBTLEFF_WORK *pEffWork) {
  HITEFFLIST *hitEffList;
  SBTL_HITEFF *pHitEffEnd;
  SBTLEFF_LISTWORK *effList;
  s32 effID;
  SBTLEFF_WORK *next;
  s32 lstIdx;
  s64 v12;
  s64 m_Items;
  HITEFFLIST *v16;
  HITEFFLIST *v17;
  s32 v18;
  SBTL_HITEFF *p_pHitEff;
  u32 v21;
  HITEFFLIST *v22;
  SBTL_HITEFF *pHitEffBgn;
  SBTL_HITEFF *v24;
  HITEFFLIST *v25;
  HITEFFLIST *v26;

  hitEffList = wk->hitEffList;
  if (hitEffList->cnt != 16)
  {
    lstIdx = hitEffList->lstIdx;
    if (lstIdx > 15)
      goto LABEL_32;
    goto LABEL_9000;
    if (lstIdx > 15)
    {
LABEL_32:
      lstIdx = 0;
      while (1)
      {
        v16 = wk->hitEffList;
        if (lstIdx >= v16->lstIdx)
          break;
        v16 = wk->hitEffList;
        if (!v16->aHitEff[lstIdx]->bUse)
          break;
        ++lstIdx;
      }
LABEL_41:
      v17 = wk->hitEffList;
      pHitEffEnd = v17->aHitEff[lstIdx];
      v18 = v17->cnt + 1;
      v17->lstIdx = lstIdx;
      v17->cnt = v18;
      pHitEffEnd->bUse = 1;
      goto LABEL_46;
    }
LABEL_9000:
    v12 = lstIdx;
    m_Items = hitEffList->aHitEff;
    while (*(u8 *)(*(u64 *)(m_Items + 8 * v12) + 16))
    {
      if ((u32)++v12 == 16)
        goto LABEL_32;
    }
    lstIdx = v12;
    goto LABEL_41;
  }
  hitEffList = wk->hitEffList;
  pHitEffEnd = hitEffList->pHitEffEnd;
  effList = wk->effList;
  effID = pHitEffEnd->effID;
  if (effList->num)
  {
    next = effList->wk;
    if (next)
    {
      while (next->eListID != effID)
      {
        next = next->next;
        if (!next)
          goto LABEL_45;
      }
      next->pHitEff = 0;
      if ((u32)(next->st - 1) > 1)
      {
        next->alpha = 0;
        next->st = 5;
      }
      else
      {
        next->flg |= 8u;
      }
    }
  }
LABEL_45:
  sBtlOutHitEff(pHitEffEnd);
LABEL_46:
  pEffWork->pHitEff = pHitEffEnd;
  p_pHitEff = &pEffWork->pHitEff;
  pHitEffEnd->effID = *((u32 *)p_pHitEff - 31);
  pHitEffEnd->prev = 0;
  v22 = wk->hitEffList;
  pHitEffBgn = v22->pHitEffBgn;
  if (pHitEffBgn)
  {
    if (!v21)
    {
      pHitEffBgn = wk->hitEffList->pHitEffBgn;
    }
    pHitEffBgn->prev = pHitEffEnd;
    v24 = wk->hitEffList->pHitEffBgn;
    pHitEffEnd->next = v24;
    v25 = wk->hitEffList;
    v25->pHitEffBgn = pHitEffEnd;
    return;
  }
  if (!v21)
  {
    v22 = wk->hitEffList;
  }
  v22->pHitEffBgn = pHitEffEnd;
  v26 = wk->hitEffList;
  v26->pHitEffEnd = pHitEffEnd;
  pHitEffEnd->next = 0;
}

// 0x2073330
void sBtlDltHitEff(SBTLEFF_WORK *pEffWork) {
  SBTL_HITEFF *p_pHitEff;
  SBTL_HITEFF *v4;
  SBTL_HITEFF *pHitEff;

  pHitEff = pEffWork->pHitEff;
  p_pHitEff = &pEffWork->pHitEff;
  v4 = pHitEff;
  if (pHitEff)
  {
    sBtlOutHitEff(v4);
    v4->bUse = 0;
    p_pHitEff = 0;
    --wk->hitEffList->cnt;
    return;
  }
}

// 0x2073420
void sBtlSetEffectData(SBTLEFF_WORK *ewk, SBTLUNIT_WORK *wk, SKLID sklid, s32 workID, SBTLEFF_BEDTYPE type, s32 no, SBTLUNIT_SIDE acterside, s32 serialID2, s32 sttime) {
  u32 v15;
  s32 side;
  SBTLACTAI_WORK *p_actaiwk;
  SBTLACTAI_WORK *v18;
  s32 ListID;
  s64 v23;
  s64 BEDno;
  SBTLEFF_PACLIST *v26;
  EFFPDATA_WORK *v27;
  s64 v28;
  s64 v29;
  SBTLEFF_PACLIST *v30;
  SBTLEFF_PACDATAWORK *v31;
  u32 v32;
  float32x2_t v33;
  f32 fadeout_time;
  f32 v35;
  s32 BEDsklid;
  f32 v37;
  s32 v38;
  f32 DataScale;
  s32 flg;
  SBTLSKILLP_TBL *v42;
  s32 v43;
  s32 v44;
  s64 num;
  s64 v48;
  s64 v49;
  SBTLSKLHIT_PACDATAWORK *v50;
  SBTLSKILLHIT_TBL *v51;
  s32 v53;
  SBTLDMG_HITLISTWORK *hitList;
  SBTLSKILLP_TBL *Skilltbl;

  v15 = type;
  side = wk->side;
  ewk->BEDsklid = sklid;
  ewk->BEDtype = v15;
  ewk->workID = workID;
  ewk->BEDno = no;
  ewk->BEDacterside = side;
  ewk->acterID = wk->ListID;
  if (sklid != 149 || v15 != 2)
  {
    p_actaiwk = &wk->actaiwk;
    if (!wk->actaiwk)
    {
      v18 = sBtlCreate();
      p_actaiwk = v18;
    }
    Skilltbl = sBtlGetSkilltbl(sklid);
    if (wk->battlemode == 3 && (Skilltbl->flg & 4) != 0)
    {
      ListID = wk->ListID;
      sBtlSetTargetID(wk, ListID);
    }
    v23 = ewk->workID;
    BEDno = ewk->BEDno;
    ewk->targetID = p_actaiwk->targetID;
    v26 = wk2->effpac[v23];
    if ((v26->status & 1) != 0)
    {
      v26 = wk2->effpac[v23];
      v27 = v26->pwk[BEDno]->wk;
      v28 = ewk->workID;
      v29 = ewk->BEDno;
LABEL_26:
      v30 = wk2->effpac[v28];
      if ((v30->status & 1) != 0)
      {
        v30 = wk2->effpac[v28];
        v31 = v30->pwk[v29];
        v32 = v27->type;
        if (v15 <= 1)
        {
LABEL_34:
          if (v32 > v15)
            return;
          goto LABEL_40;
        }
      }
      else
      {
        v31 = 0;
        v32 = v27->type;
        if (v15 <= 1)
          goto LABEL_34;
      }
      if (v32 != v15)
        return;
LABEL_40:
      v33.n64_f32[0] = v27->starttime + (f32)sttime;
      v33.n64_u32[1] = LODWORD(v27->life);
      ewk->alpha = 128;
      *(int8x8_t *)&ewk->starttime = vbsl_s8(vceq_f32(v33, vdup_n_s32(0x7F800000u)), (int8x8_t)0x8000000080000000LL, vcvt_s32_f32(v33));
      fadeout_time = v27->fadeout_time;
      if (fadeout_time == 0.0)
      {
        ewk->alpha_cnt = 128;
        if (v27->scale == 0.0)
          goto LABEL_42;
      }
      else
      {
        v37 = 128.0 / (f32)(fadeout_time + fadeout_time);
        v38 = v37;
        if (v37 == INFINITY)
          v38 = 0x80000000;
        ewk->alpha_cnt = v38;
        if (v27->scale == 0.0)
        {
LABEL_42:
          v35 = 1.5;
          ewk->scale = 1.0;
          BEDsklid = ewk->BEDsklid;
          if (BEDsklid == 464)
          {
LABEL_51:
            ewk->scale = v35;
LABEL_52:
            ewk->flg |= v27->flg;
            if (SetEffectPos(ewk, wk))
            {
              if (v31)
                goto LABEL_55;
              goto LABEL_60;
            }
            ewk->flg |= 8u;
            if (v31)
            {
LABEL_55:
              flg = v31->flg;
              v42 = Skilltbl;
              if (flg == 1)
              {
                v43 = 1;
                v44 = Skilltbl->type & 0xFFF;
                if (v44 == 14)
                  goto LABEL_64;
              }
              else
              {
                v43 = 2 * (flg == 0);
                v44 = Skilltbl->type & 0xFFF;
                if (v44 == 14)
                  goto LABEL_64;
              }
LABEL_63:
              if (v44 != 2)
              {
LABEL_66:
                if ((v42->flg2 & 0x1000) == 0)
                  goto LABEL_73;
                if (!wk->bTateNoDmg)
                {
LABEL_73:
                  if (v43 == 1)
                  {
                    num = (u32)v31->hwk->num;
                    if ((s32)num >= 1 && (u32)(sklid - 1333) >= 3 && sklid != 448)
                    {
                      v48 = -num;
                      v49 = 4;
                      do
                      {
                        v50 = *((SBTLSKLHIT_PACDATAWORK *)&v31->hwk->pwk->obj.klass + v49);
                        v51 = v50->wk;
                        v50 = *((SBTLSKLHIT_PACDATAWORK *)&v31->hwk->pwk->obj.klass + v49);
                        v53 = wk->ListID;
                        hitList = wk->hitList;
                        ++v49;
                        ewk->hitserialID = sBtlCreateHitC_New(hitList, wk, ewk, v53, sklid, Skilltbl, v51, v50, acterside, serialID2);
                      }
                      while (v48 + v49 != 4);
                    }
                  }
                }
                return;
              }
LABEL_64:
              if ((v42->area & 0x10) != 0)
                v43 = 2;
              goto LABEL_66;
            }
LABEL_60:
            v42 = Skilltbl;
            v43 = 0;
            v44 = Skilltbl->type & 0xFFF;
            if (v44 == 14)
              goto LABEL_64;
            goto LABEL_63;
          }
LABEL_50:
          if (BEDsklid != 152)
            goto LABEL_52;
          goto LABEL_51;
        }
      }
      DataScale = GetDataScale(wk, sklid);
      ewk->scale = DataScale;
      v35 = DataScale * 1.5;
      BEDsklid = ewk->BEDsklid;
      if (BEDsklid == 464)
        goto LABEL_51;
      goto LABEL_50;
    }
    else
    {
      v27 = 0;
      v28 = ewk->workID;
      v29 = ewk->BEDno;
      goto LABEL_26;
    }
    goto LABEL_26;
  }
}

// 0x2074f70
s32 sBtlGetEffectData_Num(s32 id) {
  SBTLEFF_PACLIST *v4;

  v4 = wk2->effpac[id];
  if ((v4->status & 1) == 0)
    return 0;
  return v4->num;
}

// 0x2073a30
EFFPDATA_WORK *sBtlGetEffectData(s32 id, s32 no) {
  SBTLEFF_PACLIST *v6;

  v6 = wk2->effpac[id];
  if ((v6->status & 1) == 0)
    return 0;
  v6 = wk2->effpac[id];
  return v6->pwk[no]->wk;
}

// 0x2073b00
SBTLEFF_PACDATAWORK *sBtlGetEffectPacData(s32 id, s32 no) {
  SBTLEFF_PACLIST *v6;

  v6 = wk2->effpac[id];
  if ((v6->status & 1) == 0)
    return 0;
  v6 = wk2->effpac[id];
  return v6->pwk[no];
}

// 0x2073d60
static bool SetEffectPos(SBTLEFF_WORK *ewk, SBTLUNIT_WORK *wk) {
  SBTLVISUAL_DATA *v5;
  s64 workID;
  s64 BEDno;
  SBTLEFF_PACLIST *v9;
  EFFPDATA_WORK *v10;
  u32 type;
  u32 BEDtype;
  s64 v13;
  u32 iti;
  struct sdfVector4_t v16;
  char v17;
  char v18;
  f32 v20;
  f32 v21;
  s32 v23;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 targetID;
  SBTLUNIT_WORK *v27;
  SBTLSKILLP_TBL *Skilltbl;
  s32 BEDsklid;
  u16 v31;
  SBATTLE_WORK *v34;
  SBTLUNIT_WORK *Nakama;
  SBATTLE_WORK *v37;
  SBTLUNIT_LISTWORK *v38;
  s32 v39;
  SBTLUNIT_WORK *v40;
  f32 v45;
  f32 x;
  f32 z;
  sdfVector4_t *p_rot;
  s32 muki;
  SBTLEFF_WORK *p_fields;
  f32 v55;
  f32 y;
  f32 v57;
  f32 w;
  f32 v59;
  f32 v61;
  f32 scale;
  f32 v63;
  sdfVector4_t v64;
  s32 PointLast;
  SBTLUNIT_LISTWORK *v68;
  s32 playerID;
  s32 iti_no;
  u32 flg;
  s32 v73;
  _OWORD *p_x;
  __int128 v77;
  __int128 v78;
  struct sdfVector4_t v79;
  struct sdfVector4_t v80;
  struct sdfVector4_t v83;
  struct sdfVector4_t v84;
  struct sdfVector4_t v85;
  struct sdfVector4_t v86;
  struct sdfVector4_t v87;
  sdfVector4_t v88;
  struct sdfVector4_t v93;
  sdfMatrix4_t v94;
  sdfVector4_t rot;
  sdfVector4_t pos;
  sdfMatrix4_t v97;
  sdfMatrix4_t v98;
  sdfVector4_t v99;
  sdfVector4_t v100;
  sdfVector4_t v101;

  v5 = Allocate(SBTLVISUAL_DATA);
  workID = ewk->workID;
  *(u64 *)&pos.x = 0;
  *(u64 *)&pos.z = 0;
  rot = (sdfVector4_t)xmmword_3CFD5C0;
  BEDno = ewk->BEDno;
  v9 = wk2->effpac[workID];
  if ((v9->status & 1) == 0)
  {
    v10 = 0;
    goto LABEL_12;
  }
  v10 = v9->pwk[BEDno]->wk;
LABEL_12:
  type = v10->type;
  BEDtype = ewk->BEDtype;
  v13 = wk->stack_id[wk->stack_id[0] == wk->summonindex[0]];
  if (BEDtype > 1)
  {
    if (type != BEDtype)
      return 1;
    goto LABEL_21;
  }
  if (type <= BEDtype)
  {
LABEL_21:
    iti = v10->iti;
    switch (iti & 0xF)
    {
      case 0u:
      case 1u:
      case 4u:
      case 5u:
      case 8u:
        if (iti < 0x10)
          goto LABEL_23;
        goto LABEL_180;
      case 2u:
        v23 = v10->type;
        if (v23 == 2 || v23 == 5)
          goto LABEL_178;
        UnitMng = wk->UnitMng;
        targetID = ewk->targetID;
        v27 = sBtlSearchUnit_ID(UnitMng, targetID);
        if (v27)
          goto LABEL_179;
        Skilltbl = sBtlGetSkilltbl(ewk->BEDsklid);
        if ((Skilltbl->area & 0x4000) == 0 || v10->type != 1)
          goto LABEL_178;
        v27 = wk;
        if ((Skilltbl->type & 0xFFF) == 8)
          goto LABEL_179;
        return 0;
      case 3u:
        BEDsklid = ewk->BEDsklid;
        if (BEDsklid == 416)
        {
          sBtlGetPointData(7, &pos, &rot);
          v17 = 1;
          pos = wk->pos;
        }
        else
        {
          PointLast = sBtlGetPointLast(wk, BEDsklid);
          sBtlGetPointData(PointLast, &pos, &rot);
          v17 = 1;
        }
        goto LABEL_33;
      case 6u:
        v31 = sBtlGetSkilltbl(ewk->BEDsklid)->type;
        if ((v31 & 0x1000) != 0)
        {
          goto LABEL_169;
        }
        v34 = wk;
        if (v34->member_num >= 1)
        {
          Nakama = sBtlGetNakama(0);
          goto LABEL_173;
        }
LABEL_169:
        v34 = wk;
        v68 = v34->UnitMng;
        playerID = v34->playerID;
        Nakama = sBtlSearchUnit_ID(v68, playerID);
LABEL_173:
        v27 = Nakama;
        if (!Nakama)
          goto LABEL_178;
LABEL_175:
        if (!sBtlCheckDamageTarget(v27))
LABEL_178:
          v27 = wk;
LABEL_179:
        wk = v27;
        if (v10->iti >= 0x10u)
        {
LABEL_180:
          iti_no = v10->iti_no;
          sBtlGetUnitHelperPos(wk, iti_no);
          flg = ewk->flg;
          pos = vct_A;
          if ((flg & 0x200) == 0)
          {
            flg |= 0x1000u;
            ewk->flg = flg;
            if ((v10->iti & 0x40) != 0)
              goto LABEL_187;
            goto LABEL_198;
          }
          if ((v10->iti & 0x40) != 0)
          {
LABEL_187:
            v73 = v10->iti_no;
            ewk->flg = flg | 0x800;
            ewk->helperno = v73;
            sBtlGetUnitHelperMatrix(wk, v73);
            p_x = &vf00.x;
            v77 = p_x[5];
            *(_OWORD *)&v94.m00 = p_x[4];
            *(_OWORD *)&v94.m01 = v77;
            v78 = p_x[7];
            *(_OWORD *)&v94.m02 = p_x[6];
            *(_OWORD *)&v94.m03 = v78;
            sBtlGetQuatFromMatrix(&v94);
            goto LABEL_203;
          }
LABEL_198:
          v93 = wk->rot;
          vct_A = v93;
          goto LABEL_31;
        }
LABEL_23:
        v79 = wk->pos;
        vct_A = v79;
        pos = vct_A;
        v16 = wk->rot;
        vct_A = v16;
LABEL_203:
LABEL_32:
        v17 = 0;
        rot = vct_A;
LABEL_33:
        sBtlGetCylinderData(wk, v5);
        if (v10->iti > 0xFu)
          v18 = 1;
        else
          v18 = v17;
        if ((v18 & 1) == 0)
        {
          switch (v10->takasa)
          {
            case 0:
              v80 = v5->center;
              vct_A = v80;
              v20 = 0.5;
              v21 = v5->e_height;
              goto LABEL_101;
            case 1:
              v83 = v5->center;
              vct_A = v83;
              pos = vct_A;
              break;
            case 2:
              v84 = v5->center;
              vct_A = v84;
              v20 = -0.5;
              v21 = v5->e_height;
              goto LABEL_101;
            case 3:
              v85 = v5->center;
              vct_A = v85;
              v21 = v5->e_height;
              v20 = -0.8;
LABEL_101:
              pos = vct_A;
              v45 = vct_A.y + (f32)(v21 * v20);
              goto LABEL_110;
            case 5:
              v86 = v5->center;
              vct_A = v86;
              pos = vct_A;
              x = pos.x;
              z = pos.z;
              pos.y = sBtlGetGroundPos(x, z);
              v45 = pos.y + sBtlGetYukaEffY();
LABEL_110:
              pos.y = v45;
              break;
            default:
              break;
          }
        }
        v87 = rot;
        vct_A = v87;
        p_rot = &ewk->rot;
        *p_rot = vct_A;
        muki = v10->muki;
        if (muki > 7)
        {
          v88 = pos;
          vct_A = v88;
          p_fields = &ewk->fields;
LABEL_144:
          p_fields->pos = vct_A;
          return 1;
        }
        v55 = rot.x;
        y = rot.y;
        v57 = rot.z;
        w = rot.w;
        LOBYTE(muki) = v10->muki;
        v59 = effdeg[(char)muki];
        v100.x = v55;
        v100.y = y;
        v100.z = v57;
        v100.w = w;
        sBtlGetRotateDeg(v100, v59);
        ToMatrix();
        vct_A = effdir;
        get_transpose(&v98, &mtx_A, 0);
        v101 = vct_A;
        v97 = v98;
        v99 = op_Multiply_60923920(&v97, v101, 0);
        vct_A = v99;
        v61 = v5->width;
        scale = ewk->scale;
        v63 = v61 * scale;
        vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v63);
        v64 = pos;
        vct_B = v64;
        vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
        p_fields = &ewk->fields;
        goto LABEL_144;
LABEL_31:
        goto LABEL_32;
      case 7u:
        v37 = wk;
        v38 = v37->UnitMng;
        v39 = v37->summonID[v13];
        v40 = sBtlSearchUnit_ID(v38, v39);
        if (!v40)
          goto LABEL_178;
        v27 = v40;
        goto LABEL_175;
      default:
        v17 = 1;
        goto LABEL_33;
    }
  }
  return 1;
}

// 0x2075040
void sBtlBS14_CLEAR_Pos(SBTLUNIT_WORK *wk, SBTLEFF_WORK *ewk, sdfVector4_t *p) {
  ;
}

// 0x2075050
bool sBtlCheckDeleteEffect(SBTLEFF_WORK *wk) {
  _BOOL8 v3;
  s32 effectid;

  if ((sBtlGetSkilltbl(wk->BEDsklid)->type & 0xFFFu) - 9 >= 2)
  {
    if (!wk->BEDsklid)
    {
LABEL_14:
      effectid = wk->effectid;
      if (effectid <= 14)
      {
        if ((u32)effectid < 0xF)
        {
          LODWORD(v3) = (0x3F47u >> effectid) & 1;
          return v3;
        }
      }
      else if ((u32)effectid < 0x34)
      {
        return (0x7EAFFFFFBFFFFuLL >> effectid) & 1;
      }
LABEL_19:
      LOBYTE(v3) = 1;
      return v3;
    }
    if ((wk2->effpac[wk->workID]->status & 1) != 0)
      goto LABEL_19;
    goto LABEL_14;
  }
  LOBYTE(v3) = 0;
  return v3;
}

// 0x2075240
bool sBtlCheckCancelEffect(SKLID skillID) {
  _BOOL4 v3;

  if (skillID > 442)
  {
    if ((u32)skillID <= 0x1D4)
    {
      if ((u32)(skillID - 449) < 0x14)
        return (0x80005u >> (skillID + 63)) & 1;
    }
    else
    {
      LOBYTE(v3) = 1;
      if (skillID == 472 || skillID == 477 || skillID == 1120)
        return v3;
    }
LABEL_14:
    LOBYTE(v3) = 0;
    return v3;
  }
  if (skillID > 420)
  {
    if ((u32)(skillID - 425) < 0x12)
      return (0x25D05u >> (skillID + 87)) & 1;
    goto LABEL_14;
  }
  LOBYTE(v3) = 1;
  if ((u32)(skillID - 418) >= 3 && skillID != 152)
    goto LABEL_14;
  return v3;
}

// 0x20752e0
static dds3ProcessFunc_t OnDataLoadProc(dds3ProcessID_t *id) {
  s64 v2;
  SBTLEFF_DATAWORK *v4;
  plistHandle_t *v5;
  dds3ProcessFunc_t v10;

  v2 = 0;
  do
  {
    if (sbtl_effonfilecheck[v2] == 2)
    {
      v4 = wkeffOnMem[v2];
      v5 = Create(v4->pData, 0);
      v4->hPartsList = v5;
    }
    ++v2;
  }
  while (v2 != 46);
  wk->status |= 4u;
  v10 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v10, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
  return v10;
}

// 0x2075460
static void OnDataLoadShutdown(dds3ProcessID_t *id) {
  ;
}

// 0x2075470
static void LoadOnMemoryData(SBTLEFF_WORK *wk, SBTLUNIT_WORK *wklock, u16 no) {
  u32 flg;
  SBTLEFF_DATAWORK *v9;
  s64 onmem;
  s32 v11;
  plistHandle_t *v14;
  SBTLEFF_DATAWORK *dwk;
  SBTLDMG_HITLISTWORK *hitList;
  s32 hitserialID;
  SBTLDMG_HITWORK *v19;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  long f64 v24;

  flg = wk->flg;
  if ((flg & 0x80) != 0)
  {
    if ((flg & 8) != 0)
      goto LABEL_19;
LABEL_7:
    if (no && (!wklock || wklock->actwk->status != no))
      goto LABEL_19;
    if (wk->starttime > wk->counter)
      return;
    if ((flg & 0x20) != 0)
    {
      dwk = wk->dwk;
      dwk->hPartsList = 0;
      if ((wk->flg & 0x2000) == 0)
        goto LABEL_39;
      goto LABEL_38;
    }
    if (!wk->bTateBg)
    {
      v9 = wk->dwk;
      onmem = resident[wk->effectid]->onmem;
      v11 = (u8)sbtl_effonfilecheck[onmem];
      if (v11 == 2)
      {
        v14 = Copy(wkeffOnMem[onmem]->hPartsList);
      }
      else
      {
        v14 = Create(wkeffOnMem[onmem]->pData, 0);
      }
      v9->hPartsList = v14;
    }
    if ((wk->flg & 0x200) != 0)
    {
      hitList = wk->hitList;
      hitserialID = wk->hitserialID;
      v19 = sBtlSearchHit_SerialID(hitList, hitserialID);
      if (!v19)
      {
LABEL_37:
        effPartsRotateSet(wk->dwk->hPartsList, wk->rot);
        effPartsScaleSet(wk->dwk->hPartsList, wk->scale);
        if ((wk->flg & 0x2000) == 0)
        {
LABEL_39:
          wk->cmpcounter = wk->life;
          *(u64 *)&wk->st = 3;
          return;
        }
LABEL_38:
        ColorSet(wk->dwk->hPartsList, wk->rgb);
        goto LABEL_39;
      }
      x = v19->pos.x;
      y = v19->pos.y;
      z = v19->pos.z;
      w = v19->pos.w;
      *(__n128 *)&v24 = sub_1B332C0(0, x, y, z, w);
      sub_1B335A0(&wk->fields, 0, v24);
    }
    effPartsPositionSet(wk->dwk->hPartsList, wk->pos);
    goto LABEL_37;
  }
  flg |= 0x80u;
  wk->counter = 0;
  wk->flg = flg;
  if ((flg & 8) == 0)
    goto LABEL_7;
LABEL_19:
  wk->st = 5;
}

// 0x2075770
bool sBtlCheckStopEffect(SBTLEFF_WORK *wk) {
  if ((wk->status & 0x8000000) == 0)
    return 1;
  if ((wk->flg & 0x10) != 0)
    return 1;
  return !IsSceanStop();
}

// 0x2075850
static bool IsSceanStop(void) {
  if (!IsSceanStop())
    return 0;
  if (sBtlCheckSetsuma())
    return 0;
  if (wk->battlStopEff)
    return 0;
  return 1;
}

// 0x2075980
static void LoadOnMemoryData_BED(SBTLEFF_WORK *wk, SBTLUNIT_WORK *wklock, u16 no) {
  u32 flg;
  s64 workID;
  SBTLEFF_PACLIST *v10;
  s32 BEDsklid;
  s64 effectid;
  SBTLEFF_DATAWORK *dwk;
  SBTLEFF_DATAWORK *v14;
  plistHandle_t *v15;
  effPartsListPose_t *pose;
  f32 v17;
  s64 v18;
  SBTLDMG_HITLISTWORK *hitList;
  s32 hitserialID;
  SBTLDMG_HITWORK *v22;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  long f64 v27;

  flg = wk->flg;
  if ((flg & 0x80) != 0)
  {
    if ((flg & 8) != 0)
      goto LABEL_21;
LABEL_7:
    if (no && (!wklock || wklock->actwk->status != no))
      goto LABEL_21;
    if (wk->starttime > wk->counter)
      return;
    if ((flg & 0x20) != 0)
    {
      dwk = wk->dwk;
      dwk->hPartsList = 0;
      goto LABEL_52;
    }
    workID = wk->workID;
    v10 = wk2->effpac[workID];
    if ((v10->status & 8) != 0)
    {
      v14 = wk->dwk;
      v10 = wk2->effpac[wk->workID];
      v15 = Copy(v10->pwk[wk->effectid]->hPartsList);
      goto LABEL_42;
    }
    BEDsklid = wk->BEDsklid;
    if (BEDsklid == 464)
    {
      if (wk->BEDtype != 1)
        goto LABEL_38;
      LODWORD(effectid) = wk->effectid;
      if ((u32)(effectid - 3) > 1)
        goto LABEL_38;
    }
    else if (BEDsklid != 466 || wk->BEDtype != 1 || (LODWORD(effectid) = wk->effectid, (u32)effectid > 4) || ((1 << effectid) & 0x13) == 0)
    {
LABEL_38:
      v14 = wk->dwk;
      v10 = wk2->effpac[wk->workID];
      v18 = (s64)v10->pwk + 8 * wk->effectid;
LABEL_41:
      v15 = Create(*(plistHandle_t_Resource *)(*(u64 *)(v18 + 32) + 16), 0);
LABEL_42:
      v14->hPartsList = v15;
      effPartsRotateSet(wk->dwk->hPartsList, wk->rot);
      effPartsScaleSet(wk->dwk->hPartsList, wk->scale);
      if ((wk->flg & 0x200) != 0)
      {
        hitList = wk->hitList;
        hitserialID = wk->hitserialID;
        v22 = sBtlSearchHit_SerialID(hitList, hitserialID);
        if (!v22)
          goto LABEL_52;
        x = v22->pos.x;
        y = v22->pos.y;
        z = v22->pos.z;
        w = v22->pos.w;
        *(__n128 *)&v27 = sub_1B332C0(0, x, y, z, w);
        sub_1B335A0(&wk->fields, 0, v27);
      }
      effPartsPositionSet(wk->dwk->hPartsList, wk->pos);
LABEL_52:
      wk->cmpcounter = wk->life;
      *(u64 *)&wk->st = 3;
      return;
    }
    LODWORD(effectid) = wk->effectid;
    v10 = wk2->effpac[wk->workID];
    LODWORD(workID) = wk->workID;
    pose = v10->pwk[(s32)effectid]->pData->pose;
    v17 = pose->posBase.y;
    if (v17 <= -600.0)
    {
      effectid = wk->effectid;
      pose = wk2->effpac[wk->workID]->pwk[effectid]->pData->pose;
      LODWORD(workID) = wk->workID;
      v17 = pose->posBase.y;
      pose->posBase.y = v17 + 600.0;
    }
    v14 = wk->dwk;
    LODWORD(workID) = wk->workID;
    LODWORD(effectid) = wk->effectid;
    v18 = (s64)wk2->effpac[(s32)workID]->pwk + 8 * (s32)effectid;
    goto LABEL_41;
  }
  flg |= 0x80u;
  wk->counter = 0;
  wk->flg = flg;
  if ((flg & 8) == 0)
    goto LABEL_7;
LABEL_21:
  wk->st = 5;
}

// 0x2075da0
bool sBtlSetEffectColor_Race(SBTLEFF_WORK *wk, SBTLUNIT_WORK *wklock) {
  u32 devilid;
  bool v4;
  s64 v5;

  if (wklock)
  {
    devilid = (u16)wklock->para->devilid;
    v4 = devilid > 0x3C;
    v5 = (1 << devilid) & 0x1020200000000000LL;
    if (!v4 && v5 != 0)
      effPartsColorSet(wk->dwk->hPartsList, 0x80808080);
  }
  return 1;
}

// 0x2075e00
static bool LoadEffectData_IDMask_pData(SKLID id, EFFPAC_ST flg, void *pData) {
  s64 v10;
  s64 v11;
  s64 v13;
  u32 bits;
  SBTLEFF_PACLIST *v15;
  SBTLEFF_PACLIST *v16;
  u32 v19;
  SBTLEFF_PACLIST *v20;
  u16 status;
  u16 v25;

  v10 = 0;
  while (1)
  {
    v11 = (s64)wk2->effpac + 8 * v10;
    if (*(u32 *)(*(u64 *)(v11 + 32) + 40) == id)
      goto LABEL_20;
    if (*(u32 *)(*(u64 *)(v11 + 40) + 40) == id)
    {
      LODWORD(v10) = v10 + 1;
      goto LABEL_20;
    }
    v10 += 2;
    if (v10 == 150)
      goto LABEL_21;
  }
  v10 = 0;
  while (1)
  {
    if (wk2->effpac[v10]->skillID == id)
      break;
    if (++v10 == 150)
      goto LABEL_21;
  }
LABEL_20:
  if ((u32)v10 == -1)
  {
LABEL_21:
    v13 = 32;
    while (1)
    {
      bits = (*(Il2CppClass **)((char *)&wk2->effpac->obj.klass + v13))->_1.byval_arg.bits;
      if (bits == -1)
        break;
      bits = (*(Il2CppClass **)((char *)&wk2->effpac->obj.klass + v13))->_1.byval_arg.bits;
      if (!bits)
        break;
      v13 += 8;
      if (v13 == 1232)
        return 0;
    }
    if (v13 != 0x800000018LL)
    {
      v15 = *(SBTLEFF_PACLIST *)((char *)&wk2->effpac->obj.klass + v13);
      if (CheckLoadEffectData(v15, id, flg, pData))
      {
        v20 = *(SBTLEFF_PACLIST *)((char *)&wk2->effpac->obj.klass + v13);
        status = v20->status;
        if ((flg & 8) != 0 && (status & 0x10) == 0)
        {
          v20 = *(SBTLEFF_PACLIST *)((char *)&wk2->effpac->obj.klass + v13);
          goto LABEL_60;
        }
        v20 = *(SBTLEFF_PACLIST *)((char *)&wk2->effpac->obj.klass + v13);
        goto LABEL_67;
      }
    }
    return 0;
  }
  v16 = wk2->effpac[(s32)v10];
  if (!CheckLoadEffectData(v16, id, flg, pData))
    return 0;
  v20 = wk2->effpac[(s32)v10];
  status = v20->status;
  if ((flg & 8) == 0 || (status & 0x10) != 0)
  {
    if (!v19)
    {
      v20 = wk2->effpac[(s32)v10];
LABEL_67:
      status = v20->status;
    }
    v25 = status | flg;
    goto LABEL_69;
  }
  if (!v19)
  {
    v20 = wk2->effpac[(s32)v10];
LABEL_60:
    status = v20->status;
  }
  v25 = status | flg & 0xFFF7;
LABEL_69:
  v20->status = v25;
  return 1;
}

// 0x2076cc0
static bool CheckEffectData_Core(SBTLUNIT_WORK *wk, SKLID sklid, u8 type, s32 index, s32 id, SBTLUNIT_SIDE acterside, s32 serialID2, SBTLEFF_TFLG tflg, s32 sttime, s32 count) {
  SBTLDMG_HITWORK *v14;
  SBTLSKILLP_TBL *v15;
  SBTLUNIT_LISTWORK *UnitList;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  SBTLUNIT_LISTWORK *v23;
  SBTLUNIT_WORK *v24;
  s64 v25;
  s32 v26;
  SBTLUNIT_LISTWORK *v28;
  SBTLUNIT_WORK *v29;
  SBTLUNIT_WORK *v31;
  SBTLUNIT_LISTWORK *v33;
  s32 v34;
  SBTLUNIT_WORK *v35;
  s64 v36;
  SBTLEFF_WORK *EffWork;
  s32 v38;
  s32 v39;
  SBTLUNIT_WORK *v40;
  SBTLEFF_PACLIST *v42;
  u16 area;
  SBTLEFF_LISTWORK *effList;
  u16 v47;
  SBATTLE_WORK *v49;
  s64 tateClr;
  SBATTLE_WORK *v54;
  u16 v55;
  s64 v56;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  SBTLUNIT_WORK *v61;
  SBTLUNIT_WORK *v62;
  SBTLUNIT_LISTWORK *v64;
  s32 playerID;
  SBTLUNIT_WORK *v66;
  s64 v67;
  s32 v68;
  s32 v69;
  SBTLUNIT_LISTWORK *v71;
  SBTLUNIT_WORK *v72;
  s32 v73;
  s32 devilid;
  s32 v75;
  s32 targetID;
  SBTLUNIT_LISTWORK *v77;
  SBTLUNIT_WORK *v78;
  f32 v80;
  f32 v81;
  f32 v82;
  f32 v83;
  SBTLUNIT_WORK *v84;
  SBTLUNIT_WORK *v86;
  s64 v88;
  SBTLUNIT_WORK *v89;
  u16 v90;
  SBTLDMG_HITWORK *v91;
  f32 v93;
  f32 v94;
  SBTLDMG_HITLISTWORK *hitList;
  f32 v96;
  f32 v97;
  SBTLUNIT_LISTWORK *hitlwk;
  s64 j;
  SBTLUNIT_LISTWORK *v102;
  SBTLUNIT_WORK *v103;
  s64 v104;
  f32 v105;
  f32 v106;
  f32 v107;
  f32 v108;
  SBTLUNIT_WORK *v109;
  s32 v110;
  s32 order_stockID;
  sdatUnitWork_t *StockUnitData;
  sdatUnitWork_t *v113;
  SBTLDMG_HITWORK *v115;
  f32 v117;
  f32 v118;
  SBTLDMG_HITLISTWORK *v119;
  f32 v120;
  f32 v121;
  SBTLUNIT_LISTWORK *v122;
  s64 k;
  SBTLUNIT_LISTWORK *v125;
  SBTLUNIT_WORK *v126;
  s64 v127;
  SBTLUNIT_WORK *v128;
  u16 v129;
  SBTLDMG_HITWORK *v130;
  f32 v132;
  f32 v133;
  SBTLDMG_HITLISTWORK *v134;
  f32 v135;
  f32 v136;
  SBTLUNIT_LISTWORK *v137;
  sdatUnitWork_t *v139;
  s32 n;
  sdatUnitWork_t *v141;
  SBATTLE_WORK *v143;
  sdatUnitWork_t *v144;
  sdatUnitWork_t *v145;
  SBATTLE_WORK *v147;
  s32 useitem_stock;
  sdatUnitWork_t *v150;
  sdatUnitWork_t *v151;
  s32 v153;
  s32 m;
  sdatUnitWork_t *v156;
  s32 useitemID;
  SBTLUNIT_LISTWORK *v160;
  SBTLUNIT_WORK *v161;
  s32 v163;
  SBTLUNIT_WORK *v165;
  SBTLDMG_HITWORK *v166;
  f32 v168;
  f32 v169;
  SBTLDMG_HITLISTWORK *v170;
  f32 v171;
  f32 v172;
  SBTLUNIT_LISTWORK *v173;
  sdatUnitWork_t *para;
  sdatUnitWork_t *v175;
  s16 v177;
  SBTLSKILLP_TBL *tbl;
  SBTLUNIT_LISTWORK *v179;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLUNIT_WORK *v186;
  sdfVector4_t v187;
  sdfVector4_t v188;
  sdfVector4_t v189;
  sdfVector4_t v190;
  sdfVector4_t v191;
  sdfVector4_t v192;
  sdfVector4_t v193;

  v14 = Allocate(SBTLDMG_HITWORK);
  _ctor(v14, 0);
  Skilltbl = sBtlGetSkilltbl(sklid);
  v15 = sBtlGetSkilltbl(sklid);
  UnitList = sBtlCreateUnitList(48);
  v177 = tflg;
  v186 = wk;
  tbl = v15;
  switch (tflg)
  {
    case 0:
      CheckFriend_HelperData(UnitList, wk, sklid);
      goto LABEL_66;
    case 1:
      for (i = 0; ; ++i)
      {
        UnitMng = wk->UnitMng;
        if (i >= UnitMng->number)
          goto LABEL_66;
        pUnit = UnitMng->pUnitL[i]->pUnit;
        if (!pUnit)
          continue;
        if (!sBtlCheckLiveTarget_NotHitDmg(pUnit))
          continue;
        sBtlEntryUnitList(UnitList, pUnit);
      }
    case 2:
      if (sklid == 313)
      {
        v23 = UnitList;
        v24 = wk;
        goto LABEL_65;
      }
      v67 = 0;
      v68 = 0;
      v69 = sBtlGetBothSide(wk, acterside) & 0x3F;
      while (2)
      {
        v71 = wk->UnitMng;
        if (v67 >= v71->number)
          goto LABEL_66;
        v72 = v71->pUnitL[v67]->pUnit;
        if (!v72)
          goto LABEL_159;
        v73 = v72->side;
        if ((v69 & v73) == 0)
          goto LABEL_159;
        if ((v73 & wk->side & 1) != 0 && v72->L2_muteki && (v15->flg & 4) != 0)
        {
          if (((v68 | ((u8)(BYTE1(v15->attr) & 2) >> 1)) & 1) != 0)
            goto LABEL_172;
        }
        else if ((v68 & 1) != 0)
        {
LABEL_172:
          v68 = 1;
          if (sBtlCheckLiveTarget_NotHitDmg_Kakusi(v72))
            goto LABEL_182;
LABEL_159:
          ++v67;
          continue;
        }
        break;
      }
      v68 = 0;
      if (sBtlCheckLiveTarget_NotHitDmg(v72))
        goto LABEL_182;
      goto LABEL_159;
LABEL_182:
      if (sklid != 128 || (devilid = (u16)wk->para->devilid, devilid != 300) && devilid != 262 || (v75 = (u16)v72->para->devilid, v75 == 300) || v75 == 262)
      {
        sBtlEntryUnitList(UnitList, v72);
      }
      goto LABEL_159;
    case 3:
      v25 = 0;
      v26 = sBtlGetBothSide(wk, acterside) & 0x3F;
      while (2)
      {
        v28 = wk->UnitMng;
        if (v25 < v28->number)
        {
          v29 = v28->pUnitL[v25]->pUnit;
          if (v29)
          {
            if (sBtlCheckLiveTarget_NotHitDmg(v29))
            {
              if ((v26 & v29->side) == 0)
              {
                sBtlEntryUnitList(UnitList, v29);
              }
            }
          }
          ++v25;
          continue;
        }
        break;
      }
LABEL_66:
      v179 = UnitList;
      if (UnitList->count >= 1)
      {
        v36 = 0;
        EffWork = 0;
        v38 = sttime;
        while (1)
        {
          v40 = UnitList->pUnitL[v36]->pUnit;
          v42 = wk2->effpac[index];
          if ((v42->status & 1) != 0)
          {
            v42 = wk2->effpac[index];
            if (sBtlCheckEffectCancel(v186, sklid, v42->pwk[id]->wk))
              goto LABEL_71;
          }
          else if (sBtlCheckEffectCancel(v186, sklid, 0))
          {
            goto LABEL_71;
          }
          area = sBtlGetSkilltbl(sklid)->area;
          if ((area & 0x10) != 0)
          {
            if ((area & 0x4000) != 0 && (v40->status & 0x8800) == 0x8800 && !v40->hithelpercsrno)
              goto LABEL_71;
          }
          effList = wk->effList;
          EffWork = sBtlGetEffWork(effList, v40, index, id);
          if ((Skilltbl->flg2 & 0x10) == 0)
          {
LABEL_96:
            EffWork->rgb = oneVector;
            if ((v40->vstatus & 0x4000) != 0)
              goto LABEL_99;
            goto LABEL_100;
          }
          v49 = wk;
          if (v49->sword_eff_cmb)
          {
            UnitList = v179;
            tateClr = wk->cmbSkl->tateClr;
            goto LABEL_120;
          }
          if (v49->sword_eff_step)
            goto LABEL_117;
          goto LABEL_9002;
          if (wk->sword_eff_step)
          {
LABEL_117:
            UnitList = v179;
            tateClr = wk->sword_eff_kind;
LABEL_120:
            EffWork->rgb = swordEffClrTbl[tateClr];
            if ((v40->vstatus & 0x4000) != 0)
              goto LABEL_99;
            goto LABEL_100;
          }
LABEL_9002:
          if (!sbtlplayertblChkPlayerMagSkill(sklid))
            goto LABEL_96;
          UnitList = v179;
          EffWork->rgb = swordEffDefaultClr;
          if ((v40->vstatus & 0x4000) != 0)
LABEL_99:
            EffWork->flg |= 0x10u;
LABEL_100:
          v47 = sBtlGetSkilltbl(sklid)->area;
          if ((v47 & 0x10) == 0)
            goto LABEL_68;
          if ((v47 & 0x4000) == 0 || (v40->status & 0x8800) != 0x8800 || !v40->hithelpercsrno)
          {
LABEL_68:
            v39 = v38;
            v39 = v38;
            goto LABEL_70;
          }
          v39 = sttime;
          v39 = sttime;
LABEL_70:
          sBtlSetEffectData(EffWork, v40, sklid, index, type, id, acterside, serialID2, v39);
LABEL_71:
          ++v36;
          v38 += 12;
          if (v36 >= UnitList->count)
            goto LABEL_136;
        }
      }
      EffWork = 0;
LABEL_136:
      if (type > 1u)
        goto LABEL_200;
      v54 = wk;
      if ((v54->status & 0x2000000) != 0)
        goto LABEL_200;
      if (UnitList->count < 1)
        goto LABEL_200;
      if (count)
        goto LABEL_200;
      v55 = tbl->area;
      if ((v55 & 0x10) == 0)
        goto LABEL_200;
      if ((tbl->area & 0x4000) == 0)
      {
        if (v177)
        {
          v56 = 0;
          do
          {
            x = EffWork->pos.x;
            y = EffWork->pos.y;
            z = EffWork->pos.z;
            w = EffWork->pos.w;
            v61 = UnitList->pUnitL[v56]->pUnit;
            v187.x = x;
            v187.y = y;
            v187.z = z;
            v187.w = w;
            SetDamageProc(v61, v186, sklid, v187);
            ++v56;
          }
          while (v56 < UnitList->count);
        }
        else if ((v55 & 2) != 0)
        {
          sBtlDeleteUnitList(UnitList, 0);
          UnitList = sBtlCreateUnitList(48);
          for (j = 0; ; ++j)
          {
            v102 = wk->UnitMng;
            if (j >= v102->number)
              break;
            v102 = wk->UnitMng;
            v103 = v102->pUnitL[j]->pUnit;
            if (v103)
            {
              if (CheckLiveTarget(v103) && (acterside & 0x3F & v103->side) == 0)
              {
                sBtlEntryUnitList(UnitList, v103);
              }
            }
          }
          if (UnitList->count >= 1)
          {
            v104 = 0;
            do
            {
              v105 = EffWork->pos.x;
              v106 = EffWork->pos.y;
              v107 = EffWork->pos.z;
              v108 = EffWork->pos.w;
              v109 = UnitList->pUnitL[v104]->pUnit;
              v190.x = v105;
              v190.y = v106;
              v190.z = v107;
              v190.w = v108;
              SetDamageProc(v109, v186, sklid, v190);
              ++v104;
            }
            while (v104 < UnitList->count);
          }
        }
        else
        {
          targetID = v186->actaiwk->targetID;
          if (targetID != -1)
          {
            targetID = v186->actaiwk->targetID;
            v54 = wk;
            v77 = v54->UnitMng;
            v78 = sBtlSearchUnit_ID(v77, targetID);
            v80 = EffWork->pos.x;
            v81 = EffWork->pos.y;
            v82 = EffWork->pos.z;
            v83 = EffWork->pos.w;
            v84 = v78;
            v188.x = v80;
            v188.y = v81;
            v188.z = v82;
            v188.w = v83;
            SetDamageProc(v84, v186, sklid, v188);
          }
        }
        goto LABEL_200;
      }
      v62 = v186;
      v64 = v54->UnitMng;
      playerID = v54->playerID;
      v66 = sBtlSearchUnit_ID(v64, playerID);
      if (!v66)
        goto LABEL_200;
      v86 = v66;
      if (v66->actwk->status == 34)
        goto LABEL_200;
      if (v177)
      {
        if (UnitList->count >= 1)
        {
          v88 = 0;
          while (1)
          {
            v89 = UnitList->pUnitL[v88]->pUnit;
            if (!v89)
              goto LABEL_207;
            if (!CheckLiveTarget(v89))
              goto LABEL_207;
            v90 = sBtlGetSkilltbl(sklid)->area;
            if ((v90 & 0x10) == 0)
              goto LABEL_219;
            if ((v90 & 0x4000) == 0 || (v89->status & 0x8800) != 0x8800 || v89->hithelpercsrno)
            {
LABEL_219:
              if ((v89->side & 1) == 0 || (v89->para->flag & 2) != 0 || v89 == sBtlGetNakama(0) || v89 == sBtlGetNakama(1))
              {
                v91 = Allocate(SBTLDMG_HITWORK);
                _ctor(v91, 0);
                v93 = EffWork->pos.x;
                v94 = EffWork->pos.y;
                hitList = wk->hitList;
                v96 = EffWork->pos.z;
                v97 = EffWork->pos.w;
                v189.x = v93;
                v189.y = v94;
                v189.z = v96;
                v189.w = v97;
                sBtlCreateHitC_None(hitList, v89, v186, v91, sklid, tbl, v189, -1);
                sBtlAddSerialID2();
                sBtlDamageProc(v89, v91, 0);
                hitlwk = v91->hitlwk;
                sBtlDeleteUnitList(hitlwk, 0);
              }
            }
LABEL_207:
            if (++v88 >= UnitList->count)
              goto LABEL_309;
          }
        }
        goto LABEL_310;
      }
      if ((tbl->area & 2) != 0)
      {
        sBtlDeleteUnitList(UnitList, 0);
        UnitList = sBtlCreateUnitList(48);
        for (k = 0; ; ++k)
        {
          v125 = wk->UnitMng;
          if (k >= v125->number)
            break;
          v125 = wk->UnitMng;
          v126 = v125->pUnitL[k]->pUnit;
          if (v126)
          {
            if (CheckLiveTarget(v126) && (acterside & 0x3F & v126->side) != 0)
            {
              sBtlEntryUnitList(UnitList, v126);
            }
          }
        }
        if (UnitList->count >= 1)
        {
          v127 = 0;
          do
          {
            v128 = UnitList->pUnitL[v127]->pUnit;
            if (v128)
            {
              if (CheckLiveTarget(v128))
              {
                v129 = sBtlGetSkilltbl(sklid)->area;
                if (((v129 & 0x10) == 0 || (v129 & 0x4000) == 0 || (v128->status & 0x8800) != 0x8800 || v128->hithelpercsrno) && ((v128->side & 1) == 0 || (v128->para->flag & 2) != 0 || v128 == sBtlGetNakama(0) || v128 == sBtlGetNakama(1)))
                {
                  v130 = Allocate(SBTLDMG_HITWORK);
                  _ctor(v130, 0);
                  v132 = EffWork->pos.x;
                  v133 = EffWork->pos.y;
                  v134 = wk->hitList;
                  v135 = EffWork->pos.z;
                  v136 = EffWork->pos.w;
                  v192.x = v132;
                  v192.y = v133;
                  v192.z = v135;
                  v192.w = v136;
                  sBtlCreateHitC_None(v134, v128, v186, v130, sklid, tbl, v192, -1);
                  sBtlAddSerialID2();
                  sBtlDamageProc(v128, v130, 0);
                  v137 = v130->hitlwk;
                  sBtlDeleteUnitList(v137, 0);
                }
              }
            }
            ++v127;
          }
          while (v127 < UnitList->count);
LABEL_309:
          v62 = v186;
        }
        goto LABEL_310;
      }
      v110 = v186->actaiwk->targetID;
      if ((v110 & 0x80000000) == 0)
      {
        order_stockID = v186->actwk->order_stockID;
        if ((order_stockID & 0x80000000) == 0 && (v186->side & 2) == 0)
        {
          if ((tbl->type & 8) == 0)
          {
            StockUnitData = sBtlGetStockUnitData(order_stockID);
            v113 = StockUnitData;
            if ((tbl->area & 0x100) != 0)
            {
              para = v186->para;
              sBtlGetDamage_GB(para, v113, sklid);
            }
            else if (sBtlCheckLive(StockUnitData))
            {
              if (wk->battlemode == 3)
              {
                v115 = Allocate(SBTLDMG_HITWORK);
                _ctor(v115, 0);
                v117 = EffWork->pos.x;
                v118 = EffWork->pos.y;
                v119 = wk->hitList;
                v121 = EffWork->pos.z;
                v120 = EffWork->pos.w;
                v191.x = v117;
                v191.y = v118;
                v191.z = v121;
                v191.w = v120;
                sBtlCreateHitC_None(v119, v86, v186, v115, sklid, tbl, v191, -1);
                sBtlAddSerialID2();
                sBtlDamageProc(v86, v115, 0);
                v122 = v115->hitlwk;
                sBtlDeleteUnitList(v122, 0);
              }
              else
              {
                v175 = v186->para;
                sBtlGetDamage_GB(v175, v113, sklid);
              }
              v62 = v186;
              UnitList = v179;
            }
          }
          goto LABEL_310;
        }
        v160 = wk->UnitMng;
        v161 = sBtlSearchUnit_ID(v160, v110);
        if (!v161)
          goto LABEL_310;
        v165 = v161;
        if (CheckLiveTarget(v165))
        {
          v166 = Allocate(SBTLDMG_HITWORK);
          _ctor(v166, 0);
          v168 = EffWork->pos.x;
          v169 = EffWork->pos.y;
          v170 = wk->hitList;
          v172 = EffWork->pos.z;
          v171 = EffWork->pos.w;
          v193.x = v168;
          v193.y = v169;
          v193.z = v172;
          v193.w = v171;
          sBtlCreateHitC_None(v170, v165, v186, v166, sklid, tbl, v193, -1);
          sBtlAddSerialID2();
          sBtlDamageProc(v165, v166, 0);
          v173 = v166->hitlwk;
          sBtlDeleteUnitList(v173, 0);
        }
        goto LABEL_310;
      }
LABEL_310:
      if ((tbl->type & 8) != 0)
      {
        v147 = wk;
        if (v147->battlemode != 3)
        {
          v147 = wk;
          if ((sBtlGetItemtbl(v147->useitemID)->side & 4) != 0)
          {
            for (m = 0; ; ++m)
            {
              if (m >= wk->stock_num)
                break;
              v156 = sBtlGetStockUnitData(m);
              if (sBtlCheckLive(v156))
              {
                useitemID = wk->useitemID;
                CalcItem(v156, useitemID);
                sBtlCheckItemMember(m);
              }
            }
          }
          else
          {
            useitem_stock = (u16)wk->useitem_stock;
            if (useitem_stock != 0xFFFF)
            {
              LOWORD(useitem_stock) = wk->useitem_stock;
              v150 = sBtlGetStockUnitData((s16)useitem_stock);
              v151 = v150;
              if ((tbl->area & 0x100) != 0)
              {
                v163 = wk->useitem_stock;
                sBtlCheckItemMember(v163);
                CalcItem(v151, wk->useitemID);
                sBtlCheckItemMember_Dead(wk->useitem_stock);
              }
              else if (sBtlCheckLive(v150))
              {
                v153 = wk->useitemID;
                CalcItem(v151, v153);
                sBtlCheckItemMember(wk->useitem_stock);
              }
              wk->useitem_stock = -1;
            }
          }
        }
      }
      else if ((tbl->area & 6) != 0 && (v62->side & 1) != 0)
      {
        if (wk->battlemode != 3)
        {
          v139 = v62->para;
          if (sBtlGetBadStatus(v139) - 7 >= 2)
          {
            for (n = 0; ; ++n)
            {
              v143 = wk;
              if (n >= v143->stock_num)
                break;
              v143 = wk;
              if (v143->member_num < 1)
                goto LABEL_333;
              v143 = wk;
              if (n != v143->summonindex[0])
              {
LABEL_333:
                v144 = sBtlGetStockUnitData(n);
                v145 = v144;
                if ((tbl->area & 0x100) != 0 || sBtlCheckLive(v144))
                {
                  v141 = v62->para;
                  sBtlGetDamage_GB(v141, v145, sklid);
                }
              }
            }
          }
        }
      }
LABEL_200:
      sBtlDeleteUnitList(UnitList, 0);
      return 1;
    case 4:
      sBtlEntryUnitList(UnitList, wk);
      v31 = sBtlSearchUnit_ID(wk->UnitMng, wk->actaiwk->targetID);
      if (v31)
        goto LABEL_59;
      goto LABEL_66;
    case 6:
      v33 = wk->UnitMng;
      v34 = wk->actaiwk->targetID;
      v31 = sBtlSearchUnit_ID(v33, v34);
      if (v31)
      {
LABEL_59:
        v35 = v31;
        if (sBtlCheckLiveTarget_NotHitDmg(v35))
        {
          v23 = UnitList;
          v24 = v35;
LABEL_65:
          sBtlEntryUnitList(v23, v24);
        }
      }
      goto LABEL_66;
    default:
      goto LABEL_66;
  }
}

// 0x2078e20
s32 sBtlCheckSABFile(SKLID sklid) {
  s16 SABno;

  SABno = sBtlGetSklVisualTbl(sklid)->SABno;
  if (!SABno)
    return -1;
  return SABno;
}

// 0x2078e50
bool sBtlHDloadChk(SKLID sklid) {
  if (!sklid)
    return 1;
  if ((u16)(sBtlGetSklVisualTbl(sklid)->SABno + 1) < 2u)
    return 1;
  return sBtlLoadEffectData_ID(sklid);
}

// 0x2073c10
static f32 GetDataScale(SBTLUNIT_WORK *wk, SKLID sklid) {
  SBTLVISUAL_DATA *v5;
  SBTLVISUAL_DATA *v6;
  SBTLSKILLP_TBL *Skilltbl;
  float32x2_t v8;
  f32 result;

  v5 = Allocate(SBTLVISUAL_DATA);
  v6 = Allocate(SBTLVISUAL_DATA);
  Skilltbl = sBtlGetSkilltbl(sklid);
  if (wk->para->devilid == 260 && (Skilltbl->flg & 0x100) != 0)
    return 4.0;
  sBtlGetCylinderData_ID(0, 2, v5);
  sBtlGetCylinderData(wk, v6);
  v8.n64_u64[0] = vdiv_f32(*(float32x2_t *)&v6->width, *(float32x2_t *)&v5->width).n64_u64[0];
  result = v8.n64_f32[1];
  if (v8.n64_f32[1] >= v8.n64_f32[0])
  {
    if (v8.n64_f32[1] >= 1.5)
      result = 1.5;
  }
  else
  {
    result = v8.n64_f32[0];
    if (v8.n64_f32[0] >= 1.5)
      result = 1.5;
  }
  if (result <= 0.5)
    return 0.5;
  return result;
}

// 0x2078920
s32 sBtlCheckDisp_Helper(SBTLUNIT_WORK *wk, SKLID sklid) {
  u16 area;
  s32 result;

  area = sBtlGetSkilltbl(sklid)->area;
  if ((area & 0x10) == 0)
    return 1;
  result = 1;
  if ((area & 0x4000) != 0 && (wk->status & 0x8800) == 0x8800)
    return 2 * (wk->hithelpercsrno != 0);
  return result;
}

// 0x2078790
static bool CheckFriend_HelperData(SBTLUNIT_LISTWORK *lwk, SBTLUNIT_WORK *wk, SKLID sklid) {
  SBTLUNIT_LISTWORK *v7;
  SBTLUNIT_WORK *v8;
  u32 status;
  s64 v11;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;

  if ((sBtlGetSkilltbl(sklid)->area & 0x4000) != 0)
  {
    status = wk->status;
    if ((~status & 0x8800) == 0 || (status & 0x1000) != 0 && wk->para->devilid == 258)
    {
      v11 = 0;
      while (1)
      {
        UnitMng = wk->UnitMng;
        if (v11 >= UnitMng->number)
          break;
        pUnit = UnitMng->pUnitL[v11]->pUnit;
        if (pUnit)
        {
          if ((pUnit->status & 0xC800) == 0x8800 && pUnit->hithelpercsrno)
          {
            v7 = lwk;
            v8 = pUnit;
            goto LABEL_7;
          }
        }
        ++v11;
      }
    }
  }
  v7 = lwk;
  v8 = wk;
LABEL_7:
  sBtlEntryUnitList(v7, v8);
  return 1;
}

// 0x2076350
static bool CheckLoadEffectData(SBTLEFF_PACLIST *pac, SKLID skillid, EFFPAC_ST pacflg, void *ppData) {
  char v6;
  s16 gstat;
  Il2CppObject *v10;
  char *v11;
  pacFileHandle_t *_28877184;
  void *v14;
  void *p_pData;
  s32 SkillSE;
  SBTLEFF_PACLIST *p_fields;
  pacFileHandle_t *pacHandle;
  pacFileHandle_t *v20;
  pbResourceUnit *unit;
  s64 naturalAligment;
  void *klass;
  s64 v25;
  void *v26;
  EFFPDATA_WORK *effpdata_work;
  u32 max_length;
  SBTLEFF_PACDATAWORK *v29;
  SBTLEFF_PACDATAWORK **p_pwk;
  s64 v31;
  char v32;
  s64 v33;
  s64 v34;
  void *v35;
  s64 num;
  SBTLEFF_PACDATAWORK *v37;
  SBTLEFF_PACDATAWORK *v38;
  s32 v39;
  s64 v40;
  s64 v41;
  s64 v42;
  s64 v43;
  s64 v44;
  s64 v46;
  void *v47;
  s64 v48;
  s64 v49;
  plistHandle_t *v50;
  s64 v51;
  SBTLEFF_PACDATAWORK *v52;
  void *v53;
  s32 *sklhitid;
  s64 v55;
  SBTLEFF_PACDATAWORK *v56;
  void *v57;
  SBTLSKLHIT_PACLIST *hwk;
  u32 v59;
  SBTLSKLHIT_PACDATAWORK *v60;
  SBTLSKLHIT_PACLIST *v61;
  s64 v62;
  s64 v63;
  SBTLSKLHIT_PACDATAWORK *pwk;
  void *v65;
  SBTLSKLHIT_PACDATAWORK *v66;
  SBTLSKLHIT_PACDATAWORK *v67;
  s64 v68;
  SBATTLE_WORK2 *wk2_local;
  s16 *p_effpaccnt;
  s16 effpaccnt;
  SBTLEFF_PACLIST *v76;
  SBTLEFF_PACDATAWORK **v77;
  void *target;
  s32 data;

  v6 = pacflg;
  if ((pac->status & 1) != 0)
    goto LABEL_26;
  gstat = pac->gstat;
  if (!gstat)
  {
    if (op_Equality(ppData, 0, 0))
    {
      data = sBtlGetSklVisualTbl(skillid)->SABno;
      v10 = Box(s32, &data);
      v11 = Format("sobed_{0:x3}", v10, 0);
      _28877184 = pacLoad_2(v11);
      pac->pacHandle = _28877184;
      pac->skillID = skillid;
      goto LABEL_15;
    }
    pac->skillID = skillid;
LABEL_15:
    wk->status |= 0x20000u;
    gstat = pac->gstat + 1;
    pac->gstat = gstat;
    if (gstat == 5)
    {
LABEL_25:
      pac->status |= 1u;
LABEL_26:
      LOBYTE(SkillSE) = 1;
      return SkillSE;
    }
    goto LABEL_16;
  }
  if (pac->gstat == 5)
    goto LABEL_25;
LABEL_16:
  if (gstat == 2)
  {
    goto LABEL_23;
  }
  if (gstat != 1)
    goto LABEL_43;
  if (op_Inequality(ppData, 0, 0))
  {
    v14 = ppData;
    pac->pData = ppData;
    p_pData = &pac->pData;
    goto LABEL_46;
  }
  p_fields = &pac->fields;
  pacHandle = pac->pacHandle;
  if (!pacCheckEnd(pacHandle))
  {
LABEL_43:
    LOBYTE(SkillSE) = 0;
    return SkillSE;
  }
  v20 = p_fields->pacHandle;
  unit = pacGetResrc(v20)->unit;
  if (unit)
  {
    if (unit->klass->_2.naturalAligment < (u32)naturalAligment || unit->klass->_2.typeHierarchy[naturalAligment - 1] != Project_libsdf_pbResourceUnit_BIN)
    {
      goto LABEL_90;
    }
  }
  klass = unit[1].klass;
  if (klass)
  {
    if (klass->klass->_2.naturalAligment < (u32)v25 || klass->klass->_2.typeHierarchy[v25 - 1] != Project_dds3ResourceSAB || (pac->pData = klass, v26 = &pac->pData, klass->klass->_2.naturalAligment < (u32)v25) || klass->klass->_2.typeHierarchy[v25 - 1] != Project_dds3ResourceSAB)
    {
LABEL_42:
    }
  }
  else
  {
    pac->pData = 0;
    v26 = &pac->pData;
  }
  pacHandleFree(p_fields->pacHandle);
  p_pData = &pac->fields;
  v14 = 0;
  p_fields->pacHandle = 0;
LABEL_46:
  target = &pac->pData;
  effpdata_work = pac->pData->effpdata_work;
  ++pac->gstat;
  max_length = effpdata_work->max_length;
  pac->num = max_length;
  v29 = NewSpecific(SBTLEFF_PACDATAWORK, max_length);
  pac->pwk = v29;
  p_pwk = &pac->pwk;
  if (pac->num >= 1)
  {
    v31 = 0;
    v32 = v6;
    v33 = 32;
    do
    {
      v37 = *p_pwk;
      v38 = Allocate(SBTLEFF_PACDATAWORK);
      _ctor(v38, 0);
      *(Il2CppClass **)((char *)&v37->obj.klass + v33) = v38;
      v34 = *(s64 *)((char *)&pac->pwk->obj.klass + v33);
      v35 = *(Il2CppClass **)((char *)&pac->pData->effpdata_work->obj.klass + v33);
      *(u64 *)(v34 + 40) = v35;
      num = pac->num;
      ++v31;
      v33 += 8;
    }
    while (v31 < num);
    if ((s32)num >= 1)
    {
      v39 = 0;
      v40 = 4;
      do
      {
        v43 = *((u64 *)&(*p_pwk)->obj.klass + v40);
        v44 = *(u32 *)(*(u64 *)(v43 + 40) + 20);
        if (v40 - 4 == v44)
        {
          klass = target->eplresrc[v39]->unit[0];
          if (klass)
          {
            if (klass->klass->_2.naturalAligment < (u32)v46)
              goto LABEL_42;
            if (klass->klass->_2.typeHierarchy[v46 - 1] != plistHandle_t_Resource)
              goto LABEL_42;
            *(u64 *)(v43 + 16) = klass;
            v47 = (v43 + 16);
            if (klass->klass->_2.naturalAligment < (u32)v46 || klass->klass->_2.typeHierarchy[v46 - 1] != plistHandle_t_Resource)
            {
              goto LABEL_42;
            }
          }
          else
          {
            *(u64 *)(v43 + 16) = 0;
            v47 = (v43 + 16);
          }
          ++v39;
        }
        else
        {
          klass = (*p_pwk)[(s32)v44]->pData;
          *(u64 *)(v43 + 16) = klass;
          v47 = (v43 + 16);
        }
        v48 = *((u64 *)&(*p_pwk)->obj.klass + v40);
        v49 = *(u64 *)(v48 + 48);
        *(u32 *)(v48 + 32) = 0;
        *(u32 *)(v49 + 28) = 0;
        if ((v32 & 8) != 0)
        {
          v50 = Create(*(plistHandle_t_Resource *)(v48 + 16), 0);
          *(u64 *)(v48 + 24) = v50;
          pac->status |= 0x10u;
        }
        v41 = pac->num;
        v42 = v40 - 3;
        ++v40;
      }
      while (v42 < v41);
      if ((s32)v41 >= 1 && (v32 & 8) != 0)
      {
        v51 = 0;
        do
        {
          v52 = pac->pwk[v51];
          v52->pData = 0;
          ++v51;
        }
        while (v51 < pac->num);
      }
    }
  }
  v76 = pac;
  v77 = &pac->pwk;
  v53 = target;
  sklhitid = target->sklhitid;
  if (SLODWORD(sklhitid->max_length) >= 1)
  {
    v55 = 0;
    while (1)
    {
      v56 = (*v77)[sklhitid[v55]];
      v57 = v53->sklhitresrc[v55]->unit;
      hwk = v56->hwk;
      v59 = v57->max_length;
      hwk->num = v59;
      v60 = NewSpecific(SBTLSKLHIT_PACDATAWORK, v59);
      hwk->pwk = v60;
      v56->flg = 1;
      v61 = v56->hwk;
      if (v61->num >= 1)
        break;
LABEL_73:
      ++v55;
      v53 = target;
      sklhitid = target->sklhitid;
      if (v55 >= SLODWORD(sklhitid->max_length))
        goto LABEL_83;
    }
    v62 = 0;
    v63 = 32;
    while (1)
    {
      pwk = v61->pwk;
      v65 = *(void *)((char *)&v57->obj.klass + v63);
      v66 = Allocate(SBTLSKLHIT_PACDATAWORK);
      v67 = v66;
      if (v65)
      {
        if (v65->klass->_2.naturalAligment < (u32)v68 || v65->klass->_2.typeHierarchy[v68 - 1] != Project_SBTLSKLHIT_PACDATAWORK_Resource)
        {
          break;
        }
      }
      _ctor_32245808(v66, v65, 0);
      *(Il2CppClass **)((char *)&pwk->obj.klass + v63) = v67;
      v61 = v56->hwk;
      ++v62;
      v63 += 8;
      if (v62 >= v61->num)
        goto LABEL_73;
    }
    unit = v65;
LABEL_90:
  }
LABEL_83:
  target = 0;
  pac = v76;
  wk2_local = wk2;
  effpaccnt = wk2_local->effpaccnt;
  p_effpaccnt = &wk2_local->effpaccnt;
  *p_effpaccnt = effpaccnt + 1;
  LimitRange_2(p_effpaccnt, 0, 149);
  v76->gstat = 2;
  wk->status &= ~0x20000u;
LABEL_23:
  SkillSE = sBtlLoadSkillSE(pac);
  if (SkillSE)
  {
    pac->gstat = 5;
    goto LABEL_25;
  }
  return SkillSE;
}

// 0x20791b0
bool sBtlLoadEffectData_Player_pData(s32 point, void *pData) {
  return LoadEffectData_IDMask_pData(skltbl[point], 0x28u, pData);
}

// 0x2079230
bool EffFunc_SUMMON(SBTLEFF_WORK *wk) {
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  SBTLUNIT_WORK *v7;
  s32 v9;
  s32 counter;
  s32 battlemode;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  u32 dstcolor;
  s32 v19;
  s64 i;
  SBATTLE_WORK *v22;
  s32 PlayerID;
  SBTLUNIT_WORK *PlayerUnit;
  dds3ModelHandle_t *hModel;
  sdfVector4_t v27;

  acterID = wk->acterID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, acterID);
  v7 = v6;
  switch (wk->st)
  {
    case 1:
      if (v6 && v6->mode == 4)
      {
        if ((wk->status & 4) != 0)
        {
          v9 = 6;
          goto LABEL_61;
        }
      }
      return 1;
    case 2:
      wk->life = 82;
      effSetDirectColorMode(0.25, 0.25, 0.25, 0.25);
      LoadOnMemoryData(wk, 0, 0);
      effClearDirectColorMode();
      return 1;
    case 3:
      counter = wk->counter;
      if (counter == 1)
      {
        x = v6->pos.x;
        y = v6->pos.y;
        z = v6->pos.z;
        w = v6->pos.w;
        v27.x = x;
        v27.y = y;
        v27.z = z;
        v27.w = w;
        sBtlPlaySpecialSE(v27, 4);
        counter = wk->counter;
        if (counter != 10)
        {
LABEL_21:
          if (counter < wk->cmpcounter)
            return 1;
          goto LABEL_47;
        }
      }
      else if (counter != 10)
      {
        goto LABEL_21;
      }
      v7->mode = 5;
      if (!v7->color)
      {
        dstcolor = v7->dstcolor;
        if (dstcolor)
          v19 = dstcolor & 0xFFFFFF;
        else
          v19 = 8421504;
        v7->color = v19;
      }
      for (i = 0; i != 32; ++i)
      {
        if (wk->summonflg[i] == 1)
        {
          v22 = wk;
          if (v22->summonID[i] == v7->ListID)
          {
            v22 = wk;
            v22->summonflg[i] = 2;
          }
        }
      }
      if (wk->counter >= wk->cmpcounter)
LABEL_47:
        *(u64 *)&wk->st = 4;
      return 1;
    case 4:
      v9 = 5;
      goto LABEL_61;
    case 6:
      battlemode = (u16)wk->battlemode;
      if (battlemode == 1)
        goto LABEL_60;
      if (battlemode == 3)
        goto LABEL_60;
      PlayerID = sBtlGetPlayerID();
      PlayerUnit = sBtlGetPlayerUnit(PlayerID);
      if (PlayerUnit && PlayerUnit->motionno == 16)
      {
        hModel = PlayerUnit->hModel;
        if (mdlGetMotionFrameF(hModel) < 20.0)
          return 1;
      }
LABEL_60:
      v9 = 2;
LABEL_61:
      wk->st = v9;
      return 1;
    default:
      return 1;
  }
}

// 0x2079650
static bool EffFunc_RETURN(SBTLEFF_WORK *wk) {
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  s32 st;
  s32 counter;
  SBTLUNIT_WORK *v12;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  sdatUnitWork_t *para;
  sdfVector4_t v18;

  acterID = wk->acterID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, acterID);
  st = wk->st;
  if ((u32)(st - 1) >= 2)
  {
    if (st != 3)
    {
      if (st == 4)
        wk->st = 5;
      return 1;
    }
    counter = wk->counter;
    v12 = v6;
    if (counter == 1)
    {
      x = v6->pos.x;
      y = v6->pos.y;
      z = v6->pos.z;
      w = v6->pos.w;
      v18.x = x;
      v18.y = y;
      v18.z = z;
      v18.w = w;
      sBtlPlaySpecialSE(v18, 5);
      counter = wk->counter;
    }
    if (counter != 25 || !v12)
      goto LABEL_29;
    para = v12->para;
    if (para)
    {
      if ((v12->side & 1) != 0 && (para->flag & 2) == 0)
      {
        NakamaReturnSet(v12);
        counter = wk->counter;
        goto LABEL_29;
      }
      v12->mode = 6;
    }
    counter = 25;
LABEL_29:
    if (counter >= wk->cmpcounter)
      *(u64 *)&wk->st = 4;
    return 1;
  }
  LoadOnMemoryData(wk, 0, 0);
  return 1;
}

// 0x2079840
static void NakamaReturnSet(SBTLUNIT_WORK *wklock) {
  s64 v4;

  v4 = 0;
  wklock->mode = 6;
  wklock->actwk->next_st = 18;
  do
  {
    if (wk->summonflg[v4] == 2)
    {
      if (wk->summonID[v4] == wklock->ListID)
      {
        wk->summonflg[v4] = 0;
      }
    }
    ++v4;
  }
  while (v4 != 32);
}

// 0x2079950
static bool EffFunc_RETURN_D(SBTLEFF_WORK *wk) {
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  s32 v7;
  SBTLEFF_DATAWORK *dwk;
  s32 counter;
  SBTLUNIT_WORK *v11;
  SBTLACTION_WORK *actwk;
  s64 v14;
  SBATTLE_WORK *v15;

  acterID = wk->acterID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, acterID);
  switch (wk->st)
  {
    case 1:
      v7 = 2;
      goto LABEL_13;
    case 2:
      if ((wk->flg & 8) != 0)
        goto LABEL_12;
      dwk = wk->dwk;
      dwk->hPartsList = 0;
      wk->cmpcounter = wk->life;
      *(u64 *)&wk->st = 3;
      return 1;
    case 3:
      counter = wk->counter;
      if (counter == 10)
      {
        v11 = v6;
        v6->mode = 6;
        actwk = v6->actwk;
        v14 = 0;
        actwk->next_st = 18;
        do
        {
          if (wk->summonflg[v14] == 2)
          {
            v15 = wk;
            if (v15->summonID[v14] == v11->ListID)
            {
              v15 = wk;
              v15->summonflg[v14] = 0;
            }
          }
          ++v14;
        }
        while (v14 != 32);
        counter = wk->counter;
      }
      if (counter < wk->cmpcounter)
        return 1;
      *(u64 *)&wk->st = 4;
      return 1;
    case 4:
LABEL_12:
      v7 = 5;
LABEL_13:
      wk->st = v7;
      return 1;
    default:
      return 1;
  }
}

// 0x2079b80
bool EffFunc_SUMMON_E(SBTLEFF_WORK *wk) {
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  s32 st;
  SBTLUNIT_WORK *v8;
  s64 v9;
  s32 counter;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  u32 dstcolor;
  s32 v16;
  sdfVector4_t v18;

  acterID = wk->acterID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, acterID);
  st = wk->st;
  if (st == 4)
  {
    wk->st = 5;
  }
  else
  {
    v8 = v6;
    if (st == 3)
    {
      counter = wk->counter;
      if (counter == 1)
      {
        x = v6->pos.x;
        y = v6->pos.y;
        z = v6->pos.z;
        w = v6->pos.w;
        v18.x = x;
        v18.y = y;
        v18.z = z;
        v18.w = w;
        sBtlPlaySpecialSE(v18, 4);
        Add(v8->ListID, 0);
        counter = wk->counter;
      }
      if (counter >= wk->cmpcounter || !v8)
      {
        v9 = 4;
        goto LABEL_32;
      }
      if (counter == 10 && v8->actwk->status != 10 && !v8->changeflg)
      {
        v8->mode = 5;
        if (!v8->color)
        {
          dstcolor = v8->dstcolor;
          if (dstcolor)
            v16 = dstcolor & 0xFFFFFF;
          else
            v16 = 8421504;
          v8->color = v16;
        }
        v8->actaiwk->mode = 10;
        sBtlSetMotion(v8, 9, 0, 0, 1);
      }
    }
    else if (st == 1 && v6 && v6->mode == 4)
    {
      v9 = 3;
      wk->cmpcounter = wk->life;
LABEL_32:
      *(u64 *)&wk->st = v9;
    }
  }
  return 1;
}

// 0x2079d90
static bool EffFunc_RETURN_E(SBTLEFF_WORK *wk) {
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  s32 st;
  s32 counter;

  acterID = wk->acterID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, acterID);
  st = wk->st;
  if ((u32)(st - 1) < 2)
  {
    LoadOnMemoryData(wk, 0, 0);
    return 1;
  }
  else
  {
    if (st != 3)
    {
      if (st == 4)
        wk->st = 5;
      return 1;
    }
    counter = wk->counter;
    if (counter == 10)
    {
      v6->mode = 6;
      v6->actwk->next_st = 14;
    }
    if (counter < wk->cmpcounter)
      return 1;
    *(u64 *)&wk->st = 4;
    return 1;
  }
}

// 0x2079f00
static bool EffFunc_NMLDAMAGE(SBTLEFF_WORK *wk) {
  s32 v5;
  u32 effectid;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 acterID;
  SBTLUNIT_WORK *v10;
  SBTLUNIT_WORK *v11;
  long f64 v12;
  f32 y;
  f32 *static_fields;
  f32 x;
  f32 v18;
  f32 z;
  f32 w;
  long f64 v21;

  switch (wk->st)
  {
    case 1:
      if ((wk->status & 4) != 0)
      {
        v5 = 2;
        goto LABEL_30;
      }
      return 1;
    case 2:
      LoadOnMemoryData(wk, 0, 0);
      if (wk->st != 3)
        return 1;
      effectid = wk->effectid;
      if (effectid > 0x21 || ((1 << effectid) & 0x200008200LL) == 0)
        return 1;
      UnitMng = wk->UnitMng;
      acterID = wk->acterID;
      v10 = sBtlSearchUnit_ID(UnitMng, acterID);
      if (!v10)
        return 1;
      v11 = v10;
      if ((v10->side & 1) == 0)
        return 1;
      sBtlGetUnitHelperPos(v11, 1);
      sub_1B335A0(&wk->fields, 0, v12);
      y = wk->pos.y;
      if (y >= -1.0)
      {
        wk->pos.y = y + -50.0;
LABEL_25:
        x = static_fields[42];
        v18 = static_fields[43];
        z = static_fields[44];
        w = static_fields[45];
        goto LABEL_26;
      }
      else
      {
        goto LABEL_25;
      }
      x = CameraEyePos.x;
      v18 = CameraEyePos.y;
      z = CameraEyePos.z;
      w = CameraEyePos.w;
LABEL_26:
      sub_1B332C0(0, x, v18, z, w);
      sub_1B33360(0, wk->pos.x, wk->pos.y, wk->pos.z, wk->pos.w);
      sub_1B33400(0);
      sub_1949110(0);
      sub_1B33480(0, 15.0);
      sub_1B33360(0, wk->pos.x, wk->pos.y, wk->pos.z, wk->pos.w);
      *(__n128 *)&v21 = sub_1B33520(0);
      sub_1B335A0(&wk->fields, 0, v21);
      effPartsPositionSet(wk->dwk->hPartsList, wk->pos);
      return 1;
    case 3:
      if (wk->counter >= wk->cmpcounter)
        *(u64 *)&wk->st = 4;
      else
        effPartsScaleSet(wk->dwk->hPartsList, wk->scale);
      return 1;
    case 4:
      v5 = 5;
LABEL_30:
      wk->st = v5;
      return 1;
    default:
      return 1;
  }
}

// 0x207a250
static bool EffFunc_DEADDAMAGE(SBTLEFF_WORK *wk) {
  s32 effectid;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 acterID;
  SBTLUNIT_WORK *v10;
  SBTLUNIT_WORK *v11;
  u32 v12;
  long f64 v13;
  sdfVector4_t v14;

  switch (wk->st)
  {
    case 1:
      if ((wk->status & 4) == 0)
        return 1;
      wk->st = 2;
      return 1;
    case 2:
      LoadOnMemoryData(wk, 0, 0);
      if (wk->st == 3 && (wk->flg & 0x2000) != 0)
        ColorSet(wk->dwk->hPartsList, wk->rgb);
      return 1;
    case 3:
      effectid = wk->effectid;
      if (effectid > 6)
      {
        if ((u32)effectid > 0x32 || ((1 << effectid) & 0x4000000002C00LL) == 0)
          goto LABEL_23;
LABEL_21:
        if (wk->counter < wk->cmpcounter)
          return 1;
        goto LABEL_22;
      }
      if ((u32)effectid <= 6 && ((1 << effectid) & 0x46) != 0)
        goto LABEL_21;
LABEL_23:
      UnitMng = wk->UnitMng;
      acterID = wk->acterID;
      v10 = sBtlSearchUnit_ID(UnitMng, acterID);
      if (wk->counter >= wk->cmpcounter || (v11 = v10) == 0)
      {
LABEL_22:
        *(u64 *)&wk->st = 4;
        return 1;
      }
      v12 = wk->effectid;
      if (v12 <= 0x13 && ((1 << v12) & 0xB0000) != 0)
        effPartsRotateSet(wk->dwk->hPartsList, wk->rot);
      sBtlGetUnitHelperPos(v11, 0);
      sub_1B335A0(&wk->fields, 0, v13);
      v14.y = wk->pos.y;
      if (v14.y >= -1.0)
      {
        v14.y = v14.y + -50.0;
        wk->pos.y = v14.y;
      }
      v14.x = wk->pos.x;
      v14.z = wk->pos.z;
      v14.w = wk->pos.w;
      effPartsPositionSet(wk->dwk->hPartsList, v14);
      effPartsScaleSet(wk->dwk->hPartsList, wk->scale);
      return 1;
    case 4:
      wk->st = 5;
      return 1;
    default:
      return 1;
  }
}

// 0x207a570
static bool EffFunc_SUMMON_ED(SBTLEFF_WORK *wk) {
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  SBTLUNIT_WORK *v7;
  SBTLEFF_DATAWORK *dwk;
  s32 counter;
  u32 dstcolor;
  s32 v13;
  s32 devilid;
  s32 v15;
  s32 vstatus;
  SBTLUNIT_WORK *v18;
  s32 v19;

  acterID = wk->acterID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, acterID);
  v7 = v6;
  switch (wk->st)
  {
    case 1:
      if (!v6 || v6->mode != 4)
        return 1;
      if ((wk->status & 4) == 0)
        return 1;
      wk->st = 2;
      goto LABEL_14;
    case 2:
LABEL_14:
      if ((wk->flg & 8) != 0)
        goto LABEL_17;
      dwk = wk->dwk;
      dwk->hPartsList = 0;
      wk->cmpcounter = wk->life;
      *(u64 *)&wk->st = 3;
      return 1;
    case 3:
      counter = wk->counter;
      if (counter >= wk->cmpcounter || !v6)
      {
        *(u64 *)&wk->st = 4;
        return 1;
      }
      if (counter != 2 || v6->actwk->status == 10 || v6->changeflg)
        return 1;
      v6->mode = 5;
      if (!v6->color)
      {
        dstcolor = v6->dstcolor;
        if (dstcolor)
          v13 = dstcolor & 0xFFFFFF;
        else
          v13 = 8421504;
        v6->color = v13;
      }
      devilid = (u16)v6->para->devilid;
      if ((devilid & 0xFFFE) == 0x102)
      {
        v15 = 12;
LABEL_33:
        vstatus = v6->vstatus;
        v6->color = 0;
        v6->fadergb = v15;
        v6->vstatus = vstatus | 0x200000;
        goto LABEL_34;
      }
      v15 = 8;
      if (devilid == 297 || devilid == 290)
        goto LABEL_33;
LABEL_34:
      v6->actaiwk->mode = 10;
      if ((v6->aiwk->scrflag & 0x800000) != 0)
      {
        v19 = 9;
        v18 = v7;
      }
      else
      {
        v18 = v7;
        v19 = 0;
      }
      sBtlSetMotion(v18, v19, 0, 0, 1);
      return 1;
    case 4:
LABEL_17:
      wk->st = 5;
      return 1;
    default:
      return 1;
  }
}

// 0x207a810
static bool EffFunc_Slip_G(SBTLEFF_WORK *wk) {
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  s32 v9;
  SBTLUNIT_WORK *v10;
  SBTLEFF_WORK *p_fields;
  f32 x;
  f32 z;
  f32 GroundPos;
  s32 targetID;
  SBTLUNIT_LISTWORK *v18;
  SBTLUNIT_WORK *v19;
  s32 sklid;
  u32 v21;
  s32 v22;
  s32 v23;
  s32 devilid;
  u32 v27;
  long f64 v28;

  acterID = wk->acterID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, acterID);
  switch (wk->st)
  {
    case 1:
      if ((wk->status & 4) != 0)
      {
        v9 = 2;
        goto LABEL_33;
      }
      return 1;
    case 2:
      LoadOnMemoryData(wk, 0, 0);
      return 1;
    case 3:
      v10 = v6;
      if (!v6)
      {
        *(u64 *)&wk->st = 4;
        return 1;
      }
      sBtlGetUnitHelperPos(v10, 0);
      p_fields = &wk->fields;
      p_fields->pos = vct_A;
      x = wk->pos.x;
      z = wk->pos.z;
      GroundPos = sBtlGetGroundPos(x, z);
      wk->pos.y = GroundPos;
      targetID = wk->targetID;
      v18 = wk->UnitMng;
      v19 = sBtlSearchUnit_ID(v18, targetID);
      if (!v19)
        goto LABEL_53;
      sklid = wk->sklid;
      if (sklid <= 53)
      {
        if (sklid > 21)
        {
          if (((1 << sklid) & 0x30003000000000LL) != 0)
            goto LABEL_47;
          goto LABEL_58;
        }
        if ((u32)sklid > 0x15)
          goto LABEL_58;
        v22 = 1 << sklid;
        v23 = 3145824;
        goto LABEL_46;
      }
      if ((u32)sklid > 0x183)
      {
        v21 = sklid - 390;
        if (v21 > 9)
          goto LABEL_58;
        v22 = 1 << v21;
        v23 = 547;
LABEL_46:
        if ((v22 & v23) != 0)
          goto LABEL_47;
        goto LABEL_58;
      }
      if (sklid == 56 || sklid == 387)
      {
LABEL_47:
        sBtlGetUnitHelperPos(v10, 0);
        p_fields->pos = vct_A;
        goto LABEL_53;
      }
LABEL_58:
      devilid = v19->para->devilid;
      if (devilid <= 242)
      {
        if (devilid <= 175)
        {
          if (devilid != 154)
          {
            v27 = devilid - 168;
            if (v27 > 7 || ((1 << v27) & 0xC3) == 0)
              goto LABEL_53;
          }
        }
        else if ((u32)(u16)v19->para->devilid - 187 > 0x37 || ((1 << ((u8)v19->para->devilid + 69)) & 0x80080000000001LL) == 0)
        {
          goto LABEL_53;
        }
      }
      else if ((u32)devilid <= 0x11D)
      {
        if (devilid != 262 && devilid != 285 && (devilid & 0xFFFFFFFE) != 0x10C)
          goto LABEL_53;
      }
      else if ((u32)devilid <= 0x12C)
      {
        if (devilid != 291 && v19->para->devilid != 300)
          goto LABEL_53;
      }
      else if (devilid != 308 && (devilid & 0xFFFFFFFE) != 0x130)
      {
        goto LABEL_53;
      }
      if (wk->effectid == 55)
      {
        sBtlGetUnitHelperPos(v10, 0);
        sub_1B335A0(p_fields, 0, v28);
      }
LABEL_53:
      effPartsPositionSet(wk->dwk->hPartsList, wk->pos);
      return 1;
    case 4:
      v9 = 5;
LABEL_33:
      wk->st = v9;
      return 1;
    default:
      return 1;
  }
}

// 0x207ad20
bool EffFunc_Hanyou(SBTLEFF_WORK *wk) {
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  SBTLUNIT_WORK *v8;
  s32 v10;
  s32 effectid;
  u32 devilid;
  bool v13;
  s64 v14;
  SBTLDMG_HITLISTWORK *hitList;
  s32 hitserialID;
  SBTLDMG_HITWORK *v19;
  SBTLEFF_WORK *p_fields;
  SBTLEFF_DATAWORK *dwk;
  struct sdfVector4_t pos;

  acterID = wk->acterID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, acterID);
  v8 = v6;
  switch (wk->st)
  {
    case 1:
      if ((wk->status & 4) != 0)
      {
        v10 = 2;
        goto LABEL_40;
      }
      return 1;
    case 2:
      LoadOnMemoryData(wk, 0, 0);
      if (wk->st == 3)
      {
        effectid = wk->effectid;
        if (effectid == 46 || effectid == 40)
        {
          if (v8)
          {
            devilid = (u16)v8->para->devilid;
            v13 = devilid > 0x3C;
            v14 = (1 << devilid) & 0x1020200000000000LL;
            if (!v13 && v14 != 0)
              effPartsColorSet(wk->dwk->hPartsList, 0x80808080);
          }
        }
      }
      return 1;
    case 3:
      if (!(wk->counter >= wk->cmpcounter || !v6))
      {
        if ((wk->flg & 0x200) == 0)
          return 1;
        hitList = wk->hitList;
        hitserialID = wk->hitserialID;
        v19 = sBtlSearchHit_SerialID(hitList, hitserialID);
        if (v19)
        {
          pos = v19->pos;
          vct_A = pos;
          p_fields = &wk->fields;
          dwk = wk->dwk;
          p_fields->pos = vct_A;
          effPartsPositionSet(dwk->hPartsList, wk->pos);
          return 1;
        }
      }
      *(u64 *)&wk->st = 4;
      return 1;
    case 4:
      v10 = 5;
LABEL_40:
      wk->st = v10;
      return 1;
    default:
      return 1;
  }
}

// 0x207b070
static bool EffFunc_Hanyou_BED(SBTLEFF_WORK *wk) {
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v7;
  s32 BEDsklid;
  s32 v11;
  s32 v12;
  SBTLUNIT_WORK *v13;
  SBATTLE_WORK *v15;
  SBTLUNIT_LISTWORK *v16;
  s32 playerID;
  SBTLUNIT_WORK *v18;
  f32 x;
  f32 v20;
  f32 v21;
  f32 v24;
  f32 y;
  f32 w;
  f32 z;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 v41;
  f32 v42;
  f32 v43;
  s32 cmpcounter;
  s32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 v53;
  s32 v55;
  void *hPartsList;
  f32 v57;
  f32 v58;
  f32 v59;
  f32 v60;
  f32 v61;
  f32 v62;
  u32 alpha_low;
  u32 flg;
  s32 helperno;
  _OWORD *p_x;
  __int128 v69;
  __int128 v70;
  SBTLEFF_DATAWORK *dwk;
  SBTLDMG_HITLISTWORK *hitList;
  s32 hitserialID;
  SBTLDMG_HITWORK *v76;
  SBTLDMG_HITWORK *v77;
  sdfVector4_t *p_rot;
  SBTLEFF_DATAWORK *v80;
  struct sdfVector4_t v81;
  SBTLEFF_WORK *p_fields;
  SBTLEFF_DATAWORK *v84;
  s32 v85;
  SBTLEFF_WORK *v87;
  SBTLEFF_DATAWORK *v88;
  struct sdfVector4_t v90;
  sdfMatrix4_t v93;
  sdfVector4_t rot;
  sdfVector4_t pos;
  sdfVector4_t v96;
  sdfVector4_t v97;
  sdfVector4_t v98;
  sdfVector4_t v99;
  sdfVector4_t v100;
  sdfVector4_t v101;
  sdfVector4_t v102;
  sdfVector4_t v103;
  sdfVector4_t v104;
  sdfVector4_t v105;

  *(u64 *)&pos.x = 0;
  *(u64 *)&pos.z = 0;
  *(u64 *)&rot.x = 0;
  *(u64 *)&rot.z = 0;
  acterID = wk->acterID;
  UnitMng = wk->UnitMng;
  v7 = sBtlSearchUnit_ID(UnitMng, acterID);
  switch (wk->st)
  {
    case 1:
      if ((wk->status & 4) == 0)
        return 1;
      wk->st = 2;
      BEDsklid = wk->BEDsklid;
      if ((u32)(BEDsklid - 228) <= 9)
      {
        v11 = 1 << (BEDsklid + 28);
        if ((v11 & 0x83) != 0)
          goto LABEL_16;
        if ((v11 & 0x300) != 0)
          goto LABEL_17;
      }
      if ((u32)(BEDsklid - 498) < 2)
        goto LABEL_17;
      if (BEDsklid == 474)
      {
LABEL_16:
        wk->pos.y = 9999.0;
        if ((BEDsklid & 0xFFFFFFFE) == 0xEC)
        {
LABEL_17:
          if ((u32)(wk->BEDno - 2) <= 6)
            wk->pos.y = 9999.0;
        }
      }
      return 1;
    case 2:
      LoadOnMemoryData_BED(wk, 0, 0);
      return 1;
    case 3:
      v12 = wk->BEDsklid;
      v13 = v7;
      if ((u32)(v12 - 458) <= 2)
      {
        if (wk->BEDno || wk->counter != 205)
          goto LABEL_55;
        v15 = wk;
        v16 = v15->UnitMng;
        playerID = v15->playerID;
        v18 = sBtlSearchUnit_ID(v16, playerID);
        x = v18->pos.x;
        v20 = v18->pos.y + -200.0;
        v21 = v18->pos.z + 1000.0;
        v96.w = 0.0;
        v96.x = x;
        v96.y = v20;
        v96.z = v21;
        sBtlPlay3DSE(0x5020019u, v96);
        v12 = wk->BEDsklid;
      }
      if (v12 == 465)
      {
        if (wk->BEDno > 1u || wk->counter != 1)
          goto LABEL_69;
        sBtlGetPointData(sklid_BS14_target, &pos, &rot);
        v24 = pos.x;
        y = pos.y;
        z = pos.z;
        w = pos.w;
        v97.x = v24;
        v97.y = y;
        v97.z = z;
        v97.w = w;
        sBtlPlay3DSE(0x503001Bu, v97);
        v12 = wk->BEDsklid;
      }
      if (v12 == 466)
      {
        if (wk->BEDno || wk->counter != 2)
          goto LABEL_69;
        v28 = wk->pos.x;
        v29 = wk->pos.y;
        v31 = wk->pos.z;
        v30 = wk->pos.w;
        v98.x = v28;
        v98.y = v29;
        v98.z = v31;
        v98.w = v30;
        sBtlPlay3DSE(0x503001Du, v98);
        v12 = wk->BEDsklid;
      }
      if (v12 != 464)
        goto LABEL_55;
      if (wk->BEDno != 4 || wk->counter != 1)
        goto LABEL_69;
      v32 = wk->pos.x;
      v33 = wk->pos.y;
      v35 = wk->pos.z;
      v34 = wk->pos.w;
      v99.x = v32;
      v99.y = v33;
      v99.z = v35;
      v99.w = v34;
      sBtlPlay3DSE(0x8D00001u, v99);
      v12 = wk->BEDsklid;
LABEL_55:
      if (((u32)(v12 - 228) > 7 || ((1 << (v12 + 28)) & 0x83) == 0) && v12 != 474)
        goto LABEL_63;
      if (!wk->BEDno && wk->counter == 2)
      {
        v36 = wk->pos.x;
        v37 = wk->pos.y;
        v39 = wk->pos.z;
        v38 = wk->pos.w;
        v100.x = v36;
        v100.y = v37;
        v100.z = v39;
        v100.w = v38;
        sBtlPlay3DSE(0x503001Eu, v100);
        v12 = wk->BEDsklid;
LABEL_63:
        if (v12 == 79 && !wk->BEDno && wk->counter == 2)
        {
          v40 = wk->pos.x;
          v41 = wk->pos.y;
          v43 = wk->pos.z;
          v42 = wk->pos.w;
          v101.x = v40;
          v101.y = v41;
          v101.z = v43;
          v101.w = v42;
          sBtlPlay3DSE(0x5040013u, v101);
        }
      }
LABEL_69:
      cmpcounter = wk->cmpcounter;
      if (cmpcounter && wk->counter >= cmpcounter)
        goto LABEL_142;
      v45 = wk->BEDsklid;
      if (v45 == 440)
      {
        if (wk->BEDno != 2 || wk->counter != 2)
        {
          v45 = 440;
          goto LABEL_85;
        }
        v46 = wk->pos.x;
        v47 = wk->pos.y;
        v49 = wk->pos.z;
        v48 = wk->pos.w;
        v102.x = v46;
        v102.y = v47;
        v102.z = v49;
        v102.w = v48;
        sBtlPlaySkillSE(v102, 440, 2);
        v45 = wk->BEDsklid;
      }
      if (v45 != 439)
        goto LABEL_83;
      if (wk->BEDno || wk->counter != 95)
      {
        v45 = 439;
        goto LABEL_85;
      }
      else
      {
        v50 = wk->pos.x;
        v51 = wk->pos.y;
        v53 = wk->pos.z;
        v52 = wk->pos.w;
        v103.x = v50;
        v103.y = v51;
        v103.z = v53;
        v103.w = v52;
        sBtlPlaySkillSE(v103, 439, 2);
        v45 = wk->BEDsklid;
LABEL_83:
        if (v45 == 441)
          goto LABEL_98;
LABEL_85:
        if ((u32)(v45 - 289) < 0xC)
          goto LABEL_98;
        goto LABEL_95;
      }
      if ((u32)(wk->BEDsklid - 289) < 0xC)
        goto LABEL_98;
LABEL_95:
      if (!wk->cmpcounter && !wk->life && wk->counter >= 600)
      {
LABEL_142:
        *(u64 *)&wk->st = 4;
        return 1;
      }
LABEL_98:
      v60 = wk->rgb.x;
      v61 = wk->rgb.y;
      v62 = wk->rgb.z;
      alpha_low = LOBYTE(wk->alpha);
      v105.z = v62;
      v105.w = (f32)alpha_low * 0.0078125;
      v105.x = v60;
      v105.y = v61;
      ColorSet(wk->dwk->hPartsList, v105);
      flg = wk->flg;
      if (!((flg & 0x800) == 0 || !v13))
      {
        helperno = wk->helperno;
        sBtlGetUnitHelperMatrix(v13, helperno);
        p_x = &vf00.x;
        v69 = p_x[5];
        *(_OWORD *)&v93.m00 = p_x[4];
        *(_OWORD *)&v93.m01 = v69;
        v70 = p_x[7];
        *(_OWORD *)&v93.m02 = p_x[6];
        *(_OWORD *)&v93.m03 = v70;
        sBtlGetQuatFromMatrix(&v93);
        dwk = wk->dwk;
        wk->rot = vct_A;
        effPartsRotateSet(dwk->hPartsList, wk->rot);
        flg = wk->flg;
      }
      if ((flg & 0x200) != 0)
      {
        hitList = wk->hitList;
        hitserialID = wk->hitserialID;
        v76 = sBtlSearchHit_SerialID(hitList, hitserialID);
        if (!v76)
          return 1;
        v77 = v76;
        v90 = v76->rot;
        vct_A = v90;
        p_rot = &wk->rot;
        v80 = wk->dwk;
        *p_rot = vct_A;
        effPartsRotateSet(v80->hPartsList, wk->rot);
        v81 = v77->pos;
        vct_A = v81;
        p_fields = &wk->fields;
        v84 = wk->dwk;
        p_fields->pos = vct_A;
        effPartsPositionSet(v84->hPartsList, wk->pos);
        flg = wk->flg;
      }
      if (!((flg & 0x800) == 0 || (flg & 0x200) != 0 || !v13))
      {
        v85 = wk->helperno;
        sBtlGetUnitHelperPos(v13, v85);
        v87 = &wk->fields;
        v88 = wk->dwk;
        v87->pos = vct_A;
        effPartsPositionSet(v88->hPartsList, wk->pos);
        flg = wk->flg;
      }
      if ((flg & 0x1200) == 0x1000 && v13)
      {
        SetEffectPos(wk, v13);
        effPartsRotateSet(wk->dwk->hPartsList, wk->rot);
        effPartsPositionSet(wk->dwk->hPartsList, wk->pos);
      }
      return 1;
    case 4:
      v55 = wk->alpha - wk->alpha_cnt;
      wk->alpha = v55;
      if (v55 <= 0)
      {
        wk->alpha = 0;
        wk->st = 5;
      }
      else
      {
        hPartsList = wk->dwk->hPartsList;
        if (hPartsList)
        {
          v57 = wk->rgb.x;
          v58 = wk->rgb.y;
          v59 = wk->rgb.z;
          hPartsList = wk->dwk->hPartsList;
          v104.z = v59;
          v104.w = (f32)(u8)v55 * 0.0078125;
          v104.x = v57;
          v104.y = v58;
          ColorSet(hPartsList, v104);
        }
      }
      return 1;
    default:
      return 1;
  }
}

// 0x207bcb0
static bool IsBstEffect(SBTLEFF_WORK *wk) {
  return (u32)(wk->BEDsklid - 289) < 0xC;
}

// 0x207bcd0
static bool EffFunc_SUMMON_ND(SBTLEFF_WORK *wk) {
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  SBTLUNIT_WORK *v7;
  s32 v8;
  SBTLEFF_DATAWORK *dwk;
  s32 counter;
  u32 dstcolor;
  s32 v13;
  s64 i;
  SBATTLE_WORK *v16;

  acterID = wk->acterID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, acterID);
  v7 = v6;
  switch (wk->st)
  {
    case 1:
      if (!v6 || v6->mode != 4)
        return 1;
      v8 = 2;
      goto LABEL_15;
    case 2:
      if ((wk->flg & 8) != 0)
        goto LABEL_14;
      dwk = wk->dwk;
      dwk->hPartsList = 0;
      wk->cmpcounter = wk->life;
      *(u64 *)&wk->st = 3;
      return 1;
    case 3:
      counter = wk->counter;
      if (counter == 10)
      {
        v6->mode = 5;
        if (!v6->color)
        {
          dstcolor = v6->dstcolor;
          if (dstcolor)
            v13 = dstcolor & 0xFFFFFF;
          else
            v13 = 8421504;
          v6->color = v13;
        }
        for (i = 0; i != 32; ++i)
        {
          if (wk->summonflg[i] == 1)
          {
            v16 = wk;
            if (v16->summonID[i] == v7->ListID)
            {
              v16 = wk;
              v16->summonflg[i] = 2;
            }
          }
        }
        counter = wk->counter;
      }
      if (counter < wk->cmpcounter)
        return 1;
      *(u64 *)&wk->st = 4;
      return 1;
    case 4:
LABEL_14:
      v8 = 5;
LABEL_15:
      wk->st = v8;
      return 1;
    default:
      return 1;
  }
}

// 0x207bf30
static bool EffFunc_GuardC(SBTLEFF_WORK *wk) {
  bool result;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 acterID;
  SBTLUNIT_WORK *v9;

  switch (wk->st)
  {
    case 1:
      if ((wk->status & 4) == 0)
        goto LABEL_11;
      wk->st = 2;
      return 1;
    case 2:
      LoadOnMemoryData(wk, 0, 0);
      goto LABEL_11;
    case 3:
      UnitMng = wk->UnitMng;
      acterID = wk->acterID;
      v9 = sBtlSearchUnit_ID(UnitMng, acterID);
      if (wk->counter < wk->cmpcounter && v9)
        goto LABEL_11;
      *(u64 *)&wk->st = 4;
      result = 1;
      break;
    case 4:
      wk->st = 5;
      return 1;
    default:
LABEL_11:
      result = 1;
      break;
  }
  return result;
}

// 0x207c0d0
static bool EffFunc_Sword(SBTLEFF_WORK *wk) {
  dds3ModelHandle_t *v3;
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v10;
  SBTLUNIT_LISTWORK *v11;
  SBTLUNIT_WORK *v12;
  SBTLUNIT_WORK *v13;
  SBATTLE_WORK *v15;
  s32 motionno;
  SBTLEFF_WORK *p_sword_eff;
  Il2CppObject *ModelHandle;
  long f64 v21;
  s64 v22;
  long f64 v23;
  long f64 v24;
  sdfMatrix4_t v25;
  sdfMatrix4_t v26;
  sdfMatrix4_t v27;
  sdfVector4_t v28;

  memset(&v27, 0, sizeof(v27));
  v3 = Allocate(dds3ModelHandle_t);
  _ctor(v3, 0);
  acterID = wk->acterID;
  UnitMng = wk->UnitMng;
  sBtlSearchUnit_ID(UnitMng, acterID);
  switch (wk->st)
  {
    case 1:
      if ((wk->status & 4) != 0)
        wk->st = 2;
      return 1;
    case 2:
      LoadOnMemoryData(wk, 0, 0);
      return 1;
    case 3:
      v10 = wk->acterID;
      v11 = wk->UnitMng;
      v12 = sBtlSearchUnit_ID(v11, v10);
      if (!v12)
      {
        wk->st = 4;
        return 1;
      }
      v13 = v12;
      v15 = wk;
      if (v15->sword_eff != wk)
        goto LABEL_22;
      v15 = wk;
      if (!v15->cmbSkl->tateLv)
      {
LABEL_22:
        if ((v13->vstatus & 0x1000) == 0)
        {
          motionno = v13->motionno;
          if (motionno <= 23)
          {
            if ((u32)motionno > 0x17 || ((1 << motionno) & 0xC02000) == 0)
              goto LABEL_41;
          }
          else if ((u32)motionno > 0x25 || ((1 << motionno) & 0x3806000000LL) == 0)
          {
LABEL_41:
            ModelHandle = dds3ObjectBaseGetModelHandle(&v13->pBasic);
            v22 = sub_83F0(ModelHandle, dds3ModelHandle_t, v21);
            sdfModelGetMarkPos(*(sdfModelRootNode_t *)(v22 + 64), 110);
            sub_1B335A0(&wk->fields, 0, v23);
            sdfModelGetMarkPosMatrix(*(sdfModelRootNode_t *)(v22 + 64), 110);
            sub_1B33C90(&v27, 0);
            v26 = v27;
            v25 = v26;
            sBtlGetQuatFromMatrix(&v25);
            sub_1B335A0(&wk->rot, 0, v24);
            v28.z = wk->pos.z;
            goto LABEL_39;
          }
        }
      }
      wk->pos.z = 100000.0;
      v28.z = 100000.0;
LABEL_39:
      v28.w = wk->pos.w;
      v28.x = wk->pos.x;
      v28.y = wk->pos.y;
      effPartsPositionSet(wk->dwk->hPartsList, v28);
      effPartsRotateSet(wk->dwk->hPartsList, wk->rot);
      return 1;
    case 4:
      wk->st = 5;
      p_sword_eff = &wk->sword_eff;
      p_sword_eff = 0;
      return 1;
    default:
      return 1;
  }
}

// 0x207c4b0
static bool EffFunc_GunL(SBTLEFF_WORK *wk) {
  dds3ModelHandle_t *v3;
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v9;
  s32 v11;
  SBTLUNIT_LISTWORK *v12;
  SBTLUNIT_WORK *v13;
  sdfModelRootNode_t *ModelHandle;
  sdfModelRootNode_t *v15;
  s64 naturalAligment;
  SBTLEFF_WORK *p_fields;
  _OWORD *p_x;
  __int128 v21;
  __int128 v22;
  SBTLEFF_DATAWORK *dwk;
  SBTLEFF_WORK *p_sword_eff;
  sdfMatrix4_t v28;
  sdfMatrix4_t v29;
  sdfVector4_t v30;

  v3 = Allocate(dds3ModelHandle_t);
  _ctor(v3, 0);
  acterID = wk->acterID;
  UnitMng = wk->UnitMng;
  sBtlSearchUnit_ID(UnitMng, acterID);
  switch (wk->st)
  {
    case 1:
      if ((wk->status & 4) != 0)
      {
        v9 = 2;
        goto LABEL_41;
      }
      return 1;
    case 2:
      LoadOnMemoryData(wk, 0, 0);
      return 1;
    case 3:
      v11 = wk->acterID;
      v12 = wk->UnitMng;
      v13 = sBtlSearchUnit_ID(v12, v11);
      if (v13)
      {
        ModelHandle = dds3ObjectBaseGetModelHandle(&v13->pBasic);
        v15 = ModelHandle;
        if (ModelHandle)
        {
          LOBYTE(ModelHandle[1].tm.m00) < (u32)naturalAligment || *((dds3ModelHandle_t **)(ModelHandle)->extraData + naturalAligment - 1) != dds3ModelHandle_t;
        }
        sdfModelGetMarkPos(ModelHandle[8], 41);
        p_fields = &wk->fields;
        p_fields->pos = vct_A;
        sdfModelGetMarkPosMatrix(v15[8], 41);
        p_x = &vf00.x;
        v21 = p_x[5];
        *(_OWORD *)&v29.m00 = p_x[4];
        *(_OWORD *)&v29.m01 = v21;
        v22 = p_x[7];
        *(_OWORD *)&v29.m02 = p_x[6];
        *(_OWORD *)&v29.m03 = v22;
        v28 = v29;
        sBtlGetQuatFromMatrix(&v28);
        dwk = wk->dwk;
        v30.z = wk->pos.z;
        v30.w = wk->pos.w;
        wk->rot = vct_A;
        v30.x = wk->pos.x;
        v30.y = wk->pos.y;
        effPartsPositionSet(dwk->hPartsList, v30);
        effPartsRotateSet(wk->dwk->hPartsList, wk->rot);
        return 1;
      }
      v9 = 4;
LABEL_41:
      wk->st = v9;
      return 1;
    case 4:
      wk->st = 5;
      p_sword_eff = &wk->sword_eff;
      p_sword_eff = 0;
      return 1;
    default:
      return 1;
  }
}

// 0x207c8a0
static bool EffFunc_GunR(SBTLEFF_WORK *wk) {
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  s32 v9;
  sdfModelRootNode_t *ModelHandle;
  sdfModelRootNode_t *v11;
  s64 naturalAligment;
  SBTLEFF_WORK *p_fields;
  _OWORD *p_x;
  __int128 v17;
  __int128 v18;
  SBTLEFF_DATAWORK *dwk;
  SBTLEFF_WORK *p_sword_eff;
  sdfMatrix4_t v24;
  sdfMatrix4_t v25;
  sdfVector4_t v26;

  acterID = wk->acterID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, acterID);
  switch (wk->st)
  {
    case 1:
      if ((wk->status & 4) != 0)
      {
        v9 = 2;
        goto LABEL_37;
      }
      return 1;
    case 2:
      LoadOnMemoryData(wk, 0, 0);
      return 1;
    case 3:
      if (v6)
      {
        ModelHandle = dds3ObjectBaseGetModelHandle(&v6->pBasic);
        v11 = ModelHandle;
        if (ModelHandle)
        {
          LOBYTE(ModelHandle[1].tm.m00) < (u32)naturalAligment || *((dds3ModelHandle_t **)(ModelHandle)->extraData + naturalAligment - 1) != dds3ModelHandle_t;
        }
        sdfModelGetMarkPos(ModelHandle[8], 42);
        p_fields = &wk->fields;
        p_fields->pos = vct_A;
        sdfModelGetMarkPosMatrix(v11[8], 42);
        p_x = &vf00.x;
        v17 = p_x[5];
        *(_OWORD *)&v25.m00 = p_x[4];
        *(_OWORD *)&v25.m01 = v17;
        v18 = p_x[7];
        *(_OWORD *)&v25.m02 = p_x[6];
        *(_OWORD *)&v25.m03 = v18;
        v24 = v25;
        sBtlGetQuatFromMatrix(&v24);
        dwk = wk->dwk;
        v26.z = wk->pos.z;
        v26.w = wk->pos.w;
        wk->rot = vct_A;
        v26.x = wk->pos.x;
        v26.y = wk->pos.y;
        effPartsPositionSet(dwk->hPartsList, v26);
        effPartsRotateSet(wk->dwk->hPartsList, wk->rot);
        return 1;
      }
      v9 = 4;
LABEL_37:
      wk->st = v9;
      return 1;
    case 4:
      wk->st = 5;
      p_sword_eff = &wk->sword_eff;
      p_sword_eff = 0;
      return 1;
    default:
      return 1;
  }
}

// 0x207cc30
bool EffFunc_TateBg(SBTLEFF_WORK *wk) {
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  s32 v9;
  SBTLUNIT_WORK *v10;
  s32 effectid;
  u32 devilid;
  bool v13;
  s64 v14;
  SBTLDMG_HITLISTWORK *hitList;
  s32 hitserialID;
  SBTLDMG_HITWORK *v19;
  SBTLEFF_WORK *p_fields;
  SBTLEFF_DATAWORK *dwk;
  struct sdfVector4_t pos;

  acterID = wk->acterID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, acterID);
  switch (wk->st)
  {
    case 1:
      if ((wk->status & 4) != 0)
      {
        v9 = 2;
        goto LABEL_38;
      }
      return 1;
    case 2:
      v10 = v6;
      LoadOnMemoryData(wk, 0, 0);
      if (wk->st == 3)
      {
        effectid = wk->effectid;
        if (effectid == 46 || effectid == 40)
        {
          if (v10)
          {
            devilid = (u16)v10->para->devilid;
            v13 = devilid > 0x3C;
            v14 = (1 << devilid) & 0x1020200000000000LL;
            if (!v13 && v14 != 0)
              effPartsColorSet(wk->dwk->hPartsList, 0x80808080);
          }
        }
      }
      return 1;
    case 3:
      if ((wk->flg & 0x200) == 0)
        return 1;
      hitList = wk->hitList;
      hitserialID = wk->hitserialID;
      v19 = sBtlSearchHit_SerialID(hitList, hitserialID);
      if (v19)
      {
        pos = v19->pos;
        vct_A = pos;
        p_fields = &wk->fields;
        dwk = wk->dwk;
        p_fields->pos = vct_A;
        effPartsPositionSet(dwk->hPartsList, wk->pos);
        return 1;
      }
      *(u64 *)&wk->st = 4;
      return 1;
    case 4:
      v9 = 5;
LABEL_38:
      wk->st = v9;
      return 1;
    default:
      return 1;
  }
}

// 0x2073bd0
bool sBtlCheckBEDType(SBTLEFF_BEDTYPE cmp, SBTLEFF_BEDTYPE in) {
  if (in <= 1u)
  {
    if (cmp > (u32)in)
      return 0;
  }
  else if (cmp != in)
  {
    return 0;
  }
  return 1;
}

// 0x207cf70
bool sBtlOnDataLoadInit_Pac1(void) {
  s64 i;
  s64 v2;
  s64 v3;
  s64 v4;
  pacFileHandle_t *_28877184;
  sdfPacDecodeResrcHandle_t *Resrc;
  sdfPacDecodeResrcHandle_t *next;
  SBTLEFF_DATAWORK *p_fields;
  s64 userId;
  s32 v12;
  void **p_klass;
  u64 *v15;
  SBTLEFF_DATAWORK *v18;
  plistHandle_t_Resource *v19;

  for (i = 32; i != 400; i += 8)
  {
    v2 = *(s64 *)((char *)&wkeffOnMem->obj.klass + i);
    *(u64 *)(v2 + 16) = 0;
    v3 = *(s64 *)((char *)&wkeffOnMem->obj.klass + i);
    *(u64 *)(v3 + 24) = 0;
    v4 = *(s64 *)((char *)&wkeffOnMem->obj.klass + i);
    *(u64 *)(v4 + 32) = 0;
  }
  _28877184 = pacLoad_2("sb_pack4");
  pacSync(_28877184);
  Resrc = pacGetResrc(_28877184);
  if (Resrc)
  {
    next = Resrc;
    do
    {
      userId = next->header->userId;
      v12 = (u8)sbtl_effonfilecheck[userId];
      if (!sbtl_effonfilecheck[userId])
        goto LABEL_22;
      if (v12 == 2)
        goto LABEL_22;
      goto LABEL_9000;
      if (sbtl_effonfilecheck[userId] == 2)
      {
LABEL_22:
        p_klass = &next->unit->klass;
        v15 = p_klass[4];
        v18 = wkeffOnMem[userId];
        v19 = *(plistHandle_t_Resource *)(v15[3] + 32);
        if (!v19)
        {
          v18->pData = 0;
          p_fields = &v18->fields;
        }
      }
LABEL_9000:
      next = next->next;
    }
    while (next);
  }
  pacHandleFree(_28877184);
  return 1;
}

// 0x207d2c0
bool sBtlOnDataLoadInit(void) {
  dds3ProcessFunc_t v1;
  shutdownfuncDelegate v2;
  dds3ProcessFunc_t v3;

  v1 = Allocate(dds3ProcessFunc_t);
  _ctor(v1, 0, Method_Project_sBtlEff_OnDataLoadProc__, 0);
  v2 = Allocate(shutdownfuncDelegate);
  _ctor(v2, 0, Method_Project_sBtlEff_OnDataLoadShutdown__, 0);
  dds3StartProcess("sbtleffonmem_load", 1016, 1, 1, v1, v2, 0);
  v3 = Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_sBtlEff_LoadEffectData_BadStatusProc__, 0);
  dds3StartProcess("BadStatus_pData", 1016, 1, 1, v3, 0, 0);
  return 1;
}

// 0x207d460
static bool LoadEffectData_BadStatus_pData(void) {
  s64 v2;
  bool EffectData_IDMask;
  s64 v5;
  s64 max_length_low;

  v2 = 0;
  do
  {
    v5 = v2;
    max_length_low = SLODWORD(aDirectEff->max_length);
    if (v5 >= max_length_low)
      break;
    EffectData_IDMask = sBtlLoadEffectData_IDMask(aDirectEff[v5], 0xCu);
    v2 = v5 + 1;
  }
  while (EffectData_IDMask);
  return v5 >= max_length_low;
}

// 0x207d970
static dds3ProcessFunc_t LoadEffectData_BadStatusProc(dds3ProcessID_t *id) {
  s64 v4;
  dds3ProcessFunc_t v9;

  v4 = 0;
  while (1)
  {
    if (v4 >= SLODWORD(aDirectEff->max_length))
      break;
    if (!sBtlLoadEffectData_IDMask(aDirectEff[v4++], 0xCu))
      return 0;
  }
  v9 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v9, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
  return v9;
}

// 0x207dac0
bool sBtlLoadEffectData_Decode(SBTLUNIT_WORK *wk) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  SBTLUNIT_WORK *pUnit;
  s32 side;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    number = UnitMng->number;
    if (i >= number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((u32)(pUnit->mode - 1) >= 2 && (!wk || wk->ListID == pUnit->ListID))
    {
      side = pUnit->side;
      if ((side & 0x80) == 0)
      {
        if ((side & 2) != 0)
        {
          if (pUnit->para->devilid == 292)
          {
            if (!sBtlLoadEffectData(pUnit))
              return i >= number;
          }
        }
        {
          if (!sBtlLoadEffectData_Nakama(pUnit))
            return i >= number;
        }
        else
        {
          if (!sBtlLoadEffectData_Nakama(pUnit))
            return i >= number;
        }
      }
    }
  }
  return i >= number;
}

// 0x207e290
bool sBtlLoadEffectData_Decode_FastLoad_Nakama(SBTLUNIT_WORK *wklock) {
  if (!wklock || (wklock->side & 1) == 0)
    return 1;
  if (sBtlLoadEffectData_Nakama(wklock))
    return 1;
  return 0;
}

// 0x207e320
bool sBtlInitLoadPlayerOnMemData(void) {
  SBTLEFF_PACFILE_EPL *effOnRsc_P;
  pacFileHandle_t *_28877184;
  SBTLEFF_PACFILE_EPL *v4;
  pacFileHandle_t *pacHandle;

  effOnRsc_P = wk2->effOnRsc_P;
  _28877184 = pacLoad_2("sb_pack3");
  effOnRsc_P->pacHandle = _28877184;
  v4 = wk2->effOnRsc_P;
  pacHandle = v4->pacHandle;
  *(u64 *)&v4->setflg = 0;
  pacSync(pacHandle);
  return 1;
}

// 0x207e400
bool sBtlLoadEndCheck_PlayerOnMemData(void) {
  SBTLEFF_PACFILE_EPL *effOnRsc_P;
  pacFileHandle_t *pacHandle;

  effOnRsc_P = wk2->effOnRsc_P;
  if (effOnRsc_P->setflg)
    return 1;
  pacHandle = effOnRsc_P->pacHandle;
  return pacCheckEnd(pacHandle);
}

// 0x207e520
bool sBtlLoadPlayerOnMemData(void) {
  pacFileHandle_t *pacHandle;
  sdfPacDecodeResrcHandle_t *Resrc;
  SBTLEFF_PACFILE_EPL *effOnRsc_P;
  s64 data_cnt;
  void *v9;
  pacFileHandle_t *v12;
  SBTLEFF_PACFILE_EPL *v13;

  pacHandle = wk2->effOnRsc_P->pacHandle;
  Resrc = pacGetResrc(pacHandle);
  if (!Resrc)
    goto LABEL_32;
  while (1)
  {
LABEL_11:
    if (wk2->effOnRsc_P->data_cnt <= 7u)
      goto LABEL_20;
LABEL_10:
    Resrc = Resrc->next;
    effOnRsc_P = wk2->effOnRsc_P;
    ++effOnRsc_P->data_cnt;
    if (!Resrc)
      goto LABEL_32;
  }
  while (1)
  {
LABEL_20:
    data_cnt = wk2->effOnRsc_P->data_cnt;
    v9 = (Resrc->unit->klass->vtable._4_GetExtResource.methodPtr)(Resrc->unit, Resrc->unit->klass->vtable._4_GetExtResource.method);
    if (LoadEffectData_IDMask_pData(skltbl[data_cnt], 0x28u, v9))
    {
      goto LABEL_10;
    }
  }
  Resrc = pacGetResrc(pacHandle);
  if (Resrc)
    goto LABEL_11;
LABEL_32:
  v12 = wk2->effOnRsc_P->pacHandle;
  pacHandleFree(v12);
  v13 = wk2->effOnRsc_P;
  v13->pacHandle = 0;
  wk2->effOnRsc_P->setflg = 1;
  return 1;
}

// 0x207e820
bool sBtlDeleteOnData(s32 flg) {
  s64 v4;
  void *data;
  s64 v6;
  s64 v7;
  s64 i;
  s64 v9;
  void *v10;

  if (flg == 1)
  {
    v4 = 32;
    while (1)
    {
      data = (*(Il2CppClass **)((char *)&wkeffOnMem->obj.klass + v4))->_1.byval_arg.data;
      if (!data)
      {
        goto LABEL_10;
      }
      data = (*(Il2CppClass **)((char *)&wkeffOnMem->obj.klass + v4))->_1.byval_arg.data;
      effPartsDelete(data);
      v7 = *(s64 *)((char *)&wkeffOnMem->obj.klass + v4);
      *(u64 *)(v7 + 32) = 0;
LABEL_10:
      v6 = *(s64 *)((char *)&wkeffOnMem->obj.klass + v4);
      if (*(u64 *)(v6 + 16))
      {
        v6 = *(s64 *)((char *)&wkeffOnMem->obj.klass + v4);
        *(u64 *)(v6 + 16) = 0;
      }
      v4 += 8;
      if (v4 == 400)
        return 1;
    }
  }
  for (i = 32; i != 400; i += 8)
  {
    v10 = (*(Il2CppClass **)((char *)&wkeffOnMem->obj.klass + i))->_1.byval_arg.data;
    if (!v10)
      continue;
    v10 = (*(Il2CppClass **)((char *)&wkeffOnMem->obj.klass + i))->_1.byval_arg.data;
    effPartsDelete(v10);
    v9 = *(s64 *)((char *)&wkeffOnMem->obj.klass + i);
    *(u64 *)(v9 + 32) = 0;
  }
  return 1;
}

// 0x207ea40
SBTLEFF_LISTWORK *sBtlCreateEffList(void) {
  SBTLEFF_LISTWORK *v1;

  v1 = (SBTLEFF_LISTWORK *)Allocate(SBTLEFF_LISTWORK);
  _ctor(v1, 0);
  v1->num = 0;
  v1->wk = 0;
  return v1;
}

// 0x2078990
SBTLEFF_WORK *sBtlGetEffWork(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *wk, s32 id, s32 no) {
  SBTLEFF_WORK *v9;
  Il2CppClass **v11;
  Il2CppClass *v12;
  SBTLEFF_DATAWORK *v13;
  SBTLEFF_DATAWORK *v14;
  SBTLEFF_DATAWORK *v15;
  SBTLEFF_WORK *next;
  SBTLEFF_WORK *v17;
  s32 v18;
  s32 v20;

  v9 = Allocate(SBTLEFF_WORK);
  _ctor(v9, 0);
  v11 = &wk2->effpac->obj.klass + id;
  v12 = v11[4];
  v13 = v9->dwk;
  *(u32 *)&v9->scale = 1065353216;
  LODWORD(v12) = *(u32 *)(*(u64 *)(*((u64 *)v12->_1.this_arg.data + no + 4) + 40) + 20);
  *(u64 *)&v9->starttime = 0;
  v9->effectid = (u32)v12;
  v13->hFile = 0;
  v14 = v9->dwk;
  v14->pData = 0;
  v15 = v9->dwk;
  v15->hPartsList = 0;
  v9->st = 1;
  if (wk && (wk->status & 0x10) != 0)
    v9->flg |= 0x10u;
  v9->prev = 0;
  v9->next = 0;
  next = lwk->wk;
  if (next)
  {
    do
    {
      v17 = next;
      next = next->next;
    }
    while (next);
    v17->next = v9;
    v9->prev = v17;
    v18 = lwk->num + 1;
  }
  else
  {
    lwk->wk = v9;
    v18 = 1;
  }
  lwk->num = v18;
  v20 = lwk->serial + 1;
  v9->serialID2 = lwk->serialID2;
  lwk->serial = v20;
  v9->eListID = v20;
  return v9;
}

// 0x207eab0
f32 sBtlGetDmgEffScale(SBTLUNIT_WORK *wk) {
  return 1.0;
}

// 0x207eac0
void sBtlSetDmgEffShinad(SBTLEFF_WORK *pEff, SBTLUNIT_WORK *pUnit, s32 Type) {
  SBTLEFF_WORK *p_fields;
  struct sdfVector4_t camerapos;
  struct sdfVector4_t pos;
  u16 major;
  s32 minor;
  f32 cylinder;
  struct sdfVector4_t v18;
  f32 v21;
  f32 v22;

  sBtlGetUnitHelperPos(pUnit, 0);
  p_fields = &pEff->fields;
  p_fields->pos = vct_A;
  camerapos = wk->scene->camera->camerapos;
  vct_A = camerapos;
  pos = p_fields->pos;
  vct_B = pos;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  major = pUnit->major;
  minor = pUnit->minor;
  cylinder = sBtlGetVisualData(major, minor)->nml->cylinder;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, cylinder);
  v18 = p_fields->pos;
  vct_B = v18;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  p_fields->pos = vct_A;
  v21 = pEff->pos.x * 0.5;
  v22 = -200.0;
  pEff->scale = 1.0;
  pEff->pos.z = 650.0;
  if (Type)
    v22 = 0.0;
  pEff->pos.x = v21;
  pEff->pos.y = v22;
}

// 0x207efa0
SBTLEFF_WORK *sBtlCreateEff(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *wk, EFFID effectid, s32 starttime, const sdfVector4_t *defpos, u32 rgba, s8 flg, f32 _Pow, SKLID _Skill) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBTLEFF_WORK *v22;
  int8x16_t v23;
  int8x16_t v28;
  SBTLEFF_DATAWORK *v29;
  uint32x4_t v30;
  float32x4_t v31;
  SBTLEFF_DATAWORK *v32;
  u32 status;
  s32 v35;
  u32 v36;
  s32 v37;
  s32 targetID;
  sdfVector4_t *v41;
  SBTLEFF_WORK *p_wk;
  SBTLEFF_WORK *next;
  SBTLEFF_WORK *v44;
  s32 v47;
  s32 v48;
  f32 DataScale;
  struct sdfVector4_t defrot;
  sdfVector4_t *v54;
  f32 v55;
  f32 v56;
  f32 *p_x;
  f32 v62;
  struct sdfVector4_t v65;
  u16 major;
  s32 minor;
  f32 cylinder;
  struct sdfVector4_t v70;
  f32 *v74;
  f32 *v76;
  f32 v77;
  f32 v78;
  f32 v79;
  f32 *v81;
  sdfVector4_t *v83;
  f32 *v87;
  f32 v88;
  f32 v89;
  f32 v90;
  f32 *v91;
  f32 *v92;
  f32 v94;
  f32 v95;
  f32 GroundPos;
  s32 v97;
  struct SDF_VU0 *v101;
  struct sdfVector4_t pos;
  struct sdfVector4_t v103;
  struct sdfVector4_t camerapos;
  struct sdfVector4_t v107;
  struct sdfVector4_t v114;
  sdfVector4_t v115;
  sdfVector4_t v116;
  sdfVector4_t v117;
  sdfVector4_t v118;
  sdfVector4_t v119;
  sdfVector4_t v120;

  w = defpos->w;
  z = defpos->z;
  y = defpos->y;
  x = defpos->x;
  v22 = Allocate(SBTLEFF_WORK);
  _ctor(v22, 0);
  v22->effectid = effectid;
  v22->starttime = 2 * starttime;
  *(u32 *)&v22->scale = 1065353216;
  v22->workID = 0;
  v22->life = 2 * resident[effectid]->life;
  v23.n128_u32[0] = rgba;
  v28.n128_u64[0] = 0xFF000000FFLL;
  v28.n128_u64[1] = 0xFF000000FFLL;
  v29 = v22->dwk;
  v22->sklid = Skill;
  v23.n128_u32[1] = rgba >> 8;
  v23.n128_u32[2] = HIWORD(rgba);
  v30 = vandq_s8(v23, v28);
  v30.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(rgba), 0x18u).n128_u32[3];
  v31.n128_u64[0] = 0x3C0000003C000000LL;
  v31.n128_u64[1] = 0x3C0000003C000000LL;
  *(float32x4_t *)&v22->rgb = vmulq_f32(vcvtq_f32_u32(v30), v31);
  v29->pData = 0;
  v32 = v22->dwk;
  v32->hPartsList = 0;
  v22->st = 1;
  status = wk->status;
  v35 = resident[v22->effectid]->flg | v22->flg;
  v36 = (u8)flg - 1;
  v22->flg = v35;
  if ((status & 0x10) != 0 || v36 <= 1)
  {
    v37 = status & 0x10 | v35;
    if (v36 < 2)
      v37 |= 0x2000u;
    v22->flg = v37;
  }
  v22->prev = 0;
  v22->next = 0;
  targetID = wk->actaiwk->targetID;
  v22->acterID = wk->ListID;
  v22->targetID = targetID;
  pos = wk->pos;
  vct_A = pos;
  v41 = &v22->pos;
  *v41 = vct_A;
  p_wk = &lwk->wk;
  next = lwk->wk;
  if (!next)
    goto LABEL_31;
  goto LABEL_28;
  if (!next)
  {
LABEL_31:
    lwk->wk = v22;
    lwk->num = 1;
    v47 = v22->effectid;
    v48 = v47 - 1;
LABEL_32:
    switch (v48)
    {
      case 0:
      case 1:
      case 5:
      case 9:
      case 10:
      case 12:
      case 49:
      case 54:
        if (flg == 2)
        {
          p_x = &vf00.x;
          p_x[4] = x;
          p_x[5] = y;
          p_x[6] = z;
          p_x[7] = w;
          goto LABEL_53;
        }
        sBtlGetUnitHelperPos(wk, 1);
        *v41 = vct_A;
        v88 = vct_A.x;
        v89 = vct_A.z;
        v90 = vct_A.w;
        LODWORD(v101) = (u8)byte_5755EF5;
        *(u32 *)&v22->pos.y = 0;
        if (!(u32)v101)
          goto LABEL_206;
        goto LABEL_157;
        if (!(u32)v87)
        {
LABEL_206:
LABEL_158:
          v91 = &vf00.x;
          v91[4] = x;
          v91[5] = y;
          v91[6] = z;
          v91[7] = w;
          v92 = &vf00.x;
          v117.y = 0.0;
          v120.y = 0.0;
          v120.x = v88;
          v120.z = v89;
          v120.w = v90;
          v117.x = v92[4];
          v117.z = v92[6];
          v117.w = v92[7];
          sBtlGetQuat(v117, v120);
          v94 = v22->pos.x;
          v22->rot = vct_A;
          v95 = v22->pos.z;
          GroundPos = sBtlGetGroundPos(v94, v95);
          v22->pos.y = GroundPos;
          goto LABEL_170;
        }
LABEL_157:
        goto LABEL_158;
      case 2:
      case 3:
      case 39:
      case 40:
      case 41:
      case 42:
      case 44:
      case 45:
      case 46:
      case 47:
        v103 = wk->pos;
        vct_A = v103;
        *v41 = vct_A;
        DataScale = GetDataScale(wk, 0);
        v22->scale = DataScale;
        defrot = _defrot;
        vct_A = defrot;
        v54 = &v22->rot;
        v55 = v22->pos.x;
        *v54 = vct_A;
        v56 = v22->pos.z;
        v22->pos.y = sBtlGetGroundPos(v55, v56);
        goto LABEL_171;
      case 7:
      case 11:
      case 19:
      case 20:
      case 25:
      case 26:
      case 27:
      case 28:
        sBtlGetUnitHelperPos(wk, 0);
        *v41 = vct_A;
        v62 = v22->pos.y;
        if (v62 >= -1.0)
          v22->pos.y = v62 + -50.0;
        camerapos = wk->scene->camera->camerapos;
        vct_A = camerapos;
        v65 = *v41;
        vct_B = v65;
        vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
        sub_1949110(0);
        major = wk->major;
        minor = wk->minor;
        cylinder = sBtlGetVisualData(major, minor)->nml->cylinder;
        vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, cylinder);
        v70 = *v41;
        vct_B = v70;
        vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
        *v41 = vct_A;
LABEL_170:
        *(u32 *)&v22->scale = 1065353216;
LABEL_171:
        v47 = v22->effectid;
        goto LABEL_172;
      case 8:
      case 14:
      case 32:
        v74 = &vf00.x;
        v74[4] = x;
        v74[5] = y;
        v74[6] = z;
        v74[7] = w;
        *v41 = vct_A;
        v22->scale = Pow + Pow;
        goto LABEL_171;
      case 15:
      case 16:
      case 18:
        v107 = wk->pos;
        vct_A = v107;
        v76 = &vf00.x;
        v77 = v76[4];
        v79 = v76[6];
        v78 = v76[7];
        sBtlGetPosforDistance(wk, 10.0);
        v81 = &vf00.x;
        v115.y = 0.0;
        v118.y = 0.0;
        v118.x = v77;
        v118.z = v79;
        v118.w = v78;
        v115.x = v81[4];
        v115.z = v81[6];
        v115.w = v81[7];
        sBtlGetQuat(v115, v118);
        v83 = &v22->rot;
        v119.x = y;
        v119.y = x;
        v116.z = v22->pos.z;
        v116.w = v22->pos.w;
        v119.z = z;
        v119.w = w;
        *v83 = vct_A;
        v116.y = v22->pos.x;
        v116.x = v22->pos.y;
        sBtlGetQuat(v116, v119);
        v83->x = 0.5;
        sBtlGetUnitHelperPos(wk, 1);
        v22->pos.y = vct_A.y;
        goto LABEL_170;
      case 33:
        v114 = wk->pos;
        vct_A = v114;
LABEL_53:
        *v41 = vct_A;
        goto LABEL_170;
      case 55:
        sBtlGetUnitHelperPos(wk, 0);
        *v41 = vct_A;
        goto LABEL_171;
      default:
        goto LABEL_172;
    }
  }
  do
  {
LABEL_28:
    v44 = next;
    next = next->next;
  }
  while (next);
  v44->next = v22;
  v22->prev = v44;
  ++lwk->num;
  v47 = v22->effectid;
  v48 = v47 - 1;
  if ((u32)(v47 - 1) <= 0x37)
    goto LABEL_32;
LABEL_172:
  v97 = lwk->serial + 1;
  lwk->serial = v97;
  v22->eListID = v97;
  if (v47 <= 19)
  {
    if ((u32)v47 > 0x13 || ((1 << v47) & 0xBAE02) == 0)
      goto LABEL_175;
  }
  else if (v47 != 50 && v47 != 33)
  {
LABEL_175:
    v22->pHitEff = 0;
    return v22;
  }
  sBtlAddHitEff(v22);
  return v22;
}

// 0x20751b0
bool sBtlCheckSABData(SBTLEFF_WORK *wk) {
  s16 v4;

  if (wk->BEDsklid)
  {
    return wk2->effpac[wk->workID]->status & 1;
  }
  else
  {
    LOBYTE(v4) = 0;
  }
  return v4;
}

// 0x2080190
bool sBtlCheckEffectData(SBTLUNIT_WORK *wk, SKLID sklid, u8 type, s8 flg, SBTLUNIT_SIDE acterside, s32 serialID2, s32 sttime) {
  bool v15;
  s64 v18;
  s64 v19;
  SBTLSKILLP_TBL *Skilltbl;
  s32 v21;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  SBTLEFF_PACLIST *v30;
  s64 num;
  s64 count;
  EFFPDATA_WORK *v35;
  u32 v36;
  s32 v37;
  s8 v40;
  s32 v41;
  sdfVector4_t v42;

  if (sklid == 440 && type == 2)
    return 0;
  v18 = 0;
  while (1)
  {
    v19 = (s64)wk2->effpac + 8 * v18;
    if (*(u32 *)(*(u64 *)(v19 + 32) + 40) == sklid)
      goto LABEL_24;
    if (*(u32 *)(*(u64 *)(v19 + 40) + 40) == sklid)
    {
      LODWORD(v18) = v18 + 1;
      goto LABEL_24;
    }
    v18 += 2;
    if (v18 == 150)
      return 0;
  }
  v18 = 0;
  while (1)
  {
    if (wk2->effpac[v18]->skillID == sklid)
      break;
    if (++v18 == 150)
      return 0;
  }
LABEL_24:
  if ((u32)v18 == -1)
    return 0;
  Skilltbl = sBtlGetSkilltbl(sklid);
  if (Skilltbl)
  {
    if (type == 1)
    {
      if ((Skilltbl->flg2 & 0x100000) != 0)
        goto LABEL_39;
    }
    else if (type == 2 && (Skilltbl->flg2 & 0x200000) != 0)
    {
      goto LABEL_39;
    }
  }
  if (wk->para->devilid == 258)
  {
    v42.x = 0.0;
    v21 = type;
    v42.z = 1300.0;
    v42.y = 0.0;
    v42.w = 0.0;
  }
  else
  {
    x = wk->pos.x;
    y = wk->pos.y;
    z = wk->pos.z;
    w = wk->pos.w;
    v42.x = x;
    v42.y = y;
    v21 = type;
    v42.z = z;
    v42.w = w;
  }
  sBtlPlaySkillSE(v42, sklid, v21);
LABEL_39:
  v30 = wk2->effpac[(s32)v18];
  if ((v30->status & 1) == 0)
    return 1;
  v40 = flg;
  v41 = serialID2;
  v30 = wk2->effpac[(s32)v18];
  num = (u32)v30->num;
  v15 = 1;
  if ((s32)num >= 1)
  {
    count = 0;
    while (1)
    {
      v35 = wk2->effpac[(s32)v18]->pwk[count]->wk;
      v36 = v35->type;
      if (type <= 1u)
      {
        if (v36 <= type)
        {
LABEL_63:
          if (v40 == 1)
            return 1;
          v37 = v35->iti & 0xF;
          if (v37)
          {
            switch (v37)
            {
              case 4:
                CheckEffectData_Core(wk, sklid, type, v18, count, acterside, v41, 2, sttime, count);
                break;
              case 5:
                CheckEffectData_Core(wk, sklid, type, v18, count, acterside, v41, 3, sttime, count);
                break;
              case 8:
                CheckEffectData_Core(wk, sklid, type, v18, count, acterside, v41, 4, sttime, count);
                break;
              default:
                CheckEffectData_Core(wk, sklid, type, v18, count, acterside, v41, 0, sttime, count);
                break;
            }
          }
          else
          {
            CheckEffectData_Core(wk, sklid, type, v18, count, acterside, v41, 1, sttime, count);
          }
        }
      }
      else if (v36 == type)
      {
        goto LABEL_63;
      }
      if (num == ++count)
      {
        AddSerialID2();
        sBtlAddSerialID2();
        return 1;
      }
    }
  }
  return v15;
}

// 0x20808b0
bool sBtlCheckEffectData_GunMode2(SBTLUNIT_WORK *wk, SKLID sklid, u8 type, s8 flg, SBTLUNIT_SIDE acterside, s32 serialID2, s32 sttime) {
  s32 GunLockOn_TgtPop;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v15;
  SBTLUNIT_WORK *v19;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  sdfVector4_t v30;

  if (wk->actaiwk->targetID == -1)
    goto LABEL_10;
  GunLockOn_TgtPop = sBtlGetGunLockOn_TgtPop();
  if (GunLockOn_TgtPop == -1)
  {
    GunLockOn_TgtPop = wk->actaiwk->targetID;
LABEL_8:
    UnitMng = wk->UnitMng;
    goto LABEL_9;
  }
  else
  {
    goto LABEL_8;
  }
  UnitMng = wk->UnitMng;
  v15 = sBtlSearchUnit_ID(UnitMng, GunLockOn_TgtPop);
  if (v15)
    goto LABEL_17;
LABEL_10:
  goto LABEL_11;
LABEL_9:
  v15 = sBtlSearchUnit_ID(UnitMng, GunLockOn_TgtPop);
  if (!v15)
    goto LABEL_10;
LABEL_17:
  v19 = v15;
  sBtlGetUnitHelperPos(v19, 21);
  p_x = &vf00.x;
  x = p_x[4];
  y = p_x[5];
  z = p_x[6];
  w = p_x[7];
  v30.x = x;
  v30.y = y;
  v30.z = z;
  v30.w = w;
  SetDamageProc(v19, wk, sklid, v30);
LABEL_11:
  AddSerialID2();
  sBtlAddSerialID2();
  return 1;
}

// 0x2080b80
bool sBtlCheckEffectData_SeOnly(SBTLUNIT_WORK *wk, SKLID sklid, u8 type, s8 flg, SBTLUNIT_SIDE acterside, s32 serialID2, s32 sttime) {
  s64 v13;
  s64 v14;
  SBTLSKILLP_TBL *Skilltbl;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  sdfVector4_t v21;

  v13 = 0;
  while (1)
  {
    v14 = (s64)wk2->effpac + 8 * v13;
    if (*(u32 *)(*(u64 *)(v14 + 32) + 40) == sklid)
      goto LABEL_20;
    if (*(u32 *)(*(u64 *)(v14 + 40) + 40) == sklid)
    {
      LODWORD(v13) = v13 + 1;
      goto LABEL_20;
    }
    v13 += 2;
    if (v13 == 150)
      return 0;
  }
  v13 = 0;
  while (1)
  {
    if (wk2->effpac[v13]->skillID == sklid)
      break;
    if (++v13 == 150)
      return 0;
  }
LABEL_20:
  if ((u32)v13 == -1)
    return 0;
  Skilltbl = sBtlGetSkilltbl(sklid);
  if (!Skilltbl)
    goto LABEL_28;
  if (type != 1)
  {
    if (type == 2 && (Skilltbl->flg2 & 0x200000) != 0)
      return 1;
LABEL_28:
    x = wk->pos.x;
    y = wk->pos.y;
    z = wk->pos.z;
    w = wk->pos.w;
    v21.x = x;
    v21.y = y;
    v21.z = z;
    v21.w = w;
    sBtlPlaySkillSE(v21, sklid, type);
    return 1;
  }
  if ((Skilltbl->flg2 & 0x100000) == 0)
    goto LABEL_28;
  return 1;
}

// 0x2078be0
bool SetDamageProc(SBTLUNIT_WORK *wklock, SBTLUNIT_WORK *wk, SKLID sklid, const sdfVector4_t *ppos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBTLDMG_HITWORK *v12;
  u16 area;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v15;
  SBTLDMG_HITLISTWORK *hitList;
  SBTLUNIT_LISTWORK *hitlwk;
  sdfVector4_t v20;

  w = ppos->w;
  z = ppos->z;
  y = ppos->y;
  x = ppos->x;
  v12 = Allocate(SBTLDMG_HITWORK);
  _ctor(v12, 0);
  if (!wklock)
    goto LABEL_23;
  if (!CheckLiveTarget(wklock))
    goto LABEL_23;
  area = sBtlGetSkilltbl(sklid)->area;
  if ((area & 0x10) == 0)
    goto LABEL_15;
  if ((area & 0x4000) != 0 && (wklock->status & 0x8800) == 0x8800 && !wklock->hithelpercsrno)
  {
LABEL_23:
    LOBYTE(Skilltbl) = 0;
    return (char)Skilltbl;
  }
LABEL_15:
  Skilltbl = sBtlGetSkilltbl(sklid);
  if (Skilltbl)
  {
    v15 = Skilltbl;
    hitList = wk->hitList;
    v20.x = x;
    v20.y = y;
    v20.z = z;
    v20.w = w;
    sBtlCreateHitC_None(hitList, wklock, wk, v12, sklid, v15, v20, -1);
    sBtlAddSerialID2();
    sBtlDamageProc(wklock, v12, 0);
    hitlwk = v12->hitlwk;
    sBtlDeleteUnitList(hitlwk, 0);
    LOBYTE(Skilltbl) = 1;
  }
  return (char)Skilltbl;
}

// 0x20807a0
void AddSerialID2(void) {
  SBTLEFF_LISTWORK *effList;
  s32 v3;

  effList = wk->effList;
  if (!effList)
    return;
  v3 = effList->serialID2 + 1;
  effList->serialID2 = v3;
  if (v3 < 0xFFFF)
    return;
  effList->serialID2 = 0;
}

// 0x2080d90
s32 sBtlGetEffectSerialID2_Now(void) {
  SBTLEFF_LISTWORK *effList;
  s32 serialID2;

  effList = wk->effList;
  if (!effList)
    return 0;
  if ((effList->num & 0x80000000) != 0)
    return 0;
  serialID2 = wk->effList->serialID2;
  if (!serialID2)
    return 65534;
  serialID2 = wk->effList->serialID2;
  return serialID2 - 1;
}

// 0x2080ec0
bool sBtlDeleteEffectData_SerialID2(SBTLEFF_LISTWORK *lwk, s32 serialID2) {
  SBTLEFF_WORK *wk;
  u32 v6;
  u32 flg;

  if (!lwk->num)
    return 0;
  wk = lwk->wk;
  if (!wk)
    return 0;
  do
  {
    if (wk->serialID2 != serialID2)
      goto LABEL_8;
    if (!sBtlCheckDeleteEffect(wk))
      goto LABEL_8;
    flg = wk->flg;
    if ((u32)(wk->st - 1) > 1)
    {
      v6 = flg | 0x80000000;
      wk->st = 4;
    }
    else
    {
      v6 = flg | 0x80000008;
    }
    wk->flg = v6;
LABEL_8:
    wk = wk->next;
  }
  while (wk);
  return 1;
}

// 0x2080fc0
bool sBtlSetDecAlpha_SerialID2(SBTLEFF_LISTWORK *lwk, s32 serialID2, s32 alpha) {
  SBTLEFF_WORK *wk;

  if (!lwk->num)
    return 0;
  wk = lwk->wk;
  if (!wk)
    return 0;
  do
  {
    if (wk->serialID2 != serialID2)
      goto LABEL_6;
    if (!sBtlCheckDeleteEffect(wk))
      goto LABEL_6;
    if (wk->st == 3)
      wk->alpha_cnt = alpha;
LABEL_6:
    wk = wk->next;
  }
  while (wk);
  return 1;
}

// 0x20810a0
bool sBtlDeleteEffectData_SkillID(SBTLEFF_LISTWORK *lwk, SKLID skillid) {
  SBTLEFF_WORK *wk;
  u32 v6;
  u32 flg;

  if (!lwk->num)
    return 0;
  wk = lwk->wk;
  if (!wk)
    return 0;
  do
  {
    if (wk->BEDsklid != skillid)
      goto LABEL_8;
    if (!sBtlCheckDeleteEffect(wk))
      goto LABEL_8;
    flg = wk->flg;
    if ((u32)(wk->st - 1) > 1)
    {
      v6 = flg | 0x80000000;
      wk->st = 5;
      wk->alpha = 0;
    }
    else
    {
      v6 = flg | 0x80000008;
    }
    wk->flg = v6;
LABEL_8:
    wk = wk->next;
  }
  while (wk);
  return 1;
}

// 0x20811a0
bool sBtlForceDelete_SPID(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *wk, SKLID skillid) {
  bool v7;
  SBTLEFF_WORK *next;
  char v9;
  u32 v10;
  u32 flg;

  v7 = 0;
  if (lwk->num)
  {
    next = lwk->wk;
    if (next)
    {
      if ((skillid | 0x10) != 0x1B3)
        return 0;
      v9 = 1;
      v7 = 1;
      while (1)
      {
        if (next->BEDsklid != skillid)
          goto LABEL_9;
        if (!sBtlCheckDeleteEffect(next))
          goto LABEL_9;
        if (next->BEDtype > 1u)
          goto LABEL_9;
        if (next->acterID == wk->ListID)
        {
          flg = next->flg;
          if ((u32)(next->st - 1) > 1)
          {
            v10 = flg | 0x80000000;
            next->st = 4;
          }
          else
          {
            v10 = flg | 0x80000008;
          }
          next->flg = v10;
          goto LABEL_9;
        }
        next = next->next;
        v9 = 0;
        if (!next)
          return v7;
        goto LABEL_9000;
LABEL_9:
        next = next->next;
        if (!next)
        {
          if ((v9 & 1) == 0)
            return 1;
          v7 = 1;
          sBtlStopSkillSE(skillid, 1);
          return v7;
        }
LABEL_9000:
      }
    }
  }
  return v7;
}

// 0x2081330
bool sBtlDeleteEffectData_SkillIDType(SBTLEFF_LISTWORK *lwk, SKLID skillid, SBTLEFF_BEDTYPE type) {
  bool result;
  SBTLEFF_WORK *wk;
  s32 v7;

  if (!skillid)
    return 1;
  result = 0;
  if (lwk->num)
  {
    wk = lwk->wk;
    if (wk)
    {
      do
      {
        if (wk->BEDsklid == skillid && wk->BEDtype == type)
        {
          if ((u32)(wk->st - 1) >= 2)
          {
            v7 = -2147483640;
            wk->st = 5;
            wk->alpha = 0;
          }
          else
          {
            v7 = 8;
          }
          wk->flg |= v7;
        }
        wk = wk->next;
      }
      while (wk);
      return 1;
    }
  }
  return result;
}

// 0x20813c0
bool sBtlDeleteEffectData_SkillIDTypeUnit(SBTLEFF_LISTWORK *lwk, SKLID skillid, SBTLEFF_BEDTYPE type, s32 unitID) {
  bool result;
  SBTLEFF_WORK *wk;

  if (!skillid)
    return 1;
  result = 0;
  if (lwk->num)
  {
    wk = lwk->wk;
    if (wk)
    {
      do
      {
        if (wk->BEDsklid == skillid && wk->BEDtype == type && wk->acterID == unitID)
        {
          if ((u32)(wk->st - 1) > 1)
          {
            wk->st = 5;
            wk->alpha = 0;
          }
          else
          {
            wk->flg |= 8u;
          }
        }
        wk = wk->next;
      }
      while (wk);
      return 1;
    }
  }
  return result;
}

// 0x2081450
bool sBtlEff_DeleteEffectData_EffID(SBTLEFF_LISTWORK *lwk, EFFID effid) {
  SBTLEFF_WORK *wk;

  if (!lwk->num)
    return 0;
  wk = lwk->wk;
  if (!wk)
    return 0;
  do
  {
    if (wk->effectid == effid)
    {
      wk->pHitEff = 0;
      if ((u32)(wk->st - 1) > 1)
      {
        wk->st = 5;
        wk->alpha = 0;
      }
      else
      {
        wk->flg |= 8u;
      }
    }
    wk = wk->next;
  }
  while (wk);
  return 1;
}

// 0x2081500
s16 sBtlGetStartTime_Damage(void) {
  SBATTLE_WORK *wk_local;
  s32 v3;

  wk_local = wk;
  v3 = ++wk_local->effcnt;
  if (v3 >= 8)
  {
    wk_local->effcnt = 0;
    return wk->effcnt;
  }
  {
    return wk->effcnt;
  }
  return wk->effcnt;
}

// 0x20815e0
void sBtlClearStartTime_Damage(void) {
  wk->effcnt = 0;
  return;
}

// 0x2080110
s32 sBtlGetEffTime(EFFID id) {
  return resident[id]->life;
}

// 0x2081670
bool sBtlListProc(SBTLEFF_LISTWORK *lwk) {
  bool IsSceanStop;
  _BOOL4 v6;
  _BOOL4 v9;
  void *bsc;
  _BOOL4 effNoStop2;
  SBTLEFF_WORK *next;
  s32 scrFlag;
  u32 v24;
  s32 BEDsklid;
  SBTLSKLVISUAL_TBL *SklVisualTbl;
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v30;
  SBTLUNIT_WORK *v31;
  struct sdfVector4_t rot;
  EffFuncDelegate func;
  struct sdfVector4_t pos;

  IsSceanStop = IsSceanStop();
  if (!IsSceanStop)
  {
    v6 = 0;
    goto LABEL_7;
  }
  v6 = !wk->effNoStop;
LABEL_7:
  v9 = !wk->effNoStop2 && v6;
  bsc = wk->bsc;
  if (op_Equality(bsc, 0, 0))
    return 0;
  if (!wk->effList)
    return 0;
  next = lwk->wk;
  if (!next || !lwk->num)
    return 0;
  do
  {
    if (!v9)
      goto LABEL_74;
    if (next->effectid == 40)
    {
      if (!next->BEDsklid)
        goto LABEL_74;
      if ((wk2->effpac[next->workID]->status & 1) != 0)
      {
        scrFlag = wk->scrFlag;
        if ((scrFlag & 0x20000000) != 0)
          goto LABEL_74;
        scrFlag = wk->scrFlag;
        if ((scrFlag & 0x80000) == 0)
          goto LABEL_35;
      }
      goto LABEL_74;
    }
    if (!next->BEDsklid)
      goto LABEL_74;
    if ((wk2->effpac[next->workID]->status & 1) != 0)
    {
      if ((wk->scrFlag & 0x80000) != 0)
        goto LABEL_74;
      if ((u32)(next->BEDsklid - 289) > 0xB)
        goto LABEL_35;
      if (!sBtlIsHuuma())
        goto LABEL_35;
    }
LABEL_74:
    if (next->bTateBg)
    {
      if (!v24)
      EffFunc_TateBg(next);
      goto LABEL_78;
    }
    if (v24)
    {
      if (sBtlCheckStopEffect(next))
        goto LABEL_99;
    }
    else
    {
      if (sBtlCheckStopEffect(next))
      {
LABEL_99:
        ++next->counter;
        LimitRange(&next->counter, 0, 0x7FFF);
        goto LABEL_113;
      }
    }
    if (next->BEDsklid)
    {
      if ((wk2->effpac[next->workID]->status & 1) != 0)
      {
        if ((sBtlGetSkilltbl(next->BEDsklid)->flg & 0x100) == 0 && next->st == 3)
        {
          goto LABEL_78;
        }
        goto LABEL_131;
      }
    }
    if (next->st == 3)
      goto LABEL_78;
LABEL_113:
    goto LABEL_9004;
    if (!next->BEDsklid)
    {
LABEL_126:
      goto LABEL_120;
    }
    goto LABEL_116;
LABEL_9004:
    if (!next->BEDsklid)
      goto LABEL_126;
LABEL_116:
    if ((wk2->effpac[next->workID]->status & 1) == 0)
    {
LABEL_120:
      func = resident[next->effectid]->func;
      if (func)
      {
        func = resident[next->effectid]->func;
        (func->invoke_impl)(func->method_code, next, func->method);
      }
      goto LABEL_78;
    }
LABEL_131:
    EffFunc_Hanyou_BED(next);
LABEL_78:
    if (next->st == 3)
    {
      BEDsklid = next->BEDsklid;
      if (BEDsklid)
      {
        SklVisualTbl = sBtlGetSklVisualTbl(BEDsklid);
        if (SklVisualTbl)
        {
          if ((SklVisualTbl->flg & 0x100) != 0)
          {
            acterID = next->acterID;
            UnitMng = wk->UnitMng;
            v30 = sBtlSearchUnit_ID(UnitMng, acterID);
            if (v30)
            {
              v31 = v30;
              pos = v30->pos;
              goto LABEL_89;
LABEL_90:
              vct_A = pos;
              goto LABEL_91;
LABEL_89:
              goto LABEL_90;
LABEL_91:
              next->pos = vct_A;
              effPartsPositionSet(next->dwk->hPartsList, next->pos);
              rot = v31->rot;
              goto LABEL_94;
LABEL_95:
              goto LABEL_9006;
LABEL_94:
              vct_A = rot;
              goto LABEL_95;
LABEL_9006:
              next->rot = vct_A;
              effPartsRotateSet(next->dwk->hPartsList, next->rot);
            }
          }
        }
      }
    }
LABEL_35:
    next = next->next;
  }
  while (next);
  return 1;
}

// 0x2081f10
bool Draw(void) {
  bool IsSceanStop;
  _BOOL4 v3;
  _BOOL4 v5;
  SBTLEFF_LISTWORK *effList;
  SBTLEFF_WORK *next;
  s32 effectid;
  s32 *p_acterID;
  s32 v15;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 targetID;
  SBTLUNIT_LISTWORK *v19;
  SBTLUNIT_WORK *v20;
  s32 BEDtype;
  s32 *p_ListID;
  u32 v25;
  bool v26;
  char v27;
  s32 v32;
  SBTLUNIT_LISTWORK *v33;
  SBTLUNIT_WORK *v34;
  SBTLSKILLP_TBL *Skilltbl;

  sBtlGetCutFlg();
  IsSceanStop = IsSceanStop();
  if (!IsSceanStop)
  {
    v3 = 0;
    goto LABEL_10;
  }
  v3 = (wk->scrFlag & 0x80000) == 0;
LABEL_10:
  v5 = !wk->effNoStop2 && v3;
  if (!wk->effList)
    return 0;
  if (!wk->UnitMng)
    return 0;
  effList = wk->effList;
  next = effList->wk;
  if (!next)
    return 0;
  if (!effList->num)
    return 0;
  eglSetOt(40);
  eglLinkTest(SET_10AADD12);
  eglLinkAlpha(0);
  if (v5)
    effStartEffectStop();
  do
  {
    effectid = next->effectid;
    if (effectid == 40)
    {
      if (!v5)
        goto LABEL_54;
    }
    else if (effectid != 4 || !v5)
    {
      goto LABEL_54;
    }
    if ((wk->scrFlag & 0x20000000) == 0)
      goto LABEL_54;
    effStopEffectStop_SUMMON_FR();
LABEL_54:
    if ((u32)(next->BEDsklid - 289) > 0xB)
      goto LABEL_61;
    if (!sBtlIsHuuma())
      goto LABEL_61;
    effStopEffectStop_SUMMON_FR();
LABEL_61:
    if ((u32)(next->st - 3) > 1)
      goto LABEL_125;
    p_acterID = &next->acterID;
    sBtlEffSetActer(next->acterID);
    v15 = *p_acterID;
    UnitMng = wk->UnitMng;
    if (!sBtlSearchUnit_ID(UnitMng, v15))
      goto LABEL_82;
    targetID = next->targetID;
    v19 = wk->UnitMng;
    v20 = sBtlSearchUnit_ID(v19, targetID);
    if (!v20)
      goto LABEL_82;
    BEDtype = next->BEDtype;
    p_ListID = &next->acterID;
    if (BEDtype != 2)
    {
      p_ListID = &next->acterID;
      if (BEDtype != 5)
        p_ListID = &v20->ListID;
    }
    sBtlEffSetTarget(*p_ListID);
LABEL_82:
    if (!next->dwk->hPartsList)
      goto LABEL_125;
    if (!next->BEDsklid)
      goto LABEL_92;
    if ((wk2->effpac[next->workID]->status & 1) == 0)
    {
LABEL_92:
      v25 = next->effectid;
      if (v25 <= 0x32 && ((1 << v25) & 0x4000000002C46LL) != 0)
      {
        v26 = 1;
        v27 = 1;
        goto LABEL_95;
      }
      else
      {
        v26 = 0;
        v27 = 0;
LABEL_95:
        epl_otchkflg = v27;
        goto LABEL_101;
      }
      goto LABEL_113;
    }
    v26 = 0;
    epl_otchkflg = 0;
    goto LABEL_101;
LABEL_113:
    epl_otchkflg = v26;
LABEL_101:
    if (!next->BEDsklid)
      goto LABEL_118;
    if ((wk2->effpac[next->workID]->status & 1) != 0 && (sBtlGetSkilltbl(next->BEDsklid)->flg & 0x100) != 0)
    {
      v32 = *p_acterID;
      v33 = wk->UnitMng;
      v34 = sBtlSearchUnit_ID(v33, v32);
      if (!v34)
        goto LABEL_118;
      if (v34->mode < 5 || (v34->vstatus & 0x1000) != 0)
        goto LABEL_125;
    }
LABEL_118:
    if (wk->bEffNoDraw)
    {
      Skilltbl = sBtlGetSkilltbl(next->BEDsklid);
      if ((Skilltbl->flg2 & 0x80) == 0 && (Skilltbl->type & 0x1000) == 0)
        goto LABEL_125;
    }
    effPartsDraw(next->dwk->hPartsList);
LABEL_125:
    if (next->effectid == 40 && v5)
    {
      if ((wk->scrFlag & 0x20000000) == 0)
        goto LABEL_132;
      effStartEffectStop_SUMMON_FR();
      goto LABEL_132;
    }
LABEL_132:
    if ((u32)(next->BEDsklid - 289) > 0xB)
      goto LABEL_43;
    if (!sBtlIsHuuma())
      goto LABEL_43;
    effStartEffectStop_SUMMON_FR();
LABEL_43:
    next = next->next;
  }
  while (next);
  if (v5)
    effStopEffectStop();
  return 1;
}

// 0x2082710
SBTLEFF_WORK *sBtlGetEffectWork_ID(SBTLEFF_LISTWORK *lwk, s32 eListID) {
  SBTLEFF_WORK *result;

  if (!lwk->num)
    return 0;
  for (result = lwk->wk; result; result = result->next)
  {
    if (result->eListID == eListID)
      break;
  }
  return result;
}

// 0x2082740
s32 sBtlGetEffectStat_ID(SBTLEFF_LISTWORK *lwk, s32 eListID) {
  SBTLEFF_WORK *wk;
  s32 result;

  if (!lwk->num)
    return -1;
  wk = lwk->wk;
  if (!wk)
    return -1;
  result = -1;
  while (wk->eListID != eListID)
  {
    wk = wk->next;
    if (!wk)
      return result;
  }
  return wk->st;
}

// 0x2082780
bool sBtlForceDelete_ID(SBTLEFF_LISTWORK *lwk, s32 eListID) {
  SBTLEFF_WORK *wk;
  u32 v6;
  u32 flg;

  if (!lwk->num)
    return 0;
  wk = lwk->wk;
  if (!wk)
    return 0;
  do
  {
    if (wk->eListID != eListID)
      goto LABEL_8;
    if (!sBtlCheckDeleteEffect(wk))
      goto LABEL_8;
    flg = wk->flg;
    if ((u32)(wk->st - 1) > 1)
    {
      v6 = flg | 0x80000000;
      wk->st = 5;
      wk->alpha = 0;
    }
    else
    {
      v6 = flg | 0x80000008;
    }
    wk->flg = v6;
LABEL_8:
    wk = wk->next;
  }
  while (wk);
  return 1;
}

// 0x2082880
bool sBtlForceDelete_ID_Acter(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *wk, EFFID effectid) {
  SBTLEFF_WORK *next;
  u32 v10;
  u32 flg;

  if (!wk->effList)
    return 0;
  if (!lwk->num)
    return 0;
  next = lwk->wk;
  if (!next)
    return 0;
  do
  {
    if (next->effectid != effectid)
      goto LABEL_12;
    if (!sBtlCheckDeleteEffect(next))
      goto LABEL_12;
    if (wk->ListID == next->acterID)
    {
      flg = next->flg;
      if ((u32)(next->st - 1) > 1)
      {
        v10 = flg | 0x80000000;
        next->st = 4;
      }
      else
      {
        v10 = flg | 0x80000008;
      }
      next->flg = v10;
    }
LABEL_12:
    next = next->next;
  }
  while (next);
  return 1;
}

// 0x20829f0
bool sBtlForceDelete_ID_Summon(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *wk) {
  SBTLEFF_WORK *next;
  u32 v7;
  u32 flg;

  if (!wk->effList)
    return 0;
  if (!lwk->num)
    return 0;
  next = lwk->wk;
  if (!next)
    return 0;
  do
  {
    if (next->effectid == 3 && wk->ListID == next->acterID)
    {
      flg = next->flg;
      if ((u32)(next->st - 1) > 1)
      {
        v7 = flg | 0x80000000;
        next->st = 4;
      }
      else
      {
        v7 = flg | 0x80000008;
      }
      next->flg = v7;
    }
    next = next->next;
  }
  while (next);
  return 1;
}

// 0x2082b10
bool sBtlForceDelete_ID_SummonFR(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *wk) {
  SBTLEFF_WORK *next;
  u32 v7;
  u32 flg;

  if (!wk->effList)
    return 0;
  if (!lwk->num)
    return 0;
  next = lwk->wk;
  if (!next)
    return 0;
  do
  {
    if (next->effectid == 40 && wk->ListID == next->acterID)
    {
      flg = next->flg;
      if ((u32)(next->st - 1) > 1)
      {
        v7 = flg | 0x80000000;
        next->st = 4;
      }
      else
      {
        v7 = flg | 0x80000008;
      }
      next->flg = v7;
    }
    next = next->next;
  }
  while (next);
  return 1;
}

// 0x2082c30
bool sBtlForceDelete_ID_Return(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *wk) {
  SBTLEFF_WORK *next;
  u32 v7;
  u32 flg;

  if (!wk->effList)
    return 0;
  if (!lwk->num)
    return 0;
  next = lwk->wk;
  if (!next)
    return 0;
  do
  {
    if (next->effectid == 4 && wk->ListID == next->acterID)
    {
      flg = next->flg;
      if ((u32)(next->st - 1) > 1)
      {
        v7 = flg | 0x80000000;
        next->st = 4;
      }
      else
      {
        v7 = flg | 0x80000008;
      }
      next->flg = v7;
    }
    next = next->next;
  }
  while (next);
  return 1;
}

// 0x2082d50
bool sBtlFadeOut_BadStatusEffect(SBTLUNIT_WORK *wk, s32 alpha) {
  SBTLEFF_LISTWORK *effList;
  SBTLEFF_WORK *next;
  s32 bst_effserialID2;
  SBTLEFF_LISTWORK *v11;
  SBTLEFF_WORK *i;
  u32 v13;
  u32 flg;

  effList = wk->effList;
  if (!effList->num)
    return 0;
  next = effList->wk;
  if (!next)
    return 0;
  bst_effserialID2 = wk->bst_effserialID2;
  do
  {
    if (next->serialID2 == bst_effserialID2 && next->st == 3)
      next->alpha_cnt = alpha;
    next = next->next;
  }
  while (next);
  if ((wk->status & 0x800) == 0)
  {
    sBtlResetModelColor(wk);
    sBtlResetModelColor_DST(wk);
    bst_effserialID2 = wk->bst_effserialID2;
  }
  if (bst_effserialID2 == -1)
    return 1;
  bst_effserialID2 = wk->bst_effserialID2;
  v11 = wk->effList;
  if (v11->num)
  {
    for (i = v11->wk; i; i = i->next)
    {
      if (i->serialID2 == bst_effserialID2)
      {
        if (sBtlCheckDeleteEffect(i))
        {
          flg = i->flg;
          if ((u32)(i->st - 1) > 1)
          {
            v13 = flg | 0x80000000;
            i->st = 4;
          }
          else
          {
            v13 = flg | 0x80000008;
          }
          i->flg = v13;
        }
      }
    }
  }
  wk->bst_effserialID2 = -1;
  return 1;
}

// 0x2082fb0
bool sBtlSetDecAlpha_SerialID(SBTLEFF_LISTWORK *lwk, s32 serialID, s32 alpha) {
  SBTLEFF_WORK *wk;

  if (!lwk->num)
    return 0;
  wk = lwk->wk;
  if (!wk)
    return 0;
  do
  {
    if (wk->hitserialID != serialID)
      goto LABEL_6;
    if (!sBtlCheckDeleteEffect(wk))
      goto LABEL_6;
    if (wk->st == 3)
      wk->alpha_cnt = alpha;
LABEL_6:
    wk = wk->next;
  }
  while (wk);
  return 1;
}

// 0x2083090
bool sBtlForceDelete_SerialID(SBTLEFF_LISTWORK *lwk, s32 serialID) {
  SBTLEFF_WORK *wk;
  u32 v6;
  u32 flg;

  if (!lwk->num)
    return 0;
  wk = lwk->wk;
  if (!wk)
    return 0;
  do
  {
    if (wk->hitserialID != serialID)
      goto LABEL_8;
    if (!sBtlCheckDeleteEffect(wk))
      goto LABEL_8;
    flg = wk->flg;
    if ((u32)(wk->st - 1) > 1)
    {
      v6 = flg | 0x80000000;
      wk->st = 4;
    }
    else
    {
      v6 = flg | 0x80000008;
    }
    wk->flg = v6;
LABEL_8:
    wk = wk->next;
  }
  while (wk);
  return 1;
}

// 0x2083190
bool sBtlForceDelete_SkillFlag(u32 flg) {
  SBTLEFF_LISTWORK *effList;
  SBTLEFF_WORK *i;

  effList = wk->effList;
  if (!effList->num)
    return 1;
  for (i = effList->wk; i; i = i->next)
  {
    if ((sBtlGetSkilltbl(i->BEDsklid)->flg & flg) != 0)
    {
      if ((u32)(i->st - 1) > 1)
      {
        i->st = 5;
        i->alpha = 0;
      }
      else
      {
        i->flg |= 8u;
      }
    }
  }
  return 1;
}

// 0x2083290
bool sBtlForceDelete_SkillFlag_Acter(SBTLUNIT_WORK *wk, u32 flg) {
  SBATTLE_WORK *v6;
  SBTLEFF_LISTWORK *effList;
  SBTLEFF_WORK *i;

  v6 = wk;
  if (!v6)
    return 0;
  effList = v6->effList;
  if (!effList)
    return 0;
  if (wk->bYobidousa)
    return 0;
  effList = wk->effList;
  if (effList->num)
  {
    for (i = effList->wk; i; i = i->next)
    {
      if ((sBtlGetSkilltbl(i->BEDsklid)->flg & flg) != 0 && i->acterID == wk->ListID)
      {
        if ((u32)(i->st - 1) > 1)
        {
          i->st = 5;
          i->alpha = 0;
        }
        else
        {
          i->flg |= 8u;
        }
      }
    }
  }
  return 1;
}

// 0x2083420
bool sBtlForceDelete_SkillID_Acter(SBTLUNIT_WORK *wk, SKLID skillid) {
  SBATTLE_WORK *v6;
  SBTLEFF_LISTWORK *effList;
  SBTLEFF_WORK *next;
  s32 ListID;

  v6 = wk;
  if (!v6)
    return 0;
  effList = v6->effList;
  if (!effList)
    return 0;
  if (wk->bYobidousa)
    return 0;
  effList = wk->effList;
  if (effList->num)
  {
    next = effList->wk;
    if (next)
    {
      ListID = wk->ListID;
      do
      {
        if (next->acterID == ListID && next->BEDsklid == skillid)
        {
          if ((u32)(next->st - 1) > 1)
          {
            next->st = 5;
            next->alpha = 0;
          }
          else
          {
            next->flg |= 8u;
          }
        }
        next = next->next;
      }
      while (next);
    }
  }
  return 1;
}

// 0x20835a0
void sBtlForceDeleteAll(s32 flag) {
  SBTLEFF_LISTWORK *effList;
  SBTLEFF_WORK *wk_local;
  s32 num;
  bool v7;
  s32 BEDsklid;
  SBTLSKILLP_TBL *Skilltbl;
  s32 effectid;
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v16;
  SBTLUNIT_WORK *v17;
  s32 BEDtype;
  u32 flg;
  u32 v21;

  effList = wk->effList;
  wk_local = effList->wk;
  num = effList->num;
  if (wk_local)
    v7 = (u32)flag > 3;
  else
    v7 = 1;
  if (!v7 && num != 0)
  {
    while (1)
    {
      BEDsklid = wk_local->BEDsklid;
      if (flag == 1 && BEDsklid == 1012)
        goto LABEL_15;
      Skilltbl = sBtlGetSkilltbl(BEDsklid);
      if ((IndexOf_Int32Enum_(swordEffIdTbl, wk_local->effectid) & 0x80000000) == 0)
        goto LABEL_15;
      if (flag != 2)
        break;
LABEL_45:
      BEDtype = wk_local->BEDtype;
      if (BEDtype != 2 && BEDtype != 5 && (Skilltbl->flg & 0x100) == 0)
      {
        if (sBtlCheckDeleteEffect(wk_local))
        {
          flg = wk_local->flg;
          if ((u32)(wk_local->st - 1) > 1)
          {
            v21 = flg | 0x80000000;
            wk_local->st = 5;
            wk_local->alpha = 0;
          }
          else
          {
            v21 = flg | 0x80000008;
          }
          wk_local->flg = v21;
        }
      }
LABEL_15:
      wk_local = wk_local->next;
      if (!wk_local)
        return;
    }
    effectid = wk_local->effectid;
    if (effectid != 4)
    {
      if ((u32)(effectid - 79) >= 0xFFFFFFFA)
        goto LABEL_15;
      goto LABEL_36;
    }
    acterID = wk_local->acterID;
    UnitMng = wk->UnitMng;
    v16 = sBtlSearchUnit_ID(UnitMng, acterID);
    if (v16)
    {
      v17 = v16;
      if (!sBtlCheckReturn_Unit(v16))
        goto LABEL_36;
      NakamaReturnSet(v17);
    }
LABEL_36:
    if ((flag | 2) == 3)
    {
      if (wk_local->BEDtype == 2)
      {
        wk_local->st = 5;
        wk_local->alpha = 0;
      }
      if ((Skilltbl->flg & 0x100) != 0 && wk_local->BEDsklid != 295)
      {
        wk_local->st = 5;
        wk_local->alpha = 0;
      }
      sBtlCheckDeleteEffect(wk_local);
    }
    goto LABEL_45;
  }
}

// 0x2083880
void sBtlForceDeleteAll_TimeStopSkill(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wk2) {
  SBTLEFF_LISTWORK *effList;
  SBTLEFF_WORK *next;
  u32 v8;
  SBTLSKILLP_TBL *Skilltbl;
  s32 effectid;
  s32 v14;
  s32 v15;
  s32 v16;
  s32 v17;
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
  u32 flg;
  s32 BEDtype;
  u32 v30;

  goto LABEL_3;
LABEL_7:
  next = effList->wk;
  if (!next)
    return;
  while (1)
  {
    Skilltbl = sBtlGetSkilltbl(next->BEDsklid);
    effectid = next->effectid;
    if (effectid != swordEffIdTbl[0] && effectid != swordEffIdTbl[1] && effectid != swordEffIdTbl[2] && effectid != swordEffIdTbl[3] && effectid != swordEffIdTbl[4] && effectid != swordEffIdTbl[5] && effectid != swordEffIdTbl[6] && effectid != swordEffIdTbl[7] && effectid != swordEffIdTbl[8] && effectid != swordEffIdTbl[9] && effectid != swordEffIdTbl[10] && effectid != swordEffIdTbl[11] && effectid != swordEffIdTbl[12] && effectid != swordEffIdTbl[13] && effectid != swordEffIdTbl[14])
    {
      goto LABEL_76;
    }
    goto LABEL_9001;
    if (effectid != swordEffIdTbl[0])
    {
      v14 = next->effectid;
      if (v14 == swordEffIdTbl[1])
        goto LABEL_11;
      v15 = next->effectid;
      if (v15 == swordEffIdTbl[2])
        goto LABEL_11;
      v16 = next->effectid;
      if (v16 != swordEffIdTbl[3])
      {
        v17 = next->effectid;
        if (v17 == swordEffIdTbl[4])
          goto LABEL_11;
        v18 = next->effectid;
        if (v18 == swordEffIdTbl[5])
          goto LABEL_11;
        v19 = next->effectid;
        if (v19 == swordEffIdTbl[6])
          goto LABEL_11;
        v20 = next->effectid;
        if (v20 == swordEffIdTbl[7])
          goto LABEL_11;
        v21 = next->effectid;
        if (v21 == swordEffIdTbl[8])
          goto LABEL_11;
        v22 = next->effectid;
        if (v22 == swordEffIdTbl[9])
          goto LABEL_11;
        v23 = next->effectid;
        if (v23 == swordEffIdTbl[10])
          goto LABEL_11;
        v24 = next->effectid;
        if (v24 == swordEffIdTbl[11])
          goto LABEL_11;
        v25 = next->effectid;
        if (v25 == swordEffIdTbl[12])
          goto LABEL_11;
        v26 = next->effectid;
        if (v26 == swordEffIdTbl[13])
          goto LABEL_11;
        v27 = next->effectid;
        if (v27 == swordEffIdTbl[14])
          goto LABEL_11;
        effectid = next->effectid;
LABEL_76:
        if ((u32)(effectid - 79) <= 0xFFFFFFF9)
        {
          flg = Skilltbl->flg;
          if ((flg & 0x400) == 0 || (!wk || next->acterID != wk->ListID) && (!wk2 || next->acterID != wk2->ListID))
          {
            BEDtype = next->BEDtype;
            if (BEDtype != 2 && BEDtype != 5 && (flg & 0x100) == 0)
            {
              v30 = next->flg;
              if ((u32)(next->st - 1) > 1)
              {
                v8 = v30 | 0x80000000;
                next->st = 5;
                next->alpha = 0;
              }
              else
              {
                v8 = v30 | 0x80000008;
              }
              next->flg = v8;
            }
          }
        }
      }
    }
LABEL_9001:
LABEL_11:
    next = next->next;
    if (!next)
      return;
  }
LABEL_3:
  effList = wk->effList;
  if (effList->num)
    goto LABEL_7;
}

// 0x2083d60
bool sBtlForceReset(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *wk) {
  SBTLEFF_WORK *next;
  u32 v6;
  s32 BEDsklid;
  s32 v8;
  u32 flg;

  if (!lwk->num)
    return 0;
  next = lwk->wk;
  if (!next)
    return 0;
  do
  {
    if (next->acterID != wk->ListID)
      goto LABEL_8;
    if ((next->flg & 2) == 0 || (u32)(next->st - 1) >= 2)
    {
      BEDsklid = next->BEDsklid;
      if (BEDsklid > 442)
      {
        if ((u32)BEDsklid <= 0x1D4)
        {
          if ((u32)(BEDsklid - 449) > 0x13 || ((1 << (BEDsklid + 63)) & 0x80005) == 0)
            goto LABEL_8;
        }
        else if (BEDsklid != 472 && BEDsklid != 1120 && BEDsklid != 477)
        {
          goto LABEL_8;
        }
LABEL_29:
        if (next->BEDtype == 2)
        {
          v8 = next->BEDsklid;
          if (v8 == 451 || v8 == 1120)
            goto LABEL_8;
        }
        goto LABEL_32;
      }
      if (BEDsklid <= 420)
      {
        if ((u32)(BEDsklid - 418) >= 3 && BEDsklid != 152)
          goto LABEL_8;
      }
      else if ((u32)(BEDsklid - 425) > 0x11 || ((1 << (BEDsklid + 87)) & 0x25D05) == 0)
      {
        goto LABEL_8;
      }
      goto LABEL_29;
    }
LABEL_32:
    if (!sBtlCheckDeleteEffect(next))
      goto LABEL_8;
    flg = next->flg;
    if ((u32)(next->st - 1) > 1)
    {
      v6 = flg | 0x80000000;
      next->st = 4;
    }
    else
    {
      v6 = flg | 0x80000008;
    }
    next->flg = v6;
LABEL_8:
    next = next->next;
  }
  while (next);
  return 1;
}

// 0x2083f50
bool sBtlForceReset_Tatari(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *wk) {
  SBTLEFF_WORK *next;
  s32 ListID;
  u32 flg;
  s32 BEDsklid;

  if (!lwk->num)
    return 0;
  next = lwk->wk;
  if (!next)
    return 0;
  ListID = wk->ListID;
  do
  {
    if (next->acterID == ListID)
    {
      BEDsklid = next->BEDsklid;
      if (BEDsklid == 1131 || BEDsklid == 443)
      {
        flg = next->flg;
        next->st = 4;
        next->flg = flg | 0x80000000;
      }
    }
    next = next->next;
  }
  while (next);
  return 1;
}

// 0x2083fc0
bool sBtlForceResetDecAlpha(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *wk, s32 alpha) {
  SBTLEFF_WORK *next;
  u32 v8;
  u32 flg;

  if (!lwk->num)
    return 0;
  next = lwk->wk;
  if (!next)
    return 0;
  do
  {
    if (next->acterID != wk->ListID)
      goto LABEL_8;
    if (!sBtlCheckDeleteEffect(next))
      goto LABEL_8;
    flg = next->flg;
    if ((u32)(next->st - 1) > 1)
    {
      v8 = flg | 0x80000000;
      next->st = 4;
      next->alpha_cnt = alpha;
    }
    else
    {
      v8 = flg | 0x80000008;
    }
    next->flg = v8;
LABEL_8:
    next = next->next;
  }
  while (next);
  return 1;
}

// 0x20840d0
bool sBtlReleaseEff(SBTLEFF_LISTWORK *lwk, bool flg) {
  bool v3;
  SBTLEFF_WORK *p_wk;
  SBTLEFF_WORK *wk_local;
  s32 st;
  SBTLEFF_WORK *v9;
  s32 BEDsklid;
  u32 BEDtype;
  u32 v13;
  SBTLEFF_WORK *prev;
  SBTLEFF_WORK *v15;
  SBTLEFF_WORK *next;
  SBTLEFF_WORK *v17;
  SBTLEFF_WORK *v18;
  SBTLEFF_DATAWORK *dwk;
  void *hPartsList;
  SBTLEFF_DATAWORK *v21;
  SBTLEFF_DATAWORK *v22;
  SBTLEFF_DATAWORK *p_fields;
  plistHandle_t_Resource *pData;
  SBTLDMG_HITLISTWORK *hitList;
  s32 hitserialID;
  SBTLDMG_HITWORK *v29;
  SBTLEFF_LISTWORK *effList;
  SBTLEFF_WORK *v32;
  s32 v33;
  u32 v34;
  char v35;
  char v37;

  v3 = flg;
  goto LABEL_3;
  if (!wk->effList)
  {
LABEL_77:
    v35 = 1;
    return v35 & 1;
  }
  goto LABEL_7;
LABEL_3:
  if (!wk->effList)
    goto LABEL_77;
LABEL_7:
  p_wk = &lwk->wk;
  wk_local = lwk->wk;
  if (!wk_local || !lwk->num)
    goto LABEL_77;
  v37 = 0;
  do
  {
    while (1)
    {
      while (1)
      {
        while (1)
        {
          st = wk_local->st;
          v9 = wk_local;
          if (v3)
          {
            if ((u32)(st - 1) >= 2)
            {
              wk_local->st = 5;
              goto LABEL_17;
            }
            wk_local->flg |= 8u;
            v37 = 1;
          }
          if ((u32)(st - 3) <= 0xFFFFFFFD)
            break;
          if ((wk->status & 8) != 0)
            goto LABEL_52;
          goto LABEL_9000;
          if ((wk->status & 8) != 0)
LABEL_52:
            wk_local->st = 5;
LABEL_9000:
LABEL_10:
          wk_local = wk_local->next;
          if (!wk_local)
            goto LABEL_76;
        }
        if (st != 5)
          goto LABEL_10;
LABEL_17:
        sBtlDltHitEff(wk_local);
        BEDsklid = wk_local->BEDsklid;
        BEDtype = wk_local->BEDtype;
        v13 = wk_local->flg;
        prev = wk_local->prev;
        if (!prev)
        {
          *(u64 *)&flg = 0;
          next = wk_local->next;
          if (!next)
            goto LABEL_20;
LABEL_19:
          next->prev = (SBTLEFF_WORK *)flg;
          *(u64 *)&flg = wk_local->prev;
          goto LABEL_20;
        }
        v15 = wk_local->next;
        prev->next = v15;
        *(u64 *)&flg = wk_local->prev;
        next = wk_local->next;
        if (next)
          goto LABEL_19;
LABEL_20:
        if (!flg)
        {
          v17 = wk_local->next;
          p_wk = v17;
          v18 = p_wk;
          if (p_wk)
          {
            v18->prev = 0;
          }
        }
        dwk = wk_local->dwk;
        wk_local = wk_local->next;
        hPartsList = dwk->hPartsList;
        if (hPartsList)
        {
          effPartsDelete(hPartsList);
          v21 = v9->dwk;
          v21->hPartsList = 0;
        }
        if ((v9->flg & 1) == 0)
        {
          v22 = v9->dwk;
          pData = v22->pData;
          p_fields = &v22->fields;
          if (pData)
          {
            p_fields->pData = 0;
          }
        }
        hitList = wk->hitList;
        if (!hitList)
          goto LABEL_43;
        hitserialID = v9->hitserialID;
        v29 = sBtlSearchHit_SerialID(hitList, hitserialID);
        if (!v29)
          goto LABEL_43;
        v29->st = 2;
LABEL_43:
        --lwk->num;
        if ((v13 & 0x80000000) != 0)
          break;
LABEL_44:
        if (!wk_local)
          goto LABEL_76;
      }
      effList = wk->effList;
      if (!effList->num)
        goto LABEL_72;
      v32 = effList->wk;
      if (v32)
      {
        if (BEDtype <= 1)
        {
          while (1)
          {
            if (v32->BEDsklid == BEDsklid)
            {
              v34 = v32->BEDtype;
              if (v34 <= BEDtype)
                break;
            }
            v32 = v32->next;
            if (!v32)
              goto LABEL_72;
          }
        }
        else
        {
          while (1)
          {
            if (v32->BEDsklid == BEDsklid)
            {
              v33 = v32->BEDtype;
              if (v33 == BEDtype)
                break;
            }
            v32 = v32->next;
            if (!v32)
              goto LABEL_72;
          }
        }
        goto LABEL_44;
      }
LABEL_72:
      sBtlStopSkillSE(BEDsklid, BEDtype);
      if (!wk_local)
        goto LABEL_76;
    }
    sBtlStopSkillSE(BEDsklid, BEDtype);
  }
  while (wk_local);
LABEL_76:
  v35 = v37 & v3 ^ 1;
  return v35 & 1;
}

// 0x20846a0
bool sBtlDeleteEffList(SBTLEFF_LISTWORK *lwk) {
  SBTLEFF_LISTWORK *v5;

  v5 = lwk;
  return sBtlReleaseEff(v5, 1);
}

// 0x2084730
s32 sBtlGetNumOfEffect_SAB(SBTLEFF_LISTWORK *lwk, SBTLEFF_BEDTYPE BEDtype, SBTLUNIT_SIDE side) {
  SBTLEFF_WORK *wk;
  u32 v8;
  s32 v11;
  s32 v12;
  u32 v14;

  if (!lwk->num)
    return 0;
  wk = lwk->wk;
  if (wk)
  {
    v8 = BEDtype;
    if (BEDtype >= 2u)
    {
      v11 = 0;
      while (1)
      {
        v12 = wk->BEDtype;
        if (v12 == v8)
        {
          if ((wk->BEDacterside & side) != 0)
            ++v11;
        }
        wk = wk->next;
        if (!wk)
          return v11;
      }
      do
      {
        if (wk->BEDtype == v8 && (wk->BEDacterside & side) != 0)
          ++v11;
        wk = wk->next;
      }
      while (wk);
      return v11;
    }
    v11 = 0;
    while (1)
    {
      v14 = wk->BEDtype;
      if (v14 <= v8)
      {
        if ((wk->BEDacterside & side) != 0)
          ++v11;
      }
      wk = wk->next;
      if (!wk)
        return v11;
    }
    do
    {
      if (wk->BEDtype <= v8 && (wk->BEDacterside & side) != 0)
        ++v11;
      wk = wk->next;
    }
    while (wk);
    return v11;
  }
  return 0;
}

// 0x2084590
bool sBtlSearchEffect_SAB(SBTLEFF_LISTWORK *lwk, SKLID BEDsklid, SBTLEFF_BEDTYPE BEDtype) {
  SBTLEFF_WORK *wk;
  s32 v8;
  u32 v9;

  if (!lwk->num)
    return 0;
  wk = lwk->wk;
  if (!wk)
    return 0;
  if (BEDtype > 1u)
  {
    while (1)
    {
      if (wk->BEDsklid == BEDsklid)
      {
        v8 = wk->BEDtype;
        if (v8 == BEDtype)
          break;
      }
      wk = wk->next;
      if (!wk)
        return 0;
    }
  }
  else
  {
    while (1)
    {
      if (wk->BEDsklid == BEDsklid)
      {
        v9 = wk->BEDtype;
        if (v9 <= BEDtype)
          break;
      }
      wk = wk->next;
      if (!wk)
        return 0;
    }
  }
  return 1;
}

// 0x20848d0
bool sBtlSearchEffect_SAB_Acter(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *wk, SKLID BEDsklid, s32 BEDtype) {
  u8 v5;
  SBTLEFF_WORK *i;
  u32 v11;
  s32 acterID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v15;

  v5 = BEDtype;
  if (lwk->num)
  {
    for (i = lwk->wk; i; i = i->next)
    {
      if (i->BEDsklid != BEDsklid)
        continue;
      if (!i->BEDsklid)
        continue;
      if ((wk2->effpac[i->workID]->status & 1) == 0)
        continue;
      v11 = i->BEDtype;
      if (v5 > 1u)
      {
        if (v11 != v5)
          continue;
        goto LABEL_23;
      }
      if (v11 > v5)
        continue;
LABEL_23:
      acterID = i->acterID;
      UnitMng = wk->UnitMng;
      v15 = sBtlSearchUnit_ID(UnitMng, acterID);
      if (v15 && wk->ListID == v15->ListID)
        return 1;
    }
  }
  return 0;
}

// 0x2084ab0
bool sBtlSearchEffect_ID(SBTLEFF_LISTWORK *lwk, EFFID effectid) {
  SBTLEFF_WORK *wk;
  s32 v4;
  bool result;

  if (!lwk->num)
    return 0;
  wk = lwk->wk;
  if (!wk)
    return 0;
  do
  {
    v4 = wk->effectid;
    result = v4 == effectid;
    if (v4 == effectid)
      break;
    wk = wk->next;
  }
  while (wk);
  return result;
}

// 0x2084af0
bool sBtlSearchEffect_WorkID(SBTLEFF_LISTWORK *lwk, s32 workid) {
  SBTLEFF_WORK *wk;
  s32 v4;
  bool result;

  if (!lwk->num)
    return 0;
  wk = lwk->wk;
  if (!wk)
    return 0;
  do
  {
    v4 = wk->workID;
    result = v4 == workid;
    if (v4 == workid)
      break;
    wk = wk->next;
  }
  while (wk);
  return result;
}

// 0x2084b30
bool sBtlInitEffectWork(void) {
  s64 v1;
  s64 i;
  s32 *effpac;
  SBTLEFF_PACLIST *v5;

  v1 = 0;
  for (i = 8; ; i += 2)
  {
    effpac = wk2->effpac;
    if (v1 >= effpac[6])
      break;
    v5 = Allocate(SBTLEFF_PACLIST);
    _ctor(v5, 0);
    if (v5)
      QueryInterface(v5, *(void **)(*(u64 *)effpac + 64));
    *(u64 *)&effpac[i] = v5;
    ++v1;
  }
  return 1;
}

// 0x2084c70
bool sBtlCheckLoadEnd_EffectWork(void) {
  bool v3;
  s64 v4;
  SBTLEFF_PACLIST *v5;
  u64 v6;
  s32 skillID;

  v3 = 0;
  v4 = 4;
  while (1)
  {
    if (*(s16 *)(*((u64 *)&wk2->effpac->obj.klass + v4) + 36) < 1)
      goto LABEL_5;
    if ((*(u16 *)(*((u64 *)&wk2->effpac->obj.klass + v4) + 38) & 4) == 0)
      goto LABEL_13;
LABEL_5:
    v6 = v4 - 4;
    ++v4;
    v3 = v6 > 0x94;
    if (v4 == 154)
      return v3;
  }
  if ((*(u16 *)(*((u64 *)&wk2->effpac->obj.klass + v4) + 38) & 4) != 0)
    goto LABEL_5;
LABEL_13:
  v5 = *((SBTLEFF_PACLIST *)&wk2->effpac->obj.klass + v4);
  if ((v5->status & 1) != 0)
    goto LABEL_5;
  v5 = *((SBTLEFF_PACLIST *)&wk2->effpac->obj.klass + v4);
  skillID = v5->skillID;
  CheckLoadEffectData(v5, skillID, 0, 0);
  return v3;
}

// 0x2084e00
SBTLEFF_DELLISTWORK *sBtlCreateDelList(void) {
  SBTLEFF_DELLISTWORK *v1;

  v1 = (SBTLEFF_DELLISTWORK *)Allocate(SBTLEFF_DELLISTWORK);
  _ctor(v1, 0);
  v1->num = 0;
  v1->dwk = 0;
  return v1;
}

// 0x2084e70
bool sBtlCheckDelWork_Request(SBTLEFF_DELLISTWORK *lwk, s32 GroupID) {
  SBTLEFF_DELWORK *dwk;
  s32 v4;

  if (lwk)
  {
    dwk = lwk->dwk;
    LOBYTE(lwk) = dwk
               && lwk->num
               && dwk->gstat == 1
               && (v4 = dwk->GroupID, v4 != -1)
               && v4 == GroupID;
  }
  return (char)lwk;
}

// 0x2084ec0
bool sBtlSearchDelWork_Side(SBTLEFF_DELLISTWORK *lwk, SBTLUNIT_SIDE side) {
  SBTLEFF_DELWORK *dwk;
  s32 sklid;
  SBTLEFF_LISTWORK *effList;
  SBTLEFF_WORK *i;
  s32 v11;
  SBTLEFF_LISTWORK *v12;
  u32 BEDtype;
  SBTLEFF_WORK *j;
  s32 v16;
  SBTLEFF_LISTWORK *v17;
  s32 v18;
  SBTLEFF_WORK *wk_local;
  s32 v20;

  if (!lwk)
    return 0;
  dwk = lwk->dwk;
  if (!dwk || !lwk->num)
    return 0;
  while (dwk->gstat != 1 || (dwk->side & side) == 0)
  {
LABEL_7:
    dwk = dwk->next;
    if (!dwk)
      return 0;
  }
  sklid = dwk->sklid;
  effList = wk->effList;
  if (effList->num)
  {
    for (i = effList->wk; i; i = i->next)
    {
      if (i->BEDsklid == sklid)
      {
        BEDtype = i->BEDtype;
        if (BEDtype < 2)
          goto LABEL_7;
      }
    }
  }
  v11 = dwk->sklid;
  v12 = wk->effList;
  if (v12->num)
  {
    for (j = v12->wk; j; j = j->next)
    {
      if (j->BEDsklid == v11)
      {
        v18 = j->BEDtype;
        if (v18 == 2)
          goto LABEL_7;
      }
    }
  }
  v16 = dwk->sklid;
  v17 = wk->effList;
  if (!v17->num)
    return 1;
  wk_local = v17->wk;
  if (wk_local)
  {
    while (1)
    {
      if (wk_local->BEDsklid == v16)
      {
        v20 = wk_local->BEDtype;
        if (v20 == 5)
          break;
      }
      wk_local = wk_local->next;
      if (!wk_local)
        return 1;
    }
    goto LABEL_7;
  }
  return 1;
}

// 0x2085170
bool sBtlCreateDelWork(SBTLEFF_DELLISTWORK *lwk, SKLID skillid, SBTLUNIT_SIDE side, s32 GroupID) {
  SBTLEFF_DELWORK *v9;
  SBTLEFF_DELWORK *dwk;
  SBTLEFF_DELWORK *v11;
  s32 v12;

  v9 = Allocate(SBTLEFF_DELWORK);
  _ctor(v9, 0);
  v9->prev = 0;
  v9->next = 0;
  dwk = lwk->dwk;
  if (dwk)
  {
    do
    {
      v11 = dwk;
      dwk = dwk->next;
    }
    while (dwk);
    v11->next = v9;
    v9->prev = v11;
    v12 = lwk->num + 1;
  }
  else
  {
    lwk->dwk = v9;
    v12 = 1;
  }
  lwk->num = v12;
  v9->GroupID = GroupID;
  v9->side = side;
  v9->gstat = 1;
  v9->sklid = skillid;
  return 1;
}

// 0x2085280
bool sBtlDelProc(SBTLEFF_DELLISTWORK *lwk) {
  SBTLEFF_DELWORK *dwk;
  s32 v5;
  s32 gstat;
  s32 sklid;
  SBTLEFF_LISTWORK *effList;
  SBTLEFF_WORK *i;
  s32 v12;
  SBTLEFF_LISTWORK *v13;
  u32 BEDtype;
  SBTLEFF_WORK *j;
  s32 v17;
  SBTLEFF_LISTWORK *v18;
  s32 v19;
  SBTLEFF_WORK *wk_local;
  s32 v21;
  s32 v22;

  if (!lwk)
    return 0;
  dwk = lwk->dwk;
  if (!dwk || !lwk->num)
    return 0;
  do
  {
    gstat = dwk->gstat;
    if (gstat == 2)
    {
      v5 = 3;
LABEL_8:
      dwk->gstat = v5;
      goto LABEL_9;
    }
    if (gstat == 1)
    {
      sklid = dwk->sklid;
      effList = wk->effList;
      if (effList->num)
      {
        for (i = effList->wk; i; i = i->next)
        {
          if (i->BEDsklid == sklid)
          {
            BEDtype = i->BEDtype;
            if (BEDtype < 2)
              goto LABEL_9;
          }
        }
      }
      v12 = dwk->sklid;
      v13 = wk->effList;
      if (v13->num)
      {
        for (j = v13->wk; j; j = j->next)
        {
          if (j->BEDsklid == v12)
          {
            v19 = j->BEDtype;
            if (v19 == 2)
              goto LABEL_9;
          }
        }
      }
      v17 = dwk->sklid;
      v18 = wk->effList;
      if (!v18->num)
        goto LABEL_49;
LABEL_48:
      wk_local = v18->wk;
      if (!wk_local)
      {
LABEL_49:
        v21 = dwk->sklid;
        sBtlForceDelete_EffectWork_ID(v21, 1);
        v5 = 2;
        goto LABEL_8;
      }
      while (1)
      {
        if (wk_local->BEDsklid == v17)
        {
          v22 = wk_local->BEDtype;
          if (v22 == 5)
            goto LABEL_9;
        }
        wk_local = wk_local->next;
        if (!wk_local)
          goto LABEL_49;
      }
      if (!v18->num)
        goto LABEL_49;
      goto LABEL_48;
    }
LABEL_9:
    dwk = dwk->next;
  }
  while (dwk);
  return 1;
}

// 0x2085ac0
bool sBtlReleaseDelList(SBTLEFF_DELLISTWORK *lwk, u8 flg) {
  SBTLEFF_DELLISTWORK *v3;
  SBTLEFF_DELWORK *p_dwk;
  SBTLEFF_DELWORK *dwk;
  SBTLEFF_DELWORK *prev;
  SBTLEFF_DELWORK *v7;
  SBTLEFF_DELWORK *next;
  SBTLEFF_DELWORK *v9;
  SBTLEFF_DELWORK *v10;
  SBTLEFF_DELWORK *v11;
  SBTLEFF_DELWORK *v12;
  SBTLEFF_DELWORK *v13;
  SBTLEFF_DELWORK *v14;
  SBTLEFF_DELWORK *v15;
  SBTLEFF_DELWORK *v16;
  SBTLEFF_DELWORK *v17;

  if (lwk)
  {
    v3 = lwk;
    p_dwk = &lwk->dwk;
    dwk = lwk->dwk;
    if (dwk && lwk->num)
    {
      if (flg)
      {
        while (1)
        {
          prev = dwk->prev;
          dwk->gstat = 3;
          if (prev)
            break;
          v9 = 0;
          next = dwk->next;
          if (next)
            goto LABEL_9;
LABEL_10:
          if (!v9)
          {
            v10 = dwk->next;
            p_dwk = v10;
            v11 = p_dwk;
            if (p_dwk)
            {
              v11->prev = 0;
            }
          }
          dwk = dwk->next;
          --v3->num;
          if (!dwk)
            goto LABEL_28;
        }
        v7 = dwk->next;
        prev->next = v7;
        v9 = dwk->prev;
        next = dwk->next;
        if (!next)
          goto LABEL_10;
LABEL_9:
        next->prev = v9;
        v9 = dwk->prev;
        goto LABEL_10;
      }
      while (1)
      {
        while (dwk->gstat != 3)
        {
          dwk = dwk->next;
          if (!dwk)
            goto LABEL_28;
        }
        v12 = dwk->prev;
        if (v12)
          break;
        v15 = 0;
        v14 = dwk->next;
        if (v14)
          goto LABEL_19;
LABEL_20:
        if (!v15)
        {
          v16 = dwk->next;
          p_dwk = v16;
          v17 = p_dwk;
          if (p_dwk)
          {
            v17->prev = 0;
          }
        }
        dwk = dwk->next;
        --v3->num;
        if (!dwk)
        {
LABEL_28:
          LOBYTE(lwk) = 1;
          return (char)lwk;
        }
      }
      v13 = dwk->next;
      v12->next = v13;
      v15 = dwk->prev;
      v14 = dwk->next;
      if (!v14)
        goto LABEL_20;
LABEL_19:
      v14->prev = v15;
      v15 = dwk->prev;
      goto LABEL_20;
    }
    LOBYTE(lwk) = 0;
  }
  return (char)lwk;
}

// 0x2085c30
bool sBtlDeleteDelList(SBTLEFF_DELLISTWORK *lwk) {
  sBtlReleaseDelList(lwk, 1u);
  return 1;
}

// 0x2085ca0
bool sBtlDeleteHaveSkill_EffectWork(SBTLUNIT_WORK *wk) {
  SKLID *v3;
  s64 v4;
  s32 *v5;
  SBTLEFF_DELLISTWORK *v6;
  s32 v7;
  s32 v8;
  s32 v9;
  s32 v10;
  s32 ExeSkill;
  s64 i;
  SBATTLE_WORK *v15;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s64 v18;
  s32 ExeSkill_33327568;
  s32 side;
  SBTLEFF_DELLISTWORK *effdelList;
  s32 v24;
  SBTLEFF_DELLISTWORK *v25;
  s32 v26;
  s32 v27;
  s32 v28;
  SBTLEFF_DELLISTWORK *v30;
  s32 v31;
  s32 GroupID;
  s64 v33;
  SBATTLE_WORK *v35;
  SBTLUNIT_LISTWORK *v36;
  SBTLUNIT_WORK *v37;
  s64 v38;
  s32 v39;
  s32 v40;
  u32 v41;
  SBTLEFF_DELLISTWORK *v42;
  s32 v43;
  SBTLEFF_DELLISTWORK *v44;
  s32 v45;
  s32 v46;

  v3 = NewSpecific(SKLID, 2u);
  v4 = 0;
  v5 = &v3[1];
  while (2)
  {
    if ((sBtlGetSkilltbl(wk->haveskill[v4])->flg2 & 0x1000) != 0)
      goto LABEL_6;
    v10 = wk->haveskill[v4];
    switch (v10)
    {
      case 0:
        goto LABEL_6;
      case 149:
        goto LABEL_6;
      case 288:
        goto LABEL_6;
    }
    ExeSkill = sBtlGetExeSkill(v10, v5);
    v3[0] = ExeSkill;
    if (!ExeSkill)
      goto LABEL_6;
    for (i = 0; ; ++i)
    {
      v15 = wk;
      UnitMng = v15->UnitMng;
      if (i >= UnitMng->number)
      {
        side = wk->side;
        if ((side & 2) == 0)
        {
          effdelList = v15->effdelList;
          v24 = v3[0];
          v25 = effdelList;
          v26 = v24;
          v27 = side;
          v28 = -1;
LABEL_35:
          sBtlCreateDelWork(v25, v26, v27, v28);
          goto LABEL_36;
        }
        v30 = v15->effdelList;
        v31 = v3[0];
        GroupID = wk->GroupID;
        v25 = v30;
        v26 = v31;
        v27 = side;
        v28 = GroupID;
        goto LABEL_35;
      }
      pUnit = UnitMng->pUnitL[i]->pUnit;
      if (pUnit)
        goto LABEL_21;
LABEL_13:
      ;
    }
    pUnit = wk->UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      goto LABEL_13;
LABEL_21:
    if (pUnit->ListID == wk->ListID)
      goto LABEL_13;
    v18 = 32;
    while (1)
    {
      ExeSkill_33327568 = *(u32 *)((char *)&pUnit->haveskill->obj.klass + v18);
      if ((sBtlGetSkilltbl(ExeSkill_33327568)->flg2 & 1) != 0)
        ExeSkill_33327568 = GetExeSkill(ExeSkill_33327568);
      if (ExeSkill_33327568 == v3[0])
        break;
      v18 += 4;
      if (v18 == 108)
        goto LABEL_13;
    }
LABEL_36:
    if (!*v5)
      goto LABEL_6;
    v33 = 0;
    while (2)
    {
      v35 = wk;
      v36 = v35->UnitMng;
      if (v33 >= v36->number)
      {
        v40 = wk->side;
        if ((v40 & 2) != 0)
        {
          if (!v41)
          {
            v40 = wk->side;
            v35 = wk;
          }
          v44 = v35->effdelList;
          v45 = *v5;
          v46 = wk->GroupID;
          v6 = v44;
          v7 = v45;
          v8 = v40;
          v9 = v46;
        }
        else
        {
          if (!v41)
          {
            v40 = wk->side;
            v35 = wk;
          }
          v42 = v35->effdelList;
          v43 = *v5;
          v6 = v42;
          v7 = v43;
          v8 = v40;
          v9 = -1;
        }
        sBtlCreateDelWork(v6, v7, v8, v9);
        goto LABEL_6;
      }
      v37 = wk->UnitMng->pUnitL[v33]->pUnit;
      if (!v37)
        goto LABEL_38;
      if (v37->ListID == wk->ListID)
      {
LABEL_38:
        ++v33;
        continue;
      }
      break;
    }
    v38 = 32;
    while (1)
    {
      v39 = *(u32 *)((char *)&v37->haveskill->obj.klass + v38);
      if ((sBtlGetSkilltbl(v39)->flg2 & 1) != 0)
        v39 = GetExeSkill(v39);
      if (v39 == *v5)
        break;
      v38 += 4;
      if (v38 == 108)
        goto LABEL_38;
    }
LABEL_6:
    if (++v4 != 19)
      continue;
    return 1;
  }
}

// 0x2085570
bool sBtlForceDelete_EffectWork_ID(SKLID id, s8 flg) {
  s64 v7;
  s64 v8;
  SBTLEFF_PACLIST *v9;
  u16 status;
  s64 v11;
  s32 num;
  s64 v15;
  SBTLEFF_PACDATAWORK *pwk;
  s64 v17;
  SBTLEFF_PACDATAWORK *v18;
  SBTLEFF_PACDATAWORK *v19;
  SBTLSKLHIT_PACLIST *hwk;
  s64 v21;
  s64 v22;
  s64 v23;
  void *v24;
  s64 v25;
  s64 v26;
  s64 v27;
  s64 v29;
  SBTLEFF_PACLIST *v30;
  SBATTLE_WORK2 *wk2_local;
  SBTLEFF_PACLIST *v33;
  s16 *p_effpaccnt;
  s16 effpaccnt;

  v7 = 0;
  while (1)
  {
    v8 = (s64)wk2->effpac + 8 * v7;
    if (*(u32 *)(*(u64 *)(v8 + 32) + 40) == id)
      goto LABEL_20;
    if (*(u32 *)(*(u64 *)(v8 + 40) + 40) == id)
    {
      LODWORD(v7) = v7 + 1;
      goto LABEL_20;
    }
    v7 += 2;
    if (v7 == 150)
      return 1;
  }
  v7 = 0;
  while (1)
  {
    if (wk2->effpac[v7]->skillID == id)
      break;
    if (++v7 == 150)
      return 1;
  }
LABEL_20:
  if ((u32)v7 == -1)
    return 1;
  v9 = wk2->effpac[(s32)v7];
  status = v9->status;
  if ((status & 0x20) != 0)
    return 1;
  v11 = (s32)v7;
  v9 = wk2->effpac[(s32)v7];
  status = v9->status;
  if (flg != 1 && (status & 4) != 0)
    return 1;
  if ((status & 1) == 0)
    goto LABEL_30;
  v9 = wk2->effpac[(s32)v7];
  num = v9->num;
  v9->SMGID = 0;
  if (num >= 1)
  {
    v15 = 0;
    while (1)
    {
      pwk = v9->pwk;
      v17 = v15;
      v18 = pwk[v15];
      if (v18->hPartsList)
      {
        effPartsDelete(v18->hPartsList);
        v19 = v9->pwk[v17];
        v19->hPartsList = 0;
        pwk = v9->pwk;
        v18 = pwk[v17];
      }
      if (v18->flg)
      {
        hwk = v18->hwk;
        if (hwk->num >= 1)
          break;
      }
LABEL_39:
      v18->pData = 0;
      if (++v15 >= v9->num)
        goto LABEL_56;
    }
    v21 = 4;
    while (1)
    {
      v23 = *((u64 *)&hwk->pwk->obj.klass + v21);
      if (v23)
        break;
LABEL_46:
      v22 = v21 - 3;
      ++v21;
      v18 = pwk[v15];
      hwk = v18->hwk;
      if (v22 >= hwk->num)
        goto LABEL_39;
    }
    v24 = *(void *)(v23 + 16);
    if (!op_Inequality(v24, 0, 0))
      goto LABEL_51;
    goto LABEL_9001;
    if (!op_Inequality(v24, 0, 0))
    {
LABEL_51:
      pwk = v9->pwk;
      v26 = *((u64 *)&pwk[v15]->hwk->pwk->obj.klass + v21);
      if (*(u64 *)(v26 + 32))
      {
        if (*(u64 *)(v26 + 24))
        {
          effPartsDelete(*(void *)(v26 + 24));
          v27 = *((u64 *)&v9->pwk[v17]->hwk->pwk->obj.klass + v21);
          *(u64 *)(v27 + 24) = 0;
          v26 = *((u64 *)&v9->pwk[v17]->hwk->pwk->obj.klass + v21);
        }
        *(u64 *)(v26 + 32) = 0;
        pwk = v9->pwk;
      }
      goto LABEL_46;
    }
LABEL_9001:
    v25 = *((u64 *)&v9->pwk[v15]->hwk->pwk->obj.klass + v21);
    *(u64 *)(v25 + 16) = 0;
    goto LABEL_51;
  }
LABEL_56:
  v29 = v11;
  v30 = wk2->effpac[v29];
  v30->pData = 0;
  wk2_local = wk2;
  v33 = wk2_local->effpac[v29];
  *(u32 *)&v33->gstat = 0;
  *(u64 *)&v33->skillID = 0xFFFFFFFFLL;
  wk2_local = wk2;
  effpaccnt = wk2_local->effpaccnt;
  p_effpaccnt = &wk2_local->effpaccnt;
  *p_effpaccnt = effpaccnt - 1;
  LimitRange_2(p_effpaccnt, 0, 149);
  return 1;
LABEL_30:
  v9 = wk2->effpac[(s32)v7];
  return !v9->gstat;
}

// 0x2086190
bool sBtlForceDelete_EffectWork(s8 flg) {
  u64 v3;
  bool v5;
  SBTLEFF_PACLIST *v7;
  u16 status;
  s32 num;
  s64 v12;
  SBTLEFF_PACDATAWORK *pwk;
  s64 v14;
  SBTLEFF_PACDATAWORK *v15;
  SBTLEFF_PACDATAWORK *v16;
  SBTLSKLHIT_PACLIST *hwk;
  s64 v18;
  s64 v19;
  SBTLSKLHIT_PACDATAWORK *v20;
  s64 v21;
  void *v22;
  s64 v23;
  s64 v24;
  s64 v25;
  SBTLEFF_PACLIST *v27;
  SBATTLE_WORK2 *wk2_local;
  SBTLEFF_PACLIST *v30;
  s16 *p_effpaccnt;
  s16 effpaccnt;

  v3 = 0;
  v5 = 0;
  do
  {
    if (flg == 2)
      goto LABEL_62;
    status = wk2->effpac[v3]->status;
    if ((status & 0x20) == 0)
    {
      status = wk2->effpac[v3]->status;
      if (flg == 1 || (status & 4) == 0)
      {
LABEL_62:
        v7 = wk2->effpac[v3];
        if ((v7->status & 1) != 0)
        {
          num = v7->num;
          v7->SMGID = 0;
          if (num >= 1)
            goto LABEL_30;
LABEL_49:
          v27 = wk2->effpac[v3];
          v27->pData = 0;
          wk2_local = wk2;
          v30 = wk2_local->effpac[v3];
          *(u32 *)&v30->gstat = 0;
          *(u64 *)&v30->skillID = 0xFFFFFFFFLL;
          wk2_local = wk2;
          effpaccnt = wk2_local->effpaccnt;
          p_effpaccnt = &wk2_local->effpaccnt;
          *p_effpaccnt = effpaccnt - 1;
          LimitRange_2(p_effpaccnt, 0, 149);
          goto LABEL_5;
LABEL_30:
          v12 = 0;
          while (1)
          {
            pwk = v7->pwk;
            v14 = v12;
            v15 = pwk[v12];
            if (v15->hPartsList)
            {
              effPartsDelete(v15->hPartsList);
              v16 = v7->pwk[v14];
              v16->hPartsList = 0;
              pwk = v7->pwk;
              v15 = pwk[v14];
            }
            if (v15->flg)
            {
              hwk = v15->hwk;
              if (hwk->num >= 1)
                break;
            }
LABEL_31:
            v15->pData = 0;
            if (++v12 >= v7->num)
              goto LABEL_49;
          }
          v18 = 0;
          v19 = 32;
          while (2)
          {
            v21 = *(s64 *)((char *)&hwk->pwk->obj.klass + v19);
            if (v21)
            {
              v22 = *(void *)(v21 + 16);
              if (op_Inequality(v22, 0, 0))
              {
                v23 = *(s64 *)((char *)&v7->pwk[v12]->hwk->pwk->obj.klass + v19);
                *(u64 *)(v23 + 16) = 0;
              }
              v20 = v7->pwk[v12]->hwk->pwk;
              v24 = *(s64 *)((char *)&v20->obj.klass + v19);
              if (*(u64 *)(v24 + 32))
              {
                if (*(u64 *)(v24 + 24))
                {
                  effPartsDelete(*(void *)(v24 + 24));
                  v25 = *(s64 *)((char *)&v7->pwk[v14]->hwk->pwk->obj.klass + v19);
                  *(u64 *)(v25 + 24) = 0;
                  v24 = *(s64 *)((char *)&v7->pwk[v14]->hwk->pwk->obj.klass + v19);
                }
                *(u64 *)(v24 + 32) = 0;
                v20 = v7->pwk[v12]->hwk->pwk;
              }
              *(Il2CppClass **)((char *)&v20->obj.klass + v19) = 0;
              pwk = v7->pwk;
            }
            ++v18;
            v19 += 8;
            v15 = pwk[v12];
            hwk = v15->hwk;
            if (v18 >= hwk->num)
              goto LABEL_31;
            continue;
          }
        }
        if (v7->gstat)
          return v5;
      }
    }
LABEL_5:
    v5 = v3++ > 0x94;
  }
  while (v3 != 150);
  return v5;
}

// 0x20860e0
void sBtlClearEffPacWork(s32 index) {
  s64 v4;
  SBTLEFF_PACLIST *v5;
  SBTLEFF_PACLIST *v6;

  v4 = index;
  v5 = wk2->effpac[v4];
  v5->pData = 0;
  v6 = wk2->effpac[v4];
  *(u32 *)&v6->gstat = 0;
  *(u64 *)&v6->skillID = 0xFFFFFFFFLL;
}

// 0x2076230
s32 sBtlSearchEffectData(SKLID skillid) {
  s64 v4;
  Il2CppClass **v5;

  v4 = 0;
  while (1)
  {
    v5 = &wk2->effpac->obj.klass + v4;
    if (v5[4]->_1.byval_arg.bits == skillid)
      break;
    if (v5[5]->_1.byval_arg.bits == skillid)
      return v4 + 1;
    v4 += 2;
    if (v4 == 150)
    {
      LODWORD(v4) = -1;
      return v4;
    }
  }
  return v4;
}

// 0x2076bf0
s32 sBtlSearchEffectData_Blank(SKLID skillid) {
  s64 v3;
  s32 v4;

  v3 = 4;
  while (1)
  {
    v4 = *(u32 *)(*((u64 *)&wk2->effpac->obj.klass + v3) + 40);
    if (v4 == -1)
      break;
    v4 = *(u32 *)(*((u64 *)&wk2->effpac->obj.klass + v3) + 40);
    if (!v4)
      break;
    if (++v3 == 154)
      return -1;
  }
  return v3 - 4;
}

// 0x2086660
s32 sBtlSearchEffectDataCnt(void) {
  s64 v2;
  s32 v3;
  s32 v4;
  s32 v5;
  s32 v6;
  SBTLEFF_PACLIST *effpac;
  SBTLEFF_PACLIST *v8;
  s32 skillID;
  s32 v10;
  s32 v11;
  s32 v12;
  s32 v13;
  s32 v14;
  s32 v15;
  s32 v16;

  v2 = 0;
  v3 = 0;
  v4 = 0;
  v5 = 0;
  v6 = 0;
  effpac = wk2->effpac;
  do
  {
    v8 = &effpac[v2];
    v2 += 4;
    skillID = v8->skillID;
    v10 = v8[1]->skillID;
    v11 = v8[2]->skillID;
    v12 = v8[3]->skillID;
    if (skillID)
      ++v3;
    if (v10)
      ++v4;
    if (v11)
      ++v5;
    if (v12)
      ++v6;
  }
  while (v2 != 148);
  v13 = v6 + v5 + v4 + v3;
  v14 = effpac[148]->skillID;
  v15 = effpac[149]->skillID;
  if (v14)
    ++v13;
  if (v15)
    return v13 + 1;
  else
    return v13;
  return v16;
}

// 0x207d520
bool sBtlLoadEffectData_IDMask(SKLID id, EFFPAC_ST flg) {
  s64 v7;
  s64 v8;
  s64 v10;
  u32 bits;
  SBTLEFF_PACLIST *v13;
  u32 v15;
  SBTLEFF_PACLIST *v16;
  u16 status;
  SBTLEFF_PACLIST *v18;
  u16 v21;

  if (!id)
    return 1;
  v7 = 0;
  while (1)
  {
    v8 = (s64)wk2->effpac + 8 * v7;
    if (*(u32 *)(*(u64 *)(v8 + 32) + 40) == id)
      goto LABEL_21;
    if (*(u32 *)(*(u64 *)(v8 + 40) + 40) == id)
    {
      LODWORD(v7) = v7 + 1;
      goto LABEL_21;
    }
    v7 += 2;
    if (v7 == 150)
      goto LABEL_22;
  }
  v7 = 0;
  while (1)
  {
    if (wk2->effpac[v7]->skillID == id)
      break;
    if (++v7 == 150)
      goto LABEL_22;
  }
LABEL_21:
  if ((u32)v7 == -1)
  {
LABEL_22:
    v10 = 32;
    while (1)
    {
      bits = (*(Il2CppClass **)((char *)&wk2->effpac->obj.klass + v10))->_1.byval_arg.bits;
      if (bits == -1)
        break;
      bits = (*(Il2CppClass **)((char *)&wk2->effpac->obj.klass + v10))->_1.byval_arg.bits;
      if (!bits)
        break;
      v10 += 8;
      if (v10 == 1232)
        return 0;
    }
    if (v10 == 0x800000018LL)
      return 0;
    v18 = *(SBTLEFF_PACLIST *)((char *)&wk2->effpac->obj.klass + v10);
    if (CheckLoadEffectData(v18, id, flg, 0))
    {
      v16 = *(SBTLEFF_PACLIST *)((char *)&wk2->effpac->obj.klass + v10);
      status = v16->status;
      if ((flg & 8) != 0 && (status & 0x10) == 0)
      {
        v16 = *(SBTLEFF_PACLIST *)((char *)&wk2->effpac->obj.klass + v10);
        goto LABEL_58;
      }
      v16 = *(SBTLEFF_PACLIST *)((char *)&wk2->effpac->obj.klass + v10);
      goto LABEL_68;
    }
    return 0;
  }
  v13 = wk2->effpac[(s32)v7];
  if (!CheckLoadEffectData(v13, id, flg, 0))
    return 0;
  v16 = wk2->effpac[(s32)v7];
  status = v16->status;
  if ((flg & 8) == 0 || (status & 0x10) != 0)
  {
    if (!v15)
    {
      v16 = wk2->effpac[(s32)v7];
LABEL_68:
      status = v16->status;
    }
    v21 = status | flg;
    goto LABEL_70;
  }
  if (!v15)
  {
    v16 = wk2->effpac[(s32)v7];
LABEL_58:
    status = v16->status;
  }
  v21 = status | flg & 0xFFF7;
LABEL_70:
  v16->status = v21;
  return 1;
}

// 0x2078f00
bool sBtlLoadEffectData_ID(SKLID id) {
  s64 v6;
  s64 v7;
  s64 v9;
  u32 bits;
  SBTLEFF_PACLIST *v12;

  v6 = 0;
  while (1)
  {
    v7 = (s64)wk2->effpac + 8 * v6;
    if (*(u32 *)(*(u64 *)(v7 + 32) + 40) == id)
      goto LABEL_20;
    if (*(u32 *)(*(u64 *)(v7 + 40) + 40) == id)
    {
      LODWORD(v6) = v6 + 1;
      goto LABEL_20;
    }
    v6 += 2;
    if (v6 == 150)
      goto LABEL_21;
  }
  v6 = 0;
  while (1)
  {
    if (wk2->effpac[v6]->skillID == id)
      break;
    if (++v6 == 150)
      goto LABEL_21;
  }
LABEL_20:
  if ((u32)v6 != -1)
  {
    v12 = wk2->effpac[(s32)v6];
    return CheckLoadEffectData(v12, id, 0, 0);
  }
LABEL_21:
  v9 = 32;
  while (1)
  {
    bits = (*(Il2CppClass **)((char *)&wk2->effpac->obj.klass + v9))->_1.byval_arg.bits;
    if (bits == -1)
      break;
    bits = (*(Il2CppClass **)((char *)&wk2->effpac->obj.klass + v9))->_1.byval_arg.bits;
    if (!bits)
      break;
    v9 += 8;
    if (v9 == 1232)
      return 0;
  }
  if (v9 == 0x800000018LL)
    return 0;
  v12 = *(SBTLEFF_PACLIST *)((char *)&wk2->effpac->obj.klass + v9);
  return CheckLoadEffectData(v12, id, 0, 0);
}

// 0x207e060
bool sBtlLoadEffectData_Nakama(SBTLUNIT_WORK *wk) {
  SKLID *v4;
  s32 side;
  SBTLEFF_DELLISTWORK *effdelList;
  s32 *v10;
  s64 v11;
  s32 ExeSkill;
  SBTLSKILLP_TBL *Skilltbl;
  s32 v14;
  s32 v16;
  SBTLSKILLP_TBL *v17;
  s32 v18;
  s32 v20;

  v4 = NewSpecific(SKLID, 2u);
  side = wk->side;
  effdelList = wk->effdelList;
  if (sBtlSearchDelWork_Side(effdelList, side))
    return 0;
  v10 = &v4[1];
  v11 = 40;
  while (1)
  {
    ExeSkill = sBtlGetExeSkill(*(u32 *)((char *)&wk->haveskill->obj.klass + v11), &v4[1]);
    v4[0] = ExeSkill;
    if (ExeSkill)
    {
      Skilltbl = sBtlGetSkilltbl(ExeSkill);
      if ((Skilltbl->flg2 & 0x1000) == 0)
      {
        v14 = v4[0];
        if ((Skilltbl->type & 0x2000) == 0 || v14 == 240)
        {
          if ((u16)(sBtlGetSklVisualTbl(v14)->SABno + 1) >= 2u)
          {
            v16 = v4[0];
            if (!sBtlLoadEffectData_IDMask(v16, 8u))
              break;
          }
        }
      }
      if (*v10)
      {
        v17 = sBtlGetSkilltbl(*v10);
        if ((v17->flg2 & 0x1000) == 0)
        {
          v18 = *v10;
          if ((v17->type & 0x2000) == 0 || v18 == 240)
          {
            if ((u16)(sBtlGetSklVisualTbl(v18)->SABno + 1) >= 2u)
            {
              v20 = *v10;
              if (!sBtlLoadEffectData_IDMask(v20, 8u))
                break;
            }
          }
        }
      }
    }
    v11 += 4;
    if (v11 == 104)
      return 1;
  }
  return 0;
}

// 0x207dc50
bool sBtlLoadEffectData(SBTLUNIT_WORK *wk) {
  SKLID *v3;
  u64 v4;
  bool v5;
  s32 v7;
  SBTLSKILLP_TBL *Skilltbl;
  u16 type;
  s32 v10;
  s64 v11;
  s64 v12;
  s32 v13;
  s32 *v14;
  s32 v15;
  s32 v17;
  s64 v19;
  s64 v20;
  s64 v22;
  u32 bits;
  SBTLEFF_PACLIST *v24;
  s32 v26;

  v3 = NewSpecific(SKLID, 2u);
  v4 = 0;
  v5 = 0;
  do
  {
    v7 = wk->haveskill[v4 + 2];
    v3[0] = v7;
    if (v7)
    {
      Skilltbl = sBtlGetSkilltbl(v7);
      if ((Skilltbl->flg2 & 0x1000) == 0)
      {
        type = Skilltbl->type;
        v10 = v3[0];
        if ((type & 0x2000) == 0 || v10 == 240)
        {
          v11 = 0;
          v3[0] = sBtlGetExeSkill(v10, &v3[1]);
          do
          {
            v12 = (s64)(char *)v3 + 4 * v11;
            v15 = *(u32 *)(v12 + 32);
            v14 = (v12 + 32);
            v13 = v15;
            if (!v15)
              break;
            if ((u16)(sBtlGetSklVisualTbl(v13)->SABno + 1) < 2u)
              goto LABEL_14;
            v17 = *v14;
            v19 = 0;
            v20 = &wk2->effpac[4];
            while (*(u32 *)(*(u64 *)(v20 - 32) + 40) != v17)
            {
              if (*(u32 *)(*(u64 *)(v20 - 24) + 40) == v17)
              {
                LODWORD(v19) = v19 + 1;
                if ((u32)v19 == -1)
                  goto LABEL_44;
                goto LABEL_64;
              }
              if (*(u32 *)(*(u64 *)(v20 - 16) + 40) == v17)
              {
                LODWORD(v19) = v19 + 2;
                if ((u32)v19 == -1)
                  goto LABEL_44;
                goto LABEL_64;
              }
              if (*(u32 *)(*(u64 *)(v20 - 8) + 40) == v17)
              {
                LODWORD(v19) = v19 + 3;
                goto LABEL_43;
              }
              if (*(u32 *)(*(u64 *)v20 + 40) == v17)
              {
                LODWORD(v19) = v19 + 4;
                if ((u32)v19 == -1)
                  goto LABEL_44;
                goto LABEL_64;
              }
              v19 += 5;
              v20 += 40;
              if (v19 == 150)
                goto LABEL_44;
            }
LABEL_43:
            if ((u32)v19 != -1)
            {
LABEL_64:
              v24 = wk2->effpac[(s32)v19];
              v26 = *v14;
LABEL_13:
              if (!CheckLoadEffectData(v24, v26, 0, 0))
                return v5;
              goto LABEL_14;
            }
LABEL_44:
            v22 = 32;
            while (1)
            {
              bits = (*(Il2CppClass **)((char *)&wk2->effpac->obj.klass + v22))->_1.byval_arg.bits;
              if (bits == -1)
                break;
              bits = (*(Il2CppClass **)((char *)&wk2->effpac->obj.klass + v22))->_1.byval_arg.bits;
              if (!bits)
                break;
              v22 += 8;
              if (v22 == 1232)
                goto LABEL_14;
            }
            if (v22 != 0x800000018LL)
            {
              v24 = *(SBTLEFF_PACLIST *)((char *)&wk2->effpac->obj.klass + v22);
              v26 = *v14;
              goto LABEL_13;
            }
LABEL_14:
            ++v11;
          }
          while (v11 != 2);
        }
      }
    }
    v5 = v4++ > 0xE;
  }
  while (v4 != 16);
  return v5;
}

// 0x20867a0
bool sBtlSetSummonEffect_Nakama(SBTLUNIT_WORK *wk, s8 flg) {
  s32 v7;
  SBATTLE_WORK *v8;
  SBTLEFF_LISTWORK *effList;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  s32 v14;
  sdfVector4_t v16;

  v7 = flg;
  v8 = wk;
  if ((v8->status4 & 0x200) != 0)
    v7 = 1;
  switch (v7)
  {
    case 2:
      v8 = wk;
      effList = v8->effList;
      x = wk->pos.x;
      y = wk->pos.y;
      z = wk->pos.z;
      w = wk->pos.w;
      v14 = 45;
      goto LABEL_25;
    case 1:
      v8 = wk;
      effList = v8->effList;
      x = wk->pos.x;
      y = wk->pos.y;
      z = wk->pos.z;
      w = wk->pos.w;
      v14 = 44;
      goto LABEL_25;
    case 0:
      v8 = wk;
      effList = v8->effList;
      x = wk->pos.x;
      y = wk->pos.y;
      z = wk->pos.z;
      w = wk->pos.w;
      v14 = 40;
LABEL_25:
      v16.x = x;
      v16.y = y;
      v16.z = z;
      v16.w = w;
      sBtlCreateEff(effList, wk, v14, 0, v16, 0x80808080, 0, 1.0, 0);
      break;
  }
  return 1;
}

// 0x2086950
bool sBtlSetReturnEffect_Nakama(SBTLUNIT_WORK *wk, s8 flg) {
  f32 x;
  f32 y;
  SBTLEFF_LISTWORK *effList;
  f32 z;
  f32 w;
  sdfVector4_t v13;

  if (flg == 2)
  {
    x = wk->pos.x;
    y = wk->pos.y;
    effList = wk->effList;
    z = wk->pos.z;
    w = wk->pos.w;
    v13.x = x;
    v13.y = y;
    v13.z = z;
    v13.w = w;
    sBtlCreateEff(effList, wk, 46, 0, v13, 0x80808080, 0, 1.0, 0);
  }
  return 1;
}

// 0x2086a40
SBTLEFFDMG_TBL *sBtlGetEffDamagetbl(s32 major, s32 minor) {
  struct sBtlEff *p_dmg_tbldata;

  if (major)
  {
    p_dmg_tbldata = &dmg_tbldata;
  }
  else
  {
  }
  return dmg_tbldata_p[minor];
}

// 0x2086ad0
bool sBtlCheckYukaDamageEffect(SBTLUNIT_WORK *wk, SKLID sklid, u16 htype, s32 time, s8 type, const sdfVector4_t *_HitPos, SBTLUNIT_WORK *acter) {
  f32 v8;
  f32 v9;
  f32 x;
  s32 major;
  s64 minor;
  SBTLEFFDMG_TBL *v21;
  u32 flg;
  f32 v23;
  f32 v24;
  f32 PosToDir;
  f32 v26;
  f32 v27;
  f32 w;
  f32 v29;
  s32 side;
  s32 v31;
  char v33;
  s32 v34;
  s64 v37;
  f32 v38;
  SBTLEFF_LISTWORK *effList;
  f32 v44;
  s64 y_eplno;
  SBTLEFF_LISTWORK *v47;
  SBTLUNIT_WORK *v48;
  s32 v49;
  u32 v52;
  s8 v53;
  u32 yr;
  u32 yg;
  u32 yb;
  u32 v57;
  u32 v58;
  u32 v59;
  bool v60;
  s32 v61;
  SBATTLE_WORK *v63;
  s32 devilid;
  SBTLEFF_LISTWORK *v66;
  f32 Z;
  s64 Y;
  sdfVector4_t v70;
  sdfVector4_t pos;

  v8 = HitPos->z;
  v9 = HitPos->y;
  x = HitPos->x;
  Y = 0;
  Z = 0.0;
  if ((sBtlGetSklVisualTbl(sklid)->flg & 0x80) != 0)
    goto LABEL_5;
  switch (htype & 0xFFF)
  {
    case 1:
    case 4:
      goto LABEL_5;
    case 2:
      if (acter && (acter->side & 2) != 0)
        goto LABEL_5;
      break;
    case 3:
      break;
    default:
      if ((htype & 0xFFFu) - 12 < 3)
        goto LABEL_5;
      break;
  }
  if (sklid <= 1296)
  {
    if (sklid != 65 && sklid != 191)
      return 1;
LABEL_5:
    major = wk->major;
    minor = wk->minor;
    if (major)
    {
      v21 = dmg_tbldata[minor];
      flg = v21->flg;
      if ((flg & 1) == 0)
      {
LABEL_11:
        if ((flg & 2) == 0)
          return 1;
        goto LABEL_53;
      }
LABEL_17:
        if (type)
      {
        goto LABEL_20;
      }
      goto LABEL_9001;
      if (type)
      {
LABEL_20:
        if (acter)
        {
LABEL_21:
          v23 = acter->pos.x;
          v24 = acter->pos.z;
          PosToDir = sBtlGetPosToDir(x, v8, v23, v24);
          goto LABEL_42;
        }
LABEL_39:
        v26 = wk->rot.x;
        v27 = wk->rot.y;
        v29 = wk->rot.z;
        w = wk->rot.w;
        v70.x = v26;
        v70.y = v27;
        v70.z = v29;
        v70.w = w;
        PosToDir = sBtlGetRotToDir(v70);
LABEL_42:
        Add(wk->ListID, sklid, x, v9, v8, PosToDir, 1.0, 0);
        if (acter)
        {
          side = acter->side;
          if ((side & 0x80) != 0)
            goto LABEL_49;
          if ((side & 1) == 0)
            goto LABEL_45;
          if (wk->battlemode == 3)
          {
LABEL_49:
            if (acter->actaiwk->targetID == wk->ListID)
              v31 = 3;
            else
              v31 = 2;
          }
          else
          {
            v31 = acter->side & 1;
          }
LABEL_52:
          Add(wk->ListID, x, v9, v8, sklid, v31, 0);
          flg = v21->flg;
          if ((flg & 2) == 0)
            return 1;
LABEL_53:
          if (wk->YukaDamageSkipCnt)
            return 1;
          if ((flg & 8) != 0)
          {
            yr = v21->yr;
            yg = v21->yg;
            yb = v21->yb;
            v57 = ((173019 * yg) >> 9) & 0x3FF00;
            v58 = ((173019 * yr) >> 17) | 0xA0000000;
            v59 = ((173019 * yb) >> 1) & 0x3FF0000;
            if (yb > 0xC1)
              v59 = 16711680;
            v60 = yg > 0xC1;
            v33 = 1;
            if (v60)
              v61 = 65280;
            else
              v61 = v57;
            if (yr > 0xC1)
              v58 = -1610612481;
            v34 = v58 | v61 | v59;
LABEL_56:
            if (sBtlCheckSetsuma_Kaya((f32 *)&Y + 1, &Y, &Z))
            {
LABEL_57:
              v37 = Y;
              v38 = Z;
              effList = wk->effList;
              v44 = 1.0;
              pos.w = 0.0;
              y_eplno = v21->y_eplno;
              v47 = effList;
              v48 = wk;
              v49 = time;
              pos.x = *((f32 *)&v37 + 1);
              LODWORD(pos.y) = v37;
              pos.z = v38;
              v52 = v34;
              v53 = 2;
LABEL_87:
              sBtlCreateEff(v47, v48, efftbl_y[y_eplno], v49, pos, v52, v53, v44, 0);
LABEL_88:
              wk->YukaDamageSkipCnt = 40;
              return 1;
            }
LABEL_73:
            v63 = wk;
            if (v63->battlemode == 1)
            {
              if (type || wk->pos.z < 700.0)
                goto LABEL_88;
              goto LABEL_82;
            }
            devilid = wk->para->devilid;
            if ((u32)(devilid - 261) > 0xFFFFFFFC || (devilid & 0xFFFFFFFC) == 0x138)
              goto LABEL_88;
LABEL_82:
            v63 = wk;
            v66 = v63->effList;
            v44 = 1.0;
            v47 = v66;
            y_eplno = v21->y_eplno;
            v48 = wk;
            v49 = time;
            pos = wk->pos;
            v52 = v34;
            v53 = v33;
            goto LABEL_87;
          }
          else
          {
            v33 = 0;
            v34 = -2139062144;
            goto LABEL_56;
          }
          if (sBtlCheckSetsuma_Kaya((f32 *)&Y + 1, &Y, &Z))
            goto LABEL_57;
          goto LABEL_73;
        }
LABEL_45:
        v31 = 0;
        goto LABEL_52;
      }
LABEL_9001:
      if (acter)
        goto LABEL_21;
      goto LABEL_39;
    }
    v21 = dmg_tbldata_p[minor];
    flg = v21->flg;
    if ((flg & 1) == 0)
      goto LABEL_11;
    goto LABEL_17;
  }
  if (sklid == 1550 || sklid == 1297)
    goto LABEL_5;
  return 1;
}

// 0x20870b0
static u32 colup(u32 col, u32 up_raito) {
  if ((up_raito * col) >> 10 <= 0x18)
    return (u16)(up_raito * col) / 0x64u;
  else
    return 255;
}

// 0x2073130
bool sBtlDeleteEffectData_EffListID(SBTLEFF_LISTWORK *lwk, s32 effListID) {
  SBTLEFF_WORK *wk;

  if (!lwk->num)
    return 0;
  wk = lwk->wk;
  if (!wk)
    return 0;
  while (wk->eListID != effListID)
  {
    wk = wk->next;
    if (!wk)
      return 1;
  }
  wk->pHitEff = 0;
  if ((u32)(wk->st - 1) <= 1)
  {
    wk->flg |= 8u;
    return 1;
  }
  wk->alpha = 0;
  wk->st = 5;
  return 1;
}

// 0x20731e0
void sBtlOutHitEff(SBTL_HITEFF *pHitEff) {
  SBTL_HITEFF *next;
  SBTL_HITEFF *prev;
  SBTL_HITEFF *v5;
  SBTL_HITEFF *v6;
  HITEFFLIST *v9;
  SBTL_HITEFF *v10;
  HITEFFLIST *hitEffList;
  SBTL_HITEFF *v13;
  HITEFFLIST *v14;
  HITEFFLIST *v15;

  prev = pHitEff->prev;
  next = pHitEff->next;
  if (next)
  {
    if (prev)
    {
      prev->next = next;
      v6 = pHitEff->prev;
      v5 = pHitEff->next;
      v5->prev = v6;
    }
    else
    {
      next = pHitEff->next;
      hitEffList = wk->hitEffList;
      hitEffList->pHitEffBgn = next;
      v13 = pHitEff->next;
      v13->prev = 0;
    }
  }
  else
  {
    if (prev)
    {
      prev = pHitEff->prev;
      v9 = wk->hitEffList;
      v9->pHitEffEnd = prev;
      v10 = pHitEff->prev;
      v10->next = 0;
    }
    else
    {
      v14 = wk->hitEffList;
      v14->pHitEffBgn = 0;
      v15 = wk->hitEffList;
      v15->pHitEffEnd = 0;
    }
  }
}

// 0x20870e0
bool sBtlDeleteEffectDataType(SBTLEFF_LISTWORK *lwk, SBTLEFF_BEDTYPE type) {
  SBTLEFF_WORK *wk;

  if (!lwk->num)
    return 0;
  wk = lwk->wk;
  if (!wk)
    return 0;
  do
  {
    if (wk->BEDtype == type)
    {
      if ((u32)(wk->st - 1) > 1)
      {
        wk->st = 5;
        wk->alpha = 0;
      }
      else
      {
        wk->flg |= 8u;
      }
    }
    wk = wk->next;
  }
  while (wk);
  return 1;
}

// 0x2087150
bool sBtlSetColor_SummonEffect(SBTLEFF_LISTWORK *lwk, SBTLUNIT_WORK *unit) {
  SBTLEFF_WORK *wk;
  SBTLEFF_DATAWORK *dwk;

  if (lwk)
  {
    if (lwk->num)
    {
      wk = lwk->wk;
      if (wk)
      {
        do
        {
          if (unit->ListID == wk->acterID && wk->effectid == 40 && (u32)(wk->st - 3) <= 1)
          {
            dwk = wk->dwk;
            wk->abgr = -1;
            effPartsColorSet(dwk->hPartsList, 0);
          }
          wk = wk->next;
        }
        while (wk);
        LOBYTE(lwk) = 1;
      }
      else
      {
        LOBYTE(lwk) = 0;
      }
    }
    else
    {
      LOBYTE(lwk) = 0;
    }
  }
  return (char)lwk;
}
