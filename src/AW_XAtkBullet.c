#include "types.h"
#include "aw.h"
#include "aw_sbattle.h"
#include "aw_xatkblast.h"
#include "aw_xatkbullet.h"
#include "aw_xatkbullethit.h"
#include "aw_xatkgunimpct.h"
#include "aw_xatklaser.h"
#include "aw_xatkpoison.h"
#include "aw_xatksight.h"
#include "aw_xatksmoke.h"
#include "dds3kerneldraw.h"
#include "dds3vrf.h"
#include "sbtl.h"
#include "sbtldmg.h"
#include "sbtleff.h"
#include "sbtlmain.h"
#include "sbtlplayer.h"
#include "sbtlplayerfoot.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;
typedef struct AW_XAtk_WORK_t AW_XAtk_WORK_t;

AW_XAtk_WORK_t *ArgumentParam;
static bool gBioArmFlip;

static bool SetHit(AW_WORK_t *aWork, f32 _Size);
static void SetHit_BioArm(AW_WORK_t *aWork, f32 _Size);

// 0x1e84ec0
void Init(void) {
  ;
}

// 0x1e84ed0
s32 Add(void) {
  u32 v4;
  s32 v5;
  void *Instance;
  Il2CppObject *AwPrefab;
  AW_XAtk_WORK_t *v10;
  f32 X;
  f32 Y;
  f32 Z;
  f32 v15;
  f32 v16;
  f32 w;
  f32 v18;
  Il2CppObject *v19;
  f32 *v20;
  f32 v21;
  f32 v22;
  f32 v23;
  AW_Func v24;
  AW_Func v25;
  s32 v26;
  AW_WORK_t *AW;
  AW_XAtk_WORK_t *v28;
  f32 Dir;
  s64 v30;
  s64 v31;
  __int128 v32;
  f32 DirY;
  f32 MoveSpd;
  AW_XAtk_WORK_t *v36;
  f32 v38;
  f32 v39;
  f32 v41;
  int32x2_t v42;
  s32 *StepIntBuff;
  s32 Variation;
  s32 *v46;
  f32 v48;
  f32 v49;
  s32 *v50;
  s32 *v53;
  s32 *v54;
  u32 StepFlag;
  f32 v57;
  f32 v58;
  f32 v59;
  f32 v60;
  s32 Group_AW_Idx;
  s32 Group_AW_UID;
  f32 v63;
  f32 v64;
  f32 v65;
  f32 HomingZ;
  f32 HomingX;
  f32 HomingY;
  f32 v69;
  f32 v70;
  f32 v71;
  f32 v72;
  char *v73;
  sdfVector3_t v74;
  sdfVector3_t v75;
  sdfQuaternion_t v76;

  v74.z = 0.0;
  *(u64 *)&v74.x = 0;
  if ((ArgumentParam->Flag & 0x1000) == 0)
  {
    v4 = ArgumentParam->Variation - 1;
    if (v4 <= 3)
    {
      v5 = dword_3D06CC0[v4];
      goto LABEL_14;
    }
    v5 = 98;
LABEL_14:
    Instance = get_Instance(0);
    AwPrefab = GetAwPrefab(Instance, v5, 0);
    v10 = ArgumentParam;
    if ((v10->Flag & 1) == 0)
    {
      X = v10->X;
      Y = v10->Y;
      Z = v10->Z;
      v15 = identityQuaternion.x;
      v16 = identityQuaternion.y;
      v18 = identityQuaternion.z;
      w = identityQuaternion.w;
      v75.x = X;
      v75.y = Y;
      v75.z = Z;
      v76.x = v15;
      v76.y = v16;
      v76.z = v18;
      v76.w = w;
      v19 = Instantiate_object__39504752(AwPrefab, v75, v76);
      goto LABEL_25;
    }
    v19 = 0;
LABEL_25:
    v20 = ArgumentParam;
    v21 = v20[7];
    v22 = v20[8];
    v23 = v20[9];
    v24 = Allocate(AW_Func);
    _ctor(v24, 0, Method_Project_AW_XAtkBullet_Calc__, 0);
    v25 = Allocate(AW_Func);
    _ctor(v25, 0, Method_Project_AW_XAtkBullet_Draw__, 0);
    v26 = Add(251, v21, v22, v23, v19, v24, v25, 1);
    AW = GetAW(v26);
    v28 = ArgumentParam;
    Dir = v28->Dir;
    v30 = *(u64 *)&v28->Unit_ListID;
    AW->Dir = Dir;
    *(u64 *)&AW->Unit_ListID = v30;
    v31 = *(u64 *)&v28->MoveSpdRate;
    AW->MoveLen = 0.0;
    AW->Variation = v28->Variation;
    *(u64 *)&AW->MoveSpdRate = v31;
    v32 = *(_OWORD *)&v28->Scale;
    *(u64 *)&AW->Step = 0;
    *(_OWORD *)&AW->Scale = v32;
    *(u64 *)&v32 = *(u64 *)&v28->Flag;
    DirY = v28->DirY;
    v74.z = 0.0;
    *(u64 *)&v74.x = 0;
    *(u64 *)&AW->StepFlag = v32;
    *(u64 *)&v32 = *(u64 *)&v28->Group_AW_Idx;
    AW->DirY = DirY;
    *(u64 *)&AW->Group_AW_Idx = v32;
    *(u64 *)&AW->HomingX = *(u64 *)&v28->HomingX;
    AW->HomingZ = v28->HomingZ;
    GetDirToVec(Dir, DirY, &v74);
    MoveSpd = AW->MoveSpd;
    v36 = ArgumentParam;
    *(float32x2_t *)&AW->VelocityX = vmul_n_f32(*(float32x2_t *)&v74.x, MoveSpd);
    v38 = v74.z;
    AW->StepOfsZ = 0.0;
    AW->StepBoolA = 0;
    v39 = MoveSpd * v38;
    AW->VelocityZ = v39;
    v41 = v36->HomingFrame * FPS60;
    v42.n64_u64[0] = *(u64 *)&v36->SklID;
    StepIntBuff = AW->StepIntBuff;
    AW->StepIntC = 0;
    AW->HomingFrame = v41;
    *(int32x2_t *)&AW->StepIntA = vrev64_s32(v42);
    *(u64 *)StepIntBuff = -1;
    StepIntBuff[2] = -1;
    Variation = AW->Variation;
    *(u64 *)&AW->StepFloatA = 0;
    *(u64 *)&AW->StepOfsX = 0;
    if (Variation == 2)
    {
      if (wk->encountno == 60)
      {
        Set_HDEff(v26, 1, -1);
        *(u64 *)&AW->HDEff_Speed = 0x3F8000003F800000LL;
      }
    }
    else if (Variation == 1)
    {
      Set_HDEff(v26, 1, -1);
      *(u64 *)&AW->HDEff_Speed = 0x3F8000003F800000LL;
      if ((AW->StepFlag & 0x4000) != 0)
      {
        if ((AW->StepFlag2 & 0x40) != 0)
        {
          v53 = AW->StepIntBuff;
          v53[1] = AW_XAtkBulletAdd(AW->X, AW->Y, AW->Z);
        }
      }
      else
      {
        v46 = AW->StepIntBuff;
        v47 = AW_XAtkBulletAdd(AW->X, AW->Y, AW->Z);
        v48 = AW->X;
        v49 = AW->Y;
        v46[1] = (s32)v47;
        v50 = AW->StepIntBuff;
        v50[2] = AW_XAtkBulletAdd(v48, v49, AW->Z);
      }
    }
    if ((AW->StepFlag & 4) != 0)
    {
      v54 = AW->StepIntBuff;
      v54[0] = Add(AW->HomingX, AW->HomingY + 0.01, AW->HomingZ, AW->Dir, 0);
      if (wk->encountno == 60)
      {
        AW->Step = 300;
        AW->StepTime = FPS60 * 40.0;
      }
    }
    StepFlag = AW->StepFlag;
    if ((StepFlag & 8) != 0 && !AW->StepIntA)
    {
      v57 = AW->X;
      v58 = AW->Y;
      v59 = AW->Z;
      v60 = AW->Dir;
      Group_AW_Idx = AW->Group_AW_Idx;
      Group_AW_UID = AW->Group_AW_UID;
      if ((StepFlag & 0x10) != 0)
        Add(v57, v58, v59, v60, Group_AW_Idx, Group_AW_UID);
      else
        AW_XAtkAdd2(v57, v58, v59, v60, Group_AW_Idx, Group_AW_UID);
    }
    if ((AW->StepFlag2 & 1) != 0)
    {
      v63 = AW->Z;
      v64 = AW->X;
      v65 = AW->Y;
      HomingZ = AW->HomingZ;
      HomingX = AW->HomingX;
      HomingY = AW->HomingY;
      sBtlGetPosToVec(v64, v65, v63, HomingX, HomingY, HomingZ, &AW->VelocityX, &AW->VelocityY, &AW->VelocityZ);
      v69 = AW->Z;
      v70 = AW->X;
      v71 = AW->Y;
      v72 = AW->HomingZ;
      AW->DirY = AW->VelocityY * 90.0;
      AW->StepFloatB = sBtlGetLenXYZ(v70, v71, v69, AW->HomingX, AW->HomingY, v72);
    }
    v73 = "AW_XAtkBullet";
    AW->DbgStr = "AW_XAtkBullet";
    return v26;
  }
  return AW_XAtkAdd_BioArm_Top();
}

// 0x1e86310
void Delete(AW_WORK_t *aWork) {
  s32 *StepIntBuff;
  s32 v4;
  AW_WORK_t *AW;
  s32 v6;
  AW_WORK_t *v7;
  s32 Idx;
  s32 v10;
  AW_WORK_t *v11;
  s32 v13;
  s32 v14;

  StepIntBuff = aWork->StepIntBuff;
  v4 = StepIntBuff[0];
  if (v4 != -1)
  {
    AW = GetAW(v4);
    Delete(AW);
    StepIntBuff = aWork->StepIntBuff;
    StepIntBuff[0] = -1;
  }
  v6 = StepIntBuff[1];
  if (v6 != -1)
  {
    v7 = GetAW(v6);
    Idx = v7->Idx;
    DelAW(Idx, 1);
    StepIntBuff = aWork->StepIntBuff;
    StepIntBuff[1] = -1;
    goto LABEL_12;
  }
LABEL_12:
  v10 = StepIntBuff[2];
  if (v10 != -1)
  {
    v11 = GetAW(v10);
    v13 = v11->Idx;
    DelAW(v13, 1);
    aWork->StepIntBuff[2] = -1;
  }
  v14 = aWork->Idx;
  DelAW(v14, 1);
}

// 0x1e86580
static bool SetHit(AW_WORK_t *aWork, f32 _Size) {
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v8;
  u32 status;
  bool result;
  bool IsSceanStop;
  f32 v14;
  f32 v15;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  SBATTLE_WORK *v23;
  SBTLUNIT_LISTWORK *v24;
  s32 playerID;
  SBTLUNIT_WORK *v26;
  bool v27;
  s64 v28;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  s32 v36;
  AW_WORK_t *v37;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 v41;
  f32 v42;
  f32 v43;
  f32 v44;
  s32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 y;
  f32 ABS;
  u32 StepFlag2;
  f32 v54;
  f32 v55;
  f32 v56;
  f32 x;
  f32 z;
  s32 StepIntB;
  f32 v60;
  f32 v61;
  f32 w;
  f32 v63;
  s32 v66;
  AW_WORK_t *AW;
  f32 v68;
  f32 v69;
  s32 v70;
  f32 v71;
  f32 v72;
  f32 v73;
  f32 v74;
  f32 v75;
  f32 v76;
  f32 v77;
  f32 v79;
  f32 v80;
  sdfVector4_t v81;
  sdfVector4_t v82;
  sdfVector4_t v83;

  Unit_ListID = aWork->Unit_ListID;
  UnitMng = wk->UnitMng;
  v8 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  status = wk->status;
  if ((status & 0x1000000) != 0)
    return 0;
  if ((status & 0x2000000) != 0)
    return 0;
  if (sBtlCheckPlayerDead())
    return 0;
  if (wk->enemy_zenmetu)
    return 0;
  if (wk->mode != 2)
  {
    if (!v8)
      return 0;
    goto LABEL_30;
  }
  IsSceanStop = IsSceanStop();
  result = 0;
  if (!IsSceanStop && v8)
  {
LABEL_30:
    if (v8->UID == aWork->Unit_UID)
    {
      v14 = aWork->X + aWork->StepOfsX;
      v15 = aWork->Y + aWork->StepOfsY;
      v17 = aWork->Z + aWork->StepOfsZ;
      v18 = v14 * -100.0;
      v19 = v15 * -100.0;
      v20 = v17 * -100.0;
      v21 = 20.0;
      if (gHitDonePlayer)
        goto LABEL_41;
      v23 = wk;
      v24 = v23->UnitMng;
      playerID = v23->playerID;
      v26 = sBtlSearchUnit_ID(v24, playerID);
      if (sBtlCheckIsDamage(v26))
      {
LABEL_41:
        v27 = 0;
      }
      else
      {
        y = v26->pos.y;
        ABS = sBtlGetABS(v19 - y);
        StepFlag2 = aWork->StepFlag2;
        if ((StepFlag2 & 0x80) != 0)
          v54 = 200.0;
        else
          v54 = 100.0;
        if ((StepFlag2 & 0x80) != 0)
          v55 = 0.0;
        else
          v55 = 20.0;
        if ((StepFlag2 & 0x100) != 0)
        {
          if (sBtlChkNowJumpOver(v26, -100.0))
          {
            v54 = 0.0;
            v55 = 0.0;
          }
        }
        v56 = v26->pos.y;
        if (v19 >= v56 && ABS < v55 || (v27 = 0, v19 < v56) && ABS < v54)
        {
          x = v26->pos.x;
          z = v26->pos.z;
          if (sBtlGetLenXZ(v18, v20, x, z) >= Size)
          {
            v27 = 0;
          }
          else
          {
            StepIntB = aWork->StepIntB;
            v60 = v26->pos.x;
            v61 = v26->pos.y;
            v63 = v26->pos.z;
            w = v26->pos.w;
            v82.x = v60;
            v82.y = v61;
            v82.z = v63;
            v82.w = w;
            SetDamageProc(v26, v8, StepIntB, v82);
            v21 = 20.0;
            v27 = 1;
            gHitDonePlayer = 1;
          }
        }
        if (!gHitDonePlayer)
        {
          v66 = aWork->StepIntBuff[1];
          if (v66 != -1)
          {
            AW = GetAW(v66);
            v68 = v26->pos.x;
            v18 = AW->X * -100.0;
            v69 = v26->pos.z;
            v20 = AW->Z * -100.0;
            if (sBtlGetLenXZ(v18, v20, v68, v69) < Size)
            {
              v80 = v20;
              v70 = aWork->StepIntB;
              v71 = v26->pos.x;
              v72 = v26->pos.y;
              v73 = v18;
              v74 = v19;
              v75 = v21;
              v77 = v26->pos.z;
              v76 = v26->pos.w;
              v83.x = v71;
              v83.y = v72;
              v83.z = v77;
              v83.w = v76;
              SetDamageProc(v26, v8, v70, v83);
              v21 = v75;
              v19 = v74;
              v18 = v73;
              v20 = v80;
              v27 = 1;
              gHitDonePlayer = 1;
            }
          }
        }
      }
      v28 = 32;
      while (1)
      {
        Nakama = sBtlGetNakama((u8)v28 - 32);
        if (Nakama)
        {
          v30 = Nakama;
          if (!*((u8 *)&gHitDoneNakama->obj.klass + v28))
          {
            if (!v30->L2_muteki)
            {
              v31 = v30->pos.y;
              v32 = sBtlGetABS(v19 - v31);
              v33 = 200.0;
              if ((aWork->StepFlag2 & 0x80) == 0)
                v33 = v21;
              if (v32 < v33)
              {
                v34 = v30->pos.x;
                v35 = v30->pos.z;
                if (sBtlGetLenXZ(v18, v20, v34, v35) < Size)
                  goto LABEL_63;
              }
              v36 = aWork->StepIntBuff[1];
              if (v36 != -1)
              {
                v37 = GetAW(v36);
                v38 = v37->X;
                v39 = v37->Z;
                v40 = v30->pos.x;
                v41 = v30->pos.z;
                v18 = v38 * -100.0;
                v20 = v39 * -100.0;
                if (sBtlGetLenXZ(v18, v20, v40, v41) < Size)
                {
LABEL_63:
                  v79 = v20;
                  v42 = v18;
                  v43 = v19;
                  v44 = v21;
                  v45 = aWork->StepIntB;
                  v46 = v30->pos.x;
                  v47 = v30->pos.y;
                  v48 = v30->pos.z;
                  v49 = v30->pos.w;
                  v81.x = v46;
                  v81.y = v47;
                  v81.z = v48;
                  v81.w = v49;
                  SetDamageProc(v30, v8, v45, v81);
                  v21 = v44;
                  v19 = v43;
                  v18 = v42;
                  v20 = v79;
                  v27 = 1;
                  *((u8 *)&gHitDoneNakama->obj.klass + v28) = 1;
                }
              }
            }
          }
        }
        if (++v28 == 34)
          return v27;
      }
    }
    return 0;
  }
  return result;
}

