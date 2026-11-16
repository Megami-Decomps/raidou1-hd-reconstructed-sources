#include "types.h"
#include "SKLID.h"
#include "dat_str_ref.h"
#include "frname.h"
#include "itf.h"
#include "localize.h"
#include "sbtl.h"
#include "sbtlsm.h"

typedef struct SBTLSM_LISTWORK SBTLSM_LISTWORK;
typedef struct SBTLSM_WORK SBTLSM_WORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct sBtlSM_Prio_t sBtlSM_Prio_t;

struct sBtlSM_Prio_t {
    SBTLSM Mode;
    s32 Prio;
};

static sBtlSM_Prio_t *PrioTable[15];

static bool DrawText(s32 x, s32 y, SBTLSM_WORK *dwk, bool fst);
static void SetVar(SBTLSM_WORK *dwk);
static s32 GetMessagePrio(SBTLSM Mode);
static void DeleteMessage(SBTLSM_LISTWORK *pList, SBTLSM_WORK *pData);
static void InfoClr(void);
static bool DrawTextFont(s32 x, s32 y, s32 z, u32 rgba, s32 mode, bool fst);
static bool OmikujiDrawTextFont(s32 x, s32 y, s32 z, s32 p_w, u32 rgba, u32 p_rgba, s32 mode);

// 0x21276c0
static bool DrawText(s32 x, s32 y, SBTLSM_WORK *dwk, bool fst) {
  s32 ofs_x;
  s32 ofs_y;
  s32 mode;

  ofs_x = dwk->ofs_x;
  ofs_y = dwk->ofs_y;
  mode = dwk->mode;
  DrawTextFont(ofs_x + x, ofs_y + y, (s32)dwk, fst, mode, fst);
  return 1;
}

// 0x2127bc0
static void SetVar(SBTLSM_WORK *dwk) {
  s32 mode;
  char *v4;
  char *v5;
  char *v6;
  char **v7;
  char *v8;
  s32 sklid;
  char *LocalizeText;
  char *v11;
  s32 devilid;
  char *v14;
  char **p_fontbuff;
  s32 raceid;
  char *v17;
  char *fontbuff;
  char *v19;
  char *v20;
  char **v21;
  char *v22;
  char *v23;
  Il2CppObject *v24;
  char *v25;
  char **p_fontbuff2;
  char *v27;
  char *v28;
  char *v29;
  char *v30;
  s32 data;

  frSetVariableRequest(0, "");
  frSetVariableRequest(1, "");
  mode = dwk->mode;
  if (mode <= 62)
  {
    if (mode <= 47)
    {
      if ((u32)mode <= 0x2F && ((1 << mode) & 0xE00000000C00LL) != 0)
        goto LABEL_24;
    }
    else
    {
      if ((u32)(mode - 53) > 0xFFFFFFFD)
      {
        raceid = dwk->raceid;
        if (raceid >= 12)
          raceid += 34;
        v17 = RCNAME(raceid);
        dwk->fontbuff = v17;
        fontbuff = dwk->fontbuff;
        frSetVariableRequest(0, fontbuff);
        v19 = DVNAME(dwk->devilid);
        goto LABEL_42;
      }
      if (mode == 62)
        goto LABEL_24;
    }
LABEL_32:
    if ((char)dwk->side < 0)
      return;
LABEL_33:
    devilid = dwk->devilid;
LABEL_34:
    v14 = DVNAME(devilid);
LABEL_35:
    dwk->fontbuff = v14;
    p_fontbuff = &dwk->fontbuff;
    v11 = *p_fontbuff;
LABEL_31:
    frSetVariableRequest(0, v11);
    return;
  }
  if ((u32)mode <= 0x46)
  {
    if ((mode | 4) != 0x46)
      goto LABEL_32;
LABEL_24:
    sklid = dwk->sklid;
    if (sklid == 375)
    {
      LocalizeText = GetLocalizeText("CMP_USE_MSG_L0028", 1);
    }
    else
    {
      LocalizeText = SKNAME(sklid);
    }
    dwk->fontbuff = LocalizeText;
    v11 = dwk->fontbuff;
    goto LABEL_31;
  }
  switch (mode)
  {
    case 161:
      if ((dwk->exsts & 2) == 0 && (dwk->status & 0x100000) == 0)
      {
        v22 = DVNAME(dwk->devilid);
        dwk->fontbuff = v22;
        v23 = dwk->fontbuff;
        frSetVariableRequest(0, v23);
        data = dwk->lv;
        v24 = Box(s32, &data);
        v25 = Format("{0}", v24, 0);
        dwk->fontbuff2 = v25;
        p_fontbuff2 = &dwk->fontbuff2;
        frSetVariableRequest(1, *p_fontbuff2);
        return;
      }
      v29 = DVNAME(dwk->devilid);
      dwk->fontbuff = v29;
      v30 = dwk->fontbuff;
      frSetVariableRequest(0, v30);
      v19 = GetLocalizeText("SYSMES_L0162", 1);
      break;
    case 162:
      v27 = ITNAME(dwk->sklid);
      dwk->fontbuff = v27;
      v28 = dwk->fontbuff;
      frSetVariableRequest(0, v28);
      v20 = "1";
      dwk->fontbuff2 = "1";
      v21 = &dwk->fontbuff2;
      goto LABEL_43;
    case 163:
      v14 = ToString((s32)dwk + 52, 0);
      goto LABEL_35;
    case 164:
    case 165:
      return;
    case 183:
      if (((char)dwk->side & 0x80000000) == 0)
        goto LABEL_33;
      devilid = 241;
      goto LABEL_34;
    case 185:
      goto LABEL_12;
    case 186:
    case 187:
      if (((char)dwk->side & 0x80000000) == 0)
      {
        v4 = DVNAME(dwk->devilid);
        dwk->fontbuff = v4;
        v5 = dwk->fontbuff;
        frSetVariableRequest(0, v5);
      }
LABEL_12:
      v6 = SKNAME(dwk->sklid);
      dwk->fontbuff = v6;
      v7 = &dwk->fontbuff;
      v8 = *v7;
      frSetVariableRequest(1, v8);
      return;
    default:
      goto LABEL_32;
  }
LABEL_42:
  v20 = v19;
  dwk->fontbuff2 = v19;
  v21 = &dwk->fontbuff2;
LABEL_43:
  frSetVariableRequest(1, *v21);
}

