#include "types.h"
#include "dds3kerneldraw.h"
#include "effmodel.h"
#include "effparts.h"
#include "mdl.h"
#include "sdf_vu0.h"
#include "sdfmotion.h"
#include "tneffect_model.h"

typedef struct Standard Standard;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct emdlHandle_t emdlHandle_t;

static u16 effModel_Minor;

// 0x19773e0
void Init(dds3ModelHandle_t *hModel) {
  _OWORD *p_x;

  p_x = &vf00.x;
  p_x[1] = *p_x;
  mdlSetPosition(hModel);
  vct_A = vf00;
  mdlSetRotate(hModel);
  vct_A = (struct sdfVector4_t)xmmword_3D06BB0;
  mdlSetScale(hModel);
  mdlSetColor(hModel, 0x80808080);
  if (mdlHasMotion(hModel))
  {
    mdlSingleMotion(hModel, 0, 0);
    mdlSetMotionSpeed(hModel, 1.0);
    goto LABEL_12;
  }
LABEL_12:
  mdlShow(hModel);
}

// 0x1976cf0
dds3ModelHandle_t *effHandleCreate(void *pData) {
  u16 effModel_Minor_local;
  dds3ModelResrc_t *v5;
  s32 v7;
  dds3ModelHandle_t *v8;

  effModel_Minor_local = effModel_Minor;
  while (1)
  {
    v5 = mdlSearchResrc(5u, effModel_Minor_local);
    v7 = effModel_Minor;
    if (!v5)
      break;
    effModel_Minor_local = v7 + 1;
    effModel_Minor = effModel_Minor_local;
  }
  mdlPackDecode(5u, v7, 257, pData, 0);
  v8 = mdlLoad(5u, effModel_Minor);
  Init();
  ++effModel_Minor;
  return v8;
}

// 0x1976f80
void effHandleFree(dds3ModelHandle_t *hModel) {
  mdlSetLight(hModel, 0);
  Free(hModel);
}

// 0x1978c10
dds3ModelHandle_t *effHandleCopy(dds3ModelHandle_t *hSrc) {
  u16 MajorNum;
  s32 MinorNum;
  dds3ModelHandle_t *v5;

  MajorNum = mdlGetMajorNum(hSrc);
  MinorNum = mdlGetMinorNum(hSrc);
  v5 = mdlLoad(MajorNum, MinorNum);
  Init();
  return v5;
}

// 0x1978cb0
emdlHandle_t *Create(Standard *pParts) {
  emdlHandle_t *v3;
  sdf3DLightParallelPacket_t *v4;
  u8 *v5;
  sdfBinary *v6;
  effModel_Params_t *v7;
  void *v8;
  s64 naturalAligment;
  void *klass;
  dds3ModelHandle_t *v13;
  f32 v15;
  dds3ModelHandle_t *v16;
  f32 v18;
  f32 v19;

  v3 = Allocate(emdlHandle_t);
  v4 = Allocate(sdf3DLightParallelPacket_t);
  _ctor(v4, 0);
  v3->pLightPacket = v4;
  if (pParts)
  {
    v5 = effParamsGet(pParts);
    v6 = Allocate(sdfBinary);
    _ctor_36176832(v6, v5, 0);
    v7 = Allocate(effModel_Params_t);
    v7->scale = ReadFloat(v6, 0);
    v3->param = v7;
    v8 = effDataGet(pParts);
    if (v8)
    {
      if (v8->klass->_2.naturalAligment >= (u32)naturalAligment && (Project_libsdf_sdfResourceUnit_Ext_c *)v8->klass->_2.typeHierarchy[naturalAligment - 1] == Project_libsdf_sdfResourceUnit_Ext)
      {
        klass = v8[1].klass;
        v13 = effHandleCreate(klass);
        v3->handle = v13;
        vct_A = (struct sdfVector4_t)xmmword_3D06BB0;
        v15 = *(f32 *)((u64)v3->param + 16);
        v18 = *(f32 *)((u64)v3->param + 16);
        v15 = v18;
        v19 = v15;
        v15 = v19;
        vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v15);
        v16 = v3->handle;
        mdlSetScale(v16);
        goto LABEL_22;
      }
    }
  }
LABEL_22:
  v3->index_motion = 0;
  return v3;
}

