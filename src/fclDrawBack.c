#include "types.h"
#include "buttonguide.h"
#include "cmpstatus.h"
#include "fcldrawback.h"
#include "itf.h"
#include "localize.h"

typedef struct itfSprList_t itfSprList_t;
typedef struct sprHandle_t sprHandle_t;

static itfSprList_t *arrSprListJms1[2];
static itfSprList_t *arrSprListJms2;
static itfSprList_t *arrSprListKny1;
static itfSprList_t *arrSprListKny2;
static itfSprList_t *arrSprListNwd1;
static itfSprList_t *arrSprListNwd2;
static itfSprList_t *arrSprListGoh1;
static itfSprList_t *arrSprListGoh2;
static char *strCmdHelp;
static s32 _BackSprite_count;

static void SpriteAlphaF(f32 a_x, f32 a_y, s32 a_z, u8 a_alphaRate, sprHandle_t *a_hSpr, s32 a_sprNo, u32 a_otNo);
static void _BackSprite(s32 a_moveType, s32 a_x, s32 a_y, s32 a_z, u8 a_alphaRate, sprHandle_t *a_hSpr, s32 a_sprNo, u32 a_otNo);

// 0x1a39a20
static void SpriteAlphaF(f32 a_x, f32 a_y, s32 a_z, u8 a_alphaRate, sprHandle_t *a_hSpr, s32 a_sprNo, u32 a_otNo) {
  itfFloatTo32s(a_x, 4);
  itfFloatTo32s(a_y, 3);
}

// 0x1a39aa0
static void _BackSprite(s32 a_moveType, s32 a_x, s32 a_y, s32 a_z, u8 a_alphaRate, sprHandle_t *a_hSpr, s32 a_sprNo, u32 a_otNo) {
  __int128 v9;
  int32x2_t v14;
  float32x2_t v15;
  int8x8_t v16;
  s32 v17;
  __int128 v18;
  s32 v21;
  bool v22;
  __int128 a_num;

  LODWORD(v9) = 0;
  v14.n64_u32[0] = a_x + 195;
  v14.n64_u32[1] = a_y;
  v15.n64_u64[0] = vcvt_f32_s32(v14).n64_u64[0];
  v14.n64_u32[0] = a_moveType;
  v16.n64_u64[0] = vbsl_s8(vdup_lane_s32(vceq_s32(v14, *(int32x2_t *)&v9), 0), (int8x8_t)0x41700000C1500000LL, (int8x8_t)0xC170000041500000LL).n64_u64[0];
  v17 = 16;
  *(float32x2_t *)&v9 = vadd_f32(vdiv_f32(vmul_n_f32(v16, (f32)_BackSprite_count), vdup_n_s32(0x42F00000u)), v15);
  a_num = v9;
  do
  {
    itfFloatTo32s(*(f32 *)&a_num, 4);
    itfFloatTo32s(*((f32 *)&a_num + 1), 3);
    *((u64 *)&v18 + 1) = *((u64 *)&a_num + 1);
    --v17;
    *(float32x2_t *)&v18 = vadd_f32(*(float32x2_t *)&a_num, (float32x2_t)0x41700000C1500000LL);
    a_num = v18;
  }
  while (v17);
  v21 = _BackSprite_count + 1;
  v22 = _BackSprite_count - 119 < 0;
  _BackSprite_count = v21;
  if (v22 == __OFSUB__(v21, 120))
  {
    _BackSprite_count = 0;
  }
}

// 0x1a39c90
void fclBackSprite(s32 a_type, u8 a_alphaRate1, u8 a_alphaRate2, sprHandle_t *a_hSpr) {
  s32 v9;
  char *v10;
  Il2CppObject *v11;
  s32 v12;
  u8 v13;
  sprHandle_t *v14;
  s32 v15;
  u32 v16;
  itfSprList_t *arrSprListJms1_local;
  u32 v20;
  s32 v24;
  u8 v25;
  sprHandle_t *v26;
  s32 v27;
  u32 v28;
  itfSprList_t **p_arrSprListJms2;
  u8 v36;

  v36 = a_alphaRate1;
  if (a_hSpr)
  {
    if (cmpChkDraw())
      return;
    if ((u32)(a_type - 1) >= 2)
      v9 = 107;
    else
      v9 = 53;
    itfDrawMiscSpriteAlpha(0, 0, ((u32)(a_type - 1) < 2) << 12, a_alphaRate2, a_hSpr, 5, v9);
    itfDrawMiscSpriteAlpha(0, 0, 1, a_alphaRate1, a_hSpr, 4, 107);
    v10 = ToString((u8)&v36, 0);
    v11 = Concat_54766928("背景１アルファ = ", v10, 0);
    Log(v11);
    _BackSprite(0, -8, -59, v12, v13, v14, v15, v16);
    switch (a_type)
    {
      case 0:
        arrSprListJms1_local = arrSprListJms1;
        v20 = v36;
        break;
      case 1:
        arrSprListJms1_local = arrSprListKny1;
        v20 = v36;
        break;
      case 2:
        arrSprListJms1_local = arrSprListNwd1;
        v20 = v36;
        break;
      case 3:
        arrSprListJms1_local = arrSprListGoh1;
        v20 = v36;
        break;
      default:
        arrSprListJms1_local = 0;
        v20 = v36;
        break;
    }
    itfDrawMiscSpriteList(0, 0, 1, v20, a_hSpr, 107, arrSprListJms1_local);
    _BackSprite(1, 327, 226, v24, v25, v26, v27, v28);
    switch (a_type)
    {
      case 0:
        p_arrSprListJms2 = &arrSprListJms2;
        goto LABEL_51;
      case 1:
        p_arrSprListJms2 = &arrSprListKny2;
        goto LABEL_51;
      case 2:
        p_arrSprListJms2 = &arrSprListNwd2;
        goto LABEL_51;
      case 3:
        p_arrSprListJms2 = &arrSprListGoh2;
LABEL_51:
        arrSprListJms1_local = *p_arrSprListJms2;
        break;
      default:
        break;
    }
    itfDrawMiscSpriteList(0, 0, 1, a_alphaRate2, a_hSpr, 107, arrSprListJms1_local);
  }
}

// 0x1a3a070
void fclCommandHelp(s32 a_cmdID, u8 a_alphaRate) {
  u32 v6;
  char *v7;
  char *v8;
  char *a_str;

  if ((u32)a_cmdID <= 0x28)
  {
    v6 = a_alphaRate;
    v7 = strCmdHelp[a_cmdID];
    ButtonLineHelpTextSet(v7, 0, 1, 0xA09DC380, 1);
    v8 = strCmdHelp[a_cmdID];
    a_str = GetLocalizeText(v8, 1);
    itfDrawFont(0, 31, 384, 0, 0, 0, 0xA09DC380, (f32)v6 / 255.0, 109, a_str);
  }
}
