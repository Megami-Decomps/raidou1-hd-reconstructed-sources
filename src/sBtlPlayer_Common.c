#include "types.h"
#include "SKLID.h"
#include "dat.h"
#include "sbtl.h"
#include "sbtlaction.h"
#include "sbtldmg.h"
#include "sbtlexp.h"
#include "sbtlplayer.h"
#include "sbtlplayer_common.h"
#include "sbtlplayer_ground.h"
#include "sbtlplayer_gunshot.h"
#include "sbtlplayer_jigenkiri.h"
#include "sbtlplayer_kaiten.h"
#include "sbtlplayer_magic.h"
#include "sbtlplayer_magic2.h"
#include "sbtlplayer_magic3.h"
#include "sbtlplayer_magic4.h"
#include "sbtlplayer_magic5.h"
#include "sbtlplayer_magic6.h"
#include "sbtlplayer_sddash.h"
#include "sbtlplayer_sdshot.h"
#include "sbtlplayer_spirit.h"
#include "sbtlweapon.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

// 0x20e5490
s32 sBtlPlayerRSkillInit(SBTLUNIT_WORK *wk, SKLID _SklID, s32 _ClearIndex) {
  s32 v7;
  s32 result;
  s32 v10;
  SBTLUNIT_WORK *v13;
  SBATTLE_WORK *v17;

  if (!SklID)
    return 0;
  if (SklID <= 65)
  {
    if (SklID <= 23)
    {
      if (SklID == 8)
      {
        sBtlResetAction(wk);
        sBtlPlayerRMagicInit(wk, 8, ClearIndex);
        v10 = 200;
        v13 = wk;
        v7 = 8;
        goto LABEL_89;
      }
      if (SklID == 23)
      {
        sBtlResetAction(wk);
        sBtlPlayerRMagicInit(wk, 23, ClearIndex);
        v7 = 23;
        v10 = 200;
        goto LABEL_88;
      }
    }
    else if ((u32)SklID <= 0x37)
    {
      if (SklID == 39)
      {
        sBtlResetAction(wk);
        sBtlPlayerRMagicInit(wk, 39, ClearIndex);
        v7 = 39;
        v10 = 200;
        goto LABEL_88;
      }
      if (SklID == 55)
      {
        sBtlResetAction(wk);
        sBtlPlayerRMagicInit(wk, 55, ClearIndex);
        v7 = 55;
        v10 = 200;
        goto LABEL_88;
      }
    }
    else
    {
      if (SklID == 64)
      {
        sBtlResetAction(wk);
        sBtlPlayerRGroundInit(wk, 64, ClearIndex);
        v10 = 200;
        v13 = wk;
        v7 = 64;
        goto LABEL_89;
      }
      if (SklID == 65)
      {
        sBtlResetAction(wk);
        sBtlPlayerRMagic2Init(wk, 65, ClearIndex);
        v7 = 65;
        goto LABEL_87;
      }
    }
    return 0;
  }
  if ((u32)SklID > 0xD0)
  {
    if ((u32)SklID <= 0x138)
    {
      if (SklID == 212)
      {
        sBtlResetAction(wk);
        sBtlPlayerRMagic3Init(wk, 212, ClearIndex);
        v7 = 212;
        goto LABEL_87;
      }
      if (SklID == 312)
      {
        sBtlResetAction(wk);
        sBtlPlayerRMagic5Init(wk, 312, ClearIndex);
        v7 = 312;
        goto LABEL_87;
      }
    }
    else
    {
      if (SklID == 313)
      {
        sBtlResetAction(wk);
        sBtlPlayerRMagic6Init(wk, 313, ClearIndex);
        v7 = 313;
        goto LABEL_87;
      }
      if (SklID == 744)
      {
        sBtlResetAction(wk);
        sBtlPlayerRMagic4Init(wk, 744, ClearIndex);
        v7 = 744;
LABEL_87:
        v10 = 90;
LABEL_88:
        v13 = wk;
LABEL_89:
        sBtlSetSuperArmor(v13, v7, v10);
        v17 = wk;
        v17->bHuumaCancel = 0;
        v17->ComboMotRetryCnt = 0;
        v17->ComboMotRetryUse = 0;
        return 2;
      }
    }
    return 0;
  }
  if ((u32)SklID > 0xA3)
  {
    if (SklID == 191)
    {
      sBtlResetAction(wk);
      sBtlPlayerRGunShotInit(wk, 191, ClearIndex);
      v7 = 191;
      v10 = 200;
      goto LABEL_88;
    }
    if (SklID == 208)
    {
      sBtlResetAction(wk);
      sBtlPlayerRMagic3Init(wk, 208, ClearIndex);
      v7 = 208;
      goto LABEL_87;
    }
    return 0;
  }
  result = 0;
  switch (SklID)
  {
    case 156:
      sBtlResetAction(wk);
      sBtlPlayerRSdDashInit(wk, 156, ClearIndex);
      v7 = 156;
      v10 = 600;
      goto LABEL_88;
    case 157:
      sBtlResetAction(wk);
      sBtlPlayerRJigenKiriInit(wk, 157, ClearIndex);
      v7 = 157;
      v10 = 200;
      goto LABEL_88;
    case 158:
      sBtlResetAction(wk);
      sBtlPlayerRKaitenInit(wk, 158, ClearIndex);
      v7 = 158;
      v13 = wk;
      v10 = 60;
      goto LABEL_89;
    case 163:
      sBtlResetAction(wk);
      sBtlPlayerRSdShotInit(wk, 163, ClearIndex);
      v7 = 163;
      v10 = 200;
      goto LABEL_88;
    default:
      return result;
  }
  return result;
}

