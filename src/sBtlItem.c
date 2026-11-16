#include "types.h"
#include "cmpitem.h"
#include "dat.h"
#include "sbtl.h"
#include "sbtlitem.h"

typedef struct SBTLITEM_LISTWORK SBTLITEM_LISTWORK;
typedef struct SBTLITEM_TBL SBTLITEM_TBL;

SBTLITEM_TBL *tbldata[768];

static void SortMenu(s32 **_nowList, s32 _num);

// 0x1f15cf0
SBTLITEM_TBL *sBtlGetItemtbl(s32 id) {
  return tbldata[id];
}

// 0x1f15d50
bool sBtlSetDropItem(s32 itemid, s32 num, s16 per, s32 luck) {
  s32 v6;
  u64 v10;
  char v11;
  s32 *v13;
  s32 v14;
  u32 v16;
  s32 *v17;
  s32 v19;

  LOWORD(v6) = per;
  v10 = 0;
  v11 = 1;
  while (1)
  {
    v13 = wk->drop->item[v10];
    v14 = v13[0];
    if (!v14)
      break;
    v13 = wk->drop->item[v10];
    v14 = v13[0];
    if (v14 == itemid)
    {
      v6 = (s16)v6;
      if (v13[2] < (s16)v6)
        goto LABEL_23;
      if (luck)
      {
LABEL_34:
        if (luck < 1)
        {
          v13 = wk->drop->item[v10];
          v13[1] += num;
          v19 = v13[3] - num;
        }
        else
        {
          v13 = wk->drop->item[v10];
          v19 = v13[3] + num;
        }
LABEL_44:
        v13[3] = v19;
        return v11;
      }
      goto LABEL_9000;
LABEL_23:
      v13[2] = v6;
      if (luck)
        goto LABEL_34;
LABEL_9000:
      v17 = wk->drop->item[v10];
      v17[1] += num;
      return v11;
    }
    v11 = v10++ < 0xB;
    if (v10 == 12)
      return v11;
  }
  v13 = wk->drop->item[v10];
  v13[0] = itemid;
  v13[2] = (s16)v6;
  if (!luck)
  {
    v13 = wk->drop->item[v10];
    v13[1] = num;
    v13[3] = 0;
    return v11;
  }
  if (luck < 1)
  {
    if (!v16)
    {
      v13 = wk->drop->item[v10];
    }
    v19 = -num;
    v13[1] = num;
    goto LABEL_44;
  }
  if (!v16)
  {
    v13 = wk->drop->item[v10];
  }
  v13[1] = 0;
  v13[3] = num;
  return v11;
}

// 0x1f16070
SBTLITEM_LISTWORK *sBtlCreateItemList(void) {
  SBTLITEM_LISTWORK *v1;

  v1 = (SBTLITEM_LISTWORK *)Allocate(SBTLITEM_LISTWORK);
  _ctor(v1, 0);
  v1->num = 0;
  return v1;
}

