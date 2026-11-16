#pragma once
#include "types.h"

#define AISHIFT 20
#define AICHK_IDMASK 4293918720
#define AICHK_ARGMASK 1048575

// macros
// 0x1dd5220: s32 NONE(void)
#define NONE() (0)

// 0x1dd5230: s32 MYHP(s32 n)
#define MYHP(n) (n | 0x100000)

// 0x1dd5240: s32 AREA_E(s32 n)
#define AREA_E(n) (n | 0x200000)

// 0x1dd5250: s32 MYHPU(s32 n)
#define MYHPU(n) (n | 0x300000)

// 0x1dd5260: s32 P_AREANUM_A(s32 n)
#define P_AREANUM_A(n) (n | 0x400000)

// 0x1dd5270: s32 HP(s32 n)
#define HP(n) (n | 0x500000)

// 0x1dd5280: s32 MYHP_LESS(s32 n)
#define MYHP_LESS(n) (n | 0x600000)

// 0x1dd5290: s32 AREA_EU(s32 n)
#define AREA_EU(n) (n | 0x700000)

// 0x1dd52a0: s32 BADST(s32 n)
#define BADST(n) (n | 0x800000)

// 0x1dd52b0: s32 BTLTIME(s32 n)
#define BTLTIME(n) (n | 0x900000)

// 0x1dd52c0: s32 CHKSKL(s32 n)
#define CHKSKL(n) (n | 0xA00000)

// 0x1dd52d0: s32 CHKSKL_R(s32 n)
#define CHKSKL_R(n) (n | 0xB00000)

// 0x1dd52e0: s32 USESKL(s32 n)
#define USESKL(n) (n | 0xC00000)

// 0x1dd52f0: s32 USESKL_R(s32 n)
#define USESKL_R(n) (n | 0xD00000)

// 0x1dd5300: s32 USESKLG(s32 n)
#define USESKLG(n) (n | 0xE00000)

// 0x1dd5310: s32 USESKLG_R(s32 n)
#define USESKLG_R(n) (n | 0xF00000)

// 0x1dd5320: s32 MOON(s32 n)
#define MOON(n) (n | 0x1000000)

// 0x1dd5330: s32 BADST_E(s32 n)
#define BADST_E(n) (n | 0x1100000)

// 0x1dd5340: s32 KAJYA(s32 n)
#define KAJYA(n) (n | 0x1200000)

// 0x1dd5350: s32 KAJYA_E(s32 n)
#define KAJYA_E(n) (n | 0x1300000)

// 0x1dd5360: s32 NKAJYA(s32 n)
#define NKAJYA(n) (n | 0x1400000)

// 0x1dd5370: s32 OTAKE(s32 n)
#define OTAKE(n) (n | 0x1500000)

// 0x1dd5380: s32 OTAKE_E(s32 n)
#define OTAKE_E(n) (n | 0x1600000)

// 0x1dd5390: s32 NOTAKE(s32 n)
#define NOTAKE(n) (n | 0x1700000)

// 0x1dd53a0: s32 MESHI(s32 n)
#define MESHI(n) (n | 0x1800000)

// 0x1dd53b0: s32 HANGEKI(s32 n)
#define HANGEKI(n) (n | 0x1900000)

// 0x1dd53c0: s32 RAIDOENMY(s32 n)
#define RAIDOENMY(n) (n | 0x1A00000)

// 0x1dd53d0: s32 HPP(s32 n)
#define HPP(n) (n | 0x1B00000)

// 0x1dd53e0: s32 TETORAKANE(s32 n)
#define TETORAKANE(n) (n | 0x1C00000)

// 0x1dd53f0: s32 CNT(s32 n)
#define CNT(n) (n | 0x1D00000)

// 0x1dd5400: s32 YARARE(s32 n)
#define YARARE(n) (n | 0x1E00000)

// 0x1dd5410: s32 MYLOCKON(s32 n)
#define MYLOCKON(n) (n | 0x1F00000)

// 0x1dd5420: s32 SPIRIT(s32 n)
#define SPIRIT(n) (n | 0x2000000)

// 0x1dd5430: s32 RAIDOHP(s32 n)
#define RAIDOHP(n) (n | 0x2100000)

// 0x1dd5440: s32 WEAKATK(s32 n)
#define WEAKATK(n) (n | 0x2200000)

// 0x1dd5450: s32 WEAKOFF(s32 n)
#define WEAKOFF(n) (n | 0x2300000)

// 0x1dd5460: s32 RITU(s32 n)
#define RITU(n) (n | 0x2400000)

// 0x1dd5470: s32 RAIDOAREA_E(s32 n)
#define RAIDOAREA_E(n) (n | 0x2500000)
