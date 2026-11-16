#include "types.h"
#include "basic.h"
#include "dat.h"
#include "dds3adminiprocess.h"
#include "dds3basic.h"
#include "dds3cameraobjectbasic.h"
#include "dds3effectobjectbasic.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3matterobjectbasic.h"
#include "dds3moverbasic.h"
#include "dds3objectbase.h"
#include "dds3pathbasic.h"
#include "dds3scenebasic.h"
#include "dds3unitobjectbasic.h"
#include "dds3worldbasic.h"
#include "egl.h"
#include "eve.h"
#include "evt.h"
#include "evtcommand.h"
#include "evtcutin.h"
#include "evtmoon.h"
#include "evtpicture.h"
#include "evtpmv.h"
#include "evtsky.h"
#include "evtsound.h"
#include "evtviewer.h"
#include "file.h"
#include "fld.h"
#include "itf.h"
#include "localize.h"
#include "mdl.h"
#include "mdl_check.h"
#include "sbtlcontinue.h"
#include "sbtlmain.h"
#include "scr.h"
#include "sdf_vu0.h"
#include "sdfmodel.h"
#include "sdfquat.h"
#include "sdfsound.h"
#include "slmain.h"

#define KUTIMOTION_GROUP 2

typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct evtUnitHandle_t evtUnitHandle_t;
typedef struct fileHandle_t fileHandle_t;

static evtUnitHandle_t *KutiModel;
static s32 CallKutiMotionUnitID;
static s32 s_stat;
static fileHandle_t *s_fh;

static void KutiFunction(void);
static f32 sub_r360_lr(f32 a, f32 b);
static void CallBattleSub(s32 encno, s32 eventno);
static void CallBattleSub2(s32 encno);
static dds3Basic_t *GetPathBasic(void);

// macros
// 0x1a02a40: s32 MODEL_PLAYER(void)
static inline s32 MODEL_PLAYER(void) {
  dds3Basic_t *ActiveScene;
  dds3Basic_t *ActiveUnit;
  s32 serialID;

  ActiveScene = dds3GetActiveScene();
  ActiveUnit = dds3SceneBasicGetActiveUnit(ActiveScene);
  if (!ActiveUnit)
  {
    serialID = -1;
    goto LABEL_7;
  }
  serialID = ActiveUnit->serialID;
LABEL_7:
  scrSetIntReturnValue(serialID);
  return 1;
}

// 0x1a02b60: s32 MODEL_PLAYER2(void)
static inline s32 MODEL_PLAYER2(void) {
  s32 IntPara;
  dds3Basic_t *PlayersBasic;
  s32 serialID;

  IntPara = scrGetIntPara(0);
  PlayersBasic = mapGetPlayersBasic(IntPara);
  if (!PlayersBasic)
  {
    serialID = -1;
    goto LABEL_9;
  }
  serialID = PlayersBasic->serialID;
LABEL_9:
  scrSetIntReturnValue(serialID);
  return 1;
}

// 0x1a02c50: s32 MODEL_PLAYERS_ONOFF(void)
static inline s32 MODEL_PLAYERS_ONOFF(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  mapSetPlayersVisible(IntPara, v2, v3);
  return 1;
}

// 0x1a02d20: s32 MODEL_DSP(void)
static inline s32 MODEL_DSP(void) {
  u16 IntPara;
  s32 v2;
  dds3ModelResrc_t *v3;
  s32 Unit;
  s32 v6;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = mdlPrepare(IntPara, v2, 0);
  if (READY(v3))
  {
    Unit = evtLoadUnit(IntPara, v2);
    v6 = 1;
    goto LABEL_18;
  }
  Unit = 0;
  v6 = 0;
LABEL_18:
  scrSetIntReturnValue(Unit);
  return v6;
}

// 0x1a02ea0: s32 MODEL_DSP_BUSTUP(void)
static inline s32 MODEL_DSP_BUSTUP(void) {
  u16 IntPara;
  s32 v2;
  s32 v3;
  dds3ModelResrc_t *v4;
  s32 UnitBustUp;
  s32 v7;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  dds3SetBistaBustUp();
  v4 = mdlPrepare(IntPara, v2, 0);
  if (READY(v4))
  {
    UnitBustUp = evtLoadUnitBustUp(IntPara, v2, v3);
    v7 = 1;
    goto LABEL_20;
  }
  UnitBustUp = 0;
  v7 = 0;
LABEL_20:
  scrSetIntReturnValue(UnitBustUp);
  return v7;
}

// 0x1a03060: s32 MODEL_BE(void)
#define MODEL_BE() (1)

// 0x1a03070: s32 MODEL_POS(void)
static inline s32 MODEL_POS(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;
  s32 RaidouSerialID;
  s32 AiboSerialID;
  s32 v7;
  s32 v8;
  s32 NakamaSerialID;
  s32 v10;
  s32 v11;
  s32 v12;
  s32 AiboSerialID2;
  u32 v14;
  s32 v16;
  evtUnitHandle_t *UnitHandle;
  dds3Basic_t *Owner;
  dds3PoseSet_t *poseset;
  f32 x;
  f32 z;
  s32 Light;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(0);
  v3 = scrGetIntPara(1);
  evtSetUnitPos(v2, v3);
  if (dds3SearchProcessName("fldProcSequence"))
  {
    RaidouSerialID = mapGetRaidouSerialID();
    if (IntPara != RaidouSerialID)
    {
      AiboSerialID2 = mapGetAiboSerialID2();
      if (IntPara == AiboSerialID2)
      {
        if (!v14)
        mapAibouBackUpPosReset();
        mapAiboOikakeBuffReset();
        mapAiboWakeUp(0);
        goto LABEL_51;
      }
      if (!v14)
      if (IntPara == mapGetNakamaSerialID2())
      {
        mapNakamaBackUpPosReset();
        mapNakamaOikakeBuffReset();
        v12 = 0;
        goto LABEL_48;
      }
LABEL_49:
LABEL_51:
      v16 = scrGetIntPara(0);
      UnitHandle = evtGetUnitHandle(v16);
      if (UnitHandle && UnitHandle->MapLightUse)
      {
        Owner = UnitHandle->Owner;
        poseset = Owner->poseset;
        x = poseset->pos.x;
        z = poseset->pos.z;
        Light = mapGetLight(x, z);
        mapUnitSetLight(Owner, Light, 0);
      }
      return 1;
    }
    mapRaidouBackUpPosReset();
    AiboSerialID = mapGetAiboSerialID();
    if (AiboSerialID != -1)
    {
      v7 = AiboSerialID;
      v8 = scrGetIntPara(1);
      evtSetUnitPos(v7, v8);
      mapAiboOikakeBuffReset();
      mapAiboWakeUp(1);
    }
    NakamaSerialID = mapGetNakamaSerialID();
    if (NakamaSerialID != -1)
    {
      v10 = NakamaSerialID;
      v11 = scrGetIntPara(1);
      evtSetUnitPos(v10, v11);
      mapNakamaOikakeBuffReset();
      if (!fldGb->nakamaMode)
      {
        v12 = 1;
LABEL_48:
        mapNakamaWakeUp(v12);
        goto LABEL_49;
      }
      goto LABEL_49;
    }
    mapNakamaOikakeBuffReset2();
    goto LABEL_51;
  }
  return 1;
}

// 0x1a03480: s32 MODEL_POS_CUSTOM(void)
static inline s32 MODEL_POS_CUSTOM(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;
  f32 FloatPara;
  f32 v5;
  f32 v6;
  s32 RaidouSerialID;
  s32 AiboSerialID;
  s32 v10;
  s32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  s32 NakamaSerialID;
  s32 v16;
  s32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  s32 v21;
  s32 AiboSerialID2;
  u32 v23;
  s32 v25;
  evtUnitHandle_t *UnitHandle;
  dds3Basic_t *Owner;
  dds3PoseSet_t *poseset;
  f32 x;
  f32 z;
  s32 Light;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(0);
  v3 = scrGetIntPara(1);
  FloatPara = scrGetFloatPara(2);
  v5 = scrGetFloatPara(3);
  v6 = scrGetFloatPara(4);
  evtSetUnitPosCustom(v2, v3, FloatPara, v5, v6);
  if (dds3SearchProcessName("fldProcSequence"))
  {
    RaidouSerialID = mapGetRaidouSerialID();
    if (IntPara == RaidouSerialID)
    {
      mapRaidouBackUpPosReset();
      AiboSerialID = mapGetAiboSerialID();
      if (AiboSerialID != -1)
      {
        v10 = AiboSerialID;
        v11 = scrGetIntPara(1);
        v12 = scrGetFloatPara(2);
        v13 = scrGetFloatPara(3);
        v14 = scrGetFloatPara(4);
        evtSetUnitPosCustom(v10, v11, v12, v13, v14);
        mapAiboOikakeBuffReset();
        mapAiboWakeUp(1);
      }
      NakamaSerialID = mapGetNakamaSerialID();
      if (NakamaSerialID != -1)
      {
        v16 = NakamaSerialID;
        v17 = scrGetIntPara(1);
        v18 = scrGetFloatPara(2);
        v19 = scrGetFloatPara(3);
        v20 = scrGetFloatPara(4);
        evtSetUnitPosCustom(v16, v17, v18, v19, v20);
        mapNakamaOikakeBuffReset();
        v21 = 1;
        goto LABEL_59;
      }
      mapNakamaOikakeBuffReset2();
      goto LABEL_42;
    }
    AiboSerialID2 = mapGetAiboSerialID2();
    if (IntPara == AiboSerialID2)
    {
      if (!v23)
      mapAibouBackUpPosReset();
      mapAiboOikakeBuffReset();
      mapAiboWakeUp(0);
      goto LABEL_42;
    }
    if (v23)
    {
      if (IntPara != mapGetNakamaSerialID2())
        goto LABEL_41;
    }
    else
    {
      if (IntPara != mapGetNakamaSerialID2())
      {
LABEL_41:
LABEL_42:
        v25 = scrGetIntPara(0);
        UnitHandle = evtGetUnitHandle(v25);
        if (UnitHandle && UnitHandle->MapLightUse)
        {
          Owner = UnitHandle->Owner;
          poseset = Owner->poseset;
          x = poseset->pos.x;
          z = poseset->pos.z;
          Light = mapGetLight(x, z);
          mapUnitSetLight(Owner, Light, 0);
        }
        return 1;
      }
    }
    mapNakamaBackUpPosReset();
    mapNakamaOikakeBuffReset();
    v21 = 0;
LABEL_59:
    mapNakamaWakeUp(v21);
    goto LABEL_42;
  }
  return 1;
}

// 0x1a03930: s32 MODEL_SHADOW_ON(void)
static inline s32 MODEL_SHADOW_ON(void) {
  u32 IntPara;
  dds3Basic_t *v4;
  dds3Basic_t *pBasic;

  v4 = 0;
  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  v4 = dds3SceneBasicSearch(pBasic, IntPara, 5u);
  if (v4)
  {
    dds3ObjectBaseOnFlag(v4, 0x400u);
    dds3ObjectBaseOffFlag(v4, 0x200u);
  }
  return 1;
}

// 0x1a03a60: s32 MODEL_SHADOW_ON2(void)
static inline s32 MODEL_SHADOW_ON2(void) {
  u32 IntPara;
  dds3Basic_t *v4;
  dds3Basic_t *pBasic;

  v4 = 0;
  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  v4 = dds3SceneBasicSearch(pBasic, IntPara, 5u);
  if (v4)
  {
    dds3ObjectBaseOffFlag(v4, 0x400u);
    dds3ObjectBaseOnFlag(v4, 0x200u);
  }
  return 1;
}

// 0x1a03b90: s32 MODEL_SHADOW_OFF(void)
static inline s32 MODEL_SHADOW_OFF(void) {
  u32 IntPara;
  dds3Basic_t *v4;
  dds3Basic_t *pBasic;

  v4 = 0;
  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  v4 = dds3SceneBasicSearch(pBasic, IntPara, 5u);
  if (v4)
  {
    dds3ObjectBaseOffFlag(v4, 0x400u);
    dds3ObjectBaseOffFlag(v4, 0x200u);
  }
  return 1;
}

// 0x1a03cc0: s32 MODEL_KUBI_ON(void)
static inline s32 MODEL_KUBI_ON(void) {
  u32 IntPara;
  dds3Basic_t *v3;
  dds3Basic_t *v5;
  s32 v6;
  dds3Basic_t *pBasic;

  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  v3 = dds3SceneBasicSearch(pBasic, IntPara, 5u);
  if (!v3)
    return 1;
  v5 = v3;
  v6 = scrGetIntPara(1);
  dds3UnitObjectBasicKubiOn(v5, v6);
  return 1;
}

// 0x1a03e50: s32 MODEL_KUBI_OFF(void)
static inline s32 MODEL_KUBI_OFF(void) {
  u32 IntPara;
  dds3Basic_t *v3;
  dds3Basic_t *v5;
  dds3Basic_t *pBasic;

  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  v3 = dds3SceneBasicSearch(pBasic, IntPara, 5u);
  if (!v3)
    return 1;
  v5 = v3;
  dds3UnitObjectBasicKubiOff(v5);
  return 1;
}

// 0x1a03fc0: s32 MODEL_LOD_CHG(void)
static inline s32 MODEL_LOD_CHG(void) {
  scrGetIntPara(1);
  return 1;
}

// 0x1a04020: s32 MODEL_POS_XYZ(void)
static inline s32 MODEL_POS_XYZ(void) {
  f32 w;
  u32 IntPara;
  f32 FloatPara;
  f32 v5;
  f32 v6;
  dds3Basic_t *v8;
  dds3Basic_t *pBasic;
  sdfVector4_t v10;

  v8 = 0;
  w = zeroVector.w;
  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  v8 = dds3SceneBasicSearch(pBasic, IntPara, 5u);
  if (v8)
  {
    FloatPara = scrGetFloatPara(1);
    v5 = scrGetFloatPara(2);
    v6 = scrGetFloatPara(3);
    v10.x = FloatPara;
    v10.y = v5;
    v10.z = v6;
    v10.w = w;
    dds3SetPosPoseSet(v8, v10);
  }
  return 1;
}

