#include "types.h"
#include "dds3kernelcore.h"
#include "evtbit.h"
#include "kernel.h"
#include "nwdnews.h"
#include "shpmain.h"

#define NWDNEWS_MAINPROC_NAME "nwdnews_main"
#define NWDNEWS_DRAWPROC_NAME "nwdnews_draw"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct tagNWDNEWS_WORK tagNWDNEWS_WORK;

struct tagNWDNEWS_WORK {
    dds3ProcessID_t *drawPID;
    u8 step;
    s32 flag;
    s16 count;
    f32 x;
    f32 y;
};

static dds3ProcessID_t *g_mainPID;
static char *arrNewsSprName;
static s32 nwdNewsProcess_w;
static s32 nwdNewsProcess_h;
static s32 nwdNewsImageNum;

static dds3ProcessFunc_t Process(dds3ProcessID_t *PID);
static dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *PID);
static s32 GetScene(void);
static void Release(tagNWDNEWS_WORK *wk);
static void Shutdown(dds3ProcessID_t *PID);

// 0x21afb50
static dds3ProcessFunc_t Process(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessFunc_t v7;
  void *shpUIManager_local;
  s32 v11;
  s32 v12;
  void *v13;
  Il2CppObject *Item;
  s32 monitor_high;
  s32 klass_low;
  f32 v17;
  f32 v18;
  s32 v21;
  s32 v22;
  s32 v23;
  s32 v25;
  void *v28;
  s32 v29;
  s16 v30;
  f32 v31;
  void *v32;
  f32 v33;
  void *v34;
  f32 v35;
  f32 v37;
  u32 v38;
  f32 v39;
  void *v40;
  void *v41;
  dds3ProcessID_t *id;
  sdfVector2_t v44;
  sdfVector2_t v45;
  sdfVector3_t v46;
  sdfVector3_t v47;
  sdfQuaternion_t v48;
  sdfQuaternion_t v49;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  switch (LOBYTE(ProcessData[1].monitor))
  {
    case 0:
      v7 = 0;
      if (shpCheckLoadShopUI())
      {
        shpUIManager_local = shpUIManager;
        v11 = nwdNewsImageNum - 1;
        if (v11 >= 11)
          v12 = 11;
        else
          v12 = v11;
        v13 = *(void *)(*(u64 *)&shpUIManager_local->NONCOL_POSSE + 32);
        Item = _get_Item(shpUIManager_local->NewsPaperImages, v12 & (u32)~(v12 >> 31));
        set_sprite(v13, Item, 0);
        v7 = 0;
        LOBYTE(ProcessData[1].monitor) = 1;
      }
      return v7;
    case 1:
      monitor_high = HIDWORD(ProcessData[1].monitor);
      if ((~monitor_high & 0xA) != 0)
        return 0;
      v7 = 0;
      LOWORD(ProcessData[2].klass) = 0;
      HIDWORD(ProcessData[1].monitor) = monitor_high & 0xFFFFFFF7;
      LOBYTE(ProcessData[1].monitor) = 2;
      return v7;
    case 2:
      klass_low = SLOWORD(ProcessData[2].klass);
      if (LOWORD(ProcessData[2].klass))
      {
        v17 = *((f32 *)&ProcessData[2].klass + 1) + -6.0;
        v18 = *(f32 *)&ProcessData[2].monitor + 9.0;
        *((f32 *)&ProcessData[2].klass + 1) = v17;
        *(f32 *)&ProcessData[2].monitor = v18;
        if (klass_low > 14)
        {
          v17 = *((f32 *)&ProcessData[2].klass + 1);
          v18 = *(f32 *)&ProcessData[2].monitor;
          NewsFadeIn(shpUIManager, v17, v18, 0.0, 1.0, tagNWDNEWS_WORK);
          v7 = 0;
          LOWORD(ProcessData[2].klass) = 0;
          LOBYTE(ProcessData[1].monitor) = 3;
          return v7;
        }
        v17 = *((f32 *)&ProcessData[2].klass + 1);
        v18 = *(f32 *)&ProcessData[2].monitor;
        LOWORD(klass_low) = ProcessData[2].klass;
        v31 = (s16)klass_low;
        v32 = shpUIManager;
        v33 = 15.0 - v31;
        (*(**(u64 **)(*(u64 *)&v32->NONCOL_POSSE + 32) + 680))(*(u64 *)(*(u64 *)&v32->NONCOL_POSSE + 32), *(u64 *)(**(u64 **)(*(u64 *)&v32->NONCOL_POSSE + 32) + 688), 1.0, 1.0, 1.0, v31 / 15.0);
        v44.x = v17;
        v44.y = v18;
        set_anchoredPosition(*(void *)(*(u64 *)&v32->NONCOL_POSSE + 24), v44, 0);
        v46.y = 0.0;
        v34 = *(void *)(*(u64 *)&v32->NONCOL_POSSE + 24);
        v46.z = v33 * -0.017453292;
        v46.x = 0.0;
        v48 = Internal_FromEulerRad(v46, 0);
        set_rotation(v34, v48, 0);
      }
      else
      {
        v28 = shpUIManager;
        if (!get_activeSelf(shpUIManager->NewsPaperObj, 0))
          SetActive(v28->NewsPaperObj, 1, 0);
        v29 = HIDWORD(ProcessData[1].monitor) | 4;
        *(Il2CppClass **)((char *)&ProcessData[2].klass + 4) = 0xC352000042F00000LL;
        HIDWORD(ProcessData[1].monitor) = v29;
      }
      LOWORD(v25) = ProcessData[2].klass;
      goto LABEL_53;
    case 3:
      v21 = HIDWORD(ProcessData[1].monitor);
      if ((v21 & 8) == 0)
        return 0;
      v7 = 0;
      LOWORD(ProcessData[2].klass) = 0;
      HIDWORD(ProcessData[1].monitor) = v21 & 0xFFFFFFF7;
      LOBYTE(ProcessData[1].monitor) = 4;
      return v7;
    case 4:
      v22 = SLOWORD(ProcessData[2].klass);
      if (!LOWORD(ProcessData[2].klass))
      {
        v30 = 1;
LABEL_57:
        v7 = 0;
        goto LABEL_58;
      }
      if (v22 <= 14)
      {
        v35 = *((f32 *)&ProcessData[2].klass + 1) + 6.0;
        v37 = *(f32 *)&ProcessData[2].monitor + -9.0;
        *((f32 *)&ProcessData[2].klass + 1) = v35;
        *(f32 *)&ProcessData[2].monitor = v37;
        if (!v38)
        {
          v35 = *((f32 *)&ProcessData[2].klass + 1);
          v37 = *(f32 *)&ProcessData[2].monitor;
          LOWORD(v22) = ProcessData[2].klass;
        }
        v39 = (s16)v22;
        v40 = shpUIManager;
        (*(**(u64 **)(*(u64 *)&v40->NONCOL_POSSE + 32) + 680))(*(u64 *)(*(u64 *)&v40->NONCOL_POSSE + 32), *(u64 *)(**(u64 **)(*(u64 *)&v40->NONCOL_POSSE + 32) + 688), 1.0, 1.0, 1.0, (f32)(15 - (s16)v22) / 15.0);
        v45.x = v35;
        v45.y = v37;
        set_anchoredPosition(*(void *)(*(u64 *)&v40->NONCOL_POSSE + 24), v45, 0);
        v47.y = 0.0;
        v41 = *(void *)(*(u64 *)&v40->NONCOL_POSSE + 24);
        v47.z = v39 * -0.017453292;
        v47.x = 0.0;
        v49 = Internal_FromEulerRad(v47, 0);
        set_rotation(v41, v49, 0);
        v30 = LOWORD(ProcessData[2].klass) + 1;
        goto LABEL_57;
      }
      v23 = HIDWORD(ProcessData[1].monitor);
      LOWORD(ProcessData[2].klass) = 0;
      HIDWORD(ProcessData[1].monitor) = v23 & 0xFFFFFFFB;
      LOBYTE(ProcessData[1].monitor) = 1;
      NewsSetActive(shpUIManager, 0);
      return 0;
    case 5:
      v25 = SLOWORD(ProcessData[2].klass);
      if (LOWORD(ProcessData[2].klass))
      {
        if (v25 >= 2)
        {
          v7 = 0;
          LOWORD(ProcessData[2].klass) = 0;
          LOBYTE(ProcessData[1].monitor) = 6;
          return v7;
        }
      }
      else
      {
        HIDWORD(ProcessData[1].monitor) &= ~4u;
      }
LABEL_53:
      v7 = 0;
      v30 = v25 + 1;
LABEL_58:
      LOWORD(ProcessData[2].klass) = v30;
      return v7;
    case 6:
      v7 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v7, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v7;
    default:
      return 0;
  }
}

