#include "types.h"
#include "CmbBackStatus.h"
#include "CombStSeq.h"
#include "SKLID.h"
#include "cmpstatus.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3kernelcore.h"
#include "evtmoon.h"
#include "fld.h"
#include "gohcalc.h"
#include "gohcombinetbl.h"
#include "gohcombunity.h"
#include "gohinit.h"
#include "gohmain.h"
#include "jmsmisc.h"
#include "localize.h"
#include "raijindlc.h"
#include "sbtlsub.h"
#include "sdat.h"

#define NATIVE_SKL_DRAW_MAX 8
#define lvTextOfs 1
#define listTextOfs 11
#define skilTextEnd 21
#define SEARCHI_LIST_MAX 10
#define CONDITION_LIST_MAX 10
#define SOUSA_OFS 1000
#define BACK_CARD_MAX 16
#define BACK_LIST_MAX 4
#define COMBI_WIDTH_MAX 3
#define COMBI_LIST_MAX 4
#define BACK_CSR_LOOP 4
#define COMBI_CSR_LOOP 3

typedef struct ResultCsr CombiCsr;
typedef struct MenuCsrUnity MenuCsrUnity;
typedef struct MenuCsrUnity MenuCsrUnitySp;
typedef struct NativeSkillCsr NativeSkillCsr;
typedef struct ResultCsr ResultCsr;
typedef struct gohData_t gohData_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

bool resultCheck;
NativeSkillStep nativeSkillStep;
SKLID setNativeSkill;
void *setNativeSkillList;
SKLID *rndChangeSkill;
s32 setNativeSkillEndCnt;
s32 nativeSkillInit;
NativeSkillCsr *nativeSkillCsr;
void *gohCombSearchCtrl;
MenuCsrUnitySp *searchiCsr;
MenuCsrUnitySp *conditionCsr;
void *allUnit_t;
bool allUnitTblCreated;
void *resultUnit_t;
void *combiTbl;
void *combiDrawTbl;
ResultCsr *resultCsr;
MenuCsrUnity *resultStatusCsr;
CombiCsr *combiCsr;
bool *sortSets;
MenuCsrUnity *sortCsr;
bool resultSort;
bool condition;
SearchiType decisionType;
void *conditionList;
void *conditionLvList;
void *conditionKudaList;
void *conditionSklTypeList;
void *conditionEndraceList;
char *searchiText;
char *searchiHelpText;
char *conditionText;
char *endureText;
char *sortText;
SearchiDrawSet *searchiDrawSet;
SKLID **searchiSklTbl;

// 0x1b94cc0
gohData_t *GohGetGohData(void) {
  gohData_t *result;

  result = (gohData_t *)dds3GetProcessData(GlobalPID);
  if (!result)
    return result;
  return result;
}

// 0x1b94dd0
CombStSeq GohGohNativeSq(void) {
  gohData_t *GohData;

  LODWORD(GohData) = gohProcessCheck();
  if (!(u32)GohData)
    return (s32)GohData;
  GohData = GohGetGohData();
  if (!GohData)
    return (s32)GohData;
  LODWORD(GohData) = GohData->combStSeq;
  return (s32)GohData;
}

// 0x1b94e90
void CombGuideDraw(gohData_t *_pData) {
  s32 SklCsr;
  s32 v7;
  s32 v8;
  s32 csrNo;
  void *nativeSkillList;
  s32 klass;
  bool v14;
  bool v16;

  if (pData->combStSeq != 1)
  {
    if (cmpGetModeSq() == 2)
    {
      v8 = 9;
      goto LABEL_56;
    }
    if (cmpGetModeSq() == 1)
    {
      v16 = cmpGetSklType(0) == 1;
      if (v16)
        v8 = 7;
      else
        v8 = 8;
      goto LABEL_56;
    }
    if (resultCheck || pData->m_iStatusType <= 1u)
    {
      v8 = 6;
    }
    else
    {
      v16 = GohGohNativeSq() == 0;
      if (v16)
        v8 = 25;
      else
        v8 = 26;
    }
    goto LABEL_56;
  }
  if (!cmpGetModeSq())
  {
    csrNo = nativeSkillCsr->csrNo;
    nativeSkillList = pData->BirthDevil->nativeSkillList;
    if (csrNo < nativeSkillList->_size)
    {
      csrNo = nativeSkillCsr->csrNo;
      klass = _get_Item(nativeSkillList, csrNo)[1].klass;
      v14 = _Contains(setNativeSkillList, klass);
      if (klass)
      {
        if (v14)
        {
          if (!nativeSkillCsr->endCursorOn)
            goto LABEL_52;
        }
      }
    }
    goto LABEL_54;
  }
  SklCsr = cmpGetSklCsr();
  v7 = SklCsr - nativeSkillInit;
  if (v7 < 0)
    goto LABEL_54;
  if (v7 >= setNativeSkillList->_size)
    goto LABEL_54;
  if (_get_Item(setNativeSkillList, v7))
  {
LABEL_52:
    v8 = 17;
    goto LABEL_56;
  }
LABEL_54:
  v8 = 12;
LABEL_56:
  gohSetDispButtonGuide(v8, 1, 0);
}

// 0x1b93fb0
void GohRndChangeListClear(void) {
  s64 i;
  char *v3;

  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(rndChangeSkill->max_length))
      break;
    v3 = (char *)rndChangeSkill + 4 * i;
    *((u32 *)v3 + 8) = 0;
  }
}

// 0x1b95280
void GohRndNativeSkillSet(sdatUnitWork_t *_barthDevil) {
  s32 nativeSkillSetCnt;
  void *v4;
  void *v5;
  void *nativeSkillList;
  s32 v7;
  s32 size;
  s32 v9;
  s32 v10;
  Il2CppObject *Item;
  s64 v12;
  s32 klass;
  u64 *v14;
  void *items;
  s32 v16;
  s32 v17;
  s32 v18;
  s32 v19;
  s64 v20;
  u64 *v21;
  void *v22;
  s32 v23;
  void *v24;
  s32 i;
  s32 v26;
  s32 v27;
  s64 v28;
  void *v29;
  s32 v30;
  const MethodInfo_2D926E0 *v34;
  s32 v36;
  s32 v39;

  nativeSkillSetCnt = barthDevil->nativeSkillSetCnt;
  v4 = Allocate(System_Collections_Generic_List_SKLID_);
  __ctor_47784064(v4, nativeSkillSetCnt);
  v5 = Allocate(System_Collections_Generic_List_SKLID_);
  __ctor(v5);
  nativeSkillList = barthDevil->nativeSkillList;
  if (nativeSkillList->_size < 1)
  {
    v16 = v5->_version + 1;
    v5->_size = 0;
    v5->_version = v16;
  }
  else
  {
    v7 = 0;
    do
    {
      if (HIDWORD(_get_Item(nativeSkillList, v7)[1].klass) == 2)
        HIDWORD(_get_Item(barthDevil->nativeSkillList, v7)[1].klass) = 1;
      nativeSkillList = barthDevil->nativeSkillList;
      ++v7;
      size = nativeSkillList->_size;
    }
    while (v7 < size);
    v9 = v5->_version + 1;
    v5->_size = 0;
    v5->_version = v9;
    if (size >= 1)
    {
      v10 = 0;
      do
      {
        if (HIDWORD(_get_Item(nativeSkillList, v10)[1].klass) == 1)
        {
          Item = _get_Item(barthDevil->nativeSkillList, v10);
          v12 = v5->_size;
          klass = Item[1].klass;
          v14 = Method_System_Collections_Generic_List_SKLID__Add__;
          ++v5->_version;
          items = v5->_items;
          if ((u32)v12 >= LODWORD(items->max_length))
          {
            _AddWithResize(v5, klass, *(const MethodInfo_2D92A30 **)(*(u64 *)(v14[4] + 192) + 112));
          }
          else
          {
            v5->_size = v12 + 1;
            *((u32 *)items + v12) = klass;
          }
        }
        nativeSkillList = barthDevil->nativeSkillList;
        ++v10;
      }
      while (v10 < nativeSkillList->_size);
    }
  }
  v17 = v4->_version + 1;
  v4->_size = 0;
  v4->_version = v17;
  if (nativeSkillSetCnt)
  {
    do
    {
      while (1)
      {
        v18 = sub_1905740((u32)v5->_size, 0);
        v19 = _get_Item(v5, v18);
        v20 = v4->_size;
        v21 = Method_System_Collections_Generic_List_SKLID__Add__;
        ++v4->_version;
        v22 = v4->_items;
        if ((u32)v20 < LODWORD(v22->max_length))
          break;
        _AddWithResize(v4, v19, *(const MethodInfo_2D92A30 **)(*(u64 *)(v21[4] + 192) + 112));
        _RemoveAt(v5, v18);
        if (!--nativeSkillSetCnt)
          goto LABEL_21;
      }
      v4->_size = v20 + 1;
      *((u32 *)v22 + v20) = v19;
      _RemoveAt(v5, v18);
      --nativeSkillSetCnt;
    }
    while (nativeSkillSetCnt);
LABEL_21:
    v23 = v4->_size;
    if (v23 >= 1)
    {
      v24 = barthDevil->nativeSkillList;
      if (v24->_size < 1)
        goto LABEL_32;
      for (i = 0; i < v23; ++i)
      {
        if (v24->_size >= 1)
        {
          v26 = 0;
          do
          {
            v27 = _get_Item(v4, i);
            if (v27 == LODWORD(_get_Item(barthDevil->nativeSkillList, v26)[1].klass))
              HIDWORD(_get_Item(barthDevil->nativeSkillList, v26)[1].klass) = 2;
            v24 = barthDevil->nativeSkillList;
            ++v26;
          }
          while (v26 < v24->_size);
          v23 = v4->_size;
        }
      }
      if (v23 >= 1)
      {
LABEL_32:
        v28 = 0;
        do
        {
          v34 = Method_System_Collections_Generic_List_SKLID__get_Item__;
          rndChangeSkill[v28] = 0;
          v36 = _get_Item(setNativeSkillList, v28, v34);
          if (v36 != _get_Item(v4, v28))
          {
            v29 = setNativeSkillList;
            v30 = _get_Item(v4, v28);
            _set_Item(v29, v28, v30);
            rndChangeSkill[v28] = _get_Item(v4, v28);
          }
          ++v28;
        }
        while (v28 < v4->_size);
      }
    }
  }
  v39 = barthDevil->nativeSkillSetCnt;
  setNativeSkillEndCnt = v39;
  nativeSkillCsr->endCursorOn = 1;
  SE(0);
}

