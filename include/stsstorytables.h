#pragma once
#include "types.h"

typedef struct stsPlayerParam_t stsPlayerParam_t;
typedef struct stsStoryTable_t stsStoryTable_t;

struct stsStoryTable_t {
    s32 StartType;
    s32 Param1;
    s32 Param2;
    s32 Param3;
    s32 StoryNum;
    char *pProcName;
    s32 *pOnFlag;
    s32 OnFlagNums;
    s32 *pOnJump;
    s32 OnJumpNums;
    u32 *pOnDest;
    s32 OnDestNums;
    u8 *pOnMask1;
    u8 *pOnMask2;
    u32 *pMapOpen;
    stsPlayerParam_t *PlayerParam;
    char *StoryName;
};

struct stsPlayerParam_t {
    s32 Level;
    s32 Param[4];
    s32 Devil[12];
};

extern stsStoryTable_t *stsStoryTable;
