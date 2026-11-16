#include "types.h"
#include "AUTO.h"
#include "sbtl.h"
#include "sbtlactai.h"
#include "sbtlcalc.h"
#include "sbtldmg.h"
#include "sbtlequat.h"
#include "sbtlmain.h"
#include "sbtlskill.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sbtlvisual.h"
#include "sdf_vu0.h"
#include "sdfquat.h"

typedef struct SBTLAI_EQUATWORK SBTLAI_EQUATWORK;
typedef struct SBTLSKILLP_TBL SBTLSKILLP_TBL;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct TargetCand TargetCand;

struct TargetCand {
    s32 id;
    s32 hp;
    f32 dis;
    u32 attr;
};

struct SBTLAI_EQUATWORK {
    s16 no;
    u8 flg;
    bool boolflg;
    s16 para;
};

static SBTLAI_EQUATWORK *sbtlai_equat_01[2];
static SBTLAI_EQUATWORK *sbtlai_equat_0a;

static bool SetOrderTarget(SBTLUNIT_WORK *wk);
static bool SetNextTarget(SBTLUNIT_WORK *wk);
static bool CheckEnemyTarget(SBTLUNIT_WORK *wk);
static bool CheckAutono(SBTLUNIT_WORK *wk, SBTLSKILLP_TBL *ptbl, AUTO autono);

// 0x1f3fbc0
static bool SetOrderTarget(SBTLUNIT_WORK *wk) {
  sdatUnitWork_t *para;
  SBTLAI_WORK *aiwk;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 order_targetID;
  SBTLUNIT_WORK *v9;
  SBTLUNIT_WORK *v10;
  s32 targetID;
  s32 ListID;
  s32 v14;
  SBTLUNIT_LISTWORK *v16;
  SBTLUNIT_WORK *v17;
  SBTLUNIT_WORK *v18;
  u16 area;

  para = wk->para;
  if (sBtlGetBadStatus(para) - 7 < 2)
    return 0;
  aiwk = wk->aiwk;
  if ((aiwk->status & 1) == 0 && !aiwk->cmndFrm || (wk->side & 1) == 0)
    return 0;
  UnitMng = wk->UnitMng;
  order_targetID = wk->actwk->order_targetID;
  v9 = sBtlSearchUnit_ID(UnitMng, order_targetID);
  v10 = v9;
  if ((wk->side & 0x80) == 0 && wk->aiwk->tgtmode == 1)
  {
    targetID = sBtlGetPChara()->actaiwk->targetID;
    if (targetID != -1)
    {
      sBtlSetTargetID(wk, targetID);
    }
  }
  if (v10)
  {
    if (sBtlCheckDamageTarget(v10))
    {
      ListID = v10->ListID;
      sBtlSetTargetID(wk, ListID);
      return 1;
    }
  }
  v14 = wk->actaiwk->targetID;
  if (v14 == -1)
    return 0;
  v16 = wk->UnitMng;
  v17 = sBtlSearchUnit_ID(v16, v14);
  if (!v17)
    return 0;
  v18 = v17;
  if (!sBtlCheckDamageTarget(v18))
    return 0;
  area = sBtlGetSkilltbl(wk->actwk->use_skillid)->area;
  return (area & 0x4000) != 0 && (v18->side & 1) != 0 || (area & 0x8000) != 0 && (v18->side & 2) != 0;
}

