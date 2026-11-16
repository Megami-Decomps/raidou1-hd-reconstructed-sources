#include "types.h"
#include "cmphelp.h"

#define CMPHELP_SPRNAME_HELP "/shop/setumei.spr"

typedef enum {
    CMPHELP_LINE_MAX = 2,
    CMPHELP_BASE_X = 67,
    CMPHELP_BASE_Y = 322,
    CMPHELP_HELP_OFSX = 36,
    CMPHELP_HELP_OFSY = -2,
    CMPHELP_TEXT_OFSX = 20,
    CMPHELP_TEXT_OFSY = 27,
} CMPHELP;

typedef enum {
    CMPHELP_Z_FONT = 1048576,
    CMPHELP_Z_WND = 4112,
    CMPHELP_Z_WND2 = 4096,
} CMPHELP_Z;

typedef struct tagCMPHELP_WK tagCMPHELP_WK;

tagCMPHELP_WK *wk;
s16 **cmpHelpSprParam;

// 0x1e5a9f0
void cmpSetDraw(bool a_bDraw) {
  if (a_bDraw)
  {
    wk->stat |= 2u;
    return;
  }
  wk->stat &= ~2u;
}

// 0x1e5aab0
bool cmpGetDraw(void) {
  return (LOBYTE(wk->stat) >> 1) & 1;
}

// 0x1e5ab20
void cmpSetType(CMPHELP_TYPE a_type) {
  wk->stat |= 1u;
  wk->type = a_type;
}

// 0x1e5aba0
void cmpSetId(u16 a_id) {
  s32 stat;

  stat = wk->stat;
  wk->id = a_id;
  wk->stat = stat & 0xFFFFFFFB;
}

// 0x1e5ac20
void cmpSetNew(void) {
  wk->stat |= 4u;
}

// 0x1e5ac90
void cmpDrawSpriteDef(s32 a_x, s32 a_y, s32 a_z, u8 a_alphaRate, s32 a_sprno) {
  ;
}

// 0x1e5aca0
u32 cmpSetAlphaRate(u32 a_color, f32 a_alphaRate) {
  return a_color & 0xFFFFFF00
       | (u8)(s32)(f32)((f32)((f32)(u8)a_color * a_alphaRate) / 255.0);
}

// 0x1e5acd0
void cmpDrawEx(FRW_FRW a_drawmode, f32 a_alphaRate) {
  tagCMPHELP_WK *wk_local;
  s32 stat;
  s32 i;

  wk_local = wk;
  *(u64 *)&wk_local->basePosX = 0x14200000043LL;
  stat = wk_local->stat;
  if ((stat & 1) != 0)
  {
    if ((stat & 2) == 0)
      return;
    for (i = 0; ; ++i)
    {
      if (cmpHelpSprParam[i][0] < 0)
        break;
    }
    if ((wk->stat & 4) == 0)
      return;
  }
}

// 0x1e5adf0
void cmpDraw(void) {
  f32 v2;

  cmpDrawEx((s32)cmpHelp, v2);
}

// 0x1e5ae60
void cmpDrawAlpha(f32 a_alphaRate) {
  cmpDrawEx((s32)cmpHelp, a_alphaRate);
}

// 0x1e5aed0
void Init(void) {
  Il2CppObject *v1;

  v1 = Allocate(tagCMPHELP_WK);
  _ctor(v1, 0);
  wk = (tagCMPHELP_WK *)v1;
}

// 0x1e5af80
void cmpStartLoadSprite(void) {
  ;
}

// 0x1e5af90
bool cmpCheckLoadSprite(void) {
  return wk->hSpr != 0;
}

// 0x1e5b000
void cmpEnd(void) {
  tagCMPHELP_WK *wk_local;

  wk_local = wk;
  if (!wk_local->hSpr)
  {
    goto LABEL_5;
  }
  wk_local = wk;
  wk_local->hSpr = 0;
LABEL_5:
  if (!wk)
    return;
  wk = 0;
}
