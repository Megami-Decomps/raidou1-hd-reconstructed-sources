#include "types.h"
#include "buttonguide.h"
#include "cmpmain.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3adminiprocess.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3scenebasic.h"
#include "dds3worldbasic.h"
#include "ditectivebook.h"
#include "evtbit.h"
#include "evtpmv.h"
#include "evtviewer.h"
#include "fclmisc.h"
#include "fclmsg.h"
#include "itf.h"
#include "jmsdraw.h"
#include "jmsinit.h"
#include "jmsmain.h"
#include "jmsmenu.h"
#include "jmsmisc.h"
#include "kernel.h"
#include "localize.h"
#include "mdl.h"
#include "meslogmain.h"
#include "mjn.h"
#include "raijindlc.h"
#include "scr.h"
#include "slmain.h"

#define REPORT_MAX 12

typedef enum {
    MESSAGESCROLL_DOWN = -1,
    MESSAGESCROLL_ZERO = 0,
    MESSAGESCROLL_UP = 1,
} MESSAGESCROLL;

typedef struct REPORT_READ_FLAG_CLASS REPORT_READ_FLAG_CLASS;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct jmsData_t jmsData_t;
typedef struct jmsSeqUnit_t jmsSeqUnit_t;

static char *jmsCyousaFileTitle;
static char *jmsChosaFileMesssage;
REPORT_READ_FLAG_CLASS *REPORT_READ_FLAG;
static jmsSeqUnit_t *jmsSeqUnit;
s32 NarumiIsHere;

static s32 RootInit(dds3ProcessID_t *PID);
static s32 RootDestroy(dds3ProcessID_t *PID);
static dds3ProcessFunc_t RootCalcProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t RootDrawProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t RootUpdateProcess(dds3ProcessID_t *PID);
static s32 TalkSelInit(dds3ProcessID_t *PID);
static s32 TalkSelDestroy(dds3ProcessID_t *PID);
static dds3ProcessFunc_t TalkSelCalcProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t TalkSelDrawProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t TalkSelUpdateProcess(dds3ProcessID_t *PID);
static s32 TalkInit(dds3ProcessID_t *PID);
static s32 TalkDestroy(dds3ProcessID_t *PID);
static dds3ProcessFunc_t TalkCalcProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t TalkDrawProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t TalkUpdateProcess(dds3ProcessID_t *PID);
static s32 SaveInit(dds3ProcessID_t *PID);
static s32 SaveDestroy(dds3ProcessID_t *PID);
static dds3ProcessFunc_t SaveCalcProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t SaveDrawProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t SaveUpdateProcess(dds3ProcessID_t *PID);
static s32 CyousaFileSelInit(dds3ProcessID_t *PID);
static s32 CyousaFileSelDestroy(dds3ProcessID_t *PID);
static dds3ProcessFunc_t CyousaFileSelCalcProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t CyousaFileSelDrawProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t CyousaFileSelUpdateProcess(dds3ProcessID_t *PID);
static s32 CyousaSelInit(dds3ProcessID_t *PID);
static s32 CyousaSelDestroy(dds3ProcessID_t *PID);
static dds3ProcessFunc_t CyousaSelCalcProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t CyousaSelDrawProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t CyousaSelUpdateProcess(dds3ProcessID_t *PID);
static s32 CyousaInit(dds3ProcessID_t *PID);
static s32 CyousaDestroy(dds3ProcessID_t *PID);
static dds3ProcessFunc_t CyousaCalcProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t CyousaDrawProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t CyousaUpdateProcess(dds3ProcessID_t *PID);
static s32 MahjanInit(dds3ProcessID_t *PID);
static s32 MahjanDestroy(dds3ProcessID_t *PID);
static dds3ProcessFunc_t MahjanCalcProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t MahjanDrawProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t MahjanUpdateProcess(dds3ProcessID_t *PID);
static s32 KaminInit(dds3ProcessID_t *PID);
static s32 KaminDestroy(dds3ProcessID_t *PID);
static dds3ProcessFunc_t KaminCalcProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t KaminDrawProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t KaminUpdateProcess(dds3ProcessID_t *PID);
static s32 DBOOKInit(dds3ProcessID_t *PID);
static s32 DBOOKDestroy(dds3ProcessID_t *PID);
static dds3ProcessFunc_t DBOOKCalcProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t DBOOKDrawProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t DBOOKUpdateProcess(dds3ProcessID_t *PID);
static s32 CAMPInit(dds3ProcessID_t *PID);
static s32 CAMPDestroy(dds3ProcessID_t *PID);
static dds3ProcessFunc_t CAMPCalcProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t CAMPDrawProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t CAMPUpdateProcess(dds3ProcessID_t *PID);
static s32 DLCInit(dds3ProcessID_t *PID);
static s32 DLCDestroy(dds3ProcessID_t *PID);
static dds3ProcessFunc_t DLCCalcProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t DLCDrawProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t DLCUpdateProcess(dds3ProcessID_t *PID);
static bool DLC_ItemChack(jmsData_t *_data);
static s32 ScrControl(dds3ProcessID_t *PID);
static s32 CheckCyousaFilePrev(jmsData_t *pData);
static s32 CheckCyousaFileNext(jmsData_t *pData);
static void DrawCyousaMessage(jmsData_t *pData, s32 X, s32 Y, f32 AlphaRate);
static s32 CheckMahjanError(jmsData_t *pData);
s32 Start(void);

// 0x1cdebd0
static s32 RootInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *Instance;
  void *v8;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  BYTE4(ProcessData[16].monitor) = 0;
  LODWORD(ProcessData[16].monitor) = 0;
  jmsStart();
  jmsSetFocus(1);
  Instance = get_Instance(0);
  ItfButtonGuideSet(Instance, 1, 0);
  v8 = get_Instance(0);
  ItfButtonGuideActive(v8, 1, 0);
  ButtonLineHelpDispSet(1);
  ButtonGuideDispSet("JMS01", 0, 90);
  if (HIDWORD(ProcessData[9].klass))
    return 1;
  jmsDisableSelect(1);
  return 1;
}

// 0x1cdf2f0
static s32 RootDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1cdf300
static dds3ProcessFunc_t RootCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  Il2CppObject *v8;
  Il2CppObject *v10;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v12;
  dds3ProcessFunc_t v13;
  dds3ProcessID_t *klass;
  bool v15;
  s32 v18;
  bool v19;
  bool v21;
  jmsSeqUnit_t *jmsSeqUnit_local;
  jmsSeqUnit_t *v28;
  s32 SelectIndex;
  s32 klass_high;
  jmsSeqUnit_t *v35;
  Il2CppClass *v36;
  jmsSeqUnit_t *v37;
  void *Instance;
  jmsSeqUnit_t *v40;
  jmsSeqUnit_t *v42;
  jmsSeqUnit_t *v44;
  jmsSeqUnit_t *v46;
  jmsSeqUnit_t *v48;
  jmsSeqUnit_t *v49;
  jmsSeqUnit_t *v53;
  Il2CppClass *v54;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (!g_mainPID)
  {
    v8 = 0;
    goto LABEL_21;
  }
  v8 = dds3GetProcessData(g_mainPID);
  if (!v8)
    goto LABEL_21;
  goto LABEL_19;
  if (!v8)
LABEL_19:
LABEL_21:
  v10 = ProcessData + 2;
  monitor = ProcessData[1].monitor;
  v12 = id;
  v13 = jmsSeqChange(monitor, &ProcessData[2], 0, v12);
  if (v13)
    return v13;
  if (v8)
  {
    klass = v8[1].klass;
    if (klass)
    {
      if (itfMenuGetCtrlType(v8[1].klass) == 1)
        goto LABEL_28;
      goto LABEL_9002;
      if (itfMenuGetCtrlType(klass) == 1)
      {
LABEL_28:
        v15 = HIDWORD(v8[4].klass) == 4;
LABEL_37:
        selectFlag = v15;
        v18 = ProcessData[16].monitor;
        v19 = v18 == 9;
        if (v18 <= 9)
          goto LABEL_38;
        goto LABEL_40;
      }
LABEL_9002:
      v15 = 1;
      goto LABEL_37;
    }
  }
  selectFlag = 1;
  v18 = ProcessData[16].monitor;
  v19 = v18 == 9;
  if (v18 <= 9)
  {
LABEL_38:
    LODWORD(ProcessData[16].monitor) = v18 + 1;
    if (!v19)
      goto LABEL_42;
  }
LABEL_40:
  if (!BYTE4(ProcessData[16].monitor))
    BYTE4(ProcessData[16].monitor) = 1;
LABEL_42:
  v21 = CHECK_TRIG(8194, 1);
  if (v21)
  {
    if (!selectFlag)
    {
      if (BYTE4(ProcessData[16].monitor))
      {
        SE(17);
        HIDWORD(ProcessData[16].klass) = 1;
        MenuProcessStop();
        jmsSeqUnit_local = jmsSeqUnit;
        v28 = &jmsSeqUnit_local[11];
LABEL_99:
        v49 = v28;
        v10->klass = v28;
        v28->Stat = LOWORD(v28->Stat) | 0x20000;
LABEL_100:
        v13 = 0;
        LODWORD(ProcessData[8].monitor) = 0;
        return v13;
      }
    }
  }
  SelectIndex = jmsGetSelectIndex(1);
  if (SelectIndex == -1)
  {
    if (!jmsCheckMovePrev())
      goto LABEL_100;
LABEL_69:
    Instance = get_Instance(0);
    ItfButtonGuideSet(Instance, 0, 0);
    LODWORD(ProcessData[5].monitor) = 1;
    Preload(0, 0);
    v13 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
    _ctor(v13, 0, Method_Project_jmsMain_EndProcess__, 0);
  }
  else
  {
    switch (jmsGetSelectIndex(1))
    {
      case 1:
        if (ProcessData[6].klass)
          goto LABEL_100;
        klass_high = HIDWORD(ProcessData[9].klass);
        if (klass_high)
        {
          if (klass_high == 1)
          {
            LODWORD(ProcessData[9].monitor) = 0;
            v35 = jmsSeqUnit;
            v36 = v35[3];
            v10->klass = v36;
            v37 = v35[3];
          }
          else
          {
            v53 = jmsSeqUnit;
            v54 = v53[2];
            v10->klass = v54;
            v37 = v53[2];
          }
          v13 = 0;
          v37->Stat = LOWORD(v37->Stat) | 0x20000;
        }
        else
        {
          v13 = 0;
        }
        break;
      case 3:
        v40 = jmsSeqUnit;
        v28 = &v40[4];
        goto LABEL_99;
      case 4:
        v42 = jmsSeqUnit;
        v28 = &v42[5];
        goto LABEL_99;
      case 5:
        v44 = jmsSeqUnit;
        v28 = &v44[8];
        goto LABEL_99;
      case 6:
        goto LABEL_69;
      case 7:
        v46 = jmsSeqUnit;
        v28 = &v46[10];
        goto LABEL_99;
      case 8:
        v48 = jmsSeqUnit;
        v28 = &v48[12];
        goto LABEL_99;
      default:
        goto LABEL_100;
    }
  }
  return v13;
}

