#pragma once
#include "types.h"

typedef struct Standard Standard;
typedef struct effOption effOption;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct effQuakeRequest_t effQuakeRequest_t;
typedef struct effQuake_Params_t effQuake_Params_t;
typedef struct quakeHandle_t quakeHandle_t;

struct effQuake_Params_t {
    s32 life;
    u32 power;
};

struct quakeHandle_t {
    effOption *option;
    s32 frame;
    effQuake_Params_t *param;
    effQuakeRequest_t *req;
};

quakeHandle_t *PartsCreate(Standard *pParts);
void Delete(effPartsHandle_t *handle);
quakeHandle_t *Copy(effPartsHandle_t *handle);
void effRun(effPartsHandle_t *handle);
