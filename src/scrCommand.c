#include "types.h"
#include "dat.h"
#include "dds3_pad2.h"
#include "dds3effect_blend.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3padmanager.h"
#include "eve.h"
#include "evtbit.h"
#include "evtmoon.h"
#include "fld.h"
#include "itf.h"
#include "sbattle.h"
#include "sbtlmenu.h"
#include "scr.h"
#include "scrcommand.h"
#include "sdat.h"
#include "sdf_vu0.h"
#include "sdfrand.h"
#include "sdfsystem.h"

#define MOVIE_CANCEL_FLAG_INT_INDEX 210

typedef enum {
    TAKUMI_FLAG_NONE = 0,
    TAKUMI_FLAG_RAIDOU = 1,
    TAKUMI_FLAG_NAKAMA = 2,
} TAKUMI_FLAG;

typedef enum {
    TAKUMI_TYPE_NONE = -1,
    TAKUMI_TYPE_A = 0,
    TAKUMI_TYPE_B = 1,
    TAKUMI_TYPE_C = 2,
    TAKUMI_TYPE_D = 3,
    TAKUMI_TYPE_E = 4,
    TAKUMI_TYPE_F = 5,
    TAKUMI_TYPE_G = 6,
} TAKUMI_TYPE;

typedef enum {
    TAKUMI_RET_ERROR = -2,
    TAKUMI_RET_RAIDOU = -1,
} TAKUMI_RET;

typedef struct ItemTable_t ItemTable_t;
typedef struct RateTable_t RateTable_t;
typedef struct RetInfo_t RetInfo_t;
typedef struct TakumiInfoRet_t TakumiInfoRet_t;
typedef struct TakumiInfo_t TakumiInfo_t;
typedef struct scrCommandTable_t scrCommandTable_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

typedef s32 (*TakumiKoukaFunc_t)(TakumiInfo_t *pInfo);

struct TakumiInfoRet_t {
    TAKUMI_TYPE Type;
    s32 Target;
    s32 ItemID;
    s32 ItemID2;
};

struct TakumiInfo_t {
    sdatUnitWork_t *pUnit;
    TakumiInfoRet_t *Ret;
};

struct RetInfo_t {
    s32 ItemID;
    u8 Nums;
};

scrCommandTable_t *tbl;
static bool noskip_fade;
static bool noSkipWait;
static bool is_moon;
static bool out_flg;
static TakumiInfo_t *s_ExecTakumi_info;
static RetInfo_t *s_ret_info;
void *item_takumi_table;
static s32 *rate_table;
static TakumiKoukaFunc_t **func;
RateTable_t *rate_teisatu_table;
ItemTable_t *item_teisatu_table;

static u32 IntParaToRGBA(s32 offset);
static void FldObjOut(void);
static void FldObjIn(void);
static s32 TakumiGetTarget(s32 type);
static s32 TakumiKoukaA(TakumiInfo_t *pInfo);
static s32 TakumiKoukaB(TakumiInfo_t *pInfo);
static s32 TakumiKoukaC(TakumiInfo_t *pInfo);
static s32 TakumiKoukaD(TakumiInfo_t *pInfo);
static s32 TakumiKoukaE(TakumiInfo_t *pInfo);
static s32 TakumiKoukaF(TakumiInfo_t *pInfo);
static s32 TakumiKoukaG(TakumiInfo_t *pInfo);
static s32 ExecTakumi(TakumiInfo_t *pInfo);
static s32 ExecTeisatuItem(s32 mode, sdatUnitWork_t *pUnit);

// macros
// 0x21527a0: s32 PAUSE_ONOFF(void)
static inline s32 PAUSE_ONOFF(void) {
  scrGetIntPara(0);
  return 1;
}

// 0x2152800: s32 BIT_CHK(void)
static inline s32 BIT_CHK(void) {
  s32 IntPara;
  bool v2;

  IntPara = scrGetIntPara(0);
  v2 = evtBitCheck(IntPara);
  scrSetIntReturnValue(v2);
  return 1;
}

// 0x2152890: s32 BIT_ON(void)
static inline s32 BIT_ON(void) {
  s32 IntPara;
  s64 v4;

  IntPara = scrGetIntPara(0);
  if (!IntPara)
    return 1;
  if ((u32)(IntPara - 2618) >= 0xFFFFFFC6)
    evtBitKityouItemAdd(IntPara);
  v4 = (s64)GBWK->EventBit + 4 * (IntPara / 32);
  *(u32 *)(v4 + 32) |= 1 << IntPara;
  return 1;
}

// 0x21529a0: s32 BIT_OFF(void)
static inline s32 BIT_OFF(void) {
  s32 IntPara;
  s64 v4;

  IntPara = scrGetIntPara(0);
  v4 = (s64)GBWK->EventBit + 4 * (IntPara / 32);
  *(u32 *)(v4 + 32) &= ~(1 << IntPara);
  return 1;
}

// 0x2152a90: s32 RND(void)
static inline s32 RND(void) {
  s64 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = sub_1905740(IntPara, 0);
  scrSetIntReturnValue(v2 + 1);
  return 1;
}

// 0x2152b10: s32 SYNC(void)
#define SYNC() (scrGetCommandTimer() != 0)

// 0x2152b70: s32 WAIT(void)
static inline s32 WAIT(void) {
  s32 IntPara;
  s32 result;

  IntPara = scrGetIntPara(0);
  if (!noskip_fade)
  {
    if (scrIsEventSkip(0))
      goto LABEL_11;
  }
  if (IntPara < 1)
    return 1;
  goto LABEL_18;
LABEL_11:
  result = 1;
  if (noSkipWait && IntPara > 0)
  {
LABEL_18:
    if (scrGetCommandTimer() < IntPara)
      return 0;
    noskip_fade = 0;
    return 1;
  }
  return result;
}

// 0x2152d00: s32 PUT(void)
#define PUT() (1)

// 0x2152d10: s32 PUTS(void)
#define PUTS() (1)

// 0x2152d20: s32 FADE_IN(void)
static inline s32 FADE_IN(void) {
  s32 IntPara;
  u32 v7;
  u32 v8;
  u32 v9;
  u32 v10;

  goto LABEL_3;
LABEL_9:
  IntPara = scrGetIntPara(0);
  if (IntPara != 100)
  {
    if (IntPara != 1)
    {
      if (IntPara)
        return 1;
      fademode = 0;
      v7 = scrGetIntPara(1);
      v8 = 0;
      v9 = 0;
      v10 = 0;
LABEL_29:
      dds3FadeIn(v8, v9, v10, v7);
      return 0;
    }
    fademode = 0;
    v7 = scrGetIntPara(1);
    v8 = 255;
    v9 = 255;
    v10 = 255;
    goto LABEL_29;
  }
  fademode = 0;
  v7 = scrGetIntPara(1);
  v8 = 208;
  v9 = 246;
  v10 = 173;
  goto LABEL_29;
LABEL_3:
  if (!scrGetCommandTimer())
    goto LABEL_9;
  noskip_fade = 1;
  return 1;
}

// 0x2153070: s32 FADE_OUT(void)
static inline s32 FADE_OUT(void) {
  s32 IntPara;
  u32 v7;
  u32 v8;
  u32 v9;
  u32 v10;

  goto LABEL_3;
LABEL_9:
  IntPara = scrGetIntPara(0);
  if (IntPara != 100)
  {
    if (IntPara != 1)
    {
      if (IntPara)
        return 1;
      fademode = 0;
      v7 = scrGetIntPara(1);
      v8 = 0;
      v9 = 0;
      v10 = 0;
LABEL_29:
      dds3FadeOut(v8, v9, v10, v7);
      return 0;
    }
    fademode = 0;
    v7 = scrGetIntPara(1);
    v8 = 255;
    v9 = 255;
    v10 = 255;
    goto LABEL_29;
  }
  fademode = 0;
  v7 = scrGetIntPara(1);
  v8 = 208;
  v9 = 246;
  v10 = 173;
  goto LABEL_29;
LABEL_3:
  if (!scrGetCommandTimer())
    goto LABEL_9;
  noskip_fade = 1;
  return 1;
}

// 0x21533c0: s32 CHK_FADE_END(void)
static inline s32 CHK_FADE_END(void) {
  s32 IntPara;
  s32 v5;

  IntPara = scrGetIntPara(0);
  if (IntPara != 1)
    goto LABEL_4;
  if (fadergba.w != 1.0)
    goto LABEL_17;
LABEL_9:
  v5 = 1;
  goto LABEL_19;
LABEL_4:
  if (IntPara)
    goto LABEL_17;
  if (fadergba.w == 0.0)
    goto LABEL_9;
LABEL_17:
  v5 = 0;
LABEL_19:
  scrSetIntReturnValue(v5);
  return 1;
}

