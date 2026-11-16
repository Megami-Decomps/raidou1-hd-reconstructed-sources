#include "types.h"
#include "GOH_KARTE_SORTMODE.h"
#include "SKLID.h"
#include "achievement.h"
#include "dat.h"
#include "dvl.h"
#include "evtbit.h"
#include "goh.h"
#include "gohcalc.h"
#include "gohinit.h"
#include "raijindlc.h"
#include "sbtl.h"
#include "sbtlcalc.h"
#include "sbtlsub.h"
#include "slmain.h"

#define GOH_DEVIL_LIST_MAX 12
#define GOH_DEVIL_STOCK_MAX 32
#define GOH_KARTE_LINE_MAX 10
#define GOH_SWORD_LINE_MAX 11
#define GOH_BASESWORD_LINE_MAX 5
#define GOH_KARTE_DEVIL_MAX 80
#define GOH_RECOVER_LINE_MAX 10
#define GOH_RANK1_COUNT 0
#define GOH_RANK2_COUNT 21
#define GOH_RANK3_COUNT 36
#define GOH_RANK4_COUNT 56
#define c_iGOH_DVL_MAX 80
#define c_iGOH_PARAM_MAX 40

typedef enum {
    GOH_PARAM_TYPE_INIT = -1,
    GOH_PARAM_TYPE_STR = 0,
    GOH_PARAM_TYPE_TEC = 1,
    GOH_PARAM_TYPE_VIT = 2,
    GOH_PARAM_TYPE_LUCK = 3,
    GOH_PARAM_TYPE_MAX = 4,
} GOH_PARAM_TYPE;

typedef struct gohGeneralList_t gohGeneralList_t;
typedef struct gohKarteList_t gohKarteList_t;
typedef struct gohKarteUnit_t gohKarteUnit_t;
typedef struct gohSortedDevilList_t gohSortedDevilList_t;
typedef struct gohTable_t gohTable_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

gohKarteList_t *gBackupKarteList;
static bool sortKartePro;

// 0x1b8bcd0
void gohStrongSwordFlag(s32 DevilID, s32 Mode) {
  u32 v6;
  s32 v7;
  s64 v9;
  s64 v11;

  v6 = datCheckStrongSwordDevil(DevilID);
  if (!v6)
    return;
  v7 = v6;
  if (Mode)
  {
    if (v6 - 2618 < 0xFFFFFFC6)
      goto LABEL_10;
    goto LABEL_9000;
    if ((u32)(v7 - 2618) < 0xFFFFFFC6)
    {
LABEL_10:
LABEL_11:
      v9 = (s64)GBWK->EventBit + 4 * (v7 / 32);
      *(u32 *)(v9 + 32) |= 1 << v7;
      return;
    }
LABEL_9000:
    evtBitKityouItemAdd(v7);
    goto LABEL_11;
  }
  v11 = (s64)GBWK->EventBit + 4 * (v7 / 32);
  *(u32 *)(v11 + 32) &= ~(1 << v7);
  return;
}

// 0x1b8bea0
s32 gohTablCheckEventDevil(gohTable_t *pTable, s32 DevilID) {
  s32 v5;
  s32 result;

  if (GetLength(pTable->pEventDevil, 0) < 1)
    return 1;
  v5 = 0;
  while (GetTblDate(pTable->pEventDevil, v5, 0)->DevilID != (s64)DevilID)
  {
    if (++v5 >= GetLength(pTable->pEventDevil, 0))
      return 1;
  }
  result = GetTblDate(pTable->pEventDevil, v5, 0)->Flag;
  if (result)
    return evtBitCheck(result);
  return result;
}

// 0x1b8bf50
void gohTablRegistEventDevil(gohTable_t *pTable) {
  s32 v3;
  u32 Flag;

  if (GetLength(pTable->pEventDevil, 0) >= 1)
  {
    v3 = 0;
    do
    {
      Flag = GetTblDate(pTable->pEventDevil, v3, 0)->Flag;
      if (Flag)
        evtBitCheck(Flag);
      ++v3;
    }
    while (v3 < GetLength(pTable->pEventDevil, 0));
  }
}

// 0x1b8bfd0
bool gohCheckEventDevil(s32 DevilID) {
  gohTable_t *Table;

  Table = gohGetTable();
  if (!Table)
    return 0;
  return gohTablCheckEventDevil(Table, DevilID) != 0;
}

// 0x1b8c080
s32 gohAccidentFailDevilNo(s32 idx) {
  u16 *pAccidentFail;

  pAccidentFail = gohGetTable()->pAccidentFail;
  if (SLODWORD(pAccidentFail->max_length) > idx)
    return pAccidentFail[idx];
  return 0;
}

// 0x1b8c140
u32 gohAccidentFailDevilCnt(void) {
  return gohGetTable()->pAccidentFail->max_length;
}

// 0x1b8c1a0
s32 gohSortedSkillPrioHigherCallback(void *op1, void *op2) {
  u32 klass;
  u32 v8;
  s32 v10;

  klass = op1[1].klass;
  v8 = op2[1].klass;
  if (klass < v8)
    return -1;
  if (klass > v8)
    return 1;
  if ((HIDWORD(op1[1].monitor) & 8u) <= (HIDWORD(op2[1].monitor) & 8u))
    v10 = 0;
  else
    v10 = -1;
  if ((HIDWORD(op1[1].monitor) & 8u) >= (HIDWORD(op2[1].monitor) & 8u))
    return v10;
  else
    return 1;
}

// 0x1b8c2c0
s32 gohSortedSkillPrioLowerCallback(void *op1, void *op2) {
  u32 klass;
  u32 v8;
  s32 v10;

  klass = op1[1].klass;
  v8 = op2[1].klass;
  if (klass < v8)
    return 1;
  if (klass > v8)
    return -1;
  if ((HIDWORD(op1[1].monitor) & 8u) <= (HIDWORD(op2[1].monitor) & 8u))
    v10 = 0;
  else
    v10 = -1;
  if ((HIDWORD(op1[1].monitor) & 8u) >= (HIDWORD(op2[1].monitor) & 8u))
    return v10;
  else
    return 1;
}

// 0x1b8c3e0
s32 gohSortedDevilListCallback(void *op1, void *op2) {
  s32 klass;
  s32 v8;
  s32 klass_high;
  s32 v11;

  klass = op1[1].klass;
  v8 = op2[1].klass;
  if (klass > v8)
    return 1;
  if (klass < v8)
    return -1;
  klass_high = HIDWORD(op1[1].klass);
  v11 = HIDWORD(op2[1].klass);
  if (klass_high > v11)
    return 1;
  if (klass_high >= v11)
    return 0;
  return -1;
}

// 0x1b8c500
void gohCreateSortedDevilList(gohSortedDevilList_t *pList, gohTable_t *pTable) {
  s32 v5;
  DEVILDATA_WORK *DevilData;
  s64 Nums;
  gohDevilData_t *v8;
  s64 v9;
  gohDevilData_t *v11;
  void *pData;
  s32 v13;
  void *v14;
  s64 v15;
  s64 v16;
  gohDevilData_t *v17;
  s64 v18;

  v5 = 0;
  pList->Nums = 0;
  do
  {
    if (!sBtlGetDevilData(v5, -1)->kuda_id)
      goto LABEL_5;
    if (!gohTablCheckEventDevil(pTable, v5))
      goto LABEL_5;
    if ((datCheckSameDevil(v5) & 0x80000000) == 0)
      goto LABEL_5;
    v11 = pList->pData[pList->Nums];
    DevilData = sBtlGetDevilData(v5, -1);
    Nums = pList->Nums;
    v11->KudaRace = DevilData->kuda_id;
    v8 = pList->pData[Nums];
    v8->Level = sBtlGetDevilData(v5, -1)->level;
    v9 = pList->Nums;
    pList->pData[v9]->DevilID = v5;
    pList->Nums = v9 + 1;
LABEL_5:
    ++v5;
  }
  while (v5 != 544);
  pData = pList->pData;
  v13 = pList->Nums;
  v14 = Allocate(System_Func_object__object__int_);
  object__int____ctor(v14, 0, Method_Project_gohCalc_SortedDevilListCallback__, 0);
  Sort_object_(pData, v13, v14);
  v15 = (u32)pList->Nums;
  if ((s32)v15 >= 1)
  {
    v16 = (u32)(v15 - 1);
    v17 = &pList->pData[1];
    do
    {
      v18 = *(v17 - 1);
      if (v18)
      {
        *(u32 *)(v18 + 28) = 0;
      }
      else if (v16 && *(u32 *)sub_10 == v17->KudaRace)
      {
        HIDWORD(off_18) = 1;
      }
      else
      {
        HIDWORD(off_18) = 2;
      }
      --v16;
      ++v17;
      --v15;
    }
    while (v15);
  }
}

// 0x1b8c7a0
s32 gohLevelSortedUnitListCallback(void *op1, void *op2) {
  s32 monitor_low;
  s32 v8;
  s32 klass_high;
  s32 kuda_id;
  s32 v13;
  s32 v15;
  s32 v17;
  s32 v18;

  monitor_low = SLOBYTE(op1[1].monitor);
  v8 = SLOBYTE(op2[1].monitor);
  if (monitor_low > v8)
    return 1;
  if (monitor_low < v8)
    return -1;
  klass_high = SHIWORD(op1[1].klass);
  kuda_id = sBtlGetDevilData(klass_high, -1)->kuda_id;
  v13 = SHIWORD(op2[1].klass);
  if (kuda_id > sBtlGetDevilData(v13, -1)->kuda_id)
    return 1;
  v15 = SHIWORD(op1[1].klass);
  v17 = sBtlGetDevilData(v15, -1)->kuda_id;
  v18 = SHIWORD(op2[1].klass);
  if (v17 >= sBtlGetDevilData(v18, -1)->kuda_id)
    return 0;
  else
    return -1;
}

// 0x1b8ca70
s32 gohRaceSortedUnitListCallback(void *op1, void *op2) {
  s32 klass_high;
  s32 kuda_id;
  s32 v10;
  s32 v12;
  s32 v13;
  s32 v15;
  s32 v16;
  s32 monitor_low;
  s32 v19;

  klass_high = SHIWORD(op1[1].klass);
  kuda_id = sBtlGetDevilData(klass_high, -1)->kuda_id;
  v10 = SHIWORD(op2[1].klass);
  if (kuda_id > sBtlGetDevilData(v10, -1)->kuda_id)
    return 1;
  v13 = SHIWORD(op1[1].klass);
  v15 = sBtlGetDevilData(v13, -1)->kuda_id;
  v16 = SHIWORD(op2[1].klass);
  v12 = -1;
  if (v15 < sBtlGetDevilData(v16, -1)->kuda_id)
    return v12;
  monitor_low = SLOBYTE(op1[1].monitor);
  v19 = SLOBYTE(op2[1].monitor);
  if (monitor_low > v19)
    return 1;
  if (monitor_low >= v19)
    return 0;
  else
    return -1;
}