// 0x1a04200: s32 MODEL_DISP_POS_XYZ(void)
static inline s32 MODEL_DISP_POS_XYZ(void) {
  f32 w;
  s32 IntPara;
  u32 v3;
  f32 FloatPara;
  f32 v6;
  f32 v7;
  f32 *p_x;
  dds3PoseSet_t *poseset;
  sdfVector4_t *p_pos2;
  dds3Basic_t *v13;
  dds3Basic_t *pBasic;
  sdfVector4_t v15;

  v13 = 0;
  w = zeroVector.w;
  IntPara = scrGetIntPara(0);
  if (IntPara == -1)
    return 1;
  v3 = IntPara;
  pBasic = dds3GetActiveScene();
  v13 = dds3SceneBasicSearch(pBasic, v3, 5u);
  if (v13)
  {
    FloatPara = scrGetFloatPara(1);
    v6 = scrGetFloatPara(2);
    v7 = scrGetFloatPara(3);
    v15.x = FloatPara;
    v15.y = v6;
    v15.z = v7;
    v15.w = w;
    dds3SetPosPoseSet(v13, v15);
    p_x = &vf00.x;
    p_x[4] = FloatPara;
    p_x[5] = v6;
    p_x[6] = v7;
    p_x[7] = w;
    poseset = v13->poseset;
    p_pos2 = &poseset->pos2;
    *p_pos2 = vct_A;
    if (mapGetAiboSerialID2() != -1)
    {
      if (v3 == mapGetAiboSerialID2())
      {
        mapAibouBackUpPosReset();
        mapAiboOikakeBuffReset();
        mapAiboWakeUp(0);
        return 1;
      }
    }
    if (mapGetNakamaSerialID2() != -1)
    {
      if (v3 == mapGetNakamaSerialID2())
      {
        mapNakamaBackUpPosReset();
        mapNakamaOikakeBuffReset();
        mapNakamaWakeUp(0);
      }
    }
    return 1;
  }
  return 1;
}

// 0x1a045d0: s32 MODEL_ROT_XYZ(void)
static inline s32 MODEL_ROT_XYZ(void) {
  u32 IntPara;
  f32 v3;
  f32 FloatPara;
  f32 v6;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  dds3Basic_t *v16;
  dds3Basic_t *pBasic;
  sdfVector4_t v18;

  v16 = 0;
  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  v16 = dds3SceneBasicSearch(pBasic, IntPara, 5u);
  if (v16)
  {
    v3 = scrGetFloatPara(1) * 0.017453292;
    FloatPara = scrGetFloatPara(2);
    FromEuler(v3, FloatPara * 0.017453292, 0.0);
    vct_B = vct_A;
    v6 = scrGetFloatPara(3);
    FromEuler(0.0, 0.0, v6 * 0.017453292);
    Mult();
    p_x = &vf00.x;
    x = p_x[4];
    y = p_x[5];
    z = p_x[6];
    w = p_x[7];
    v18.x = x;
    v18.y = y;
    v18.z = z;
    v18.w = w;
    dds3SetRotPoseSet(v16, v18);
    return 1;
  }
  return 1;
}

// 0x1a048b0: s32 MODEL_SCL_XYZ(void)
static inline s32 MODEL_SCL_XYZ(void) {
  u32 IntPara;
  f32 FloatPara;
  f32 v4;
  f32 v5;
  dds3Basic_t *v7;
  dds3Basic_t *pBasic;
  sdfVector4_t v9;

  v7 = 0;
  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  v7 = dds3SceneBasicSearch(pBasic, IntPara, 5u);
  if (v7)
  {
    FloatPara = scrGetFloatPara(1);
    v4 = scrGetFloatPara(2);
    v5 = scrGetFloatPara(3);
    v9.w = 1.0;
    v9.x = FloatPara;
    v9.y = v4;
    v9.z = v5;
    dds3SetSclPoseSet(v7, v9);
  }
  return 1;
}

// 0x1a04a60: s32 MODEL_MOTION(void)
static inline s32 MODEL_MOTION(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  evtUnitHandle_t *v4;
  s32 v5;
  s32 v6;
  s32 v7;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  if (!UnitHandle)
    return 1;
  v4 = UnitHandle;
  v5 = scrGetIntPara(1);
  v6 = scrGetIntPara(2);
  v7 = scrGetIntPara(3);
  evtSetUnitMotion(v4, v5, v6, v7, 0, 0);
  return 1;
}

// 0x1a04bb0: s32 MODEL_MOTION2(void)
static inline s32 MODEL_MOTION2(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  dds3ModelHandle_t *Model;
  evtUnitHandle_t *v4;
  s32 v6;
  s32 v7;
  s32 v8;
  s32 v9;
  s32 v10;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  if (UnitHandle)
  {
    Model = UnitHandle->Model;
    v4 = UnitHandle;
    Model->motions[0]->isWaitMot = 0;
    v6 = scrGetIntPara(1);
    v7 = scrGetIntPara(2);
    v8 = scrGetIntPara(3);
    v9 = scrGetIntPara(4);
    evtSetUnitMotion(v4, v6, v7, v8, v9, 0);
    if (dds3SearchProcessName("fldProcSequence"))
    {
      v10 = scrGetIntPara(0);
      mapObjNpcKuseScriptStop(v10);
    }
  }
  return 1;
}

// 0x1a04d90: s32 MODEL_TIMELIMIT_LOOPMOTION2(void)
static inline s32 MODEL_TIMELIMIT_LOOPMOTION2(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  evtUnitHandle_t *v3;
  s32 v4;
  s32 v5;
  s32 v6;
  s32 v7;
  s32 v8;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  if (UnitHandle)
  {
    v3 = UnitHandle;
    v4 = scrGetIntPara(1);
    v5 = scrGetIntPara(2);
    v6 = scrGetIntPara(3);
    v7 = scrGetIntPara(4);
    evtSetUnitMotion(v3, v4, v5, v6, 4, v7);
    if (dds3SearchProcessName("fldProcSequence"))
    {
      v8 = scrGetIntPara(0);
      mapObjNpcKuseScriptStop(v8);
    }
  }
  return 1;
}

// 0x1a04f60: s32 MODEL_EXMOTION(void)
static inline s32 MODEL_EXMOTION(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  evtUnitHandle_t *v3;
  s32 v4;
  s32 v5;
  s32 v8;
  s32 v9;
  s32 v10;
  s32 v11;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  if (UnitHandle)
  {
    v3 = UnitHandle;
    v4 = scrGetIntPara(1);
    v5 = scrGetIntPara(2);
    if (v4 == 2 && v5 == 5)
    {
      goto LABEL_13;
    }
    else
    {
      v3->Model->motions[v4]->isWaitMot = 0;
      v8 = scrGetIntPara(3);
      v9 = scrGetIntPara(4);
      v10 = scrGetIntPara(5);
      evtSetUnitExMotion(v3, v4, v5, v8, v9, v10, 0);
LABEL_13:
      if (!dds3SearchProcessName("fldProcSequence"))
        return 1;
LABEL_21:
      v11 = scrGetIntPara(0);
      mapObjNpcKuseScriptStop(v11);
      return 1;
    }
    if (!dds3SearchProcessName("fldProcSequence"))
      return 1;
    goto LABEL_21;
  }
  return 1;
}

// 0x1a051b0: s32 MODEL_TIMELIMIT_LOOPMOTION(void)
static inline s32 MODEL_TIMELIMIT_LOOPMOTION(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  evtUnitHandle_t *v3;
  s32 v4;
  s32 v5;
  s32 v6;
  s32 v7;
  s32 v8;
  s32 v9;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  if (UnitHandle)
  {
    v3 = UnitHandle;
    v4 = scrGetIntPara(1);
    v5 = scrGetIntPara(2);
    v3->Model->motions[v4]->isWaitMot = 0;
    v6 = scrGetIntPara(3);
    v7 = scrGetIntPara(4);
    v8 = scrGetIntPara(5);
    evtSetUnitExMotion(v3, v4, v5, v6, v7, 4, v8);
    if (dds3SearchProcessName("fldProcSequence"))
    {
      v9 = scrGetIntPara(0);
      mapObjNpcKuseScriptStop(v9);
    }
  }
  return 1;
}

// 0x1a05aa0: s32 KUTISET(void)
static inline s32 KUTISET(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  evtUnitHandle_t *v4;
  s8 v5;
  s8 v6;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  if (!UnitHandle)
    return 1;
  v4 = UnitHandle;
  v5 = scrGetIntPara(1);
  v6 = scrGetIntPara(2);
  v4->KutiGroup = v5;
  v4->KutiMotion = v6;
  KutiModel = v4;
  scrGetMessageHandle();
  return 1;
}

// 0x1a05c00: s32 KUTI(void)
static inline s32 KUTI(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  evtUnitHandle_t *v4;
  s8 v5;
  s8 v6;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  if (!UnitHandle)
    return 1;
  v4 = UnitHandle;
  v5 = scrGetIntPara(1);
  v6 = scrGetIntPara(2);
  v4->KutiGroup = v5;
  v4->KutiMotion = v6;
  KutiModel = v4;
  scrGetMessageHandle();
  return 1;
}

// 0x1a05d60: s32 MODEL_WAIT(void)
static inline s32 MODEL_WAIT(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  evtUnitHandle_t *v3;
  s32 Stat;
  dds3ModelHandle_t *Model;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  if (!UnitHandle)
    return 1;
  v3 = UnitHandle;
  Stat = (u16)v3->Stat;
  if (!v3->Stat)
    return 1;
  if (Stat == 2 && v3->Frame >= 1)
  {
    Model = v3->Model;
    if (mdlChkMotionEnd(Model))
      return 1;
  }
  return 0;
}

// 0x1a05f20: s32 MODEL_WAIT_WAITMOTION(void)
static inline s32 MODEL_WAIT_WAITMOTION(void) {
  s32 IntPara;
  dds3ModelHandle_t *Model;
  Il2CppObject *v3;
  Il2CppObject *v4;
  char *v5;
  char *name;
  void *CurrentAnimatorClipInfo;
  void *clip;
  s32 v10;
  s16 data;

  IntPara = scrGetIntPara(0);
  Model = evtGetUnitHandle(IntPara)->Model;
  data = Model->motions[0]->userId;
  v3 = Box(s16, &data);
  v10 = scrGetIntPara(1);
  v4 = Box(s32, &v10);
  v5 = Format_54759776("anim{0:x1}{1:x2}", v3, v4, 0);
  name = "";
  if (GetCurrentAnimatorClipInfo(Model->modelRoot->modelObj->animator, 0, 0) && GetCurrentAnimatorClipInfo(Model->modelRoot->modelObj->animator, 0, 0)->max_length)
  {
    CurrentAnimatorClipInfo = GetCurrentAnimatorClipInfo(Model->modelRoot->modelObj->animator, 0, 0);
    clip = get_clip((UnityEngine_AnimatorClipInfo_o)CurrentAnimatorClipInfo, 0);
    name = get_name(clip, 0);
  }
  return Model->motions[0]->isWaitMot
      && op_Inequality(name, "", 0)
      && op_Equality(v5, name, 0);
}

// 0x1a06140: s32 MODEL_EXWAIT(void)
static inline s32 MODEL_EXWAIT(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  evtUnitHandle_t *v3;
  EVT_EXMOT *ExFlags;
  s32 v5;
  dds3ModelHandle_t *Model;
  s32 v7;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  if (!UnitHandle)
    return 1;
  v3 = UnitHandle;
  ExFlags = UnitHandle->ExFlags;
  v5 = 1;
  if ((ExFlags[scrGetIntPara(1)] & 1) != 0)
  {
    Model = v3->Model;
    v7 = scrGetIntPara(1);
    return mdlChkMotionEndEx(Model, v7);
  }
  return v5;
}

// 0x1a062a0: s32 MODEL_CLS(void)
static inline s32 MODEL_CLS(void) {
  u32 IntPara;
  dds3Basic_t *v3;
  dds3Basic_t *v5;
  void *workdata;
  Project_Basic_dds3Basic_t_WORK_c *klass;
  void *p_instance_size;
  dds3Basic_t *pBasic;

  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  v3 = dds3SceneBasicSearch(pBasic, IntPara, 5u);
  if (!v3)
    return 1;
  v5 = v3;
  workdata = v3->workdata;
  klass = workdata[2].klass;
  p_instance_size = &klass[1]._2.instance_size;
  DelMesh(p_instance_size);
  dds3SceneBasicDelete(v5);
  return 1;
}

// 0x1a064a0: s32 MODEL_MOVE(void)
static inline s32 MODEL_MOVE(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  evtUnitHandle_t *v3;
  s16 v4;
  s32 v5;
  s32 v6;
  s32 v7;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  if (UnitHandle)
  {
    v3 = UnitHandle;
    UnitHandle->Frame = 0;
    v4 = scrGetIntPara(2);
    v5 = scrGetIntPara(1);
    v6 = scrGetIntPara(3);
    v7 = scrGetIntPara(4);
    evtSetUnitMove2(v3, v4, v5, -1, v6, v7, 0, 0);
    if (scrGetIntPara(2) == 1)
    {
      evtCalcFrame_UnitMoveType0(v3);
    }
  }
  return 1;
}

// 0x1a06610: s32 MODEL_MOVE2(void)
static inline s32 MODEL_MOVE2(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  evtUnitHandle_t *v3;
  s32 v4;
  s32 v5;
  s32 v6;
  s32 v7;
  s32 v8;
  s32 v9;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  if (!UnitHandle)
    return 1;
  v3 = UnitHandle;
  UnitHandle->Frame = 0;
  v4 = scrGetIntPara(1);
  v5 = scrGetIntPara(5);
  v6 = scrGetIntPara(6);
  v7 = scrGetIntPara(2);
  v8 = scrGetIntPara(4);
  v9 = scrGetIntPara(3);
  evtSetUnitMove3(v3, v4, v5, v6, v7, v8, v9);
  return 1;
}

// 0x1a06780: s32 MODEL_MOVE_BUSTUP(void)
static inline s32 MODEL_MOVE_BUSTUP(void) {
  f32 w;
  s32 IntPara;
  s32 v3;
  evtUnitHandle_t *UnitHandle;
  evtUnitHandle_t *v5;
  dds3ModelHandle_t *Model;
  f32 x;
  f32 v12;
  s32 v13;
  f32 v14;
  f32 v15;
  f32 rate;
  f32 y;
  f32 z;
  sdfVector4_t v19;
  sdfVector4_t v20;

  w = zeroVector.w;
  IntPara = scrGetIntPara(0);
  v3 = scrGetIntPara(1);
  UnitHandle = evtGetUnitHandle(IntPara);
  if (!UnitHandle)
    return 1;
  v5 = UnitHandle;
  Model = UnitHandle->Model;
  mdlGetPosition(Model);
  goto LABEL_15;
LABEL_23:
  v12 = v5->MoveDefPos.x;
  v13 = v3 == 0;
  if (x <= 0.0)
  {
    if (v3)
      v14 = v12 + -150.0;
    else
      v14 = v5->MoveDefPos.x;
    if (v3)
      v15 = v5->MoveDefPos.x;
    else
      v15 = v12 + -150.0;
    rate = 0.0;
    if ((v5->Flag & 0x1000000) == 0)
      goto LABEL_40;
  }
  else
  {
    v13 = v3 != 0;
    if (v3)
      v14 = v5->MoveDefPos.x;
    else
      v14 = v12 + 150.0;
    if (v3)
      v15 = v12 + 150.0;
    else
      v15 = v5->MoveDefPos.x;
    rate = 0.0;
    if ((v5->Flag & 0x1000000) == 0)
      goto LABEL_40;
  }
  rate = (v5->MovePara1 / v5->MovePara2);
LABEL_40:
  y = vct_A.y;
  z = vct_A.z;
  v19.x = v14;
  v19.y = y;
  v19.z = z;
  v19.w = w;
  v20.x = v15;
  v20.y = y;
  v20.z = z;
  v20.w = w;
  evtSetUnitMoveBustup(v5, v19, v20, rate, -1, 30, v13);
  return 1;
LABEL_15:
  x = vct_A.x;
  if (x != 0.0)
    goto LABEL_23;
  LogWarning("バストアップ座標取得エラー", 0);
  return 0;
}

