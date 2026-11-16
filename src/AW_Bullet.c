#include "types.h"
#include "aw.h"
#include "aw_bullet.h"
#include "aw_bulletsmokep.h"
#include "aw_bulletsmoket.h"
#include "aw_hits.h"
#include "dds3kerneldraw.h"
#include "dds3vrf.h"
#include "sbtl.h"
#include "sbtlscene.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e2eea0
void Init(void) {
  ;
}

// 0x1e2eeb0
s32 Add(f32 _SX, f32 _SY, f32 _SZ, f32 _SDir, s32 _TargetListID, s32 _SubIdx) {
  f32 Dir180;
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 v16;
  f32 x;
  f32 y;
  f32 v20;
  f32 v21;
  f32 z;
  f32 w;
  Il2CppObject *v24;
  AW_Func v25;
  AW_Func v27;
  s32 v30;
  AW_WORK_t *v32;
  u32 v33;
  f32 Dir;
  f32 v35;
  f32 PosToDir;
  f32 v39;
  f32 v40;
  s32 v41;
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v45;
  f32 StepOfsZ;
  f32 v48;
  s64 v49;
  f32 v50;
  f32 v51;
  f32 DirY;
  f32 MoveSpd;
  u64 v54;
  f32 v55;
  f32 v56;
  f32 HomingZ;
  f32 v59;
  f32 v60;
  f32 v61;
  f32 v62;
  f32 v63;
  s32 v64;
  char *v65;
  sdfVector3_t v67;
  sdfVector3_t v68;
  sdfQuaternion_t v69;

  v67.z = 0.0;
  *(u64 *)&v67.x = 0;
  Dir180 = sBtlGetDir180(SDir);
  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 5, 0);
  v16 = SX / -100.0;
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  v20 = SY / -100.0;
  v21 = SZ / -100.0;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v68.x = v16;
  v68.y = v20;
  v68.z = v21;
  v69.x = x;
  v69.y = y;
  v69.z = z;
  v69.w = w;
  v24 = Instantiate_object__39504752(AwPrefab, v68, v69);
  v25 = Allocate(AW_Func);
  _ctor(v25, 0);
  v27 = Allocate(AW_Func);
  _ctor(v27, 0);
  v30 = Add(400, v16, v20, v21, v24, v25, v27, 1);
  v32 = gWork[v30];
  v32->Unit_ListID = TargetListID;
  v32->Dir = Dir180;
  v33 = sub_1905740(30, 0);
  Dir = v32->Dir;
  v32->DirY = 0.0;
  v32->Dir = Dir + (f32)((f32)v33 + -15.0);
  v35 = (f32)(u32)sub_1905740(20, 0) + -15.0;
  v32->DirY = v32->DirY + v35;
  PosToDir = sBtlGetPosToDir(CameraTargetPos.x, CameraTargetPos.z, CameraEyePos.x, CameraEyePos.z);
  v32->StepOfsY = 0.1;
  v39 = PosToDir;
  switch (SubIdx)
  {
    case 0:
      v40 = 0.0;
      sBtlGetMoveXZ(0.0, 0.0, v39 + 0.0, 0.3, &v32->StepOfsX, &v32->StepOfsZ);
      goto LABEL_37;
    case 1:
      sBtlGetMoveXZ(0.0, 0.0, v39 + -20.0, 0.3, &v32->StepOfsX, &v32->StepOfsZ);
      *(f32 *)&v41 = 0.4;
      goto LABEL_36;
    case 2:
      sBtlGetMoveXZ(0.0, 0.0, v39 + -60.0, 0.3, &v32->StepOfsX, &v32->StepOfsZ);
      *(f32 *)&v41 = -0.1;
      goto LABEL_36;
    case 3:
      sBtlGetMoveXZ(0.0, 0.0, v39 + 60.0, 0.3, &v32->StepOfsX, &v32->StepOfsZ);
      *(f32 *)&v41 = -0.2;
      goto LABEL_36;
    case 4:
      sBtlGetMoveXZ(0.0, 0.0, v39 + 30.0, 0.3, &v32->StepOfsX, &v32->StepOfsZ);
      *(f32 *)&v41 = -0.4;
      goto LABEL_36;
    case 5:
      sBtlGetMoveXZ(0.0, 0.0, v39 + 45.0, 0.3, &v32->StepOfsX, &v32->StepOfsZ);
      *(f32 *)&v41 = -0.3;
LABEL_36:
      v40 = *(f32 *)&v41;
LABEL_37:
      v32->StepOfsY = (f32)(v32->StepOfsY + v40) + 0.1;
      break;
    default:
      break;
  }
  Unit_ListID = v32->Unit_ListID;
  UnitMng = wk->UnitMng;
  v45 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  if (v45)
  {
    if (v45->para->devilid == 257)
    {
      StepOfsZ = v32->StepOfsZ;
      v32->StepOfsX = v32->StepOfsX * 0.3;
      v48 = v32->StepOfsY * 0.3;
      v32->StepOfsZ = StepOfsZ * 0.3;
      v32->StepOfsY = v48 + 0.15;
    }
  }
  v49 = *(u64 *)&v32->X;
  v50 = v32->Z;
  v32->MoveLen = 0.0;
  v32->DirIKY = 0.0;
  v32->MoveSpd = 2.0;
  *(u64 *)&v32->HomingX = v49;
  v32->HomingZ = v50;
  GetTargetPos(v32, &v32->HomingX, &v32->HomingY, &v32->HomingZ);
  v67.z = 0.0;
  *(u64 *)&v67.x = 0;
  v51 = v32->Dir;
  DirY = v32->DirY;
  GetDirToVec(v51, DirY, &v67);
  MoveSpd = v32->MoveSpd;
  v54 = vmul_n_f32(*(float32x2_t *)&v67.x, MoveSpd).n64_u64[0];
  v55 = MoveSpd * v67.z;
  v56 = v32->X;
  HomingZ = v32->HomingZ;
  *(u64 *)&v32->VelocityX = v54;
  v32->VelocityZ = v55;
  v59 = sBtlGetLenXZ(v56, v32->Z, v32->HomingX, HomingZ) / 1.5;
  if (v59 < 4.0)
    v59 = 4.0;
  if (v59 > 12.0)
    v59 = 12.0;
  v60 = v32->Z;
  v61 = FPS60 * v59;
  v62 = v32->X;
  v63 = v32->Y;
  v32->HomingFrame = v61;
  v64 = Add(v62, v63, v60);
  v65 = "AW_Bullet";
  v32->Child_AW_Idx = v64;
  v32->DbgStr = v65;
  return v30;
}

