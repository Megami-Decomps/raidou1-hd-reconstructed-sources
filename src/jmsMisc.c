#include "types.h"
#include "dds3_pad.h"
#include "jmscmdmenu.h"
#include "jmsmisc.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct jmsSeqHandle_t jmsSeqHandle_t;
typedef struct jmsSeqUnit_t jmsSeqUnit_t;

char *szSeqNameNull;

static void CalcSeqHandle(s32 Mode, jmsSeqUnit_t *pSeqUnit, jmsSeqHandle_t *pSeqHandle, dds3ProcessID_t *ID);

// 0x1cefe10
void jmsInitSeqHandle(jmsSeqHandle_t *pSeqHandle) {
  Il2CppObject *v2;
  void *v3;
  Il2CppClass *v4;

  v2 = Allocate(jmsSeqHandle_t);
  v3 = NewSpecific(jmsSeqUnit_t, 0x10u);
  v2[1].monitor = v3;
  v4 = NewSpecific(jmsSeqUnit_t, 2u);
  v2[2].klass = v4;
  _ctor(v2, 0);
}

// 0x1cefed0
static void CalcSeqHandle(s32 Mode, jmsSeqUnit_t *pSeqUnit, jmsSeqHandle_t *pSeqHandle, dds3ProcessID_t *ID) {
  jmsSeqHandle_t *v5;
  s32 UnitCnt;
  s32 v9;
  jmsInt32Delegate pDestroy;
  jmsInt32Delegate pInit;
  s64 v13;
  s64 v14;
  jmsSeqUnit_t *pUnit;
  Il2CppClass **v16;
  s32 v17;
  jmsSeqUnit_t *v18;
  void **v19;
  jmsSeqUnit_t *v20;
  void *v21;
  jmsSeqHandle_t *v22;
  jmsSeqUnit_t *v23;
  char *v24;

  v5 = pSeqHandle;
  if (pSeqHandle)
  {
    if (Mode)
    {
      if ((u32)(Mode - 3) >= 0xFFFFFFFE)
      {
        UnitCnt = v5->UnitCnt;
        if (UnitCnt)
        {
          v9 = UnitCnt - 1;
          if (Mode == 1)
          {
            pDestroy = v5->pUnit[v9]->pDestroy;
            if (pDestroy)
            {
              (pDestroy->invoke_impl)(pDestroy->method_code, ID, pDestroy->ID);
              v5 = pSeqHandle;
              v9 = pSeqHandle->UnitCnt - 1;
            }
          }
          v5->UnitCnt = v9;
        }
      }
    }
    else
    {
      pInit = pSeqUnit->pInit;
      if (pInit)
      {
        if (pSeqUnit->pDestroy)
        {
          LODWORD(v13) = v5->UnitCnt;
          if ((s32)v13 < 1)
          {
LABEL_15:
            pUnit = v5->pUnit;
            v5->UnitCnt = v13 + 1;
            v16 = &pUnit->obj.klass + (s32)v13;
            v16[4] = pSeqUnit;
            if ((pSeqUnit->Stat & 0x20000) != 0)
            {
              v17 = pSeqHandle->UnitCnt;
              if (v17 >= 2)
              {
                v18 = pSeqHandle->pUnit;
                v19 = &v18[v17 - 1];
                v20 = v18[v17 - 2];
                v21 = *v19;
                sub_C80(v18, v20);
                *v19 = v20;
                v22 = pSeqHandle;
                v23 = pSeqHandle->pUnit;
                LODWORD(v19) = v22->UnitCnt;
                sub_C80(v23, v21);
                v24 = (char *)v23 + 8 * (s32)v19 - 16;
                *((u64 *)v24 + 4) = v21;
              }
            }
            (pSeqUnit->pInit->invoke_impl)(pSeqUnit->pInit->method_code, ID, pSeqUnit->pInit->method);
          }
          else
          {
            v14 = 0;
            while (!op_Equality(pSeqUnit->pInit, v5->pUnit[v14]->pInit, 0))
            {
              v5 = pSeqHandle;
              ++v14;
              v13 = pSeqHandle->UnitCnt;
              if (v14 >= v13)
                goto LABEL_15;
            }
          }
        }
        else
        {
          (pInit->invoke_impl)(pInit->method_code, ID, pInit->method);
        }
      }
    }
  }
}

