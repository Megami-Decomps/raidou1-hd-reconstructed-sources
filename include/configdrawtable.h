#pragma once
#include "types.h"

typedef enum {
    MT_A = 0,
    MT_B = 1,
    MT_C = 2,
    MT_D = 3,
    MT_E = 4,
    MT_F = 5,
    MT_G = 6,
} MT;

typedef enum {
    DR_T1 = 0,
    DR_T2 = 1,
    DR_T3 = 2,
    DR_T4 = 3,
    DR_T5 = 4,
    DR_T6 = 5,
    DR_T7 = 6,
} DR;

extern MT *menuTbl[4];
extern DR **DRTbl;
