#pragma once
#include "types.h"
#include "configgamepad.h"
#include "dds3padmanager.h"
#include "libsdf.h"

// macros
// 0x2299440: bool CHECK_PRESS(SDF_PADMAP id)
static inline bool CHECK_PRESS(SDF_PADMAP id) {
  SDF_PAD *v4;

  v4 = PadMap[1][1];
  return v4[ConfigGameGetConfigPadMap(id, 1) & 0xFFFFFFFFFFFF00FFLL] != 0;
}

// 0x2299510: bool CHECK_TRIG(SDF_PADMAP id)
static inline bool CHECK_TRIG(SDF_PADMAP id) {
  SDF_PAD *v4;

  v4 = PadMap[1][1];
  return ((u32)v4[ConfigGameGetConfigPadMap(id, 1) & 0xFFFFFFFFFFFF00FFLL] >> 7)
       & 1;
}

// 0x22995e0: bool CHECK_REP(SDF_PADMAP id)
static inline bool CHECK_REP(SDF_PADMAP id) {
  SDF_PAD *v4;

  v4 = PadMap[1][1];
  return ((u32)v4[ConfigGameGetConfigPadMap(id, 1) & 0xFFFFFFFFFFFF00FFLL] >> 1)
       & 1;
}
