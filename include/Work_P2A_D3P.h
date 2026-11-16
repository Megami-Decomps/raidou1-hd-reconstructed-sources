#pragma once
#include "types.h"

typedef struct Work_P2A_D3P Work_P2A_D3P;
typedef struct mdlEffectResrcItem_t mdlEffectResrcItem_t;
typedef struct sdfModelExtraChunkMarkPos_t sdfModelExtraChunkMarkPos_t;

struct Work_P2A_D3P {
    mdlEffectResrcItem_t *resrc;
    sdfModelExtraChunkMarkPos_t *mark;
    f32 z_offset;
};