// 0x1cf00d0
void jmsSeqDestroyAll(jmsSeqHandle_t *pSeqHandle, dds3ProcessID_t *ID) {
  s32 i;
  jmsInt32Delegate pDestroy;

  for (i = pSeqHandle->UnitCnt; i; pSeqHandle->UnitCnt = i)
  {
    i = pSeqHandle->UnitCnt;
    if (!i)
      break;
    pDestroy = pSeqHandle->pUnit[--i]->pDestroy;
    if (pDestroy)
    {
      (pDestroy->invoke_impl)(pDestroy->method_code, ID, pDestroy->method);
      i = pSeqHandle->UnitCnt - 1;
    }
  }
}

// 0x1cf0190
s32 jmsChkSeqChange(jmsSeqUnit_t *pSeqUnit) {
  return (LODWORD(pSeqUnit->Stat) >> 21) & 1;
}

// 0x1cdfa50
dds3ProcessFunc_t jmsSeqChange(jmsSeqHandle_t *pSeqHandle, jmsSeqUnit_t *pSeqUnit, s32 Mode, dds3ProcessID_t *ID) {
  dds3ProcessFunc_t v5;
  jmsSeqUnit_t *v9;
  s64 Stat;
  jmsInt32Delegate pCheck;
  s64 v12;
  s32 v13;
  char v14;
  dds3ProcessFunc_t pCalc;
  dds3ProcessFunc_t v18;
  s32 UnitCnt;
  jmsSeqUnit_t *pLastSeqUnit;
  jmsSeqUnit_t *v21;
  jmsSeqUnit_t *v22;
  jmsSeqUnit_t *v23;
  dds3ProcessFunc_t pUpdate;
  jmsSeqHandle_t *pSeqHandlea;

  v5 = (dds3ProcessFunc_t)ID;
  pSeqHandlea = pSeqHandle;
  if (!v5)
    return v5;
  v9 = pSeqUnit;
  if (!pSeqUnit)
    return 0;
  Stat = v9->Stat;
  if ((Stat & 0x400000) != 0)
    return 0;
  if (Mode != 2)
  {
    if (Mode != 1)
    {
      if (!Mode)
      {
        pCheck = v9->pCheck;
        v12 = Stat | 0x100000;
        v9->Stat = v12;
        if (pCheck && (v13 = (pCheck->invoke_impl)(pCheck->method_code, v5, pCheck->ID), v9 = pSeqUnit, v12 = pSeqUnit->Stat, !v13))
        {
          if ((v12 & 0x10001) != 1)
          {
LABEL_34:
            if ((v12 & 1) == 0)
              return 0;
            v9->Stat = v12 | 0x400000;
            pCalc = v9->pCalc;
            goto LABEL_38;
          }
          v14 = 1;
        }
        else
        {
          if ((v12 & 0x10000) != 0)
            goto LABEL_36;
          v14 = 0;
        }
        CalcSeqHandle(0, v9, pSeqHandlea, v5);
        v9 = pSeqUnit;
        v12 = pSeqUnit->Stat | 0x10000;
        pSeqUnit->Stat = v12;
        if ((v14 & 1) != 0)
          goto LABEL_34;
LABEL_36:
        v18 = v9->pCalc;
        v9->Stat = v12 | 0x200000;
        return v18;
      }
      return 0;
    }
    if ((Stat & 0x100000) == 0)
      return 0;
    if ((Stat & 0x200000) != 0)
      return v9->pDraw;
    if ((Stat & 1) == 0)
      return 0;
    v9->Stat = Stat | 0x400000;
    pCalc = v9->pDraw;
LABEL_38:
    (pCalc->invoke_impl)(pCalc->method_code, v5, pCalc->ID);
    pSeqUnit->Stat &= ~0x400000u;
    return 0;
  }
  if ((Stat & 0x100000) == 0)
    return 0;
  if ((Stat & 0x200000) == 0)
  {
    if ((Stat & 1) == 0)
      return 0;
    v9->Stat = Stat | 0x400000;
    pCalc = v9->pUpdate;
    goto LABEL_38;
  }
  if ((Stat & 0x20000) != 0)
  {
    if ((Stat & 0x40000) != 0)
    {
      if (pSeqHandle)
      {
        UnitCnt = pSeqHandle->UnitCnt;
        if (UnitCnt)
          pSeqHandle->UnitCnt = UnitCnt - 1;
      }
    }
    else
    {
      CalcSeqHandle(1, 0, pSeqHandlea, v5);
    }
  }
  pLastSeqUnit = pSeqHandle->pLastSeqUnit;
  v21 = pLastSeqUnit[1];
  pSeqUnit->Stat &= 0xFFFFFFFF0000FFFFLL;
  sub_C80(pLastSeqUnit, v21);
  pLastSeqUnit[0] = v21;
  v22 = pSeqHandle->pLastSeqUnit;
  v23 = pSeqUnit;
  sub_C80(v22, pSeqUnit);
  v22[1] = v23;
  pUpdate = pSeqUnit->pUpdate;
  pSeqUnit = 0;
  return pUpdate;
}

