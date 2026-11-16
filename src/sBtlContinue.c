#include "types.h"
#include "achievement.h"
#include "cfg.h"
#include "dat.h"
#include "dds3adminiprocess.h"
#include "fld.h"
#include "movie.h"
#include "sbtlcontinue.h"
#include "sbtlencount.h"
#include "sbtlscene.h"
#include "sdfsound.h"
#include "slmain.h"

typedef struct AITABLE AITABLE;
typedef struct CONTINUE_PARAM CONTINUE_PARAM;
typedef struct SAVEDATA SAVEDATA;
typedef struct SBTLMAIN_DATA SBTLMAIN_DATA;
typedef struct SequenceParameter SequenceParameter;

struct CONTINUE_PARAM {
    s32 start;
    s32 exec;
    SBTLMAIN_DATA *data;
    bool restore;
    SAVEDATA *saveData;
    s32 gamelevel;
};

struct AITABLE {
    s32 ec;
    s32 id;
    s32 **tbl;
};

static CONTINUE_PARAM *continuewk;
static s32 continue_count;
static bool dlc_battle;
static s32 dlc_kiretu;
static s32 zakuro_Idx;
static s32 **vice_up_raito;
static AITABLE *aitable;

static bool IsBoss(void);

// 0x2060110
void sBtlCountClear(void) {
  continue_count = 0;
  return;
}

// 0x2060190
s32 sBtlCountGet(void) {
  return continue_count;
}

// 0x2060210
void sBtlSelectStart(s32 movie_no) {
  char *v4;

  if (movie_no != 14)
    return;
  v4 = "bt_continue";
  Load(Dependent, v4, v4);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  LoadSceneAsync(_Ctrl_k__BackingField, "UI_continue", 0);
  *(u64 *)&continuewk->start = 1;
}

// 0x20603c0
bool sBtlIsContiune(void) {
  if (!continuewk->start)
    return 0;
  return continuewk->exec == 1;
}

// 0x2060480
bool sBtlIsLevelContiune(void) {
  if (!continuewk->start)
    return 0;
  return continuewk->exec == 2;
}

// 0x2060540
bool sBtlIsGiveUp(void) {
  if (!continuewk->start)
    return 0;
  return continuewk->exec == 3;
}

// 0x2060600
void sBtlSave(SequenceParameter *sequenceParameter, bool restore) {
  bool v7;
  CONTINUE_PARAM *continuewk_local;
  SBTLMAIN_DATA *v9;
  s32 v12;
  CONTINUE_PARAM *v14;
  s32 nowKiretsuIdx;
  char *player_first;
  char *v22;
  char *player_family;
  char *v28;
  dds3GlobalWork_tag *p_suspendBuff;
  dds3GlobalWork_t *GBWK_local;
  char *v35;
  GameFileInfo_t *GameFileInfo;
  char *v38;
  dds3GlobalWork_t *v40;
  char *v41;
  GameFileInfo_t *v43;
  char *v44;

  if (sequenceParameter)
  {
    v7 = restore;
    continuewk_local = continuewk;
    v9 = Allocate(SBTLMAIN_DATA);
    _ctor(v9, 0);
    continuewk_local->data = v9;
    ClassCopy(sequenceParameter->CallData5, continuewk->data, 0);
    continuewk->restore = v7;
    if ((sBtlGetDlcMapNo() & 0xFFFFFFFE) != 4)
    {
      dlc_battle = 0;
LABEL_19:
      zakuro_Idx = -1;
      nowKiretsuIdx = fldGb->nowKiretsuIdx;
      if (nowKiretsuIdx < 0)
      {
        goto LABEL_22;
      }
      zakuro_Idx = nowKiretsuIdx;
LABEL_22:
      player_first = GBWK->player_first;
      if (SLODWORD(slUnicodeToIndexByte2(player_first)->max_length) < 21)
      {
        goto LABEL_25;
      }
      GBWK_local = GBWK;
      v35 = "　　　　";
      GBWK_local->player_first = "　　　　";
LABEL_25:
      v22 = GBWK->GameFileInfo->player_first;
      if (SLODWORD(slUnicodeToIndexByte2(v22)->max_length) < 21)
      {
        goto LABEL_28;
      }
      GameFileInfo = GBWK->GameFileInfo;
      v38 = "　　　　";
      GameFileInfo->player_first = "　　　　";
LABEL_28:
      player_family = GBWK->player_family;
      if (SLODWORD(slUnicodeToIndexByte2(player_family)->max_length) < 21)
      {
        goto LABEL_31;
      }
      v40 = GBWK;
      v41 = "　　　　";
      v40->player_family = "　　　　";
LABEL_31:
      v28 = GBWK->GameFileInfo->player_family;
      if (SLODWORD(slUnicodeToIndexByte2(v28)->max_length) < 21)
      {
LABEL_34:
        Init(&continuewk->saveData->suspendBuff, 0);
        p_suspendBuff = &continuewk->saveData->suspendBuff;
        Backup(p_suspendBuff, GBWK);
        return;
      }
      v43 = GBWK->GameFileInfo;
      v44 = "　　　　";
      v43->player_family = "　　　　";
      goto LABEL_34;
    }
    v12 = fldGb->nowKiretsuIdx;
    dlc_kiretu = v12;
    dlc_battle = 1;
    goto LABEL_19;
  }
  v14 = continuewk;
  v14->data = 0;
}

