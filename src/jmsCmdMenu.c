#include "types.h"
#include "jmscmdmenu.h"

bool mouseNoScroll;

// 0x1c97f60
void *CmdListItemMoveNextEx(void *pCmdList, s32 Mode, s32 BlurMode) {
  void *pCurrent;
  void *p_pCurrent;
  s32 ItemCnt;
  s32 Flag;
  void *pNext;
  s32 v14;
  s32 v15;
  void *pTail;
  void *pHead;
  void *v18;
  void *pListTop;
  u32 v20;
  s32 DrawItemMax;
  s32 v22;
  void *v23;
  u32 v24;
  s32 v25;
  void *pCmdLista;

  pCmdLista = pCmdList;
  p_pCurrent = &pCmdList->pCurrent;
  pCurrent = pCmdList->pCurrent;
  ItemCnt = pCmdList->ItemCnt;
  Flag = pCmdList->Flag;
  if (ItemCnt > 1)
  {
    if ((Flag & 2) == 0)
      goto LABEL_4;
LABEL_9:
    pCmdList->Flag = Flag & 0xFFFFFFFE;
    return 0;
  }
  Flag |= 2u;
  pCmdList->Flag = Flag;
  if ((Flag & 2) != 0)
    goto LABEL_9;
LABEL_4:
  if (ItemCnt == 1)
    return pCurrent;
  if (pCurrent == pCmdList->pTail)
  {
    if (ItemCnt >= 1)
    {
      pHead = pCmdList->pHead;
      pCmdList->pListTop = pHead;
      v18 = pCmdList->pHead;
      pCmdList->pCurrent = v18;
      pCmdList->ItemOfs = 0;
    }
    pListTop = pCmdList->pListTop;
    if (pListTop)
    {
      v20 = pCmdList->Stat & 0xFFFFFFFE | (pListTop->pPrev != 0);
      DrawItemMax = pCmdList->DrawItemMax;
      if (DrawItemMax < 1)
      {
LABEL_25:
        v22 = v20 | 2;
      }
      else
      {
        while (1)
        {
          pListTop = pListTop->pNext;
          if (!pListTop)
            break;
          if (!--DrawItemMax)
            goto LABEL_25;
        }
        v22 = v20 & 0xFFFFFFFD;
      }
      pNext = p_pCurrent;
      goto LABEL_41;
    }
    pNext = p_pCurrent;
LABEL_38:
    pCmdList->Stat = 0;
    return pNext;
  }
  if (!pCurrent)
    return 0;
  pNext = pCurrent->pNext;
  if (!pNext)
    return pNext;
  if (!BlurMode)
    pCurrent->Timer = 256;
  pCmdList->pCurrent = pNext;
  v14 = pCmdList->ItemOfs + 1;
  v15 = pCmdList->DrawItemMax;
  pCmdList->ItemOfs = v14;
  if (v14 < v15)
  {
    pTail = pCmdList->pTail;
    if (pNext != pTail)
      goto LABEL_17;
LABEL_30:
    pCmdList->Flag |= 3u;
    if (pNext->pNext != pTail)
      goto LABEL_33;
    goto LABEL_31;
  }
  if (Mode)
  {
    mouseNoScroll = 0;
    pTail = pCmdList->pTail;
    if (pNext == pTail)
      goto LABEL_30;
  }
  else
  {
    pNext = CmdListMoveUp(pCmdLista);
    pTail = pCmdList->pTail;
    if (pNext == pTail)
      goto LABEL_30;
  }
LABEL_17:
  if (pNext->pNext != pTail)
    goto LABEL_33;
LABEL_31:
  if ((pTail->Flag & 2) != 0)
    pCmdList->Flag |= 3u;
LABEL_33:
  v23 = pCmdList->pListTop;
  if (!v23)
    goto LABEL_38;
  v24 = pCmdList->Stat & 0xFFFFFFFE | (v23->pPrev != 0);
  v25 = pCmdList->DrawItemMax;
  if (v25 < 1)
  {
LABEL_37:
    v22 = v24 | 2;
  }
  else
  {
    while (1)
    {
      v23 = v23->pNext;
      if (!v23)
        break;
      if (!--v25)
        goto LABEL_37;
    }
    v22 = v24 & 0xFFFFFFFD;
  }
LABEL_41:
  pCmdList->Stat = v22;
  return pNext;
}

// 0x1c98330
void *CmdListItemMovePrevEx(void *pCmdList, s32 Mode, s32 BlurMode) {
  void *pCurrent;
  void *p_pCurrent;
  s32 ItemCnt;
  s32 Flag;
  void *pPrev;
  s32 v14;
  void *pHead;
  void *pListTop;
  u32 v17;
  s32 DrawItemMax;
  s32 v19;
  void *pNext;
  u32 v21;
  s32 v22;
  void *pCmdLista;

  pCmdLista = pCmdList;
  p_pCurrent = &pCmdList->pCurrent;
  pCurrent = pCmdList->pCurrent;
  ItemCnt = pCmdList->ItemCnt;
  Flag = pCmdList->Flag;
  if (ItemCnt > 1)
  {
    if ((Flag & 2) == 0)
      goto LABEL_4;
LABEL_9:
    pCmdList->Flag = Flag & 0xFFFFFFFE;
    return 0;
  }
  Flag |= 2u;
  pCmdList->Flag = Flag;
  if ((Flag & 2) != 0)
    goto LABEL_9;
LABEL_4:
  if (ItemCnt == 1)
    return pCurrent;
  if (pCurrent == pCmdList->pHead)
  {
    CmdListItemMoveIndex(ItemCnt - 1, pCmdLista);
    pListTop = pCmdList->pListTop;
    if (pListTop)
    {
      v17 = pCmdList->Stat & 0xFFFFFFFE | (pListTop->pPrev != 0);
      DrawItemMax = pCmdList->DrawItemMax;
      if (DrawItemMax < 1)
      {
LABEL_23:
        v19 = v17 | 2;
      }
      else
      {
        while (1)
        {
          pListTop = pListTop->pNext;
          if (!pListTop)
            break;
          if (!--DrawItemMax)
            goto LABEL_23;
        }
        v19 = v17 & 0xFFFFFFFD;
      }
      pPrev = p_pCurrent;
      goto LABEL_39;
    }
    pPrev = p_pCurrent;
LABEL_36:
    pCmdList->Stat = 0;
    return pPrev;
  }
  if (!pCurrent)
    return 0;
  pPrev = pCurrent->pPrev;
  if (!pPrev)
    return pPrev;
  if (!BlurMode)
    pCurrent->Timer = 256;
  pCmdList->pCurrent = pPrev;
  v14 = pCmdList->ItemOfs - 1;
  pCmdList->ItemOfs = v14;
  if (v14 >= 0)
  {
    pHead = pCmdList->pHead;
    if (pPrev != pHead)
      goto LABEL_17;
LABEL_28:
    pCmdList->Flag |= 3u;
    if (pPrev->pPrev != pHead)
      goto LABEL_31;
    goto LABEL_29;
  }
  if (Mode)
  {
    mouseNoScroll = 0;
    pHead = pCmdList->pHead;
    if (pPrev == pHead)
      goto LABEL_28;
  }
  else
  {
    pPrev = CmdListMoveDown(pCmdLista);
    pHead = pCmdList->pHead;
    if (pPrev == pHead)
      goto LABEL_28;
  }
LABEL_17:
  if (pPrev->pPrev != pHead)
    goto LABEL_31;
LABEL_29:
  if ((pHead->Flag & 2) != 0)
    pCmdList->Flag |= 3u;
LABEL_31:
  pNext = pCmdList->pListTop;
  if (!pNext)
    goto LABEL_36;
  v21 = pCmdList->Stat & 0xFFFFFFFE | (pNext->pPrev != 0);
  v22 = pCmdList->DrawItemMax;
  if (v22 < 1)
  {
LABEL_35:
    v19 = v21 | 2;
  }
  else
  {
    while (1)
    {
      pNext = pNext->pNext;
      if (!pNext)
        break;
      if (!--v22)
        goto LABEL_35;
    }
    v19 = v21 & 0xFFFFFFFD;
  }
LABEL_39:
  pCmdList->Stat = v19;
  return pPrev;
}

