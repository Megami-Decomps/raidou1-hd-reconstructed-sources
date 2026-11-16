#include "types.h"
#include "aw.h"
#include "aw_xatk.h"
#include "aw_xatkdebug.h"
#include "dds3vrf.h"
#include "sbtl.h"
#include "sbtlunit.h"

typedef struct AW_WORK_t AW_WORK_t;

static s32 gIDTable[1];

// 0x1e8d7c0
void Init(void) {
  ;
}

// 0x1e8d7d0
s32 Add(void) {
  AW_Func v1;
  s32 v2;
  AW_WORK_t *AW;
  char *v4;

  v1 = Allocate(AW_Func);
  _ctor(v1, 0, Method_Project_AW_XAtkDebug_Calc__, 0);
  v2 = Add(601, 0.0, 0.0, 0.0, 0, v1, 0, 4);
  AW = GetAW(v2);
  v4 = "AW_XAtkDebug";
  AW->StepIntA = 0;
  AW->DbgStr = v4;
  return v2;
}

// 0x1e8d8d0
void Calc(AW_WORK_t *aWork) {
  f32 v6;
  SBTLUNIT_LISTWORK *other_List2;
  SBTLUNIT_LISTWORK *p_other_List2;
  SBATTLE_WORK *wk_local;
  SBTLUNIT_LISTWORK *TargetList_MASK;
  SBTLUNIT_LISTWORK *v13;
  SBTLUNIT_WORK *pUnit;
  s32 v16;
  AW_XAtk_Arg_t *ArgumentParam_local;
  SBTLUNIT_LISTWORK *v20;
  SBTLUNIT_LISTWORK *v21;
  s32 Step;
  s32 v23;
  s32 v24;
  f32 v27;
  f32 v28;

  if (ChkPause(aWork))
    return;
  goto LABEL_7;
  if (!ChkPause(aWork))
  {
LABEL_7:
    switch (aWork->Step)
    {
      case 0:
        v6 = aWork->StepTime + VRF_DeltaTime;
        aWork->StepTime = v6;
        if (v6 > (f32)(FPS60 * 600.0))
          goto LABEL_44;
        return;
      case 1:
        other_List2 = wk->other_List2;
        if (other_List2)
        {
          other_List2 = wk->other_List2;
          sBtlDeleteUnitList(other_List2, 0);
          p_other_List2 = &wk->other_List2;
          p_other_List2 = 0;
        }
        wk_local = wk;
        TargetList_MASK = sBtlCreateTargetList_MASK(2, 0, 0x10000);
        wk_local->other_List2 = TargetList_MASK;
        v13 = wk->other_List2;
        if (v13->count >= 1)
        {
          v13 = wk->other_List2;
          pUnit = v13->pUnitL[0]->pUnit;
          v16 = gIDTable[aWork->StepIntA];
          ArgumentParam_local = ArgumentParam;
          ArgumentParam_local->wk = pUnit;
          ArgumentParam_local = ((char *)ArgumentParam_local + 24);
          LODWORD(ArgumentParam_local[-1].wk) = v16;
          Add_2();
          pUnit->BossXAtk = 1;
        }
        v20 = wk->other_List2;
        sBtlDeleteUnitList(v20, 0);
        v21 = &wk->other_List2;
        v21 = 0;
        Step = aWork->Step;
        aWork->StepTime = 0.0;
        v23 = Step + 1;
        goto LABEL_45;
      case 2:
        v24 = aWork->StepIntA + 1;
        aWork->StepIntA = v24;
        if (v24 >= SLODWORD(gIDTable->max_length))
          aWork->StepIntA = 0;
        aWork->StepTime = 0.0;
        v23 = 3;
        goto LABEL_45;
      case 3:
        v27 = FPS60;
        v28 = aWork->StepTime + VRF_DeltaTime;
        aWork->StepTime = v28;
        if (v28 <= (f32)(v27 * 1200.0))
          return;
LABEL_44:
        v23 = 1;
        aWork->StepTime = 0.0;
LABEL_45:
        aWork->Step = v23;
        return;
      default:
        return;
    }
  }
}
