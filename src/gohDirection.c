#include "types.h"
#include "achievement.h"
#include "cfg.h"
#include "cmpstatus.h"
#include "dat.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3objectbase.h"
#include "dds3scenebasic.h"
#include "dds3worldbasic.h"
#include "dvl.h"
#include "evtbit.h"
#include "evtviewer.h"
#include "fclmisc.h"
#include "fclmsg.h"
#include "gohaccident.h"
#include "gohcalc.h"
#include "gohcombunity.h"
#include "gohdirection.h"
#include "gohinit.h"
#include "gohmain.h"
#include "gohmenu.h"
#include "gohrenken.h"
#include "itf.h"
#include "jmsmisc.h"
#include "kernel.h"
#include "mdl.h"
#include "meslogmain.h"
#include "rspecialskill.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlvisual.h"
#include "sbtlweapon.h"
#include "scr.h"
#include "scrcommand.h"
#include "sdat.h"
#include "sdf_vu0.h"
#include "sdfmodel.h"
#include "sdfsound.h"
#include "slmain.h"
#include "sndat3.h"

#define MODEL_MAJOR_NO 7
#define HELPER_PB_NAME "elv.PB"
#define LIGHT1_PB_NAME "devil.PB"
#define LIGHT2_PB_NAME "devil.PB"
#define LIGHT3_PB_NAME "devil.PB"
#define DEVIL_POS_LEFT 31
#define DEVIL_POS_RIGHT 32
#define BIRTH_POS 33
#define CAMERA_NORMAL 0
#define CAMERA_LARGE 1
#define SKIP_LIMIT_FRAME 1109
#define SPLIT_FRAME 1110
#define NORMAL_MSG_FRAME 1530
#define MODEL_MAJOR_NO_KATANA 6
#define MODEL_MINOR_NO_KATANA 79
#define MODEL_MINOR_NO_MATERIAL 45
#define ACCIDENT_MSG_FRAME 1260
#define MAIN_COMBINE_50 50
#define MAIN_COMBINE_LETTER 50

typedef enum {
    GOH_SEQ_DI_ROOT = 0,
    GOH_SEQ_DI_DIRECTION2 = 1,
    GOH_SEQ_DI_DIRECTION_RESULT = 2,
    GOH_SEQ_DI_DIRECTION_END = 3,
    GOH_SEQ_DI_DIRECTION_END2 = 4,
    GOH_SEQ_DI_OMOIDE_SKILL = 5,
    GOH_SEQ_DI_SPIRIT_SET = 6,
    GOH_SEQ_DI_NEW_SWORD_SKL_SET = 7,
    GOH_SEQ_DI_EQUIP_SWORD = 8,
    GOH_SEQ_DI_BAK_NML_COMB = 9,
    GOH_SEQ_DI_BAK_BAK_COMB = 10,
    GOH_SEQ_DI_BAK_SEARCH_COMB = 11,
    GOH_SEQ_DI_BAK_TREE = 12,
} GOH_SEQ_DI;

typedef enum {
    OmoCalcState_Init = 0,
    OmoCalcState_CompCheck = 1,
    OmoCalcState_MitamaChack = 2,
    OmoCalcState_MitamaYNCheck = 3,
    OmoCalcState_OmoSetCall = 4,
    OmoCalcState_OmoMesWait = 5,
    OmoCalcState_OmoSetWait = 6,
    OmoCalcState_OmoEndMesCall = 7,
    OmoCalcState_OmoEndMesWait = 8,
    OmoCalcState_OmoEndFadeOut = 9,
    OmoCalcState_OmoEndFadeCheck = 10,
    OmoCalcState_StateEndCheck = 11,
    OmoCalcState_StateEndFadeIn = 12,
    OmoCalcState_GiftCheck = 13,
    OmoCalcState_GiftScript = 14,
    OmoCalcState_GiftFadeCheck = 15,
    OmoCalcState_StateStartFadeIn = 16,
    OmoCalcState_OmoCompFadeCheck = 17,
    OmoCalcState_DvlReportStart = 18,
    OmoCalcState_DvlReportScript = 19,
    OmoCalcState_End = 20,
} OmoCalcState;

typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct gohData_t gohData_t;
typedef struct jmsSeqUnit_t jmsSeqUnit_t;
typedef struct message_tag message_tag;

s8 s_CameraTable[139];
static jmsSeqUnit_t *gohSeqUnit;
bool is_Direction2;
s32 is_CombineFlag;

u32 GetDevilSE(s32 devilID, s32 motionID);

// 0x1b9cd30
void gohSetModelScale(s32 DevilID, dds3ModelHandle_t *Model) {
  f32 gohScale;
  f32 v6;
  f32 v7;
  f32 *p_x;

  gohScale = sBtlGetVisualDataZ(DevilID)->gohScale;
  v6 = sBtlGetVisualDataZ(DevilID)->gohScale;
  v7 = sBtlGetVisualDataZ(DevilID)->gohScale;
  p_x = &vf00.x;
  p_x[4] = gohScale;
  p_x[5] = v6;
  p_x[6] = v7;
  p_x[7] = 1.0;
  mdlSetScale(Model);
}

// 0x1b9ce90
void gohModelFree(gohData_t *pData) {
  dds3ModelHandle_t *DevilModel;
  dds3ModelHandle_t *v4;
  dds3ModelHandle_t *v5;
  dds3ModelHandle_t *v6;

  DevilModel = pData->pDirData->DevilModel;
  v4 = DevilModel[0];
  if (v4)
  {
    Free(v4);
    DevilModel = pData->pDirData->DevilModel;
  }
  v5 = DevilModel[1];
  if (v5)
  {
    Free(v5);
    DevilModel = pData->pDirData->DevilModel;
  }
  v6 = DevilModel[2];
  if (v6)
  {
    Free(v6);
  }
}

// 0x1b9cf90
void gohModelLightSet(char *pUnitPbName, dds3ModelHandle_t *Model) {
  evtUnitHandle_t *v5;
  dds3Basic_t *v7;
  void *workdata;
  sdf3DLightParallelPacket_t *methodPtr;
  dds3Basic_t *scene;

  v5 = Allocate(evtUnitHandle_t);
  _ctor(v5, 0);
  if (Model)
  {
    scene = dds3GetActiveScene();
    v7 = dds3SceneBasicSearchName(scene, pUnitPbName);
    scene = v7;
    if (!v7)
      return;
    workdata = v7->workdata;
    methodPtr = workdata[2].klass->vtable._1_Finalize.methodPtr;
    if (methodPtr)
    {
      mdlSetLight(Model, methodPtr);
    }
    return;
  }
}

// 0x1b9d140
s32 gohInit(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  Il2CppObject *Instance;
  Il2CppObject *v6;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  Instance = _get_Instance();
  CombBackActive(Instance, 0, 0);
  v6 = _get_Instance();
  CombiActive(v6, 0, 0);
  if (ProcessData->m_eCombineType != 2 && ProcessData->BirthDevil)
  {
    gohAppendNewDevil(ProcessData);
  }
  return 1;
}

// 0x1b9d2a0
s32 gohDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1b9d2b0
s32 Direction2Init(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 v5;
  Il2CppObject *Instance;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (LODWORD(ProcessData[13].klass) == 2)
  {
    v5 = 2;
    goto LABEL_14;
  }
  else
  {
    v5 = LOBYTE(ProcessData[20].klass) != 0;
    goto LABEL_14;
  }
LABEL_14:
  is_CombineFlag = v5;
  is_Direction2 = 1;
  gAns = 0;
  dds3FadeIn(0, 0, 0, 0x1Eu);
  Instance = _get_Instance();
  CombineProductUiOff(Instance, 0);
  return 1;
}

// 0x1b9d4b0
bool gohIsDirection2(void) {
  return is_Direction2;
}

// 0x1b9d530
s32 gohIsCombineFlag(void) {
  return is_CombineFlag;
}

