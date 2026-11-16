#pragma once
#include "types.h"
#include "EFFPFLIST_TYPE.h"

typedef struct effOption effOption;
typedef struct effPolygonFlashMesh effPolygonFlashMesh;
typedef struct fplistHandle_t fplistHandle_t;

extern void *pflist3FaceIndex;
extern void *uvTable;

fplistHandle_t *effPolygonFlashCreate(u32 face, EFFPFLIST_TYPE type, void *pTex, effPolygonFlashMesh *mesh);
void effPolygonFlashDelete(fplistHandle_t *hPolygon);
fplistHandle_t *Copy(fplistHandle_t *hSrc, effPolygonFlashMesh *mesh);
void effPolygonFlashDraw(fplistHandle_t *hPolygon, const sdfMatrix4_t *pMatrix, effOption *option);
void effPolygonFlashInit(void);
bool effPolygonFlashSetMesh(fplistHandle_t *hPolygon);
