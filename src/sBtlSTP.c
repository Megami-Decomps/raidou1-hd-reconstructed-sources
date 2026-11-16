#include "types.h"
#include "SBTLSTP_ID.h"
#include "sbtl.h"
#include "sbtlcamera.h"
#include "sbtldraw.h"
#include "sbtlpanel.h"
#include "sbtlplayer.h"
#include "sbtlstp.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sbtlvisual.h"
#include "sdf_vu0.h"
#include "smnr.h"

typedef struct SBTLSTP_LISTWORK SBTLSTP_LISTWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

static bool IsCriticalDisp(SBTLSTP_LISTWORK *lwk, s32 ListID);
static s32 CreateSTP(SBTLSTP_LISTWORK *lwk, s32 ListID, const sdfVector4_t *pos, SBTLSTP_ID id, s32 time, u32 bstf, u32 attr);
static void WeakDispOff(SBTLUNIT_WORK *wk);

// 0x1fbca90
SBTLSTP_LISTWORK *sBtlCreateSTPList(void) {
  SBTLSTP_LISTWORK *v1;

  v1 = (SBTLSTP_LISTWORK *)Allocate(SBTLSTP_LISTWORK);
  _ctor(v1, 0);
  v1->num = 0;
  v1->wk = 0;
  return v1;
}

// 0x1fbcb00
s32 sBtlCreateSTP_Unit(SBTLSTP_LISTWORK *lwk, SBTLUNIT_WORK *wk, SBTLSTP_ID id, s32 time, u32 bstf, u32 attr) {
  SBTLVISUAL_DATA *v13;
  SBTLSTP_WORK *next;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 hithelperreqID;
  SBTLUNIT_WORK *v19;
  s32 v22;
  struct sdfVector4_t pos;
  struct sdfVector4_t v24;

  v13 = Allocate(SBTLVISUAL_DATA);
  if (wk->bTateNoDmg)
    return -1;
  if (id == 2)
  {
    if (wk->eff_wait_kaisin)
      return -1;
    {
      if (lwk)
      {
        next = lwk->wk;
        if (next)
        {
          while (next->ListID != wk->ListID || next->id != 2)
          {
            next = next->next;
            if (!next)
              goto LABEL_19;
          }
          return -1;
        }
      }
    }
  }
LABEL_19:
  if ((wk->status & 0x1000) != 0)
  {
    UnitMng = wk->UnitMng;
    hithelperreqID = wk->hithelperreqID;
    v19 = sBtlSearchUnit_ID(UnitMng, hithelperreqID);
    if (v19)
      goto LABEL_24;
  }
  sBtlGetCylinderData(wk, v13);
  v24 = v13->center;
  vct_A = v24;
  goto LABEL_45;
LABEL_24:
  pos = v19->pos;
  vct_A = pos;
LABEL_45:
  if (time <= 0)
    v22 = 60;
  else
    v22 = time;
  if ((u32)id <= 6 && ((1 << id) & 0x5A) != 0)
    wk->stpflg = 1;
  return CreateSTP(lwk, wk->ListID, vct_A, id, v22, bstf, attr);
}

// 0x1fbcef0
static bool IsCriticalDisp(SBTLSTP_LISTWORK *lwk, s32 ListID) {
  SBTLSTP_WORK *wk;

  if (lwk)
  {
    wk = lwk->wk;
    if (wk)
    {
      while (wk->ListID != ListID || wk->id != 2)
      {
        wk = wk->next;
        if (!wk)
          goto LABEL_3;
      }
      LOBYTE(lwk) = 1;
    }
    else
    {
LABEL_3:
      LOBYTE(lwk) = 0;
    }
  }
  return (char)lwk;
}