// 0x1b9d5b0
s32 Direction2Destroy(dds3ProcessID_t *PID) {
  itfSetGuidePMV("", 0);
  is_Direction2 = 0;
  return 1;
}

// 0x1b9d660
dds3ProcessFunc_t Direction2CalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqUnit_t *v5;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  dds3ProcessID_t *v9;
  _BOOL4 v10;
  dds3ProcessID_t *v13;
  void *Instance;
  dds3ProcessID_t *v16;
  s32 v17;
  dds3ProcessID_t *v18;
  jmsSeqUnit_t *gohSeqUnit_local;
  dds3Basic_t *basic;
  dds3ProcessID_t *id;

  id = PID;
  basic = 0;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = &ProcessData[2];
  monitor = ProcessData[1].monitor;
  v7 = id;
  v8 = jmsSeqChange(monitor, &ProcessData[2], 0, v7);
  if (v8)
    return v8;
  basic = dds3GetActiveScene();
  if (basic)
  {
    dds3SceneBasicVisible(basic, 1);
  }
  v9 = ProcessData[2].monitor;
  if (evtSetFrame(v9, -1) <= 1108)
  {
    if (cfgGetConfigGAME(14, 0) == 1)
    {
      v10 = LODWORD(ProcessData[13].klass) != 2;
LABEL_28:
      if (gAns == 2 || v10)
      {
        v13 = ProcessData[2].monitor;
        evtSetFrame(v13, 1110);
        is_Direction2 = 0;
        itfSetGuidePMV("", 0);
        Instance = get_Instance(0);
        uiOffGaugeOff(Instance, 1, 0);
        sndImmediateBgmStop();
        p2sdSEStopAll();
      }
      goto LABEL_45;
    }
    v10 = 0;
    goto LABEL_28;
  }
LABEL_45:
  v16 = ProcessData[2].monitor;
  if (LODWORD(ProcessData[13].klass) == 2)
    v17 = 1060;
  else
    v17 = 1110;
  if (evtSetFrame(ProcessData[2].monitor, -1) < v17)
    return v8;
  v18 = ProcessData[2].monitor;
  evtSetFrame(v18, 1110);
  gohSeqUnit_local = gohSeqUnit;
  jmsSeqJumpAndFree(v5, &gohSeqUnit_local[2]);
  return v8;
}

// 0x1b9db00
dds3ProcessFunc_t Direction2DrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ModelHandle_t *v5;
  Il2CppObject *ModelHandle;
  Il2CppObject *v8;
  s64 v10;
  dds3ModelHandle_t *v11;
  dds3ModelHandle_t *v12;
  dds3ModelHandle_t *v14;
  dds3ModelHandle_t *v15;
  dds3ModelHandle_t *v16;
  dds3ModelHandle_t *v18;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v20;
  dds3Basic_t *scene;
  dds3Basic_t *pObjectBasic;
  dds3ProcessID_t *id;

  id = PID;
  pObjectBasic = 0;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = Allocate(dds3ModelHandle_t);
  _ctor(v5, 0);
  scene = dds3GetActiveScene();
  pObjectBasic = dds3SceneBasicSearchName(scene, "elv.PB");
  if (pObjectBasic)
  {
    ModelHandle = dds3ObjectBaseGetModelHandle(pObjectBasic);
    v8 = ModelHandle;
    v10 = *((u64 *)ProcessData[19].monitor + 3);
    v11 = *(dds3ModelHandle_t *)(v10 + 32);
    if (v11)
    {
      gohModelLightSet("devil.PB", v11);
      sdfModelGetMarkPos(v8[4].klass, 31);
      v12 = *(dds3ModelHandle_t *)(*((u64 *)ProcessData[19].monitor + 3) + 32);
      mdlSetPosition(v12);
      v14 = *(dds3ModelHandle_t *)(*((u64 *)ProcessData[19].monitor + 3) + 32);
      Link(v14, ModelOt[0]);
      v10 = *((u64 *)ProcessData[19].monitor + 3);
    }
    v15 = *(dds3ModelHandle_t *)(v10 + 40);
    if (v15)
    {
      gohModelLightSet("devil.PB", v15);
      sdfModelGetMarkPos(v8[4].klass, 32);
      v16 = *(dds3ModelHandle_t *)(*((u64 *)ProcessData[19].monitor + 3) + 40);
      mdlSetPosition(v16);
      v18 = *(dds3ModelHandle_t *)(*((u64 *)ProcessData[19].monitor + 3) + 40);
      Link(v18, ModelOt[0]);
    }
  }
  monitor = ProcessData[1].monitor;
  v20 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 1, v20);
}

// 0x1b9dee0
dds3ProcessFunc_t Direction2UpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1b9e000
s32 gohResultInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *Instance;
  s32 v6;
  dds3ModelHandle_t *v8;
  s16 *monitor;
  s32 v11;
  il2cpp_array_size_t max_length;
  s64 v15;
  bool v16;
  s32 v17;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  Instance = get_Instance(0);
  uiOffGaugeOff(Instance, 1, 0);
  if (LODWORD(ProcessData[13].klass) == 2)
  {
    v6 = *(&ProcessData[24].klass->_1.byval_arg.bits + 1);
    GBWK->IntVariable[200] = 0;
    v8 = *(dds3ModelHandle_t *)(*((u64 *)ProcessData[19].monitor + 3) + 48);
    mdlLoopMotion(v8, 0, v6);
    mdlSetMotionSpeedEx(*(dds3ModelHandle_t *)(*((u64 *)ProcessData[19].monitor + 3) + 48), 0, 0.5);
    return 1;
  }
  monitor = ProcessData[16].monitor;
  v11 = monitor[11];
  if (!monitor[11])
    goto LABEL_37;
  max_length = s_CameraTable->max_length;
  LODWORD(v15) = v11 - 261;
  if (v11 < 336)
    LODWORD(v15) = v11;
  v16 = (s32)v15 >= (s32)max_length || (s32)v15 <= -1;
  v15 = (s32)v15;
  if (v16)
    v15 = 0;
  v17 = (u8)s_CameraTable[v15];
  if (v17 != 1)
  {
    if (v17)
      return 1;
LABEL_37:
    GBWK->IntVariable[200] = 0;
    return 1;
  }
  GBWK->IntVariable[200] = 1;
  return 1;
}