// 0x21b02a0
static dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    return 0;
  return 0;
}

// 0x21b0380
static s32 GetScene(void) {
  if (evtBitCheck(206))
    return 12;
  if (evtBitCheck(195))
    return 11;
  if (evtBitCheck(185))
    return 10;
  if (evtBitCheck(176))
    return 9;
  if (evtBitCheck(166))
    return 8;
  if (evtBitCheck(160))
    return 7;
  if (evtBitCheck(145))
    return 6;
  if (evtBitCheck(131))
    return 5;
  if (evtBitCheck(111))
    return 4;
  if (evtBitCheck(96))
    return 3;
  if (evtBitCheck(65))
    return 2;
  return evtBitCheck(42);
}

// 0x21b04e0
void nwdLoadSprite(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  nwdNewsImageNum = GetScene();
  HIDWORD(ProcessData[1].monitor) |= 2u;
}

// 0x21b0600
void nwdCallNext(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  HIDWORD(ProcessData[1].monitor) |= 8u;
}

// 0x21b0710
static void Release(tagNWDNEWS_WORK *wk) {
  if ((wk->flag & 2) != 0)
    wk->flag &= 2u;
}

// 0x21b0730
static void Shutdown(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 monitor_high;
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
  monitor_high = HIDWORD(ProcessData[1].monitor);
  if ((monitor_high & 2) == 0)
  {
    v6 = &ProcessData[1];
    if (!dds3ExistProcess(v6))
      goto LABEL_12;
    goto LABEL_16;
  }
  HIDWORD(ProcessData[1].monitor) = monitor_high & 2;
  v6 = &ProcessData[1];
  if (!dds3ExistProcess(v6))
  {
LABEL_12:
    goto LABEL_13;
  }
LABEL_16:
  dds3KillProcess(v6, 0);
  v6 = 0;
LABEL_13:
  g_mainPID = 0;
}

