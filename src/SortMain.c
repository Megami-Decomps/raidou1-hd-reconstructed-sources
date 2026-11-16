#include "types.h"
#include "dds3kernelcore.h"
#include "kernel.h"
#include "sortmain.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

dds3ProcessID_t *GlobalPID;
char *PROCESS_NAME;

// 0x21e1150
dds3ProcessID_t *ProcessStart(void) {
  dds3ProcessID_t *v1;
  Il2CppObject *v2;
  dds3ProcessFunc_t v5;
  shutdownfuncDelegate v6;
  dds3ProcessID_t *started;
  void *Instance;

  v1 = Allocate(dds3ProcessID_t);
  _ctor(v1, 0);
  v2 = Allocate(Project_SortMain_MainSort_t);
  _ctor(v2, 0);
  v5 = Allocate(dds3ProcessFunc_t);
  _ctor(v5, 0, Method_Project_SortMain_Process__, 0);
  v6 = Allocate(shutdownfuncDelegate);
  _ctor(v6, 0, Method_Project_SortMain_Destroy__, 0);
  started = dds3StartProcess(PROCESS_NAME, 11011, 0, 0, v5, v6, v2);
  GlobalPID = started;
  Instance = get_Instance(0);
  SortInit(Instance, 0);
  return started;
}

// 0x21e1350
dds3ProcessFunc_t Process(dds3ProcessID_t *_PID) {
  void *Instance;

  Instance = get_Instance(0);
  SortUpdate(Instance, 0);
  return 0;
}

// 0x21e13c0
void Destroy(dds3ProcessID_t *_PID) {
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  GlobalPID = 0;
}

// 0x21e14b0
bool LogProcessCheck(void) {
  return dds3SearchProcessName(PROCESS_NAME) != 0;
}

// 0x21e1570
void LogProcessEnd(void) {
  dds3KillProcessName(PROCESS_NAME, 1);
}
