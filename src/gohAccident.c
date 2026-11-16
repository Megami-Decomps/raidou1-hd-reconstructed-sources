#include "types.h"
#include "gohAccidentKN.h"
#include "gohAccidentLR.h"
#include "gohaccident.h"

typedef struct CMAccident CMAccident;

CMAccident *s_pcInst;

// 0x1b8b380
void gohCreateInstance(void) {
  CMAccident *v1;

  v1 = Allocate(CMAccident);
  _ctor(v1, 0);
  s_pcInst = v1;
}

// 0x1b8b410
void gohDestroyInstance(void) {
  if (s_pcInst)
  {
    Dispose(s_pcInst, 0);
    s_pcInst = 0;
  }
}

// 0x1b8b490
void gohClear(void) {
  if (s_pcInst)
    Clear(s_pcInst);
}

// 0x1b8b4f0
void gohSetForceAccident(gohAccidentTN eNo) {
  if (s_pcInst)
    s_pcInst->m_eForceAccident = eNo;
}

// 0x1b8b550
void gohSetCombineCnt(s32 iCnt) {
  if (s_pcInst)
    s_pcInst->m_iCombineCnt = iCnt;
}

// 0x1b8b5b0
void gohSetMoonAge(s32 iMoonAge) {
  if (s_pcInst)
    SetMoonAge(s_pcInst, iMoonAge, 0);
}

// 0x1b8b630
void gohSetMoonAge16(s32 iMoonAge) {
  if (s_pcInst)
    SetMoonAge16(s_pcInst, iMoonAge, 0);
}

// 0x1b8b6b0
void gohSetHeroLevel(s32 iLevel) {
  if (s_pcInst)
    SetHeroLevel(s_pcInst, iLevel, 0);
}

// 0x1b8b730
void gohSetLuckRank(gohAccidentLR eRank) {
  if (s_pcInst)
    s_pcInst->m_eLuckRank = eRank;
}

// 0x1b8b790
s32 gohRequestItemCnt(void) {
  if (s_pcInst)
    return s_pcInst->m_iReqItemCnt;
  else
    return 0;
}

// 0x1b8b800
s32 gohRequestItemNo(void) {
  if (s_pcInst)
    LODWORD(s_pcInst) = RequestLastItemNo(s_pcInst, 0);
  return (s32)s_pcInst;
}

// 0x1b8b860
bool gohPresentItem(bool bGetItem) {
  if (s_pcInst)
    LOBYTE(s_pcInst) = PresentItem(s_pcInst, bGetItem, 0);
  return (char)s_pcInst;
}

// 0x1b8b8e0
gohAccidentKN gohGetKindNo(void) {
  if (s_pcInst)
    return s_pcInst->m_eKind;
  else
    return 0;
}

// 0x1b8b950
bool gohDecide(void) {
  bool result;

  result = false;
  if (s_pcInst)
  {
    Decide(s_pcInst, 0);
    if (s_pcInst->m_iTypeCnt)
      return true;
  }
  return result;
}

// 0x1b8b9d0
s32 gohGetTypeCnt(void) {
  if (s_pcInst)
    return s_pcInst->m_iTypeCnt;
  else
    return 0;
}

// 0x1b8ba40
bool gohGetEndFlag(void) {
  return s_pcInst && s_pcInst->m_setEnd;
}

// 0x1b8bab0
gohAccidentTN gohGetTypeNo(s32 idx) {
  if (s_pcInst && s_pcInst->m_iTypeCnt > idx)
    return s_pcInst->m_aeType[idx];
  else
    return 0;
}

// 0x1b8bb40
s32 gohGetTypeVal(s32 iNo) {
  if (!s_pcInst)
    return 0;
  if (iNo == 2)
    return s_pcInst->m_iTypeValSkill;
  if (iNo != 1)
  {
    if (!iNo)
      return s_pcInst->m_iTypeValParam;
    return 0;
  }
  return s_pcInst->m_iTypeValValue;
}

// 0x1b8bbf0
s32 gohGetCreateDevilNo(void) {
  if (s_pcInst)
    return s_pcInst->m_iCreateDevilNo;
  else
    return 0;
}

// 0x1b8bc60
void gohDebugMajinDead(void) {
  if (s_pcInst)
    DebugMajinDead(s_pcInst, 0);
}
