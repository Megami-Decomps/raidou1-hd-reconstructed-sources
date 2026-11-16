#include "types.h"
#include "dds3adminiprocess.h"
#include "dds3kernelcore.h"
#include "dds3sequencelist.h"
#include "kernel.h"
#include "sbtlcontinue.h"

typedef struct SBTLMAIN_DATA SBTLMAIN_DATA;
typedef struct SceneParam_t SceneParam_t;
typedef struct SequenceParameter SequenceParameter;
typedef struct dds3AdminiData_t dds3AdminiData_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;

static dds3AdminiData_t *GetData(void);
static dds3ProcessFunc_t StartSequence(dds3ProcessID_t *id);
static dds3ProcessFunc_t EndCheck(dds3ProcessID_t *id);
static dds3ProcessFunc_t NeoProcess(dds3ProcessID_t *id);
static void NeoShutdown(dds3ProcessID_t *id);

// 0x2282d00
static dds3AdminiData_t *GetData(void) {
  dds3AdminiData_t *result;

  result = (dds3AdminiData_t *)dds3SearchProcessName("Admini")->workdata;
  if (!result)
    return result;
  return result;
}

// 0x2282f70
void dds3AdminiCallSequence2(DDS3_ADMINI_LIST sequence, s32 data, s32 datasize, bool restore) {
  SequenceParameter *v8;
  dds3AdminiData_t *v10;
  SequenceParameter *p_param;
  s32 v12;
  u32 v13;
  s32 v14;

  v8 = Allocate(SequenceParameter);
  _ctor(v8, 0);
  v8->CallData2 = data;
  if (sequence <= 43)
  {
    if (sequence == 19)
    {
      sBtlSave(v8, restore);
    }
    v10 = GetData();
    v10->param = v8;
    p_param = &v10->param;
    v12 = *((u32 *)p_param - 10);
    *((u32 *)p_param - 7) = sequence;
    v13 = v12 & 0xFFFEFFF2;
    *((u32 *)p_param + 2) = 2;
    if (restore)
      v14 = 5;
    else
      v14 = 1;
    *((u32 *)p_param - 10) = v13 | v14;
  }
}

// 0x2283160
void dds3AdminiCallSequence4(DDS3_ADMINI_LIST sequence, SceneParam_t *data, s32 datasize, bool restore) {
  SequenceParameter *v8;
  dds3AdminiData_t *v10;
  SequenceParameter *p_param;
  s32 v12;
  u32 v13;
  s32 v14;

  v8 = Allocate(SequenceParameter);
  _ctor(v8, 0);
  v8->CallData4 = data;
  if (sequence <= 43)
  {
    if (sequence == 19)
    {
      sBtlSave(v8, restore);
    }
    v10 = GetData();
    v10->param = v8;
    p_param = &v10->param;
    v12 = *((u32 *)p_param - 10);
    *((u32 *)p_param - 7) = sequence;
    v13 = v12 & 0xFFFEFFF2;
    *((u32 *)p_param + 2) = 2;
    if (restore)
      v14 = 5;
    else
      v14 = 1;
    *((u32 *)p_param - 10) = v13 | v14;
  }
}

// 0x2283290
void dds3AdminiCallSequence5(DDS3_ADMINI_LIST sequence, SBTLMAIN_DATA *data, s32 datasize, bool restore) {
  SequenceParameter *v8;
  dds3AdminiData_t *v10;
  SequenceParameter *p_param;
  s32 v12;
  u32 v13;
  s32 v14;

  v8 = Allocate(SequenceParameter);
  _ctor(v8, 0);
  v8->CallData5 = data;
  if (sequence <= 43)
  {
    if (sequence == 19)
    {
      sBtlSave(v8, restore);
    }
    v10 = GetData();
    v10->param = v8;
    p_param = &v10->param;
    v12 = *((u32 *)p_param - 10);
    *((u32 *)p_param - 7) = sequence;
    v13 = v12 & 0xFFFEFFF2;
    *((u32 *)p_param + 2) = 2;
    if (restore)
      v14 = 5;
    else
      v14 = 1;
    *((u32 *)p_param - 10) = v13 | v14;
  }
}

