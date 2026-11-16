#pragma once
#include "types.h"

typedef struct FontReq_t FontReq_t;
typedef struct frFontTable_t frFontTable_t;

struct frFontTable_t {
    s32 GsFontNums;
    s32 TextHandleNums;
    s32 FontHandleNums;
    void *pTextRing;
    void *pRequestRing;
    FontReq_t *DestroyHandleList[2];
};
