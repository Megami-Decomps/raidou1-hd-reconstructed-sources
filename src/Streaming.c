#include "types.h"
#include "dat.h"
#include "dds3kernelcore.h"
#include "evtbit.h"
#include "fclmisc.h"
#include "fclmsg.h"
#include "kernel.h"
#include "scr.h"
#include "slmain.h"
#include "streaming.h"

#define ProcessName "Streaming"
#define mesKey "fld_common"
#define mesfile "mc_sys.bmd"

typedef enum {
    State_None = 0,
    State_CallMes = 1,
    State_MesWait = 2,
    State_End = 3,
} State;

typedef struct GameFileInfo_t GameFileInfo_t;
typedef struct StreamingWk StreamingWk;
typedef struct dds3ProcessID_t dds3ProcessID_t;

struct StreamingWk {
    dds3ProcessID_t *MesPID;
    State state;
    bool installMes;
};

dds3ProcessID_t *MainPID;

static dds3ProcessFunc_t Process(dds3ProcessID_t *PID);

// macros
// 0x2251280: s32 INSTALL_UI(void)
static inline s32 INSTALL_UI(void) {
  bool v1;

  v1 = scrGetIntPara(0) != 0;
  InstallUi(v1);
  scrSetIntReturnValue(1);
  return 1;
}

// 0x2251310: s32 INSTALL_UI_GAME(void)
static inline s32 INSTALL_UI_GAME(void) {
  scrSetIntReturnValue(1);
  return 1;
}

// 0x2250780
static dds3ProcessFunc_t Process(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 *EventBit;
  s32 monitor;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (!GBWK || !GBWK->EventBit)
    return 0;
  if (evtBitCheck(693))
  {
    EventBit = GBWK->EventBit;
    EventBit[21] &= ~0x200000u;
    goto LABEL_17;
  }
LABEL_17:
  if (!ProcessData[1].klass)
    goto LABEL_26;
  if (fclChkMessageDisp())
    goto LABEL_26;
  v9 = fmProcessChk();
  if (!(u32)v9)
    End();
LABEL_26:
  monitor = ProcessData[1].monitor;
  if (monitor != 2)
  {
    if (monitor == 1)
      LODWORD(ProcessData[1].monitor) = 2;
    return 0;
  }
  if (fclUpdateEx(ProcessData[1].klass))
    return 0;
  LODWORD(ProcessData[1].monitor) = 0;
  InstallUi(0);
  return 0;
}

// 0x2250c10
void Init(void) {
  StreamingWk *v4;
  dds3ProcessFunc_t v6;
  dds3ProcessID_t *started;
  dds3ProcessID_t *v8;
  dds3ProcessID_t *v9;

  GBWK->EventBit[21] |= 0x200000u;
  v4 = Allocate(StreamingWk);
  v4->state = 0;
  v4->installMes = 0;
  v6 = Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_Streaming_Process__, 0);
  started = dds3StartProcess("Streaming", 1007, 0, 0, v6, 0, v4);
  MainPID = started;
  v8 = fclProcessStart();
  v4->MesPID = v8;
  v9 = &v4->MesPID;
  fclLoadDataEx(v9, "mc_sys.bmd", "fld_common", 1);
  Unload(Dependent, "fld_common");
}

// 0x22509e0
void End(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  dds3ProcessID_t *klass;

  ProcessData = dds3GetProcessData(MainPID);
  InstallUi(0);
  klass = ProcessData[1].klass;
  v4 = ProcessData + 1;
  fclResetEx(klass);
  fclProcessEnd(v4->klass);
  v4->klass = 0;
  LODWORD(v4->monitor) = 3;
}

// 0x22509d0
bool InstallCheck(void) {
  return 1;
}

// 0x2251230
bool SaveStremingCheck(GameFileInfo_t *_info) {
    return 0;
}

// 0x2250ae0
s32 InstallUi(bool _active) {
  Il2CppObject *ProcessData;
  bool v6;
  void *Instance;

  if (MainPID)
  {
    ProcessData = dds3GetProcessData(MainPID);
    if (!ProcessData)
      goto LABEL_10;
    goto LABEL_9000;
    if (!ProcessData)
    {
LABEL_10:
      v6 = active;
      BYTE4(ProcessData[1].monitor) = v6;
      Instance = get_Instance(0);
      InstallGaugeOnOff(Instance, v6, 0);
      return 1;
    }
LABEL_9000:
    goto LABEL_10;
  }
  return 1;
}

// 0x2251270
s32 InstallUiGame(void) {
  return 1;
}

// 0x2251370
void CallMes(void) {
  Il2CppObject *ProcessData;

  if (MainPID)
  {
    ProcessData = dds3GetProcessData(MainPID);
    if (!ProcessData)
      goto LABEL_10;
    goto LABEL_9000;
    if (!ProcessData)
    {
LABEL_10:
      InstallUi(1);
      fclResetEx(ProcessData[1].klass);
      fclStart(ProcessData[1].klass, 1, 23, 0);
      LODWORD(ProcessData[1].monitor) = 1;
      return;
    }
LABEL_9000:
    goto LABEL_10;
  }
}

// 0x2251490
bool MesCheck(void) {
  Il2CppObject *ProcessData;

  if (!MainPID)
    return 0;
  ProcessData = dds3GetProcessData(MainPID);
  if (!ProcessData)
    return LODWORD(ProcessData[1].monitor) != 0;
  return LODWORD(ProcessData[1].monitor) != 0;
}

// 0x2251590
bool MesEnd(void) {
  Il2CppObject *ProcessData;

  if (!MainPID)
    return 0;
  ProcessData = dds3GetProcessData(MainPID);
  if (!ProcessData)
    return BYTE4(ProcessData[1].monitor) != 0;
  return BYTE4(ProcessData[1].monitor) != 0;
}