// 0x2283090
void dds3AdminiCallSequence(DDS3_ADMINI_LIST sequence, SequenceParameter *sequenceParameter, bool restore) {
  dds3AdminiData_t *Data;
  SequenceParameter *p_param;
  s32 v9;
  u32 v10;
  s32 v11;

  if (sequence <= 43)
  {
    if (sequence == 19)
    {
      sBtlSave(sequenceParameter, restore);
    }
    Data = GetData();
    Data->param = sequenceParameter;
    p_param = &Data->param;
    v9 = *((u32 *)p_param - 10);
    *((u32 *)p_param - 7) = sequence;
    v10 = v9 & 0xFFFEFFF2;
    *((u32 *)p_param + 2) = 2;
    if (restore)
      v11 = 5;
    else
      v11 = 1;
    *((u32 *)p_param - 10) = v10 | v11;
  }
}

// 0x22833c0
void dds3AdminiExitSequence(void) {
  dds3AdminiData_t *Data;

  Data = GetData();
  Data->Stat |= 2u;
}

// 0x22833e0
s32 dds3AdminiGetActiveSequence(void) {
  return GetData()->NowSequence;
}

// 0x2283400
s32 dds3AdminiGetNextSequence(void) {
  return GetData()->NextSequence;
}

// 0x2283420
s32 dds3AdminiGetPrevSequence(void) {
  dds3AdminiData_t *Data;
  s32 v2;
  bool v3;
  s32 v4;
  s32 v5;
  s32 v6;

  Data = GetData();
  v2 = Data->HistoryPointer + 7;
  v4 = -v2;
  v3 = -v2 < 0;
  v5 = v2 & 7;
  v6 = v4 & 7;
  if (!v3)
    v5 = -v6;
  return Data->SequenceHistory[v5];
}

// 0x2283460
s32 dds3AdminiGetPrevHistoryFlag(void) {
  dds3AdminiData_t *Data;
  s32 v2;
  bool v3;
  s32 v4;
  s32 v5;
  s32 v6;

  Data = GetData();
  v2 = Data->HistoryPointer + 7;
  v4 = -v2;
  v3 = -v2 < 0;
  v5 = v2 & 7;
  v6 = v4 & 7;
  if (!v3)
    v5 = -v6;
  return Data->FlagHistory[v5];
}

// 0x22834a0
static dds3ProcessFunc_t StartSequence(dds3ProcessID_t *id) {
  Il2CppObject *workdata;
  s32 klass;
  s32 monitor_high;
  s32 v8;
  bool v9;
  s32 v10;
  u32 v12;
  char *v13;
  u32 v14;
  s32 v15;
  bool v16;
  s32 v17;
  s32 v18;
  s32 v19;
  s32 v20;
  s32 v21;
  s32 v22;
  Il2CppClass *v23;
  void *start;
  dds3ProcessFunc_t v26;

  workdata = id->workdata;
  if (!workdata)
  klass = workdata[1].klass;
  if ((klass & 1) != 0)
  {
    monitor_high = HIDWORD(workdata[1].monitor);
    if ((monitor_high & 0x80000000) == 0)
    {
      v8 = workdata[4].klass;
      v9 = __OFSUB__(v8, 1);
      v10 = v8 - 1;
      if (v10 < 0 == v9)
      {
        LODWORD(workdata[4].klass) = v10;
        return 0;
      }
      LODWORD(workdata[1].monitor) = monitor_high;
      HIDWORD(workdata[1].monitor) = -1;
      v12 = klass & 0xFFFFFFFC;
      workdata[1].klass = (klass & 0xFFFFFFFC);
      if ((klass & 4) != 0)
      {
        v13 = (char *)workdata[3].klass + SLODWORD(workdata[2].klass);
        v13[32] |= 1u;
        v12 = (s64)workdata[1].klass & 0xFFFFFFFB;
        LODWORD(workdata[1].klass) = v12;
      }
      if ((v12 & 0x10000) != 0)
      {
        v20 = workdata[2].klass;
        v14 = 1;
        LODWORD(workdata[1].klass) = v12 & 0xFFFEFFFF;
        v20 += 7;
        v21 = -v20;
        v16 = -v20 < 0;
        v18 = v20 & 7;
        v22 = v21 & 7;
        if (!v16)
          v18 = -v22;
        LODWORD(workdata[2].klass) = v18;
      }
      else
      {
        v14 = 0;
        if ((v12 & 8) != 0)
        {
          LODWORD(workdata[1].klass) = v12 & 0xFFFFFFF7;
          v18 = workdata[2].klass;
        }
        else
        {
          v15 = LODWORD(workdata[2].klass) + 1;
          v17 = -v15;
          v16 = -v15 < 0;
          v18 = v15 & 7;
          v19 = v17 & 7;
          if (!v16)
            v18 = -v19;
          LODWORD(workdata[2].klass) = v18;
        }
      }
      v23 = workdata[3].klass;
      *((u32 *)workdata[2].monitor + v18 + 8) = workdata[1].monitor;
      *((u8 *)&v23->_1.byval_arg.data + SLODWORD(workdata[2].klass)) = 0;
      start = AdminiList[SLODWORD(workdata[1].monitor)]->start;
      if (start)
      {
        start = AdminiList[SLODWORD(workdata[1].monitor)]->start;
        (start->invoke_impl)(start->method_code, v14, workdata[3].monitor, start->method);
      }
    }
  }
  v26 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v26, 0);
  return v26;
}

