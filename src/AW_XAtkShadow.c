#include "types.h"
#include "aw.h"
#include "aw_xatkshadow.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1ebc210
void Init(void) {
  ;
}

// 0x1ebc220
s32 Add(f32 _X, f32 _Y, f32 _Z, f32 _Dir) {
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 w;
  Il2CppObject *v16;
  AW_Func v17;
  AW_Func v18;
  s32 v19;
  AW_WORK_t *AW;
  char *v21;
  sdfVector3_t v23;
  sdfQuaternion_t v24;

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 97, 0);
  v12 = identityQuaternion.x;
  v13 = identityQuaternion.y;
  v14 = identityQuaternion.z;
  w = identityQuaternion.w;
  v23.x = X;
  v23.y = Y;
  v23.z = Z;
  v24.x = v12;
  v24.y = v13;
  v24.z = v14;
  v24.w = w;
  v16 = Instantiate_object__39504752(AwPrefab, v23, v24);
  v17 = Allocate(AW_Func);
  _ctor(v17, 0, Method_Project_AW_XAtkShadow_Calc__, 0);
  v18 = Allocate(AW_Func);
  _ctor(v18, 0, Method_Project_AW_XAtkShadow_Draw__, 0);
  v19 = Add(264, X, Y, Z, v16, v17, v18, 1);
  AW = GetAW(v19);
  v21 = "AW_XAtkShadow";
  AW->Dir = Dir;
  AW->Y = 0.0;
  AW->DbgStr = v21;
  return v19;
}

// 0x1ebc450
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1ebc4c0
void Delete_2(s32 _AwIdx) {
  AW_WORK_t *AW;
  s32 Idx;

  if (AwIdx != -1)
  {
    AW = GetAW(AwIdx);
    if (!AW)
      return;
    Idx = AW->Idx;
    DelAW(Idx, 1);
  }
}

// 0x1ebc580
void Calc(AW_WORK_t *aWork) {
  ;
}

// 0x1ebc590
void Draw(AW_WORK_t *aWork) {
  void *transform;
  void *v4;
  sdfVector3_t v5;

  transform = get_transform(aWork->Obj, 0);
  set_localPosition(transform, *(sdfVector3_t *)&aWork->X, 0);
  v4 = get_transform(aWork->Obj, 0);
  v5.y = aWork->Dir;
  v5.x = 0.0;
  v5.z = 0.0;
  set_eulerAngles(v4, v5, 0);
}
