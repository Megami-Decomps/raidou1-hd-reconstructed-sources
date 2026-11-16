#pragma once
#include "types.h"

typedef struct effCtexHandle_t effCtexHandle_t;
typedef struct splistHandle_t splistHandle_t;

extern void *splistFaceIndex;
extern effCtexHandle_t *hSplistCacheTex;
extern effCtexHandle_t *hSplistCacheMTex;

splistHandle_t *effPolygonScalyCreate(u32 number, u32 face);
void effPolygonScalyDelete(splistHandle_t *hPolygon);
splistHandle_t *Copy(splistHandle_t *hSrc);
void effPolygonScalyDraw(splistHandle_t *hPolygon, const sdfMatrix4_t *pMatrix);
void effPolygonScalyInit(void);
