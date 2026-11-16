#include "types.h"
#include "dat.h"
#include "evtbit.h"
#include "evtmoon.h"

// 0x1a11690
void evtInitGlobalWork(void) {
  Clear(GBWK->EventBit, 0, 512, 0);
  evtMoonSetAge(0);
  evtMoonDisableDraw(1);
  evtMoonDisableCalc();
}

// 0x1a11780
void evtBitAllOff(void) {
  Clear(GBWK->EventBit, 0, 512, 0);
}

// 0x1a117f0
void evtBitAllOff_FieldDebug(void) {
  s32 v1;
  u32 i;
  u32 v3;
  s32 v4;
  s64 v5;
  u32 j;
  u32 v8;
  s32 v9;
  s64 v10;

  v1 = (u8)byte_5755E7B;
  for (i = 0; i != 3072; ++i)
  {
    if (v1)
    {
      goto LABEL_2;
    }
    else
    {
      v1 = 1;
      goto LABEL_2;
    }
    v1 = (u8)byte_5755E7B;
LABEL_2:
    v3 = i >> 5;
    v4 = 1 << i;
    v5 = (s64)GBWK->EventBit + 4 * v3;
    *(u32 *)(v5 + 32) &= ~v4;
  }
  for (j = 3328; j != 0x4000; ++j)
  {
    if (v1)
    {
      goto LABEL_9;
    }
    else
    {
      v1 = 1;
      goto LABEL_9;
    }
    v1 = (u8)byte_5755E7B;
LABEL_9:
    v8 = j >> 5;
    v9 = 1 << j;
    v10 = (s64)GBWK->EventBit + 4 * v8;
    *(u32 *)(v10 + 32) &= ~v9;
  }
}

// 0x1a11920
void evtBitKityouItemAdd(s32 _no) {
  s32 v4;

  v4 = no - 2160;
  if (!datCheckEventItem(v4))
    return;
  UpdateGetList(GBWK->sortSave, v4, 1, 0);
}

// 0x1a119f0
void evtBitOn(s32 no) {
  s32 v4;
  s64 v6;

  if (no)
  {
    if ((u32)(no - 2618) < 0xFFFFFFC6)
      goto LABEL_8;
    v4 = no - 2160;
    if (!datCheckEventItem(v4))
      goto LABEL_8;
    goto LABEL_14;
    if (!datCheckEventItem(v4))
    {
LABEL_8:
LABEL_10:
      v6 = (s64)GBWK->EventBit + 4 * (no / 32);
      *(u32 *)(v6 + 32) |= 1 << no;
      return;
    }
LABEL_14:
    UpdateGetList(GBWK->sortSave, v4, 1, 0);
    goto LABEL_10;
  }
}

// 0x1a11b40
void evtBitOff(s32 no) {
  s64 v4;

  v4 = (s64)GBWK->EventBit + 4 * (no / 32);
  *(u32 *)(v4 + 32) &= ~(1 << no);
}

// 0x1a11be0
void evtBitSet(s32 no, bool bBool) {
  s64 v5;

  if (bBool)
  {
    sub_1A21FE0(no, 0);
    return;
  }
  v5 = (s64)GBWK->EventBit + 4 * (no / 32);
  *(u32 *)(v5 + 32) &= ~(1 << no);
}

// 0x1a0b200
bool evtBitCheck(s32 no) {
  _BOOL4 v4;

  if (no)
  {
    return ((u32)GBWK->EventBit[no / 32] >> no) & 1;
  }
  else
  {
    LOBYTE(v4) = 0;
  }
  return v4;
}
