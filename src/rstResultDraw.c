#include "types.h"
#include "buttonguide.h"
#include "dat.h"
#include "itf.h"
#include "rstresultdraw.h"
#include "sbtlitem.h"
#include "sdat.h"
#include "tips.h"

typedef struct sdfIVector2_t sdfIVector2_t;
typedef struct sprHandle_t sprHandle_t;

void *rstGuides;
void *rstSprTable01;
void *rstSprTable02;
void *rstSprTable03;
void *rstSprTableRoot;

// macros
// 0x1e01980: void BG(void *pBG, s32 AlphaRate, u32 OtNo)
static inline void BG(void *pBG, s32 AlphaRate, u32 OtNo) {
  u64 *v5;
  void *v6;
  void *v7;
  s64 v8;
  s32 Timer;
  s64 v11;
  s32 v12;

  v5 = NewSpecific(rstAlphaTable_t, 3u);
  v6 = Allocate(rstAlphaTable_t);
  *(u64 *)&v6->Frame = 0x3200000000LL;
  if (!QueryInterface(v6, *(void **)(*v5 + 64)))
    goto LABEL_117;
  v5[4] = v6;
  v7 = Allocate(rstAlphaTable_t);
  *(u64 *)&v7->Frame = 0x4600000078LL;
  {
LABEL_117:
  }
  v5[6] = v8;
  Timer = pBG->Timer;
  rstCalcAlphaRate(Timer, v5, *((u32 *)v5 + 6));
  v11 = (v5[3] << 32) - 0x100000000LL;
  v12 = pBG->Timer + 1;
  pBG->Timer = v12;
  if (v12 > *(u32 *)(*(u64 *)((char *)v5 + (v11 >> 29) + 32) + 16))
  {
    pBG->Timer = 0;
LABEL_10:
    goto LABEL_11;
  }
  else
  {
    goto LABEL_10;
  }
LABEL_11:
  return;
}

// 0x1dfd720
void rstResultResultGuideSet(GUIDE_RESULT _id, bool _timer, s32 _waitTimer) {
  Il2CppObject *Item;
  void *Instance;
  Il2CppObject *v16;

  if (tipsProcessCheck())
    return;
  if (object___ContainsKey(rstGuides, id))
  {
    if (logdispwk->start)
      return;
    Item = object___get_Item(**((void ***)rstResultDraw + 23), id);
    if (op_Inequality(GuideName, Item, 0))
    {
      Instance = get_Instance(0);
      ItfButtonGuideActive(Instance, 1, 0);
      v16 = object___get_Item(rstGuides, id);
      ButtonGuideDispSet(v16, timer, waitTimer);
    }
    return;
  }
  LogWarning("無効なボタンガイドID", 0);
}

// 0x1e01280
s32 rstResultGetSpriteNo(s32 TableNo, s32 PartsNo) {
  return rstSprTableRoot[TableNo]->pSprTable[PartsNo]->No;
}

// 0x1e01310
void rstResultGetSpritePos(s32 TableNo, s32 PartsNo, s32 pX, s32 pY) {

}

// 0x1e01370
void rstResultSpriteParts(s32 X, s32 Y, const sdfVector2_t *Scale, s32 AlphaRate, s32 TableNo, s32 PartsNo, sprHandle_t *pSpr, u32 OtNo) {
  return;
}

// 0x1e01420
void rstResultSpritePartsEx(s32 X, s32 Y, const sdfVector2_t *Scale, s32 AlphaRate, s32 TableNo, s32 PartsNo, sprHandle_t *pSpr, s32 color, u32 OtNo) {
  int32x4_t *v11;

  v11 = NewSpecific(uint, 4u);
  v11[2] = vdupq_n_s32(color);
  return;
}

// 0x1e01510
s32 rstCheckNumArea(s32 Val, s32 Min, s32 Max) {
  return Val >= Min && Val < Max;
}

// 0x1e01520
s32 rstCalcAlphaRate(s32 NowFrame, void *pTable, s32 TableNums) {
  s64 v7;
  s64 v9;
  s32 Frame;
  s32 v11;
  void *v12;
  void *v13;

  v7 = (u32)(TableNums - 1);
  if ((s32)v7 < 1)
    return 0;
  v9 = 0;
  Frame = pTable[0]->Frame;
  while (1)
  {
    v11 = pTable[v9 + 1]->Frame;
    if (Frame <= NowFrame && v11 > NowFrame)
      break;
    ++v9;
    Frame = v11;
    if (v7 == v9)
      return 0;
  }
  v12 = pTable[(u32)v9];
  v13 = pTable[(u32)(v9 + 1)];
  return ((v13->Alpha - v12->Alpha) * (NowFrame - v12->Frame) / (v13->Frame - v12->Frame) + v12->Alpha) << 8 >> 7;
}

// 0x1e01680
void rstCalcScale(s32 NowFrame, void *pTable, s32 TableNums, const sdfVector2_t *Scale) {
  s64 v8;
  void *v9;
  s32 Frame;
  s32 v12;

  v8 = (TableNums - 1) & (u32)~((TableNums - 1) >> 31);
  v9 = &pTable[1];
  do
  {
    if (!v8)
      break;
    Frame = (*(v9 - 1))->Frame;
    v12 = v9->Frame;
    --v8;
    ++v9;
  }
  while (Frame > NowFrame || v12 <= NowFrame);
}

