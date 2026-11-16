#include "types.h"
#include "dat.h"
#include "dds3_pad.h"
#include "rspecialskill.h"
#include "rspecialskillstatus.h"
#include "swordskill.h"

// 0x1e29280
void Init(void) {
  s32 SelectListState;
  SpecialSkillCsr *NowSkillCsr;
  s64 spiritCnt;
  SpecialSkillCsr *NowPossSkilCsr;
  u32 SwordSkillCount;
  s32 v9;
  char v10;
  void *v12;
  void *v13;
  void *v14;
  void *v15;

  RSpecialSkillGetHaveSwordSkill();
  RSpecialSkillIsSwordSkillSort();
  RSpecialSkillSetTab(1);
  RSpecialSkillLosdListSide(1);
  SelectListState = RSpecialSkillGetSelectListState();
  RSpecialSkillSetBeforeIdx(SelectListState);
  NowSkillCsr = RSpecialSkillGetNowSkillCsr();
  spiritCnt = (u32)GBWK->player->spiritCnt;
  (NowSkillCsr->klass->vtable._5_SetMaxPar.methodPtr)(NowSkillCsr, spiritCnt, (u32)spiritCnt, NowSkillCsr->klass->vtable._5_SetMaxPar.method);
  NowPossSkilCsr = RSpecialSkillGetNowPossSkilCsr();
  SwordSkillCount = RSpecialSkillGetSwordSkillCount();
  (NowPossSkilCsr->klass->vtable._5_SetMaxPar.methodPtr)(NowPossSkilCsr, SwordSkillCount, 6, NowPossSkilCsr->klass->vtable._5_SetMaxPar.method);
  RSpecialSkillSetBarLength();
  RSpecialSkillInitListDisp();
  InitUseButtonImage(instance);
  SetActive(instance->m_battle_panel->image_base_obj, 0, 0);
  SetActive(instance->m_battle_panel->skill_list_obj, 0, 0);
  SetActive(instance->m_sword_panel->image_base_obj, 1, 0);
  SetActive(instance->m_sword_panel->skill_list_obj, 1, 0);
  RSpecialSkillGetCsrData();
  RSpecialSkillSetInfo();
  v9 = RSpecialSkillGetSelectListState();
  v10 = v9 != 0;
  if (!v9)
  {
    v10 = 0;
LABEL_21:
    v12 = get_Instance(0);
    ItfSortMenuActive(v12, v10, 0);
    goto LABEL_22;
  }
  if (RSpecialSkillGetSelectListState() != 1)
    goto LABEL_22;
  v10 = 1;
  goto LABEL_21;
LABEL_22:
  v13 = get_Instance(0);
  v14 = Allocate(System_Action);
  _ctor(v14, 0, Method_Project_RSpecialSkillStatus_SwordSkillSortFunc__, 0);
  v15 = Allocate(System_Action);
  _ctor(v15, 0, Method_Project_RSpecialSkillStatus_EndSwordSkillSortFunc__, 0);
  SetActiveCallBack(v13, v14, v15, 0);
}

// 0x1e295b0
void Update(void) {
  State = GetState();
  if ((u32)State == 2)
  {
    SelectUpdate();
    return;
  }
  if ((u32)State == 1)
    NoramalUpdate();
}

// 0x1e29f20
void Draw(void) {
  s32 SelectListState;

  SelectListState = RSpecialSkillGetSelectListState();
  if (SelectListState == 1)
  {
    RSpecialSkillSetListDisplayRight();
    RSpecialSkillDrawScrollBar();
    goto LABEL_10;
  }
  if (!SelectListState)
  {
    RSpecialSkillSetListDisplayLeft();
  }
LABEL_10:
  RSpecialSkillSkillCsrColorReset();
  RSpecialSkillSKillCsrReset();
  RSpecialSkillDrawHelpText();
}

