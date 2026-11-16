#include "types.h"
#include "aw.h"
#include "aw_xatkbullet.h"
#include "aw_xatkcharge.h"
#include "aw_xatkchargel.h"
#include "aw_xatkhatudo.h"
#include "aw_xatkmuzzle.h"
#include "aw_xatkpad.h"
#include "aw_xatkparam.h"
#include "aw_xatksightl.h"
#include "bsflow.h"
#include "dds3vrf.h"
#include "sbtl.h"
#include "sbtlplayer.h"
#include "sbtlplayer_spirit.h"
#include "sbtlscene.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sdf_vu0.h"

#define V_TEST_S 131088
#define V_TEST_S45 131089
#define V_TEST_S90 131090
#define V_TEST_S180 131091
#define V_TEST_S360 131097
#define V_TEST_LS 131092
#define V_TEST_LL 131093
#define V_TEST_L360 131094
#define V_TEST_L720 131095
#define V_TEST_LV 131096
#define V_TEST_HOMI 131098
#define V_TEST_BOMB 131099
#define V_TEST_CRAC 131100
#define V_TEST_BIOARM_R 131101
#define V_TEST_BIOARM_L 131102
#define V_TEST_POIS 131103
#define V_E016_5 131425
#define V_E016_BARA 131426
#define V_E016_10 131427
#define V_E018_90 131457
#define V_E018_360 131458
#define V_E018_FB 131459
#define V_E018_BAR 131460
#define V_E018_90_V103 131461
#define V_E01D_L 131537
#define V_E01D_K 131538
#define V_E01D_K2 131539
#define V_E028_POI_S 131713
#define V_E028_POI_M 131714
#define V_E028_POI_L 131715
#define V_E028_POI_LL 131716
#define V_E02D_90 131793
#define V_E02D_BOMB_L 131794
#define V_E02D_BAR 131795
#define V_E02D_BIOARM_L 131796
#define V_E02E_K 131809
#define V_E02E_K2 131810
#define V_E02E_K3 131811
#define V_E02E_K4 131812
#define V_E024_K 131649
#define V_E024_K2 131650
#define V_E026_BIOARM_R 131681
#define V_E218_K 139649
#define V_E218_K2 139650
#define V_E218_K3 139651
#define V_E218_BOMB_L 139652
#define V_E03B_BS14_CLEAR 132017
#define V_E03B_BS14_CHOU_R 132018
#define V_E03B_BS14_CHOU_R_2 132019
#define V_E03C_K2 132035
#define V_E03C_BARA 132036
#define V_E03C_BIOARM_L 132037
#define V_E03C_90 132038
#define V_E03C_10 132039
#define V_E03C_360 132040
#define V_E03C_10F 132041
#define V_E03C_BARA2 132042
#define V_E03C_FLOWCLR 132043
#define V_E01A_BS0_KIJYUUS 131489
#define V_E01C_BS0_CLEARRI 131521
#define V_E01B_E_ZON_SHT 131505
#define V_E217_360 139633
#define V_E217_L 139634

typedef struct AW_WORK_t AW_WORK_t;
typedef struct AW_XAtkPad_Arg_t AW_XAtkPad_Arg_t;
typedef struct AW_XAtkPad_Table_t AW_XAtkPad_Table_t;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

struct AW_XAtkPad_Table_t {
    s32 ID;
    s32 V;
    s32 Pad_1StWait;
    s32 Pad_ShotDirRate;
    s32 Pad_ShotWay;
    s32 Pad_ShotWayRange;
    s32 Pad_ShotRapid;
    s32 Pad_ShotRapidInt;
    s32 Pad_SeShot;
    u32 Pad_StepFlag;
    u32 Pad_StepFlag2;
    s32 Shot_Variation;
    f32 Shot_DirY;
    f32 Shot_Scale;
    f32 Shot_MoveDirRate;
    f32 Shot_MoveSpd;
    f32 Shot_MoveSpdRate;
    f32 Shot_MoveSpdMax;
    f32 Shot_HomingFrame;
    u32 Shot_StepFlag;
    u32 Shot_StepFlag2;
    s32 Laser_FrameS;
    s32 Laser_FrameL;
    f32 Laser_RangeS;
    f32 Laser_OfsLen;
    f32 Laser_Rev;
};

AW_XAtkPad_Arg_t *ArgumentParam;
static s32 *gTableHomingFrameShiftS;
static s32 *gTableHomingFrameShiftM;
static s32 gHomingFrameShift;
static u32 gHomingSE;
static f32 gHomingPosX;
static f32 gHomingPosY;
static f32 gHomingPosZ;
static sdfVector2_t *gTableOffsetXZ;
static f32 *gTableOffsetDir_Scatter;
static f32 *gTableOffsetDir_Scatter2;
static AW_XAtkPad_Table_t *gPadTable;

static void SetTableToWork(AW_WORK_t *aWork, AW_WORK_t *aWorkShotParam, AW_WORK_t *aWorkLaserGroup, AW_XAtkPad_Table_t *aPadTable);
static void SetUnitPos(AW_WORK_t *aWork);

// 0x1e901a0
void Init(void) {
  ;
}

