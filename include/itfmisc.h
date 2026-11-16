#pragma once
#include "types.h"

typedef struct itfMiscLinkHeader_t itfMiscLinkHeader_t;
typedef struct itfMiscLinkStack_t itfMiscLinkStack_t;
typedef struct sdfDrawTag_t sdfDrawTag_t;
typedef struct sdfIVector4_t sdfIVector4_t;

void itfMiscLinkInitialize(itfMiscLinkStack_t *pstack, itfMiscLinkHeader_t *ptop, s32 numelem);
itfMiscLinkHeader_t *itfMiscLinkTake(itfMiscLinkStack_t *pstack);
void itfMiscLinkGive(itfMiscLinkHeader_t *pelem, itfMiscLinkStack_t *pstack);
void itfMiscSetRatioRGB(sdfIVector4_t **pout, s32 off, s32 red, s32 green, s32 blue, s32 alpha, sdfIVector4_t *pratio, s32 num);
void itfMiscDrawSpritePrim(sdfIVector4_t pos, sdfIVector4_t uv, const sdfColor32_t *color, u32 z, void *texhandle, s32 context, sdfDrawTag_t *pdrawtag, void *mesh);
void itfMiscDrawAlphaPrim(sdfDrawTag_t *pdrawtag, s32 tp, s32 context);
s32 itfCamp(void);
