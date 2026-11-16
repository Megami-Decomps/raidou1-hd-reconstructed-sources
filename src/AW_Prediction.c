#include "types.h"
#include "aw.h"
#include "aw_prediction.h"
#include "dds3vrf.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e495a0
void Init(void) {
  ;
}

// 0x1e495b0
s32 Add(const sdfVector4_t *_Pos, f32 _SizeR, f32 _Life, s32 _Wait) {
  f32 y;
  f32 x;
  Il2CppObject *v10;
  f32 v12;
  f32 v13;
  f32 w;
  f32 v15;
  Il2CppObject *v16;
  AW_Func v17;
  AW_Func v18;
  s32 v19;
  AW_WORK_t *AW;
  AW_WORK_t *v21;
  f32 v22;
  char *v23;
  f32 z;
  sdfVector3_t v26;
  sdfQuaternion_t v27;

  y = Pos->y;
  x = Pos->x;
  z = Pos->z;
  v10 = get_Instance(*(const MethodInfo **)&Wait)->AwPrefab[119];
  v12 = identityQuaternion.x;
  v13 = identityQuaternion.y;
  v15 = identityQuaternion.z;
  w = identityQuaternion.w;
  v26.x = 0.0;
  v26.y = 0.0;
  v26.z = 0.0;
  v27.x = v12;
  v27.y = v13;
  v27.z = v15;
  v27.w = w;
  v16 = Instantiate_object__39504752(v10, v26, v27);
  v17 = Allocate(AW_Func);
  _ctor(v17, 0, Method_Project_AW_Prediction_Calc__, 0);
  v18 = Allocate(AW_Func);
  _ctor(v18, 0, Method_Project_AW_Prediction_Draw__, 0);
  v19 = Add(408, 0.0, 0.0, 0.0, v16, v17, v18, 1);
  AW = GetAW(v19);
  v21 = AW;
  AW->StepFloatC = Life;
  AW->StepIntA = Wait;
  AW->StepIntB = 0;
  *(u64 *)&AW->Step = 0;
  v22 = (f32)(SizeR / 100.0) * 0.5;
  AW->StepFloatA = v22;
  AW->StepFloatB = SizeR / 100.0;
  AW->Scale = v22;
  AW->X = x / -100.0;
  AW->Y = (f32)(y / -100.0) + 0.03;
  AW->Z = z / -100.0;
  if (Wait)
  {
    SetActive(AW->Obj, 0, 0);
    v21->Step = 10;
  }
  v23 = "AW_Prediction";
  v21->DbgStr = "AW_Prediction";
  return v19;
}

// 0x1e49850
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e498c0
void DeleteAll(void) {
  DelAW_ID(408, 1);
}

// 0x1e49940
void Calc(AW_WORK_t *aWork) {
  s32 Step;
  s32 v6;
  bool v7;
  f32 v8;
  f32 v9;
  f32 v11;
  f32 StepTime;
  f32 v13;
  f32 StepFloatA;
  f32 StepFloatB;
  f32 v16;
  s32 v17;
  void *Obj;
  bool v19;
  f32 StepFloatC;
  f32 v21;
  s32 v22;
  s32 Idx;

  if (ChkPause(aWork))
    return;
  Step = aWork->Step;
  if (Step == 10)
  {
    v17 = aWork->StepIntA - 1;
    Obj = aWork->Obj;
    v19 = aWork->StepIntA == 1;
    aWork->StepIntA = v17;
    if (v17 < 0 || v19)
    {
      SetActive(Obj, 1, 0);
      aWork->Step = 0;
    }
    else if (get_activeSelf(Obj, 0))
    {
      SetActive(aWork->Obj, 0, 0);
    }
  }
  else if (Step == 1)
  {
    StepFloatC = aWork->StepFloatC;
    if (StepFloatC == -1.0)
      return;
    v21 = StepFloatC + -1.0;
    aWork->StepFloatC = v21;
    if (v21 <= 0.0)
      goto LABEL_30;
    v22 = aWork->StepIntB + 1;
    v7 = aWork->StepIntB - 360 < 0;
    aWork->StepIntB = v22;
    if (v7 == __OFSUB__(v22, 361))
      Delete(aWork);
  }
  else
  {
    if (Step)
      return;
    v6 = aWork->StepIntB + 1;
    v7 = aWork->StepIntB - 360 < 0;
    aWork->StepIntB = v6;
    if (v7 == __OFSUB__(v6, 361))
    {
LABEL_30:
      Idx = aWork->Idx;
      DelAW(Idx, 1);
      return;
    }
    v8 = 0.0;
    v9 = 0.0;
    v11 = FPS60 * 8.0;
    StepTime = aWork->StepTime;
    if (v11 != 0.0)
    {
      v13 = 1.0;
      if ((f32)(StepTime / v11) <= 1.0)
        v13 = StepTime / v11;
      v9 = 0.0;
      if ((f32)(StepTime / v11) >= 0.0)
        v9 = v13;
    }
    StepFloatA = aWork->StepFloatA;
    StepFloatB = aWork->StepFloatB;
    if (v9 >= 0.0)
      v8 = v9;
    v16 = StepTime + VRF_DeltaTime;
    aWork->StepTime = v16;
    aWork->Scale = StepFloatA + (f32)(v8 * (f32)(StepFloatB - StepFloatA));
    if (v16 > v11)
    {
      aWork->StepIntB = 0;
      *(u64 *)&aWork->Step = 1;
    }
  }
}

// 0x1e49b90
void Draw(AW_WORK_t *aWork) {
  void *transform;
  void *v4;
  sdfVector3_t v5;

  transform = get_transform(aWork->Obj, 0);
  set_localPosition(transform, *(sdfVector3_t *)&aWork->X, 0);
  v4 = get_transform(aWork->Obj, 0);
  v5.x = aWork->Scale;
  v5.y = v5.x;
  v5.z = v5.x;
  set_localScale(v4, v5, 0);
}
