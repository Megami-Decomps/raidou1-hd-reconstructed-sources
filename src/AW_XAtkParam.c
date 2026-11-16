#include "types.h"
#include "aw.h"
#include "aw_xatkparam.h"

typedef struct AW_WORK_t AW_WORK_t;

// 0x1ebbb40
void Init(void) {
  ;
}

// 0x1ebbb50
s32 Add(void) {
  s32 v1;
  AW_WORK_t *AW;
  char *v3;

  v1 = Add(250, 0.0, 0.0, 0.0, 0, 0, 0, 4);
  AW = GetAW(v1);
  v3 = "AW_XAtkParam";
  AW->DbgStr = "AW_XAtkParam";
  return v1;
}

// 0x1ebbc00
void Delete(AW_WORK_t *aWork) {
  s32 Idx;

  Idx = aWork->Idx;
  DelAW(Idx, 0);
}
