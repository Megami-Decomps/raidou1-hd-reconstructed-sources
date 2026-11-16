#include "types.h"
#include "SKLID.h"
#include "aw.h"
#include "aw_hitlight.h"
#include "dds3vrf.h"
#include "sbtl.h"
#include "sbtlmain.h"
#include "sbtlplayertbl.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sbtlvisual.h"

typedef struct AW_WORK_t AW_WORK_t;

static bool CalcPos_KudaSupport(AW_WORK_t *aWork);
static void SetVariation(AW_WORK_t *aWork, SKLID _skillid);

// 0x1e39d30
void Init(void) {
  ;
}

// 0x1e39d40
s32 Add(s32 _ListID, f32 _SX, f32 _SY, f32 _SZ, SKLID _skillid, s32 _prio) {
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v15;
  SBTLUNIT_WORK *v16;
  f32 v17;
  f32 v19;
  f32 v20;
  f32 v21;
  AW_WORK_t *AW_ID;
  AW_WORK_t *v24;
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  Il2CppObject *v32;
  AW_Func v33;
  AW_Func v34;
  s32 Idx;
  AW_WORK_t *AW;
  void *transform;
  void *v38;
  void *gameObject;
  void *Component_object;
  char *v43;
  s32 StepIntA;
  bool v45;
  s32 v46;
  long f64 v49;
  u16 major;
  s32 minor;
  f32 cylinder;
  f32 RotToDir;
  s64 FromX;
  s64 FromZ;
  sdfVector3_t v56;
  sdfQuaternion_t v57;

  FromX = 0;
  FromZ = 0;
  if (skillid != 1300)
    goto LABEL_12;
  UnitMng = wk->UnitMng;
  v15 = sBtlSearchUnit_ID(UnitMng, ListID);
  if (v15)
  {
    v16 = v15;
    SX = 400.0;
    SZ = -1200.0;
    v17 = -400.0;
    switch (v15->para->devilid)
    {
      case 0x102:
      case 0x13A:
        SX = 0.0;
        v17 = -500.0;
        SZ = -1000.0;
        goto LABEL_15;
      case 0x103:
      case 0x138:
      case 0x139:
        SX = 0.0;
        v17 = -500.0;
        SZ = -1200.0;
        goto LABEL_16;
      case 0x104:
      case 0x13B:
LABEL_15:
        goto LABEL_16;
      default:
        FromX = 0;
        FromZ = 0;
        sBtlGetUnitHelperPos(v16, 0);
        sub_1B335A0(&FromX, 0, v49);
        major = v16->major;
        minor = v16->minor;
        cylinder = sBtlGetVisualData(major, minor)->nml->cylinder;
        RotToDir = sBtlGetRotToDir(v16->rot);
        sBtlGetMoveXZ(*(f32 *)&FromX, *(f32 *)&FromZ, RotToDir, cylinder, &FromX, &FromZ);
        SX = *(f32 *)&FromX;
        v17 = SY;
        SZ = *(f32 *)&FromZ;
        goto LABEL_16;
    }
  }
LABEL_12:
  v17 = SY;
LABEL_16:
  v19 = SX / -100.0;
  v20 = v17 / -100.0;
  v21 = SZ / -100.0;
  AW_ID = GetAW_ID(402);
  if (AW_ID)
  {
    v24 = AW_ID;
    switch (prio)
    {
      case 0:
        if (AW_ID->StepIntA)
          goto LABEL_43;
        goto LABEL_40;
      case 1:
        StepIntA = AW_ID->StepIntA;
        v45 = StepIntA == 1;
        if (StepIntA < 1)
          goto LABEL_41;
        goto LABEL_38;
      case 2:
        v46 = AW_ID->StepIntA;
        v45 = v46 == 2;
        if (v46 < 2)
          goto LABEL_41;
LABEL_38:
        if (!v45)
          goto LABEL_43;
LABEL_40:
        if (AW_ID->StepBoolA)
        {
LABEL_41:
          AW_ID->Unit_ListID = ListID;
          *(u64 *)&AW_ID->Step = 0;
          AW_ID->X = v19;
          AW_ID->Y = v20;
          AW_ID->Z = v21;
          AW_ID->StepIntA = prio;
          *(u16 *)&AW_ID->StepBoolA = 0;
          SetVariation(AW_ID, skillid);
          Calc(v24);
          Idx = v24->Idx;
        }
        else
        {
LABEL_43:
          Idx = -1;
        }
        break;
      case 3:
        if (AW_ID->StepIntA >= 4)
          goto LABEL_43;
        goto LABEL_41;
      default:
        goto LABEL_43;
    }
  }
  else
  {
    Instance = get_Instance(0);
    AwPrefab = GetAwPrefab(Instance, 9, 0);
    x = identityQuaternion.x;
    y = identityQuaternion.y;
    z = identityQuaternion.z;
    w = identityQuaternion.w;
    v56.x = v19;
    v56.y = v20;
    v56.z = v21;
    v57.x = x;
    v57.y = y;
    v57.z = z;
    v57.w = w;
    v32 = Instantiate_object__39504752(AwPrefab, v56, v57);
    v33 = Allocate(AW_Func);
    _ctor(v33, 0, Method_Project_AW_HitLight_Calc__, 0);
    v34 = Allocate(AW_Func);
    _ctor(v34, 0, Method_Project_AW_HitLight_Draw__, 0);
    Idx = Add(402, v19, v20, v21, v32, v33, v34, 1);
    AW = GetAW(Idx);
    transform = get_transform(AW->Obj, 0);
    v38 = Find(transform, "PointLight", 0);
    if (op_Inequality(v38, 0, 0))
    {
      gameObject = get_gameObject(v38, 0);
      if (op_Inequality(gameObject, 0, 0))
      {
        Component_object = GetComponent_object_(gameObject);
        if (op_Inequality(Component_object, 0, 0))
        {
          AW->ComLight = Component_object;
        }
      }
    }
    AW->Unit_ListID = ListID;
    AW->StepIntA = prio;
    *(u16 *)&AW->StepBoolA = 0;
    SetVariation(AW, skillid);
    Calc(AW);
    v43 = "AW_HitLight";
    AW->DbgStr = "AW_HitLight";
  }
  return Idx;
}

