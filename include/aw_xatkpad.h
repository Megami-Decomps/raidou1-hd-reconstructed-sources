#pragma once
#include "types.h"
#include "SKLID.h"

typedef struct AW_WORK_t AW_WORK_t;
typedef struct AW_XAtkPad_Arg_t AW_XAtkPad_Arg_t;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

struct AW_XAtkPad_Arg_t {
    s32 V;
    f32 Ps2X;
    f32 Ps2Y;
    f32 Ps2Z;
    f32 Ps2Dir;
    s32 Delay;
    SKLID SklID;
    u32 Flag;
    SBTLUNIT_WORK *wk;
};

extern AW_XAtkPad_Arg_t *ArgumentParam;

void Init(void);
s32 Add(void);
void Delete(AW_WORK_t *aWork);
void Calc(AW_WORK_t *aWork);
void AW_XAtkCalc3(AW_WORK_t *aWork);
void AW_XAtkSetHomingPos(f32 _Ps2X, f32 _Ps2Y, f32 _Ps2Z);
void AW_XAtkDelete_XATK_FLAG2_BsFlowClr(void);
void AW_XAtkDelete_XATK_FLAG2_BsFlowClr_Setsuma(void);
void AW_XAtkDelete_BossDYING(SBTLUNIT_WORK *wkBoss);
void AW_XAtkDelete_DuplicationNG(SBTLUNIT_WORK *wkBoss);
void AW_XAtkClearBattleEnd_Pad(void);
