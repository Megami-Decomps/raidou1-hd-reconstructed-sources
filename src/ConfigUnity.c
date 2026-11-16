#include "types.h"
#include "buttonguide.h"
#include "cfg.h"
#include "cmp.h"
#include "cmpmain.h"
#include "configaudio.h"
#include "configdisplay.h"
#include "configgame.h"
#include "configgamepad.h"
#include "configgraphics.h"
#include "configunity.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3vrf.h"
#include "fclmisc.h"
#include "fclmsg.h"
#include "fld.h"
#include "itf.h"
#include "kernel.h"
#include "localize.h"
#include "sbattle.h"
#include "scr.h"
#include "slmain.h"
#include "tips.h"

#define CFG_ARRAY_MAX 256
#define CONFIG_MAINPROC_NAME "config_main"
#define CONFIG_DRAWPROC_NAME "config_draw"
#define GRAPHIC_SET_SECONDS 11

typedef struct CONFIG_WORK CONFIG_WORK;
typedef struct ConfigCursor ConfigCursor;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct fileLoadAsset_Request fileLoadAsset_Request;

char *uiSceneName;
fileLoadAsset_Request *sceneLoadReq;
dds3ProcessID_t *g_mainPID;
bool g_isTabchange;
char *headText_pad;
char *headText_km;
char *tabText;
static s32 configver;
static bool isDrag;
bool IsCamp;
bool IsBattle;
static dds3ProcessFunc_t SuspendFunc;
static dds3ProcessID_t *SuspendID;

static void BackConfigData(bool bakc_f_d);
static void DefaultConfigData(ConfigTab _tab);
static s32 *GetDefaultPar(ConfigTab _tab);
static bool SaveConfig(void);
static void ChangeTab(bool _a);
static bool IsTabChange(void);
static void ChangeMessage(void);
static void CountDown(void);
static void SetTabNo(ConfigTab tab);

// 0x18c69e0
void SetConfigData(s32 _setPar, s32 _value) {
  Il2CppObject *ProcessData;
  Il2CppObject *v8;
  s32 monitor_high;
  s32 v11;
  u64 v12;
  s32 v13;
  u64 v14;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  v8 = ProcessData;
  monitor_high = HIDWORD(ProcessData[2].monitor);
  v14 = 0;
  int____ctor((System_ValueTuple_int__int__o)&v14, monitor_high, setPar);
  v11 = v14;
  v12 = HIDWORD(v14);
  v13 = HIDWORD(v8[2].monitor);
  if (v13 == 1)
  {
    if ((u32)(v12 - 6) <= 0xA)
      LODWORD(v12) = dword_3E5FDA0[(s32)v12 - 6];
    v13 = HIDWORD(v8[2].monitor);
  }
  if (v13 == 3)
  {
    if ((u32)(v12 - 5) <= 0x1E)
      LODWORD(v12) = dword_3E5FDCC[(s32)v12 - 5];
  }
  *(u32 *)(*((u64 *)&v8[4].klass->_1.byval_arg.data + v11) + 4 * (s32)v12 + 32) = value;
}

// 0x18d0a70
void *Get255Over(s32 _setTab, s32 _setIdx) {
  System_ValueTuple_int__int__o v5;

  v5 = 0;
  int____ctor((System_ValueTuple_int__int__o)&v5, setTab, setIdx);
  return v5;
}

// 0x18ccb30
void SetConfigDataHi(s32 _setPar, s32 _value) {
  u16 v3;
  u16 ConfigData;

  v3 = value;
  ConfigData = GetConfigData(setPar);
  SetConfigData(setPar, ConfigData | (v3 << 16));
}

// 0x18ccbb0
void SetConfigDataLw(s32 _setPar, s32 _value) {
  s32 v3;
  s32 ConfigData;
  Il2CppObject *ProcessData;

  v3 = value;
  ConfigData = GetConfigData(setPar);
  SetConfigData(setPar, ConfigData & 0xFFFF0000 | v3);
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  if (HIDWORD(ProcessData[2].monitor) == 3)
  {
    if (!ConfigGameIsCtrl(setPar))
      return;
    switch (v3)
    {
      case 0:
        v3 = 4;
        break;
      case 1:
        v3 = 5;
        break;
      case 2:
        v3 = 6;
        break;
      case 3:
        v3 = 7;
        break;
      default:
        break;
    }
    SetConfigDataHi(setPar, v3);
  }
}

// 0x18c6090
s32 GetConfigData(s32 _setPar) {
  Il2CppObject *ProcessData;
  Il2CppObject *v6;
  s32 monitor_high;
  s32 v9;
  u64 v10;
  s32 v11;
  u64 v13;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return (s32)ProcessData;
  v6 = ProcessData;
  monitor_high = HIDWORD(ProcessData[2].monitor);
  v13 = 0;
  int____ctor((System_ValueTuple_int__int__o)&v13, monitor_high, setPar);
  v9 = v13;
  v10 = HIDWORD(v13);
  v11 = HIDWORD(v6[2].monitor);
  if (v11 == 1)
  {
    if ((u32)(v10 - 6) <= 0xA)
      LODWORD(v10) = dword_3E5FDA0[(s32)v10 - 6];
    v11 = HIDWORD(v6[2].monitor);
  }
  if (v11 == 3)
  {
    if ((u32)(v10 - 5) <= 0x1E)
      LODWORD(v10) = dword_3E5FDCC[(s32)v10 - 5];
  }
  LODWORD(ProcessData) = *(u32 *)(*((u64 *)&v6[4].klass->_1.byval_arg.data + v9) + 4 * (s32)v10 + 32);
  return (s32)ProcessData;
}

// 0x18cc170
s32 GetConfigDataHi(s32 _setPar) {
  return GetConfigData(setPar) >> 16;
}

// 0x18cc100
s32 GetConfigDataLw(s32 _setPar) {
  return (u16)GetConfigData(setPar);
}

// 0x18c7250
s32 *GetConfigTab(s32 _setTab) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return *((s32 **)&ProcessData[4].klass->_1.byval_arg.data + setTab);
  return *((s32 **)&ProcessData[4].klass->_1.byval_arg.data + setTab);
}

// 0x18d0af0
s32 GetConfigDataMinMax(s32 _setPar, ConfigMinMax _MinMax) {
  Il2CppObject *ProcessData;
  s32 ***p_minMaxPar;
  u64 **v11;
  u64 *p_image;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return (s32)ProcessData;
  switch (HIDWORD(ProcessData[2].monitor))
  {
    case 0:
      p_minMaxPar = &minMaxPar;
      goto LABEL_23;
    case 1:
      v11 = &ConfigGame;
      goto LABEL_22;
    case 2:
      v11 = &ConfigGraphics;
      goto LABEL_22;
    case 3:
      v11 = &ConfigGamePad;
      p_image = *v11;
LABEL_22:
      p_minMaxPar = (p_image[23] + 32);
LABEL_23:
      LODWORD(ProcessData) = (*p_minMaxPar)[setPar][MinMax];
      break;
    default:
      LODWORD(ProcessData) = -1;
      break;
  }
  return (s32)ProcessData;
}