// 0x1a06a90: s32 MODEL_ZOOM_BUSTUP(void)
#define MODEL_ZOOM_BUSTUP() (1)

// 0x1a06aa0: s32 MODEL_LIGHT_BUSTUP(void)
static inline s32 MODEL_LIGHT_BUSTUP(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  evtSetLightBustup(IntPara, v2, v3, 0);
  return 1;
}

// 0x1a06b70: s32 MODEL_WAIT_EXMOT(void)
static inline s32 MODEL_WAIT_EXMOT(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  s16 *ExWaitMotion;
  s32 v5;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  if (!UnitHandle)
    return 1;
  ExWaitMotion = UnitHandle->ExWaitMotion;
  v5 = scrGetIntPara(1);
  ExWaitMotion[v5] = scrGetIntPara(2);
  return 1;
}

// 0x1a06c70: s32 MODEL_WAIT_EXHOKAN(void)
static inline s32 MODEL_WAIT_EXHOKAN(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  evtUnitHandle_t *v4;
  s16 *ExWaitBefore;
  s32 v6;
  s16 v7;
  char *v8;
  s16 *ExNowSmooth;
  s32 v10;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  if (!UnitHandle)
    return 1;
  v4 = UnitHandle;
  ExWaitBefore = UnitHandle->ExWaitBefore;
  v6 = scrGetIntPara(1);
  v7 = scrGetIntPara(2);
  v8 = (char *)ExWaitBefore + 2 * v6;
  ExNowSmooth = v4->ExNowSmooth;
  *((u16 *)v8 + 16) = v7;
  v10 = scrGetIntPara(1);
  ExNowSmooth[v10] = scrGetIntPara(3);
  return 1;
}

// 0x1a06da0: s32 MODEL_WAIT_MOT(void)
static inline s32 MODEL_WAIT_MOT(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  evtUnitHandle_t *v4;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  if (!UnitHandle)
    return 1;
  v4 = UnitHandle;
  v4->WaitMotion = scrGetIntPara(1);
  return 1;
}

// 0x1a06e90: s32 MODEL_WAIT_HOKAN(void)
static inline s32 MODEL_WAIT_HOKAN(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  evtUnitHandle_t *v4;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  if (!UnitHandle)
    return 1;
  v4 = UnitHandle;
  v4->WaitBefore = scrGetIntPara(1);
  v4->WaitSmooth = scrGetIntPara(2);
  return 1;
}

// 0x1a06f90: s32 MODEL_MOVE_MOT(void)
static inline s32 MODEL_MOVE_MOT(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  evtUnitHandle_t *v4;
  s32 v5;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  if (!UnitHandle)
    return 1;
  v4 = UnitHandle;
  v5 = scrGetIntPara(1);
  evtSetUnitMotion(v4, v5, 5, 7, 1, 0);
  return 1;
}

// 0x1a070b0: s32 MODEL_ROT(void)
static inline s32 MODEL_ROT(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  evtUnitHandle_t *v4;
  s32 v5;
  s32 v6;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  if (!UnitHandle)
    return 1;
  v4 = UnitHandle;
  UnitHandle->Frame = 0;
  v5 = scrGetIntPara(1);
  v6 = scrGetIntPara(2);
  evtSetUnitRot2(v4, v5, v6);
  return 1;
}

// 0x1a072b0: s32 MODEL_ROT_LOOKPOS(void)
static inline s32 MODEL_ROT_LOOKPOS(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  evtUnitHandle_t *v3;
  u32 v4;
  u32 v6;
  dds3Basic_t *v9;
  void *workdata;
  dds3Basic_t *v11;
  s64 v13;
  f32 v15;
  long f64 v16;
  f32 v17;
  f32 LookRotY;
  f32 v19;
  _BOOL4 v20;
  f32 v21;
  f32 v22;
  f32 v24;
  f32 v25;
  s32 v26;
  f32 v27;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  s32 v35;
  f32 v36;
  s32 v37;
  _BOOL4 v38;
  f32 v39;
  f32 v40;
  f32 v41;
  f32 v44;
  s32 v45;
  s32 v46;
  s32 v47;
  s32 v48;
  dds3Basic_t *v49;
  s32 serialID;
  dds3Basic_t *v52;
  dds3Basic_t *pBasic;
  sdfVector4_t v54;

  v52 = 0;
  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  if (!UnitHandle)
    return 1;
  v3 = UnitHandle;
  UnitHandle->Frame = 0;
  v4 = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  v52 = dds3SceneBasicSearch(pBasic, v4, 5u);
  if (v52)
  {
    v6 = scrGetIntPara(1);
    pBasic = dds3GetActiveScene();
    v9 = dds3SceneBasicSearch(pBasic, v6, 0x10u);
    if (!v9)
      return 1;
    workdata = v9->workdata;
    v11 = v9;
    dds3GetPosPoseSet(v52);
    if ((v3->LookRotFlag & 1) == 0)
    {
      dds3GetRotPoseSet(v52);
      v15 = EulerAngleAxisY();
      v3->LookRotFlag |= 1u;
      v3->LookRotY = v15 * -57.29578;
    }
    v16 = sub_18E6660(0, v13);
    v17 = *(f32 *)&v16 * 57.32484;
    LookRotY = v3->LookRotY;
    v19 = v17 + 360.0;
    v20 = LookRotY < 0.0;
    if (v17 < 0.0)
      v20 = 1;
    if (v20)
      LookRotY = LookRotY + 360.0;
    else
      v19 = v17;
    if (LookRotY == INFINITY)
      v21 = -128.0;
    else
      v21 = ((s32)LookRotY % 360);
    if (v19 == INFINITY)
      v22 = -128.0;
    else
      v22 = ((s32)v19 % 360);
    if ((f32)(v21 - v22) > 180.0 || (f32)(v21 - v22) < -180.0)
    {
      if (v21 >= v22)
      {
        v24 = (f32)(v22 + 360.0) - v21;
        if (v24 < -135.0)
          goto LABEL_59;
        goto LABEL_64;
      }
      v21 = v21 + 360.0;
    }
    v24 = v22 - v21;
    if (v24 < -135.0)
    {
LABEL_59:
      v25 = 135.0;
      *(f32 *)&v26 = -135.0;
      goto LABEL_66;
    }
LABEL_64:
    if (v24 <= 135.0)
      goto LABEL_67;
    v25 = -135.0;
    *(f32 *)&v26 = 135.0;
LABEL_66:
    v17 = v17 - (f32)(v24 + v25);
    v24 = *(f32 *)&v26;
LABEL_67:
    v27 = v17 + (f32)((f32)(v24 + v24) / -3.0);
    FromEuler(0.0, v27 * 0.017453292, 0.0);
    p_x = &vf00.x;
    x = p_x[4];
    y = p_x[5];
    z = p_x[6];
    w = p_x[7];
    v35 = scrGetIntPara(2);
    v36 = v3->LookRotY;
    if (v35 >= 100)
      v37 = 100;
    else
      v37 = v35;
    v38 = v27 < 0.0;
    v39 = v27 + 360.0;
    if (v36 < 0.0)
      v38 = 1;
    if (v38)
      v36 = v36 + 360.0;
    else
      v39 = v27;
    if (v36 == INFINITY)
      v40 = -128.0;
    else
      v40 = ((s32)v36 % 360);
    if (v39 == INFINITY)
      v41 = -128.0;
    else
      v41 = ((s32)v39 % 360);
    if ((f32)(v40 - v41) > 180.0 || (f32)(v40 - v41) < -180.0)
    {
      if (v40 >= v41)
        v41 = v41 + 360.0;
      else
        v40 = v40 + 360.0;
    }
    v44 = v41 - v40;
    if (v44 < 0.0)
      v44 = -v44;
    if (v44 > 90.0)
      v44 = 90.0;
    v45 = v44;
    if (v44 == INFINITY)
      v45 = 0x80000000;
    v46 = v45 * v37;
    if (v46 / 90 >= 100)
      v47 = 100;
    else
      v47 = v46 / 90;
    if (v46 <= 89)
      v48 = 1;
    else
      v48 = v47;
    v54.x = x;
    v54.y = y;
    v54.z = z;
    v54.w = w;
    evtSetUnitRot1(v3, v54, v48);
    v49 = v52;
    serialID = v11->serialID;
    dds3UnitObjectBasicKubiOn(v49, serialID);
    return 1;
  }
  return 1;
}

// 0x1a07a40: s32 MODEL_RET_LOOKPOS(void)
static inline s32 MODEL_RET_LOOKPOS(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  char LookRotFlag;
  evtUnitHandle_t *v4;
  u32 v5;
  f32 v7;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  s32 v15;
  f32 LookRotY;
  s32 v17;
  f32 v18;
  _BOOL4 v19;
  f32 v20;
  f32 v21;
  f32 v24;
  s32 v25;
  s32 v26;
  s32 v27;
  s32 v28;
  dds3Basic_t *v29;
  dds3Basic_t *v31;
  dds3Basic_t *pBasic;
  sdfVector4_t v33;

  v31 = 0;
  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  if (!UnitHandle)
    return 1;
  LookRotFlag = UnitHandle->LookRotFlag;
  v4 = UnitHandle;
  UnitHandle->Frame = 0;
  if ((LookRotFlag & 1) == 0)
    return 1;
  v5 = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  v31 = dds3SceneBasicSearch(pBasic, v5, 5u);
  if (v31)
  {
    dds3GetRotPoseSet(v31);
    v7 = EulerAngleAxisY();
    FromEuler(0.0, v4->LookRotY * 0.017453292, 0.0);
    p_x = &vf00.x;
    x = p_x[4];
    y = p_x[5];
    z = p_x[6];
    w = p_x[7];
    v15 = scrGetIntPara(1);
    LookRotY = v4->LookRotY;
    if (v15 >= 100)
      v17 = 100;
    else
      v17 = v15;
    v18 = v7 * -57.29578;
    v19 = (f32)(v7 * -57.29578) < 0.0;
    if (LookRotY < 0.0)
      v19 = 1;
    if (v19)
    {
      v18 = (f32)(v7 * -57.29578) + 360.0;
      LookRotY = LookRotY + 360.0;
    }
    if (v18 == INFINITY)
      v20 = -128.0;
    else
      v20 = ((s32)v18 % 360);
    if (LookRotY == INFINITY)
      v21 = -128.0;
    else
      v21 = ((s32)LookRotY % 360);
    if ((f32)(v20 - v21) > 180.0 || (f32)(v20 - v21) < -180.0)
    {
      if (v20 >= v21)
        v21 = v21 + 360.0;
      else
        v20 = v20 + 360.0;
    }
    v24 = v21 - v20;
    if (v24 < 0.0)
      v24 = -v24;
    if (v24 > 90.0)
      v24 = 90.0;
    v25 = v24;
    if (v24 == INFINITY)
      v25 = 0x80000000;
    v26 = v25 * v17;
    if (40 * (v26 / 90) / 100 >= 100)
      v27 = 100;
    else
      v27 = 40 * (v26 / 90) / 100;
    if (v26 <= 269)
      v28 = 1;
    else
      v28 = v27;
    v33.x = x;
    v33.y = y;
    v33.z = z;
    v33.w = w;
    evtSetUnitRot1(v4, v33, v28);
    v29 = v31;
    dds3UnitObjectBasicKubiOff(v29);
    return 1;
  }
  return 1;
}

// 0x1a07ec0: s32 MODEL_ON(void)
static inline s32 MODEL_ON(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  dds3ModelHandle_t *Model;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  if (!UnitHandle)
    return 1;
  Model = UnitHandle->Model;
  mdlShow(Model);
  return 1;
}

// 0x1a07fb0: s32 MODEL_OFF(void)
static inline s32 MODEL_OFF(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  dds3ModelHandle_t *Model;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  if (!UnitHandle)
    return 1;
  Model = UnitHandle->Model;
  mdlHide(Model);
  return 1;
}

// 0x1a080a0: s32 MODEL_LIGHT_ON(void)
static inline s32 MODEL_LIGHT_ON(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  evtUnitLightOn(UnitHandle);
  return 1;
}

// 0x1a08140: s32 MODEL_LIGHT_OFF(void)
static inline s32 MODEL_LIGHT_OFF(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  s32 v3;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  v3 = scrGetIntPara(1);
  evtUnitLightOff(UnitHandle, v3);
  return 1;
}

// 0x1a08200: s32 MODEL_LIGHT_WAIT(void)
static inline s32 MODEL_LIGHT_WAIT(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  return !evtUnitLightAnimeStat(UnitHandle);
}