// 0x21535b0: s32 BISTA_IN(void)
static inline s32 BISTA_IN(void) {
  u32 IntPara;

  if (scrGetCommandTimer())
    return 1;
  IntPara = scrGetIntPara(0);
  dds3BistaIn(IntPara);
  FldObjIn();
  return 0;
}

// 0x2153950: s32 BISTA_OUT(void)
static inline s32 BISTA_OUT(void) {
  u32 IntPara;
  u32 v5;

  if (scrGetCommandTimer())
    return 1;
  dds3ChangeBistaMode(1);
  IntPara = scrGetIntPara(0);
  v5 = scrGetIntPara(1);
  dds3BistaOutEx(IntPara, v5);
  FldObjOut();
  return 0;
}

// 0x2153dd0: s32 BISTA_OUT2(void)
static inline s32 BISTA_OUT2(void) {
  u32 IntPara;
  u32 v5;

  if (scrGetCommandTimer())
    return 1;
  dds3ChangeBistaMode(2);
  IntPara = scrGetIntPara(0);
  v5 = scrGetIntPara(1);
  dds3BistaOutEx(IntPara, v5);
  FldObjOut();
  return 0;
}

// 0x2153f20: s32 BISTA_OUT3(void)
static inline s32 BISTA_OUT3(void) {
  u32 IntPara;

  if (scrGetCommandTimer())
    return 1;
  dds3ChangeBistaMode(3);
  IntPara = scrGetIntPara(0);
  dds3BistaOut(IntPara);
  FldObjOut();
  return 0;
}

// 0x2154060: s32 BISTA_OUT_HD(void)
static inline s32 BISTA_OUT_HD(void) {
  s32 IntPara;
  u32 v4;

  if (scrGetCommandTimer())
    return 1;
  IntPara = scrGetIntPara(2);
  dds3ChangeBistaMode(IntPara);
  v4 = scrGetIntPara(0);
  dds3BistaOut(v4);
  FldObjOut();
  return 0;
}

// 0x2154190: s32 POSTESP_ON(void)
static inline s32 POSTESP_ON(void) {
  u32 IntPara;

  if (scrGetCommandTimer())
    return 1;
  IntPara = scrGetIntPara(0);
  dds3PostEspOn(IntPara);
  return 0;
}

// 0x2154270: s32 POSTESP_OFF(void)
static inline s32 POSTESP_OFF(void) {
  u32 IntPara;

  if (scrGetCommandTimer())
    return 1;
  IntPara = scrGetIntPara(0);
  dds3PostEspOff(IntPara);
  return 0;
}

// 0x2154450: s32 MOON_OUT(void)
static inline s32 MOON_OUT(void) {
  FldObjOut();
  return 1;
}

// 0x21544d0: s32 MOON_IN(void)
static inline s32 MOON_IN(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  if (IntPara == 1)
  {
    *((u8 *)*((const MethodInfo *)scrCommand + 2).virtualMethodPointer + 10) = 1;
    return 1;
  }
  else
  {
    FldObjIn();
    return 1;
  }
}

// 0x21545a0: s32 MOON_IN_PROGRAM(void)
static inline s32 MOON_IN_PROGRAM(void) {
  FldObjIn();
  return 1;
}

// 0x2154620: s32 SEL_JMP(void)
static inline s32 SEL_JMP(void) {
  s32 IntPara;
  s32 v4;
  s32 v5;
  s32 v6;
  s32 LabelCodeAddress;

  IntPara = scrGetIntPara(0);
  if (IntPara < 0)
    return 1;
  v4 = IntPara;
  v5 = scrGetIntPara(IntPara + 1);
  if (v5 < 0)
    return 1;
  v6 = v5;
  LabelCodeAddress = scrGetLabelCodeAddress(v6);
  scrSetCodePointer(LabelCodeAddress);
  return 1;
}

// 0x2154710: s32 PAD_TRIG(void)
static inline s32 PAD_TRIG(void) {
  s32 IntPara;
  bool v2;

  IntPara = scrGetIntPara(0);
  v2 = CHECK_TRIG(IntPara, 0);
  scrSetIntReturnValue(v2);
  return 1;
}

// 0x21547a0: s32 PAD_PRESS(void)
static inline s32 PAD_PRESS(void) {
  s32 IntPara;
  bool v2;

  IntPara = scrGetIntPara(0);
  v2 = CHECK_PRESS(IntPara, 0);
  scrSetIntReturnValue(v2);
  return 1;
}

// 0x2154830: s32 PAD_ACT(void)
static inline s32 PAD_ACT(void) {
  u32 IntPara;
  u8 v2;
  u32 v3;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  dds3PadAct(IntPara, v2, v3);
  return 1;
}

// 0x2154900: s32 SET_FOVY(void)
static inline s32 SET_FOVY(void) {
  f32 v1;

  v1 = scrGetFloatPara(0) * 0.017453292;
  if (v1 > 5.0 && v1 < 180.0)
  {
    dds3SetScreenFovy(v1);
  }
  return 1;
}

// 0x21549c0: s32 SCR_RUN(void)
static inline s32 SCR_RUN(void) {
  s32 startproc;
  dds3ProcessID_t *ProcessID;
  s32 priority;
  s32 IntPara;
  dds3ProcessID_t *started;

  startproc = scrGetIntPara(0);
  if (!s_hNowpWork)
    return 1;
  ProcessID = s_hNowpWork->ProcessID;
  if (!ProcessID || startproc < 0 || startproc >= s_hNowpWork->TypeTable[0]->ItemCount)
    return 1;
  priority = ProcessID->priority;
  IntPara = scrGetIntPara(1);
  started = scrStartScript1(IntPara + priority, s_hNowpWork->Header, s_hNowpWork->TypeTable, s_hNowpWork->ProcTable, s_hNowpWork->LabelTable, s_hNowpWork->Code, s_hNowpWork->MessageData, s_hNowpWork->StringData, startproc);
  scrSetdds3ProcessIDReturnValue(started);
  return 1;
}

// 0x2154b10: s32 SCR_KILL(void)
static inline s32 SCR_KILL(void) {
  dds3ProcessID_t *id;

  id = scrGetdds3ProcessIDPara(0);
  if (!dds3ExistProcess(id))
    return 1;
  dds3KillProcess(id, 1);
  return 1;
}

// 0x2154c00: s32 SCR_WAIT(void)
static inline s32 SCR_WAIT(void) {
  dds3ProcessID_t *id;

  id = scrGetdds3ProcessIDPara(0);
  return !dds3ExistProcess(id);
}

// 0x2154ca0: s32 SCR_STAT(void)
static inline s32 SCR_STAT(void) {
  bool exist;
  dds3ProcessID_t *id;

  id = scrGetdds3ProcessIDPara(0);
  exist = dds3ExistProcess(id);
  scrSetIntReturnValue(exist);
  return 1;
}

// 0x2154d60: s32 SCR_TIME(void)
static inline s32 SCR_TIME(void) {
  u32 ProcessRunTime;
  dds3ProcessID_t *id;

  id = scrGetdds3ProcessIDPara(0);
  if (dds3ExistProcess(id))
  {
    ProcessRunTime = dds3GetProcessRunTime(id);
    goto LABEL_14;
  }
  ProcessRunTime = 0;
LABEL_14:
  scrSetIntReturnValue(ProcessRunTime);
  return 1;
}

// 0x2154e60: s32 QUAKE_ON(void)
static inline s32 QUAKE_ON(void) {
  s32 IntPara;
  u32 v2;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  dds3SetQuake(IntPara, v2);
  return 1;
}

// 0x2154f10: s32 QUAKE_OFF(void)
static inline s32 QUAKE_OFF(void) {
  dds3StopQuake();
  return 1;
}

// 0x2154f90: s32 SCENE_LIGHT_RGB(void)
static inline s32 SCENE_LIGHT_RGB(void) {
  f32 FloatPara;
  f32 v3;
  f32 v5;
  f32 *p_x;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  u32 IntPara;
  sdfVector4_t v14;

  FloatPara = scrGetFloatPara(1);
  vct_A.x = FloatPara;
  v3 = scrGetFloatPara(2);
  vct_A.y = v3;
  v5 = scrGetFloatPara(3);
  vct_A.z = v5;
  vct_A.w = 0.0;
  p_x = &vf00.x;
  v8 = p_x[4];
  v9 = p_x[5];
  v10 = p_x[6];
  v11 = p_x[7];
  IntPara = scrGetIntPara(0);
  v14.x = v8;
  v14.y = v9;
  v14.z = v10;
  v14.w = v11;
  dds3SetLightColor(IntPara, 0, v14);
  return 1;
}