// 0x2128090
static s32 GetMessagePrio(SBTLSM Mode) {
  s64 v4;
  Il2CppClass **v5;
  Il2CppClass *v6;
  sBtlSM_Prio_t *PrioTable_local;

  v4 = 0;
  do
  {
    PrioTable_local = PrioTable;
    if (v4 >= SLODWORD(PrioTable_local->max_length))
      return 0;
    PrioTable_local = PrioTable;
    v5 = &PrioTable_local->obj.klass + v4++;
    v6 = v5[4];
  }
  while (LODWORD(v6->_1.name) != Mode);
  return HIDWORD(v6->_1.name);
}

// 0x21281a0
static void DeleteMessage(SBTLSM_LISTWORK *pList, SBTLSM_WORK *pData) {
  SBTLSM_WORK *next;
  SBTLSM_WORK *prev;
  s32 v8;

  if (pData && pList->num)
  {
    prev = pData->prev;
    next = pData->next;
    if (pData->mode == 72)
    {
      wk->status5 &= ~0x40u;
    }
    if (prev)
    {
      prev->next = next;
    }
    if (next)
    {
      next->prev = prev;
    }
    v8 = pList->num - 1;
    pList->num = v8;
    if (v8)
    {
      if (!prev)
      {
        pList->dwk = next;
      }
    }
    else
    {
      pList->dwk = 0;
    }
  }
}