// 0x1ce0200
static dds3ProcessFunc_t RootDrawProcess(dds3ProcessID_t *PID) {
  sprHandle_t *v4;
  jmsData_t *ProcessData;
  s32 MenuFade;
  dds3ProcessID_t *v10;
  jmsSeqUnit_t *pSeqUnit;
  s64 Stat;
  jmsData_t *pData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  MenuFade = ProcessData->MenuFade;
  pData = ProcessData;
  if (MenuFade)
  {
    goto LABEL_11;
  }
  DrawBtnIcon(0, (s32)jmsData_t, v4);
LABEL_11:
  DrawModel(&pData, -1);
  v10 = id;
  if (!v10)
    return 0;
  pSeqUnit = ProcessData->pSeqUnit;
  if (!pSeqUnit)
    return 0;
  Stat = pSeqUnit->Stat;
  if ((Stat & 0x500000) != 0x100000)
    return 0;
  if ((Stat & 0x200000) != 0)
    return pSeqUnit->pDraw;
  if ((Stat & 1) == 0)
    return 0;
  pSeqUnit->Stat = Stat | 0x400000;
  (pSeqUnit->pDraw->invoke_impl)(pSeqUnit->pDraw->method_code, v10, pSeqUnit->pDraw->method);
  ProcessData->pSeqUnit->Stat &= ~0x400000u;
  return 0;
}

// 0x1ce09e0
static dds3ProcessFunc_t RootUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
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
  return jmsSeqChange(monitor, &ProcessData[2], 2, v7);
}

// 0x1ce0b00
static s32 TalkSelInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  u32 *monitor;
  void *Instance;
  void *v8;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[4].monitor;
  BYTE4(ProcessData[16].monitor) = 0;
  LODWORD(ProcessData[16].monitor) = 0;
  if (!monitor[6])
    monitor[4] = 0;
  monitor[5] = 1;
  monitor[7] = 0;
  Instance = get_Instance(0);
  ItfButtonGuideSet(Instance, 1, 0);
  v8 = get_Instance(0);
  ItfButtonGuideActive(v8, 1, 0);
  ButtonLineHelpDispSet(1);
  ButtonGuideDispSet("JMS03", 0, 90);
  return 1;
}

// 0x1ce0ca0
static s32 TalkSelDestroy(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  *((u32 *)ProcessData[4].monitor + 5) = 0;
  SetActiveSelIcon(jmsUIctrlSub, 0, 0);
  return 1;
}

// 0x1ce0db0
static dds3ProcessFunc_t TalkSelCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  Il2CppObject *v6;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v9;
  dds3ProcessFunc_t v10;
  dds3ProcessID_t *klass;
  char v12;
  s32 v14;
  bool v15;
  bool v17;
  jmsSeqUnit_t *jmsSeqUnit_local;
  Il2CppClass **v24;
  s32 SelectIndex;
  jmsSeqUnit_t *v31;
  jmsSeqUnit_t *v33;
  Il2CppClass *v34;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v6 = dds3GetProcessData(g_mainPID);
  if (!v6)
  monitor = ProcessData[1].monitor;
  v9 = id;
  v10 = jmsSeqChange(monitor, &ProcessData[2], 0, v9);
  if (!v10)
  {
    klass = v6[1].klass;
    if (itfMenuGetCtrlType(v6[1].klass) == 1)
      goto LABEL_20;
    goto LABEL_9002;
    if (itfMenuGetCtrlType(klass) == 1)
    {
LABEL_20:
      v12 = HIDWORD(v6[4].klass) == 4;
      selectFlag = v12;
      v14 = ProcessData[16].monitor;
      v15 = v14 == 9;
      if (v14 <= 9)
      {
LABEL_27:
        LODWORD(ProcessData[16].monitor) = v14 + 1;
        if (!v15)
          goto LABEL_31;
      }
LABEL_29:
      if (!BYTE4(ProcessData[16].monitor))
        BYTE4(ProcessData[16].monitor) = 1;
LABEL_31:
      v17 = CHECK_TRIG(8194, 1);
      if (!v17)
        goto LABEL_41;
      if (selectFlag)
        goto LABEL_41;
      if (BYTE4(ProcessData[16].monitor))
      {
        SE(17);
        HIDWORD(ProcessData[16].klass) = 2;
        MenuProcessStop();
        jmsSeqUnit_local = jmsSeqUnit;
        v24 = &jmsSeqUnit_local[11];
        goto LABEL_62;
      }
LABEL_41:
      SelectIndex = jmsGetSelectIndex(0);
      if (SelectIndex == -1)
      {
        if (!jmsCheckMovePrev())
          goto LABEL_63;
        v33 = jmsSeqUnit;
        v24 = &v33[1];
      }
      else
      {
        if (jmsGetSelectIndex(0) < 24)
          goto LABEL_63;
        *((u32 *)ProcessData[4].monitor + 5) = 0;
        LODWORD(ProcessData[9].monitor) = jmsGetSelectIndex(0) - 24;
        v31 = jmsSeqUnit;
        v24 = &v31[3];
      }
LABEL_62:
      v34 = *v24;
      ProcessData[2].klass = *v24;
      (*v24)->_1.name = (LOWORD((*v24)->_1.name) | 0x20000);
LABEL_63:
      LODWORD(ProcessData[8].monitor) = 0;
      return v10;
LABEL_24:
      selectFlag = v12;
      v14 = ProcessData[16].monitor;
      v15 = v14 == 9;
      if (v14 <= 9)
        goto LABEL_27;
      goto LABEL_29;
    }
LABEL_9002:
    v12 = 1;
    goto LABEL_24;
  }
  return v10;
}

// 0x1ce1260
static dds3ProcessFunc_t TalkSelDrawProcess(dds3ProcessID_t *PID) {
  jmsData_t *ProcessData;
  s32 v7;
  dds3ProcessID_t *v8;
  jmsSeqUnit_t *pSeqUnit;
  s64 Stat;
  jmsData_t *v12;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v12 = ProcessData;
  v7 = jmsGetCursorPosID() - 24;
  DrawModel(&v12, v7);
  v8 = id;
  if (!v8)
    return 0;
  pSeqUnit = ProcessData->pSeqUnit;
  if (!pSeqUnit)
    return 0;
  Stat = pSeqUnit->Stat;
  if ((Stat & 0x500000) != 0x100000)
    return 0;
  if ((Stat & 0x200000) != 0)
    return pSeqUnit->pDraw;
  if ((Stat & 1) == 0)
    return 0;
  pSeqUnit->Stat = Stat | 0x400000;
  (pSeqUnit->pDraw->invoke_impl)(pSeqUnit->pDraw->method_code, v8, pSeqUnit->pDraw->method);
  ProcessData->pSeqUnit->Stat &= ~0x400000u;
  return 0;
}

// 0x1ce1610
static dds3ProcessFunc_t TalkSelUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
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
  return jmsSeqChange(monitor, &ProcessData[2], 2, v7);
}

// 0x1ce1730
static s32 TalkInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *Instance;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  Instance = get_Instance(0);
  ItfButtonGuideSet(Instance, 0, 0);
  if (!ProcessData)
  LODWORD(ProcessData[5].monitor) = 2;
  return 1;
}

// 0x1ce1850
static s32 TalkDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1ce1860
static dds3ProcessFunc_t TalkCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  Il2CppObject *v6;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v8;
  dds3ProcessFunc_t v10;
  dds3ProcessID_t *v11;
  void *Instance;
  jmsSeqUnit_t *jmsSeqUnit_local;
  jmsSeqUnit_t *v17;
  void *v18;
  jmsSeqUnit_t *v22;
  jmsSeqUnit_t *v23;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v6 = ProcessData + 2;
  monitor = ProcessData[1].monitor;
  v8 = id;
  v10 = jmsSeqChange(monitor, &ProcessData[2], 0, v8);
  if (!v10)
  {
    v11 = id;
    if (!ScrControl(id))
    {
      if (HIDWORD(ProcessData[9].klass) == 1)
      {
        Instance = get_Instance(0);
        ItfButtonGuideSet(Instance, 1, 0);
        jmsSeqUnit_local = jmsSeqUnit;
        v17 = &jmsSeqUnit_local[1];
        goto LABEL_30;
      }
      v18 = get_Instance(0);
      ItfButtonGuideSet(v18, 1, 0);
      jmsStart();
      v22 = jmsSeqUnit;
      v17 = &v22[2];
LABEL_30:
      v23 = v17;
      v6->klass = v17;
      v17->Stat = LOWORD(v17->Stat) | 0x20000;
      return v10;
    }
  }
  return v10;
}

// 0x1ce1f70
static dds3ProcessFunc_t TalkDrawProcess(dds3ProcessID_t *PID) {
  jmsData_t *ProcessData;
  dds3ProcessID_t *v6;
  jmsSeqUnit_t *pSeqUnit;
  s64 Stat;
  jmsData_t *pData;
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
  DrawModel(&pData, -1);
  v6 = id;
  if (!v6)
    return 0;
  pSeqUnit = ProcessData->pSeqUnit;
  if (!pSeqUnit)
    return 0;
  Stat = pSeqUnit->Stat;
  if ((Stat & 0x500000) != 0x100000)
    return 0;
  if ((Stat & 0x200000) != 0)
    return pSeqUnit->pDraw;
  if ((Stat & 1) == 0)
    return 0;
  pSeqUnit->Stat = Stat | 0x400000;
  (pSeqUnit->pDraw->invoke_impl)(pSeqUnit->pDraw->method_code, v6, pSeqUnit->pDraw->method);
  ProcessData->pSeqUnit->Stat &= ~0x400000u;
  return 0;
}

// 0x1ce2170
static dds3ProcessFunc_t TalkUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
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
  return jmsSeqChange(monitor, &ProcessData[2], 2, v7);
}

// 0x1ce2290
static s32 SaveInit(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1ce22a0
static s32 SaveDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1ce22b0
static dds3ProcessFunc_t SaveCalcProcess(dds3ProcessID_t *PID) {
  jmsData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  GameFileInfo_t *GameFileInfo;
  s32 v13;
  jmsSeqUnit_t *v18;
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
  SeqHandle = ProcessData->SeqHandle;
  v7 = id;
  v8 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v7);
  if (!v8)
  {
    switch (ProcessData->SaveStat)
    {
      case 0:
        dds3FadeOut(0, 0, 0, 0x1Eu);
        goto LABEL_31;
      case 1:
        if (dds3FadeCheck())
          return v8;
        Delete(0);
        ProcessEnd();
LABEL_31:
        v13 = ProcessData->SaveStat + 1;
        break;
      case 2:
        basic = dds3GetActiveScene();
        dds3SceneBasicVisible(basic, 0);
        GameFileInfo = GBWK->GameFileInfo;
        *(u16 *)&GameFileInfo->TmnlMode = 0;
        slSetTmnlID(0, 0);
        fmProcTrigSequence(0);
        goto LABEL_31;
      case 3:
        if (fmProcessChk())
          return v8;
        ProcessStart(jmsMenu);
        Create(0);
        jmsAddTalkMenu(ProcessData);
        basic = dds3GetActiveScene();
        dds3SceneBasicVisible(basic, 1);
        dds3FadeIn(0, 0, 0, 0x1Eu);
        v18 = jmsSeqUnit[1];
        ProcessData->pSeqUnit = v18;
        v13 = 0;
        jmsSeqUnit[1]->Stat = LOWORD(jmsSeqUnit[1]->Stat) | 0x20000;
        break;
      default:
        return v8;
    }
    ProcessData->SaveStat = v13;
  }
  return v8;
}

