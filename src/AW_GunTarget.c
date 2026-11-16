#include "types.h"
#include "aw.h"
#include "aw_guntarget.h"
#include "dds3vrf.h"
#include "sbtl.h"
#include "sbtlcamera.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sbtlvisual.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e38840
void Init(void) {
  ;
}

// 0x1e38850
s32 Add(s32 _Unit_ListID, s32 _SubIdx) {
  void *AwParentImage;
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  void *transform;
  Il2CppObject *v12;
  AW_Func v13;
  AW_Func v14;
  s32 v15;
  AW_WORK_t *AW;
  char *v17;
  sdfVector3_t v21;
  sdfQuaternion_t v22;

  AwParentImage = get_Instance(0)->AwParentImage;
  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 0, 0);
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  transform = get_transform(AwParentImage, 0);
  v21.x = 0.0;
  v21.y = 0.0;
  v21.z = 0.0;
  v22.x = x;
  v22.y = y;
  v22.z = z;
  v22.w = w;
  v12 = Instantiate_object__39505040(AwPrefab, v21, v22, transform);
  v13 = Allocate(AW_Func);
  _ctor(v13, 0, Method_Project_AW_GunTarget_Calc__, 0);
  v14 = Allocate(AW_Func);
  _ctor(v14, 0, Method_Project_AW_GunTarget_Draw__, 0);
  v15 = Add(303, 0.0, 0.0, 0.0, v12, v13, v14, 1);
  Set_AnimObj(v15, 0, "guntarget_0");
  Set_AnimObj(v15, 1, "guntarget_1");
  Set_AnimObj(v15, 2, "guntarget_2");
  Set_AnimObj(v15, 3, "guntarget_3");
  Set_AnimObj(v15, 4, "guntarget_4");
  Set_AnimObj(v15, 5, "guntarget_5");
  Set_AnimObj(v15, 6, "guntarget_6");
  Set_AnimObj(v15, 7, "guntarget_7");
  AW = GetAW(v15);
  AW->AnimStep = 0;
  AW->AnimIdx = 0;
  *(u64 *)&AW->Step = 0;
  *(u64 *)&AW->StepOfsX = 0;
  AW->StepFloatB = 0.0;
  AW->SubIdx = SubIdx;
  AW->Unit_ListID = Unit_ListID;
  v17 = "AW_GunTarget";
  AW->DbgStr = "AW_GunTarget";
  return v15;
}

// 0x1e38bf0
void Del(s32 _Unit_ListID, s32 _SubIdx) {
  AW_WORK_t *AW_Unit_ListID_SubIdx;
  s32 Idx;

  AW_Unit_ListID_SubIdx = GetAW_Unit_ListID_SubIdx(303, Unit_ListID, SubIdx);
  if (!AW_Unit_ListID_SubIdx)
    return;
  Idx = AW_Unit_ListID_SubIdx->Idx;
  DelAW(Idx, 1);
}

// 0x1e38cc0
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e38d30
void DeleteAll(void) {
  DelAW_ID(303, 1);
}