// 0x1f3ff70
static bool SetNextTarget(SBTLUNIT_WORK *wk) {
  u64 *v3;
  SBTLSKILLP_TBL *Skilltbl;
  u16 major;
  s32 minor;
  VISUALDATA_WORK *VisualData;
  SBTLDMG_HITWORK *v8;
  s32 side;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 targetID;
  SBTLUNIT_WORK *v13;
  SBATTLE_WORK *v15;
  SBTLUNIT_LISTWORK *v16;
  s32 playerID;
  s32 v18;
  SBTLUNIT_LISTWORK *v20;
  u32 attr;
  u32 v22;
  u32 v23;
  Il2CppObject *v24;
  s64 v26;
  Il2CppObject *v27;
  s64 v28;
  Il2CppObject *v30;
  s64 v31;
  Il2CppObject *v33;
  s64 v34;
  Il2CppObject *v36;
  s64 v37;
  Il2CppObject *v39;
  s64 v40;
  s64 v42;
  SBTLUNIT_LISTWORK *other_List;
  u32 v45;
  SBTLUNIT_WORK *pUnit;
  u32 v47;
  u32 v48;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  s64 v55;
  f32 v56;
  sdatUnitWork_t *para;
  SBTLACTAI_WORK *v58;
  sdatUnitWork_t *v59;
  s64 v60;
  sdatParaWork_t *now;
  s64 v62;
  s32 hp;
  s64 v64;
  s64 v66;
  s64 v67;
  s32 v68;
  SBTLUNIT_WORK *v69;
  s32 ListID;
  SBTLACTAI_WORK *actaiwk;
  SBTLDMG_HITWORK *v73;
  SBTLSKILLP_TBL *v74;
  SBTLSKILLP_TBL *v76;
  f32 v77;
  f32 v78;
  SBTLDMG_HITLISTWORK *hitList;
  s32 use_skillid;
  f32 w;
  f32 v82;
  s32 v83;
  s32 v84;
  s32 Damage;
  SBTLUNIT_LISTWORK *hitlwk;
  s32 v87;
  struct sdfVector4_t pos;
  f32 *v90;
  f32 v91;
  f32 v92;
  f32 v93;
  char v97;
  u64 *v98;
  SBTLUNIT_WORK *wka;
  SBTLSKILLP_TBL *tbl[2];
  SBTLSKILLP_TBL *tbla[2];
  SBTLSKILLP_TBL *tblc;
  SBTLSKILLP_TBL *tblb[2];
  s32 a_pHanshaType;
  sdfVector4_t v107;

  v3 = NewSpecific(TargetCand, 6u);
  Skilltbl = sBtlGetSkilltbl(wk->actwk->use_skillid);
  major = wk->major;
  minor = wk->minor;
  VisualData = sBtlGetVisualData(major, minor);
  v8 = Allocate(SBTLDMG_HITWORK);
  _ctor(v8, 0);
  side = wk->side;
  a_pHanshaType = 0;
  wka = wk;
  v97 = side;
  if ((side & 1) != 0)
  {
    UnitMng = wk->UnitMng;
    targetID = wk->actaiwk->targetID;
    v13 = sBtlSearchUnit_ID(UnitMng, targetID);
    if ((wk->side & 0x80) == 0 && wk->aiwk->tgtmode == 1)
    {
      v15 = wk;
      v16 = v15->UnitMng;
      playerID = v15->playerID;
      v18 = sBtlSearchUnit_ID(v16, playerID)->actaiwk->targetID;
      if (v18 != -1)
      {
        v20 = wk->UnitMng;
        v13 = sBtlSearchUnit_ID(v20, v18);
        sBtlSetTargetID(wka, v18);
      }
    }
    if (!v13)
      goto LABEL_37;
    if (!sBtlCheckDamageTarget(v13))
      goto LABEL_37;
    if ((wka->side & 0x81) == 0 || (v13->side & 2) == 0)
      goto LABEL_37;
    attr = Skilltbl->attr;
    v22 = sBtlCheckAisyoEx(v13, attr, &a_pHanshaType);
    if (v22 == 4096 || (v23 = v22, v22 == 0x2000))
    {
LABEL_37:
      v24 = Allocate(TargetCand);
      _ctor(v24, 0);
      if (v24 && !QueryInterface(v24, *(void **)(*v3 + 64)))
        goto LABEL_157;
      v3[4] = v24;
      v98 = v3 + 4;
      v26 = v3[4];
      *(u64 *)(v26 + 24) = 0x100047C35000LL;
      *(u64 *)(v26 + 16) = 0x270FFFFFFFFFLL;
      v27 = Allocate(TargetCand);
      _ctor(v27, 0);
      if (v27)
      {
        if (!QueryInterface(v27, *(void **)(*v3 + 64)))
          goto LABEL_157;
      }
      v3[5] = v27;
      v28 = v3[5];
      *(u64 *)(v28 + 16) = 0x270FFFFFFFFFLL;
      *(u64 *)(v28 + 24) = 0x100047C35000LL;
      v30 = Allocate(TargetCand);
      _ctor(v30, 0);
      if (v30)
      {
        if (!QueryInterface(v30, *(void **)(*v3 + 64)))
          goto LABEL_157;
      }
      v3[6] = v30;
      v31 = v3[6];
      *(u64 *)(v31 + 16) = 0x270FFFFFFFFFLL;
      *(u64 *)(v31 + 24) = 0x100047C35000LL;
      v33 = Allocate(TargetCand);
      _ctor(v33, 0);
      if (v33)
      {
        if (!QueryInterface(v33, *(void **)(*v3 + 64)))
          goto LABEL_157;
      }
      v3[7] = v33;
      v34 = v3[7];
      *(u64 *)(v34 + 16) = 0x270FFFFFFFFFLL;
      *(u64 *)(v34 + 24) = 0x100047C35000LL;
      v36 = Allocate(TargetCand);
      _ctor(v36, 0);
      if (v36)
      {
        if (!QueryInterface(v36, *(void **)(*v3 + 64)))
          goto LABEL_157;
      }
      v3[8] = v36;
      v37 = v3[8];
      *(u64 *)(v37 + 16) = 0x270FFFFFFFFFLL;
      *(u64 *)(v37 + 24) = 0x100047C35000LL;
      v39 = Allocate(TargetCand);
      _ctor(v39, 0);
      if (v39)
      {
        if (!QueryInterface(v39, *(void **)(*v3 + 64)))
        {
LABEL_157:
        }
      }
      v3[9] = v39;
      v40 = v3[9];
      *(u64 *)(v40 + 16) = 0x270FFFFFFFFFLL;
      *(u64 *)(v40 + 24) = 0x100047C35000LL;
      *(sdfVector4_t *)tbl = wka->pos;
LABEL_52:
      v42 = 0;
      vct_B = *(sdfVector4_t *)tbl;
      while (1)
      {
        other_List = wk->other_List;
        if (v42 >= other_List->count)
        {
          v68 = *(u32 *)(v3[9] + 16);
          if ((Skilltbl->area & 0x80) != 0)
          {
            v69 = wka;
            if (v68 == -1)
            {
              v68 = *(u32 *)(v3[7] + 16);
              if (v68 == -1)
              {
                v68 = *(u32 *)(v3[5] + 16);
                if (v68 == -1)
                {
                  v68 = *(u32 *)(v3[6] + 16);
                  if (v68 == -1)
                  {
                    v68 = *(u32 *)(*v98 + 16);
                    if (v68 == -1)
                      v68 = *(u32 *)(v3[8] + 16);
                  }
                }
              }
            }
          }
          else
          {
            v69 = wka;
            if (v68 == -1)
            {
              v68 = *(u32 *)(v3[6] + 16);
              if (v68 == -1)
              {
                v68 = *(u32 *)(v3[8] + 16);
                if (v68 == -1)
                  v68 = *(u32 *)(v3[7] + 16);
              }
            }
          }
          other_List = wk->other_List;
          ListID = other_List->pUnitL[v68]->pUnit->ListID;
          sBtlSetTargetID(v69, ListID);
          actaiwk = v69->actaiwk;
          actaiwk->target_frame = sub_1905740(15, 0) + 5;
          return v97 & 1;
        }
        other_List = wk->other_List;
        v45 = Skilltbl->attr;
        pUnit = other_List->pUnitL[v42]->pUnit;
        v47 = sBtlCheckAisyoEx(pUnit, v45, &a_pHanshaType);
        if (!pUnit)
          goto LABEL_53;
        v48 = v47;
        if (!sBtlCheckDamageTarget(pUnit))
          goto LABEL_53;
        *(sdfVector4_t *)tbla = pUnit->pos;
        vct_A = *(sdfVector4_t *)tbla;
        vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
        p_x = &vf00.x;
        x = p_x[4];
        y = p_x[5];
        z = p_x[6];
        v55 = v3[8];
        v56 = sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z));
        if (*(f32 *)(v55 + 24) > v56)
        {
          para = pUnit->para;
          *(u32 *)(v55 + 28) = v48;
          *(f32 *)(v55 + 24) = v56;
          LODWORD(para) = para->now->hp;
          *(u32 *)(v55 + 16) = v42;
          *(u32 *)(v55 + 20) = (u32)para;
        }
        v58 = wka->actaiwk;
        if (v58->bk_targetID != -1)
        {
          v59 = pUnit->para;
          if (v58->bk_devilID == v59->devilid)
          {
            v60 = v3[9];
            if (*(f32 *)(v60 + 24) > v56)
            {
              now = v59->now;
              *(u32 *)(v60 + 28) = v48;
              *(f32 *)(v60 + 24) = v56;
              LODWORD(now) = now->hp;
              *(u32 *)(v60 + 16) = v42;
              *(u32 *)(v60 + 20) = (u32)now;
            }
          }
        }
        if (v48 != 4096 && v48 != 0x2000)
        {
          v62 = *v98;
          hp = pUnit->para->now->hp;
          if (*(u32 *)(*v98 + 20) > hp)
          {
            *(u32 *)(v62 + 16) = v42;
            *(u32 *)(v62 + 20) = hp;
            *(u32 *)(v62 + 28) = v48;
            *(f32 *)(v62 + 24) = v56;
            v64 = v3[5];
            if (*(f32 *)(v64 + 24) <= v56)
              goto LABEL_86;
          }
          else
          {
            v64 = v3[5];
            if (*(f32 *)(v64 + 24) <= v56)
            {
LABEL_86:
              if (v48 != 0x4000)
                goto LABEL_53;
LABEL_99:
              v66 = v3[6];
              if (*(u32 *)(v66 + 20) > hp)
              {
                *(u32 *)(v66 + 16) = v42;
                *(u32 *)(v66 + 20) = hp;
                *(f32 *)(v66 + 24) = v56;
                *(u32 *)(v66 + 28) = 0x4000;
              }
              v67 = v3[7];
              if (*(f32 *)(v67 + 24) > v56)
              {
                *(u32 *)(v67 + 16) = v42;
                *(u32 *)(v67 + 20) = hp;
                *(f32 *)(v67 + 24) = v56;
                *(u32 *)(v67 + 28) = 0x4000;
              }
              goto LABEL_53;
            }
          }
          *(u32 *)(v64 + 16) = v42;
          *(u32 *)(v64 + 20) = hp;
          *(u32 *)(v64 + 28) = v48;
          *(f32 *)(v64 + 24) = v56;
          if (v48 != 0x4000)
            goto LABEL_53;
          goto LABEL_99;
        }
LABEL_53:
        ++v42;
      }
      goto LABEL_52;
    }
    v73 = Allocate(SBTLDMG_HITWORK);
    _ctor(v73, 0);
    v74 = sBtlGetSkilltbl(wka->actwk->use_skillid);
    v76 = v74;
    v74 = v76;
    v77 = v13->pos.x;
    v78 = v13->pos.y;
    hitList = wk->hitList;
    use_skillid = wka->actwk->use_skillid;
    v82 = v13->pos.z;
    w = v13->pos.w;
    tblc = v74;
    v83 = wka->actwk->use_skillid;
    use_skillid = v83;
    v74 = tblc;
    v107.x = v77;
    v107.y = v78;
    v107.z = v82;
    v107.w = w;
    sBtlCreateHitC_None(hitList, wka, wka, v73, use_skillid, v74, v107, -1);
    v84 = wka->actwk->use_skillid;
    Damage = sBtlGetDamage(wka, v13, v73, v84, v23, 1);
    hitlwk = v73->hitlwk;
    v87 = Damage;
    sBtlDeleteUnitList(hitlwk, 0);
    if (v13->para->now->hp >= 3 * v87)
    {
      if ((Skilltbl->area & 0x80) == 0)
        goto LABEL_37;
      *(sdfVector4_t *)tblb = wka->pos;
      vct_A = *(sdfVector4_t *)tblb;
      pos = v13->pos;
      vct_B = pos;
      vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v90 = &vf00.x;
      v91 = v90[6];
      v92 = v90[4];
      v93 = v90[5];
      if (sqrtf((f32)((f32)(v92 * v92) + (f32)(v93 * v93)) + (f32)(v91 * v91)) < (f32)(VisualData->nml->cylinder * 1.8))
        return v97 & 1;
      goto LABEL_37;
    }
  }
  return v97 & 1;
}