// 0x18d0d10
bool CheckConfigData(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  s32 *monitor;
  bool v7;
  s64 v8;
  s32 v9;
  s64 v11;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return 0;
  v4 = ProcessData;
  monitor = ProcessData[4].monitor;
  v7 = 1;
  if (monitor[6] >= 1)
  {
    v8 = 0;
    while (*(s32 *)(*(u64 *)&monitor[2 * v8 + 8] + 24) < 1)
    {
LABEL_13:
      if (++v8 >= monitor[6])
        return 1;
    }
    v9 = 0;
    {
LABEL_19:
      v11 = 0;
      int____ctor((System_ValueTuple_int__int__o)&v11, v8, v9);
      monitor = v4[4].monitor;
      if (*(u32 *)(*((u64 *)&v4[4].klass->_1.byval_arg.data + (s32)v11) + 4 * (v11 >> 32) + 32) != *(u32 *)(*(u64 *)&monitor[2 * (s32)v11 + 8] + 4 * (v11 >> 32) + 32))
        return 0;
      if (++v9 >= *(u32 *)(*(u64 *)&monitor[2 * v8 + 8] + 24))
        goto LABEL_13;
    }
    goto LABEL_19;
  }
  return v7;
}

// 0x18d0f40
static void BackConfigData(bool bakc_f_d) {
  Il2CppObject *ProcessData;
  Il2CppObject *v6;
  void *monitor;
  s64 v9;
  s64 v10;
  s64 v11;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  v6 = ProcessData;
  monitor = ProcessData[4].monitor;
  if (*((s32 *)monitor + 6) >= 1)
  {
    v9 = 4;
    do
    {
      v10 = *((u64 *)&v6[4].klass->_1.image + v9);
      Copy_56180528(monitor[v9], v10, *(u32 *)(v10 + 24), 0);
      monitor = v6[4].monitor;
      v11 = v9 - 3;
      ++v9;
    }
    while (v11 < *((s32 *)monitor + 6));
  }
  ChangeConfigAll((s32)ConfigUnity, 0);
}

// 0x18d10e0
void ChangeConfigAll(ConfigTab _tab, bool bakc_f_d) {
  VolumeChnage(1, 0);
  BrightnessChange();
  ContrastChange();
}

// 0x18d11f0
static void DefaultConfigData(ConfigTab _tab) {
  Il2CppObject *ProcessData;
  Il2CppObject *v6;
  s32 *ConfigInitTable;
  Il2CppClass *klass;
  void *v15;
  s64 v16;
  s32 v17;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (ProcessData)
  {
    v6 = ProcessData;
    ConfigInitTable = cfgGetConfigInitTable(tab);
    if (!ConfigInitTable)
    {
LABEL_12:
      ChangeConfigAll((s32)ConfigUnity, 0);
      return;
    }
    klass = v6[4].klass;
    v15 = ConfigInitTable;
    if (tab == 1)
      ConfigInitTable[1] = *(u32 *)(*(u64 *)&klass->_1.byval_arg.bits + 36);
    v16 = 8 * tab;
    v17 = *(u32 *)(*(u64 *)((char *)v6[4].monitor + v16 + 32) + 24);
    Copy_56180528(ConfigInitTable, *(void *)((char *)&klass->_1.byval_arg.data + v16), (*(u32 **)((char *)&klass->_1.byval_arg.data + v16))[6], 0);
    Copy_56180528(v15, *(void *)((char *)v6[4].monitor + v16 + 32), v17, 0);
    goto LABEL_12;
  }
}

// 0x18d14d0
void SaveConfigData(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  Il2CppClass *klass;
  s64 v7;
  s64 v8;
  s64 v9;
  s32 v10;
  s32 v14;
  s32 v18;
  s32 v22;
  s32 v26;
  s32 v30;
  s32 v34;
  s32 v38;
  s64 v40;
  s32 v42;
  s32 v43;
  s32 v47;
  s32 v51;
  s64 v53;
  s32 v55;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  v4 = ProcessData;
  klass = ProcessData[4].klass;
  if (SLODWORD(klass->_1.namespaze) >= 1)
  {
    v7 = 4;
    do
    {
      v8 = *((u64 *)v4[4].monitor + v7);
      Copy_56180528(*((void *)&klass->_1.image + v7), v8, *(u32 *)(v8 + 24), 0);
      klass = v4[4].klass;
      v9 = v7 - 3;
      ++v7;
    }
    while (v9 < SLODWORD(klass->_1.namespaze));
  }
  v10 = *((u32 *)klass->_1.byval_arg.data + 8);
  GBWK->config_data[0][0] = v10;
  v14 = *((u32 *)v4[4].klass->_1.byval_arg.data + 9);
  GBWK->config_data[0][1] = v14;
  v18 = *((u32 *)v4[4].klass->_1.byval_arg.data + 10);
  GBWK->config_data[0][2] = v18;
  v22 = *((u32 *)v4[4].klass->_1.byval_arg.data + 11);
  GBWK->config_data[0][3] = v22;
  v26 = *((u32 *)v4[4].klass->_1.byval_arg.data + 12);
  GBWK->config_data[0][4] = v26;
  v30 = *((u32 *)v4[4].klass->_1.byval_arg.data + 13);
  GBWK->config_data[0][5] = v30;
  v34 = *((u32 *)v4[4].klass->_1.byval_arg.data + 14);
  GBWK->config_data[0][6] = v34;
  v38 = *((u32 *)v4[4].klass->_1.byval_arg.data + 15);
  v40 = 32;
  GBWK->config_data[0][7] = v38;
  do
  {
    v42 = *(u32 *)(*(u64 *)&v4[4].klass->_1.byval_arg.bits + v40);
    *(u32 *)((char *)&GBWK->config_data[1]->obj.klass + v40) = v42;
    v40 += 4;
  }
  while (v40 != 100);
  v43 = *((u32 *)v4[4].klass->_1.this_arg.data + 8);
  GBWK->config_data[2][0] = v43;
  v47 = *((u32 *)v4[4].klass->_1.this_arg.data + 9);
  GBWK->config_data[2][1] = v47;
  v51 = *((u32 *)v4[4].klass->_1.this_arg.data + 10);
  v53 = 32;
  GBWK->config_data[2][2] = v51;
  while (2)
  {
    v55 = *(u32 *)(*(u64 *)&v4[4].klass->_1.this_arg.bits + v53);
    *(u32 *)((char *)&GBWK->config_data[3]->obj.klass + v53) = v55;
    v53 += 4;
    if (v53 != 584)
      continue;
    break;
  }
  goto LABEL_67;
LABEL_68:
  if (sbattleIsBattle())
    goto LABEL_108;
  if (cmpProcessCheck())
    goto LABEL_108;
  goto LABEL_9004;
LABEL_67:
  goto LABEL_68;
LABEL_108:
  SetRAIDOU_Flag();
LABEL_9004:
}

