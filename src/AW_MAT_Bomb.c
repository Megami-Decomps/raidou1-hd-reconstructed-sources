#include "types.h"
#include "aw.h"
#include "aw_mat_bomb.h"
#include "sbtl.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e47d20
void Init(void) {
  ;
}

// 0x1e47d30
s32 Add(f32 _PS2X, f32 _PS2Y, f32 _PS2Z) {
  Il2CppObject *v7;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v13;
  AW_Func v14;
  AW_Func v15;
  s32 v16;
  AW_WORK_t *AW;
  char *v18;
  sdfVector3_t v20;
  sdfQuaternion_t v21;

  v7 = get_Instance()->AwPrefab[156];
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v20.x = 0.0;
  v20.y = 0.0;
  v20.z = 0.0;
  v21.x = x;
  v21.y = y;
  v21.z = z;
  v21.w = w;
  v13 = Instantiate_object__39504752(v7, v20, v21);
  v14 = Allocate(AW_Func);
  _ctor(v14, 0, Method_Project_AW_MAT_Bomb_Calc__, 0);
  v15 = Allocate(AW_Func);
  _ctor(v15, 0, Method_Project_AW_MAT_Bomb_Draw__, 0);
  v16 = Add(268, 0.0, 0.0, 0.0, v13, v14, v15, 3);
  Set_HDEff(v16, 1, -1);
  AW = GetAW(v16);
  v18 = "AW_MAT_Bomb";
  AW->Dir = 0.0;
  AW->DbgStr = v18;
  AW->X = PS2X / -100.0;
  AW->Y = PS2Y / -100.0;
  AW->Z = PS2Z / -100.0;
  return v16;
}

// 0x1e47f80
void Calc(AW_WORK_t *aWork) {
  s32 encountno;
  s32 v5;
  SBTLUNIT_WORK *UnitFromDevilID;
  u32 status;
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v10;

  memset(&v10, 0, sizeof(v10));
  encountno = wk->encountno;
  if (encountno == 54)
  {
    v5 = 300;
    goto LABEL_8;
LABEL_12:
    status = UnitFromDevilID->actwk->status;
    if (status == 10 || status == 40)
      goto LABEL_18;
    goto LABEL_14;
  }
  if (encountno != 43)
    goto LABEL_14;
  v5 = 262;
LABEL_8:
  UnitFromDevilID = sBtlGetUnitFromDevilID(v5);
  if (UnitFromDevilID)
    goto LABEL_12;
LABEL_14:
  if (ChkPause(aWork))
    return;
LABEL_18:
  _GetEnumerator(&v10, aWork->ParticleSystemList);
  while (_MoveNext(&v10))
  {
    if (IsAlive_61441520(v10._current, 0))
    {
      _Dispose(&v10);
      return;
    }
  }
  _Dispose(&v10);
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e48220
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
