#include "types.h"
#include "achievement.h"
#include "aw.h"
#include "buttonguide.h"
#include "cfg.h"
#include "cmpitem.h"
#include "dat.h"
#include "dds3adminiprocess.h"
#include "dds3effect.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3kernelmain.h"
#include "dds3padmanager.h"
#include "dds3randomize.h"
#include "dds3vrf.h"
#include "dds3worldbasic.h"
#include "ditectivebook.h"
#include "effstat.h"
#include "evtcutin.h"
#include "evtmoon.h"
#include "file.h"
#include "fld.h"
#include "gohdevilres.h"
#include "itf.h"
#include "kernel.h"
#include "meslogmain.h"
#include "movie.h"
#include "nmeutil.h"
#include "sbtl.h"
#include "scr.h"
#include "sdfvsync.h"
#include "sndmanager.h"
#include "sortmain.h"
#include "streaming.h"

typedef struct FsSaveData FsSaveData;
typedef struct SequenceParameter SequenceParameter;

u32 FrameCount;
static u32 RunCount;
s32 FrameID;
static bool SoftResetFlag;
bool PauseSign;
static u32 PauseTime;
static s32 PauseCount;
static bool PauseSign_;
static bool PauseObject;
bool DebugSign;
static u16 SleepTime;
static bool FileLoadPrioMode;
FsSaveData *saveData;
static void *_MainThread_k__BackingField;
static void *pauseKey;

static void FirstInit(DDS3_ADMINI_LIST startSequence, SequenceParameter *sequenceParameter);
static bool IsUpdate(void);

// 0x22946d0
void dds3SetMainThred(void) {
  void *Current;

  Current = get_Current(0);
  _MainThread_k__BackingField = Current;
}

// 0x22947b0
static void FirstInit(DDS3_ADMINI_LIST startSequence, SequenceParameter *sequenceParameter) {
  dds3ProcessFunc_t v6;
  dds3ProcessFunc_t v7;
  dds3ProcessFunc_t v8;
  dds3ProcessFunc_t v11;
  dds3ProcessFunc_t v12;
  dds3ProcessFunc_t v13;
  shutdownfuncDelegate v14;
  dds3Basic_t *v17;
  dds3ProcessFunc_t v19;

  set_targetFrameRate(60, 0);
  dds3InitDrawEnv();
  dds3PadInitialize();
  v6 = Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_Kernel_dds3KernelProcess_FirstProcess__, 0);
  dds3StartProcess("1st", 0, 0, 0, v6, 0, 0);
  v7 = Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_Kernel_dds3KernelProcess_DrawFirstProcess__, 0);
  dds3StartProcess("draw1st", 10000, 0, 0, v7, 0, 0);
  v8 = Allocate(dds3ProcessFunc_t);
  _ctor(v8, 0, Method_Project_Kernel_dds3KernelProcess_DrawProcess__, 0);
  dds3StartProcess("RequestDraw", 20000, 0, 0, v8, 0, 0);
  dds3TheWorld = 0;
  v11 = Allocate(dds3ProcessFunc_t);
  _ctor(v11, 0, Method_Project_Kernel_dds3KernelProcess_BasicMainProcess__, 0);
  dds3StartProcess("basic_main", 1019, 1, 1, v11, 0, 0);
  v12 = Allocate(dds3ProcessFunc_t);
  _ctor(v12, 0, Method_Project_Kernel_dds3KernelProcess_BasicDrawProcess__, 0);
  dds3StartProcess("basic_draw", 11015, 1, 1, v12, 0, 0);
  frInitFontTable(256, 512);
  v13 = Allocate(dds3ProcessFunc_t);
  _ctor(v13, 0, Method_Project_itf_frFlipPacketBuf__, 0);
  v14 = Allocate(shutdownfuncDelegate);
  _ctor(v14, 0, Method_Project_itf_frDestroyFontTable__, 0);
  dds3StartProcess("font_sys", 19999, 0, 0, v13, v14, 0);
  fileSysInit();
  itfMesMngInitializeManager();
  sndInit();
  dds3EffectManagerInit();
  movieInitManager();
  SoftResetFlag = 0;
  FrameCount = 0;
  v17 = Add(10000, 0);
  dds3InitRandCB();
  dds3InitAdmini();
  dds3AdminiCallSequence(startSequence, sequenceParameter, 0);
  VRF = 0.0;
  *(u64 *)&VRF_DeltaTime = 0x3C88888900000000LL;
  VRF_Active = 0;
  dds3FadeClear();
  LoadOnMemoryData();
  datGlobalWorkInit();
  Init();
  cfgBtnTagConfigLoad();
  evtFirstInit();
  itfIconInit();
  evtMoonInitProcess();
  itfMoneyProcessStart();
  ProcessStart(0);
  encInitProcess();
  fldFirstInit();
  fldBgTaskInit();
  nmeInitialize();
  Init();
  cmpLoadScript();
  CreateInstance();
  ButtonGuideInit();
  v19 = Allocate(dds3ProcessFunc_t);
  _ctor(v19, 0, Method_Project_ButtonGuide_GuideMain__, 0);
  dds3StartProcess("ButtonGuide", 21011, 0, 0, v19, 0, 0);
  Receipt_ProcessStart();
  SetDisp(ctrl, 0, 0);
  FadeIn(ctrl, 0);
  scrLogInit();
  ProcessStart(0);
  Init();
  Initialize(0);
  Instance(0);
}

