#pragma once
#include "types.h"

typedef struct Standard Standard;
typedef struct effParts_t effParts_t;

u8 *effParamsGet(void *hParts);
void *effDataGet(void *hParts);
effParts_t *Create(Standard *pData);
void Delete(effParts_t *hParts);
void effParamsDelete(effParts_t *hParts);
void effDataDelete(effParts_t *hParts);
effParts_t *Copy(effParts_t *hCopyParts);
void Draw(effParts_t *hParts);
void PositionSet(effParts_t *hParts, const sdfVector4_t *pPos);
void RotateSet(effParts_t *hParts, const sdfVector4_t *pRot);
void ScaleSet(effParts_t *hParts, f32 scale);
void ColorSet(effParts_t *hParts, const sdfVector4_t *abgr);