// 0x18d1dd0
void SetRAIDOU_Flag(void) {
  s32 *EventBit;
  s32 *v5;

  if (GBWK->config_data[1][1] == 4)
  {
    EventBit = GBWK->EventBit;
    EventBit[92] |= 0x20000u;
    goto LABEL_18;
  }
  v5 = GBWK->EventBit;
  v5[92] &= ~0x20000u;
LABEL_18:
  SetDifficulty = 1;
}

// 0x18d1450
static s32 *GetDefaultPar(ConfigTab _tab) {
  s32 v4;

  v4 = tab;
  return cfgGetConfigInitTable(v4);
}

// 0x18d1fa0
char *GetSelectText(s32 _setPar) {
  char *result;
  s32 ConfigData;
  s32 v10;
  s32 v11;
  char **v12;
  char **v13;
  char **v14;
  char **v15;

  result = dds3GetProcessData(g_mainPID);
  if (!result)
    return result;
  switch (*(u32 *)&result[1]._firstChar)
  {
    case 0:
      ConfigData = GetConfigData(setPar);
      if (!setPar)
        return "CONFIG_MAIN_L0011";
      if (setPar != 6)
        goto LABEL_51;
      v14 = &"CONFIG_AUDIO_L0007";
      v15 = &"CONFIG_AUDIO_L0006";
      goto LABEL_52;
    case 1:
      v10 = GetConfigData(setPar);
      return GetSelectText(setPar, v10);
    case 2:
      v11 = GetConfigData(setPar);
      v12 = &"CONFIG_MAIN_L0011";
      v13 = &"CONFIG_MAIN_L0010";
      if (v11)
        v13 = &"CONFIG_MAIN_L0009";
      if (setPar)
        v12 = v13;
      return *v12;
    case 3:
      ConfigData = GetConfigData(setPar);
      if (!setPar)
        return "CONFIG_MAIN_L0011";
      if (setPar == 1)
      {
        result = prisetText[ConfigData];
      }
      else
      {
LABEL_51:
        v14 = &"CONFIG_MAIN_L0009";
        v15 = &"CONFIG_MAIN_L0010";
LABEL_52:
        if (!ConfigData)
          v14 = v15;
        result = *v14;
      }
      break;
    default:
      return 0;
  }
  return result;
}

// 0x18caeb0
void ChangeState(CONFIG_STAT _stat) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  LODWORD(ProcessData[2].klass) = stat;
}

// 0x18caa90
bool IsSpecifiedState(CONFIG_STAT stat_) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return (char)ProcessData;
  LOBYTE(ProcessData) = LODWORD(ProcessData[2].klass) == stat_;
  return (char)ProcessData;
}

// 0x18c7cc0
void InitMessage(CONFIG_MESSAGE _mesType, bool befor_chk) {
  Il2CppObject *ProcessData;
  Il2CppObject *v8;
  s32 v10;
  s32 v11;
  s32 v12;
  Il2CppObject *v18;
  char *v19;
  s32 v20;
  char *v22;
  char *LocalizeText;
  s32 data;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  v8 = ProcessData;
  if (LODWORD(ProcessData[2].klass) != 1)
  {
    if (!befor_chk)
      goto LABEL_17;
    if (fclGetMessageWindowAlpha() <= 0.0 && HIDWORD(v8[2].klass) == 3)
    {
LABEL_17:
      LODWORD(v8[5].klass) = mesType;
      Reset(0);
      itfSetPrefMesNom();
      v10 = 15;
      v11 = 11;
      v12 = 12;
      switch (LODWORD(v8[5].klass))
      {
        case 0:
          v11 = 9;
          BYTE4(v8[6].klass) = 0;
LABEL_21:
          SaveConfigData();
          fclSetMessageInvalid(1);
          fclStartMessage(v11);
LABEL_56:
          ChangeState(1);
          break;
        case 1:
          itfSetPrefMesCmn();
          v11 = 10;
          v10 = 10;
          v12 = 10;
          switch (LODWORD(v8[5].klass))
          {
            case 0:
              goto LABEL_21;
            case 1:
            case 2:
              goto LABEL_32;
            case 3:
            case 4:
            case 5:
            case 6:
              goto LABEL_51;
            case 7:
              goto LABEL_36;
            case 8:
              goto LABEL_39;
            default:
              v12 = 10;
              goto LABEL_53;
          }
        case 2:
LABEL_32:
          fclSetMessageInvalid(1);
          fclStartMessage(10);
          goto LABEL_56;
        case 3:
        case 4:
          goto LABEL_51;
        case 5:
          v12 = 13;
          goto LABEL_53;
        case 6:
          v12 = 14;
          goto LABEL_53;
        case 7:
LABEL_36:
          LODWORD(v8[5].monitor) = 1093664768;
          data = 1093664768;
          v18 = Box(f32, &data);
          v19 = Format("{0}", v18, 0);
          fclSetMessageVar(0, v19);
          fclSetMessageInvalid(0);
          fclSetSelMessagePos(0);
          fclSetSelCancelPos(1);
          v20 = v11;
          goto LABEL_54;
        case 8:
LABEL_39:
          v22 = tabText[SHIDWORD(v8[2].monitor)];
          LocalizeText = GetLocalizeText(v22, 1);
          fclSetMessageVar(0, LocalizeText);
          fclSetMessageInvalid(0);
          fclSetSelMessagePos(0);
          fclSetSelCancelPos(1);
          v20 = v10;
          goto LABEL_54;
        case 9:
          v12 = 16;
LABEL_51:
          goto LABEL_53;
        default:
          v12 = 9;
LABEL_53:
          fclSetMessageInvalid(1);
          fclSetSelMessagePos(0);
          fclSetSelCancelPos(1);
          v20 = v12;
LABEL_54:
          fclStartMessage(v20);
          fclStartSelMessage(0);
          goto LABEL_56;
      }
    }
  }
}

// 0x18c67d0
void InitSaveToMessage(CONFIG_MESSAGE _mesType) {
  Il2CppObject *ProcessData;
  Il2CppObject *v6;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  v6 = ProcessData;
  SaveConfigData();
  cmpCmpGuideSet(43, 0, 90);
  cmpCmpGuideSet(42, 0, 90);
  HIDWORD(v6[5].klass) = mesType;
  LODWORD(v6[1].monitor) = 0;
  *(Il2CppClass **)((char *)&v6[2].klass + 4) = 0x800000006LL;
  return;
}