// 0x1b95770
bool GohNativeSkillListUpdate(sdatUnitWork_t *_barthDevil) {
  s64 i;
  char *v11;
  s32 v14;
  void *nativeSkillList;
  void *v20;
  Il2CppObject *Item;
  s32 klass;

  if (nativeSkillStep == 3)
  {
    for (i = 0; ; ++i)
    {
      if (i >= SLODWORD(rndChangeSkill->max_length))
        break;
      v11 = (char *)rndChangeSkill + 4 * i;
      *((u32 *)v11 + 8) = 0;
    }
    return 1;
  }
  if (nativeSkillStep == 2)
  {
    cmpIncModeSq(1);
    v14 = nativeSkillInit
        + _IndexOf(setNativeSkillList, 0);
    if (v14 != -1)
    {
      cmpSetSklCsr(v14);
    }
    return 0;
  }
  if (nativeSkillStep != 1)
    return 0;
  (nativeSkillCsr->klass->vtable._5_SetMaxPar.methodPtr)(nativeSkillCsr, (u32)barthDevil->nativeSkillList->_size, 8, nativeSkillCsr->klass->vtable._5_SetMaxPar.method);
  (nativeSkillCsr->klass->vtable._10_CsrUpdate.methodPtr)(nativeSkillCsr, nativeSkillCsr->klass->vtable._10_CsrUpdate.method);
  if (CHECK_TRIG(4096, 1))
  {
    if (nativeSkillCsr->endCursorOn)
    {
LABEL_45:
      nativeSkillStep = 3;
LABEL_52:
      SE(0);
      return 0;
    }
    nativeSkillList = barthDevil->nativeSkillList;
    if (HIDWORD(_get_Item(nativeSkillList, nativeSkillCsr->csrNo)[1].klass))
    {
      v20 = barthDevil->nativeSkillList;
      Item = _get_Item(v20, nativeSkillCsr->csrNo);
      HIDWORD(Item[1].klass) = 2;
      klass = _get_Item(barthDevil->nativeSkillList, nativeSkillCsr->csrNo)[1].klass;
      nativeSkillStep = 2;
      setNativeSkill = klass;
      goto LABEL_52;
    }
    return 0;
  }
  if (!CHECK_TRIG(46594, 1))
  {
    if (CHECK_TRIG(46595, 1))
    {
      goto LABEL_45;
    }
    return 0;
  }
  GohRndNativeSkillSet(barthDevil);
  return 0;
}

// 0x1b95b50
void GohNativeSkillSetAllClear(gohData_t *_pData) {
  void *nativeSkillList;
  Il2CppObject *Instance;
  NativeSkillCsr *v5;
  s32 v12;
  s32 v13;
  u64 *v14;
  void *v15;
  s64 size;
  void *items;
  s32 v18;
  s32 v19;

  nativeSkillList = pData->BirthDevil->nativeSkillList;
  Instance = _get_Instance();
  (*(*(u64 *)Instance[10].monitor + 408))(Instance[10].monitor, *(u64 *)(*(u64 *)Instance[10].monitor + 416));
  v5 = Allocate(NativeSkillCsr);
  _ctor(v5, 0);
  *(u64 *)&v5->csrNo = 0;
  v5->endCursorOn = 0;
  v5->listDrwNo = 0;
  nativeSkillCsr = v5;
  setNativeSkillEndCnt = 0;
  v12 = setNativeSkillList->_version + 1;
  setNativeSkillList->_size = 0;
  setNativeSkillList->_version = v12;
  if (pData->BirthDevil->nativeSkillSetCnt >= 1)
  {
    v13 = 0;
    do
    {
      while (1)
      {
        v14 = Method_System_Collections_Generic_List_SKLID__Add__;
        v15 = setNativeSkillList;
        size = v15->_size;
        ++v15->_version;
        items = v15->_items;
        if ((u32)size < LODWORD(items->max_length))
          break;
        _AddWithResize(v15, 0, *(const MethodInfo_2D92A30 **)(*(u64 *)(v14[4] + 192) + 112));
        if (++v13 >= pData->BirthDevil->nativeSkillSetCnt)
          goto LABEL_12;
      }
      v15->_size = size + 1;
      *((u32 *)items + size) = 0;
      ++v13;
    }
    while (v13 < pData->BirthDevil->nativeSkillSetCnt);
  }
LABEL_12:
  if (nativeSkillList->_size >= 1)
  {
    v18 = 0;
    do
    {
      if (HIDWORD(_get_Item(nativeSkillList, v18)[1].klass) == 2)
        HIDWORD(_get_Item(nativeSkillList, v18)[1].klass) = 1;
      ++v18;
    }
    while (v18 < nativeSkillList->_size);
  }
  if (pData->m_eResultType != 5)
  {
    v19 = IndexOf_Int32Enum_(pData->BirthDevil->haveskill, 0);
LABEL_23:
    nativeSkillInit = v19;
    return;
  }
  if (evtMoonGetAge() != 8)
    return;
  v19 = 0;
  goto LABEL_23;
}

// 0x1b95e50
void GohInitSkillChange(gohData_t *_pData, bool _allReset) {
  Il2CppObject *Instance;

  if (pData->m_eResultType != 5)
    goto LABEL_12;
  if (evtMoonGetAge() == 8)
    goto LABEL_12;
  goto LABEL_11;
  if (evtMoonGetAge() != 8)
  {
LABEL_11:
    Instance = _get_Instance();
    (*(*(u64 *)Instance[10].monitor + 536))(Instance[10].monitor, 0, *(u64 *)(*(u64 *)Instance[10].monitor + 544));
  }
LABEL_12:
  *(u64 *)&nativeSkillStep = 1;
  if (!allReset)
  {
    if (pData->m_eResultType == 5)
    {
      if (evtMoonGetAge() != 8)
      {
        goto LABEL_23;
      }
    }
    GohSkl1SlotDel(pData);
    goto LABEL_23;
  }
  GohNativeSkillSetAllClear(pData);
  if ((nativeSkillInit & 0x80000000) == 0)
    return;
  goto LABEL_34;
LABEL_23:
  if ((nativeSkillInit & 0x80000000) == 0)
    return;
LABEL_34:
  nativeSkillInit = 0;
}

// 0x1b964e0
void GohReturnNativeSklSet(gohData_t *_pData) {
  if (pData->m_eResultType != 5)
    goto LABEL_11;
  if (evtMoonGetAge() == 8)
    goto LABEL_11;
  pData->combStSeq = 0;
  return;
LABEL_11:
  cmpSklTypeSet(0, 1);
  pData->combStSeq = 1;
}

// 0x1b96620
bool GohNaitiveSklMove(gohData_t *_pData) {
  if (resultCheck)
    return 0;
  if (!!cmpGetModeSq())
    return 0;
  if (pData->combStSeq)
    return 0;
  if (pData->m_eResultType != 5)
    return 1;
  return evtMoonGetAge() == 8;
}

// 0x1b967a0
bool GohMitamaNativeSklNone(gohData_t *_pData) {
  if (GohNaitiveSklMove(pData))
    return 0;
  return pData->m_eResultType == 5;
}

// 0x1b96850
bool GohMitamaBurstChk(gohData_t *_pData) {
  if ((byte_5756F5C & 1) != 0)
  {
    if (pData->m_eResultType != 5)
      return 0;
  }
  else
  {
    if (pData->m_eResultType != 5)
      return 0;
  }
  if (evtMoonGetAge() == 8)
    return 1;
  return 0;
}

