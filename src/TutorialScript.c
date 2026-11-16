#include "types.h"
#include "SBTLUNIT_MOTION.h"
#include "dds3kerneldraw.h"
#include "fld.h"
#include "mdl.h"
#include "sbtl.h"
#include "sbtlaction.h"
#include "sbtlcamera.h"
#include "sbtlencount.h"
#include "sbtlmain.h"
#include "sbtlplayer.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sdf_vu0.h"
#include "sdfquat.h"
#include "sdfsystem.h"
#include "tutorialscript.h"

#define ALP_ROT -50
#define UKOBAC_ROT 45

static sdfVector4_t BOSS_CAM_RAIDOU_POS;
static s32 rotFrame;

// 0x2133540
void RaidouMotion(SBTLUNIT_MOTION _motion) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v7;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v7 = sBtlSearchUnit_ID(UnitMng, playerID);
  v7->vstatus |= 0x2000000u;
  sBtlSetMotion(v7, motion, 0, 0, 1);
  if (motion == 42)
  {
    v7->actaiwk->scrMotion = 43;
  }
  else if (motion == 186)
  {
    v7->actaiwk->scrMotion = 187;
  }
  else
  {
    if (motion == 188)
      motion = 189;
    v7->actaiwk->scrMotion = motion;
  }
}

// 0x2133670
void T_OkikumuMotion(SBTLUNIT_MOTION _motion) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 boss_eventID;
  SBTLUNIT_WORK *v7;
  s32 v8;

  UnitMng = wk->UnitMng;
  boss_eventID = wk->boss_eventID;
  v7 = sBtlSearchUnit_ID(UnitMng, boss_eventID);
  v7->vstatus |= 0x2000000u;
  sBtlSetMotion(v7, motion, 0, 0, 1);
  v8 = motion - 32;
  if ((u32)(motion - 32) <= 7 && ((0xABu >> v8) & 1) != 0)
    motion = dword_3E60598[v8];
  v7->actaiwk->scrMotion = motion;
}

// 0x2133770
void LoadEff(void) {
  void *Asset;
  void *v7;
  void *p_effRec;
  void *v9;

  Load(Dependent, "bossevent", "bossevent");
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Asset = LoadAsset(_Ctrl_k__BackingField, "bossevent", "effect_072", 0);
  if (!Asset)
  {
    v9 = 0;
    effRec = 0;
    p_effRec = &effRec;
    goto LABEL_23;
  }
  if (Asset->klass == UnityEngine_GameObject)
    v7 = Asset;
  else
    v7 = 0;
  effRec = v7;
  p_effRec = &effRec;
  if (Asset->klass == UnityEngine_GameObject)
    v9 = Asset;
  else
    v9 = 0;
LABEL_23:
  Unload(Dependent, "bossevent", 0);
}

// 0x2133960
void InstanceEff(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 boss_eventID;
  SBTLUNIT_WORK *v5;
  void *transform;
  Il2CppObject *v11;
  void *v13;
  void *v14;
  void *v15;
  void *v16;
  sdfVector3_t position;
  sdfQuaternion_t rotation;

  UnitMng = wk->UnitMng;
  boss_eventID = wk->boss_eventID;
  v5 = sBtlSearchUnit_ID(UnitMng, boss_eventID);
  transform = get_transform(hook, 0);
  v11 = Instantiate_object__39504352(effRec, transform);
  effObj = v11;
  v13 = get_transform(effObj, 0);
  v14 = get_transform(v5->hModel->modelRoot->modelObj, 0);
  position = get_position(v14, 0);
  set_position(v13, position, 0);
  v15 = get_transform(effObj, 0);
  v16 = get_transform(v5->hModel->modelRoot->modelObj, 0);
  rotation = get_rotation(v16, 0);
  set_rotation(v15, rotation, 0);
}

// 0x2133b50
void DestroyEff(void) {
  Destroy_61007920(effObj, 0);
  effObj = 0;
  effRec = 0;
}

