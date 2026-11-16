#include "types.h"
#include "dds3billboard.h"
#include "effmuzzleflash.h"
#include "effparts.h"
#include "sdf_vu0.h"
#include "sdfquat.h"

typedef struct Standard Standard;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct mzfHandle_t mzfHandle_t;

static sdfVector4_t v;

// 0x197a410
mzfHandle_t *Create(Standard *pParts) {
  mzfHandle_t *v3;
  sdfVector4_t *v7;
  sdfVector4_t *v8;
  u8 *v11;
  sdfBinary *v12;
  effMuzzleFlash_Params_t *v13;
  f32 Float;
  s32 point;
  void *v16;
  void *v17;
  dds3Billboard_Basic_t *v18;

  v3 = Allocate(mzfHandle_t);
  v3->frame = 0;
  *(u32 *)&v3->scale = 1065353216;
  v3->abgr = oneVector;
  v7 = &v3->pos;
  *v7 = vf00;
  v8 = &v3->rot;
  *v8 = vf00;
  if (!pParts)
    return v3;
  v11 = effParamsGet(pParts);
  v12 = Allocate(sdfBinary);
  _ctor_36176832(v12, v11, 0);
  v13 = Allocate(effMuzzleFlash_Params_t);
  v13->scale_h = ReadFloat(v12, 0);
  Float = ReadFloat(v12, 0);
  point = v12->point;
  v3->param = v13;
  v13->scale_w = Float;
  v12->point = point + 48;
  v16 = effDataGet(pParts);
  v17 = *(void *)((v16->klass->vtable._5_GetExtUnits.methodPtr)(v16, v16->klass->vtable._5_GetExtUnits.method) + 32);
  v18 = dds3BillboardCreate(1u, v17);
  v3->hBillboard = v18;
  return v3;
}

// 0x197a770
void Delete(effPartsHandle_t *handle) {
  void *option;

  option = handle[3].option;
  if (option)
  {
    dds3BillboardDelete(option);
  }
}

// 0x197a840
mzfHandle_t *Copy(effPartsHandle_t *handle) {
  effPartsHandle_t *v4;
  u64 *monitor;
  Il2CppObject *v6;
  Il2CppClass *v7;

  v4 = Create(0);
  monitor = handle[3].monitor;
  v6 = Allocate(effMuzzleFlash_Params_t);
  _ctor(v6, 0);
  v7 = monitor[2];
  v4[3].monitor = v6;
  v6[1].klass = v7;
  ResourceCopy(v4, handle);
  return (mzfHandle_t *)v4;
}

// 0x197a980
void ResourceCopy(effPartsHandle_t *dst, effPartsHandle_t *src) {
  u64 *p_option;
  void *v8;
  effOption *option;
  void *v10;
  dds3Billboard_Basic_t *v11;

  option = dst[3].option;
  p_option = &dst[3].option;
  v8 = option;
  if (option)
  {
    dds3BillboardDelete(v8);
  }
  v10 = src[3].option;
  v11 = dds3BillboardCopy(v10);
  *p_option = v11;
}

// 0x197ab60
void Draw(effPartsHandle_t *handle) {
  dds3Billboard_Basic_t *option;
  s32 AnimFrame;
  s32 klass_high;
  dds3Billboard_Basic_t *v8;
  struct effMuzzleFlash v10;
  f32 *p_x;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 DirectionRotate;
  f32 DirectionScale;
  f32 *monitor;
  void *v22;
  f32 v23;
  f32 v24;
  f32 v25;
  struct sdfVector4_t v26;
  sdfMatrix4_t v29;
  sdfMatrix4_t v30;
  sdfVector4_t v31;
  sdfVector4_t v33;
  sdfVector4_t v34;

  option = handle[3].option;
  AnimFrame = dds3BillboardGetAnimFrame(handle[3].option);
  klass_high = HIDWORD(handle[3].klass);
  if (AnimFrame <= klass_high)
    return;
  v8 = handle[3].option;
  dds3BillboardSetAnimKey2(v8, klass_high);
  v26 = *(sdfVector4_t *)&handle[1].option;
  vct_A = v26;
  ToMatrix();
  v10 = v;
  vct_A = v10.v;
  vct_A.w = 0.0;
  get_transpose(&v30, &mtx_A, 0);
  v29 = v30;
  v31 = op_Multiply_60923920(&v29, vct_A, 0);
  vct_A = v31;
  p_x = &vf00.x;
  v15 = p_x[4];
  v16 = p_x[5];
  v34.y = v16;
  v17 = p_x[6];
  v18 = p_x[7];
  v34.w = v18;
  v34.x = v15;
  v34.z = v17;
  DirectionRotate = dds3BillboardGetDirectionRotate(*(sdfVector4_t *)&handle[1].klass, v34);
  v33.x = v15;
  v33.y = v16;
  v33.z = v17;
  v33.w = v18;
  DirectionScale = dds3BillboardGetDirectionScale(v33);
  monitor = handle[3].monitor;
  v22 = handle[3].option;
  v23 = *(f32 *)&handle[2].monitor;
  v24 = monitor[4] * v23;
  if (DirectionScale < 0.3)
    DirectionScale = 0.3;
  v25 = (f32)(DirectionScale * v23) * monitor[5];
  dds3BillboardSetScale(v22, v25, v24);
  dds3BillboardSetRotate(handle[3].option, DirectionRotate);
  dds3BillboardSetPosition(handle[3].option, *(sdfVector4_t *)&handle[1].klass);
  dds3BillboardDraw(handle[3].option);
  if (!get_STOP(0))
    ++HIDWORD(handle[3].klass);
}

// 0x197af70
void PositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;

  w = pPos->w;
  z = pPos->z;
  y = pPos->y;
  x = pPos->x;
  *(f32 *)&handle[1].monitor = z;
  *((f32 *)&handle[1].monitor + 1) = w;
  *(f32 *)&handle[1].klass = x;
  *((f32 *)&handle[1].klass + 1) = y;
}

// 0x197b020
void RotateSet(effPartsHandle_t *handle, const sdfVector4_t *pRot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;

  w = pRot->w;
  z = pRot->z;
  y = pRot->y;
  x = pRot->x;
  *(f32 *)&handle[2].klass = z;
  *((f32 *)&handle[2].klass + 1) = w;
  *(f32 *)&handle[1].option = x;
  *((f32 *)&handle[1].option + 1) = y;
}

// 0x197b0d0
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;

  w = abgr->w;
  z = abgr->z;
  y = abgr->y;
  x = abgr->x;
  *((f32 *)&handle[2].option + 1) = z;
  *(f32 *)&handle[3].klass = w;
  *((f32 *)&handle[2].monitor + 1) = x;
  *(f32 *)&handle[2].option = y;
}

// 0x197b180
void ScaleSet(effPartsHandle_t *handle, f32 scale) {
  *(f32 *)&handle[2].monitor = scale;
}
