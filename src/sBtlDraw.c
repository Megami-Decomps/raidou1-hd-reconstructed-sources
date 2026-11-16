#include "types.h"
#include "buttonguide.h"
#include "cmpitem.h"
#include "cmpstatus.h"
#include "dat.h"
#include "dds3basic.h"
#include "dds3objectbase.h"
#include "evtbit.h"
#include "itf.h"
#include "kernel.h"
#include "sbtl.h"
#include "sbtlcalc.h"
#include "sbtlcamera.h"
#include "sbtldraw.h"
#include "sbtlevent.h"
#include "sbtlmain.h"
#include "sbtlmenu.h"
#include "sbtlscene.h"
#include "sbtlskill.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sbtlvisual.h"
#include "sdat.h"
#include "sdf_vu0.h"
#include "sdfmodel.h"
#include "smnr.h"

#define DEF_ANALYSE_Y 88
#define DEF_PLAYER_PNL_X 100
#define DEF_FACE_W 25
#define DEF_NAME_X 9
#define DEF_PLAYER_PNL_Y 10
#define DEF_PLAYER_PNL_H 27
#define DEF_GUAGE_Y_LCL 14
#define DEF_GUAGENUM_X 63
#define DEF_GUAGE_OFS_X 3
#define DEF_MAGGG_W 107
#define BTLDRAW_TIME_PANEL_X 36
#define BTLDRAW_TIME_PANEL_Y 380
#define BTLDRAW_TIME_MIN_X 8
#define BTLDRAW_TIME_SEC_X 104

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct S_MapStatusBar S_MapStatusBar;
typedef struct effCtexHandle_t effCtexHandle_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;
typedef struct sprHandle_t sprHandle_t;

char *g_strPlayerName;
S_MapStatusBar *g_MapStatusBar;
s32 gAddMagNum;
s32 gAddMagNumDrawCnt;
s32 gAddMagNumNow;
s32 gAddMagNumUp;
s32 g_RedCnt;
f32 f_uncnt;
bool g_bDrawNakamaIcon;
s32 g_cntTgtCur;
s32 g_cntViceMax;
s32 g_cntViceUp;
s32 g_oldVice;
s32 g_cntHuuma;
s32 g_oldHuuma;
s32 g_cntEscape;
s32 g_cntDangerPly;
s32 g_cntDangerDvl;
s32 g_cntDamagePly;
s32 g_cntDamageDvl;
s32 g_oldHpPly;
s32 g_oldHpDvl;
s32 g_devilID_sav;
s32 g_mag_sav;
s32 g_cntPanelPly;
s32 g_cntPanelDvl;
s8 g_typPanelPly;
s8 g_typPanelDvl;
s16 ggAnmCnt;
s32 gTargetPosHokanFastFlag;
f32 g_fHelpRed;
sdfVector4_t gTargetPosHokanBuff0;
sdfVector4_t gTargetPosHokanBuff1;
sdfVector4_t gTargetPosHokanBuff2;
sdfVector4_t gTargetPosHokanBuff3;
sdfVector4_t gTargetPosHokanBuff4;

static void PlayerStatusDraw(SBTLUNIT_WORK *pBtlUnit);
static void DrawBulletUI(SBTLUNIT_WORK *wk);
static void DrawHpGageHD(SBTLUNIT_WORK *pBtlUnit);
static void DrawEnemyName(SBTLUNIT_WORK *pBtlUnit);
static s32 CalcEatkNotice(SBTLUNIT_WORK *pBtlUnit);

// 0x2067360
s32 sBtlFont(s32 a_x, s32 a_y, u8 a_type, u32 a_color, u8 a_alphaRate, u32 a_ot, char *a_str) {
  return 0;
}

// 0x2067370
void sBtlParam(u16 a_type, s32 a_x, s32 a_y, u8 a_alphaRate, u32 a_ot, u32 now, u32 max, bool a_bSecret, sdatUnitWork_t *unit) {
  ;
}

// 0x2067380
void sBtlNum3(s32 a_x, s32 a_y, u32 a_rgba, u8 a_alphaRate, s32 a_num, DDS3_OT a_ot, f32 scale, u32 rinkaku_rgba) {
  ;
}

// 0x2067390
void sBtlIcon(s32 a_x, s32 a_y, u8 a_alpha, s32 a_sprNo, DDS3_OT a_ot) {
  ;
}

// 0x20673a0
void sBtlInitAddMag(void) {
  *(u64 *)&gAddMagNum = 0;
  *(u64 *)&gAddMagNumNow = 0;
  return;
}

// 0x2067420
void SetAddMag(s32 num) {
  s32 v5;
  s32 v6;

  v5 = gAddMagNum + num;
  gAddMagNum = v5;
  gAddMagNumDrawCnt = 100;
  v6 = v5 - gAddMagNumNow;
  gAddMagNumUp = v6 / 8;
  if (v6 <= 7)
  {
    gAddMagNumUp = 1;
  }
}

// 0x20674e0
void DrawAddMag(s32 x, s32 y) {
  s32 v9;

  if ((wk->status3 & 2) == 0)
  {
LABEL_23:
    goto LABEL_24;
LABEL_35:
    v9 = gAddMagNumUp + gAddMagNumNow;
    gAddMagNumNow = v9;
    if (v9 <= gAddMagNum)
      goto LABEL_37;
    gAddMagNumNow = gAddMagNum;
LABEL_38:
    if (gAddMagNumDrawCnt > 0)
      goto LABEL_39;
    *(u64 *)&gAddMagNum = 0;
    *(u64 *)&gAddMagNumNow = 0;
    return;
  }
  if (gAddMagNumDrawCnt != 90)
    goto LABEL_19;
  sBtlPlaySE(0x10020u);
  if (gAddMagNum > 100)
    goto LABEL_19;
  goto LABEL_17;
  if (gAddMagNum > 100)
LABEL_17:
LABEL_19:
  if (gAddMagNumDrawCnt != 80)
  {
    goto LABEL_22;
  }
  sBtlPlaySE(0x10020u);
LABEL_22:
  if (gAddMagNumDrawCnt != 70)
    goto LABEL_23;
  sBtlPlaySE(0x10020u);
LABEL_24:
  if (gAddMagNumNow < gAddMagNum)
    goto LABEL_35;
LABEL_37:
  goto LABEL_38;
LABEL_39:
  if (gAddMagNumNow < gAddMagNum)
  {
    goto LABEL_42;
  }
  --gAddMagNumDrawCnt;
LABEL_42:
  if (gAddMagNumDrawCnt > 9)
  {
LABEL_55:
    goto LABEL_56;
  }
  goto LABEL_55;
LABEL_56:
  if ((wk->status3 & 2) == 0)
    return;
  if ((gAddMagNumDrawCnt & 1) == 0)
    return;
}

// 0x20679a0
void sBtlBadStatusIcon(s32 a_x, s32 a_y, u8 a_alpha, DDS3_OT a_ot, sdatUnitWork_t *unit) {
  if (unit)
  {
    sBtlGetBadStatus(unit);
  }
}

// 0x2067a20
void sBtlMoonOff(void) {
  wk->barCtrl->barStart = 40;
}

// 0x2067a90
bool sBtlBarCtrl(void) {
  return 1;
}

// 0x2067aa0
void DrawStatusBar(sdatUnitWork_t *pUnit, effCtexHandle_t *cTex, s32 y, s32 mode, s32 idx) {
  s64 v10;
  STATUS_BAR *v12;
  s32 cnt;
  s32 v15;
  s32 v16;
  s32 v17;
  s32 v18;
  s32 IntervalRand;
  s32 v21;
  SBATTLE_WORK *v23;
  sdatParaWork_t *now;
  signed s32 hp;
  s64 v26;
  SBATTLE_WORK *v27;
  s32 grnCnt;
  s32 barLong;
  s32 devilid;
  u32 PlayerLuckStep;

  v10 = idx;
  if (wk->aRedGuage[idx]->bgn > pUnit->now->hp)
  {
    wk->aStatusBar[idx]->cnt = 40;
  }
  v12 = wk->aStatusBar[idx];
  cnt = v12->cnt;
  if (cnt)
  {
    v15 = cnt - 1;
    v12->cnt = v15;
    if (v15)
    {
      v12 = wk->aStatusBar[idx];
      v15 = v12->cnt;
      v16 = v15 / 7;
      v17 = v16 + 1;
      v18 = ~v16;
      IntervalRand = GetIntervalRand(~v16, v16 + 1);
      v12->x = IntervalRand;
      v12 = wk->aStatusBar[idx];
      v21 = GetIntervalRand(v18, v17);
LABEL_21:
      v12->y = v21;
      goto LABEL_22;
    }
    v12 = wk->aStatusBar[idx];
    v21 = 0;
    v12->x = 0;
    goto LABEL_21;
  }
LABEL_22:
  v23 = **((SBATTLE_WORK ***)sbtl + 23);
  if (v23->aStatusBar[idx]->cnt)
  {
    if (*((u32 *)sbtl + 56))
      goto LABEL_34;
    goto LABEL_30;
  }
  if (idx)
    goto LABEL_32;
  if (!*((u32 *)sbtl + 56))
  {
    v23 = wk;
  }
  if (!v23->grnCnt)
  {
LABEL_32:
    now = pUnit->now;
    hp = now->hp;
    v26 = 5153960757LL * now->maxhp;
    {
LABEL_34:
      if (idx)
        goto LABEL_41;
      goto LABEL_35;
    }
LABEL_30:
    goto LABEL_34;
  }
LABEL_35:
  v27 = **((SBATTLE_WORK ***)sbtl + 23);
  grnCnt = v27->grnCnt;
  if (grnCnt)
  {
    if (!*((u32 *)sbtl + 56))
    {
      v27 = wk;
      grnCnt = v27->grnCnt;
    }
    v27->grnCnt = grnCnt - 1;
  }
LABEL_41:
  if (*((u32 *)sbtl + 56))
  {
    barLong = (**((SBATTLE_WORK ***)sbtl + 23))->barCtrl->barLong;
    if (barLong < 201)
      goto LABEL_54;
  }
  else
  {
    barLong = wk->barCtrl->barLong;
    if (barLong < 201)
      goto LABEL_54;
  }
  if (!*((u32 *)sbtl + 56))
  {
    barLong = wk->barCtrl->barLong;
  }
  if (2 * barLong - 445 < 1)
  {
LABEL_54:
    goto LABEL_56;
  }
  if (*((u32 *)sbtl + 56))
  {
    devilid = pUnit->devilid;
    if (pUnit->devilid)
    {
LABEL_50:
      sdatDevilName(devilid, 0);
      goto LABEL_54;
    }
  }
  else
  {
    devilid = pUnit->devilid;
    if (pUnit->devilid)
      goto LABEL_50;
  }
  sdatDevilName(241, 0);
LABEL_56:
  sBtlDrawRedGg(wk->barCtrl->barStart + wk->barCtrl->barLong - 197, y + 14, wk->aRedGuage[v10], pUnit->now->hp, pUnit->now->maxhp);
  sBtlGetBadStatus(pUnit);
  if (wk->barCtrl->barLong < 251 || pUnit->devilid)
    return;
  f_uncnt = f_uncnt + 0.08;
  PlayerLuckStep = sBtlGetPlayerLuckStep();
  if (PlayerLuckStep > 6)
    return;
  switch (PlayerLuckStep)
  {
    case 0u:
    case 1u:
    case 2u:
    case 4u:
    case 5u:
    case 6u:
      break;
    default:
      return;
  }
}

// 0x20681c0
void sBtlMap_Init(void) {
  S_MapStatusBar *v1;

  v1 = Allocate(S_MapStatusBar);
  _ctor(v1, 0);
  g_MapStatusBar = v1;
  g_MapStatusBar->m_stkIdx = -1;
}

// 0x2068270
bool sBtlChkTutorial(void) {
  return sBtlCheckTutorialBattle();
}

// 0x20682e0
char *sBtlGetPlayerNameEx(u8 a_type) {
  if (a_type > 2u)
    return 0;
  return g_strPlayerName[a_type];
}

// 0x2068140
char *sBtlGetPlayerName(void) {
  return sdatDevilName(241, 0);
}

// 0x2068370
void sBtlSetNakamaIconOn(void) {
  g_bDrawNakamaIcon = 1;
  return;
}

// 0x2068400
void sBtlSetNakamaIconOff(void) {
  g_bDrawNakamaIcon = 0;
  return;
}

// 0x2068480
void Init(void) {
  __int128 v3;

  *(u64 *)&v3 = -1;
  *((u64 *)&v3 + 1) = -1;
  g_bDrawNakamaIcon = 1;
  g_cntTgtCur = 0;
  g_oldHuuma = 0;
  *(_OWORD *)&g_cntEscape = v3;
  *(_OWORD *)&g_cntDamageDvl = v3;
  *(u64 *)&g_cntViceMax = -1;
  *(u64 *)&g_oldVice = -1;
  *(_OWORD *)((char *)&g_devilID_sav + 2) = v3;
}

// 0x2068500
void sBtlInitDevil(void) {
  g_oldVice = -1;
  g_cntDangerDvl = -1;
  g_cntDamageDvl = -1;
  g_cntPanelDvl = -1;
  *(u64 *)&g_cntViceMax = -1;
  g_typPanelDvl = -1;
}

// 0x2068580
char *sBtlGetRaceName(s32 a_raceID) {
  return sdatRaceName(a_raceID + 34);
}

// 0x2068610
void sBtlSpriteEx(s32 a_x, s32 a_y, u8 a_alpha, s32 a_sprNo, DDS3_OT a_ot) {
  sprHandle_t *hPanelSpr3;

  hPanelSpr3 = wk->panelwk->hPanelSpr3;
  itfDrawMiscSpriteAlpha(a_x, a_y, 0, a_alpha, hPanelSpr3, a_sprNo, a_ot);
}

// 0x20686f0
void sBtlSprite(s32 a_x, s32 a_y, u8 a_alpha, s32 a_sprNo) {
  sprHandle_t *hPanelSpr3;

  hPanelSpr3 = wk->panelwk->hPanelSpr3;
  itfDrawMiscSpriteAlpha(a_x, a_y, 0, a_alpha, hPanelSpr3, a_sprNo, 109);
}

// 0x2068830
void sBtlNum(s32 a_x, s32 a_y, u32 a_rgba, u8 a_alphaRate, s32 a_num, DDS3_OT a_ot) {
  s32 Figure;
  s32 i;
  s32 FigureNum;
  s32 v16;
  sprHandle_t *hPanelSpr3;

  Figure = itfGetFigure(a_num);
  if (Figure >= 1)
  {
    for (i = Figure; i; --i)
    {
      FigureNum = itfGetFigureNum(a_num, i);
      if ((FigureNum & 0x80000000) == 0)
      {
        v16 = FigureNum;
        hPanelSpr3 = wk->panelwk->hPanelSpr3;
        itfDrawMiscSpriteAlpha(a_x, a_y, 0, a_alphaRate, hPanelSpr3, v16 + 70, a_ot);
        a_x += 9;
      }
    }
  }
}

// 0x2068a10
void sBtlDrawNum4(s32 a_x, s32 a_y, u32 a_rgba, u8 a_alphaRate, s32 a_num, u32 a_ot, f32 scale, u32 rinkaku_rgba, f32 a_size) {
  s32 v17;
  s32 v18;
  s32 v19;

  if (a_num >= 10)
    v17 = -36;
  else
    v17 = -16;
  if (a_num <= 99)
    v18 = v17;
  else
    v18 = -48;
  if (a_num <= 999)
    v19 = v18;
  else
    v19 = -60;
  Num4(wk->bsc, v19 + a_x, a_y - 12, a_rgba, a_alphaRate, a_num, a_size, 0);
}

