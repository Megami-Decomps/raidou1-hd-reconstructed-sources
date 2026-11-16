#pragma once
#include "types.h"
#include "kernel.h"

typedef enum {
    DEFAULT_OT = 109,
    ANALYZE_OT = 110,
    GAUGE_OT = 109,
    NUMFNT_W = 9,
    NUMFNT_H = 12,
} SBTLDRAW;

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct S_MapStatusBar S_MapStatusBar;
typedef struct effCtexHandle_t effCtexHandle_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;
typedef struct sprHandle_t sprHandle_t;

struct S_MapStatusBar {
    sprHandle_t *m_hSpr;
    s32 m_stkIdx;
    void *m_CachepDataIcon;
    s32 m_loadStep;
};

extern char *g_strPlayerName;
extern S_MapStatusBar *g_MapStatusBar;
extern s32 gAddMagNum;
extern s32 gAddMagNumDrawCnt;
extern s32 gAddMagNumNow;
extern s32 gAddMagNumUp;
extern s32 g_RedCnt;
extern f32 f_uncnt;
extern bool g_bDrawNakamaIcon;
extern s32 g_cntTgtCur;
extern s32 g_cntViceMax;
extern s32 g_cntViceUp;
extern s32 g_oldVice;
extern s32 g_cntHuuma;
extern s32 g_oldHuuma;
extern s32 g_cntEscape;
extern s32 g_cntDangerPly;
extern s32 g_cntDangerDvl;
extern s32 g_cntDamagePly;
extern s32 g_cntDamageDvl;
extern s32 g_oldHpPly;
extern s32 g_oldHpDvl;
extern s32 g_devilID_sav;
extern s32 g_mag_sav;
extern s32 g_cntPanelPly;
extern s32 g_cntPanelDvl;
extern s8 g_typPanelPly;
extern s8 g_typPanelDvl;
extern s16 ggAnmCnt;
extern s32 gTargetPosHokanFastFlag;
extern f32 g_fHelpRed;
extern sdfVector4_t gTargetPosHokanBuff0;
extern sdfVector4_t gTargetPosHokanBuff1;
extern sdfVector4_t gTargetPosHokanBuff2;
extern sdfVector4_t gTargetPosHokanBuff3;
extern sdfVector4_t gTargetPosHokanBuff4;

