#include "types.h"
#include "aw.h"
#include "aw_shieldb.h"
#include "aw_shieldb_wait.h"
#include "dds3vrf.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e50630
void Init(void) {
  ;
}

// 0x1e520a0
s32 Add(s32 _ListID, s32 acterID) {
  AW_Func v5;
  s32 v6;
  AW_WORK_t *AW;
  char *v8;

  v5 = Allocate(AW_Func);
  _ctor(v5, 0, Method_Project_AW_ShieldB_Wait_Calc__, 0);
  v6 = Add(222, 0.0, 0.0, 0.0, 0, v5, 0, 1);
  AW = GetAW(v6);
  v8 = "AW_ShieldB_Wait";
  AW->Unit_ListID = ListID;
  AW->StepIntA = acterID;
  AW->DbgStr = v8;
  return v6;
}

// 0x1e521c0
void Calc(AW_WORK_t *aWork) {
  f32 v6;
  f32 v7;
  s32 Idx;

  if (ChkPause(aWork))
    return;
  if (!aWork->Step)
  {
    v6 = aWork->StepTime + VRF_DeltaTime;
    v7 = FPS60 * 30.0;
    aWork->StepTime = v6;
    if (v6 > v7)
    {
      Add(aWork->Unit_ListID, aWork->StepIntA);
      Idx = aWork->Idx;
      DelAW(Idx, 0);
    }
  }
}
