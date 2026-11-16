#include "types.h"
#include "aw.h"
#include "aw_mag.h"
#include "aw_magt.h"
#include "dds3vrf.h"
#include "sbtl.h"
#include "sbtlcalc.h"
#include "sbtldraw.h"
#include "sbtlplayer.h"
#include "sbtlplayer_spirit.h"
#include "sbtlscene.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e42c20
void Init(void) {
  ;
}

// 0x1e42c30
s32 Add(s32 _Variation, f32 _SX, f32 _SY, f32 _SZ, s32 MagKaifuku) {
  s32 PlayerID;
  SBTLUNIT_WORK *PlayerUnit;
  f32 x;
  f32 z;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 PosToDir;
  f32 v19;
  f32 y;
  f32 v21;
  f32 v22;
  AW_Func v23;
  s32 v24;
  AW_WORK_t *AW;
  float32x2_t *v26;
  s32 v27;
  u32 v28;
  u32 v29;
  f32 v30;
  f32 v31;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 LenXZ;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 v41;
  f32 v43;
  u32 v44;
  s32 v45;
  char *v46;
  sdfVector3_t v48;

  v48.z = 0.0;
  *(u64 *)&v48.x = 0;
  PlayerID = sBtlGetPlayerID();
  PlayerUnit = sBtlGetPlayerUnit(PlayerID);
  x = PlayerUnit->pos.x;
  z = PlayerUnit->pos.z;
  v15 = SX / -100.0;
  v16 = SY / -100.0;
  v17 = SZ / -100.0;
  PosToDir = sBtlGetPosToDir(SX, SZ, x, z);
  v19 = PlayerUnit->pos.x;
  y = PlayerUnit->pos.y;
  v21 = PosToDir;
  v22 = PlayerUnit->pos.z;
  v23 = Allocate(AW_Func);
  _ctor(v23, 0, Method_Project_AW_Mag_Calc__, 0);
  v24 = Add(406, v15, v16, v17, 0, v23, 0, 1);
  AW = GetAW(v24);
  AW->StepFloatA = 0.0;
  AW->StepFloatB = 0.0;
  v26 = AW;
  AW->StepFloatC = 0.1;
  AW->StepIntA = MagKaifuku;
  v27 = sub_1905740(4, 0);
  v26[33].n64_u32[1] = v27 + 6;
  if (MagKaifuku <= 0)
    v26[33].n64_u32[1] = v27 + sub_1905740(4, 0) + 8;
  v26[13].n64_f32[0] = v21;
  v28 = sub_1905740(80, 0);
  v26[13].n64_u32[1] = 1110704128;
  v26[13].n64_f32[0] = v26[13].n64_f32[0] + (f32)((f32)v28 + -40.0);
  v29 = sub_1905740(60, 0);
  v30 = v26[13].n64_f32[1];
  v26[4].n64_u32[1] = Variation;
  v26[13].n64_f32[1] = v30 + (f32)((f32)v29 + -30.0);
  if ((u32)(Variation - 4) < 2)
  {
    v26[30].n64_u32[0] = 30;
    v26[25].n64_f32[1] = v19 / -100.0;
    v26[26].n64_f32[0] = 1.58 - (f32)(y / 100.0);
    v26[26].n64_f32[1] = v22 / -100.0;
    v26[16].n64_f32[0] = (f32)((f32)(u32)sub_1905740(10, 0) * 0.1) + 2.5;
    v26[13].n64_f32[0] = v21 + 180.0;
    v31 = (f32)(u32)sub_1905740(120, 0) + -60.0;
    v34 = v26[13].n64_f32[0] + v31;
    v26[13].n64_f32[0] = v34;
    v26[13].n64_f32[0] = sBtlGet360(v34);
    v35 = v26[10].n64_f32[0];
    v36 = v26[11].n64_f32[0];
    v26[13].n64_u32[1] = 0;
    LenXZ = sBtlGetLenXZ(v35, v36, v26[25].n64_f32[1], v26[26].n64_f32[1]);
    v26[13].n64_f32[1] = v26[13].n64_f32[1]
                       - (f32)(sBtlGetPosToDir(0.0, 0.0, LenXZ, v26[26].n64_f32[0] - v26[10].n64_f32[1]) + -90.0);
    v38 = v26[13].n64_f32[1] + (f32)((f32)(u32)sub_1905740(100, 0) + -50.0);
    v26[13].n64_f32[1] = v38;
    v39 = sBtlGet360(v38);
    v26[13].n64_f32[1] = v39;
    v40 = v26[13].n64_f32[0];
    *(u64 *)&v48.x = 0;
    v48.z = 0.0;
    GetDirToVec(v40, v39, &v48);
    v41 = v26[16].n64_f32[0];
    v26[27].n64_u64[0] = vmul_n_f32(*(float32x2_t *)&v48.x, v41).n64_u64[0];
    v26[28].n64_f32[0] = v41 * v48.z;
    v26[25].n64_f32[0] = FPS60 * 35.0;
  }
  else if (Variation == 10)
  {
    v43 = v26[13].n64_f32[0] + 180.0;
    v26[13].n64_f32[0] = v43;
    if (!v44)
    v26[13].n64_f32[0] = sBtlGet360(v43);
  }
  else if (Variation == 3)
  {
    v26[30].n64_u32[0] = 20;
    v26[32].n64_u32[1] = 1028443341;
  }
  v45 = Add(Variation, v26[10].n64_f32[0], v26[10].n64_f32[1], v26[11].n64_f32[0], 0);
  v46 = "AW_Mag";
  v26[28].n64_u32[1] = v45;
  v26[52].n64_u64[0] = v46;
  return v24;
}