// 0x1b9e400
s32 gohResultDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1b9e410
dds3ProcessFunc_t gohResultCalcProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v8;
  s32 ResultStat;
  dds3ProcessID_t *PmvPID;
  sdatPlayerUnitWork_t *v12;
  u8 *m_pScrData;
  u8 *v15;
  s32 v16;
  s32 TypeCnt;
  gohDirData_t *v18;
  s32 v19;
  dds3ProcessID_t *v20;
  u8 *v21;
  dds3ProcessID_t *started;
  dds3ProcessID_t *p_m_ScrPID;
  s32 v24;
  dds3ProcessID_t *m_ScrPID;
  gohDirData_t *pDirData;
  dds3ProcessID_t *v27;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  SeqHandle = ProcessData->SeqHandle;
  v6 = id;
  v8 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v6);
  if (v8)
    return v8;
  if (ProcessData->m_eCombineType == 2)
  {
    ResultStat = ProcessData->pDirData->ResultStat;
    switch (ResultStat)
    {
      case 2:
LABEL_44:
        gohResultCalcStateFadeOutWait(ProcessData);
        return 0;
      case 1:
LABEL_39:
        m_ScrPID = ProcessData->m_ScrPID;
        if (m_ScrPID)
        {
          if (!gohCheckScrRun(m_ScrPID))
          {
            pDirData = ProcessData->pDirData;
            ProcessData->m_ScrPID = 0;
            ++pDirData->ResultStat;
            return 0;
          }
        }
        break;
      case 0:
        PmvPID = ProcessData->PmvPID;
        if (evtSetFrame(PmvPID, -1) >= 1400)
        {
          v12 = Allocate(sdatPlayerUnitWork_t);
          _ctor(v12, 0);
          ClassCopy(v12, GBWK->player, 0);
          gohGetSwordSkl(ProcessData, v12);
          gohAchievementUnlock(v12);
          m_pScrData = ProcessData->m_pScrData;
          v15 = m_pScrData;
          v16 = 6;
          goto LABEL_33;
        }
        break;
    }
    return v8;
  }
  TypeCnt = gohGetTypeCnt();
  v18 = ProcessData->pDirData;
  v19 = v18->ResultStat;
  if (!TypeCnt)
  {
    switch (v19)
    {
      case 0:
        if (ProcessData->BonusFlag < 0)
        {
          v24 = 1;
          goto LABEL_64;
        }
        v27 = ProcessData->PmvPID;
        if (evtSetFrame(v27, -1) < 1530)
          return v8;
        fclStartMessage(8);
        v18 = ProcessData->pDirData;
        break;
      case 1:
      case 3:
LABEL_36:
        gohResultCalcStateMessageWait(ProcessData);
        return 0;
      case 2:
LABEL_47:
        gohResultCalcStateMessageBirth(ProcessData);
        return 0;
      case 4:
LABEL_53:
        v24 = 6;
        goto LABEL_64;
      case 5:
        goto LABEL_39;
      case 6:
LABEL_50:
        gohResultCalcStateFadeOut(ProcessData);
        return 0;
      case 7:
        goto LABEL_44;
      default:
        return v8;
    }
    goto LABEL_34;
  }
  switch (v19)
  {
    case 0:
      v20 = ProcessData->PmvPID;
      if (evtSetFrame(v20, -1) < 1260)
        return v8;
      v21 = ProcessData->m_pScrData;
      v15 = v21;
      v16 = 1;
      break;
    case 1:
    case 5:
      goto LABEL_39;
    case 2:
      goto LABEL_47;
    case 3:
      goto LABEL_36;
    case 4:
      goto LABEL_53;
    case 6:
      goto LABEL_50;
    case 7:
      goto LABEL_44;
    default:
      return v8;
  }
LABEL_33:
  started = scrStartScript2(1, v15, v16, 1);
  ProcessData->m_ScrPID = started;
  p_m_ScrPID = &ProcessData->m_ScrPID;
  v18 = p_m_ScrPID[22];
LABEL_34:
  v24 = v18->ResultStat + 1;
LABEL_64:
  v18->ResultStat = v24;
  return 0;
}

// 0x1b9f540
dds3ProcessFunc_t gohResultDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ModelHandle_t *v5;
  Il2CppObject *ModelHandle;
  Il2CppObject *v8;
  dds3ModelHandle_t *v10;
  dds3ModelHandle_t *v11;
  dds3ModelHandle_t *v20;
  dds3ModelHandle_t *v21;
  sdfModelOt_t *v23;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v25;
  dds3Basic_t *scene;
  dds3Basic_t *pObjectBasic;
  dds3ProcessID_t *id;

  id = PID;
  pObjectBasic = 0;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = Allocate(dds3ModelHandle_t);
  _ctor(v5, 0);
  scene = dds3GetActiveScene();
  pObjectBasic = dds3SceneBasicSearchName(scene, "elv.PB");
  if (!pObjectBasic)
    goto LABEL_34;
  ModelHandle = dds3ObjectBaseGetModelHandle(pObjectBasic);
  v8 = ModelHandle;
  v10 = *(dds3ModelHandle_t *)(*((u64 *)ProcessData[19].monitor + 3) + 48);
  if (v10)
  {
    gohModelLightSet("devil.PB", v10);
    sdfModelGetMarkPos(v8[4].klass, 33);
    v11 = *(dds3ModelHandle_t *)(*((u64 *)ProcessData[19].monitor + 3) + 48);
    mdlSetPosition(*(dds3ModelHandle_t *)(*((u64 *)ProcessData[19].monitor + 3) + 48));
    if (LODWORD(ProcessData[13].klass) != 2)
      goto LABEL_31;
    __asm { FMOV            V0.4S, #1.0 }
    vct_A = _Q0;
    v20 = *(dds3ModelHandle_t *)(*((u64 *)ProcessData[19].monitor + 3) + 48);
    mdlSetScale(v20);
LABEL_31:
    v21 = *(dds3ModelHandle_t *)(*((u64 *)ProcessData[19].monitor + 3) + 48);
    v23 = ModelOt[0];
    Link(v21, v23);
    goto LABEL_34;
  }
LABEL_34:
  monitor = ProcessData[1].monitor;
  v25 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 1, v25);
}

// 0x1b9f970
dds3ProcessFunc_t gohResultUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  fclUpdateMessage();
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1b9fad0
s32 gohEndInit(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1b9fae0
s32 gohEndDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1b9faf0
dds3ProcessFunc_t gohEndCalcProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqUnit_t *p_pSeqUnit;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  jmsSeqUnit_t *gohSeqUnit_local;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  p_pSeqUnit = &ProcessData->pSeqUnit;
  SeqHandle = ProcessData->SeqHandle;
  v7 = id;
  v8 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v7);
  if (v8)
    return v8;
  if (!!dds3FadeCheck())
    return v8;
  gohModelFree(ProcessData);
  gohSeqUnit_local = gohSeqUnit;
  jmsSeqJumpAndFree(p_pSeqUnit, &gohSeqUnit_local[4]);
  return 0;
}

// 0x1b9fce0
dds3ProcessFunc_t gohEndDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 1, v6);
}

// 0x1b9fe00
dds3ProcessFunc_t gohEndUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1b9ff20
s32 gohEnd2Init(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  p2sdSndStopAll();
  if (!ProcessData)
  gohBgmLoad(ProcessData);
  return 1;
}

// 0x1ba0060
s32 gohEnd2Destroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1ba0070
dds3ProcessFunc_t gohEnd2CalcProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqUnit_t *p_pSeqUnit;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  dds3ProcessID_t *PmvPID;
  Il2CppObject *Instance;
  sdatPlayerUnitWork_t *player;
  jmsSeqUnit_t *v16;
  jmsSeqUnit_t *v17;
  jmsSeqUnit_t *gohSeqUnit_local;
  sdatPlayerUnitWork_t *v20;
  jmsSeqUnit_t *v22;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  p_pSeqUnit = &ProcessData->pSeqUnit;
  SeqHandle = ProcessData->SeqHandle;
  v7 = id;
  v8 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v7);
  if (!v8)
  {
    if (gohBgmPlay(ProcessData))
    {
      if (ModelLoad(ProcessData))
        return v8;
      if (p2sdLoadCheckMidi(4259840))
      {
        ProcessData->combStSeq = 0;
        PmvPID = ProcessData->PmvPID;
        evtChgSeq(PmvPID, 3, 0);
        evtIgnoreFade(ProcessData->PmvPID);
        ProcessData->pDirData = 0;
        ProcessStart(0);
        ProcessStart(0);
        if (ProcessData->m_eCombineType != 2)
        {
          gohSeqUnit_local = gohSeqUnit;
          v17 = &gohSeqUnit_local[5];
          goto LABEL_63;
        }
        Instance = _get_Instance();
        ArrTreeOnOff(Instance[16].klass, 0, ProcessData->spSword, 0);
        if (ProcessData->raidouSkl)
        {
          player = GBWK->player;
          if (datRaidouSkillGetMaster(player, tbl[ProcessData->m_iSelectNewSwordNo]->m_hojo))
          {
LABEL_38:
            v16 = gohSeqUnit;
            v17 = &v16[8];
LABEL_63:
            jmsSeqJumpAndFree(p_pSeqUnit, v17);
            return v8;
          }
        }
        else
        {
          v20 = GBWK->player;
          if (datSpiritSkillGetMaster(v20, tbl[ProcessData->m_iSelectNewSwordNo]->m_hojo))
          {
            goto LABEL_38;
          }
        }
        ProcessData->sklSet = 1;
        v22 = gohSeqUnit;
        v17 = &v22[7];
        goto LABEL_63;
      }
      p2sdLoadSMGFile(4259840);
    }
  }
  return v8;
}

