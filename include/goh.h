#pragma once
#include "types.h"

typedef enum {
    accident = 0,
    accident_result = 1,
    devilgift = 2,
    omoide_complete = 3,
    given_card = 4,
    renken = 5,
    renken_result = 6,
    renken_equip_sword = 7,
    devilkarte_error = 8,
    renken_sprit = 9,
    devil_report = 10,
} goh_;

typedef struct Base_t Base_t;
typedef struct ModelTable_t ModelTable_t;

struct Base_t {
    u32 Root;
    u32 Normal;
    u32 Inverse;
};

struct ModelTable_t {
    s32 Minor;
    f32 Pos[3];
    Base_t *Flag[13];
};

extern ModelTable_t *ModelTable[1];

// macros
// 0x1d96290: s32 KARTE_RESTORE_RATE(s32 _lev, s32 _str, s32 _tec, s32 _vit, s32 _luc)
static inline s32 KARTE_RESTORE_RATE(s32 _lev, s32 _str, s32 _tec, s32 _vit, s32 _luc) {
  s64 v6;

  v6 = 1717986919 * (tec + str + vit + luc) * (tec + str + vit + luc);
  return 100 * ((v6 >> 35) + ((u64)v6 >> 63) + lev);
}
