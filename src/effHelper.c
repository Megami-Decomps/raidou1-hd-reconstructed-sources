#include "types.h"
#include "dds3kerneldraw.h"
#include "eff.h"
#include "effbehavior.h"
#include "effhelper.h"
#include "effmodel.h"
#include "effparts.h"
#include "effpartslist.h"
#include "mdl.h"
#include "sdf_vu0.h"
#include "sdfbase.h"
#include "sdfmodel.h"
#include "sdfquat.h"
#include "tneffect_model.h"

typedef struct Standard Standard;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct ehlpHandle_t ehlpHandle_t;

static sdfVector4_t q;

// 0x19767d0
ehlpHandle_t *Create(Standard *pParts) {
  ehlpHandle_t *v3;
  u8 *v4;
  sdfBinary *v5;
  effHelper_Params_t *v6;
  void *v8;
  s64 naturalAligment;
  dds3ModelHandle_t *v11;
  dds3ModelHandle_t *v12;
  dds3ModelHandle_t *v13;
  s32 MarkPosCount;
  dds3ModelHandle_t *v15;
  s32 v17;
  s32 v18;
  void *v19;
  void *v20;
  void *v21;
  s64 v22;
  u64 *v23;
  s64 v24;
  plistHandle_t *v25;
  plistHandle_t *v26;
  s32 v27;
  s64 v28;
  s64 v29;
  s64 v30;
  plistHandle_t *v31;
  plistHandle_t *v32;

  v3 = Allocate(ehlpHandle_t);
  v4 = effParamsGet(pParts);
  v5 = Allocate(sdfBinary);
  _ctor_36176832(v5, v4, 0);
  v6 = Allocate(effHelper_Params_t);
  _ctor_26700736(v6, v5);
  v3->pParams = v6;
  v8 = (pParts->param->pData->klass->vtable._4_GetExtResource.methodPtr)(pParts->param->pData, pParts->param->pData->klass->vtable._4_GetExtResource.method);
  if (v8)
  {
    if (v8->klass->_2.naturalAligment < (u32)naturalAligment || v8->klass->_2.typeHierarchy[naturalAligment - 1] != Project_libsdf_sdfResource)
    {
      goto LABEL_37;
    }
  }
  v11 = effHandleCreate(v8);
  v3->hModel = v11;
  v12 = &v3->hModel;
  v13 = v3->hModel;
  if (!mdlHasMotion(v12))
    goto LABEL_10;
  goto LABEL_9000;
  if (!mdlHasMotion(v13))
  {
LABEL_10:
    MarkPosCount = sdfModelGetMarkPosCount(*(sdfModelRootNode_t *)((u64)v3->hModel + 64));
    v3->number = MarkPosCount;
    if (!MarkPosCount)
      return v3;
    goto LABEL_21;
  }
LABEL_9000:
  v15 = v12;
  if (*(u32 *)((u64)v3->pParams + 32))
  {
    mdlSingleMotion(v15, 0, 0);
    v17 = sdfModelGetMarkPosCount(*(sdfModelRootNode_t *)((u64)v3->hModel + 64));
    v3->number = v17;
    if (!v17)
      return v3;
  }
  else
  {
    mdlLoopMotion(v15, 0, 0);
    v18 = sdfModelGetMarkPosCount(*(sdfModelRootNode_t *)((u64)v3->hModel + 64));
    v3->number = v18;
    if (!v18)
      return v3;
  }
LABEL_21:
  v19 = effDataGet(pParts);
  if (!v19)
    return v3;
  v20 = v19;
  v21 = NewSpecific(plistHandle_t, v3->number);
  v3->phPartsList = v21;
  v22 = &v3->phPartsList;
  v23 = v3->phPartsList;
  v8 = *(void *)((v20->klass->vtable._5_GetExtUnits.methodPtr)(v20, v20->klass->vtable._5_GetExtUnits.method) + 32);
  if (v8)
  {
    if (v8->klass->_2.naturalAligment < (u32)v24 || v8->klass->_2.typeHierarchy[v24 - 1] != plistHandle_t_Resource)
    {
LABEL_37:
    }
  }
  v25 = Create(v8, 0);
  v26 = v25;
  if (v25 && !QueryInterface(v25, *(void **)(*v23 + 64)))
    goto LABEL_35;
  v23[4] = v26;
  if (v3->number >= 2u)
  {
    v27 = 2;
    v28 = 1;
    while (1)
    {
      v30 = *(u64 *)v22;
      v31 = Copy(*(void *)(*(u64 *)v22 + 32));
      v32 = v31;
      if (v31)
      {
        if (!QueryInterface(v31, *(void **)(*(u64 *)v30 + 64)))
          break;
      }
      v29 = v30 + 8 * v28;
      *(u64 *)(v29 + 32) = v32;
      v28 = v27++;
      if (v28 >= v3->number)
        return v3;
    }
LABEL_35:
  }
  return v3;
}

