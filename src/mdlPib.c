#include "types.h"
#include "mdlpib.h"

typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct pibChunk_t pibChunk_t;
typedef struct pibHeaderChunk_t pibHeaderChunk_t;

// 0x1d643f0
pibChunk_t *mdlPibGetChunk(dds3ModelHandle_t *handle, s32 group) {
  pibHeaderChunk_t *effectData;
  pibChunk_t *chunk;
  s64 max_length;
  pibChunk_t *i;
  pibChunk_t *result;

  effectData = handle->resrc->effectData;
  if (!effectData)
    return 0;
  chunk = effectData->chunk;
  if ((s32)chunk->max_length < 1)
    return 0;
  max_length = (u32)chunk->max_length;
  for (i = chunk; ; ++i)
  {
    result = i;
    if (i->group == group)
      break;
    if (!--max_length)
      return 0;
  }
  return result;
}

// 0x1d64440
s32 mdlPibGetEffectCount(pibHeaderChunk_t *data) {
  return data->effectCount;
}

// 0x1d64450
s32 mdlPibGetMotionCount(pibHeaderChunk_t *data) {
  return data->motionCount;
}
