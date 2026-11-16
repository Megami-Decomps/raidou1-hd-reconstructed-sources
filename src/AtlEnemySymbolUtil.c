#include "types.h"
#include "atlenemysymbolutil.h"
#include "atlfieldtableresource.h"
#include "atlfieldutil.h"
#include "dat.h"
#include "field.h"
#include "fieldEnemySymbol.h"
#include "fld.h"
#include "glb_stat.h"
#include "sbtlencount.h"

typedef struct AtlEnemySymbol AtlEnemySymbol;
typedef struct AtlEnemySymbolChoiceData AtlEnemySymbolChoiceData;
typedef struct AtlEnemySymbolTableData AtlEnemySymbolTableData;
typedef struct ESEncountTbl_EncountPack_t ESEncountTbl_EncountPack_t;
typedef struct ESEncountTbl_t ESEncountTbl_t;
typedef struct datRndEncTbl_t datRndEncTbl_t;

static s32 _CalcMaxLv(s32 encountID, s32 dlcID);

// 0x22e6820
bool IsEnableChapter(ESEncountTbl_t *data) {
  bool *chapters;

  chapters = data->_chapters;
  return chapters[GBWK->GameFileInfo->chapter];
}

// 0x22ed9b0
void mapDraw_KemuriReq_E(const sdfVector3_t *pos) {
  f32 z;
  f32 y;
  f32 x;
  sdfVector3_t v5;

  z = pos->z;
  y = pos->y;
  x = pos->x;
  v5.y = (f32)(y / -100.0) + 0.1;
  v5.z = z / -100.0;
  v5.x = x / -100.0;
  addPlayerFootEffect_Pos(v5, 1.5);
}

// 0x22eda50
void mapDraw_KemuriReq_Big2(const sdfVector3_t *pos) {
  f32 z;
  f32 y;
  f32 x;
  sdfVector3_t v5;

  z = pos->z;
  y = pos->y;
  x = pos->x;
  v5.y = (f32)(y / -100.0) + 0.1;
  v5.z = z / -100.0;
  v5.x = x / -100.0;
  addPlayerFootEffect_Pos(v5, 1.5);
}

// 0x22e68a0
datRndEncTbl_t *GetEncountTableInRndPackData(ESEncountTbl_EncountPack_t *pack) {
  s32 DLCIndex;
  SB_RNDENCPAC *RndEncPac;
  s64 RndEncPackIndex;
  datRndEncTbl_t *result;
  Il2CppClass **v7;
  s64 RndEncTableIndex;
  const char *name;

  DLCIndex = pack->DLCIndex;
  if (DLCIndex < 0)
    return 0;
  RndEncPac = sBtlGetRndEncPac(DLCIndex);
  RndEncPackIndex = pack->RndEncPackIndex;
  result = 0;
  if ((s32)RndEncPackIndex < SLODWORD(RndEncPac->max_length))
  {
    v7 = &RndEncPac->obj.klass + RndEncPackIndex;
    RndEncTableIndex = pack->RndEncTableIndex;
    name = v7[4]->_1.name;
    if ((s32)RndEncTableIndex < *((u32 *)name + 6))
      return *(datRndEncTbl_t *)&name[8 * RndEncTableIndex + 32];
    return 0;
  }
  return result;
}