// 0x1c98660
void *CmdListItemMoveIndexEx(void *pCmdList, s32 index) {
  void *p_pCurrent;
  void *pCurrent;
  s32 ItemCnt;
  s32 Flag;
  s32 v9;
  void *result;
  void *pHead;
  s32 v13;
  void *v14;
  void *v15;
  void *pListTop;
  u32 v17;
  s32 DrawItemMax;
  s32 v19;
  void *pTail;
  s32 v21;
  void *pCmdLista;

  pCmdLista = pCmdList;
  p_pCurrent = &pCmdList->pCurrent;
  pCurrent = pCmdList->pCurrent;
  ItemCnt = pCmdList->ItemCnt;
  Flag = pCmdList->Flag;
  if (ItemCnt > 1)
  {
    if ((Flag & 2) == 0)
      goto LABEL_4;
LABEL_10:
    pCmdList->Flag = Flag & 0xFFFFFFFE;
    return 0;
  }
  Flag |= 2u;
  pCmdList->Flag = Flag;
  if ((Flag & 2) != 0)
    goto LABEL_10;
LABEL_4:
  v9 = pCurrent->Index;
  if (v9 >= index)
  {
    if (ItemCnt == 1 || v9 <= index)
      return pCurrent;
    if (pCurrent == pCmdList->pHead)
    {
      CmdListItemMoveIndex(ItemCnt - 1, pCmdLista);
      jmsUpdateCmdListStat(pCmdLista);
      pCurrent = p_pCurrent;
      if (p_pCurrent->Index != index)
        goto LABEL_20;
    }
    else if (v9 != index)
    {
LABEL_20:
      pHead = pCmdList->pHead;
      do
      {
        result = pHead;
        if (pCurrent == pHead)
          break;
        pCurrent = pCurrent->pPrev;
        pCmdList->pCurrent = pCurrent;
        v13 = pCmdList->ItemOfs - 1;
        pHead = pCmdList->pHead;
        pCmdList->ItemOfs = v13;
        if (pCurrent != pHead && v13 <= 0)
          mouseNoScroll = 1;
        result = pCurrent;
      }
      while (pCurrent->Index != index);
      return result;
    }
    return pCurrent;
  }
  if (ItemCnt == 1)
    return pCurrent;
  if (pCurrent == pCmdList->pTail)
  {
    if (ItemCnt >= 1)
    {
      v14 = pCmdList->pHead;
      pCmdList->pListTop = v14;
      v15 = pCmdList->pHead;
      pCmdList->pCurrent = v15;
      pCmdList->ItemOfs = 0;
    }
    pListTop = pCmdList->pListTop;
    if (pListTop)
    {
      v17 = pCmdList->Stat & 0xFFFFFFFE | (pListTop->pPrev != 0);
      DrawItemMax = pCmdList->DrawItemMax;
      if (DrawItemMax < 1)
      {
LABEL_32:
        v19 = v17 | 2;
      }
      else
      {
        while (1)
        {
          pListTop = pListTop->pNext;
          if (!pListTop)
            break;
          if (!--DrawItemMax)
            goto LABEL_32;
        }
        v19 = v17 & 0xFFFFFFFD;
      }
      pCmdList->Stat = v19;
    }
    else
    {
      pCmdList->Stat = 0;
    }
    pCurrent = p_pCurrent;
    if (p_pCurrent->Index == index)
      return pCurrent;
  }
  else if (v9 == index)
  {
    return pCurrent;
  }
  pTail = pCmdList->pTail;
  do
  {
    result = pTail;
    if (pCurrent == pTail)
      break;
    pCurrent = pCurrent->pNext;
    pCmdList->pCurrent = pCurrent;
    v21 = pCmdList->ItemOfs + 1;
    pTail = pCmdList->pTail;
    pCmdList->ItemOfs = v21;
    if (pCurrent != pTail && v21 >= pCmdList->DrawItemMax - 1)
      mouseNoScroll = 1;
    result = pCurrent;
  }
  while (pCurrent->Index != index);
  return result;
}

// 0x1c98950
void jmsDrawCursorCore(s32 X, s32 Y, u32 Z, s32 AlphaRate, void *pCursor, s32 Mode, s32 OtNo) {
  u32 Type;
  sdfIVector2_t *v9;
  sdfIVector2_t v10;
  sdfIVector2_t v11;
  sdfIVector2_t *v13;
  s32 SprMax;
  s64 v15;
  sdfIVector2_t v16;

  Type = pCursor->Type;
  if (Type >= 4)
  {
    if (Type == 4)
    {
      v13 = NewSpecific(sdfIVector2_t, 0);
      SprMax = pCursor->SprMax;
      if (SprMax >= 1)
      {
        v15 = 0;
        v16 = (sdfIVector2_t)((s64)&v13[0]);
        do
        {
          if ((u32)v15 != 3 && (u32)v15 != 5)
          {
            get_Item(v16, 0, 0);
            get_Item(v16, 1, 0);
            SprMax = pCursor->SprMax;
          }
          ++v15;
          *(u64 *)&v16 += 8;
        }
        while (v15 < SprMax);
      }
    }
    else if (Type == 5)
    {
      v9 = NewSpecific(sdfIVector2_t, 0);
      v10 = (sdfIVector2_t)((s64)&v9[0]);
      v11 = (sdfIVector2_t)v9;
      get_Item((sdfIVector2_t)((s64)&v9[0]), 0, 0);
      get_Item(v10, 1, 0);
      *(u64 *)&v11 += 40;
      get_Item(v11, 0, 0);
      get_Item(v11, 1, 0);
    }
  }
  else
  {
    NewSpecific(sdfIVector2_t, 0);
  }
}

// 0x1c98cf0
void jmsSetScrollBarUi(void) {
  ;
}

// 0x1c98d00
void *jmsCreateCmdList(u32 Type, s32 DrawItemMax, s32 StepY) {
  void *v6;

  v6 = (void *)Allocate(jmsCmdList_s);
  _ctor(v6, 0);
  v6->Type = Type;
  v6->DrawItemMax = DrawItemMax;
  v6->pCurrent = 0;
  v6->pListTop = 0;
  v6->pHead = 0;
  v6->ItemOfs = 0;
  v6->AlphaRate = 256;
  return v6;
}

// 0x1c98db0
s32 jmsDestroyCmdList(void *pCmdList) {
  while (jmsDelCmdListItem(pCmdList))
    ;
  return 1;
}

// 0x1c98280
void jmsUpdateCmdListStat(void *pCmdList) {
  void *v2;
  void *pListTop;
  u32 v4;
  s32 DrawItemMax;

  v2 = pCmdList;
  pListTop = pCmdList->pListTop;
  if (pListTop)
  {
    v4 = v2->Stat & 0xFFFFFFFE | (pListTop->pPrev != 0);
    DrawItemMax = v2->DrawItemMax;
    if (DrawItemMax < 1)
    {
LABEL_5:
      v2->Stat = v4 | 2;
    }
    else
    {
      while (1)
      {
        pListTop = pListTop->pNext;
        if (!pListTop)
          break;
        if (!--DrawItemMax)
          goto LABEL_5;
      }
      v2->Stat = v4 & 0xFFFFFFFD;
    }
  }
  else
  {
    v2->Stat = 0;
  }
}

// 0x1c99070
void *jmsAddCmdListItem(void *pCmdList, s8 pItemName) {
  void *v5;
  void *pTail;
  void *v7;
  void *pPrev;
  s32 ItemCnt;
  void *pListTop;
  s32 v11;
  u32 v12;
  s32 DrawItemMax;
  s32 v14;
  s32 v15;

  v5 = (void *)Allocate(jmsCmdListItem_s);
  _ctor(v5, 0);
  if (!pCmdList->ItemCnt)
  {
    pCmdList->pListTop = v5;
    pCmdList->pCurrent = v5;
    pCmdList->pHead = v5;
  }
  v5->pItemName = pItemName;
  pTail = pCmdList->pTail;
  v5->pPrev = pTail;
  v5->pNext = 0;
  v7 = pCmdList->pTail;
  v5->pPrev = v7;
  pPrev = v5->pPrev;
  if (pPrev)
  {
    pPrev->pNext = v5;
  }
  pCmdList->pTail = v5;
  ItemCnt = pCmdList->ItemCnt;
  v5->Index = ItemCnt;
  pListTop = pCmdList->pListTop;
  v11 = ItemCnt + 1;
  pCmdList->ItemCnt = v11;
  if (pListTop)
  {
    v12 = pCmdList->Stat & 0xFFFFFFFE | (pListTop->pPrev != 0);
    DrawItemMax = pCmdList->DrawItemMax;
    if (DrawItemMax < 1)
    {
LABEL_12:
      v15 = v12 | 2;
    }
    else
    {
      v14 = pCmdList->DrawItemMax;
      while (1)
      {
        pListTop = pListTop->pNext;
        if (!pListTop)
          break;
        if (!--v14)
          goto LABEL_12;
      }
      v15 = v12 & 0xFFFFFFFD;
    }
    pCmdList->Stat = v15;
    if (DrawItemMax > 2)
      return v5;
  }
  else
  {
    DrawItemMax = pCmdList->DrawItemMax;
    pCmdList->Stat = 0;
    if (DrawItemMax > 2)
      return v5;
  }
  if (DrawItemMax >= v11)
    return v5;
  pCmdList->DrawItemMax = v11;
  return v5;
}

// 0x1c99210
s32 jmsChkCmdListDrawTail(void *pCmdList) {
  void *pListTop;
  s32 v3;

  pListTop = pCmdList->pListTop;
  if (pListTop)
  {
    v3 = (pCmdList->DrawItemMax & ~(pCmdList->DrawItemMax >> 31)) + 1;
    do
    {
      if (!--v3)
        break;
      if (pListTop == pCmdList->pTail)
        return 1;
      pListTop = pListTop->pNext;
    }
    while (pListTop);
  }
  return 0;
}