// 0x1e86d40
void Calc(AW_WORK_t *aWork) {
  AW_WORK_t *AW;
  f32 X;
  s32 Step;
  f32 Z;
  void *ParticleSystemList;
  f32 v10;
  __int128 v11;
  Il2CppObject *v12;
  f32 v13;
  f32 StepTime;
  f32 v18;
  f32 v19;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 Unit_ListID;
  SBTLUNIT_WORK *v23;
  SBTLUNIT_WORK *v24;
  s32 Group_AW_Idx;
  AW_WORK_t *v26;
  f32 v27;
  f32 v28;
  f32 Dir;
  f32 MoveLen;
  float32x2_t v31;
  f32 v32;
  f32 MoveSpd;
  f32 MoveDir;
  f32 MoveSpdMax;
  f32 v36;
  f32 v37;
  f32 v39;
  f32 Y;
  f32 v41;
  AW_WORK_t *v42;
  f32 v43;
  __int128 v44;
  Il2CppObject *current;
  f32 HDEff_SimSpeed;
  float32x2_t v47;
  f32 v48;
  f32 v49;
  f32 PopX;
  f32 PopZ;
  f32 PosToDir;
  f32 LenXZ;
  f32 v54;
  s32 *StepIntBuff;
  s32 v56;
  AW_WORK_t *v57;
  f32 v58;
  s32 v59;
  f32 HomingFrame;
  f32 VelocityZ;
  f32 v62;
  float32x2_t v63;
  float32x2_t v64;
  float32x2_t v65;
  f32 HomingZ;
  f32 v68;
  f32 v69;
  f32 v70;
  char v71;
  u32 v72;
  int32x2_t v73;
  f32 v75;
  float32x2_t v76;
  float32x2_t v77;
  f32 v78;
  float32x2_t v79;
  f32 v80;
  f32 v81;
  f32 v82;
  f32 v83;
  f32 v84;
  f32 v85;
  f32 v86;
  f32 v87;
  f32 v88;
  s32 StepIntC;
  s32 v90;
  f32 StepFloatA;
  s32 *v92;
  s32 v93;
  AW_WORK_t *v94;
  f32 v95;
  AW_WORK_t *v96;
  f32 v97;
  f32 v98;
  s32 v99;
  AW_WORK_t *v100;
  f32 v101;
  AW_WORK_t *v102;
  f32 v103;
  f32 v104;
  f32 v105;
  u32 StepFlag2;
  u32 v107;
  f32 v108;
  u32 v109;
  f32 v110;
  f32 HomingX;
  f32 HomingY;
  f32 v113;
  s32 StepIntB;
  f32 v115;
  u32 StepFlag;
  f32 v118;
  f32 v119;
  f32 v120;
  s32 v121;
  f32 v122;
  f32 v123;
  f32 ToX;
  u32 ToXa;
  f32 ToXb;
  f32 v128;
  u64 v129;
  System_Collections_Generic_List_Enumerator_T__o v130;
  void *v131;
  void *m_ParticleSystem;
  System_Collections_Generic_List_Enumerator_T__o v133;
  s64 ToZ;
  UnityEngine_ParticleSystem_MainModule_o v135;
  UnityEngine_ParticleSystem_MainModule_o v136;
  sdfVector4_t v137;
  sdfVector4_t v138;
  sdfVector4_t v139;
  sdfVector4_t v140;
  sdfVector4_t v141;

  ToZ = 0;
  memset(&v133, 0, sizeof(v133));
  v131 = 0;
  m_ParticleSystem = 0;
  AW = ChkPause(aWork);
  if (((u8)AW & 1) != 0)
    return;
  X = aWork->X;
  Step = aWork->Step;
  Z = aWork->Z;
  if (Step <= 101)
  {
    if (Step > 99)
    {
      if (Step != 100)
        goto LABEL_25;
      v39 = aWork->StepTime + VRF_DeltaTime;
      aWork->StepTime = v39;
      if (v39 <= (f32)(FPS60 * 120.0))
        goto LABEL_181;
      if (!aWork->StepBoolA)
      {
        Y = aWork->Y;
        aWork->StepBoolA = 1;
        v41 = Y * -100.0;
        v138.w = 0.0;
        v138.x = X * -100.0;
        v138.y = v41;
        v138.z = Z * -100.0;
        sBtlPlay3DSE(0x10097u, v138);
      }
      v42 = aWork;
      v43 = 200.0;
      goto LABEL_73;
    }
    if (Step)
    {
      if (Step == 1)
        goto LABEL_25;
LABEL_181:
      if (aWork->Variation != 1)
        return;
      goto LABEL_182;
    }
    if ((aWork->StepFlag & 0x10) != 0)
    {
      Group_AW_Idx = aWork->Group_AW_Idx;
      AW = GetAW(Group_AW_Idx);
      if (AW)
      {
        v26 = AW;
        if (AW->UID == aWork->Group_AW_UID)
        {
          v27 = AW->X;
          v28 = AW->Z;
          Dir = AW->Dir;
          MoveLen = aWork->MoveLen;
          sBtlGetMoveXZ(v27, v28, Dir, MoveLen, &aWork->X, &aWork->Z);
          aWork->Dir = v26->Dir;
          aWork->MoveDir = v26->Dir;
        }
      }
    }
    v31.n64_u32[0] = LODWORD(aWork->X);
    v32 = aWork->Z;
    MoveSpd = aWork->MoveSpd;
    if ((aWork->StepFlag2 & 1) != 0)
    {
      v47.n64_u64[0] = vmul_n_f32(*(float32x2_t *)&aWork->VelocityX, MoveSpd).n64_u64[0];
      v48 = MoveSpd * aWork->VelocityZ;
      v31.n64_u32[1] = LODWORD(aWork->Y);
      v49 = MoveSpd + aWork->MoveSpdRate;
      MoveSpdMax = aWork->MoveSpdMax;
      aWork->MoveLen = MoveSpd + aWork->MoveLen;
      v31.n64_u64[0] = vadd_f32(v31, v47).n64_u64[0];
      v32 = v32 + v48;
      aWork->MoveSpd = v49;
      *(float32x2_t *)&aWork->X = v31;
      aWork->Z = v32;
      if (v49 <= MoveSpdMax)
        goto LABEL_84;
    }
    else
    {
      if ((aWork->StepFlag & 0x40) != 0)
        goto LABEL_84;
      MoveDir = aWork->MoveDir;
      v128 = aWork->MoveSpd;
      ToX = aWork->X;
      v31.n64_f32[0] = ToX;
      MoveSpd = v128;
      sBtlGetMoveXZ(v31.n64_f32[0], v32, MoveDir, MoveSpd, (f32 *)&ToZ + 1, &ToZ);
      MoveSpdMax = aWork->MoveSpdMax;
      v36 = v128 + aWork->MoveLen;
      v31.n64_u32[0] = HIDWORD(ToZ);
      v32 = *(f32 *)&ToZ;
      aWork->X = *((f32 *)&ToZ + 1);
      aWork->Z = v32;
      aWork->MoveLen = v36;
      aWork->MoveDir = aWork->MoveDir + aWork->MoveDirRate;
      v37 = aWork->MoveSpd + aWork->MoveSpdRate;
      aWork->MoveSpd = v37;
      if (v37 <= MoveSpdMax)
      {
LABEL_84:
        if ((aWork->StepFlag & 0x4000) != 0)
        {
          PopX = aWork->PopX;
          PopZ = aWork->PopZ;
          ToXa = v31.n64_u32[0];
          v31.n64_u32[0] = ToXa;
          PosToDir = sBtlGetPosToDir(PopX, PopZ, v31.n64_f32[0], v32);
          LenXZ = sBtlGetLenXZ(aWork->PopX, aWork->PopZ, aWork->X, aWork->Z);
          v54 = sBtlGet360(PosToDir + 2.0);
          sBtlGetMoveXZ(aWork->PopX, aWork->PopZ, v54, LenXZ, &aWork->X, &aWork->Z);
          StepIntBuff = aWork->StepIntBuff;
          aWork->Dir = v54;
          aWork->MoveDir = v54;
          v56 = StepIntBuff[1];
          if (v56 != -1)
          {
            v57 = GetAW(v56);
            v58 = sBtlGet360(PosToDir + -9.25);
            sBtlGetMoveXZ(aWork->PopX, aWork->PopZ, v58, LenXZ, &v57->X, &v57->Z);
            v57->Dir = v58;
            v57->MoveDir = v58;
          }
        }
        if ((aWork->StepFlag & 0x40) == 0)
        {
          v59 = 0;
          goto LABEL_114;
        }
        HomingFrame = aWork->HomingFrame;
        VelocityZ = aWork->VelocityZ;
        v62 = aWork->Z;
        v63.n64_u64[0] = *(u64 *)&aWork->VelocityX;
        v64.n64_u64[0] = *(u64 *)&aWork->X;
        v65.n64_u64[0] = *(u64 *)&aWork->HomingX;
        HomingZ = aWork->HomingZ;
        ToXb = aWork->HomingFrame;
        v129 = *(u64 *)&aWork->VelocityX;
        HomingFrame = ToXb;
        v63.n64_u64[0] = v129;
        if ((f32)(HomingFrame - VRF_DeltaTime) >= 0.0)
        {
          v73.n64_u64[0] = vsub_f32(v65, v64).n64_u64[0];
          v59 = 0;
          v75 = zeroVector.z;
          v76.n64_u64[0] = *(u64 *)&zeroVector.x;
          aWork->HomingFrame = HomingFrame - VRF_DeltaTime;
          v77.n64_u64[0] = vsub_f32(v73, vmul_f32((float32x2_t)__PAIR64__(LODWORD(HomingFrame), v63.n64_u32[0]), (float32x2_t)__PAIR64__(v63.n64_u32[1], LODWORD(HomingFrame)))).n64_u64[0];
          v73.n64_f32[0] = HomingFrame * HomingFrame;
          v78 = VelocityZ
              + (f32)(VRF_DeltaTime * (f32)((f32)((f32)((f32)((f32)(HomingZ - v62) - (f32)(HomingFrame * VelocityZ)) + (f32)((f32)(HomingZ - v62) - (f32)(HomingFrame * VelocityZ))) / (f32)(HomingFrame * HomingFrame)) + v75));
          v79.n64_u64[0] = vadd_f32(v63, vmul_n_f32(vadd_f32(vdiv_f32(vadd_f32(v77, v77), vdup_lane_s32(v73, 0)), v76), VRF_DeltaTime)).n64_u64[0];
          aWork->VelocityZ = v78;
          *(float32x2_t *)&aWork->VelocityX = v79;
          aWork->Z = v62 + (f32)(VRF_DeltaTime * v78);
          *(float32x2_t *)&aWork->X = vadd_f32(v64, vmul_n_f32(v79, VRF_DeltaTime));
LABEL_114:
          if (aWork->Variation == 1 && (aWork->StepFlag & 0x4000) == 0)
          {
            StepIntC = aWork->StepIntC;
            if (StepIntC == 1)
            {
              v90 = 2;
              StepFloatA = fminf(aWork->StepFloatA, 3.0);
            }
            else if (StepIntC)
            {
              StepFloatA = aWork->StepFloatA;
              v90 = 0;
            }
            else
            {
              v90 = 1;
              StepFloatA = fminf(aWork->StepFloatA, 1.5);
            }
            aWork->StepIntC = v90;
            v92 = aWork->StepIntBuff;
            v93 = v92[1];
            if (v93 != -1)
            {
              v94 = GetAW(v93);
              v95 = aWork->X;
              v96 = v94;
              v97 = aWork->Z;
              v98 = aWork->Dir;
              sBtlGetMoveXZ(v95, v97, v98 + 90.0, StepFloatA, (f32 *)&ToZ + 1, &ToZ);
              v96->X = *((f32 *)&ToZ + 1);
              LODWORD(v96->Z) = ToZ;
              v96->Dir = aWork->Dir;
              v92 = aWork->StepIntBuff;
            }
            v99 = v92[2];
            if (v99 != -1)
            {
              v100 = GetAW(v99);
              v101 = aWork->X;
              v102 = v100;
              v103 = aWork->Z;
              v104 = aWork->Dir;
              sBtlGetMoveXZ(v101, v103, v104 + -90.0, StepFloatA, (f32 *)&ToZ + 1, &ToZ);
              v102->X = *((f32 *)&ToZ + 1);
              LODWORD(v102->Z) = ToZ;
              v102->Dir = aWork->Dir;
            }
            v105 = aWork->StepFloatA + 0.05;
            aWork->StepFloatA = v105;
            if (v105 > 4.5)
              aWork->StepFloatA = 4.5;
          }
          StepFlag2 = aWork->StepFlag2;
          if (((StepFlag2 >> 4) & 1 & ~v59) != 0)
          {
LABEL_162:
            StepFlag = aWork->StepFlag;
            v118 = aWork->StepTime + VRF_DeltaTime;
            aWork->StepTime = v118;
            if ((StepFlag & 0x18) == 8)
            {
              v119 = aWork->MoveLen;
              if ((aWork->StepFlag2 & 0x20) == 0)
              {
                v120 = 30.0;
                goto LABEL_171;
              }
              *(f32 *)&v121 = 40.0;
            }
            else
            {
              if ((StepFlag & 0x10) != 0)
              {
                v119 = aWork->MoveLen;
                v120 = 15.0;
LABEL_171:
                if (v119 <= v120)
                  goto LABEL_181;
                goto LABEL_172;
              }
              if (v118 > (f32)(FPS60 * 240.0))
                goto LABEL_172;
              v119 = aWork->MoveLen;
              *(f32 *)&v121 = 50.0;
            }
            v120 = *(f32 *)&v121;
            goto LABEL_171;
          }
          if ((StepFlag2 & 1) == 0)
          {
            if ((aWork->StepFlag & 0x8000) == 0)
            {
              if ((StepFlag2 & 8) != 0)
              {
                if (!v107)
                v108 = 200.0;
              }
              else
              {
                if (!v107)
                v108 = 100.0;
              }
              SetHit(aWork);
            }
            goto LABEL_162;
          }
          if (aWork->Y > 0.0 && aWork->MoveLen < aWork->StepFloatB)
          {
            if ((aWork->StepFlag & 0x8000) == 0)
            {
              if ((StepFlag2 & 8) != 0)
              {
                if (!v109)
                v110 = 200.0;
              }
              else
              {
                if (!v109)
                v110 = 100.0;
              }
              if (SetHit(aWork))
                *(u64 *)&aWork->Step = (u32)(aWork->Step + 1);
            }
            goto LABEL_162;
          }
          if ((StepFlag2 & 2) != 0)
          {
            HomingX = aWork->HomingX;
            HomingY = aWork->HomingY;
            aWork->X = HomingX;
            aWork->Y = HomingY;
            v113 = aWork->HomingZ;
            StepIntB = aWork->StepIntB;
            aWork->Z = v113;
            Add(HomingX, HomingY, v113, StepIntB);
          }
          if ((aWork->StepFlag & 0x8000) != 0)
            goto LABEL_172;
          if ((aWork->StepFlag2 & 8) != 0)
            v115 = 200.0;
          else
            v115 = 100.0;
          v43 = v115;
          v42 = aWork;
LABEL_73:
          SetHit(v42);
          goto LABEL_172;
        }
        v68 = aWork->HomingZ;
        v69 = aWork->HomingX;
        v70 = aWork->HomingY;
        ++aWork->Step;
        aWork->StepTime = 0.0;
        v71 = BYTE1(aWork->StepFlag);
        aWork->X = v69;
        aWork->Y = v70;
        aWork->Z = v68;
        if ((v71 & 2) != 0)
        {
          AW_XAtkAdd(v69, v70, v68, 1.0);
          AW_XAtkFadeOut(aWork->StepIntBuff[0]);
          aWork->StepIntBuff[0] = -1;
          if ((aWork->StepFlag2 & 4) == 0)
          {
LABEL_100:
            v72 = aWork->StepFlag;
            if ((v72 & 0x2000) == 0)
              goto LABEL_101;
            goto LABEL_108;
          }
        }
        else if ((aWork->StepFlag2 & 4) == 0)
        {
          goto LABEL_100;
        }
        v80 = aWork->X * -100.0;
        v81 = aWork->Y * -100.0;
        v82 = aWork->Z * -100.0;
        v139.w = 0.0;
        v139.x = v80;
        v139.y = v81;
        v139.z = v82;
        sBtlPlay3DSE_BaseVol(0x502001Au, 127, v139);
        v72 = aWork->StepFlag;
        if ((v72 & 0x2000) == 0)
        {
LABEL_101:
          if ((v72 & 0x400) == 0)
          {
LABEL_102:
            v59 = 1;
            goto LABEL_114;
          }
LABEL_111:
          Add(aWork->X, aWork->Y, aWork->Z, AW);
          v86 = aWork->X * -100.0;
          v87 = aWork->Y * -100.0;
          v88 = aWork->Z * -100.0;
          v141.w = 0.0;
          v141.x = v86;
          v141.y = v87;
          v141.z = v88;
          sBtlPlay3DSE(0x10095u, v141);
          v59 = 1;
          *(u64 *)&aWork->Step = 100;
          goto LABEL_114;
        }
LABEL_108:
        Add(aWork->X, aWork->Y, aWork->Z, 0);
        v83 = aWork->X * -100.0;
        v84 = aWork->Y * -100.0;
        v85 = aWork->Z * -100.0;
        v140.w = 0.0;
        v140.x = v83;
        v140.y = v84;
        v140.z = v85;
        sBtlPlay3DSE(0x1009Cu, v140);
        *(u64 *)&aWork->Step = 200;
        if ((aWork->StepFlag & 0x400) == 0)
          goto LABEL_102;
        goto LABEL_111;
      }
    }
    aWork->MoveSpd = MoveSpdMax;
    goto LABEL_84;
  }
  if (Step == 200)
  {
    StepTime = aWork->StepTime + VRF_DeltaTime;
    aWork->StepTime = StepTime;
    if (StepTime > (f32)(FPS60 * 107.0) && StepTime < (f32)(FPS60 * 110.0))
    {
      if (!aWork->StepBoolA)
      {
        v18 = aWork->Y;
        aWork->StepBoolA = 1;
        v19 = v18 * -100.0;
        v137.w = 0.0;
        v137.x = X * -100.0;
        v137.y = v19;
        v137.z = Z * -100.0;
        sBtlPlay3DSE(0x1009Eu, v137);
      }
      SetHit(aWork, 200.0);
      StepTime = aWork->StepTime;
    }
    if (StepTime <= (f32)(FPS60 * 120.0))
    {
      UnitMng = wk->UnitMng;
      Unit_ListID = aWork->Unit_ListID;
      v23 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
      if (v23)
      {
        v24 = v23;
        if (v23->UID == aWork->Unit_UID)
        {
          if (sBtlCheckLiveTarget2(v24))
            goto LABEL_181;
        }
      }
    }
LABEL_172:
    ++aWork->Step;
    aWork->StepTime = 0.0;
    if (aWork->Variation != 1)
      return;
LABEL_182:
    v122 = aWork->X;
    v123 = aWork->Z;
    if (sBtlGetLenXZ(X, Z, v122, v123) < 0.005 && aWork->Variation == 1)
    {
      Delete(aWork);
    }
    return;
  }
  if (Step != 201)
  {
    if (Step == 300)
    {
      ParticleSystemList = aWork->ParticleSystemList;
      v10 = aWork->StepTime - VRF_DeltaTime;
      aWork->StepTime = v10;
      if (v10 <= 0.0)
      {
        if (ParticleSystemList && aWork->HDEff_SimSpeed != 1.0)
        {
          aWork->HDEff_SimSpeed = 1.0;
          _GetEnumerator(&v130, ParticleSystemList);
          v44 = *(_OWORD *)&v130._list;
          v130._list = 0;
          *(u64 *)&v130._index = &v133;
          v133._current = v130._current;
          *(_OWORD *)&v133._list = v44;
          while (_MoveNext(&v133))
          {
            current = v133._current;
            if (!op_Equality(current, 0, 0))
            {
              v136.m_ParticleSystem = get_main(current, 0).m_ParticleSystem;
              HDEff_SimSpeed = aWork->HDEff_SimSpeed;
              m_ParticleSystem = v136.m_ParticleSystem;
              set_simulationSpeed((UnityEngine_ParticleSystem_MainModule_o)&m_ParticleSystem, HDEff_SimSpeed, 0);
            }
          }
          sub_33DC8(&v130);
        }
        *(u64 *)&aWork->Step = 0;
      }
      else if (ParticleSystemList && aWork->HDEff_SimSpeed != 0.0)
      {
        aWork->HDEff_SimSpeed = 0.0;
        _GetEnumerator(&v130, ParticleSystemList);
        v11 = *(_OWORD *)&v130._list;
        v130._list = 0;
        *(u64 *)&v130._index = &v133;
        v133._current = v130._current;
        *(_OWORD *)&v133._list = v11;
        while (_MoveNext(&v133))
        {
          v12 = v133._current;
          if (!op_Equality(v12, 0, 0))
          {
            v135.m_ParticleSystem = get_main(v12, 0).m_ParticleSystem;
            v13 = aWork->HDEff_SimSpeed;
            v131 = v135.m_ParticleSystem;
            set_simulationSpeed((UnityEngine_ParticleSystem_MainModule_o)&v131, v13, 0);
          }
        }
        sub_33E04(&v130);
        if (aWork->Variation != 1)
          return;
        goto LABEL_182;
      }
    }
    goto LABEL_181;
  }
LABEL_25:
  Delete(aWork);
}

