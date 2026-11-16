#pragma once
#include "types.h"
#include "cfg.h"
#include "configgamepad.h"
#include "dds3padmanager.h"
#include "libsdf.h"

#define REPEAT_TIME_1ST 8
#define REPEAT_TIME 2

// macros
// 0x22988e0: bool CHECK_PRESS2(SDF_PADMAP id)
static inline bool CHECK_PRESS2(SDF_PADMAP id) {
  SDF_PAD *v4;

  v4 = PadMap[0][0];
  return v4[ConfigGameGetConfigPadMap(id, 1) & 0xFFFFFFFFFFFF00FFLL] != 0;
}

// 0x22989b0: bool CHECK_TRIG2(SDF_PADMAP id)
static inline bool CHECK_TRIG2(SDF_PADMAP id) {
  SDF_PAD *v4;

  v4 = PadMap[0][0];
  return ((u32)v4[ConfigGameGetConfigPadMap(id, 1) & 0xFFFFFFFFFFFF00FFLL] >> 7)
       & 1;
}

// 0x2298a80: bool CHECK_REP2(SDF_PADMAP id)
static inline bool CHECK_REP2(SDF_PADMAP id) {
  SDF_PAD *v4;

  v4 = PadMap[0][0];
  return ((u32)v4[ConfigGameGetConfigPadMap(id, 1) & 0xFFFFFFFFFFFF00FFLL] >> 1)
       & 1;
}

// 0x2298b50: bool CHECK_OTHER_PRESS(SDF_PADMAP *id)
static inline bool CHECK_OTHER_PRESS(SDF_PADMAP *id) {
  void *v6;
  void *v7;
  s64 v8;
  il2cpp_array_size_t max_length;
  s32 v10;
  s32 ConfigPadMap;
  s64 size;
  s64 v13;
  void *items;
  s32 v15;
  s32 v16;
  bool v17;
  s32 i;
  s32 Item;
  s32 ConfigGAMEPAD;
  s64 v25;
  SDF_PAD *v26;
  s32 v27;
  s32 v28;

  v6 = Allocate(System_Collections_Generic_List_int_);
  __ctor_47770768(v6, keyid_to_padmap);
  v7 = Allocate(System_Collections_Generic_List_SDF_PADMAP_);
  __ctor_47784064(v7, id->max_length);
  if (SLODWORD(id->max_length) < 1)
    return 0;
  v8 = 0;
  do
  {
    while (1)
    {
      v10 = id[v8];
      ConfigPadMap = ConfigGameGetConfigPadMap(v10, 0);
      _Remove(v6, ConfigPadMap);
      size = v7->_size;
      v13 = Method_System_Collections_Generic_List_SDF_PADMAP__Add__;
      ++v7->_version;
      items = v7->_items;
      if ((u32)size < LODWORD(items->max_length))
        break;
      _AddWithResize(v7, ConfigPadMap, *(const MethodInfo_2D92A30 **)(*(u64 *)(*(u64 *)(v13 + 32) + 192) + 112));
      max_length = id->max_length;
      if (++v8 >= (s32)max_length)
        goto LABEL_14;
    }
    v7->_size = size + 1;
    *((u32 *)items + size) = ConfigPadMap;
    max_length = id->max_length;
    ++v8;
  }
  while (v8 < (s32)max_length);
LABEL_14:
  if ((s32)max_length < 1)
    return 0;
  v15 = v6->_size;
  if (v15 < 1)
    return 0;
  v16 = 0;
  while (2)
  {
    if (v15 < 1)
      goto LABEL_22;
    v28 = v16;
    for (i = 0; i < v15; ++i)
    {
      Item = _get_Item(v6, i);
      if ((Item & 0xFFFFFFFC) == 0x1000)
      {
        ConfigGAMEPAD = cfgGetConfigGAMEPAD(1, 0);
        v25 = 0;
        if ((ConfigGAMEPAD & 0xFFFFFFFE) == 2)
          goto LABEL_35;
        goto LABEL_34;
      }
LABEL_34:
      v25 = 1;
LABEL_35:
      v26 = PadMap[v25][0];
      v27 = _get_Item(v6, i);
      v17 = 1;
      if (v26[ConfigGameGetConfigPadMap(v27, 1) & 0xFFFFFFFFFFFF00FFLL])
        return v17;
      v15 = v6->_size;
    }
    max_length = id->max_length;
    v16 = v28;
LABEL_22:
    ++v16;
    v17 = 0;
    if (v16 < (s32)max_length)
      continue;
    return v17;
  }
}

// 0x22990b0: bool CHECK_PRESS(SDF_PADMAP id, bool mouseCheck)
static inline bool CHECK_PRESS(SDF_PADMAP id, bool mouseCheck) {
  s32 ConfigGAMEPAD;
  s64 v8;
  SDF_PAD *v9;

  if ((id & 0xFFFFFFFC) == 0x1000)
  {
    ConfigGAMEPAD = cfgGetConfigGAMEPAD(1, 0);
    v8 = 0;
    if ((ConfigGAMEPAD & 0xFFFFFFFE) == 2)
      goto LABEL_14;
  }
  v8 = 1;
LABEL_14:
  v9 = PadMap[v8][0];
  return v9[ConfigGameGetConfigPadMap(id, 1) & 0xFFFFFFFFFFFF00FFLL] != 0;
}

// 0x2298fb0: s32 PadMapIdx(SDF_PADMAP id)
static inline s32 PadMapIdx(SDF_PADMAP id) {
  if ((id & 0xFFFFFFFC) != 0x1000)
    return 1;
  return (cfgGetConfigGAMEPAD(1, 0) & 0xFFFFFFFE) != 2;
}

// 0x22982f0: bool CHECK_TRIG(SDF_PADMAP id, bool mouseCheck)
static inline bool CHECK_TRIG(SDF_PADMAP id, bool mouseCheck) {
  s32 ConfigGAMEPAD;
  s64 v8;
  SDF_PAD *v9;

  if ((id & 0xFFFFFFFC) == 0x1000)
  {
    ConfigGAMEPAD = cfgGetConfigGAMEPAD(1, 0);
    v8 = 0;
    if ((ConfigGAMEPAD & 0xFFFFFFFE) == 2)
      goto LABEL_14;
  }
  v8 = 1;
LABEL_14:
  v9 = PadMap[v8][0];
  return ((u32)v9[ConfigGameGetConfigPadMap(id, 1) & 0xFFFFFFFFFFFF00FFLL] >> 7)
       & 1;
}

// 0x2299270: bool CHECK_REP(SDF_PADMAP id, bool mouseCheck)
static inline bool CHECK_REP(SDF_PADMAP id, bool mouseCheck) {
  s32 ConfigGAMEPAD;
  s64 v8;
  SDF_PAD *v9;

  if ((id & 0xFFFFFFFC) == 0x1000)
  {
    ConfigGAMEPAD = cfgGetConfigGAMEPAD(1, 0);
    v8 = 0;
    if ((ConfigGAMEPAD & 0xFFFFFFFE) == 2)
      goto LABEL_14;
  }
  v8 = 1;
LABEL_14:
  v9 = PadMap[v8][0];
  return ((u32)v9[ConfigGameGetConfigPadMap(id, 1) & 0xFFFFFFFFFFFF00FFLL] >> 1)
       & 1;
}
