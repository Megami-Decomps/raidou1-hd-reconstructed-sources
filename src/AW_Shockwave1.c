#include "types.h"
#include "aw.h"
#include "aw_shockwave1.h"
#include "sbtlscene.h"
#include "sbtlsub.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e505e0
void Init(void) {
  ;
}

// 0x1e52b60
s32 Add(f32 _SX, f32 _SY, f32 _SZ, f32 _SDir, s32 _Variation) {
  f32 YukaEffY;
  f32 v12;
  f32 Dir180;
  s64 v15;
  Il2CppObject *v16;
  f32 v17;
  f32 x;
  f32 y;
  f32 v21;
  f32 v22;
  f32 z;
  f32 w;
  Il2CppObject *v25;
  AW_Func v26;
  AW_Func v27;
  s32 v28;
  s32 v29;
  AW_WORK_t *AW;
  char *v31;
  sdfVector3_t v33;
  sdfQuaternion_t v34;

  YukaEffY = sBtlGetYukaEffY();
  v12 = YukaEffY + SY;
  Dir180 = sBtlGetDir180(SDir);
  if (Variation == 1)
    v15 = 18;
  else
    v15 = 12;
  v16 = get_Instance()->AwPrefab[v15];
  v17 = SX / -100.0;
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  v21 = v12 / -100.0;
  v22 = SZ / -100.0;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v33.x = v17;
  v33.y = v21;
  v33.z = v22;
  v34.x = x;
  v34.y = y;
  v34.z = z;
  v34.w = w;
  v25 = Instantiate_object__39504752(v16, v33, v34);
  v26 = Allocate(AW_Func);
  _ctor(v26, 0, Method_Project_AW_Shockwave1_Calc__, 0);
  v27 = Allocate(AW_Func);
  _ctor(v27, 0, Method_Project_AW_Shockwave1_Draw__, 0);
  if (Variation == 1)
    v28 = 205;
  else
    v28 = 204;
  v29 = Add(v28, v17, v21, v22, v25, v26, v27, 1);
  Set_HDEff(v29, 1, -1);
  AW = GetAW(v29);
  v31 = "AW_Shockwave1";
  AW->Dir = Dir180;
  AW->Variation = Variation;
  AW->DbgStr = v31;
  return v29;
}

// 0x1e52e40
void Calc(AW_WORK_t *aWork) {
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v4;

  memset(&v4, 0, sizeof(v4));
  _GetEnumerator(&v4, aWork->ParticleSystemList);
  while (_MoveNext(&v4))
  {
    if (IsAlive_61441520(v4._current, 0))
    {
      _Dispose(&v4);
      return;
    }
  }
  _Dispose(&v4);
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e52fd0
void Draw(AW_WORK_t *aWork) {
}
