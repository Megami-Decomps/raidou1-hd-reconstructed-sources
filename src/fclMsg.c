#include "types.h"
#include "dds3initialize.h"
#include "dds3kernelcore.h"
#include "fclmisc.h"
#include "fclmsg.h"
#include "itf.h"
#include "kernel.h"
#include "meslogmain.h"
#include "scr.h"

#define UNITY_MES_WAIT_FRAME 15

typedef struct dds3ProcessID_t dds3ProcessID_t;

dds3ProcessID_t *g_mainPID;
static bool direct_call_mes;

static void FreeData(void *wk);
static s32 _Update(void *wk, dds3ProcessID_t *PID);
static dds3ProcessFunc_t Process(dds3ProcessID_t *PID);
static void Release(void *wk);
static void Shutdown(dds3ProcessID_t *PID);

// 0x1b3a5a0
static void FreeData(void *wk) {
  wk->pDatMsg = 0;
}

// 0x1b3a5b0
void fclLoadDataEx(dds3ProcessID_t *PID, char *filename, char *assetName, bool assetUnload) {
  Il2CppObject *ProcessData;
  Il2CppObject *v11;
  char *v12;
  void *Asset;
  sdfBinary *v17;
  u8 *data;
  Il2CppObject *klass;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if ((BYTE4(ProcessData[1].monitor) & 3) != 0)
    return;
  ProcessData[1].klass = 0;
  v11 = ProcessData + 1;
  v12 = "";
  if (!op_Inequality(assetName, "", 0))
    assetName = v12;
  Load(Dependent, assetName, assetName);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Asset = LoadAsset(_Ctrl_k__BackingField, assetName, filename, 0);
  v17 = Allocate(sdfBinary);
  _ctor(v17, Asset, 0);
  data = v17->data;
  v11->klass = data;
  if (!dds3AlwaysAssetCheck(assetName) && assetUnload)
  {
    Unload(Dependent, assetName, 0);
  }
  klass = v11->klass;
  fclInitMessage(klass);
}

// 0x1b3a9f0
void fclLoadData(char *filename, char *assetName, bool assetUnload) {
  fclLoadDataEx(g_mainPID, filename, assetName, assetUnload);
}

// 0x1b3aa70
void fclLinkDataEx(dds3ProcessID_t *PID, u8 *a_pDatMsg) {
  Il2CppObject *ProcessData;
  Il2CppObject **v7;
  Il2CppObject *v9;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if ((BYTE4(ProcessData[1].monitor) & 3) == 0)
  {
    ProcessData[1].klass = 0;
    v7 = &ProcessData[1];
    *v7 = &a_pDatMsg->obj;
    v9 = *v7;
    fclInitMessage(*v7);
  }
}

// 0x1b3abe0
void fclLinkData(u8 *a_pDatMsg) {
  fclLinkDataEx(g_mainPID, a_pDatMsg);
}

// 0x1b3ac40
void fclResetEx(dds3ProcessID_t *PID) {
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
  if ((BYTE4(ProcessData[1].monitor) & 3) == 0)
  {
    fclDestroyMessage();
    fclInitMessage(ProcessData[1].klass);
  }
}

// 0x1b3aed0
bool fclStart(dds3ProcessID_t *PID, s32 a_type, s32 a_no, bool skip_enable) {
  Il2CppObject *ProcessData;
  s32 monitor_high;
  _BOOL4 v13;
  dds3ProcessID_t *v14;
  bool v15;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor_high = HIDWORD(ProcessData[1].monitor);
  v13 = (monitor_high & 3) == 0 && (a_no | a_type) >= 0;
  if (!v13)
    return v13;
  LOBYTE(ProcessData[2].klass) = a_type;
  WORD1(ProcessData[2].klass) = a_no;
  HIDWORD(ProcessData[1].monitor) = monitor_high | 4;
  if (skip_enable)
  {
    v14 = id;
    scrLogStart(v14);
    v15 = 1;
  }
  else
  {
    if ((u8)a_type == 2)
      goto LABEL_25;
    scrEventSkipEnd(0, 0);
    v15 = 0;
  }
  direct_call_mes = v15;
LABEL_25:
  if (LOBYTE(ProcessData[2].klass) != 2)
    return v13;
  if (BYTE4(ProcessData[3].monitor))
  {
    itfMesMngSetBitStatManager(1);
    return v13;
  }
  itfMesMngClearBitStatManager(1);
  return 1;
}

// 0x1b3b100
void fclSetSelInvild(dds3ProcessID_t *PID, bool _flag) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  if (PID)
  {
    ProcessData = dds3GetProcessData(id);
    if (!ProcessData)
      goto LABEL_10;
    goto LABEL_9000;
    if (!ProcessData)
    {
LABEL_10:
      BYTE4(ProcessData[3].klass) = flag;
      return;
    }
LABEL_9000:
    goto LABEL_10;
  }
}

