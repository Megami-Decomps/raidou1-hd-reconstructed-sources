#include "types.h"
#include "buttonguide.h"
#include "cfg.h"
#include "cmpmodel.h"
#include "configunity.h"
#include "creditsmain.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3adminiprocess.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3padmanager.h"
#include "evtmoon.h"
#include "evtviewer.h"
#include "fclmisc.h"
#include "fclmsg.h"
#include "fld.h"
#include "itf.h"
#include "jmsmisc.h"
#include "kernel.h"
#include "localize.h"
#include "movie.h"
#include "raijindlc.h"
#include "scr.h"
#include "scrcommand.h"
#include "sdfmem.h"
#include "sdfsound.h"
#include "slmain.h"
#include "sndat3.h"
#include "sndmanager.h"
#include "titlemain.h"
#include "titlemes.h"

#define TITLE_MESSAGE_WAIT 8
#define TITLE_MESSAGE_ENDWAIT 13

typedef enum {
    LICENSETEXTSCROLL_DOWN = -1,
    LICENSETEXTSCROLL_ZERO = 0,
    LICENSETEXTSCROLL_UP = 1,
} LICENSETEXTSCROLL;

typedef enum {
    DISSOLVE_STATE_NONE = -1,
    DISSOLVE_STATE_IN = 0,
    DISSOLVE_STATE_OUT = 1,
} DISSOLVE_STATE;

typedef enum {
    LEVEL_CHECK__GAME_INIT = 0,
    LEVEL_CHECK__GAME_WAIT = 1,
    LEVEL_CHECK__GAME_CHECK = 2,
    LEVEL_CHECK__GAME_END = 3,
} LEVEL_CHECK__GAME;

typedef enum {
    TITLE_DLC_GAME_INIT = 0,
    TITLE_DLC_GAME_WAIT = 1,
    TITLE_DLC_GAME_SAVE = 2,
    TITLE_DLC_GAME_END = 3,
} TITLE_DLC_GAME;

typedef enum {
    TITLE_FIRST_SAVE_INIT = 0,
    TITLE_FIRST_SAVE_SAVE = 1,
    TITLE_FIRST_SAVE_END = 2,
} TITLE_FIRST_SAVE;

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct jmsSeqUnit_t jmsSeqUnit_t;
typedef struct titleAlphaTable_t titleAlphaTable_t;
typedef struct titleCursor_t titleCursor_t;
typedef struct titleData_t titleData_t;
typedef struct titleSprTable_t titleSprTable_t;

s32 handover_type;
s32 *titleAdvMovieList;
s32 *titleMoveList;
s32 m_playMode;
static s32 movieNowFrame;
static s32 movieOldFrame;
static s32 movieFrameOverCount;
static DISSOLVE_STATE dissolveState;
static f32 titleDisolvePar;
static dds3ProcessFunc_t SuspendFunc;
static dds3ProcessID_t *SuspendID;
static TITLE_DLC_GAME DLCGameProc;
static TITLE_FIRST_SAVE FirstSaveProc;
static char *devilVoiceName;
char *title_scene_name;
static LEVEL_CHECK__GAME LevelCheckProc;
jmsSeqUnit_t *titleSeqUnit;
titleSprTable_t *titleSprTable;

static void SakuraEffectDraw(void);
static bool DLCChack(titleData_t *data);
static bool titleDLCMsgCheck(dds3ProcessID_t *PID);
static bool titleDLCMsgDraw(dds3ProcessID_t *PID);
static void JugeMovieFrameUpdate(void);
static void DispSubTitle(s32 frame, bool active);
static void SubTitleDissolveCalc(void);
static s32 PlayMainSubAt3(titleData_t *pData);
void CreditsInit(void);
void CreditsDestroy(void);
void CalcProcess(void);
void DrawProcess(void);

// 0x22235e0
s32 TitleHandOverInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *Instance;
  char klass;
  void *v8;
  void *v9;
  void *v10;
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
  ClossMenuList(Instance, 0);
  klass = ProcessData[8].klass;
  if (klass)
  {
    klass = 1;
    LOBYTE(ProcessData[8].klass) = 0;
  }
  BYTE4(ProcessData[8].monitor) = klass;
  HIDWORD(ProcessData[4].klass->_1.this_arg.data) = 2;
  v8 = get_Instance(0);
  SettingNoteCtr(v8, 0, 0);
  v9 = get_Instance(0);
  OpenHandOverSelMenu(v9, 0);
  v10 = get_Instance(0);
  LevelSelectCursor(v10, HIDWORD(ProcessData[4].klass->_1.this_arg.data), 1, 0);
  LOBYTE(ProcessData[10].klass) = 0;
  return 1;
}

// 0x2223770
s32 TitleHandOverDestroy(dds3ProcessID_t *PID) {
  titleData_t *ProcessData;
  s32 Flag;
  s32 result;
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
  if ((Flag & 8) == 0)
  {
    ProcessData->Flag = Flag & 0xFFFFFFE3;
    result = TitleAt3Load(ProcessData, 80);
    if (!result)
      return result;
LABEL_19:
    if ((ProcessData->Flag & 0x18) != 8)
      return 1;
    sndBgmPlay(0, 0);
    ProcessData->Flag |= 0x10u;
    return 1;
  }
  sndBgmStop();
  sndBgmFree();
  ProcessData->Flag &= 0xFFFFFFE3;
  result = TitleAt3Load(ProcessData, 80);
  if (result)
    goto LABEL_19;
  return result;
}

// 0x2223bf0
dds3ProcessFunc_t TitleHandOverCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqUnit_t *v5;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  dds3ProcessID_t *v10;
  titleCursor_t *klass;
  s32 data_high;
  jmsSeqUnit_t *titleSeqUnit_local;
  void *Instance;
  jmsSeqUnit_t *v21;
  void *v23;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  v5 = &ProcessData[2];
  monitor = ProcessData[1].monitor;
  v7 = id;
  v8 = jmsSeqChange(monitor, &ProcessData[2], 0, v7);
  if (!v8)
  {
    if (dds3FadeCheck())
      return v8;
    if (movieCheckStandby())
    {
      if (dds3FadeCheck())
      {
LABEL_24:
        v10 = id;
        klass = ProcessData[4].klass;
        TitleCalcCursor(v10, klass, 2);
        if (CHECK_TRIG(4096, 0))
        {
          SE(0);
          data_high = HIDWORD(ProcessData[4].klass->_1.this_arg.data);
          LOBYTE(ProcessData[10].klass) = 1;
          LOBYTE(ProcessData[8].klass) = 1;
          handover_type = data_high;
          titleSeqUnit_local = titleSeqUnit;
          jmsSeqJumpAndFree(v5, &titleSeqUnit_local[12]);
          return v8;
        }
        if (!CHECK_TRIG(4097, 1))
          return v8;
        Instance = get_Instance(0);
        if (!op_Inequality(Instance, 0, 0))
        {
          SE(1);
          goto LABEL_38;
        }
        v23 = get_Instance(0);
        ClossHandOverSelMenu(v23, 0, 0);
        dds3FadeIn(0, 0, 0, 0x28u);
        SE(1);
LABEL_38:
        v21 = titleSeqUnit;
        jmsSeqJumpAndFree(&ProcessData[2], &v21[6]);
        LOBYTE(ProcessData[10].klass) = 0;
        return v8;
      }
      if (BYTE4(ProcessData[8].monitor))
        goto LABEL_24;
      dds3FadeIn(0, 0, 0, 0x1Eu);
      BYTE4(ProcessData[8].monitor) = 1;
    }
  }
  return v8;
}

// 0x22245a0
dds3ProcessFunc_t TitleHandOverDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
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
  v7 = jmsSeqChange(monitor, &ProcessData[2], 1, v6);
  jmsSeqChange(ProcessData[1].monitor, &ProcessData[2], 2, id);
  return v7;
}

// 0x22246f0
void TitleLoadTitleUI(dds3ProcessID_t *ParentPID, titleData_t *pData) {
  char *v5;
  char *v8;
  void *SceneAsync;
  dds3ProcessID_t *PmvPID;

  v5 = "UI_title";
  title_scene_name = "UI_title";
  v8 = "title";
  Load(Dependent, v8, v8);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  SceneAsync = LoadSceneAsync(_Ctrl_k__BackingField, title_scene_name, 0);
  scene_asyncLoad = SceneAsync;
  PmvPID = pData->PmvPID;
  evtIgnoreFade(PmvPID);
}

// 0x22248f0
s32 TitleCheckTitleUi(titleData_t *pData) {
  if (!scene_asyncLoad)
  {
LABEL_5:
    scene_asyncLoad = 0;
    pData->Flag |= 2u;
    return 1;
  }
  if (get_isDone(scene_asyncLoad, 0))
  {
    goto LABEL_5;
  }
  return 0;
}

// 0x2224a10
void TitleFreeTitleUi(titleData_t *pData) {
  titleData_t *v3;
  dds3ProcessID_t *PmvPID;

  v3 = pData;
  PmvPID = pData->PmvPID;
  if (PmvPID)
  {
    evtEnd(PmvPID);
    v3 = pData;
  }
  v3->PmvPID = 0;
}

// 0x2224a90
void TitleUnloadTitleUi(void) {
  UnityEngine_SceneManagement_Scene_o v5;

  if (IsNullOrEmpty(title_scene_name, 0))
    return;
  v5.m_Handle = GetSceneByName(title_scene_name, 0).m_Handle;
  UnloadSceneAsync_61083440(v5, 0);
  title_scene_name = 0;
  return;
}

// 0x2224bb0
dds3ProcessFunc_t TitleFirstCalcProcess(dds3ProcessID_t *PID) {
  titleData_t *ProcessData;
  dds3ProcessFunc_t v8;
  titleData_t *pData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  pData = ProcessData;
  TitleLoadTitleUI(TitleMain, pData);
  Create(0);
  fclLinkData(sys);
  v8 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v8, 0, Method_Project_TitleMain_FirstCalcProcess2__, 0);
  return v8;
}

// 0x2224d40
dds3ProcessFunc_t TitleFirstCalcProcess2(dds3ProcessID_t *PID) {
  titleData_t *ProcessData;
  dds3ProcessFunc_t v7;
  titleData_t *v10;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v10 = ProcessData;
  ProcessData->WorkStat = 0;
  if (!TitleCheckTitleUi(v10))
    return 0;
  Unload(Dependent, "title", 0);
  v7 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_TitleMain_FirstCalcProcess3__, 0);
  return v7;
}

// 0x2224f10
dds3ProcessFunc_t TitleFirstCalcProcess3(dds3ProcessID_t *PID) {
  titleData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
  s32 Mode;
  bool v11;
  jmsSeqUnit_t *titleSeqUnit_local;
  jmsSeqUnit_t *v15;
  jmsSeqUnit_t *v17;
  jmsSeqUnit_t *v18;
  jmsSeqUnit_t *v21;
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
  SeqHandle = ProcessData->SeqHandle;
  v6 = id;
  v7 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v6);
  if (v7)
    return v7;
  dds3BistaClear();
  scrEndEventSkipMsg1st();
  ProcessData->Flag |= 2u;
  evtMoonDisableDraw(1);
  if (p2sdLoadCheckMidi(5242880))
  {
    Mode = ProcessData->Mode;
    if (Mode != 3)
      goto LABEL_21;
    goto LABEL_36;
  }
  p2sdLoadSMGFile(5242880);
  Mode = ProcessData->Mode;
  if (Mode != 3)
  {
LABEL_21:
    if (Mode != 2)
    {
      if (!Mode)
      {
        v11 = GetLanguageTYPE() == 2;
        if (v11)
        {
          titleSeqUnit_local = titleSeqUnit;
          v15 = &titleSeqUnit_local[1];
        }
        else
        {
          v22 = titleSeqUnit;
          v15 = &v22[2];
        }
        jmsSeqJump(&ProcessData->pSeqUnit, v15);
      }
      goto LABEL_62;
    }
    if (ProcessData->Count >= 10)
    {
      ProcessData->WorkStat = 2;
      dds3FadeIn(0, 0, 0, 0xAu);
      ButtonGuideDispOff();
      v21 = titleSeqUnit;
      v18 = &v21[6];
      goto LABEL_55;
    }
LABEL_62:
    ++ProcessData->Count;
    return v7;
  }
