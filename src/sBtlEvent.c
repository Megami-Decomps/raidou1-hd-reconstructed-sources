#include "types.h"
#include "cfg.h"
#include "dat.h"
#include "dat_str_ref.h"
#include "dds3kernelcore.h"
#include "evtbit.h"
#include "fclmisc.h"
#include "file.h"
#include "itf.h"
#include "localize.h"
#include "sbtl.h"
#include "sbtlactai.h"
#include "sbtlaction.h"
#include "sbtlbossevent.h"
#include "sbtlcalc.h"
#include "sbtldead.h"
#include "sbtldvltk.h"
#include "sbtleff.h"
#include "sbtlevent.h"
#include "sbtlevt.h"
#include "sbtlmain.h"
#include "sbtlplayer.h"
#include "sbtlscene.h"
#include "sbtlsub.h"
#include "sbtlsum.h"
#include "sbtlunit.h"
#include "sbtlvice.h"
#include "sbtlvisual.h"
#include "scr.h"
#include "sdf_vu0.h"
#include "sdfquat.h"
#include "smnr.h"
#include "tips.h"

#define DEADMES_000 0
#define DEADMES_00A 1
#define DEADMES_00B 2
#define DEADMES_00F 3
#define EFF_WAIT 86
#define SUMMON_WAIT 60

typedef enum {
    NakamaDeadEvent_Init = 0,
    NakamaDeadEvent_CallMsg = 1,
    NakamaDeadEvent_ChkMsg = 2,
    NakamaDeadEvent_Summon = 3,
    NakamaDeadEvent_End = 4,
} NakamaDeadEvent;

typedef enum {
    BattleTipsStep_Init = 0,
    BattleTipsStep_Update = 1,
    BattleTipsStep_End = 2,
} BattleTipsStep;

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

typedef bool (*sBtlEvent_EventProcTblDelegate)(void);

static bool e_0d_stop_flg;
static sBtlEvent_EventProcTblDelegate *sBtlEvent_EventProcTbl;

static bool EventProcTbl_02(void);
static bool EventProcTbl_03(void);
static bool EventProcTbl_04(void);
static bool EventProcTbl_05(void);
static bool EventProcTbl_07(void);
static bool EventProcTbl_06(void);
static bool EventProcTbl_00(void);
static bool EventProcTbl_01(void);
static bool EventProcTbl_08(void);
static bool EventProcTbl_09(void);
static bool EventProcTbl_0A(void);
static void AiMsgLoad(void);
static void AiMsgUnLoad(void);
static bool EventProcTbl_0B(void);
static bool EventProcTbl_0C(void);
static SBTLUNIT_WORK *GetTutrialNakama(s8 idx);
static bool EventProcTbl_0D(void);
static bool EventProcTbl_0F(void);
static void LoadHuuma_MesData2(SBTLUNIT_WORK *wk);

// 0x1f16fa0
static bool EventProcTbl_02(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 eventListID;
  s16 *p_eventcounter;
  SBATTLE_WORK *v9;
  bool result;
  SBATTLE_WORK *v12;
  s16 eventgstat;

  UnitMng = wk->UnitMng;
  eventListID = wk->eventListID;
  wk->status2 |= 0x80u;
  sBtlSearchUnit_ID(UnitMng, eventListID);
  p_eventcounter = &wk->eventcounter;
  ++*p_eventcounter;
  LimitRange_2(p_eventcounter, 0, 10000);
  v9 = wk;
  if (v9->eventgstat != 1)
  {
    result = 0;
    if (v9->eventgstat)
      return result;
    sBtlDefaultZoom2(15);
    result = 0;
    v12 = wk;
    eventgstat = v12->eventgstat;
    v12->eventcounter = 0;
    v12->eventgstat = eventgstat + 1;
    return result;
  }
  if (v9->eventcounter < 15)
    return 0;
  wk->eventgstat = 0;
  RestartBattle();
  *(int8x8_t *)&wk->status = vand_s8(*(int8x8_t *)&wk->status, (int8x8_t)0xFFFFFF7FFFFFFBFFLL);
  sBtlResetNSTOP();
  return 1;
}

// 0x1f17240
static bool EventProcTbl_03(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 huuma_targetID;
  s32 devilid;
  SBTLUNIT_WORK *v7;
  SBATTLE_WORK *v9;

  UnitMng = wk->UnitMng;
  huuma_targetID = wk->huuma_targetID;
  wk->status2 |= 0x80u;
  devilid = sBtlSearchUnit_ID(UnitMng, huuma_targetID)->para->devilid;
  sBtlGetDevilData(devilid, -1);
  v7 = sBtlSearchUnit_ID(wk->UnitMng, wk->playerID);
  v9 = wk;
  switch (v9->eventgstat)
  {
    case 0:
      sBtlSetMapFade_H(10, 0x80202020, 1);
      goto LABEL_17;
    case 1:
      if ((v9->scene->status & 0x10) != 0)
        return 0;
      v9 = wk;
LABEL_18:
      ++v9->eventgstat;
      return 0;
    case 2:
      sBtlSetMapFade_H(10, 0x80808080, 0);
LABEL_17:
      v9 = wk;
      goto LABEL_18;
    case 3:
      if ((v9->scene->status & 0x10) != 0)
        return 0;
      v9 = wk;
      v9->huuma_targetID = -1;
      v9->eventgstat = 0;
      RestartBattle();
      *(int8x8_t *)&wk->status = vand_s8(*(int8x8_t *)&wk->status, (int8x8_t)0xFFFFFF7FFFFFFBFFLL);
      sBtlResetAction(v7);
      sBtlResetNSTOP();
      sBtlSetAction(v7, 1, 0);
      return 1;
    default:
      return 0;
  }
}

