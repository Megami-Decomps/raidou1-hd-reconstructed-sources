#include "types.h"
#include "cmpmain.h"
#include "configgraphics.h"
#include "configunity.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"

#define DRAW_LIST_MAX 3

typedef enum {
    GraphicsSet_Decision = 0,
    GraphicsSet_Brightness = 1,
    GraphicsSet_Contrast = 2,
    GraphicsSet_Max = 3,
} GraphicsSet;

char *menuText;
char *helpText;
char *paformanceText;
char *renderingText;
s32 **minMaxPar;
static f32 *BrightnessTbl;
static f32 *ContrastTbl;

// 0x18cfd40
char *GetSelectText(s32 _setPar, s32 _value) {
  char **v5;

  if (value)
    v5 = &"CONFIG_MAIN_L0009";
  else
    v5 = &"CONFIG_MAIN_L0010";
  if (!setPar)
    v5 = &"CONFIG_MAIN_L0011";
  return *v5;
}

// 0x18cfde0
void InitSelectCnt(void) {
  s32 *v3;
  s32 **v4;
  s32 *v5;
  s32 **v6;
  s32 *v7;

  v3 = NewSpecific(s32, 2u);
  minMaxPar[0] = v3;
  v4 = minMaxPar;
  v5 = NewSpecific(s32, 2u);
  v5[1] = 18;
  v4[1] = v5;
  v6 = minMaxPar;
  v7 = NewSpecific(s32, 2u);
  v6[2] = v7;
  v7[1] = 18;
}

// 0x18cfed0
void Init(void) {
  ConfigCursor *NowCsr;

  NowCsr = GetNowCsr();
  (NowCsr->klass->vtable._5_SetMaxPar.methodPtr)(NowCsr, 3, 3, NowCsr->klass->vtable._5_SetMaxPar.method);
}

// 0x18cff40
void Update(void) {
  ConfigCursor *NowCsr;
  s64 csrNo;
  s32 ConfigData;
  s32 *v7;
  s32 v8;
  s32 v9;
  s32 setNo;

  NowCsr = GetNowCsr();
  csrNo = NowCsr->csrNo;
  ConfigData = GetConfigData(NowCsr->setNo);
  if (!(u32)csrNo)
  {
    if (CHECK_TRIG(4096, 1))
    {
      SE(0);
      InitMessage(7, 1);
    }
    goto LABEL_17;
  }
  v7 = minMaxPar[csrNo];
  v8 = v7[0];
  v9 = v7[1];
  if (CsrTopReturn(NowCsr, 0))
    return;
  if ((u32)(csrNo - 3) >= 0xFFFFFFFE)
  {
    if (CHECK_REP(4103, 0))
    {
      if (ConfigData < v9)
      {
        SE(3);
        ++ConfigData;
      }
    }
    else if (CHECK_REP(4102, 0) && ConfigData > v8)
    {
      SE(3);
      --ConfigData;
    }
  }
LABEL_17:
  setNo = NowCsr->setNo;
  SetConfigData(setNo, ConfigData);
  if ((u32)csrNo != 2)
  {
    if ((u32)csrNo == 1)
    {
      BrightnessChange();
    }
    return;
  }
  ContrastChange();
}

// 0x18d0580
void Draw(void) {
  ConfigCursor *NowCsr;
  s32 setNo;

  NowCsr = GetNowCsr();
  cmpCmpGuideSet(42, 0, 90);
  setNo = NowCsr->setNo;
  MenuHelpDraw(instance, setNo, helpText, 0);
}

// 0x18d0180
void BrightnessChange(void) {
  s32 *ConfigTab;
  s64 v6;
  f32 v7;
  s32 *v9;

  if (dds3SearchProcessName("config_main"))
  {
    ConfigTab = GetConfigTab(2);
    goto LABEL_8;
  }
  ConfigTab = 0;
LABEL_8:
  if (ConfigTab)
  {
    v6 = ConfigTab[1];
    goto LABEL_12;
  }
  v9 = GBWK->config_data[2];
  v6 = v9[1];
LABEL_12:
  v7 = BrightnessTbl[v6];
  dds3FinishBrightness(v7);
}

// 0x18d0380
void ContrastChange(void) {
  s32 *ConfigTab;
  s64 v6;
  f32 v7;
  s32 *v9;

  if (dds3SearchProcessName("config_main"))
  {
    ConfigTab = GetConfigTab(2);
    goto LABEL_8;
  }
  ConfigTab = 0;
LABEL_8:
  if (ConfigTab)
  {
    v6 = ConfigTab[2];
    goto LABEL_12;
  }
  v9 = GBWK->config_data[2];
  v6 = v9[2];
LABEL_12:
  v7 = ContrastTbl[v6];
  dds3FinishContrast(v7);
}

// 0x18c4610
void ChgConfigGraphicsAll(void) {
  BrightnessChange();
  ContrastChange();
}