LABEL_36:
  if (ProcessData->Count < 10)
    goto LABEL_62;
  if (TitleAt3Load(ProcessData, 80))
  {
    if ((ProcessData->Flag & 0x18) != 8)
    {
      v17 = titleSeqUnit;
LABEL_44:
      v18 = &v17[16];
LABEL_55:
      jmsSeqJump(&ProcessData->pSeqUnit, v18);
      ProcessData->Count = 0;
      goto LABEL_62;
    }
    sndBgmPlay(0, 0);
    ProcessData->Flag |= 0x10u;
    v17 = titleSeqUnit;
    goto LABEL_44;
  }
  return v7;
}

// 0x22253e0
dds3ProcessFunc_t TitleFirstDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
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
  v7 = jmsSeqChange(monitor, &ProcessData[2], 1, v6);
  jmsSeqChange(ProcessData[1].monitor, &ProcessData[2], 2, id);
  return v7;
}

// 0x2225530
s32 TitleCesaInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *Instance;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  dds3FadeIn(0, 0, 0, 0x28u);
  Instance = get_Instance(0);
  CesaLogoCtr(Instance, 1, 0);
  BYTE5(ProcessData[8].monitor) = SystemWork->titleFlg == 1;
  return 1;
}

// 0x22256d0
s32 TitleCesaDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x22256e0
dds3ProcessFunc_t TitleCesaCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t result;
  s32 v8;
  s32 klass;
  jmsSeqUnit_t *titleSeqUnit_local;
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
  result = jmsSeqChange(monitor, &ProcessData[2], 0, v6);
  if (!result)
  {
    if (CHECK_TRIG(4096, 1))
    {
      v8 = BYTE5(ProcessData[8].monitor);
      if (!CHECK_TRIG(4110, 1))
      {
        if (!v8)
          goto LABEL_22;
LABEL_20:
        if ((u32)(LODWORD(ProcessData[3].klass) - 300) >= 0xFFFFFEFC)
          LODWORD(ProcessData[3].klass) = 300;
LABEL_22:
        klass = ProcessData[3].klass;
        if (klass == 300)
        {
          dds3FadeOut(0, 0, 0, 0x28u);
          klass = ProcessData[3].klass;
        }
        if (klass >= 340)
        {
          titleSeqUnit_local = titleSeqUnit;
          jmsSeqJumpAndFree(&ProcessData[2], &titleSeqUnit_local[2]);
          klass = ProcessData[3].klass;
        }
        LODWORD(ProcessData[3].klass) = klass + 1;
        return 0;
      }
    }
    else
    {
      if (!CHECK_TRIG(4110, 1))
        goto LABEL_22;
      v8 = 0;
    }
    if (!v8 && !BYTE5(ProcessData[8].monitor))
      goto LABEL_22;
    goto LABEL_20;
  }
  return result;
}

// 0x2225970
dds3ProcessFunc_t TitleCesaDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
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
  v7 = jmsSeqChange(monitor, &ProcessData[2], 1, v6);
  jmsSeqChange(ProcessData[1].monitor, &ProcessData[2], 2, id);
  return v7;
}

// 0x2225ac0
s32 TitleLightWarningInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *Instance;
  void *v6;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  LODWORD(ProcessData[3].klass) = 0;
  dds3FadeIn(0, 0, 0, 0x28u);
  Instance = get_Instance(0);
  CesaLogoCtr(Instance, 0, 0);
  v6 = get_Instance(0);
  LightWarningObjCtrl(v6, 1, 0);
  BYTE5(ProcessData[8].monitor) = SystemWork->titleFlg == 1;
  return 1;
}

// 0x2225c70
s32 TitleLightWarningDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x2225c80
dds3ProcessFunc_t TitleLightWarningCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t result;
  s32 v8;
  s32 klass;
  jmsSeqUnit_t *titleSeqUnit_local;
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
  result = jmsSeqChange(monitor, &ProcessData[2], 0, v6);
  if (!result)
  {
    if (CHECK_TRIG(4096, 1))
    {
      v8 = BYTE5(ProcessData[8].monitor);
      if (!CHECK_TRIG(4110, 1))
      {
        if (!v8)
          goto LABEL_22;
LABEL_20:
        if ((u32)(LODWORD(ProcessData[3].klass) - 300) >= 0xFFFFFEFC)
          LODWORD(ProcessData[3].klass) = 300;
LABEL_22:
        klass = ProcessData[3].klass;
        if (klass == 300)
        {
          dds3FadeOut(0, 0, 0, 0x28u);
          klass = ProcessData[3].klass;
        }
        if (klass >= 340)
        {
          titleSeqUnit_local = titleSeqUnit;
          jmsSeqJumpAndFree(&ProcessData[2], &titleSeqUnit_local[3]);
          klass = ProcessData[3].klass;
        }
        LODWORD(ProcessData[3].klass) = klass + 1;
        return 0;
      }
    }
    else
    {
      if (!CHECK_TRIG(4110, 1))
        goto LABEL_22;
      v8 = 0;
    }
    if (!v8 && !BYTE5(ProcessData[8].monitor))
      goto LABEL_22;
    goto LABEL_20;
  }
  return result;
}

// 0x2225f10
dds3ProcessFunc_t TitleLightWarningDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
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
  v7 = jmsSeqChange(monitor, &ProcessData[2], 1, v6);
  jmsSeqChange(ProcessData[1].monitor, &ProcessData[2], 2, id);
  return v7;
}

// 0x2226060
s32 TitleAtlusLogoInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *Instance;
  void *v6;
  void *v7;
  s32 v9;
  char *v11;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  LODWORD(ProcessData[3].klass) = 0;
  dds3FadeIn(0, 0, 0, 0x28u);
  Instance = get_Instance(0);
  SetCameraActive(Instance, 1, 0);
  cmpLoadEffect();
  v6 = get_Instance(0);
  LightWarningObjCtrl(v6, 0, 0);
  v7 = get_Instance(0);
  AtlusLogoCtr(v7, 1, 0);
  BYTE5(ProcessData[8].monitor) = SystemWork->titleFlg == 1;
  v9 = Range_60964768(0, 18, 0);
  v11 = devilVoiceName[v9];
  sndVoicePlayFile(v11, 0);
  return 1;
}

// 0x22262d0
s32 TitleAtlusLogoDestroy(dds3ProcessID_t *PID) {
  void *Instance;

  Instance = get_Instance(0);
  SetCameraActive(Instance, 0, 0);
  cmpDeleteEffect();
  End();
  return 1;
}

// 0x2226370
static void SakuraEffectDraw(void) {
  cmpEffectSetRGBA(0x80808080);
  cmpDrawEffect();
}

// 0x22263d0
dds3ProcessFunc_t TitleAtlusLogoCalcProcess(dds3ProcessID_t *PID) {
  titleData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v8;
  _BOOL4 skipFlag;
  s32 WaitTimer;
  jmsSeqUnit_t *titleSeqUnit_local;
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
  if (!v8)
  {
    if (TitleAt3Load(ProcessData, 80))
    {
      if (CHECK_TRIG(4096, 1))
      {
        skipFlag = ProcessData->skipFlag;
        if (!CHECK_TRIG(4110, 1))
        {
          if (!skipFlag)
            goto LABEL_25;
LABEL_23:
          if ((u32)(ProcessData->WaitTimer - 300) >= 0xFFFFFEFC)
            ProcessData->WaitTimer = 300;
          goto LABEL_25;
        }
      }
      else
      {
        if (!CHECK_TRIG(4110, 1))
        {
LABEL_25:
          WaitTimer = ProcessData->WaitTimer;
          if (WaitTimer == 300)
          {
            dds3FadeOut(0, 0, 0, 0x28u);
            WaitTimer = ProcessData->WaitTimer;
          }
          if (WaitTimer >= 340)
          {
            titleSeqUnit_local = titleSeqUnit;
            jmsSeqJumpAndFree(&ProcessData->pSeqUnit, &titleSeqUnit_local[4]);
            WaitTimer = ProcessData->WaitTimer;
          }
          ProcessData->WaitTimer = WaitTimer + 1;
          return v8;
        }
        skipFlag = 0;
      }
      if (!skipFlag && !ProcessData->skipFlag)
        goto LABEL_25;
      goto LABEL_23;
    }
  }
  return v8;
}

// 0x2226650
dds3ProcessFunc_t TitleAtlusLogoDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
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
  v7 = jmsSeqChange(monitor, &ProcessData[2], 1, v6);
  jmsSeqChange(ProcessData[1].monitor, &ProcessData[2], 2, id);
  cmpEffectSetRGBA(0x80808080);
  cmpDrawEffect();
  return v7;
}

// 0x2226830
s32 TitleMovieInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *Instance;
  void *v11;
  void *v12;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  HIDWORD(ProcessData[2].monitor) = 0;
  LODWORD(ProcessData[5].monitor) = 0;
  dds3FadeIn(0, 0, 0, 0x28u);
  Instance = get_Instance(0);
  AtlusLogoCtr(Instance, 0, 0);
  if (ProcessData[3].monitor)
  {
    goto LABEL_15;
  }
  else
  {
    dds3LinkProcess(id, &ProcessData[3].monitor);
LABEL_15:
    FirstSaveProc = 0;
    goto LABEL_16;
  }
  FirstSaveProc = 0;
LABEL_16:
  if (SystemWork->titleFlg == 1)
  {
    BYTE6(ProcessData[8].monitor) = 0;
    goto LABEL_28;
  }
  BYTE6(ProcessData[8].monitor) = 1;
  SystemWork->titleFlg = 1;
LABEL_28:
  v11 = get_Instance(0);
  OpMovieNameSet(v11, 0);
  moviePlay(24, 0, 1);
  v12 = get_Instance(0);
  OpMovieNameActive(v12, 1, 0);
  return 1;
}

// 0x2226b20
s32 TitleMovieDestroy(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 v5;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = HIDWORD(ProcessData[5].monitor) + 1;
  HIDWORD(ProcessData[5].monitor) = v5;
  if (v5 < SLODWORD(titleMoveList->max_length))
    return 1;
  HIDWORD(ProcessData[5].monitor) = 0;
  return 1;
}

// 0x2226c80
dds3ProcessFunc_t TitleMovieCalcProcess(dds3ProcessID_t *PID) {
  titleData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t result;
  s32 MovieSkipFlag;
  s32 v12;
  void *Instance;
  void *v15;
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
  result = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v6);
  if (!result)
  {
    if (ProcessData->saveFlag)
    {
      if (MainTitleFirstSave(ProcessData))
        goto LABEL_72;
    }
    MovieSkipFlag = ProcessData->MovieSkipFlag;
    if (MovieSkipFlag > 1)
    {
      if (MovieSkipFlag == 2)
      {
        movieStop(0);
        if (movieCheckStandby())
        {
          Instance = get_Instance(0);
          OpMovieNameActive(Instance, 0, 0);
          ProcessData->MovieSkipFlag = 0;
          dds3FadeIn(0xFFu, 0xFFu, 0xFFu, 0x28u);
          TitleGoMain(ProcessData);
        }
        goto LABEL_72;
      }
      if (MovieSkipFlag == 100)
      {
        movieStop(0);
        v15 = get_Instance(0);
        OpMovieNameActive(v15, 0, 0);
        v12 = 101;
        goto LABEL_71;
      }
      if (MovieSkipFlag != 101)
        goto LABEL_72;
      goto LABEL_23;
      if (drawEnd)
      {
LABEL_57:
        movieStop(0);
        v12 = 2;
        goto LABEL_71;
      }
LABEL_72:
      ++ProcessData->Timer;
      return 0;
LABEL_23:
      if (!drawEnd)
        goto LABEL_72;
      goto LABEL_57;
    }
    if (MovieSkipFlag)
    {
      if (MovieSkipFlag != 1)
        goto LABEL_72;
      if (drawEnd)
      {
        dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 1u);
        v12 = 2;
        goto LABEL_71;
      }
      if (ProcessData->Timer < 60 || !CHECK_REP(14, 1) && !CHECK_TRIG(4096, 1))
      {
        goto LABEL_72;
      }
      v12 = 100;
      goto LABEL_71;
    }
    if (drawEnd)
      goto LABEL_72;
    v12 = 1;
LABEL_71:
    ProcessData->MovieSkipFlag = v12;
    goto LABEL_72;
  }
  return result;
}

