#pragma once
#include "types.h"
#include "SaveResultType.h"
#include "kernel.h"

typedef enum {
    LoadResultType_Success = 0,
    LoadResultType_DataBroken = 1,
    LoadResultType_Other = 2,
} LoadResultType;

typedef struct FsSaveData FsSaveData;
typedef struct SAVEDATA SAVEDATA;
typedef struct SequenceParameter SequenceParameter;

struct FsSaveData {
    SAVEDATA *saveData;
    SaveResultType saveResultType;
    LoadResultType loadResultType;
};

extern bool DebugSign;
extern FsSaveData *saveData;
extern s32 FrameID;
extern bool PauseSign;
extern u32 FrameCount;

void dds3SetMainThred(void);
void dds3NewGameStart(void);
u32 dds3GetKernelCount(void);
s32 dds3GetFrameID(void);
void dds3PauseOn(u32 frame, char *id);
void dds3PauseOff(char *id);
bool dds3IsPause(void);
void dds3SoftResetOn(void);
void dds3SoftResetOff(void);
void KernelSetDebugSign(bool bFlag);
void *KernelMain(DDS3_ADMINI_LIST startSequence, SequenceParameter *sequenceParameter);
void dds3UnityInit(void);
