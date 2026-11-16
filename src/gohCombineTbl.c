#include "types.h"
#include "cmdevilresps2_cs.h"
#include "dat.h"
#include "evtbit.h"
#include "evtmoon.h"
#include "gohAccidentKN.h"
#include "gohAccidentLR.h"
#include "gohaccident.h"
#include "gohcombinetbl.h"
#include "gohmain.h"
#include "sbtlsub.h"

typedef struct gohData_t gohData_t;
typedef struct gohResult_t gohResult_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

u8 *gohCombine;

// 0x1b92500
void gohResultUnit(gohResult_t *pResult, gohData_t *pData, sdatUnitWork_t *pDevil1, sdatUnitWork_t *pDevil2) {
  s32 v9;
  sdatUnitWork_t *Devil;
  s32 devilid;

  v9 = gohNormal(pData, &pResult->Devil, pDevil1, pDevil2);
  Devil = pResult->Devil;
  pResult->m_iType = v9;
  devilid = pDevil1->devilid;
  Devil->badstatus = 0;
  gohCreateGoodbyMes(pData, devilid, pDevil2->devilid);
}

// 0x1b92b10
s32 gohGift(gohResult_t *pResult, sdatUnitWork_t *pBirthDevil, sdatUnitWork_t *pDevil1, sdatUnitWork_t *pDevil2) {
  void *v9;
  void *v10;
  void *v11;
  s32 PlayerStance;
  s32 v13;

  v9 = Allocate(Project_CMAkuma);
  _ctor_29424192(v9, pDevil1, 0);
  v10 = Allocate(Project_CMAkuma);
  _ctor_29424192(v10, pDevil2, 0);
  v11 = Allocate(Project_CMAkuma);
  _ctor_29424192(v11, pBirthDevil, 0);
  PlayerStance = datGetPlayerStance();
  v13 = ExecuteCombHitokotoMessage(v11, PlayerStance, v9, v10, 0);
  if (v13)
  {
    pResult->m_iMesNo = v13;
    ExecuteGiftItemNo(v11, GBWK->player->para->level, 0);
    pResult->m_iDevilNo = GetGiftDevilNo(v11, 0);
    pResult->m_iItemNo = GetGiftItemNo(v11, 0);
    pResult->m_iItemNum = GetGiftItemNum(v11, 0);
    pResult->m_iDvlReport = GetGiftDvlReport(v11, 0);
  }
  return v13;
}