// 0x1b960d0
bool GohNaitiveSklSetting(gohData_t *_pData) {
  if ((byte_5756FAD & 1) == 0)
  {
    if (pData->m_eResultType == 5)
      goto LABEL_3;
    return 1;
  }
  if (pData->m_eResultType != 5)
    return 1;
LABEL_3:
  return evtMoonGetAge() == 8;
}

// 0x1b96160
void GohSkl1SlotDel(gohData_t *_pData) {
  void *nativeSkillList;
  s32 size;
  s32 csrNo;
  void *v7;
  s32 klass;
  bool v9;
  char v11;
  s32 v13;
  s32 v20;

  nativeSkillList = pData->BirthDevil->nativeSkillList;
  size = nativeSkillList->_size;
  csrNo = nativeSkillCsr->csrNo;
  if (size <= csrNo)
    return;
  v7 = pData->BirthDevil->nativeSkillList;
  csrNo = nativeSkillCsr->csrNo;
  klass = _get_Item(v7, csrNo)[1].klass;
  v9 = _Contains(setNativeSkillList, klass);
  if (klass && v9)
  {
    if (nativeSkillCsr->endCursorOn)
      goto LABEL_13;
    v11 = 1;
    goto LABEL_15;
  }
LABEL_13:
  v11 = 0;
LABEL_15:
  v13 = setNativeSkillList->_size;
  nativeSkillCsr->endCursorOn = 0;
  if (v13 - 1 >= 0)
  {
    if ((v11 & 1) != 0)
    {
      while (1)
      {
        _get_Item(setNativeSkillList, --v13);
        if (_get_Item(setNativeSkillList, v13) == klass)
          break;
        if (v13 <= 0)
          goto LABEL_32;
      }
    }
    else
    {
      while (1)
      {
        if (_get_Item(setNativeSkillList, --v13))
        {
          break;
        }
        if (v13 <= 0)
          goto LABEL_32;
      }
    }
    --setNativeSkillEndCnt;
    klass = _get_Item(setNativeSkillList, v13);
    _set_Item(setNativeSkillList, v13, 0);
  }
LABEL_32:
  if (klass)
  {
    v20 = nativeSkillList->_size;
    if (v20 - 1 >= 0)
    {
      while (HIDWORD(_get_Item(nativeSkillList, --v20)[1].klass) != 2 || LODWORD(_get_Item(nativeSkillList, v20)[1].klass) != klass)
      {
        if (v20 <= 0)
          return;
      }
      HIDWORD(_get_Item(nativeSkillList, v20)[1].klass) = 1;
    }
  }
}

// 0x1b96900
void GohSkillChangeSettingDestroy(void) {
  NativeSkillCsr *v4;
  s32 v10;
  s64 i;
  char *v12;

  setNativeSkill = 0;
  nativeSkillInit = 0;
  v4 = Allocate(NativeSkillCsr);
  _ctor(v4, 0);
  *(u64 *)&v4->csrNo = 0;
  v4->endCursorOn = 0;
  v4->listDrwNo = 0;
  nativeSkillCsr = v4;
  nativeSkillStep = 0;
  setNativeSkillEndCnt = 0;
  v10 = setNativeSkillList->_version + 1;
  setNativeSkillList->_size = 0;
  setNativeSkillList->_version = v10;
  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(rndChangeSkill->max_length))
      break;
    v12 = (char *)rndChangeSkill + 4 * i;
    *((u32 *)v12 + 8) = 0;
  }
}

// 0x1b96a50
void GohSetNativeSkill(gohData_t *_pData) {
  void *v3;
  sdatUnitWork_t *BirthDevil;
  SKLID *battleskill;
  s64 v6;
  s32 v7;
  s32 v8;
  s32 v9;
  s32 v10;
  SKLID *haveskill;
  s32 v13;
  s32 Item;
  sdatUnitWork_t *v17;
  SKLID *v18;
  s64 v19;
  s32 SkillNo;
  char *v21;

  v3 = Allocate(Project_CMSkillPriority);
  _ctor(v3, 0);
  BirthDevil = pData->BirthDevil;
  battleskill = BirthDevil->battleskill;
  if (SLODWORD(battleskill->max_length) >= 1)
  {
    v6 = 0;
    do
    {
      v7 = battleskill[v6];
      if (v7)
      {
        AddSkillNo(v3, v7, 0);
        BirthDevil = pData->BirthDevil;
      }
      battleskill = BirthDevil->battleskill;
      ++v6;
    }
    while (v6 < SLODWORD(battleskill->max_length));
  }
  v8 = 0;
  v9 = 0;
  while (1)
  {
    if (v8 >= setNativeSkillList->_size)
      break;
    if (!_get_Item(setNativeSkillList, v8))
    {
      ++v9;
      goto LABEL_10;
    }
    Item = _get_Item(setNativeSkillList, v8);
    AddSkillNo(v3, Item, 0);
    v17 = pData->BirthDevil;
    v10 = datCheckRsvSkillCnt(v17);
    haveskill = pData->BirthDevil->haveskill;
    v13 = v8 + v10 + nativeSkillInit - v9;
    haveskill[v13] = _get_Item(setNativeSkillList, v8);
LABEL_10:
    ++v8;
  }
  Sort(v3, 0);
  v18 = pData->BirthDevil->battleskill;
  if (SLODWORD(v18->max_length) >= 1)
  {
    v19 = 0;
    do
    {
      SkillNo = GetSkillNo(v3, v19, 0);
      v21 = (char *)v18 + 4 * v19++;
      *((u32 *)v21 + 8) = SkillNo;
      v18 = pData->BirthDevil->battleskill;
    }
    while (SLODWORD(v18->max_length) > v19);
  }
}

// 0x1b96ce0
bool GohSkillChangeUpdate(gohData_t *_pData) {
  sdatUnitWork_t *BirthDevil;
  bool v5;
  Il2CppObject *Instance;

  BirthDevil = pData->BirthDevil;
  v5 = GohNativeSkillListUpdate(BirthDevil);
  if (!v5)
    return v5;
  Instance = _get_Instance();
  (*(*(u64 *)Instance[10].monitor + 536))(Instance[10].monitor, 0, *(u64 *)(*(u64 *)Instance[10].monitor + 544));
  pData->combStSeq = 2;
  return v5;
}

// 0x1b96dd0
void CombBackGuideSet(CmbBackStatus _type, bool _back) {
  s32 v8;

  if (resultSort)
    return;
  if (back)
  {
    if (resultCsr->statusCsr)
      v8 = 16;
    else
      v8 = 15;
    goto LABEL_22;
  }
  else
  {
    if (resultCsr->statusCsr)
      v8 = 24;
    else
      v8 = 23;
    goto LABEL_22;
  }
LABEL_22:
  gohSetDispButtonGuide(v8, 0, 0);
  return;
}

// 0x1b96f00
void GohCombiGuideSet(CmbBackStatus _type, bool _back, GohStatusType _statusType) {
  s32 v9;

  if (resultSort)
    return;
  if (back)
  {
    if (combiCsr->statusCsr)
      v9 = 16;
    else
      v9 = 15;
    goto LABEL_22;
  }
  else
  {
    if (combiCsr->statusCsr)
      v9 = 24;
    else
      v9 = 23;
    goto LABEL_22;
  }
LABEL_22:
  gohSetDispButtonGuide(v9, 0, 0);
  return;
}

