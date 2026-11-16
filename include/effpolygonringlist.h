#pragma once
#include "types.h"

typedef struct rplistHandle_t rplistHandle_t;

extern void *rplistFaceIndex;

rplistHandle_t *effPolygonRingCreate(u32 face);
void effPolygonRingDelete(rplistHandle_t *hPolygon);
void effPolygonRingDraw(rplistHandle_t *hPolygon, const sdfMatrix4_t *pMatrix);
