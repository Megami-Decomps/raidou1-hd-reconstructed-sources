#include "types.h"
#include "ITM.h"
#include "achievement.h"
#include "configgame.h"
#include "dat.h"
#include "evtbit.h"
#include "gohrenken.h"
#include "gohswordhistory.h"
#include "sbtlweapon.h"

typedef struct gohData_t gohData_t;
typedef struct gohRenkenNewSwordList_t gohRenkenNewSwordList_t;
typedef struct gohRenkenSelMaterial_t gohRenkenSelMaterial_t;
typedef struct gohRenkenSelSwordList_t gohRenkenSelSwordList_t;
typedef struct sdatPlayerUnitWork_t sdatPlayerUnitWork_t;

// 0x1c0a380
void gohSelSwordList(gohRenkenSelSwordList_t *psSelf) {
  void *v2;
  gohRenkenSelSwordList_t *v3;
  s32 v4;
  void *v5;
  s32 m_iNewSowrdNo;
  void *v8;
  s64 v10;
  s64 v11;
  s32 SwordNo;
  void *v13;
  s8 Type;
  s16 Power;
  char *Name;
  char *SkillName;
  gohRenkenSword_t *m_asSword;
  char *v19;
  gohRenkenSword_t *v20;
  gohRenkenSword_t *v21;
  gohRenkenSword_t *v22;
  void *v23;

  v2 = Allocate(Project_CMRenkenjyutsu);
  _ctor(v2, 0);
  v3 = psSelf;
  if (GetSwordMax(0) >= 2)
  {
    v4 = 1;
    do
    {
      v5 = Allocate(Project_CMSword);
      _ctor_29468336(v5, v4, 0);
      if (GetSwordNum(v5, 0))
        Append(v2, v4, 0);
      ++v4;
    }
    while (v4 < GetSwordMax(0));
  }
  m_iNewSowrdNo = GBWK->SwordHistory->m_iNewSowrdNo;
  v8 = Allocate(Project_CMSword);
  _ctor_29468336(v8, m_iNewSowrdNo, 0);
  if (GetSwordNum(v8, 0))
  {
    Append(v2, GBWK->SwordHistory->m_iNewSowrdNo, 0);
  }
  Sort(v2, 0);
  if (v2->m_iSwordCnt < 1)
  {
    LODWORD(v11) = 0;
  }
  else
  {
    v10 = 0;
    v11 = 0;
    v23 = v2;
    do
    {
      SwordNo = GetSwordNo(v2->m_asSwords[v10]->m_cSword, 0);
      if ((GetSwordNo2ItemNo(SwordNo, 0) & 0xFFFFFFFC) != 0xBC || evtBitCheck(2960))
      {
        v13 = Allocate(Project_CMSword);
        _ctor_29468336(v13, SwordNo, 0);
        Type = GetType(v13, 0);
        Power = GetPower(v13, 0);
        Name = GetName(v13, 0);
        SkillName = GetSkillName(v13, 0);
        m_asSword = v3->m_asSword;
        if (v11 < SLODWORD(m_asSword->max_length))
        {
          v19 = SkillName;
          v20 = m_asSword[v11];
          v20->m_iIdx = v11 + 1;
          v20->m_iSwordNo = SwordNo;
          v20->m_iCnt = GetSwordNum(v13, 0);
          v3 = psSelf;
          v21 = psSelf->m_asSword[v11];
          v21->m_szSwordName = Name;
          v21->m_iType = Type;
          v21->m_iPower = Power;
          v22 = psSelf->m_asSword[v11];
          v22->m_szSkillName = v19;
          ++v11;
        }
        v2 = v23;
      }
      ++v10;
    }
    while (v10 < v2->m_iSwordCnt);
  }
  v3->m_iSwordCnt = v11;
}

