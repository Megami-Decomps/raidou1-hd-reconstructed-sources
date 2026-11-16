#pragma once
#include "types.h"

extern void *_achievementTbl_k__BackingField;

void Initialize(void *gameObj);
void ConvertDataUnlock(void);
void ConvertDataStoryUnlock(s32 *ids);
void UnlockDataUpdate(s32 _id);
bool UnlockDataCheck(s32 _id);
void Unlock(s32 id);
void ProgressUnlock(s32 id, s64 now, s64 max);
void ProgressUnlock_2(s32 id, s32 value);
void ProgressUnlock_3(char *id, s64 now, s64 max);
void ProgressUnlock_4(char *id, s32 value);
void Unlock_2(char *id);
s32 Unlock_3(void);
