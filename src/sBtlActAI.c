#include "types.h"
#include "SBTLUNIT_SIDE.h"
#include "SBTL_ACTAIMODE.h"
#include "SKLID.h"
#include "dds3kerneldraw.h"
#include "dds3unitobjectbasic.h"
#include "fld.h"
#include "mdl.h"
#include "sbtl.h"
#include "sbtlactai.h"
#include "sbtlaction.h"
#include "sbtlai.h"
#include "sbtlcalc.h"
#include "sbtlcamera.h"
#include "sbtlcontinue.h"
#include "sbtldmg.h"
#include "sbtldvltk.h"
#include "sbtleff.h"
#include "sbtlencount.h"
#include "sbtlequat.h"
#include "sbtlmain.h"
#include "sbtlpath.h"
#include "sbtlplayer.h"
#include "sbtlplayer_spirit.h"
#include "sbtlplayerfoot.h"
#include "sbtlscene.h"
#include "sbtlskill.h"
#include "sbtlsm.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sbtlvisual.h"
#include "sdf_vu0.h"
#include "sdfquat.h"
#include "smnr.h"

#define EAICODE_SHIFT 16
#define EAICODE_MASK 4294901760
#define EAICODE_ARG 65535
#define SPT_000 0
#define SPT_001 1
#define SPT_002 2
#define SPT_003 3
#define SPT_004 4
#define SPT_005 5
#define SPT_006 6
#define SPT_007 7
#define ACT_000 8
#define ACT_001 9
#define ACT_002 10
#define ACT_003 11
#define ACT_004 12
#define ACT_005 13
#define ACT_006 14
#define ACT_007 15
#define ACT_NON 16

typedef struct AITBLDATA_WORK AITBLDATA_WORK;
typedef struct SBTLACTAI_WORK SBTLACTAI_WORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct sdfBinary sdfBinary;

static AITBLDATA_WORK *ai_tbldata[16];
AITBLDATA_WORK *ai_tbldata2;
CheckFuncTblDelegate *CheckFuncTbl;
sBtlActAI_EAIInit_FuncDelegate *EAIInit_Func;
sBtlActAI_EAIProc_FuncDelegate *EAIProc_Func;
sBtlActAI_AAIInit_FuncDelegate *sBtlActAI_AAIInit_Func;
sBtlActAI_AAIProc_FuncDelegate *sBtlActAI_AAIProc_Func;

static f32 CorrectionMoveDistance(SBTLUNIT_WORK *wk, f32 distance);
static void MapOverHD(SBTLUNIT_WORK *wk, sdfVector4_t *pos);
static bool GetSenkaiPointSub(SBTLUNIT_WORK *wk, const sdfVector4_t *center_pos, SBTLUNIT_WORK *wklock, sdfVector4_t *pos, s32 area);
static void SetUnitHitPush(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, f32 _Yohaku);
static void SetUnitHitPush_Sub(f32 _X1, f32 _Z1, f32 _Size1, f32 _X2, f32 _Z2, f32 _Size2, SBTLUNIT_WORK *wklock, f32 _Yohaku);
static void SetUnitHitApproach(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, f32 _Yohaku);
static void PosOut(SBTLUNIT_WORK *wk);
static void AAIProc_Skl_S_EXE_SKL(SBTLUNIT_WORK *wk, const sdfVector4_t *spd);
static void AAIProc_Skl_SRT_EXE_SKL(SBTLUNIT_WORK *wk, const sdfVector4_t *spd);

// macros
// 0x1db3240: s32 AICHK_NONE(SBTLUNIT_WORK *wk, s32 arg, s32 index)
#define AICHK_NONE(wk, arg, index) (-1)

// 0x1db3250: s32 AICHK_MYHP(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_MYHP(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  SBTLUNIT_WORK *v7;

  v7 = sBtlCheckCharmTarget(wk);
  if (1000 * v7->para->now->hp / v7->para->now->maxhp > 10 * arg)
    return 0;
  wk->actaiwk->ai_target[index] = wk->ListID;
  return 1;
}

// 0x1db3320: s32 AICHK_AREA_E(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_AREA_E(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  s32 side;
  SBTLUNIT_LISTWORK *SideList_AI;
  s64 count;
  SBTLUNIT_LISTWORK *v10;
  s64 v11;
  f32 y;
  f32 z;
  f32 w;
  SBTLUNIT_WORK *pUnit;
  f32 x;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 hit_area_r;
  sdfVector4_t vector2;
  f32 vector1;
  f32 vector1_4;
  sdfVector4_t v26;

  side = wk->side;
  SideList_AI = sBtlCreateSideList_AI(side, 1);
  LODWORD(count) = SideList_AI->count;
  v10 = SideList_AI;
  if ((s32)count < 1)
  {
    LODWORD(v11) = 0;
LABEL_13:
  }
  else
  {
    v11 = 0;
    vector1_4 = arg;
    while (1)
    {
      v26.x = wk->pos.x;
      y = wk->pos.y;
      z = wk->pos.z;
      w = wk->pos.w;
      pUnit = v10->pUnitL[v11]->pUnit;
      x = pUnit->pos.x;
      v17 = pUnit->pos.y;
      v19 = pUnit->pos.z;
      v18 = pUnit->pos.w;
      hit_area_r = pUnit->actaiwk->hit_area_r;
      vector1 = wk->pos.x;
      v26.x = vector1;
      v26.y = y;
      v26.z = z;
      v26.w = w;
      *(u64 *)&vector2.z = __PAIR64__(LODWORD(v18), LODWORD(v19));
      *(u64 *)&vector2.x = __PAIR64__(LODWORD(v17), LODWORD(x));
      if (sBtlCheckCrossCircle(v26, vector1_4, vector2, hit_area_r))
        break;
      count = v10->count;
      if (++v11 >= count)
        goto LABEL_13;
    }
    wk->actaiwk->ai_target[index] = pUnit->ListID;
    LODWORD(count) = v10->count;
  }
  sBtlDeleteUnitList(v10, 0);
  return (s32)v11 < (s32)count;
}

// 0x1db34e0: s32 AICHK_MYHPU(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_MYHPU(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  SBTLUNIT_WORK *v7;

  v7 = sBtlCheckCharmTarget(wk);
  if (1000 * v7->para->now->hp / v7->para->now->maxhp < 10 * arg)
    return 0;
  wk->actaiwk->ai_target[index] = wk->ListID;
  return 1;
}

// 0x1db35b0: s32 AICHK_P_AREANUM_A(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_P_AREANUM_A(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  SBATTLE_WORK *v8;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v11;
  SBTLUNIT_LISTWORK *SideList;
  s64 v13;
  s32 v14;
  f32 y;
  f32 z;
  f32 w;
  SBTLUNIT_WORK *pUnit;
  f32 x;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 hit_area_r;
  sdfVector4_t vector2;
  f32 vector1;
  sdfVector4_t v27;

  v8 = wk;
  UnitMng = v8->UnitMng;
  playerID = v8->playerID;
  v11 = sBtlSearchUnit_ID(UnitMng, playerID);
  SideList = sBtlCreateSideList(v11->side, 1);
  if (SideList->count < 1)
  {
    v14 = 0;
  }
  else
  {
    v13 = 0;
    v14 = 0;
    do
    {
      v27.x = v11->pos.x;
      y = v11->pos.y;
      z = v11->pos.z;
      w = v11->pos.w;
      pUnit = SideList->pUnitL[v13]->pUnit;
      x = pUnit->pos.x;
      v20 = pUnit->pos.y;
      v21 = pUnit->pos.z;
      v22 = pUnit->pos.w;
      hit_area_r = pUnit->actaiwk->hit_area_r;
      vector1 = v11->pos.x;
      v27.x = vector1;
      v27.y = y;
      v27.z = z;
      v27.w = w;
      *(u64 *)&vector2.z = __PAIR64__(LODWORD(v22), LODWORD(v21));
      *(u64 *)&vector2.x = __PAIR64__(LODWORD(v20), LODWORD(x));
      if (sBtlCheckCrossCircle(v27, 250.0, vector2, hit_area_r) && pUnit->aiwk->mode)
      {
        ++v14;
        wk->actaiwk->ai_target[index] = pUnit->ListID;
      }
      ++v13;
    }
    while (v13 < SideList->count);
  }
  sBtlDeleteUnitList(SideList, 0);
  return v14 >= arg;
}

// 0x1db37d0: s32 AICHK_HP(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_HP(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  s32 side;
  sdatUnitWork_t *para;
  u32 BadStatus;
  s32 v12;
  s32 v13;
  SBTLUNIT_LISTWORK *SideList;
  s64 count;
  SBTLUNIT_LISTWORK *v16;
  s64 i;
  SBTLUNIT_WORK *pUnit;
  sdatParaWork_t *now;
  s32 hp;

  side = wk->side;
  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  if ((side & 2) != 0)
    v12 = 1;
  else
    v12 = 2;
  if (BadStatus == 7)
    v13 = v12;
  else
    v13 = side;
  SideList = sBtlCreateSideList(v13, 0);
  count = (u32)SideList->count;
  v16 = SideList;
  if ((s32)count >= 1)
  {
    for (i = 0; i != count; ++i)
    {
      pUnit = SideList->pUnitL[i]->pUnit;
      now = pUnit->para->now;
      hp = now->hp;
      if (hp >= 1 && 1000 * hp / now->maxhp <= 10 * arg)
      {
        wk->actaiwk->ai_target[index] = pUnit->ListID;
        LODWORD(count) = SideList->count;
        goto LABEL_28;
      }
    }
    LODWORD(i) = SideList->count;
    goto LABEL_28;
  }
  LODWORD(i) = 0;
LABEL_28:
  sBtlDeleteUnitList(v16, 0);
  return (s32)i < (s32)count;
}

// 0x1db39f0: s32 AICHK_MYHP_LESS(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_MYHP_LESS(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  SBTLUNIT_WORK *v7;

  v7 = sBtlCheckCharmTarget(wk);
  if (100 * v7->para->now->hp >= v7->para->now->maxhp * arg)
    return 0;
  wk->actaiwk->ai_target[index] = wk->ListID;
  return 1;
}

// 0x1db3ac0: s32 AICHK_AREA_EU(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_AREA_EU(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  s32 side;
  SBTLUNIT_LISTWORK *SideList_AI;
  s64 count;
  SBTLUNIT_LISTWORK *v10;
  s64 v11;
  f32 y;
  f32 z;
  f32 w;
  SBTLUNIT_WORK *pUnit;
  f32 x;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 hit_area_r;
  sdfVector4_t vector2;
  f32 vector1;
  f32 vector1_4;
  sdfVector4_t v26;

  side = wk->side;
  SideList_AI = sBtlCreateSideList_AI(side, 1);
  LODWORD(count) = SideList_AI->count;
  v10 = SideList_AI;
  if ((s32)count < 1)
  {
    LODWORD(v11) = 0;
LABEL_13:
  }
  else
  {
    v11 = 0;
    vector1_4 = arg;
    while (1)
    {
      v26.x = wk->pos.x;
      y = wk->pos.y;
      z = wk->pos.z;
      w = wk->pos.w;
      pUnit = v10->pUnitL[v11]->pUnit;
      x = pUnit->pos.x;
      v17 = pUnit->pos.y;
      v19 = pUnit->pos.z;
      v18 = pUnit->pos.w;
      hit_area_r = pUnit->actaiwk->hit_area_r;
      vector1 = wk->pos.x;
      v26.x = vector1;
      v26.y = y;
      v26.z = z;
      v26.w = w;
      *(u64 *)&vector2.z = __PAIR64__(LODWORD(v18), LODWORD(v19));
      *(u64 *)&vector2.x = __PAIR64__(LODWORD(v17), LODWORD(x));
      if (!sBtlCheckCrossCircle(v26, vector1_4, vector2, hit_area_r))
        break;
      count = v10->count;
      if (++v11 >= count)
        goto LABEL_13;
    }
    wk->actaiwk->ai_target[index] = pUnit->ListID;
    LODWORD(count) = v10->count;
  }
  sBtlDeleteUnitList(v10, 0);
  return (s32)v11 < (s32)count;
}

// 0x1db3c80: s32 AICHK_BADST(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_BADST(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  s32 side;
  sdatUnitWork_t *para;
  u32 BadStatus;
  s32 v12;
  s32 v13;
  SBTLUNIT_LISTWORK *SideList;
  s64 count;
  SBTLUNIT_LISTWORK *v16;
  s64 v17;
  SBTLUNIT_WORK *pUnit;

  side = wk->side;
  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  if ((side & 2) != 0)
    v12 = 1;
  else
    v12 = 2;
  if (BadStatus == 7)
    v13 = v12;
  else
    v13 = side;
  SideList = sBtlCreateSideList(v13, 0);
  count = (u32)SideList->count;
  v16 = SideList;
  if ((s32)count >= 1)
  {
    v17 = 0;
    while (1)
    {
      pUnit = SideList->pUnitL[v17]->pUnit;
      if ((pUnit->para->badstatus & arg) != 0)
        break;
      if (count == ++v17)
      {
        LODWORD(v17) = SideList->count;
        goto LABEL_27;
      }
    }
    wk->actaiwk->ai_target[index] = pUnit->ListID;
    LODWORD(count) = SideList->count;
    goto LABEL_27;
  }
  LODWORD(v17) = 0;
LABEL_27:
  sBtlDeleteUnitList(v16, 0);
  return (s32)v17 < (s32)count;
}

// 0x1db3e80: s32 AICHK_BTLTIME(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_BTLTIME(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  SBTLACTAI_WORK *actaiwk;
  s32 ListID;

  if (wk->aiwk->syscnt_stop < arg)
    return 0;
  actaiwk = wk->actaiwk;
  ListID = wk->ListID;
  actaiwk->ai_target[index] = ListID;
  return 1;
}

// 0x1db3ec0: s32 AICHK_CHKSKL(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_CHKSKL(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  s32 v6;
  u32 v7;
  u32 v9;

  v6 = arg & 0xF000;
  if ((arg & 0xF000) != 0)
  {
    if (v6 == 0x4000)
    {
      v7 = 0;
      while (1)
      {
        if ((sBtlGetSkilltbl(v7)->flg & arg) != 0)
        {
          if (((wk->actaiwk->chkskl[v7 >> 5] >> v7) & 1) != 0)
            break;
        }
        if (++v7 == 1600)
          return 0;
      }
    }
    else
    {
      if (v6 != 0x8000)
        return 0;
      v9 = 0;
      while (1)
      {
        if ((sBtlGetSkilltbl(v9)->attr & arg) != 0)
        {
          if (((wk->actaiwk->chkskl[v9 >> 5] >> v9) & 1) != 0)
            break;
        }
        if (++v9 == 1600)
          return 0;
      }
    }
    return 1;
  }
  else
  {
    return (wk->actaiwk->chkskl[((u32)arg >> 5) & 0x7F] >> arg) & 1;
  }
}

// 0x1db4080: s32 AICHK_CHKSKL_R(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_CHKSKL_R(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  s32 v6;
  u32 v7;
  SBTLACTAI_WORK *p_actaiwk;
  s64 v9;
  s32 v10;
  u32 *chkskl;
  u32 v13;

  v6 = arg & 0xF000;
  if ((arg & 0xF000) != 0)
  {
    if (v6 == 0x4000)
    {
      v7 = 0;
      p_actaiwk = &wk->actaiwk;
      while (1)
      {
        if ((sBtlGetSkilltbl(v7)->flg & arg) != 0)
        {
          v9 = v7 >> 5;
          v10 = 1 << v7;
          chkskl = p_actaiwk->chkskl;
          if ((chkskl[(u32)v9] & (1 << v7)) != 0)
            break;
        }
        if (++v7 == 1600)
          return 0;
      }
      goto LABEL_24;
    }
    if (v6 == 0x8000)
    {
      v13 = 0;
      p_actaiwk = &wk->actaiwk;
      while (1)
      {
        if ((sBtlGetSkilltbl(v13)->attr & arg) != 0)
        {
          v9 = v13 >> 5;
          v10 = 1 << v13;
          chkskl = p_actaiwk->chkskl;
          if ((chkskl[(u32)v9] & (1 << v13)) != 0)
            break;
        }
        if (++v13 == 1600)
          return 0;
      }
LABEL_24:
      goto LABEL_26;
    }
    return 0;
  }
  v9 = ((u32)arg >> 5) & 0x7F;
  v10 = 1 << arg;
  chkskl = wk->actaiwk->chkskl;
  if ((chkskl[(u32)v9] & (1 << arg)) == 0)
    return 0;
  p_actaiwk = &wk->actaiwk;
  chkskl = p_actaiwk->chkskl;
LABEL_26:
  chkskl[v9] &= ~v10;
  return 1;
}

// 0x1db42c0: s32 AICHK_USESKL(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_USESKL(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  s32 v6;
  u32 v7;
  u32 v9;

  v6 = arg & 0xF000;
  if ((arg & 0xF000) != 0)
  {
    if (v6 == 0x4000)
    {
      v7 = 0;
      while (1)
      {
        if ((sBtlGetSkilltbl(v7)->flg & arg) != 0)
        {
          if (((wk->actaiwk->useskl[v7 >> 5] >> v7) & 1) != 0)
            break;
        }
        if (++v7 == 1600)
          return 0;
      }
    }
    else
    {
      if (v6 != 0x8000)
        return 0;
      v9 = 0;
      while (1)
      {
        if ((sBtlGetSkilltbl(v9)->attr & arg) != 0)
        {
          if (((wk->actaiwk->useskl[v9 >> 5] >> v9) & 1) != 0)
            break;
        }
        if (++v9 == 1600)
          return 0;
      }
    }
    return 1;
  }
  else
  {
    return (wk->actaiwk->useskl[((u32)arg >> 5) & 0x7F] >> arg) & 1;
  }
}

// 0x1db4480: s32 AICHK_USESKL_R(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_USESKL_R(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  s32 v6;
  u32 v7;
  SBTLACTAI_WORK *p_actaiwk;
  s64 v9;
  s32 v10;
  u32 *useskl;
  u32 v13;

  v6 = arg & 0xF000;
  if ((arg & 0xF000) != 0)
  {
    if (v6 == 0x4000)
    {
      v7 = 0;
      p_actaiwk = &wk->actaiwk;
      while (1)
      {
        if ((sBtlGetSkilltbl(v7)->flg & arg) != 0)
        {
          v9 = v7 >> 5;
          v10 = 1 << v7;
          useskl = p_actaiwk->useskl;
          if ((useskl[(u32)v9] & (1 << v7)) != 0)
            break;
        }
        if (++v7 == 1600)
          return 0;
      }
      goto LABEL_24;
    }
    if (v6 == 0x8000)
    {
      v13 = 0;
      p_actaiwk = &wk->actaiwk;
      while (1)
      {
        if ((sBtlGetSkilltbl(v13)->attr & arg) != 0)
        {
          v9 = v13 >> 5;
          v10 = 1 << v13;
          useskl = p_actaiwk->useskl;
          if ((useskl[(u32)v9] & (1 << v13)) != 0)
            break;
        }
        if (++v13 == 1600)
          return 0;
      }
LABEL_24:
      goto LABEL_26;
    }
    return 0;
  }
  v9 = ((u32)arg >> 5) & 0x7F;
  v10 = 1 << arg;
  useskl = wk->actaiwk->useskl;
  if ((useskl[(u32)v9] & (1 << arg)) == 0)
    return 0;
  p_actaiwk = &wk->actaiwk;
  useskl = p_actaiwk->useskl;
LABEL_26:
  useskl[v9] &= ~v10;
  return 1;
}

// 0x1db46c0: s32 AICHK_USESKLG(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_USESKLG(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  s64 i;
  s32 result;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 v11;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if (!CheckLiveTarget(pUnit))
      continue;
    if ((pUnit->side & wk->side & 0x3F) != 0 && pUnit->GroupID == wk->GroupID)
    {
      result = AICHK_USESKL(pUnit, arg, v11);
      if (result == 1)
        return result;
    }
  }
  return 0;
}

// 0x1db4860: s32 AICHK_USESKLG_R(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_USESKLG_R(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  s64 i;
  s32 result;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 v11;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if (!CheckLiveTarget(pUnit))
      continue;
    if ((pUnit->side & wk->side & 0x3F) != 0 && pUnit->GroupID == wk->GroupID)
    {
      result = AICHK_USESKL_R(pUnit, arg, v11);
      if (result == 1)
        return result;
    }
  }
  return 0;
}

// 0x1db4a00: s32 AICHK_MOON(SBTLUNIT_WORK *wk, s32 arg, s32 index)
#define AICHK_MOON(wk, arg, index) (sBtlCheckMoon(arg))

// 0x1db4a70: s32 AICHK_BADST_E(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_BADST_E(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  s32 side;
  sdatUnitWork_t *para;
  u32 BadStatus;
  char v12;
  u8 v13;
  SBTLUNIT_LISTWORK *SideList_AI;
  s64 count;
  SBTLUNIT_LISTWORK *v16;
  s64 v17;
  SBTLUNIT_WORK *pUnit;

  side = wk->side;
  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  if ((side & 2) != 0)
    v12 = 1;
  else
    v12 = 2;
  if (BadStatus == 7)
    v13 = v12;
  else
    v13 = side;
  SideList_AI = sBtlCreateSideList_AI(v13, 1);
  count = (u32)SideList_AI->count;
  v16 = SideList_AI;
  if ((s32)count >= 1)
  {
    v17 = 0;
    while (1)
    {
      pUnit = SideList_AI->pUnitL[v17]->pUnit;
      if ((pUnit->para->badstatus & arg) != 0)
        break;
      if (count == ++v17)
      {
        LODWORD(v17) = SideList_AI->count;
        goto LABEL_27;
      }
    }
    wk->actaiwk->ai_target[index] = pUnit->ListID;
    LODWORD(count) = SideList_AI->count;
    goto LABEL_27;
  }
  LODWORD(v17) = 0;
LABEL_27:
  sBtlDeleteUnitList(v16, 0);
  return (s32)v17 < (s32)count;
}

// 0x1db4c70: s32 AICHK_KAJYA(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_KAJYA(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  s32 side;
  sdatUnitWork_t *para;
  u32 BadStatus;
  char v12;
  u8 v13;
  SBTLUNIT_LISTWORK *SideList;
  SBTLUNIT_WORK *pUnit;
  SBTLUNIT_LISTWORK *v16;
  s64 v17;
  SBTLUNIT_LISTWK *pUnitL;
  s32 pCount;

  pCount = 0;
  side = wk->side;
  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  if ((side & 2) != 0)
    v12 = 1;
  else
    v12 = 2;
  if (BadStatus == 7)
    v13 = v12;
  else
    v13 = side;
  SideList = sBtlCreateSideList(v13, 0);
  LODWORD(pUnit) = SideList->count;
  v16 = SideList;
  if ((s32)pUnit < 1)
  {
    LODWORD(v17) = 0;
LABEL_29:
  }
  else
  {
    v17 = 0;
    while (1)
    {
      pUnitL = v16->pUnitL;
      pCount = 0;
      pUnit = pUnitL[v17]->pUnit;
      if (sBtlCheckKajaAnyEx(pUnit, &pCount) && pCount >= arg)
        break;
      pUnit = v16->count;
      if (++v17 >= (s64)pUnit)
        goto LABEL_29;
    }
    wk->actaiwk->ai_target[index] = pUnit->ListID;
    LODWORD(pUnit) = v16->count;
  }
  sBtlDeleteUnitList(v16, 0);
  return (s32)v17 < (s32)pUnit;
}

// 0x1db4e90: s32 AICHK_KAJYA_E(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_KAJYA_E(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  s32 side;
  sdatUnitWork_t *para;
  u32 BadStatus;
  s32 v12;
  s32 v13;
  SBTLUNIT_LISTWORK *SideList_AI;
  SBTLUNIT_WORK *pUnit;
  SBTLUNIT_LISTWORK *v16;
  s64 v17;
  SBTLUNIT_LISTWK *pUnitL;
  s32 pCount;

  pCount = 0;
  side = wk->side;
  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  if ((side & 2) != 0)
    v12 = 1;
  else
    v12 = 2;
  if (BadStatus == 7)
    v13 = v12;
  else
    v13 = side;
  SideList_AI = sBtlCreateSideList_AI(v13, 1);
  LODWORD(pUnit) = SideList_AI->count;
  v16 = SideList_AI;
  if ((s32)pUnit < 1)
  {
    LODWORD(v17) = 0;
LABEL_29:
  }
  else
  {
    v17 = 0;
    while (1)
    {
      pUnitL = v16->pUnitL;
      pCount = 0;
      pUnit = pUnitL[v17]->pUnit;
      if (sBtlCheckKajaAnyEx(pUnit, &pCount) && pCount >= arg)
        break;
      pUnit = v16->count;
      if (++v17 >= (s64)pUnit)
        goto LABEL_29;
    }
    wk->actaiwk->ai_target[index] = pUnit->ListID;
    LODWORD(pUnit) = v16->count;
  }
  sBtlDeleteUnitList(v16, 0);
  return (s32)v17 < (s32)pUnit;
}

// 0x1db50b0: s32 AICHK_NKAJYA(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_NKAJYA(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  s32 side;
  sdatUnitWork_t *para;
  u32 BadStatus;
  s32 v12;
  s32 v13;
  SBTLUNIT_LISTWORK *SideList;
  SBTLUNIT_WORK *pUnit;
  SBTLUNIT_LISTWORK *v16;
  s64 v17;

  side = wk->side;
  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  if ((side & 2) != 0)
    v12 = 1;
  else
    v12 = 2;
  if (BadStatus == 7)
    v13 = v12;
  else
    v13 = side;
  SideList = sBtlCreateSideList(v13, 0);
  LODWORD(pUnit) = SideList->count;
  v16 = SideList;
  if ((s32)pUnit < 1)
  {
    LODWORD(v17) = 0;
LABEL_25:
  }
  else
  {
    v17 = 0;
    while (1)
    {
      pUnit = v16->pUnitL[v17]->pUnit;
      if (sBtlCheckEnableUseKaja(pUnit, arg) >= 1)
        break;
      pUnit = v16->count;
      if (++v17 >= (s64)pUnit)
        goto LABEL_25;
    }
    wk->actaiwk->ai_target[index] = pUnit->ListID;
    LODWORD(pUnit) = v16->count;
  }
  sBtlDeleteUnitList(v16, 0);
  return (s32)v17 < (s32)pUnit;
}

// 0x1db52c0: s32 AICHK_OTAKE(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_OTAKE(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  s32 side;
  sdatUnitWork_t *para;
  u32 BadStatus;
  s32 v11;
  s32 v12;
  SBTLUNIT_LISTWORK *SideList;
  s64 count;
  SBTLUNIT_LISTWORK *v15;
  s64 v16;
  SBTLUNIT_WORK *pUnit;
  tagSBTLSKL_AURA_WORK *wkAura;

  side = wk->side;
  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  if ((side & 2) != 0)
    v11 = 1;
  else
    v11 = 2;
  if (BadStatus == 7)
    v12 = v11;
  else
    v12 = side;
  SideList = sBtlCreateSideList(v12, 0);
  count = (u32)SideList->count;
  v15 = SideList;
  if ((s32)count < 1)
  {
    LODWORD(v16) = 0;
    goto LABEL_27;
  }
  else
  {
    v16 = 0;
    while (1)
    {
      pUnit = SideList->pUnitL[v16]->pUnit;
      wkAura = pUnit->wkAura;
      if (wkAura[0]->auracnt || wkAura[1]->auracnt || wkAura[2]->auracnt)
      {
        break;
      }
      if (count == ++v16)
      {
        LODWORD(v16) = SideList->count;
        goto LABEL_27;
      }
    }
    wk->actaiwk->ai_target[index] = pUnit->ListID;
    LODWORD(count) = SideList->count;
    goto LABEL_27;
  }
LABEL_27:
  sBtlDeleteUnitList(v15, 0);
  return (s32)v16 < (s32)count;
}

// 0x1db54d0: s32 AICHK_OTAKE_E(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_OTAKE_E(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  s32 side;
  sdatUnitWork_t *para;
  u32 BadStatus;
  s32 v11;
  s32 v12;
  SBTLUNIT_LISTWORK *SideList_AI;
  s64 count;
  SBTLUNIT_LISTWORK *v15;
  s64 v16;
  SBTLUNIT_WORK *pUnit;
  tagSBTLSKL_AURA_WORK *wkAura;

  side = wk->side;
  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  if ((side & 2) != 0)
    v11 = 1;
  else
    v11 = 2;
  if (BadStatus == 7)
    v12 = v11;
  else
    v12 = side;
  SideList_AI = sBtlCreateSideList_AI(v12, 1);
  count = (u32)SideList_AI->count;
  v15 = SideList_AI;
  if ((s32)count < 1)
  {
    LODWORD(v16) = 0;
    goto LABEL_27;
  }
  else
  {
    v16 = 0;
    while (1)
    {
      pUnit = SideList_AI->pUnitL[v16]->pUnit;
      wkAura = pUnit->wkAura;
      if (wkAura[0]->auracnt || wkAura[1]->auracnt || wkAura[2]->auracnt)
      {
        break;
      }
      if (count == ++v16)
      {
        LODWORD(v16) = SideList_AI->count;
        goto LABEL_27;
      }
    }
    wk->actaiwk->ai_target[index] = pUnit->ListID;
    LODWORD(count) = SideList_AI->count;
    goto LABEL_27;
  }
LABEL_27:
  sBtlDeleteUnitList(v15, 0);
  return (s32)v16 < (s32)count;
}

// 0x1db56e0: s32 AICHK_NOTAKE(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_NOTAKE(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  s32 side;
  sdatUnitWork_t *para;
  u32 BadStatus;
  s32 v11;
  s32 v12;
  SBTLUNIT_LISTWORK *SideList;
  s64 count;
  SBTLUNIT_LISTWORK *v15;
  s64 i;
  SBTLUNIT_WORK *pUnit;
  tagSBTLSKL_AURA_WORK *wkAura;

  side = wk->side;
  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  if ((side & 2) != 0)
    v11 = 1;
  else
    v11 = 2;
  if (BadStatus == 7)
    v12 = v11;
  else
    v12 = side;
  SideList = sBtlCreateSideList(v12, 0);
  count = (u32)SideList->count;
  v15 = SideList;
  if ((s32)count < 1)
  {
    LODWORD(i) = 0;
    goto LABEL_23;
  }
  else
  {
    for (i = 0; i != count; ++i)
    {
      pUnit = SideList->pUnitL[i]->pUnit;
      wkAura = pUnit->wkAura;
      if (!wkAura[0]->auracnt && !wkAura[1]->auracnt && !wkAura[2]->auracnt)
      {
        wk->actaiwk->ai_target[index] = pUnit->ListID;
        LODWORD(count) = SideList->count;
        goto LABEL_23;
      }
    }
    LODWORD(i) = SideList->count;
    goto LABEL_23;
  }
LABEL_23:
  sBtlDeleteUnitList(v15, 0);
  return (s32)i < (s32)count;
}

// 0x1db58f0: s32 AICHK_MESHI(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_MESHI(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  if (!sBtlCheckGenerator_D())
    return 0;
  if (wk->enemy_num < 6)
    return 1;
  return 0;
}

// 0x1db5af0: s32 AICHK_HANGEKI(SBTLUNIT_WORK *wk, s32 arg, s32 index)
#define AICHK_HANGEKI(wk, arg, index) (wk->hangeki_on != 0)

// 0x1db5b00: s32 AICHK_RAIDOENMY(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_RAIDOENMY(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  SBATTLE_WORK *v6;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v9;
  SBTLUNIT_LISTWORK *SideList;
  s64 v11;
  s32 v12;
  f32 y;
  f32 z;
  f32 w;
  SBTLUNIT_WORK *pUnit;
  f32 x;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 hit_area_r;
  s32 targetID;
  u32 status;
  sdfVector4_t vector2;
  f32 vector1;
  sdfVector4_t v28;

  v6 = wk;
  UnitMng = v6->UnitMng;
  playerID = v6->playerID;
  v9 = sBtlSearchUnit_ID(UnitMng, playerID);
  SideList = sBtlCreateSideList(v9->side, 1);
  if (SideList->count >= 1)
  {
    v11 = 0;
    v12 = 0;
    while (1)
    {
      v28.x = v9->pos.x;
      y = v9->pos.y;
      z = v9->pos.z;
      w = v9->pos.w;
      pUnit = SideList->pUnitL[v11]->pUnit;
      x = pUnit->pos.x;
      v18 = pUnit->pos.y;
      v19 = pUnit->pos.z;
      v20 = pUnit->pos.w;
      hit_area_r = pUnit->actaiwk->hit_area_r;
      vector1 = v9->pos.x;
      v28.x = vector1;
      v28.y = y;
      v28.z = z;
      v28.w = w;
      *(u64 *)&vector2.z = __PAIR64__(LODWORD(v20), LODWORD(v19));
      *(u64 *)&vector2.x = __PAIR64__(LODWORD(v18), LODWORD(x));
      if (!sBtlCheckCrossCircle(v28, 250.0, vector2, hit_area_r) || !pUnit->aiwk->mode)
      {
        goto LABEL_9;
      }
      targetID = pUnit->actaiwk->targetID;
      if (targetID == wk->playerID)
      {
        status = pUnit->actwk->status;
        if (status <= 0x37 && ((1 << status) & 0xA0000080000048LL) != 0)
        {
          ++v12;
          wk->actaiwk->ai_target[index] = pUnit->ListID;
        }
      }
LABEL_9:
      if (++v11 >= SideList->count)
        goto LABEL_22;
    }
  }
  v12 = 0;
LABEL_22:
  sBtlDeleteUnitList(SideList, 0);
  return v12 > 0;
}

// 0x1db5d90: s32 AICHK_HPP(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_HPP(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  s32 side;
  sdatUnitWork_t *para;
  u32 BadStatus;
  s32 v12;
  s32 v13;
  SBTLUNIT_LISTWORK *SideList;
  s64 count;
  SBTLUNIT_LISTWORK *v16;
  s64 v17;
  SBTLUNIT_WORK *pUnit;
  sdatParaWork_t *now;
  s32 hp;
  s32 v21;
  bool v22;
  bool v23;
  s32 kaifuku_skl_cnt;
  u32 Rand;
  s32 v26;

  side = wk->side;
  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  if ((side & 2) != 0)
    v12 = 1;
  else
    v12 = 2;
  if (BadStatus == 7)
    v13 = v12;
  else
    v13 = side;
  SideList = sBtlCreateSideList(v13, 0);
  count = (u32)SideList->count;
  v16 = SideList;
  if ((s32)count < 1)
    goto LABEL_35;
  v17 = 0;
  while (1)
  {
    pUnit = SideList->pUnitL[v17]->pUnit;
    now = pUnit->para->now;
    hp = now->hp;
    v21 = 1000 * hp / now->maxhp;
    v22 = v21 > 10 * arg || v21 < 151;
    v23 = v22;
    if (hp > 99 || !v23)
      break;
    if (count == ++v17)
      goto LABEL_35;
  }
  wk->actaiwk->ai_target[index] = pUnit->ListID;
  if ((s32)v17 < SideList->count)
  {
    kaifuku_skl_cnt = wk->kaifuku_skl_cnt;
    if (kaifuku_skl_cnt >= 3)
    {
      v26 = GetRand(0x64u) < 0x14u;
      goto LABEL_37;
    }
    Rand = GetRand(0x64u);
    if (kaifuku_skl_cnt < 1)
    {
      v26 = Rand < 0x5A;
      goto LABEL_37;
    }
    v26 = Rand < 0x28;
  }
  else
  {
LABEL_35:
    v26 = 0;
  }
LABEL_37:
  sBtlDeleteUnitList(v16, 0);
  return v26;
}

// 0x1db6020: s32 AICHK_TETORAKANE(SBTLUNIT_WORK *wk, s32 arg, s32 index)
#define AICHK_TETORAKANE(wk, arg, index) (wk->wkKarn[0]->m_cnt > 0)

// 0x1db6040: s32 AICHK_CNT(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_CNT(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  SBTLACTAI_WORK *actaiwk;
  s32 ListID;

  if (wk->aiwk->hcnt < arg)
    return 0;
  actaiwk = wk->actaiwk;
  ListID = wk->ListID;
  actaiwk->ai_target[index] = ListID;
  return 1;
}

// 0x1db6080: s32 AICHK_YARARE(SBTLUNIT_WORK *wk, s32 arg, s32 index)
#define AICHK_YARARE(wk, arg, index) ((wk->exflg & 1) == arg)

// 0x1db60a0: s32 AICHK_MYLOCKON(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_MYLOCKON(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  s32 v6;
  SBTLUNIT_WORK *PlayerUnit;
  SBTLUNIT_WORK *v9;

  v6 = sBtlGetPlayerID();
  PlayerUnit = sBtlGetPlayerUnit(v6);
  if (!PlayerUnit)
    return 0;
  v9 = PlayerUnit;
  if (wk->CameraGazeOff)
    return 0;
  return v9->actaiwk->targetID == wk->ListID;
}

// 0x1db61b0: s32 AICHK_SPIRIT(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_SPIRIT(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  s32 vice;

  vice = wk->para->vice;
  return sBtlGetViceLevel(vice) >= arg;
}

// 0x1db6230: s32 AICHK_RAIDOHP(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_RAIDOHP(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  SBTLUNIT_WORK *PChara;

  PChara = sBtlGetPChara();
  return 100 * PChara->para->now->hp <= PChara->para->now->maxhp * arg;
}

// 0x1db6280: s32 AICHK_WEAKATK(SBTLUNIT_WORK *wk, s32 arg, s32 index)
#define AICHK_WEAKATK(wk, arg, index) ((wk->hstatus & 0x200000) != 0 && wk->WeakAtkCnt <= arg)

// 0x1db62b0: s32 AICHK_WEAKOFF(SBTLUNIT_WORK *wk, s32 arg, s32 index)
#define AICHK_WEAKOFF(wk, arg, index) (wk->WeakReceiveFlg && wk->WeakReceiveCnt <= arg)

// 0x1db62e0: s32 AICHK_RITU(SBTLUNIT_WORK *wk, s32 arg, s32 index)
#define AICHK_RITU(wk, arg, index) ((s32)sub_1905740(100, 0) < arg)

// 0x1db6310: s32 AICHK_RAIDOAREA_E(SBTLUNIT_WORK *wk, s32 arg, s32 index)
static inline s32 AICHK_RAIDOAREA_E(SBTLUNIT_WORK *wk, s32 arg, s32 index) {
  s32 side;
  SBTLUNIT_LISTWORK *SideList_AI;
  s64 count;
  SBTLUNIT_LISTWORK *v10;
  s64 v11;
  f32 y;
  f32 z;
  f32 w;
  SBTLUNIT_WORK *pUnit;
  f32 x;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 hit_area_r;
  sdfVector4_t vector2;
  f32 vector1;
  f32 vector1_4;
  sdfVector4_t v26;

  side = wk->side;
  SideList_AI = sBtlCreateSideList_AI(side, 2);
  LODWORD(count) = SideList_AI->count;
  v10 = SideList_AI;
  if ((s32)count < 1)
  {
    LODWORD(v11) = 0;
LABEL_13:
  }
  else
  {
    v11 = 0;
    vector1_4 = arg;
    while (1)
    {
      v26.x = wk->pos.x;
      y = wk->pos.y;
      z = wk->pos.z;
      w = wk->pos.w;
      pUnit = v10->pUnitL[v11]->pUnit;
      x = pUnit->pos.x;
      v17 = pUnit->pos.y;
      v19 = pUnit->pos.z;
      v18 = pUnit->pos.w;
      hit_area_r = pUnit->actaiwk->hit_area_r;
      vector1 = wk->pos.x;
      v26.x = vector1;
      v26.y = y;
      v26.z = z;
      v26.w = w;
      *(u64 *)&vector2.z = __PAIR64__(LODWORD(v18), LODWORD(v19));
      *(u64 *)&vector2.x = __PAIR64__(LODWORD(v17), LODWORD(x));
      if (sBtlCheckCrossCircle(v26, vector1_4, vector2, hit_area_r))
        break;
      count = v10->count;
      if (++v11 >= count)
        goto LABEL_13;
    }
    wk->actaiwk->ai_target[index] = pUnit->ListID;
    LODWORD(count) = v10->count;
  }
  sBtlDeleteUnitList(v10, 0);
  return (s32)v11 < (s32)count;
}

// 0x1da5ac0
void sBtlInitAIdata(sdfBinary *head_bin, s32 dlc_no) {
  s64 v5;
  AITBLDATA_WORK **ai_tbldata_local;
  Il2CppClass *v8;
  Il2CppClass *v9;
  Il2CppClass **v10;
  s64 v11;
  u64 v12;
  AITBLDATA_WORK *v14;
  AITBLDATA_WORK *v15;
  u64 v16;
  Il2CppClass **v17;
  AITBLDATA_WORK *v18;
  s64 v19;
  const char *v20;
  AICHK_WORK *act;
  AICHK_WORK *v23;
  const char *name;
  const char *v27;
  const char *v29;
  const char *namespaze;
  const char *v33;
  const char *v35;
  const char *v37;
  const char *v39;
  const char *v41;
  const char *v43;
  s64 i;
  s64 j;
  AIACT_TBL *acttbl;
  AIACT_TBL *v48;
  Il2CppClass **v49;
  AIACT_TBL *v50;
  s64 v51;
  s32 S32;
  AIACT_TBL *v54;
  s64 v55;
  s32 v56;
  AIACT_TBL *v58;
  s64 v59;
  s64 k;
  s32 *pat_tbl;
  s64 m;
  s32 *v65;
  s32 v66;
  il2cpp_array_size_t v67;
  s64 n;
  s32 *v70;
  s64 ii;
  s32 *v73;
  s64 jj;
  s32 *v76;
  s64 kk;
  s32 *v79;
  s64 mm;
  s32 *v82;
  s64 nn;
  s32 *v85;
  AITBLDATA_WORK **v87;
  u32 length[2];

  if (dlc_no)
    v5 = 32;
  else
    v5 = 544;
  *(u64 *)length = v5;
  if (dlc_no)
  {
    goto LABEL_8;
  }
  v87 = NewSpecific(Project_AITBLDATA_WORK__, 0x10u);
  ai_tbldata = v87;
LABEL_8:
  ai_tbldata_local = ai_tbldata;
  v8 = NewSpecific(AITBLDATA_WORK, length[0]);
  v9 = v8;
  v10 = &ai_tbldata_local->obj.klass + dlc_no;
  v11 = dlc_no;
  v10[4] = v9;
  v12 = 0;
  do
  {
    v14 = ai_tbldata[v11];
    v15 = Allocate(AITBLDATA_WORK);
    _ctor(v15, 0);
    v16 = v12;
    v17 = &v14->obj.klass + v12;
    v17[4] = v15;
    v18 = ai_tbldata[v11][v12];
    v19 = 32;
    v18->scr_no = ReadS32(head_bin, 0);
    do
    {
      act = ai_tbldata[v11][v12]->act;
      v23 = Allocate(AICHK_WORK);
      _ctor(v23, 0);
      *(Il2CppClass **)((char *)&act->obj.klass + v19) = v23;
      name = (*(Il2CppClass **)((char *)&ai_tbldata[v11][v12]->act->obj.klass + v19))->_1.name;
      *((u32 *)name + 8) = ReadU32(head_bin, 0);
      v27 = (*(Il2CppClass **)((char *)&ai_tbldata[v11][v12]->act->obj.klass + v19))->_1.name;
      *((u32 *)v27 + 9) = ReadU32(head_bin, 0);
      v29 = (*(Il2CppClass **)((char *)&ai_tbldata[v11][v12]->act->obj.klass + v19))->_1.name;
      *((u32 *)v29 + 10) = ReadU32(head_bin, 0);
      namespaze = (*(Il2CppClass **)((char *)&ai_tbldata[v11][v12]->act->obj.klass + v19))->_1.namespaze;
      *((u8 *)namespaze + 32) = ReadS8(head_bin, 0);
      v33 = (*(Il2CppClass **)((char *)&ai_tbldata[v11][v12]->act->obj.klass + v19))->_1.namespaze;
      *((u8 *)v33 + 33) = ReadS8(head_bin, 0);
      v35 = (*(Il2CppClass **)((char *)&ai_tbldata[v11][v12]->act->obj.klass + v19))->_1.namespaze;
      *((u8 *)v35 + 34) = ReadS8(head_bin, 0);
      v37 = (*(Il2CppClass **)((char *)&ai_tbldata[v11][v12]->act->obj.klass + v19))->_1.namespaze;
      *((u8 *)v37 + 35) = ReadS8(head_bin, 0);
      v39 = (*(Il2CppClass **)((char *)&ai_tbldata[v11][v12]->act->obj.klass + v19))->_1.namespaze;
      *((u8 *)v39 + 36) = ReadS8(head_bin, 0);
      v41 = (*(Il2CppClass **)((char *)&ai_tbldata[v11][v12]->act->obj.klass + v19))->_1.namespaze;
      *((u8 *)v41 + 37) = ReadS8(head_bin, 0);
      v43 = (*(Il2CppClass **)((char *)&ai_tbldata[v11][v12]->act->obj.klass + v19))->_1.namespaze;
      *((u8 *)v43 + 38) = ReadS8(head_bin, 0);
      v20 = (*(Il2CppClass **)((char *)&ai_tbldata[v11][v12]->act->obj.klass + v19))->_1.namespaze;
      v19 += 8;
      *((u8 *)v20 + 39) = ReadS8(head_bin, 0);
    }
    while (v19 != 48);
    for (i = 0; i != 8; ++i)
    {
      for (j = 0; j != 4; ++j)
      {
        acttbl = ai_tbldata[v11][v16]->acttbl;
        v48 = Allocate(AIACT_TBL);
        _ctor(v48, 0);
        v49 = &acttbl->obj.klass + j + i * acttbl->bounds[1].length;
        v49[4] = v48;
        v50 = ai_tbldata[v11][v16]->acttbl;
        v51 = *((u64 *)&v50[j] + i * v50->bounds[1].length);
        S32 = ReadS32(head_bin, 0);
        *(u32 *)(v51 + 16) = S32;
        v54 = ai_tbldata[v11][v16]->acttbl;
        v55 = *((u64 *)&v54[j] + i * v54->bounds[1].length);
        v56 = ReadS32(head_bin, 0);
        *(u32 *)(v55 + 20) = v56;
        v58 = ai_tbldata[v11][v16]->acttbl;
        v59 = *((u64 *)&v58[j] + i * v58->bounds[1].length);
        *(u32 *)(v59 + 24) = ReadS32(head_bin, 0);
      }
    }
    for (k = 32; k != 120; k += 4)
    {
      pat_tbl = ai_tbldata[v11][v12]->pat_tbl;
      *(u32 *)((char *)&pat_tbl->obj.klass + k) = ReadS32(head_bin, 0);
    }
    for (m = 0; m != 22; ++m)
    {
      v65 = ai_tbldata[v11][v12]->pat_tbl;
      v66 = ReadS32(head_bin, 0);
      v67 = m + v65->bounds[1].length;
      v65[v67] = v66;
    }
    for (n = 32; n != 120; n += 4)
    {
      v70 = ai_tbldata[v11][v12]->pat_tbl;
      *(u32 *)((char *)&v70->obj.klass + 8 * v70->bounds[1].length + n) = ReadS32(head_bin, 0);
    }
    for (ii = 32; ii != 120; ii += 4)
    {
      v73 = ai_tbldata[v11][v12]->pat_tbl;
      *(u32 *)((char *)&v73->obj.klass + 12 * v73->bounds[1].length + ii) = ReadS32(head_bin, 0);
    }
    for (jj = 32; jj != 120; jj += 4)
    {
      v76 = ai_tbldata[v11][v12]->pat_tbl;
      *(u32 *)((char *)&v76->obj.klass + 16 * v76->bounds[1].length + jj) = ReadS32(head_bin, 0);
    }
    for (kk = 32; kk != 120; kk += 4)
    {
      v79 = ai_tbldata[v11][v12]->pat_tbl;
      *(u32 *)((char *)&v79->obj.klass + 20 * v79->bounds[1].length + kk) = ReadS32(head_bin, 0);
    }
    for (mm = 32; mm != 120; mm += 4)
    {
      v82 = ai_tbldata[v11][v12]->pat_tbl;
      *(u32 *)((char *)&v82->obj.klass + 24 * v82->bounds[1].length + mm) = ReadS32(head_bin, 0);
    }
    for (nn = 32; nn != 120; nn += 4)
    {
      v85 = ai_tbldata[v11][v12]->pat_tbl;
      *(u32 *)((char *)&v85->obj.klass + 28 * v85->bounds[1].length + nn) = ReadS32(head_bin, 0);
    }
    ++v12;
  }
  while (v12 != *(u64 *)length);
}

// 0x1da6580
void sBtlInitAIdataDLC(s32 dlc_no) {
  char *v4;
  char *v5;
  char *v6;
  char *v7;
  void *Asset;
  sdfBinary *v10;
  s32 v12;
  s32 dlc_noa;

  dlc_noa = dlc_no;
  if (!fldCheckDlcData(dlc_no))
    return;
  v4 = ToString((s32)&dlc_noa, 0);
  v5 = Concat_54766928("battle_dlc", v4, 0);
  v6 = ToString((s32)&dlc_noa, 0);
  v7 = Concat_54831728("sb_devilai_DLC", v6, "_R1.TBL", 0);
  Asset = LoadAsset(_Ctrl_k__BackingField, v5, v7, 0);
  v10 = Allocate(sdfBinary);
  _ctor(v10, Asset, 0);
  v12 = dlc_noa;
  sBtlInitAIdata(v10, v12);
}

// 0x1da6790
bool sBtlGotoAtkPos(SBTLUNIT_WORK *wk, bool bRinchi) {
  MOTIONDATA_WORK *v5;
  SBTLUNIT_WORK *PChara;
  SBTLACTAI_WORK *actaiwk;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v9;
  SBTLUNIT_WORK *v11;
  SBTLUNIT_WORK *v12;
  s32 use_skillid;
  s32 motionno;
  s32 side;
  s32 v16;
  u16 major;
  s32 minor;
  MOTIONDATA_WORK *MotionVisualData;
  SBTLACTAI_WORK *v20;
  SBTLSKILLP_TBL *v22;
  SBTLAI_WORK *v24;
  u32 v25;
  SBTLPNL_SETDATA *data;
  s32 LockID;
  SBTLUNIT_WORK *v29;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 targetID;
  SBTLUNIT_WORK *v34;
  s64 v35;
  f32 v40;
  f32 v41;
  f32 v42;
  f32 v43;
  f32 v44;
  f32 v45;
  SBTLACTAI_WORK *v47;
  s32 v48;
  sdfVector4_t *v51;
  SBTLACTAI_WORK *v52;
  SBTLACTAI_WORK *v54;
  struct sdfVector4_t v56;
  f32 *v57;
  f32 v58;
  f32 v59;
  f32 v60;
  s32 target_frame;
  bool v63;
  s32 v64;
  f32 v68;
  f32 v69;
  f32 v70;
  f32 v71;
  f32 v72;
  long f64 v73;
  f32 v74;
  s32 motionID;
  SBTLUNIT_WORK *v79;
  s32 v80;
  sdfVector4_t *p_pos;
  s32 devilid;
  f32 *p_x;
  char v85;
  s32 v86;
  s32 v87;
  SBTLAI_WORK *v88;
  f32 v92;
  f32 v93;
  f32 v94;
  f32 v95;
  f32 v96;
  f32 Radian;
  f32 v99;
  f32 v101;
  f32 v102;
  f32 v103;
  f32 v104;
  s32 v105;
  f32 v106;
  f32 v107;
  f32 v108;
  long f64 v109;
  s32 v110;
  f32 v111;
  f32 v112;
  f32 v113;
  f32 v114;
  f32 v115;
  s64 v116;
  sdfVector4_t v119;
  f32 *v120;
  f32 v121;
  f32 v122;
  f32 v123;
  s32 ListID;
  s32 v126;
  f32 y;
  f32 z;
  f32 v130;
  f32 *v132;
  struct sdfVector4_t v134;
  f32 *v136;
  s64 v138;
  f32 v139;
  s64 v140;
  float32x2_t *v142;
  f32 v143;
  float32x4_t v147;
  f32 v149;
  f32 v150;
  f32 v152;
  f32 v153;
  f32 *v154;
  f32 v156;
  float32x4_t v157;
  struct sdfVector4_t v158;
  f32 v159;
  f32 v161;
  f32 *v162;
  __n128 v163;
  s32 v164;
  f32 v165;
  f32 v166;
  long f64 v167;
  long f64 v168;
  long f64 v169;
  long f64 v170;
  long f64 v171;
  s32 nakamaAtkPos;
  struct sdfVector4_t v174;
  struct sdfVector4_t v177;
  f32 v178;
  f32 v179;
  f32 x;
  f32 v185;
  f32 v186;
  f32 v187;
  f32 v188;
  f32 v189;
  f32 v190;
  f32 v191;
  f32 v192;
  f32 v193;
  f32 v194;
  f32 v195;
  f32 LenXZ;
  f32 v197;
  f32 v198;
  f32 v199;
  f32 w;
  long f64 v201;
  f32 v202;
  f32 v203;
  f32 v204;
  f32 v205;
  SBTLUNIT_WORK *v206;
  f32 v208;
  f32 v209;
  f32 v210;
  f32 v211;
  long f64 v212;
  sdfVector4_t v213;
  f32 v214;
  f32 v215;
  f32 v216;
  f32 v217;
  f32 v218;
  f32 v219;
  f32 v220;
  f32 v221;
  f32 v222;
  f32 v223;
  f32 v224;
  f32 v225;
  f32 v226;
  f32 v227;
  f32 v228;
  f32 v229;
  f32 v230;
  long f64 v231;
  f32 v232;
  f32 v233;
  f32 v234;
  f32 v235;
  f32 v236;
  f32 v237;
  f32 v238;
  f32 v239;
  long f64 v240;
  f32 v241;
  f32 v242;
  f32 v243;
  f32 v244;
  f32 v246;
  f32 v247;
  f32 v248;
  f32 v250;
  f32 v251;
  f32 v252;
  f32 v253;
  long f64 v257;
  f32 v258;
  SBTLACTAI_WORK *v259;
  f32 v260;
  f32 v261;
  f32 v262;
  f32 v263;
  long f64 v264;
  SBTLACTAI_WORK *v266;
  f64 v267;
  sdfVector4_t *p_ppos;
  sdfVector4_t v269;
  SBTLACTAI_WORK *v270;
  f32 r2;
  f32 m_mv_area_r;
  s32 v273;
  u32 z_low;
  SBTLAI_WORK *aiwk;
  f32 v276;
  f32 v277;
  f32 v278;
  f32 v279;
  f32 v280;
  f32 v281;
  f32 v283;
  f32 v284;
  f32 v285;
  f32 v286;
  f32 v287;
  f32 v289;
  long f64 v290;
  f32 v291;
  f32 v292;
  f32 v293;
  f32 v294;
  f32 v295;
  long f64 v296;
  f32 v298;
  f32 v299;
  f32 v300;
  f32 v301;
  f32 v302;
  f32 v303;
  f32 v306;
  long f64 v307;
  f32 v308;
  SBTLACTAI_WORK *v310;
  s32 v311;
  sdfVector4_t *p_mv_spdbk;
  SBTLACTAI_WORK *v315;
  SBTLAI_WORK *v318;
  u32 status;
  sdfVector4_t *p_mv_spd;
  f32 v325;
  f32 v326;
  f32 v327;
  f32 v328;
  f32 v329;
  f32 v330;
  f32 v331;
  f32 v332;
  f32 v333;
  f32 v335;
  s32 v336;
  f32 v337;
  f32 v338;
  f32 v339;
  f32 v340;
  f32 v341;
  f32 v342;
  f32 v343;
  long f64 v344;
  f32 v345;
  long f64 v346;
  f32 v347;
  f32 v348;
  f32 v349;
  f32 v350;
  f32 v351;
  f32 v352;
  f32 v353;
  f32 v354;
  long f64 v355;
  f32 v356;
  f32 v357;
  s32 v358;
  s32 v359;
  SBTLACTAI_WORK *v360;
  f32 v361;
  f32 v362;
  f32 v363;
  f32 v364;
  long f64 v365;
  SBTLACTAI_WORK *v366;
  sdfVector4_t per;
  f32 v369;
  f32 v370;
  f32 v371;
  f32 v372;
  f32 v373;
  f32 v377;
  f32 v378;
  struct sdfVector4_t v379;
  f32 v380;
  sdfVector4_t pos;
  f32 v382;
  f32 v387;
  f32 v388;
  f32 v389;
  f32 v390;
  f32 v391;
  MOTIONDATA_WORK *t1;
  f32 t1b;
  f32 t1c;
  f32 t1d;
  f32 t1e;
  f32 t1a;
  SBTLUNIT_WORK *t1_8;
  f32 t1_8b;
  f32 t1_8c;
  f32 t1_8a;
  f32 t1_8d;
  SBTLSKILLP_TBL *rot;
  f32 rotc;
  f32 rotd;
  struct sdfVector4_t rota;
  f32 rotb;
  sdfVector4_t FromZ;
  struct sdfVector4_t v409;
  struct sdfVector4_t v410;
  struct sdfVector4_t vct_A_local;
  sdfVector4_t v412;
  sdfVector4_t v413;
  sdfVector4_t v414;
  sdfVector4_t v415;
  sdfVector4_t v416;
  sdfVector4_t v417;
  sdfVector4_t v418;
  sdfVector4_t v419;
  sdfVector4_t v420;
  sdfVector4_t v421;
  sdfVector4_t v422;
  sdfVector4_t v423;
  sdfVector4_t v424;
  sdfVector4_t v425;
  sdfVector4_t v426;
  sdfVector4_t v427;
  sdfVector4_t v428;
  sdfVector4_t v429;
  sdfVector4_t v430;
  sdfVector4_t v431;
  sdfVector4_t v432;
  sdfVector4_t v433;

  vct_A_local = (struct sdfVector4_t)0;
  v409 = (struct sdfVector4_t)0;
  v410 = (struct sdfVector4_t)0;
  FromZ = (sdfVector4_t)0;
  v5 = Allocate(MOTIONDATA_WORK);
  _ctor(v5, 0);
  PChara = sBtlGetPChara();
  actaiwk = wk->actaiwk;
    if (actaiwk->mode > 11)
  {
    goto LABEL_14;
  }
LABEL_14:
  Nakama = sBtlGetNakama(0);
  v9 = sBtlGetNakama(1);
  v11 = v9;
  if (Nakama == wk || (v12 = 0, v9 == wk))
  {
    v12 = sBtlGetNakama(Nakama == wk);
    use_skillid = wk->actwk->use_skillid;
    if (use_skillid)
    {
LABEL_17:
      t1_8 = PChara;
      rot = sBtlGetSkilltbl(use_skillid);
      motionno = sBtlGetSklVisualTbl(wk->actwk->use_skillid)->motionno;
      side = wk->side;
      v16 = sBtlGetMotionNo(wk, side, motionno);
      major = wk->major;
      minor = wk->minor;
      MotionVisualData = sBtlGetMotionVisualData(major, minor, v16);
      v20 = wk->actaiwk;
      if ((v20->status & 0x180) == 0x100)
      {
        v22 = rot;
        if (v20->mode > 11)
          goto LABEL_46;
LABEL_41:
        LockID = v20->LockID;
        if (wk->battlemode == 3 || (wk->side & 0x80) == 0)
        {
LABEL_47:
          t1 = MotionVisualData;
          v29 = sBtlSearchUnit_ID(wk->UnitMng, LockID);
            if ((v22->type & 0x1000) == 0)
          {
            goto LABEL_52;
          }
          goto LABEL_9020;
          if ((v22->type & 0x1000) == 0)
          {
LABEL_52:
            if (IsSceanStop())
            {
              wk->mv_spd.z = 0.0;
              return 1;
            }
            if (!v29)
            {
              if (LockID == -1)
              {
                v85 = 0;
                if ((v22->flg & 0x224) != 0)
                  goto LABEL_468;
LABEL_434:
                if ((wk->side & 1) != 0)
                {
                  aiwk = wk->aiwk;
                  if (aiwk->atkCnt)
                  {
                    if (wk->actwk->use_skillid == aiwk->dfltOdrSkl && wk->actaiwk->targetID != -1)
                    {
                      if (wk->motionID)
                      {
                        sBtlSetMotion(wk, 0, 4, 0, 0);
                      }
                      *(u64 *)&wk->mv_spd.x = 0;
                      wk->mv_spd.z = 0.0;
                      return 1;
                    }
                  }
                }
LABEL_468:
                if (sBtlCheckCost(wk, 0))
                {
                  v310 = wk->actaiwk;
                  v310->mode = 16;
                  v310->frame = 0;
                  v311 = wk->actwk->use_skillid;
                  sBtlSetUseSkill(wk, v311, 0);
                  *(u64 *)&vct_A.x = 0;
                  *(u64 *)&vct_A.z = 0;
                  p_mv_spdbk = &wk->mv_spdbk;
                  v315 = wk->actaiwk;
                  *p_mv_spdbk = vct_A;
                  v315->status &= ~0x200u;
                  if (Nakama == wk)
                  {
                    wk->nakamaAtkPos0 = v85;
                  }
                  else if (v11 == wk)
                  {
                    wk->nakamaAtkPos1 = v85;
                  }
                  return 1;
                }
                sBtlSetNoMP(wk);
                sBtlResetAAI(wk);
                v318 = wk->aiwk;
                status = v318->status;
                if ((status & 1) != 0)
                {
                  v318->meirei_nobk = 7;
                  v318->status = status & 0xFFFFFFF6;
LABEL_35:
                  data = wk->panelwk->data;
                  data[sBtlGetSmnNo(wk)]->meirei_no = 7;
                  wk->aiwk->status &= ~0x10u;
                  wk->NakamaAtkFormationUse = 0;
                  return 1;
                }
                return 1;
              }
              ResetAction(wk, 0, 0);
              sBtlResetAAI(wk);
              goto LABEL_121;
            }
            v54 = wk->actaiwk;
            v54->bk_targetID = v54->targetID;
            v54->bk_devilID = v29->para->devilid;
            if ((v29->side & 2) == 0)
            {
LABEL_123:
              *(u64 *)&v54->target_frame = 0;
              if ((wk->side & 1) != 0 && (v22->area & 0x80) != 0 && bRinchi)
              {
                if (t1_8->actaiwk->targetID == LockID)
                  goto LABEL_131;
                if (v12)
                {
                  if (sBtlGetLockID(v12, *(const MethodInfo **)&v412.z) == LockID)
                  {
LABEL_131:
                    p_pos = &t1_8->pos;
                    pos = t1_8->pos;
                    vct_A = pos;
                    devilid = (u16)v29->para->devilid;
                    if (devilid == 314 || devilid == 258)
                      p_x = &t1_8->pos.x;
                    else
                      p_x = &v29->pos.x;
                    y = wk->pos.y;
                    z = v29->pos.z;
                    v130 = *p_x;
                    v132 = &vf00.x;
                    v132[8] = v130;
                    v132[9] = y;
                    v132[10] = z;
                    v132[11] = 0.0;
                    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
                    v134 = *p_pos;
                    vct_B = v134;
                    v136 = &vf00.x;
                    v136[4] = v130;
                    v136[5] = y;
                    v136[6] = z;
                    v136[7] = 0.0;
                    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
                    sub_1949110(0);
                    v387 = v130;
                    vct_A_local = vct_A;
                    v138 = *(u64 *)&vct_A_local.z;
                    v139 = -vct_A_local.z;
                    v140 = *(u64 *)&vct_A_local.x;
                    v410.w = vct_A_local.w;
                    v410.x = -vct_A_local.z;
                    *(u64 *)&v410.y = __PAIR64__(LODWORD(vct_A_local.x), LODWORD(vct_A_local.y));
                    vct_A.x = v139;
                    vct_A.y = *((f32 *)&v140 + 1);
                    LODWORD(vct_A.z) = v140;
                    vct_A.w = *((f32 *)&v138 + 1);
                    v143 = v142[3].n64_f32[0];
                    v142[2].n64_u64[0] = vneg_f32(v142[2]).n64_u64[0];
                    v142[3].n64_f32[0] = -v143;
                    v409 = vct_A;
                    *(u64 *)&vct_A.x = v140;
                    *(u64 *)&vct_A.z = v138;
                    v147.n128_u64[0] = 0x3F0000003F000000LL;
                    v147.n128_u64[1] = 0x3F0000003F000000LL;
                    vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, v147);
                    vct_B.x = v139;
                    vct_B.y = *((f32 *)&v140 + 1);
                    LODWORD(vct_B.z) = v140;
                    vct_B.w = *((f32 *)&v138 + 1);
                    v149 = z;
                    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
                    sub_1949110(0);
                    v150 = v29->actaiwk->hit_area_r
                         + wk->actaiwk->hit_area_r;
                    v152 = v150 + 50.0;
                    v152 = v150 + 50.0;
                    v153 = y;
                    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v152);
                    v154 = &vf00.x;
                    v154[10] = v149;
                    v154[11] = 0.0;
                    v154[8] = v387;
                    v154[9] = y;
                    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
                    v410 = vct_A;
                    *(u64 *)&vct_A.x = v140;
                    *(u64 *)&vct_A.z = v138;
                    v156 = v387;
                    v157.n128_u64[0] = 0x3F0000003F000000LL;
                    v157.n128_u64[1] = 0x3F0000003F000000LL;
                    vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, v157);
                    v158 = v409;
                    vct_B = v158;
                    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
                    sub_1949110(0);
                    v159 = v29->actaiwk->hit_area_r
                         + wk->actaiwk->hit_area_r;
                    v161 = v159 + 50.0;
                    v161 = v159 + 50.0;
                    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v161);
                    v162 = &vf00.x;
                    v162[8] = v156;
                    v162[9] = v153;
                    v162[10] = v149;
                    v162[11] = 0.0;
                    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
                    v163 = (__n128)vct_A;
                    v164 = v29->para->devilid;
                    v409 = (struct sdfVector4_t)v163;
                    if (v164 <= 260)
                    {
                      if ((v164 & 0xFFFFFFFE) != 0x102)
                      {
                        if (v164 != 260)
                          goto LABEL_319;
LABEL_312:
                        v165 = t1_8->pos.y;
                        v166 = t1_8->pos.z;
                        sub_1B33360(0, v156, v165, v166, 0.0);
                        sub_1B332C0(0, v156, v153, v149, 0.0);
                        sub_1B33400(0);
                        sub_1949110(0);
                        sub_1B335A0(&vct_A_local, 0, v167);
                        v410.w = vct_A_local.w;
                        v410.x = -vct_A_local.z;
                        *(u64 *)&v410.y = __PAIR64__(LODWORD(vct_A_local.x), LODWORD(vct_A_local.y));
                        *(__n128 *)&v168 = sub_1B332C0(0, -vct_A_local.z, vct_A_local.y, vct_A_local.x, vct_A_local.w);
                        v169 = (loc_1DCC840)(0, v168);
                        sub_1B335A0(&v409, 0, v169);
                        sub_1B332C0(0, vct_A_local.x, vct_A_local.y, vct_A_local.z, vct_A_local.w);
                        sub_1B33480(0, 0.5);
                        sub_1B33360(0, v410.x, v410.y, v410.z, v410.w);
                        sub_1B33520(0);
                        sub_1949110(0);
                        sub_1B33480(0, (f32)(v29->actaiwk->hit_area_r + wk->actaiwk->hit_area_r) + 50.0);
                        sub_1B33360(0, v156, v153, v149, 0.0);
                        *(__n128 *)&v170 = sub_1B33520(0);
                        sub_1B335A0(&v410, 0, v170);
                        sub_1B332C0(0, vct_A_local.x, vct_A_local.y, vct_A_local.z, vct_A_local.w);
                        sub_1B33480(0, 0.5);
                        sub_1B33360(0, v409.x, v409.y, v409.z, v409.w);
                        sub_1B33520(0);
                        sub_1949110(0);
                        sub_1B33480(0, (f32)(v29->actaiwk->hit_area_r + wk->actaiwk->hit_area_r) + 50.0);
                        sub_1B33360(0, v156, v153, v149, 0.0);
                        *(__n128 *)&v171 = sub_1B33520(0);
                        v163 = sub_1B335A0(&v409, 0, v171);
                      }
                    }
                    else if ((u32)(v164 - 315) <= 0xFFFFFFFC)
                    {
                      if (v164 != 315)
                        goto LABEL_319;
                      goto LABEL_312;
                    }
                    v163.n128_f32[0] = 900.0 - wk->actaiwk->hit_area_r;
                    if (v410.z > v163.n128_f32[0])
                      v410.z = 900.0 - wk->actaiwk->hit_area_r;
                    if (v409.z > v163.n128_f32[0])
                      LODWORD(v409.z) = v163.n128_u32[0];
LABEL_319:
                    nakamaAtkPos = (u8)wk->nakamaAtkPos;
                    if (wk->nakamaAtkPos)
                    {
                      nakamaAtkPos = (u8)wk->nakamaAtkPos;
                      if (nakamaAtkPos == 2)
                      {
                        v85 = 1;
                        v174 = v410;
                        goto LABEL_362;
                      }
                      if (nakamaAtkPos != 1)
                      {
                        v85 = 0;
                        goto LABEL_363;
                      }
                      v174 = v409;
                      v85 = 2;
                    }
                    else
                    {
                      v177 = v410;
                      sub_1B332C0(0, v177.x, v177.y, v177.z, v177.w);
                      sub_1B33360(0, wk->pos.x, wk->pos.y, wk->pos.z, wk->pos.w);
                      sub_1B33400(0);
                      v178 = (loc_1CDE880)(0);
                      sub_1B332C0(0, v409.x, v409.y, v409.z, v409.w);
                      sub_1B33360(0, wk->pos.x, wk->pos.y, wk->pos.z, wk->pos.w);
                      sub_1B33400(0);
                      v179 = (loc_1CDE880)(0);
                      if (v178 >= v179)
                      {
                        v85 = 2;
                        v174 = v409;
                      }
                      else
                      {
                        v85 = 1;
                        v174 = v410;
                      }
                      wk->nakamaAtkPos = v85;
                    }
LABEL_362:
                    v163 = sub_1B332C0(0, v174.x, v174.y, v174.z, v174.w);
LABEL_363:
                    sub_1B335A0(&FromZ, 0, *(long f64 *)&v163);
                    x = wk->pos.x;
                    v185 = wk->pos.z;
                    v186 = t1_8->pos.x;
                    v187 = t1_8->pos.z;
                    if (sBtlGetLenXZ(x, v185, v186, v187) > (f32)(t1_8->actaiwk->hit_area_r + wk->actaiwk->hit_area_r))
                    {
                      v188 = wk->pos.x;
                      v189 = wk->pos.z;
                      v190 = FromZ.x;
                      v191 = FromZ.z;
                      if (sBtlGetLenXZ(v188, v189, v190, v191) < 150.0)
                      {
                        v192 = wk->pos.x;
                        v193 = wk->pos.z;
                        v194 = v29->pos.x;
                        v195 = v29->pos.z;
                        LenXZ = sBtlGetLenXZ(v192, v193, v194, v195);
                        if (LenXZ < sBtlGetLenXZ(FromZ.x, FromZ.z, v29->pos.x, v29->pos.z))
                        {
                          v197 = wk->pos.x;
                          v198 = wk->pos.y;
                          v199 = wk->pos.z;
                          w = wk->pos.w;
                          *(__n128 *)&v201 = sub_1B332C0(0, v197, v198, v199, w);
                          sub_1B335A0(&FromZ, 0, v201);
                        }
                      }
                    }
                    v202 = FromZ.x;
                    v203 = FromZ.z;
                    v204 = t1_8->pos.x;
                    v205 = t1_8->pos.z;
                    v22 = rot;
                    if (sBtlGetLenXZ(v202, v203, v204, v205) < (f32)(t1_8->actaiwk->hit_area_r + wk->actaiwk->hit_area_r))
                    {
                      v208 = wk->pos.x;
                      v209 = wk->pos.y;
                      v210 = wk->pos.z;
                      v211 = wk->pos.w;
                      *(__n128 *)&v212 = sub_1B332C0(0, v208, v209, v210, v211);
                      sub_1B335A0(&FromZ, 0, v212);
                    }
                    v213 = FromZ;
                    FromZ = sBtlGetFixFormationPos(wk, v29, v206, v213, 50);
                    v214 = t1_8->pos.x;
                    v215 = wk->pos.x;
                    v216 = wk->pos.z;
                    v217 = t1_8->pos.z;
                    if (sBtlGetLenXZ(v215, v216, v214, v217) > (f32)(t1_8->actaiwk->hit_area_r + wk->actaiwk->hit_area_r))
                    {
                      v218 = wk->pos.x;
                      v219 = wk->pos.z;
                      v220 = FromZ.x;
                      v221 = FromZ.z;
                      if (sBtlGetLenXZ(v218, v219, v220, v221) < 150.0)
                      {
                        v222 = wk->pos.x;
                        v223 = wk->pos.z;
                        v224 = v29->pos.x;
                        v225 = v29->pos.z;
                        v226 = sBtlGetLenXZ(v222, v223, v224, v225);
                        if (v226 < sBtlGetLenXZ(FromZ.x, FromZ.z, v29->pos.x, v29->pos.z))
                        {
                          v227 = wk->pos.x;
                          v228 = wk->pos.y;
                          v229 = wk->pos.z;
                          v230 = wk->pos.w;
                          *(__n128 *)&v231 = sub_1B332C0(0, v227, v228, v229, v230);
                          sub_1B335A0(&FromZ, 0, v231);
                        }
                      }
                    }
                    v232 = FromZ.x;
                    v233 = FromZ.z;
                    v234 = t1_8->pos.x;
                    v235 = t1_8->pos.z;
                    if (sBtlGetLenXZ(v232, v233, v234, v235) < (f32)(t1_8->actaiwk->hit_area_r + wk->actaiwk->hit_area_r))
                    {
                      v236 = wk->pos.x;
                      v237 = wk->pos.y;
                      v238 = wk->pos.z;
                      v239 = wk->pos.w;
                      *(__n128 *)&v240 = sub_1B332C0(0, v236, v237, v238, v239);
                      sub_1B335A0(&FromZ, 0, v240);
                    }
                    v241 = wk->pos.x;
                    v242 = wk->pos.z;
                    v243 = FromZ.x;
                    v244 = FromZ.z;
                    if (sBtlGetLenXZ(v241, v242, v243, v244) <= 0.0)
                    {
                      wk->NakamaAtkFormationUse = 0;
                    }
                    else
                    {
                      v247 = FromZ.y;
                      v246 = FromZ.x;
                      v430.x = wk->rot.x;
                      v248 = FromZ.z;
                      wk->NakamaAtkFormationUse = 1;
                      *(u64 *)&wk->NakamaAtkFormationPos.x = __PAIR64__(LODWORD(v247), LODWORD(v246));
                      wk->NakamaAtkFormationPos.z = v248;
                      v251 = wk->pos.x;
                      v250 = wk->pos.y;
                      v253 = wk->pos.z;
                      v252 = wk->pos.w;
                      v430.w = wk->rot.w;
                      v430.y = wk->rot.y;
                      v430.z = wk->rot.z;
                      v388 = v430.x;
                      v372 = wk->rot.z;
                      v377 = wk->rot.w;
                      v370 = wk->rot.y;
                      v430.y = v370;
                      v430.z = v372;
                      v430.w = v377;
                      v430.x = v388;
                      v421.x = v251;
                      v421.y = v250;
                      v421.z = v253;
                      v421.w = v252;
                      *(u64 *)&v413.x = 0;
                      *(f32 *)&v257 = sBtlGetRadian(v421, v430, v413, v246);
                      v258 = *(f32 *)&v257 / 3.0;
                      sub_1B335A0(&wk->rot, 0, v257);
                      sBtlAddUnitDeg(wk, v258);
                    }
                    v86 = 1;
                    if ((rot->flg & 0x224) == 0)
                    {
LABEL_151:
                      if (v86)
                      {
                        v99 = wk->pos.y;
                      }
                      else
                      {
                        v101 = wk->pos.x;
                        v102 = wk->pos.y;
                        v104 = wk->pos.z;
                        v103 = wk->pos.w;
                        sub_1B332C0(0, v101, v102, v104, v103);
                        v105 = (u16)v29->para->devilid;
                        if (v105 == 314 || v105 == 258)
                          v106 = 900.0;
                        else
                          v106 = v29->pos.z;
                        v107 = v29->pos.x;
                        v108 = wk->pos.y;
                        sub_1B33360(0, v107, v108, v106, 0.0);
                        sub_1B33400(0);
                        (loc_1CDE880)(0);
                        sub_1949110(0);
                        sub_1B335A0(&FromZ, 0, v109);
                        v110 = wk->actwk->use_skillid;
                        if (v110 == 168 || v110 == 156)
                        {
                          v111 = FromZ.x;
                          v112 = 300.0;
                        }
                        else
                        {
                          v111 = FromZ.x;
                          v112 = 150.0;
                        }
                        v99 = wk->pos.y;
                        v113 = v29->pos.z;
                        v114 = v29->pos.w;
                        FromZ.x = v29->pos.x + (f32)(v111 * v112);
                        FromZ.y = v99;
                        FromZ.z = v113 + (f32)(FromZ.z * v112);
                        FromZ.w = v114;
                      }
                      v115 = wk->pos.x;
                      v116 = *(u64 *)&wk->pos.z;
                      vct_A.x = v115;
                      vct_A.y = v99;
                      v119 = FromZ;
                      *(u64 *)&vct_A.z = v116;
                      vct_B = v119;
                      vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
                      v120 = &vf00.x;
                      v121 = v120[6];
                      v122 = v120[4];
                      v123 = v120[5];
                      v87 = 0;
                      if (sqrtf((f32)((f32)(v122 * v122) + (f32)(v123 * v123)) + (f32)(v121 * v121)) > 500.0 && v29 != t1_8)
                      {
                        ListID = v29->ListID;
                        v126 = ListID;
                        v259 = wk->actaiwk;
                        v259->LockID = v126;
                        v259->targetID = ListID;
                        v260 = wk->max_mvspd.x;
                        v261 = wk->max_mvspd.y;
                        v262 = wk->max_mvspd.z;
                        v263 = wk->max_mvspd.w;
                        *(__n128 *)&v264 = sub_1B332C0(0, v260, v261, v262, v263);
                        sub_1B335A0(&wk->mv_spdbk, 0, v264);
                        v266 = wk->actaiwk;
                        v266->mode = 2;
                        if ((v22->flg & 0x224) != 0)
                        {
                          v267 = 20.0;
                        }
                        else if ((v22->area & 0x80) != 0)
                        {
                          v267 = 20.0;
                        }
                        else
                        {
                          v267 = 250.0;
                        }
                        p_ppos = &v266->ppos;
                        v269 = FromZ;
                        sBtlGetNWarpPoint(wk, v29, v269, p_ppos, (s32)v267);
                        *(u64 *)&wk->actaiwk->frame = 0x2000000000LL;
                        sBtlSetAction(wk, 57, 32);
                        v87 = 1;
                        v22 = rot;
                        wk->actaiwk->stat = 2;
                        wk->aiwk->stat = 2;
                      }
LABEL_426:
                      if ((v22->area & 0x80) != 0)
                      {
                        r2 = v29->actaiwk->hit_area_r;
                        m_mv_area_r = t1->m_mv_area_r;
                        v270 = wk->actaiwk;
                        if (v270->priv_area_r >= m_mv_area_r)
                          v270->priv_area_r = m_mv_area_r;
                      }
                      else
                      {
                        v270 = wk->actaiwk;
                        r2 = 600.0;
                        m_mv_area_r = v270->priv_area_r;
                      }
                      v273 = (u16)v29->para->devilid;
                      if (v273 == 314 || v273 == 258)
                      {
                        z_low = 1147207680;
                        if ((v22->flg & 0x224) != 0)
                          goto LABEL_433;
                      }
                      else
                      {
                        z_low = LODWORD(v29->pos.z);
                        if ((v22->flg & 0x224) != 0)
                        {
LABEL_433:
                          if ((v22->flg & 0x224) != 0)
                            goto LABEL_468;
                          goto LABEL_434;
                        }
                      }
                      v276 = v29->pos.x;
                      v277 = wk->pos.y;
                      if (!v86 || (v278 = wk->pos.y, v270->frame >= 21))
                      {
                        v279 = wk->pos.x;
                        v281 = wk->pos.z;
                        v280 = wk->pos.w;
                        v422.x = v279;
                        v422.y = v277;
                        v422.z = v281;
                        v422.w = v280;
                        *(u64 *)&per.z = z_low;
                        *(u64 *)&per.x = __PAIR64__(LODWORD(v277), LODWORD(v276));
                        if (sBtlCheckCrossCircle(v422, m_mv_area_r, per, r2))
                        {
                          t1_8a = v276;
                          v431.x = wk->rot.x;
                          v283 = wk->pos.x;
                          v284 = wk->pos.y;
                          v286 = wk->pos.z;
                          v285 = wk->pos.w;
                          v287 = wk->rot.w;
                          v431.y = wk->rot.y;
                          v289 = wk->rot.z;
                          t1d = wk->rot.x;
                          v389 = wk->rot.y;
                          v431.y = v389;
                          v431.x = t1d;
                          v423.y = v284;
                          v423.z = v286;
                          v423.w = v285;
                          v431.z = v289;
                          v431.w = v287;
                          *(u64 *)&v414.x = 0;
                          v423.x = v283;
                          *(f32 *)&v290 = sBtlGetRadian(v423, v431, v414, t1_8a);
                          v291 = *(f32 *)&v290;
                          if ((rot->area & 0x80) != 0)
                          {
                            LODWORD(v290) = 3.0;
                            v291 = v291 / 3.0;
                          }
                          sub_1B335A0(&wk->rot, 0, v290);
                          goto LABEL_467;
                        }
                        if (!v86)
                        {
LABEL_499:
                          rota = wk->max_mvspd;
                          vct_A = rota;
                          p_mv_spd = &wk->mv_spd;
                          *p_mv_spd = vct_A;
                          v325 = wk->mv_spd.z * 1.5;
                          wk->mv_spd.z = v325;
                          if (v87 || p_mv_spd->x == 0.0 && wk->mv_spd.y == 0.0 && v325 == 0.0)
                          {
LABEL_508:
                            if (!wk->motionID)
                              return 1;
                            goto LABEL_509;
                          }
LABEL_537:
                          if (wk->motionID == 5)
                            return 1;
                          v80 = 5;
                          v79 = wk;
                          goto LABEL_122;
                        }
                        v278 = wk->pos.y;
                      }
                      v292 = wk->pos.x;
                      v294 = wk->pos.z;
                      v293 = wk->pos.w;
                      sub_1B332C0(0, v292, v278, v294, v293);
                      sub_1B33360(0, FromZ.x, FromZ.y, FromZ.z, FromZ.w);
                      sub_1B33400(0);
                      v295 = (loc_1CDE880)(0);
                      *(__n128 *)&v296 = sub_1B332C0(0, wk->max_mvspd.x, wk->max_mvspd.y, wk->max_mvspd.z, wk->max_mvspd.w);
                      v298 = (loc_1CDE880)(0, v296);
                      if (v295 < (f32)(v298 + v298))
                      {
                        v299 = v276;
                        v432.x = wk->rot.x;
                        v301 = wk->pos.x;
                        v300 = wk->pos.y;
                        v302 = wk->pos.z;
                        v303 = wk->pos.w;
                        v432.y = wk->rot.y;
                        v432.z = wk->rot.z;
                        v306 = wk->rot.w;
                        t1_8d = wk->rot.x;
                        t1e = wk->rot.y;
                        v390 = wk->rot.z;
                        v432.z = v390;
                        v432.y = t1e;
                        v432.x = t1_8d;
                        v424.x = v301;
                        v424.y = v300;
                        v424.z = v302;
                        v424.w = v303;
                        *(u64 *)&v415.x = 0;
                        v432.w = v306;
                        *(f32 *)&v307 = sBtlGetRadian(v424, v432, v415, v299);
                        v308 = *(f32 *)&v307;
                        v291 = v308 / 3.0;
                        sub_1B335A0(&wk->rot, 0, v307);
LABEL_467:
                        sBtlAddUnitDeg(wk, v291);
                        if ((rot->flg & 0x224) != 0)
                          goto LABEL_468;
                        goto LABEL_434;
                      }
                      goto LABEL_499;
                    }
LABEL_139:
                    v87 = 0;
                    goto LABEL_426;
                  }
                }
              }
              wk->NakamaAtkFormationUse = 0;
              if ((v22->flg & 0x224) != 0)
              {
                v85 = 0;
                v86 = 0;
                goto LABEL_139;
              }
              v88 = wk->aiwk;
              if (!v88->bFarOk && !v88->cmndFrm && !v88->rsvSkl && (v22->area & 0x80) == 0 && (wk->side & 1) != 0)
              {
                v326 = wk->pos.x;
                v327 = wk->pos.y;
                v329 = wk->pos.z;
                v328 = wk->pos.w;
                sub_1B332C0(0, v326, v327, v329, v328);
                sub_1B33360(0, v29->pos.x, v29->pos.y, v29->pos.z, v29->pos.w);
                sub_1B33400(0);
                v330 = wk->pos.x;
                v331 = wk->pos.z;
                v332 = v29->pos.x;
                v333 = v29->pos.z;
                v335 = sBtlGetLenXZ(v330, v331, v332, v333);
                if (v335 > 300.0 && v335 < 500.0 || wk->actaiwk->frame >= 61)
                {
                  wk->aiwk->bFarOk = 1;
                  return 1;
                }
                v336 = (u16)v29->para->devilid;
                if (v336 == 314 || v336 == 258)
                  v391 = 900.0;
                else
                  v391 = v29->pos.z;
                rotb = v29->pos.x;
                v337 = wk->rot.x;
                v338 = wk->pos.x;
                v339 = wk->pos.z;
                v340 = wk->pos.w;
                t1a = wk->pos.y;
                v341 = wk->rot.y;
                v342 = wk->rot.z;
                v343 = wk->rot.w;
                v425.z = v339;
                v425.w = v340;
                v425.y = t1a;
                v433.x = v337;
                v433.y = v341;
                v433.z = v342;
                v433.w = v343;
                *(u64 *)&v416.x = 0;
                v425.x = v338;
                *(f32 *)&v344 = sBtlGetRadian(v425, v433, v416, rotb);
                v345 = *(f32 *)&v344 / 3.0;
                sub_1B335A0(&wk->rot, 0, v344);
                sBtlAddUnitDeg(wk, v345);
                *(__n128 *)&v346 = sub_1B332C0(0, wk->max_mvspd.x, wk->max_mvspd.y, wk->max_mvspd.z, wk->max_mvspd.w);
                sub_1B335A0(&wk->mv_spd, 0, v346);
                if (v335 < 300.0)
                {
                  wk->mv_spd.z = -10.0;
                  if (!wk->motionID)
                    return 1;
LABEL_509:
LABEL_121:
                  v79 = wk;
                  v80 = 0;
LABEL_122:
                  sBtlSetMotion(v79, v80, 4, 0, 0);
                  return 1;
                }
                if (v335 >= 700.0)
                {
                  v347 = wk->pos.x;
                  v348 = wk->pos.y;
                  v349 = wk->pos.z;
                  v350 = wk->pos.w;
                  sub_1B332C0(0, v347, v348, v349, v350);
                  sub_1B33360(0, rotb, t1a, v391, 0.0);
                  sub_1B33400(0);
                  v351 = wk->pos.x;
                  v352 = wk->pos.z;
                  v353 = v29->pos.x;
                  v354 = v29->pos.z;
                  sBtlGetLenXZ(v351, v352, v353, v354);
                  sub_1949110(0);
                  sub_1B335A0(&FromZ, 0, v355);
                  v356 = v29->pos.y;
                  FromZ.x = v29->pos.x + (f32)(FromZ.x * 350.0);
                  FromZ.y = v356;
                  v357 = v29->pos.w;
                  FromZ.z = v29->pos.z + (f32)(FromZ.z * 350.0);
                  FromZ.w = v357;
                  if (v29 != t1_8)
                  {
                    v358 = v29->ListID;
                    v359 = v358;
                    v360 = wk->actaiwk;
                    v360->LockID = v359;
                    v360->targetID = v358;
                    v361 = wk->max_mvspd.x;
                    v362 = wk->max_mvspd.y;
                    v363 = wk->max_mvspd.z;
                    v364 = wk->max_mvspd.w;
                    *(__n128 *)&v365 = sub_1B332C0(0, v361, v362, v363, v364);
                    sub_1B335A0(&wk->mv_spdbk, 0, v365);
                    v366 = wk->actaiwk;
                    v426 = FromZ;
                    v366->mode = 2;
                    sBtlGetNWarpPoint(wk, v29, v426, &v366->ppos, 10);
                    *(u64 *)&wk->actaiwk->frame = 0x2000000000LL;
                    sBtlSetAction(wk, 57, 32);
                    wk->actaiwk->stat = 2;
                    wk->aiwk->stat = 2;
                    return 1;
                  }
                  if (wk->mv_spd.x <= 0.1 && wk->mv_spd.y <= 0.1 && wk->mv_spd.z <= 0.1)
                  {
                    goto LABEL_508;
                  }
                }
                else
                {
                  wk->mv_spd.z = 10.0;
                }
                goto LABEL_537;
              }
              v429 = wk->rot;
              v92 = wk->pos.x;
              v93 = wk->pos.y;
              v94 = wk->pos.z;
              v95 = wk->pos.w;
              v96 = v29->pos.x;
              v382 = wk->rot.x;
              v371 = wk->rot.z;
              v373 = wk->rot.y;
              v369 = wk->rot.w;
              v429.w = v369;
              v429.z = v371;
              v429.y = v373;
              v429.x = v382;
              v420.x = v92;
              v420.y = v93;
              v420.z = v94;
              v420.w = v95;
              *(u64 *)&v412.x = 0;
              Radian = sBtlGetRadian(v420, v429, v412, v96);
              wk->rot = vct_A;
              sBtlAddUnitDeg(wk, Radian * 0.25);
              v22 = rot;
              v85 = 0;
              v86 = 0;
              if ((rot->flg & 0x224) == 0)
                goto LABEL_151;
              goto LABEL_139;
            }
            v379 = wk->pos;
            vct_A = v379;
            v56 = v29->pos;
            vct_B = v56;
            vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
            v57 = &vf00.x;
            v58 = v57[6];
            v59 = v57[4];
            v60 = v57[5];
            v54 = wk->actaiwk;
            if (sqrtf((f32)((f32)(v59 * v59) + (f32)(v60 * v60)) + (f32)(v58 * v58)) > 300.0)
            {
              target_frame = v54->target_frame;
              v63 = __OFSUB__(target_frame, 1);
              v64 = target_frame - 1;
              if (v64 < 0 == v63)
              {
                v54->target_frame = v64;
                v428 = wk->rot;
                v68 = wk->pos.x;
                v69 = wk->pos.y;
                v70 = wk->pos.z;
                v71 = wk->pos.w;
                v72 = v29->pos.x;
                rotd = wk->rot.x;
                t1_8c = wk->rot.y;
                t1c = wk->rot.z;
                v380 = wk->rot.w;
                v428.w = v380;
                v428.z = t1c;
                v428.y = t1_8c;
                v428.x = rotd;
                v419.x = v68;
                v419.y = v69;
                v419.z = v70;
                v419.w = v71;
                *(u64 *)&v412.x = 0;
                *(f32 *)&v73 = sBtlGetRadian(v419, v428, v412, v72);
                v74 = *(f32 *)&v73 / 10.0;
                sub_1B335A0(&wk->rot, 0, v73);
                sBtlAddUnitDeg(wk, v74);
                motionID = wk->motionID;
                wk->mv_spd.z = 0.0;
                if (motionID)
                {
                  sBtlSetMotion(wk, 0, 4, 0, 0);
                }
                wk->NakamaAtkFormationUse = 0;
                return 1;
              }
            }
            goto LABEL_123;
          }
LABEL_9020:
          UnitMng = wk->UnitMng;
          targetID = wk->actaiwk->targetID;
          v34 = sBtlSearchUnit_ID(UnitMng, targetID);
          if (!v34)
          {
LABEL_67:
            v47 = wk->actaiwk;
            v47->mode = 16;
            v47->frame = 0;
            v47->target_frame = 0;
            v48 = wk->actwk->use_skillid;
            sBtlSetUseSkill(wk, v48, 0);
            *(u64 *)&vct_A.x = 0;
            *(u64 *)&vct_A.z = 0;
            v51 = &wk->mv_spdbk;
            v52 = wk->actaiwk;
            *v51 = vct_A;
            v52->status &= ~0x200u;
            if (Nakama == wk)
            {
              wk->nakamaAtkPos0 = 0;
            }
            else if (v11 == wk)
            {
              wk->nakamaAtkPos1 = 0;
            }
            return 1;
          }
          v427 = wk->rot;
          v40 = wk->pos.x;
          v41 = wk->pos.y;
          v42 = wk->pos.z;
          v43 = wk->pos.w;
          v44 = v34->pos.x;
          rotc = wk->rot.x;
          t1_8b = wk->rot.y;
          t1b = wk->rot.z;
          v378 = wk->rot.w;
          v427.w = v378;
          v427.z = t1b;
          v427.y = t1_8b;
          v427.x = rotc;
          v418.x = v40;
          v418.y = v41;
          v418.z = v42;
          v418.w = v43;
          *(u64 *)&v417.x = 0;
          *(u64 *)&v417.z = v35;
          v45 = sBtlGetRadian(v418, v427, v417, v44);
          wk->rot = vct_A;
          sBtlAddUnitDeg(wk, v45);
          goto LABEL_67;
        }
        v20 = wk->actaiwk;
LABEL_46:
        LockID = v20->targetID;
        goto LABEL_47;
      }
      v22 = rot;
      if (v20->mode > 11)
        goto LABEL_46;
      goto LABEL_41;
    }
  }
  else
  {
    use_skillid = wk->actwk->use_skillid;
    if (use_skillid)
      goto LABEL_17;
  }
  sBtlSetNoMP(wk);
  sBtlResetAAI(wk);
  v24 = wk->aiwk;
  v25 = v24->status;
  if ((v25 & 1) != 0)
  {
    v24->meirei_nobk = 7;
    v24->status = v25 & 0xFFFFFFF6;
    goto LABEL_35;
  }
  return 1;
}

// 0x1dab040
bool sBtlNakamaGoalChk(SBTLUNIT_WORK *wk) {
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v4;
  SBTLUNIT_WORK *v6;
  f32 v7;
  f32 v8;
  f32 v9;
  u16 major;
  s32 minor;
  MOTIONDATA_WORK *MotionVisualData;
  SBTLUNIT_WORK *v14;

  Nakama = sBtlGetNakama(0);
  v4 = sBtlGetNakama(1);
  if (!Nakama)
    goto LABEL_22;
  v6 = v4;
  if (!v4)
    goto LABEL_22;
  v7 = Nakama->pos.x - v4->pos.x;
  v8 = Nakama->pos.z - v4->pos.z;
  v9 = sqrtf((f32)(v7 * v7) + (f32)(v8 * v8));
  if (v9 <= 1.0)
    goto LABEL_22;
  major = Nakama->major;
  minor = Nakama->minor;
  MotionVisualData = sBtlGetMotionVisualData(major, minor, 1);
  if (v9 < (f32)(MotionVisualData->m_mv_area_r + sBtlGetMotionVisualData(v6->major, v6->minor, 1)->m_mv_area_r))
  {
    if (sBtlNakamaGaolChk_Sub(Nakama))
      return 1;
    v14 = v6;
  }
  else
  {
LABEL_22:
    v14 = wk;
  }
  return sBtlNakamaGaolChk_Sub(v14);
}

// 0x1dab390
s32 sBtlSetAIData(SBTLUNIT_WORK *wk, PEAICODE code, s32 arg, s32 codet, s32 arg2) {
  s32 Rand;
  s32 v11;
  s32 v12;
  SBTLUNIT_LISTWORK *v14;
  SBTLUNIT_WORK *v15;
  s32 v16;
  SBTLACTAI_WORK *v18;
  SBTLUNIT_WORK *v19;
  sdfVector4_t *v21;
  struct sdfVector4_t v24;
  SBTLACTAI_WORK *v25;
  sdfVector4_t *v26;
  f32 v28;
  s32 v29;
  s32 devilid;
  s32 v31;
  SBTLACTION_WORK *actwk;
  SBTLACTAI_WORK *actaiwk;
  sdatUnitWork_t *para;
  u32 BadStatus;
  SBTLACTAI_WORK *v38;
  s32 *data_p;
  SKLID *haveskill;
  s32 v41;
  u16 Percentage;
  s64 v43;
  s32 v44;
  s32 v45;
  s32 v46;
  s32 v47;
  s32 v48;
  s32 v49;
  s32 v50;
  s32 v51;
  s32 v52;
  s32 v53;
  s32 v54;
  s32 v55;
  s32 v56;
  s32 v57;
  s32 v58;
  s32 v59;
  s32 v60;
  s32 v61;
  s32 v62;
  s32 v64;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v67;
  SBTLUNIT_WORK *v68;
  sdfVector4_t *p_mv_spdbk;
  SBTLACTAI_WORK *v71;
  struct sdfVector4_t pos;
  SBTLACTAI_WORK *v73;
  sdfVector4_t *p_ppos;
  struct sdfVector4_t v75;
  f32 *p_x;
  f32 z;
  f32 x;
  f32 y;
  SBTLACTAI_WORK *v81;
  f32 v83;
  s32 v84;
  s32 v85;
  SBTLUNIT_LISTWORK *v87;
  SBTLUNIT_WORK *v88;
  SBTLUNIT_WORK *v89;
  sdfVector4_t *v91;
  SBTLACTAI_WORK *v92;
  f32 v94;
  sdfVector4_t *v95;
  s32 v96;
  s32 v97;
  SBTLUNIT_LISTWORK *v99;
  SBTLUNIT_WORK *v100;
  SBTLUNIT_WORK *v102;
  sdfVector4_t *v104;
  SBTLACTAI_WORK *v108;
  sdfVector4_t *v109;
  f32 v110;
  s32 v111;
  s32 v112;
  s32 v114;
  SBTLUNIT_LISTWORK *v116;
  SBTLUNIT_WORK *v117;
  SBTLUNIT_WORK *v118;
  sdfVector4_t *v120;
  SBTLACTAI_WORK *v121;
  struct sdfVector4_t v122;
  SBTLACTAI_WORK *v123;
  sdfVector4_t *v124;
  struct sdfVector4_t v125;
  f32 *v126;
  f32 v127;
  f32 v128;
  f32 v129;
  f32 v131;
  f32 v133;
  struct sdfVector4_t v134;
  SBTLACTAI_WORK *v135;
  sdfVector4_t *v136;
  f32 v138;
  SBTLACTAI_WORK *v139;
  f32 v140;
  s32 v141;
  SBTLUNIT_WORK *v142;
  s32 v143;
  s32 v144;
  s32 v146;
  SBTLUNIT_LISTWORK *v148;
  SBTLUNIT_WORK *v149;
  s8 v150;
  sdfVector4_t *v151;
  SBTLUNIT_WORK *v153;
  s32 ListID;
  s32 mode;
  s32 v157;
  SBATTLE_WORK *v160;
  SBTLUNIT_LISTWORK *v161;
  s32 playerID;
  s8 v163;
  sdfVector4_t *v165;
  SBTLACTION_WORK *v167;
  SBTLACTAI_WORK *v168;
  SBTLACTION_WORK *v169;
  SBTLACTAI_WORK *v170;
  s8 v171;
  sdfVector4_t *v172;
  SBTLACTION_WORK *v174;
  SBTLACTAI_WORK *v175;
  SBTLACTION_WORK *v176;
  s32 v177;
  SBTLACTAI_WORK *v178;
  s32 v179;
  SBTLUNIT_LISTWORK *v181;
  SBTLUNIT_WORK *v183;
  s32 v186;
  s32 targetID;
  SBTLUNIT_LISTWORK *v190;
  SBATTLE_WORK *v192;
  SBTLUNIT_LISTWORK *v193;
  s32 v194;
  s32 v195;
  s32 v196;
  SBTLACTAI_WORK *v197;
  f32 v198;
  f32 v199;
  f32 w;
  f32 v201;
  long f64 v202;
  f32 v204;
  s32 v205;
  s32 v206;
  u32 v207;
  SBTLDVLTK_LISTWORK *dvltkList;
  SBTLUNIT_WORK *PChara;
  s32 UseTable_Target;
  SBTLACTAI_WORK *v213;
  struct sdfVector4_t v215;
  struct sdfVector4_t max_mvspd;
  struct sdfVector4_t v217;
  struct sdfVector4_t v218;
  struct sdfVector4_t v219;

  Rand = arg;
  v11 = 1;
  switch (code)
  {
    case 0:
      return v11;
    case 1:
      v31 = 1;
      wk->actaiwk->mode = 1;
      actwk = wk->actwk;
      actwk->total_homing = 0.0;
      actwk->no_homing = 0;
      goto LABEL_291;
    case 2:
      v11 = 2;
      wk->actaiwk->mode = 2;
      sBtlSetNormalAction(wk, 2, arg, Rand, *(sdfVector4_t *)&arg2);
      actaiwk = wk->actaiwk;
      goto LABEL_295;
    case 7:
      v11 = 0;
      wk->actaiwk->data_p[1] = Rand;
      return v11;
    case 8:
      return 0;
    case 9:
      para = wk->para;
      BadStatus = sBtlGetBadStatus(para);
      wk->actwk->use_skillid = Rand;
      if (Rand != 149 && BadStatus - 9 >= 0xFFFFFFFE && (sBtlGetSkilltbl(Rand)->flg & 0x24) != 0)
      {
        wk->actwk->use_skillid = 149;
      }
      goto LABEL_419;
    case 10:
      v38 = wk->actaiwk;
      goto LABEL_250;
    case 11:
      v11 = 0;
      data_p = wk->actaiwk->data_p;
      data_p[0] = Rand;
      data_p[1] = 0;
      return v11;
    case 12:
      haveskill = wk->haveskill;
      v41 = haveskill[0];
      if (!(!v41 || v41 == 149 || v41 == 288))
      {
        Percentage = GetPercentage();
        v43 = 0;
        if (Percentage < 0x32u)
          goto LABEL_417;
        haveskill = wk->haveskill;
      }
      v44 = haveskill[1];
      if (!(!v44 || v44 == 149 || v44 == 288))
      {
        if (GetPercentage() < 0x32u)
        {
          v43 = 1;
          goto LABEL_417;
        }
        haveskill = wk->haveskill;
      }
      v45 = haveskill[2];
      if (v45 && v45 != 149 && v45 != 288)
      {
        if (GetPercentage() < 0x32u)
        {
          v43 = 2;
          goto LABEL_417;
        }
        haveskill = wk->haveskill;
      }
      v46 = haveskill[3];
      if (v46 && v46 != 149 && v46 != 288)
      {
        if (GetPercentage() < 0x32u)
        {
          v43 = 3;
          goto LABEL_417;
        }
        haveskill = wk->haveskill;
      }
      v47 = haveskill[4];
      if (v47 && v47 != 149 && v47 != 288)
      {
        if (GetPercentage() < 0x32u)
        {
          v43 = 4;
          goto LABEL_417;
        }
        haveskill = wk->haveskill;
      }
      v48 = haveskill[5];
      if (v48 && v48 != 149 && v48 != 288)
      {
        if (GetPercentage() < 0x32u)
        {
          v43 = 5;
          goto LABEL_417;
        }
        haveskill = wk->haveskill;
      }
      v49 = haveskill[6];
      if (v49 && v49 != 149 && v49 != 288)
      {
        if (GetPercentage() < 0x32u)
        {
          v43 = 6;
          goto LABEL_417;
        }
        haveskill = wk->haveskill;
      }
      v50 = haveskill[7];
      if (v50 && v50 != 149 && v50 != 288)
      {
        if (GetPercentage() < 0x32u)
        {
          v43 = 7;
          goto LABEL_417;
        }
        haveskill = wk->haveskill;
      }
      v51 = haveskill[8];
      if (v51 && v51 != 149 && v51 != 288)
      {
        if (GetPercentage() < 0x32u)
        {
          v43 = 8;
          goto LABEL_417;
        }
        haveskill = wk->haveskill;
      }
      v52 = haveskill[9];
      if (v52 && v52 != 149 && v52 != 288)
      {
        if (GetPercentage() < 0x32u)
        {
          v43 = 9;
          goto LABEL_417;
        }
        haveskill = wk->haveskill;
      }
      v53 = haveskill[10];
      if (v53 && v53 != 149 && v53 != 288)
      {
        if (GetPercentage() < 0x32u)
        {
          v43 = 10;
          goto LABEL_417;
        }
        haveskill = wk->haveskill;
      }
      v54 = haveskill[11];
      if (v54 && v54 != 149 && v54 != 288)
      {
        if (GetPercentage() < 0x32u)
        {
          v43 = 11;
          goto LABEL_417;
        }
        haveskill = wk->haveskill;
      }
      v55 = haveskill[12];
      if (v55 && v55 != 149 && v55 != 288)
      {
        if (GetPercentage() < 0x32u)
        {
          v43 = 12;
          goto LABEL_417;
        }
        haveskill = wk->haveskill;
      }
      v56 = haveskill[13];
      if (v56 && v56 != 149 && v56 != 288)
      {
        if (GetPercentage() < 0x32u)
        {
          v43 = 13;
          goto LABEL_417;
        }
        haveskill = wk->haveskill;
      }
      v57 = haveskill[14];
      if (v57 && v57 != 149 && v57 != 288)
      {
        if (GetPercentage() < 0x32u)
        {
          v43 = 14;
          goto LABEL_417;
        }
        haveskill = wk->haveskill;
      }
      v58 = haveskill[15];
      if (v58 && v58 != 149 && v58 != 288)
      {
        if (GetPercentage() < 0x32u)
        {
          v43 = 15;
          goto LABEL_417;
        }
        haveskill = wk->haveskill;
      }
      v59 = haveskill[16];
      if (v59 && v59 != 149 && v59 != 288)
      {
        if (GetPercentage() < 0x32u)
        {
          v43 = 16;
          goto LABEL_417;
        }
        haveskill = wk->haveskill;
      }
      v60 = haveskill[17];
      if (!v60 || v60 == 149 || v60 == 288)
        goto LABEL_135;
      if (GetPercentage() < 0x32u)
      {
        Rand = 149;
      }
      else
      {
        haveskill = wk->haveskill;
LABEL_135:
        v61 = haveskill[18];
        if (v61 && v61 != 149 && v61 != 288 && GetPercentage() <= 0x31u)
        {
          v43 = 18;
LABEL_417:
          Rand = wk->haveskill[v43];
        }
      }
      wk->actwk->use_skillid = Rand;
LABEL_419:
      UseTable_Target = sBtlGetUseTable_Target(wk, codet, arg2);
      wk->actaiwk->targetID = UseTable_Target;
      wk->actaiwk->targetID = sBtlCheckEnemyTarget(wk, UseTable_Target);
      sBtlSetAIMode(wk);
      v213 = wk->actaiwk;
      wk->aiwk->stat = 2;
      v213->stat = 1;
      v213->dataflg = 1;
      v213->mode = 14;
      return 4;
    case 13:
      v62 = sBtlGetUseTable_Target(wk, codet, arg2);
      v64 = sBtlCheckEnemyTarget(wk, v62);
      UnitMng = wk->UnitMng;
      v67 = sBtlSearchUnit_ID(UnitMng, v64);
      v18 = wk->actaiwk;
      if (!v67)
        goto LABEL_307;
      v68 = v67;
      v18->status = v18->status & 0xFFFFFDE0 | 0x14;
      max_mvspd = wk->max_mvspd;
      vct_A = max_mvspd;
      p_mv_spdbk = &wk->mv_spdbk;
      v71 = wk->actaiwk;
      *p_mv_spdbk = vct_A;
      v71->mode = 2;
      pos = v68->pos;
      vct_A = pos;
      v73 = wk->actaiwk;
      p_ppos = &v73->ppos;
      *p_ppos = vct_A;
      v75 = wk->pos;
      vct_B = v75;
      vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      p_x = &vf00.x;
      z = p_x[6];
      x = p_x[4];
      y = p_x[5];
      v81 = wk->actaiwk;
      v81->frame = 0;
      v83 = sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z)) / wk->mv_spdbk.z;
      if (v83 <= (f32)Rand)
        v83 = Rand;
      v84 = v83;
      if (v83 == INFINITY)
        v84 = 0x80000000;
      v81->cmpframe = v84;
      goto LABEL_302;
    case 14:
      v85 = sBtlGetUseTable_Target(wk, codet, arg2);
      v87 = wk->UnitMng;
      v88 = sBtlSearchUnit_ID(v87, v85);
      v18 = wk->actaiwk;
      if (!v88)
        goto LABEL_307;
      v89 = v88;
      v18->status = v18->status & 0xFFFFFDE0 | 0x14;
      v217 = wk->max_mvspd;
      vct_A = v217;
      v91 = &wk->mv_spdbk;
      v92 = wk->actaiwk;
      *v91 = vct_A;
      v92->mode = 2;
      v94 = (f32)GetRand(0x64u) + 400.0;
      v95 = &wk->actaiwk->ppos;
      if (v94 == INFINITY)
        v96 = 0x80000000;
      else
        v96 = v94;
      sBtlGetFukinPoint(v89, wk, v95, v96);
      goto LABEL_301;
    case 15:
      v97 = sBtlGetUseTable_Target(wk, codet, arg2);
      v99 = wk->UnitMng;
      v100 = sBtlSearchUnit_ID(v99, v97);
      v18 = wk->actaiwk;
      if (!v100)
        goto LABEL_307;
      v102 = v100;
      v18->status = v18->status & 0xFFFFFDE0 | 0x14;
      v218 = wk->max_mvspd;
      vct_A = v218;
      v104 = &wk->mv_spdbk;
      v108 = wk->actaiwk;
      v109 = &v108->ppos;
      *v104 = vct_A;
      v108->mode = 2;
      vct_A.x = wk->mv_spdbk.z * 1.5;
      wk->mv_spdbk.z = vct_A.x;
      v110 = vct_A.x * (f32)Rand;
      if (!(u32)v108)
      if (v110 == INFINITY)
        v111 = 0x80000000;
      else
        v111 = v110;
      sBtlGetEscapePoint(wk, v102, v109, v111);
      goto LABEL_301;
    case 16:
    case 35:
      v12 = sBtlGetUseTable_Target(wk, codet, arg2);
      v14 = wk->UnitMng;
      v15 = sBtlSearchUnit_ID(v14, v12);
      v18 = wk->actaiwk;
      if (!v15)
        goto LABEL_307;
      v19 = v15;
      v18->status = v18->status & 0xFFFFFDE0 | 0x14;
      v215 = wk->max_mvspd;
      vct_A = v215;
      v21 = &wk->mv_spdbk;
      v24 = vct_A;
      v25 = wk->actaiwk;
      v26 = &v25->ppos;
      *v21 = v24;
      v25->mode = 2;
      if (code == 16)
      {
        v28 = wk->mv_spdbk.z * (f32)Rand;
        if (v28 == INFINITY)
          v29 = 0x80000000;
        else
          v29 = v28;
        sBtlGetSenkaiPoint(wk, v19, v26, v29);
      }
      else
      {
        sBtlGetShinSenkaiPoint(wk, v19, v26, v16);
      }
LABEL_301:
      v178 = wk->actaiwk;
      v178->frame = 0;
      v178->cmpframe = Rand;
      goto LABEL_302;
    case 17:
      v112 = sBtlGetUseTable_Target(wk, codet, arg2);
      v114 = sBtlCheckEnemyTarget(wk, v112);
      v116 = wk->UnitMng;
      v117 = sBtlSearchUnit_ID(v116, v114);
      v18 = wk->actaiwk;
      if (!v117)
        goto LABEL_307;
      v118 = v117;
      v18->status = v18->status & 0xFFFFFDE0 | 0x14;
      v219 = wk->max_mvspd;
      vct_A = v219;
      v120 = &wk->mv_spdbk;
      v121 = wk->actaiwk;
      *v120 = vct_A;
      v121->mode = 2;
      v122 = v118->pos;
      vct_A = v122;
      v123 = wk->actaiwk;
      v124 = &v123->ppos;
      *v124 = vct_A;
      v125 = wk->pos;
      vct_B = v125;
      vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v126 = &vf00.x;
      v127 = v126[6];
      v128 = v126[4];
      v129 = v126[5];
      v131 = sqrtf((f32)((f32)(v128 * v128) + (f32)(v129 * v129)) + (f32)(v127 * v127));
      sub_1949110(0);
      v133 = v131 * 2.5;
      v133 = v131 * 2.5;
      vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v133);
      v134 = wk->pos;
      vct_B = v134;
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v135 = wk->actaiwk;
      v136 = &v135->ppos;
      *v136 = vct_A;
      v138 = wk->mv_spdbk.z;
      v139 = wk->actaiwk;
      v139->frame = 0;
      v140 = (f32)(v131 / v138) * 2.5;
      v141 = v140;
      if (v140 == INFINITY)
        v141 = 0x80000000;
      v139->cmpframe = v141;
LABEL_302:
      sBtlSetMotion(wk, 5, 4, 0, 0);
      sBtlSetAction(wk, 2, 0);
      v18 = wk->actaiwk;
      v18->stat = 2;
      wk->aiwk->stat = 2;
LABEL_307:
      v18->dataflg = 1;
      return 4;
    case 18:
      wk->actaiwk->mode = 12;
      v142 = wk;
      v143 = 12;
      goto LABEL_294;
    case 19:
      v38 = wk->actaiwk;
      v38->datamode = Rand;
LABEL_250:
      v38->dataflg = 0;
      *(u64 *)v38->data_p = 0;
      return v11;
    case 20:
      v144 = sBtlGetUseTable_Target(wk, codet, arg2);
      v146 = sBtlCheckEnemyTarget(wk, v144);
      v148 = wk->UnitMng;
      v149 = sBtlSearchUnit_ID(v148, v146);
      v18 = wk->actaiwk;
      if (v149)
      {
        v153 = v149;
        ListID = v149->ListID;
        mode = 6;
        v18->mode = 6;
        v157 = ListID;
        v18 = wk->actaiwk;
        v157 = v153->ListID;
        mode = v18->mode;
        v18->LockID = v157;
        v18->targetID = ListID;
        sBtlSetNormalAction(wk, mode, v150, Rand, v151);
        v18 = wk->actaiwk;
        v18->stat = 2;
        wk->aiwk->stat = 2;
      }
      goto LABEL_307;
    case 21:
    case 32:
      wk->actaiwk->mode = 1;
      Rand = GetRand(Rand + 1);
      if (code == 32)
      {
        devilid = wk->para->devilid;
        Rand = sBtlGetContinueRaito(devilid) * Rand / 100;
      }
      v31 = wk->actaiwk->mode;
      goto LABEL_293;
    case 22:
      *(u64 *)wk->actaiwk->data_p = (u32)(Rand - 8);
      sBtlUseTableDataProc(wk);
      wk->actaiwk->dataflg = 1;
      return v11;
    case 23:
      wk->actaiwk->mode = 3;
      v142 = wk;
      v143 = 3;
      goto LABEL_294;
    case 24:
      v11 = 0;
      if (!Rand)
        wk->actaiwk->aiPtnCont = arg2 != 0;
      return v11;
    case 25:
      v160 = wk;
      v161 = v160->UnitMng;
      playerID = v160->playerID;
      if (sBtlSearchUnit_ID(v161, playerID)->vstatus != 0x8000)
      {
        v179 = sBtlGetUseTable_Target(wk, codet, arg2);
        v181 = wk->UnitMng;
        v183 = sBtlSearchUnit_ID(v181, v179);
        if (!v183)
        {
          v186 = sBtlGetUseTable_Target(wk, codet, arg2);
          wk->actaiwk->targetID = v186;
          targetID = sBtlCheckEnemyTarget(wk, v186);
          wk->actaiwk->targetID = targetID;
          v190 = wk->UnitMng;
          v183 = sBtlSearchUnit_ID(v190, targetID);
          if (!v183)
          {
            v192 = wk;
            v193 = v192->UnitMng;
            v194 = v192->playerID;
            v183 = sBtlSearchUnit_ID(v193, v194);
            if (!v183)
              goto LABEL_404;
          }
        }
        v195 = v183->ListID;
        v196 = v195;
        v196 = v183->ListID;
        v197 = wk->actaiwk;
        v197->LockID = v196;
        v197->targetID = v195;
        v198 = wk->max_mvspd.x;
        v199 = wk->max_mvspd.y;
        v201 = wk->max_mvspd.z;
        w = wk->max_mvspd.w;
        *(__n128 *)&v202 = sub_1B332C0(0, v198, v199, v201, w);
        sub_1B335A0(&wk->mv_spdbk, 0, v202);
        wk->actaiwk->mode = 2;
        v204 = (f32)GetRand(0x190u) + 500.0;
        if (v204 == INFINITY)
          v205 = 0x80000000;
        else
          v205 = v204;
        sBtlGetWarpPoint(wk, v183, &wk->actaiwk->ppos, v205);
        *(u64 *)&wk->actaiwk->frame = 0x3C00000000LL;
        sBtlSetAction(wk, 54, 60);
        wk->actaiwk->stat = 2;
        wk->aiwk->stat = 2;
        v206 = sBtlGetPChara()->actaiwk->targetID;
        if (v206 != -1 && wk->ListID == v206)
        {
          v207 = wk->para->aisyo->para[1];
          if (v207 < 0x1000 || (v207 & 0x4000) != 0)
          {
            dvltkList = wk->dvltkList;
            PChara = sBtlGetPChara();
            sBtlCreateDvltk_Gouto(dvltkList, PChara, 262, 1);
          }
        }
LABEL_404:
        v18 = wk->actaiwk;
        goto LABEL_307;
      }
      wk->actaiwk->mode = 1;
      v167 = wk->actwk;
      v167->total_homing = 0.0;
      v167->no_homing = 0;
      sBtlSetNormalAction(wk, 1, v163, Rand, v165);
      v168 = wk->actaiwk;
      v168->stat = 2;
      wk->aiwk->stat = 2;
      v168->dataflg = 1;
      return 4;
    case 26:
      wk->aiwk->syscnt_stop = 0;
      goto LABEL_280;
    case 27:
      ++wk->aiwk->hcnt;
      goto LABEL_280;
    case 28:
      wk->aiwk->hcnt = 0;
LABEL_280:
      wk->actaiwk->mode = 1;
      v169 = wk->actwk;
      v169->total_homing = 0.0;
      v169->no_homing = 0;
      v11 = 4;
      sBtlSetNormalAction(wk, 1, arg, 4, *(sdfVector4_t *)&arg2);
      v170 = wk->actaiwk;
      v170->stat = 2;
      wk->aiwk->stat = 2;
      v170->dataflg = 1;
      return v11;
    case 29:
      sBtlZakoRouletteSet(wk);
      wk->actaiwk->mode = 1;
      v174 = wk->actwk;
      v174->total_homing = 0.0;
      v174->no_homing = 0;
      sBtlSetNormalAction(wk, 1, v171, 310, v172);
      v175 = wk->actaiwk;
      v175->stat = 2;
      wk->aiwk->stat = 2;
      v175->dataflg = 1;
      return 4;
    case 31:
      wk->actaiwk->mode = 1;
      v176 = wk->actwk;
      v176->total_homing = 0.0;
      v176->no_homing = 0;
      v177 = wk->para->devilid;
      Rand = sBtlGetContinueRaito(v177) * Rand / 100;
      v31 = wk->actaiwk->mode;
LABEL_291:
LABEL_293:
      v142 = wk;
      v143 = v31;
LABEL_294:
      sBtlSetNormalAction(v142, v143, arg, Rand, *(sdfVector4_t *)&arg2);
      actaiwk = wk->actaiwk;
      v11 = 2;
LABEL_295:
      actaiwk->stat = 2;
      wk->aiwk->stat = 2;
      actaiwk->dataflg = 1;
      return v11;
    case 33:
      if (!wk->weak_shild)
        goto LABEL_297;
      return 2;
    case 34:
LABEL_297:
      wk->weak_shild = Rand;
      return 2;
    default:
      return 2;
  }
}

// 0x1db2700
bool sBtlCheckCodeArg(PEAICODE code) {
  return ((u32)code < 0x24) & (0x80313F200uLL >> code);
}

// 0x1db2720
SBTLUNIT_WORK *sBtlCheckCharmTarget(SBTLUNIT_WORK *wk) {
  sdatUnitWork_t *para;
  SBATTLE_WORK *v7;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v10;

  para = wk->para;
  if (sBtlGetBadStatus(para) != 7)
    return wk;
  v7 = wk;
  UnitMng = v7->UnitMng;
  playerID = v7->playerID;
  v10 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (v10)
    return v10;
  return wk;
}

// 0x1db2850
SBTLUNIT_SIDE sBtlGetCharmSide(SBTLUNIT_WORK *wk, SBTLUNIT_SIDE side) {
  sdatUnitWork_t *para;
  u32 BadStatus;
  s32 v7;

  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  if ((side & 2) != 0)
    v7 = 1;
  else
    v7 = 2;
  if (BadStatus == 7)
    return v7;
  else
    return side;
}

// 0x1db28e0
bool sBtlCheckCrossUnit_HIT(SBTLUNIT_WORK *wk, const sdfVector4_t *ppos) {
  f32 y;
  f32 x;
  s32 side;
  SBTLUNIT_LISTWORK *SideList;
  s32 count;
  SBTLUNIT_LISTWORK *v9;
  s64 v10;
  f32 hit_area_r;
  SBTLUNIT_WORK *pUnit;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  bool v18;
  sdfVector4_t vector2;
  f32 z;
  f32 w;
  sdfVector4_t v24;

  z = ppos->z;
  w = ppos->w;
  y = ppos->y;
  x = ppos->x;
  side = wk->side;
  SideList = sBtlCreateSideList(side, 1);
  count = SideList->count;
  v9 = SideList;
  if (count < 1)
  {
    LODWORD(v10) = 0;
    goto LABEL_12;
  }
  v10 = 0;
  hit_area_r = wk->actaiwk->hit_area_r;
  do
  {
    pUnit = v9->pUnitL[v10]->pUnit;
    v13 = pUnit->pos.x;
    v14 = pUnit->pos.y;
    v15 = pUnit->actaiwk->hit_area_r;
    v16 = pUnit->pos.z;
    v17 = pUnit->pos.w;
    v24.z = z;
    v24.w = w;
    v24.x = x;
    v24.y = y;
    *(u64 *)&vector2.z = __PAIR64__(LODWORD(v17), LODWORD(v16));
    *(u64 *)&vector2.x = __PAIR64__(LODWORD(v14), LODWORD(v13));
    v18 = sBtlCheckCrossCircle(v24, hit_area_r, vector2, v15);
    count = v9->count;
    if (v18)
      break;
    ++v10;
  }
  while (v10 < count);
LABEL_12:
  sBtlDeleteUnitList(v9, 0);
  return (s32)v10 >= count;
}

// 0x1db2a70
bool sBtlCheckEquationProc(SBTLUNIT_WORK *wk) {
  s32 *v3;
  sdatUnitWork_t *para;
  s32 devilid;
  SB_ENCOUNTPAC *EncountPac;
  AITBLDATA_WORK *AITBL;
  s32 v13;
  SBTLACTAI_WORK *actaiwk;
  s32 *ai_target;
  u32 *code;
  u64 v17;
  u64 v18;
  u64 v19;
  s32 v20;
  s32 v21;
  s64 v22;
  u64 v23;
  u32 v24;
  CheckFuncTblDelegate v26;
  s32 v27;
  SBTLACTAI_WORK *v28;
  u64 v29;
  u32 v30;
  CheckFuncTblDelegate v32;
  s32 v33;
  SBTLACTAI_WORK *v34;
  u64 v35;
  u32 v36;
  CheckFuncTblDelegate v38;
  s32 v39;
  bool v40;
  SBTLACTAI_WORK *v41;
  s32 v42;
  s64 v43;
  signed s16 Percentage;
  AIACT_TBL *acttbl;
  il2cpp_array_size_t v47;
  Il2CppClass **v48;
  s32 name;
  s64 v50;
  s32 v51;
  s32 v52;
  s32 v53;
  s64 v54;
  s32 v55;
  s32 v56;
  s32 v57;
  s32 v58;
  s32 v59;

  v3 = NewSpecific(s32, 3u);
  wk->actaiwk->aiPtnCont = 0;
  if (sBtlIsHuuma())
    return 1;
  if (wk->para->devilid == 316)
    return 1;
  if (wk->encountno == 22)
  {
    para = wk->para;
    devilid = (u16)para->devilid;
    if ((devilid == 164 || devilid == 90) && para->now->hp == para->now->maxhp)
      return 1;
  }
  EncountPac = sBtlGetEncountPac(-1);
  if ((EncountPac[wk->encountno]->flag & 4) == 0 && (wk->side & 2) != 0 && wk->actaiwk->nonempflg)
  {
    AITBL = ai_tbldata[0][0];
    goto LABEL_29;
  }
  v13 = wk->para->devilid;
  AITBL = sBtlGetAITBL(v13, wk);
LABEL_29:
  actaiwk = wk->actaiwk;
  v3[2] = -1;
  *(u64 *)&v3[0] = -1;
  ai_target = actaiwk->ai_target;
  *(u64 *)ai_target = -1;
  ai_target[2] = -1;
  code = AITBL->act[actaiwk->datamode]->code;
  v17 = code[8];
  if ((u32)v17 >= 0x100000)
  {
    v23 = v17 >> 20;
    v24 = v17 & 0xFFFFF;
    v26 = CheckFuncTbl[v23];
    v27 = (v26->invoke_impl)(v26->method_code, wk, v24, 0, v26->method);
    v28 = wk->actaiwk;
    v3[0] = v27;
    code = AITBL->act[v28->datamode]->code;
    v18 = code[9];
    if ((u32)v18 < 0x100000)
    {
LABEL_31:
      v19 = code[10];
      if ((u32)v19 < 0x100000)
        goto LABEL_32;
LABEL_41:
      v35 = v19 >> 20;
      v36 = v19 & 0xFFFFF;
      v38 = CheckFuncTbl[v35];
      v39 = (v38->invoke_impl)(v38->method_code, wk, v36, 2, v38->method);
      v3[2] = v39;
      v20 = v3[1];
      v21 = v39;
      if (v3[0] == 1)
        goto LABEL_33;
      goto LABEL_44;
    }
  }
  else
  {
    v18 = code[9];
    if ((u32)v18 < 0x100000)
      goto LABEL_31;
  }
  v29 = v18 >> 20;
  v30 = v18 & 0xFFFFF;
  v32 = CheckFuncTbl[v29];
  v33 = (v32->invoke_impl)(v32->method_code, wk, v30, 1, v32->method);
  v34 = wk->actaiwk;
  v3[1] = v33;
  v19 = AITBL->act[v34->datamode]->code[2];
  if ((u32)v19 >= 0x100000)
    goto LABEL_41;
LABEL_32:
  v20 = v3[1];
  v21 = v3[2];
  if (v3[0] == 1)
  {
LABEL_33:
    if (v20 == 1)
    {
      v22 = v21 != 1;
    }
    else
    {
      v40 = v21 == 1;
      v22 = 4;
      if (v40)
        v22 = 2;
    }
    goto LABEL_53;
  }
LABEL_44:
  if (v20 == 1)
  {
    v40 = v21 == 1;
    v22 = 5;
    if (v40)
      v22 = 3;
  }
  else
  {
    v40 = v21 == 1;
    v22 = 6;
    if (!v40)
      v22 = 7;
  }
LABEL_53:
  v41 = wk->actaiwk;
  v42 = AITBL->act[v41->datamode]->jmptbl[v22];
  if (v42 <= 7)
  {
    v43 = v42;
    Percentage = GetPercentage();
    acttbl = AITBL->acttbl;
    v47 = acttbl->bounds[1].length * v43;
    v48 = &acttbl->obj.klass + v47;
    name = v48[4]->_1.name;
    if (name << 16 < 1 || (v50 = 0, (s16)name < Percentage))
    {
      v51 = LODWORD(v48[5]->_1.name) + name;
      if (v51 << 16 < 1 || (s16)v51 < Percentage)
      {
        v52 = LODWORD(v48[6]->_1.name) + v51;
        if (v52 << 16 < 1 || (s16)v52 < Percentage)
        {
          v53 = LODWORD(v48[7]->_1.name) + v52;
          if (v53 << 16 < 1 || (s16)v53 < Percentage)
            return 1;
          v50 = 3;
        }
        else
        {
          v50 = 2;
        }
      }
      else
      {
        v50 = 1;
      }
    }
    v54 = *((u64 *)&acttbl[v47] + v50);
    v55 = *(u32 *)(v54 + 20);
    LODWORD(v54) = *(u32 *)(v54 + 24);
    v56 = v55 >> 16;
    v57 = (u16)v55;
    v58 = (s32)v54 >> 16;
    v59 = (u16)v54;
    sBtlSetAIData(wk, v56, v57, v58, v59);
    if (v56 == 22)
      return 1;
    wk->actaiwk->dataflg = 0;
    return 1;
  }
  else
  {
    if ((u32)v42 > 0xF)
      return 1;
    v41->data_p[0] = v42 - 8;
    sBtlUseTableDataProc(wk);
    return 1;
  }
}

// 0x1db64d0
SBTLUNIT_WORK *sBtlGetWarpUnit_ID(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  s32 targetID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v10;
  SBTLUNIT_WORK *v11;
  SBATTLE_WORK *v14;
  SBTLUNIT_LISTWORK *v15;
  s32 playerID;

  actaiwk = wk->actaiwk;
  if ((actaiwk->status & 0x180) != 0x100)
  {
LABEL_10:
    if (actaiwk->mode <= 11)
      goto LABEL_11;
LABEL_19:
    targetID = actaiwk->targetID;
    goto LABEL_20;
  }
  goto LABEL_10;
LABEL_11:
  targetID = actaiwk->LockID;
  if (wk->battlemode == 3)
    goto LABEL_20;
  goto LABEL_17;
  if (wk->battlemode != 3)
  {
LABEL_17:
    if ((wk->side & 0x80) == 0)
      goto LABEL_20;
    actaiwk = wk->actaiwk;
    goto LABEL_19;
  }
LABEL_20:
  UnitMng = wk->UnitMng;
  v10 = sBtlSearchUnit_ID(UnitMng, targetID);
  if (v10)
  {
    v11 = v10;
    if (sBtlCheckExist(v10))
      return v11;
  }
  v14 = wk;
  v15 = v14->UnitMng;
  playerID = v14->playerID;
  return sBtlSearchUnit_ID(v15, playerID);
}

// 0x1db6740
void sBtlSetWalk(SBTLUNIT_WORK *wk, f32 length) {
  SBTLACTAI_WORK *actaiwk;

  if (!sBtlCheckMotionID(wk, 5))
    return;
  if ((wk->side & 2) == 0)
  {
    if ((wk->aiwk->m_status & 0x40000) != 0 || (actaiwk = wk->actaiwk, !actaiwk->target_frame) && !actaiwk->mahaskl_waitframe)
    {
      sBtlSetMotion(wk, 5, 4, 0, 0);
    }
    sBtlSetAction(wk, 2, 0);
  }
}

// 0x1db6870
bool sBtlCheckWapIN(SBTLUNIT_WORK *wk) {
  return 0;
}

// 0x1da9780
s32 sBtlGetLockID(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  s32 LockID;

  actaiwk = wk->actaiwk;
  if ((actaiwk->status & 0x180) == 0x100)
  {
    actaiwk = wk->actaiwk;
  }
  if (actaiwk->mode <= 11)
  {
    LockID = actaiwk->LockID;
    if (wk->battlemode == 3)
      return LockID;
    if ((wk->side & 0x80) == 0)
      return LockID;
    actaiwk = wk->actaiwk;
  }
  return actaiwk->targetID;
}

// 0x1daa260
void sBtlSetLockID(SBTLUNIT_WORK *wk, s32 lockid) {
  wk->actaiwk->LockID = lockid;
}

// 0x1daa250
void sBtlSetTargetID(SBTLUNIT_WORK *wk, s32 targetd) {
  wk->actaiwk->targetID = targetd;
}

// 0x1db6880
bool sBtlPrivAreaCheck(SBTLUNIT_WORK *wk, s32 flg) {
  s64 v5;
  long f64 v6;
  s64 v7;
  s64 v8;
  long f64 v9;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 side;
  s32 v14;
  s32 v15;
  s32 v16;
  s32 devilid;
  s32 v20;
  u32 status;
  f32 x;
  f32 y;
  f32 hit_area_r;
  f32 z;
  f32 w;
  f32 v31;
  f32 v32;
  f32 r2;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 GroundPos;
  bool v39;
  long f64 v40;
  f32 v44;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 Radian;
  f32 v51;
  f32 v52;
  f32 v54;
  f32 v55;
  f32 v56;
  f32 v57;
  f32 v58;
  f32 v59;
  sdfVector4_t vector2;
  f32 v62;
  f32 v63;
  f32 v64;
  f32 v65;
  f32 v66;
  f32 v67;
  s64 v68;
  s64 v69;
  sdfVector4_t v70;
  sdfVector4_t v71;
  sdfVector4_t v72;
  sdfVector4_t v73;
  sdfVector4_t v74;
  sdfVector4_t v75;

  v5 = 0;
  v68 = 0;
  v69 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v5 >= UnitMng->number)
      return 1;
    pUnit = UnitMng->pUnitL[v5]->pUnit;
    if (!pUnit)
      goto LABEL_8;
    if (pUnit->ListID == wk->ListID)
      goto LABEL_8;
    side = wk->side;
    if ((side & 7) != 0)
    {
      v14 = pUnit->side;
      v15 = ((u8)v14 | (u8)side) & 2;
      v16 = ((u8)v14 ^ (u8)side) & 7;
      if ((v14 & 7) != 0 && v15 == 0 && v16 == 0)
        goto LABEL_8;
    }
    devilid = wk->para->devilid;
    if (devilid != 292 && (u32)(devilid - 297) <= 0xFFFFFFFC)
    {
      v20 = pUnit->para->devilid;
      if (v20 == 292 || (u32)(v20 - 297) > 0xFFFFFFFC)
        goto LABEL_8;
      if (!sBtlCheckExist2(pUnit))
        goto LABEL_8;
      status = wk->status;
      if ((status & 0x800) != 0)
        goto LABEL_8;
      if (!(pUnit->status & 0x800 | status & 1 | ((u16)pUnit->status | (u16)status) & 0x1000 | pUnit->status & 1) && (wk->vstatus & 0x200) == 0 && flg == 1 && (pUnit->vstatus & 0x200) == 0)
      {
        x = pUnit->pos.x;
        y = pUnit->pos.y;
        v71.x = wk->pos.x;
        v71.y = wk->pos.y;
        hit_area_r = wk->actaiwk->hit_area_r;
        z = wk->pos.z;
        w = wk->pos.w;
        v32 = pUnit->pos.z;
        v31 = pUnit->pos.w;
        r2 = pUnit->actaiwk->hit_area_r;
        v64 = wk->pos.y;
        v66 = wk->pos.x;
        v71.y = v64;
        v71.x = v66;
        v71.z = z;
        v71.w = w;
        *(u64 *)&vector2.z = __PAIR64__(LODWORD(v31), LODWORD(v32));
        *(u64 *)&vector2.x = __PAIR64__(LODWORD(y), LODWORD(x));
        if (sBtlCheckCrossCircle(v71, hit_area_r, vector2, r2))
        {
          v34 = pUnit->pos.x;
          v35 = pUnit->pos.z;
          v36 = pUnit->actaiwk->hit_area_r;
          v37 = wk->actaiwk->hit_area_r;
          GroundPos = sBtlGetGroundPos(v34, v35);
          v39 = sBtlSetPushPos(wk, v37, pUnit, v36, GroundPos);
          sub_1B335A0(&pUnit->pos, 0, v40);
          pUnit->mv_spd.z = 0.0;
          if (!v39)
          {
            v72.x = wk->pos.x;
            v72.y = wk->pos.y;
            v72.z = wk->pos.z;
            v44 = wk->pos.w;
            v45 = wk->rot.x;
            v75.y = wk->rot.y;
            v46 = wk->rot.z;
            v47 = wk->rot.w;
            v48 = pUnit->pos.x;
            v65 = wk->pos.y;
            v67 = wk->pos.x;
            v62 = wk->rot.y;
            v63 = wk->pos.z;
            v75.y = v62;
            v72.z = v63;
            v72.y = v65;
            v72.x = v67;
            v72.w = v44;
            v75.x = v45;
            v75.z = v46;
            v75.w = v47;
            *(u64 *)&v70.x = 0;
            Radian = sBtlGetRadian(v72, v75, v70, v48);
            v51 = wk->actaiwk->hit_area_r;
            v52 = pUnit->actaiwk->hit_area_r;
            v73.x = v51 + v52;
            v73.y = 2.0;
            if (!sBtlGetMovePos_MapHit_2(wk, pUnit, v73, (f32)(v51 + v52) + 2.0, Radian, 1))
            {
              v54 = wk->actaiwk->hit_area_r;
              v55 = pUnit->actaiwk->hit_area_r;
              v74.x = v54 + v55;
              if (!sBtlGetMovePos_MapHit_2(wk, pUnit, v74, v55 + (f32)(v54 + v55), Radian, 1))
              {
                v56 = pUnit->pos.x;
                v57 = pUnit->pos.y;
                v58 = pUnit->pos.z;
                v59 = pUnit->pos.w;
                *(__n128 *)&v6 = sub_1B332C0(0, v56, v57, v58, v59);
                sub_1B335A0(&v68, 0, v6);
              }
            }
            v7 = v68;
            v8 = v69;
            *(__n128 *)&v9 = sub_1B332C0(0, *(f32 *)&v7, *((f32 *)&v7 + 1), *(f32 *)&v8, *((f32 *)&v8 + 1));
            sub_1B335A0(&pUnit->pos, 0, v9);
          }
        }
      }
    }
LABEL_8:
    ++v5;
  }
}

// 0x1db7580
bool sBtlCheckSearchEnemy(SBTLUNIT_WORK *wk, s32 id, s8 mode) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  s64 number;
  bool v10;
  SBTLUNIT_WORK *pUnit;
  f32 enmy_area_r;
  f32 z;
  f32 w;
  f32 hit_area_r;
  f32 x;
  f32 y;
  f32 v20;
  f32 v21;
  sdfVector4_t vector2;
  f32 v24;
  f32 v25;
  sdfVector4_t v26;

  if (!mode || GetPercentage() >= 0x5Bu)
  {
    for (i = 0; ; ++i)
    {
      UnitMng = wk->UnitMng;
      number = UnitMng->number;
      v10 = i < number;
      if (i >= number)
        return v10;
      pUnit = UnitMng->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if (wk->ListID == pUnit->ListID)
        continue;
      if (!sBtlCheckExist(pUnit))
        continue;
      if ((pUnit->side & 7) != 0 && (((u8)pUnit->side ^ (u8)wk->side) & 7) != 0)
      {
        enmy_area_r = wk->actaiwk->enmy_area_r;
        v26.x = wk->pos.x;
        v26.y = wk->pos.y;
        z = wk->pos.z;
        w = wk->pos.w;
        hit_area_r = pUnit->actaiwk->hit_area_r;
        x = pUnit->pos.x;
        y = pUnit->pos.y;
        v21 = pUnit->pos.z;
        v20 = pUnit->pos.w;
        v24 = wk->pos.y;
        v25 = wk->pos.x;
        v26.y = v24;
        v26.x = v25;
        v26.z = z;
        v26.w = w;
        *(u64 *)&vector2.z = __PAIR64__(LODWORD(v20), LODWORD(v21));
        *(u64 *)&vector2.x = __PAIR64__(LODWORD(y), LODWORD(x));
        if (sBtlCheckCrossCircle(v26, enmy_area_r, vector2, hit_area_r))
          return v10;
      }
    }
  }
  return 0;
}

// 0x1db77a0
bool sBtlSetSearchEnemyMode(SBTLUNIT_WORK *wk, s32 targetid) {
  SBTLACTAI_WORK *actaiwk;

  wk->actaiwk->searchflg = 1;
  sBtlSetGroupAction(wk, targetid, 0xCu, 0);
  actaiwk = wk->actaiwk;
  actaiwk->datamode = 0;
  actaiwk->dataflg = 0;
  *(u64 *)actaiwk->data_p = 0;
  return 1;
}

// 0x1db6dd0
bool sBtlCheckSide(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock) {
  s32 side;
  s32 v4;
  bool result;
  s32 v6;
  bool v7;

  side = wk->side;
  if ((side & 7) == 0)
    return 1;
  v4 = wklock->side;
  result = 1;
  if ((v4 & 7) != 0)
  {
    v6 = ((u8)v4 | (u8)side) & 2;
    v7 = (((u8)v4 ^ (u8)side) & 7) != 0;
    return v6 || v7;
  }
  return result;
}

// 0x1daf760
bool sBtlGetEscapePoint(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, sdfVector4_t *pos, s32 area) {
  struct sdfVector4_t v10;
  _OWORD *p_x;
  f32 hit_area_r;
  f32 v17;
  struct sdfVector4_t v18;
  s32 v19;
  f32 *v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 z;
  f32 v27;
  f32 x;
  f32 y;
  _OWORD *v32;
  s32 v33;
  f32 v34;
  struct sdfVector4_t v35;
  sdfVector4_t *v36;
  f32 *v39;
  sdfVector4_t *v41;
  struct sdfVector4_t pos0;
  f32 pos0a;
  f32 v51;
  struct sdfVector4_t v52;
  struct sdfVector4_t v54;
  struct sdfVector4_t v55;
  __int128 v56;
  __int128 v57;
  __int128 v58;
  __int128 v59;
  sdfMatrix4_t v60;
  sdfMatrix4_t v61;
  sdfVector4_t v62;
  sdfVector4_t v63;
  sdfVector4_t v64;
  sdfVector4_t v65;
  sdfVector4_t v66;

  v51 = CorrectionMoveDistance(wk, (f32)area);
  v52 = wk->pos;
  vct_A = v52;
  vct_A.y = 0.0;
  v10 = wklock->pos;
  vct_A = v10;
  vct_A.y = 0.0;
  pos0 = vct_A;
  sub_1949280(0, 0.5235988);
  p_x = &vf00.x;
  v56 = p_x[4];
  v57 = p_x[5];
  v58 = p_x[6];
  v59 = p_x[7];
  vct_B = pos0;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  hit_area_r = wk->actaiwk->hit_area_r;
  v54 = vct_A;
  v17 = v51 + hit_area_r;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v17);
  v18 = wk->pos;
  vct_B = v18;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v41 = pos;
  v19 = 12;
  while (1)
  {
    v20 = &vf00.x;
    v22 = v20[6];
    v21 = v20[7];
    v24 = v20[4];
    v23 = v20[5];
    v25 = wk->actaiwk->hit_area_r;
    v63.x = v24;
    v63.y = v23;
    v63.z = v22;
    v63.w = v21;
    if (!sBtlCheckArea(wk, v63, v25))
      break;
LABEL_46:
    v32 = &vf00.x;
    v33 = (u8)byte_5755EF5;
    v32[4] = v56;
    v32[5] = v57;
    v32[6] = v58;
    v32[7] = v59;
    if (v33)
    {
      goto LABEL_51;
    }
    else
    {
LABEL_51:
      vct_A = v54;
      goto LABEL_52;
    }
    vct_A = v54;
LABEL_52:
    get_transpose(&v61, &mtx_A, 0);
    v65 = vct_A;
    v60 = v61;
    v62 = op_Multiply_60923920(&v60, v65, 0);
    vct_A = v62;
    v34 = wk->actaiwk->hit_area_r;
    v54 = vct_A;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v51 + v34);
    v35 = wk->pos;
    vct_B = v35;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    if (!--v19)
    {
      v55 = wk->pos;
      v36 = v41;
      vct_A = v55;
      goto LABEL_88;
    }
  }
  z = wk->pos.z;
  pos0a = wk->pos.w;
  v27 = wk->actaiwk->hit_area_r;
  x = wk->pos.x;
  y = wk->pos.y;
  v64.y = y;
  v64.z = z;
  v64.w = pos0a;
  v66.x = v24;
  v66.y = v23;
  v66.z = v22;
  v66.w = v21;
  v64.x = x;
  if (!sBtlCheckMapHit_Cross(v64, v66, v51 + v27))
    goto LABEL_46;
  v36 = v41;
  goto LABEL_126;
LABEL_127:
  v39 = &vf00.x;
  v39[4] = v24;
  v39[5] = v23;
  v39[6] = v22;
  v39[7] = v21;
LABEL_88:
  goto LABEL_89;
LABEL_126:
  goto LABEL_127;
LABEL_89:
  *v36 = vct_A;
  return 1;
}

// 0x1db7cf0
static f32 CorrectionMoveDistance(SBTLUNIT_WORK *wk, f32 distance) {
  s32 encountno;
  s64 v9;
  f32 z;
  f32 collider_center_x;
  f32 collider_center_y;
  f32 collider_center_z;
  SBATTLE_WORK *v14;
  f32 *p_x;
  _OWORD *v20;
  f32 hit_area_r;
  f32 v23;
  f32 *v24;
  s32 v25;
  f32 *v26;
  f32 x;
  f32 y;
  f32 v29;
  f32 w;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 LenXZ;
  _OWORD *v39;
  s32 v40;
  f32 v41;
  struct sdfVector4_t pos;
  f32 v43;
  struct sdfVector4_t v45;
  struct sdfVector4_t v50;
  __int128 v51;
  __int128 v52;
  __int128 v53;
  __int128 v54;
  f32 posZ;
  f32 posX;
  sdfMatrix4_t v57;
  sdfMatrix4_t v58;
  sdfVector4_t v59;
  sdfVector4_t v60;
  sdfVector4_t v61;
  sdfVector4_t v62;

  encountno = wk->encountno;
  if (encountno == 31)
    return distance;
  if (encountno == 51)
    return distance;
  posZ = -1.0;
  posX = -1.0;
  v9 = *(u64 *)&rightVector.x;
  z = rightVector.z;
  collider_center_x = 0.0;
  collider_center_y = 0.0;
  collider_center_z = 0.0;
  v14 = wk;
  if (v14->collider_type == 100)
  {
    v14 = wk;
    collider_center_x = v14->collider_center_x;
    collider_center_y = v14->collider_center_y;
    collider_center_z = v14->collider_center_z;
LABEL_18:
    goto LABEL_19;
  }
  else
  {
    goto LABEL_18;
  }
LABEL_19:
  p_x = &vf00.x;
  p_x[4] = collider_center_x;
  p_x[5] = collider_center_y;
  p_x[6] = collider_center_z;
  p_x[7] = 1.0;
  vct_A.y = 0.0;
  *(u64 *)&vct_A.x = v9;
  vct_A.z = z;
  vct_A.w = 1.0;
  vct_A.y = 0.0;
  v45 = vct_A;
  sub_1949280(0, 0.17453292);
  v20 = &vf00.x;
  v51 = v20[4];
  v52 = v20[5];
  v53 = v20[6];
  v54 = v20[7];
  vct_B = v45;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  hit_area_r = wk->actaiwk->hit_area_r;
  v50 = vct_A;
  v23 = hit_area_r + distance;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v23);
  v24 = &vf00.x;
  v24[8] = collider_center_x;
  v24[9] = collider_center_y;
  v24[10] = collider_center_z;
  v24[11] = 1.0;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
LABEL_50:
  v25 = 36;
  v43 = distance;
  while (1)
  {
    v26 = &vf00.x;
    x = wk->pos.x;
    y = wk->pos.y;
    v29 = wk->pos.z;
    w = wk->pos.w;
    v32 = v26[6];
    v31 = v26[7];
    v34 = v26[4];
    v33 = v26[5];
    v60.x = x;
    v60.y = y;
    v60.z = v29;
    v60.w = w;
    v62.x = v34;
    v62.y = v33;
    v62.z = v32;
    v62.w = v31;
    if (sBtlGetHitPos(v60, v62, &posX, &posZ))
    {
      v36 = posZ;
      v35 = posX;
      LenXZ = sBtlGetLenXZ(0.0, 0.0, v35, v36);
      if (LenXZ >= 0.0 && LenXZ < v43)
        v43 = LenXZ - wk->actaiwk->hit_area_r;
    }
    v39 = &vf00.x;
    v40 = (u8)byte_5755EF5;
    v39[4] = v51;
    v39[5] = v52;
    v39[6] = v53;
    v39[7] = v54;
    if (v40)
    {
      goto LABEL_65;
    }
    else
    {
LABEL_65:
      vct_A = v50;
      goto LABEL_66;
    }
    vct_A = v50;
LABEL_66:
    get_transpose(&v58, &mtx_A, 0);
    v61 = vct_A;
    v57 = v58;
    v59 = op_Multiply_60923920(&v57, v61, 0);
    vct_A = v59;
    v41 = wk->actaiwk->hit_area_r;
    v50 = vct_A;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v41 + distance);
    pos = wk->pos;
    vct_B = pos;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    if (!--v25)
      return v43;
  }
  goto LABEL_50;
}

// 0x1db0360
bool sBtlGetWarpPoint(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, sdfVector4_t *pos, s32 area) {
  struct sdfVector4_t v10;
  _OWORD *p_x;
  f32 *v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 hit_area_r;
  f32 v23;
  struct sdfVector4_t v24;
  s32 v26;
  s32 v27;
  _OWORD *v30;
  s32 v31;
  f32 *v32;
  f32 *v33;
  f32 v34;
  struct sdfVector4_t v35;
  s64 v38;
  s64 v39;
  s32 v40;
  f32 v42;
  f32 v43;
  f32 v44;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 v49;
  f32 v51;
  f32 v52;
  f32 v53;
  f32 v54;
  _OWORD *v56;
  s32 v57;
  f32 *v58;
  f32 *v60;
  f32 v61;
  struct sdfVector4_t v62;
  sdfVector4_t *v64;
  sdfVector4_t *v68;
  s64 v69;
  s64 v70;
  s64 v71;
  s64 v72;
  f32 v73;
  f32 v74;
  struct sdfVector4_t v75;
  f32 v78;
  struct sdfVector4_t v79;
  f32 v86;
  struct sdfVector4_t v89;
  __int128 v90;
  __int128 v91;
  __int128 v92;
  __int128 v93;
  sdfMatrix4_t v94;
  sdfMatrix4_t v95;
  sdfVector4_t v96;
  sdfVector4_t v97;
  sdfVector4_t v98;
  sdfVector4_t v99;
  sdfVector4_t v100;
  sdfVector4_t v101;
  sdfVector4_t v102;

  v79 = wk->pos;
  vct_A = v79;
  vct_A.y = 0.0;
  v10 = wklock->pos;
  vct_A = v10;
  vct_A.y = 0.0;
  v75 = vct_A;
  sub_1949280(0, 0.7853982);
  p_x = &vf00.x;
  v90 = p_x[4];
  v91 = p_x[5];
  v92 = p_x[6];
  v93 = p_x[7];
  vct_B = v75;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v16 = &vf00.x;
  v17 = area;
  v18 = v16[4];
  v19 = v16[5];
  v20 = v16[6];
  v21 = v16[7];
  hit_area_r = wk->actaiwk->hit_area_r;
  v23 = hit_area_r + v17;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v23);
  v24 = wk->pos;
  vct_B = v24;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v69 = *(u64 *)&vct_A.z;
  v71 = *(u64 *)&vct_A.x;
  v26 = sub_1905740(8, 0);
  v68 = pos;
  if (v26 >= 1)
  {
    v27 = v26;
    while (1)
    {
      v30 = &vf00.x;
      v31 = (u8)byte_5755EF5;
      v30[4] = v90;
      v30[5] = v91;
      v30[6] = v92;
      v30[7] = v93;
      if (v31)
      {
        goto LABEL_68;
      }
      else
      {
LABEL_68:
        v32 = &vf00.x;
        v32[4] = v18;
        v32[5] = v19;
        v32[6] = v20;
        v32[7] = v21;
        goto LABEL_69;
      }
      vct_A.x = v18;
      vct_A.y = v19;
      vct_A.z = v20;
      vct_A.w = v21;
LABEL_69:
      get_transpose(&v95, &mtx_A, 0);
      v99 = vct_A;
      v94 = v95;
      v96 = op_Multiply_60923920(&v94, v99, 0);
      vct_A = v96;
      v33 = &vf00.x;
      v18 = v33[4];
      v19 = v33[5];
      v20 = v33[6];
      v21 = v33[7];
      v34 = wk->actaiwk->hit_area_r;
      vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v34 + v17);
      v35 = wk->pos;
      vct_B = v35;
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      if (!--v27)
      {
        v38 = *(u64 *)&vct_A.x;
        v39 = *(u64 *)&vct_A.z;
        goto LABEL_108;
      }
    }
  }
  v39 = v69;
  v38 = v71;
LABEL_108:
  v40 = 8;
  while (1)
  {
    v73 = v21;
    v74 = v20;
    v78 = v19;
    v42 = wk->actaiwk->hit_area_r;
    v86 = v18;
    v70 = v39;
    v72 = v38;
    v39 = v70;
    v38 = v72;
    v43 = *((f32 *)&v38 + 1);
    v44 = *((f32 *)&v39 + 1);
    *(u64 *)&v98.x = v38;
    *(u64 *)&v98.z = v39;
    if (!sBtlCheckArea(wk, v98, v42))
      break;
LABEL_117:
    v51 = v86;
    v53 = v74;
    v52 = v78;
    v54 = v73;
    v56 = &vf00.x;
    v57 = (u8)byte_5755EF5;
    v56[4] = v90;
    v56[5] = v91;
    v56[6] = v92;
    v56[7] = v93;
    if (v57)
    {
      goto LABEL_122;
    }
    else
    {
LABEL_122:
      v58 = &vf00.x;
      v58[4] = v51;
      v58[5] = v52;
      v58[6] = v53;
      v58[7] = v54;
      goto LABEL_123;
    }
    vct_A.x = v51;
    vct_A.y = v52;
    vct_A.z = v53;
    vct_A.w = v54;
LABEL_123:
    get_transpose(&v95, &mtx_A, 0);
    v101 = vct_A;
    v94 = v95;
    v97 = op_Multiply_60923920(&v94, v101, 0);
    vct_A = v97;
    v60 = &vf00.x;
    v18 = v60[4];
    v19 = v60[5];
    v20 = v60[6];
    v21 = v60[7];
    v61 = wk->actaiwk->hit_area_r;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v61 + v17);
    v62 = wk->pos;
    vct_B = v62;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    --v40;
    v38 = *(u64 *)&vct_A.x;
    v39 = *(u64 *)&vct_A.z;
    if (!v40)
    {
      v89 = wk->pos;
      v64 = v68;
      vct_A = v89;
LABEL_159:
      goto LABEL_160;
    }
  }
  x = wk->pos.x;
  y = wk->pos.y;
  z = wk->pos.z;
  w = wk->pos.w;
  v49 = wk->actaiwk->hit_area_r;
  v100.y = y;
  v100.z = z;
  v100.w = w;
  v100.x = x;
  v102.y = v43;
  v102.w = v44;
  LODWORD(v102.z) = v70;
  LODWORD(v102.x) = v72;
  if (!sBtlCheckMapHit_Cross(v100, v102, v49 + v17))
    goto LABEL_117;
  v64 = v68;
  *(u64 *)&vct_A.x = v72;
  *(u64 *)&vct_A.z = v70;
  goto LABEL_159;
LABEL_160:
  *v64 = vct_A;
  return 1;
}

// 0x1db13d0
bool sBtlGetFukinPoint(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, sdfVector4_t *pos, s32 area) {
  struct sdfVector4_t v10;
  _OWORD *p_x;
  f32 *v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 hit_area_r;
  f32 v23;
  struct sdfVector4_t v24;
  s32 v26;
  s32 v27;
  _OWORD *v30;
  s32 v31;
  f32 *v32;
  f32 *v33;
  f32 v34;
  struct sdfVector4_t v35;
  s64 v38;
  s64 v39;
  s32 v40;
  f32 v42;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 x;
  f32 y;
  f32 v48;
  f32 z;
  f32 w;
  f32 v52;
  f32 v53;
  f32 v54;
  f32 v55;
  f32 v56;
  f32 v57;
  f32 v58;
  f32 v59;
  f32 v60;
  f32 v61;
  f32 v63;
  f32 v64;
  f32 v65;
  _OWORD *v67;
  s32 v68;
  f32 *v69;
  f32 *v71;
  f32 v72;
  struct sdfVector4_t v73;
  sdfVector4_t *v75;
  f32 pos0;
  f32 v80;
  f32 v81;
  f32 v82;
  f32 v83;
  struct sdfVector4_t v84;
  s64 v85;
  s64 v88;
  struct sdfVector4_t v89;
  s64 v91;
  s64 v97;
  struct sdfVector4_t v100;
  __int128 v101;
  __int128 v102;
  __int128 v103;
  __int128 v104;
  sdfMatrix4_t v105;
  sdfMatrix4_t v106;
  sdfVector4_t v107;
  sdfVector4_t v108;
  sdfVector4_t v109;
  sdfVector4_t v110;
  sdfVector4_t v111;
  sdfVector4_t v112;
  sdfVector4_t v113;
  sdfVector4_t v114;
  sdfVector4_t v115;
  sdfVector4_t v116;

  v89 = wk->pos;
  vct_A = v89;
  vct_A.y = 0.0;
  v10 = wklock->pos;
  vct_A = v10;
  vct_A.y = 0.0;
  v84 = vct_A;
  sub_1949280(0, 0.7853982);
  p_x = &vf00.x;
  v101 = p_x[4];
  v102 = p_x[5];
  v103 = p_x[6];
  v104 = p_x[7];
  vct_B = v84;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v16 = &vf00.x;
  v17 = area;
  v19 = v16[4];
  v18 = v16[5];
  v20 = v16[6];
  v21 = v16[7];
  hit_area_r = wk->actaiwk->hit_area_r;
  v23 = hit_area_r + v17;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v23);
  v24 = wk->pos;
  vct_B = v24;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v85 = *(u64 *)&vct_A.z;
  v91 = *(u64 *)&vct_A.x;
  v26 = sub_1905740(8, 0);
  if (v26 >= 1)
  {
    v27 = v26;
    while (1)
    {
      v30 = &vf00.x;
      v31 = (u8)byte_5755EF5;
      v30[4] = v101;
      v30[5] = v102;
      v30[6] = v103;
      v30[7] = v104;
      if (v31)
      {
        goto LABEL_43;
      }
      else
      {
LABEL_43:
        v32 = &vf00.x;
        v32[4] = v19;
        v32[5] = v18;
        v32[6] = v20;
        v32[7] = v21;
        goto LABEL_44;
      }
      vct_A.x = v19;
      vct_A.y = v18;
      vct_A.z = v20;
      vct_A.w = v21;
LABEL_44:
      get_transpose(&v106, &mtx_A, 0);
      v110 = vct_A;
      v105 = v106;
      v107 = op_Multiply_60923920(&v105, v110, 0);
      vct_A = v107;
      v33 = &vf00.x;
      v19 = v33[4];
      v18 = v33[5];
      v20 = v33[6];
      v21 = v33[7];
      v34 = wk->actaiwk->hit_area_r;
      vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v34 + v17);
      v35 = wk->pos;
      vct_B = v35;
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      if (!--v27)
      {
        v38 = *(u64 *)&vct_A.x;
        v39 = *(u64 *)&vct_A.z;
        goto LABEL_107;
      }
    }
  }
  v39 = v85;
  v38 = v91;
LABEL_107:
  v40 = 8;
  while (1)
  {
    v81 = v21;
    v82 = v20;
    v83 = v18;
    v42 = wk->actaiwk->hit_area_r;
    v88 = v39;
    v97 = v38;
    v39 = v88;
    v38 = v97;
    v43 = *((f32 *)&v38 + 1);
    v44 = *((f32 *)&v39 + 1);
    *(u64 *)&v109.x = v38;
    *(u64 *)&v109.z = v39;
    if (!sBtlCheckArea(wk, v109, v42 + 30.0))
      break;
LABEL_123:
    v64 = v82;
    v63 = v83;
    v65 = v81;
    v67 = &vf00.x;
    v68 = (u8)byte_5755EF5;
    v67[4] = v101;
    v67[5] = v102;
    v67[6] = v103;
    v67[7] = v104;
    if (v68)
    {
      goto LABEL_128;
    }
    else
    {
LABEL_128:
      v69 = &vf00.x;
      v69[4] = v19;
      v69[5] = v63;
      v69[6] = v64;
      v69[7] = v65;
      goto LABEL_129;
    }
    vct_A.x = v19;
    vct_A.y = v63;
    vct_A.z = v64;
    vct_A.w = v65;
LABEL_129:
    get_transpose(&v106, &mtx_A, 0);
    v114 = vct_A;
    v105 = v106;
    v108 = op_Multiply_60923920(&v105, v114, 0);
    vct_A = v108;
    v71 = &vf00.x;
    v19 = v71[4];
    v18 = v71[5];
    v20 = v71[6];
    v21 = v71[7];
    v72 = wk->actaiwk->hit_area_r;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v72 + v17);
    v73 = wk->pos;
    vct_B = v73;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    --v40;
    v38 = *(u64 *)&vct_A.x;
    v39 = *(u64 *)&vct_A.z;
    if (!v40)
    {
      v100 = wk->pos;
      v75 = pos;
      vct_A = v100;
LABEL_168:
      goto LABEL_169;
    }
  }
  v80 = v19;
  v45 = v17;
  x = wk->pos.x;
  y = wk->pos.y;
  v48 = wk->actaiwk->hit_area_r;
  z = wk->pos.z;
  w = wk->pos.w;
  v111.y = y;
  v111.z = z;
  v111.w = w;
  v111.x = x;
  v115.y = v43;
  v115.w = v44;
  v17 = v45;
  LODWORD(v115.z) = v88;
  LODWORD(v115.x) = v97;
  v19 = v80;
  if (!sBtlCheckMapHit_Cross(v111, v115, v48 + v45))
    goto LABEL_123;
  v52 = wk->pos.z;
  v54 = wk->pos.x;
  v53 = wk->pos.y;
  v55 = wk->actaiwk->hit_area_r;
  v112.w = 1.0;
  v56 = v54 + (f32)((f32)(*(f32 *)&v97 - v54) * 0.5);
  v112.y = v53;
  v57 = v52 + (f32)((f32)(*(f32 *)&v88 - v52) * 0.5);
  v112.x = v56;
  v112.z = v57;
  if (sBtlCheckArea(wk, v112, v55 + 30.0))
    goto LABEL_123;
  v58 = wk->pos.z;
  pos0 = wk->pos.w;
  v59 = wk->actaiwk->hit_area_r;
  v60 = wk->pos.x;
  v61 = wk->pos.y;
  v113.w = pos0;
  v113.y = v61;
  v113.z = v58;
  v116.x = v56;
  v116.y = v53;
  v116.z = v57;
  v113.x = v60;
  v116.w = 1.0;
  v17 = v45;
  v19 = v80;
  if (!sBtlCheckMapHit_Cross(v113, v116, v59 + v45))
    goto LABEL_123;
  v75 = pos;
  *(u64 *)&vct_A.x = v97;
  *(u64 *)&vct_A.z = v88;
  goto LABEL_168;
LABEL_169:
  *v75 = vct_A;
  return 1;
}

// 0x1da9cf0
sdfVector4_t sBtlGetFixFormationPos(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, SBTLUNIT_WORK *wkPc, const sdfVector4_t *tgtPos, s32 area) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v13;
  f32 hit_area_r;
  f32 v16;
  bool v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 dis;
  sdfVector4_t *p_pos;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 *p_w;
  f32 v30;
  f32 v31;
  f32 PosToDir;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  SBTLACTAI_WORK *actaiwk;
  f32 v42;
  f32 v43;
  f32 *v44;
  s64 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 v50;
  s32 devilid;
  f32 v52;
  f32 v53;
  f32 v54;
  f32 v55;
  s64 v56;
  f32 v57;
  f32 v58;
  f32 v59;
  f32 v60;
  f32 v61;
  f32 v62;
  f32 v63;
  sdfVector4_t *v68;
  f32 v69;
  f32 v70;
  sdfVector4_t pos0;
  s64 v72;
  sdfVector4_t v73;
  sdfVector4_t v74;
  sdfVector4_t v75;
  sdfVector4_t v76;
  sdfVector4_t v77;
  sdfVector4_t result;
  sdfVector4_t v79;
  sdfVector4_t v80;

  w = tgtPos->w;
  z = tgtPos->z;
  y = tgtPos->y;
  x = tgtPos->x;
  v13 = area;
  pos0.y = (f32)area;
  hit_area_r = wk->actaiwk->hit_area_r;
  *(u64 *)&pos0.z = 0;
  v72 = 0;
  v13 = area;
  v16 = hit_area_r + v13;
  v73.x = x;
  v73.y = y;
  v73.z = z;
  v73.w = w;
  v17 = sBtlCheckArea_SubCylinder(wk, v73, v16);
  if (!v17)
  {
    v18 = wk->pos.y;
    v19 = wk->pos.z;
    v20 = wk->pos.w;
    pos0.x = wk->pos.x;
    v21 = wk->actaiwk->hit_area_r;
    dis = v21 + pos0.y;
    v74.x = pos0.x;
    v74.y = v18;
    v74.z = v19;
    v74.w = v20;
    v79.x = x;
    v79.y = y;
    v79.z = z;
    v79.w = w;
    if (sBtlCheckMapHit_Cross(v74, v79, dis))
      goto LABEL_51;
    if (wk->NakamaAtkFormationUse)
    {
      x = wk->NakamaAtkFormationPos.x;
      z = wk->NakamaAtkFormationPos.z;
    }
    goto LABEL_12;
  }
LABEL_12:
  p_pos = &wk->pos;
  v25 = wk->pos.x;
  v26 = wklock->pos.x;
  v27 = wklock->pos.z;
  v28 = wk->pos.z;
  if (sBtlGetLenXZ(v25, v28, x, z) >= 0.1)
  {
    v30 = wk->pos.x;
    v31 = wk->pos.z;
    v68 = &wk->pos;
    PosToDir = sBtlGetPosToDir(v30, v31, x, z);
  }
  else
  {
    if (v17)
    {
      y = wk->pos.y;
      z = wk->pos.z;
      p_w = &wk->pos.w;
      goto LABEL_50;
    }
    v33 = wk->rot.x;
    v34 = wk->rot.y;
    v35 = wk->rot.z;
    v36 = wk->rot.w;
    v75.x = v33;
    v75.y = v34;
    v75.z = v35;
    v75.w = v36;
    v68 = &wk->pos;
    PosToDir = sBtlGetRotToDir(v75);
  }
  v37 = PosToDir;
  v38 = wk->pos.x;
  v39 = wk->pos.z;
  v40 = sBtlGetPosToDir(v38, v39, v26, v27);
  sBtlGetAtoB_LR(v37, v40);
  actaiwk = wk->actaiwk;
  pos0.z = 0.0;
  v42 = wk->pos.y;
  v72 = 0;
  pos0.w = v42;
  v43 = actaiwk->hit_area_r;
  v44 = NewSpecific(f32, 0x10u);
  InitializeArray_55364416(v44, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__13CE034068FFEC27C643F553DE5DB44D6B6E2AD4730AB428CDB1509CA89E1E81, 0);
  if (*(s32 *)((char *)v44 + 24) < 1)
  {
LABEL_48:
    y = wk->pos.y;
    z = wk->pos.z;
    p_w = &wk->pos.w;
    p_pos = v68;
    goto LABEL_50;
  }
  v45 = 0;
  v46 = v43 + pos0.y;
  v69 = v43 + pos0.y;
  v70 = v37;
  while (1)
  {
    v47 = wk->pos.x;
    v48 = wk->pos.z;
    v49 = *(f32 *)((s64)&v44[0] + 4 * v45);
    sBtlGetMoveXZ(v47, v48, v37 + v49, v46, &pos0.z, &v72);
    v50 = *(f32 *)&v72;
    devilid = wklock->para->devilid;
    v52 = wk->actaiwk->hit_area_r;
    if (((u32)(devilid - 258) < 3 || (devilid & 0xFFFFFFFC) == 0x138) && *(f32 *)&v72 > (f32)(900.0 - v52))
    {
      v50 = 900.0 - v52;
      *(f32 *)&v72 = 900.0 - v52;
    }
    v53 = pos0.z;
    v54 = pos0.w;
    v55 = *((f32 *)&v72 + 1);
    v77.x = v53;
    v77.y = v54;
    v77.z = v50;
    v77.w = v55;
    if (!sBtlCheckArea_SubCylinder(wk, v77, v52))
    {
      v56 = v72;
      LODWORD(pos0.x) = v72;
      v57 = wk->actaiwk->hit_area_r;
      v58 = wk->pos.x;
      v59 = wk->pos.y;
      v60 = wk->pos.z;
      v61 = wk->pos.w;
      v62 = pos0.z;
      v63 = pos0.w;
      v80.z = pos0.x;
      v76.y = v59;
      v76.z = v60;
      v76.w = v61;
      v80.x = v62;
      v80.y = v63;
      v76.x = v58;
      v80.w = *((f32 *)&v56 + 1);
      v46 = v69;
      v37 = v70;
      if (sBtlCheckMapHit_Cross(v76, v80, v57 + *(f32 *)&v56))
        break;
    }
    if (++v45 >= *(s32 *)((char *)v44 + 24))
      goto LABEL_48;
  }
  y = pos0.w;
  z = *(f32 *)&v72;
  p_pos = &pos0.z;
  p_w = (f32 *)&v72 + 1;
LABEL_50:
  x = p_pos->x;
  w = *p_w;
LABEL_51:
  result.x = x;
  result.y = y;
  result.z = z;
  result.w = w;
  return result;
}

// 0x1daa270
bool sBtlGetNWarpPoint(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, const sdfVector4_t *tgtpos, sdfVector4_t *pos, s32 area) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 hit_area_r;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 dis;
  f32 *p_x;
  f32 v22;
  f32 v23;
  f32 *v25;
  _OWORD *v29;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 *v34;
  u32 v35;
  f32 *v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 v41;
  f32 v42;
  f32 v43;
  f32 v44;
  f32 v45;
  _OWORD *v48;
  s32 v49;
  f32 v50;
  f32 v51;
  f32 *v52;
  sdfVector4_t *v53;
  f32 *v56;
  sdfVector4_t *v59;
  struct sdfVector4_t v60;
  f32 v61;
  f32 v63;
  f32 v64;
  struct sdfVector4_t pos0;
  f32 pos0a;
  f32 v68;
  f32 v69;
  struct sdfVector4_t v71;
  struct sdfVector4_t v72;
  __int128 v73;
  __int128 v74;
  __int128 v75;
  __int128 v76;
  sdfMatrix4_t v77;
  sdfMatrix4_t v78;
  sdfVector4_t v79;
  sdfVector4_t v80;
  sdfVector4_t v81;
  sdfVector4_t v82;
  sdfVector4_t v83;
  sdfVector4_t v84;
  sdfVector4_t v85;
  sdfVector4_t v86;

  w = tgtpos->w;
  z = tgtpos->z;
  y = tgtpos->y;
  x = tgtpos->x;
  hit_area_r = wk->actaiwk->hit_area_r;
  v80.y = y;
  v80.z = z;
  v80.w = w;
  v68 = area;
  v80.x = x;
  if (!sBtlCheckArea(wk, v80, hit_area_r))
  {
    v69 = w;
    v14 = wk->actaiwk->hit_area_r;
    v15 = wk->pos.x;
    v16 = wk->pos.y;
    v17 = wk->pos.z;
    v18 = wk->pos.w;
    dis = v14 + v68;
    v81.x = v15;
    v81.y = v16;
    v81.z = v17;
    v81.w = v18;
    v85.x = x;
    v85.y = y;
    v85.z = z;
    v85.w = v69;
    if (sBtlCheckMapHit_Cross(v81, v85, dis))
    {
      p_x = &vf00.x;
      p_x[4] = x;
      p_x[5] = y;
      p_x[6] = z;
      p_x[7] = v69;
      *pos = vct_A;
      return 1;
    }
  }
  pos0 = wk->pos;
  v22 = wklock->pos.x;
  v23 = wklock->pos.z;
  vct_A = pos0;
  vct_A.y = 0.0;
  v25 = &vf00.x;
  v25[4] = v22;
  v25[6] = v23;
  v25[5] = pos0.y;
  v25[7] = 1.0;
  vct_A.y = 0.0;
  v60 = vct_A;
  sub_1949280(0, 0.41887903);
  v29 = &vf00.x;
  v73 = v29[4];
  v74 = v29[5];
  v75 = v29[6];
  v76 = v29[7];
  vct_B = v60;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v71 = vct_A;
  v31 = wk->actaiwk->hit_area_r + wklock->actaiwk->hit_area_r;
  v32 = v31 + v68;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v32);
  v33 = pos0.y;
  v34 = &vf00.x;
  v34[8] = v22;
  v34[9] = v33;
  v34[10] = v23;
  v34[11] = 1.0;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v59 = pos;
  v35 = 0;
  v63 = v23;
  v64 = v22;
  v61 = v33;
  while (1)
  {
    v36 = &vf00.x;
    v38 = v36[6];
    v37 = v36[7];
    v40 = v36[4];
    v39 = v36[5];
    v41 = wk->actaiwk->hit_area_r;
    v82.x = v40;
    v82.y = v39;
    v82.z = v38;
    v82.w = v37;
    if (!sBtlCheckArea(wk, v82, v41))
      break;
LABEL_59:
    v48 = &vf00.x;
    v49 = (u8)byte_5755EF5;
    v48[4] = v73;
    v48[5] = v74;
    v48[6] = v75;
    v48[7] = v76;
    if (v49)
    {
      goto LABEL_64;
    }
    else
    {
LABEL_64:
      vct_A = v71;
      goto LABEL_65;
    }
    vct_A = v71;
LABEL_65:
    get_transpose(&v78, &mtx_A, 0);
    v84 = vct_A;
    v77 = v78;
    v79 = op_Multiply_60923920(&v77, v84, 0);
    vct_A = v79;
    v50 = wk->actaiwk->hit_area_r;
    v71 = vct_A;
    v51 = wklock->actaiwk->hit_area_r;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, (f32)(v50 + v51) + v68);
    v52 = &vf00.x;
    v52[8] = v22;
    v52[9] = v33;
    v52[10] = v23;
    v52[11] = 1.0;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    if (++v35 == 15)
      goto LABEL_130;
  }
  v42 = wk->pos.y;
  pos0a = wk->pos.x;
  v43 = wk->actaiwk->hit_area_r;
  v44 = wk->pos.z;
  v45 = wk->pos.w;
  v83.y = v42;
  v83.z = v44;
  v83.w = v45;
  v86.x = v40;
  v86.y = v39;
  v86.z = v38;
  v86.w = v37;
  v83.x = pos0a;
  v23 = v63;
  v22 = v64;
  v33 = v61;
  if (!sBtlCheckMapHit_Cross(v83, v86, v43 + v68))
    goto LABEL_59;
  if (v35 <= 7)
  {
    v53 = v59;
    v56 = &vf00.x;
    v56[4] = v40;
    v56[5] = v39;
    v56[6] = v38;
    v56[7] = v37;
    goto LABEL_134;
  }
LABEL_130:
  v72 = wk->pos;
  v53 = v59;
  goto LABEL_132;
LABEL_133:
  vct_A = v72;
  goto LABEL_134;
LABEL_132:
  goto LABEL_133;
LABEL_134:
  *v53 = vct_A;
  return 1;
}

// 0x1db8910
static void MapOverHD(SBTLUNIT_WORK *wk, sdfVector4_t *pos) {
  ;
}

// 0x1db1270
bool sBtlGetSenkaiPoint(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, sdfVector4_t *pos, s32 area) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  sdfVector4_t v14;

  x = wk->pos.x;
  y = wk->pos.y;
  z = wk->pos.z;
  w = wk->pos.w;
  v14.x = x;
  v14.y = y;
  v14.z = z;
  v14.w = w;
  GetSenkaiPointSub(wk, v14, wklock, pos, area);
  return 1;
}

// 0x1db8920
static bool GetSenkaiPointSub(SBTLUNIT_WORK *wk, const sdfVector4_t *center_pos, SBTLUNIT_WORK *wklock, sdfVector4_t *pos, s32 area) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  struct sdfVector4_t v15;
  u32 Percentage;
  _OWORD *p_x;
  _OWORD *v23;
  s32 v24;
  f32 v26;
  f32 hit_area_r;
  f32 v28;
  f32 *v29;
  char v30;
  char v31;
  f32 *v32;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 v44;
  struct sdfVector4_t v45;
  sdfVector4_t *v46;
  f32 *v50;
  sdfVector4_t *v52;
  f32 v53;
  struct sdfVector4_t v54;
  f32 v55;
  struct sdfVector4_t v61;
  struct sdfVector4_t v63;
  struct sdfVector4_t v64;
  struct sdfVector4_t v65;
  __int128 v66;
  __int128 v67;
  __int128 v68;
  __int128 v69;
  sdfMatrix4_t v70;
  sdfMatrix4_t v71;
  sdfVector4_t v72;
  sdfVector4_t v73;
  sdfVector4_t v74;
  sdfVector4_t v75;
  sdfVector4_t v76;
  sdfVector4_t v77;
  sdfVector4_t v78;

  w = center_pos->w;
  z = center_pos->z;
  y = center_pos->y;
  x = center_pos->x;
  v61 = wk->pos;
  vct_A = v61;
  vct_A.y = 0.0;
  v15 = wklock->pos;
  vct_A = v15;
  vct_A.y = 0.0;
  v54 = vct_A;
  Percentage = GetPercentage();
  if (Percentage <= 0x31)
  {
    sub_1949280(0, 1.5707964);
  }
  else
  {
    sub_1949280(0, -1.5707964);
  }
  p_x = &vf00.x;
  v66 = p_x[4];
  v67 = p_x[5];
  v68 = p_x[6];
  v69 = p_x[7];
  vct_B = v54;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v63 = vct_A;
  v23 = &vf00.x;
  v24 = (u8)byte_5755EF5;
  v23[4] = v66;
  v23[5] = v67;
  v23[6] = v68;
  v23[7] = v69;
  if (v24)
  {
    goto LABEL_40;
  }
  else
  {
LABEL_40:
    vct_A = v63;
    goto LABEL_41;
  }
  vct_A = v63;
LABEL_41:
  get_transpose(&v71, &mtx_A, 0);
  v74 = vct_A;
  v70 = v71;
  v72 = op_Multiply_60923920(&v70, v74, 0);
  vct_A = v72;
  v26 = area;
  hit_area_r = wk->actaiwk->hit_area_r;
  v64 = vct_A;
  v28 = hit_area_r + v26;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v28);
  v29 = &vf00.x;
  v29[8] = x;
  v29[9] = y;
  v29[10] = z;
  v29[11] = w;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v52 = pos;
  v30 = 1;
  while (1)
  {
    v31 = v30;
    v32 = &vf00.x;
    v34 = v32[6];
    v33 = v32[7];
    v36 = v32[4];
    v35 = v32[5];
    v37 = wk->actaiwk->hit_area_r;
    v75.x = v36;
    v75.y = v35;
    v75.z = v34;
    v75.w = v33;
    if (!sBtlCheckArea(wk, v75, v37))
      break;
LABEL_61:
    sub_1949280(0, 3.1415927);
    vct_A = v64;
    get_transpose(&v71, &mtx_A, 0);
    v77 = vct_A;
    v70 = v71;
    v73 = op_Multiply_60923920(&v70, v77, 0);
    vct_A = v73;
    v44 = wk->actaiwk->hit_area_r;
    v64 = vct_A;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v44 + v26);
    v45 = wk->pos;
    vct_B = v45;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v30 = 0;
    if ((v31 & 1) == 0)
    {
      v65 = wk->pos;
      v46 = v52;
      vct_A = v65;
      goto LABEL_101;
    }
  }
  v38 = wk->pos.z;
  v53 = wk->pos.y;
  v55 = wk->pos.x;
  v39 = wk->actaiwk->hit_area_r;
  v40 = wk->pos.w;
  v76.z = v38;
  v76.w = v40;
  v78.x = v36;
  v76.y = v53;
  v76.x = v55;
  v78.y = v35;
  v78.z = v34;
  v78.w = v33;
  if (!sBtlCheckMapHit_Cross(v76, v78, v39 + v26))
    goto LABEL_61;
  v46 = v52;
  goto LABEL_147;
LABEL_148:
  v50 = &vf00.x;
  v50[4] = v36;
  v50[5] = v35;
  v50[6] = v34;
  v50[7] = v33;
LABEL_101:
  goto LABEL_102;
LABEL_147:
  goto LABEL_148;
LABEL_102:
  *v46 = vct_A;
  return 1;
}

// 0x1db1320
bool sBtlGetShinSenkaiPoint(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, sdfVector4_t *pos, s32 area) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  sdfVector4_t v13;

  x = wklock->pos.x;
  y = wklock->pos.y;
  z = wklock->pos.z;
  w = wklock->pos.w;
  v13.x = x;
  v13.y = y;
  v13.z = z;
  v13.w = w;
  GetSenkaiPointSub(wk, v13, wklock, pos, 500);
  return 1;
}

// 0x1db96e0
void sBtlSetAAIData(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;

  actaiwk = wk->actaiwk;
  actaiwk->mode = 14;
  actaiwk->frame = 0;
  actaiwk->stat = 2;
}

// 0x1db87f0
bool sBtlCheckMapHit(const sdfVector4_t *pos0, const sdfVector4_t *ppos, f32 dis) {
  f32 v4;
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v22;

  v4 = dis;
  w = ppos->w;
  z = ppos->z;
  y = ppos->y;
  x = ppos->x;
  v9 = pos0->w;
  v10 = pos0->z;
  v11 = pos0->y;
  v12 = pos0->x;
  v4 = dis;
  pos0->x = v12;
  pos0->y = v11;
  pos0->z = v10;
  pos0->w = v9;
  ppos->x = x;
  ppos->y = y;
  ppos->z = z;
  ppos->w = w;
  v13 = ppos->w;
  v14 = ppos->z;
  v22 = v4;
  v15 = ppos->y;
  v16 = ppos->x;
  v17 = pos0->w;
  v18 = pos0->z;
  v19 = pos0->y;
  v20 = pos0->x;
  v4 = v22;
  pos0->x = v20;
  pos0->y = v19;
  pos0->z = v18;
  pos0->w = v17;
  ppos->x = v16;
  ppos->y = v15;
  ppos->z = v14;
  ppos->w = v13;
  return sBtlCheckMapHit_Cross(pos0, ppos, v4);
}

// 0x1db3230
bool sBtlCheckResetDataflg(PEAICODE code) {
  return code != 22;
}

// 0x1db9700
bool sBtlCheckUserUnit(SBTLUNIT_WORK *wk) {
  s32 v4;

  if (wk->battlemode == 3)
    v4 = 1;
  else
    v4 = 128;
  return (wk->side & v4) != 0;
}

// 0x1da9870
void sBtlSetNoMP(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  SBTLSM_LISTWORK *sysmsgList;
  s32 use_skillid;
  SBTLACTAI_WORK *v7;

  actaiwk = wk->actaiwk;
  if (!actaiwk->nonempflg && (wk->side & 2) != 0)
  {
    actaiwk->nonempflg = 1;
    sysmsgList = wk->sysmsgList;
    use_skillid = wk->actwk->use_skillid;
    sBtlCreateSM(sysmsgList, wk, 2, use_skillid, 0, 120);
    v7 = wk->actaiwk;
    v7->datamode = 0;
    v7->dataflg = 0;
    *(u64 *)v7->data_p = 0;
  }
}

// 0x1db9790
bool sBtlCheckPadMode(SBTLUNIT_WORK *wk) {
  if (wk->battlemode == 3)
    return 1;
  return (wk->vstatus & 0x4000) == 0;
}

// 0x1da9c00
void sBtlResetNakamaAction(SBTLUNIT_WORK *wk) {
  SBTLAI_WORK *aiwk;
  u32 status;
  SBTLPNL_SETDATA *data;
  s32 SmnNo;

  aiwk = wk->aiwk;
  status = aiwk->status;
  if ((status & 1) == 0)
    return;
  aiwk->meirei_nobk = 7;
  aiwk->status = status & 0xFFFFFFF6;
  data = wk->panelwk->data;
  SmnNo = sBtlGetSmnNo(wk);
  wk->NakamaAtkFormationUse = 0;
  data[SmnNo]->meirei_no = 7;
  wk->aiwk->status &= ~0x10u;
}

// 0x1db6e20
bool sBtlCheckHITCheck_Char(SBTLUNIT_WORK *wk) {
  s32 devilid;

  devilid = wk->para->devilid;
  return devilid != 292 && (u32)(devilid - 297) < 0xFFFFFFFD;
}

// 0x1db9850
bool sBtlEnemyAI(SBTLUNIT_WORK *wk) {
  bool result;
  SBATTLE_WORK *v6;
  u32 status2;
  sdatUnitWork_t *para;
  s32 devilid;
  SBTLACTAI_WORK *actaiwk;
  s32 mode;
  s32 stat;
  sBtlActAI_EAIInit_FuncDelegate v15;
  SBTLACTAI_WORK *v16;
  s32 *p_frame;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  long f64 v23;
  long f64 v24;
  sBtlActAI_EAIProc_FuncDelegate v26;

  if (kaiwa_btlendflg)
    return 0;
  v6 = wk;
  if ((v6->status & 0x1000000) != 0)
    return 0;
  status2 = v6->status2;
  if ((status2 & 0x80000) != 0)
    return 0;
  if ((wk->status2 & 0x40000000) != 0)
    return 0;
  para = wk->para;
  devilid = (u16)para->devilid;
  if ((devilid == 302 || devilid == 263) && para->now->hp < 1)
    return 0;
  sBtlCheckEquation(wk);
  actaiwk = wk->actaiwk;
  mode = actaiwk->mode;
  if (mode <= 13)
  {
    stat = actaiwk->stat;
    if (stat == 2)
    {
      p_frame = &actaiwk->frame;
      ++actaiwk->frame;
      LimitRange(p_frame, 0, 0x7FFF);
      x = wk->mv_spdbk.x;
      y = wk->mv_spdbk.y;
      z = wk->mv_spdbk.z;
      w = wk->mv_spdbk.w;
      *(__n128 *)&v23 = sub_1B332C0(0, x, y, z, w);
      *(__n128 *)&v24 = sub_1B335A0(&wk->mv_spd, 0, v23);
      v26 = EAIProc_Func[wk->actaiwk->mode];
      (v26->invoke_impl)(v26->method_code, wk, v26->v24);
    }
    else if (stat == 1)
    {
      mode = wk->actaiwk->mode;
      v15 = EAIInit_Func[mode];
      if (((v15->invoke_impl)(v15->method_code, wk, v15->method) & 1) != 0)
      {
        v16 = wk->actaiwk;
        v16->stat = 2;
        v16->next_timer = 0;
      }
    }
    return 1;
  }
  if (wk->aiwk->stat != 1 || actaiwk->stat != 2)
  {
    sBtlAAIProc(wk);
    return 1;
  }
  result = 1;
  actaiwk->mode = 12;
  if ((actaiwk->status & 0x1000) == 0)
    actaiwk->stat = 1;
  return result;
}

// 0x1db9ee0
bool sBtlEAIInit_Dummy(SBTLUNIT_WORK *wk) {
  return 1;
}

// 0x1db9ef0
bool sBtlEAIInit_None(SBTLUNIT_WORK *wk) {
  s32 devilid;
  s8 v5;
  sdfVector4_t *v6;
  SBTLACTAI_WORK *actaiwk;
  SBTLACTAI_WORK *v10;

  devilid = wk->para->devilid;
  if (sBtlCheckScriptData(devilid, wk))
  {
    sBtlSetAIWkStat(wk, 1);
    actaiwk = wk->actaiwk;
    actaiwk->mode = 12;
    actaiwk->stat = 1;
    return 0;
  }
  v10 = wk->actaiwk;
  if ((v10->status & 0x400) != 0)
  {
    sBtlSetNextPathData(wk);
    return 0;
  }
  else
  {
    v10->mode = 1;
    sBtlSetNormalAction(wk, 1, v5, -1, v6);
    return 1;
  }
}

// 0x1dba050
bool sBtlEAIInit_Summon(SBTLUNIT_WORK *wk) {
  sdfVector4_t *p_mv_spd;
  sdfVector4_t *p_mv_spdbk;
  SBTLACTAI_WORK *actaiwk;
  SBATTLE_WORK *v12;
  s64 v14;
  s32 v15;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  sdatUnitWork_t *para;
  sdatUnitWork_t *v19;
  u32 mode;
  bool v21;
  s32 v22;
  SB_ENCOUNTPAC *EncountPac;
  SBTLSM_LISTWORK *sysmsgList;
  s32 v29;
  s64 v31;
  SBTLUNIT_LISTWORK *v32;
  SBTLUNIT_WORK *v33;
  sdatUnitWork_t *v34;
  sdatUnitWork_t *v35;

  wk->actaiwk->status = wk->actaiwk->status & 0xFFFFFDC0 | 0x24;
  *(u64 *)&vct_A.x = 0;
  *(u64 *)&vct_A.z = 0;
  p_mv_spd = &wk->mv_spd;
  *p_mv_spd = vct_A;
  p_mv_spdbk = &wk->mv_spdbk;
  actaiwk = wk->actaiwk;
  *p_mv_spdbk = vct_A;
  *(u64 *)&actaiwk->frame = 0x3C00000000LL;
  if ((wk->vstatus & 0x4000000) != 0)
    goto LABEL_24;
  v12 = wk;
  if (!v12->maigoEnc)
    goto LABEL_22;
LABEL_24:
  wk->vstatus &= ~0x4000000u;
  return 1;
LABEL_22:
  if (v12->encountno == 515)
    goto LABEL_24;
  v14 = 0;
  v15 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v14 >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[v14]->pUnit;
    if (pUnit)
    {
      if ((pUnit->side & 2) != 0 && pUnit->ListID != wk->ListID)
      {
        para = pUnit->para;
        v19 = wk->para;
        if (para->raceid == v19->raceid && para->devilid == v19->devilid)
        {
          mode = pUnit->mode;
          v21 = mode > 4;
          v22 = (1 << mode) & 0x16;
          if (!v21 && v22 != 0)
            ++v15;
        }
      }
    }
    ++v14;
  }
  EncountPac = sBtlGetEncountPac(-1);
  if ((EncountPac[wk->encountno]->flag & 4) == 0)
  {
    if (!sBtlPlayerCheckRSpirit())
    {
      if (v15 < 1)
      {
        sysmsgList = wk->sysmsgList;
        v29 = 51;
      }
      else
      {
        sysmsgList = wk->sysmsgList;
        v29 = 52;
      }
      sBtlCreateSM(sysmsgList, wk, v29, 0, 0, 120);
    }
    v31 = 0;
    while (2)
    {
      v32 = wk->UnitMng;
      if (v31 >= v32->number)
        return 1;
      v33 = v32->pUnitL[v31]->pUnit;
      if (!v33)
        goto LABEL_68;
      goto LABEL_9001;
      if (!v33)
      {
LABEL_68:
        ++v31;
        continue;
      }
LABEL_9001:
      break;
    }
    if ((v33->side & 2) != 0 && v33->ListID != wk->ListID)
    {
      v34 = v33->para;
      v35 = wk->para;
      if (v34->raceid == v35->raceid && v34->devilid == v35->devilid)
        v33->vstatus |= 0x4000000u;
    }
    goto LABEL_68;
  }
  return 1;
}

// 0x1dba5a0
bool sBtlEAIInit_BtlInit(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;

  wk->actaiwk->status = wk->actaiwk->status & 0xFFFFFDE0 | 4;
  *(u64 *)&vct_A.x = 0;
  *(u64 *)&vct_A.z = 0;
  actaiwk = wk->actaiwk;
  wk->mv_spdbk = vct_A;
  actaiwk->mode = 13;
  *(u64 *)&actaiwk->frame = 0x3C00000000LL;
  return 1;
}

// 0x1dba6e0
bool sBtlEAIInit_BtlWait(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;

  wk->actaiwk->status = wk->actaiwk->status & 0xFFFFFDE0 | 5;
  *(u64 *)&vct_A.x = 0;
  *(u64 *)&vct_A.z = 0;
  actaiwk = wk->actaiwk;
  wk->mv_spdbk = vct_A;
  actaiwk->mode = 11;
  actaiwk->stat = 2;
  *(u64 *)&actaiwk->frame = 0x3C00000000LL;
  return 1;
}

// 0x1dba830
bool sBtlEAIProc_Dummy(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;

  actaiwk = wk->actaiwk;
  actaiwk->stat = 2;
  return 1;
}

// 0x1dba850
bool sBtlEAIProc_Wait(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;

  if (wk->actaiwk->cmpframe > wk->actaiwk->frame)
    return 1;
  sBtlResetAAI(wk);
  sBtlSetAIWkStat(wk, 1);
  actaiwk = wk->actaiwk;
  actaiwk->mode = 0;
  actaiwk->stat = 1;
  return 1;
}

// 0x1dba9d0
bool sBtlEAIProc_Movef(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  f32 y;
  f32 z;
  f32 w;
  f32 priv_area_r;
  f32 x;
  f32 v9;
  f32 v10;
  f32 v11;
  SBTLACTAI_WORK *v12;
  sdfVector4_t vector2;
  f32 vector1;
  sdfVector4_t v16;

  actaiwk = wk->actaiwk;
  if (actaiwk->cmpframe <= actaiwk->frame)
    goto LABEL_18;
  if ((actaiwk->status & 0x10) != 0)
  {
    v16.x = wk->pos.x;
    y = wk->pos.y;
    z = wk->pos.z;
    w = wk->pos.w;
    priv_area_r = actaiwk->priv_area_r;
    x = actaiwk->ppos.x;
    v9 = actaiwk->ppos.y;
    v11 = actaiwk->ppos.z;
    v10 = actaiwk->ppos.w;
    vector1 = wk->pos.x;
    v16.x = vector1;
    v16.y = y;
    v16.z = z;
    v16.w = w;
    *(u64 *)&vector2.z = __PAIR64__(LODWORD(v10), LODWORD(v11));
    *(u64 *)&vector2.x = __PAIR64__(LODWORD(v9), LODWORD(x));
    if (sBtlCheckCrossCircle(v16, priv_area_r, vector2, 2.0))
    {
LABEL_18:
      sBtlResetAAI(wk);
      sBtlSetAIWkStat(wk, 1);
      v12 = wk->actaiwk;
      v12->mode = 0;
      v12->stat = 1;
    }
  }
  return 1;
}

// 0x1dbab40
bool sBtlEAIProc_Guard(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;

  wk->status |= 0x100u;
  if (wk->actaiwk->cmpframe <= wk->actaiwk->frame)
  {
    sBtlResetAAI(wk);
    sBtlSetAIWkStat(wk, 1);
    actaiwk = wk->actaiwk;
    actaiwk->mode = 0;
    actaiwk->stat = 1;
    wk->status &= ~0x100u;
  }
  return 1;
}

// 0x1dbac30
bool sBtlEAIProc_Ctact(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  SBTLACTAI_WORK *v4;
  s32 targetID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v10;
  SBTLUNIT_WORK *v11;
  f32 priv_area_r;
  f32 z;
  f32 w;
  f32 x;
  f32 y;
  f32 v18;
  f32 v19;
  f32 v20;
  s32 v22;
  SBTLACTAI_WORK *v24;
  sdfVector4_t vector2;
  f32 v27;
  f32 v28;
  sdfVector4_t v29;

  actaiwk = wk->actaiwk;
  if (actaiwk->cmpframe <= actaiwk->frame)
    goto LABEL_38;
  v4 = wk->actaiwk;
  if ((v4->status & 0x180) == 0x100)
  {
    v4 = wk->actaiwk;
    if (v4->mode > 11)
      goto LABEL_18;
    goto LABEL_12;
  }
  if (v4->mode > 11)
  {
LABEL_18:
    targetID = v4->targetID;
    goto LABEL_19;
  }
LABEL_12:
  targetID = v4->LockID;
  if (wk->battlemode != 3 && (wk->side & 0x80) != 0)
  {
    v4 = wk->actaiwk;
    goto LABEL_18;
  }
LABEL_19:
  UnitMng = wk->UnitMng;
  v10 = sBtlSearchUnit_ID(UnitMng, targetID);
  if (!v10)
    goto LABEL_37;
  v11 = v10;
  if (sBtlCheckExist(v11))
    goto LABEL_29;
LABEL_37:
  actaiwk = wk->actaiwk;
  goto LABEL_38;
LABEL_29:
  priv_area_r = wk->actaiwk->priv_area_r;
  v29.x = wk->pos.x;
  v29.y = wk->pos.y;
  z = wk->pos.z;
  w = wk->pos.w;
  x = v11->pos.x;
  y = v11->pos.y;
  v19 = v11->pos.z;
  v18 = v11->pos.w;
  v20 = v11->actaiwk->priv_area_r;
  v27 = wk->pos.y;
  v28 = wk->pos.x;
  v29.y = v27;
  v29.x = v28;
  v29.z = z;
  v29.w = w;
  *(u64 *)&vector2.z = __PAIR64__(LODWORD(v18), LODWORD(v19));
  *(u64 *)&vector2.x = __PAIR64__(LODWORD(y), LODWORD(x));
  if (sBtlCheckCrossCircle(v29, priv_area_r, vector2, v20))
  {
    actaiwk = wk->actaiwk;
    if (!actaiwk->searchflg)
    {
LABEL_38:
      actaiwk->mode = 0;
      actaiwk->stat = 1;
      return 1;
    }
    v22 = actaiwk->targetID;
    v11->actaiwk->searchflg = 1;
    sBtlSetGroupAction(v11, v22, 0xCu, 0);
    v24 = v11->actaiwk;
    v24->datamode = 0;
    v24->dataflg = 0;
    *(u64 *)v24->data_p = 0;
    goto LABEL_37;
  }
  return 1;
}

// 0x1dbafa0
bool sBtlEAIProc_Search(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  s32 *data_p;

  actaiwk = wk->actaiwk;
  if (actaiwk->cmpframe > actaiwk->frame)
  {
    if (!sBtlCheckSearchEnemy(wk, (s32)0))
      return 1;
    wk->actaiwk->searchflg = 1;
    sBtlSetGroupAction(wk, 0, 0xCu, 0);
    actaiwk = wk->actaiwk;
    actaiwk->datamode = 0;
    data_p = actaiwk->data_p;
    actaiwk->dataflg = 0;
    *(u64 *)data_p = 0;
    goto LABEL_13;
  }
  actaiwk->mode = 0;
LABEL_13:
  actaiwk->stat = 1;
  return 1;
}

// 0x1dbb100
bool sBtlEAIProc_Chase(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  s32 targetID;
  SBATTLE_WORK *v6;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v8;
  SBTLACTAI_WORK *v11;
  SBTLUNIT_WORK *v13;
  f32 r1;
  f32 z;
  f32 w;
  f32 r2;
  f32 v23;
  f32 *p_x;
  struct sdfVector4_t v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 y;
  f32 x;
  f32 v40;
  f32 vector1b;
  struct sdfVector4_t vector1;
  f32 vector1a;
  f32 v46;
  f32 pos0a;
  f32 pos0;
  sdfVector4_t v49;
  sdfVector4_t v50;
  sdfVector4_t pos;
  sdfVector4_t v52;
  sdfVector4_t v53;
  sdfVector4_t v54;

  actaiwk = wk->actaiwk;
  if (actaiwk->cmpframe <= actaiwk->frame)
  {
    sBtlResetAAI(wk);
LABEL_15:
    sBtlSetAIWkStat(wk, 1);
    v11 = wk->actaiwk;
    v11->mode = 0;
    v11->stat = 1;
    return 1;
  }
  actaiwk = wk->actaiwk;
  targetID = actaiwk->targetID;
  v6 = wk;
  UnitMng = v6->UnitMng;
  v8 = sBtlSearchUnit_ID(v6->UnitMng, targetID);
  if (!v8)
    goto LABEL_37;
  v13 = v8;
  if (!CheckLiveTarget(v8))
    goto LABEL_37;
  r1 = wk->actaiwk->priv_area_r;
  pos = wk->pos;
  v53.x = wk->rot.x;
  v53.y = wk->rot.y;
  z = wk->rot.z;
  w = wk->rot.w;
  r2 = v13->pos.x;
  v23 = v13->pos.z;
  vector1b = wk->pos.x;
  pos0a = wk->pos.y;
  v40 = wk->pos.z;
  v46 = wk->pos.w;
  y = wk->rot.y;
  x = wk->rot.x;
  v53.y = y;
  v53.x = x;
  pos.z = v40;
  pos.w = v46;
  pos.y = pos0a;
  pos.x = vector1b;
  v53.z = z;
  v53.w = w;
  *(u64 *)&v50.x = 0;
  *(u64 *)&v50.z = v9;
  if (sBtlCheckCrossCircle_Rot(pos, v53, r1, v50, r2, v23))
  {
    vector1 = wk->pos;
    vct_A = vector1;
    p_x = &vf00.x;
    v27 = v13->pos;
    v28 = p_x[4];
    v29 = p_x[6];
    v30 = p_x[7];
    vct_A = v27;
    vector1a = v29;
    pos0 = v30;
    v31 = vct_A.x;
    v32 = wk->rot.x;
    v33 = wk->rot.y;
    v34 = wk->rot.z;
    v35 = wk->rot.w;
    v52.z = vector1a;
    v52.y = 0.0;
    v52.x = v28;
    v52.w = pos0;
    v54.x = v32;
    v54.y = v33;
    v54.z = v34;
    v54.w = v35;
    *(u64 *)&v49.x = 0;
    if (sBtlCheckVerticalArea(v52, v54, v49, v31))
    {
LABEL_37:
      sBtlResetAAI(wk);
      goto LABEL_15;
    }
    return 1;
  }
  return 1;
}

// 0x1dbb5e0
bool sBtlEAIProc_Escape(SBTLUNIT_WORK *wk) {
  return 1;
}

// 0x1dbb5f0
bool sBtlEAIProc_Summonw(SBTLUNIT_WORK *wk) {
  bool result;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  SBTLACTAI_WORK *actaiwk;
  s32 status;

  if ((wk->status & 0x10000) == 0)
    return 0;
  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 2) != 0 && (u32)(pUnit->mode - 1) < 2)
      return 0;
  }
  if (!wk->motionno)
    goto LABEL_25;
  if (sBtlCheckMotionEnd(wk))
    goto LABEL_25;
  return 1;
LABEL_25:
  if ((wk->vstatus & 1) != 0)
    return 1;
  result = 1;
  if ((u32)(wk->mode - 1) >= 2)
  {
    wk->hstatus |= 0x80u;
    actaiwk = wk->actaiwk;
    status = actaiwk->status;
    actaiwk->mode = 0;
    actaiwk->stat = 1;
    actaiwk->status = status & 0xFFFFFF9F | 0x40;
  }
  return result;
}

// 0x1dbb7e0
bool sBtlEAIProc_BtlAI(SBTLUNIT_WORK *wk) {
  s64 v3;
  s32 v4;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  f32 move_area_r;
  f32 z;
  f32 w;
  f32 hit_area_r;
  f32 v13;
  f32 y;
  f32 v15;
  f32 v16;
  s32 actcounter;
  s32 v18;
  s32 devilid;
  sdfVector4_t vector2;
  f32 v22;
  f32 v23;
  s32 x;
  sdfVector4_t v25;

  v3 = 0;
  LOWORD(v4) = wk->actcounter_max;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v3 >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[v3]->pUnit;
    if (!pUnit)
      goto LABEL_5;
    if (!sBtlCheckDamageTarget(pUnit))
      goto LABEL_5;
    if ((pUnit->side & 1) != 0)
    {
      move_area_r = wk->actaiwk->move_area_r;
      v25.x = wk->pos.x;
      v25.y = wk->pos.y;
      z = wk->pos.z;
      w = wk->pos.w;
      hit_area_r = pUnit->actaiwk->hit_area_r;
      v13 = pUnit->pos.x;
      y = pUnit->pos.y;
      v16 = pUnit->pos.z;
      v15 = pUnit->pos.w;
      v23 = wk->pos.x;
      v22 = wk->pos.y;
      v25.y = v22;
      v25.x = v23;
      v25.z = z;
      v25.w = w;
      *(u64 *)&vector2.z = __PAIR64__(LODWORD(v15), LODWORD(v16));
      *(u64 *)&vector2.x = __PAIR64__(LODWORD(y), LODWORD(v13));
      if (sBtlCheckCrossCircle(v25, move_area_r, vector2, hit_area_r))
      {
        v4 = wk->actcounter_max >> 4;
        break;
      }
    }
LABEL_5:
    ++v3;
  }
  actcounter = wk->actcounter;
  if (actcounter >= (s16)v4)
  {
    wk->actcounter = 0;
    devilid = wk->para->devilid;
    if (sBtlCheckScriptData(devilid, wk))
      return 1;
    sBtlSetAIWkStat(wk, 1);
  }
  else
  {
    v18 = actcounter + 1;
    wk->actcounter = v18;
    x = v18;
    LimitRange(&x, 0, (s16)v4);
    wk->actcounter = x;
  }
  return 1;
}

// 0x1db7840
bool sBtlSetGroupAction(SBTLUNIT_WORK *wk, s32 targetid, u32 mode, s8 flg) {
  void *v7;
  s32 side;
  bool result;
  s64 v10;
  s32 v11;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  SBTLACTAI_WORK *actaiwk;
  _BOOL4 v16;
  s32 LeaderID;
  s32 ListID;
  s32 devilid;
  bool v20;
  _BOOL4 v21;
  SBTLACTAI_WORK *v23;
  s8 v25;
  sdfVector4_t *v26;
  s32 v28;
  s8 v29;
  sdfVector4_t *v30;
  SBTLACTAI_WORK *v32;
  s32 v33;
  u32 v35;
  s32 v36;
  s32 *v37;

  v7 = NewSpecific(SBTL_ACTAIMODE, 0xBu);
  InitializeArray_55364416(v7, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__250C5355F8A24CBF2E926DE71DC8C992E0218FA659A22D894ED11A2BD0100BF0, 0);
  side = wk->side;
  result = 1;
  if ((side & 1) != 0 || (side & 7) == 0)
    return result;
  v10 = 0;
  v37 = (s32 *)&v7[2] + mode;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v10 >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[v10]->pUnit;
    if (!pUnit)
      goto LABEL_9;
    if (pUnit->ListID == wk->ListID)
      goto LABEL_9;
    if (!sBtlCheckExist(pUnit))
      goto LABEL_9;
    actaiwk = pUnit->actaiwk;
    if ((actaiwk->status & 0x100) != 0 && wk->actaiwk->LeaderID == actaiwk->LeaderID)
    {
      v16 = ((pUnit->side ^ wk->side) & 7) == 0;
      if (flg == 1)
        goto LABEL_27;
    }
    else
    {
      v16 = 0;
      if (flg == 1)
      {
LABEL_27:
        if (((pUnit->side ^ wk->side) & 7) == 0)
          v16 = 1;
      }
    }
    LeaderID = actaiwk->LeaderID;
    ListID = wk->ListID;
    devilid = pUnit->para->devilid;
    if (sBtlCheckScriptData(devilid, pUnit))
      goto LABEL_9;
    if ((pUnit->status & 0x800) == 0)
    {
      v20 = ListID != LeaderID && !v16;
      v21 = !v20;
      if ((pUnit->side & 7) != 0 && v21)
      {
        if (mode <= 0xB)
        {
          v11 = *v37;
          sBtlSetNormalAction(pUnit, v11, v25, -1, v26);
        }
        else
        {
          v23 = pUnit->actaiwk;
          if ((u32)(v23->mode - 15) >= 0xFFFFFFFD)
          {
            v23 = pUnit->actaiwk;
            v23->targetID = targetid;
          }
          else
          {
            v23 = pUnit->actaiwk;
            v23->targetID = targetid;
            v23->mode = mode;
            v23->stat = 1;
            v23->status = v23->status & 0xFFFFFD80 | 0x44;
          }
        }
      }
    }
LABEL_9:
    ++v10;
  }
  v28 = wk->para->devilid;
  if (sBtlCheckScriptData(v28, wk))
    return 0;
  if ((wk->status & 0x800) != 0)
    return 0;
  v32 = wk->actaiwk;
  v33 = v32->mode;
  if (v33 <= 11)
  {
    if (mode > 0xB)
    {
LABEL_60:
      v32 = wk->actaiwk;
LABEL_61:
      v32->stat = 1;
      v32->targetID = targetid;
      v32->mode = mode;
      v32->status = v32->status & 0xFFFFFD80 | 0x44;
      return 1;
    }
    v36 = *v37;
    sBtlSetNormalAction(wk, v36, v29, -1, v30);
    return 1;
  }
  else
  {
    if ((u32)v33 > 0xE)
    {
      if (!v35)
        goto LABEL_60;
      goto LABEL_61;
    }
    if (!v35)
    {
      v32 = wk->actaiwk;
    }
    v32->targetID = targetid;
    return 1;
  }
}

// 0x1dbbab0
static void SetUnitHitPush(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, f32 _Yohaku) {
  f32 x;
  f32 z;
  f32 v9;
  f32 v10;
  f32 PosToDir;
  f32 LenXZ;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 ZeroZ;
  s64 ZeroY;

  ZeroY = 0;
  ZeroZ = 0.0;
  x = wk->pos.x;
  z = wk->pos.z;
  v9 = wklock->pos.x;
  v10 = wklock->pos.z;
  PosToDir = sBtlGetPosToDir(x, z, v9, v10);
  LenXZ = sBtlGetLenXZ(wk->pos.x, wk->pos.z, wklock->pos.x, wklock->pos.z);
  if (LenXZ >= 0.01)
    goto LABEL_12;
  sBtlGetZeroPos((f32 *)&ZeroY + 1, &ZeroY, &ZeroZ);
  v13 = wklock->pos.x;
  v14 = wklock->pos.z;
  v15 = *((f32 *)&ZeroY + 1);
  v16 = ZeroZ;
  PosToDir = sBtlGetPosToDir(v13, v14, v15, v16);
  LenXZ = sBtlGetLenXZ(wklock->pos.x, wklock->pos.z, *((f32 *)&ZeroY + 1), ZeroZ);
  if (LenXZ <= 0.0)
  {
LABEL_12:
    v17 = (f32)((f32)(wk->actaiwk->hit_area_r + wklock->actaiwk->hit_area_r) + Yohaku)
        - LenXZ;
    if (v17 <= 0.0)
      return;
  }
  else
  {
    v17 = (f32)(wk->actaiwk->hit_area_r + wklock->actaiwk->hit_area_r) + Yohaku;
  }
  wklock->UnitHitPushDir = PosToDir;
  wklock->UnitHitPushLen = v17;
  wklock->UnitHitPushUse = 1;
}

// 0x1dbbc80
static void SetUnitHitPush_Sub(f32 _X1, f32 _Z1, f32 _Size1, f32 _X2, f32 _Z2, f32 _Size2, SBTLUNIT_WORK *wklock, f32 _Yohaku) {
  f32 PosToDir;
  f32 v18;

  PosToDir = sBtlGetPosToDir(X1, Z1, X2, Z2);
  v18 = (f32)((f32)(Size1 + Size2) + Yohaku) - sBtlGetLenXZ(X1, Z1, X2, Z2);
  if (v18 > 0.0)
  {
    wklock->UnitHitPushDir = PosToDir;
    wklock->UnitHitPushLen = v18;
    wklock->UnitHitPushUse = 1;
  }
}

// 0x1dbbd70
static void SetUnitHitApproach(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, f32 _Yohaku) {
  f32 x;
  f32 z;
  f32 v9;
  f32 v10;
  f32 PosToDir;
  f32 v12;

  x = wk->pos.x;
  z = wk->pos.z;
  v9 = wklock->pos.x;
  v10 = wklock->pos.z;
  PosToDir = sBtlGetPosToDir(x, z, v9, v10);
  v12 = (f32)((f32)(wk->actaiwk->hit_area_r + wklock->actaiwk->hit_area_r) + Yohaku)
      - sBtlGetLenXZ(wk->pos.x, wk->pos.z, wklock->pos.x, wklock->pos.z);
  if (v12 < 0.0)
  {
    wk->UnitHitPushDir = PosToDir;
    wk->UnitHitPushUse = 1;
    wk->UnitHitPushLen = -v12;
  }
}

// 0x1dbbe70
bool sBtlMVSupport(SBTLUNIT_WORK *wk) {
  s32 flg;
  s32 side;
  s32 v6;
  SBTLACTAI_WORK *actaiwk;
  s32 LockID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v10;
  char v11;
  char IsEnemyLastDeadStop;
  char IsSetsumaPadStop;
  bool IsHuuma;
  SBTLACTAI_WORK *v17;
  s32 status;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 priv_area_r;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 hit_area_r;
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
  long f64 v44;
  f32 frid_area_r;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 v53;
  f32 v54;
  f32 v55;
  f32 v56;
  f32 v57;
  long f64 v58;
  SBTLACTION_WORK *actwk;
  f32 v60;
  u32 v61;
  SBTLACTION_WORK *v62;
  f32 v63;
  u32 v64;
  sdatUnitWork_t *para;
  u32 v66;
  bool v67;
  f32 v68;
  f32 v69;
  f32 v70;
  f32 v71;
  u32 v72;
  SBTLACTAI_WORK *v73;
  f32 hitbk_start_wait_cnt;
  f32 Bezier;
  SBTLACTAI_WORK *v76;
  f32 hitbk_rate;
  f32 v78;
  f32 v79;
  f32 v80;
  f32 v81;
  f32 v82;
  f32 v83;
  struct sdfVector4_t pos;
  float32x4_t *v86;
  SBTLACTAI_WORK *v90;
  f32 hitbk_cnt;
  f32 *p_x;
  f32 v95;
  f32 v96;
  f32 v97;
  u32 v99;
  f32 Bounce_Spd;
  s32 Bounce_HitStopWait;
  s32 v103;
  f32 v104;
  f32 v105;
  s32 Bounce_HitStopCnt;
  bool v107;
  s32 v108;
  s32 Bounce_Cnt;
  dds3Basic_t *pBasic;
  s32 v111;
  f32 v113;
  s32 battlemode;
  f32 front_deg;
  f32 Dir180;
  sdfVector4_t *p_pos;
  f32 *p_z;
  s64 i;
  SBTLUNIT_LISTWORK *v124;
  SBTLUNIT_WORK *pUnit;
  s64 v126;
  s32 size;
  f32 v128;
  SBTLUNIT_LISTWORK *v130;
  SBTLUNIT_WORK *v131;
  s32 ListID;
  s32 v133;
  u32 v134;
  s32 v135;
  s32 v136;
  s32 v137;
  s32 v138;
  bool v139;
  s32 mode;
  s32 devilid;
  s32 v143;
  bool v144;
  f32 v145;
  f32 v146;
  f32 v147;
  f32 v148;
  f32 v150;
  f32 v151;
  f32 v152;
  f32 v153;
  f32 v156;
  SBTLACTAI_WORK *v157;
  f32 *v158;
  f32 *v159;
  bool *SubCylinder_Use;
  s64 v161;
  f32 *SubCylinder_Size;
  f32 v163;
  f32 v164;
  f32 v165;
  f32 v166;
  f32 v167;
  f32 v168;
  f32 v169;
  f32 RotToDir;
  s32 v175;
  s32 v176;
  s32 v177;
  f32 v178;
  s64 v179;
  f32 v180;
  f32 v181;
  f32 PosToDir;
  f32 v184;
  s32 v186;
  s32 v187;
  u32 v188;
  f32 v189;
  f32 v190;
  f32 v191;
  f32 v192;
  f32 v193;
  f32 v195;
  f32 v196;
  f32 v197;
  f32 v198;
  u32 v199;
  f32 v200;
  s64 v201;
  f32 v202;
  f32 v203;
  f32 v205;
  f32 v206;
  s32 motionno;
  bool v208;
  bool v209;
  f32 v210;
  f32 v211;
  f32 v212;
  f32 v214;
  f32 v215;
  s64 v216;
  f32 v217;
  f32 v218;
  f32 v220;
  f32 v221;
  f32 v222;
  f32 v223;
  s64 v224;
  f32 v225;
  f32 v227;
  s64 v228;
  f32 v229;
  f32 v230;
  f32 *v235;
  f32 v236;
  f32 v237;
  f32 v238;
  char v240;
  SBTLACTAI_WORK *v241;
  s64 v242;
  f32 v243;
  f32 v244;
  f32 v245;
  f32 v247;
  f32 v248;
  f32 v249;
  s64 v250;
  f32 v251;
  f32 v252;
  f32 v254;
  f32 v255;
  f32 v257;
  f32 v258;
  u32 v259;
  f32 v260;
  f32 v261;
  s64 v262;
  f32 v263;
  f32 v264;
  s64 v265;
  f32 v266;
  f32 v267;
  f32 v269;
  f32 v270;
  f32 v271;
  f32 v272;
  s64 v273;
  f32 v274;
  f32 v275;
  f32 v276;
  f32 v277;
  f32 v278;
  f32 v279;
  f32 v280;
  f32 v281;
  s64 v282;
  f32 v283;
  f32 v284;
  f32 v286;
  f32 v287;
  f32 v288;
  f32 v289;
  s64 v290;
  f32 v291;
  f32 v292;
  f32 v293;
  f32 v294;
  f32 v295;
  f32 v296;
  f32 v297;
  f32 v298;
  f32 v299;
  s64 v300;
  f32 v302;
  f32 v303;
  f32 v304;
  f32 v305;
  f32 v306;
  s64 v307;
  f32 v308;
  f32 v309;
  s32 v310;
  bool v311;
  u32 v312;
  s32 v314;
  s32 v316;
  f32 v318;
  u32 v320;
  f32 v321;
  f32 v322;
  f32 v323;
  f32 v324;
  f32 v325;
  SBTLUNIT_WORK *v326;
  SBTLUNIT_WORK *v327;
  f32 v328;
  f32 v329;
  f32 v330;
  f32 v331;
  f32 v332;
  f32 v333;
  f32 v334;
  f32 v335;
  f32 v336;
  f32 v337;
  f32 v338;
  f32 v339;
  s32 v340;
  s32 targetID;
  SBTLUNIT_LISTWORK *v343;
  SBTLUNIT_WORK *v344;
  f32 v345;
  SBTLUNIT_WORK *v346;
  f32 v347;
  f32 v348;
  f32 v350;
  SBATTLE_WORK *v351;
  SBTLUNIT_LISTWORK *v352;
  s32 playerID;
  SBTLUNIT_WORK *v354;
  f32 v355;
  f32 v356;
  f32 v357;
  f32 v358;
  f32 LenXZ;
  f32 v361;
  f32 UnitHitPushLen;
  f32 v363;
  f32 v364;
  f32 v365;
  f32 UnitHitPushDir;
  f32 v367;
  f32 v368;
  f32 GroundPos;
  u32 v370;
  f32 v371;
  f32 v372;
  f32 v373;
  SBTLACTION_WORK *v374;
  s32 *p_gravcnt;
  s32 gravcnt;
  SBTLACTION_WORK *v377;
  s32 vstatus;
  SBTLACTAI_WORK *v382;
  f32 v383;
  f32 hitbk_eff_len_oldx;
  f32 hitbk_eff_len_oldz;
  f32 v386;
  f32 v387;
  SBTLACTAI_WORK *v388;
  f32 v389;
  sdfVector4_t vector2;
  sdfVector4_t vector2a;
  s32 v394;
  s32 v395;
  bool v396;
  s16 v397;
  struct sdfVector4_t mv_spd;
  f32 v399;
  f32 v400;
  f32 v401;
  f32 v402;
  f32 v403;
  f32 v404;
  struct sdfVector4_t hitbk_dir;
  f32 v406;
  f32 vector1d;
  f32 vector1e;
  f32 vector1;
  struct sdfVector4_t vector1a;
  struct sdfVector4_t vector1b;
  u8 vector1c;
  s32 v415;
  struct sdfVector4_t koteipos;
  u64 ToZ[2];
  sdfVector4_t v418;
  sdfVector4_t v419;
  sdfVector4_t v420;
  sdfVector4_t v421;
  sdfVector4_t v422;
  sdfVector4_t v423;
  sdfVector4_t v424;

  flg = wk->flg;
  ToZ[0] = 0;
  if ((flg & 0x100) == 0)
  {
    side = wk->side;
    if (wk->battlemode == 3)
      v6 = 1;
    else
      v6 = 128;
    actaiwk = wk->actaiwk;
    if ((actaiwk->status & 0x180) == 0x100)
    {
      if (actaiwk->mode > 11)
        goto LABEL_27;
    }
    else if (actaiwk->mode > 11)
    {
      goto LABEL_27;
    }
    LockID = actaiwk->LockID;
    if (wk->battlemode == 3 || (wk->side & 0x80) == 0)
    {
LABEL_28:
      v397 = flg;
      UnitMng = wk->UnitMng;
      v10 = sBtlSearchUnit_ID(UnitMng, LockID);
      if (IsSceanStop())
      {
        v11 = (wk->status & 0x10) == 0;
        if (wk->battlemode == 3)
          goto LABEL_47;
LABEL_45:
        if ((wk->vstatus & 0x4000) != 0)
          v11 = 1;
LABEL_47:
        v415 = v6 & side;
        if (IsSceanStop())
        {
          IsEnemyLastDeadStop = sBtlIsEnemyLastDeadStop();
          v11 &= ~IsEnemyLastDeadStop;
          if (!v415)
            goto LABEL_57;
          goto LABEL_53;
        }
        IsEnemyLastDeadStop = 0;
        if (!v415)
          goto LABEL_57;
LABEL_53:
        if (IsSceanStop())
        {
          IsSetsumaPadStop = sBtlIsSetsumaPadStop();
          IsEnemyLastDeadStop |= IsSetsumaPadStop;
          v11 &= ~IsSetsumaPadStop;
        }
LABEL_57:
        IsHuuma = sBtlIsHuuma();
        v396 = IsHuuma;
        if ((v11 & 1) != 0)
          goto LABEL_174;
        goto LABEL_9001;
        if ((v11 & 1) != 0)
        {
LABEL_174:
          v394 = 1;
          goto LABEL_175;
        }
LABEL_9001:
        if (!IsHuuma)
        {
          v17 = wk->actaiwk;
          status = v17->status;
          if ((status & 0x10) != 0)
          {
            x = v17->ppos.x;
            y = v17->ppos.y;
            z = v17->ppos.z;
            w = v17->ppos.w;
            v418.x = x;
            v418.y = y;
            v418.z = z;
            v418.w = w;
            sBtlGetRotate(wk, v418);
            sBtlCheckRotSpd(wk, wk->actaiwk->ppos);
            status = wk->actaiwk->status;
          }
          if ((status & 1) != 0 && LockID != wk->ListID && v10)
          {
            if (sBtlCheckExist(v10))
            {
              priv_area_r = wk->actaiwk->priv_area_r;
              v419.x = wk->pos.x;
              v419.y = wk->pos.y;
              v25 = wk->pos.z;
              v26 = wk->pos.w;
              v27 = v10->pos.x;
              v28 = v10->pos.y;
              v30 = v10->pos.z;
              v29 = v10->pos.w;
              hit_area_r = v10->actaiwk->hit_area_r;
              vector1d = wk->pos.x;
              v403 = wk->pos.y;
              v419.y = v403;
              v419.x = vector1d;
              v419.z = v25;
              v419.w = v26;
              *(u64 *)&vector2.z = __PAIR64__(LODWORD(v29), LODWORD(v30));
              *(u64 *)&vector2.x = __PAIR64__(LODWORD(v28), LODWORD(v27));
              if (!sBtlCheckCrossCircle(v419, priv_area_r, vector2, hit_area_r))
              {
                v32 = v10->pos.x;
                v33 = v10->pos.y;
                v34 = v10->pos.z;
                v35 = v10->pos.w;
                v420.x = v32;
                v420.y = v33;
                v420.z = v34;
                v420.w = v35;
                sBtlGetRotate(wk, v420);
                sBtlCheckRotSpd(wk, v10->pos);
              }
            }
          }
          if ((wk->actaiwk->status & 0x200) != 0 && LockID != wk->ListID && v10)
          {
            if (sBtlCheckExist(v10))
            {
              v36 = v10->pos.x;
              v37 = v10->pos.y;
              v38 = v10->pos.z;
              v39 = v10->pos.w;
              v421.x = v36;
              v421.y = v37;
              v421.z = v38;
              v421.w = v39;
              sBtlGetRotate(wk, v421);
              sBtlCheckRotSpd(wk, v10->pos);
            }
          }
          if ((wk->actaiwk->status & 8) != 0 && LockID != wk->ListID && v10)
          {
            if (sBtlCheckExist(v10))
            {
              wk->mv_rot = v10->mv_rot;
              v40 = v10->rot.x;
              v41 = v10->rot.y;
              v43 = v10->rot.z;
              v42 = v10->rot.w;
              *(__n128 *)&v44 = sub_1B332C0(0, v40, v41, v43, v42);
              sub_1B335A0(&wk->rot, 0, v44);
              wk->mv_rotbk = v10->mv_rotbk;
            }
          }
          if ((wk->actaiwk->status & 2) != 0 && LockID != wk->ListID && v10)
          {
            if (sBtlCheckExist(v10))
            {
              frid_area_r = wk->actaiwk->frid_area_r;
              v422.x = wk->pos.x;
              v422.y = wk->pos.y;
              v47 = wk->pos.z;
              v48 = wk->pos.w;
              v49 = v10->pos.x;
              v50 = v10->pos.y;
              v52 = v10->pos.z;
              v51 = v10->pos.w;
              v53 = v10->actaiwk->priv_area_r;
              vector1e = wk->pos.x;
              v404 = wk->pos.y;
              v422.y = v404;
              v422.x = vector1e;
              v422.z = v47;
              v422.w = v48;
              *(u64 *)&vector2a.z = __PAIR64__(LODWORD(v51), LODWORD(v52));
              *(u64 *)&vector2a.x = __PAIR64__(LODWORD(v50), LODWORD(v49));
              if (sBtlCheckCrossCircle(v422, frid_area_r, vector2a, v53))
              {
                wk->mv_rot = v10->mv_rot;
                wk->mv_rotbk = v10->mv_rotbk;
                v54 = v10->mv_spd.x;
                v55 = v10->mv_spd.y;
                v57 = v10->mv_spd.z;
                v56 = v10->mv_spd.w;
                *(__n128 *)&v58 = sub_1B332C0(0, v54, v55, v57, v56);
                sub_1B335A0(&wk->mv_spd, 0, v58);
              }
            }
          }
        }
        if (v415)
          goto LABEL_140;
        if ((wk->side & 2) == 0)
        {
          if (wk->UnitHitPushUse)
          {
            actwk = wk->actwk;
            v60 = 0.1;
            wk->UnitHitPushUse = 0;
            v61 = actwk->status;
            if (v61 <= 0x15 && ((1 << v61) & 0x200048) != 0)
              v60 = 0.05;
            goto LABEL_137;
          }
LABEL_140:
          if ((wk->vstatus & 0x800) == 0)
            goto LABEL_174;
          v72 = wk->status;
          if ((v72 & 0x800) != 0)
            goto LABEL_174;
          v73 = wk->actaiwk;
          hitbk_start_wait_cnt = v73->hitbk_start_wait_cnt;
          if (!(IsEnemyLastDeadStop & 1 | (hitbk_start_wait_cnt <= 0.0)))
          {
            v394 = 0;
            v73->hitbk_start_wait_cnt = hitbk_start_wait_cnt + -1.0;
LABEL_175:
            vector1a = wk->mv_spd;
            vct_A = vector1a;
            sub_1949110(0);
            p_x = &vf00.x;
            v95 = p_x[4];
            v96 = p_x[5];
            v97 = p_x[6];
            v99 = wk->actwk->status;
            if (v99 == 10)
            {
LABEL_195:
              Bounce_Spd = wk->Bounce_Spd;
              if (Bounce_Spd == 0.0)
                goto LABEL_241;
              Bounce_HitStopWait = wk->Bounce_HitStopWait;
              v103 = Bounce_HitStopWait - 1;
              if (Bounce_HitStopWait >= 1)
              {
                --Bounce_HitStopWait;
                wk->Bounce_HitStopWait = v103;
              }
              if (Bounce_HitStopWait || (Bounce_HitStopCnt = wk->Bounce_HitStopCnt, v107 = __OFSUB__(Bounce_HitStopCnt, 1), v108 = Bounce_HitStopCnt - 1, (v108 < 0) ^ v107) || (wk->Bounce_HitStopCnt = v108) == 0)
              {
                v104 = Bounce_Spd + 0.81666666;
                v105 = v104 + wk->JumpOfsPos.y;
                wk->Bounce_Spd = v104;
                wk->JumpOfsPos.y = v105;
                if (v105 < -100.0)
                {
                  wk->JumpOfsPos.y = -100.0;
                  wk->Bounce_Spd = v104 + 0.81666666;
                  goto LABEL_241;
                }
              }
              else
              {
                v105 = wk->JumpOfsPos.y;
              }
              if (v105 > 0.0)
              {
                Bounce_Cnt = wk->Bounce_Cnt;
                wk->JumpOfsPos.y = 0.0;
                wk->yure = 0;
                wk->Bounce_Cnt = Bounce_Cnt + 1;
                pBasic = wk->pBasic;
                dds3UnitObjectBasicSetDamageYure(pBasic, 0.0);
                v111 = wk->Bounce_Cnt;
                wk->Bounce_Spd = wk->Bounce_Spd * -0.5;
                if (v111 == 1)
                {
                  FootEff(wk, 0.0, 0.0, 0.3, 5.0, 0);
                  if (!QuakeFlag)
                  {
                    dds3SetQuake(20, 0x1Eu);
                  }
                }
                v113 = wk->Bounce_Spd;
                if (sBtlGetABS(v113) <= 0.81666666 || wk->Bounce_Cnt > wk->Bounce_ReBound)
                {
                  wk->Bounce_Spd = 0.0;
                  wk->JumpOfsPos.y = 0.0;
                  *(u64 *)&wk->Bounce_HitStopWait = 0;
                }
              }
LABEL_241:
              if ((wk->hstatus & 0x1000) != 0)
              {
                front_deg = wk->front_deg;
                Dir180 = sBtlGetDir180(front_deg);
                FromEuler(0.0, Dir180 * 0.017453292, 0.0);
                goto LABEL_267;
              }
              battlemode = (u16)wk->battlemode;
              if (battlemode != 3)
                goto LABEL_254;
              goto LABEL_9021;
              if (battlemode != 3)
              {
LABEL_254:
                if (battlemode == 3)
                {
LABEL_261:
                  vector1b = wk->rot;
                  goto LABEL_263;
                }
                if ((wk->side & 0x80) == 0)
                  goto LABEL_261;
LABEL_282:
                vector1b = wk->rotbk;
LABEL_263:
                vct_A = vector1b;
LABEL_267:
                if ((wk->actaiwk->status & 4) == 0)
                  goto LABEL_747;
                p_pos = &wk->pos;
                p_z = &wk->pos.z;
                if (v396)
                {
                  for (i = 0; ; ++i)
                  {
                    v124 = wk->UnitMng;
                    if (i >= v124->number)
                      goto LABEL_699;
                    pUnit = v124->pUnitL[i]->pUnit;
                    if (!pUnit)
                      continue;
                  }
                }
                v126 = 0;
                v399 = sqrtf((f32)((f32)(v95 * v95) + (f32)(v96 * v96)) + (f32)(v97 * v97));
                while (1)
                {
                  v130 = wk->UnitMng;
                  if (v126 >= v130->number)
                  {
LABEL_699:
                    if (v396)
                    {
                      if (sBtlGetHuuma_Camera() == 1)
                      {
                        v340 = wk->side;
                        if ((v340 & 2) != 0)
                        {
                          v345 = 1.0;
                          v350 = (f32)(wk->actaiwk->hit_area_r + -50.0) / 130.0;
                          if (v350 < 0.0)
                            v350 = 0.0;
                          if (v350 <= 1.0)
                            v348 = (f32)(v350 * 100.0) + 150.0;
                          else
                            v348 = 250.0;
                          v351 = wk;
                          v352 = v351->UnitMng;
                          playerID = v351->playerID;
                          v354 = sBtlSearchUnit_ID(v352, playerID);
                          if (wk->ListID == v354->actaiwk->targetID)
                          {
                            v346 = v354;
                            goto LABEL_727;
                          }
                        }
                        else if ((v340 & 0x80) != 0)
                        {
                          targetID = wk->actaiwk->targetID;
                          if (targetID != -1)
                          {
                            targetID = wk->actaiwk->targetID;
                            v343 = wk->UnitMng;
                            v344 = sBtlSearchUnit_ID(v343, targetID);
                            if (v344)
                            {
                              v345 = 1.0;
                              v346 = v344;
                              v347 = (f32)(v344->actaiwk->hit_area_r + -50.0)
                                   / 130.0;
                              if (v347 < 0.0)
                                v347 = 0.0;
                              if (v347 <= 1.0)
                                v348 = (f32)(v347 * 100.0) + 150.0;
                              else
                                v348 = 250.0;
LABEL_727:
                              v355 = p_pos->x;
                              v356 = *p_z;
                              v357 = v346->pos.x;
                              v358 = v346->pos.z;
                              LenXZ = sBtlGetLenXZ(v355, v356, v357, v358);
                              v361 = wk->actaiwk->hit_area_r
                                   + v346->actaiwk->hit_area_r;
                              if (LenXZ >= (f32)(v348 + v361))
                              {
                                v363 = v348 + 10.0;
                                if (LenXZ > (f32)(v363 + v361) && (wk->status & 0x80) == 0)
                                {
                                  SetUnitHitApproach(wk, v346, v363);
                                  if (wk->UnitHitPushUse)
                                  {
                                    UnitHitPushLen = wk->UnitHitPushLen;
                                    wk->UnitHitPushUse = 0;
                                    if (UnitHitPushLen < v345)
                                    {
                                      UnitHitPushLen = v345;
LABEL_743:
                                      wk->UnitHitPushLen = 1.0;
                                    }
LABEL_744:
                                    v364 = wk->pos.x;
                                    v365 = wk->pos.z;
                                    UnitHitPushDir = wk->UnitHitPushDir;
                                    sBtlGetMoveXZ(v364, v365, UnitHitPushDir, UnitHitPushLen * 0.2, &wk->pos.x, p_z);
                                  }
                                }
                              }
                              else if ((wk->status & 0x80) == 0)
                              {
                                SetUnitHitPush(v346, wk, v348);
                                if (wk->UnitHitPushUse)
                                {
                                  UnitHitPushLen = wk->UnitHitPushLen;
                                  wk->UnitHitPushUse = 0;
                                  if (UnitHitPushLen < 1.0)
                                  {
                                    UnitHitPushLen = 1.0;
                                    goto LABEL_743;
                                  }
                                  goto LABEL_744;
                                }
                              }
                            }
                          }
                        }
                      }
                    }
LABEL_747:
                    v367 = wk->pos.x;
                    wk->ground = 0.0;
                    v368 = wk->pos.z;
                    GroundPos = sBtlGetGroundPos(v367, v368);
                    if (IsSceanStop())
                      goto LABEL_769;
                    if ((wk->para->devilid & 0xFFFE) == 0x138)
                      goto LABEL_769;
                    v370 = wk->status;
                    if ((v370 & 0x20) != 0 || (wk->vstatus & 0x80) != 0)
                    {
                      v374 = wk->actwk;
                      gravcnt = v374->gravcnt;
                      p_gravcnt = &v374->gravcnt;
                      *p_gravcnt = gravcnt + 1;
                      LimitRange(p_gravcnt, 0, 0x7FFF);
                      v377 = wk->actwk;
                      v373 = wk->pos.y
                           + (f32)((f32)((f32)((f32)v377->gravcnt * 0.1633) * (f32)v377->gravcnt) * 0.5);
                      if (v373 >= GroundPos)
                      {
                        vstatus = wk->vstatus;
                        v377->gravcnt = 0;
                        v373 = GroundPos;
                        wk->vstatus = vstatus & 0xFFFFFF7F;
                      }
                      goto LABEL_768;
                    }
                    if ((v370 & 0x200000) == 0)
                    {
                      v370 = wk->status;
                      if ((v370 & 0x1800) == 0 && (wk->vstatus & 0x800000) == 0)
                      {
                        v371 = wk->pos.x;
                        v372 = wk->pos.z;
                        v373 = sBtlGetGroundPos(v371, v372);
LABEL_768:
                        wk->pos.y = v373;
                      }
                    }
LABEL_769:
                    if (sBtlCheckSetsuma())
                    {
LABEL_783:
                      LOWORD(flg) = v397;
                      if ((wk->vstatus & 0x800) != 0 && ((v394 ^ 1 | ((u8)(BYTE1(wk->status) & 8) >> 3)) & 1) == 0)
                      {
                        v382 = wk->actaiwk;
                        v383 = wk->pos.x;
                        hitbk_eff_len_oldx = v382->hitbk_eff_len_oldx;
                        hitbk_eff_len_oldz = v382->hitbk_eff_len_oldz;
                        v386 = wk->pos.z;
                        v387 = sBtlGetLenXZ(hitbk_eff_len_oldx, hitbk_eff_len_oldz, v383, v386);
                        v388 = wk->actaiwk;
                        v388->hitbk_eff_len_oldx = wk->pos.x;
                        v388->hitbk_eff_len_oldz = wk->pos.z;
                        v389 = v387 + v388->hitbk_eff_len;
                        v388->hitbk_eff_len = v389;
                        if (v389 > 100.0)
                        {
                          v388->hitbk_eff_len = v389 + -100.0;
                          FootEff(wk, 0.0, 0.0, 0.15, 3.5, 0);
                        }
                      }
                      return (flg & 0x100) == 0;
                    }
                    if ((wk->status & 0x80000) == 0)
                      goto LABEL_783;
                    koteipos = wk->koteipos;
                    vct_A = koteipos;
                    goto LABEL_779;
LABEL_780:
                    goto LABEL_781;
LABEL_779:
                    goto LABEL_780;
LABEL_781:
                    wk->pos = vct_A;
                    goto LABEL_783;
                  }
                  v131 = v130->pUnitL[v126]->pUnit;
                  if (!v131)
                    goto LABEL_301;
                  ListID = v131->ListID;
                  v133 = wk->ListID;
                  if (ListID == v133)
                    goto LABEL_362;
                  if (ListID == v133)
                    goto LABEL_362;
                  v134 = wk->status;
                  if ((v134 & 0x800) != 0)
                    goto LABEL_362;
                  if (v131->status & 0x1800 | v134 & 0x1000)
                    goto LABEL_362;
                  if (!sBtlCheckExist2(v131))
                    goto LABEL_362;
                  if ((wk->status & 1) != 0)
                    goto LABEL_362;
                  v135 = wk->side;
                  if ((v135 & 7) != 0)
                  {
                    v136 = v131->side;
                    v137 = ((u8)v136 | (u8)v135) & 2;
                    v138 = ((u8)v136 ^ (u8)v135) & 7;
                    v139 = (v136 & 7) != 0 && v137 == 0;
                    if (v139 && v138 == 0)
                    {
LABEL_362:
                      mode = 0;
LABEL_363:
                      if (v131->ListID == wk->ListID)
                        goto LABEL_301;
                      goto LABEL_364;
                    }
                  }
                  mode = 0;
                  devilid = wk->para->devilid;
                  if (devilid == 292 || (u32)(devilid - 297) > 0xFFFFFFFC)
                    goto LABEL_363;
                  v143 = v131->para->devilid;
                  v144 = v143 == 292 || (u32)(v143 - 297) > 0xFFFFFFFC;
                  if (v144 || (v131->status & 1) != 0)
                    goto LABEL_362;
                  if ((wk->vstatus & 0x200) != 0 && (v131->vstatus & 0x200) == 0)
                    goto LABEL_301;
                  if ((wk->status & 0x80000) != 0)
                  {
                    v145 = wk->koteipos.x;
                    v146 = wk->koteipos.y;
                    v147 = wk->koteipos.z;
                    v148 = wk->koteipos.w;
                    sub_1B332C0(0, v145, v146, v147, v148);
                    PosOut(wk);
                  }
                  if (!v415 && v131->UnitHitPushUse)
                    goto LABEL_301;
                  if (sBtlCheckActDamage(wk, v131, 286))
                    goto LABEL_301;
                  v150 = p_pos->x;
                  v151 = *p_z;
                  v152 = v131->pos.x;
                  v153 = v131->pos.z;
                  v156 = sBtlGetLenXZ(v150, v151, v152, v153);
                  v157 = v131->actaiwk;
                  if (v156 <= (f32)((f32)(wk->actaiwk->hit_area_r + v157->hit_area_r) + 100.0))
                    break;
LABEL_360:
                  mode = 1;
                  if (v131->ListID == wk->ListID)
                    goto LABEL_301;
LABEL_364:
                  v158 = &v131->pos.x;
                  v402 = v131->pos.y;
                  v406 = v131->pos.x;
                  v159 = &v131->pos.z;
                  v400 = v131->pos.w;
                  v401 = v131->pos.z;
                  if (wk->para->devilid != 258)
                  {
                    if (!mode)
                      goto LABEL_301;
                    vector1c = 0;
                    SubCylinder_Use = wk->SubCylinder_Use;
                    if (SLODWORD(SubCylinder_Use->max_length) < 1)
                      goto LABEL_301;
LABEL_370:
                    v161 = 0;
                    v395 = vector1c & 1;
                    while (2)
                    {
                      if (!SubCylinder_Use[v161])
                        goto LABEL_372;
                      SubCylinder_Size = wk->SubCylinder_Size;
                      ToZ[0] = 0;
                      v163 = wk->rot.x;
                      v164 = wk->rot.y;
                      v165 = wk->rot.z;
                      v166 = wk->rot.w;
                      v167 = SubCylinder_Size[v161];
                      v168 = wk->SubCylinder_PosDir[v161];
                      v169 = wk->SubCylinder_PosLen[v161];
                      v424.x = v163;
                      v424.y = v164;
                      v424.z = v165;
                      v424.w = v166;
                      RotToDir = sBtlGetRotToDir(v424);
                      sBtlGetMoveXZ(p_pos->x, *p_z, v168 + RotToDir, v169, (f32 *)ToZ + 1, ToZ);
                      if (sBtlGetLenXZ(*((f32 *)ToZ + 1), *(f32 *)ToZ, v131->pos.x, v131->pos.z) > (f32)((f32)(v167 + v131->actaiwk->hit_area_r) + 100.0) || v415 != 0)
                      {
LABEL_372:
                        SubCylinder_Use = wk->SubCylinder_Use;
                        if (++v161 >= SLODWORD(SubCylinder_Use->max_length))
                          goto LABEL_301;
                        continue;
                      }
                      break;
                    }
                    if ((wk->side & 2) == 0)
                    {
                      v175 = v131->side;
                      if (wk->battlemode == 3)
                        v176 = 1;
                      else
                        v176 = 128;
                      if ((v176 & v175) != 0)
                        goto LABEL_372;
                      v177 = wk->actaiwk->status;
                      if ((v175 & 2) == 0)
                      {
                        if ((v177 & 0x20) == 0)
                        {
                          if ((v131->status & 0x80) == 0)
                          {
                            v178 = v131->pos.x;
                            v179 = ToZ[0];
                            v180 = v131->pos.z;
                            v181 = v131->actaiwk->hit_area_r;
                            PosToDir = sBtlGetPosToDir(*((f32 *)&v179 + 1), *(f32 *)&v179, v178, v180);
                            v184 = (f32)((f32)(v167 + v181) + 0.0)
                                 - sBtlGetLenXZ(*((f32 *)&v179 + 1), *(f32 *)&v179, v178, v180);
                            if (v184 > 0.0)
                            {
                              v131->UnitHitPushDir = PosToDir;
                              v131->UnitHitPushLen = v184;
                              v131->UnitHitPushUse = 1;
                            }
                          }
LABEL_430:
                          if ((wk->status & 0x80) != 0 || wk->UnitHitPushUse)
                            goto LABEL_372;
                          v210 = v131->pos.x;
                          v211 = v131->pos.z;
                          v212 = *((f32 *)ToZ + 1);
                          v192 = *(f32 *)ToZ;
                          v193 = v131->actaiwk->hit_area_r;
                          v195 = sBtlGetPosToDir(v210, v211, v212, v192);
                          v196 = v210;
                          v197 = v211;
                          v198 = v212;
LABEL_436:
                          v214 = (f32)((f32)(v167 + v193) + 0.0)
                               - sBtlGetLenXZ(v196, v197, v198, v192);
                          if (v214 <= 0.0)
                            goto LABEL_372;
LABEL_451:
                          wk->UnitHitPushDir = v195;
                          wk->UnitHitPushLen = v214;
                          wk->UnitHitPushUse = 1;
                          goto LABEL_372;
                        }
LABEL_422:
                        v200 = v131->pos.x;
                        v201 = ToZ[0];
                        v202 = v131->pos.z;
                        v203 = v131->actaiwk->hit_area_r;
                        v205 = sBtlGetPosToDir(*((f32 *)&v201 + 1), *(f32 *)&v201, v200, v202);
                        v206 = (f32)((f32)(v167 + v203) + 0.0)
                             - sBtlGetLenXZ(*((f32 *)&v201 + 1), *(f32 *)&v201, v200, v202);
                        if (v206 <= 0.0)
                          goto LABEL_372;
LABEL_456:
                        v131->UnitHitPushDir = v205;
                        v131->UnitHitPushLen = v206;
                        v131->UnitHitPushUse = 1;
                        goto LABEL_372;
                      }
                      if ((v177 & 0x20) == 0)
                        goto LABEL_430;
LABEL_452:
                      v227 = v131->pos.x;
                      v228 = ToZ[0];
                      v229 = v131->pos.z;
                      v230 = v131->actaiwk->hit_area_r;
                      v205 = sBtlGetPosToDir(*((f32 *)&v228 + 1), *(f32 *)&v228, v227, v229);
                      v206 = (f32)((f32)(v167 + v230) + 100.0)
                           - sBtlGetLenXZ(*((f32 *)&v228 + 1), *(f32 *)&v228, v227, v229);
                      if (v206 <= 0.0)
                        goto LABEL_372;
                      goto LABEL_456;
                    }
                    v186 = v131->side;
                    if (wk->battlemode == 3)
                      v187 = 1;
                    else
                      v187 = 128;
                    if ((v187 & v186) != 0)
                    {
                      if (v399 > 0.0)
                      {
                        v188 = wk->actwk->status;
                        switch (v188)
                        {
                          case 3u:
                            goto LABEL_802;
                          case 0x15u:
                            goto LABEL_372;
                          case 6u:
LABEL_802:
                            if ((wk->status & 0x80) != 0 || wk->UnitHitPushUse)
                              goto LABEL_372;
                            v189 = v131->pos.x;
                            v190 = v131->pos.z;
                            v191 = *((f32 *)ToZ + 1);
                            v192 = *(f32 *)ToZ;
                            v193 = v131->actaiwk->hit_area_r;
                            v195 = sBtlGetPosToDir(v189, v190, v191, v192);
                            v196 = v189;
                            v197 = v190;
                            v198 = v191;
                            goto LABEL_436;
                        }
                        if ((wk->status & 0x80) != 0 || wk->UnitHitPushUse)
                          goto LABEL_372;
                        v271 = v131->pos.x;
                        v272 = v131->pos.z;
                        v273 = ToZ[0];
                        v274 = v131->actaiwk->hit_area_r;
                        v275 = 0.0;
                        v276 = v271;
                        v277 = v272;
                        v278 = v274;
                        v279 = *((f32 *)&v273 + 1);
                        v280 = *(f32 *)&v273;
LABEL_528:
                        SetUnitHitPush_Sub(v276, v277, v278, v279, v280, v167, wk, v275);
                        goto LABEL_372;
                      }
                      motionno = v131->motionno;
                      if (motionno <= 96)
                      {
                        v209 = motionno == 42;
                        v208 = motionno == 96;
                      }
                      else
                      {
                        v208 = (u32)(motionno - 103) < 4;
                        v209 = motionno == 135;
                      }
                      mv_spd = v131->mv_spd;
                      vct_A = mv_spd;
                      sub_1949110(0);
                      v235 = &vf00.x;
                      p_z = &wk->pos.z;
                      v236 = v235[6];
                      v237 = v235[4];
                      v238 = v235[5];
                      v240 = v209 || v208;
                      if (sqrtf((f32)((f32)(v237 * v237) + (f32)(v238 * v238)) + (f32)(v236 * v236)) != 0.0)
                        v240 = 1;
                      if ((v240 & 1) == 0 && (v131->hstatus & 0x80000) == 0)
                      {
                        v241 = v131->actaiwk;
                        if (((u32)v241->status >> 5) & 1 | v395)
                        {
                          v242 = ToZ[0];
                          v243 = *v158;
                          v244 = *v159;
                          v245 = v241->hit_area_r;
                          v247 = sBtlGetPosToDir(*((f32 *)&v242 + 1), *(f32 *)&v242, v243, v244);
                          v248 = (f32)((f32)(v167 + v245) + 0.0)
                               - sBtlGetLenXZ(*((f32 *)&v242 + 1), *(f32 *)&v242, v243, v244);
                          if (v248 > 0.0)
                          {
                            v131->UnitHitPushDir = v247;
                            v131->UnitHitPushLen = v248;
                            goto LABEL_568;
                          }
LABEL_567:
                          if (!v131->UnitHitPushUse)
                            goto LABEL_372;
LABEL_568:
                          v131->UnitHitPushUse = 0;
                          v292 = v131->pos.x;
                          v293 = v131->pos.z;
                          v294 = v131->UnitHitPushDir;
                          v295 = v131->UnitHitPushLen;
                          v296 = 0.5;
LABEL_571:
                          sBtlGetMoveXZ(v292, v293, v294, v295 * v296, &v131->pos.x, &v131->pos.z);
LABEL_371:
                          v423.y = v402;
                          v423.x = v406;
                          v423.w = v400;
                          v423.z = v401;
                          CheckMapHit(v131, v423);
                          goto LABEL_372;
                        }
                        if ((wk->side & 2) == 0)
                          goto LABEL_372;
                        if ((wk->status & 0x80) != 0)
                        {
                          goto LABEL_562;
                        }
                        else
                        {
                          v297 = *v158;
                          v298 = *v159;
                          v299 = v241->hit_area_r;
                          v300 = ToZ[0];
                          SetUnitHitPush_Sub(v297, v298, v299, *((f32 *)&v300 + 1), *(f32 *)&v300, v167, wk, 0.0);
LABEL_562:
                          if (wk->mode == 1)
                            goto LABEL_372;
                        }
                        if ((v131->status & 0x80) != 0)
                          goto LABEL_372;
                        v306 = v131->pos.x;
                        v307 = ToZ[0];
                        v308 = v131->pos.z;
                        v309 = v131->actaiwk->hit_area_r;
                        SetUnitHitPush_Sub(*((f32 *)&v307 + 1), *(f32 *)&v307, v167, v306, v308, v309, v131, 0.0);
                        goto LABEL_567;
                      }
                      if ((vector1c & 1) != 0)
                      {
                        v249 = v131->pos.x;
                        v250 = ToZ[0];
                        v251 = v131->pos.z;
                        v252 = v131->actaiwk->hit_area_r;
                        v254 = sBtlGetPosToDir(*((f32 *)&v250 + 1), *(f32 *)&v250, v249, v251);
                        v255 = (f32)((f32)(v167 + v252) + 0.0)
                             - sBtlGetLenXZ(*((f32 *)&v250 + 1), *(f32 *)&v250, v249, v251);
                        if (v255 <= 0.0)
                        {
                          if (!v131->UnitHitPushUse)
                            goto LABEL_372;
                        }
                        else
                        {
                          v131->UnitHitPushDir = v254;
                          v131->UnitHitPushLen = v255;
                        }
                        v131->UnitHitPushUse = 0;
                        v292 = v131->pos.x;
                        v293 = v131->pos.z;
                        v294 = v131->UnitHitPushDir;
                        v295 = v131->UnitHitPushLen;
                        v296 = 0.3;
                        goto LABEL_571;
                      }
                      v257 = 1.0;
                      v257 = 1.0;
                      v258 = v257;
                      if (wk->mode != 1)
                      {
                        v258 = v257;
                        if ((wk->side & 2) != 0)
                        {
                          v258 = v257;
                          v259 = wk->actwk->status;
                          if (v259 <= 0x15)
                          {
                            v258 = v257;
                            if (((1 << v259) & 0x200048) != 0)
                            {
                              if ((wk->status & 0x80) == 0)
                              {
                                v260 = v131->pos.x;
                                v261 = v131->pos.z;
                                v262 = ToZ[0];
                                v263 = v131->actaiwk->hit_area_r;
                                SetUnitHitPush_Sub(v260, v261, v263, *((f32 *)&v262 + 1), *(f32 *)&v262, v167, wk, 0.0);
                              }
                              v258 = 0.1;
                            }
                          }
                        }
                      }
                      if ((v131->status & 0x80) != 0)
                        goto LABEL_372;
                      v264 = v131->pos.x;
                      v265 = ToZ[0];
                      v266 = v131->pos.z;
                      v267 = v131->actaiwk->hit_area_r;
                      v269 = sBtlGetPosToDir(*((f32 *)&v265 + 1), *(f32 *)&v265, v264, v266);
                      v270 = (f32)((f32)(v167 + v267) + 0.0)
                           - sBtlGetLenXZ(*((f32 *)&v265 + 1), *(f32 *)&v265, v264, v266);
                      if (v270 <= 0.0)
                      {
                        if (!v131->UnitHitPushUse)
                          goto LABEL_372;
                      }
                      else
                      {
                        v131->UnitHitPushDir = v269;
                        v131->UnitHitPushLen = v270;
                      }
                      v131->UnitHitPushUse = 0;
                      v302 = v131->pos.x;
                      v303 = v131->pos.z;
                      v304 = v131->UnitHitPushDir;
                      v305 = v131->UnitHitPushLen;
                      sBtlGetMoveXZ(v302, v303, v304, v258 * v305, &v131->pos.x, &v131->pos.z);
                      goto LABEL_371;
                    }
                    v199 = wk->actaiwk->status;
                    if ((v186 & 2) == 0)
                    {
                      if ((v199 >> 5) & 1 | v395)
                        goto LABEL_422;
                      if ((v131->status & 0x80) == 0)
                      {
                        v281 = v131->pos.x;
                        v282 = ToZ[0];
                        v283 = v131->pos.z;
                        v284 = v131->actaiwk->hit_area_r;
                        v286 = sBtlGetPosToDir(*((f32 *)&v282 + 1), *(f32 *)&v282, v281, v283);
                        v287 = (f32)((f32)(v167 + v284) + 0.0)
                             - sBtlGetLenXZ(*((f32 *)&v282 + 1), *(f32 *)&v282, v281, v283);
                        if (v287 > 0.0)
                        {
                          v131->UnitHitPushDir = v286;
                          v131->UnitHitPushLen = v287;
                          v131->UnitHitPushUse = 1;
                        }
                      }
                      if (v399 <= 0.0 || (wk->status & 0x80) != 0 || wk->UnitHitPushUse)
                      {
                        goto LABEL_372;
                      }
                      v288 = v131->pos.x;
                      v289 = v131->pos.z;
                      v290 = ToZ[0];
                      v291 = v131->actaiwk->hit_area_r;
                      v276 = v288;
                      v277 = v289;
                      v275 = 100.0;
                      v278 = v291;
                      v279 = *((f32 *)&v290 + 1);
                      v280 = *(f32 *)&v290;
                      goto LABEL_528;
                    }
                    if ((v199 & 0x20) != 0)
                      goto LABEL_452;
                    if ((v131->status & 0x80) == 0)
                    {
                      v215 = v131->pos.x;
                      v216 = ToZ[0];
                      v217 = v131->pos.z;
                      v218 = v131->actaiwk->hit_area_r;
                      v220 = sBtlGetPosToDir(*((f32 *)&v216 + 1), *(f32 *)&v216, v215, v217);
                      v221 = (f32)((f32)(v167 + v218) + 100.0)
                           - sBtlGetLenXZ(*((f32 *)&v216 + 1), *(f32 *)&v216, v215, v217);
                      if (v221 > 0.0)
                      {
                        v131->UnitHitPushDir = v220;
                        v131->UnitHitPushLen = v221;
                        v131->UnitHitPushUse = 1;
                      }
                    }
                    if ((wk->status & 0x80) != 0 || wk->UnitHitPushUse)
                      goto LABEL_372;
                    v222 = v131->pos.x;
                    v223 = v131->pos.z;
                    v224 = ToZ[0];
                    v225 = v131->actaiwk->hit_area_r;
                    v195 = sBtlGetPosToDir(v222, v223, *((f32 *)&v224 + 1), *(f32 *)&v224);
                    v214 = (f32)((f32)(v167 + v225) + 100.0)
                         - sBtlGetLenXZ(v222, v223, *((f32 *)&v224 + 1), *(f32 *)&v224);
                    if (v214 <= 0.0)
                      goto LABEL_372;
                    goto LABEL_451;
                  }
                  vector1c = v131->side;
                  if (((mode | vector1c) & 1) != 0)
                  {
                    SubCylinder_Use = wk->SubCylinder_Use;
                    if (SLODWORD(SubCylinder_Use->max_length) >= 1)
                      goto LABEL_370;
                  }
LABEL_301:
                  ++v126;
                }
                if (!v415)
                {
                  if ((wk->side & 2) == 0)
                  {
                    if (!v312)
                    if (sBtlCheckUserUnit(v131))
                      goto LABEL_677;
                    v314 = wk->actaiwk->status;
                    if ((v131->side & 2) == 0)
                    {
                      if ((v314 & 0x20) == 0)
                      {
                        if ((v131->status & 0x80) == 0)
                        {
                          SetUnitHitPush(wk, v131, 0.0);
                        }
LABEL_653:
                        if ((wk->status & 0x80) == 0 && !wk->UnitHitPushUse)
                        {
                          v325 = 0.0;
                          goto LABEL_668;
                        }
LABEL_677:
                        mode = 1;
                        goto LABEL_678;
                      }
LABEL_669:
                      v325 = 0.0;
LABEL_675:
                      v326 = wk;
                      v327 = v131;
LABEL_676:
                      SetUnitHitPush(v326, v327, v325);
                      goto LABEL_677;
                    }
                    if ((v314 & 0x20) == 0)
                      goto LABEL_653;
LABEL_672:
                    v325 = 100.0;
                    goto LABEL_675;
                  }
                  if (!v312)
                  if (sBtlCheckUserUnit(v131))
                  {
                    if (v399 > 0.0 && wk->actwk->status != 21)
                      goto LABEL_653;
                    goto LABEL_677;
                  }
                  v316 = wk->actaiwk->status;
                  if ((v131->side & 2) != 0)
                  {
                    if ((v316 & 0x20) != 0)
                      goto LABEL_672;
                    if ((v131->status & 0x80) == 0)
                    {
                      SetUnitHitPush(wk, v131, 100.0);
                    }
                  }
                  else
                  {
                    if ((v316 & 0x20) != 0)
                      goto LABEL_669;
                    if ((v131->status & 0x80) == 0)
                    {
                      SetUnitHitPush(wk, v131, 0.0);
                    }
                    if (v399 <= 0.0)
                      goto LABEL_677;
                  }
                  if ((wk->status & 0x80) != 0 || wk->UnitHitPushUse)
                    goto LABEL_677;
                  v325 = 100.0;
LABEL_668:
                  v326 = v131;
                  v327 = wk;
                  goto LABEL_676;
                }
                v310 = wk->motionno;
                if (v310 <= 96)
                {
                  v311 = 0;
                  if (v310 == 42 || v310 == 96)
                    goto LABEL_629;
                }
                else
                {
                  if ((u32)(v310 - 103) < 0x21 && ((0x10000000FuLL >> ((u8)v310 - 103)) & 1) != 0)
                  {
LABEL_619:
                    v311 = 0;
                    goto LABEL_629;
                  }
                  if ((u32)(v310 - 179) >= 0xFFFFFFFC)
                  {
                    v311 = v157->targetID == v131->ListID;
LABEL_629:
                    v318 = 1.0;
                    if (wk->mode != 1)
                    {
                      v318 = 1.0;
                      if ((v131->side & 2) != 0 && !v311)
                      {
                        v318 = 1.0;
                        v320 = v131->actwk->status;
                        if (v320 <= 0x15)
                        {
                          v318 = 1.0;
                          if (((1 << v320) & 0x200048) != 0)
                          {
                            if ((v131->status & 0x80) == 0)
                            {
                              SetUnitHitPush(wk, v131, 0.0);
                            }
                            v318 = 0.1;
                            p_z = &wk->pos.z;
                          }
                        }
                      }
                    }
                    if ((wk->status & 0x80) != 0)
                    {
                      mode = 1;
                      if (v131->ListID == wk->ListID)
                        goto LABEL_301;
                      goto LABEL_364;
                    }
                    SetUnitHitPush(v131, wk, 0.0);
                    if (wk->UnitHitPushUse)
                    {
                      wk->UnitHitPushUse = 0;
                      v321 = wk->pos.x;
                      v322 = wk->pos.z;
                      v323 = wk->UnitHitPushDir;
                      v324 = wk->UnitHitPushLen;
                      sBtlGetMoveXZ(v321, v322, v323, v318 * v324, &wk->pos.x, p_z);
                    }
                    goto LABEL_360;
                  }
                }
                if (v399 == 0.0)
                {
                  if ((wk->hstatus & 0x80000) == 0)
                  {
                    if ((v157->status & 0x20) == 0)
                    {
                      if ((v131->side & 2) == 0)
                        goto LABEL_697;
                      if ((v131->status & 0x80) == 0)
                      {
                        SetUnitHitPush(wk, v131, 0.0);
                        mode = wk->mode;
                        if (mode != 1)
                        {
LABEL_690:
                          if ((wk->status & 0x80) == 0)
                          {
                            SetUnitHitPush(v131, wk, 0.0);
                            if (wk->UnitHitPushUse)
                            {
                              wk->UnitHitPushUse = 0;
                              v336 = wk->pos.x;
                              v337 = wk->pos.z;
                              v338 = wk->UnitHitPushDir;
                              v339 = wk->UnitHitPushLen;
                              v333 = v337;
                              v334 = v338;
                              v335 = v339 * 0.3;
                              v332 = v336;
                              goto LABEL_686;
                            }
                          }
                          goto LABEL_697;
                        }
                        goto LABEL_678;
                      }
                      mode = wk->mode;
                      if (mode != 1)
                        goto LABEL_690;
                      goto LABEL_678;
                    }
                    SetUnitHitPush(v131, wk, 0.0);
                    if (wk->UnitHitPushUse)
                    {
                      wk->UnitHitPushUse = 0;
                      v328 = wk->pos.x;
                      v329 = wk->pos.z;
                      v330 = wk->UnitHitPushDir;
                      v331 = wk->UnitHitPushLen;
                      v332 = v328;
                      v333 = v329;
                      v334 = v330;
                      v335 = v331;
LABEL_686:
                      p_z = &wk->pos.z;
                      sBtlGetMoveXZ(v332, v333, v334, v335, &wk->pos.x, &wk->pos.z);
                      mode = 1;
                      if (v131->ListID == wk->ListID)
                        goto LABEL_301;
                      goto LABEL_364;
                    }
LABEL_697:
                    mode = 1;
LABEL_678:
                    p_z = &wk->pos.z;
                    if (v131->ListID == wk->ListID)
                      goto LABEL_301;
                    goto LABEL_364;
                  }
                  v311 = 0;
                  p_z = &wk->pos.z;
                  goto LABEL_629;
                }
                goto LABEL_619;
              }
LABEL_9021:
              if ((wk->side & 1) != 0)
                goto LABEL_282;
              goto LABEL_254;
            }
            if (v99 != 40)
            {
              if (IsSceanStop())
                goto LABEL_241;
            }
            goto LABEL_195;
          }
          Bezier = 0.0;
          if ((v72 & 0x10000000) != 0)
          {
LABEL_150:
            if (Bezier > 40.0)
              Bezier = 40.0;
            if (Bezier < -40.0)
              Bezier = -40.0;
            if ((IsEnemyLastDeadStop & 1) != 0)
              Bezier = Bezier * 0.05;
            vector1 = Bezier;
            hitbk_dir = wk->actaiwk->hitbk_dir;
            vct_A = hitbk_dir;
            vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, vector1);
            pos = wk->pos;
            vct_B = pos;
            v86[1] = vaddq_f32(v86[1], v86[2]);
            v90 = wk->actaiwk;
            wk->pos = vct_A;
            hitbk_cnt = v90->hitbk_cnt;
            if ((IsEnemyLastDeadStop & 1) == 0)
            {
              hitbk_cnt = hitbk_cnt + v90->hitbk_cmpcnt;
              v90->hitbk_cnt = hitbk_cnt;
            }
            if (hitbk_cnt >= 1.0)
              wk->vstatus &= ~0x800u;
            goto LABEL_174;
          }
          v76 = wk->actaiwk;
          if (v76->hitbk_size_ignore)
            goto LABEL_145;
          size = wk->size;
          if (size == 2)
          {
            hitbk_rate = v76->hitbk_rate;
            v78 = v76->hitbk_cnt;
            v79 = 0.5;
            v80 = 0.2;
            goto LABEL_148;
          }
          if (size == 1)
          {
LABEL_145:
            hitbk_rate = v76->hitbk_rate;
            v78 = v76->hitbk_cnt;
            v79 = 0.6;
            v80 = 0.3;
          }
          else
          {
            if (wk->size)
            {
              v128 = v76->hitbk_rate;
              v78 = v76->hitbk_cnt;
              v81 = v128 * 0.1;
              v83 = v128;
              v82 = v128 * 0.1;
              goto LABEL_149;
            }
            hitbk_rate = v76->hitbk_rate;
            v78 = v76->hitbk_cnt;
            v79 = 0.7;
            v80 = 0.4;
          }
LABEL_148:
          v81 = hitbk_rate * v79;
          v82 = hitbk_rate * v80;
          v83 = hitbk_rate;
LABEL_149:
          Bezier = sBtlGetBezier(v83, v81, v82, 0.0, v78);
          goto LABEL_150;
        }
        if (!wk->UnitHitPushUse)
          goto LABEL_140;
        v62 = wk->actwk;
        v63 = 0.2;
        wk->UnitHitPushUse = 0;
        v64 = v62->status;
        if (v64 <= 0x15 && ((1 << v64) & 0x200048) != 0)
          v63 = 0.05;
        para = wk->para;
        v66 = (u16)para->devilid;
        if (para->devilid <= 291)
        {
          if (v66 == 262)
          {
LABEL_129:
            v67 = v64 == 64;
LABEL_130:
            if (v67)
              v60 = 0.0;
            else
              v60 = v63;
            goto LABEL_137;
          }
          if (v66 != 290)
          {
            if (v66 == 291)
            {
              v67 = v62->use_skillid == 1549;
              goto LABEL_130;
            }
            goto LABEL_133;
          }
        }
        else
        {
          if (v66 > 0x12C)
          {
            v60 = 0.0;
            if (v66 == 323 || v66 == 521)
              goto LABEL_137;
            goto LABEL_133;
          }
          if (v66 != 297)
          {
            if (v66 == 300)
              goto LABEL_129;
LABEL_133:
            v60 = v63;
LABEL_137:
            v68 = wk->pos.x;
            v69 = wk->UnitHitPushDir;
            v70 = wk->pos.z;
            v71 = wk->UnitHitPushLen;
            sBtlGetMoveXZ(v68, v70, v69, v60 * v71, &wk->pos.x, &wk->pos.z);
            goto LABEL_140;
          }
        }
        if ((para->aisyo->para[0] & 0x1000) != 0)
          v60 = 0.0;
        else
          v60 = v63;
        goto LABEL_137;
LABEL_40:
        if (wk->battlemode == 3)
          goto LABEL_47;
        goto LABEL_45;
LABEL_39:
        goto LABEL_40;
LABEL_38:
        goto LABEL_39;
      }
      v11 = 0;
      goto LABEL_38;
    }
    actaiwk = wk->actaiwk;
LABEL_27:
    LockID = actaiwk->targetID;
    goto LABEL_28;
  }
  return (flg & 0x100) == 0;
}

// 0x1dbf5a0
static void PosOut(SBTLUNIT_WORK *wk) {
  wk->pos = vct_A;
}

// 0x1db6e40
bool sBtlCheckHit_HitHelper(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock) {
  return (wk->status & 0x800) != 0 || (wklock->status & 0x1800 | wk->status & 0x1000) != 0;
}

// 0x1dbf670
void sBtlForceAddBtlNum(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock) {
  ;
}

// 0x1dbf680
void sBtlAddBtlNum(SBTLUNIT_WORK *wk) {
  ;
}

// 0x1dbf690
void sBtlDecBtlNum(SBTLUNIT_WORK *wk) {
  ;
}

// 0x1dbf6a0
void sBtlDecBtlNum_Mine(s32 id) {
  ;
}

// 0x1dad260
bool sBtlSetNormalAction(SBTLUNIT_WORK *wk, SBTL_ACTAIMODE type, s8 flg, s32 time, sdfVector4_t *pos) {
  sdatUnitWork_t *para;
  u32 BadStatus;
  s32 v12;
  u32 v13;
  sdfVector4_t *p_mv_spdbk;
  SBTLACTAI_WORK *actaiwk;
  sdatUnitWork_t *v19;
  SBTLUNIT_WORK *v21;
  s32 v22;
  s32 v23;
  f32 Rand;
  sdfVector4_t *p_ppos;
  f32 z;
  SBTLACTAI_WORK *v29;
  sdfVector4_t *v30;
  SBTLACTAI_WORK *v31;
  sdatUnitWork_t *v32;
  sdfVector4_t *v34;
  SBTLACTAI_WORK *v35;
  SBTLACTAI_WORK *v37;
  sdatUnitWork_t *v38;
  sdfVector4_t *v42;
  SBTLACTAI_WORK *v43;
  s32 v44;
  SBTLUNIT_WORK *v45;
  s32 v46;
  sdfVector4_t *v48;
  SBTLACTAI_WORK *v49;
  sdfVector4_t *v53;
  SBTLACTAI_WORK *v54;
  sdfVector4_t *v57;
  SBTLACTAI_WORK *v58;
  s32 v59;
  sdfVector4_t *v65;
  SBTLACTAI_WORK *v66;
  sdatUnitWork_t *v67;
  struct sdfVector4_t v73;
  struct sdfVector4_t max_mvspd;
  struct sdfVector4_t v75;
  struct sdfVector4_t v76;

  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  v12 = type - 1;
  if ((u32)(type - 1) > 0xB)
    return 1;
  v13 = BadStatus;
  switch (v12)
  {
    case 0:
      wk->actaiwk->status = wk->actaiwk->status & 0xFFFFFDE0 | 4;
      *(u64 *)&vct_A.x = 0;
      *(u64 *)&vct_A.z = 0;
      p_mv_spdbk = &wk->mv_spdbk;
      actaiwk = wk->actaiwk;
      *p_mv_spdbk = vct_A;
      actaiwk->mode = 1;
      actaiwk->frame = 0;
      if (v13 == 9 && !wk->bYobidousa)
      {
        actaiwk->cmpframe = 1;
        goto LABEL_22;
      }
      else
      {
        v19 = wk->para;
        if (sBtlIsKoufun(v19) && !wk->bYobidousa)
          time = 1;
        wk->actaiwk->cmpframe = time;
        goto LABEL_22;
      }
LABEL_22:
      v21 = wk;
      v22 = 0;
      v23 = 0;
      goto LABEL_108;
    case 1:
      Rand = GetRand(0x168u);
      p_ppos = &wk->actaiwk->ppos;
      z = wk->max_mvspd.z;
      if (!sBtlGetMovePos_MapHit(wk, wk, p_ppos, z * (f32)time, Rand, 0))
      {
        v73 = wk->pos;
        vct_A = v73;
        v29 = wk->actaiwk;
        v30 = &v29->ppos;
        *v30 = vct_A;
      }
      v31 = wk->actaiwk;
      v31->mode = 2;
      v31->frame = 0;
      if (v13 == 9 && !wk->bYobidousa)
      {
        time = 1;
      }
      else
      {
        v32 = wk->para;
        if (sBtlIsKoufun(v32) && !wk->bYobidousa)
          time = 1;
        v31 = wk->actaiwk;
      }
      v31->cmpframe = time;
      max_mvspd = wk->max_mvspd;
      vct_A = max_mvspd;
      v34 = &wk->mv_spdbk;
      v35 = wk->actaiwk;
      *v34 = vct_A;
      v35->status = v35->status & 0xFFFFFDE0 | 0x14;
      goto LABEL_87;
    case 2:
      v37 = wk->actaiwk;
      v37->mode = 3;
      v37->frame = 0;
      if (BadStatus == 9 && !wk->bYobidousa)
      {
        v37->cmpframe = 1;
      }
      else
      {
        v38 = wk->para;
        if (sBtlIsKoufun(v38) && !wk->bYobidousa)
          time = 1;
        wk->actaiwk->cmpframe = time;
      }
      *(u64 *)&vct_A.x = 0;
      *(u64 *)&vct_A.z = 0;
      v42 = &wk->mv_spdbk;
      v43 = wk->actaiwk;
      *v42 = vct_A;
      v43->status = v43->status & 0xFFFFFDE0 | 4;
      v44 = 29;
      v45 = wk;
      v46 = 0;
      goto LABEL_88;
    case 3:
      wk->actaiwk->status = wk->actaiwk->status & 0xFFFFFDE0 | 5;
      v75 = wk->max_mvspd;
      vct_A = v75;
      v48 = &wk->mv_spdbk;
      v49 = wk->actaiwk;
      *v48 = vct_A;
      v49->mode = 4;
      *(u64 *)&v49->frame = 0x4B000000000LL;
      goto LABEL_87;
    case 4:
      wk->actaiwk->status = wk->actaiwk->status & 0xFFFFFDE0 | 4;
      *(u64 *)&vct_A.x = 0;
      *(u64 *)&vct_A.z = 0;
      v53 = &wk->mv_spdbk;
      v54 = wk->actaiwk;
      *v53 = vct_A;
      v54->mode = 5;
      *(u64 *)&v54->frame = 0xB400000000LL;
      v21 = wk;
      v22 = 0;
      goto LABEL_107;
    case 5:
      wk->actaiwk->status = wk->actaiwk->status & 0xFFFFFDE0 | 0x204;
      v76 = wk->max_mvspd;
      vct_A = v76;
      v57 = &wk->mv_spdbk;
      v58 = wk->actaiwk;
      *v57 = vct_A;
      v58->mode = 6;
      v58->frame = 0;
      v58->cmpframe = time;
LABEL_87:
      v44 = 5;
      v45 = wk;
      v46 = 4;
LABEL_88:
      sBtlSetMotion(v45, v44, v46, 0, 0);
      v59 = 2;
      goto LABEL_90;
    case 11:
      wk->actaiwk->status = wk->actaiwk->status & 0xFFFFFDE0 | 4;
      *(u64 *)&vct_A.x = 0;
      *(u64 *)&vct_A.z = 0;
      v65 = &wk->mv_spdbk;
      v66 = wk->actaiwk;
      *v65 = vct_A;
      v66->mode = 1;
      v66->frame = 0;
      if (v13 == 9 && !wk->bYobidousa)
      {
        v66->cmpframe = 1;
      }
      else
      {
        v67 = wk->para;
        if (sBtlIsKoufun(v67) && !wk->bYobidousa)
          time = 1;
        wk->actaiwk->cmpframe = time;
      }
      v21 = wk;
      v22 = 2;
LABEL_107:
      v23 = 4;
LABEL_108:
      sBtlSetMotion(v21, v22, v23, 0, 0);
      v59 = 1;
LABEL_90:
      sBtlSetAction(wk, v59, 0);
      return 1;
    default:
      return 1;
  }
}

// 0x1dbf6b0
bool sBtlGetMovePos_MapHit(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, sdfVector4_t *pos, f32 dis, f32 deg, s32 flg) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  _OWORD *p_x;
  u32 v15;
  s32 v16;
  bool v17;
  _OWORD *v18;
  _OWORD *v21;
  s32 v22;
  struct sdfVector4_t v24;
  f32 *v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  sdfVector4_t *v40;
  f32 *v42;
  sdfVector4_t *v45;
  __int128 v52;
  __int128 v53;
  __int128 v54;
  __int128 v55;
  sdfMatrix4_t v56;
  sdfMatrix4_t v57;
  sdfVector4_t v58;
  sdfVector4_t v59;
  sdfVector4_t v61;
  sdfVector4_t v62;
  sdfVector4_t v63;
  sdfVector4_t v64;

  x = wk->rot.x;
  y = wk->rot.y;
  z = wk->rot.z;
  w = wk->rot.w;
  v59.x = x;
  v59.y = y;
  v59.z = z;
  v59.w = w;
  sBtlGetRotateDeg(v59, deg);
  ToMatrix();
  v45 = pos;
  p_x = &vf00.x;
  v15 = 0;
  v16 = 30;
  v17 = 1;
  v52 = p_x[4];
  v53 = p_x[5];
  v54 = p_x[6];
  v55 = p_x[7];
  while (1)
  {
    v21 = &vf00.x;
    v22 = (u8)byte_5755EF5;
    v21[4] = v52;
    v21[5] = v53;
    v21[6] = v54;
    v21[7] = v55;
    if (v22)
    {
      goto LABEL_18;
    }
    else
    {
LABEL_18:
      vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
      goto LABEL_19;
    }
    vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
LABEL_19:
    get_transpose(&v57, &mtx_A, 0);
    v56 = v57;
    v58 = op_Multiply_60923920(&v56, vct_A, 0);
    vct_A = v58;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, dis);
    v24 = wk->pos;
    vct_B = v24;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v25 = &vf00.x;
    v26 = wk->pos.x;
    v27 = wk->pos.y;
    v29 = wk->pos.z;
    v28 = wk->pos.w;
    v30 = v25[4];
    v31 = v25[5];
    v32 = v25[6];
    v33 = v25[7];
    v61.y = v27;
    v61.z = v29;
    v61.w = v28;
    v64.x = v30;
    v64.y = v31;
    v64.z = v32;
    v61.x = v26;
    v64.w = v33;
    if (sBtlCheckMapHit_Cross(v61, v64, dis))
    {
      if (flg != 1)
        break;
      v62.x = v30;
      v62.y = v31;
      v62.z = v32;
      v62.w = v33;
      if (sBtlCheckCrossUnit_HIT(wklock, v62))
        break;
    }
    v36 = wk->rot.x;
    v37 = wk->rot.y;
    v38 = wk->rot.z;
    v39 = wk->rot.w;
    v63.z = v38;
    v63.w = v39;
    v63.x = v36;
    v63.y = v37;
    sBtlGetRotateDeg(v63, (f32)v16 + deg);
    ToMatrix();
    v18 = &vf00.x;
    v17 = v15++ < 0xB;
    v16 += 30;
    v52 = v18[4];
    v53 = v18[5];
    v54 = v18[6];
    v55 = v18[7];
    if (v15 == 12)
      return v17;
  }
  v40 = v45;
  goto LABEL_65;
LABEL_66:
  v42 = &vf00.x;
  v42[4] = v30;
  v42[5] = v31;
  v42[6] = v32;
  v42[7] = v33;
  goto LABEL_67;
LABEL_65:
  goto LABEL_66;
LABEL_67:
  *v40 = vct_A;
  return v17;
}

// 0x1dbfda0
bool sBtlGetMovePos_MapHit_Nakama(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, sdfVector4_t *pos, f32 dis, f32 deg, s32 flg, s32 nakama) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  _OWORD *p_x;
  u32 v17;
  s32 v18;
  bool v19;
  _OWORD *v20;
  _OWORD *v23;
  s32 v24;
  struct sdfVector4_t v26;
  f32 *v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 v41;
  f32 v43;
  sdfVector4_t *v44;
  f32 *v46;
  sdfVector4_t *v49;
  __int128 v56;
  __int128 v57;
  __int128 v58;
  __int128 v59;
  sdfMatrix4_t v60;
  sdfMatrix4_t v61;
  sdfVector4_t v62;
  sdfVector4_t v63;
  sdfVector4_t v65;
  sdfVector4_t v66;
  sdfVector4_t v67;
  sdfVector4_t v68;

  x = wk->rot.x;
  y = wk->rot.y;
  z = wk->rot.z;
  w = wk->rot.w;
  v63.x = x;
  v63.y = y;
  v63.z = z;
  v63.w = w;
  sBtlGetRotateDeg(v63, deg);
  ToMatrix();
  v49 = pos;
  p_x = &vf00.x;
  v17 = 0;
  v18 = 30;
  v19 = 1;
  v56 = p_x[4];
  v57 = p_x[5];
  v58 = p_x[6];
  v59 = p_x[7];
  while (1)
  {
    v23 = &vf00.x;
    v24 = (u8)byte_5755EF5;
    v23[4] = v56;
    v23[5] = v57;
    v23[6] = v58;
    v23[7] = v59;
    if (v24)
    {
      goto LABEL_18;
    }
    else
    {
LABEL_18:
      vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
      goto LABEL_19;
    }
    vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
LABEL_19:
    get_transpose(&v61, &mtx_A, 0);
    v60 = v61;
    v62 = op_Multiply_60923920(&v60, vct_A, 0);
    vct_A = v62;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, dis);
    v26 = wk->pos;
    vct_B = v26;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v27 = &vf00.x;
    v28 = wk->pos.x;
    v29 = wk->pos.y;
    v31 = wk->pos.z;
    v30 = wk->pos.w;
    v32 = v27[4];
    v33 = v27[5];
    v34 = v27[6];
    v35 = v27[7];
    v65.y = v29;
    v65.z = v31;
    v65.w = v30;
    v68.x = v32;
    v68.y = v33;
    v68.z = v34;
    v65.x = v28;
    v68.w = v35;
    if (sBtlCheckMapHit_Cross(v65, v68, dis))
    {
      if (flg != 1)
        break;
      v66.x = v32;
      v66.y = v33;
      v66.z = v34;
      v66.w = v35;
      if (sBtlCheckCrossUnit_HIT(wklock, v66))
        break;
    }
    v38 = wk->rot.x;
    v39 = wk->rot.y;
    v40 = wk->rot.z;
    v41 = wk->rot.w;
    if (nakama)
    {
      v43 = (f32)v18 + deg;
    }
    else
    {
      v43 = deg - (f32)v18;
    }
    v67.x = v38;
    v67.y = v39;
    v67.z = v40;
    v67.w = v41;
    sBtlGetRotateDeg(v67, v43);
    ToMatrix();
    v20 = &vf00.x;
    v19 = v17++ < 0xB;
    v18 += 30;
    v56 = v20[4];
    v57 = v20[5];
    v58 = v20[6];
    v59 = v20[7];
    if (v17 == 12)
      return v19;
  }
  v44 = v49;
  goto LABEL_70;
LABEL_71:
  v46 = &vf00.x;
  v46[4] = v32;
  v46[5] = v33;
  v46[6] = v34;
  v46[7] = v35;
  goto LABEL_72;
LABEL_70:
  goto LABEL_71;
LABEL_72:
  *v44 = vct_A;
  return v19;
}

// 0x1db6e70
bool sBtlGetMovePos_MapHit_2(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *wklock, const sdfVector4_t *pos, f32 dis, f32 deg, s32 flg) {
  void *v8;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  _OWORD *p_x;
  u64 v15;
  bool v16;
  _OWORD *v17;
  _OWORD *v20;
  s32 v21;
  struct sdfVector4_t v23;
  f32 *v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 *v41;
  __int128 v50;
  __int128 v51;
  __int128 v52;
  __int128 v53;
  sdfMatrix4_t v54;
  sdfMatrix4_t v55;
  sdfVector4_t v56;
  sdfVector4_t v57;
  sdfVector4_t v59;
  sdfVector4_t v60;
  sdfVector4_t v61;
  sdfVector4_t v62;

  v8 = NewSpecific(f32, 0x18u);
  InitializeArray_55364416(v8, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__93312F211C9111E8D199CA1F71A38D4FDF69E33DD5A9F940CFE4F624496CB0DF, 0);
  x = wk->rot.x;
  y = wk->rot.y;
  z = wk->rot.z;
  w = wk->rot.w;
  v57.x = x;
  v57.y = y;
  v57.z = z;
  v57.w = w;
  sBtlGetRotateDeg(v57, deg);
  ToMatrix();
  p_x = &vf00.x;
  v15 = 0;
  v16 = 1;
  v50 = p_x[4];
  v51 = p_x[5];
  v52 = p_x[6];
  v53 = p_x[7];
  while (1)
  {
    v20 = &vf00.x;
    v21 = (u8)byte_5755EF5;
    v20[4] = v50;
    v20[5] = v51;
    v20[6] = v52;
    v20[7] = v53;
    if (v21)
    {
      goto LABEL_18;
    }
    else
    {
LABEL_18:
      vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
      goto LABEL_19;
    }
    vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
LABEL_19:
    get_transpose(&v55, &mtx_A, 0);
    v54 = v55;
    v56 = op_Multiply_60923920(&v54, vct_A, 0);
    vct_A = v56;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, dis);
    v23 = wk->pos;
    vct_B = v23;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v24 = &vf00.x;
    v25 = wk->pos.x;
    v26 = wk->pos.y;
    v28 = wk->pos.z;
    v27 = wk->pos.w;
    v29 = v24[4];
    v30 = v24[5];
    v31 = v24[6];
    v32 = v24[7];
    v59.y = v26;
    v59.z = v28;
    v59.w = v27;
    v62.x = v29;
    v62.y = v30;
    v62.z = v31;
    v59.x = v25;
    v62.w = v32;
    if (sBtlCheckMapHit_Cross(v59, v62, dis))
    {
      if (flg != 1)
        break;
      v60.x = v29;
      v60.y = v30;
      v60.z = v31;
      v60.w = v32;
      if (sBtlCheckCrossUnit_HIT(wklock, v60))
        break;
    }
    v35 = wk->rot.x;
    v36 = wk->rot.y;
    v37 = wk->rot.z;
    v38 = wk->rot.w;
    v39 = *((f32 *)&v8[2].klass + v15);
    v61.y = v36;
    v61.z = v37;
    v61.w = v38;
    v61.x = v35;
    sBtlGetRotateDeg(v61, v39 + deg);
    ToMatrix();
    v17 = &vf00.x;
    v16 = v15++ < 0x17;
    v50 = v17[4];
    v51 = v17[5];
    v52 = v17[6];
    v53 = v17[7];
    if (v15 == 24)
      return v16;
  }
  goto LABEL_65;
LABEL_66:
  v41 = &vf00.x;
  v41[4] = v29;
  v41[5] = v30;
  v41[6] = v31;
  v41[7] = v32;
  goto LABEL_67;
LABEL_65:
  goto LABEL_66;
LABEL_67:
  return v16;
}

// 0x1db9d40
bool sBtlAAIProc(SBTLUNIT_WORK *wk) {
  s32 stat;
  u64 *p_klass;
  s64 v8;

  sBtlBS_LASTB1_Action_Set(wk);
  stat = wk->actaiwk->stat;
  if (stat == 2)
  {
    p_klass = &sBtlActAI_AAIProc_Func->obj.klass;
    goto LABEL_18;
  }
  if (stat == 1)
  {
    if (sBtlGetNakama(0) == wk)
    {
      wk->nakamaAtkPos0 = 0;
      goto LABEL_14;
    }
    else
    {
      if (sBtlGetNakama(1) == wk)
      {
        wk->nakamaAtkPos1 = 0;
      }
      goto LABEL_14;
    }
LABEL_14:
    p_klass = &sBtlActAI_AAIInit_Func->obj.klass;
LABEL_18:
    v8 = p_klass[wk->aiwk->mode + 4];
    (*(v8 + 24))(*(u64 *)(v8 + 64), wk, *(u64 *)(v8 + 40));
  }
  return 1;
}

// 0x1dc04a0
bool sBtlAAIInit_None(SBTLUNIT_WORK *wk) {
  return 1;
}

// 0x1dc04b0
bool sBtlAAIInit_Free(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  s32 PlayerID;
  sdfVector4_t *p_mv_spdbk;
  SBTLACTAI_WORK *v9;
  f32 v11;
  struct sdfVector4_t max_mvspd;

  actaiwk = wk->actaiwk;
  actaiwk->mode = 2;
  actaiwk->status = actaiwk->status & 0xFFFFFDE0 | 5;
  PlayerID = sBtlGetPlayerID();
  wk->actaiwk->LockID = PlayerID;
  max_mvspd = wk->max_mvspd;
  vct_A = max_mvspd;
  p_mv_spdbk = &wk->mv_spdbk;
  *p_mv_spdbk = vct_A;
  wk->mv_spdbk.z = 8.0;
  v9 = wk->actaiwk;
  v9->mode = 4;
  *(u64 *)&v9->frame = 0;
  sBtlGetWarpUnit_ID(wk);
  if (wk->miusinai || (wk->aiwk->m_status & 0x40000) != 0)
  {
    if (sBtlNakamaGoalChk(wk))
    {
      wk->mv_spdbk.z = 0.0;
      goto LABEL_27;
    }
  }
  sBtlSetWalk(wk, v11);
LABEL_27:
  wk->actaiwk->stat = 2;
  return 1;
}

// 0x1dc06f0
bool sBtlAAIInit_N_Escape(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  sdfVector4_t *p_mv_spdbk;
  f32 v8;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  s32 v13;
  s32 v15;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v18;
  f32 *p_x;
  f32 v21;
  f32 v22;
  f32 v23;
  _OWORD *v25;
  struct sdfVector4_t v26;
  struct sdfVector4_t v27;
  f32 priv_area_r;
  f32 v30;
  f32 *v31;
  SBTLACTAI_WORK *v32;
  sdfVector4_t *p_ppos;
  s32 v34;
  SBTLACTAI_WORK *v35;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 hit_area_r;
  f32 v41;
  SBTLACTAI_WORK *v42;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 v46;
  f32 dis;
  f32 v48;
  f32 v49;
  f32 v51;
  _OWORD *v53;
  s32 v54;
  f32 v56;
  f32 *v57;
  SBTLACTAI_WORK *v58;
  SBTLACTAI_WORK *v60;
  struct sdfVector4_t v62;
  f32 *v63;
  f32 v64;
  f32 v65;
  f32 v66;
  f32 v68;
  s32 v69;
  f32 v72;
  f32 v73;
  f32 v74;
  f32 pos0;
  f32 v77;
  struct sdfVector4_t max_mvspd;
  struct sdfVector4_t pos;
  struct sdfVector4_t ppos;
  __int128 v88;
  __int128 v89;
  __int128 v90;
  __int128 v91;
  sdfMatrix4_t v92;
  sdfMatrix4_t v93;
  sdfVector4_t v94;
  sdfVector4_t v95;
  sdfVector4_t v96;
  sdfVector4_t v97;
  sdfVector4_t v98;
  sdfVector4_t v99;

  actaiwk = wk->actaiwk;
  actaiwk->status = actaiwk->status & 0xFFFFFDE0 | 0x14;
  actaiwk->mode = 14;
  max_mvspd = wk->max_mvspd;
  vct_A = max_mvspd;
  p_mv_spdbk = &wk->mv_spdbk;
  *p_mv_spdbk = vct_A;
  wk->actaiwk->frame = 0;
  sBtlGetWarpUnit_ID(wk);
  sBtlSetWalk(wk, v8);
  x = wk->rot.x;
  y = wk->rot.y;
  z = wk->rot.z;
  w = wk->rot.w;
  v95.x = x;
  v95.y = y;
  v95.z = z;
  v95.w = w;
  v13 = sBtlGetNearTarget_Random(wk, v95, 4000.0, -1.0, -1.0, 3);
  if (v13 == -1)
  {
    sBtlResetAAI(wk);
    sBtlSetMotion(wk, 0, 0, 0, 0);
    wk->actaiwk->status &= ~0x10u;
    wk->actcounter = wk->actcounter_max;
    return 1;
  }
  v15 = v13;
  UnitMng = wk->UnitMng;
  v18 = sBtlSearchUnit_ID(UnitMng, v15);
  pos = wk->pos;
  vct_A = pos;
  p_x = &vf00.x;
  v21 = p_x[4];
  v22 = p_x[5];
  v23 = p_x[6];
  v77 = p_x[7];
  sub_1949280(0, 0.5235988);
  v25 = &vf00.x;
  v88 = v25[4];
  v89 = v25[5];
  v26 = v18->pos;
  v90 = v25[6];
  v91 = v25[7];
  vct_A = v26;
  vct_B = vct_A;
  v27 = wk->pos;
  vct_A = v27;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  priv_area_r = wk->actaiwk->priv_area_r;
  v30 = priv_area_r * 2.5;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v30);
  v31 = &vf00.x;
  v31[8] = v21;
  v31[9] = v22;
  v31[10] = v23;
  v31[11] = v77;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v32 = wk->actaiwk;
  p_ppos = &v32->ppos;
  v34 = 12;
  v73 = v22;
  v74 = v21;
  v72 = v23;
  *p_ppos = vct_A;
  while (1)
  {
    v35 = wk->actaiwk;
    v36 = v35->ppos.x;
    v37 = v35->ppos.y;
    v38 = v35->ppos.z;
    v39 = v35->ppos.w;
    hit_area_r = v35->hit_area_r;
    v96.x = v36;
    v96.y = v37;
    v96.z = v38;
    v96.w = v39;
    if (!sBtlCheckArea(wk, v96, hit_area_r))
      break;
LABEL_62:
    v51 = 2.5;
    v53 = &vf00.x;
    v54 = (u8)byte_5755EF5;
    v53[4] = v88;
    v53[5] = v89;
    v53[6] = v90;
    v53[7] = v91;
    if (v54)
    {
      goto LABEL_67;
    }
    else
    {
LABEL_67:
      goto LABEL_68;
    }
LABEL_68:
    get_transpose(&v93, &mtx_A, 0);
    v98 = vct_A;
    v92 = v93;
    v94 = op_Multiply_60923920(&v92, v98, 0);
    vct_A = v94;
    v56 = wk->actaiwk->priv_area_r;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v56 * v51);
    v57 = &vf00.x;
    v57[8] = v21;
    v57[9] = v22;
    v57[10] = v23;
    v57[11] = v77;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v58 = wk->actaiwk;
    --v34;
    v58->ppos = vct_A;
    if (!v34)
      goto LABEL_136;
  }
  v41 = wk->pos.x;
  pos0 = wk->pos.y;
  v42 = wk->actaiwk;
  v44 = v42->ppos.x;
  v43 = v42->ppos.y;
  v45 = v42->ppos.z;
  v46 = v42->ppos.w;
  dis = v42->hit_area_r;
  v48 = wk->pos.z;
  v49 = wk->pos.w;
  v97.y = pos0;
  v97.x = v41;
  v97.z = v48;
  v97.w = v49;
  v99.x = v44;
  v99.y = v43;
  v99.z = v45;
  v99.w = v46;
  v22 = v73;
  v21 = v74;
  v23 = v72;
  if (!sBtlCheckMapHit_Cross(v97, v99, dis))
    goto LABEL_62;
LABEL_136:
  v60 = wk->actaiwk;
  v60->stat = 2;
  ppos = v60->ppos;
  goto LABEL_138;
LABEL_139:
  vct_A = ppos;
  v62 = wk->pos;
  goto LABEL_140;
LABEL_141:
  vct_B = v62;
  goto LABEL_142;
LABEL_138:
  goto LABEL_139;
LABEL_140:
  goto LABEL_141;
LABEL_142:
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  goto LABEL_146;
LABEL_147:
  goto LABEL_9007;
LABEL_146:
  v63 = &vf00.x;
  v64 = v63[6];
  v65 = v63[4];
  v66 = v63[5];
  goto LABEL_147;
LABEL_9007:
  v68 = sqrtf((f32)((f32)(v65 * v65) + (f32)(v66 * v66)) + (f32)(v64 * v64)) / wk->mv_spdbk.z;
  v69 = v68;
  if ((u32)(s32)v68 <= 1)
    v69 = 1;
  if (v68 == INFINITY)
    v69 = 0x80000000;
  wk->actaiwk->cmpframe = v69;
  return 1;
}

// 0x1dc14d0
bool sBtlAAIInit_N_Kaihi(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  sdfVector4_t *p_mv_spdbk;
  SBTLACTAI_WORK *v10;
  f32 v12;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 kaihiID;
  SBTLUNIT_WORK *v16;
  SBTLUNIT_WORK *v17;
  s32 v20;
  struct sdfVector4_t pos;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  struct sdfVector4_t v33;
  f32 priv_area_r;
  f32 v36;
  struct sdfVector4_t v37;
  SBTLACTAI_WORK *v38;
  sdfVector4_t *p_ppos;
  f32 v41;
  struct sdfVector4_t pos1;
  sdfVector4_t pos1a;
  f32 pos1d;
  struct sdfVector4_t pos1b;
  struct sdfVector4_t pos1c;
  sdfMatrix4_t v54;
  sdfMatrix4_t v55;
  f32 v56;
  f32 v57;
  sdfVector4_t v58;
  sdfVector4_t v59;
  sdfVector4_t v60;
  sdfVector4_t v61;

  actaiwk = wk->actaiwk;
  actaiwk->status = actaiwk->status & 0xFFFFFDE0 | 0x14;
  actaiwk->mode = 14;
  pos1 = wk->max_mvspd;
  vct_A = pos1;
  p_mv_spdbk = &wk->mv_spdbk;
  v10 = wk->actaiwk;
  *p_mv_spdbk = vct_A;
  *(u64 *)&v10->frame = 0;
  sBtlGetWarpUnit_ID(wk);
  sBtlSetWalk(wk, v12);
  UnitMng = wk->UnitMng;
  kaihiID = wk->actaiwk->kaihiID;
  v16 = sBtlSearchUnit_ID(UnitMng, kaihiID);
  if (!v16)
    goto LABEL_57;
  v17 = v16;
  if (!sBtlCheckDamageTarget(v16))
    goto LABEL_57;
  pos1a = v17->rot;
  vct_A = pos1a;
  ToMatrix();
  v20 = (u8)byte_5756085;
  vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
  if (v20)
  {
    goto LABEL_30;
  }
  else
  {
    goto LABEL_30;
  }
LABEL_30:
  get_transpose(&v55, &mtx_A, 0);
  v59 = vct_A;
  v54 = v55;
  vct_A = op_Multiply_60923920(&v54, v59, 0);
  sub_1949110(0);
  vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, vdupq_n_s32(0x44FA0000u));
  pos = v17->pos;
  vct_B = pos;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  x = v17->pos.x;
  y = v17->pos.y;
  z = v17->pos.z;
  w = v17->pos.w;
  v61 = vct_A;
  pos1d = vct_A.x;
  v41 = vct_A.y;
  v56 = vct_A.w;
  v57 = v61.z;
  v61.w = v56;
  v61.z = v57;
  v61.y = v41;
  v61.x = pos1d;
  v60.x = x;
  v60.y = y;
  *(u64 *)&v58.x = 0;
  v60.z = z;
  v60.w = w;
  sBtlGetVerticalLength_Point(v60, v61, v58);
  pos1b = vct_A;
  v33 = wk->pos;
  vct_A = v33;
  vct_B = pos1b;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  priv_area_r = wk->actaiwk->priv_area_r;
  v36 = priv_area_r + priv_area_r;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v36);
  v37 = wk->pos;
  vct_B = v37;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v38 = wk->actaiwk;
  goto LABEL_62;
LABEL_57:
  pos1c = wk->pos;
  vct_A = pos1c;
  v38 = wk->actaiwk;
LABEL_62:
  p_ppos = &v38->ppos;
  *p_ppos = vct_A;
  wk->actaiwk->stat = 2;
  return 1;
}

// 0x1dc1de0
bool sBtlAAIInit_N_Wait(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  s32 actcounter_max;
  SBTLACTAI_WORK *v6;
  f32 v7;
  f32 v8;
  s32 v9;
  s32 v10;

  actaiwk = wk->actaiwk;
  actaiwk->mode = 2;
  actaiwk->status = actaiwk->status & 0xFFFFFDE0 | 4;
  sBtlSetMotion(wk, 0, 0, 0, 0);
  actcounter_max = wk->actcounter_max;
  v6 = wk->actaiwk;
  v6->stat = 2;
  v6->frame = 0;
  v7 = (f32)actcounter_max * 0.8;
  v8 = (f32)actcounter_max * 1.2;
  if (v7 == INFINITY)
    v9 = 0x80000000;
  else
    v9 = v7;
  if (v8 == INFINITY)
    v10 = 0x80000000;
  else
    v10 = v8;
  v6->cmpframe = GetIntervalRand(v9, v10);
  return 1;
}

// 0x1dc1ee0
bool sBtlAAIInit_N_Sabato(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  s32 status;
  s32 v5;

  actaiwk = wk->actaiwk;
  status = actaiwk->status;
  actaiwk->mode = 2;
  v5 = status & ~ACTAIFLGMASK();
  actaiwk->status = v5;
  sBtlSetMotion(wk, 0, 0, 0, 0);
  wk->actaiwk->stat = 2;
  return 1;
}

// 0x1dc1f90
bool sBtlAAIInit_N_GardeT(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  sdfVector4_t *p_mv_spdbk;
  SBTLACTAI_WORK *v8;
  f32 v10;
  SBTLACTAI_WORK *v11;
  s32 h_serialID;
  SBATTLE_WORK *v14;
  SBTLDMG_HITLISTWORK *hitList;
  SBTLDMG_HITWORK *v16;
  SBTLDMG_HITWORK *v17;
  SBATTLE_WORK *v19;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v22;
  f32 x;
  s64 v26;
  struct sdfVector4_t v28;
  f32 priv_area_r;
  f32 v30;
  f32 v32;
  struct sdfVector4_t v33;
  SBTLACTAI_WORK *v34;
  sdfVector4_t *p_ppos;
  struct sdfVector4_t max_mvspd;
  struct sdfVector4_t pos;

  actaiwk = wk->actaiwk;
  actaiwk->mode = 2;
  actaiwk->status = actaiwk->status & 0xFFFFFDE0 | 0x14;
  actaiwk = wk->actaiwk;
  actaiwk->LockID = -1;
  max_mvspd = wk->max_mvspd;
  vct_A = max_mvspd;
  p_mv_spdbk = &wk->mv_spdbk;
  v8 = wk->actaiwk;
  *p_mv_spdbk = vct_A;
  v8->mode = 14;
  v8->cmpframe = 0;
  v8->frame = 0;
  sBtlGetWarpUnit_ID(wk);
  sBtlSetWalk(wk, v10);
  v11 = wk->actaiwk;
  v11->stat = 2;
  v11 = wk->actaiwk;
  h_serialID = v11->h_serialID;
  v14 = wk;
  hitList = v14->hitList;
  v16 = sBtlSearchHit_SerialID(v14->hitList, h_serialID);
  if (!v16)
    return 1;
  v17 = v16;
  v19 = wk;
  UnitMng = v19->UnitMng;
  playerID = v19->playerID;
  v22 = sBtlSearchUnit_ID(UnitMng, playerID);
  pos = v17->pos;
  vct_A = pos;
  x = vct_A.x;
  v26 = *(u64 *)&vct_A.z;
  vct_A.x = x;
  vct_A.y = 0.0;
  *(u64 *)&vct_A.z = v26;
  v28 = v22->pos;
  vct_B = v28;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  priv_area_r = v22->actaiwk->priv_area_r;
  v30 = wk->actaiwk->priv_area_r;
  v32 = priv_area_r + v30;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v32);
  v33 = v22->pos;
  vct_B = v33;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v34 = wk->actaiwk;
  p_ppos = &v34->ppos;
  *p_ppos = vct_A;
  return 1;
}

// 0x1dc25a0
bool sBtlAAIInit_N_Renkei(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  s32 status;
  s32 v5;
  f32 per;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 Radian;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  sdfVector4_t v24;
  sdfVector4_t v25;
  sdfVector4_t rot;

  actaiwk = wk->actaiwk;
  actaiwk->mode = 2;
  status = actaiwk->status;
  v5 = status & ~ACTAIFLGMASK();
  actaiwk->status = v5;
  sBtlSetMotion(wk, 30, 0, 0, 1);
  per = sBtlSearchUnit_ID(wk->UnitMng, wk->playerID)->pos.x;
  rot = wk->rot;
  x = wk->pos.x;
  y = wk->pos.y;
  z = wk->pos.z;
  w = wk->pos.w;
  v22 = wk->rot.y;
  v23 = wk->rot.x;
  v20 = wk->rot.w;
  v21 = wk->rot.z;
  rot.w = v20;
  rot.z = v21;
  rot.y = v22;
  rot.x = v23;
  v25.x = x;
  v25.y = y;
  v25.z = z;
  v25.w = w;
  *(u64 *)&v24.x = 0;
  Radian = sBtlGetRadian(v25, rot, v24, per);
  wk->rot = vct_A;
  sBtlAddUnitDeg(wk, Radian);
  wk->actaiwk->stat = 2;
  return 1;
}

// 0x1dc27d0
bool sBtlAAIInit_N_Comb_E(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  s32 status;
  s32 v5;
  f32 per;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 Radian;
  SBTLACTAI_WORK *v19;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  sdfVector4_t v25;
  sdfVector4_t v26;
  sdfVector4_t rot;

  actaiwk = wk->actaiwk;
  actaiwk->mode = 2;
  status = actaiwk->status;
  v5 = status & ~ACTAIFLGMASK();
  actaiwk->status = v5;
  sBtlSetMotion(wk, 29, 4, 0, 1);
  per = sBtlSearchUnit_ID(wk->UnitMng, wk->playerID)->pos.x;
  rot = wk->rot;
  x = wk->pos.x;
  y = wk->pos.y;
  z = wk->pos.z;
  w = wk->pos.w;
  v23 = wk->rot.y;
  v24 = wk->rot.x;
  v21 = wk->rot.w;
  v22 = wk->rot.z;
  rot.w = v21;
  rot.z = v22;
  rot.y = v23;
  rot.x = v24;
  v26.x = x;
  v26.y = y;
  v26.z = z;
  v26.w = w;
  *(u64 *)&v25.x = 0;
  Radian = sBtlGetRadian(v26, rot, v25, per);
  wk->rot = vct_A;
  sBtlAddUnitDeg(wk, Radian);
  v19 = wk->actaiwk;
  v19->stat = 2;
  v19->frame = 0;
  return 1;
}

// 0x1dc2a00
bool sBtlAAIInit_N_Comb_R(SBTLUNIT_WORK *wk) {
  return 1;
}

// 0x1dc2a10
bool sBtlAAIInit_N_Return(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  s32 status;
  s32 v5;

  actaiwk = wk->actaiwk;
  status = actaiwk->status;
  actaiwk->mode = 2;
  v5 = status & ~ACTAIFLGMASK();
  actaiwk->status = v5;
  wk->actaiwk->stat = 2;
  return 1;
}

// 0x1dc2a60
bool sBtlAAIInit_Attack(SBTLUNIT_WORK *wk) {
  sdfVector4_t *p_mv_spdbk;
  SBTLACTAI_WORK *actaiwk;
  s32 targetID;
  SBATTLE_WORK *v10;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v12;
  SBTLACTAI_WORK *v14;
  f32 priv_area_r;
  f32 hit_area_r;
  struct sdfVector4_t v18;
  f32 *p_x;
  f32 z;
  f32 x;
  f32 y;
  f32 v23;
  f32 v25;
  f32 v26;
  s32 v27;
  struct sdfVector4_t max_mvspd;
  struct sdfVector4_t pos;

  sBtlGetSkilltbl(wk->actwk->use_skillid);
  wk->actaiwk->status = wk->actaiwk->status & 0xFFFFFDE0 | 4;
  max_mvspd = wk->max_mvspd;
  vct_A = max_mvspd;
  p_mv_spdbk = &wk->mv_spdbk;
  *p_mv_spdbk = vct_A;
  actaiwk = wk->actaiwk;
  actaiwk->mode = 14;
  actaiwk->frame = 0;
  actaiwk->actioncnt = 0;
  actaiwk = wk->actaiwk;
  targetID = actaiwk->targetID;
  v10 = wk;
  UnitMng = v10->UnitMng;
  v12 = sBtlSearchUnit_ID(v10->UnitMng, targetID);
  v14 = wk->actaiwk;
  if (!v12)
  {
    v14->cmpframe = 180;
    goto LABEL_41;
  }
  priv_area_r = v14->priv_area_r;
  pos = v12->pos;
  hit_area_r = v12->actaiwk->hit_area_r;
  vct_A = pos;
  v18 = wk->pos;
  vct_B = v18;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  p_x = &vf00.x;
  z = p_x[6];
  x = p_x[4];
  y = p_x[5];
  v23 = priv_area_r + hit_area_r;
  v25 = sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z));
  v26 = v25 / wk->mv_spdbk.z;
  v27 = v26;
  if (v26 == INFINITY)
    v27 = 0x80000000;
  if (v27 <= 23 && (wk->side & 1) != 0)
    v27 = 24;
  wk->actaiwk->cmpframe = v27;
  if (v25 >= v23)
  {
    sBtlSetWalk(wk, v25);
  }
LABEL_41:
  wk->actaiwk->stat = 2;
  return 1;
}

// 0x1dc2f10
bool sBtlAAIInit_BAttack(SBTLUNIT_WORK *wk) {
  sdfVector4_t *p_mv_spdbk;
  SBTLACTAI_WORK *actaiwk;

  wk->actaiwk->status = wk->actaiwk->status & 0xFFFFFDE0 | 4;
  *(u64 *)&vct_A.x = 0;
  *(u64 *)&vct_A.z = 0;
  p_mv_spdbk = &wk->mv_spdbk;
  actaiwk = wk->actaiwk;
  *p_mv_spdbk = vct_A;
  actaiwk->mode = 14;
  *(u64 *)&actaiwk->frame = 0xB400000000LL;
  sBtlSetMotion(wk, 18, 4, 0, 0);
  sBtlSetAction(wk, 2, 0);
  wk->actaiwk->stat = 2;
  return 1;
}

// 0x1dc30f0
bool sBtlAAIInit_Skl_S(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  s32 v5;
  sdfVector4_t *p_mv_spdbk;
  SBTLACTAI_WORK *v10;

  if ((sBtlGetSkilltbl(wk->actwk->use_skillid)->area & 0x40) != 0 && (wk->side & 2) != 0)
  {
    wk->actaiwk->status = wk->actaiwk->status & 0xFFFFFDE0 | 4;
  }
  else
  {
    wk->actaiwk->status = wk->actaiwk->status & 0xFFFF7DE0 | 0x8004;
    if ((wk->aiwk->scrflag & 0x20000) == 0 || wk->actwk->status != 10)
    {
      sBtlSetAction(wk, 2, 0);
      actaiwk = wk->actaiwk;
      if (!actaiwk->target_frame && !actaiwk->mahaskl_waitframe)
      {
        sBtlSetMotion(wk, 5, 4, 0, 0);
      }
    }
  }
  v5 = (u8)byte_5755EF6;
  vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
  if (v5)
  {
    p_mv_spdbk = &wk->mv_spdbk;
    goto LABEL_20;
  }
  else
  {
    p_mv_spdbk = &wk->mv_spdbk;
    goto LABEL_20;
  }
LABEL_20:
  v10 = wk->actaiwk;
  *p_mv_spdbk = vct_A;
  v10->cmpframe = 240;
  v10 = wk->actaiwk;
  v10->mode = 14;
  v10->frame = 0;
  v10->stat = 2;
  return 1;
}

// 0x1dc3350
bool sBtlAAIInit_SUMMON(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  s32 PlayerID;
  SBTLACTAI_WORK *v10;

  actaiwk = wk->actaiwk;
  actaiwk->mode = 2;
  actaiwk->status = actaiwk->status & 0xFFFFFC00 | 0x164;
  PlayerID = sBtlGetPlayerID();
  wk->actaiwk->LockID = PlayerID;
  *(u64 *)&vct_A.x = 0;
  *(u64 *)&vct_A.z = 0;
  v10 = wk->actaiwk;
  wk->mv_spdbk = vct_A;
  *(u64 *)&v10->frame = 0;
  v10->stat = 2;
  return 1;
}

// 0x1dc3500
bool sBtlAAIInit_N_GuardH(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  s32 v6;
  sdfVector4_t *p_mv_spdbk;
  SBTLACTAI_WORK *v11;

  actaiwk = wk->actaiwk;
  actaiwk->mode = 3;
  *(u64 *)&actaiwk->frame = 0x5A00000000LL;
  v6 = (u8)byte_5755EF6;
  vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
  if (v6)
  {
    p_mv_spdbk = &wk->mv_spdbk;
    goto LABEL_8;
  }
  else
  {
    p_mv_spdbk = &wk->mv_spdbk;
    goto LABEL_8;
  }
LABEL_8:
  v11 = wk->actaiwk;
  *p_mv_spdbk = vct_A;
  v11->status = v11->status & 0xFFFFFDE0 | 4;
  sBtlSetMotion(wk, 29, 0, 0, 0);
  sBtlSetAction(wk, 2, 0);
  wk->actaiwk->stat = 2;
  return 1;
}

// 0x1dc36d0
bool sBtlAAIInit_SAttack(SBTLUNIT_WORK *wk) {
  s32 v5;
  sdfVector4_t *p_mv_spdbk;
  SBTLACTAI_WORK *actaiwk;

  wk->actaiwk->status = wk->actaiwk->status & 0xFFFFFDE0 | 0x205;
  v5 = (u8)byte_5755EF6;
  vct_A = (struct sdfVector4_t)xmmword_3D03EF0;
  if (v5)
  {
    p_mv_spdbk = &wk->mv_spdbk;
    goto LABEL_8;
  }
  else
  {
    p_mv_spdbk = &wk->mv_spdbk;
    goto LABEL_8;
  }
LABEL_8:
  actaiwk = wk->actaiwk;
  *p_mv_spdbk = vct_A;
  actaiwk->mode = 14;
  *(u64 *)&actaiwk->frame = 0x7800000000LL;
  sBtlSetMotion(wk, 5, 4, 0, 0);
  sBtlSetAction(wk, 2, 0);
  wk->actaiwk->stat = 2;
  return 1;
}

// 0x1dc38a0
bool sBtlAAIInit_TurnMV(SBTLUNIT_WORK *wk) {
  sdfVector4_t *p_mv_spdbk;
  SBTLACTAI_WORK *actaiwk;
  struct sdfVector4_t ppos;
  struct sdfVector4_t pos;
  f32 *p_x;
  f32 z;
  f32 x;
  f32 y;
  f32 v14;
  SBTLACTAI_WORK *v15;
  f32 v17;
  s32 v18;

  wk->actaiwk->status = wk->actaiwk->status & 0xFFFFFDE0 | 0x14;
  *(u64 *)&vct_A.x = 0;
  *(u64 *)&vct_A.z = 0;
  p_mv_spdbk = &wk->mv_spdbk;
  actaiwk = wk->actaiwk;
  *p_mv_spdbk = vct_A;
  ppos = actaiwk->ppos;
  vct_A = ppos;
  pos = wk->pos;
  vct_B = pos;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  p_x = &vf00.x;
  z = p_x[6];
  x = p_x[4];
  y = p_x[5];
  v14 = wk->max_mvspd.z;
  v15 = wk->actaiwk;
  v15->frame = 0;
  v17 = sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z)) / v14;
  v18 = v17;
  if (v17 == INFINITY)
    v18 = 0x80000000;
  v15->cmpframe = v18;
  v15->mode = 14;
  sBtlSetMotion(wk, 18, 4, 0, 0);
  sBtlSetAction(wk, 2, 0);
  wk->actaiwk->stat = 2;
  return 1;
}

// 0x1dba950
void sBtlResetMode(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;

  sBtlSetAIWkStat(wk, 1);
  actaiwk = wk->actaiwk;
  actaiwk->stat = 1;
  actaiwk->mode = 0;
}

// 0x1da9990
void sBtlResetAAI(SBTLUNIT_WORK *wk) {
  s32 v5;
  sdfVector4_t *p_mv_spd;
  sdfVector4_t *p_mv_spdbk;
  s32 v8;

  v5 = (u8)byte_5755EF6;
  vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
  if (v5)
  {
    p_mv_spd = &wk->mv_spd;
    goto LABEL_7;
  }
  else
  {
    p_mv_spd = &wk->mv_spd;
LABEL_7:
    *p_mv_spd = vct_A;
    p_mv_spdbk = &wk->mv_spdbk;
    goto LABEL_17;
  }
  v8 = (u8)byte_5755EF6;
  *p_mv_spd = vct_A;
  if (v8)
  {
    p_mv_spdbk = &wk->mv_spdbk;
    goto LABEL_17;
  }
  p_mv_spdbk = &wk->mv_spdbk;
LABEL_17:
  *p_mv_spdbk = vct_A;
  sBtlSetAIWkStat(wk, 1);
  sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
  if ((wk->side & 1) == 0)
  {
LABEL_21:
    wk->NakamaAtkFormationUse = 0;
    return;
  }
  if ((wk->status & 0x40000) == 0)
    goto LABEL_21;
  wk->status |= 0x4000u;
  wk->NakamaAtkFormationUse = 0;
}

// 0x1dc3c80
bool sBtlAAIProc_None(SBTLUNIT_WORK *wk) {
  return 1;
}

// 0x1dc3c90
bool sBtlAAIProc_Free(SBTLUNIT_WORK *wk) {
  u32 v3;
  sdfVector4_t *p_mv_spd;
  s32 *p_frame;
  SBTLACTAI_WORK *actaiwk;
  s32 cmpframe;
  SBTLACTAI_WORK *v11;
  s32 targetID;
  s32 *p_actcnt;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v17;
  SBTLUNIT_WORK *v18;
  f32 priv_area_r;
  f32 z;
  f32 w;
  f32 x;
  f32 y;
  f32 v26;
  f32 v27;
  f32 hit_area_r;
  s32 ListID;
  s32 *v32;
  sdfVector4_t vector2;
  f32 v36;
  struct sdfVector4_t mv_spdbk;
  f32 v38;
  sdfVector4_t v39;

  v3 = wk->status & 0x840000;
  if (v3 == 8650752)
    return v3 != 8650752;
  mv_spdbk = wk->mv_spdbk;
  vct_A = mv_spdbk;
  p_mv_spd = &wk->mv_spd;
  p_frame = &wk->actaiwk->frame;
  *p_mv_spd = vct_A;
  ++*p_frame;
  LimitRange(p_frame, 0, 0x7FFF);
  if ((wk->side & 1) != 0 && !wk->miusinai && (wk->aiwk->m_status & 0x40000) == 0 || (actaiwk = wk->actaiwk, (cmpframe = actaiwk->cmpframe) != 0) && cmpframe <= actaiwk->frame)
  {
    sBtlResetAAI(wk);
    p_actcnt = &wk->aiwk->actcnt;
    LimitRange(p_actcnt, 0, 0x7FFF);
    if (!wk->motionID)
      goto LABEL_36;
    goto LABEL_35;
  }
  v11 = wk->actaiwk;
    if (v11->mode > 11)
  {
LABEL_43:
    targetID = v11->targetID;
    goto LABEL_44;
  }
  targetID = v11->LockID;
  if (wk->battlemode != 3 && (wk->side & 0x80) != 0)
  {
    v11 = wk->actaiwk;
    goto LABEL_43;
  }
LABEL_44:
  UnitMng = wk->UnitMng;
  v17 = sBtlSearchUnit_ID(UnitMng, targetID);
  if (v17)
  {
    v18 = v17;
    if (sBtlCheckExist(v18))
    {
      if (!wk->miusinai && (wk->aiwk->m_status & 0x40000) == 0)
      {
        priv_area_r = wk->actaiwk->priv_area_r;
        v39.x = wk->pos.x;
        v39.y = wk->pos.y;
        z = wk->pos.z;
        w = wk->pos.w;
        x = v18->pos.x;
        y = v18->pos.y;
        v27 = v18->pos.z;
        v26 = v18->pos.w;
        hit_area_r = v18->actaiwk->hit_area_r;
        v36 = wk->pos.y;
        v38 = wk->pos.x;
        v39.y = v36;
        v39.x = v38;
        v39.z = z;
        v39.w = w;
        *(u64 *)&vector2.z = __PAIR64__(LODWORD(v26), LODWORD(v27));
        *(u64 *)&vector2.x = __PAIR64__(LODWORD(y), LODWORD(x));
        if (!sBtlCheckCrossCircle(v39, priv_area_r, vector2, hit_area_r))
          return v3 != 8650752;
        ListID = v18->ListID;
        if (ListID == wk->playerID && v18->mv_spd.z > 0.0)
          return v3 != 8650752;
LABEL_65:
        sBtlResetAAI(wk);
        v32 = &wk->aiwk->actcnt;
        LimitRange(v32, 0, 0x7FFF);
        if (!wk->motionID)
          goto LABEL_36;
LABEL_35:
        sBtlSetMotion(wk, 0, 4, 0, 0);
LABEL_36:
        wk->actaiwk->status &= ~1u;
        return v3 != 8650752;
      }
      if (sBtlNakamaGoalChk(wk))
      {
        wk->mv_spdbk.z = 0.0;
        goto LABEL_65;
      }
      if (wk->mv_spdbk.z < 1.0)
      {
        sBtlSetAIWkStat(wk, 1);
      }
    }
  }
  return v3 != 8650752;
}

// 0x1dc4200
bool sBtlAAIProc_N_Wait(SBTLUNIT_WORK *wk) {
  u32 status;
  s32 v4;
  s32 *p_frame;
  SBTLACTAI_WORK *actaiwk;
  s32 cmpframe;

  status = wk->status;
  wk->NakamaAtkFormationUse = 0;
  v4 = status & 0x840000;
  if ((status & 0x840000) != 0x840000)
  {
    p_frame = &wk->actaiwk->frame;
    ++*p_frame;
    LimitRange(p_frame, 0, 0x7FFF);
    actaiwk = wk->actaiwk;
    cmpframe = actaiwk->cmpframe;
    if (cmpframe && cmpframe <= actaiwk->frame)
    {
      sBtlResetAAI(wk);
      sBtlSetMotion(wk, 0, 4, 0, 0);
      wk->actcounter = wk->actcounter_max;
    }
  }
  return v4 != 8650752;
}

// 0x1dc4330
bool sBtlAAIProc_N_Sabato(SBTLUNIT_WORK *wk) {
  s16 *p_actcounter;
  s16 actcounter_max;

  p_actcounter = &wk->actcounter;
  ++wk->actcounter;
  actcounter_max = wk->actcounter_max;
  LimitRange_2(p_actcounter, 0, actcounter_max);
  return 1;
}

// 0x1dc43c0
bool sBtlAAIProc_N_Renkei(SBTLUNIT_WORK *wk) {
  s16 actcounter_max;
  SBATTLE_WORK *v6;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;

  actcounter_max = wk->actcounter_max;
  ++wk->actcounter;
  LimitRange_2(&wk->actcounter, 0, actcounter_max);
  v6 = wk;
  UnitMng = v6->UnitMng;
  playerID = v6->playerID;
  if (sBtlSearchUnit_ID(UnitMng, playerID)->actwk->status <= 2)
  {
    sBtlStatusBitOff(wk, 0xFFFFBFEF);
    sBtlResetAAI(wk);
    sBtlSetMotion(wk, 0, 4, 0, 0);
  }
  return 1;
}

// 0x1dc4540
bool sBtlAAIProc_N_Comb_E(SBTLUNIT_WORK *wk) {
  return 1;
}

// 0x1dc4550
bool sBtlAAIProc_N_Comb_R(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  s32 status;
  SBTLAI_WORK *aiwk;
  u32 m_status;
  SBTLUNIT_WORK *pNakama1;
  SBTLUNIT_WORK *v16;
  SBTLUNIT_WORK *v17;

  v4 = wk;
  UnitMng = v4->UnitMng;
  playerID = v4->playerID;
  status = sBtlSearchUnit_ID(UnitMng, playerID)->actaiwk->status;
  if ((status & 0x4000) != 0)
    return (status & 0x4000) == 0;
  sBtlSetMode(2);
  sBtlStatusBitOff(wk, 0xFFFFBFEF);
  sBtlResetAAI(wk);
  aiwk = wk->aiwk;
  m_status = aiwk->m_status;
  if ((m_status & 0x40000) != 0)
  {
    aiwk->m_status = m_status & 0xFFFBFFFF;
    aiwk->mode = 0;
    goto LABEL_15;
  }
  aiwk->mode = 0;
LABEL_15:
  sBtlSetMotion(wk, 0, 4, 0, 0);
  pNakama1 = wk->cmbSkl->pNakama1;
  if (pNakama1)
  {
    sBtlStatusBitOff(pNakama1, 0xFFFFBFEF);
    v16 = wk->cmbSkl->pNakama1;
    sBtlResetAAI(v16);
    v17 = wk->cmbSkl->pNakama1;
    v17->aiwk->mode = 0;
    sBtlSetMotion(v17, 0, 4, 0, 0);
    return (status & 0x4000) == 0;
  }
  return (status & 0x4000) == 0;
}

// 0x1dc47d0
bool sBtlAAIProc_N_Return(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v3;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v6;
  SBTLUNIT_WORK *v7;

  v3 = wk;
  UnitMng = v3->UnitMng;
  playerID = v3->playerID;
  v6 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (!v6)
    return 1;
  v7 = v6;
  if (!sBtlCheckDamageTarget(v6))
    return 1;
  sBtlSetReturn(v7, 0);
  return 1;
}

// 0x1dc4900
bool sBtlAAIProc_N_Escape(SBTLUNIT_WORK *wk) {
  u32 v3;
  sdfVector4_t *p_mv_spd;
  s32 *p_frame;
  SBTLACTAI_WORK *actaiwk;
  s32 cmpframe;
  s32 mode;
  f32 y;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v26;
  f32 v27;
  struct sdfVector4_t v31;
  SBTLACTAI_WORK *v32;
  sdfVector4_t *p_ppos;
  s32 v36;
  struct sdfVector4_t pos;
  f32 z;
  f32 w;
  struct sdfVector4_t rot;
  s32 v43;
  f32 hit_area_r;
  f32 v48;
  f32 *p_x;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 VerticalLength;
  SBTLACTAI_WORK *v55;
  f32 x;
  s32 v59;
  sdfVector4_t vector2;
  f32 v62;
  f32 v63;
  struct sdfVector4_t vector1;
  f32 vector1c;
  sdfVector4_t vector1a;
  s64 vector1b;
  sdfVector4_t vector1d;
  sdfMatrix4_t v74;
  sdfMatrix4_t v75;
  f32 pos0;
  sdfVector4_t v77;
  sdfVector4_t v78;
  sdfVector4_t v79;
  sdfVector4_t v80;
  sdfVector4_t v81;
  sdfVector4_t v84;
  sdfVector4_t v85;
  sdfVector4_t v86;
  sdfVector4_t v87;

  v3 = wk->status & 0x840000;
  if (v3 == 8650752)
    return v3 != 8650752;
  vector1 = wk->mv_spdbk;
  vct_A = vector1;
  p_mv_spd = &wk->mv_spd;
  p_frame = &wk->actaiwk->frame;
  *p_mv_spd = vct_A;
  ++*p_frame;
  LimitRange(p_frame, 0, 0x7FFF);
  actaiwk = wk->actaiwk;
  cmpframe = actaiwk->cmpframe;
  if (cmpframe && cmpframe <= actaiwk->frame)
    goto LABEL_80;
  mode = actaiwk->mode;
  if (mode == 2)
  {
    *(u64 *)&vct_A.x = 0;
    *(u64 *)&vct_A.z = 0;
    v36 = (u8)byte_5755EF5;
    *p_mv_spd = vct_A;
    pos = wk->pos;
    if (v36)
      goto LABEL_51;
    goto LABEL_91;
    if (v59)
    {
LABEL_51:
      goto LABEL_52;
    }
LABEL_91:
    vector1d = pos;
    pos = vector1d;
LABEL_52:
    vct_A = pos;
    z = vct_A.z;
    w = vct_A.w;
    vector1b = *(u64 *)&vct_A.x;
    rot = wk->rot;
    vct_A = rot;
    ToMatrix();
    v43 = (u8)byte_5756085;
    vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
    get_transpose(&v75, &mtx_A, 0);
    v74 = v75;
    vct_A = op_Multiply_60923920(&v74, vct_A, 0);
    sub_1949110(0);
    hit_area_r = wk->actaiwk->hit_area_r;
    v62 = wk->actaiwk->hit_area_r;
    hit_area_r = v62;
    v63 = hit_area_r;
    hit_area_r = v63;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, hit_area_r);
    vct_B.z = z;
    vct_B.w = w;
    *(u64 *)&vct_B.x = vector1b;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    LODWORD(v84.x) = vector1b;
    pos0 = w;
    v48 = z;
    p_x = &vf00.x;
    v50 = p_x[4];
    v52 = p_x[6];
    v51 = p_x[7];
    LODWORD(v84.x) = vector1b;
    v84.w = pos0;
    v84.y = 0.0;
    v86.y = 0.0;
    v84.z = v48;
    v86.x = v50;
    *(u64 *)&v77.x = 0;
    v86.z = v52;
    v86.w = v51;
    VerticalLength = sBtlGetVerticalLength(v84, v86, v77);
    v55 = wk->actaiwk;
    if (VerticalLength > (f32)(v55->hit_area_r * 0.3))
      return v3 != 8650752;
    x = v55->ppos.x;
    v85.w = pos0;
    v85.y = 0.0;
    v87.y = 0.0;
    v85.z = v48;
    v87.x = v50;
    *(u64 *)&v78.x = 0;
    v87.z = v52;
    v87.w = v51;
    LODWORD(v85.x) = vector1b;
    if (!sBtlCheckInner(v85, v87, v78, x))
      return v3 != 8650752;
LABEL_80:
    sBtlResetAAI(wk);
    sBtlSetMotion(wk, 0, 0, 0, 0);
    wk->actaiwk->status &= ~0x10u;
    wk->actcounter = wk->actcounter_max;
    return v3 != 8650752;
  }
  if (mode == 14)
  {
    v80.x = wk->pos.x;
    y = wk->pos.y;
    v14 = wk->pos.z;
    v15 = wk->pos.w;
    v16 = actaiwk->hit_area_r;
    v17 = actaiwk->ppos.x;
    v18 = actaiwk->ppos.y;
    v20 = actaiwk->ppos.z;
    v19 = actaiwk->ppos.w;
    vector1c = wk->pos.x;
    v80.x = vector1c;
    v80.y = y;
    v80.z = v14;
    v80.w = v15;
    *(u64 *)&vector2.z = __PAIR64__(LODWORD(v19), LODWORD(v20));
    *(u64 *)&vector2.x = __PAIR64__(LODWORD(v18), LODWORD(v17));
    if (sBtlCheckCrossCircle(v80, v16, vector2, 30.0))
    {
      wk->actaiwk->mode = 2;
      v21 = wk->rot.x;
      v22 = wk->rot.y;
      v23 = wk->rot.z;
      v24 = wk->rot.w;
      v81.x = v21;
      v81.y = v22;
      v81.z = v23;
      v81.w = v24;
      sBtlGetRotateDeg(v81, 180.0);
      v26 = wk->actaiwk->hit_area_r;
      vector1a = vct_A;
      v27 = -v26;
      *(u64 *)&vct_B.x = 0;
      vct_B.z = v27;
      vct_B.w = 0.0;
      vct_A = vector1a;
      ToMatrix();
      get_transpose(&v75, &mtx_A, 0);
      *(_OWORD *)&v74.m00 = *(_OWORD *)&v75.m00;
      *(_OWORD *)&v74.m01 = *(_OWORD *)&v75.m01;
      *(_OWORD *)&v74.m02 = *(_OWORD *)&v75.m02;
      *(_OWORD *)&v74.m03 = *(_OWORD *)&v75.m03;
      v79 = op_Multiply_60923920(&v74, vct_B, 0);
      vct_B = v79;
      v31 = wk->pos;
      vct_A = v31;
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v32 = wk->actaiwk;
      p_ppos = &v32->ppos;
      *p_ppos = vct_A;
      return v3 != 8650752;
    }
  }
  return v3 != 8650752;
}

// 0x1dc53a0
bool sBtlAAIProc_N_Kaihi(SBTLUNIT_WORK *wk) {
  s16 actcounter_max;
  u32 v5;
  sdfVector4_t *p_mv_spd;
  s32 *p_frame;
  SBTLACTAI_WORK *actaiwk;
  s32 cmpframe;
  s32 mode;
  f32 y;
  f32 z;
  f32 w;
  f32 hit_area_r;
  f32 x;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  long f64 v27;
  long f64 v28;
  SBTLAI_WORK *aiwk;
  s32 *p_actcnt;
  s32 v35;
  struct sdfVector4_t pos;
  f32 v38;
  f32 v39;
  struct sdfVector4_t rot;
  s32 v42;
  f32 v44;
  f32 *p_x;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 VerticalLength;
  SBTLACTAI_WORK *v53;
  f32 v54;
  SBTLAI_WORK *v56;
  s32 v58;
  sdfVector4_t vector2;
  f32 pos0a;
  f32 pos0b;
  f32 pos0;
  struct sdfVector4_t vector1;
  f32 vector1b;
  s64 vector1a;
  sdfVector4_t vector1c;
  s64 v70;
  s64 v71;
  sdfMatrix4_t v72;
  sdfMatrix4_t v73;
  sdfVector4_t v74;
  sdfVector4_t v75;
  sdfVector4_t v76;
  sdfVector4_t v77;
  sdfVector4_t v79;
  sdfVector4_t v80;
  sdfVector4_t v81;
  sdfVector4_t v82;

  actcounter_max = wk->actcounter_max;
  ++wk->actcounter;
  v70 = 0;
  v71 = 0;
  LimitRange_2(&wk->actcounter, 0, actcounter_max);
  v5 = wk->status & 0x840000;
  if (v5 == 8650752)
    return v5 != 8650752;
  vector1 = wk->mv_spdbk;
  vct_A = vector1;
  p_mv_spd = &wk->mv_spd;
  p_frame = &wk->actaiwk->frame;
  *p_mv_spd = vct_A;
  ++*p_frame;
  LimitRange(p_frame, 0, 0x7FFF);
  actaiwk = wk->actaiwk;
  cmpframe = actaiwk->cmpframe;
  if (cmpframe && cmpframe <= actaiwk->frame || wk->actcounter >= wk->actcounter_max)
  {
    aiwk = wk->aiwk;
    if (aiwk->backmode)
    {
      aiwk->mode = aiwk->backmode;
      aiwk->backmode = 0;
      aiwk->stat = 2;
LABEL_28:
      actaiwk->stat = 1;
      return v5 != 8650752;
    }
    sBtlResetAAI(wk);
    p_actcnt = &wk->aiwk->actcnt;
    LimitRange(p_actcnt, 0, 0x7FFF);
    goto LABEL_40;
  }
  mode = actaiwk->mode;
  if (mode != 2)
  {
    if (mode == 14)
    {
      v76.x = wk->pos.x;
      y = wk->pos.y;
      z = wk->pos.z;
      w = wk->pos.w;
      hit_area_r = actaiwk->hit_area_r;
      x = actaiwk->ppos.x;
      v20 = actaiwk->ppos.y;
      v22 = actaiwk->ppos.z;
      v21 = actaiwk->ppos.w;
      vector1b = wk->pos.x;
      v76.x = vector1b;
      v76.y = y;
      v76.z = z;
      v76.w = w;
      *(u64 *)&vector2.z = __PAIR64__(LODWORD(v21), LODWORD(v22));
      *(u64 *)&vector2.x = __PAIR64__(LODWORD(v20), LODWORD(x));
      if (sBtlCheckCrossCircle(v76, hit_area_r, vector2, 30.0))
      {
        wk->actaiwk->mode = 2;
        v23 = wk->rot.x;
        v24 = wk->rot.y;
        v25 = wk->rot.z;
        v26 = wk->rot.w;
        v77.x = v23;
        v77.y = v24;
        v77.z = v25;
        v77.w = v26;
        sBtlGetRotateDeg(v77, 180.0);
        sub_1B335A0(&v70, 0, v27);
        sub_1B33360(0, 0.0, 0.0, -wk->actaiwk->hit_area_r, 0.0);
        sub_1B332C0(0, *(f32 *)&v70, *((f32 *)&v70 + 1), *(f32 *)&v71, *((f32 *)&v71 + 1));
        ToMatrix();
        (loc_1DCC8D0)(0);
        sub_1B332C0(0, wk->pos.x, wk->pos.y, wk->pos.z, wk->pos.w);
        *(__n128 *)&v28 = sub_1B33520(0);
        sub_1B335A0(&wk->actaiwk->ppos, 0, v28);
      }
    }
    return v5 != 8650752;
  }
  *(u64 *)&vct_A.x = 0;
  *(u64 *)&vct_A.z = 0;
  v35 = (u8)byte_5755EF5;
  *p_mv_spd = vct_A;
  pos = wk->pos;
  if (v35)
    goto LABEL_48;
  goto LABEL_86;
  if (v58)
  {
LABEL_48:
    goto LABEL_49;
  }
LABEL_86:
  vector1c = pos;
  pos = vector1c;
LABEL_49:
  vct_A = pos;
  v39 = vct_A.z;
  v38 = vct_A.w;
  vector1a = *(u64 *)&vct_A.x;
  rot = wk->rot;
  vct_A = rot;
  ToMatrix();
  v42 = (u8)byte_5756085;
  vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
  get_transpose(&v73, &mtx_A, 0);
  v72 = v73;
  vct_A = op_Multiply_60923920(&v72, vct_A, 0);
  sub_1949110(0);
  v44 = wk->actaiwk->hit_area_r;
  pos0a = wk->actaiwk->hit_area_r;
  v44 = pos0a;
  pos0b = v44;
  v44 = pos0b;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v44);
  vct_B.z = v39;
  vct_B.w = v38;
  *(u64 *)&vct_B.x = vector1a;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  LODWORD(v79.x) = vector1a;
  pos0 = v38;
  p_x = &vf00.x;
  v48 = p_x[4];
  v49 = p_x[6];
  v50 = p_x[7];
  LODWORD(v79.x) = vector1a;
  v79.w = pos0;
  v79.y = 0.0;
  v81.y = 0.0;
  v79.z = v39;
  v81.x = v48;
  *(u64 *)&v74.x = 0;
  v81.z = v49;
  v81.w = v50;
  VerticalLength = sBtlGetVerticalLength(v79, v81, v74);
  v53 = wk->actaiwk;
  if (VerticalLength <= (f32)(v53->hit_area_r * 0.3))
  {
    v54 = v53->ppos.x;
    v80.w = pos0;
    v80.y = 0.0;
    v82.y = 0.0;
    v80.z = v39;
    v82.x = v48;
    *(u64 *)&v75.x = 0;
    v82.z = v49;
    v82.w = v50;
    LODWORD(v80.x) = vector1a;
    if (sBtlCheckInner(v80, v82, v75, v54))
    {
      v56 = wk->aiwk;
      if (v56->backmode)
      {
        v56->mode = v56->backmode;
        v56->backmode = 0;
        v56->stat = 2;
        actaiwk = wk->actaiwk;
        goto LABEL_28;
      }
      sBtlResetAAI(wk);
      wk->aiwk->mode = 12;
LABEL_40:
      sBtlSetMotion(wk, 0, 4, 0, 0);
      wk->actaiwk->status &= ~0x10u;
    }
  }
  return v5 != 8650752;
}

// 0x1dc5d40
bool sBtlAAIProc_N_GardeT(SBTLUNIT_WORK *wk) {
  u32 v3;
  sdfVector4_t *p_mv_spd;
  s32 *p_frame;
  SBTLACTAI_WORK *actaiwk;
  s32 cmpframe;
  f32 y;
  f32 z;
  f32 w;
  f32 hit_area_r;
  f32 x;
  f32 v17;
  f32 v18;
  f32 v19;
  s32 *p_actcnt;
  sdfVector4_t vector2;
  struct sdfVector4_t vector1;
  f32 vector1a;
  sdfVector4_t v25;

  v3 = wk->status & 0x840000;
  if (v3 != 8650752)
  {
    vector1 = wk->mv_spdbk;
    vct_A = vector1;
    p_mv_spd = &wk->mv_spd;
    p_frame = &wk->actaiwk->frame;
    *p_mv_spd = vct_A;
    ++*p_frame;
    LimitRange(p_frame, 0, 0x7FFF);
    actaiwk = wk->actaiwk;
    cmpframe = actaiwk->cmpframe;
    if (cmpframe && cmpframe <= actaiwk->frame)
      goto LABEL_33;
    if (actaiwk->mode == 14)
    {
      v25.x = wk->pos.x;
      y = wk->pos.y;
      z = wk->pos.z;
      w = wk->pos.w;
      hit_area_r = actaiwk->hit_area_r;
      x = actaiwk->ppos.x;
      v17 = actaiwk->ppos.y;
      v19 = actaiwk->ppos.z;
      v18 = actaiwk->ppos.w;
      vector1a = wk->pos.x;
      v25.x = vector1a;
      v25.y = y;
      v25.z = z;
      v25.w = w;
      *(u64 *)&vector2.z = __PAIR64__(LODWORD(v18), LODWORD(v19));
      *(u64 *)&vector2.x = __PAIR64__(LODWORD(v17), LODWORD(x));
      if (sBtlCheckCrossCircle(v25, hit_area_r, vector2, 10.0))
      {
LABEL_33:
        sBtlResetAAI(wk);
        p_actcnt = &wk->aiwk->actcnt;
        LimitRange(p_actcnt, 0, 0x7FFF);
        sBtlSetMotion(wk, 0, 4, 0, 0);
      }
    }
    return v3 != 8650752;
  }
  return v3 != 8650752;
}

// 0x1dc6030
bool sBtlAAIProc_Attack(SBTLUNIT_WORK *wk) {
  f32 *p_x;
  f32 v7;
  f32 v8;
  f32 v9;
  s32 *p_frame;
  SBTLACTAI_WORK *actaiwk;
  s32 cmpframe;
  sdfVector4_t *p_mv_spd;
  SBTLACTION_WORK *actwk;
  SBTLSKILLP_TBL *Skilltbl;
  s32 mode;
  SBTLSKILLP_TBL *v19;
  SBTLACTAI_WORK *v20;
  s32 targetID;
  dds3ModelHandle_t *hModel;
  SBTLACTAI_WORK *v24;
  SBTLAI_WORK *aiwk;
  s32 *p_actcnt;
  s32 actcnt;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v31;
  SBTLAI_WORK *v34;
  s32 motionID;
  SBTLACTAI_WORK *v39;
  s32 use_skillid;
  f32 y;
  SBTLUNIT_WORK *v42;
  f32 v43;
  f32 ABS;
  f32 v47;
  s32 encountno;
  SBTLAI_WORK *v51;
  u32 v52;
  SBTLAI_WORK *v53;
  u32 status;
  SBTLPNL_SETDATA *v56;
  s32 v57;
  s32 v58;
  SBTLUNIT_WORK *v59;
  f32 x;
  f32 z;
  f32 v62;
  f32 v63;
  SBTLPNL_SETDATA *data;
  s32 SmnNo;
  SBTLACTAI_WORK *v69;
  struct sdfVector4_t pos;
  struct sdfVector4_t mv_spdbk;

  if (wk->actaiwk->mode == 14)
  {
    pos = wk->pos;
    goto LABEL_4;
  }
  wk->NakamaAtkFormationUse = 0;
  pos = wk->pos;
LABEL_4:
  vct_A = pos;
  p_x = &vf00.x;
  v7 = p_x[6];
  v9 = p_x[4];
  v8 = p_x[5];
  p_frame = &wk->actaiwk->frame;
  ++*p_frame;
  LimitRange(p_frame, 0, 0x7FFF);
  if ((wk->side & 1) != 0)
  {
    actaiwk = wk->actaiwk;
    cmpframe = actaiwk->cmpframe;
    if (cmpframe)
    {
      if (cmpframe <= actaiwk->frame)
      {
        sBtlResetAAI(wk);
LABEL_61:
        if (!wk->motionID)
          return 1;
        goto LABEL_62;
      }
    }
  }
  mv_spdbk = wk->mv_spdbk;
  vct_A = mv_spdbk;
  p_mv_spd = &wk->mv_spd;
  actwk = wk->actwk;
  *p_mv_spd = vct_A;
  Skilltbl = sBtlGetSkilltbl(actwk->use_skillid);
  mode = wk->actaiwk->mode;
  if (mode == 16)
  {
    hModel = wk->hModel;
    if (hModel)
    {
      if ((mdlGetMotionFrame(hModel) & 0x80000000) == 0)
      {
        v24 = wk->actaiwk;
        *(u64 *)&v24->frame = 0;
        v24->mode = 15;
        sBtlCheckMHTData(wk, wk->actwk->use_skillid);
      }
    }
    return 1;
  }
  if (mode == 15)
  {
    if (sBtlCheckStatus_Move(wk))
    {
      sBtlResetAAI(wk);
      aiwk = wk->aiwk;
      actcnt = aiwk->actcnt;
      p_actcnt = &aiwk->actcnt;
      *p_actcnt = actcnt + 1;
      LimitRange(p_actcnt, 0, 0x7FFF);
    }
    return 1;
  }
  if (mode != 14)
    return 1;
  v19 = Skilltbl;
  v20 = wk->actaiwk;
    if (v20->mode > 11)
  {
LABEL_65:
    targetID = v20->targetID;
    goto LABEL_66;
  }
  targetID = v20->LockID;
  if (wk->battlemode != 3 && (wk->side & 0x80) != 0)
  {
    v20 = wk->actaiwk;
    goto LABEL_65;
  }
LABEL_66:
  UnitMng = wk->UnitMng;
  v31 = sBtlSearchUnit_ID(UnitMng, targetID);
  if (v31)
    goto LABEL_70;
  if ((u32)sub_1905740(100, 0) > 0x31)
    goto LABEL_79;
  v53 = wk->aiwk;
  status = v53->status;
  if ((status & 1) == 0)
    goto LABEL_148;
  goto LABEL_145;
  if ((status & 1) == 0)
  {
LABEL_148:
    sBtlResetAAI(wk);
    sBtlSetAIWkStat(wk, 1);
    v69 = wk->actaiwk;
    v69->mode = 0;
    v69->stat = 1;
    wk->aiwk->mode = 12;
    ResetAction(wk, 0, 0);
    wk->actaiwk->tgt_nullmode = 1;
    goto LABEL_155;
  }
LABEL_145:
  v53->meirei_nobk = 7;
  v53->status = status & 0xFFFFFFF6;
  data = wk->panelwk->data;
  SmnNo = sBtlGetSmnNo(wk);
  wk->NakamaAtkFormationUse = 0;
  data[SmnNo]->meirei_no = 7;
  wk->aiwk->status &= ~0x10u;
  goto LABEL_148;
LABEL_70:
  if ((wk->side & 1) == 0)
    goto LABEL_71;
  y = v31->pos.y;
  v42 = v31;
  v43 = wk->pos.y;
  ABS = sBtlGetABS(v43 - y);
  v47 = ABS;
  encountno = wk->encountno;
  if (encountno <= 30)
  {
    if (encountno != 25 && encountno != 30)
      goto LABEL_71;
  }
  else
  {
    if (encountno == 60)
      goto LABEL_137;
    if (encountno != 53)
      goto LABEL_71;
  }
  x = wk->pos.x;
  z = wk->pos.z;
  v62 = v42->pos.x;
  v63 = v42->pos.z;
  if (sBtlGetLenXZ(x, z, v62, v63) < 500.0)
  {
LABEL_137:
    if (v47 > 200.0)
    {
      sBtlResetNakamaAction(wk);
      sBtlResetAAI(wk);
      sBtlResetMode(wk);
      wk->aiwk->mode = 12;
      ResetAction(wk, 0, 0);
      goto LABEL_155;
    }
  }
LABEL_71:
  wk->actaiwk->tgt_nullmode = 0;
  if ((v19->area & 0x40) == 0 && (wk->status & 0x2000000) == 0 && (wk->side & 2) == 0)
  {
    sBtlGotoAtkPos(wk, 1);
    return 1;
  }
LABEL_79:
  if ((wk->flg & 8) == 0 && (v19->flg & 0x224) == 0 && (wk->side & 1) != 0)
  {
    v34 = wk->aiwk;
    if (v34->atkCnt)
    {
      if (wk->actwk->use_skillid == v34->dfltOdrSkl && wk->actaiwk->targetID != -1)
      {
        motionID = wk->motionID;
        *(u64 *)&wk->mv_spd.x = 0;
        wk->mv_spd.z = 0.0;
        if (!motionID)
          return 1;
LABEL_62:
LABEL_155:
        v59 = wk;
        v58 = 0;
        goto LABEL_156;
      }
    }
  }
  *(u64 *)&vct_A.x = 0;
  *(u64 *)&vct_A.z = 0;
  wk->mv_spdbk = vct_A;
  if (sBtlCheckCost(wk, 1))
  {
    v39 = wk->actaiwk;
    *(u64 *)&v39->frame = 0;
    v39->status = v39->status & 0xFFFFFDE0 | 4;
    v39->mode = 16;
    use_skillid = wk->actwk->use_skillid;
    sBtlSetUseSkill(wk, use_skillid, 0);
    return 1;
  }
  sBtlSetNoMP(wk);
  sBtlResetAAI(wk);
  v51 = wk->aiwk;
  v52 = v51->status;
  if ((v52 & 1) == 0)
  {
    if (wk->actaiwk->mode != 14)
      return 1;
LABEL_125:
    if (wk->pos.x != v9 || wk->pos.y != v8 || wk->pos.z != v7)
    {
      if (wk->motionID == 5)
        return 1;
      v58 = 5;
      v59 = wk;
LABEL_156:
      sBtlSetMotion(v59, v58, 4, 0, 0);
      return 1;
    }
    goto LABEL_61;
  }
  v51->meirei_nobk = 7;
  v51->status = v52 & 0xFFFFFFF6;
  v56 = wk->panelwk->data;
  v57 = sBtlGetSmnNo(wk);
  wk->NakamaAtkFormationUse = 0;
  v56[v57]->meirei_no = 7;
  wk->aiwk->status &= ~0x10u;
  if (wk->actaiwk->mode == 14)
    goto LABEL_125;
  return 1;
}

// 0x1dc6bc0
bool sBtlAAIProc_BAttack(SBTLUNIT_WORK *wk) {
  SBTLSKILLP_TBL *Skilltbl;
  s32 *p_frame;
  SBTLACTAI_WORK *actaiwk;
  s32 cmpframe;
  sdfVector4_t *p_mv_spd;
  SBTLACTAI_WORK *v11;
  s32 mode;
  SBTLAI_WORK *v13;
  SBTLACTAI_WORK *v15;
  s32 status;
  SBTLAI_WORK *aiwk;
  s32 *p_actcnt;
  s32 actcnt;
  SBTLAI_WORK *v24;
  u32 v25;
  SBTLPNL_SETDATA *data;
  s32 SmnNo;
  struct sdfVector4_t mv_spdbk;

  Skilltbl = sBtlGetSkilltbl(wk->actwk->use_skillid);
  p_frame = &wk->actaiwk->frame;
  ++*p_frame;
  LimitRange(p_frame, 0, 0x7FFF);
  actaiwk = wk->actaiwk;
  cmpframe = actaiwk->cmpframe;
  if (cmpframe && cmpframe <= actaiwk->frame)
  {
    sBtlResetAAI(wk);
    sBtlSetMotion(wk, 0, 4, 0, 0);
    return 1;
  }
  mv_spdbk = wk->mv_spdbk;
  vct_A = mv_spdbk;
  p_mv_spd = &wk->mv_spd;
  v11 = wk->actaiwk;
  *p_mv_spd = vct_A;
  mode = v11->mode;
  if (mode == 15)
  {
    if (sBtlCheckStatus_Move(wk))
    {
      sBtlResetAAI(wk);
      aiwk = wk->aiwk;
      actcnt = aiwk->actcnt;
      p_actcnt = &aiwk->actcnt;
      *p_actcnt = actcnt + 1;
      LimitRange(p_actcnt, 0, 0x7FFF);
    }
  }
  else if (mode == 14)
  {
    if (sBtlCheckMotionEnd(wk))
    {
      if ((Skilltbl->flg & 0x224) != 0 || (wk->side & 1) == 0 || (v13 = wk->aiwk, !v13->atkCnt) || wk->actwk->use_skillid != v13->dfltOdrSkl || wk->actaiwk->targetID == -1)
      {
        if (sBtlCheckCost(wk, 1))
        {
          v15 = wk->actaiwk;
          status = v15->status;
          v15->mode = 15;
          v15->status = status & 0xFFFFFDE0 | 4;
          *(u64 *)&v15->frame = 0xB400000000LL;
          return 1;
        }
        sBtlResetAAI(wk);
        sBtlSetMotion(wk, 0, 4, 0, 0);
        sBtlSetNoMP(wk);
        v24 = wk->aiwk;
        v25 = v24->status;
        if ((v25 & 1) != 0)
        {
          v24->status = v25 & 0xFFFFFFF6;
          v24->meirei_nobk = 7;
          data = wk->panelwk->data;
          SmnNo = sBtlGetSmnNo(wk);
          wk->NakamaAtkFormationUse = 0;
          data[SmnNo]->meirei_no = 7;
          wk->aiwk->status &= ~0x10u;
        }
      }
    }
  }
  return 1;
}

// 0x1dc7060
bool sBtlAAIProc_TurnMV(SBTLUNIT_WORK *wk) {
  s32 *p_frame;
  sdfVector4_t *p_mv_spdbk;
  sdfVector4_t *p_mv_spd;
  SBTLACTAI_WORK *actaiwk;
  s32 mode;
  SBTLACTAI_WORK *v12;
  f32 v13;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  SBTLACTAI_WORK *v24;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 v32;
  SBTLAI_WORK *aiwk;
  s32 *p_actcnt;
  s32 actcnt;
  SBTLACTAI_WORK *v38;
  f32 hit_area_r;
  f32 v40;
  f32 v41;
  f32 v42;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 v46;
  SBTLACTAI_WORK *v47;
  SBTLACTAI_WORK *v49;
  f32 offset_z;
  f32 v53;
  f32 v54;
  f32 GroundPos;
  SBTLACTAI_WORK *v62;
  sdfVector4_t area;
  f32 v66;
  f32 v67;
  f32 v68;
  f32 v69;
  f32 v70;
  f32 v71;
  struct sdfVector4_t vector1;
  f32 vector1b;
  struct sdfVector4_t vector1a;
  f32 vector1c;
  f32 vector1d;
  sdfVector4_t v77;
  sdfVector4_t v78;
  sdfVector4_t v79;
  sdfVector4_t pos;
  sdfVector4_t v81;
  sdfVector4_t v82;
  sdfVector4_t v83;

  p_frame = &wk->actaiwk->frame;
  ++*p_frame;
  LimitRange(p_frame, 0, 0x7FFF);
  p_mv_spdbk = &wk->mv_spdbk;
  vector1 = wk->mv_spdbk;
  vct_A = vector1;
  p_mv_spd = &wk->mv_spd;
  actaiwk = wk->actaiwk;
  *p_mv_spd = vct_A;
  mode = actaiwk->mode;
  if (mode == 15)
  {
    pos = wk->pos;
    x = wk->rot.x;
    y = wk->rot.y;
    z = wk->rot.z;
    w = wk->rot.w;
    v32 = actaiwk->ppos.x;
    v71 = wk->pos.y;
    vector1c = wk->pos.x;
    v67 = wk->pos.w;
    v69 = wk->pos.z;
    pos.w = v67;
    pos.z = v69;
    pos.y = v71;
    pos.x = vector1c;
    v83.x = x;
    v83.y = y;
    v83.z = z;
    v83.w = w;
    *(u64 *)&v77.x = 0;
    if (sBtlCheckVerticalArea(pos, v83, v77, v32))
    {
      sBtlResetAAI(wk);
      aiwk = wk->aiwk;
      actcnt = aiwk->actcnt;
      p_actcnt = &aiwk->actcnt;
      *p_actcnt = actcnt + 1;
      LimitRange(p_actcnt, 0, 0x7FFF);
      wk->actwk->use_skillid = 0;
    }
    return 1;
  }
  if (mode != 14)
    return 1;
  if (!sBtlCheckMotionID(wk, 5))
  {
    v38 = wk->actaiwk;
    hit_area_r = v38->hit_area_r;
    v81.x = wk->pos.x;
    v40 = wk->pos.y;
    v41 = wk->pos.z;
    v42 = wk->pos.w;
    v43 = v38->ppos.x;
    v44 = v38->ppos.y;
    v46 = v38->ppos.z;
    v45 = v38->ppos.w;
    vector1d = wk->pos.x;
    v81.x = vector1d;
    v81.y = v40;
    v81.z = v41;
    v81.w = v42;
    *(u64 *)&area.z = __PAIR64__(LODWORD(v45), LODWORD(v46));
    *(u64 *)&area.x = __PAIR64__(LODWORD(v44), LODWORD(v43));
    if (!sBtlCheckCrossCircle(v81, hit_area_r, area, 2.0))
      return 1;
    v47 = wk->actaiwk;
    v49 = wk->actaiwk;
    v47->ppos.x = main_data->offset_x + 0.0;
    offset_z = main_data->offset_z;
    v53 = v49->ppos.x;
    v54 = offset_z + 400.0;
    v49->ppos.z = offset_z + 400.0;
    if (!(u32)main_data)
    GroundPos = sBtlGetGroundPos(v53, v54);
    v49->ppos.y = GroundPos + 0.0;
    *(u64 *)&vct_A.x = 0;
    *(u64 *)&vct_A.z = 0;
    v62 = wk->actaiwk;
    *p_mv_spdbk = vct_A;
    v62->mode = 15;
    *(u64 *)&v62->frame = 0x2A3000000000LL;
    sBtlSetMotion(wk, 18, 4, 0, 0);
    return 1;
  }
  v12 = wk->actaiwk;
  v12->frame = 0;
  v13 = v12->ppos.x;
  v79 = wk->pos;
  v17 = wk->rot.x;
  v18 = wk->rot.y;
  v19 = wk->rot.z;
  v20 = wk->rot.w;
  v70 = wk->pos.y;
  vector1b = wk->pos.x;
  v66 = wk->pos.w;
  v68 = wk->pos.z;
  v79.w = v66;
  v79.z = v68;
  v79.y = v70;
  v79.x = vector1b;
  v82.x = v17;
  v82.y = v18;
  v82.z = v19;
  v82.w = v20;
  *(u64 *)&v78.x = 0;
  if (sBtlCheckVerticalArea(v79, v82, v78, v13))
  {
    vector1a = wk->max_mvspd;
    vct_A = vector1a;
    *p_mv_spdbk = vct_A;
    sBtlSetMotion(wk, 5, 4, 0, 0);
    v24 = wk->actaiwk;
    v24->frame = 0;
    v24->status = v24->status & 0xFFFFFDE0 | 0x14;
    return 1;
  }
  return 1;
}

// 0x1dc76f0
static void AAIProc_Skl_S_EXE_SKL(SBTLUNIT_WORK *wk, const sdfVector4_t *spd) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBATTLE_WORK *v9;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v12;
  sdfVector4_t *p_rot;
  SBTLACTION_WORK *actwk;
  SBTLACTAI_WORK *actaiwk;
  s32 use_skillid;
  f32 *p_x;
  struct sdfVector4_t rot;

  w = spd->w;
  z = spd->z;
  y = spd->y;
  x = spd->x;
  wk->actaiwk->status &= ~0x200u;
  v9 = wk;
  UnitMng = v9->UnitMng;
  playerID = v9->playerID;
  v12 = sBtlSearchUnit_ID(UnitMng, playerID);
  rot = v12->rot;
  vct_A = rot;
  p_rot = &wk->rot;
  actwk = wk->actwk;
  actaiwk = wk->actaiwk;
  *p_rot = vct_A;
  actaiwk->mode = 16;
  vct_A.x = v12->mv_rotbk;
  use_skillid = actwk->use_skillid;
  wk->mv_rotbk = vct_A.x;
  if (!(u32)actaiwk)
  sBtlSetUseSkill(wk, use_skillid, 0);
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  wk->mv_spdbk = vct_A;
}

// 0x1dc79d0
bool sBtlAAIProc_Skl_S(SBTLUNIT_WORK *wk) {
  SBTLSKILLP_TBL *Skilltbl;
  s32 *p_frame;
  SBTLACTAI_WORK *actaiwk;
  s32 cmpframe;
  sdfVector4_t *p_mv_spd;
  SBTLACTAI_WORK *v11;
  s32 mode;
  f32 hit_area_r;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  SBTLACTAI_WORK *v21;
  s32 targetID;
  dds3ModelHandle_t *hModel;
  SBTLACTAI_WORK *v25;
  SBTLAI_WORK *aiwk;
  s32 *p_actcnt;
  s32 actcnt;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v34;
  s32 flg;
  SBTLUNIT_WORK *v37;
  s32 v40;
  f32 *v43;
  f32 *v44;
  struct sdfVector4_t pos;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  SBTLAI_WORK *v51;
  bool v52;
  f32 pos1;
  f32 v63;
  struct sdfVector4_t mv_spdbk;
  struct sdfVector4_t rot;
  f32 v66;
  sdfMatrix4_t v67;
  sdfMatrix4_t v68;
  sdfVector4_t v69;
  sdfVector4_t v71;
  sdfVector4_t v72;
  sdfVector4_t v73;

  Skilltbl = sBtlGetSkilltbl(wk->actwk->use_skillid);
  p_frame = &wk->actaiwk->frame;
  ++*p_frame;
  LimitRange(p_frame, 0, 0x7FFF);
  actaiwk = wk->actaiwk;
  cmpframe = actaiwk->cmpframe;
  if (cmpframe && cmpframe <= actaiwk->frame)
  {
    sBtlResetAAI(wk);
    return 1;
  }
  mv_spdbk = wk->mv_spdbk;
  vct_A = mv_spdbk;
  p_mv_spd = &wk->mv_spd;
  v11 = wk->actaiwk;
  *p_mv_spd = vct_A;
  mode = v11->mode;
  if (mode == 16)
  {
    hModel = wk->hModel;
    if (hModel)
    {
      if ((mdlGetMotionFrame(hModel) & 0x80000000) == 0)
      {
        v25 = wk->actaiwk;
        v25->mode = 15;
        *(u64 *)&v25->frame = 0;
        sBtlCheckMHTData(wk, wk->actwk->use_skillid);
      }
    }
    return 1;
  }
  if (mode == 15)
  {
    if (sBtlCheckStatus_Move(wk))
    {
      sBtlResetAAI(wk);
      aiwk = wk->aiwk;
      actcnt = aiwk->actcnt;
      p_actcnt = &aiwk->actcnt;
      *p_actcnt = actcnt + 1;
      LimitRange(p_actcnt, 0, 0x7FFF);
    }
    return 1;
  }
  if (mode != 14)
    return 1;
  hit_area_r = v11->hit_area_r;
  sBtlGetPosforDistance(wk, -hit_area_r);
  p_x = &vf00.x;
  x = p_x[4];
  y = p_x[5];
  z = p_x[6];
  w = p_x[7];
  *(u64 *)&vct_A.x = 0;
  *(u64 *)&vct_A.z = 0;
  wk->mv_spdbk = vct_A;
  v21 = wk->actaiwk;
    if (v21->mode > 11)
  {
LABEL_31:
    targetID = v21->targetID;
    goto LABEL_65;
  }
  targetID = v21->LockID;
  if (wk->battlemode != 3 && (wk->side & 0x80) != 0)
  {
    v21 = wk->actaiwk;
    goto LABEL_31;
  }
LABEL_65:
  UnitMng = wk->UnitMng;
  v34 = sBtlSearchUnit_ID(UnitMng, targetID);
  flg = wk->flg;
  if ((flg & 8) == 0)
    goto LABEL_69;
LABEL_113:
  v72.x = 0.0;
  v72.y = 0.0;
  v72.z = 0.0;
  v72.w = 0.0;
  AAIProc_Skl_S_EXE_SKL(wk, v72);
  return 1;
LABEL_69:
  v37 = v34;
  if (v34 && (Skilltbl->type & 0x1000) == 0)
  {
    rot = wk->rot;
    vct_A = rot;
    ToMatrix();
    v40 = (u8)byte_5756085;
    vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
    get_transpose(&v68, &mtx_A, 0);
    v67 = v68;
    vct_A = op_Multiply_60923920(&v67, vct_A, 0);
    sub_1949110(0);
    vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, vdupq_n_s32(0x447A0000u));
    v43 = &vf00.x;
    v43[8] = x;
    v43[9] = y;
    v43[10] = z;
    v43[11] = w;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v44 = &vf00.x;
    pos = v37->pos;
    v47 = v44[4];
    v46 = v44[5];
    v48 = v44[6];
    v49 = v44[7];
    vct_A = pos;
    v63 = v48;
    v66 = v46;
    pos1 = v49;
    v73.z = v63;
    v73.y = v66;
    v71.x = x;
    v73.w = pos1;
    v71.y = y;
    v71.z = z;
    v71.w = w;
    v73.x = v47;
    *(u64 *)&v69.x = 0;
    if (sBtlGetVerticalLength(v71, v73, v69) > v37->actaiwk->hit_area_r)
      return 1;
    flg = wk->flg;
    goto LABEL_99;
  }
LABEL_99:
  if ((flg & 8) != 0 || (Skilltbl->flg & 0x224) != 0 || (wk->side & 1) == 0 || (v51 = wk->aiwk, !v51->atkCnt) || wk->actwk->use_skillid != v51->dfltOdrSkl || wk->actaiwk->targetID == -1)
  {
    v52 = sBtlCheckCost(wk, 1);
    if (v52)
    {
      goto LABEL_113;
    }
    sBtlResetAAI(wk);
    sBtlSetNoMP(wk);
    sBtlResetNakamaAction(wk);
  }
  return 1;
}

// 0x1dc8420
bool sBtlAAIProc_Skl_SMV(SBTLUNIT_WORK *wk) {
  SBTLSKILLP_TBL *Skilltbl;
  s32 *p_frame;
  SBTLACTAI_WORK *actaiwk;
  s32 cmpframe;
  sdfVector4_t *p_mv_spdbk;
  sdfVector4_t *p_mv_spd;
  SBTLACTAI_WORK *v12;
  s32 mode;
  SBTLACTAI_WORK *v14;
  s32 targetID;
  SBTLAI_WORK *aiwk;
  s32 *p_actcnt;
  s32 actcnt;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v23;
  s64 v24;
  f32 r1;
  f32 z;
  f32 w;
  f32 r2;
  f32 v34;
  SBTLAI_WORK *v35;
  s32 use_skillid;
  SBTLACTAI_WORK *v42;
  SBTLAI_WORK *v45;
  u32 status;
  SBTLPNL_SETDATA *data;
  s32 SmnNo;
  f32 v52;
  f32 v53;
  f32 v54;
  f32 v55;
  f32 y;
  struct sdfVector4_t mv_spdbk;
  f32 x;
  sdfVector4_t v59;
  sdfVector4_t pos;
  sdfVector4_t v61;

  Skilltbl = sBtlGetSkilltbl(wk->actwk->use_skillid);
  p_frame = &wk->actaiwk->frame;
  ++*p_frame;
  LimitRange(p_frame, 0, 0x7FFF);
  actaiwk = wk->actaiwk;
  cmpframe = actaiwk->cmpframe;
  if (cmpframe && cmpframe <= actaiwk->frame)
  {
    sBtlResetAAI(wk);
    return 1;
  }
  p_mv_spdbk = &wk->mv_spdbk;
  mv_spdbk = wk->mv_spdbk;
  vct_A = mv_spdbk;
  p_mv_spd = &wk->mv_spd;
  v12 = wk->actaiwk;
  *p_mv_spd = vct_A;
  mode = v12->mode;
  if (mode == 15)
  {
    if (sBtlCheckStatus_Move(wk))
    {
      sBtlResetAAI(wk);
      aiwk = wk->aiwk;
      actcnt = aiwk->actcnt;
      p_actcnt = &aiwk->actcnt;
      *p_actcnt = actcnt + 1;
      LimitRange(p_actcnt, 0, 0x7FFF);
    }
    return 1;
  }
  if (mode != 14)
    return 1;
  v14 = wk->actaiwk;
    if (v14->mode > 11)
  {
LABEL_21:
    targetID = v14->targetID;
    goto LABEL_43;
  }
  targetID = v14->LockID;
  if (wk->battlemode != 3 && (wk->side & 0x80) != 0)
  {
    v14 = wk->actaiwk;
    goto LABEL_21;
  }
LABEL_43:
  UnitMng = wk->UnitMng;
  v23 = sBtlSearchUnit_ID(UnitMng, targetID);
  if (v23)
  {
    if (targetID != wk->ListID)
    {
      r1 = wk->actaiwk->priv_area_r;
      pos = wk->pos;
      v61.x = wk->rot.x;
      v61.y = wk->rot.y;
      z = wk->rot.z;
      w = wk->rot.w;
      r2 = v23->pos.x;
      v34 = v23->pos.z;
      y = wk->pos.y;
      x = wk->pos.x;
      v54 = wk->pos.w;
      v55 = wk->pos.z;
      v52 = wk->rot.y;
      v53 = wk->rot.x;
      v61.y = v52;
      v61.x = v53;
      pos.w = v54;
      pos.z = v55;
      pos.y = y;
      pos.x = x;
      v61.z = z;
      v61.w = w;
      *(u64 *)&v59.x = 0;
      *(u64 *)&v59.z = v24;
      if (!sBtlCheckCrossCircle_Rot(pos, v61, r1, v59, r2, v34))
        return 1;
    }
  }
  if ((Skilltbl->flg & 0x224) == 0 && (wk->side & 1) != 0)
  {
    v35 = wk->aiwk;
    if (v35->atkCnt)
    {
      if (wk->actwk->use_skillid == v35->dfltOdrSkl && wk->actaiwk->targetID != -1)
        return 1;
    }
  }
  *(u64 *)&vct_A.x = 0;
  *(u64 *)&vct_A.z = 0;
  *p_mv_spdbk = vct_A;
  if (sBtlCheckCost(wk, 1))
  {
    wk->actaiwk->mode = 15;
    use_skillid = wk->actwk->use_skillid;
    sBtlSetUseSkill(wk, use_skillid, 0);
    *(u64 *)&vct_A.x = 0;
    *(u64 *)&vct_A.z = 0;
    v42 = wk->actaiwk;
    *p_mv_spdbk = vct_A;
    v42->status &= ~0x200u;
    return 1;
  }
  sBtlResetAAI(wk);
  sBtlSetNoMP(wk);
  v45 = wk->aiwk;
  status = v45->status;
  if ((status & 1) != 0)
  {
    v45->meirei_nobk = 7;
    v45->status = status & 0xFFFFFFF6;
    data = wk->panelwk->data;
    SmnNo = sBtlGetSmnNo(wk);
    wk->NakamaAtkFormationUse = 0;
    data[SmnNo]->meirei_no = 7;
    wk->aiwk->status &= ~0x10u;
  }
  return 1;
}

// 0x1dc8bb0
static void AAIProc_Skl_SRT_EXE_SKL(SBTLUNIT_WORK *wk, const sdfVector4_t *spd) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBTLACTAI_WORK *actaiwk;
  s32 use_skillid;
  f32 *p_x;
  SBTLACTAI_WORK *v12;

  w = spd->w;
  z = spd->z;
  y = spd->y;
  x = spd->x;
  sBtlCheckCost(wk, 1);
  actaiwk = wk->actaiwk;
  actaiwk->mode = 16;
  actaiwk->frame = 0;
  use_skillid = wk->actwk->use_skillid;
  sBtlSetUseSkill(wk, use_skillid, 0);
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v12 = wk->actaiwk;
  wk->mv_spdbk = vct_A;
  v12->status &= 0xFFFF7DFF;
}

// 0x1dc8d80
bool sBtlAAIProc_Skl_SRT(SBTLUNIT_WORK *wk) {
  s32 *p_frame;
  SBTLACTAI_WORK *actaiwk;
  s32 cmpframe;
  SBTLSKILLP_TBL *Skilltbl;
  sdfVector4_t *p_mv_spd;
  SBTLACTAI_WORK *v12;
  s32 mode;
  SBTLACTAI_WORK *v18;
  s32 LockID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v22;
  SBTLUNIT_WORK *v24;
  s32 v25;
  SBTLACTAI_WORK *v26;
  f32 hit_area_r;
  f32 z;
  f32 w;
  struct sdfVector4_t rot;
  s32 v34;
  f32 *p_x;
  struct sdfVector4_t pos;
  f32 x;
  f32 v41;
  f32 v42;
  dds3ModelHandle_t *hModel;
  SBTLACTAI_WORK *v44;
  SBTLAI_WORK *aiwk;
  s32 *p_actcnt;
  s32 actcnt;
  SBTLAI_WORK *v51;
  u32 status;
  SBTLPNL_SETDATA *data;
  SBTLACTAI_WORK *v55;
  s32 v56;
  SBTLAI_WORK *v57;
  struct sdfVector4_t pos0;
  s64 pos0a;
  sdfMatrix4_t v66;
  sdfMatrix4_t v67;
  sdfVector4_t v68;
  sdfVector4_t v70;
  sdfVector4_t v71;
  sdfVector4_t v72;
  sdfVector4_t v73;

  p_frame = &wk->actaiwk->frame;
  ++*p_frame;
  LimitRange(p_frame, 0, 0x7FFF);
  actaiwk = wk->actaiwk;
  cmpframe = actaiwk->cmpframe;
  if (cmpframe && cmpframe <= actaiwk->frame)
  {
    sBtlResetAAI(wk);
    return 1;
  }
  Skilltbl = sBtlGetSkilltbl(wk->actwk->use_skillid);
  pos0 = wk->mv_spdbk;
  vct_A = pos0;
  p_mv_spd = &wk->mv_spd;
  v12 = wk->actaiwk;
  *p_mv_spd = vct_A;
  mode = v12->mode;
  if (mode == 16)
  {
    hModel = wk->hModel;
    if (hModel)
    {
      if ((mdlGetMotionFrame(hModel) & 0x80000000) == 0)
      {
        v44 = wk->actaiwk;
        v44->mode = 15;
        *(u64 *)&v44->frame = 0;
        sBtlCheckMHTData(wk, wk->actwk->use_skillid);
      }
    }
    return 1;
  }
  if (mode == 15)
  {
    if (sBtlCheckStatus_Move(wk))
    {
      sBtlResetAAI(wk);
      aiwk = wk->aiwk;
      actcnt = aiwk->actcnt;
      p_actcnt = &aiwk->actcnt;
      *p_actcnt = actcnt + 1;
      LimitRange(p_actcnt, 0, 0x7FFF);
    }
    return 1;
  }
  if (mode != 14)
    return 1;
  if ((wk->flg & 8) == 0)
  {
    goto LABEL_17;
LABEL_98:
    wk->actwk->use_skillid = 149;
    sBtlSetNoMP(wk);
    sBtlResetAAI(wk);
    v51 = wk->aiwk;
    status = v51->status;
    if ((status & 1) != 0)
    {
      v51->status = status & 0xFFFFFFF6;
      v51->meirei_nobk = 7;
      data = wk->panelwk->data;
      data[sBtlGetSmnNo(wk)]->meirei_no = 7;
      wk->aiwk->status &= ~0x10u;
      wk->NakamaAtkFormationUse = 0;
    }
    return 1;
  }
  v71.x = 0.0;
  v71.y = 0.0;
  v71.z = 0.0;
  v71.w = 0.0;
  AAIProc_Skl_SRT_EXE_SKL(wk, v71);
LABEL_17:
  if (!sBtlCheckCost(wk, 0))
    goto LABEL_98;
  if ((wk->side & 1) == 0)
  {
    v18 = wk->actaiwk;
    v18 = wk->actaiwk;
    if (v18->mode <= 11)
    {
      LockID = v18->LockID;
      if (wk->battlemode == 3 || (wk->side & 0x80) == 0)
      {
LABEL_33:
        UnitMng = wk->UnitMng;
        v22 = sBtlSearchUnit_ID(UnitMng, LockID);
        v24 = v22;
        v25 = (LOBYTE(Skilltbl->area) >> 6) & 1;
        v26 = wk->actaiwk;
        if ((v26->status & 0x8000) != 0)
          v25 = 1;
        if (!(!v22 || v25))
        {
          hit_area_r = v26->hit_area_r;
          sBtlGetPosforDistance(wk, -hit_area_r);
          z = vct_A.z;
          w = vct_A.w;
          pos0a = *(u64 *)&vct_A.x;
          rot = wk->rot;
          vct_A = rot;
          ToMatrix();
          v34 = (u8)byte_5756085;
          vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
          get_transpose(&v67, &mtx_A, 0);
          v66 = v67;
          vct_A = op_Multiply_60923920(&v66, vct_A, 0);
          sub_1949110(0);
          vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, vdupq_n_s32(0x44160000u));
          vct_B.z = z;
          vct_B.w = w;
          *(u64 *)&vct_B.x = pos0a;
          vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
          p_x = &vf00.x;
          pos = v24->pos;
          x = p_x[4];
          v41 = p_x[6];
          v42 = p_x[7];
          vct_A = pos;
          v70.y = 0.0;
          v73.y = 0.0;
          v73.x = x;
          v73.z = v41;
          *(u64 *)&v68.x = 0;
          v73.w = v42;
          v70.z = z;
          v70.w = w;
          LODWORD(v70.x) = pos0a;
          v25 = sBtlGetVerticalLength(v70, v73, v68) <= v24->actaiwk->hit_area_r
             || (Skilltbl->type & 0x1000) != 0;
        }
        v55 = wk->actaiwk;
        v56 = v55->cmpframe;
        if (v56 && v56 <= v55->frame - 2)
          v25 = 1;
        if (!v24 || v25)
        {
          if ((Skilltbl->flg & 0x224) != 0 || (wk->side & 1) == 0 || (v57 = wk->aiwk, !v57->atkCnt) || wk->actwk->use_skillid != v57->dfltOdrSkl || v55->targetID == -1)
          {
            v72.x = 0.0;
            v72.y = 0.0;
            v72.z = 0.0;
            v72.w = 0.0;
            AAIProc_Skl_SRT_EXE_SKL(wk, v72);
          }
        }
        return 1;
      }
      v18 = wk->actaiwk;
    }
    LockID = v18->targetID;
    goto LABEL_33;
  }
  sBtlGotoAtkPos(wk, 0);
  return 1;
}

// 0x1dc9810
bool sBtlAAIProc_SUMMON(SBTLUNIT_WORK *wk) {
  s32 *p_frame;
  sdfVector4_t *p_mv_spdbk;
  SBTLACTAI_WORK *actaiwk;
  s32 cmpframe;

  p_frame = &wk->actaiwk->frame;
  ++*p_frame;
  LimitRange(p_frame, 0, 0x7FFF);
  *(u64 *)&vct_A.x = 0;
  *(u64 *)&vct_A.z = 0;
  p_mv_spdbk = &wk->mv_spdbk;
  goto LABEL_10;
LABEL_17:
  if (cmpframe <= actaiwk->frame)
    goto LABEL_23;
  goto LABEL_18;
LABEL_10:
  actaiwk = wk->actaiwk;
  *p_mv_spdbk = vct_A;
  cmpframe = actaiwk->cmpframe;
  if (cmpframe)
    goto LABEL_17;
LABEL_18:
  if (wk->mode != 8 || (wk->vstatus & 1) != 0)
    return 1;
  if (!sBtlCheckNextAction(wk))
    return 1;
LABEL_23:
  if (!sBtlLoadEffectData_Decode(wk))
    return 1;
  sBtlSetAction(wk, 1, 0);
  sBtlSetAIWkStat(wk, 1);
  wk->actaiwk->status = wk->actaiwk->status & 0xFFFFFF9F | 0x40;
  return 1;
}

// 0x1dc9ac0
bool sBtlAAIProc_N_GuardH(SBTLUNIT_WORK *wk) {
  s32 *p_frame;

  p_frame = &wk->actaiwk->frame;
  ++*p_frame;
  LimitRange(p_frame, 0, 4000);
  wk->status |= 0x100u;
  if (wk->actaiwk->cmpframe <= wk->actaiwk->frame)
  {
    sBtlResetAAI(wk);
    wk->status &= ~0x100u;
  }
  return 1;
}

// 0x1dc9ba0
bool sBtlAAIProc_SAttack(SBTLUNIT_WORK *wk) {
  sBtlResetAAI(wk);
  return 1;
}

// 0x1dc9c10
s32 sBtlMawariChk(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pTgt) {
  f32 x;
  f32 v6;
  f32 z;
  f32 v8;
  f32 v9;
  f32 y;
  f32 v11;
  f32 w;
  f32 v13;
  f32 v14;
  f32 RotToDir;
  f32 PosToDir;
  f32 v17;
  s32 v18;
  s32 v19;
  s32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v26;
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
  f32 v44;
  f32 dis;
  bool v47;
  f32 v53;
  f32 v54;
  f32 v55;
  f32 v56;
  f32 v57;
  f32 v58;
  f32 v59;
  f32 v60;
  f32 v61;
  f32 v62;
  f32 v63;
  f32 v64;
  f32 v65;
  f32 v66;
  f32 v67;
  f32 pos0;
  f32 pos0_4;
  f32 pos0_8;
  sdfMatrix4_t pos0_12;
  sdfMatrix4_t v74;
  sdfVector4_t v75;
  sdfVector4_t v76;
  sdfVector4_t v77;
  sdfVector4_t v79;
  sdfVector4_t v80;
  sdfVector4_t v81;
  sdfVector4_t v82;
  sdfVector4_t v83;
  sdfVector4_t v84;
  sdfVector4_t v85;

  x = wk->pos.x;
  v6 = pTgt->pos.x;
  z = wk->pos.z;
  v8 = pTgt->pos.z;
  v9 = wk->rot.x;
  y = wk->rot.y;
  v11 = wk->rot.z;
  w = wk->rot.w;
  v77.x = v9;
  v77.y = y;
  v77.z = v11;
  v77.w = w;
  v13 = x - v6;
  v14 = z - v8;
  RotToDir = sBtlGetRotToDir(v77);
  PosToDir = sBtlGetPosToDir(wk->pos.x, wk->pos.z, pTgt->pos.x, pTgt->pos.z);
  if (sBtlGetAtoB_LR(RotToDir, PosToDir) >= 0.0)
  {
    v17 = 1.5707964;
    v18 = 1;
    v19 = -1;
    *(f32 *)&v20 = -1.5707964;
  }
  else
  {
    v17 = -1.5707964;
    v18 = -1;
    v19 = 1;
    *(f32 *)&v20 = 1.5707964;
  }
  v21 = *(f32 *)&v20;
  v22 = (f32)(v13 * v13) + (f32)(v14 * v14);
  sub_1949280(0, v17);
  v23 = sqrtf(v22);
  v24 = v13 / v23;
  v26 = v14 / v23;
  vct_A.x = v24;
  vct_A.y = 0.0;
  vct_A.z = v26;
  vct_A.w = 1.0;
  get_transpose(&v74, &mtx_A, 0);
  pos0_12 = v74;
  v75 = op_Multiply_60923920(&pos0_12, vct_A, 0);
  vct_A = v75;
  v30 = 10.0;
  v31 = wk->pos.x;
  v32 = wk->pos.z;
  v33 = (f32)((f32)(pTgt->actaiwk->hit_area_r + wk->actaiwk->hit_area_r) + 10.0) + 10.0;
  v34 = pTgt->pos.x + (f32)(vct_A.x * v33);
  v35 = pTgt->pos.z + (f32)(vct_A.z * v33);
  v79.w = 1.0;
  v79.y = 0.0;
  v79.x = v34;
  v79.z = v35;
  if (!sBtlCheckArea(wk, v79, 50.0))
  {
    v36 = v31 - v34;
    pos0_4 = v26;
    pos0_8 = v24;
    v37 = v32 - v35;
    v38 = wk->pos.z;
    v39 = wk->pos.w;
    v40 = v21;
    v41 = v36 * v36;
    v42 = wk->pos.y;
    v43 = v37 * v37;
    pos0 = wk->pos.x;
    v44 = v41 + v43;
    dis = sqrtf(v44);
    v21 = v40;
    v80.x = pos0;
    v84.y = 0.0;
    v80.y = v42;
    v80.z = v38;
    v80.w = v39;
    v84.x = v34;
    v84.z = v35;
    v84.w = 1.0;
    v47 = sBtlCheckMapHit_Cross(v80, v84, dis);
    v26 = pos0_4;
    v24 = pos0_8;
    v30 = 10.0;
    if (v47)
      return v18;
  }
  sub_1949280(0, v21);
  vct_A.x = v24;
  vct_A.y = 0.0;
  vct_A.z = v26;
  vct_A.w = 1.0;
  get_transpose(&v74, &mtx_A, 0);
  v81 = vct_A;
  pos0_12 = v74;
  v76 = op_Multiply_60923920(&pos0_12, v81, 0);
  vct_A = v76;
  v53 = wk->pos.x;
  v54 = wk->pos.z;
  v55 = (f32)((f32)(pTgt->actaiwk->hit_area_r + wk->actaiwk->hit_area_r) + v30) + v30;
  v56 = pTgt->pos.x + (f32)(vct_A.x * v55);
  v57 = pTgt->pos.z + (f32)(vct_A.z * v55);
  v82.w = 1.0;
  v82.y = 0.0;
  v82.x = v56;
  v82.z = v57;
  if (sBtlCheckArea(wk, v82, 50.0))
    return 0;
  v58 = v53 - v56;
  v59 = v54 - v57;
  v60 = wk->pos.x;
  v61 = wk->pos.y;
  v62 = v58 * v58;
  v63 = wk->pos.z;
  v64 = wk->pos.w;
  v65 = v59 * v59;
  v66 = v62 + v65;
  v67 = sqrtf(v66);
  v85.y = 0.0;
  v83.x = v60;
  v83.y = v61;
  v83.z = v63;
  v83.w = v64;
  v85.x = v56;
  v85.z = v57;
  v85.w = 1.0;
  if (sBtlCheckMapHit_Cross(v83, v85, v67))
    return v19;
  else
    return 0;
}

// 0x1da9ce0
bool sBtlWarpDevilChk(s32 devilId) {
  return 1;
}

// 0x1dab1f0
bool sBtlNakamaGaolChk_Sub(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v7;
  u16 major;
  s32 minor;
  f32 m_mv_area_r;
  f32 y;
  f32 hit_area_r;
  f32 z;
  f32 w;
  f32 x;
  f32 v16;
  f32 v17;
  f32 v18;
  sdfVector4_t vector2;
  f32 v21;
  f32 v22;
  sdfVector4_t v23;

  v4 = wk;
  UnitMng = v4->UnitMng;
  playerID = v4->playerID;
  v7 = sBtlSearchUnit_ID(UnitMng, playerID);
  major = wk->major;
  minor = wk->minor;
  m_mv_area_r = sBtlGetMotionVisualData(major, minor, 1)->m_mv_area_r;
  v23.x = wk->pos.x;
  y = wk->pos.y;
  hit_area_r = v7->actaiwk->hit_area_r;
  z = wk->pos.z;
  w = wk->pos.w;
  x = v7->pos.x;
  v16 = v7->pos.y;
  v18 = v7->pos.z;
  v17 = v7->pos.w;
  v21 = wk->pos.x;
  v22 = m_mv_area_r;
  v23.x = v21;
  m_mv_area_r = v22;
  v23.y = y;
  v23.z = z;
  v23.w = w;
  *(u64 *)&vector2.z = __PAIR64__(LODWORD(v17), LODWORD(v18));
  *(u64 *)&vector2.x = __PAIR64__(LODWORD(v16), LODWORD(x));
  return sBtlCheckCrossCircle(v23, m_mv_area_r, vector2, hit_area_r)
      && v7->mv_spd.z <= 0.0;
}

// 0x1dca3a0
bool sBtlNakamaGoalChk2(SBTLUNIT_WORK *wk) {
  SBTLUNIT_WORK *v4;

  v4 = wk;
  return sBtlNakamaGaolChk_Sub(v4);
}

// 0x1dca420
void sBtlACTAIFLG_Clr(SBTLUNIT_WORK *wk) {
  wk->actaiwk->status &= 0xFFFFFDFE;
}

// 0x1dca440
SBTLACTAI_WORK *sBtlCreate(void) {
  SBTLACTAI_WORK *v1;
  s32 v3;

  v1 = Allocate(SBTLACTAI_WORK);
  _ctor(v1, 0);
  v1->eventStart = 0;
  v1->mode = 0;
  v1->dataflg = 0;
  *(_OWORD *)&v1->hit_area_r = xmmword_3CFAFF0;
  v3 = v1->status;
  *(u64 *)&v1->targetGroupID = -1;
  v1->status = v3 | 0x24;
  v1->targetID = -1;
  *(u64 *)&v1->bk_targetID = 0xFFFFFFFFLL;
  *(u32 *)((u64)v1->data_p + 36) = 0;
  return v1;
}

// 0x1dca4f0
bool sBtlDelete(SBTLACTAI_WORK *wk) {
  return 1;
}

// 0x1dca500
bool sBtlProc(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v5;
  s32 side;
  SBATTLE_WORK *v7;

  if (kaiwa_btlendflg)
    return 0;
  v5 = wk;
  if ((v5->status & 0x1000000) != 0)
    return 0;
  if ((v5->status2 & 0x80000) != 0)
    return 0;
  side = wk->side;
  if ((side & 2) != 0)
  {
    v5 = wk;
    if (v5->cmbSkl->bRun)
      return 0;
    side = wk->side;
    if ((side & 2) != 0 && (wk->status & 0x100000) == 0 && (wk->exsts & 2) == 0)
    {
      if (wk->aiBgnCnt < 120)
        return 0;
      side = wk->side;
    }
  }
  if ((side & 0x80) != 0 || (wk->vstatus & 0x4000) != 0)
  {
    wk->actaiwk->mode = 0;
    return 0;
  }
  if ((wk->status & 6) != 0)
  {
    v7 = wk;
    if ((v7->status & 0x10000) != 0)
    {
      v7 = wk;
      if ((v7->status2 & 0x20000000) == 0)
      {
        v7 = wk;
        if ((v7->status4 & 0x400) == 0)
        {
          sBtlAAIProc(wk);
          return 1;
        }
      }
    }
    return 0;
  }
  sBtlEnemyAI(wk);
  return 1;
}

// 0x1db30b0
AITBLDATA_WORK *sBtlGetAITBL(s32 devilid, SBTLUNIT_WORK *wk) {
  u32 exflg;
  s64 v6;
  SB_ENCOUNTPAC *EncountPac;
  Il2CppClass **v11;
  u32 v12;
  u32 v13;

  if (wk)
  {
    if (!wk)
      goto LABEL_9;
    exflg = wk->exflg;
    if (exflg >= 0x10000)
    {
      EncountPac = sBtlGetEncountPac(-1);
      v11 = &EncountPac->obj.klass + wk->encountno;
      devilid = HIWORD(exflg);
      v12 = *(&v11[4]->_1.byval_arg.bits + 1);
      v13 = HIWORD(v12) & 1;
      if ((v12 & 0x20000) != 0)
        v13 = 2;
      if ((v12 & 0x40000) != 0)
        v13 = 3;
      if ((v12 & 0x80000) != 0)
        v13 = 4;
      if ((v12 & 0x100000) != 0)
        v6 = 5;
      else
        v6 = v13;
      return ai_tbldata[v6][devilid];
    }
  }
LABEL_9:
  v6 = 0;
  return ai_tbldata[v6][devilid];
}

// 0x1dca760
s32 sBtlGetAIPatternData(SBTLUNIT_WORK *unit, s32 id, s32 p1, s32 p2) {
  AITBLDATA_WORK *AITBL;

  AITBL = sBtlGetAITBL(id, unit);
  return AITBL->pat_tbl[AITBL->pat_tbl->bounds[1].length * p1 + p2];
}

// 0x1dca800
bool sBtlSetSkillData_AI(SBTLUNIT_WORK *wk, SKLID skillid) {
  SBTLACTAI_WORK *actaiwk;

  wk->actwk->use_skillid = skillid;
  sBtlSetAIMode(wk);
  wk->actaiwk->stat = 1;
  sBtlCheckTargetEquation(wk);
  actaiwk = wk->actaiwk;
  wk->aiwk->stat = 2;
  actaiwk->mode = 14;
  return 1;
}

// 0x1db9bc0
bool sBtlCheckEquation(SBTLUNIT_WORK *wk) {
  SBTLAI_WORK *aiwk;
  SBTLACTAI_WORK *actaiwk;
  SBATTLE_WORK *v6;
  SBTLAI_WORK *v7;
  SBTLACTAI_WORK *v8;
  SBTLACTION_WORK *actwk;

  aiwk = wk->aiwk;
  if (aiwk->scr_actcheckflg == 1)
    return 0;
  actaiwk = wk->actaiwk;
  if ((u32)(actaiwk->mode - 9) < 2 || aiwk->stat != 1 || actaiwk->stat != 2 && wk->bYobidousa)
  {
    return 0;
  }
  v6 = wk;
  if (v6->bosseventflg)
    return 0;
  v6 = wk;
  if ((v6->status2 & 0x80000) != 0)
    return 0;
  v7 = wk->aiwk;
  if (v7->bWait)
  {
    v8 = wk->actaiwk;
LABEL_18:
    actwk = wk->actwk;
    v7->mode = 1;
    v8->stat = 1;
    actwk->use_skillid = 0;
    return 1;
  }
  v8 = wk->actaiwk;
  if (v7->bWait2)
    goto LABEL_18;
  if (v8->dataflg)
  {
    sBtlUseTableDataProc(wk);
    return 1;
  }
  else
  {
    sBtlCheckEquationProc(wk);
    return 1;
  }
}

// 0x1db4050
bool sBtlCheckChkskl(SBTLUNIT_WORK *wk, s32 sklid) {
  return (wk->actaiwk->chkskl[sklid / 32] >> sklid) & 1;
}

// 0x1dca8b0
void sBtlSetChkskl(SBTLUNIT_WORK *wk, s32 sklid) {
  char *v3;

  v3 = (char *)wk->actaiwk->chkskl + 4 * (sklid / 32);
  *((u32 *)v3 + 8) |= 1 << sklid;
}

// 0x1dca8f0
void SetChkskl(SBTLUNIT_WORK *wk, SKLID sklid) {
  char *v5;

  v5 = (char *)wk->actaiwk->chkskl + 4 * (sklid / 32);
  *((u32 *)v5 + 8) |= 1 << sklid;
}

// 0x1db4280
void sBtlResetChkskl(SBTLUNIT_WORK *wk, s32 sklid) {
  char *v3;

  v3 = (char *)wk->actaiwk->chkskl + 4 * (sklid / 32);
  *((u32 *)v3 + 8) &= ~(1 << sklid);
}

// 0x1db4450
bool sBtlCheckUseskl(SBTLUNIT_WORK *wk, s32 sklid) {
  return (wk->actaiwk->useskl[sklid / 32] >> sklid) & 1;
}

// 0x1dca980
void sBtlSetUseskl(SBTLUNIT_WORK *wk, s32 sklid) {
  char *v3;

  v3 = (char *)wk->actaiwk->useskl + 4 * (sklid / 32);
  *((u32 *)v3 + 8) |= 1 << sklid;
}

// 0x1dca9c0
void SetUseskl(SBTLUNIT_WORK *wk, SKLID sklid) {
  char *v5;

  v5 = (char *)wk->actaiwk->useskl + 4 * (sklid / 32);
  *((u32 *)v5 + 8) |= 1 << sklid;
}

// 0x1db4680
void sBtlResetUseskl(SBTLUNIT_WORK *wk, s32 sklid) {
  char *v3;

  v3 = (char *)wk->actaiwk->useskl + 4 * (sklid / 32);
  *((u32 *)v3 + 8) &= ~(1 << sklid);
}

// 0x1db5a30
bool sBtlCheckMeshiyose(SBTLUNIT_WORK *wk) {
  if (!sBtlCheckGenerator_D())
    return 0;
  return wk->enemy_num < 6;
}

// 0x1dcaa50
s32 sBtlGetEnemyNum(void) {
  s64 v2;
  s32 v3;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;

  v2 = 0;
  v3 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v2 >= UnitMng->number)
      return v3;
    pUnit = wk->UnitMng->pUnitL[v2]->pUnit;
    if (pUnit)
      v3 += ((u32)pUnit->side >> 1) & 1;
    ++v2;
  }
}

// 0x1db2420
bool sBtlUseTableDataProc(SBTLUNIT_WORK *wk) {
  SB_ENCOUNTPAC *EncountPac;
  s32 devilid;
  s32 v7;
  s32 v8;
  s32 *data_p;
  s64 v10;
  s64 v11;
  AITBLDATA_WORK *AITBL;
  s32 v16;
  s32 *v18;
  s32 v19;
  s32 v20;
  AITBLDATA_WORK *v22;
  s32 v23;
  s32 v24;
  s32 v25;

  EncountPac = sBtlGetEncountPac(-1);
  if ((EncountPac[wk->encountno]->flag & 4) == 0 && (wk->side & 2) != 0 && wk->actaiwk->nonempflg)
  {
    devilid = 0;
  }
  else
  {
    devilid = wk->para->devilid;
  }
  v7 = 0;
  v8 = 0;
  do
  {
    data_p = wk->actaiwk->data_p;
    v10 = data_p[0];
    v11 = data_p[1];
    AITBL = sBtlGetAITBL(devilid, wk);
    v16 = AITBL->pat_tbl[v11 + AITBL->pat_tbl->bounds[1].length * v10];
    if (!((u32)(v16 >> 16) > 0x23 || ((1 << SBYTE2(v16)) & 0x80313F200LL) == 0))
    {
      v18 = wk->actaiwk->data_p;
      v19 = v18[1];
      v20 = v18[0];
      v22 = sBtlGetAITBL(devilid, wk);
      v23 = v22->pat_tbl[v22->pat_tbl->bounds[1].length * v20 + 1 + v19];
      v7 = v23 >> 16;
      v8 = (u16)v23;
    }
    v24 = sBtlSetAIData(wk, v16 >> 16, (u16)v16, v7, v8);
    if ((v24 & 0xFFFFFFFE) == 2)
    {
      v25 = 1;
      goto LABEL_38;
    }
  }
  while (!v24);
  if (v24 != 4)
    return 0;
  v25 = 2;
LABEL_38:
  wk->actaiwk->data_p[1] += v25;
  return 0;
}

// 0x1dade80
s32 sBtlGetUseTable_Target(SBTLUNIT_WORK *wk, PAITARGET code, s32 arg) {
  s32 *v7;
  s16 *v8;
  SBATTLE_WORK *v10;
  s32 member_num;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v13;
  SBTLUNIT_WORK *v14;
  SBTLUNIT_LISTWORK *v15;
  s32 v16;
  SBTLUNIT_WORK *v17;
  SBTLUNIT_WORK *v18;
  s32 result;
  s64 v20;
  s32 v21;
  SBTLUNIT_LISTWORK *v22;
  SBTLUNIT_WORK *pUnit;
  u16 Percentage;
  s64 v25;
  s64 v26;
  s32 v27;
  SBTLUNIT_LISTWORK *v28;
  SBTLUNIT_WORK *v29;
  s32 ListID;
  u16 v31;
  s64 v32;
  char *v33;
  SBTLUNIT_LISTWORK *v34;
  s32 aborttargetID;
  SBTLUNIT_WORK *v36;
  SBTLUNIT_WORK *v37;
  SBATTLE_WORK *v39;
  SBTLUNIT_LISTWORK *v40;
  s32 v41;
  SBTLUNIT_WORK *v42;
  s32 side;
  SBTLUNIT_LISTWORK *SideList_AI;
  s32 count;
  SBTLUNIT_LISTWORK *v47;
  s64 pUnitL;
  s32 v49;
  SBTLUNIT_LISTWORK *v50;
  f32 v51;
  s64 v52;
  s32 v53;
  s64 v55;
  f32 v56;
  SBTLUNIT_WORK *v57;
  struct sdfVector4_t v59;
  f32 *v60;
  f32 v61;
  f32 v62;
  f32 v63;
  s32 v65;
  SBTLUNIT_LISTWORK *v66;
  s64 v67;
  f32 v68;
  s64 v69;
  s32 v70;
  sdatParaWork_t *now;
  f32 maxhp;
  s32 v73;
  SBTLUNIT_LISTWORK *v74;
  s64 v75;
  f32 v76;
  sdatParaWork_t *v77;
  f32 v78;
  s64 v79;
  SBTLUNIT_WORK *v80;
  SBATTLE_WORK *v82;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v85;
  s64 v86;
  s32 v87;
  SBTLUNIT_LISTWORK *v88;
  SBTLUNIT_WORK *v90;
  s64 v91;
  s32 *v92;
  s16 *v93;
  s16 v94;
  s16 v95;
  s32 v96;
  s64 v97;
  s32 *v98;
  s16 *v99;
  s16 v100;
  s16 v101;
  s32 v102;
  SBTLUNIT_WORK *v103;
  f32 v104;
  SBTLUNIT_WORK *v105;
  SBTLUNIT_LISTWORK *v107;
  s64 v108;
  s64 v109;
  SBTLUNIT_WORK *v110;
  struct sdfVector4_t v112;
  f32 *v113;
  f32 v114;
  f32 v115;
  f32 v116;
  s64 v119;
  s16 v120;
  SBTLUNIT_WORK *v121;
  struct sdfVector4_t v123;
  f32 *p_x;
  f32 z;
  f32 x;
  f32 y;
  struct sdfVector4_t v129;
  f32 v131;
  f32 v132;
  f32 v133;
  f32 v134;
  f32 *v135;
  f32 v136;
  f32 v137;
  f32 v138;
  f32 v139;
  f32 v140;
  SBTLUNIT_WORK *v142;
  s32 v143;
  sdatUnitWork_t *para;
  u32 BadStatus;
  s32 v147;
  s32 v148;
  SBTLUNIT_LISTWORK *SideList;
  s32 v150;
  SBTLUNIT_LISTWORK *v151;
  s64 v152;
  s32 v153;
  s64 m_Items;
  s64 v155;
  s32 v156;
  f32 v158;
  f32 v159;
  f32 w;
  f32 v161;
  f32 v162;
  s32 v165;
  struct sdfVector4_t v166;
  struct sdfVector4_t v169;
  struct sdfVector4_t pos;

  v7 = NewSpecific(s32, 0x40u);
  v8 = NewSpecific(s16, 0x40u);
  v10 = wk;
  if (v10->NakamaShugouOn)
    member_num = 0;
  else
    member_num = v10->member_num;
  switch (code)
  {
    case 1:
      if (member_num < 1)
        goto LABEL_139;
      Nakama = sBtlGetNakama(0);
      v13 = sBtlGetNakama(1);
      v14 = v13;
      if (Nakama)
      {
        if (!CheckLiveTarget(Nakama))
          Nakama = 0;
        if (!v14)
        {
          if (Nakama)
            return Nakama->ListID;
          goto LABEL_139;
        }
      }
      else
      {
        if (!v13)
          goto LABEL_139;
        Nakama = 0;
      }
      if (CheckLiveTarget(v14))
        v105 = v14;
      else
        v105 = 0;
      if (Nakama && v105)
      {
        pos = wk->pos;
        vct_B = pos;
        v123 = Nakama->pos;
        vct_A = v123;
        vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
        p_x = &vf00.x;
        z = p_x[6];
        x = p_x[4];
        y = p_x[5];
        v129 = v105->pos;
        vct_A = v129;
        v131 = x * x;
        v132 = y * y;
        vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
        v133 = v131 + v132;
        v134 = z * z;
        v135 = &vf00.x;
        v136 = v133 + v134;
        v137 = v135[6];
        v138 = v135[4];
        v139 = v135[5];
        v140 = sqrtf(v136);
        if (v140 < sqrtf((f32)((f32)(v138 * v138) + (f32)(v139 * v139)) + (f32)(v137 * v137)))
          return Nakama->ListID;
        return v105->ListID;
      }
      if (Nakama)
        return Nakama->ListID;
      if (v105)
        return v105->ListID;
LABEL_139:
      v82 = wk;
      UnitMng = v82->UnitMng;
      playerID = v82->playerID;
      v85 = sBtlSearchUnit_ID(UnitMng, playerID);
      if (!v85)
        return -1;
      wk = v85;
LABEL_161:
      if (CheckLiveTarget(wk))
        return wk->ListID;
      return -1;
    case 2:
      v10 = wk;
      v15 = v10->UnitMng;
      v16 = v10->playerID;
      v17 = sBtlSearchUnit_ID(v15, v16);
      if (v17)
      {
        v18 = v17;
        if (CheckLiveTarget(v18))
          return v18->ListID;
      }
      if (member_num < 1)
        return -1;
      Nakama = sBtlGetNakama(0);
      v103 = sBtlGetNakama(1);
      v18 = v103;
      if (Nakama)
      {
        if (!CheckLiveTarget(Nakama))
          Nakama = 0;
        if (!v18)
        {
          if (!Nakama)
            return -1;
          return Nakama->ListID;
        }
      }
      else
      {
        if (!v103)
          return -1;
        Nakama = 0;
      }
      if (!CheckLiveTarget(v18))
        v18 = 0;
      if (Nakama && v18)
      {
        v158 = wk->pos.x;
        v159 = wk->pos.y;
        v161 = wk->pos.z;
        w = wk->pos.w;
        sub_1B33360(0, v158, v159, v161, w);
        sub_1B332C0(0, Nakama->pos.x, Nakama->pos.y, Nakama->pos.z, Nakama->pos.w);
        sub_1B33400(0);
        v162 = (loc_1CDE880)(0);
        sub_1B332C0(0, v18->pos.x, v18->pos.y, v18->pos.z, v18->pos.w);
        sub_1B33400(0);
        if (v162 < (loc_1CDE880)(0))
          return Nakama->ListID;
        return v18->ListID;
      }
      if (Nakama)
        return Nakama->ListID;
      if (v18)
        return v18->ListID;
      return -1;
    case 3:
      v20 = 0;
      v21 = 0;
      while (2)
      {
        v22 = wk->UnitMng;
        if (v20 < v22->number)
        {
          pUnit = v22->pUnitL[v20]->pUnit;
          if (pUnit)
          {
            if (sBtlCheckDamageTarget(pUnit))
            {
              if (((pUnit->side ^ wk->side) & 7) == 0)
              {
                v7[v21] = pUnit->ListID;
                Percentage = GetPercentage();
                v25 = (s64)(char *)v8 + 2 * v21++;
                *(u16 *)(v25 + 32) = Percentage;
              }
            }
          }
          ++v20;
          continue;
        }
        break;
      }
      if (v21 >= 1)
      {
        v91 = v21;
        v92 = &v7[0];
        v93 = &v8[0];
        result = -1;
        v94 = 101;
        do
        {
          v96 = *v93++;
          v95 = v96;
          if (v96 <= v94)
          {
            result = *v92;
            v94 = v95;
          }
          ++v92;
          --v91;
        }
        while (v91);
        return result;
      }
      return -1;
    case 4:
      v26 = 0;
      v27 = 0;
      while (2)
      {
        v28 = wk->UnitMng;
        if (v26 >= v28->number)
        {
          if (v27 < 1)
            return wk->ListID;
          v97 = v27;
          v98 = &v7[0];
          v99 = &v8[0];
          result = -1;
          v100 = 101;
          do
          {
            v102 = *v99++;
            v101 = v102;
            if (v102 <= v100)
            {
              result = *v98;
              v100 = v101;
            }
            ++v98;
            --v97;
          }
          while (v97);
          return result;
        }
        v29 = v28->pUnitL[v26]->pUnit;
        if (v29)
        {
          if (sBtlCheckDamageTarget(v29))
          {
            if (((v29->side ^ wk->side) & 7) == 0)
            {
              ListID = v29->ListID;
              if (wk->ListID != ListID)
              {
                v7[v27] = ListID;
                v31 = GetPercentage();
                v32 = (s64)(char *)v8 + 2 * v27++;
                *(u16 *)(v32 + 32) = v31;
              }
            }
          }
        }
        ++v26;
        continue;
      }
    case 5:
      v33 = (char *)wk->actaiwk->ai_target + 4 * arg;
      return *((u32 *)v33 + 8);
    case 6:
      return wk->ListID;
    case 7:
      v10 = wk;
      v34 = v10->UnitMng;
      aborttargetID = wk->actaiwk->aborttargetID;
      v36 = sBtlSearchUnit_ID(v34, aborttargetID);
      if (v36)
      {
        v37 = v36;
        if (CheckLiveTarget(v37) && (wk->side & v37->side) == 0)
          return wk->actaiwk->aborttargetID;
      }
      v39 = wk;
      v40 = v39->UnitMng;
      v41 = v39->playerID;
      v42 = sBtlSearchUnit_ID(v40, v41);
      if (!v42)
        return -1;
      wk = v42;
      goto LABEL_161;
    case 8:
      side = wk->side;
      SideList_AI = sBtlCreateSideList_AI(side, 1);
      count = SideList_AI->count;
      v47 = SideList_AI;
      if (count < 1)
        goto LABEL_220;
      if (count == 1)
      {
        pUnitL = SideList_AI->pUnitL;
LABEL_128:
        v79 = *(u64 *)(*(u64 *)(pUnitL + 32) + 24);
        sBtlDeleteUnitList(v47, 0);
        return *(u32 *)(v79 + 364);
      }
      else
      {
        v119 = 0;
        v120 = 49;
        while (1)
        {
          v121 = v47->pUnitL[v119]->pUnit;
          if (v120 >= (s32)GetPercentage())
            break;
          v120 += 50;
          if (++v119 >= v47->count)
          {
LABEL_220:
            sBtlDeleteUnitList(v47, 0);
            return -1;
          }
        }
        sBtlDeleteUnitList(v47, 0);
        return v121->ListID;
      }
    case 9:
      v49 = wk->side;
      v50 = sBtlCreateSideList_AI(v49, 1);
      if (v50->count < 1)
      {
        v104 = 2200.0;
        goto LABEL_178;
      }
      v51 = 2000.0;
      v52 = 0;
      v53 = 0;
      do
      {
        v57 = v50->pUnitL[v52]->pUnit;
        v166 = wk->pos;
        vct_A = v166;
        v59 = v57->pos;
        vct_B = v59;
        vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
        v60 = &vf00.x;
        v61 = v60[4];
        v62 = v60[5];
        v63 = v60[6];
        v55 = v50->count;
        v56 = sqrtf((f32)((f32)(v61 * v61) + (f32)(v62 * v62)) + (f32)(v63 * v63));
        if (v51 >= v56)
        {
          v51 = v56;
          v53 = v52;
        }
        ++v52;
      }
      while (v52 < v55);
      v104 = v51 + 200.0;
      if (v53 < (s32)v55)
      {
        v105 = v50->pUnitL[v53]->pUnit;
        goto LABEL_180;
      }
LABEL_178:
      v105 = 0;
LABEL_180:
      sBtlDeleteUnitList(v50, 0);
      v107 = sBtlCreateSideList_AI(wk->side, 1);
      if (v107->count < 1)
      {
LABEL_214:
        sBtlDeleteUnitList(v107, 0);
        if (v105)
          return v105->ListID;
        return -1;
      }
      v108 = 0;
      v165 = 0;
      while (2)
      {
        if ((wk->para->badstatus & 0x305F) == 0)
        {
          v110 = v107->pUnitL[v108]->pUnit;
          v169 = wk->pos;
          vct_A = v169;
          v112 = v110->pos;
          goto LABEL_189;
LABEL_190:
          goto LABEL_191;
LABEL_192:
          goto LABEL_193;
LABEL_194:
          goto LABEL_195;
LABEL_189:
          vct_B = v112;
          goto LABEL_190;
LABEL_191:
          vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
          goto LABEL_192;
LABEL_193:
          v113 = &vf00.x;
          v114 = v113[4];
          v115 = v113[5];
          v116 = v113[6];
          goto LABEL_194;
LABEL_195:
          if (v104 >= sqrtf((f32)((f32)(v114 * v114) + (f32)(v115 * v115)) + (f32)(v116 * v116)))
            v165 = v108;
        }
        v109 = v107->count;
        if (++v108 < v109)
          continue;
        break;
      }
      if (v165 >= (s32)v109)
        goto LABEL_214;
      wk = v107->pUnitL[v165]->pUnit;
      sBtlDeleteUnitList(v107, 0);
      return wk->ListID;
    case 10:
      v65 = wk->side;
      v66 = sBtlCreateSideList_AI(v65, 1);
      v67 = (u32)v66->count;
      v47 = v66;
      if ((s32)v67 < 1)
        goto LABEL_220;
      v68 = 0.0;
      v69 = 0;
      v70 = 0;
      do
      {
        now = v66->pUnitL[v69]->pUnit->para->now;
        maxhp = now->maxhp;
        if (v68 < (f32)((f32)((f32)now->hp * 100.0) / maxhp))
        {
          v68 = (f32)((f32)now->hp * 100.0) / maxhp;
          v70 = v69;
        }
        ++v69;
      }
      while (v67 != v69);
      goto LABEL_126;
    case 11:
      v73 = wk->side;
      v74 = sBtlCreateSideList_AI(v73, 1);
      v67 = (u32)v74->count;
      v47 = v74;
      if ((s32)v67 < 1)
        goto LABEL_220;
      v75 = 0;
      v76 = 100.0;
      v70 = 0;
      do
      {
        v77 = v74->pUnitL[v75]->pUnit->para->now;
        v78 = v77->maxhp;
        if (v76 >= (f32)((f32)((f32)v77->hp * 100.0) / v78))
        {
          v76 = (f32)((f32)v77->hp * 100.0) / v78;
          v70 = v75;
        }
        ++v75;
      }
      while (v67 != v75);
LABEL_126:
      if (v70 >= (s32)v67)
        goto LABEL_220;
      pUnitL = (s64)v47->pUnitL + 8 * v70;
      goto LABEL_128;
    case 12:
      if (member_num < 1)
        goto LABEL_139;
      v80 = sBtlGetNakama(0);
      if (!v80)
        goto LABEL_139;
      goto LABEL_136;
    case 13:
      if (member_num < 1)
        goto LABEL_139;
      v80 = sBtlGetNakama(1);
      if (!v80)
        goto LABEL_139;
LABEL_136:
      wk = v80;
      if (!CheckLiveTarget(wk))
        goto LABEL_139;
      return wk->ListID;
    case 14:
      v86 = arg;
      v87 = wk->actaiwk->ai_target[arg];
      if (v87 == -1)
        goto LABEL_260;
      v88 = v10->UnitMng;
      v90 = sBtlSearchUnit_ID(v88, v87);
      if (!v90)
        goto LABEL_260;
      v142 = v90;
      if ((v90->side & 1) == 0)
      {
        if (CheckLiveTarget(v142) && 1000 * v142->para->now->hp / v142->para->now->maxhp <= 900)
        {
          goto LABEL_287;
        }
      }
LABEL_260:
      v143 = wk->side;
      para = wk->para;
      BadStatus = sBtlGetBadStatus(para);
      if ((v143 & 2) != 0)
        v147 = 1;
      else
        v147 = 2;
      if (BadStatus == 7)
        v148 = v147;
      else
        v148 = v143;
      SideList = sBtlCreateSideList(v148, 0);
      v150 = SideList->count;
      v151 = SideList;
      if (v150 < 1)
      {
        v153 = 1000;
      }
      else
      {
        v152 = 0;
        v153 = 1000;
        m_Items = SideList->pUnitL;
        do
        {
          v155 = *(u64 *)(*(u64 *)(m_Items + 8 * v152) + 24);
          v156 = 1000
               * *(u32 *)(*(u64 *)(*(u64 *)(v155 + 376) + 40) + 16)
               / *(u32 *)(*(u64 *)(*(u64 *)(v155 + 376) + 40) + 20);
          if ((u32)(v156 - 1) <= 0x3E6 && v153 > v156)
          {
            v153 = 1000
                 * *(u32 *)(*(u64 *)(*(u64 *)(v155 + 376) + 40) + 16)
                 / *(u32 *)(*(u64 *)(*(u64 *)(v155 + 376) + 40) + 20);
            wk->actaiwk->ai_target[v86] = *(u32 *)(v155 + 364);
            v150 = SideList->count;
          }
          ++v152;
        }
        while (v152 < v150);
      }
      sBtlDeleteUnitList(v151, 0);
      if (v153 > 999)
        return wk->ListID;
LABEL_287:
      v33 = (char *)wk->actaiwk->ai_target + 4 * v86;
      return *((u32 *)v33 + 8);
    default:
      return -1;
  }
}

// 0x1daf500
s32 sBtlCheckEnemyTarget(SBTLUNIT_WORK *wk, s32 id) {
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v9;
  sdatUnitWork_t *para;
  u16 area;
  SBTLUNIT_WORK *v14;
  s32 v15;

  UnitMng = wk->UnitMng;
  v9 = sBtlSearchUnit_ID(UnitMng, id);
  if (v9)
  {
    if ((~v9->side & 0x81) == 0 && (v9->hstatus & 0x100) != 0)
      return -1;
  }
  para = wk->para;
  if (sBtlGetBadStatus(wk->para) - 7 <= 1)
  {
    area = sBtlGetSkilltbl(wk->actwk->use_skillid)->area;
    if ((area & 0x4000) != 0)
    {
      v14 = wk;
      v15 = 8;
    }
    else
    {
      v14 = wk;
      v15 = 4;
    }
    return sBtlGetUseTable_Target(v14, v15, 0);
  }
  if ((wk->status & 0x100000) == 0)
  {
    if (!v9)
      return -1;
    return id;
  }
  if (v9)
    return id;
  return wk->playerID;
}

// 0x1db26e0
bool sBtlResetAIPattern(SBTLUNIT_WORK *wk, s32 mode) {
  SBTLACTAI_WORK *actaiwk;

  actaiwk = wk->actaiwk;
  actaiwk->datamode = mode;
  actaiwk->dataflg = 0;
  *(u64 *)actaiwk->data_p = 0;
  return 1;
}

// 0x1dcab40
bool sBtlEAIProc_BtlWait(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  SBTLACTAI_WORK *v6;

  actaiwk = wk->actaiwk;
  if (actaiwk->cmpframe > actaiwk->frame)
    return 1;
  actaiwk->status &= ~1u;
  sBtlResetAAI(wk);
  v6 = wk->actaiwk;
  v6->mode = 0;
  v6->stat = 1;
  sBtlSetMotion(wk, 0, 4, 0, 0);
  return 1;
}
