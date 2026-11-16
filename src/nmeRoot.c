#include "types.h"
#include "dds3kernelcore.h"
#include "nmeinput0.h"
#include "nmemain.h"
#include "nmeroot.h"
#include "scr.h"

// 0x1d8df20
s32 nmeScrCmd_CALL_NAME(void) {
  scrHandle_t *s_hNowpWork_local;
  dds3ProcessID_t *p_ProcessID;
  dds3ProcessID_t *ProcessID;
  u32 v10;
  s32 id;
  dds3ProcessID_t *target;

  s_hNowpWork_local = s_hNowpWork;
  if (!s_hNowpWork_local)
    return 1;
  ProcessID = s_hNowpWork_local->ProcessID;
  p_ProcessID = &s_hNowpWork_local->ProcessID;
  if (!ProcessID)
    return 1;
  IntPara = scrGetIntPara(0);
  if ((u32)IntPara == 2)
  {
    v10 = 1;
    goto LABEL_21;
  }
  if ((u32)IntPara != 1)
  {
    if ((u32)IntPara)
      return 1;
    target = Start();
    goto LABEL_23;
  }
  v10 = 0;
LABEL_21:
  target = nmeStart(v10);
LABEL_23:
  dds3LinkProcess(p_ProcessID, target);
  id = target->id;
  scrSetIntReturnValue(id);
  return 1;
}

// 0x1d8e0e0
s32 nmeScrCmd_CALL_NAME_WAIT(void) {
  s32 IntPara;
  dds3ProcessID_t *id;

  IntPara = scrGetIntPara(0);
  id = dds3SearchProcessID(IntPara);
  return !dds3ExistProcess(id);
}

// 0x1d8e190
s32 ScrCmd_GET_DREAM_COMPARE(void) {
  scrSetIntReturnValue(gCompareCount);
  return 1;
}
