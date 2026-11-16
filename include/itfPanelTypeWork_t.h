#pragma once
#include "types.h"

typedef struct itfPanelTypeWork_t itfPanelTypeWork_t;
typedef struct sdfGrPacketHeader_t sdfGrPacketHeader_t;
typedef struct sdfIVector2_t sdfIVector2_t;
typedef struct sdfIVector4_t sdfIVector4_t;

struct itfPanelTypeWork_t {
    sdfGrPacketHeader_t *next;
    s32 ctxt;
    sdfIVector2_t *pvertex[40];
    sdfIVector4_t *pcolor[8];
};
