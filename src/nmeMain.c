#include "types.h"
#include "buttonguide.h"
#include "dat.h"
#include "dds3kernelcore.h"
#include "fclmsg.h"
#include "itf.h"
#include "kernel.h"
#include "localize.h"
#include "nmemain.h"
#include "scr.h"

#define NME_PROCNAME "nmeProcess"
#define NME_PROCNAME_DRAW "nmeDrawProcess"

typedef struct dds3ProcessID_t dds3ProcessID_t;

static dds3ProcessFunc_t Process(dds3ProcessID_t *proc);
static void Release(dds3ProcessID_t *proc);
static dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *proc);
static void InitEdit(dds3ProcessID_t *proc);

// 0x1d8d320
static dds3ProcessFunc_t Process(dds3ProcessID_t *proc) {
  nmeWork_tag *workdata;
  s32 mode;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v8;
  s32 v13;

  workdata = proc->workdata;
  mode = workdata->mode;
  if (mode != 2)
  {
    if (mode != 1)
    {
      if (!mode)
      {
        if (Init())
        {
          v13 = 1;
LABEL_31:
          workdata->mode = v13;
          return 0;
        }
      }
      return 0;
    }
    if (!_Update(instance))
      return 0;
    EndDisp(workdata);
    v13 = 2;
    goto LABEL_31;
  }
  v6 = Update();
  if ((u32)v6 == 1)
  {
    workdata->mode = 1;
    _Return(instance);
    return 0;
  }
  v8 = 0;
  if (!(u32)v6)
  {
    nmeSetBuffer(v6);
    v8 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
    _ctor(v8, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
  }
  return v8;
}

// 0x1d8d800
static void Release(dds3ProcessID_t *proc) {
  Il2CppObject *workdata;
  dds3ProcessID_t *klass;

  workdata = proc->workdata;
  if (workdata[1].klass)
  {
    dds3KillProcess(&workdata[1], 0);
  }
  Release(Project_nmeKeyboards);
  klass = workdata[2].klass;
  itfMenuProcessEnd(klass);
  Delete(0);
  ButtonGuideDispOut();
}

// 0x1d8d970
static dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *proc) {
  return 0;
}

// 0x1d8d600
static void InitEdit(dds3ProcessID_t *proc) {

}

// 0x1d8d640
void nmeSetBuffer(dds3ProcessID_t *proc) {
  dds3GlobalWork_t *GBWK_local;
  char *v7;
  dds3GlobalWork_t *v8;
  char *v10;
  dds3GlobalWork_t *v11;

  GBWK_local = GBWK;
  v7 = mojiSave[0];
  GBWK_local->player_first = v7;
  v8 = GBWK;
  v10 = mojiSave[1];
  v8->player_family = v10;
  v11 = GBWK;
  v11->name_language = GetLanguage();
}

// 0x1d8d9b0
dds3ProcessID_t *Start(void) {
  nmeMainWork_tag *v1;
  dds3ProcessFunc_t v2;
  shutdownfuncDelegate v3;
  dds3ProcessID_t *started;
  dds3ProcessFunc_t v5;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *v8;
  dds3ProcessID_t *v9;

  if (scrIsLogSave())
  {
    scrLogEnd(0);
  }
  v1 = Allocate(nmeMainWork_tag);
  v2 = Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_nmeMain_Process__, 0);
  v3 = Allocate(shutdownfuncDelegate);
  _ctor(v3, 0, Method_Project_nmeMain_Release__, 0);
  started = dds3StartProcess("nmeProcess", 1024, 0, 0, v2, v3, v1);
  v5 = Allocate(dds3ProcessFunc_t);
  _ctor(v5, 0, Method_Project_nmeMain_DrawProcess__, 0);
  v6 = dds3StartProcess("nmeDrawProcess", 11015, 0, 0, v5, 0, v1);
  v1->proc_draw = v6;
  GetAppendix();
  v1->mode = 0;
  v8 = itfMenuProcessStart();
  v1->menuPID = v8;
  v9 = &v1->menuPID;
  itfMenuSetFlag(v9, 64, 1);
  Create(0);
  fclLoadData("nameEnd.bmd", "nameEnd", 1);
  return started;
}

// 0x1d8dca0
void Finish(dds3ProcessID_t *proc) {
  dds3ProcessID_t *id;

  id = proc;
  dds3KillProcess(id, 0);
}