// 0x1ba0570
dds3ProcessFunc_t gohEnd2DrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 1, v6);
}

// 0x1ba0690
dds3ProcessFunc_t gohEnd2UpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1ba07b0
s32 gohOmoideSkillInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  LODWORD(ProcessData[13].klass) = 1;
  HIDWORD(ProcessData[21].klass) = 0;
  HIDWORD(ProcessData[20].monitor) = 0;
  HIDWORD(ProcessData[11].klass) = 3;
  return 1;
}

// 0x1ba08a0
s32 gohOmoideSkillDestroy(dds3ProcessID_t *PID) {
  cmpSklTypeSet(0, 0);
  return 1;
}

// 0x1ba0910
dds3ProcessFunc_t gohOmoideSkillCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqUnit_t *v5;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  u32 *v10;
  sdatUnitWork_t *v11;
  sdatUnitWork_t *v12;
  u8 *klass;
  dds3ProcessID_t *started;
  void **p_monitor;
  dds3ProcessID_t *v17;
  dds3ProcessID_t *v18;
  s32 v20;
  Il2CppObject *v21;
  char *v22;
  char *v23;
  s32 v24;
  bool v25;
  s32 v26;
  s32 v27;
  s32 v28;
  long f64 v29;
  u8 *v30;
  dds3ProcessID_t *v32;
  void **v33;
  dds3ProcessID_t *v34;
  dds3ProcessID_t *v35;
  void **v36;
  u8 *v37;
  dds3ProcessID_t *v38;
  void **v39;
  dds3ProcessID_t *v40;
  u32 *v41;
  s32 v42;
  u32 v43;
  s64 StockDevilIndex;
  long f64 v45;
  s64 v46;
  char *v47;
  s32 KarteTrophChkCnt;
  s32 NakamaCount;
  long f64 v50;
  s64 v51;
  char *v52;
  jmsSeqUnit_t *gohSeqUnit_local;
  jmsSeqUnit_t *m_Items;
  s64 v56;
  char *v57;
  s32 monitor_high;
  jmsSeqUnit_t *v60;
  jmsSeqUnit_t *v62;
  jmsSeqUnit_t *v64;
  s32 data;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = &ProcessData[2];
  monitor = ProcessData[1].monitor;
  v7 = id;
  v8 = jmsSeqChange(monitor, &ProcessData[2], 0, v7);
  if (v8)
    return v8;
  v10 = (u32 *)&ProcessData[20].monitor + 1;
  switch (HIDWORD(ProcessData[20].monitor))
  {
    case 0:
      v11 = ProcessData[16].monitor;
      if (datOmoideSkillGetCount(v11))
      {
        gohStartBirthDevilStatus(ProcessData);
        v12 = ProcessData[16].monitor;
        if (datOmoideSkillIsComplete(v12))
        {
          if (!GBWK->omoideMax)
          {
            klass = ProcessData[8].klass;
            started = scrStartScript2(1, klass, 3, 1);
            ProcessData[8].monitor = started;
          }
        }
        *v10 = 16;
      }
      else
      {
        dds3FadeIn(0, 0, 0, 0x1Eu);
        *v10 = 15;
      }
      return v8;
    case 1:
      v18 = ProcessData[8].monitor;
      p_monitor = &ProcessData[8].monitor;
      v17 = v18;
      if (v18)
      {
        if (!gohCheckScrRun(v17))
        {
          *p_monitor = 0;
          GBWK->omoideMax = 1;
        }
      }
      else
      {
        *v10 = 2;
      }
      return v8;
    case 2:
      if (LODWORD(ProcessData[11].monitor) != 5)
        goto LABEL_42;
      fclSetMessageInvalid(1);
      fclStart2(11, 0, 1);
      fclSetSelMes(g_mainPID, 12);
      SetMessagePos(1u);
      fclSetSelCancelPos(1);
      *(void **)((char *)&ProcessData[20].monitor + 4) = &xmmword_0 + 3;
      return v8;
    case 3:
      v20 = Update();
      if (v20 == 1)
      {
        cmpSetEvent(3);
        goto LABEL_153;
      }
      if (!v20)
LABEL_42:
        *v10 = 4;
      return v8;
    case 4:
      data = *((s16 *)ProcessData[16].monitor + 108);
      v21 = Box(s32, &data);
      v22 = Format("{0:D}", v21, 0);
      v23 = Concat_54766928(0, v22, 0);
      fclSetMessageVar(0, v23);
      fclStart1(9, 0);
      *(void **)((char *)&ProcessData[20].monitor + 4) = &xmmword_0 + 5;
      return v8;
    case 5:
      if (!fclChkMessage())
      {
        v24 = LODWORD(ProcessData[21].klass) + 1;
        v25 = LODWORD(ProcessData[21].klass) - 29 < 0;
        LODWORD(ProcessData[21].klass) = v24;
        if (v25 == __OFSUB__(v24, 30))
        {
          cmpSetEvent(1);
          *(u64 *)v10 = 6;
        }
      }
      return v8;
    case 6:
      if (cmpOmoideSkillIsFinish())
      {
        v26 = LODWORD(ProcessData[21].klass) + 1;
        v25 = LODWORD(ProcessData[21].klass) - 29 < 0;
        LODWORD(ProcessData[21].klass) = v26;
        if (v25 == __OFSUB__(v26, 30))
        {
          v27 = ProcessData[1].klass;
          HIDWORD(ProcessData[21].klass) = 0;
          LODWORD(ProcessData[1].klass) = v27 & 0xFFFEFFFF;
          HIDWORD(ProcessData[20].monitor) = 7;
        }
      }
      return v8;
    case 7:
      fclStart2(10, 0, 1);
      SetMessagePos(1u);
      fclSetSelMes(g_mainPID, 12);
      fclSetSelCancelPos(1);
      *(void **)((char *)&ProcessData[20].monitor + 4) = &xmmword_0 + 8;
      return v8;
    case 8:
      v28 = Update();
      if (v28 == 1)
      {
        cmpSetEvent(4);
        *v10 = 6;
      }
      else if (!v28)
      {
LABEL_153:
        *v10 = 9;
      }
      return v8;
    case 9:
      *v10 = 10;
      dds3FadeOut(0, 0, 0, 0x14u);
      return v8;
    case 0xA:
      if (!dds3FadeCheck())
      {
        cmpSetEvent(2);
        *v10 = 11;
      }
      return v8;
    case 0xB:
      if (cmpChkEnd())
        *v10 = 12;
      return v8;
    case 0xC:
      if (gohStopStatusDraw(ProcessData, 0, 0) >= 4)
      {
        dds3FadeIn(0, 0, 0, 0xAu);
        goto LABEL_99;
      }
      return v8;
    case 0xD:
      if (!WORD2(ProcessData[11].monitor))
        goto LABEL_90;
      gohSetLetterCnt(1);
      if (SystemWork->letterCnt < 0x32u)
      {
        v30 = ProcessData[8].klass;
        goto LABEL_87;
      }
      v56 = sub_1A24F60(0, v29);
      v57 = sub_8360(30, Project_DefineAchievementID_string_, v56);
      Unlock_2(v57);
      v30 = ProcessData[8].klass;
LABEL_87:
      v32 = scrStartScript2(1, v30, 2, 1);
      ProcessData[8].monitor = v32;
      SetNoSkipEnd(1);
LABEL_90:
      *v10 = 14;
      return v8;
    case 0xE:
      v35 = ProcessData[8].monitor;
      v33 = &ProcessData[8].monitor;
      v34 = v35;
      if (v35)
      {
        if (!gohCheckScrRun(v34))
        {
          v36 = v33;
          *v33 = 0;
          goto LABEL_120;
        }
      }
      else
      {
        *v10 = 18;
      }
      return v8;
    case 0xF:
      if (!dds3FadeCheck())
LABEL_99:
        *v10 = 13;
      return v8;
    case 0x10:
      if (!cmpGetStartStatusFlag())
      {
        dds3FadeIn(0, 0, 0, 0x1Eu);
        *v10 = 17;
      }
      return v8;
    case 0x11:
      if (!dds3FadeCheck())
        *v10 = 1;
      return v8;
    case 0x12:
      SetNoSkipEnd(1);
      v37 = ProcessData[8].klass;
      v38 = scrStartScript2(1, v37, 10, 1);
      ProcessData[8].monitor = v38;
      v39 = &ProcessData[8].monitor;
      *((u32 *)v39 + 49) = 19;
      return v8;
    case 0x13:
      v40 = ProcessData[8].monitor;
      if (v40)
      {
        if (!gohCheckScrRun(v40))
        {
          ProcessData[8].monitor = 0;
          v36 = &ProcessData[8].monitor;
LABEL_120:
        }
      }
      else
      {
        fclDestroyMessage();
        fclLinkData(ProcessData[3].klass);
        HIDWORD(ProcessData[20].monitor) = 20;
      }
      return v8;
    case 0x14:
      SetNoSkipEnd(0);
      if (!GohCreateAllUnitSortTbl(ProcessData))
        return v8;
      if (HIBYTE(ProcessData[33].monitor))
      {
        (*(ProcessData[34].klass->_1.image + 181))(ProcessData[34].klass, ProcessData[16].monitor, *((u64 *)ProcessData[34].klass->_1.image + 182));
        HIBYTE(ProcessData[33].monitor) = 0;
      }
      v41 = ProcessData[16].monitor;
      v42 = *((s16 *)v41 + 11);
      v43 = v41[70];
      StockDevilIndex = datGetStockDevilIndex(v42, v43);
      Copy_56180528(*((void *)ProcessData[16].monitor + 24), GBWK->player->stock_id[StockDevilIndex]->aOmoideSkill, *(u32 *)(*((u64 *)ProcessData[16].monitor + 24) + 24), 0);
      datCalcNowParam(GBWK->player->stock_id[StockDevilIndex], 0, 0);
      v46 = sub_1A24F60(0, v45);
      v47 = sub_8360(34, Project_DefineAchievementID_string_, v46);
      KarteTrophChkCnt = GetKarteTrophChkCnt(GBWK->karte_list, 0);
      NakamaCount = GetNakamaCount();
      ProgressUnlock_3(v47, KarteTrophChkCnt, NakamaCount);
      LODWORD(v47) = GetKarteTrophChkCnt(GBWK->karte_list, 0);
      if ((s32)v47 >= GetNakamaCount())
      {
        v51 = sub_1A24F60(0, v50);
        v52 = sub_8360(34, Project_DefineAchievementID_string_, v51);
        Unlock_2(v52);
      }
      if (LOBYTE(ProcessData[31].klass))
      {
        gohSeqUnit_local = gohSeqUnit;
        m_Items = &gohSeqUnit_local[11];
        goto LABEL_180;
      }
      if (LODWORD(ProcessData[13].klass) != 1)
        goto LABEL_170;
      monitor_high = HIDWORD(ProcessData[27].monitor);
      if (monitor_high == 4)
      {
        v64 = gohSeqUnit;
        m_Items = &v64[10];
      }
      else if (monitor_high == 1)
      {
        v60 = gohSeqUnit;
        m_Items = &v60[9];
      }
      else
      {
LABEL_170:
        v62 = gohSeqUnit;
        m_Items = v62;
      }
LABEL_180:
      jmsSeqJumpAndFree(v5, m_Items);
      return v8;
    default:
      return v8;
  }
}