// 0x1e83e60
s32 Add(void) {
  AW_Func v1;
  s32 v2;
  AW_Func v3;
  AW_WORK_t *AW;
  s32 Delay;
  SBTLUNIT_WORK *wk_local;
  u32 Flag;
  f32 *p_x;
  f32 y;
  f32 Ps2X;
  f32 RotToDir;
  f32 Ps2Z;
  f32 Dir180;
  f32 v22;
  f32 v23;
  f32 v24;
  s32 *StepIntBuff;
  AW_XAtkPad_Arg_t *v27;
  s32 V;
  s32 v29;
  AW_WORK_t *v30;
  AW_WORK_t *v32;
  s32 *v33;
  s32 v34;
  s32 *v35;
  AW_WORK_t *v36;
  AW_WORK_t *v37;
  s64 v38;
  f32 v41;
  f32 v42;
  f32 Ps2Dir;
  f32 v45;
  s64 v47;
  s32 *v48;
  AW_XAtkPad_Table_t *v50;
  AW_XAtkPad_Table_t *v52;
  s32 v53;
  s32 v54;
  s32 v55;
  int8x8_t v56;
  f32 v57;
  s32 v58;
  u32 StepFlag;
  s32 Pad_ShotDirRate;
  s32 Pad_ShotRapidInt;
  s32 Pad_ShotRapid;
  int8x8_t v64;
  f32 Shot_DirY;
  s32 Shot_Variation;
  SBATTLE_WORK *v68;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v71;
  f32 X;
  f32 v73;
  f32 Z;
  f32 v75;
  f32 PosToDir;
  char *v77;

  v1 = Allocate(AW_Func);
  _ctor(v1, 0, Method_Project_AW_XAtkPad_Calc__, 0);
  v2 = Add(600, 0.0, 0.0, 0.0, 0, v1, 0, 4);
  v3 = Allocate(AW_Func);
  _ctor(v3, 0, Method_Project_AW_XAtkPad_Calc3__, 0);
  Set_Calc3Func(v2, v3);
  AW = GetAW(v2);
  Delay = ArgumentParam->Delay;
  *(u64 *)&AW->Step = 0;
  if (!Delay)
  {
LABEL_10:
    AW->StepIntA = Delay;
    goto LABEL_11;
  }
  goto LABEL_10;
LABEL_11:
  wk_local = ArgumentParam->wk;
  if (!wk_local)
  {
    AW->wk = 0;
    *(u64 *)&AW->Unit_ListID = -1;
    goto LABEL_30;
  }
  wk_local = ArgumentParam->wk;
  AW->wk = wk_local;
  *(u64 *)&AW->Unit_ListID = *(u64 *)&wk_local->ListID;
  Flag = ArgumentParam->Flag;
  if ((Flag & 0x10000000) != 0)
  {
    sBtlGetUnitHelperPos(wk_local, 0);
    p_x = &vf00.x;
    y = wk_local->pos.y;
    Ps2X = p_x[4];
LABEL_40:
    Ps2Z = p_x[6];
    RotToDir = sBtlGetRotToDir(wk_local->rot);
    goto LABEL_41;
  }
  if ((ArgumentParam->Flag & 0x20000000) != 0)
  {
    sBtlGetUnitHelperPos(wk_local, 0);
    p_x = &vf00.x;
    Ps2X = p_x[4];
    y = p_x[5];
    goto LABEL_40;
  }
LABEL_30:
  Ps2X = ArgumentParam->Ps2X;
  y = ArgumentParam->Ps2Y;
  Ps2Z = ArgumentParam->Ps2Z;
  RotToDir = ArgumentParam->Ps2Dir;
LABEL_41:
  Dir180 = sBtlGetDir180(RotToDir);
  v22 = Ps2Z / -100.0;
  v23 = y / -100.0;
  v24 = Ps2X / -100.0;
  StepIntBuff = AW->StepIntBuff;
  AW->X = v24;
  AW->Y = v23;
  AW->Z = v22;
  AW->PopX = v24;
  AW->PopY = v23;
  AW->PopZ = v22;
  v27 = ArgumentParam;
  AW->Dir = Dir180;
  AW->DirY = 0.0;
  V = v27->V;
  LODWORD(v27) = v27->Flag;
  AW->ShotRapidCnt = 0;
  AW->ShotDir = Dir180;
  AW->StepFlag2 = 0;
  AW->Variation = V;
  AW->StepFlag = (u32)v27;
  *(u64 *)&AW->StepIntB = 0xFFFFFFFFLL;
  StepIntBuff[0] = Add(0);
  v29 = AW->StepIntBuff[0];
  v30 = GetAW(v29);
  *(u64 *)&v30->StepFlag = 0;
  v32 = v30;
  v33 = AW->StepIntBuff;
  v30->StepIntB = ArgumentParam->SklID;
  v34 = Add(0);
  v35 = AW->StepIntBuff;
  v33[1] = v34;
  v36 = GetAW(v35[1]);
  *(u64 *)&v36->Step = 0;
  v37 = v36;
  v38 = *(u64 *)&AW->X;
  v36->DirY = 0.0;
  *(u64 *)&v36->X = v38;
  v36->Z = AW->Z;
  v36->Dir = AW->Dir;
  if ((AW->StepFlag & 0x30000000) == 0)
  {
    Ps2Dir = ArgumentParam->Ps2Dir;
    v42 = sBtlGetDir180(Ps2Dir);
    goto LABEL_53;
  }
  v41 = ArgumentParam->Ps2Dir;
  v42 = Dir180 + sBtlGetDir180(v41);
LABEL_53:
  v45 = sBtlGet360(v42);
  *(u64 *)&v37->StepFlag = 0;
  *(u16 *)&v37->StepBoolA = 0;
  v47 = 0;
  v37->Scale = 1.0;
  v48 = AW->StepIntBuff;
  v37->LaserDirSS = v45;
  *(u64 *)&v48[2] = -1;
  v48[4] = -1;
  while (1)
  {
    if (v47 >= SLODWORD(gPadTable->max_length))
      break;
    v50 = gPadTable[v47];
    if (v50->V == AW->Variation)
    {
      AW->StepIntB = v47;
      Pad_ShotDirRate = v50->Pad_ShotDirRate;
      AW->ShotWay = v50->Pad_ShotWay;
      Pad_ShotRapidInt = v50->Pad_ShotRapidInt;
      AW->ShotDirRate = (f32)Pad_ShotDirRate;
      AW->ShotWayRange = (f32)v50->Pad_ShotWayRange;
      Pad_ShotRapid = v50->Pad_ShotRapid;
      AW->ShotRapidInt = Pad_ShotRapidInt;
      v64.n64_u64[0] = *(u64 *)&v50->Pad_StepFlag;
      AW->ShotRapid = (f32)Pad_ShotRapid;
      *(int8x8_t *)&AW->StepFlag = vorr_s8(v64, *(int8x8_t *)&AW->StepFlag);
      Shot_DirY = v50->Shot_DirY;
      Shot_Variation = v50->Shot_Variation;
      v32->Scale = v50->Shot_Scale;
      v32->DirY = Shot_DirY;
      v32->Variation = Shot_Variation;
      *(_OWORD *)&v32->MoveDirRate = *(_OWORD *)&v50->Shot_MoveDirRate;
      v32->HomingFrame = v50->Shot_HomingFrame;
      *(u64 *)&v32->StepFlag = *(u64 *)&v50->Shot_StepFlag;
      *(u64 *)&v37->LaserFrameS = *(u64 *)&v50->Laser_FrameS;
      v37->LaserRangeS = v50->Laser_RangeS;
      *(u64 *)&v37->LaserOfsLen = *(u64 *)&v50->Laser_OfsLen;
      StepFlag = AW->StepFlag;
      AW->StepFloatA = (f32)gPadTable[AW->StepIntB]->Pad_1StWait;
      if ((StepFlag & 0x40000) != 0)
        goto LABEL_70;
      goto LABEL_77;
    }
    ++v47;
  }
  v52 = gPadTable[0];
  v53 = v52->Pad_ShotDirRate;
  AW->ShotWay = v52->Pad_ShotWay;
  v54 = v52->Pad_ShotRapidInt;
  AW->ShotDirRate = (f32)v53;
  AW->ShotWayRange = (f32)v52->Pad_ShotWayRange;
  v55 = v52->Pad_ShotRapid;
  AW->ShotRapidInt = v54;
  v56.n64_u64[0] = *(u64 *)&v52->Pad_StepFlag;
  AW->ShotRapid = (f32)v55;
  *(int8x8_t *)&AW->StepFlag = vorr_s8(v56, *(int8x8_t *)&AW->StepFlag);
  v57 = v52->Shot_DirY;
  v58 = v52->Shot_Variation;
  v32->Scale = v52->Shot_Scale;
  v32->DirY = v57;
  v32->Variation = v58;
  *(_OWORD *)&v32->MoveDirRate = *(_OWORD *)&v52->Shot_MoveDirRate;
  v32->HomingFrame = v52->Shot_HomingFrame;
  *(u64 *)&v32->StepFlag = *(u64 *)&v52->Shot_StepFlag;
  *(u64 *)&v37->LaserFrameS = *(u64 *)&v52->Laser_FrameS;
  v37->LaserRangeS = v52->Laser_RangeS;
  *(u64 *)&v37->LaserOfsLen = *(u64 *)&v52->Laser_OfsLen;
  StepFlag = AW->StepFlag;
  AW->StepFloatA = 0.0;
  if ((StepFlag & 0x40000) != 0)
  {
LABEL_70:
    v68 = wk;
    UnitMng = v68->UnitMng;
    playerID = v68->playerID;
    v71 = sBtlSearchUnit_ID(UnitMng, playerID);
    X = AW->X;
    v73 = v71->pos.x / -100.0;
    Z = AW->Z;
    v75 = v71->pos.z / -100.0;
    PosToDir = sBtlGetPosToDir(X, Z, v73, v75);
    AW->Dir = PosToDir;
    StepFlag = AW->StepFlag;
    v37->Dir = PosToDir;
    AW->ShotDir = PosToDir;
    v37->LaserDirSS = AW->Dir;
  }
LABEL_77:
  if ((StepFlag & 0x30000000) != 0)
    AW->ShotDir = 0.0;
  v77 = "AW_XAtkPad";
  AW->DbgStr = "AW_XAtkPad";
  return v2;
}