s32 sBtlFont(s32 a_x, s32 a_y, u8 a_type, u32 a_color, u8 a_alphaRate, u32 a_ot, char *a_str);
void sBtlParam(u16 a_type, s32 a_x, s32 a_y, u8 a_alphaRate, u32 a_ot, u32 now, u32 max, bool a_bSecret, sdatUnitWork_t *unit);
void sBtlNum3(s32 a_x, s32 a_y, u32 a_rgba, u8 a_alphaRate, s32 a_num, DDS3_OT a_ot, f32 scale, u32 rinkaku_rgba);
void sBtlIcon(s32 a_x, s32 a_y, u8 a_alpha, s32 a_sprNo, DDS3_OT a_ot);
void sBtlInitAddMag(void);
void SetAddMag(s32 num);
void DrawAddMag(s32 x, s32 y);
void sBtlBadStatusIcon(s32 a_x, s32 a_y, u8 a_alpha, DDS3_OT a_ot, sdatUnitWork_t *unit);
void sBtlMoonOff(void);
bool sBtlBarCtrl(void);
void DrawStatusBar(sdatUnitWork_t *pUnit, effCtexHandle_t *cTex, s32 y, s32 mode, s32 idx);
void sBtlMap_Init(void);
bool sBtlChkTutorial(void);
char *sBtlGetPlayerNameEx(u8 a_type);
char *sBtlGetPlayerName(void);
void sBtlSetNakamaIconOn(void);
void sBtlSetNakamaIconOff(void);
void Init(void);
void sBtlInitDevil(void);
char *sBtlGetRaceName(s32 a_raceID);
void sBtlSpriteEx(s32 a_x, s32 a_y, u8 a_alpha, s32 a_sprNo, DDS3_OT a_ot);
void sBtlSprite(s32 a_x, s32 a_y, u8 a_alpha, s32 a_sprNo);
void sBtlNum(s32 a_x, s32 a_y, u32 a_rgba, u8 a_alphaRate, s32 a_num, DDS3_OT a_ot);
void sBtlDrawNum4(s32 a_x, s32 a_y, u32 a_rgba, u8 a_alphaRate, s32 a_num, u32 a_ot, f32 scale, u32 rinkaku_rgba, f32 a_size);
s32 sBtlFontCenter(s32 a_x, s32 a_y, s32 a_wMax, u32 a_color, u8 a_alphaRate, DDS3_OT a_ot, char *a_str);
void sBtlNumFont(s32 a_x, s32 a_y, u32 a_color, u8 a_alphaRate, DDS3_OT a_ot, char *a_str);
void sBtlMagnetiteData(void);
void sBtlPlayerData(void);
void sBtlSummonDevilAshimotoReset(SBTLUNIT_WORK *wk);
void sBtlSummonDevilAshimoto(SBTLUNIT_WORK *wk, s32 idx);
void sBtlSummonDevilData_Sub(SBTLUNIT_WORK *wk, s32 idx);
void sBtlSummonDevilData(void);
void sBtlEnemyData(void);
sdfVector4_t sBtlGetGagePos(SBTLUNIT_WORK *pBtlUnit);
sdfVector4_t sBtlGetChestPos(SBTLUNIT_WORK *pBtlUnit);
void sBtlDrawBossHP(SBTLUNIT_WORK *wk);
void sBtlAnalyzeBackEx(u8 a_type, s32 a_x, s32 a_y, u8 a_alphaRate, sprHandle_t *a_hSpr);
void sBtlAnalyzeBack(u8 a_type, u8 a_alphaRate);
void sBtlAnalyzeLvEx(sdatUnitWork_t *unit, s32 a_x, s32 a_y, u8 a_alphaRate, bool a_bSecret, sprHandle_t *a_hSpr);
void sBtlAnalyzeLv(sdatUnitWork_t *unit, u8 a_alphaRate, bool a_bSecret);
void sBtlAnalyzeHpEx(sdatUnitWork_t *unit, s32 a_x, s32 a_y, u8 a_alphaRate, bool a_bSecret, sprHandle_t *a_hSpr);
void sBtlAnalyzeHp(sdatUnitWork_t *unit, u8 a_alphaRate, bool a_bSecret);
void sBtlAnalyzeLoyalty(sdatUnitWork_t *unit, s32 a_x, s32 a_y, u8 a_alphaRate, sprHandle_t *a_hSpr);
void sBtlAnalyzeSkill(s32 a_type, s32 a_x, s32 a_y, u32 a_rgba, u8 a_alphaRate, char *a_str);
void sBtlSkillData(s32 a_skillid, s32 a_x, s32 a_y, u32 a_rgba, u8 a_alphaRate, char *a_str);
void sBtlAnalyzeAisyo(s32 a_type, s32 a_devilID, u8 a_alphaRate);
void sBtlAnalyzeTalkSkill(s32 a_devilId, u8 a_alphaRate);
void sBtlAnalyzeMeisi(s32 a_devilId, u8 a_alphaRate, s32 a_y_ofs);
void sBtlAnalyzePlayer(sdatUnitWork_t *unit, u8 a_alphaRate);
void sBtlAnalyzeBoss(SBTLUNIT_WORK *wk, u8 a_alphaRate);
void sBtlAnalyzeEnemy(SBTLUNIT_WORK *wk, u8 a_alphaRate);
void sBtlNakamaCursor(SBTLUNIT_WORK *wk, const sdfVector4_t *pos);
void sBtlTargetNoCursor(const sdfVector4_t *pos, char *str, s32 _num);
void sBtlTargetCursor(const sdfVector4_t *pos, char *str);
void sBtlResetTargetCursor(void);
bool sBtlSelectTargetCursorSub(SBTLUNIT_WORK *wk, bool bDrawName);
bool sBtlSelectTargetCursor(bool bDrawName);
void sBtlHelpEx(s32 a_type, s32 a_num, sprHandle_t *a_hSpr, u8 a_alphaRate);
void sBtlHelp(s32 a_type, s32 a_num, u8 a_alphaRate);
void sBtlHelpCantUseEx(s32 a_type, s32 a_num, sprHandle_t *a_hSpr, u8 a_alphaRate);
void sBtlHelpCantUse(s32 a_type, s32 a_num, u8 a_alphaRate);
void sBtlEscapeGauge(s32 a_cnt, s32 a_max);
void sBtlResetEscapeGauge(void);
void sBtlDamagePanelE(const sdfVector4_t *pos, s32 dmg, u32 rgba, u32 rgba2, f32 a_size, s32 dispmode, bool weak_k);
void sBtlDamagePanelN(const sdfVector4_t *pos, s32 dmg, u32 rgba, u32 rgba2, s32 minor, s32 uniq_code, f32 a_size);
void sBtlDamagePanelR(const sdfVector4_t *pos, s32 dmg, u32 rgba, u32 rgba2, f32 a_size);
void DrawTime(void);