// 0x1f17590
static bool EventProcTbl_04(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 huuma_targetID;
  s32 devilid;
  SBATTLE_WORK *v7;
  s32 eventgstat;
  s16 v9;
  bool result;

  UnitMng = wk->UnitMng;
  huuma_targetID = wk->huuma_targetID;
  wk->status2 |= 0x80u;
  devilid = sBtlSearchUnit_ID(UnitMng, huuma_targetID)->para->devilid;
  sBtlGetDevilData(devilid, -1);
  sBtlSearchUnit_ID(wk->UnitMng, wk->playerID);
  v7 = wk;
  eventgstat = v7->eventgstat;
  if (eventgstat == 2)
  {
    v7 = wk;
    v7->eventgstat = 0;
    *(int8x8_t *)&v7->status = vand_s8(*(int8x8_t *)&v7->status, (int8x8_t)0xFFFFFF7FFFFFFBFFLL);
    return 1;
  }
  else
  {
    v9 = v7->eventgstat;
    if (eventgstat == 1)
    {
      v7 = wk;
      v9 = v7->eventgstat;
      result = 0;
      goto LABEL_21;
    }
    if (!v7->eventgstat)
    {
      v7 = wk;
      v9 = v7->eventgstat;
      result = 0;
      v7->huuma_txtno = 38;
LABEL_21:
      v7->eventgstat = v9 + 1;
      return result;
    }
    return 0;
  }
}

// 0x1f17780
static bool EventProcTbl_05(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 eventListID;
  SBATTLE_WORK *v8;
  SBTLUNIT_LISTWORK *v9;
  s32 playerID;
  SBTLUNIT_WORK *v11;
  SBATTLE_WORK *v12;
  s32 eventgstat;

  NewSpecific(s32, 2u);
  UnitMng = wk->UnitMng;
  eventListID = wk->eventListID;
  wk->status2 |= 0x80u;
  sBtlSearchUnit_ID(UnitMng, eventListID);
  v8 = wk;
  v9 = v8->UnitMng;
  playerID = v8->playerID;
  v11 = sBtlSearchUnit_ID(v9, playerID);
  v12 = wk;
  eventgstat = v12->eventgstat;
  if (eventgstat != 1)
  {
    if (v12->eventgstat)
      return 0;
    v12 = wk;
    LOWORD(eventgstat) = v12->eventgstat;
    v12->eventgstat = eventgstat + 1;
    return 0;
  }
  wk->eventgstat = 0;
  RestartBattle();
  *(int8x8_t *)&wk->status = vand_s8(*(int8x8_t *)&wk->status, (int8x8_t)0xFFFFFF7FFFFFFBFFLL);
  sBtlResetAction(v11);
  sBtlSetAction(v11, 1, 0);
  sBtlResetNSTOP();
  return 1;
}

// 0x1f17a10
static bool EventProcTbl_07(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 huuma_targetID;
  s32 devilid;
  SBATTLE_WORK *v7;
  s32 eventgstat;
  SBATTLE_WORK *v11;
  u32 status;

  UnitMng = wk->UnitMng;
  huuma_targetID = wk->huuma_targetID;
  wk->status2 |= 0x80u;
  devilid = sBtlSearchUnit_ID(UnitMng, huuma_targetID)->para->devilid;
  sBtlGetDevilData(devilid, -1);
  v7 = wk;
  eventgstat = v7->eventgstat;
  if (eventgstat == 2)
  {
    v7 = wk;
    v7->status2 &= ~0x80u;
    sBtlResetNSTOP();
    v11 = wk;
    status = v11->status;
    v11->eventgstat = 0;
    v11->status = status & 0xFFFFFBFF;
    return 1;
  }
  else if (eventgstat == 1)
  {
    v7 = wk;
    LOWORD(eventgstat) = v7->eventgstat;
    v7->eventgstat = eventgstat + 1;
    return 0;
  }
  else if (v7->eventgstat)
  {
    return 0;
  }
  else
  {
    v7 = wk;
    v7->huuma_txtno = GetIntervalRand(35, 37);
    ++wk->eventgstat;
    return 0;
  }
}

// 0x1f17c50
static bool EventProcTbl_06(void) {
  s16 *p_eventcounter;
  SBATTLE_WORK *wk_local;
  s32 eventcounter;
  SBATTLE_WORK *v8;

  p_eventcounter = &wk->eventcounter;
  ++*p_eventcounter;
  LimitRange_2(p_eventcounter, 0, 10000);
  wk_local = wk;
  eventcounter = wk_local->eventcounter;
  if (eventcounter >= 90)
  {
    *(u32 *)&wk_local->eventcounter = 0;
    if (wk_local->eventdeadflg)
    {
      wk_local = wk;
      wk_local->eventdeadflg = 0;
      goto LABEL_14;
    }
    RestartBattle();
LABEL_14:
    v8 = wk;
    v8->status &= ~0x400u;
    sBtlResetNSTOP();
  }
  return eventcounter > 89;
}

// 0x1f17e00
static bool EventProcTbl_00(void) {
  void *v1;
  s16 eventno;

  v1 = NewSpecific(s16, 8u);
  InitializeArray_55364416(v1, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__D686E4CF6F89C1899AE3ED009C849F43299B381388FFF10C03F5F324A4F20844, 0);
  eventno = wk->eventno;
  sBtlGetEventMes(eventno);
  fclEndMessage();
  wk->status &= 0xFFFFFB3F;
  sBtlActiveAction();
  return 1;
}

// 0x1f18120
static bool EventProcTbl_01(void) {
  s32 eventgstat;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 eventListID;
  s64 v6;
  SBATTLE_WORK *v7;
  u32 stock_mask;
  bool result;
  u32 *p_stock_mask;

  eventgstat = wk->eventgstat;
  if (eventgstat != 1)
  {
    if (eventgstat)
      return 0;
    LOWORD(eventgstat) = wk->eventgstat;
    wk->eventgstat = eventgstat + 1;
    return 0;
  }
  UnitMng = wk->UnitMng;
  eventListID = wk->eventListID;
  if (sBtlSearchUnit_ID(UnitMng, eventListID))
    goto LABEL_13;
  wk->status &= 0xFFFFFB3F;
LABEL_28:
  sBtlActiveAction();
  result = 1;
LABEL_29:
  wk->eventgstat = 0;
  return result;
LABEL_13:
  v6 = 0;
  {
    stock_mask = wk->stock_mask;
LABEL_18:
    if (sBtlCheckBit(stock_mask, v6))
      goto LABEL_22;
LABEL_15:
    if (++v6 == 32)
    {
      wk->status &= 0xFFFFFB3F;
      goto LABEL_28;
    }
  }
  stock_mask = wk->stock_mask;
  goto LABEL_18;
LABEL_22:
  v7 = wk;
  if (v7->summonID[v6] != v7->eventListID)
    goto LABEL_15;
  v7 = wk;
  if (v7->summonflg[v6] == 2)
  {
    SetReturn(v6, 0);
    p_stock_mask = &wk->stock_mask;
    sBtlResetBit(p_stock_mask, v6);
    wk->status &= 0xFFFFFB3F;
    sBtlActiveAction();
    result = 0;
    goto LABEL_29;
  }
  return 0;
}

