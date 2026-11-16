#include "types.h"
#include "aw.h"
#include "aw_xatkbullethit.h"
#include "dds3vrf.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e8c150
void AW_XAtkBulletInit(void) {
  ;
}

// 0x1e85d10
s32 AW_XAtkBulletAdd(f32 _X, f32 _Y, f32 _Z) {
  AW_Func v7;
  s32 v8;
  AW_WORK_t *AW;
  char *v10;

  v7 = Allocate(AW_Func);
  _ctor(v7, 0, Method_Project_AW_XAtkBulletHit_Calc__, 0);
  v8 = Add(252, X, Y, Z, 0, v7, 0, 1);
  AW = GetAW(v8);
  v10 = "AW_XAtkBulletHit";
  AW->DbgStr = "AW_XAtkBulletHit";
  return v8;
}

// 0x1e86510
void AW_XAtkBulletDelete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e8c160
void AW_XAtkBulletCalc(AW_WORK_t *aWork) {
  s32 Step;
  s32 Idx;

  if (ChkPause(aWork))
    return;
  Step = aWork->Step;
  if (Step == 1)
  {
    Idx = aWork->Idx;
    DelAW(Idx, 1);
  }
  else if (!Step)
  {
    aWork->StepTime = aWork->StepTime + VRF_DeltaTime;
  }
}

// 0x1e8c290
void AW_XAtkBulletDraw(AW_WORK_t *aWork) {
  void *Obj;
  void *transform;
  void *v6;
  sdfVector3_t v7;

  Obj = aWork->Obj;
  if (op_Equality(Obj, 0, 0))
    return;
  transform = get_transform(aWork->Obj, 0);
  set_localPosition(transform, *(sdfVector3_t *)&aWork->X, 0);
  v6 = get_transform(aWork->Obj, 0);
  v7.y = aWork->Dir;
  v7.x = 0.0;
  v7.z = 0.0;
  set_eulerAngles(v6, v7, 0);
  return;
}
