#include "types.h"
#include "CMP_SPR.h"
#include "cmpfile.h"

typedef struct sprHandle_t sprHandle_t;

typedef bool (*cmpMotFunc_t)(void);

static cmpMotFunc_t *cmpResetMotFunc[2];
static cmpMotFunc_t *cmpLinkMotFunc;
sprHandle_t *g_hSpr;
static s32 *g_nCallLoadHnd;
static char *strCmpSpriteName;
static s32 *arrSprToMot;

// 0x1e598a0
bool cmpLinkMotMoya(void) {
  return g_hSpr[0] != 0;
}

// 0x1e59910
bool cmpLinkMotSakura(void) {
  return g_hSpr[2] != 0;
}

// 0x1e59980
bool cmpLinkMotion(CMP_SPR a_sprFileNo) {
  s64 v5;
  cmpMotFunc_t v6;

  if ((u32)a_sprFileNo > 4)
    return 0;
  v5 = (u32)arrSprToMot[a_sprFileNo];
  if ((v5 & 0x80000000) != 0)
    return 0;
  v6 = cmpLinkMotFunc[v5];
  return (v6->invoke_impl)(v6->method_code, v6->method);
}

// 0x1e59a50
bool _FreeMotion(s32 a_motNo) {
  return 0;
}

// 0x1e59a60
bool cmpFreeMotion(CMP_SPR a_sprFileNo) {
  if ((u32)a_sprFileNo > 4)
    return 0;
    return 0;
}

// 0x1e59b00
bool _ResetMotion(CMP_SPR a_sprFileNo, s32 a_sprNo) {
  return (u32)a_sprFileNo < 5 && a_sprNo >= 0;
}

// 0x1e59b10
bool cmpResetMotMoya(void) {
  return 1;
}

// 0x1e59b80
bool cmpResetMotSakura(void) {
  return 1;
}

// 0x1e59bf0
bool cmpResetMotion(s32 a_motNo) {
  cmpMotFunc_t v4;

  if ((u32)a_motNo > 1)
    return 0;
  v4 = cmpResetMotFunc[a_motNo];
  return (v4->invoke_impl)(v4->method_code, v4->method);
}

// 0x1e59c90
bool cmpFreeSpriteMem(CMP_SPR a_no) {
  return 0;
}

// 0x1e59ca0
bool cmpLoadSpriteMem(CMP_SPR a_no) {
  return (u32)a_no < 5;
}

// 0x1e59cb0
bool cmpFreeSpriteHnd(CMP_SPR a_no) {
  char *v7;
  s32 v8;
  bool v9;

  if ((u32)a_no > 4)
    return 0;
  if (!g_hSpr[a_no])
  {
    g_nCallLoadHnd[a_no] = 0;
    return 0;
  }
  v7 = (char *)g_nCallLoadHnd + 4 * (u32)a_no;
  v8 = *((u32 *)v7 + 8) - 1;
  v9 = *((u32 *)v7 + 8) == 1;
  *((u32 *)v7 + 8) = v8;
  if (v8 >= 0 && !v9)
    return 0;
  g_nCallLoadHnd[a_no] = 0;
  if (arrSprToMot[a_no] < 0)
    return 1;
  return 1;
}

// 0x1e59e60
bool cmpLoadSpriteHnd(CMP_SPR a_no) {
  s64 v5;
  s32 *g_nCallLoadHnd_local;
  s64 v9;
  cmpMotFunc_t v10;

  if ((u32)a_no > 4)
    return 0;
  v5 = a_no;
  if (!g_hSpr[a_no])
  {
LABEL_15:
    g_nCallLoadHnd[v5] = 1;
    v9 = (u32)arrSprToMot[v5];
    if ((v9 & 0x80000000) == 0)
    {
      v10 = cmpLinkMotFunc[v9];
      (v10->invoke_impl)(v10->method_code, v10->method);
      return 1;
    }
    return 1;
  }
  g_nCallLoadHnd_local = g_nCallLoadHnd;
  if (!g_nCallLoadHnd_local[v5])
    goto LABEL_15;
  g_nCallLoadHnd_local = g_nCallLoadHnd;
  ++g_nCallLoadHnd_local[v5];
  return 0;
}

// 0x1e5a050
bool cmpLoadSpriteToMem(void) {
  return 1;
}

// 0x1e5a100
void cmpFreeSpriteToMem(void) {

}

// 0x1e5a1a0
void cmpFreeSpriteToGS(void) {
  cmpFreeSpriteHnd(0);
  cmpFreeSpriteHnd(1);
  cmpFreeSpriteHnd(2);
  cmpFreeSpriteHnd(3);
  cmpFreeSpriteHnd(4);
}

// 0x1e57450
sprHandle_t *cmpGetSpriteHnd(CMP_SPR a_no) {
  if ((u32)a_no > 4)
    return 0;
  return g_hSpr[a_no];
}

// 0x1e5a2c0
void cmpInit(void) {
  sprHandle_t *v5;
  sprHandle_t *v8;
  sprHandle_t *v11;
  sprHandle_t *v14;

  g_hSpr[0] = 0;
  g_nCallLoadHnd[0] = 0;
  v5 = g_hSpr;
  v5[1] = 0;
  g_nCallLoadHnd[1] = 0;
  v8 = g_hSpr;
  v8[2] = 0;
  g_nCallLoadHnd[2] = 0;
  v11 = g_hSpr;
  v11[3] = 0;
  g_nCallLoadHnd[3] = 0;
  v14 = g_hSpr;
  v14[4] = 0;
  g_nCallLoadHnd[4] = 0;
}