// 0x18d2480
void UpdateMessage(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  s32 v7;
  s32 SelMessagePos;
  s32 v13;
  s32 v15;
  s32 monitor_high;
  s32 v20;
  s32 v22;
  s32 klass;
  s32 klass_high;
  s32 v31;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  v4 = ProcessData;
  fclUpdateMessage();
  switch (LODWORD(v4[5].klass))
  {
    case 0:
      if (!BYTE4(v4[6].klass))
      {
        SaveConfig();
        BYTE4(v4[6].klass) = 1;
      }
      cmpCmpGuideSet(43, 0, 90);
      cmpCmpGuideSet(42, 0, 90);
      if (!fclChkMessage())
      {
        BYTE4(v4[6].klass) = 0;
        fclEndMessage();
        LODWORD(v4[5].klass) = 11;
      }
      return;
    case 1:
    case 2:
      if (!fclChkMessage())
      {
        fclEndMessage();
        v7 = 2;
        goto LABEL_22;
      }
      return;
    case 3:
    case 4:
      if (!fclChkSelMessage())
      {
        SelMessagePos = fclGetSelMessagePos();
        if (SelMessagePos == 1)
          goto LABEL_106;
        if (!SelMessagePos)
        {
          fclEndMessage();
          if (HIDWORD(v4[2].monitor) == 3)
          {
            ConfigGameSetDuplication();
          }
          goto LABEL_109;
        }
      }
      return;
    case 5:
    case 7:
      if (fclChkSelMessage())
        goto LABEL_39;
      v22 = fclGetSelMessagePos();
      if (v22 == 1)
      {
        fclEndMessage();
        ChangeState(0);
        BackConfigData(1);
        if (LODWORD(v4[5].klass) == 5)
        {
          klass_high = HIDWORD(v4[3].klass);
          v31 = klass_high;
        }
        else
        {
          if (((loc_18D77F0)(0) & 1) == 0)
            return;
          ChangeTab(0);
          v31 = HIDWORD(v4[3].klass);
        }
        SetTabNo(v31);
        return;
      }
      if (v22)
      {
LABEL_39:
        CountDown();
        return;
      }
      klass = v4[5].klass;
      if (klass != 5)
      {
        if (klass != 7)
        {
LABEL_143:
          fclEndMessage();
          return;
        }
        SaveConfig();
        ChangeState(0);
        if (((loc_18D77F0)(0) & 1) == 0)
        {
LABEL_142:
          InitSaveToMessage(-1);
          goto LABEL_143;
        }
        ChangeTab(0);
        SetTabNo(HIDWORD(v4[3].klass));
        goto LABEL_142;
      }
      if (HIDWORD(v4[2].monitor) != 2)
      {
        SaveConfigData();
        ChangeState(0);
        SetTabNo(HIDWORD(v4[3].klass));
        goto LABEL_142;
      }
      ChangeMessage();
      ChangeTab(1);
      return;
    case 6:
      if (!fclChkSelMessage())
      {
        v13 = fclGetSelMessagePos();
        if (v13 == 1)
          goto LABEL_106;
        if (!v13)
        {
          fclEndMessage();
          BackConfigData(0);
          v7 = 0;
          goto LABEL_22;
        }
      }
      return;
    case 8:
      if (!fclChkSelMessage())
      {
        v15 = fclGetSelMessagePos();
        if (v15 == 1)
        {
LABEL_106:
          fclEndMessage();
          goto LABEL_109;
        }
        if (!v15)
        {
          fclEndMessage();
          monitor_high = HIDWORD(v4[2].monitor);
          DefaultConfigData(monitor_high);
          SaveConfig();
          ChangeState(0);
          cmpCmpGuideSet(43, 0, 90);
          cmpCmpGuideSet(42, 0, 90);
        }
      }
      return;
    case 9:
      if (!fclChkSelMessage())
      {
        v20 = fclGetSelMessagePos();
        if (v20 == 1)
        {
          fclEndMessage();
          LODWORD(v4[5].klass) = 10;
        }
        else if (!v20)
        {
          fclEndMessage();
          BackConfigData(0);
          HIDWORD(v4[2].klass) = 4;
        }
      }
      return;
    case 0xA:
      if (!fclChkMessage())
        goto LABEL_109;
      return;
    case 0xB:
LABEL_109:
      v7 = 0;
LABEL_22:
      ChangeState(v7);
      return;
    default:
      return;
  }
}

// 0x18d2400
static bool SaveConfig(void) {
  SaveConfigData();
  return 1;
}

// 0x18d2c40
static void ChangeTab(bool _a) {
  _BOOL4 v4;

  v4 = a;
  if (g_isTabchange == v4)
    return;
  g_isTabchange = v4;
}

// 0x18d3510
static bool IsTabChange(void) {
  return g_isTabchange;
}

// 0x18d2fb0
static void ChangeMessage(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  Il2CppObject *v6;
  char *v7;
  s32 data;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  v4 = ProcessData;
  if (LODWORD(ProcessData[2].klass) == 1)
  {
    LODWORD(ProcessData[5].klass) = 7;
    Reset(0);
    LODWORD(v4[5].monitor) = 1093664768;
    data = 1093664768;
    v6 = Box(f32, &data);
    v7 = Format("{0}", v6, 0);
    fclSetMessageVar(0, v7);
    fclSetMessageInvalid(0);
    fclSetSelMessagePos(0);
    fclSetSelCancelPos(1);
    fclStartMessage(11);
    fclStartSelMessage(0);
  }
}

// 0x18d31c0
static void CountDown(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  f32 v6;
  s32 PrefMesWin;
  char *LocalizeText;
  f32 v12;
  char *v13;
  s32 v14;
  Il2CppObject *v15;
  char *v16;
  char *v17;
  char *v18;
  char **p_g_replace_text;
  s32 data;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  v4 = ProcessData;
  if (LODWORD(ProcessData[5].klass) == 7)
  {
    v6 = *(f32 *)&ProcessData[5].monitor - VRF_DeltaTime;
    *(f32 *)&ProcessData[5].monitor = v6;
    if (v6 == INFINITY || (s32)v6 <= 0)
    {
      fclEndMessage();
      BackConfigData(1);
      ChangeState(0);
    }
    else
    {
      PrefMesWin = itfGetPrefMesWin();
      if (itfGetMsgWndTmpText(PrefMesWin))
      {
        LocalizeText = GetLocalizeText("CMP_SYS_L0010", 1);
        v12 = *(f32 *)&v4[5].monitor;
        v13 = LocalizeText;
        v14 = v12;
        if (v12 == INFINITY)
          v14 = 0x80000000;
        data = v14;
        v15 = Box(s32, &data);
        v16 = Format("{0}", v15, 0);
        v17 = itfNumConv(v16);
        v18 = Replace_54838864(v13, "<V 0>", v17, 0);
        p_g_replace_text = &g_replace_text;
        *p_g_replace_text = v18;
      }
    }
  }
}

