#include "types.h"
#include "aw.h"
#include "aw_camlockon.h"
#include "aw_fatkbtn.h"
#include "sbtlsub.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e368f0
void Init(void) {
  ;
}

// 0x1e36900
s32 Add(s32 _SubIdx, const sdfVector3_t *_Pos3D) {
  f32 z;
  f32 y;
  f32 x;
  s32 v7;
  AW_WORK_t *AW;
  char *v12;
  sdfVector3_t v14;

  z = Pos3D->z;
  y = Pos3D->y;
  x = Pos3D->x;
  get_Instance(0);
  v7 = Add(311, 0.0, 0.0, 0.0, 0, 0, 0, 1);
  AW = GetAW(v7);
  AW->Step = 0;
  AW->Dir = 0.0;
  AW->AnimStep = 0;
  AW->AnimIdx = 0;
  AW->AnimTime = 0.0;
  AW->SubIdx = SubIdx;
  Add(0);
  v14.x = x;
  v14.y = y;
  v14.z = z;
  OnVisible(AW->SubIdx);
  v12 = "AW_FAtkBtn";
  AW->DbgStr = "AW_FAtkBtn";
  return v7;
}

// 0x1e36b40
void DeleteAll(void) {
  DeleteAll();
  DelAW_ID(311, 1);
}

// 0x1e36a40
void OnVisible(s32 _SubIdx, const sdfVector3_t *_Pos3D) {
  f32 z;
  f32 y;
  f32 x;
  AW_WORK_t *AW_ID;
  sdfVector3_t v9;

  z = Pos3D->z;
  y = Pos3D->y;
  x = Pos3D->x;
  AW_ID = GetAW_ID(311);
  if (!AW_ID)
    return;
  AW_ID->SubIdx = SubIdx;
  AW_ID->PopX = x;
  AW_ID->PopY = y;
  AW_ID->PopZ = z;
  v9.y = y;
  v9.z = z;
  v9.x = x;
  OnVisible(v9);
}

// 0x1e36c10
void OffVisible(s32 _SubIdx) {
  AW_WORK_t *AW_SubIdx;

  AW_SubIdx = GetAW_SubIdx(311, SubIdx);
  if (!AW_SubIdx)
    return;
  AW_SubIdx->AnimIdx = -1;
  OffVisible();
}

// 0x1e36d00
void Cng(s32 _SubIdx) {
  if (!GetAW_SubIdx(311, SubIdx))
    return;
  Cng();
}

// 0x1e36de0
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

// 0x1e36ec0
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