// 0x2068af0
s32 sBtlFontCenter(s32 a_x, s32 a_y, s32 a_wMax, u32 a_color, u8 a_alphaRate, DDS3_OT a_ot, char *a_str) {
  if (a_str)
    return 0;
  else
    return -1;
}

// 0x2068b00
void sBtlNumFont(s32 a_x, s32 a_y, u32 a_color, u8 a_alphaRate, DDS3_OT a_ot, char *a_str) {
  itfDrawFont(3, a_x, a_y, 0, 0, 0, a_color, (f32)a_alphaRate / 255.0, a_ot, a_str);
}

// 0x2068bd0
void sBtlMagnetiteData(void) {
  Il2CppObject *v2;
  char *v3;
  char *v4;
  s32 data;

  data = wk->mag;
  v2 = Box(s32, &data);
  v3 = Format("{0,4:d}", v2, 0);
  v4 = Concat_54766928(0, v3, 0);
  itfDrawMiscFont(4, 28, 106, 0, 0, 0xA09DC380, 0xFFu, v4);
}

// 0x2068cf0
static void PlayerStatusDraw(SBTLUNIT_WORK *pBtlUnit) {
  bool v3;
  evtUnitHandle_t *hEveUnit;
  SBTLVISUAL_DATA *v5;
  f32 height;
  f32 v7;
  f32 v9;
  f32 *p_x;
  f32 v12;
  s32 x;
  s32 v14;
  void *bsc;
  sdfVector4_t v17;
  sdfVector4_t GagePos;

  if ((pBtlUnit->vstatus & 0x9000) != 0 || !HIBYTE(pBtlUnit->color) || (pBtlUnit->hstatus & 0x400000) != 0)
  {
    v3 = 0;
    hEveUnit = pBtlUnit->hEveUnit;
    if (!hEveUnit)
      return;
  }
  else
  {
    v3 = 1;
    hEveUnit = pBtlUnit->hEveUnit;
    if (!hEveUnit)
      return;
  }
  if (!hEveUnit->Model)
    return;
  GagePos = sBtlGetGagePos(pBtlUnit);
  v5 = Allocate(SBTLVISUAL_DATA);
  _ctor(v5, 0);
  sBtlGetCylinderData(pBtlUnit, v5);
  height = v5->height;
  v7 = height * -0.5;
  v9 = GagePos.y + v7;
  p_x = &vf00.x;
  p_x[4] = GagePos.x;
  p_x[5] = v9;
  p_x[6] = GagePos.z;
  p_x[7] = GagePos.w;
  *(u64 *)&v17.x = 0;
  *(u64 *)&v17.z = 0;
  if (!sBtlChangeWorldtoScreenUnity(&v17))
    return;
  v12 = v17.y + -16.0;
  if (v17.x == INFINITY)
    x = 0x80000000;
  else
    x = (s32)v17.x;
  if (v12 == INFINITY)
    v14 = 0x80000000;
  else
    v14 = v12;
  bsc = wk->bsc;
  if (op_Inequality(bsc, 0, 0) && v17.z >= 0.0)
  {
    DrawBafuDeBfuGagePlayer(wk->bsc, pBtlUnit, x, v14, 0, 0xFFFFFFFF, v3, 0);
  }
}

// 0x2069110
void sBtlPlayerData(void) {
  u32 status2;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v7;
  SBTLUNIT_WORK *v8;
  _BARCTRL *barCtrl;
  s32 barStart;
  sprHandle_t *m_hSpr;
  _BARCTRL *v16;
  s32 v17;
  s32 v18;
  s32 v19;
  sprHandle_t *v22;
  SBATTLE_WORK *v24;
  s32 mag;
  s16 v27;
  s32 magMax;
  s32 v29;
  s32 v30;
  sprHandle_t *v31;
  s32 v32;
  s32 v33;
  u32 v34;
  s32 Figure;
  s32 v37;
  s32 v38;
  s32 v39;
  SBATTLE_WORK *v41;
  s32 bltNumDrwCnt;
  f32 x;
  f32 y;
  s64 v47;
  f32 v48;
  f32 v51;
  f32 v52;
  sprHandle_t *v53;
  s32 v54;
  s32 v55;
  f32 v56;
  f32 v57;
  u32 v58;
  s32 Gun_Num;
  s32 v61;
  s32 v62;
  struct sdfVector4_t pos;
  sdfVector4_t ppos;

  *(u64 *)&ppos.x = 0;
  *(u64 *)&ppos.z = 0;
  if (sBtlGetMode() == 1)
    return;
  status2 = wk->status2;
  if ((status2 & 0x20000) != 0)
    return;
  status2 = wk->status2;
  if ((status2 & 0x10000) != 0)
    return;
  status2 = wk->status2;
  if ((status2 & 0x40000) != 0)
    return;
  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v7 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (!v7)
    return;
  v8 = v7;
  barCtrl = wk->barCtrl;
  barStart = barCtrl->barStart;
  m_hSpr = g_MapStatusBar->m_hSpr;
  itfDrawMiscSprite(barStart - 25, 10, 0, m_hSpr, 20, 108);
  v16 = wk->barCtrl;
  v17 = v16->barStart;
  LODWORD(v16) = v16->barLong;
  v18 = (u16)ggAnmCnt++ + 1;
  v19 = (u32)v16 + v17;
  if (v18 << 16 >= 1572864)
  {
    ggAnmCnt = 0;
  }
  v22 = g_MapStatusBar->m_hSpr;
  itfDrawMiscSprite(v19 - 100, 24, 0, v22, 0, 109);
  v24 = wk;
  mag = v24->mag;
  if (mag >= 1)
  {
    v24 = wk;
    mag = v24->mag;
    v27 = ggAnmCnt + ((ggAnmCnt >> 29) & 3);
    magMax = v24->magMax;
    if (mag >= magMax)
      v29 = v24->magMax;
    else
      v29 = mag;
    v30 = v27 >> 2;
    v31 = g_MapStatusBar->m_hSpr;
    v32 = v30 + 1;
    itfCalcSpriteWidth(v31, v32, v29, magMax);
    itfDrawMiscSprite(v19 - 97, 24, 0, g_MapStatusBar->m_hSpr, v32, 109);
  }
  v33 = wk->mag;
  Figure = itfGetFigure(v33);
  v37 = wk->mag;
  sBtlNum(v19 + 9 * (4 - Figure) - 37, 14, v34, 0xFFu, v37, 109);
  DrawAddMag(v38, v39);
  v41 = wk;
  bltNumDrwCnt = v41->bltNumDrwCnt;
  if (!bltNumDrwCnt)
    goto LABEL_89;
  v41 = wk;
  bltNumDrwCnt = v41->bltNumDrwCnt;
  v41->bltNumDrwCnt = bltNumDrwCnt - 1;
  pos = v8->pos;
  vct_A = pos;
  x = vct_A.x;
  y = vct_A.y;
  v47 = *(u64 *)&vct_A.z;
  v48 = y + -200.0;
  vct_A.x = x;
  vct_A.y = v48;
  *(u64 *)&vct_A.z = v47;
  if (sBtlChangeWorldtoScreen(&ppos))
  {
    v52 = ppos.x;
    v51 = ppos.y;
    v53 = g_MapStatusBar->m_hSpr;
    if (v52 == INFINITY)
      v54 = 0x80000000;
    else
      v54 = v52;
    if (v51 == INFINITY)
      v55 = 0x80000000;
    else
      v55 = v51;
    itfDrawMiscSprite(v54, v55, 0, v53, 14, 109);
    v57 = ppos.x;
    v56 = ppos.y;
    Gun_Num = sBtlGetGun_Num();
    if (v57 == INFINITY)
      v61 = -2147483638;
    else
      v61 = (s32)v57 + 10;
    if (v56 == INFINITY)
      v62 = -2147483643;
    else
      v62 = (s32)v56 + 5;
    sBtlNum(v61, v62, v58, 0xFFu, Gun_Num, 109);
LABEL_89:
  }
}

// 0x20697e0
static void DrawBulletUI(SBTLUNIT_WORK *wk) {
  ;
}

// 0x20697f0
void sBtlSummonDevilAshimotoReset(SBTLUNIT_WORK *wk) {
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v4;

  if (wk)
  {
    Nakama = sBtlGetNakama(0);
    v4 = sBtlGetNakama(1);
    if (v4 == wk || Nakama == wk)
    {
      if (v4 == wk || Nakama != wk)
      {
        dds3ObjectBaseOnFlag(&wk->apMarkerUnit[5], 1u);
        dds3ObjectBaseOnFlag(&wk->apMarkerUnitR[5], 1u);
        dds3ObjectBaseOnFlag(&wk->apMarkerUnit[6], 1u);
        dds3ObjectBaseOnFlag(&wk->apMarkerUnitR[6], 1u);
        dds3ObjectBaseOnFlag(&wk->apMarkerUnit[7], 1u);
        dds3ObjectBaseOnFlag(&wk->apMarkerUnitR[7], 1u);
      }
      else
      {
        dds3ObjectBaseOnFlag(&wk->apMarkerUnit[2], 1u);
        dds3ObjectBaseOnFlag(&wk->apMarkerUnitR[2], 1u);
        dds3ObjectBaseOnFlag(&wk->apMarkerUnit[3], 1u);
        dds3ObjectBaseOnFlag(&wk->apMarkerUnitR[3], 1u);
        dds3ObjectBaseOnFlag(&wk->apMarkerUnit[4], 1u);
        dds3ObjectBaseOnFlag(&wk->apMarkerUnitR[4], 1u);
      }
    }
  }
}