// 0x1ce2bd0
static dds3ProcessFunc_t SaveDrawProcess(dds3ProcessID_t *PID) {
  jmsData_t *ProcessData;
  s32 SaveStat;
  dds3ProcessID_t *v8;
  jmsSeqUnit_t *pSeqUnit;
  s64 Stat;
  jmsData_t *pData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  SaveStat = ProcessData->SaveStat;
  pData = ProcessData;
  if (SaveStat <= 1)
  {
    DrawModel(&pData, -1);
    v8 = id;
LABEL_11:
    goto LABEL_12;
  }
  else
  {
    v8 = id;
    goto LABEL_11;
  }
LABEL_12:
  if (!v8)
    return 0;
  pSeqUnit = ProcessData->pSeqUnit;
  if (!pSeqUnit)
    return 0;
  Stat = pSeqUnit->Stat;
  if ((Stat & 0x500000) != 0x100000)
    return 0;
  if ((Stat & 0x200000) != 0)
    return pSeqUnit->pDraw;
  if ((Stat & 1) == 0)
    return 0;
  pSeqUnit->Stat = Stat | 0x400000;
  (pSeqUnit->pDraw->invoke_impl)(pSeqUnit->pDraw->method_code, v8, pSeqUnit->pDraw->method);
  ProcessData->pSeqUnit->Stat &= ~0x400000u;
  return 0;
}

// 0x1ce2df0
static dds3ProcessFunc_t SaveUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
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
  return jmsSeqChange(monitor, &ProcessData[2], 2, v7);
}

// 0x1ce2f10
static s32 CyousaFileSelInit(dds3ProcessID_t *PID) {
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
  BYTE4(ProcessData[16].monitor) = 0;
  LODWORD(ProcessData[16].monitor) = 0;
  Instance = get_Instance(0);
  ItfButtonGuideSet(Instance, 1, 0);
  v6 = get_Instance(0);
  ItfButtonGuideActive(v6, 1, 0);
  ButtonLineHelpDispSet(1);
  ButtonGuideDispSet("JMS03", 0, 90);
  return 1;
}

// 0x1ce3090
static s32 CyousaFileSelDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1ce30a0
static dds3ProcessFunc_t CyousaFileSelCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  Il2CppObject *v6;
  Il2CppObject *v8;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v10;
  dds3ProcessFunc_t v11;
  dds3ProcessID_t *klass;
  char v13;
  s32 v15;
  bool v16;
  bool v18;
  jmsSeqUnit_t *jmsSeqUnit_local;
  jmsSeqUnit_t *v25;
  s32 SelectIndex;
  jmsSeqUnit_t *v31;
  jmsSeqUnit_t *v33;
  jmsSeqUnit_t *v34;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v6 = dds3GetProcessData(g_mainPID);
  if (!v6)
  v8 = ProcessData + 2;
  monitor = ProcessData[1].monitor;
  v10 = id;
  v11 = jmsSeqChange(monitor, &ProcessData[2], 0, v10);
  if (v11)
    return v11;
  klass = v6[1].klass;
  if (itfMenuGetCtrlType(v6[1].klass) == 1)
    goto LABEL_20;
  v13 = 1;
LABEL_24:
  selectFlag = v13;
  v15 = ProcessData[16].monitor;
  v16 = v15 == 9;
  if (v15 <= 9)
    goto LABEL_27;
  goto LABEL_29;
LABEL_20:
  v13 = HIDWORD(v6[4].klass) == 4;
  goto LABEL_24;
  if (v15 <= 9)
  {
LABEL_27:
    LODWORD(ProcessData[16].monitor) = v15 + 1;
    if (!v16)
      goto LABEL_31;
  }
LABEL_29:
  if (!BYTE4(ProcessData[16].monitor))
    BYTE4(ProcessData[16].monitor) = 1;
LABEL_31:
  v18 = CHECK_TRIG(8194, 1);
  if (v18)
  {
    if (!selectFlag)
    {
      if (BYTE4(ProcessData[16].monitor))
      {
        SE(17);
        HIDWORD(ProcessData[16].klass) = 5;
        MenuProcessStop();
        jmsSeqUnit_local = jmsSeqUnit;
        v25 = &jmsSeqUnit_local[11];
LABEL_60:
        v34 = v25;
        v8->klass = v25;
        v25->Stat = LOWORD(v25->Stat) | 0x20000;
        return v11;
      }
    }
  }
  SelectIndex = jmsGetSelectIndex(0);
  if (SelectIndex == -1)
  {
    if (jmsCheckMovePrev())
    {
      v33 = jmsSeqUnit;
      v25 = &v33[1];
      goto LABEL_60;
    }
  }
  else
  {
    if ((u32)(jmsGetSelectIndex(0) - 9) <= 2)
    {
      v31 = jmsSeqUnit;
      v25 = &v31[6];
      goto LABEL_60;
    }
  }
  return v11;
}

// 0x1ce3520
static dds3ProcessFunc_t CyousaFileSelDrawProcess(dds3ProcessID_t *PID) {
  jmsData_t *ProcessData;
  dds3ProcessID_t *v6;
  jmsSeqUnit_t *pSeqUnit;
  s64 Stat;
  jmsData_t *pData;
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
  DrawModel(&pData, -1);
  v6 = id;
  if (!v6)
    return 0;
  pSeqUnit = ProcessData->pSeqUnit;
  if (!pSeqUnit)
    return 0;
  Stat = pSeqUnit->Stat;
  if ((Stat & 0x500000) != 0x100000)
    return 0;
  if ((Stat & 0x200000) != 0)
    return pSeqUnit->pDraw;
  if ((Stat & 1) == 0)
    return 0;
  pSeqUnit->Stat = Stat | 0x400000;
  (pSeqUnit->pDraw->invoke_impl)(pSeqUnit->pDraw->method_code, v6, pSeqUnit->pDraw->method);
  ProcessData->pSeqUnit->Stat &= ~0x400000u;
  return 0;
}

// 0x1ce3720
static dds3ProcessFunc_t CyousaFileSelUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
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
  return jmsSeqChange(monitor, &ProcessData[2], 2, v7);
}

// 0x1ce3840
static s32 CyousaSelInit(dds3ProcessID_t *PID) {
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
  BYTE4(ProcessData[16].monitor) = 0;
  LODWORD(ProcessData[16].monitor) = 0;
  Instance = get_Instance(0);
  ItfButtonGuideSet(Instance, 1, 0);
  v6 = get_Instance(0);
  ItfButtonGuideActive(v6, 1, 0);
  ButtonLineHelpDispSet(1);
  ButtonGuideDispSet("JMS03", 0, 90);
  return 1;
}

// 0x1ce39c0
static s32 CyousaSelDestroy(dds3ProcessID_t *PID) {
  jmsReturnReadFlagData();
  return 1;
}

// 0x1ce3a40
static dds3ProcessFunc_t CyousaSelCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  Il2CppObject *v6;
  Il2CppObject *v8;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v10;
  dds3ProcessFunc_t v11;
  dds3ProcessID_t *klass;
  char v13;
  s32 v15;
  bool v16;
  bool v18;
  jmsSeqUnit_t *jmsSeqUnit_local;
  jmsSeqUnit_t *v25;
  s32 SelectIndex;
  jmsSeqUnit_t *v31;
  jmsSeqUnit_t *v33;
  jmsSeqUnit_t *v34;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v6 = dds3GetProcessData(g_mainPID);
  if (!v6)
  v8 = ProcessData + 2;
  monitor = ProcessData[1].monitor;
  v10 = id;
  v11 = jmsSeqChange(monitor, &ProcessData[2], 0, v10);
  if (v11)
    return v11;
  klass = v6[1].klass;
  if (itfMenuGetCtrlType(v6[1].klass) == 1)
    goto LABEL_20;
  v13 = 1;
LABEL_24:
  selectFlag = v13;
  v15 = ProcessData[16].monitor;
  v16 = v15 == 9;
  if (v15 <= 9)
    goto LABEL_27;
  goto LABEL_29;
LABEL_20:
  v13 = HIDWORD(v6[4].klass) == 4;
  goto LABEL_24;
  if (v15 <= 9)
  {
LABEL_27:
    LODWORD(ProcessData[16].monitor) = v15 + 1;
    if (!v16)
      goto LABEL_31;
  }
LABEL_29:
  if (!BYTE4(ProcessData[16].monitor))
    BYTE4(ProcessData[16].monitor) = 1;
LABEL_31:
  v18 = CHECK_TRIG(8194, 1);
  if (v18)
  {
    if (!selectFlag)
    {
      if (BYTE4(ProcessData[16].monitor))
      {
        SE(17);
        HIDWORD(ProcessData[16].klass) = 6;
        MenuProcessStop();
        jmsSeqUnit_local = jmsSeqUnit;
        v25 = &jmsSeqUnit_local[11];
LABEL_57:
        v34 = v25;
        v8->klass = v25;
        v25->Stat = LOWORD(v25->Stat) | 0x20000;
        return v11;
      }
    }
  }
  SelectIndex = jmsGetSelectIndex(0);
  if (SelectIndex != -1)
  {
    LODWORD(ProcessData[10].monitor) = jmsGetSelectIndex(0) - 12;
    v31 = jmsSeqUnit;
    v25 = &v31[7];
    goto LABEL_57;
  }
  if (jmsCheckMovePrev())
  {
    v33 = jmsSeqUnit;
    v25 = &v33[5];
    goto LABEL_57;
  }
  return v11;
}

// 0x1ce3ed0
static dds3ProcessFunc_t CyousaSelDrawProcess(dds3ProcessID_t *PID) {
  jmsData_t *ProcessData;
  dds3ProcessID_t *v6;
  jmsSeqUnit_t *pSeqUnit;
  s64 Stat;
  jmsData_t *pData;
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
  DrawModel(&pData, -1);
  v6 = id;
  if (!v6)
    return 0;
  pSeqUnit = ProcessData->pSeqUnit;
  if (!pSeqUnit)
    return 0;
  Stat = pSeqUnit->Stat;
  if ((Stat & 0x500000) != 0x100000)
    return 0;
  if ((Stat & 0x200000) != 0)
    return pSeqUnit->pDraw;
  if ((Stat & 1) == 0)
    return 0;
  pSeqUnit->Stat = Stat | 0x400000;
  (pSeqUnit->pDraw->invoke_impl)(pSeqUnit->pDraw->method_code, v6, pSeqUnit->pDraw->method);
  ProcessData->pSeqUnit->Stat &= ~0x400000u;
  return 0;
}

// 0x1ce40d0
static dds3ProcessFunc_t CyousaSelUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
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
  return jmsSeqChange(monitor, &ProcessData[2], 2, v7);
}