// 0x1e01730
void rstCalcPosition(s32 NowFrame, void *pTable, s32 TableNums, sdfIVector2_t Position) {
  s64 v8;
  void *v9;
  s64 v10;
  s32 Frame;
  s32 v13;
  s64 v14;
  void *m_Items;
  s32 v16;
  s64 v17;
  f32 v18;
  void *v19;
  s32 v20;
  s32 Item;
  f32 v22;
  s32 v23;
  s32 v24;
  f32 v25;
  s32 v26;
  void *v27;
  s32 v28;
  s32 v29;
  f32 v30;
  s32 v31;
  s32 v32;
  f32 v33;
  s32 v34;
  sdfIVector2_t v35;

  v35 = Position;
  v8 = (TableNums - 1) & (u32)~((TableNums - 1) >> 31);
  v9 = &pTable[1];
  v10 = 1;
  while (v8 + v10 != 1)
  {
    Frame = (*(v9 - 1))->Frame;
    v13 = v9->Frame;
    --v10;
    ++v9;
    if (Frame <= NowFrame && v13 > NowFrame)
    {
      v8 = -v10;
      break;
    }
  }
  v14 = v8;
  m_Items = pTable;
  v16 = m_Items[v8]->Frame;
  v17 = (s32)v8 + 1;
  v18 = (NowFrame - v16);
  v19 = m_Items[v17];
  v20 = v19->Frame - v16;
  Item = get_Item((sdfIVector2_t)&v19->Position, 0, 0);
  v22 = (Item - get_Item((sdfIVector2_t)&m_Items[v14]->Position, 0, 0));
  v23 = get_Item((sdfIVector2_t)&m_Items[v14]->Position, 0, 0);
  set_Item((sdfIVector2_t)&v35, 0, v23, 0);
  v24 = get_Item((sdfIVector2_t)&v35, 0, 0);
  v25 = (f32)(v18 * v22) / (f32)v20;
  v26 = v25;
  if (v25 == INFINITY)
    v26 = 0x80000000;
  set_Item((sdfIVector2_t)&v35, 0, v26 + v24, 0);
  v27 = m_Items[v17];
  v28 = v27->Frame - m_Items[v14]->Frame;
  v29 = get_Item((sdfIVector2_t)&v27->Position, 1, 0);
  v30 = (v29 - get_Item((sdfIVector2_t)&m_Items[v14]->Position, 1, 0));
  v31 = get_Item((sdfIVector2_t)&m_Items[v14]->Position, 1, 0);
  set_Item((sdfIVector2_t)&v35, 1, v31, 0);
  v32 = get_Item((sdfIVector2_t)&v35, 1, 0);
  v33 = (f32)(v18 * v30) / (f32)v28;
  v34 = v33;
  if (v33 == INFINITY)
    v34 = 0x80000000;
  set_Item((sdfIVector2_t)&v35, 1, v34 + v32, 0);
}

// 0x1e021f0
void rstResultGetExpCyuusei(void *pData, s32 X, s32 Y, s32 AlphaRate, s32 Exp, s32 Cyuusei, sprHandle_t *pSpr) {
  s32 v21;
  int32x4_t *v29;
  s32 v31;
  s32 v32;
  int32x4_t *v33;
  s32 v34;
  u32 v36;
  Il2CppObject *Instance;

  if ((pData->Reward->lucktypef & 1) == 0)
  {
    goto LABEL_18;
  }
  if (pData->step >= 7)
  {
    v29 = NewSpecific(uint, 4u);
    v21 = -1600756608;
    v29[2] = vdupq_n_s32(0xA0966480);
    goto LABEL_24;
  }
LABEL_18:
  v21 = 0;
LABEL_24:
  goto LABEL_26;
LABEL_47:
  if (pData->step < 5)
    goto LABEL_48;
  v31 = 257 * v21;
  v32 = (v21 << 8) | (v31 << 16);
  v33 = NewSpecific(uint, 4u);
  v34 = v32 | v21;
  v36 = v34 - 1600756608;
  v33[2] = vdupq_n_s32(v36);
LABEL_54:
  goto LABEL_55;
LABEL_26:
  if ((pData->Reward->lucktypef & 2) != 0)
    goto LABEL_47;
LABEL_48:
  goto LABEL_54;
LABEL_55:
  goto LABEL_56;
LABEL_98:
  if (pData->step < 1)
    goto LABEL_102;
  goto LABEL_102;
LABEL_56:
  if ((pData->Reward->lucktypef & 1) != 0)
    goto LABEL_98;
LABEL_102:
  if ((pData->Reward->lucktypef & 2) == 0)
    goto LABEL_115;
  if (pData->step < 1)
LABEL_115:
  Instance = _get_Instance();
  AllExpCyuuseiDrawUnity(Instance[6].klass, Exp, Cyuusei, 0);
}

// 0x1e02950
void rstResultExpGauge(void *pData, s32 X, s32 Y, s32 AlphaRate, s32 CurrentExp, s32 CurrentLevelExp, s32 NextLevelExp, s32 *pPartsList, sprHandle_t *pSpr, ResultDrawType _type) {
  s32 v16;
  s32 v18;
  s32 v19;
  Il2CppObject *Instance;

  goto LABEL_5;
LABEL_11:
  goto LABEL_14;
LABEL_19:
  v19 = (NextLevelExp - CurrentExp) / 256;
  goto LABEL_20;
LABEL_5:
  v16 = CurrentExp - CurrentLevelExp;
  if (CurrentExp >= CurrentLevelExp)
    goto LABEL_11;
LABEL_14:
  v18 = NextLevelExp - CurrentLevelExp;
  if (v18)
    goto LABEL_19;
  v19 = 0;
LABEL_20:
  Instance = _get_Instance();
  ExpDrawUnity(Instance[6].monitor, v19, v16, v18, type, 0);
}