// 0x2227550
dds3ProcessFunc_t TitleMovieDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
  void *Instance;
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
  v7 = jmsSeqChange(monitor, &ProcessData[2], 1, v6);
  jmsSeqChange(ProcessData[1].monitor, &ProcessData[2], 2, id);
  if (v7)
    return v7;
  Instance = get_Instance(0);
  OpNameAnimUpdate(Instance, 0);
  return 0;
}

// 0x22276f0
s32 MainInit(dds3ProcessID_t *PID) {
  titleData_t *ProcessData;
  titleCursor_t *Cursor;
  titleData_t *v10;
  bool v12;
  void *Instance;
  void *v15;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  ProcessData->Timer = 0;
  ProcessData->AnimTimer = 0;
  Cursor = ProcessData->Cursor;
  ProcessData->FadeOut = 0;
  Cursor->Index = 0;
  Cursor->LevelIndex = 0;
  moviePlay(33, 1, 1);
  itfSetIsmesWndBaseDisp(1);
  JugeMovieFrameUpdate();
  v9 = PlayMainSubAt3(ProcessData);
  TitlePlayMovieSe();
  FirstSaveProc = 0;
  v12 = DLCChack(v10);
  ProcessData->saveFlag = v12;
  Instance = get_Instance(0);
  TopCtr(Instance, 1, 0);
  v15 = get_Instance(0);
  VerCtr(v15, 1, 0);
  return 1;
}

// 0x2228400
s32 MainDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x2228410
dds3ProcessFunc_t MainCalcProcess(dds3ProcessID_t *PID) {
  titleData_t *ProcessData;
  jmsSeqUnit_t *p_pSeqUnit;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  void *Instance;
  s32 WaitTimer;
  bool v16;
  s32 v17;
  dds3ProcessID_t *v19;
  jmsSeqUnit_t *titleSeqUnit_local;
  s32 Flag;
  titleCursor_t *Cursor;
  void *v27;
  jmsSeqUnit_t *v31;
  void *v32;
  jmsSeqUnit_t *v38;
  jmsSeqUnit_t *v41;
  void *v42;
  void *v43;
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
  if ((ProcessData->Flag & 0x18) == 8)
  {
    sndBgmPlay(0, 0);
    ProcessData->Flag |= 0x10u;
  }
  JugeMovieFrameUpdate();
  TitlePlayMovieSe();
  Instance = get_Instance(0);
  DispSubTitle(Instance->startFrame, 1);
  SubTitleDissolveCalc();
  WaitTimer = ProcessData->WaitTimer;
  v16 = __OFSUB__(WaitTimer, 1);
  v17 = WaitTimer - 1;
  if (v17 < 0 == v16)
  {
    ProcessData->WaitTimer = v17;
    return v8;
  }
  if (!ProcessData->saveFlag)
    goto LABEL_30;
  if (!MainTitleFirstSave(ProcessData))
  {
LABEL_30:
    v19 = id;
    if (titleDLCMsgCheck(id))
    {
      titleSeqUnit_local = titleSeqUnit;
      jmsSeqJumpAndFree(p_pSeqUnit, &titleSeqUnit_local[14]);
      return v8;
    }
    if (ProcessData->Timer > 1199)
    {
      if (!ProcessData->FadeOut)
      {
        sndBgmFadeOut();
        dds3FadeOut(0, 0, 0, 0x3Cu);
        ProcessData->FadeOut = 1;
        goto LABEL_64;
      }
      if (!dds3FadeCheck())
      {
        Flag = ProcessData->Flag;
        if ((Flag & 0x60) == 0x20)
        {
          ProcessData->Flag = Flag | 0x40;
          return v8;
        }
        ProcessData->MovieCounter = 0;
        ProcessData->Flag = Flag & 0xFFFFFF9F;
        TitleAt3Stop(ProcessData);
        if (ProcessData->AdvSkipFlag)
        {
          DispSubTitle(-1, 0);
          TitleStopMovieSe();
          movieStop(0);
          if (!movieCheckStandby())
            goto LABEL_64;
          v38 = titleSeqUnit;
          jmsSeqJumpAndFree(&ProcessData->pSeqUnit, &v38[3]);
          ProcessData->AdvSkipFlag = 0;
        }
        else
        {
          DispSubTitle(-1, 0);
          TitleStopMovieSe();
          movieStop(0);
          if (!movieCheckStandby())
            goto LABEL_64;
          v41 = titleSeqUnit;
          jmsSeqJumpAndFree(&ProcessData->pSeqUnit, &v41[3]);
        }
        v42 = get_Instance(0);
        TopCtr(v42, 0, 0);
        v43 = get_Instance(0);
        VerCtr(v43, 0, 0);
      }
LABEL_64:
      ++ProcessData->Timer;
      return v8;
    }
    if (!dds3PadIsAnyKey())
      goto LABEL_64;
    Cursor = ProcessData->Cursor;
    *(u64 *)&Cursor->ScaleTimer = 6;
    v27 = get_Instance(0);
    if (!op_Inequality(v27, 0, 0))
    {
      goto LABEL_57;
    }
    v32 = get_Instance(0);
    TopCtr(v32, 0, 0);
LABEL_57:
    v31 = titleSeqUnit;
    jmsSeqJumpAndFree(&ProcessData->pSeqUnit, &v31[6]);
    SE(5242880);
    goto LABEL_64;
  }
  return v8;
}

// 0x2229b70
dds3ProcessFunc_t MainDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s64 v5;
  titleAlphaTable_t *v6;
  titleAlphaTable_t *v7;
  s64 v8;
  s32 klass_high;
  s32 v10;
  s64 v11;
  s64 v12;
  s32 v14;
  s32 v15;
  s32 v16;
  jmsSeqHandle_t *monitor;
  s64 v19;
  dds3ProcessID_t *v20;
  s32 v21;
  dds3ProcessFunc_t v22;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  v5 = NewSpecific(titleAlphaTable_t, 3u);
  v6 = Allocate(titleAlphaTable_t);
  *(u64 *)&v6->Frame = 0x3400000000LL;
  if (!QueryInterface(v6, *(void **)(*(u64 *)v5 + 64)))
    goto LABEL_32;
  *(u64 *)(v5 + 32) = v6;
  v7 = Allocate(titleAlphaTable_t);
  *(u64 *)&v7->Frame = (char *)&xmmword_38 + 4;
  {
LABEL_32:
  }
  *(u64 *)(v5 + 48) = v8;
  klass_high = HIDWORD(ProcessData[3].klass);
  v10 = *(u32 *)(v5 + 24);
  v11 = (v10 - 1) & (u32)~((v10 - 1) >> 31);
  v12 = v5 + 40;
  do
  {
    if (!v11)
      break;
    v14 = *(u32 *)(*(u64 *)(v12 - 8) + 16);
    v15 = *(u32 *)(*(u64 *)v12 + 16);
    v12 += 8;
    --v11;
  }
  while (v14 > klass_high || v15 <= klass_high);
  v16 = HIDWORD(ProcessData[3].klass);
  monitor = ProcessData[1].monitor;
  v19 = v5 + (((*(u64 *)(v5 + 24) << 32) - 0x100000000LL) >> 29);
  v20 = id;
  if (v16 + 1 <= *(u32 *)(*(u64 *)(v19 + 32) + 16))
    v21 = v16 + 1;
  else
    v21 = 0;
  HIDWORD(ProcessData[3].klass) = v21;
  v22 = jmsSeqChange(monitor, &ProcessData[2], 1, v20);
  jmsSeqChange(ProcessData[1].monitor, &ProcessData[2], 2, id);
  return v22;
}

// 0x2229ff0
s32 MainSubInit(dds3ProcessID_t *PID) {
  titleData_t *ProcessData;
  s32 v5;
  void *Instance;
  void *v10;
  void *v11;
  void *v17;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  ProcessData->Timer = 0;
  ProcessData->FadeOut = 0;
  v5 = !slSaveDataCheck();
  Instance = get_Instance(0);
  OpenMenuList(Instance, v5, 0);
  ProcessData->menu_plus = v5;
  if (ProcessData->inMenu)
  {
    moviePlay(33, 1, 1);
  }
  else
  {
    moviePlay(33, 1, 1);
    itfSetIsmesWndBaseDisp(1);
    ProcessData->inMenu = 1;
    JugeMovieFrameUpdate();
    v16 = PlayMainSubAt3(ProcessData);
    TitlePlayMovieSe();
    v17 = get_Instance(0);
    DispSubTitle(v17->startFrame, 1);
  }
  v10 = get_Instance(0);
  VerCtr(v10, 1, 0);
  ProcessData->Cursor->Index += ProcessData->menu_plus;
  v11 = get_Instance(0);
  TitleChangeCursor(v11, ProcessData->Cursor->Index, 0);
  GBWK->GameFileInfo->newfile = 0;
  return 1;
}

// 0x222a2e0
s32 MainSubDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x222a2f0
dds3ProcessFunc_t MainSubCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqUnit_t *v5;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v8;
  dds3ProcessFunc_t v9;
  void *Instance;
  s32 v16;
  s32 v21;
  void *v22;
  jmsSeqUnit_t *v24;
  jmsSeqUnit_t *v25;
  dds3ProcessID_t *v26;
  titleCursor_t *klass;
  void *v29;
  void *v30;
  void *v31;
  jmsSeqUnit_t *titleSeqUnit_local;
  void *v34;
  s32 v35;
  Il2CppClass *v36;
  Il2CppClass *v37;
  s32 v38;
  void *v39;
  jmsSeqUnit_t *v41;
  jmsSeqUnit_t *v43;
  jmsSeqUnit_t *v45;
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
  v8 = id;
  LODWORD(ProcessData[1].klass) |= 2u;
  v9 = jmsSeqChange(monitor, &ProcessData[2], 0, v8);
  if (v9)
    return v9;
  JugeMovieFrameUpdate();
  TitlePlayMovieSe();
  Instance = get_Instance(0);
  DispSubTitle(Instance->startFrame, 1);
  SubTitleDissolveCalc();
  if (LODWORD(ProcessData[4].monitor) != 1)
  {
    v26 = id;
    klass = ProcessData[4].klass;
    if (TitleCalcCursor(v26, klass, 0))
      LODWORD(ProcessData[2].monitor) = 0;
    if (CHECK_TRIG(4097, 1))
    {
      LODWORD(ProcessData[2].monitor) = 1200;
      v29 = get_Instance(0);
      if (op_Inequality(v29, 0, 0))
      {
        v30 = get_Instance(0);
        TopCtr(v30, 1, 0);
        v31 = get_Instance(0);
        ClossMenuList(v31, 0);
      }
    }
    if (SLODWORD(ProcessData[2].monitor) > 1199)
    {
      BYTE1(ProcessData[8].klass) = 0;
      titleSeqUnit_local = titleSeqUnit;
      jmsSeqJumpAndFree(&ProcessData[2], &titleSeqUnit_local[5]);
      SE(1);
      v34 = get_Instance(0);
      ClossMenuList(v34, 0);
      goto LABEL_105;
    }
    if (CHECK_TRIG(4096, 0))
    {
      v35 = *(&ProcessData[4].klass->_1.byval_arg.bits + 1);
      if (v35 && v35 != 3)
      {
        dds3FadeOut(0, 0, 0, 0xAu);
        v35 = *(&ProcessData[4].klass->_1.byval_arg.bits + 1);
      }
      if ((u32)(v35 - 2) < 2)
      {
        v38 = 0;
      }
      else
      {
        if (v35 != 1)
        {
          if (!v35)
            BYTE1(ProcessData[8].klass) = 0;
          goto LABEL_104;
        }
        v38 = 5242882;
      }
      SE(v38);
LABEL_104:
      LODWORD(ProcessData[4].monitor) = 1;
      goto LABEL_105;
    }
    if (CHECK_TRIG(48131, 1))
    {
      v36 = ProcessData[4].klass;
      LODWORD(ProcessData[4].monitor) = 1;
      LODWORD(ProcessData[8].monitor) = *(&v36->_1.byval_arg.bits + 1) - HIDWORD(ProcessData[8].klass);
      *(&v36->_1.byval_arg.bits + 1) = 5;
    }
    else
    {
      if (!CHECK_TRIG(48130, 1))
      {
LABEL_105:
        ++LODWORD(ProcessData[2].monitor);
        return v9;
      }
      v37 = ProcessData[4].klass;
      LODWORD(ProcessData[8].monitor) = *(&v37->_1.byval_arg.bits + 1) - HIDWORD(ProcessData[8].klass);
      *(&v37->_1.byval_arg.bits + 1) = 4;
      LODWORD(ProcessData[4].monitor) = 1;
      dds3FadeOut(0, 0, 0, 0x1Eu);
    }
    SE(0);
    goto LABEL_105;
  }
  if (!dds3FadeCheck())
  {
    v16 = *(&ProcessData[4].klass->_1.byval_arg.bits + 1);
    if (!v16 || v16 == 3)
    {
LABEL_30:
      switch (*(&ProcessData[4].klass->_1.byval_arg.bits + 1))
      {
        case 0u:
        case 1u:
          v22 = get_Instance(0);
          VerCtr(v22, 0, 0);
          v24 = titleSeqUnit;
          v25 = &v24[7];
          goto LABEL_98;
        case 2u:
          v39 = get_Instance(0);
          VerCtr(v39, 0, 0);
          v41 = titleSeqUnit;
          jmsSeqJumpAndFree(&ProcessData[2], &v41[8]);
          *(&ProcessData[4].klass->_1.byval_arg.bits + 1) -= HIDWORD(ProcessData[8].klass);
          return v9;
        case 3u:
          if (!p2sdIsPlaySE(0))
          {
            (Inctance->klass->vtable._5_OpenDLCBrowser.methodPtr)(Inctance, Inctance->klass->vtable._5_OpenDLCBrowser.method);
            LODWORD(ProcessData[4].monitor) = 0;
          }
          return v9;
        case 4u:
          v43 = titleSeqUnit;
          v25 = &v43[15];
          goto LABEL_98;
        case 5u:
          v45 = titleSeqUnit;
          v25 = &v45[10];
LABEL_98:
          jmsSeqJumpAndFree(v5, v25);
          break;
        default:
          return v9;
      }
      return v9;
    }
    movieNowFrame = 0;
    movieOldFrame = 0;
    movieFrameOverCount = 0;
    p2sdSndStop(62);
    DispSubTitle(-1, 0);
    movieNowFrame = 0;
    movieOldFrame = 0;
    v21 = *(&ProcessData[4].klass->_1.byval_arg.bits + 1) == 2;
    movieStop(v21);
    goto LABEL_30;
  }
  return v9;
}