// 0x1c99250
void *jmsInsertCmdListItem(void *pCmdList, void *pItem, s8 pItemName, s32 DelItemIndex, u32 Mode) {
  char v6;
  void *v11;
  void *v12;
  void *pPrev;
  void *v14;
  void *v15;
  void *v16;
  void *v17;
  void *p_pListTop;
  void *v20;
  void *pNext;
  void *v22;
  void *v25;
  void *v26;
  void *v27;
  void *v28;
  void *pListTop;
  void *v30;
  s32 Index;
  s32 v32;
  void *pCurrent;
  void *p_pCurrent;
  void *v35;
  void *pHead;
  void *v38;
  void *v39;
  s32 v40;
  void *v41;
  void *v42;
  void *v43;
  s32 DrawItemMax;
  s32 v45;
  s32 ItemCnt;
  u32 v47;
  s32 v48;
  s32 v49;

  v6 = Mode;
  if (!pCmdList->ItemCnt || !pItem || pItem == pCmdList->pTail)
  {
    v20 = jmsAddCmdListItem(pCmdList, pItemName);
    if (pCmdList->ItemOfs < pCmdList->DrawItemMax - 1 || pCmdList->pCurrent == pCmdList->pTail)
    {
      if (DelItemIndex == -2)
      {
        CmdListItemMoveNextEx(pCmdList, 0, 1);
        return v20;
      }
    }
    else
    {
      pNext = pCmdList->pListTop->pNext;
      pCmdList->pListTop = pNext;
      v22 = pCmdList->pCurrent->pNext;
      pCmdList->pCurrent = v22;
      if (DelItemIndex == -1)
      {
        CmdListItemMovePrevEx(pCmdList, 0, 1);
        return v20;
      }
    }
    return v20;
  }
  v11 = (void *)Allocate(jmsCmdListItem_s);
  _ctor(v11, 0);
  v12 = pItem;
  v11->pItemName = pItemName;
  if ((v6 & 2) != 0)
  {
    v11->pPrev = v12;
    v25 = pItem->pNext;
    v11->pNext = v25;
    v26 = pItem;
    v11->Index = pItem->Index;
    v27 = v26->pNext;
    if (v27)
    {
      v27->pPrev = v11;
      v26 = pItem;
    }
    v26->pNext = v11;
    v28 = v11;
    do
    {
      ++v28->Index;
      v28 = v28->pNext;
    }
    while (v28);
  }
  else
  {
    pPrev = v12->pPrev;
    v11->pPrev = pPrev;
    v14 = pItem;
    v11->pNext = pItem;
    v15 = pItem;
    v11->Index = pItem->Index;
    v16 = v15->pPrev;
    if (v16)
    {
      v16->pNext = v11;
      v15 = pItem;
    }
    v15->pPrev = v11;
    v17 = pItem;
    if (pItem == pCmdList->pHead)
    {
      pCmdList->pHead = v11;
      p_pListTop = &pCmdList->pListTop;
      if (pCmdList->pCurrent == pCmdList->pListTop || pCmdList->ItemCnt < pCmdList->DrawItemMax)
      {
        p_pListTop = v11;
      }
      v17 = pItem;
    }
    for (; v17; v17 = v17->pNext)
      ++v17->Index;
  }
  v30 = &pCmdList->pListTop;
  pListTop = pCmdList->pListTop;
  Index = pListTop->Index;
  ++pCmdList->ItemCnt;
  v32 = v11->Index;
  if (v32 < Index)
    goto LABEL_53;
  p_pCurrent = &pCmdList->pCurrent;
  pCurrent = pCmdList->pCurrent;
  if (v32 >= pCurrent->Index)
    goto LABEL_52;
  v35 = pCurrent->pPrev;
  pCmdList->pCurrent = v35;
  pHead = pCmdList->pHead;
  v38 = pCmdList->pListTop;
  if (pHead == v38)
  {
    DrawItemMax = pCmdList->DrawItemMax;
    v45 = DrawItemMax + 1;
    ItemCnt = pCmdList->ItemCnt;
    if ((DelItemIndex & 0x80000000) == 0 || DelItemIndex == -2)
    {
      if (ItemCnt < v45 || p_pCurrent->Index - pHead->Index != DrawItemMax - 1)
      {
        if (DelItemIndex != -2)
          goto LABEL_52;
        goto LABEL_51;
      }
    }
    else if (ItemCnt < v45 || p_pCurrent->Index - pHead->Index != DrawItemMax - 1)
    {
LABEL_51:
      CmdListItemMoveNextEx(pCmdList, 0, 1);
      goto LABEL_52;
    }
    v41 = pHead->pNext;
LABEL_39:
    v30 = v41;
    v42 = &pCmdList->pCurrent;
    v43 = p_pCurrent->pNext;
    p_pCurrent = v43;
LABEL_40:
    goto LABEL_52;
  }
  if (v38)
  {
    v39 = pCmdList->pListTop;
    v40 = (pCmdList->DrawItemMax & ~(pCmdList->DrawItemMax >> 31)) + 1;
    do
    {
      if (!--v40)
        break;
      if (v39 == pCmdList->pTail)
      {
        if (DelItemIndex < 0 && DelItemIndex != -2)
        {
          v43 = v38->pNext;
          v42 = &pCmdList->pListTop;
          v30 = v43;
          goto LABEL_40;
        }
        goto LABEL_52;
      }
      v39 = v39->pNext;
    }
    while (v39);
  }
  if (DelItemIndex < 0 && DelItemIndex != -2 || DelItemIndex == -2)
  {
    v41 = v38->pNext;
    goto LABEL_39;
  }
LABEL_52:
  pListTop = v30;
  if (!v30)
  {
    pCmdList->Stat = 0;
    return v11;
  }
LABEL_53:
  v47 = pCmdList->Stat & 0xFFFFFFFE | (pListTop->pPrev != 0);
  v48 = pCmdList->DrawItemMax;
  if (v48 < 1)
  {
LABEL_56:
    v49 = v47 | 2;
  }
  else
  {
    while (1)
    {
      pListTop = pListTop->pNext;
      if (!pListTop)
        break;
      if (!--v48)
        goto LABEL_56;
    }
    v49 = v47 & 0xFFFFFFFD;
  }
  pCmdList->Stat = v49;
  return v11;
}

// 0x1c98de0
void *jmsDelCmdListItem(void *pCmdList) {
  void *pCurrent;
  void *p_pCurrent;
  void *pNext;
  s32 Index;
  bool v7;
  s32 v8;
  void *pPrev;
  void *v10;
  void *p_pTail;
  void *pListTop;
  void *p_pListTop;
  void *v14;
  void *v15;
  void *v17;
  void *v18;
  u32 v19;
  s32 DrawItemMax;
  s32 v21;
  void *v22;
  void *v23;

  if (!pCmdList->ItemCnt)
    return 0;
  p_pCurrent = &pCmdList->pCurrent;
  pCurrent = pCmdList->pCurrent;
  if (!pCurrent)
    return 0;
  pNext = pCmdList->pCurrent;
  do
  {
    Index = pNext->Index;
    v7 = __OFSUB__(Index, 1);
    v8 = Index - 1;
    if (v8 < 0 == v7)
      pNext->Index = v8;
    pNext = pNext->pNext;
  }
  while (pNext);
  v10 = pCurrent->pNext;
  pPrev = pCurrent->pPrev;
  p_pTail = &pCmdList->pTail;
  p_pListTop = &pCmdList->pListTop;
  pListTop = pCmdList->pListTop;
  if (pCmdList->pTail->Index - pListTop->Index + 1 > pCmdList->DrawItemMax)
  {
    if (!v10)
      goto LABEL_15;
    goto LABEL_9;
  }
  if (pListTop != pCmdList->pHead)
  {
    v17 = pListTop->pPrev;
    p_pListTop = v17;
    p_pCurrent = pPrev;
    v14 = p_pCurrent;
    v15 = pPrev;
    goto LABEL_14;
  }
  if (pCurrent == pListTop)
  {
    if (!v10)
    {
      v23 = pCurrent->pPrev;
      pCmdList->pListTop = pPrev;
      goto LABEL_40;
    }
    v22 = pCurrent->pNext;
    p_pListTop = v10;
LABEL_9:
    v14 = p_pCurrent;
    v15 = v10;
    p_pCurrent = v10;
LABEL_14:
LABEL_15:
    if (p_pCurrent)
      goto LABEL_17;
    goto LABEL_16;
  }
  if (v10)
    goto LABEL_9;
LABEL_40:
  pCmdList->pCurrent = pPrev;
  --pCmdList->ItemOfs;
  if (!p_pCurrent)
  {
LABEL_16:
    pCmdList->pListTop = 0;
    pCmdList->pHead = 0;
    pCmdList->pTail = 0;
    pCmdList->ItemOfs = 0;
  }
LABEL_17:
  if (pPrev)
  {
    pPrev->pNext = v10;
  }
  if (v10)
  {
    v10->pPrev = pPrev;
  }
  if (pPrev)
  {
    if (v10)
      goto LABEL_23;
LABEL_29:
    p_pTail = pPrev;
    --pCmdList->ItemCnt;
    v18 = pCmdList->pListTop;
    if (v18)
      goto LABEL_24;
    goto LABEL_30;
  }
  pCmdList->pListTop = v10;
  pCmdList->pHead = v10;
  if (!v10)
    goto LABEL_29;
LABEL_23:
  --pCmdList->ItemCnt;
  v18 = pCmdList->pListTop;
  if (v18)
  {
LABEL_24:
    v19 = pCmdList->Stat & 0xFFFFFFFE | (v18->pPrev != 0);
    DrawItemMax = pCmdList->DrawItemMax;
    if (DrawItemMax < 1)
    {
LABEL_27:
      v21 = v19 | 2;
    }
    else
    {
      while (1)
      {
        v18 = v18->pNext;
        if (!v18)
          break;
        if (!--DrawItemMax)
          goto LABEL_27;
      }
      v21 = v19 & 0xFFFFFFFD;
    }
    pCmdList->Stat = v21;
    return *p_pCurrent;
  }
LABEL_30:
  pCmdList->Stat = 0;
  return *p_pCurrent;
}