// 0x1e02af0
void rstResultAddLevelUpAnimQue(void *pQue) {
  s32 *Timer;
  s32 v3;
  s32 *m_Items;
  s32 v5;
  s32 v6;
  s32 *v7;
  s32 v8;
  s32 v9;
  s32 *v10;
  s32 v11;
  s32 v12;
  s32 *v13;
  s32 v14;
  s32 v15;
  s32 *v16;
  s32 v17;
  s32 v18;
  s32 *v19;
  s32 v20;
  s32 *v21;
  s32 *v22;

  Timer = pQue->Timer;
  v3 = Timer[1];
  m_Items = Timer;
  if (Timer[0])
  {
    v5 = 1;
    v6 = Timer[2];
    v7 = &Timer[1];
    if (v3)
      goto LABEL_3;
  }
  else
  {
    v5 = Timer[1];
    *m_Items = v3;
    v6 = Timer[2];
    v7 = &Timer[1];
    if (v3)
    {
LABEL_3:
      v8 = 1;
      v9 = Timer[3];
      v10 = &Timer[2];
      if (v6)
        goto LABEL_4;
      goto LABEL_21;
    }
  }
  v8 = v6;
  *v7 = v6;
  v9 = Timer[3];
  v10 = &Timer[2];
  if (v6)
  {
LABEL_4:
    v11 = 1;
    v12 = Timer[4];
    v13 = &Timer[3];
    if (v9)
      goto LABEL_5;
    goto LABEL_22;
  }
LABEL_21:
  v11 = v9;
  *v10 = v9;
  v12 = Timer[4];
  v13 = &Timer[3];
  if (v9)
  {
LABEL_5:
    v14 = 1;
    v15 = Timer[5];
    v16 = &Timer[4];
    if (v12)
      goto LABEL_6;
    goto LABEL_23;
  }
LABEL_22:
  v14 = v12;
  *v13 = v12;
  v15 = Timer[5];
  v16 = &Timer[4];
  if (v12)
  {
LABEL_6:
    v17 = 1;
    v18 = Timer[6];
    v19 = &Timer[5];
    if (v15)
      goto LABEL_7;
LABEL_24:
    v20 = v18;
    *v19 = v18;
    if (v18)
      goto LABEL_9;
    goto LABEL_8;
  }
LABEL_23:
  v17 = v15;
  *v16 = v15;
  v18 = Timer[6];
  v19 = &Timer[5];
  if (!v15)
    goto LABEL_24;
LABEL_7:
  v20 = 1;
  if (!v18)
  {
LABEL_8:
    v18 = Timer[7];
    Timer[6] = v18;
  }
LABEL_9:
  Timer[7] = 0;
  v21 = &Timer[7];
  if (v5)
  {
    m_Items = v7;
    if (v8)
    {
      m_Items = v10;
      if (v11)
      {
        m_Items = v13;
        if (v14)
        {
          m_Items = v16;
          if (v17)
          {
            m_Items = v19;
            if (v20)
            {
              v22 = &Timer[6];
              if (v18)
                m_Items = v21;
              else
                m_Items = v22;
            }
          }
        }
      }
    }
  }
  *m_Items = 45;
}

// 0x1e02c30
void rstResultLevelUpAnim(s32 X, s32 Y, s32 AlphaRate, s32 Type, void *pQue, sprHandle_t *pSpr) {
  u64 *v8;
  void *v9;
  void *v10;
  void *v11;
  u64 *v12;
  void *v13;
  void *v14;
  void *v15;
  s32 *Timer;
  s64 i;
  s32 v19;
  s32 v20;
  s64 v24;
  s64 v25;
  s64 v26;

  v8 = NewSpecific(rstAlphaTable_t, 3u);
  v9 = Allocate(rstAlphaTable_t);
  *(u64 *)&v9->Frame = 0x8000000000LL;
  if (!QueryInterface(v9, *(void **)(*v8 + 64)))
    goto LABEL_25;
  v8[4] = v9;
  v10 = Allocate(rstAlphaTable_t);
  *(u64 *)&v10->Frame = 0x4600000014LL;
  if (!QueryInterface(v10, *(void **)(*v8 + 64)))
    goto LABEL_25;
  v8[5] = v10;
  v11 = Allocate(rstAlphaTable_t);
  *(u64 *)&v11->Frame = 45;
  if (!QueryInterface(v11, *(void **)(*v8 + 64)))
    goto LABEL_25;
  v8[6] = v11;
  v12 = NewSpecific(rstPositionTable_t, 3u);
  v13 = Allocate(rstPositionTable_t);
  v13->Frame = 0;
  v26 = 0;
  _ctor((sdfIVector2_t)&v26, 0, 0, 0);
  *(u64 *)&v13->Position = v26;
  if (!QueryInterface(v13, *(void **)(*v12 + 64)))
    goto LABEL_25;
  v12[4] = v13;
  v14 = Allocate(rstPositionTable_t);
  v25 = 0;
  v14->Frame = 20;
  _ctor((sdfIVector2_t)&v25, 0, -10, 0);
  *(u64 *)&v14->Position = v25;
  if (!QueryInterface(v14, *(void **)(*v12 + 64)))
    goto LABEL_25;
  v12[5] = v14;
  v15 = Allocate(rstPositionTable_t);
  v24 = 0;
  v15->Frame = 45;
  _ctor((sdfIVector2_t)&v24, 0, -20, 0);
  *(u64 *)&v15->Position = v24;
  if (!QueryInterface(v15, *(void **)(*v12 + 64)))
  {
LABEL_25:
  }
  v12[6] = v15;
  Timer = pQue->Timer;
  for (i = 32; i != 64; i += 4)
  {
    v19 = *(u32 *)((char *)&Timer->obj.klass + i);
    if (!v19)
      continue;
    v20 = 45 - v19;
    rstCalcAlphaRate(v20, v8, *((u32 *)v8 + 6));
    rstCalcPosition(v20, v12, *((u32 *)v12 + 6), 0);
    Timer = pQue->Timer;
    --*(u32 *)((char *)&Timer->obj.klass + i);
  }
}

// 0x1e02ff0
void rstResultCyuuseiGauge(void *pData, s32 X, s32 Y, s32 AlphaRate, s32 Cyuusei, sprHandle_t *pSpr, ResultDrawType _type) {
  u32 *v21;
  int32x4_t v23;
  u32 *v24;
  u32 *v26;
  Il2CppObject *Instance;
  int32x4_t v29;

  if ((pData->Reward->lucktypef & 2) == 0)
  {
    goto LABEL_8;
  }
  if (pData->step >= 7)
  {
    v21 = NewSpecific(uint, 4u);
    v23 = vdupq_n_s32(0xA0966480);
    *(int32x4_t *)&v21[0] = v23;
    v29 = v23;
    v24 = NewSpecific(uint, 4u);
    *(int32x4_t *)&v24[0] = v29;
    v26 = NewSpecific(uint, 4u);
    *(int32x4_t *)&v26[0] = v29;
    goto LABEL_57;
  }
LABEL_8:
LABEL_57:
  Instance = _get_Instance();
  CyuuseiGaugeDrawUnity(Instance[6].monitor, Cyuusei, type, 0);
}

