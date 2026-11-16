#pragma once
#include "types.h"

typedef struct effCtexHandle_t effCtexHandle_t;

void effEnvInit(void);
effCtexHandle_t *Create(void *pTex);
effCtexHandle_t *effCreateGID(void *pTex);
void Delete(effCtexHandle_t *hCtex);
effCtexHandle_t *Copy(effCtexHandle_t *hCTex);