// 0x1c996f0
void *CmdListGetTargetItem(s32 Index, void *pCmdList) {
  void *result;
  bool v5;
  s32 v6;
  bool v7;

  result = pCmdList->pHead;
  if (result)
    v5 = Index == 0;
  else
    v5 = 1;
  if (!v5)
  {
    v6 = Index - 1;
    do
    {
      result = result->pNext;
      if (result)
        v7 = v6 == 0;
      else
        v7 = 1;
      --v6;
    }
    while (!v7);
  }
  return result;
}

// 0x1c99730
s32 CmdListItemMoveIndex(s32 Index, void *pCmdList) {
  void *v4;
  void *pHead;
  void *v7;
  void *v8;
  void *pNext;
  void *p_pListTop;
  void *p_pCurrent;
  void *v12;
  void *v13;
  void *pListTop;
  void *v15;
  void *pCurrent;
  void *v17;

  v4 = pCmdList;
  if (pCmdList->ItemCnt <= Index)
    return 0;
  pHead = v4->pHead;
  v4->pListTop = pHead;
  v7 = pCmdList;
  v8 = pCmdList->pHead;
  v7->pCurrent = v8;
  pCmdList->ItemOfs = 0;
  if (Index >= 1)
  {
    do
    {
      while (1)
      {
        v13 = pCmdList;
        pListTop = pCmdList->pListTop;
        if (pCmdList->ItemCnt - pListTop->Index <= pCmdList->DrawItemMax)
          break;
        pNext = pListTop->pNext;
        p_pListTop = &pCmdList->pListTop;
        p_pListTop = pNext;
        p_pCurrent = &pCmdList->pCurrent;
        v12 = p_pCurrent->pNext;
        p_pCurrent = v12;
        if (!--Index)
          return 1;
      }
      ++v13->ItemOfs;
      pCurrent = v13->pCurrent;
      v15 = &v13->pCurrent;
      v17 = pCurrent->pNext;
      v15 = v17;
      --Index;
    }
    while (Index);
  }
  return 1;
}

// 0x1c98230
void CmdListItemMoveHead(void *pCmdList) {
  void *v3;
  void *pHead;
  void *v5;
  void *v6;

  v3 = pCmdList;
  if (v3->ItemCnt >= 1)
  {
    pHead = v3->pHead;
    v3->pListTop = pHead;
    v5 = pCmdList;
    v6 = pCmdList->pHead;
    v5->pCurrent = v6;
    pCmdList->ItemOfs = 0;
  }
}

// 0x1c985d0
void CmdListItemMoveTail(void *pCmdList) {
  CmdListItemMoveIndex(pCmdList->ItemCnt - 1, pCmdList);
}

// 0x1c982e0
void *CmdListMoveUp(void *pCmdList) {
  void *v2;
  void *v4;
  void *p_pListTop;
  void *pListTop;
  void *pNext;

  v2 = pCmdList;
  v4 = pCmdList;
  pListTop = v4->pListTop;
  p_pListTop = &v4->pListTop;
  pNext = pListTop->pNext;
  if (pNext)
  {
    p_pListTop = pNext;
    v2 = pCmdList;
    --pCmdList->ItemOfs;
  }
  return v2->pCurrent;
}

// 0x1c985f0
void *CmdListMoveDown(void *pCmdList) {
  void *v2;
  s32 DrawItemMax;
  void *p_pListTop;
  void *pListTop;
  void *pPrev;

  v2 = pCmdList;
  DrawItemMax = pCmdList->DrawItemMax;
  p_pListTop = &pCmdList->pListTop;
  if (DrawItemMax < 1)
  {
LABEL_5:
    pPrev = v2->pListTop->pPrev;
    p_pListTop = pPrev;
    v2 = pCmdList;
    ++pCmdList->ItemOfs;
  }
  else
  {
    pListTop = v2->pListTop;
    while (pListTop)
    {
      pListTop = pListTop->pNext;
      if (!--DrawItemMax)
        goto LABEL_5;
    }
  }
  return v2->pCurrent;
}

// 0x1c99820
void *CmdListItemMoveNext(void *pCmdList) {
  return CmdListItemMoveNextEx(pCmdList, 0, 0);
}

// 0x1c99830
void *CmdListItemMovePrev(void *pCmdList) {
  return CmdListItemMovePrevEx(pCmdList, 0, 0);
}

// 0x1c99840
void *CmdListItemMoveNextPage(void *pCmdList) {
  void *p_pCurrent;
  s32 DrawItemMax;
  s32 v5;
  void *p_pListTop;
  void *v7;
  void *pNext;
  s32 v9;
  void *v10;
  void *pListTop;
  s32 v12;
  u32 v13;

  p_pCurrent = &pCmdList->pCurrent;
  if (!pCmdList->pCurrent)
    return 0;
  DrawItemMax = pCmdList->DrawItemMax;
  if (DrawItemMax >= 1)
  {
    v5 = 0;
    p_pListTop = &pCmdList->pListTop;
    do
    {
      if (p_pListTop)
      {
        pNext = p_pListTop;
        v9 = (DrawItemMax & ~(DrawItemMax >> 31)) + 1;
        do
        {
          if (!--v9)
            break;
          if (pNext == pCmdList->pTail)
          {
            if (v5)
              goto LABEL_13;
            if (p_pCurrent != pNext)
            {
LABEL_24:
              pCmdList->pCurrent = pNext;
              pCmdList->ItemOfs = DrawItemMax - 1;
              return *p_pCurrent;
            }
            return 0;
          }
          pNext = pNext->pNext;
        }
        while (pNext);
      }
      v10 = p_pListTop->pNext;
      if (v10)
      {
        pCmdList->pListTop = v10;
        --pCmdList->ItemOfs;
      }
      v7 = pCmdList->pCurrent->pNext;
      pCmdList->pCurrent = v7;
      ++v5;
      ++pCmdList->ItemOfs;
      DrawItemMax = pCmdList->DrawItemMax;
    }
    while (v5 < DrawItemMax);
  }
LABEL_13:
  pListTop = pCmdList->pListTop;
  if (pListTop)
  {
    pNext = pCmdList->pListTop;
    v12 = (DrawItemMax & ~(DrawItemMax >> 31)) + 1;
    do
    {
      if (!--v12)
        break;
      if (pNext == pCmdList->pTail)
        goto LABEL_24;
      pNext = pNext->pNext;
    }
    while (pNext);
    v13 = pCmdList->Stat & 0xFFFFFFFE | (pListTop->pPrev != 0);
    if (DrawItemMax < 1)
    {
LABEL_21:
      pCmdList->Stat = v13 | 2;
      return *p_pCurrent;
    }
    else
    {
      while (1)
      {
        pListTop = pListTop->pNext;
        if (!pListTop)
          break;
        if (!--DrawItemMax)
          goto LABEL_21;
      }
      pCmdList->Stat = v13 & 0xFFFFFFFD;
      return *p_pCurrent;
    }
  }
  else
  {
    pCmdList->Stat = 0;
    return *p_pCurrent;
  }
}