// 0x1f184c0
static bool EventProcTbl_08(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 eventListID;
  SBTLUNIT_WORK *v5;
  SBATTLE_WORK *v7;
  SBTLUNIT_WORK *v8;
  s16 eventgstat;
  s32 framecnt;
  f32 ActionTime;
  SBTLACTION_WORK *actwk;
  s32 side;
  SBATTLE_WORK *v16;
  SBTLACTION_WORK *v18;
  bool result;
  SBTLACTION_WORK *v20;
  char vstatus;
  u32 status;

  UnitMng = wk->UnitMng;
  eventListID = wk->eventListID;
  v5 = sBtlSearchUnit_ID(UnitMng, eventListID);
  v7 = wk;
  v8 = v5;
  eventgstat = v7->eventgstat;
  switch (eventgstat)
  {
    case 0:
      goto LABEL_30;
    case 1:
      sBtlGetActionTime(v8, 1);
      framecnt = v8->actwk->framecnt;
      ActionTime = sBtlGetActionTime(v8, 1);
      if (ActionTime != INFINITY && framecnt < (s32)ActionTime)
        goto LABEL_19;
      actwk = v8->actwk;
      v8->m_rate = 0.0;
      actwk->action_flg = 1;
      side = v8->side;
      v16 = wk;
      ++v16->eventgstat;
      sBtlCheckEffectData(v8, 470, 1u, 0, side, -1, 0);
      v18 = v8->actwk;
      v18->framecnt = 0;
      v18->total_homing = 0.0;
      v18->no_homing = 0;
      result = 0;
      break;
    case 2:
      v20 = v5->actwk;
      result = 0;
      v8->m_rate = 0.0;
      if (v20->framecnt < 186)
        return result;
      goto LABEL_30;
    case 3:
      v8->m_rate = 0.0;
      sBtlSetFade(v8, 1026, 0, 0, 3);
      ++wk->eventgstat;
      return 0;
    case 4:
      vstatus = v5->vstatus;
      result = 0;
      v8->m_rate = 0.0;
      if ((vstatus & 2) == 0)
        goto LABEL_30;
      return result;
    case 5:
      v5->m_rate = 0.5;
LABEL_30:
      v7 = wk;
      eventgstat = wk->eventgstat;
      v7->eventgstat = eventgstat + 1;
      result = 0;
      break;
    case 6:
      v7 = wk;
      status = v7->status;
      v7->eventgstat = 0;
      v7->status = status & 0xFFFFFBFF;
      result = 1;
      break;
    default:
LABEL_19:
      result = 0;
      break;
  }
  return result;
}

// 0x1f187e0
static bool EventProcTbl_09(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 eventListID;
  SBTLUNIT_WORK *v5;
  SBATTLE_WORK *v7;
  u8 *evtloadpData;
  s32 evtload_evtno;
  dds3ProcessID_t *started;
  SBATTLE_WORK *v14;
  u32 status;

  UnitMng = wk->UnitMng;
  eventListID = wk->eventListID;
  v5 = sBtlSearchUnit_ID(UnitMng, eventListID);
  v7 = wk;
  if (v7->eventgstat == 1)
  {
    if (dds3SearchProcessPriority(1015))
      return 0;
    v14 = wk;
    status = v14->status;
    v14->eventgstat = 0;
    v14->status = status & 0xFFFFFBFF;
    RestartBattle();
    sBtlResetAAI(v5);
    return 1;
  }
  if (v7->eventgstat)
    return 0;
  if ((v7->status & 0x10000000) == 0)
    return 1;
  v7 = wk;
  evtloadpData = v7->evtloadpData;
  evtload_evtno = v7->evtload_evtno;
  started = scrStartScript2(1015, evtloadpData, evtload_evtno, 1);
  v7->eventprocID = started;
  ++wk->eventgstat;
  StopBattle();
  return 0;
}

// 0x1f18a80
static bool EventProcTbl_0A(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 eventListID;
  SBATTLE_WORK *v8;
  s32 evtload_evtno;
  dds3ProcessID_t *started;
  SBATTLE_WORK *v14;
  u32 status;

  UnitMng = wk->UnitMng;
  eventListID = wk->eventListID;
  sBtlSearchUnit_ID(UnitMng, eventListID);
  if (wk->eventgstat != 1)
  {
    if (!wk->eventgstat)
    {
      Load(Dependent, "battle", "battle");
      Load(Dependent, "battle", "battle");
      v8 = wk;
      evtload_evtno = wk->evtload_evtno;
      started = scrStartScript2(1015, ai_scr, evtload_evtno, 1);
      v8->eventprocID = started;
      ++wk->eventgstat;
      return 0;
    }
    return 0;
  }
  if (dds3SearchProcessPriority(1015))
    return 0;
  v14 = wk;
  status = v14->status;
  v14->eventgstat = 0;
  v14->status = status & 0xFFFFFBFF;
  AiMsgUnLoad();
  return 1;
}

// 0x1f18d70
static void AiMsgLoad(void) {
  Load(Dependent, "battle", "battle");
  Load(Dependent, "battle", "battle");
}