// 0x2155240: s32 SCENE_LIGHT_DIR(void)
static inline s32 SCENE_LIGHT_DIR(void) {
  f32 FloatPara;
  f32 v2;
  f32 v3;
  u32 IntPara;
  sdfVector4_t v6;

  FloatPara = scrGetFloatPara(1);
  v2 = scrGetFloatPara(2);
  v3 = scrGetFloatPara(3);
  if (fabsf(FloatPara) > 0.01)
    goto LABEL_17;
  if (fabsf(v2) > 0.01)
    goto LABEL_17;
  if (fabsf(v3) <= 0.01)
    return 1;
LABEL_17:
  IntPara = scrGetIntPara(0);
  v6.w = 0.0;
  v6.x = FloatPara;
  v6.y = v2;
  v6.z = v3;
  dds3SetLightDir(IntPara, 0, v6);
  return 1;
}

// 0x2155430: s32 SCENE_AMBIENT(void)
static inline s32 SCENE_AMBIENT(void) {
  f32 FloatPara;
  f32 v3;
  f32 v5;
  f32 *p_x;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  u32 IntPara;
  sdfVector4_t v14;

  FloatPara = scrGetFloatPara(1);
  vct_A.x = FloatPara;
  v3 = scrGetFloatPara(2);
  vct_A.y = v3;
  v5 = scrGetFloatPara(3);
  vct_A.z = v5;
  vct_A.w = 1.0;
  p_x = &vf00.x;
  v8 = p_x[4];
  v9 = p_x[5];
  v10 = p_x[6];
  v11 = p_x[7];
  IntPara = scrGetIntPara(0);
  v14.x = v8;
  v14.y = v9;
  v14.z = v10;
  v14.w = v11;
  dds3SetAmbientColor(IntPara, v14);
  return 1;
}

// 0x21556f0: s32 SCENE_FOG_RGB(void)
static inline s32 SCENE_FOG_RGB(void) {
  scrGetFloatPara(1);
  scrGetFloatPara(2);
  scrGetFloatPara(3);
  return 1;
}

// 0x2155770: s32 SCENE_FOG_PARA(void)
#define SCENE_FOG_PARA() (1)

// 0x2155780: s32 SOFTEN_BIAS(void)
#define SOFTEN_BIAS() (1)

// 0x2155790: s32 BLUR(void)
static inline s32 BLUR(void) {
  u32 IntPara;
  s32 v2;
  s32 v3;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = scrGetIntPara(2);
  dds3SetBlur(IntPara, v2, v3);
  return 1;
}

// 0x2155860: s32 MUL_BLUR_PARA(void)
static inline s32 MUL_BLUR_PARA(void) {
  SDF_GS_ALPHA *p_SEMI;
  SDF_GS_ALPHA *SEMI_local;
  s32 IntPara;
  SDF_GS_ALPHA *p_SUB;
  f32 FloatPara;
  f32 v12;

  p_SEMI = &SEMI;
  SEMI_local = p_SEMI;
  IntPara = scrGetIntPara(2);
  if (IntPara == 2)
  {
    p_SUB = &SUB;
  }
  else
  {
    if (IntPara != 1)
      goto LABEL_16;
    p_SUB = &ADD;
  }
  SEMI_local = p_SUB;
LABEL_16:
  FloatPara = scrGetFloatPara(0);
  v12 = scrGetFloatPara(1);
  SetPara(MultiBlur, FloatPara, v12, SEMI_local, 0);
  return 1;
}

// 0x2155a10: s32 MUL_BLUR_RGBA(void)
static inline s32 MUL_BLUR_RGBA(void) {
  u8 IntPara;
  u8 v3;
  u8 v4;
  s32 v5;

  IntPara = scrGetIntPara(0);
  v3 = scrGetIntPara(1);
  v4 = scrGetIntPara(2);
  v5 = scrGetIntPara(3);
  _SetRGBA(MultiBlur, IntPara | (u16)(v3 << 8) | (v4 << 16) | (v5 << 24));
  return 1;
}

// 0x2155b70: s32 MUL_BLUR_AREA(void)
static inline s32 MUL_BLUR_AREA(void) {
  s32 IntPara;
  s32 v6;
  s32 v7;

  IntPara = scrGetIntPara(0);
  v6 = scrGetIntPara(1);
  v7 = scrGetIntPara(2);
  SetArea(MultiBlur, IntPara, v6, v7, 0);
  return 1;
}

// 0x2155c70: s32 MUL_BLUR_SWAP(void)
static inline s32 MUL_BLUR_SWAP(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  _Swap(MultiBlur, IntPara);
  return 1;
}

// 0x2155d30: s32 MUL_BLUR_ON(void)
static inline s32 MUL_BLUR_ON(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  _On(MultiBlur, IntPara);
  return 1;
}

// 0x2155df0: s32 MUL_BLUR_OFF(void)
static inline s32 MUL_BLUR_OFF(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  _Off(MultiBlur, IntPara);
  return 1;
}

// 0x2155eb0: s32 DIST_BLUR_PARA(void)
static inline s32 DIST_BLUR_PARA(void) {
  SDF_GS_ALPHA *p_SEMI;
  SDF_GS_ALPHA *SEMI_local;
  s32 IntPara;
  SDF_GS_ALPHA *p_SUB;
  s32 v11;
  s32 v12;
  s32 v13;
  f32 FloatPara;
  f32 v15;
  f32 v16;

  p_SEMI = &SEMI;
  SEMI_local = p_SEMI;
  IntPara = scrGetIntPara(6);
  if (IntPara == 2)
  {
    p_SUB = &SUB;
  }
  else
  {
    if (IntPara != 1)
      goto LABEL_16;
    p_SUB = &ADD;
  }
  SEMI_local = p_SUB;
LABEL_16:
  v11 = scrGetIntPara(0);
  v12 = scrGetIntPara(1);
  v13 = scrGetIntPara(2);
  FloatPara = scrGetFloatPara(3);
  v15 = scrGetFloatPara(4);
  v16 = scrGetFloatPara(5);
  SetPara(DistBlur, v11, v12, v13, FloatPara, v15, v16, SEMI_local, 0);
  return 1;
}

// 0x21560b0: s32 DIST_BLUR_RGBA(void)
static inline s32 DIST_BLUR_RGBA(void) {
  u8 IntPara;
  u8 v3;
  u8 v4;
  s32 v5;

  IntPara = scrGetIntPara(0);
  v3 = scrGetIntPara(1);
  v4 = scrGetIntPara(2);
  v5 = scrGetIntPara(3);
  _SetRGBA(DistBlur, IntPara | (u16)(v3 << 8) | (v4 << 16) | (v5 << 24));
  return 1;
}

// 0x2156210: s32 DIST_BLUR_AREA(void)
static inline s32 DIST_BLUR_AREA(void) {
  s32 IntPara;
  s32 v6;
  s32 v7;

  IntPara = scrGetIntPara(0);
  v6 = scrGetIntPara(1);
  v7 = scrGetIntPara(2);
  SetArea(DistBlur, IntPara, v6, v7, 0);
  return 1;
}

// 0x2156310: s32 DIST_BLUR_SWAP(void)
static inline s32 DIST_BLUR_SWAP(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  _Swap(DistBlur, IntPara);
  return 1;
}

// 0x21563d0: s32 DIST_BLUR_ON(void)
static inline s32 DIST_BLUR_ON(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  _On(DistBlur, IntPara);
  return 1;
}

// 0x2156490: s32 DIST_BLUR_OFF(void)
static inline s32 DIST_BLUR_OFF(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  _Off(DistBlur, IntPara);
  return 1;
}

// 0x2156550: s32 RIP_BLUR_PARA(void)
static inline s32 RIP_BLUR_PARA(void) {
  SDF_GS_ALPHA *p_SEMI;
  SDF_GS_ALPHA *SEMI_local;
  s32 IntPara;
  SDF_GS_ALPHA *p_SUB;
  s32 v11;
  f32 FloatPara;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;

  p_SEMI = &SEMI;
  SEMI_local = p_SEMI;
  IntPara = scrGetIntPara(6);
  if (IntPara == 2)
  {
    p_SUB = &SUB;
  }
  else
  {
    if (IntPara != 1)
      goto LABEL_16;
    p_SUB = &ADD;
  }
  SEMI_local = p_SUB;
LABEL_16:
  v11 = scrGetIntPara(0);
  FloatPara = scrGetFloatPara(1);
  v13 = scrGetFloatPara(2);
  v14 = scrGetFloatPara(3);
  v15 = scrGetFloatPara(4);
  v16 = scrGetFloatPara(5);
  SetPara(RipBlur, v11, FloatPara, v13, v14, v15, v16, SEMI_local, 0);
  return 1;
}

// 0x2156750: s32 RIP_BLUR_RGBA(void)
static inline s32 RIP_BLUR_RGBA(void) {
  u8 IntPara;
  u8 v3;
  u8 v4;
  s32 v5;

  IntPara = scrGetIntPara(0);
  v3 = scrGetIntPara(1);
  v4 = scrGetIntPara(2);
  v5 = scrGetIntPara(3);
  _SetRGBA(RipBlur, IntPara | (u16)(v3 << 8) | (v4 << 16) | (v5 << 24));
  return 1;
}