// 0x1e3b240
s32 Add_Fld(f32 _SX, f32 _SY, f32 _SZ) {
  f32 v7;
  f32 v8;
  f32 v9;
  AW_WORK_t *AW_ID;
  AW_WORK_t *v11;
  s32 v12;
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  Il2CppObject *v20;
  AW_Func v21;
  AW_Func v22;
  AW_WORK_t *AW;
  void *transform;
  void *v25;
  void *gameObject;
  void *Component_object;
  void *v28;
  char *v30;
  void *ComLight;
  sdfVector3_t v34;
  sdfColor_t v35;
  sdfColor_t v36;
  sdfQuaternion_t v37;

  v7 = SX / -100.0;
  v8 = SY / -100.0;
  v9 = SZ / -100.0;
  AW_ID = GetAW_ID(402);
  if (AW_ID)
  {
    v11 = AW_ID;
    if (AW_ID->StepIntA || !AW_ID->StepBoolA)
    {
      return -1;
    }
    else
    {
      v36.r = 1.0;
      v36.g = 0.9;
      v36.b = 0.8;
      ComLight = AW_ID->ComLight;
      v36.a = 1.0;
      *(u64 *)&v11->Step = 0;
      v11->X = v7;
      v11->Y = v8;
      v11->Z = v9;
      v11->StepIntA = 0;
      v11->StepBoolA = 0;
      set_color(ComLight, v36, 0);
      set_range(v11->ComLight, 6.0, 0);
      *(u64 *)&v11->StepFloatA = 0x41A0000041200000LL;
      Calc(v11);
      return v11->Idx;
    }
  }
  else
  {
    Instance = get_Instance(0);
    AwPrefab = GetAwPrefab(Instance, 9, 0);
    x = identityQuaternion.x;
    y = identityQuaternion.y;
    z = identityQuaternion.z;
    w = identityQuaternion.w;
    v34.x = v7;
    v34.y = v8;
    v34.z = v9;
    v37.x = x;
    v37.y = y;
    v37.z = z;
    v37.w = w;
    v20 = Instantiate_object__39504752(AwPrefab, v34, v37);
    v21 = Allocate(AW_Func);
    _ctor(v21, 0, Method_Project_AW_HitLight_Calc__, 0);
    v22 = Allocate(AW_Func);
    _ctor(v22, 0, Method_Project_AW_HitLight_Draw__, 0);
    v12 = Add(402, v7, v8, v9, v20, v21, v22, 1);
    AW = GetAW(v12);
    transform = get_transform(AW->Obj, 0);
    v25 = Find(transform, "PointLight", 0);
    if (op_Inequality(v25, 0, 0))
    {
      gameObject = get_gameObject(v25, 0);
      if (op_Inequality(gameObject, 0, 0))
      {
        Component_object = GetComponent_object_(gameObject);
        if (op_Inequality(Component_object, 0, 0))
        {
          AW->ComLight = Component_object;
        }
      }
    }
    v35.r = 1.0;
    v35.g = 0.9;
    v35.b = 0.8;
    v28 = AW->ComLight;
    v35.a = 1.0;
    AW->StepIntA = 0;
    AW->StepBoolA = 0;
    set_color(v28, v35, 0);
    set_range(AW->ComLight, 6.0, 0);
    *(u64 *)&AW->StepFloatA = 0x41A0000041200000LL;
    Calc(AW);
    v30 = "AW_HitLight_Fld";
    AW->DbgStr = "AW_HitLight_Fld";
  }
  return v12;
}