// 0x1f18e10
static void AiMsgUnLoad(void) {
  char *Appendix;
  char *v4;

  Appendix = GetAppendix();
  Remove_30362592("AI_MSG", 0);
  v4 = Concat_54766928("battle", Appendix, 0);
  Unload(Dependent, v4, 0);
}

// 0x1f18f00
static bool EventProcTbl_0B(void) {
  return 0;
}

// 0x1f18f10
static bool EventProcTbl_0C(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 eventListID;
  SBATTLE_WORK *v8;
  s32 evtload_evtno;
  dds3ProcessID_t *started;
  SBATTLE_WORK *v15;
  u32 status;

  UnitMng = wk->UnitMng;
  eventListID = wk->eventListID;
  sBtlSearchUnit_ID(UnitMng, eventListID);
  if (wk->eventgstat != 1)
  {
    if (!wk->eventgstat)
    {
      Load(Dependent, "battle", "battle");
      Load(Dependent, "battle", "battle");
      v8 = wk;
      evtload_evtno = wk->evtload_evtno;
      started = scrStartScript2(1015, ai_scr, evtload_evtno, 1);
      v8->eventprocID = started;
      ++wk->eventgstat;
      StopBattle();
      return 0;
    }
    return 0;
  }
  if (dds3SearchProcessPriority(1015))
    return 0;
  v15 = wk;
  status = v15->status;
  v15->eventgstat = 0;
  v15->status = status & 0xFFFFFBFF;
  AiMsgUnLoad();
  RestartBattle();
  return 1;
}

// 0x1f19230
static SBTLUNIT_WORK *GetTutrialNakama(s8 idx) {
  u32 v5;
  s64 v6;
  s32 v7;
  SBATTLE_WORK *v8;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v10;
  SBTLUNIT_WORK *result;
  sdatUnitWork_t *para;

  if ((u8)idx > 1u)
    return 0;
  v5 = wk->summonindex[(u8)idx];
  if (v5 > 0x1F)
    return 0;
  v6 = idx;
  if (wk->summonindex_menu[(u8)idx] != v5)
    return 0;
  v7 = wk->summonflg[wk->summonindex[(u8)idx]];
  if (v7 != 1)
  {
    v7 = wk->summonflg[wk->summonindex[(u8)idx]];
    if (v7 != 3)
    {
      v7 = wk->summonflg[wk->summonindex[(u8)idx]];
      if (v7 != 2)
      {
        if (wk->battlemode != 3)
          return 0;
      }
    }
  }
  v8 = wk;
  UnitMng = v8->UnitMng;
  v10 = v8->summonID[v8->summonindex[v6]];
  result = sBtlSearchUnit_ID(UnitMng, v10);
  if (!result)
    return 0;
  para = result->para;
  if (!para || !para->devilid)
    return 0;
  return result;
}

// 0x1f19450
static bool EventProcTbl_0D(void) {
  SBATTLE_WORK *wk_local;
  s32 v3;
  bool v5;
  s32 v7;
  SBATTLE_WORK *v8;
  SBATTLE_WORK *v13;
  u32 status;
  SBATTLE_WORK *v19;
  SBATTLE_WORK *v20;
  s32 v21;
  Il2CppObject *Item;
  s32 v24;
  s64 v28;
  s8 v29;
  s64 v31;
  SBATTLE_WORK *v33;
  s32 evtload_evtno;
  dds3ProcessID_t *started;
  s32 *stock_id;
  sdatUnitWork_t *v41;
  sdatParaWork_t *now;
  f32 v44;
  f32 v45;
  SBATTLE_WORK *v46;
  s64 v47;
  s64 v48;
  f32 v49;
  f32 v50;
  sdfVector4_t *p_nakama_rot;
  SBTLUNIT_WORK *PChara;
  s32 v58;
  SBATTLE_WORK *v59;
  u32 *p_stock_mask;
  s32 v61;
  SBATTLE_WORK *v62;
  sdfVector4_t v64;

  if (cfgGetConfigGAME(6, 0) && get_Instance(0)->sc_pause)
  {
    if (IsSceanStop())
      return 0;
  }
  if (!!IsSceanStop())
  {
    if (!e_0d_stop_flg)
      return 0;
  }
  wk_local = wk;
  switch (wk_local->eventgstat)
  {
    case 0:
      v3 = ++wk_local->eventcounter;
      if (v3 < 86)
        return 0;
      if (IsSceanStop())
      {
        goto LABEL_67;
      }
      StopBattle();
      e_0d_stop_flg = 1;
      sBtlSetNSTOP();
LABEL_67:
      *(u32 *)&wk->eventcounter = 0x10000;
      return 0;
    case 1:
      Load(Dependent, "battle", "battle");
      Load(Dependent, "battle", "battle");
      v5 = evtBitCheck(10002);
      if (v5)
        v7 = 109;
      else
        v7 = 108;
      wk->evtload_evtno = v7;
      v8 = wk;
      if (v8->evtload_evtno == 109)
      {
        v8 = wk;
        if (v8->tutorialMesCount >= 1)
        {
          goto LABEL_40;
        }
      }
      v19 = wk;
      if (v19->evtload_evtno == 109)
      {
        v19 = wk;
        ++v19->tutorialMesCount;
        goto LABEL_100;
      }
LABEL_100:
      v33 = wk;
      evtload_evtno = wk->evtload_evtno;
      started = scrStartScript2(1015, ai_scr, evtload_evtno, 1);
      v33->eventprocID = started;
      battle_key_wait = 120;
      wk->eventgstat = 2;
      return 0;
    case 2:
      if (dds3SearchProcessPriority(1015))
        return 0;
LABEL_40:
      AiMsgUnLoad();
      wk->eventgstat = 3;
      return 0;
    case 3:
      if (IsSceanStop())
      {
        RestartBattle();
        sBtlResetNSTOP();
        goto LABEL_86;
      }
LABEL_86:
      v20 = wk;
      v21 = ++v20->eventcounter;
      if (v21 < 86)
        return 0;
      v20 = wk;
      Item = _get_Item(v20->deadUnit, 0);
      v24 = *((s16 *)Item[23].monitor + 11);
      if (v24 == 13)
      {
        if (GetTutrialNakama(0))
        {
          v28 = 1;
          v29 = 1;
          goto LABEL_95;
        }
        v28 = 0;
      }
      else
      {
        v28 = 1;
        if (GetTutrialNakama(1))
        {
          v28 = 0;
          v29 = 0;
LABEL_95:
          GetTutrialNakama(v29);
          v31 = 0;
          goto LABEL_132;
        }
      }
      v31 = 0;
LABEL_132:
      while (1)
      {
        stock_id = wk->stock_id;
        if (v31 >= SLODWORD(stock_id->max_length))
          break;
        stock_id = wk->stock_id;
        if (stock_id[v31] == v24)
          goto LABEL_134;
        ++v31;
      }
      LODWORD(v31) = 0;
LABEL_134:
      v41 = GBWK->player->stock_id[(u32)v31];
      if (v41)
      {
        v41 = GBWK->player->stock_id[(u32)v31];
        now = v41->now;
        v41->badstatus = 0;
        now->hp = now->maxhp;
      }
      v44 = *((f32 *)&Item[10].klass + 1);
      v45 = *(f32 *)&Item[10].monitor;
      v46 = wk;
      v47 = (s64)v46->summonindex + 2 * v28;
      v48 = (s64)v46->summonindex_menu + 4 * v28;
      *(u16 *)(v47 + 32) = v31;
      *(u32 *)(v48 + 32) = v31;
      v50 = *((f32 *)&Item[10].monitor + 1);
      v49 = *(f32 *)&Item[11].klass;
      nakama_pos.x = v44;
      nakama_pos.y = v45;
      nakama_pos.z = v50;
      nakama_pos.w = 1.0;
      FromEuler(0.0, 0.0, 0.0);
      p_nakama_rot = &nakama_rot;
      *p_nakama_rot = vct_A;
      nakama_mv_rotbk = 0.0;
      PChara = sBtlGetPChara();
      v58 = wk->summonindex[v28];
      v64.x = v44;
      v64.y = v45;
      v64.z = v50;
      v64.w = v49;
      sBtlSetSummon_Unit(PChara, v58, 0, 1, v64, 2, 0);
      v59 = wk;
      p_stock_mask = &v59->stock_mask;
      v61 = v59->summonindex[v28];
      sBtlSetBit(p_stock_mask, v61);
      _RemoveAt(wk->deadUnit, 0);
      v62 = wk;
      if (!v62->deadUnit->_size)
      {
        v62 = wk;
        v62->eventgstat = 4;
      }
      e_0d_stop_flg = 0;
      return 0;
    case 4:
      wk_local = wk;
      *(u32 *)&wk_local->eventcounter = 0;
      if (wk_local->eventdeadflg)
      {
        wk_local = wk;
        wk_local->eventdeadflg = 0;
      }
      v13 = wk;
      status = v13->status;
      v13->eventgstat = 0;
      v13->status = status & 0xFFFFFBFF;
      e_0d_stop_flg = 0;
      return 1;
    default:
      return 1;
  }
}

