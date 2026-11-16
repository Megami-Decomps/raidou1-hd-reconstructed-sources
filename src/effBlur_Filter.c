#include "types.h"
#include "effblur_filter.h"

#define DDS3EFFECT_FILTER_OT 79

f32 EFF_BLURVAL;

// 0x19563e0
f32 effBlurGetBlurValid(void) {
  return EFF_BLURVAL;
}

// 0x1956430
void effBlurSetBlurValid(f32 val) {
  EFF_BLURVAL = val;
}