// 0x1f160d0
bool sBtlEntryItemList(SBTLITEM_LISTWORK *lwk) {
  int32x4_t v4;
  int8x16_t v5;
  s64 v6;
  int32x4_t v7;
  int32x4_t v8;
  int32x4_t v9;
  int32x4_t v10;
  int32x4_t v11;
  int32x4_t v12;
  int32x4_t v13;
  int16x8_t *v14;
  uint16x8_t v15;
  uint16x8_t v16;
  uint16x8_t v17;
  uint16x8_t v18;
  signed s32 v19;
  SBTLITEM_DATA *v20;
  SBTLITEM_DATA **p_data;
  s64 j;
  SBTLITEM_DATA *v23;
  SBTLITEM_DATA *v24;
  s32 v26;
  s32 v27;
  s32 ItemIDFromSortNo;
  s32 v29;
  SBTLITEM_TBL *v30;
  SBTLITEM_DATA *v32;
  SBTLITEM_LISTWORK *v37;

  v4 = 0u;
  v5.n128_u64[0] = 0x100000001LL;
  v5.n128_u64[1] = 0x100000001LL;
  v6 = 0;
  v7 = 0u;
  v8 = 0u;
  v9 = 0u;
  v10 = 0u;
  v11 = 0u;
  v12 = 0u;
  v13 = 0u;
  do
  {
    v14 = ((char *)GBWK->player->item + v6);
    v6 += 64;
    v15 = vtstq_s16(v14[3], v14[3]);
    v16 = vtstq_s16(v14[5], v14[5]);
    v17 = vtstq_s16(v14[2], v14[2]);
    v18 = vtstq_s16(v14[4], v14[4]);
    v9 = vaddq_s32(v9, vandq_s8(vmovl_high_u16(v15), v5));
    v8 = vaddq_s32(v8, vandq_s8(vmovl_u16((uint16x4_t)v15.n128_u64[0]), v5));
    v13 = vaddq_s32(v13, vandq_s8(vmovl_high_u16(v16), v5));
    v12 = vaddq_s32(v12, vandq_s8(vmovl_u16((uint16x4_t)v16.n128_u64[0]), v5));
    v7 = vaddq_s32(v7, vandq_s8(vmovl_high_u16(v17), v5));
    v4 = vaddq_s32(v4, vandq_s8(vmovl_u16((uint16x4_t)v17.n128_u64[0]), v5));
    v11 = vaddq_s32(v11, vandq_s8(vmovl_high_u16(v18), v5));
    v10 = vaddq_s32(v10, vandq_s8(vmovl_u16((uint16x4_t)v18.n128_u64[0]), v5));
  }
  while (v6 != 1536);
  v19 = vaddvq_s32(vaddq_s32(vaddq_s32(v12, vaddq_s32(v10, vaddq_s32(v8, v4))), vaddq_s32(v13, vaddq_s32(v11, vaddq_s32(v9, v7)))));
  v37 = lwk;
  if (v19)
  {
    v20 = NewSpecific(SBTLITEM_DATA, v19);
    lwk->data = v20;
    p_data = &lwk->data;
    if (v19 >= 1)
    {
      for (j = 0; j != v19; ++j)
      {
        v23 = *p_data;
        v24 = Allocate(SBTLITEM_DATA);
        _ctor(v24, 0);
        v23[j] = v24;
      }
    }
    v26 = 0;
    v27 = 0;
    while (1)
    {
      ItemIDFromSortNo = cmpGetItemIDFromSortNo(v26);
      if (ItemIDFromSortNo < 0)
        goto LABEL_16;
      v29 = ItemIDFromSortNo;
      if (datCheckItem(ItemIDFromSortNo, 1))
        goto LABEL_25;
      goto LABEL_9000;
      if (datCheckItem(v29, 1))
      {
LABEL_25:
        v30 = tbldata[v29];
        if ((v30->usetype & 2) != 0 && (v30->type & 0x1001) != 0)
        {
          v32 = (*p_data)[v27];
          v32->id = v29;
          ++v27;
          v32->num = datGetItemNum(v29);
        }
      }
LABEL_9000:
LABEL_16:
      if (++v26 == 768)
        goto LABEL_38;
    }
  }
  v27 = 0;
LABEL_38:
  v37->num = v27;
  return v19 != 0;
}

