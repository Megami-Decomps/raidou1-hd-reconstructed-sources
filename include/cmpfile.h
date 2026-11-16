#pragma once
#include "types.h"
#include "CMP_SPR.h"

typedef struct sprHandle_t sprHandle_t;

extern sprHandle_t *g_hSpr;

bool cmpLinkMotMoya(void);
bool cmpLinkMotSakura(void);
bool cmpLinkMotion(CMP_SPR a_sprFileNo);
bool _FreeMotion(s32 a_motNo);
bool cmpFreeMotion(CMP_SPR a_sprFileNo);
bool _ResetMotion(CMP_SPR a_sprFileNo, s32 a_sprNo);
bool cmpResetMotMoya(void);
bool cmpResetMotSakura(void);
bool cmpResetMotion(s32 a_motNo);
bool cmpFreeSpriteMem(CMP_SPR a_no);
bool cmpLoadSpriteMem(CMP_SPR a_no);
bool cmpFreeSpriteHnd(CMP_SPR a_no);
bool cmpLoadSpriteHnd(CMP_SPR a_no);
bool cmpLoadSpriteToMem(void);
void cmpFreeSpriteToMem(void);
void cmpFreeSpriteToGS(void);
sprHandle_t *cmpGetSpriteHnd(CMP_SPR a_no);
void cmpInit(void);
