#include "types.h"
#include "effblur.h"
#include "effparts.h"
#include "sdftex.h"

typedef struct Standard Standard;
typedef struct eblurHandle_t eblurHandle_t;
typedef struct effPartsHandle_t effPartsHandle_t;

static void *effBlurTypeTable[6];

static eblurHandle_t *Create(u32 type, u8 *pParams);

// 0x1971270
static eblurHandle_t *Create(u32 type, u8 *pParams) {
  void *v6;
  sdfBinary *v7;
  eblurHandle_t *v8;

  v6 = effBlurTypeTable[type];
  v7 = Allocate(sdfBinary);
  _ctor_36176832(v7, pParams, 0);
  v8 = (eblurHandle_t *)(v6->invoke_impl)(v6->method_code, v7, v6->method);
  (v8->klass->vtable._4_Create.methodPtr)(v8, v8->klass->vtable._4_Create.method);
  return v8;
}

// 0x1971340
eblurHandle_t *PartsCreate(Standard *pParts) {
  u8 *v4;
  u32 type;
  eblurHandle_t *v6;

  v4 = effParamsGet(pParts);
  type = pParts->param->type;
  v6 = Create(type, v4);
  (v6->klass->vtable._8_TexSet.methodPtr)(v6, pParts, v6->klass->vtable._8_TexSet.method);
  return v6;
}

// 0x1971400
void Delete(effPartsHandle_t *handle) {
  effPartsHandle_t *klass;
  void *v5;
  effPartsHandle_t *v6;

  klass = handle->klass;
  (klass[1]._1.name)(handle, klass[1]._1.namespaze);
  v5 = handle[4].klass;
  if (!op_Inequality(handle[4].klass, 0, 0))
    return;
  if (LOWORD(handle[3].option) != 4)
  {
    v6 = handle[4].klass;
    sdfTexFreeDelayed(v6);
  }
}

// 0x1971550
eblurHandle_t *Copy(effPartsHandle_t *handle) {
  effPartsHandle_t *klass;
  effPartsHandle_t *v5;
  effPartsHandle_t *v6;

  klass = handle->klass;
  (v6[1]._1.image)(v5, v6[1]._1.gc_desc);
  return (eblurHandle_t *)handle;
}

// 0x19716a0
void effDraw(effPartsHandle_t *handle) {
  effPartsHandle_t *klass;

  klass = handle->klass;
  (klass[1]._1.this_arg.data)(handle, *(u64 *)&klass[1]._1.this_arg.bits);
  if (!get_STOP(0))
    ++HIDWORD(handle[2].option);
}

// 0x1971750
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

// 0x1971800
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;

  w = abgr->w;
  z = abgr->z;
  y = abgr->y;
  x = abgr->x;
  *(f32 *)&handle[2].monitor = z;
  *((f32 *)&handle[2].monitor + 1) = w;
  *(f32 *)&handle[2].klass = x;
  *((f32 *)&handle[2].klass + 1) = y;
}

// 0x19718b0
void ScaleSet(effPartsHandle_t *handle, f32 scale) {
  *(f32 *)&handle[2].option = scale;
}
