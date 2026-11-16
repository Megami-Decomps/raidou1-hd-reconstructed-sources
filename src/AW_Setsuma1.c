#include "types.h"
#include "aw.h"
#include "aw_setsuma1.h"
#include "sbtl.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

static bool CalcPos(AW_WORK_t *aWork);

// 0x1e505f0
void Init(void) {
  ;
}

// 0x1e50730
s32 Add(s32 _Unit_ListID, f32 _X, f32 _Y, f32 _Z) {
  Il2CppObject *v6;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 w;
  Il2CppObject *v12;
  AW_Func v13;
  AW_Func v14;
  s32 v15;
  AW_WORK_t *AW;
  char *v18;
  sdfVector3_t v20;
  sdfQuaternion_t v21;

  v6 = get_Instance(*(const MethodInfo **)&Unit_ListID)->AwPrefab[21];
  v8 = identityQuaternion.x;
  v9 = identityQuaternion.y;
  v10 = identityQuaternion.z;
  w = identityQuaternion.w;
  v20.x = 0.0;
  v20.y = 0.0;
  v20.z = 0.0;
  v21.x = v8;
  v21.y = v9;
  v21.z = v10;
  v21.w = w;
  v12 = Instantiate_object__39504752(v6, v20, v21);
  v13 = Allocate(AW_Func);
  _ctor(v13, 0, Method_Project_AW_Setsuma1_Calc__, 0);
  v14 = Allocate(AW_Func);
  _ctor(v14, 0, Method_Project_AW_Setsuma1_Draw__, 0);
  v15 = Add(216, 0.0, 0.0, 0.0, v12, v13, v14, 1);
  Set_HDEff(v15, 1, -1);
  AW = GetAW(v15);
  AW->HDEff_PosLink = 1;
  AW->StepFloatA = Y;
  CalcPos(AW);
  v18 = "AW_Setsuma1";
  AW->DbgStr = "AW_Setsuma1";
  return v15;
}

// 0x1e50b40
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e50bb0
void DeleteAll(void) {
  DelAW_ID(216, 1);
}

// 0x1e50960
static bool CalcPos(AW_WORK_t *aWork) {
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  SBTLUNIT_WORK *v7;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  f32 RotToDir;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 *camera;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 Dir180;
  f32 GetZ;
  f32 GetY;
  f32 GetX;
  sdfVector4_t v27;

  Unit_ListID = aWork->Unit_ListID;
  UnitMng = wk->UnitMng;
  v6 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  v7 = v6;
  if (v6 && !aWork->Step)
  {
    if (aWork->HDEff_PosLink)
    {
      x = v6->rot.x;
      y = v6->rot.y;
      z = v6->rot.z;
      w = v6->rot.w;
      v27.x = x;
      v27.y = y;
      v27.z = z;
      v27.w = w;
      RotToDir = sBtlGetRotToDir(v27);
      v14 = v7->pos.x;
      v15 = v7->pos.y + aWork->StepFloatA;
      v16 = v7->pos.z;
      GetZ = v16;
      GetY = v15;
      GetX = v14;
      camera = wk->scene->camera;
      GetMovePosToPos(v14, v15, v16, camera[16], camera[17], camera[18], 50.0, &GetX, &GetY, &GetZ);
      v19 = GetX / -100.0;
      v20 = GetY / -100.0;
      v21 = GetZ / -100.0;
      Dir180 = sBtlGetDir180(RotToDir);
      aWork->X = v19;
      aWork->Y = v20;
      aWork->Z = v21;
      aWork->Dir = Dir180;
    }
    else
    {
      aWork->Step = 1;
    }
  }
  return v7 != 0;
}

// 0x1e50c30
void Calc(AW_WORK_t *aWork) {
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v5;

  memset(&v5, 0, sizeof(v5));
  _GetEnumerator(&v5, aWork->ParticleSystemList);
  do
  {
    if (!_MoveNext(&v5))
    {
      _Dispose(&v5);
      goto LABEL_9;
    }
  }
  while (!IsAlive_61441520(v5._current, 0));
  _Dispose(&v5);
  if (CalcPos(aWork))
    return;
LABEL_9:
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e50dd0
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
