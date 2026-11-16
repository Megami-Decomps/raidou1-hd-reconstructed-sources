#include "types.h"
#include "aw.h"
#include "aw_combicam.h"
#include "dds3kerneldraw.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e34170
void Init(void) {
  ;
}

// 0x1e34180
s32 Add(s32 _Variation) {
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v10;
  AW_Func v11;
  s32 v12;
  AW_WORK_t *AW;
  char *v14;
  sdfVector3_t v16;
  sdfQuaternion_t v17;

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, Variation + 50, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v16.x = 0.0;
  v16.y = 0.0;
  v16.z = 0.0;
  v17.x = x;
  v17.y = y;
  v17.z = z;
  v17.w = w;
  v10 = Instantiate_object__39504752(AwPrefab, v16, v17);
  v11 = Allocate(AW_Func);
  _ctor(v11, 0, Method_Project_AW_CombiCam_Calc__, 0);
  v12 = Add(501, 0.0, 0.0, 0.0, v10, v11, 0, 1);
  AW = GetAW(v12);
  AW->Variation = Variation;
  SetActive(AW->Obj, 1, 0);
  if (AW->Variation <= 2u)
  {
    dds3SetOverwrite_ScreenParam_sensorSize(1, 36.0, 24.0);
  }
  v14 = "AW_CombiCam";
  AW->DbgStr = "AW_CombiCam";
  return v12;
}

// 0x1e343c0
void DeleteAll(void) {
  DelAW_ID(501, 1);
  dds3SetOverwrite_ScreenParam_sensorSize(0, 0.0, 0.0);
}

// 0x1e34460
void Calc(AW_WORK_t *aWork) {
  ;
}