// 0x2133c40
void UnitOnOff(s32 _unit, s32 _active) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 boss_eventID;
  SBATTLE_WORK *v11;
  SBTLUNIT_WORK *Nakama;

  switch (unit)
  {
    case 0:
      UnitMng = wk->UnitMng;
      boss_eventID = wk->boss_eventID;
      goto LABEL_12;
    case 1:
      v11 = wk;
      UnitMng = v11->UnitMng;
      boss_eventID = v11->playerID;
LABEL_12:
      Nakama = sBtlSearchUnit_ID(UnitMng, boss_eventID);
      if (!Nakama)
        return;
      goto LABEL_17;
    case 2:
      Nakama = sBtlGetNakama(0);
      if (!Nakama)
        return;
      goto LABEL_17;
    case 3:
      Nakama = sBtlGetNakama(1);
      if (Nakama)
LABEL_17:
        Nakama->vstatus = Nakama->vstatus & 0xFFFFEFFF | ((active != 0) << 12);
      break;
    default:
      return;
  }
}

// 0x2133d90
bool NakamaRot(s32 _unit, s32 _frame) {
  SBTLUNIT_WORK *Nakama;
  f32 v6;
  SBTLUNIT_WORK *v7;
  struct sdfVector4_t vct_A_local;
  sdfVector4_t *p_rot;

  Nakama = sBtlGetNakama(unit);
  if (Nakama)
  {
    v6 = -0.87266463;
    v7 = Nakama;
    if (unit != 1)
      v6 = 0.7853982;
    FromEuler(0.0, v6, 0.0);
    vct_A_local = vct_A;
    vct_B = vct_A_local;
    FromEuler(0.0, 0.0, 0.0);
    Slerp((f32)rotFrame / (f32)frame, 0);
    p_rot = &v7->rot;
    *p_rot = vct_A;
    sBtlSetRotateDeg(v7);
    if (rotFrame >= frame)
    {
      rotFrame = 0;
      LOBYTE(Nakama) = 1;
    }
    else
    {
      LOBYTE(Nakama) = 0;
      rotFrame = rotFrame + 1;
    }
    return (char)Nakama;
  }
  return (char)Nakama;
}

// 0x2134070
void PosReset(s32 _boss, s32 _lookUp) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v10;
  SB_ENCOUNTPAC *EncountPac;
  s16 start_playerpos;
  f32 v14;
  sdfVector4_t *p_rot;
  s32 v17;
  sdfVector4_t *p_rot_p;
  f32 *p_x;
  f32 v22;
  f32 v23;
  f32 z;
  f32 w;
  f32 *v27;
  dds3ModelHandle_t *hModel;
  struct sdfVector4_t v29;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v32;
  f32 v34;
  f32 Dir180;
  f32 PosToDir;
  f32 v37;
  f32 LenXZ;
  f32 v39;
  f32 v40;
  f32 v42;
  f32 v43;
  sdfVector4_t *v46;
  dds3ModelHandle_t *v47;
  struct sdfVector4_t v48;
  SBTLUNIT_WORK *v51;
  SBTLUNIT_WORK *v52;
  f32 v54;
  f32 v55;
  f32 v56;
  f32 v57;
  f32 v58;
  f32 v59;
  f32 v60;
  f32 v62;
  f32 v63;
  sdfVector4_t *v66;
  dds3ModelHandle_t *v67;
  struct sdfVector4_t v68;
  s32 v71;
  s64 v79;
  s64 ToZ;
  s64 r;
  f32 y;
  f32 x;

  v79 = 0;
  ToZ = 0;
  x = 0.0;
  y = 0.0;
  r = 0;
  sBtlShugouKaijyo();
  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v10 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (v10)
  {
    EncountPac = sBtlGetEncountPac(-1);
    start_playerpos = EncountPac[wk->encountno]->start_playerpos;
    mapEncPointGet(start_playerpos, &x, &y, (f32 *)&r + 1, &r);
    v14 = y;
    v10->pos.x = x;
    v10->pos.y = v14;
    v10->pos.z = *((f32 *)&r + 1);
    FromEuler(0.0, *(f32 *)&r * 0.017453292, 0.0);
    p_rot = &v10->rot;
    v17 = (u8)byte_5755EF5;
    *p_rot = vct_A;
    if (v17)
      goto LABEL_20;
    goto LABEL_75;
    if (v71)
    {
LABEL_20:
      goto LABEL_21;
    }
LABEL_75:
LABEL_21:
    *(u64 *)&vct_A.x = 0;
    *(u64 *)&vct_A.z = 0;
    p_rot_p = &v10->rot_p;
    *p_rot_p = vct_A;
    LODWORD(v10->mv_rotbk) = r;
    if (boss)
    {
      p_x = &BOSS_CAM_RAIDOU_POS.x;
      v22 = *p_x;
      v10->pos.x = *p_x;
      v23 = p_x[1];
      v10->pos.y = v23;
      z = p_x[2];
      v10->pos.z = z;
      w = v10->pos.w;
LABEL_27:
      v27 = &vf00.x;
      v27[4] = v22;
      v27[5] = v23;
      v27[6] = z;
      v27[7] = w;
      hModel = v10->hModel;
      mdlSetPosition(v10->hModel);
      v29 = *p_rot;
      vct_A = v29;
      mdlSetRotate(v10->hModel);
      sBtlResetAction_FO_Eve(v10, lookUp == 1);
      sBtlStatusBitOff(v10, 0xFFFFFFEF);
      goto LABEL_37;
    }
    v22 = v10->pos.x;
    v23 = v10->pos.y;
    z = v10->pos.z;
    w = v10->pos.w;
    goto LABEL_27;
  }
