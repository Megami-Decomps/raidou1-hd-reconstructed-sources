#include "types.h"
#include "cmpmain.h"
#include "configgame.h"
#include "configunity.h"
#include "dat.h"
#include "dds3_pad.h"
#include "evtbit.h"
#include "sbattle.h"

#define DRAW_LIST_MAX 7

typedef enum {
    GameSet_Decision = 0,
    GameSet_Difficulty = 1,
    GameSet_AutoSave = 2,
    GameSet_CsrSave = 3,
    GameSet_CameraUD = 4,
    GameSet_CameraLR = 5,
    GameSet_R2Stop = 6,
    GameSet_Huuma = 7,
    GameSet_SubTitle = 8,
    GameSet_Vibration = 9,
    GameSet_Attack = 10,
    GameSet_Next = 11,
    GameSet_NextStop = 12,
    GameSet_InvSkill = 13,
    GameSet_DvlComb = 14,
    GameSet_SrdComb = 15,
    GameSet_DvlReport = 16,
    GameSet_Max = 17,
} GameSet;

typedef struct LevelData LevelData;

struct LevelData {
    s32 id;
    f32 raito[5];
};

char *menuText;
char *helpText;
char *selectText;
char *huuma_selectText;
s32 **minMaxPar;
static LevelData *leveltable;

static GameSet GetGameSet(void);

// 0x18c87c0
void LevelDataLoad(void) {
  void *Asset;
  s64 naturalAligment;
  void *v5;
  LevelData *v6;
  s64 v9;
  s64 v10;
  LevelData *leveltable_local;
  LevelData *v13;
  LevelData *v14;

  Asset = LoadAsset(_Ctrl_k__BackingField, "common", "leveltable", 0);
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_LevelTableFormat)
      v5 = Asset;
    else
      v5 = 0;
  }
  else
  {
    v5 = 0;
  }
  v6 = NewSpecific(LevelData, 0x27u);
  leveltable = v6;
  v9 = 0;
  v10 = 32;
  do
  {
    leveltable_local = leveltable;
    v13 = GetLEVELTABLE(v5, v9, 0);
    v14 = v13;
    *(Il2CppClass **)((char *)&leveltable_local->obj.klass + v10) = v14;
    ++v9;
    v10 += 8;
  }
  while (v9 != 39);
}

// 0x18c89e0
f32 GetLevelData(LTYPE type, Glvl lvl) {
  return leveltable[type]->raito[lvl];
}

// 0x18c8a60
f32 ConvLevelValue(LTYPE type, f32 val) {
  s64 v7;

  v7 = GBWK->config_data[1][1];
  return leveltable[type]->raito[v7] * val;
}

// 0x18c8bf0
char *GetSelectText(s32 _setPar, s32 _value) {
  char **v6;
  char **v7;
  char **v8;
  char *selectText_local;
  char *result;

  if ((u32)setPar > 0xB)
  {
LABEL_17:
    v7 = &"CONFIG_MAIN_L0009";
    v8 = &"CONFIG_MAIN_L0010";
LABEL_18:
    if (!value)
      v7 = v8;
    return *v7;
  }
  v6 = &"CONFIG_MAIN_L0011";
  switch (setPar)
  {
    case 0:
      goto LABEL_16;
    case 1:
      selectText_local = selectText;
      goto LABEL_15;
    case 6:
    case 8:
      selectText_local = huuma_selectText;
LABEL_15:
      v6 = &selectText_local[value];
LABEL_16:
      result = *v6;
      break;
    case 9:
    case 10:
    case 11:
      v7 = &"CONFIG_MAIN_L0010";
      v8 = &"CONFIG_MAIN_L0009";
      goto LABEL_18;
    default:
      goto LABEL_17;
  }
  return result;
}

// 0x18c8d40
s32 ParToGameSet(s32 _setPar) {
  if ((u32)(setPar - 6) <= 0xA)
    return dword_3E5FDA0[setPar - 6];
  return setPar;
}

