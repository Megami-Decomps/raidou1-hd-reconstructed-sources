#pragma once
#include "types.h"
#include "gohAccidentKN.h"
#include "gohAccidentLR.h"

typedef struct gohData_t gohData_t;
typedef struct gohResult_t gohResult_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

extern u8 *gohCombine;

void gohResultUnit(gohResult_t *pResult, gohData_t *pData, sdatUnitWork_t *pDevil1, sdatUnitWork_t *pDevil2);
s32 gohGift(gohResult_t *pResult, sdatUnitWork_t *pBirthDevil, sdatUnitWork_t *pDevil1, sdatUnitWork_t *pDevil2);
gohAccidentKN gohChkAccident(gohData_t *pData);
s32 gohAccidentDevil(gohData_t *pData);
s32 gohNormal(gohData_t *pData, sdatUnitWork_t *pBirthDevil, sdatUnitWork_t *pDevil1, sdatUnitWork_t *pDevil2);
s32 gohNormalSearchi(sdatUnitWork_t *pBirthDevil, sdatUnitWork_t *pDevil1, sdatUnitWork_t *pDevil2);
void gohCreateGoodbyMes(gohData_t *pData, s32 iDevilNo1, s32 iDevilNo2);
gohAccidentLR gohGetLuckRank(void);