// 0x1976e20
void Delete(effPartsHandle_t *handle) {
  effPartsHandle_t *klass;
  effPartsHandle_t *p_fields;
  effOption *v6;
  effOption *option;
  s64 v8;

  klass = handle[2].klass;
  if (klass)
  {
    mdlSetLight(klass, 0);
    Free(klass);
    handle[2].klass = 0;
  }
  option = handle[1].option;
  p_fields = &handle[1].fields;
  v6 = option;
  if (option)
  {
    if (SLODWORD(v6->adjustRGBA.x) >= 1)
    {
      v8 = 0;
      do
        effPartsDelete(*((void *)&v6->adjustRGBA.z + v8++));
      while (v8 < SLODWORD(v6->adjustRGBA.x));
    }
    p_fields->option = 0;
  }
}

// 0x1977000
ehlpHandle_t *Copy(effPartsHandle_t *handle) {
  effPartsHandle_t *v4;
  void *monitor;

  v4 = Allocate(ehlpHandle_t);
  _ctor(v4, 0);
  monitor = handle[1].monitor;
  v4[1].monitor = monitor;
  effResourceCopy(v4, handle);
  return (ehlpHandle_t *)v4;
}

// 0x19770e0
void effResourceCopy(effPartsHandle_t *dst, effPartsHandle_t *src) {
  dds3ModelHandle_t *v7;
  effPartsHandle_t *klass;
  effPartsHandle_t *v9;
  u16 MajorNum;
  s32 MinorNum;
  dds3ModelHandle_t *v12;
  effPartsHandle_t *v14;
  s32 MarkPosCount;
  effOption *option;
  effOption *v18;
  u32 v19;
  s64 v20;
  effOption *v21;
  s64 v22;
  s32 v23;
  effOption **v24;
  effOption *v25;
  plistHandle_t *v26;
  plistHandle_t *v27;

  v7 = &dst[2];
  klass = dst[2].klass;
  if (klass)
  {
    mdlSetLight(klass, 0);
    Free(klass);
  }
  v9 = src[2].klass;
  MajorNum = mdlGetMajorNum(v9);
  MinorNum = mdlGetMinorNum(src[2].klass);
  v12 = mdlLoad(MajorNum, MinorNum);
  v7 = v12;
  Init();
  if (mdlHasMotion(v7))
  {
    v14 = dst[2].klass;
    if (*((u32 *)dst[1].monitor + 8))
    {
      mdlSingleMotion(v14, 0, 0);
    }
    else
    {
      mdlLoopMotion(v14, 0, 0);
    }
  }
  MarkPosCount = sdfModelGetMarkPosCount(dst[2].klass->_1.element_class);
  option = src[1].option;
  LODWORD(dst[1].klass) = MarkPosCount;
  if (option)
  {
    v18 = dst[1].option;
    v19 = MarkPosCount;
    if (v18 && SLODWORD(v18->adjustRGBA.x) >= 1)
    {
      v20 = 0;
      do
        effPartsDelete(*((void *)&v18->adjustRGBA.z + v20++));
      while (v20 < SLODWORD(v18->adjustRGBA.x));
      v19 = dst[1].klass;
    }
    v21 = NewSpecific(plistHandle_t, v19);
    dst[1].option = v21;
    if (LODWORD(dst[1].klass))
    {
      v22 = 0;
      v23 = 1;
      do
      {
        v25 = dst[1].option;
        v26 = Copy(*(void *)&src[1].option->adjustRGBA.z);
        v27 = v26;
        v24 = &v25->klass + v22;
        v24[4] = (effOption *)v27;
        v22 = v23++;
      }
      while (v22 < LODWORD(dst[1].klass));
    }
  }
}