// 0x1e88260
void Draw(AW_WORK_t *aWork) {
  void *Obj;
  void *transform;
  void *v6;
  void *v7;
  sdfVector3_t v8;
  sdfVector3_t v9;

  Obj = aWork->Obj;
  if (op_Equality(Obj, 0, 0))
    return;
  transform = get_transform(aWork->Obj, 0);
  set_localPosition(transform, *(sdfVector3_t *)&aWork->X, 0);
  v6 = get_transform(aWork->Obj, 0);
  v8.y = aWork->Dir;
  v8.z = 0.0;
  v8.x = -aWork->DirY;
  set_eulerAngles(v6, v8, 0);
  v7 = get_transform(aWork->Obj, 0);
  v9.x = aWork->Scale;
  v9.y = v9.x;
  v9.z = v9.x;
  set_localScale(v7, v9, 0);
  return;
}

// 0x1e855f0
s32 AW_XAtkAdd_BioArm_Top(void) {
  s32 v2;
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v15;
  AW_XAtk_WORK_t *v16;
  s32 Variation;
  f32 v18;
  f32 v19;
  f32 v20;
  AW_Func v21;
  AW_Func v22;
  intptr_t *v23;
  AW_Func v24;
  s32 v25;
  AW_WORK_t *AW;
  int32x4_t v28;
  AW_XAtk_WORK_t *v31;
  int32x4_t v32;
  int32x4_t v33;
  u32 Flag;
  f32 HomingZ;
  s32 *p_SklID;
  bool v37;
  f32 v39;
  f32 v40;
  f32 HomingX;
  f32 v42;
  f32 LenXZ;
  f32 v44;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 PosToDir;
  f32 DirY;
  f32 MoveSpd;
  u64 v57;
  f32 v59;
  f32 HomingFrame;
  s32 *StepIntBuff;
  s32 *v64;
  s32 v66;
  s32 *v67;
  float32x2_t v68;
  f32 v69;
  s32 v70;
  char *v71;
  u64 pos;
  u64 posa;
  sdfVector3_t Vec;
  sdfVector4_t v76;
  sdfVector4_t v77;
  sdfVector3_t v78;
  sdfQuaternion_t v79;

  Vec.z = 0.0;
  *(u64 *)&Vec.x = 0;
  if (ArgumentParam->Variation == 11)
    v2 = 102;
  else
    v2 = 100;
  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, v2, 0);
  v7 = ArgumentParam[9];
  v8 = ArgumentParam[7];
  v9 = ArgumentParam[8];
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v78.x = v8;
  v78.y = v9;
  v78.z = v7;
  v79.x = x;
  v79.y = y;
  v79.z = z;
  v79.w = w;
  v15 = Instantiate_object__39504752(AwPrefab, v78, v79);
  v16 = ArgumentParam;
  Variation = v16->Variation;
  if (Variation == 11)
  {
    v16 = ArgumentParam;
    v18 = v16->X;
    v19 = v16->Y;
    v20 = v16->Z;
    v21 = Allocate(AW_Func);
    v22 = v21;
    v23 = &Method_Project_AW_XAtkBullet_Calc_BioArm_Top_L__;
LABEL_22:
    _ctor(v21, 0, *v23, 0);
    v24 = Allocate(AW_Func);
    _ctor(v24, 0, Method_Project_AW_XAtkBullet_Draw_BioArm__, 0);
    v25 = Add(251, v18, v19, v20, v15, v22, v24, 1);
    goto LABEL_26;
  }
  if (Variation == 10)
  {
    v16 = ArgumentParam;
    v18 = v16->X;
    v19 = v16->Y;
    v20 = v16->Z;
    v21 = Allocate(AW_Func);
    v22 = v21;
    v23 = &Method_Project_AW_XAtkBullet_Calc_BioArm_Top_R__;
    goto LABEL_22;
  }
  v25 = -1;
LABEL_26:
  Set_HDEff(v25, 1, -1);
  AW = GetAW(v25);
  v31 = ArgumentParam;
  v32 = *(int32x4_t *)&ArgumentParam->MoveDir;
  v28.n128_u32[0] = LODWORD(ArgumentParam->Dir);
  AW->MoveLen = 0.0;
  *(int32x4_t *)&AW->MoveDir = v32;
  AW->MoveSpdMax = v31->MoveSpdMax;
  v32.n128_u64[0] = *(u64 *)&v31->DirY;
  v33 = vzip1q_s32(v28, v32);
  v33.n128_u32[2] = v33.n128_u32[1];
  *(int32x4_t *)&AW->Dir = v33;
  *(u64 *)&AW->HomingX = *(u64 *)&v31->HomingX;
  *(u64 *)&AW->Unit_ListID = *(u64 *)&v31->Unit_ListID;
  Flag = v31->Flag;
  AW->Variation = v31->Variation;
  AW->StepFlag = Flag;
  v33.n128_u64[0] = *(u64 *)&v31->Group_AW_Idx;
  HomingZ = v31->HomingZ;
  AW->StepFloatA = 0.0;
  *(u64 *)&AW->Group_AW_Idx = v33.n128_u64[0];
  AW->HomingZ = HomingZ;
  p_SklID = &v31->SklID;
  LODWORD(v31) = v31->SklID;
  AW->StepIntA = p_SklID[1];
  AW->StepIntB = (s32)v31;
  v37 = !gBioArmFlip;
  gBioArmFlip = v37;
  *(u64 *)&AW->StepOfsX = 0;
  v39 = AW->X;
  AW->StepBoolB = v37;
  AW->StepOfsZ = 0.0;
  v40 = AW->Z;
  HomingX = AW->HomingX;
  *(u64 *)&AW->StepFloatB = 1065353216;
  v42 = AW->HomingZ;
  LenXZ = sBtlGetLenXZ(v39, v40, HomingX, v42);
  if (LenXZ >= 8.0)
  {
    if (LenXZ <= 18.0)
      goto LABEL_41;
    v44 = AW->X;
    v45 = AW->Z;
    v46 = AW->HomingX;
    v47 = AW->HomingZ;
    v48 = 18.0;
  }
  else
  {
    v44 = AW->X;
    v45 = AW->Z;
    v46 = AW->HomingX;
    v47 = AW->HomingZ;
    v48 = 8.0;
  }
  sBtlGetMovePosToPos(v44, v45, v46, v47, v48, &AW->HomingX, &AW->HomingZ);