// 0x1ba1720
dds3ProcessFunc_t gohOmoideSkillDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t result;
  s32 v8;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[1].monitor;
  v6 = id;
  result = jmsSeqChange(monitor, &ProcessData[2], 1, v6);
  if (!result && HIDWORD(ProcessData[20].monitor) == 6)
  {
    if (cmpCheckSklSet())
      v8 = 13;
    else
      v8 = 14;
    gohSetDispButtonGuide(v8, 1, 0);
    return 0;
  }
  return result;
}

// 0x1ba18f0
dds3ProcessFunc_t gohOmoideSkillUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1ba1a10
s32 gohSpiritInit(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  _BOOL4 raidouSkl;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  ProcessData->m_iStatusType = 7;
  raidouSkl = ProcessData->raidouSkl;
  ProcessData->WorkStat = 0;
  ProcessData->m_eCombineType = 0;
  ProcessData->m_eCombineType2 = 0;
  gohGetSwordSkl(ProcessData, GBWK->player);
  if (raidouSkl)
    return 1;
  fclSetMessageInvalid(1);
  fclStartMessage(30);
  return 1;
}

// 0x1ba1ba0
s32 gohSpiritDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1ba1bb0
dds3ProcessFunc_t gohSpiritCalcProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqUnit_t *p_pSeqUnit;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  dds3ProcessFunc_t result;
  s32 v10;
  s32 v11;
  bool v12;
  s32 WorkStat;
  u8 *m_pScrData;
  dds3ProcessID_t *started;
  dds3ProcessID_t *p_m_ScrPID;
  dds3ProcessID_t *m_ScrPID;
  _BOOL4 raidouSkl;
  jmsSeqUnit_t *gohSeqUnit_local;
  s32 v21;
  _BOOL4 spirit;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  p_pSeqUnit = &ProcessData->pSeqUnit;
  SeqHandle = ProcessData->SeqHandle;
  v7 = id;
  v8 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v7);
  if (v8)
    return v8;
  switch (ProcessData->WorkStat)
  {
    case 0:
      gohStartBirthDevilStatus(ProcessData);
      v10 = 11;
      goto LABEL_68;
    case 1:
      if (fclChkMessage())
        return v8;
      v11 = ProcessData->WorkstatCnt + 1;
      v12 = ProcessData->WorkstatCnt - 29 < 0;
      ProcessData->WorkstatCnt = v11;
      if (v12 != __OFSUB__(v11, 30))
        return v8;
      cmpSetEvent(1);
      WorkStat = ProcessData->WorkStat;
      ProcessData->WorkstatCnt = 0;
      v10 = WorkStat + 1;
      goto LABEL_68;
    case 2:
      if (!cmpOmoideSkillIsFinish())
        return v8;
      ProcessData->Flag &= ~0x10000u;
      goto LABEL_42;
    case 3:
      cmpEquipSwordNoHelp(1);
      m_pScrData = ProcessData->m_pScrData;
      started = scrStartScript2(1, m_pScrData, 9, 1);
      ProcessData->m_ScrPID = started;
      p_m_ScrPID = &ProcessData->m_ScrPID;
      *(dds3ProcessID_t *)((char *)p_m_ScrPID + 196) = (dds3ProcessID_t *)(u32)(*((u32 *)p_m_ScrPID + 49) + 1);
      return 0;
    case 4:
      m_ScrPID = ProcessData->m_ScrPID;
      if (m_ScrPID)
      {
        if (!gohCheckScrRun(m_ScrPID))
        {
          ProcessData->m_ScrPID = 0;
          return 0;
        }
        return v8;
      }
      v21 = ProcessData->WorkstatCnt + 1;
      v12 = ProcessData->WorkstatCnt - 29 < 0;
      ProcessData->WorkstatCnt = v21;
      if (v12 != __OFSUB__(v21, 30))
        return v8;
      spirit = ProcessData->spirit;
      ProcessData->WorkstatCnt = 0;
      if (spirit)
      {
        v10 = 5;
      }
      else
      {
        cmpSetEvent(4);
LABEL_67:
        v10 = 1;
      }
LABEL_68:
      ProcessData->WorkStat = v10;
      result = 0;
      break;
    case 5:
      v10 = 6;
      goto LABEL_68;
    case 6:
      cmpSetEvent(5);
LABEL_42:
      v10 = ProcessData->WorkStat + 1;
      goto LABEL_68;
    case 7:
      goto LABEL_50;
    case 0xA:
      raidouSkl = ProcessData->raidouSkl;
      if (dds3FadeCheck())
        return v8;
      if (!raidouSkl)
        goto LABEL_67;
      cmpSetEvent(5);
LABEL_50:
      gohSeqUnit_local = gohSeqUnit;
      jmsSeqJumpAndFree(p_pSeqUnit, &gohSeqUnit_local[8]);
      return 0;
    case 0xB:
      if (cmpGetStartStatusFlag())
        return v8;
      dds3FadeIn(0, 0, 0, 0x1Eu);
      v10 = 10;
      goto LABEL_68;
    default:
      return v8;
  }
  return result;
}