// 0x1f1a030
static bool EventProcTbl_0F(void) {
  SBATTLE_WORK *wk_local;
  s32 eventgstat;
  s32 v5;
  s32 v9;
  s32 callTips;
  SBATTLE_WORK *v13;

  if (get_Instance(0)->sc_pause)
    return 0;
  wk_local = wk;
  eventgstat = wk_local->eventgstat;
  if (eventgstat != 2)
  {
    if (eventgstat != 1)
    {
      if (!eventgstat)
      {
        v5 = ++wk_local->eventcounter;
        if (v5 >= 60)
          goto LABEL_24;
        goto LABEL_9000;
        if (v9 >= 60)
        {
LABEL_24:
          sBtlSetNSTOP();
          StopBattle();
          callTips = wk->callTips;
          tipsTIPSStart(callTips);
          *(u32 *)&wk->eventcounter = 0x10000;
          return 0;
        }
LABEL_9000:
      }
      return 0;
    }
    if (IsSceanStop())
    {
      goto LABEL_21;
    }
    StopBattle();
LABEL_21:
    if (tipsProcessCheck())
      return 0;
    v13 = wk;
    v13->eventgstat = 2;
    v13->callTips = -1;
    return 0;
  }
  wk_local = wk;
  wk_local->eventgstat = 0;
  wk_local->status &= ~0x400u;
  RestartBattle();
  return 1;
}

