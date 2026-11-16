#include "types.h"
#include "dds3kerneldraw.h"
#include "jmsdraw.h"
#include "mdl.h"
#include "sbtlsub.h"

typedef struct jmsCyousaPanel_t jmsCyousaPanel_t;
typedef struct jmsData_t jmsData_t;
typedef struct jmsModelCursor_t jmsModelCursor_t;
typedef struct sdfIVector2_t sdfIVector2_t;
typedef struct sprHandle_t sprHandle_t;

f32 offsetCharaIcon[7];
static void *jmsSprTable01;
static void *jmsSprTable02;
static void *jmsSprTable03;
static void *jmsSprTable04;
static void *jmsSprTable05;
static void *jmsSprTableRoot;

static void DrawGetSpritePos(s32 TableNo, s32 PartsNo, s32 pX, s32 pY);
static void DrawSpritePartsEx(s32 TableNo, s32 PartsNo, s32 OfsX, s32 OfsY, s32 AlphaRate, const sdfVector2_t *Scale, sprHandle_t *pSpr, u32 OtNo);
static void DrawSpriteParts(s32 TableNo, s32 PartsNo, s32 AlphaRate, sprHandle_t *pSpr, u32 OtNo);
static void DrawSprite(s32 TableNo, f32 AlphaRate, sprHandle_t *pSpr, u32 OtNo);
static s32 CheckNumArea(s32 Val, s32 Min, s32 Max);
static s32 CalcAlphaRate(s32 *NowFrame, void *pTable, s32 TableNums);
static void CalcScale(s32 NowFrame, void *pTable, s32 TableNums, sdfVector2_t *Scale);
static void DrawCyousaPanelCursor(jmsCyousaPanel_t *pPanel, sprHandle_t *pSpr);
static void DrawModelCursor(sdfIVector2_t CursorPos, jmsModelCursor_t *pCursor, sprHandle_t *pSpr);

// 0x1cf0cf0
static void DrawGetSpritePos(s32 TableNo, s32 PartsNo, s32 pX, s32 pY) {

}

// 0x1cf0d50
static void DrawSpritePartsEx(s32 TableNo, s32 PartsNo, s32 OfsX, s32 OfsY, s32 AlphaRate, const sdfVector2_t *Scale, sprHandle_t *pSpr, u32 OtNo) {
  return;
}

// 0x1cf0e00
static void DrawSpriteParts(s32 TableNo, s32 PartsNo, s32 AlphaRate, sprHandle_t *pSpr, u32 OtNo) {
  return;
}

// 0x1cf0f00
static void DrawSprite(s32 TableNo, f32 AlphaRate, sprHandle_t *pSpr, u32 OtNo) {
  s32 v7;

  v7 = -1;
  do
  {
    ++v7;
  }
  while (v7 < jmsSprTableRoot[TableNo]->Nums);
}

// 0x1cf0fa0
static s32 CheckNumArea(s32 Val, s32 Min, s32 Max) {
  return Val >= Min && Val < Max;
}

// 0x1cf0fb0
static s32 CalcAlphaRate(s32 *NowFrame, void *pTable, s32 TableNums) {
  s64 v7;
  s64 v8;
  s32 v10;
  Il2CppClass **v11;
  s32 name;
  s32 v13;
  void *v14;

  v7 = (TableNums - 1) & (u32)~((TableNums - 1) >> 31);
  v8 = 0;
  while (1)
  {
    v10 = *NowFrame;
    if (v7 == v8)
      break;
    v11 = &pTable->obj.klass + v8;
    name = v11[4]->_1.name;
    v13 = v11[5]->_1.name;
    ++v8;
    if (v10 >= name && v10 < v13)
    {
      v10 = *NowFrame;
      v7 = v8 - 1;
      break;
    }
  }
  v14 = pTable[v7];
  *NowFrame = v10 - v14->Frame;
  LODWORD(v14) = (u64)(2155905153LL * (v14->Alpha << 8)) >> 32;
  return ((s32)v14 >> 7) + ((u32)v14 >> 31);
}

