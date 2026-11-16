#include "types.h"
#include "dds3kernelmain.h"
#include "switchsys.h"

static bool isInitialized;

// 0x22536b0
void Initialize(void) {
  if ((byte_5759249 & 1) != 0)
  {
    if (isInitialized)
      return;
LABEL_5:
    SetFocusHandlingMode(3, 0);
    isInitialized = 1;
    return;
  }
  if (!isInitialized)
    goto LABEL_5;
}

// 0x2253740
void BoostBegin(void) {
  SetCpuBoostMode(1, 0);
}

// 0x2253750
void BoostEnd(void) {
  SetCpuBoostMode(0, 0);
}

// 0x22535b0
void BeginKeyboard(void) {
  dds3PauseOn(0, 0);
  SetFocusHandlingMode(0, 0);
}

// 0x2253620
void EndKeyboard(void) {
  SetFocusHandlingMode(3, 0);
  dds3PauseOff(0);
}