// 0x1f1a330
void sBtlCheckTutorialEnd(void) {
  sdatPlayerUnitWork_t *PlayerData;
  s32 *EventBit;
  sdatUnitWork_t *para;
  sdatParaWork_t *now;
  s32 maxmp;
  sdatUnitWork_t *StockUnitData;
  sdatParaWork_t *v11;
  sdatUnitWork_t *v12;
  s32 v14;
  sdatUnitWork_t *v16;
  sdatParaWork_t *v17;
  sdatUnitWork_t *v18;
  s32 v20;
  s32 *v25;
  sdatUnitWork_t *v27;
  sdatUnitWork_t *v29;
  sdatUnitWork_t *v30;
  sdatUnitWork_t *v33;
  sdatUnitWork_t *v34;
  s16 *item;
  s32 mag;
  il2cpp_array_size_t max_length;
  s16 *v42;
  u64 v43;
  u64 v44;
  s16 *v45;
  s16 *v46;
  u64 v47;
  __int128 v48;
  __int128 v49;
  __int128 v50;
  __int128 v51;
  u64 v52;
  u64 v53;
  s64 v54;
  s16 *v55;
  u16 *v56;
  s16 v57;
  SortSave *sortSave;
  void *getItemList;
  void *v60;

  if (!evtBitCheck(2100))
    return;
  GBWK->EventBit[65] &= ~0x100000u;
  PlayerData = sBtlGetPlayerData();
  if (evtBitCheck(2096))
  {
    if (wk->encountno == 515)
    {
      EventBit = GBWK->EventBit;
      EventBit[312] |= 0x100u;
    }
    para = PlayerData->para;
    now = para->now;
    maxmp = now->maxmp;
    now->hp = now->maxhp;
    now->mp = maxmp;
    PlayerData->mag = PlayerData->maxmag;
    sBtlResetBadStatus_GB(para, 0x3FFFF);
    StockUnitData = sBtlGetStockUnitData(0);
    if (StockUnitData)
    {
      v11 = StockUnitData->now;
      v12 = StockUnitData;
      v14 = v11->maxmp;
      v11->hp = v11->maxhp;
      v11->mp = v14;
      sBtlResetBadStatus_GB(v12, 0x3FFFF);
      *(u32 *)GBWK->player->stack_p = -65536;
    }
    v16 = sBtlGetStockUnitData(1);
    if (v16)
    {
      v17 = v16->now;
      v18 = v16;
      v20 = v17->maxmp;
      v17->hp = v17->maxhp;
      v17->mp = v20;
      sBtlResetBadStatus_GB(v18, 0x3FFFF);
      GBWK->player->stack_p[1] = 1;
    }
    goto LABEL_71;
  }
  v25 = GBWK->EventBit;
  v25[21] &= ~0x20u;
  ClearFlgOnGameOver();
  v27 = PlayerData->para;
  ClassCopy(v27, tutorial_bk->para, 0);
  v29 = sBtlGetStockUnitData(0);
  if (v29)
  {
    v30 = v29;
    ClassCopy(v30, tutorial_bk->stock_id[0], 0);
    *(u32 *)GBWK->player->stack_p = -65536;
  }
  v33 = sBtlGetStockUnitData(1);
  if (v33)
  {
    v34 = v33;
    ClassCopy(v34, tutorial_bk->stock_id[1], 0);
    GBWK->player->stack_p[1] = 1;
  }
  item = PlayerData->item;
  mag = tutorial_bk->mag;
  PlayerData->gold = tutorial_bk->gold;
  max_length = item->max_length;
  PlayerData->mag = mag;
  if ((s32)max_length >= 1)
  {
    v42 = tutorial_bk->item;
    item[0] = v42[0];
    if ((u32)max_length >= 2)
    {
      v43 = 1;
      v44 = (u32)max_length - 1;
      if (v44 < 0x20)
        goto LABEL_63;
      if ((u64)((char *)item - (char *)v42) < 0x40)
        goto LABEL_63;
      v45 = &item[25];
      v46 = &v42[9];
      v43 = v44 & 0xFFFFFFFFFFFFFFE0LL | 1;
      v47 = v44 & 0xFFFFFFFFFFFFFFE0LL;
      do
      {
        v48 = *((_OWORD *)v46 - 1);
        v49 = *(_OWORD *)v46;
        v47 -= 32;
        v50 = *((_OWORD *)v46 + 1);
        v51 = *((_OWORD *)v46 + 2);
        v46 += 32;
        *((_OWORD *)v45 - 3) = v48;
        *((_OWORD *)v45 - 2) = v49;
        *((_OWORD *)v45 - 1) = v50;
        *(_OWORD *)v45 = v51;
        v45 += 32;
      }
      while (v47);
      if (v44 != (v44 & 0xFFFFFFFFFFFFFFE0LL))
      {
LABEL_63:
        v52 = v43 + 1;
        if ((max_length & 1) == 0)
        {
          item[v43] = v42[v43];
          ++v43;
        }
        if ((u32)max_length != v52)
        {
          v53 = (u32)max_length - v43;
          v54 = 2 * v43 + 34;
          v55 = ((char *)v42 + v54);
          v56 = ((char *)item + v54);
          do
          {
            v53 -= 2;
            *(v56 - 1) = *(v55 - 1);
            v57 = *v55;
            v55 += 2;
            *v56 = v57;
            v56 += 2;
          }
          while (v53);
        }
      }
    }
  }
  sortSave = GBWK->sortSave;
  getItemList = tutorial_bk->getItemList;
  v60 = Allocate(System_Collections_Generic_List_ITM_);
  __ctor_47784336(v60, getItemList);
  sortSave->getItemList = v60;
  *(u64 *)&PlayerData->hgunnum = *(u64 *)&tutorial_bk->hgunnum;
LABEL_71:
  wk->tutorialMesCount = 0;
  return;
}

// 0x1f1aa00
void sBtlTutorialEndNakamaChack(void) {
  sdatUnitWork_t *StockUnitData;
  sdatParaWork_t *now;
  sdatUnitWork_t *v4;
  sdatUnitWork_t *v6;
  sdatParaWork_t *v7;
  sdatUnitWork_t *v8;

  if (!evtBitCheck(2100))
    return;
  if (evtBitCheck(2096))
  {
    StockUnitData = sBtlGetStockUnitData(0);
    if (StockUnitData)
    {
      now = StockUnitData->now;
      v4 = StockUnitData;
      now->hp = now->maxhp;
      now->mp = now->maxmp;
      sBtlResetBadStatus_GB(v4, 0x3FFFF);
      *(u32 *)GBWK->player->stack_p = -65536;
    }
    v6 = sBtlGetStockUnitData(1);
    if (v6)
    {
      v7 = v6->now;
      v8 = v6;
      v7->hp = v7->maxhp;
      v7->mp = v7->maxmp;
      sBtlResetBadStatus_GB(v8, 0x3FFFF);
      GBWK->player->stack_p[1] = 1;
    }
  }
}

// 0x1f1abc0
void sBtlInitTutorial(void) {
  _BOOL4 v3;
  s32 *EventBit;
  _BOOL4 v5;
  s32 *v6;
  _BOOL4 v7;
  s32 *v8;
  sdatPlayerUnitWork_t *PlayerData;
  sdatPlayerUnitWork_t *tutorial_bk_local;
  void *getItemList;
  void *v14;

  if (!evtBitCheck(2100))
    return;
  v3 = 0;
  EventBit = GBWK->EventBit;
  EventBit[65] &= ~0x10000u;
  v5 = 0;
  v6 = GBWK->EventBit;
  v6[65] &= ~0x20000u;
  v7 = 0;
  v8 = GBWK->EventBit;
  v8[65] &= ~0x40000u;
  GBWK->EventBit[65] &= ~0x80000u;
  PlayerData = sBtlGetPlayerData();
  ClassCopy(tutorial_bk, PlayerData, 0);
  tutorial_bk_local = tutorial_bk;
  getItemList = GBWK->sortSave->getItemList;
  v14 = Allocate(System_Collections_Generic_List_ITM_);
  __ctor_47784336(v14, getItemList);
  tutorial_bk_local->getItemList = v14;
}