// 0x1e3b630
s32 Add_Huuma(f32 _SX, f32 _SY, f32 _SZ) {
  f32 v7;
  f32 v8;
  f32 v9;
  AW_WORK_t *AW_ID;
  AW_WORK_t *v11;
  void *ComLight;
  s32 v14;
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  Il2CppObject *v22;
  AW_Func v23;
  AW_Func v24;
  AW_WORK_t *AW;
  void *transform;
  void *v27;
  void *gameObject;
  void *Component_object;
  void *v30;
  char *v32;
  sdfVector3_t v34;
  sdfColor_t v35;
  sdfColor_t v36;
  sdfQuaternion_t v37;

  v7 = SX / -100.0;
  v8 = SY / -100.0;
  v9 = SZ / -100.0;
  AW_ID = GetAW_ID(402);
  if (AW_ID)
  {
    v35.g = 1.0;
    v11 = AW_ID;
    *(u64 *)&AW_ID->Step = 10;
    v35.r = 0.4;
    v35.b = 0.6;
    AW_ID->X = v7;
    AW_ID->Y = v8;
    AW_ID->Z = v9;
    AW_ID->StepIntA = 0;
    ComLight = AW_ID->ComLight;
    v35.a = 1.0;
    v11->StepBoolA = 0;
    set_color(ComLight, v35, 0);
    set_range(v11->ComLight, 6.0, 0);
    v11->StepFloatC = 0.0;
    *(u64 *)&v11->StepFloatA = 0x4270000041400000LL;
    Calc(v11);
    return v11->Idx;
  }
  else
  {
    Instance = get_Instance(0);
    AwPrefab = GetAwPrefab(Instance, 9, 0);
    x = identityQuaternion.x;
    y = identityQuaternion.y;
    z = identityQuaternion.z;
    w = identityQuaternion.w;
    v34.x = v7;
    v34.y = v8;
    v34.z = v9;
    v37.x = x;
    v37.y = y;
    v37.z = z;
    v37.w = w;
    v22 = Instantiate_object__39504752(AwPrefab, v34, v37);
    v23 = Allocate(AW_Func);
    _ctor(v23, 0, Method_Project_AW_HitLight_Calc__, 0);
    v24 = Allocate(AW_Func);
    _ctor(v24, 0, Method_Project_AW_HitLight_Draw__, 0);
    v14 = Add(402, v7, v8, v9, v22, v23, v24, 1);
    AW = GetAW(v14);
    transform = get_transform(AW->Obj, 0);
    v27 = Find(transform, "PointLight", 0);
    if (op_Inequality(v27, 0, 0))
    {
      gameObject = get_gameObject(v27, 0);
      if (op_Inequality(gameObject, 0, 0))
      {
        Component_object = GetComponent_object_(gameObject);
        if (op_Inequality(Component_object, 0, 0))
        {
          AW->ComLight = Component_object;
        }
      }
    }
    v36.g = 1.0;
    v30 = AW->ComLight;
    AW->Step = 10;
    v36.r = 0.4;
    v36.b = 0.6;
    v36.a = 1.0;
    AW->StepIntA = 0;
    AW->StepBoolA = 0;
    set_color(v30, v36, 0);
    set_range(AW->ComLight, 6.0, 0);
    AW->StepFloatC = 0.0;
    *(u64 *)&AW->StepFloatA = 0x4270000041400000LL;
    Calc(AW);
    v32 = "AW_HitLight_Huuma";
    AW->DbgStr = "AW_HitLight_Huuma";
  }
  return v14;
}

