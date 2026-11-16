#pragma once
#include "types.h"
#include "kernel.h"

typedef struct SBTLMAIN_DATA SBTLMAIN_DATA;
typedef struct SceneParam_t SceneParam_t;
typedef struct SequenceParameter SequenceParameter;

void dds3AdminiCallSequence2(DDS3_ADMINI_LIST sequence, s32 data, s32 datasize, bool restore);
void dds3AdminiCallSequence4(DDS3_ADMINI_LIST sequence, SceneParam_t *data, s32 datasize, bool restore);
void dds3AdminiCallSequence5(DDS3_ADMINI_LIST sequence, SBTLMAIN_DATA *data, s32 datasize, bool restore);
void dds3AdminiCallSequence(DDS3_ADMINI_LIST sequence, SequenceParameter *sequenceParameter, bool restore);
void dds3AdminiExitSequence(void);
s32 dds3AdminiGetActiveSequence(void);
s32 dds3AdminiGetNextSequence(void);
s32 dds3AdminiGetPrevSequence(void);
s32 dds3AdminiGetPrevHistoryFlag(void);
void dds3InitAdmini(void);