// 0x2283850
static dds3ProcessFunc_t EndCheck(dds3ProcessID_t *id) {
  Il2CppObject *workdata;
  s32 monitor;
  void *end;
  s32 v9;
  dds3ProcessFunc_t v10;

  workdata = id->workdata;
  if (!workdata)
    goto LABEL_9;
  goto LABEL_7;
  if (!workdata)
LABEL_7:
LABEL_9:
  monitor = workdata[1].monitor;
  if (monitor < 0)
    goto LABEL_17;
  end = AdminiList[SLODWORD(workdata[1].monitor)]->end;
  if (end)
    goto LABEL_14;
LABEL_17:
  v10 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v10, 0);
  return v10;
LABEL_14:
  v9 = (end->invoke_impl)(end->method_code, end->method);
  if ((v9 & 0x80000000) == 0)
  {
    LODWORD(workdata[4].klass) = v9 + 1;
    LODWORD(workdata[1].monitor) = -1;
    goto LABEL_17;
  }
  return 0;
}

// 0x2283a40
static dds3ProcessFunc_t NeoProcess(dds3ProcessID_t *id) {
  s64 v3;
  Il2CppObject *workdata;
  s32 klass;
  s32 monitor;
  void *check;
  s32 v9;
  void *v10;
  s32 v11;
  bool v12;
  s32 v13;
  s32 v14;
  s32 v15;
  s32 v16;
  s64 v17;
  s32 *v18;
  s32 v19;
  s32 v20;
  s32 v21;
  dds3AdminiData_t *Data;
  s32 HistoryPointer;
  dds3ProcessFunc_t v24;

  workdata = id->workdata;
  if (!workdata)
    goto LABEL_9;
  goto LABEL_7;
  if (!workdata)
LABEL_7:
LABEL_9:
  klass = workdata[1].klass;
  if ((klass & 2) != 0)
    goto LABEL_22;
  monitor = workdata[1].monitor;
  if (monitor < 0)
    goto LABEL_34;
  check = AdminiList[SLODWORD(workdata[1].monitor)]->check;
  if (!check)
  {
    klass = workdata[1].klass;
    ++HIDWORD(workdata[1].klass);
    if ((klass & 2) == 0)
      goto LABEL_34;
    goto LABEL_22;
  }
  if (*(u32 *)(v3 + 224))
  {
    v3 = (check->invoke_impl)(check->method_code, check->method);
    klass = workdata[1].klass;
    if ((v3 & 1) != 0)
      goto LABEL_15;
  }
  else
  {
    v10 = AdminiList[SLODWORD(workdata[1].monitor)]->check;
    v3 = (v10->invoke_impl)(v10->method_code, v10->method);
    klass = workdata[1].klass;
    if ((v3 & 1) != 0)
    {
LABEL_15:
      klass |= 2u;
      v9 = HIDWORD(workdata[1].klass) + 1;
      LODWORD(workdata[1].klass) = klass;
      HIDWORD(workdata[1].klass) = v9;
      if ((klass & 2) == 0)
        goto LABEL_34;
      goto LABEL_22;
    }
  }
  ++HIDWORD(workdata[1].klass);
  if ((klass & 2) == 0)
    goto LABEL_34;
LABEL_22:
  if (((s64)workdata[1].monitor & 0x80000000) == 0)
  {
    v11 = LODWORD(workdata[2].klass) + 7;
    v13 = -v11;
    v12 = -v11 < 0;
    v14 = v11 & 7;
    v15 = v13 & 7;
    if (v12)
      v16 = v14;
    else
      v16 = -v15;
    v17 = (s64)workdata[2].monitor + 4 * v16;
    v19 = *(u32 *)(v17 + 32);
    v18 = (v17 + 32);
    if ((v19 & 0x80000000) == 0 && (*((u8 *)&workdata[3].klass->_1.byval_arg.data + v16) & 1) != 0)
    {
      v20 = klass | 0x10001;
      workdata[3].monitor = 0;
      LODWORD(workdata[1].klass) = v20;
      v21 = *v18;
      LODWORD(workdata[1].klass) = v20 & 0xFFFFFFFB;
      HIDWORD(workdata[1].monitor) = v21;
      LODWORD(workdata[4].klass) = 2;
      klass = workdata[1].klass;
    }
    if ((klass & 1) == 0)
    {
      Data = GetData();
      Data->param = 0;
      Data = ((char *)Data + 56);
      HistoryPointer = Data[-1].HistoryPointer;
      HIDWORD(Data[-1].SequenceHistory) = 0;
      LODWORD(Data->monitor) = 2;
      Data[-1].HistoryPointer = HistoryPointer & 0xFFFEFFF2 | 1;
      klass = workdata[1].klass;
    }
    klass &= ~2u;
    LODWORD(workdata[1].klass) = klass;
  }
LABEL_34:
  if ((klass & 1) == 0 || (HIDWORD(workdata[1].monitor) & 0x80000000) != 0)
    return 0;
  v24 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v24, 0);
  return v24;
}

