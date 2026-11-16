#pragma once
#include "types.h"
#include "SKLID.h"
#include "sbtlsub.h"

typedef struct sdatLvUpDevilGift_t sdatLvUpDevilGift_t;
typedef struct sdatLvUpDevilParamUp_t sdatLvUpDevilParamUp_t;
typedef struct sdatLvUpPlayerParamUp_t sdatLvUpPlayerParamUp_t;
typedef struct sdatLvUpPlayerRankUp_t sdatLvUpPlayerRankUp_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

struct sdatLvUpDevilGift_t {
    u16 ItemID;
    u8 Rate;
    u16 Level;
    u8 NumMax;
};

struct sdatLvUpDevilParamUp_t {
    u8 Param[4];
};

extern sdatLvUpPlayerParamUp_t *sdatLvUpPlayerParamUp;
extern sdatLvUpPlayerRankUp_t *sdatLvUpPlayerRankUp;

char *sdatRaceName(s32 id);
char *sdatDevilName(s32 id, bool label);
char *sdatSkillName(s32 id);
char *sdatItemName(s32 id);
char *sdatItemHelp(s32 id, bool label);
char *sdatParHelp(s32 id, bool label);
char *sdatSkillHelp(s32 id, bool label);
char *sdatAisyoHelp(s32 id);
char *sdatTalkName(s32 id);
char *sdatPlayerRankName(s32 id);
s32 sdatCalcSkill(sdatUnitWork_t *acter, sdatUnitWork_t *target, SKLID skillid);
s32 sdatCalcItem(sdatUnitWork_t *unit, s32 itemid);
s32 sdatCalcDrink(void);
s32 sdatCalc_GetBadStatus(sdatUnitWork_t *unit);
bool sdatCalc_CheckAnlyzBit(s32 devilid);
s32 sdatGetMoney(void);
sdatLvUpDevilGift_t *sdatGetLvUpDevilGift(s32 dvlno);
sdatLvUpDevilParamUp_t *sdatGetLvUpDevilParamUp(s32 dvlno);

// macros
// 0x19498d0: s32 PLAYER_EXP(s32 _lev)
static inline s32 PLAYER_EXP(s32 _lev) {
  f32 v2;

  v2 = (f32)((f32)((f32)lev * (f32)lev) * (f32)lev) * 1.01;
  if (v2 == INFINITY)
    return 0x80000000;
  else
    return (s32)v2;
}

// 0x1949910: s32 DEVIL_EXP_BASE(s32 _lev)
static inline s32 DEVIL_EXP_BASE(s32 _lev) {
  f32 v2;
  f32 v3;
  s32 v4;
  bool v5;
  f32 v6;
  f32 v7;
  f32 v8;

  v2 = lev;
  v3 = (f32)((f32)(v2 * v2) * v2) * 1.01;
  v4 = v3;
  v5 = v3 == INFINITY;
  v6 = -2147500000.0;
  v7 = v4;
  if (!v5)
    v6 = v7;
  v8 = (f32)((f32)(v2 * 0.001) + 1.1) * v6;
  if (v8 == INFINITY)
    return 0x80000000;
  else
    return (s32)v8;
}

// 0x1949980: s32 DEVIL_EXP(s32 _devil_id, s32 _lev)
static inline s32 DEVIL_EXP(s32 _devil_id, s32 _lev) {
  u32 v5;
  float32x2_t v6;
  float32x2_t v7;
  float32x2_t v8;
  float32x2_t v9;
  int32x2_t v10;

  LOWORD(v5) = sBtlGetDevilData(devil_id, -1)->level;
  v6.n64_f32[0] = (f32)lev;
  v6.n64_f32[1] = (f32)v5;
  v7.n64_u64[0] = vdup_n_s32(0x7F800000u).n64_u64[0];
  v8.n64_u64[0] = vmul_f32(vmul_f32(vmul_f32(v6, v6), v6), vdup_n_s32(0x3F8147AEu)).n64_u64[0];
  v9.n64_u64[0] = vmul_f32(vadd_f32(vmul_f32(v6, vdup_n_s32(0x3A83126Fu)), vdup_n_s32(0x3F8CCCCDu)), vbsl_s8(vceq_f32(v8, v7), (int8x8_t)0xCF000000CF000000LL, vcvt_f32_s32(vcvt_s32_f32(v8)))).n64_u64[0];
  v10.n64_u64[0] = vbsl_s8(vceq_f32(v9, v7), (int8x8_t)0x8000000080000000LL, vcvt_s32_f32(v9)).n64_u64[0];
  return vsub_s32(v10, vdup_lane_s32(v10, 1)).n64_u32[0];
}
