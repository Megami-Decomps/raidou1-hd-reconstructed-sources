#include "types.h"
#include "SBTLUNIT_MARK.h"
#include "SKLID.h"
#include "cmpitem.h"
#include "dat.h"
#include "dds3kerneldraw.h"
#include "dds3padmanager.h"
#include "evtbit.h"
#include "fld.h"
#include "localize.h"
#include "sbattle.h"
#include "sbtl.h"
#include "sbtlcalc.h"
#include "sbtlencount.h"
#include "sbtlmain.h"
#include "sbtlscript.h"
#include "sbtlskill.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sdf_vu0.h"
#include "sdfmodel.h"
#include "sdfquat.h"

typedef struct DEVILDATA_WORK DEVILDATA_WORK;
typedef struct DEVIL_HUUMAITEM DEVIL_HUUMAITEM;
typedef struct SBTLANIM_HOKAN SBTLANIM_HOKAN;
typedef struct SBTLDMG_CYLINDERWORK SBTLDMG_CYLINDERWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

static DEVILDATA_WORK *devil_tbldata[2];
static DEVIL_HUUMAITEM **devil_huumaitem;
u8 *wajutsu_namedata;
u8 *prank_namedata;
u8 *sbtlsysmsg_data;
u8 *player_namedata;
u8 *meirei_data;
u8 *num_data;
u8 *badst_namedata;
static sdfVector4_t _yv;
static sdfVector4_t _yvX;
s32 nowSkillHelpID;
s32 nowItemHelpID;

static sdfVector4_t GetTgtVec(f32 deg, const sdfVector4_t *rot, const sdfVector4_t *dir, const sdfVector4_t *pos);

// 0x1fc9f00
bool sBtlSetVibeFadeIn(s32 index, s32 power, s32 frame) {
  char v5;
  s64 v8;
  s32 *vibe_frame;
  char *v12;

  v5 = power;
  v8 = index;
  wk->vibe_startf[v8] = frame;
  vibe_frame = wk->vibe_frame;
  v12 = (char *)wk->vibe_power + index;
  vibe_frame[v8] = frame;
  v12[32] = v5;
  wk->vibe_type[index] = 1;
  return 1;
}

// 0x1fc9fd0
bool sBtlSetVibeFadeOut(s32 index, s32 power, s32 frame) {
  char v5;
  s64 v8;
  s64 v11;
  char *v12;

  v5 = power;
  v8 = index;
  wk->vibe_startf[v8] = frame;
  v11 = (s64)wk->vibe_frame + v8 * 4;
  v12 = (char *)wk->vibe_power + index;
  *(u32 *)(v11 + 32) = frame;
  v12[32] = v5;
  wk->vibe_type[index] = 0;
  return 1;
}

// 0x1fca090
void sBtlStopVibe(void) {
  s32 *vibe_frame;
  u8 *vibe_power;
  SBATTLE_WORK *v5;
  s32 *v6;
  u8 *v7;

  wk->vibe_startf[0] = 0;
  vibe_frame = wk->vibe_frame;
  vibe_power = wk->vibe_power;
  vibe_frame[0] = 0;
  vibe_power[0] = 0;
  wk->vibe_type[0] = 0;
  v5 = wk;
  v5->vibe_startf[1] = 0;
  v6 = v5->vibe_frame;
  v7 = v5->vibe_power;
  v6[1] = 0;
  v7[1] = 0;
  wk->vibe_type[1] = 0;
  dds3PadActAllStop();
}

// 0x1fca190
void sBtlUpdateVibe(void) {
  s64 v1;
  char v3;
  char *v4;
  char v5;
  s32 v7;
  f32 v9;
  f32 v10;
  u8 v11;
  SBATTLE_WORK *v12;
  u8 v14;

  v1 = 0;
  v3 = 1;
  do
  {
    v5 = v3;
    if (!wk->vibe_power[v1])
      goto LABEL_5;
    if (wk->vibe_frame[v1] >= 1)
    {
      v7 = wk->vibe_startf[v1];
      if (v7 >= 1)
      {
        v7 = wk->vibe_startf[v1];
        v9 = (f32)wk->vibe_frame[v1] / (f32)v7;
        if (wk->vibe_type[v1])
          v10 = 1.0 - v9;
        else
          v10 = (f32)wk->vibe_frame[v1] / (f32)v7;
        LOBYTE(v9) = wk->vibe_power[v1];
        v11 = (s32)(f32)(v10 * (f32)LODWORD(v9));
        dds3PadAct(v1, v11, 0x64u);
        v4 = (char *)wk->vibe_frame + 4 * v1;
        --*((u32 *)v4 + 8);
        goto LABEL_5;
      }
    }
    v12 = wk;
    if (v12->vibe_type[v1] == 1)
    {
      v14 = v12->vibe_power[v1];
      dds3PadAct(v1, v14, 0x64u);
      goto LABEL_5;
    }
    dds3PadAct(v1, 0, 0);
    wk->vibe_startf[v1] = 0;
LABEL_5:
    v3 = 0;
    v1 = 1;
  }
  while ((v5 & 1) != 0);
}

// 0x1fca4c0
bool SetVibe(s32 in, s32 life, s32 out, s32 power) {
  u8 v5;
  SBTLVIBE_WORK *vibe;
  SBTLVIBE_WORK *v12;
  SBTLVIBE_WORK *v17;

  v5 = power;
  sBtlStopVibe();
  vibe = wk->vibe;
  v12 = vibe[0];
  v12->in = in;
  v12->out = out;
  v12->power = v5;
  v12->life = life;
  v12->count = 0;
  v17 = vibe[1];
  v17->in = in;
  v17->out = out;
  v17->power = v5;
  v17->life = life;
  v17->count = 0;
  return 1;
}

// 0x1fca5f0
bool sBtlCalcVibe(void) {
  s64 v1;
  char v2;
  char v4;
  SBTLVIBE_WORK *v5;
  s32 life;
  s32 out;
  SBTLVIBE_WORK *v8;
  s32 v9;
  s32 v10;
  SBTLVIBE_WORK *v13;
  s32 *p_count;
  s32 count;
  u8 power;
  s32 in;
  s64 v21;
  s64 v22;
  u8 v24;
  SBATTLE_WORK *v26;
  s64 v27;
  s64 v28;

  v1 = 0;
  v2 = 1;
  do
  {
    v4 = v2;
    v5 = wk->vibe[v1];
    out = v5->out;
    life = v5->life;
    if (life < out)
      break;
    if (!v5->count)
    {
      power = v5->power;
      in = v5->in;
      goto LABEL_21;
LABEL_22:
      goto LABEL_23;
LABEL_21:
      goto LABEL_22;
LABEL_23:
      wk->vibe_startf[v1] = in;
      v21 = (s64)wk->vibe_frame + 4 * v1;
      v22 = (s64)wk->vibe_power + v1;
      *(u32 *)(v21 + 32) = in;
      *(u8 *)(v22 + 32) = power;
      wk->vibe_type[v1] = 1;
      goto LABEL_11;
    }
LABEL_11:
    v8 = wk->vibe[v1];
    v9 = v8->life;
    if (v9 >= 1)
    {
      v10 = v8->out;
      if (v8->count == v9 - v10)
        goto LABEL_26;
      goto LABEL_9003;
      if (v8->count == v8->life - v10)
      {
LABEL_26:
        v24 = v8->power;
        goto LABEL_28;
LABEL_29:
        goto LABEL_30;
LABEL_28:
        goto LABEL_29;
LABEL_30:
        v26 = wk;
        v26->vibe_startf[v1] = v10;
        v27 = (s64)v26->vibe_frame + 4 * v1;
        v28 = (s64)v26->vibe_power + v1;
        *(u32 *)(v27 + 32) = v10;
        *(u8 *)(v28 + 32) = v24;
        wk->vibe_type[v1] = 0;
        goto LABEL_16;
      }
LABEL_9003:
    }
LABEL_16:
    v13 = wk->vibe[v1];
    count = v13->count;
    p_count = &v13->count;
    *p_count = count + 1;
    LimitRange(p_count, 0, 0x7FFF);
    v2 = 0;
    v1 = 1;
  }
  while ((v4 & 1) != 0);
  return life >= out;
}

// 0x1fc6e80
bool sBtlGetUnitHelperPos(SBTLUNIT_WORK *wk, SBTLUNIT_MARK mark) {
  struct sdfVector4_t scrPos3;

  if (!wk)
    return 1;
  if (wk->para->devilid == 259)
  {
    switch (mark)
    {
      case 300:
        mark = 101;
        break;
      case 302:
        mark = 102;
        if (!wk->hModel)
          goto LABEL_21;
        goto LABEL_14;
      case 301:
        scrPos3 = wk->actaiwk->scrPos3;
        goto LABEL_28;
    }
  }
  if (!wk->hModel)
    goto LABEL_21;
LABEL_14:
  if ((wk->side & 7) != 0 && ((wk->status & 0x40) == 0 || !wk->changeflg))
  {
    if (!sdfModelGetMarkPos(wk->hEveUnit->Model->modelRoot, mark))
      sdfModelGetMarkPos(wk->hEveUnit->Model->modelRoot, 0);
    return 1;
  }
LABEL_21:
  scrPos3 = wk->pos;
LABEL_28:
  vct_A = scrPos3;
  return 1;
}

// 0x1fca9d0
bool sBtlGetUnitHelperMatrix(SBTLUNIT_WORK *wk, SBTLUNIT_MARK mark) {
  if (GetUnitHelperMatrix(wk, mark))
    return 1;
  if (wk->hModel && ((wk->status & 0x40) == 0 || !wk->changeflg))
  {
    sdfModelGetMarkPosMatrix(wk->hEveUnit->Model->modelRoot, mark);
    return 1;
  }
  mtx_A = identityMatrix;
  return 1;
}

// 0x1fcab70
void sBtlGetQuatFromMatrix(const sdfMatrix4_t *mat) {
  f32 Item_60922080;
  f32 v4;
  f32 v5;
  f32 v6;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  _BOOL4 v13;
  f32 v14;
  s32 v15;
  s32 v16;
  s32 v17;
  s32 v18;
  s32 v19;
  f32 v20;
  s32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 *v25;
  f32 *v26;
  f32 *v27;
  f32 *v28;
  f32 v29;
  f32 v30;
  f32 *v31;
  f32 v32;
  f32 v33;
  f32 *v34;
  f32 v35;
  f32 v36;
  s64 v37;
  void *v40;
  void *v41;
  char *v42;
  void *v43;
  u8 v44[4];
  f32 v45;
  s64 v46;

  v46 = 0;
  v45 = 0.0;
  Item_60922080 = get_Item_60922080(mat, 0, 0);
  v4 = get_Item_60922080(mat, 5, 0);
  v5 = (f32)((f32)(Item_60922080 + v4) + get_Item_60922080(mat, 10, 0)) + 1.0;
  if (v5 <= 1.0)
  {
    v12 = get_Item_60922080(mat, 0, 0);
    v13 = v12 <= get_Item_60922080(mat, 5, 0);
    v14 = get_Item_60922080(mat, 10, 0);
    if (v14 <= get_Item_60922080(mat, v13 | (4 * v13), 0))
      v15 = v13;
    else
      v15 = 2;
    v16 = 4 * v15;
    if ((u32)(v15 + 1) < 3)
      v17 = v15 + 1;
    else
      v17 = v15 - 2;
    if ((u32)(v17 + 1) < 3)
      v18 = v17 + 1;
    else
      v18 = v17 - 2;
    v19 = 4 * v17;
    v20 = get_Item_60922080(mat, 5 * v15, 0);
    v21 = 4 * v18;
    v22 = get_Item_60922080(mat, 5 * v17, 0);
    v23 = sqrtf((f32)((f32)(v20 - v22) - get_Item_60922080(mat, 5 * v18, 0)) + 1.0);
    v24 = v23 + v23;
    if ((f32)(v23 + v23) == 0.0)
    {
      if (v15)
      {
        if (v15 == 2)
          v25 = &v45;
        else
          v25 = &v46;
      }
      else
      {
        v25 = (f32 *)&v46 + 1;
      }
      *v25 = 1.0;
      v26 = (f32 *)&v46 + 1;
      switch (v17)
      {
        case 0:
          goto LABEL_24;
        case 1:
          v26 = &v46;
          goto LABEL_24;
        case 2:
          v26 = &v45;
          goto LABEL_24;
        case 3:
          v26 = v44;
LABEL_24:
          *v26 = 0.0;
          v27 = (f32 *)&v46 + 1;
          switch (v18)
          {
            case 0:
              goto LABEL_28;
            case 1:
              v27 = &v46;
              goto LABEL_28;
            case 2:
              v27 = &v45;
              goto LABEL_28;
            case 3:
              v27 = v44;
LABEL_28:
              v8 = 0.0;
              *v27 = 0.0;
              goto LABEL_43;
            default:
              goto LABEL_50;
          }
        default:
          break;
      }
    }
    else
    {
      if (v15)
      {
        if (v15 == 2)
          v28 = &v45;
        else
          v28 = &v46;
      }
      else
      {
        v28 = (f32 *)&v46 + 1;
      }
      *v28 = v24 * 0.25;
      v29 = get_Item_60922080(mat, v19 + v15, 0);
      v30 = get_Item_60922080(mat, v17 + v16, 0);
      v31 = (f32 *)&v46 + 1;
      switch (v17)
      {
        case 0:
          goto LABEL_38;
        case 1:
          v31 = &v46;
          goto LABEL_38;
        case 2:
          v31 = &v45;
          goto LABEL_38;
        case 3:
          v31 = v44;
LABEL_38:
          *v31 = (f32)(v29 + v30) / v24;
          v32 = get_Item_60922080(mat, v21 + v15, 0);
          v33 = get_Item_60922080(mat, v18 + v16, 0);
          v34 = (f32 *)&v46 + 1;
          switch (v18)
          {
            case 0:
              goto LABEL_42;
            case 1:
              v34 = &v46;
              goto LABEL_42;
            case 2:
              v34 = &v45;
              goto LABEL_42;
            case 3:
              v34 = v44;
LABEL_42:
              *v34 = (f32)(v32 + v33) / v24;
              v35 = get_Item_60922080(mat, v21 + v17, 0);
              v8 = (f32)-(f32)(v35 - get_Item_60922080(mat, v18 + v19, 0)) / v24;
              goto LABEL_43;
            default:
              goto LABEL_50;
          }
        default:
          break;
      }
    }
LABEL_50:
    v40 = InitializedMetadata(&System_IndexOutOfRangeException);
    v41 = Allocate(v40);
    v42 = InitializedMetadata(&"Invalid Vector4 index!");
    v43 = InitializedMetadata(&Method_UnityEngine_Vector4_set_Item__);
  }
  v6 = sqrtf(v5);
  v7 = v6 + v6;
  v8 = (f32)(v6 + v6) * -0.25;
  v9 = get_Item_60922080(mat, 9, 0);
  *((f32 *)&v46 + 1) = (f32)(v9 - get_Item_60922080(mat, 6, 0)) / v7;
  v10 = get_Item_60922080(mat, 2, 0);
  *(f32 *)&v46 = (f32)(v10 - get_Item_60922080(mat, 8, 0)) / v7;
  v11 = get_Item_60922080(mat, 4, 0);
  v45 = (f32)(v11 - get_Item_60922080(mat, 1, 0)) / v7;
LABEL_43:
  v36 = v45;
  v37 = v46;
  vct_A.x = *((f32 *)&v37 + 1);
  LODWORD(vct_A.y) = v37;
  vct_A.z = v36;
  vct_A.w = v8;
  Normalize();
}

// 0x1fcb090
void sBtlQuatFromVector(sdfVector4_t *qt, f32 x, f32 y, f32 z, f32 rad) {
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
  f32 v21;
  f32 v22;
  float32x2_t *v26;
  u64 v27;
  f32 v28;

  v11 = (f32)(rad + 1.5708) * 0.15915494;
  v12 = (s32)v11;
  if (v11 == INFINITY)
    v12 = -2147500000.0;
  v13 = v11 - v12;
  if ((f32)(v11 - v12) <= 0.5)
  {
    v14 = v11 - v12;
    if (v13 < -0.5)
      v14 = v13 + 1.0;
  }
  else
  {
    v14 = v13 + -1.0;
  }
  v15 = -0.5 - v14;
  if (v14 >= -0.25)
    v15 = v14;
  if (v14 > 0.25)
    v16 = 0.5 - v14;
  else
    v16 = v15;
  v17 = v16 * 4.0;
  v18 = v17 * v17;
  v28 = sqrtf((f32)(1.0 - (f32)((f32)((f32)((f32)((f32)(v17 * 1.5708) + (f32)((f32)(v17 * (f32)(v17 * v17)) * -0.6459637)) + (f32)((f32)(v18 * (f32)(v17 * (f32)(v17 * v17))) * 0.07968968)) + (f32)((f32)(v18 * (f32)(v18 * (f32)(v17 * (f32)(v17 * v17)))) * -0.0046737655)) + (f32)((f32)(v18 * (f32)(v18 * (f32)((f32)(v17 * v17) * (f32)(v17 * (f32)(v17 * v17))))) * 0.00015148419))) * 0.5);
  if (v13 <= 0.5)
  {
    if (v13 < -0.5)
      v13 = v13 + 1.0;
  }
  else
  {
    v13 = v13 + -1.0;
  }
  v19 = -0.5 - v13;
  if (v13 >= -0.25)
    v19 = v13;
  if (v13 > 0.25)
    v19 = 0.5 - v13;
  v20 = v19 * 4.0;
  v21 = v20 * v20;
  v22 = sqrtf((f32)((f32)((f32)((f32)((f32)((f32)(v20 * 1.5708) + (f32)((f32)(v20 * (f32)(v20 * v20)) * -0.6459637)) + (f32)((f32)((f32)(v20 * v20) * (f32)(v20 * (f32)(v20 * v20))) * 0.07968968)) + (f32)((f32)(v21 * (f32)(v21 * (f32)(v20 * (f32)(v20 * v20)))) * -0.0046737655)) + (f32)((f32)(v21 * (f32)(v21 * (f32)((f32)(v20 * v20) * (f32)(v20 * (f32)(v20 * v20))))) * 0.00015148419)) + 1.0) * 0.5);
  vct_A.x = x;
  vct_A.y = y;
  vct_A.z = z;
  vct_A.w = 1.0;
  sub_1949110(0);
  v27 = vmul_n_f32(v26[2], v28).n64_u64[0];
  qt->z = v28 * v26[3].n64_f32[0];
  qt->w = v22;
  *(u64 *)&qt->x = v27;
}

// 0x1fcb410
f32 sBtlGetUnitDeg(const sdfVector4_t *rot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;

  w = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  return EulerAngleAxisY() * 57.29578;
}

// 0x1fcb500
void sBtlAddUnitDeg(SBTLUNIT_WORK *wk, f32 deg) {
  f32 i;

  for (i = wk->mv_rotbk + deg; ; i = i + 360.0)
  {
    while (i >= 360.0)
    {
      i = i + -360.0;
      if (i < 0.0)
        goto LABEL_6;
    }
    if (i >= 0.0)
      break;
LABEL_6:
    ;
  }
  wk->mv_rotbk = i;
}

// 0x1fcb560
bool sBtlGetRotateDeg(const sdfVector4_t *rot, f32 deg) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  struct sdfVector4_t yv;

  w = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  yv = _yv;
  vct_A = yv;
  FromRotation(deg * -0.017453292);
  vct_B = vct_A;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  Mult();
  return 1;
}

// 0x1fcb770
void sBtlSetRotateDeg(SBTLUNIT_WORK *wk) {
  struct sdfVector4_t rot;

  rot = wk->rot;
  vct_A = rot;
  wk->mv_rotbk = EulerAngleAxisY() * -57.29578;
}

// 0x1fcb870
bool sBtlGetRotateDegX(const sdfVector4_t *rot, f32 deg) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  struct sdfVector4_t yvX;

  w = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  yvX = _yvX;
  vct_A = yvX;
  FromRotation(deg * -0.017453292);
  vct_B = vct_A;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  Mult();
  return 1;
}

