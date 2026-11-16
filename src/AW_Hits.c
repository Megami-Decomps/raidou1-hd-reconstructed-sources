#include "types.h"
#include "SKLID.h"
#include "aw.h"
#include "aw_hits.h"
#include "aw_hitsscore.h"
#include "bsflow.h"
#include "dds3kerneldraw.h"
#include "sbtl.h"
#include "sbtlevent.h"
#include "sbtlmain.h"
#include "sbtlplayer.h"
#include "sbtlplayer_spirit.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

static bool CalcPos(AW_WORK_t *aWork);

// 0x1e3c140
void Init(void) {
  ;
}

// 0x1e3c150
s32 Add(s32 _ListID, SKLID _SkillID, f32 _X, f32 _Y, f32 _Z, f32 _Dir, f32 _Scale) {
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v19;
  s32 v20;
  SBTLUNIT_WORK *v22;
  s32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 RotToDir;
  s32 v29;
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  Il2CppObject *v37;
  AW_Func v38;
  AW_Func v39;
  AW_WORK_t *AW;
  float32x2_t *v41;
  s32 devilid;
  f32 v43;
  char *v44;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 w;
  f32 Scalea;
  sdfVector3_t v51;
  sdfVector4_t v52;
  sdfVector4_t v53;
  sdfQuaternion_t v54;

  UnitMng = wk->UnitMng;
  v19 = sBtlSearchUnit_ID(UnitMng, ListID);
  if (!v19)
    return -1;
  v22 = v19;
  Scalea = Scale;
  if (SkillID > 157)
  {
    if ((u32)SkillID > 0x2A2)
    {
      if ((u32)SkillID <= 0x542)
      {
        v23 = 72;
        switch (SkillID)
        {
          case 1296:
          case 1297:
            v23 = 85;
            goto LABEL_57;
          case 1298:
          case 1302:
          case 1307:
          case 1309:
          case 1318:
          case 1338:
            goto LABEL_56;
          case 1299:
          case 1301:
          case 1319:
            goto LABEL_46;
          case 1300:
            v46 = v19->rot.x;
            v47 = v19->rot.y;
            v48 = v19->rot.z;
            w = v19->rot.w;
            v53.x = v46;
            v53.y = v47;
            v53.z = v48;
            v53.w = w;
            RotToDir = sBtlGetRotToDir(v53) + 180.0;
            goto LABEL_49;
          case 1303:
          case 1304:
          case 1305:
          case 1306:
          case 1308:
            goto LABEL_41;
          case 1310:
          case 1315:
            v23 = 71;
            goto LABEL_57;
          case 1311:
            goto LABEL_57;
          case 1312:
            v23 = 73;
            goto LABEL_57;
          case 1313:
            v23 = 74;
            goto LABEL_57;
          case 1314:
            if ((u32)sub_1E446B0(0) == 1)
              v23 = 74;
            else
              v23 = 75;
            goto LABEL_57;
          case 1316:
          case 1317:
            v23 = 77;
            goto LABEL_57;
          case 1320:
            dds3PostHitFlashStart(0x28u);
            goto LABEL_28;
          case 1321:
            dds3PostHitFlashStart(0x28u);
            v23 = 83;
            goto LABEL_57;
          case 1322:
            dds3PostHitFlashStart(0x28u);
            v23 = 87;
            goto LABEL_57;
          case 1323:
          case 1330:
          case 1336:
            v23 = 78;
            goto LABEL_57;
          case 1324:
          case 1331:
            v23 = 79;
            goto LABEL_57;
          case 1325:
          case 1329:
          case 1340:
          case 1344:
            goto LABEL_22;
          case 1326:
          case 1327:
          case 1328:
          case 1332:
          case 1335:
          case 1341:
          case 1343:
LABEL_28:
            v23 = 81;
            goto LABEL_57;
          case 1333:
            v23 = 88;
            goto LABEL_57;
          case 1334:
            v23 = 89;
            goto LABEL_57;
          case 1337:
            v23 = 83;
            goto LABEL_57;
          case 1339:
          case 1345:
            if ((u32)sub_1E446B0(0) == 1)
              v23 = 87;
            else
              v23 = 86;
            goto LABEL_57;
          case 1342:
          case 1346:
            v23 = 87;
            goto LABEL_57;
          default:
            if ((u32)(SkillID - 690) > 0xB || ((1 << (SkillID + 78)) & 0xA67) == 0)
              goto LABEL_56;
            AW_HitsAdd_Go(ListID, v20, X, Y, Z, Dir, Scale);
            return -1;
        }
      }
      if (SkillID > 1475)
      {
        switch (SkillID)
        {
          case 1476:
            v23 = 115;
            goto LABEL_57;
          case 1550:
LABEL_46:
            v24 = v19->rot.x;
            v25 = v19->rot.y;
            v26 = v19->rot.z;
            v27 = v19->rot.w;
            v52.x = v24;
            v52.y = v25;
            v52.z = v26;
            v52.w = v27;
            RotToDir = sBtlGetRotToDir(v52);
LABEL_49:
            Dir = sBtlGet360(RotToDir);
            v23 = 90;
            goto LABEL_57;
          case 1558:
            goto LABEL_41;
        }
      }
      goto LABEL_56;
    }
    if ((u32)SkillID <= 0x1A3)
    {
      if (SkillID == 191)
      {
        v23 = 123;
        goto LABEL_57;
      }
      if (SkillID != 419)
        goto LABEL_56;
    }
    else if (SkillID != 463)
    {
      if (SkillID != 674)
        goto LABEL_56;
LABEL_22:
      v23 = 84;
      goto LABEL_57;
    }
    v23 = 151;
    goto LABEL_57;
  }
  if (SkillID <= 55)
  {
    if (SkillID <= 23)
    {
      if (SkillID == 8)
      {
        v23 = 125;
        goto LABEL_57;
      }
      if (SkillID != 23)
        goto LABEL_56;
      v23 = 127;
    }
    else
    {
      if (SkillID == 39)
      {
        v23 = 129;
        goto LABEL_57;
      }
      if (SkillID != 55)
        goto LABEL_56;
      v23 = 131;
    }
  }
  else if ((u32)SkillID <= 0x90)
  {
    if (SkillID == 65)
    {
LABEL_41:
      v23 = 70;
      goto LABEL_57;
    }
    if (SkillID != 144)
    {
LABEL_56:
      v23 = 82;
      goto LABEL_57;
    }
    v23 = 76;
  }
  else
  {
    if (SkillID == 156)
    {
      v23 = 136;
      goto LABEL_57;
    }
    if (SkillID != 157)
      goto LABEL_56;
    v23 = sub_1905740(6, 0) + 70;
  }
LABEL_57:
  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, v23, 0);
  v33 = identityQuaternion.x;
  v34 = identityQuaternion.y;
  v36 = identityQuaternion.z;
  v35 = identityQuaternion.w;
  v51.x = 0.0;
  v51.y = 0.0;
  v51.z = 0.0;
  v54.x = v33;
  v54.y = v34;
  v54.z = v36;
  v54.w = v35;
  v37 = Instantiate_object__39504752(AwPrefab, v51, v54);
  v38 = Allocate(AW_Func);
  _ctor(v38, 0, Method_Project_AW_Hits_Calc__, 0);
  v39 = Allocate(AW_Func);
  _ctor(v39, 0, Method_Project_AW_Hits_Draw__, 0);
  v29 = Add(240, 0.0, 0.0, 0.0, v37, v38, v39, 1);
  Set_HDEff(v29, 1, -1);
  AW = GetAW(v29);
  AW->Unit_ListID = ListID;
  AW->HDEff_SkillID = SkillID;
  v41 = AW;
  AW->HDEff_PosLink = 1;
  AW->Scale = Scalea;
  *(u64 *)&AW->HDEff_Speed = 0x3F8000003F800000LL;
  AW->X = X / -100.0;
  AW->Y = Y / -100.0;
  AW->Z = Z / -100.0;
  v41[13].n64_f32[0] = sBtlGetDir180(Dir);
  devilid = v22->para->devilid;
  v43 = v22->pos.z / 100.0;
  v41[27].n64_u64[0] = vadd_f32(v41[10], vdiv_f32(*(float32x2_t *)&v22->pos.x, vdup_n_s32(0x42C80000u))).n64_u64[0];
  v41[28].n64_f32[0] = v41[11].n64_f32[0] + v43;
  if ((u32)(devilid - 258) < 3 || (devilid & 0xFFFFFFFC) == 0x138)
    v41[49].n64_u32[0] = -1;
  v44 = "AW_Hits";
  v41[52].n64_u64[0] = "AW_Hits";
  return v29;
}