// 0x1e38db0
void Calc(AW_WORK_t *aWork) {
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v7;
  SBTLUNIT_WORK *v8;
  u16 major;
  s32 minor;
  V_POSITION_WORK *nml;
  f32 z;
  f32 x;
  f32 v14;
  s32 devilid;
  f32 v16;
  f32 v17;
  s32 Idx;
  s32 motionno;
  bool v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 Y;
  s32 AnimStep;
  f32 v27;
  s32 v28;
  f32 v29;
  f32 v30;
  s32 v31;
  s32 height;
  signed s32 v33;
  f32 v34;
  s32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  s32 v41;
  f32 v42;
  s32 v43;
  f32 v44;
  s32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  s32 Step;
  f32 v51;
  f32 v53;
  f32 StepFloatA;
  f32 StepOfsY;
  f32 v57;
  s32 AnimNum;
  s32 v60;
  unsigned __int128 v61;
  sdfVector4_t HelperPos;
  sdfVector4_t ppos;

  *(u64 *)&ppos.x = 0;
  *(u64 *)&ppos.z = 0;
  *(u64 *)&HelperPos.x = 0;
  *(u64 *)&HelperPos.z = 0;
  v61 = 0u;
  Unit_ListID = aWork->Unit_ListID;
  UnitMng = wk->UnitMng;
  v7 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  if (v7)
  {
    v8 = v7;
    major = v7->major;
    minor = v7->minor;
    nml = sBtlGetVisualData(major, minor)->nml;
    z = v8->pos.z;
    *(u64 *)&ppos.x = 0;
    *(u64 *)&ppos.z = 0;
    x = v8->pos.x;
    v14 = nml->height * -0.5;
    devilid = (u16)v8->para->devilid;
    v16 = v8->pos.y + v14;
    if ((s16)devilid <= 175)
    {
      if (devilid != 99 && devilid != 175)
      {
LABEL_42:
        if (!sBtlChangeWorldtoScreenUnity3(x, v16, z, &ppos))
          goto LABEL_58;
        if ((wk->status & 0x400) != 0)
          goto LABEL_58;
        if (sBtlChkMenu2Open())
          goto LABEL_55;
        goto LABEL_9000;
        if (sBtlChkMenu2Open())
        {
LABEL_55:
          switch (aWork->SubIdx)
          {
            case 0:
              aWork->X = 0.0;
              Y = 0.0;
              break;
            case 1:
              aWork->X = (f32)(get_height(0) / 135);
              v27 = (f32)get_height(0) / 16.875;
              v28 = v27;
              v20 = v27 == INFINITY;
              Y = -2147500000.0;
              v29 = v28;
              if (!v20)
                Y = v29;
              break;
            case 2:
              v30 = (f32)get_height(0) / 16.875;
              v31 = v30;
              if (v30 == INFINITY)
                v31 = 0x80000000;
              aWork->X = (f32)-v31;
              height = get_height(0);
              v33 = ((s32)(((u64)(222702007 * height) >> 32) - height) >> 7)
                  + ((u32)(((u64)(222702007 * height) >> 32) - height) >> 31);
              goto LABEL_81;
            case 3:
              v34 = (f32)get_height(0) / 21.6;
              v35 = v34;
              v20 = v34 == INFINITY;
              v36 = -2147500000.0;
              v37 = v35;
              if (!v20)
                v36 = v37;
              aWork->X = v36;
              v38 = get_height(0);
              v39 = 67.5;
              goto LABEL_78;
            case 4:
              v40 = (f32)get_height(0) / 27.0;
              v41 = v40;
              if (v40 == INFINITY)
                v41 = 0x80000000;
              aWork->X = (f32)-v41;
              v42 = (f32)get_height(0) / 13.5;
              v43 = v42;
              if (v42 == INFINITY)
                v43 = 0x80000000;
              goto LABEL_80;
            case 5:
              v44 = (f32)get_height(0) / 22.5;
              v45 = v44;
              v20 = v44 == INFINITY;
              v46 = -2147500000.0;
              v47 = v45;
              if (!v20)
                v46 = v47;
              aWork->X = v46;
              v38 = get_height(0);
              v39 = 16.875;
LABEL_78:
              v48 = v38 / v39;
              v43 = v48;
              if (v48 == INFINITY)
                v43 = 0x80000000;
LABEL_80:
              v33 = -v43;
LABEL_81:
              Y = (f32)v33;
              break;
            default:
              Y = aWork->Y;
              break;
          }
          v49 = Y + ppos.y;
          Step = aWork->Step;
          v51 = aWork->X + ppos.x;
          aWork->X = v51;
          aWork->Y = v49;
          if (Step == 2)
          {
            v53 = aWork->StepTime + VRF_DeltaTime;
            StepFloatA = aWork->StepFloatA;
            aWork->StepTime = v53;
            if (v53 > (f32)(StepFloatA * FPS60))
              *(u64 *)&aWork->Step = 1;
          }
          else if (Step == 1)
          {
            *(u64 *)&aWork->Step = 2;
            aWork->StepOfsX = (f32)(u32)sub_1905740(2, 0);
            aWork->StepOfsY = (f32)(u32)sub_1905740(2, 0);
            aWork->StepFloatA = (f32)(u32)sub_1905740(2, 0) + 1.0;
            v51 = aWork->X;
            v49 = aWork->Y;
          }
          StepOfsY = aWork->StepOfsY;
          aWork->X = v51 + aWork->StepOfsX;
          aWork->Y = v49 + StepOfsY;
          v57 = aWork->AnimTime + VRF_DeltaTime;
          aWork->AnimTime = v57;
          if (v57 <= FPS60)
          {
            AnimStep = aWork->AnimStep;
          }
          else
          {
            AnimStep = aWork->AnimStep + 1;
            AnimNum = aWork->AnimNum;
            aWork->AnimTime = v57 - FPS60;
            aWork->AnimStep = AnimStep;
            if (AnimStep >= AnimNum)
            {
              AnimStep = AnimNum - 1;
              v60 = aWork->Step;
              aWork->AnimStep = AnimStep;
              if (!v60)
                aWork->Step = 1;
            }
          }
          goto LABEL_59;
        }
LABEL_9000:
        if ((wk->status & 0x40) == 0)
          goto LABEL_55;
LABEL_58:
        AnimStep = -1;
LABEL_59:
        aWork->AnimIdx = AnimStep;
        return;
      }
    }
    else
    {
      if ((u32)(devilid - 417) > 0xFFFFFFFB)
      {
        v24 = 180.0;
LABEL_41:
        v16 = v16 + v24;
        goto LABEL_42;
      }
      if (devilid != 529)
      {
        if (devilid != 442)
          goto LABEL_42;
        *(u64 *)&HelperPos.x = 0;
        *(u64 *)&HelperPos.z = 0;
        sBtlGetUnitDamagePos(v8, &HelperPos);
        v17 = HelperPos.y;
        goto LABEL_35;
      }
    }
    v61 = 0u;
    sBtlGetUnitDamagePos(v8, &v61);
    motionno = v8->motionno;
    v20 = motionno == 15 || motionno == 6;
    if (v20)
    {
      v21 = *((f32 *)&v61 + 1) - v16;
      if ((f32)(*((f32 *)&v61 + 1) - v16) < -80.0)
        v21 = -80.0;
      v22 = 80.0;
      v23 = 0.2;
      goto LABEL_38;
    }
    v17 = *((f32 *)&v61 + 1);
LABEL_35:
    v21 = v17 - v16;
    v23 = 0.02;
    if (v21 < -30.0)
      v21 = -30.0;
    v22 = 30.0;
LABEL_38:
    if (v21 > v22)
      v21 = v22;
    v24 = aWork->StepFloatB + (f32)((f32)(v21 - aWork->StepFloatB) * v23);
    aWork->StepFloatB = v24;
    goto LABEL_41;
  }
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e394e0
void Draw(AW_WORK_t *aWork) {
  void *transform;

  transform = get_transform(aWork->Obj, 0);
  set_position(transform, *(sdfVector3_t *)&aWork->X, 0);
  Draw_AnimObj(aWork);
}