// 0x1e901b0
static void SetTableToWork(AW_WORK_t *aWork, AW_WORK_t *aWorkShotParam, AW_WORK_t *aWorkLaserGroup, AW_XAtkPad_Table_t *aPadTable) {
  s32 Pad_ShotDirRate;
  s32 Pad_ShotRapidInt;
  s32 Pad_ShotRapid;
  int8x8_t v8;
  f32 Shot_DirY;
  s32 Shot_Variation;

  Pad_ShotDirRate = aPadTable->Pad_ShotDirRate;
  aWork->ShotWay = aPadTable->Pad_ShotWay;
  Pad_ShotRapidInt = aPadTable->Pad_ShotRapidInt;
  aWork->ShotDirRate = (f32)Pad_ShotDirRate;
  aWork->ShotWayRange = (f32)aPadTable->Pad_ShotWayRange;
  Pad_ShotRapid = aPadTable->Pad_ShotRapid;
  aWork->ShotRapidInt = Pad_ShotRapidInt;
  v8.n64_u64[0] = *(u64 *)&aPadTable->Pad_StepFlag;
  aWork->ShotRapid = (f32)Pad_ShotRapid;
  *(int8x8_t *)&aWork->StepFlag = vorr_s8(v8, *(int8x8_t *)&aWork->StepFlag);
  Shot_DirY = aPadTable->Shot_DirY;
  Shot_Variation = aPadTable->Shot_Variation;
  aWorkShotParam->Scale = aPadTable->Shot_Scale;
  aWorkShotParam->DirY = Shot_DirY;
  aWorkShotParam->Variation = Shot_Variation;
  *(_OWORD *)&aWorkShotParam->MoveDirRate = *(_OWORD *)&aPadTable->Shot_MoveDirRate;
  aWorkShotParam->HomingFrame = aPadTable->Shot_HomingFrame;
  *(u64 *)&aWorkShotParam->StepFlag = *(u64 *)&aPadTable->Shot_StepFlag;
  *(u64 *)&aWorkLaserGroup->LaserFrameS = *(u64 *)&aPadTable->Laser_FrameS;
  aWorkLaserGroup->LaserRangeS = aPadTable->Laser_RangeS;
  *(u64 *)&aWorkLaserGroup->LaserOfsLen = *(u64 *)&aPadTable->Laser_OfsLen;
}

// 0x1e90240
void Delete(AW_WORK_t *aWork) {
  s32 v4;
  AW_WORK_t *AW;
  s32 Idx;
  s32 *StepIntBuff;
  s32 v9;
  AW_WORK_t *v10;
  s32 v12;
  s32 *v13;
  s32 v14;
  s32 v15;

  v4 = aWork->StepIntBuff[0];
  AW = GetAW(v4);
  if (!AW)
  {
    v9 = aWork->StepIntBuff[1];
    goto LABEL_7;
  }
  Idx = AW->Idx;
  DelAW(Idx, 1);
  StepIntBuff = aWork->StepIntBuff;
  StepIntBuff[0] = -1;
  v9 = StepIntBuff[1];
LABEL_7:
  v10 = GetAW(v9);
  if (v10)
  {
    v12 = v10->Idx;
    DelAW(v12, 1);
    v13 = aWork->StepIntBuff;
    v13[1] = -1;
    v14 = v13[2];
    if (v14 != -1)
      goto LABEL_11;
    goto LABEL_12;
  }
  v14 = aWork->StepIntBuff[2];
  if (v14 != -1)
  {
LABEL_11:
    Delete_2(v14);
    aWork->StepIntBuff[2] = -1;
  }
LABEL_12:
  v15 = aWork->Idx;
  DelAW(v15, 1);
}

// 0x1e903d0
static void SetUnitPos(AW_WORK_t *aWork) {
  u32 StepFlag;
  SBTLUNIT_LISTWORK *v5;
  s32 v6;
  SBTLUNIT_WORK *v7;
  SBTLUNIT_WORK *v8;
  f32 *p_y;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 Unit_ListID;
  SBTLUNIT_WORK *v15;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 RotToDir;
  f32 Dir180;
  s32 v22;
  f32 X;
  f32 Y;
  f32 Z;
  AW_WORK_t *AW;
  SBTLUNIT_LISTWORK *v29;
  s32 v30;
  SBTLUNIT_WORK *v31;
  SBTLUNIT_WORK *v32;
  f32 v35;
  f32 v36;
  f32 v37;
  s32 v38;
  AW_WORK_t *v39;

  StepFlag = aWork->StepFlag;
  if ((StepFlag & 0x10000000) != 0)
  {
    UnitMng = wk->UnitMng;
    Unit_ListID = aWork->Unit_ListID;
    v15 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
    if (!v15)
      goto LABEL_31;
    v8 = v15;
    if (v15->UID != aWork->Unit_UID)
      goto LABEL_31;
    sBtlGetUnitHelperPos(v8, 0);
    p_y = &v8->pos.y;
    goto LABEL_30;
  }
  if ((StepFlag & 0x20000000) != 0)
  {
    v5 = wk->UnitMng;
    v6 = aWork->Unit_ListID;
    v7 = sBtlSearchUnit_ID(v5, v6);
    if (v7)
    {
      v8 = v7;
      if (v7->UID == aWork->Unit_UID)
      {
        sBtlGetUnitHelperPos(v8, 0);
        p_y = &vct_A.y;
LABEL_30:
        v17 = vct_A.x / -100.0;
        v18 = vct_A.z / -100.0;
        v19 = *p_y / -100.0;
        RotToDir = sBtlGetRotToDir(v8->rot);
        Dir180 = sBtlGetDir180(RotToDir);
        aWork->X = v17;
        aWork->Y = v19;
        aWork->Z = v18;
        aWork->Dir = Dir180;
        goto LABEL_31;
      }
    }
  }
LABEL_31:
  v22 = aWork->StepIntBuff[2];
  if (v22 == -1)
    goto LABEL_36;
  X = aWork->X;
  Y = aWork->Y;
  Z = aWork->Z;
  AW = GetAW(v22);
  if (!AW)
    goto LABEL_36;
  goto LABEL_35;
  if (AW)
  {
LABEL_35:
    AW->Z = Z;
    AW->X = X;
    AW->Y = Y + 0.03;
  }
LABEL_36:
  if (aWork->StepIntBuff[4] != -1 && (aWork->StepFlag & 0x30000000) != 0)
  {
    v29 = wk->UnitMng;
    v30 = aWork->Unit_ListID;
    v31 = sBtlSearchUnit_ID(v29, v30);
    if (v31)
    {
      v32 = v31;
      if (v31->UID == aWork->Unit_UID)
      {
        sBtlGetUnitHelperPos(v32, 0);
        v35 = v32->pos.y;
        v36 = vct_A.x;
        v37 = vct_A.z;
        v38 = aWork->StepIntBuff[4];
        if (v38 != -1)
        {
          v39 = GetAW(v38);
          if (v39)
          {
            v39->X = v36 / -100.0;
            v39->Y = 0.02 - (f32)(v35 / 100.0);
            v39->Z = v37 / -100.0;
          }
        }
        return;
      }
    }
  }
}