// 0x1c99a10
void *CmdListItemMovePrevPage(void *pCmdList) {
  void *p_pCurrent;
  s32 DrawItemMax;
  s32 v5;
  void *pPrev;
  void *v7;
  void *pListTop;
  void *pNext;
  void *v10;
  void *v11;
  s32 v12;
  s32 v13;
  void *v14;
  void *v15;
  u32 v16;

  p_pCurrent = &pCmdList->pCurrent;
  if (!pCmdList->pCurrent)
    return 0;
  DrawItemMax = pCmdList->DrawItemMax;
  if (DrawItemMax >= 1)
  {
    v5 = 0;
    while (1)
    {
      pListTop = pCmdList->pListTop;
      if (pListTop == pCmdList->pHead)
        break;
      if (DrawItemMax < 1)
      {
LABEL_4:
        pPrev = pListTop->pPrev;
        pCmdList->pListTop = pPrev;
        ++pCmdList->ItemOfs;
      }
      else
      {
        pNext = pCmdList->pListTop;
        while (pNext)
        {
          pNext = pNext->pNext;
          if (!--DrawItemMax)
            goto LABEL_4;
        }
      }
      v7 = pCmdList->pCurrent->pPrev;
      pCmdList->pCurrent = v7;
      ++v5;
      DrawItemMax = pCmdList->DrawItemMax;
      --pCmdList->ItemOfs;
      if (v5 >= DrawItemMax)
        goto LABEL_12;
    }
    if (v5 || p_pCurrent != pListTop)
      goto LABEL_28;
    return 0;
  }
LABEL_12:
  v10 = pCmdList->pListTop;
  pListTop = pCmdList->pHead;
  if (v10 == pListTop)
  {
LABEL_28:
    pCmdList->ItemOfs = 0;
    pCmdList->pCurrent = pListTop;
    return *p_pCurrent;
  }
  v11 = pCmdList->pListTop;
  if (DrawItemMax >= 1)
  {
    v12 = DrawItemMax;
    v11 = pCmdList->pListTop;
    do
    {
      v11 = v11->pNext;
      if (!v11)
        break;
      --v12;
    }
    while (v12);
  }
  if (p_pCurrent == v11)
  {
    pCmdList->pCurrent = v10;
    pCmdList->ItemOfs = DrawItemMax - 2;
    DrawItemMax = pCmdList->DrawItemMax;
    if (DrawItemMax - 2 >= 1)
    {
      v13 = 0;
      do
      {
        v14 = pCmdList->pCurrent->pNext;
        pCmdList->pCurrent = v14;
        DrawItemMax = pCmdList->DrawItemMax;
        ++v13;
      }
      while (v13 < DrawItemMax - 2);
    }
  }
  v15 = pCmdList->pListTop;
  if (v15)
  {
    v16 = pCmdList->Stat & 0xFFFFFFFE | (v15->pPrev != 0);
    if (DrawItemMax < 1)
    {
LABEL_25:
      pCmdList->Stat = v16 | 2;
      return *p_pCurrent;
    }
    else
    {
      while (1)
      {
        v15 = v15->pNext;
        if (!v15)
          break;
        if (!--DrawItemMax)
          goto LABEL_25;
      }
      pCmdList->Stat = v16 & 0xFFFFFFFD;
      return *p_pCurrent;
    }
  }
  else
  {
    pCmdList->Stat = 0;
    return *p_pCurrent;
  }
}

// 0x1c99c50
void CmdListMoveUnlock(void *pCmdList) {
  pCmdList->Flag &= 0xFFFFFFFC;
}

// 0x1c99c60
u32 jmsChkCmdListMoveLock(void *pCmdList) {
  return pCmdList->Flag & 2;
}

// 0x1c99c70
s32 jmsGetCmdListH(void *pCmdList) {
  return pCmdList->DrawItemMax * pCmdList->StepY;
}

// 0x1c99c80
void jmsClearCmdListCursorBlur(void *pCmdList) {
  void *i;

  for (i = pCmdList->pHead; i; i = i->pNext)
    i->Timer = 0;
}

// 0x1c99ca0
void jmsUpdateCmdListTimer(void *pCmdList) {
  void *i;
  s32 Timer;

  for (i = pCmdList->pHead; i; i = i->pNext)
  {
    Timer = i->Timer;
    if (Timer <= 0)
    {
      if ((Timer & 0x80000000) == 0)
        continue;
    }
    else
    {
      Timer -= 16;
    }
    i->Timer = Timer & ~(Timer >> 31);
  }
}

// 0x1c99ce0
void jmsDrawCmdListIcon(s32 X, s32 Y, u32 Z, void *pCmdList, void *pItem, s32 OtNo) {
  ;
}

// 0x1c99cf0
u32 jmsGetCmdListItemColor(u32 Col, void *pItem) {
  return 0;
}

// 0x1c99d00
void jmsDrawCmdListEx(s32 X, s32 Y, u32 Z, s32 StrOfsX, s32 StrOfsY, s32 AlphaRate, u32 Flag, void *pCmdList, s32 OtNo) {
  void *pListTop;
  void *i;
  s32 v16;
  s32 Timer;
  void *UserDrawFunc;

  *(u64 *)(NewSpecific(sbyte, 8u) + 32) = 0;
  pListTop = pCmdList->pListTop;
  for (i = pCmdList->pHead; i; i = i->pNext)
  {
    Timer = i->Timer;
    if (Timer <= 0)
    {
      if ((Timer & 0x80000000) == 0)
        continue;
    }
    else
    {
      Timer -= 16;
    }
    i->Timer = Timer & ~(Timer >> 31);
  }
  if (pListTop)
  {
    v16 = -1;
    do
    {
      if (++v16 >= pCmdList->DrawItemMax)
        break;
      UserDrawFunc = pCmdList->UserDrawFunc;
      if (UserDrawFunc)
      {
        if (!(UserDrawFunc->invoke_impl)(UserDrawFunc->method_code, X, Y, Z, pCmdList, pListTop, OtNo, UserDrawFunc->method))
          break;
      }
      Y += pCmdList->StepY;
      pListTop = pListTop->pNext;
    }
    while (pListTop);
  }
}

// 0x1c99e20
void jmsDrawCmdList(s32 X, s32 Y, u32 Z, void *pCmdList, s32 OtNo) {
  void *pListTop;
  void *i;
  s32 v13;
  s32 Timer;
  void *UserDrawFunc;

  *(u64 *)(NewSpecific(sbyte, 8u) + 32) = 0;
  pListTop = pCmdList->pListTop;
  for (i = pCmdList->pHead; i; i = i->pNext)
  {
    Timer = i->Timer;
    if (Timer <= 0)
    {
      if ((Timer & 0x80000000) == 0)
        continue;
    }
    else
    {
      Timer -= 16;
    }
    i->Timer = Timer & ~(Timer >> 31);
  }
  if (pListTop)
  {
    v13 = -1;
    do
    {
      if (++v13 >= pCmdList->DrawItemMax)
        break;
      UserDrawFunc = pCmdList->UserDrawFunc;
      if (UserDrawFunc)
      {
        if (!(UserDrawFunc->invoke_impl)(UserDrawFunc->method_code, X, Y, Z, pCmdList, pListTop, OtNo, UserDrawFunc->method))
          break;
      }
      Y += pCmdList->StepY;
      pListTop = pListTop->pNext;
    }
    while (pListTop);
  }
}

// 0x1c99f40
void SetScrollBarUi(void *_menu, void *_scrollBarUi) {
  menu->scrollBarUi = scrollBarUi;
}

// 0x1c99f50
void *jmsCreateCmdMenu(u32 Type, s32 StrOfsX, s32 StrOfsY, s32 DrawItemMax, s32 StepY) {
  void *v10;
  char v11;
  void *v12;

  v10 = (void *)Allocate(jmsCmdMenu_s);
  _ctor(v10, 0);
  v10->Type = Type;
  v11 = byte_5757691;
  v10->StrOfsX = StrOfsX;
  v10->StrOfsY = StrOfsY;
  v12 = Allocate(jmsCmdList_s);
  _ctor(v12, 0);
  v12->Type = Type;
  v12->DrawItemMax = DrawItemMax;
  v12->pCurrent = 0;
  v12->pListTop = 0;
  v12->pHead = 0;
  v12->ItemOfs = 0;
  v10->pCmdList = v12;
  v12->AlphaRate = 256;
  v10->AlphaRate = 0;
  return v10;
}

// 0x1c9a070
void jmsDestroyCmdMenu(void *pCmdMenu) {
  void *pCmdList;

  pCmdList = pCmdMenu->pCmdList;
  while (jmsDelCmdListItem(pCmdList))
    ;
}

// 0x1c9a0b0
void jmsSetCmdListAlphaRate(void *pCmdList, s32 AlphaRate) {
  pCmdList->AlphaRate = AlphaRate;
}

// 0x1c9a0c0
void jmsSetCmdMenuAlphaRate(void *pCmdMenu, s32 AlphaRate) {
  pCmdMenu->AlphaRate = AlphaRate;
}

// 0x1c9a0d0
void jmsSetCmdMenuCursor(void *pCmdMenu, void *pCursor, s32 X1, s32 X2, s32 X3, s32 X4) {
  void *v7;
  s32 *OfsX;

  v7 = pCmdMenu;
  OfsX = pCmdMenu->Cursor->OfsX;
  OfsX[0] = X1;
  OfsX[1] = X2;
  OfsX[2] = X3;
  OfsX[3] = X4;
  v7->Flag |= 4u;
}

// 0x1c9a100
void CmdMenuCursorDrawUnlock(void *pCmdMenu) {
  pCmdMenu->Flag &= ~4u;
}

// 0x1c9a120
void *jmsAddCmdMenuItem(void *pCmdMenu, s8 pItemName) {
  return jmsAddCmdListItem(pCmdMenu->pCmdList, pItemName);
}

// 0x1c9a130
void *jmsInsertCmdMenuItem(void *pCmdMenu, void *pItem, s8 pItemName, s32 DelItemIndex, u32 Mode) {
  void *pCmdList;
  void *pItema;

  pCmdList = pCmdMenu->pCmdList;
  pItema = pItem;
  return jmsInsertCmdListItem(pCmdList, pItema, pItemName, DelItemIndex, Mode);
}

