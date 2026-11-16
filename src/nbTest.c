#include "types.h"
#include "nbtest.h"

typedef struct bDrawText bDrawText;

// 0x194f3f0
void PreBtlMenuObj(s32 idx) {
  ;
}

// 0x194f400
void btlDrawTagLink(bDrawText *setText, bDrawText *dt, s32 idx) {
  ;
}

// 0x194f410
bDrawText *btlDevPrintf(s32 aX, s32 aY, s32 aZ, s32 color, char *aStr, s32 f) {
  bDrawText *v9;

  v9 = Allocate(bDrawText);
  v9->DrawTxt = aStr;
  v9->color = color;
  return v9;
}

// 0x194f490
void SetBtlMenuObj(s32 idx) {
  ;
}

// 0x194f4a0
void deleteBtlMenuObj(s32 idx) {
  ;
}