// 0x1e908f0
void Calc(AW_WORK_t *aWork) {
  s32 *StepIntBuff;
  s32 v4;
  AW_WORK_t *AW;
  AW_WORK_t *v6;
  f32 v9;
  s32 Step;
  f32 v11;
  f32 Y;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v17;
  s32 StepIntA;
  s32 *v19;
  u32 StepFlag;
  f32 v22;
  f32 StepFloatA;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 Unit_ListID;
  SBTLUNIT_WORK *v27;
  SBTLUNIT_WORK *v28;
  u32 v29;
  s32 v31;
  SBTLUNIT_LISTWORK *v32;
  SBTLUNIT_WORK *v33;
  SBTLUNIT_WORK *v34;
  long f64 v35;
  s32 v37;
  SBTLUNIT_LISTWORK *v38;
  SBTLUNIT_WORK *v39;
  f32 x;
  f32 v41;
  f32 *v42;
  f32 w;
  f32 z;
  f32 RotToDir;
  f32 Dir180;
  f32 v47;
  f32 v48;
  f32 v49;
  u32 v50;
  SBTLUNIT_LISTWORK *v53;
  s32 playerID;
  SBTLUNIT_WORK *v55;
  f32 v56;
  f32 v57;
  f32 v58;
  f32 v59;
  f32 PosToDir;
  f32 Dir;
  f32 ShotDir;
  f32 v63;
  SBTLUNIT_LISTWORK *v65;
  s32 v66;
  SBTLUNIT_WORK *v67;
  SBTLUNIT_WORK *v68;
  s32 v70;
  f32 ShotRapid;
  f32 v72;
  f32 v75;
  u32 Pad_SeShot;
  s32 v78;
  s32 v79;
  u32 v80;
  s32 v81;
  s32 v82;
  s32 v83;
  s32 v84;
  f32 LaserRangeS;
  f32 LaserDirSS;
  f32 LaserFrameL;
  f32 v89;
  f32 v90;
  f32 v91;
  u32 v92;
  f32 v93;
  f32 v94;
  f32 v95;
  f32 StepTime;
  s32 LaserFrameS;
  f32 v99;
  f32 v100;
  f32 v101;
  f32 v102;
  f32 LaserOfsLen;
  u32 v104;
  f32 v107;
  s32 StepIntB;
  u32 v111;
  f32 ShotWay;
  f32 v114;
  f32 v115;
  f32 v116;
  f32 v117;
  u32 StepFlag2;
  f32 v119;
  f32 v121;
  f32 *gTableOffsetDir_Scatter_local;
  f32 v124;
  s32 v125;
  f32 v129;
  s32 Variation;
  AW_XAtk_WORK_t *ArgumentParam_local;
  f32 v132;
  f32 DirY;
  s64 v134;
  f32 v135;
  u32 v136;
  AW_XAtk_WORK_t *v140;
  f32 HomingFrame;
  AW_XAtk_WORK_t *v145;
  f32 v146;
  s32 v147;
  SBTLUNIT_WORK *PlayerUnit;
  f32 v149;
  f32 v150;
  f32 v152;
  f32 v153;
  f32 LenXZ;
  f32 v156;
  AW_XAtk_WORK_t *v157;
  f32 v158;
  f32 v159;
  f32 v160;
  f32 v161;
  f32 v163;
  AW_XAtk_WORK_t *v164;
  s32 ShotRapidCnt;
  s32 v167;
  f32 v168;
  u32 v169;
  f32 *v170;
  f32 v171;
  f32 v172;
  f32 v173;
  f32 v174;
  f32 v175;
  f32 v176;
  f32 v177;
  f32 v178;
  f32 *v181;
  f32 v182;
  f32 v183;
  f32 v184;
  f32 v185;
  f32 v186;
  f32 v187;
  f32 v188;
  f32 v189;
  s32 v191;
  SBTLUNIT_WORK *v192;
  f32 v193;
  f32 v194;
  f32 v195;
  AW_XAtk_WORK_t *v197;
  f32 v198;
  f32 v199;
  f32 v200;
  f32 v201;
  AW_XAtk_WORK_t *v203;
  f32 v204;
  f32 v205;
  f32 v206;
  AW_XAtk_WORK_t *v208;
  f32 v209;
  f32 v210;
  f32 GroundPos;
  u32 v212;
  f32 v213;
  f32 v215;
  s32 v216;
  SBTLUNIT_WORK *v217;
  f32 v218;
  f32 v219;
  f32 v220;
  AW_XAtk_WORK_t *v222;
  f32 v223;
  f32 v224;
  f32 v225;
  f32 v226;
  AW_XAtk_WORK_t *v228;
  f32 v229;
  f32 v230;
  f32 v231;
  AW_XAtk_WORK_t *v233;
  f32 v234;
  f32 v235;
  f32 v236;
  u32 v237;
  f32 v238;
  f32 v240;
  u32 v241;
  AW_XAtk_WORK_t *v245;
  AW_XAtk_WORK_t *v246;
  u32 v248;
  u32 v249;
  AW_XAtk_WORK_t *v251;
  s32 v252;
  SBTLUNIT_WORK *v253;
  float32x2_t v254;
  f32 v255;
  AW_XAtk_WORK_t *v257;
  u32 v258;
  u32 v259;
  AW_XAtk_WORK_t *v261;
  AW_XAtk_WORK_t *v263;
  f32 HomingZ;
  s32 v265;
  f32 HomingX;
  f32 HomingY;
  f32 v269;
  AW_XAtk_WORK_t *v271;
  f32 v272;
  s32 v273;
  s64 v275;
  s32 v276;
  s32 v277;
  sdfVector2_t *gTableOffsetXZ_local;
  s32 max_length;
  f32 *v283;
  AW_XAtk_WORK_t *v284;
  AW_XAtk_WORK_t *v286;
  AW_XAtk_WORK_t *v287;
  f32 *VZ;
  f32 *p_VelocityY;
  f32 *p_VelocityX;
  int32x2_t v291;
  f32 v292;
  f32 v293;
  f32 ZeroZ;
  s64 ZeroY;
  s64 v296;
  s64 v297;
  f32 ToZ;
  f32 ToX;
  sdfVector4_t v300;
  sdfVector4_t v301;
  sdfVector4_t v302;
  sdfVector4_t v303;

  StepIntBuff = aWork->StepIntBuff;
  v296 = 0;
  v297 = 0;
  ZeroY = 0;
  ZeroZ = 0.0;
  v4 = StepIntBuff[1];
  AW = GetAW(v4);
  v6 = GetAW(aWork->StepIntBuff[0]);
  v7 = ChkPause(aWork);
  if (((u8)v7 & 1) != 0)
  {
    if ((aWork->StepFlag2 & 0x800000) != 0)
    {
      if (sBtlCheckSetsuma())
        goto LABEL_114;
      if (sBtlPlayerCheckRSpirit())
        goto LABEL_114;
    }
    if (!aWork->Step || (v6->StepFlag & 8) == 0)
      return;
    if (sBtlCheckSetsuma())
      goto LABEL_114;
    if (!sBtlPlayerCheckRSpirit())
      return;
LABEL_114:
    Pad_SeShot = gPadTable[aWork->StepIntB]->Pad_SeShot;
    if (Pad_SeShot != -1)
    {
      Pad_SeShot = gPadTable[aWork->StepIntB]->Pad_SeShot;
      if (Pad_SeShot)
      {
        sBtlStopSE(Pad_SeShot);
      }
    }
LABEL_125:
    Delete(aWork);
    return;
  }
  ToX = aWork->X;
  v9 = ToX;
  Step = aWork->Step;
  ToZ = aWork->Z;
  v11 = ToZ;
  Y = aWork->Y;
  v13 = ToX * -100.0;
  v14 = Y * -100.0;
  v15 = ToZ * -100.0;
  switch (Step)
  {
    case 0:
      v17 = aWork->StepTime + VRF_DeltaTime;
      StepIntA = aWork->StepIntA;
      aWork->StepTime = v17;
      if (v17 <= (f32)(FPS60 * (f32)StepIntA))
        goto LABEL_135;
      v19 = aWork->StepIntBuff;
      v19[2] = -1;
      if ((aWork->StepFlag & 0x2000000) != 0)
      {
        v7 = Add(v9, Y, v11);
        v19[2] = (s32)v7;
        v19 = aWork->StepIntBuff;
        v19[3] = -1;
        if ((aWork->StepFlag & 0x4000000) == 0)
        {
LABEL_14:
          v19[4] = -1;
          StepFlag = aWork->StepFlag;
          if ((StepFlag & 0x20000) == 0)
            goto LABEL_15;
          goto LABEL_128;
        }
      }
      else
      {
        v19[3] = -1;
        if ((aWork->StepFlag & 0x4000000) == 0)
          goto LABEL_14;
      }
      v7 = AW_XAtkChargeAdd(aWork->X, aWork->Y, aWork->Z, aWork->Dir);
      v19[3] = (s32)v7;
      v19 = aWork->StepIntBuff;
      v19[4] = -1;
      StepFlag = aWork->StepFlag;
      if ((StepFlag & 0x20000) == 0)
      {
LABEL_15:
        if ((StepFlag & 0x8000000) == 0)
          goto LABEL_16;
        goto LABEL_131;
      }
LABEL_128:
      v19[4] = Add(aWork->X, aWork->Y, aWork->Z);
      v301.w = 0.0;
      v301.x = v13;
      v301.y = v14;
      v301.z = v15;
      sBtlPlay3DSE_BaseVol(0x1008Cu, 120, v301);
      if ((aWork->StepFlag & 0x8000000) == 0)
      {
LABEL_16:
        if ((aWork->StepFlag2 & 0x1000000) == 0)
          goto LABEL_132;
LABEL_160:
        ClrAction();
        goto LABEL_161;
      }
LABEL_131:
      AW_XAtkSightAdd(aWork->X, aWork->Y, aWork->Z, aWork->Dir);
      if ((aWork->StepFlag2 & 0x1000000) == 0)
        goto LABEL_132;
      goto LABEL_160;
    case 1:
      SetUnitPos(aWork);
      v22 = aWork->StepTime + VRF_DeltaTime;
      StepFloatA = aWork->StepFloatA;
      aWork->StepTime = v22;
      if (v22 <= (f32)(StepFloatA * FPS60))
        goto LABEL_135;
      goto LABEL_132;
    case 2:
      SetUnitPos(aWork);
      UnitMng = wk->UnitMng;
      Unit_ListID = aWork->Unit_ListID;
      v27 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
      if (v27)
      {
        v28 = v27;
        if (v27->UID == aWork->Unit_UID)
        {
          if (sBtlCheckLiveTarget2(v28))
          {
            v293 = aWork->Y;
            v29 = aWork->StepFlag;
            ToX = aWork->X;
            ToZ = aWork->Z;
            if ((v29 & 0x40000000) != 0)
            {
              v31 = aWork->Unit_ListID;
              v32 = wk->UnitMng;
              v33 = sBtlSearchUnit_ID(v32, v31);
              if (v33)
              {
                v34 = v33;
                v296 = 0;
                v297 = 0;
                sBtlGetUnitHelperPos(v34, 20);
                sub_1B335A0(&v296, 0, v35);
                ToZ = *(f32 *)&v297 / -100.0;
                ToX = *(f32 *)&v296 / -100.0;
                v293 = *((f32 *)&v296 + 1) / -100.0;
              }
              v29 = aWork->StepFlag;
            }
            if ((v29 & 0x80000000) != 0)
            {
              v37 = aWork->Unit_ListID;
              v38 = wk->UnitMng;
              v39 = sBtlSearchUnit_ID(v38, v37);
              if (v39)
              {
                x = v39->rot.x;
                v41 = v39->rot.y;
                v42 = v39;
                z = v39->rot.z;
                w = v39->rot.w;
                v300.x = x;
                v300.y = v41;
                v300.z = z;
                v300.w = w;
                RotToDir = sBtlGetRotToDir(v300);
                Dir180 = sBtlGetDir180(RotToDir);
                v48 = v42[42];
                v47 = v42[43];
                ToX = v42[41] / -100.0;
                ToZ = v47 / -100.0;
                v49 = v48 / -100.0;
                sBtlGetMoveXZ(ToX, v47 / -100.0, Dir180, 0.7, &ToX, &ToZ);
                v293 = v49 + 1.7;
              }
            }
            v50 = aWork->StepFlag;
            if ((v50 & 0x80000) != 0)
            {
              v53 = wk->UnitMng;
              playerID = wk->playerID;
              v55 = sBtlSearchUnit_ID(v53, playerID);
              v56 = aWork->X;
              v57 = v55->pos.x / -100.0;
              v58 = aWork->Z;
              v59 = v55->pos.z / -100.0;
              PosToDir = sBtlGetPosToDir(v56, v58, v57, v59);
              aWork->Dir = PosToDir;
              aWork->ShotDir = PosToDir;
              AW->Dir = PosToDir;
              AW->LaserDirSS = aWork->Dir;
              v50 = aWork->StepFlag;
              if ((v50 & 0x30000000) != 0)
                aWork->ShotDir = 0.0;
            }
            if ((v50 & 0x30000000) != 0)
            {
              Dir = aWork->Dir;
              ShotDir = aWork->ShotDir;
              v63 = Dir + ShotDir;
            }
            else
            {
              v63 = aWork->ShotDir;
            }
            v107 = sBtlGet360(v63);
            if ((aWork->StepFlag & 0x10000) != 0 && (v6->StepFlag & 0x40) == 0)
              Add(aWork->X, aWork->Y, aWork->Z, v107, 1.0);
            StepIntB = aWork->StepIntB;
            if (StepIntB != -1)
            {
              StepIntB = aWork->StepIntB;
              v111 = gPadTable[StepIntB]->Pad_SeShot;
              if (v111 != -1)
              {
                v111 = gPadTable[aWork->StepIntB]->Pad_SeShot;
                if (v111 == 65680)
                {
                  if (aWork->StepIntC <= 0)
                    v111 = 65680;
                  else
                    v111 = 0;
                }
                else if (v111 == 65695)
                {
                  if (gHomingSE - 1 >= 3)
                    v111 = 65695;
                  else
                    v111 = gHomingSE + 65793;
                  gHomingSE = ((u8)gHomingSE + 1) & 3;
                }
                if (((aWork->StepFlag2 & 0x200000) == 0 || aWork->StepIntC <= 0) && v111 && (v111 != 87490577 || aWork->StepIntC <= 0))
                {
                  v303.w = 0.0;
                  v303.x = v13;
                  v303.y = v14;
                  v303.z = v15;
                  sBtlPlay3DSE_BaseVol(v111, 120, v303);
                }
              }
            }
            AW_XAtkSetPos(aWork->StepIntBuff[2], aWork->X, aWork->Y, aWork->Z);
            ShotWay = aWork->ShotWay;
            v292 = aWork->ShotWayRange / ShotWay;
            if ((aWork->StepFlag & 0x30000000) != 0)
            {
              v114 = aWork->Dir;
              v115 = aWork->ShotDir;
              v116 = v114 + v115;
            }
            else
            {
              v116 = aWork->ShotDir;
            }
            v117 = sBtlGet360(v116 + (f32)((f32)(v292 * ShotWay) * -0.5));
            StepFlag2 = aWork->StepFlag2;
            if ((StepFlag2 & 0x10000) != 0)
            {
              v121 = aWork->Dir;
              gTableOffsetDir_Scatter_local = gTableOffsetDir_Scatter;
            }
            else
            {
              v119 = v117;
              if ((StepFlag2 & 0x20000) == 0)
              {
LABEL_234:
                if (aWork->ShotWay < 1)
                {
LABEL_453:
                  v78 = aWork->Step;
LABEL_133:
                  v79 = v78 + 1;
                  goto LABEL_134;
                }
                p_VelocityY = &aWork->VelocityY;
                p_VelocityX = &aWork->VelocityX;
                VZ = &aWork->VelocityZ;
                v125 = 0;
                v291.n64_u64[0] = vdup_n_s32(0xC2C80000).n64_u64[0];
                while (1)
                {
                  v129 = ToX;
                  Variation = v6->Variation;
                  ArgumentParam_local = ArgumentParam;
                  ArgumentParam_local->X = ToX;
                  ArgumentParam_local->Y = v293;
                  v132 = ToZ;
                  ArgumentParam_local->Variation = Variation;
                  ArgumentParam_local->Z = v132;
                  ArgumentParam_local->Dir = v119;
                  DirY = v6->DirY;
                  ArgumentParam_local->MoveDir = v119;
                  ArgumentParam_local->DirY = DirY;
                  ArgumentParam_local->Scale = v6->Scale;
                  *(_OWORD *)&ArgumentParam_local->MoveDirRate = *(_OWORD *)&v6->MoveDirRate;
                  ArgumentParam_local->HomingFrame = v6->HomingFrame;
                  v134 = *(u64 *)&v6->StepFlag;
                  *(u64 *)&ArgumentParam_local->Flag = v134;
                  ArgumentParam_local->SklID = v6->StepIntB;
                  ArgumentParam_local->Pad_No = aWork->StepIntC;
                  *(u64 *)&ArgumentParam_local->Unit_ListID = *(u64 *)&aWork->Unit_ListID;
                  if ((v134 & 0x40) != 0)
                  {
                    if ((v134 & 0x1000) == 0)
                    {
                      v135 = v293;
                      ArgumentParam_local->Z = v132 + 0.0;
                      ArgumentParam_local->X = v129 + 0.0;
                      ArgumentParam_local->Y = v135 + 1.8;
                    }
                    if ((aWork->StepFlag & 0x10000) != 0)
                    {
                      AW_XAtkAdd_Homing(ArgumentParam->X, ArgumentParam->Y + 0.1, ArgumentParam->Z, ArgumentParam->Dir, 1.0);
                    }
                  }
                  v136 = v6->StepFlag;
                  if ((v136 & 0x80) != 0)
                  {
                    v140 = ArgumentParam;
                    HomingFrame = ArgumentParam->HomingFrame;
                    v140->HomingFrame = HomingFrame
                                             + (f32)gTableHomingFrameShiftS[gHomingFrameShift];
                    if ((v6->StepFlag & 0x100) != 0)
                    {
LABEL_261:
                      v145 = ArgumentParam;
                      v146 = ArgumentParam->HomingFrame;
                      v145->HomingFrame = v146
                                               + (f32)gTableHomingFrameShiftM[gHomingFrameShift];
                      if ((aWork->StepFlag2 & 0x10000) == 0)
                        goto LABEL_318;
                      goto LABEL_266;
                    }
                  }
                  else if ((v136 & 0x100) != 0)
                  {
                    goto LABEL_261;
                  }
                  if ((aWork->StepFlag2 & 0x10000) == 0)
                    goto LABEL_318;
LABEL_266:
                  v147 = sBtlGetPlayerID();
                  PlayerUnit = sBtlGetPlayerUnit(v147);
                  if (PlayerUnit)
                  {
                    v149 = PlayerUnit->pos.x;
                    v150 = PlayerUnit->pos.z;
                    v152 = ArgumentParam->Z;
                    v153 = v150 / -100.0;
                    LenXZ = sBtlGetLenXZ(0.0, v152, 0.0, v153);
                    if (LenXZ < 4.0)
                      LenXZ = 4.0;
                    if (LenXZ <= 22.0)
                      v156 = LenXZ;
                    else
                      v156 = 22.0;
                    v157 = ArgumentParam;
                    v158 = v157->X;
                    v159 = v157->Z;
                    v160 = v157->Dir;
                    v161 = v149 / -100.0;
                    sBtlGetMoveXZ(v158, v159, v160, v156, &v157->HomingX, &v157->HomingZ);
                    v163 = ToX;
                    v164 = ArgumentParam;
                    v164->HomingY = 0.0;
                    ShotRapidCnt = aWork->ShotRapidCnt;
                    if (v163 <= 0.0)
                    {
                      if (v153 < -3.0 && v161 < -8.0 && ShotRapidCnt == 17)
                      {
                        *(f32 *)&v167 = 0.8;
LABEL_291:
                        v168 = *(f32 *)&v167;
                        v164 = ArgumentParam;
                        v164->HomingX = v161 + v168;
                        v164->HomingZ = v153 + 0.8;
                      }
                    }
                    else if (v153 < -3.0 && v161 > 8.0 && ShotRapidCnt == 6)
                    {
                      *(f32 *)&v167 = -0.8;
                      goto LABEL_291;
                    }
                    v169 = aWork->StepFlag;
                    if (!v125 && (v169 & 0x40000000) != 0)
                    {
                      v170 = ArgumentParam;
                      v171 = v170[9];
                      v172 = v170[7];
                      v173 = v170[8];
                      v174 = v170[21];
                      v175 = v170[19];
                      v176 = v170[20];
                      sBtlGetPosToVec(v172, v173, v171, v175, v176, v174, p_VelocityX, p_VelocityY, VZ);
                      v177 = aWork->VelocityY * 90.0;
                      v178 = -45.0;
                      aWork->DirY = v177;
                      if (v177 < -45.0 || (v178 = 45.0, v177 > 45.0))
                      {
                        v177 = v178;
                        aWork->DirY = v178;
                      }
                      v177 = aWork->DirY;
                      AW_XAtkAdd_Gun(ArgumentParam->X, ArgumentParam->Y, ArgumentParam->Z, ArgumentParam->Dir, v177);
                      v169 = aWork->StepFlag;
                    }
                    if (!v125 && (v169 & 0x80000000) != 0)
                    {
                      v181 = ArgumentParam;
                      v182 = v181[9];
                      v183 = v181[7];
                      v184 = v181[8];
                      v185 = v181[21];
                      v186 = v181[19];
                      v187 = v181[20];
                      sBtlGetPosToVec(v183, v184, v182, v186, v187, v185, p_VelocityX, p_VelocityY, VZ);
                      v188 = aWork->VelocityY * 90.0;
                      v189 = -45.0;
                      aWork->DirY = v188;
                      if (v188 < -45.0 || (v189 = 45.0, v188 > 45.0))
                      {
                        v188 = v189;
                        aWork->DirY = v189;
                      }
                      v188 = aWork->DirY;
                      AW_XAtkAdd_Gun(ArgumentParam->X, ArgumentParam->Y, ArgumentParam->Z, ArgumentParam->Dir, v188);
                    }
                  }
LABEL_318:
                  if ((aWork->StepFlag2 & 0x20000) != 0)
                  {
                    v191 = sBtlGetPlayerID();
                    v192 = sBtlGetPlayerUnit(v191);
                    if (v192)
                    {
                      if ((aWork->StepFlag2 & 0x100000) != 0)
                      {
                        v194 = v192->pos.x;
                        v195 = v192->pos.z;
                        v197 = ArgumentParam;
                        v198 = v197->X;
                        v199 = v197->Z;
                        v200 = sBtlGetLenXZ(v198, v199, v194 / -100.0, v195 / -100.0);
                        if (v200 >= 10.0)
                          v201 = v200;
                        else
                          v201 = 10.0;
                        v193 = v201 + (f32)((f32)((f32)(u32)sub_1905740(800, 0) + -500.0) / 100.0);
                        if (v193 < 4.0)
                          v193 = 4.0;
                      }
                      else
                      {
                        v193 = 40.0;
                      }
                      v203 = ArgumentParam;
                      v204 = v203->X;
                      v205 = v203->Z;
                      v206 = v203->Dir;
                      sBtlGetMoveXZ(v204, v205, v206, v193, &v203->HomingX, &v203->HomingZ);
                      v208 = ArgumentParam;
                      v208->HomingY = v208->Y;
                      if ((aWork->StepFlag2 & 0x100000) != 0)
                      {
                        v208 = ArgumentParam;
                        v209 = v208->X;
                        v210 = v208->Z;
                        GroundPos = sBtlGetGroundPos(v209 * -100.0, v210 * -100.0);
                        ArgumentParam->HomingY = GroundPos / -100.0;
                      }
                      v212 = aWork->StepFlag;
                      if (!v125 && (v212 & 0x40000000) != 0)
                      {
                        aWork->DirY = 0.0;
                        v213 = 0.0;
                        v213 = aWork->DirY;
                        AW_XAtkAdd_Gun(ArgumentParam->X, ArgumentParam->Y, ArgumentParam->Z, ArgumentParam->Dir, v213);
                        v212 = aWork->StepFlag;
                      }
                      if (!v125 && (v212 & 0x80000000) != 0)
                      {
                        aWork->DirY = 0.0;
                        v215 = 0.0;
                        v215 = aWork->DirY;
                        AW_XAtkAdd_Gun(ArgumentParam->X, ArgumentParam->Y, ArgumentParam->Z, ArgumentParam->Dir, v215);
                      }
                    }
                  }
                  if ((aWork->StepFlag2 & 0x80000) != 0)
                  {
                    v216 = sBtlGetPlayerID();
                    v217 = sBtlGetPlayerUnit(v216);
                    if (v217)
                    {
                      if ((aWork->StepFlag2 & 0x100000) != 0)
                      {
                        v219 = v217->pos.x;
                        v220 = v217->pos.z;
                        v222 = ArgumentParam;
                        v223 = v222->X;
                        v224 = v222->Z;
                        v225 = sBtlGetLenXZ(v223, v224, v219 / -100.0, v220 / -100.0);
                        if (v225 >= 10.0)
                          v226 = v225;
                        else
                          v226 = 10.0;
                        v218 = v226 + (f32)((f32)((f32)(u32)sub_1905740(800, 0) + -500.0) / 100.0);
                        if (v218 < 4.0)
                          v218 = 4.0;
                      }
                      else
                      {
                        v218 = 40.0;
                      }
                      v228 = ArgumentParam;
                      v229 = v228->X;
                      v230 = v228->Z;
                      v231 = v228->Dir;
                      sBtlGetMoveXZ(v229, v230, v231, v218, &v228->HomingX, &v228->HomingZ);
                      v233 = ArgumentParam;
                      v233->HomingY = v233->Y;
                      if ((aWork->StepFlag2 & 0x100000) != 0)
                      {
                        v233 = ArgumentParam;
                        v234 = v233->X;
                        v235 = v233->Z;
                        v236 = sBtlGetGroundPos(v234 * -100.0, v235 * -100.0);
                        ArgumentParam->HomingY = v236 / -100.0;
                      }
                      v237 = aWork->StepFlag;
                      if (!v125 && (v237 & 0x40000000) != 0)
                      {
                        aWork->DirY = 0.0;
                        v238 = 0.0;
                        v238 = aWork->DirY;
                        AW_XAtkAdd_Gun(ArgumentParam->X, ArgumentParam->Y, ArgumentParam->Z, ArgumentParam->Dir, v238);
                        v237 = aWork->StepFlag;
                      }
                      if (!v125 && (v237 & 0x80000000) != 0)
                      {
                        aWork->DirY = 0.0;
                        v240 = 0.0;
                        v240 = aWork->DirY;
                        AW_XAtkAdd_Gun(ArgumentParam->X, ArgumentParam->Y, ArgumentParam->Z, ArgumentParam->Dir, v240);
                      }
                    }
                  }
                  v241 = aWork->StepFlag2;
                  if ((v241 & 0x40000) != 0)
                  {
                    v245 = ArgumentParam;
                    v246 = ArgumentParam;
                    v245->HomingX = gHomingPosX;
                    *(u64 *)&v246->HomingY = *(u64 *)&gHomingPosY;
                    if ((aWork->StepFlag2 & 0x400000) == 0)
                    {
LABEL_390:
                      if ((aWork->StepFlag & 0x100000) == 0)
                        goto LABEL_411;
LABEL_401:
                      v252 = sBtlGetPlayerID();
                      v253 = sBtlGetPlayerUnit(v252);
                      if (v253)
                      {
                        v254.n64_u64[0] = *(u64 *)&v253->pos.x;
                        v255 = v253->pos.z;
                        v257 = ArgumentParam;
                        *(float32x2_t *)&v257->HomingX = vdiv_f32(v254, v291);
                        v257->HomingZ = v255 / -100.0;
                        if ((aWork->StepFlag & 0x400000) != 0 && aWork->ShotRapidCnt | v125)
                        {
                          v258 = sub_1905740(500, 0);
                          v259 = sub_1905740(500, 0);
                          v261 = ArgumentParam;
                          v261->HomingX = (f32)((f32)((f32)v258 + -250.0) / 100.0) + v261->HomingX;
                          v261->HomingZ = (f32)((f32)((f32)v259 + -250.0) / 100.0) + v261->HomingZ;
                        }
                      }
                      goto LABEL_411;
                    }
                  }
                  else if ((v241 & 0x400000) == 0)
                  {
                    goto LABEL_390;
                  }
                  v248 = sub_1905740(250, 0);
                  v249 = sub_1905740(250, 0);
                  v251 = ArgumentParam;
                  v251->HomingX = (f32)((f32)((f32)v248 + -125.0) / 100.0) + v251->HomingX;
                  v251->HomingZ = (f32)((f32)((f32)v249 + -125.0) / 100.0) + v251->HomingZ;
                  if ((aWork->StepFlag & 0x100000) != 0)
                    goto LABEL_401;
LABEL_411:
                  if ((aWork->StepFlag & 0x200000) == 0)
                    goto LABEL_425;
                  if (aWork->ShotRapidCnt | v125)
                  {
                    v263 = ArgumentParam;
                    *(u64 *)&v263->HomingX = *(u64 *)&aWork->HomingX;
                    HomingZ = aWork->HomingZ;
LABEL_424:
                    v263->HomingZ = HomingZ;
                    goto LABEL_425;
                  }
                  v265 = sBtlGetPlayerID();
                  if (sBtlGetPlayerUnit(v265))
                  {
                    sBtlGetZeroPos((f32 *)&ZeroY + 1, &ZeroY, &ZeroZ);
                    HomingX = *((f32 *)&ZeroY + 1) / -100.0;
                    HomingY = *(f32 *)&ZeroY / -100.0;
                    v269 = ZeroZ;
                    aWork->HomingX = *((f32 *)&ZeroY + 1) / -100.0;
                    aWork->HomingY = HomingY;
                    HomingZ = v269 / -100.0;
                    aWork->HomingZ = HomingZ;
                    HomingX = aWork->HomingX;
                    HomingY = aWork->HomingY;
                    HomingZ = aWork->HomingZ;
                    v263 = ArgumentParam;
                    v263->HomingX = HomingX;
                    v263->HomingY = HomingY;
                    goto LABEL_424;
                  }
LABEL_425:
                  if ((aWork->StepFlag & 0x1000000) == 0)
                    goto LABEL_438;
                  if (aWork->ShotRapidCnt | v125)
                  {
                    v271 = ArgumentParam;
                    *(u64 *)&v271->HomingX = *(u64 *)&aWork->HomingX;
                    v272 = aWork->HomingZ;
                    goto LABEL_437;
                  }
                  v273 = sBtlGetPlayerID();
                  if (sBtlGetPlayerUnit(v273))
                  {
                    *(u64 *)&aWork->HomingX = 0;
                    aWork->HomingZ = 0.0;
                    v272 = 0.0;
                    v275 = 0;
                    v271 = ArgumentParam;
                    *(u64 *)&v271->HomingX = v275;
LABEL_437:
                    v271->HomingZ = v272;
                  }
LABEL_438:
                  if ((aWork->StepFlag & 0x800000) != 0)
                  {
                    v276 = aWork->ShotRapidCnt;
                    v277 = aWork->ShotWay;
                    gTableOffsetXZ_local = gTableOffsetXZ;
                    max_length = gTableOffsetXZ_local->max_length;
                    gTableOffsetXZ_local = gTableOffsetXZ;
                    v283 = (&gTableOffsetXZ_local->obj.klass + (v125 + v277 * v276) % max_length);
                    v284 = ArgumentParam;
                    v284->HomingX = v284->HomingX + (f32)(v283[8] * 3.5);
                    v284->HomingZ = v284->HomingZ + (f32)(v283[9] * 3.5);
                  }
                  if (AW)
                  {
                    v286 = ArgumentParam;
                    v286->Group_AW_Idx = AW->Idx;
                    v286->Group_AW_UID = AW->UID;
                    goto LABEL_237;
                  }
                  else
                  {
                    v287 = ArgumentParam;
                    v287->Group_AW_Idx = -1;
                    v287->Group_AW_UID = -1;
                    goto LABEL_237;
                  }
LABEL_237:
                  Add(AW_XAtkBullet);
                  ++v125;
                  v119 = v292 + v119;
                  gHomingFrameShift = (gHomingFrameShift + 1)
                                                         % SLODWORD(gTableHomingFrameShiftS->max_length);
                  ++aWork->StepIntC;
                  if (v125 >= aWork->ShotWay)
                    goto LABEL_453;
                }
              }
              v121 = aWork->Dir;
              gTableOffsetDir_Scatter_local = gTableOffsetDir_Scatter2;
            }
            v124 = gTableOffsetDir_Scatter_local[aWork->ShotRapidCnt];
            v119 = sBtlGet360(v121 + v124);
            goto LABEL_234;
          }
        }
      }
      *(u64 *)&aWork->Step = 11;
      if (AW)
        goto LABEL_136;
      return;
    case 3:
      aWork->StepTime = aWork->StepTime + VRF_DeltaTime;
      if (!AW || !v6)
        goto LABEL_84;
      if (AW->StepBoolA)
        goto LABEL_97;
      v65 = wk->UnitMng;
      v66 = aWork->Unit_ListID;
      v67 = sBtlSearchUnit_ID(v65, v66);
      if (!v67)
        goto LABEL_83;
      v68 = v67;
      if (v67->UID != aWork->Unit_UID)
        goto LABEL_83;
      if (!sBtlCheckLiveTarget2(v68))
LABEL_83:
        AW->StepBoolB = 1;
LABEL_84:
      SetUnitPos(aWork);
      if (aWork->StepTime <= (f32)(FPS60 * (f32)aWork->ShotRapidInt))
        goto LABEL_135;
      v70 = aWork->ShotRapidCnt + 1;
      ShotRapid = aWork->ShotRapid;
      aWork->ShotRapidCnt = v70;
      if (ShotRapid > (f32)v70)
      {
        v72 = aWork->ShotDir + aWork->ShotDirRate;
        aWork->ShotDir = v72;
        aWork->ShotDir = sBtlGet360(v72);
        *(u64 *)&aWork->Step = 2;
        if (!AW)
          return;
LABEL_136:
        v80 = v6->StepFlag;
        if ((v80 & 0x18) != 8)
          goto LABEL_143;
        v81 = AW->Step;
        if (v81)
        {
          if (v81 != 1 || aWork->Step != 10)
          {
LABEL_143:
            if ((v80 & 0x10) == 0)
              return;
            v83 = AW->Step;
            if (v83 == 2)
            {
              LaserRangeS = AW->LaserRangeS;
              LaserDirSS = AW->LaserDirSS;
              LaserFrameL = AW->LaserFrameL;
              v89 = AW->StepTime + VRF_DeltaTime;
              AW->StepTime = v89;
              v90 = v89 * (f32)(LaserRangeS / (f32)(FPS60 * LaserFrameL));
              if (v90 <= LaserRangeS)
                v91 = v90;
              else
                v91 = LaserRangeS;
              if (AW->LaserRev == -1.0)
              {
                if (!v92)
                v93 = LaserDirSS - v91;
              }
              else
              {
                if (!v92)
                v93 = v91 + LaserDirSS;
              }
              v99 = sBtlGet360(v93);
              aWork->Dir = v99;
              StepTime = AW->StepTime;
              LaserFrameS = AW->LaserFrameL;
            }
            else
            {
              if (v83 != 1)
              {
                if (v83 || aWork->StepIntC < 1)
                {
LABEL_170:
                  if ((aWork->StepFlag & 0x30000000) != 0)
                  {
                    v100 = aWork->X;
                    v101 = aWork->Z;
                    v102 = aWork->Dir;
                    LaserOfsLen = AW->LaserOfsLen;
                    sBtlGetMoveXZ(v100, v101, v102, LaserOfsLen, &aWork->X, &aWork->Z);
                  }
                  return;
                }
                v84 = 1;
LABEL_169:
                AW->Step = v84;
                AW->StepTime = 0.0;
                goto LABEL_170;
              }
              if (!aWork->StepIntC)
                goto LABEL_170;
              AW->StepTime = AW->StepTime + VRF_DeltaTime;
              v94 = AW->LaserDirSS;
              v95 = sBtlGet360(v94);
              aWork->Dir = v95;
              StepTime = AW->StepTime;
              LaserFrameS = AW->LaserFrameS;
            }
            if (StepTime <= (f32)(FPS60 * (f32)LaserFrameS))
              goto LABEL_170;
            v84 = 2;
            goto LABEL_169;
          }
          v82 = 2;
        }
        else
        {
          v82 = 1;
        }
        AW->Step = v82;
        AW->StepTime = 0.0;
        goto LABEL_143;
      }
      *(u64 *)&aWork->Step = 10;
      if (v6 && (v6->StepFlag & 0x10) != 0)
      {
        v79 = 4;
LABEL_134:
        aWork->Step = v79;
      }
      else
      {
        v104 = aWork->StepFlag;
        if ((v104 & 0x2000000) != 0)
        {
          AW_XAtkScaleFadeOut(aWork->StepIntBuff[2]);
          aWork->StepIntBuff[2] = -1;
          v302.w = 0.0;
          v302.x = v13;
          v302.y = v14;
          v302.z = v15;
          sBtlPlay3DSE_BaseVol(0x1008Du, 120, v302);
          v104 = aWork->StepFlag;
        }
        if ((v104 & 0x4000000) != 0)
        {
          AW_XAtkChargeScaleFadeOut(aWork->StepIntBuff[3]);
          aWork->StepIntBuff[3] = -1;
          if (!AW)
            return;
          goto LABEL_136;
        }
      }
LABEL_135:
      if (!AW)
        return;
      goto LABEL_136;
    case 4:
      SetUnitPos(aWork);
      if (!AW)
        return;
      if (AW->StepBoolA || AW->Step == 2)
      {
LABEL_97:
        *(u64 *)&aWork->Step = 10;
        AW_XAtkScaleFadeOut(aWork->StepIntBuff[2]);
        aWork->StepIntBuff[2] = -1;
      }
      goto LABEL_136;
    case 10:
      SetUnitPos(aWork);
      v75 = aWork->StepTime + VRF_DeltaTime;
      aWork->StepTime = v75;
      if (v75 <= (f32)(FPS60 * 60.0))
        goto LABEL_135;
LABEL_132:
      v78 = aWork->Step;
      aWork->StepTime = 0.0;
      goto LABEL_133;
    case 11:
LABEL_161:
      goto LABEL_125;
    default:
      goto LABEL_135;
  }
}