// 0x1fcba80
s32 sBtlCheckCrossBox(const sdfVector4_t *vector1, f32 r1, u8 side, const sdfVector4_t *vector2, f32 width, f32 height) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 *v21;
  f32 v22;
  f32 *v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v31;
  f32 v33;
  f32 v34;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 *v43;
  u32 *v44;
  f32 *v45;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 *v53;
  f32 *v55;
  f32 v56;
  f32 v57;
  f32 v58;
  sdfVector4_t v61;
  sdfVector4_t v62;
  sdfVector4_t v63;
  f32 vector1a;
  u64 vector1_4;
  f32 vector1_12;
  f32 v68;
  sdfVector4_t v69;
  sdfVector4_t v70;
  sdfVector4_t v71;

  w = vector1->w;
  z = vector1->z;
  y = vector1->y;
  x = vector1->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v15 = vct_A.w;
  vector1_12 = vct_A.x;
  v16 = vct_A.z;
  v68 = vct_A.y;
  v18 = vector2->z;
  v17 = vector2->w;
  v20 = vector2->x;
  v19 = vector2->y;
  v21 = &vf00.x;
  v21[4] = v20;
  v21[5] = v19;
  v21[6] = v18;
  v21[7] = v17;
  v22 = v68;
  v23 = &vf00.x;
  v24 = v23[4];
  v25 = v23[5];
  v27 = v23[6];
  v26 = v23[7];
  v31 = width;
  if (v25 < v22)
    goto LABEL_36;
  vector1a = v24;
  vector1_4 = __PAIR64__(LODWORD(v26), LODWORD(v27));
  v33 = v16;
  v34 = v15;
  v36 = vct_A.x;
  v37 = vct_A.z;
  v38 = vct_A.w;
  v39 = vct_A.y - height;
  v69.x = vector1_12;
  v69.z = v33;
  v69.w = v34;
  v69.y = v68;
  *(u64 *)&v61.z = __PAIR64__(LODWORD(v38), LODWORD(v37));
  *(u64 *)&v61.x = __PAIR64__(LODWORD(v39), LODWORD(v36));
  v16 = v33;
  v15 = v34;
  v26 = *((f32 *)&vector1_4 + 1);
  LODWORD(v27) = vector1_4;
  v24 = vector1a;
  if (!sBtlCheckCrossCircle(v69, r1, v61, v31))
  {
LABEL_36:
    v71.z = v16;
    v71.x = vector1_12;
    v71.w = v15;
    *(u64 *)&v63.z = __PAIR64__(LODWORD(v26), LODWORD(v27));
    *(u64 *)&v63.x = __PAIR64__(LODWORD(v25), LODWORD(v24));
    v71.y = v68;
    if (!sBtlCheckCrossCircle(v71, r1, v63, v31) || v68 != v25)
      return 3;
    goto LABEL_40;
  }
  if ((f32)(v39 - v31) > v68)
  {
    v70.x = vector1_12;
    v70.y = v68;
    v70.z = v16;
    v70.w = v15;
    *(u64 *)&v62.z = vector1_4;
    *(u64 *)&v62.x = __PAIR64__(LODWORD(v25), LODWORD(vector1a));
    if (!sBtlCheckCrossCircle(v70, r1, v62, v31))
      return 3;
LABEL_40:
    v43 = &vf00.x;
    v43[5] = 0.0;
    v43[6] = v16;
    v43[7] = v15;
    v43[4] = vector1_12;
    v44 = &vf00.x;
    v44[8] = LODWORD(v24);
    v44[9] = 0;
    v44[10] = LODWORD(v27);
    v44[11] = LODWORD(v26);
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v45 = &vf00.x;
    v46 = v45[6];
    v47 = v45[4];
    v48 = v45[5];
    if ((f32)(r1 + v31) > sqrtf((f32)((f32)(v47 * v47) + (f32)(v48 * v48)) + (f32)(v46 * v46)))
      return 1;
    return 3;
  }
  v53 = &vf00.x;
  v53[5] = 0.0;
  v53[6] = v16;
  v53[7] = v15;
  v53[4] = vector1_12;
  vct_B.x = vector1a;
  vct_B.y = 0.0;
  *(u64 *)&vct_B.z = vector1_4;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v55 = &vf00.x;
  v56 = v55[6];
  v57 = v55[4];
  v58 = v55[5];
  if ((f32)((f32)(r1 * 0.5) + v31) <= sqrtf((f32)((f32)(v57 * v57) + (f32)(v58 * v58)) + (f32)(v56 * v56)))
    return 3;
  return 0;
}

// 0x1fcc1c0
bool sBtlCheckCrossCircle(const sdfVector4_t *vector1, f32 r1, const sdfVector4_t *vector2, f32 r2) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 *v17;
  f32 *v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;

  w = vector1->w;
  z = vector1->z;
  y = vector1->y;
  x = vector1->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v14 = vector2->z;
  v13 = vector2->w;
  v16 = vector2->x;
  v15 = vector2->y;
  v17 = &vf00.x;
  v17[8] = v16;
  v17[9] = v15;
  v17[10] = v14;
  v17[11] = v13;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v18 = &vf00.x;
  v19 = v18[6];
  v20 = v18[4];
  v21 = v18[5];
  v22 = r2;
  return sqrtf((f32)((f32)(v20 * v20) + (f32)(v21 * v21)) + (f32)(v19 * v19)) <= (f32)(r1 + v22);
}

// 0x1fcc450
bool sBtlCheckCrossCircle_Rot(const sdfVector4_t *vector1, const sdfVector4_t *rot1, f32 r1, const sdfVector4_t *vector2, f32 r2, f32 area) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  f32 *v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 *v23;
  f32 *v26;
  f32 *v27;
  f32 *v29;
  f32 *v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v35;
  f32 v36;
  f32 v47;
  u64 v49;
  struct sdfVector4_t v50;
  sdfMatrix4_t v52;
  sdfMatrix4_t v53;
  f32 v54;
  f32 v55;
  sdfVector4_t v57;

  w = vector1->w;
  z = vector1->z;
  y = vector1->y;
  x = vector1->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v14 = &vf00.x;
  v15 = v14[4];
  v16 = v14[5];
  v17 = v14[6];
  v18 = v14[7];
  v20 = area;
  v19 = *(&area + 1);
  v22 = r2;
  v21 = *(&r2 + 1);
  v23 = &vf00.x;
  v23[4] = v22;
  v23[5] = v21;
  v23[6] = v20;
  v23[7] = v19;
  vct_B = (struct sdfVector4_t)xmmword_3CFBEC0;
  vct_A = rot1;
  ToMatrix();
  get_transpose(&v53, &mtx_A, 0);
  *(_OWORD *)&v52.m00 = *(_OWORD *)&v53.m00;
  *(_OWORD *)&v52.m01 = *(_OWORD *)&v53.m01;
  *(_OWORD *)&v52.m02 = *(_OWORD *)&v53.m02;
  *(_OWORD *)&v52.m03 = *(_OWORD *)&v53.m03;
  v57 = op_Multiply_60923920(&v52, vct_B, 0);
  vct_B = v57;
  v26 = &vf00.x;
  v26[4] = v15;
  v26[5] = v16;
  v26[6] = v17;
  v26[7] = v18;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v27 = &vf00.x;
  v27[8] = v15;
  v27[9] = v16;
  v27[10] = v17;
  v27[11] = v18;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v50 = vct_A;
  v29 = &vf00.x;
  v29[8] = v15;
  v29[9] = v16;
  v29[10] = v17;
  v29[11] = v18;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v30 = &vf00.x;
  v31 = v30[6];
  v32 = v30[4];
  v33 = v30[5];
  v35 = (f32)((f32)(v32 * v32) + (f32)(v33 * v33)) + (f32)(v31 * v31);
  sub_1949110(0);
  v36 = sqrtf(v35);
  if (v36 == 0.0)
    return 1;
  vct_B = v50;
  v47 = v55;
  v49 = vmul_f32(*(float32x2_t *)&vct_A.y, *(float32x2_t *)&vct_B.y).n64_u64[0];
  return (f32)(*((f32 *)&v49 + 1) + (f32)((f32)(vct_A.x * vct_B.x) + *(f32 *)&v49)) >= v47
      && v36 <= (f32)(r1 + v54);
}

// 0x1fccca0
bool sBtlCheckCrossCylinder_Circle(const sdfVector4_t *pos1, const sdfVector4_t *rot1, SBTLDMG_CYLINDERWORK *wk, const sdfVector4_t *pos2, f32 area) {
  f32 y;
  f32 x;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 *p_x;
  f32 *v16;
  f32 v17;
  f32 v18;
  s64 v19;
  f32 v20;
  f32 v21;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 *v27;
  f32 xrad;
  f32 v31;
  _OWORD *v34;
  __int128 v35;
  __int128 v36;
  __int128 v37;
  s32 v39;
  f32 height;
  f32 *v42;
  f32 v43;
  f32 *v44;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 area_r;
  f32 v54;
  f32 v57;
  sdfVector4_t rad;
  sdfVector4_t rada;
  f32 z;
  f32 w;
  f32 v66;
  f32 v67;
  f32 v68;
  f32 v69;
  f32 v70;
  f32 vector2;
  f32 vector2_4;
  sdfMatrix4_t vector2_8;
  sdfMatrix4_t v74;
  sdfMatrix4_t v75;
  sdfMatrix4_t v76;
  s64 v77;
  f32 v78;
  sdfVector4_t v79;
  sdfVector4_t v80;
  sdfVector4_t v81;
  sdfVector4_t v82;
  sdfVector4_t v84;
  sdfVector4_t v85;
  sdfVector4_t v86;
  sdfVector4_t v87;
  sdfVector4_t v88;
  sdfVector4_t v89;
  sdfVector4_t v90;
  sdfVector4_t v91;

  z = rot1->z;
  w = rot1->w;
  y = rot1->y;
  x = rot1->x;
  v8 = pos1->w;
  v9 = pos1->z;
  v10 = pos1->y;
  v11 = pos1->x;
  p_x = &vf00.x;
  p_x[4] = v11;
  p_x[5] = v10;
  p_x[6] = v9;
  p_x[7] = v8;
  v16 = &vf00.x;
  v67 = v16[6];
  v17 = v16[4];
  v18 = v16[5];
  vector2_4 = v16[7];
  v19 = v77;
  v21 = area;
  v20 = *(&area + 1);
  vct_A.x = v21;
  vct_A.y = v20;
  *(u64 *)&vct_A.z = v19;
  v23 = v67;
  v24 = v17;
  v25 = v18;
  v70 = vct_A.z;
  vector2 = vct_A.x;
  v68 = vct_A.y;
  v69 = vct_A.w;
  v27 = &vf00.x;
  v27[4] = x;
  v27[5] = y;
  v27[6] = z;
  v27[7] = w;
  vct_B = vct_A;
  xrad = wk->xrad;
  v31 = xrad * 0.017453292;
  sub_1949540(0, xrad * 0.017453292);
  v34 = &vf00.x;
  v35 = v34[5];
  v36 = v34[6];
  v37 = v34[7];
  *(_OWORD *)&v74.m00 = v34[4];
  *(_OWORD *)&v74.m01 = v35;
  *(_OWORD *)&v74.m02 = v36;
  *(_OWORD *)&v74.m03 = v37;
  if (!(u32)v34)
  vector2_8 = v74;
  sBtlGetQuatFromMatrix(&vector2_8);
  Mult();
  ToMatrix();
  v39 = (u8)byte_5756085;
  vct_A = (struct sdfVector4_t)xmmword_3CFEDD0;
  if (v39)
  {
    goto LABEL_24;
  }
  else
  {
    goto LABEL_24;
  }
LABEL_24:
  get_transpose(&v76, &mtx_A, 0);
  v75 = v76;
  v82 = op_Multiply_60923920(&v75, vct_A, 0);
  vct_A = v82;
  height = wk->height;
  if (!*(u32 *)(*(u64 *)&v79.x + 224))
  {
    v66 = height;
    height = v66;
  }
  *(float32x4_t *)(*(u64 *)(*(u64 *)&v79.x + 184) + 16) = vmulq_n_f32(*(float32x4_t *)(*(u64 *)(*(u64 *)&v79.x + 184) + 16), height);
  if (*(u32 *)(*(u64 *)&v79.x + 224))
  v42 = *(f32 **)(*(u64 *)&v79.x + 184);
  v42[8] = v24;
  v42[9] = v25;
  v42[10] = v23;
  v42[11] = vector2_4;
  if (!*(u32 *)(*(u64 *)&v79.x + 224))
    goto LABEL_9002;
  *(float32x4_t *)(*(u64 *)(*(u64 *)&v79.x + 184) + 16) = vaddq_f32(*(float32x4_t *)(*(u64 *)(*(u64 *)&v79.x + 184) + 16), *(float32x4_t *)(*(u64 *)(*(u64 *)&v79.x + 184) + 32));
  goto LABEL_31;
LABEL_75:
  goto LABEL_32;
LABEL_9002:
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
LABEL_31:
  v43 = v78;
  if (!*(u32 *)(*(u64 *)&v79.x + 224))
    goto LABEL_75;
LABEL_32:
  v84.z = v23;
  v44 = *(f32 **)(*(u64 *)&v79.x + 184);
  v45 = v44[4];
  v46 = v44[5];
  v47 = v44[6];
  v48 = v44[7];
  v89.y = v46;
  v89.w = v48;
  v84.w = vector2_4;
  v89.x = v45;
  v89.z = v47;
  v84.x = v24;
  v84.y = v25;
  if (sBtlGetVerticalLength(v84, v89, v79) > v43)
    return 0;
  v85.z = v23;
  v90.x = v45;
  v85.w = vector2_4;
  v90.y = v46;
  v90.z = v47;
  v90.w = v48;
  v85.x = v24;
  v85.y = v25;
  if (!sBtlCheckInner(v85, v90, v80, vector2))
  {
    area_r = wk->area_r;
    v86.w = vector2_4;
    v54 = v43 - area_r;
    v23 = v67;
    *(u64 *)&rad.x = __PAIR64__(LODWORD(v68), LODWORD(vector2));
    v86.z = v67;
    *(u64 *)&rad.z = __PAIR64__(LODWORD(v69), LODWORD(v70));
    v86.x = v24;
    v86.y = v25;
    if (!sBtlCheckCrossCircle(v86, v54, rad, 1.0))
      return 0;
  }
  v87.z = v47;
  v87.w = v48;
  v91.w = vector2_4;
  v91.x = v24;
  v91.y = v25;
  v91.z = v23;
  v87.x = v45;
  v87.y = v46;
  if (sBtlCheckInner(v87, v91, v81, vector2))
    return 1;
  v57 = wk->area_r;
  v88.z = v47;
  v88.w = v48;
  *(u64 *)&rada.x = __PAIR64__(LODWORD(v68), LODWORD(vector2));
  *(u64 *)&rada.z = __PAIR64__(LODWORD(v69), LODWORD(v70));
  v88.x = v45;
  v88.y = v46;
  return sBtlCheckCrossCircle(v88, v43 - v57, rada, 1.0);
}

// 0x1fcdc80
f32 sBtlGetRadian(const sdfVector4_t *t1, const sdfVector4_t *rot, const sdfVector4_t *t2, f32 per) {
  f32 x;
  f32 v6;
  f32 v7;
  f32 y;
  f32 v9;
  f32 *p_x;
  f32 *v13;
  f32 v14;
  f32 v15;
  f32 v16;
  s64 v17;
  f32 v18;
  f32 v19;
  f32 v22;
  s64 v23;
  f32 *v24;
  f32 v25;
  f32 *v28;
  f32 *v29;
  f32 *v31;
  f32 *v34;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 *v39;
  u64 v41;
  f32 v42;
  f32 v44;
  f32 *v45;
  f32 v46;
  f32 *v52;
  f32 v53;
  f32 *v60;
  f32 v61;
  f32 *v65;
  f32 *v66;
  f32 *v68;
  f32 v69;
  u64 v71;
  f32 v72;
  f32 v79;
  f32 rota;
  sdfMatrix4_t v81;
  sdfMatrix4_t v82;
  f32 z;
  f32 w;
  s64 v85;
  f32 v86;
  sdfVector4_t v87;
  sdfVector4_t v88;
  sdfVector4_t v90;
  sdfVector4_t v91;

  z = rot->z;
  w = rot->w;
  rota = rot->y;
  x = rot->x;
  v6 = t1->w;
  v7 = t1->z;
  y = t1->y;
  v9 = t1->x;
  p_x = &vf00.x;
  p_x[4] = v9;
  p_x[5] = y;
  p_x[6] = v7;
  p_x[7] = v6;
  v13 = &vf00.x;
  v14 = v13[4];
  v15 = v13[6];
  v16 = v13[7];
  v17 = v85;
  v19 = per;
  v18 = *(&per + 1);
  vct_A.x = v19;
  vct_A.y = v18;
  *(u64 *)&vct_A.z = v17;
  v22 = vct_A.x;
  v23 = *(u64 *)&vct_A.z;
  vct_B = (struct sdfVector4_t)xmmword_3CFDEB0;
  v24 = &vf00.x;
  v24[4] = x;
  v24[5] = rota;
  v25 = w;
  v24[6] = z;
  v24[7] = v25;
  ToMatrix();
  get_transpose(&v82, &mtx_A, 0);
  *(_OWORD *)&v81.m00 = *(_OWORD *)&v82.m00;
  *(_OWORD *)&v81.m01 = *(_OWORD *)&v82.m01;
  *(_OWORD *)&v81.m02 = *(_OWORD *)&v82.m02;
  *(_OWORD *)&v81.m03 = *(_OWORD *)&v82.m03;
  v87 = op_Multiply_60923920(&v81, vct_B, 0);
  vct_B = v87;
  v28 = &vf00.x;
  v28[4] = v14;
  v28[5] = 0.0;
  v28[6] = v15;
  v28[7] = v16;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v29 = &vf00.x;
  v29[8] = v14;
  v29[9] = 0.0;
  v29[10] = v15;
  v29[11] = v16;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v31 = &vf00.x;
  v31[8] = v14;
  v31[9] = 0.0;
  v31[10] = v15;
  v31[11] = v16;
  vct_A.x = v22;
  vct_A.y = 0.0;
  *(u64 *)&vct_A.z = v23;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v34 = &vf00.x;
  v36 = v34[4];
  v35 = v34[5];
  v37 = v34[6];
  v38 = v34[7];
  v39 = &vf00.x;
  v39[8] = v36;
  v39[9] = v35;
  v39[10] = v37;
  v39[11] = v38;
  v41 = vmul_f32(*(float32x2_t *)&vct_A.y, *(float32x2_t *)&vct_B.y).n64_u64[0];
  v42 = *((f32 *)&v41 + 1) + (f32)((f32)(vct_A.x * vct_B.x) + *(f32 *)&v41);
  if (v42 > 1.0)
  {
    v44 = 0.0;
    v45 = &vf00.x;
    v45[4] = x;
    v45[5] = rota;
    v46 = w;
    v45[6] = z;
    v45[7] = v46;
    return v44;
  }
  if (v42 < -1.0)
  {
    v52 = &vf00.x;
    v52[4] = x;
    v52[5] = rota;
    v53 = w;
    v52[6] = z;
    v52[7] = v53;
    return 180.0;
  }
  v79 = sub_188E3F0(v42);
  vct_A = (struct sdfVector4_t)xmmword_3D015F0;
  FromRotation(-1.570796);
  vct_B = vct_A;
  v60 = &vf00.x;
  v60[4] = x;
  v60[5] = rota;
  v61 = w;
  v60[6] = z;
  v60[7] = v61;
  Mult();
  vct_B = (struct sdfVector4_t)xmmword_3CFDEB0;
  ToMatrix();
  get_transpose(&v82, &mtx_A, 0);
  *(_OWORD *)&v81.m00 = *(_OWORD *)&v82.m00;
  *(_OWORD *)&v81.m01 = *(_OWORD *)&v82.m01;
  v90 = vct_B;
  *(_OWORD *)&v81.m02 = *(_OWORD *)&v82.m02;
  *(_OWORD *)&v81.m03 = *(_OWORD *)&v82.m03;
  v88 = op_Multiply_60923920(&v81, v90, 0);
  vct_B = v88;
  v65 = &vf00.x;
  v65[4] = v14;
  v65[5] = 0.0;
  v65[6] = v15;
  v65[7] = v16;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v66 = &vf00.x;
  v66[8] = v14;
  v66[9] = 0.0;
  v66[10] = v15;
  v66[11] = v16;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v68 = &vf00.x;
  v68[8] = v36;
  v68[9] = v35;
  v68[10] = v37;
  v68[11] = v38;
  v69 = v86;
  v71 = vmul_f32(*(float32x2_t *)&vct_A.y, *(float32x2_t *)&vct_B.y).n64_u64[0];
  if ((f32)(*((f32 *)&v71 + 1) + (f32)((f32)(vct_A.x * vct_B.x) + *(f32 *)&v71)) >= 0.0)
    v72 = v79;
  else
    v72 = -v79;
  v44 = (f32)(v72 * 57.29578) * v69;
  v91.y = rota;
  v91.x = x;
  v91.z = z;
  v91.w = w;
  sBtlGetRotateDeg(v91, v44);
  return v44;
}