// 0x1cf01a0
s32 jmsSeqChkLast(jmsSeqHandle_t *pSeqHandle, jmsSeqUnit_t *pSeqUnit) {
  return pSeqHandle->pLastSeqUnit[0] == pSeqUnit;
}

// 0x1cea030
void jmsSeqJump(jmsSeqUnit_t *pCurrentSeqUnit, jmsSeqUnit_t *pSeqUnit) {
  jmsSeqUnit_t *v4;

  v4 = pSeqUnit;
  pCurrentSeqUnit = v4;
  pSeqUnit->Stat = LOWORD(pSeqUnit->Stat);
}

// 0x1cdfea0
void jmsSeqJumpAndFree(jmsSeqUnit_t *pCurrentSeqUnit, jmsSeqUnit_t *pSeqUnit) {
  jmsSeqUnit_t *v4;

  v4 = pSeqUnit;
  pCurrentSeqUnit = v4;
  pSeqUnit->Stat = LOWORD(pSeqUnit->Stat) | 0x20000;
}

// 0x1cf01c0
void jmsSeqJumpAndPop(jmsSeqUnit_t **pCurrentSeqUnit, jmsSeqUnit_t *pSeqUnit) {
  jmsSeqUnit_t *v3;
  jmsSeqUnit_t *v5;

  v3 = *pCurrentSeqUnit;
  v5 = pSeqUnit;
  v3[0] = v5;
  pSeqUnit->Stat = LOWORD(pSeqUnit->Stat) | 0x60000;
}

// 0x1cf0230
void jmsSeqReturn(jmsSeqHandle_t *pSeqHandle, jmsSeqUnit_t *pCurrentSeqUnit) {
  jmsSeqUnit_t *pLastSeqUnit;
  jmsSeqUnit_t *target;

  pLastSeqUnit = pSeqHandle->pLastSeqUnit;
  if (pLastSeqUnit)
  {
    target = pLastSeqUnit[0];
    pLastSeqUnit[0]->Stat = LOWORD(pLastSeqUnit[0]->Stat) | 0x20000;
  }
}