// 0x1e3ca60
s32 Add_Score(s32 _ListID, SKLID _SkillID, f32 _X, f32 _Y, f32 _Z, f32 _Dir, f32 _Scale) {
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v18;
  s32 v19;
  SBTLUNIT_WORK *v20;
  sdatUnitWork_t *para;
  f32 v22;
  s32 v23;
  s32 devilid;
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 w;
  Il2CppObject *v32;
  AW_Func v33;
  AW_Func v34;
  AW_WORK_t *AW;
  float32x2_t *v36;
  s32 v37;
  f32 v38;
  char *v39;
  f32 dir;
  sdfVector3_t v42;
  sdfQuaternion_t v43;

  UnitMng = wk->UnitMng;
  v18 = sBtlSearchUnit_ID(UnitMng, ListID);
  v19 = -1;
  if (!v18)
    return v19;
  v20 = v18;
  dir = Dir;
  switch (SkillID)
  {
    case 690:
      para = v18->para;
      v22 = 0.0;
      v23 = 125;
      goto LABEL_15;
    case 691:
    case 695:
    case 699:
      para = v18->para;
      v22 = 0.0;
      v23 = 129;
      goto LABEL_15;
    case 692:
      para = v18->para;
      v22 = 0.0;
      v23 = 131;
      goto LABEL_15;
    case 696:
      para = v18->para;
      v22 = 0.0;
      v23 = 127;
      goto LABEL_15;
    case 701:
      para = v18->para;
      v22 = 0.0;
      v23 = 145;
LABEL_15:
      devilid = para->devilid;
      if ((u32)(devilid - 258) >= 3 && (devilid & 0xFFFFFFFC) != 0x138)
        v22 = v18->pos.y;
      Instance = get_Instance(0);
      AwPrefab = GetAwPrefab(Instance, v23, 0);
      v28 = identityQuaternion.x;
      v29 = identityQuaternion.y;
      v30 = identityQuaternion.z;
      w = identityQuaternion.w;
      v42.x = 0.0;
      v42.y = 0.0;
      v42.z = 0.0;
      v43.x = v28;
      v43.y = v29;
      v43.z = v30;
      v43.w = w;
      v32 = Instantiate_object__39504752(AwPrefab, v42, v43);
      v33 = Allocate(AW_Func);
      _ctor(v33, 0, Method_Project_AW_Hits_Calc__, 0);
      v34 = Allocate(AW_Func);
      _ctor(v34, 0, Method_Project_AW_Hits_Draw__, 0);
      v19 = Add(240, 0.0, 0.0, 0.0, v32, v33, v34, 1);
      Set_HDEff(v19, 1, -1);
      AW = GetAW(v19);
      AW->Scale = Scale;
      AW->Unit_ListID = ListID;
      AW->HDEff_SkillID = SkillID;
      v36 = AW;
      AW->HDEff_PosLink = 1;
      *(u64 *)&AW->HDEff_Speed = 0x3F8000003F800000LL;
      AW->X = X / -100.0;
      AW->Y = v22 / -100.0;
      AW->Z = Z / -100.0;
      v36[13].n64_f32[0] = sBtlGetDir180(dir);
      v37 = v20->para->devilid;
      v38 = v20->pos.z / 100.0;
      v36[27].n64_u64[0] = vadd_f32(v36[10], vdiv_f32(*(float32x2_t *)&v20->pos.x, vdup_n_s32(0x42C80000u))).n64_u64[0];
      v36[28].n64_f32[0] = v36[11].n64_f32[0] + v38;
      if ((u32)(v37 - 258) < 3 || (v37 & 0xFFFFFFFC) == 0x138)
        v36[49].n64_u32[0] = -1;
      v39 = "AW_Hits";
      v36[52].n64_u64[0] = "AW_Hits";
      break;
    default:
      return v19;
  }
  return v19;
}