// 0x1fce9b0
f32 sBtlGetRadian_AndSet_New(SBTLUNIT_WORK *wk, const sdfVector4_t *t1, const sdfVector4_t *rot, const sdfVector4_t *t2, f32 per, f32 _Limit) {
  f32 z;
  f32 y;
  f32 x;
  f32 v10;
  f32 v13;
  f32 v14;
  f32 RotToDir;
  f32 v16;
  f32 v17;
  _BOOL4 v18;
  f32 v19;
  f32 v20;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  sdfVector4_t *p_rot;
  f32 rota;
  f32 v33;
  f32 v34;
  sdfVector4_t v35;

  rota = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  v10 = t1->x;
  t1->x = per - v10;
  v13 = sub_188E410(*(long f64 *)&t1) * 57.29578;
  if (v13 >= 0.0)
    v14 = v13;
  else
    v14 = v13 + 360.0;
  v35.x = x;
  v35.y = y;
  v35.z = z;
  v35.w = rota;
  RotToDir = sBtlGetRotToDir(v35);
  v16 = RotToDir + 360.0;
  v17 = v14 + 360.0;
  v18 = RotToDir < 0.0;
  if (v14 < 0.0)
    v18 = 1;
  if (!v18)
  {
    v16 = RotToDir;
    v17 = v14;
  }
  if (v16 == INFINITY)
    v19 = -128.0;
  else
    v19 = ((s32)v16 % 360);
  if (v17 == INFINITY)
    v20 = -128.0;
  else
    v20 = ((s32)v17 % 360);
  if ((f32)(v19 - v20) > 180.0 || (f32)(v19 - v20) < -180.0)
  {
    if (v19 >= v20)
      v20 = v20 + 360.0;
    else
      v19 = v19 + 360.0;
  }
  v22 = v20 - v19;
  if (v22 < (f32)-v34)
    v22 = -v34;
  if (v22 > v34)
    v22 = v34;
  v23 = RotToDir + (f32)(v22 * v33);
  v24 = v23 + -360.0;
  if (v23 <= 360.0)
    v24 = v23;
  if (v24 < 0.0)
    v24 = v24 + 360.0;
  v25 = v24 + 180.0;
  v26 = v25 + -360.0;
  if (v25 < 360.0)
    v26 = v25;
  if (v26 >= 0.0)
    v27 = v26;
  else
    v27 = v26 + 360.0;
  FromEuler(0.0, v27 * 0.017453292, 0.0);
  p_rot = &wk->rot;
  *p_rot = vct_A;
  wk->rotbk = vct_A;
  return v27;
}

// 0x1fcefc0
f32 sBtlGetChorikiDeg(const sdfVector4_t *t1, const sdfVector4_t *rot, const sdfVector4_t *tVec2, f32 per) {
  f32 v5;
  f32 v6;
  f32 v7;
  f32 v8;
  f32 *p_x;
  f32 *v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 *v17;
  f32 v18;
  f32 *v21;
  f32 *v22;
  s64 v24;
  f32 v25;
  f32 v26;
  f32 *v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 *v34;
  f32 *v35;
  f32 v36;
  f32 *v39;
  f32 v40;
  f32 *v44;
  f32 *v45;
  f32 *v47;
  f32 v50;
  f32 v51;
  float32x2_t v52;
  float32x2_t v53;
  f32 v54;
  f32 v56;
  f32 v57;
  f32 v69;
  f32 x;
  f32 y;
  sdfMatrix4_t v72;
  sdfMatrix4_t v73;
  f32 z;
  f32 w;
  s64 v76;
  f32 v77;
  sdfVector4_t v78;
  sdfVector4_t v79;
  sdfVector4_t v81;
  sdfVector4_t v82;

  z = rot->z;
  w = rot->w;
  x = rot->x;
  y = rot->y;
  v5 = t1->w;
  v6 = t1->z;
  v7 = t1->y;
  v8 = t1->x;
  p_x = &vf00.x;
  p_x[4] = v8;
  p_x[5] = v7;
  p_x[6] = v6;
  p_x[7] = v5;
  v12 = &vf00.x;
  v13 = v12[4];
  v14 = v12[5];
  v16 = v12[6];
  v15 = v12[7];
  vct_B = (struct sdfVector4_t)xmmword_3CFDEB0;
  v17 = &vf00.x;
  v17[4] = x;
  v17[5] = y;
  v18 = w;
  v17[6] = z;
  v17[7] = v18;
  ToMatrix();
  get_transpose(&v73, &mtx_A, 0);
  *(_OWORD *)&v72.m00 = *(_OWORD *)&v73.m00;
  *(_OWORD *)&v72.m01 = *(_OWORD *)&v73.m01;
  *(_OWORD *)&v72.m02 = *(_OWORD *)&v73.m02;
  *(_OWORD *)&v72.m03 = *(_OWORD *)&v73.m03;
  v78 = op_Multiply_60923920(&v72, vct_B, 0);
  vct_B = v78;
  v21 = &vf00.x;
  v21[4] = v13;
  v21[5] = v14;
  v21[6] = v16;
  v21[7] = v15;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v22 = &vf00.x;
  v22[8] = v13;
  v22[9] = v14;
  v22[10] = v16;
  v22[11] = v15;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v24 = v76;
  v26 = per;
  v25 = *(&per + 1);
  vct_A.x = v26;
  vct_A.y = v25;
  *(u64 *)&vct_A.z = v24;
  sub_1949110(0);
  v29 = &vf00.x;
  v30 = v29[4];
  v31 = v29[5];
  v32 = v29[6];
  v33 = v29[7];
  v34 = &vf00.x;
  v34[8] = v30;
  v34[9] = v31;
  v34[10] = v32;
  v34[11] = v33;
  v69 = v33;
  v35 = &vf00.x;
  v36 = sub_188E3F0((f32)(v35[6] * v35[10]) + (f32)((f32)(v35[4] * v35[8]) + (f32)(v35[5] * v35[9])));
  vct_A = (struct sdfVector4_t)xmmword_3D015F0;
  FromRotation(-1.570796);
  vct_B = vct_A;
  v39 = &vf00.x;
  v39[4] = x;
  v39[5] = y;
  v40 = w;
  v39[6] = z;
  v39[7] = v40;
  Mult();
  vct_B = (struct sdfVector4_t)xmmword_3CFDEB0;
  ToMatrix();
  get_transpose(&v73, &mtx_A, 0);
  *(_OWORD *)&v72.m00 = *(_OWORD *)&v73.m00;
  *(_OWORD *)&v72.m01 = *(_OWORD *)&v73.m01;
  v81 = vct_B;
  *(_OWORD *)&v72.m02 = *(_OWORD *)&v73.m02;
  *(_OWORD *)&v72.m03 = *(_OWORD *)&v73.m03;
  v79 = op_Multiply_60923920(&v72, v81, 0);
  vct_B = v79;
  v44 = &vf00.x;
  v44[4] = v13;
  v44[5] = v14;
  v44[6] = v16;
  v44[7] = v15;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v45 = &vf00.x;
  v45[8] = v13;
  v45[9] = v14;
  v45[10] = v16;
  v45[11] = v15;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v47 = &vf00.x;
  v47[8] = v30;
  v47[9] = v31;
  v47[10] = v32;
  v47[11] = v69;
  v50 = vct_A.x;
  v51 = vct_B.x;
  v52.n64_u64[0] = *(u64 *)&vct_A.y;
  v53.n64_u64[0] = *(u64 *)&vct_B.y;
  *(float32x2_t *)&v82.x = vmul_f32(v52, v53);
  v82.z = z;
  v82.w = w;
  if ((f32)(v54 + (f32)((f32)(v50 * v51) + v82.x)) >= 0.0)
    v56 = v36;
  else
    v56 = -v36;
  v57 = (f32)(v56 * 57.29578) * v77;
  v82.x = x;
  v82.y = y;
  sBtlGetRotateDeg(v82, v57);
  return v57;
}

// 0x1fcfa90
sdfVector4_t sBtlGetTargrtVec(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *tgt) {
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  f32 *p_x;
  f32 v11;
  f32 v12;
  f32 v14;
  s64 v15;
  f32 *v16;
  f32 *v19;
  f32 *v20;
  f32 *v22;
  f32 *v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 *v30;
  f32 *v31;
  f32 v32;
  f32 *v35;
  f32 *v39;
  f32 v40;
  f32 *v41;
  f32 v42;
  f32 *v45;
  u64 v47;
  f32 v48;
  f32 v49;
  bool v52;
  f32 v56;
  sdfVector4_t dir;
  struct sdfVector4_t v64;
  f32 rot;
  struct sdfVector4_t pos;
  f32 v68;
  sdfMatrix4_t v69;
  sdfMatrix4_t v70;
  f32 v71;
  f32 v72;
  sdfVector4_t v73;
  sdfVector4_t v74;
  sdfVector4_t v75;
  sdfVector4_t TgtVec;
  sdfVector4_t v78;
  sdfVector4_t result;
  sdfVector4_t v80;

  x = wk->rot.x;
  y = wk->rot.y;
  z = wk->rot.z;
  w = wk->rot.w;
  pos = wk->pos;
  v64 = tgt->pos;
  vct_A = pos;
  p_x = &vf00.x;
  v68 = p_x[4];
  v11 = p_x[6];
  v12 = p_x[7];
  vct_A = v64;
  v14 = vct_A.x;
  v15 = *(u64 *)&vct_A.z;
  vct_B = (struct sdfVector4_t)xmmword_3CFDEB0;
  v16 = &vf00.x;
  v16[4] = x;
  v16[5] = y;
  v16[6] = z;
  v16[7] = w;
  ToMatrix();
  get_transpose(&v70, &mtx_A, 0);
  *(_OWORD *)&v69.m00 = *(_OWORD *)&v70.m00;
  *(_OWORD *)&v69.m01 = *(_OWORD *)&v70.m01;
  *(_OWORD *)&v69.m02 = *(_OWORD *)&v70.m02;
  *(_OWORD *)&v69.m03 = *(_OWORD *)&v70.m03;
  v74 = op_Multiply_60923920(&v69, vct_B, 0);
  vct_B = v74;
  v19 = &vf00.x;
  v19[5] = 0.0;
  v19[6] = v11;
  v19[7] = v12;
  v19[4] = v68;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v20 = &vf00.x;
  v20[9] = 0.0;
  v20[10] = v11;
  v20[11] = v12;
  v20[8] = v68;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v22 = &vf00.x;
  v22[9] = 0.0;
  v22[10] = v11;
  v22[11] = v12;
  v22[8] = v68;
  vct_A.x = v14;
  vct_A.y = 0.0;
  *(u64 *)&vct_A.z = v15;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  rot = y;
  v71 = v12;
  v72 = v11;
  v25 = &vf00.x;
  v26 = v25[4];
  v27 = v25[5];
  v28 = v25[6];
  v29 = v25[7];
  v30 = &vf00.x;
  v30[8] = v26;
  v30[9] = v27;
  v30[10] = v28;
  v30[11] = v29;
  v31 = &vf00.x;
  v32 = sub_188E3F0((f32)(v31[6] * v31[10]) + (f32)((f32)(v31[4] * v31[8]) + (f32)(v31[5] * v31[9])));
  vct_A = (struct sdfVector4_t)xmmword_3D015F0;
  FromRotation(-1.570796);
  vct_B = vct_A;
  v35 = &vf00.x;
  v35[6] = z;
  v35[7] = w;
  v35[4] = x;
  v35[5] = rot;
  Mult();
  vct_B = (struct sdfVector4_t)xmmword_3CFDEB0;
  ToMatrix();
  get_transpose(&v70, &mtx_A, 0);
  *(_OWORD *)&v69.m00 = *(_OWORD *)&v70.m00;
  *(_OWORD *)&v69.m01 = *(_OWORD *)&v70.m01;
  v78 = vct_B;
  *(_OWORD *)&v69.m02 = *(_OWORD *)&v70.m02;
  *(_OWORD *)&v69.m03 = *(_OWORD *)&v70.m03;
  v75 = op_Multiply_60923920(&v69, v78, 0);
  vct_B = v75;
  v39 = &vf00.x;
  v39[5] = 0.0;
  v39[4] = v68;
  v40 = v71;
  v39[6] = v72;
  v39[7] = v40;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v41 = &vf00.x;
  v41[9] = 0.0;
  v41[8] = v68;
  v42 = v71;
  v41[10] = v72;
  v41[11] = v42;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v45 = &vf00.x;
  v45[8] = v26;
  v45[9] = v27;
  v45[10] = v28;
  v45[11] = v29;
  v47 = vmul_f32(*(float32x2_t *)&vct_A.y, *(float32x2_t *)&vct_B.y).n64_u64[0];
  if ((f32)(*((f32 *)&v47 + 1) + (f32)((f32)(vct_A.x * vct_B.x) + *(f32 *)&v47)) >= 0.0)
    v48 = v32;
  else
    v48 = -v32;
  v49 = v48 * 57.29578;
  if (v49 >= 45.0)
  {
    v56 = 45.0;
  }
  else
  {
    result.z = v28;
    result.w = v29;
    v52 = v49 > -45.0;
    result.x = v26;
    result.y = v27;
    if (v52)
      return result;
    v56 = -45.0;
  }
  *(u64 *)&dir.x = 0;
  *(u64 *)&dir.z = 0x3F800000BF800000LL;
  v80.y = rot;
  v80.z = z;
  v80.w = w;
  v80.x = x;
  TgtVec = GetTgtVec(v56, v80, dir, v73);
  result.x = TgtVec.x;
  result.y = TgtVec.y;
  result.z = TgtVec.z;
  result.w = TgtVec.w;
  return result;
}

// 0x1fd0700
static sdfVector4_t GetTgtVec(f32 deg, const sdfVector4_t *rot, const sdfVector4_t *dir, const sdfVector4_t *pos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 *v21;
  s64 v24;
  s64 v25;
  f32 *v29;
  struct sdfVector4_t yv;
  sdfMatrix4_t v37;
  sdfMatrix4_t v38;
  s64 v39;
  s64 v40;
  sdfVector4_t v41;
  sdfVector4_t result;

  w = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  yv = _yv;
  vct_A = yv;
  FromRotation(deg * -0.017453292);
  vct_B = vct_A;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  Mult();
  v18 = dir->z;
  v17 = dir->w;
  v20 = dir->x;
  v19 = dir->y;
  v21 = &vf00.x;
  v21[8] = v20;
  v21[9] = v19;
  v21[10] = v18;
  v21[11] = v17;
  ToMatrix();
  get_transpose(&v38, &mtx_A, 0);
  *(_OWORD *)&v37.m00 = *(_OWORD *)&v38.m00;
  *(_OWORD *)&v37.m01 = *(_OWORD *)&v38.m01;
  *(_OWORD *)&v37.m02 = *(_OWORD *)&v38.m02;
  *(_OWORD *)&v37.m03 = *(_OWORD *)&v38.m03;
  v41 = op_Multiply_60923920(&v37, vct_B, 0);
  vct_B = v41;
  v24 = v40;
  v25 = v39;
  *(u64 *)&vct_A.x = v25;
  *(u64 *)&vct_A.z = v24;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  *(u64 *)&vct_B.x = v25;
  *(u64 *)&vct_B.z = v24;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v29 = &vf00.x;
  result.x = v29[4];
  result.y = v29[5];
  result.z = v29[6];
  result.w = v29[7];
  return result;
}

// 0x1fd0bd0
bool sBtlGetRadian_X(const sdfVector4_t *t1, const sdfVector4_t *rot, const sdfVector4_t *rot2, const sdfVector4_t *t2, f32 per) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  f32 *v13;
  f32 v14;
  f32 v15;
  f32 v16;
  s64 v17;
  s64 v18;
  s64 v21;
  f32 v22;
  s64 v23;
  f32 v24;
  f32 v25;
  f32 *v31;
  f32 *v32;
  f32 *v34;
  f32 *v37;
  f32 v38;
  f32 v39;
  f32 *v40;
  u64 v42;
  f32 v43;
  bool v44;
  f32 *v53;
  f32 *v54;
  f32 *v56;
  f32 v59;
  float32x2_t v60;
  f32 v61;
  f32 v62;
  f32 v64;
  f32 v65;
  f32 v66;
  f32 v86;
  f32 v88;
  f32 v89;
  f32 v90;
  sdfMatrix4_t v92;
  sdfMatrix4_t v93;
  s64 v94;
  s64 v95;
  s64 v96;
  f32 v97;
  sdfVector4_t v99;
  sdfVector4_t v100;
  sdfVector4_t v101;
  sdfVector4_t v102;
  sdfVector4_t v104;
  sdfVector4_t v105;
  sdfVector4_t v106;

  w = t1->w;
  z = t1->z;
  y = t1->y;
  x = t1->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v13 = &vf00.x;
  v14 = v13[5];
  v15 = v13[6];
  v16 = v13[7];
  v17 = v96;
  v18 = v95;
  *(u64 *)&vct_A.x = v18;
  *(u64 *)&vct_A.z = v17;
  v21 = *(u64 *)&vct_A.y;
  v22 = vct_A.w;
  vct_B = (struct sdfVector4_t)xmmword_3CFBEC0;
  v23 = v94;
  v24 = per;
  v25 = *(&per + 1);
  v86 = v24;
  vct_A.x = v24;
  vct_A.y = v25;
  *(u64 *)&vct_A.z = v23;
  ToMatrix();
  get_transpose(&v93, &mtx_A, 0);
  *(_OWORD *)&v92.m00 = *(_OWORD *)&v93.m00;
  *(_OWORD *)&v92.m01 = *(_OWORD *)&v93.m01;
  *(_OWORD *)&v92.m02 = *(_OWORD *)&v93.m02;
  *(_OWORD *)&v92.m03 = *(_OWORD *)&v93.m03;
  v99 = op_Multiply_60923920(&v92, vct_B, 0);
  vct_B = v99;
  vct_A = rot;
  ToMatrix();
  get_transpose(&v93, &mtx_A, 0);
  *(_OWORD *)&v92.m00 = *(_OWORD *)&v93.m00;
  *(_OWORD *)&v92.m01 = *(_OWORD *)&v93.m01;
  v104 = vct_B;
  *(_OWORD *)&v92.m02 = *(_OWORD *)&v93.m02;
  *(_OWORD *)&v92.m03 = *(_OWORD *)&v93.m03;
  v100 = op_Multiply_60923920(&v92, v104, 0);
  vct_B = v100;
  v31 = &vf00.x;
  v31[4] = 0.0;
  v31[5] = v14;
  v31[6] = v15;
  v31[7] = v16;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v32 = &vf00.x;
  v32[8] = 0.0;
  v32[9] = v14;
  v32[10] = v15;
  v32[11] = v16;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v34 = &vf00.x;
  v34[8] = 0.0;
  v34[9] = v14;
  v34[10] = v15;
  v34[11] = v16;
  vct_A.x = 0.0;
  *(u64 *)&vct_A.y = v21;
  vct_A.w = v22;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v37 = &vf00.x;
  v38 = v37[5];
  v39 = v37[6];
  v89 = v37[7];
  v90 = v37[4];
  v40 = &vf00.x;
  v40[8] = v90;
  v40[9] = v38;
  v40[10] = v39;
  v40[11] = v89;
  v42 = vmul_f32(*(float32x2_t *)&vct_A.y, *(float32x2_t *)&vct_B.y).n64_u64[0];
  v43 = *((f32 *)&v42 + 1) + (f32)((f32)(vct_A.x * vct_B.x) + *(f32 *)&v42);
  v44 = v43 >= -1.0 && v43 <= 1.0;
  if (!v44)
  {
    vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
    return v44;
  }
  v88 = sub_188E3F0(v43);
  vct_A = (struct sdfVector4_t)xmmword_3D079D0;
  FromRotation(-1.570796);
  vct_B = vct_A;
  *(u64 *)&vct_A.z = v23;
  vct_A.x = v86;
  vct_A.y = v25;
  Mult();
  vct_B = (struct sdfVector4_t)xmmword_3CFBEC0;
  ToMatrix();
  get_transpose(&v93, &mtx_A, 0);
  *(_OWORD *)&v92.m00 = *(_OWORD *)&v93.m00;
  *(_OWORD *)&v92.m01 = *(_OWORD *)&v93.m01;
  v105 = vct_B;
  *(_OWORD *)&v92.m02 = *(_OWORD *)&v93.m02;
  *(_OWORD *)&v92.m03 = *(_OWORD *)&v93.m03;
  v101 = op_Multiply_60923920(&v92, v105, 0);
  vct_B = v101;
  vct_A = rot;
  ToMatrix();
  get_transpose(&v93, &mtx_A, 0);
  *(_OWORD *)&v92.m00 = *(_OWORD *)&v93.m00;
  *(_OWORD *)&v92.m01 = *(_OWORD *)&v93.m01;
  v106 = vct_B;
  *(_OWORD *)&v92.m02 = *(_OWORD *)&v93.m02;
  *(_OWORD *)&v92.m03 = *(_OWORD *)&v93.m03;
  v102 = op_Multiply_60923920(&v92, v106, 0);
  vct_B = v102;
  v53 = &vf00.x;
  v53[4] = 0.0;
  v53[5] = v14;
  v53[6] = v15;
  v53[7] = v16;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v54 = &vf00.x;
  v54[8] = 0.0;
  v54[9] = v14;
  v54[10] = v15;
  v54[11] = v16;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v56 = &vf00.x;
  v56[8] = v90;
  v56[9] = v38;
  v56[10] = v39;
  v56[11] = v89;
  v59 = vct_A.x * vct_B.x;
  v60.n64_u64[0] = vmul_f32(*(float32x2_t *)&vct_A.y, *(float32x2_t *)&vct_B.y).n64_u64[0];
  v61 = v60.n64_f32[1];
  v62 = v59 + v60.n64_f32[0];
  v64 = v61 + v62;
  v65 = v97;
  vct_A = (struct sdfVector4_t)xmmword_3D079D0;
  v66 = -v88;
  if (v64 < 0.0)
    v66 = v88;
  FromRotation(v66 * v65);
  vct_B = vct_A;
  vct_A = rot;
  Mult();
  return v44;
}