// 0x18d3590
void KeyConfigUpdate(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  if (HIDWORD(ProcessData[2].monitor) == 3)
  {
    if (!ConfigGameChange())
      return;
    if (LODWORD(v4[2].klass) != 1)
    {
      ChangeState(0);
    }
  }
}

// 0x18d3710
ConfigCursor *GetCsrTabType(ConfigTab _tab) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return *((ConfigCursor *)ProcessData[3].monitor + tab + 4);
  return *((ConfigCursor *)ProcessData[3].monitor + tab + 4);
}

// 0x18c5c60
ConfigCursor *GetNowCsr(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return *((ConfigCursor *)ProcessData[3].monitor + SHIDWORD(ProcessData[2].monitor) + 4);
  return *((ConfigCursor *)ProcessData[3].monitor + SHIDWORD(ProcessData[2].monitor) + 4);
}

// 0x18d3840
s32 GetNowListTop(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return *(u32 *)(*((u64 *)ProcessData[3].monitor + SHIDWORD(ProcessData[2].monitor) + 4) + 20);
  return *(u32 *)(*((u64 *)ProcessData[3].monitor + SHIDWORD(ProcessData[2].monitor) + 4) + 20);
}

// 0x18d3960
s32 GetNowTab(void) {
  Il2CppObject *ProcessData;

  if (!g_mainPID)
  {
    LODWORD(ProcessData) = 0;
    return (s32)ProcessData;
  }
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return (s32)ProcessData;
  LODWORD(ProcessData) = HIDWORD(ProcessData[2].monitor);
  return (s32)ProcessData;
}

// 0x18d3ab0
void TabChange(s32 _cnt, bool _se) {
  Il2CppObject *ProcessData;
  CONFIG_WORK *v9;
  s32 tab;
  s32 v12;
  s32 v13;
  s32 v14;

  ProcessData = dds3GetProcessData(g_mainPID);
  v9 = ProcessData;
  if (se)
    SE(9);
  tab = v9->tab;
  v9->tab_old = tab;
  v12 = tab + cnt;
  if (v9->changeBgmPlaying)
  {
    RestoreChangeSound(v9);
    v9->changeBgmPlaying = 0;
  }
  if (v12 >= 4)
    v13 = 0;
  else
    v13 = v12;
  if (v13 < 0)
    v14 = 3;
  else
    v14 = v13;
  if (!CheckConfigData())
  {
    InitMessage(5, 1);
    v9->changeTab = v14;
    return;
  }
  SetTabNo(v14);
}

// 0x18d2d10
static void SetTabNo(ConfigTab tab) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  HIDWORD(ProcessData[2].monitor) = tab;
  if (!!op_Inequality(instance, 0, 0))
    TabChange(instance, tab);
  TabInit();
}

// 0x18d3fb0
void MainInput(void) {
  Il2CppObject *ProcessData;
  CONFIG_WORK *v4;
  s32 v9;
  bool v10;
  s32 step;
  bool v15;
  bool v16;
  bool v17;
  bool v18;
  ConfigCursor *v21;
  ConfigCursor *v22;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  if (LODWORD(ProcessData[2].klass) == 1)
    return;
  if (!CHECK_TRIG(4097, 1))
  {
    if (CHECK_TRIG(4104, 1) && v4->step == 3)
    {
      v9 = -1;
LABEL_27:
      TabChange(v9, 1);
      return;
    }
    if (CHECK_TRIG(4107, 1) && v4->step == 3)
    {
      v9 = 1;
      goto LABEL_27;
    }
    v10 = CHECK_TRIG(41230, 1);
    step = v4->step;
    if (v10)
    {
      if (step == 3)
      {
        if (v4->changeBgmPlaying)
        {
          RestoreChangeSound(v4);
          v4->changeBgmPlaying = 0;
        }
        SE(0);
        InitMessage(8, 1);
      }
      return;
    }
    if (step != 3)
      return;
    v15 = CHECK_TRIG(4100, 1);
    v16 = CHECK_REP(4100, 1);
    v17 = CHECK_TRIG(4101, 1);
    v18 = CHECK_REP(4101, 1);
    if (!IsCsrMove(instance, 0))
      return;
    if (!isDrag)
    {
      v21 = v4->csr[v4->tab];
      (v21->klass->vtable._7_CsrUp.methodPtr)(v21, v15, v16, v21->klass->vtable._7_CsrUp.method);
      v22 = v4->csr[v4->tab];
      (v22->klass->vtable._8_CsrDown.methodPtr)(v22, v17, v18, v22->klass->vtable._8_CsrDown.method);
    }
    return;
  }
  if (CheckConfigData())
    goto LABEL_11;
  InitMessage(9, 1);
  if (!v4->changeBgmPlaying)
  {
LABEL_12:
    if (v4->stat)
      return;
LABEL_44:
    v4->step = 4;
    return;
  }
  goto LABEL_41;
LABEL_11:
  if (!v4->changeBgmPlaying)
    goto LABEL_12;
LABEL_41:
  RestoreChangeSound(v4);
  v4->changeBgmPlaying = 0;
  if (!v4->stat)
    goto LABEL_44;
}

// 0x18d4420
bool GetDragFlg(void) {
  return isDrag;
}

// 0x18d44a0
void LoadLocalizeText(void) {
  ;
}

// 0x18d44b0
void LoadScene(void) {
  fileLoadAsset_Request *Asset__AllSceneAsync;

  Asset__AllSceneAsync = AllSceneAsync("config_cs", 0);
  sceneLoadReq = Asset__AllSceneAsync;
}

// 0x18d4540
void UnloadScene(char *_sceneName) {
  UnityEngine_SceneManagement_Scene_o v3;

  v3.m_Handle = GetSceneByName(sceneName, 0).m_Handle;
  UnloadSceneAsync_61083440(v3, 0);
}