// 0x21568b0: s32 RIP_BLUR_AREA(void)
static inline s32 RIP_BLUR_AREA(void) {
  s32 IntPara;
  s32 v6;
  s32 v7;

  IntPara = scrGetIntPara(0);
  v6 = scrGetIntPara(1);
  v7 = scrGetIntPara(2);
  SetArea(RipBlur, IntPara, v6, v7, 0);
  return 1;
}

// 0x21569b0: s32 RIP_BLUR_SWAP(void)
static inline s32 RIP_BLUR_SWAP(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  _Swap(RipBlur, IntPara);
  return 1;
}

// 0x2156a70: s32 RIP_BLUR_ON(void)
static inline s32 RIP_BLUR_ON(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  _On(RipBlur, IntPara);
  return 1;
}

// 0x2156b30: s32 RIP_BLUR_OFF(void)
static inline s32 RIP_BLUR_OFF(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  _Off(RipBlur, IntPara);
  return 1;
}

// 0x2156bf0: s32 BLUR2_PARA(void)
static inline s32 BLUR2_PARA(void) {
  SDF_GS_ALPHA *p_SEMI;
  SDF_GS_ALPHA *SEMI_local;
  s32 IntPara;
  SDF_GS_ALPHA *p_SUB;
  f32 FloatPara;
  f32 v12;

  p_SEMI = &SEMI;
  SEMI_local = p_SEMI;
  IntPara = scrGetIntPara(2);
  if (IntPara == 2)
  {
    p_SUB = &SUB;
  }
  else
  {
    if (IntPara != 1)
      goto LABEL_16;
    p_SUB = &ADD;
  }
  SEMI_local = p_SUB;
LABEL_16:
  FloatPara = scrGetFloatPara(0);
  v12 = scrGetFloatPara(1);
  SetPara(Blur2, FloatPara, v12, SEMI_local, 0);
  return 1;
}

// 0x2156da0: s32 BLUR2_RGBA(void)
static inline s32 BLUR2_RGBA(void) {
  u8 IntPara;
  u8 v3;
  u8 v4;
  s32 v5;

  IntPara = scrGetIntPara(0);
  v3 = scrGetIntPara(1);
  v4 = scrGetIntPara(2);
  v5 = scrGetIntPara(3);
  _SetRGBA(Blur2, IntPara | (u16)(v3 << 8) | (v4 << 16) | (v5 << 24));
  return 1;
}

// 0x2156f00: s32 BLUR2_AREA(void)
static inline s32 BLUR2_AREA(void) {
  s32 IntPara;
  s32 v6;

  IntPara = scrGetIntPara(0);
  v6 = scrGetIntPara(1);
  SetArea(Blur2, IntPara, v6, 0);
  return 1;
}

// 0x2156fe0: s32 BLUR2_SWAP(void)
static inline s32 BLUR2_SWAP(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  _Swap(Blur2, IntPara);
  return 1;
}

// 0x21570a0: s32 BLUR2_ON(void)
static inline s32 BLUR2_ON(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  _On(DistBlur, IntPara);
  return 1;
}

// 0x2157160: s32 BLUR2_OFF(void)
static inline s32 BLUR2_OFF(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  _Off(DistBlur, IntPara);
  return 1;
}

// 0x2157220: s32 FILTER2_PARA(void)
static inline s32 FILTER2_PARA(void) {
  SDF_GS_ALPHA *p_SEMI;
  SDF_GS_ALPHA *SEMI_local;
  s32 IntPara;
  SDF_GS_ALPHA *p_NEG;

  p_SEMI = &SEMI;
  SEMI_local = p_SEMI;
  IntPara = scrGetIntPara(0);
  switch (IntPara)
  {
    case 3:
      p_NEG = &NEG;
      break;
    case 2:
      p_NEG = &SUB;
      break;
    case 1:
      p_NEG = &ADD;
      break;
    default:
      goto LABEL_20;
  }
  SEMI_local = p_NEG;
LABEL_20:
  SetPara(Filter2, SEMI_local, 0);
  return 1;
}

// 0x21573a0: s32 FILTER2_RGBA(void)
static inline s32 FILTER2_RGBA(void) {
  u8 IntPara;
  u8 v3;
  u8 v4;
  s32 v5;

  IntPara = scrGetIntPara(0);
  v3 = scrGetIntPara(1);
  v4 = scrGetIntPara(2);
  v5 = scrGetIntPara(3);
  _SetRGBA(Filter2, IntPara | (u16)(v3 << 8) | (v4 << 16) | (v5 << 24));
  return 1;
}

// 0x2157500: s32 FILTER2_SWAP(void)
static inline s32 FILTER2_SWAP(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  _Swap(Filter2, IntPara);
  return 1;
}

// 0x21575c0: s32 FILTER2_ON(void)
static inline s32 FILTER2_ON(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  _On(Filter2, IntPara);
  return 1;
}

// 0x2157680: s32 FILTER2_OFF(void)
static inline s32 FILTER2_OFF(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  _Off(Filter2, IntPara);
  return 1;
}

// 0x2157740: s32 MFILTER_PARA(void)
static inline s32 MFILTER_PARA(void) {
  SDF_GS_ALPHA *p_SEMI;
  SDF_GS_ALPHA *SEMI_local;
  s32 IntPara;
  SDF_GS_ALPHA *p_NEG;

  p_SEMI = &SEMI;
  SEMI_local = p_SEMI;
  IntPara = scrGetIntPara(0);
  switch (IntPara)
  {
    case 3:
      p_NEG = &NEG;
      break;
    case 2:
      p_NEG = &SUB;
      break;
    case 1:
      p_NEG = &ADD;
      break;
    default:
      goto LABEL_20;
  }
  SEMI_local = p_NEG;
LABEL_20:
  SetPara(MFilter, SEMI_local, 0);
  return 1;
}

// 0x21578c0: s32 MFILTER_RGBA(void)
static inline s32 MFILTER_RGBA(void) {
  u8 IntPara;
  u8 v3;
  u8 v4;
  s32 v5;

  IntPara = scrGetIntPara(0);
  v3 = scrGetIntPara(1);
  v4 = scrGetIntPara(2);
  v5 = scrGetIntPara(3);
  _SetRGBA(MFilter, IntPara | (u16)(v3 << 8) | (v4 << 16) | (v5 << 24));
  return 1;
}

// 0x2157a20: s32 MFILTER_AREA(void)
static inline s32 MFILTER_AREA(void) {
  s32 IntPara;
  s32 v6;
  s32 v7;

  IntPara = scrGetIntPara(0);
  v6 = scrGetIntPara(1);
  v7 = scrGetIntPara(2);
  SetArea(MFilter, IntPara, v6, v7, 0);
  return 1;
}

// 0x2157b20: s32 MFILTER_SWAP(void)
static inline s32 MFILTER_SWAP(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  _Swap(MFilter, IntPara);
  return 1;
}

// 0x2157be0: s32 MFILTER_ON(void)
static inline s32 MFILTER_ON(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  _On(MFilter, IntPara);
  return 1;
}

// 0x2157ca0: s32 MFILTER_OFF(void)
static inline s32 MFILTER_OFF(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  _Off(MFilter, IntPara);
  return 1;
}

// 0x2157d60: s32 BLUR_ALLOFF(void)
static inline s32 BLUR_ALLOFF(void) {
  dds3SetBlur(0, 0, 0);
  _Off(DistBlur, 0);
  _Off(MultiBlur, 0);
  _Off(DistBlur, 0);
  _Off(RipBlur, 0);
  (ParallelBlur->klass->vtable._5_OFF.methodPtr)(ParallelBlur, ParallelBlur->klass->vtable._5_OFF.method);
  return 1;
}

// 0x2157eb0: s32 FILTER_ALLOFF(void)
static inline s32 FILTER_ALLOFF(void) {
  _Off(Filter2, 0);
  _Off(MFilter, 0);
  dds3FilterSetAnime(0);
  gFilterAlpha = 128;
  gFilterFilterAlpOfs = 0;
  dds3FilterSet(0, 1, 0);
  return 1;
}

// 0x2158030: s32 ENABLE_MOVIESKIP(void)
static inline s32 ENABLE_MOVIESKIP(void) {
  GBWK->IntVariable[210] = 0;
  return 1;
}

// 0x21580a0: s32 DISABLE_MOVIESKIP(void)
static inline s32 DISABLE_MOVIESKIP(void) {
  GBWK->IntVariable[210] = 1;
  return 1;
}