// 0x1f40dc0
static bool CheckEnemyTarget(SBTLUNIT_WORK *wk) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 targetID;
  SBTLUNIT_WORK *v6;
  SBTLUNIT_WORK *v7;

  if ((wk->side & 2) == 0)
    return 0;
  UnitMng = wk->UnitMng;
  targetID = wk->actaiwk->targetID;
  v6 = sBtlSearchUnit_ID(UnitMng, targetID);
  if (!v6)
    return 0;
  v7 = v6;
  if (sBtlCheckDamageTarget(v6))
    return 1;
  return 0;
}

// 0x1f40ee0
static bool CheckAutono(SBTLUNIT_WORK *wk, SBTLSKILLP_TBL *ptbl, AUTO autono) {
  if (autono == 15)
  {
    if ((((ptbl->attr & 0xFFF) >> wk->para->autost_cnt) & 1) != 0)
      return 1;
  }
  else if (autono == 14)
  {
    if ((ptbl->type & 0xFFF) == 3)
      return 1;
  }
  else if (autono == 13 && (ptbl->type & 0xFFF) == 1)
  {
    return 1;
  }
  return 0;
}

// 0x1f40f50
bool sBtlCheckArea(SBTLUNIT_WORK *wk, const sdfVector4_t *pos, f32 area) {
  f32 z;
  f32 y;
  f32 x;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  SBTLUNIT_WORK *pUnit;
  s32 side;
  f32 hit_area_r;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  sdfVector4_t vector2;
  f32 w;
  sdfVector4_t v23;

  z = pos->z;
  y = pos->y;
  x = pos->x;
  w = pos->w;
  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    number = UnitMng->number;
    if (i >= number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if (!sBtlCheckDamageTarget(pUnit))
      continue;
    side = pUnit->side;
    if ((side & 7) != 0 && ((wk->side ^ side) & 7) != 0)
    {
      hit_area_r = pUnit->actaiwk->hit_area_r;
      v15 = pUnit->pos.x;
      v16 = pUnit->pos.y;
      v18 = pUnit->pos.z;
      v17 = pUnit->pos.w;
      v23.w = w;
      v23.x = x;
      v23.y = y;
      v23.z = z;
      *(u64 *)&vector2.z = __PAIR64__(LODWORD(v17), LODWORD(v18));
      *(u64 *)&vector2.x = __PAIR64__(LODWORD(v16), LODWORD(v15));
      if (sBtlCheckCrossCircle(v23, area, vector2, hit_area_r))
        return i < number;
    }
  }
  return i < number;
}

