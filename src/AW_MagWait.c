#include "types.h"
#include "aw.h"
#include "aw_mag.h"
#include "aw_magwait.h"
#include "sbtlplayer.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1e47980
void Init(void) {
  ;
}

// 0x1e47990
s32 Add(s32 _Variation, f32 _SX, f32 _SY, f32 _SZ, s32 _MagKaifuku) {
  AW_WORK_t *AW_ID;
  AW_Func v9;
  s32 v10;
  AW_WORK_t *AW;
  char *v12;

  AW_ID = GetAW_ID(407);
  v9 = Allocate(AW_Func);
  _ctor(v9, 0, Method_Project_AW_MagWait_Calc__, 0);
  v10 = Add(407, 0.0, 0.0, 0.0, 0, v9, 0, 1);
  AW = GetAW(v10);
  v12 = "AW_MagWait";
  AW->StepIntA = MagKaifuku;
  AW->Variation = Variation;
  AW->StepBoolA = AW_ID != 0;
  AW->DbgStr = v12;
  return v10;
}

// 0x1e47ae0
void AW_MagDelete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 0);
}

// 0x1e47b50
void Calc(AW_WORK_t *aWork) {
  s32 Idx;
  f32 Z;
  s64 Y;

  Y = 0;
  Z = 0.0;
  if (!sBtlChkEnemyPosReset((f32 *)&Y + 1, &Y, &Z))
    return;
  Add(aWork->Variation, *((f32 *)&Y + 1), *(f32 *)&Y, Z, aWork->StepIntA, 0);
  if (aWork->StepBoolA)
  {
    goto LABEL_9;
  }
  else
  {
    Add(aWork->Variation, *((f32 *)&Y + 1), *(f32 *)&Y, Z, -1, 0);
    Add(aWork->Variation, *((f32 *)&Y + 1), *(f32 *)&Y, Z, -1, 0);
    Add(aWork->Variation, *((f32 *)&Y + 1), *(f32 *)&Y, Z, -1, 0);
    Add(aWork->Variation, *((f32 *)&Y + 1), *(f32 *)&Y, Z, -1, 0);
LABEL_9:
    Idx = aWork->Idx;
LABEL_10:
    DelAW(Idx, 0);
    return;
  }
  Idx = aWork->Idx;
  goto LABEL_10;
}