// 0x1979030
void Delete(effPartsHandle_t *handle) {
  dds3ModelHandle_t *monitor;

  monitor = handle[1].monitor;
  if (monitor)
  {
    mdlSetLight(monitor, 0);
    Free(monitor);
  }
}

// 0x1979120
emdlHandle_t *Copy(effPartsHandle_t *handle) {
  effPartsHandle_t *v4;
  effPartsHandle_t *klass;
  effModel_Params_t *v6;
  s32 name;

  v4 = Create(0);
  klass = handle[1].klass;
  v6 = Allocate(effModel_Params_t);
  name = klass->_1.name;
  v4[1].klass = (effPartsHandle_t *)v6;
  *(u32 *)&v6->scale = name;
  ResourceCopy(v4, handle);
  return (emdlHandle_t *)v4;
}

// 0x1979240
void ResourceCopy(effPartsHandle_t *dst, effPartsHandle_t *src) {
  u64 *p_monitor;
  dds3ModelHandle_t *monitor;
  dds3ModelHandle_t *v9;
  u16 MajorNum;
  s32 MinorNum;
  dds3ModelHandle_t *v12;
  f32 v15;
  f32 v16;

  p_monitor = &dst[1].monitor;
  monitor = dst[1].monitor;
  if (monitor)
  {
    mdlSetLight(monitor, 0);
    Free(monitor);
  }
  v9 = src[1].monitor;
  MajorNum = mdlGetMajorNum(v9);
  MinorNum = mdlGetMinorNum(src[1].monitor);
  v12 = mdlLoad(MajorNum, MinorNum);
  Init();
  vct_A = (struct sdfVector4_t)xmmword_3D06BB0;
  v15 = *(f32 *)&dst[1].klass->_1.name;
  v16 = *(f32 *)&dst[1].klass->_1.name;
  v15 = v16;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v15);
  mdlSetScale(v12);
  *p_monitor = v12;
}

// 0x19795e0
void Draw(effPartsHandle_t *handle) {
  dds3ModelHandle_t *monitor;
  effOption *option;
  dds3ModelHandle_t *v6;
  effOption *v7;
  dds3ModelHandle_t *v8;
  f32 v9;
  dds3ModelHandle_t *v10;

  monitor = handle[1].monitor;
  option = handle[1].option;
  if (PacketMake(monitor, option, 0))
  {
    v6 = handle[1].monitor;
    v7 = handle[1].option;
    mdlSetLight(v6, v7);
  }
  v8 = handle[1].monitor;
  if (get_STOP(0))
    v9 = 0.0;
  else
    v9 = 1.0;
  mdlSetMotionSpeed(v8, v9);
  v10 = handle[1].monitor;
  Link(v10, ModelOt[OT]);
}

// 0x19797b0
void PositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  dds3ModelHandle_t *monitor;

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
  monitor = handle[1].monitor;
  mdlSetPosition(monitor);
}

// 0x1979920
void RotateSet(effPartsHandle_t *handle, const sdfVector4_t *pRot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  dds3ModelHandle_t *monitor;

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
  monitor = handle[1].monitor;
  mdlSetRotate(monitor);
}

// 0x1979a90
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  dds3ModelHandle_t *monitor;
  sdfVector4_t v10;

  w = abgr->w;
  z = abgr->z;
  y = abgr->y;
  x = abgr->x;
  monitor = handle[1].monitor;
  v10.z = z;
  v10.w = w;
  v10.x = x;
  v10.y = y;
  SetColor(monitor, v10);
}

// 0x1979b70
void ScaleSet(effPartsHandle_t *handle, f32 scale) {
  f32 v6;
  f32 v7;
  int32x4_t v11;
  dds3ModelHandle_t *monitor;

  v6 = *(f32 *)&handle[1].klass->_1.name;
  v7 = v6 * scale;
  v11 = vzip1q_s32((int32x4_t)LODWORD(v7), (int32x4_t)LODWORD(v7));
  v11.n128_f32[2] = v7;
  vct_A = (struct sdfVector4_t)v11;
  monitor = handle[1].monitor;
  mdlSetScale(monitor);
}