// 0x1f1ae90
void sBtlCheckBattleWin(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v5;
  SBTLUNIT_WORK *v6;
  SBTLUNIT_WORK *v7;
  s32 *huuma_devilID;
  _BOOL4 v10;
  s32 *v11;
  _BOOL4 v12;
  s32 *v13;
  s32 *v14;
  s32 *v15;
  s32 *v18;
  _BOOL4 v19;
  s32 *v20;
  _BOOL4 v21;
  s32 *v22;
  s32 *v23;
  _BOOL4 v24;
  s32 *EventBit;
  s32 *v26;
  s32 *v27;

  if (!evtBitCheck(2100))
    return;
  if (evtBitCheck(1934))
    goto LABEL_94;
  if (!evtBitCheck(1933) && !evtBitCheck(248))
    goto LABEL_25;
  if (wk->stock_num < 1)
    goto LABEL_25;
  if (wk->member_num >= 1)
  {
    UnitMng = wk->UnitMng;
    v5 = wk->summonID[wk->summonindex[0]];
    v6 = sBtlSearchUnit_ID(UnitMng, v5);
    if (v6)
    {
      v7 = v6;
      if (CheckLiveTarget(v7))
      {
LABEL_25:
        if (evtBitCheck(1933) || evtBitCheck(248) || !evtBitCheck(1932))
        {
          goto LABEL_94;
        }
        huuma_devilID = wk->huuma_devilID;
        if (huuma_devilID[11] != -1 || huuma_devilID[10] != -1 || huuma_devilID[9] != -1 || huuma_devilID[8] != -1 || huuma_devilID[7] != -1 || huuma_devilID[6] != -1 || huuma_devilID[5] != -1 || huuma_devilID[4] != -1 || huuma_devilID[3] != -1 || huuma_devilID[2] != -1 || huuma_devilID[1] != -1)
        {
          goto LABEL_94;
        }
        if (huuma_devilID[0] == -1)
        {
          v24 = 0;
          EventBit = GBWK->EventBit;
          EventBit[65] &= ~0x10000u;
          v26 = GBWK->EventBit;
          v26[65] &= ~0x20000u;
          v27 = GBWK->EventBit;
          v27[65] |= 0x40000u;
LABEL_109:
LABEL_110:
          v23 = GBWK->EventBit;
          v23[65] &= ~0x80000u;
          return;
        }
LABEL_94:
        v18 = GBWK->EventBit;
        v18[65] |= 0x10000u;
        v19 = 0;
        v20 = GBWK->EventBit;
        v20[65] &= ~0x20000u;
        v21 = 0;
        v22 = GBWK->EventBit;
        v22[65] &= ~0x40000u;
        if (!v21)
          goto LABEL_110;
        goto LABEL_109;
      }
    }
  }
  v10 = 0;
  v11 = GBWK->EventBit;
  v11[65] &= ~0x10000u;
  v12 = 0;
  v13 = GBWK->EventBit;
  v13[65] &= ~0x20000u;
  v14 = GBWK->EventBit;
  v14[65] &= ~0x40000u;
  v15 = GBWK->EventBit;
  v15[65] |= 0x80000u;
}

// 0x1f1b6c0
void sBtlCheckBattleLose(void) {
  s32 *EventBit;
  s32 *v4;
  _BOOL4 v5;
  s32 *v6;
  s32 *v7;

  if (!evtBitCheck(2100))
    return;
  EventBit = GBWK->EventBit;
  EventBit[65] &= ~0x10000u;
  v4 = GBWK->EventBit;
  v4[65] |= 0x20000u;
  v5 = 0;
  v6 = GBWK->EventBit;
  v6[65] &= ~0x40000u;
  v7 = GBWK->EventBit;
  v7[65] &= ~0x80000u;
}

// 0x1f07920
bool sBtlCheckTutorialBattle(void) {
  return evtBitCheck(2100);
}

// 0x1f1b8c0
bool sBtlEvent_CheckRain(void) {
  return 1;
}

// 0x1f1b8d0
bool sBtlEvent_LoadEventScript(void) {
  s32 evtloadst;

  if ((wk->status & 0x10000000) != 0)
    return 1;
  evtloadst = (u16)wk->evtloadst;
  if (evtloadst == 1)
  {
    wk->status |= 0x10000000u;
    return 1;
  }
  if (evtloadst)
    return 0;
  wk->evtloadst = 1;
  return 0;
}

// 0x1f1ba10
bool sBtlEvent_DeleteEventScript(void) {
  if ((wk->status & 0x10000000) == 0)
  {
    return wk->evtloadst == 0;
  }
  wk->evtloadst = 0;
  return 1;
}

// 0x1f1bb00
bool sBtlEvent_SetCharacterProc(s32 negoid) {
  return 0;
}

// 0x1f17f80
u8 *sBtlGetEventMes(s16 eventno) {
  u64 *v3;
  void **p_msg_00;
  void *v6;
  void **p_msg;
  void *v9;
  void **v11;
  void *v12;
  void **v14;
  void *v15;
  u8 *v19;
  void *v20;

  v3 = NewSpecific(byte__, 8u);
  p_msg_00 = &msg_00;
  v6 = *p_msg_00;
  v3[4] = *p_msg_00;
  p_msg = &msg;
  v9 = *p_msg;
  v3[5] = *p_msg;
  v11 = &msg;
  v12 = *v11;
  v3[6] = *v11;
  v14 = &msg;
  v15 = *v14;
  v3[8] = *v14;
  v3[10] = msg_00;
  v19 = msg_00;
  v3[11] = msg_00;
  v20 = v3 + 11;
  return *((u8 **)v20 + eventno - 7);
}