// 0x1ce41f0
static s32 CyousaInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *Instance;
  char *v8;
  char *LocalizeText;
  char *v11;
  s64 monitor_low;
  REPORT_READ_FLAG_CLASS *v14;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  SetChosasyoAnim(jmsUIctrlSub, 1, 0);
  Instance = get_Instance(0);
  ItfButtonGuideSet(Instance, 1, 0);
  ButtonGuideDispSet("JMS02", 0, 90);
  *(u64 *)((char *)ProcessData[12].monitor + 20) = 0;
  jmsCallDrawBack();
  v8 = jmsChosaFileMesssage[SLODWORD(ProcessData[10].monitor)];
  LocalizeText = GetLocalizeText(v8, 0);
  v11 = GetLocalizeText(jmsCyousaFileTitle[SLODWORD(ProcessData[10].monitor)], 0);
  ChosasyoSetMessage(jmsUIctrlSub, LocalizeText, v11, 0);
  ChosasyoTextScrollReset(jmsUIctrlSub, 0);
  monitor_low = SLODWORD(ProcessData[10].monitor);
  v14 = REPORT_READ_FLAG[monitor_low];
  if (v14->READ_FLAG)
    return 1;
  v14 = REPORT_READ_FLAG[monitor_low];
  v14->READ_FLAG = 1;
  return 1;
}

// 0x1ce4970
static s32 CyousaDestroy(dds3ProcessID_t *PID) {
  jmsStart();
  jmsCallDrawBack();
  return 1;
}

// 0x1ce49f0
static dds3ProcessFunc_t CyousaCalcProcess(dds3ProcessID_t *PID) {
  jmsData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v9;
  jmsCyousaPanel_t *CyousaPanel;
  f32 AlphaRate;
  jmsSeqUnit_t *v14;
  jmsCyousaPanel_t *v15;
  s32 v17;
  jmsCyousaPanel_t *v19;
  jmsCyousaPanel_t *v20;
  f32 LCursorAlphaRate;
  f32 RCursorAlphaRate;
  s32 v23;
  jmsCyousaPanel_t *v25;
  s32 v26;
  jmsCyousaPanel_t *v29;
  f32 UCursorAlphaRate;
  void *v31;
  jmsCyousaPanel_t *v32;
  f32 DCursorAlphaRate;
  s32 v36;
  REPORT_READ_FLAG_CLASS *v41;
  char *v42;
  char *LocalizeText;
  char *v45;
  s32 v48;
  u32 v50;
  REPORT_READ_FLAG_CLASS *v53;
  char *v54;
  char *v55;
  char *v57;
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
  v7 = id;
  v9 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v7);
  if (v9)
    return v9;
  CyousaPanel = ProcessData->CyousaPanel;
  AlphaRate = CyousaPanel->AlphaRate;
  if (!CyousaPanel->FadeFlag)
  {
    if (AlphaRate >= 1.0)
    {
      if (AlphaRate <= 1.0)
      {
LABEL_25:
        if (CHECK_TRIG(4097, 1))
        {
          SetChosasyoAnim(jmsUIctrlSub, 2, 0);
          ProcessData->CyousaPanel->FadeFlag = 1;
          SE(1);
        }
        goto LABEL_33;
      }
    }
    else
    {
      AlphaRate = AlphaRate + 0.0625;
    }
    if (AlphaRate > 1.0)
      AlphaRate = 1.0;
    CyousaPanel->AlphaRate = AlphaRate;
    goto LABEL_25;
  }
  if (AlphaRate == 0.0)
  {
    v14 = jmsSeqUnit[6];
    ProcessData->pSeqUnit = v14;
    jmsSeqUnit[6]->Stat = LOWORD(jmsSeqUnit[6]->Stat) | 0x20000;
  }
  else
  {
    if (AlphaRate <= 0.0)
    {
      if (AlphaRate >= 0.0)
        goto LABEL_33;
    }
    else
    {
      AlphaRate = AlphaRate + -0.0625;
    }
    if (AlphaRate < 0.0)
      AlphaRate = 0.0;
    CyousaPanel->AlphaRate = AlphaRate;
  }
LABEL_33:
  v15 = ProcessData->CyousaPanel;
  v17 = CheckCyousaFilePrev(ProcessData) ^ 1;
  v15->LCursorFadeFlag = v17;
  v19 = ProcessData->CyousaPanel;
  v19->RCursorFadeFlag = CheckCyousaFileNext(ProcessData) ^ 1;
  v20 = ProcessData->CyousaPanel;
  LCursorAlphaRate = v20->LCursorAlphaRate;
  if (v20->LCursorFadeFlag)
  {
    if (LCursorAlphaRate == 1.0)
    {
      ChosasyoCursorSetAnim_L(jmsUIctrlSub, 2, 0);
      v20 = ProcessData->CyousaPanel;
      LCursorAlphaRate = v20->LCursorAlphaRate;
    }
    if (LCursorAlphaRate <= 0.0)
    {
      if (LCursorAlphaRate >= 0.0)
        goto LABEL_54;
    }
    else
    {
      LCursorAlphaRate = LCursorAlphaRate + -0.0625;
    }
    if (LCursorAlphaRate < 0.0)
      LCursorAlphaRate = 0.0;
  }
  else
  {
    if (LCursorAlphaRate == 0.0)
    {
      ChosasyoCursorSetAnim_L(jmsUIctrlSub, 1, 0);
      v20 = ProcessData->CyousaPanel;
      LCursorAlphaRate = v20->LCursorAlphaRate;
    }
    if (LCursorAlphaRate >= 1.0)
    {
      if (LCursorAlphaRate <= 1.0)
        goto LABEL_54;
    }
    else
    {
      LCursorAlphaRate = LCursorAlphaRate + 0.0625;
    }
    if (LCursorAlphaRate > 1.0)
      LCursorAlphaRate = 1.0;
  }
  v20->LCursorAlphaRate = LCursorAlphaRate;
LABEL_54:
  RCursorAlphaRate = v20->RCursorAlphaRate;
  if (v20->RCursorFadeFlag)
  {
    if (RCursorAlphaRate == 1.0)
    {
      ChosasyoCursorSetAnim_R(jmsUIctrlSub, 2, 0);
      v20 = ProcessData->CyousaPanel;
      RCursorAlphaRate = v20->RCursorAlphaRate;
    }
    if (RCursorAlphaRate <= 0.0)
    {
      if (RCursorAlphaRate >= 0.0)
        goto LABEL_71;
    }
    else
    {
      RCursorAlphaRate = RCursorAlphaRate + -0.0625;
    }
    if (RCursorAlphaRate < 0.0)
      RCursorAlphaRate = 0.0;
  }
  else
  {
    if (RCursorAlphaRate == 0.0)
    {
      ChosasyoCursorSetAnim_R(jmsUIctrlSub, 1, 0);
      v20 = ProcessData->CyousaPanel;
      RCursorAlphaRate = v20->RCursorAlphaRate;
    }
    if (RCursorAlphaRate >= 1.0)
    {
      if (RCursorAlphaRate <= 1.0)
        goto LABEL_71;
    }
    else
    {
      RCursorAlphaRate = RCursorAlphaRate + 0.0625;
    }
    if (RCursorAlphaRate > 1.0)
      RCursorAlphaRate = 1.0;
  }
  v20->RCursorAlphaRate = RCursorAlphaRate;
LABEL_71:
  v23 = ChosasyoCheckTextScroll_U(jmsUIctrlSub, 0);
  v20->UCursorFadeFlag = v23;
  v25 = ProcessData->CyousaPanel;
  v26 = ChosasyoCheckTextScroll_D(jmsUIctrlSub, 0);
  v25->DCursorFadeFlag = v26;
  if (ProcessData->CyousaPanel->UCursorFadeFlag)
  {
    ChosasyoCursorSetAnim_U(jmsUIctrlSub, 1, 0);
    v29 = ProcessData->CyousaPanel;
    UCursorAlphaRate = v29->UCursorAlphaRate;
    if (UCursorAlphaRate >= 1.0)
    {
      if (UCursorAlphaRate <= 1.0)
        goto LABEL_84;
    }
    else
    {
      UCursorAlphaRate = UCursorAlphaRate + 0.0625;
    }
    if (UCursorAlphaRate > 1.0)
      UCursorAlphaRate = 1.0;
  }
  else
  {
    ChosasyoCursorSetAnim_U(jmsUIctrlSub, 2, 0);
    v29 = ProcessData->CyousaPanel;
    UCursorAlphaRate = v29->UCursorAlphaRate;
    if (UCursorAlphaRate <= 0.0)
    {
      if (UCursorAlphaRate >= 0.0)
        goto LABEL_84;
    }
    else
    {
      UCursorAlphaRate = UCursorAlphaRate + -0.0625;
    }
    if (UCursorAlphaRate < 0.0)
      UCursorAlphaRate = 0.0;
  }
  v29->UCursorAlphaRate = UCursorAlphaRate;
LABEL_84:
  v31 = jmsUIctrlSub;
  if (!v29->DCursorFadeFlag)
  {
    ChosasyoCursorSetAnim_D(v31, 2, 0);
    v32 = ProcessData->CyousaPanel;
    DCursorAlphaRate = v32->DCursorAlphaRate;
    if (DCursorAlphaRate <= 0.0)
    {
      if (DCursorAlphaRate >= 0.0)
        goto LABEL_97;
    }
    else
    {
      DCursorAlphaRate = DCursorAlphaRate + -0.0625;
    }
    if (DCursorAlphaRate < 0.0)
      DCursorAlphaRate = 0.0;
    goto LABEL_96;
  }
  ChosasyoCursorSetAnim_D(v31, 1, 0);
  v32 = ProcessData->CyousaPanel;
  DCursorAlphaRate = v32->DCursorAlphaRate;
  if (DCursorAlphaRate < 1.0)
  {
    DCursorAlphaRate = DCursorAlphaRate + 0.0625;
    goto LABEL_88;
  }
  if (DCursorAlphaRate > 1.0)
  {
LABEL_88:
    if (DCursorAlphaRate > 1.0)
      DCursorAlphaRate = 1.0;
LABEL_96:
    v32->DCursorAlphaRate = DCursorAlphaRate;
  }
LABEL_97:
  if (CHECK_REP(4101, 1) && ProcessData->CyousaPanel->DCursorFadeFlag)
    ChosasyoTextScrollCtrl(jmsUIctrlSub, -1, 0);
  if (CHECK_REP(4100, 1) && ProcessData->CyousaPanel->UCursorFadeFlag)
    ChosasyoTextScrollCtrl(jmsUIctrlSub, 1, 0);
  if (CHECK_REP(4104, 1))
  {
    if (CheckCyousaFilePrev(ProcessData))
    {
      v36 = ProcessData->CyousaFileIndex - 1;
      ProcessData->CyousaFileIndex = v36;
      v41 = REPORT_READ_FLAG[v36];
      if (!v41->READ_FLAG)
      {
        v41 = REPORT_READ_FLAG[v36];
        v41->READ_FLAG = 1;
      }
      v42 = jmsChosaFileMesssage[ProcessData->CyousaFileIndex];
      LocalizeText = GetLocalizeText(v42, 0);
      v45 = GetLocalizeText(jmsCyousaFileTitle[ProcessData->CyousaFileIndex], 0);
      ChosasyoSetMessage(jmsUIctrlSub, LocalizeText, v45, 0);
      ChosasyoTextScrollReset(jmsUIctrlSub, 0);
      SE(4259852);
    }
  }
  if (CHECK_REP(4107, 1))
  {
    if (CheckCyousaFileNext(ProcessData))
    {
      v48 = ProcessData->CyousaFileIndex + 1;
      ProcessData->CyousaFileIndex = v48;
      if (v50)
      {
        goto LABEL_127;
      }
      else
      {
LABEL_127:
        goto LABEL_128;
      }
LABEL_128:
      v53 = REPORT_READ_FLAG[v48];
      if (!v53->READ_FLAG)
      {
        v53 = REPORT_READ_FLAG[v48];
        v53->READ_FLAG = 1;
      }
      v54 = jmsChosaFileMesssage[ProcessData->CyousaFileIndex];
      v55 = GetLocalizeText(v54, 0);
      v57 = GetLocalizeText(jmsCyousaFileTitle[ProcessData->CyousaFileIndex], 0);
      ChosasyoSetMessage(jmsUIctrlSub, v55, v57, 0);
      ChosasyoTextScrollReset(jmsUIctrlSub, 0);
      SE(4259852);
    }
  }
  return v9;
}