// 0x1ba20c0
dds3ProcessFunc_t gohSpiritDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t result;
  s32 v8;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[1].monitor;
  v6 = id;
  result = jmsSeqChange(monitor, &ProcessData[2], 1, v6);
  if (!result && HIDWORD(ProcessData[20].monitor) == 2)
  {
    if (cmpCheckSklSet())
      v8 = 13;
    else
      v8 = 14;
    gohSetDispButtonGuide(v8, 1, 0);
    return 0;
  }
  return result;
}

// 0x1ba2290
dds3ProcessFunc_t gohSpiritUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  fclUpdateMessage();
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1ba23f0
s32 gohNewSwordSklInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  *(void **)((char *)&ProcessData[20].monitor + 4) = 0;
  gohGetSwordSkl(ProcessData, GBWK->player);
  return 1;
}

// 0x1ba2520
s32 gohNewSwordSklDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1ba2530
dds3ProcessFunc_t gohNewSwordSklCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqUnit_t *v5;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  s32 klass;
  s32 v11;
  Il2CppObject *Instance;
  s32 v13;
  Il2CppObject *v14;
  void *v15;
  s32 monitor_high;
  jmsSeqUnit_t *gohSeqUnit_local;
  dds3Basic_t *basic;
  dds3ProcessID_t *id;

  id = PID;
  basic = 0;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = &ProcessData[2];
  monitor = ProcessData[1].monitor;
  v7 = id;
  v8 = jmsSeqChange(monitor, &ProcessData[2], 0, v7);
  if (!v8)
  {
    switch (HIDWORD(ProcessData[20].monitor))
    {
      case 0:
        klass = ProcessData[21].klass;
        if (klass < 11)
          goto LABEL_36;
        v11 = 1;
        goto LABEL_35;
      case 1:
        basic = dds3GetActiveScene();
        dds3SceneBasicVisible(basic, 0);
        Instance = _get_Instance();
        CanvasActive(Instance, 0, 0);
        v13 = BYTE3(ProcessData[33].monitor) == 0;
        ProcessStart(v13, 1, 0);
        ++HIDWORD(ProcessData[20].monitor);
        break;
      case 2:
        if (!ProcessCheck())
        {
          v14 = _get_Instance();
          CanvasActive(v14, 1, 0);
          basic = dds3GetActiveScene();
          dds3SceneBasicVisible(basic, 1);
          v15 = get_Instance(0);
          ItfButtonGuideSet(v15, 0, 0);
          monitor_high = HIDWORD(ProcessData[20].monitor);
          LODWORD(ProcessData[21].klass) = 0;
          HIDWORD(ProcessData[20].monitor) = monitor_high + 1;
        }
        break;
      case 3:
        klass = ProcessData[21].klass;
        if (klass >= 11)
        {
          v11 = 4;
LABEL_35:
          HIDWORD(ProcessData[20].monitor) = v11;
        }
LABEL_36:
        LODWORD(ProcessData[21].klass) = klass + 1;
        break;
      case 4:
        gohSeqUnit_local = gohSeqUnit;
        jmsSeqJumpAndFree(v5, &gohSeqUnit_local[8]);
        break;
      default:
        return v8;
    }
  }
  return v8;
}

// 0x1ba28e0
dds3ProcessFunc_t gohNewSwordSklDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 1, v6);
}

// 0x1ba2a00
dds3ProcessFunc_t gohNewSwordSklUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  fclUpdateMessage();
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1ba2b60
s32 gohEquipSwordInit(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  s32 Flag;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  Flag = ProcessData->Flag;
  ProcessData->WorkStat = 0;
  ProcessData->m_eCombineType = 0;
  ProcessData->m_eCombineType2 = 0;
  ProcessData->Flag = Flag & 0xFFFEFFFF;
  ProcessData->m_iStatusType = 6;
  gohStartBirthDevilStatus(ProcessData);
  ProcessData->WorkStat = 10;
  return 1;
}

// 0x1ba2ca0
s32 gohEquipSwordDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1ba2cb0
dds3ProcessFunc_t gohEquipSwordCalcProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
  dds3ProcessFunc_t result;
  u8 *m_pScrData;
  dds3ProcessID_t *started;
  dds3ProcessID_t *m_ScrPID;
  jmsSeqUnit_t *gohSeqUnit_local;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  SeqHandle = ProcessData->SeqHandle;
  v6 = id;
  v7 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v6);
  if (v7)
    return v7;
  switch (ProcessData->WorkStat)
  {
    case 0:
      if (cmpGetStatusStep() != 5)
        return v7;
      ++ProcessData->WorkstatCnt;
      if ((jmsChkCommonInput(3u) & 1) != 0 || ProcessData->WorkstatCnt >= 31)
      {
        ProcessData->WorkstatCnt = 0;
        cmpEquipSwordNoHelp(1);
        m_pScrData = ProcessData->m_pScrData;
        started = scrStartScript2(1, m_pScrData, 7, 1);
        ProcessData->m_ScrPID = started;
        ++ProcessData->WorkStat;
      }
      goto LABEL_35;
    case 1:
      m_ScrPID = ProcessData->m_ScrPID;
      if (!m_ScrPID)
        goto LABEL_35;
      if (gohCheckScrRun(m_ScrPID))
        goto LABEL_35;
      ProcessData->m_ScrPID = 0;
LABEL_34:
      ++ProcessData->WorkStat;
LABEL_35:
      gohStartBirthDevilStatus(ProcessData);
      result = 0;
      break;
    case 2:
      if (!dds3FadeCheck())
        goto LABEL_34;
      goto LABEL_35;
    case 3:
      if (gohStopStatusDraw(ProcessData, 0, 0) < 4)
        return v7;
      goto LABEL_57;
    case 0xA:
      if (cmpGetStartStatusFlag())
        return v7;
      if (!gohSwordShortCutCheck(ProcessData, 0) || ProcessData->sklSet)
      {
        dds3FadeIn(0, 0, 0, 0x1Eu);
      }
LABEL_57:
      ++ProcessData->WorkStat;
      result = 0;
      break;
    case 0xB:
      if (dds3FadeCheck())
        return v7;
      ProcessData->WorkStat = 0;
      result = 0;
      break;
    default:
      gohSeqUnit_local = gohSeqUnit;
      jmsSeqJumpAndFree(&ProcessData->pSeqUnit, &gohSeqUnit_local[12]);
      ProcessData->combEndJump = 1;
      result = 0;
      break;
  }
  return result;
}

// 0x1ba3160
dds3ProcessFunc_t gohEquipSwordDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqUnit_t *v5;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t result;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = &ProcessData[2];
  monitor = ProcessData[1].monitor;
  v7 = id;
  result = jmsSeqChange(monitor, v5, 1, v7);
  if (!result)
  {
    gohSetDispButtonGuide(34, 1, 0);
    return 0;
  }
  return result;
}