// 0x1cf02c0
u32 jmsChkCommonInput(u32 ControlBit) {
  u32 v3;

  if ((ControlBit & 1) != 0)
  {
    v3 = CHECK_TRIG(4096, 0);
    if ((ControlBit & 2) == 0)
      goto LABEL_7;
  }
  else
  {
    v3 = 0;
    if ((ControlBit & 2) == 0)
      goto LABEL_7;
  }
  if (CHECK_TRIG(4097, 1))
    v3 |= 2u;
LABEL_7:
  if ((ControlBit & 0x10) != 0 && (CHECK_REP(4100, 1) || CHECK_TRIG(4100, 1)))
  {
    v3 |= 0x10u;
  }
  if ((ControlBit & 0x20) != 0 && (CHECK_REP(4101, 1) || CHECK_TRIG(4101, 1)))
  {
    v3 |= 0x20u;
  }
  if ((ControlBit & 0x40) != 0 && (CHECK_REP(4102, 1) || CHECK_TRIG(4102, 1)))
  {
    v3 |= 0x40u;
  }
  if ((ControlBit & 0x80) != 0 && (CHECK_REP(4103, 1) || CHECK_TRIG(4103, 1)))
  {
    v3 |= 0x80u;
  }
  if ((ControlBit & 4) != 0)
  {
    if (CHECK_TRIG(4098, 1))
      v3 |= 4u;
    if ((ControlBit & 8) == 0)
    {
LABEL_25:
      if ((ControlBit & 0x200) == 0)
        goto LABEL_36;
      goto LABEL_33;
    }
  }
  else if ((ControlBit & 8) == 0)
  {
    goto LABEL_25;
  }
  if (CHECK_TRIG(4099, 1))
    v3 |= 8u;
  if ((ControlBit & 0x200) != 0)
  {
LABEL_33:
    if (CHECK_REP(4107, 1) || CHECK_TRIG(4107, 1))
      v3 |= 0x200u;
  }
LABEL_36:
  if ((ControlBit & 0x100) != 0 && (CHECK_REP(4104, 1) || CHECK_TRIG(4104, 1)))
  {
    v3 |= 0x100u;
  }
  if ((ControlBit & 0x800) != 0 && (CHECK_REP(4108, 1) || CHECK_TRIG(4108, 1)))
  {
    v3 |= 0x800u;
  }
  if ((ControlBit & 0x400) != 0 && (CHECK_REP(4105, 1) || CHECK_TRIG(4105, 1)))
  {
    v3 |= 0x400u;
  }
  if ((ControlBit & 0x1000) != 0)
  {
    if (CHECK_TRIG(4110, 1))
      v3 |= 0x1000u;
    if ((ControlBit & 0x2000) == 0)
    {
LABEL_50:
      if ((ControlBit & 0x20000) == 0)
        goto LABEL_51;
      goto LABEL_71;
    }
  }
  else if ((ControlBit & 0x2000) == 0)
  {
    goto LABEL_50;
  }
  if (CHECK_TRIG(4111, 1))
    v3 |= 0x2000u;
  if ((ControlBit & 0x20000) == 0)
  {
LABEL_51:
    if ((ControlBit & 0x10000) == 0)
      goto LABEL_52;
    goto LABEL_74;
  }
LABEL_71:
  if (CHECK_TRIG(4107, 1))
    v3 |= 0x20000u;
  if ((ControlBit & 0x10000) == 0)
  {
LABEL_52:
    if ((ControlBit & 0x80000) == 0)
      goto LABEL_53;
    goto LABEL_77;
  }
LABEL_74:
  if (CHECK_TRIG(4104, 1))
    v3 |= 0x10000u;
  if ((ControlBit & 0x80000) == 0)
  {
LABEL_53:
    if ((ControlBit & 0x40000) == 0)
      goto LABEL_54;
    goto LABEL_80;
  }
LABEL_77:
  if (CHECK_TRIG(4108, 1))
    v3 |= 0x80000u;
  if ((ControlBit & 0x40000) == 0)
  {
LABEL_54:
    if ((ControlBit & 0x10) == 0)
      goto LABEL_55;
    goto LABEL_83;
  }
LABEL_80:
  if (CHECK_TRIG(4105, 1))
    v3 |= 0x40000u;
  if ((ControlBit & 0x10) == 0)
  {
LABEL_55:
    if ((ControlBit & 0x20) == 0)
      goto LABEL_56;
    goto LABEL_86;
  }
LABEL_83:
  if (CHECK_PRESS(4100, 1))
    v3 |= 0x100000u;
  if ((ControlBit & 0x20) == 0)
  {
LABEL_56:
    if ((ControlBit & 0x40) == 0)
      goto LABEL_57;
    goto LABEL_89;
  }
LABEL_86:
  if (CHECK_PRESS(4101, 1))
    v3 |= 0x200000u;
  if ((ControlBit & 0x40) == 0)
  {
LABEL_57:
    if ((ControlBit & 0x80) == 0)
      goto LABEL_58;
    goto LABEL_92;
  }
LABEL_89:
  if (CHECK_PRESS(4102, 1))
    v3 |= 0x400000u;
  if ((ControlBit & 0x80) == 0)
  {
LABEL_58:
    if ((ControlBit & 0x40) == 0)
      goto LABEL_59;
    goto LABEL_97;
  }
LABEL_92:
  if (CHECK_PRESS(4103, 1))
    v3 |= 0x800000u;
  if (CHECK_PRESS(4107, 1))
    v3 |= 0x1000000u;
  if ((ControlBit & 0x40) == 0)
  {
LABEL_59:
    if ((ControlBit & 0x80) == 0)
      goto LABEL_60;
LABEL_100:
    if (CHECK_PRESS(4108, 1))
      v3 |= 0x4000000u;
    if ((ControlBit & 0x40) == 0)
      goto LABEL_61;
    goto LABEL_103;
  }
LABEL_97:
  if (CHECK_PRESS(4104, 1))
    v3 |= 0x2000000u;
  if ((ControlBit & 0x80) != 0)
    goto LABEL_100;
LABEL_60:
  if ((ControlBit & 0x40) == 0)
  {
LABEL_61:
    if ((v3 & 1) != 0)
      return v3 & 1;
    else
      return v3;
  }
LABEL_103:
  if (CHECK_PRESS(4105, 1))
    v3 |= 0x8000000u;
  if ((v3 & 1) != 0)
    return v3 & 1;
  else
    return v3;
}

