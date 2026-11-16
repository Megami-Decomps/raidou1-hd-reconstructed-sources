#include "types.h"
#include "dds3kernelcore.h"
#include "kernel.h"
#include "meslogmain.h"

typedef struct MesLogData_t MesLogData_t;
typedef struct SCRLOG SCRLOG;
typedef struct dds3ProcessID_t dds3ProcessID_t;

dds3ProcessID_t *GlobalPID;
char *PROCESS_NAME;
bool is_field;

// 0x1d51ac0
dds3ProcessID_t *ProcessStart(void) {
  dds3ProcessID_t *v1;
  Il2CppObject *v2;
  dds3ProcessFunc_t v6;
  shutdownfuncDelegate v7;
  dds3ProcessID_t *started;

  v1 = Allocate(dds3ProcessID_t);
  _ctor(v1, 0);
  v2 = Allocate(MesLogData_t);
  _ctor(v2, 0);
  Init();
  v6 = Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_MesLogMain_Process__, 0);
  v7 = Allocate(shutdownfuncDelegate);
  _ctor(v7, 0, Method_Project_MesLogMain_Destroy__, 0);
  started = dds3StartProcess(PROCESS_NAME, 1032, 0, 0, v6, v7, v2);
  GlobalPID = started;
  return started;
}

// 0x1d51d50
dds3ProcessFunc_t Process(dds3ProcessID_t *_PID) {
  MesSkip *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  Update(ProcessData[2], MesLogData_t);
  return 0;
}

// 0x1d52040
void Destroy(dds3ProcessID_t *_PID) {
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
  ProcessData[1].klass = 0;
  GlobalPID = 0;
}

// 0x1d52170
bool ProcessCheck(void) {
  return dds3SearchProcessName(PROCESS_NAME) != 0;
}

// 0x1d52230
void ProcessEnd(void) {
  dds3KillProcessName(PROCESS_NAME, 1);
}

// 0x1d52300
void NewGameInit(void) {
  MesLogData_t *Wk;
  MesLog *mesLog;
  void *logList;
  s32 size;
  s32 v7;

  Wk = GetWk();
  if (!Wk)
    return;
  mesLog = Wk->mesLog;
  logList = mesLog->logList;
  size = logList->_size;
  v7 = logList->_version + 1;
  logList->_size = 0;
  logList->_version = v7;
  if (size >= 1)
    Clear(logList->_items, 0, size, 0);
}

// 0x1d52500
bool AddLog(char *_msg, char *_spk, char *_voice) {
  MesLogData_t *Wk;
  MesLog *mesLog;
  MesLogData_t *v12;
  s32 *enable_id;
  s64 v14;
  s64 v15;
  s32 v16;
  dds3ProcessID_t *v17;

  Wk = GetWk();
  if (!Wk)
    return 0;
  mesLog = Wk->mesLog;
  v12 = Wk;
  if (!mesLog->enable_cnt)
    return 0;
  enable_id = mesLog->enable_id;
  if (SLODWORD(enable_id->max_length) < 1)
    return AddLog(v12->mesLog, msg, spk);
  v14 = 8;
  do
  {
    v16 = *((u32 *)&enable_id->obj.klass + v14);
    if (!v16)
      goto LABEL_12;
    v17 = dds3SearchProcessID(v16);
    enable_id = mesLog->enable_id;
    if (v17)
      goto LABEL_12;
    *((u32 *)&enable_id->obj.klass + v14) = 0;
    mesLog->enable_cnt = (mesLog->enable_cnt - 1) & ~((mesLog->enable_cnt - 1) >> 31);
LABEL_12:
    v15 = v14 - 7;
    ++v14;
  }
  while (v15 < SLODWORD(enable_id->max_length));
  if (mesLog->enable_cnt)
    return AddLog(v12->mesLog, msg, spk);
  return 0;
}

// 0x1d52690
void *GetLog(MsgLogType _type) {
  MesLog *ProcessData;
  s64 naturalAligment;

  ProcessData = dds3GetProcessData(GlobalPID);
  if (ProcessData)
    LOBYTE(ProcessData[6].data) < (u32)naturalAligment || *((MesLogData_t **)(ProcessData)[4].monitor + naturalAligment - 1) != MesLogData_t;
  if (type == 2)
    return GetVoiceLogList(ProcessData[3], MesLogData_t);
  if (type == 1)
    return GetSpkLogList(ProcessData[3], MesLogData_t);
  if (type)
    return 0;
  return GetMesLogList(ProcessData[3], MesLogData_t);
}

// 0x1d52800
void SetLog(SCRLOG *_log) {
  MesLogData_t *Wk;

  Wk = GetWk();
  if (!Wk)
    return;
  goto LABEL_4;
  if (Wk)
LABEL_4:
    SetLog(Wk->mesLog);
}

// 0x1d52890
void LogStart(dds3ProcessID_t *pid) {
  MesLogData_t *Wk;
  MesLog *mesLog;
  s32 *enable_id;
  s32 id;
  s64 max_length;
  s32 *m_Items;
  s32 v11;

  Wk = GetWk();
  if (!Wk)
    return;
  mesLog = Wk->mesLog;
  if (mesLog->enable_cnt != 8)
  {
    enable_id = mesLog->enable_id;
    if (pid)
      goto LABEL_11;
LABEL_17:
    id = 0;
    goto LABEL_18;
  }
  enable_id = mesLog->enable_id;
  mesLog->enable_cnt = 0;
  if ((s32)enable_id->max_length >= 1)
    sub_188E3B0(enable_id, 0, 4 * (u32)enable_id->max_length);
  if (!pid)
    goto LABEL_17;
LABEL_11:
  id = pid->id;
  if ((s32)enable_id->max_length < 1)
  {
LABEL_18:
    enable_id[mesLog->enable_cnt++] = id;
    return;
  }
  max_length = (u32)enable_id->max_length;
  m_Items = enable_id;
  while (1)
  {
    v11 = *m_Items++;
    if (v11 == id)
      break;
    if (!--max_length)
      goto LABEL_18;
  }
}

// 0x1d529b0
s32 GetListCount(void) {
  MesLogData_t *Wk;
  MesLog *mesLog;

  Wk = GetWk();
  if (!Wk)
    return (s32)Wk;
  mesLog = Wk->mesLog;
  LODWORD(Wk) = mesLog->logList->_size;
  return (s32)Wk;
}

// 0x1d52a60
bool GetNoSkipEnd(void) {
  MesLogData_t *Wk;

  Wk = GetWk();
  if (Wk)
    LOBYTE(Wk) = Wk->mesSkip->noSkipEnd;
  return (char)Wk;
}

// 0x1d52ae0
void SetNoSkipEnd(bool _active) {
  MesLogData_t *Wk;

  Wk = GetWk();
  if (!Wk)
    return;
  Wk->mesSkip->noSkipEnd = active;
}

// 0x1d52b70
void RestartReset(void) {
  MesLogData_t *Wk;

  Wk = GetWk();
  if (!Wk)
    return;
  Wk->mesSkip->restart = 0;
}

// 0x1d523d0
MesLogData_t *GetWk(void) {
  MesLogData_t *result;

  if (!GlobalPID)
    return 0;
  result = (MesLogData_t *)dds3GetProcessData(GlobalPID);
  if (!result)
    return result;
  return result;
}