// 0x1fcd7c0
bool sBtlCheckInner(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *pos2, f32 rad) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 *p_x;
  f32 *v16;
  s64 v18;
  f32 v19;
  f32 v20;
  f32 *v22;
  f32 v24;
  u64 v26;
  struct sdfVector4_t v32;
  s64 v34;
  f32 v35;

  w = pos1->w;
  z = pos1->z;
  y = pos1->y;
  x = pos1->x;
  v9 = pos0->w;
  v10 = pos0->z;
  v11 = pos0->y;
  v12 = pos0->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v16 = &vf00.x;
  v16[8] = v12;
  v16[9] = v11;
  v16[10] = v10;
  v16[11] = v9;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v18 = v34;
  v20 = rad;
  v19 = *(&rad + 1);
  vct_A.x = v20;
  vct_A.y = v19;
  *(u64 *)&vct_A.z = v18;
  v22 = &vf00.x;
  v22[8] = v12;
  v22[9] = v11;
  v22[10] = v10;
  v22[11] = v9;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v32 = vct_A;
  vct_B = v32;
  v24 = v35;
  v26 = vmul_f32(*(float32x2_t *)&vct_A.y, *(float32x2_t *)&vct_B.y).n64_u64[0];
  return (f32)(*((f32 *)&v26 + 1) + (f32)((f32)(vct_A.x * vct_B.x) + *(f32 *)&v26)) >= v24;
}

// 0x1fd1be0
bool sBtlCheckPos_Right(const sdfVector4_t *t1, const sdfVector4_t *rot, const sdfVector4_t *t2) {
  f32 w;
  f32 z;
  f32 v6;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 *p_x;
  f32 *v13;
  f32 v14;
  f32 v15;
  f32 v16;
  s64 v17;
  s64 v18;
  f32 v20;
  f32 v21;
  f32 v23;
  s64 v24;
  f32 *v25;
  f32 *v28;
  f32 *v29;
  f32 *v31;
  f32 *v35;
  f32 *v39;
  f32 *v40;
  u64 v43;
  f32 y;
  f32 v53;
  f32 x;
  sdfMatrix4_t v55;
  sdfMatrix4_t v56;
  s64 v57;
  s64 v58;
  sdfVector4_t v59;
  sdfVector4_t v60;
  sdfVector4_t v62;

  y = rot->y;
  x = rot->x;
  w = rot->w;
  z = rot->z;
  v6 = t1->w;
  v7 = t1->z;
  v8 = t1->y;
  v9 = t1->x;
  p_x = &vf00.x;
  p_x[4] = v9;
  p_x[5] = v8;
  p_x[6] = v7;
  p_x[7] = v6;
  v13 = &vf00.x;
  v14 = z;
  v15 = v13[6];
  v16 = v13[7];
  v53 = v13[4];
  v17 = v58;
  v18 = v57;
  *(u64 *)&vct_A.x = v18;
  *(u64 *)&vct_A.z = v17;
  v20 = w;
  v21 = v14;
  v23 = vct_A.x;
  v24 = *(u64 *)&vct_A.z;
  vct_B = (struct sdfVector4_t)xmmword_3CFBEC0;
  v25 = &vf00.x;
  v25[6] = v21;
  v25[7] = v20;
  v25[4] = x;
  v25[5] = y;
  ToMatrix();
  get_transpose(&v56, &mtx_A, 0);
  *(_OWORD *)&v55.m00 = *(_OWORD *)&v56.m00;
  *(_OWORD *)&v55.m01 = *(_OWORD *)&v56.m01;
  *(_OWORD *)&v55.m02 = *(_OWORD *)&v56.m02;
  *(_OWORD *)&v55.m03 = *(_OWORD *)&v56.m03;
  v59 = op_Multiply_60923920(&v55, vct_B, 0);
  vct_B = v59;
  v28 = &vf00.x;
  v28[4] = v53;
  v28[5] = 0.0;
  v28[6] = v15;
  v28[7] = v16;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v29 = &vf00.x;
  v29[8] = v53;
  v29[9] = 0.0;
  v29[10] = v15;
  v29[11] = v16;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v31 = &vf00.x;
  v31[8] = v53;
  v31[9] = 0.0;
  v31[10] = v15;
  v31[11] = v16;
  vct_A.x = v23;
  vct_A.y = 0.0;
  *(u64 *)&vct_A.z = v24;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  vct_A = (struct sdfVector4_t)xmmword_3D015F0;
  FromRotation(-1.570796);
  vct_B = vct_A;
  v35 = &vf00.x;
  v35[6] = v21;
  v35[7] = v20;
  v35[4] = x;
  v35[5] = y;
  Mult();
  vct_B = (struct sdfVector4_t)xmmword_3CFBEC0;
  ToMatrix();
  get_transpose(&v56, &mtx_A, 0);
  *(_OWORD *)&v55.m00 = *(_OWORD *)&v56.m00;
  *(_OWORD *)&v55.m01 = *(_OWORD *)&v56.m01;
  v62 = vct_B;
  *(_OWORD *)&v55.m02 = *(_OWORD *)&v56.m02;
  *(_OWORD *)&v55.m03 = *(_OWORD *)&v56.m03;
  v60 = op_Multiply_60923920(&v55, v62, 0);
  vct_B = v60;
  v39 = &vf00.x;
  v39[4] = v53;
  v39[5] = 0.0;
  v39[6] = v15;
  v39[7] = v16;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v40 = &vf00.x;
  v40[8] = v53;
  v40[9] = 0.0;
  v40[10] = v15;
  v40[11] = v16;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  vct_B = vct_A;
  v43 = vmul_f32(*(float32x2_t *)&vct_A.y, *(float32x2_t *)&vct_B.y).n64_u64[0];
  return (f32)(*((f32 *)&v43 + 1) + (f32)((f32)(vct_A.x * vct_B.x) + *(f32 *)&v43)) >= 0.0;
}

// 0x1fd2630
bool sBtlGetQuat(const sdfVector4_t *t1, const sdfVector4_t *t2) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 *p_x;
  f32 *v14;
  s64 v15;
  f32 v18;
  _BOOL4 v19;
  _BOOL4 v20;
  long f64 v21;

  w = t2->w;
  z = t2->z;
  y = t2->y;
  x = t2->x;
  v7 = t1->w;
  v8 = t1->z;
  v9 = t1->y;
  v10 = t1->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v14 = &vf00.x;
  v14[8] = v10;
  v14[9] = v9;
  v14[10] = v8;
  v14[11] = v7;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v18 = vct_A.z;
  v19 = vct_A.x != 0.0;
  v20 = v18 != 0.0 || v19;
  if (!v20)
  {
    vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
    return v20;
  }
  v21 = sub_18E6660(0, v15);
  FromEuler(0.0, *(f32 *)&v21, 0.0);
  return v20;
}

// 0x1fd28f0
bool sBtlGetNextPos(SBTLUNIT_WORK *wk) {
  f32 x;
  f32 z;
  f32 v7;
  f32 v8;
  struct sdfVector4_t rot;
  struct sdfVector4_t pos;
  sdfMatrix4_t v19;
  sdfMatrix4_t v20;
  sdfVector4_t v21;

  x = wk->mv_spd.x;
  z = wk->mv_spd.z;
  v7 = -x;
  v8 = -z;
  vct_B.x = v7;
  vct_B.y = 0.0;
  vct_B.z = v8;
  vct_B.w = 0.0;
  rot = wk->rot;
  vct_A = rot;
  ToMatrix();
  get_transpose(&v20, &mtx_A, 0);
  *(_OWORD *)&v19.m00 = *(_OWORD *)&v20.m00;
  *(_OWORD *)&v19.m01 = *(_OWORD *)&v20.m01;
  *(_OWORD *)&v19.m02 = *(_OWORD *)&v20.m02;
  *(_OWORD *)&v19.m03 = *(_OWORD *)&v20.m03;
  v21 = op_Multiply_60923920(&v19, vct_B, 0);
  vct_B = v21;
  pos = wk->pos;
  vct_A = pos;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  return 1;
}

// 0x1fd2ba0
bool sBtlGetPosforDistance(SBTLUNIT_WORK *wk, f32 distance) {
  f32 v7;
  struct sdfVector4_t rot;
  struct sdfVector4_t pos;
  sdfMatrix4_t v18;
  sdfMatrix4_t v19;
  sdfVector4_t v20;

  v7 = -distance;
  *(u64 *)&vct_B.x = 0;
  vct_B.z = v7;
  vct_B.w = 0.0;
  rot = wk->rot;
  vct_A = rot;
  ToMatrix();
  get_transpose(&v19, &mtx_A, 0);
  *(_OWORD *)&v18.m00 = *(_OWORD *)&v19.m00;
  *(_OWORD *)&v18.m01 = *(_OWORD *)&v19.m01;
  *(_OWORD *)&v18.m02 = *(_OWORD *)&v19.m02;
  *(_OWORD *)&v18.m03 = *(_OWORD *)&v19.m03;
  v20 = op_Multiply_60923920(&v18, vct_B, 0);
  vct_B = v20;
  pos = wk->pos;
  vct_A = pos;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  return 1;
}

// 0x1fd2e30
bool sBtlSetPushPos(SBTLUNIT_WORK *wk1, f32 r1, SBTLUNIT_WORK *wk2, f32 r2, f32 ground) {
  struct sdfVector4_t v13;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  f32 *p_x;
  f32 v24;
  f32 v25;
  f32 v26;
  struct sdfVector4_t v28;
  f32 v29;
  f32 *v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v35;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 v50;
  s32 v51;
  f32 v66;
  struct sdfVector4_t v68;
  f32 v69;
  struct sdfVector4_t pos;
  f32 dis;
  struct sdfVector4_t v72;
  struct sdfVector4_t nextpos;
  s64 pz;
  sdfVector4_t v77;
  sdfVector4_t v78;

  pz = 0;
  if ((wk2->status & 0x80000) == 0)
  {
    pos = wk1->pos;
    vct_A = pos;
    vct_B = vct_A;
    v13 = wk2->pos;
    vct_A = v13;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    sub_1949110(0);
    dis = r1 + r2;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, dis);
    vct_B = vct_A;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    x = vct_A.x;
    y = vct_A.y;
    z = vct_A.z;
    w = vct_A.w;
    if (y != ground)
    {
      if ((wk2->status & 0x200000) == 0 && (wk2->vstatus & 0x80) == 0)
      {
        v68 = wk1->pos;
        vct_A = v68;
        p_x = &vf00.x;
        v24 = p_x[4];
        v25 = p_x[6];
        v26 = p_x[7];
        vct_A.x = v24;
        vct_A.y = ground;
        vct_A.z = v25;
        vct_A.w = v26;
        v28 = wk1->pos;
        vct_B = v28;
        vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
        v66 = v24;
        v69 = v26;
        v29 = v25;
        v30 = &vf00.x;
        v31 = v30[6];
        v32 = v30[4];
        v33 = v30[5];
        v35 = sqrtf((f32)((f32)(v32 * v32) + (f32)(v33 * v33)) + (f32)(v31 * v31));
        dis = sqrtf((f32)(dis * dis) - (f32)(v35 * v35));
        vct_A.x = x;
        vct_A.y = ground;
        vct_A.z = z;
        vct_A.w = w;
        vct_B.x = v66;
        vct_B.y = ground;
        vct_B.z = v29;
        vct_B.w = v69;
        vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
        sub_1949110(0);
        vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, dis);
        vct_B.x = v66;
        vct_B.y = ground;
        vct_B.z = v29;
        vct_B.w = v69;
        vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
        x = vct_A.x;
        y = vct_A.y;
        z = vct_A.z;
        w = vct_A.w;
        if ((wk2->status & 0x80) != 0)
          goto LABEL_113;
        goto LABEL_94;
      }
    }
    vct_A.x = x;
    vct_A.y = y;
    vct_A.z = z;
    vct_A.w = w;
    if ((wk2->status & 0x80) != 0)
      goto LABEL_113;
LABEL_94:
    v45 = wk2->pos.x;
    v46 = wk2->pos.y;
    v48 = wk2->pos.z;
    v47 = wk2->pos.w;
    v77.y = v46;
    v77.z = v48;
    v77.w = v47;
    v78.x = x;
    v78.y = y;
    v78.z = z;
    v77.x = v45;
    v78.w = w;
    if (!sBtlCheckMapHit_Cross(v77, v78, dis))
      goto LABEL_101;
    v49 = wk2->pos.x;
    v50 = wk2->pos.z;
    v51 = sBtlCheckMapHit_Data(v49, v50, x, z, (f32 *)&pz + 1, &pz);
    if (v51)
    {
      if (v51 != -1)
      {
        x = *((f32 *)&pz + 1);
        z = *(f32 *)&pz;
        goto LABEL_113;
      }
LABEL_101:
      wk2->mv_spd.z = 0.0;
      nextpos = wk2->nextpos;
      vct_A = nextpos;
      return 0;
    }
LABEL_113:
    vct_A.x = x;
    vct_A.y = y;
    vct_A.z = z;
    vct_A.w = w;
    return 1;
  }
  v72 = wk2->pos;
  vct_A = v72;
  return 1;
}