// 0x21582b0: s32 SET_AFTERSKIP_BGMFLAG(void)
static inline s32 SET_AFTERSKIP_BGMFLAG(void) {
  GBWK->afterSkipPlayBgm = 1;
  return 1;
}

// 0x21583b0: s32 DRAW_NEWEFFECT(void)
static inline s32 DRAW_NEWEFFECT(void) {
  char *v1;
  Il2CppObject *StrPara;
  char *v3;
  void *v5;
  void *transform;
  Il2CppObject *v10;

  v1 = "neweffect";
  StrPara = scrGetStrPara(0);
  if (scrGetStrPara(1))
  {
    v3 = scrGetStrPara(1);
    if (op_Inequality(v3, "", 0))
    {
      v1 = scrGetStrPara(1);
    }
  }
  if (object___ContainsKey(newEffects, StrPara))
  {
    v5 = 0;
    goto LABEL_21;
  }
  v5 = fldNewEffectLoad(v1, StrPara);
LABEL_21:
  if (op_Equality(v5, 0, 0))
    return 1;
  transform = get_transform(hook, 0);
  v10 = Instantiate_object__39504352(v5, transform);
  object___set_Item(newEffects, StrPara, v10);
  return 1;
}

// 0x2158650: s32 SET_NEWEFF_POS(void)
static inline s32 SET_NEWEFF_POS(void) {
  f32 z;
  f32 x;
  f32 y;
  char *StrPara;
  s32 IntPara;
  Il2CppObject *Item;
  void *transform;
  sdfVector3_t v14;

  z = zeroVector.z;
  x = zeroVector.x;
  y = zeroVector.y;
  StrPara = scrGetStrPara(0);
  IntPara = scrGetIntPara(1);
  if (IntPara != 1)
  {
    if (!IntPara)
    {
      x = fldGb[43] / -100.0;
      z = fldGb[45] / -100.0;
      y = fldGb[44] / 100.0;
    }
    if (!op_Inequality(StrPara, "", 0))
      return 1;
LABEL_17:
    if (object___ContainsKey(newEffects, StrPara))
    {
      Item = object___get_Item(newEffects, StrPara);
      transform = get_transform(Item, 0);
      v14.x = x;
      v14.y = y;
      v14.z = z;
      set_position(transform, v14, 0);
    }
    return 1;
  }
  x = scrGetFloatPara(2);
  y = scrGetFloatPara(3);
  z = scrGetFloatPara(4);
  if (op_Inequality(StrPara, "", 0))
    goto LABEL_17;
  return 1;
}

// 0x2158890: s32 SET_NEWEFF_ROT(void)
static inline s32 SET_NEWEFF_ROT(void) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  Il2CppObject *StrPara;
  s32 IntPara;
  f32 PlayerKakudo;
  f32 FloatPara;
  f32 v11;
  f32 v12;
  Il2CppObject *Item;
  void *transform;
  f32 v18;
  Il2CppObject *v19;
  void *v20;
  f32 v21;
  s64 v22;
  f32 *cam_xzy;
  f32 v24;
  f32 v25;
  f32 v27;
  f32 v28;
  f32 *p_x;
  long f64 v31;
  f32 *v33;
  f32 v34;
  f32 v35;
  f32 v36;
  Il2CppObject *v37;
  void *v38;
  f32 v39;
  f32 v40;
  f32 v41;
  Il2CppObject *v43;
  void *v44;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  sdfVector3_t position;
  sdfQuaternion_t v51;
  sdfQuaternion_t v52;
  sdfVector3_t v53;
  sdfVector3_t v54;
  sdfQuaternion_t v55;

  x = identityQuaternion.x;
  y = identityQuaternion.y;
  z = identityQuaternion.z;
  w = identityQuaternion.w;
  StrPara = scrGetStrPara(0);
  IntPara = scrGetIntPara(1);
  if (op_Inequality(StrPara, "", 0))
  {
    if (!object___ContainsKey(newEffects, StrPara))
      return 1;
    switch (IntPara)
    {
      case 0:
        PlayerKakudo = fldGb->PlayerKakudo;
        goto LABEL_37;
      case 1:
        FloatPara = scrGetFloatPara(2);
        v11 = scrGetFloatPara(3);
        v12 = scrGetFloatPara(4);
        v53.y = v11 * 0.017453292;
        v53.z = v12 * 0.017453292;
        v53.x = FloatPara * 0.017453292;
        goto LABEL_38;
      case 2:
        Item = object___get_Item(newEffects, StrPara);
        transform = get_transform(Item, 0);
        v18 = get_position(transform, 0).x;
        v19 = object___get_Item(newEffects, StrPara);
        v20 = get_transform(v19, 0);
        v21 = get_position(v20, 0).z;
        cam_xzy = GetFldCutTable(CutDataTbl, fldGb->fieldID, fldGb->cut_idx, 0)->_cam_xzy;
        v25 = cam_xzy[0];
        v24 = cam_xzy[1];
        v27 = -v25;
        v28 = -v24;
        vct_A.x = v27;
        vct_A.y = 0.0;
        vct_A.z = v28;
        vct_A.w = 1.0;
        p_x = &vf00.x;
        p_x[8] = v18;
        p_x[9] = 0.0;
        p_x[10] = v21;
        p_x[11] = 1.0;
        vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
        v31 = sub_18E6660(0, v22);
        PlayerKakudo = *(f32 *)&v31 * 57.29578;
LABEL_37:
        v53.z = 0.0;
        v53.y = PlayerKakudo * 0.017453292;
        v53.x = 0.0;
LABEL_38:
        v51 = Internal_FromEulerRad(v53, 0);
        v46 = v51.x;
        v47 = v51.y;
        v48 = v51.z;
        v49 = v51.w;
LABEL_44:
        x = v46;
        y = v47;
        z = v48;
        w = v49;
LABEL_45:
        v43 = object___get_Item(newEffects, StrPara);
        v44 = get_transform(v43, 0);
        v55.x = x;
        v55.y = y;
        v55.z = z;
        v55.w = w;
        set_rotation(v44, v55, 0);
        break;
      case 3:
        v33 = GetFldCutTable(CutDataTbl, fldGb->fieldID, fldGb->cut_idx, 0)->_cam_xzy;
        v34 = v33[2];
        v35 = -v33[0];
        v36 = -v33[1];
        v37 = object___get_Item(newEffects, StrPara);
        v38 = get_transform(v37, 0);
        position = get_position(v38, 0);
        v39 = v35 - position.x;
        v40 = v34 - position.y;
        v41 = v36 - position.z;
        v54.x = v39;
        v54.y = v40;
        v54.z = v41;
        v52 = LookRotation(v54, upVector, 0);
        v46 = v52.x;
        v47 = v52.y;
        v48 = v52.z;
        v49 = v52.w;
        goto LABEL_44;
      default:
        goto LABEL_45;
    }
  }
  return 1;
}

// 0x2158e10: s32 DELETE_NEWEFFECT(void)
static inline s32 DELETE_NEWEFFECT(void) {
  Il2CppObject *StrPara;
  Il2CppObject *Item;

  StrPara = scrGetStrPara(0);
  if (!object___ContainsKey(newEffects, StrPara))
    return 1;
  Item = object___get_Item(newEffects, StrPara);
  Destroy_61007920(Item, 0);
  object___Remove(newEffects, StrPara);
  return 1;
}

// 0x2158fb0: s32 NO_SKIP_WAIT(void)
static inline s32 NO_SKIP_WAIT(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  noSkipWait = IntPara != 0;
  return 1;
}

// 0x2159050: s32 ITEM_PLUS(void)
static inline s32 ITEM_PLUS(void) {
  s32 IntPara;
  s32 v2;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  datAddItem(IntPara, v2);
  return 1;
}

// 0x2159100: s32 ITEM_CHECK(void)
static inline s32 ITEM_CHECK(void) {
  s32 IntPara;
  s32 v2;
  bool v3;

  IntPara = scrGetIntPara(0);
  v2 = scrGetIntPara(1);
  v3 = datCheckItem(IntPara, v2);
  scrSetIntReturnValue(v3);
  return 1;
}

// 0x21591d0: s32 ITEM_CHK_KICHOU(void)
static inline s32 ITEM_CHK_KICHOU(void) {
  s32 IntPara;
  bool v2;

  IntPara = scrGetIntPara(0);
  v2 = datCheckEventItem(IntPara);
  scrSetIntReturnValue(v2);
  return 1;
}

// 0x2159290: s32 MAG_PLUS(void)
static inline s32 MAG_PLUS(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  datAddMag(IntPara);
  return 1;
}

// 0x2159330: s32 MAG_CHECK(void)
static inline s32 MAG_CHECK(void) {
  s32 IntPara;
  bool v2;

  IntPara = scrGetIntPara(0);
  v2 = datCheckMag(IntPara);
  scrSetIntReturnValue(v2);
  return 1;
}

