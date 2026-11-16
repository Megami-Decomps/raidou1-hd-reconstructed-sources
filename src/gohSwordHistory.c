#include "types.h"
#include "achievement.h"
#include "dat.h"
#include "gohswordhistory.h"

typedef enum {
    c_gohSword_Max = 100,
} c_gohSword;

typedef struct gohSwordHistory_t gohSwordHistory_t;

// 0x1c0be00
void Clear(void) {
  gohSwordHistory_t *SwordHistory;
  u8 *v5;
  u8 *v6;

  SwordHistory = GBWK->SwordHistory;
  SwordHistory->m_iRegistNums = 0;
  v5 = NewSpecific(byte, 0x18u);
  SwordHistory->m_iaBits = v5;
  v6 = NewSpecific(byte, 0x18u);
  SwordHistory->m_haveBits = v6;
  SwordHistory = ((char *)SwordHistory + 32);
  HIDWORD(SwordHistory[-1].m_iaBits) = 1;
}

// 0x1c0bf90
void gohOnSword(s32 iSwordNo) {
  u64 v4;

  if ((u32)iSwordNo <= 0x63)
  {
    v4 = (u64)GBWK->SwordHistory->m_iaBits
       + ((u64)(u32)iSwordNo >> 3);
    *(u8 *)(v4 + 32) |= 1 << (iSwordNo & 7);
  }
}

// 0x1c0c040
void gohOnSwordHave(s32 iSwordNo) {
  u64 v4;

  if ((u32)iSwordNo <= 0x63)
  {
    v4 = (u64)GBWK->SwordHistory->m_haveBits
       + ((u64)(u32)iSwordNo >> 3);
    *(u8 *)(v4 + 32) |= 1 << (iSwordNo & 7);
  }
}

// 0x1c0c0e0
bool gohCheckSword(s32 iSwordNo) {
  _BOOL4 v4;

  if ((u32)iSwordNo > 0x63)
  {
    LOBYTE(v4) = 0;
  }
  else
  {
    return (GBWK->SwordHistory->m_iaBits[(u32)iSwordNo >> 3] >> (iSwordNo & 7))
         & 1;
  }
  return v4;
}

// 0x1c0c180
bool gohCheckSwordHave(s32 iSwordNo) {
  _BOOL4 v4;

  if ((u32)iSwordNo > 0x63)
  {
    LOBYTE(v4) = 0;
  }
  else
  {
    return (GBWK->SwordHistory->m_haveBits[(u32)iSwordNo >> 3] >> (iSwordNo & 7))
         & 1;
  }
  return v4;
}

// 0x1c0bb00
bool gohCheckSwordHaveComplete(void) {
  char v1;
  s32 v2;
  u32 i;
  s64 v5;
  char v6;
  void *achievementTbl_k__BackingField;
  Project_DefineAchievementID_string__c *klass;
  s64 v11;
  Project_DefineAchievementID_string__c **p_offset;
  s64 v13;
  char *v14;

  v1 = byte_5757286;
  v2 = 0;
  for (i = 0; i != 100; ++i)
  {
    v1 = 1;
    v5 = i >> 3;
    v6 = i & 7;
    v2 += (GBWK->SwordHistory->m_haveBits[v5] >> v6) & 1;
  }
  achievementTbl_k__BackingField = _achievementTbl_k__BackingField;
  klass = achievementTbl_k__BackingField->klass;
  v11 = *(u16 *)&achievementTbl_k__BackingField->klass->_2.rank;
  if (!*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
    goto LABEL_21;
  goto LABEL_18;
  if (!*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
  {
LABEL_21:
    v13 = sub_4227F4(achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0x23u);
    goto LABEL_23;
  }
LABEL_18:
  p_offset = &klass->_1.interfaceOffsets->offset;
  while (*(p_offset - 1) != Project_DefineAchievementID_string_)
  {
    p_offset += 2;
    if (!--v11)
      goto LABEL_21;
  }
  v13 = (&klass[1]._1.this_arg + *(u32 *)p_offset);
LABEL_23:
  v14 = (*v13)(achievementTbl_k__BackingField, *(u64 *)(v13 + 8));
  ProgressUnlock_3(v14, v2, 46);
  return v2 > 45;
}

// 0x1c0c220
void gohAppendSword(s32 iSwordNo, bool bFlag) {
  gohSwordHistory_t *SwordHistory;
  u64 v7;
  s32 v8;
  char *v9;
  char *v11;
  void *v12;
  s32 ItemNo;

  SwordHistory = GBWK->SwordHistory;
  if ((u32)iSwordNo > 0x63)
  {
    if (!bFlag)
      return;
    goto LABEL_19;
  }
  v7 = (u64)(u32)iSwordNo >> 3;
  v8 = 1 << (iSwordNo & 7);
  v9 = (char *)GBWK->SwordHistory->m_iaBits + v7;
  v9[32] |= v8;
  v11 = (char *)GBWK->SwordHistory->m_haveBits + v7;
  v11[32] |= v8;
  if (bFlag)
  {
LABEL_19:
    v12 = Allocate(Project_CMSword);
    _ctor_29468336(v12, iSwordNo, 0);
    ItemNo = GetItemNo(v12, 0);
    datAddItem(ItemNo, 1);
    SwordHistory->m_iNewSowrdNo = iSwordNo;
  }
}

// 0x1c0a6c0
s32 gohGetNewSword(void) {
  return GBWK->SwordHistory->m_iNewSowrdNo;
}

// 0x1c0bf00
gohSwordHistory_t *GetSelf(void) {
  return GBWK->SwordHistory;
}

// 0x1c0c030
bool gohIsSwordNo(s32 iSwordNo) {
  return (u32)iSwordNo < 0x64;
}