// 0x1b97030
void *GohGetUnitList(SearchiType _type) {
  void *v3;
  s32 StockDevilNums;
  s32 v5;
  s32 v6;
  s32 v7;
  u64 v8;
  s64 v9;
  Project_GohCombUnity___c__DisplayClass69_0_Fields *p_fields;
  void *p__9__2;
  sdatUnitWork_t *v13;
  s32 devilid;
  bool v15;
  s32 v16;
  s32 v18;
  void *v20;
  Il2CppObject *devil;
  s64 v22;
  u64 *v23;
  s64 v24;
  s64 v25;
  s32 v26;
  s32 v27;
  __int128 v29;
  Il2CppObject *current;
  s32 klass_high;
  s32 v33;
  s64 v35;
  u64 *v36;
  s64 v37;
  s64 v38;
  void *_9__69_0;
  Il2CppObject *v42;
  void *v44;
  void *_9__69_1;
  Il2CppObject *v48;
  void *v50;
  void *v51;
  void *object;
  System_Collections_Generic_List_Enumerator_T__o v54;
  System_Collections_Generic_List_Enumerator_T__o v55;

  memset(&v55, 0, sizeof(v55));
  object = Allocate(Project_GohCombUnity___c__DisplayClass69_0);
  _c__DisplayClass69_0___ctor(object, 0);
  v3 = Allocate(System_Collections_Generic_List_sdatUnitWork_t_);
  __ctor(v3);
  if ((u32)type > 1)
  {
    v26 = v3->_size;
    v27 = v3->_version + 1;
    v3->_size = 0;
    v3->_version = v27;
    if (v26 >= 1)
      Clear(v3->_items, 0, v26, 0);
    _GetEnumerator(&v54, allUnit_t);
    v29 = *(_OWORD *)&v54._list;
    v54._list = 0;
    *(u64 *)&v54._index = &v55;
    v55._current = v54._current;
    *(_OWORD *)&v55._list = v29;
    while (1)
    {
      do
      {
        if (!_MoveNext(&v55))
        {
          _Dispose(&v55);
          goto LABEL_67;
        }
        current = v55._current;
        klass_high = SHIWORD(v55._current[1].klass);
      }
      while (!DlcDevilSelCheck(klass_high) || !BYTE4(current[1].klass));
      if (*(u32 *)((instance->klass->vtable._6_GetSearchiCtrl.methodPtr)(instance, instance->klass->vtable._6_GetSearchiCtrl.method) + 48) == -1)
      {
LABEL_64:
        v35 = v3->_size;
        v36 = Method_System_Collections_Generic_List_sdatUnitWork_t__Add__;
        ++v3->_version;
        v37 = v3->_items;
        if ((u32)v35 >= *(u32 *)(v37 + 24))
        {
          _AddWithResize(v3, current, *(const MethodInfo_2DFC660 **)(*(u64 *)(v36[4] + 192) + 112));
        }
        else
        {
          v38 = v37 + 8 * v35;
          v3->_size = v35 + 1;
          *(u64 *)(v38 + 32) = current;
        }
      }
      else
      {
        v33 = SBYTE4(current[1].klass);
        if (*(u32 *)((instance->klass->vtable._6_GetSearchiCtrl.methodPtr)(instance, instance->klass->vtable._6_GetSearchiCtrl.method) + 48) == v33)
          goto LABEL_64;
      }
    }
  }
  StockDevilNums = datGetStockDevilNums(0);
  v5 = v3->_size;
  v6 = StockDevilNums;
  v7 = v3->_version + 1;
  v3->_size = 0;
  v3->_version = v7;
  if (v5 >= 1)
    Clear(v3->_items, 0, v5, 0);
  if (v6 >= 1)
  {
    v8 = 0;
    v9 = 8 * (u32)v6;
    p_fields = &object->fields;
    p__9__2 = &object->__9__2;
    do
    {
      v13 = GBWK->player->stock_id[v8 / 8];
      p_fields->devil = v13;
      devilid = p_fields->devil->devilid;
      v15 = DlcDevilSelCheck(devilid);
      if (type != 1)
      {
        v16 = p_fields->devil->devilid;
        if (*(u32 *)((instance->klass->vtable._6_GetSearchiCtrl.methodPtr)(instance, instance->klass->vtable._6_GetSearchiCtrl.method) + 68) != v16 && v15)
        {
          goto LABEL_26;
        }
        goto LABEL_11;
      }
      v18 = p_fields->devil->devilid;
      if (*(u32 *)((instance->klass->vtable._6_GetSearchiCtrl.methodPtr)(instance, instance->klass->vtable._6_GetSearchiCtrl.method) + 32) != v18 && v15)
      {
LABEL_26:
        v20 = p__9__2;
        if (!p__9__2)
        {
          v20 = Allocate(System_Predicate_sdatUnitWork_t_);
          __ctor(v20, object, Method_Project_GohCombUnity___c__DisplayClass69_0__GetUnitList_b__2__, 0);
          object->__9__2 = v20;
        }
        if (!_Find(v3, v20))
        {
          devil = p_fields->devil;
          v22 = v3->_size;
          v23 = Method_System_Collections_Generic_List_sdatUnitWork_t__Add__;
          ++v3->_version;
          v24 = v3->_items;
          if ((u32)v22 >= *(u32 *)(v24 + 24))
          {
            _AddWithResize(v3, devil, *(const MethodInfo_2DFC660 **)(*(u64 *)(v23[4] + 192) + 112));
          }
          else
          {
            v25 = v24 + 8 * v22;
            v3->_size = v22 + 1;
            *(u64 *)(v25 + 32) = devil;
          }
        }
      }
LABEL_11:
      v8 += 8;
    }
    while (v9 != v8);
  }
LABEL_67:
  _9__69_0 = __9__69_0;
  if (!_9__69_0)
  {
    v42 = __9;
    _9__69_0 = Allocate(System_Func_sdatUnitWork_t__int_);
    int____ctor(_9__69_0, v42, Method_Project_GohCombUnity___c__GetUnitList_b__69_0__, 0);
    __9__69_0 = _9__69_0;
  }
  v44 = OrderBy_object__int_(v3, _9__69_0);
  _9__69_1 = __9__69_1;
  if (!_9__69_1)
  {
    v48 = __9;
    _9__69_1 = Allocate(System_Func_sdatUnitWork_t__sbyte_);
    sbyte____ctor(_9__69_1, v48, Method_Project_GohCombUnity___c__GetUnitList_b__69_1__, 0);
    __9__69_1 = _9__69_1;
  }
  v50 = ThenBy_object__sbyte_(v44, _9__69_1);
  v51 = Allocate(System_Collections_Generic_List_sdatUnitWork_t_);
  __ctor_48217552(v51, v50);
  return v51;
}

// 0x1b978e0
void GohCreateSklTextTbl(void *_tbl) {
}

// 0x1b97fc0
void *GohGetTextList(SearchiType _type) {
  void *v3;
  void *v5;
  void *UnitList;
  void *v7;
  s32 v8;
  s32 klass_high;
  char *v10;
  s32 v11;
  ConditionList *v12;
  s32 version;
  s64 size;
  u64 *v15;
  void *items;
  Il2CppClass **v17;
  void *conditionLvList_local;
  char *v25;
  char *LocalizeText;
  ConditionList *v27;
  const MethodInfo_2DFDA00 *v28;

  v3 = Allocate(System_Collections_Generic_List_ConditionList_);
  __ctor(v3);
  v5 = 0;
  switch (type)
  {
    case 0:
    case 1:
    case 6:
      UnitList = GohGetUnitList(type);
      if (UnitList->_size >= 1)
      {
        v7 = UnitList;
        v8 = 0;
        while (1)
        {
          klass_high = SHIWORD(_get_Item(v7, v8)[1].klass);
          v10 = sdatDevilName(klass_high, 0);
          v11 = SHIWORD(_get_Item(v7, v8)[1].klass);
          v12 = Allocate(ConditionList);
          v12->text = v10;
          version = v3->_version;
          size = v3->_size;
          v15 = Method_System_Collections_Generic_List_ConditionList__Add__;
          v12->setNo = v11;
          v3->_version = version + 1;
          items = v3->_items;
          if ((u32)size >= LODWORD(items->max_length))
          {
            _AddWithResize(v3, v12, *(const MethodInfo_2DFC660 **)(*(u64 *)(v15[4] + 192) + 112));
            if (++v8 >= v7->_size)
              goto LABEL_12;
          }
          else
          {
            v17 = &items->obj.klass + size;
            v3->_size = size + 1;
            v17[4] = v12;
            if (++v8 >= v7->_size)
            {
LABEL_12:
              v5 = v3;
              goto LABEL_31;
            }
          }
        }
      }
      v5 = v3;
LABEL_31:
      v25 = conditionText[0];
      LocalizeText = GetLocalizeText(v25, 1);
      v27 = Allocate(ConditionList);
      v27->text = LocalizeText;
      v28 = Method_System_Collections_Generic_List_ConditionList__Insert__;
      v27->setNo = -1;
      _Insert(v5, 0, v27, v28);
      return v5;
    case 3:
    case 4:
      conditionLvList_local = conditionLvList;
      goto LABEL_30;
    case 5:
      conditionLvList_local = conditionKudaList;
      goto LABEL_30;
    case 7:
      conditionLvList_local = conditionSklTypeList;
      goto LABEL_30;
    case 8:
      CreateSklTextTbl(v3);
      v5 = v3;
      goto LABEL_31;
    case 9:
      conditionLvList_local = conditionEndraceList;
LABEL_30:
      v5 = Allocate(System_Collections_Generic_List_ConditionList_);
      __ctor_48217552(v5, conditionLvList_local);
      goto LABEL_31;
    default:
      goto LABEL_31;
  }
}