// 0x1e3ba20
void EndLoop(void) {
  AW_WORK_t *AW_ID;

  AW_ID = GetAW_ID(402);
  if (!AW_ID)
    return;
  if (AW_ID->Step == 10)
    *(u64 *)&AW_ID->Step = 11;
}

// 0x1e3bac0
s32 Add_KudaSupport(f32 _SX, f32 _SY, f32 _SZ) {
  f32 v7;
  f32 v8;
  f32 v9;
  AW_WORK_t *AW_ID;
  AW_WORK_t *v11;
  void *ComLight;
  s32 v14;
  void *Instance;
  Il2CppObject *AwPrefab;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  Il2CppObject *v22;
  AW_Func v23;
  AW_Func v24;
  AW_WORK_t *AW;
  void *transform;
  void *v27;
  void *gameObject;
  void *Component_object;
  void *v30;
  char *v32;
  sdfVector3_t v34;
  sdfColor_t v35;
  sdfColor_t v36;
  sdfQuaternion_t v37;

  v7 = SX / -100.0;
  v8 = SY / -100.0;
  v9 = SZ / -100.0;
  AW_ID = GetAW_ID(402);
  if (AW_ID)
  {
    v35.g = 1.0;
    v11 = AW_ID;
    *(u64 *)&AW_ID->Step = 20;
    AW_ID->X = v7;
    AW_ID->Y = v8;
    AW_ID->StepIntA = 4;
    v35.r = 0.7;
    v35.b = 0.8;
    AW_ID->Z = v9;
    ComLight = AW_ID->ComLight;
    v35.a = 1.0;
    v11->StepBoolA = 0;
    set_color(ComLight, v35, 0);
    set_range(v11->ComLight, 2.0, 0);
    set_intensity(v11->ComLight, 0.0, 0);
    v11->StepFloatC = 0.0;
    *(u64 *)&v11->StepFloatA = 0x4220000040800000LL;
    Calc(v11);
    return v11->Idx;
  }
  else
  {
    Instance = get_Instance(0);
    AwPrefab = GetAwPrefab(Instance, 9, 0);
    x = identityQuaternion.x;
    y = identityQuaternion.y;
    z = identityQuaternion.z;
    w = identityQuaternion.w;
    v34.x = v7;
    v34.y = v8;
    v34.z = v9;
    v37.x = x;
    v37.y = y;
    v37.z = z;
    v37.w = w;
    v22 = Instantiate_object__39504752(AwPrefab, v34, v37);
    v23 = Allocate(AW_Func);
    _ctor(v23, 0, Method_Project_AW_HitLight_Calc__, 0);
    v24 = Allocate(AW_Func);
    _ctor(v24, 0, Method_Project_AW_HitLight_Draw__, 0);
    v14 = Add(402, v7, v8, v9, v22, v23, v24, 1);
    AW = GetAW(v14);
    transform = get_transform(AW->Obj, 0);
    v27 = Find(transform, "PointLight", 0);
    if (op_Inequality(v27, 0, 0))
    {
      gameObject = get_gameObject(v27, 0);
      if (op_Inequality(gameObject, 0, 0))
      {
        Component_object = GetComponent_object_(gameObject);
        if (op_Inequality(Component_object, 0, 0))
        {
          AW->ComLight = Component_object;
        }
      }
    }
    v36.g = 1.0;
    v30 = AW->ComLight;
    AW->Step = 20;
    AW->StepIntA = 4;
    v36.r = 0.7;
    v36.b = 0.8;
    v36.a = 1.0;
    AW->StepBoolA = 0;
    set_color(v30, v36, 0);
    set_range(AW->ComLight, 2.0, 0);
    set_intensity(AW->ComLight, 0.0, 0);
    AW->StepFloatC = 0.0;
    *(u64 *)&AW->StepFloatA = 0x4220000040800000LL;
    Calc(AW);
    v32 = "AW_HitLight_KudaSupport";
    AW->DbgStr = "AW_HitLight_KudaSupport";
  }
  return v14;
}