// 0x22eb6d0
AtlEnemySymbolChoiceData ChoiceEncount(AtlEnemySymbolTableData *data, bool isAlreadyDestroy) {
  AtlEnemySymbolTableData *v6;
  AtlEnemySymbolChoiceData *result;
  AtlEnemySymbolTableData *v8;
  EncountPack *m_EncountPacks;
  s64 v10;
  s32 v11;
  EncountPack *v12;
  ESEncountTbl_EncountPack_t *m_Pack;
  s32 v14;
  s32 DLCIndex;
  SB_ENCOUNTPAC *EncountPac;
  bool IsNullOrEmpty;
  s64 m_EncountDevilIDIndex;
  s32 v20;
  s32 v21;
  AtlEnemySymbolTableData *v22;
  ESEncountTbl_t *m_Body;
  f32 x;
  f32 z;
  s32 v26;
  s32 v27;
  s32 rndEncPacID;
  s32 v29;
  s32 v30;
  s32 RndEncPackIndex;
  s32 RndEncTableIndex;
  AtlEnemySymbolChoiceData *v33;
  s32 v34;
  SB_ENCOUNTPAC *v35;
  s64 m_DLCIndex_low;
  bool v37;
  s32 v38;
  s32 v39;
  s32 v40;
  __int128 v41;
  __int128 v42;
  s32 encountIndex;
  u8 target[48];
  System_ValueTuple_int__int__o v46;

  v6 = data;
  encountIndex = 0;
  *(u64 *)target = v6;
  memset(&target[8], 0, 40);
  v8 = data;
  m_EncountPacks = data->m_EncountPacks;
  if (SLODWORD(m_EncountPacks->max_length) >= 1)
  {
    v10 = 0;
    v11 = -1;
    while (1)
    {
      v12 = m_EncountPacks[v10];
      if (!v12->m_IsEnable)
        goto LABEL_7;
      m_Pack = v12->m_Pack;
      if (isAlreadyDestroy)
        break;
      if (m_Pack->_encountID)
      {
        *(u32 *)&target[20] = v11;
        DLCIndex = m_Pack->DLCIndex;
LABEL_13:
        EncountPac = sBtlGetEncountPac(DLCIndex);
        IsNullOrEmpty = IsNullOrEmpty(EncountPac[m_Pack->_encountID]->end_scrip, 0);
        m_EncountDevilIDIndex = v12->m_EncountDevilIDIndex;
        target[36] = data->m_Body->_is_ignoreInstantDeath || !IsNullOrEmpty;
        v20 = m_Pack->DLCIndex;
        *(u32 *)&target[12] = m_Pack->_encountID;
        v21 = v12->m_PackDevilIDs[m_EncountDevilIDIndex];
        *(u32 *)&target[16] = v20;
        *(u32 *)&target[20] = v21;
        v46 = CalcBattleMapID(v12, 0, 0, 0);
        v22 = data;
        *(void *)&target[28] = v46;
        m_Body = v22->m_Body;
        x = m_Body->Pos.x;
        z = m_Body->Pos.z;
        *(u32 *)&target[24] = mapGetRndEnc(x, z);
        v26 = *(u32 *)&target[12];
        v27 = *(u32 *)&target[16];
LABEL_17:
        result = (AtlEnemySymbolChoiceData *)sBtlGetEncountDevilMaxLv(v26, v27);
        *(u32 *)&target[40] = (u32)result;
        goto LABEL_20;
      }
      rndEncPacID = m_Pack->_rndEncPacID;
      *(u32 *)&target[20] = v11;
      if (rndEncPacID)
        goto LABEL_26;
      *(u32 *)&target[8] = v10;
LABEL_6:
      v8 = data;
LABEL_7:
      m_EncountPacks = v8->m_EncountPacks;
      if (++v10 >= SLODWORD(m_EncountPacks->max_length))
        goto LABEL_33;
    }
    v14 = m_Pack->_rndEncPacID;
    *(u32 *)&target[20] = v11;
    if (v14)
    {
LABEL_26:
      v29 = v11;
      encountIndex = 0;
      v30 = m_Pack->DLCIndex;
      RndEncPackIndex = m_Pack->RndEncPackIndex;
      RndEncTableIndex = m_Pack->RndEncTableIndex;
      result = (AtlEnemySymbolChoiceData *)sBtlRndEncCalc_Symbol2(v30, RndEncPackIndex, RndEncTableIndex, &encountIndex);
      v11 = v29;
      if (!result)
        goto LABEL_33;
      v33 = result;
      v34 = m_Pack->DLCIndex;
      v35 = sBtlGetEncountPac(v34);
      m_DLCIndex_low = LOWORD(v33->m_DLCIndex);
      *(u32 *)&target[12] = LOWORD(v33->m_DLCIndex);
      v37 = IsNullOrEmpty(v35[m_DLCIndex_low]->end_scrip, 0);
      v39 = m_Pack->DLCIndex;
      v38 = m_Pack->RndEncPackIndex;
      target[36] = data->m_Body->_is_ignoreInstantDeath || !v37;
      v40 = v12->m_PackDevilIDs[encountIndex];
      *(u32 *)&target[16] = v39;
      *(u32 *)&target[20] = v40;
      *(u32 *)&target[24] = v38;
      *(void *)&target[28] = CalcBattleMapID(v12, 1, encountIndex, 0);
      v26 = *(u32 *)&target[12];
      v27 = *(u32 *)&target[16];
      goto LABEL_17;
    }
    if (m_Pack->_encountID)
    {
      DLCIndex = m_Pack->DLCIndex;
      goto LABEL_13;
    }
LABEL_20:
    *(u32 *)&target[8] = v10;
    if (*(u32 *)&target[20] != -1)
      goto LABEL_33;
    goto LABEL_6;
  }
LABEL_33:
  v41 = *(_OWORD *)target;
  v42 = *(_OWORD *)&target[16];
  *(_OWORD *)&retstr->m_BattleAreaID = *(_OWORD *)&target[32];
  *(_OWORD *)&retstr->m_Table = v41;
  *(_OWORD *)&retstr->m_DLCIndex = v42;
  return result;
}

