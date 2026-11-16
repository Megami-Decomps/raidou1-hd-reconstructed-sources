#pragma once
#include "types.h"
#include "libsdf.h"

extern s32 **sbtl_shortCutDefault;

void cfgBtnTagConfigLoad(void);
char *cfgGetBtnTagConfig(char *text_label, char *org_text);
char *cfgGetBtnTagConfigSingle(char *btntag, char *text_label);
s32 cfgGetPadToKeyID(SDF_PADMAP pad);
void cfgBtnReWrite(void);
s32 *cfgGetConfigInitTable(s32 tabpos);
s32 *cfgGetBattleShortCutDefault(s32 _key);
void cfgSystemToGwCopy(s32 **config_data);
void cfgGwToSystemCopy(s32 **config_data);
void cfgInitGlobalWork(void);
void cfgInitSbtlShortCut(void);
s32 cfgChkFlagChange(void);
void cfgCopyFlagGblToBak(void);
void cfgCopyFlagBakToGbl(void);
void cfgSetChange(void);
s32 cfgScrCmd_GET_CONFIG_GAME(void);
s32 cfgGetConfigAUDIO(s32 type, s32 *config_data);
s32 cfgGetConfigGAME(s32 type, s32 *config_data);
s32 cfgGetConfigGRAPHICS(s32 type, s32 *config_data);
s32 cfgGetConfigDISPLAY(s32 type, s32 *config_data);
s32 cfgGetConfigGAMEPAD(s32 type, s32 *config_data);
s32 cfgGetConfigKEYBOARD(s32 type);
void cfgSetConfigAUDIO(s32 type, s32 val, s32 *config_data);
void cfgSetConfigGAME(s32 type, s32 val, s32 *config_data);
void cfgSetConfigGRAPHICS(s32 type, s32 val, s32 *config_data);
void cfgSetConfigDISPLAY(s32 type, s32 val, s32 *config_data);
void cfgSetConfigGAMEPAD(s32 type, s32 val, s32 *config_data);
void cfgSetConfigKEYBOARD(s32 type, s32 val, s32 *config_data);
