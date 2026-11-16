#pragma once
#include "types.h"
#include "SKLID.h"
#include "sbtl.h"

typedef struct AW_WORK_t AW_WORK_t;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

typedef void (*AW_Func)(AW_WORK_t *aWork);

struct AW_WORK_t {
    bool Use;
    s32 Idx;
    s32 SubIdx;
    s32 ID;
    s32 UID;
    s32 Variation;
    s32 ListType;
    AW_Func FuncCalc;
    AW_Func FuncDraw;
    AW_Func FuncCalc2;
    AW_Func FuncCalc3;
    f32 X;
    f32 Y;
    f32 Z;
    f32 PopX;
    f32 PopY;
    f32 PopZ;
    f32 Dir;
    f32 DirY;
    f32 DirIKY;
    f32 Scale;
    f32 MoveDir;
    f32 MoveDirRate;
    f32 MoveSpd;
    f32 MoveSpdRate;
    f32 MoveSpdMax;
    f32 MoveLen;
    f32 ShotDir;
    f32 ShotDirRate;
    f32 ShotCount;
    f32 ShotRapid;
    s32 ShotRapidInt;
    s32 ShotRapidCnt;
    s32 ShotWay;
    f32 ShotWayRange;
    s32 LaserFrameS;
    s32 LaserFrameL;
    f32 LaserRangeS;
    f32 LaserDirSS;
    f32 LaserOfsLen;
    f32 LaserRev;
    f32 HomingFrame;
    f32 HomingX;
    f32 HomingY;
    f32 HomingZ;
    f32 VelocityX;
    f32 VelocityY;
    f32 VelocityZ;
    s32 Child_AW_Idx;
    s32 Group_AW_Idx;
    s32 Group_AW_UID;
    s32 Step;
    f32 StepTime;
    s32 StepCnt;
    f32 StepFloatA;
    f32 StepFloatB;
    f32 StepFloatC;
    s32 StepIntA;
    s32 StepIntB;
    s32 StepIntC;
    bool StepBoolA;
    bool StepBoolB;
    u32 StepFlag;
    u32 StepFlag2;
    f32 StepOfsX;
    f32 StepOfsY;
    f32 StepOfsZ;
    s32 StepIntBuff[8];
    bool HDEff_Use;
    f32 HDEff_Speed;
    f32 HDEff_SimSpeed;
    f32 HDEff_Size;
    s32 HDEff_TblIdx;
    void *ParticleSystemList;
    SKLID HDEff_SkillID;
    bool HDEff_PosLink;
    s32 AnimStep;
    s32 AnimNum;
    s32 AnimIdx;
    s32 AnimIdxOld;
    f32 AnimTime;
    s32 AnimCnt;
    SBTLUNIT_WORK *wk;
    s32 Unit_ListID;
    s32 Unit_UID;
    char *DbgStr;
    s32 PrevListIdx;
    s32 NextListIdx;
};

extern AW_WORK_t *gWork[720];
extern AW_WORK_t *gWorkAvtiveTop_Default;
extern AW_WORK_t *gWorkAvtiveTop_HDEff;
extern AW_WORK_t *gWorkAvtiveTop_Battle;
extern AW_WORK_t *gWorkAvtiveTop_Pad;
extern bool gUseCalc2;
extern bool gUseCalc3;
extern sdfVector3_t gCamUnityPos;
extern s32 gUID;

// macros
// 0x1e2a020: void Init(void)
#define Init() do { \
    s64 i; \
    AW_WORK_t *v7; \
    s64 v9; \
    s64 v10; \
    AW_WORK_t *gWork_local; \
    AW_WORK_t *v13; \
    if (gWork) \
    { \
    goto LABEL_5; \
    } \
    v7 = NewSpecific(AW_WORK_t, 0x2D0u); \
    gWork = v7; \
    v9 = 32; \
    v10 = 720; \
    do \
    { \
    gWork_local = gWork; \
    v13 = Allocate(AW_WORK_t); \
    _ctor(v13); \
    *(Il2CppClass **)((char *)&gWork_local->obj.klass + v9) = v13; \
    v9 += 8; \
    --v10; \
    } \
    while (v10); \
    LABEL_5: \
    for (i = 4; i != 724; ++i) \
    { \
    WorkClear(*((AW_WORK_t *)&gWork->obj.klass + i), i - 4); \
    } \
    AWList_Init(); \
    *(u16 *)&gUseCalc2 = 0; \
    gUID = 0; \
} while (0)

