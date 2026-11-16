#pragma once
#include "types.h"

typedef struct wplistHandle_t wplistHandle_t;

extern void *wplistFaceIndex;

wplistHandle_t *effPolygonWindCreate(u32 number, u32 face, void *pTex);
void effPolygonWindDelete(wplistHandle_t *hPolygon);
wplistHandle_t *Copy(wplistHandle_t *hSrc);
void effPolygonWindDraw(wplistHandle_t *hPolygon, const sdfMatrix4_t *pMatrix);
void effPolygonWindInit(void);
