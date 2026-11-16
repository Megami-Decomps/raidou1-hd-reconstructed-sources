#include "types.h"
#include "achievement.h"
#include "scr.h"
#include "slmain.h"

#define ACHIVEMENT_MAX 42
#define UNLOCK_WAIT 5

void *_achievementTbl_k__BackingField;
static void *progressChkList;
static s32 *storyTrophy;

static void Log(char *log);

// 0x1d690d0
static void Log(char *log) {
  Log(log);
}

// 0x1d69160
void Initialize(void *gameObj) {
  Il2CppObject *v2;

  v2 = Allocate(Project_AchivementDummyID);
  _ctor(v2, 0);
  _achievementTbl_k__BackingField = (void *)v2;
}

// 0x1d69250
void ConvertDataUnlock(void) {
  ;
}

// 0x1d69260
void ConvertDataStoryUnlock(s32 *ids) {
  s64 v3;
  s32 v4;
  void *v7;
  u64 v8;
  s32 v9;

  if (SLODWORD(ids->max_length) >= 1)
  {
    v3 = 0;
    v4 = 0;
    do
    {
      v8 = (u32)ids[v3];
      if ((s32)v8 <= 0)
        v9 = -(-(s32)v8 & 7);
      else
        LOBYTE(v9) = v8 & 7;
      if (SLODWORD(SystemWork->trophyUnlock->max_length) > (s64)(v8 >> 3))
      {
        if (((1 << v9) & SystemWork->trophyUnlock[v8 >> 3]) != 0)
        {
          ++v4;
          v7 = Allocate(System_Action_int_);
          __ctor(v7, 0, Method_Project_Achievement_Unlock___83873832, 0);
          AddFunc(manager, v7, v8, 0);
        }
      }
      ++v3;
    }
    while (v3 < SLODWORD(ids->max_length));
    if (v4 >= 1)
    {
      StartActions(manager, 5.0, 0);
    }
  }
}

// 0x1d69460
void UnlockDataUpdate(s32 _id) {
  signed s64 v4;
  s8 *trophyUnlock;
  char v6;

  v4 = (u64)(u32)id >> 3;
  if (id <= 0)
    id = -(-id & 7);
  else
    LOBYTE(id) = id & 7;
  trophyUnlock = SystemWork->trophyUnlock;
  if (SLODWORD(trophyUnlock->max_length) <= v4)
    return;
  v6 = id & 0x1F;
  trophyUnlock = SystemWork->trophyUnlock;
  trophyUnlock[v4] |= 1 << v6;
}

// 0x1d69550
bool UnlockDataCheck(s32 _id) {
  s64 v4;
  s8 *trophyUnlock;
  char v6;

  v4 = (u32)id >> 3;
  if (id <= 0)
    id = -(-id & 7);
  else
    LOBYTE(id) = id & 7;
  trophyUnlock = SystemWork->trophyUnlock;
  if (SLODWORD(trophyUnlock->max_length) <= v4)
    return 0;
  v6 = id & 0x1F;
  trophyUnlock = SystemWork->trophyUnlock;
  return (trophyUnlock[v4] & (0x1000000 << v6 >> 24)) != 0;
}

// 0x1d69640
void Unlock(s32 id) {
  signed s64 v5;
  s8 *trophyUnlock;
  char v7;

  v5 = (u64)(u32)id >> 3;
  if (id <= 0)
    id = -(-id & 7);
  else
    LOBYTE(id) = id & 7;
  trophyUnlock = SystemWork->trophyUnlock;
  if (SLODWORD(trophyUnlock->max_length) <= v5)
    return;
  v7 = id & 0x1F;
  trophyUnlock = SystemWork->trophyUnlock;
  trophyUnlock[v5] |= 1 << v7;
}

// 0x1d69790
void ProgressUnlock(s32 id, s64 now, s64 max) {
  ;
}

// 0x1d697a0
void ProgressUnlock_2(s32 id, s32 value) {
  ;
}

// 0x1d697b0
void ProgressUnlock_3(char *id, s64 now, s64 max) {
  ;
}

// 0x1d697c0
void ProgressUnlock_4(char *id, s32 value) {
  ;
}

// 0x1d697d0
void Unlock_2(char *id) {
  ;
}

// 0x1d697e0
s32 Unlock_3(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  Unlock(IntPara);
  return 1;
}