// 0x1ce55a0
static dds3ProcessFunc_t CyousaDrawProcess(dds3ProcessID_t *PID) {
  jmsData_t *ProcessData;
  s32 v7;
  sprHandle_t *v8;
  dds3ProcessID_t *v10;
  jmsSeqUnit_t *pSeqUnit;
  s64 Stat;
  jmsData_t *pData;
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
  DrawModel(&pData, -1);
  DrawCyousaPanel(ProcessData->CyousaPanel, ProcessData->pSpr);
  DrawBtnIcon(1, v7, v8);
  v10 = id;
  if (!v10)
    return 0;
  pSeqUnit = ProcessData->pSeqUnit;
  if (!pSeqUnit)
    return 0;
  Stat = pSeqUnit->Stat;
  if ((Stat & 0x500000) != 0x100000)
    return 0;
  if ((Stat & 0x200000) != 0)
    return pSeqUnit->pDraw;
  if ((Stat & 1) == 0)
    return 0;
  pSeqUnit->Stat = Stat | 0x400000;
  (pSeqUnit->pDraw->invoke_impl)(pSeqUnit->pDraw->method_code, v10, pSeqUnit->pDraw->method);
  ProcessData->pSeqUnit->Stat &= ~0x400000u;
  return 0;
}

// 0x1ce58a0
static dds3ProcessFunc_t CyousaUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
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
  return jmsSeqChange(monitor, &ProcessData[2], 2, v7);
}

// 0x1ce4880
void jmsReportReadFlagUpdate(s32 FileID) {
  REPORT_READ_FLAG_CLASS *v4;

  v4 = REPORT_READ_FLAG[FileID];
  if (v4->READ_FLAG)
    return;
  v4->READ_FLAG = 1;
}

// 0x1ce59c0
bool jmsReportReadFlagChack(s32 FileID) {
  return REPORT_READ_FLAG[FileID]->READ_FLAG;
}

// 0x1ce5a40
static s32 MahjanInit(dds3ProcessID_t *PID) {
  jmsData_t *ProcessData;
  s32 v5;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  NarumiIsHere = 0;
  if (!ProcessData)
  v5 = CheckMahjanError(ProcessData);
  ProcessData->MahjanStat = 0;
  ProcessData->MahjanErr = v5;
  return 1;
}

// 0x1ce5d90
static s32 MahjanDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1ce5da0
static dds3ProcessFunc_t MahjanCalcProcess(dds3ProcessID_t *PID) {
  jmsData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  s32 MahjanStat;
  s32 MahjanErr;
  s32 v12;
  jmsSeqUnit_t *v16;
  void *Instance;
  s32 v19;
  s32 MjnFinishCnt;
  dds3ProcessID_t *v22;
  jmsData_t *v24;
  u8 *pMsgData;
  jmsData_t *v26;
  jmsSeqUnit_t *p_pSeqUnit;
  jmsSeqUnit_t *v29;
  jmsSeqUnit_t *v30;
  jmsData_t *pData;
  dds3ProcessID_t *id;

  id = PID;
  pData = 0;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  SeqHandle = ProcessData->SeqHandle;
  pData = ProcessData;
  v7 = id;
  v8 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v7);
  if (!v8)
  {
    MahjanStat = ProcessData->MahjanStat;
    MahjanErr = ProcessData->MahjanErr;
    if (MahjanErr)
    {
      if (MahjanStat == 1)
      {
        if (!fclChkMessage())
        {
          v16 = jmsSeqUnit[1];
          ProcessData->pSeqUnit = v16;
          jmsSeqUnit[1]->Stat = LOWORD(jmsSeqUnit[1]->Stat) | 0x20000;
          ProcessData->MahjanStat = 0;
        }
      }
      else if (!MahjanStat)
      {
        switch (MahjanErr)
        {
          case 1:
            v12 = 0;
            goto LABEL_19;
          case 2:
            v12 = 1;
            goto LABEL_19;
          case 3:
            v12 = 2;
            goto LABEL_19;
          case 4:
            v12 = 3;
LABEL_19:
            fclStartMessage(v12);
            break;
          default:
            break;
        }
LABEL_24:
        ++ProcessData->MahjanStat;
      }
    }
    else
    {
      switch (MahjanStat)
      {
        case 0:
          dds3FadeOut(0, 0, 0, 0x1Eu);
          goto LABEL_24;
        case 1:
          if (dds3FadeCheck())
            return v8;
          ProcessEnd();
          jmsModelFree(pData);
          jmsFreeBgModel(pData);
          fclDestroyMessage();
          goto LABEL_68;
        case 2:
          if (!evtCheckProcess())
          {
            Instance = get_Instance(0);
            ItfButtonGuideActive(Instance, 0, 0);
            Start();
            v19 = ProcessData->MahjanStat;
            ProcessData->MjnFinishCnt = 0;
            ProcessData->MahjanStat = v19 + 1;
          }
          return v8;
        case 3:
          if (gMjnRun)
            return v8;
          MjnFinishCnt = ProcessData->MjnFinishCnt;
          if (MjnFinishCnt <= 10)
          {
            ProcessData->MjnFinishCnt = MjnFinishCnt + 1;
          }
          else
          {
            ProcessData->Flag &= 0xFFFFFCFF;
            ProcessData->BgmNo = 16;
            jmsBgmLoad(pData);
LABEL_68:
            ++pData->MahjanStat;
          }
          break;
        case 4:
          if (!jmsBgmPlay(pData))
            return v8;
          goto LABEL_68;
        case 5:
          if (jmsModelLoad(pData))
            return v8;
          v22 = id;
          jmsLoadBgModel(v22, pData);
          goto LABEL_68;
        case 6:
          if (jmsCheckBgModel(pData))
          {
            ProcessStart(jmsMenu);
            v24 = pData;
            jmsAddTalkMenu(v24);
            pMsgData = pData->pMsgData;
            fclInitMessage(&pMsgData->obj);
            dds3FadeIn(0, 0, 0, 0x1Eu);
            v26 = pData;
            p_pSeqUnit = &v26->pSeqUnit;
            v29 = jmsSeqUnit;
            v30 = v29[1];
            p_pSeqUnit = v30;
            v29[1]->Stat = LOWORD(v29[1]->Stat) | 0x20000;
            pData->MahjanStat = 0;
          }
          return v8;
        default:
          return v8;
      }
    }
  }
  return v8;
}

// 0x1ce6430
static dds3ProcessFunc_t MahjanDrawProcess(dds3ProcessID_t *PID) {
  jmsData_t *ProcessData;
  dds3ProcessID_t *v8;
  jmsSeqUnit_t *pSeqUnit;
  s64 Stat;
  jmsData_t *pData;
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
  DrawModel_M(pData, (s32)jmsData_t);
  v8 = id;
  if (!v8)
    return 0;
  pSeqUnit = ProcessData->pSeqUnit;
  if (!pSeqUnit)
    return 0;
  Stat = pSeqUnit->Stat;
  if ((Stat & 0x500000) != 0x100000)
    return 0;
  if ((Stat & 0x200000) != 0)
    return pSeqUnit->pDraw;
  if ((Stat & 1) == 0)
    return 0;
  pSeqUnit->Stat = Stat | 0x400000;
  (pSeqUnit->pDraw->invoke_impl)(pSeqUnit->pDraw->method_code, v8, pSeqUnit->pDraw->method);
  ProcessData->pSeqUnit->Stat &= ~0x400000u;
  return 0;
}

// 0x1ce6760
static dds3ProcessFunc_t MahjanUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (LODWORD(ProcessData[11].klass))
  {
    fclUpdateMessage();
  }
  monitor = ProcessData[1].monitor;
  v7 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v7);
}

// 0x1ce68c0
static s32 KaminInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  u8 *monitor;
  dds3ProcessID_t *started;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[13].monitor;
  started = scrStartScript2(1, monitor, 0, 1);
  ProcessData[14].klass = started;
  return 1;
}

// 0x1ce69f0
static s32 KaminDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1ce6a00
static dds3ProcessFunc_t KaminCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  Il2CppObject *v6;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v8;
  dds3ProcessFunc_t v9;
  dds3ProcessFunc_t v10;
  Il2CppObject *v11;
  dds3ProcessID_t *v12;
  Il2CppClass *klass;
  Il2CppClass *v18;
  dds3ProcessID_t *id;
  dds3ProcessID_t *v21;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v6 = ProcessData + 2;
  monitor = ProcessData[1].monitor;
  v8 = id;
  v9 = jmsSeqChange(monitor, &ProcessData[2], 0, v8);
  v10 = v9;
  if (v9)
  {
    return v10;
  }
  klass = ProcessData[14].klass;
  v11 = ProcessData + 14;
  v12 = klass;
  if (!klass)
  {
    v18 = jmsSeqUnit[1];
    v6->klass = v18;
    jmsSeqUnit[1]->Stat = LOWORD(jmsSeqUnit[1]->Stat) | 0x20000;
    return v10;
  }
  v21 = v12;
  goto LABEL_18;
  if (dds3GetProcessStat(v21) == 3)
  {
LABEL_31:
    v11->klass = 0;
    return v10;
  }
  goto LABEL_28;
LABEL_18:
  if (dds3GetProcessStat(v21) == 3)
    goto LABEL_31;
LABEL_28:
  if (!dds3GetProcessStat(v21))
    goto LABEL_31;
  return v10;
}

// 0x1ce6d60
static dds3ProcessFunc_t KaminDrawProcess(dds3ProcessID_t *PID) {
  jmsData_t *ProcessData;
  dds3ProcessID_t *v6;
  jmsSeqUnit_t *pSeqUnit;
  s64 Stat;
  dds3ProcessFunc_t result;
  jmsData_t *pData;
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
  DrawModel(&pData, -1);
  v6 = id;
  if (!v6)
    return 0;
  pSeqUnit = ProcessData->pSeqUnit;
  if (!pSeqUnit)
    return 0;
  Stat = pSeqUnit->Stat;
  if ((Stat & 0x500000) != 0x100000)
    return 0;
  if ((Stat & 0x200000) != 0)
  {
    result = pSeqUnit->pDraw;
  }
  else
  {
    if ((Stat & 1) != 0)
    {
      pSeqUnit->Stat = Stat | 0x400000;
      (pSeqUnit->pDraw->invoke_impl)(pSeqUnit->pDraw->method_code, v6, pSeqUnit->pDraw->method);
      ProcessData->pSeqUnit->Stat &= ~0x400000u;
    }
    return 0;
  }
  return result;
}

