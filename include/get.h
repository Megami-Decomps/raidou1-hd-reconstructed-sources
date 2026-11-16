#pragma once
#include "types.h"

// macros
// 0x1d96200: s32 LEVEL(s32 _lev1, s32 _deflev1, s32 _lev2, s32 _deflev2)
#define LEVEL(_lev1, _deflev1, _lev2, _deflev2) ((deflev2 + deflev1) / 2 + 3)

// 0x1d96220: s32 HENI_LEVEL(s32 _lev1, s32 _deflev1, s32 _lev2, s32 _deflev2)
#define HENI_LEVEL(_lev1, _deflev1, _lev2, _deflev2) ((deflev2 + deflev1) / 2)

// 0x1d96240: s32 CYUUSEI(s32 _lev1, s32 _deflev1, s32 _lev2, s32 _deflev2)
#define CYUUSEI(_lev1, _deflev1, _lev2, _deflev2) (5 * (lev1 + lev2 - (deflev1 + deflev2)))

// 0x1d96260: s32 CUSTOM_CYUUSEI(s32 _cyuusei1, s32 _cyuusei2)
#define CUSTOM_CYUUSEI(_cyuusei1, _cyuusei2) ((cyuusei2 + cyuusei1) / 2)
