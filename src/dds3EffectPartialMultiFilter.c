#include "types.h"
#include "dds3billboard.h"
#include "dds3effectfilter.h"
#include "dds3effectmultifilter.h"
#include "dds3effectpartialmultifilter.h"

typedef struct dds3Effect_PartialMultiFilterParam_t dds3Effect_PartialMultiFilterParam_t;
typedef struct effPartialMultiFilterHandle_t effPartialMultiFilterHandle_t;

// 0x19594b0
effPartialMultiFilterHandle_t *dds3EffectPartialMultiFilterCreate(dds3Effect_PartialMultiFilterParam_t *pParam) {
  Il2CppObject *v3;
  dds3Billboard_Basic_t *v5;
  char *name;
  dds3Effect_PartialMultiFilterParam_t *v8;
  dds3Effect_Filter_t *Filter;
  dds3Effect_Filter_t *v10;

  v3 = Allocate(effPartialMultiFilterHandle_t);
  _ctor(v3, 0);
  v5 = hGeneralBillboard[0];
  if (!v5)
    goto LABEL_13;
  goto LABEL_11;
  if (!v5)
LABEL_11:
LABEL_13:
  name = v5[1].klass->_1.name;
  v3[1].monitor = name;
  v8 = Allocate(dds3Effect_PartialMultiFilterParam_t);
  _ctor(v8, 0);
  v8->area = pParam->area;
  v8->center = Clone((sdfIVector2_t)&pParam->center, 0);
  Filter = pParam->Filter;
  v10 = Allocate(dds3Effect_Filter_t);
  _ctor_26578656(v10, Filter);
  v8->Filter = v10;
  v3[1].klass = v8;
  return (effPartialMultiFilterHandle_t *)v3;
}

// 0x1959760
void dds3EffectPartialMultiFilterDelete(effPartialMultiFilterHandle_t *hPartialMultiFilter) {
  dds3EffectDelete(hPartialMultiFilter->param->Filter);
}

// 0x1959770
void dds3EffectPartialMultiFilterDraw(effPartialMultiFilterHandle_t *hPartialMultiFilter) {
  dds3Effect_PartialMultiFilterParam_t *param;
  f32 v4;
  s32 v5;
  s32 v6;
  s32 v7;

  param = hPartialMultiFilter->param;
  v4 = (f32)param->area * 1.4;
  if (v4 == INFINITY)
    v5 = 0x80000000;
  else
    v5 = v4;
  v6 = get_Item((sdfIVector2_t)&param->center, 0, 0) + 256;
  v7 = get_Item((sdfIVector2_t)&hPartialMultiFilter->param->center, 1, 0)
     + 224;
  set_Item((sdfIVector2_t)hPartialMultiFilter->param->Filter->xy, 0, 16 * (v6 - v5), 0);
  set_Item((sdfIVector2_t)hPartialMultiFilter->param->Filter->xy, 1, 8 * (v7 - v5), 0);
  set_Item((sdfIVector2_t)&hPartialMultiFilter->param->Filter->xy[1], 0, 16 * (v5 + v6), 0);
  set_Item((sdfIVector2_t)&hPartialMultiFilter->param->Filter->xy[1], 1, 8 * (v5 + v7), 0);
  Execute(hPartialMultiFilter->param->Filter, hPartialMultiFilter->hAlphaTex);
}

// 0x1959890
void dds3EffectPartialMultiFilterDrawI4(effPartialMultiFilterHandle_t *hPartialMultiFilter) {
  dds3Effect_PartialMultiFilterParam_t *param;
  f32 v4;
  s32 v5;
  s32 v6;
  s32 v7;
  s32 v8;

  param = hPartialMultiFilter->param;
  v4 = (f32)param->area * 1.4;
  if (v4 == INFINITY)
    v5 = 0x80000000;
  else
    v5 = v4;
  v6 = get_Item((sdfIVector2_t)&param->center, 0, 0) + 4096;
  v7 = (get_Item((sdfIVector2_t)&hPartialMultiFilter->param->center, 1, 0) + 3584) >> 1;
  set_Item((sdfIVector2_t)hPartialMultiFilter->param->Filter->xy, 0, v6 - v5, 0);
  set_Item((sdfIVector2_t)&hPartialMultiFilter->param->Filter->xy[1], 0, v5 + v6, 0);
  v8 = v5 >> 1;
  set_Item((sdfIVector2_t)hPartialMultiFilter->param->Filter->xy, 1, v7 - v8, 0);
  set_Item((sdfIVector2_t)&hPartialMultiFilter->param->Filter->xy[1], 1, v8 + v7, 0);
  Execute(hPartialMultiFilter->param->Filter, hPartialMultiFilter->hAlphaTex);
}