// 0x21593f0: s32 MONEY_PLUS(void)
static inline s32 MONEY_PLUS(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  datAddMoney(IntPara);
  return 1;
}

// 0x2159490: s32 MONEY_CHECK(void)
static inline s32 MONEY_CHECK(void) {
  s32 IntPara;
  bool v2;

  IntPara = scrGetIntPara(0);
  v2 = datCheckMoney(IntPara);
  scrSetIntReturnValue(v2);
  return 1;
}

// 0x2159550: s32 MONEY_HAVE(void)
static inline s32 MONEY_HAVE(void) {
  s32 gold;

  gold = GBWK->player->gold;
  scrSetIntReturnValue(gold);
  return 1;
}

// 0x21595f0: s32 PARTY_RECOVERY(void)
static inline s32 PARTY_RECOVERY(void) {
  datPartyRecovery();
  return 1;
}

// 0x215aa90: s32 EXEC_TAKUMI(void)
static inline s32 EXEC_TAKUMI(void) {
  s32 IntPara;
  s32 StockDevilIndex;
  s32 Type;
  s32 v6;
  TakumiInfo_t *s_ExecTakumi_info_local;
  sdatUnitWork_t *v11;

  IntPara = scrGetIntPara(0);
  StockDevilIndex = datGetStockDevilIndex(GBWK->mapSummonID, GBWK->mapSummonUNIQ);
  if ((StockDevilIndex & 0x80000000) == 0)
  {
    switch (IntPara)
    {
      case 1:
        Type = s_ExecTakumi_info->Ret->Type;
        break;
      case 2:
        Type = s_ExecTakumi_info->Ret->Target;
        break;
      case 3:
        Type = s_ExecTakumi_info->Ret->ItemID;
        break;
      case 4:
        Type = s_ExecTakumi_info->Ret->ItemID2;
        break;
      default:
        v6 = StockDevilIndex;
        s_ExecTakumi_info_local = s_ExecTakumi_info;
        v11 = GBWK->player->stock_id[v6];
        s_ExecTakumi_info_local->pUnit = v11;
        Type = ExecTakumi(s_ExecTakumi_info);
        break;
    }
    goto LABEL_33;
  }
  Type = 0;
LABEL_33:
  scrSetIntReturnValue(Type);
  return 1;
}

// 0x215b1b0: s32 EXEC_TEISATU_ITEM(void)
static inline s32 EXEC_TEISATU_ITEM(void) {
  s32 IntPara;
  u32 StockDevilIndex;
  sdatUnitWork_t *v6;
  s32 v7;

  IntPara = scrGetIntPara(0);
  StockDevilIndex = datGetStockDevilIndex(GBWK->mapSummonID, 0);
  if (!IntPara)
  {
    if (GBWK->Moon->TeisatuCnt)
      goto LABEL_29;
  }
  if ((StockDevilIndex & 0x80000000) != 0)
  {
LABEL_29:
    scrSetIntReturnValue(0);
    return 1;
  }
  else
  {
    v6 = GBWK->player->stock_id[StockDevilIndex];
    v7 = ExecTeisatuItem(IntPara, v6);
    scrSetIntReturnValue(v7);
    if (!IntPara && v7)
    {
      evtMoonTeisatuCntReset();
    }
    return 1;
  }
}

// 0x215b370: s32 PARTY_DAMAGE(void)
static inline s32 PARTY_DAMAGE(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  datPartyDamageMap(IntPara);
  return 1;
}

// 0x215b410: s32 PLAYER_GET_PARAM(void)
static inline s32 PLAYER_GET_PARAM(void) {
  s32 IntPara;
  s32 PlayerParam;

  IntPara = scrGetIntPara(0);
  PlayerParam = datGetPlayerParam(IntPara);
  scrSetIntReturnValue(PlayerParam);
  return 1;
}

// 0x215b4b0: s32 MASTER_SPIRITSKILl(void)
static inline s32 MASTER_SPIRITSKILl(void) {
  sdatPlayerUnitWork_t *player;
  s32 IntPara;
  s32 v7;

  player = GBWK->player;
  IntPara = scrGetIntPara(0);
  if (!player)
    return 1;
  v7 = IntPara;
  if (datSpiritSkillHaveSkill(player, IntPara))
    return 1;
  SpiritSkillSetMaster(player, v7, 1, 0);
  return 1;
}

// 0x21525d0
s32 mphCommand_BUSTUP_LOAD(void) {
  return 1;
}

// 0x21525e0
s32 mphCommand_BUSTUP_LOAD_WAIT(void) {
  return 1;
}

// 0x21525f0
s32 mphCommand_BUSTUP_ON(void) {
  return 1;
}

// 0x2152600
s32 mphCommand_BUSTUP_OFF(void) {
  return 1;
}

// 0x2152610
s32 datCommand_CLEAR_STOCK(void) {
  return 1;
}

// 0x2152620
s32 datCommand_PLAYER_LUCK_STEP(void) {
  return 1;
}

// 0x2152630
s32 datCommand_GET_BATTLE_RESULT(void) {
  return 1;
}

// 0x2152640
s32 nimCommand_NIM_INPUT(void) {
  return 1;
}

// 0x2152650
s32 nimCommand_NIM_CHECK(void) {
  return 1;
}

// 0x2152660
s32 datCommand_PLAYER_LUCK_SET(void) {
  return 1;
}

// 0x2152670
s32 cmpCommand_INIT_LUCKPOINT(void) {
  return 1;
}

// 0x2152680
s32 cmpCommand_UPDATE_LUCKPOINT(void) {
  return 1;
}

// 0x2152690
s32 datCommand_CHECK_DEVIL_ID(void) {
  return 1;
}

// 0x21526a0
s32 itfMesMngSelect_NEW_SEL(void) {
  return 1;
}

// 0x21526b0
s32 itfInitRegistMessage(void) {
  return 1;
}

// 0x21526c0
s32 itfRegistMessage(void) {
  return 1;
}

// 0x21526d0
s32 itfDispRegistMessage(void) {
  return 1;
}

// 0x21526e0
s32 nmeScrCmd_GET_DREAM_COMPARE(void) {
  return 1;
}

// 0x21526f0
static u32 IntParaToRGBA(s32 offset) {
  u8 IntPara;
  u8 v4;
  u8 v5;

  IntPara = scrGetIntPara(offset);
  v4 = scrGetIntPara(offset + 1);
  v5 = scrGetIntPara(offset + 2);
  return IntPara | (u16)(v4 << 8) | (v5 << 16) | (scrGetIntPara(offset + 3) << 24);
}

// 0x2154350
void scrFldObjOutReset(void) {
  *(u16 *)&is_moon = 0;
  return;
}

// 0x2153aa0
static void FldObjOut(void) {
  _BOOL4 Draw;
  void *Instance;
  void *v7;
  void *v8;
  void *v9;

  Draw = evtMoonGetDraw();
  is_moon = Draw;
  if (!Draw)
  {
    goto LABEL_6;
  }
  evtMoonDisableDraw(0);
LABEL_6:
  if (!sbattleIsBattle())
    goto LABEL_32;
  Instance = get_Instance(0);
  if (!op_Inequality(Instance, 0, 0))
    goto LABEL_32;
  v7 = get_Instance(0);
  CharaIconActive(v7, 0, 0);
  v8 = get_Instance(0);
  AllInOut(v8, 0, 1, 1, 1, 0);
  v9 = get_Instance(0);
  DevilHPactive(v9, 0, 0);
  if (!IsStart())
  {
    battle_key_wait = 120;
    goto LABEL_32;
  }
LABEL_32:
  out_flg = 1;
}

// 0x21536d0
static void FldObjIn(void) {
  void *Instance;
  void *v6;
  void *v7;
  void *v8;

  if (!out_flg)
    goto LABEL_23;
  if (is_moon)
  {
    evtMoonEnableDraw();
  }
  is_moon = 0;
  goto LABEL_15;
LABEL_19:
  Instance = get_Instance(0);
  if (!op_Inequality(Instance, 0, 0))
    goto LABEL_23;
  v6 = get_Instance(0);
  CharaIconActive(v6, 1, 0);
  v7 = get_Instance(0);
  AllInOut(v7, 1, 1, 1, 1, 0);
  v8 = get_Instance(0);
  DevilHPactive(v8, 1, 0);
  goto LABEL_24;
LABEL_15:
  if (sbattleIsBattle())
    goto LABEL_19;
LABEL_23:
LABEL_24:
  *(u16 *)&is_moon = 0;
  return;
}

// 0x21543d0
bool scrIsMoonOut(void) {
  return out_flg;
}

// 0x2158110
void scrSetMovieCancel(s32 Mode) {
  s32 v5;

  if (!Mode)
  {
    v5 = 1;
    goto LABEL_8;
  }
  v5 = 0;
LABEL_8:
  GBWK->IntVariable[210] = v5;
}