// 0x1b983b0
void GohLoadConditionTbl(void) {
  s32 size;
  s32 v4;
  bool v5;
  void *v7;
  char *v8;
  s32 v9;
  ConditionList *v10;
  s32 version;
  s64 v12;
  u64 *v13;
  void *items;
  Il2CppClass **v15;
  s32 v18;
  s32 v19;
  s32 v20;
  void *v22;
  char *v23;
  s32 v24;
  ConditionList *v25;
  s32 v26;
  s64 v27;
  u64 *v28;
  void *v29;
  Il2CppClass **v30;
  s32 v33;
  s32 v34;
  s32 v35;
  void *v38;
  char *v39;
  char *LocalizeText;
  s32 v41;
  ConditionList *v42;
  s32 v43;
  s64 v44;
  u64 *v45;
  void *v46;
  Il2CppClass **v47;
  s32 v50;
  s32 v51;
  s32 j;
  void *v56;
  char *v57;
  char *v58;
  s32 v59;
  ConditionList *v60;
  s32 v61;
  s64 v62;
  u64 *v63;
  void *v64;
  Il2CppClass **v65;
  s32 i;

  size = conditionLvList->_size;
  v4 = conditionLvList->_version + 1;
  conditionLvList->_size = 0;
  conditionLvList->_version = v4;
  if (size >= 1)
    Clear(conditionLvList->_items, 0, size, 0);
  i = 1;
  do
  {
    while (1)
    {
      v7 = conditionLvList;
      v8 = ToString((s32)&i, 0);
      v9 = i;
      v10 = Allocate(ConditionList);
      v10->text = v8;
      version = v7->_version;
      v12 = v7->_size;
      v13 = Method_System_Collections_Generic_List_ConditionList__Add__;
      v10->setNo = v9;
      v7->_version = version + 1;
      items = v7->_items;
      if ((u32)v12 < LODWORD(items->max_length))
        break;
      _AddWithResize(v7, v10, *(const MethodInfo_2DFC660 **)(*(u64 *)(v13[4] + 192) + 112));
      v5 = i - 99 < 0;
      if (v5 == __OFSUB__(++i, 100))
        goto LABEL_14;
    }
    v15 = &items->obj.klass + v12;
    v7->_size = v12 + 1;
    v15[4] = v10;
    v5 = i - 99 < 0;
    ++i;
  }
  while (v5 != __OFSUB__(i, 100));
LABEL_14:
  v18 = conditionKudaList->_size;
  v19 = conditionKudaList->_version + 1;
  conditionKudaList->_size = 0;
  conditionKudaList->_version = v19;
  if (v18 >= 1)
    Clear(conditionKudaList->_items, 0, v18, 0);
  v20 = 1;
  for (i = 1; i < 10; v20 = i)
  {
    while (1)
    {
      v22 = conditionKudaList;
      v23 = sdatRaceName(v20);
      v24 = i;
      v25 = Allocate(ConditionList);
      v25->text = v23;
      v26 = v22->_version;
      v27 = v22->_size;
      v28 = Method_System_Collections_Generic_List_ConditionList__Add__;
      v25->setNo = v24;
      v22->_version = v26 + 1;
      v29 = v22->_items;
      if ((u32)v27 < LODWORD(v29->max_length))
        break;
      _AddWithResize(v22, v25, *(const MethodInfo_2DFC660 **)(*(u64 *)(v28[4] + 192) + 112));
      v20 = ++i;
      if (i >= 10)
        goto LABEL_27;
    }
    v30 = &v29->obj.klass + v27;
    v22->_size = v27 + 1;
    v30[4] = v25;
    ++i;
  }
LABEL_27:
  v33 = conditionSklTypeList->_size;
  v34 = conditionSklTypeList->_version + 1;
  conditionSklTypeList->_size = 0;
  conditionSklTypeList->_version = v34;
  if (v33 >= 1)
    Clear(conditionSklTypeList->_items, 0, v33, 0);
  v35 = 11;
  i = 11;
  do
  {
    while (1)
    {
      v35 = i;
      v38 = conditionSklTypeList;
      v39 = conditionText[v35];
      LocalizeText = GetLocalizeText(v39, 1);
      v41 = i;
      v42 = Allocate(ConditionList);
      v42->text = LocalizeText;
      v43 = v38->_version;
      v44 = v38->_size;
      v45 = Method_System_Collections_Generic_List_ConditionList__Add__;
      v42->setNo = v41 - 11;
      v38->_version = v43 + 1;
      v46 = v38->_items;
      if ((u32)v44 < LODWORD(v46->max_length))
        break;
      _AddWithResize(v38, v42, *(const MethodInfo_2DFC660 **)(*(u64 *)(v45[4] + 192) + 112));
      v5 = i - 21 < 0;
      v35 = ++i;
      if (v5 == __OFSUB__(i, 22))
        goto LABEL_40;
    }
    v47 = &v46->obj.klass + v44;
    v38->_size = v44 + 1;
    v47[4] = v42;
    v5 = i - 21 < 0;
    v35 = ++i;
  }
  while (v5 != __OFSUB__(i, 22));
LABEL_40:
  v50 = conditionEndraceList->_size;
  v51 = conditionEndraceList->_version + 1;
  conditionEndraceList->_size = 0;
  conditionEndraceList->_version = v51;
  if (v50 >= 1)
    Clear(conditionEndraceList->_items, 0, v50, 0);
  for (j = 0; ; j = i + 1)
  {
    i = j;
    if (j >= SLODWORD(endureText->max_length))
      break;
    v56 = conditionEndraceList;
    v57 = endureText[i];
    v58 = GetLocalizeText(v57, 1);
    v59 = i;
    v60 = Allocate(ConditionList);
    v60->text = v58;
    v61 = v56->_version;
    v62 = v56->_size;
    v63 = Method_System_Collections_Generic_List_ConditionList__Add__;
    v60->setNo = v59;
    v56->_version = v61 + 1;
    v64 = v56->_items;
    if ((u32)v62 >= LODWORD(v64->max_length))
    {
      _AddWithResize(v56, v60, *(const MethodInfo_2DFC660 **)(*(u64 *)(v63[4] + 192) + 112));
    }
    else
    {
      v65 = &v64->obj.klass + v62;
      v56->_size = v62 + 1;
      v65[4] = v60;
    }
  }
}

// 0x1b98980
bool CombCheck(bool *_type) {
  if (type[0])
    return 0;
  if (type[1])
    return 0;
  if (type[2])
    return 0;
  if (type[3])
    return 0;
  if (type[4])
    return 0;
  if (type[5])
    return 0;
  if (type[6])
    return 0;
  return !type[7];
}

// 0x1b98a00
bool GohCreateResultTbl(bool _serchi) {
  void *v2;
  void *v3;
  s32 v4;
  s32 v5;
  void *v7;
  __int128 v8;
  void *v9;
  Il2CppObject *current;
  Project_GohCombUnity___c__DisplayClass74_0_Fields *p_fields;
  sdatUnitWork_t *v12;
  void *v13;
  Il2CppObject *v14;
  sdatUnitWork_t *v15;
  Il2CppClass *klass;
  s32 v17;
  u64 *v18;
  s64 v19;
  s64 v20;
  s64 v21;
  System_Collections_Generic_List_Enumerator_T__o v26;
  System_Collections_Generic_List_Enumerator_T__o v27;

  memset(&v27, 0, sizeof(v27));
  v2 = Allocate(System_Collections_Generic_List_sdatUnitWork_t_);
  __ctor(v2);
  v3 = Allocate(System_Collections_Generic_List_sdatUnitWork_t_);
  __ctor(v3);
  v4 = v3->_size;
  v5 = v3->_version + 1;
  v3->_size = 0;
  v3->_version = v5;
  if (v4 >= 1)
    Clear(v3->_items, 0, v4, 0);
  v7 = (instance->klass->vtable._8_GetSearchCombTbls.methodPtr)(instance, 0, instance->klass->vtable._8_GetSearchCombTbls.method);
  _GetEnumerator(&v26, v7);
  v27._current = v26._current;
  v8 = *(_OWORD *)&v26._list;
  v26._list = 0;
  *(u64 *)&v26._index = &v27;
  *(_OWORD *)&v27._list = v8;
  while (_MoveNext(&v27))
  {
    v9 = Allocate(Project_GohCombUnity___c__DisplayClass74_0);
    _c__DisplayClass74_0___ctor(v9, 0);
    current = v27._current;
    v9->name = (void *)v27._current;
    p_fields = &v9->fields;
    v12 = Allocate(sdatUnitWork_t);
    _ctor(v12, 0);
    v13 = Allocate(System_Predicate_sdatUnitWork_t_);
    __ctor(v13, v9, Method_Project_GohCombUnity___c__DisplayClass74_0__CreateResultTbl_b__0__, 0);
    v14 = _Find(v3, v13);
    v15 = v14;
    if (v14)
    {
      klass = v14[16].klass;
      if (LOBYTE(klass->_1.byval_arg.data) || BYTE1(klass->_1.byval_arg.data) || BYTE2(klass->_1.byval_arg.data) || BYTE3(klass->_1.byval_arg.data) || BYTE4(klass->_1.byval_arg.data) || BYTE5(klass->_1.byval_arg.data) || BYTE6(klass->_1.byval_arg.data) || HIBYTE(klass->_1.byval_arg.data))
      {
        ClassCopy(v12, p_fields->name->_barthDevil_k__BackingField, 0);
        v12->restoreMoney = p_fields->name->_devil2_k__BackingField->restoreMoney
                                 + p_fields->name->_devil1_k__BackingField->restoreMoney;
        ClassCopy(v15, v12, 0);
      }
    }
    else
    {
      ClassCopy(v12, p_fields->name->_barthDevil_k__BackingField, 0);
      v17 = p_fields->name->_devil2_k__BackingField->restoreMoney
          + p_fields->name->_devil1_k__BackingField->restoreMoney;
      v12->restoreMoney = v17;
      if (!serchi && v17)
      {
        _Dispose(&v27);
        return 0;
      }
      v18 = Method_System_Collections_Generic_List_sdatUnitWork_t__Add__;
      v19 = v3->_size;
      ++v3->_version;
      v20 = v3->_items;
      if ((u32)v19 >= *(u32 *)(v20 + 24))
      {
        _AddWithResize(v3, v12, *(const MethodInfo_2DFC660 **)(*(u64 *)(v18[4] + 192) + 112));
      }
      else
      {
        v21 = v20 + 8 * v19;
        v3->_size = v19 + 1;
        *(u64 *)(v21 + 32) = v12;
      }
    }
  }
  _Dispose(&v27);
  resultUnit_t = v3;
  return 1;
}