// 0x1cf10b0
static void CalcScale(s32 NowFrame, void *pTable, s32 TableNums, sdfVector2_t *Scale) {
  s64 v9;
  void *v10;
  s64 v11;
  s32 Frame;
  s32 v14;
  void *v15;
  s32 v16;
  void *v17;
  f32 v18;

  v9 = (TableNums - 1) & (u32)~((TableNums - 1) >> 31);
  v10 = &pTable[1];
  v11 = 1;
  while (v9 + v11 != 1)
  {
    Frame = (*(v10 - 1))->Frame;
    v14 = v10->Frame;
    --v11;
    ++v10;
    if (Frame <= NowFrame && v14 > NowFrame)
    {
      v9 = -v11;
      break;
    }
  }
  v15 = pTable[v9];
  v16 = v15->Frame;
  v17 = pTable[(s32)v9 + 1];
  v18 = (v17->Frame - v16);
  Scale->x = v15->Scale.x
                  + (f32)((f32)((f32)(v17->Scale.x - v15->Scale.x) * (f32)(NowFrame - v16)) / v18);
  Scale->y = v15->Scale.y
                  + (f32)((f32)((f32)(v17->Scale.y - v15->Scale.y) * (f32)(NowFrame - v16)) / v18);
}

// 0x1cf11f0
static void DrawCyousaPanelCursor(jmsCyousaPanel_t *pPanel, sprHandle_t *pSpr) {
  void *v4;
  void *v5;
  void *v6;
  s64 v7;
  s32 v8;
  s64 v9;
  s64 v10;
  s32 CursorTimer;
  s64 v13;
  s32 v14;
  s32 v15;
  s32 v16;
  s32 v17;

  v4 = NewSpecific(jmsAlphaTable_t, 3u);
  v5 = Allocate(jmsAlphaTable_t);
  *(u64 *)&v5->Frame = 0x1400000000LL;
  if (!QueryInterface(v5, *(void **)(*(u64 *)v4 + 64)))
    goto LABEL_24;
  v4[0] = v5;
  v6 = Allocate(jmsAlphaTable_t);
  *(u64 *)&v6->Frame = 0xA000000032LL;
  {
LABEL_24:
  }
  v4[2] = v7;
  v8 = *(u32 *)((char *)v4 + 24);
  v9 = 0;
  v10 = (v8 - 1) & (u32)~((v8 - 1) >> 31);
  while (1)
  {
    CursorTimer = pPanel->CursorTimer;
    if (v10 == v9)
      break;
    v13 = (s64)(char *)v4 + 8 * v9;
    v14 = *(u32 *)(*(u64 *)(v13 + 32) + 16);
    v15 = *(u32 *)(*(u64 *)(v13 + 40) + 16);
    ++v9;
    if (CursorTimer >= v14 && CursorTimer < v15)
    {
      CursorTimer = pPanel->CursorTimer;
      v10 = v9 - 1;
      break;
    }
  }
  v16 = CursorTimer - *(u32 *)((u64)v4[v10] + 16);
  if (v16 + 1 <= 100)
    v17 = v16 + 1;
  else
    v17 = 0;
  pPanel->CursorTimer = v17;
}

// 0x1ce57b0
void DrawCyousaPanel(jmsCyousaPanel_t *pPanel, sprHandle_t *pSpr) {
  s32 v6;

  goto LABEL_9;
  do
  {
    ++v6;
  }
  while (v6 < jmsSprTableRoot[0]->Nums);
LABEL_9:
  DrawCyousaPanelCursor(pPanel, pSpr);
}

// 0x1ce0440
void DrawBtnIcon(s32 Type, s32 AlphaRate, sprHandle_t *pSpr) {
  s32 v10;
  s32 v11;

  if (Type != 1)
  {
    if (Type)
      return;
    return;
    do
    {
      ++v10;
    }
    while (v10 < jmsSprTableRoot[2]->Nums);
    return;
  }
  return;
  do
  {
    ++v11;
  }
  while (v11 < jmsSprTableRoot[3]->Nums);
}