// 0x1c0a780
void gohNewSwordList(gohRenkenNewSwordList_t *psSelf, s32 iSwordNo) {
  gohRenkenNewSwordList_t *v5;
  void *v7;
  s32 NewSwordMax;
  s32 v9;
  s64 v10;
  s32 i;
  s32 NewSword;
  void *v13;
  char *Name;
  char *SkillName;
  gohRenkenSword_t *m_asSword;
  s64 v17;
  s64 v18;
  gohRenkenNewSwordList_t *v19;
  gohRenkenSword_t *v20;
  char *v21;
  s32 SwordNum;
  gohRenkenNewSwordList_t *v23;
  gohRenkenSword_t *v24;
  char *v25;
  s64 v26;
  s64 v27;
  s32 v28;
  s16 Power;
  s8 Type;

  v5 = Allocate(gohRenkenNewSwordList_t);
  _ctor(v5);
  psSelf = v5;
  v7 = Allocate(Project_CMSword);
  _ctor_29468336(v7, iSwordNo, 0);
  NewSwordMax = GetNewSwordMax(v7, 0);
  if (NewSwordMax < 1)
  {
    LODWORD(v10) = 0;
  }
  else
  {
    v9 = NewSwordMax;
    v28 = NewSwordMax;
    v10 = 0;
    for (i = 0; i != v9; ++i)
    {
      NewSword = GetNewSword(v7, i, 0);
      if ((GetSwordNo2ItemNo(NewSword, 0) & 0xFFFFFFFC) != 0xBC || evtBitCheck(2960))
      {
        v13 = Allocate(Project_CMSword);
        _ctor_29468336(v13, NewSword, 0);
        Type = GetType(v13, 0);
        Power = GetPower(v13, 0);
        Name = GetName(v13, 0);
        SkillName = GetSkillName(v13, 0);
        m_asSword = psSelf->m_asSword;
        if (v10 < SLODWORD(m_asSword->max_length))
        {
          v17 = v10;
          v18 = v10;
          v19 = psSelf;
          v20 = m_asSword[v18];
          v21 = SkillName;
          v20->m_iIdx = v17 + 1;
          v20->m_iSwordNo = NewSword;
          SwordNum = GetSwordNum(v13, 0);
          v23 = v19;
          v20->m_iCnt = SwordNum;
          psSelf = v19;
          v24 = v23->m_asSword[v18];
          v24->m_szSwordName = Name;
          v24->m_iType = Type;
          v24->m_iPower = Power;
          v25 = (char *)(v19)->m_asSword + v18 * 8;
          v26 = v17;
          v9 = v28;
          v27 = *((u64 *)v25 + 4);
          *(u64 *)(v27 + 40) = v21;
          v10 = v26 + 1;
        }
      }
    }
  }
  psSelf->m_iSwordCnt = v10;
}

// 0x1c0a9d0
void gohSelMaterial(gohRenkenSelMaterial_t *psSelf, s32 iSwordNo) {
  gohRenkenSelMaterial_t *v5;
  void *v7;
  il2cpp_array_size_t max_length;
  s32 v9;
  s64 v10;
  s64 v11;
  s32 ItemNum;
  gohRenkenSelMaterial_t *v13;
  gohRenkenSelMaterialItem_t *v14;
  char *BaseMaterialItemName;
  s64 v16;
  s32 BaseMaterialItemNo;
  gohRenkenSelMaterialItem_t *v18;
  s32 BaseMaterialItemNum;
  gohRenkenSelMaterial_t *v20;
  gohRenkenSelMaterialItem_t *v21;
  s32 BaseSword;
  s32 SwordNo2ItemNo;
  s32 v24;
  gohRenkenSelMaterialItem_t *v25;
  s32 v26;
  gohRenkenSelMaterial_t *v27;
  gohRenkenSelMaterialItem_t *v28;
  char *BaseSwordName;
  gohRenkenSelMaterial_t *v30;
  gohRenkenSelMaterial_t *v31;
  s32 m_iGold;
  f32 v33;
  s32 v34;
  gohRenkenSelMaterial_t *v35;

  v5 = Allocate(gohRenkenSelMaterial_t);
  _ctor(v5);
  psSelf = v5;
  v7 = Allocate(Project_CMSword);
  _ctor_29468336(v7, iSwordNo, 0);
  max_length = psSelf->m_asMatrial->max_length;
  psSelf->m_sNewSword->m_iSwordNo = iSwordNo;
  if ((s32)max_length < 1)
  {
    v9 = 0;
  }
  else
  {
    v9 = 0;
    v10 = 0;
    if ((u32)max_length <= 1u)
      v11 = 1;
    else
      v11 = (u32)max_length;
    do
    {
      if (GetBaseMaterialItemNum(v7, v10, 0))
      {
        v16 = v9;
        BaseMaterialItemNo = GetBaseMaterialItemNo(v7, v10, 0);
        v18 = psSelf->m_asMatrial[v16];
        v18->m_iNo = BaseMaterialItemNo;
        BaseMaterialItemNum = GetBaseMaterialItemNum(v7, v10, 0);
        v20 = psSelf;
        v18->m_iNum = BaseMaterialItemNum;
        v21 = v20->m_asMatrial[v16];
        ItemNum = datGetItemNum(BaseMaterialItemNo);
        v13 = psSelf;
        v21->m_iPossessionNum = ItemNum;
        v14 = v13->m_asMatrial[v9];
        BaseMaterialItemName = GetBaseMaterialItemName(v7, v10, 0);
        v14->m_szName = BaseMaterialItemName;
        ++v9;
      }
      ++v10;
    }
    while (v11 != v10);
  }
  BaseSword = GetBaseSword(v7, 0, 0);
  SwordNo2ItemNo = GetSwordNo2ItemNo(BaseSword, 0);
  if (SwordNo2ItemNo != 144)
  {
    v24 = SwordNo2ItemNo;
    v25 = psSelf->m_asMatrial[v9];
    v25->m_iNo = SwordNo2ItemNo;
    v25->m_iNum = 1;
    v26 = datGetItemNum(v24);
    v27 = psSelf;
    v25->m_iPossessionNum = v26;
    v28 = v27->m_asMatrial[v9];
    BaseSwordName = GetBaseSwordName(v7, BaseSword, 0);
    v28->m_szName = BaseSwordName;
    ++v9;
  }
  v30 = psSelf;
  psSelf->m_iMatrialCnt = v9;
  v30->m_iGold = GetCompositionGold(v7, 0);
  v31 = psSelf;
  m_iGold = psSelf->m_iGold;
  v33 = ConvLevelValue(27, (f32)m_iGold);
  v34 = v33;
  v35 = psSelf;
  if (v33 == INFINITY)
    v34 = 0x80000000;
  v31->m_iGold = v34;
  v35->m_iAuraNo = GetAuraNo(v7, 0);
}

