#pragma once
#include "types.h"

typedef struct SequenceParameter SequenceParameter;

void sBtlCountClear(void);
s32 sBtlCountGet(void);
void sBtlSelectStart(s32 movie_no);
bool sBtlIsContiune(void);
bool sBtlIsLevelContiune(void);
bool sBtlIsGiveUp(void);
void sBtlSave(SequenceParameter *sequenceParameter, bool restore);
void sBtlExecSet(s32 flg);
void sBtlLevelSet(s32 glvl);
s32 sBtlExec(void);
void sBtlClear(void);
bool sBtlIsSuperRaido(void);
bool sBtlIsSuperBoss(void);
s32 sBtlGetViceRaito(void);
s32 sBtlGetContinueRaito(s32 id);
