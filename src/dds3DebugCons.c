#include "types.h"
#include "dds3debugcons.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

// 0x22844e0
dds3ProcessFunc_t dds3DebugConsProcess(dds3ProcessID_t *id) {
  return 0;
}

// 0x22844f0
void dds3DebugConsShutdown(dds3ProcessID_t *id) {
  ;
}

// 0x2284500
void dds3Printf(char *str, void *LegacyParamArray) {
  ;
}

// 0x2284510
void dds3DebugConsOpenPrintf(char *str, void *LegacyParamArray) {
  ;
}