// 0x1e3ced0
s32 Add_Hajiki(s32 _ListID, f32 _X, f32 _Y, f32 _Z, f32 _Dir) {
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v13;
  SBTLUNIT_WORK *v14;
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 w;
  Il2CppObject *v22;
  AW_Func v23;
  AW_Func v24;
  s32 v25;
  AW_WORK_t *AW;
  f32 v27;
  AW_WORK_t *v28;
  f32 v29;
  char *v30;
  sdfVector3_t v34;
  sdfVector4_t v35;
  sdfQuaternion_t v36;

  UnitMng = wk->UnitMng;
  v13 = sBtlSearchUnit_ID(UnitMng, ListID);
  if (!v13)
    return -1;
  v14 = v13;
  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 26, 0);
  v18 = identityQuaternion.x;
  v19 = identityQuaternion.y;
  v20 = identityQuaternion.z;
  w = identityQuaternion.w;
  v34.z = Z;
  v36.x = v18;
  v36.y = v19;
  v36.z = v20;
  v36.w = w;
  v34.x = X;
  v34.y = Y;
  v22 = Instantiate_object__39504752(AwPrefab, v34, v36);
  v23 = Allocate(AW_Func);
  _ctor(v23, 0, Method_Project_AW_Hits_Calc__, 0);
  v24 = Allocate(AW_Func);
  _ctor(v24, 0, Method_Project_AW_Hits_Draw__, 0);
  v25 = Add(240, X, Y, Z, v22, v23, v24, 1);
  Set_HDEff(v25, 1, -1);
  AW = GetAW(v25);
  *(u64 *)&AW->HDEff_Speed = 0x3F8000003F800000LL;
  AW->Scale = 1.0;
  AW->Z = Z;
  AW->Dir = Dir;
  v27 = v14->pos.z;
  v28 = AW;
  AW->Unit_ListID = ListID;
  AW->HDEff_SkillID = 0;
  AW->HDEff_PosLink = 1;
  AW->X = X;
  AW->Y = Y;
  *(float32x2_t *)&AW->VelocityX = vadd_f32(vdiv_f32(*(float32x2_t *)&v14->pos.x, vdup_n_s32(0x42C80000u)), (float32x2_t)__PAIR64__(LODWORD(Y), LODWORD(X)));
  AW->VelocityZ = (f32)(v27 / 100.0) + Z;
  v29 = Z * -100.0;
  v35.w = 0.0;
  v35.x = X * -100.0;
  v35.y = Y * -100.0;
  v35.z = v29;
  sBtlPlay3DSE(0x5010018u, v35);
  v30 = "AW_Hits_Hajiki";
  v28->DbgStr = "AW_Hits_Hajiki";
  return v25;
}