// 0x1f18110
bool sBtlEvent_NegoProc(u8 *adr, s32 no) {
  return 1;
}

// 0x1f1bb10
bool sBtlMessageProc(u8 *adr, s32 no, SBTLUNIT_WORK *wk, s32 flg) {
  SBATTLE_WORK *v10;
  u32 nego_gstat;
  sdatUnitWork_t *para;
  s32 devilid;
  DEVILDATA_WORK *DevilData;
  char *v15;
  s32 v16;
  char *v17;
  s32 v18;
  char *v21;

  v10 = wk;
  nego_gstat = v10->nego_gstat;
  if (nego_gstat > 5)
    return 1;
  switch (nego_gstat)
  {
    case 0u:
      fclInitMessage(&adr->obj);
      goto LABEL_35;
    case 1u:
      para = wk->para;
      if (flg)
      {
        devilid = para->devilid;
        DevilData = sBtlGetDevilData(devilid, -1);
        v15 = DVNAME(DevilData->huumaID);
        v16 = 0;
        v17 = v15;
      }
      else
      {
        v21 = RCNAME(para->raceid);
        fclSetMessageVar(0, v21);
        v17 = DVNAME(wk->para->devilid);
        v16 = 1;
      }
      fclSetMessageVar(v16, v17);
      goto LABEL_35;
    case 2u:
      fclStartMessage(no);
      fclChangeMessageWindowAlpha(1u);
      goto LABEL_35;
    case 3u:
      if (fclChkMessage() == 1)
        goto LABEL_39;
LABEL_35:
      ++wk->nego_gstat;
      return 0;
LABEL_39:
      fclUpdateMessage();
      return 0;
    case 4u:
      v18 = 5;
      v10->nego_gstat = v18;
      return 0;
    case 5u:
      fclDestroyMessage();
      wk->nego_gstat = 0;
      return 1;
    default:
      return 1;
  }
}

// 0x1f1be40
bool EventProc(void) {
  u32 status2;
  bool v5;
  sBtlEvent_EventProcTblDelegate v10;

  status2 = wk->status2;
  if (sBtlProcessCheck())
    return 0;
  if ((status2 & 2) != 0)
    return 0;
  v5 = sBtlCheckSetsuma();
  if (!v5)
    goto LABEL_18;
  if (wk->eventno != 10)
    goto LABEL_18;
  return 0;
LABEL_18:
  if ((wk->status & 0x400) == 0)
    return 0;
  v10 = sBtlEvent_EventProcTbl[wk->eventno];
  return (v10->invoke_impl)(v10->method_code, v10->method);
}

// 0x1f1c070
bool sBtlChkEvent(void) {
  _BOOL4 v2;

  if (sBtlProcessCheck())
  {
    LOBYTE(v2) = 1;
    return v2;
  }
  return (BYTE1(wk->status) >> 2) & 1;
}

// 0x1f1c130
bool sBtlLoadHuuma_MesData(void) {
  bool result;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 huuma_targetID;
  SBTLUNIT_WORK *v7;
  s32 devilid;
  sbtldvltk_unitworktag *dvltkwk;
  fileHandle_t *hFile;
  sbtldvltk_unitworktag *v11;
  s32 hstatus;

  if (sBtlCheckMsgMemType())
    return 1;
  UnitMng = wk->UnitMng;
  huuma_targetID = wk->huuma_targetID;
  v7 = sBtlSearchUnit_ID(UnitMng, huuma_targetID);
  devilid = v7->para->devilid;
  sBtlGetDevilData(devilid, -1);
  if ((v7->hstatus & 1) != 0)
    return 1;
  if (v7->dvltk_gstat == 1)
  {
    dvltkwk = v7->dvltkwk;
    if (dvltkwk->pData)
      return 0;
    hFile = dvltkwk->hFile;
    if (!fileCheckEnd(hFile))
    {
      return 0;
    }
    else
    {
      v11 = v7->dvltkwk;
      v11->hFile = 0;
      hstatus = v7->hstatus;
      ++v7->dvltk_gstat;
      v7->hstatus = hstatus | 1;
      return 1;
    }
  }
  else
  {
    result = 0;
    if (!v7->dvltk_gstat)
      v7->dvltk_gstat = 1;
  }
  return result;
}

// 0x1f1c330
static void LoadHuuma_MesData2(SBTLUNIT_WORK *wk) {
  s32 devilid;
  s32 huumaID;
  sbtldvltk_unitworktag *dvltkwk;
  s32 Kucyou;
  u8 *v9;
  u8 **v10;
  void *v11;
  void *pData;
  u8 **v13;
  s32 v14;

  devilid = wk->para->devilid;
  huumaID = sBtlGetDevilData(devilid, -1)->huumaID;
  dvltkwk = wk->dvltkwk;
  Kucyou = sBtlGetKucyou(huumaID);
  v9 = NewSpecific(byte, pGlobalMsg[Kucyou]->max_length);
  dvltkwk->pData = v9;
  v10 = pGlobalMsg;
  v11 = v10[sBtlGetKucyou(huumaID)];
  pData = wk->dvltkwk->pData;
  v13 = pGlobalMsg;
  v14 = sBtlGetKucyou(huumaID);
  Copy_56180528(v11, pData, v13[v14]->max_length, 0);
}

// 0x1f1c480
s32 sBtlEventChkMemory(s16 eventno) {
  return (wk->eventMemory[(s16)(eventno + (((u32)eventno >> 28) & 7)) >> 3] & (0x1000000 << (eventno - ((eventno + (((u32)eventno >> 28) & 7)) & 0x18)) >> 24)) != 0;
}

// 0x1f1c520
void sBtlEventSetMemory(s16 eventno) {
  s32 v2;
  s32 v4;
  char *v5;

  v2 = eventno;
  v4 = v2 + (((u32)(s16)v2 >> 28) & 7);
  v5 = (char *)wk->eventMemory + ((s16)v4 >> 3);
  v5[32] |= 1 << (v2 - (v4 & 0x18));
}