// 0x222aa70
dds3ProcessFunc_t MainSubDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
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
  v7 = id;
  v8 = jmsSeqChange(monitor, &ProcessData[2], 1, v7);
  jmsSeqChange(ProcessData[1].monitor, &ProcessData[2], 2, id);
  return v8;
}

// 0x2227190
bool MainTitleFirstSave(titleData_t *data) {
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v9;
  dds3ProcessFunc_t v13;
  dds3ProcessID_t *v14;
  dds3ProcessFunc_t v16;
  dds3ProcessID_t *SuspendID_local;

  if (FirstSaveProc == 2)
  {
    data->saveFlag = 0;
    return 0;
  }
  if (FirstSaveProc == 1)
  {
    v16 = (SuspendID->processfunc->invoke_impl)(SuspendID->processfunc->method_code);
    SuspendFunc = v16;
    if (SuspendFunc)
    {
      SuspendID_local = SuspendID;
      SuspendID_local->processfunc = SuspendFunc;
    }
    slGetSaveResultType();
    data->dlcMesSave = 0;
    FirstSaveProc = 2;
    return 1;
  }
  if (FirstSaveProc)
    return 0;
  if (data->saveFlag)
  {
    v6 = Allocate(dds3ProcessID_t);
    _ctor(v6, 0);
    SuspendID = v6;
    v9 = slSystemDataProc();
    SuspendFunc = v9;
    v13 = SuspendFunc;
    if (v13)
    {
      v13 = SuspendFunc;
      v14 = SuspendID;
      v14->processfunc = v13;
    }
    FirstSaveProc = 1;
    return 1;
  }
  else
  {
    FirstSaveProc = 2;
    return 0;
  }
}

// 0x2227e00
static bool DLCChack(titleData_t *data) {
  s8 *dlcflg;
  bool v5;
  s8 *v8;
  s8 *v10;
  s8 *v12;
  s8 *v14;
  s8 *v16;
  s8 *v18;
  s8 *v20;
  s8 *v22;

  if (Exists("new_exp"))
  {
LABEL_14:
    v5 = 0;
    goto LABEL_16;
  }
  dlcflg = SystemWork->dlcflg;
  if (!dlcflg[0])
    goto LABEL_14;
  dlcflg = SystemWork->dlcflg;
  v5 = 1;
  dlcflg[0] = 0;
LABEL_16:
  if (!Exists("new_oni"))
  {
    v8 = SystemWork->dlcflg;
    if (v8[1])
    {
      v8 = SystemWork->dlcflg;
      v5 = 1;
      v8[1] = 0;
    }
  }
  if (!Exists("new_devil"))
  {
    v10 = SystemWork->dlcflg;
    if (v10[2])
    {
      v10 = SystemWork->dlcflg;
      v5 = 1;
      v10[2] = 0;
    }
  }
  if (!Exists("new_title"))
  {
    v12 = SystemWork->dlcflg;
    if (v12[3])
    {
      v12 = SystemWork->dlcflg;
      v5 = 1;
      v12[3] = 0;
    }
  }
  if (!Exists("new_dbook"))
  {
    v14 = SystemWork->dlcflg;
    if (v14[4])
    {
      v14 = SystemWork->dlcflg;
      v5 = 1;
      v14[4] = 0;
    }
  }
  if (!Exists("new_glasses"))
  {
    v16 = SystemWork->dlcflg;
    if (v16[5])
    {
      v16 = SystemWork->dlcflg;
      v5 = 1;
      v16[5] = 0;
    }
  }
  if (!Exists("new_skill"))
  {
    v18 = SystemWork->dlcflg;
    if (v18[6])
    {
      v18 = SystemWork->dlcflg;
      v5 = 1;
      v18[6] = 0;
    }
  }
  if (!Exists("new_item"))
  {
    v20 = SystemWork->dlcflg;
    if (v20[7])
    {
      v20 = SystemWork->dlcflg;
      v5 = 1;
      v20[7] = 0;
    }
  }
  if (Exists("new_crm"))
    return v5;
  v22 = SystemWork->dlcflg;
  if (!v22[8])
    return v5;
  v22 = SystemWork->dlcflg;
  v22[8] = 0;
  return 1;
}

// 0x222ac00
s32 TitleEndWaitInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  LODWORD(ProcessData[6].monitor) = 0;
  return 1;
}

// 0x222ace0
s32 TitleEndWaitDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x222acf0
dds3ProcessFunc_t TitleEndWaitCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t result;
  s32 klass;
  s32 v9;
  s32 v10;
  Il2CppClass *v11;
  jmsSeqUnit_t *titleSeqUnit_local;
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
  result = jmsSeqChange(monitor, &ProcessData[2], 0, v6);
  if (!result)
  {
    klass = ProcessData[1].klass;
    if ((klass & 0x60) == 0x20)
    {
      LODWORD(ProcessData[1].klass) = klass | 0x40;
      return 0;
    }
    LODWORD(ProcessData[5].klass) = 0;
    LODWORD(ProcessData[1].klass) = klass & 0xFFFFFF9F;
    v9 = *(&ProcessData[4].klass->_1.byval_arg.bits + 1);
    if (v9 == 1)
    {
      titleSeqUnit_local = titleSeqUnit;
      jmsSeqJumpAndFree(&ProcessData[2], &titleSeqUnit_local[12]);
      *(&ProcessData[4].klass->_1.byval_arg.bits + 1) = 0;
    }
    else if (!v9)
    {
      v10 = ProcessData[6].monitor;
      if (v10)
      {
        if (v10 >= 10)
        {
          dds3AdminiCallSequence(3, 0, 0);
          v11 = ProcessData[4].klass;
          LODWORD(ProcessData[6].monitor) = 0;
          *(&v11->_1.byval_arg.bits + 1) = 0;
        }
      }
      else
      {
        SE(5242882);
        dds3FadeOut(0, 0, 0, 0xAu);
      }
    }
    ++LODWORD(ProcessData[6].monitor);
    return 0;
  }
  return result;
}

// 0x222afa0
dds3ProcessFunc_t TitleEndWaitDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
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
  v7 = jmsSeqChange(monitor, &ProcessData[2], 1, v6);
  jmsSeqChange(ProcessData[1].monitor, &ProcessData[2], 2, id);
  return v7;
}

// 0x222b0f0
s32 TitleConfigInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *Instance;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  LODWORD(ProcessData[2].monitor) = 0;
  Instance = get_Instance(0);
  ClossMenuList(Instance, 0);
  Delete(0);
  ProcessStart(0);
  return 1;
}

// 0x222b230
s32 TitleConfigDestroy(dds3ProcessID_t *PID) {
  titleData_t *ProcessData;
  s32 result;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  result = TitleAt3Load(ProcessData, 80);
  if (result)
  {
    if ((ProcessData->Flag & 0x18) != 8)
      return 1;
    sndBgmPlay(0, 0);
    ProcessData->Flag |= 0x10u;
    return 1;
  }
  return result;
}

// 0x222b3e0
dds3ProcessFunc_t TitleConfigCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqUnit_t *v5;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  jmsSeqUnit_t *titleSeqUnit_local;
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
  v8 = jmsSeqChange(monitor, v5, 0, v7);
  if (v8)
    return v8;
  if (!!ProcessCheck())
    return v8;
  dds3FadeIn(0, 0, 0, 0xAu);
  ButtonGuideDispOff();
  Create(0);
  fclLinkData(sys);
  titleSeqUnit_local = titleSeqUnit;
  jmsSeqJumpAndFree(v5, &titleSeqUnit_local[6]);
  return 0;
}

// 0x222b680
dds3ProcessFunc_t TitleConfigDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
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
  v7 = jmsSeqChange(monitor, &ProcessData[2], 1, v6);
  jmsSeqChange(ProcessData[1].monitor, &ProcessData[2], 2, id);
  return v7;
}

// 0x222b7d0
s32 TitleAdvertiseInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  HIDWORD(ProcessData[6].klass) = 0;
  ProcessData[2].monitor = 0;
  return 1;
}

// 0x222b8b0
s32 TitleAdvertiseDestroy(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 v5;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = LODWORD(ProcessData[6].klass) + 1;
  LODWORD(ProcessData[6].klass) = v5;
  if (v5 < SLODWORD(titleAdvMovieList->max_length))
    return 1;
  LODWORD(ProcessData[6].klass) = 0;
  return 1;
}

// 0x222ba10
dds3ProcessFunc_t TitleAdvertiseCalcProcess(dds3ProcessID_t *PID) {
  titleData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v8;
  s32 AdvSkipFlag;
  s64 v13;
  u32 v14;
  s32 SkipTimer;
  jmsSeqUnit_t *titleSeqUnit_local;
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
  SeqHandle = ProcessData->SeqHandle;
  v6 = id;
  v8 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v6);
  if (!v8)
  {
    if (TitleAt3Load(ProcessData, 80))
    {
      switch (TitleMoviePlay((s32)TitleMain, 0, 0, 0, ProcessData))
      {
        case 0:
          return v8;
        case 1:
          dds3FadeIn(0, 0, 0, 0);
          AdvSkipFlag = ProcessData->AdvSkipFlag;
          if (AdvSkipFlag != 2)
            goto LABEL_30;
          goto LABEL_40;
        case 2:
          if (!ProcessData->AdvSkipFlag)
          {
            if (CHECK_TRIG(4096, 1))
              ProcessData->AdvSkipFlag = 1;
            if (CHECK_TRIG(4110, 1))
              ProcessData->AdvSkipFlag = 1;
          }
          ++ProcessData->Timer;
          goto LABEL_29;
        case 3:
          titleSeqUnit_local = titleSeqUnit;
          jmsSeqJumpAndFree(&ProcessData->pSeqUnit, &titleSeqUnit_local[3]);
          AdvSkipFlag = ProcessData->AdvSkipFlag;
          if (AdvSkipFlag == 2)
            goto LABEL_40;
          goto LABEL_30;
        default:
LABEL_29:
          AdvSkipFlag = ProcessData->AdvSkipFlag;
          if (AdvSkipFlag == 2)
          {
LABEL_40:
            dds3FadeSet_2(0xFFu, 0xFFu, 0xFFu, 0x80u);
            Flag = ProcessData->Flag;
            if ((Flag & 0x60) == 0x20)
            {
              ProcessData->Flag = Flag | 0x40;
            }
            else
            {
              ProcessData->MovieCounter = 0;
              ProcessData->Flag = Flag & 0xFFFFFF9F;
              TitleGoMain(ProcessData);
            }
          }
          else
          {
LABEL_30:
            if (AdvSkipFlag == 1)
            {
              v13 = 1717986919 * (ProcessData->SkipTimer << 7);
              v14 = (v13 >> 33) + ((u64)v13 >> 63);
              dds3FadeSet_2(0xFFu, 0xFFu, 0xFFu, v14);
              SkipTimer = ProcessData->SkipTimer;
              if (SkipTimer <= 4)
                ProcessData->SkipTimer = SkipTimer + 1;
              else
                ProcessData->AdvSkipFlag = 2;
            }
          }
          break;
      }
    }
  }
  return v8;
}