// 0x2069a30
void sBtlSummonDevilAshimoto(SBTLUNIT_WORK *wk, s32 idx) {
  dds3ModelHandle_t *v5;
  SBATTLE_WORK *v7;
  dds3Basic_t *v9;
  sdatParaWork_t *now;
  s32 hp;
  s64 v13;
  s32 v14;
  s64 v16;
  f32 v17;
  s64 v18;
  dds3Basic_t *apMarkerUnitR;
  dds3Basic_t *v24;
  dds3Basic_t *apMarkerUnit;
  s32 kaiwaflg;
  void *v30;
  void *v31;
  f32 x;
  f32 y;
  s64 v34;
  f32 YukaEffY;
  f32 v37;
  f32 *p_x;
  f32 v40;
  f32 v41;
  f32 z;
  f32 w;
  f32 v47;
  f32 v48;
  f32 v51;
  f32 v52;
  u16 major;
  s32 minor;
  u8 sdw_flg;
  f32 v57;
  s32 v58;
  f32 v61;
  f32 v62;
  f32 asimoto_pos_x2;
  f32 asimoto_pos_z2;
  f32 v65;
  f32 v66;
  f32 v67;
  f32 v68;
  f32 v69;
  f32 v70;
  f32 v71;
  void *Instance;
  void *v73;
  f32 asimoto_pos_z;
  f32 asimoto_pos_x;
  f32 v76;
  f32 v77;
  dds3Basic_t *v78;
  dds3Basic_t *v79;
  dds3Basic_t *pBasic;
  dds3Basic_t *pObjectBasic;
  sdfVector3_t v82;
  sdfVector3_t v83;
  sdfVector4_t v84;
  sdfVector4_t v85;
  sdfVector4_t v86;
  sdfVector4_t v87;
  sdfVector4_t v88;
  sdfVector4_t v89;
  sdfVector4_t v90;
  sdfVector4_t v91;

  pBasic = 0;
  pObjectBasic = 0;
  v78 = 0;
  v79 = 0;
  v5 = Allocate(dds3ModelHandle_t);
  _ctor(v5, 0);
  v7 = wk;
  if ((v7->status & 0x800) == 0)
    return;
  if (idx)
  {
    v7 = wk;
    dds3ObjectBaseOnFlag(&v7->apMarkerUnit[5], 1u);
    dds3ObjectBaseOnFlag(&wk->apMarkerUnitR[5], 1u);
    dds3ObjectBaseOnFlag(&wk->apMarkerUnit[6], 1u);
    dds3ObjectBaseOnFlag(&wk->apMarkerUnitR[6], 1u);
    dds3ObjectBaseOnFlag(&wk->apMarkerUnit[7], 1u);
    v9 = &wk->apMarkerUnitR[7];
  }
  else
  {
    v7 = wk;
    dds3ObjectBaseOnFlag(&v7->apMarkerUnit[2], 1u);
    dds3ObjectBaseOnFlag(&wk->apMarkerUnitR[2], 1u);
    dds3ObjectBaseOnFlag(&wk->apMarkerUnit[3], 1u);
    dds3ObjectBaseOnFlag(&wk->apMarkerUnitR[3], 1u);
    dds3ObjectBaseOnFlag(&wk->apMarkerUnit[4], 1u);
    v9 = &wk->apMarkerUnitR[4];
  }
  dds3ObjectBaseOnFlag(v9, 1u);
  now = wk->para->now;
  hp = now->hp;
  v13 = 34359738375LL * now->maxhp;
  v14 = (v13 >> 37) + ((u64)v13 >> 63);
  if (hp <= v14)
  {
    v18 = idx;
    dds3ObjectBaseOnFlag(&wk->apMarkerUnit[v18], 1u);
    dds3ObjectBaseOffFlag(&wk->apMarkerUnitR[v18], 1u);
    pObjectBasic = wk->apMarkerUnitR[v18];
    if (!IsSceanStop())
    {
      v17 = 0.2;
      goto LABEL_27;
    }
  }
  else
  {
    v16 = idx;
    dds3ObjectBaseOnFlag(&wk->apMarkerUnitR[v16], 1u);
    dds3ObjectBaseOffFlag(&wk->apMarkerUnit[v16], 1u);
    pObjectBasic = wk->apMarkerUnit[v16];
    if (!IsSceanStop())
    {
      v17 = 0.05;
LABEL_27:
      wk->nakama_asimoto_anim = wk->nakama_asimoto_anim + v17;
    }
  }
  if (wk->asimoto_mode != 1)
    goto LABEL_47;
  if (hp <= v14)
  {
    if (idx)
    {
      pBasic = wk->apMarkerUnitR[5];
      v79 = wk->apMarkerUnitR[6];
      apMarkerUnitR = wk->apMarkerUnitR;
      goto LABEL_38;
    }
    pBasic = wk->apMarkerUnitR[2];
    v79 = wk->apMarkerUnitR[3];
    apMarkerUnit = wk->apMarkerUnitR;
LABEL_45:
    v24 = apMarkerUnit[4];
    goto LABEL_46;
  }
  if (!idx)
  {
    pBasic = wk->apMarkerUnit[2];
    v79 = wk->apMarkerUnit[3];
    apMarkerUnit = wk->apMarkerUnit;
    goto LABEL_45;
  }
  pBasic = wk->apMarkerUnit[5];
  v79 = wk->apMarkerUnit[6];
  apMarkerUnitR = wk->apMarkerUnit;
LABEL_38:
  v24 = apMarkerUnitR[7];
LABEL_46:
  v78 = v24;
LABEL_47:
  if ((wk->vstatus & 0x1000) == 0)
  {
    kaiwaflg = (u8)wk->kaiwaflg;
    if (kaiwaflg == 1)
      goto LABEL_54;
    if (kaiwaflg == 2)
      goto LABEL_54;
    dds3ObjectBaseOffFlag(pObjectBasic, 1u);
    if (pBasic)
      dds3ObjectBaseOffFlag(pBasic, 1u);
    if (v79)
      dds3ObjectBaseOffFlag(v79, 1u);
    if (v78)
      dds3ObjectBaseOffFlag(v78, 1u);
    x = wk->pos.x;
    y = wk->pos.y;
    v34 = *(u64 *)&wk->pos.z;
    YukaEffY = sBtlGetYukaEffY();
    v37 = y + YukaEffY;
    vct_A.x = x;
    vct_A.y = v37;
    *(u64 *)&vct_A.z = v34;
    p_x = &vf00.x;
    v41 = p_x[4];
    v40 = p_x[5];
    z = p_x[6];
    w = p_x[7];
    v47 = vct_A.y;
    v48 = vct_A.w;
    v51 = vct_A.y;
    v52 = vct_A.w;
    if (wk->asimoto_mode == 1)
    {
      v76 = w;
      v77 = v40;
      asimoto_pos_z = wk->asimoto_pos_z;
      asimoto_pos_x = wk->asimoto_pos_x;
      v61 = vct_A.y;
      v62 = vct_A.w;
      asimoto_pos_x2 = wk->asimoto_pos_x2;
      asimoto_pos_z2 = wk->asimoto_pos_z2;
      v85.x = asimoto_pos_x2;
      v85.y = v47;
      v85.z = asimoto_pos_z2;
      v85.w = v48;
      dds3SetPosPoseSet(pBasic, v85);
      v86.x = wk->asimoto_pos_x3;
      v86.y = v51;
      v86.w = v52;
      v86.z = wk->asimoto_pos_z3;
      dds3SetPosPoseSet(v79, v86);
      v87.x = wk->asimoto_pos_x4;
      v87.y = v61;
      v87.w = v62;
      v87.z = wk->asimoto_pos_z4;
      dds3SetPosPoseSet(v78, v87);
      w = v76;
      v40 = v77;
      z = asimoto_pos_z;
      v41 = asimoto_pos_x;
LABEL_95:
      v84.x = v41;
      v84.y = v40;
      v84.z = z;
      v84.w = w;
      dds3SetPosPoseSet(pObjectBasic, v84);
      major = wk->major;
      minor = wk->minor;
      sdw_flg = sBtlGetVisualData(major, minor)->sdw_flg;
      if ((sdw_flg & 4) != 0)
      {
        *(f32 *)&v58 = 35.0;
      }
      else if ((sdw_flg & 8) != 0)
      {
        *(f32 *)&v58 = 51.000004;
      }
      else
      {
        if ((sdw_flg & 0x10) == 0)
        {
          v57 = 84.0;
          if ((sdw_flg & 0x20) == 0)
            v57 = 100.0;
LABEL_114:
          v65 = wk->nakama_asimoto_anim * 0.15915494;
          v66 = (s32)v65;
          if (v65 == INFINITY)
            v66 = -2147500000.0;
          v67 = 0.5;
          v68 = v65 - v66;
          if (v68 <= 0.5)
          {
            if (v68 < -0.5)
              v68 = v68 + 1.0;
          }
          else
          {
            v68 = v68 + -1.0;
          }
          if (v68 <= 0.25)
          {
            if (v68 >= -0.25)
            {
LABEL_124:
              v69 = v68 * 4.0;
              v70 = v57
                  + (f32)((f32)((f32)((f32)((f32)((f32)(v69 * 1.5707963) + (f32)((f32)(v69 * (f32)(v69 * v69)) * -0.6459637)) + (f32)((f32)((f32)(v69 * v69) * (f32)(v69 * (f32)(v69 * v69))) * 0.07968968)) + (f32)((f32)((f32)(v69 * v69) * (f32)((f32)(v69 * v69) * (f32)(v69 * (f32)(v69 * v69)))) * -0.0046737655)) + (f32)((f32)((f32)(v69 * v69) * (f32)((f32)(v69 * v69) * (f32)((f32)(v69 * v69) * (f32)(v69 * (f32)(v69 * v69))))) * 0.00015148419)) * 4.0);
              if (v70 >= 1.0)
                v71 = v70 * 0.03;
              else
                v71 = 0.03;
              v88.x = v71;
              v88.z = v71;
              v88.y = 1.0;
              v88.w = 1.0;
              dds3SetSclPoseSet(pObjectBasic, v88);
              if (pBasic)
              {
                v89.x = v71;
                v89.y = 1.0;
                v89.z = v71;
                v89.w = 1.0;
                dds3SetSclPoseSet(pBasic, v89);
              }
              if (v79)
              {
                v90.x = v71;
                v90.y = 1.0;
                v90.z = v71;
                v90.w = 1.0;
                dds3SetSclPoseSet(v79, v90);
              }
              if (v78)
              {
                v91.x = v71;
                v91.y = 1.0;
                v91.z = v71;
                v91.w = 1.0;
                dds3SetSclPoseSet(v78, v91);
              }
              Instance = get_Instance(0);
              if (op_Inequality(Instance, 0, 0))
              {
                v73 = get_Instance(0);
                v83.y = 1.0;
                v82.x = v41;
                v82.y = v40;
                v82.z = z;
                v83.x = v71;
                v83.z = v71;
                NakamaMarkDisp(v73, idx, v82, v83, 0);
              }
              return;
            }
            v67 = -0.5;
          }
          v68 = v67 - v68;
          goto LABEL_124;
        }
        *(f32 *)&v58 = 58.8;
      }
      v57 = *(f32 *)&v58;
      goto LABEL_114;
    }
    goto LABEL_95;
  }
LABEL_54:
  dds3ObjectBaseOnFlag(pObjectBasic, 1u);
  if (pBasic)
    dds3ObjectBaseOnFlag(pBasic, 1u);
  if (v79)
    dds3ObjectBaseOnFlag(v79, 1u);
  if (v78)
    dds3ObjectBaseOnFlag(v78, 1u);
  v30 = get_Instance(0);
  if (!op_Inequality(v30, 0, 0))
    return;
  v31 = get_Instance(0);
  NakamaMarkDispOff(v31, idx, 0);
}

// 0x206a6c0
void sBtlSummonDevilData_Sub(SBTLUNIT_WORK *wk, s32 idx) {
  sdatUnitWork_t *para;
  u32 status;
  SBTLAI_WORK *aiwk;
  s32 rsvSkl;
  SBTLSKILLP_TBL *Skilltbl;
  s32 *p_rsvSkl;
  s32 RepeatOdrSkl;
  s32 dfltOdrSkl;
  s32 use_skillid;
  s32 v15;
  _BOOL4 v18;
  s32 v24;
  SBATTLE_WORK *v25;
  s32 v27;
  sprHandle_t *m_hSpr;
  SBATTLE_WORK *v31;
  sprHandle_t *v33;
  s32 barriersklid;
  CMBSKL *cmbSkl;
  SBTLAI_WORK *v37;
  sprHandle_t *v39;
  sprHandle_t *v42;
  s32 sklId;
  s32 *v48;
  tagSBTLSKL_KARN_WORK *v49;
  s32 m_cnt;
  s32 cmndFrmMax;
  sprHandle_t *v53;
  s32 m_skillid;
  s32 *aAiGgFlsAlpha;
  char *v57;
  s32 v58;
  s32 barriercnt;
  s32 v61;
  sprHandle_t *v62;
  s32 v63;
  s32 enchantcnt;
  s32 v66;
  sprHandle_t *v67;
  s32 bulletcnt;
  s32 v71;
  sprHandle_t *v72;
  tagSBTLSKL_AURA_WORK *wkAura;
  tagSBTLSKL_AURA_WORK *v74;
  s32 auracnt;
  s32 v77;
  sprHandle_t *v78;
  s32 v79;
  tagSBTLSKL_AURA_WORK *v80;
  s32 v81;
  s32 v83;
  sprHandle_t *v84;
  s32 v85;
  tagSBTLSKL_AURA_WORK *v86;
  s32 v87;
  s32 v89;
  sprHandle_t *v90;
  s32 cmndFrm;
  s32 v93;
  sprHandle_t *v94;
  sprHandle_t *v97;
  sprHandle_t *v99;
  sprHandle_t *v101;
  long f64 v102;
  sdfVector4_t v103;

  para = wk->para;
  *(u64 *)&v103.x = 0;
  *(u64 *)&v103.z = 0;
  if (para->devilid)
  {
    if (sBtlGetMode() == 1)
      return;
    if ((wk->status2 & 0x20000) == 0)
    {
      status = wk->actwk->status;
      if (status > 0x1F || ((1 << status) & 0x80000048) == 0)
        goto LABEL_26;
      aiwk = wk->aiwk;
      rsvSkl = aiwk->rsvSkl;
      if (rsvSkl)
      {
        Skilltbl = sBtlGetSkilltbl(rsvSkl);
        p_rsvSkl = &wk->aiwk->rsvSkl;
      }
      else
      {
        RepeatOdrSkl = aiwk->RepeatOdrSkl;
        if (RepeatOdrSkl == 149)
        {
          dfltOdrSkl = aiwk->dfltOdrSkl;
          if (dfltOdrSkl == 149 || (wk->side & 1) == 0)
            goto LABEL_22;
          Skilltbl = sBtlGetSkilltbl(dfltOdrSkl);
          p_rsvSkl = &wk->aiwk->dfltOdrSkl;
        }
        else
        {
          Skilltbl = sBtlGetSkilltbl(RepeatOdrSkl);
          p_rsvSkl = &wk->aiwk->RepeatOdrSkl;
        }
      }
      if (Skilltbl && (Skilltbl->flg2 & 1) != 0)
      {
        v15 = *p_rsvSkl;
        wk->nakama_skill_name = v15;
        if (v15 != 149)
        {
LABEL_23:
          if ((wk->vstatus & 0x1000) != 0)
            goto LABEL_50;
LABEL_27:
          if (!g_bDrawNakamaIcon)
            goto LABEL_39;
          if (wk->battlemode == 3)
            goto LABEL_39;
          if (CheckLiveTarget(wk))
          {
            if (wk->aiwk->mode == 4)
            {
              v18 = (wk->color & 0xC0000000) != 0;
              goto LABEL_41;
            }
            else
            {
              v18 = 1;
LABEL_41:
              if ((sBtlGetCutFlg() & 4) == 0 && v18)
              {
                *(f32 *)&v102 = sBtlGetChestPos(wk).x;
                sub_1B335A0(&v103, 0, v102);
                sBtlNakamaCursor(wk, v103);
              }
LABEL_50:
              v24 = 27 * idx + 51;
              v25 = wk;
              v27 = v25->barCtrl->barLong + v25->barCtrl->barStart;
              m_hSpr = g_MapStatusBar->m_hSpr;
              itfDrawMiscSprite(v27 - 100, v24, 0, m_hSpr, 9, 109);
              if (wk->byctCnt)
              {
LABEL_124:
                aAiGgFlsAlpha = wk->aAiGgFlsAlpha;
                if (aAiGgFlsAlpha[idx])
                {
                  aAiGgFlsAlpha = wk->aAiGgFlsAlpha;
                  v57 = (char *)aAiGgFlsAlpha + 4 * idx;
                  v58 = *((u32 *)v57 + 8) - 10;
                  *((u32 *)v57 + 8) = v58;
                  if (v58 < 0)
                  {
                    aAiGgFlsAlpha = wk->aAiGgFlsAlpha;
                    aAiGgFlsAlpha[idx] = 0;
                  }
                }
                return;
              }
              v31 = wk;
              if (v31->rsvCmbSkl[idx])
              {
                v33 = g_MapStatusBar->m_hSpr;
                itfCalcSpriteWidth(v33, 8, 1, 1);
                itfDrawMiscSpriteAlpha(v27 - 97, v24, 0, 0x60u, g_MapStatusBar->m_hSpr, 8, 109);
                barriersklid = wk->rsvCmbSkl[idx];
                if (barriersklid == 149)
                  goto LABEL_124;
                barriersklid = wk->rsvCmbSkl[idx];
                goto LABEL_93;
              }
              v31 = wk;
              cmbSkl = v31->cmbSkl;
              if (!cmbSkl->bRun)
                goto LABEL_80;
              cmbSkl = wk->cmbSkl;
              if (cmbSkl->pNakama0 != wk)
              {
                cmbSkl = wk->cmbSkl;
                if (cmbSkl->pNakama1 != wk)
                {
LABEL_80:
                  v37 = wk->aiwk;
                  if (v37->rsvSkl)
                  {
                    if (wk->aAiGgFlsAlpha[idx])
                    {
                      v39 = g_MapStatusBar->m_hSpr;
                      itfCalcSpriteWidth(v39, 8, 1, 1);
                      itfDrawMiscSpriteAlpha(v27 - 97, v24, 0, wk->aAiGgFlsAlpha[idx], g_MapStatusBar->m_hSpr, 8, 109);
                    }
                    barriersklid = wk->aiwk->rsvSkl;
                  }
                  else
                  {
                    v49 = wk->wkKarn[0];
                    if (v49->m_skillid)
                    {
                      m_cnt = v49->m_cnt;
                      if (m_cnt)
                      {
                        m_cnt = wk->wkKarn[0]->m_cnt;
                        v37 = wk->aiwk;
                        cmndFrmMax = v37->cmndFrmMax;
                        v53 = g_MapStatusBar->m_hSpr;
                        itfCalcSpriteWidth(v53, 8, m_cnt, cmndFrmMax);
                        itfDrawMiscSpriteAlpha(v27 - 97, v24, 0, 0xFFu, g_MapStatusBar->m_hSpr, 8, 109);
                        m_skillid = wk->wkKarn[0]->m_skillid;
                        sdatSkillName(m_skillid);
                        goto LABEL_124;
                      }
                    }
                    switch (wk->drawgaugetype)
                    {
                      case 1:
                        barriercnt = wk->barriercnt;
                        if (!barriercnt || !wk->barriersklid)
                          goto LABEL_183;
                        barriercnt = wk->barriercnt;
                        v37 = wk->aiwk;
                        v61 = v37->cmndFrmMax;
                        v62 = g_MapStatusBar->m_hSpr;
                        v63 = barriercnt;
                        barriercnt = v63;
                        itfCalcSpriteWidth(v62, 8, barriercnt, v61);
                        itfDrawMiscSpriteAlpha(v27 - 97, v24, 0, 0xFFu, g_MapStatusBar->m_hSpr, 8, 109);
                        barriersklid = wk->barriersklid;
                        break;
                      case 2:
                        enchantcnt = wk->enchantcnt;
                        if (!enchantcnt)
                          goto LABEL_183;
                        enchantcnt = wk->enchantcnt;
                        v37 = wk->aiwk;
                        v66 = v37->cmndFrmMax;
                        v67 = g_MapStatusBar->m_hSpr;
                        itfCalcSpriteWidth(v67, 8, enchantcnt, v66);
                        itfDrawMiscSpriteAlpha(v27 - 97, v24, 0, 0xFFu, g_MapStatusBar->m_hSpr, 8, 109);
                        barriersklid = wk->sword_eff_skl;
                        if (barriersklid == 149)
                          goto LABEL_124;
                        barriersklid = wk->sword_eff_skl;
                        goto LABEL_93;
                      case 3:
                        bulletcnt = wk->bulletcnt;
                        if (!bulletcnt)
                          goto LABEL_183;
                        bulletcnt = wk->bulletcnt;
                        v37 = wk->aiwk;
                        v71 = v37->cmndFrmMax;
                        v72 = g_MapStatusBar->m_hSpr;
                        itfCalcSpriteWidth(v72, 8, bulletcnt, v71);
                        itfDrawMiscSpriteAlpha(v27 - 97, v24, 0, 0xFFu, g_MapStatusBar->m_hSpr, 8, 109);
                        barriersklid = wk->bulletskl;
                        break;
                      case 4:
                        wkAura = wk->wkAura;
                        v74 = wkAura[0];
                        auracnt = v74->auracnt;
                        if (auracnt && v74->auraskl)
                        {
                          auracnt = wk->wkAura[0]->auracnt;
                          v37 = wk->aiwk;
                          v77 = v37->cmndFrmMax;
                          v78 = g_MapStatusBar->m_hSpr;
                          v79 = auracnt;
                          auracnt = v79;
                          itfCalcSpriteWidth(v78, 8, auracnt, v77);
                          itfDrawMiscSpriteAlpha(v27 - 97, v24, 0, 0xFFu, g_MapStatusBar->m_hSpr, 8, 109);
                          barriersklid = wk->wkAura[0]->auraskl;
                        }
                        else
                        {
                          v80 = wkAura[1];
                          v81 = v80->auracnt;
                          if (v81 && v80->auraskl)
                          {
                            v81 = wk->wkAura[1]->auracnt;
                            v37 = wk->aiwk;
                            v83 = v37->cmndFrmMax;
                            v84 = g_MapStatusBar->m_hSpr;
                            v85 = v81;
                            v81 = v85;
                            itfCalcSpriteWidth(v84, 8, v81, v83);
                            itfDrawMiscSpriteAlpha(v27 - 97, v24, 0, 0xFFu, g_MapStatusBar->m_hSpr, 8, 109);
                            barriersklid = wk->wkAura[1]->auraskl;
                          }
                          else
                          {
                            v86 = wkAura[2];
                            v87 = v86->auracnt;
                            if (v87 && v86->auraskl)
                            {
                              v87 = wk->wkAura[2]->auracnt;
                              v37 = wk->aiwk;
                              v89 = v37->cmndFrmMax;
                              v90 = g_MapStatusBar->m_hSpr;
                              itfCalcSpriteWidth(v90, 8, v87, v89);
                              itfDrawMiscSpriteAlpha(v27 - 97, v24, 0, 0xFFu, g_MapStatusBar->m_hSpr, 8, 109);
                              barriersklid = wk->wkAura[2]->auraskl;
                            }
                            else
                            {
LABEL_183:
                              cmndFrm = v37->cmndFrm;
                              if (cmndFrm)
                              {
                                v37 = wk->aiwk;
                                cmndFrm = v37->cmndFrm;
                                v93 = v37->cmndFrmMax;
                                v94 = g_MapStatusBar->m_hSpr;
                                itfCalcSpriteWidth(v94, 8, cmndFrm, v93);
                                if (wk->aiwk->bCmndEnd)
                                {
                                  v97 = g_MapStatusBar->m_hSpr;
                                  itfDrawMiscSprite(v27 - 97, v24, 0, v97, 8, 109);
                                }
                                else
                                {
                                  v101 = g_MapStatusBar->m_hSpr;
                                  itfDrawMiscSpriteAlpha(v27 - 97, v24, 0, 0x60u, v101, 8, 109);
                                }
                                barriersklid = wk->aiwk->cmndSkl;
                              }
                              else
                              {
                                if (!v37->dfltOdrSkl)
                                  goto LABEL_124;
                                if (wk->aAiGgFlsAlpha[idx])
                                {
                                  v99 = g_MapStatusBar->m_hSpr;
                                  itfCalcSpriteWidth(v99, 8, 1, 1);
                                  itfDrawMiscSpriteAlpha(v27 - 97, v24, 0, wk->aAiGgFlsAlpha[idx], g_MapStatusBar->m_hSpr, 8, 109);
                                }
                                barriersklid = wk->aiwk->dfltOdrSkl;
                              }
                            }
                          }
                        }
                        break;
                      default:
                        goto LABEL_183;
                    }
                  }
                  if (barriersklid == 149)
                    goto LABEL_124;
LABEL_93:
                  sdatSkillName(barriersklid);
                  goto LABEL_124;
                }
              }
              v42 = g_MapStatusBar->m_hSpr;
              itfCalcSpriteWidth(v42, 8, 1, 1);
              itfDrawMiscSpriteAlpha(v27 - 99, v24, 0, wk->aAiGgFlsAlpha[idx], g_MapStatusBar->m_hSpr, 8, 109);
              sklId = wk->cmbSkl->sklId;
              if (sklId != 149)
              {
                sdatSkillName(sklId);
                goto LABEL_107;
LABEL_109:
                v48 = wk->aAiGgFlsAlpha;
                if (v48[idx] <= 63)
                {
                  v48 = wk->aAiGgFlsAlpha;
                  v48[idx] = 255;
                }
                goto LABEL_124;
              }
LABEL_107:
              goto LABEL_109;
            }
          }
          else
          {
LABEL_39:
            v18 = 0;
            goto LABEL_41;
          }
          goto LABEL_41;
        }
LABEL_26:
        wk->nakama_skill_name = 0;
        if ((wk->vstatus & 0x1000) != 0)
          goto LABEL_50;
        goto LABEL_27;
      }
LABEL_22:
      use_skillid = wk->actwk->use_skillid;
      wk->nakama_skill_name = use_skillid;
      if (use_skillid != 149)
        goto LABEL_23;
      goto LABEL_26;
    }
  }
}