// 0x18d45b0
void Init(CONFIG_WORK *_wk) {
  ConfigCursor *csr;
  ConfigCursor *v5;
  ConfigCursor *v6;
  ConfigCursor *v7;
  ConfigCursor *v8;
  ConfigCursor *v9;
  ConfigCursor *v10;
  ConfigCursor *v11;
  s32 **nowPar;
  s32 *v14;
  s32 **v15;
  s32 *v16;
  s32 **v17;
  s32 *v18;
  s32 **v19;
  s32 *v20;
  s32 **setPar;
  s32 *v22;
  s32 **v23;
  s32 *v24;
  s32 **v25;
  s32 *v26;
  s32 **v27;
  s32 *v28;
  s32 *v29;
  s32 *v30;
  struct dat *static_fields;
  s32 *v34;
  s32 *v35;
  struct dat *v37;
  s32 *v39;
  s32 *v40;
  struct dat *v42;
  s32 *v44;
  s32 *v45;
  struct dat *v47;
  s32 *v49;
  s32 *v50;
  struct dat *v52;
  s32 *v54;
  s32 *v55;
  struct dat *v57;
  s32 *v59;
  s32 *v60;
  struct dat *v62;
  s32 *v64;
  s32 *v65;
  s64 v67;
  s32 v68;
  s32 v70;
  s32 *v71;
  s32 *v72;
  s32 *v73;
  s32 *v74;
  struct dat *v76;
  s32 *v78;
  s32 *v79;
  struct dat *v81;
  s32 *v83;
  s32 *v84;
  s64 v86;
  s32 v87;
  dds3GlobalWork_t *GBWK_local;
  s32 *v89;
  s32 *v90;

  wk->step = 0;
  csr = wk->csr;
  wk->processStat = 8;
  v5 = Allocate(ConfigCursor);
  _ctor(v5, 0);
  csr[0] = v5;
  v6 = wk->csr;
  v7 = Allocate(ConfigCursor);
  _ctor(v7, 0);
  v6[1] = v7;
  v8 = wk->csr;
  v9 = Allocate(ConfigCursor);
  _ctor(v9, 0);
  v8[2] = v9;
  v10 = wk->csr;
  v11 = Allocate(ConfigCursor);
  _ctor(v11, 0);
  v10[3] = v11;
  wk->tab = 0;
  nowPar = wk->nowPar;
  v14 = NewSpecific(s32, 8u);
  nowPar[0] = v14;
  v15 = wk->nowPar;
  v16 = NewSpecific(s32, 0x11u);
  v15[1] = v16;
  v17 = wk->nowPar;
  v18 = NewSpecific(s32, 3u);
  v17[2] = v18;
  v19 = wk->nowPar;
  v20 = NewSpecific(s32, 0x8Au);
  v19[3] = v20;
  setPar = wk->setPar;
  v22 = NewSpecific(s32, 8u);
  setPar[0] = v22;
  v23 = wk->setPar;
  v24 = NewSpecific(s32, 0x11u);
  v23[1] = v24;
  v25 = wk->setPar;
  v26 = NewSpecific(s32, 3u);
  v25[2] = v26;
  v27 = wk->setPar;
  v28 = NewSpecific(s32, 0x8Au);
  v27[3] = v28;
  v29 = wk->nowPar[0];
  v30 = wk->setPar[0];
  LODWORD(static_fields) = GBWK->config_data[0][0];
  v30[0] = (s32)static_fields;
  v29[0] = (s32)static_fields;
  v34 = wk->nowPar[0];
  v35 = wk->setPar[0];
  LODWORD(v37) = GBWK->config_data[0][1];
  v35[1] = (s32)v37;
  v34[1] = (s32)v37;
  v39 = wk->nowPar[0];
  v40 = wk->setPar[0];
  LODWORD(v42) = GBWK->config_data[0][2];
  v40[2] = (s32)v42;
  v39[2] = (s32)v42;
  v44 = wk->nowPar[0];
  v45 = wk->setPar[0];
  LODWORD(v47) = GBWK->config_data[0][3];
  v45[3] = (s32)v47;
  v44[3] = (s32)v47;
  v49 = wk->nowPar[0];
  v50 = wk->setPar[0];
  LODWORD(v52) = GBWK->config_data[0][4];
  v50[4] = (s32)v52;
  v49[4] = (s32)v52;
  v54 = wk->nowPar[0];
  v55 = wk->setPar[0];
  LODWORD(v57) = GBWK->config_data[0][5];
  v55[5] = (s32)v57;
  v54[5] = (s32)v57;
  v59 = wk->nowPar[0];
  v60 = wk->setPar[0];
  LODWORD(v62) = GBWK->config_data[0][6];
  v60[6] = (s32)v62;
  v59[6] = (s32)v62;
  v64 = wk->nowPar[0];
  v65 = wk->setPar[0];
  v67 = 32;
  v68 = GBWK->config_data[0][7];
  v65[7] = v68;
  v64[7] = v68;
  do
  {
    v71 = wk->nowPar[1];
    v72 = wk->setPar[1];
    v70 = *(u32 *)((char *)&GBWK->config_data[1]->obj.klass + v67);
    *(u32 *)((char *)&v72->obj.klass + v67) = v70;
    *(u32 *)((char *)&v71->obj.klass + v67) = v70;
    v67 += 4;
  }
  while (v67 != 100);
  v73 = wk->nowPar[2];
  v74 = wk->setPar[2];
  LODWORD(v76) = GBWK->config_data[2][0];
  v74[0] = (s32)v76;
  v73[0] = (s32)v76;
  v78 = wk->nowPar[2];
  v79 = wk->setPar[2];
  LODWORD(v81) = GBWK->config_data[2][1];
  v79[1] = (s32)v81;
  v78[1] = (s32)v81;
  v83 = wk->nowPar[2];
  v84 = wk->setPar[2];
  v86 = 32;
  v87 = GBWK->config_data[2][2];
  v84[2] = v87;
  v83[2] = v87;
  while (2)
  {
    v89 = wk->nowPar[3];
    v90 = wk->setPar[3];
    goto LABEL_58;
LABEL_59:
    GBWK_local = GBWK;
    if (!GBWK_local)
      goto LABEL_55;
    GBWK_local = GBWK;
    LODWORD(GBWK_local) = *(u32 *)((char *)&GBWK_local->config_data[3]->obj.klass + v86);
    goto LABEL_55;
LABEL_58:
    goto LABEL_59;
LABEL_55:
    *(u32 *)((char *)&v90->obj.klass + v86) = (u32)GBWK_local;
    *(u32 *)((char *)&v89->obj.klass + v86) = (u32)GBWK_local;
    v86 += 4;
    if (v86 != 584)
      continue;
    break;
  }
  scrLogEnd(0);
  wk->saveFlag = 0;
  wk->mesType = -1;
  wk->mesCunter = 11.0;
}

