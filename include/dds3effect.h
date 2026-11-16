#pragma once
#include "types.h"
#include "effect.h"

typedef enum {
    DDS3EFFECT_PARTICLE = 0,
    DDS3EFFECT_PARTICLE_EXP = 1,
    DDS3EFFECT_POLYGON = 2,
    DDS3EFFECT_MAGATUHI = 3,
    DDS3EFFECT_PCF = 4,
    DDS3EFFECT_EPL = 5,
    DDS3EFFECT_NOP = 6,
    DDS3EFFECT_COUNT = 7,
} DDS3EFFECT;

typedef struct effHandle_t effHandle_t;
typedef struct sdfRandCB_t sdfRandCB_t;

extern sdfRandCB_t *Rand;

void dds3EffectManagerInit(void);
effHandle_t *dds3EffectCreate(DDS3EFFECT major, u16 minor, void *pData);
void Delete(effHandle_t *hEffect);
void dds3EffectDraw(effHandle_t *hEffect);
void dds3EffectSetScale(effHandle_t *hEffect, f32 scale);
DDS3EFFECT_STATE dds3EffectGetState(effHandle_t *hEffect);
void dds3EffectSetPosition(effHandle_t *hEffect, const sdfVector4_t *pPos);
void dds3EffectSetRotateMatrix(effHandle_t *hEffect, const sdfMatrix4_t *pMatrix);
void dds3EffectSetRGBA(effHandle_t *hEffect, u32 abgr);
void SetRGBA(effHandle_t *hEffect, const sdfVector4_t *abgr);
void dds3EffectSetLoop(effHandle_t *hEffect, u8 loop);
u8 dds3EffectGetLoop(effHandle_t *hEffect);
effHandle_t *dds3EffectCopy(effHandle_t *hCopyEff);
effHandle_t *dds3EffectLoad(void *pD3P);
effHandle_t *dds3EffectLoadEPL(void *pEPL);
