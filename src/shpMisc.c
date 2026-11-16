#include "types.h"
#include "dat.h"
#include "dds3kerneldraw.h"
#include "evtbit.h"
#include "sbtlitem.h"
#include "sdf_vu0.h"
#include "shpaction.h"
#include "shpdattable.h"
#include "shpmisc.h"

#define SELL20_RAITO 5

static s32 g_arrChapterFlag[14];
static s32 *g_arrKnyRankFlag;
static s32 *g_arrNwdRankFlag;

static void shpMiscQuickSort(s16 **pList, s32 max);
static s32 shpGetChapter(void);
static s8 shpChkArrivalChapter(s32 a_type);
static bool _shpChkNewArrival(s32 a_type, s32 a_itemID);
static void _shpReadNewArrival(s32 a_type, s32 a_itemID);

// 0x21a57f0
void shpPoint3To2(f32 x3, f32 y3, f32 z3, f32 *x2, f32 *y2) {
  sdfMatrix4_t *p_CameraTM;
  __int128 v14;
  __int128 v17;
  __int128 v18;
  _OWORD *p_x;
  long f64 v21;
  __int128 v22;
  sdfMatrix4_t *p_TM;
  _OWORD *v25;
  __int128 v26;
  __int128 v27;
  __int128 v28;
  struct sdfVector4_t scale;
  struct sdfVector4_t trans;
  f32 y;
  long f64 v37;
  sdfMatrix4_t v42;
  sdfMatrix4_t v43;
  sdfVector4_t v44;

  p_CameraTM = &CameraTM;
  v14 = *(_OWORD *)&p_CameraTM->m01;
  *(_OWORD *)&v43.m00 = *(_OWORD *)&p_CameraTM->m00;
  *(_OWORD *)&v43.m01 = v14;
  v17 = *(_OWORD *)&p_CameraTM->m03;
  *(_OWORD *)&v43.m02 = *(_OWORD *)&p_CameraTM->m02;
  *(_OWORD *)&v43.m03 = v17;
  v18 = *(_OWORD *)&v43.m01;
  p_x = &vf00.x;
  p_x[4] = *(_OWORD *)&v43.m00;
  p_x[5] = v18;
  v21 = *(long f64 *)&v43.m02;
  v22 = *(_OWORD *)&v43.m03;
  p_x[6] = *(_OWORD *)&v43.m02;
  p_x[7] = v22;
  p_TM = &ScreenParam->TM;
  sub_19636F0(&ScreenParam->TM, 0, v21);
  v25 = &vf00.x;
  v26 = v25[5];
  v27 = v25[6];
  v28 = v25[7];
  v25[8] = v25[4];
  v25[9] = v26;
  v25[10] = v27;
  v25[11] = v28;
  vct_A.x = x3;
  vct_A.y = y3;
  vct_A.z = z3;
  vct_A.w = 1.0;
  vct_A.w = 1.0;
  get_transpose(&v43, &mtx_A, 0);
  v42 = v43;
  v44 = op_Multiply_60923920(&v42, vct_A, 0);
  vct_A.x = v44.x * (f32)(1.0 / v44.w);
  vct_A.y = v44.y * (f32)(1.0 / v44.w);
  vct_A.z = v44.z * (f32)(1.0 / v44.w);
  vct_A.w = 1.0 / v44.w;
  scale = ScreenParam->scale;
  vct_B = scale;
  vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  trans = ScreenParam->trans;
  vct_B = trans;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  y = vct_A.y;
  *x2 = vct_A.x;
  *y2 = y;
}

// 0x21a5cb0
s32 knyGetGoodPoint(void) {
  return GBWK->shpSave->knyGoodPoint;
}

// 0x21a5d20
void knySetGoodPoint(s32 a_point) {
  GBWK->shpSave->knyGoodPoint = a_point;
}

// 0x21a5d90
s32 knyGetGoodRank(void) {
  s32 knyGoodPoint;

  knyGoodPoint = GBWK->shpSave->knyGoodPoint;
  if (knyGoodPoint < arrKnyGoodRank[9])
  {
    if (knyGoodPoint >= arrKnyGoodRank[8])
      return 8;
    if (knyGoodPoint >= arrKnyGoodRank[7])
      return 7;
    if (knyGoodPoint < arrKnyGoodRank[6])
    {
      if (knyGoodPoint < arrKnyGoodRank[5])
      {
        if (knyGoodPoint < arrKnyGoodRank[4])
        {
          if (knyGoodPoint < arrKnyGoodRank[3])
          {
            if (knyGoodPoint < arrKnyGoodRank[2])
            {
              if (knyGoodPoint >= arrKnyGoodRank[1])
                return 1;
              goto LABEL_45;
            }
            return 2;
          }
          return 3;
        }
        return 4;
      }
      return 5;
    }
    return 6;
  }
  return 9;
LABEL_45:
  if (knyGoodPoint >= arrKnyGoodRank[0])
    return 0;
  else
    return -1;
}

// 0x21a6110
void knyAddGoodPoint(s32 a_add) {
  s32 GoodRank;
  s32 v6;
  s32 v8;
  s32 v9;
  s32 v10;
  s32 v11;
  s64 v13;
  s32 v14;

  GoodRank = knyGetGoodRank();
  if (GBWK->shpSave->knyGoodPoint + a_add >= 0xFFFF)
    v6 = 0xFFFF;
  else
    v6 = GBWK->shpSave->knyGoodPoint + a_add;
  v8 = v6 & ~(v6 >> 31);
  *(u32 *)(*(u64 *)(*((u64 *)*((MethodInfo *)dat + 2).virtualMethodPointer + 60) + 144) + 16) = v8;
  v9 = knyGetGoodRank();
  if (v9 > GoodRank)
  {
    v10 = GoodRank + 1;
    v11 = v9;
    while (v10 <= v11)
    {
      v14 = g_arrKnyRankFlag[v10];
      if (v14)
      {
        if ((u32)(v14 - 2618) >= 0xFFFFFFC6)
          evtBitKityouItemAdd(v14);
        v13 = (s64)GBWK->EventBit + 4 * (v14 / 32);
        *(u32 *)(v13 + 32) |= 1 << v14;
      }
      ++v10;
    }
  }
}