// 0x1e2f9f0
void Delete(AW_WORK_t *aWork) {
  s32 Idx;
  s32 v6;

  Idx = aWork->Idx;
  v6 = Idx;
  DelAW(v6, 1);
}

// 0x1e2f600
void GetTargetPos(AW_WORK_t *aWork, f32 *_TgtX, f32 *_TgtY, f32 *_TgtZ) {
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v12;
  SBTLUNIT_WORK *v13;
  f32 z;
  f32 v16;
  f32 v17;
  sdfVector4_t v18;

  *TgtX = aWork->HomingX;
  *TgtY = aWork->HomingY;
  *TgtZ = aWork->HomingZ;
  Unit_ListID = aWork->Unit_ListID;
  UnitMng = wk->UnitMng;
  v12 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  if (!v12)
    return;
  v13 = v12;
  *(u64 *)&v18.x = 0;
  *(u64 *)&v18.z = 0;
  GetUnitHelperPos(v13, &v18);
  z = v18.z;
  v16 = v18.y / 100.0;
  *TgtX = aWork->StepOfsX - (f32)(v18.x / 100.0);
  *TgtY = aWork->StepOfsY - v16;
  *TgtZ = aWork->StepOfsZ - (f32)(z / 100.0);
  v17 = 0.4 - (f32)(v13->pos.y / 100.0);
  if (*TgtY < v17)
    *TgtY = v17;
}