// 0x1f41140
bool sBtlCheckArea_SubCylinder(SBTLUNIT_WORK *wk, const sdfVector4_t *pos, f32 area) {
  f32 x;
  s64 v6;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  SBTLUNIT_WORK *pUnit;
  s32 side;
  f32 hit_area_r;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  bool *SubCylinder_Use;
  s64 i;
  f32 RotToDir;
  f32 *SubCylinder_Size;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  sdfVector4_t vector2;
  f32 y;
  f32 w;
  f32 z;
  s64 ToZ;
  sdfVector4_t v35;
  sdfVector4_t v36;

  x = pos->x;
  z = pos->z;
  y = pos->y;
  w = pos->w;
  v6 = 0;
  ToZ = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    number = UnitMng->number;
    if (v6 >= number)
      return v6 < number;
    pUnit = UnitMng->pUnitL[v6]->pUnit;
    if (!pUnit)
      goto LABEL_4;
    if (!v6)
      goto LABEL_19;
    if (!sBtlCheckDamageTarget(pUnit))
      goto LABEL_4;
    side = pUnit->side;
    if ((side & 7) != 0 && ((wk->side ^ side) & 7) != 0)
    {
LABEL_19:
      hit_area_r = pUnit->actaiwk->hit_area_r;
      v13 = pUnit->pos.x;
      v14 = pUnit->pos.y;
      v15 = pUnit->pos.z;
      v16 = pUnit->pos.w;
      v35.y = y;
      v35.w = w;
      v35.x = x;
      v35.z = z;
      *(u64 *)&vector2.z = __PAIR64__(LODWORD(v16), LODWORD(v15));
      *(u64 *)&vector2.x = __PAIR64__(LODWORD(v14), LODWORD(v13));
      if (sBtlCheckCrossCircle(v35, area, vector2, hit_area_r))
        return v6 < number;
      SubCylinder_Use = pUnit->SubCylinder_Use;
      if (SLODWORD(SubCylinder_Use->max_length) >= 1)
      {
        for (i = 0; i < SLODWORD(SubCylinder_Use->max_length); ++i)
        {
          if (SubCylinder_Use[i])
          {
            SubCylinder_Size = pUnit->SubCylinder_Size;
            ToZ = 0;
            v21 = SubCylinder_Size[i];
            v22 = pUnit->rot.x;
            v23 = pUnit->rot.y;
            v24 = pUnit->rot.z;
            v25 = pUnit->rot.w;
            v26 = pUnit->SubCylinder_PosDir[i];
            v27 = pUnit->SubCylinder_PosLen[i];
            v36.x = v22;
            v36.y = v23;
            v36.z = v24;
            v36.w = v25;
            RotToDir = sBtlGetRotToDir(v36);
            sBtlGetMoveXZ(pUnit->pos.x, pUnit->pos.z, v26 + RotToDir, v27, (f32 *)&ToZ + 1, &ToZ);
            if (sBtlGetLenXZ(*((f32 *)&ToZ + 1), *(f32 *)&ToZ, x, z) <= (f32)(v21 + area))
              return v6 < number;
            SubCylinder_Use = pUnit->SubCylinder_Use;
          }
        }
      }
    }
LABEL_4:
    ++v6;
  }
}

