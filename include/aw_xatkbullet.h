#pragma once
#include "types.h"
#include "SKLID.h"

typedef struct AW_WORK_t AW_WORK_t;
typedef struct AW_XAtk_WORK_t AW_XAtk_WORK_t;

struct AW_XAtk_WORK_t {
    s32 Unit_ListID;
    s32 Unit_UID;
    s32 Variation;
    f32 X;
    f32 Y;
    f32 Z;
    f32 Dir;
    f32 DirY;
    f32 Scale;
    f32 MoveDir;
    f32 MoveDirRate;
    f32 MoveSpd;
    f32 MoveSpdRate;
    f32 MoveSpdMax;
    f32 HomingFrame;
    f32 HomingX;
    f32 HomingY;
    f32 HomingZ;
    u32 Flag;
    u32 Flag2;
    s32 Group_AW_Idx;
    s32 Group_AW_UID;
    SKLID SklID;
    s32 Pad_No;
};

extern AW_XAtk_WORK_t *ArgumentParam;

void Init(void);
s32 Add(void);
void Delete(AW_WORK_t *aWork);
void Calc(AW_WORK_t *aWork);
void Draw(AW_WORK_t *aWork);
s32 AW_XAtkAdd_BioArm_Top(void);
s32 AW_XAtkAdd_BioArm_Root(AW_WORK_t *aWorkTop);
s32 AW_XAtkAdd_BioArm_Mid(AW_WORK_t *aWorkTop, s32 _NumID);
void AW_XAtkDelete_BioArm(AW_WORK_t *aWork);
void AW_XAtkDelete_BioArm_Mid(AW_WORK_t *aWork);
void AW_XAtkCalc_BioArm_Top_R(AW_WORK_t *aWork);
void AW_XAtkCalc_BioArm_Top_L(AW_WORK_t *aWork);
void AW_XAtkCalc_BioArm_Root(AW_WORK_t *aWork);
void AW_XAtkCalc_BioArm_Mid(AW_WORK_t *aWork);
void AW_XAtkDraw_BioArm(AW_WORK_t *aWork);