// 0x1b8cd20
s32 gohFavSortedUnitListCallback(void *op1, void *op2) {
  gohKarteUnit_t *KarteUnit;
  gohKarteUnit_t *v10;
  s32 klass_high;
  _BOOL4 v12;
  gohKarteUnit_t *v13;
  gohKarteUnit_t *v14;
  s32 v15;
  _BOOL4 v16;
  gohKarteUnit_t *v17;
  gohKarteUnit_t *v18;
  s32 v19;
  _BOOL4 v21;
  gohKarteUnit_t *v22;
  gohKarteUnit_t *v23;
  s32 v24;
  s32 monitor_low;
  s32 v27;

  KarteUnit = gohGetKarteUnit(op1, sortKartePro);
  if (KarteUnit)
  {
    v10 = KarteUnit;
    klass_high = SHIWORD(op1[1].klass);
    if (!DlcDevilSelCheck(klass_high))
      goto LABEL_25;
    if (!v10->fav)
      goto LABEL_25;
    v12 = sortKartePro;
    v13 = gohGetKarteUnit(op2, v12);
    if (v13)
    {
      v14 = v13;
      v15 = SHIWORD(op2[1].klass);
      if (!DlcDevilSelCheck(v15))
        return -1;
      if (v14->fav)
        goto LABEL_25;
    }
    return -1;
  }
LABEL_25:
  v16 = sortKartePro;
  v17 = gohGetKarteUnit(op2, v16);
  if (v17)
  {
    v18 = v17;
    v19 = SHIWORD(op2[1].klass);
    if (!DlcDevilSelCheck(v19))
      goto LABEL_42;
    if (!v18->fav)
      goto LABEL_42;
    v21 = sortKartePro;
    v22 = gohGetKarteUnit(op1, v21);
    if (!v22)
      return 1;
    v23 = v22;
    v24 = SHIWORD(op1[1].klass);
    if (!DlcDevilSelCheck(v24))
      return 1;
    if (v23->fav)
      goto LABEL_42;
    return 1;
  }
LABEL_42:
  monitor_low = SLOBYTE(op1[1].monitor);
  v27 = SLOBYTE(op2[1].monitor);
  if (monitor_low > v27)
    return 1;
  if (monitor_low >= v27)
    return 0;
  else
    return -1;
}

// 0x1b8d120
void gohCreateSortedUnitList(s32 UnitNums, sdatUnitWork_t *pUnitList, GOH_KARTE_SORTMODE Mode, bool _pro) {
  bool v8;
  intptr_t *v9;
  void *v10;

  v8 = pro;
  sortKartePro = v8;
  if ((u32)Mode <= 2)
  {
    v9 = (&off_4CD9AE0)[Mode];
    v10 = Allocate(System_Func_object__object__int_);
    object__int____ctor(v10, 0, *v9, 0);
    Sort_object_(pUnitList, UnitNums, v10);
  }
}

// 0x1b8d230
s32 gohUnitListIndex(s32 _unitNum, sdatUnitWork_t *_searchiUnit, sdatUnitWork_t *pUnitList, bool _pro) {
  s64 v6;
  s64 v7;
  sdatUnitWork_t *m_Items;

  if (!searchiUnit || unitNum < 1)
    return -1;
  v6 = 0;
  v7 = unitNum;
  m_Items = pUnitList;
  while (!SameDataCheck(searchiUnit, m_Items[v6], 0))
  {
    if (v7 == ++v6)
      return -1;
  }
  return v6;
}

// 0x1b8d2c0
s32 gohCheckHaveSkill(sdatUnitWork_t *pUnit, SKLID SkillID) {
  SKLID *haveskill;

  haveskill = pUnit->haveskill;
  if (haveskill[0] == SkillID)
    return 1;
  if (haveskill[1] == SkillID)
    return 1;
  if (haveskill[2] == SkillID)
    return 1;
  if (haveskill[3] == SkillID)
    return 1;
  if (haveskill[4] == SkillID)
    return 1;
  if (haveskill[5] == SkillID)
    return 1;
  if (haveskill[6] == SkillID)
    return 1;
  if (haveskill[7] == SkillID)
    return 1;
  if (haveskill[8] == SkillID)
    return 1;
  if (haveskill[9] == SkillID)
    return 1;
  if (haveskill[10] == SkillID)
    return 1;
  if (haveskill[11] == SkillID)
    return 1;
  if (haveskill[12] == SkillID)
    return 1;
  if (haveskill[13] == SkillID)
    return 1;
  if (haveskill[14] == SkillID)
    return 1;
  if (haveskill[15] == SkillID)
    return 1;
  return haveskill[16] == SkillID;
}

// 0x1b8d420
s32 gohDelDevilFromGeneralList(gohGeneralList_t *pGeneralList, s32 Index) {
  s32 m_DevilCnt;
  s32 v4;
  s64 v6;
  s64 v7;
  s64 v8;
  char *v9;
  sdatUnitWork_t *m_pDevil;
  char *v11;
  s64 v12;
  void *v13;
  Il2CppClass **v16;

  m_DevilCnt = pGeneralList->m_DevilCnt;
  if (m_DevilCnt <= Index)
    return 0;
  v4 = Index;
  if (m_DevilCnt - 1 > Index)
  {
    v6 = 0;
    v7 = 8 * Index;
    v8 = 32;
    do
    {
      m_pDevil = pGeneralList->m_pDevil;
      v11 = (char *)m_pDevil + v7;
      v12 = (s64)m_pDevil + 8 * v6 + v7;
      v13 = *(void **)(v12 + 40);
      *(u64 *)(v12 + 32) = v13;
      v8 += 8;
      v9 = (char *)pGeneralList->m_DevilVal + 4 * v4 + 4 * v6++;
      *((u32 *)v9 + 8) = *((u32 *)v9 + 9);
    }
    while (v4 + v6 < pGeneralList->m_DevilCnt - 1);
    v4 += v6;
  }
  v16 = &pGeneralList->m_pDevil->obj.klass + v4;
  v16[4] = 0;
  pGeneralList->m_DevilVal[v4] = 0;
  --pGeneralList->m_DevilCnt;
  return 1;
}

// 0x1b8d540
bool gohKarteIsInvalidateSkillNo(SKLID iSkillNo) {
  bool v2;

  v2 = iSkillNo != 288;
  if (iSkillNo == 149)
    v2 = 0;
  return iSkillNo && v2;
}

// 0x1b8d560
SKLID gohKarteUnitGetSkill(gohKarteUnit_t *psKarteUnit, s64 iIdx) {
  SKLID *Skill;

  Skill = psKarteUnit->Skill;
  if (SLODWORD(Skill->max_length) <= iIdx)
    return 0;
  else
    return Skill[iIdx];
}

// 0x1b8d5e0
void gohKarteUnitSetSkill(gohKarteUnit_t *psKarteUnit, s64 iIdx, SKLID uSkillNo) {
  SKLID *Skill;

  Skill = psKarteUnit->Skill;
  if (SLODWORD(Skill->max_length) <= iIdx)
    return;
  Skill[iIdx] = uSkillNo;
  return;
}

// 0x1b8d670
bool gohKarteUnitGetReserveSkillFlag(gohKarteUnit_t *psKarteUnit, s64 iIdx) {
  return ((psKarteUnit->RsvSklFlag >> iIdx) & 1) == 0;
}

// 0x1b8d690
void gohKarteUnitSetReserveSkillFlag(gohKarteUnit_t *psKarteUnit, s64 iIdx, bool bFlag) {
  s32 RsvSklFlag;
  s32 v5;

  RsvSklFlag = psKarteUnit->RsvSklFlag;
  v5 = RsvSklFlag | (1 << iIdx);
  if (bFlag)
    LOBYTE(v5) = RsvSklFlag & ~(1 << iIdx);
  psKarteUnit->RsvSklFlag = v5;
}

// 0x1b8d6c0
bool gohKarteAllRegCheck(s32 _devilId) {
  gohKarteList_t *karte_list;
  s64 RegistNums;
  s64 m_Items;
  s64 v7;
  bool result;
  s64 karte2WakuCnt;
  gohKarteUnit_t *Karte2Unit;
  s64 v11;
  gohKarteUnit_t *v12;
  s64 v13;
  s32 v14;

  karte_list = GBWK->karte_list;
  RegistNums = (u32)karte_list->RegistNums;
  if ((s32)RegistNums < 1)
    goto LABEL_13;
  m_Items = karte_list->KarteUnit;
  v7 = 0xFFFFFFFFLL;
  while (*(s16 *)(*(u64 *)m_Items + 22) != devilId)
  {
    --v7;
    --RegistNums;
    m_Items += 8;
    if (!RegistNums)
      goto LABEL_13;
  }
  if (v7)
    return 1;
LABEL_13:
  karte2WakuCnt = (u32)karte_list->karte2WakuCnt;
  if ((s32)karte2WakuCnt < 1)
    return 0;
  Karte2Unit = karte_list->Karte2Unit;
  v11 = karte2WakuCnt - 1;
  v12 = Karte2Unit;
  do
  {
    v13 = (s64)*v12++;
    v14 = *(s16 *)(v13 + 22);
    result = v14 == devilId;
  }
  while (v14 != devilId && v11-- != 0);
  return result;
}

// 0x1b8d820
s32 gohKarteSearchFromKarteList(s32 DevilID, gohKarteList_t *pKarteList, bool _pro) {
  s64 v4;
  s64 v5;
  s64 v6;
  s64 v7;

  v4 = 56;
  if (!pro)
    v4 = 16;
  v5 = 24;
  v6 = *(u32 *)((char *)&pKarteList->klass + v4);
  if (pro)
    v5 = 48;
  if ((s32)v6 < 1)
    return -1;
  v7 = 0;
  while (*(s16 *)(*((u64 *)&(*(gohKarteList_t **)((char *)&pKarteList->klass + v5))->_1.byval_arg.data + v7) + 22) != DevilID)
  {
    if (v6 == ++v7)
      return -1;
  }
  return v7;
}

// 0x1b8d8a0
s32 gohKarteSearchUcFromKarteList(s32 DevilID, u32 _uniqCode, gohKarteList_t *pKarteList, bool _pro) {
  s64 v5;
  s64 v6;
  s64 v7;
  s64 v8;
  s64 v9;

  v5 = 56;
  if (!pro)
    v5 = 16;
  v6 = 24;
  v7 = *(u32 *)((char *)&pKarteList->klass + v5);
  if (pro)
    v6 = 48;
  if ((s32)v7 < 1)
    return -1;
  v8 = 0;
  while (1)
  {
    v9 = *((u64 *)&(*(gohKarteList_t **)((char *)&pKarteList->klass + v6))->_1.byval_arg.data + v8);
    if (*(u32 *)(v9 + 120) == uniqCode && *(s16 *)(v9 + 22) == DevilID)
      break;
    if (v7 == ++v8)
      return -1;
  }
  return v8;
}

// 0x1b8d920
s32 gohKarteCreateUnitFromKarteList(s32 DevilID, sdatUnitWork_t *pUnit, gohKarteList_t *pKarteList) {
  s64 RegistNums;
  gohKarteUnit_t *KarteUnit;
  s64 v6;

  RegistNums = (u32)pKarteList->RegistNums;
  if ((s32)RegistNums < 1)
    return 0;
  KarteUnit = pKarteList->KarteUnit;
  v6 = 0;
  while (KarteUnit[v6]->DevilID != DevilID)
  {
    if (RegistNums == ++v6)
      return 0;
  }
  if ((v6 & 0x80000000) == 0)
  {
    gohKarteCreateUnitFromKarteUnit(pUnit, KarteUnit[v6]);
    return 1;
  }
  return 0;
}

