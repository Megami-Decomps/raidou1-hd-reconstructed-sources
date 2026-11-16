#include "types.h"
#include "aw.h"
#include "aw_disco.h"
#include "sbtlsub.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e35140
void Init(void) {
  ;
}

// 0x1e35150
s32 Add(s32 _SubIdx, const sdfVector3_t *_Pos3D) {
  f32 z;
  f32 y;
  f32 x;
  void *AwParentImage;
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 w;
  void *transform;
  Il2CppObject *v16;
  AW_Func v17;
  AW_Func v18;
  s32 v19;
  AW_WORK_t *AW;
  AW_WORK_t *v21;
  char *v23;
  sdfVector3_t v25;
  sdfVector3_t v26;
  sdfQuaternion_t v27;

  z = Pos3D->z;
  y = Pos3D->y;
  x = Pos3D->x;
  AwParentImage = get_Instance(0)->AwParentImage;
  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 33, 0);
  v11 = identityQuaternion.x;
  v12 = identityQuaternion.y;
  v13 = identityQuaternion.z;
  w = identityQuaternion.w;
  transform = get_transform(AwParentImage, 0);
  v25.x = 0.0;
  v25.y = 0.0;
  v25.z = 0.0;
  v27.x = v11;
  v27.y = v12;
  v27.z = v13;
  v27.w = w;
  v16 = Instantiate_object__39505040(AwPrefab, v25, v27, transform);
  v17 = Allocate(AW_Func);
  _ctor(v17, 0, Method_Project_AW_Disco_Calc__, 0);
  v18 = Allocate(AW_Func);
  _ctor(v18, 0, Method_Project_AW_Disco_Draw__, 0);
  v19 = Add(310, 0.0, 0.0, 0.0, v16, v17, v18, 1);
  Set_AnimObj(v19, 0, "f_disco_0");
  AW = GetAW(v19);
  v26.x = x;
  v26.y = y;
  v21 = AW;
  v26.z = z;
  AW->Step = 0;
  AW->Dir = 0.0;
  AW->AnimStep = 0;
  AW->AnimIdx = 0;
  AW->AnimTime = 0.0;
  AW->SubIdx = SubIdx;
  OnVisible(SubIdx);
  v23 = "AW_Disco";
  v21->DbgStr = "AW_Disco";
  return v19;
}

// 0x1e355b0
void DeleteAll(void) {
  DelAW_ID(310, 1);
}

// 0x1e35630
void Delete(s32 _SubIdx) {
  AW_WORK_t *AW_SubIdx;
  s32 Idx;

  AW_SubIdx = GetAW_SubIdx(310, SubIdx);
  if (!AW_SubIdx)
    return;
  Idx = AW_SubIdx->Idx;
  DelAW(Idx, 1);
}

// 0x1e353f0
void OnVisible(s32 _SubIdx, const sdfVector3_t *_Pos3D) {
  f32 z;
  f32 y;
  f32 x;
  AW_WORK_t *AW_SubIdx;
  f32 v9;
  f32 v10;
  AW_WORK_t *v12;
  unsigned __int128 v13;

  z = Pos3D->z;
  y = Pos3D->y;
  x = Pos3D->x;
  AW_SubIdx = GetAW_SubIdx(310, SubIdx);
  if (!AW_SubIdx)
    return;
  AW_SubIdx->PopX = x;
  AW_SubIdx->PopY = y;
  AW_SubIdx->PopZ = z;
  AW_SubIdx->AnimIdx = 0;
  v13 = 0u;
  sBtlChangeWorldtoScreenUnity3(x, y, z, &v13);
  v9 = *(f32 *)&v13;
  if (*(f32 *)&v13 <= -16.0 || v9 >= (f32)(get_width(0) + 16) || (v10 = *((f32 *)&v13 + 1), *((f32 *)&v13 + 1) <= 0.0) || v10 >= (f32)get_height(0))
  {
    v12 = GetAW_SubIdx(310, SubIdx);
    if (!v12)
      return;
    v12->AnimIdx = -1;
  }
}

// 0x1e356f0
void OffVisible(s32 _SubIdx) {
  AW_WORK_t *AW_SubIdx;

  AW_SubIdx = GetAW_SubIdx(310, SubIdx);
  if (!AW_SubIdx)
    return;
  AW_SubIdx->AnimIdx = -1;
}

// 0x1e35790
void Calc(AW_WORK_t *aWork) {
  s32 Step;
  f32 PopX;
  f32 PopY;
  f32 PopZ;
  s64 v8;
  s32 v9;
  unsigned __int128 v10;

  Step = aWork->Step;
  v10 = 0u;
  if (Step)
    return;
  PopX = aWork->PopX;
  PopY = aWork->PopY;
  PopZ = aWork->PopZ;
  if (sBtlChangeWorldtoScreenUnity3(PopX, PopY, PopZ, &v10))
  {
    v8 = v10;
    v9 = 0;
    aWork->Z = 0.0;
    *(u64 *)&aWork->X = v8;
  }
  else
  {
    v9 = -1;
  }
  aWork->AnimIdx = v9;
}

// 0x1e35870
void Draw(AW_WORK_t *aWork) {
  void *transform;
  void *v4;
  sdfVector3_t v5;

  transform = get_transform(aWork->Obj, 0);
  set_position(transform, *(sdfVector3_t *)&aWork->X, 0);
  v4 = get_transform(aWork->Obj, 0);
  v5.z = aWork->Dir;
  v5.x = 0.0;
  v5.y = 0.0;
  set_eulerAngles(v4, v5, 0);
  Draw_AnimObj(aWork);
}