LABEL_37:
  Nakama = sBtlGetNakama(0);
  if (Nakama)
  {
    v32 = Nakama;
    Nakama->pos.x = v10->pos.x;
    Nakama->pos.y = v10->pos.y;
    Nakama->pos.z = v10->pos.z;
    v34 = wk->scene->camera->followUpAngle.x;
    Dir180 = sBtlGetDir180(v34);
    PosToDir = sBtlGetPosToDir(0.0, 0.0, -200.0, 200.0);
    v37 = sBtlGet360(Dir180 + PosToDir);
    LenXZ = sBtlGetLenXZ(0.0, 0.0, -200.0, 200.0);
    sBtlGetMoveXZ(0.0, 0.0, v37, LenXZ, (f32 *)&ToZ + 1, &ToZ);
    v39 = v32->pos.y;
    v40 = v32->pos.x + *((f32 *)&ToZ + 1);
    v42 = v32->pos.w;
    v43 = v32->pos.z + *(f32 *)&ToZ;
    v32->pos.x = v40;
    v32->pos.z = v43;
    v32->rot = v10->rot;
    v32->rot_p = v10->rot;
    v32->mv_rotbk = v10->mv_rotbk;
    v46 = &v32->rot;
    vct_A.x = v40;
    vct_A.y = v39;
    vct_A.z = v43;
    vct_A.w = v42;
    v47 = v32->hModel;
    mdlSetPosition(v32->hModel);
    v48 = *v46;
    vct_A = v48;
    mdlSetRotate(v32->hModel);
    v32->vstatus |= 0x2000000u;
    sBtlSetMotion(v32, 0, 6, 0, 2);
    sBtlSetAction(v32, 1, 0);
  }
  v51 = sBtlGetNakama(1);
  if (v51)
  {
    v52 = v51;
    v51->pos.x = v10->pos.x;
    v51->pos.y = v10->pos.y;
    v51->pos.z = v10->pos.z;
    v54 = wk->scene->camera->followUpAngle.x;
    v55 = sBtlGetDir180(v54);
    v56 = sBtlGetPosToDir(0.0, 0.0, 200.0, 200.0);
    v57 = sBtlGet360(v55 + v56);
    v58 = sBtlGetLenXZ(0.0, 0.0, 200.0, 200.0);
    sBtlGetMoveXZ(0.0, 0.0, v57, v58, (f32 *)&v79 + 1, &v79);
    v59 = v52->pos.y;
    v60 = v52->pos.x + *((f32 *)&v79 + 1);
    v62 = v52->pos.w;
    v63 = v52->pos.z + *(f32 *)&v79;
    v52->pos.x = v60;
    v52->pos.z = v63;
    v52->rot = v10->rot;
    v52->rot_p = v10->rot;
    v52->mv_rotbk = v10->mv_rotbk;
    v66 = &v52->rot;
    vct_A.x = v60;
    vct_A.y = v59;
    vct_A.z = v63;
    vct_A.w = v62;
    v67 = v52->hModel;
    mdlSetPosition(v52->hModel);
    v68 = *v66;
    vct_A = v68;
    mdlSetRotate(v52->hModel);
    v52->vstatus |= 0x2000000u;
    sBtlSetMotion(v52, 0, 6, 0, 2);
    sBtlSetAction(v52, 1, 0);
  }
  sBtlResetIdling_HD();
}