// 0x1fbcf30
static s32 CreateSTP(SBTLSTP_LISTWORK *lwk, s32 ListID, const sdfVector4_t *pos, SBTLSTP_ID id, s32 time, u32 bstf, u32 attr) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBTLSTP_WORK *v18;
  SBTLSTP_WORK *wk;
  SBTLSTP_WORK *v20;
  s32 v21;
  bool v24;
  u32 v25;
  f32 *p_x;
  sdfVector4_t *p_pos;
  f32 IntervalRand;
  s32 num;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  if (!lwk)
    return 0;
  v18 = Allocate(SBTLSTP_WORK);
  _ctor(v18, 0);
  v18->prev = 0;
  v18->next = 0;
  wk = lwk->wk;
  if (wk)
  {
    do
    {
      v20 = wk;
      wk = wk->next;
    }
    while (wk);
    v20->next = v18;
    v18->prev = v20;
    v21 = lwk->num + 1;
  }
  else
  {
    lwk->wk = v18;
    v21 = 1;
  }
  lwk->num = v21;
  v24 = attr == 1 && id == 1;
  v18->id = id;
  if (v24)
    v25 = 0x2000;
  else
    v25 = bstf;
  v18->mode = 0;
  v18->ListID = ListID;
  v18->stpBSTF = v25;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  p_pos = &v18->pos;
  *p_pos = vct_A;
  v18->pos.y = v18->pos.y - (f32)GetIntervalRand(0, 20);
  IntervalRand = GetIntervalRand(10, 40);
  v18->counterMax = time;
  num = lwk->num;
  v18->IsSprit = 0;
  v18->spd = IntervalRand * 0.01;
  return num - 1;
}