// 0x21282b0
bool sBtlAddMessage(SBTLSM_LISTWORK *pList, SBTLSM_WORK *pData, SBTLSM Mode, bool duplication) {
  SBTLSM_WORK *p_dwk;
  SBTLSM_WORK *dwk;
  s32 MessagePrio;
  SBTLSM_WORK *next;
  SBTLSM_WORK *v14;
  SBTLSM_WORK *v15;
  s32 v16;
  s32 v17;
  s32 v18;
  s32 v19;
  SBTLSM_WORK *v20;
  SBTLSM_WORK *p_prev;
  SBTLSM_WORK *prev;
  f32 v23;
  f32 v24;
  s32 v25;
  SBTLSM_WORK *v27;
  SBTLSM_WORK *v28;

  p_dwk = &pList->dwk;
  dwk = pList->dwk;
  MessagePrio = GetMessagePrio(Mode);
  next = dwk;
  do
  {
    v14 = next;
    next = next->next;
  }
  while (next);
  v15 = dwk->next;
  if (!v15)
  {
LABEL_27:
    v20 = dwk->next;
    dwk->next = pData;
    pData->prev = dwk;
    pData->next = v20;
    if (!v20)
    {
LABEL_30:
      ++pList->num;
LABEL_31:
      prev = pData->prev;
      if (prev)
      {
        if (prev->mode < 1)
          v23 = 0.25;
        else
          v23 = 0.5;
        v24 = (f32)prev->cmpcounter * v23;
        v25 = v24;
        if (v24 == INFINITY)
          v25 = 0x80000000;
        prev->cmpcounter = v25;
      }
      else
      {
        p_dwk = pData;
      }
      return 1;
    }
    v20->prev = pData;
    p_prev = &v20->prev;
LABEL_29:
    goto LABEL_30;
  }
  if (MessagePrio)
  {
    while (1)
    {
      v16 = v15->mode;
      v17 = GetMessagePrio(v16);
      if (!v17 || v17 >= MessagePrio)
        break;
      v15 = v15->next;
      if (!v15)
        goto LABEL_26;
    }
    v27 = v15->prev;
    if (v17 != MessagePrio)
    {
      if (v27)
      {
        v27->next = pData;
      }
      pData->prev = v27;
      pData->next = v15;
      v15->prev = pData;
      p_prev = &v15->prev;
      goto LABEL_29;
    }
LABEL_45:
    v28 = v15->next;
    if (v27)
    {
      v27->next = pData;
    }
    pData->prev = v27;
    pData->next = v28;
    if (v28)
    {
      v28->prev = pData;
    }
    goto LABEL_31;
  }
  if (!duplication)
  {
    while (1)
    {
      v19 = v15->mode;
      if (!GetMessagePrio(v19))
        break;
      v15 = v15->next;
      if (!v15)
      {
LABEL_26:
        dwk = v14;
        goto LABEL_27;
      }
    }
LABEL_44:
    v27 = v15->prev;
    goto LABEL_45;
  }
  while (1)
  {
    v18 = v15->mode;
    if (v18 == Mode)
      return 0;
    if (!GetMessagePrio(v18))
      goto LABEL_44;
    v15 = v15->next;
    if (!v15)
      goto LABEL_26;
  }
}

// 0x2128570
SBTLSM_LISTWORK *sBtlCreateSMList(void) {
  SBTLSM_LISTWORK *v1;

  v1 = (SBTLSM_LISTWORK *)Allocate(SBTLSM_LISTWORK);
  _ctor(v1, 0);
  v1->num = 0;
  v1->dwk = 0;
  return v1;
}

// 0x21285e0
SBTLSM_WORK *sBtlCreateSM(SBTLSM_LISTWORK *lwk, SBTLUNIT_WORK *wk, SBTLSM mode, SKLID sklid, bool duplication, s32 cmpcounter) {
  SBTLSM_WORK *v13;
  s32 ListID;
  sdatUnitWork_t *para;
  s32 level;
  s32 raceid;
  s64 v20;

  if (lwk->bLock)
    return 0;
  v13 = Allocate(SBTLSM_WORK);
  v13->prev = 0;
  v13->next = 0;
  if (!lwk->dwk)
  {
    lwk->dwk = v13;
    lwk->num = 1;
    if (wk)
    {
LABEL_13:
      ListID = wk->ListID;
      v13->mode = mode;
      v13->listID = ListID;
      para = wk->para;
      level = para->level;
      raceid = para->raceid;
      LODWORD(para) = para->devilid;
      v20 = *(u64 *)&wk->status;
      v13->raceid = raceid;
      v13->devilid = (u32)para;
      v13->lv = level;
      *(u64 *)&v13->status = v20;
      if (!sklid)
        sklid = wk->actwk->use_skillid;
      v13->sklid = sklid;
      v13->side = wk->side;
      goto LABEL_16;
    }
LABEL_10:
    v13->mode = mode;
LABEL_16:
    v13->cmpcounter = cmpcounter;
    *(u64 *)&v13->ofs_x = 0;
    v13->gstat = 0;
    return v13;
  }
  if (sBtlAddMessage(lwk, v13, mode, duplication))
  {
    if (wk)
      goto LABEL_13;
    goto LABEL_10;
  }
  return 0;
}

