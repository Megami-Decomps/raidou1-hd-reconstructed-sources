#include "types.h"
#include "aw.h"
#include "aw_guncylinder.h"
#include "aw_gunrapidbar.h"
#include "sbtl.h"
#include "sbtlcamera.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e37710
void Init(void) {
  ;
}

// 0x1e37720
s32 Add(void) {
  void *AwParentImage;
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  void *transform;
  Il2CppObject *v10;
  AW_Func v11;
  AW_Func v12;
  s32 v13;
  char *v50;
  sdfVector3_t v52;
  sdfQuaternion_t v53;

  AwParentImage = get_Instance(0)->AwParentImage;
  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 142, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  transform = get_transform(AwParentImage, 0);
  v52.x = 0.0;
  v52.y = 0.0;
  v52.z = 0.0;
  v53.x = x;
  v53.y = y;
  v53.z = z;
  v53.w = w;
  v10 = Instantiate_object__39505040(AwPrefab, v52, v53, transform);
  v11 = Allocate(AW_Func);
  _ctor(v11, 0, Method_Project_AW_GunCylinder_Calc__, 0);
  v12 = Allocate(AW_Func);
  _ctor(v12, 0, Method_Project_AW_GunCylinder_Draw__, 0);
  v13 = Add(305, 0.0, 0.0, 0.0, v10, v11, v12, 1);
  Set_AnimObj(v13, 0, "Image_cylinder");
  AW = GetAW(v13);
  v15 = Add(0.0);
  v16 = Add(10.0);
  v17 = Add(20.0);
  v18 = Add(30.0);
  v19 = Add(40.0);
  v20 = Add(50.0);
  v21 = Add(60.0);
  v22 = Add(70.0);
  v23 = Add(80.0);
  v24 = Add(90.0);
  v25 = Add(100.0);
  v26 = Add(110.0);
  v27 = Add(120.0);
  v28 = Add(130.0);
  v29 = Add(140.0);
  v30 = Add(150.0);
  v31 = Add(160.0);
  v32 = Add(170.0);
  v33 = Add(180.0);
  v34 = Add(190.0);
  v35 = Add(200.0);
  v36 = Add(210.0);
  v37 = Add(220.0);
  v38 = Add(230.0);
  v39 = Add(240.0);
  v40 = Add(250.0);
  v41 = Add(260.0);
  v42 = Add(270.0);
  v43 = Add(280.0);
  v44 = Add(290.0);
  v45 = Add(300.0);
  v46 = Add(310.0);
  v47 = Add(320.0);
  v48 = Add(330.0);
  v49 = Add(340.0);
  Add(350.0);
  v50 = "AW_GunCylinder";
  AW[4].genericMethod = "AW_GunCylinder";
  return v13;
}

// 0x1e37e20
void Del(s32 _Unit_ListID, s32 _SubIdx) {
  AW_WORK_t *AW_Unit_ListID_SubIdx;
  s32 Idx;

  AW_Unit_ListID_SubIdx = GetAW_Unit_ListID_SubIdx(305, Unit_ListID, SubIdx);
  if (!AW_Unit_ListID_SubIdx)
    return;
  Idx = AW_Unit_ListID_SubIdx->Idx;
  DelAW(Idx, 1);
  DelAW_ID(306, 1);
}

// 0x1e37fb0
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
  DelAW_ID(306, 1);
}

// 0x1e38060
void DeleteAll(void) {
  DelAW_ID(305, 1);
  DelAW_ID(306, 1);
}

// 0x1e38110
void Calc(AW_WORK_t *aWork) {
  s32 height;

  if ((wk->status & 0x400) != 0)
    goto LABEL_15;
  if (sBtlChkMenu2Open())
    goto LABEL_13;
  goto LABEL_9001;
  if (sBtlChkMenu2Open())
  {
LABEL_13:
    aWork->X = (f32)((f32)get_width(0) / 100.0) * 50.0;
    height = get_height(0);
    aWork->Scale = 1.0;
    aWork->Y = (f32)((f32)height / 100.0) * 50.0;
    aWork->AnimIdx = 0;
    return;
  }
LABEL_9001:
  if ((wk->status & 0x40) == 0)
    goto LABEL_13;
LABEL_15:
  aWork->AnimIdx = -1;
}

// 0x1e38290
void Draw(AW_WORK_t *aWork) {
  void *transform;
  void *v4;
  sdfVector3_t v5;

  transform = get_transform(aWork->Obj, 0);
  set_position(transform, *(sdfVector3_t *)&aWork->X, 0);
  v4 = get_transform(aWork->Obj, 0);
  v5.x = aWork->Scale;
  v5.y = v5.x;
  v5.z = v5.x;
  set_localScale(v4, v5, 0);
  Draw_AnimObj(aWork);
}
