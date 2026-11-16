#include "types.h"
#include "effoption.h"

typedef struct effOption effOption;
typedef struct effOption_Resource effOption_Resource;

struct effOption {
    s32 FieldOt;
    f32 colorAdjust;
    sdfVector4_t adjustRGBA;
};

static s32 fieldOtTable[2];

// 0x1960900
effOption *effGet(effOption_Resource *resrc) {
  effOption *v3;
  il2cpp_array_size_t max_length;
  s64 v5;
  effOption_Resource *v6;
  s32 type;
  f32 *param;
  s64 v9;
  s64 v10;
  f32 *m_Items;
  f32 *v12;
  f32 v13;
  f32 v15;
  u64 v16;
  void *v18;
  void *v19;
  char *v20;
  void *v21;

  if (!resrc || !resrc->max_length)
    return 0;
  v3 = Allocate(effOption);
  *(u64 *)&v3->FieldOt = 0x3F800000FFFFFFFFLL;
  v3->adjustRGBA = oneVector;
  _ctor(v3, 0);
  max_length = resrc->max_length;
  if ((s32)max_length >= 1)
  {
    v5 = 0;
    do
    {
      v6 = resrc[v5];
      type = v6->type;
      if (type)
      {
        if (type == 1)
        {
          v3->colorAdjust = v6->param[0];
        }
        else if (type == 2)
        {
          param = v6->param;
          if ((s32)param->max_length >= 1)
          {
            v9 = 0;
            v10 = (u32)param->max_length;
            m_Items = param;
            do
            {
              v12 = &v3->adjustRGBA;
              switch ((s32)v9)
              {
                case 0:
                  break;
                case 1:
                  v12 = &v3->adjustRGBA.y;
                  break;
                case 2:
                  v12 = &v3->adjustRGBA.z;
                  break;
                case 3:
                  v12 = &v3->adjustRGBA.w;
                  break;
                default:
                  v18 = InitializedMetadata(&System_IndexOutOfRangeException);
                  v19 = Allocate(v18);
                  v20 = InitializedMetadata(&"Invalid Vector4 index!");
                  v21 = InitializedMetadata(&Method_UnityEngine_Vector4_set_Item__);
              }
              v13 = m_Items[v9++];
              *v12 = v13;
            }
            while (v10 != v9);
          }
        }
      }
      else
      {
        max_length = resrc->max_length;
        v15 = v6->param[0];
        v16 = (s32)v15;
        if (v15 == INFINITY)
          v16 = 0xFFFFFFFF80000000LL;
        v3->FieldOt = fieldOtTable[v16];
      }
      ++v5;
    }
    while (v5 < (s32)max_length);
  }
  return v3;
}
