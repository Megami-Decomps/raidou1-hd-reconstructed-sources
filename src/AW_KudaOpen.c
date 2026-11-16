#include "types.h"
#include "aw.h"
#include "aw_kudaopen.h"
#include "dds3vrf.h"
#include "sbtl.h"
#include "sbtlsound.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e41570
void Init(void) {
  ;
}

// 0x1e41580
s32 Add(s32 _ListID) {
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v7;
  SBTLUNIT_WORK *v8;
  void *KudaObj;
  AW_WORK_t *AW_ID;
  void *Instance;
  Il2CppObject *AwPrefab;
  void *transform;
  Il2CppObject *v15;
  AW_Func v16;
  AW_Func v17;
  s32 v18;
  AW_WORK_t *AW;
  char *v20;

  UnitMng = wk->UnitMng;
  v7 = sBtlSearchUnit_ID(UnitMng, ListID);
  if (!v7)
    return -1;
  v8 = v7;
  KudaObj = v7->KudaObj;
  if (!!op_Equality(KudaObj, 0, 0))
    return -1;
  AW_ID = GetAW_ID(229);
  if (AW_ID)
    return -1;
  Instance = get_Instance(AW_ID);
  AwPrefab = GetAwPrefab(Instance, 46, 0);
  transform = get_transform(v8->KudaObj, 0);
  v15 = Instantiate_object__39504352(AwPrefab, transform);
  v16 = Allocate(AW_Func);
  _ctor(v16, 0, Method_Project_AW_KudaOpen_Calc__, 0);
  v17 = Allocate(AW_Func);
  _ctor(v17, 0, Method_Project_AW_KudaOpen_Draw__, 0);
  v18 = Add(229, 0.0, 0.0, 0.0, v15, v16, v17, 1);
  Set_HDEff(v18, 1, -1);
  AW = GetAW(v18);
  AW->Unit_ListID = ListID;
  v20 = "AW_KudaUpen";
  AW->DbgStr = "AW_KudaUpen";
  return v18;
}

// 0x1e41880
void Del(void) {
  AW_WORK_t *AW_ID_Default;
  s32 Idx;

  AW_ID_Default = GetAW_ID_Default(229);
  if (!AW_ID_Default)
    return;
  Idx = AW_ID_Default->Idx;
  DelAW(Idx, 1);
}