// 0x1f16480
bool sBtlEntryKatanaList(SBTLITEM_LISTWORK *lwk) {
  s64 v3;
  int32x4_t v5;
  int8x16_t v6;
  s64 v7;
  int32x4_t v8;
  int32x4_t v9;
  int32x4_t v10;
  int32x4_t v11;
  int32x4_t v12;
  int32x4_t v13;
  int32x4_t v14;
  int16x8_t *v15;
  uint16x8_t v16;
  uint16x8_t v17;
  uint16x8_t v18;
  uint16x8_t v19;
  signed s32 v20;
  SBTLITEM_DATA *v21;
  SBTLITEM_DATA **p_data;
  s64 j;
  SBTLITEM_DATA *v24;
  SBTLITEM_DATA *v25;
  s32 v27;
  s32 v28;
  char *v29;
  s32 ItemIDFromSortNo;
  s32 v31;
  SBTLITEM_TBL *v32;
  s64 v33;
  void *Instance;
  s64 v36;
  s32 v37;
  s64 v38;
  s32 v39;
  s64 v40;
  SBTLITEM_TBL *v41;
  char *v42;
  SBTLITEM_LISTWORK *v43;
  SBTLITEM_DATA *v45;
  s32 v46;
  s64 v50;
  s32 *nowList;

  v3 = NewSpecific(s32, 0x7Eu);
  nowList = v3;
  v5 = 0u;
  v6.n128_u64[0] = 0x100000001LL;
  v6.n128_u64[1] = 0x100000001LL;
  v7 = 0;
  v8 = 0u;
  v9 = 0u;
  v10 = 0u;
  v11 = 0u;
  v12 = 0u;
  v13 = 0u;
  v14 = 0u;
  do
  {
    v15 = ((char *)GBWK->player->item + v7);
    v7 += 64;
    v16 = vtstq_s16(v15[3], v15[3]);
    v17 = vtstq_s16(v15[5], v15[5]);
    v18 = vtstq_s16(v15[2], v15[2]);
    v19 = vtstq_s16(v15[4], v15[4]);
    v10 = vaddq_s32(v10, vandq_s8(vmovl_high_u16(v16), v6));
    v9 = vaddq_s32(v9, vandq_s8(vmovl_u16((uint16x4_t)v16.n128_u64[0]), v6));
    v14 = vaddq_s32(v14, vandq_s8(vmovl_high_u16(v17), v6));
    v13 = vaddq_s32(v13, vandq_s8(vmovl_u16((uint16x4_t)v17.n128_u64[0]), v6));
    v8 = vaddq_s32(v8, vandq_s8(vmovl_high_u16(v18), v6));
    v5 = vaddq_s32(v5, vandq_s8(vmovl_u16((uint16x4_t)v18.n128_u64[0]), v6));
    v12 = vaddq_s32(v12, vandq_s8(vmovl_high_u16(v19), v6));
    v11 = vaddq_s32(v11, vandq_s8(vmovl_u16((uint16x4_t)v19.n128_u64[0]), v6));
  }
  while (v7 != 1536);
  v20 = vaddvq_s32(vaddq_s32(vaddq_s32(v13, vaddq_s32(v11, vaddq_s32(v9, v5))), vaddq_s32(v14, vaddq_s32(v12, vaddq_s32(v10, v8)))));
  if (!v20)
    goto LABEL_46;
  v21 = NewSpecific(SBTLITEM_DATA, v20);
  lwk->data = v21;
  p_data = &lwk->data;
  if (v20 >= 1)
  {
    for (j = 0; j != v20; ++j)
    {
      v24 = *p_data;
      v25 = Allocate(SBTLITEM_DATA);
      _ctor(v25, 0);
      v24[j] = v25;
    }
  }
  v27 = 0;
  v28 = 0;
  v29 = &byte_5758000;
  do
  {
    ItemIDFromSortNo = cmpGetItemIDFromSortNo(v27);
    if (ItemIDFromSortNo < 1)
      goto LABEL_15;
    v31 = ItemIDFromSortNo;
    if (!datCheckItem(ItemIDFromSortNo, 1))
      goto LABEL_15;
    v32 = tbldata[v31];
    if ((v32->usetype & 2) == 0 && (v32->type & 0x400) != 0)
    {
      v33 = v3 + 4 * v28++;
      *(u32 *)(v33 + 32) = v31;
    }
LABEL_15:
    ++v27;
  }
  while (v27 != 768);
  Instance = get_Instance(0);
  SortSetting(Instance, 8, 0);
  SortMenu(&nowList, v28);
  if (*(s32 *)(v3 + 24) >= 1)
  {
    v36 = 0;
    v37 = 0;
    v50 = v3;
    v38 = v3 + 32;
    while (1)
    {
      v39 = *(u32 *)(v38 + 4 * v36);
      if (v39 >= 1)
      {
        if (datCheckItem(v39, 1))
        {
          v40 = *(s32 *)(v38 + 4 * v36);
          if ((v29[714] & 1) == 0)
          {
            v29[714] = 1;
          }
          v41 = tbldata[v40];
          if ((v41->usetype & 2) == 0 && (v41->type & 0x400) != 0)
          {
            v42 = v29;
            v43 = lwk;
            v45 = (*p_data)[v37];
            v45->id = *(u32 *)(v38 + 4 * v36);
            v46 = *(u32 *)(v38 + 4 * v36);
            v45->num = datGetItemNum(v46);
            lwk = v43;
            v29 = v42;
            v3 = v50;
            ++v37;
          }
        }
      }
      if (++v36 >= *(s32 *)(v3 + 24))
        goto LABEL_47;
    }
  }
LABEL_46:
  v37 = 0;
LABEL_47:
  lwk->num = v37;
  return v20 != 0;
}

