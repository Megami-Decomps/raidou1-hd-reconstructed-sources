#pragma once
#include "types.h"

typedef enum {
    EMRT_NONE = 0,
    EMRT_GUREN = 1,
    EMRT_GINSUI = 2,
    EMRT_RAIDEN = 3,
    EMRT_SIPUU = 4,
    EMRT_BANRYOKU = 5,
    EMRT_GEHOU = 6,
    EMRT_GIGEI = 7,
    EMRT_DUMMY8 = 8,
    EMRT_DUMMY9 = 9,
    EMRT_DUMMY10 = 10,
    EMRT_DUMMY11 = 11,
    EMRT_DUMMY12 = 12,
    EMRT_DUMMY13 = 13,
    EMRT_DUMMY14 = 14,
    EMRT_DUMMY15 = 15,
    EMRT_DUMMY16 = 16,
    EMRT_DUMMY17 = 17,
    EMRT_DUMMY18 = 18,
    EMRT_SEIREI = 19,
    EMRT_MITAMA = 20,
    EMRT_MAJIN = 21,
    EMRT_TOSHI = 22,
} EMRaceType;

typedef struct SMRankChangeTbl SMRankChangeTbl;

struct SMRankChangeTbl {
    EMRaceType eRaceType;
    u16 uData;
};