// 0x1ce6fb0
static dds3ProcessFunc_t KaminUpdateProcess(dds3ProcessID_t *PID) {
  dds3ProcessFunc_t result;
  s64 naturalAligment;
  Il2CppObject **p_m_target;
  jmsSeqHandle_t *invoke_impl;
  dds3ProcessID_t *v8;
  dds3ProcessID_t *id;

  id = PID;
  result = (dds3ProcessFunc_t)dds3GetProcessData(id);
  if (result)
  {
    if (result->klass->_2.naturalAligment < (u32)naturalAligment || result->klass->_2.typeHierarchy[naturalAligment - 1] != jmsData_t)
    {
      goto LABEL_15;
    }
  }
  p_m_target = &result->m_target;
  invoke_impl = result->invoke_impl;
  v8 = id;
  result = jmsSeqChange(invoke_impl, p_m_target, 2, id);
  if (!result)
    return result;
  if (result->klass != dds3ProcessFunc_t)
LABEL_15:
  return result;
}

// 0x1ce7110
static s32 DBOOKInit(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  return 1;
}

// 0x1ce7190
static s32 DBOOKDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1ce71a0
static dds3ProcessFunc_t DBOOKCalcProcess(dds3ProcessID_t *PID) {
  jmsData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  s32 v10;
  jmsSeqUnit_t *v15;
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
  SeqHandle = ProcessData->SeqHandle;
  v7 = id;
  v8 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v7);
  if (!v8)
  {
    switch (ProcessData->DBOOKstep)
    {
      case 0:
        dds3FadeOut(0, 0, 0, 0x1Eu);
        goto LABEL_31;
      case 1:
        if (dds3FadeCheck())
          return v8;
        goto LABEL_31;
      case 2:
        jmsSetBgDisp(0);
        basic = dds3GetActiveScene();
        dds3SceneBasicVisible(basic, 0);
        ProcessEnd();
        ProcessStart(0);
LABEL_31:
        v10 = ProcessData->DBOOKstep + 1;
        goto LABEL_32;
      case 3:
        if (ProcessCheck())
          return v8;
        basic = dds3GetActiveScene();
        dds3SceneBasicVisible(basic, 1);
        ProcessStart(jmsMenu);
        jmsAddTalkMenu(ProcessData);
        jmsSetBgDisp(1);
        dds3FadeIn(0, 0, 0, 0x1Eu);
        v15 = jmsSeqUnit[1];
        ProcessData->pSeqUnit = v15;
        v10 = 0;
        jmsSeqUnit[1]->Stat = LOWORD(jmsSeqUnit[1]->Stat) | 0x20000;
LABEL_32:
        ProcessData->DBOOKstep = v10;
        break;
      default:
        return v8;
    }
  }
  return v8;
}

// 0x1ce75c0
static dds3ProcessFunc_t DBOOKDrawProcess(dds3ProcessID_t *PID) {
  jmsData_t *ProcessData;
  s32 DBOOKstep;
  dds3ProcessID_t *v8;
  jmsSeqUnit_t *pSeqUnit;
  s64 Stat;
  jmsData_t *pData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  DBOOKstep = ProcessData->DBOOKstep;
  pData = ProcessData;
  if (DBOOKstep <= 1)
  {
    DrawModel(&pData, -1);
    v8 = id;
LABEL_11:
    goto LABEL_12;
  }
  else
  {
    v8 = id;
    goto LABEL_11;
  }
LABEL_12:
  if (!v8)
    return 0;
  pSeqUnit = ProcessData->pSeqUnit;
  if (!pSeqUnit)
    return 0;
  Stat = pSeqUnit->Stat;
  if ((Stat & 0x500000) != 0x100000)
    return 0;
  if ((Stat & 0x200000) != 0)
    return pSeqUnit->pDraw;
  if ((Stat & 1) == 0)
    return 0;
  pSeqUnit->Stat = Stat | 0x400000;
  (pSeqUnit->pDraw->invoke_impl)(pSeqUnit->pDraw->method_code, v8, pSeqUnit->pDraw->method);
  ProcessData->pSeqUnit->Stat &= ~0x400000u;
  return 0;
}

// 0x1ce77e0
static dds3ProcessFunc_t DBOOKUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
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
  return jmsSeqChange(monitor, &ProcessData[2], 2, v7);
}

// 0x1ce7900
static s32 CAMPInit(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  fclDestroyMessage();
  return 1;
}

// 0x1ce79e0
static s32 CAMPDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1ce79f0
static dds3ProcessFunc_t CAMPCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  s32 v10;
  Il2CppObject *v16;
  dds3ProcessID_t *v17;
  s64 klass_high;
  jmsSeqUnit_t *jmsSeqUnit_local;
  Il2CppClass **v21;
  Il2CppClass *v22;
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
  monitor = ProcessData[1].monitor;
  v7 = id;
  v8 = jmsSeqChange(monitor, &ProcessData[2], 0, v7);
  if (!v8)
  {
    switch (HIDWORD(ProcessData[14].monitor))
    {
      case 0:
        SetTitleAnim(jmsUIctrlSub, 2, 0);
        SetBackAnim(jmsUIctrlSub, 2, 0);
        AnimSet(jmsUIctrlSub, 2, 0);
        jmsUiCampCheck = 1;
        MenuProcessStop();
        dds3FadeOut(0, 0, 0, 0x1Eu);
        v8 = 0;
        v10 = 1;
        goto LABEL_90;
      case 1:
        v8 = 0;
        if (dds3FadeCheck())
          return v8;
        jmsSetBgDisp(0);
        basic = dds3GetActiveScene();
        dds3SceneBasicVisible(basic, 0);
        v8 = 0;
        v10 = 2;
        goto LABEL_90;
      case 2:
        cmpProcessStartEx(0);
        goto LABEL_32;
      case 3:
        v8 = 0;
        if (cmpProcessCheck())
          return v8;
        v8 = 0;
        v10 = 4;
        goto LABEL_90;
      case 4:
        if (g_endmode)
        {
          if (g_endmode == 2)
            goto LABEL_103;
          fmProcTrigSequence(1);
          v8 = 0;
          v10 = 5;
          goto LABEL_90;
        }
        jmsUiCampCheck = 0;
        MenuProcessRestart();
        v16 = ProcessData[11].monitor;
        fclInitMessage(v16);
        SetTitleAnim(jmsUIctrlSub, 1, 0);
        SetBackAnim(jmsUIctrlSub, 1, 0);
        AnimSet(jmsUIctrlSub, 3, 0);
        v17 = ProcessData[2].monitor;
        evtSetFrame(v17, 0);
        basic = dds3GetActiveScene();
        dds3SceneBasicVisible(basic, 1);
        jmsSetBgDisp(1);
        dds3FadeIn(0, 0, 0, 0x1Eu);
        klass_high = SHIDWORD(ProcessData[16].klass);
        jmsSeqUnit_local = jmsSeqUnit;
        v21 = &jmsSeqUnit_local->obj.klass + klass_high;
        v22 = v21[4];
        ProcessData[2].klass = v22;
        v8 = 0;
        v21[4]->_1.name = (LOWORD(v21[4]->_1.name) | 0x20000);
        HIDWORD(ProcessData[14].monitor) = 0;
        HIDWORD(ProcessData[16].klass) = 0;
        return v8;
      case 5:
        v8 = 0;
        if (fmProcessChk())
          return v8;
        if (gslExitType)
        {
          basic = dds3GetActiveScene();
          dds3SceneBasicVisible(basic, 0);
          cmpProcessStartEx(1);
          dds3FadeIn2(8u);
LABEL_32:
          v8 = 0;
          v10 = 3;
LABEL_90:
          HIDWORD(ProcessData[14].monitor) = v10;
        }
        else
        {
          basic = dds3GetActiveScene();
          dds3SceneBasicVisible(basic, 0);
          if (GBWK->GameFileInfo->newfile != 1)
            dds3AdminiCallSequence4(8, 0, 0, 0);
LABEL_103:
          gCallFromSubMenu = 1;
          v8 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
          _ctor(v8, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
        }
        break;
      default:
        return 0;
    }
  }
  return v8;
}

// 0x1ce8440
static dds3ProcessFunc_t CAMPDrawProcess(dds3ProcessID_t *PID) {
  jmsData_t *ProcessData;
  s32 CAMPstep;
  dds3ProcessID_t *v8;
  jmsSeqUnit_t *pSeqUnit;
  s64 Stat;
  jmsData_t *pData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  CAMPstep = ProcessData->CAMPstep;
  pData = ProcessData;
  if (CAMPstep <= 1)
  {
    DrawModel(&pData, -1);
    v8 = id;
LABEL_11:
    goto LABEL_12;
  }
  else
  {
    v8 = id;
    goto LABEL_11;
  }
LABEL_12:
  if (!v8)
    return 0;
  pSeqUnit = ProcessData->pSeqUnit;
  if (!pSeqUnit)
    return 0;
  Stat = pSeqUnit->Stat;
  if ((Stat & 0x500000) != 0x100000)
    return 0;
  if ((Stat & 0x200000) != 0)
    return pSeqUnit->pDraw;
  if ((Stat & 1) == 0)
    return 0;
  pSeqUnit->Stat = Stat | 0x400000;
  (pSeqUnit->pDraw->invoke_impl)(pSeqUnit->pDraw->method_code, v8, pSeqUnit->pDraw->method);
  ProcessData->pSeqUnit->Stat &= ~0x400000u;
  return 0;
}

// 0x1ce8660
static dds3ProcessFunc_t CAMPUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
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
  return jmsSeqChange(monitor, &ProcessData[2], 2, v7);
}

// 0x1ce8780
static s32 DLCInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *Instance;
  Il2CppObject *monitor;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  Instance = get_Instance(0);
  ItfButtonGuideSet(Instance, 0, 0);
  if (!ProcessData)
  monitor = ProcessData[11].monitor;
  fclInitMessage(monitor);
  LODWORD(ProcessData[19].monitor) = 0;
  *(_OWORD *)&ProcessData[18].monitor = xmmword_3CFDF20;
  DLC_ItemChack(ProcessData);
  return 1;
}