// 0x1a082a0: s32 MODEL_LIGHT_RGB(void)
static inline s32 MODEL_LIGHT_RGB(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  f32 FloatPara;
  f32 v5;
  f32 v7;
  f32 x;
  float32x2_t v11;
  f32 w;
  f32 v13;
  f32 v15;
  f32 v17;
  int32x2_t v19;
  uint32x2_t v20;
  u32 v21;
  u32 v22;
  u8 v24;
  int32x2_t v25;
  f32 v26;
  f32 v27;
  u8 v28;
  int8x8_t v29;
  u8 v30;
  s32 v31;
  u32 v32;
  u32 v33;
  u32 v34;
  bool v35;
  float32x2_t v36;
  u8 v37;
  int32x2_t v38;
  u8 v39;
  int32x2_t v40;
  uint32x2_t v41;
  u64 v42;
  u32 v43;
  u32 v44;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  FloatPara = scrGetFloatPara(2);
  vct_A.x = FloatPara;
  v5 = scrGetFloatPara(3);
  vct_A.y = v5;
  v7 = scrGetFloatPara(4);
  vct_A.z = v7;
  vct_A.w = 0.0;
  x = vct_A.x;
  v11.n64_u64[0] = *(u64 *)&vct_A.y;
  w = vct_A.w;
  v13 = scrGetFloatPara(5);
  vct_A.x = v13;
  v15 = scrGetFloatPara(6);
  vct_A.y = v15;
  v17 = scrGetFloatPara(7);
  vct_A.z = v17;
  vct_A.w = 1.0;
  v19.n64_u64[0] = vcvt_n_s32_f32(v11, 7u).n64_u64[0];
  v20.n64_u64[0] = vcvt_n_u32_f32(v11, 7u).n64_u64[0];
  v21 = vcvts_n_s32_f32(w, 7u);
  v22 = vcvts_n_u32_f32(w, 7u);
  v24 = vcvts_n_s32_f32(x, 7u);
  v25.n64_u64[0] = vcltz_f32(vmul_f32(v11, (float32x2_t)0x4300000043000000LL)).n64_u64[0];
  v26 = vct_A.x;
  if ((f32)(w * 128.0) >= 0.0)
    v21 = v22;
  v27 = vct_A.w;
  v28 = vcvts_n_u32_f32(x, 7u);
  v29.n64_u64[0] = vand_s8(vshl_u32(vbsl_s8(v25, v19, v20), (uint32x2_t)0x1000000008LL), (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
  if ((f32)(x * 128.0) >= 0.0)
    v30 = v28;
  else
    v30 = v24;
  v31 = v30 | (v21 << 24);
  v32 = vcvts_n_s32_f32(v27, 7u);
  v33 = vcvts_n_u32_f32(v27, 7u);
  v34 = v31 | v29.n64_u32[0] | v29.n64_u32[1];
  if ((f32)(v27 * 128.0) >= 0.0)
    v32 = v33;
  v35 = (f32)(v26 * 128.0) < 0.0;
  v36.n64_u64[0] = *(u64 *)&vct_A.y;
  v37 = vcvts_n_s32_f32(v26, 7u);
  v38.n64_u64[0] = vcltz_f32(vmul_f32(v36, (float32x2_t)0x4300000043000000LL)).n64_u64[0];
  v39 = vcvts_n_u32_f32(v26, 7u);
  v40.n64_u64[0] = vcvt_n_s32_f32(v36, 7u).n64_u64[0];
  v41.n64_u64[0] = vcvt_n_u32_f32(v36, 7u).n64_u64[0];
  if (!v35)
    v37 = v39;
  v42 = vand_s8(vshl_u32(vbsl_s8(v38, v40, v41), (uint32x2_t)0x1000000008LL), (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
  v43 = v37 | (v32 << 24) | v42 | HIDWORD(v42);
  v44 = scrGetIntPara(1);
  evtSetUnitLightAndAmbient(UnitHandle, v44, v34, v43);
  return 1;
}

// 0x1a087f0: s32 MODEL_LIGHT_DIR(void)
static inline s32 MODEL_LIGHT_DIR(void) {
  f32 w;
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  f32 FloatPara;
  f32 v5;
  f32 v6;
  f32 *p_x;
  s32 v10;

  w = zeroVector.w;
  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  FloatPara = scrGetFloatPara(2);
  v5 = scrGetFloatPara(3);
  v6 = scrGetFloatPara(4);
  if (fabsf(FloatPara) > 0.01 || fabsf(v5) > 0.01 || fabsf(v6) > 0.01)
  {
    p_x = &vf00.x;
    p_x[4] = FloatPara;
    p_x[5] = v5;
    p_x[6] = v6;
    p_x[7] = w;
    v10 = scrGetIntPara(1);
    evtSetUnitLightDir(UnitHandle, v10);
    return 1;
  }
  return 1;
}

// 0x1a08a20: s32 MODEL_RGB(void)
static inline s32 MODEL_RGB(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  f32 FloatPara;
  f32 v5;
  f32 v7;
  f32 w;
  f32 x;
  u32 v12;
  u32 v13;
  u8 v14;
  u8 v15;
  bool v16;
  float32x2_t v17;
  float32x2_t v18;
  int32x2_t v19;
  uint32x2_t v20;
  u64 v21;
  u32 v22;
  u32 v23;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  FloatPara = scrGetFloatPara(2);
  vct_A.x = FloatPara;
  v5 = scrGetFloatPara(3);
  vct_A.y = v5;
  v7 = scrGetFloatPara(4);
  vct_A.z = v7;
  vct_A.w = 0.0;
  w = vct_A.w;
  x = vct_A.x;
  v12 = vcvts_n_s32_f32(w, 7u);
  v13 = vcvts_n_u32_f32(w, 7u);
  v14 = vcvts_n_s32_f32(x, 7u);
  if ((f32)(w * 128.0) >= 0.0)
    v12 = v13;
  v15 = vcvts_n_u32_f32(x, 7u);
  v16 = (f32)(x * 128.0) < 0.0;
  v17.n64_u64[0] = *(u64 *)&vct_A.y;
  v18.n64_u64[0] = vmul_f32(v17, (float32x2_t)0x4300000043000000LL).n64_u64[0];
  v19.n64_u64[0] = vcvt_n_s32_f32(v17, 7u).n64_u64[0];
  v20.n64_u64[0] = vcvt_n_u32_f32(v17, 7u).n64_u64[0];
  if (v16)
    v15 = v14;
  v21 = vand_s8(vshl_u32(vbsl_s8(vcltz_f32(v18), v19, v20), (uint32x2_t)0x1000000008LL), (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
  v22 = v15 | (v12 << 24) | v21 | HIDWORD(v21);
  v23 = scrGetIntPara(1);
  evtSetUnitColorRGB(UnitHandle, v23, v22);
  return 1;
}

// 0x1a08d50: s32 MODEL_A(void)
static inline s32 MODEL_A(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  f32 FloatPara;
  f32 w;
  f32 x;
  u32 v9;
  u32 v10;
  u8 v11;
  u8 v12;
  bool v13;
  float32x2_t v14;
  float32x2_t v15;
  int32x2_t v16;
  uint32x2_t v17;
  u64 v18;
  u32 v19;
  u32 v20;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  vct_A = vf00;
  FloatPara = scrGetFloatPara(2);
  vct_A.w = FloatPara;
  w = vct_A.w;
  x = vct_A.x;
  v9 = vcvts_n_s32_f32(w, 7u);
  v10 = vcvts_n_u32_f32(w, 7u);
  v11 = vcvts_n_s32_f32(x, 7u);
  if ((f32)(w * 128.0) >= 0.0)
    v9 = v10;
  v12 = vcvts_n_u32_f32(x, 7u);
  v13 = (f32)(x * 128.0) < 0.0;
  v14.n64_u64[0] = *(u64 *)&vct_A.y;
  v15.n64_u64[0] = vmul_f32(v14, (float32x2_t)0x4300000043000000LL).n64_u64[0];
  v16.n64_u64[0] = vcvt_n_s32_f32(v14, 7u).n64_u64[0];
  v17.n64_u64[0] = vcvt_n_u32_f32(v14, 7u).n64_u64[0];
  if (v13)
    v12 = v11;
  v18 = vand_s8(vshl_u32(vbsl_s8(vcltz_f32(v15), v16, v17), (uint32x2_t)0x1000000008LL), (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
  v19 = v12 | (v9 << 24) | v18 | HIDWORD(v18);
  v20 = scrGetIntPara(1);
  evtSetUnitColorA(UnitHandle, v20, v19);
  return 1;
}

// 0x1a08fc0: s32 MODEL_DISSOLVEALPHA(void)
static inline s32 MODEL_DISSOLVEALPHA(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  f32 FloatPara;
  f32 v5;
  dds3ModelHandle_t *Model;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  FloatPara = scrGetFloatPara(1);
  UnitHandle->dissolveAlphaMove = FloatPara;
  if (FloatPara <= 0.0)
    v5 = 1.0;
  else
    v5 = 0.0;
  UnitHandle->dissolveAlpha = v5;
  Model = UnitHandle->Model;
  mdlSetDissolveAlpha(Model, v5);
  return 1;
}

// 0x1a090d0: s32 MODEL_LIGHT_LINK(void)
static inline s32 MODEL_LIGHT_LINK(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  u32 v3;
  s32 v5;
  dds3Basic_t *light;
  dds3Basic_t *pBasic;

  light = 0;
  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  v3 = scrGetIntPara(2);
  pBasic = dds3GetActiveScene();
  light = dds3SceneBasicSearch(pBasic, v3, 9u);
  if (light)
  {
    v5 = scrGetIntPara(1);
    evtLinkLightObjectBasic(UnitHandle, light, v5);
  }
  return 1;
}

// 0x1a09280: s32 MODEL_LIGHT_UNLINK(void)
static inline s32 MODEL_LIGHT_UNLINK(void) {
  s32 IntPara;
  evtUnitHandle_t *UnitHandle;
  s32 v3;

  IntPara = scrGetIntPara(0);
  UnitHandle = evtGetUnitHandle(IntPara);
  v3 = scrGetIntPara(1);
  evtUnlinkLightObjectBasic(UnitHandle, v3);
  return 1;
}

// 0x1a09340: s32 EFFECT_BE(void)
#define EFFECT_BE() (1)

// 0x1a09350: s32 EFFECT_LOAD(void)
#define EFFECT_LOAD() (1)

// 0x1a09360: s32 EFFBED_LOAD(void)
#define EFFBED_LOAD() (1)

// 0x1a09370: s32 EFFBED_BE(void)
#define EFFBED_BE() (1)

// 0x1a09380: s32 EFFBED_BE_EVO(void)
#define EFFBED_BE_EVO() (1)

// 0x1a09390: s32 EFFBED_START(void)
#define EFFBED_START() (1)

// 0x1a093a0: s32 EFFBED_START_EVO(void)
#define EFFBED_START_EVO() (1)

// 0x1a093b0: s32 EFFEPL_LOAD(void)
static inline s32 EFFEPL_LOAD(void) {
  fileHandle_t *v3;
  fileHandle_t *v4;
  void *topPtr;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  void *data;
  u32 serialID;
  s32 v14;
  char *StrPara;
  char *FileName;
  char *v17;
  fileHandle_t *v18;
  dds3Basic_t *basic;
  sdfVector4_t v23;
  sdfVector4_t v24;

  if (s_fh)
  {
    goto LABEL_4;
  }
  StrPara = scrGetStrPara(0);
  FileName = GetFileName(StrPara, 0);
  v17 = Replace_54838864(FileName, ".EPL", "", 0);
  v18 = fileLoadEx("e_eff", v17, 0, 0);
  s_fh = v18;
LABEL_4:
  if (!fileCheckEnd(s_fh))
    return 0;
  v3 = s_fh;
  v4 = v3;
  topPtr = v3->topPtr;
  fileHandleFree(v4);
  x = zeroVector.x;
  y = zeroVector.y;
  z = zeroVector.z;
  w = zeroVector.w;
  data = topPtr[1].klass->_1.byval_arg.data;
  v24.w = 1.0;
  v24.x = 0.0;
  v24.y = 0.0;
  v24.z = 0.0;
  v23.x = x;
  v23.y = y;
  v23.z = z;
  v23.w = w;
  basic = dds3EffectObjectBasicAddEPL(data, v23, v24);
  if (basic)
  {
    dds3EffectObjectBasicStatOn(basic, 1u);
    serialID = basic->serialID;
    v14 = serialID;
  }
  else
  {
    v14 = 0;
  }
  scrSetIntReturnValue(v14);
  s_fh = 0;
  return 1;
}

// 0x1a09760: s32 EFFEPL_LOAD2(void)
static inline s32 EFFEPL_LOAD2(void) {
  fileHandle_t *v3;
  fileHandle_t *v4;
  void *topPtr;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  void *data;
  u32 serialID;
  s32 v14;
  char *StrPara;
  char *v16;
  char *FileName;
  char *v18;
  fileHandle_t *v19;
  dds3Basic_t *basic;
  sdfVector4_t v24;
  sdfVector4_t v25;

  basic = 0;
  if (s_fh)
  {
    goto LABEL_5;
  }
  else
  {
    StrPara = scrGetStrPara(0);
    v16 = scrGetStrPara(1);
    if (Contains(StrPara, "NEGA_RDH", 0))
    {
      scrSetIntReturnValue(0);
      return 1;
    }
    FileName = GetFileName(StrPara, 0);
    v18 = Replace_54838864(FileName, ".EPL", "", 0);
    v19 = fileLoadEx(v16, v18, 0, 0);
    s_fh = v19;
LABEL_5:
    if (fileCheckEnd(s_fh))
      goto LABEL_6;
    return 0;
  }
  if (!fileCheckEnd(s_fh))
    return 0;
LABEL_6:
  v3 = s_fh;
  v4 = v3;
  topPtr = v3->topPtr;
  fileHandleFree(v4);
  x = zeroVector.x;
  y = zeroVector.y;
  z = zeroVector.z;
  w = zeroVector.w;
  data = topPtr[1].klass->_1.byval_arg.data;
  v25.w = 1.0;
  v25.x = 0.0;
  v25.y = 0.0;
  v25.z = 0.0;
  v24.x = x;
  v24.y = y;
  v24.z = z;
  v24.w = w;
  basic = dds3EffectObjectBasicAddEPL(data, v24, v25);
  if (basic)
  {
    dds3EffectObjectBasicStatOn(basic, 1u);
    serialID = basic->serialID;
    v14 = serialID;
  }
  else
  {
    v14 = 0;
  }
  scrSetIntReturnValue(v14);
  s_fh = 0;
  return 1;
}

// 0x1a09b30: s32 LOAD_SDOKUSINEFF(void)
static inline s32 LOAD_SDOKUSINEFF(void) {
  fldLoadDOKUSIN();
  return 1;
}

// 0x1a09bb0: s32 DRAW_MUDO_T(void)
static inline s32 DRAW_MUDO_T(void) {
  u32 IntPara;
  dds3Basic_t *v2;
  f32 *workdata;
  f32 v5;
  f32 v6;
  f32 v7;
  f32 FloatPara;
  s32 v9;
  s32 v10;
  dds3Basic_t *pBasic;

  pBasic = dds3GetControlScene();
  IntPara = scrGetIntPara(0);
  v2 = dds3SceneBasicSearch(pBasic, IntPara, 0x10u);
  if (!v2)
    return 1;
  workdata = v2->workdata;
  v5 = workdata[6];
  v6 = workdata[4];
  v7 = workdata[5];
  FloatPara = scrGetFloatPara(1);
  v9 = scrGetIntPara(2);
  v10 = scrGetIntPara(3);
  return fldDrawMUDO_T(v6, v7, v5, FloatPara, v9, v10);
}

// 0x1a09db0: s32 EFFMG1_LOAD(void)
#define EFFMG1_LOAD() (1)

// 0x1a09dc0: s32 EFFMG1_BE(void)
#define EFFMG1_BE() (1)

// 0x1a09dd0: s32 EFFMG2_LOAD(void)
#define EFFMG2_LOAD() (1)

// 0x1a09de0: s32 EFFMG2_BE(void)
#define EFFMG2_BE() (1)

// 0x1a09df0: s32 EFFMG2_PRESET(void)
#define EFFMG2_PRESET() (1)

// 0x1a09e00: s32 EFFECT_PRESET(void)
#define EFFECT_PRESET() (1)

// 0x1a09e10: s32 EFFECT_CLS(void)
static inline s32 EFFECT_CLS(void) {
  u32 IntPara;
  dds3Basic_t *v3;
  dds3Basic_t *v5;
  dds3Basic_t *pBasic;

  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  v3 = dds3SceneBasicSearch(pBasic, IntPara, 7u);
  if (!v3)
    return 1;
  v5 = v3;
  dds3SceneBasicDelete(v5);
  return 1;
}

// 0x1a09f70: s32 EFFECT_POS_XYZ(void)
static inline s32 EFFECT_POS_XYZ(void) {
  u32 IntPara;
  dds3Basic_t *v3;
  void *workdata;
  dds3Basic_t *v5;
  dds3PoseSet_t *poseset;
  dds3PoseSet_t *v8;
  dds3PoseSet_t *v9;
  f32 FloatPara;
  dds3PoseSet_t *v11;
  dds3Basic_t *pBasic;

  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  v3 = dds3SceneBasicSearch(pBasic, IntPara, 7u);
  workdata = v3->workdata;
  v5 = v3;
  if (((s64)workdata[1].monitor & 4) != 0)
  {
    *(f32 *)&workdata[2].monitor = scrGetFloatPara(1);
    *((f32 *)&workdata[2].monitor + 1) = scrGetFloatPara(2);
    *(f32 *)&workdata[3].klass = scrGetFloatPara(3);
    return 1;
  }
  else
  {
    poseset = v3->poseset;
    poseset->pos.x = scrGetFloatPara(1);
    v8 = v5->poseset;
    v8->pos.y = scrGetFloatPara(2);
    v9 = v5->poseset;
    FloatPara = scrGetFloatPara(3);
    v11 = v5->poseset;
    v9->pos.z = FloatPara;
    v11->flag = v11->flag & 0xFFFFFFFC | 1;
    return 1;
  }
}

// 0x1a0a180: s32 EFFECT_ROT_XYZ(void)
static inline s32 EFFECT_ROT_XYZ(void) {
  u32 IntPara;
  void *workdata;
  f32 v5;
  f32 FloatPara;
  f32 v8;
  f32 *p_x;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  dds3Basic_t *v16;
  dds3Basic_t *pBasic;
  sdfVector4_t v18;

  v16 = 0;
  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  v16 = dds3SceneBasicSearch(pBasic, IntPara, 7u);
  workdata = v16->workdata;
  if (((s64)workdata[1].monitor & 4) == 0)
  {
    v5 = scrGetFloatPara(1) * 0.017453292;
    FloatPara = scrGetFloatPara(2);
    FromEuler(v5, FloatPara * 0.017453292, 0.0);
    vct_B = vct_A;
    v8 = scrGetFloatPara(3);
    FromEuler(0.0, 0.0, v8 * 0.017453292);
    Mult();
    p_x = &vf00.x;
    v11 = p_x[4];
    v12 = p_x[5];
    v14 = p_x[6];
    v13 = p_x[7];
    v18.x = v11;
    v18.y = v12;
    v18.z = v14;
    v18.w = v13;
    dds3SetRotPoseSet(v16, v18);
    return 1;
  }
  return 1;
}

// 0x1a0a490: s32 EFFECT_POS(void)
static inline s32 EFFECT_POS(void) {
  u32 IntPara;
  dds3Basic_t *v3;
  dds3Basic_t *v4;
  u32 v5;
  dds3Basic_t *v8;
  void *workdata;
  void *v11;
  dds3PoseSet_t *poseset;
  dds3Basic_t *pBasic;

  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  v3 = dds3SceneBasicSearch(pBasic, IntPara, 7u);
  if (!v3)
    return 1;
  v4 = v3;
  v5 = scrGetIntPara(1);
  pBasic = dds3GetActiveScene();
  v8 = dds3SceneBasicSearch(pBasic, v5, 0x10u);
  if (!v8)
    return 1;
  workdata = v8->workdata;
  v11 = v4->workdata;
  poseset = v4->poseset;
  if (((s64)v11[1].monitor & 4) == 0)
  {
    poseset->pos.x = *(f32 *)&workdata[1].klass;
    poseset->pos.y = *((f32 *)&workdata[1].klass + 1);
    poseset->pos.z = *(f32 *)&workdata[1].monitor;
    poseset->rot.x = *(f32 *)&workdata[2].klass;
    poseset->rot.y = *((f32 *)&workdata[2].klass + 1);
    poseset->rot.z = *(f32 *)&workdata[2].monitor;
    poseset->rot.w = *((f32 *)&workdata[2].monitor + 1);
  }
  poseset->flag = poseset->flag & 0xFFFFFFFC | 1;
  return 1;
}

// 0x1a0a780: s32 EFFMG1_POS(void)
#define EFFMG1_POS() (1)

// 0x1a0a790: s32 EFFMG2_POS(void)
#define EFFMG2_POS() (1)

// 0x1a0a7a0: s32 EFFECT_ON(void)
#define EFFECT_ON() (1)

// 0x1a0a7b0: s32 EFFECT_LINK(void)
#define EFFECT_LINK() (1)

// 0x1a0a7c0: s32 EFFECT_LINK2(void)
#define EFFECT_LINK2() (1)

// 0x1a0a7d0: s32 EFFECT_UNLINK(void)
#define EFFECT_UNLINK() (1)

// 0x1a0a7e0: s32 EFFECT_OFF(void)
#define EFFECT_OFF() (1)

// 0x1a0a7f0: s32 EFFECT_PATH_MOVE(void)
#define EFFECT_PATH_MOVE() (1)

// 0x1a0a800: s32 EFFECT_PATH_WAIT(void)
#define EFFECT_PATH_WAIT() (0)

// 0x1a0a810: s32 SEARCH_ID(void)
static inline s32 SEARCH_ID(void) {
  char *StrPara;
  dds3Basic_t *v2;
  s32 serialID;
  dds3Basic_t *scene;

  scene = dds3GetControlScene();
  StrPara = scrGetStrPara(0);
  v2 = dds3SceneBasicSearchName(scene, StrPara);
  if (!v2)
  {
    serialID = 0;
    goto LABEL_11;
  }
  serialID = v2->serialID;
LABEL_11:
  scrSetIntReturnValue(serialID);
  return 1;
}

// 0x1a0a930: s32 RTRN_TITLE(void)
static inline s32 RTRN_TITLE(void) {
  s32 result;

  result = sBtlExec();
  if (result == 1)
    return result;
  if (result == 2)
    return 0;
  dds3AdminiCallSequence4(2, 0, 0, 0);
  return 1;
}

// 0x1a0a9f0: s32 CALL_STAFF(void)
static inline s32 CALL_STAFF(void) {
  dds3AdminiCallSequence4(14, 0, 0, 0);
  return 1;
}

// 0x1a0aa20: s32 CALL_ENDSAVE(void)
static inline s32 CALL_ENDSAVE(void) {
  dds3AdminiCallSequence4(5, 0, 0, 0);
  return 1;
}

// 0x1a0aa50: s32 CALL_SAVE(void)
static inline s32 CALL_SAVE(void) {
  fldGbLocationSavePointStore();
  dds3AdminiCallSequence4(4, 0, 0, 0);
  scrSetIntReturnValue(0);
  return 1;
}

// 0x1a0ab00: s32 CALL_NEXT(void)
#define CALL_NEXT() (1)

// 0x1a0ab10: s32 CALL_EVENT(void)
static inline s32 CALL_EVENT(void) {
  s32 IntPara;
  SequenceParameter *v2;

  IntPara = scrGetIntPara(0);
  v2 = Allocate(SequenceParameter);
  _ctor(v2, 0);
  v2->CallData2 = IntPara;
  dds3AdminiCallSequence(9, v2, 0);
  scrAllReleaseScript();
  return 1;
}

// 0x1a0abc0: s32 EXIT_EVENT(void)
static inline s32 EXIT_EVENT(void) {
  if (scrGetCommandTimer())
    return 0;
  dds3AdminiExitSequence();
  return 0;
}

// 0x1a0b2a0: s32 CALL_BATTLE(void)
static inline s32 CALL_BATTLE(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  CallBattleSub(IntPara, 0);
  return 1;
}

// 0x1a0b6c0: s32 CALL_BATTLE2(void)
static inline s32 CALL_BATTLE2(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  CallBattleSub2(IntPara);
  return 1;
}

// 0x1a0b730: s32 RESTORE_BATTLE(void)
static inline s32 RESTORE_BATTLE(void) {
  s32 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  CallBattleSub(IntPara, v2);
  return 1;
}

// 0x1a0b7b0: s32 CALL_MAP(void)
static inline s32 CALL_MAP(void) {
  u32 IntPara;
  s32 v2;
  s32 v3;
  char *label;

  label = 0;
  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  if (IntPara <= 0x1E && ((1 << IntPara) & 0x64000000) != 0)
  {
    fldGb->MapTitleID = IntPara;
    scrEventSkipEnd(0, 0);
    goto LABEL_10;
  }
LABEL_10:
  mapCallMap(IntPara, v2, v3, &label);
  return 1;
}

// 0x1a0b910: s32 CALL_MAP2(void)
static inline s32 CALL_MAP2(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;
  char *label;

  label = scrGetStrPara(3);
  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  mapCallMap(IntPara, v2, v3, &label);
  return 1;
}

// 0x1a0b9f0: s32 CALL_LMAP(void)
static inline s32 CALL_LMAP(void) {
  SequenceParameter *v1;

  v1 = Allocate(SequenceParameter);
  _ctor(v1, 0);
  v1->CallData2 = scrGetIntPara(0);
  dds3AdminiCallSequence(35, v1, 0);
  return 1;
}

// 0x1a0baa0: s32 FIELD_BE(void)
#define FIELD_BE() (1)

// 0x1a0bab0: s32 FIELD_DSP(void)
static inline s32 FIELD_DSP(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;
  s32 v5;
  s32 v6;
  dds3Basic_t *scene;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = v2 + (IntPara << 16);
  scene = dds3GetControlScene();
  if (dds3GetMapNo(scene) == v3)
    return 1;
  v5 = scrGetIntPara(0);
  v6 = scrGetIntPara(1);
  evtLoadMap(v5, v6);
  return 1;
}

// 0x1a0bc30: s32 FIELD_ANIME_START(void)
static inline s32 FIELD_ANIME_START(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  evtStageAnimeControl(0, IntPara);
  return 1;
}

// 0x1a0bcd0: s32 FIELD_ANIME_STOP(void)
static inline s32 FIELD_ANIME_STOP(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  evtStageAnimeControl(1, IntPara);
  return 1;
}

// 0x1a0bd70: s32 FIELD_CLS(void)
static inline s32 FIELD_CLS(void) {
  evtFreeAllUnit();
  evtFreeStage();
  DrawFlag |= 0x2000000u;
  return 1;
}

// 0x1a0be10: s32 FIELD_CLS_STOP(void)
static inline s32 FIELD_CLS_STOP(void) {
  evtFreeAllUnit();
  evtFreeStage();
  DrawFlag |= 0x2000000u;
  return 1;
}

// 0x1a0beb0: s32 UNIT_CLS(void)
static inline s32 UNIT_CLS(void) {
  evtFreeAllUnit();
  return 1;
}

// 0x1a0bf30: s32 UNIT_CLS_STOP(void)
static inline s32 UNIT_CLS_STOP(void) {
  evtFreeAllUnit();
  return 1;
}

// 0x1a0bfb0: s32 CAM_SEL(void)
static inline s32 CAM_SEL(void) {
  u32 IntPara;
  dds3Basic_t *cameraBasic_local;
  dds3Basic_t *ActiveScene;
  dds3Basic_t *pBasic;

  if (scrGetIntPara(0) < 0)
  {
    cameraBasic_local = cameraBasic;
    if (!cameraBasic_local)
      return 1;
    goto LABEL_25;
  }
  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  cameraBasic_local = dds3SceneBasicSearch(pBasic, IntPara, 4u);
  if (!cameraBasic_local)
    return 1;
LABEL_25:
  ActiveScene = dds3GetActiveScene();
  SetActiveCamera(ActiveScene, cameraBasic_local, 0);
  return 1;
}

// 0x1a0c210: s32 CAM_SEL_FOVY(void)
static inline s32 CAM_SEL_FOVY(void) {
  u32 IntPara;
  dds3Basic_t *cameraBasic_local;
  void *workdata;
  dds3Basic_t *ActiveScene;
  dds3Basic_t *pBasic;

  if (scrGetIntPara(0) < 0)
  {
    cameraBasic_local = cameraBasic;
    if (cameraBasic_local)
      goto LABEL_26;
    return 1;
  }
  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  cameraBasic_local = dds3SceneBasicSearch(pBasic, IntPara, 4u);
  workdata = cameraBasic_local->workdata;
  HIDWORD(workdata[9].monitor) |= 1u;
LABEL_26:
  ActiveScene = dds3GetActiveScene();
  SetActiveCamera(ActiveScene, cameraBasic_local, 0);
  return 1;
}

// 0x1a0c4c0: s32 CAM_PATH_MOVE(void)
static inline s32 CAM_PATH_MOVE(void) {
  u32 IntPara;
  dds3Basic_t *cameraBasic_local;
  u32 v6;
  dds3Basic_t *v9;
  dds3Basic_t *v10;
  dds3Basic_t *pBasic;

  if ((scrGetIntPara(0) & 0x80000000) == 0)
  {
    IntPara = scrGetIntPara(0);
    pBasic = dds3GetActiveScene();
    cameraBasic_local = dds3SceneBasicSearch(pBasic, IntPara, 4u);
    if (!cameraBasic_local)
      return 1;
    goto LABEL_25;
  }
  cameraBasic_local = cameraBasic;
  if (!cameraBasic_local)
    return 1;
LABEL_25:
  v6 = scrGetIntPara(1);
  pBasic = dds3GetActiveScene();
  v9 = dds3SceneBasicSearch(pBasic, v6, 0xFu);
  if (!v9)
    return 1;
  v10 = v9;
  evtPathLinkAndMake(v10, cameraBasic_local);
  return 1;
}

// 0x1a0c7c0: s32 CAM_PATH_WAIT(void)
static inline s32 CAM_PATH_WAIT(void) {
  u32 IntPara;
  dds3Basic_t *cameraBasic_local;
  u32 v5;
  dds3Basic_t *pBasic;

  if ((scrGetIntPara(0) & 0x80000000) == 0)
  {
    IntPara = scrGetIntPara(0);
    pBasic = dds3GetActiveScene();
    cameraBasic_local = dds3SceneBasicSearch(pBasic, IntPara, 4u);
    if (cameraBasic_local)
      goto LABEL_12;
    return 1;
  }
  cameraBasic_local = cameraBasic;
  if (!cameraBasic_local)
    return 1;
LABEL_12:
  v5 = evtCheckPathStat(cameraBasic_local) + 1;
  if (v5 <= 2)
    return dword_3E60F68[v5];
  return 0;
}

// 0x1a0ca20: s32 CAM_CREATE(void)
static inline s32 CAM_CREATE(void) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  u32 v6;
  dds3Basic_t *pBasic;
  sdfVector4_t v9;
  sdfVector4_t v10;

  x = zeroVector.x;
  y = zeroVector.y;
  z = zeroVector.z;
  w = zeroVector.w;
  v6 = dds3SerializeID();
  v10.x = 0.0;
  v10.y = 0.0;
  v10.z = 0.0;
  v9.x = x;
  v9.y = y;
  v9.z = z;
  v9.w = w;
  v10.w = 1.0;
  pBasic = dds3CameraObjectBasicAddTypeFree(v6, v9, v10);
  dds3SetRadiusPoseSet(pBasic, 1.0);
  scrSetIntReturnValue(v6);
  return 1;
}

// 0x1a0cb80: s32 CAM_CLS(void)
static inline s32 CAM_CLS(void) {
  u32 IntPara;
  dds3Basic_t *v3;
  dds3Basic_t *v5;
  dds3Basic_t *pBasic;

  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  v3 = dds3SceneBasicSearch(pBasic, IntPara, 4u);
  if (!v3)
    return 1;
  v5 = v3;
  dds3SceneBasicDelete(v5);
  return 1;
}

// 0x1a0cce0: s32 CAM_POS_XYZ(void)
static inline s32 CAM_POS_XYZ(void) {
  f32 w;
  u32 IntPara;
  f32 FloatPara;
  f32 v6;
  f32 v7;
  dds3Basic_t *cameraBasic_local;
  dds3Basic_t *pBasic;
  sdfVector4_t v11;

  cameraBasic_local = 0;
  w = zeroVector.w;
  if ((scrGetIntPara(0) & 0x80000000) != 0)
  {
    cameraBasic_local = cameraBasic;
    if (!cameraBasic_local)
      return 1;
    goto LABEL_27;
  }
  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  cameraBasic_local = dds3SceneBasicSearch(pBasic, IntPara, 4u);
  if (cameraBasic_local)
  {
LABEL_27:
    FloatPara = scrGetFloatPara(1);
    v6 = scrGetFloatPara(2);
    v7 = scrGetFloatPara(3);
    v11.x = FloatPara;
    v11.y = v6;
    v11.z = v7;
    v11.w = w;
    dds3SetPosPoseSet(cameraBasic_local, v11);
  }
  return 1;
}

// 0x1a0cf80: s32 CAM_ROT_XYZ(void)
static inline s32 CAM_ROT_XYZ(void) {
  u32 IntPara;
  f32 v5;
  f32 FloatPara;
  f32 v8;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  dds3Basic_t *cameraBasic_local;
  dds3Basic_t *pBasic;
  sdfVector4_t v20;

  cameraBasic_local = 0;
  if ((scrGetIntPara(0) & 0x80000000) == 0)
    goto LABEL_4;
  cameraBasic_local = cameraBasic;
  if (!cameraBasic_local)
    return 1;
LABEL_25:
  v5 = scrGetFloatPara(1) * 0.017453292;
  FloatPara = scrGetFloatPara(2);
  FromEuler(v5, FloatPara * 0.017453292, 0.0);
  vct_B = vct_A;
  v8 = scrGetFloatPara(3);
  FromEuler(0.0, 0.0, v8 * 0.017453292);
  Mult();
  p_x = &vf00.x;
  x = p_x[4];
  y = p_x[5];
  z = p_x[6];
  w = p_x[7];
  v20.x = x;
  v20.y = y;
  v20.z = z;
  v20.w = w;
  dds3SetRotPoseSet(cameraBasic_local, v20);
  return 1;
LABEL_4:
  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  cameraBasic_local = dds3SceneBasicSearch(pBasic, IntPara, 4u);
  if (cameraBasic_local)
    goto LABEL_25;
  return 1;
}

// 0x1a0d330: s32 CAM_ROT_Q(void)
static inline s32 CAM_ROT_Q(void) {
  u32 IntPara;
  f32 FloatPara;
  f32 v6;
  f32 v7;
  f32 v8;
  dds3Basic_t *cameraBasic_local;
  dds3Basic_t *pBasic;
  sdfVector4_t v12;

  cameraBasic_local = 0;
  if ((scrGetIntPara(0) & 0x80000000) != 0)
  {
    cameraBasic_local = cameraBasic;
    if (!cameraBasic_local)
      return 1;
    goto LABEL_27;
  }
  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  cameraBasic_local = dds3SceneBasicSearch(pBasic, IntPara, 4u);
  if (cameraBasic_local)
  {
LABEL_27:
    FloatPara = scrGetFloatPara(1);
    v6 = scrGetFloatPara(2);
    v7 = scrGetFloatPara(3);
    v8 = scrGetFloatPara(4);
    v12.x = FloatPara;
    v12.y = v6;
    v12.z = v7;
    v12.w = v8;
    dds3SetRotPoseSet(cameraBasic_local, v12);
  }
  return 1;
}

// 0x1a0d5f0: s32 OBJ_PATH_MOVE(void)
static inline s32 OBJ_PATH_MOVE(void) {
  u32 IntPara;
  dds3Basic_t *v3;
  dds3Basic_t *v4;
  u32 v5;
  dds3Basic_t *v8;
  dds3Basic_t *v9;
  dds3ObjectBaseControlWorkData_t *ControlWorkData;
  dds3Basic_t *v11;
  void *workdata;
  dds3ObjectBaseControlWorkData_t *v13;
  s32 v16;
  dds3PathBasicControl_t *PathControl;
  dds3Basic_t *pObjectBasic;
  dds3Basic_t *pBasic;

  PathControl = 0;
  pObjectBasic = 0;
  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  v3 = dds3SceneBasicSearch(pBasic, IntPara, 6u);
  pObjectBasic = v3;
  if (!v3)
    return 1;
  v4 = v3;
  v5 = scrGetIntPara(1);
  pBasic = dds3GetActiveScene();
  v8 = dds3SceneBasicSearch(pBasic, v5, 0xFu);
  if (!v8)
    return 1;
  v9 = v8;
  ControlWorkData = dds3MatterObjectBasicGetControlWorkData(v4);
  v11 = ControlWorkData->pBasic[1];
  if (v11)
  {
    workdata = v11->workdata;
    if (!workdata)
      goto LABEL_30;
    goto LABEL_28;
  }
  v13 = ControlWorkData;
  dds3ObjectBaseCreateMover(pObjectBasic);
  v11 = v13->pBasic[1];
  workdata = v11->workdata;
  if (!workdata)
LABEL_28:
LABEL_30:
  if (workdata[2].monitor)
  {
    goto LABEL_32;
  }
  else
  {
    dds3MoverBasicSetPath(v11, v9);
    dds3MoverBasicMakePath(v11);
LABEL_32:
    PathControl = dds3MoverBasicGetPathControl(v11);
    if (!PathControl)
      return 1;
    goto LABEL_38;
  }
  PathControl = dds3MoverBasicGetPathControl(v11);
  if (!PathControl)
    return 1;
LABEL_38:
  v16 = scrGetIntPara(2);
  if (v16 == 1)
  {
    v16 = 1;
    goto LABEL_47;
  }
  if (!v16)
  {
    v16 = 0;
LABEL_47:
    dds3PathBasicControlAlterMode(PathControl, v16);
    return 1;
  }
  return 1;
}

// 0x1a0d9f0: s32 OBJ_PATH_MOVE2(void)
static inline s32 OBJ_PATH_MOVE2(void) {
  u32 IntPara;
  dds3Basic_t *v3;
  dds3Basic_t *v4;
  u32 v5;
  dds3Basic_t *v8;
  dds3Basic_t *v9;
  dds3ObjectBaseControlWorkData_t *ControlWorkData;
  dds3Basic_t *v11;
  void *workdata;
  dds3ObjectBaseControlWorkData_t *v13;
  s32 v15;
  dds3PathBasicControl_t *PathControl;
  dds3Basic_t *pObjectBasic;
  dds3Basic_t *pBasic;

  PathControl = 0;
  pObjectBasic = 0;
  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  v3 = dds3SceneBasicSearch(pBasic, IntPara, 6u);
  pObjectBasic = v3;
  if (!v3)
    return 1;
  v4 = v3;
  v5 = scrGetIntPara(1);
  pBasic = dds3GetActiveScene();
  v8 = dds3SceneBasicSearch(pBasic, v5, 0xFu);
  if (!v8)
    return 1;
  v9 = v8;
  ControlWorkData = dds3MatterObjectBasicGetControlWorkData(v4);
  v11 = ControlWorkData->pBasic[1];
  if (v11)
  {
    workdata = v11->workdata;
    if (!workdata)
      goto LABEL_30;
    goto LABEL_28;
  }
  v13 = ControlWorkData;
  dds3ObjectBaseCreateMover(pObjectBasic);
  v11 = v13->pBasic[1];
  workdata = v11->workdata;
  if (!workdata)
LABEL_28:
LABEL_30:
  if (workdata[2].monitor)
  {
    dds3MatterObjectBasicPosToBase(pObjectBasic);
  }
  dds3MoverBasicSetPath(v11, v9);
  dds3MoverBasicMakePath(v11);
  PathControl = dds3MoverBasicGetPathControl(v11);
  if (!PathControl)
    return 1;
  v15 = scrGetIntPara(2);
  if (v15 == 1)
  {
    v15 = 1;
    goto LABEL_48;
  }
  if (!v15)
  {
    v15 = 0;
LABEL_48:
    dds3PathBasicControlAlterMode(PathControl, v15);
    return 1;
  }
  return 1;
}

// 0x1a0dde0: s32 OBJ_PATH_WAIT(void)
static inline s32 OBJ_PATH_WAIT(void) {
  u32 IntPara;
  dds3Basic_t *v3;
  dds3Basic_t *v4;
  u32 v5;
  dds3Basic_t *pBasic;

  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  v3 = dds3SceneBasicSearch(pBasic, IntPara, 6u);
  if (!v3)
    return 1;
  v4 = v3;
  v5 = evtCheckPathStat(v3) + 1;
  if (v5 <= 2)
    return dword_3E60F68[v5];
  return 0;
}

// 0x1a0df90: s32 MOON_START(void)
static inline s32 MOON_START(void) {
  evtMoonEnableCalc();
  return 1;
}

// 0x1a0e010: s32 MOON_STOP(void)
static inline s32 MOON_STOP(void) {
  evtMoonDisableCalc();
  return 1;
}

// 0x1a0e090: s32 GET_MOON(void)
static inline s32 GET_MOON(void) {
  s32 Age;

  Age = evtMoonGetAge();
  scrSetIntReturnValue(Age);
  return 1;
}

// 0x1a0e150: s32 GET_MOON16(void)
static inline s32 GET_MOON16(void) {
  s32 Age16;

  Age16 = evtMoonGetAge16();
  scrSetIntReturnValue(Age16);
  return 1;
}

// 0x1a0e210: s32 CHG_MOON(void)
static inline s32 CHG_MOON(void) {
  u32 IntPara;

  IntPara = scrGetIntPara(0);
  evtMoonSetAge(IntPara);
  return 1;
}

// 0x1a0e2b0: s32 LOAD_BE(void)
#define LOAD_BE() (0)

// 0x1a0e2c0: s32 READ_BE(void)
#define READ_BE() (1)

// 0x1a0e2d0: s32 CHK_BE(void)
#define CHK_BE() (1)

// 0x1a0e2e0: s32 DEL_BE(void)
#define DEL_BE() (1)

// 0x1a0e2f0: s32 PMV_LOAD(void)
static inline s32 PMV_LOAD(void) {
  scrHandle_t *s_hNowpWork_local;
  dds3ProcessID_t *v5;
  dds3ProcessID_t *p_ProcessID;
  dds3ProcessID_t *ProcessID;
  s32 priority;
  s32 IntPara;
  s32 v10;
  dds3ProcessID_t *target;

  s_hNowpWork_local = s_hNowpWork;
  if (!s_hNowpWork_local)
    return 1;
  ProcessID = s_hNowpWork_local->ProcessID;
  p_ProcessID = &s_hNowpWork_local->ProcessID;
  v5 = ProcessID;
  if (!ProcessID)
    return 1;
  priority = v5->priority;
  IntPara = scrGetIntPara(0);
  v10 = scrGetIntPara(1);
  target = evtStart2(priority, IntPara, v10, 0);
  dds3LinkProcess(p_ProcessID, target);
  evtSetFlag(target, 1);
  scrSetIntReturnValue(target->id);
  return 1;
}

// 0x1a0e4b0: s32 PMV_RUN2(void)
static inline s32 PMV_RUN2(void) {
  s32 IntPara;
  dds3ProcessID_t *v2;

  IntPara = scrGetIntPara(0);
  v2 = dds3SearchProcessID(IntPara);
  evtResetFlag(v2, 1);
  scrSetIntReturnValue(v2->id);
  return 1;
}

// 0x1a0e590: s32 PMV_RUN(void)
static inline s32 PMV_RUN(void) {
  scrHandle_t *s_hNowpWork_local;
  dds3ProcessID_t *p_ProcessID;
  dds3ProcessID_t *ProcessID;
  s32 IntPara;
  s32 v7;
  s32 v8;
  s32 priority;
  dds3ProcessID_t *target;

  target = 0;
  scrEventSkipEnd(0, 0);
  s_hNowpWork_local = s_hNowpWork;
  if (!s_hNowpWork_local)
    return 1;
  ProcessID = s_hNowpWork_local->ProcessID;
  p_ProcessID = &s_hNowpWork_local->ProcessID;
  if (!ProcessID)
    return 1;
  IntPara = scrGetIntPara(0);
  v7 = scrGetIntPara(1);
  v8 = scrGetIntPara(2);
  priority = p_ProcessID->priority;
  target = evtStart2(priority, IntPara, v7, v8);
  dds3LinkProcess(p_ProcessID, target);
  scrSetIntReturnValue(target->id);
  itfSetPmvRun(1);
  return 1;
}

// 0x1a0e780: s32 PMV_CHK(void)
static inline s32 PMV_CHK(void) {
  s32 IntPara;
  dds3ProcessID_t *v2;
  dds3ProcessID_t *v3;
  bool v4;
  s32 v6;
  dds3ProcessID_t *id;

  IntPara = scrGetIntPara(0);
  id = dds3SearchProcessID(IntPara);
  if (dds3ExistProcess(id))
  {
    v2 = id;
    if (evtCheckRun(id))
      goto LABEL_10;
    goto LABEL_9000;
    if (evtCheckRun(v2))
    {
LABEL_10:
      v3 = id;
      v4 = evtCheckSeqEnd(v3);
      if (v4)
        v6 = 2;
      else
        v6 = 1;
      goto LABEL_20;
    }
LABEL_9000:
    v6 = 0;
LABEL_20:
    scrSetIntReturnValue(v6);
    return 1;
  }
  return 1;
}

// 0x1a0e8e0: s32 PMV_SEQ_WAIT(void)
static inline s32 PMV_SEQ_WAIT(void) {
  s32 IntPara;
  dds3ProcessID_t *v2;
  dds3ProcessID_t *id;

  IntPara = scrGetIntPara(0);
  id = dds3SearchProcessID(IntPara);
  if (!id)
    return 1;
  if (!dds3ExistProcess(id))
    return 1;
  v2 = id;
  return evtCheckSeqEnd(v2);
}

// 0x1a0ea30: s32 PMV_END(void)
static inline s32 PMV_END(void) {
  s32 IntPara;
  dds3ProcessID_t *v3;
  dds3ProcessID_t *v5;
  dds3ProcessID_t *id;

  id = 0;
  itfSetPmvRun(0);
  itfPmvButtonGuideCtrl(0);
  DrawFlag |= 0x2000000u;
  itfSetMsgWndDefault();
  IntPara = scrGetIntPara(0);
  id = dds3SearchProcessID(IntPara);
  if (!id)
    return 1;
  if (!dds3ExistProcess(id))
    return 1;
  v3 = id;
  if (!evtCheckRun(v3))
    return 1;
  v5 = id;
  evtEnd(v5);
  return 0;
}

// 0x1a0ed40: s32 PMV_SEQ_CHG(void)
static inline s32 PMV_SEQ_CHG(void) {
  s32 IntPara;
  s32 v2;
  dds3ProcessID_t *v3;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *id;

  IntPara = scrGetIntPara(0);
  id = dds3SearchProcessID(IntPara);
  v2 = scrGetIntPara(1);
  if (!dds3ExistProcess(id))
    return 1;
  v3 = id;
  if (!evtCheckRun(id))
    return 1;
  v6 = id;
  evtChgSeq(v6, v2, 0);
  return 1;
}

// 0x1a0f550: s32 PATH_STOP(void)
static inline s32 PATH_STOP(void) {
  s64 v1;
  dds3Basic_t *v2;

  v1 = (loc_1A21A40)(0);
  if (v1)
  {
    v2 = v1;
    evtPathStop(v2);
  }
  return 1;
}

// 0x1a0f5c0: s32 PATH_START(void)
static inline s32 PATH_START(void) {
  s64 v1;
  dds3Basic_t *v2;

  v1 = (loc_1A21A40)(0);
  if (v1)
  {
    v2 = v1;
    evtPathStart(v2);
  }
  return 1;
}

// 0x1a0f630: s32 PATH_RATE(void)
static inline s32 PATH_RATE(void) {
  s64 v1;
  dds3Basic_t *v2;
  f32 FloatPara;

  v1 = (loc_1A21A40)(0);
  if (v1)
  {
    v2 = v1;
    FloatPara = scrGetFloatPara(1);
    evtPathRate(v2, FloatPara);
  }
  return 1;
}

// 0x1a0f6e0: s32 PATH_DIR(void)
static inline s32 PATH_DIR(void) {
  s64 v1;
  dds3Basic_t *v2;
  s32 IntPara;

  v1 = (loc_1A21A40)(0);
  if (v1)
  {
    v2 = v1;
    IntPara = scrGetIntPara(1);
    evtPathDir(v2, IntPara);
  }
  return 1;
}

// 0x1a0f790: s32 PATH_LOOP_ON(void)
static inline s32 PATH_LOOP_ON(void) {
  s64 v1;
  dds3Basic_t *v2;

  v1 = (loc_1A21A40)(0);
  if (v1)
  {
    v2 = v1;
    evtPathLoop(v2, 1);
  }
  return 1;
}

// 0x1a0f810: s32 PATH_LOOP_OFF(void)
static inline s32 PATH_LOOP_OFF(void) {
  s64 v1;
  dds3Basic_t *v2;

  v1 = (loc_1A21A40)(0);
  if (v1)
  {
    v2 = v1;
    evtPathLoop(v2, 0);
  }
  return 1;
}

// 0x1a0f890: s32 LIGHT_PATH_MOVE(void)
static inline s32 LIGHT_PATH_MOVE(void) {
  u32 IntPara;
  dds3Basic_t *v3;
  u32 v4;
  dds3Basic_t *v6;
  dds3Basic_t *pBasic;

  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  v3 = dds3SceneBasicSearch(pBasic, IntPara, 9u);
  v4 = scrGetIntPara(1);
  pBasic = dds3GetActiveScene();
  v6 = dds3SceneBasicSearch(pBasic, v4, 0xFu);
  evtPathLinkAndMake(v6, v3);
  return 1;
}

// 0x1a0fa70: s32 LIGHT_PATH_WAIT(void)
static inline s32 LIGHT_PATH_WAIT(void) {
  u32 IntPara;
  dds3Basic_t *v3;
  u32 v4;
  dds3Basic_t *pBasic;

  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  v3 = dds3SceneBasicSearch(pBasic, IntPara, 9u);
  v4 = evtCheckPathStat(v3) + 1;
  if (v4 <= 2)
    return dword_3E60F68[v4];
  return 0;
}

// 0x1a0fbf0: s32 TEX_BE(void)
#define TEX_BE() (1)

// 0x1a0fc00: s32 TEX_LOAD(void)
static inline s32 TEX_LOAD(void) {
  scrHandle_t *s_hNowpWork_local;
  dds3ProcessID_t *p_ProcessID;
  dds3ProcessID_t *ProcessID;
  char *StrPara;
  dds3ProcessID_t *target;

  s_hNowpWork_local = s_hNowpWork;
  if (!s_hNowpWork_local)
    return 1;
  ProcessID = s_hNowpWork_local->ProcessID;
  p_ProcessID = &s_hNowpWork_local->ProcessID;
  if (!ProcessID)
    return 1;
  StrPara = scrGetStrPara(0);
  target = StartProcess(11004, StrPara);
  dds3LinkProcess(p_ProcessID, target);
  scrSetdds3ProcessIDReturnValue(target);
  return 1;
}

// 0x1a0fd60: s32 TEX_ON(void)
static inline s32 TEX_ON(void) {
  s32 IntPara;
  dds3ProcessID_t *id;

  IntPara = scrGetIntPara(0);
  id = dds3SearchProcessID(IntPara);
  if (dds3ExistProcess(id))
    evtPictureDrawOn(id);
  return 1;
}

// 0x1a0fe20: s32 TEX_OFF(void)
static inline s32 TEX_OFF(void) {
  s32 IntPara;
  dds3ProcessID_t *id;

  IntPara = scrGetIntPara(0);
  id = dds3SearchProcessID(IntPara);
  if (dds3ExistProcess(id))
    evtPictureDrawOff(id);
  return 1;
}

// 0x1a0fee0: s32 TEX_CLS(void)
static inline s32 TEX_CLS(void) {
  s32 IntPara;
  dds3ProcessID_t *id;

  IntPara = scrGetIntPara(0);
  id = dds3SearchProcessID(IntPara);
  if (dds3ExistProcess(id))
    KillProcess(id);
  return 1;
}

// 0x1a0ffa0: s32 SET_SKY(void)
static inline s32 SET_SKY(void) {
  s32 IntPara;
  s32 v5;
  s32 v6;

  dds3FilterSetAnime(0);
  gFilterAlpha = 128;
  IntPara = scrGetIntPara(0);
  v5 = scrGetIntPara(1);
  v6 = scrGetIntPara(2);
  dds3FilterSet(IntPara, v5, v6);
  return 1;
}

// 0x1a10100: s32 SET_SKY_A(void)
static inline s32 SET_SKY_A(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;
  s32 v4;

  IntPara = scrGetIntPara(1);
  if (IntPara <= -255)
    v2 = -255;
  else
    v2 = IntPara;
  if (v2 >= 255)
    v3 = 255;
  else
    v3 = v2;
  v4 = scrGetIntPara(0);
  evtSetAlpha(v4, v3);
  return 1;
}

// 0x1a101b0: s32 BOKASI_ON(void)
static inline s32 BOKASI_ON(void) {
  fldbokasi = 1;
  return 1;
}

// 0x1a10210: s32 BOKASI_OFF(void)
static inline s32 BOKASI_OFF(void) {
  fldbokasi = 0;
  return 1;
}

// 0x1a10260: s32 LOAD_SOUND_E(void)
static inline s32 LOAD_SOUND_E(void) {
  s32 CommandTimer;
  s32 v5;
  s32 IntPara;

  CommandTimer = scrGetCommandTimer();
  if (!CommandTimer)
  {
    IntPara = scrGetIntPara(0);
    evtLoad(IntPara);
    return 0;
  }
  v5 = scrGetIntPara(0);
  return CheckLoad(v5);
}

// 0x1a10360: s32 BGM_PLAY_E(void)
static inline s32 BGM_PLAY_E(void) {
  s32 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  evtPlayBgm(IntPara, v2);
  return 1;
}

// 0x1a103e0: s32 BGM_TRANS_E(void)
static inline s32 BGM_TRANS_E(void) {
  s32 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  evtTransBgm(IntPara, v2);
  return 1;
}

// 0x1a10460: s32 FADEOUT_E(void)
static inline s32 FADEOUT_E(void) {
  s32 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  evtFadeOutBgm(IntPara, v2);
  return 1;
}

// 0x1a104e0: s32 BGM_VOL_DOWN(void)
static inline s32 BGM_VOL_DOWN(void) {
  p2sdSEStopAll();
  return 1;
}

// 0x1a10560: s32 BGM_VOL_UP(void)
static inline s32 BGM_VOL_UP(void) {
  p2sdSEStopAll();
  return 1;
}

// 0x1a105e0: s32 SE_PLAY_E(void)
static inline s32 SE_PLAY_E(void) {
  s32 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  evtPlaySe(IntPara, v2);
  return 1;
}

// 0x1a10660: s32 SE_STOP_E(void)
static inline s32 SE_STOP_E(void) {
  s32 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  evtStopSe(IntPara, v2);
  return 1;
}

// 0x1a106e0: s32 DIST_BLUR_TEX_BE(void)
#define DIST_BLUR_TEX_BE() (1)

// 0x1a106f0: s32 DIST_BLUR_TEX_DEF(void)
static inline s32 DIST_BLUR_TEX_DEF(void) {
  _SetDefTex(DistortionBlur);
  return 1;
}

// 0x1a10770: s32 DRAWSTOP(void)
static inline s32 DRAWSTOP(void) {
  s32 CommandTimer;
  s32 v3;

  if (scrGetIntPara(0) > 0)
    goto LABEL_4;
  v3 = 1;
LABEL_13:
  DrawFlag |= 0x2000000u;
  return v3;
LABEL_4:
  CommandTimer = scrGetCommandTimer();
  if (CommandTimer < scrGetIntPara(0))
  {
    v3 = 0;
    goto LABEL_13;
  }
  return 1;
}

// 0x1a108a0: s32 TEX2_LOAD(void)
static inline s32 TEX2_LOAD(void) {
  scrHandle_t *s_hNowpWork_local;
  dds3ProcessID_t *p_ProcessID;
  dds3ProcessID_t *ProcessID;
  char *StrPara;
  dds3ProcessID_t *target;

  s_hNowpWork_local = s_hNowpWork;
  if (!s_hNowpWork_local)
    return 1;
  ProcessID = s_hNowpWork_local->ProcessID;
  p_ProcessID = &s_hNowpWork_local->ProcessID;
  if (!ProcessID)
    return 1;
  StrPara = scrGetStrPara(0);
  target = evtPictureStartProcess3(11004, StrPara, "");
  dds3LinkProcess(p_ProcessID, target);
  scrSetIntReturnValue(target->id);
  return 1;
}

// 0x1a10a10: s32 TEX2_CHK(void)
static inline s32 TEX2_CHK(void) {
  s32 IntPara;
  s32 v3;
  dds3ProcessID_t *id;

  IntPara = scrGetIntPara(0);
  id = dds3SearchProcessID(IntPara);
  if (dds3ExistProcess(id) && evtPictureLoadCheckProcess(id))
  {
    v3 = 1;
  }
  else
  {
    v3 = 0;
  }
  scrSetIntReturnValue(v3);
  return 1;
}

// 0x1a10b10: s32 TEX2_POS(void)
static inline s32 TEX2_POS(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;
  dds3ProcessID_t *id;

  IntPara = scrGetIntPara(0);
  id = dds3SearchProcessID(IntPara);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  if (dds3ExistProcess(id))
    evtPictureSetDrawPos(id, v2, v3);
  return 1;
}

// 0x1a10c00: s32 TEX2_COL(void)
static inline s32 TEX2_COL(void) {
  s32 IntPara;
  s32 v2;
  s32 v3;
  s32 v4;
  s32 v5;
  dds3ProcessID_t *id;

  IntPara = scrGetIntPara(0);
  id = dds3SearchProcessID(IntPara);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  v4 = scrGetIntPara(3);
  v5 = scrGetIntPara(4);
  if (dds3ExistProcess(id))
    evtPictureSetDrawCol(id, v2, v3, v4, v5);
  return 1;
}

// 0x1a10d20: s32 CUTIN_DSP(void)
static inline s32 CUTIN_DSP(void) {
  s32 IntPara;
  s32 v5;
  s32 v6;
  u32 v7;
  dds3ProcessID_t *PIDfromUID;
  dds3ProcessID_t *v9;
  dds3ProcessID_t *ProcessID;
  s32 id;

  if (!s_hNowpWork)
    return 1;
  IntPara = scrGetIntPara(0);
  v5 = scrGetIntPara(1);
  v6 = scrGetIntPara(2);
  v7 = scrGetIntPara(3);
  PIDfromUID = evtGetPIDfromUID(v7);
  if (!PIDfromUID)
  {
    ProcessID = s_hNowpWork->ProcessID;
    evtStartCommand(ProcessID, IntPara, v5, v6, v7);
    id = evtGetPIDfromUID(v7)->id;
    goto LABEL_22;
  }
  v9 = PIDfromUID;
  if (evtPictureLoadCheckProcess(PIDfromUID))
    return 1;
  id = v9->id;
LABEL_22:
  scrSetIntReturnValue(id);
  return 0;
}

// 0x1a10f30: s32 CUTIN_CLS(void)
static inline s32 CUTIN_CLS(void) {
  s32 IntPara;
  dds3ProcessID_t *v3;
  dds3ProcessID_t *id;

  IntPara = scrGetIntPara(0);
  id = dds3SearchProcessID(IntPara);
  if (!id)
    return 1;
  if (!dds3ExistProcess(id))
    return 1;
  v3 = id;
  evtEndCommand(v3);
  return 1;
}

// 0x1a11050: s32 RAIN_START(void)
static inline s32 RAIN_START(void) {
  s32 v2;

  v2 = evtCheckRain();
  if (v2)
    return v2 != 1;
  evtStartRain(0);
  return 0;
}

// 0x1a11100: s32 RAIN_END(void)
static inline s32 RAIN_END(void) {
  evtEndRain();
  return 1;
}

// 0x1a11180: s32 STORY_SAVE(void)
static inline s32 STORY_SAVE(void) {
  switch (s_stat)
  {
    case 2:
      if (fmProcessChk())
        return 0;
      dds3FadeIn(0, 0, 0, 0);
      s_stat = 0;
      return 1;
    case 1:
      dds3FadeIn(0, 0, 0, 0);
      goto LABEL_15;
    case 0:
      slSetTmnlID(2, 0);
      fmProcTrigSequence(0);
LABEL_15:
      ++s_stat;
      return 0;
  }
  return 1;
}

// 0x1a11310: s32 PMV_LAST_SKIPSTAT(void)
#define PMV_LAST_SKIPSTAT() (1)

// 0x1a11320: s32 DLC_CHECK(void)
static inline s32 DLC_CHECK(void) {
  s32 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = fldCheckDlcData(IntPara);
  scrSetIntReturnValue(v2);
  return 1;
}

// 0x1a113c0: s32 MODEL_DSP_NCUTIN(void)
static inline s32 MODEL_DSP_NCUTIN(void) {
  s32 IntPara;
  void *Instance;

  IntPara = scrGetIntPara(0);
  Instance = get_Instance(0);
  NCutInReq(Instance, IntPara, 0);
  return 1;
}

// 0x1a11460: s32 LOAD_EVENT_MSG(void)
static inline s32 LOAD_EVENT_MSG(void) {
  s32 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  if (IntPara)
  {
    RemovePM1LocalizeText(v2);
    return 1;
  }
  else
  {
    LoadPM1LocalizeText(v2);
    return 1;
  }
}

// 0x1a11540: s32 CHECK_ESCAPE(void)
static inline s32 CHECK_ESCAPE(void) {
  s32 v2;

  if (sBtlCheckEndTimeUp() || sBtlCheckEndEscape() != 1)
  {
    v2 = 0;
  }
  else
  {
    v2 = 1;
  }
  scrSetIntReturnValue(v2);
  return 1;
}

// 0x1a115e0: s32 SET_EVE_MOVE_COLLISION_ENABLE(void)
static inline s32 SET_EVE_MOVE_COLLISION_ENABLE(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  IsEvtMoveCollisionCheck = IntPara == 1;
  return 1;
}

// 0x1a02960
dds3Basic_t *evtSearchBasic(BASIC_TYPE type, s32 serial) {
  dds3Basic_t *pBasic;

  pBasic = dds3GetActiveScene();
  return dds3SceneBasicSearch(pBasic, serial, type);
}

// 0x1a053b0
static void KutiFunction(void) {

}

// 0x1a05420
void evtLipsExecFunction(s32 unit_uniqid, s32 motion_no) {
  void *workdata;
  s64 v6;
  s64 v7;
  s64 naturalAligment;
  dds3ModelHandle_t *v9;

  if (unit_uniqid)
  {
    workdata = dds3GetActiveScene()->workdata;
    if (!workdata)
    {
LABEL_10:
      v7 = *(u64 *)(*((u64 *)workdata[1].monitor + 9) + 32);
      if (!v7)
        return;
      while (1)
      {
        workdata = *(void *)(v7 + 48);
        if (workdata)
        {
          if (workdata->klass->_2.naturalAligment < (u32)naturalAligment || workdata->klass->_2.typeHierarchy[naturalAligment - 1] != Project_Basic_dds3UnitObjectBasicWorkData_t)
          {
            goto LABEL_28;
          }
        }
        v9 = *((dds3ModelHandle_t *)workdata[2].monitor + 5);
        if (sdfModelGetUniqueID(v9->modelRoot) == unit_uniqid)
          break;
        v7 = *(u64 *)(v7 + 72);
        if (!v7)
          return;
      }
      workdata = *(void *)(v7 + 48);
      {
        if (workdata[2].klass)
        {
          if (mdlGetNumOfCut(v9, 2) > motion_no)
            CallKutiMotionUnitID = unit_uniqid;
        }
        return;
      }
LABEL_28:
    }
    if (workdata->klass->_2.naturalAligment < (u32)v6 || workdata->klass->_2.typeHierarchy[v6 - 1] != dds3SceneBasic_t)
    {
      goto LABEL_28;
    }
    goto LABEL_10;
  }
}

// 0x1a05670
void evtLipsStopFunction(s32 motion_no) {
  void *workdata;
  s64 v3;
  s64 v4;
  s64 naturalAligment;
  dds3ModelHandle_t *v6;

  if (CallKutiMotionUnitID)
  {
    workdata = dds3GetActiveScene()->workdata;
    if (!workdata)
    {
LABEL_10:
      v4 = *(u64 *)(*((u64 *)workdata[1].monitor + 9) + 32);
      if (!v4)
        return;
      while (1)
      {
        workdata = *(void *)(v4 + 48);
        if (workdata)
        {
          if (workdata->klass->_2.naturalAligment < (u32)naturalAligment || workdata->klass->_2.typeHierarchy[naturalAligment - 1] != Project_Basic_dds3UnitObjectBasicWorkData_t)
          {
            goto LABEL_28;
          }
        }
        v6 = *((dds3ModelHandle_t *)workdata[2].monitor + 5);
        if (sdfModelGetUniqueID(v6->modelRoot) == CallKutiMotionUnitID)
          break;
        v4 = *(u64 *)(v4 + 72);
        if (!v4)
          return;
      }
      workdata = *(void *)(v4 + 48);
      {
        if (workdata[2].klass)
        {
          if (mdlGetNumOfCut(v6, 2))
            CallKutiMotionUnitID = 0;
        }
        return;
      }
LABEL_28:
    }
    if (workdata->klass->_2.naturalAligment < (u32)v3 || workdata->klass->_2.typeHierarchy[v3 - 1] != dds3SceneBasic_t)
    {
      goto LABEL_28;
    }
    goto LABEL_10;
  }
}

// 0x1a058d0
dds3ModelHandle_t *evtGetLipModel(s32 unit_uniqid) {
  void *workdata;
  dds3ModelHandle_t *v4;
  s64 naturalAligment;
  s64 v7;
  s64 v8;

  if (!unit_uniqid)
    return 0;
  workdata = dds3GetActiveScene()->workdata;
  if (workdata)
  {
    if (workdata->klass->_2.naturalAligment < (u32)naturalAligment || workdata->klass->_2.typeHierarchy[naturalAligment - 1] != dds3SceneBasic_t)
    {
      goto LABEL_23;
    }
  }
  v7 = *(u64 *)(*((u64 *)workdata[1].monitor + 9) + 32);
  if (v7)
  {
    while (1)
    {
      workdata = *(void *)(v7 + 48);
      if (workdata)
      {
        if (workdata->klass->_2.naturalAligment < (u32)v8 || workdata->klass->_2.typeHierarchy[v8 - 1] != Project_Basic_dds3UnitObjectBasicWorkData_t)
        {
          break;
        }
      }
      v4 = *((dds3ModelHandle_t *)workdata[2].monitor + 5);
      if (sdfModelGetUniqueID(v4->modelRoot) != unit_uniqid)
      {
        v7 = *(u64 *)(v7 + 72);
        if (v7)
          continue;
      }
      return v4;
    }
LABEL_23:
  }
  return 0;
}

// 0x1a071d0
static f32 sub_r360_lr(f32 a, f32 b) {
  _BOOL4 v3;
  f32 v4;
  f32 v5;

  v3 = a < 0.0;
  if (b < 0.0)
    v3 = 1;
  if (v3)
  {
    a = a + 360.0;
    b = b + 360.0;
  }
  if (a == INFINITY)
    v4 = -128.0;
  else
    v4 = ((s32)a % 360);
  if (b == INFINITY)
    v5 = -128.0;
  else
    v5 = ((s32)b % 360);
  if ((f32)(v4 - v5) > 180.0 || (f32)(v4 - v5) < -180.0)
  {
    if (v4 < v5)
      return v5 - (f32)(v4 + 360.0);
    v5 = v5 + 360.0;
  }
  return v5 - v4;
}

// 0x1a0ac50
static void CallBattleSub(s32 encno, s32 eventno) {
  SequenceParameter *v5;
  SBTLMAIN_DATA *v9;
  SBTLMAIN_DATA *p_CallData5;
  SBTLMAIN_DATA *CallData5;
  SBTLMAIN_DATA *v13;
  sdfVector4_t *p_pos;
  s32 v15;
  SBTLMAIN_DATA *v16;
  sdfVector4_t *p_rot;
  SBTLMAIN_DATA *v18;
  SBTLMAIN_DATA *v20;
  SBTLMAIN_DATA *v25;
  s32 v26;

  v5 = Allocate(SequenceParameter);
  _ctor(v5, 0);
  wk->evtEncountNo = encno;
  mapRndEncParamSet();
  SE(15);
  encStart(0);
  v9 = Allocate(SBTLMAIN_DATA);
  _ctor(v9, 0);
  v5->CallData5 = v9;
  p_CallData5 = &v5->CallData5;
  CallData5 = v5->CallData5;
  CallData5->encountno = encno;
  CallData5->type = 1;
  vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
  v13 = p_CallData5;
  p_pos = &v13->pos;
  v15 = (u8)byte_5755EF5;
  *p_pos = vct_A;
  if (v15)
    goto LABEL_13;
  goto LABEL_54;
  if (v26)
  {
LABEL_13:
    goto LABEL_14;
  }
LABEL_54:
LABEL_14:
  vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
  v16 = p_CallData5;
  p_rot = &v16->rot;
  *p_rot = vct_A;
  v18 = p_CallData5;
  *(u64 *)&v18->offset_x = 0;
  *(u32 *)&v18->mode = -65536;
  if (encno == 31)
  {
    v18->mode = 1;
LABEL_18:
    goto LABEL_19;
  }
  else if ((byte_5756782 & 1) != 0)
  {
    goto LABEL_18;
  }
LABEL_19:
  if ((GBWK->EventBit[5] & 2) == 0)
    goto LABEL_28;
  if ((GBWK->EventBit[5] & 8) != 0)
    goto LABEL_28;
  goto LABEL_27;
  if ((GBWK->EventBit[5] & 8) == 0)
LABEL_27:
    p_CallData5->mode = 2;
LABEL_28:
  v20 = p_CallData5;
  if ((GBWK->EventBit[93] & 0x20000) != 0)
  {
    v20->mode = 3;
    v20->stock_id = datGetStockDevilIndex(GBWK->mapSummonID, GBWK->mapSummonUNIQ);
    v25 = p_CallData5;
    *(u64 *)&v25->type2 = 0;
    v25->EnemyID = 0;
LABEL_34:
    NextEventNo = eventno;
    goto LABEL_35;
  }
  else
  {
    *(u64 *)&v20->type2 = 0;
    v20->EnemyID = 0;
    goto LABEL_34;
  }
  NextEventNo = eventno;
LABEL_35:
  HukidashiDisp = 0;
  sBtlCountClear();
  dds3AdminiCallSequence(19, v5, 0);
  scrAllReleaseScript();
}

// 0x1a0b310
static void CallBattleSub2(s32 encno) {
  SequenceParameter *v3;
  SBTLMAIN_DATA *v4;
  SBTLMAIN_DATA *p_CallData5;
  SBTLMAIN_DATA *v7;
  sdfVector4_t *p_pos;
  s32 v9;
  SBTLMAIN_DATA *v10;
  sdfVector4_t *p_rot;
  SBTLMAIN_DATA *v12;
  SBTLMAIN_DATA *v13;
  s32 v16;

  v3 = Allocate(SequenceParameter);
  _ctor(v3, 0);
  encStart(0);
  v4 = Allocate(SBTLMAIN_DATA);
  _ctor(v4, 0);
  v3->CallData5 = v4;
  p_CallData5 = &v3->CallData5;
  v3->CallData5->encountno = encno;
  vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
  v7 = p_CallData5;
  p_pos = &v7->pos;
  v9 = (u8)byte_5755EF5;
  *p_pos = vct_A;
  if (v9)
    goto LABEL_11;
  goto LABEL_27;
  if (v16)
  {
LABEL_11:
    goto LABEL_12;
  }
LABEL_27:
LABEL_12:
  vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
  v10 = p_CallData5;
  p_rot = &v10->rot;
  *p_rot = vct_A;
  v12 = p_CallData5;
  *(u64 *)&v12->offset_x = 0;
  fldEncountParamSet(v12);
  v13 = p_CallData5;
  *(u64 *)&v13->type2 = 0;
  v13->encountno = encno;
  v13->EnemyID = 0;
  NextEventNo = 0;
  HukidashiDisp = 0;
  sBtlCountClear();
  dds3AdminiCallSequence(19, v3, 0);
  scrAllReleaseScript();
}

// 0x1a0efc0
static dds3Basic_t *GetPathBasic(void) {
  u32 IntPara;
  dds3Basic_t *result;
  _BOOL4 v4;
  u32 v5;
  u32 v8;
  u32 v11;
  u32 v14;
  u32 v17;
  s32 v20;
  dds3Basic_t *pBasic;

  IntPara = scrGetIntPara(0);
  pBasic = dds3GetActiveScene();
  result = dds3SceneBasicSearch(pBasic, IntPara, 4u);
  v4 = result == 0;
  if (!result)
  {
    v5 = scrGetIntPara(0);
    pBasic = dds3GetActiveScene();
    result = dds3SceneBasicSearch(pBasic, v5, 5u);
    v4 = result == 0;
    if (result)
      goto LABEL_36;
    v8 = scrGetIntPara(0);
    pBasic = dds3GetActiveScene();
    result = dds3SceneBasicSearch(pBasic, v8, 6u);
    v4 = result == 0;
    if (result)
      goto LABEL_36;
    v11 = scrGetIntPara(0);
    pBasic = dds3GetActiveScene();
    result = dds3SceneBasicSearch(pBasic, v11, 7u);
    v4 = result == 0;
    if (result)
      goto LABEL_36;
    v14 = scrGetIntPara(0);
    pBasic = dds3GetActiveScene();
    result = dds3SceneBasicSearch(pBasic, v14, 8u);
    v4 = result == 0;
    if (result)
      goto LABEL_36;
    v17 = scrGetIntPara(0);
    pBasic = dds3GetActiveScene();
    result = dds3SceneBasicSearch(pBasic, v17, 9u);
    v4 = result == 0;
    goto LABEL_36;
  }
LABEL_36:
  if (v4)
  {
    v20 = scrGetIntPara(0);
    return fldGetMatter_From_ModelRangeID(v20);
  }
  return result;
}
