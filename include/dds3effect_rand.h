#pragma once
#include "types.h"
#include "dds3effect.h"
#include "sdfrand.h"

// macros
// 0x195eee0: f32 FA(f32 r)
static inline f32 FA(f32 r) {
  sdfRandCB_t *Rand_local;
  u32 *v;
  u32 v10;
  s32 v11;
  u32 v12;
  s32 v13;
  s32 v14;

  Rand_local = Rand;
  if (!Rand_local)
    Rand_local = sdfDefaultRandCB;
  v = Rand_local->v;
  v10 = v[0];
  v11 = *(u64 *)v >> 30;
  v12 = v[2];
  v13 = *(u64 *)&v[2] >> 31;
  v[2] = v[1];
  v[3] = v12;
  v14 = v13 ^ v11;
  v[0] = v14;
  v[1] = v10;
  return (f32)(1.0 - r) + (f32)((f32)((f32)(v14 & 0xFFFFFF) * 5.9604645e-08) * r);
}