// 0x1c9a160
void *jmsDelCmdMenuItem(void *pCmdMenu) {
  return jmsDelCmdListItem(pCmdMenu->pCmdList);
}

// 0x1c9a170
void *CmdMenuItemMoveNextEx(void *pCmdMenu, s32 Mode) {
  return CmdListItemMoveNextEx(pCmdMenu->pCmdList, Mode, 0);
}

// 0x1c9a180
void *CmdMenuItemMovePrevEx(void *pCmdMenu, s32 Mode) {
  return CmdListItemMovePrevEx(pCmdMenu->pCmdList, Mode, 0);
}

// 0x1c9a190
void *CmdMenuItemMoveNext(void *pCmdMenu) {
  return CmdListItemMoveNextEx(pCmdMenu->pCmdList, 0, 0);
}

// 0x1c9a1a0
void *CmdMenuItemMovePrev(void *pCmdMenu) {
  return CmdListItemMovePrevEx(pCmdMenu->pCmdList, 0, 0);
}

// 0x1c9a1b0
void CmdMenuMoveUnlock(void *pCmdMenu) {
  pCmdMenu->pCmdList->Flag &= 0xFFFFFFFC;
}

// 0x1c9a1d0
u32 jmsChkCmdMenuMoveLock(void *pCmdMenu) {
  return pCmdMenu->pCmdList->Flag & 2;
}

// 0x1c9a0a0
void jmsDestroyScrollBar(void *pScrollBar) {
  ;
}

// 0x1c9a1e0
void jmsDrawScrollBar(s32 X, s32 Y, s32 Z, s32 AlphaRate, void *pCmdList, void *pScrollBar, u32 OtNo) {
  ;
}

// 0x1c9a1f0
void jmsDrawCmdMenuScrollBar(s32 X, s32 Y, u32 Z, void *pCmdMenu, s32 OtNo) {
  ;
}

// 0x1c9a200
void jmsDrawCmdMenuPanelTypeNormal(s32 X, s32 Y, u32 Z, void *pCmdMenu, s32 LineMax, u32 OtNo) {
  ;
}

// 0x1c9a220
void jmsDrawCmdMenuPanel(s32 X, s32 Y, u32 Z, void *pCmdMenu, u32 OtNo) {
  ;
}

// 0x1c9a230
void jmsDrawCmdMenuTitle(s32 X, s32 Y, u32 Z, void *pCmdMenu, s32 OtNo) {
  ;
}

// 0x1c9a240
void jmsDrawCmdMenuCursor(s32 X, s32 Y, u32 Z, void *pCmdMenu, s32 OtNo) {
  s32 v6;
  void *Cursor;
  s32 Timer;
  s32 v11;
  s32 v12;
  s32 v13;

  jmsDrawCursorCore(X, Y, Z, (s32)pCmdMenu, pCmdMenu->Cursor, (s32)v6);
  Cursor = pCmdMenu->Cursor;
  Timer = Cursor->Timer;
  v11 = Timer + 32;
  v12 = Timer + 16;
  if (v11 >= 256)
    v11 = 256;
  if (v12 >= 512)
    v12 = 512;
  if ((pCmdMenu->Flag & 4) != 0)
    v13 = v12;
  else
    v13 = v11;
  Cursor->Timer = v13;
}

// 0x1c9a2f0
void jmsDrawCmdMenu(s32 X, s32 Y, u32 Z, void *pCmdMenu, s32 OtNo) {
  s32 v6;
  void *v9;
  void *pCmdList;
  void *Cursor;
  s32 Timer;
  s32 v17;
  s32 v18;
  s32 v19;
  void *v20;
  void *v21;
  void *pListTop;
  void *i;
  s32 v24;
  u32 v25;
  s32 v26;
  void *UserDrawFunc;
  void *v28;
  void *v29;

  v9 = pCmdMenu;
  pCmdList = pCmdMenu->pCmdList;
  pCmdList->AlphaRate = pCmdMenu->AlphaRate;
  if (pCmdList->ItemCnt)
  {
    jmsDrawCursorCore(X, Y, Z, (s32)pCmdMenu, v9->Cursor, (s32)v6);
    Cursor = pCmdMenu->Cursor;
    Timer = Cursor->Timer;
    v17 = Timer + 32;
    v18 = Timer + 16;
    if (v17 >= 256)
      v17 = 256;
    if (v18 >= 512)
      v18 = 512;
    if ((pCmdMenu->Flag & 4) != 0)
      v19 = v18;
    else
      v19 = v17;
    Cursor->Timer = v19;
    v9 = pCmdMenu;
  }
  v20 = v9->UserFunc[0];
  if (v20)
  {
    if (!(v20->invoke_impl)(v20->method_code, X, Y, Z))
      return;
    v9 = pCmdMenu;
  }
  v21 = v9->pCmdList;
  *(u64 *)(NewSpecific(sbyte, 8u) + 32) = 0;
  pListTop = v21->pListTop;
  for (i = v21->pHead; i; i = i->pNext)
  {
    v26 = i->Timer;
    if (v26 <= 0)
    {
      if ((v26 & 0x80000000) == 0)
        continue;
    }
    else
    {
      v26 -= 16;
    }
    i->Timer = v26 & ~(v26 >> 31);
  }
  if (pListTop)
  {
    v24 = -1;
    v25 = Y;
    do
    {
      if (++v24 >= v21->DrawItemMax)
        break;
      UserDrawFunc = v21->UserDrawFunc;
      if (UserDrawFunc)
      {
        if (!(UserDrawFunc->invoke_impl)(UserDrawFunc->method_code, X, v25, Z, v21, pListTop, OtNo, UserDrawFunc->method))
          break;
      }
      v25 += v21->StepY;
      pListTop = pListTop->pNext;
    }
    while (pListTop);
  }
  v28 = pCmdMenu;
  v29 = pCmdMenu->UserFunc[1];
  if (v29)
  {
    if (!(v29->invoke_impl)(v29->method_code, X, Y, Z))
      return;
    v28 = pCmdMenu;
  }
  v28->Flag |= 4u;
}

// 0x1c9a510
void jmsResetCursorMotion(void *pCursor) {
  ;
}

// 0x1c9a520
void jmsDestroyCursor(void *pCursor) {
  ;
}

// 0x1c98af0
void jmsDrawCursorNormal(s32 X, s32 Y, u32 Z, s32 *AlphaRate, void *pCursor, s32 Mode, s32 OtNo) {
  s32 Timer;

  NewSpecific(sdfIVector2_t, 0);
  Timer = pCursor->Timer;
  if (Timer < 257)
    return;
  *AlphaRate = (0x20000 - (Timer << 8)) >> 8;
  return;
}

// 0x1c98b90
void jmsDrawCursorLR(s32 X, s32 Y, u32 Z, s32 AlphaRate, void *pCursor, s32 OtNo) {
  sdfIVector2_t *v8;
  s32 SprMax;
  s64 v10;
  sdfIVector2_t v11;

  v8 = NewSpecific(sdfIVector2_t, 0);
  SprMax = pCursor->SprMax;
  if (SprMax >= 1)
  {
    v10 = 0;
    v11 = (sdfIVector2_t)((s64)&v8[0]);
    do
    {
      if ((u32)v10 != 3 && (u32)v10 != 5)
      {
        get_Item(v11, 0, 0);
        get_Item(v11, 1, 0);
        SprMax = pCursor->SprMax;
      }
      ++v10;
      *(u64 *)&v11 += 8;
    }
    while (v10 < SprMax);
  }
}

// 0x1c98c50
void jmsDrawCursorTabLR(s32 X, s32 Y, u32 Z, s32 AlphaRate, void *pCursor, s32 OtNo) {
  sdfIVector2_t *v7;
  sdfIVector2_t v8;
  sdfIVector2_t v9;

  v7 = NewSpecific(sdfIVector2_t, 0);
  v8 = (sdfIVector2_t)((s64)&v7[0]);
  v9 = (sdfIVector2_t)v7;
  get_Item((sdfIVector2_t)((s64)&v7[0]), 0, 0);
  get_Item(v8, 1, 0);
  *(u64 *)&v9 += 40;
  get_Item(v9, 0, 0);
  get_Item(v9, 1, 0);
}

// 0x1c9a530
void jmsDrawCursorEx(s32 X, s32 Y, u32 Z, s32 AlphaRate, void *pCursor, s32 Mode, s32 OtNo) {
  jmsDrawCursorCore(X, Y, Z, AlphaRate, pCursor, Mode, OtNo);
}

// 0x1c9a540
void jmsDrawCursor(s32 X, s32 Y, u32 Z, void *pCursor, s32 OtNo) {
  s32 v6;

  jmsDrawCursorCore(X, Y, Z, (s32)pCursor, pCursor, (s32)v6);
}

// 0x1c9a2e0
void jmsUpdateCursor(void *pCursor) {
  ;
}