// 0x1b92c90
gohAccidentKN gohChkAccident(gohData_t *pData) {
  s32 ForcedAccident;
  CMAccident *v5;
  s32 m_sCombCnt;
  CMAccident *v8;
  s32 Age;
  CMAccident *v10;
  s32 Age16;
  CMAccident *v12;
  s32 level;
  CMAccident *v15;
  CMAccident *v16;
  s32 v17;
  bool v18;
  s32 v19;
  __int128 v21;
  CMAccident *v22;
  sdatUnitWork_t *combiDevil1;
  sdatUnitWork_t *combiDevil2;
  sdatUnitWork_t *stock_id;
  sdatUnitWork_t *v27;
  CMAccident *v29;
  CMAccident *v30;
  System_Collections_Generic_List_Enumerator_T__o v32;
  System_Collections_Generic_List_Enumerator_T__o v33;

  memset(&v33, 0, sizeof(v33));
  if (s_pcInst)
    Clear(s_pcInst);
  ForcedAccident = pData->ForcedAccident;
  v5 = s_pcInst;
  if (v5)
    v5->m_eForceAccident = ForcedAccident;
  m_sCombCnt = GBWK->karte_list->m_sCombCnt;
  v8 = s_pcInst;
  if (v8)
    v8->m_iCombineCnt = m_sCombCnt + 1;
  Age = evtMoonGetAge();
  v10 = s_pcInst;
  if (!v10)
    goto LABEL_23;
  goto LABEL_22;
  if (v10)
LABEL_22:
    SetMoonAge(v10, Age, 0);
LABEL_23:
  Age16 = evtMoonGetAge16();
  v12 = s_pcInst;
  if (v12)
    SetMoonAge16(v12, Age16, 0);
  level = GBWK->player->para->level;
  v15 = s_pcInst;
  if (v15)
    SetHeroLevel(v15, level, 0);
  v16 = s_pcInst;
  if (!v16)
    goto LABEL_37;
  goto LABEL_36;
  if (v16)
LABEL_36:
    v16->m_eLuckRank = 3;
LABEL_37:
  v17 = ChgRaceKind_29458896(pData->m_eResultType, 0);
  s_pcInst->m_eRaceKind = v17;
  v18 = !evtBitCheck(65);
  s_pcInst->m_bLimitFlag = v18;
  v19 = !evtBitCheck(65);
  _GetEnumerator(&v32, sMCombSpTbl);
  v33._current = v32._current;
  v21 = *(_OWORD *)&v32._list;
  v32._list = 0;
  *(u64 *)&v32._index = &v33;
  *(_OWORD *)&v33._list = v21;
  while (_MoveNext(&v33))
    v19 |= CheckBirthDevil_29464848(v33._current, pData->BirthDevil->devilid, 0)
        && v17 != 5;
  _Dispose(&v33);
  v22 = s_pcInst;
  v22->m_bProhibitFlag = v19 & 1;
  SetNormalDevilNo(v22, pData->BirthDevil->devilid, 0);
  if (pData->m_eCombineType2 == 4)
  {
    combiDevil1 = pData->combiDevil1;
    combiDevil2 = pData->combiDevil2;
    goto LABEL_57;
  }
  stock_id = GBWK->player->stock_id;
  combiDevil1 = stock_id[gohGetSelDevilStockIndex(pData, 0)];
  v27 = GBWK->player->stock_id;
  combiDevil2 = v27[gohGetSelDevilStockIndex(pData, 1)];
LABEL_57:
  SetStateFlag(s_pcInst, combiDevil1, combiDevil2, 0);
  pData->AccidentFlag = 0;
  v29 = s_pcInst;
  if (v29)
  {
    Decide(v29, 0);
    if (s_pcInst->m_iTypeCnt)
      pData->AccidentFlag = 1;
  }
  v30 = s_pcInst;
  if (v30)
    return v30->m_eKind;
  else
    return 0;
}

// 0x1b93350
s32 gohAccidentDevil(gohData_t *pData) {
  sdatUnitWork_t *p_BirthDevil;
  sdatUnitWork_t *BirthDevil;
  void *v5;
  void *cAkuma;

  p_BirthDevil = &pData->BirthDevil;
  BirthDevil = pData->BirthDevil;
  v5 = Allocate(Project_CMAkuma);
  _ctor_29424192(v5, BirthDevil, 0);
  cAkuma = v5;
  Execute(s_pcInst, &cAkuma, 0);
  Store(cAkuma, p_BirthDevil, 0);
  return cAkuma->m_iDevilNo;
}

