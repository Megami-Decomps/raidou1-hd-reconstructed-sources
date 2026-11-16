#pragma once
#include "types.h"

typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct pibChunk_t pibChunk_t;
typedef struct pibHeaderChunk_t pibHeaderChunk_t;

pibChunk_t *mdlPibGetChunk(dds3ModelHandle_t *handle, s32 group);
s32 mdlPibGetEffectCount(pibHeaderChunk_t *data);
s32 mdlPibGetMotionCount(pibHeaderChunk_t *data);
