#pragma once
#include "types.h"

typedef struct sprHandle_t sprHandle_t;

void fclBackSprite(s32 a_type, u8 a_alphaRate1, u8 a_alphaRate2, sprHandle_t *a_hSpr);
void fclCommandHelp(s32 a_cmdID, u8 a_alphaRate);