// 0x206bab0
void sBtlSummonDevilData(void) {
  u64 *v1;
  dds3Basic_t *apMarkerUnit;
  dds3Basic_t *v5;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v7;
  SBTLUNIT_WORK *v9;
  u64 *v10;
  SBTLUNIT_WORK *v12;
  SBTLUNIT_WORK *v13;

  v1 = NewSpecific(SBTLUNIT_WORK, 2u);
  if (wk)
  {
    apMarkerUnit = wk->apMarkerUnit;
    if (apMarkerUnit[0])
    {
      apMarkerUnit = wk->apMarkerUnit;
      dds3ObjectBaseOnFlag(apMarkerUnit, 1u);
      dds3ObjectBaseOnFlag(wk->apMarkerUnitR, 1u);
    }
    v5 = wk->apMarkerUnit;
    if (v5[1])
    {
      v5 = wk->apMarkerUnit;
      dds3ObjectBaseOnFlag(&v5[1], 1u);
      dds3ObjectBaseOnFlag(&wk->apMarkerUnitR[1], 1u);
    }
  }
  Nakama = sBtlGetNakama(0);
  v7 = Nakama;
  v1[5] = v9;
  v10 = v1 + 5;
  v12 = *(v10 - 1);
  if (v12)
  {
    sBtlSummonDevilData_Sub(v12, 0);
  }
  v13 = *v10;
  if (v13)
  {
    sBtlSummonDevilData_Sub(v13, 1);
  }
}

// 0x206bd20
void sBtlEnemyData(void) {
  s32 *v2;
  s32 *v4;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLACTION_WORK *actwk;
  u32 status;
  bool v15;
  u32 v16;
  bool v17;
  s32 use_skillid;
  f32 y;
  f32 cap_skillpos_x;
  f32 z;
  s64 v22;
  s32 v23;
  s32 v24;
  s32 v25;
  void *bsc;
  s32 v32;
  s32 v33;
  s32 v34;
  s32 v35;
  s32 x;
  s32 xa;
  sdfVector4_t ppos;

  *(u64 *)&ppos.x = 0;
  *(u64 *)&ppos.z = 0;
  if ((sBtlGetCutFlg() & 1) != 0)
    return;
  v2 = NewSpecific(s32, 3u);
  v4 = v2;
  if ((s32)*(u64 *)((char *)v2 + 24) >= 1)
    sub_188E3B0(&v2[0], 0, 4 * (u32)*(u64 *)((char *)v2 + 24));
  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 2) == 0)
    {
      DrawHpGageHD(pUnit);
      continue;
    }
    if ((pUnit->vstatus & 0x1000) == 0)
    {
      Skilltbl = sBtlGetSkilltbl(pUnit->actwk->use_skillid);
      if ((pUnit->status & 0x100000) == 0 && (Skilltbl->flg & 0x40000000) == 0 && (Skilltbl->flg2 & 0x40000) == 0)
      {
        if ((wk->status2 & 0x1000) == 0)
        {
          actwk = pUnit->actwk;
          status = actwk->status;
          v15 = status > 0x1F;
          v16 = (1 << status) & 0x80000048;
          v17 = v15 || v16 == 0;
          if (v17 || (use_skillid = actwk->use_skillid) == 0 || use_skillid == 149 || !pUnit->hEveUnit)
          {
            sBtlDrawSkillNameOff(pUnit);
            *(u64 *)&pUnit->cap_skillpos_y = 0;
            *(_OWORD *)&pUnit->cap_skillname_x = 0u;
          }
          else
          {
            sBtlGetChestPos(pUnit);
            cap_skillpos_x = pUnit->pos.x;
            y = pUnit->pos.y;
            z = pUnit->pos.z;
            if (use_skillid == 433 && pUnit->cap_skillpos_x != 0.0 && pUnit->cap_skillpos_y != 0.0 && pUnit->cap_skillpos_z != 0.0)
            {
              z = pUnit->cap_skillpos_z;
              y = pUnit->cap_skillpos_y;
              cap_skillpos_x = pUnit->cap_skillpos_x;
            }
            if (sBtlChangeWorldtoScreenUnity3(cap_skillpos_x, y, z, &ppos))
            {
              if (ppos.x == INFINITY)
                v22 = 0x80000000LL;
              else
                v22 = (u32)(s32)ppos.x;
              if ((f32)(ppos.y + 16.0) == INFINITY)
                v23 = 0x80000000;
              else
                v23 = (f32)(ppos.y + 16.0);
              if (ppos.z == INFINITY)
                v24 = 0x80000000;
              else
                v24 = ppos.z;
              if (use_skillid == 433 && pUnit->cap_skillpos_x == 0.0 && pUnit->cap_skillpos_y == 0.0)
              {
                v32 = v24;
                v34 = v23;
                x = v22;
                sBtlGetGagePos(pUnit);
                *(u64 *)&pUnit->cap_skillpos_x = *(u64 *)&pUnit->pos.x;
                v23 = v34;
                LODWORD(v22) = x;
                v24 = v32;
                pUnit->cap_skillpos_z = pUnit->pos.z;
              }
              v35 = v23;
              xa = v22;
              v33 = v24;
              v24 = v33;
              v23 = v35;
              LODWORD(v22) = xa;
              sBtlDrawSkillName(pUnit, v22, v23, v24, 0xB080A080, use_skillid);
            }
          }
        }
      }
    }
    v25 = CalcEatkNotice(pUnit);
    if (v25 != -1)
      ++v4[v25];
    DrawHpGageHD(pUnit);
    if (evtBitCheck(2100))
      continue;
    DrawEnemyName(pUnit);
  }
  bsc = wk->bsc;
  if (op_Inequality(bsc, 0, 0))
  {
    EatkNoticeDispSet(wk->bsc, v4, 0);
  }
}

// 0x2069000
sdfVector4_t sBtlGetGagePos(SBTLUNIT_WORK *pBtlUnit) {
  f32 *p_x;
  sdfVector4_t result;

  if (sdfModelGetMarkPos(pBtlUnit->hEveUnit->Model->modelRoot, 1))
  {
    goto LABEL_5;
  }
  else
  {
    sdfModelGetMarkPos(pBtlUnit->hEveUnit->Model->modelRoot, 0);
LABEL_5:
    goto LABEL_6;
  }
LABEL_6:
  p_x = &vf00.x;
  result.x = p_x[4];
  result.y = p_x[5];
  result.z = p_x[6];
  result.w = p_x[7];
  return result;
}

// 0x206b670
sdfVector4_t sBtlGetChestPos(SBTLUNIT_WORK *pBtlUnit) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  sdfVector4_t result;

  if (sdfModelGetMarkPos(pBtlUnit->hEveUnit->Model->modelRoot, 1))
  {
    goto LABEL_5;
  }
  else
  {
    sdfModelGetMarkPos(pBtlUnit->hEveUnit->Model->modelRoot, 0);
LABEL_5:
    goto LABEL_6;
  }
LABEL_6:
  x = vct_A.x;
  y = vct_A.y;
  z = vct_A.z;
  w = vct_A.w;
  switch (pBtlUnit->para->devilid)
  {
    case 0x167:
    case 0x16D:
    case 0x171:
    case 0x175:
    case 0x181:
    case 0x1A7:
    case 0x1AD:
    case 0x1B1:
    case 0x1B5:
    case 0x1C1:
      y = y + 25.0;
      break;
    default:
      break;
  }
  result.x = x;
  result.z = z;
  result.y = y;
  result.w = w;
  vct_A.x = x;
  vct_A.y = y;
  vct_A.z = z;
  vct_A.w = w;
  return result;
}

