#include "types.h"
#include "field.h"

#define c_TargetRingPool 8

typedef struct AtlHUDPrefabPoolConst_Data AtlHUDPrefabPoolConst_Data;

static AtlHUDPrefabPoolConst_Data *c_Datas[10];

static AtlHUDPrefabPoolConst_Data *Find(ePrefab type);

// 0x22aa820
static AtlHUDPrefabPoolConst_Data *Find(ePrefab type) {
  s64 v4;
  Il2CppClass **v5;
  AtlHUDPrefabPoolConst_Data *v6;
  AtlHUDPrefabPoolConst_Data *c_Datas_local;

  v4 = 0;
  do
  {
    c_Datas_local = c_Datas;
    if (v4 >= SLODWORD(c_Datas_local->max_length))
      return 0;
    c_Datas_local = c_Datas;
    v5 = &c_Datas_local->obj.klass + v4++;
    v6 = (AtlHUDPrefabPoolConst_Data *)v5[4];
  }
  while (v6->m_Prefab != type);
  return v6;
}