// 0x2158240
bool scrCheckEnableMovieCancel(void) {
  return GBWK->IntVariable[210] == 0;
}

// 0x2158320
s32 scrGetAfterSkipBgmFlag(void) {
  return GBWK->afterSkipPlayBgm;
}

// 0x2159670
static s32 TakumiGetTarget(s32 type) {
  s32 *v3;
  u32 *v;
  u32 v7;
  s32 v8;
  u32 v9;
  s32 v10;
  s32 v11;
  s64 v12;
  s32 v13;
  s64 v15;
  u32 *v18;
  u32 v19;
  s32 v20;
  u32 v21;
  s32 v22;
  u32 v23;

  v3 = NewSpecific(s32, 0x20u);
  v = sdfDefaultRandCB->v;
  v7 = v[0];
  v8 = *(u64 *)v >> 30;
  v9 = v[2];
  v10 = *(u64 *)&v[2] >> 31;
  v[2] = v[1];
  v[3] = v9;
  v11 = v10 ^ v8;
  v[0] = v11;
  v[1] = v7;
  if (v11 & 1 | type)
  {
    v12 = 0;
    v13 = 0;
    while (1)
    {
      if (v12 >= datGetStockDevilNums(0))
        break;
      if (GBWK->player->stock_id[v12]->now->hp >= 1)
      {
        v15 = (s64)(char *)v3 + 4 * v13++;
        *(u32 *)(v15 + 32) = v12;
      }
      ++v12;
    }
    if (v13 >= 1)
    {
      v18 = sdfDefaultRandCB->v;
      v19 = v18[0];
      v20 = *(u64 *)v18 >> 30;
      v21 = v18[2];
      v22 = *(u64 *)&v18[2] >> 31;
      v18[2] = v18[1];
      v18[3] = v21;
      v23 = v22 ^ v20;
      v18[0] = v23;
      v18[1] = v19;
      return *(u32 *)((s64)(char *)v3 + 4 * (v23 % v13) + 32);
    }
  }
  return -1;
}

// 0x2159920
static s32 TakumiKoukaA(TakumiInfo_t *pInfo) {
  u32 Target;
  sdatParaWork_t *now;
  TakumiInfoRet_t *Ret;
  TakumiInfoRet_t *v11;
  sdatPlayerUnitWork_t *player;

  Target = TakumiGetTarget(0);
  if ((Target & 0x80000000) == 0)
  {
    now = GBWK->player->stock_id[Target]->now;
    now->hp = now->maxhp;
    Ret = pInfo->Ret;
    Ret->Type = 0;
    Ret->Target = datGetStockDevilID(Target);
    return Target;
  }
  v11 = pInfo->Ret;
  player = GBWK->player;
  v11->Type = 0;
  player->para->now->hp = player->para->now->maxhp;
  v11->Target = 241;
  return Target;
}

// 0x2159a80
static s32 TakumiKoukaB(TakumiInfo_t *pInfo) {
  s32 Target;
  sdatParaWork_t *now;
  s32 maxhp;
  s32 v8;
  s32 v9;
  TakumiInfoRet_t *Ret;

  Target = TakumiGetTarget(1);
  now = GBWK->player->stock_id[Target]->now;
  maxhp = now->maxhp;
  if (maxhp >= 0)
    v8 = now->maxhp;
  else
    v8 = maxhp + 1;
  v9 = now->hp + (v8 >> 1);
  now->hp = v9;
  if (v9 > maxhp)
  {
    now = GBWK->player->stock_id[Target]->now;
    maxhp = now->maxhp;
    now->hp = maxhp;
  }
  Ret = pInfo->Ret;
  Ret->Type = 1;
  if (Target < 0)
  {
    Ret->Target = 241;
    return Target;
  }
  else
  {
    Ret->Target = datGetStockDevilID(Target);
    return Target;
  }
}

// 0x2159c00
static s32 TakumiKoukaC(TakumiInfo_t *pInfo) {
  s32 Target;
  sdatParaWork_t *now;
  s32 maxmp;
  s32 v8;
  TakumiInfoRet_t *Ret;

  Target = TakumiGetTarget(1);
  now = GBWK->player->stock_id[Target]->now;
  maxmp = now->maxmp;
  v8 = now->mp + maxmp / 4;
  now->mp = v8;
  if (v8 > maxmp)
  {
    now = GBWK->player->stock_id[Target]->now;
    maxmp = now->maxmp;
    now->mp = maxmp;
  }
  Ret = pInfo->Ret;
  Ret->Type = 2;
  if (Target < 0)
  {
    Ret->Target = 241;
    return Target;
  }
  else
  {
    Ret->Target = datGetStockDevilID(Target);
    return Target;
  }
}

// 0x2159d90
static s32 TakumiKoukaD(TakumiInfo_t *pInfo) {
  s32 *v3;
  u32 Target;
  u32 *v;
  u32 v11;
  u32 v12;
  u32 v13;
  s32 v14;
  s64 v15;
  s32 v16;
  s64 p_para;
  sdatUnitWork_t *v20;
  s64 v21;
  s32 v22;
  s32 v23;
  sdatParaWork_t *now;
  TakumiInfoRet_t *Ret;
  s32 StockDevilID;
  TakumiInfoRet_t *v28;

  v3 = NewSpecific(s32, 4u);
  InitializeArray_55364416(v3, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__C2422A2158E69A6A7B3C68419CA0EEE605C77AED45F1138BD8B3182449197136, 0);
  Target = TakumiGetTarget(0);
  v = sdfDefaultRandCB->v;
  v11 = v[0];
  v12 = *(u64 *)v >> 30;
  v13 = v[2];
  v14 = *(u64 *)&v[2] >> 31;
  v[2] = v[1];
  v[3] = v13;
  v15 = v14 ^ v12;
  v[0] = v15;
  v[1] = v11;
  v16 = *(u32 *)((s64)(char *)v3 + 4 * (v15 % *(s32 *)((char *)v3 + 24)) + 32);
  if ((Target & 0x80000000) != 0)
  {
    p_para = &GBWK->player->para;
  }
  else
  {
    p_para = &GBWK->player->stock_id[Target];
  }
  v20 = *(sdatUnitWork_t *)p_para;
  v21 = *(u64 *)(*(u64 *)p_para + 40);
  v22 = *(u32 *)(v21 + 16);
  v23 = *(u32 *)(v21 + 24);
  sdatCalcItem(v20, v16);
  datCalcNowParam(v20, GBWK->player->swordno, 0);
  datDvlParaUpdate(0);
  now = v20->now;
  now->hp = v22;
  now->mp = v23;
  Ret = pInfo->Ret;
  Ret->Type = 3;
  if ((Target & 0x80000000) != 0)
  {
    StockDevilID = 241;
    v28 = Ret;
  }
  else
  {
    StockDevilID = datGetStockDevilID(Target);
    v28 = pInfo->Ret;
  }
  Ret->Target = StockDevilID;
  v28->ItemID = v16;
  return Target;
}

// 0x215a0a0
static s32 TakumiKoukaE(TakumiInfo_t *pInfo) {
  datAddMag(GBWK->player->maxmag / 2);
  pInfo->Ret->Type = 4;
  return 0;
}

// 0x215a140
static s32 TakumiKoukaF(TakumiInfo_t *pInfo) {
  datAddMag(300);
  pInfo->Ret->Type = 5;
  return 0;
}

