#pragma once
#include "types.h"
#include "SKLID.h"

extern u8 sys[2249];
extern char *mskTbl;

bool cmpChkSousaSkill(SKLID _sklID);
char *cmpGetSousaSklName(s32 id, bool labelDraw);
char *cmpGetMskHelpFont(s32 id, bool labelDraw);
char *cmpSousaSklName(s32 id, bool label);
char *cmpMskHelp(s32 id, bool label);
