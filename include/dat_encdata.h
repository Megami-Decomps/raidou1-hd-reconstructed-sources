#pragma once
#include "types.h"

// macros
// 0x18f4e50: u32 MAKE(u32 x, u32 y, u32 z)
#define MAKE(x, y, z) ((y << 16) | (x << 24) | z)