// 0x2128770
bool Proc(SBTLSM_LISTWORK *lwk) {
  SBTLSM_WORK *dwk;
  bool result;
  s32 gstat;
  s32 cmpcounter;

  if (!lwk)
    return 0;
  dwk = lwk->dwk;
  if (!dwk || !lwk->num)
    return 0;
  if (wk->kaiwaflg)
    goto LABEL_24;
  if ((wk->status & 0x8000000) == 0)
    goto LABEL_17;
  if (dwk->mode == 71)
    goto LABEL_17;
  return 0;
LABEL_17:
  if ((wk->status2 & 0xA) != 0)
  {
    InfoClr();
    return 0;
  }
LABEL_24:
  gstat = dwk->gstat;
  if (gstat == 1)
  {
    if (!lwk->bLock)
      ++dwk->counter;
    cmpcounter = dwk->cmpcounter;
    LimitRange(&dwk->counter, 0, cmpcounter);
    if (dwk->counter >= dwk->cmpcounter)
    {
      DeleteMessage(lwk, dwk);
    }
    return 1;
  }
  if (gstat)
    return 1;
  dwk->alpha += 12;
  LimitRange(&dwk->alpha, 0, 128);
  result = 1;
  if (dwk->alpha >= 128)
    dwk->gstat = 1;
  return result;
}

// 0x2128ae0
bool Draw(SBTLSM_LISTWORK *lwk) {
  SBTLSM_WORK *dwk;
  u32 status4;
  s32 mode;
  s32 v9;
  s32 v10;
  s32 gstat;
  s32 v12;
  u32 v13;
  s32 ofs_x;
  s32 ofs_y;
  s32 v18;
  s32 v21;
  u32 v22;
  s32 v25;
  s32 v26;
  s32 v27;

  if (!lwk)
    return 0;
  dwk = lwk->dwk;
  if (!dwk || !lwk->num)
  {
LABEL_26:
    InfoClr();
    return 0;
  }
  status4 = wk->status4;
  if ((status4 & 0x2000) != 0)
  {
    status4 = wk->status4;
    wk->status4 = status4 & 0xFFFFDFFF;
    goto LABEL_26;
  }
  mode = dwk->mode;
  if (wk->cmbSkl->bRun)
    v9 = -200;
  else
    v9 = 200;
  switch (mode)
  {
    case 54:
    case 55:
    case 59:
    case 60:
    case 74:
    case 158:
    case 159:
    case 160:
    case 161:
    case 162:
    case 163:
      v9 -= 100;
      break;
    default:
      break;
  }
  if (mode == 73)
    v10 = v9 - 100;
  else
    v10 = v9;
  gstat = dwk->gstat;
  if (gstat != 1)
  {
    if (!gstat)
    {
      SetVar(dwk);
      ofs_x = dwk->ofs_x;
      ofs_y = dwk->ofs_y;
      v18 = dwk->mode;
      DrawTextFont(ofs_x, ofs_y + v10, v12, v13, v18, 1);
      return 1;
    }
    InfoClr();
    return 1;
  }
  SetVar(dwk);
  v25 = dwk->ofs_x;
  v26 = dwk->ofs_y;
  v27 = dwk->mode;
  DrawTextFont(v25, v26 + v10, v21, v22, v27, 0);
  return 1;
}

// 0x21289d0
static void InfoClr(void) {
  void *Instance;
  void *v4;

  Instance = get_Instance(0);
  if (!op_Inequality(Instance, 0, 0))
    return;
  v4 = get_Instance(0);
  InfoTextClr(v4, 0);
}

// 0x2128df0
bool sBtlReleaseSM_List(SBTLSM_LISTWORK *lwk, u8 flg) {
  SBTLSM_LISTWORK *v3;
  SBTLSM_WORK *p_dwk;
  SBTLSM_WORK *dwk;
  SBTLSM_WORK *prev;
  SBTLSM_WORK *v7;
  SBTLSM_WORK *next;
  SBTLSM_WORK *v9;
  SBTLSM_WORK *v10;
  SBTLSM_WORK *v11;
  SBTLSM_WORK *v12;
  SBTLSM_WORK *v13;
  SBTLSM_WORK *v14;
  SBTLSM_WORK *v15;
  SBTLSM_WORK *v16;
  SBTLSM_WORK *v17;

  if (lwk)
  {
    v3 = lwk;
    p_dwk = &lwk->dwk;
    dwk = lwk->dwk;
    if (dwk && lwk->num)
    {
      if (flg)
      {
        while (1)
        {
          prev = dwk->prev;
          dwk->gstat = 2;
          if (prev)
            break;
          v9 = 0;
          next = dwk->next;
          if (next)
            goto LABEL_9;
LABEL_10:
          if (!v9)
          {
            v10 = dwk->next;
            p_dwk = v10;
            v11 = p_dwk;
            if (p_dwk)
            {
              v11->prev = 0;
            }
          }
          dwk = dwk->next;
          --v3->num;
          if (!dwk)
            goto LABEL_28;
        }
        v7 = dwk->next;
        prev->next = v7;
        v9 = dwk->prev;
        next = dwk->next;
        if (!next)
          goto LABEL_10;
LABEL_9:
        next->prev = v9;
        v9 = dwk->prev;
        goto LABEL_10;
      }
      while (1)
      {
        while (dwk->gstat != 2)
        {
          dwk = dwk->next;
          if (!dwk)
            goto LABEL_28;
        }
        v12 = dwk->prev;
        if (v12)
          break;
        v15 = 0;
        v14 = dwk->next;
        if (v14)
          goto LABEL_19;
LABEL_20:
        if (!v15)
        {
          v16 = dwk->next;
          p_dwk = v16;
          v17 = p_dwk;
          if (p_dwk)
          {
            v17->prev = 0;
          }
        }
        dwk = dwk->next;
        --v3->num;
        if (!dwk)
        {
LABEL_28:
          LOBYTE(lwk) = 1;
          return (char)lwk;
        }
      }
      v13 = dwk->next;
      v12->next = v13;
      v15 = dwk->prev;
      v14 = dwk->next;
      if (!v14)
        goto LABEL_20;
LABEL_19:
      v14->prev = v15;
      v15 = dwk->prev;
      goto LABEL_20;
    }
    LOBYTE(lwk) = 0;
  }
  return (char)lwk;
}