// 0x18c8d60
void InitSelectCnt(void) {
  s32 *v3;
  s32 **v4;
  s32 *v5;
  bool v6;
  s32 **v7;
  s32 v8;
  s32 **v10;
  s32 *v11;
  s32 **v12;
  s32 *v13;
  s32 **v14;
  s32 *v15;
  s32 **v16;
  s32 *v17;
  s32 **v18;
  s32 *v19;
  s32 **v20;
  s32 *v21;
  s32 **v22;
  s32 *v23;
  s32 **v24;
  s32 *v25;
  s32 **v26;
  s32 *v27;
  s32 **v28;
  s32 *v29;
  s32 **v30;
  s32 *v31;
  s32 **v32;
  s32 *v33;
  s32 **v34;
  s32 *v35;
  s32 **v36;
  s32 *v37;
  s32 **v38;
  s32 *v39;

  v3 = NewSpecific(s32, 2u);
  minMaxPar[0] = v3;
  v4 = minMaxPar;
  v5 = NewSpecific(s32, 2u);
  v6 = evtBitCheck(2960);
  v4[1] = v5;
  v7 = &v4[1];
  if (v6)
    v8 = 4;
  else
    v8 = 3;
  v5[1] = v8;
  v10 = minMaxPar;
  v11 = NewSpecific(s32, 2u);
  v11[1] = 1;
  v10[2] = v11;
  v12 = minMaxPar;
  v13 = NewSpecific(s32, 2u);
  v12[3] = v13;
  v13[1] = 1;
  v14 = minMaxPar;
  v15 = NewSpecific(s32, 2u);
  v14[4] = v15;
  v15[1] = 1;
  v16 = minMaxPar;
  v17 = NewSpecific(s32, 2u);
  v16[5] = v17;
  v17[1] = 1;
  v18 = minMaxPar;
  v19 = NewSpecific(s32, 2u);
  v18[6] = v19;
  v19[1] = 1;
  v20 = minMaxPar;
  v21 = NewSpecific(s32, 2u);
  v20[7] = v21;
  v21[1] = 1;
  v22 = minMaxPar;
  v23 = NewSpecific(s32, 2u);
  v22[8] = v23;
  v23[1] = 1;
  v24 = minMaxPar;
  v25 = NewSpecific(s32, 2u);
  v24[9] = v25;
  v25[1] = 1;
  v26 = minMaxPar;
  v27 = NewSpecific(s32, 2u);
  v26[10] = v27;
  v27[1] = 1;
  v28 = minMaxPar;
  v29 = NewSpecific(s32, 2u);
  v28[11] = v29;
  v29[1] = 1;
  v30 = minMaxPar;
  v31 = NewSpecific(s32, 2u);
  v30[12] = v31;
  v31[1] = 1;
  v32 = minMaxPar;
  v33 = NewSpecific(s32, 2u);
  v32[13] = v33;
  v33[1] = 1;
  v34 = minMaxPar;
  v35 = NewSpecific(s32, 2u);
  v34[14] = v35;
  v35[1] = 1;
  v36 = minMaxPar;
  v37 = NewSpecific(s32, 2u);
  v36[15] = v37;
  v37[1] = 1;
  v38 = minMaxPar;
  v39 = NewSpecific(s32, 2u);
  v38[16] = v39;
  v39[1] = 1;
}

// 0x18c90e0
void Init(void) {
  u32 v3;
  ConfigCursor *NowCsr;

  if (!sbattleIsBattle())
  {
    if (cmpProcessCheck())
      v3 = 17;
    else
      v3 = 16;
    goto LABEL_19;
  }
  v3 = 17;
LABEL_19:
  NowCsr = GetNowCsr();
  (NowCsr->klass->vtable._5_SetMaxPar.methodPtr)(NowCsr, v3, 7, NowCsr->klass->vtable._5_SetMaxPar.method);
}

// 0x18c9240
bool LevelDisp(void) {
  if (sbattleIsBattle())
    return 1;
  return cmpProcessCheck();
}

// 0x18c9300
static GameSet GetGameSet(void) {
  s32 csrNo;

  csrNo = GetNowCsr()->csrNo;
  if (csrNo < 1)
    return csrNo;
  if (sbattleIsBattle())
    return csrNo;
  return csrNo + !cmpProcessCheck();
}

// 0x18c9470
void Update(void) {
  ConfigCursor *NowCsr;
  s32 GameSet;
  s32 ConfigData;
  s32 *v7;
  s32 v8;
  s32 v9;

  NowCsr = GetNowCsr();
  goto LABEL_4;
LABEL_10:
  if (CHECK_TRIG(4096, 1))
  {
    SE(0);
    InitSaveToMessage(0);
  }
  goto LABEL_27;
LABEL_4:
  GameSet = GetGameSet();
  ConfigData = GetConfigData(GameSet);
  if (!GameSet)
    goto LABEL_10;
  v7 = minMaxPar[GameSet];
  v8 = v7[0];
  v9 = v7[1];
  if (CsrTopReturn(NowCsr, 0))
    return;
  if ((u32)(GameSet - 17) >= 0xFFFFFFF0)
  {
    if (GameSet != 1)
      goto LABEL_19;
    if (!sbattleIsBattle())
    {
LABEL_19:
      if (CHECK_TRIG(4103, 1))
      {
        SE(3);
        if (ConfigData + 1 <= v9)
          ++ConfigData;
        else
          ConfigData = v8;
      }
      else if (CHECK_TRIG(4102, 1))
      {
        SE(3);
        if (ConfigData - 1 >= v8)
          --ConfigData;
        else
          ConfigData = v9;
      }
    }
  }
LABEL_27:
  SetConfigData(GameSet, ConfigData);
}

// 0x18c9680
void Draw(void) {
  ConfigCursor *NowCsr;
  s32 GameSet;
  s32 ConfigData;
  void *v10;
  void *v18;

  NowCsr = GetNowCsr();
  GameSet = GetGameSet();
  ConfigData = GetConfigData(NowCsr->setNo);
  cmpCmpGuideSet(42, 0, 90);
  if (GameSet == 1)
  {
    MenuHelpDraw(instance, ConfigData + 1, helpText, 0);
    return;
  }
  if (GameSet)
  {
    v18 = instance;
    MenuHelpDraw(v18, GameSet + LODWORD(selectText->max_length) - 1, helpText, 0);
    return;
  }
  v10 = instance;
  MenuHelpDraw(v10, 0, helpText, 0);
}