// 0x1cf1430
static void DrawModelCursor(sdfIVector2_t CursorPos, jmsModelCursor_t *pCursor, sprHandle_t *pSpr) {
  s64 v5;
  void *v6;
  void *v7;
  u64 *v8;
  void *v9;
  s64 v10;
  s32 Timer;
  s32 v18;
  s64 v19;
  s64 v20;
  s64 v22;
  s32 v23;
  s32 v24;
  s64 v25;
  s32 v26;
  s32 v27;
  s32 v28;
  s64 v29;
  u64 *v30;
  s32 v32;
  s32 v33;
  s32 v34;
  s32 Fade;
  jmsModelCursor_t *v37;
  s32 AlphaRate;
  s32 v41;
  s32 v43;
  s32 Item;
  sdfIVector2_t v45;

  v45 = CursorPos;
  v5 = NewSpecific(jmsAlphaTable_t, 2u);
  v6 = Allocate(jmsAlphaTable_t);
  *(u64 *)&v6->Frame = 0xA000000000LL;
  if (!QueryInterface(v6, *(void **)(*(u64 *)v5 + 64)))
    goto LABEL_87;
  *(u64 *)(v5 + 32) = v6;
  v7 = Allocate(jmsAlphaTable_t);
  *(u64 *)&v7->Frame = (char *)&xmmword_38 + 4;
  if (!QueryInterface(v7, *(void **)(*(u64 *)v5 + 64)))
    goto LABEL_87;
  *(u64 *)(v5 + 40) = v7;
  v8 = NewSpecific(jmsScaleTable_t, 2u);
  v9 = Allocate(jmsScaleTable_t);
  *(u32 *)&v9->Scale.y = 1065353216;
  *(u64 *)&v9->Frame = 0x3F80000000000000LL;
  {
LABEL_87:
  }
  v8[5] = v10;
  Item = get_Item((sdfIVector2_t)&v45, 0, 0);
  v43 = get_Item((sdfIVector2_t)&v45, 1, 0);
  Timer = pCursor->Timer;
  v18 = *(u32 *)(v5 + 24);
  v19 = 0;
  v20 = (v18 - 1) & (u32)~((v18 - 1) >> 31);
  while (v20 != v19)
  {
    v22 = v5 + 8 * v19;
    v23 = *(u32 *)(*(u64 *)(v22 + 32) + 16);
    v24 = *(u32 *)(*(u64 *)(v22 + 40) + 16);
    ++v19;
    if (Timer >= v23 && Timer < v24)
    {
      v20 = v19 - 1;
      break;
    }
  }
  v25 = v5 + 8 * v20;
  v26 = *(u32 *)(v5 + 24);
  v27 = *(u32 *)(*(u64 *)(v25 + 32) + 16);
  v28 = Timer - v27;
  v29 = (v26 - 1) & (u32)~((v26 - 1) >> 31);
  v30 = v8 + 5;
  do
  {
    if (!v29)
      break;
    v32 = *(u32 *)(*(v30 - 1) + 16);
    v33 = *(u32 *)(*v30 + 16);
    ++v30;
    --v29;
  }
  while (v32 > v28 || v33 <= v28);
  v34 = *(u32 *)(*(u64 *)(v5 + (((*(u64 *)(v5 + 24) << 32) - 0x100000000LL) >> 29) + 32) + 16);
  Fade = pCursor->Fade;
  v37 = pCursor;
  if (!!op_Inequality(jmsUIctrlSub, 0, 0))
  {
    SetSelIcon(jmsUIctrlSub, (f32)Item, (f32)v43, 0);
    AlphaRate = v37->AlphaRate;
    if (v37->Fade)
      goto LABEL_50;
    goto LABEL_76;
  }
  AlphaRate = v37->AlphaRate;
  if (v37->Fade)
  {
LABEL_50:
    if (AlphaRate >= 256)
    {
      if (AlphaRate <= 256)
        goto LABEL_81;
    }
    else
    {
      AlphaRate += 12;
    }
    if (AlphaRate >= 256)
      AlphaRate = 256;
    goto LABEL_80;
  }
LABEL_76:
  if (AlphaRate <= 0)
  {
    if ((AlphaRate & 0x80000000) == 0)
      goto LABEL_81;
  }
  else
  {
    AlphaRate -= 12;
  }
  AlphaRate &= ~(AlphaRate >> 31);
LABEL_80:
  v37->AlphaRate = AlphaRate;
LABEL_81:
  if (Fade)
    v41 = 0;
  else
    v41 = v34;
  if (v28 < v34)
    v41 = v28 + 1;
  v37->Timer = v41;
}