// 0x1e034d0
void rstResultAddCyuuseiMaxAnimQue(void *pQue) {
  s32 *Timer;
  s32 v3;
  s32 *m_Items;
  s32 v5;
  s32 v6;
  s32 *v7;
  s32 v8;
  s32 v9;
  s32 *v10;
  s32 v11;
  s32 v12;
  s32 *v13;
  s32 v14;
  s32 v15;
  s32 *v16;
  s32 v17;
  s32 v18;
  s32 *v19;
  s32 v20;
  s32 *v21;
  s32 *v22;

  Timer = pQue->Timer;
  v3 = Timer[1];
  m_Items = Timer;
  if (Timer[0])
  {
    v5 = 1;
    v6 = Timer[2];
    v7 = &Timer[1];
    if (v3)
      goto LABEL_3;
  }
  else
  {
    v5 = Timer[1];
    *m_Items = v3;
    v6 = Timer[2];
    v7 = &Timer[1];
    if (v3)
    {
LABEL_3:
      v8 = 1;
      v9 = Timer[3];
      v10 = &Timer[2];
      if (v6)
        goto LABEL_4;
      goto LABEL_21;
    }
  }
  v8 = v6;
  *v7 = v6;
  v9 = Timer[3];
  v10 = &Timer[2];
  if (v6)
  {
LABEL_4:
    v11 = 1;
    v12 = Timer[4];
    v13 = &Timer[3];
    if (v9)
      goto LABEL_5;
    goto LABEL_22;
  }
LABEL_21:
  v11 = v9;
  *v10 = v9;
  v12 = Timer[4];
  v13 = &Timer[3];
  if (v9)
  {
LABEL_5:
    v14 = 1;
    v15 = Timer[5];
    v16 = &Timer[4];
    if (v12)
      goto LABEL_6;
    goto LABEL_23;
  }
LABEL_22:
  v14 = v12;
  *v13 = v12;
  v15 = Timer[5];
  v16 = &Timer[4];
  if (v12)
  {
LABEL_6:
    v17 = 1;
    v18 = Timer[6];
    v19 = &Timer[5];
    if (v15)
      goto LABEL_7;
LABEL_24:
    v20 = v18;
    *v19 = v18;
    if (v18)
      goto LABEL_9;
    goto LABEL_8;
  }
LABEL_23:
  v17 = v15;
  *v16 = v15;
  v18 = Timer[6];
  v19 = &Timer[5];
  if (!v15)
    goto LABEL_24;
LABEL_7:
  v20 = 1;
  if (!v18)
  {
LABEL_8:
    v18 = Timer[7];
    Timer[6] = v18;
  }
LABEL_9:
  Timer[7] = 0;
  v21 = &Timer[7];
  if (v5)
  {
    m_Items = v7;
    if (v8)
    {
      m_Items = v10;
      if (v11)
      {
        m_Items = v13;
        if (v14)
        {
          m_Items = v16;
          if (v17)
          {
            m_Items = v19;
            if (v20)
            {
              v22 = &Timer[6];
              if (v18)
                m_Items = v21;
              else
                m_Items = v22;
            }
          }
        }
      }
    }
  }
  *m_Items = 50;
}

// 0x1e03610
s32 rstResultCyuuseiMaxAnim(s32 X, s32 Y, s32 AlphaRate, void *pQue, sprHandle_t *pSpr) {
  u64 *v6;
  void *v7;
  void *v8;
  void *v9;
  void *v10;
  u64 *v11;
  void *v12;
  void *v13;
  void *v14;
  s64 v15;
  void *v16;
  void *v17;
  s64 v18;
  s64 v20;
  s32 result;
  s32 *Timer;
  s32 v23;
  s32 v24;
  s32 v28;
  s64 v29;
  s64 v30;
  s64 v31;
  s32 v33;
  s32 v34;
  s64 v37;

  v6 = NewSpecific(rstAlphaTable_t, 4u);
  v7 = Allocate(rstAlphaTable_t);
  *(u64 *)&v7->Frame = 0;
  if (!QueryInterface(v7, *(void **)(*v6 + 64)))
    goto LABEL_53;
  v6[4] = v7;
  v8 = Allocate(rstAlphaTable_t);
  *(u64 *)&v8->Frame = 7;
  if (!QueryInterface(v8, *(void **)(*v6 + 64)))
    goto LABEL_53;
  v6[5] = v8;
  v9 = Allocate(rstAlphaTable_t);
  *(u64 *)&v9->Frame = 0x6E0000000ALL;
  if (!QueryInterface(v9, *(void **)(*v6 + 64)))
    goto LABEL_53;
  v6[6] = v9;
  v10 = Allocate(rstAlphaTable_t);
  *(u64 *)&v10->Frame = 0x6E00000032LL;
  if (!QueryInterface(v10, *(void **)(*v6 + 64)))
    goto LABEL_53;
  v6[7] = v10;
  v11 = NewSpecific(rstAlphaTable_t, 3u);
  v12 = Allocate(rstAlphaTable_t);
  *(u64 *)&v12->Frame = 0;
  if (!QueryInterface(v12, *(void **)(*v11 + 64)))
    goto LABEL_53;
  v11[4] = v12;
  v13 = Allocate(rstAlphaTable_t);
  *(u64 *)&v13->Frame = 0x800000000ALL;
  if (!QueryInterface(v13, *(void **)(*v11 + 64)))
    goto LABEL_53;
  v11[5] = v13;
  v14 = Allocate(rstAlphaTable_t);
  *(u64 *)&v14->Frame = 50;
  if (!QueryInterface(v14, *(void **)(*v11 + 64)))
    goto LABEL_53;
  v11[6] = v14;
  v15 = NewSpecific(rstScaleTable_t, 3u);
  v16 = Allocate(rstScaleTable_t);
  *(u32 *)&v16->Scale.y = 1056964608;
  *(u64 *)&v16->Frame = 0x3F33333300000000LL;
  if (!QueryInterface(v16, *(void **)(*(u64 *)v15 + 64)))
    goto LABEL_53;
  *(u64 *)(v15 + 32) = v16;
  v17 = Allocate(rstScaleTable_t);
  *(u32 *)&v17->Scale.y = 1067869798;
  *(u64 *)&v17->Frame = 0x3FCCCCCD0000000ALL;
  {
LABEL_53:
  }
  *(u64 *)(v15 + 48) = v18;
  v20 = 0;
  v37 = v15 + 40;
  result = (s32)(*(u32 *)(*(u64 *)((char *)v6 + (((v6[3] << 32) - 0x100000000LL) >> 29) + 32) + 20) << 8) >> 7;
  Timer = pQue->Timer;
  do
  {
    v23 = Timer[v20];
    if (!v23)
      goto LABEL_17;
    v24 = 50 - v23;
    rstCalcAlphaRate(50 - v23, v6, *((u32 *)v6 + 6));
    v28 = *(u32 *)(v15 + 24);
    v29 = v15;
    v30 = v37;
    v31 = (v28 - 1) & (u32)~((v28 - 1) >> 31);
    do
    {
      if (!v31)
        break;
      v33 = *(u32 *)(*(u64 *)(v30 - 8) + 16);
      v34 = *(u32 *)(*(u64 *)v30 + 16);
      v30 += 8;
      --v31;
    }
    while (v33 > v24 || v34 <= v24);
    v15 = v29;
    rstCalcAlphaRate(v24, v11, *((u32 *)v11 + 6));
    result = 0;
    Timer = pQue->Timer;
    --Timer[v20];
LABEL_17:
    ++v20;
  }
  while (v20 != 8);
  return result;
}