// 0x1979cf0
emdlHandle_t *effCreate2(Standard *pParts) {
  emdlHandle_t *v3;
  u8 *v4;
  sdfBinary *v5;
  effModel2_Params_t *v6;
  dds3ModelHandle_t *handle;
  dds3ModelHandle_t *v8;

  v3 = Create(pParts);
  if (pParts)
  {
    v4 = effParamsGet(pParts);
    v5 = Allocate(sdfBinary);
    _ctor_36176832(v5, v4, 0);
    v6 = Allocate(effModel2_Params_t);
    v6->scale = ReadFloat(v5, 0);
    v6->flg = ReadU8(v5, 0) != 0;
    Align(v5, 4, 0);
    handle = v3->handle;
    if (!handle)
      goto LABEL_15;
    if (!mdlHasMotion(v3->handle))
      goto LABEL_15;
    goto LABEL_9000;
    if (!mdlHasMotion(handle))
    {
LABEL_15:
      v3->param = (effModel_Params_t *)v6;
      return v3;
    }
LABEL_9000:
    if (!v6->flg)
    {
      v8 = v3->handle;
      mdlLoopMotion(v8, 0, 0);
    }
    goto LABEL_15;
  }
  return v3;
}

// 0x1979ef0
emdlHandle_t *effCopy2(effPartsHandle_t *handle) {
  effPartsHandle_t *v4;
  effPartsHandle_t *klass;
  Il2CppObject *v6;
  Il2CppObject *v7;
  s32 name;

  v4 = Create(0);
  klass = handle[1].klass;
  v6 = Allocate(effModel2_Params_t);
  v7 = v6;
  _ctor(v6, 0);
  name = klass->_1.name;
  BYTE4(v7[1].klass) = BYTE4(klass->_1.name);
  LODWORD(v7[1].klass) = name;
  v4[1].klass = (effPartsHandle_t *)v7;
  effResourceCopy2(v4, handle);
  return (emdlHandle_t *)v4;
}

// 0x197a0b0
void effResourceCopy2(effPartsHandle_t *dst, effPartsHandle_t *src) {
  s64 naturalAligment;
  s64 v6;
  dds3ModelHandle_t *monitor;
  u8 *klass;
  s64 v9;
  dds3ModelHandle_t *v10;

  ResourceCopy(dst, src);
  if (src)
  {
    if (src->klass->_2.naturalAligment < (u32)v6 || src->klass->_2.typeHierarchy[v6 - 1] != emdlHandle_t)
    {
      klass = src;
      goto LABEL_23;
    }
  }
  monitor = dst[1].monitor;
  if (!mdlHasMotion(dst[1].monitor))
    return;
  klass = src[1].klass;
  if (klass)
  {
    if (*(u8 *)(*(u64 *)klass + 304) < (u32)v9 || *(effModel2_Params_t **)(*(u64 *)(*(u64 *)klass + 200) + 8 * v9 - 8) != effModel2_Params_t)
    {
LABEL_23:
    }
  }
  if (!klass[20])
  {
    v10 = dst[1].monitor;
    mdlLoopMotion(v10, 0, 0);
  }
}

// 0x197a250
void effReset2(effPartsHandle_t *handle) {
  s64 naturalAligment;
  dds3ModelHandle_t *monitor;
  u8 *klass;
  s64 v6;
  dds3ModelHandle_t *v7;

  if (handle)
  {
    if (handle->klass->_2.naturalAligment < (u32)naturalAligment || handle->klass->_2.typeHierarchy[naturalAligment - 1] != emdlHandle_t)
    {
      klass = handle;
      goto LABEL_21;
    }
  }
  sdfMotionSeek(*((sdfMotionCtrlr_t *)handle[1].monitor + 9), 0.0);
  monitor = handle[1].monitor;
  if (!mdlHasMotion(handle[1].monitor))
    return;
  klass = handle[1].klass;
  if (klass)
  {
    if (*(u8 *)(*(u64 *)klass + 304) < (u32)v6 || *(effModel2_Params_t **)(*(u64 *)(*(u64 *)klass + 200) + 8 * v6 - 8) != effModel2_Params_t)
    {
LABEL_21:
    }
  }
  v7 = handle[1].monitor;
  if (klass[20])
  {
    mdlSingleMotion(v7, 0, 0);
  }
  else
  {
    mdlLoopMotion(v7, 0, 0);
  }
}
