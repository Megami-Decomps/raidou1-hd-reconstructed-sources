#pragma once
#include "types.h"
#include "effect.h"

typedef enum {
    DDS3PARTICLE_SPIRAL = 0,
    DDS3PARTICLE_SMOKE = 1,
    DDS3PARTICLE_SPARK = 2,
    DDS3PARTICLE_RADIATE = 3,
    DDS3PARTICLE_SPHERESPIRAL = 4,
    DDS3PARTICLE_SPHERESMOKE = 5,
    DDS3PARTICLE_SPHERERING = 6,
    DDS3PARTICLE_SPARK2 = 7,
    DDS3PARTICLE_SPHEREATOM = 8,
    DDS3PARTICLE_NOP = 9,
    DDS3PARTICLE_SPARKOFFSET = 10,
    DDS3PARTICLE_SMOKEOFFSET = 11,
    DDS3PARTICLE_SPHERESPIRAL2 = 12,
} DDS3PARTICLE;

typedef struct dds3Particle_Basic_t dds3Particle_Basic_t;
typedef struct sdfRandCB_t sdfRandCB_t;

extern sdfRandCB_t *ParRand;

void dds3ParticleManagerInit(void);
void dds3ParticleManagerExit(void);
dds3Particle_Basic_t *dds3ParticleCreate(u16 type, void *pData);
void dds3ParticleDelete(void *handle);
void dds3ParticleDraw(void *handle);
void *dds3ParticleCopy(void *handle);
void dds3ParticleSetScale(void *handle, f32 scale);
DDS3EFFECT_STATE dds3ParticleGetState(void *handle);
void dds3ParticleSetPosition(void *handle, const sdfVector4_t *pPos);
void dds3ParticleSetRotateMatrix(void *handle, const sdfMatrix4_t *pMatrix);
void dds3ParticleSetRGBA(void *handle, const sdfVector4_t *abgr);
void dds3ParticleSetLoop(void *handle, u8 loop);
u8 dds3ParticleGetLoop(void *handle);
dds3Particle_Basic_t *dds3ParticleExpCreate(u16 type, void *pData);