// 0x1e03c30
void rstResultPlayerLevel(s32 X, s32 Y, s32 AlphaRate, void *pData, sprHandle_t *pSpr) {
  void *v7;
  Il2CppObject *v10;
  char *v11;
  char *v14;
  s32 exp;
  s32 level;
  s32 v17;
  void *PlayerExp;
  s32 v19;
  s32 v20;
  s32 v21;
  s32 *v22;
  s32 v23;
  s32 v24;
  s32 v25;
  s32 v26;
  sprHandle_t *v27;
  Il2CppObject *Instance;
  sprHandle_t *v30;
  s8 data[4];

  v7 = NewSpecific(s32, 6u);
  InitializeArray_55364416(v7, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__94647FA6773A6521B9434F0561D44B3DC6673843C932EAAC722F86B905EF0F4F, 0);
  data[0] = pData->Player->para->level;
  v10 = Box(sbyte, data);
  v11 = Format("{0,2:d}", v10, 0);
  Concat_54766928(0, v11, 0);
  v14 = sdatDevilName(241, 0);
  exp = pData->PlayerMul->para->exp;
  level = pData->Player->para->level;
  v17 = datGetPlayerExp(level) << 8;
  PlayerExp = datGetPlayerExp(pData->Player->para->level + 1);
  rstResultExpGauge(PlayerExp, v19, v20, v21, exp, v17, (u32)PlayerExp << 8, v22, v30, 0);
  rstResultLevelUpAnim(v23, v24, v25, v26, pData->aLevelUpAnimQue[0], v27);
  Instance = _get_Instance();
  PlayerLevelDrawUnity(Instance[6].monitor, v14, pData->Player->para->level, 0);
}

// 0x1e03f50
void rstResultNakamaLevel(s32 X, s32 Y, s32 AlphaRate, void *pData, sprHandle_t *pSpr, s32 index, s32 IorO) {
  void *v12;
  sdatUnitWork_t *v13;
  s64 v16;
  Il2CppObject *v17;
  char *v18;
  s32 devilid;
  s32 exp;
  s32 level;
  s32 v22;
  s32 v23;
  s32 type;
  void *monitor;
  s32 v26;
  char *v27;
  bool v28;
  Il2CppObject *Instance;
  s32 v30;
  s32 v31;
  s32 v32;
  s32 *v33;
  s32 v35;
  s32 v36;
  s32 v37;
  sprHandle_t *v38;
  s32 v40;
  s32 v41;
  s32 v42;
  sprHandle_t *v43;
  void *v46;
  s32 v47;
  s32 v48;
  s32 v49;
  sprHandle_t *v50;
  sprHandle_t *v54;
  s8 data[4];

  v12 = NewSpecific(s32, 6u);
  InitializeArray_55364416(v12, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8AF81024F38CC2076915F728923CEB598968702CBECABB8D11F83973E7E081B3, 0);
  if (index < 0)
    return;
  if (!datGetStockDevilID(index))
    return;
  v13 = pData->Player->stock_id[index];
  v16 = index;
  data[0] = v13->level;
  v17 = Box(sbyte, data);
  v18 = Format("{0,2:d}", v17, 0);
  Concat_54766928(0, v18, 0);
  devilid = v13->devilid;
  exp = pData->PlayerMul->stock_id[index]->exp;
  level = pData->Player->stock_id[v16]->level;
  v22 = datGetDevilExp(devilid, level) << 8;
  v23 = datGetDevilExp(v13->devilid, pData->Player->stock_id[v16]->level + 1) << 8;
  if (Y)
    type = 2;
  else
    type = 1;
  monitor = _get_Instance()[6].monitor;
  v26 = v13->devilid;
  v27 = sdatDevilName(v26, 0);
  NakamaLevelDrawUnity(monitor, v27, v13->level, type, v13->devilid, 0);
  v28 = v13->DevilReportStok->_size > 0;
  Instance = _get_Instance();
  DrawHukidasi(Instance[6].monitor, type, v28, 0);
  rstResultExpGauge(rstResultDraw, v30, v31, v32, exp, v22, v23, v33, v54, type);
  rstResultCyuuseiGauge(pData, v35, v36, v37, v13->chuusei, v38, type);
  v46 = pData->aLevelUpAnimQue[IorO + 1];
  rstResultLevelUpAnim((s32)rstResultDraw, v40, v41, v42, v46, v43);
  if (rstResultCyuuseiMaxAnim(v47, v48, v49, pData->aCyuuseiMaxAnimQue[IorO], v50) < 1 || v13->chuusei != 100)
  {
    return;
  }
  goto LABEL_41;
LABEL_42:
  return;
LABEL_41:
  goto LABEL_42;
}