// 0x206c400
static void DrawHpGageHD(SBTLUNIT_WORK *pBtlUnit) {
  bool v4;
  bool v5;
  s32 devilid;
  evtUnitHandle_t *hEveUnit;
  s32 use_skillid;
  f32 z;
  SBTLVISUAL_DATA *v10;
  int32x2_t v11;
  s32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v20;
  f32 *p_x;
  f32 v23;
  s32 v24;
  s32 v25;
  void *bsc;
  s32 side;
  void *v31;
  s32 encountno;
  void *v35;
  void *transform;
  SBTLUNIT_WORK *v38;
  void *v39;
  s32 v40;
  s32 v41;
  void *hpGageObj;
  SBATTLE_WORK *v44;
  s32 v45;
  f32 y;
  f32 x;
  sdfVector4_t ppos;
  sdfVector3_t position;
  sdfVector4_t GagePos;

  v4 = (pBtlUnit->hstatus & 0x400000) == 0 && HIBYTE(pBtlUnit->color) != 0;
  v5 = (pBtlUnit->vstatus & 0x1000) == 0 && v4;
  devilid = (u16)pBtlUnit->para->devilid;
  if (devilid == 259 || devilid == 323 || devilid == 311)
    v5 = 0;
  hEveUnit = pBtlUnit->hEveUnit;
  if (!hEveUnit || !hEveUnit->Model)
    return;
  use_skillid = pBtlUnit->actwk->use_skillid;
  GagePos = sBtlGetGagePos(pBtlUnit);
  x = GagePos.x;
  z = GagePos.z;
  y = GagePos.y;
  v10 = Allocate(SBTLVISUAL_DATA);
  _ctor(v10, 0);
  sBtlGetCylinderData(pBtlUnit, v10);
  if (use_skillid == 433)
  {
    if (*(u64 *)&pBtlUnit->cap_skillname_x)
    {
      y = pBtlUnit->cap_skillname_y;
      x = (f32)pBtlUnit->cap_skillname_x;
      z = pBtlUnit->cap_skillname_z;
    }
    else
    {
      v11.n64_u64[0] = vdup_n_s32(0x7F800000u).n64_u64[0];
      if (GagePos.z == INFINITY)
        v12 = 0x80000000;
      else
        v12 = GagePos.z;
      pBtlUnit->cap_skillname_z = v12;
      *(int8x8_t *)&pBtlUnit->cap_skillname_x = vbsl_s8(vceq_f32(*(float32x2_t *)&GagePos.x, v11), (int8x8_t)0x8000000080000000LL, vcvt_s32_f32(*(float32x2_t *)&GagePos.x));
    }
  }
  v13 = pBtlUnit->hpPosition.y;
  v14 = pBtlUnit->hpPosition.x;
  if (pBtlUnit->para->devilid == 184)
    v15 = 0.25;
  else
    v15 = -0.5;
  v16 = v13 * v15;
  v17 = v14 * 0.5;
  v18 = y + v16;
  v20 = x + v17;
  p_x = &vf00.x;
  p_x[4] = v20;
  p_x[5] = v18;
  p_x[6] = z;
  p_x[7] = GagePos.w;
  *(u64 *)&ppos.x = 0;
  *(u64 *)&ppos.z = 0;
  if (!sBtlChangeWorldtoScreenUnity(&ppos))
    return;
  v23 = ppos.y + -16.0;
  if (ppos.x == INFINITY)
    v24 = 0x80000000;
  else
    v24 = ppos.x;
  if (v23 == INFINITY)
    v25 = 0x80000000;
  else
    v25 = v23;
  bsc = wk->bsc;
  if (op_Inequality(bsc, 0, 0) && ppos.z >= 0.0)
  {
    side = pBtlUnit->side;
    if ((side & 2) == 0)
    {
      if ((side & 0x80) != 0)
      {
        DrawCallMark(wk->bsc, pBtlUnit, v24, v25, 0, 0);
      }
      else
      {
        DrawHpGageNakama(wk->bsc, pBtlUnit, v24, v25, 0, 0xFFFFFFFF, v5, 0);
      }
      return;
    }
    encountno = wk->encountno;
    if (encountno == 46)
      goto LABEL_119;
    encountno = wk->encountno;
    if (encountno == 55 || (pBtlUnit->para->devilid & 0xFFFE) == 0x138)
    {
LABEL_119:
      DrawHpGageBossEnemy_double(wk->bsc, pBtlUnit, v24, v25, 0, 0xFFFFFFFF, v5, 0, 0);
      return;
    }
    v39 = wk->bsc;
    v38 = pBtlUnit;
    v40 = v24;
    v41 = v25;
LABEL_112:
    DrawHpGageEnemy(v39, v38, v40, v41, 0, 0xFFFFFFFF, v5, 0, 0);
    return;
  }
  v31 = wk->bsc;
  if (!op_Inequality(v31, 0, 0))
    goto LABEL_91;
  if (ppos.z >= 0.0 || (pBtlUnit->status & 0x80000000) != 0)
  {
LABEL_91:
    if ((pBtlUnit->side & 2) != 0)
    {
      hpGageObj = pBtlUnit->hpGageObj;
      if (op_Inequality(hpGageObj, 0, 0) && (pBtlUnit->status & 0x80000000) != 0)
      {
        v44 = wk;
        v45 = v44->encountno;
        if (v45 == 46)
          goto LABEL_120;
        v44 = wk;
        v45 = v44->encountno;
        if (v45 == 55 || (pBtlUnit->para->devilid & 0xFFFE) == 0x138)
        {
LABEL_120:
          DrawHpGageBossEnemy_double(wk->bsc, pBtlUnit, v24, v25, 0, 0xFFFFFFFF, v5, 1, 0);
        }
        else
        {
          v44 = wk;
          DrawHpGageEnemy(v44->bsc, pBtlUnit, v24, v25, 0, 0xFFFFFFFF, v5, 1, 0);
        }
      }
    }
    return;
  }
  if ((pBtlUnit->side & 2) != 0)
  {
    v35 = pBtlUnit->hpGageObj;
    if (op_Inequality(v35, 0, 0))
    {
      transform = get_transform(pBtlUnit->hpGageObj, 0);
      position = get_position(transform, 0);
      if ((position.y < 600.0 || position.y > -600.0 || position.x < 1000.0 || position.x > -1000.0) && (position.y != ppos.y || position.x != ppos.x))
      {
        v38 = pBtlUnit;
        v39 = wk->bsc;
        v40 = 10 * v24;
        v41 = 10 * v25;
        goto LABEL_112;
      }
    }
  }
}

// 0x206cb80
static void DrawEnemyName(SBTLUNIT_WORK *pBtlUnit) {
  bool v4;
  evtUnitHandle_t *hEveUnit;
  bool v6;
  void *bsc;
  void *v11;
  s32 x;
  s32 y;
  sdfVector4_t v14;
  sdfVector4_t GagePos;

  v4 = (pBtlUnit->hstatus & 0x400000) == 0 && HIBYTE(pBtlUnit->color) != 0;
  hEveUnit = pBtlUnit->hEveUnit;
  v6 = (pBtlUnit->vstatus & 0x1000) == 0 && v4;
  if (hEveUnit && hEveUnit->Model)
  {
    GagePos = sBtlGetGagePos(pBtlUnit);
    vct_A = GagePos;
    goto LABEL_20;
  }
LABEL_20:
  *(u64 *)&v14.x = 0;
  *(u64 *)&v14.z = 0;
  if (!sBtlChangeWorldtoScreenUnity(&v14))
    return;
  bsc = wk->bsc;
  if (!op_Inequality(bsc, 0, 0))
    return;
  if (v14.z >= 0.0 && (pBtlUnit->side & 2) != 0)
  {
    v11 = wk->bsc;
    if (v14.x == INFINITY)
      x = 0x80000000;
    else
      x = v14.x;
    if (v14.y == INFINITY)
      y = 0x80000000;
    else
      y = v14.y;
    DrawNameEnemy(v11, pBtlUnit, x, y, 0, v6, 0);
  }
}

// 0x206c270
static s32 CalcEatkNotice(SBTLUNIT_WORK *pBtlUnit) {
  s32 result;
  SBTLACTION_WORK *actwk;
  s32 width;
  s32 height;
  f32 v7;
  f32 v8;
  unsigned __int128 v9;

  if (!pBtlUnit)
    return -1;
  if ((pBtlUnit->side & 2) == 0)
    return -1;
  actwk = pBtlUnit->actwk;
  result = -1;
  if (actwk->status == 6 && !pBtlUnit->actaiwk->targetID && actwk->use_skillid && HIBYTE(pBtlUnit->color) && (pBtlUnit->vstatus & 0x1000) == 0)
  {
    sBtlGetGagePos(pBtlUnit);
    v9 = 0u;
    width = get_width(0);
    height = get_height(0);
    v7 = width;
    v8 = height;
    sBtlChangeWorldtoScreenUnity(&v9);
    if (*(f32 *)&v9 >= 0.0)
    {
      result = -1;
      if (*(f32 *)&v9 <= v7)
        return result;
    }
    else if (*((f32 *)&v9 + 1) <= v8)
    {
      result = 0;
      if (*(f32 *)&v9 <= v7)
        return result;
    }
    else
    {
      result = 2;
      if (*(f32 *)&v9 <= v7)
        return result;
    }
    if (*((f32 *)&v9 + 1) <= v8)
      return 1;
    else
      return 2;
  }
  return result;
}

// 0x206ce20
void sBtlDrawBossHP(SBTLUNIT_WORK *wk) {
  ;
}

// 0x206ce30
void sBtlAnalyzeBackEx(u8 a_type, s32 a_x, s32 a_y, u8 a_alphaRate, sprHandle_t *a_hSpr) {
  u32 v7;
  s32 v11;

  LOBYTE(v7) = a_alphaRate;
  if (a_hSpr)
  {
    switch (a_type)
    {
      case 0u:
        v7 = (u8)v7;
        itfDrawMiscSpriteAlpha(a_x, a_y, 0, (u8)v7, a_hSpr, 22, 110);
        itfDrawMiscSpriteAlpha(a_x - 283, a_y, 0, (u8)v7, a_hSpr, 21, 110);
        v11 = 159;
        goto LABEL_21;
      case 1u:
        v7 = (u8)v7;
        itfDrawMiscSpriteAlpha(a_x, a_y, 0, (u8)v7, a_hSpr, 19, 110);
        itfDrawMiscSpriteAlpha(a_x - 283, a_y, 0, (u8)v7, a_hSpr, 20, 110);
        v11 = 233;
        goto LABEL_21;
      case 2u:
        v7 = (u8)v7;
        itfDrawMiscSpriteAlpha(a_x, a_y, 0, (u8)v7, a_hSpr, 16, 110);
        itfDrawMiscSpriteAlpha(a_x - 283, a_y, 0, (u8)v7, a_hSpr, 17, 110);
        v11 = 152;
        goto LABEL_21;
      case 3u:
        v7 = (u8)v7;
        itfDrawMiscSpriteAlpha(a_x, a_y, 0, (u8)v7, a_hSpr, 111, 110);
        itfDrawMiscSpriteAlpha(a_x - 283, a_y, 0, (u8)v7, a_hSpr, 110, 110);
        v11 = 133;
        goto LABEL_21;
      case 4u:
        v7 = (u8)v7;
        itfDrawMiscSpriteAlpha(a_x, a_y, 0, (u8)v7, a_hSpr, 108, 110);
        itfDrawMiscSpriteAlpha(a_x - 283, a_y, 0, (u8)v7, a_hSpr, 109, 110);
        v11 = 257;
LABEL_21:
        itfDrawMiscSpriteAlpha(a_x, v11 + a_y, 0, v7, a_hSpr, 18, 110);
        break;
      default:
        return;
    }
  }
}

// 0x206d120
void sBtlAnalyzeBack(u8 a_type, u8 a_alphaRate) {
  sprHandle_t *hPanelSpr3;

  hPanelSpr3 = wk->panelwk->hPanelSpr3;
  sBtlAnalyzeBackEx(a_type, 273, 88, a_alphaRate, hPanelSpr3);
}

// 0x206d1d0
void sBtlAnalyzeLvEx(sdatUnitWork_t *unit, s32 a_x, s32 a_y, u8 a_alphaRate, bool a_bSecret, sprHandle_t *a_hSpr) {
  Il2CppObject *v16;
  char *v17;
  char *a_str;
  s32 v19;
  s32 v20;
  s32 devilid;
  s8 data[4];

  itfDrawMiscSpriteAlpha(a_x, a_y, 0, a_alphaRate, a_hSpr, 33, 110);
  if (!a_bSecret)
  {
    data[0] = unit->level;
    v16 = Box(sbyte, data);
    v17 = Format("{0,2:d}", v16, 0);
    a_str = Concat_54766928(0, v17, 0);
    v19 = a_x + 21;
    v20 = a_y - 2;
    itfDrawFont(3, v19, v20, 0, 0, 0, 0xA09DC380, (f32)a_alphaRate / 255.0, 110, a_str);
    if ((unit->flag & 2) == 0)
      goto LABEL_19;
LABEL_8:
    goto LABEL_9;
  }
  Concat_54766928(0, "??", 0);
  if ((unit->flag & 2) == 0)
    goto LABEL_19;
  goto LABEL_8;
LABEL_19:
  devilid = unit->devilid;
  sdatDevilName(devilid, 0);
LABEL_9:
  sBtlGetBadStatus(unit);
}

// 0x206d4d0
void sBtlAnalyzeLv(sdatUnitWork_t *unit, u8 a_alphaRate, bool a_bSecret) {
  sprHandle_t *hPanelSpr3;

  hPanelSpr3 = wk->panelwk->hPanelSpr3;
  sBtlAnalyzeLvEx(unit, 19, 121, a_alphaRate, a_bSecret, hPanelSpr3);
}

// 0x206d590
void sBtlAnalyzeHpEx(sdatUnitWork_t *unit, s32 a_x, s32 a_y, u8 a_alphaRate, bool a_bSecret, sprHandle_t *a_hSpr) {
  sprHandle_t *m_hSpr;

  if (!a_bSecret)
  {
    m_hSpr = g_MapStatusBar->m_hSpr;
    itfDrawMiscSpriteAlpha(67, 159, 0, a_alphaRate, m_hSpr, 9, 110);
    itfCalcSpriteWidth(g_MapStatusBar->m_hSpr, 7, unit->now->hp, unit->now->maxhp);
    itfDrawMiscSpriteAlpha(70, 159, 0, a_alphaRate, g_MapStatusBar->m_hSpr, 7, 110);
  }
  itfDrawMiscSpriteAlpha(a_x, a_y, 0, a_alphaRate, a_hSpr, 7, 110);
  itfDrawMiscSpriteAlpha(a_x + 55, a_y, 0, a_alphaRate, a_hSpr, 35, 110);
}

// 0x206d7b0
void sBtlAnalyzeHp(sdatUnitWork_t *unit, u8 a_alphaRate, bool a_bSecret) {
  sprHandle_t *hPanelSpr3;

  hPanelSpr3 = wk->panelwk->hPanelSpr3;
  sBtlAnalyzeHpEx(unit, 67, 144, a_alphaRate, a_bSecret, hPanelSpr3);
}

// 0x206d870
void sBtlAnalyzeLoyalty(sdatUnitWork_t *unit, s32 a_x, s32 a_y, u8 a_alphaRate, sprHandle_t *a_hSpr) {
  s32 v11;

  if ((unit->flag & 2) == 0)
  {
    v11 = a_y + 81;
    itfDrawMiscSpriteAlpha(a_x - 149, a_y + 89, 0, a_alphaRate, a_hSpr, 103, 110);
    itfDrawMiscSpriteAlpha(a_x - 91, a_y + 89, 0, a_alphaRate, a_hSpr, 104, 110);
    itfCalcSpriteWidth(a_hSpr, 105, unit->chuusei, 100);
    itfDrawMiscSpriteAlpha(a_x - 147, a_y + 91, 0, a_alphaRate, a_hSpr, 105, 110);
    if (unit->chuusei >= 100)
    {
      itfDrawMiscSpriteAlpha(a_x - 123, v11, 0, a_alphaRate, a_hSpr, 114, 110);
    }
    itfDrawMiscSpriteAlpha(a_x - 197, v11, 0, a_alphaRate, a_hSpr, 102, 110);
  }
}

// 0x206da30
void sBtlAnalyzeSkill(s32 a_type, s32 a_x, s32 a_y, u32 a_rgba, u8 a_alphaRate, char *a_str) {
  void *v11;
  s32 v12;
  s32 v13;

  v11 = NewSpecific(s32, 4u);
  InitializeArray_55364416(v11, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__AD355071B6A280261B9CFCF1C44B2B3BC9FA214B036598DF60FF7D4089725011, 0);
  if ((u32)a_type <= 3)
  {
    v12 = a_y + 1;
    v13 = *((u32 *)&v11[2].klass + (u32)a_type);
    itfIconDrawSprite(a_x + 4, v12, 0, a_alphaRate, v13, 110);
  }
}

// 0x206db60
void sBtlSkillData(s32 a_skillid, s32 a_x, s32 a_y, u32 a_rgba, u8 a_alphaRate, char *a_str) {
  s32 SkillIconSpriteNo;
  s32 v14;
  s32 v15;

  SkillIconSpriteNo = cmpGetSkillIconSpriteNo(a_skillid);
  if (SkillIconSpriteNo < 0)
  {
    return;
  }
  v14 = SkillIconSpriteNo;
  v15 = a_y + 1;
  itfIconDrawSprite(a_x + 4, v15, 0, a_alphaRate, v14, 110);
}