// 0x1c9a550
void CmdListRecalcHead(void *pCmdList) {
  void *v2;
  void *pCurrent;
  void *v4;

  v2 = pCmdList;
  pCurrent = v2->pCurrent;
  if (pCurrent)
  {
    do
    {
      v4 = pCurrent;
      pCurrent = pCurrent->pPrev;
    }
    while (pCurrent);
    v2->pHead = v4;
  }
  else
  {
    v2->pHead = 0;
  }
}

// 0x1c9a580
void CmdListRecalcTail(void *pCmdList) {
  void *v2;
  void *pCurrent;
  void *v4;

  v2 = pCmdList;
  pCurrent = v2->pCurrent;
  if (pCurrent)
  {
    do
    {
      v4 = pCurrent;
      pCurrent = pCurrent->pNext;
    }
    while (pCurrent);
    v2->pTail = v4;
  }
  else
  {
    v2->pTail = 0;
  }
}

// 0x1c9a5b0
void CmdListRecalcListTop(void *pCmdList, u32 Mode) {
  void *v4;
  void *pHead;
  void *monitor;
  void *v8;
  void *v9;
  void *v11;
  void *i;

  v4 = pCmdList;
  pHead = v4->pHead;
  v4->pListTop = pHead;
  v4 = ((char *)v4 + 48);
  monitor = v4->monitor;
  v8 = pCmdList;
  v9 = pCmdList->pHead;
  v8->pCurrent = v9;
  v11 = pCmdList;
  pCmdList->ItemOfs = 0;
  if (Mode == 1)
  {
    for (i = v11->pHead; i && i != monitor; i = i->pNext)
      CmdListItemMoveNextEx(pCmdList, 0, 0);
  }
}

// 0x1c9a640
void CmdListRecalcLinkList(void **pItemList, s32 Nums) {
  void *v5;
  void *v6;
  void *v7;
  s64 v8;
  char *v9;
  s64 v10;
  void *v11;
  char *v12;
  s64 v13;
  void *v14;
  s64 v15;
  void *m_Items;
  void *v17;
  void *v18;
  void *v19;
  void *v20;
  s64 v21;
  s64 v22;
  void *v23;
  s64 v24;
  s32 v25;
  s64 v26;
  s32 v27;
  s32 v28;
  void *v29;
  s64 v30;
  Il2CppClass **v31;
  Il2CppClass *v32;
  Il2CppClass *v33;

  v5 = (*pItemList)[0];
  v5->pPrev = 0;
  v6 = (*pItemList)[0];
  v7 = (*pItemList)[1];
  v6->pNext = v7;
  if (Nums - 1 > 1)
  {
    v8 = 0;
    do
    {
      v9 = (char *)*pItemList + v8;
      v11 = *((void **)v9 + 4);
      v10 = *((u64 *)v9 + 5);
      *(u64 *)(v10 + 48) = v11;
      v12 = (char *)*pItemList + v8;
      v13 = *((u64 *)v12 + 5);
      v14 = *((void **)v12 + 6);
      *(u64 *)(v13 + 40) = v14;
      v8 += 8;
    }
    while (8 * (u32)(Nums - 1) - 8 != v8);
  }
  v15 = Nums - 1;
  m_Items = (*pItemList);
  v17 = m_Items[v15];
  v18 = m_Items[Nums - 2];
  v17->pPrev = v18;
  v19 = (*pItemList)[v15];
  v19->pNext = 0;
  if (Nums >= 1)
  {
    v20 = *pItemList;
    if ((u32)Nums >= 4)
    {
      v22 = 0;
      v21 = Nums & 0xFFFFFFFC;
      v23 = &v20[3];
      do
      {
        v24 = *(v23 - 2);
        v25 = v22 + 1;
        v26 = *(v23 - 1);
        v27 = v22 + 2;
        v28 = v22 + 3;
        (*(v23 - 3))->Index = v22;
        v29 = v23;
        v23 += 4;
        v22 += 4;
        *(u32 *)(v24 + 16) = v25;
        *(u32 *)(v26 + 16) = v27;
        v29->Index = v28;
      }
      while (v21 != v22);
      if (v21 == Nums)
        return;
    }
    else
    {
      v21 = 0;
    }
    v30 = ~v21;
    if ((Nums & 1) != 0)
    {
      v20[v21]->Index = v21;
      v21 |= 1u;
    }
    if (v30 + (u32)Nums)
    {
      do
      {
        v31 = &v20->obj.klass + v21;
        v33 = v31[4];
        v32 = v31[5];
        LODWORD(v33->_1.name) = v21;
        LODWORD(v33) = v21 + 1;
        v21 += 2;
        LODWORD(v32->_1.name) = (u32)v33;
      }
      while (v21 != Nums);
    }
  }
}

// 0x1c9a7e0
s32 CmdListSortCallbackA(void *op1, void *op2) {
  u32 v7;
  u32 v8;
  bool v9;
  s32 v10;

  v7 = *((u32 *)op1[3].monitor + 8);
  v8 = *((u32 *)op2[3].monitor + 8);
  v9 = v7 > v8;
  v10 = v7 < v8;
  if (v9)
    return -1;
  else
    return v10;
}

// 0x1c9a8c0
s32 CmdListSortCallbackA_R(void *op1, void *op2) {
  u32 v7;
  u32 v8;
  bool v9;
  s32 v10;

  v7 = *((u32 *)op1[3].monitor + 8);
  v8 = *((u32 *)op2[3].monitor + 8);
  v9 = v7 > v8;
  if (v7 >= v8)
    v10 = 0;
  else
    v10 = -1;
  if (v9)
    return 1;
  else
    return v10;
}

// 0x1c9a9a0
s32 CmdListSortCallbackB(void *op1, void *op2) {
  u32 v7;
  u32 v8;
  bool v9;
  s32 v10;

  v7 = *((u32 *)op1[3].monitor + 9);
  v8 = *((u32 *)op2[3].monitor + 9);
  v9 = v7 > v8;
  v10 = v7 < v8;
  if (v9)
    return -1;
  else
    return v10;
}

// 0x1c9aa80
s32 CmdListSortCallbackB_R(void *op1, void *op2) {
  u32 v7;
  u32 v8;
  bool v9;
  s32 v10;

  v7 = *((u32 *)op1[3].monitor + 9);
  v8 = *((u32 *)op2[3].monitor + 9);
  v9 = v7 > v8;
  if (v7 >= v8)
    v10 = 0;
  else
    v10 = -1;
  if (v9)
    return 1;
  else
    return v10;
}

// 0x1c9ab60
s32 CmdListSortCallbackC(void *op1, void *op2) {
  u32 v7;
  u32 v8;
  bool v9;
  s32 v10;

  v7 = *((u32 *)op1[3].monitor + 10);
  v8 = *((u32 *)op2[3].monitor + 10);
  v9 = v7 > v8;
  v10 = v7 < v8;
  if (v9)
    return -1;
  else
    return v10;
}

// 0x1c9ac40
s32 CmdListSortCallbackC_R(void *op1, void *op2) {
  u32 v7;
  u32 v8;
  bool v9;
  s32 v10;

  v7 = *((u32 *)op1[3].monitor + 10);
  v8 = *((u32 *)op2[3].monitor + 10);
  v9 = v7 > v8;
  if (v7 >= v8)
    v10 = 0;
  else
    v10 = -1;
  if (v9)
    return 1;
  else
    return v10;
}

// 0x1c9ad20
void CmdListSort(void *pCmdList, u32 Type, u32 Mode) {
  void *v5;
  u64 *v6;
  void *v7;
  void *v8;
  void *v9;
  void *v10;
  void *v11;
  void *v12;
  void *p_pHead;
  void *pHead;
  s32 v15;
  void *m_Items;
  void *v17;
  void *v20;
  u32 v21;
  void *pCurrent;
  void *p_pCurrent;
  void *v25;
  void *pNext;
  void *v27;
  void *v28;
  void *v29;
  void *v33;
  void *pItemList;

  v5 = NewSpecific(jmsCmdListItem_s, pCmdList->ItemCnt);
  pItemList = v5;
  v6 = NewSpecific(System_Func_object__object__int_, 6u);
  v7 = Allocate(System_Func_object__object__int_);
  object__int____ctor(v7, 0, Method_Project_jmsCmdMenu_CmdListSortCallbackA__, 0);
  v6[4] = v7;
  v8 = Allocate(System_Func_object__object__int_);
  object__int____ctor(v8, 0, Method_Project_jmsCmdMenu_CmdListSortCallbackB__, 0);
  v6[5] = v8;
  v9 = Allocate(System_Func_object__object__int_);
  object__int____ctor(v9, 0, Method_Project_jmsCmdMenu_CmdListSortCallbackC__, 0);
  v6[6] = v9;
  v10 = Allocate(System_Func_object__object__int_);
  object__int____ctor(v10, 0, Method_Project_jmsCmdMenu_CmdListSortCallbackA_R__, 0);
  v6[7] = v10;
  v11 = Allocate(System_Func_object__object__int_);
  object__int____ctor(v11, 0, Method_Project_jmsCmdMenu_CmdListSortCallbackB_R__, 0);
  v6[8] = v11;
  v12 = Allocate(System_Func_object__object__int_);
  object__int____ctor(v12, 0, Method_Project_jmsCmdMenu_CmdListSortCallbackC_R__, 0);
  v6[9] = v12;
  v33 = pCmdList;
  p_pHead = &pCmdList->pHead;
  pHead = pCmdList->pHead;
  if (pHead)
  {
    v15 = 0;
    m_Items = v5;
    do
    {
      v17 = Allocate(jmsCmdListItem_s);
      _ctor(v17, 0);
      v20 = pHead;
      pHead = pHead->pNext;
      ++v15;
    }
    while (pHead);
  }
  else
  {
    v15 = 0;
  }
  v21 = Type + 3;
  if (!Mode)
    v21 = Type;
  Sort_object_(v5, v15, v6[v21 + 4]);
  CmdListRecalcLinkList(&pItemList, v15);
  p_pCurrent = &v33->pCurrent;
  pCurrent = v33->pCurrent;
  if (pCurrent)
  {
    do
    {
      v25 = pCurrent;
      pCurrent = pCurrent->pPrev;
    }
    while (pCurrent);
    p_pHead = v25;
    pNext = p_pCurrent;
    if (!p_pCurrent)
      goto LABEL_20;
  }
  else
  {
    p_pHead = 0;
    pNext = p_pCurrent;
    if (!p_pCurrent)
    {
LABEL_20:
      v27 = 0;
      goto LABEL_21;
    }
  }
  do
  {
    v27 = pNext;
    pNext = pNext->pNext;
  }
  while (pNext);
LABEL_21:
  v33->pTail = v27;
  v28 = v33->pHead;
  v33->pListTop = v28;
  v29 = v33->pHead;
  v33->pCurrent = v29;
  v33->ItemOfs = 0;
}

