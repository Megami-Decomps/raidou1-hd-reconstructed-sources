#pragma once
#include "types.h"

typedef enum {
    Glvl_SuperEASY = 0,
    Glvl_EASY = 1,
    Glvl_NORMAL = 2,
    Glvl_HARD = 3,
    Glvl_RAIDOU = 4,
    Glvl_MAX = 5,
} Glvl;

typedef enum {
    LTYPE_LEVEL000 = 0,
    LTYPE_LEVEL001 = 1,
    LTYPE_LEVEL002 = 2,
    LTYPE_LEVEL003 = 3,
    LTYPE_LEVEL004 = 4,
    LTYPE_LEVEL005 = 5,
    LTYPE_LEVEL006 = 6,
    LTYPE_LEVEL007 = 7,
    LTYPE_LEVEL008 = 8,
    LTYPE_LEVEL009 = 9,
    LTYPE_LEVEL010 = 10,
    LTYPE_LEVEL011 = 11,
    LTYPE_LEVEL012 = 12,
    LTYPE_LEVEL013 = 13,
    LTYPE_LEVEL014 = 14,
    LTYPE_LEVEL015 = 15,
    LTYPE_LEVEL016 = 16,
    LTYPE_LEVEL017 = 17,
    LTYPE_LEVEL018 = 18,
    LTYPE_LEVEL019 = 19,
    LTYPE_LEVEL020 = 20,
    LTYPE_LEVEL021 = 21,
    LTYPE_LEVEL022 = 22,
    LTYPE_LEVEL023 = 23,
    LTYPE_LEVEL024 = 24,
    LTYPE_LEVEL025 = 25,
    LTYPE_LEVEL026 = 26,
    LTYPE_LEVEL027 = 27,
    LTYPE_LEVEL028 = 28,
    LTYPE_LEVEL029 = 29,
    LTYPE_LEVEL030 = 30,
    LTYPE_LEVEL031 = 31,
    LTYPE_LEVEL032 = 32,
    LTYPE_LEVEL033 = 33,
    LTYPE_LEVEL034 = 34,
    LTYPE_LEVEL035 = 35,
    LTYPE_LEVEL036 = 36,
    LTYPE_LEVEL037 = 37,
    LTYPE_LEVEL038 = 38,
    LTYPE_MAX = 39,
} LTYPE;

extern char *menuText;
extern char *helpText;
extern char *selectText;
extern char *huuma_selectText;
extern s32 **minMaxPar;

void LevelDataLoad(void);
f32 GetLevelData(LTYPE type, Glvl lvl);
f32 ConvLevelValue(LTYPE type, f32 val);
char *GetSelectText(s32 _setPar, s32 _value);
s32 ParToGameSet(s32 _setPar);
void InitSelectCnt(void);
void Init(void);
bool LevelDisp(void);
void Update(void);
void Draw(void);
