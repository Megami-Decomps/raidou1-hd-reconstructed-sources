#pragma once
#include "types.h"

typedef struct tplistHandle_t tplistHandle_t;

extern void *tplistFaceIndex;

tplistHandle_t *effPolygonThunderCreate(u32 face);
void effPolygonThunderDelete(tplistHandle_t *hPolygon);