// 0x1c0acc0
bool gohCheckAporion(s32 iNewSwordNo, s32 iBaseSwordNo) {
  GetSwordNo2ItemNo(iNewSwordNo, 0);
  return 1;
}

// 0x1c0ace0
s32 gohCheckComposition(s32 iNewSwordNo, s32 iBaseSwordNo) {
  void *v5;
  void *v6;
  s32 ItemNo;
  s32 v8;
  s32 BaseMaterialItemNo;
  s32 BaseMaterialItemNum;
  s32 v11;
  s32 v12;
  s32 v13;
  s32 v14;
  s32 v15;
  s32 v16;
  s32 v17;
  s32 v18;
  s32 v19;
  s32 v20;
  f32 CompositionGold;
  f32 v22;
  f32 v23;
  s32 v24;

  v5 = Allocate(Project_CMSword);
  _ctor_29468336(v5, iNewSwordNo, 0);
  v6 = Allocate(Project_CMSword);
  _ctor_29468336(v6, iBaseSwordNo, 0);
  ItemNo = GetItemNo(v6, 0);
  v8 = 1;
  if (!datCheckItem(ItemNo, 1))
    return v8;
  BaseMaterialItemNo = GetBaseMaterialItemNo(v5, 0, 0);
  BaseMaterialItemNum = GetBaseMaterialItemNum(v5, 0, 0);
  if (BaseMaterialItemNum)
  {
    v11 = BaseMaterialItemNum;
    if (!datCheckItem(BaseMaterialItemNo, BaseMaterialItemNum))
      return 2;
  }
  v12 = GetBaseMaterialItemNo(v5, 1, 0);
  v13 = GetBaseMaterialItemNum(v5, 1, 0);
  if (v13)
  {
    v14 = v13;
    if (!datCheckItem(v12, v13))
      return 2;
  }
  v15 = GetBaseMaterialItemNo(v5, 2, 0);
  v16 = GetBaseMaterialItemNum(v5, 2, 0);
  if (v16)
  {
    v17 = v16;
    if (!datCheckItem(v15, v16))
      return 2;
  }
  v18 = GetBaseMaterialItemNo(v5, 3, 0);
  v19 = GetBaseMaterialItemNum(v5, 3, 0);
  if (!v19)
    goto LABEL_25;
  v20 = v19;
  if (datCheckItem(v18, v19))
    goto LABEL_25;
  return 2;
LABEL_25:
  CompositionGold = GetCompositionGold(v5, 0);
  v22 = ConvLevelValue(27, CompositionGold);
  if (v22 == INFINITY)
    v23 = -2147500000.0;
  else
    v23 = (s32)v22;
  if (!datCheckMoney((s32)v23))
    return 3;
  v24 = GetItemNo(v5, 0);
  if (datCheckItemFull(v24))
    return 4;
  else
    return 0;
}

