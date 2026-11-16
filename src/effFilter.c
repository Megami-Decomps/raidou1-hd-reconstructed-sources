#include "types.h"
#include "efffilter.h"
#include "effparts.h"
#include "sdftex.h"

typedef struct Standard Standard;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct efilterHandle_t efilterHandle_t;

static bool gDirectColor_Use;
static sdfVector4_t gDirectColor_abgr;
static void *effFilterTypeTable;

static efilterHandle_t *Create(u32 type, u8 *pParams);

// 0x1971f00
static efilterHandle_t *Create(u32 type, u8 *pParams) {
  void *v6;
  sdfBinary *v7;
  efilterHandle_t *v8;

  v6 = effFilterTypeTable[type];
  v7 = Allocate(sdfBinary);
  _ctor_36176832(v7, pParams, 0);
  v8 = (efilterHandle_t *)(v6->invoke_impl)(v6->method_code, v7, v6->method);
  (v8->klass->vtable._4_Create.methodPtr)(v8, v8->klass->vtable._4_Create.method);
  return v8;
}

// 0x1971fd0
efilterHandle_t *PartsCreate(Standard *pParts) {
  u8 *v4;
  u32 type;
  efilterHandle_t *v6;

  v4 = effParamsGet(pParts);
  type = pParts->param->type;
  v6 = Create(type, v4);
  (v6->klass->vtable._8_TexSet.methodPtr)(v6, pParts, v6->klass->vtable._8_TexSet.method);
  return v6;
}

// 0x1972090
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

// 0x19721e0
efilterHandle_t *Copy(effPartsHandle_t *handle) {
  effPartsHandle_t *klass;
  effPartsHandle_t *v5;
  effPartsHandle_t *v6;

  klass = handle->klass;
  (v6[1]._1.image)(v5, v6[1]._1.gc_desc);
  return (efilterHandle_t *)handle;
}

// 0x1972330
void Draw(effPartsHandle_t *handle) {
  effPartsHandle_t *klass;

  klass = handle->klass;
  (klass[1]._1.this_arg.data)(handle, *(u64 *)&klass[1]._1.this_arg.bits);
  if (!get_STOP(0))
    ++HIDWORD(handle[2].option);
}

// 0x19723e0
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

// 0x1972490
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  s64 v11;
  s64 naturalAligment;

  w = abgr->w;
  z = abgr->z;
  y = abgr->y;
  x = abgr->x;
  goto LABEL_3;
LABEL_12:
  if (handle->klass->_2.naturalAligment >= (u32)naturalAligment && handle->klass->_2.typeHierarchy[naturalAligment - 1] == efilterHandle_t)
  {
    goto LABEL_14;
  }
LABEL_15:
LABEL_3:
  if (!gDirectColor_Use)
    goto LABEL_12;
  if (handle)
  {
    if (handle->klass->_2.naturalAligment < (u32)v11 || handle->klass->_2.typeHierarchy[v11 - 1] != efilterHandle_t)
      goto LABEL_15;
  }
  x = gDirectColor_abgr.x;
  y = gDirectColor_abgr.y;
  z = gDirectColor_abgr.z;
  w = gDirectColor_abgr.w;
LABEL_14:
  *(f32 *)&handle[2].monitor = z;
  *((f32 *)&handle[2].monitor + 1) = w;
  *(f32 *)&handle[2].klass = x;
  *((f32 *)&handle[2].klass + 1) = y;
}

// 0x19725e0
void ScaleSet(effPartsHandle_t *handle, f32 scale) {
  *(f32 *)&handle[2].option = scale;
}

// 0x1972670
void effSetDirectColorMode(f32 _R, f32 _G, f32 _B, f32 _A) {
  gDirectColor_abgr.z = B;
  gDirectColor_abgr.w = A;
  gDirectColor_Use = 1;
  gDirectColor_abgr.x = R;
  gDirectColor_abgr.y = G;
}

// 0x1972700
void effClearDirectColorMode(void) {
  gDirectColor_Use = 0;
  return;
}
