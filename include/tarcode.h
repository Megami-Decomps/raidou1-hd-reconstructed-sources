#pragma once
#include "types.h"

#define IDMASK 4290772992
#define ARGMASK 4194303

extern s32 AISHIFT;

// macros
// 0x18efc00: s32 BAD(s32 n)
#define BAD(n) ((2 << AISHIFT) | n)

// 0x18efc80: s32 ID(s32 n)
#define ID(n) ((3 << AISHIFT) | n)

// 0x18f00f0: s32 NOTBAD(s32 n)
#define NOTBAD(n) ((14 << AISHIFT) | n)

// 0x18f0250: s32 REFRACT(s32 n)
#define REFRACT(n) ((17 << AISHIFT) | n)

// 0x18f0340: s32 ATTR_N(s32 n)
#define ATTR_N(n) ((19 << AISHIFT) | n)

// 0x18f0430: s32 CNT_HPMIN(s32 n)
#define CNT_HPMIN(n) ((21 << AISHIFT) | n)