// 0x21a6360
void knyCtrlGoodRank(s8 a_mode) {
  s32 v4;
  s32 v5;
  s32 v6;
  s32 v8;
  s32 v10;
  s64 v11;
  s32 v12;
  s64 v16;
  s32 v17;
  s32 v19;

  goto LABEL_3;
LABEL_16:
  if (v6 > 8)
    return;
  v16 = v6 + 1;
  v17 = arrKnyGoodRank[v16];
  GBWK->shpSave->knyGoodPoint = v17;
  v19 = g_arrKnyRankFlag[v16];
  if (v19)
  {
    if ((u32)(v19 - 2618) >= 0xFFFFFFC6)
      evtBitKityouItemAdd(v19);
    v11 = (s64)GBWK->EventBit + 4 * (v19 / 32);
    v12 = *(u32 *)(v11 + 32) | (1 << v19);
    goto LABEL_30;
  }
  return;
LABEL_3:
  v4 = knyGetGoodRank();
  v5 = a_mode;
  v6 = v4;
  if (a_mode == 1)
    goto LABEL_16;
  if (!v5 && v6 >= 1)
  {
    v8 = arrKnyGoodRank[v6 - 1];
    GBWK->shpSave->knyGoodPoint = v8;
    v10 = g_arrKnyRankFlag[v6];
    v11 = (s64)GBWK->EventBit + 4 * (v10 / 32);
    v12 = *(u32 *)(v11 + 32) & ~(1 << v10);
LABEL_30:
    *(u32 *)(v11 + 32) = v12;
    return;
  }
}

// 0x21a66a0
s32 nwdGetGoodPoint(void) {
  return GBWK->shpSave->nwdGoodPoint;
}

// 0x21a6710
void nwdSetGoodPoint(s32 a_point) {
  GBWK->shpSave->nwdGoodPoint = a_point;
}

// 0x21a6780
s32 nwdGetGoodRank(void) {
  s32 nwdGoodPoint;

  nwdGoodPoint = GBWK->shpSave->nwdGoodPoint;
  if (nwdGoodPoint < arrNwdGoodRank[9])
  {
    if (nwdGoodPoint >= arrNwdGoodRank[8])
      return 8;
    if (nwdGoodPoint >= arrNwdGoodRank[7])
      return 7;
    if (nwdGoodPoint < arrNwdGoodRank[6])
    {
      if (nwdGoodPoint < arrNwdGoodRank[5])
      {
        if (nwdGoodPoint < arrNwdGoodRank[4])
        {
          if (nwdGoodPoint < arrNwdGoodRank[3])
          {
            if (nwdGoodPoint < arrNwdGoodRank[2])
            {
              if (nwdGoodPoint >= arrNwdGoodRank[1])
                return 1;
              goto LABEL_45;
            }
            return 2;
          }
          return 3;
        }
        return 4;
      }
      return 5;
    }
    return 6;
  }
  return 9;
LABEL_45:
  if (nwdGoodPoint >= arrNwdGoodRank[0])
    return 0;
  else
    return -1;
}

// 0x21a6b00
void nwdAddGoodPoint(s32 a_add) {
  s32 GoodRank;
  s32 v6;
  s32 v8;
  s32 v9;
  s32 v10;
  s32 v11;
  s64 v13;
  s32 v14;

  GoodRank = nwdGetGoodRank();
  if (GBWK->shpSave->nwdGoodPoint + a_add >= 0xFFFF)
    v6 = 0xFFFF;
  else
    v6 = GBWK->shpSave->nwdGoodPoint + a_add;
  v8 = v6 & ~(v6 >> 31);
  *(u32 *)(*(u64 *)(*((u64 *)*((MethodInfo *)dat + 2).virtualMethodPointer + 60) + 144) + 20) = v8;
  v9 = nwdGetGoodRank();
  if (v9 > GoodRank)
  {
    v10 = GoodRank + 1;
    v11 = v9;
    while (v10 <= v11)
    {
      v14 = g_arrNwdRankFlag[v10];
      if (v14)
      {
        if ((u32)(v14 - 2618) >= 0xFFFFFFC6)
          evtBitKityouItemAdd(v14);
        v13 = (s64)GBWK->EventBit + 4 * (v14 / 32);
        *(u32 *)(v13 + 32) |= 1 << v14;
      }
      ++v10;
    }
  }
}