// 0x1fbd1b0
bool Proc(SBTLSTP_LISTWORK *lwk) {
  SBTLVISUAL_DATA *v3;
  SBTLSTP_WORK *wk_local;
  SBATTLE_WORK *v6;
  s32 ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v10;
  f32 *p_height;
  s32 devilid;
  s32 mode;
  SBATTLE_WORK *v19;
  SBTLACTION_WORK *actwk;
  s32 cmpframecnt;
  f32 v24;
  SBATTLE_WORK *v25;
  HpCallCtrl *weekAct;
  f32 x;
  f32 y;
  f32 z;
  sdfVector4_t GagePos;

  v3 = Allocate(SBTLVISUAL_DATA);
  _ctor(v3, 0);
  if (!lwk)
    return 0;
  wk_local = lwk->wk;
  if (!wk_local || !lwk->num)
    return 0;
  v6 = wk;
  if ((v6->status & 0x8000000) != 0)
    return 0;
  if ((v6->status2 & 0x40) == 0)
    goto LABEL_18;
  return 0;
  if ((wk->status2 & 0x40) == 0)
  {
    while (1)
    {
LABEL_18:
      ListID = wk_local->ListID;
      UnitMng = wk->UnitMng;
      v10 = sBtlSearchUnit_ID(UnitMng, ListID);
      if (!v10)
        goto LABEL_33;
      if (!sBtlCheckLiveTarget(v10))
      {
LABEL_33:
        wk_local->mode = 2;
LABEL_34:
        mode = wk_local->mode;
        if (mode == 2)
          goto LABEL_85;
        goto LABEL_35;
      }
      if ((u32)(wk_local->id - 1) > 1 || (v10->status & 0x800) != 0)
        goto LABEL_34;
      sBtlGetCylinderData(v10, v3);
      GagePos = sBtlGetGagePos(v10);
      x = GagePos.x;
      y = GagePos.y;
      z = GagePos.z;
      p_height = &v3->height;
      if ((v10->status & 0x100000) == 0)
      {
        p_height = &v10->hpPosition.y;
        x = x + (f32)(v10->hpPosition.x * 0.5);
        devilid = v10->para->devilid;
        if (devilid == 258)
          goto LABEL_77;
        goto LABEL_75;
      }
      devilid = v10->para->devilid;
      if (devilid == 258)
        goto LABEL_77;
LABEL_75:
      if (devilid == 315)
      {
        x = 0.0;
        z = 900.0;
        v24 = -250.0;
      }
      else
      {
        if (devilid == 314)
        {
LABEL_77:
          z = 900.0;
          x = 200.0;
          v24 = -450.0;
          goto LABEL_84;
        }
        v24 = y + (f32)(*p_height * -0.5);
      }
LABEL_84:
      wk_local->pos.x = x;
      wk_local->pos.y = v24;
      wk_local->pos.z = z;
      mode = wk_local->mode;
      if (mode == 2)
      {
LABEL_85:
        wk_local->alpha -= 16;
        LimitRange(&wk_local->alpha, 0, 128);
        if (wk_local->alpha <= 0)
        {
          wk_local->mode = 3;
          if (wk_local->id == 1)
          {
LABEL_91:
            if (v10)
            {
              WeakGageOff(wk->bsc, v10, 0);
              weekAct = v10->weekAct;
              if (weekAct)
                CallSign(weekAct, 0, 1, 0);
            }
            goto LABEL_17;
          }
        }
        else if (wk_local->id == 1)
        {
          goto LABEL_91;
        }
        goto LABEL_17;
      }
LABEL_35:
      if (mode != 1)
      {
        if (!mode)
        {
          wk_local->alpha += 16;
          LimitRange(&wk_local->alpha, 0, 127);
          if (wk_local->alpha >= 127)
          {
            wk_local->mode = 1;
            wk_local->counter = 0;
          }
          if (wk_local->id == 1)
          {
            v25 = wk;
            if (v25->cmbSkl->bRun)
            {
              v25 = wk;
              WeakGageDraw(v25->bsc, v10, v10->actwk->cmpframecnt - v10->actwk->framecntC, v10->actwk->cmpframecnt, wk_local->stpBSTF, 1, 0);
              wk_local->IsSprit = 1;
              goto LABEL_17;
            }
            v25 = wk;
            WeakGageDraw(v25->bsc, v10, v10->actwk->cmpframecnt - v10->actwk->framecntC, v10->actwk->cmpframecnt, wk_local->stpBSTF, 0, 0);
          }
          wk_local->IsSprit = 0;
        }
        goto LABEL_17;
      }
      if (wk_local->id == 1 && wk_local->IsSprit)
      {
        WeakGageDraw(wk->bsc, v10, v10->actwk->cmpframecnt - v10->actwk->framecntC, v10->actwk->cmpframecnt, wk_local->stpBSTF, 1, 0);
      }
      v19 = wk;
      if (v19->cmbSkl->bRun)
      {
        if (v10->actwk->status == 9)
          goto LABEL_17;
      }
      if (wk_local->id == 1)
      {
        actwk = v10->actwk;
        cmpframecnt = actwk->cmpframecnt;
        if (actwk->framecnt < cmpframecnt)
        {
          actwk = v10->actwk;
          cmpframecnt = actwk->cmpframecnt;
          v19 = wk;
          WeakGageDraw(v19->bsc, v10, cmpframecnt - actwk->framecntC, cmpframecnt, wk_local->stpBSTF, 0, 0);
          goto LABEL_17;
        }
LABEL_81:
        wk_local->mode = 2;
        goto LABEL_17;
      }
      if (wk_local->counter <= 59)
      {
        wk_local->y = wk_local->y - wk_local->spd;
LABEL_65:
        if (!sBtlCheckSetsuma())
          goto LABEL_71;
        goto LABEL_69;
      }
      else
      {
        goto LABEL_65;
      }
      if (!sBtlCheckSetsuma())
        goto LABEL_71;
LABEL_69:
      if (sBtlCheckSetsumaEnd())
        goto LABEL_71;
      goto LABEL_9001;
      if (sBtlCheckSetsumaEnd())
      {
LABEL_71:
        ++wk_local->counter;
        goto LABEL_80;
      }
LABEL_9001:
LABEL_80:
      LimitRange(&wk_local->counter, 0, 0x7FFF);
      if (wk_local->counter >= wk_local->counterMax)
        goto LABEL_81;
LABEL_17:
      wk_local = wk_local->next;
      if (!wk_local)
        return 1;
    }
  }
  return 0;
}

// 0x1fbd8b0
static void WeakDispOff(SBTLUNIT_WORK *wk) {
  HpCallCtrl *weekAct;

  if (wk)
  {
    WeakGageOff(wk->bsc, wk, 0);
    weekAct = wk->weekAct;
    if (weekAct)
      CallSign(weekAct, 0, 1, 0);
  }
}