// 0x1e2a430: void WorkClear(AW_WORK_t *aWork, s32 _Idx)
#define WorkClear(aWork, _Idx) do { \
    s32 *p_Step; \
    s64 v11; \
    s64 v12; \
    s64 v13; \
    s64 v14; \
    s64 v15; \
    s64 v16; \
    s64 v17; \
    s64 v18; \
    s64 v19; \
    s64 v20; \
    s64 v21; \
    s64 v22; \
    s64 v23; \
    char *v24; \
    aWork->Use = 0; \
    aWork->Idx = Idx; \
    aWork->FuncCalc = 0; \
    *(_OWORD *)&aWork->SubIdx = xmmword_3CFCD90; \
    aWork->FuncDraw = 0; \
    aWork->FuncCalc2 = 0; \
    aWork->FuncCalc3 = 0; \
    *(_OWORD *)&aWork->Step = 0u; \
    p_Step = &aWork->Step; \
    *(u64 *)(p_Step - 3) = -1; \
    __asm { FMOV            V1.2S, #1.0 } \
    *((u64 *)p_Step - 16) = 0x3F80000000000000LL; \
    *(p_Step - 1) = -1; \
    *((u64 *)p_Step + 6) = 0; \
    p_Step[14] = 0; \
    *((u8 *)p_Step + 72) = 0; \
    p_Step[19] = 1065353216; \
    p_Step[22] = -1; \
    *((u64 *)p_Step + 10) = _D1; \
    *((u8 *)p_Step + 108) = 0; \
    *((u64 *)p_Step + 12) = 0; \
    *((_OWORD *)p_Step + 1) = 0u; \
    *(u64 *)((char *)p_Step + 30) = 0; \
    *((_OWORD *)p_Step - 10) = 0u; \
    *((_OWORD *)p_Step - 9) = 0u; \
    v11 = *((u64 *)p_Step + 14); \
    *(u64 *)(v11 + 32) = 0; \
    v12 = *((u64 *)p_Step + 14); \
    *(u64 *)(v12 + 40) = 0; \
    v13 = *((u64 *)p_Step + 14); \
    *(u64 *)(v13 + 48) = 0; \
    v14 = *((u64 *)p_Step + 14); \
    *(u64 *)(v14 + 56) = 0; \
    v15 = *((u64 *)p_Step + 14); \
    *(u64 *)(v15 + 64) = 0; \
    v16 = *((u64 *)p_Step + 14); \
    *(u64 *)(v16 + 72) = 0; \
    v17 = *((u64 *)p_Step + 14); \
    *(u64 *)(v17 + 80) = 0; \
    v18 = *((u64 *)p_Step + 14); \
    *(u64 *)(v18 + 88) = 0; \
    v19 = *((u64 *)p_Step + 14); \
    *(u64 *)(v19 + 96) = 0; \
    v20 = *((u64 *)p_Step + 14); \
    *(u64 *)(v20 + 104) = 0; \
    v21 = *((u64 *)p_Step + 14); \
    *(u64 *)(v21 + 112) = 0; \
    v22 = *((u64 *)p_Step + 14); \
    *(u64 *)(v22 + 120) = 0; \
    v23 = *((u64 *)p_Step + 14); \
    *(u64 *)(v23 + 128) = 0; \
    *((u64 *)p_Step + 17) = 0; \
    *((u64 *)p_Step + 18) = 0; \
    *(_OWORD *)(p_Step + 30) = xmmword_3CFC710; \
    p_Step[38] = 0; \
    *((u64 *)p_Step + 20) = 0; \
    *((u64 *)p_Step + 21) = 0; \
    v24 = ""; \
    *((u64 *)p_Step + 22) = ""; \
} while (0)

// 0x1e2a2c0: void WorkAllClear(void)
#define WorkAllClear() do { \
    s64 i; \
    for (i = 0; i != 720; ++i) \
    { \
    WorkClear(gWork[i], i); \
    } \
} while (0)

// 0x1e2a650: void WorkFreeAllClear_BattleEnd(void)
#define WorkFreeAllClear_BattleEnd() do { \
    s64 i; \
    AW_WORK_t *v4; \
    for (i = 0; i != 720; ++i) \
    { \
    v4 = gWork[i]; \
    if (v4->Use) \
    continue; \
    if (v4->wk) \
    { \
    ClassMemAlloc(v4->wk, 0); \
    v4->wk = 0; \
    } \
    WorkClear(v4, i); \
    } \
} while (0)

// 0x1e2a740: AW_WORK_t *GetFreeWork(s32 _ListType)
static inline AW_WORK_t *GetFreeWork(s32 _ListType) {
  AW_WORK_t *v5;
  AW_WORK_t *v6;
  s64 m_Items;
  s64 v9;
  s64 v10;
  s32 v11;
  s32 Idx;

  v5 = gWork[0];
  v6 = gWork[v5->NextListIdx];
  LODWORD(gWork) = v6->NextListIdx;
  v6->Use = 1;
  v5->NextListIdx = (s32)gWork;
  m_Items = gWork;
  v9 = *(u64 *)(m_Items + 8 * ListType);
  v10 = *(u64 *)(m_Items + 8 * *(s32 *)(v9 + 424));
  v11 = *(u32 *)(v10 + 428);
  v6->PrevListIdx = *(u32 *)(v10 + 20);
  Idx = v6->Idx;
  v6->NextListIdx = v11;
  *(u32 *)(v10 + 428) = Idx;
  *(u32 *)(v9 + 424) = Idx;
  return v6;
}

// 0x1e2a8d0: AW_WORK_t *GetAW(s32 _AW_Idx)
#define GetAW(_AW_Idx) (gWork[AW_Idx])

// 0x1e2a940: AW_WORK_t *GetAW_ID(s32 _Id)
static inline AW_WORK_t *GetAW_ID(s32 _Id) {
  s64 i;
  AW_WORK_t *v5;

  for (i = 4; i != 724; ++i)
  {
    v5 = *((AW_WORK_t *)&gWork->obj.klass + i);
    if (!v5->Use)
      continue;
    if (v5->ID == Id)
      return v5;
  }
  return 0;
}

