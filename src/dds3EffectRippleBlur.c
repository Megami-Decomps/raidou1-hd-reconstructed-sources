#include "types.h"
#include "dds3billboard.h"
#include "dds3effectrippleblur.h"

typedef struct dds3Effect_RipBlurPart_t dds3Effect_RipBlurPart_t;
typedef struct dds3Effect_RippleBlurParam_t dds3Effect_RippleBlurParam_t;
typedef struct effRippleBlurHandle_t effRippleBlurHandle_t;

static void PartInit(dds3Effect_RippleBlurParam_t *pParam, dds3Effect_RipBlurPart_t *pPart);

// 0x1957b80
static void PartInit(dds3Effect_RippleBlurParam_t *pParam, dds3Effect_RipBlurPart_t *pPart) {
  dds3Effect_Blur_t *v6;
  SDF_GS_ALPHA *v9;
  dds3EffectBlendData *blend;

  *(u64 *)&pPart->scale = 0;
  v6 = Allocate(dds3Effect_Blur_t);
  _ctor(v6);
  v6->abgr = pParam->abgr;
  v9 = Get(pParam->_blend);
  blend = v6->_blend;
  blend->data = v9;
  v6->rotate = pParam->rotate;
  v6->center = pParam->center;
  pPart->Blur = v6;
}

// 0x1957c30
effRippleBlurHandle_t *dds3EffectRippleBlurCreate(dds3Effect_RippleBlurParam_t *pParam) {
  Il2CppObject *v3;
  dds3Effect_RippleBlurParam_t *v4;
  dds3Effect_RippleBlurParam_t *v6;
  Il2CppClass *v7;
  Il2CppObject *v8;
  dds3Billboard_Basic_t *v10;
  char *name;
  s64 v13;
  s64 v14;
  dds3Effect_RipBlurPart_t *v15;
  Il2CppClass *klass;

  v3 = Allocate(effRippleBlurHandle_t);
  _ctor(v3, 0);
  v4 = Allocate(dds3Effect_RippleBlurParam_t);
  _ctor_26574528(v4, pParam);
  v3[1].klass = v4;
  v6 = &v3[1];
  v7 = NewSpecific(dds3Effect_RipBlurPart_t, pParam->number);
  v3[2].klass = v7;
  v8 = v3 + 2;
  v10 = hGeneralBillboard[3];
  if (!v10)
    goto LABEL_13;
  goto LABEL_11;
  if (!v10)
LABEL_11:
LABEL_13:
  name = v10[1].klass->_1.name;
  v3[1].monitor = name;
  if (SLODWORD(v3[2].klass->_1.namespaze) >= 1)
  {
    v13 = 0;
    v14 = 32;
    do
    {
      v15 = Allocate(dds3Effect_RipBlurPart_t);
      _ctor(v15, 0);
      PartInit(v6, v15);
      klass = v8->klass;
      v15->scale = -(f32)(v6->interval * (f32)(s32)v13);
      QueryInterface(v15, *((void **)klass->_1.image + 8));
      *(void **)((char *)&klass->_1.image + v14) = v15;
      ++v13;
      v14 += 8;
    }
    while (v13 < SLODWORD(v8->klass->_1.namespaze));
  }
  return (effRippleBlurHandle_t *)v3;
}

// 0x1957fa0
void dds3EffectRippleBlurDelete(effRippleBlurHandle_t *hRippleBlur) {
  ;
}

// 0x1957fb0
void dds3EffectRippleBlurDraw(effRippleBlurHandle_t *hRippleBlur) {
  ;
}
