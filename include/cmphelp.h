#pragma once
#include "types.h"

typedef enum {
    CMPHELP_STAT_TYPE = 1,
    CMPHELP_STAT_DRAW = 2,
    CMPHELP_STAT_NEW = 4,
} CMPHELP_STAT;

typedef enum {
    CMPHELP_TYPE_SKILL = 0,
    CMPHELP_TYPE_ITEM = 1,
} CMPHELP_TYPE;

typedef enum {
    FRW_FRW_TAG_NONE = 0,
    FRW_FRW_RETTAG_ON = 1,
    FRW_FRW_AFDELTAG_ON = 2,
    FRW_FRW_AFDELTAG_RET_ON = 4,
    FRW_FRW_FLAG_MASK = -65536,
    FRW_FRW_FLAG_CENTER = 65536,
} FRW_FRW;

typedef struct sprHandle_t sprHandle_t;
typedef struct tagCMPHELP_WK tagCMPHELP_WK;

struct tagCMPHELP_WK {
    sprHandle_t *hSpr;
    CMPHELP_STAT stat;
    CMPHELP_TYPE type;
    u16 id;
    s32 basePosX;
    s32 basePosY;
};

extern tagCMPHELP_WK *wk;
extern s16 **cmpHelpSprParam;

void cmpSetDraw(bool a_bDraw);
bool cmpGetDraw(void);
void cmpSetType(CMPHELP_TYPE a_type);
void cmpSetId(u16 a_id);
void cmpSetNew(void);
void cmpDrawSpriteDef(s32 a_x, s32 a_y, s32 a_z, u8 a_alphaRate, s32 a_sprno);
u32 cmpSetAlphaRate(u32 a_color, f32 a_alphaRate);
void cmpDrawEx(FRW_FRW a_drawmode, f32 a_alphaRate);
void cmpDraw(void);
void cmpDrawAlpha(f32 a_alphaRate);
void Init(void);
void cmpStartLoadSprite(void);
bool cmpCheckLoadSprite(void);
void cmpEnd(void);