// 0x1e2aa60: AW_WORK_t *GetAW_ID_Default(s32 _Id)
static inline AW_WORK_t *GetAW_ID_Default(s32 _Id) {
  AW_WORK_t *gWorkAvtiveTop_Default_local;
  s32 Idx;

  gWorkAvtiveTop_Default_local = gWorkAvtiveTop_Default;
  while (1)
  {
    gWorkAvtiveTop_Default_local = gWork[gWorkAvtiveTop_Default_local->NextListIdx];
    Idx = gWorkAvtiveTop_Default_local->Idx;
    if (Idx == gWorkAvtiveTop_Default->Idx)
      break;
    if (gWorkAvtiveTop_Default_local->Use && gWorkAvtiveTop_Default_local->ID == Id)
      return gWorkAvtiveTop_Default_local;
  }
  return 0;
}

// 0x1e2ab40: void DebugGetAW(void)
static inline void DebugGetAW(void) {
  s32 v2;

  v2 = 720;
  do
  {
    while (1)
    {
      if (!--v2)
        return;
    }
    --v2;
  }
  while (v2);
}

// 0x1e2ac00: AW_WORK_t *GetAW_Unit_ListID(s32 _ID, s32 _Unit_ListID)
static inline AW_WORK_t *GetAW_Unit_ListID(s32 _ID, s32 _Unit_ListID) {
  s64 i;
  AW_WORK_t *v7;

  for (i = 4; i != 724; ++i)
  {
    v7 = *((AW_WORK_t *)&gWork->obj.klass + i);
    if (!v7->Use)
      continue;
    if (v7->ID == ID && v7->Unit_ListID == Unit_ListID)
      return v7;
  }
  return 0;
}

// 0x1e2ad30: AW_WORK_t *GetAW_Unit_ListID_SubIdx(s32 _ID, s32 _Unit_ListID, s32 _SubIdx)
static inline AW_WORK_t *GetAW_Unit_ListID_SubIdx(s32 _ID, s32 _Unit_ListID, s32 _SubIdx) {
  s64 i;
  AW_WORK_t *v9;

  for (i = 4; i != 724; ++i)
  {
    v9 = *((AW_WORK_t *)&gWork->obj.klass + i);
    if (!v9->Use)
      continue;
    if (v9->ID == ID && v9->Unit_ListID == Unit_ListID && v9->SubIdx == SubIdx)
      return v9;
  }
  return 0;
}

// 0x1e2ae60: AW_WORK_t *GetAW_SubIdx(s32 _ID, s32 _SubIdx)
static inline AW_WORK_t *GetAW_SubIdx(s32 _ID, s32 _SubIdx) {
  s64 i;
  AW_WORK_t *v7;

  for (i = 4; i != 724; ++i)
  {
    v7 = *((AW_WORK_t *)&gWork->obj.klass + i);
    if (!v7->Use)
      continue;
    if (v7->ID == ID && v7->SubIdx == SubIdx)
      return v7;
  }
  return 0;
}

// 0x1e2af90: AW_WORK_t *GetAW_IDNUM(s32 _Id, s32 _Num)
static inline AW_WORK_t *GetAW_IDNUM(s32 _Id, s32 _Num) {
  s32 v6;
  s64 i;
  AW_WORK_t *v8;

  v6 = 0;
  for (i = 4; i != 724; ++i)
  {
    v8 = *((AW_WORK_t *)&gWork->obj.klass + i);
    if (!v8->Use)
      continue;
    if (v8->ID == Id)
    {
      if (v6 == Num)
        return v8;
      ++v6;
    }
  }
  return 0;
}

// 0x1e2a350: void AWList_Init(void)
#define AWList_Init() do { \
    AW_WORK_t *v7; \
    AW_WORK_t *v9; \
    AW_WORK_t *v11; \
    AW_WORK_t *v13; \
    AddAW_ListTop(0); \
    AddAW_ListTop(1); \
    AddAW_ListTop(2); \
    AddAW_ListTop(3); \
    AddAW_ListTop(4); \
    v7 = gWork[1]; \
    gWorkAvtiveTop_Default = v7; \
    v9 = gWork[2]; \
    gWorkAvtiveTop_HDEff = v9; \
    v11 = gWork[3]; \
    gWorkAvtiveTop_Battle = v11; \
    v13 = gWork[4]; \
    gWorkAvtiveTop_Pad = v13; \
    AWList_FreeInit(); \
} while (0)

// 0x1e2b180: void AWList_FreeInit(void)
#define AWList_FreeInit() do { \
    AW_WORK_t *v3; \
    s32 *p_PrevListIdx; \
    s64 v6; \
    AW_WORK_t *m_Items; \
    AW_WORK_t *v8; \
    s32 v9; \
    s32 Idx; \
    v3 = gWork[0]; \
    p_PrevListIdx = &v3->PrevListIdx; \
    v6 = 0; \
    m_Items = gWork; \
    do \
    { \
    v8 = m_Items[v6]; \
    if (!v8->Use) \
    { \
    v9 = v3->Idx; \
    *p_PrevListIdx = v6; \
    v3->NextListIdx = v6; \
    v3 = v8; \
    v8->PrevListIdx = v9; \
    v8->NextListIdx = *p_PrevListIdx; \
    } \
    ++v6; \
    } \
    while (v6 != 720); \
} while (0)