// 0x215a1c0
static s32 TakumiKoukaG(TakumiInfo_t *pInfo) {
  f32 *v3;
  il2cpp_array_size_t max_length;
  s64 v6;
  s64 v7;
  s64 v8;
  s32 v9;
  s64 v10;
  s32 SrcItem;
  s64 v13;
  u32 *v;
  u32 v19;
  u32 v20;
  u32 v21;
  s32 v22;
  s64 v23;
  s64 v24;
  void *v25;
  s32 v26;
  s32 luck;
  s32 v29;
  u32 *v34;
  u32 v35;
  u32 v36;
  u32 v37;
  s32 v38;
  s64 v39;
  f32 v40;
  f32 v41;
  TakumiInfo_t *v46;
  u32 *v47;
  u32 v48;
  s32 v49;
  u32 v50;
  s32 v51;
  u32 v52;
  void *v53;
  void *v54;
  s32 DstItem2;
  TakumiInfoRet_t *Ret;
  TakumiInfo_t *v59;

  v3 = NewSpecific(f32, 8u);
  InitializeArray_55364416(v3, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__58ED0B706F2EC6F4897ACBA11E15459119ED5BC63B80BB73C4B0E8F1DF98362E, 0);
  max_length = item_takumi_table->max_length;
  v6 = NewSpecific(s32, max_length);
  if ((s32)max_length < 1)
    return -2;
  v7 = v6;
  v8 = 0;
  v9 = 0;
  v10 = (u32)max_length;
  do
  {
    SrcItem = item_takumi_table[v8]->SrcItem;
    if (!!datCheckItem(SrcItem, 1))
    {
      v13 = v7 + 4 * v9++;
      *(u32 *)(v13 + 32) = v8;
    }
    ++v8;
  }
  while (v10 != v8);
  if (!v9)
    return -2;
  v59 = pInfo;
  goto LABEL_18;
LABEL_19:
  goto LABEL_20;
LABEL_18:
  goto LABEL_19;
LABEL_20:
  v = sdfDefaultRandCB->v;
  v19 = v[0];
  v20 = v[2];
  v21 = *(u64 *)v >> 30;
  v22 = *(u64 *)&v[2] >> 31;
  v[2] = v[1];
  v[3] = v20;
  v23 = v22 ^ v21;
  v[0] = v23;
  v[1] = v19;
  v24 = *(s32 *)(v7 + 4 * (v23 % v9) + 32);
  v25 = item_takumi_table[v24];
  v26 = v25->SrcItem;
  if (v25->DstItem2)
  {
    luck = GBWK->player->para->now->luck;
    v29 = v59->pUnit->now->luck;
    goto LABEL_27;
LABEL_28:
    goto LABEL_29;
LABEL_27:
    goto LABEL_28;
LABEL_29:
    v34 = sdfDefaultRandCB->v;
    v35 = v34[0];
    v36 = v34[2];
    v37 = *(u64 *)v34 >> 30;
    v38 = *(u64 *)&v34[2] >> 31;
    v34[2] = v34[1];
    v34[3] = v36;
    v39 = v38 ^ v37;
    v34[0] = v39;
    v34[1] = v35;
    v40 = *(f32 *)((s64)(char *)v3 + 4 * (v39 % *(s32 *)((char *)v3 + 24)) + 32);
    v41 = v40 * (f32)(v29 + luck);
    if (v41 == INFINITY || (s32)v41 < item_takumi_table[v24]->Luck)
      goto LABEL_71;
    goto LABEL_37;
LABEL_38:
    goto LABEL_39;
LABEL_37:
    goto LABEL_38;
LABEL_39:
    v46 = v59;
    v47 = sdfDefaultRandCB->v;
    v48 = v47[0];
    v49 = *(u64 *)v47 >> 30;
    v50 = v47[2];
    v51 = *(u64 *)&v47[2] >> 31;
    v47[2] = v47[1];
    v47[3] = v50;
    v52 = v51 ^ v49;
    v47[0] = v51 ^ v49;
    v47[1] = v48;
    v53 = item_takumi_table[v24];
    if ((s32)(v52 % 0x64) < v53->Rate)
    {
LABEL_71:
      v46 = v59;
      v54 = item_takumi_table[v24];
      DstItem2 = v54->DstItem2;
    }
    else
    {
      v53 = item_takumi_table[v24];
      DstItem2 = v53->DstItem1;
    }
  }
  {
    v46 = v59;
    DstItem2 = v25->DstItem1;
  }
  else
  {
    v46 = v59;
    DstItem2 = item_takumi_table[v24]->DstItem1;
  }
  datAddItem(v26, -1);
  datAddItem(DstItem2, 1);
  Ret = v46->Ret;
  Ret->Type = 6;
  Ret->ItemID = v26;
  Ret->ItemID2 = DstItem2;
  return 0;
}

// 0x215a7d0
static s32 ExecTakumi(TakumiInfo_t *pInfo) {
  s64 v6;
  s32 v7;
  u32 *v;
  u32 v10;
  s32 v11;
  u32 v12;
  s32 v13;
  s32 v14;
  s32 v15;
  char *v16;
  s64 v20;
  s64 v22;
  TakumiInfo_t *v23;

  v23 = pInfo;
  Clear(pInfo->Ret);
  v6 = 0;
  v7 = 0;
  v = sdfDefaultRandCB->v;
  v10 = v[0];
  v11 = *(u64 *)v >> 30;
  v12 = v[2];
  v13 = *(u64 *)&v[2] >> 31;
  v[2] = v[1];
  v[3] = v12;
  v14 = v13 ^ v11;
  v15 = v14 & 0x7F;
  v[0] = v14;
  v[1] = v10;
  do
  {
    if (v6 >= SLODWORD(rate_table->max_length))
      return 0;
    v16 = (char *)rate_table + 4 * v6++;
    v7 += *((u32 *)v16 + 8);
  }
  while (v15 >= v7);
  v20 = *(u64 *)(*(&func->max_length + v6) + 32);
  if ((*(v20 + 24))(*(u64 *)(v20 + 64), &v23, *(u64 *)(v20 + 40)) != -2)
    return 1;
  if (*(u64 *)(*(&func->max_length + v6) + 40))
  {
    Clear(v23->Ret);
    v22 = *(u64 *)(*(&func->max_length + v6) + 40);
    (*(v22 + 24))(*(u64 *)(v22 + 64), &v23, *(u64 *)(v22 + 40));
    return 1;
  }
  return 1;
}

// 0x215ad20
static s32 ExecTeisatuItem(s32 mode, sdatUnitWork_t *pUnit) {
  s64 v10;
  Il2CppClass **v11;
  Il2CppClass *v12;
  RateTable_t *rate_teisatu_table_local;
  s32 chuusei;
  u32 v15;
  u32 *v;
  u32 v19;
  s32 v20;
  u32 v21;
  s32 v22;
  u32 v23;
  s64 v25;
  s32 i;
  Il2CppClass **v27;
  ItemTable_t *item_teisatu_table_local;
  s64 v32;
  s32 v33;
  u32 *v35;
  u32 v36;
  u32 v37;
  u32 v38;
  s32 v39;
  s64 v40;
  s32 v41;
  Il2CppClass **v42;
  Il2CppClass *v43;
  ItemTable_t *v45;
  s32 name;
  s32 v48;

  if (mode == 1)
  {
    return s_ret_info->ItemID;
  }
  else if (mode == 2)
  {
    return s_ret_info->Nums;
  }
  else
  {
    Clear(s_ret_info);
    v10 = 0;
    while (1)
    {
      rate_teisatu_table_local = rate_teisatu_table;
      if (v10 >= SLODWORD(rate_teisatu_table_local->max_length))
        return 0;
      chuusei = pUnit->chuusei;
      rate_teisatu_table_local = rate_teisatu_table;
      v11 = &rate_teisatu_table_local->obj.klass + v10++;
      v12 = v11[4];
      if (chuusei <= LOBYTE(v12->_1.name))
      {
        v15 = BYTE1(v12->_1.name);
        if (!BYTE1(v12->_1.name))
          return 0;
        goto LABEL_26;
LABEL_27:
        goto LABEL_28;
LABEL_26:
        goto LABEL_27;
LABEL_28:
        v = sdfDefaultRandCB->v;
        v19 = v[0];
        v20 = *(u64 *)v >> 30;
        v21 = v[2];
        v22 = *(u64 *)&v[2] >> 31;
        v[2] = v[1];
        v[3] = v21;
        v23 = v22 ^ v20;
        v[0] = v23;
        v[1] = v19;
        if (v23 % v15)
          return 0;
        v25 = 0;
        for (i = 0; ; i += BYTE5(v27[4]->_1.name))
        {
          item_teisatu_table_local = item_teisatu_table;
          if (v25 >= SLODWORD(item_teisatu_table_local->max_length))
            break;
          item_teisatu_table_local = item_teisatu_table;
          v27 = &item_teisatu_table_local->obj.klass + v25++;
        }
        goto LABEL_43;
LABEL_44:
        goto LABEL_9000;
LABEL_43:
        goto LABEL_44;
LABEL_9000:
        v32 = 0;
        v33 = 0;
        v35 = sdfDefaultRandCB->v;
        v36 = v35[0];
        v37 = *(u64 *)v35 >> 30;
        v38 = v35[2];
        v39 = *(u64 *)&v35[2] >> 31;
        v35[2] = v35[1];
        v35[3] = v38;
        v40 = v39 ^ v37;
        v35[0] = v40;
        v35[1] = v36;
        v41 = v40 % i;
        while (1)
        {
          v45 = item_teisatu_table;
          if (v32 >= SLODWORD(v45->max_length))
            break;
          v45 = item_teisatu_table;
          v42 = &v45->obj.klass + v32++;
          v43 = v42[4];
          v33 += BYTE5(v43->_1.name);
          if (v33 > v41)
          {
            v43 = *(&item_teisatu_table->max_length + v32);
            name = v43->_1.name;
            s_ret_info->ItemID = name;
            v48 = BYTE4(v43->_1.name);
            s_ret_info->Nums = v48;
            datAddItem(name, v48);
            return 1;
          }
        }
        return 0;
      }
    }
  }
}