// 0x2295750
void dds3NewGameStart(void) {
  s32 newfile;
  SequenceParameter *v3;

  newfile = GBWK->GameFileInfo->newfile;
  datGlobalWorkUserInit2(newfile != 0);
  v3 = Allocate(SequenceParameter);
  v3->CallData2 = 690;
  dds3AdminiCallSequence(9, v3, 0);
}

// 0x2295820
u32 dds3GetKernelCount(void) {
  return FrameCount;
}

// 0x22958a0
s32 dds3GetFrameID(void) {
  return FrameID;
}

// 0x22959a0
void dds3PauseOn(u32 frame, char *id) {
  void *Instance;
  void *v7;
  void *pauseKey_local;
  u64 *v13;
  s64 size;
  void *items;
  Il2CppClass **v16;

  if (PauseCount)
  {
    if (!frame)
      goto LABEL_25;
LABEL_17:
    if (PauseTime)
    {
      --PauseCount;
    }
    if (PauseTime >= frame)
      goto LABEL_25;
    PauseTime = frame;
LABEL_26:
    ++PauseCount;
    if (!id)
      return;
    goto LABEL_34;
  }
  Instance = get_Instance(0);
  if (op_Inequality(Instance, 0, 0))
  {
    v7 = get_Instance(0);
    Pause(v7, 1, 0);
  }
  set_pause(1, 0);
  moviePause(1);
  PauseSign = 1;
  if (frame)
    goto LABEL_17;
LABEL_25:
  goto LABEL_26;
LABEL_34:
  if (_Contains(pauseKey, id))
  {
    return;
  }
  pauseKey_local = pauseKey;
  v13 = Method_System_Collections_Generic_List_string__Add__;
  size = pauseKey_local->_size;
  ++pauseKey_local->_version;
  items = pauseKey_local->_items;
  if ((u32)size >= LODWORD(items->max_length))
  {
    _AddWithResize(pauseKey_local, id, *(const MethodInfo_2DFC660 **)(*(u64 *)(v13[4] + 192) + 112));
  }
  else
  {
    v16 = &items->obj.klass + size;
    pauseKey_local->_size = size + 1;
    v16[4] = id;
  }
}

// 0x2295cb0
void dds3PauseOff(char *id) {
  s32 v6;
  s32 v8;
  void *Instance;
  void *v10;

  if (!PauseCount)
    return;
  v6 = PauseCount - 1;
  PauseCount = v6;
  if (v6)
    goto LABEL_9;
  goto LABEL_9000;
  if (v8)
  {
LABEL_9:
    if (!id)
      return;
    goto LABEL_22;
  }
LABEL_9000:
  Instance = get_Instance(0);
  if (op_Inequality(Instance, 0, 0))
  {
    v10 = get_Instance(0);
    Pause(v10, 0, 0);
  }
  set_pause(0, 0);
  moviePause(0);
  PauseSign = 0;
  PauseTime = 0;
  if (!id)
    return;
LABEL_22:
  if (_Contains(pauseKey, id))
  {
    _Remove(pauseKey, id);
  }
}

// 0x2295ec0
bool dds3IsPause(void) {
  return PauseSign;
}

// 0x2295f40
void dds3SoftResetOn(void) {
  ;
}

// 0x2295f50
void dds3SoftResetOff(void) {
  ;
}

// 0x2295f60
void KernelSetDebugSign(bool bFlag) {
  ;
}

// 0x2295f70
static bool IsUpdate(void) {
  bool update;

  if (!firstFrame)
  {
LABEL_13:
    goto LABEL_14;
  }
  if (PauseSign_ == PauseSign)
    goto LABEL_13;
  if (PauseSign)
  {
    update = Instance->update;
    PauseObject = update;
    ObjectContinue(Instance, 0);
    goto LABEL_32;
  }
  if (PauseObject)
  {
    ObjectUpdate(Instance, 0);
    PauseObject = 0;
  }
LABEL_32:
  PauseSign_ = PauseSign;
LABEL_14:
  if (PauseSign_)
  {
    set_timeScale(0.0, 0);
    return 0;
  }
  set_timeScale(timeScale, 0);
  return isUpdate;
}

// 0x22962f0
void *KernelMain(DDS3_ADMINI_LIST startSequence, SequenceParameter *sequenceParameter) {
  void *v5;

  v5 = Allocate(Project_Kernel_dds3KernelMain__KernelMain_d__33);
  v5->__1__state = 0;
  v5->sequenceParameter = sequenceParameter;
  v5->startSequence = startSequence;
  return v5;
}

// 0x2295180
void dds3UnityInit(void) {
  set_targetFrameRate(60, 0);
}