// 0x2134ad0
sdfVector4_t WajutsuPosSet(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v5;
  SBTLUNIT_WORK *v6;
  sdfVector4_t *p_rot;
  s32 v9;
  sdfVector4_t *p_rot_p;
  s32 v12;
  struct sdfVector4_t pos;
  dds3ModelHandle_t *hModel;
  struct sdfVector4_t v17;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  s32 v29;
  struct sdfVector4_t v30;
  struct sdfVector4_t v31;
  sdfVector4_t v34;
  sdfVector4_t result;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v5 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (!v5)
  {
    x = 0.0;
    y = 0.0;
    z = 0.0;
    w = 0.0;
    goto LABEL_24;
  }
  v6 = v5;
  *(u64 *)&v5->pos.y = 0;
  v5->pos.x = 0.0;
  FromEuler(0.0, 0.0, 0.0);
  p_rot = &v6->rot;
  v9 = (u8)byte_5755EF5;
  *p_rot = vct_A;
  if (v9)
    goto LABEL_12;
  goto LABEL_30;
  if (v29)
  {
LABEL_12:
    goto LABEL_13;
  }
LABEL_30:
LABEL_13:
  vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
  p_rot_p = &v6->rot_p;
  v12 = (u8)byte_5755EF5;
  v6->mv_rotbk = 0.0;
  *p_rot_p = vct_A;
  pos = v6->pos;
  if (v12)
  {
    goto LABEL_17;
  }
  else
  {
    v30 = v6->pos;
    pos = v30;
LABEL_17:
    vct_A = pos;
    hModel = v6->hModel;
    goto LABEL_18;
  }
  v31 = pos;
  vct_A = v31;
  hModel = v6->hModel;
LABEL_18:
  mdlSetPosition(hModel);
  v17 = *p_rot;
  vct_A = v17;
  mdlSetRotate(v6->hModel);
  sBtlResetAction(v6);
  sBtlSetAction(v6, 1, 0);
  x = v6->pos.x;
  y = v6->pos.y;
  z = v6->pos.z;
  w = v6->pos.w;
LABEL_24:
  v34.x = x;
  v34.y = y;
  v34.z = z;
  v34.w = w;
  NakamaRaidouPosSet(v34, 0.0);
  result.x = x;
  result.y = y;
  result.z = z;
  result.w = w;
  return result;
}

// 0x21355e0
void CameraNormalPosSet(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v5;
  dds3ModelHandle_t *hModel;
  s32 v12;
  sdfVector4_t v13;

  dds3BistaClear();
  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v5 = sBtlSearchUnit_ID(UnitMng, playerID);
  v5->pos = (struct sdfVector4_t)xmmword_3CF91B0;
  vct_A = (struct sdfVector4_t)xmmword_3CF91B0;
  hModel = v5->hModel;
  mdlSetPosition(hModel);
  v13.w = 1.0;
  v13.y = 0.0;
  v13.x = 50.0;
  v13.z = -347.0;
  NakamaRaidouPosSet(v13, 180.0);
  v12 = (u8)byte_5755EF6;
  vct_A = (struct sdfVector4_t)xmmword_3CFA980;
  if (v12)
  {
    return;
  }
}

