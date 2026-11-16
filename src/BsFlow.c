#include "types.h"
#include "BOSSACT.h"
#include "bsflow.h"
#include "sbtl.h"

// 0x1fdc450
void Init(void) {
  if (!wk)
    return;
  wk->bossflow = 0;
}

// 0x1fdc5b0
void SetAction(BOSSACT act) {
  if (!wk)
    return;
  wk->bossflow = act;
  wk->bossflow_camdone = 0;
}

// 0x1fdc500
void ClrAction(void) {
  if (!wk)
    return;
  wk->bossflow = 0;
}

// 0x1fdc680
bool IsAction(BOSSACT act) {
  if (!wk)
    return 0;
  return wk->bossflow == act;
}

// 0x1fdc740
void SetCamDone(void) {
  if (!wk)
    return;
  wk->bossflow_camdone = 1;
}

// 0x1fdc800
bool IsCamDone(void) {
  if (!wk)
    return 0;
  return wk->bossflow_camdone;
}