// 0x20e6ea0
void sBtlPlayerRSkill_CoolTimeClr(SBTLUNIT_WORK *wk, s32 _ClearIndex) {
  sBtlRaidouWazaCoolTimeClr(ClearIndex);
  sBtlRwazaSpiritAdd();
  sBtlCombSklTrophyUpdate();
}

// 0x20e6f70
bool sBtlPlayerRSkillCancel_Setsuma(SBTLUNIT_WORK *wk) {
  s32 v4;
  s32 v5;

  goto LABEL_3;
LABEL_13:
  LOBYTE(v4) = 0;
  return v4;
LABEL_3:
  if (!wk->bSetsuma)
    goto LABEL_13;
  v4 = sBtlInputChkSetsuma(wk);
  if (v4)
  {
    v5 = v4;
    sBtlResetAction(wk);
    sBtlSetFirstAtk(v5);
    LOBYTE(v4) = 1;
  }
  return v4;
}

// 0x20e7080
bool sBtlPlayerRSkillCancel_RSptrit(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  _BOOL4 bSpiritSkill;

  v4 = wk;
  bSpiritSkill = v4->bSpiritSkill;
  if (!v4->bSpiritSkill)
    return bSpiritSkill;
  sBtlResetAction(wk);
  sBtlPlayerRSpiritInit(wk);
  return bSpiritSkill;
}

// 0x20e71b0
bool sBtlPlayerRSkillCancel_Skill(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v5;
  s32 v10;

  v5 = wk;
  if (v5->bRaiSkill_RU)
  {
    return sBtlPlayerRSkillInit(wk, GBWK->player->raidouSkill[0], 0) != 0;
  }
  if (v5->bRaiSkill_RL)
  {
    return sBtlPlayerRSkillInit(wk, GBWK->player->raidouSkill[1], 1) != 0;
  }
  if (v5->bRaiSkill_RD)
  {
    return sBtlPlayerRSkillInit(wk, GBWK->player->raidouSkill[2], 2) != 0;
  }
  v5 = wk;
  if (v5->bRR)
    goto LABEL_67;
  v5 = wk;
  if (v5->bRR_Assist)
  {
LABEL_67:
    sBtlBS_LASTB1_Action_Req();
    sBtlResetAction(wk);
    v10 = 1310;
LABEL_35:
    sBtlSetFirstAtk(v10);
    return 1;
  }
  v5 = wk;
  if (v5->bComboSRU)
    goto LABEL_68;
  v5 = wk;
  if (v5->bRU_Assist)
  {
LABEL_68:
    sBtlBS_LASTB1_Action_Req();
    if (sBtlDat()->m_type == 1)
    {
      sBtlResetAction(wk);
      v10 = 1323;
      goto LABEL_35;
    }
    if (sBtlDat()->m_type == 2)
    {
      sBtlResetAction(wk);
      v10 = 1333;
      goto LABEL_35;
    }
    if (sBtlDat()->m_type == 3)
    {
      sBtlResetAction(wk);
      v10 = 1339;
      goto LABEL_35;
    }
    return 0;
  }
  v5 = wk;
  if (!v5->bComboLRU)
    return 0;
  sBtlResetAction(wk);
  sBtlSetUseSkill(wk, 0, 0);
  sBtlSetAction(wk, 1, 0);
  return 1;
}

// 0x20e7610
bool sBtlPlayerRSkillCancel_Move(SBTLUNIT_WORK *wk) {
  bool IsMoveBtn;

  IsMoveBtn = sBtlIsMoveBtn(wk);
  if (!IsMoveBtn)
    return IsMoveBtn;
  sBtlResetAction(wk);
  sBtlSetUseSkill(wk, 0, 0);
  return IsMoveBtn;
}

// 0x20e7730
bool sBtlPlayerRSkillCancel_Huuma(SBTLUNIT_WORK *wk) {
  wk->bHuumaCancel = 1;
  if (IsSceanStop())
    return 0;
  if (sBtlNormalProc_Huuma(wk, 0) == 2)
    return 1;
  return 0;
}

// 0x20e7850
bool sBtlPlayerRSkillCancel_Guard(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  _BOOL4 bGuard;

  v4 = wk;
  bGuard = v4->bGuard;
  if (!v4->bGuard)
    return bGuard;
  sBtlResetAction(wk);
  sBtlSetUseSkill(wk, 0, 0);
  return bGuard;
}

// 0x20e7980
bool sBtlPlayerRSkillCancel_Jump(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  _BOOL4 bJump;

  v4 = wk;
  bJump = v4->bJump;
  if (!v4->bJump)
    return bJump;
  sBtlResetAction(wk);
  sBtlJumpStart(wk);
  return bJump;
}

// 0x20e7a70
bool sBtlPlayerRSkillCancel_Kaihi(SBTLUNIT_WORK *wk) {
  bool IsBattleKey;

  IsBattleKey = sBtlIsBattleKey(4124, 2);
  if (!IsBattleKey)
    return IsBattleKey;
  sBtlResetAction(wk);
  sBtlKaihiInit(wk);
  return IsBattleKey;
}

// 0x20e7b50
bool sBtlPlayerRSkillCancel_Gun(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  _BOOL4 bGunMode;

  v4 = wk;
  bGunMode = v4->bGunMode;
  if (!v4->bGunMode)
    return bGunMode;
  sBtlResetAction(wk);
  sBtlChangeGunMode(wk);
  return bGunMode;
}

// 0x20e7c40
bool sBtlPlayerIsRSkillCancel(void) {
  return (u32)(wk->mode - 21) < 0xD;
}