// 0x2283d50
static void NeoShutdown(dds3ProcessID_t *id) {
  Il2CppObject *workdata;
  s32 monitor;
  void *end;

  workdata = id->workdata;
  if (!workdata)
    goto LABEL_9;
  goto LABEL_7;
  if (!workdata)
LABEL_7:
LABEL_9:
  monitor = workdata[1].monitor;
  if (monitor < 0)
    return;
  end = AdminiList[monitor]->end;
  if (!end)
    return;
  end = AdminiList[SLODWORD(workdata[1].monitor)]->end;
  (end->invoke_impl)(end->method_code, end->method);
}

// 0x2283ec0
void dds3InitAdmini(void) {
  dds3AdminiData_t *v4;
  s64 v6;
  s64 v7;
  s64 v8;
  s64 v9;
  s64 v10;
  s64 v11;
  s64 v12;
  s64 v13;
  s64 v14;
  dds3ProcessFunc_t v15;
  shutdownfuncDelegate v17;

  if (dds3SearchProcessName("Admini"))
    return;
  v4 = Allocate(dds3AdminiData_t);
  _ctor(v4);
  v4->HistoryPointer = 0;
  v6 = v4->SequenceHistory;
  v7 = v4->FlagHistory;
  *(_OWORD *)&v4->Stat = xmmword_3CF99C0;
  *(u32 *)(v6 + 32) = -1;
  *(u8 *)(v7 + 32) = 0;
  v8 = v4->FlagHistory;
  *(u32 *)((u64)v4->SequenceHistory + 36) = -1;
  *(u8 *)(v8 + 33) = 0;
  v9 = v4->FlagHistory;
  *(u32 *)((u64)v4->SequenceHistory + 40) = -1;
  *(u8 *)(v9 + 34) = 0;
  v10 = v4->FlagHistory;
  *(u32 *)((u64)v4->SequenceHistory + 44) = -1;
  *(u8 *)(v10 + 35) = 0;
  v11 = v4->FlagHistory;
  *(u32 *)((u64)v4->SequenceHistory + 48) = -1;
  *(u8 *)(v11 + 36) = 0;
  v12 = v4->FlagHistory;
  *(u32 *)((u64)v4->SequenceHistory + 52) = -1;
  *(u8 *)(v12 + 37) = 0;
  v13 = v4->FlagHistory;
  *(u32 *)((u64)v4->SequenceHistory + 56) = -1;
  *(u8 *)(v13 + 38) = 0;
  v14 = v4->FlagHistory;
  *(u32 *)((u64)v4->SequenceHistory + 60) = -1;
  *(u8 *)(v14 + 39) = 0;
  v4->param = 0;
  v15 = Allocate(dds3ProcessFunc_t);
  _ctor(v15, 0);
  v17 = Allocate(shutdownfuncDelegate);
  _ctor(v17, 0);
  dds3StartProcess("Admini", 2, 0, 1, v15, v17, v4);
}