LABEL_41:
  v49 = AW->X;
  v50 = AW->Z;
  v51 = AW->HomingX;
  v52 = AW->HomingZ;
  PosToDir = sBtlGetPosToDir(v49, v50, v51, v52);
  DirY = AW->DirY;
  AW->MoveDir = PosToDir;
  AW->Dir = PosToDir;
  *(u64 *)&Vec.x = 0;
  Vec.z = 0.0;
  GetDirToVec(PosToDir, DirY, &Vec);
  MoveSpd = AW->MoveSpd;
  v57 = vmul_n_f32(*(float32x2_t *)&Vec.x, MoveSpd).n64_u64[0];
  v59 = MoveSpd * Vec.z;
  *(u64 *)&AW->VelocityX = v57;
  AW->VelocityZ = v59;
  HomingFrame = ArgumentParam->HomingFrame;
  StepIntBuff = AW->StepIntBuff;
  StepIntBuff[0] = 20;
  StepIntBuff[1] = v25;
  AW->HomingFrame = HomingFrame * FPS60;
  StepIntBuff[2] = AW_XAtkAdd_BioArm_Root(AW);
  v64 = AW->StepIntBuff;
  v66 = AW_XAtkAdd_BioArm_Mid(AW, v64[0] - 1);
  v67 = AW->StepIntBuff;
  v64[4] = v66;
  v67[5] = -1;
  v68.n64_u64[0] = vmul_f32(vadd_f32(*(float32x2_t *)&AW->X, *(float32x2_t *)&AW->StepOfsX), vdup_n_s32(0xC2C80000)).n64_u64[0];
  v69 = (f32)(AW->Z + AW->StepOfsZ) * -100.0;
  v70 = ArgumentParam->Variation;
  if (v70 == 11)
  {
    AW->StepIntC = 3;
    AW->StepBoolA = 0;
    posa = v68.n64_u64[0];
    v68.n64_u64[0] = posa;
    *(float32x2_t *)&v77.x = v68;
    v77.z = v69;
    v77.w = 0.0;
    sBtlPlay3DSE(0x10098u, v77);
    if (wk->encountno != 60)
      goto LABEL_57;
    AW->StepIntC = 2;
    goto LABEL_57;
  }
  if (v70 == 10)
  {
    AW->StepIntC = 0;
    AW->StepBoolA = 0;
    pos = v68.n64_u64[0];
    v68.n64_u64[0] = pos;
    *(float32x2_t *)&v76.x = v68;
    v76.z = v69;
    v76.w = 0.0;
    sBtlPlay3DSE(0x1009Au, v76);
  }
LABEL_57:
  v71 = "AW_XAtkBullet_BioArm_Top";
  AW->DbgStr = "AW_XAtkBullet_BioArm_Top";
  return v25;
}

// 0x1e88360
s32 AW_XAtkAdd_BioArm_Root(AW_WORK_t *aWorkTop) {
  s32 Variation;
  s32 v4;
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v17;
  AW_XAtk_WORK_t *v18;
  f32 v19;
  f32 v20;
  f32 v21;
  AW_Func v22;
  AW_Func v23;
  s32 v24;
  AW_WORK_t *AW;
  AW_WORK_t *v27;
  f32 Dir;
  f32 MoveDir;
  AW_XAtk_WORK_t *v31;
  s64 v32;
  __int128 v33;
  s64 v34;
  f32 MoveSpd;
  AW_XAtk_WORK_t *v38;
  f32 v41;
  s32 *p_SklID;
  s32 *StepIntBuff;
  s32 *v44;
  s32 v45;
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v48;
  f32 v49;
  f32 v50;
  char *v51;
  s32 DirY;
  sdfVector3_t Vec;
  sdfVector3_t v55;
  sdfQuaternion_t v56;

  Variation = aWorkTop->Variation;
  Vec.z = 0.0;
  *(u64 *)&Vec.x = 0;
  if (Variation == 11)
    v4 = 103;
  else
    v4 = 101;
  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, v4, 0);
  v9 = ArgumentParam[9];
  v10 = ArgumentParam[7];
  v11 = ArgumentParam[8];
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v55.x = v10;
  v55.y = v11;
  v55.z = v9;
  v56.x = x;
  v56.y = y;
  v56.z = z;
  v56.w = w;
  v17 = Instantiate_object__39504752(AwPrefab, v55, v56);
  v18 = ArgumentParam;
  v19 = v18->Z;
  v20 = v18->X;
  v21 = v18->Y;
  v22 = Allocate(AW_Func);
  _ctor(v22, 0, Method_Project_AW_XAtkBullet_Calc_BioArm_Root__, 0);
  v23 = Allocate(AW_Func);
  _ctor(v23, 0, Method_Project_AW_XAtkBullet_Draw_BioArm__, 0);
  v24 = Add(251, v20, v21, v19, v17, v22, v23, 1);
  Set_HDEff(v24, 1, -1);
  AW = GetAW(v24);
  v27 = AW;
  AW->Variation = aWorkTop->Variation;
  Dir = aWorkTop->Dir;
  MoveDir = aWorkTop->MoveDir;
  AW->Dir = Dir;
  AW->MoveDir = MoveDir;
  v31 = ArgumentParam;
  Vec.z = 0.0;
  *(u64 *)&Vec.x = 0;
  v32 = *(u64 *)&v31->Unit_ListID;
  v33 = *(_OWORD *)&v31->MoveDirRate;
  AW->MoveLen = 0.0;
  *(u64 *)&AW->Unit_ListID = v32;
  *(_OWORD *)&AW->MoveDirRate = v33;
  v34 = *(u64 *)&v31->DirY;
  AW->StepFlag = v31->Flag;
  *(u64 *)&v33 = *(u64 *)&v31->Group_AW_Idx;
  LODWORD(AW->DirY) = v34;
  *(u64 *)&AW->DirIKY = v34;
  *(u64 *)&AW->Group_AW_Idx = v33;
  *(u64 *)&AW->HomingX = *(u64 *)&v31->HomingX;
  AW->HomingZ = v31->HomingZ;
  DirY = v34;
  LODWORD(v34) = DirY;
  GetDirToVec(Dir, *(f32 *)&v34, &Vec);
  MoveSpd = v27->MoveSpd;
  v27->StepOfsZ = 0.0;
  v27->StepFloatC = 0.0;
  *(float32x2_t *)&v27->VelocityX = vmul_n_f32(*(float32x2_t *)&Vec.x, MoveSpd);
  v38 = ArgumentParam;
  v27->VelocityZ = MoveSpd * Vec.z;
  v41 = v38->HomingFrame * FPS60;
  p_SklID = &v38->SklID;
  LODWORD(v38) = v38->SklID;
  v27->StepIntA = p_SklID[1];
  StepIntBuff = aWorkTop->StepIntBuff;
  v27->StepIntB = (s32)v38;
  v44 = v27->StepIntBuff;
  v45 = StepIntBuff[0];
  *(u64 *)&v27->StepOfsX = 0;
  *(u64 *)&v27->StepFloatA = 0;
  v27->HomingFrame = v41;
  v44[0] = v45;
  v44[1] = StepIntBuff[1];
  v44[2] = v24;
  Unit_ListID = v27->Unit_ListID;
  UnitMng = wk->UnitMng;
  v48 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  if (v48)
  {
    v49 = v48->pos.z;
    v50 = v27->Z;
    *(float32x2_t *)&v27->VelocityX = vadd_f32(*(float32x2_t *)&v27->X, vdiv_f32(*(float32x2_t *)&v48->pos.x, vdup_n_s32(0x42C80000u)));
    v27->VelocityZ = v50 + (f32)(v49 / 100.0);
  }
  v51 = "AW_XAtkBullet_BioArm_Root";
  v27->DbgStr = "AW_XAtkBullet_BioArm_Root";
  return v24;
}

// 0x1e887e0
s32 AW_XAtkAdd_BioArm_Mid(AW_WORK_t *aWorkTop, s32 _NumID) {
  s32 Variation;
  s32 v6;
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *v19;
  AW_XAtk_WORK_t *v20;
  f32 v21;
  f32 v22;
  f32 v23;
  AW_Func v24;
  AW_Func v25;
  s32 v26;
  AW_WORK_t *AW;
  AW_WORK_t *v29;
  f32 Dir;
  f32 MoveDir;
  AW_XAtk_WORK_t *v33;
  s64 v34;
  __int128 v35;
  u32 Flag;
  f32 DirY;
  f32 MoveSpd;
  struct dds3VRF *v42;
  AW_XAtk_WORK_t *v43;
  s32 *StepIntBuff;
  f32 HomingFrame;
  s32 *p_SklID;
  s32 *v48;
  f32 v49;
  bool v50;
  s32 v51;
  char *v52;
  sdfVector3_t v54;
  sdfVector3_t v55;
  sdfQuaternion_t v56;

  Variation = aWorkTop->Variation;
  v54.z = 0.0;
  *(u64 *)&v54.x = 0;
  if (Variation == 11)
    v6 = 103;
  else
    v6 = 101;
  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, v6, 0);
  v11 = ArgumentParam[9];
  v12 = ArgumentParam[7];
  v13 = ArgumentParam[8];
  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  v55.x = v12;
  v55.y = v13;
  v55.z = v11;
  v56.x = x;
  v56.y = y;
  v56.z = z;
  v56.w = w;
  v19 = Instantiate_object__39504752(AwPrefab, v55, v56);
  v20 = ArgumentParam;
  v21 = v20->Z;
  v22 = v20->X;
  v23 = v20->Y;
  v24 = Allocate(AW_Func);
  _ctor(v24, 0, Method_Project_AW_XAtkBullet_Calc_BioArm_Mid__, 0);
  v25 = Allocate(AW_Func);
  _ctor(v25, 0, Method_Project_AW_XAtkBullet_Draw_BioArm__, 0);
  v26 = Add(251, v22, v23, v21, v19, v24, v25, 1);
  Set_HDEff(v26, 1, -1);
  AW = GetAW(v26);
  v29 = AW;
  Dir = aWorkTop->Dir;
  AW->Dir = Dir;
  MoveDir = aWorkTop->MoveDir;
  AW->Variation = aWorkTop->Variation;
  AW->MoveDir = MoveDir;
  v33 = ArgumentParam;
  v54.z = 0.0;
  *(u64 *)&v54.x = 0;
  v34 = *(u64 *)&v33->Unit_ListID;
  v35 = *(_OWORD *)&v33->MoveDirRate;
  AW->MoveLen = 0.0;
  AW->DirIKY = 0.0;
  *(u64 *)&AW->Unit_ListID = v34;
  Flag = v33->Flag;
  *(_OWORD *)&AW->MoveDirRate = v35;
  AW->StepFlag = Flag;
  DirY = v33->DirY;
  AW->Scale = v33->Scale;
  *(u64 *)&v35 = *(u64 *)&v33->Group_AW_Idx;
  AW->DirY = DirY;
  *(u64 *)&AW->Group_AW_Idx = v35;
  *(u64 *)&AW->HomingX = *(u64 *)&v33->HomingX;
  AW->HomingZ = v33->HomingZ;
  GetDirToVec(Dir, DirY, &v54);
  MoveSpd = v29->MoveSpd;
  v29->StepOfsZ = 0.0;
  *(float32x2_t *)&v29->VelocityX = vmul_n_f32(*(float32x2_t *)&v54.x, MoveSpd);
  v43 = ArgumentParam;
  StepIntBuff = v29->StepIntBuff;
  v29->VelocityZ = MoveSpd * v54.z;
  HomingFrame = v43->HomingFrame;
  p_SklID = &v43->SklID;
  LODWORD(v43) = v43->SklID;
  LODWORD(v42) = p_SklID[1];
  *(u64 *)&v29->StepOfsX = 0;
  v29->StepIntB = (s32)v43;
  v29->StepIntA = (s32)v42;
  LODWORD(v42) = aWorkTop->UID;
  v29->Group_AW_Idx = aWorkTop->Idx;
  v29->Group_AW_UID = (s32)v42;
  v48 = aWorkTop->StepIntBuff;
  *(u64 *)&v29->StepFloatA = 0x3F80000000000000LL;
  v29->HomingFrame = HomingFrame * FPS60;
  LODWORD(v42) = v48[0];
  v29->StepFloatC = aWorkTop->StepFloatC;
  StepIntBuff[0] = (s32)v42;
  StepIntBuff[1] = v48[1];
  StepIntBuff[2] = v48[2];
  StepIntBuff[3] = NumID;
  v49 = (v48[0] + 1);
  LODWORD(v48) = NumID + 1;
  v50 = __OFSUB__(NumID, 1);
  v51 = NumID - 1;
  v29->LaserOfsLen = (f32)(1.0 / v49) * (f32)(s32)v48;
  if (v51 < 0 != v50)
  {
    StepIntBuff[4] = -1;
  }
  else
  {
    StepIntBuff[4] = AW_XAtkAdd_BioArm_Mid(v29, v51);
    StepIntBuff = v29->StepIntBuff;
  }
  StepIntBuff[5] = aWorkTop->Idx;
  v52 = "AW_XAtkBullet_BioArm_Mid";
  v29->DbgStr = "AW_XAtkBullet_BioArm_Mid";
  return v26;
}