// 0x206dc90
void sBtlAnalyzeAisyo(s32 a_type, s32 a_devilID, u8 a_alphaRate) {
  s32 v7;
  sprHandle_t *hPanelSpr3;
  sprHandle_t *v12;
  s32 v14;
  sprHandle_t *v15;

  if (a_devilID < 1)
  {
    datGetSwordAisyo();
    v7 = 173;
  }
  else
  {
    if (a_type)
      v7 = 254;
    else
      v7 = 278;
    sBtlGetDevilData(a_devilID, -1);
  }
  hPanelSpr3 = wk->panelwk->hPanelSpr3;
  itfDrawMiscSpriteAlpha(17, v7, 0, a_alphaRate, hPanelSpr3, 25, 110);
  v12 = wk->panelwk->hPanelSpr3;
  itfDrawMiscSpriteAlpha(0, v7 + 18, 0, a_alphaRate, v12, 80, 110);
  v14 = v7 + 41;
  v15 = wk->panelwk->hPanelSpr3;
  itfDrawMiscSpriteAlpha(44, v14, 0, a_alphaRate, v15, 81, 110);
}

// 0x206df90
void sBtlAnalyzeTalkSkill(s32 a_devilId, u8 a_alphaRate) {
  s32 talkskill;

  talkskill = datGetDevilFormat(a_devilId)->talkskill;
  sBtlGetWajutsuNameFont(talkskill);
  return;
}

// 0x206e080
void sBtlAnalyzeMeisi(s32 a_devilId, u8 a_alphaRate, s32 a_y_ofs) {

}

// 0x206e0c0
void sBtlAnalyzePlayer(sdatUnitWork_t *unit, u8 a_alphaRate) {
  u8 v6;
  sprHandle_t *hPanelSpr3;
  sprHandle_t *v11;
  sprHandle_t *v14;
  u32 v17;
  sprHandle_t *v18;
  sprHandle_t *v20;
  sprHandle_t *v22;
  sprHandle_t *v24;
  s64 v25;
  s32 v26;
  s32 v27;
  s32 v28;
  u32 v29;
  char *v30;
  s32 devilid;
  sprHandle_t *v35;
  u32 v36;
  sprHandle_t *v38;
  sprHandle_t *v40;
  sprHandle_t *v42;
  sprHandle_t *v44;
  sprHandle_t *v46;
  sprHandle_t *v48;
  s64 v49;
  u8 v50;
  s32 v52;
  s32 v53;
  s32 v54;
  u32 v55;
  char *v56;
  s32 v58;

  if ((unit->flag & 2) != 0)
    v6 = 2;
  else
    v6 = 4;
  hPanelSpr3 = wk->panelwk->hPanelSpr3;
  sBtlAnalyzeBackEx(v6, 273, 88, a_alphaRate, hPanelSpr3);
  v11 = wk->panelwk->hPanelSpr3;
  sBtlAnalyzeLvEx(unit, 19, 121, a_alphaRate, 0, v11);
  v14 = wk->panelwk->hPanelSpr3;
  sBtlAnalyzeHpEx(unit, 67, 144, a_alphaRate, 0, v14);
  if ((unit->flag & 6) == 2)
  {
    v17 = a_alphaRate;
    v18 = wk->panelwk->hPanelSpr3;
    itfDrawMiscSpriteAlpha(21, 173, 0, v17, v18, 31, 110);
    v20 = wk->panelwk->hPanelSpr3;
    itfDrawMiscSpriteAlpha(275, 173, 0, v17, v20, 32, 110);
    v22 = wk->panelwk->hPanelSpr3;
    itfDrawMiscSpriteAlpha(21, 198, 0, v17, v22, 31, 110);
    v24 = wk->panelwk->hPanelSpr3;
    v25 = 32;
    itfDrawMiscSpriteAlpha(275, 198, 0, v17, v24, 32, 110);
    v26 = 0;
    do
    {
      v27 = *(u32 *)((char *)&unit->aOmoideSkill->obj.klass + v25);
      if ((v27 & 0x80000000) == 0 && v27 && v27 != 149 && v27 != 288)
      {
        if (v26 >= 0)
          v28 = v26;
        else
          v28 = v26 + 1;
        sdatSkillName(v27);
        sBtlSkillData(v27, 130 * (v26 - (v28 & 0xFFFFFFFE)) + 21, 25 * (v28 >> 1) + 172, v29, a_alphaRate, v30);
        if (++v26 > 3)
          break;
      }
      v25 += 4;
    }
    while (v25 != 64);
    return;
  }
  devilid = unit->devilid;
  sBtlAnalyzeAisyo(0, devilid, a_alphaRate);
  if ((unit->flag & 4) != 0)
  {
    v35 = wk->panelwk->hPanelSpr3;
    sBtlAnalyzeLoyalty(unit, 273, 88, a_alphaRate, v35);
    v36 = a_alphaRate;
    v38 = wk->panelwk->hPanelSpr3;
    itfDrawMiscSpriteAlpha(21, 195, 0, v36, v38, 31, 110);
    v40 = wk->panelwk->hPanelSpr3;
    itfDrawMiscSpriteAlpha(275, 195, 0, v36, v40, 32, 110);
    v42 = wk->panelwk->hPanelSpr3;
    itfDrawMiscSpriteAlpha(21, 220, 0, v36, v42, 31, 110);
    v44 = wk->panelwk->hPanelSpr3;
    itfDrawMiscSpriteAlpha(275, 220, 0, v36, v44, 32, 110);
    v46 = wk->panelwk->hPanelSpr3;
    itfDrawMiscSpriteAlpha(21, 245, 0, v36, v46, 31, 110);
    v48 = wk->panelwk->hPanelSpr3;
    v49 = 32;
    itfDrawMiscSpriteAlpha(275, 245, 0, v36, v48, 32, 110);
    v52 = 0;
    do
    {
      v53 = *(u32 *)((char *)&unit->battleskill->obj.klass + v49);
      if ((v53 & 0x80000000) == 0 && v53 && v53 != 149 && v53 != 288)
      {
        if (v52 >= 0)
          v54 = v52;
        else
          v54 = v52 + 1;
        sdatSkillName(v53);
        sBtlSkillData(v53, 130 * (v52 - (v54 & 0xFFFFFFFE)) + 21, 25 * (v54 >> 1) + 194, v55, a_alphaRate, v56);
        if (++v52 > 5)
          break;
      }
      v49 += 4;
    }
    while (v49 != 64);
    v58 = unit->devilid;
    sBtlAnalyzeTalkSkill(v58, v50);
    return;
  }
}

// 0x206eb70
void sBtlAnalyzeBoss(SBTLUNIT_WORK *wk, u8 a_alphaRate) {
  sprHandle_t *hPanelSpr3;
  sdatUnitWork_t *para;
  sprHandle_t *v12;
  sdatUnitWork_t *v14;
  sprHandle_t *v16;
  u32 v17;
  sprHandle_t *v19;
  sprHandle_t *v21;
  sprHandle_t *v23;
  sprHandle_t *v25;
  sprHandle_t *v27;
  sprHandle_t *v29;
  s32 devilid;

  hPanelSpr3 = wk->panelwk->hPanelSpr3;
  sBtlAnalyzeBackEx(1u, 273, 88, a_alphaRate, hPanelSpr3);
  para = wk->para;
  v12 = wk->panelwk->hPanelSpr3;
  sBtlAnalyzeLvEx(para, 19, 121, a_alphaRate, 1, v12);
  v14 = wk->para;
  v16 = wk->panelwk->hPanelSpr3;
  sBtlAnalyzeHpEx(v14, 67, 144, a_alphaRate, 1, v16);
  v17 = a_alphaRate;
  v19 = wk->panelwk->hPanelSpr3;
  itfDrawMiscSpriteAlpha(21, 173, 0, v17, v19, 31, 110);
  v21 = wk->panelwk->hPanelSpr3;
  itfDrawMiscSpriteAlpha(275, 173, 0, v17, v21, 32, 110);
  v23 = wk->panelwk->hPanelSpr3;
  itfDrawMiscSpriteAlpha(21, 198, 0, v17, v23, 31, 110);
  v25 = wk->panelwk->hPanelSpr3;
  itfDrawMiscSpriteAlpha(275, 198, 0, v17, v25, 32, 110);
  v27 = wk->panelwk->hPanelSpr3;
  itfDrawMiscSpriteAlpha(21, 223, 0, v17, v27, 31, 110);
  v29 = wk->panelwk->hPanelSpr3;
  itfDrawMiscSpriteAlpha(275, 223, 0, v17, v29, 32, 110);
  devilid = wk->para->devilid;
  sBtlAnalyzeAisyo(2, devilid, a_alphaRate);
}

// 0x206f150
void sBtlAnalyzeEnemy(SBTLUNIT_WORK *wk, u8 a_alphaRate) {
  void *Instance;
  void *v6;

  Instance = get_Instance(0);
  if (DrawAnalizeEnemyInfo(Instance, wk, 0))
  {
    goto LABEL_7;
  }
  v6 = get_Instance(0);
  GuideSet(v6, "BTL001", 0, 90, 0);
LABEL_7:
  if (wk->modeSq)
    return;
  ButtonLineHelpDispSet(0);
}

// 0x206b830
void sBtlNakamaCursor(SBTLUNIT_WORK *wk, const sdfVector4_t *pos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  s32 nakama_skill_name;
  f32 v14;
  s32 v15;
  s32 v16;
  s32 v17;
  sdfVector4_t v18;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  *(u64 *)&v18.x = 0;
  *(u64 *)&v18.z = 0;
  if (!wk->panelwk)
    return;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  if (!sBtlChangeWorldtoScreenUnity(&v18))
    return;
  if ((wk->status2 & 0x1000) != 0)
    goto LABEL_34;
  goto LABEL_9001;
  if ((wk->status2 & 0x1000) != 0)
  {
LABEL_34:
    sBtlDrawSkillNameOff(wk);
    return;
  }
LABEL_9001:
  nakama_skill_name = wk->nakama_skill_name;
  if (!nakama_skill_name)
    goto LABEL_34;
  v14 = v18.y + 16.0;
  if (v18.x == INFINITY)
    v15 = 0x80000000;
  else
    v15 = v18.x;
  if (v14 == INFINITY)
    v16 = 0x80000000;
  else
    v16 = v14;
  if (v18.z == INFINITY)
    v17 = 0x80000000;
  else
    v17 = v18.z;
  sBtlDrawSkillName(wk, v15, v16, v17, 0x80A0A0A0, nakama_skill_name);
}

// 0x206f2b0
void sBtlTargetNoCursor(const sdfVector4_t *pos, char *str, s32 _num) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *v12;
  f32 *p_x;
  f32 v17;
  f32 v18;
  f32 v20;
  f32 v21;
  s32 v22;
  s32 v23;
  sdfVector4_t ppos;
  sdfVector4_t v27;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  *(u64 *)&ppos.x = 0;
  *(u64 *)&ppos.z = 0;
  if (!wk->panelwk)
    return;
  goto LABEL_10;
LABEL_16:
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  goto LABEL_17;
LABEL_10:
  v12 = &vf00.x;
  v12[4] = x;
  v12[5] = y;
  v12[6] = z;
  v12[7] = w;
  goto LABEL_16;
LABEL_17:
  if (!sBtlChangeWorldtoScreenUnity4(&ppos))
  {
    TargetNoCursorOff(wk->bsc, num, 0);
    return;
  }
  v17 = ppos.x;
  if (ppos.x > -16.0 && v17 < (f32)(get_width(0) + 16))
  {
    v18 = ppos.y;
    if (ppos.y > 0.0 && v18 < (f32)get_height(0))
    {
      *(int8x8_t *)&v27.x = vbsl_s8(vceq_f32(*(float32x2_t *)&ppos.x, vdup_n_s32(0x7F800000u)), (int8x8_t)0xCF000000CF000000LL, vcvt_f32_s32(vcvt_s32_f32(*(float32x2_t *)&ppos.x)));
      v27.z = 0.0;
      v27.w = 0.0;
      TargetNoCursorDrawUnity(wk->bsc, v27, num, 0);
      if (str)
      {
        v21 = ppos.x;
        v20 = ppos.y;
        if (v21 == INFINITY)
          v22 = 0x80000000;
        else
          v22 = v21;
        if (v20 == INFINITY)
          v23 = 0x80000000;
        else
          v23 = v20;
        itfDrawFont(0, v22, v23, 0x100000, 0, 0, 0xA0A0A0A0, 1.0, 109, str);
      }
    }
  }
}

