#include "types.h"
#include "sbtlshadow.h"
#include "sbtlvisual.h"

#define SBTLSDW_SDWDEPTH -0.15

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

// 0x1fc86a0
bool sBtlDrawShadow(SBTLUNIT_WORK *wk) {
  u16 major;
  s32 minor;

  major = wk->major;
  minor = wk->minor;
  return sBtlGetVisualData(major, minor) != 0;
}