// 0x1c0b050
void gohComposition(s32 iNewSwordNo, s32 iBaseSwordNo) {
  void *v5;
  void *v6;
  s32 ItemNo;
  s32 BaseMaterialItemNo;
  s32 BaseMaterialItemNum;
  s32 v10;
  s32 v11;
  s32 v12;
  s32 v13;
  s32 v14;
  s32 v15;
  s32 v16;
  s32 v17;
  s32 v18;
  s32 v19;
  s32 CompositionGold;
  f32 v21;
  s32 v22;

  v5 = Allocate(Project_CMSword);
  _ctor_29468336(v5, iNewSwordNo, 0);
  v6 = Allocate(Project_CMSword);
  _ctor_29468336(v6, iBaseSwordNo, 0);
  ItemNo = GetItemNo(v6, 0);
  datAddItem(ItemNo, -1);
  BaseMaterialItemNo = GetBaseMaterialItemNo(v5, 0, 0);
  BaseMaterialItemNum = GetBaseMaterialItemNum(v5, 0, 0);
  if (BaseMaterialItemNum)
  {
    v10 = BaseMaterialItemNum;
    datAddItem(BaseMaterialItemNo, -v10);
  }
  v11 = GetBaseMaterialItemNo(v5, 1, 0);
  v12 = GetBaseMaterialItemNum(v5, 1, 0);
  if (v12)
  {
    v13 = v12;
    datAddItem(v11, -v13);
  }
  v14 = GetBaseMaterialItemNo(v5, 2, 0);
  v15 = GetBaseMaterialItemNum(v5, 2, 0);
  if (v15)
  {
    v16 = v15;
    datAddItem(v14, -v16);
  }
  v17 = GetBaseMaterialItemNo(v5, 3, 0);
  v18 = GetBaseMaterialItemNum(v5, 3, 0);
  if (v18)
  {
    v19 = v18;
    datAddItem(v17, -v19);
  }
  CompositionGold = GetCompositionGold(v5, 0);
  v21 = ConvLevelValue(27, (f32)CompositionGold);
  v22 = v21;
  if (v21 == INFINITY)
    v22 = 0x80000000;
  datAddMoney(-v22);
}

// 0x1c0b2d0
char *gohGetSwordName(s32 iSwordNo) {
  void *v3;

  v3 = Allocate(Project_CMSword);
  _ctor_29468336(v3, iSwordNo, 0);
  return GetName(v3, 0);
}

// 0x1c0b340
s32 gohGetSwordType(s32 iSwordNo) {
  void *v3;

  v3 = Allocate(Project_CMSword);
  _ctor_29468336(v3, iSwordNo, 0);
  return GetType(v3, 0);
}

// 0x1c0b3b0
s32 gohGetSwordAuraNo(s32 iSwordNo) {
  void *v3;

  v3 = Allocate(Project_CMSword);
  _ctor_29468336(v3, iSwordNo, 0);
  return GetAuraNo(v3, 0);
}

// 0x1c0a730
bool gohCheckSwordFlag(s32 iSwordNo) {
  return (GetSwordNo2ItemNo(iSwordNo, 0) & 0xFFFFFFFC) != 0xBC
      || evtBitCheck(2960);
}

// 0x1c0b420
void gohCreateMaterialDate(gohRenkenSelMaterial_t *_mat, ITM _swordNo) {
  gohSelMaterial(mat, swordNo);
}

// 0x1c0b430
void gohGetSwordSkl(gohData_t *_pData, sdatPlayerUnitWork_t *_player) {
  s32 v6;
  s32 m_hojo;
  s32 v8;

  if (!pData->raidouSkl)
  {
    m_hojo = tbl[pData->m_iSelectNewSwordNo]->m_hojo;
    if (datSpiritSkillGetMaster(player, m_hojo))
      return;
    JUMPOUT(0x19004B0);
  }
  v6 = tbl[pData->m_iSelectNewSwordNo]->m_hojo;
  if (datRaidouSkillGetMaster(player, v6))
    return;
  v8 = tbl[pData->m_iSelectNewSwordNo]->m_hojo;
  datRaidouSkillSetMaster(player, v8, 1);
}