// 0x1e41940
void Calc(AW_WORK_t *aWork) {
  Il2CppObject *current;
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v5;

  memset(&v5, 0, sizeof(v5));
  _GetEnumerator(&v5, aWork->ParticleSystemList);
  while (_MoveNext(&v5))
  {
    current = v5._current;
    if (!op_Equality(current, 0, 0) && IsAlive_61441520(current, 0))
    {
      _Dispose(&v5);
      return;
    }
  }
  _Dispose(&v5);
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e41b10
void Draw(AW_WORK_t *aWork) {
}

// 0x1e41b40
s32 Add_Support(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v5;
  SBTLUNIT_WORK *v6;
  void *KudaSupportObj;
  void *p_KudaSupportObj;
  s32 v9;
  void *gameObject;
  void *transform;
  void *v12;
  void *v13;
  Il2CppClass *klass;
  void *Instance;
  Il2CppObject *AwPrefab;
  void *v17;
  Il2CppObject *v18;
  AW_Func v19;
  AW_Func v20;
  AW_WORK_t *AW;
  char *v22;
  float32x2_t *v23;
  float32x2_t v24;
  f32 v25;
  u64 pos;
  sdfVector4_t v28;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v5 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (!v5)
    return -1;
  v6 = v5;
  KudaSupportObj = v5->KudaSupportObj;
  p_KudaSupportObj = &v5->KudaSupportObj;
  if (!op_Equality(KudaSupportObj, 0, 0))
    goto LABEL_21;
  gameObject = get_gameObject(v6->hModel->modelRoot->modelObj, 0);
  if (!op_Inequality(gameObject, 0, 0))
    goto LABEL_21;
  transform = get_transform(gameObject, 0);
  v12 = Find(transform, "program_ctrl/linknode", 0);
  if (op_Inequality(v12, 0, 0))
  {
    v13 = get_gameObject(v12, 0);
    klass = GetComponent_object_(v13)[4].klass;
    p_KudaSupportObj = klass;
  }
LABEL_21:
  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 46, 0);
  v17 = get_transform(p_KudaSupportObj, 0);
  v18 = Instantiate_object__39504352(AwPrefab, v17);
  v19 = Allocate(AW_Func);
  _ctor(v19, 0, Method_Project_AW_KudaOpen_Calc_Support__, 0);
  v20 = Allocate(AW_Func);
  _ctor(v20, 0, Method_Project_AW_KudaOpen_Draw_Support__, 0);
  v9 = Add(230, 0.0, 0.0, 0.0, v18, v19, v20, 1);
  Set_HDEff(v9, 1, -1);
  AW = GetAW(v9);
  v22 = "AW_KudaUpen_Support";
  v23 = AW;
  AW->Scale = 0.1;
  AW->DbgStr = v22;
  v24.n64_u64[0] = vmul_f32(vadd_f32(v23[10], v23[36]), vdup_n_s32(0xC2C80000)).n64_u64[0];
  v25 = (f32)(v23[11].n64_f32[0] + v23[37].n64_f32[0]) * -100.0;
  pos = v24.n64_u64[0];
  v24.n64_u64[0] = pos;
  *(float32x2_t *)&v28.x = v24;
  v28.z = v25;
  v28.w = 0.0;
  sBtlPlay3DSE(0x1006Au, v28);
  return v9;
}

// 0x1e41f60
void Calc_Support(AW_WORK_t *aWork) {
  __int128 v3;
  Il2CppObject *current;
  s32 Step;
  f32 v6;
  s32 Idx;
  f32 v9;
  s64 v10;
  f32 v11;
  System_Collections_Generic_List_Enumerator_T__o v12;
  System_Collections_Generic_List_Enumerator_T__o v13;

  _GetEnumerator(&v12, aWork->ParticleSystemList);
  v13._current = v12._current;
  v3 = *(_OWORD *)&v12._list;
  v12._list = 0;
  *(u64 *)&v12._index = &v13;
  *(_OWORD *)&v13._list = v3;
  while (_MoveNext(&v13))
  {
    current = v13._current;
    if (!op_Equality(current, 0, 0) && IsAlive_61441520(current, 0))
    {
      _Dispose(&v13);
      Step = aWork->Step;
      if (Step)
      {
        if (Step != 1)
        {
          if (Step == 2)
          {
            v6 = aWork->Scale + -0.1;
            aWork->Scale = v6;
            if (v6 <= 0.0)
            {
              aWork->Scale = 0.0;
              goto LABEL_15;
            }
          }
          return;
        }
        v9 = aWork->StepTime + VRF_DeltaTime;
        aWork->StepTime = v9;
        if (v9 <= (f32)(FPS60 * 50.0))
          return;
        v10 = 2;
      }
      else
      {
        v11 = aWork->Scale + 0.05;
        aWork->Scale = v11;
        if (v11 < 1.0)
          return;
        aWork->Scale = 1.0;
        v10 = 1;
      }
      *(u64 *)&aWork->Step = v10;
      return;
    }
  }
  _Dispose(&v13);
LABEL_15:
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e42200
void Draw_Support(AW_WORK_t *aWork) {
  void *transform;
  void *v4;
  sdfVector3_t v5;
  sdfVector3_t v6;

  transform = get_transform(aWork->Obj, 0);
  v5.x = 0.0;
  v5.y = 0.0;
  v5.z = 0.0;
  set_localPosition(transform, v5, 0);
  v4 = get_transform(aWork->Obj, 0);
  v6.x = aWork->Scale;
  v6.y = v6.x;
  v6.z = v6.x;
  set_localScale(v4, v6, 0);
}