// 0x1e92840
void AW_XAtkCalc3(AW_WORK_t *aWork) {
  s32 v4;
  AW_WORK_t *AW;

  if (IsSceanStop())
    return;
  if (wk->mode == 5)
    return;
  v4 = aWork->StepIntBuff[1];
  AW = GetAW(v4);
  if (AW)
  {
    if ((aWork->StepFlag & 0x30000000) != 0)
    {
      *(u64 *)&AW->X = *(u64 *)&aWork->X;
      AW->Z = aWork->Z;
    }
    *(u64 *)&AW->Dir = *(u64 *)&aWork->Dir;
  }
}

// 0x1e92990
void AW_XAtkSetHomingPos(f32 _Ps2X, f32 _Ps2Y, f32 _Ps2Z) {
  f32 *static_fields;

  static_fields[8] = Ps2X / -100.0;
  static_fields[9] = Ps2Y / -100.0;
  static_fields[10] = Ps2Z / -100.0;
}

// 0x1e83c80
void AW_XAtkDelete_XATK_FLAG2_BsFlowClr(void) {
  s32 v1;
  AW_WORK_t *AW_IDNUM;
  AW_WORK_t *v5;

  v1 = 0;
  while (1)
  {
    AW_IDNUM = GetAW_IDNUM(600, v1);
    if (!AW_IDNUM)
      break;
    v5 = AW_IDNUM;
    if ((AW_IDNUM->StepFlag2 & 0x1000000) != 0)
    {
      Delete(v5);
    }
    else
    {
      ++v1;
    }
  }
}

