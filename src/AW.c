#include "types.h"
#include "aw.h"

typedef struct AW_WORK_t AW_WORK_t;

AW_WORK_t *gWork[720];
AW_WORK_t *gWorkAvtiveTop_Default;
AW_WORK_t *gWorkAvtiveTop_HDEff;
AW_WORK_t *gWorkAvtiveTop_Battle;
AW_WORK_t *gWorkAvtiveTop_Pad;
bool gUseCalc2;
bool gUseCalc3;
s32 gUID;
static sdfVector3_t gCamPs2Pos;
sdfVector3_t gCamUnityPos;