// 0x1e2b2d0: void AWList_Del(AW_WORK_t *aWork)
#define AWList_Del(aWork) do { \
    s64 PrevListIdx; \
    s64 NextListIdx; \
    AW_WORK_t *gWork_local; \
    AW_WORK_t *v7; \
    s64 v8; \
    s64 v9; \
    PrevListIdx = aWork->PrevListIdx; \
    NextListIdx = aWork->NextListIdx; \
    gWork_local = gWork; \
    v7 = gWork_local[0]; \
    gWork_local = ((char *)gWork_local + 32); \
    v8 = v7->PrevListIdx; \
    *(u32 *)(*((u64 *)&gWork_local->obj.klass + PrevListIdx) + 428) = NextListIdx; \
    v9 = *((u64 *)&gWork_local->obj.klass + v8); \
    *(u32 *)(*((u64 *)&gWork_local->obj.klass + NextListIdx) + 424) = PrevListIdx; \
    LODWORD(PrevListIdx) = *(u32 *)(v9 + 428); \
    aWork->PrevListIdx = *(u32 *)(v9 + 20); \
    LODWORD(gWork_local) = aWork->Idx; \
    aWork->NextListIdx = PrevListIdx; \
    v7->PrevListIdx = (s32)gWork_local; \
    *(u32 *)(v9 + 428) = (u32)gWork_local; \
} while (0)

// 0x1e2a830: void AWList_ActiveAdd(AW_WORK_t *aWork, s32 _ListType)
#define AWList_ActiveAdd(aWork, _ListType) do { \
    s64 m_Items; \
    s64 v7; \
    s64 v8; \
    s32 v9; \
    s32 Idx; \
    m_Items = gWork; \
    v7 = *(u64 *)(m_Items + 8 * ListType); \
    v8 = *(u64 *)(m_Items + 8 * *(s32 *)(v7 + 424)); \
    v9 = *(u32 *)(v8 + 428); \
    aWork->PrevListIdx = *(u32 *)(v8 + 20); \
    Idx = aWork->Idx; \
    aWork->NextListIdx = v9; \
    *(u32 *)(v8 + 428) = Idx; \
    *(u32 *)(v7 + 424) = Idx; \
} while (0)

// 0x1e2b380: void DelAW(s32 _Index, bool _ObjDel)
#define DelAW(_Index, _ObjDel) do { \
    AW_WORK_t *v7; \
    void *ParticleSystemList; \
    s32 size; \
    s32 v10; \
    void *Obj; \
    s64 PrevListIdx; \
    s64 NextListIdx; \
    s32 Idx; \
    AW_WORK_t *gWork_local; \
    AW_WORK_t *v18; \
    s64 v19; \
    s64 v20; \
    void *v21; \
    v7 = gWork[Index]; \
    if (!ObjDel) \
    { \
    LABEL_16: \
    goto LABEL_17; \
    } \
    ParticleSystemList = v7->ParticleSystemList; \
    if (ParticleSystemList) \
    { \
    size = ParticleSystemList->_size; \
    v10 = ParticleSystemList->_version + 1; \
    ParticleSystemList->_size = 0; \
    ParticleSystemList->_version = v10; \
    if (size >= 1) \
    Clear(ParticleSystemList->_items, 0, size, 0); \
    } \
    Obj = v7->Obj; \
    if (!op_Inequality(v7->Obj, 0, 0)) \
    goto LABEL_16; \
    v21 = v7->Obj; \
    Destroy_61007920(v21, 0); \
    LABEL_17: \
    PrevListIdx = v7->PrevListIdx; \
    NextListIdx = v7->NextListIdx; \
    Idx = v7->Idx; \
    gWork_local = gWork; \
    v18 = gWork_local[0]; \
    gWork_local = ((char *)gWork_local + 32); \
    v19 = v18->PrevListIdx; \
    *(u32 *)(*((u64 *)&gWork_local->obj.klass + PrevListIdx) + 428) = NextListIdx; \
    v20 = *((u64 *)&gWork_local->obj.klass + v19); \
    *(u32 *)(*((u64 *)&gWork_local->obj.klass + NextListIdx) + 424) = PrevListIdx; \
    LODWORD(PrevListIdx) = *(u32 *)(v20 + 428); \
    v7->PrevListIdx = *(u32 *)(v20 + 20); \
    v7->NextListIdx = PrevListIdx; \
    v18->PrevListIdx = Idx; \
    *(u32 *)(v20 + 428) = Idx; \
    WorkClear(v7, Idx); \
} while (0)

// 0x1e2b5d0: void DelAW_ID(s32 _Id, bool _ObjDel)
#define DelAW_ID(_Id, _ObjDel) do { \
    s64 v6; \
    bool v7; \
    s64 v8; \
    s32 v9; \
    v6 = 4; \
    v7 = ObjDel; \
    do \
    { \
    v8 = *((u64 *)&gWork->obj.klass + v6); \
    if (!!*(u8 *)(v8 + 16)) \
    { \
    if (*(u32 *)(v8 + 28) == Id) \
    { \
    v9 = *(u32 *)(v8 + 20); \
    DelAW(v9, v7); \
    } \
    } \
    ++v6; \
    } \
    while (v6 != 724); \
} while (0)

