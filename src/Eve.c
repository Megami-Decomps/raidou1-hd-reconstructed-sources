#include "types.h"
#include "dds3effectdistortionblur.h"
#include "dds3effectpartialmultiblur.h"
#include "dds3effectpartialmultifilter.h"
#include "dds3effectrippleblur.h"
#include "eve.h"

typedef struct CtrlBlur CtrlBlur;
typedef struct CtrlDistortionBlur CtrlDistortionBlur;
typedef struct CtrlFilter CtrlFilter;
typedef struct CtrlParallelBlur CtrlParallelBlur;
typedef struct CtrlPartialMultiBlur CtrlPartialMultiBlur;
typedef struct CtrlPartialMultiFilter CtrlPartialMultiFilter;
typedef struct CtrlRippleBlur CtrlRippleBlur;
typedef struct dds3Effect_Blur_t dds3Effect_Blur_t;

CtrlBlur *Blur;
CtrlPartialMultiBlur *PartialMultiBlur;
CtrlDistortionBlur *DistortionBlur;
CtrlRippleBlur *RippleBlur;
CtrlParallelBlur *ParallelBlur;
CtrlFilter *Filter;
CtrlPartialMultiFilter *PartialMultiFilter;
dds3Effect_Blur_t *effEvent_Edit_Blur;

// 0x1959c10
void EffectInit(void) {
  CtrlPartialMultiBlur *PartialMultiBlur_local;
  effPartialMultiBlurHandle_t *v4;
  CtrlDistortionBlur *DistortionBlur_local;
  effDistortionBlurHandle_t *v7;
  CtrlPartialMultiFilter *PartialMultiFilter_local;
  effPartialMultiFilterHandle_t *v10;
  CtrlRippleBlur *RippleBlur_local;
  effRippleBlurHandle_t *v13;

  PartialMultiBlur_local = PartialMultiBlur;
  v4 = dds3EffectPartialMultiBlurCreate(PartialMultiBlur_local->param);
  PartialMultiBlur_local->handle = v4;
  DistortionBlur_local = DistortionBlur;
  v7 = dds3EffectDistortionBlurCreate(DistortionBlur_local->param);
  DistortionBlur_local->handle = v7;
  PartialMultiFilter_local = PartialMultiFilter;
  v10 = dds3EffectPartialMultiFilterCreate(PartialMultiFilter_local->param);
  PartialMultiFilter_local->handle = v10;
  RippleBlur_local = RippleBlur;
  v13 = dds3EffectRippleBlurCreate(RippleBlur_local->param);
  RippleBlur_local->handle = v13;
  LODWORD(RippleBlur_local->param[1].klass) = 4;
}

// 0x1959dd0
void EffectDraw(void) {
  if (!Blur->Show)
    goto LABEL_5;
  goto LABEL_4;
  if (Blur->Show)
  {
LABEL_4:
    (Blur->klass->vtable._8_CallDraw.methodPtr)(Blur, Blur->klass->vtable._8_CallDraw.method);
  }
LABEL_5:
  if (PartialMultiBlur->Show)
  {
    (PartialMultiBlur->klass->vtable._8_CallDraw.methodPtr)(PartialMultiBlur, PartialMultiBlur->klass->vtable._8_CallDraw.method);
  }
  if (DistortionBlur->Show)
  {
    (DistortionBlur->klass->vtable._8_CallDraw.methodPtr)(DistortionBlur, DistortionBlur->klass->vtable._8_CallDraw.method);
  }
  if (RippleBlur->Show)
  {
    (RippleBlur->klass->vtable._8_CallDraw.methodPtr)(RippleBlur, RippleBlur->klass->vtable._8_CallDraw.method);
  }
  if (ParallelBlur->Show)
  {
    (ParallelBlur->klass->vtable._8_CallDraw.methodPtr)(ParallelBlur, ParallelBlur->klass->vtable._8_CallDraw.method);
  }
  if (Filter->Show)
  {
    (Filter->klass->vtable._8_CallDraw.methodPtr)(Filter, Filter->klass->vtable._8_CallDraw.method);
  }
  if (PartialMultiFilter->Show)
    (PartialMultiFilter->klass->vtable._8_CallDraw.methodPtr)(PartialMultiFilter, PartialMultiFilter->klass->vtable._8_CallDraw.method);
}

// 0x1959f50
dds3Effect_Blur_t *BlurEditorGetParams(void) {
  return effEvent_Edit_Blur;
}

// 0x1959fd0
void BlurSetParam2(dds3Effect_Blur_t *pParam) {
  dds3Effect_Blur_t *effEvent_Edit_Blur_local;
  SDF_GS_ALPHA *v5;
  dds3EffectBlendData *blend;
  sdfIVector2_t *xy;
  s64 v8;
  s64 v9;
  sdfIVector2_t *v10;
  sdfIVector2_t v11;

  effEvent_Edit_Blur_local = effEvent_Edit_Blur;
  effEvent_Edit_Blur_local->abgr = pParam->abgr;
  v5 = Get(pParam->_blend);
  blend = effEvent_Edit_Blur_local->_blend;
  blend->data = v5;
  *(u64 *)&effEvent_Edit_Blur_local->rotate = *(u64 *)&pParam->rotate;
  effEvent_Edit_Blur_local->center = Clone((sdfIVector2_t)&pParam->center, 0);
  xy = pParam->xy;
  if (SLODWORD(xy->max_length) >= 1)
  {
    v8 = 0;
    v9 = 32;
    do
    {
      v11 = Clone((sdfIVector2_t)((char *)xy + v9), 0);
      v10 = (&xy->obj.klass + v8++);
      v9 += 8;
      v10[4] = v11;
      xy = pParam->xy;
    }
    while (v8 < SLODWORD(xy->max_length));
  }
}