// 0x1f16ba0
bool sBtlEntryItemList_Type(SBTLITEM_LISTWORK *lwk, u16 type) {
  int32x4_t v6;
  int8x16_t v7;
  s64 v8;
  int32x4_t v9;
  int32x4_t v10;
  int32x4_t v11;
  int32x4_t v12;
  int32x4_t v13;
  int32x4_t v14;
  int32x4_t v15;
  int16x8_t *v16;
  uint16x8_t v17;
  uint16x8_t v18;
  uint16x8_t v19;
  uint16x8_t v20;
  signed s32 v21;
  SBTLITEM_DATA *v22;
  SBTLITEM_DATA **p_data;
  s64 j;
  SBTLITEM_DATA *v25;
  SBTLITEM_DATA *v26;
  s32 v28;
  s32 v29;
  s32 ItemIDFromSortNo;
  s32 v31;
  SBTLITEM_DATA *v32;
  SBTLITEM_LISTWORK *v36;

  v6 = 0u;
  v7.n128_u64[0] = 0x100000001LL;
  v7.n128_u64[1] = 0x100000001LL;
  v8 = 0;
  v9 = 0u;
  v10 = 0u;
  v11 = 0u;
  v12 = 0u;
  v13 = 0u;
  v14 = 0u;
  v15 = 0u;
  do
  {
    v16 = ((char *)GBWK->player->item + v8);
    v8 += 64;
    v17 = vtstq_s16(v16[3], v16[3]);
    v18 = vtstq_s16(v16[5], v16[5]);
    v19 = vtstq_s16(v16[2], v16[2]);
    v20 = vtstq_s16(v16[4], v16[4]);
    v11 = vaddq_s32(v11, vandq_s8(vmovl_high_u16(v17), v7));
    v10 = vaddq_s32(v10, vandq_s8(vmovl_u16((uint16x4_t)v17.n128_u64[0]), v7));
    v15 = vaddq_s32(v15, vandq_s8(vmovl_high_u16(v18), v7));
    v14 = vaddq_s32(v14, vandq_s8(vmovl_u16((uint16x4_t)v18.n128_u64[0]), v7));
    v9 = vaddq_s32(v9, vandq_s8(vmovl_high_u16(v19), v7));
    v6 = vaddq_s32(v6, vandq_s8(vmovl_u16((uint16x4_t)v19.n128_u64[0]), v7));
    v13 = vaddq_s32(v13, vandq_s8(vmovl_high_u16(v20), v7));
    v12 = vaddq_s32(v12, vandq_s8(vmovl_u16((uint16x4_t)v20.n128_u64[0]), v7));
  }
  while (v8 != 1536);
  v21 = vaddvq_s32(vaddq_s32(vaddq_s32(v14, vaddq_s32(v12, vaddq_s32(v10, v6))), vaddq_s32(v15, vaddq_s32(v13, vaddq_s32(v11, v9)))));
  v36 = lwk;
  if (v21)
  {
    v22 = NewSpecific(SBTLITEM_DATA, v21);
    lwk->data = v22;
    p_data = &lwk->data;
    if (v21 >= 1)
    {
      for (j = 0; j != v21; ++j)
      {
        v25 = *p_data;
        v26 = Allocate(SBTLITEM_DATA);
        _ctor(v26, 0);
        v25[j] = v26;
      }
    }
    v28 = 0;
    v29 = 0;
    while (1)
    {
      ItemIDFromSortNo = cmpGetItemIDFromSortNo(v28);
      if (ItemIDFromSortNo < 0)
        goto LABEL_16;
      v31 = ItemIDFromSortNo;
      if (datCheckItem(ItemIDFromSortNo, 1))
        goto LABEL_25;
      goto LABEL_9000;
      if (datCheckItem(v31, 1))
      {
LABEL_25:
        if ((tbldata[v31]->type & type) != 0)
        {
          v32 = (*p_data)[v29];
          v32->id = v31;
          ++v29;
          v32->num = datGetItemNum(v31);
        }
      }
LABEL_9000:
LABEL_16:
      if (++v28 == 768)
        goto LABEL_37;
    }
  }
  v29 = 0;
LABEL_37:
  v36->num = v29;
  return v21 != 0;
}