// 0x18d4fc0
void ProcessStart(void) {
  fileLoadAsset_Request *Asset__AllSceneAsync;
  bool v5;
  bool IsBattle_local;
  CONFIG_WORK *v10;
  dds3ProcessFunc_t v12;
  shutdownfuncDelegate v13;
  dds3ProcessID_t *started;
  dds3ProcessFunc_t v16;
  dds3ProcessID_t *v17;

  Asset__AllSceneAsync = AllSceneAsync("config_cs", 0);
  sceneLoadReq = Asset__AllSceneAsync;
  v5 = cmpProcessCheck();
  IsCamp = v5;
  IsBattle_local = sbattleIsBattle();
  IsBattle = IsBattle_local;
  if (!IsCamp)
  {
    Create(0);
    fclLinkData(sys);
  }
  v10 = Allocate(CONFIG_WORK);
  _ctor(v10, 0);
  Init();
  v12 = Allocate(dds3ProcessFunc_t);
  _ctor(v12, 0, Method_Project_ConfigUnity_Process__, 0);
  v13 = Allocate(shutdownfuncDelegate);
  _ctor(v13, 0, Method_Project_ConfigUnity_Shutdown__, 0);
  started = dds3StartProcess("config_main", 1007, 0, 0, v12, v13, v10);
  g_mainPID = started;
  v16 = Allocate(dds3ProcessFunc_t);
  _ctor(v16, 0, Method_Project_ConfigUnity_DrawProcess__, 0);
  v17 = dds3StartProcess("config_draw", 11012, 0, 0, v16, 0, v10);
  v10->drawPID = v17;
  TabChange(0, 0);
  InitSelectCnt();
  InitSelectCnt();
  InitSelectCnt();
  ConfigGameInitSelectCnt();
  InitSelectCnt();
}

// 0x18d5460
dds3ProcessFunc_t Process(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  Il2CppObject *v7;
  void *v15;
  void *v16;
  s32 v18;
  s32 klass;
  s32 monitor;
  s32 **config_data;
  dds3ProcessID_t *v27;
  dds3ProcessFunc_t v30;
  dds3ProcessID_t *SuspendID_local;
  s32 v35;
  dds3ProcessFunc_t processfunc;
  dds3ProcessFunc_t v38;
  dds3ProcessFunc_t v41;
  dds3ProcessID_t *v42;
  s32 klass_high;
  dds3ProcessFunc_t v46;
  UnityEngine_SceneManagement_Scene_o v51;

  ProcessData = dds3GetProcessData(g_mainPID);
  v7 = ProcessData;
  switch (HIDWORD(ProcessData[2].klass))
  {
    case 0:
      if (!sceneLoadReq->isDone)
        return 0;
      if (op_Equality(instance, 0, 0))
        return 0;
      v35 = 1;
      goto LABEL_133;
    case 1:
      HIDWORD(v7[2].klass) = 2;
      if (IsCamp)
      {
        ButtonLineHelpTextSet(0, 0, 1, 0xA09DC380, 1);
      }
      else
      {
        dds3FadeOut(0, 0, 0, 1u);
      }
      v15 = get_Instance(0);
      ItfButtonGuideSet(v15, 1, 0);
      v16 = get_Instance(0);
      ItfButtonGuideActive(v16, 1, 0);
      ButtonGuideDispOn();
      ButtonLineHelpDispSet(1);
      return 0;
    case 2:
      if (IsCamp)
        goto LABEL_33;
      monitor = v7[1].monitor;
      if (!monitor)
      {
        dds3FadeIn(0, 0, 0, 0xAu);
        goto LABEL_127;
      }
      if (monitor >= 10)
      {
LABEL_33:
        v18 = 3;
        goto LABEL_49;
      }
      goto LABEL_128;
    case 3:
      klass = ProcessData[2].klass;
      switch (klass)
      {
        case 2:
          KeyConfigUpdate();
          return 0;
        case 1:
          UpdateMessage();
          return 0;
        case 0:
          MainInput();
          if (HIDWORD(v7[2].klass) == 3)
          {
            TabUpdate();
            return 0;
          }
          break;
      }
      return 0;
    case 4:
      if (LODWORD(v7[1].monitor))
      {
        if (IsCamp || SLODWORD(v7[1].monitor) >= 10)
        {
          v18 = 5;
LABEL_49:
          LODWORD(v7[1].monitor) = 0;
          HIDWORD(v7[2].klass) = v18;
          return 0;
        }
      }
      else
      {
        if (IsCamp)
        {
          SE(1);
        }
        else
        {
          GuideObjClr();
          SE(18);
          dds3FadeOut(0, 0, 0, 0xAu);
          Delete(0);
        }
      }
LABEL_127:
      monitor = v7[1].monitor;
LABEL_128:
      LODWORD(v7[1].monitor) = monitor + 1;
      return 0;
    case 5:
      monitor = ProcessData[1].monitor;
      if (monitor)
      {
        if (monitor >= 2)
        {
          monitor = 0;
          *(Il2CppClass **)((char *)&ProcessData[2].klass + 4) = 0x900000006LL;
        }
      }
      else
      {
        v51.m_Handle = GetSceneByName(uiSceneName, 0).m_Handle;
        UnloadSceneAsync_61083440(v51, 0);
        monitor = v7[1].monitor;
        HIDWORD(v7[1].monitor) &= ~8u;
      }
      goto LABEL_128;
    case 6:
      config_data = GBWK->config_data;
      cfgGwToSystemCopy(config_data);
      v27 = Allocate(dds3ProcessID_t);
      _ctor(v27, 0);
      SuspendID = v27;
      v30 = slSystemDataProc();
      SuspendFunc = v30;
      if (SuspendFunc)
      {
        SuspendID_local = SuspendID;
        SuspendID_local->processfunc = SuspendFunc;
      }
      v35 = 7;
      goto LABEL_133;
    case 7:
      processfunc = SuspendID->processfunc;
      v38 = (processfunc->invoke_impl)(processfunc->method_code);
      SuspendFunc = v38;
      v41 = SuspendFunc;
      if (v41)
      {
        v41 = SuspendFunc;
        v42 = SuspendID;
        v42->processfunc = v41;
      }
      if (!slGetSaveResultType())
        goto LABEL_132;
      if (gslErrorKeyNoWait == 1)
        goto LABEL_132;
      if (gslInfoCode != 100)
        return 0;
LABEL_132:
      v35 = v7[2].monitor;
LABEL_133:
      HIDWORD(v7[2].klass) = v35;
      return 0;
    case 8:
      LODWORD(ProcessData[1].monitor) = 0;
      HIDWORD(ProcessData[2].klass) = 3;
      klass_high = HIDWORD(ProcessData[5].klass);
      if (klass_high == -1)
        return 0;
      InitMessage(klass_high, 1);
      return 0;
    case 9:
      tipsReDestCall();
      v46 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v46, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v46;
    default:
      return 0;
  }
}

