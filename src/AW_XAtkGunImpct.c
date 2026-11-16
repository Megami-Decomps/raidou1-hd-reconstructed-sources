#include "types.h"
#include "SKLID.h"
#include "aw.h"
#include "aw_xatkgunimpct.h"
#include "sbtlsound.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e8ddc0
void Init(void) {
  ;
}

// 0x1e87f70
s32 Add(f32 _UnityX, f32 _UnityY, f32 _UnityZ, SKLID _SklID) {
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
  u32 v25;
  char *v27;
  sdfVector3_t v29;
  sdfVector4_t v30;
  sdfQuaternion_t v31;

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 150, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v29.x = UnityX;
  v29.y = UnityY;
  v29.z = UnityZ;
  v31.x = x;
  v31.y = y;
  v31.z = z;
  v31.w = w;
  v16 = Instantiate_object__39504752(AwPrefab, v29, v31);
  v17 = Allocate(AW_Func);
  _ctor(v17, 0, Method_Project_AW_XAtkGunImpct_Calc__, 0);
  v18 = Allocate(AW_Func);
  _ctor(v18, 0, Method_Project_AW_XAtkGunImpct_Draw__, 0);
  v19 = Add(255, UnityX, UnityY, UnityZ, v16, v17, v18, 1);
  Set_HDEff(v19, 1, -1);
  AW = GetAW(v19);
  v21 = AW->X;
  v22 = AW->Y;
  v23 = AW;
  v24 = AW->Z;
  switch (SklID)
  {
    case 418:
      v25 = 144900099;
      goto LABEL_14;
    case 463:
      v25 = 147783683;
      goto LABEL_14;
    case 419:
      v25 = 144834563;
LABEL_14:
      v30.w = 0.0;
      v30.x = v21 * -100.0;
      v30.y = v22 * -100.0;
      v30.z = v24 * -100.0;
      sBtlPlay3DSE_BaseVol(v25, 120, v30);
      break;
  }
  v27 = "AW_XAtkGunImpct";
  v23->DbgStr = "AW_XAtkGunImpct";
  return v19;
}

// 0x1e8ddd0
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e8de40
void Calc(AW_WORK_t *aWork) {
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

// 0x1e8e080
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