// 0x1977730
void Draw(effPartsHandle_t *handle) {
  effPartsHandle_t *klass;
  effPartsHandle_t *v7;
  f32 x;
  f32 v9;
  effPartsHandle_t *v10;
  u32 *monitor;
  dds3ModelHandle_t *v15;
  s32 v16;
  s32 klass_high;
  s64 klass_low;
  sdfModelRootNode_t *modelRoot;
  f32 v20;
  f32 v21;
  s64 v22;
  s32 v23;
  char *v24;
  char *v25;
  void **v26;
  void *v27;
  f32 v29;
  f32 y;
  f32 z;
  f32 w;
  _OWORD *p_x;
  __int128 v36;
  __int128 v37;
  void **v38;
  char *v39;
  char *v40;
  void *unity_user_data;
  bool v42;
  void *transform;
  f32 *v45;
  f32 v50;
  f32 v51;
  sdfVector4_t abgr_4;
  sdfMatrix4_t v53;
  sdfMatrix4_t v54;
  sdfVector3_t localPosition;
  sdfVector4_t v56;
  sdfVector4_t Color;
  sdfVector4_t Row;
  sdfVector4_t v59;
  sdfVector4_t v60;

  memset(&v54, 0, sizeof(v54));
  klass = handle[2].klass;
  mdlGetScale(handle[2].klass);
  v7 = handle[2].klass;
  x = vct_A.x;
  v9 = 0.0;
  if (!get_STOP(0))
    v9 = *((f32 *)handle[1].monitor + 9);
  mdlSetMotionSpeed(v7, v9);
  v10 = handle[2].klass;
  Link(v10, ModelOt[OT]);
  monitor = handle[1].monitor;
  v15 = handle[2].klass;
  v16 = monitor[8];
  klass_low = LODWORD(handle[1].klass);
  klass_high = HIDWORD(handle[1].klass);
  modelRoot = v15->modelRoot;
  if ((klass_high < v16 || !v16) && handle[1].option)
  {
    v56 = effColorAnimation(*((u64 *)monitor + 2), *((u64 *)monitor + 3), klass_high, v16);
    Color = mdlGetColor(v15);
    if ((u32)klass_low)
    {
      v20 = v56.z * Color.z;
      v21 = v56.y * Color.y;
      v22 = 0;
      v23 = 0;
      v24 = &byte_5756000;
      v25 = &byte_5756000;
      v26 = &eff;
      v50 = x;
      v51 = 1.0 / x;
      do
      {
        v27 = *((void *)&handle[1].option->adjustRGBA.z + v22);
        sdfModelGetMarkPosMatrix(modelRoot, v23);
        if (!v24[655])
        {
          v24[655] = 1;
          goto LABEL_27;
        }
LABEL_27:
        Row = GetRow(&mtx_A, 3, 0);
        v29 = Row.x;
        y = Row.y;
        z = Row.z;
        w = Row.w;
        if (x == 0.0)
        {
          goto LABEL_29;
        }
        vct_A = (struct sdfVector4_t)xmmword_3D06BB0;
        vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v51);
        sub_197D730(0);
LABEL_29:
        if (v25[142])
        {
          goto LABEL_31;
        }
        v25[142] = 1;
LABEL_31:
        p_x = &vf00.x;
        v36 = p_x[5];
        *(_OWORD *)&v54.m00 = p_x[4];
        *(_OWORD *)&v54.m01 = v36;
        v37 = p_x[7];
        *(_OWORD *)&v54.m02 = p_x[6];
        *(_OWORD *)&v54.m03 = v37;
        if (Row.x == 0.0 && Row.y == 0.0 && Row.z == 0.0 && modelRoot)
        {
          v38 = v26;
          v39 = v25;
          v40 = v24;
          unity_user_data = handle[2].klass->_1.element_class->_2.unity_user_data;
          v42 = op_Inequality(unity_user_data, 0, 0);
          v24 = v40;
          v25 = v39;
          v26 = v38;
          if (v42)
          {
            transform = get_transform(handle[2].klass->_1.element_class->_2.unity_user_data, 0);
            localPosition = get_localPosition(transform, 0);
            v26 = v38;
            v45 = &modVec.x;
            v21 = v56.y * Color.y;
            v20 = v56.z * Color.z;
            x = v50;
            y = Row.y + (f32)(localPosition.y * v45[4]);
            v29 = Row.x + (f32)(localPosition.x * v45[3]);
            z = Row.z + (f32)(localPosition.z * v45[5]);
            w = Row.w + 0.0;
          }
        }
        v60.x = v29;
        v60.y = y;
        v60.z = z;
        v60.w = w;
        effPartsPositionSet(v27, v60);
        if (!*((u32 *)*v26 + 56))
        v53 = v54;
        effMatrixToQuat(&v53);
        abgr_4 = q;
        vct_B = abgr_4;
        Mult();
        effPartsRotateSet(v27, vct_A);
        effPartsScaleSet(v27, x);
        v59.x = v56.x * Color.x;
        v59.y = v21;
        v59.z = v20;
        v59.w = v56.w * Color.w;
        ColorSet(v27, v59);
        effPartsDraw(v27);
        v22 = ++v23;
      }
      while (v23 < klass_low);
    }
  }
  if (!get_STOP(0))
    ++HIDWORD(handle[1].klass);
}