// 0x206f610
void sBtlTargetCursor(const sdfVector4_t *pos, char *str) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  float32x2_t *v12;
  float32x2_t v14;
  f32 v15;
  f32 v24;
  f32 v25;
  f32 v26;
  float32x2_t v35;
  f32 v36;
  float32x2_t v37;
  int32x2_t v38;
  float32x2_t v40;
  f32 v42;
  f32 v48;
  f32 v49;
  f32 v55;
  f32 v56;
  f32 v62;
  f32 v63;
  f32 *v66;
  f32 v69;
  f32 v70;
  f32 v72;
  f32 v73;
  s32 v74;
  s32 v75;
  s32 v79;
  sdfVector4_t ppos;
  sdfVector4_t v86;
  sdfVector4_t v87;
  sdfVector4_t v88;
  sdfVector4_t v89;
  sdfVector4_t v90;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  *(u64 *)&ppos.x = 0;
  *(u64 *)&ppos.z = 0;
  if (!wk->panelwk)
    return;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v14.n64_u64[0] = v12[2].n64_u64[0];
  v15 = v12[3].n64_f32[0];
  if (gTargetPosHokanFastFlag)
    goto LABEL_15;
  __asm { FMOV            V3.2S, #10.0 }
  v35.n64_u64[0] = vadd_f32(*(float32x2_t *)&gTargetPosHokanBuff0.x, vdiv_f32(vsub_f32(v14, *(float32x2_t *)&gTargetPosHokanBuff0.x), _D3)).n64_u64[0];
  v36 = gTargetPosHokanBuff0.z + (f32)((f32)(v15 - gTargetPosHokanBuff0.z) / 10.0);
  v37.n64_u64[0] = vsub_f32(v35, v14).n64_u64[0];
  *(float32x2_t *)&gTargetPosHokanBuff0.x = v35;
  gTargetPosHokanBuff0.z = v36;
  v38.n64_u64[0] = vmul_f32(v37, v37).n64_u64[0];
  v38.n64_f32[0] = sqrtf(vaddv_f32(v38) + (f32)((f32)(v36 - v15) * (f32)(v36 - v15)));
  __asm { FMOV            V5.2S, #4.0 }
  v40.n64_u64[0] = vmul_n_f32(vdiv_f32(v37, vdup_lane_s32(v38, 0)), v38.n64_f32[0] / 5.0).n64_u64[0];
  __asm { FMOV            V3.2S, #3.0 }
  v42 = (f32)((f32)(v36 - v15) / v38.n64_f32[0]) * (f32)(v38.n64_f32[0] / 5.0);
  *(float32x2_t *)&gTargetPosHokanBuff1.x = vadd_f32(v14, v40);
  *(float32x2_t *)&gTargetPosHokanBuff2.x = vadd_f32(v14, vadd_f32(v40, v40));
  gTargetPosHokanBuff1.z = v15 + v42;
  gTargetPosHokanBuff3.z = v15 + (f32)(v42 * 3.0);
  *(float32x2_t *)&gTargetPosHokanBuff3.x = vadd_f32(v14, vmul_f32(v40, _D3));
  *(float32x2_t *)&gTargetPosHokanBuff4.x = vadd_f32(v14, vmul_f32(v40, _D5));
  gTargetPosHokanBuff2.z = v15 + (f32)(v42 + v42);
  gTargetPosHokanBuff4.z = v15 + (f32)(v42 * 4.0);
  goto LABEL_19;
LABEL_15:
  gTargetPosHokanFastFlag = 0;
  *(float32x2_t *)&gTargetPosHokanBuff0.x = v14;
  gTargetPosHokanBuff0.z = v15;
  *(float32x2_t *)&gTargetPosHokanBuff1.x = v14;
  gTargetPosHokanBuff1.z = v15;
  *(float32x2_t *)&gTargetPosHokanBuff2.x = v14;
  gTargetPosHokanBuff2.z = v15;
  *(float32x2_t *)&gTargetPosHokanBuff3.x = v14;
  gTargetPosHokanBuff3.z = v15;
  *(float32x2_t *)&gTargetPosHokanBuff4.x = v14;
  gTargetPosHokanBuff4.z = v15;
LABEL_19:
  vct_A = gTargetPosHokanBuff1;
  v24 = -16.0;
  if (sBtlChangeWorldtoScreenUnity(&ppos))
  {
    v25 = ppos.x;
    if (ppos.x > v24 && v25 < (f32)(get_width(0) + 16))
    {
      v26 = ppos.y;
      if (ppos.y > 0.0 && v26 < (f32)get_height(0))
      {
        *(int8x8_t *)&v86.x = vbsl_s8(vceq_f32(*(float32x2_t *)&ppos.x, vdup_n_s32(0x7F800000u)), (int8x8_t)0xCF000000CF000000LL, vcvt_f32_s32(vcvt_s32_f32(*(float32x2_t *)&ppos.x)));
        v86.z = 0.0;
        v86.w = 0.0;
        TargetCursorDrawUnity(wk->bsc, v86, 0);
      }
    }
    goto LABEL_53;
  }
  TargetCursorOff(wk->bsc, 0);
LABEL_53:
  vct_A = gTargetPosHokanBuff2;
  if (!!sBtlChangeWorldtoScreenUnity(&ppos))
  {
    v48 = ppos.x;
    if (ppos.x > v24 && v48 < (f32)(get_width(0) + 16))
    {
      v49 = ppos.y;
      if (ppos.y > 0.0 && v49 < (f32)get_height(0))
      {
        *(int8x8_t *)&v87.x = vbsl_s8(vceq_f32(*(float32x2_t *)&ppos.x, vdup_n_s32(0x7F800000u)), (int8x8_t)0xCF000000CF000000LL, vcvt_f32_s32(vcvt_s32_f32(*(float32x2_t *)&ppos.x)));
        v87.z = 0.0;
        v87.w = 0.0;
        TargetCursorDrawUnity(wk->bsc, v87, 0);
      }
    }
  }
  vct_A = gTargetPosHokanBuff3;
  if (!!sBtlChangeWorldtoScreenUnity(&ppos))
  {
    v55 = ppos.x;
    if (ppos.x > v24 && v55 < (f32)(get_width(0) + 16))
    {
      v56 = ppos.y;
      if (ppos.y > 0.0 && v56 < (f32)get_height(0))
      {
        *(int8x8_t *)&v88.x = vbsl_s8(vceq_f32(*(float32x2_t *)&ppos.x, vdup_n_s32(0x7F800000u)), (int8x8_t)0xCF000000CF000000LL, vcvt_f32_s32(vcvt_s32_f32(*(float32x2_t *)&ppos.x)));
        v88.z = 0.0;
        v88.w = 0.0;
        TargetCursorDrawUnity(wk->bsc, v88, 0);
      }
    }
  }
  vct_A = gTargetPosHokanBuff4;
  if (!!sBtlChangeWorldtoScreenUnity(&ppos))
  {
    v62 = ppos.x;
    if (ppos.x > v24 && v62 < (f32)(get_width(0) + 16))
    {
      v63 = ppos.y;
      if (ppos.y > 0.0 && v63 < (f32)get_height(0))
      {
        *(int8x8_t *)&v89.x = vbsl_s8(vceq_f32(*(float32x2_t *)&ppos.x, vdup_n_s32(0x7F800000u)), (int8x8_t)0xCF000000CF000000LL, vcvt_f32_s32(vcvt_s32_f32(*(float32x2_t *)&ppos.x)));
        v89.z = 0.0;
        v89.w = 0.0;
        TargetCursorDrawUnity(wk->bsc, v89, 0);
      }
    }
  }
  v66 = &vf00.x;
  v66[4] = x;
  v66[5] = y;
  v66[6] = z;
  v66[7] = w;
  if (!!sBtlChangeWorldtoScreenUnity(&ppos))
  {
    v69 = ppos.x;
    if (ppos.x <= v24 || v69 >= (f32)(get_width(0) + 16) || (v70 = ppos.y, ppos.y <= 0.0) || v70 >= (f32)get_height(0))
    {
      TargetCursorOff(wk->bsc, 0);
    }
    else
    {
      *(int8x8_t *)&v90.x = vbsl_s8(vceq_f32(*(float32x2_t *)&ppos.x, vdup_n_s32(0x7F800000u)), (int8x8_t)0xCF000000CF000000LL, vcvt_f32_s32(vcvt_s32_f32(*(float32x2_t *)&ppos.x)));
      v90.z = 0.0;
      v90.w = 0.0;
      TargetCursorDrawUnity(wk->bsc, v90, 0);
      if (str)
      {
        v73 = ppos.x;
        v72 = ppos.y;
        if (v73 == INFINITY)
          v74 = 0x80000000;
        else
          v74 = v73;
        if (v72 == INFINITY)
          v75 = 0x80000000;
        else
          v75 = v72;
        itfDrawFont(0, v74, v75, 0x100000, 0, 0, 0xA0A0A0A0, 1.0, 109, str);
      }
    }
  }
  v79 = g_cntTgtCur + 1;
  _NF = g_cntTgtCur - 59 < 0;
  g_cntTgtCur = v79;
  if (_NF != __OFSUB__(v79, 60))
    return;
  g_cntTgtCur = 0;
}

// 0x2070210
void sBtlResetTargetCursor(void) {
  g_cntTgtCur = 0;
  gTargetPosHokanFastFlag = 1;
}

// 0x2070280
bool sBtlSelectTargetCursorSub(SBTLUNIT_WORK *wk, bool bDrawName) {
  SBTLSKILLP_TBL *Skilltbl;
  SBTLUNIT_WORK *PChara;
  SBTLUNIT_WORK *v7;
  s32 devilid;
  s64 v10;
  SBTLUNIT_LISTWORK *v12;
  SBTLUNIT_WORK *v13;
  s32 v15;
  s64 v16;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  sdatUnitWork_t *para;
  sdfVector4_t v21;
  s32 v22;
  char *v23;
  SBTLITEM_TBL *item_keep;
  s32 v28;
  SBTLUNIT_WORK *Nakama;
  s64 v33;
  s64 v35;
  char *v37;
  long f64 v39;
  struct sdfVector4_t v40;
  struct sdfVector4_t pos;
  sdfVector4_t HelperPos;
  sdfVector4_t vct_A_local;
  sdfVector4_t v44;

  vct_A_local = (sdfVector4_t)0;
  Skilltbl = sBtlGetSkilltbl(0);
  *(u64 *)&HelperPos.x = 0;
  *(u64 *)&HelperPos.z = 0;
  PChara = sBtlGetPChara();
  if (wk)
  {
    v7 = PChara;
    if (!CheckLiveTarget(wk))
      return 1;
    if ((wk->status & 0x800) == 0)
    {
      devilid = (u16)wk->para->devilid;
      if (devilid == 258)
      {
        v16 = 0;
        while (1)
        {
          UnitMng = wk->UnitMng;
          if (v16 >= UnitMng->number)
            break;
          UnitMng = wk->UnitMng;
          pUnit = UnitMng->pUnitL[v16]->pUnit;
          if (pUnit && pUnit->para->devilid == 314 && (pUnit->status & 0x800) != 0)
          {
            GetUnitHelperPos(pUnit, &HelperPos);
            HelperPos.x = v7->pos.x;
LABEL_50:
            vct_A_local = HelperPos;
            break;
          }
          ++v16;
        }
      }
      else
      {
        if (devilid != 260)
        {
          *(f32 *)&v39 = sBtlGetChestPos(wk).x;
          sub_1B335A0(&vct_A_local, 0, v39);
          if (bDrawName)
          {
LABEL_52:
            para = wk->para;
            v21 = vct_A_local;
            v22 = para->devilid;
            if (para->devilid)
            {
              v23 = sdatDevilName(v22, 0);
              goto LABEL_69;
            }
LABEL_60:
            v23 = sdatDevilName(241, 0);
LABEL_69:
            sBtlTargetCursor(v21, v23);
            item_keep = wk->item_keep;
            if (item_keep)
            {
              item_keep = wk->item_keep;
              Skilltbl = sBtlGetSkilltbl(item_keep->sklid);
            }
            if ((Skilltbl->area & 4) == 0)
              return 1;
            v28 = 0;
            while (1)
            {
              if (v28 == 2)
              {
                Nakama = sBtlGetPChara();
                if (!Nakama)
                  goto LABEL_79;
              }
              else
              {
                Nakama = sBtlGetNakama(v28);
                if (!Nakama)
                  goto LABEL_79;
              }
              if (CheckLiveTarget(Nakama))
              {
                if ((Nakama->status & 0x800) == 0)
                {
                  sBtlGetChestPos(Nakama);
                  goto LABEL_91;
LABEL_92:
                  goto LABEL_93;
LABEL_91:
                  goto LABEL_92;
LABEL_93:
                  LOWORD(Nakama) = Nakama->para->devilid;
                  vct_A_local = vct_A;
                  v33 = *(u64 *)&vct_A_local.x;
LABEL_101:
                  v35 = *(u64 *)&vct_A_local.z;
                  v37 = sdatDevilName((s16)Nakama, 0);
                  *(u64 *)&v44.x = v33;
                  *(u64 *)&v44.z = v35;
                  sBtlTargetNoCursor(v44, v37, v28);
                  goto LABEL_79;
                }
                pos = Nakama->pos;
                goto LABEL_96;
LABEL_97:
                vct_A = pos;
                goto LABEL_98;
LABEL_96:
                goto LABEL_97;
LABEL_98:
                LODWORD(Nakama) = (u16)Nakama->para->devilid;
                vct_A_local = vct_A;
                v33 = *(u64 *)&vct_A_local.x;
                if ((u32)Nakama == 315)
                {
                  LOWORD(Nakama) = 315;
                  vct_A_local.x = vct_A_local.x + 32.0;
                  vct_A_local.y = vct_A_local.y + -600.0;
                  v33 = *(u64 *)&vct_A_local.x;
                }
                goto LABEL_101;
              }
LABEL_79:
              if (++v28 == 3)
                return 1;
            }
            goto LABEL_60;
          }
LABEL_66:
          v21 = vct_A_local;
          v23 = 0;
          goto LABEL_69;
        }
        v10 = 0;
        while (1)
        {
          v12 = wk->UnitMng;
          if (v10 >= v12->number)
            break;
          v12 = wk->UnitMng;
          v13 = v12->pUnitL[v10]->pUnit;
          if (v13 && v13->para->devilid == 315 && (v13->status & 0x800) != 0)
          {
            GetUnitHelperPos(v13, &HelperPos);
            goto LABEL_50;
          }
          ++v10;
        }
      }
LABEL_51:
      if (bDrawName)
        goto LABEL_52;
      goto LABEL_66;
    }
    v40 = wk->pos;
    vct_A = v40;
    v15 = (u16)wk->para->devilid;
    vct_A_local = vct_A;
    if (v15 == 315)
    {
      *(float32x2_t *)&vct_A_local.x = vadd_f32(*(float32x2_t *)&vct_A_local.x, (float32x2_t)0xC416000042000000LL);
      if (bDrawName)
        goto LABEL_52;
      goto LABEL_66;
    }
    goto LABEL_51;
  }
  return 1;
}

// 0x2070a80
bool sBtlSelectTargetCursor(bool bDrawName) {
  SBTLUNIT_LISTWORK *tgtList;
  SBTLUNIT_LISTWORK *v7;
  s32 tgt_csr;
  SBTLUNIT_WORK *v10;

  tgtList = wk->tgtList;
  if (!tgtList)
    return 0;
  if (wk->tgtList->count < 1)
    return 0;
  if ((wk->status & 0x80000) == 0)
    return 0;
  v7 = wk->tgtList;
  tgt_csr = wk->tgt_csr;
  v10 = sBtlSearchUnit_ID(v7, tgt_csr);
  sBtlSelectTargetCursorSub(v10, bDrawName);
  return 1;
}

// 0x2070c30
void sBtlHelpEx(s32 a_type, s32 a_num, sprHandle_t *a_hSpr, u8 a_alphaRate) {
  char *MenuHelpStr;
  _BOOL4 v8;
  void *Instance;
  char *v10;
  char *v11;
  char *v12;
  char *NoneItemText;
  bool v14;
  u8 v15;
  char **v16;
  char *v17;
  char *v18;

  switch (a_type)
  {
    case 3:
      MenuHelpStr = sBtlGetMenuHelpStr(a_num);
      v8 = 0;
      if (MenuHelpStr)
        goto LABEL_13;
      break;
    case 2:
      MenuHelpStr = sdatItemHelp(a_num, 1);
      v8 = a_num == 9;
      if (MenuHelpStr)
        goto LABEL_13;
      break;
    case 1:
      MenuHelpStr = sdatSkillHelp(a_num, 1);
      v8 = 0;
      if (!MenuHelpStr)
        return;
LABEL_13:
      Instance = get_Instance(0);
      v10 = HelpDraw(Instance, MenuHelpStr, 0, 0);
      v11 = 0;
      if (v8)
      {
        v12 = sdatItemHelp(a_num, 0);
        NoneItemText = cmpGetNoneItemText();
        v14 = op_Inequality(v12, NoneItemText, 0);
        v11 = 0;
        if (v14)
        {
          v15 = cmpCheckSeikatu();
          v16 = &"CMP_USE_MSG_L0027";
          if (v15)
            v16 = &"CMP_USE_MSG_L0026";
          v17 = *v16;
          v11 = ButtonLineHelpAddTextSet(v17, 1, 2, 0);
        }
      }
      v18 = Concat_54766928(v10, v11, 0);
      ButtonLineHelpTextSetNoConvert(v18, 0xA09DC380);
      return;
    default:
      return;
  }
}

// 0x2070ed0
void sBtlHelp(s32 a_type, s32 a_num, u8 a_alphaRate) {
  s32 v9;
  s32 v10;

  v9 = a_type;
  v10 = a_num;
  sBtlHelpEx(v9, v10, a_alphaRate, (u8)method);
}

// 0x2070fa0
void sBtlHelpCantUseEx(s32 a_type, s32 a_num, sprHandle_t *a_hSpr, u8 a_alphaRate) {
  char *MenuHelpStr;
  void *Instance;

  switch (a_type)
  {
    case 1:
      MenuHelpStr = sdatSkillHelp(a_num, 0);
      if (MenuHelpStr)
        goto LABEL_22;
      return;
    case 2:
      MenuHelpStr = sdatItemHelp(a_num, 0);
      if (MenuHelpStr)
        goto LABEL_22;
      return;
    case 3:
      MenuHelpStr = sBtlGetMenuHelpStr(a_num);
      if (MenuHelpStr)
        goto LABEL_22;
      return;
    case 7:
      if (a_num == 2)
      {
        MenuHelpStr = "SBTLMENUHELP_L0023";
        if (!"SBTLMENUHELP_L0023")
          return;
      }
      else if (a_num == 1)
      {
        MenuHelpStr = "SBTLMENUHELP_L0022";
        if (!"SBTLMENUHELP_L0022")
          return;
      }
      else
      {
        if (a_num)
          return;
        MenuHelpStr = "SBTLMENUHELP_L0021";
        if (!"SBTLMENUHELP_L0021")
          return;
      }
LABEL_22:
      Instance = get_Instance(0);
      HelpDraw(Instance, MenuHelpStr, 1, 0);
      return;
    default:
      return;
  }
}

// 0x2071170
void sBtlHelpCantUse(s32 a_type, s32 a_num, u8 a_alphaRate) {
  s32 v9;
  s32 v10;

  v9 = a_type;
  v10 = a_num;
  sBtlHelpCantUseEx(v9, v10, a_alphaRate, (u8)method);
}

// 0x2071240
void sBtlEscapeGauge(s32 a_cnt, s32 a_max) {
  u64 *v3;
  void *v4;
  void *v5;
  void *v6;
  void *v7;
  void *v8;
  void *v9;
  void *v10;
  void *v11;
  void *v12;
  void *v13;
  void *v14;
  void *v15;
  u32 v21;
  s32 v22;
  s32 v25;
  u32 v26;
  u32 v27;
  s32 v30;
  u32 v31;
  u32 v32;
  s32 v35;
  u32 v36;
  u32 v37;
  s32 v40;
  bool v41;

  v3 = NewSpecific(sbyte__, 0xCu);
  v4 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v4, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__B5B0FB499DD9FBEFFC258B75F7D4767C5A08BF57A24414A6EC638B1557FA8BB0, 0);
  v3[4] = v4;
  v5 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v5, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__681297ED2D602B162BC46BAE798C156146EFB1F8E280DE0311C2FCCD866DB445, 0);
  v3[5] = v5;
  v6 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v6, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__B4D4B5C1BAE19B57C94EFB751C34A3ADFB61BFC5B711B4F3AFE9823E767A21F1, 0);
  v3[6] = v6;
  v7 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v7, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__399E32E45861A505BA8D3C85FFD58F507965A89D7443393A413E43093F203674, 0);
  v3[7] = v7;
  v8 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v8, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__96A67E63669939E37391850133933CCE98C5643D6E678D8A0C04D6A88CDB2244, 0);
  v3[8] = v8;
  v9 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v9, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__E3FBC81C92F15386176D10407F25CD203AB0846A82A4FDCFE4D0672C83CF7608, 0);
  v3[9] = v9;
  v10 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v10, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__EE950F4F9D32B7629A6B8A63B0DDFF59E61E9E5878F780BD37AA88F9CB34D92E, 0);
  v3[10] = v10;
  v11 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v11, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__0DAC81DD90FE345F6724C37A7CFB56A9E60AAD984CF2FD158AB709D4977BAD30, 0);
  v3[11] = v11;
  v12 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v12, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__6334D9E0F749E9E3AADDE1BE745D5BD9E2053EEDA95C34B497B27C3462F4C3D4, 0);
  v3[12] = v12;
  v13 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v13, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__FDDBD16D3E31DF40001E22FB08C631C2BDC2CE7E8398042C593878A67FFD7F95, 0);
  v3[13] = v13;
  v14 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v14, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__DFE8A9AFB7A4D817D4F1FCBFA2E0DB038E9E780A9EF47E947FB6D79412720177, 0);
  v3[14] = v14;
  v15 = NewSpecific(sbyte, 3u);
  InitializeArray_55364416(v15, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__875475CF00F2E76D5992CF893E4F01B5CE41F63F4FA04859D5E50022DF4082D2, 0);
  v3[15] = v15;
  if (a_max >= 1)
  {
    if ((g_cntEscape & 0x80000000) == 0)
    {
      goto LABEL_9;
      if (g_cntEscape > 11)
      {
LABEL_10:
        if (g_cntEscape > 17)
        {
          if (v21)
          {
            if (g_cntEscape >= 48)
              goto LABEL_14;
          }
          else
          {
            if (g_cntEscape >= 48)
            {
LABEL_14:
              if (g_cntEscape > 59)
              {
                LOBYTE(v22) = 0;
                goto LABEL_36;
              }
              v22 = (((g_cntEscape << 7) - 6144) / -12) ^ 0xFFFFFF80;
LABEL_36:
              sBtlSprite(15, 403, v22, 99);
              v25 = g_cntEscape;
              if (v25 < 12)
                goto LABEL_43;
              if (v25 > 23)
              {
                if (v26)
                {
                  if (v25 >= 48)
                    goto LABEL_41;
                }
                else
                {
                  v25 = g_cntEscape;
                  if (v25 >= 48)
                  {
LABEL_41:
                    if (v25 > 59)
                      goto LABEL_43;
                    goto LABEL_9001;
                    if (v25 > 59)
                    {
LABEL_43:
                      LOBYTE(v27) = 0;
                      goto LABEL_45;
                    }
LABEL_9001:
                    v25 = g_cntEscape;
                    v27 = (((v25 << 7) - 6144) / -12) ^ 0xFFFFFF80;
LABEL_45:
                    sBtlSprite(64, 416, v27, 100);
                    v30 = g_cntEscape;
                    if (v30 < 24)
                      goto LABEL_50;
                    if (v30 > 47)
                    {
                      if (v31)
                      {
                        if (v30 > 59)
                          goto LABEL_50;
                      }
                      else
                      {
                        v30 = g_cntEscape;
                        if (v30 > 59)
                        {
LABEL_50:
                          LOBYTE(v32) = 0;
                          goto LABEL_52;
                        }
                      }
                      v30 = g_cntEscape;
                      v32 = (((v30 << 7) - 6144) / -12) ^ 0xFFFFFF80;
LABEL_52:
                      sBtlSprite(72, 416, v32, 100);
                      v35 = g_cntEscape;
                      if (v35 < 36)
                        goto LABEL_57;
                      if (v35 > 47)
                      {
                        if (v36)
                        {
                          if (v35 > 59)
                            goto LABEL_57;
                        }
                        else
                        {
                          v35 = g_cntEscape;
                          if (v35 > 59)
                          {
LABEL_57:
                            LOBYTE(v37) = 0;
                            goto LABEL_59;
                          }
                        }
                        v35 = g_cntEscape;
                        v37 = (((v35 << 7) - 6144) / -12) ^ 0xFFFFFF80;
LABEL_59:
                        sBtlSprite(80, 416, v37, 100);
                        v40 = g_cntEscape + 1;
                        v41 = g_cntEscape - 59 < 0;
                        g_cntEscape = v40;
                        if (v41 != __OFSUB__(v40, 60))
                          return;
                        g_cntEscape = 0;
                        return;
                      }
                      if (!v36)
                      {
                        v35 = g_cntEscape;
                      }
                      v37 = ((v35 << 7) - 4608) / 12;
                      goto LABEL_59;
                    }
                    if (!v31)
                    {
                      v30 = g_cntEscape;
                    }
                    v32 = ((v30 << 7) - 3072) / 24;
                    goto LABEL_52;
                  }
                }
                LOBYTE(v27) = 0x80;
                goto LABEL_45;
              }
              if (!v26)
              {
                v25 = g_cntEscape;
              }
              v27 = ((v25 << 7) - 1536) / 12;
              goto LABEL_45;
            }
          }
          LOBYTE(v22) = 0x80;
          goto LABEL_36;
        }
        v22 = (52 * g_cntEscape - 624) / -6 - 76;
        goto LABEL_36;
      }
LABEL_22:
      v22 = 180 * g_cntEscape / 12;
      goto LABEL_36;
    }
    g_cntEscape = 0;
LABEL_9:
    if (g_cntEscape > 11)
      goto LABEL_10;
    goto LABEL_22;
  }
}

