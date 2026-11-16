#include "types.h"
#include "atlenemymotionconst.h"
#include "fieldEnemySymbol.h"

typedef struct AtlEnemyMotionConst_Data AtlEnemyMotionConst_Data;

static AtlEnemyMotionConst_Data *s_Datas[8];

// 0x22cea40
AtlEnemyMotionConst_Data *Find(eEnemyMotion mot) {
  s64 v4;
  Il2CppClass **v5;
  AtlEnemyMotionConst_Data *v6;
  AtlEnemyMotionConst_Data *s_Datas_local;

  v4 = 0;
  do
  {
    s_Datas_local = s_Datas;
    if (v4 >= SLODWORD(s_Datas_local->max_length))
      return 0;
    s_Datas_local = s_Datas;
    v5 = &s_Datas_local->obj.klass + v4++;
    v6 = (AtlEnemyMotionConst_Data *)v5[4];
  }
  while (v6->m_MotID != mot);
  return v6;
}
