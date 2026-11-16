#include "types.h"
#include "cmpmain.h"
#include "configdisplay.h"
#include "configunity.h"
#include "dds3_pad.h"

#define DRAW_LIST_MAX 5

typedef enum {
    DisplaySet_Decision = 0,
    DisplaySet_Resolution = 1,
    DisplaySet_Monitor = 2,
    DisplaySet_Screen = 3,
    DisplaySet_V_Sync = 4,
    DisplaySet_Max = 5,
} DisplaySet;

char *menuText;
char *helpText;
char *screenText;
s32 **minMaxPar;
char *reslution_str;

static bool IsBorderless(void);
static bool IsWindowed(void);

// 0x18c7750
char *GetSelectText(s32 _setPar, s32 _value) {
  char *result;
  s32 v7;

  result = "";
  switch (setPar)
  {
    case 0:
      result = "CONFIG_MAIN_L0011";
      break;
    case 1:
      return result;
    case 2:
      v7 = value + 1;
      result = ToString_55996800((s32)&v7, "d", 0);
      break;
    case 3:
      result = screenText[value];
      break;
    default:
      if (value)
        result = "CONFIG_MAIN_L0009";
      else
        result = "CONFIG_MAIN_L0010";
      break;
  }
  return result;
}

// 0x18c78c0
void InitSelectCnt(void) {
  s32 *v3;
  s32 **v4;
  s32 *v5;
  s32 **v6;
  s32 *v7;
  s32 **v8;
  s32 *v9;
  s32 **v10;
  s32 *v11;

  v3 = NewSpecific(s32, 2u);
  minMaxPar[0] = v3;
  v4 = minMaxPar;
  v5 = NewSpecific(s32, 2u);
  v5[1] = 1;
  v4[1] = v5;
  v6 = minMaxPar;
  v7 = NewSpecific(s32, 2u);
  v6[2] = v7;
  v7[1] = 1;
  v8 = minMaxPar;
  v9 = NewSpecific(s32, 2u);
  v8[3] = v9;
  v9[1] = 2;
  v10 = minMaxPar;
  v11 = NewSpecific(s32, 2u);
  v10[4] = v11;
  v11[1] = 1;
}

// 0x18c7a10
void Init(void) {
  ConfigCursor *NowCsr;

  NowCsr = GetNowCsr();
  (NowCsr->klass->vtable._5_SetMaxPar.methodPtr)(NowCsr, 5, 5, NowCsr->klass->vtable._5_SetMaxPar.method);
}

// 0x18c7a80
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
      InitMessage(7, 1);
      SE(0);
    }
    goto LABEL_32;
  }
  v7 = minMaxPar[csrNo];
  v8 = v7[0];
  v9 = v7[1];
  if (CsrTopReturn(NowCsr, 0))
    return;
  if ((u32)(csrNo - 5) < 0xFFFFFFFC)
    goto LABEL_32;
  if ((u32)csrNo != 1)
    goto LABEL_24;
  goto LABEL_18;
LABEL_19:
  if (GetConfigData(3) == 2)
    goto LABEL_32;
LABEL_24:
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
  goto LABEL_32;
LABEL_18:
  goto LABEL_19;
LABEL_32:
  setNo = NowCsr->setNo;
  SetConfigData(setNo, ConfigData);
}

// 0x18c82b0
void Draw(void) {
  ConfigCursor *NowCsr;
  s32 setNo;

  NowCsr = GetNowCsr();
  setNo = NowCsr->setNo;
  MenuHelpDraw(instance, setNo, helpText, 0);
  cmpCmpGuideSet(42, 0, 90);
}

// 0x18c8250
static bool IsBorderless(void) {
  return GetConfigData(3) == 2;
}

// 0x18c8440
static bool IsWindowed(void) {
  return GetConfigData(3) == 0;
}