// 0x1b3b1e0
void fclSelMesSpeedMax(dds3ProcessID_t *PID, bool _flag) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  if (PID)
  {
    ProcessData = dds3GetProcessData(id);
    if (!ProcessData)
      goto LABEL_10;
    goto LABEL_9000;
    if (!ProcessData)
    {
LABEL_10:
      BYTE4(ProcessData[3].monitor) = flag;
      return;
    }
LABEL_9000:
    goto LABEL_10;
  }
}

// 0x1b3b2c0
void fclSetSelMes(dds3ProcessID_t *PID, s32 _selMes) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  if (PID)
  {
    ProcessData = dds3GetProcessData(id);
    if (!ProcessData)
      goto LABEL_10;
    goto LABEL_9000;
    if (!ProcessData)
    {
LABEL_10:
      LODWORD(ProcessData[3].monitor) = selMes;
      return;
    }
LABEL_9000:
    goto LABEL_10;
  }
}

// 0x1b3b3a0
void fclSkipNoEnd(dds3ProcessID_t *PID, bool _flag) {
  SetNoSkipEnd(flag);
}

// 0x1b3b430
void fclGetLogStop(dds3ProcessID_t *PID, bool _flag) {
  ;
}

// 0x1b3b440
void fclDirectCallMesClear(void) {
  direct_call_mes = 0;
}

// 0x1b3b490
bool fclStart1(s32 a_no, bool skip_enable) {
  return fclStart(g_mainPID, 1, a_no, skip_enable);
}

// 0x1b3b500
bool fclStart2(s32 a_no, bool skip_enable, bool _invild) {
  fclSetMessageInvalid(!invild);
  fclSetSelInvild(g_mainPID, invild);
  return fclStart(g_mainPID, 2, a_no, skip_enable);
}

// 0x1b3b740
s32 fclGetSelect(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if ((BYTE4(ProcessData[1].monitor) & 3) != 0)
    return -1;
  else
    return (s32)ProcessData[2].monitor;
}

// 0x1b3b850
void fclSetMessagePosEx(dds3ProcessID_t *PID, u8 a_pos) {
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
  if ((BYTE4(ProcessData[1].monitor) & 3) == 0)
    LOBYTE(ProcessData[1].monitor) = a_pos;
}

// 0x1b3b950
void SetMessagePos(u8 a_pos) {
  fclSetMessagePosEx(g_mainPID, a_pos);
}

// 0x1b3b9b0
void fclSetClsModeEx(dds3ProcessID_t *PID, s32 a_mode) {
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
  if ((BYTE4(ProcessData[1].monitor) & 3) == 0)
    LODWORD(ProcessData[3].klass) = a_mode;
}

// 0x1b3bab0
void fclSetClsMode(s32 a_mode) {
  fclSetClsModeEx(g_mainPID, a_mode);
}

// 0x1b3bb10
bool ChkMessage(void *wk) {
  bool v4;

  v4 = fclChkMessage() == 0;
  if (wk->type != 2)
    return v4;
  gMsgFlag = (u8)gMsgFlag;
  if (gMsgFlag == 2)
    goto LABEL_13;
  if (gMsgFlag != 1)
    goto LABEL_14;
  goto LABEL_13;
  if (gMsgFlag == 1)
LABEL_13:
    v4 = 0;
LABEL_14:
  if (wk->select == -1)
    return 0;
  return v4;
}

// 0x1b3bd90
static s32 _Update(void *wk, dds3ProcessID_t *PID) {
  s32 flag;
  s32 msgNo;
  s32 selMesNo;
  s32 msgPos;
  s32 clsMode;
  s32 SelMessagePos;

  switch (wk->step)
  {
    case 0:
      flag = wk->flag;
      if ((flag & 4) == 0)
        return -2;
      wk->select = 0;
      wk->flag = flag & 0xFFFFFFFB;
      wk->step = 1;
      return -1;
    case 1:
      msgNo = wk->msgNo;
      fclStartMessage(msgNo);
      if (wk->type != 2)
        goto LABEL_49;
      selMesNo = wk->selMesNo;
      if (gMsgID < 0)
      {
        msgPos = wk->msgPos;
        goto LABEL_14;
      }
      gSelMsgNo = selMesNo;
      SelMessagePos = fclGetSelMessagePos();
      gLastSelMsgPos = SelMessagePos;
      msgPos = wk->msgPos;
LABEL_14:
      if (gMsgID < 0)
        goto LABEL_49;
      gSelMsgPos = msgPos;
LABEL_49:
      if (direct_call_mes)
      {
        scrEventSkipMsg1st();
      }
      wk->step = 2;
      return -1;
    case 2:
      if (ChkMessage(wk))
      {
        wk->step = 3;
        if (wk->selMesMax)
        {
          itfMesMngClearBitStatManager(1);
          return -1;
        }
        return -1;
      }
      clsMode = wk->clsMode;
      fclUpdateMessageEx(clsMode);
      if (wk->type != 2)
        return -1;
      if (fclChkSelMessage())
      {
        if (!wk->selInvild)
          return -1;
        wk->selInvild = 0;
        gMsgInvFlag = 0;
        return -1;
      }
      else
      {
        wk->select = fclGetSelMessagePos();
        return -1;
      }
    case 3:
      if (wk->clsMode == 1)
        fclResetEx(PID);
      if ((wk->flag & 4) == 0)
      {
        wk->type = -1;
        wk->msgNo = -1;
      }
      wk->step = 0;
      if (!direct_call_mes)
        goto LABEL_68;
      if (!GetNoSkipEnd())
      {
LABEL_68:
        scrEventSkipEnd(0, 0);
        scrLogEnd(PID);
      }
      return wk->select;
    default:
      return -2;
  }
}

