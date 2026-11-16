#pragma once
#include "types.h"

typedef struct Standard Standard;
typedef struct effOption effOption;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct effQuake2_Params_t effQuake2_Params_t;
typedef struct quake2Handle_t quake2Handle_t;

struct effQuake2_Params_t {
    s32 life;
    u16 power;
    u32 fade_in;
    u32 fade_out;
};

struct quake2Handle_t {
    effOption *option;
    s32 frame;
    effQuake2_Params_t *param;
};

quake2Handle_t *PartsCreate(Standard *pParts);
void Delete(effPartsHandle_t *handle);
quake2Handle_t *Copy(effPartsHandle_t *handle);
void Run(effPartsHandle_t *handle);