// 0x21a6d50
void nwdCtrlGoodRank(s8 a_mode) {
  s32 v4;
  s32 v5;
  s32 v6;
  s32 v8;
  s32 v10;
  s64 v11;
  s32 v12;
  s64 v16;
  s32 v17;
  s32 v19;

  goto LABEL_3;
LABEL_16:
  if (v6 > 8)
    return;
  v16 = v6 + 1;
  v17 = arrNwdGoodRank[v16];
  GBWK->shpSave->nwdGoodPoint = v17;
  v19 = g_arrNwdRankFlag[v16];
  if (v19)
  {
    if ((u32)(v19 - 2618) >= 0xFFFFFFC6)
      evtBitKityouItemAdd(v19);
    v11 = (s64)GBWK->EventBit + 4 * (v19 / 32);
    v12 = *(u32 *)(v11 + 32) | (1 << v19);
    goto LABEL_30;
  }
  return;
LABEL_3:
  v4 = nwdGetGoodRank();
  v5 = a_mode;
  v6 = v4;
  if (a_mode == 1)
    goto LABEL_16;
  if (!v5 && v6 >= 1)
  {
    v8 = arrNwdGoodRank[v6 - 1];
    GBWK->shpSave->nwdGoodPoint = v8;
    v10 = g_arrNwdRankFlag[v6];
    v11 = (s64)GBWK->EventBit + 4 * (v10 / 32);
    v12 = *(u32 *)(v11 + 32) & ~(1 << v10);
LABEL_30:
    *(u32 *)(v11 + 32) = v12;
    return;
  }
}

// 0x21a7090
void shpAddGoodPointBuy(s32 a_price) {
  f32 v3;
  s32 v4;

  v3 = (f32)((f32)a_price + 0.1) * 0.02;
  if (v3 == INFINITY)
    v4 = 0x80000000;
  else
    v4 = v3;
  knyAddGoodPoint(v4);
}

// 0x21a7130
void shpAddGoodPointSell(s32 a_price) {
  f32 v3;
  s32 v4;

  v3 = (f32)((f32)a_price + 0.1) * 0.01;
  if (v3 == INFINITY)
    v4 = 0x80000000;
  else
    v4 = v3;
  knyAddGoodPoint(v4);
}

// 0x21a71d0
void shpAddGoodPointOrder(s32 a_price) {
  f32 v3;
  s32 v4;

  v3 = (f32)((f32)a_price + 0.1) * 0.01;
  if (v3 == INFINITY)
    v4 = 0x80000000;
  else
    v4 = v3;
  nwdAddGoodPoint(v4);
}

// 0x21a7270
void shpAddGoodPointTrade(s32 a_price) {
  f32 v3;
  s32 v4;

  v3 = (f32)((f32)a_price + 0.1) * 0.1;
  if (v3 == INFINITY)
    v4 = 0x80000000;
  else
    v4 = v3;
  nwdAddGoodPoint(v4);
}

// 0x21a7300
s32 knyGetPriceBuy(s32 a_itemNo) {
  s32 gold;
  bool v4;
  s32 v9;
  s32 *v11;

  if ((u32)a_itemNo > 0x2FF)
    return 0;
  gold = tbldata[a_itemNo]->gold;
  v4 = evtBitCheck(2462);
  if (v4)
  {
    v9 = arrKnyPriceRatioBuy[knyGetGoodRank()] - 20;
  }
  else
  {
    v11 = arrKnyPriceRatioBuy;
    v9 = v11[knyGetGoodRank()];
  }
  return v9 * gold / 100;
}

// 0x21a7490
s32 knyGetPriceSell(s32 a_itemNo) {
  SBTLITEM_TBL *v3;
  s32 v4;
  u64 v7;
  u64 v10;

  if ((u32)a_itemNo > 0x2FF)
    return 0;
  v3 = tbldata[a_itemNo];
  if ((v3->flg & 8) != 0)
  {
    v7 = 6871947675LL * tbldata[a_itemNo]->gold;
    v4 = (v7 >> 63) + (SHIDWORD(v7) >> 5);
    goto LABEL_15;
  }
  v4 = v3->gold >> 1;
LABEL_15:
  v10 = 1374389535 * arrKnyPriceRatioSell[knyGetGoodRank()] * v4;
  return (v10 >> 63) + (SHIDWORD(v10) >> 5);
}

// 0x21a7660
s32 nwdGetPriceOrder(s32 a_itemNo) {
  if ((byte_5758F18 & 1) != 0)
  {
    if ((u32)a_itemNo <= 0x2FF)
      goto LABEL_3;
  }
  else
  {
    if ((u32)a_itemNo <= 0x2FF)
    {
LABEL_3:
      return tbldata[a_itemNo]->gold;
    }
  }
  return 0;
}

// 0x21a7730
s32 nwdGetMagTrade(s32 a_stockNo) {
  sdatUnitWork_t *v4;
  s32 level;
  s16 *now;
  s32 v7;
  s32 v8;
  s32 v9;
  s32 v10;
  f32 v13;

  if ((u32)a_stockNo > 0x1F)
    return 0;
  v4 = GBWK->player->stock_id[a_stockNo];
  level = v4->level;
  now = v4->now;
  v7 = now[16];
  v8 = now[18];
  v9 = now[17];
  v10 = now[19];
  v13 = arrNwdMagRatioTrade[nwdGetGoodRank()] * (f32)(v7 + 2 * level + v8 + v9 + v10);
  if (v13 == INFINITY)
    return 0x80000000;
  else
    return (s32)v13;
}

// 0x21a78b0
static void shpMiscQuickSort(s16 **pList, s32 max) {
  s64 v3;
  s16 *m_Items;
  s16 *v5;
  s16 *v6;
  s32 v7;
  s32 v8;

  v3 = 0;
  while (v3 != ((max - 1) & ~((max - 1) >> 31)))
  {
    m_Items = (*pList);
    v5 = &m_Items[v3++];
    v6 = &m_Items[v3];
    v7 = *v5;
    v8 = *v6;
    if (v7 > v8)
    {
      v3 = 0;
      *v5 = v8;
      *v6 = v7;
    }
  }
}