// 0x1e3d280
static bool CalcPos(AW_WORK_t *aWork) {
  s32 Unit_ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v6;
  f32 z;
  f32 VelocityZ;

  Unit_ListID = aWork->Unit_ListID;
  if (Unit_ListID != -1)
  {
    UnitMng = wk->UnitMng;
    v6 = sBtlSearchUnit_ID(UnitMng, Unit_ListID);
    if (!v6)
      return (char)v6;
    if ((v6->vstatus & 2) != 0)
    {
      aWork->HDEff_PosLink = 0;
      LOBYTE(v6) = 1;
      return (char)v6;
    }
    if (aWork->HDEff_PosLink)
    {
      z = v6->pos.z;
      VelocityZ = aWork->VelocityZ;
      *(float32x2_t *)&aWork->X = vadd_f32(*(float32x2_t *)&aWork->VelocityX, vdiv_f32(*(float32x2_t *)&v6->pos.x, vdup_n_s32(0xC2C80000)));
      aWork->Z = VelocityZ + (f32)(z / -100.0);
    }
  }
  LOBYTE(v6) = 1;
  return (char)v6;
}

// 0x1e3d3d0
void Calc(AW_WORK_t *aWork) {
  __int128 v7;
  Il2CppObject *current;
  s32 PlayerID;
  SBTLUNIT_WORK *PlayerUnit;
  s32 Idx;
  SBTLUNIT_WORK *v14;
  f32 HDEff_SimSpeed;
  void *ParticleSystemList;
  __int128 v18;
  f32 v19;
  System_Collections_Generic_List_Enumerator_T__o v20;
  void *m_ParticleSystem;
  System_Collections_Generic_List_Enumerator_T__o v22;
  f32 MSlow_Speed;
  UnityEngine_ParticleSystem_MainModule_o v24;

  MSlow_Speed = 0.0;
  memset(&v22, 0, sizeof(v22));
  m_ParticleSystem = 0;
  if (wk->BtlEnd_Boss_Sprit)
    goto LABEL_38;
  if ((wk->status4 & 0x800000) != 0)
    goto LABEL_38;
  if (sBtlCheckSetsuma())
    goto LABEL_38;
  if (sBtlPlayerCheckRSpirit())
    goto LABEL_38;
  if (!sBtlIsHuuma() && !sBtlIsSetsumaPadStop() && !sBtlIsEnemyLastDeadStop())
  {
    if (wk->enemy_zenmetu)
    {
      if ((u32)(aWork->HDEff_SkillID - 690) > 0xB || ((1 << (LOBYTE(aWork->HDEff_SkillID) + 78)) & 0xA67) == 0)
      {
        goto LABEL_35;
      }
    }
    else if (!IsAction(20) && !IsAction(21))
    {
      if (!sBtlChkEvent())
      {
LABEL_35:
        if (ChkPause(aWork))
          return;
      }
    }
  }
LABEL_38:
  _GetEnumerator(&v20, aWork->ParticleSystemList);
  v22._current = v20._current;
  v7 = *(_OWORD *)&v20._list;
  v20._list = 0;
  *(u64 *)&v20._index = &v22;
  *(_OWORD *)&v22._list = v7;
  do
  {
    if (!_MoveNext(&v22))
    {
      _Dispose(&v22);
      Idx = aWork->Idx;
      DelAW(Idx, 1);
      return;
    }
    current = v22._current;
  }
  while (op_Equality(current, 0, 0) || !IsAlive_61441520(current, 0));
  _Dispose(&v22);
  if (!CalcPos(aWork))
    return;
  PlayerID = sBtlGetPlayerID();
  PlayerUnit = sBtlGetPlayerUnit(PlayerID);
  if (!PlayerUnit)
    return;
  v14 = PlayerUnit;
  HDEff_SimSpeed = aWork->HDEff_SimSpeed;
  if (!sBtlChkSlowMotion(PlayerUnit, &MSlow_Speed))
  {
    if (HDEff_SimSpeed == aWork->HDEff_SimSpeed)
      return;
    goto LABEL_66;
  }
  if (wk->enemy_zenmetu && (u32)(aWork->HDEff_SkillID - 690) <= 0xB && ((1 << (LOBYTE(aWork->HDEff_SkillID) + 78)) & 0xA67) != 0 && MSlow_Speed < 0.4)
  {
    MSlow_Speed = 0.4;
  }
  HDEff_SimSpeed = aWork->HDEff_Speed * MSlow_Speed;
  if (HDEff_SimSpeed != aWork->HDEff_SimSpeed)
  {
LABEL_66:
    ParticleSystemList = aWork->ParticleSystemList;
    aWork->HDEff_SimSpeed = HDEff_SimSpeed;
    _GetEnumerator(&v20, ParticleSystemList);
    v22._current = v20._current;
    v18 = *(_OWORD *)&v20._list;
    v20._list = 0;
    *(u64 *)&v20._index = &v22;
    *(_OWORD *)&v22._list = v18;
    while (_MoveNext(&v22))
    {
      v24.m_ParticleSystem = get_main(v22._current, 0).m_ParticleSystem;
      v19 = aWork->HDEff_SimSpeed;
      m_ParticleSystem = v24.m_ParticleSystem;
      set_simulationSpeed((UnityEngine_ParticleSystem_MainModule_o)&m_ParticleSystem, v19, 0);
    }
    _Dispose(&v22);
  }
}

