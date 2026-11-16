#include "types.h"
#include "SKLID.h"
#include "sbtl.h"
#include "sbtlactai.h"
#include "sbtlai.h"
#include "sbtlsupport.h"
#include "sbtlunit.h"
#include "scr.h"
#include "sdf_vu0.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

static s32 RunReactProcess(void);
static s32 GetLowestLvlCharSortCallBack(void *_a, void *_b);
SBTLUNIT_WORK *Support_GetNakamaData(s32 idx);

// macros
// 0x211f960: s32 GET_LOWEST_LVL_CHAR(void)
static inline s32 GET_LOWEST_LVL_CHAR(void) {
  u32 *v1;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v6;
  SBTLUNIT_WORK *NakamaData;
  SBTLUNIT_WORK *v10;
  s32 level;
  s32 v12;
  s32 v13;

  v1 = NewSpecific(s32, 3u);
  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v6 = sBtlSearchUnit_ID(UnitMng, playerID);
  NakamaData = Support_GetNakamaData(0);
  v10 = Support_GetNakamaData(1);
  if (v6)
  {
    level = v6->para->level;
    v1[8] = level;
    if (NakamaData)
      goto LABEL_11;
  }
  else
  {
    level = 999;
    v1[8] = 999;
    if (NakamaData)
    {
LABEL_11:
      v12 = 0x20000;
      v1[9] = NakamaData->para->level;
      if (v10)
        goto LABEL_12;
      goto LABEL_26;
    }
  }
  v12 = 0x20000;
  v1[9] = 999;
  if (v10)
  {
LABEL_12:
    v13 = v10->para->level;
    if (level == v13)
      v12 = 851968;
    else
      v12 = 0x20000;
    v1[10] = v13;
    if (!NakamaData)
      goto LABEL_18;
    goto LABEL_16;
  }
LABEL_26:
  v1[10] = 999;
  if (!NakamaData)
    goto LABEL_18;
LABEL_16:
  if (level == NakamaData->para->level)
    v12 = 786432;
LABEL_18:
  if (v6 && level == v6->para->level)
    v12 = 0x20000;
  scrSetIntReturnValue(v12);
  return 1;
}

// 0x211eee0
s32 sBtlSetSkillTarget(SBTLUNIT_WORK *wk, SKLID skillID, u32 targetCode) {
  SBTLUNIT_WORK *v8;
  s32 UseTable_Target;
  s32 v11;
  SBTLACTION_WORK *actwk;
  SBTLACTAI_WORK *actaiwk;

  wk->actwk->use_skillid = skillID;
  if (skillID == 479)
  {
    v8 = wk->scrUnitList[2];
    goto LABEL_11;
  }
  if (skillID == 480)
  {
    v8 = wk->scrUnitList[1];
LABEL_11:
    wk->actaiwk->targetID = v8->ListID;
    goto LABEL_15;
  }
  UseTable_Target = sBtlGetUseTable_Target(wk, HIWORD(targetCode), (u16)targetCode);
  sBtlSetTargetID(wk, UseTable_Target);
  v11 = sBtlCheckEnemyTarget(wk, wk->actaiwk->targetID);
  sBtlSetTargetID(wk, v11);
LABEL_15:
  actwk = wk->actwk;
  if (actwk->status - 9 >= 2)
    actwk->status = 1;
  wk->actaiwk->dataflg = 0;
  sBtlSetAIMode(wk);
  actaiwk = wk->actaiwk;
  actaiwk->stat = 1;
  wk->aiwk->stat = 2;
  actaiwk->mode = 14;
  return 1;
}

