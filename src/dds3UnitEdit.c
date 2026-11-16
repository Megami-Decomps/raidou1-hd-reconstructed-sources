#include "types.h"
#include "dds3unitedit.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

static dds3ProcessID_t *gPID;

// 0x22a3100
dds3ProcessFunc_t UnitEdit(dds3ProcessID_t *ID) {
  return 0;
}

// 0x22a3110
void dds3ExitUnitEdit(dds3ProcessID_t *ID) {
  ;
}