// 0x21a7900
static s32 shpGetChapter(void) {
  s32 v2;
  s64 i;
  bool v4;
  s32 *g_arrChapterFlag_local;
  s32 v6;

  v2 = 0;
  for (i = 8; ; ++i)
  {
    g_arrChapterFlag_local = g_arrChapterFlag;
    if (i - 8 >= SLODWORD(g_arrChapterFlag_local->max_length))
      break;
    v6 = *((u32 *)&g_arrChapterFlag_local->obj.klass + i);
    if (v6 < 1)
      continue;
    v6 = *((u32 *)&g_arrChapterFlag->obj.klass + i);
    v4 = !evtBitCheck(v6);
    if (!v4)
      v2 = i - 8;
  }
  return v2;
}

// 0x21a7a00
static s8 shpChkArrivalChapter(s32 a_type) {
  s32 Chapter;
  s32 v5;
  s32 v8;
  s32 v11;
  s8 result;

  *(u64 *)(NewSpecific(s32, 2u) + 32) = 0;
  Chapter = shpGetChapter();
  if (Chapter < 0)
    return 0;
  v5 = Chapter;
  if (v5 >= SLODWORD(g_arrChapterFlag->max_length))
    return 0;
  v8 = g_arrChapterFlag[v5];
  if (!v8)
    return 0;
  if (a_type)
  {
    v11 = arrNwdArrivalFlag[0][0];
    result = v11 >= 0;
    if (v11 < 0)
      return result;
LABEL_23:
    if (v8 != v11)
    {
      while (1)
        ;
    }
    return result;
  }
  v11 = arrKnyArrivalFlag[0][0];
  result = v11 >= 0;
  if ((v11 & 0x80000000) == 0)
    goto LABEL_23;
  return result;
}

// 0x21a7bb0
s8 knyChkArrivalChapter(void) {
  return shpChkArrivalChapter(0);
}

// 0x21a7c20
s8 nwdChkArrivalChapter(void) {
  return shpChkArrivalChapter(1);
}

// 0x21a7c90
s8 knyChkArrivalRank(s32 a_rank_new, s32 a_rank_old) {
  s32 i;
  s32 v7;

  for (i = 0; ; ++i)
  {
    v7 = arrKnyArrivalRank[i][0];
    if (v7 < 0)
      return 0;
    if (v7 <= a_rank_old)
      continue;
    if (arrKnyArrivalRank[i][0] <= a_rank_new)
      break;
  }
  return 1;
}

// 0x21a7db0
s8 nwdChkArrivalRank(s32 a_rank_new, s32 a_rank_old) {
  s32 i;
  s32 v7;

  for (i = 0; ; ++i)
  {
    v7 = arrNwdArrivalRank[i][0];
    if (v7 < 0)
      return 0;
    if (v7 <= a_rank_old)
      continue;
    if (arrNwdArrivalRank[i][0] <= a_rank_new)
      break;
  }
  return 1;
}

// 0x21a7ed0
s32 shpSetItemList(s32 a_listtype, s32 a_listmax, s16 **a_pList, bool _bo) {
  s32 v9;
  s32 i;
  s32 v12;
  s64 v14;
  char *v15;
  s32 j;
  char *v17;
  s32 v19;
  s64 v21;
  s32 GoodRank;
  s32 v24;
  s32 *v26;
  s32 v27;
  s64 v29;
  char *v30;
  s32 v32;
  s32 v33;
  s32 *v35;
  s32 v36;
  s64 v38;
  char *v39;
  s32 v41;

  if (a_listtype != 1)
  {
    if (a_listtype != 3)
    {
      v9 = 0;
      if (!bo)
        goto LABEL_90;
      goto LABEL_91;
    }
    v9 = 0;
    for (i = 0; ; ++i)
    {
      v12 = arrNwdArrivalFlag[i][0];
      if (v12 < 0)
      {
        GoodRank = nwdGetGoodRank();
        v24 = 0;
        while (2)
        {
          v26 = arrNwdArrivalRank[v24];
          v27 = v26[0];
          if (v27 < 0)
            goto LABEL_91;
          if (GoodRank >= v27)
          {
            v29 = v26[1];
            if (tbldata[v29]->type == 32)
            {
              v30 = (char *)*a_pList + 2 * v9++;
              *((u16 *)v30 + 16) = v29;
            }
          }
          ++v24;
          continue;
        }
      }
      if (!evtBitCheck(v12))
        continue;
      v14 = arrNwdArrivalFlag[i][1];
      if (tbldata[v14]->type == 32)
      {
        v15 = (char *)*a_pList + 2 * v9++;
        *((u16 *)v15 + 16) = v14;
      }
    }
  }
  v41 = a_listmax;
  v9 = 0;
  for (j = 0; ; ++j)
  {
    v19 = arrKnyArrivalFlag[j][0];
    if (v19 < 0)
      break;
    if (!evtBitCheck(v19))
      continue;
    v21 = arrKnyArrivalFlag[j][1];
    if ((tbldata[v21]->type & 1) == 0)
    {
      if ((tbldata[v21]->type & 0x2000) == 0)
      {
        if ((tbldata[v21]->type & 0x800) == 0)
          continue;
      }
    }
    v17 = (char *)*a_pList + 2 * v9++;
    *((u16 *)v17 + 16) = v21;
  }
  v32 = knyGetGoodRank();
  v33 = 0;
  while (2)
  {
    v35 = arrKnyArrivalRank[v33];
    v36 = v35[0];
    if ((v36 & 0x80000000) == 0)
    {
      if (v32 >= v36)
      {
        v38 = v35[1];
        if ((tbldata[v38]->type & 1) != 0)
        {
          v39 = (char *)*a_pList + 2 * v9++;
          *((u16 *)v39 + 16) = v38;
        }
      }
      ++v33;
      continue;
    }
    break;
  }
  a_listmax = v41;
  if (!bo)
LABEL_90:
    shpSortMenu(a_pList, v9, 1);
LABEL_91:
  if (v9 < a_listmax)
    sub_188E3B0(&(*a_pList)[v9], 255, 2 * (u32)(~v9 + a_listmax) + 2);
  return v9;
}

