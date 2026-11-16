#pragma once
#include "types.h"
#include "basic.h"

typedef struct dds3Basic_t dds3Basic_t;

// macros
// 0x22f0330: BASIC_TYPE GETBASICTYPEL(dds3Basic_t *pBasic)
#define GETBASICTYPEL(pBasic) (HIBYTE(pBasic->type))

// 0x22f3430: void printf(char *a)
#define printf(a) do { \
    ; \
} while (0)