// 0x1ba32d0
dds3ProcessFunc_t gohEquipSwordUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  fclUpdateMessage();
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1ba3430
void gohModelLoad(gohData_t *pData) {
  dds3ModelHandle_t *DevilModel;
  dds3ModelHandle_t *v4;
  s32 SelDevil1;
  dds3ModelHandle_t *v6;
  s32 SelDevil2;
  dds3ModelHandle_t *v8;
  dds3ModelHandle_t *v9;
  s32 v11;
  dds3ModelHandle_t *v12;
  dds3ModelHandle_t *v13;
  dds3ModelHandle_t *v14;
  dds3ModelHandle_t *v15;
  dds3ModelHandle_t *v16;
  s32 v18;
  dds3ModelHandle_t *v19;
  s32 devilid;
  s16 v22;
  dds3ModelHandle_t *v23;

  DevilModel = pData->pDirData->DevilModel;
  if (pData->m_eCombineType == 2)
  {
    v4 = mdlLoad(6u, 79);
    if (!v4)
    DevilModel[0] = v4;
    mdlLoopMotion(pData->pDirData->DevilModel[0], 0, 0);
    mdlSetMotionSpeedEx(pData->pDirData->DevilModel[0], 0, 0.5);
    if (pData->m_eCombineType != 2)
      goto LABEL_13;
LABEL_22:
    v13 = pData->pDirData->DevilModel;
    v14 = mdlLoad(6u, 45);
    if (!v14)
      goto LABEL_27;
    goto LABEL_9000;
    if (!v14)
    {
LABEL_27:
      v13[1] = v14;
      mdlLoopMotion(pData->pDirData->DevilModel[1], 0, 0);
      mdlSetMotionSpeedEx(pData->pDirData->DevilModel[1], 0, 1.0);
LABEL_28:
      v15 = pData->pDirData->DevilModel;
      if (pData->m_eCombineType != 2)
        goto LABEL_38;
      goto LABEL_29;
    }
LABEL_9000:
    goto LABEL_27;
  }
  SelDevil1 = pData->SelDevil1;
  v6 = mdlLoad(7u, SelDevil1);
  if (!v6)
  DevilModel[0] = v6;
  mdlLoopMotion(pData->pDirData->DevilModel[0], 0, 0);
  mdlSetMotionSpeedEx(pData->pDirData->DevilModel[0], 0, 0.5);
  v11 = pData->SelDevil1;
  v12 = pData->pDirData->DevilModel[0];
  gohSetModelScale(v11, v12);
  if (pData->m_eCombineType == 2)
    goto LABEL_22;
LABEL_13:
  SelDevil2 = pData->SelDevil2;
  if (SelDevil2 < 1)
    goto LABEL_28;
  v8 = pData->pDirData->DevilModel;
  v9 = mdlLoad(7u, SelDevil2);
  if (!v9)
  v8[1] = v9;
  mdlLoopMotion(pData->pDirData->DevilModel[1], 0, 0);
  mdlSetMotionSpeedEx(pData->pDirData->DevilModel[1], 0, 0.5);
  v18 = pData->SelDevil2;
  v19 = pData->pDirData->DevilModel[1];
  gohSetModelScale(v18, v19);
  v15 = pData->pDirData->DevilModel;
  if (pData->m_eCombineType != 2)
  {
LABEL_38:
    devilid = pData->BirthDevil->devilid;
    v16 = mdlLoad(7u, devilid);
    if (v16)
      goto LABEL_41;
    goto LABEL_42;
  }
LABEL_29:
  v16 = mdlLoad(6u, 79);
  if (v16)
  {
LABEL_41:
  }
LABEL_42:
  v15[2] = v16;
  mdlLoopMotion(pData->pDirData->DevilModel[2], 0, 0);
  mdlSetMotionSpeedEx(pData->pDirData->DevilModel[2], 0, 0.5);
  v22 = pData->BirthDevil->devilid;
  v23 = pData->pDirData->DevilModel[2];
  gohSetModelScale(v22, v23);
}

// 0x1ba3900
dds3ProcessFunc_t gohCalcProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqUnit_t *p_pSeqUnit;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t result;
  Il2CppObject *v9;
  void *v10;
  dds3ProcessID_t *PmvPID;
  s32 TypeCnt;
  s32 v14;
  s32 i;
  s32 TypeNo;
  s32 v17;
  dds3ProcessID_t *v19;
  dds3ProcessID_t *v21;
  jmsSeqUnit_t *gohSeqUnit_local;
  dds3ProcessID_t *v24;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  p_pSeqUnit = &ProcessData->pSeqUnit;
  SeqHandle = ProcessData->SeqHandle;
  v7 = id;
  result = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v7);
  if (!result)
  {
    fclLinkData(ProcessData->pMsgData);
    v9 = Allocate(gohDirData_t);
    v10 = NewSpecific(dds3ModelHandle_t, 3u);
    v9[1].monitor = v10;
    _ctor(v9, 0);
    ProcessData->pDirData = (gohDirData_t *)v9;
    gohModelLoad(ProcessData);
    gohBgmStop(ProcessData);
    scrSetMovieCancel(0);
    PmvPID = ProcessData->PmvPID;
    evtNoSkipMes(ProcessData->PmvPID);
    if (gohGetTypeCnt())
    {
      TypeCnt = gohGetTypeCnt();
      if (TypeCnt < 1)
      {
        v17 = 0;
        v19 = ProcessData->PmvPID;
      }
      else
      {
        v14 = TypeCnt;
        for (i = 0; i != v14; ++i)
          TypeNo = gohGetTypeNo(i);
        v17 = TypeNo;
        v19 = ProcessData->PmvPID;
      }
      evtChgSeq(v19, 2, v17);
      v21 = ProcessData->PmvPID;
      goto LABEL_29;
    }
    v24 = ProcessData->PmvPID;
    evtChgSeq(v24, 1, 0);
    v21 = ProcessData->PmvPID;
LABEL_29:
    evtIgnoreFade(v21);
    gohSeqUnit_local = gohSeqUnit;
    jmsSeqJumpAndFree(p_pSeqUnit, &gohSeqUnit_local[1]);
    return 0;
  }
  return result;
}

// 0x1ba3d50
dds3ProcessFunc_t gohDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 1, v6);
}

// 0x1ba3e70
dds3ProcessFunc_t gohUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1b9e340
s32 gohGetCameraTable(s32 iDevilId) {
  il2cpp_array_size_t max_length;
  s64 v5;
  bool v6;

  max_length = s_CameraTable->max_length;
  LODWORD(v5) = iDevilId - 261;
  if (iDevilId < 336)
    LODWORD(v5) = iDevilId;
  v6 = (s32)v5 >= (s32)max_length || (s32)v5 <= -1;
  v5 = (s32)v5;
  if (v6)
    v5 = 0;
  return s_CameraTable[v5];
}

// 0x1ba3f90
void gohCallPartVoice(message_tag *_tag) {
  gohData_t *GohData;
  s32 devilid;
  u32 DevilSE;

  if (scrIsEventSkip(0))
    return;
  GohData = GohGetGohData();
  if (tag->maxpage - 1 == tag->page)
  {
    devilid = GohData->BirthDevil->devilid;
    DevilSE = GetDevilSE(devilid, 17);
    sBtlStopSE(DevilSE);
    sBtlPlaySESub(DevilSE, 127);
  }
}

