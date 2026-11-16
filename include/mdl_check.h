#pragma once
#include "types.h"

typedef struct dds3ModelResrc_t dds3ModelResrc_t;

extern dds3ModelResrc_t *PREPARE_RE_LOADING;

// macros
// 0x1d81420: bool READY(dds3ModelResrc_t *st)
static inline bool READY(dds3ModelResrc_t *st) {
  if (!st)
    return 0;
  return PREPARE_RE_LOADING != st;
}
