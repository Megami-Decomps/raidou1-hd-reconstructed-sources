#pragma once
#include "types.h"

typedef struct GameFileInfo_t GameFileInfo_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;

extern dds3ProcessID_t *MainPID;

void Init(void);
void End(void);
bool InstallCheck(void);
bool SaveStremingCheck(GameFileInfo_t *_info);
s32 InstallUi(bool _active);
s32 InstallUiGame(void);
void CallMes(void);
bool MesCheck(void);
bool MesEnd(void);