// 0x1f41410
s32 sBtlCheckAreaCount(SBTLUNIT_WORK *wk, const sdfVector4_t *pos, f32 area) {
  f32 z;
  f32 y;
  f32 x;
  s64 v8;
  s32 v9;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 side;
  f32 hit_area_r;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  sdfVector4_t vector2;
  f32 w;
  sdfVector4_t v23;

  z = pos->z;
  y = pos->y;
  x = pos->x;
  w = pos->w;
  v8 = 0;
  v9 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v8 >= UnitMng->number)
      return v9;
    pUnit = UnitMng->pUnitL[v8]->pUnit;
    if (!pUnit)
      goto LABEL_5;
    if (!sBtlCheckDamageTarget(pUnit))
      goto LABEL_5;
    side = pUnit->side;
    if ((side & 7) != 0 && ((wk->side ^ side) & 7) != 0)
    {
      hit_area_r = pUnit->actaiwk->hit_area_r;
      v15 = pUnit->pos.x;
      v16 = pUnit->pos.y;
      v18 = pUnit->pos.z;
      v17 = pUnit->pos.w;
      v23.w = w;
      v23.x = x;
      v23.y = y;
      v23.z = z;
      *(u64 *)&vector2.z = __PAIR64__(LODWORD(v17), LODWORD(v18));
      *(u64 *)&vector2.x = __PAIR64__(LODWORD(v16), LODWORD(v15));
      v9 += sBtlCheckCrossCircle(v23, area, vector2, hit_area_r);
    }
