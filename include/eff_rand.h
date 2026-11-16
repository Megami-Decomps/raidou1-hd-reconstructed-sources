#pragma once
#include "types.h"
#include "dds3randomize.h"
#include "sdfrand.h"

// macros
// 0x1978780: f32 FA(f32 r)
static inline f32 FA(f32 r) {
  sdfRandCB_t *CB_local;
  u32 *v;
  u32 v8;
  s32 v9;
  u32 v10;
  s32 v11;
  s32 v12;

  CB_local = CB;
  if (!CB_local)
    CB_local = sdfDefaultRandCB;
  v = CB_local->v;
  v8 = v[0];
  v9 = *(u64 *)v >> 30;
  v10 = v[2];
  v11 = *(u64 *)&v[2] >> 31;
  v[2] = v[1];
  v[3] = v10;
  v12 = v11 ^ v9;
  v[0] = v12;
  v[1] = v8;
  return (f32)(1.0 - r) + (f32)((f32)((f32)(v12 & 0xFFFFFF) * 5.9604645e-08) * r);
}

// 0x1978900: f32 FR(f32 r)
static inline f32 FR(f32 r) {
  sdfRandCB_t *CB_local;
  u32 *v;
  u32 v8;
  s32 v9;
  u32 v10;
  s32 v11;
  s32 v12;

  CB_local = CB;
  if (!CB_local)
    CB_local = sdfDefaultRandCB;
  v = CB_local->v;
  v8 = v[0];
  v9 = *(u64 *)v >> 30;
  v10 = v[2];
  v11 = *(u64 *)&v[2] >> 31;
  v[2] = v[1];
  v[3] = v10;
  v12 = v11 ^ v9;
  v[0] = v12;
  v[1] = v8;
  return (f32)((f32)(v12 & 0xFFFFFF) * 5.9604645e-08) * r;
}