// 0x1e29650
void NoramalUpdate(void) {
  s32 SelectListState;
  s32 v3;
  SpecialSkillCsr *NowSkillCsr;
  s32 v7;
  void *v8;
  void *v9;
  SpecialSkillCsr *NowPossSkilCsr;

  SelectListState = RSpecialSkillGetSelectListState();
  if (SelectListState != 1)
  {
    if (!SelectListState)
    {
      if (CHECK_TRIG(4096, 0))
      {
        SE(0);
        RSpecialSkillSelectRememberCsr();
        RSpecialSkillGetChangeSource();
        ChangeState(2);
        RSpecialSkillSelectChange(1);
        v3 = RSpecialSkillGetSelectListState();
        RSpecialSkillSetBeforeIdx(v3);
        RSpecialSkillSelectGetCsrData();
        RSpecialSkillSetInfo();
      }
      else
      {
        NowSkillCsr = RSpecialSkillGetNowSkillCsr();
        SetCsrActive(instance, 1, 0, NowSkillCsr->listDrwNo);
        if (CHECK_TRIG(45327, 1))
        {
          RSpecialSkillCancelSetting();
        }
      }
    }
    return;
  }
  if (!RSpecialSkillIsHaveSKill(1, 1))
    goto LABEL_34;
  goto LABEL_9001;
  if (!RSpecialSkillIsHaveSKill(1, 1))
  {
LABEL_34:
    v9 = instance;
    NowPossSkilCsr = RSpecialSkillGetNowPossSkilCsr();
    SetCsrActive(v9, 1, 1, NowPossSkilCsr->listDrwNo);
    return;
  }
LABEL_9001:
  if (!CHECK_TRIG(4096, 0))
    goto LABEL_34;
  SE(0);
  RSpecialSkillSelectRememberCsr();
  RSpecialSkillGetChangeSource();
  ChangeState(2);
  RSpecialSkillSelectChange(0);
  v7 = RSpecialSkillGetSelectListState();
  RSpecialSkillSetBeforeIdx(v7);
  RSpecialSkillSelectGetCsrData();
  RSpecialSkillSetInfo();
  v8 = get_Instance(0);
  ItfSortMenuActive(v8, 0, 0);
}

// 0x1e29990
void SelectUpdate(void) {
  s32 v2;
  s32 v5;
  s32 v6;
  void *v7;
  s32 v11;
  s32 SelectListState;
  s32 listDrwNo;
  void *v18;
  s32 v19;
  void *v20;
  void *v21;

  if (!CHECK_TRIG(4097, 0))
  {
    if (!RSpecialSkillConfigurable())
    {
LABEL_50:
      SelectListState = RSpecialSkillGetSelectListState();
      if (SelectListState != 1)
      {
        if (SelectListState)
          return;
        listDrwNo = RSpecialSkillGetNowSkillCsr()->listDrwNo;
        v18 = instance;
        v19 = 0;
LABEL_58:
        SetCsrActive(v18, 1, v19, listDrwNo);
        return;
      }
      v20 = instance;
      listDrwNo = RSpecialSkillGetNowPossSkilCsr()->listDrwNo;
      v18 = v20;
      v19 = 1;
      goto LABEL_58;
    }
    if (!CHECK_TRIG(4096, 0))
      goto LABEL_50;
    SE(0);
    RSpecialSkillSelectRememberCsr();
    RSpecialSkillSetSwordSkill();
    RSpecialSkillSwordListAutoArrange();
    SetSkillNameDraw(instance, 1);
    ChangeState(1);
    RSpecialSkillSelectChange(m_change_listTop);
    v11 = RSpecialSkillGetSelectListState();
    RSpecialSkillSetBeforeIdx(v11);
    RSpecialSkillGetCsrData();
    RSpecialSkillSetInfo();
    if (m_change_listTop != 1)
    {
      if (m_change_listTop)
        goto LABEL_29;
      v6 = 0;
      goto LABEL_28;
LABEL_72:
      goto LABEL_28;
    }
    v21 = get_Instance(0);
    v6 = 1;
    ItfSortMenuActive(v21, 1, 0);
    goto LABEL_72;
  }
  SE(1);
  RSpecialSkillSelectRememberCsr();
  ChangeState(1);
  RSpecialSkillSelectChange(m_change_listTop);
  v2 = RSpecialSkillGetSelectListState();
  RSpecialSkillSetBeforeIdx(v2);
  RSpecialSkillGetCsrData();
  RSpecialSkillSetInfo();
  v5 = m_change_listTop;
  if (v5 == 1)
  {
    v7 = get_Instance(0);
    v6 = 1;
    ItfSortMenuActive(v7, 1, 0);
    goto LABEL_27;
  }
  if (!v5)
  {
    v6 = 0;
LABEL_27:
LABEL_28:
    SetCursorSprite(instance, 1, 1, v6);
    goto LABEL_29;
  }
LABEL_29:
  RSpecialSkillSetChangeSource();
}
