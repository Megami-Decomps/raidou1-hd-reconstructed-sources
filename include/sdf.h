#pragma once
#include "types.h"

#define PI 3.1415927
#define PIx2 6.2831855
#define PI_2 1.5707964
#define PI_4 0.7853982
#define _1_PI 0.31830987
#define _2_PI 0.63661975
#define SQRT2 1.4142135
#define _1_SQRT2 0.70710677
#define PAD_COUNT 2

// macros
// 0x225c7e0: void MESSAGE(char *p)
#define MESSAGE(p) do { \
    ; \
} while (0)

// 0x225c7f0: void Log(void *p)
#define Log(p) do { \
    ; \
} while (0)

// 0x225c800: void Log_2(void *message, void *context)
#define Log_2(message, context) do { \
    ; \
} while (0)

// 0x225c810: void WARNING(char *p)
#define WARNING(p) do { \
    ; \
} while (0)

// 0x225c820: void ERROR(char *p)
#define ERROR(p) do { \
    ; \
} while (0)

// 0x225c830: void ASSERT(bool e)
#define ASSERT(e) do { \
    ; \
} while (0)

// 0x225c840: void ABORT(char *p)
#define ABORT(p) do { \
    ; \
} while (0)

// 0x225c860: f32 DEGtoRAD(f32 n)
#define DEGtoRAD(n) (n * 0.017453292)

// 0x225c880: f32 RADtoDEG(f32 n)
#define RADtoDEG(n) (n * 57.29578)
