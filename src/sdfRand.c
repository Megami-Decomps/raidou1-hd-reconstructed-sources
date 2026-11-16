#include "types.h"
#include "sdfrand.h"
#include "sdftime.h"

typedef struct sdfRandCB_t sdfRandCB_t;

sdfRandCB_t *sdfDefaultRandCB;
static u16 *monthTbl;

// 0x2281960
u32 sdfGet(sdfRandCB_t *aCB) {
  u32 *v;
  u32 v5;
  s32 v6;
  u32 v7;
  s32 v8;

  if (!aCB)
  {
    aCB = sdfDefaultRandCB;
  }
  v = aCB->v;
  v5 = v[0];
  v6 = *(u64 *)v >> 30;
  v7 = v[2];
  v8 = *(u64 *)&v[2] >> 31;
  v[2] = v[1];
  v[3] = v7;
  v[0] = v8 ^ v6;
  v[1] = v5;
  return v8 ^ v6;
}

// 0x22819f0
f32 sdfGetFloat(sdfRandCB_t *aCB) {
  u32 *v;
  u32 v6;
  u32 v7;
  s32 v8;
  s32 v9;
  s32 v10;

  if (!aCB)
    aCB = sdfDefaultRandCB;
  v = aCB->v;
  v6 = v[0];
  v7 = v[2];
  v8 = *(u64 *)v >> 30;
  v9 = *(u64 *)&v[2] >> 31;
  v[2] = v[1];
  v[3] = v7;
  v10 = v9 ^ v8;
  v[0] = v10;
  v[1] = v6;
  return (f32)(v10 & 0xFFFFFF) * 5.9604645e-08;
}

// 0x2281ae0
u32 sdfGetInt(sdfRandCB_t *aCB, u32 aLimit) {
  u32 *v;
  u32 v8;
  s32 v9;
  u32 v10;
  s32 v11;
  u32 v12;

  if (!aCB)
    aCB = sdfDefaultRandCB;
  v = aCB->v;
  v8 = v[0];
  v9 = *(u64 *)v >> 30;
  v10 = v[2];
  v11 = *(u64 *)&v[2] >> 31;
  v[2] = v[1];
  v[3] = v10;
  v12 = v11 ^ v9;
  v[0] = v12;
  v[1] = v8;
  return v12 % aLimit;
}

// 0x2281bd0
void Init(sdfRandCB_t *aCB, u32 aSeed) {
  u32 *v;
  u32 v7;
  u64 v8;
  u32 v9;

  if (!aCB)
  {
    aCB = sdfDefaultRandCB;
  }
  v = aCB->v;
  HIDWORD(v8) = aSeed ^ 0xAED1A0C;
  LODWORD(v8) = aSeed ^ 0xAED1A0C;
  v7 = v8 >> 8;
  v[0] = aSeed ^ 0xAED1A0C;
  v[1] = v7;
  HIDWORD(v8) = v7 ^ 0xAA5A02FE;
  LODWORD(v8) = v7 ^ 0xAA5A02FE;
  v9 = v8 >> 8;
  HIDWORD(v8) = v9 ^ 0x11BE81C7;
  LODWORD(v8) = v9 ^ 0x11BE81C7;
  v[2] = v9;
  v[3] = v8 >> 8;
}

// 0x2281c80
void sdfInitByTime(sdfRandCB_t *aCB) {
  sdfTime_t *v3;
  s32 year;
  s32 day;
  s32 hour;
  s32 min;
  s32 sec;
  s32 v10;
  u32 *v;
  u32 v13;
  u64 v14;
  u32 v15;
  sdfTime_t *aTime;

  aTime = 0;
  Get(aTime);
  v3 = aTime;
  year = aTime->year;
  v3 = aTime;
  day = v3->day;
  hour = v3->hour;
  min = v3->min;
  sec = v3->sec;
  v10 = *((u16 *)&monthTbl->max_length + v3->month + 3);
  if (!aCB)
  {
    aCB = sdfDefaultRandCB;
  }
  v = aCB->v;
  HIDWORD(v14) = (sec + 60 * (min + 60 * (hour + 24 * (v10 + 366 * year + day))) + 2128295040) ^ 0xAED1A0C;
  LODWORD(v14) = HIDWORD(v14);
  v13 = v14 >> 8;
  v[0] = HIDWORD(v14);
  v[1] = v13;
  HIDWORD(v14) = v13 ^ 0xAA5A02FE;
  LODWORD(v14) = v13 ^ 0xAA5A02FE;
  v15 = v14 >> 8;
  HIDWORD(v14) = v15 ^ 0x11BE81C7;
  LODWORD(v14) = v15 ^ 0x11BE81C7;
  v[2] = v15;
  v[3] = v14 >> 8;
}