// 0x21b08e0
void nwdProcessStart(void) {
  Il2CppObject *v1;
  dds3ProcessID_t *v2;
  dds3ProcessFunc_t v3;
  shutdownfuncDelegate v4;
  dds3ProcessID_t *started;
  dds3ProcessFunc_t v7;
  dds3ProcessID_t *v8;

  v1 = Allocate(tagNWDNEWS_WORK);
  v2 = Allocate(dds3ProcessID_t);
  _ctor(v2, 0);
  v1[1].klass = v2;
  _ctor(v1, 0);
  v3 = Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_nwdNews_Process__, 0);
  v4 = Allocate(shutdownfuncDelegate);
  _ctor(v4, 0, Method_Project_nwdNews_Shutdown__, 0);
  started = dds3StartProcess("nwdnews_main", 1024, 0, 0, v3, v4, v1);
  g_mainPID = started;
  v7 = Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_nwdNews_DrawProcess__, 0);
  v8 = dds3StartProcess("nwdnews_draw", 11015, 0, 0, v7, 0, v1);
  v1[1].klass = v8;
}

// 0x21b0b50
void nwdProcessEnd(void) {
  Il2CppObject *ProcessData;
  s32 monitor_high;

  if (!g_mainPID)
    return;
  if (!dds3ExistProcess(g_mainPID))
    return;
  goto LABEL_15;
LABEL_19:
  goto LABEL_21;
LABEL_15:
  ProcessData = dds3GetProcessData(g_mainPID);
  if (ProcessData)
    goto LABEL_19;
LABEL_21:
  monitor_high = HIDWORD(ProcessData[1].monitor);
  if ((monitor_high & 1) == 0)
  {
    LOWORD(ProcessData[2].klass) = 0;
    HIDWORD(ProcessData[1].monitor) = monitor_high | 1;
    LOBYTE(ProcessData[1].monitor) = 5;
  }
}

// 0x21b0d00
bool nwdProcessCheck(void) {
  if (!g_mainPID)
    return 0;
  if (dds3GetProcessStat(g_mainPID) != 3)
  {
    if (dds3GetProcessStat(g_mainPID))
    {
      return 1;
    }
  }
  g_mainPID = 0;
  return 0;
}