// 0x1e92a20
void AW_XAtkDelete_XATK_FLAG2_BsFlowClr_Setsuma(void) {
  s32 i;
  AW_WORK_t *AW_IDNUM;
  s32 v3;
  AW_WORK_t *v5;
  AW_WORK_t *v6;

  for (i = 0; i != 999; ++i)
  {
    AW_IDNUM = GetAW_IDNUM(600, i);
    if (!AW_IDNUM)
      break;
    if ((AW_IDNUM->StepFlag2 & 0x2000000) != 0)
      return;
  }
  v3 = 0;
  while (1)
  {
    v5 = GetAW_IDNUM(600, v3);
    if (!v5)
      break;
    v6 = v5;
    if ((v5->StepFlag2 & 0x1000000) != 0)
    {
      ClrAction();
      Delete(v6);
    }
    else
    {
      ++v3;
    }
  }
}

// 0x1e92b50
void AW_XAtkDelete_BossDYING(SBTLUNIT_WORK *wkBoss) {
  s32 v3;
  AW_WORK_t *AW_IDNUM;
  AW_WORK_t *v7;

  if (wkBoss)
  {
    v3 = 0;
    while (1)
    {
      AW_IDNUM = GetAW_IDNUM(600, v3);
      if (!AW_IDNUM)
        break;
      v7 = AW_IDNUM;
      if (AW_IDNUM->Unit_UID == wkBoss->UID)
      {
        if ((AW_IDNUM->StepFlag2 & 0x1000000) != 0)
          ClrAction();
        Delete(v7);
      }
      else
      {
        ++v3;
      }
    }
  }
}

// 0x1e83d70
void AW_XAtkDelete_DuplicationNG(SBTLUNIT_WORK *wkBoss) {
  s32 v3;
  AW_WORK_t *AW_IDNUM;
  AW_WORK_t *v7;

  if (wkBoss)
  {
    v3 = 0;
    while (1)
    {
      AW_IDNUM = GetAW_IDNUM(600, v3);
      if (!AW_IDNUM)
        break;
      v7 = AW_IDNUM;
      if (AW_IDNUM->Unit_UID == wkBoss->UID)
      {
        Delete(v7);
      }
      else
      {
        ++v3;
      }
    }
  }
}

// 0x1e92c70
void AW_XAtkClearBattleEnd_Pad(void) {
  SBTLUNIT_WORK *wk;
  AW_XAtkPad_Arg_t *ArgumentParam_local;

  wk = ArgumentParam->wk;
  if (!wk)
    return;
  wk = ArgumentParam->wk;
  ClassMemAlloc(wk, 0);
  ArgumentParam_local = ArgumentParam;
  ArgumentParam_local->wk = 0;
}
