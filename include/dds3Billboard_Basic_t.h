#pragma once
#include "types.h"
#include "dds3EffectHandle_t_DrawFunc.h"
#include "dds3billboard.h"
#include "effect.h"

typedef struct dds3Billboard_Basic_t dds3Billboard_Basic_t;
typedef struct effOption effOption;

struct dds3Billboard_Basic_t {
    sdfVector4_t pos;
    sdfVector4_t scale;
    f32 rot;
    sdfVector4_t abgr;
    dds3EffectHandle_t_DrawFunc Draw;
    DDS3BILLBOARD type;
    BILL_MODE mode;
    s32 camID;
    effOption *option;
};