// 0x1c9b100
void jmsCreateCmdMenuMover(void *pMover) {
  s32 *pItem;
  s64 v4;
  s64 v5;
  void *v6;

  pItem = pMover->pItem;
  if (pItem[6] >= 1)
  {
    v4 = 0;
    v5 = 8;
    do
    {
      v6 = Allocate(jmsCmdMenuMoverCore_t);
      _ctor(v6, 0);
      if (v6)
      {
        QueryInterface(v6, *(void **)(*(u64 *)pItem + 64));
      }
      *(u64 *)&pItem[v5] = v6;
      ++v4;
      v5 += 2;
      pItem = pMover->pItem;
    }
    while (v4 < pItem[6]);
  }
}

// 0x1c9b1e0
void jmsDestroyCmdMenuMover(void *pMover) {
  ;
}

// 0x1c9b1f0
void jmsSetCmdMenuToMover(u32 Type, void *pCmdMenu, void *pMover) {
  void *pItem;
  s64 ItemCnt;
  void *v6;

  pItem = pMover->pItem;
  ItemCnt = pMover->ItemCnt;
  if (SLODWORD(pItem->max_length) < ItemCnt)
  {
    pMover->ItemCnt = ItemCnt + 1;
    v6 = pItem[ItemCnt];
    v6->pCmdMenu = pCmdMenu;
    v6 = ((char *)v6 + 32);
    LODWORD(v6[-1].pCmdMenu) = Type;
  }
}

// 0x1c9b230
void jmsDelCmdMenuFromMover(void *pMover, u32 Index) {
  s64 v5;
  void *pItem;
  void *v7;
  void *pCmdList;
  void *v9;
  u32 ItemCnt;
  u32 v11;
  s64 v12;
  signed s32 v13;
  void *v14;
  void *v15;
  Il2CppClass **v16;
  void *v17;
  void *v18;
  void *v19;

  v5 = Index;
  pItem = pMover->pItem;
  if (SLODWORD(pItem->max_length) < (s64)Index)
  {
    v7 = pItem[Index];
    if (v7->Type)
    {
      pCmdList = v7->pCmdMenu->pCmdList;
      while (jmsDelCmdListItem(pCmdList))
        ;
      v7 = pMover->pItem[v5];
    }
    v7->pCmdMenu = 0;
    v9 = pMover;
    ItemCnt = pMover->ItemCnt;
    v11 = ItemCnt - 1;
    v12 = (s32)(ItemCnt - 1);
    if (v12 > v5)
    {
      v13 = ItemCnt - 2;
      do
      {
        v15 = pMover->pItem;
        v16 = &v15->obj.klass + v12;
        v18 = v16[4];
        v17 = (v16 + 4);
        v19 = Allocate(jmsCmdMenuMoverCore_t);
        _ctor_25914976(v19, v18, 0);
        v17 = v19;
        v14 = pMover->pItem[v12];
        v14->pCmdMenu = 0;
        v12 = v13--;
      }
      while (v12 > v5);
      v9 = pMover;
      v11 = pMover->ItemCnt - 1;
    }
    v9->ItemCnt = v11;
  }
}

// 0x1c9b3b0
void jmsDrawCmdMenuMover(u32 Z, void *pMover, u32 OtNo) {
  s64 v8;
  s32 v9;
  void *v10;

  if (pMover->ItemCnt)
  {
    v8 = 0;
    v9 = 1;
    do
    {
      v10 = pMover->pItem[v8];
      jmsDrawCmdMenu(v10->X, v10->Y, Z, &v10->pCmdMenu, OtNo);
      v8 = v9++;
    }
    while (v8 < pMover->ItemCnt);
  }
}

// 0x1c9b430
void jmsUpdateCmdMenuMover(void *pMover) {
  void *pItem;
  s64 v5;
  void *v6;
  u32 Timer;
  void *pMovera;

  pItem = pMover->pItem;
  pMovera = pMover;
  if (SLODWORD(pItem->max_length) >= 1)
  {
    v5 = 0;
    do
    {
      while (1)
      {
        v6 = pItem[v5];
        Timer = v6->Timer;
        if (Timer)
          break;
        jmsDelCmdMenuFromMover(pMovera, v5);
        pItem = pMover->pItem;
        if (++v5 >= SLODWORD(pItem->max_length))
          return;
      }
      v6->Timer = Timer - 64;
      ++v5;
    }
    while (v5 < SLODWORD(pItem->max_length));
  }
}

// 0x1c9b4c0
void jmsInitCmdMenuManager(void *pHandle) {
  void *v3;

  v3 = pHandle;
  v3->pDst = 0;
  v3 = ((char *)v3 + 48);
  *(u64 *)&v3[-1].DstTimer = 0x20000000000LL;
  pHandle->DstTimer = 0;
}

// 0x1c9b500
void jmsSetCmdMenuManager(void *pCmdMenu, void *pHandle) {
  void *v4;
  void *v5;
  void *p_pDst;

  v4 = pHandle;
  *(u64 *)&pHandle->SrcScrollBarFlag = 0x20000000000LL;
  v5 = pCmdMenu;
  if (pCmdMenu)
  {
    v5->Cursor->Timer = 512;
    v5->Flag |= 4u;
  }
  v4->pDst = v5;
  p_pDst = &v4->pDst;
  *((u32 *)p_pDst + 2) = 0;
}

// 0x1c9b540
void jmsResetCmdMenuManager(void *pHandle) {
  void *v3;

  v3 = pHandle;
  v3->pDst = 0;
  v3 = ((char *)v3 + 48);
  *(&v3[-1].DstTimer + 1) = 512;
  pHandle->DstTimer = 0;
}

// 0x1c9b580
void jmsDrawCmdMenuManager(s32 X, s32 Y, s32 Z, void *pHandle, u32 OtNo) {
  void *v7;
  s32 SrcTimer;
  void *Src;
  void *SrcScrollBar;
  s32 v15;
  void *p_pDst;
  void *v17;
  void *pDst;
  void *v20;
  s32 DstTimer;

  v7 = pHandle;
  SrcTimer = v7->SrcTimer;
  if (SrcTimer <= 511)
  {
    Src = v7->Src;
    SrcScrollBar = v7->SrcScrollBar;
    Src->pScrollBar = SrcScrollBar;
    Src = ((char *)Src + 80);
    LODWORD(Src[-1].Title) = 256 - SrcTimer / 2;
    v7 = pHandle;
    v15 = pHandle->SrcTimer;
    if (v15 >= 512)
    {
      if (v15 < 513)
        goto LABEL_8;
    }
    else
    {
      v15 += 100;
    }
    if (v15 >= 512)
      v15 = 512;
    v7->SrcTimer = v15;
  }
LABEL_8:
  pDst = v7->pDst;
  p_pDst = &v7->pDst;
  v17 = pDst;
  pDst->AlphaRate = *((u32 *)p_pDst + 2) / 2;
  if (!pDst->Cursor->Timer)
    v17->Flag &= ~4u;
  jmsDrawCmdMenu(X, Y, Z, p_pDst, OtNo);
  v20 = pHandle;
  DstTimer = pHandle->DstTimer;
  if (DstTimer >= 512)
  {
    if (DstTimer < 513)
      goto LABEL_16;
  }
  else
  {
    DstTimer += 80;
  }
  if (DstTimer >= 512)
    DstTimer = 512;
  v20->DstTimer = DstTimer;
LABEL_16:
  jmsDrawCmdMenu(X, Y, Z, &v20->pDst, OtNo);
}