// 0x22edaf0
static s32 _CalcMaxLv(s32 encountID, s32 dlcID) {
  return sBtlGetEncountDevilMaxLv(encountID, dlcID);
}

// 0x22edb60
bool IsEnableEncountPack(ESEncountTbl_EncountPack_t *pack) {
  s32 flag1;
  s32 flag1j;
  s32 flag2;
  s32 flag2j;

  if (!pack->_rndEncPacID && !pack->_encountID)
    return 0;
  flag1 = pack->_flag1;
  flag1j = pack->_flag1j;
  if (!IsOnEventFlag(flag1, flag1j))
    return 0;
  flag2 = pack->_flag2;
  flag2j = pack->_flag2j;
  return IsOnEventFlag(flag2, flag2j);
}

// 0x22e6960
s32 ConvEncountIDToEnemyID(s32 dlcID, s32 encountID) {
  SB_ENCOUNTPAC *EncountPac;

  if ((encountID & 0x80000000) == 0)
  {
    EncountPac = sBtlGetEncountPac(dlcID);
    if (SLODWORD(EncountPac->max_length) > encountID)
      return EncountPac[encountID]->devil_visible_id;
  }
  return 0;
}

// 0x22e5b50
eEnemySymbolPopSkillStatus CalcCurrentPopSkillStatus(void) {
  u32 stat;
  u32 v7;

  if (!GBWK)
    return 0;
  stat = GBWK->stat;
  if ((ESUTOMA_CHK() & stat) != 0)
    return 2;
  v7 = GBWK->stat;
  return (RIBERAMA_CHK() & v7) != 0;
}