// 0x1b98ef0
bool GohCreateAllUnitSortTbl(gohData_t *pData) {
  if (allUnitTblCreated)
    return 1;
  GohCreateAllTbl();
  (instance->klass->vtable._9_CombCreateTblSettingClear.methodPtr)(instance, instance->klass->vtable._9_CombCreateTblSettingClear.method);
  return 1;
}

// 0x1b993c0
void GohAllUnitSortTbl(void) {
  void *_9__76_0;
  Il2CppObject *v7;
  void *v9;
  void *v10;

  _9__76_0 = __9__76_0;
  if (!_9__76_0)
  {
    v7 = __9;
    _9__76_0 = Allocate(System_Func_sdatUnitWork_t__short_);
    short____ctor(_9__76_0, v7, Method_Project_GohCombUnity___c__AllUnitSortTbl_b__76_0__, 0);
    __9__76_0 = _9__76_0;
  }
  v9 = OrderBy_object__short_(allUnit_t, _9__76_0);
  v10 = Allocate(System_Collections_Generic_List_sdatUnitWork_t_);
  __ctor_48217552(v10, v9);
  allUnit_t = v10;
}

// 0x1b99030
void GohCreateAllTbl(void) {
  void *v2;
  void *v3;
  s32 v5;
  s32 v6;
  void *AllKarteUnitList;
  void *v8;
  Il2CppObject *current;
  void *v10;
  s64 v11;
  Il2CppObject *karteUnit;
  u64 *v13;
  s64 v14;
  s64 v15;
  System_Collections_Generic_List_Enumerator_T__o v19;
  System_Collections_Generic_List_Enumerator_T__o v20;

  memset(&v20, 0, sizeof(v20));
  if (allUnitTblCreated)
    return;
  v2 = Allocate(System_Collections_Generic_List_sdatUnitWork_t_);
  __ctor(v2);
  v3 = Allocate(System_Collections_Generic_List_sdatUnitWork_t_);
  __ctor(v3);
  v5 = v3->_size;
  v6 = v3->_version + 1;
  v3->_size = 0;
  v3->_version = v6;
  if (v5 >= 1)
    Clear(v3->_items, 0, v5, 0);
  AllKarteUnitList = gohCreateAllKarteUnitList();
  if (AllKarteUnitList)
  {
    _GetEnumerator(&v19, AllKarteUnitList);
    v20 = v19;
    v19._list = 0;
    *(u64 *)&v19._index = &v20;
    while (_MoveNext(&v20))
    {
      v8 = Allocate(Project_GohCombUnity___c__DisplayClass77_0);
      _c__DisplayClass77_0___ctor(v8, 0);
      current = v20._current;
      v8->karteUnit = (sdatUnitWork_t *)v20._current;
      v10 = Allocate(System_Predicate_sdatUnitWork_t_);
      __ctor(v10, v8, Method_Project_GohCombUnity___c__DisplayClass77_0__CreateAllTbl_b__0__, 0);
      if (!_Find(v3, v10))
      {
        v11 = v3->_size;
        karteUnit = v8->karteUnit;
        v13 = Method_System_Collections_Generic_List_sdatUnitWork_t__Add__;
        ++v3->_version;
        v14 = v3->_items;
        if ((u32)v11 >= *(u32 *)(v14 + 24))
        {
          _AddWithResize(v3, karteUnit, *(const MethodInfo_2DFC660 **)(*(u64 *)(v13[4] + 192) + 112));
        }
        else
        {
          v15 = v14 + 8 * v11;
          v3->_size = v11 + 1;
          *(u64 *)(v15 + 32) = karteUnit;
        }
      }
    }
    _Dispose(&v20);
  }
  allUnit_t = v3;
  GohAllUnitSortTbl();
  allUnitTblCreated = 1;
}

// 0x1b99590
void GohResultSortFunc(void) {
  void *Instance;
  void *DvlList;

  Instance = get_Instance(0);
  DvlList = GetDvlList(Instance, 0, 0);
  resultUnit_t = DvlList;
}

// 0x1b99650
void GohCmbSortFunc(void) {
  void *Instance;
  void *SearchComblList;

  Instance = get_Instance(0);
  SearchComblList = GetSearchComblList(Instance, 0);
  combiTbl = SearchComblList;
}

// 0x1b99700
void GohSortOnFunc(void) {
  resultSort = 1;
  return;
}

// 0x1b99790
void GohSortOffFunc(void) {
  resultSort = 0;
  return;
}

// 0x1b99810
void GohResultCalcSortSetting(gohData_t *_pData) {
  void *Instance;
  void *v3;
  void *v5;
  void *v6;
  void *v7;
  void *v8;
  void *v9;

  Instance = get_Instance(0);
  SortSetting(Instance, 11, 0);
  v3 = get_Instance(0);
  ListSet_object_(v3, resultUnit_t);
  v5 = get_Instance(0);
  v6 = Allocate(System_Action);
  _ctor(v6, 0, Method_Project_GohCombUnity_ResultSortFunc__, 0);
  SetSortCallBack(v5, v6, 0);
  v7 = get_Instance(0);
  v8 = Allocate(System_Action);
  _ctor(v8, 0, Method_Project_GohCombUnity_SortOnFunc__, 0);
  v9 = Allocate(System_Action);
  _ctor(v9, 0, Method_Project_GohCombUnity_SortOffFunc__, 0);
  SetActiveCallBack(v7, v8, v9, 0);
}

// 0x1b999d0
void GohCmbCalcSortSetting(gohData_t *_pData) {
  void *Instance;
  void *v3;
  void *v5;
  void *v6;
  void *v7;
  void *v8;
  void *v9;

  Instance = get_Instance(0);
  SortSetting(Instance, 12, 0);
  v3 = get_Instance(0);
  ListSet_object_(v3, combiTbl);
  v5 = get_Instance(0);
  v6 = Allocate(System_Action);
  _ctor(v6, 0, Method_Project_GohCombUnity_CmbSortFunc__, 0);
  SetSortCallBack(v5, v6, 0);
  v7 = get_Instance(0);
  v8 = Allocate(System_Action);
  _ctor(v8, 0, Method_Project_GohCombUnity_SortOnFunc__, 0);
  v9 = Allocate(System_Action);
  _ctor(v9, 0, Method_Project_GohCombUnity_SortOffFunc__, 0);
  SetActiveCallBack(v7, v8, v9, 0);
}

// 0x1b99b90
void GohResultGetStatusCsrCnt(gohData_t *_pData, s32 *_cursorMax, s32 *_listMaxCnt) {
  Il2CppObject *Item;
  sdatUnitWork_t *DevilFormatDevil;
  s32 cmbBackStatus;
  sdatUnitWork_t *v14;
  SKLID *haveskill;
  s32 v16;
  s64 max_length;
  s32 *m_Items;
  s32 v20;
  s32 v21;
  SKLID *v22;
  SKLID *aOmoideSkill;
  bool v24;
  s32 klass_high;
  s32 skill2;
  s32 skill1;

  if (resultUnit_t->_size >= 1)
    goto LABEL_4;
  v20 = 0;
  v21 = 0;
LABEL_24:
  *cursorMax = v20;
  goto LABEL_26;
LABEL_4:
  Item = _get_Item(resultUnit_t, resultCsr->csrNo);
  DevilFormatDevil = GohCreateDevilFormatDevil(SHIWORD(Item[1].klass));
  cmbBackStatus = pData->cmbBackStatus;
  v14 = DevilFormatDevil;
  if (cmbBackStatus == 1)
  {
    v22 = NewSpecific(SKLID, 2u);
    aOmoideSkill = v14->aOmoideSkill;
    v22[0] = 0;
    v22[0] = aOmoideSkill[0];
    v22[1] = 0;
    LODWORD(aOmoideSkill) = aOmoideSkill[1];
    v24 = (u32)aOmoideSkill == 0;
    v22[1] = (u32)aOmoideSkill;
    v21 = 8;
    if (v24)
      v20 = 1;
    else
      v20 = 2;
    goto LABEL_24;
  }
  if (cmbBackStatus)
  {
    skill1 = 255;
    skill2 = 255;
    klass_high = SHIWORD(_get_Item(resultUnit_t, resultCsr->csrNo)[1].klass);
    mskGetNo(klass_high, &skill1, &skill2);
    v20 = 2;
    v21 = 2;
    goto LABEL_24;
  }
  haveskill = DevilFormatDevil->haveskill;
  *cursorMax = 0;
  if ((s32)haveskill->max_length >= 1)
  {
    v16 = 0;
    max_length = (u32)haveskill->max_length;
    m_Items = haveskill;
    do
    {
      if (*m_Items++)
        *cursorMax = ++v16;
      --max_length;
    }
    while (max_length);
  }
  v21 = 8;
LABEL_26:
  *listMaxCnt = v21;
}