// 0x1e2b700: void DelAW_ID2(s32 _Id0, s32 _Id1, bool _ObjDel)
#define DelAW_ID2(_Id0, _Id1, _ObjDel) do { \
    s64 v8; \
    bool v9; \
    s64 v10; \
    s32 v11; \
    s32 v13; \
    v8 = 4; \
    v9 = ObjDel; \
    do \
    { \
    v10 = *((u64 *)&gWork->obj.klass + v8); \
    if (!!*(u8 *)(v10 + 16)) \
    { \
    v11 = *(u32 *)(v10 + 28); \
    if (v11 == Id0 || v11 == Id1) \
    { \
    v13 = *(u32 *)(v10 + 20); \
    DelAW(v13, v9); \
    } \
    } \
    ++v8; \
    } \
    while (v8 != 724); \
} while (0)

// 0x1e2b830: void DelAW_ID3(s32 _Id0, s32 _Id1, s32 _Id2, bool _ObjDel)
#define DelAW_ID3(_Id0, _Id1, _Id2, _ObjDel) do { \
    s64 v10; \
    bool v11; \
    s64 v12; \
    s32 v13; \
    s32 v16; \
    v10 = 4; \
    v11 = ObjDel; \
    do \
    { \
    v12 = *((u64 *)&gWork->obj.klass + v10); \
    if (!!*(u8 *)(v12 + 16)) \
    { \
    v13 = *(u32 *)(v12 + 28); \
    if (v13 == Id2 || v13 == Id0 || v13 == Id1) \
    { \
    v16 = *(u32 *)(v12 + 20); \
    DelAW(v16, v11); \
    } \
    } \
    ++v10; \
    } \
    while (v10 != 724); \
} while (0)

// 0x1e2b980: void DelAW_ID6(s32 _Id0, s32 _Id1, s32 _Id2, s32 _Id3, s32 _Id4, s32 _Id5, bool _ObjDel)
#define DelAW_ID6(_Id0, _Id1, _Id2, _Id3, _Id4, _Id5, _ObjDel) do { \
    s64 v16; \
    s64 v17; \
    s32 v18; \
    s32 v24; \
    bool v25; \
    v16 = 4; \
    v25 = ObjDel; \
    do \
    { \
    v17 = *((u64 *)&gWork->obj.klass + v16); \
    if (!!*(u8 *)(v17 + 16)) \
    { \
    v18 = *(u32 *)(v17 + 28); \
    if (v18 == Id5 || v18 == Id4 || v18 == Id3 || v18 == Id2 || v18 == Id0 || v18 == Id1) \
    { \
    v24 = *(u32 *)(v17 + 20); \
    DelAW(v24, v25); \
    } \
    } \
    ++v16; \
    } \
    while (v16 != 724); \
} while (0)

// 0x1e2baf0: void DelAW_ListType(s32 _ListType, bool _ObjDel)
#define DelAW_ListType(_ListType, _ObjDel) do { \
    s64 v6; \
    bool v7; \
    s64 v8; \
    s32 v9; \
    v6 = 4; \
    v7 = ObjDel; \
    do \
    { \
    v8 = *((u64 *)&gWork->obj.klass + v6); \
    if (!!*(u8 *)(v8 + 16)) \
    { \
    if (*(u32 *)(v8 + 40) == ListType) \
    { \
    v9 = *(u32 *)(v8 + 20); \
    DelAW(v9, v7); \
    } \
    } \
    ++v6; \
    } \
    while (v6 != 724); \
} while (0)

// 0x1e2b0b0: void AddAW_ListTop(s32 _ListType)
#define AddAW_ListTop(_ListType) do { \
    AW_WORK_t *v4; \
    s32 Idx; \
    char *v6; \
    char *v7; \
    s32 v8; \
    v8 = ListType; \
    v4 = gWork[ListType]; \
    v4->Use = 1; \
    v4->ID = 3000; \
    Idx = v4->Idx; \
    v4->NextListIdx = Idx; \
    v4->PrevListIdx = Idx; \
    v6 = ToString((s32)&v8, 0); \
    v7 = Concat_54766928("AWLIST_Top_", v6, 0); \
    v4->DbgStr = v7; \
} while (0)

// 0x1e2bc20: s32 GetUID(void)
static inline s32 GetUID(void) {
  s32 result;

  result = (u16)(LOWORD(gUID) + 1);
  gUID = result;
  return result;
}