// 0x1ce91b0
static s32 DLCDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1ce91c0
static dds3ProcessFunc_t DLCCalcProcess(dds3ProcessID_t *PID) {
  jmsData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  s32 dlcState;
  dds3ProcessID_t *v11;
  s64 dlc_itemNum1;
  void *Instance;
  jmsSeqUnit_t *v19;
  s32 v20;
  s64 dlc_itemNum2;
  s32 v22;
  s64 dlc_itemNum3;
  s32 v24;
  s32 v25;
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
  v7 = id;
  v8 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v7);
  if (v8)
    return v8;
  dlcState = ProcessData->dlcState;
  if (dlcState)
    goto LABEL_18;
  v11 = id;
  LogStart(v11);
  scrEventSkipMsg1st();
  dlcState = ProcessData->dlcState;
  if (dlcState)
  {
LABEL_18:
    if (dlcState != 1)
      return v8;
    if (fclChkMessage())
      return v8;
    if (DLC_ItemChack(ProcessData))
    {
      ProcessData->dlcState = 0;
      return 0;
    }
    if (IsBuyItem())
    {
LABEL_34:
      Instance = get_Instance(0);
      ItfButtonGuideSet(Instance, 1, 0);
      v19 = jmsSeqUnit[1];
      ProcessData->pSeqUnit = v19;
      jmsSeqUnit[1]->Stat = LOWORD(jmsSeqUnit[1]->Stat) | 0x20000;
      ProcessData->MahjanStat = 0;
      scrEventSkipEnd(0, 0);
      scrLogEnd(0);
      scrEndEventSkipMsg1st();
      return 0;
    }
    jmsDisableSelect(8);
    goto LABEL_34;
  }
  switch (ProcessData->dlc_mes_No)
  {
    case 1:
      fclStartMessage(4);
      dlc_itemNum1 = ProcessData->dlc_itemNum1;
      ProcessData->dlcitem_pac1[dlc_itemNum1]->_Count = 0;
      ProcessData->dlc_itemNum1 = dlc_itemNum1 + 1;
      break;
    case 2:
      v20 = 5;
      goto LABEL_52;
    case 3:
      v20 = 6;
LABEL_52:
      fclStartMessage(v20);
      ++ProcessData->dlc_itemNum1;
      break;
    case 4:
      fclStartMessage(7);
      dlc_itemNum2 = ProcessData->dlc_itemNum2;
      ProcessData->dlcitem_pac2[dlc_itemNum2]->_Count = 0;
      ProcessData->dlc_itemNum2 = dlc_itemNum2 + 1;
      break;
    case 5:
      v22 = 8;
      goto LABEL_62;
    case 6:
      v22 = 9;
LABEL_62:
      fclStartMessage(v22);
      ++ProcessData->dlc_itemNum2;
      break;
    case 7:
      fclStartMessage(10);
      dlc_itemNum3 = ProcessData->dlc_itemNum3;
      ProcessData->dlcitem_pac3[dlc_itemNum3]->_Count = 0;
      v24 = dlc_itemNum3 + 1;
      goto LABEL_73;
    case 8:
      v25 = 11;
      goto LABEL_72;
    case 9:
      v25 = 12;
LABEL_72:
      fclStartMessage(v25);
      v24 = ProcessData->dlc_itemNum3 + 1;
LABEL_73:
      ProcessData->dlc_itemNum3 = v24;
      break;
    default:
      break;
  }
  ++ProcessData->dlcState;
  return 0;
}

// 0x1ce9760
static dds3ProcessFunc_t DLCDrawProcess(dds3ProcessID_t *PID) {
  jmsData_t *ProcessData;
  dds3ProcessID_t *v6;
  jmsSeqUnit_t *pSeqUnit;
  s64 Stat;
  jmsData_t *pData;
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
  DrawModel(&pData, -1);
  v6 = id;
  if (!v6)
    return 0;
  pSeqUnit = ProcessData->pSeqUnit;
  if (!pSeqUnit)
    return 0;
  Stat = pSeqUnit->Stat;
  if ((Stat & 0x500000) != 0x100000)
    return 0;
  if ((Stat & 0x200000) != 0)
    return pSeqUnit->pDraw;
  if ((Stat & 1) == 0)
    return 0;
  pSeqUnit->Stat = Stat | 0x400000;
  (pSeqUnit->pDraw->invoke_impl)(pSeqUnit->pDraw->method_code, v6, pSeqUnit->pDraw->method);
  ProcessData->pSeqUnit->Stat &= ~0x400000u;
  return 0;
}

// 0x1ce9960
static dds3ProcessFunc_t DLCUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (HIDWORD(ProcessData[18].monitor))
  {
    fclUpdateMessage();
  }
  monitor = ProcessData[1].monitor;
  v7 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v7);
}

// 0x1ce8910
static bool DLC_ItemChack(jmsData_t *_data) {
  DlcItem_t *dlcitem_pac1;
  s32 dlc_itemNum1;
  s32 max_length;
  s64 i;
  s64 v7;
  s32 v8;
  s32 ItemMaxNum;
  s64 v11;
  s32 v12;
  s64 name_low;
  s32 v14;
  s32 v15;
  DlcItem_t *dlcitem_pac2;
  s32 dlc_itemNum2;
  s32 v18;
  s64 v19;
  s32 v20;
  s32 v21;
  s64 v23;
  s32 v24;
  s64 v25;
  s32 v26;
  s32 v27;
  DlcItem_t *dlcitem_pac3;
  s32 dlc_itemNum3;
  s32 v30;
  s64 v31;
  s32 v32;
  s32 v33;
  s64 v35;
  s32 v36;
  s64 v37;
  s32 v38;
  s32 v39;
  bool v40;
  DlcItem_t *v41;
  s32 Count;
  s32 v43;
  s32 v44;
  DlcItem_t *v45;
  s64 v46;
  DlcItem_t *v47;
  s32 v48;
  s32 v49;
  s32 v50;
  DlcItem_t *v51;
  s32 v52;
  s32 v53;
  s32 v54;
  s64 v55;
  s32 v56;
  DlcItem_t *v57;
  s32 ItemID;
  s32 v61;
  DlcItem_t *v62;
  s32 v63;
  s32 v64;
  DlcItem_t *v65;
  u32 v67;
  s32 v68;
  s32 v69;
  s32 v70;
  DlcItem_t *v71;
  u32 v73;
  s32 v74;

  dlcitem_pac1 = data->dlcitem_pac1;
  dlc_itemNum1 = data->dlc_itemNum1;
  max_length = dlcitem_pac1->max_length;
  if (dlc_itemNum1 < max_length)
  {
    i = 8 * dlc_itemNum1 + 32;
    while (1)
    {
      v7 = *(s64 *)((char *)&dlcitem_pac1->obj.klass + i);
      v8 = *(u32 *)(v7 + 16);
      if (v8)
      {
        if (*(u32 *)(v7 + 20))
          break;
      }
      ++dlc_itemNum1;
      i += 8;
      if (max_length == dlc_itemNum1)
        goto LABEL_16;
    }
    ItemMaxNum = datGetItemMaxNum(v8);
    v11 = *(s64 *)((char *)&data->dlcitem_pac1->obj.klass + i);
    v12 = *(u32 *)(v11 + 20);
    name_low = *(s32 *)(v11 + 16);
    v14 = GBWK->player->item[name_low];
    if (v12 + v14 > ItemMaxNum)
    {
      if (ItemMaxNum == v14)
      {
        data->dlc_itemNum1 = dlc_itemNum1;
        data->dlc_mes_No = 3;
        v15 = name_low;
LABEL_73:
        itfSetTextValue(0, 3, v15, 0);
        v62 = data->dlcitem_pac1;
LABEL_92:
        v55 = (s64)v62 + i;
        goto LABEL_93;
      }
      v56 = ItemMaxNum - v14;
      data->dlc_itemNum1 = dlc_itemNum1;
      data->dlc_mes_No = 2;
      datAddItem(name_low, v56);
      v57 = data->dlcitem_pac1;
      ItemID = v57[data->dlc_itemNum1]->_ItemID;
      HIDWORD((*(Il2CppClass **)((char *)&v57->obj.klass + i))->_1.name) -= v56;
      DelBuyItem(0, ItemID, v56);
      v61 = data->dlcitem_pac1[data->dlc_itemNum1]->_ItemID;
      v15 = v61;
      goto LABEL_73;
    }
    data->dlc_itemNum1 = dlc_itemNum1;
    data->dlc_mes_No = 1;
    datAddItem(name_low, v12);
    v41 = data->dlcitem_pac1[data->dlc_itemNum1];
    v43 = v41->_ItemID;
    Count = v41->_Count;
    DelBuyItem(0, v43, Count);
    v44 = data->dlcitem_pac1[data->dlc_itemNum1]->_ItemID;
    itfSetTextValue(0, 3, v44, 0);
    v45 = data->dlcitem_pac1;
    v46 = data->dlc_itemNum1;
LABEL_64:
    v55 = &v45[v46];
LABEL_93:
    v40 = 1;
    itfSetTextValue(1, 0, *(u32 *)(*(u64 *)v55 + 20), 0);
    return v40;
  }
LABEL_16:
  dlcitem_pac2 = data->dlcitem_pac2;
  dlc_itemNum2 = data->dlc_itemNum2;
  v18 = dlcitem_pac2->max_length;
  if (dlc_itemNum2 < v18)
  {
    i = 8 * dlc_itemNum2 + 32;
    while (1)
    {
      v19 = *(s64 *)((char *)&dlcitem_pac2->obj.klass + i);
      v20 = *(u32 *)(v19 + 16);
      if (v20)
      {
        if (*(u32 *)(v19 + 20))
          break;
      }
      ++dlc_itemNum2;
      i += 8;
      if (v18 == dlc_itemNum2)
        goto LABEL_29;
    }
    v21 = datGetItemMaxNum(v20);
    v23 = *(s64 *)((char *)&data->dlcitem_pac2->obj.klass + i);
    v24 = *(u32 *)(v23 + 20);
    v25 = *(s32 *)(v23 + 16);
    v26 = GBWK->player->item[v25];
    if (v24 + v26 <= v21)
    {
      data->dlc_itemNum2 = dlc_itemNum2;
      data->dlc_mes_No = 4;
      DelBuyItem(1, v25, v24);
      v47 = data->dlcitem_pac2[data->dlc_itemNum2];
      v48 = v47->_ItemID;
      v49 = v47->_Count;
      datAddItem(v48, v49);
      v50 = data->dlcitem_pac2[data->dlc_itemNum2]->_ItemID;
      itfSetTextValue(0, 3, v50, 0);
      v45 = data->dlcitem_pac2;
      v46 = data->dlc_itemNum2;
      goto LABEL_64;
    }
    if (v21 == v26)
    {
      data->dlc_itemNum2 = dlc_itemNum2;
      data->dlc_mes_No = 6;
      v27 = v25;
LABEL_82:
      itfSetTextValue(0, 3, v27, 0);
      v62 = data->dlcitem_pac2;
      goto LABEL_92;
    }
    v63 = v21 - v26;
    data->dlc_itemNum2 = dlc_itemNum2;
    data->dlc_mes_No = 5;
    datAddItem(v25, v63);
    v64 = data->dlcitem_pac2[data->dlc_itemNum2]->_ItemID;
    DelBuyItem(1, v64, v63);
    v65 = data->dlcitem_pac2;
    v68 = v65[data->dlc_itemNum2]->_ItemID;
    HIDWORD((*(Il2CppClass **)((char *)&v65->obj.klass + i))->_1.name) -= v63;
    if (!v67)
    v27 = v68;
    goto LABEL_82;
  }
LABEL_29:
  dlcitem_pac3 = data->dlcitem_pac3;
  dlc_itemNum3 = data->dlc_itemNum3;
  v30 = dlcitem_pac3->max_length;
  if (dlc_itemNum3 < v30)
  {
    for (i = 8 * dlc_itemNum3 + 32; ; i += 8)
    {
      v31 = *(s64 *)((char *)&dlcitem_pac3->obj.klass + i);
      v32 = *(u32 *)(v31 + 16);
      if (v32)
      {
        if (*(u32 *)(v31 + 20))
          break;
      }
      if (v30 == ++dlc_itemNum3)
        return 0;
    }
    v33 = datGetItemMaxNum(v32);
    v35 = *(s64 *)((char *)&data->dlcitem_pac3->obj.klass + i);
    v36 = *(u32 *)(v35 + 20);
    v37 = *(s32 *)(v35 + 16);
    v38 = GBWK->player->item[v37];
    if (v36 + v38 <= v33)
    {
      data->dlc_itemNum3 = dlc_itemNum3;
      data->dlc_mes_No = 7;
      DelBuyItem(2, v37, v36);
      v51 = data->dlcitem_pac3[data->dlc_itemNum3];
      v52 = v51->_ItemID;
      v53 = v51->_Count;
      datAddItem(v52, v53);
      v54 = data->dlcitem_pac3[data->dlc_itemNum3]->_ItemID;
      itfSetTextValue(0, 3, v54, 0);
      v45 = data->dlcitem_pac3;
      v46 = data->dlc_itemNum3;
      goto LABEL_64;
    }
    if (v33 == v38)
    {
      data->dlc_itemNum3 = dlc_itemNum3;
      data->dlc_mes_No = 9;
      v39 = v37;
LABEL_91:
      itfSetTextValue(0, 3, v39, 0);
      v62 = data->dlcitem_pac3;
      goto LABEL_92;
    }
    v69 = v33 - v38;
    data->dlc_itemNum3 = dlc_itemNum3;
    data->dlc_mes_No = 8;
    datAddItem(v37, v69);
    v70 = data->dlcitem_pac3[data->dlc_itemNum3]->_ItemID;
    DelBuyItem(2, v70, v69);
    v71 = data->dlcitem_pac3;
    v74 = v71[data->dlc_itemNum3]->_ItemID;
    HIDWORD((*(Il2CppClass **)((char *)&v71->obj.klass + i))->_1.name) -= v69;
    if (!v73)
    v39 = v74;
    goto LABEL_91;
  }
  return 0;
}