// 0x1b8de40
s32 gohKarteCreateUnitUcFromKarteList(s32 DevilID, u32 _uniqCode, sdatUnitWork_t *pUnit, gohKarteList_t *pKarteList, bool _pro) {
  s64 v6;
  s64 v7;
  s64 v8;
  s64 v9;
  Il2CppType *p_byval_arg;
  s64 v11;
  s64 v12;

  v6 = 16;
  if (pro)
    v6 = 56;
  v7 = 48;
  if (!pro)
    v7 = 24;
  v8 = *(u32 *)((char *)&pKarteList->klass + v6);
  if ((s32)v8 < 1)
    return 0;
  v9 = 0;
  p_byval_arg = &(*(gohKarteList_t **)((char *)&pKarteList->klass + v7))->_1.byval_arg;
  while (1)
  {
    v11 = *((u64 *)&p_byval_arg->data + v9);
    if (*(u32 *)(v11 + 120) == uniqCode && *(s16 *)(v11 + 22) == DevilID)
      break;
    if (v8 == ++v9)
      return 0;
  }
  if ((v9 & 0x80000000) != 0)
    return 0;
  v12 = 24;
  if (pro)
    v12 = 48;
  gohKarteCreateUnitFromKarteUnit(pUnit, *((gohKarteUnit_t *)&(*(gohKarteList_t **)((char *)&pKarteList->klass + v12))->_1.byval_arg.data + v9));
  return 1;
}

// 0x1b8def0
void *gohCreateAllKarteUnitList(void) {
  Il2CppObject *v1;
  gohKarteList_t *karte_list;
  s32 RegistNums;
  s32 karte2WakuCnt;
  void *v6;
  s32 v7;
  s32 v8;
  s64 v9;
  sdatUnitWork_t *v10;
  void *p_monitor;
  sdatUnitWork_t *v13;
  sdatUnitWork_t *v16;
  void *v17;
  s64 v18;
  Il2CppObject *v19;
  u64 *v20;
  s64 v21;
  s64 v22;
  s64 v23;
  void *v24;
  sdatUnitWork_t *v25;
  sdatUnitWork_t *v28;
  void *v29;
  s64 v30;
  Il2CppObject *v31;
  u64 *v32;
  s64 v33;
  s64 v34;

  v1 = Allocate(Project_gohCalc___c__DisplayClass46_0);
  _ctor(v1, 0);
  karte_list = GBWK->karte_list;
  RegistNums = karte_list->RegistNums;
  karte2WakuCnt = karte_list->karte2WakuCnt;
  v6 = Allocate(System_Collections_Generic_List_sdatUnitWork_t_);
  __ctor_48217280(v6, karte2WakuCnt + RegistNums);
  v7 = v6->_size;
  v8 = v6->_version + 1;
  v6->_size = 0;
  v6->_version = v8;
  if (v7 >= 1)
    Clear(v6->_items, 0, v7, 0);
  v9 = 0;
  v10 = &v1[1];
  p_monitor = &v1[1].monitor;
  while (1)
  {
    if (v9 >= GBWK->karte_list->RegistNums)
      break;
    v13 = Allocate(sdatUnitWork_t);
    _ctor(v13, 0);
    v10 = v13;
    v16 = v10;
    gohKarteCreateUnitFromKarteUnit(v16, GBWK->karte_list->KarteUnit[v9]);
    if (v10->devilid)
    {
      if (p_monitor)
      {
        if (_Find(v6, p_monitor))
        {
          goto LABEL_9;
        }
      }
      else
      {
        v17 = Allocate(System_Predicate_sdatUnitWork_t_);
        __ctor(v17, v1, Method_Project_gohCalc___c__DisplayClass46_0__CreateAllKarteUnitList_b__0__, 0);
        v1[1].monitor = v17;
        if (_Find(v6, v17))
        {
          goto LABEL_9;
        }
      }
      v18 = v6->_size;
      v19 = v10;
      v20 = Method_System_Collections_Generic_List_sdatUnitWork_t__Add__;
      ++v6->_version;
      v21 = v6->_items;
      if ((u32)v18 >= *(u32 *)(v21 + 24))
      {
        _AddWithResize(v6, v19, *(const MethodInfo_2DFC660 **)(*(u64 *)(v20[4] + 192) + 112));
      }
      else
      {
        v22 = v21 + 8 * v18;
        v6->_size = v18 + 1;
        *(u64 *)(v22 + 32) = v19;
      }
    }
LABEL_9:
    ++v9;
  }
  v23 = 0;
  v24 = &v1[2];
  while (1)
  {
    if (v23 >= GBWK->karte_list->karte2WakuCnt)
      break;
    v25 = Allocate(sdatUnitWork_t);
    _ctor(v25, 0);
    v10 = v25;
    v28 = v10;
    gohKarteCreateUnitFromKarteUnit(v28, GBWK->karte_list->Karte2Unit[v23]);
    if (v10->devilid)
    {
      if (v24)
      {
        if (_Find(v6, v24))
        {
          goto LABEL_24;
        }
      }
      else
      {
        v29 = Allocate(System_Predicate_sdatUnitWork_t_);
        __ctor(v29, v1, Method_Project_gohCalc___c__DisplayClass46_0__CreateAllKarteUnitList_b__1__, 0);
        v1[2].klass = v29;
        if (_Find(v6, v29))
        {
          goto LABEL_24;
        }
      }
      v30 = v6->_size;
      v31 = v10;
      v32 = Method_System_Collections_Generic_List_sdatUnitWork_t__Add__;
      ++v6->_version;
      v33 = v6->_items;
      if ((u32)v30 >= *(u32 *)(v33 + 24))
      {
        _AddWithResize(v6, v31, *(const MethodInfo_2DFC660 **)(*(u64 *)(v32[4] + 192) + 112));
      }
      else
      {
        v34 = v33 + 8 * v30;
        v6->_size = v30 + 1;
        *(u64 *)(v34 + 32) = v31;
      }
    }
LABEL_24:
    ++v23;
  }
  if (v6->_size)
    return v6;
  else
    return 0;
}

// 0x1b8e380
void *gohCreateAllKarteDevilList(s32 _devilId) {
  void *v3;
  s32 v4;
  s32 v5;
  sdatUnitWork_t *v6;
  gohKarteList_t *karte_list;
  s64 RegistNums;
  gohKarteUnit_t *KarteUnit;
  s64 v13;
  gohKarteList_t *v15;
  s64 v16;
  s32 v17;
  s64 m_Items;
  u64 *v19;
  s64 v20;
  s64 v21;
  s64 v22;
  void *UnitList;
  void *v24;
  s32 v25;
  Il2CppObject *Item;
  s64 v27;
  u64 *v28;
  Il2CppObject *v29;
  s64 v30;
  s64 v31;

  v3 = Allocate(System_Collections_Generic_List_sdatUnitWork_t_);
  __ctor(v3);
  v4 = v3->_size;
  v5 = v3->_version + 1;
  v3->_size = 0;
  v3->_version = v5;
  if (v4 >= 1)
    Clear(v3->_items, 0, v4, 0);
  v6 = Allocate(sdatUnitWork_t);
  _ctor(v6, 0);
  karte_list = GBWK->karte_list;
  RegistNums = (u32)karte_list->RegistNums;
  if ((s32)RegistNums < 1)
    goto LABEL_31;
  KarteUnit = karte_list->KarteUnit;
  v13 = 0;
  while (KarteUnit[v13]->DevilID != devilId)
  {
    if (RegistNums == ++v13)
      goto LABEL_31;
  }
  if ((v13 & 0x80000000) == 0)
  {
    gohKarteCreateUnitFromKarteUnit(v6, KarteUnit[v13]);
    v15 = GBWK->karte_list;
    v16 = (u32)v15->RegistNums;
    if ((s32)v16 < 1)
      goto LABEL_31;
    v17 = 0;
    m_Items = v15->KarteUnit;
    do
    {
      if (*(s16 *)(*(u64 *)m_Items + 22) == devilId && *(u8 *)(*(u64 *)m_Items + 18))
        v17 = 1;
      --v16;
      m_Items += 8;
    }
    while (v16);
    if (v17)
    {
      v19 = Method_System_Collections_Generic_List_sdatUnitWork_t__Add__;
      v20 = v3->_size;
      ++v3->_version;
      v21 = v3->_items;
      if ((u32)v20 >= *(u32 *)(v21 + 24))
      {
        _AddWithResize(v3, v6, *(const MethodInfo_2DFC660 **)(*(u64 *)(v19[4] + 192) + 112));
      }
      else
      {
        v22 = v21 + 8 * v20;
        v3->_size = v20 + 1;
        *(u64 *)(v22 + 32) = v6;
      }
    }
    goto LABEL_31;
  }
LABEL_31:
  UnitList = gohKarteProCreateUnitList(devilId);
  if (UnitList)
  {
    v24 = UnitList;
    if (UnitList->_size >= 1)
    {
      v25 = 0;
      do
      {
        while (1)
        {
          Item = _get_Item(v24, v25);
          v27 = v3->_size;
          v28 = Method_System_Collections_Generic_List_sdatUnitWork_t__Add__;
          v29 = Item;
          ++v3->_version;
          v30 = v3->_items;
          if ((u32)v27 < *(u32 *)(v30 + 24))
            break;
          _AddWithResize(v3, Item, *(const MethodInfo_2DFC660 **)(*(u64 *)(v28[4] + 192) + 112));
          if (++v25 >= v24->_size)
            goto LABEL_37;
        }
        v31 = v30 + 8 * v27;
        v3->_size = v27 + 1;
        *(u64 *)(v31 + 32) = v29;
        ++v25;
      }
      while (v25 < v24->_size);
    }
  }
LABEL_37:
  if (v3->_size)
    return v3;
  else
    return 0;
}

// 0x1b8ea10
void *gohKarteProCreateUnitList(s32 _devilId) {
  void *v3;
  s32 v4;
  s32 v5;
  gohKarteList_t *karte_list;
  s64 karte2WakuCnt;
  gohKarteUnit_t *m_Items;
  sdatUnitWork_t *v9;
  s64 v11;
  u64 *v12;
  s64 v13;
  s64 v14;

  v3 = Allocate(System_Collections_Generic_List_sdatUnitWork_t_);
  __ctor(v3);
  v4 = v3->_size;
  v5 = v3->_version + 1;
  v3->_size = 0;
  v3->_version = v5;
  if (v4 >= 1)
    Clear(v3->_items, 0, v4, 0);
  karte_list = GBWK->karte_list;
  karte2WakuCnt = (u32)karte_list->karte2WakuCnt;
  if ((s32)karte2WakuCnt < 1)
    goto LABEL_15;
  m_Items = karte_list->Karte2Unit;
  do
  {
    if (m_Items->DevilID == devilId)
    {
      v9 = Allocate(sdatUnitWork_t);
      _ctor(v9, 0);
      gohKarteCreateUnitFromKarteUnit(v9, m_Items);
      v11 = v3->_size;
      v12 = Method_System_Collections_Generic_List_sdatUnitWork_t__Add__;
      ++v3->_version;
      v13 = v3->_items;
      if ((u32)v11 >= *(u32 *)(v13 + 24))
      {
        _AddWithResize(v3, v9, *(const MethodInfo_2DFC660 **)(*(u64 *)(v12[4] + 192) + 112));
      }
      else
      {
        v14 = v13 + 8 * v11;
        v3->_size = v11 + 1;
        *(u64 *)(v14 + 32) = v9;
      }
    }
    ++m_Items;
    --karte2WakuCnt;
  }
  while (karte2WakuCnt);
LABEL_15:
  if (v3->_size)
    return v3;
  else
    return 0;
}

// 0x1b8e720
s32 gohKarteCreateUnit(s32 DevilID, sdatUnitWork_t *pUnit) {
  gohKarteList_t *karte_list;
  s64 RegistNums;
  gohKarteUnit_t *KarteUnit;
  s64 v9;

  karte_list = GBWK->karte_list;
  RegistNums = (u32)karte_list->RegistNums;
  if ((s32)RegistNums < 1)
    return 0;
  KarteUnit = karte_list->KarteUnit;
  v9 = 0;
  while (KarteUnit[v9]->DevilID != DevilID)
  {
    if (RegistNums == ++v9)
      return 0;
  }
  if ((v9 & 0x80000000) == 0)
  {
    gohKarteCreateUnitFromKarteUnit(pUnit, KarteUnit[v9]);
    return 1;
  }
  return 0;
}