// 0x1b99f40
void GohSetStatusCsrCollider(CmbBackStatus _status, MenuCsrUnity *_csr) {
  ;
}

// 0x1b99dd0
sdatUnitWork_t *GohCreateDevilFormatDevil(s32 _devilID) {
  sdatUnitWork_t *v3;
  SKLID *aOmoideSkill;
  SKLID *v5;
  SKLID *v6;
  s32 v7;
  s32 v8;

  v3 = (sdatUnitWork_t *)Allocate(sdatUnitWork_t);
  _ctor(v3, 0);
  datCreateDevilUnit(devilID, v3);
  aOmoideSkill = v3->aOmoideSkill;
  aOmoideSkill[0] = sBtlGetDevilData(devilID, -1)->memskill[0]->skill;
  v5 = v3->aOmoideSkill;
  v5[1] = sBtlGetDevilData(devilID, -1)->memskill[1]->skill;
  v6 = v3->aOmoideSkill;
  v7 = v6[0];
  if (v7)
  {
    datOmoideSkillSetMaster(v3, v7, 1);
    v6 = v3->aOmoideSkill;
  }
  v8 = v6[1];
  if (v8)
  {
    datOmoideSkillSetMaster(v3, v8, 1);
  }
  return v3;
}

// 0x1b99f50
void GohCreateCombiTbl(gohData_t *_pData) {
  void *v3;
  void *v5;
  void *v6;
  void *v7;
  void *v8;

  v3 = Allocate(Project_GohCombUnity___c__DisplayClass87_0);
  _c__DisplayClass87_0___ctor(v3, 0);
  v3->_pData = pData;
  v5 = (instance->klass->vtable._8_GetSearchCombTbls.methodPtr)(instance, 0, instance->klass->vtable._8_GetSearchCombTbls.method);
  v6 = Allocate(System_Func_SearchCombTbl__bool_);
  bool____ctor(v6, v3, Method_Project_GohCombUnity___c__DisplayClass87_0__CreateCombiTbl_b__0__, 0);
  v7 = Where_object_(v5, v6);
  v8 = Allocate(System_Collections_Generic_List_SearchCombTbl_);
  __ctor_48217552(v8, v7);
  combiTbl = v8;
}

// 0x1b9a140
void CombStatusCheck(gohData_t *_pData, GohStatusType _type) {
  gohResult_t *v5;
  jmsSeqUnit_t *p_pSeqUnit;
  jmsSeqUnit_t *gohSeqUnit_local;
  Il2CppObject *Instance;
  sdatUnitWork_t *BirthDevil;

  v5 = Allocate(gohResult_t);
  _ctor(v5, 0);
  if (type == 1)
  {
    pData->m_iStatusType = 1;
    goto LABEL_9;
  }
  if (!type)
  {
    pData->m_iStatusType = 0;
LABEL_9:
    resultCheck = 0;
    p_pSeqUnit = &pData->pSeqUnit;
    goto LABEL_11;
  }
  Instance = _get_Instance();
  (*(*(u64 *)Instance[10].monitor + 536))(Instance[10].monitor, 0, *(u64 *)(*(u64 *)Instance[10].monitor + 544));
  BirthDevil = pData->BirthDevil;
  resultCheck = 1;
  ClassCopy(BirthDevil, pData->combiBarthDevil, 0);
  pData->m_iStatusType = 2;
  p_pSeqUnit = &pData->pSeqUnit;
LABEL_11:
  gohSeqUnit_local = gohSeqUnit;
  jmsSeqJumpAndFree(p_pSeqUnit, &gohSeqUnit_local[12]);
  SE(0);
}

// 0x1b9a300
void GohDisableComb(gohData_t *_pData, sdatUnitWork_t *_devil1, sdatUnitWork_t *_devil2, sdatUnitWork_t *_barthDevil) {
  sdatUnitWork_t *v9;
  sdatUnitWork_t *v10;
  gohResult_t *v11;
  s32 v15;
  sdatUnitWork_t *v16;
  s32 v17;
  s16 v20;
  sdatUnitWork_t *v22;
  sdatUnitWork_t *v23;
  sdatUnitWork_t *BirthDevil;
  s32 restoreMoney;
  u32 v26;
  jmsSeqUnit_t *p_pSeqUnit;
  jmsSeqUnit_t *gohSeqUnit_local;

  v9 = Allocate(sdatUnitWork_t);
  _ctor(v9, 0);
  ClassCopy(v9, devil1, 0);
  v10 = Allocate(sdatUnitWork_t);
  _ctor(v10, 0);
  ClassCopy(v10, devil2, 0);
  v11 = Allocate(gohResult_t);
  _ctor(v11, 0);
  if (*(s32 *)((u64)v9->now + 16) >= 1 && *(s32 *)((u64)v10->now + 16) >= 1 && (*(u8 *)((char *)v9 + 146) & 0x12) == 0 && (*(u8 *)((char *)v10 + 146) & 0x12) == 0)
  {
    resultCheck = 0;
    v15 = gohNormal(pData, &v11->Devil, v9, v10);
    v16 = v11->Devil;
    v11->m_iType = v15;
    v17 = v9->devilid;
    v16->badstatus = 0;
    gohCreateGoodbyMes(pData, v17, v10->devilid);
    if (gohGift(v11, v11->Devil, v9, v10))
    {
      pData->m_iGiftDevilNo = v11->m_iDevilNo;
      v20 = v11->m_iMesNo;
      *(u32 *)&pData->m_iGiftItemNo = *(u32 *)&v11->m_iItemNo;
      pData->m_DvlReport = v11->m_iDvlReport;
    }
    else
    {
      v20 = 0;
    }
    pData->m_iGiftMesNo = v20;
    v22 = Allocate(sdatUnitWork_t);
    _ctor(v22, 0);
    pData->m_ReprtDevil1 = v22;
    v23 = Allocate(sdatUnitWork_t);
    _ctor(v23, 0);
    pData->m_ReprtDevil2 = v23;
    ClassCopy(pData->m_ReprtDevil1, v9, 0);
    ClassCopy(pData->m_ReprtDevil2, v10, 0);
    ClassCopy(pData->BirthDevil, v11->Devil, 0);
    Copy_56180528(barthDevil->cmbTblErrorType, pData->BirthDevil->cmbTblErrorType, barthDevil->cmbTblErrorType->max_length, 0);
    BirthDevil = pData->BirthDevil;
    restoreMoney = barthDevil->restoreMoney;
    pData->combiDevil1 = v9;
    BirthDevil->restoreMoney = restoreMoney;
    LODWORD(BirthDevil) = v11->m_iType;
    pData->m_iStatusType = 2;
    pData->m_eResultType = (s32)BirthDevil;
    pData->combiDevil2 = v10;
    v26 = v9->uniq_code;
    pData->combStSeq = 0;
    pData->devilUniq1 = v26;
    pData->devilUniq2 = v10->uniq_code;
    p_pSeqUnit = &pData->pSeqUnit;
    gohSeqUnit_local = gohSeqUnit;
    jmsSeqJumpAndFree(p_pSeqUnit, &gohSeqUnit_local[12]);
    return;
  }
}