// 0x1fbd950
bool Draw(SBTLSTP_LISTWORK *lwk) {
  void *v3;
  SBTLSTP_WORK *wk_local;
  SBATTLE_WORK *v7;
  bool result;
  void *bsc;
  f32 y;
  s32 x;
  s32 v12;
  s32 v13;
  s32 alpha;
  s32 v17;
  f32 v18;
  s32 v19;
  SBATTLE_WORK *v20;
  struct sdfVector4_t pos;
  sdfVector4_t ppos;

  *(u64 *)&ppos.x = 0;
  *(u64 *)&ppos.z = 0;
  NewSpecific(uint, 4u);
  v3 = NewSpecific(s32, 8u);
  InitializeArray_55364416(v3, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__BDBA9B2DF34291F8B0B83BB0575F991C0F7F23AED7779AC998DAA6A665B4287D, 0);
  if ((wk->status2 & 0x20) != 0)
    return 0;
  if ((sBtlGetCutFlg() & 2) == 0)
  {
    if (!lwk)
      return 0;
    wk_local = lwk->wk;
    if (!wk_local || !lwk->num)
      return 0;
    v7 = wk;
    if (!v7->panelwk)
      return 0;
    v7 = wk;
    if ((v7->status2 & 0x40) != 0)
      return 0;
    while (wk_local->mode > 2u)
    {
LABEL_30:
      wk_local = wk_local->next;
      result = 1;
      if (!wk_local)
        return result;
    }
    pos = wk_local->pos;
    vct_A = pos;
    sBtlChangeWorldtoScreenUnity(&ppos);
    alpha = wk_local->alpha;
    if (wk_local->id == 1)
      v17 = 20;
    else
      v17 = -40;
    if (wk_local->id == 1)
      v18 = 0.8;
    else
      v18 = 0.7;
    if (wk_local->id == 1)
      v19 = -116;
    else
      v19 = -176;
    v20 = wk;
    if (!v20->cmbSkl->bRun && ppos.z >= 0.0)
    {
      v20 = wk;
      bsc = v20->bsc;
      y = wk_local->y;
      if (ppos.x == INFINITY)
        x = 0x80000000;
      else
        x = ppos.x;
      v12 = ppos.y;
      v13 = y;
      if (ppos.y == INFINITY)
        v12 = 0x80000000;
      if (y == INFINITY)
        v13 = 0x80000000;
      sBtlStpSprite(bsc, x, v13 + v12, (f32)alpha * 0.0078125, wk_local->id, v19, v17, v18, 0);
    }
    goto LABEL_30;
  }
  return 1;
}

// 0x1fbde30
bool sBtlReleaseSTP_List(SBTLSTP_LISTWORK *lwk, u8 flg) {
  SBTLSTP_WORK *p_wk;
  SBTLSTP_WORK *wk_local;
  s32 ListID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v10;
  HpCallCtrl *weekAct;
  SBTLSTP_WORK *prev;
  SBTLSTP_WORK *next;
  SBTLSTP_WORK *v15;
  SBTLSTP_WORK *v16;
  SBTLSTP_WORK *v17;
  SBTLSTP_WORK *v18;

  if (!lwk)
    return 1;
  p_wk = &lwk->wk;
  wk_local = lwk->wk;
  if (wk_local && lwk->num)
  {
    while (1)
    {
      while (1)
      {
        if (flg && flg != 2 && (flg != 3 || wk_local->id != 1))
          wk_local->mode = 3;
        if (wk_local->mode == 3)
          break;
        wk_local = wk_local->next;
        if (!wk_local)
          return 1;
      }
      ListID = wk_local->ListID;
      UnitMng = wk->UnitMng;
      v10 = sBtlSearchUnit_ID(UnitMng, ListID);
      if (v10)
      {
        WeakGageOff(wk->bsc, v10, 0);
        weekAct = v10->weekAct;
        if (weekAct)
          CallSign(weekAct, 0, 1, 0);
      }
      prev = wk_local->prev;
      if (!prev)
        break;
      next = wk_local->next;
      prev->next = next;
      v16 = wk_local->prev;
      v15 = wk_local->next;
      if (v15)
        goto LABEL_27;
LABEL_28:
      if (!v16)
      {
        v17 = wk_local->next;
        p_wk = v17;
        v18 = p_wk;
        if (p_wk)
        {
          v18->prev = 0;
        }
      }
      wk_local = wk_local->next;
      --lwk->num;
      if (!wk_local)
        return 1;
    }
    v16 = 0;
    v15 = wk_local->next;
    if (!v15)
      goto LABEL_28;
LABEL_27:
    v15->prev = v16;
    v16 = wk_local->prev;
    goto LABEL_28;
  }
  return 0;
}

// 0x1fbe040
bool sBtlDeleteSTPList(SBTLSTP_LISTWORK *lwk) {
  if (lwk)
    sBtlReleaseSTP_List(lwk, 1u);
  return 1;
}
