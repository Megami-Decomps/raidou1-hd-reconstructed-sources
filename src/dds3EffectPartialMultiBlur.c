#include "types.h"
#include "dds3billboard.h"
#include "dds3effectpartialmultiblur.h"

typedef struct dds3Effect_PartialMultiBlurParam_t dds3Effect_PartialMultiBlurParam_t;
typedef struct effPartialMultiBlurHandle_t effPartialMultiBlurHandle_t;

// 0x1956b20
effPartialMultiBlurHandle_t *dds3EffectPartialMultiBlurCreate(dds3Effect_PartialMultiBlurParam_t *pParam) {
  Il2CppObject *v3;
  dds3Billboard_Basic_t *v5;
  char *name;
  dds3Effect_PartialMultiBlurParam_t *v8;
  dds3Effect_Blur_t *Blur;
  dds3Effect_Blur_t *v10;

  v3 = Allocate(effPartialMultiBlurHandle_t);
  _ctor(v3, 0);
  v5 = hGeneralBillboard[2];
  if (!v5)
    goto LABEL_13;
  goto LABEL_11;
  if (!v5)
LABEL_11:
LABEL_13:
  name = v5[1].klass->_1.name;
  v3[1].monitor = name;
  v8 = Allocate(dds3Effect_PartialMultiBlurParam_t);
  _ctor(v8, 0);
  v8->area = pParam->area;
  Blur = pParam->Blur;
  v10 = Allocate(dds3Effect_Blur_t);
  _ctor_26568960(v10, Blur);
  v8->Blur = v10;
  v3[1].klass = v8;
  return (effPartialMultiBlurHandle_t *)v3;
}

// 0x1956db0
void dds3EffectPartialMultiBlurDelete(effPartialMultiBlurHandle_t *hPartialMultiBlur) {
  ;
}

// 0x1956dc0
void dds3EffectPartialMultiBlurDraw(effPartialMultiBlurHandle_t *hPartialMultiBlur) {
  ;
}

// 0x1956dd0
void dds3EffectPartialMultiBlurDrawI4(effPartialMultiBlurHandle_t *hPartialMultiBlur) {
  ;
}
