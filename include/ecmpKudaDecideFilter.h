#pragma once
#include "types.h"

typedef enum {
    ecmpKudaDecideFilter_None = 0,
    ecmpKudaDecideFilter_Party = 1,
    ecmpKudaDecideFilter_NoSummon = 2,
    ecmpKudaDecideFilter_Stock = 4,
    ecmpKudaDecideFilter_RaidoOnly = 8,
    ecmpKudaDecideFilter_NoRaido = 16,
    ecmpKudaDecideFilter_NoStock = 32,
    ecmpKudaDecideFilter_Summon = 64,
    ecmpKudaDecideFilter_Empty = 128,
    ecmpKudaDecideFilter_NoEmpty = 256,
} ecmpKudaDecideFilter;