// 0x1b925a0
s32 gohNormal(gohData_t *pData, sdatUnitWork_t *pBirthDevil, sdatUnitWork_t *pDevil1, sdatUnitWork_t *pDevil2) {
  void *v9;
  void *v10;
  void *v11;
  s32 v12;
  void *v13;
  void *monitor;
  s64 v15;
  s64 v16;
  void *v17;
  void *v18;
  s64 v19;
  u32 v20;
  u32 klass;
  s64 v22;
  void *v23;
  s32 v24;
  s32 v25;
  bool v26;
  char v27;
  char *v28;

  v9 = Allocate(Project_CMAkuma);
  _ctor_29424192(v9, pDevil1, 0);
  v10 = Allocate(Project_CMAkuma);
  _ctor_29424192(v10, pDevil2, 0);
  v11 = Allocate(Project_CMAkuma);
  _ctor(v11, 0);
  v12 = CombNormal(v11, v9, v10, 0);
  if (v12)
  {
    v13 = NewSpecific(EMParam, 8u);
    InitializeArray_55364416(v13, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__33C621957A75E34E6EF62222B83D41BCEF4ADAE1016E05AF7A33DE7BB9B600C4, 0);
    monitor = v13[1].monitor;
    v15 = (u64)monitor << 32;
    v16 = (s32)monitor;
    v17 = Allocate(Project_CMAkuma);
    _ctor(v17, 0);
    (v17->klass->vtable._10_SetDevilNo.methodPtr)(v17, (u32)v11->m_iDevilNo, v17->klass->vtable._10_SetDevilNo.method);
    if (v12 == 5)
    {
      if (((s_pcInst->klass->vtable._10_IsFullMoon.methodPtr)(s_pcInst, s_pcInst->klass->vtable._10_IsFullMoon.method) & 1) != 0)
      {
        ClearActSkill(v17, 0);
      }
      else
      {
        if (v15 < 1)
        {
LABEL_24:
          Store(v11, pBirthDevil, 0);
          return ChgRaceKind(v12, 0);
        }
        v18 = v13 + 2;
        if (v16 <= 1)
          v19 = 1;
        else
          v19 = v16;
        do
        {
          v20 = (v11->klass->vtable._6_GetParamInteger.methodPtr)(v11, LODWORD(v18->klass), v11->klass->vtable._6_GetParamInteger.method);
          klass = v18->klass;
          v18 = ((char *)v18 + 4);
          (v17->klass->vtable._7_SetParamInteger.methodPtr)(v17, klass, v20, v17->klass->vtable._7_SetParamInteger.method);
          --v19;
        }
        while (v19);
      }
    }
    if (v15 >= 1)
    {
      v22 = 0;
      v23 = v13 + 2;
      if (v16 <= 1)
        v16 = 1;
      do
      {
        v24 = (v11->klass->vtable._6_GetParamInteger.methodPtr)(v11, *((u32 *)&v23->klass + v22), v11->klass->vtable._6_GetParamInteger.method);
        v25 = (v17->klass->vtable._6_GetParamInteger.methodPtr)(v17, *((u32 *)&v23->klass + v22), v17->klass->vtable._6_GetParamInteger.method);
        if (v24)
          v26 = v25 == v24;
        else
          v26 = 1;
        v27 = !v26;
        v28 = (char *)pData->m_abActSkillFlag + v22++;
        v28[32] = v27;
      }
      while (v16 != v22);
    }
    goto LABEL_24;
  }
  return ChgRaceKind(v12, 0);
}

// 0x1b93420
s32 gohNormalSearchi(sdatUnitWork_t *pBirthDevil, sdatUnitWork_t *pDevil1, sdatUnitWork_t *pDevil2) {
  void *v7;
  void *v8;
  void *v9;
  s32 v10;
  void *v11;
  void *monitor;
  s64 v13;
  s64 v14;
  void *v15;
  void *v16;
  s64 v17;
  u32 v18;
  u32 klass;
  void *v20;
  u32 v21;

  v7 = Allocate(Project_CMAkuma);
  _ctor_29424192(v7, pDevil1, 0);
  v8 = Allocate(Project_CMAkuma);
  _ctor_29424192(v8, pDevil2, 0);
  v9 = Allocate(Project_CMAkuma);
  _ctor(v9, 0);
  v10 = CombNormal(v9, v7, v8, 0);
  if (v10)
  {
    v11 = NewSpecific(EMParam, 8u);
    InitializeArray_55364416(v11, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__33C621957A75E34E6EF62222B83D41BCEF4ADAE1016E05AF7A33DE7BB9B600C4, 0);
    monitor = v11[1].monitor;
    v13 = (u64)monitor << 32;
    v14 = (s32)monitor;
    v15 = Allocate(Project_CMAkuma);
    _ctor(v15, 0);
    (v15->klass->vtable._10_SetDevilNo.methodPtr)(v15, (u32)v9->m_iDevilNo, v15->klass->vtable._10_SetDevilNo.method);
    if (v10 == 5)
    {
      if (((s_pcInst->klass->vtable._10_IsFullMoon.methodPtr)(s_pcInst, s_pcInst->klass->vtable._10_IsFullMoon.method) & 1) != 0)
      {
        ClearActSkill(v15, 0);
      }
      else
      {
        if (v13 < 1)
        {
LABEL_18:
          Store(v9, pBirthDevil, 0);
          return ChgRaceKind(v10, 0);
        }
        v16 = v11 + 2;
        if (v14 <= 1)
          v17 = 1;
        else
          v17 = v14;
        do
        {
          v18 = (v9->klass->vtable._6_GetParamInteger.methodPtr)(v9, LODWORD(v16->klass), v9->klass->vtable._6_GetParamInteger.method);
          klass = v16->klass;
          v16 = ((char *)v16 + 4);
          (v15->klass->vtable._7_SetParamInteger.methodPtr)(v15, klass, v18, v15->klass->vtable._7_SetParamInteger.method);
          --v17;
        }
        while (v17);
      }
    }
    if (v13 >= 1)
    {
      v20 = v11 + 2;
      if (v14 <= 1)
        v14 = 1;
      do
      {
        (v9->klass->vtable._6_GetParamInteger.methodPtr)(v9, LODWORD(v20->klass), v9->klass->vtable._6_GetParamInteger.method);
        v21 = v20->klass;
        v20 = ((char *)v20 + 4);
        (v15->klass->vtable._6_GetParamInteger.methodPtr)(v15, v21, v15->klass->vtable._6_GetParamInteger.method);
        --v14;
      }
      while (v14);
    }
    goto LABEL_18;
  }
  return ChgRaceKind(v10, 0);
}