// 0x1fd3a50
bool sBtlSetPullPos(SBTLUNIT_WORK *wk1, f32 r1, SBTLUNIT_WORK *wk2, f32 r2, f32 ground) {
  f32 y;
  f32 x;
  f32 w;
  f32 z;
  f32 *p_x;
  struct sdfVector4_t pos;
  f32 *v20;
  struct sdfVector4_t rot;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v25;
  s32 v27;
  s64 v28;
  f32 *v31;
  u64 v33;
  f32 v34;
  f32 *v36;
  struct sdfVector4_t v37;
  f32 v39;
  f32 v40;
  f32 v41;
  f32 v42;
  f32 *v44;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  bool v52;
  f32 v54;
  f32 v55;
  f32 v56;
  f32 v57;
  f32 v58;
  f32 v61;
  struct sdfVector4_t v62;
  struct sdfVector4_t v63;
  struct sdfVector4_t v64;
  f32 *v65;
  f32 *v71;
  f32 v72;
  f32 v73;
  f32 v74;
  struct sdfVector4_t v76;
  f32 v77;
  f32 v78;
  f32 *v79;
  f32 v80;
  f32 v81;
  f32 v82;
  f32 v84;
  f32 *v86;
  f32 *v87;
  f32 *v89;
  f32 v94;
  f32 v95;
  f32 v96;
  f32 v97;
  f32 v98;
  f32 v99;
  s32 v100;
  f32 v114;
  f32 v115;
  f32 v116;
  f32 v117;
  f32 v118;
  f32 v121;
  f32 v122;
  f32 v123;
  struct sdfVector4_t v126;
  f32 v127;
  f32 dis;
  struct sdfVector4_t nextpos;
  s64 pz;
  sdfMatrix4_t v143;
  sdfMatrix4_t v144;
  sdfVector4_t v145;
  sdfVector4_t v146;
  sdfVector4_t v147;
  sdfVector4_t v149;
  sdfVector4_t v150;
  sdfVector4_t v151;
  sdfVector4_t v152;
  sdfVector4_t v153;
  sdfVector4_t v154;

  pz = 0;
  x = wk1->pos.x;
  y = wk1->pos.y;
  z = wk1->pos.z;
  w = wk1->pos.w;
  if ((wk1->status & 0x80000) == 0)
  {
    p_x = &vf00.x;
    p_x[4] = x;
    p_x[5] = y;
    p_x[6] = z;
    p_x[7] = w;
    pos = wk2->pos;
    vct_B = pos;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    sub_1949110(0);
    v20 = &vf00.x;
    rot = wk2->rot;
    v22 = v20[4];
    v23 = v20[5];
    v24 = v20[6];
    v25 = v20[7];
    vct_A = rot;
    ToMatrix();
    v27 = (u8)byte_5756085;
    vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
    if (v27)
    {
      goto LABEL_19;
    }
    else
    {
      goto LABEL_19;
    }
LABEL_19:
    get_transpose(&v144, &mtx_A, 0);
    v143 = v144;
    v145 = op_Multiply_60923920(&v143, vct_A, 0);
    vct_A = v145;
    v31 = &vf00.x;
    v31[8] = v22;
    v31[9] = v23;
    v31[10] = v24;
    v31[11] = v25;
    v33 = vmul_f32(*(float32x2_t *)&vct_A.y, *(float32x2_t *)&vct_B.y).n64_u64[0];
    v34 = *((f32 *)&v33 + 1)
        + (f32)((f32)(vct_A.x * vct_B.x) + *(f32 *)&v33);
    if (v34 < 0.9 && v34 > -0.9)
    {
      goto LABEL_26;
LABEL_27:
      v36 = &vf00.x;
      v36[4] = v22;
      v36[5] = v23;
      v36[6] = v24;
      v36[7] = v25;
      dis = r1 + r2;
      vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, dis);
      v37 = wk2->pos;
      vct_B = v37;
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v39 = vct_A.x;
      v40 = vct_A.y;
      v42 = vct_A.z;
      v41 = vct_A.w;
      if (v40 != ground)
      {
        if ((wk1->status & 0x200000) == 0 && (wk1->vstatus & 0x80) == 0)
        {
          v126 = wk2->pos;
          vct_A = v126;
          v71 = &vf00.x;
          v72 = v71[4];
          v73 = v71[6];
          v74 = v71[7];
          vct_A.x = v72;
          vct_A.y = ground;
          vct_A.z = v73;
          vct_A.w = v74;
          v76 = wk2->pos;
          vct_B = v76;
          vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
          v122 = v72;
          v127 = v74;
          v77 = v73;
          v78 = ground;
          v79 = &vf00.x;
          v80 = v79[6];
          v82 = v79[4];
          v81 = v79[5];
          v84 = sqrtf((f32)((f32)(v82 * v82) + (f32)(v81 * v81)) + (f32)(v80 * v80));
          dis = sqrtf((f32)(dis * dis) - (f32)(v84 * v84));
          v86 = &vf00.x;
          v86[4] = v39;
          v86[5] = v78;
          v86[6] = v42;
          v86[7] = v41;
          v87 = &vf00.x;
          v87[8] = v122;
          v87[9] = v78;
          v87[10] = v77;
          v87[11] = v127;
          vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
          sub_1949110(0);
          vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, dis);
          v89 = &vf00.x;
          v89[8] = v122;
          v89[9] = v78;
          v89[10] = v77;
          v89[11] = v127;
          vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
          v39 = vct_A.x;
          v40 = vct_A.y;
          v42 = vct_A.z;
          v41 = vct_A.w;
          if ((wk1->status & 0x80) != 0)
            goto LABEL_188;
          goto LABEL_147;
        }
      }
      vct_A.x = v39;
      vct_A.y = v40;
      vct_A.z = v42;
      vct_A.w = v41;
      if ((wk1->status & 0x80) != 0)
        goto LABEL_188;
LABEL_147:
      v94 = wk1->pos.x;
      v95 = wk1->pos.y;
      v97 = wk1->pos.z;
      v96 = wk1->pos.w;
      v152.y = v95;
      v152.z = v97;
      v152.w = v96;
      v154.x = v39;
      v154.y = v40;
      v154.z = v42;
      v152.x = v94;
      v154.w = v41;
      if (!sBtlCheckMapHit_Cross(v152, v154, dis))
        goto LABEL_154;
      v98 = wk1->pos.x;
      v99 = wk1->pos.z;
      v100 = sBtlCheckMapHit_Data(v98, v99, v39, v42, (f32 *)&pz + 1, &pz);
      if (v100)
      {
        if (v100 != -1)
        {
          v39 = *((f32 *)&pz + 1);
          v42 = *(f32 *)&pz;
          goto LABEL_188;
        }
LABEL_154:
        wk1->mv_spd.z = 0.0;
        nextpos = wk1->nextpos;
        vct_A = nextpos;
        return 0;
      }
LABEL_188:
      vct_A.x = v39;
      vct_A.y = v40;
      vct_A.z = v42;
      vct_A.w = v41;
      return 1;
    }
    v118 = r1;
    v121 = r2;
    v123 = ground;
    v149.x = wk1->pos.x;
    v45 = wk1->pos.y;
    v46 = wk1->pos.z;
    v47 = wk1->pos.w;
    v48 = wk1->rot.x;
    v153.y = wk1->rot.y;
    v153.z = wk1->rot.z;
    v153.w = wk1->rot.w;
    v116 = wk1->rot.y;
    v117 = wk1->pos.x;
    v114 = wk1->rot.w;
    v115 = wk1->rot.z;
    v153.w = v114;
    v153.z = v115;
    v153.y = v116;
    v149.x = v117;
    v149.y = v45;
    v149.z = v46;
    v149.w = v47;
    v153.x = v48;
    *(u64 *)&v147.z = v28;
    v52 = !sBtlCheckPos_Right(v149, v153, v147);
    if (v52)
      v54 = 90.0;
    else
      v54 = -90.0;
    v55 = wk1->rot.x;
    v56 = wk1->rot.y;
    v57 = wk1->rot.z;
    v58 = wk1->rot.w;
    v150.x = v55;
    v150.y = v56;
    v150.z = v57;
    v150.w = v58;
    sBtlGetRotateDeg(v150, v54);
    ToMatrix();
    ground = v123;
    r1 = v118;
    r2 = v121;
    vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
    get_transpose(&v144, &mtx_A, 0);
    v151 = vct_A;
    v143 = v144;
    v146 = op_Multiply_60923920(&v143, v151, 0);
    vct_A = v146;
    v61 = wk1->mv_spd.z;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v61);
    v62 = wk1->pos;
    vct_B = v62;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v63 = vct_A;
    vct_A = v63;
    v64 = wk2->pos;
    vct_B = v64;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    sub_1949110(0);
    v65 = &vf00.x;
    v22 = v65[4];
    v23 = v65[5];
    v24 = v65[6];
    v25 = v65[7];
LABEL_26:
    goto LABEL_27;
  }
  v44 = &vf00.x;
  v44[4] = x;
  v44[5] = y;
  v44[6] = z;
  v44[7] = w;
  return 1;
}

// 0x1fd4dc0
bool sBtlCheckWorldtoScreen(const sdfVector4_t *pos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  struct sdfVector4_t CameraEyePos_local;
  f32 *v12;
  f32 v13;
  f32 v14;
  f32 v15;
  sdfMatrix4_t *p_CameraTM;
  _OWORD *v22;
  s32 v23;
  long f64 *v24;
  __int128 v26;
  long f64 v27;
  __int128 v28;
  u64 v32;
  long f64 v36;
  __int128 v39;
  __int128 v40;
  __int128 v41;
  __int128 v42;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  CameraEyePos_local = CameraEyePos;
  vct_B = CameraEyePos_local;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v12 = &vf00.x;
  v13 = v12[6];
  v14 = v12[4];
  v15 = v12[5];
  if (sqrtf((f32)((f32)(v14 * v14) + (f32)(v15 * v15)) + (f32)(v13 * v13)) <= 16.0)
    return 0;
  sub_1949110(0);
  vct_B = vct_A;
  p_CameraTM = &CameraTM;
  v39 = *(_OWORD *)&p_CameraTM->m00;
  v40 = *(_OWORD *)&p_CameraTM->m01;
  v41 = *(_OWORD *)&p_CameraTM->m02;
  v42 = *(_OWORD *)&p_CameraTM->m03;
  v22 = &vf00.x;
  v23 = (u8)byte_575642E;
  v22[4] = v39;
  v22[5] = v40;
  v22[6] = v41;
  v22[7] = v42;
  if (v23)
  {
    goto LABEL_24;
  }
  else
  {
    goto LABEL_24;
  }
LABEL_24:
  v24 = (long f64 *)&vf00.x;
  v26 = *((_OWORD *)v24 + 5);
  v24[8] = v24[4];
  *((_OWORD *)v24 + 9) = v26;
  v27 = v24[6];
  v28 = *((_OWORD *)v24 + 7);
  v24[10] = v27;
  *((_OWORD *)v24 + 11) = v28;
  sub_1996630(0, v27);
  vct_A = GetRow(&mtx_A, 2, 0);
  sub_1949110(0);
  v32 = vmul_f32(*(float32x2_t *)&vct_A.y, *(float32x2_t *)&vct_B.y).n64_u64[0];
  return (f32)(*((f32 *)&v32 + 1) + (f32)((f32)(vct_A.x * vct_B.x) + *(f32 *)&v32)) > 0.5;
}

// 0x1fd5340
bool sBtlChangeWorldtoScreen(sdfVector4_t *ppos) {
  struct sdfVector4_t CameraEyePos_local;
  f32 *p_x;
  f32 z;
  f32 x;
  f32 y;
  sdfMatrix4_t *p_CameraTM;
  __int128 v18;
  __int128 v20;
  __int128 v22;
  _OWORD *v23;
  s32 v24;
  __int128 v25;
  long f64 *v26;
  __int128 v27;
  long f64 v28;
  __int128 v29;
  u64 v33;
  long f64 *v35;
  __int128 v37;
  long f64 v38;
  __int128 v39;
  sdfMatrix4_t *p_TM;
  struct sdfVector4_t scale;
  struct sdfVector4_t trans;
  bool result;
  f32 v51;
  f32 v52;
  f32 v53;
  bool v54;
  f32 v55;
  f32 v56;
  f32 v57;
  long f64 v59;
  long f64 v60;
  sdfMatrix4_t v67;
  sdfMatrix4_t v68;
  sdfVector4_t v69;

  *(u64 *)&ppos->x = 0;
  *(u64 *)&ppos->z = 0;
  vct_C = vct_A;
  CameraEyePos_local = CameraEyePos;
  vct_B = CameraEyePos_local;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  p_x = &vf00.x;
  z = p_x[6];
  x = p_x[4];
  y = p_x[5];
  if (sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z)) <= 16.0)
    return 0;
  sub_1949110(0);
  vct_B = vct_A;
  p_CameraTM = &CameraTM;
  v18 = *(_OWORD *)&p_CameraTM->m01;
  *(_OWORD *)&v68.m00 = *(_OWORD *)&p_CameraTM->m00;
  *(_OWORD *)&v68.m01 = v18;
  v20 = *(_OWORD *)&p_CameraTM->m03;
  *(_OWORD *)&v68.m02 = *(_OWORD *)&p_CameraTM->m02;
  *(_OWORD *)&v68.m03 = v20;
  v22 = *(_OWORD *)&v68.m01;
  v23 = &vf00.x;
  v24 = (u8)byte_575642E;
  v23[4] = *(_OWORD *)&v68.m00;
  v23[5] = v22;
  v25 = *(_OWORD *)&v68.m03;
  v23[6] = *(_OWORD *)&v68.m02;
  v23[7] = v25;
  if (v24)
  {
    goto LABEL_24;
  }
  else
  {
    goto LABEL_24;
  }
LABEL_24:
  v26 = (long f64 *)&vf00.x;
  v27 = *((_OWORD *)v26 + 5);
  v26[8] = v26[4];
  *((_OWORD *)v26 + 9) = v27;
  v28 = v26[6];
  v29 = *((_OWORD *)v26 + 7);
  v26[10] = v28;
  *((_OWORD *)v26 + 11) = v29;
  sub_1996630(0, v28);
  vct_A = GetRow(&mtx_A, 2, 0);
  sub_1949110(0);
  v33 = vmul_f32(*(float32x2_t *)&vct_A.y, *(float32x2_t *)&vct_B.y).n64_u64[0];
  if ((f32)(*((f32 *)&v33 + 1) + (f32)((f32)(vct_A.x * vct_B.x) + *(f32 *)&v33)) <= 0.5)
    return 0;
  vct_A = vct_C;
  v35 = (long f64 *)&vf00.x;
  v37 = *((_OWORD *)v35 + 9);
  v35[4] = v35[8];
  *((_OWORD *)v35 + 5) = v37;
  v38 = v35[10];
  v39 = *((_OWORD *)v35 + 11);
  v35[6] = v38;
  *((_OWORD *)v35 + 7) = v39;
  p_TM = &ScreenParam->TM;
  sub_19636F0(p_TM, 0, v38);
  vct_A.w = 1.0;
  get_transpose(&v68, &mtx_A, 0);
  v67 = v68;
  v69 = op_Multiply_60923920(&v67, vct_A, 0);
  vct_A.x = v69.x * (f32)(1.0 / v69.w);
  vct_A.y = v69.y * (f32)(1.0 / v69.w);
  vct_A.z = v69.z * (f32)(1.0 / v69.w);
  vct_A.w = 1.0 / v69.w;
  scale = ScreenParam->scale;
  vct_B = scale;
  vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  trans = ScreenParam->trans;
  vct_B = trans;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  result = 1;
  v51 = vct_A.x;
  v52 = vct_A.y;
  v53 = ((s32)v51 - 1792);
  v54 = v51 == INFINITY;
  v55 = 2147500000.0;
  if (!v54)
    v55 = v53;
  v54 = v52 == INFINITY;
  v56 = (2 * (s32)v52 - 3872);
  v57 = -3872.0;
  if (!v54)
    v57 = v56;
  ppos->x = v55;
  ppos->y = v57;
  return result;
}

// 0x1fbdcd0
bool sBtlChangeWorldtoScreenUnity(sdfVector4_t *ppos) {
  f32 *p_x;
  f32 z;
  f32 x;
  f32 y;
  sdfVector3_t v12;

  p_x = &vf00.x;
  z = p_x[6];
  x = p_x[4];
  y = p_x[5];
  v12.z = z / -100.0;
  v12.y = y / -100.0;
  v12.x = x / -100.0;
  *(sdfVector3_t *)&ppos->x = WorldToScreenPoint_60728304(cameraObject->_camera, v12, 0);
  ppos->w = 0.0;
  return 1;
}

// 0x1fd5cb0
bool sBtlChangeWorldtoScreenUnity4(sdfVector4_t *ppos) {
  f32 *p_x;
  f32 v7;
  f32 v8;
  f32 v9;
  void *camera;
  bool result;
  bool v12;
  sdfVector3_t v13;
  sdfVector3_t v14;
  sdfVector3_t v15;
  sdfVector3_t v16;

  p_x = &vf00.x;
  v7 = p_x[4] / -100.0;
  v8 = p_x[5] / -100.0;
  v9 = p_x[6] / -100.0;
  v15.x = v7;
  v15.y = v8;
  v15.z = v9;
  camera = cameraObject->_camera;
  v13 = WorldToScreenPoint_60728304(camera, v15, 0);
  result = 0;
  *(sdfVector3_t *)&ppos->x = v13;
  ppos->w = 0.0;
  if (v13.z >= 0.0)
  {
    v16.x = v7;
    v16.y = v8;
    v16.z = v9;
    v14 = WorldToViewportPoint_60728416(camera, v16, 0);
    v12 = v14.x >= 0.0;
    if (v14.x >= 1.0)
      v12 = 0;
    if (v14.y < 0.0)
      v12 = 0;
    return v14.y < 1.0 && v12;
  }
  return result;
}

// 0x1fd5e40
bool sBtlChangeWorldtoScreenUnity3(f32 x, f32 y, f32 z, sdfVector4_t *ppos) {
  f32 v10;
  f32 v11;
  f32 v12;
  void *camera;
  bool result;
  bool v15;
  sdfVector3_t v16;
  sdfVector3_t v17;
  sdfVector3_t v18;
  sdfVector3_t v19;

  v10 = x / -100.0;
  v11 = y / -100.0;
  v12 = z / -100.0;
  v18.x = v10;
  v18.y = v11;
  v18.z = v12;
  camera = cameraObject->_camera;
  v16 = WorldToScreenPoint_60728304(camera, v18, 0);
  result = 0;
  *(sdfVector3_t *)&ppos->x = v16;
  ppos->w = 0.0;
  if (v16.z >= 0.0)
  {
    v19.x = v10;
    v19.y = v11;
    v19.z = v12;
    v17 = WorldToViewportPoint_60728416(camera, v19, 0);
    v15 = v17.x >= 0.0;
    if (v17.x >= 1.0)
      v15 = 0;
    if (v17.y < 0.0)
      v15 = 0;
    return v17.y < 1.0 && v15;
  }
  return result;
}

// 0x1fd5f50
bool sBtlChangeWorldtoScreen2(sdfVector4_t *ppos) {
  struct sdfVector4_t CameraEyePos_local;
  sdfMatrix4_t *p_CameraTM;
  __int128 v12;
  __int128 v14;
  __int128 v15;
  _OWORD *p_x;
  s32 v17;
  __int128 v18;
  long f64 *v19;
  __int128 v21;
  long f64 v22;
  __int128 v23;
  long f64 *v27;
  __int128 v28;
  long f64 v29;
  __int128 v30;
  struct sdfVector4_t scale;
  struct sdfVector4_t trans;
  bool result;
  f32 x;
  f32 y;
  f32 v42;
  bool v43;
  f32 v44;
  f32 v45;
  f32 v46;
  long f64 v50;
  sdfMatrix4_t v57;
  sdfMatrix4_t v58;
  sdfVector4_t v59;

  vct_C = vct_A;
  CameraEyePos_local = CameraEyePos;
  vct_B = CameraEyePos_local;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  vct_B = vct_A;
  p_CameraTM = &CameraTM;
  v12 = *(_OWORD *)&CameraTM.m01;
  *(_OWORD *)&v58.m00 = *(_OWORD *)&p_CameraTM->m00;
  *(_OWORD *)&v58.m01 = v12;
  v14 = *(_OWORD *)&p_CameraTM->m03;
  *(_OWORD *)&v58.m02 = *(_OWORD *)&p_CameraTM->m02;
  *(_OWORD *)&v58.m03 = v14;
  v15 = *(_OWORD *)&v58.m01;
  p_x = &vf00.x;
  v17 = (u8)byte_575642E;
  p_x[4] = *(_OWORD *)&v58.m00;
  p_x[5] = v15;
  v18 = *(_OWORD *)&v58.m03;
  p_x[6] = *(_OWORD *)&v58.m02;
  p_x[7] = v18;
  if (v17)
  {
    goto LABEL_20;
  }
  else
  {
    goto LABEL_20;
  }
LABEL_20:
  v19 = (long f64 *)&vf00.x;
  v21 = *((_OWORD *)v19 + 5);
  v19[8] = v19[4];
  *((_OWORD *)v19 + 9) = v21;
  v22 = v19[6];
  v23 = *((_OWORD *)v19 + 7);
  v19[10] = v22;
  *((_OWORD *)v19 + 11) = v23;
  sub_1996630(0, v22);
  vct_A = GetRow(&mtx_A, 2, 0);
  sub_1949110(0);
  vct_A = vct_C;
  v27 = (long f64 *)&vf00.x;
  v28 = *((_OWORD *)v27 + 9);
  v27[4] = v27[8];
  *((_OWORD *)v27 + 5) = v28;
  v29 = v27[10];
  v30 = *((_OWORD *)v27 + 11);
  v27[6] = v29;
  *((_OWORD *)v27 + 7) = v30;
  sub_19636F0(&ScreenParam->TM, 0, v29);
  vct_A.w = 1.0;
  get_transpose(&v58, &mtx_A, 0);
  v57 = v58;
  v59 = op_Multiply_60923920(&v57, vct_A, 0);
  vct_A.x = v59.x * (f32)(1.0 / v59.w);
  vct_A.y = v59.y * (f32)(1.0 / v59.w);
  vct_A.z = v59.z * (f32)(1.0 / v59.w);
  vct_A.w = 1.0 / v59.w;
  ppos->z = vct_A.z;
  scale = ScreenParam->scale;
  vct_B = scale;
  vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  trans = ScreenParam->trans;
  vct_B = trans;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  result = 1;
  x = vct_A.x;
  y = vct_A.y;
  v42 = ((s32)x - 1792);
  v43 = x == INFINITY;
  v44 = 2147500000.0;
  if (!v43)
    v44 = v42;
  v43 = y == INFINITY;
  v45 = (2 * (s32)y - 3872);
  v46 = -3872.0;
  if (!v43)
    v46 = v45;
  ppos->x = v44;
  ppos->y = v46;
  return result;
}

// 0x1fd67e0
bool sBtlChkWorldtoScreenIn(f32 x, f32 y, f32 z) {
  f32 v8;
  f32 v9;
  f32 v10;
  void *camera;
  bool v13;
  sdfVector3_t v14;
  sdfVector3_t v15;
  sdfVector3_t v16;

  v8 = x / -100.0;
  v9 = y / -100.0;
  v10 = z / -100.0;
  v15.x = v8;
  v15.y = v9;
  v15.z = v10;
  camera = cameraObject->_camera;
  if (COERCE_FLOAT(LODWORD(WorldToScreenPoint_60728304(camera, v15, 0).z)) < 0.0)
    return 0;
  v16.x = v8;
  v16.y = v9;
  v16.z = v10;
  v14 = WorldToViewportPoint_60728416(camera, v16, 0);
  v13 = v14.x >= 0.0;
  if (v14.x >= 1.0)
    v13 = 0;
  if (v14.y < 0.0)
    v13 = 0;
  return v14.y < 1.0 && v13;
}