// 0x222bfd0
dds3ProcessFunc_t TitleAdvertiseDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
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
  v7 = jmsSeqChange(monitor, &ProcessData[2], 1, v6);
  jmsSeqChange(ProcessData[1].monitor, &ProcessData[2], 2, id);
  return v7;
}

// 0x222c120
s32 TitleSettingNoteInit(dds3ProcessID_t *PID) {
  void *Instance;
  void *v5;
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  Instance = get_Instance(0);
  ClossMenuList(Instance, 0);
  v5 = get_Instance(0);
  SettingNoteCtr(v5, 1, 0);
  return 1;
}

// 0x222c210
s32 TitleSettingNoteDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x222c220
dds3ProcessFunc_t TitleSettingNoteCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqUnit_t *v5;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  jmsSeqUnit_t *titleSeqUnit_local;
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
  v8 = jmsSeqChange(monitor, v5, 0, v7);
  if (v8 || !CHECK_TRIG(4096, 1))
    return v8;
  titleSeqUnit_local = titleSeqUnit;
  jmsSeqJumpAndFree(v5, &titleSeqUnit_local[12]);
  return 0;
}

// 0x222c3e0
dds3ProcessFunc_t TitleSettingNoteDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
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
  v7 = jmsSeqChange(monitor, &ProcessData[2], 1, v6);
  jmsSeqChange(ProcessData[1].monitor, &ProcessData[2], 2, id);
  return v7;
}

// 0x222c530
s32 TitleLevelInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *Instance;
  char klass;
  void *v8;
  void *v9;
  void *v10;
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
  ClossMenuList(Instance, 0);
  klass = ProcessData[8].klass;
  if (klass)
  {
    klass = 1;
    LOBYTE(ProcessData[8].klass) = 0;
  }
  BYTE4(ProcessData[8].monitor) = klass;
  HIDWORD(ProcessData[4].klass->_1.this_arg.data) = 2;
  v8 = get_Instance(0);
  SettingNoteCtr(v8, 0, 0);
  v9 = get_Instance(0);
  OpenLvSelectMenu(v9, 0);
  v10 = get_Instance(0);
  LevelSelectCursor(v10, HIDWORD(ProcessData[4].klass->_1.this_arg.data), 0, 0);
  return 1;
}

// 0x222c6c0
s32 TitleLevelDestroy(dds3ProcessID_t *PID) {
  titleData_t *ProcessData;
  s32 Flag;
  s32 result;
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
  if ((Flag & 8) == 0)
  {
    ProcessData->Flag = Flag & 0xFFFFFFE3;
    result = TitleAt3Load(ProcessData, 80);
    if (!result)
      return result;
LABEL_19:
    if ((ProcessData->Flag & 0x18) != 8)
      return 1;
    sndBgmPlay(0, 0);
    ProcessData->Flag |= 0x10u;
    return 1;
  }
  sndBgmStop();
  sndBgmFree();
  ProcessData->Flag &= 0xFFFFFFE3;
  result = TitleAt3Load(ProcessData, 80);
  if (result)
    goto LABEL_19;
  return result;
}

// 0x222c910
dds3ProcessFunc_t TitleLevelCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqUnit_t *v5;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  dds3ProcessID_t *v10;
  titleCursor_t *klass;
  jmsSeqUnit_t *titleSeqUnit_local;
  void *Instance;
  void *v15;
  void *v16;
  void *v17;
  jmsSeqUnit_t *v19;
  jmsSeqUnit_t *v20;
  jmsSeqUnit_t *v22;
  void *v23;
  jmsSeqUnit_t *v27;
  void *v29;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  v5 = &ProcessData[2];
  monitor = ProcessData[1].monitor;
  v7 = id;
  v8 = jmsSeqChange(monitor, &ProcessData[2], 0, v7);
  if (!v8)
  {
    if (dds3FadeCheck())
      return v8;
    if (movieCheckStandby())
    {
      if (dds3FadeCheck())
        goto LABEL_24;
      goto LABEL_9002;
      if (dds3FadeCheck())
      {
LABEL_24:
        v10 = id;
        klass = ProcessData[4].klass;
        TitleCalcCursor(v10, klass, 1);
        if (CHECK_TRIG(4096, 0))
        {
          switch (HIDWORD(ProcessData[4].klass->_1.this_arg.data))
          {
            case 0:
            case 1:
            case 2:
            case 3:
              SE(5242882);
              titleSeqUnit_local = titleSeqUnit;
              jmsSeqJumpAndFree(v5, &titleSeqUnit_local[13]);
              Instance = get_Instance(0);
              if (op_Inequality(Instance, 0, 0))
              {
                v15 = get_Instance(0);
                ClossLvSelectMenu(v15, 1, 0);
              }
              return v8;
            case 4:
              SE(5242882);
              v23 = get_Instance(0);
              if (!op_Inequality(v23, 0, 0))
              {
                goto LABEL_71;
              }
              v29 = get_Instance(0);
              ClossLvSelectMenu(v29, 1, 0);
LABEL_71:
              v27 = titleSeqUnit;
              v20 = &v27[13];
              goto LABEL_73;
            default:
              return v8;
          }
        }
        if (CHECK_TRIG(4097, 1))
        {
          v16 = get_Instance(0);
          if (op_Inequality(v16, 0, 0) && !LOBYTE(ProcessData[10].klass))
          {
            v17 = get_Instance(0);
            ClossLvSelectMenu(v17, 0, 0);
            dds3FadeIn(0, 0, 0, 0x28u);
          }
          SE(1);
          if (LOBYTE(ProcessData[10].klass))
          {
            LOBYTE(ProcessData[8].klass) = 1;
            v19 = titleSeqUnit;
            v20 = &v19[16];
          }
          else
          {
            v22 = titleSeqUnit;
            v20 = &v22[6];
          }
LABEL_73:
          jmsSeqJumpAndFree(v5, v20);
        }
        return v8;
      }
LABEL_9002:
      if (!BYTE4(ProcessData[8].monitor))
      {
        dds3FadeIn(0, 0, 0, 0x1Eu);
        BYTE4(ProcessData[8].monitor) = 1;
        return v8;
      }
      goto LABEL_24;
    }
  }
  return v8;
}

// 0x222cec0
dds3ProcessFunc_t TitleLevelDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
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
  v7 = jmsSeqChange(monitor, &ProcessData[2], 1, v6);
  jmsSeqChange(ProcessData[1].monitor, &ProcessData[2], 2, id);
  return v7;
}

// 0x222d010
s32 TitleLevelCheckInit(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  LevelCheckProc = 0;
  itfSetIsmesWndBaseDisp(1);
  return 1;
}

// 0x222d100
s32 TitleLevelCheckDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x222d110
dds3ProcessFunc_t TitleLevelCheckCalcProcess(dds3ProcessID_t *PID) {
  titleData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
  s32 Timer;
  s32 v12;
  s32 SelMessagePos;
  s32 v17;
  s64 v19;
  s32 v20;
  jmsSeqUnit_t *titleSeqUnit_local;
  s32 LevelIndex;
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
  if (!v7)
  {
    fclUpdateMessage();
    if (fclChkMessage())
      return v7;
    switch (LevelCheckProc)
    {
      case 0:
        Reset(0);
        fclSetMessageInvalid(1);
        fclStartMessage(11);
        LevelCheckProc = 1;
        return v7;
      case 1:
        Timer = ProcessData->Timer;
        if (Timer < 9)
        {
          v12 = Timer + 1;
          goto LABEL_45;
        }
        fclSetMessageInvalid(0);
        fclStartMessage(12);
        fclStartSelMessage(9);
        fclSetSelMessagePos(1);
        fclSetSelCancelPos(1);
        ProcessData->Timer = 0;
        LevelCheckProc = 2;
        return v7;
      case 2:
        if (fclChkSelMessage())
          return v7;
        SelMessagePos = fclGetSelMessagePos();
        if (SelMessagePos != 1)
        {
          if (SelMessagePos)
            return v7;
          SelectYesSe = -1;
          fclEndMessage();
          TitleAt3Stop(ProcessData);
          TitleNewGameStart(v17);
          if (ProcessData->Cursor->LevelIndex == 4)
            sub_1A21FE0(2961, 0, v19);
          else
            sub_1B34170(2961, 0);
          LevelIndex = ProcessData->Cursor->LevelIndex;
          cfgSetConfigGAME(1, LevelIndex, 0);
          ProcessData->HoverCheckReturn = 0;
          return v7;
        }
        SelectYesSe = -1;
        fclEndMessage();
        LevelCheckProc = 3;
        ProcessData->LevelCheckReturn = 1;
        return v7;
      case 3:
        v20 = ProcessData->Timer;
        if (v20 >= 14)
        {
          titleSeqUnit_local = titleSeqUnit;
          jmsSeqJumpAndFree(&ProcessData->pSeqUnit, &titleSeqUnit_local[12]);
          v20 = 0;
          LevelCheckProc = 0;
        }
        v12 = v20 + 1;
LABEL_45:
        ProcessData->Timer = v12;
        return v7;
      default:
        return v7;
    }
  }
  return v7;
}

// 0x222d6f0
dds3ProcessFunc_t TitleLevelCheckDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
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
  v7 = jmsSeqChange(monitor, &ProcessData[2], 1, v6);
  jmsSeqChange(ProcessData[1].monitor, &ProcessData[2], 2, id);
  return v7;
}

// 0x222d840
s32 TitleDLCInit(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  itfSetIsmesWndBaseDisp(1);
  return 1;
}

// 0x222d920
s32 TitleDLCDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x222d930
dds3ProcessFunc_t TitleDLCCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqUnit_t *v5;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  void *Instance;
  dds3ProcessID_t *v17;
  s32 v18;
  dds3ProcessFunc_t result;
  s32 v21;
  dds3ProcessFunc_t v22;
  dds3ProcessFunc_t v25;
  dds3ProcessID_t *v26;
  jmsSeqUnit_t *titleSeqUnit_local;
  dds3ProcessID_t *v29;
  dds3ProcessFunc_t v32;
  dds3ProcessID_t *SuspendID_local;
  s32 v38;
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
  JugeMovieFrameUpdate();
  TitlePlayMovieSe();
  Instance = get_Instance(0);
  DispSubTitle(Instance->startFrame, 1);
  SubTitleDissolveCalc();
  fclUpdateMessage();
  if (!!fclChkMessage())
    return v8;
  switch (DLCGameProc)
  {
    case 0:
      v17 = id;
      titleDLCMsgDraw(v17);
      v18 = 1;
      goto LABEL_40;
    case 1:
      v21 = ProcessData[2].monitor;
      if (v21 >= 16)
      {
        if (HIDWORD(ProcessData[7].monitor))
        {
          v29 = Allocate(dds3ProcessID_t);
          _ctor(v29, 0);
          SuspendID = v29;
          v32 = slSystemDataProc();
          SuspendFunc = v32;
          if (SuspendFunc)
          {
            SuspendID_local = SuspendID;
            SuspendID_local->processfunc = SuspendFunc;
          }
          v38 = 2;
        }
        else
        {
          v38 = 3;
        }
        DLCGameProc = v38;
        LODWORD(ProcessData[2].monitor) = 0;
        return 0;
      }
      else
      {
        LODWORD(ProcessData[2].monitor) = v21 + 1;
        return 0;
      }
    case 2:
      v22 = (SuspendID->processfunc->invoke_impl)(SuspendID->processfunc->method_code);
      SuspendFunc = v22;
      v25 = SuspendFunc;
      if (v25)
      {
        v25 = SuspendFunc;
        v26 = SuspendID;
        v26->processfunc = v25;
      }
      slGetSaveResultType();
      v18 = 3;
      HIDWORD(ProcessData[7].monitor) = 0;
LABEL_40:
      DLCGameProc = v18;
      result = 0;
      break;
    case 3:
      titleSeqUnit_local = titleSeqUnit;
      jmsSeqJumpAndFree(v5, &titleSeqUnit_local[5]);
      DLCGameProc = 0;
      result = 0;
      break;
    default:
      return v8;
  }
  return result;
}