// 0x1b9eaf0
void gohResultCalcStateMessageBirth(gohData_t *psSelf) {
  dds3ProcessID_t *PmvPID;
  s32 devilid;
  u32 DevilSE;
  u32 v7;
  u32 v8;
  void *v9;
  u32 v10;
  char *v11;
  s32 v12;
  u32 v14;
  DEVILDATA_WORK *DevilData;
  char *v16;
  DEVILDATA_WORK *v17;
  void *achievementTbl_k__BackingField;
  Project_DefineAchievementID_string__c *klass;
  s64 v22;
  Project_DefineAchievementID_string__c **p_offset;
  void *v24;
  u32 v25;
  s64 v27;
  Project_DefineAchievementID_string__c **v28;
  s64 v29;
  s32 v30;
  char *v31;
  void *v34;
  Project_DefineAchievementID_string__c *v35;
  s64 v36;
  Project_DefineAchievementID_string__c **v37;
  s64 v38;
  char *v39;
  s32 v41;
  s32 *EventBit;
  void *v44;
  Project_DefineAchievementID_string__c *v45;
  s64 v46;
  Project_DefineAchievementID_string__c **v47;
  s64 v48;
  char *v49;

  PmvPID = psSelf->PmvPID;
  if (evtSetFrame(PmvPID, -1) < 1530)
    return;
  devilid = psSelf->BirthDevil->devilid;
  DevilSE = GetDevilSE(devilid, -1);
  p2sdLoadSMGFile(DevilSE);
  p2sdLoadSMGFile(DevilSE + 0x10000000);
  v7 = GetDevilSE(psSelf->BirthDevil->devilid, 13);
  sBtlStopSE(v7);
  sBtlPlaySESub(v7, 127);
  LogStart(0);
  v8 = RAND(0);
  v9 = Allocate(System_Action_itf_message_tag_);
  __ctor(v9, 0, Method_Project_gohDirection_CallPartVoice__, 0);
  fclSetPageUpdateCallBack(v9);
  v10 = v8 / 3;
  v11 = sdatDevilName(devilid, 0);
  fclSetMessageVar(0, v11);
  v12 = 3 * v10;
  v14 = v8 - v12;
  DevilData = sBtlGetDevilData(devilid, -1);
  v16 = sdatRaceName(DevilData->kuda_id);
  fclSetMessageVar(4, v16);
  v17 = sBtlGetDevilData(devilid, -1);
  fclStartMessage((v14 | 0x30) - v17->kucyo + 8 * v17->kucyo);
  *(u64 *)&psSelf->pDirData->ResultStat = (u32)(psSelf->pDirData->ResultStat + 1);
  if (devilid != 66)
  {
    if ((u16)devilid != 58)
      goto LABEL_54;
    achievementTbl_k__BackingField = _achievementTbl_k__BackingField;
    klass = achievementTbl_k__BackingField->klass;
    v22 = *(u16 *)&achievementTbl_k__BackingField->klass->_2.rank;
    if (*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
    {
      p_offset = &klass->_1.interfaceOffsets->offset;
      while (*(p_offset - 1) != Project_DefineAchievementID_string_)
      {
        p_offset += 2;
        if (!--v22)
          goto LABEL_31;
      }
      v30 = *(u32 *)p_offset + 32;
LABEL_52:
      v29 = &klass->vtable[v30];
      goto LABEL_53;
    }
LABEL_31:
    v24 = _achievementTbl_k__BackingField;
    v25 = 32;
    goto LABEL_43;
  }
  achievementTbl_k__BackingField = _achievementTbl_k__BackingField;
  klass = achievementTbl_k__BackingField->klass;
  v27 = *(u16 *)&achievementTbl_k__BackingField->klass->_2.rank;
  if (*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
  {
    v28 = &klass->_1.interfaceOffsets->offset;
    while (*(v28 - 1) != Project_DefineAchievementID_string_)
    {
      v28 += 2;
      if (!--v27)
        goto LABEL_42;
    }
    v30 = *(u32 *)v28 + 33;
    goto LABEL_52;
  }
LABEL_42:
  v25 = 33;
  v24 = _achievementTbl_k__BackingField;
LABEL_43:
  v29 = sub_4227F4(v24, Project_DefineAchievementID_string_, v25);
LABEL_53:
  v31 = (*v29)(achievementTbl_k__BackingField, *(u64 *)(v29 + 8));
  Unlock_2(v31);
LABEL_54:
  if (!SystemWork->cmbCnt)
    goto LABEL_70;
  v34 = _achievementTbl_k__BackingField;
  v35 = v34->klass;
  v36 = *(u16 *)&v34->klass->_2.rank;
  if (*(u16 *)&v34->klass->_2.rank)
  {
    v37 = &v35->_1.interfaceOffsets->offset;
    while (*(v37 - 1) != Project_DefineAchievementID_string_)
    {
      v37 += 2;
      if (!--v36)
        goto LABEL_64;
    }
    v38 = &v35->vtable[*(u32 *)v37 + 28];
  }
  else
  {
LABEL_64:
    v38 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0x1Cu);
  }
  v39 = (*v38)(v34, *(u64 *)(v38 + 8));
  Unlock_2(v39);
LABEL_70:
  if (psSelf->AccidentFlag)
  {
    if (evtBitCheck(2121))
      goto LABEL_78;
    v41 = 512;
    goto LABEL_76;
  }
  if (!evtBitCheck(2120))
  {
    v41 = 256;
LABEL_76:
    EventBit = GBWK->EventBit;
    EventBit[66] |= v41;
  }
LABEL_78:
  if (SystemWork->cmbCnt < 0x32u)
    return;
  v44 = _achievementTbl_k__BackingField;
  v45 = v44->klass;
  v46 = *(u16 *)&v44->klass->_2.rank;
  if (*(u16 *)&v44->klass->_2.rank)
  {
    v47 = &v45->_1.interfaceOffsets->offset;
    while (*(v47 - 1) != Project_DefineAchievementID_string_)
    {
      v47 += 2;
      if (!--v46)
        goto LABEL_88;
    }
    v48 = &v45->vtable[*(u32 *)v47 + 29];
  }
  else
  {
LABEL_88:
    v48 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0x1Du);
  }
  v49 = (*v48)(v44, *(u64 *)(v48 + 8));
  Unlock_2(v49);
}

// 0x1b9f330
bool gohResultCalcStateMessageGiveCard(gohData_t *psSelf) {
  return 0;
}

// 0x1b9e970
void gohResultCalcStateMessageWait(gohData_t *psSelf) {
  gohDirData_t *pDirData;
  s32 v5;
  bool v6;
  s32 devilid;
  u32 DevilSE;

  if (fclChkMessage())
    return;
  pDirData = psSelf->pDirData;
  v5 = pDirData->ResultStatCnt + 1;
  v6 = pDirData->ResultStatCnt - 29 < 0;
  pDirData->ResultStatCnt = v5;
  if (v6 == __OFSUB__(v5, 30))
  {
    devilid = psSelf->BirthDevil->devilid;
    DevilSE = GetDevilSE(devilid, -1);
    p2sdLoadSMGFile(DevilSE);
    p2sdLoadSMGFile(DevilSE + 0x10000000);
    ++psSelf->pDirData->ResultStat;
    scrEventSkipEnd(0, 0);
    scrLogEnd(0);
  }
}

// 0x1b9f340
void gohResultCalcStateFadeOut(gohData_t *psSelf) {
  dds3ProcessID_t *PmvPID;

  PmvPID = psSelf->PmvPID;
  evtIgnoreFade(PmvPID);
  dds3FadeOut(0, 0, 0, 0x1Eu);
  ++psSelf->pDirData->ResultStat;
}

// 0x1b9f430
void gohResultCalcStateFadeOutWait(gohData_t *psSelf) {
  jmsSeqUnit_t *p_pSeqUnit;
  jmsSeqUnit_t *gohSeqUnit_local;

  if (dds3FadeCheck())
    return;
  p_pSeqUnit = &psSelf->pSeqUnit;
  gohSeqUnit_local = gohSeqUnit;
  jmsSeqJumpAndFree(p_pSeqUnit, &gohSeqUnit_local[3]);
  return;
}