LABEL_5:
    ++v8;
  }
}

// 0x1f41610
bool sBtlCheckArea_Atk(SBTLUNIT_WORK *wk, const sdfVector4_t *pos, f32 area) {
  f32 z;
  f32 y;
  f32 x;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  SBTLUNIT_WORK *pUnit;
  s32 side;
  f32 hit_area_r;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  SBTLACTAI_WORK *actaiwk;
  sdfVector4_t vector2;
  f32 w;
  sdfVector4_t v24;

  z = pos->z;
  y = pos->y;
  x = pos->x;
  w = pos->w;
  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    number = UnitMng->number;
    if (i >= number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if (!sBtlCheckDamageTarget(pUnit))
      continue;
    side = pUnit->side;
    if ((side & 7) != 0 && ((wk->side ^ side) & 7) != 0)
    {
      hit_area_r = pUnit->actaiwk->hit_area_r;
      v15 = pUnit->pos.x;
      v16 = pUnit->pos.y;
      v18 = pUnit->pos.z;
      v17 = pUnit->pos.w;
      v24.w = w;
      v24.x = x;
      v24.y = y;
      v24.z = z;
      *(u64 *)&vector2.z = __PAIR64__(LODWORD(v17), LODWORD(v18));
      *(u64 *)&vector2.x = __PAIR64__(LODWORD(v16), LODWORD(v15));
      if (sBtlCheckCrossCircle(v24, area, vector2, hit_area_r))
      {
        actaiwk = pUnit->actaiwk;
        if (actaiwk->mode >= 15 && actaiwk->targetID == wk->ListID)
          return i < number;
      }
    }
  }
  return i < number;
}