// 0x1fd68f0
s32 sBtlGetLargePara(s16 *adr, s32 max) {
  s64 v4;
  s16 v5;
  s32 result;
  s16 *m_Items;
  s32 v8;
  _BOOL4 v10;

  if (max < 1)
    return 0;
  v4 = 0;
  v5 = 0;
  result = 0;
  m_Items = adr;
  do
  {
    v8 = m_Items[v4];
    v10 = v8 < 1 || v8 < v5;
    if (!v10)
      result = v4;
    ++v4;
    if (!v10)
      v5 = v8;
  }
  while (max != v4);
  return result;
}

// 0x1fd6950
void sBtlParaAdd(s32 *para, s32 add, s32 max, s32 reset) {
  s32 v5;

  v5 = *para + add;
  if (v5 > max)
    v5 = reset;
  *para = v5;
}

// 0x1fd6970
void sBtlParaAdd_16(s16 *para, s16 add, s16 max, s16 reset) {
  s16 v5;

  v5 = *para + add;
  if (v5 > max)
    v5 = reset;
  *para = v5;
}

// 0x1fd6990
void sBtlParaAdd_8(s8 *para, s8 add, s8 max, s8 reset) {
  s8 v5;

  v5 = *para + add;
  if (v5 > max)
    v5 = reset;
  *para = v5;
}

// 0x1fd69b0
void sBtlParaDec(s32 *para, s32 dec, s32 max) {
  s32 v4;

  v4 = *para - dec;
  if (v4 < 0)
    v4 = max;
  *para = v4;
}

// 0x1fd69d0
void sBtlParaDec_16(s16 *para, s16 dec, s16 max) {
  s16 v4;

  v4 = *para - dec;
  if (v4 < 0)
    v4 = max;
  *para = v4;
}

// 0x1fd69f0
void sBtlParaDec_8(s8 *para, s8 dec, s8 max) {
  s8 v4;

  v4 = *para - dec;
  if (v4 < 0)
    v4 = max;
  *para = v4;
}

// 0x1fd6a10
f32 sBtlGetBezier(f32 x0, f32 x1, f32 x2, f32 x3, f32 bt) {
  return (f32)((f32)((f32)(x3 * bt) * bt) * bt)
       + (f32)((f32)((f32)(1.0 - bt) * (f32)((f32)((f32)(x2 * 3.0) * bt) * bt)) + (f32)((f32)((f32)(1.0 - bt) * (f32)((f32)((f32)(x1 * 3.0) * bt) * (f32)(1.0 - bt))) + (f32)((f32)(1.0 - bt) * (f32)((f32)(1.0 - bt) * (f32)((f32)(1.0 - bt) * x0)))));
}

// 0x1fd6a70
u8 sBtlGetMeireiFont(s32 id) {
  return meirei_data[id];
}

// 0x1fd6ae0
void sBtlDrawMeireiList(s32 x, s32 y, s32 z, u32 rgba, s32 id) {
  ;
}

// 0x1fd6af0
void sBtlDrawNum_Hex(s32 x, s32 y, s32 z, u32 rgba, char *str) {
  ;
}

// 0x1fd6b00
void sBtlDrawNum(s32 x, s32 y, s32 z, u32 rgba, s8 str) {
  ;
}

// 0x1fd6b10
char *sBtlGetRaceNameFont(s32 id) {
  Il2CppObject *v3;
  char *v4;
  char *v5;
  s32 data;

  data = id;
  v3 = Box(s32, &data);
  v4 = Format("{0:d4}", v3, 0);
  v5 = Concat_54766928("RACE_L", v4, 0);
  return GetLocalizeText(v5, 1);
}

// 0x1fd6c00
void sBtlDrawRaceName(s32 x, s32 y, s32 z, u32 rgba, s32 id) {
  ;
}

// 0x1fd6c10
char *sBtlGetPlayerNameFont(s32 id) {
  return "test_player_name";
}

// 0x1fd6c60
void sBtlDrawPlayerName(s32 x, s32 y, s32 z, u32 rgba, s32 id) {
  char *DevilNameFont;

  DevilNameFont = sBtlGetDevilNameFont(id, 0);
  sprDbgPrintStr(x, y, 0, rgba, DevilNameFont, 109, 24);
}

// 0x1fd6d30
char *sBtlGetDevilNameFont(s32 id, bool tagID) {
  s32 v4;
  s32 v5;
  Il2CppObject *v6;
  char *v7;
  char *v8;
  s32 *EventBit;
  bool v13;
  s32 data;

  if (id == 512)
    v4 = 364;
  else
    v4 = id;
  if (v4 == 513)
    v4 = 38;
  if (v4 == 514)
    v4 = 353;
  if (v4 == 515)
    v4 = 358;
  if (v4 == 516)
    v4 = 67;
  if (v4 == 517)
    v4 = 54;
  if (v4 == 518)
    v4 = 49;
  if (v4 == 519)
    v4 = 382;
  if (v4 == 520)
    v4 = 11;
  if (v4 == 521)
    v4 = 386;
  if (v4 == 522)
    v4 = 13;
  if (v4 == 523)
    v4 = 147;
  if (v4 == 524)
    v4 = 41;
  if (v4 == 525)
    v4 = 398;
  if (v4 == 526)
    v4 = 354;
  if (v4 == 527)
    v4 = 13;
  if (v4 == 528)
    v4 = 358;
  if (v4 == 529)
    v4 = 19;
  if (v4 == 530)
    v4 = 29;
  if (v4 == 531)
    v4 = 52;
  if (v4 == 532)
    v4 = 383;
  if (v4 == 533)
    v4 = 22;
  if (v4 == 534)
    v5 = 365;
  else
    v5 = v4;
  if ((u32)(v5 - 413) >= 4)
  {
    if (v5 == 480)
    {
      v4 = 380;
    }
    else if ((u32)(v5 - 464) >= 0xFFFFFFC0)
    {
      v4 = v5 - 64;
    }
    else
    {
      v4 = v5;
    }
  }
  data = v4;
  v6 = Box(s32, &data);
  v7 = Format("{0:d4}", v6, 0);
  v8 = Concat_54766928("DEVIL_L", v7, 0);
  if (!!get_isPlaying(0))
  {
    if (GBWK)
    {
      EventBit = GBWK->EventBit;
      v13 = v5 != 241 || EventBit == 0;
      if (!v13 && !evtBitCheck(42))
        v8 = Concat_54766928(v8, "_1", 0);
    }
  }
  return GetLocalizeText(v8, 1);
}

// 0x1fd7050
bool sBtlIsDLCDevil(s32 id) {
  return (u32)(id - 496) < 6;
}

// 0x1fd7060
void sBtlDrawDevilName(s32 x, s32 y, s32 z, u32 rgba, s32 id) {
  char *DevilNameFont;

  DevilNameFont = sBtlGetDevilNameFont(id, 0);
  sprDbgPrintStr(x, y, z, rgba, DevilNameFont, 109, 24);
}

// 0x1fd7130
void sBtlDrawDevilName2(SBTLUNIT_WORK *wk, s32 x, s32 y, s32 z, u32 rgba, s32 id) {
  char *DevilNameFont;
  void *gageUI;
  char *v15;
  char *v16;
  s32 v17;

  v17 = id;
  DevilNameFont = sBtlGetDevilNameFont(id, 0);
  gageUI = wk->gageUI;
  if (!op_Inequality(gageUI, 0, 0))
    return;
  v15 = ToString_55996800((s32)&v17, "X3", 0);
  v16 = Concat_54832128("[0x", v15, "]", DevilNameFont, 0);
  DrawSkillName(gageUI, x, y, z, rgba, v16, 0);
}

// 0x1fd72b0
void sBtlDrawNum_Font0(s32 x, s32 y, s32 z, u32 rgba, s32 num, s8 mode) {
  ;
}

// 0x1fd72c0
void sBtlDrawNum_X(s32 x, s32 y, s32 z, u32 rgba, s32 id) {
  ;
}

// 0x1fd72d0
char *sBtlGetSkillNameFont(s32 id) {
  Il2CppObject *v3;
  char *v4;
  char *v5;
  s32 data;

  data = id;
  v3 = Box(s32, &data);
  v4 = Format("{0:d4}", v3, 0);
  v5 = Concat_54766928("SKILL_L", v4, 0);
  return GetLocalizeText(v5, 1);
}

// 0x1fd73c0
char *sBtlGetSkillHelpFont(s32 id, bool tagID) {
  Il2CppObject *v8;
  char *v9;
  char *v10;
  char *LocalizeText;
  s32 data;

  data = id;
  nowSkillHelpID = id;
  v8 = Box(s32, &data);
  v9 = Format("{0:d4}", v8, 0);
  v10 = Concat_54766928("SKILLHELP_L", v9, 0);
  if (!tagID)
  {
    LocalizeText = GetLocalizeText(v10, 1);
    return sBtlGetSkillHelpValue(id, LocalizeText);
  }
  return v10;
}

// 0x1fd7510
char *sBtlGetSkillHelpValue(s32 id, char *name) {
  SBTLSKILLP_TBL *v5;
  s32 shild_dmg;
  char **v8;
  char *LocalizeText;
  char *v10;
  s32 para;
  f32 v13;
  s32 v14;
  char *v15;
  s32 v17;

  v17 = 0;
  v5 = tbldata[id];
  shild_dmg = v5->shild_dmg;
  if (shild_dmg <= 4)
  {
    v8 = &"SYSMES_L0166";
    goto LABEL_14;
  }
  if ((u32)shild_dmg <= 9)
  {
    v8 = &"SYSMES_L0167";
  }
  else
  {
    if ((u32)shild_dmg <= 0xE)
      v8 = &"SYSMES_L0168";
    else
      v8 = &"SYSMES_L0169";
  }
LABEL_14:
  LocalizeText = GetLocalizeText(*v8, 1);
  v10 = Replace_54838864(name, "<V 0>", LocalizeText, 0);
  para = v5->para;
  v17 = para;
  if (wk->battlemode != 3)
  {
    if (!sBtlGetSpiritSkillChk(1450))
      goto LABEL_25;
    if ((v5->flg & 0x200001) == 1)
    {
      para *= 2;
      v17 = para;
    }
  }
LABEL_25:
  if (!!sBtlGetSpiritSkillChk(1447))
  {
    v13 = (f32)para * 0.8;
    v14 = v13;
    if (v13 == INFINITY)
      v14 = 0x80000000;
    v17 = v14;
  }
  v15 = ToString((s32)&v17, 0);
  return Replace_54838864(v10, "<V 1>", v15, 0);
}

// 0x1fd77d0
void sBtlDrawSkillName(SBTLUNIT_WORK *wk, s32 x, s32 y, s32 z, u32 rgba, SKLID id) {
  char *SkillNameFont;
  void *gageUI;

  SkillNameFont = sBtlGetSkillNameFont(id);
  gageUI = wk->gageUI;
  if (!op_Inequality(gageUI, 0, 0))
    return;
  goto LABEL_7;
  if (op_Inequality(gageUI, 0, 0))
LABEL_7:
    DrawSkillName(gageUI, x, y, z, rgba, SkillNameFont, 0);
}

// 0x1fd78e0
void sBtlDrawSkillNameOff(SBTLUNIT_WORK *wk) {
  void *gageUI;

  gageUI = wk->gageUI;
  if (!op_Inequality(gageUI, 0, 0))
    return;
  goto LABEL_4;
  if (op_Inequality(gageUI, 0, 0))
LABEL_4:
    DrawSkillName(gageUI, 0, 0, 0, 0, "", 0);
}

// 0x1fd79c0
char *sBtlGetItemNameFont(s32 id) {
  Il2CppObject *v3;
  char *v4;
  char *v5;
  s32 data;

  data = id;
  v3 = Box(s32, &data);
  v4 = Format("{0:d4}", v3, 0);
  v5 = Concat_54766928("ITEM_L", v4, 0);
  return GetLocalizeText(v5, 1);
}

// 0x1fd7ab0
char *sBtlGetItemHelpFont(s32 id, bool tagID) {
  Il2CppObject *v8;
  char *v9;
  char *v10;
  char *LocalizeText;
  s32 data;

  data = id;
  nowItemHelpID = id;
  v8 = Box(s32, &data);
  v9 = Format("{0:d4}", v8, 0);
  v10 = Concat_54766928("ITEMHELP_L", v9, 0);
  if (!tagID)
  {
    LocalizeText = GetLocalizeText(v10, 1);
    return sBtlGetItemHelpValue(id, LocalizeText);
  }
  return v10;
}

// 0x1fd7c00
char *sBtlGetItemHelpValue(s32 id, char *name) {
  s32 sklID;
  s32 v10;
  char *v11;

  if ((u32)(id - 512) <= 0xEF)
  {
    if (get_Item(sklItemConvTbl, id, 0))
    {
      sklID = get_Item(sklItemConvTbl, id, 0)->sklID;
      goto LABEL_10;
    }
    else
    {
      sklID = 0;
LABEL_10:
      v10 = sklID;
      v11 = name;
      return sBtlGetSkillHelpValue(v10, v11);
    }
    v10 = sklID;
    v11 = name;
    return sBtlGetSkillHelpValue(v10, v11);
  }
  return name;
}

// 0x1fd7d20
char *sBtlGetParHelpFont(s32 id, bool tagID) {
  Il2CppObject *v5;
  char *v6;
  char *v7;
  s32 data;

  data = id;
  v5 = Box(s32, &data);
  v6 = Format("{0:d4}", v5, 0);
  v7 = Concat_54766928("PARHELP_L", v6, 0);
  if (!tagID)
  {
    return GetLocalizeText(v7, 1);
  }
  return v7;
}

// 0x1fd7e20
void sBtlDrawItemName(s32 x, s32 y, s32 z, u32 rgba, s32 id) {
  ;
}

// 0x1fd7e30
char *sBtlGetAisyoNameFont(s32 id) {
  Il2CppObject *v3;
  char *v4;
  char *v5;
  s32 data;

  data = id;
  v3 = Box(s32, &data);
  v4 = Format("{0:d4}", v3, 0);
  v5 = Concat_54766928("AISYO_L", v4, 0);
  return GetLocalizeText(v5, 1);
}

// 0x1fd7f20
char *sBtlGetAisyoHelpFont(s32 id) {
  Il2CppObject *v3;
  char *v4;
  char *v5;
  s32 data;

  data = id;
  v3 = Box(s32, &data);
  v4 = Format("{0:d4}", v3, 0);
  v5 = Concat_54766928("AISYOHELP_L", v4, 0);
  return GetLocalizeText(v5, 1);
}

// 0x1fd8010
void sBtlDrawAisyoName(s32 x, s32 y, s32 z, u32 rgba, s32 id) {
  ;
}

// 0x1fd8020
char *sBtlGetWajutsuNameFont(s32 id) {
  return "test_wajutsu_namedata";
}

// 0x1fd8070
char *sBtlGetPlayerRankNameFont(s32 id) {
  return "test_prank_name";
}

// 0x1fd80c0
char *sBtlGetBSTNameFont(s32 id) {
  Il2CppObject *v3;
  char *v4;
  char *v5;
  s32 data;

  data = id;
  v3 = Box(s32, &data);
  v4 = Format("{0:d4}", v3, 0);
  v5 = Concat_54766928("BADST_L", v4, 0);
  return GetLocalizeText(v5, 1);
}

// 0x1fd81b0
void sBtlDrawBSTName(s32 x, s32 y, s32 z, u32 rgba, s32 id) {
  char *BSTNameFont;
  s32 v13;

  BSTNameFont = sBtlGetBSTNameFont(id);
  v13 = 8 * y + 15;
  if ((y & 0x10000000) == 0)
    v13 = 8 * y;
  sprDbgPrintStr(16 * x, 8 * y + (v13 >> 4), 0, rgba, BSTNameFont, 109, 24);
}

// 0x1fd82b0
void sBtlGetSkillMenu(SBTLUNIT_WORK *wk, u16 typeflg) {
  s32 v4;
  SBATTLE_WORK *v6;
  SKLID *v7;
  s32 v8;
  s64 i;
  s64 v10;
  s64 v11;
  SKLID *haveskill;
  u32 v14;
  s32 v15;
  s32 v17;
  s64 v19;
  s32 v20;
  s64 v22;
  s32 v23;
  s64 v25;
  s32 v26;
  s64 v28;
  s32 v29;
  s64 v31;
  s32 v32;
  s64 v34;
  s32 v35;
  s64 v37;
  s32 v38;
  s64 v40;
  s32 v41;
  s64 v43;
  s32 v44;
  s64 v47;

  v4 = typeflg;
  v6 = wk;
  v7 = NewSpecific(SKLID, 0xBu);
  v6->stock_useskill = v7;
  if (v4)
  {
    v8 = 0;
    for (i = 32; i != 76; i += 4)
    {
      v11 = *(u32 *)((char *)&wk->haveskill->obj.klass + i);
      if ((u32)v11 && (u32)v11 != 288)
      {
        if ((tbldata[v11]->type & (u16)v4) == 0)
        {
          v10 = (s64)wk->stock_useskill + 4 * v8++;
          *(u32 *)(v10 + 32) = *(u32 *)((char *)&wk->haveskill->obj.klass + i);
        }
      }
    }
  }
  else
  {
    haveskill = wk->haveskill;
    v14 = 0;
    v15 = haveskill[0];
    if (v15 && v15 != 288)
    {
      haveskill = wk->haveskill;
      v15 = haveskill[0];
      v14 = 1;
      wk->stock_useskill[0] = v15;
    }
    v17 = haveskill[1];
    if (v17 && v17 != 288)
    {
      haveskill = wk->haveskill;
      v17 = haveskill[1];
      v19 = (s64)wk->stock_useskill + 4 * v14++;
      *(u32 *)(v19 + 32) = v17;
    }
    v20 = haveskill[2];
    if (v20 && v20 != 288)
    {
      haveskill = wk->haveskill;
      v20 = haveskill[2];
      v22 = (s64)wk->stock_useskill + 4 * v14++;
      *(u32 *)(v22 + 32) = v20;
    }
    v23 = haveskill[3];
    if (v23 && v23 != 288)
    {
      haveskill = wk->haveskill;
      v23 = haveskill[3];
      v25 = (s64)wk->stock_useskill + 4 * v14++;
      *(u32 *)(v25 + 32) = v23;
    }
    v26 = haveskill[4];
    if (v26 && v26 != 288)
    {
      haveskill = wk->haveskill;
      v26 = haveskill[4];
      v28 = (s64)wk->stock_useskill + 4 * v14++;
      *(u32 *)(v28 + 32) = v26;
    }
    v29 = haveskill[5];
    if (v29 && v29 != 288)
    {
      haveskill = wk->haveskill;
      v29 = haveskill[5];
      v31 = (s64)wk->stock_useskill + 4 * v14++;
      *(u32 *)(v31 + 32) = v29;
    }
    v32 = haveskill[6];
    if (v32 && v32 != 288)
    {
      haveskill = wk->haveskill;
      v32 = haveskill[6];
      v34 = (s64)wk->stock_useskill + 4 * v14++;
      *(u32 *)(v34 + 32) = v32;
    }
    v35 = haveskill[7];
    if (v35 && v35 != 288)
    {
      haveskill = wk->haveskill;
      v35 = haveskill[7];
      v37 = (s64)wk->stock_useskill + 4 * v14++;
      *(u32 *)(v37 + 32) = v35;
    }
    v38 = haveskill[8];
    if (v38 && v38 != 288)
    {
      haveskill = wk->haveskill;
      v38 = haveskill[8];
      v40 = (s64)wk->stock_useskill + 4 * v14++;
      *(u32 *)(v40 + 32) = v38;
    }
    v41 = haveskill[9];
    if (v41 && v41 != 288)
    {
      haveskill = wk->haveskill;
      v41 = haveskill[9];
      v43 = (s64)wk->stock_useskill + 4 * v14++;
      *(u32 *)(v43 + 32) = v41;
    }
    v44 = haveskill[10];
    if (v44 && v44 != 288)
    {
      v44 = wk->haveskill[10];
      wk->stock_useskill[v14] = v44;
    }
  }
  v47 = 32;
  wk->stock_skillnum = 0;
  do
  {
    if (!!*(u32 *)((char *)&wk->stock_useskill->obj.klass + v47))
      ++wk->stock_skillnum;
    v47 += 4;
  }
  while (v47 != 76);
}

