#pragma once
#include "types.h"

#define MASK 65535

// macros
// 0x18f3a20: s32 SN(s32 n)
#define SN(n) (n | 0x10000)

// 0x18f3a30: s32 EVENT(s32 n)
#define EVENT(n) (n | 0x20000)
