#include "types.h"
#include "SKLID.h"
#include "aw.h"
#include "aw_rsbullet.h"
#include "dds3vrf.h"
#include "sbtl.h"
#include "sbtleff.h"
#include "sbtlplayer_gunshot.h"
#include "sbtlplayer_magic.h"
#include "sbtlscene.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

static void SetHit(AW_WORK_t *aWork);

// 0x1e4ad70
void Init(void) {
  ;
}

// 0x1e4ad80
s32 Add(s32 _ListID, SKLID _SkillID, f32 _X, f32 _Y, f32 _Z, f32 _Dir) {
  f32 Dir180;
  s64 v16;
  s64 v17;
  Il2CppObject *v18;
  f32 v19;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 w;
  Il2CppObject *v27;
  AW_Func v28;
  AW_Func v29;
  s32 v30;
  AW_WORK_t *AW;
  float32x2_t *v32;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v35;
  SBTLUNIT_WORK *v36;
  u32 v37;
  sdfVector4_t *p_pos;
  float32x2_t v39;
  SBTLUNIT_LISTWORK *v42;
  s32 playerID;
  f32 v44;
  u32 v45;
  f32 v47;
  f32 v48;
  u64 v49;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 v53;
  s32 *StepIntBuff;
  il2cpp_array_size_t max_length;
  char *v56;
  sdfVector4_t v58;
  sdfVector3_t Vec;
  sdfVector3_t v60;
  sdfQuaternion_t v61;

  Vec.z = 0.0;
  *(u64 *)&v58.x = 0;
  *(u64 *)&v58.z = 0;
  *(u64 *)&Vec.x = 0;
  Dir180 = sBtlGetDir180(Dir);
  if (SkillID <= 39)
  {
    v17 = 124;
    if (SkillID == 23)
      v17 = 126;
    if (SkillID == 39)
      v16 = 128;
    else
      v16 = v17;
  }
  else
  {
    switch (SkillID)
    {
      case 55:
        v16 = 130;
        break;
      case 163:
        v16 = 138;
        break;
      case 191:
        v16 = 122;
        break;
      default:
        v16 = 124;
        break;
    }
  }
  v18 = get_Instance()->AwPrefab[v16];
  v19 = X / -100.0;
  v21 = identityQuaternion.x;
  v22 = identityQuaternion.y;
  v23 = Y / -100.0;
  v24 = Z / -100.0;
  v25 = identityQuaternion.z;
  w = identityQuaternion.w;
  v60.x = v19;
  v60.y = v23;
  v60.z = v24;
  v61.x = v21;
  v61.y = v22;
  v61.z = v25;
  v61.w = w;
  v27 = Instantiate_object__39504752(v18, v60, v61);
  v28 = Allocate(AW_Func);
  _ctor(v28, 0, Method_Project_AW_RsBullet_Calc__, 0);
  v29 = Allocate(AW_Func);
  _ctor(v29, 0, Method_Project_AW_RsBullet_Draw__, 0);
  v30 = Add(273, v19, v23, v24, v27, v28, v29, 1);
  Set_HDEff(v30, 1, -1);
  AW = GetAW(v30);
  v32 = AW;
  AW->Unit_ListID = ListID;
  AW->StepFloatC = 0.5;
  AW->DirY = 90.0;
  AW->StepOfsY = 0.1;
  AW->StepFloatA = 0.0;
  AW->StepFloatB = 0.0;
  AW->Dir = Dir180;
  AW->HDEff_SkillID = SkillID;
  *(u64 *)&AW->HDEff_Speed = 0x3F8000003F800000LL;
  AW->HDEff_PosLink = 0;
  AW->SubIdx = SkillID;
  if (SkillID <= 39)
  {
    if ((u32)SkillID > 0x27 || ((1 << SkillID) & 0x8000800100LL) == 0)
      goto LABEL_51;
LABEL_31:
    UnitMng = wk->UnitMng;
    v35 = sBtlSearchUnit_ID(UnitMng, ListID);
    if (!v35)
      goto LABEL_46;
    goto LABEL_37;
    if (!v35)
    {
LABEL_46:
      v45 = v32[32].n64_u32[1];
      v32[13].n64_u32[1] = 0;
      *(u64 *)&Vec.x = 0;
      Vec.z = 0.0;
      v47 = v32[13].n64_f32[0];
      v32[16].n64_u32[0] = v45;
      GetDirToVec(v47, 0.0, &Vec);
      v48 = v32[16].n64_f32[0];
      v49 = vmul_n_f32(*(float32x2_t *)&Vec.x, v48).n64_u64[0];
      v50 = v48 * Vec.z;
      v51 = v32[10].n64_f32[0];
      v52 = v32[26].n64_f32[1];
      v32[27].n64_u64[0] = v49;
      v32[28].n64_f32[0] = v50;
      v53 = sBtlGetLenXZ(v51, v32[11].n64_f32[0], v32[25].n64_f32[1], v52) / v32[16].n64_f32[0];
      if (v53 > 60.0)
        v53 = 60.0;
      v32[25].n64_f32[0] = v53 * FPS60;
      goto LABEL_51;
    }
LABEL_37:
    v36 = v35;
    *(u64 *)&v58.x = 0;
    *(u64 *)&v58.z = 0;
    if (!v37)
    p_pos = &v58;
    GetUnitHelperPos(v36, &v58);
    v39.n64_u64[0] = vdiv_f32(*(float32x2_t *)&v58.y, vdup_n_s32(0xC2C80000)).n64_u64[0];
    if (v36->para->devilid == 314)
    {
      v42 = wk->UnitMng;
      playerID = wk->playerID;
      p_pos = &sBtlSearchUnit_ID(v42, playerID)->pos;
    }
    v44 = p_pos->x;
    v32[26].n64_u64[0] = v39.n64_u64[0];
    v32[25].n64_f32[1] = v44 / -100.0;
    goto LABEL_46;
  }
  switch (SkillID)
  {
    case 191:
      goto LABEL_31;
    case 163:
      AW->StepFloatC = 0.7;
      StepIntBuff = AW->StepIntBuff;
      max_length = StepIntBuff->max_length;
      if ((s32)max_length < 1)
        goto LABEL_53;
      goto LABEL_52;
    case 55:
      goto LABEL_31;
  }
LABEL_51:
  StepIntBuff = v32[38].n64_u64[0];
  max_length = StepIntBuff->max_length;
  if ((s32)max_length >= 1)
LABEL_52:
    sub_188E3B0(StepIntBuff, 0, 4 * (u32)max_length);
LABEL_53:
  v56 = "AW_RsBullet";
  v32[52].n64_u64[0] = "AW_RsBullet";
  return v30;
}