// 0x1e2bc90: s32 Add(s32 _ID, f32 _X, f32 _Y, f32 _Z, void *_Obj, AW_Func _Calc, AW_Func _Draw, s32 _ListType)
static inline s32 Add(s32 _ID, f32 _X, f32 _Y, f32 _Z, void *_Obj, AW_Func _Calc, AW_Func _Draw, s32 _ListType) {
  AW_WORK_t *FreeWork;
  AW_WORK_t *v18;
  s32 v22;
  void *v24;

  FreeWork = GetFreeWork(ListType);
  FreeWork->ID = ID;
  v18 = FreeWork;
  v18->X = X;
  v18->Y = Y;
  v18->Z = Z;
  v18->PopX = X;
  v18->PopY = Y;
  v18->PopZ = Z;
  v18->Obj = Obj;
  v22 = (u16)(gUID + 1);
  gUID = v22;
  v18->UID = v22;
  v18->FuncCalc = Calc;
  v18->FuncDraw = Draw;
  *(u64 *)&v18->Step = 0;
  v18->ListType = ListType;
  v24 = v18->Obj;
  if (!op_Inequality(v24, 0, 0))
    return v18->Idx;
  goto LABEL_11;
  if (op_Inequality(v18->Obj, 0, 0))
LABEL_11:
    SetActive(v18->Obj, 0, 0);
  return v18->Idx;
}

// 0x1e2be50: void Set_Calc2Func(s32 _AW_Idx, AW_Func _Calc2)
#define Set_Calc2Func(_AW_Idx, _Calc2) do { \
    AW_WORK_t *v7; \
    v7 = gWork[AW_Idx]; \
    v7->FuncCalc2 = Calc2; \
    gUseCalc2 = 1; \
} while (0)

// 0x1e2bf40: void Set_Calc3Func(s32 _AW_Idx, AW_Func _Calc3)
#define Set_Calc3Func(_AW_Idx, _Calc3) do { \
    AW_WORK_t *v7; \
    v7 = gWork[AW_Idx]; \
    v7->FuncCalc3 = Calc3; \
    gUseCalc3 = 1; \
} while (0)

// 0x1e2c030: void Set_HDEff(s32 _AW_Idx, bool _UseHDEff, s32 _TblIdx)
#define Set_HDEff(_AW_Idx, _UseHDEff, _TblIdx) do { \
    const MethodInfo_253CB50 *v9; \
    AW_WORK_t *v10; \
    void *Obj; \
    void *ComponentsInChildren_object__39045968; \
    void *v13; \
    v9 = Method_UnityEngine_GameObject_GetComponentsInChildren_ParticleSystem___; \
    v10 = gWork[AW_Idx]; \
    Obj = v10->Obj; \
    v10->HDEff_Use = UseHDEff; \
    v10->HDEff_TblIdx = TblIdx; \
    ComponentsInChildren_object__39045968 = GetComponentsInChildren_object__39045968(Obj, v9); \
    v13 = ToList_object_(ComponentsInChildren_object__39045968); \
    v10->ParticleSystemList = v13; \
} while (0)

// 0x1e2c150: void Set_AnimObj(s32 _AW_Idx, s32 _AnimIdx, char *_Name)
static inline void Set_AnimObj(s32 _AW_Idx, s32 _AnimIdx, char *_Name) {
  AW_WORK_t *v9;
  void *AnimObj;
  void *transform;
  void *v12;
  void *gameObject;
  s64 v14;
  void *v15;
  s32 v16;

  v9 = gWork[AW_Idx];
  AnimObj = v9->AnimObj;
  transform = get_transform(v9->Obj, 0);
  v12 = Find(transform, Name, 0);
  gameObject = get_gameObject(v12, 0);
  v14 = AnimIdx;
  AnimObj[v14] = gameObject;
  v15 = v9->AnimObj[v14];
  if (!op_Inequality(v15, 0, 0))
  {
    v16 = AnimIdx + 1;
    if (v9->AnimNum >= AnimIdx + 1)
      return;
LABEL_15:
    v9->AnimNum = v16;
    return;
  }
  SetActive(v9->AnimObj[AnimIdx], 0, 0);
  v16 = AnimIdx + 1;
  if (v9->AnimNum < AnimIdx + 1)
    goto LABEL_15;
}

// 0x1e2c320: void Draw_AnimObj(AW_WORK_t *aWork)
#define Draw_AnimObj(aWork) do { \
    s32 AnimIdx; \
    s32 AnimNum; \
    s64 v5; \
    s64 v6; \
    AnimIdx = aWork->AnimIdx; \
    if (aWork->AnimIdxOld != AnimIdx) \
    { \
    AnimNum = aWork->AnimNum; \
    aWork->AnimIdxOld = AnimIdx; \
    if (AnimIdx == -1) \
    { \
    if (AnimNum >= 1) \
    { \
    v6 = 0; \
    do \
    SetActive(aWork->AnimObj[v6++], 0, 0); \
    while (v6 < aWork->AnimNum); \
    } \
    } \
    else if (AnimNum >= 1) \
    { \
    v5 = 0; \
    do \
    { \
    SetActive(aWork->AnimObj[v5], v5 == aWork->AnimIdx, 0); \
    ++v5; \
    } \
    while (v5 < aWork->AnimNum); \
    } \
    } \
} while (0)

// 0x1e2c3e0: void Draw_BillboardObj(AW_WORK_t *aWork)
#define Draw_BillboardObj(aWork) do { \
    void *transform; \
    transform = get_transform(aWork->Obj, 0); \
    LookAt(transform, gCamUnityPos); \
} while (0)

// 0x1e2c470: void SetPosLink_ID(s32 _Id, bool _OnOff)
#define SetPosLink_ID(_Id, _OnOff) do { \
    bool v4; \
    s64 i; \
    s64 v7; \
    v4 = OnOff; \
    for (i = 4; i != 724; ++i) \
    { \
    v7 = *((u64 *)&gWork->obj.klass + i); \
    if (!*(u8 *)(v7 + 16)) \
    continue; \
    if (*(u32 *)(v7 + 28) == Id) \
    *(u8 *)(v7 + 348) = v4; \
    } \
} while (0)