// 0x1f16f70
bool sBtlReleaseItemList(SBTLITEM_LISTWORK *lwk) {
  lwk->num = 0;
  return 1;
}

// 0x1f16f80
bool sBtlDeleteItemList(SBTLITEM_LISTWORK *lwk) {
  return 1;
}

// 0x1f16990
static void SortMenu(s32 **_nowList, s32 _num) {
  void *v5;
  u64 v6;
  s64 v7;
  u64 *v8;
  s32 v9;
  s64 size;
  s32 *items;
  void *Instance;
  void *v13;
  void *v14;
  void *IndexList;
  void *v16;
  s64 v17;
  s64 i;
  s32 *v19;
  s16 Item;
  char *v21;

  v5 = Allocate(System_Collections_Generic_List_int_);
  __ctor(v5);
  if (num >= 1)
  {
    v6 = 0;
    v7 = 4 * (u32)num;
    v8 = Method_System_Collections_Generic_List_int__Add__;
    do
    {
      while (1)
      {
        v9 = (*nowList)[v6 / 4];
        size = v5->_size;
        ++v5->_version;
        items = v5->_items;
        if ((u32)size < LODWORD(items->max_length))
          break;
        _AddWithResize(v5, v9, *(const MethodInfo_2D8F530 **)(*(u64 *)(v8[4] + 192) + 112));
        v8 = Method_System_Collections_Generic_List_int__Add__;
        v6 += 4;
        if (v7 == v6)
          goto LABEL_8;
      }
      v5->_size = size + 1;
      items[size] = v9;
      v6 += 4;
    }
    while (v7 != v6);
  }
LABEL_8:
  Instance = get_Instance(0);
  ListSet_object_(Instance, v5);
  v13 = get_Instance(0);
  ListSort(v13, 0);
  v14 = get_Instance(0);
  IndexList = GetIndexList(v14, 0);
  if (num >= 1)
  {
    v16 = IndexList;
    v17 = num;
    sub_188E3B0((*nowList), 255, 4 * (u32)num);
    for (i = 0; i != v17; ++i)
    {
      v19 = *nowList;
      Item = _get_Item(v16, i);
      v21 = (char *)v19 + 4 * i;
      *((u32 *)v21 + 8) = Item;
    }
  }
}