// 0x1e3d9a0
void Draw(AW_WORK_t *aWork) {
  void *transform;
  void *v4;
  void *v5;
  sdfVector3_t v6;
  sdfVector3_t v7;

  transform = get_transform(aWork->Obj, 0);
  set_localPosition(transform, *(sdfVector3_t *)&aWork->X, 0);
  v4 = get_transform(aWork->Obj, 0);
  v6.y = aWork->Dir;
  v6.x = 0.0;
  v6.z = 0.0;
  set_eulerAngles(v4, v6, 0);
  v5 = get_transform(aWork->Obj, 0);
  v7.x = aWork->Scale;
  v7.y = v7.x;
  v7.z = v7.x;
  set_localScale(v5, v7, 0);
}

// 0x1e3da20
s32 Add_Fld(f32 _X, f32 _Y, f32 _Z, f32 _Dir, f32 _Scale) {
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 v13;
  f32 v14;
  f32 w;
  f32 v16;
  Il2CppObject *v17;
  AW_Func v18;
  AW_Func v19;
  s32 v20;
  AW_WORK_t *AW;
  f32 Dir180;
  char *v23;
  sdfVector3_t v26;
  sdfQuaternion_t v27;

  Instance = get_Instance(0);
  AwPrefab = GetAwPrefab(Instance, 82, 0);
  v13 = identityQuaternion.x;
  v14 = identityQuaternion.y;
  v16 = identityQuaternion.z;
  w = identityQuaternion.w;
  v26.x = 0.0;
  v26.y = 0.0;
  v26.z = 0.0;
  v27.x = v13;
  v27.y = v14;
  v27.z = v16;
  v27.w = w;
  v17 = Instantiate_object__39504752(AwPrefab, v26, v27);
  v18 = Allocate(AW_Func);
  _ctor(v18, 0, Method_Project_AW_Hits_Calc_Fld__, 0);
  v19 = Allocate(AW_Func);
  _ctor(v19, 0, Method_Project_AW_Hits_Draw__, 0);
  v20 = Add(240, 0.0, 0.0, 0.0, v17, v18, v19, 1);
  Set_HDEff(v20, 1, -1);
  AW = GetAW(v20);
  AW->Scale = Scale;
  AW->X = X / -100.0;
  AW->Y = Y / -100.0;
  AW->Z = Z / -100.0;
  Dir180 = sBtlGetDir180(Dir);
  v23 = "AW_Hits_Fld";
  AW->Dir = Dir180;
  AW->DbgStr = v23;
  return v20;
}

// 0x1e3dcc0
void Calc_Fld(AW_WORK_t *aWork) {
  Il2CppObject *current;
  s32 Idx;
  System_Collections_Generic_List_Enumerator_T__o v5;

  memset(&v5, 0, sizeof(v5));
  _GetEnumerator(&v5, aWork->ParticleSystemList);
  while (_MoveNext(&v5))
  {
    current = v5._current;
    if (!op_Equality(current, 0, 0) && IsAlive_61441520(current, 0))
    {
      _Dispose(&v5);
      return;
    }
  }
  _Dispose(&v5);
  Idx = aWork->Idx;
  DelAW(Idx, 1);
}
