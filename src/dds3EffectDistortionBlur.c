#include "types.h"
#include "dds3billboard.h"
#include "dds3effectdistortionblur.h"

typedef struct dds3Effect_DistBlurPart_t dds3Effect_DistBlurPart_t;
typedef struct dds3Effect_DistortionBlurParam_t dds3Effect_DistortionBlurParam_t;
typedef struct effDistortionBlurHandle_t effDistortionBlurHandle_t;

static void PartInit(dds3Effect_DistortionBlurParam_t *pParam, dds3Effect_DistBlurPart_t *pPart);

// 0x1957010
static void PartInit(dds3Effect_DistortionBlurParam_t *pParam, dds3Effect_DistBlurPart_t *pPart) {
  u32 v5;
  dds3Effect_Blur_t *v7;
  SDF_GS_ALPHA *v10;
  dds3EffectBlendData *blend;
  dds3Effect_Blur_t *p_Blur;
  s32 area;
  s32 width;
  sdfIVector2_t p_center;
  s32 v16;
  f32 v17;
  s32 v19;
  f32 PM;
  s32 v22;
  f32 v23;
  s32 v24;
  s32 v25;
  s32 v26;
  s32 v27;
  s32 v28;
  struct sdfIVector2_t v29;

  v29 = 0;
  v5 = get_I(pParam) % (pParam->interval + 1);
  pPart->wait = v5;
  pPart->radiun = -3.1415927;
  v7 = Allocate(dds3Effect_Blur_t);
  _ctor(v7);
  v7->abgr = pParam->abgr;
  v10 = Get(pParam->_blend);
  blend = v7->_blend;
  blend->data = v10;
  v7->rotate = pParam->rotate;
  pPart->Blur = v7;
  p_Blur = &pPart->Blur;
  area = pParam->area;
  width = pParam->width;
  p_center = (sdfIVector2_t)&pParam->center;
  v16 = width >> 1;
  v17 = area;
  Item = get_Item(p_center, 0, 0);
  v19 = Item;
  PM = get_PM();
  v21 = get_Item(p_center, 1, 0);
  v22 = v21;
  v23 = get_PM() * v17;
  v24 = (f32)(PM * v17);
  if ((f32)(PM * v17) == INFINITY)
    v24 = 0x80000000;
  v25 = v24 + v19;
  v26 = v23;
  if (v23 == INFINITY)
    v26 = 0x80000000;
  _ctor((sdfIVector2_t)&v29, v25, v26 + v22, 0);
  v27 = get_Item((sdfIVector2_t)&v29, 0, 0) + 256;
  v28 = get_Item((sdfIVector2_t)&v29, 1, 0) + 224;
  p_Blur->center = v29;
  set_Item((sdfIVector2_t)(p_Blur)->xy, 0, v27 - v16, 0);
  set_Item((sdfIVector2_t)(p_Blur)->xy, 1, v28 - v16, 0);
  set_Item((sdfIVector2_t)&p_Blur->xy[1], 0, v27 + v16, 0);
  set_Item((sdfIVector2_t)&p_Blur->xy[1], 1, v28 + v16, 0);
}

// 0x19574e0
effDistortionBlurHandle_t *dds3EffectDistortionBlurCreate(dds3Effect_DistortionBlurParam_t *pParam) {
  effDistortionBlurHandle_t *v3;
  dds3Effect_DistortionBlurParam_t *v4;
  void *v6;
  s64 v7;
  dds3Billboard_Basic_t *v9;
  char *name;
  s64 v12;
  s64 v13;
  dds3Effect_DistBlurPart_t *v14;
  s64 v16;

  v3 = Allocate(effDistortionBlurHandle_t);
  v4 = Allocate(dds3Effect_DistortionBlurParam_t);
  _ctor_26572672(v4, pParam);
  v3->param = v4;
  v6 = NewSpecific(dds3Effect_DistBlurPart_t, pParam->number);
  v3->pwork = v6;
  v7 = &v3->pwork;
  v9 = hGeneralBillboard[2];
  if (!v9)
    goto LABEL_13;
  goto LABEL_11;
  if (!v9)
LABEL_11:
LABEL_13:
  name = v9[1].klass->_1.name;
  v3->hAlphaTex = name;
  if (*(s32 *)((u64)v3->pwork + 24) >= 1)
  {
    v12 = 0;
    v13 = 32;
    do
    {
      v14 = Allocate(dds3Effect_DistBlurPart_t);
      PartInit(v3->param, v14);
      v16 = *(u64 *)v7;
      *(u32 *)&v14->radiun = 1082427374;
      QueryInterface(v14, *(void **)(*(u64 *)v16 + 64));
      *(u64 *)(v16 + v13) = v14;
      ++v12;
      v13 += 8;
    }
    while (v12 < *(s32 *)(*(u64 *)v7 + 24));
  }
  return v3;
}

// 0x1957860
void dds3EffectDistortionBlurDelete(effDistortionBlurHandle_t *hDistortionBlur) {
  ;
}

// 0x1957870
void dds3EffectDistortionBlurDraw(effDistortionBlurHandle_t *hDistortionBlur) {
  ;
}