// 0x1b8ec10
s32 gohKarteCreateUnitUc(s32 DevilID, u32 _uniqCode, sdatUnitWork_t *pUnit, bool _pro) {
  s64 v10;
  gohKarteList_t *karte_list;
  s64 v12;
  s64 v13;
  s64 v14;
  s64 v15;
  s64 v16;

  v10 = 48;
  karte_list = GBWK->karte_list;
  v12 = 16;
  if (pro)
    v12 = 56;
  else
    v10 = 24;
  v13 = *(u32 *)((char *)&karte_list->klass + v12);
  if ((s32)v13 < 1)
    return 0;
  v14 = *(s64 *)((char *)&karte_list->klass + v10);
  v15 = 0;
  while (1)
  {
    v16 = *(u64 *)(v14 + 32 + 8 * v15);
    if (*(u32 *)(v16 + 120) == uniqCode && *(s16 *)(v16 + 22) == DevilID)
      break;
    if (v13 == ++v15)
      return 0;
  }
  if ((v15 & 0x80000000) != 0)
    return 0;
  gohKarteCreateUnitFromKarteUnit(pUnit, *(gohKarteUnit_t *)(v14 + 8 * v15 + 32));
  return 1;
}

// 0x1b8ed20
s32 gohKarteCheckRegist(sdatUnitWork_t *pUnit, gohKarteList_t *pKarteList, bool _pro, bool _uniqChk) {
  sdatUnitWork_t *v9;
  sdatUnitWork_t *v10;
  s32 devilid;
  u32 uniq_code;
  s64 karte2WakuCnt;
  gohKarteUnit_t *KarteUnit;
  s64 v16;
  gohKarteUnit_t *v17;
  s32 result;
  s64 RegistNums;
  gohKarteUnit_t *v20;
  sdatParaWork_t *now;
  sdatParaWork_t *v22;
  SKLID *haveskill;
  s32 v24;
  SKLID *v27;
  s32 v28;
  s32 v30;
  s32 v32;
  s32 v34;
  s32 v36;
  s32 v38;
  s32 v40;
  SKLID *aOmoideSkill;
  SKLID *v42;
  SKLID *sousaSkill;
  SKLID *v44;
  s8 *v45;
  s64 max_length;
  s8 *m_Items;
  s8 *v48;
  s32 v49;
  s32 v50;
  s32 v51;
  sdatUnitWork_t *v52;
  s64 v54;
  s32 v55;
  gohKarteUnit_t *v56;
  s64 v57;

  v9 = Allocate(sdatUnitWork_t);
  _ctor(v9, 0);
  v10 = Allocate(sdatUnitWork_t);
  _ctor(v10, 0);
  ClassCopy(v10, pUnit, 0);
  devilid = (u16)pUnit->devilid;
  uniq_code = pUnit->uniq_code;
  if (!pro)
  {
    RegistNums = (u32)pKarteList->RegistNums;
    if ((s32)RegistNums >= 1)
    {
      KarteUnit = pKarteList->KarteUnit;
      v16 = 0;
      while (1)
      {
        v20 = KarteUnit[v16];
        if (v20->uniqCode == uniq_code && (u16)v20->DevilID == devilid)
          break;
        if (RegistNums == ++v16)
          goto LABEL_63;
      }
      if ((v16 & 0x80000000) == 0)
        goto LABEL_17;
    }
LABEL_63:
    if (uniqChk)
    {
      v52 = Allocate(sdatUnitWork_t);
      _ctor(v52, 0);
      v54 = (u32)pKarteList->RegistNums;
      v55 = (u16)pUnit->devilid;
      if ((s32)v54 >= 1)
      {
        v56 = pKarteList->KarteUnit;
        v57 = 0;
        while ((u16)v56[v57]->DevilID != v55)
        {
          if (v54 == ++v57)
            goto LABEL_71;
        }
        if ((v57 & 0x80000000) == 0)
        {
          gohKarteCreateUnitFromKarteUnit(v52, v56[v57]);
          v55 = (u16)pUnit->devilid;
        }
      }
LABEL_71:
      if ((u16)v52->devilid == v55 && v52->uniq_code != pUnit->uniq_code)
        return 1;
    }
    return 0;
  }
  karte2WakuCnt = (u32)pKarteList->karte2WakuCnt;
  if ((s32)karte2WakuCnt < 1)
    return 0;
  KarteUnit = pKarteList->Karte2Unit;
  v16 = 0;
  while (1)
  {
    v17 = KarteUnit[v16];
    if (v17->uniqCode == uniq_code && (u16)v17->DevilID == devilid)
      break;
    if (karte2WakuCnt == ++v16)
      return 0;
  }
  if ((v16 & 0x80000000) != 0)
    return 0;
LABEL_17:
  gohKarteCreateUnitFromKarteUnit(v9, KarteUnit[(u32)v16]);
  if (pUnit->exp != v9->exp)
    return 1;
  if (pUnit->chuusei != v9->chuusei)
    return 1;
  if (pUnit->level != v9->level)
    return 1;
  now = pUnit->now;
  v22 = v9->now;
  if (now->maxhp != v22->maxhp || now->str != v22->str || now->tec != v22->tec || now->vit != v22->vit || now->luck != v22->luck || ((v9->flag ^ pUnit->flag) & 0xF0) != 0)
  {
    return 1;
  }
  datGetTmpSklDelHaveSkl(v10);
  haveskill = v9->haveskill;
  v24 = haveskill[0];
  if (!gohCheckHaveSkill(v10, v24))
    return 1;
  v27 = v10->haveskill;
  if (v24 != v27[0])
    return 1;
  v28 = haveskill[1];
  if (!gohCheckHaveSkill(v10, v28))
    return 1;
  if (v28 != v27[1])
    return 1;
  v30 = haveskill[2];
  if (!gohCheckHaveSkill(v10, v30))
    return 1;
  if (v30 != v27[2])
    return 1;
  v32 = haveskill[3];
  if (!gohCheckHaveSkill(v10, v32))
    return 1;
  if (v32 != v27[3])
    return 1;
  v34 = haveskill[4];
  if (!gohCheckHaveSkill(v10, v34))
    return 1;
  if (v34 != v27[4])
    return 1;
  v36 = haveskill[5];
  if (!gohCheckHaveSkill(v10, v36))
    return 1;
  if (v36 != v27[5])
    return 1;
  v38 = haveskill[6];
  if (!gohCheckHaveSkill(v10, v38))
    return 1;
  if (v38 != v27[6])
    return 1;
  v40 = haveskill[7];
  if (!gohCheckHaveSkill(v10, v40) || v40 != v27[7])
    return 1;
  datGetTmpDelOmoideSkl(v10);
  aOmoideSkill = v9->aOmoideSkill;
  v42 = v10->aOmoideSkill;
  if (aOmoideSkill[0] != v42[0])
    return 1;
  if (aOmoideSkill[1] != v42[1])
    return 1;
  if (aOmoideSkill[2] != v42[2])
    return 1;
  if (aOmoideSkill[3] != v42[3])
    return 1;
  if (aOmoideSkill[4] != v42[4])
    return 1;
  if (aOmoideSkill[5] != v42[5])
    return 1;
  if (aOmoideSkill[6] != v42[6])
    return 1;
  if (aOmoideSkill[7] != v42[7])
    return 1;
  sousaSkill = v9->sousaSkill;
  v44 = pUnit->sousaSkill;
  if (sousaSkill[0] != v44[0] || sousaSkill[1] != v44[1])
    return 1;
  v45 = datOmoideSkillDelOfcSkl(v10);
  if ((s32)v10->aOmoideSkillMaster->max_length >= 1)
  {
    max_length = (u32)v10->aOmoideSkillMaster->max_length;
    m_Items = v45;
    result = 2;
    v48 = v9->aOmoideSkillMaster;
    while (1)
    {
      v50 = (u8)*m_Items++;
      v49 = v50;
      v51 = (u8)*v48++;
      if (v49 != v51)
        break;
      if (!--max_length)
        return result;
    }
    return 1;
  }
  return 2;
}

// 0x1b8f260
s32 gohKarteRestoreDevil(sdatUnitWork_t *pUnit) {
  s64 v3;

  v3 = 4;
  while (1)
  {
    if (SameDataCheck(pUnit, *((sdatUnitWork_t *)&GBWK->player->stock_id->obj.klass + v3), 0))
    {
      break;
    }
    if (++v3 == 36)
    {
      return datAddDevilUnit(pUnit);
    }
  }
  ClassCopy(*((sdatUnitWork_t *)&GBWK->player->stock_id->obj.klass + v3), pUnit, 0);
  return v3 - 4;
}

// 0x1b8f370
s32 gohKarteRegistDevilBtl(sdatUnitWork_t *pUnit, gohKarteList_t *pKarteList, s32 Mode, s32 type) {
  sdatUnitWork_t *v6;
  s32 devilid;

  v6 = Allocate(sdatUnitWork_t);
  _ctor(v6, 0);
  devilid = pUnit->devilid;
  datCalcEnemyToNakamaID(devilid);
  return -1;
}

// 0x1b8f410
void gohKarteBackupAll(void) {
  gohKarteList_t *karte_list;
  gohKarteList_t *v3;

  karte_list = GBWK->karte_list;
  v3 = Allocate(gohKarteList_t);
  _ctor_28898512(v3, karte_list);
  gBackupKarteList = v3;
}

// 0x1b8f700
void gohInitGlobalWorkKarte(void) {
  gohKarteList_t *karte_list;
  s32 addCnt;

  karte_list = GBWK->karte_list;
  addCnt = gohKarteWakuSetting->addCnt;
  if (karte_list->karte2WakuCnt < addCnt)
  {
    karte_list = GBWK->karte_list;
    addCnt = gohKarteWakuSetting->addCnt;
    karte_list->karte2WakuCnt = addCnt;
  }
}

// 0x1b8f7a0
void gohDlcKarteReg(void) {
  s32 v2;
  sdatUnitWork_t *v4;
  gohKarteList_t *karte_list;
  s64 RegistNums;
  s64 v8;
  s64 m_Items;

  if (Exists("new_devil"))
  {
    v2 = 496;
    do
    {
      karte_list = GBWK->karte_list;
      RegistNums = (u32)karte_list->RegistNums;
      if ((s32)RegistNums >= 1)
      {
        v8 = 0xFFFFFFFFLL;
        m_Items = karte_list->KarteUnit;
        while (v2 != *(s16 *)(*(u64 *)m_Items + 22))
        {
          --v8;
          --RegistNums;
          m_Items += 8;
          if (!RegistNums)
            goto LABEL_8;
        }
        if (v8)
          goto LABEL_11;
      }
LABEL_8:
      v4 = Allocate(sdatUnitWork_t);
      _ctor(v4, 0);
      datCreateDevilUnit(v2, v4);
      gohKarteRegistDevil(v4, GBWK->karte_list, 1, 1, 0, 0);
LABEL_11:
      ++v2;
    }
    while (v2 != 502);
  }
}

// 0x1b90120
s32 gohKarteRestoreAll(void) {
  dds3GlobalWork_t *GBWK_local;
  gohKarteList_t *v4;

  GBWK_local = GBWK;
  v4 = Allocate(gohKarteList_t);
  _ctor_28898512(v4, gBackupKarteList);
  GBWK_local->karte_list = v4;
  gBackupKarteList = 0;
  return 1;
}

