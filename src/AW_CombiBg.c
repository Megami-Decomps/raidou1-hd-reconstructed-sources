#include "types.h"
#include "aw.h"
#include "aw_combibg.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e33e60
void Init(void) {
  ;
}

// 0x1e33e70
s32 Add(s32 _Variation) {
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v10;
  AW_Func v11;
  AW_Func v12;
  s32 v13;
  AW_WORK_t *AW;
  char *v15;
  sdfVector3_t v17;
  sdfQuaternion_t v18;

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, Variation + 60, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v17.x = 0.0;
  v17.y = 0.0;
  v17.z = 0.0;
  v18.x = x;
  v18.y = y;
  v18.z = z;
  v18.w = w;
  v10 = Instantiate_object__39504752(AwPrefab, v17, v18);
  v11 = Allocate(AW_Func);
  _ctor(v11, 0, Method_Project_AW_CombiBg_Calc__, 0);
  v12 = Allocate(AW_Func);
  _ctor(v12, 0, Method_Project_AW_CombiBg_Draw__, 0);
  v13 = Add(404, 0.0, 0.0, 0.0, v10, v11, v12, 1);
  AW = GetAW(v13);
  v15 = "AW_CombiBg";
  AW->Variation = Variation;
  AW->DbgStr = v15;
  return v13;
}

// 0x1e34090
void DeleteAll(void) {
  DelAW_ID(404, 1);
}

// 0x1e34110
void Calc(AW_WORK_t *aWork) {
  ;
}

// 0x1e34120
void Draw(AW_WORK_t *aWork) {
  void *transform;

  transform = get_transform(aWork->Obj, 0);
  set_localPosition(transform, *(sdfVector3_t *)&aWork->X, 0);
}
