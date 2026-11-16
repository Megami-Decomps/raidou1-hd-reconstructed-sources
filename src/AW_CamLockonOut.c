#include "types.h"
#include "aw.h"
#include "aw_camlockonout.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e33720
void AW_CamLockonInit(void) {
  ;
}

// 0x1e33730
s32 AW_CamLockonAdd(s32 _SubIdx) {
  void *AwParentImage;
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  void *transform;
  Il2CppObject *v11;
  AW_Func v12;
  AW_Func v13;
  s32 v14;
  AW_WORK_t *AW;
  char *v16;
  sdfVector3_t v19;
  sdfQuaternion_t v20;

  AwParentImage = get_Instance(0)->AwParentImage;
  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 10, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  transform = get_transform(AwParentImage, 0);
  v19.x = 0.0;
  v19.y = 0.0;
  v19.z = 0.0;
  v20.x = x;
  v20.y = y;
  v20.z = z;
  v20.w = w;
  v11 = Instantiate_object__39505040(AwPrefab, v19, v20, transform);
  v12 = Allocate(AW_Func);
  _ctor(v12, 0, Method_Project_AW_CamLockonOut_Calc__, 0);
  v13 = Allocate(AW_Func);
  _ctor(v13, 0, Method_Project_AW_CamLockonOut_Draw__, 0);
  v14 = Add(302, 0.0, 0.0, 0.0, v11, v12, v13, 3);
  Set_AnimObj(v14, 0, "outside_u");
  Set_AnimObj(v14, 1, "outside_r");
  Set_AnimObj(v14, 2, "outside_d");
  Set_AnimObj(v14, 3, "outside_l");
  AW = GetAW(v14);
  AW->StepFloatA = 0.0;
  AW->SubIdx = SubIdx;
  AW->AnimIdx = -1;
  v16 = "AW_CamLockonOut";
  AW->DbgStr = "AW_CamLockonOut";
  return v14;
}

// 0x1e33a20
void AW_CamLockonDeleteAll(void) {
  DelAW_ID(302, 1);
}

// 0x1e33aa0
void AW_CamLockonSetPos(s32 _AW_Idx, f32 _2DX, f32 _2DY, f32 _NormalTime) {
  AW_WORK_t *AW;
  AW_WORK_t *v10;
  s32 width;
  s32 height;
  s32 v13;
  f32 v14;
  f32 v15;
  f32 StepFloatA;
  f32 v17;
  f32 v18;
  f32 Y;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 X;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;

  if (AW_Idx != -1)
  {
    AW = GetAW(AW_Idx);
    if (AW)
    {
      v10 = AW;
      AW->StepFloatA = NormalTime;
      if (2DX <= -16.0)
        goto LABEL_36;
      width = get_width(0);
      if (2DY <= 0.0 || (f32)(width + 16) <= 2DX || (f32)get_height(0) <= 2DY)
        goto LABEL_36;
      v10->X = 2DX;
      v10->Y = 2DY;
      v10->Z = 0.0;
      height = get_height(0);
      v13 = get_height(0);
      v14 = (height / 18);
      v15 = (v13 / 38);
      switch (v10->SubIdx)
      {
        case 0:
          StepFloatA = v10->StepFloatA;
          v17 = 1.0;
          v18 = v15 - v14;
          Y = v10->Y;
          v10->AnimIdx = 0;
          if (StepFloatA <= 1.0)
            v17 = StepFloatA;
          if (StepFloatA < 0.0)
            v17 = 0.0;
          v20 = (f32)(v18 * v17) + v14;
          goto LABEL_28;
        case 1:
          StepFloatA = v10->StepFloatA;
          v21 = 1.0;
          v22 = v15 - v14;
          X = v10->X;
          v10->AnimIdx = 1;
          if (StepFloatA <= 1.0)
            v21 = StepFloatA;
          if (StepFloatA < 0.0)
            v21 = 0.0;
          v24 = (f32)(v22 * v21) + v14;
          goto LABEL_34;
        case 2:
          StepFloatA = v10->StepFloatA;
          v25 = 1.0;
          v26 = v14 - v15;
          Y = v10->Y;
          v10->AnimIdx = 2;
          if (StepFloatA <= 1.0)
            v25 = StepFloatA;
          if (StepFloatA < 0.0)
            v25 = 0.0;
          v20 = (f32)(v26 * v25) - v14;
LABEL_28:
          v10->Y = Y + v20;
          break;
        case 3:
          StepFloatA = v10->StepFloatA;
          v27 = 1.0;
          v28 = v14 - v15;
          X = v10->X;
          v10->AnimIdx = 3;
          if (StepFloatA <= 1.0)
            v27 = StepFloatA;
          if (StepFloatA < 0.0)
            v27 = 0.0;
          v24 = (f32)(v28 * v27) - v14;
LABEL_34:
          v10->X = X + v24;
          break;
        default:
          StepFloatA = v10->StepFloatA;
          break;
      }
      if (StepFloatA < 0.2)
LABEL_36:
        v10->AnimIdx = -1;
    }
  }
}

// 0x1e33d00
void AW_CamLockonSetVisible(s32 _AW_Idx, bool _OnOff) {
  AW_WORK_t *AW;
  u32 SubIdx;

  if (AW_Idx != -1)
  {
    AW = GetAW(AW_Idx);
    if (AW)
    {
      if (OnOff)
      {
        SubIdx = AW->SubIdx;
        if (SubIdx > 3)
          return;
      }
      else
      {
        SubIdx = -1;
      }
      AW->AnimIdx = SubIdx;
    }
  }
}

// 0x1e33da0
void AW_CamLockonCalc(AW_WORK_t *aWork) {
  ;
}

// 0x1e33db0
void AW_CamLockonDraw(AW_WORK_t *aWork) {
  void *transform;

  transform = get_transform(aWork->Obj, 0);
  set_position(transform, *(sdfVector3_t *)&aWork->X, 0);
  Draw_AnimObj(aWork);
}