// 0x1e3bee0
static bool CalcPos_KudaSupport(AW_WORK_t *aWork) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v7;
  f32 v10;
  f32 v11;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 RotToDir;
  f32 Dir180;
  sdfVector4_t v19;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v7 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (!v7)
    return v7 != 0;
  v10 = (f32)(v7->pos.y / -100.0) + 1.3;
  v11 = v7->pos.z / -100.0;
  aWork->X = v7->pos.x / -100.0;
  aWork->Y = v10;
  aWork->Z = v11;
  x = v7->rot.x;
  y = v7->rot.y;
  z = v7->rot.z;
  w = v7->rot.w;
  v19.x = x;
  v19.y = y;
  v19.z = z;
  v19.w = w;
  RotToDir = sBtlGetRotToDir(v19);
  Dir180 = sBtlGetDir180(RotToDir);
  aWork->Dir = Dir180;
  sBtlGetMoveXZ(aWork->X, aWork->Z, Dir180, 0.3, &aWork->X, &aWork->Z);
  return v7 != 0;
}

// 0x1e3a380
static void SetVariation(AW_WORK_t *aWork, SKLID _skillid) {
  void *ComLight;
  void *v9;
  s32 SkillATRB;
  s32 v12;
  s32 encountno;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v19;
  s32 targetID;
  SBTLUNIT_WORK *v21;
  SBTLUNIT_LISTWORK *v23;
  SBTLUNIT_WORK *v24;
  void *v25;
  f32 v26;
  u32 v31;
  SBATTLE_WORK *v32;
  s32 v33;
  SBTLUNIT_LISTWORK *v34;
  s32 v35;
  SBTLUNIT_WORK *v36;
  s32 v37;
  SBTLUNIT_WORK *v38;
  SBTLUNIT_LISTWORK *v40;
  SBTLUNIT_WORK *v41;
  void *v42;
  f32 v43;
  s32 devilid;
  s32 v45;
  sdfColor_t v46;
  sdfColor_t v47;
  sdfColor_t v48;
  sdfColor_t v49;
  sdfColor_t v50;
  sdfColor_t v51;
  sdfColor_t v52;
  sdfColor_t v53;
  sdfColor_t v54;
  sdfColor_t v55;
  sdfColor_t v56;

  ComLight = aWork->ComLight;
  if (op_Equality(ComLight, 0, 0))
  {
    aWork->Variation = 0;
    *(u64 *)&aWork->StepFloatA = 0x41A0000041200000LL;
    return;
  }
  if (skillid <= 1319)
  {
    switch (skillid)
    {
      case 1299:
        v46.b = 1.0;
        v46.r = 0.57;
        v46.g = 0.79;
        v9 = aWork->ComLight;
        v46.a = 1.0;
        goto LABEL_39;
      case 1300:
        v51.r = 1.0;
        v51.g = 0.8;
        v51.b = 0.6;
        v51.a = 1.0;
        set_color(aWork->ComLight, v51, 0);
        set_range(aWork->ComLight, 10.0, 0);
        *(u64 *)&aWork->StepFloatA = 0x4248000041700000LL;
        encountno = wk->encountno;
        if (encountno != 59)
        {
          encountno = wk->encountno;
          if (encountno != 60)
            return;
LABEL_80:
          set_range(aWork->ComLight, 30.0, 0);
          *(u64 *)&aWork->StepFloatA = 0x42A0000043FA0000LL;
          return;
        }
        UnitMng = wk->UnitMng;
        playerID = wk->playerID;
        v19 = sBtlSearchUnit_ID(UnitMng, playerID);
        targetID = v19->actaiwk->targetID;
        if (targetID == -1)
          return;
        v21 = v19;
        v23 = wk->UnitMng;
        v24 = sBtlSearchUnit_ID(v23, targetID);
        if (!v24)
          return;
        devilid = (u16)v24->para->devilid;
        if (devilid != 314 && devilid != 258)
          return;
        goto LABEL_80;
      case 1301:
        v9 = aWork->ComLight;
        v46.g = 1.0;
        v46.r = 0.4;
        v46.b = 0.6;
        v46.a = 1.0;
LABEL_39:
        set_color(v9, v46, 0);
        set_range(aWork->ComLight, 10.0, 0);
        *(u64 *)&aWork->StepFloatA = 0x4248000041700000LL;
        return;
      case 1318:
        goto LABEL_23;
      case 1319:
        v52.g = 1.0;
        v52.r = 0.77;
        v52.b = 0.8;
        v52.a = 1.0;
        set_color(aWork->ComLight, v52, 0);
        set_range(aWork->ComLight, 6.0, 0);
        *(u64 *)&aWork->StepFloatA = 0x4220000041700000LL;
        return;
      default:
        goto LABEL_15;
    }
  }
  switch (skillid)
  {
    case 1325:
      v49.g = 1.0;
      v49.r = 0.4;
      v49.b = 0.6;
      v49.a = 1.0;
      set_color(aWork->ComLight, v49, 0);
      set_range(aWork->ComLight, 12.0, 0);
      *(u64 *)&aWork->StepFloatA = 0x4220000041F00000LL;
      return;
    case 1329:
      v50.g = 1.0;
      v50.r = 0.4;
      v50.b = 0.6;
      v50.a = 1.0;
      set_color(aWork->ComLight, v50, 0);
      set_range(aWork->ComLight, 10.0, 0);
      *(u64 *)&aWork->StepFloatA = 0x4220000041A00000LL;
      return;
    case 1550:
LABEL_23:
      v48.g = 1.0;
      v48.r = 0.77;
      v48.b = 0.8;
      v48.a = 1.0;
      set_color(aWork->ComLight, v48, 0);
      set_range(aWork->ComLight, 10.0, 0);
      *(u64 *)&aWork->StepFloatA = 0x425C000041700000LL;
      return;
  }
LABEL_15:
  SkillATRB = sbtlplayertblGetSkillATRB(skillid);
  if ((u32)(skillid - 1472) >= 7)
    v12 = SkillATRB;
  else
    v12 = 8;
  aWork->Variation = v12;
  if (wk->battlemode == 1)
  {
    v47.r = 1.0;
    v47.g = 0.9;
    v47.b = 0.8;
    v47.a = 1.0;
    set_color(aWork->ComLight, v47, 0);
    set_range(aWork->ComLight, 2.0, 0);
    *(u64 *)&aWork->StepFloatA = 0x41A0000040000000LL;
    return;
  }
  switch (aWork->Variation)
  {
    case 0:
    case 8:
      v25 = aWork->ComLight;
      v53.g = 0.9;
      v26 = 0.8;
      goto LABEL_65;
    case 1:
      v54.b = 1.0;
      v54.r = 0.37;
      v54.g = 0.69;
      v54.a = 1.0;
      set_color(aWork->ComLight, v54, 0);
      set_range(aWork->ComLight, 6.0, 0);
      *(u64 *)&aWork->StepFloatA = 0x41A0000041200000LL;
      goto LABEL_51;
    case 2:
      v55.g = 1.0;
      v55.r = 0.4;
      v55.b = 0.6;
      v55.a = 1.0;
      set_color(aWork->ComLight, v55, 0);
      set_range(aWork->ComLight, 10.0, 0);
      *(u64 *)&aWork->StepFloatA = 0x41F0000041200000LL;
LABEL_51:
      v32 = wk;
      v33 = v32->encountno;
      if (v33 != 59)
      {
        if (!v31)
        {
          v33 = wk->encountno;
        }
        if (v33 == 60)
          goto LABEL_85;
        return;
      }
      if (!v31)
      {
        v32 = wk;
      }
      v34 = v32->UnitMng;
      v35 = v32->playerID;
      v36 = sBtlSearchUnit_ID(v34, v35);
      v37 = v36->actaiwk->targetID;
      if (v37 == -1)
        return;
      v38 = v36;
      v40 = wk->UnitMng;
      v41 = sBtlSearchUnit_ID(v40, v37);
      if (!v41)
        return;
      v45 = (u16)v41->para->devilid;
      if (v45 == 314 || v45 == 258)
      {
LABEL_85:
        set_range(aWork->ComLight, 12.0, 0);
        aWork->StepFloatA = 50.0;
        return;
      }
      break;
    case 3:
      v56.r = 1.0;
      v56.g = 0.8;
      v56.b = 0.6;
      v56.a = 1.0;
      set_color(aWork->ComLight, v56, 0);
      v42 = aWork->ComLight;
      v43 = 8.0;
      goto LABEL_71;
    case 4:
      v25 = aWork->ComLight;
      v53.g = 0.4;
      v26 = 0.2;
LABEL_65:
      v53.r = 1.0;
      v53.b = v26;
      v53.a = 1.0;
      goto LABEL_70;
    case 5:
      v25 = aWork->ComLight;
      v53.r = 0.2;
      v53.g = 0.7;
      goto LABEL_68;
    case 6:
      v25 = aWork->ComLight;
      v53.r = 0.2;
      v53.g = 0.5;
LABEL_68:
      v53.b = 1.0;
      v53.a = 1.0;
      goto LABEL_70;
    case 7:
      v25 = aWork->ComLight;
      v53.g = 1.0;
      v53.r = 0.2;
      v53.b = 0.5;
      v53.a = 1.0;
      goto LABEL_70;
    default:
      v25 = aWork->ComLight;
      v53.r = 0.8;
      v53.a = 1.0;
      v53.g = 0.8;
      v53.b = 0.8;
LABEL_70:
      set_color(v25, v53, 0);
      v42 = aWork->ComLight;
      v43 = 6.0;
LABEL_71:
      set_range(v42, v43, 0);
      *(u64 *)&aWork->StepFloatA = 0x41A0000041200000LL;
      return;
  }
}