// 0x1e04410
void rstResultMoneyMagItem(s32 X, s32 Y, s32 AlphaRate, void *pData, sprHandle_t *pSpr) {
  void **v6;
  char *v10;
  Il2CppObject *v20;
  char *v21;
  char *v22;
  Il2CppObject *Instance;
  u8 v25;
  s64 v26;
  s32 iconType;
  Il2CppClass *klass;
  char *v29;
  u32 *v30;
  s32 step;
  s32 v32;
  s32 v33;
  s32 v34;
  void *v35;
  void *v36;
  s32 v37;
  int32x4_t *v38;
  void *v39;
  void *v40;
  void *v41;
  int32x4_t *v42;
  void *v43;
  char v44;
  void **v45;
  s32 v46;
  Il2CppObject *v47;
  char *v48;
  char *v49;
  char *v50;
  void *Reward;
  s32 v52;
  Il2CppObject *v54;
  void *v55;
  void *Item;
  void *v57;
  void *v58;
  void *v59;
  void *v60;
  void *v61;
  void *v62;
  void *v63;
  void *v64;
  void *v65;
  void *v66;
  void *v67;
  void *v68;
  void *v69;
  void *v70;
  void *v71;
  void *v72;
  void *v73;
  u32 v74;
  s32 ofst_y;
  s32 v76;
  u32 *v77;
  int32x4_t v79;
  u32 *v80;
  s32 rate_cnt;
  s32 v83;
  char *v84;
  Il2CppObject *v85;
  char *v86;
  s64 v87;
  int32x4_t v88;
  int32x4_t v89;
  s32 v90;
  s32 v91;
  s32 data;

  v6 = &rstResultDraw;
  v10 = &byte_5757000;
  if ((pData->Reward->lucktypef & 4) == 0)
  {
    goto LABEL_14;
  }
  if (pData->step >= 5)
  {
    v77 = NewSpecific(uint, 4u);
    v79 = vdupq_n_s32(0xA0966480);
    *(int32x4_t *)&v77[0] = v79;
    v89 = v79;
    v80 = NewSpecific(uint, 4u);
    *(int32x4_t *)&v80[0] = v89;
LABEL_23:
    goto LABEL_25;
  }
LABEL_14:
  goto LABEL_23;
LABEL_25:
  data = pData->Reward->drawmon;
  v20 = Box(s32, &data);
  v21 = Format("{0,7:d}", v20, 0);
  v22 = Concat_54766928(0, v21, 0);
  Instance = _get_Instance();
  MoneyDrawUnity(Instance[7].klass, pData->Reward->drawmon, 0);
  if ((pData->Reward->lucktypef & 4) == 0)
  v25 = 0;
  v26 = 4;
  v87 = 0;
  do
  {
    v30 = *((u32 **)&pData->Reward->Item->obj.klass + v26);
    if (!v30[4])
      goto LABEL_33;
    step = pData->step;
    v33 = v30[5];
    v32 = v30[6];
    if (step <= 2)
      v34 = 0;
    else
      v34 = v32;
    if (v32 < 1)
    {
      if (v33)
        v25 = 1;
    }
    else
    {
      LODWORD(v87) = v87 + 1;
      if (v33)
      {
        if (step < 3)
        {
          v25 = 1;
          goto LABEL_47;
        }
      }
      else if (step < 3)
      {
        v25 = 0;
        goto LABEL_47;
      }
      v25 = 2;
      HIDWORD(v87) = ((HIDWORD(v87) << 24) | (HIDWORD(v87) << 16) | (HIDWORD(v87) << 8)) - 1600756608;
    }
LABEL_47:
    if (*((u32 *)*v6 + 56))
    {
      if ((v10[3398] & 1) != 0)
        goto LABEL_49;
    }
    else
    {
      if ((v10[3398] & 1) != 0)
      {
LABEL_49:
        v35 = *v6;
        if (*((u32 *)*v6 + 56))
          goto LABEL_50;
        goto LABEL_54;
      }
    }
    v10[3398] = 1;
    v35 = *v6;
    if (*((u32 *)*v6 + 56))
    {
LABEL_50:
      if (*(s32 *)(*((u64 *)&pData->Reward->Item->obj.klass + v26) + 24) < 1)
        goto LABEL_57;
      goto LABEL_55;
    }
LABEL_54:
    if (*(s32 *)(*((u64 *)&pData->Reward->Item->obj.klass + v26) + 24) < 1)
      goto LABEL_57;
LABEL_55:
    if (!*((u32 *)*v6 + 56))
LABEL_57:
    v36 = *v6;
    v37 = *((u32 *)*v6 + 56);
    v88 = vdupq_n_s32(HIDWORD(v87));
    if (v25 > 1u)
    {
      v38 = NewSpecific(uint, 4u);
      if (*((u32 *)*v6 + 56))
      {
        if ((v10[3398] & 1) != 0)
          goto LABEL_63;
LABEL_94:
        v10[3398] = 1;
        v39 = *v6;
        if (!*((u32 *)*v6 + 56))
          goto LABEL_95;
      }
      else
      {
        if ((v10[3398] & 1) == 0)
          goto LABEL_94;
LABEL_63:
        v39 = *v6;
        if (!*((u32 *)*v6 + 56))
LABEL_95:
      }
      v38[2] = v88;
LABEL_71:
      v42 = NewSpecific(uint, 4u);
      if (*((u32 *)*v6 + 56))
      {
        if ((v10[3398] & 1) != 0)
          goto LABEL_76;
LABEL_81:
        v10[3398] = 1;
        v43 = *v6;
        if (!*((u32 *)*v6 + 56))
          goto LABEL_82;
LABEL_77:
        v42[2] = v88;
      }
      else
      {
        if ((v10[3398] & 1) == 0)
          goto LABEL_81;
LABEL_76:
        v43 = *v6;
        if (*((u32 *)*v6 + 56))
          goto LABEL_77;
LABEL_82:
        v44 = v10[3398];
        v42[2] = v88;
        if ((v44 & 1) == 0)
        {
          v10[3398] = 1;
        }
      }
      v45 = v6;
      if (!*((u32 *)*v6 + 56))
      v46 = v33 + v34;
      v91 = v33 + v34;
      v47 = Box(s32, &v91);
      v48 = Format("{0}", v47, 0);
      v49 = Concat_54766928(v22, v48, 0);
      v50 = v10;
      iconType = tbldata[*(s32 *)(*((u64 *)&pData->Reward->Item->obj.klass + v26) + 16)]->iconType;
      klass = _get_Instance()[7].klass;
      v29 = sdatItemName(*(u32 *)(*((u64 *)&pData->Reward->Item->obj.klass + v26) + 16));
      ItemDrawUnity(klass, v29, v46, v26 - 4, iconType, 0);
      v10 = v50;
      v22 = v49;
      v6 = v45;
      goto LABEL_33;
    }
    if (v37)
    {
      goto LABEL_67;
    }
    else
    {
LABEL_67:
      v40 = *v6;
      if (*((u32 *)*v6 + 56))
        goto LABEL_68;
      goto LABEL_98;
    }
    v40 = *v6;
    if (*((u32 *)*v6 + 56))
    {
LABEL_68:
      if ((v10[3398] & 1) != 0)
        goto LABEL_69;
      goto LABEL_99;
    }
LABEL_98:
    if ((v10[3398] & 1) != 0)
    {
LABEL_69:
      v41 = *v6;
      if (!*((u32 *)*v6 + 56))
        goto LABEL_100;
      goto LABEL_70;
    }
LABEL_99:
    v10[3398] = 1;
    v41 = *v6;
    if (!*((u32 *)*v6 + 56))
    {
LABEL_100:
      if (v25)
        goto LABEL_71;
      goto LABEL_101;
    }
LABEL_70:
    if (v25)
      goto LABEL_71;
LABEL_101:
    v25 = 0;
LABEL_33:
    ++v26;
  }
  while (v26 != 12);
  Reward = pData->Reward;
  if (Reward->Item[0]->ID)
  {
    v52 = v87;
    if ((Reward->lucktypef & 4) == 0)
      goto LABEL_133;
LABEL_128:
    if (pData->step >= 1)
    {
      if (*((u32 *)*v6 + 56))
      {
        if ((v10[3398] & 1) != 0)
          goto LABEL_131;
LABEL_239:
        v10[3398] = 1;
        v55 = *v6;
        if (!*((u32 *)*v6 + 56))
          goto LABEL_240;
      }
      else
      {
        if ((v10[3398] & 1) == 0)
          goto LABEL_239;
LABEL_131:
        v55 = *v6;
        if (!*((u32 *)*v6 + 56))
LABEL_240:
      }
      Reward = pData->Reward;
    }
  }
  else
  {
    v54 = _get_Instance();
    ItemNoneDraw(v54[7].klass, 0);
    Reward = pData->Reward;
    v52 = v87;
    if ((Reward->lucktypef & 4) != 0)
      goto LABEL_128;
  }
LABEL_133:
  Item = Reward->Item;
  v57 = Item[0];
  if (v57->ID && v57->kounfuun)
  {
    if (*((u32 *)*v6 + 56))
    {
      if ((v10[3398] & 1) != 0)
        goto LABEL_137;
LABEL_214:
      v10[3398] = 1;
      v58 = *v6;
      if (!*((u32 *)*v6 + 56))
        goto LABEL_215;
    }
    else
    {
      if ((v10[3398] & 1) == 0)
        goto LABEL_214;
LABEL_137:
      v58 = *v6;
      if (!*((u32 *)*v6 + 56))
LABEL_215:
    }
    Item = pData->Reward->Item;
  }
  v59 = Item[1];
  if (v59->ID && v59->kounfuun)
  {
    if (*((u32 *)*v6 + 56))
    {
      if ((v10[3398] & 1) != 0)
        goto LABEL_143;
LABEL_217:
      v10[3398] = 1;
      v60 = *v6;
      if (!*((u32 *)*v6 + 56))
        goto LABEL_218;
    }
    else
    {
      if ((v10[3398] & 1) == 0)
        goto LABEL_217;
LABEL_143:
      v60 = *v6;
      if (!*((u32 *)*v6 + 56))
LABEL_218:
    }
    Item = pData->Reward->Item;
  }
  v61 = Item[2];
  if (v61->ID && v61->kounfuun)
  {
    if (*((u32 *)*v6 + 56))
    {
      if ((v10[3398] & 1) != 0)
        goto LABEL_149;
LABEL_220:
      v10[3398] = 1;
      v62 = *v6;
      if (!*((u32 *)*v6 + 56))
        goto LABEL_221;
    }
    else
    {
      if ((v10[3398] & 1) == 0)
        goto LABEL_220;
LABEL_149:
      v62 = *v6;
      if (!*((u32 *)*v6 + 56))
LABEL_221:
    }
    Item = pData->Reward->Item;
  }
  v63 = Item[3];
  if (v63->ID && v63->kounfuun)
  {
    if (*((u32 *)*v6 + 56))
    {
      if ((v10[3398] & 1) != 0)
        goto LABEL_155;
LABEL_223:
      v10[3398] = 1;
      v64 = *v6;
      if (!*((u32 *)*v6 + 56))
        goto LABEL_224;
    }
    else
    {
      if ((v10[3398] & 1) == 0)
        goto LABEL_223;
LABEL_155:
      v64 = *v6;
      if (!*((u32 *)*v6 + 56))
LABEL_224:
    }
    Item = pData->Reward->Item;
  }
  v65 = Item[4];
  if (v65->ID && v65->kounfuun)
  {
    if (*((u32 *)*v6 + 56))
    {
      if ((v10[3398] & 1) != 0)
        goto LABEL_161;
LABEL_226:
      v10[3398] = 1;
      v66 = *v6;
      if (!*((u32 *)*v6 + 56))
        goto LABEL_227;
    }
    else
    {
      if ((v10[3398] & 1) == 0)
        goto LABEL_226;
LABEL_161:
      v66 = *v6;
      if (!*((u32 *)*v6 + 56))
LABEL_227:
    }
    Item = pData->Reward->Item;
  }
  v67 = Item[5];
  if (v67->ID && v67->kounfuun)
  {
    if (*((u32 *)*v6 + 56))
    {
      if ((v10[3398] & 1) != 0)
        goto LABEL_167;
LABEL_229:
      v10[3398] = 1;
      v68 = *v6;
      if (!*((u32 *)*v6 + 56))
        goto LABEL_230;
    }
    else
    {
      if ((v10[3398] & 1) == 0)
        goto LABEL_229;
LABEL_167:
      v68 = *v6;
      if (!*((u32 *)*v6 + 56))
LABEL_230:
    }
    Item = pData->Reward->Item;
  }
  v69 = Item[6];
  if (v69->ID && v69->kounfuun)
  {
    if (*((u32 *)*v6 + 56))
    {
      if ((v10[3398] & 1) != 0)
        goto LABEL_173;
LABEL_232:
      v10[3398] = 1;
      v70 = *v6;
      if (!*((u32 *)*v6 + 56))
        goto LABEL_233;
    }
    else
    {
      if ((v10[3398] & 1) == 0)
        goto LABEL_232;
LABEL_173:
      v70 = *v6;
      if (!*((u32 *)*v6 + 56))
LABEL_233:
    }
    Item = pData->Reward->Item;
  }
  v71 = Item[7];
  if (!v71->ID || !v71->kounfuun)
    goto LABEL_180;
  if (*((u32 *)*v6 + 56))
  {
    if ((v10[3398] & 1) != 0)
      goto LABEL_179;
LABEL_235:
    v10[3398] = 1;
    v72 = *v6;
    if (!*((u32 *)*v6 + 56))
      goto LABEL_236;
LABEL_180:
    v73 = pData->HankoWork[2];
    v74 = v73->step;
    if (!v74)
      goto LABEL_181;
  }
  else
  {
    if ((v10[3398] & 1) == 0)
      goto LABEL_235;
LABEL_179:
    v72 = *v6;
    if (*((u32 *)*v6 + 56))
      goto LABEL_180;
LABEL_236:
    v73 = pData->HankoWork[2];
    v74 = v73->step;
    if (!v74)
    {
LABEL_181:
      v73->rate_cnt = 0;
      *(u64 *)&v73->ofst_y = 0xFFFFFFFD00000001LL;
    }
  }
  if (v52 && pData->step >= 4)
  {
    ofst_y = v73->ofst_y;
    if (v74 >= 4)
    {
      ofst_y += 3 * v73->rate;
      v73->ofst_y = ofst_y;
    }
    if (ofst_y < -50)
    {
      v76 = 1;
LABEL_207:
      v73->rate = v76;
    }
    else if (ofst_y >= 3)
    {
      v76 = -3;
      goto LABEL_207;
    }
    rate_cnt = v73->rate_cnt;
    if (rate_cnt + 1 < 1000000)
      v83 = rate_cnt + 1;
    else
      v83 = 0;
    v73->rate_cnt = v83;
    v90 = v52;
    v84 = Concat_54766928(v22, "+", 0);
    v85 = Box(uint, &v90);
    v86 = Format("{0,2:d}", v85, 0);
    Concat_54766928(v84, v86, 0);
  }
}

