#include "types.h"
#include "cfg.h"
#include "configaudio.h"
#include "dds3kernelcore.h"
#include "kernel.h"
#include "sdfsound.h"
#include "smg_file.h"
#include "sndat3.h"
#include "sndmanager.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

static dds3ProcessID_t *sndManagerProcess_id;
static char *voie_fname;
s32 PublicPan;
s32 PublicSE;
static bool sndInitFlag;
static s16 sndNowBgmNum;
static s32 *sndCommonSMG;

static dds3ProcessFunc_t Process(dds3ProcessID_t *id);
static void Shutdown(dds3ProcessID_t *id);
static void ProcessInit(void);

// 0x21eddc0
static dds3ProcessFunc_t Process(dds3ProcessID_t *id) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
  ++HIDWORD(ProcessData[1].klass);
  return 0;
}

// 0x21edea0
static void Shutdown(dds3ProcessID_t *id) {
  dds3ProcessID_t *ida;

  ida = id;
  dds3GetProcessData(ida);
  sndManagerProcess_id = 0;
}

// 0x21edf90
static void ProcessInit(void) {
  void *v1;
  dds3ProcessFunc_t v2;
  shutdownfuncDelegate v3;
  dds3ProcessID_t *started;

  v1 = Allocate(sndManagerProcessData_t);
  v2 = Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_sndManager_Process__, 0);
  v3 = Allocate(shutdownfuncDelegate);
  _ctor(v3, 0, Method_Project_sndManager_Shutdown__, 0);
  started = dds3StartProcess("sndman", 21010, 1, 1, v2, v3, 0);
  sndManagerProcess_id = started;
  dds3SetProcessData(sndManagerProcess_id, v1);
  *(u64 *)&v1->voice_sel = 0;
}

// 0x21ee140
void sndInit(void) {
  s64 v3;
  s32 v8;

  if (sndInitFlag)
  {
    p2sdSndStopAll();
    return;
  }
  v3 = 0;
  sndInitFlag = 1;
  while (1)
  {
    if (v3 >= SLODWORD(sndCommonSMG->max_length))
      break;
    v8 = sndCommonSMG[v3];
    p2sdLoadSMGFile(v8);
    ++v3;
  }
  sndNowBgmNum = -1;
  Init();
}

// 0x21ee320
bool sndIsCommonSMG(s32 smg_no) {
  s64 v4;
  u32 v5;
  s32 v6;
  s64 v7;
  s64 max_length_low;

  v4 = 0;
  v5 = smg_no & 0xFFFF0000;
  do
  {
    v7 = v4;
    max_length_low = SLODWORD(sndCommonSMG->max_length);
    if (v7 >= max_length_low)
      break;
    v6 = sndCommonSMG[v7];
    v4 = v7 + 1;
  }
  while (v6 != v5);
  return v7 < max_length_low;
}

// 0x21ee3e0
s32 sndGetNumOfReq(void) {
  return TIMES;
}

// 0x21ee460
bool sndVoicePlayFile(char *pName, void *source) {
  f32 Volume;
  void *Instance;

  Volume = GetVolume(1.0, 5);
  if (!cfgGetConfigAUDIO(6, 0))
    goto LABEL_8;
  goto LABEL_7;
  if (cfgGetConfigAUDIO(6, 0))
LABEL_7:
    pName = Concat_54766928(pName, "_e", 0);
LABEL_8:
  if (!cfgGetConfigAUDIO(4, 0))
    Volume = 0.0;
  Instance = get_Instance(0);
  return PlayVoice(Instance, pName, Volume, source, 0);
}

// 0x21ee5a0
bool sndIsVoicePlayFile(char *pName) {
  void *Instance;

  if (IsNullOrEmpty(pName, 0))
    return 0;
  Instance = get_Instance(0);
  return IsVoiceFile(Instance, pName, 0);
}

// 0x21ee5f0
void sndVoiceSel(s32 sel) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(sndManagerProcess_id);
  if (!ProcessData)
  LODWORD(ProcessData[1].klass) = sel;
}

// 0x21ee710
void sndVoicePlayId(s32 id) {
  u16 *v2;
  Il2CppObject *ProcessData;

  v2 = NewSpecific(char, 0x10u);
  CreateString_54864672(0, v2, 0);
  ProcessData = dds3GetProcessData(sndManagerProcess_id);
  if (!ProcessData)
  HIDWORD(ProcessData[1].klass) = 0;
}

// 0x21ee840
void sndVoiceGetFileName(s32 id, s32 idx, char **ptr) {
  ;
}

// 0x21ee850
s32 sndVoiceGetFileChk(s32 id, s32 idx) {
  u16 *v3;

  v3 = NewSpecific(char, 0x20u);
  CreateString_54864672(0, v3, 0);
  return 0;
}

// 0x21ee8b0
void sndVoiceStop(void *source) {
  void *Instance;

  Instance = get_Instance(0);
  PlayVoiceStop(Instance, source, 0);
}

// 0x21ee8e0
bool sndVoiceStatus(void *source) {
  void *Instance;

  Instance = get_Instance(0);
  return IsVoicePlay(Instance, source, 0);
}

// 0x21ee910
void sndVoicePause(void) {
  ;
}

// 0x21ee920
s32 sndVoiceGetTime(void) {
  s32 *ProcessData;

  ProcessData = dds3GetProcessData(sndManagerProcess_id);
  if (!ProcessData)
    return ProcessData[5];
  return ProcessData[5];
}