// 0x1cf0700
void jmsPageControlEx(void *pScrollBar, void *pCmdMenu, s32 *pPad) {
  void *pCmdList;
  void *Page;
  void *v8;
  void *pCmdMenua;

  pCmdMenua = pCmdMenu;
  if (!pScrollBar || (pCmdList = pCmdMenu->pCmdList, pCmdList->ItemCnt < pCmdList->DrawItemMax))
  {
    *pPad &= 0xFFFFF3FF;
    return;
  }
  if ((*pPad & 0x400) != 0)
  {
    Page = CmdListItemMovePrevPage(pCmdList);
    if ((*pPad & 0x800) != 0)
    {
LABEL_6:
      v8 = CmdListItemMoveNextPage(pCmdMenu->pCmdList);
      if (!Page)
        goto LABEL_10;
      goto LABEL_11;
    }
  }
  else
  {
    Page = 0;
    if ((*pPad & 0x800) != 0)
      goto LABEL_6;
  }
  v8 = 0;
  if (!Page)
LABEL_10:
    *pPad &= ~0x400u;
LABEL_11:
  if (!v8)
    *pPad &= ~0x800u;
  CmdMenuCursorDrawUnlock(pCmdMenua);
}

// 0x1cf07d0
void jmsPageControl(void *pCmdMenu, s32 pPad) {
  s16 v3;
  void *pScrollBar;
  void *pCmdList;
  void *pCmdMenua;

  v3 = pPad;
  pScrollBar = pCmdMenu->pScrollBar;
  pCmdMenua = pCmdMenu;
  if (!pScrollBar)
    return;
  pCmdList = pCmdMenu->pCmdList;
  if (pCmdList->ItemCnt >= pCmdList->DrawItemMax)
  {
    if ((v3 & 0x400) != 0)
      CmdListItemMovePrevPage(pCmdList);
    if ((v3 & 0x800) != 0)
      CmdListItemMoveNextPage(pCmdMenu->pCmdList);
    CmdMenuCursorDrawUnlock(pCmdMenua);
  }
}

// 0x1cf08b0
void jmsPlaySE(u32 Type, u32 PadBit, void *pCmdList) {
  s16 v4;

  if ((PadBit & 0xC000) != 0)
  {
    SE(13);
    return;
  }
  v4 = PadBit;
  if (PadBit)
  {
    if ((PadBit & 1) != 0)
    {
      SE(0);
      if ((v4 & 2) == 0)
      {
LABEL_7:
        if ((v4 & 0xCF0) == 0)
          return;
LABEL_11:
        if (!pCmdList || (pCmdList->Flag & 3) != 2)
          SE(3);
        return;
      }
    }
    else if ((PadBit & 2) == 0)
    {
      goto LABEL_7;
    }
    SE(1);
    if ((v4 & 0xCF0) == 0)
      return;
    goto LABEL_11;
  }
}
