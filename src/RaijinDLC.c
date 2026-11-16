#include "types.h"
#include "ITM.h"
#include "dat.h"
#include "raijindlc.h"

#define NAME_EXP "new_exp"
#define NAME_ONI "new_oni"
#define NAME_DEVIL "new_devil"
#define NAME_TITLE "new_title"
#define NAME_DBOOK "new_dbook"
#define NAME_GLASSES "new_glasses"
#define NAME_SKILL "new_skill"
#define NAME_ITEM "new_item"
#define NAME_CRM "new_crm"
#define DLC_ITEMPAC_MAX 3
#define STORE_SKILL_ID ""
#define STORE_ITEM_ID ""
#define STORE_CRM_ID ""
#define D_K_BITS_SIZE 2

typedef struct DlcItem DlcItem;
typedef struct ITEMLIST ITEMLIST;

struct ITEMLIST {
    ITM item_no;
    s32 count;
};

struct DlcItem {
    ITM item;
    char *dlcName;
};

static ITEMLIST *dlcItem_List[3];
static void *dlcItemTbl;

static bool ItemDLC_Exists(s32 pack_no);
static s32 GetIndexPack(s32 pack_no);
static s32 GetIndexItem(s32 pack_no, s32 itmidx);
static s32 GetDvlKarteFCheckID(s32 _devilID);

// 0x194b050
bool Exists(char *name) {
  return Exists_36017472(_Dlc_k__BackingField, name, 0);
}

// 0x194b120
void DLC_ItemInit(void) {
  s64 v2;
  s32 v3;
  ITEMLIST *v7;
  s64 v8;
  s32 v9;
  ITEMLIST *v10;
  s64 m_Items;
  s32 v12;

  v2 = 0;
  v3 = 18;
  do
  {
    if (!ItemDLC_Exists(v2))
      goto LABEL_5;
    if (!GBWK->buy_item[128 * v2])
    {
      v7 = dlcItem_List[v2];
      if (SLODWORD(v7->max_length) > 0)
      {
        v8 = 0;
        v9 = v3;
        while (1)
        {
          v10 = v7[v8++];
          m_Items = GBWK->buy_item;
          *(u32 *)(m_Items + 4 * (v9 - 2)) = v10->item_no;
          v12 = v9 - 1;
          LODWORD(v10) = v10->count;
          *(u32 *)(m_Items + 4 * v9) = v2;
          v9 += 4;
          *(u32 *)(m_Items + 4 * v12) = (u32)v10;
          if (v8 >= SLODWORD(v7->max_length))
            goto LABEL_26;
        }
      }
LABEL_26:
      GBWK->buy_item[128 * v2] = 1;
    }
LABEL_5:
    ++v2;
    v3 += 128;
  }
  while (v2 != 3);
}

// 0x194b320
static bool ItemDLC_Exists(s32 pack_no) {
  char *v3;
  char *v6;
  char *v9;

  if (pack_no == 2)
  {
    v6 = "new_crm";
    return Exists_36017472(_Dlc_k__BackingField, v6, 0);
  }
  if (pack_no == 1)
  {
    v9 = "new_item";
    return Exists_36017472(_Dlc_k__BackingField, v9, 0);
  }
  if (pack_no)
    return 0;
  v3 = "new_skill";
  return Exists_36017472(_Dlc_k__BackingField, v3, 0);
}

// 0x194b6e0
static s32 GetIndexPack(s32 pack_no) {
  return pack_no << 7;
}

// 0x194b6f0
static s32 GetIndexItem(s32 pack_no, s32 itmidx) {
  return (pack_no << 7) + 4 * itmidx + 16;
}

// 0x194b700
s32 GetPackItemMax(s32 pack_no) {
  return dlcItem_List[pack_no]->max_length;
}

// 0x194b780
s32 GetPackItemNo(s32 pack_no, s32 index) {
  return GBWK->buy_item[128 * pack_no + 16 + 4 * index];
}

// 0x194b850
s32 GetPackItemCnt(s32 pack_no, s32 index) {
  s32 v7;

  if (ItemDLC_Exists(pack_no))
  {
    v7 = (pack_no << 7) + 4 * index + 16;
    return *(s32 *)((char *)GBWK->buy_item + ((4 * v7) | 4));
  }
  return 0;
}

// 0x194b970
s32 GetPackItemPackNo(s32 pack_no, s32 index) {
  return GBWK->buy_item[128 * pack_no + 18 + 4 * index];
}

// 0x194ba40
void DelBuyItem(s32 pack_no, ITM item_no, s32 del_val) {
  s64 v7;
  s64 v8;
  s32 i;
  s32 *buy_item;
  char *v13;
  s32 v14;

  v7 = 0;
  v8 = pack_no;
  for (i = (pack_no << 7) | 0x11; ; i += 4)
  {
    if (v7 >= SLODWORD(dlcItem_List[v8]->max_length))
      break;
    buy_item = GBWK->buy_item;
    if (buy_item[i - 1] != item_no)
      goto LABEL_5;
    v13 = (char *)buy_item + 4 * i;
    v14 = *((u32 *)v13 + 8) - del_val;
    *((u32 *)v13 + 8) = v14;
    if (v14 >= 0)
      goto LABEL_5;
    buy_item = GBWK->buy_item;
    buy_item[i] = 0;
LABEL_5:
    ++v7;
  }
}

