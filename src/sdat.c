#include "types.h"
#include "SKLID.h"
#include "dat.h"
#include "sbtlcalc.h"
#include "sbtlsub.h"
#include "sdat.h"

#define GIFT_TBL_MAX 4

typedef struct sdatLvUpDevilGift_t sdatLvUpDevilGift_t;
typedef struct sdatLvUpDevilParamUp_t sdatLvUpDevilParamUp_t;
typedef struct sdatLvUpPlayerParamUp_t sdatLvUpPlayerParamUp_t;
typedef struct sdatLvUpPlayerRankUp_t sdatLvUpPlayerRankUp_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

static sdatLvUpDevilParamUp_t *LvUpDevilParamUp[80];
static sdatLvUpDevilParamUp_t *LvUpDevilParamUp2;
static sdatLvUpDevilParamUp_t *LvUpDevilParamUp3;
sdatLvUpPlayerParamUp_t *sdatLvUpPlayerParamUp;
sdatLvUpPlayerRankUp_t *sdatLvUpPlayerRankUp;

// 0x18e8a70
char *sdatRaceName(s32 id) {
  return sBtlGetRaceNameFont(id);
}

// 0x18e8b00
char *sdatDevilName(s32 id, bool label) {
  return sBtlGetDevilNameFont(id, label);
}

// 0x18e8b70
char *sdatSkillName(s32 id) {
  return sBtlGetSkillNameFont(id);
}

// 0x18e8c00
char *sdatItemName(s32 id) {
  return sBtlGetItemNameFont(id);
}

// 0x18e8c90
char *sdatItemHelp(s32 id, bool label) {
  return sBtlGetItemHelpFont(id, label);
}

// 0x18e8d00
char *sdatParHelp(s32 id, bool label) {
  return sBtlGetParHelpFont(id, label);
}

// 0x18e8d70
char *sdatSkillHelp(s32 id, bool label) {
  return sBtlGetSkillHelpFont(id, label);
}

// 0x18e8de0
char *sdatAisyoHelp(s32 id) {
  return sBtlGetAisyoHelpFont(id);
}

// 0x18e8e70
char *sdatTalkName(s32 id) {
  return sBtlGetWajutsuNameFont(id);
}

// 0x18e8f00
char *sdatPlayerRankName(s32 id) {
  return sBtlGetPlayerRankNameFont(id);
}

// 0x18e9030
s32 sdatCalcSkill(sdatUnitWork_t *acter, sdatUnitWork_t *target, SKLID skillid) {
  return sBtlGetDamage_GB(acter, target, skillid);
}

// 0x18e90b0
s32 sdatCalcItem(sdatUnitWork_t *unit, s32 itemid) {
  return CalcItem(unit, itemid);
}

// 0x18e9120
s32 sdatCalcDrink(void) {
  return sBtlCheckDrink();
}

// 0x18e9190
s32 sdatCalc_GetBadStatus(sdatUnitWork_t *unit) {
  return sBtlGetBadStatus(unit);
}

// 0x18e9220
bool sdatCalc_CheckAnlyzBit(s32 devilid) {
  return (GBWK->anlyzBit[devilid / 32] >> devilid) & 1;
}

// 0x18e92b0
s32 sdatGetMoney(void) {
  return GBWK->player->gold;
}

// 0x18e9320
sdatLvUpDevilGift_t *sdatGetLvUpDevilGift(s32 dvlno) {
  s32 v4;

  v4 = dvlno - 1984;
  if (dvlno < 1984)
  {
    if (op_Equality(sdatLvUpDevilGiftTbl, 0, 0))
      goto LABEL_20;
    goto LABEL_15;
    if (!op_Equality(sdatLvUpDevilGiftTbl, 0, 0))
    {
LABEL_15:
      return GetTblDate(sdatLvUpDevilGiftTbl, dvlno, 0);
    }
LABEL_20:
    LogError("テーブルが読み込みされていない", 0);
    return 0;
  }
  if (op_Equality(sdatLvUpDevilGiftTbl_DLC, 0, 0))
    goto LABEL_20;
  return GetTblDate(sdatLvUpDevilGiftTbl_DLC, v4, 0);
}

// 0x18e94f0
sdatLvUpDevilParamUp_t *sdatGetLvUpDevilParamUp(s32 dvlno) {
  if (dvlno <= 335)
  {
    return LvUpDevilParamUp[dvlno];
  }
  else
  {
    if ((u32)dvlno <= 0x1EF)
    {
      return LvUpDevilParamUp2[dvlno - 336];
    }
    else
    {
      return LvUpDevilParamUp3[dvlno - 496];
    }
  }
}