// 0x1ce0690
void DrawModel(jmsData_t *pData, s32 CursorIndex) {
  jmsData_t *v5;
  s64 i;
  dds3ModelHandle_t *v7;
  sdfModelOt_t *v9;
  void *jmsModel;
  f32 v11;
  f32 *Pos;
  f32 v14;
  s64 v15;
  f32 v16;
  f32 v17;
  jmsData_t *v18;
  s32 x;
  s32 y;
  sprHandle_t *v21;
  jmsData_t *v23;
  jmsModelCursor_t *ModelCursor;
  sdfIVector2_t v25;
  sdfIVector2_t CursorPos;
  sdfVector4_t ppos;

  v5 = pData;
  CursorPos = 0;
  if (v5->ModelLoadCnt >= 1)
  {
    for (i = 0; i < v5->ModelLoadCnt; ++i)
    {
      v7 = v5->Model[i];
      if (!v7)
        continue;
      v9 = ModelOt[0];
      Link(v7, v9);
      v5 = pData;
    }
  }
  jmsModel = v5->jmsModel;
  *(u64 *)&ppos.x = 0;
  *(u64 *)&ppos.z = 0;
  v11 = GetTbl(jmsModel, v5->ModelIndex[v5->ModelCursor->SelIndex], 0)->Pos[0];
  Pos = GetTbl(pData->jmsModel, pData->ModelIndex[pData->ModelCursor->SelIndex], 0)->Pos;
  v14 = Pos[1];
  v15 = pData->ModelIndex[pData->ModelCursor->SelIndex];
  v16 = offsetCharaIcon[v15];
  v17 = GetTbl(pData->jmsModel, v15, 0)->Pos[2];
  sBtlChangeWorldtoScreenUnity3(v11, v14 - v16, v17, &ppos);
  if ((CursorIndex & 0x80000000) == 0)
  {
    v18 = pData;
    pData->ModelCursor->SelIndex = CursorIndex;
    if (v18->ModelLoadCnt >= 2)
    {
      CursorPos = 0;
      if (ppos.x == INFINITY)
        x = 0x80000000;
      else
        x = ppos.x;
      set_Item((sdfIVector2_t)&CursorPos, 0, x, 0);
      if (ppos.y == INFINITY)
        y = 0x80000000;
      else
        y = ppos.y;
      set_Item((sdfIVector2_t)&CursorPos, 1, y, 0);
      v23 = pData;
      ModelCursor = pData->ModelCursor;
      if (v23->ModelIndex[ModelCursor->SelIndex])
      {
        v25 = CursorPos;
        DrawModelCursor(v25, ModelCursor, v21);
      }
      else
      {
        if (op_Inequality(jmsUIctrlSub, 0, 0))
          SetSelIconSp(jmsUIctrlSub, 0);
      }
    }
  }
}

// 0x1ce6650
void DrawModel_M(jmsData_t *pData, s32 CursorIndex) {
  jmsData_t *v4;
  s64 i;
  dds3ModelHandle_t *v6;
  sdfModelOt_t *v8;

  v4 = pData;
  if (pData->ModelLoadCnt >= 1)
  {
    for (i = 0; i < v4->ModelLoadCnt; ++i)
    {
      v6 = v4->Model[i];
      if (!v6)
        continue;
      v8 = ModelOt[0];
      Link(v6, v8);
      v4 = pData;
    }
  }
}