// 0x22edc40
sdfVector3_t CalcOtherEnemyClosestPoint(AtlEnemySymbol *checkSymbol, sdfVector3_t *pos) {
  s64 v5;
  s64 v6;
  void *v7;
  bool v8;
  bool v9;
  AtlEnemySymbolChara *m_Chara;
  void *m_BaseCollision;
  void *Enemies;
  u32 i;
  System_Collections_Generic_IReadOnlyList_AtlEnemySymbol__c *klass;
  s64 v15;
  s32 *p_offset;
  s64 v17;
  s64 v18;
  System_Collections_Generic_IReadOnlyList_AtlEnemySymbol__c *v19;
  s64 v20;
  s32 *v21;
  s64 v22;
  s64 v23;
  System_Collections_Generic_IReadOnlyList_AtlEnemySymbol__c *v24;
  s64 v25;
  s32 *v26;
  s64 v27;
  s64 v28;
  s64 v29;
  s64 v30;
  void *v31;
  sdfQuaternion_t Rotate;
  sdfVector3_t Scale;
  sdfVector3_t Position;
  sdfVector3_t nextPos;
  sdfVector3_t result;

  nextPos = *pos;
  v5 = *((u64 *)Method_AtlUtil_AtSingleton_AtlEnemySymbolManager__get_Instance__ + 4);
  if ((*(u8 *)(v5 + 309) & 1) != 0)
  {
    v6 = *(u64 *)(*(u64 *)(v5 + 192) + 16);
    if ((*(u16 *)(v6 + 309) & 1) != 0)
      goto LABEL_5;
LABEL_12:
    v7 = **(void ***)(sub_42269C(v6) + 184);
    if (v7)
      v9 = checkSymbol == 0;
    else
      v9 = 1;
    if (v9)
      goto LABEL_45;
    goto LABEL_16;
  }
  v6 = *(u64 *)(*(u64 *)(sub_42269C(v5) + 192) + 16);
  if ((*(u16 *)(v6 + 309) & 1) == 0)
    goto LABEL_12;
LABEL_5:
  v7 = **(void ***)(v6 + 184);
  if (v7)
    v8 = checkSymbol == 0;
  else
    v8 = 1;
  if (v8)
    goto LABEL_45;
LABEL_16:
  m_Chara = checkSymbol->m_Chara;
  if (m_Chara)
  {
    m_BaseCollision = m_Chara->m_BaseCollision;
    if (m_BaseCollision)
    {
      Position = get_Position(m_Chara->m_BaseCollision, 0);
      Scale = get_Scale(m_BaseCollision, 0);
      Rotate = get_Rotate(m_BaseCollision, 0);
      (m_BaseCollision->klass->vtable._9_SetLocalTRS.methodPtr)(m_BaseCollision, pos, &Scale, &Rotate, m_BaseCollision->klass->vtable._9_SetLocalTRS.method);
      Enemies = GetEnemies(v7, 0);
      for (i = 0; ; ++i)
      {
        klass = Enemies->klass;
        v15 = *(u16 *)&Enemies->klass->_2.rank;
        if (*(u16 *)&Enemies->klass->_2.rank)
        {
          p_offset = &klass->_1.interfaceOffsets->offset;
          while (*((System_Collections_Generic_IReadOnlyCollection_AtlEnemySymbol__c **)p_offset - 1) != System_Collections_Generic_IReadOnlyCollection_AtlEnemySymbol_)
          {
            p_offset += 4;
            if (!--v15)
              goto LABEL_24;
          }
          v18 = &klass->vtable[*p_offset];
          if ((s32)i >= (*v18)(Enemies, *(u64 *)(v18 + 8)))
          {
LABEL_44:
            Scale = get_Scale(m_BaseCollision, 0);
            Rotate = get_Rotate(m_BaseCollision, 0);
            (m_BaseCollision->klass->vtable._9_SetLocalTRS.methodPtr)(m_BaseCollision, &Position, &Scale, &Rotate, m_BaseCollision->klass->vtable._9_SetLocalTRS.method);
            break;
          }
        }
        else
        {
LABEL_24:
          v17 = sub_4227F4(Enemies, System_Collections_Generic_IReadOnlyCollection_AtlEnemySymbol_, 0);
          if ((s32)i >= (*v17)(Enemies, *(u64 *)(v17 + 8)))
            goto LABEL_44;
        }
        v19 = Enemies->klass;
        v20 = *(u16 *)&Enemies->klass->_2.rank;
        if (*(u16 *)&Enemies->klass->_2.rank)
        {
          v21 = &v19->_1.interfaceOffsets->offset;
          while (*((System_Collections_Generic_IReadOnlyList_AtlEnemySymbol__c **)v21 - 1) != System_Collections_Generic_IReadOnlyList_AtlEnemySymbol_)
          {
            v21 += 4;
            if (!--v20)
              goto LABEL_31;
          }
          v23 = &v19->vtable[*v21];
          if ((*v23)(Enemies, i, *(u64 *)(v23 + 8)) == checkSymbol)
            continue;
        }
        else
        {
LABEL_31:
          v22 = sub_4227F4(Enemies, System_Collections_Generic_IReadOnlyList_AtlEnemySymbol_, 0);
          if ((*v22)(Enemies, i, *(u64 *)(v22 + 8)) == checkSymbol)
            continue;
        }
        v24 = Enemies->klass;
        v25 = *(u16 *)&Enemies->klass->_2.rank;
        if (*(u16 *)&Enemies->klass->_2.rank)
        {
          v26 = &v24->_1.interfaceOffsets->offset;
          while (*((System_Collections_Generic_IReadOnlyList_AtlEnemySymbol__c **)v26 - 1) != System_Collections_Generic_IReadOnlyList_AtlEnemySymbol_)
          {
            v26 += 4;
            if (!--v25)
              goto LABEL_38;
          }
          v29 = &v24->vtable[*v26];
          v28 = (*v29)(Enemies, i, *(u64 *)(v29 + 8));
          if (!v28)
            continue;
        }
        else
        {
LABEL_38:
          v27 = sub_4227F4(Enemies, System_Collections_Generic_IReadOnlyList_AtlEnemySymbol_, 0);
          v28 = (*v27)(Enemies, i, *(u64 *)(v27 + 8));
          if (!v28)
            continue;
        }
        v30 = *(u64 *)(v28 + 104);
        if (v30)
        {
          v31 = *(void *)(v30 + 96);
          if (v31)
          {
            if (CalcClosestPoint_30831328(v31, m_BaseCollision, &nextPos, 0))
            {
              goto LABEL_44;
            }
          }
        }
      }
    }
  }
LABEL_45:
  result.y = nextPos.y;
  result.z = nextPos.z;
  result.x = nextPos.x;
  return result;
}