// 0x1b3ca00
s32 fclUpdateEx(dds3ProcessID_t *PID) {
  s32 *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    return ProcessData[11];
  return ProcessData[11];
}

// 0x1b3cae0
s32 Update(void) {
  return fclUpdateEx(g_mainPID);
}

// 0x1b3cb30
static dds3ProcessFunc_t Process(dds3ProcessID_t *PID) {
  void *ProcessData;
  s32 flag;
  dds3ProcessFunc_t v8;
  s32 count;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  flag = ProcessData->flag;
  if ((flag & 1) != 0)
  {
    v8 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
    _ctor(v8, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
    return v8;
  }
  else if ((flag & 2) != 0)
  {
    count = ProcessData->count;
    if (ProcessData->count)
    {
      if (count >= 2)
      {
        LOWORD(count) = -1;
        ProcessData->flag = flag | 1;
      }
    }
    else
    {
      fclDestroyMessage();
      LOWORD(count) = ProcessData->count;
    }
    ProcessData->count = count + 1;
    return 0;
  }
  else
  {
    ProcessData->ret = _Update(ProcessData, id);
    return 0;
  }
}

// 0x1b3cd00
void Create(void) {
  dds3ProcessID_t *v1;

  v1 = fclProcessStart();
  g_mainPID = v1;
}

// 0x1b3cf00
dds3ProcessID_t *getID(void) {
  return g_mainPID;
}

// 0x1b3cf50
void fclFlagFalse(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  HIDWORD(ProcessData[1].monitor) |= 1u;
}

// 0x1b3d030
void Delete(void) {
  fclProcessEnd(g_mainPID);
  g_mainPID = 0;
}

// 0x1b3d1c0
bool fclCheck(void) {
  dds3ProcessID_t *id;

  id = g_mainPID;
  if (!g_mainPID)
    return 0;
  if (dds3GetProcessStat(id) == 3)
    return 0;
  if (dds3GetProcessStat(id))
    return 1;
  return 0;
}

// 0x1b3d3b0
static void Release(void *wk) {
  wk->pDatMsg = 0;
}

// 0x1b3d3c0
static void Shutdown(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  ProcessData[1].klass = 0;
}

// 0x1b3cd60
dds3ProcessID_t *fclProcessStart(void) {
  dds3ProcessID_t *v1;
  void *v2;
  dds3ProcessFunc_t v3;
  shutdownfuncDelegate v4;
  dds3ProcessID_t *result;

  v1 = Allocate(dds3ProcessID_t);
  _ctor(v1, 0);
  v2 = Allocate(tagFCLMSG_WORK);
  v3 = Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_fclMsg_Process__, 0);
  v4 = Allocate(shutdownfuncDelegate);
  _ctor(v4, 0, Method_Project_fclMsg_Shutdown__, 0);
  result = dds3StartProcess("fclmsg", 1024, 0, 0, v3, v4, v2);
  v2->selInvild = 0;
  v2->msgPos = 1;
  v2->selMesNo = 0;
  v2->selMesMax = 0;
  *(u64 *)&v2->ret = 0x1FFFFFFFELL;
  return result;
}

// 0x1b3d0a0
void fclProcessEnd(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 monitor_high;
  dds3ProcessID_t *id;

  id = PID;
  if (PID)
  {
    if (!dds3ExistProcess(id))
      return;
    ProcessData = dds3GetProcessData(id);
    if (!ProcessData)
    {
LABEL_14:
      monitor_high = HIDWORD(ProcessData[1].monitor);
      if ((monitor_high & 2) == 0)
      {
        HIWORD(ProcessData[2].klass) = 0;
        HIDWORD(ProcessData[1].monitor) = monitor_high | 2;
      }
      return;
    }
    goto LABEL_14;
  }
}

// 0x1b3d2d0
bool fclProcessCheck(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  if (!PID)
    return 0;
  if (dds3GetProcessStat(id) == 3)
    return 0;
  if (dds3GetProcessStat(id))
    return 1;
  return 0;
}