// 0x1e4b340
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e4b3b0
static void SetHit(AW_WORK_t *aWork) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v7;
  f32 v8;
  f32 v9;
  f32 Dir;
  s64 i;
  SBTLUNIT_WORK *pUnit;
  s32 *StepIntBuff;
  char v16;
  s64 max_length;
  s32 *m_Items;
  s32 v19;
  s32 v20;
  f32 v21;
  f32 v22;
  f32 x;
  f32 z;
  s32 *v25;
  s64 v26;
  s32 *v27;
  f32 v28;
  f32 y;
  s32 HDEff_SkillID;
  f32 v31;
  f32 w;
  f32 ToZ;
  f32 ToX;
  sdfVector4_t v35;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v7 = sBtlSearchUnit_ID(UnitMng, playerID);
  v8 = aWork->X * -100.0;
  v9 = aWork->Z * -100.0;
  Dir = aWork->Dir;
  ToZ = v9;
  ToX = v8;
  sBtlGetMoveXZ(v8, v9, Dir + 180.0, 200.0, &ToX, &ToZ);
  for (i = 0; i != 48; ++i)
  {
    pUnit = wk->UnitMng->pUnitL[i]->pUnit;
    if (pUnit)
    {
      if ((pUnit->side & 2) != 0)
      {
        StepIntBuff = aWork->StepIntBuff;
        if (pUnit->para->devilid != 314 || !StepIntBuff[0])
        {
          if ((s32)StepIntBuff->max_length < 1)
            goto LABEL_39;
          v16 = 0;
          max_length = (u32)StepIntBuff->max_length;
          m_Items = StepIntBuff;
          do
          {
            v20 = *m_Items++;
            v19 = v20;
            if (!v20)
              break;
            --max_length;
            v16 |= v19 == pUnit->UID;
          }
          while (max_length);
          if ((v16 & 1) == 0)
          {
LABEL_39:
            if (!sBtlCheckDamageTarget(pUnit))
              continue;
            v22 = ToZ;
            v21 = ToX;
            x = pUnit->pos.x;
            z = pUnit->pos.z;
            if ((f32)(sBtlGetLenXZ(v21, v22, x, z) - pUnit->actaiwk->hit_area_r) <= 400.0)
            {
              v25 = aWork->StepIntBuff;
              if ((s32)v25->max_length >= 1)
              {
                v26 = (u32)v25->max_length;
                v27 = v25;
                while (*v27)
                {
                  ++v27;
                  if (!--v26)
                    goto LABEL_11;
                }
                *v27 = pUnit->UID;
                v28 = pUnit->pos.x;
                y = pUnit->pos.y;
                HDEff_SkillID = aWork->HDEff_SkillID;
                v31 = pUnit->pos.z;
                w = pUnit->pos.w;
                v35.x = v28;
                v35.y = y;
                v35.z = v31;
                v35.w = w;
                SetDamageProc(pUnit, v7, HDEff_SkillID, v35);
              }
            }
          }
        }
      }
    }
LABEL_11:
    ;
  }
}

