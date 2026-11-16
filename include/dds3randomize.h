#pragma once
#include "types.h"

typedef struct sdfRandCB_t sdfRandCB_t;

extern sdfRandCB_t *CB;

u32 dds3GetRandA(void);
u32 dds3GetRandB(void);
f32 dds3GetRandFloatA(void);
f32 dds3GetRandFloatB(void);
u32 dds3GetRandIntA(u32 aLimit);
u32 dds3GetRandIntB(u32 aLimit);
s32 dds3Choose(f32 *probs);
void dds3InitRandCB(void);