// 0x21a8540
static bool _shpChkNewArrival(s32 a_type, s32 a_itemID) {
  s32 ***p_arrNwdArrivalFlag;
  s32 **v8;
  s32 Chapter;
  s32 *v11;
  s32 v12;
  s64 v13;
  s32 v14;
  s32 v15;
  s64 v16;
  s32 *v18;
  s32 v19;
  s32 v20;
  s64 v21;
  u32 v22;
  s32 *g_arrKnyRankFlag_local;
  s32 **arrKnyArrivalRank_local;
  bool *rankItem_readFlag;
  s32 *v30;
  s32 v31;
  s64 v32;
  s32 v33;
  Il2CppClass **v34;
  s32 *v35;
  s32 v36;
  s64 v37;
  s32 v38;
  Il2CppClass **v39;
  s32 *v40;
  s32 v41;
  s64 v42;
  s32 v43;
  Il2CppClass **v44;
  s32 *v45;
  s32 v46;
  s64 v47;
  s32 v48;
  Il2CppClass **v49;
  s32 *v50;
  s32 v51;
  s64 v52;
  s32 v53;
  Il2CppClass **v54;
  s32 *v55;
  s32 v56;
  s64 v57;
  s32 v58;
  Il2CppClass **v59;
  s32 *v60;
  s32 v61;
  s64 v62;
  s32 v63;
  Il2CppClass **v64;
  s32 *v65;
  s32 v66;
  s64 v67;
  s32 v68;
  Il2CppClass **v69;
  s32 *v70;
  s32 v71;
  s64 v72;
  s32 v73;
  Il2CppClass **v74;

  NewSpecific(int__, 2u);
  if (a_type)
  {
    p_arrNwdArrivalFlag = &arrNwdArrivalFlag;
  }
  else
  {
    p_arrNwdArrivalFlag = &arrKnyArrivalFlag;
  }
  v8 = *p_arrNwdArrivalFlag;
  if (!evtBitCheck(2306) || evtBitCheck(2307))
  {
    Chapter = shpGetChapter();
    v11 = v8[0];
    v12 = v11[0];
    if (v12 < 0)
      goto LABEL_30;
    v13 = 0;
    v14 = 1;
    v15 = g_arrChapterFlag[Chapter];
    while (1)
    {
      if (v12 == v15 && v11[1] == a_itemID)
      {
        if (!GBWK->chapterItem_readFlag[v13])
          return 1;
      }
      v16 = (s64)v8 + 8 * v14;
      v13 = v14++;
      v11 = *(s32 **)(v16 + 32);
      v12 = v11[0];
      if (v12 < 0)
        goto LABEL_30;
    }
  }
  if (evtBitCheck(2960))
  {
    v18 = v8[0];
    v19 = v18[0];
    if ((v19 & 0x80000000) == 0)
    {
      v20 = 1;
      while (v19 != 2960 || v18[1] != a_itemID)
      {
        v21 = (s64)v8 + 8 * v20++;
        v18 = *(s32 **)(v21 + 32);
        v19 = v18[0];
        if (v19 < 0)
          goto LABEL_30;
      }
      return 1;
    }
  }
LABEL_30:
  if (!a_type)
  {
    if (v22)
    {
      g_arrKnyRankFlag_local = g_arrKnyRankFlag;
      goto LABEL_38;
    }
    else
    {
      g_arrKnyRankFlag_local = g_arrKnyRankFlag;
LABEL_38:
      arrKnyArrivalRank_local = *((s32 ***)*((MethodInfo *)shpDatTable + 2).virtualMethodPointer + 7);
      knyGetGoodRank();
LABEL_39:
      rankItem_readFlag = GBWK->rankItem_readFlag;
      if (!evtBitCheck(g_arrKnyRankFlag_local[1]))
        goto LABEL_47;
      goto LABEL_40;
    }
    arrKnyArrivalRank_local = arrKnyArrivalRank;
    knyGetGoodRank();
    goto LABEL_39;
  }
  if (v22)
  {
    g_arrKnyRankFlag_local = g_arrNwdRankFlag;
    goto LABEL_33;
  }
  g_arrKnyRankFlag_local = g_arrNwdRankFlag;
LABEL_33:
  arrKnyArrivalRank_local = *((s32 ***)*((MethodInfo *)shpDatTable + 2).virtualMethodPointer + 8);
  nwdGetGoodRank();
  rankItem_readFlag = GBWK->drink_readFlag;
  if (!evtBitCheck(g_arrKnyRankFlag_local[1]))
    goto LABEL_47;
LABEL_40:
  v30 = arrKnyArrivalRank_local[0];
  v31 = v30[0];
  if (v31 >= 1)
  {
    v32 = 0;
    v33 = 1;
    while (v31 != 1 || v30[1] != a_itemID || rankItem_readFlag[v32])
    {
      v34 = &arrKnyArrivalRank_local->obj.klass + v33;
      v32 = v33++;
      v30 = v34[4];
      v31 = v30[0];
      if (v31 <= 0)
        goto LABEL_47;
    }
    return 1;
  }
LABEL_47:
  if (evtBitCheck(g_arrKnyRankFlag_local[2]))
  {
    v35 = arrKnyArrivalRank_local[0];
    v36 = v35[0];
    if (v36 >= 1)
    {
      v37 = 0;
      v38 = 1;
      while (v36 != 2 || v35[1] != a_itemID || rankItem_readFlag[v37])
      {
        v39 = &arrKnyArrivalRank_local->obj.klass + v38;
        v37 = v38++;
        v35 = v39[4];
        v36 = v35[0];
        if (v36 <= 0)
          goto LABEL_55;
      }
      return 1;
    }
  }
LABEL_55:
  if (evtBitCheck(g_arrKnyRankFlag_local[3]))
  {
    v40 = arrKnyArrivalRank_local[0];
    v41 = v40[0];
    if (v41 >= 1)
    {
      v42 = 0;
      v43 = 1;
      while (v41 != 3 || v40[1] != a_itemID || rankItem_readFlag[v42])
      {
        v44 = &arrKnyArrivalRank_local->obj.klass + v43;
        v42 = v43++;
        v40 = v44[4];
        v41 = v40[0];
        if (v41 <= 0)
          goto LABEL_63;
      }
      return 1;
    }
  }
LABEL_63:
  if (evtBitCheck(g_arrKnyRankFlag_local[4]))
  {
    v45 = arrKnyArrivalRank_local[0];
    v46 = v45[0];
    if (v46 >= 1)
    {
      v47 = 0;
      v48 = 1;
      while (v46 != 4 || v45[1] != a_itemID || rankItem_readFlag[v47])
      {
        v49 = &arrKnyArrivalRank_local->obj.klass + v48;
        v47 = v48++;
        v45 = v49[4];
        v46 = v45[0];
        if (v46 <= 0)
          goto LABEL_71;
      }
      return 1;
    }
  }
LABEL_71:
  if (evtBitCheck(g_arrKnyRankFlag_local[5]))
  {
    v50 = arrKnyArrivalRank_local[0];
    v51 = v50[0];
    if (v51 >= 1)
    {
      v52 = 0;
      v53 = 1;
      while (v51 != 5 || v50[1] != a_itemID || rankItem_readFlag[v52])
      {
        v54 = &arrKnyArrivalRank_local->obj.klass + v53;
        v52 = v53++;
        v50 = v54[4];
        v51 = v50[0];
        if (v51 <= 0)
          goto LABEL_79;
      }
      return 1;
    }
  }
LABEL_79:
  if (evtBitCheck(g_arrKnyRankFlag_local[6]))
  {
    v55 = arrKnyArrivalRank_local[0];
    v56 = v55[0];
    if (v56 >= 1)
    {
      v57 = 0;
      v58 = 1;
      while (v56 != 6 || v55[1] != a_itemID || rankItem_readFlag[v57])
      {
        v59 = &arrKnyArrivalRank_local->obj.klass + v58;
        v57 = v58++;
        v55 = v59[4];
        v56 = v55[0];
        if (v56 <= 0)
          goto LABEL_87;
      }
      return 1;
    }
  }
LABEL_87:
  if (evtBitCheck(g_arrKnyRankFlag_local[7]))
  {
    v60 = arrKnyArrivalRank_local[0];
    v61 = v60[0];
    if (v61 >= 1)
    {
      v62 = 0;
      v63 = 1;
      while (v61 != 7 || v60[1] != a_itemID || rankItem_readFlag[v62])
      {
        v64 = &arrKnyArrivalRank_local->obj.klass + v63;
        v62 = v63++;
        v60 = v64[4];
        v61 = v60[0];
        if (v61 <= 0)
          goto LABEL_95;
      }
      return 1;
    }
  }
LABEL_95:
  if (evtBitCheck(g_arrKnyRankFlag_local[8]))
  {
    v65 = arrKnyArrivalRank_local[0];
    v66 = v65[0];
    if (v66 >= 1)
    {
      v67 = 0;
      v68 = 1;
      while (v66 != 8 || v65[1] != a_itemID || rankItem_readFlag[v67])
      {
        v69 = &arrKnyArrivalRank_local->obj.klass + v68;
        v67 = v68++;
        v65 = v69[4];
        v66 = v65[0];
        if (v66 <= 0)
          goto LABEL_103;
      }
      return 1;
    }
  }
LABEL_103:
  if (evtBitCheck(g_arrKnyRankFlag_local[9]))
  {
    v70 = arrKnyArrivalRank_local[0];
    v71 = v70[0];
    if (v71 >= 1)
    {
      v72 = 0;
      v73 = 1;
      while (v71 != 9 || v70[1] != a_itemID || rankItem_readFlag[v72])
      {
        v74 = &arrKnyArrivalRank_local->obj.klass + v73;
        v72 = v73++;
        v70 = v74[4];
        v71 = v70[0];
        if (v71 <= 0)
          return 0;
      }
      return 1;
    }
  }
  return 0;
}