// 0x1b90200
s32 gohGetCombiCount(s32 iMode) {
  s32 result;

  result = GBWK->karte_list->m_sCombCnt;
  if (iMode != 2)
  {
    if (iMode == 1)
      result %= 1000;
    return result;
  }
  if (result >= 999)
    return 999;
  return result;
}

// 0x1b902e0
void gohSetCombiCount(s32 iValue) {
  gohKarteList_t *karte_list;
  void *achievementTbl_k__BackingField;
  Project_DefineAchievementID_string__c *klass;
  s64 v11;
  Project_DefineAchievementID_string__c **p_offset;
  s64 v13;
  char *v15;

  karte_list = GBWK->karte_list;
  karte_list->m_sCombCnt = iValue;
  if (iValue >= 1000)
  {
    karte_list = GBWK->karte_list;
    karte_list->m_sCombCnt = 999;
    goto LABEL_21;
  }
  if (iValue >= 256)
  {
LABEL_21:
    SystemWork->cmbCnt = -1;
    return;
  }
  SystemWork->cmbCnt = iValue;
  achievementTbl_k__BackingField = _achievementTbl_k__BackingField;
  klass = achievementTbl_k__BackingField->klass;
  v11 = *(u16 *)&achievementTbl_k__BackingField->klass->_2.rank;
  if (*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
  {
    p_offset = &klass->_1.interfaceOffsets->offset;
    while (*(p_offset - 1) != Project_DefineAchievementID_string_)
    {
      p_offset += 2;
      if (!--v11)
        goto LABEL_17;
    }
    v13 = &klass->vtable[*(u32 *)p_offset + 29];
  }
  else
  {
LABEL_17:
    v13 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0x1Du);
  }
  v15 = (*v13)(achievementTbl_k__BackingField, *(u64 *)(v13 + 8));
  ProgressUnlock_3(v15, SystemWork->cmbCnt, 50);
}

// 0x1b90500
void gohAddCombiCount(s32 iVal) {
  gohSetCombiCount(GBWK->karte_list->m_sCombCnt + iVal);
}

