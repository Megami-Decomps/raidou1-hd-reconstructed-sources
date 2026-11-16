#pragma once
#include "types.h"

typedef enum {
    ATRB_MASK = 4095,
    ATRB_NONE = 0,
    ATRB_BUTURI = 1,
    ATRB_HGUN = 2,
    ATRB_KAEN = 4,
    ATRB_ICE = 8,
    ATRB_THUNDER = 16,
    ATRB_ZAN = 32,
    ATRB_JYUSATU = 64,
    ATRB_SEISHIN = 128,
    ATRB_BANNOU = 256,
    ATRB_RECV = 512,
    ATRB_KATANA = 1024,
    ATRB_ALL = 268435455,
    ATRB_KUDAN = 382,
    ATRB_NUM = 16,
} ATRB;