// 0x21a8c90
bool shpChkNewArrival(s32 a_itemID, s32 a_acttype) {
  s32 v5;
  s32 v7;
  s32 v8;

  if (a_acttype == 1058)
  {
    v5 = 1;
    goto LABEL_6;
  }
  if (a_acttype == 138)
  {
    v5 = 0;
LABEL_6:
    v7 = v5;
    v8 = a_itemID;
    return _shpChkNewArrival(v7, v8);
  }
  return 0;
}

// 0x21a8d50
static void _shpReadNewArrival(s32 a_type, s32 a_itemID) {
  s32 **arrNwdArrivalFlag_local;
  s32 Chapter;
  s32 *v12;
  s32 v13;
  s64 v14;
  s32 v15;
  s32 v16;
  bool *chapterItem_readFlag;
  s64 v18;
  u32 v20;
  s32 *g_arrNwdRankFlag_local;
  s32 **arrNwdArrivalRank_local;
  bool *drink_readFlag;
  s32 *v29;
  s32 v30;
  s64 v31;
  s32 v32;
  Il2CppClass **v33;
  char *v34;
  u8 *v35;
  s32 v36;
  s32 *v37;
  s32 v38;
  s64 v39;
  s32 v40;
  Il2CppClass **v41;
  char *v42;
  u8 *v43;
  s32 v44;
  s32 *v45;
  s32 v46;
  s64 v47;
  s32 v48;
  Il2CppClass **v49;
  char *v50;
  u8 *v51;
  s32 v52;
  s32 *v53;
  s32 v54;
  s64 v55;
  s32 v56;
  Il2CppClass **v57;
  char *v58;
  u8 *v59;
  s32 v60;
  s32 *v61;
  s32 v62;
  s64 v63;
  s32 v64;
  Il2CppClass **v65;
  char *v66;
  u8 *v67;
  s32 v68;
  s32 *v69;
  s32 v70;
  s64 v71;
  s32 v72;
  Il2CppClass **v73;
  char *v74;
  u8 *v75;
  s32 v76;
  s32 *v77;
  s32 v78;
  s64 v79;
  s32 v80;
  Il2CppClass **v81;
  char *v82;
  u8 *v83;
  s32 v84;
  s32 *v85;
  s32 v86;
  s64 v87;
  s32 v88;
  Il2CppClass **v89;
  char *v90;
  u8 *v91;
  s32 v92;
  s32 *v93;
  s32 v94;
  s64 v95;
  s32 v96;
  Il2CppClass **v97;
  char *v98;
  u8 *v99;
  s32 v100;
  bool **p_drink_readFlag;

  NewSpecific(int__, 2u);
  if (a_type)
  {
    arrNwdArrivalFlag_local = arrNwdArrivalFlag;
  }
  else
  {
    arrNwdArrivalFlag_local = arrKnyArrivalFlag;
  }
  Chapter = shpGetChapter();
  v12 = arrNwdArrivalFlag_local[0];
  v13 = v12[0];
  if (v13 < 0)
  {
LABEL_16:
    if (a_type)
    {
      if (v20)
      {
        g_arrNwdRankFlag_local = g_arrNwdRankFlag;
        goto LABEL_19;
      }
      else
      {
        g_arrNwdRankFlag_local = g_arrNwdRankFlag;
LABEL_19:
        arrNwdArrivalRank_local = *((s32 ***)*((MethodInfo *)shpDatTable + 2).virtualMethodPointer + 8);
        nwdGetGoodRank();
LABEL_20:
        drink_readFlag = GBWK->drink_readFlag;
        if (!evtBitCheck(g_arrNwdRankFlag_local[1]))
        {
LABEL_37:
          if (evtBitCheck(g_arrNwdRankFlag_local[2]))
          {
            v37 = arrNwdArrivalRank_local[0];
            v38 = v37[0];
            if (v38 >= 1)
            {
              v39 = 0;
              v40 = 1;
              do
              {
                if (v38 == 2 && v37[1] == a_itemID)
                {
                  v42 = (char *)drink_readFlag + v39;
                  v44 = (u8)v42[32];
                  v43 = v42 + 32;
                  if (!v44)
                    *v43 = 1;
                }
                v41 = &arrNwdArrivalRank_local->obj.klass + v40;
                v39 = v40++;
                v37 = v41[4];
                v38 = v37[0];
              }
              while (v38 > 0);
            }
          }
          if (evtBitCheck(g_arrNwdRankFlag_local[3]))
          {
            v45 = arrNwdArrivalRank_local[0];
            v46 = v45[0];
            if (v46 >= 1)
            {
              v47 = 0;
              v48 = 1;
              do
              {
                if (v46 == 3 && v45[1] == a_itemID)
                {
                  v50 = (char *)drink_readFlag + v47;
                  v52 = (u8)v50[32];
                  v51 = v50 + 32;
                  if (!v52)
                    *v51 = 1;
                }
                v49 = &arrNwdArrivalRank_local->obj.klass + v48;
                v47 = v48++;
                v45 = v49[4];
                v46 = v45[0];
              }
              while (v46 > 0);
            }
          }
          if (evtBitCheck(g_arrNwdRankFlag_local[4]))
          {
            v53 = arrNwdArrivalRank_local[0];
            v54 = v53[0];
            if (v54 >= 1)
            {
              v55 = 0;
              v56 = 1;
              do
              {
                if (v54 == 4 && v53[1] == a_itemID)
                {
                  v58 = (char *)drink_readFlag + v55;
                  v60 = (u8)v58[32];
                  v59 = v58 + 32;
                  if (!v60)
                    *v59 = 1;
                }
                v57 = &arrNwdArrivalRank_local->obj.klass + v56;
                v55 = v56++;
                v53 = v57[4];
                v54 = v53[0];
              }
              while (v54 > 0);
            }
          }
          if (evtBitCheck(g_arrNwdRankFlag_local[5]))
          {
            v61 = arrNwdArrivalRank_local[0];
            v62 = v61[0];
            if (v62 >= 1)
            {
              v63 = 0;
              v64 = 1;
              do
              {
                if (v62 == 5 && v61[1] == a_itemID)
                {
                  v66 = (char *)drink_readFlag + v63;
                  v68 = (u8)v66[32];
                  v67 = v66 + 32;
                  if (!v68)
                    *v67 = 1;
                }
                v65 = &arrNwdArrivalRank_local->obj.klass + v64;
                v63 = v64++;
                v61 = v65[4];
                v62 = v61[0];
              }
              while (v62 > 0);
            }
          }
          if (evtBitCheck(g_arrNwdRankFlag_local[6]))
          {
            v69 = arrNwdArrivalRank_local[0];
            v70 = v69[0];
            if (v70 >= 1)
            {
              v71 = 0;
              v72 = 1;
              do
              {
                if (v70 == 6 && v69[1] == a_itemID)
                {
                  v74 = (char *)drink_readFlag + v71;
                  v76 = (u8)v74[32];
                  v75 = v74 + 32;
                  if (!v76)
                    *v75 = 1;
                }
                v73 = &arrNwdArrivalRank_local->obj.klass + v72;
                v71 = v72++;
                v69 = v73[4];
                v70 = v69[0];
              }
              while (v70 > 0);
            }
          }
          if (evtBitCheck(g_arrNwdRankFlag_local[7]))
          {
            v77 = arrNwdArrivalRank_local[0];
            v78 = v77[0];
            if (v78 >= 1)
            {
              v79 = 0;
              v80 = 1;
              do
              {
                if (v78 == 7 && v77[1] == a_itemID)
                {
                  v82 = (char *)drink_readFlag + v79;
                  v84 = (u8)v82[32];
                  v83 = v82 + 32;
                  if (!v84)
                    *v83 = 1;
                }
                v81 = &arrNwdArrivalRank_local->obj.klass + v80;
                v79 = v80++;
                v77 = v81[4];
                v78 = v77[0];
              }
              while (v78 > 0);
            }
          }
          if (evtBitCheck(g_arrNwdRankFlag_local[8]))
          {
            v85 = arrNwdArrivalRank_local[0];
            v86 = v85[0];
            if (v86 >= 1)
            {
              v87 = 0;
              v88 = 1;
              do
              {
                if (v86 == 8 && v85[1] == a_itemID)
                {
                  v90 = (char *)drink_readFlag + v87;
                  v92 = (u8)v90[32];
                  v91 = v90 + 32;
                  if (!v92)
                    *v91 = 1;
                }
                v89 = &arrNwdArrivalRank_local->obj.klass + v88;
                v87 = v88++;
                v85 = v89[4];
                v86 = v85[0];
              }
              while (v86 > 0);
            }
          }
          if (evtBitCheck(g_arrNwdRankFlag_local[9]))
          {
            v93 = arrNwdArrivalRank_local[0];
            v94 = v93[0];
            if (v94 >= 1)
            {
              v95 = 0;
              v96 = 1;
              do
              {
                if (v94 == 9 && v93[1] == a_itemID)
                {
                  v98 = (char *)drink_readFlag + v95;
                  v100 = (u8)v98[32];
                  v99 = v98 + 32;
                  if (!v100)
                    *v99 = 1;
                }
                v97 = &arrNwdArrivalRank_local->obj.klass + v96;
                v95 = v96++;
                v93 = v97[4];
                v94 = v93[0];
              }
              while (v94 > 0);
            }
          }
          if (a_type)
          {
            p_drink_readFlag = &GBWK->drink_readFlag;
            *p_drink_readFlag = drink_readFlag;
          }
          else
          {
            p_drink_readFlag = &GBWK->rankItem_readFlag;
            *p_drink_readFlag = drink_readFlag;
          }
          return;
        }
LABEL_30:
        v29 = arrNwdArrivalRank_local[0];
        v30 = v29[0];
        if (v30 >= 1)
        {
          v31 = 0;
          v32 = 1;
          do
          {
            if (v30 == 1 && v29[1] == a_itemID)
            {
              v34 = (char *)drink_readFlag + v31;
              v36 = (u8)v34[32];
              v35 = v34 + 32;
              if (!v36)
                *v35 = 1;
            }
            v33 = &arrNwdArrivalRank_local->obj.klass + v32;
            v31 = v32++;
            v29 = v33[4];
            v30 = v29[0];
          }
          while (v30 > 0);
        }
        goto LABEL_37;
      }
      arrNwdArrivalRank_local = arrNwdArrivalRank;
      nwdGetGoodRank();
      goto LABEL_20;
    }
    if (v20)
    {
      g_arrNwdRankFlag_local = g_arrKnyRankFlag;
      goto LABEL_28;
    }
    else
    {
      g_arrNwdRankFlag_local = g_arrKnyRankFlag;
LABEL_28:
      arrNwdArrivalRank_local = *((s32 ***)*((MethodInfo *)shpDatTable + 2).virtualMethodPointer + 7);
      knyGetGoodRank();
LABEL_29:
      drink_readFlag = GBWK->rankItem_readFlag;
      if (!evtBitCheck(g_arrNwdRankFlag_local[1]))
        goto LABEL_37;
      goto LABEL_30;
    }
    arrNwdArrivalRank_local = arrKnyArrivalRank;
    knyGetGoodRank();
    goto LABEL_29;
  }
  v14 = 0;
  v15 = 1;
  v16 = g_arrChapterFlag[Chapter];
  while (1)
  {
    if (v13 == v16 && v12[1] == a_itemID)
    {
      chapterItem_readFlag = GBWK->chapterItem_readFlag;
      if (!chapterItem_readFlag[v14])
        break;
    }
    v18 = (s64)arrNwdArrivalFlag_local + 8 * v15;
    v14 = v15++;
    v12 = *(s32 **)(v18 + 32);
    v13 = v12[0];
    if (v13 < 0)
      goto LABEL_16;
  }
  chapterItem_readFlag = GBWK->chapterItem_readFlag;
  chapterItem_readFlag[v14] = 1;
}
