#include "types.h"
#include "SKLID.h"
#include "cmp.h"
#include "fld.h"
#include "localize.h"

u8 sys[2249];
char *mskTbl;

// 0x1d93fa0
bool cmpChkSousaSkill(SKLID _sklID) {
  return (u32)(sklID - 1408) < 0xF;
}

// 0x1d93fb0
char *cmpGetSousaSklName(s32 id, bool labelDraw) {
  char *v5;

  if (id != 255)
  {
    v5 = *(char **)(*(u64 *)&gActionWinAlpha + 8 * id + 32);
    if (!labelDraw)
      goto LABEL_4;
    return v5;
  }
  v5 = "CMP_STATUS_L0018";
  if (labelDraw)
    return v5;
LABEL_4:
  return GetLocalizeText(v5, 1);
}

// 0x1d940a0
char *cmpGetMskHelpFont(s32 id, bool labelDraw) {
  char *v5;

  if (id != 255)
  {
    v5 = mskTbl[id];
    if (!labelDraw)
      goto LABEL_4;
    return v5;
  }
  v5 = "CMP_HELP_L0029";
  if (labelDraw)
    return v5;
LABEL_4:
  return GetLocalizeText(v5, 1);
}

// 0x1d94190
char *cmpSousaSklName(s32 id, bool label) {
  bool v6;
  s32 v7;

  v6 = label;
  v7 = id;
  return cmpGetSousaSklName(v7, v6);
}

// 0x1d94220
char *cmpMskHelp(s32 id, bool label) {
  bool v6;
  s32 v7;

  v6 = label;
  v7 = id;
  return cmpGetMskHelpFont(v7, v6);
}