// 0x194bc20
bool IsBuyItem(void) {
  s64 v4;
  s32 v5;
  s64 v6;
  s32 v7;
  bool v9;
  il2cpp_array_size_t max_length;
  il2cpp_array_size_t v16;
  s64 v17;
  s64 v18;
  s32 v22;
  s64 v23;
  s64 v24;
  s32 v28;

  if ((s32)dlcItem_List[0]->max_length >= 1)
  {
    v4 = 0;
    v5 = 0;
    v6 = 4 * (u32)dlcItem_List[0]->max_length;
    while (1)
    {
      v9 = ItemDLC_Exists(0);
      v7 = 0;
      if (v9)
        v7 = GBWK->buy_item[(s32)v4 + 17];
      v4 += 4;
      v5 += v7;
      if (v6 == v4)
      {
        goto LABEL_24;
      }
    }
  }
  v5 = 0;
LABEL_24:
  goto LABEL_26;
  if ((s32)max_length < 1)
  {
LABEL_27:
LABEL_28:
    goto LABEL_30;
  }
  goto LABEL_38;
LABEL_26:
  max_length = dlcItem_List[1]->max_length;
  if ((s32)max_length < 1)
    goto LABEL_27;
LABEL_38:
  v17 = 0;
  v18 = 4 * (u32)max_length;
  do
  {
    {
LABEL_42:
      goto LABEL_43;
LABEL_39:
      v17 += 4;
      if (v18 == v17)
        goto LABEL_54;
    }
    goto LABEL_42;
LABEL_43:
    if (!ItemDLC_Exists(1))
      goto LABEL_39;
    v22 = GBWK->buy_item[(s32)v17 + 145];
    v17 += 4;
    v5 += v22;
  }
  while (v18 != v17);
LABEL_54:
  goto LABEL_28;
LABEL_58:
  v23 = 0;
  v24 = 4 * (u32)v16;
  while (2)
  {
    while (2)
    {
      goto LABEL_62;
LABEL_63:
      if (!ItemDLC_Exists(2))
        goto LABEL_59;
      goto LABEL_9003;
LABEL_62:
      goto LABEL_63;
      if (!ItemDLC_Exists(2))
      {
LABEL_59:
        v23 += 4;
        if (v24 == v23)
          return v5 != 0;
        continue;
      }
LABEL_9003:
      break;
    }
    v28 = GBWK->buy_item[(s32)v23 + 273];
    v23 += 4;
    v5 += v28;
    if (v24 == v23)
      return v5 != 0;
    continue;
  }
LABEL_30:
  v16 = dlcItem_List[2]->max_length;
  if ((s32)v16 >= 1)
    goto LABEL_58;
  return v5 != 0;
}

// 0x194c110
bool IsRmegane(void) {
  char *v2;

  v2 = "new_glasses";
  return Exists_36017472(_Dlc_k__BackingField, v2, 0);
}

// 0x194c250
bool DlcItemGetCheck(ITM _item) {
  void *v3;
  void *v6;
  void *All;
  bool v8;
  s32 v9;
  bool v10;
  char *v11;
  System_Collections_Generic_List_Enumerator_T__o v14;

  memset(&v14, 0, sizeof(v14));
  v3 = Allocate(Project_RaijinDLC___c__DisplayClass29_0);
  v3->_item = item;
  v6 = Allocate(System_Predicate_RaijinDLC_DlcItem_);
  __ctor(v6, v3, Method_Project_RaijinDLC___c__DisplayClass29_0__DlcItemGetCheck_b__0__, 0);
  All = _FindAll(dlcItemTbl, v6);
  v8 = 1;
  if (All->_size < 1)
    return v8;
  _GetEnumerator(&v14, All);
  v9 = 5;
  while (1)
  {
    v10 = _MoveNext(&v14);
    if (!v10)
      break;
    v11 = *(char **)((char *)&v14._current->klass + (u64)&off_18);
    if (Exists_36017472(_Dlc_k__BackingField, v11, 0))
      goto LABEL_22;
  }
  v9 = 6;
LABEL_22:
  _Dispose(&v14);
  return v9 == 5 && v10;
}

// 0x194c540
bool DlcDevilSelCheck(s32 _devilID) {
  char *v4;

  if ((u32)(devilID - 502) < 0xFFFFFFFA)
    return 1;
  v4 = "new_devil";
  return Exists_36017472(_Dlc_k__BackingField, v4, 0);
}

// 0x194c6a0
bool DlcDevilCheck(s32 _devilID) {
  char *v3;

  if ((u32)(devilID - 502) < 0xFFFFFFFA)
    return 0;
  v3 = "new_devil";
  return Exists_36017472(_Dlc_k__BackingField, v3, 0);
}

// 0x194c820
bool GetDlcDevilKarteF(s32 _devilID) {
  char v4;
  s32 v5;
  s32 v7;
  s32 v8;

  if (!DlcDevilCheck(devilID))
    return 0;
  v4 = devilID + 17;
  v5 = devilID - 488;
  if (devilID - 495 >= 0)
    v5 = devilID - 495;
  v7 = v5 >> 3;
  v8 = 1 << (v4 - (v5 & 0x18));
  return (u8)(v8 & GBWK->dlcKarteF[v7]) == 0;
}

// 0x194c940
void SetDlcDvlKarteF(s32 _devilID) {
  char v5;
  s32 v6;
  s32 v8;
  s32 v9;
  char *v10;

  if (!DlcDevilCheck(devilID))
    return;
  v5 = devilID + 17;
  v6 = devilID - 488;
  if (devilID - 495 >= 0)
    v6 = devilID - 495;
  v8 = v6 >> 3;
  v9 = 1 << (v5 - (v6 & 0x18));
  v10 = (char *)GBWK->dlcKarteF + v8;
  v10[32] |= v9;
}

// 0x194c930
static s32 GetDvlKarteFCheckID(s32 _devilID) {
  return devilID - 495;
}