// 0x1ce6c90
s32 jmsCheckScrRun(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  if (dds3GetProcessStat(id) == 3)
    return 0;
  return dds3GetProcessStat(id) != 0;
}

// 0x1ce1b20
static s32 ScrControl(dds3ProcessID_t *PID) {
  jmsData_t *ProcessData;
  dds3ProcessID_t *Evt2ScrPID;
  dds3ProcessID_t *ScrPID;
  s32 ScrReq;
  s32 v10;
  dds3ProcessID_t *p_Evt2ScrPID;
  dds3ModelHandle_t *Model;
  s64 v13;
  dds3ModelHandle_t *v14;
  s32 ModelDefaultMotion;
  u8 *pScrData;
  dds3ProcessID_t *started;
  jmsData_t *pData;
  dds3ProcessID_t *id;
  dds3ProcessID_t *v21;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  Evt2ScrPID = ProcessData->Evt2ScrPID;
  pData = ProcessData;
  if (Evt2ScrPID)
  {
    v21 = Evt2ScrPID;
    if (dds3GetProcessStat(v21) == 3)
      goto LABEL_31;
    if (!dds3GetProcessStat(v21))
      goto LABEL_31;
    return 1;
LABEL_31:
    if ((ProcessData->Flag & 0x1400) == 0x400)
    {
      jmsBgmLoad(pData);
      if (!jmsBgmPlay(pData))
        return 1;
      ProcessData = pData;
    }
    ProcessData->Evt2ScrPID = 0;
    p_Evt2ScrPID = &ProcessData->Evt2ScrPID;
    goto LABEL_53;
  }
  ScrPID = ProcessData->ScrPID;
  if (ScrPID)
  {
    v21 = ProcessData->ScrPID;
    if (dds3GetProcessStat(v21) == 3)
      goto LABEL_43;
    goto LABEL_40;
    if (dds3GetProcessStat(v21) == 3)
    {
LABEL_43:
      Model = ProcessData->Model;
      if (SLODWORD(Model->max_length) >= 1)
      {
        v13 = 0;
        do
        {
          v14 = Model[v13];
          if (v14)
          {
            ModelDefaultMotion = jmsGetModelDefaultMotion(v13, ProcessData);
            mdlSmoothLoopMotion(v14, 0, ModelDefaultMotion, 15.0, 15.0, 0.0);
            Model = ProcessData->Model;
          }
          ++v13;
        }
        while (v13 < SLODWORD(Model->max_length));
      }
      ProcessData->ScrPID = 0;
      p_Evt2ScrPID = &ProcessData->ScrPID;
LABEL_53:
      return 1;
    }
LABEL_40:
    if (dds3GetProcessStat(v21))
      return 1;
    goto LABEL_43;
  }
  ScrReq = ProcessData->ScrReq;
  if (ScrReq < 0 || ProcessData->ExitFlag)
    return 0;
  ProcessData->MenuFade = 1;
  pScrData = ProcessData->pScrData;
  v10 = 1;
  started = scrStartScript2(1, pScrData, ScrReq, 1);
  ProcessData->ScrPID = started;
  ProcessData->ScrReq = -1;
  return v10;
}

// 0x1ce9ac0
dds3ProcessFunc_t jmsRootWaitCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  Il2CppObject *v6;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v8;
  dds3ProcessFunc_t result;
  bool v12;
  s32 monitor_high;
  dds3ProcessID_t *v15;
  Il2CppClass *v19;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v6 = ProcessData + 2;
  monitor = ProcessData[1].monitor;
  v8 = id;
  result = jmsSeqChange(ProcessData[1].monitor, &ProcessData[2], 0, id);
  if (result)
    return result;
  v12 = dds3FadeCheck();
  result = 0;
  if (v12)
    return result;
  monitor_high = HIDWORD(ProcessData[8].monitor);
  v15 = id;
  if (monitor_high)
  {
    return EndProcess(v15);
  }
  else
  {
    if (ScrControl(v15))
    {
      return 0;
    }
    else
    {
      datPartyRecovery();
      datAddMag(300);
      v19 = jmsSeqUnit[1];
      v6->klass = v19;
      jmsSeqUnit[1]->Stat = LOWORD(jmsSeqUnit[1]->Stat);
      return 0;
    }
  }
}

// 0x1cea070
dds3ProcessFunc_t jmsRootWaitDrawProcess(dds3ProcessID_t *PID) {
  jmsData_t *ProcessData;
  dds3ProcessID_t *v6;
  jmsSeqUnit_t *pSeqUnit;
  s64 Stat;
  jmsData_t *pData;
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
  DrawModel(&pData, -1);
  v6 = id;
  if (!v6)
    return 0;
  pSeqUnit = ProcessData->pSeqUnit;
  if (!pSeqUnit)
    return 0;
  Stat = pSeqUnit->Stat;
  if ((Stat & 0x500000) != 0x100000)
    return 0;
  if ((Stat & 0x200000) != 0)
    return pSeqUnit->pDraw;
  if ((Stat & 1) == 0)
    return 0;
  pSeqUnit->Stat = Stat | 0x400000;
  (pSeqUnit->pDraw->invoke_impl)(pSeqUnit->pDraw->method_code, v6, pSeqUnit->pDraw->method);
  ProcessData->pSeqUnit->Stat &= ~0x400000u;
  return 0;
}

// 0x1cea270
dds3ProcessFunc_t jmsRootWaitUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
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
  return jmsSeqChange(monitor, &ProcessData[2], 2, v7);
}

// 0x1ce5360
static s32 CheckCyousaFilePrev(jmsData_t *pData) {
  s32 CyousaFileIndex;
  s32 v5;

  CyousaFileIndex = pData->CyousaFileIndex;
  if (CyousaFileIndex < 1)
    return 0;
  v5 = MenuFlag[CyousaFileIndex + 11];
  if (v5)
    return evtBitCheck(v5);
  return 1;
}

// 0x1ce5480
static s32 CheckCyousaFileNext(jmsData_t *pData) {
  s32 CyousaFileIndex;
  s32 v5;

  CyousaFileIndex = pData->CyousaFileIndex;
  if (CyousaFileIndex > 10)
    return 0;
  v5 = MenuFlag[CyousaFileIndex + 13];
  if (v5)
    return evtBitCheck(v5);
  return 1;
}

// 0x1cea450
static void DrawCyousaMessage(jmsData_t *pData, s32 X, s32 Y, f32 AlphaRate) {
  char *v7;
  char *LocalizeText;
  char *v10;

  v7 = jmsChosaFileMesssage[pData->CyousaFileIndex];
  LocalizeText = GetLocalizeText(v7, 0);
  v10 = GetLocalizeText(jmsCyousaFileTitle[pData->CyousaFileIndex], 0);
  ChosasyoSetMessage(jmsUIctrlSub, LocalizeText, v10, 0);
}

// 0x1ce5b50
static s32 CheckMahjanError(jmsData_t *pData) {
  s64 ModelLoadCnt;
  s32 *m_Items;

  ModelLoadCnt = (u32)pData->ModelLoadCnt;
  if ((s32)ModelLoadCnt < 1)
  {
LABEL_7:
    if (!evtBitCheck(81))
      goto LABEL_16;
    goto LABEL_12;
  }
  m_Items = pData->ModelIndex;
  while (*m_Items++)
  {
    if (!--ModelLoadCnt)
      goto LABEL_7;
  }
  NarumiIsHere = 1;
  if (evtBitCheck(81))
  {
LABEL_12:
    if (!evtBitCheck(83))
    {
      NarumiIsHere = 0;
    }
  }
LABEL_16:
  if (datGetStockDevilNums(1) > 1)
    goto LABEL_24;
  if (NarumiIsHere != 1)
    goto LABEL_24;
  return 2;
LABEL_24:
  if (datGetStockDevilNums(1) > 2)
    goto LABEL_30;
  if (NarumiIsHere)
    goto LABEL_30;
  return 2;
LABEL_30:
  if (GBWK->player->gold)
    return 0;
  else
    return 3;
}

// 0x1ce9d70
dds3ProcessFunc_t EndProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *monitor;
  dds3ProcessFunc_t v11;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v6 = id;
  if (ScrControl(id))
    return 0;
  LODWORD(ProcessData[8].monitor) = 1;
  if (HIDWORD(ProcessData[8].monitor))
  {
LABEL_14:
    monitor = ProcessData[2].monitor;
    if (monitor)
    {
      if (((s64)ProcessData[1].klass & 0x80) == 0)
      {
        evtEnd(monitor);
        LODWORD(ProcessData[1].klass) |= 0x80u;
        return 0;
      }
      if (evtCheckRun(monitor))
        return 0;
      ProcessData[2].monitor = 0;
    }
    v11 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
    _ctor(v11, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
    return v11;
  }
  if (((s64)ProcessData[1].klass & 0x40) != 0)
  {
    if (dds3FadeCheck())
      return 0;
    goto LABEL_14;
  }
  dds3FadeOut(0, 0, 0, 0x1Eu);
  LODWORD(ProcessData[1].klass) |= 0x40u;
  return 0;
}

// 0x1cea560
s32 jmsCheckNarumiIsHere(void) {
  return NarumiIsHere;
}
