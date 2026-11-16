#include "types.h"
#include "BTL_TIME.h"
#include "dat.h"
#include "sbtl.h"
#include "sbtlbossevent.h"
#include "sbtlencount.h"
#include "sbtlevent.h"
#include "sbtlexp.h"
#include "sbtlplayer.h"
#include "sbtlsm.h"
#include "sbtltime.h"
#include "sbtlunit.h"

typedef struct TYPE_BTL_TIME_EVENT TYPE_BTL_TIME_EVENT;

struct TYPE_BTL_TIME_EVENT {
    s32 encID;
    s32 devilID;
    s32 time;
    BTL_TIME resultID;
    s8 drawflg;
};

static TYPE_BTL_TIME_EVENT *btl_time_event[5];
static s32 sBtlExTimeMode;
static s32 sBtlExTimeCnt;

static void Result(void);

// 0x1fdb4f0
s32 Start(s32 encid, s32 devilid) {
  s64 v5;
  TYPE_BTL_TIME_EVENT *btl_time_event_local;
  SBATTLE_WORK *v11;
  s32 v12;
  SB_ENCOUNTPAC *EncountPac;
  s64 v15;
  Il2CppClass **v16;
  Il2CppClass *v18;
  SBATTLE_WORK *v19;

  v5 = 4;
  while (1)
  {
    btl_time_event_local = btl_time_event;
    if (v5 - 4 >= SLODWORD(btl_time_event_local->max_length))
      return 0;
    if (*(u32 *)(*((u64 *)&btl_time_event_local->obj.klass + v5) + 16) != encid)
      goto LABEL_5;
    if (*(u32 *)(*((u64 *)&btl_time_event->obj.klass + v5) + 20) != devilid)
      goto LABEL_5;
    if (!wk->timeflg)
      break;
LABEL_5:
    ++v5;
  }
  v11 = wk;
  v12 = *(u32 *)(*((u64 *)&btl_time_event->obj.klass + v5) + 28);
  wk->timeresult = v12;
  EncountPac = sBtlGetEncountPac(-1);
  v15 = *((u64 *)&btl_time_event->obj.klass + v5);
  v16 = &EncountPac->obj.klass + *(s32 *)(v15 + 16);
  v18 = v16[4];
  v19 = wk;
  v19->timedrawflg = *(u8 *)(v15 + 32);
  LODWORD(v15) = 60 * HIDWORD(v18->_1.generic_class);
  v19->timeflg = 1;
  v11->timecount = v15;
  gb_btltime = 0;
  return 1;
}

// 0x1fdb780
bool sBtlCheckEnemyAllDead(void) {
  SBTLUNIT_LISTWORK *TargetList;
  s64 v2;
  s32 v3;
  SBTLUNIT_WORK *pUnit;

  TargetList = sBtlCreateTargetList(2);
  if (TargetList->count < 1)
  {
    v3 = 0;
  }
  else
  {
    v2 = 0;
    v3 = 0;
    do
    {
      pUnit = TargetList->pUnitL[v2]->pUnit;
      ++v2;
      v3 += sBtlCheckDamageTarget(pUnit);
    }
    while (v2 < TargetList->count);
  }
  sBtlDeleteUnitList(TargetList, 0);
  if (v3)
    return 0;
  if (!sBtlCheckGeneratorAll())
    return 1;
  if (sBtlCheckGenerator_ND())
    return 0;
  return 1;
}