// 0x1b92830
void gohCreateGoodbyMes(gohData_t *pData, s32 iDevilNo1, s32 iDevilNo2) {
  s32 *v7;
  DEVILDATA_WORK *DevilData;
  u64 v9;
  s32 kucyo;
  s16 *m_aiGoodbyMesNo;
  s64 v12;
  int16x8_t v13;
  int16x8_t v14;
  int16x8_t *v15;
  int16x8_t *v16;
  s64 v17;
  int16x8_t v18;
  int16x8_t v19;
  int16x8_t v20;
  int16x8_t v21;
  int16x8_t v22;
  s64 v23;
  s16 *v24;
  s16 *v25;
  s16 v26;
  s32 *v27;
  s64 v28;
  s64 v29;
  s64 v30;
  u64 v31;
  s64 v32;
  s16 *v33;
  s16 v34;
  s16 v35;
  s16 *v36;
  s16 *v37;
  s16 v38;
  s16 v39;
  s32 v40;
  int32x4_t v41;
  int32x4_t v42;
  int32x4_t v43;
  int32x4_t v44;
  int32x4_t v45;
  int32x4_t *v46;
  s64 v47;
  int32x4_t v48;
  int32x4_t v49;
  s32 v50;
  s16 *v51;
  s64 v52;
  s32 v53;
  s32 v54;
  s16 *v55;
  s16 v56;

  v7 = NewSpecific(s32, 2u);
  v7[0] = sBtlGetDevilData(iDevilNo1, -1)->kucyo;
  DevilData = sBtlGetDevilData(iDevilNo2, -1);
  v9 = *(u64 *)((char *)v7 + 24);
  kucyo = DevilData->kucyo;
  v7[1] = kucyo;
  if ((s32)v9 >= 1)
  {
    v9 = (u32)v9;
    m_aiGoodbyMesNo = pData->m_aiGoodbyMesNo;
    if ((u32)v9 <= 1u)
      v9 = 1;
    if (v9 < 0x20)
    {
      v12 = 0;
LABEL_13:
      v23 = v9 - v12;
      v24 = ((s64)(char *)v7 + 4 * v12 + 32);
      v25 = &m_aiGoodbyMesNo[v12];
      do
      {
        v26 = *v24;
        v24 += 2;
        --v23;
        *v25++ = 7 * v26 + 45;
      }
      while (v23);
      goto LABEL_15;
    }
    v13.n128_u64[0] = 0x7000700070007LL;
    v13.n128_u64[1] = 0x7000700070007LL;
    v14.n128_u64[0] = 0x2D002D002D002DLL;
    v14.n128_u64[1] = 0x2D002D002D002DLL;
    v12 = (u32)v9 & 0xFFFFFFE0;
    v15 = &m_aiGoodbyMesNo[24];
    v16 = &v7[8];
    v17 = v12;
    do
    {
      v17 -= 32;
      v18 = vuzp1q_s16(*v16, v16[1]);
      v19 = vuzp1q_s16(v16[2], v16[3]);
      v20 = vmlaq_s16(v14, vuzp1q_s16(v16[-2], v16[-1]), v13);
      v22 = v16[4];
      v21 = v16[5];
      v16 += 8;
      v15[-3] = v20;
      v15[-2] = vmlaq_s16(v14, v18, v13);
      v15[-1] = vmlaq_s16(v14, v19, v13);
      *v15 = vmlaq_s16(v14, vuzp1q_s16(v22, v21), v13);
      v15 += 4;
    }
    while (v17);
    if (v9 != v12)
      goto LABEL_13;
  }
LABEL_15:
  if (v7[0] == kucyo)
  {
    v27 = NewSpecific(s32, 3u);
    v28 = *(u64 *)((char *)v27 + 24);
    v29 = v27;
    v30 = (s32)v28;
    if (v28 << 32 >= 1)
    {
      if ((s32)v28 <= 1)
        v31 = 1;
      else
        v31 = (s32)v28;
      if (v31 >= 0x10)
      {
        v41.n128_u64[0] = 0x400000004LL;
        v41.n128_u64[1] = 0x400000004LL;
        v42.n128_u64[0] = 0x800000008LL;
        v42.n128_u64[1] = 0x800000008LL;
        v43 = xmmword_3CFBEA0;
        v44.n128_u64[0] = 0xC0000000CLL;
        v44.n128_u64[1] = 0xC0000000CLL;
        v45.n128_u64[0] = 0x1000000010LL;
        v45.n128_u64[1] = 0x1000000010LL;
        v32 = v31 & 0x7FFFFFFFFFFFFFF0LL;
        v46 = &v27[12];
        v47 = v31 & 0x7FFFFFFFFFFFFFF0LL;
        do
        {
          v48 = vaddq_s32(v43, v42);
          v47 -= 16;
          v46[-3] = v43;
          v46[-2] = vaddq_s32(v43, v41);
          v49 = vaddq_s32(v43, v44);
          v43 = vaddq_s32(v43, v45);
          v46[-1] = v48;
          *v46 = v49;
          v46 += 4;
        }
        while (v47);
        if (v31 == v32)
          goto LABEL_27;
      }
      else
      {
        v32 = 0;
      }
      do
      {
        *(u32 *)((s64)&v27[0] + 4 * v32) = v32;
        ++v32;
      }
      while (v31 != v32);
    }
LABEL_27:
    v50 = sub_1905740((u16)v28, 0);
    v51 = pData->m_aiGoodbyMesNo;
    v52 = 4 * v50;
    v53 = (u16)v51[0] + *(u32 *)(v29 + 32 + v52);
    *(u32 *)(v29 + 32 + v52) = *(u32 *)(v29 + 32 + 4 * (v30 - 1));
    v51[0] = v53;
    v54 = sub_1905740((u16)(v30 - 1), 0);
    v55 = pData->m_aiGoodbyMesNo;
    v40 = *(u32 *)(v29 + 32 + 4 * v54);
    v56 = v55[1];
    v37 = &v55[1];
    v38 = v56;
    goto LABEL_28;
  }
  v33 = pData->m_aiGoodbyMesNo;
  v34 = v33[0];
  v35 = sub_1905740(3, 0);
  v36 = pData->m_aiGoodbyMesNo;
  v33[0] = v34 + v35;
  v39 = v36[1];
  v37 = &v36[1];
  v38 = v39;
  LOWORD(v40) = sub_1905740(3, 0);
LABEL_28:
  *v37 = v38 + v40;
}

// 0x1b93340
gohAccidentLR gohGetLuckRank(void) {
  return 3;
}