// 0x222e2f0
dds3ProcessFunc_t TitleDLCDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
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
  v7 = jmsSeqChange(monitor, &ProcessData[2], 1, v6);
  jmsSeqChange(ProcessData[1].monitor, &ProcessData[2], 2, id);
  return v7;
}

// 0x2229320
static bool titleDLCMsgCheck(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 v8;
  s32 v9;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (fclChkMessage())
    return 0;
  if (!Exists("new_exp"))
    goto LABEL_20;
  if (SystemWork->dlcflg[0])
    goto LABEL_20;
  v8 = 0;
  v9 = 281;
LABEL_46:
  mapHukidashiEndOff(v9);
  HIDWORD(ProcessData[7].klass) = v8;
  return 1;
LABEL_20:
  if (!Exists("new_oni"))
    goto LABEL_26;
  if (SystemWork->dlcflg[1])
    goto LABEL_26;
  v8 = 1;
  v9 = 282;
  goto LABEL_46;
LABEL_26:
  if (!!Exists("new_devil"))
  {
    if (!SystemWork->dlcflg[2])
    {
      HIDWORD(ProcessData[7].klass) = 2;
      return 1;
    }
  }
  if (!!Exists("new_title"))
  {
    if (!SystemWork->dlcflg[3])
    {
      HIDWORD(ProcessData[7].klass) = 3;
      return 1;
    }
  }
  if (!!Exists("new_dbook"))
  {
    if (!SystemWork->dlcflg[4])
    {
      HIDWORD(ProcessData[7].klass) = 4;
      return 1;
    }
  }
  if (!!Exists("new_glasses"))
  {
    if (!SystemWork->dlcflg[5])
    {
      HIDWORD(ProcessData[7].klass) = 5;
      return 1;
    }
  }
  if (!!Exists("new_skill"))
  {
    if (!SystemWork->dlcflg[6])
    {
      HIDWORD(ProcessData[7].klass) = 6;
      return 1;
    }
  }
  if (!!Exists("new_item"))
  {
    if (!SystemWork->dlcflg[7])
    {
      HIDWORD(ProcessData[7].klass) = 7;
      return 1;
    }
  }
  if (!Exists("new_crm"))
    goto LABEL_83;
  if (SystemWork->dlcflg[8])
  {
LABEL_83:
    if (LODWORD(ProcessData[7].monitor) == 1)
    {
      HIDWORD(ProcessData[7].klass) = 100;
      return 1;
    }
    return 0;
  }
  HIDWORD(ProcessData[7].klass) = 8;
  return 1;
}

// 0x222de00
static bool titleDLCMsgDraw(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 v5;
  s32 klass_high;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = fclChkMessage();
  if (v5)
    return v5 == 0;
  Reset(0);
  klass_high = HIDWORD(ProcessData[7].klass);
  switch (klass_high)
  {
    case 0:
      fclSetMessageInvalid(1);
      fclStartMessage(0);
      SystemWork->dlcflg[0] = 1;
      goto LABEL_63;
    case 1:
      fclSetMessageInvalid(1);
      fclStartMessage(3);
      SystemWork->dlcflg[1] = 1;
      goto LABEL_63;
    case 2:
      fclSetMessageInvalid(1);
      fclStartMessage(13);
      SystemWork->dlcflg[2] = 1;
      goto LABEL_63;
    case 3:
      fclSetMessageInvalid(1);
      fclStartMessage(5);
      SystemWork->dlcflg[3] = 1;
      goto LABEL_63;
    case 4:
      fclSetMessageInvalid(1);
      fclStartMessage(6);
      SystemWork->dlcflg[4] = 1;
      goto LABEL_63;
    case 5:
      fclSetMessageInvalid(1);
      fclStartMessage(16);
      SystemWork->dlcflg[5] = 1;
      goto LABEL_63;
    case 6:
      fclSetMessageInvalid(1);
      fclStartMessage(14);
      SystemWork->dlcflg[6] = 1;
      goto LABEL_63;
    case 7:
      fclSetMessageInvalid(1);
      fclStartMessage(15);
      SystemWork->dlcflg[7] = 1;
      goto LABEL_63;
    case 8:
      fclSetMessageInvalid(1);
      fclStartMessage(17);
      SystemWork->dlcflg[8] = 1;
LABEL_63:
      LODWORD(ProcessData[7].monitor) = 1;
      break;
    default:
      if (klass_high == 100)
      {
        fclSetMessageInvalid(1);
        fclStartMessage(8);
        ProcessData[7].monitor = 0x100000000LL;
      }
      break;
  }
  HIDWORD(ProcessData[7].klass) = -1;
  return v5 == 0;
}

// 0x222e440
s32 TitleCreditsInit(dds3ProcessID_t *PID) {
  titleData_t *ProcessData;
  void *Instance;
  void *v6;
  s32 Flag;
  void *v8;
  s32 result;
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
  ClossMenuList(Instance, 0);
  v6 = get_Instance(0);
  ChangeFadeOutTime(v6, 60, 0);
  Flag = ProcessData->Flag;
  if ((Flag & 8) != 0)
  {
    sndBgmStop();
    sndBgmFree();
    Flag = ProcessData->Flag;
  }
  ProcessData->Flag = Flag & 0xFFFFFFE3;
  v8 = get_Instance(0);
  OpenCredits(v8, 0);
  dds3FadeIn(0, 0, 0, 0xAu);
  result = TitleAt3Load(ProcessData, 14);
  if (result)
  {
    if ((ProcessData->Flag & 0x18) != 8)
    {
LABEL_27:
      CreditsInit();
      return 1;
    }
    sndBgmPlayLoop(0);
    ProcessData->Flag |= 0x10u;
    goto LABEL_27;
  }
  return result;
}

// 0x222e7e0
s32 TitleCreditsDestroy(dds3ProcessID_t *PID) {
  titleData_t *ProcessData;
  s32 Flag;
  s32 result;
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
  if ((Flag & 8) == 0)
  {
    ProcessData->Flag = Flag & 0xFFFFFFE3;
    goto LABEL_13;
  }
  sndBgmStop();
  sndBgmFree();
  ProcessData->Flag &= 0xFFFFFFE3;
LABEL_13:
  CreditsDestroy();
  result = TitleAt3Load(ProcessData, 80);
  if (!result)
    return result;
  if ((ProcessData->Flag & 0x18) != 8)
    return 1;
  sndBgmPlay(0, 0);
  ProcessData->Flag |= 0x10u;
  return 1;
}

// 0x222ea80
dds3ProcessFunc_t TitleCreditsCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
  jmsSeqUnit_t *titleSeqUnit_local;
  void *Instance;
  void *v11;
  jmsSeqUnit_t *v16;
  void *v17;
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
  v7 = jmsSeqChange(monitor, &ProcessData[2], 0, v6);
  if (!v7)
  {
    if (CHECK_TRIG(4097, 1))
    {
      titleSeqUnit_local = titleSeqUnit;
      jmsSeqJumpAndFree(&ProcessData[2], &titleSeqUnit_local[6]);
      Instance = get_Instance(0);
      CloseCredits(Instance, 0);
      dds3FadeIn(0, 0, 0, 0x28u);
      v11 = get_Instance(0);
      ChangeFadeOutTime(v11, 60, 0);
      goto LABEL_41;
    }
    if (!is_end)
    {
LABEL_25:
      CalcProcess(0);
      return v7;
    }
    v16 = titleSeqUnit;
    jmsSeqJumpAndFree(&ProcessData[2], &v16[6]);
    v17 = get_Instance(0);
    CloseCredits(v17, 0);
    dds3FadeIn(0, 0, 0, 0x28u);
LABEL_41:
    *(&ProcessData[4].klass->_1.byval_arg.bits + 1) = (u32)ProcessData[8].monitor;
    goto LABEL_25;
  }
  return v7;
}

// 0x222ee30
dds3ProcessFunc_t TitleCreditsDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
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
  v7 = jmsSeqChange(monitor, &ProcessData[2], 1, v6);
  jmsSeqChange(ProcessData[1].monitor, &ProcessData[2], 2, id);
  if (v7)
    return v7;
  DrawProcess(0);
  return 0;
}

// 0x222efd0
s32 TitleRightsNoteInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *Instance;
  void *v6;
  void *v7;
  s32 klass;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  BYTE4(ProcessData[8].monitor) = 0;
  HIDWORD(ProcessData[6].monitor) = 0;
  HIDWORD(ProcessData[9].monitor) = 0;
  Instance = get_Instance(0);
  ClossMenuList(Instance, 0);
  v6 = get_Instance(0);
  title_backCtr(v6, 0, 0);
  v7 = get_Instance(0);
  OpenRightsNote(v7, 1, 0);
  LOBYTE(ProcessData[9].monitor) = 0;
  klass = ProcessData[1].klass;
  if ((klass & 8) != 0)
  {
    sndBgmStop();
    sndBgmFree();
    klass = ProcessData[1].klass;
  }
  LODWORD(ProcessData[1].klass) = klass & 0xFFFFFFE3;
  return 1;
}

// 0x222f1c0
s32 TitleRightsNoteDestroy(dds3ProcessID_t *PID) {
  titleData_t *ProcessData;
  s32 result;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  result = TitleAt3Load(ProcessData, 80);
  if (result)
  {
    if ((ProcessData->Flag & 0x18) != 8)
      return 1;
    sndBgmPlay(0, 0);
    ProcessData->Flag |= 0x10u;
    return 1;
  }
  return result;
}

// 0x222f370
dds3ProcessFunc_t TitleRightsNoteCalcProcess(dds3ProcessID_t *PID) {
  titleData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
  bool v8;
  _BOOL4 fadeChack;
  void *Instance;
  jmsSeqUnit_t *titleSeqUnit_local;
  void *v14;
  void *v15;
  void *v17;
  void *v18;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  SeqHandle = ProcessData->SeqHandle;
  v6 = id;
  v7 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v6);
  if (v7)
    return v7;
  if (dds3FadeCheck())
    return v7;
  if (!movieCheckStandby())
    return v7;
  v8 = dds3FadeCheck();
  fadeChack = ProcessData->fadeChack;
  if (v8)
    goto LABEL_21;
  if (!fadeChack)
  {
    ProcessData->fadeChack = 1;
    return v7;
  }
LABEL_25:
  if (!ProcessData->fadeStep)
  {
    dds3FadeIn(0, 0, 0, 0x1Eu);
    ProcessData->fadeStep = 1;
    return v7;
  }
  goto LABEL_26;
LABEL_21:
  if (fadeChack)
    goto LABEL_25;