// 0x1e3c080
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 1);
}

// 0x1e3ac90
void Calc(AW_WORK_t *aWork) {
  s32 Step;
  s32 Idx;
  void *ComLight;
  f32 v7;
  f32 v8;
  f32 StepFloatA;
  void *v10;
  f32 StepFloatB;
  void *v13;
  f32 v14;
  f32 StepFloatC;
  f32 v16;
  void *v17;
  f32 v18;
  f32 v19;
  f32 v20;
  void *v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v25;
  bool v26;
  f32 v27;
  f32 v28;
  s64 v29;
  f32 v30;
  f32 v31;
  void *v32;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 VRF_DeltaTime_local;
  f32 v41;
  f32 v42;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 v46;

  Step = aWork->Step;
  if (Step > 1)
  {
    switch (Step)
    {
      case 10:
        ComLight = aWork->ComLight;
        if (op_Inequality(ComLight, 0, 0))
        {
          v7 = sub_188E3D0(aWork->StepTime * 16.0);
          v8 = v7 + v7;
          StepFloatA = aWork->StepFloatA;
          v10 = aWork->ComLight;
          aWork->StepFloatC = v8;
          set_intensity(v10, v8 + StepFloatA, 0);
        }
        aWork->StepTime = aWork->StepTime + VRF_DeltaTime;
        return;
      case 11:
        StepFloatB = aWork->StepFloatB;
        v13 = aWork->ComLight;
        v14 = StepFloatB * FPS60;
        if (!op_Inequality(v13, 0, 0))
          goto LABEL_82;
        StepFloatC = aWork->StepFloatC;
        if (StepFloatC >= 0.0)
        {
          v16 = StepFloatC + -0.1;
          aWork->StepFloatC = v16;
          if (v16 >= 0.0)
            goto LABEL_73;
        }
        else
        {
          v16 = StepFloatC + 0.1;
          aWork->StepFloatC = v16;
          if (v16 <= 0.0)
            goto LABEL_73;
        }
        v16 = 0.0;
        aWork->StepFloatC = 0.0;
LABEL_73:
        v42 = 0.0;
        if (v14 != 0.0)
        {
          v43 = 1.0;
          v44 = aWork->StepTime / v14;
          if (v44 <= 1.0)
            v43 = aWork->StepTime / v14;
          v26 = v44 < 0.0;
          v42 = 0.0;
          if (!v26)
            v42 = v43;
        }
        if (v42 < 0.0)
          v42 = 0.0;
        v45 = aWork->StepFloatA + (f32)((f32)(0.0 - aWork->StepFloatA) * v42);
        set_intensity(aWork->ComLight, v16 + v45, 0);
        if (v45 < 1.0)
          aWork->StepBoolA = 0;
LABEL_82:
        v46 = aWork->StepTime + VRF_DeltaTime;
        aWork->StepTime = v46;
        if (v46 <= v14)
          return;
        v29 = 12;
        break;
      case 12:
      case 22:
        Idx = aWork->Idx;
        goto LABEL_15;
      case 20:
        CalcPos_KudaSupport(aWork);
        v17 = aWork->ComLight;
        if (op_Inequality(v17, 0, 0))
        {
          v18 = get_intensity(aWork->ComLight, 0) + 0.5;
          if (v18 >= aWork->StepFloatA)
          {
            v18 = aWork->StepFloatA;
            *(u64 *)&aWork->Step = 21;
          }
          set_intensity(aWork->ComLight, v18, 0);
        }
        return;
      case 21:
        CalcPos_KudaSupport(aWork);
        v19 = aWork->StepFloatB;
        v20 = FPS60;
        v21 = aWork->ComLight;
        v22 = v19 * v20;
        if (op_Inequality(v21, 0, 0))
        {
          v23 = 0.0;
          if (v22 != 0.0)
          {
            v24 = 1.0;
            v25 = aWork->StepTime / v22;
            if (v25 <= 1.0)
              v24 = aWork->StepTime / v22;
            v26 = v25 < 0.0;
            v23 = 0.0;
            if (!v26)
              v23 = v24;
          }
          if (v23 < 0.0)
            v23 = 0.0;
          v27 = aWork->StepFloatA + (f32)((f32)(0.0 - aWork->StepFloatA) * v23);
          set_intensity(aWork->ComLight, v27, 0);
          if (v27 < 1.0)
            aWork->StepBoolA = 0;
        }
        v28 = aWork->StepTime + VRF_DeltaTime;
        aWork->StepTime = v28;
        if (v28 <= v22)
          return;
        v29 = 22;
        goto LABEL_84;
      default:
        return;
    }
    goto LABEL_84;
  }
  if (Step)
  {
    if (Step == 1)
    {
      Idx = aWork->Idx;
LABEL_15:
      DelAW(Idx, 1);
    }
  }
  else if (!sBtlIsSetsumaPadStop())
  {
    if (sBtlIsEnemyLastDeadStop())
    {
      aWork->StepBoolB = 1;
    }
    else
    {
      v30 = aWork->StepFloatB;
      v31 = FPS60;
      v32 = aWork->ComLight;
      v33 = v30 * v31;
      if (op_Inequality(v32, 0, 0))
      {
        v34 = 0.0;
        if (v33 != 0.0)
        {
          v35 = aWork->StepTime / v33;
          v36 = v35 <= 1.0 ? aWork->StepTime / v33 : 1.0;
          v26 = v35 < 0.0;
          v34 = 0.0;
          if (!v26)
            v34 = v36;
        }
        if (v34 < 0.0)
          v34 = 0.0;
        v37 = aWork->StepFloatA;
        v38 = v37 + (f32)((f32)(0.0 - v37) * v34);
        if (aWork->StepBoolB)
          v39 = v38 * 1.3;
        else
          v39 = v37 + (f32)((f32)(0.0 - v37) * v34);
        set_intensity(aWork->ComLight, v39, 0);
        if (v38 < 1.0)
          aWork->StepBoolA = 0;
      }
      VRF_DeltaTime_local = VRF_DeltaTime;
      if (aWork->StepBoolB)
        VRF_DeltaTime_local = VRF_DeltaTime_local * 0.2;
      v41 = aWork->StepTime + VRF_DeltaTime_local;
      aWork->StepTime = v41;
      if (v41 > v33)
      {
        v29 = 1;
LABEL_84:
        *(u64 *)&aWork->Step = v29;
      }
    }
  }
}

// 0x1e3c0f0
void Draw(AW_WORK_t *aWork) {
  void *transform;

  transform = get_transform(aWork->Obj, 0);
  set_localPosition(transform, *(sdfVector3_t *)&aWork->X, 0);
}