// 0x211f0a0
s32 sBtlGetNumDistance(f32 dist) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v7;
  SBTLUNIT_WORK *NakamaData;
  SBTLUNIT_WORK *scrunit;
  struct sdfVector4_t v14;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  struct sdfVector4_t v21;
  f32 *v22;
  f32 v23;
  f32 v24;
  f32 v25;
  SBTLUNIT_WORK *v27;
  SBTLUNIT_WORK *v28;
  struct sdfVector4_t v30;
  f32 *v31;
  f32 v32;
  f32 v33;
  f32 v34;
  struct sdfVector4_t pos;
  struct sdfVector4_t v41;
  struct sdfVector4_t v42;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v7 = sBtlSearchUnit_ID(UnitMng, playerID);
  NakamaData = Support_GetNakamaData(0);
  scrunit = wk->scrunit;
  if (v7)
  {
    pos = scrunit->pos;
    vct_A = pos;
    v14 = v7->pos;
    vct_B = v14;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    p_x = &vf00.x;
    x = p_x[4];
    y = p_x[5];
    z = p_x[6];
    if (sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z)) >= dist)
    {
      LODWORD(v7) = 0;
      if (!NakamaData)
        goto LABEL_43;
      goto LABEL_30;
    }
    LODWORD(v7) = 1;
  }
  if (!NakamaData)
    goto LABEL_43;
LABEL_30:
  v41 = scrunit->pos;
  vct_A = v41;
  v21 = NakamaData->pos;
  vct_B = v21;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v22 = &vf00.x;
  v23 = v22[4];
  v24 = v22[5];
  v25 = v22[6];
  if (sqrtf((f32)((f32)(v23 * v23) + (f32)(v24 * v24)) + (f32)(v25 * v25)) < dist)
    LODWORD(v7) = (u32)v7 | 2;
LABEL_43:
  v27 = Support_GetNakamaData(1);
  if (!v27)
    return (s32)v7;
  v28 = v27;
  v42 = scrunit->pos;
  vct_A = v42;
  v30 = v28->pos;
  vct_B = v30;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v31 = &vf00.x;
  v32 = v31[4];
  v33 = v31[5];
  v34 = v31[6];
  if (sqrtf((f32)((f32)(v32 * v32) + (f32)(v33 * v33)) + (f32)(v34 * v34)) < dist)
    LODWORD(v7) = (u32)v7 + 2;
  return (s32)v7;
}

// 0x211f830
static s32 RunReactProcess(void) {
  SBTLUNIT_WORK *scrunit;
  SBTLAI_WORK *aiwk;
  s32 mode;
  s32 NumDistance;
  SBTLAI_WORK *v8;
  u32 *p_scrflag;
  u32 v10;
  u32 v11;
  SBTLAI_WORK *v13;
  u32 scrflag;

  scrunit = wk->scrunit;
  aiwk = scrunit->aiwk;
  if ((aiwk->scrflag & 0x80) == 0)
    return 0;
  mode = scrunit->actaiwk->mode;
  if (mode != 12 && mode != 2)
    return 0;
  NumDistance = sBtlGetNumDistance(aiwk->scrReactDist);
  switch (NumDistance)
  {
    case 3:
      goto LABEL_15;
    case 2:
      sBtlSetSkillTarget(scrunit, scrunit->aiwk->scrReactSkillID, 0x10000u);
      v13 = scrunit->aiwk;
      scrflag = v13->scrflag;
      p_scrflag = &v13->scrflag;
      v10 = scrflag;
      if ((scrflag & 0x4000) == 0)
        return 1;
      goto LABEL_16;
    case 1:
LABEL_15:
      sBtlSetSkillTarget(scrunit, scrunit->aiwk->scrReactSkillID, 0x20000u);
      v8 = scrunit->aiwk;
      v11 = v8->scrflag;
      p_scrflag = &v8->scrflag;
      v10 = v11;
      if ((v11 & 0x4000) == 0)
        return 1;
LABEL_16:
      *p_scrflag = v10 & 0xFFFFFF7F;
      return 1;
  }
  return 0;
}

// 0x211fb20
static s32 GetLowestLvlCharSortCallBack(void *_a, void *_b) {
  Il2CppObject *v4;
  Il2CppObject *v5;
  s32 klass;

  v4 = a;
  if (!v4)
    goto LABEL_10;
  v5 = v4;
  a = Unbox(v4);
  if (!b)
  {
LABEL_10:
    v5 = (loc_3BDC60)(a, b);
  }
  klass = a->klass;
  if (klass <= *(u32 *)Unbox(b))
    return -1;
  else
    return 1;
}