// 0x2128f60
bool sBtlDeleteSMList(SBTLSM_LISTWORK *lwk) {
  sBtlReleaseSM_List(lwk, 1u);
  return 1;
}

// 0x2127760
static bool DrawTextFont(s32 x, s32 y, s32 z, u32 rgba, s32 mode, bool fst) {
  char *v7;
  char *v8;
  char *v9;
  char **v10;
  char *LocalizeText;
  char *v12;
  char *VariableRequest;
  char *v14;
  char *v15;
  char *v16;
  char *v17;
  char *v18;
  char *v19;
  char *v20;
  char *v21;
  char *v22;
  char *v23;
  void *Instance;
  void *v27;
  void *v28;
  s32 v33;

  v33 = mode;
  v7 = ToString_55996800((s32)&v33, "d4", 0);
  v8 = Concat_54766928("SYSMES_L", v7, 0);
  if (v33 == 163)
  {
    v10 = &"MAP_COM_L0044";
  }
  else
  {
    v9 = v8;
    if (v33 != 162)
      goto LABEL_10;
    v10 = &"MAP_COM_L0043";
  }
  v9 = *v10;
LABEL_10:
  LocalizeText = GetLocalizeText(v9, 1);
  v12 = Replace_54838864(LocalizeText, "<FONT 0>", "", 0);
  VariableRequest = frGetVariableRequest(0);
  v14 = Replace_54838864(v12, "<V 0>", VariableRequest, 0);
  v15 = frGetVariableRequest(1);
  v16 = Replace_54838864(v14, "<V 1>", v15, 0);
  v17 = frGet1NString();
  v18 = Replace_54838864(v16, "<NAME1N 0>", v17, 0);
  v19 = Replace_54838864(v18, "<COLOR 0>", "<color=#ffffff>", 0);
  v20 = Replace_54838864(v19, "<COLOR 1>", "<color=#ffffff>", 0);
  v21 = Replace_54838864(v20, "<COLOR 2>", "<color=#ffffff>", 0);
  v22 = Replace_54838864(v21, "<COLOR 3>", "<color=#ffffff>", 0);
  v23 = Replace_54838864(v22, "<COLOR 4>", "<color=#ffffff>", 0);
  Instance = get_Instance(0);
  if (!op_Inequality(Instance, 0, 0))
    return 0;
  if (wk->endcnt)
    return 0;
  if ((wk->status2 & 0xA) != 0)
    return 0;
  v27 = get_Instance(0);
  SetInfoPos(v27, x, y, 0);
  v28 = get_Instance(0);
  InfoTextSet(v28, v23, fst, 0);
  return 0;
}

// 0x2128fd0
bool sBtlUnDramDrawTextFont(s32 x, s32 y, s32 z, s32 p_w, u32 rgba, u32 p_rgba, s32 mode, s32 num) {
  return 0;
}

// 0x2128fe0
void sBtlUnDramDrawText(s32 x, s32 y, s32 w, s32 mode, s32 col, s32 pcol, s32 num) {

}

// 0x2129040
static bool OmikujiDrawTextFont(s32 x, s32 y, s32 z, s32 p_w, u32 rgba, u32 p_rgba, s32 mode) {
  return 0;
}

// 0x2129050
void sBtlOmikujiDrawText(s32 x, s32 y, s32 w, s32 mode, s32 col, s32 pcol) {

}