// 0x1e88c40
void AW_XAtkDelete_BioArm(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e88cb0
void AW_XAtkDelete_BioArm_Mid(AW_WORK_t *aWork) {
  s32 v3;
  AW_WORK_t *AW;
  s32 Idx;

  v3 = aWork->StepIntBuff[4];
  if (v3 != -1)
  {
    AW = GetAW(v3);
    AW_XAtkDelete_BioArm_Mid(AW);
  }
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e88d80
static void SetHit_BioArm(AW_WORK_t *aWork, f32 _Size) {
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v8;
  u32 status;
  float32x2_t v12;
  f32 v13;
  int32x2_t v14;
  u64 v16;
  f32 v17;
  s64 i;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v20;
  f32 v21;
  f32 v22;
  f32 v23;
  s32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  s32 **v30;
  s32 *StepIntBuff;
  s32 v33;
  AW_WORK_t *v34;
  float32x2_t v35;
  float32x2_t v36;
  f32 v37;
  f32 v38;
  f32 v39;
  u64 v40;
  f32 v41;
  f32 v42;
  s32 v43;
  f32 v44;
  f32 v45;
  f32 v46;
  f32 v47;
  SBATTLE_WORK *v50;
  SBTLUNIT_LISTWORK *v51;
  s32 playerID;
  SBTLUNIT_WORK *v53;
  f32 y;
  f32 x;
  f32 z;
  s32 StepIntB;
  f32 v58;
  f32 v59;
  f32 w;
  f32 v61;
  s32 **p_StepIntBuff;
  s32 v65;
  AW_WORK_t *AW;
  float32x2_t v67;
  float32x2_t v68;
  f32 v69;
  f32 StepOfsZ;
  f32 v71;
  u64 v72;
  f32 v73;
  f32 v74;
  s32 v75;
  f32 v76;
  f32 v77;
  f32 v78;
  f32 v79;
  u64 FromX;
  sdfVector4_t v82;
  sdfVector4_t v83;
  sdfVector4_t v84;
  sdfVector4_t v85;

  Unit_ListID = aWork->Unit_ListID;
  UnitMng = wk->UnitMng;
  v8 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  status = wk->status;
  if ((status & 0x1000000) == 0)
  {
    if ((status & 0x2000000) != 0)
      return;
    if (!sBtlCheckPlayerDead())
    {
      if (!wk->enemy_zenmetu)
      {
        if (wk->mode != 2)
          goto LABEL_26;
        if (!IsSceanStop())
        {
LABEL_26:
          if (v8 && v8->UID == aWork->Unit_UID)
          {
            v12.n64_u64[0] = vadd_f32(*(float32x2_t *)&aWork->X, *(float32x2_t *)&aWork->StepOfsX).n64_u64[0];
            v13 = aWork->Z + aWork->StepOfsZ;
            v14.n64_u64[0] = vdup_n_s32(0xC2C80000).n64_u64[0];
            v16 = vmul_f32(v12, v14).n64_u64[0];
            v17 = v13 * -100.0;
            FromX = v16;
            if (!gHitDonePlayer)
            {
              v50 = wk;
              v51 = v50->UnitMng;
              playerID = v50->playerID;
              v53 = sBtlSearchUnit_ID(v51, playerID);
              y = v53->pos.y;
              if (sBtlGetABS(*((f32 *)&FromX + 1) - y) < 40.0)
              {
                x = v53->pos.x;
                z = v53->pos.z;
                if (sBtlGetLenXZ(*(f32 *)&FromX, v17, x, z) < Size)
                {
                  StepIntB = aWork->StepIntB;
                  v58 = v53->pos.x;
                  v59 = v53->pos.y;
                  v61 = v53->pos.z;
                  w = v53->pos.w;
                  v84.x = v58;
                  v84.y = v59;
                  v84.z = v61;
                  v84.w = w;
                  SetDamageProc(v53, v8, StepIntB, v84);
                  gHitDonePlayer = 1;
                }
              }
              if (aWork->StepIntBuff[4] != -1)
              {
                p_StepIntBuff = &aWork->StepIntBuff;
                do
                {
                  if (gHitDonePlayer)
                    break;
                  v65 = (*p_StepIntBuff)[4];
                  AW = GetAW(v65);
                  v67.n64_u64[0] = *(u64 *)&AW->X;
                  v68.n64_u64[0] = *(u64 *)&AW->StepOfsX;
                  v69 = AW->Z;
                  StepOfsZ = AW->StepOfsZ;
                  v71 = v53->pos.y;
                  v72 = vmul_f32(vadd_f32(v67, v68), v14).n64_u64[0];
                  v17 = (f32)(v69 + StepOfsZ) * -100.0;
                  FromX = v72;
                  if (sBtlGetABS(*((f32 *)&v72 + 1) - v71) < 40.0)
                  {
                    v73 = v53->pos.x;
                    v74 = v53->pos.z;
                    if (sBtlGetLenXZ(*(f32 *)&FromX, v17, v73, v74) < Size)
                    {
                      v75 = aWork->StepIntB;
                      v76 = v53->pos.x;
                      v77 = v53->pos.y;
                      v78 = v53->pos.z;
                      v79 = v53->pos.w;
                      v85.x = v76;
                      v85.y = v77;
                      v85.z = v78;
                      v85.w = v79;
                      SetDamageProc(v53, v8, v75, v85);
                      gHitDonePlayer = 1;
                    }
                  }
                  p_StepIntBuff = &AW->StepIntBuff;
                }
                while (AW->StepIntBuff[4] != -1);
              }
            }
            for (i = 0; i != 2; ++i)
            {
              Nakama = sBtlGetNakama(i);
              if (Nakama)
              {
                v20 = Nakama;
                if (!gHitDoneNakama[i])
                {
                  if (!v20->L2_muteki)
                  {
                    v21 = v20->pos.y;
                    if (sBtlGetABS(*((f32 *)&FromX + 1) - v21) < 40.0)
                    {
                      v22 = v20->pos.x;
                      v23 = v20->pos.z;
                      if (sBtlGetLenXZ(*(f32 *)&FromX, v17, v22, v23) < Size)
                      {
                        v24 = aWork->StepIntB;
                        v25 = v20->pos.x;
                        v26 = v20->pos.y;
                        v27 = v20->pos.z;
                        v28 = v20->pos.w;
                        v82.x = v25;
                        v82.y = v26;
                        v82.z = v27;
                        v82.w = v28;
                        SetDamageProc(v20, v8, v24, v82);
                        gHitDoneNakama[i] = 1;
                      }
                    }
                    v30 = &aWork->StepIntBuff;
                    StepIntBuff = aWork->StepIntBuff;
                    while (StepIntBuff[4] != -1)
                    {
                      if (gHitDoneNakama[i])
                        break;
                      v33 = (*v30)[4];
                      v34 = GetAW(v33);
                      v35.n64_u64[0] = *(u64 *)&v34->X;
                      v36.n64_u64[0] = *(u64 *)&v34->StepOfsX;
                      v37 = v34->Z;
                      v38 = v34->StepOfsZ;
                      v39 = v20->pos.y;
                      v40 = vmul_f32(vadd_f32(v35, v36), v14).n64_u64[0];
                      v17 = (f32)(v37 + v38) * -100.0;
                      FromX = v40;
                      if (sBtlGetABS(*((f32 *)&v40 + 1) - v39) < 40.0)
                      {
                        v41 = v20->pos.x;
                        v42 = v20->pos.z;
                        if (sBtlGetLenXZ(*(f32 *)&FromX, v17, v41, v42) < Size)
                        {
                          v43 = aWork->StepIntB;
                          v44 = v20->pos.x;
                          v45 = v20->pos.y;
                          v46 = v20->pos.z;
                          v47 = v20->pos.w;
                          v83.x = v44;
                          v83.y = v45;
                          v83.z = v46;
                          v83.w = v47;
                          SetDamageProc(v20, v8, v43, v83);
                          gHitDoneNakama[i] = 1;
                        }
                      }
                      StepIntBuff = v34->StepIntBuff;
                      v30 = &v34->StepIntBuff;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

// 0x1e89580
void AW_XAtkCalc_BioArm_Top_R(AW_WORK_t *aWork) {
  s32 v4;
  AW_WORK_t *AW;
  f32 X;
  f32 Z;
  AW_WORK_t *v8;
  f32 v9;
  f32 v10;
  f32 PosToDir;
  f32 StepOfsX;
  f32 v13;
  f32 Y;
  f32 v15;
  f32 StepOfsY;
  f32 v17;
  f32 StepOfsZ;
  _BOOL4 StepBoolB;
  f32 VRF_DeltaTime_local;
  f32 v21;
  f32 StepFloatC;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 Unit_ListID;
  SBTLUNIT_WORK *v35;
  SBTLUNIT_WORK *v36;
  s32 Step;
  f32 v40;
  SBTLUNIT_LISTWORK *v43;
  s32 playerID;
  SBTLUNIT_WORK *v45;
  f32 v46;
  f32 *p_HomingZ;
  f32 v48;
  f32 *p_HomingX;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 v53;
  f32 v54;
  f32 v55;
  f32 v56;
  f32 v57;
  f32 v58;
  f32 v59;
  f32 v60;
  f32 v61;
  f32 v62;
  f32 v63;
  f32 v64;
  f32 v65;
  f32 v66;
  s32 v67;
  AW_WORK_t *v69;
  s32 Idx;
  s32 v72;
  f32 v74;
  f32 StepTime;
  f32 v76;
  f32 v78;
  f32 HomingX;
  f32 HomingZ;
  f32 v81;
  f32 LenXZ;
  char v84;
  f32 v86;
  f32 v87;
  float32x2_t v88;
  float32x2_t v89;
  f32 v90;
  float32x2_t v92;
  u32 v93;
  f32 v94;
  int32x2_t v95;
  f32 v96;
  f32 HomingY;
  f32 v98;
  f32 v99;
  s32 v100;
  f32 v101;
  f32 v102;
  float32x2_t v103;
  f32 v104;
  s32 v105;
  AW_WORK_t *v107;
  float32x2_t v110;
  float32x2_t v111;
  f32 v112;
  float32x2_t v113;
  f32 v116;
  f32 v117;
  f32 v118;
  f32 v119;
  f32 v120;
  f32 v121;
  f32 v122;
  f32 v123;
  f32 v124;
  u32 v125;
  f32 Dir_Hokan;
  f32 v127;
  f32 v128;
  f32 v129;
  f32 v130;
  f32 v131;
  float32x2_t v132;
  f32 VelocityZ;
  f32 Lena;
  f32 Len;
  f32 Lenb;
  u64 Lenc;
  f32 v138;
  f32 v139;
  f32 v140;
  f32 v141;
  sdfVector4_t v142;

  if (ChkPause(aWork))
    return;
  v4 = aWork->StepIntBuff[2];
  AW = GetAW(v4);
  X = AW->X;
  Z = aWork->Z;
  v8 = AW;
  v9 = aWork->X;
  v10 = AW->Z;
  PosToDir = sBtlGetPosToDir(X, v10, v9, Z);
  StepOfsX = aWork->StepOfsX;
  v13 = PosToDir;
  v15 = aWork->X;
  Y = aWork->Y;
  StepOfsY = aWork->StepOfsY;
  v17 = aWork->Z;
  StepOfsZ = aWork->StepOfsZ;
  StepBoolB = aWork->StepBoolB;
  VRF_DeltaTime_local = VRF_DeltaTime;
  if (aWork->Step == 1)
    VRF_DeltaTime_local = VRF_DeltaTime_local * 0.2;
  v21 = aWork->StepFloatA + VRF_DeltaTime_local;
  StepFloatC = aWork->StepFloatC;
  aWork->StepFloatA = v21;
  v23 = v21 * 5.0;
  v24 = -(f32)(v21 * 5.0);
  if (!StepBoolB)
    v24 = v23;
  v25 = v24 * 0.15915494;
  v26 = (s32)v25;
  if (v25 == INFINITY)
    v26 = -2147500000.0;
  v27 = v25 - v26;
  if (v27 <= 0.5)
  {
    if (v27 >= -0.5)
      goto LABEL_22;
    v28 = 1.0;
  }
  else
  {
    v28 = -1.0;
  }
  v27 = v27 + v28;
LABEL_22:
  v29 = StepFloatC * 3.0;
  if (v27 <= 0.25)
  {
    if (v27 < -0.25)
      v27 = -0.5 - v27;
  }
  else
  {
    v27 = 0.5 - v27;
  }
  v30 = v27 * 4.0;
  v31 = v29
      * (f32)((f32)((f32)((f32)((f32)(v30 * 1.5707963) + (f32)((f32)(v30 * (f32)(v30 * v30)) * -0.6459637)) + (f32)((f32)((f32)(v30 * v30) * (f32)(v30 * (f32)(v30 * v30))) * 0.07968968)) + (f32)((f32)((f32)(v30 * v30) * (f32)((f32)(v30 * v30) * (f32)(v30 * (f32)(v30 * v30)))) * -0.0046737655)) + (f32)((f32)((f32)(v30 * v30) * (f32)((f32)(v30 * v30) * (f32)((f32)(v30 * v30) * (f32)(v30 * (f32)(v30 * v30))))) * 0.00015148419));
  sBtlGetMoveXZ(0.0, 0.0, v13 + 90.0, v31, &aWork->StepOfsX, &aWork->StepOfsZ);
  UnitMng = wk->UnitMng;
  Unit_ListID = aWork->Unit_ListID;
  v35 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  if (!v35)
  {
LABEL_62:
    v67 = aWork->StepIntBuff[4];
    v69 = GetAW(v67);
    AW_XAtkDelete_BioArm_Mid(v69);
    Idx = v8->Idx;
    DelAW(Idx, 1);
    v72 = aWork->Idx;
    DelAW(v72, 1);
    return;
  }
  v36 = v35;
  if (v35->UID != aWork->Unit_UID)
    goto LABEL_62;
  if (!sBtlCheckLiveTarget2(v35))
    goto LABEL_62;
  Step = aWork->Step;
  v140 = StepOfsY;
  v141 = Y;
  switch (Step)
  {
    case 2:
      v139 = StepOfsX;
      v74 = aWork->StepFloatC + -0.008;
      StepTime = aWork->StepTime;
      v76 = v8->X;
      v78 = v8->Z;
      HomingX = aWork->HomingX;
      HomingZ = aWork->HomingZ;
      aWork->StepFloatB = aWork->StepFloatB + -0.02;
      v81 = VRF_DeltaTime;
      if (v74 < 0.0)
        v74 = 0.0;
      aWork->StepFloatC = v74;
      aWork->StepTime = StepTime + v81;
      LenXZ = sBtlGetLenXZ(v76, v78, HomingX, HomingZ);
      sBtlGetMoveXZ(v8->X, v8->Z, v13, LenXZ * aWork->StepFloatB, &aWork->X, &aWork->Z);
      if (aWork->StepFloatB <= 0.0)
      {
        v105 = aWork->StepIntBuff[4];
        v107 = GetAW(v105);
        AW_XAtkDelete_BioArm_Mid(v107);
        AW_XAtkDelete_BioArm(v8);
        AW_XAtkDelete_BioArm(aWork);
        return;
      }
      StepOfsX = v139;
      if ((aWork->StepFlag & 0x8000) == 0)
      {
        SetHit_BioArm(aWork, 190.0);
      }
      break;
    case 1:
      v84 = BYTE1(aWork->StepFlag);
      v86 = aWork->StepTime + VRF_DeltaTime;
      aWork->StepTime = v86;
      if ((v84 & 0x80) == 0)
      {
        SetHit_BioArm(aWork, 190.0);
        v86 = aWork->StepTime;
      }
      if (v86 > (f32)(FPS60 * 6.0))
        *(u64 *)&aWork->Step = (u32)(aWork->Step + 1);
      break;
    case 0:
      v40 = aWork->StepFloatC + 0.05;
      if (v40 > 0.8)
        v40 = 0.8;
      aWork->StepFloatC = v40;
      v138 = StepOfsX;
      v43 = wk->UnitMng;
      playerID = wk->playerID;
      v45 = sBtlSearchUnit_ID(v43, playerID);
      v46 = v45->pos.x / -100.0;
      p_HomingZ = &aWork->HomingZ;
      v48 = aWork->HomingZ;
      p_HomingX = &aWork->HomingX;
      v50 = aWork->HomingX;
      v51 = v45->pos.z / -100.0;
      v52 = sBtlGetLenXZ(v50, v48, v46, v51);
      if (v52 > 1.0)
      {
        v53 = *p_HomingX;
        v54 = v52 * 0.1;
        v55 = *p_HomingZ;
        if (v54 <= 0.08)
          v56 = v54;
        else
          v56 = 0.08;
        Lena = v56;
        v56 = Lena;
        sBtlGetMovePosToPos(v53, v55, v46, v51, v56, &aWork->HomingX, &aWork->HomingZ);
      }
      v57 = v8->X;
      v58 = v8->Z;
      v59 = *p_HomingX;
      v60 = *p_HomingZ;
      v61 = sBtlGetLenXZ(v57, v58, v59, v60);
      if (v61 >= 8.0)
      {
        if (v61 <= 18.0)
        {
LABEL_95:
          v87 = aWork->Z;
          Len = aWork->HomingFrame;
          v88.n64_u64[0] = *(u64 *)&aWork->X;
          v89.n64_u64[0] = *(u64 *)&aWork->HomingX;
          v90 = aWork->HomingZ;
          VelocityZ = aWork->VelocityZ;
          v132.n64_u64[0] = *(u64 *)&aWork->VelocityX;
          sub_1E94EE0(0);
          v96 = VRF_DeltaTime;
          if ((f32)(Len - v96) >= 0.0)
          {
            v110.n64_u64[0] = vsub_f32(v89, v88).n64_u64[0];
            aWork->HomingFrame = Len - v96;
            v92.n64_u32[1] = v93;
            StepOfsX = v138;
            v111.n64_u64[0] = vsub_f32(v110, vmul_f32((float32x2_t)__PAIR64__(LODWORD(Len), v132.n64_u32[0]), (float32x2_t)__PAIR64__(v132.n64_u32[1], LODWORD(Len)))).n64_u64[0];
            v95.n64_f32[0] = Len * Len;
            v112 = VelocityZ
                 + (f32)(v96 * (f32)(v94 + (f32)((f32)((f32)((f32)(v90 - v87) - (f32)(Len * VelocityZ)) + (f32)((f32)(v90 - v87) - (f32)(Len * VelocityZ))) / (f32)(Len * Len))));
            v113.n64_u64[0] = vadd_f32(v132, vmul_n_f32(vadd_f32(v92, vdiv_f32(vadd_f32(v111, v111), vdup_lane_s32(v95, 0))), v96)).n64_u64[0];
            *(float32x2_t *)&aWork->VelocityX = v113;
            aWork->VelocityZ = v112;
            aWork->Z = v87 + (f32)(v96 * v112);
            *(float32x2_t *)&aWork->X = vadd_f32(v88, vmul_n_f32(v113, v96));
          }
          else
          {
            v98 = aWork->HomingX;
            HomingY = aWork->HomingY;
            aWork->X = v98;
            aWork->Y = HomingY;
            v99 = aWork->HomingZ;
            v100 = aWork->Step + 1;
            aWork->Z = v99;
            aWork->Step = v100;
            aWork->StepTime = 0.0;
            v101 = aWork->StepOfsX;
            v102 = aWork->StepOfsZ;
            Lenb = aWork->StepOfsZ;
            v102 = Lenb;
            FootEff_XYZ(v98 + v101, HomingY + 0.4, v99 + v102, 4.0);
            FootEff_XYZ(aWork->X + aWork->StepOfsX, aWork->Y + 0.6, aWork->Z + aWork->StepOfsZ, 3.0);
            dds3SetQuake(30, 0xB4u);
            Add(aWork->X, aWork->Y, aWork->Z, aWork->Dir, 0, 0);
            v103.n64_u64[0] = vmul_f32(vadd_f32(*(float32x2_t *)&aWork->X, *(float32x2_t *)&aWork->StepOfsX), vdup_n_s32(0xC2C80000)).n64_u64[0];
            StepOfsX = v138;
            v104 = (f32)(aWork->Z + aWork->StepOfsZ) * -100.0;
            Lenc = v103.n64_u64[0];
            v103.n64_u64[0] = Lenc;
            *(float32x2_t *)&v142.x = v103;
            v142.z = v104;
            v142.w = 0.0;
            sBtlPlay3DSE(0x1009Bu, v142);
            *(u64 *)&aWork->Step = 1;
          }
          if ((aWork->StepFlag & 0x8000) == 0)
          {
            SetHit_BioArm(aWork, 190.0);
          }
          v116 = aWork->StepTime + VRF_DeltaTime;
          aWork->StepTime = v116;
          if (v116 > (f32)(FPS60 * 120.0))
          {
            aWork->StepBoolA = 0;
            *(u64 *)&aWork->Step = 2;
          }
          break;
        }
        v62 = v8->X;
        v63 = v8->Z;
        v64 = *p_HomingX;
        v65 = *p_HomingZ;
        v66 = 18.0;
      }
      else
      {
        v62 = v8->X;
        v63 = v8->Z;
        v64 = *p_HomingX;
        v65 = *p_HomingZ;
        v66 = 8.0;
      }
      sBtlGetMovePosToPos(v62, v63, v64, v65, v66, &aWork->HomingX, &aWork->HomingZ);
      goto LABEL_95;
  }
  v117 = v17 + StepOfsZ;
  v118 = v15 + StepOfsX;
  v119 = aWork->Z;
  v120 = aWork->X;
  v121 = aWork->StepOfsX;
  v122 = aWork->StepOfsZ;
  v123 = sBtlGetLenXZ(v118, v117, v120 + v121, v119 + v122);
  if (v123 > 0.01)
  {
    v124 = (f32)(aWork->Y + aWork->StepOfsY) - (f32)(v141 + v140);
    aWork->DirIKY = aWork->DirIKY
                         + (f32)((f32)(sBtlGetPosToDir(0.0, 0.0, v123, v124) - aWork->DirIKY) * 0.3);
  }
  v125 = aWork->Step;
  if (v125 < 2)
  {
    v127 = v8->X;
    v128 = v8->Z;
    v129 = aWork->HomingX;
    v130 = aWork->HomingZ;
    v131 = sBtlGetPosToDir(v127, v128, v129, v130);
    Dir_Hokan = sBtlGetDir_Hokan(aWork->MoveDir, v131, 5.0);
  }
  else
  {
    if (v125 != 2)
      return;
    Dir_Hokan = aWork->MoveDir + (f32)((f32)(v13 - aWork->MoveDir) * 0.1);
  }
  aWork->MoveDir = Dir_Hokan;
}

// 0x1e8a2b0
void AW_XAtkCalc_BioArm_Top_L(AW_WORK_t *aWork) {
  s32 *StepIntBuff;
  s32 v4;
  AW_WORK_t *AW;
  f32 X;
  f32 *p_Z;
  f32 Z;
  f32 v9;
  f32 *p_X;
  f32 v11;
  f32 PosToDir;
  f32 v14;
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v17;
  SBTLUNIT_WORK *v18;
  s32 v19;
  AW_WORK_t *v21;
  s32 Idx;
  s32 v24;
  f32 v26;
  f32 StepOfsX;
  f32 v28;
  f32 StepOfsZ;
  f32 v30;
  _BOOL4 StepBoolB;
  f32 VRF_DeltaTime_local;
  f32 v33;
  f32 StepFloatC;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 v41;
  f32 *p_StepOfsX;
  f32 *p_StepOfsZ;
  f32 v44;
  f32 v45;
  char v46;
  char v47;
  s32 Step;
  SBATTLE_WORK *v51;
  SBTLUNIT_LISTWORK *v52;
  s32 v53;
  SBTLUNIT_WORK *v54;
  f32 v55;
  f32 *v56;
  f32 *v57;
  f32 v58;
  u32 v59;
  f32 v60;
  f32 v61;
  f32 v62;
  f32 v63;
  f32 v64;
  f32 v65;
  f32 v66;
  f32 v67;
  f32 v68;
  f32 v69;
  f32 v70;
  f32 v71;
  f32 v73;
  SBTLUNIT_LISTWORK *v75;
  s32 playerID;
  SBTLUNIT_WORK *v77;
  f32 v78;
  f32 *p_HomingZ;
  f32 HomingZ;
  f32 *p_HomingX;
  f32 HomingX;
  f32 v83;
  f32 LenXZ;
  f32 v85;
  f32 v86;
  f32 v87;
  f32 v88;
  f32 v89;
  f32 v90;
  f32 v91;
  f32 v92;
  f32 v93;
  f32 v94;
  f32 v95;
  f32 v96;
  f32 v97;
  f32 v98;
  f32 v99;
  f32 StepTime;
  char v102;
  f32 v104;
  char v105;
  SBATTLE_WORK *v108;
  SBTLUNIT_LISTWORK *v109;
  s32 v110;
  SBTLUNIT_WORK *v111;
  f32 v112;
  f32 v113;
  f32 v114;
  f32 v115;
  f32 v116;
  f32 v117;
  f32 v118;
  SBATTLE_WORK *v120;
  SBTLUNIT_LISTWORK *v121;
  s32 v122;
  SBTLUNIT_WORK *v123;
  f32 v124;
  f32 v125;
  f32 v126;
  f32 v127;
  f32 v128;
  f32 v129;
  float32x2_t v130;
  f32 v131;
  f32 v132;
  f32 v133;
  float32x2_t v135;
  u32 v136;
  f32 v137;
  f32 v139;
  s64 v140;
  f32 v141;
  f32 v142;
  f32 v143;
  f32 StepFloatB;
  f32 v146;
  f32 v147;
  f32 v148;
  f32 v149;
  f32 v150;
  f32 v151;
  f32 v152;
  s64 v153;
  f32 v155;
  s32 v156;
  AW_WORK_t *v158;
  f32 VelocityZ;
  f32 v162;
  float32x2_t v163;
  float32x2_t v164;
  f32 v165;
  float32x2_t v167;
  u32 v168;
  f32 v169;
  int32x2_t v170;
  f32 v171;
  f32 HomingY;
  f32 v173;
  f32 v174;
  s32 v175;
  f32 v176;
  f32 v177;
  float32x2_t v178;
  f32 v179;
  s32 v180;
  float32x2_t v181;
  f32 v182;
  float32x2_t v183;
  f32 v184;
  f32 v185;
  f32 v186;
  f32 v187;
  f32 v188;
  f32 DirY;
  f32 MoveSpd;
  f32 v191;
  int32x2_t v192;
  float32x2_t v193;
  float32x2_t v194;
  f32 v195;
  float32x2_t v196;
  f32 v198;
  f32 v200;
  s32 v201;
  bool v202;
  f32 v203;
  f32 v204;
  f32 v205;
  f32 v206;
  f32 v207;
  f32 v208;
  f32 v209;
  u32 v210;
  f32 v211;
  f32 v212;
  f32 v213;
  f32 v214;
  f32 v215;
  f32 v216;
  f32 v217;
  f32 v218;
  f32 v219;
  f32 DirIKY;
  f32 v221;
  f32 v222;
  u32 v223;
  f32 v224;
  f32 v225;
  f32 v226;
  f32 v227;
  f32 v228;
  f32 Dir_Hokan;
  f32 v230;
  f32 v231;
  float32x2_t v232;
  float32x2_t pos;
  f32 posa;
  u64 posb;
  f32 v236;
  f32 HomingFrame;
  f32 v238;
  f32 v239;
  f32 v240;
  f32 v241;
  f32 v242;
  f32 StepOfsY;
  f32 Y;
  f32 *v245;
  f32 *v246;
  sdfVector3_t Vec;
  sdfVector3_t v248;
  sdfVector4_t v249;

  StepIntBuff = aWork->StepIntBuff;
  v248.z = 0.0;
  *(u64 *)&v248.x = 0;
  Vec.z = 0.0;
  *(u64 *)&Vec.x = 0;
  v4 = StepIntBuff[2];
  AW = GetAW(v4);
  X = AW->X;
  p_Z = &aWork->Z;
  Z = aWork->Z;
  v9 = AW->Z;
  p_X = &aWork->X;
  v11 = aWork->X;
  PosToDir = sBtlGetPosToDir(X, v9, v11, Z);
  v14 = PosToDir;
  Unit_ListID = aWork->Unit_ListID;
  UnitMng = wk->UnitMng;
  v17 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  if (!v17)
    goto LABEL_19;
  v18 = v17;
  if (v17->UID != aWork->Unit_UID)
    goto LABEL_19;
  if (sBtlCheckLiveTarget2(v17))
    goto LABEL_15;
LABEL_19:
  v19 = aWork->StepIntBuff[4];
  v21 = GetAW(v19);
  AW_XAtkDelete_BioArm_Mid(v21);
  Idx = AW->Idx;
  DelAW(Idx, 1);
  v24 = aWork->Idx;
  DelAW(v24, 1);
  return;
LABEL_15:
  if (ChkPause(aWork))
    return;
  v26 = aWork->X;
  StepOfsX = aWork->StepOfsX;
  StepOfsY = aWork->StepOfsY;
  Y = aWork->Y;
  v28 = aWork->Z;
  StepOfsZ = aWork->StepOfsZ;
  v30 = 0.5;
  StepBoolB = aWork->StepBoolB;
  VRF_DeltaTime_local = VRF_DeltaTime;
  if (aWork->StepBoolA)
    VRF_DeltaTime_local = VRF_DeltaTime_local * 0.5;
  v33 = aWork->StepFloatA + VRF_DeltaTime_local;
  StepFloatC = aWork->StepFloatC;
  aWork->StepFloatA = v33;
  v35 = v33 * 5.0;
  v36 = -(f32)(v33 * 5.0);
  if (!StepBoolB)
    v36 = v35;
  v37 = v36 * 0.15915494;
  v38 = (s32)v37;
  if (v37 == INFINITY)
    v38 = -2147500000.0;
  v39 = v37 - v38;
  if (v39 <= 0.5)
  {
    if (v39 >= -0.5)
      goto LABEL_44;
    v40 = 1.0;
  }
  else
  {
    v40 = -1.0;
  }
  v39 = v39 + v40;
LABEL_44:
  v41 = StepFloatC * 3.0;
  if (v39 <= 0.25)
  {
    if (v39 >= -0.25)
      goto LABEL_48;
    v30 = -0.5;
  }
  v39 = v30 - v39;
LABEL_48:
  p_StepOfsX = &aWork->StepOfsX;
  p_StepOfsZ = &aWork->StepOfsZ;
  v44 = v39 * 4.0;
  v45 = v41
      * (f32)((f32)((f32)((f32)((f32)(v44 * 1.5707963) + (f32)((f32)(v44 * (f32)(v44 * v44)) * -0.6459637)) + (f32)((f32)((f32)(v44 * v44) * (f32)(v44 * (f32)(v44 * v44))) * 0.07968968)) + (f32)((f32)((f32)(v44 * v44) * (f32)((f32)(v44 * v44) * (f32)(v44 * (f32)(v44 * v44)))) * -0.0046737655)) + (f32)((f32)((f32)(v44 * v44) * (f32)((f32)(v44 * v44) * (f32)((f32)(v44 * v44) * (f32)(v44 * (f32)(v44 * v44))))) * 0.00015148419));
  p_StepOfsX = &aWork->StepOfsX;
  p_StepOfsZ = &aWork->StepOfsZ;
  v245 = p_StepOfsX;
  v246 = p_StepOfsZ;
  sBtlGetMoveXZ(0.0, 0.0, v14 + 90.0, v45, p_StepOfsX, p_StepOfsZ);
  Step = aWork->Step;
  if (!(!v47 & v46))
  {
    switch (Step)
    {
      case 0:
        v73 = aWork->StepFloatC + 0.05;
        if (v73 > 0.8)
          v73 = 0.8;
        aWork->StepFloatC = v73;
        v239 = v26;
        v75 = wk->UnitMng;
        playerID = wk->playerID;
        v77 = sBtlSearchUnit_ID(v75, playerID);
        v78 = v77->pos.x / -100.0;
        p_HomingZ = &aWork->HomingZ;
        HomingZ = aWork->HomingZ;
        p_HomingX = &aWork->HomingX;
        HomingX = aWork->HomingX;
        v83 = v77->pos.z / -100.0;
        LenXZ = sBtlGetLenXZ(HomingX, HomingZ, v78, v83);
        v236 = StepOfsX;
        if (LenXZ > 1.0)
        {
          v85 = *p_HomingX;
          v86 = *p_HomingZ;
          v87 = LenXZ * 0.1;
          if (v87 <= 0.08)
            v88 = v87;
          else
            v88 = 0.08;
          sBtlGetMovePosToPos(v85, v86, v78, v83, v88, &aWork->HomingX, &aWork->HomingZ);
        }
        v89 = AW->X;
        v90 = AW->Z;
        v91 = *p_HomingX;
        v92 = *p_HomingZ;
        v93 = sBtlGetLenXZ(v89, v90, v91, v92);
        if (v93 >= 8.0)
        {
          if (v93 <= 18.0)
            goto LABEL_131;
          v94 = AW->X;
          v95 = AW->Z;
          v96 = *p_HomingX;
          v97 = *p_HomingZ;
          v98 = 18.0;
        }
        else
        {
          v94 = AW->X;
          v95 = AW->Z;
          v96 = *p_HomingX;
          v97 = *p_HomingZ;
          v98 = 8.0;
        }
        sBtlGetMovePosToPos(v94, v95, v96, v97, v98, &aWork->HomingX, &aWork->HomingZ);
LABEL_131:
        v232.n64_u64[0] = *(u64 *)&aWork->VelocityX;
        posa = aWork->HomingFrame;
        VelocityZ = aWork->VelocityZ;
        v162 = aWork->Z;
        v163.n64_u64[0] = *(u64 *)&aWork->X;
        v164.n64_u64[0] = *(u64 *)&aWork->HomingX;
        v165 = aWork->HomingZ;
        sub_1E94EE0(0);
        v171 = VRF_DeltaTime;
        if ((f32)(posa - v171) >= 0.0)
        {
          v167.n64_u32[1] = v168;
          aWork->HomingFrame = posa - v171;
          v181.n64_u64[0] = vsub_f32(vsub_f32(v164, v163), vmul_f32((float32x2_t)__PAIR64__(LODWORD(posa), v232.n64_u32[0]), (float32x2_t)__PAIR64__(v232.n64_u32[1], LODWORD(posa)))).n64_u64[0];
          v170.n64_f32[0] = posa * posa;
          v182 = VelocityZ
               + (f32)(v171 * (f32)(v169 + (f32)((f32)((f32)((f32)(v165 - v162) - (f32)(posa * VelocityZ)) + (f32)((f32)(v165 - v162) - (f32)(posa * VelocityZ))) / (f32)(posa * posa))));
          v183.n64_u64[0] = vadd_f32(v232, vmul_n_f32(vadd_f32(v167, vdiv_f32(vadd_f32(v181, v181), vdup_lane_s32(v170, 0))), v171)).n64_u64[0];
          *(float32x2_t *)&aWork->VelocityX = v183;
          aWork->VelocityZ = v182;
          aWork->Z = v162 + (f32)(v171 * v182);
          *(float32x2_t *)&aWork->X = vadd_f32(v163, vmul_n_f32(v183, v171));
          StepOfsX = v236;
          v26 = v239;
        }
        else
        {
          v173 = aWork->HomingX;
          HomingY = aWork->HomingY;
          aWork->X = v173;
          aWork->Y = HomingY;
          v174 = aWork->HomingZ;
          v175 = aWork->Step + 1;
          aWork->Z = v174;
          aWork->Step = v175;
          aWork->StepTime = 0.0;
          v176 = aWork->StepOfsX;
          v177 = aWork->StepOfsZ;
          FootEff_XYZ(v173 + v176, HomingY + 0.4, v174 + v177, 4.0);
          FootEff_XYZ(aWork->X + aWork->StepOfsX, aWork->Y + 0.6, aWork->Z + aWork->StepOfsZ, 3.0);
          dds3SetQuake(30, 0x96u);
          Add(aWork->X, aWork->Y, aWork->Z, aWork->Dir, 1, 0);
          v178.n64_u64[0] = vmul_f32(vadd_f32(*(float32x2_t *)&aWork->X, *(float32x2_t *)&aWork->StepOfsX), vdup_n_s32(0xC2C80000)).n64_u64[0];
          StepOfsX = v236;
          v26 = v239;
          v179 = (f32)(aWork->Z + aWork->StepOfsZ) * -100.0;
          posb = v178.n64_u64[0];
          v178.n64_u64[0] = posb;
          *(float32x2_t *)&v249.x = v178;
          v249.z = v179;
          v249.w = 0.0;
          sBtlPlay3DSE(0x10099u, v249);
          v180 = aWork->StepIntC - 1;
          aWork->StepIntC = v180;
          if (v180 < 1)
          {
            aWork->StepBoolA = 0;
            *(u64 *)&aWork->Step = 20;
          }
          else
          {
            *(u64 *)&aWork->Step = 10;
            aWork->StepBoolA = 1;
          }
        }
        if ((aWork->StepFlag & 0x8000) == 0)
        {
          SetHit_BioArm(aWork, 100.0);
        }
        v200 = aWork->StepTime + VRF_DeltaTime;
        aWork->StepTime = v200;
        if (v200 > (f32)(FPS60 * 120.0))
        {
          v201 = aWork->StepIntC - 1;
          v202 = aWork->StepIntC - 2 < 0;
          aWork->StepIntC = v201;
          if (v202 != __OFSUB__(v201, 1))
            goto LABEL_164;
          *(u64 *)&aWork->Step = 10;
          aWork->StepBoolA = 1;
        }
        break;
      case 1:
        v99 = aWork->StepFloatC + -0.001;
        StepTime = aWork->StepTime + VRF_DeltaTime;
        v102 = BYTE1(aWork->StepFlag);
        aWork->StepTime = StepTime;
        if (v99 < 0.3)
          v99 = 0.3;
        aWork->StepFloatC = v99;
        if ((v102 & 0x80) == 0)
        {
          SetHit_BioArm(aWork, 100.0);
          StepTime = aWork->StepTime;
        }
        v104 = 30.0;
        goto LABEL_97;
      case 2:
LABEL_164:
        v153 = 20;
        aWork->StepBoolA = 0;
LABEL_165:
        *(u64 *)&aWork->Step = v153;
        break;
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      case 9:
        break;
      case 10:
        v105 = BYTE1(aWork->StepFlag);
        StepTime = aWork->StepTime + VRF_DeltaTime;
        aWork->StepTime = StepTime;
        if ((v105 & 0x80) == 0)
        {
          SetHit_BioArm(aWork, 100.0);
          StepTime = aWork->StepTime;
        }
        v104 = 5.0;
LABEL_97:
        if (StepTime > (f32)(FPS60 * v104))
          *(u64 *)&aWork->Step = (u32)(aWork->Step + 1);
        break;
      default:
        switch (Step)
        {
          case 11:
            v238 = v26;
            v51 = wk;
            v52 = v51->UnitMng;
            v53 = v51->playerID;
            v54 = sBtlSearchUnit_ID(v52, v53);
            v55 = v54->pos.z;
            aWork->HomingX = v54->pos.x / -100.0;
            v56 = &aWork->HomingX;
            aWork->HomingZ = v55 / -100.0;
            v57 = &aWork->HomingZ;
            v58 = (f32)((f32)(u32)sub_1905740(500, 0) + -250.0) / 100.0;
            v59 = sub_1905740(500, 0);
            v60 = aWork->HomingX;
            aWork->DirY = 90.0;
            aWork->MoveSpd = 30.0;
            v61 = aWork->Z;
            v62 = v60 + v58;
            v63 = aWork->HomingZ;
            v64 = aWork->X;
            aWork->HomingX = v62;
            v65 = v63 + (f32)((f32)((f32)v59 + -250.0) / 100.0);
            aWork->HomingZ = v65;
            v66 = sBtlGetLenXZ(v64, v61, v62, v65);
            if (v66 >= 8.0)
            {
              if (v66 <= 18.0)
                goto LABEL_146;
              v67 = *p_X;
              v68 = *p_Z;
              v69 = *v56;
              v70 = *v57;
              v71 = 18.0;
            }
            else
            {
              v67 = *p_X;
              v68 = *p_Z;
              v69 = *v56;
              v70 = *v57;
              v71 = 8.0;
            }
            sBtlGetMovePosToPos(v67, v68, v69, v70, v71, &aWork->HomingX, &aWork->HomingZ);
LABEL_146:
            v184 = *p_X;
            v185 = *p_Z;
            v186 = *v56;
            v187 = *v57;
            v188 = sBtlGetPosToDir(v184, v185, v186, v187);
            DirY = aWork->DirY;
            aWork->MoveDir = v188;
            aWork->Dir = v188;
            *(u64 *)&v248.x = 0;
            v248.z = 0.0;
            GetDirToVec(v188, DirY, &v248);
            MoveSpd = aWork->MoveSpd;
            *(float32x2_t *)&aWork->VelocityX = vmul_n_f32(*(float32x2_t *)&v248.x, MoveSpd);
            aWork->VelocityZ = MoveSpd * v248.z;
            v26 = v238;
            v191 = FPS60;
            *(u64 *)&aWork->Step = 0;
            aWork->HomingFrame = v191 * 60.0;
            break;
          case 20:
            v240 = v26;
            v108 = wk;
            v109 = v108->UnitMng;
            v110 = v108->playerID;
            v111 = sBtlSearchUnit_ID(v109, v110);
            v112 = AW->X;
            v113 = v111->pos.x / -100.0;
            v114 = AW->Z;
            v115 = v111->pos.z / -100.0;
            sBtlGetMovePosToPos(v112, v114, v113, v115, 3.0, &aWork->HomingX, &aWork->HomingZ);
            v116 = AW->Y;
            aWork->DirY = 90.0;
            aWork->MoveSpd = 20.0;
            *(u64 *)&Vec.x = 0;
            Vec.z = 0.0;
            aWork->HomingY = v116 + 8.0;
            GetDirToVec(aWork->Dir, 90.0, &Vec);
            v117 = aWork->MoveSpd;
            *(float32x2_t *)&aWork->VelocityX = vmul_n_f32(*(float32x2_t *)&Vec.x, v117);
            aWork->VelocityZ = v117 * Vec.z;
            v26 = v240;
            v118 = FPS60;
            *(u64 *)&aWork->Step = 21;
            aWork->HomingFrame = v118 * 60.0;
            goto LABEL_166;
          case 21:
            v241 = v26;
            v120 = wk;
            v121 = v120->UnitMng;
            v122 = v120->playerID;
            v123 = sBtlSearchUnit_ID(v121, v122);
            v124 = AW->X;
            v125 = v123->pos.x / -100.0;
            v126 = AW->Z;
            v127 = v123->pos.z / -100.0;
            sBtlGetMovePosToPos(v124, v126, v125, v127, 3.0, &aWork->HomingX, &aWork->HomingZ);
            v128 = AW->Y + 8.0;
            v129 = aWork->VelocityZ;
            v130.n64_u64[0] = *(u64 *)&aWork->X;
            v131 = aWork->Z;
            pos.n64_u64[0] = *(u64 *)&aWork->VelocityX;
            HomingFrame = aWork->HomingFrame;
            v132 = aWork->HomingX;
            v133 = aWork->HomingZ;
            aWork->HomingY = v128;
            v230 = v128;
            v231 = v132;
            sub_1E94EE0(0);
            v139 = VRF_DeltaTime;
            if ((f32)(HomingFrame - v139) >= 0.0)
            {
              aWork->HomingFrame = HomingFrame - v139;
              v135.n64_u32[1] = v136;
              v192.n64_u64[0] = vsub_f32((float32x2_t)__PAIR64__(LODWORD(v230), LODWORD(v231)), v130).n64_u64[0];
              v193.n64_u64[0] = vsub_f32(v192, vmul_f32((float32x2_t)__PAIR64__(LODWORD(HomingFrame), pos.n64_u32[0]), (float32x2_t)__PAIR64__(pos.n64_u32[1], LODWORD(HomingFrame)))).n64_u64[0];
              v192.n64_f32[0] = HomingFrame * HomingFrame;
              v194.n64_u64[0] = vadd_f32(pos, vmul_n_f32(vadd_f32(v135, vdiv_f32(vadd_f32(v193, v193), vdup_lane_s32(v192, 0))), v139)).n64_u64[0];
              v195 = v129
                   + (f32)(v139 * (f32)(v137 + (f32)((f32)((f32)((f32)(v133 - v131) - (f32)(HomingFrame * v129)) + (f32)((f32)(v133 - v131) - (f32)(HomingFrame * v129))) / (f32)(HomingFrame * HomingFrame))));
              v196.n64_u64[0] = vmul_n_f32(v194, v139).n64_u64[0];
              *(float32x2_t *)&aWork->VelocityX = v194;
              aWork->VelocityZ = v195;
              v141 = v131 + (f32)(v139 * v195);
              *(float32x2_t *)&aWork->X = vadd_f32(v130, v196);
            }
            else
            {
              v140 = *(u64 *)&aWork->HomingX;
              *(u64 *)&aWork->Step = 22;
              *(u64 *)&aWork->X = v140;
              v141 = aWork->HomingZ;
            }
            v26 = v241;
            aWork->Z = v141;
            if ((aWork->StepFlag & 0x8000) == 0)
            {
              SetHit_BioArm(aWork, 100.0);
            }
            v198 = aWork->StepTime + VRF_DeltaTime;
            aWork->StepTime = v198;
            if (v198 <= (f32)(FPS60 * 120.0))
              goto LABEL_166;
            v153 = 22;
            goto LABEL_165;
          case 22:
            v242 = StepOfsZ;
            v142 = v28;
            v143 = v26;
            StepFloatB = aWork->StepFloatB;
            v146 = aWork->HomingX;
            v147 = aWork->HomingZ;
            aWork->StepTime = aWork->StepTime
                                   + VRF_DeltaTime;
            aWork->StepFloatB = StepFloatB + -0.05;
            v148 = aWork->StepFloatC + -0.1;
            if (v148 < 0.0)
              v148 = 0.0;
            aWork->StepFloatC = v148;
            v149 = AW->X;
            v150 = AW->Z;
            v151 = sBtlGetLenXZ(v149, v150, v146, v147);
            sBtlGetMoveXZ(AW->X, AW->Z, v14, v151 * aWork->StepFloatB, &aWork->X, &aWork->Z);
            v26 = v143;
            v28 = v142;
            v152 = aWork->StepFloatB;
            StepOfsZ = v242;
            aWork->Y = AW->Y + (f32)((f32)(aWork->HomingY - AW->Y) * v152);
            if (v152 > 0.0)
              goto LABEL_166;
            v153 = 23;
            goto LABEL_165;
          case 23:
            v155 = aWork->StepTime + VRF_DeltaTime;
            aWork->StepTime = v155;
            if (v155 <= (f32)(FPS60 * 3.0))
              goto LABEL_166;
            v156 = aWork->StepIntBuff[4];
            v158 = GetAW(v156);
            AW_XAtkDelete_BioArm_Mid(v158);
            AW_XAtkDelete_BioArm(AW);
            AW_XAtkDelete_BioArm(aWork);
            return;
          default:
            goto LABEL_166;
        }
        break;
    }
  }
LABEL_166:
  v203 = v26 + StepOfsX;
  v204 = v28 + StepOfsZ;
  v205 = *p_X;
  v206 = *p_Z;
  v207 = *v245;
  v208 = *v246;
  v209 = sBtlGetLenXZ(v203, v204, v205 + v207, v206 + v208);
  v210 = aWork->Step & 0xFFFFFFFE;
  if (v210 == 22)
  {
    v218 = 1.0;
    v217 = 0.0;
LABEL_182:
    v219 = sBtlGetPosToDir(0.0, 0.0, v217, v218);
    DirIKY = aWork->DirIKY;
    v221 = 0.1;
    goto LABEL_190;
  }
  v211 = v209;
  v212 = aWork->StepOfsY;
  v213 = (f32)(aWork->Y + v212) - (f32)(Y + StepOfsY);
  if (v210 == 20)
  {
    v214 = aWork->StepTime;
    v215 = FPS60;
    if (v214 < (f32)(v215 * 20.0))
      v213 = -5.0;
    if (v214 <= (f32)(v215 * 45.0))
      v216 = v213;
    else
      v216 = 5.0;
    if (v211 <= 0.01)
      goto LABEL_191;
    v217 = v211;
    v218 = v216;
    goto LABEL_182;
  }
  if (aWork->StepBoolA)
    v222 = -5.0;
  else
    v222 = (f32)(aWork->Y + v212) - (f32)(Y + StepOfsY);
  if (v211 <= 0.01)
    goto LABEL_191;
  v219 = sBtlGetPosToDir(0.0, 0.0, v211, v222);
  DirIKY = aWork->DirIKY;
  v221 = 0.3;
LABEL_190:
  aWork->DirIKY = DirIKY + (f32)((f32)(v219 - DirIKY) * v221);
LABEL_191:
  v223 = aWork->Step;
  if (v223 <= 0xB && ((1 << v223) & 0xC03) != 0)
  {
    v224 = AW->X;
    v225 = AW->Z;
    v226 = aWork->HomingX;
    v227 = aWork->HomingZ;
    v228 = sBtlGetPosToDir(v224, v225, v226, v227);
    Dir_Hokan = sBtlGetDir_Hokan(aWork->MoveDir, v228, 5.0);
    goto LABEL_196;
  }
  if ((v223 & 0xFFFFFFFC) == 0x14)
  {
    Dir_Hokan = aWork->MoveDir + (f32)((f32)(v14 - aWork->MoveDir) * 0.1);
LABEL_196:
    aWork->MoveDir = Dir_Hokan;
  }
}

// 0x1e8b7c0
void AW_XAtkCalc_BioArm_Root(AW_WORK_t *aWork) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 Unit_ListID;
  SBTLUNIT_WORK *v7;
  f32 z;
  f32 VelocityZ;

  if (ChkPause(aWork))
    return;
  if (!aWork->Step)
  {
    UnitMng = wk->UnitMng;
    Unit_ListID = aWork->Unit_ListID;
    v7 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
    if (v7)
    {
      if (v7->UID == aWork->Unit_UID)
      {
        z = v7->pos.z;
        VelocityZ = aWork->VelocityZ;
        *(float32x2_t *)&aWork->X = vadd_f32(*(float32x2_t *)&aWork->VelocityX, vdiv_f32(*(float32x2_t *)&v7->pos.x, vdup_n_s32(0xC2C80000)));
        aWork->Z = VelocityZ + (f32)(z / -100.0);
      }
    }
  }
}

// 0x1e8b920
void AW_XAtkCalc_BioArm_Mid(AW_WORK_t *aWork) {
  f32 LaserOfsLen;
  s32 v5;
  AW_WORK_t *AW;
  AW_WORK_t *v7;
  s32 *StepIntBuff;
  AW_WORK_t *v9;
  s32 v10;
  AW_WORK_t *v11;
  s32 v12;
  f32 v13;
  float32x2_t *v14;
  f32 *p_X;
  f32 X;
  f32 *p_Z;
  f32 Z;
  f32 *v19;
  f32 v20;
  f32 v21;
  f32 PosToDir;
  f32 StepFloatA;
  f32 v24;
  f32 v25;
  _BOOL4 StepBoolB;
  f32 StepFloatC;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  s32 Step;
  f32 Y;
  f32 v40;
  f32 v41;
  f32 v42;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 v47;
  float32x2_t v48;
  float32x2_t v49;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 v53;
  f32 v54;
  f32 v55;
  f32 LenXZ;
  f32 v58;
  f32 v59;
  char v60;
  float32x2_t *v61;
  f32 GetY;

  GetY = 0.0;
  if (ChkPause(aWork))
    return;
  LaserOfsLen = aWork->LaserOfsLen;
  v5 = aWork->StepIntBuff[1];
  AW = GetAW(v5);
  v7 = GetAW(aWork->StepIntBuff[2]);
  StepIntBuff = aWork->StepIntBuff;
  v9 = v7;
  v10 = StepIntBuff[4];
  if (v10 != -1)
  {
    v11 = GetAW(v10);
    v12 = aWork->StepIntBuff[5];
    v13 = 1.0;
    v61 = v11;
    if (v12 != -1)
      goto LABEL_13;
LABEL_17:
    v14 = 0;
    goto LABEL_18;
  }
  v12 = StepIntBuff[5];
  v13 = 1.0;
  v61 = 0;
  if (v12 == -1)
    goto LABEL_17;
LABEL_13:
  v14 = GetAW(v12);
LABEL_18:
  p_X = &aWork->X;
  X = aWork->X;
  p_Z = &v9->Z;
  Z = v9->Z;
  v19 = &aWork->Z;
  v20 = aWork->Z;
  v21 = v9->X;
  PosToDir = sBtlGetPosToDir(v21, Z, X, v20);
  StepFloatA = AW->StepFloatA;
  v24 = PosToDir;
  v25 = LaserOfsLen + LaserOfsLen;
  StepBoolB = AW->StepBoolB;
  StepFloatC = AW->StepFloatC;
  aWork->StepFloatA = StepFloatA;
  v28 = StepFloatA - (f32)(v13 - LaserOfsLen);
  if ((f32)(LaserOfsLen + LaserOfsLen) > v13)
    v25 = v13;
  v29 = v28 * 5.0;
  v30 = -(f32)(v28 * 5.0);
  v31 = StepFloatC * 3.0;
  if (!StepBoolB)
    v30 = v29;
  v32 = v30 * 0.15915494;
  v33 = -2147500000.0;
  if (v32 != INFINITY)
    v33 = (s32)v32;
  v34 = v32 - v33;
  if (v34 <= 0.5)
  {
    if (v34 < -0.5)
      v34 = v34 + v13;
  }
  else
  {
    v34 = v34 + -1.0;
  }
  v35 = v25 * v31;
  if (v34 <= 0.25)
  {
    if (v34 < -0.25)
      v34 = -0.5 - v34;
  }
  else
  {
    v34 = 0.5 - v34;
  }
  v36 = v34 * 4.0;
  v37 = v35
      * (f32)((f32)((f32)((f32)((f32)(v36 * 1.5707963) + (f32)((f32)(v36 * (f32)(v36 * v36)) * -0.6459637)) + (f32)((f32)((f32)(v36 * v36) * (f32)(v36 * (f32)(v36 * v36))) * 0.07968968)) + (f32)((f32)((f32)(v36 * v36) * (f32)((f32)(v36 * v36) * (f32)(v36 * (f32)(v36 * v36)))) * -0.0046737655)) + (f32)((f32)((f32)(v36 * v36) * (f32)((f32)(v36 * v36) * (f32)((f32)(v36 * v36) * (f32)(v36 * (f32)(v36 * v36))))) * 0.00015148419));
  sBtlGetMoveXZ(0.0, 0.0, v24 + 90.0, v37, &aWork->StepOfsX, &aWork->StepOfsZ);
  Step = aWork->Step;
  if (Step != 1)
  {
    if (!Step)
    {
      Y = aWork->Y;
      v40 = v9->Z;
      v41 = v9->X;
      v42 = v9->Y;
      v43 = AW->Z;
      v44 = AW->X;
      v45 = AW->Y;
      sBtlGetNormalPosToPos(v41, v42, v40, v44, v45, v43, LaserOfsLen, &aWork->X, &GetY, &aWork->Z);
      v47 = GetY;
      if (Y >= GetY)
      {
        if (v61 && v14)
        {
          if (LaserOfsLen <= 0.9)
          {
            v50 = 0.4;
            v51 = 0.6;
          }
          else
          {
            v50 = 0.6;
            v51 = 0.4;
          }
          v47 = (f32)(v14[10].n64_f32[1] * v50) + (f32)(v61[10].n64_f32[1] * v51);
        }
        else if (!v61 && v14)
        {
          v47 = (f32)(v14[10].n64_f32[1] * 0.4) + (f32)(v9->Y * 0.6);
        }
        v60 = BYTE1(aWork->StepFlag);
        aWork->Y = v47;
        if ((v60 & 0x80) == 0)
        {
          SetHit_BioArm(aWork, 120.0);
        }
      }
      else
      {
        aWork->Y = GetY;
      }
      if (AW->Step >= 20)
        *(u64 *)&aWork->Step = 1;
    }
    return;
  }
  if (v61 && v14)
  {
    p_Z = &v61[11];
    v48.n64_u64[0] = v61[10].n64_u64[0];
    v49.n64_u64[0] = vmul_f32(v14[10], (float32x2_t)0x3F0000003F000000LL).n64_u64[0];
LABEL_52:
    *(float32x2_t *)p_X = vadd_f32(v49, vmul_f32(v48, (float32x2_t)0x3F0000003F000000LL));
    *v19 = (f32)(v14[11].n64_f32[0] * 0.5) + (f32)(*p_Z * 0.5);
    goto LABEL_53;
  }
  if (!v61 && v14)
  {
    v49.n64_u64[0] = vmul_f32(v14[10], (float32x2_t)0x3F0000003F000000LL).n64_u64[0];
    v48.n64_u64[0] = *(u64 *)&v9->X;
    goto LABEL_52;
  }
LABEL_53:
  v52 = v9->X;
  v53 = v9->Z;
  v54 = AW->X;
  v55 = AW->Z;
  LenXZ = sBtlGetLenXZ(v52, v53, v54, v55);
  if (LenXZ >= sBtlGetLenXZ(v9->X, v9->Z, *p_X, *v19))
  {
    v58 = aWork->Y;
    v59 = AW->Y;
    if (v58 <= v59)
    {
LABEL_57:
      if ((aWork->StepFlag & 0x8000) != 0)
        return;
      goto LABEL_61;
    }
  }
  else
  {
    *p_X = AW->X;
    *v19 = AW->Z;
    v58 = aWork->Y;
    v59 = AW->Y;
    if (v58 <= v59)
      goto LABEL_57;
  }
  aWork->Y = v58 + (f32)((f32)(v58 - v59) * -0.2);
  if ((aWork->StepFlag & 0x8000) != 0)
    return;
LABEL_61:
  SetHit_BioArm(aWork, 120.0);
}

// 0x1e8bf70
void AW_XAtkDraw_BioArm(AW_WORK_t *aWork) {
  void *Obj;
  void *transform;
  void *v6;
  void *v7;
  sdfVector3_t v8;
  sdfVector3_t v9;
  sdfVector3_t v10;

  Obj = aWork->Obj;
  if (op_Equality(Obj, 0, 0))
    return;
  transform = get_transform(aWork->Obj, 0);
  v8.x = aWork->X + aWork->StepOfsX;
  v8.y = (f32)(aWork->Y + aWork->StepOfsY) + 0.5;
  v8.z = aWork->Z + aWork->StepOfsZ;
  set_localPosition(transform, v8, 0);
  v6 = get_transform(aWork->Obj, 0);
  v9.x = aWork->DirIKY;
  v9.z = 0.0;
  v9.y = aWork->MoveDir;
  set_eulerAngles(v6, v9, 0);
  v7 = get_transform(aWork->Obj, 0);
  v10.x = aWork->Scale;
  v10.y = v10.x;
  v10.z = v10.x;
  set_localScale(v7, v10, 0);
  return;
}