// 0x1f41820
s32 sBtlCheckArea_Masic(SBTLUNIT_WORK *wk, const sdfVector4_t *pos, f32 area, s32 flg) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  s64 v13;
  f32 *v14;
  f32 v15;
  s32 v16;
  f32 v17;
  f32 v18;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 side;
  f32 hit_area_r;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  SBTLACTAI_WORK *actaiwk;
  f32 *v32;
  struct sdfVector4_t v35;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 *v45;
  f32 *v46;
  f32 *v47;
  f32 *v48;
  f32 v49;
  f32 v50;
  f32 v51;
  sdfVector4_t vector2;
  f32 v57;
  f32 v58;
  struct sdfVector4_t rot;
  f32 v60;
  int32x4_t v61;
  f32 pos1;
  f32 pos1a;
  f32 v68;
  f32 v69;
  f32 v70;
  f32 v71;
  sdfMatrix4_t v72;
  sdfMatrix4_t v73;
  sdfVector4_t v74;
  sdfVector4_t v75;
  sdfVector4_t v77;
  sdfVector4_t v78;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v13 = 0;
  v14 = &vf00.x;
  pos1 = -1.0;
  v15 = 0.0;
  v16 = -1;
  v17 = 0.0;
  v18 = 0.0;
  v70 = v14[5];
  v71 = v14[4];
  v68 = v14[7];
  v69 = v14[6];
  v61 = vdupq_n_s32(0x44FA0000u);
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v13 >= UnitMng->number)
      return v16;
    pUnit = UnitMng->pUnitL[v13]->pUnit;
    if (!pUnit)
      goto LABEL_15;
    if (!sBtlCheckDamageTarget(pUnit))
      goto LABEL_15;
    side = pUnit->side;
    if ((side & 7) != 0 && ((wk->side ^ side) & 7) != 0)
    {
      hit_area_r = pUnit->actaiwk->hit_area_r;
      v25 = pUnit->pos.x;
      v26 = pUnit->pos.y;
      v27 = pUnit->pos.z;
      v28 = pUnit->pos.w;
      v75.y = v70;
      v75.x = v71;
      v75.w = v68;
      v75.z = v69;
      *(u64 *)&vector2.z = __PAIR64__(LODWORD(v28), LODWORD(v27));
      *(u64 *)&vector2.x = __PAIR64__(LODWORD(v26), LODWORD(v25));
      if (sBtlCheckCrossCircle(v75, area, vector2, hit_area_r))
      {
        actaiwk = pUnit->actaiwk;
        if (actaiwk->mode >= 15 && pUnit->actwk->status == 6 && (!flg || actaiwk->targetID == wk->ListID))
        {
          rot = pUnit->rot;
          vct_A = rot;
          ToMatrix();
          v32 = &vf00.x;
          v32[4] = v15;
          v32[5] = v17;
          v32[6] = pos1;
          v32[7] = v18;
          get_transpose(&v73, &mtx_A, 0);
          v72 = v73;
          vct_A = op_Multiply_60923920(&v72, vct_A, 0);
          sub_1949110(0);
          vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, v61);
          v35 = pUnit->pos;
          goto LABEL_47;
LABEL_48:
          goto LABEL_49;
LABEL_50:
          goto LABEL_51;
LABEL_47:
          vct_B = v35;
          goto LABEL_48;
LABEL_49:
          vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
          goto LABEL_50;
LABEL_51:
          v37 = pUnit->pos.x;
          v38 = pUnit->pos.y;
          v39 = pUnit->pos.z;
          v40 = pUnit->pos.w;
          v78 = vct_A;
          pos1a = vct_A.x;
          v58 = vct_A.z;
          v60 = vct_A.y;
          v57 = vct_A.w;
          v78.w = v57;
          v78.z = v58;
          v78.y = v60;
          v78.x = pos1a;
          v77.x = v37;
          v77.y = v38;
          *(u64 *)&v74.x = 0;
          v77.z = v39;
          v77.w = v40;
          sBtlGetVerticalLength_Point(v77, v78, v74);
          goto LABEL_55;
LABEL_56:
          goto LABEL_57;
LABEL_55:
          v45 = &vf00.x;
          v15 = v45[4];
          v17 = v45[5];
          v18 = v45[7];
          pos1 = v45[6];
          goto LABEL_56;
LABEL_57:
          v46 = &vf00.x;
          v46[4] = v71;
          v46[5] = v70;
          v46[6] = v69;
          v46[7] = v68;
          v47 = &vf00.x;
          v47[8] = v15;
          v47[9] = v17;
          v47[10] = pos1;
          v47[11] = v18;
          vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
          goto LABEL_63;
LABEL_64:
          goto LABEL_9002;
LABEL_63:
          v48 = &vf00.x;
          v49 = v48[4];
          v50 = v48[5];
          v51 = v48[6];
          goto LABEL_64;
LABEL_9002:
          if (sqrtf((f32)((f32)(v49 * v49) + (f32)(v50 * v50)) + (f32)(v51 * v51)) <= (f32)(wk->actaiwk->hit_area_r + wk->actaiwk->hit_area_r))
            return pUnit->ListID;
        }
      }
    }
LABEL_15:
    ++v13;
  }
}