// 0x18d3ce0
void TabInit(void) {
  Il2CppObject *ProcessData;
  ConfigCursor *NowCsr;
  ConfigCursor *v9;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  BYTE4(ProcessData[5].monitor) = 1;
  switch (HIDWORD(ProcessData[2].monitor))
  {
    case 0:
      NowCsr = GetNowCsr();
      (NowCsr->klass->vtable._5_SetMaxPar.methodPtr)(NowCsr, 8, 7, NowCsr->klass->vtable._5_SetMaxPar.method);
      return;
    case 1:
      Init();
      return;
    case 2:
      v9 = GetNowCsr();
      (v9->klass->vtable._5_SetMaxPar.methodPtr)(v9, 3, 3, v9->klass->vtable._5_SetMaxPar.method);
      return;
    case 3:
      ConfigGameInit();
      return;
    default:
      return;
  }
}

// 0x18d5e20
void TabUpdate(void) {
  Il2CppObject *ProcessData;
  CONFIG_WORK *v5;

  ProcessData = dds3GetProcessData(g_mainPID);
  v5 = ProcessData;
  if (LODWORD(ProcessData[2].klass) != 1)
  {
    switch (HIDWORD(ProcessData[2].monitor))
    {
      case 0:
        Update(v5, CONFIG_WORK);
        break;
      case 1:
        Update();
        break;
      case 2:
        Update();
        break;
      case 3:
        ConfigGameUpdate();
        break;
      default:
        return;
    }
  }
}

// 0x18d6050
void TabDraw(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  switch (HIDWORD(ProcessData[2].monitor))
  {
    case 0:
      Draw();
      break;
    case 1:
      Draw();
      break;
    case 2:
      Draw();
      break;
    case 3:
      ConfigGameDraw();
      break;
    default:
      return;
  }
}

// 0x18d6270
void DrawListActive(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  if (!!HIDWORD(ProcessData[2].monitor))
  {
    ListActive(instance, 0, 0, 0, 0);
    if (HIDWORD(v4[2].monitor) == 1)
      goto LABEL_16;
  }
  ListActive(instance, 1, 0, 0, 0);
  if (HIDWORD(v4[2].monitor) == 2)
    goto LABEL_24;
LABEL_16:
  ListActive(instance, 2, 0, 0, 0);
  if (HIDWORD(v4[2].monitor) == 3)
  {
    goto LABEL_21;
  }
LABEL_24:
  ListActive(instance, 3, 0, 0, 0);
LABEL_21:
  ListActive(instance, HIDWORD(v4[2].monitor), 1, *(u32 *)(*((u64 *)v4[3].monitor + SHIDWORD(v4[2].monitor) + 4) + 48), 0);
  BYTE4(v4[5].monitor) = 0;
}

// 0x18d6620
char *GetMenuText(ConfigTab _tab) {
  char *result;

  switch (tab)
  {
    case 0:
      result = menuText;
      break;
    case 1:
      result = menuText;
      break;
    case 2:
      result = menuText;
      break;
    case 3:
      result = menuText;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

// 0x18d6790
dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  Il2CppObject *v5;
  s64 monitor_high;
  char v15;
  void *v21;
  u32 v23;
  void *v27;
  void *v33;
  void *v35;
  s32 v36;
  char *MenuText;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return 0;
  v5 = ProcessData;
  goto LABEL_14;
LABEL_15:
  if (op_Equality(instance, 0, 0))
    return 0;
  monitor_high = SHIDWORD(v5[2].monitor);
  DrawListActive();
  TabDraw();
  v15 = !IsCamp;
  if (IsCamp)
  {
    v15 = 0;
LABEL_39:
    BackActive(instance, v15, 0);
    MenuScloll(instance, monitor_high, *(u32 *)(*((u64 *)v5[3].monitor + monitor_high + 4) + 20), 0);
    v21 = instance;
    TabCsrDraw(v21, monitor_high, tabText, 0);
    MenuCsrDraw(instance, monitor_high, *(u32 *)(*((u64 *)v5[3].monitor + monitor_high + 4) + 48), 0);
    if ((u32)monitor_high == 3)
    {
      if (v23)
      {
        goto LABEL_50;
      }
      else
      {
LABEL_50:
        goto LABEL_51;
      }
LABEL_51:
      v27 = instance;
      MenuDraw_D(v27, 3, headText_pad, 0);
LABEL_60:
      v35 = instance;
      v36 = *(u32 *)(*((u64 *)v5[3].monitor + monitor_high + 4) + 48);
      MenuText = GetMenuText(monitor_high);
      MenuTextDraw(v35, monitor_high, v36, MenuText, IsCamp, 0);
      MenuTypeDraw(instance, monitor_high, *(u32 *)(*((u64 *)v5[3].monitor + monitor_high + 4) + 48), 0);
      return 0;
    }
    if (v23)
    {
      goto LABEL_56;
    }
    else
    {
LABEL_56:
      goto LABEL_57;
    }
LABEL_57:
    v33 = instance;
    MenuDraw_D(v33, monitor_high, headText_km, 0);
    goto LABEL_60;
  }
  v15 = 1;
  goto LABEL_39;
LABEL_14:
  goto LABEL_15;
}

// 0x18d6e60
void Shutdown(dds3ProcessID_t *PID) {
  dds3ProcessID_t *ProcessData;
  s64 naturalAligment;
  dds3ProcessID_t *v5;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (ProcessData)
    LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((CONFIG_WORK **)(ProcessData)[1].next + naturalAligment - 1) != CONFIG_WORK;
  v5 = ProcessData + 2;
  if (dds3ExistProcess(ProcessData + 2))
  {
    dds3KillProcess(v5, 0);
    v5 = 0;
  }
  id = 0;
  g_mainPID = 0;
  if (dds3SearchProcessName("fldProcSequence"))
  {
    miniCharUpdate = 1;
  }
}

// 0x18d7020
bool ProcessCheck(void) {
  if (!g_mainPID)
    return 0;
  if (dds3GetProcessStat(g_mainPID) != 3)
  {
    if (dds3GetProcessStat(g_mainPID))
    {
      return 1;
    }
  }
  g_mainPID = 0;
  return 0;
}

// 0x18d7190
void ProcessEnd(void) {
  Il2CppObject *ProcessData;
  s32 monitor_high;

  if (!g_mainPID)
    return;
  if (!dds3ExistProcess(g_mainPID))
    return;
  goto LABEL_15;
LABEL_19:
  goto LABEL_21;
LABEL_15:
  ProcessData = dds3GetProcessData(g_mainPID);
  if (ProcessData)
    goto LABEL_19;
LABEL_21:
  monitor_high = HIDWORD(ProcessData[1].monitor);
  if ((monitor_high & 1) == 0)
  {
    LODWORD(ProcessData[1].monitor) = 0;
    HIDWORD(ProcessData[1].monitor) = monitor_high | 1;
    HIDWORD(ProcessData[2].klass) = 9;
  }
}