// 0x1e43100
void Delete(AW_WORK_t *aWork) {
  s32 Child_AW_Idx;
  s32 Idx;

  Child_AW_Idx = aWork->Child_AW_Idx;
  if (Child_AW_Idx != -1)
  {
    DelAW(Child_AW_Idx, 1);
    aWork->Child_AW_Idx = -1;
  }
  Idx = aWork->Idx;
  DelAW(Idx, 0);
}

// 0x1e431a0
bool ChkUse(void) {
  return GetAW_ID(406) != 0;
}

// 0x1e43210
void AllGetAndDelete(void) {
  s32 i;
  AW_WORK_t *AW;
  s32 ID;
  s32 StepIntA;

  for (i = 0; i != 720; ++i)
  {
    AW = GetAW(i);
    if (!AW->Use)
      continue;
    ID = AW->ID;
    if (ID == 407 || ID == 406)
    {
      StepIntA = AW->StepIntA;
      if (StepIntA >= 1)
      {
        sBtlAddMag(StepIntA);
      }
    }
  }
  DelAW_ID(224, 1);
  DelAW_ID(406, 1);
}

// 0x1e43330
void Calc(AW_WORK_t *aWork) {
  float32x2_t v5;
  f32 Z;
  s32 Step;
  s32 v8;
  _BOOL4 v9;
  SBTLUNIT_WORK *UnitFromDevilID;
  SBTLUNIT_WORK *v11;
  u32 v12;
  f32 v13;
  float32x2_t v14;
  f32 v15;
  f32 v17;
  f32 v19;
  s32 StepIntB;
  s32 Variation;
  s32 v22;
  s32 v23;
  AW_WORK_t *AW;
  f32 v25;
  f32 v27;
  s64 v28;
  SBTLUNIT_WORK *v29;
  SBTLUNIT_WORK *v30;
  u32 v31;
  f32 v32;
  float32x2_t v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v38;
  int8x8_t v39;
  f32 v45;
  f32 v46;
  s64 v47;
  s32 PlayerID;
  SBTLUNIT_WORK *PlayerUnit;
  SBTLUNIT_WORK *v50;
  f32 X;
  float32x2_t v52;
  f32 v53;
  f32 LenXZ;
  f32 StepFloatC;
  int8x8_t v58;
  f32 v60;
  f32 v61;
  s32 v62;
  SBTLUNIT_WORK *v63;
  SBTLUNIT_WORK *v64;
  f32 v65;
  float32x2_t v66;
  f32 v67;
  f32 v69;
  s32 Child_AW_Idx;
  s32 Idx;
  s32 v72;
  SBTLUNIT_WORK *v73;
  SBTLUNIT_WORK *v74;
  float32x2_t v75;
  f32 v76;
  int32x2_t v77;
  f32 y;
  f32 v79;
  f32 w;
  f32 v81;
  u32 v82;
  u32 v83;
  s32 v84;
  s32 v85;
  SBTLUNIT_WORK *v86;
  SBTLUNIT_WORK *v87;
  f32 v89;
  s64 v90;
  SBTLUNIT_WORK *v91;
  SBTLUNIT_WORK *v92;
  u32 v93;
  f32 v94;
  SBTLUNIT_WORK *v95;
  SBTLUNIT_WORK *v96;
  u32 v97;
  f32 v99;
  s32 v100;
  SBTLUNIT_WORK *v101;
  f32 v102;
  f32 v103;
  SBTLUNIT_WORK *v104;
  f32 v105;
  f32 v106;
  f32 RotToDir;
  f32 v108;
  f32 v109;
  f32 v110;
  f32 HomingFrame;
  f32 VelocityZ;
  float32x2_t v113;
  float32x2_t v114;
  f32 v115;
  s32 v116;
  s64 v119;
  int32x2_t v120;
  float32x2_t v122;
  float32x2_t v123;
  float32x2_t v124;
  f32 v125;
  f32 StepTime;
  float32x2_t v127;
  f32 v128;
  f32 HomingZ;
  f32 v130;
  s32 StepIntA;
  s32 v133;
  f32 v134;
  f32 v135;
  f32 v136;
  s32 v137;
  AW_WORK_t *v138;
  f32 v139;
  f32 Dir;
  f32 v141;
  f32 DirY;
  f32 PosToDir;
  f32 AtoB_LR;
  f32 ABS;
  f32 StepFloatA;
  f32 v147;
  f32 v148;
  f32 v149;
  f32 v150;
  f32 v151;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 Unit_ListID;
  SBTLUNIT_WORK *v155;
  f32 v156;
  f32 v157;
  f32 v158;
  f32 v159;
  f32 v160;
  f32 v161;
  f32 v162;
  f32 StepFloatB;
  f32 v164;
  f32 v165;
  f32 v166;
  u64 v167;
  float32x2_t ToX;
  u64 ToXb;
  u64 ToXa;
  s64 v171;
  s64 ToZ;
  s64 v173;
  sdfVector4_t v174;
  sdfVector4_t v175;
  sdfVector4_t HelperPos;
  sdfVector4_t v177;
  float32x2_t v178;
  s64 CZ;
  sdfVector4_t v180;
  sdfVector4_t v181;
  sdfVector4_t v182;
  sdfVector4_t v183;
  sdfVector4_t v184;
  sdfVector4_t v185;

  *(u64 *)&v183.x = 0;
  *(u64 *)&v183.z = 0;
  *(u64 *)&v182.x = 0;
  *(u64 *)&v182.z = 0;
  *(u64 *)&v181.x = 0;
  *(u64 *)&v181.z = 0;
  v171 = 0;
  *(u64 *)&v180.x = 0;
  *(u64 *)&v180.z = 0;
  v178.n64_u64[0] = 0;
  CZ = 0;
  *(u64 *)&v177.x = 0;
  *(u64 *)&v177.z = 0;
  *(u64 *)&HelperPos.x = 0;
  *(u64 *)&HelperPos.z = 0;
  *(u64 *)&v175.x = 0;
  *(u64 *)&v175.z = 0;
  *(u64 *)&v174.x = 0;
  *(u64 *)&v174.z = 0;
  ToZ = 0;
  v173 = 0;
  if (sBtlCheckSetsuma())
    goto LABEL_16;
  if (sBtlPlayerCheckRSpirit())
    goto LABEL_16;
  if ((aWork->Variation & 0xFFFFFFFE) != 4)
  {
    if (ChkPause(aWork))
      return;
  }
LABEL_16:
  v5.n64_u64[0] = *(u64 *)&aWork->X;
  Z = aWork->Z;
  Step = aWork->Step;
  if (Step <= 20)
  {
    v8 = 0;
    v9 = 0;
    switch (Step)
    {
      case 0:
        v19 = aWork->StepTime + VRF_DeltaTime;
        StepIntB = aWork->StepIntB;
        aWork->StepTime = v19;
        if (v19 <= (f32)(FPS60 * (f32)StepIntB))
        {
          v9 = 0;
        }
        else
        {
          Variation = aWork->Variation;
          v8 = 1;
          *(u64 *)&aWork->Step = 1;
          if (Variation != 10)
            goto LABEL_146;
          v9 = 0;
          aWork->Step = 100;
        }
LABEL_139:
        v8 = 1;
        goto LABEL_160;
      case 1:
        PlayerID = sBtlGetPlayerID();
        PlayerUnit = sBtlGetPlayerUnit(PlayerID);
        if (!PlayerUnit)
          goto LABEL_84;
        v50 = PlayerUnit;
        *(u64 *)&v183.x = 0;
        *(u64 *)&v183.z = 0;
        GetUnitHelperPos(v50, &v183);
        X = aWork->X;
        v52.n64_u64[0] = vdiv_f32(*(float32x2_t *)&v183.x, vdup_n_s32(0xC2C80000)).n64_u64[0];
        v53 = aWork->Z;
        Z = v183.z / -100.0;
        ToX.n64_u64[0] = v52.n64_u64[0];
        v52.n64_u32[0] = ToX.n64_u32[0];
        LenXZ = sBtlGetLenXZ(X, v53, v52.n64_f32[0], Z);
        StepFloatC = aWork->StepFloatC;
        if (LenXZ <= (f32)(StepFloatC + 0.2))
          goto LABEL_136;
        v58.n64_u64[0] = vadd_f32(*(float32x2_t *)&aWork->StepFloatA, vmul_n_f32((float32x2_t)0x3E4CCCCD3F000000LL, VRF)).n64_u64[0];
        __asm { FMOV            V3.2S, #10.0 }
        *(int8x8_t *)&aWork->StepFloatA = vbsl_s8(vcgt_f32(v58, _D3), _D3, v58);
        v60 = StepFloatC + (f32)(VRF * 0.001);
        if (v60 > 0.2)
          v60 = 0.2;
        aWork->StepFloatC = v60;
        v61 = aWork->StepTime + VRF_DeltaTime;
        aWork->StepTime = v61;
        if (v61 <= (f32)(FPS60 * 100.0))
          goto LABEL_144;
        v8 = 0;
        v9 = 0;
        v47 = 2;
        goto LABEL_73;
      case 2:
        v62 = sBtlGetPlayerID();
        v63 = sBtlGetPlayerUnit(v62);
        if (!v63)
          goto LABEL_84;
        v64 = v63;
        *(u64 *)&v182.x = 0;
        *(u64 *)&v182.z = 0;
        GetUnitHelperPos(v64, &v182);
        v65 = aWork->X;
        v66.n64_u64[0] = vdiv_f32(*(float32x2_t *)&v182.x, vdup_n_s32(0xC2C80000)).n64_u64[0];
        v67 = aWork->Z;
        Z = v182.z / -100.0;
        ToX.n64_u64[0] = v66.n64_u64[0];
        v66.n64_u32[0] = ToX.n64_u32[0];
        if (sBtlGetLenXZ(v65, v67, v66.n64_f32[0], Z) <= (f32)(aWork->StepFloatC + 0.2))
        {
LABEL_136:
          v28 = 10;
          goto LABEL_141;
        }
        v5.n64_u64[0] = ToX.n64_u64[0];
        *(float32x2_t *)&aWork->X = vadd_f32(*(float32x2_t *)&aWork->X, vmul_f32(vsub_f32(ToX, *(float32x2_t *)&aWork->X), vdup_n_s32(0x3E4CCCCDu)));
        aWork->Z = aWork->Z + (f32)((f32)(Z - aWork->Z) * 0.2);
        v69 = aWork->StepTime + VRF_DeltaTime;
        aWork->StepTime = v69;
        if (v69 <= (f32)(FPS60 * 30.0))
          goto LABEL_145;
        v8 = 0;
        *(u64 *)&aWork->Step = 10;
        v9 = 0;
        break;
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      case 9:
      case 13:
      case 14:
      case 15:
      case 16:
      case 17:
      case 18:
      case 19:
        goto LABEL_160;
      case 10:
        v72 = sBtlGetPlayerID();
        v73 = sBtlGetPlayerUnit(v72);
        if (!v73)
          goto LABEL_135;
        v74 = v73;
        *(u64 *)&v181.x = 0;
        *(u64 *)&v181.z = 0;
        GetUnitHelperPos(v74, &v181);
        v75.n64_u64[0] = *(u64 *)&v181.x;
        v76 = v181.z;
        v77.n64_u64[0] = vdup_n_s32(0xC2C80000).n64_u64[0];
        if (aWork->StepIntA >= 1)
        {
          v79 = v74->pos.x;
          y = v74->pos.y;
          v81 = v74->pos.z;
          w = v74->pos.w;
          if (aWork->Variation == 2)
          {
            if (!v82)
            v83 = 137887748;
            v84 = 120;
          }
          else
          {
            if (!v82)
            v83 = 65568;
            v84 = 48;
          }
          v185.x = v79;
          v185.y = y;
          v185.z = v81;
          v185.w = w;
          sBtlPlay3DSE_BaseVol(v83, v84, v185);
          StepIntA = aWork->StepIntA;
          sBtlAddMag(StepIntA);
          wk->grnCnt = 10;
          v133 = aWork->StepIntA;
          SetAddMag(v133);
        }
        v8 = 0;
        v5.n64_u64[0] = vdiv_f32(v75, v77).n64_u64[0];
        *(u64 *)&aWork->Step = 11;
        v9 = 1;
        Z = v76 / -100.0;
        goto LABEL_160;
      case 11:
        v85 = sBtlGetPlayerID();
        v86 = sBtlGetPlayerUnit(v85);
        if (!v86)
          goto LABEL_135;
        v87 = v86;
        *(u64 *)&v180.x = 0;
        *(u64 *)&v180.z = 0;
        GetUnitHelperPos(v87, &v180);
        v5.n64_u64[0] = vdiv_f32(*(float32x2_t *)&v180.x, vdup_n_s32(0xC2C80000)).n64_u64[0];
        Z = v180.z / -100.0;
        v89 = aWork->StepTime + VRF_DeltaTime;
        aWork->StepTime = v89;
        if (v89 <= (f32)(FPS60 * 4.0))
        {
LABEL_137:
          v8 = 0;
          v9 = 1;
        }
        else
        {
          v8 = 0;
          v90 = 12;
LABEL_124:
          *(u64 *)&aWork->Step = v90;
          v9 = 1;
        }
        goto LABEL_160;
      case 12:
        goto LABEL_135;
      case 20:
        v9 = 0;
        aWork->StepTime = aWork->StepTime + VRF_DeltaTime;
        goto LABEL_139;
      default:
        goto LABEL_60;
    }
    goto LABEL_160;
  }
  if ((u32)Step > 0x64)
  {
    v8 = 0;
    v9 = 0;
    switch (Step)
    {
      case 'f':
        UnitFromDevilID = sBtlGetUnitFromDevilID(257);
        if (!UnitFromDevilID)
          goto LABEL_84;
        v11 = UnitFromDevilID;
        *(u64 *)&HelperPos.x = 0;
        *(u64 *)&HelperPos.z = 0;
        if (!v12)
        GetUnitHelperPos(v11, &HelperPos);
        v13 = aWork->X;
        v14.n64_u64[0] = vdiv_f32(*(float32x2_t *)&HelperPos.x, vdup_n_s32(0xC2C80000)).n64_u64[0];
        v15 = aWork->Z;
        Z = HelperPos.z / -100.0;
        ToX.n64_u64[0] = v14.n64_u64[0];
        v14.n64_u32[0] = ToX.n64_u32[0];
        if (sBtlGetLenXZ(v13, v15, v14.n64_f32[0], Z) <= (f32)(aWork->StepFloatC + 0.2))
          goto LABEL_140;
        v5.n64_u64[0] = ToX.n64_u64[0];
        *(float32x2_t *)&aWork->X = vadd_f32(*(float32x2_t *)&aWork->X, vmul_f32(vsub_f32(ToX, *(float32x2_t *)&aWork->X), vdup_n_s32(0x3E4CCCCDu)));
        aWork->Z = aWork->Z + (f32)((f32)(Z - aWork->Z) * 0.2);
        v17 = aWork->StepTime + VRF_DeltaTime;
        aWork->StepTime = v17;
        if (v17 <= (f32)(FPS60 * 30.0))
          goto LABEL_145;
        v8 = 0;
        *(u64 *)&aWork->Step = 110;
        v9 = 0;
        break;
      case 'g':
      case 'h':
      case 'i':
      case 'j':
      case 'k':
      case 'l':
      case 'm':
        goto LABEL_160;
      case 'n':
        v91 = sBtlGetUnitFromDevilID(257);
        if (!v91)
          goto LABEL_135;
        v92 = v91;
        *(u64 *)&v175.x = 0;
        *(u64 *)&v175.z = 0;
        if (!v93)
        GetUnitHelperPos(v92, &v175);
        v8 = 0;
        v9 = 1;
        v5.n64_u64[0] = vdiv_f32(*(float32x2_t *)&v175.x, vdup_n_s32(0xC2C80000)).n64_u64[0];
        v94 = v175.z;
        *(u64 *)&aWork->Step = 111;
        Z = v94 / -100.0;
        goto LABEL_160;
      case 'o':
        v95 = sBtlGetUnitFromDevilID(257);
        if (!v95)
          goto LABEL_135;
        v96 = v95;
        *(u64 *)&v174.x = 0;
        *(u64 *)&v174.z = 0;
        if (!v97)
        GetUnitHelperPos(v96, &v174);
        v5.n64_u64[0] = vdiv_f32(*(float32x2_t *)&v174.x, vdup_n_s32(0xC2C80000)).n64_u64[0];
        Z = v174.z / -100.0;
        v99 = aWork->StepTime + VRF_DeltaTime;
        aWork->StepTime = v99;
        if (v99 <= (f32)(FPS60 * 4.0))
          goto LABEL_137;
        v8 = 0;
        v90 = 112;
        goto LABEL_124;
      case 'p':
        goto LABEL_84;
      default:
        goto LABEL_60;
    }
    goto LABEL_160;
  }
  v8 = 0;
  if (Step > 31)
  {
    if (Step == 32)
    {
LABEL_84:
      Child_AW_Idx = aWork->Child_AW_Idx;
      if (Child_AW_Idx != -1)
      {
        DelAW(Child_AW_Idx, 1);
        aWork->Child_AW_Idx = -1;
      }
      Idx = aWork->Idx;
      DelAW(Idx, 0);
      return;
    }
    v9 = 0;
    if (Step == 100)
    {
      v29 = sBtlGetUnitFromDevilID(257);
      if (v29)
      {
        v30 = v29;
        *(u64 *)&v177.x = 0;
        *(u64 *)&v177.z = 0;
        if (!v31)
        GetUnitHelperPos(v30, &v177);
        v32 = aWork->X;
        v33.n64_u64[0] = vdiv_f32(*(float32x2_t *)&v177.x, vdup_n_s32(0xC2C80000)).n64_u64[0];
        v34 = aWork->Z;
        Z = v177.z / -100.0;
        ToX.n64_u64[0] = v33.n64_u64[0];
        v33.n64_u32[0] = ToX.n64_u32[0];
        v35 = sBtlGetLenXZ(v32, v34, v33.n64_f32[0], Z);
        v36 = aWork->StepFloatC;
        if (v35 > (f32)(v36 + 0.2))
        {
          v38 = VRF;
          v39.n64_u64[0] = vadd_f32(*(float32x2_t *)&aWork->StepFloatA, vmul_n_f32((float32x2_t)0x3E4CCCCD3F000000LL, v38)).n64_u64[0];
          __asm { FMOV            V3.2S, #10.0 }
          *(int8x8_t *)&aWork->StepFloatA = vbsl_s8(vcgt_f32(v39, _D3), _D3, v39);
          v45 = v36 + (f32)(v38 * 0.001);
          if (v45 > 0.2)
            v45 = 0.2;
          aWork->StepFloatC = v45;
          v46 = aWork->StepTime + VRF_DeltaTime;
          aWork->StepTime = v46;
          if (v46 <= (f32)(FPS60 * 100.0))
          {
LABEL_144:
            v5.n64_u64[0] = ToX.n64_u64[0];
LABEL_145:
            v8 = 0;
LABEL_146:
            v9 = 0;
          }
          else
          {
            v8 = 0;
            v9 = 0;
            v47 = 102;
LABEL_73:
            v5.n64_u64[0] = ToX.n64_u64[0];
            *(u64 *)&aWork->Step = v47;
          }
          goto LABEL_160;
        }
LABEL_140:
        v28 = 110;
LABEL_141:
        v8 = 0;
        goto LABEL_142;
      }
LABEL_135:
      Delete(aWork);
      return;
    }
  }
  else
  {
    if (Step == 30)
    {
      v100 = sBtlGetPlayerID();
      v101 = sBtlGetPlayerUnit(v100);
      if (v101)
      {
        v178.n64_u64[0] = 0;
        CZ = 0;
        v102 = v101->rot.x;
        v103 = v101->rot.y;
        v104 = v101;
        v106 = v101->rot.z;
        v105 = v101->rot.w;
        v184.x = v102;
        v184.y = v103;
        v184.z = v106;
        v184.w = v105;
        RotToDir = sBtlGetRotToDir(v184);
        v108 = v104->pos.x;
        v109 = v104->pos.z;
        v178.n64_f32[1] = v104->pos.y + -158.0;
        sBtlGetMoveXZ(v108, v109, RotToDir + 0.0, 100.0, &v178, &CZ);
        sBtlDrawLineX_PS2(v178.n64_f32[0], v178.n64_f32[1], *(f32 *)&CZ, 100.0, 0x80808080);
        v5.n64_u64[0] = vdiv_f32(v178, vdup_n_s32(0xC2C80000)).n64_u64[0];
        v110 = *(f32 *)&CZ;
        HomingFrame = aWork->HomingFrame;
        VelocityZ = aWork->VelocityZ;
        v113.n64_u64[0] = *(u64 *)&aWork->VelocityX;
        v114.n64_u64[0] = *(u64 *)&aWork->X;
        v115 = aWork->Z;
        v116 = (u8)byte_5755D2C;
        *(float32x2_t *)&aWork->HomingX = v5;
        Z = v110 / -100.0;
        aWork->HomingZ = v110 / -100.0;
        if (!v116)
        {
          v167 = v113.n64_u64[0];
          ToXb = v5.n64_u64[0];
          v166 = HomingFrame;
          HomingFrame = v166;
          v113.n64_u64[0] = v167;
          v5.n64_u64[0] = ToXb;
        }
        v9 = (f32)(HomingFrame - VRF_DeltaTime) < 0.0;
        if ((f32)(HomingFrame - VRF_DeltaTime) < 0.0)
        {
          v119 = *(u64 *)&aWork->HomingX;
          aWork->Step = 31;
          HomingZ = aWork->HomingZ;
          *(u64 *)&aWork->X = v119;
          StepTime = 0.0;
        }
        else
        {
          v120.n64_u64[0] = vsub_f32(v5, v114).n64_u64[0];
          v122.n64_u64[0] = vsub_f32(v120, vmul_f32((float32x2_t)__PAIR64__(LODWORD(HomingFrame), v113.n64_u32[0]), (float32x2_t)__PAIR64__(v113.n64_u32[1], LODWORD(HomingFrame)))).n64_u64[0];
          v120.n64_f32[0] = HomingFrame * HomingFrame;
          v123.n64_u64[0] = vdiv_f32(vadd_f32(v122, v122), vdup_lane_s32(v120, 0)).n64_u64[0];
          v124.n64_u64[0] = *(u64 *)&zeroVector.x;
          v125 = zeroVector.z;
          aWork->HomingFrame = HomingFrame - VRF_DeltaTime;
          StepTime = aWork->StepTime;
          v127.n64_u64[0] = vadd_f32(v113, vmul_n_f32(vadd_f32(v123, v124), VRF_DeltaTime)).n64_u64[0];
          v128 = VelocityZ
               + (f32)(VRF_DeltaTime * (f32)((f32)((f32)((f32)((f32)(Z - v115) - (f32)(HomingFrame * VelocityZ)) + (f32)((f32)(Z - v115) - (f32)(HomingFrame * VelocityZ))) / (f32)(HomingFrame * HomingFrame)) + v125));
          *(float32x2_t *)&aWork->VelocityX = v127;
          aWork->VelocityZ = v128;
          HomingZ = v115 + (f32)(VRF_DeltaTime * v128);
          *(float32x2_t *)&aWork->X = vadd_f32(v114, vmul_n_f32(v127, VRF_DeltaTime));
        }
        v130 = VRF_DeltaTime + StepTime;
        aWork->Z = HomingZ;
        v8 = 0;
        aWork->StepTime = v130;
        if (v130 > (f32)(FPS60 * 200.0))
        {
          *(float32x2_t *)&aWork->X = v5;
          aWork->Z = Z;
          *(u64 *)&aWork->Step = 31;
        }
        goto LABEL_160;
      }
      goto LABEL_135;
    }
    if (Step == 31)
    {
      ToX.n64_u64[0] = *(u64 *)&aWork->X;
      v22 = sBtlGetPlayerID();
      if (sBtlGetPlayerUnit(v22))
      {
        v23 = aWork->Child_AW_Idx;
        if (v23 != -1)
        {
          AW = GetAW(v23);
          v25 = AW->Scale + -0.03;
          AW->Scale = v25;
          if (v25 < 0.1)
            AW->Scale = 0.1;
        }
        v8 = 0;
        v27 = aWork->StepTime + VRF_DeltaTime;
        aWork->StepTime = v27;
        if (v27 <= (f32)(FPS60 * 30.0))
          goto LABEL_143;
        v28 = 32;
LABEL_142:
        *(u64 *)&aWork->Step = v28;
LABEL_143:
        v5.n64_u64[0] = ToX.n64_u64[0];
        v9 = 1;
        goto LABEL_160;
      }
      goto LABEL_135;
    }
LABEL_60:
    v9 = 0;
  }
LABEL_160:
  ToXa = v5.n64_u64[0];
  if (sBtlPlayerCheckRSpirit())
    goto LABEL_169;
  if ((aWork->Variation & 0xFFFFFFFE) == 4)
    goto LABEL_169;
  v134 = aWork->X;
  v135 = aWork->Z;
  if (v9)
  {
    v136 = *(f32 *)&ToXa;
    *(u64 *)&aWork->X = ToXa;
    aWork->Z = Z;
    v136 = *(f32 *)&ToXa;
    sBtlGetLenXZ(v134, v135, v136, Z);
LABEL_169:
    v137 = aWork->Child_AW_Idx;
    if (v137 == -1)
      return;
    goto LABEL_170;
  }
  v139 = aWork->Y;
  Dir = aWork->Dir;
  if (v8)
  {
    v141 = aWork->StepFloatC;
    sBtlGetMoveXZ(v134, v135, Dir, v141, (f32 *)&v173 + 1, (f32 *)&ToZ + 1);
    DirY = aWork->DirY;
    aWork->X = *((f32 *)&v173 + 1);
    aWork->Z = *((f32 *)&ToZ + 1);
    sBtlGetMoveXZ(0.0, v139, DirY, aWork->StepFloatC * 0.5, (f32 *)&v173 + 1, &v173);
    LODWORD(aWork->Y) = v173;
    v137 = aWork->Child_AW_Idx;
    if (v137 == -1)
      return;
LABEL_170:
    v138 = GetAW(v137);
    *(u64 *)&v138->X = *(u64 *)&aWork->X;
    v138->Z = aWork->Z;
    return;
  }
  PosToDir = sBtlGetPosToDir(v134, v135, *(f32 *)&ToXa, Z);
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
  v147 = aWork->StepFloatC;
  sBtlGetMoveXZ(v134, v135, PosToDir, v147, &ToZ, (f32 *)&v171 + 1);
  v149 = *((f32 *)&v171 + 1);
  v148 = *(f32 *)&ToZ;
  aWork->Dir = PosToDir;
  aWork->X = v148;
  aWork->Z = v149;
  v150 = sBtlGetLenXZ(v134, v135, v148, v149);
  sBtlGetLenXZ(v134, v135, *(f32 *)&ToXa, Z);
  v151 = aWork->DirY;
  UnitMng = wk->UnitMng;
  Unit_ListID = aWork->Unit_ListID;
  v155 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
  if (v155)
  {
    v156 = v155->pos.x;
    v157 = v155->pos.z;
    v158 = sBtlGetGroundPos(v156, v157) / -100.0;
  }
  else
  {
    v158 = 0.0;
  }
  v159 = *((f32 *)&ToXa + 1);
  v159 = *((f32 *)&ToXa + 1);
  v160 = sBtlGetPosToDir(v158, v139, v150, v159);
  v161 = sBtlGetAtoB_LR(aWork->DirY, v160);
  v162 = sBtlGetABS(v161);
  StepFloatB = aWork->StepFloatB;
  if (v162 >= StepFloatB)
  {
    if (v161 >= 0.0)
      v160 = v151 + StepFloatB;
    else
      v160 = v151 - StepFloatB;
  }
  v164 = aWork->StepFloatC;
  sBtlGetMoveXZ(v158, v139, v160, v164 * 0.5, &ToZ, &v171);
  v165 = *(f32 *)&v171;
  aWork->DirY = v160;
  aWork->Y = v165;
  v137 = aWork->Child_AW_Idx;
  if (v137 != -1)
    goto LABEL_170;
}