// 0x1e2fa80
void Calc(AW_WORK_t *aWork) {
  f32 HomingX;
  s32 Step;
  f32 X;
  f32 Y;
  f32 Z;
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  int32x2_t v13;
  float32x2_t v14;
  f32 v15;
  f32 v16;
  f32 HomingFrame;
  f32 VelocityZ;
  float32x2_t v19;
  float32x2_t v20;
  f32 v21;
  f32 v23;
  s32 v25;
  SBTLUNIT_LISTWORK *v26;
  SBTLUNIT_WORK *v27;
  f32 Dir;
  f32 v29;
  SBTLUNIT_WORK *v30;
  f32 PosToDir;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v37;
  s32 Idx;
  s32 v39;
  SBTLUNIT_LISTWORK *v40;
  SBTLUNIT_WORK *v41;
  f32 v42;
  f32 v43;
  f32 v44;
  f32 v46;
  f32 v47;
  f32 LenXZ;
  f32 v50;
  s64 Child_AW_Idx;
  f32 v52;
  AW_WORK_t *v54;
  float32x2_t v57;
  float32x2_t v58;
  float32x2_t v59;
  f32 v60;
  float32x2_t v61;
  f32 v62;
  float32x2_t v63;
  float32x2_t v64;
  float32x2_t v65;
  f32 v66;
  f32 v67;
  u32 v68;
  u64 v69;
  u32 v70;
  f32 ToZ;
  f32 ToX;
  f32 TgtZ;
  f32 TgtY;
  f32 TgtX;

  ToZ = 0.0;
  ToX = 0.0;
  HomingX = aWork->HomingX;
  TgtY = aWork->HomingY;
  TgtX = HomingX;
  Step = aWork->Step;
  X = aWork->X;
  Y = aWork->Y;
  TgtZ = aWork->HomingZ;
  Z = aWork->Z;
  switch (Step)
  {
    case 0:
      Unit_ListID = aWork->Unit_ListID;
      UnitMng = wk->UnitMng;
      if (!sBtlSearchUnit_ID(UnitMng, Unit_ListID))
      {
        *(u64 *)&aWork->Step = 10;
        goto LABEL_31;
      }
      GetTargetPos(aWork, &TgtX, &TgtY, &TgtZ);
      v15 = TgtY;
      v14.n64_f32[0] = TgtX;
      v16 = TgtZ;
      aWork->HomingX = TgtX;
      aWork->HomingY = v15;
      HomingFrame = aWork->HomingFrame;
      VelocityZ = aWork->VelocityZ;
      v19.n64_u64[0] = *(u64 *)&aWork->VelocityX;
      v20.n64_u64[0] = *(u64 *)&aWork->X;
      aWork->HomingZ = v16;
      v21 = aWork->Z;
      v66 = HomingFrame;
      v67 = v15;
      v68 = v14.n64_u32[0];
      v69 = v19.n64_u64[0];
      HomingFrame = v66;
      v15 = v67;
      v14.n64_u32[0] = v68;
      v19.n64_u64[0] = v69;
      v23 = HomingFrame - VRF_DeltaTime;
      if ((f32)(HomingFrame - VRF_DeltaTime) >= 0.0)
      {
        v14.n64_f32[1] = v15;
        v13.n64_f32[0] = HomingFrame * HomingFrame;
        v57.n64_u64[0] = __PAIR64__(v19.n64_u32[1], LODWORD(HomingFrame));
        v58.n64_u64[0] = vsub_f32(v14, v20).n64_u64[0];
        v59.n64_u64[0] = __PAIR64__(LODWORD(HomingFrame), v19.n64_u32[0]);
        v60 = VelocityZ
            + (f32)(VRF_DeltaTime * (f32)((f32)((f32)((f32)((f32)(v16 - v21) - (f32)(HomingFrame * VelocityZ)) + (f32)((f32)(v16 - v21) - (f32)(HomingFrame * VelocityZ))) / (f32)(HomingFrame * HomingFrame)) + zeroVector.z));
        v61.n64_u64[0] = vsub_f32(v58, vmul_f32(v59, v57)).n64_u64[0];
        v62 = v21 + (f32)(VRF_DeltaTime * v60);
        v63.n64_u64[0] = *(u64 *)&zeroVector.x;
        aWork->VelocityZ = v60;
        aWork->HomingFrame = v23;
        aWork->Z = v62;
        v64.n64_u64[0] = vadd_f32(v19, vmul_n_f32(vadd_f32(vdiv_f32(vadd_f32(v61, v61), vdup_lane_s32(v13, 0)), v63), VRF_DeltaTime)).n64_u64[0];
        *(float32x2_t *)&aWork->VelocityX = v64;
        v65.n64_u64[0] = vadd_f32(v20, vmul_n_f32(v64, VRF_DeltaTime)).n64_u64[0];
        *(float32x2_t *)&aWork->X = v65;
        v70 = v65.n64_u32[0];
        v65.n64_u32[0] = v70;
        aWork->Dir = sBtlGetPosToDir(X, Z, v65.n64_f32[0], v62);
      }
      else
      {
        LODWORD(aWork->X) = v14.n64_u32[0];
        aWork->Y = v15;
        *(u64 *)&aWork->Step = 2;
        aWork->Z = v16;
        v25 = aWork->Unit_ListID;
        v26 = wk->UnitMng;
        v27 = sBtlSearchUnit_ID(v26, v25);
        Dir = aWork->Dir;
        v29 = sBtlGet360(Dir + 180.0);
        v30 = sBtlSearchUnit_ID(wk->UnitMng, wk->playerID);
        PosToDir = sBtlGetPosToDir(aWork->X, aWork->Z, v30->pos.x / -100.0, v30->pos.z / -100.0);
        if (!v27 || v27->para->devilid != 257)
        {
LABEL_31:
          goto LABEL_33;
        }
        v32 = PosToDir;
        v33 = aWork->X;
        v34 = aWork->Z;
        sBtlGetMoveXZ(v33, v34, v32, 0.8, &ToX, &ToZ);
        Add_Hajiki(aWork->Unit_ListID, ToX, aWork->Y, ToZ, v29);
      }
LABEL_33:
      v39 = aWork->Unit_ListID;
      v40 = wk->UnitMng;
      v41 = sBtlSearchUnit_ID(v40, v39);
      if (v41)
      {
        v42 = v41->pos.x;
        v43 = v41->pos.z;
        v44 = sBtlGetGroundPos(v42, v43) / -100.0;
        v46 = aWork->X;
        v47 = aWork->Z;
        goto LABEL_39;
      }
      v44 = 0.0;
      v46 = aWork->X;
      v47 = aWork->Z;
LABEL_39:
      LenXZ = sBtlGetLenXZ(X, Z, v46, v47);
      if (LenXZ > 0.01)
      {
        v52 = aWork->Y;
        aWork->DirIKY = sBtlGetPosToDir(v44, Y, LenXZ, v52);
        v50 = LenXZ + aWork->MoveLen;
        aWork->MoveLen = v50;
        if (v50 <= 2.0)
        {
LABEL_41:
          Child_AW_Idx = aWork->Child_AW_Idx;
          if ((u32)Child_AW_Idx == -1)
            return;
          goto LABEL_47;
        }
      }
      else
      {
        v50 = LenXZ + aWork->MoveLen;
        aWork->MoveLen = v50;
        if (v50 <= 2.0)
          goto LABEL_41;
      }
      aWork->MoveLen = v50 + -2.0;
      Add(X, Y, Z);
      Child_AW_Idx = aWork->Child_AW_Idx;
      if ((u32)Child_AW_Idx == -1)
        return;
LABEL_47:
      v54 = gWork[Child_AW_Idx];
      *(u64 *)&v54->X = *(u64 *)&aWork->X;
      v54->Z = aWork->Z;
      return;
    case 1:
    case 2:
      goto LABEL_24;
    case 10:
      v37 = aWork->StepTime + VRF_DeltaTime;
      aWork->StepTime = v37;
      if (v37 <= (f32)(FPS60 * 15.0))
        goto LABEL_31;
LABEL_24:
      Idx = aWork->Idx;
      DelAW(Idx, 1);
      return;
    default:
      goto LABEL_31;
  }
}

// 0x1e303b0
void Draw(AW_WORK_t *aWork) {
  void *transform;
  void *v4;
  sdfVector3_t v5;

  transform = get_transform(aWork->Obj, 0);
  set_localPosition(transform, *(sdfVector3_t *)&aWork->X, 0);
  v4 = get_transform(aWork->Obj, 0);
  v5.x = aWork->DirIKY;
  v5.z = 0.0;
  v5.y = aWork->Dir;
  set_eulerAngles(v4, v5, 0);
}