// 0x1e4b6c0
bool Chk_C_ZANTOBI(void) {
  return GetAW_SubIdx(273, 163) != 0;
}

// 0x1e4b730
void Calc(AW_WORK_t *aWork) {
  f32 X;
  f32 Y;
  f32 Z;
  __int128 v8;
  Il2CppObject *current;
  s32 v10;
  s32 Idx;
  f32 v13;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 Unit_ListID;
  SBTLUNIT_WORK *v17;
  SBTLUNIT_WORK *v18;
  u32 v19;
  sdfVector4_t *p_HelperPos;
  f32 v21;
  f32 v22;
  SBTLUNIT_LISTWORK *v25;
  s32 playerID;
  f32 v27;
  f32 StepOfsX;
  f32 StepOfsY;
  f32 StepOfsZ;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 GroundPos;
  s32 HDEff_SkillID;
  f32 v38;
  f32 v40;
  f32 v41;
  f32 v42;
  f32 v43;
  s32 v44;
  f32 v46;
  f32 *p_StepTime;
  s32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  s32 v52;
  _BOOL4 v53;
  f32 StepTime;
  int8x8_t v56;
  int8x8_t v57;
  f32 v58;
  SBTLUNIT_LISTWORK *v60;
  s32 v61;
  f32 v63;
  f32 v64;
  f32 HomingFrame;
  f32 VelocityX;
  f32 VelocityY;
  f32 VelocityZ;
  f32 v69;
  f32 v70;
  f32 v71;
  f32 v72;
  f32 v73;
  f32 Dir;
  f32 PosToDir;
  f32 AtoB_LR;
  f32 ABS;
  f32 StepFloatA;
  f32 v81;
  f32 v82;
  f32 v83;
  f32 v84;
  f32 v85;
  f32 v86;
  f32 v87;
  f32 v88;
  f32 v89;
  f32 StepFloatC;
  s64 v91;
  f32 LenXZ;
  f32 v93;
  f32 DirY;
  SBTLUNIT_LISTWORK *v97;
  s32 v98;
  SBTLUNIT_WORK *v99;
  f32 v100;
  f32 v101;
  f32 v102;
  SBTLUNIT_LISTWORK *v103;
  s32 v104;
  SBTLUNIT_WORK *v105;
  f32 v106;
  f32 v107;
  f32 v108;
  f32 v109;
  f32 v110;
  f32 v111;
  f32 v112;
  f32 StepFloatB;
  f32 v114;
  f32 v115;
  f32 v116;
  System_Collections_Generic_List_Enumerator_T__o v117;
  s64 v118;
  s64 v119;
  s64 v120;
  sdfVector4_t HelperPos;
  System_Collections_Generic_List_Enumerator_T__o v122;
  s64 ToZ;

  memset(&v122, 0, sizeof(v122));
  ToZ = 0;
  *(u64 *)&HelperPos.x = 0;
  *(u64 *)&HelperPos.z = 0;
  v118 = 0;
  v119 = 0;
  v120 = 0;
  if (ChkPause(aWork))
    return;
  X = aWork->X;
  Y = aWork->Y;
  Z = aWork->Z;
  if (aWork->HDEff_SkillID != 163)
    goto LABEL_15;
  _GetEnumerator(&v117, aWork->ParticleSystemList);
  v8 = *(_OWORD *)&v117._list;
  v117._list = 0;
  *(u64 *)&v117._index = &v122;
  v122._current = v117._current;
  *(_OWORD *)&v122._list = v8;
  do
  {
    if (!_MoveNext(&v122))
    {
      _Dispose(&v122);
LABEL_19:
      Idx = aWork->Idx;
      DelAW(Idx, 1);
      return;
    }
    current = v122._current;
  }
  while (op_Equality(current, 0, 0) || !IsAlive_61441520(current, 0));
  _Dispose(&v122);
LABEL_15:
  v10 = 0;
  switch (aWork->Step)
  {
    case 0:
      UnitMng = wk->UnitMng;
      Unit_ListID = aWork->Unit_ListID;
      v17 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
      if (!v17)
      {
        p_StepTime = &aWork->StepTime;
        v10 = 0;
        if (aWork->HDEff_SkillID == 163)
          v48 = 20;
        else
          v48 = 10;
LABEL_75:
        aWork->Step = v48;
        goto LABEL_76;
      }
      v18 = v17;
      *(u64 *)&HelperPos.x = 0;
      *(u64 *)&HelperPos.z = 0;
      if (!v19)
      p_HelperPos = &HelperPos;
      GetUnitHelperPos(v18, &HelperPos);
      v22 = HelperPos.y;
      v21 = HelperPos.z;
      if (v18->para->devilid == 314)
      {
        v25 = wk->UnitMng;
        playerID = wk->playerID;
        p_HelperPos = &sBtlSearchUnit_ID(v25, playerID)->pos;
      }
      v27 = v22 / 100.0;
      StepOfsX = aWork->StepOfsX;
      StepOfsY = aWork->StepOfsY;
      StepOfsZ = aWork->StepOfsZ;
      v31 = v18->pos.x;
      v32 = v18->pos.z;
      v33 = p_HelperPos->x / 100.0;
      v34 = v21 / 100.0;
      X = StepOfsX - v33;
      Y = StepOfsY - v27;
      Z = StepOfsZ - v34;
      GroundPos = sBtlGetGroundPos(v31, v32);
      HDEff_SkillID = aWork->HDEff_SkillID;
      v38 = GroundPos / -100.0;
      if (HDEff_SkillID <= 39)
      {
        if ((u32)HDEff_SkillID <= 0x27 && ((1 << HDEff_SkillID) & 0x8000800100LL) != 0)
          goto LABEL_53;
        goto LABEL_55;
      }
      if (HDEff_SkillID == 55)
        goto LABEL_53;
      if (HDEff_SkillID == 163)
      {
        SetHit(aWork);
LABEL_73:
        v10 = 0;
        p_StepTime = &aWork->StepTime;
        StepTime = aWork->StepTime;
        v56.n64_u64[0] = vdup_n_s32(0x42B40000u).n64_u64[0];
        v57.n64_u64[0] = vadd_f32(vld1_dup_f32(&VRF), *(float32x2_t *)&aWork->StepFloatA).n64_u64[0];
        *(int8x8_t *)&aWork->StepFloatA = vbsl_s8(vcgt_f32(v57, v56), v56, v57);
        v58 = StepTime + VRF_DeltaTime;
        aWork->StepTime = v58;
        if (v58 <= (f32)(FPS60 * 120.0))
          goto LABEL_77;
        v48 = 1;
        goto LABEL_75;
      }
      if (HDEff_SkillID != 191)
        goto LABEL_55;
LABEL_53:
      v49 = v38 + 0.3;
      if (Y < v49)
        Y = v49;
LABEL_55:
      v50 = aWork->X;
      v51 = aWork->Z;
      if (sBtlGetLenXZ(v50, v51, X, StepOfsZ - v34) > (f32)(aWork->StepFloatC + 0.2))
        goto LABEL_73;
      v52 = aWork->HDEff_SkillID;
      if (v52 > 39)
      {
        if (v52 != 55)
        {
          if (v52 == 163)
          {
            v10 = 0;
            aWork->Step = 3;
            p_StepTime = &aWork->StepTime;
          }
          else
          {
            if (v52 != 191)
              goto LABEL_63;
            sBtlPlayerCallHitDone();
LABEL_71:
            v10 = 1;
            aWork->Step = 2;
            p_StepTime = &aWork->StepTime;
          }
LABEL_76:
          *p_StepTime = 0.0;
          goto LABEL_77;
        }
LABEL_70:
        CallHitDone();
        goto LABEL_71;
      }
      v10 = 0;
      if ((u32)v52 <= 0x27 && ((1 << v52) & 0x8000800100LL) != 0)
        goto LABEL_70;
LABEL_77:
      v42 = aWork->X;
      v41 = aWork->Y;
      v43 = aWork->Z;
      v44 = aWork->HDEff_SkillID;
      if (v44 <= 39)
      {
LABEL_64:
        v53 = 0;
        if ((u32)v44 <= 0x27 && ((1 << v44) & 0x8000800100LL) != 0)
        {
LABEL_81:
          v60 = wk->UnitMng;
          v61 = aWork->Unit_ListID;
          v53 = sBtlSearchUnit_ID(v60, v61) != 0;
        }
        if (v10)
          goto LABEL_87;
LABEL_95:
        v116 = Y;
        if (v53)
        {
          HomingFrame = aWork->HomingFrame;
          aWork->HomingX = X;
          aWork->HomingY = Y;
          VelocityX = aWork->VelocityX;
          VelocityY = aWork->VelocityY;
          aWork->HomingZ = Z;
          VelocityZ = aWork->VelocityZ;
          v70 = aWork->X;
          v69 = aWork->Y;
          v71 = aWork->Z;
          v115 = Z;
          v72 = X;
          v73 = VelocityY;
          VelocityY = v73;
          X = v72;
          Z = v115;
          if ((f32)(HomingFrame - VRF_DeltaTime) >= 0.0)
          {
            v81 = zeroVector.x;
            v83 = zeroVector.y;
            v82 = zeroVector.z;
            aWork->HomingFrame = HomingFrame - VRF_DeltaTime;
            v84 = VelocityZ
                + (f32)(VRF_DeltaTime * (f32)((f32)((f32)((f32)((f32)(Z - v71) - (f32)(HomingFrame * VelocityZ)) + (f32)((f32)(Z - v71) - (f32)(HomingFrame * VelocityZ))) / (f32)(HomingFrame * HomingFrame)) + v82));
            v85 = VelocityX
                + (f32)(VRF_DeltaTime * (f32)((f32)((f32)((f32)((f32)(X - v70) - (f32)(HomingFrame * VelocityX)) + (f32)((f32)(X - v70) - (f32)(HomingFrame * VelocityX))) / (f32)(HomingFrame * HomingFrame)) + v81));
            v86 = VelocityY
                + (f32)(VRF_DeltaTime * (f32)((f32)((f32)((f32)((f32)(v116 - v69) - (f32)(HomingFrame * VelocityY)) + (f32)((f32)(v116 - v69) - (f32)(HomingFrame * VelocityY))) / (f32)(HomingFrame * HomingFrame)) + v83));
            aWork->VelocityZ = v84;
            aWork->VelocityX = v85;
            aWork->VelocityY = v86;
            aWork->X = v70 + (f32)(VRF_DeltaTime * v85);
            aWork->Y = v69 + (f32)(VRF_DeltaTime * v86);
            aWork->Z = v71 + (f32)(VRF_DeltaTime * v84);
          }
          else
          {
            *(u64 *)&aWork->X = *(u64 *)&aWork->HomingX;
            aWork->Z = aWork->HomingZ;
          }
        }
        else
        {
          Dir = aWork->Dir;
          PosToDir = sBtlGetPosToDir(v42, v43, X, Z);
          AtoB_LR = sBtlGetAtoB_LR(aWork->Dir, PosToDir);
          ABS = sBtlGetABS(AtoB_LR);
          StepFloatA = aWork->StepFloatA;
          if (ABS >= StepFloatA)
          {
            if (AtoB_LR >= 0.0)
              PosToDir = Dir + StepFloatA;
            else
              PosToDir = Dir - StepFloatA;
          }
          StepFloatC = aWork->StepFloatC;
          sBtlGetMoveXZ(v42, v43, PosToDir, StepFloatC, (f32 *)&v119 + 1, &v119);
          v91 = v119;
          aWork->Dir = PosToDir;
          aWork->X = *((f32 *)&v91 + 1);
          LODWORD(aWork->Z) = v91;
          LenXZ = sBtlGetLenXZ(v42, v43, *((f32 *)&v91 + 1), *(f32 *)&v91);
          v93 = sBtlGetLenXZ(v42, v43, X, Z);
          DirY = aWork->DirY;
          if (v93 >= 4.0)
          {
            v103 = wk->UnitMng;
            v104 = aWork->Unit_ListID;
            v105 = sBtlSearchUnit_ID(v103, v104);
            if (v105)
            {
              v106 = v105->pos.x;
              v107 = v105->pos.z;
              v108 = sBtlGetGroundPos(v106, v107) / -100.0;
            }
            else
            {
              v108 = 0.0;
            }
            v109 = sBtlGetPosToDir(v108, v41, LenXZ, v116);
            v111 = sBtlGetAtoB_LR(aWork->DirY, v109);
            v112 = sBtlGetABS(v111);
            StepFloatB = aWork->StepFloatB;
            if (v112 >= StepFloatB)
            {
              if (v111 >= 0.0)
                v109 = DirY + StepFloatB;
              else
                v109 = DirY - StepFloatB;
            }
            v114 = aWork->StepFloatC;
            sBtlGetMoveXZ(v108, v41, v109, v114 * 0.5, (f32 *)&v119 + 1, &v118);
            v110 = *(f32 *)&v118;
          }
          else
          {
            v97 = wk->UnitMng;
            v98 = aWork->Unit_ListID;
            v99 = sBtlSearchUnit_ID(v97, v98);
            if (v99)
            {
              v100 = v99->pos.x;
              v101 = v99->pos.z;
              v102 = sBtlGetGroundPos(v100, v101) / -100.0;
            }
            else
            {
              v102 = 0.0;
            }
            v109 = DirY + (f32)((f32)(sBtlGetPosToDir(v102, v41, LenXZ, v116) - DirY) * 0.3);
            sBtlGetMoveXZ(0.0, v41, v109, aWork->StepFloatC * 0.5, (f32 *)&v119 + 1, (f32 *)&v118 + 1);
            v110 = *((f32 *)&v118 + 1);
          }
          aWork->DirY = v109;
          aWork->Y = v110;
        }
      }
      else
      {
LABEL_78:
        switch (v44)
        {
          case 191:
            goto LABEL_81;
          case 163:
            v63 = aWork->Dir;
            if (v10)
            {
              v64 = aWork->StepFloatC;
              sBtlGetMoveXZ(v42, v43, v63, v64, (f32 *)&ToZ + 1, &ToZ);
              aWork->X = *((f32 *)&ToZ + 1);
              LODWORD(aWork->Z) = ToZ;
            }
            else
            {
              v87 = sBtlGetPosToDir(v42, v43, X, Z);
              v88 = sBtlGetAtoB_LR(aWork->Dir, v87);
              sBtlGetABS(v88);
              sBtlGetMoveXZ(v42, v43, v63, aWork->StepFloatC, (f32 *)&v120 + 1, &v120);
              v89 = *((f32 *)&v120 + 1);
              aWork->Dir = v63;
              aWork->X = v89;
              LODWORD(aWork->Z) = v120;
            }
            break;
          case 55:
            goto LABEL_81;
          default:
            v53 = 0;
            if (!v10)
              goto LABEL_95;
LABEL_87:
            aWork->X = X;
            aWork->Y = Y;
            aWork->Z = Z;
            sBtlGetLenXZ(v42, v43, X, Z);
            break;
        }
      }
      return;
    case 1:
    case 2:
      goto LABEL_16;
    case 3:
      v40 = aWork->StepTime + VRF_DeltaTime;
      aWork->StepTime = v40;
      if (v40 > (f32)(FPS60 * 30.0))
      {
LABEL_16:
        goto LABEL_19;
      }
      v10 = 1;
      v42 = aWork->X;
      v41 = aWork->Y;
      v43 = aWork->Z;
      v44 = aWork->HDEff_SkillID;
      if (v44 <= 39)
        goto LABEL_64;
      goto LABEL_78;
    case 0xA:
      v46 = aWork->StepTime + VRF_DeltaTime;
      aWork->StepTime = v46;
      if (v46 > (f32)(FPS60 * 15.0))
        goto LABEL_48;
      goto LABEL_63;
    case 0x14:
      v13 = aWork->StepTime + VRF_DeltaTime;
      aWork->StepTime = v13;
      if (v13 > (f32)(FPS60 * 40.0))
      {
LABEL_48:
        Delete(aWork);
        return;
      }
LABEL_63:
      v10 = 0;
      v42 = aWork->X;
      v41 = aWork->Y;
      v43 = aWork->Z;
      v44 = aWork->HDEff_SkillID;
      if (v44 <= 39)
        goto LABEL_64;
      goto LABEL_78;
    default:
      goto LABEL_77;
  }
}

// 0x1e4c470
void Draw(AW_WORK_t *aWork) {
}