// 0x1e05400
void rstResultResultDraw(void *pData) {
  u32 v2;
  void *pBG;
  s32 v6;
  s32 v7;
  s32 v8;
  s32 v9;
  sprHandle_t *v10;
  void *Reward;
  s32 drawexp;
  s32 drawchu;
  s32 v15;
  s32 v16;
  sprHandle_t *v17;
  s32 StockIndex0;
  s32 v22;
  s32 v23;
  sprHandle_t *v24;
  s32 v26;
  s32 v27;
  s32 v28;
  sprHandle_t *v29;
  Il2CppObject *Instance;

  pBG = pData->pBG;
  BG(pBG, (s32)v2);
  v6 = -1;
  do
  {
    ++v6;
  }
  while (v6 < datGetStockDevilNums(0));
  Reward = pData->Reward;
  drawexp = Reward->drawexp;
  drawchu = Reward->drawchu;
  rstResultGetExpCyuusei(pData, v7, v8, v9, drawexp, drawchu, v10);
  if ((pData->Flag & 0x80000) != 0)
  {
    StockIndex0 = pData->Reward->StockIndex0;
    goto LABEL_12;
  }
  rstResultPlayerLevel((s32)rstResultDraw, v15, v16, pData, v17);
  StockIndex0 = pData->Reward->StockIndex0;
LABEL_12:
  rstResultNakamaLevel((s32)rstResultDraw, 0, v16, pData, v17, StockIndex0, 0);
  rstResultNakamaLevel(v22, 100, v23, pData, v24, pData->Reward->StockIndex1, 1);
  rstResultMoneyMagItem(v26, v27, v28, pData, v29);
  Instance = _get_Instance();
  ResultAnimIn(Instance, 0);
}

// 0x1e053f0
void rstResultDrawStar(void *pData, s32 x, s32 y, u8 mode) {
  ;
}