LABEL_26:
  if (!dds3FadeCheck() && ProcessData->licenceFade)
  {
    dds3FadeIn(0, 0, 0, 0x1Eu);
    Instance = get_Instance(0);
    ClossRightsNote(Instance, 0);
    ProcessData->licenceFade = 0;
    titleSeqUnit_local = titleSeqUnit;
    jmsSeqJumpAndFree(&ProcessData->pSeqUnit, &titleSeqUnit_local[6]);
  }
  if (get_Instance(0)->isCalculate)
  {
    v14 = get_Instance(0);
    CalculateMaxDisplayLines(v14, ProcessData, 0);
  }
  if (CHECK_TRIG(4097, 1))
  {
    ProcessData->Cursor->Index = ProcessData->oldIndex;
    v15 = get_Instance(0);
    title_backCtr(v15, 1, 0);
    ProcessData->licenceFade = 1;
    dds3FadeOut(0, 0, 0, 0x1Eu);
    SE(1);
    if (!CHECK_REP(4101, 1))
    {
LABEL_47:
      if (!CHECK_REP(4100, 1))
        return v7;
      goto LABEL_57;
    }
  }
  else if (!CHECK_REP(4101, 1))
  {
    goto LABEL_47;
  }
  v17 = get_Instance(0);
  TextScrollCtrl(v17, ProcessData, -1, 0);
  if (CHECK_REP(4100, 1))
  {
LABEL_57:
    v18 = get_Instance(0);
    TextScrollCtrl(v18, ProcessData, 1, 0);
  }
  return v7;
}

// 0x222f7f0
dds3ProcessFunc_t TitleRightsNoteDrawProcess(dds3ProcessID_t *PID) {
  titleData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
  void *Instance;
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
  v7 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 1, v6);
  jmsSeqChange(ProcessData->SeqHandle, &ProcessData->pSeqUnit, 2, id);
  if (v7)
    return v7;
  Instance = get_Instance(0);
  DrawScrollArrowLight(Instance, ProcessData, 0);
  return 0;
}

// 0x222f990
s32 TitleCheckNumArea(s32 Val, s32 Min, s32 Max) {
  return Val >= Min && Val < Max;
}

// 0x2229ed0
s32 TitleCalcAlphaRate(s32 NowFrame, titleAlphaTable_t *pTable, s32 TableNums) {
  s64 v7;
  titleAlphaTable_t *v8;
  s32 v9;
  s64 v10;
  s32 Frame;
  s32 v13;
  titleAlphaTable_t *m_Items;
  u32 v15;
  titleAlphaTable_t *v16;
  titleAlphaTable_t *v17;

  v7 = (TableNums - 1) & (u32)~((TableNums - 1) >> 31);
  v8 = &pTable[1];
  v9 = -1;
  v10 = v7;
  while (v10)
  {
    Frame = (*(v8 - 1))->Frame;
    v13 = v8->Frame;
    ++v9;
    --v10;
    ++v8;
    if (Frame <= NowFrame && v13 > NowFrame)
      goto LABEL_13;
  }
  v9 = v7;
LABEL_13:
  m_Items = pTable;
  if (v9 + 1 >= SLODWORD(pTable->max_length))
    v15 = 1;
  else
    v15 = v9;
  v16 = m_Items[v15];
  v17 = m_Items[v15 + 1];
  return ((v17->Alpha - v16->Alpha) * (NowFrame - v16->Frame) / (v17->Frame - v16->Frame) + v16->Alpha) << 8 >> 7;
}

// 0x2229a50
void TitleInitCursor(titleCursor_t *pCursor) {
  *(u64 *)&pCursor->ScaleTimer = 6;
}

// 0x222f9a0
void TitleConfigSub(titleCursor_t *pCursor, s32 Mode) {
  if (Mode == 1)
    pCursor->Index = 2;
  pCursor->ScaleTimer = 6;
}

// 0x2224020
s32 TitleCalcCursor(dds3ProcessID_t *PID, titleCursor_t *pCursor, CURSOR_MODE _step) {
  s32 *ProcessData;
  s32 v10;
  s32 v11;
  s32 v12;
  s32 LevelIndex;
  s32 v14;
  void *v16;
  s32 v17;
  s32 Index;
  void *Instance;
  void *v20;
  u32 v21;
  s32 *ItemAlpha;
  il2cpp_array_size_t max_length;
  void *v24;
  s32 v25;
  void *v26;
  s32 v27;
  s32 *m_Items;
  s64 v29;
  s32 *v30;
  s32 *v31;
  s64 v32;
  s32 v33;
  s32 v34;
  s32 ScaleTimer;
  bool v36;
  s32 v37;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (GBWK->GameFileInfo->newfile)
    v10 = 4;
  else
    v10 = 3;
  if (step == 2)
    v11 = 2;
  else
    v11 = v10;
  if (!step)
  {
    if (!CHECK_REP(4100, 1))
    {
      v17 = 0;
      if (!CHECK_REP(4101, 1))
        goto LABEL_38;
LABEL_31:
      Index = pCursor->Index;
      if (Index != 3 || !pCursor->LastPush)
      {
        pCursor->Timer = 0;
        pCursor->ScaleTimer = 6;
        pCursor->Index = Index + 1;
        SE(5242881);
        if (pCursor->Index >= 4)
          pCursor->Index = ProcessData[33];
      }
      Instance = get_Instance(0);
      TitleChangeCursor(Instance, pCursor->Index, 0);
      v17 = 1;
LABEL_38:
      if (CHECK_PRESS(4100, 1))
      {
        pCursor->LastPush = 1;
        if (!CHECK_REP(4097, 1))
          goto LABEL_45;
      }
      else
      {
        pCursor->LastPush = CHECK_PRESS(4101, 1);
        if (!CHECK_REP(4097, 1))
          goto LABEL_45;
      }
      v20 = get_Instance(0);
      TitleChangeCursor(v20, pCursor->Index, 0);
LABEL_45:
      v21 = pCursor->Index;
      ItemAlpha = pCursor->ItemAlpha;
      max_length = ItemAlpha->max_length;
      if ((s32)max_length < 1)
        goto LABEL_75;
      goto LABEL_64;
    }
    v14 = pCursor->Index;
    if (v14 == ProcessData[33] && pCursor->LastPush || (pCursor->Timer = 0, pCursor->ScaleTimer = 6, pCursor->Index = v14 - 1, SE(5242881), pCursor->Index - ProcessData[33] >= 0))
    {
      goto LABEL_26;
    }
    else
    {
      pCursor->Index = 3;
      goto LABEL_26;
    }
LABEL_26:
    v16 = get_Instance(0);
    TitleChangeCursor(v16, pCursor->Index, 0);
    v17 = 1;
    if (!CHECK_REP(4101, 1))
      goto LABEL_38;
    goto LABEL_31;
  }
  v12 = step == 2;
  if (!CHECK_REP(4100, 1))
  {
    v17 = 0;
    if (!CHECK_REP(4101, 1))
      goto LABEL_61;
    goto LABEL_54;
  }
  LevelIndex = pCursor->LevelIndex;
  if (LevelIndex || !pCursor->LastPush)
  {
    pCursor->Timer = 0;
    pCursor->ScaleTimer = 6;
    pCursor->LevelIndex = LevelIndex - 1;
    SE(5242881);
    if (pCursor->LevelIndex < 0)
      pCursor->LevelIndex = v11;
  }
  v24 = get_Instance(0);
  LevelSelectCursor(v24, pCursor->LevelIndex, v12, 0);
  v17 = 1;
  if (CHECK_REP(4101, 1))
  {
LABEL_54:
    v25 = pCursor->LevelIndex;
    if (v25 != v11 || !pCursor->LastPush)
    {
      pCursor->Timer = 0;
      pCursor->ScaleTimer = 6;
      pCursor->LevelIndex = v25 + 1;
      SE(5242881);
      if (pCursor->LevelIndex > v11)
        pCursor->LevelIndex = 0;
    }
    v26 = get_Instance(0);
    LevelSelectCursor(v26, pCursor->LevelIndex, v12, 0);
    v17 = 1;
  }
LABEL_61:
  v27 = 1;
  if (!CHECK_PRESS(4100, 1))
    v27 = CHECK_PRESS(4101, 1);
  pCursor->LastPush = v27;
  CHECK_REP(4097, 1);
  v21 = pCursor->LevelIndex + pCursor->Index;
  ItemAlpha = pCursor->ItemAlpha;
  max_length = ItemAlpha->max_length;
  if ((s32)max_length >= 1)
  {
LABEL_64:
    m_Items = ItemAlpha;
    v29 = v21;
    v30 = &m_Items[v21];
    max_length = (u32)max_length;
    v31 = m_Items;
    v32 = v29;
    do
    {
      if (v32)
      {
        v33 = *v31;
        if (*v31 >= 1)
        {
          v33 -= 32;
          *v31 = v33;
        }
        if (v33 < 0)
          *v31 = 0;
      }
      else
      {
        v34 = *v30;
        if (*v30 < 128)
        {
          v34 += 32;
          m_Items[v29] = v34;
        }
        if (v34 > 128)
          *v30 = 128;
      }
      --v32;
      ++v31;
      --max_length;
    }
    while (max_length);
  }
LABEL_75:
  ScaleTimer = pCursor->ScaleTimer;
  v36 = __OFSUB__(ScaleTimer, 1);
  v37 = ScaleTimer - 1;
  if (v37 < 0 == v36)
    pCursor->ScaleTimer = v37;
  return v17;
}

// 0x2229a60
s32 TitleMovieStop(titleData_t *pData) {
  s32 Flag;

  Flag = pData->Flag;
  if ((Flag & 0x60) == 0x20)
  {
    pData->Flag = Flag | 0x40;
    return 0;
  }
  else
  {
    pData->MovieCounter = 0;
    pData->Flag = Flag & 0xFFFFFF9F;
    return 1;
  }
}

// 0x222bdc0
s32 TitleMoviePlay(s32 MovieNo, s32 Length, s32 FadeFrame, s32 Mode, titleData_t *pData) {
  s32 Flag;
  s32 MoviePlayWait;
  s32 MovieCounter;
  s32 result;
  s32 v14;
  s32 MovieAlpha;
  s32 *p_MovieAlpha;
  s32 v18;
  s32 v19;
  s32 v20;
  s32 v21;

  Flag = pData->Flag;
  if ((Flag & 0x20) == 0)
  {
    MoviePlayWait = pData->MoviePlayWait;
    pData->MoviePlayWait = MoviePlayWait + 1;
    if (MoviePlayWait >= 2)
    {
      MovieCounter = pData->MovieCounter;
      pData->MoviePlayWait = 0;
      pData->Flag = Flag | 0x20;
      pData->MovieCounter = 0;
      pData->MovieAlpha = (MovieCounter == 0) << 7;
    }
    return 0;
  }
  if (Length < 1)
  {
LABEL_19:
    goto LABEL_20;
  }
  v14 = pData->MovieCounter;
  if (v14 >= Length - FadeFrame && pData->MovieAlpha >= 1)
    pData->MovieAlpha = ((Length - v14) << 7) / FadeFrame;
  MovieAlpha = pData->MovieAlpha;
  if (v14 <= FadeFrame)
  {
    if (MovieAlpha >= 128)
    {
      p_MovieAlpha = &pData->MovieAlpha;
      goto LABEL_17;
    }
    MovieAlpha = (v14 << 7) / FadeFrame;
    pData->MovieAlpha = MovieAlpha;
  }
  p_MovieAlpha = &pData->MovieAlpha;
  if ((MovieAlpha & 0x80000000) == 0)
  {
LABEL_17:
    if ((u32)MovieAlpha >= 0x81)
      *p_MovieAlpha = 128;
    goto LABEL_19;
  }
  *p_MovieAlpha = 0;
LABEL_20:
  if ((Flag & 0x60) == 0x20)
  {
    v18 = Flag | 0x40;
    pData->Flag = v18;
    if ((v18 & 0x40) != 0)
      goto LABEL_22;
    goto LABEL_28;
  }
  v18 = Flag & 0xFFFFFF9F;
  pData->MovieCounter = 0;
  pData->Flag = v18;
  if ((v18 & 0x40) != 0)
  {
LABEL_22:
    if ((v18 & 0x60) == 0x20)
    {
      v19 = v18 | 0x40;
LABEL_37:
      pData->Flag = v19;
      return 2;
    }
    v19 = v18 & 0xFFFFFF9F;
    pData->MovieCounter = 0;
    goto LABEL_37;
  }
LABEL_28:
  v20 = pData->MovieCounter;
  if (Mode)
    v21 = 2;
  else
    v21 = 3;
  if (v20)
    result = v21;
  else
    result = 1;
  pData->MovieCounter = v20 + 1;
  return result;
}

// 0x2223a60
s32 TitleAt3Load(titleData_t *pData, TITLEenum bgmId) {
  if ((pData->Flag & 4) != 0)
  {
    goto LABEL_4;
  }
  sndBgmLoadId_XF(bgmId);
  pData->Flag |= 4u;
LABEL_4:
  if (sndBgmStatus_XF() == 2)
  {
    pData->Flag |= 8u;
    return 1;
  }
  return 0;
}