// 0x2071c20
void sBtlResetEscapeGauge(void) {
  g_cntEscape = -1;
  return;
}

// 0x2071cb0
void sBtlDamagePanelE(const sdfVector4_t *pos, s32 dmg, u32 rgba, u32 rgba2, f32 a_size, s32 dispmode, bool weak_k) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  f32 v18;
  f32 v19;
  s64 v20;
  f32 v21;
  s64 v26;
  s32 v27;
  s32 v28;
  s32 v29;
  s32 v30;
  s32 v32;
  void *bsc;
  s32 v34;
  sdfVector4_t v35;
  s32 a_num;

  a_num = dmg;
  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  *(u64 *)&v35.x = 0;
  *(u64 *)&v35.z = 0;
  if ((sBtlGetCutFlg() & 1) != 0)
    return;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v18 = vct_A.x;
  v19 = vct_A.y;
  v20 = *(u64 *)&vct_A.z;
  v21 = v19 + -40.0;
  vct_A.x = v18;
  vct_A.y = v21;
  *(u64 *)&vct_A.z = v20;
  if (!sBtlChangeWorldtoScreenUnity(&v35))
    return;
  if (v35.z < 0.0)
    return;
  ToString_55996800((s32)&a_num, "d3", 0);
  v26 = *(u64 *)&v35.x;
  v27 = a_num;
  if (*(f32 *)&v26 == INFINITY)
    v28 = 0x80000000;
  else
    v28 = *(f32 *)&v26;
  v29 = *((f32 *)&v26 + 1);
  if (v27 <= 999)
  {
    if (v27 > 99)
    {
      v30 = -48;
      v32 = v29 - 12;
      goto LABEL_42;
    }
    else
    {
      if (v27 >= 10)
        v30 = -36;
      else
        v30 = -16;
      v32 = v29 - 12;
      goto LABEL_42;
    }
    goto LABEL_41;
  }
  v30 = -60;
  v32 = v29 - 12;
LABEL_41:
LABEL_42:
  bsc = wk->bsc;
  if (*((f32 *)&v26 + 1) == INFINITY)
    v34 = 2147483636;
  else
    v34 = v32;
  Num4(bsc, v30 + v28, v34, rgba, 0xFFu, v27, a_size, 0);
}

// 0x2072060
void sBtlDamagePanelN(const sdfVector4_t *pos, s32 dmg, u32 rgba, u32 rgba2, s32 minor, s32 uniq_code, f32 a_size) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v20;
  SBTLUNIT_WORK *v21;
  f32 *p_x;
  f32 v26;
  f32 v27;
  s64 v28;
  f32 v29;
  s64 v33;
  s32 v34;
  s32 v35;
  s32 v36;
  s32 v38;
  void *bsc;
  s32 v41;
  sdfVector4_t v42;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  *(u64 *)&v42.x = 0;
  *(u64 *)&v42.z = 0;
  if ((sBtlGetCutFlg() & 1) != 0)
    return;
  Nakama = sBtlGetNakama(0);
  if (!Nakama || (v20 = Nakama, Nakama->minor != minor) || Nakama->para->uniq_code != (s64)uniq_code)
  {
    v21 = sBtlGetNakama(1);
    if (!v21 || (v20 = v21, v21->minor != minor) || v21->para->uniq_code != (s64)uniq_code)
    {
      p_x = &vf00.x;
      p_x[4] = x;
      p_x[5] = y;
      p_x[6] = z;
      p_x[7] = w;
LABEL_21:
      goto LABEL_22;
    }
  }
  sBtlGetChestPos(v20);
  goto LABEL_21;
LABEL_22:
  v26 = vct_A.x;
  v27 = vct_A.y;
  v28 = *(u64 *)&vct_A.z;
  v29 = v27 + -120.0;
  vct_A.x = v26;
  vct_A.y = v29;
  *(u64 *)&vct_A.z = v28;
  if (!sBtlChangeWorldtoScreenUnity(&v42))
    return;
  if (v42.z < 0.0)
    return;
  v33 = *(u64 *)&v42.x;
  if (*(f32 *)&v33 == INFINITY)
    v34 = 0x80000000;
  else
    v34 = *(f32 *)&v33;
  v35 = *((f32 *)&v33 + 1);
  if (dmg <= 999)
  {
    if (dmg > 99)
    {
      v36 = -48;
      v38 = v35 - 36;
      goto LABEL_54;
    }
    else
    {
      if (dmg >= 10)
        v36 = -36;
      else
        v36 = -16;
      v38 = v35 - 36;
      goto LABEL_54;
    }
    goto LABEL_53;
  }
  v36 = -60;
  v38 = v35 - 36;
LABEL_53:
LABEL_54:
  bsc = wk->bsc;
  if (*((f32 *)&v33 + 1) == INFINITY)
    v41 = 2147483612;
  else
    v41 = v38;
  Num4(bsc, v36 + v34, v41, rgba, 0xFFu, dmg, a_size, 0);
}

// 0x20724a0
void sBtlDamagePanelR(const sdfVector4_t *pos, s32 dmg, u32 rgba, u32 rgba2, f32 a_size) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v17;
  SBTLUNIT_WORK *v19;
  f32 v23;
  s64 v24;
  s64 v27;
  s32 v28;
  s32 v29;
  s32 v30;
  s32 v31;
  s32 v33;
  f32 *p_x;
  void *bsc;
  s32 v37;
  sdfVector4_t v39;
  s32 a_num;

  a_num = dmg;
  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  *(u64 *)&v39.x = 0;
  *(u64 *)&v39.z = 0;
  if ((sBtlGetCutFlg() & 1) != 0)
    return;
  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v17 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (!v17)
  {
    p_x = &vf00.x;
    p_x[4] = x;
    p_x[5] = y;
    p_x[6] = z;
    p_x[7] = w;
    goto LABEL_16;
  }
  v19 = v17;
  sBtlGetChestPos(v19);
LABEL_16:
  v23 = vct_A.x;
  v24 = *(u64 *)&vct_A.z;
  vct_A.x = v23;
  vct_A.y = -120.0;
  *(u64 *)&vct_A.z = v24;
  if (sBtlChangeWorldtoScreenUnity(&v39) && v39.z >= 0.0)
  {
    ToString_55996800((s32)&a_num, "d3", 0);
    v27 = *(u64 *)&v39.x;
    v28 = a_num;
    if (*(f32 *)&v27 == INFINITY)
      v29 = 0x80000000;
    else
      v29 = *(f32 *)&v27;
    v30 = *((f32 *)&v27 + 1);
    if (v28 > 999)
    {
      v31 = -60;
      v33 = v30 - 12;
LABEL_49:
      bsc = wk->bsc;
      if (*((f32 *)&v27 + 1) == INFINITY)
        v37 = 2147483636;
      else
        v37 = v33;
      Num4(bsc, v31 + v29, v37, rgba, 0xFFu, v28, a_size, 0);
      return;
    }
    else if (v28 > 99)
    {
      v31 = -48;
      v33 = v30 - 12;
      goto LABEL_49;
    }
    else
    {
      if (v28 >= 10)
        v31 = -36;
      else
        v31 = -16;
      v33 = v30 - 12;
      goto LABEL_49;
    }
    goto LABEL_49;
  }
}

// 0x20728e0
void DrawTime(void) {
  s32 timecount;
  s32 v5;
  s32 gb_btltime_local;
  s32 v9;
  s32 v10;
  s32 v11;

  if ((wk->status4 & 0x10) != 0)
    return;
  ++g_RedCnt;
  timecount = wk->timecount;
  if (timecount)
  {
    v5 = timecount - gb_btltime;
    gb_btltime_local = v5 & ~(v5 >> 31);
    goto LABEL_16;
  }
  gb_btltime_local = gb_btltime;
LABEL_16:
  if (!wk->timedrawflg)
    return;
  v9 = gb_btltime_local / 60;
  v10 = gb_btltime_local / 3600;
  v11 = v9 % 60;
  TimeLimitDrawUnity(wk->bsc, v10, v11, 0);
}