// 0x1c0b700
void gohAchievementUnlock(sdatPlayerUnitWork_t *_player) {
  void *achievementTbl_k__BackingField;
  Project_DefineAchievementID_string__c *klass;
  s64 v8;
  Project_DefineAchievementID_string__c **p_offset;
  s64 v10;
  char *v11;
  _BOOL8 v12;
  void *v16;
  Project_DefineAchievementID_string__c *v17;
  s64 v18;
  s64 v20;
  void *v23;
  Project_DefineAchievementID_string__c *v24;
  s64 v25;
  Project_DefineAchievementID_string__c **v26;
  s64 v27;
  Project_DefineAchievementID_string__c **v28;
  s64 v29;
  char *v30;
  char *v31;

  achievementTbl_k__BackingField = _achievementTbl_k__BackingField;
  klass = achievementTbl_k__BackingField->klass;
  v8 = *(u16 *)&achievementTbl_k__BackingField->klass->_2.rank;
  if (!*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
    goto LABEL_14;
  goto LABEL_11;
  if (!*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
  {
LABEL_14:
    v10 = sub_4227F4(achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0x1Fu);
    goto LABEL_16;
  }
LABEL_11:
  p_offset = &klass->_1.interfaceOffsets->offset;
  while (*(p_offset - 1) != Project_DefineAchievementID_string_)
  {
    p_offset += 2;
    if (!--v8)
      goto LABEL_14;
  }
  v10 = &klass->vtable[*(u32 *)p_offset + 31];
LABEL_16:
  v11 = (*v10)(achievementTbl_k__BackingField, *(u64 *)(v10 + 8));
  Unlock_2(v11);
  v12 = evtBitCheck(2122);
  if (v12)
  {
    if (!gohCheckSwordHaveComplete())
      goto LABEL_18;
    goto LABEL_29;
  }
  v20 = *(u64 *)(*((u64 *)*((MethodInfo *)dat + 2).virtualMethodPointer + 60) + 56);
  *(u32 *)(v20 + 296) |= 0x400u;
  if (!gohCheckSwordHaveComplete())
  {
LABEL_18:
    goto LABEL_19;
  }
LABEL_29:
  v23 = _achievementTbl_k__BackingField;
  v24 = v23->klass;
  v25 = *(u16 *)&v23->klass->_2.rank;
  if (!*(u16 *)&v23->klass->_2.rank)
    goto LABEL_49;
  goto LABEL_46;
  if (!*(u16 *)&v23->klass->_2.rank)
  {
LABEL_49:
    v29 = sub_4227F4(v23, Project_DefineAchievementID_string_, 0x23u);
    goto LABEL_53;
  }
LABEL_46:
  v28 = &v24->_1.interfaceOffsets->offset;
  while (*(v28 - 1) != Project_DefineAchievementID_string_)
  {
    v28 += 2;
    if (!--v25)
      goto LABEL_49;
  }
  v29 = (&v24[1]._1.this_arg + *(u32 *)v28);
LABEL_53:
  v31 = (*v29)(v23, *(u64 *)(v29 + 8));
  Unlock_2(v31);
LABEL_19:
  if (!datRaidouSkillIsComplete(player))
    return;
  v16 = _achievementTbl_k__BackingField;
  v17 = v16->klass;
  v18 = *(u16 *)&v16->klass->_2.rank;
  if (!*(u16 *)&v16->klass->_2.rank)
    goto LABEL_40;
  goto LABEL_37;
  if (!*(u16 *)&v16->klass->_2.rank)
  {
LABEL_40:
    v27 = sub_4227F4(v16, Project_DefineAchievementID_string_, 0x24u);
LABEL_51:
    v30 = (*v27)(v16, *(u64 *)(v27 + 8));
    Unlock_2(v30);
    return;
  }
LABEL_37:
  v26 = &v17->_1.interfaceOffsets->offset;
  while (*(v26 - 1) != Project_DefineAchievementID_string_)
  {
    v26 += 2;
    if (!--v18)
      goto LABEL_40;
  }
  v27 = (&v17[1]._1.element_class + 2 * *(u32 *)v26);
  goto LABEL_51;
}