// 0x2134f30
void NakamaRaidouPosSet(const sdfVector4_t *_raidouPos, f32 _r) {
  f32 z;
  f32 y;
  f32 x;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v8;
  f32 v9;
  f32 v10;
  sdfVector4_t *p_rot;
  s32 v13;
  sdfVector4_t *p_rot_p;
  s32 v16;
  struct sdfVector4_t pos;
  dds3ModelHandle_t *hModel;
  struct sdfVector4_t v21;
  SBTLUNIT_WORK *v23;
  SBTLUNIT_WORK *v24;
  f32 v25;
  f32 v26;
  s32 v27;
  sdfVector4_t *v29;
  s32 v30;
  sdfVector4_t *v31;
  struct sdfVector4_t v32;
  s32 v33;
  struct sdfVector4_t v34;
  dds3ModelHandle_t *v37;
  struct sdfVector4_t v38;
  s32 v40;
  struct sdfVector4_t v41;
  struct sdfVector4_t v42;
  struct sdfVector4_t v45;
  struct sdfVector4_t v46;

  z = raidouPos->z;
  y = raidouPos->y;
  x = raidouPos->x;
  Nakama = sBtlGetNakama(1);
  if (Nakama)
  {
    v8 = Nakama;
    Nakama->pos.x = x;
    Nakama->pos.y = y;
    Nakama->pos.z = z;
    if (r > -45.0 && r < 45.0)
    {
      v9 = -200.0;
LABEL_15:
      Nakama->pos.x = x + v9;
LABEL_16:
      FromEuler(0.0, r * 0.017453292, 0.0);
      p_rot = &v8->rot;
      v13 = (u8)byte_5755EF5;
      *p_rot = vct_A;
      if (v13)
        goto LABEL_20;
      goto LABEL_40;
      if (v27)
      {
LABEL_20:
        goto LABEL_21;
      }
LABEL_40:
LABEL_21:
      vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
      p_rot_p = &v8->rot_p;
      v16 = (u8)byte_5755EF5;
      v8->mv_rotbk = r;
      *p_rot_p = vct_A;
      pos = v8->pos;
      if (v16)
      {
        goto LABEL_25;
      }
      else
      {
        v41 = v8->pos;
        pos = v41;
LABEL_25:
        vct_A = pos;
        hModel = v8->hModel;
        goto LABEL_26;
      }
      v42 = pos;
      vct_A = v42;
      hModel = v8->hModel;
LABEL_26:
      mdlSetPosition(hModel);
      v21 = *p_rot;
      vct_A = v21;
      mdlSetRotate(v8->hModel);
      goto LABEL_29;
    }
    if (r >= -45.0 || r <= -135.0)
    {
      if (r <= 45.0 || r >= 135.0)
      {
        v9 = 200.0;
        goto LABEL_15;
      }
      v10 = 200.0;
    }
    else
    {
      v10 = -200.0;
    }
    Nakama->pos.z = z + v10;
    goto LABEL_16;
  }
LABEL_29:
  v23 = sBtlGetNakama(0);
  if (v23)
  {
    v24 = v23;
    v23->pos.x = x;
    v23->pos.y = y;
    v23->pos.z = z;
    if (r > -45.0 && r < 45.0)
    {
      v25 = 200.0;
LABEL_54:
      v23->pos.x = x + v25;
LABEL_55:
      FromEuler(0.0, r * 0.017453292, 0.0);
      v29 = &v24->rot;
      v30 = (u8)byte_5755EF5;
      *v29 = vct_A;
      if (v30)
        goto LABEL_59;
      goto LABEL_71;
      if (v40)
      {
LABEL_59:
        goto LABEL_60;
      }
LABEL_71:
LABEL_60:
      vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
      v31 = &v24->rot_p;
      v32 = vct_A;
      v33 = (u8)byte_5755EF5;
      v24->mv_rotbk = r;
      *v31 = v32;
      v34 = v24->pos;
      if (v33)
      {
        goto LABEL_64;
      }
      else
      {
        v45 = v24->pos;
        v34 = v45;
LABEL_64:
        vct_A = v34;
        v37 = v24->hModel;
        goto LABEL_65;
      }
      v46 = v34;
      vct_A = v46;
      v37 = v24->hModel;
LABEL_65:
      mdlSetPosition(v37);
      v38 = *v29;
      vct_A = v38;
      mdlSetRotate(v24->hModel);
      return;
    }
    if (r >= -45.0 || r <= -135.0)
    {
      if (r <= 45.0 || r >= 135.0)
      {
        v25 = -200.0;
        goto LABEL_54;
      }
      v26 = -200.0;
    }
    else
    {
      v26 = 200.0;
    }
    v23->pos.z = z + v26;
    goto LABEL_55;
  }
}
