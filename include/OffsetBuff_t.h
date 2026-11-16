#pragma once
#include "types.h"

typedef struct OffsetBuff_t OffsetBuff_t;
typedef struct dds3Particle_SphereSpiral2_t_OffsetBuff_t_Parts_t dds3Particle_SphereSpiral2_t_OffsetBuff_t_Parts_t;

struct dds3Particle_SphereSpiral2_t_OffsetBuff_t_Parts_t {
    u32 point;
    u32 count;
    sdfVector3_t pPosBuff;
};

struct OffsetBuff_t {
    dds3Particle_SphereSpiral2_t_OffsetBuff_t_Parts_t *pParts;
    u32 length;
};
