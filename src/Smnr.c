#include "types.h"
#include "smnr.h"

u32 Getrandstate;
u32 Getrandper;

// 0x21273e0
u16 GetRand(u16 mod) {
  u32 v4;

  v4 = 1103515245 * Getrandstate + 12345;
  Getrandstate = v4;
  return (u32)(HIWORD(v4) * mod) >> 16;
}

// 0x2127460
s32 GetIntervalRand(s32 min, s32 max) {
  s32 v6;
  s32 v7;
  u32 v8;

  if (min <= max)
    v6 = max;
  else
    v6 = min;
  if (min >= max)
    v7 = max;
  else
    v7 = min;
  v8 = 1103515245 * Getrandstate + 12345;
  Getrandstate = v8;
  return (s32)((u32)(0xFFFF * HIWORD(v8)) >> 16) % (v6 - v7 + 1) + v7;
}

// 0x2127500
u16 GetPercentage(void) {
  u32 v3;
  u32 v4;
  u32 v5;
  u32 v7;
  u32 v8;

  v3 = 1103515245 * Getrandstate + 12345;
  v4 = 1103515245 * v3 + 12345;
  Getrandstate = v4;
  v5 = (3197 * (((v4 >> 20) + (v3 >> 20)) & 0xFFF)) >> 17;
  if (Getrandper < v5 - 3 || Getrandper > v5 + 3)
  {
    Getrandper = v5;
  }
  else
  {
    v7 = 1103515245 * v4 + 12345;
    v8 = 1103515245 * v7 + 12345;
    Getrandstate = v8;
    Getrandper = v5;
    return (3197 * (((v8 >> 20) + (v7 >> 20)) & 0xFFF)) >> 17;
  }
  return v5;
}