// 0x22ed330
eType CalcTargetRingType(AtlEnemySymbol *symbol) {
  const MethodInfo_3083B10 *v2;
  const MethodInfo_3083AB0 *v3;
  __int128 v5;
  __int128 v6;
  __int128 v7;
  s32 m_MaxLv;
  sdatPlayerUnitWork_t *player;
  sdatUnitWork_t *para;
  s32 v12;
  AtlEnemySymbolChoiceData v15;
  __int128 v16;
  __int128 v17;
  __int128 v18;
  s64 v19;
  __int128 v20;
  __int128 v21;
  __int128 v22;
  s64 v23;
  System_Nullable_T__o v24;
  System_Nullable_T__o v25;

  if (symbol)
  {
    *(u64 *)&v24.hasValue = &v20;
    v5 = *(_OWORD *)&symbol->m_TableParam.m_Table;
    v24.value = &v16;
    v23 = 0;
    v6 = *(_OWORD *)&symbol->m_TableParam.m_DLCIndex;
    v16 = v5;
    v17 = v6;
    v7 = *(_OWORD *)&symbol->m_TableParam.m_BattleAreaID;
    v20 = 0u;
    v21 = 0u;
    v22 = 0u;
    v18 = v7;
    __ctor(v24, Method_System_Nullable_AtlEnemySymbolChoiceData___ctor__, v3);
    v16 = v20;
    v17 = v21;
    v19 = v23;
    v18 = v22;
  }
  else
  {
    v19 = 0;
    v17 = 0u;
    v18 = 0u;
    v16 = 0u;
  }
  v20 = v16;
  v21 = v17;
  v23 = v19;
  v22 = v18;
  if (!(u8)v16)
    return 4;
  *(u64 *)&v25.hasValue = &v20;
  v25.value = Method_System_Nullable_AtlEnemySymbolChoiceData__get_Value__;
  _get_Value(&v15, v25, v2);
  m_MaxLv = v15.m_MaxLv;
  if (!GBWK)
    return 4;
  player = GBWK->player;
  if (!player)
    return 4;
  para = player->para;
  if (!para)
    return 4;
  v12 = para->level - m_MaxLv;
  if (GetConst(fldESConstTbl, 24, 0) <= (f32)v12)
    return symbol->m_TableParam.m_IsIgnoreInstantDeath;
  if ((v12 & 0x80000000) == 0)
    return 1;
  if (GetConst(fldESConstTbl, 25, 0) <= (f32)-v12)
    return 2;
  else
    return 1;
}

// 0x22e9310
bool IsInstantDeath(AtlEnemySymbol *symbol) {
  if (CalcTargetRingType(symbol))
    return 0;
  if (IsChasePlayer(symbol, 0))
    return 0;
  return !symbol->m_TableParam.m_IsIgnoreInstantDeath;
}
