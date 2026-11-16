#pragma once
#include "types.h"

typedef enum {
    GUIDE_RESULT_RST = 0,
    GUIDE_RESULT_RAIDOU_LV = 1,
    GUIDE_RESULT_RAIDOU_LV_NR = 2,
    GUIDE_RESULT_DEVIL_LV = 3,
    GUIDE_RESULT_DEVIL_SKL = 4,
    GUIDE_RESULT_DEVIL_SKL_O = 5,
    GUIDE_RESULT_VIEWER = 6,
    GUIDE_RESULT_DEVIL_O_LOG = 7,
    GUIDE_RESULT_DEVIL_O_OVER = 8,
} GUIDE_RESULT;

typedef enum {
    ResultDrawType_PLAYER = 0,
    ResultDrawType_STOCK1 = 1,
    ResultDrawType_STOCK2 = 2,
} ResultDrawType;

typedef struct sdfIVector2_t sdfIVector2_t;
typedef struct sprHandle_t sprHandle_t;

extern void *rstGuides;
extern void *rstSprTable01;
extern void *rstSprTable02;
extern void *rstSprTable03;
extern void *rstSprTableRoot;

void rstResultResultGuideSet(GUIDE_RESULT _id, bool _timer, s32 _waitTimer);
s32 rstResultGetSpriteNo(s32 TableNo, s32 PartsNo);
void rstResultGetSpritePos(s32 TableNo, s32 PartsNo, s32 pX, s32 pY);
void rstResultSpriteParts(s32 X, s32 Y, const sdfVector2_t *Scale, s32 AlphaRate, s32 TableNo, s32 PartsNo, sprHandle_t *pSpr, u32 OtNo);
void rstResultSpritePartsEx(s32 X, s32 Y, const sdfVector2_t *Scale, s32 AlphaRate, s32 TableNo, s32 PartsNo, sprHandle_t *pSpr, s32 color, u32 OtNo);
s32 rstCheckNumArea(s32 Val, s32 Min, s32 Max);
s32 rstCalcAlphaRate(s32 NowFrame, void *pTable, s32 TableNums);
void rstCalcScale(s32 NowFrame, void *pTable, s32 TableNums, const sdfVector2_t *Scale);
void rstCalcPosition(s32 NowFrame, void *pTable, s32 TableNums, sdfIVector2_t Position);
void rstResultGetExpCyuusei(void *pData, s32 X, s32 Y, s32 AlphaRate, s32 Exp, s32 Cyuusei, sprHandle_t *pSpr);
void rstResultExpGauge(void *pData, s32 X, s32 Y, s32 AlphaRate, s32 CurrentExp, s32 CurrentLevelExp, s32 NextLevelExp, s32 *pPartsList, sprHandle_t *pSpr, ResultDrawType _type);
void rstResultAddLevelUpAnimQue(void *pQue);
void rstResultLevelUpAnim(s32 X, s32 Y, s32 AlphaRate, s32 Type, void *pQue, sprHandle_t *pSpr);
void rstResultCyuuseiGauge(void *pData, s32 X, s32 Y, s32 AlphaRate, s32 Cyuusei, sprHandle_t *pSpr, ResultDrawType _type);
void rstResultAddCyuuseiMaxAnimQue(void *pQue);
s32 rstResultCyuuseiMaxAnim(s32 X, s32 Y, s32 AlphaRate, void *pQue, sprHandle_t *pSpr);
void rstResultPlayerLevel(s32 X, s32 Y, s32 AlphaRate, void *pData, sprHandle_t *pSpr);
void rstResultNakamaLevel(s32 X, s32 Y, s32 AlphaRate, void *pData, sprHandle_t *pSpr, s32 index, s32 IorO);
void rstResultMoneyMagItem(s32 X, s32 Y, s32 AlphaRate, void *pData, sprHandle_t *pSpr);
void rstResultResultDraw(void *pData);
void rstResultDrawStar(void *pData, s32 x, s32 y, u8 mode);
