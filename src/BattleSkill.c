#include "types.h"
#include "battleskill.h"
#include "dat.h"
#include "dds3_pad.h"
#include "rspecialskill.h"
#include "rspecialskillstatus.h"

static void NormalUpdate(void);
static void SelectUpdate(void);

// 0x1e16100
void Init(void) {
  RSpecialSkillStatus *SelectListState;
  s32 v7;
  s32 v8;
  SpecialSkillCsr *NowSkillCsr;
  s64 max_length_low;
  SpecialSkillCsr *NowPossSkilCsr;
  u32 BattleSkillCount;
  s32 v21;
  char v22;
  void *Instance;
  void *v27;
  void *v28;
  void *v29;

  RSpecialSkillGetHaveBattleSkill();
  RSpecialSkillIsBtlSkillSort();
  RSpecialSkillSetTab(0);
  RSpecialSkillLosdListSide(0);
  SelectListState = RSpecialSkillGetSelectListState();
  v7 = SelectListState;
  if (v7 == 1)
  {
    v7 = 14;
    v8 = 14;
    v8 = v7;
  }
  else
  {
    if (v7)
      goto LABEL_14;
    v8 = 0;
  }
  HIDWORD(skillListSelect) = v8;
LABEL_14:
  NowSkillCsr = RSpecialSkillGetNowSkillCsr();
  max_length_low = LODWORD(GBWK->player->raidouSkill->max_length);
  v12 = (NowSkillCsr->klass->vtable._5_SetMaxPar.methodPtr)(NowSkillCsr, max_length_low, (u32)max_length_low, NowSkillCsr->klass->vtable._5_SetMaxPar.method);
  NowPossSkilCsr = RSpecialSkillGetNowPossSkilCsr();
  BattleSkillCount = RSpecialSkillGetBattleSkillCount();
  v15 = (NowPossSkilCsr->klass->vtable._5_SetMaxPar.methodPtr)(NowPossSkilCsr, BattleSkillCount, 6, NowPossSkilCsr->klass->vtable._5_SetMaxPar.method);
  RSpecialSkillSetBarLength();
  RSpecialSkillSetListDisplayRight();
  InitUseButtonImage(instance, 0);
  ChangePanel(instance, 0, 0);
  SetBtlSkillTimeObj(instance, 0);
  RSpecialSkillGetCsrData();
  RSpecialSkillSetListDisplayRight();
  RSpecialSkillDrawScrollBar();
  v21 = RSpecialSkillGetSelectListState();
  v22 = v21 != 0;
  if (!v21)
  {
    v22 = 0;
LABEL_41:
    Instance = get_Instance(0);
    ItfSortMenuActive(Instance, v22, 0);
    goto LABEL_42;
  }
  if (RSpecialSkillGetSelectListState() != 1)
    goto LABEL_42;
  v22 = 1;
  goto LABEL_41;
LABEL_42:
  v27 = get_Instance(0);
  v28 = Allocate(System_Action);
  _ctor(v28, 0, Method_Project_RSpecialSkillStatus_BattleSkillSortFunc__, 0);
  v29 = Allocate(System_Action);
  _ctor(v29, 0, Method_Project_RSpecialSkillStatus_EndBattleSkillSortFunc__, 0);
  SetActiveCallBack(v27, v28, v29, 0);
}

// 0x1e15280
void Update(void) {
  State = GetState();
  if ((u32)State == 2)
  {
    SelectUpdate();
    return;
  }
  if ((u32)State == 1)
    NormalUpdate();
}

// 0x1e15320
void Draw(void) {
  s32 SelectListState;

  SelectListState = RSpecialSkillGetSelectListState();
  if (SelectListState != 1)
  {
    if (!SelectListState)
    {
      RSpecialSkillSetListDisplayLeft();
    }
    goto LABEL_9;
  }
  RSpecialSkillSetListDisplayRight();
  RSpecialSkillDrawScrollBar();
LABEL_9:
  RSpecialSkillSkillCsrColorReset();
  RSpecialSkillSKillCsrReset();
  RSpecialSkillDrawHelpText();
}