// 0x1b9a680
void GohCombiGetStatusCsrCnt(gohData_t *_pData, s32 _curType, s32 _hightNum, s32 *_cursorMax, s32 *_listMaxCnt) {
  s32 cmbBackStatus;
  Il2CppObject *v13;
  SKLID *haveskill;
  s32 v16;
  s64 max_length;
  s32 *m_Items;
  Il2CppObject *Item;
  sdatUnitWork_t *DevilFormatDevil;
  s32 Count;
  s32 v26;
  Il2CppObject *v28;
  u64 *monitor;
  char *typeMetadataHandle;
  s64 v32;
  Il2CppClass *klass;
  s32 v35;
  u32 *v36;
  s32 name_high;
  s32 skill2;
  s32 skill1;

  cmbBackStatus = pData->cmbBackStatus;
  if (cmbBackStatus == 1)
  {
    if (curType)
    {
      if (curType == 2)
      {
        Item = _get_Item(combiTbl, hightNum);
        DevilFormatDevil = GohCreateDevilFormatDevil(*((s16 *)Item[2].monitor + 11));
        goto LABEL_20;
      }
      else
      {
        DevilFormatDevil = _get_Item(combiTbl, hightNum)[2].klass;
        goto LABEL_20;
      }
    }
    else
    {
      DevilFormatDevil = _get_Item(combiTbl, hightNum)[1].monitor;
      goto LABEL_20;
    }
LABEL_20:
    Count = datOmoideSkillGetCount(DevilFormatDevil);
    v26 = 8;
LABEL_55:
    *cursorMax = Count;
    goto LABEL_56;
  }
  if (cmbBackStatus)
  {
    skill1 = 255;
    skill2 = 255;
    if (curType == 1)
    {
      v28 = _get_Item(combiTbl, hightNum)
          + 2;
    }
    else if (curType)
    {
      v28 = ((char *)_get_Item(combiTbl, hightNum) + 40);
    }
    else
    {
      v28 = ((char *)_get_Item(combiTbl, hightNum) + 24);
    }
    name_high = SHIWORD(v28->klass->_1.name);
    mskGetNo(name_high, &skill1, &skill2);
    Count = 2;
    v26 = 2;
    goto LABEL_55;
  }
  if (!curType)
  {
    monitor = _get_Item(combiTbl, hightNum)[1].monitor;
    *cursorMax = 0;
    typeMetadataHandle = monitor[13];
    v32 = *((u64 *)typeMetadataHandle + 3);
    if ((s32)v32 < 1)
      goto LABEL_37;
LABEL_33:
    v35 = 0;
    v32 = (u32)v32;
    v36 = typeMetadataHandle + 32;
    do
    {
      if (*v36++)
        *cursorMax = ++v35;
      --v32;
    }
    while (v32);
    goto LABEL_37;
  }
  if (curType != 2)
  {
    klass = _get_Item(combiTbl, hightNum)[2].klass;
    *cursorMax = 0;
    typeMetadataHandle = klass->_1.typeMetadataHandle;
    v32 = *((u64 *)typeMetadataHandle + 3);
    if ((s32)v32 < 1)
      goto LABEL_37;
    goto LABEL_33;
  }
  v13 = _get_Item(combiTbl, hightNum);
  haveskill = GohCreateDevilFormatDevil(*((s16 *)v13[2].monitor + 11))->haveskill;
  *cursorMax = 0;
  if ((s32)haveskill->max_length >= 1)
  {
    v16 = 0;
    max_length = (u32)haveskill->max_length;
    m_Items = haveskill;
    do
    {
      if (*m_Items++)
        *cursorMax = ++v16;
      --max_length;
    }
    while (max_length);
  }
LABEL_37:
  v26 = 8;
LABEL_56:
  *listMaxCnt = v26;
}

// 0x1b9aad0
void GohNativeSkillSet(gohData_t *_pData, u32 _pad) {
  char v3;
  sdatUnitWork_t *BirthDevil;
  s32 v8;
  s32 v11;
  s32 SklCsr;
  s32 v16;
  void *nativeSkillList;
  s32 Item;
  s32 size;
  void *v23;
  Il2CppObject *v24;
  s32 v28;
  s32 v31;
  s32 v32;
  s32 v36;
  s32 v38;
  s32 v39;
  s32 v40;
  s32 v41;
  bool v43;
  s32 v46;
  s32 v47;
  s32 v49;
  void *v51;
  s32 v52;
  u32 v59;
  u64 v63[2];
  System_Collections_Generic_List_Enumerator_T__o v64;

  v3 = pad;
  memset(&v64, 0, sizeof(v64));
  cmpSklCsrMouse(0);
  if ((v3 & 0x10) != 0)
  {
    cmpSklCsrU();
    return;
  }
  if ((v3 & 0x20) != 0)
  {
    cmpSklCsrD();
    return;
  }
  if ((v3 & 0x40) != 0)
  {
    cmpSklCsrL();
    return;
  }
  if (v3 < 0)
  {
    cmpSklCsrR();
    return;
  }
  if (CHECK_TRIG(46594, 1))
  {
    cmpDecModeSq(1);
    BirthDevil = pData->BirthDevil;
    GohRndNativeSkillSet(BirthDevil);
    nativeSkillStep = 1;
    return;
  }
  if ((v3 & 2) != 0)
  {
    SklCsr = cmpGetSklCsr();
    v16 = SklCsr - nativeSkillInit;
    nativeSkillList = pData->BirthDevil->nativeSkillList;
    if (v16 >= 0)
    {
      if (v16 < setNativeSkillList->_size)
      {
        Item = _get_Item(setNativeSkillList, v16);
        if (Item)
        {
          _set_Item(setNativeSkillList, v16, 0);
          --setNativeSkillEndCnt;
          if (Item != LODWORD(_get_Item(nativeSkillList, nativeSkillCsr->csrNo)[1].klass))
          {
            size = nativeSkillList->_size;
            if (size - 1 >= 0)
            {
              while (HIDWORD(_get_Item(nativeSkillList, --size)[1].klass) != 2 || LODWORD(_get_Item(nativeSkillList, size)[1].klass) != Item)
              {
                if (size <= 0)
                  goto LABEL_58;
              }
              HIDWORD(_get_Item(nativeSkillList, size)[1].klass) = 1;
            }
          }
LABEL_58:
          SE(1);
          return;
        }
      }
    }
    v23 = setNativeSkillList;
    v24 = _get_Item(nativeSkillList, nativeSkillCsr->csrNo);
    if (_Contains(v23, (s32)v24[1].klass))
    {
      goto LABEL_63;
    }
    else
    {
      HIDWORD(_get_Item(nativeSkillList, nativeSkillCsr->csrNo)[1].klass) = 1;
LABEL_63:
      cmpDecModeSq(0);
LABEL_64:
      nativeSkillStep = 1;
      return;
    }
    cmpDecModeSq(0);
    goto LABEL_64;
  }
  if ((v3 & 1) != 0)
  {
    v8 = cmpGetSklCsr();
    if (cmpGetRsvCsr() == -1)
    {
      v11 = cmpGetSklCsr();
      if (v11 < nativeSkillInit)
        return;
      v28 = cmpGetSklCsr();
      if (v28 < pData->BirthDevil->nativeSkillSetCnt + nativeSkillInit)
      {
        v31 = v8 - nativeSkillInit;
        v32 = _get_Item(setNativeSkillList, v31);
        if (v32)
        {
          v36 = _get_Item(setNativeSkillList, v31);
          if (v36 != setNativeSkill)
          {
            v38 = _get_Item(setNativeSkillList, v31);
            v39 = _IndexOf(setNativeSkillList, setNativeSkill);
            v40 = v31;
            v41 = v39;
            _set_Item(setNativeSkillList, v40, setNativeSkill);
            if (v41 == -1)
            {
              v51 = pData->BirthDevil->nativeSkillList;
              if (v51->_size >= 1)
              {
                v52 = 0;
                do
                {
                  if (LODWORD(_get_Item(v51, v52)[1].klass) == v38)
                    HIDWORD(_get_Item(pData->BirthDevil->nativeSkillList, v52)[1].klass) = 1;
                  ++v52;
                  v51 = pData->BirthDevil->nativeSkillList;
                }
                while (v52 < v51->_size);
              }
            }
            else
            {
              _set_Item(setNativeSkillList, v41, v38);
            }
          }
        }
        else
        {
          v43 = _Contains(setNativeSkillList, setNativeSkill);
          if (v43)
          {
            v46 = _IndexOf(setNativeSkillList, setNativeSkill);
            if (v46 != -1)
            {
              v47 = v46;
              v49 = _get_Item(setNativeSkillList, v47);
              _set_Item(setNativeSkillList, v47, 0);
              _GetEnumerator(&v64, pData->BirthDevil->nativeSkillList);
              v63[0] = 0;
              v63[1] = &v64;
              while (_MoveNext(&v64))
              {
                if (*(u32 *)((char *)&v64._current->klass + (u64)sub_10) == v49)
                  *(u32 *)((char *)&v64._current->klass + (u64)&locret_14) = 1;
              }
              sub_90D0(v63);
              _set_Item(setNativeSkillList, v31, setNativeSkill);
              HIDWORD(_get_Item(pData->BirthDevil->nativeSkillList, nativeSkillCsr->csrNo)[1].klass) = 2;
            }
          }
          else
          {
            _set_Item(setNativeSkillList, v31, setNativeSkill);
            ++setNativeSkillEndCnt;
            HIDWORD(_get_Item(pData->BirthDevil->nativeSkillList, nativeSkillCsr->csrNo)[1].klass) = 2;
          }
        }
        nativeSkillCsr->seOff = 1;
        CsrAutoDown(nativeSkillCsr, 1);
        nativeSkillCsr->seOff = 0;
        if (pData->BirthDevil->nativeSkillSetCnt == setNativeSkillEndCnt)
        {
          if (!v59)
          cmpDecModeSq(1);
          nativeSkillCsr->endCursorOn = 1;
        }
        else
        {
          if (!v59)
          cmpDecModeSq(1);
        }
        nativeSkillStep = 1;
        SE(0);
      }
      return;
    }
  }
}