// 0x1fbe6c0
DEVILDATA_WORK *sBtlGetDevilData(s32 id, s32 encountno) {
  s32 nowKiretsuIdx;
  s32 v6;
  s32 v7;
  s32 v8;
  SB_ENCOUNTPAC *EncountPac;
  s32 v11;
  Il2CppClass **v12;
  s32 v14;
  _BOOL4 v17;

  nowKiretsuIdx = fldGb->nowKiretsuIdx;
  v6 = nowKiretsuIdx;
  v7 = nowKiretsuIdx;
  v8 = nowKiretsuIdx;
  if (encountno == -1)
    encountno = wk->encountno;
  EncountPac = sBtlGetEncountPac(-1);
  if (encountno >= SLODWORD(EncountPac->max_length))
    v11 = 0;
  else
    v11 = encountno;
  v12 = &EncountPac->obj.klass + v11;
  v14 = *(&v12[4]->_1.byval_arg.bits + 1);
  v17 = (u32)(id - 400) < 0xFFFFFFC0 && (u32)(id - 76) < 0xFFFFFFB5 && id < 496;
  if ((v14 & 0x70000) == 0 && v8 != 53 && nowKiretsuIdx != 52 && v7 != 51 && v6 != 50)
    v17 = 0;
  return devil_tbldata[v17][id];
}

// 0x1fd87a0
void sBtlSetDevilDataInit(s32 index, void *tbl) {
  DEVILDATA_WORK **devil_tbldata_local;
  Il2CppClass *v7;
  Il2CppClass *v8;
  Il2CppClass **v9;
  s64 v10;
  s64 v11;
  s64 v12;
  DEVILDATA_WORK *v14;
  DEVILDATA_WORK *DEVILDATA;
  DEVILDATA_WORK *v16;
  DEVILDATA_WORK **v18;

  if (index)
  {
    goto LABEL_4;
  }
  v18 = NewSpecific(Project_DEVILDATA_WORK__, 2u);
  devil_tbldata = v18;
LABEL_4:
  devil_tbldata_local = devil_tbldata;
  v7 = NewSpecific(DEVILDATA_WORK, 0x220u);
  v8 = v7;
  v9 = &devil_tbldata_local->obj.klass + index;
  v10 = index;
  v9[4] = v8;
  v11 = 0;
  v12 = 32;
  do
  {
    v14 = devil_tbldata[v10];
    DEVILDATA = GetDEVILDATA(tbl, v11, 0);
    v16 = DEVILDATA;
    *(Il2CppClass **)((char *)&v14->obj.klass + v12) = v16;
    ++v11;
    v12 += 8;
  }
  while (v11 != 544);
}

// 0x1fd8970
void sBtlSetDevilHuumaItemInit(s32 index, void *tbl) {
  DEVIL_HUUMAITEM **devil_huumaitem_local;
  Il2CppClass *v7;
  Il2CppClass *v8;
  Il2CppClass **v9;
  s64 v10;
  s64 v11;
  s64 v12;
  DEVIL_HUUMAITEM *v14;
  DEVIL_HUUMAITEM *DEVILHUUMAITEM;
  DEVIL_HUUMAITEM *v16;
  DEVIL_HUUMAITEM **v18;

  if (index)
  {
    goto LABEL_4;
  }
  v18 = NewSpecific(Project_DEVIL_HUUMAITEM__, 2u);
  devil_huumaitem = v18;
LABEL_4:
  devil_huumaitem_local = devil_huumaitem;
  v7 = NewSpecific(DEVIL_HUUMAITEM, 0x1D0u);
  v8 = v7;
  v9 = &devil_huumaitem_local->obj.klass + index;
  v10 = index;
  v9[4] = v8;
  v11 = 0;
  v12 = 32;
  do
  {
    v14 = devil_huumaitem[v10];
    DEVILHUUMAITEM = GetDEVILHUUMAITEM(tbl, v11, 0);
    v16 = DEVILHUUMAITEM;
    *(Il2CppClass **)((char *)&v14->obj.klass + v12) = v16;
    ++v11;
    v12 += 8;
  }
  while (v11 != 464);
}

// 0x1fd8b40
DEVIL_HUUMAITEM *sBtlGetDevilHuumaItem(s32 id) {
  s32 DlcMapNo;

  DlcMapNo = sBtlGetDlcMapNo();
  return devil_huumaitem[DlcMapNo != 0][id - 80];
}

// 0x1fd8c30
bool sBtlCheckVerticalArea(const sdfVector4_t *pos0, const sdfVector4_t *rot, const sdfVector4_t *pos1, f32 area) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 *p_x;
  f32 *v16;
  f32 *v17;
  s32 v19;
  f32 *v23;
  f32 *v24;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 pos0a;
  f32 v35;
  f32 v36;
  sdfMatrix4_t v37;
  sdfMatrix4_t v38;
  f32 v39;
  sdfVector4_t v40;
  sdfVector4_t v41;
  sdfVector4_t v43;
  sdfVector4_t v44;
  sdfVector4_t v45;
  sdfVector4_t v46;

  w = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  v9 = pos0->w;
  v10 = pos0->z;
  v11 = pos0->y;
  v12 = pos0->x;
  p_x = &vf00.x;
  p_x[4] = v12;
  p_x[5] = v11;
  p_x[6] = v10;
  p_x[7] = v9;
  v16 = &vf00.x;
  v35 = v16[6];
  v36 = v16[4];
  pos0a = v16[7];
  v17 = &vf00.x;
  v17[4] = x;
  v17[5] = y;
  v17[6] = z;
  v17[7] = w;
  ToMatrix();
  v19 = (u8)byte_5756085;
  vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
  if (v19)
  {
    goto LABEL_13;
  }
  else
  {
    goto LABEL_13;
  }
LABEL_13:
  get_transpose(&v38, &mtx_A, 0);
  v37 = v38;
  vct_A = op_Multiply_60923920(&v37, vct_A, 0);
  sub_1949110(0);
  v23 = &vf00.x;
  v23[8] = v12;
  v23[9] = v11;
  v23[10] = v10;
  v23[11] = v9;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v24 = &vf00.x;
  v26 = v24[4];
  v27 = v24[6];
  v28 = v24[7];
  v43.z = v35;
  v43.x = v36;
  v43.y = 0.0;
  v43.w = pos0a;
  v45.y = 0.0;
  v45.x = v26;
  v45.z = v27;
  v45.w = v28;
  if (sBtlGetVerticalLength(v43, v45, v40) > v39)
    return 0;
  v44.z = v35;
  v44.x = v36;
  v44.y = 0.0;
  v44.w = pos0a;
  v46.y = 0.0;
  v46.x = v26;
  v46.z = v27;
  v46.w = v28;
  return sBtlCheckInner(v44, v46, v41, area);
}

// 0x1fd90e0
void sBtlGetVerticalVector(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *pos2) {
  f32 x;
  f32 w;
  f32 z;
  f32 y;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 *p_x;
  f32 *v15;
  f32 *v17;
  int32x2_t v19;
  int32x2_t v20;
  float32x2_t v21;
  float32x2_t v22;
  int32x2_t v24;
  int32x2_t v25;
  float32x2_t v26;
  float32x2_t v27;
  s64 v31;
  s64 v32;

  x = pos0->x;
  w = pos1->w;
  z = pos1->z;
  y = pos1->y;
  v8 = pos1->x;
  v9 = pos0->w;
  v10 = pos0->z;
  v11 = pos0->y;
  p_x = &vf00.x;
  p_x[4] = v8;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v15 = &vf00.x;
  v15[8] = x;
  v15[9] = v11;
  v15[10] = v10;
  v15[11] = v9;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  vct_C = vct_A;
  *(u64 *)&vct_B.x = v31;
  *(u64 *)&vct_B.z = v32;
  v17 = &vf00.x;
  v17[4] = x;
  v17[5] = v11;
  v17[6] = v10;
  v17[7] = v9;
  vct_B = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_B, (float32x4_t)vct_A);
  vct_A = vct_C;
  v19.n64_u64[0] = *(u64 *)&vct_A.y;
  v20.n64_u64[0] = *(u64 *)&vct_B.y;
  v21.n64_u32[0] = vdup_lane_s32(v20, 1).n64_u32[0];
  v22.n64_u32[0] = vdup_lane_s32(v19, 1).n64_u32[0];
  v21.n64_u32[1] = LODWORD(vct_B.x);
  v22.n64_u32[1] = LODWORD(vct_A.x);
  vct_A.z = (f32)(v22.n64_f32[1] * v20.n64_f32[0]) - (f32)(v21.n64_f32[1] * v19.n64_f32[0]);
  *(float32x2_t *)&vct_A.x = vsub_f32(vmul_f32(v19, v21), vmul_f32(v22, v20));
  vct_B = vct_A;
  vct_A = vct_C;
  v24.n64_u64[0] = *(u64 *)&vct_A.y;
  v25.n64_u64[0] = *(u64 *)&vct_B.y;
  v26.n64_u32[0] = vdup_lane_s32(v25, 1).n64_u32[0];
  v27.n64_u32[0] = vdup_lane_s32(v24, 1).n64_u32[0];
  v26.n64_u32[1] = LODWORD(vct_B.x);
  v27.n64_u32[1] = LODWORD(vct_A.x);
  vct_A.z = (f32)(v27.n64_f32[1] * v25.n64_f32[0]) - (f32)(v26.n64_f32[1] * v24.n64_f32[0]);
  *(float32x2_t *)&vct_A.x = vsub_f32(vmul_f32(v24, v26), vmul_f32(v27, v25));
  sub_1949110(0);
}

// 0x1fcd430
f32 sBtlGetVerticalLength(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *pos2) {
  f32 v4;
  f32 v5;
  f32 v6;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 *p_x;
  s64 v13;
  u64 v16;
  f32 z;
  f32 w;
  f32 x;
  f32 y;
  s64 v24;
  s64 v25;
  sdfVector4_t v26;

  z = pos0->z;
  w = pos0->w;
  x = pos0->x;
  y = pos0->y;
  v4 = pos1->y;
  v5 = pos1->x;
  v6 = pos1->w;
  v7 = pos1->z;
  pos1->z = v7;
  pos1->w = v6;
  v8 = pos1->w;
  v9 = v4;
  v10 = pos1->z;
  pos1->z = v10;
  v4 = v9;
  pos1->w = v8;
  v26.x = x;
  v26.y = y;
  pos1->x = v5;
  pos1->y = v4;
  v26.w = w;
  v26.z = z;
  sBtlGetVerticalVector(v26, pos1, pos2);
  p_x = &vf00.x;
  p_x[6] = z;
  p_x[7] = w;
  p_x[4] = x;
  p_x[5] = y;
  v13 = v25;
  *(u64 *)&vct_B.x = v24;
  *(u64 *)&vct_B.z = v13;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  vct_B = vct_A;
  v16 = vmul_f32(*(float32x2_t *)&vct_A.y, *(float32x2_t *)&vct_B.y).n64_u64[0];
  return *((f32 *)&v16 + 1) + (f32)((f32)(vct_A.x * vct_B.x) + *(f32 *)&v16);
}

// 0x1fd9620
f32 sBtlGetVerticalLength_Point(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *pos2) {
  f32 v4;
  f32 v5;
  f32 v6;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v12;
  f32 *p_x;
  s64 v14;
  f32 *v16;
  f32 v17;
  f32 v18;
  f32 z;
  f32 w;
  f32 x;
  f32 y;
  f32 v28;
  s64 v29;
  s64 v30;
  sdfVector4_t v31;

  z = pos0->z;
  w = pos0->w;
  x = pos0->x;
  y = pos0->y;
  v4 = pos1->y;
  v5 = pos1->x;
  v6 = pos1->w;
  v7 = pos1->z;
  pos1->z = v7;
  pos1->w = v6;
  v8 = pos1->w;
  v9 = v4;
  v10 = pos1->z;
  pos1->z = v10;
  v4 = v9;
  pos1->w = v8;
  v31.x = x;
  v31.y = y;
  pos1->x = v5;
  pos1->y = v4;
  v31.w = w;
  v31.z = z;
  sBtlGetVerticalVector(v31, pos1, pos2);
  v12 = *((f32 *)&v29 + 1);
  p_x = &vf00.x;
  p_x[6] = z;
  p_x[7] = w;
  p_x[4] = x;
  p_x[5] = y;
  v14 = v30;
  LODWORD(vct_B.x) = v29;
  vct_B.y = v12;
  *(u64 *)&vct_B.z = v14;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  vct_B = vct_A;
  v16 = &vf00.x;
  v17 = v16[6] * v16[10];
  v18 = (f32)(v16[4] * v16[8]) + (f32)(v16[5] * v16[9]);
  v28 = v17 + v18;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v28);
  LODWORD(vct_B.x) = v29;
  vct_B.y = v12;
  *(u64 *)&vct_B.z = v14;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  return v28;
}

// 0x1fd9ac0
void sBtlInitOutInPara(SBTLANIM_HOKAN *hwk, f32 para) {
  hwk->o_div = para;
  hwk->o_val = 0.0;
}

// 0x1fd9ad0
f32 sBtlCalcOutInPara(SBTLANIM_HOKAN *hwk) {
  f32 o_div;
  f32 result;
  f32 v4;

  o_div = hwk->o_div;
  if (o_div <= 0.0)
    return 1.0;
  result = 1.0;
  v4 = (f32)((f32)((f32)(o_div + -0.5) * hwk->o_val) + 1.0) / o_div;
  hwk->o_val = v4;
  if (v4 < 1.0)
    return v4;
  return result;
}

// 0x1fd9b20
void sBtlInitInOutPara(SBTLANIM_HOKAN *hwk, f32 time) {
  hwk->i_ttime = time;
  hwk->i_rtime = time;
  *(u64 *)&hwk->i_speed = 0;
  if (time != 0.0)
    hwk->i_accele = 1.0 / (f32)((f32)(time * time) * 0.25);
}

// 0x1fd9b60
f32 sBtlCalcInOutPara(SBTLANIM_HOKAN *hwk, f32 time) {
  f32 v3;
  f32 v4;
  f32 v5;
  f32 result;

  v3 = hwk->i_rtime - time;
  hwk->i_rtime = v3;
  if (v3 <= 0.0)
  {
    hwk->i_rtime = 0.0;
    return 1.0;
  }
  else
  {
    if (v3 >= (f32)(hwk->i_ttime * 0.5))
      v4 = hwk->i_accele * time;
    else
      v4 = -(f32)(hwk->i_accele * time);
    v5 = hwk->i_speed + v4;
    result = hwk->i_val + (f32)(v5 * time);
    hwk->i_speed = v5;
    hwk->i_val = result;
  }
  return result;
}

// 0x1fd9bc0
s16 sBtlGetPlayerLuck(void) {
  return sBtlGetPlayerData()->downluck;
}

// 0x1fd9be0
PLAYER_LUCK sBtlGetPlayerLuckStep(void) {
  sBtlGetPlayerData();
  return 3;
}

// 0x1fd9c00
s16 sBtlGetCorrectionParamLuck(void) {
  s16 *v1;

  v1 = NewSpecific(s16, 7u);
  InitializeArray_55364416(v1, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__CD2CCC901150130632D02FF2C482B718692D0311DCEBCEBE0BAAD20BE38A8A53, 0);
  sBtlGetPlayerData();
  return v1[3];
}

// 0x1fd9cb0
void sBtlPurificationPlayerLuck(void) {
  sBtlGetPlayerData()->downluck = 0;
  return;
}

// 0x1fd9d30
void sBtlSetPlayerLuck(s32 num) {
  sBtlGetPlayerData()->downluck = num;
}

// 0x1fd9d60
s32 sBtlUpdatePlayerLuck(s32 updown) {
  return 0;
}

// 0x1fd9d70
void sBtlDeadFlagOn(SBTLUNIT_WORK *wk) {
  ;
}

// 0x1fcecf0
f32 sBtlGetPosToDir(f32 _FromX, f32 _FromZ, f32 _ToX, f32 _ToZ) {
  long f64 v5;
  f32 result;

  *(f32 *)&v5 = ToX - FromX;
  result = sub_188E410(v5) * 57.29578;
  if (result < 0.0)
    return result + 360.0;
  return result;
}

// 0x1fd9d80
void sBtlGetPosToVec(f32 _FromX, f32 _FromY, f32 _FromZ, f32 _ToX, f32 _ToY, f32 _ToZ, f32 *_VX, f32 *_VY, f32 *_VZ) {
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;

  v10 = ToX - FromX;
  v11 = ToY - FromY;
  v12 = ToZ - FromZ;
  v13 = fabsf(sqrtf((f32)((f32)(v10 * v10) + (f32)(v11 * v11)) + (f32)(v12 * v12)));
  *VX = v10 / v13;
  *VY = v11 / v13;
  *VZ = v12 / v13;
}

// 0x1fd9dd0
f32 sBtlGetVecToDir(f32 _VX, f32 _VZ) {
  long f64 v4;
  f32 result;

  *(f32 *)&v4 = VX;
  result = sub_188E410(v4) * 57.29578;
  if (result < 0.0)
    return result + 360.0;
  return result;
}

// 0x1fd9e60
void sBtlGetDirToVec(f32 _Dir, f32 *_VX, f32 *_VZ) {
  sdfVector3_t v6;
  sdfQuaternion_t v7;
  sdfVector3_t v8;

  v8.z = 0.0;
  v8.y = Dir * 0.017453292;
  v8.x = 0.0;
  v7 = Internal_FromEulerRad(v8, 0);
  v6 = op_Multiply_60935616(v7, forwardVector, 0);
  *VX = v6.x;
  *VZ = v6.z;
}

// 0x1fd9f20
f32 sBtlGetMag(f32 _VX, f32 _VZ) {
  return fabsf(sqrtf((f32)(VX * VX) + (f32)(VZ * VZ)));
}

// 0x1fcee60
f32 sBtlGetAtoB_LR(f32 a, f32 b) {
  _BOOL4 v3;
  f32 v4;
  f32 v5;

  v3 = a < 0.0;
  if (b < 0.0)
    v3 = 1;
  if (v3)
  {
    a = a + 360.0;
    b = b + 360.0;
  }
  if (a == INFINITY)
    v4 = -128.0;
  else
    v4 = ((s32)a % 360);
  if (b == INFINITY)
    v5 = -128.0;
  else
    v5 = ((s32)b % 360);
  if ((f32)(v4 - v5) > 180.0 || (f32)(v4 - v5) < -180.0)
  {
    if (v4 < v5)
      return v5 - (f32)(v4 + 360.0);
    v5 = v5 + 360.0;
  }
  return v5 - v4;
}

// 0x1fd9f40
f32 sBtlGetAtoB_LR_ABS(f32 a, f32 b) {
  _BOOL4 v5;
  f32 v6;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 result;

  v5 = a < 0.0;
  if (b < 0.0)
    v5 = 1;
  if (v5)
    v6 = b + 360.0;
  else
    v6 = b;
  if (v5)
    v7 = a + 360.0;
  else
    v7 = a;
  if (v7 == INFINITY)
    v8 = -128.0;
  else
    v8 = ((s32)v7 % 360);
  v9 = ((s32)v6 % 360);
  if (v6 == INFINITY)
    v9 = -128.0;
  if ((f32)(v8 - v9) > 180.0 || (f32)(v8 - v9) < -180.0)
  {
    if (v8 >= v9)
      v9 = v9 + 360.0;
    else
      v8 = v8 + 360.0;
  }
  result = v9 - v8;
  if (result < 0.0)
    return -result;
  return result;
}