// 0x1e17650
static void NormalUpdate(void) {
  s32 SelectListState;
  RSpecialSkillStatus *v9;
  s32 v10;
  s32 v11;
  void *v14;
  SpecialSkillCsr *NowSkillCsr;
  RSpecialSkillStatus *v23;
  s32 v24;
  s32 v25;
  void *v27;
  SpecialSkillCsr *NowPossSkilCsr;
  void *Instance;

  SelectListState = RSpecialSkillGetSelectListState();
  if (SelectListState != 1)
    goto LABEL_4;
  if (!RSpecialSkillIsHaveSKill(0, 1))
    goto LABEL_42;
  if (CHECK_TRIG(4096, 0))
  {
    SE(0);
    RSpecialSkillSelectRememberCsr();
    RSpecialSkillGetChangeSource();
    ChangeState(2);
    RSpecialSkillSelectChange(0);
    v23 = RSpecialSkillGetSelectListState();
    v24 = v23;
    if (v24 == 1)
    {
      v24 = 14;
      v25 = 14;
      v25 = v24;
    }
    else
    {
      if (v24)
      {
LABEL_59:
        RSpecialSkillSelectGetCsrData();
        RSpecialSkillSetListDisplayRight();
        RSpecialSkillDrawScrollBar();
        Instance = get_Instance(0);
        ItfSortMenuActive(Instance, 0, 0);
        return;
      }
      v25 = 0;
    }
    HIDWORD(skillListSelect) = v25;
    goto LABEL_59;
  }
LABEL_42:
  v27 = instance;
  NowPossSkilCsr = RSpecialSkillGetNowPossSkilCsr();
  SetCsrActive(v27, 0, 1, NowPossSkilCsr->listDrwNo, 0);
  return;
LABEL_4:
  if (!SelectListState)
  {
    if (CHECK_TRIG(4096, 0))
    {
      SE(0);
      RSpecialSkillSelectRememberCsr();
      RSpecialSkillGetChangeSource();
      ChangeState(2);
      RSpecialSkillSelectChange(1);
      v9 = RSpecialSkillGetSelectListState();
      v10 = v9;
      if (v10 == 1)
      {
        v10 = 14;
        v11 = 14;
        v11 = v10;
      }
      else
      {
        if (v10)
          goto LABEL_50;
        v11 = 0;
      }
      HIDWORD(skillListSelect) = v11;
LABEL_50:
      RSpecialSkillSelectGetCsrData();
      RSpecialSkillSetListDisplayRight();
      RSpecialSkillDrawScrollBar();
      return;
    }
    v14 = instance;
    NowSkillCsr = RSpecialSkillGetNowSkillCsr();
    SetCsrActive(v14, 0, 0, NowSkillCsr->listDrwNo, 0);
    if (CHECK_TRIG(45327, 1))
    {
      RSpecialSkillCancelSetting();
    }
  }
}

// 0x1e17ab0
static void SelectUpdate(void) {
  RSpecialSkillStatus *SelectListState;
  s32 v7;
  s32 v8;
  RSpecialSkillStatus *v18;
  s32 v19;
  s32 v20;
  s32 v21;
  void *v23;
  s32 listDrwNo;
  s32 v29;
  void *Instance;
  void *v37;
  s32 v38;
  s32 v43;
  void *v46;

  if (CHECK_TRIG(4097, 0))
  {
    SE(1);
    RSpecialSkillSelectRememberCsr();
    ChangeState(1);
    RSpecialSkillSelectChange(m_change_listTop);
    SelectListState = RSpecialSkillGetSelectListState();
    v7 = SelectListState;
    if (v7 == 1)
    {
      v7 = 14;
      v8 = 14;
      v8 = v7;
    }
    else
    {
      if (v7)
        goto LABEL_47;
      v8 = 0;
    }
    HIDWORD(skillListSelect) = v8;
LABEL_47:
    RSpecialSkillGetCsrData();
    RSpecialSkillSetListDisplayRight();
    RSpecialSkillDrawScrollBar();
    if (m_change_listTop != 1)
    {
      if (m_change_listTop)
      {
LABEL_65:
        RSpecialSkillSetChangeSource();
        return;
      }
      v29 = 0;
LABEL_63:
LABEL_64:
      SetCursorSprite(instance, 1, 0, v29, 0);
      goto LABEL_65;
    }
    Instance = get_Instance(0);
    v29 = 1;
    ItfSortMenuActive(Instance, 1, 0);
    goto LABEL_63;
  }
  if (!RSpecialSkillConfigurable())
    goto LABEL_36;
  if (!CHECK_TRIG(4096, 0))
    goto LABEL_36;
  SE(0);
  RSpecialSkillSelectRememberCsr();
  RSpecialSkillSetBattleSkill();
  SetSkillNameDraw(instance, 0, 0);
  ChangeState(1);
  RSpecialSkillSelectChange(m_change_listTop);
  v18 = RSpecialSkillGetSelectListState();
  v19 = v18;
  if (v19 == 1)
  {
    v19 = 14;
    v20 = 14;
    v20 = v19;
  }
  else
  {
    if (v19)
      goto LABEL_81;
    v20 = 0;
  }
  HIDWORD(skillListSelect) = v20;
LABEL_81:
  RSpecialSkillGetCsrData();
  RSpecialSkillSetListDisplayRight();
  RSpecialSkillDrawScrollBar();
  v43 = m_change_listTop;
  if (v43 != 1)
  {
    if (v43)
      goto LABEL_65;
    v29 = 0;
    goto LABEL_64;
LABEL_97:
    goto LABEL_64;
  }
  v46 = get_Instance(0);
  v29 = 1;
  ItfSortMenuActive(v46, 1, 0);
  goto LABEL_97;
LABEL_36:
  v21 = RSpecialSkillGetSelectListState();
  if (v21 != 1)
  {
    if (!v21)
    {
      v23 = instance;
      listDrwNo = RSpecialSkillGetNowSkillCsr()->listDrwNo;
      SetCsrActive(v23, 0, 0, listDrwNo, 0);
    }
    return;
  }
  v37 = instance;
  v38 = RSpecialSkillGetNowPossSkilCsr()->listDrwNo;
  SetCsrActive(v37, 0, 1, v38, 0);
}
