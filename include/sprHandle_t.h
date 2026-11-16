#pragma once
#include "types.h"

typedef struct sprHandle_t sprHandle_t;

struct sprHandle_t {
    u32 Type;
    u32 SpriteNums;
    u32 TexNums;
    sprHandle_t *pLink;
    sprHandle_t *pCurrent;
};
