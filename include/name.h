#pragma once
#include "types.h"

#define NAMEMAX_PLAYER_FIRST 10
#define NAMEMAX_PLAYER_FAMILY 10
#define DREAMMAX 20
#define STRINGMAX_PLAYER_FIRST 20
#define STRINGMAX_PLAYER_FAMILY 20
#define STRINGDREAMMAX 40

typedef enum {
    NME_SEQ_NAME = 0,
    NME_SEQ_INPUT0 = 1,
    NME_SEQ_INPUT0_CHECK = 2,
    NME_SEQ_DEBUG = 3,
    NME_SEQ_NORMAL = 4,
} NME_SEQ;

typedef enum {
    NME_MODE_LOAD = 0,
    NME_MODE_INPUT = 1,
    NME_MODE_CHECK = 2,
    NME_MODE_END = 3,
} NME_MODE;
