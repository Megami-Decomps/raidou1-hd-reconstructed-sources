#include "types.h"
#include "atlfieldplayermotionconst.h"
#include "field.h"

typedef struct AtlFieldPlayerMotionConst_Data AtlFieldPlayerMotionConst_Data;

static AtlFieldPlayerMotionConst_Data *c_Datas[1];

// 0x22aa610
AtlFieldPlayerMotionConst_Data *Find(eFieldPlayerMotion mot) {
  s64 v4;
  Il2CppClass **v5;
  AtlFieldPlayerMotionConst_Data *v6;
  AtlFieldPlayerMotionConst_Data *c_Datas_local;

  v4 = 0;
  do
  {
    c_Datas_local = c_Datas;
    if (v4 >= SLODWORD(c_Datas_local->max_length))
      return 0;
    c_Datas_local = c_Datas;
    v5 = &c_Datas_local->obj.klass + v4++;
    v6 = (AtlFieldPlayerMotionConst_Data *)v5[4];
  }
  while (v6->m_MotID != mot);
  return v6;
}
