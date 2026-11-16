#include "types.h"
#include "dat.h"
#include "frdream.h"
#include "localize.h"

// 0x1c94c70
char *frGetCode(void) {
  return GBWK->dream_code;
}

// 0x1c94d00
char *frGetLanguage(s32 Language) {
  char *v3;
  char *v4;
  u64 *v5;
  s64 v6;
  char *v7;
  char *v8;
  char *v9;
  char *v10;
  char *v11;
  char *v12;
  char *v13;
  char *v14;

  v3 = NewSpecific(string, 8u);
  v4 = "SYSTEM_L0005";
  v5 = v3;
  v3[0] = "SYSTEM_L0005";
  v6 = &v3[0];
  v7 = "SYSTEM_L0006";
  v5[5] = "SYSTEM_L0006";
  v8 = "SYSTEM_L0007";
  v5[6] = "SYSTEM_L0007";
  v9 = "SYSTEM_L0008";
  v5[7] = "SYSTEM_L0008";
  v10 = "SYSTEM_L0009";
  v5[8] = "SYSTEM_L0009";
  v11 = "SYSTEM_L0010";
  v5[9] = "SYSTEM_L0010";
  v12 = "SYSTEM_L0011";
  v5[10] = "SYSTEM_L0011";
  v13 = "SYSTEM_L0004";
  v5[11] = "SYSTEM_L0004";
  v14 = *(char **)(v6 + 8 * Language);
  return GetLocalizeText(v14, 1);
}