// 0x1e2c580: bool ChkPause(AW_WORK_t *aWork)
static inline bool ChkPause(AW_WORK_t *aWork) {
  void *ParticleSystemList;
  f32 HDEff_Speed;
  __int128 v7;
  Il2CppObject *current;
  f32 HDEff_SimSpeed;
  SBATTLE_WORK *v11;
  System_Collections_Generic_List_Enumerator_T__o v13;
  void *m_ParticleSystem;
  System_Collections_Generic_List_Enumerator_T__o v15;
  UnityEngine_ParticleSystem_MainModule_o v16;

  ParticleSystemList = aWork->ParticleSystemList;
  memset(&v15, 0, sizeof(v15));
  m_ParticleSystem = 0;
  if (ParticleSystemList)
  {
    HDEff_Speed = aWork->HDEff_Speed;
    if (IsSceanStop())
      goto LABEL_15;
    if (wk->mode == 5)
      goto LABEL_15;
    if (!wk->cmbSkl->bRun)
      goto LABEL_16;
LABEL_15:
    HDEff_Speed = 0.0;
LABEL_16:
    if (HDEff_Speed != aWork->HDEff_SimSpeed)
    {
      aWork->HDEff_SimSpeed = HDEff_Speed;
      _GetEnumerator(&v13, aWork->ParticleSystemList);
      v7 = *(_OWORD *)&v13._list;
      v13._list = 0;
      *(u64 *)&v13._index = &v15;
      v15._current = v13._current;
      *(_OWORD *)&v15._list = v7;
      while (_MoveNext(&v15))
      {
        current = v15._current;
        if (!op_Equality(current, 0, 0))
        {
          v16.m_ParticleSystem = get_main(current, 0).m_ParticleSystem;
          HDEff_SimSpeed = aWork->HDEff_SimSpeed;
          m_ParticleSystem = v16.m_ParticleSystem;
          set_simulationSpeed((UnityEngine_ParticleSystem_MainModule_o)&m_ParticleSystem, HDEff_SimSpeed, 0);
        }
      }
      _Dispose(&v15);
    }
  }
  if (IsSceanStop())
    return 1;
  v11 = wk;
  if (v11->mode == 5)
    return 1;
  v11 = wk;
  return v11->cmbSkl->bRun;
}

// 0x1e2c8b0: bool ChkPause_MenuOnly(AW_WORK_t *aWork)
static inline bool ChkPause_MenuOnly(AW_WORK_t *aWork) {
  void *ParticleSystemList;
  f32 HDEff_Speed;
  f32 v6;
  Il2CppObject *current;
  f32 HDEff_SimSpeed;
  void *m_ParticleSystem;
  System_Collections_Generic_List_Enumerator_T__o v11;
  UnityEngine_ParticleSystem_MainModule_o v12;

  ParticleSystemList = aWork->ParticleSystemList;
  memset(&v11, 0, sizeof(v11));
  m_ParticleSystem = 0;
  if (!ParticleSystemList)
    goto LABEL_22;
  HDEff_Speed = aWork->HDEff_Speed;
  v6 = 0.0;
  if (wk->mode != 5)
    v6 = HDEff_Speed;
  if (v6 != aWork->HDEff_SimSpeed)
  {
    aWork->HDEff_SimSpeed = v6;
    _GetEnumerator(&v11, aWork->ParticleSystemList);
    while (_MoveNext(&v11))
    {
      current = v11._current;
      if (!op_Equality(current, 0, 0))
      {
        v12.m_ParticleSystem = get_main(current, 0).m_ParticleSystem;
        HDEff_SimSpeed = aWork->HDEff_SimSpeed;
        m_ParticleSystem = v12.m_ParticleSystem;
        set_simulationSpeed((UnityEngine_ParticleSystem_MainModule_o)&m_ParticleSystem, HDEff_SimSpeed, 0);
      }
    }
    _Dispose(&v11);
  }
  else
  {
LABEL_22:
  }
  return wk->mode == 5;
}

