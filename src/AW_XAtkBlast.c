#include "types.h"
#include "aw.h"
#include "aw_xatkblast.h"
#include "dds3kerneldraw.h"
#include "sbtlsound.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e84890
void AW_XAtkInit(void) {
  ;
}

// 0x1e848a0
s32 AW_XAtkAdd(f32 _UnityX, f32 _UnityY, f32 _UnityZ, f32 _Size) {
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v16;
  AW_Func v17;
  AW_Func v18;
  s32 v19;
  AW_WORK_t *AW;
  f32 v21;
  f32 v22;
  AW_WORK_t *v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  char *v29;
  sdfVector3_t v31;
  sdfVector4_t v32;
  sdfQuaternion_t v33;

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 116, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v31.x = UnityX;
  v31.y = UnityY;
  v31.z = UnityZ;
  v33.x = x;
  v33.y = y;
  v33.z = z;
  v33.w = w;
  v16 = Instantiate_object__39504752(AwPrefab, v31, v33);
  v17 = Allocate(AW_Func);
  _ctor(v17, 0, Method_Project_AW_XAtkBlast_Calc__, 0);
  v18 = Allocate(AW_Func);
  _ctor(v18, 0, Method_Project_AW_XAtkBlast_Draw__, 0);
  v19 = Add(254, UnityX, UnityY, UnityZ, v16, v17, v18, 1);
  Set_HDEff(v19, 1, -1);
  AW = GetAW(v19);
  v22 = AW->X;
  v21 = AW->Y;
  v23 = AW;
  AW->Scale = Size;
  v24 = v21 + 1.0;
  v25 = AW->Z;
  v26 = v22 * -100.0;
  AW->Y = v24;
  v27 = v24 * -100.0;
  v28 = v25 * -100.0;
  v32.w = 0.0;
  v32.x = v26;
  v32.y = v27;
  v32.z = v28;
  sBtlPlay3DSE_BaseVol(0x10101u, 120, v32);
  dds3SetQuake(30, 0x32u);
  v29 = "AW_XAtkBlast";
  v23->DbgStr = "AW_XAtkBlast";
  return v19;
}

// 0x1e84b80
void AW_XAtkDelete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e84bf0
void AW_XAtkCalc(AW_WORK_t *aWork) {
  Il2CppObject *current;
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v6;

  memset(&v6, 0, sizeof(v6));
  if (ChkPause(aWork))
    return;
  _GetEnumerator(&v6, aWork->ParticleSystemList);
  while (_MoveNext(&v6))
  {
    current = v6._current;
    if (!op_Equality(current, 0, 0) && IsAlive_61441520(current, 0))
    {
      _Dispose(&v6);
      return;
    }
  }
  _Dispose(&v6);
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e84e30
void AW_XAtkDraw(AW_WORK_t *aWork) {
  void *transform;
  void *v4;
  void *v5;
  sdfVector3_t v6;
  sdfVector3_t v7;

  transform = get_transform(aWork->Obj, 0);
  set_localPosition(transform, *(sdfVector3_t *)&aWork->X, 0);
  v4 = get_transform(aWork->Obj, 0);
  v6.y = aWork->Dir;
  v6.x = 0.0;
  v6.z = 0.0;
  set_eulerAngles(v4, v6, 0);
  v5 = get_transform(aWork->Obj, 0);
  v7.x = aWork->Scale;
  v7.y = v7.x;
  v7.z = v7.x;
  set_localScale(v5, v7, 0);
}