// 0x1fdb930
s32 Check(void) {
  s32 v3;
  s32 timecount;
  s64 v9;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s64 i;
  SBTLUNIT_LISTWORK *v14;
  SBTLUNIT_WORK *v15;
  s32 v16;
  SBATTLE_WORK *v17;
  s32 ListID;

  if (wk->timeflg != 1)
    return 0;
  if (wk->timecount)
  {
    if (sBtlCheckEnemyAllDead())
      return 0;
    timecount = wk->timecount;
    v3 = timecount - gb_btltime;
    if (v3 > 0)
      return v3;
    v3 &= ~(v3 >> 31);
    v9 = 0;
    wk->status4 |= 0x4000u;
    while (1)
    {
      UnitMng = wk->UnitMng;
      if (v9 >= UnitMng->number)
        break;
      UnitMng = wk->UnitMng;
      pUnit = UnitMng->pUnitL[v9]->pUnit;
      if (pUnit && (pUnit->side & 2) != 0)
      {
        Result();
        return 0;
      }
      ++v9;
    }
    for (i = 0; ; ++i)
    {
      v14 = wk->UnitMng;
      if (i >= v14->number)
        return v3;
      v14 = wk->UnitMng;
      v15 = v14->pUnitL[i]->pUnit;
      if (v15)
      {
        if (!sBtlCheckDamageTarget(v15))
        {
          continue;
        }
        v16 = sBtlCheck(v15, 7, 0);
        if ((v16 & 0x80000000) == 0)
        {
          v17 = wk;
          v17->timeflg = 2;
          ListID = v15->ListID;
          v17->boss_timeno = v16;
          v17->boss_eventID = ListID;
          return v3;
        }
      }
    }
  }
  return gb_btltime;
}

// 0x1fdbcc0
static void Result(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v5;
  SBATTLE_WORK *v6;
  SBTLSM_LISTWORK *sysmsgList;
  SBATTLE_WORK *v10;
  int8x8_t v11;
  SBATTLE_WORK *v14;
  s32 timeresult;
  int8x8_t v16;
  s64 v17;
  s32 *EventBit;
  bool v23;
  u32 *p_status;
  s64 v26;
  bool v27;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v5 = sBtlSearchUnit_ID(UnitMng, playerID);
  v6 = wk;
  if ((v6->status & 0x1000000) == 0)
  {
    sBtlResetAction(v5);
    sBtlResetNSTOP();
    sysmsgList = wk->sysmsgList;
    sBtlCreateSM(sysmsgList, v5, 5, 0, 0, 120);
    wk->sord_counter = 0;
    sBtlStatusBitOn(v5, 0x4000u);
    wk->status |= 0x1000000u;
    sBtlSetEscapeFlag();
    v10 = wk;
    v10->status |= 0x40000000u;
    v10->mode = 16;
    return;
  }
  if (v6->escape_cnt < 90)
    return;
  if (sBtlCheckUnit_Exec())
  {
    v14 = wk;
    timeresult = v14->timeresult;
    if (timeresult == 2)
    {
      v14 = wk;
      v16.n64_u64[0] = *(u64 *)&v14->status;
      v11.n64_u32[0] = 1073741832;
      LODWORD(v17) = vorr_s8(v16, v11).n64_u32[0];
      HIDWORD(v17) = (v16.n64_u64[0] & 0xEFFFFFFFEFFFFFFFLL) >> 32;
      *(u64 *)&v14->status = v17;
      v14->status5 |= 0x10u;
      sBtlInitDropWork();
      sBtlSetEndData();
LABEL_39:
      EventBit = GBWK->EventBit;
      EventBit[69] |= 0x80000000;
      *(u16 *)&wk->timeflg = 0;
      return;
    }
    if (timeresult != 4)
      goto LABEL_38;
    goto LABEL_9002;
    if (wk->timeresult != 4)
    {
LABEL_38:
      goto LABEL_39;
    }
LABEL_9002:
    v23 = sBtlCheckTutorialBattle();
    if (v23)
      goto LABEL_50;
    goto LABEL_9003;
    if (v27)
    {
LABEL_50:
      goto LABEL_51;
    }
LABEL_9003:
    wk->status |= 0x20u;
LABEL_51:
    p_status = &wk->status;
    LODWORD(v26) = *(u64 *)p_status | 8;
    HIDWORD(v26) = HIDWORD(*(u64 *)p_status) & 0xEFFFFFFF;
    *(u64 *)p_status = v26;
    goto LABEL_39;
  }
}

// 0x1fdc1a0
void End(void) {
  *(u16 *)&wk->timeflg = 0;
}