// 0x1e2caf0: void CalcUpdate(void)
static inline void CalcUpdate(void) {
  s64 v1;
  s64 v3;
  void *v4;
  s64 v6;
  s64 v7;
  s64 v8;
  s64 i;
  s64 v10;
  s64 v11;

  v1 = 4;
  do
  {
    v3 = *((u64 *)&gWork->obj.klass + v1);
    if (!!*(u8 *)(v3 + 16))
    {
      if (*(u64 *)(v3 + 48))
      {
        if (*(u32 *)(v3 + 368) != -1)
        {
          v4 = *(void *)(v3 + 400);
          if (op_Inequality(*(void *)(v3 + 400), 0, 0))
            SetActive(*(void *)(v3 + 400), 1, 0);
        }
        (*(*(u64 *)(v3 + 48) + 24))(*(u64 *)(*(u64 *)(v3 + 48) + 64), v3, *(u64 *)(*(u64 *)(v3 + 48) + 40));
      }
    }
    ++v1;
  }
  while (v1 != 724);
  if (!gUseCalc3)
    goto LABEL_41;
  goto LABEL_25;
  if (gUseCalc3)
  {
LABEL_25:
    v6 = 4;
    gUseCalc3 = 0;
    do
    {
      v7 = *((u64 *)&gWork->obj.klass + v6);
      if (*(u8 *)(v7 + 16))
      {
        v8 = *(u64 *)(v7 + 72);
        if (v8)
        {
          (*(v8 + 24))(*(u64 *)(v8 + 64));
          gUseCalc3 = 1;
        }
      }
      ++v6;
    }
    while (v6 != 724);
  }
LABEL_41:
  if (!gUseCalc2)
    return;
  goto LABEL_45;
  if (gUseCalc2)
  {
LABEL_45:
    for (i = 4; i != 724; ++i)
    {
      v10 = *((u64 *)&gWork->obj.klass + i);
      if (*(u8 *)(v10 + 16))
        goto LABEL_55;
      continue;
      if (*(u8 *)(v10 + 16))
      {
LABEL_55:
        v11 = *(u64 *)(v10 + 64);
        if (v11)
        {
          (*(v11 + 24))(*(u64 *)(v11 + 64), v10, *(u64 *)(v11 + 40));
          *(u64 *)(v10 + 64) = 0;
        }
      }
    }
  }
}

// 0x1e2ce90: void DrawUpdate(void)
#define DrawUpdate() do { \
    AW_WORK_t *gWorkAvtiveTop_HDEff_local; \
    s32 Idx; \
    AW_WORK_t *gWorkAvtiveTop_Battle_local; \
    s32 v7; \
    AW_Func FuncDraw; \
    AW_WORK_t *gWorkAvtiveTop_Pad_local; \
    s32 v11; \
    AW_Func v13; \
    AW_WORK_t *gWorkAvtiveTop_Default_local; \
    s32 v15; \
    AW_Func v16; \
    gWorkAvtiveTop_HDEff_local = gWorkAvtiveTop_HDEff; \
    while (1) \
    { \
    gWorkAvtiveTop_HDEff_local = gWork[gWorkAvtiveTop_HDEff_local->NextListIdx]; \
    Idx = gWorkAvtiveTop_HDEff_local->Idx; \
    if (Idx == gWorkAvtiveTop_HDEff->Idx) \
    break; \
    (gWorkAvtiveTop_HDEff_local->FuncDraw->invoke_impl)(gWorkAvtiveTop_HDEff_local->FuncDraw->method_code, gWorkAvtiveTop_HDEff_local, gWorkAvtiveTop_HDEff_local->FuncDraw->method); \
    } \
    gWorkAvtiveTop_Battle_local = gWorkAvtiveTop_Battle; \
    while (1) \
    { \
    gWorkAvtiveTop_Battle_local = gWork[gWorkAvtiveTop_Battle_local->NextListIdx]; \
    v7 = gWorkAvtiveTop_Battle_local->Idx; \
    if (v7 == gWorkAvtiveTop_Battle->Idx) \
    break; \
    FuncDraw = gWorkAvtiveTop_Battle_local->FuncDraw; \
    if (FuncDraw) \
    { \
    (FuncDraw->invoke_impl)(FuncDraw->method_code, gWorkAvtiveTop_Battle_local, FuncDraw->method); \
    } \
    } \
    gWorkAvtiveTop_Pad_local = gWorkAvtiveTop_Pad; \
    while (1) \
    { \
    gWorkAvtiveTop_Pad_local = gWork[gWorkAvtiveTop_Pad_local->NextListIdx]; \
    v11 = gWorkAvtiveTop_Pad_local->Idx; \
    if (v11 == gWorkAvtiveTop_Pad->Idx) \
    break; \
    v13 = gWorkAvtiveTop_Pad_local->FuncDraw; \
    if (v13) \
    { \
    (v13->invoke_impl)(v13->method_code, gWorkAvtiveTop_Pad_local, v13->method); \
    } \
    } \
    gWorkAvtiveTop_Default_local = gWorkAvtiveTop_Default; \
    while (1) \
    { \
    gWorkAvtiveTop_Default_local = gWork[gWorkAvtiveTop_Default_local->NextListIdx]; \
    v15 = gWorkAvtiveTop_Default_local->Idx; \
    if (v15 == gWorkAvtiveTop_Default->Idx) \
    break; \
    v16 = gWorkAvtiveTop_Default_local->FuncDraw; \
    if (v16) \
    { \
    (v16->invoke_impl)(v16->method_code, gWorkAvtiveTop_Default_local, v16->method); \
    } \
    } \
} while (0)

// 0x1e2d120: void SetCameraPs2Pos(f32 _CamPs2X, f32 _CamPs2Y, f32 _CamPs2Z)
#define SetCameraPs2Pos(_CamPs2X, _CamPs2Y, _CamPs2Z) do { \
    f32 *static_fields; \
    static_fields[12] = CamPs2X; \
    static_fields[13] = CamPs2Y; \
    static_fields[14] = CamPs2Z; \
    static_fields[15] = CamPs2X / -100.0; \
    static_fields[16] = CamPs2Y / -100.0; \
    static_fields[17] = CamPs2Z / -100.0; \
} while (0)