// 0x1fda090
f32 sBtlGetDir_PosDirToPos(f32 _FromX, f32 _FromZ, f32 aDirFrom, f32 _ToX, f32 _ToZ) {
  long f64 v9;
  f32 v10;
  f32 v11;
  _BOOL4 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 result;

  *(f32 *)&v9 = ToX - FromX;
  v10 = sub_188E410(v9) * 57.29578;
  if (v10 < 0.0)
    v10 = v10 + 360.0;
  if (v10 <= 360.0)
    v11 = v10;
  else
    v11 = v10 + -360.0;
  v13 = aDirFrom < 0.0;
  if (v11 < 0.0)
    v13 = 1;
  if (v13)
    v14 = v11 + 360.0;
  else
    v14 = v11;
  if (v13)
    v15 = aDirFrom + 360.0;
  else
    v15 = aDirFrom;
  if (v15 == INFINITY)
    v16 = -128.0;
  else
    v16 = ((s32)v15 % 360);
  v17 = ((s32)v14 % 360);
  if (v14 == INFINITY)
    v17 = -128.0;
  if ((f32)(v16 - v17) > 180.0 || (f32)(v16 - v17) < -180.0)
  {
    if (v16 >= v17)
      v17 = v17 + 360.0;
    else
      v16 = v16 + 360.0;
  }
  result = v17 - v16;
  if (result < 0.0)
    return -result;
  return result;
}

// 0x1fda080
f32 sBtlGetABS(f32 a) {
  if (a < 0.0)
    return -a;
  return a;
}

// 0x1fda280
s32 GetABS(s32 a) {
  if (a < 0)
    return -a;
  return a;
}

// 0x1fda290
s32 sBtlGetCeilToInt(f32 a, f32 b) {
  f32 v3;

  v3 = (f32)((f32)((f32)(a * 100.0) + (f32)(b * 100.0)) + -1.0) / (f32)(b * 100.0);
  if (v3 == INFINITY)
    return 0x80000000;
  else
    return (s32)v3;
}

// 0x1fced30
f32 sBtlGetRotToDir(const sdfVector4_t *rot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  f32 result;

  w = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  result = (f32)(EulerAngleAxisY() * -57.29578) + 180.0;
  if (result >= 360.0)
    result = result + -360.0;
  if (result < 0.0)
    return result + 360.0;
  return result;
}

// 0x1fda2d0
void sBtlGetRotToVector(const sdfVector4_t *rot, sdfVector4_t *_Vec) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  f32 v11;
  f32 v12;
  s64 v13;
  s64 v14;
  s64 v15;

  w = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v11 = EulerAngleAxisY();
  v12 = sub_188E3D0(v11);
  Vec->y = 0.0;
  Vec->x = -v12;
  Vec->z = sub_188E3C0(v13, v14, v15);
  Vec->w = 0.0;
}

// 0x1fcef70
f32 sBtlGetDir180(f32 dir) {
  f32 result;

  result = dir + 180.0;
  if (result >= 360.0)
    result = result + -360.0;
  if (result < 0.0)
    return result + 360.0;
  return result;
}

// 0x1fda3f0
f32 sBtlGetDirZ180(f32 dir) {
  f32 result;

  result = (f32)(360.0 - dir) + 180.0;
  if (result >= 360.0)
    result = result + -360.0;
  if (result < 0.0)
    return result + 360.0;
  return result;
}

// 0x1fda430
f32 sBtlGetLenXZ(f32 _FromX, f32 _FromZ, f32 _ToX, f32 _ToZ) {
  return fabsf(sqrtf((f32)((f32)(ToX - FromX) * (f32)(ToX - FromX)) + (f32)((f32)(ToZ - FromZ) * (f32)(ToZ - FromZ))));
}

// 0x1fda450
f32 sBtlGetLenXYZ(f32 _FromX, f32 _FromY, f32 _FromZ, f32 _ToX, f32 _ToY, f32 _ToZ) {
  return fabsf(sqrtf((f32)((f32)((f32)(ToX - FromX) * (f32)(ToX - FromX)) + (f32)((f32)(ToY - FromY) * (f32)(ToY - FromY))) + (f32)((f32)(ToZ - FromZ) * (f32)(ToZ - FromZ))));
}

// 0x1fda480
f32 GetLenXYZ(const sdfVector3_t *_FromXYZ, const sdfVector3_t *_ToXYZ) {
  return fabsf(sqrtf((f32)((f32)(ToXYZ->z - FromXYZ->z) * (f32)(ToXYZ->z - FromXYZ->z)) + (f32)((f32)((f32)(ToXYZ->x - FromXYZ->x) * (f32)(ToXYZ->x - FromXYZ->x)) + (f32)((f32)(ToXYZ->y - FromXYZ->y) * (f32)(ToXYZ->y - FromXYZ->y)))));
}

// 0x1fcef40
f32 sBtlGet360(f32 a) {
  if (a > 360.0)
    a = a + -360.0;
  if (a < 0.0)
    return a + 360.0;
  return a;
}

// 0x1fda4b0
void sBtlGetMoveXZ(f32 _FromX, f32 _FromZ, f32 _Dir, f32 _Len, f32 *_ToX, f32 *_ToZ) {
  f32 v12;
  s64 v13;
  s64 v14;
  s64 v15;
  f32 v16;

  v12 = sub_188E3D0(Dir * 0.017453292) * Len;
  v16 = sub_188E3C0(v13, v14, v15);
  *ToX = v12 + FromX;
  *ToZ = (f32)(v16 * Len) + FromZ;
}

// 0x1fda530
void sBtlGetMovePosToPos(f32 _FromX, f32 _FromZ, f32 _ToX, f32 _ToZ, f32 _Len, f32 *_GetX, f32 *_GetZ) {
  long f64 v14;
  f32 v15;
  f32 v16;
  s64 v17;
  s64 v18;
  s64 v19;
  f32 v20;

  *(f32 *)&v14 = ToX - FromX;
  v15 = sub_188E410(v14) * 57.29578;
  if (v15 < 0.0)
    v15 = v15 + 360.0;
  v16 = sub_188E3D0(v15 * 0.017453292) * Len;
  v20 = sub_188E3C0(v17, v18, v19);
  *GetX = v16 + FromX;
  *GetZ = (f32)(v20 * Len) + FromZ;
}

// 0x1fda630
void GetMovePosToPos(f32 _FromX, f32 _FromY, f32 _FromZ, f32 _ToX, f32 _ToY, f32 _ToZ, f32 _Len, f32 *_GetX, f32 *_GetY, f32 *_GetZ) {
  f32 v21;

  v21 = fabsf(sqrtf((f32)((f32)((f32)(ToX - FromX) * (f32)(ToX - FromX)) + (f32)((f32)(ToY - FromY) * (f32)(ToY - FromY))) + (f32)((f32)(ToZ - FromZ) * (f32)(ToZ - FromZ))));
  *GetX = (f32)((f32)((f32)(ToX - FromX) / v21) * Len) + FromX;
  *GetY = (f32)((f32)((f32)(ToY - FromY) / v21) * Len) + FromY;
  *GetZ = (f32)((f32)((f32)(ToZ - FromZ) / v21) * Len) + FromZ;
}

// 0x1fda730
void sBtlGetMovePosToVec(f32 _FromX, f32 _FromY, f32 _FromZ, f32 _VX, f32 _VY, f32 _VZ, f32 _Len, f32 *_GetX, f32 *_GetY, f32 *_GetZ) {
  *GetX = (f32)(VX * Len) + FromX;
  *GetY = (f32)(VY * Len) + FromY;
  *GetZ = (f32)(VZ * Len) + FromZ;
}

// 0x1fda760
void sBtlGetNormalPosToPos(f32 _FromX, f32 _FromY, f32 _FromZ, f32 _ToX, f32 _ToY, f32 _ToZ, f32 _Nml, f32 *_GetX, f32 *_GetY, f32 *_GetZ) {
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  bool v15;
  f32 v16;

  v11 = 1.0;
  v12 = ToX - FromX;
  v13 = ToY - FromY;
  v14 = ToZ - FromZ;
  if (Nml <= 1.0)
    v11 = Nml;
  v15 = Nml < 0.0;
  v16 = 0.0;
  if (!v15)
    v16 = v11;
  *GetX = (f32)(v12 * v16) + FromX;
  *GetY = (f32)(v13 * v16) + FromY;
  *GetZ = (f32)(v14 * v16) + FromZ;
}

// 0x1fda7b0
f32 sBtlGetDir_Hokan(f32 nowdir, f32 goaldir, f32 rotspeed) {
  _BOOL4 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v13;

  v7 = nowdir < 0.0;
  if (goaldir < 0.0)
    v7 = 1;
  if (v7)
    v8 = goaldir + 360.0;
  else
    v8 = goaldir;
  if (v7)
    v9 = nowdir + 360.0;
  else
    v9 = nowdir;
  if (v9 == INFINITY)
    v10 = -128.0;
  else
    v10 = ((s32)v9 % 360);
  v11 = ((s32)v8 % 360);
  if (v8 == INFINITY)
    v11 = -128.0;
  if ((f32)(v10 - v11) <= 180.0 && (f32)(v10 - v11) >= -180.0)
  {
LABEL_25:
    v13 = v11 - v10;
    if (v13 < 0.0)
      goto LABEL_26;
    goto LABEL_30;
  }
  if (v10 < v11)
  {
    v10 = v10 + 360.0;
    goto LABEL_25;
  }
  v13 = (f32)(v11 + 360.0) - v10;
  if (v13 < 0.0)
  {
LABEL_26:
    if ((f32)-v13 > rotspeed)
      return nowdir - rotspeed;
    return goaldir;
  }
LABEL_30:
  if (v13 <= rotspeed)
    return goaldir;
  return nowdir + rotspeed;
}

// 0x1fda940
f32 sBtlGetDir_Hokan_Mul(f32 nowdir, f32 goaldir, f32 min, f32 mul) {
  _BOOL4 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;

  v8 = nowdir < 0.0;
  if (goaldir < 0.0)
    v8 = 1;
  if (v8)
    v9 = goaldir + 360.0;
  else
    v9 = goaldir;
  if (v8)
    v10 = nowdir + 360.0;
  else
    v10 = nowdir;
  if (v10 == INFINITY)
    v11 = -128.0;
  else
    v11 = ((s32)v10 % 360);
  v12 = ((s32)v9 % 360);
  if (v9 == INFINITY)
    v12 = -128.0;
  if ((f32)(v11 - v12) > 180.0 || (f32)(v11 - v12) < -180.0)
  {
    if (v11 >= v12)
      v12 = v12 + 360.0;
    else
      v11 = v11 + 360.0;
  }
  return (f32)((f32)(v12 - v11) * mul) + nowdir;
}

// 0x1fdaa90
f32 sBtlGetDirY(f32 _Len, f32 _Y) {
  f32 result;

  result = 0.0;
  if (Len != 0.0)
    return (f32)(sub_188E430(Y / Len) * 180.0) / 3.1415927;
  return result;
}

// 0x1fdaae0
void GetDirToVec(f32 _Dir, f32 _DirY, sdfVector3_t *_Vec) {
  f32 v4;
  sdfQuaternion_t v6;
  sdfVector3_t v7;

  v4 = DirY * -0.017453292;
  v7.z = 0.0;
  v7.y = Dir * 0.017453292;
  v7.x = v4;
  v6 = Internal_FromEulerRad(v7, 0);
  *Vec = op_Multiply_60935616(v6, forwardVector, 0);
}

// 0x1fdabb0
s32 sBtlGetLineCircle(f32 _FromX, f32 _FromZ, f32 _ToX, f32 _ToZ, f32 _CX, f32 _CZ, f32 _CR, f32 *_HitX1, f32 *_HitZ1, f32 *_HitX2, f32 *_HitZ2) {
  f32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  long f64 v29;
  s64 v30;
  s64 v31;
  s64 v32;
  f32 v33;
  s32 result;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  s64 v39;
  s64 v40;
  s64 v41;
  f32 v42;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 v46;
  s64 v47;
  s64 v48;
  s64 v49;
  f32 v50;

  v23 = ToZ - FromZ;
  v24 = FromX - ToX;
  v25 = (f32)-(f32)(v23 * FromX) - (f32)(v24 * FromZ);
  v26 = v25 + (f32)((f32)(v23 * CX) + (f32)(v24 * CZ));
  v27 = v26 / fabsf(sqrtf((f32)(v24 * v24) + (f32)(v23 * v23)));
  if (v27 >= 0.0)
    v28 = v27;
  else
    v28 = -v27;
  *(f32 *)&v29 = v24;
  v33 = sub_188E410(v29);
  if (v28 <= CR)
  {
    v36 = v33;
    if (v28 == CR)
    {
      if (v26 > 0.0)
        v36 = v33 + 3.14;
      v37 = (f32)(sub_188E3C0(v30, v31, v32) * CR) + CX;
      v38 = sub_188E3D0(v36);
      *HitX1 = v37;
      result = 1;
      *HitZ1 = (f32)(v38 * CR) + CZ;
      *HitX2 = 0.0;
      v35 = 0.0;
    }
    else
    {
      v42 = sub_188E3F0(v28 / CR);
      v43 = v36 - v42;
      v44 = v36 + v42;
      if (v26 <= 0.0)
        v45 = v43;
      else
        v45 = v43 + 3.14;
      if (v26 <= 0.0)
        v46 = v44;
      else
        v46 = v44 + 3.14;
      *HitX1 = (f32)(sub_188E3C0(v39, v40, v41) * CR) + CX;
      *HitZ1 = (f32)(sub_188E3D0(v45) * CR) + CZ;
      *HitX2 = (f32)(sub_188E3C0(v47, v48, v49) * CR) + CX;
      v50 = sub_188E3D0(v46);
      result = 2;
      v35 = (f32)(v50 * CR) + CZ;
    }
  }
  else
  {
    result = 0;
    *HitX1 = 0.0;
    v35 = 0.0;
    *HitZ1 = 0.0;
    *HitX2 = 0.0;
  }
  *HitZ2 = v35;
  return result;
}

// 0x1fdadb0
f32 sBtlGetRandomRange(f32 _A, f32 _B) {
  if (A >= B)
    return Range(B, A, 0);
  else
    return Range(A, B, 0);
}

// 0x1fdade0
bool sBtlRaycast_PS2(f32 _SX, f32 _SY, f32 _SZ, f32 _EX, f32 _EY, f32 _EZ, s32 _LayerMask, void *_Hit, f32 *_HitX, f32 *_HitY, f32 *_HitZ) {
  f32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 x;
  f32 y;
  f32 z;
  bool v42;
  __int128 v43;
  bool v44;
  f32 v45;
  f32 v47;
  UnityEngine_Ray_o v48;
  UnityEngine_RaycastHit_o v49;
  f32 v50;
  f32 v51;

  v47 = EX;
  v50 = EY;
  v51 = EZ;
  memset(&v49, 0, sizeof(v49));
  v23 = SX / -100.0;
  v24 = SY / -100.0;
  v25 = SZ / -100.0;
  v26 = EX / -100.0;
  v27 = EY / -100.0;
  v28 = EZ / -100.0;
  v29 = v26 - v23;
  v30 = v27 - v24;
  v31 = v28 - v25;
  v32 = fabsf(sqrtf((f32)((f32)(v29 * v29) + (f32)(v30 * v30)) + (f32)(v31 * v31)));
  v33 = v29 / v32;
  v34 = v30 / v32;
  v35 = v31 / v32;
  v36 = sqrtf((f32)(v35 * v35) + (f32)((f32)(v33 * v33) + (f32)(v34 * v34)));
  if (v36 > 0.00001)
  {
    x = v33 / v36;
    y = v34 / v36;
    z = v35 / v36;
    goto LABEL_16;
  }
  x = zeroVector.x;
  y = zeroVector.y;
  z = zeroVector.z;
LABEL_16:
  v48.m_Origin.x = v23;
  v48.m_Origin.y = v24;
  v48.m_Origin.z = v25;
  v48.m_Direction.x = x;
  v48.m_Direction.y = y;
  v48.m_Direction.z = z;
  v42 = Raycast_61463616(&v48, &v49, v32, LayerMask, 0);
  v43 = *(_OWORD *)&v49.m_Normal.y;
  v44 = v42;
  *(_OWORD *)&Hit->m_Point.x = *(_OWORD *)&v49.m_Point.x;
  *(_OWORD *)&Hit->m_Normal.y = v43;
  *(_OWORD *)&Hit->m_Distance = *(_OWORD *)&v49.m_Distance;
  if (v42)
  {
    *HitX = get_point(&v49, 0).x * -100.0;
    *HitY = get_point(&v49, 0).y * -100.0;
    v45 = COERCE_FLOAT(LODWORD(get_point(&v49, 0).z)) * -100.0;
  }
  else
  {
    *HitX = v47;
    *HitY = v50;
    v45 = v51;
  }
  *HitZ = v45;
  return v44;
}

// 0x1fdb080
bool sBtlRaycastAll_PS2(f32 _SX, f32 _SY, f32 _SZ, f32 _EX, f32 _EY, f32 _EZ, s32 _LayerMask, void **_Hits) {
  f32 v17;
  f32 v18;
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
  f32 v29;
  f32 v30;
  f32 x;
  f32 y;
  f32 z;
  void *v36;
  UnityEngine_Ray_o v38;

  v17 = SX / -100.0;
  v18 = SY / -100.0;
  v19 = SZ / -100.0;
  v20 = EX / -100.0;
  v21 = EY / -100.0;
  v22 = EZ / -100.0;
  v23 = v20 - v17;
  v24 = v21 - v18;
  v25 = v22 - v19;
  v26 = fabsf(sqrtf((f32)((f32)(v23 * v23) + (f32)(v24 * v24)) + (f32)(v25 * v25)));
  v27 = v23 / v26;
  v28 = v24 / v26;
  v29 = v25 / v26;
  v30 = sqrtf((f32)(v29 * v29) + (f32)((f32)(v27 * v27) + (f32)(v28 * v28)));
  if (v30 <= 0.00001)
  {
    x = zeroVector.x;
    y = zeroVector.y;
    z = zeroVector.z;
  }
  else
  {
    x = v27 / v30;
    y = v28 / v30;
    z = v29 / v30;
  }
  v38.m_Origin.x = v17;
  v38.m_Origin.y = v18;
  v38.m_Origin.z = v19;
  v38.m_Direction.x = x;
  v38.m_Direction.y = y;
  v38.m_Direction.z = z;
  v36 = RaycastAll_61466384(&v38, v26, LayerMask, 0);
  *Hits = v36;
  return (*Hits)->max_length != 0;
}

// 0x1fdb290
bool sBtlRaycastInside_PS2(f32 _SX, f32 _SY, f32 _SZ, s32 _LayerMask, void **_HitColliders) {
  void *v11;
  sdfVector3_t v13;

  v13.z = SZ / -100.0;
  v13.y = SY / -100.0;
  v13.x = SX / -100.0;
  v11 = OverlapSphere_61471088(v13, 0.1, LayerMask, 0);
  *HitColliders = v11;
  return (*HitColliders)->max_length != 0;
}

// 0x1fcefb0
void sBtlDrawLine_PS2(f32 _SX, f32 _SY, f32 _SZ, f32 _EX, f32 _EY, f32 _EZ, u32 _RGBA) {
  ;
}

// 0x1fdb360
void sBtlDrawLine_Unity(f32 _SX, f32 _SY, f32 _SZ, f32 _EX, f32 _EY, f32 _EZ, u32 _RGBA) {
  ;
}

// 0x1fdb370
void sBtlDrawLineX_PS2(f32 _CX, f32 _CY, f32 _CZ, f32 _Size, u32 _RGBA) {
  ;
}

// 0x1fdb380
void sBtlDrawLineX_Unity(f32 _CX, f32 _CY, f32 _CZ, f32 _Size, u32 _RGBA) {
  ;
}