// 0x2060c10
void sBtlExecSet(s32 flg) {
  void *achievementTbl_k__BackingField;
  Project_DefineAchievementID_string__c *klass;
  s64 v8;
  Project_DefineAchievementID_string__c **p_offset;
  s64 v10;
  char *v11;

  continuewk->exec = flg;
  if (flg == 1)
    goto LABEL_4;
  return;
  if (flg == 1)
  {
LABEL_4:
    achievementTbl_k__BackingField = _achievementTbl_k__BackingField;
    klass = achievementTbl_k__BackingField->klass;
    v8 = *(u16 *)&achievementTbl_k__BackingField->klass->_2.rank;
    if (!*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
      goto LABEL_18;
    goto LABEL_15;
    if (!*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
    {
LABEL_18:
      v10 = sub_4227F4(achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0x19u);
LABEL_20:
      v11 = (*v10)(achievementTbl_k__BackingField, *(u64 *)(v10 + 8));
      Unlock_2(v11);
      return;
    }
LABEL_15:
    p_offset = &klass->_1.interfaceOffsets->offset;
    while (*(p_offset - 1) != Project_DefineAchievementID_string_)
    {
      p_offset += 2;
      if (!--v8)
        goto LABEL_18;
    }
    v10 = &klass->vtable[*(u32 *)p_offset + 25];
    goto LABEL_20;
  }
}

// 0x2060dd0
void sBtlLevelSet(s32 glvl) {
  continuewk->gamelevel = glvl;
}

// 0x2060e40
s32 sBtlExec(void) {
  CONTINUE_PARAM *v3;
  CONTINUE_PARAM *v6;
  SAVEDATA *saveData;
  dds3GlobalWork_tag *p_suspendBuff;
  SequenceParameter *v13;
  SBTLMAIN_DATA *data;
  s32 *p_dlc_kiretu;
  s32 gamelevel;

  if (continuewk->exec != 1)
  {
LABEL_13:
    v3 = continuewk;
    if (v3->exec != 2)
    {
LABEL_21:
      if (!continuewk->data)
        return 3;
      sBtlInitSceneRndEnc_IDFlag();
      movieStop(0);
      p2sdSndStopAll();
      v6 = continuewk;
      *(u64 *)&v6->start = 0;
      ret_field_scene = 0;
      return 3;
    }
    if (!v3->start)
      goto LABEL_21;
    return 2;
  }
  if (!continuewk->start)
    goto LABEL_13;
  if (!continuewk->data)
    return 3;
  movieStop(0);
  saveData = continuewk->saveData;
  p_suspendBuff = &saveData->suspendBuff;
  Restore(p_suspendBuff, &GBWK, 0);
  ++continue_count;
  v13 = Allocate(SequenceParameter);
  _ctor(v13, 0);
  data = continuewk->data;
  v13->CallData5 = data;
  if (dlc_battle)
  {
    p_dlc_kiretu = &dlc_kiretu;
  }
  else
  {
    if (zakuro_Idx < 0)
      goto LABEL_58;
    p_dlc_kiretu = &zakuro_Idx;
  }
  fldGb->nowKiretsuIdx = *p_dlc_kiretu;
LABEL_58:
  gamelevel = continuewk->gamelevel;
  cfgSetConfigGAME(1, gamelevel, 0);
  dds3AdminiCallSequence(19, v13, continuewk->restore);
  *(u64 *)&continuewk->start = 0;
  return 1;
}

// 0x2061310
void sBtlClear(void) {
  continue_count = 0;
  return;
}

// 0x20613e0
static bool IsBoss(void) {
  SB_ENCOUNTPAC *EncountPac;
  _BOOL4 v4;

  goto LABEL_3;
LABEL_11:
  LOBYTE(v4) = 0;
  return v4;
LABEL_3:
  if (!continuewk->data)
    goto LABEL_11;
  EncountPac = sBtlGetEncountPac(-1);
  return (LOBYTE(EncountPac[continuewk->data->encountno]->flag) >> 2)
       & 1;
}

// 0x20614e0
bool sBtlIsSuperRaido(void) {
  return cfgGetConfigGAME(1, 0) == 4;
}

// 0x2061550
bool sBtlIsSuperBoss(void) {
  if (IsBoss())
  {
    return cfgGetConfigGAME(1, 0) == 4;
  }
  return 0;
}

// 0x2061650
s32 sBtlGetViceRaito(void) {
  s32 ConfigGAME;
  s32 v5;

  ConfigGAME = cfgGetConfigGAME(1, 0);
  if (continue_count >= 9)
    v5 = 9;
  else
    v5 = continue_count;
  return vice_up_raito[ConfigGAME][v5];
}

// 0x2061730
s32 sBtlGetContinueRaito(s32 id) {
  s64 v4;
  s32 v5;
  Il2CppClass **v6;
  AITABLE *aitable_local;
  s32 ConfigGAME;
  s32 continue_count_local;
  s32 v12;

  v4 = 0;
  v5 = 100;
  while (1)
  {
    aitable_local = aitable;
    if (v4 >= SLODWORD(aitable_local->max_length))
      break;
    aitable_local = aitable;
    v6 = &aitable_local->obj.klass + v4++;
    if (HIDWORD(v6[4]->_1.name) == id)
    {
      ConfigGAME = cfgGetConfigGAME(1, 0);
      continue_count_local = continue_count;
      v12 = *(u32 *)(*(u64 *)(*(&aitable->max_length + v4) + 24) + 24);
      if (continue_count_local >= v12)
      {
        v12 = *(u32 *)(*(u64 *)(*(&aitable->max_length + v4) + 24) + 24);
        continue_count_local = v12 - 1;
      }
      return *(u32 *)(*(u64 *)(*(u64 *)(*(&aitable->max_length + v4) + 24) + 8 * continue_count_local + 32) + 4 * ConfigGAME + 32);
    }
  }
  return v5;
}