// 0x1b90580
void gohSetLetterCnt(s32 iVal) {
  s32 v5;
  void *achievementTbl_k__BackingField;
  Project_DefineAchievementID_string__c *klass;
  s64 v12;
  Project_DefineAchievementID_string__c **p_offset;
  s64 v14;
  char *v15;

  v5 = SystemWork->letterCnt + iVal;
  if (v5 <= 49)
  {
    SystemWork->letterCnt = v5;
    achievementTbl_k__BackingField = _achievementTbl_k__BackingField;
    klass = achievementTbl_k__BackingField->klass;
    v12 = *(u16 *)&achievementTbl_k__BackingField->klass->_2.rank;
    if (!*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
      goto LABEL_22;
    goto LABEL_19;
    if (!*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
    {
LABEL_22:
      v14 = sub_4227F4(achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0x1Eu);
LABEL_24:
      v15 = (*v14)(achievementTbl_k__BackingField, *(u64 *)(v14 + 8));
      ProgressUnlock_3(v15, SystemWork->letterCnt, 50);
      return;
    }
LABEL_19:
    p_offset = &klass->_1.interfaceOffsets->offset;
    while (*(p_offset - 1) != Project_DefineAchievementID_string_)
    {
      p_offset += 2;
      if (!--v12)
        goto LABEL_22;
    }
    v14 = &klass->vtable[*(u32 *)p_offset + 30];
    goto LABEL_24;
  }
  SystemWork->letterCnt = 50;
}

// 0x1b90790
s32 gohGetRank(void) {
  return 0;
}

// 0x1b907a0
void gohKarteCreateKarteUnitFromUnit(gohKarteUnit_t *pKarteUnit, sdatUnitWork_t *pUnit, s8 mode) {
  gohKarteUnit_t *v6;
  gohKarteUnit_t *v8;
  s64 v10;
  gohKarteUnit_t *v11;
  s32 v12;
  u8 RsvSklFlag;
  u8 v14;
  u8 v15;
  s32 v16;
  s32 v17;
  s32 v18;
  s32 v19;
  _BOOL4 v20;
  gohKarteUnit_t *v21;
  SKLID *Skill;
  SKLID *sousaSkill;
  SKLID *v24;
  SKLID *battleskill;
  SKLID *v27;
  SKLID *aOmoideSkill;
  il2cpp_array_size_t max_length;
  SKLID *v30;
  u64 v31;
  u64 v32;
  s32 *v33;
  s32 *v34;
  u64 v35;
  __int128 v36;
  __int128 v37;
  __int128 v38;
  __int128 v39;
  char v40;
  u64 v41;
  u64 v42;
  s64 v43;
  u32 *v44;
  s32 *v45;
  s32 v46;
  void *v47;
  sdatParaWork_t *backup;
  gohKarteUnit_t *v49;
  u8 *Str;
  u8 *Tec;
  u8 *Vit;
  u8 *Luck;
  u8 *v54;
  u8 *v55;
  u8 *v56;
  u8 *v57;
  gohKarteUnit_t *v58;

  v6 = Allocate(gohKarteUnit_t);
  _ctor(v6);
  pKarteUnit = v6;
  v8 = pKarteUnit;
  v8->DevilID = pUnit->devilid;
  v8->Exp = pUnit->exp;
  v8->Cyuusei = pUnit->chuusei;
  v8->Level = pUnit->level;
  v8->UnitFlag = (LOBYTE(pUnit->flag) >> 3) & 7;
  datGetTmpSklDelHaveSkl(pUnit);
  v10 = 0;
  do
  {
    v16 = pUnit->haveskill[v10];
    if ((u32)(v10 - 4) < 0xFFFFFFFD)
    {
      v17 = 1;
      if (!v16)
        goto LABEL_6;
LABEL_21:
      if (v16 != 149 && v16 != 288)
      {
        v21 = pKarteUnit;
        Skill = v21->Skill;
        if (SLODWORD(Skill->max_length) > v10)
          Skill[v10] = v16;
      }
      goto LABEL_6;
    }
    v18 = pUnit->aRsvSkl[(u32)(v10 - 1)];
    if (v18 == 288)
      v19 = pUnit->haveskill[v10];
    else
      v19 = pUnit->aRsvSkl[(u32)(v10 - 1)];
    v20 = v18 == 288;
    if (v18 == 149)
    {
      v19 = pUnit->haveskill[v10];
      v20 = 1;
    }
    if (v18)
    {
      v16 = v19;
      v17 = v20;
    }
    else
    {
      v17 = 1;
    }
    if (v16)
      goto LABEL_21;
LABEL_6:
    v11 = pKarteUnit;
    v12 = 1 << v10++;
    RsvSklFlag = pKarteUnit->RsvSklFlag;
    v14 = RsvSklFlag & ~(u8)v12;
    v15 = RsvSklFlag | v12;
    if (v17)
      v15 = v14;
    v11->RsvSklFlag = v15;
  }
  while (v10 != 8);
  sousaSkill = pUnit->sousaSkill;
  v24 = v11->sousaSkill;
  v24[0] = sousaSkill[0];
  v24[1] = sousaSkill[1];
  battleskill = pUnit->battleskill;
  v27 = v11->battleskill;
  v27[0] = battleskill[0];
  v27[1] = battleskill[1];
  v27[2] = battleskill[2];
  v27[3] = battleskill[3];
  v27[4] = battleskill[4];
  v27[5] = battleskill[5];
  v27[6] = battleskill[6];
  v27[7] = battleskill[7];
  v11->iOmoideSkillCnt = pUnit->iOmoideSkillCnt;
  datGetTmpDelOmoideSkl(pUnit);
  aOmoideSkill = pKarteUnit->aOmoideSkill;
  max_length = aOmoideSkill->max_length;
  if ((s32)max_length >= 1)
  {
    v30 = pUnit->aOmoideSkill;
    v31 = (u32)aOmoideSkill->max_length;
    v32 = 0;
    if (v31 < 0x10)
      goto LABEL_35;
    if ((u64)((char *)aOmoideSkill - (char *)v30) < 0x40)
      goto LABEL_35;
    v33 = &aOmoideSkill[12];
    v34 = &v30[4];
    v32 = v31 - (aOmoideSkill->max_length & 0xF);
    v35 = v32;
    do
    {
      v36 = *((_OWORD *)v34 - 1);
      v37 = *(_OWORD *)v34;
      v35 -= 16;
      v38 = *((_OWORD *)v34 + 1);
      v39 = *((_OWORD *)v34 + 2);
      v34 += 16;
      *((_OWORD *)v33 - 3) = v36;
      *((_OWORD *)v33 - 2) = v37;
      *((_OWORD *)v33 - 1) = v38;
      *(_OWORD *)v33 = v39;
      v33 += 16;
    }
    while (v35);
    if ((max_length & 0xF) != 0)
    {
LABEL_35:
      v40 = max_length - v32;
      v41 = v32 + 1;
      if ((v40 & 1) != 0)
      {
        aOmoideSkill[v32] = v30[v32];
        ++v32;
      }
      if (v31 != v41)
      {
        v42 = v31 - v32;
        v43 = 4 * v32 + 36;
        v44 = ((char *)aOmoideSkill + v43);
        v45 = ((char *)v30 + v43);
        do
        {
          v42 -= 2;
          *(v44 - 1) = *(v45 - 1);
          v46 = *v45;
          v45 += 2;
          *v44 = v46;
          v44 += 2;
        }
        while (v42);
      }
    }
  }
  v47 = datOmoideSkillDelOfcSkl(pUnit);
  Copy_56180528(v47, pKarteUnit->aOmoideSkillMaster, pKarteUnit->aOmoideSkillMaster->max_length, 0);
  backup = pUnit->backup;
  v49 = pKarteUnit;
  v49->MaxHP = pUnit->now->maxhp;
  v49->Str[0] = backup->str;
  pKarteUnit->Tec[0] = pUnit->backup->tec;
  pKarteUnit->Vit[0] = pUnit->backup->vit;
  pKarteUnit->Luck[0] = pUnit->backup->luck;
  Str = pKarteUnit->Str;
  Str[1] = GETITEMPARA_LOW(pUnit->pitem->str);
  Tec = pKarteUnit->Tec;
  Tec[1] = GETITEMPARA_LOW(pUnit->pitem->tec);
  Vit = pKarteUnit->Vit;
  Vit[1] = GETITEMPARA_LOW(pUnit->pitem->vit);
  Luck = pKarteUnit->Luck;
  Luck[1] = GETITEMPARA_LOW(pUnit->pitem->luck);
  pKarteUnit->Str[2] = pUnit->pbtl->str;
  pKarteUnit->Tec[2] = pUnit->pbtl->tec;
  pKarteUnit->Vit[2] = pUnit->pbtl->vit;
  pKarteUnit->Luck[2] = pUnit->pbtl->luck;
  pKarteUnit->Str[3] = pUnit->huuma->str;
  pKarteUnit->Tec[3] = pUnit->huuma->tec;
  pKarteUnit->Vit[3] = pUnit->huuma->vit;
  pKarteUnit->Luck[3] = pUnit->huuma->luck;
  v54 = pKarteUnit->Str;
  v54[4] = GETITEMPARA_HIGH(pUnit->pitem->str);
  v55 = pKarteUnit->Tec;
  v55[4] = GETITEMPARA_HIGH(pUnit->pitem->tec);
  v56 = pKarteUnit->Vit;
  v56[4] = GETITEMPARA_HIGH(pUnit->pitem->vit);
  v57 = pKarteUnit->Luck;
  v57[4] = GETITEMPARA_HIGH(pUnit->pitem->luck);
  if (mode)
  {
    v58 = pKarteUnit;
    pKarteUnit->nakamaflag = 1;
  }
  else
  {
    LogError("倒した悪魔登録はオミットなので来ないはず", 0);
    v58 = pKarteUnit;
    pKarteUnit->killflag = 1;
  }
  v58->accidentBonusHp = pUnit->accident->maxhp;
  v58->uniqCode = pUnit->uniq_code;
}

// 0x1b8d9a0
void gohKarteCreateUnitFromKarteUnit(sdatUnitWork_t *pUnit, gohKarteUnit_t *pKarteUnit) {
  s32 DevilID;
  u32 uniqCode;
  s32 UnitFlag;
  SKLID *Skill;
  s32 v9;
  SKLID *v10;
  s64 v11;
  s64 v12;
  s64 v13;
  s64 max_length_low;
  u32 *v15;
  s32 v16;
  char *v17;
  sdatUnitWork_t *v18;
  s32 v19;
  SKLID *sousaSkill;
  SKLID *v21;
  SKLID *battleskill;
  SKLID *v23;
  SKLID *aOmoideSkill;
  il2cpp_array_size_t max_length;
  SKLID *v26;
  u64 v27;
  u64 v28;
  s32 *v29;
  s32 *v30;
  u64 v31;
  __int128 v32;
  __int128 v33;
  __int128 v34;
  __int128 v35;
  char v36;
  u64 v37;
  u64 v38;
  s64 v39;
  u32 *v40;
  s32 *v41;
  s32 v42;
  s32 MaxHP;
  sdatParaWork_t *now;
  sdatParaWork_t *backup;
  sdatParaWork_t *huuma;
  u8 *Str;
  u8 *Tec;
  u8 *Vit;
  u8 *Luck;
  sdatParaWork_t *pitem;
  sdatParaWork_t *pbtl;
  sdatParaWork_t *v54;

  DevilID = pKarteUnit->DevilID;
  uniqCode = pKarteUnit->uniqCode;
  datCreateDevilUnitEx(DevilID, 0, pUnit, uniqCode);
  pUnit->devilid = pKarteUnit->DevilID;
  UnitFlag = pKarteUnit->UnitFlag;
  pUnit->exp = pKarteUnit->Exp;
  pUnit->chuusei = pKarteUnit->Cyuusei;
  pUnit->level = pKarteUnit->Level;
  pUnit->flag |= 8 * UnitFlag;
  Skill = pKarteUnit->Skill;
  if (SLODWORD(Skill->max_length) >= 1)
  {
    v9 = Skill[0];
    if (v9)
    {
      if (v9 != 149 && v9 != 288 && (pKarteUnit->RsvSklFlag & 1) == 0)
        pUnit->haveskill[0] = v9;
    }
  }
  v10 = pKarteUnit->Skill;
  v11 = 0;
  v12 = 1;
  v13 = 32;
  max_length_low = SLODWORD(v10->max_length);
  do
  {
    if (max_length_low <= v11 + 1 || (v16 = v10[v11 + 1]) == 0 || v16 == 149 || v16 == 288)
    {
      if ((u32)(v11 - 3) >= 0xFFFFFFFD)
      {
        v17 = (char *)pUnit->aRsvSkl + 4 * (u32)(v12 - 1);
LABEL_14:
        v15 = v17 + 32;
LABEL_15:
        *v15 = 0;
      }
    }
    else if (((pKarteUnit->RsvSklFlag >> (v11 + 1)) & 1) != 0)
    {
      if ((u32)(v11 - 3) >= 0xFFFFFFFD)
      {
        pUnit->aRsvSkl[v11] = v16;
        v17 = (char *)pUnit->haveskill + 4 * v12;
        goto LABEL_14;
      }
    }
    else
    {
      pUnit->haveskill[v11 + 1] = v16;
      if ((u32)(v11 - 3) >= 0xFFFFFFFD)
      {
        v15 = ((char *)pUnit->aRsvSkl + v13);
        goto LABEL_15;
      }
    }
    ++v11;
    ++v12;
    v13 += 4;
  }
  while (v11 != 7);
  if (!v10[0])
  {
    v18 = Allocate(sdatUnitWork_t);
    _ctor(v18, 0);
    v19 = pKarteUnit->DevilID;
    datCreateDevilUnit(v19, v18);
    pUnit->haveskill[0] = v18->haveskill[0];
  }
  sousaSkill = pKarteUnit->sousaSkill;
  v21 = pUnit->sousaSkill;
  v21[0] = sousaSkill[0];
  battleskill = pKarteUnit->battleskill;
  v21[1] = sousaSkill[1];
  v23 = pUnit->battleskill;
  v23[0] = battleskill[0];
  v23[1] = battleskill[1];
  v23[2] = battleskill[2];
  v23[3] = battleskill[3];
  v23[4] = battleskill[4];
  v23[5] = battleskill[5];
  pUnit->iOmoideSkillCnt = pKarteUnit->iOmoideSkillCnt;
  v23[6] = battleskill[6];
  v23[7] = battleskill[7];
  aOmoideSkill = pUnit->aOmoideSkill;
  max_length = aOmoideSkill->max_length;
  if ((s32)max_length >= 1)
  {
    v26 = pKarteUnit->aOmoideSkill;
    v27 = (u32)aOmoideSkill->max_length;
    v28 = 0;
    if (v27 < 0x10)
      goto LABEL_38;
    if ((u64)((char *)aOmoideSkill - (char *)v26) < 0x40)
      goto LABEL_38;
    v29 = &aOmoideSkill[12];
    v30 = &v26[4];
    v28 = v27 - (aOmoideSkill->max_length & 0xF);
    v31 = v28;
    do
    {
      v32 = *((_OWORD *)v30 - 1);
      v33 = *(_OWORD *)v30;
      v31 -= 16;
      v34 = *((_OWORD *)v30 + 1);
      v35 = *((_OWORD *)v30 + 2);
      v30 += 16;
      *((_OWORD *)v29 - 3) = v32;
      *((_OWORD *)v29 - 2) = v33;
      *((_OWORD *)v29 - 1) = v34;
      *(_OWORD *)v29 = v35;
      v29 += 16;
    }
    while (v31);
    if ((max_length & 0xF) != 0)
    {
LABEL_38:
      v36 = max_length - v28;
      v37 = v28 + 1;
      if ((v36 & 1) != 0)
      {
        aOmoideSkill[v28] = v26[v28];
        ++v28;
      }
      if (v27 != v37)
      {
        v38 = v27 - v28;
        v39 = 4 * v28 + 36;
        v40 = ((char *)aOmoideSkill + v39);
        v41 = ((char *)v26 + v39);
        do
        {
          v38 -= 2;
          *(v40 - 1) = *(v41 - 1);
          v42 = *v41;
          v41 += 2;
          *v40 = v42;
          v40 += 2;
        }
        while (v38);
      }
    }
  }
  Copy_56180528(pKarteUnit->aOmoideSkillMaster, pUnit->aOmoideSkillMaster, pUnit->aOmoideSkillMaster->max_length, 0);
  MaxHP = pKarteUnit->MaxHP;
  now = pUnit->now;
  backup = pUnit->backup;
  now->hp = MaxHP;
  now->maxhp = MaxHP;
  huuma = pUnit->huuma;
  pUnit->accident->maxhp = pKarteUnit->accidentBonusHp;
  Str = pKarteUnit->Str;
  Tec = pKarteUnit->Tec;
  backup->str = Str[0];
  backup->tec = Tec[0];
  Vit = pKarteUnit->Vit;
  Luck = pKarteUnit->Luck;
  backup->vit = Vit[0];
  backup->luck = Luck[0];
  pitem = pUnit->pitem;
  pbtl = pUnit->pbtl;
  pitem->str = Str[1] | (Str[4] << 8);
  pitem->tec = Tec[1] | (Tec[4] << 8);
  pitem->vit = Vit[1] | (Vit[4] << 8);
  pitem->luck = Luck[1] | (Luck[4] << 8);
  pbtl->str = Str[2];
  pbtl->tec = Tec[2];
  pbtl->vit = Vit[2];
  pbtl->luck = Luck[2];
  huuma->str = Str[3];
  huuma->tec = Tec[3];
  huuma->vit = Vit[3];
  huuma->luck = Luck[3];
  backup->maxhp = datGetDevilMaxHP(pUnit, 0);
  datCalcNowParam(pUnit, 0, 0);
  v54 = pUnit->now;
  v54->hp = v54->maxhp;
  v54->mp = v54->maxmp;
}

// 0x1b8f980
s32 gohKarteRegistDevil(sdatUnitWork_t *pUnit, gohKarteList_t *pKarteList, s32 Mode, s32 type, bool _pro, sdatUnitWork_t *_overwrite) {
  gohKarteUnit_t *v13;
  s32 devilid;
  gohKarteUnit_t *Karte2Unit;
  u64 karte2WakuCnt;
  gohKarteUnit_t *v20;
  s32 v21;
  gohKarteUnit_t *v22;
  u64 v23;
  u64 v24;
  gohKarteUnit_t *v25;
  Il2CppClass **v26;
  Il2CppClass *v27;
  char *v28;
  Il2CppClass *v29;
  s32 KarteTrophChkCnt;
  s64 v33;
  gohKarteUnit_t *v35;
  Il2CppClass **v37;
  void *achievementTbl_k__BackingField;
  Project_DefineAchievementID_string__c *klass;
  s64 v42;
  Project_DefineAchievementID_string__c **p_offset;
  s64 v44;
  char *v45;
  gohKarteList_t *karte_list;
  s64 RegistNums;
  s64 v48;
  s32 v49;
  s32 v50;
  s32 v51;
  s32 NakamaCount;
  gohKarteList_t *v53;
  s64 v54;
  s64 v55;
  s32 v56;
  s32 v57;
  long f64 v58;
  s64 v59;
  char *v60;
  gohKarteUnit_t *v61;
  s32 v62;
  s32 Level;
  s32 DevilExp;
  gohKarteUnit_t *v65;
  gohKarteUnit_t *pKarteUnit;

  v13 = Allocate(gohKarteUnit_t);
  _ctor(v13);
  pKarteUnit = v13;
  devilid = pUnit->devilid;
  if (!pUnit->devilid || devilid >= 80 && (u32)(devilid - 337) >= 0x40 && (u32)(devilid - 496) > 5)
  {
    goto LABEL_47;
  }
  if (!DlcDevilSelCheck(devilid))
    goto LABEL_47;
  if (type)
  {
    gohKarteCreateKarteUnitFromUnit(pKarteUnit, pUnit, type);
    if (pro)
    {
      Karte2Unit = pKarteList->Karte2Unit;
      if (overwrite)
      {
        karte2WakuCnt = (u32)pKarteList->karte2WakuCnt;
        if ((s32)karte2WakuCnt < 1)
        {
          v21 = -1;
LABEL_41:
          goto LABEL_43;
        }
        else
        {
          v20 = 0;
          v21 = -1;
          while (1)
          {
            v22 = Karte2Unit[(u64)v20];
            if (v22->uniqCode == overwrite->uniq_code && v22->DevilID == overwrite->devilid)
              break;
            v20 = ((char *)v20 + 1);
            if (karte2WakuCnt == v20)
              goto LABEL_41;
          }
          if (((u32)v20 & 0x80000000) == 0)
          {
LABEL_35:
            v26 = &Karte2Unit->obj.klass + (u32)v20;
            v29 = v26[4];
            v28 = (v26 + 4);
            v27 = v29;
            if (!BYTE2(v29->_1.name))
              goto LABEL_110;
            if (BYTE4(v27->_1.klass))
            {
              LODWORD(v20) = -2;
              return (s32)v20;
            }
            if (Mode != 1)
            {
LABEL_110:
              v61 = pKarteUnit;
              if (Mode != 2 || overwrite)
                goto LABEL_104;
              v62 = pKarteUnit->DevilID;
              Level = pKarteUnit->Level;
              DevilExp = datGetDevilExp(v62, Level);
              if (datGetDevilExp(*(s16 *)(*(u64 *)v28 + 22), *(u8 *)(*(u64 *)v28 + 16)) <= DevilExp)
              {
                v61 = pKarteUnit;
                if (*(u8 *)(*(u64 *)v28 + 16) < (u32)pKarteUnit->Level)
                {
LABEL_104:
                  v65 = Allocate(gohKarteUnit_t);
                  _ctor_28905184(v65, v61);
                  sub_C80(Karte2Unit, v65);
                  *(u64 *)v28 = v65;
LABEL_65:
                  achievementTbl_k__BackingField = _achievementTbl_k__BackingField;
                  klass = achievementTbl_k__BackingField->klass;
                  v42 = *(u16 *)&achievementTbl_k__BackingField->klass->_2.rank;
                  if (*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
                  {
                    p_offset = &klass->_1.interfaceOffsets->offset;
                    while (*(p_offset - 1) != Project_DefineAchievementID_string_)
                    {
                      p_offset += 2;
                      if (!--v42)
                        goto LABEL_71;
                    }
                    v44 = (&klass[1]._1.byval_arg + *(u32 *)p_offset);
                  }
                  else
                  {
LABEL_71:
                    v44 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0x22u);
                  }
                  v45 = (*v44)(achievementTbl_k__BackingField, *(u64 *)(v44 + 8));
                  karte_list = GBWK->karte_list;
                  LODWORD(RegistNums) = karte_list->RegistNums;
                  if ((s32)RegistNums >= 1)
                  {
                    v48 = 0;
                    v49 = 0;
                    do
                    {
                      v50 = karte_list->KarteUnit[v48]->DevilID;
                      ++v48;
                      v49 += !DlcDevilSelCheck(v50);
                      RegistNums = karte_list->RegistNums;
                    }
                    while (v48 < RegistNums);
                    goto LABEL_85;
                  }
                  v49 = 0;
LABEL_85:
                  v51 = RegistNums - v49;
                  NakamaCount = GetNakamaCount();
                  ProgressUnlock_3(v45, v51, NakamaCount);
                  v53 = GBWK->karte_list;
                  LODWORD(v54) = v53->RegistNums;
                  if ((s32)v54 < 1)
                  {
                    v56 = 0;
                  }
                  else
                  {
                    v55 = 0;
                    v56 = 0;
                    do
                    {
                      v57 = v53->KarteUnit[v55]->DevilID;
                      ++v55;
                      v56 += !DlcDevilSelCheck(v57);
                      v54 = v53->RegistNums;
                    }
                    while (v55 < v54);
                  }
                  if ((s32)v54 - v56 >= GetNakamaCount())
                  {
                    v59 = sub_1A24F60(0, v58);
                    v60 = sub_8360(34, Project_DefineAchievementID_string_, v59);
                    Unlock_2(v60);
                  }
                  return (s32)v20;
                }
              }
            }
LABEL_47:
            LODWORD(v20) = -1;
            return (s32)v20;
          }
          v21 = v20;
          goto LABEL_43;
        }
LABEL_43:
        LogError("上書き指定悪魔が存在しない", 0);
        goto LABEL_44;
      }
      v24 = (u32)pKarteList->karte2WakuCnt;
      if ((s32)v24 < 1)
      {
        v21 = -1;
        LODWORD(v20) = -1;
        if (Mode == 2)
          return (s32)v20;
        goto LABEL_50;
      }
      v20 = 0;
      v21 = -1;
      while (1)
      {
        v25 = Karte2Unit[(u64)v20];
        if (v25->uniqCode == pUnit->uniq_code && v25->DevilID == pUnit->devilid)
          break;
        v20 = ((char *)v20 + 1);
        if (v24 == v20)
          goto LABEL_44;
      }
    }
    else
    {
      v23 = (u32)pKarteList->RegistNums;
      Karte2Unit = pKarteList->KarteUnit;
      if ((s32)v23 < 1)
      {
        v21 = -1;
        LODWORD(v20) = -1;
        if (Mode == 2)
          return (s32)v20;
        goto LABEL_46;
      }
      v20 = 0;
      v21 = -1;
      while (Karte2Unit[(u64)v20]->DevilID != pUnit->devilid)
      {
        v20 = ((char *)v20 + 1);
        if (v23 == v20)
          goto LABEL_44;
      }
    }
    v21 = v20;
    if (((u32)v20 & 0x80000000) == 0)
      goto LABEL_35;
LABEL_44:
    if (Mode == 2)
      goto LABEL_47;
    if (pro)
    {
LABEL_50:
      if ((s32)Karte2Unit->max_length >= 1)
      {
        v33 = 0;
        while (Karte2Unit[v33]->DevilID)
        {
          if ((u32)Karte2Unit->max_length == ++v33)
            goto LABEL_56;
        }
        v21 = v33;
      }
LABEL_56:
      if (pro)
      {
        LODWORD(v20) = -3;
        if (v21 == -1 || v21 >= GBWK->karte_list->karte2WakuCnt)
          return (s32)v20;
      }
      else
      {
        v21 = pKarteList->RegistNums;
        pKarteList->RegistNums = v21 + 1;
      }
      v20 = pKarteUnit;
      v35 = Allocate(gohKarteUnit_t);
      _ctor_28905184(v35, v20);
      sub_C80(Karte2Unit, v35);
      v37 = &Karte2Unit->obj.klass + v21;
      v37[4] = v35;
      LODWORD(v20) = v21;
      goto LABEL_65;
    }
LABEL_46:
    KarteTrophChkCnt = GetKarteTrophChkCnt(pKarteList);
    if (KarteTrophChkCnt >= GetNakamaCount())
      goto LABEL_47;
    goto LABEL_50;
  }
  LogError("倒した悪魔登録はオミットなので来ないはず", 0);
  LODWORD(v20) = -1;
  return (s32)v20;
}

// 0x1b912a0
s32 gohGetKarteProUnitCnt(gohKarteList_t *pKarteList) {
  s64 karte2WakuCnt;
  gohKarteUnit_t *Karte2Unit;
  s64 v6;
  s32 result;
  s32 v8;
  s32 v9;
  s32 v10;
  s32 v11;
  gohKarteUnit_t *v12;
  s64 v13;
  s32 v14;
  gohKarteUnit_t *v15;
  s32 v16;
  s32 v17;
  s32 v18;
  s64 v19;
  Il2CppClass **v20;
  s64 v21;
  gohKarteUnit_t *v22;
  s64 v23;
  gohKarteUnit_t *v24;
  s32 DevilID;
  s32 v26;

  karte2WakuCnt = (u32)GBWK->karte_list->karte2WakuCnt;
  if ((s32)karte2WakuCnt < 1)
    return 0;
  Karte2Unit = pKarteList->Karte2Unit;
  if ((u32)karte2WakuCnt < 4)
  {
    v6 = 0;
    result = 0;
LABEL_20:
    v19 = ~v6;
    if ((karte2WakuCnt & 1) != 0)
    {
      v20 = &Karte2Unit->obj.klass + v6;
      v6 |= 1u;
      if (HIWORD(v20[4]->_1.name))
        ++result;
    }
    if (v19 + karte2WakuCnt)
    {
      v21 = karte2WakuCnt - v6;
      v22 = &Karte2Unit[v6 + 1];
      do
      {
        v23 = *(v22 - 1);
        v24 = v22;
        v22 += 2;
        DevilID = (u16)v24->DevilID;
        if (*(u16 *)(v23 + 22))
          v26 = result + 1;
        else
          v26 = result;
        if (DevilID)
          result = v26 + 1;
        else
          result = v26;
        v21 -= 2;
      }
      while (v21);
    }
    return result;
  }
  v6 = karte2WakuCnt & 0x7FFFFFFC;
  v8 = 0;
  v9 = 0;
  v10 = 0;
  v11 = 0;
  v12 = &Karte2Unit[3];
  v13 = (u32)karte2WakuCnt & 0xFFFFFFFC;
  do
  {
    v14 = (u16)(*(v12 - 3))->DevilID;
    v15 = v12;
    v16 = (u16)(*(v12 - 2))->DevilID;
    v17 = (u16)(*(v12 - 1))->DevilID;
    v12 += 4;
    v18 = (u16)v15->DevilID;
    if (v14)
      ++v8;
    if (v16)
      ++v9;
    if (v17)
      ++v10;
    if (v18)
      ++v11;
    v13 -= 4;
  }
  while (v13);
  result = v11 + v10 + v9 + v8;
  if (v6 != karte2WakuCnt)
    goto LABEL_20;
  return result;
}

// 0x1b91440
s32 gohKarteProRegistDelDevil(sdatUnitWork_t *pUnit, gohKarteList_t *pKarteList) {
  gohKarteUnit_t *v5;
  s32 devilid;
  s16 v9;
  s64 karte2WakuCnt;
  gohKarteUnit_t *Karte2Unit;
  s64 v12;
  s64 v13;
  s32 v14;
  u32 uniq_code;
  gohKarteUnit_t *m_Items;
  gohKarteUnit_t *v17;
  il2cpp_array_size_t max_length;
  s64 v20;
  char *v21;
  Il2CppObject *v22;
  gohKarteUnit_t *v24;
  s32 v25;
  gohKarteUnit_t *v26;
  gohKarteUnit_t *v29;
  gohKarteUnit_t *v31;
  char *v33;
  s64 v34;
  char *v35;
  gohKarteUnit_t *v36;
  gohKarteUnit_t *pKarteUnit;

  v5 = Allocate(gohKarteUnit_t);
  _ctor(v5);
  pKarteUnit = v5;
  v9 = (u16)pUnit + 22;
  devilid = pUnit->devilid;
  if (!pUnit->devilid || devilid >= 80 && (u32)(devilid - 337) >= 0x40 && (u32)(devilid - 496) > 5)
  {
    goto LABEL_20;
  }
  gohKarteCreateKarteUnitFromUnit(pKarteUnit, pUnit, 1);
  karte2WakuCnt = (u32)pKarteList->karte2WakuCnt;
  if ((s32)karte2WakuCnt < 1)
    goto LABEL_17;
  Karte2Unit = pKarteList->Karte2Unit;
  v12 = 0;
  v13 = 0;
  v14 = (u16)pUnit->devilid;
  uniq_code = pUnit->uniq_code;
  m_Items = Karte2Unit;
  while (m_Items->uniqCode != uniq_code || (u16)(m_Items)->DevilID != v14)
  {
    ++v13;
    v12 += 0x100000000LL;
    ++m_Items;
    if (karte2WakuCnt == v13)
      goto LABEL_17;
  }
  if ((v13 & 0x80000000) != 0)
  {
LABEL_17:
    v21 = ToString(v9, 0);
    v22 = Concat_54766928("削除悪魔が存在しない::", v21, 0);
    LogError(v22, 0);
LABEL_20:
    LODWORD(v13) = -1;
    return v13;
  }
  v17 = Allocate(gohKarteUnit_t);
  _ctor(v17);
  m_Items = v17;
  m_Items->DevilID = 0;
  max_length = Karte2Unit->max_length;
  if ((s32)v13 >= (s32)max_length)
    return v13;
  v36 = Karte2Unit;
  v20 = v13;
  while (1)
  {
    if (++v20 >= (s32)max_length)
    {
      v31 = Allocate(gohKarteUnit_t);
      _ctor(v31);
      {
        v33 = (char *)Karte2Unit + (v12 >> 29);
        *((u64 *)v33 + 4) = v31;
        v34 = *((u64 *)v33 + 4);
        goto LABEL_34;
      }
    }
    v24 = m_Items[1];
    v25 = (u16)v24->DevilID;
    v26 = Allocate(gohKarteUnit_t);
    v29 = v26;
    if (!v25)
      break;
    _ctor_28905184(v26, v24);
    m_Items = v29;
    max_length = Karte2Unit->max_length;
    v12 += 0x100000000LL;
    ++m_Items;
    if (v20 >= (s32)max_length)
      return v13;
  }
  _ctor(v26);
  v35 = (char *)Karte2Unit + (v12 >> 29);
  *((u64 *)v35 + 4) = v29;
  v34 = *((u64 *)v35 + 4);
LABEL_34:
  *(u16 *)(v34 + 22) = 0;
  return v13;
}

// 0x1b91740
s32 gohKarteGetRestoreCost(sdatUnitWork_t *pUnit) {
  sdatParaWork_t *v3;
  s32 level;
  sdatUnitWork_t *para;
  sdatParaWork_t *now;
  sdatParaWork_t *pbtl;
  s32 v9;
  s32 raceid;
  s32 v11;
  s32 devilid;
  s32 v13;
  f32 v14;
  s32 v15;

  v3 = Allocate(sdatParaWork_t);
  _ctor(v3, 0);
  level = pUnit->level;
  para = GBWK->player->para;
  sBtlGetPlayerTec_ParaUp(para, v3);
  now = pUnit->now;
  pbtl = pUnit->pbtl;
  v9 = KARTE_RESTORE_RATE(level, now->str - pbtl->str, now->tec - pbtl->tec, now->vit - pbtl->vit, now->luck - pbtl->luck);
  raceid = (u8)pUnit->raceid;
  v11 = v9 + 1000;
  devilid = pUnit->devilid;
  if (raceid != 8)
    v11 = v9;
  if (raceid == 9)
    v13 = v9 + 4000;
  else
    v13 = v11;
  v14 = (f32)v13 * 0.1;
  if (v14 == INFINITY)
    v15 = 0x80000000;
  else
    v15 = (s32)v14;
  if (GetDlcDevilKarteF(devilid))
    return 0;
  else
    return v15;
}

// 0x1b918e0
s32 gohCreateRecoverUnit(gohGeneralList_t *pGeneralList) {
  gohGeneralList_t *v3;
  sdatPlayerUnitWork_t *player;
  sdatUnitWork_t *para;
  s32 v8;
  s32 v9;
  f32 v10;
  s32 v11;
  gohGeneralList_t *v12;
  s32 v13;
  s64 i;
  sdatUnitWork_t *v16;
  sdatParaWork_t *now;
  s32 devilid;
  s32 maxhp;
  s32 hp;
  f32 v21;
  s32 v22;
  f32 v23;
  f32 v24;
  s32 badstatus;
  s32 v26;
  sdatUnitWork_t *m_pDevil;
  s64 m_DevilCnt;
  Il2CppClass **v29;
  s64 v30;
  s32 *m_DevilVal;

  v3 = Allocate(gohGeneralList_t);
  _ctor(v3);
  pGeneralList = v3;
  player = GBWK->player;
  para = player->para;
  v8 = para->now->maxhp - para->now->hp;
  if (!v8)
  {
    v9 = 0;
LABEL_12:
    if ((para->badstatus & 0xC00) != 0)
      v11 = v9 + 300;
    else
      v11 = v9;
    if (!v11)
      goto LABEL_23;
    v12 = pGeneralList;
    player = GBWK->player;
    v12->m_pPlayer = player;
    v13 = 1;
    pGeneralList->m_PlayerVal = v11;
    goto LABEL_24;
  }
  v10 = (f32)v8 * 1.5;
  if (v10 == INFINITY)
    v9 = 0x80000000;
  else
    v9 = v10;
  goto LABEL_12;
LABEL_23:
  v13 = 0;
LABEL_24:
  for (i = 0; ; ++i)
  {
    if (i >= datGetStockDevilNums(0))
      break;
    v16 = GBWK->player->stock_id[i];
    now = v16->now;
    devilid = v16->devilid;
    hp = now->hp;
    maxhp = now->maxhp;
    if (!DlcDevilSelCheck(devilid))
      continue;
    v21 = (maxhp - hp);
    if (v16->now->hp)
    {
      if (maxhp == hp)
      {
        v22 = 0;
      }
      else
      {
        v24 = v21 * 1.5;
        v22 = v24;
        if (v24 == INFINITY)
          v22 = 0x80000000;
      }
    }
    else
    {
      v22 = -21474836;
      v23 = (f32)((f32)(v21 * 90.0) * 1.5) * 1.3;
      if (v23 != INFINITY)
        v22 = (s32)v23 / 100;
    }
    badstatus = v16->badstatus;
    if ((badstatus & 0xC00) != 0)
      v26 = v22 + 300;
    else
      v26 = v22;
    if ((badstatus & 0x100000) == 0 && v26)
    {
      m_pDevil = pGeneralList->m_pDevil;
      m_DevilCnt = pGeneralList->m_DevilCnt;
      v29 = &m_pDevil->obj.klass + m_DevilCnt;
      v29[4] = v16;
      ++v13;
      v30 = pGeneralList->m_DevilCnt;
      m_DevilVal = pGeneralList->m_DevilVal;
      pGeneralList->m_DevilCnt = v30 + 1;
      m_DevilVal[v30] = v26;
    }
  }
  return v13;
}

// 0x1b91cd0
s32 gohGetKarteProRegistNum(void) {
  s64 v2;
  s32 v3;
  gohKarteUnit_t *Karte2Unit;

  v2 = 0;
  v3 = 200;
  while (1)
  {
    Karte2Unit = GBWK->karte_list->Karte2Unit;
    if (v2 >= SLODWORD(Karte2Unit->max_length))
      return v3;
    Karte2Unit = GBWK->karte_list->Karte2Unit;
    if (!Karte2Unit[v2]->DevilID)
      return v2;
    ++v2;
  }
}

// 0x1b8e820
s32 gohChkKarteState(s32 devilid, s32 _uniqCode, bool _pro) {
  gohKarteUnit_t *Karte2Unit;
  s64 v10;
  s32 RegistNums;
  gohKarteUnit_t *v12;
  gohKarteList_t *karte_list;
  s64 v14;
  s32 result;
  gohKarteUnit_t *v16;
  gohKarteUnit_t *v17;
  bool v18;
  gohKarteUnit_t *m_Items;

  if (pro)
  {
    Karte2Unit = GBWK->karte_list->Karte2Unit;
    v10 = 0;
    RegistNums = 200;
    while (1)
    {
      v12 = GBWK->karte_list->Karte2Unit;
      if (v10 >= SLODWORD(v12->max_length))
        goto LABEL_19;
      v12 = GBWK->karte_list->Karte2Unit;
      if (!v12[v10]->DevilID)
      {
        RegistNums = v10;
        if ((s32)v10 >= 1)
          goto LABEL_19;
        return 0;
      }
      ++v10;
    }
  }
  karte_list = GBWK->karte_list;
  Karte2Unit = karte_list->KarteUnit;
  RegistNums = karte_list->RegistNums;
  if (RegistNums < 1)
    return 0;
LABEL_19:
  v14 = RegistNums;
  if (uniqCode == -1)
  {
    result = 0;
    m_Items = Karte2Unit;
    do
    {
      if (m_Items->DevilID == devilid && m_Items->nakamaflag)
        result = 1;
      ++m_Items;
      --v14;
    }
    while (v14);
  }
  else
  {
    result = 0;
    v16 = Karte2Unit;
    do
    {
      v17 = v16;
      if (v16->DevilID == devilid)
      {
        if (v17->nakamaflag)
          v18 = v17->uniqCode == (s64)uniqCode;
        else
          v18 = 0;
        if (v18)
          result = 1;
      }
      ++v16;
      --v14;
    }
    while (v14);
  }
  return result;
}

// 0x1b91da0
gohKarteUnit_t *gohGetKarteUnit(sdatUnitWork_t *_unit, bool _pro) {
  gohKarteUnit_t *Karte2Unit;
  s64 v8;
  s32 RegistNums;
  gohKarteUnit_t *v10;
  gohKarteList_t *karte_list;
  s32 devilid;
  s64 v13;
  gohKarteUnit_t *m_Items;
  gohKarteUnit_t *result;

  if (pro)
  {
    Karte2Unit = GBWK->karte_list->Karte2Unit;
    v8 = 0;
    RegistNums = 200;
    while (1)
    {
      v10 = GBWK->karte_list->Karte2Unit;
      if (v8 >= SLODWORD(v10->max_length))
        goto LABEL_21;
      v10 = GBWK->karte_list->Karte2Unit;
      if (!v10[v8]->DevilID)
      {
        RegistNums = v8;
        if ((s32)v8 < 1)
          return 0;
        goto LABEL_21;
      }
      ++v8;
    }
  }
  karte_list = GBWK->karte_list;
  Karte2Unit = karte_list->KarteUnit;
  RegistNums = karte_list->RegistNums;
  if (RegistNums < 1)
    return 0;
LABEL_21:
  devilid = (u16)unit->devilid;
  v13 = RegistNums;
  m_Items = Karte2Unit;
  if (pro)
  {
    while (1)
    {
      result = m_Items;
      if ((u16)(m_Items)->DevilID == devilid && result->uniqCode == unit->uniq_code)
        break;
      ++m_Items;
      if (!--v13)
        return 0;
    }
  }
  else
  {
    while (1)
    {
      result = m_Items;
      if ((u16)(m_Items)->DevilID == devilid)
        break;
      ++m_Items;
      if (!--v13)
        return 0;
    }
  }
  return result;
}

// 0x1b91f70
void gohSetKarteLock(sdatUnitWork_t *_unit, bool _set, bool _pro) {
  gohKarteUnit_t *KarteUnit;

  KarteUnit = gohGetKarteUnit(unit, pro);
  if (KarteUnit)
    KarteUnit->lockDvl = set;
}

// 0x1b91fa0
bool gohGetKarteLock(sdatUnitWork_t *_unit, bool _pro) {
  gohKarteUnit_t *KarteUnit;
  gohKarteUnit_t *v6;
  s32 devilid;

  KarteUnit = gohGetKarteUnit(unit, pro);
  if (KarteUnit)
  {
    v6 = KarteUnit;
    devilid = unit->devilid;
    if (DlcDevilSelCheck(devilid))
    {
      LOBYTE(KarteUnit) = v6->lockDvl;
      return (char)KarteUnit;
    }
    LOBYTE(KarteUnit) = 0;
  }
  return (char)KarteUnit;
}

// 0x1b92060
void gohSetKarteFavSet(sdatUnitWork_t *_unit, bool _set, bool _pro) {
  gohKarteUnit_t *KarteUnit;

  KarteUnit = gohGetKarteUnit(unit, pro);
  if (KarteUnit)
    KarteUnit->fav = set;
}

// 0x1b8d060
bool gohGetKarteFav(sdatUnitWork_t *_unit, bool _pro) {
  gohKarteUnit_t *KarteUnit;
  gohKarteUnit_t *v6;
  s32 devilid;

  KarteUnit = gohGetKarteUnit(unit, pro);
  if (KarteUnit)
  {
    v6 = KarteUnit;
    devilid = unit->devilid;
    if (DlcDevilSelCheck(devilid))
    {
      LOBYTE(KarteUnit) = v6->fav;
      return (char)KarteUnit;
    }
    LOBYTE(KarteUnit) = 0;
  }
  return (char)KarteUnit;
}