// 0x2223b50
void TitleAt3Play(titleData_t *pData) {
  if ((byte_5759155 & 1) != 0)
  {
    if ((pData->Flag & 0x18) != 8)
      return;
  }
  else
  {
    if ((pData->Flag & 0x18) != 8)
      return;
  }
  sndBgmPlay(0, 0);
  pData->Flag |= 0x10u;
}

// 0x222e740
void TitleAt3PlayLoop(titleData_t *pData) {
  if ((byte_5759156 & 1) != 0)
  {
    if ((pData->Flag & 0x18) != 8)
      return;
  }
  else
  {
    if ((pData->Flag & 0x18) != 8)
      return;
  }
  sndBgmPlayLoop(0);
  pData->Flag |= 0x10u;
}

// 0x222f9c0
void TitleCreditsAt3Stop(titleData_t *pData) {
  s32 Flag;

  Flag = pData->Flag;
  if ((Flag & 8) == 0)
  {
    pData->Flag = Flag & 0xFFFFFFE3;
    return;
  }
  sndBgmStop();
  sndBgmFree();
  pData->Flag &= 0xFFFFFFE3;
}

// 0x22239c0
void TitleAt3Stop(titleData_t *pData) {
  s32 Flag;

  Flag = pData->Flag;
  if ((Flag & 8) == 0)
  {
    pData->Flag = Flag & 0xFFFFFFE3;
    return;
  }
  sndBgmStop();
  sndBgmFree();
  pData->Flag &= 0xFFFFFFE3;
}

// 0x2227c10
void TitlePlayMovieSe(void) {
  goto LABEL_5;
LABEL_13:
  if (procStat != 3)
    return;
  if (movieOldFrame <= movieNowFrame)
    return;
  goto LABEL_25;
LABEL_5:
  if (procStat != 1)
    goto LABEL_13;
  if (p2sdIsBeforePlayback(62))
    return;
LABEL_25:
  SE(62);
  return;
}

// 0x2229aa0
void TitleStopMovieSe(void) {
  *(u64 *)&movieOldFrame = 0;
  movieNowFrame = 0;
  p2sdSndStop(62);
}

// 0x22278f0
static void JugeMovieFrameUpdate(void) {
  s32 Frame;
  s32 FrameCount;

  if (procStat != 3)
    return;
  movieOldFrame = movieNowFrame;
  Frame = movieGetFrame();
  movieNowFrame = Frame
                                                           - movieFrameOverCount
                                                           * movieGetFrameCount();
  if (movieGetFrameCount() <= movieNowFrame)
  {
    DispSubTitle(-1, 0);
    FrameCount = movieGetFrameCount();
    movieNowFrame = movieNowFrame - FrameCount;
    ++movieFrameOverCount;
  }
}

// 0x2228aa0
static void DispSubTitle(s32 frame, bool active) {
  s32 FrameCount;
  void *Instance;
  void *v7;
  void *dissolveMat;
  void *v11;
  f32 v12;
  void *subTitleImage;
  void *v17;
  void *v18;
  void *v19;
  void *v20;
  void *v23;
  void *v24;
  void *v25;
  void *v26;
  f32 v28;
  s32 v29;
  s32 v30;
  void *v31;
  void *v32;
  u32 v35;
  void *v36;

  if (frame == -1)
  {
    Instance = get_Instance(0);
    v7 = (Instance->subTitleImage->klass->vtable._32_get_material.methodPtr)(Instance->subTitleImage, Instance->subTitleImage->klass->vtable._32_get_material.method);
    dissolveMat = get_Instance(0)->dissolveMat;
    if (!op_Inequality(v7, dissolveMat, 0))
    {
      if (active)
        goto LABEL_12;
      goto LABEL_25;
    }
    subTitleImage = get_Instance(0)->subTitleImage;
    v17 = get_Instance(0);
    (subTitleImage->klass->vtable._33_set_material.methodPtr)(subTitleImage, v17->dissolveMat, subTitleImage->klass->vtable._33_set_material.method);
    if (active)
    {
LABEL_12:
      v11 = get_Instance(0);
      SubTitleCtr(v11, 1, 0);
      v12 = 1.0;
LABEL_29:
      titleDisolvePar = v12;
      v19 = get_Instance(0);
      v20 = (v19->subTitleImage->klass->vtable._32_get_material.methodPtr)(v19->subTitleImage, v19->subTitleImage->klass->vtable._32_get_material.method);
LABEL_33:
      SetFloat(v20, "_AlphaClipThreshold", titleDisolvePar, 0);
      return;
    }
LABEL_25:
    v18 = get_Instance(0);
    SubTitleCtr(v18, 0, 0);
    v12 = 0.0;
    goto LABEL_29;
  }
  FrameCount = movieGetFrameCount();
  if (frame < 0)
    return;
  if (FrameCount < frame)
    return;
  if (movieOldFrame <= frame)
  {
    if (movieNowFrame > frame)
      goto LABEL_47;
  }
  if (movieOldFrame <= movieNowFrame)
    return;
  if (movieOldFrame > frame)
    return;
LABEL_47:
  v23 = get_Instance(0);
  v24 = (v23->subTitleImage->klass->vtable._32_get_material.methodPtr)(v23->subTitleImage, v23->subTitleImage->klass->vtable._32_get_material.method);
  v25 = get_Instance(0)->dissolveMat;
  if (!op_Inequality(v24, v25, 0))
  {
    if (active)
      goto LABEL_52;
    goto LABEL_60;
  }
  v31 = get_Instance(0)->subTitleImage;
  v32 = get_Instance(0);
  (v31->klass->vtable._33_set_material.methodPtr)(v31, v32->dissolveMat, v31->klass->vtable._33_set_material.method);
  if (active)
  {
LABEL_52:
    v26 = get_Instance(0);
    SubTitleCtr(v26, 1, 0);
    v28 = 1.0;
    v29 = 0;
    v30 = 0;
LABEL_62:
    dissolveState = v30;
    titleDisolvePar = v28;
    if (!v35)
    v36 = get_Instance(0);
    v20 = (v36->subTitleImage->klass->vtable._32_get_material.methodPtr)(v36->subTitleImage, v36->subTitleImage->klass->vtable._32_get_material.method);
    goto LABEL_33;
  }
LABEL_60:
  v28 = 0.0;
  v29 = 1;
  v30 = 1;
  goto LABEL_62;
}

// 0x2228fa0
static void SubTitleDissolveCalc(void) {
  void *Instance;
  void *v3;
  void *dissolveMat;
  void *v6;
  void *v7;
  f32 v12;
  s32 v13;
  f32 v14;
  f32 v17;
  void *subTitleImage;
  void *v19;
  s32 playFrame;
  f32 v22;
  void *v23;
  void *v24;

  if (dissolveState == -1)
    return;
  Instance = get_Instance(0);
  v3 = (Instance->subTitleImage->klass->vtable._32_get_material.methodPtr)(Instance->subTitleImage, Instance->subTitleImage->klass->vtable._32_get_material.method);
  dissolveMat = get_Instance(0)->dissolveMat;
  if (!op_Inequality(v3, dissolveMat, 0))
  {
    goto LABEL_12;
  }
  subTitleImage = get_Instance(0)->subTitleImage;
  v19 = get_Instance(0);
  (subTitleImage->klass->vtable._33_set_material.methodPtr)(subTitleImage, v19->dissolveMat, subTitleImage->klass->vtable._33_set_material.method);
LABEL_12:
  v6 = get_Instance(0);
  v7 = (v6->subTitleImage->klass->vtable._32_get_material.methodPtr)(v6->subTitleImage, v6->subTitleImage->klass->vtable._32_get_material.method);
  if (!HasProperty_60811712(v7, "_AlphaClipThreshold", 0))
    return;
  if (!dissolveState)
  {
    playFrame = get_Instance(0)->playFrame;
    v22 = titleDisolvePar + (f32)(-1.0 / (f32)playFrame);
    titleDisolvePar = v22;
    if (v22 >= 0.0)
      goto LABEL_40;
    v14 = 0.0;
    goto LABEL_39;
  }
  if (dissolveState != 1)
    goto LABEL_40;
  v12 = titleDisolvePar;
  v13 = get_Instance(0)->playFrame;
  v14 = 1.0;
  v17 = v12 + (f32)(1.0 / (f32)v13);
  titleDisolvePar = v17;
  if (v17 <= 1.0)
    goto LABEL_40;
LABEL_39:
  titleDisolvePar = v14;
  dissolveState = -1;
LABEL_40:
  v23 = get_Instance(0);
  v24 = (v23->subTitleImage->klass->vtable._32_get_material.methodPtr)(v23->subTitleImage, v23->subTitleImage->klass->vtable._32_get_material.method);
  SetFloat(v24, "_AlphaClipThreshold", titleDisolvePar, 0);
}

// 0x2227460
void TitleGoMain(titleData_t *pData) {
  jmsSeqUnit_t *titleSeqUnit_local;

  scrSetMovieCancel(0);
  pData->WaitTimer = 60;
  titleSeqUnit_local = titleSeqUnit;
  jmsSeqJumpAndFree(&pData->pSeqUnit, &titleSeqUnit_local[5]);
}

// 0x2229ec0
void TitleDrawLogo(titleData_t *pData) {
  ;
}

// 0x2227ad0
static s32 PlayMainSubAt3(titleData_t *pData) {
  s32 result;

  result = TitleAt3Load(pData, 80);
  if (!result)
    return result;
  if ((pData->Flag & 0x18) != 8)
    return 1;
  sndBgmPlay(0, 0);
  pData->Flag |= 0x10u;
  return 1;
}

// 0x222d610
void TitleNewGameStart(s32 iMode) {
  SequenceParameter *v3;

  cfgCopyFlagGblToBak();
  datGlobalWorkUserInit2(GBWK->GameFileInfo->newfile);
  cfgCopyFlagBakToGbl();
  v3 = Allocate(SequenceParameter);
  _ctor(v3, 0);
  v3->CallData2 = 690;
  dds3AdminiCallSequence(9, v3, 0);
}

// 0x222fa60
titleData_t *TitleInit(s32 Mode) {
  titleData_t *v2;
  jmsSeqHandle_t *SeqHandle;

  v2 = (titleData_t *)Allocate(titleData_t);
  _ctor(v2);
  cfgCopyFlagGblToBak();
  SeqHandle = v2->SeqHandle;
  jmsInitSeqHandle(SeqHandle);
  v2->Flag |= 1u;
  return v2;
}

// 0x222fb50
void TitleDestroy(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void **p_monitor;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *monitor;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[3].monitor;
  p_monitor = &ProcessData[3].monitor;
  v6 = monitor;
  if (monitor)
    evtEnd(v6);
  *p_monitor = 0;
  *(u64 *)&movieOldFrame = 0;
  movieNowFrame = 0;
  p2sdSndStop(62);
  movieStop(0);
  fclFilterOFF();
  Delete(0);
}

// 0x222fdc0
void TitleProcessStart(s32 Mode) {
  dds3ProcessID_t *v2;
  titleData_t *v5;
  dds3ProcessFunc_t v6;
  dds3ProcessFunc_t v7;
  shutdownfuncDelegate v8;

  v2 = Allocate(dds3ProcessID_t);
  _ctor(v2, 0);
  minMapSceneClr();
  v5 = TitleInit((s32)TitleMain);
  v6 = Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_TitleMain_FirstCalcProcess__, 0);
  dds3StartProcess("title_calc", 1031, 0, 0, v6, 0, v5);
  v7 = Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_TitleMain_FirstDrawProcess__, 0);
  v8 = Allocate(shutdownfuncDelegate);
  _ctor(v8, 0, Method_Project_TitleMain_Destroy__, 0);
  dds3StartProcess("title_draw", 11031, 0, 0, v7, v8, v5);
  v5->Mode = Mode;
  sdfMemSetAllocated();
}

// 0x2230010
void TitleProcessEnd(void) {
  dds3KillProcessName("title_calc", 0);
  dds3KillProcessName("title_draw", 0);
  TitleUnloadTitleUi();
}

// 0x22300f0
bool TitleProcessCheck(void) {
  return dds3SearchProcessName("title_calc") != 0;
}