// 0x1977f20
void PositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  effPartsHandle_t *klass;

  w = pPos->w;
  z = pPos->z;
  y = pPos->y;
  x = pPos->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  if (!handle)
    goto LABEL_13;
  goto LABEL_11;
  if (!handle)
LABEL_11:
LABEL_13:
  klass = handle[2].klass;
  mdlSetPosition(klass);
}

// 0x1978090
void RotateSet(effPartsHandle_t *handle, const sdfVector4_t *pRot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  effPartsHandle_t *klass;

  w = pRot->w;
  z = pRot->z;
  y = pRot->y;
  x = pRot->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  if (!handle)
    goto LABEL_13;
  goto LABEL_11;
  if (!handle)
LABEL_11:
LABEL_13:
  klass = handle[2].klass;
  mdlSetRotate(klass);
}

// 0x1978200
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  effPartsHandle_t *klass;
  sdfVector4_t v10;

  w = abgr->w;
  z = abgr->z;
  y = abgr->y;
  x = abgr->x;
  klass = handle[2].klass;
  v10.z = z;
  v10.w = w;
  v10.x = x;
  v10.y = y;
  SetColor(klass, v10);
}

// 0x19782e0
void ScaleSet(effPartsHandle_t *handle, f32 scale) {
  s32 v6;
  effPartsHandle_t *klass;

  v6 = (u8)byte_575608A;
  vct_A = (struct sdfVector4_t)xmmword_3D06BB0;
  if (v6)
  {
    goto LABEL_7;
  }
  else
  {
LABEL_7:
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, scale);
    if (!handle)
      goto LABEL_17;
    goto LABEL_15;
  }
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, scale);
  if (!handle)
LABEL_15:
LABEL_17:
  klass = handle[2].klass;
  mdlSetScale(klass);
}
