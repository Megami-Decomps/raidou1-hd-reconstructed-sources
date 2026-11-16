#include "types.h"
#include "buttonguide.h"
#include "cfg.h"
#include "configgamepad.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3kernelcore.h"
#include "dds3padmanager.h"
#include "fld.h"
#include "itf.h"
#include "kernel.h"
#include "libsdf.h"
#include "lmap.h"
#include "localize.h"
#include "sbtlsub.h"

#define GUIDE_OPEN_TIME 90
#define GUIDE_CLOSE_TIME 150

typedef struct GuideData GuideData;
typedef struct GuideSet GuideSet;
typedef struct dds3ProcessID_t dds3ProcessID_t;

struct GuideSet {
    s32 button1;
    char *btnName1;
    s32 button2;
    char *btnName2;
    char *text;
};

struct GuideData {
    char *name;
    char *category;
    GuideSet *guideSet[7];
};

static void *GuideList;
static void *_buttonguideUI;
static bool TimeCheck;
static s32 StartTime;
static s32 WaitTime;
s32 GuideNowAnm;
static bool TypeClose;
char *GuideName;
static void *LineHelpUI;
static char *oldLineHelpLabel;
static void *_bakbuttonguideUI;
static void *bakLineHelpUI;
static dds3ProcessID_t *g_mainPID;
static void *TmpButtonguideUI;
static bool TmpTimeCheck;
static s32 TmpStartTime;
static s32 TmpWaitTime;
static s32 TmpGuideNowAnm;
static bool TmpTypeClose;
static char *TmpGuideName;
static void *TmpLineHelpUI;

static bool GuideCheck(bool reset);
static bool GuideResetCheck(void);
static bool GuideResetCheckLmap(void);
static bool GuideResetCheck_2(bool reset);
static bool TmpGuideCheck(bool reset);
static void *GetUDLR_Spr(s32 keyID1, s32 keyID2);
static void *GetJA_Spr(s32 cfg1, s32 cfg2);
static void *GetRA_Spr(s32 cfg1, s32 cfg2);
bool mapAutoMapLAnalogCheck(SDF_PADMAP key);

// 0x1d753d0
void ButtonGuideInit(void) {
  void *Asset;
  s64 naturalAligment;
  void *v6;
  void *v7;
  s64 v9;

  ButtonGuideDispOff();
  TimeCheck = 0;
  Asset = LoadAsset(_Ctrl_k__BackingField, "common", "ButtonGuideTbl", 0);
  if (!Asset)
  {
    v7 = 0;
    GuideList = 0;
LABEL_16:
    return;
  }
  if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_ButtonGuideTbl)
      v6 = Asset;
    else
      v6 = 0;
  }
  else
  {
    v6 = 0;
  }
  GuideList = v6;
  if (Asset->klass->_2.naturalAligment >= (u32)v9)
  {
    if (Asset->klass->_2.typeHierarchy[v9 - 1] == Project_ButtonGuideTbl)
      v7 = Asset;
    else
      v7 = 0;
    goto LABEL_16;
  }
}

// 0x1d75870
void GuideObjSet(void *GuideObj, bool SetLineHelp) {
  Il2CppObject *Component_object;
  Il2CppClass *klass;
  Il2CppObject *v12;
  Il2CppObject *v14;
  char *v19;

  Component_object = GetComponent_object_(GuideObj);
  if (op_Inequality(Component_object, 0, 0))
  {
    GuideObj = Component_object[2].klass;
    klass = Component_object[3].klass;
    BaseBroadObj = klass;
    ButtonLineHelpSet(Component_object[2].monitor, SetLineHelp);
  }
  ButtonGuideObj = GuideObj;
  v12 = GetComponent_object_(ButtonGuideObj);
  _buttonguideUI = (void *)v12;
  v14 = GetComponent_object_(ButtonGuideObj);
  buttonGuideRect = v14;
  oldLineHelpLabel = 0;
  fldSetupObject(ButtonGuideObj, 0);
  fldSetupObject(BaseBroadObj, 0);
  ButtonGuideDispOff();
  v19 = "";
  GuideName = "";
}

// 0x1d75b50
void GuideObjClr(void) {
  fldSetupObject(ButtonGuideObj, 0);
  fldSetupObject(LineHelpObj, 0);
  fldSetupObject(BaseBroadObj, 0);
  ButtonGuideObj = 0;
  LineHelpObj = 0;
  BaseBroadObj = 0;
  oldLineHelpLabel = 0;
}

// 0x1d75c90
dds3ProcessFunc_t ButtonGuideMain(dds3ProcessID_t *id) {
  u32 playtime;

  if (!GuideCheck(0))
    return 0;
  if (TypeClose)
  {
    ButtonGuideDispOut();
    playtime = GBWK->playtime;
    TypeClose = 0;
    StartTime = playtime;
    WaitTime = 90;
    return 0;
  }
  ButtonGuideDispIn();
  return 0;
}

// 0x1d76690
void ButtonGuideDispSet(char *name, bool timer, s32 waitTimer) {
  GuideData *GuideData;
  GuideSet *v12;
  char *category;
  GuideSet *guideSet;
  s64 i;
  char *LocalizeText;
  s32 button1;
  void *v20;
  GuideSet *v21;
  void *v24;
  void *v26;
  char *text;
  void *v28;
  void *v29;
  char TypeClose_local;
  char v35;
  u32 playtime;

  if (IsNullOrEmpty(name, 0))
    return;
  GuideData = GetGuideData(GuideList, name);
  v12 = GuideData->guideSet[0];
  WaitTime = waitTimer;
  if (v12->button1 > 0)
  {
    category = GuideData->category;
    GuideName = category;
    guideSet = GuideData->guideSet;
    if (SLODWORD(guideSet->max_length) >= 1)
    {
      for (i = 0; i < SLODWORD(guideSet->max_length); ++i)
      {
        while (1)
        {
          button1 = guideSet[i]->button1;
          if (button1 > 0)
            break;
          v28 = _buttonguideUI->guideObj[i];
          fldSetupObject(v28, 0);
          guideSet = GuideData->guideSet;
          if (++i >= SLODWORD(guideSet->max_length))
            goto LABEL_41;
        }
        v20 = _buttonguideUI->guideObj[i];
        fldSetupObject(v20, 1);
        v21 = GuideData->guideSet[i];
        if (!ChangeMain(_buttonguideUI, i, v21->button1, v21->button2, 0))
        {
          if (GuideData->guideSet[i]->button2 <= 0)
          {
            v29 = _buttonguideUI->subObj[i];
            fldSetupObject(v29, 0);
            goto LABEL_27;
          }
          v24 = _buttonguideUI->subObj[i];
          fldSetupObject(v24, 1);
          ChangeSub(_buttonguideUI, i, GuideData->guideSet[i]->button2, 0);
        }
LABEL_27:
        v26 = _buttonguideUI->_guideText[i];
        text = GuideData->guideSet[i]->text;
        LocalizeText = GetLocalizeText(text, 1);
        (v26->klass->vtable._66_set_text.methodPtr)(v26, LocalizeText, v26->klass->vtable._66_set_text.method);
        guideSet = GuideData->guideSet;
      }
    }
LABEL_41:
    if (timer)
    {
      if (TypeClose)
        goto LABEL_44;
      ButtonGuideDispOff();
      v35 = 1;
      goto LABEL_59;
    }
LABEL_44:
    ButtonGuideDispOn();
    if (timer)
    {
LABEL_53:
      v35 = 1;
LABEL_59:
      TypeClose_local = v35;
      goto LABEL_60;
    }
    TypeClose_local = TypeClose;
    if (TypeClose_local)
      goto LABEL_53;
    v35 = 0;
LABEL_60:
    TimeCheck = TypeClose_local;
    playtime = GBWK->playtime;
    StartTime = playtime;
    return;
  }
  ButtonGuideDispOff();
  TimeCheck = 0;
}

// 0x1d76d20
void ButtonAliasGuideDispSet(char *name, bool timer, s32 waitTimer) {
  if (!op_Inequality(GuideName, name, 0))
    return;
  ButtonGuideDispSet(name, timer, waitTimer);
}

// 0x1d75e60
static bool GuideCheck(bool reset) {
  bool v9;
  u32 playtime;

  if (!TimeCheck)
    return 0;
  if (TypeClose)
    goto LABEL_40;
  if (StartTime < 0 || reset)
    goto LABEL_35;
  if (!!fldProcCheckFlag(0x40u))
  {
    if ((u32)(SequenceControl->phase - 19) <= 1)
    {
      goto LABEL_40;
    }
  }
  goto LABEL_30;
LABEL_35:
  playtime = GBWK->playtime;
  StartTime = playtime;
  goto LABEL_40;
LABEL_30:
  v9 = lmapProcCheckFlag();
  if (!v9)
    goto LABEL_35;
LABEL_40:
  return WaitTime + StartTime < (s64)GBWK->playtime;
}

// 0x1d76e50
static bool GuideResetCheck(void) {
  if (!fldProcCheckFlag(0x40u))
    return 0;
  return (u32)(SequenceControl->phase - 19) < 2;
}

// 0x1d76f10
static bool GuideResetCheckLmap(void) {
  return lmapProcCheckFlag();
}

// 0x1d76f80
static bool GuideResetCheck_2(bool reset) {
  if (StartTime < 0)
    return 1;
  if (reset)
    return 1;
  return !fldProcCheckFlag(0x40u);
}

// 0x1d765c0
void ButtonGuideTimerReset(void) {
  u32 playtime;

  playtime = GBWK->playtime;
  StartTime = playtime;
  return;
}

// 0x1d76bf0
void ButtonGuideDispOn(void) {
  if (GuideNowAnm == 2)
    return;
  mapUI_DispChange(1);
  fldSetupObject(ButtonGuideObj, 1);
  fldSetupObject(BaseBroadObj, 1);
  GuideNowAnm = 2;
  return;
}

// 0x1d761c0
void ButtonGuideDispIn(void) {
  if (GuideNowAnm == 1)
    return;
  if (GuideNowAnm == 2)
    return;
  mapUI_DispChange(1);
  fldSetupObject(ButtonGuideObj, 1);
  fldSetupObject(BaseBroadObj, 1);
  GuideNowAnm = 1;
}

// 0x1d755c0
void ButtonGuideDispOff(void) {
  void *v9;

  mapUI_DispChange(3);
  if (!GuideNowAnm)
    return;
  fldSetupObject(ButtonGuideObj, 0);
  ButtonLineHelpDispSet(0);
  if (op_Equality(LineHelpObj, 0, 0))
  {
    goto LABEL_26;
  }
  v9 = LineHelpObj;
  if (!op_Inequality(v9, 0, 0))
    goto LABEL_29;
  goto LABEL_23;
  if (op_Inequality(v9, 0, 0))
  {
LABEL_23:
    if (get_activeSelf(LineHelpObj, 0))
      goto LABEL_29;
LABEL_26:
    fldSetupObject(BaseBroadObj, 0);
    goto LABEL_29;
  }
LABEL_29:
  *(u64 *)&WaitTime = 90;
}

// 0x1d76300
void ButtonGuideDispOut(void) {
  void *v9;

  mapUI_DispChange(3);
  if (GuideNowAnm == 3)
    return;
  if (GuideNowAnm)
  {
    fldSetupObject(ButtonGuideObj, 0);
    if (op_Equality(LineHelpObj, 0, 0))
    {
      goto LABEL_29;
    }
    v9 = LineHelpObj;
    if (!op_Inequality(v9, 0, 0))
      goto LABEL_32;
LABEL_26:
    if (get_activeSelf(LineHelpObj, 0))
      goto LABEL_32;
LABEL_29:
    fldSetupObject(BaseBroadObj, 0);
    goto LABEL_32;
    if (!op_Inequality(v9, 0, 0))
    {
LABEL_32:
      *(u64 *)&WaitTime = 0x30000005ALL;
      return;
    }
    goto LABEL_26;
  }
}

// 0x1d77420
void CheckPlayerCtrl(void) {
  u32 playtime;

  if (!TimeCheck)
    return;
  if (TypeClose)
    return;
  if (CHECK_PRESS(4102, 1) || CHECK_PRESS(4103, 1) || CHECK_PRESS(4100, 1) || CHECK_PRESS(4101, 1) || CHECK_PRESS(4099, 1) || CHECK_PRESS(4096, 1) || CHECK_PRESS(4098, 1) || CHECK_PRESS(4097, 1) || CHECK_PRESS(4104, 1) || CHECK_PRESS(4105, 1) || CHECK_PRESS(4107, 1) || CHECK_PRESS(4108, 1) || CHECK_PRESS(4110, 1) || CHECK_PRESS(4111, 1) || CHECK_PRESS(4106, 1) || CHECK_PRESS(4109, 1))
  {
    goto LABEL_50;
  }
  if (mapAutoMapLAnalogCheck(4102))
    goto LABEL_50;
  if (mapAutoMapLAnalogCheck(4103))
    goto LABEL_50;
  if (mapAutoMapLAnalogCheck(4100))
    goto LABEL_50;
  if (mapAutoMapLAnalogCheck(4101))
  {
LABEL_50:
    ButtonGuideDispOut();
    playtime = GBWK->playtime;
    StartTime = playtime;
    return;
  }
}

// 0x1d77790
bool ButtonIsGuideButtonHit(void) {
  return 0;
}

// 0x1d777a0
void SetTypeClose(bool flg) {
  TypeClose = flg;
}

// 0x1d77810
void ButtonGuideDispDel(void) {
  void *v5;

  fldSetupObject(ButtonGuideObj, 0);
  if (op_Equality(LineHelpObj, 0, 0))
  {
    goto LABEL_21;
  }
  v5 = LineHelpObj;
  if (!op_Inequality(v5, 0, 0))
    goto LABEL_24;
  if (get_activeSelf(LineHelpObj, 0))
    goto LABEL_24;
LABEL_21:
  fldSetupObject(BaseBroadObj, 0);
LABEL_24:
  TimeCheck = 0;
  *(u64 *)&WaitTime = 90;
}

// 0x1d77a30
char *GuideNameGet(void) {
  return GuideName;
}

// 0x1d77ab0
void GuideDispStop(bool disp) {
  if (disp)
  {
    *((u8 *)*((MethodInfo *)ButtonGuide + 2).virtualMethodPointer + 32) = 1;
    return;
  }
  ButtonGuideDispOff();
  TimeCheck = 0;
  StartTime = -1;
}

// 0x1d75a90
void ButtonLineHelpSet(void *HelpObj, bool setup) {
  Il2CppObject *Component_object;

  LineHelpObj = HelpObj;
  Component_object = GetComponent_object_(LineHelpObj);
  LineHelpUI = (void *)Component_object;
  ButtonLineHelpDispSet(setup);
}

// 0x1d77060
void ButtonLineHelpDispSet(bool setup) {
  void *v8;
  void *v13;
  void *v15;
  void *v18;
  void *helpText;

  if (op_Equality(LineHelpObj, 0, 0))
    return;
  v8 = LineHelpObj;
  fldSetupObject(v8, setup);
  if (setup)
  {
    fldSetupObject(BaseBroadObj, 1);
    return;
  }
  v13 = BaseBroadObj;
  if (op_Equality(v13, 0, 0))
    goto LABEL_34;
  v15 = BaseBroadObj;
  if (!op_Inequality(v15, 0, 0))
    goto LABEL_37;
  if (!get_activeSelf(BaseBroadObj, 0))
  {
LABEL_34:
    v18 = BaseBroadObj;
    fldSetupObject(v18, 0);
    goto LABEL_37;
  }
LABEL_37:
  if (!op_Inequality(LineHelpUI, 0, 0))
    return;
  helpText = LineHelpUI->helpText;
  (helpText->klass->vtable._66_set_text.methodPtr)(helpText, "", helpText->klass->vtable._66_set_text.method);
  oldLineHelpLabel = 0;
}

// 0x1d77b60
void ButtonLineHelpTextSetNoConvert(char *newText, u32 color) {
  u32 rgba;
  void *helpText;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  void *v20;
  void *v22;
  char *v23;
  void *v25;
  void *scrollCtrler;

  if (op_Equality(LineHelpObj, 0, 0))
    return;
  if (op_Equality(LineHelpUI, 0, 0))
    return;
  rgba = itfGetFontColorUnity2(color, 0, 1).rgba;
  helpText = LineHelpUI->helpText;
  v14 = (helpText->klass->vtable._22_get_color.methodPtr)(helpText, helpText->klass->vtable._22_get_color.method);
  v17 = (f32)HIBYTE(rgba) / 255.0;
  if ((f32)((f32)((f32)(v18 - v17) * (f32)(v18 - v17)) + (f32)((f32)((f32)(v16 - (f32)((f32)BYTE2(rgba) / 255.0)) * (f32)(v16 - (f32)((f32)BYTE2(rgba) / 255.0))) + (f32)((f32)((f32)(v14 - (f32)((f32)(u8)rgba / 255.0)) * (f32)(v14 - (f32)((f32)(u8)rgba / 255.0))) + (f32)((f32)(v15 - (f32)((f32)BYTE1(rgba) / 255.0)) * (f32)(v15 - (f32)((f32)BYTE1(rgba) / 255.0)))))) >= 9.9999994e-11)
  {
    v20 = LineHelpUI->helpText;
    (v20->klass->vtable._23_set_color.methodPtr)(v20, v20->klass->vtable._23_set_color.(f32)(u8)rgba / 255.0, (f32)BYTE1(rgba) / 255.0, (f32)BYTE2(rgba) / 255.0, v17);
  }
  v22 = LineHelpUI->helpText;
  v23 = (v22->klass->vtable._65_get_text.methodPtr)(v22, v22->klass->vtable._65_get_text.method);
  if (op_Inequality(v23, newText, 0))
  {
    v25 = LineHelpUI->helpText;
    (v25->klass->vtable._66_set_text.methodPtr)(v25, newText, v25->klass->vtable._66_set_text.method);
    scrollCtrler = LineHelpUI->scrollCtrler;
    MeshClear(scrollCtrler);
    LODWORD(scrollCtrler->charaInfo.highlightState.padding.m_Bottom) = 1;
  }
}

// 0x1d77e80
char *ButtonLineHelpTextSet(char *text, bool mark, bool tag, u32 color, bool _textSet) {
  bool v15;
  char *v16;
  bool v20;
  void *markObj;
  void *helpText;
  char *v25;
  char *LocalizeText;
  char *SkillHelpValue;
  u32 rgba;
  void *v34;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  void *v41;
  void *v43;
  void *scrollCtrler;

  v15 = op_Equality(LineHelpObj, 0, 0);
  v16 = 0;
  if (v15)
    return v16;
  v20 = op_Equality(LineHelpUI, 0, 0);
  v16 = 0;
  if (v20)
    return v16;
  markObj = LineHelpUI->markObj;
  fldSetupObject(markObj, mark);
  helpText = LineHelpUI->helpText;
  v25 = (helpText->klass->vtable._65_get_text.methodPtr)(helpText, helpText->klass->vtable._65_get_text.method);
  LocalizeText = GetLocalizeText(text, 1);
  if (!text)
    goto LABEL_31;
  if (Contains(text, "SKILLHELP_L", 0))
  {
    SkillHelpValue = sBtlGetSkillHelpValue(nowSkillHelpID, LocalizeText);
LABEL_30:
    LocalizeText = SkillHelpValue;
    goto LABEL_31;
  }
  if (Contains(text, "ITEMHELP_L", 0))
  {
    SkillHelpValue = sBtlGetItemHelpValue(nowItemHelpID, LocalizeText);
    goto LABEL_30;
  }
LABEL_31:
  if (op_Equality(oldLineHelpLabel, text, 0) && textSet)
    return v25;
  if (tag)
  {
    LocalizeText = itfTextTagReplace(LocalizeText, 1);
  }
  oldLineHelpLabel = text;
  rgba = itfGetFontColorUnity2(color, 0, 1).rgba;
  v34 = LineHelpUI->helpText;
  v35 = (v34->klass->vtable._22_get_color.methodPtr)(v34, v34->klass->vtable._22_get_color.method);
  v38 = (f32)HIBYTE(rgba) / 255.0;
  if ((f32)((f32)((f32)(v39 - v38) * (f32)(v39 - v38)) + (f32)((f32)((f32)(v37 - (f32)((f32)BYTE2(rgba) / 255.0)) * (f32)(v37 - (f32)((f32)BYTE2(rgba) / 255.0))) + (f32)((f32)((f32)(v35 - (f32)((f32)(u8)rgba / 255.0)) * (f32)(v35 - (f32)((f32)(u8)rgba / 255.0))) + (f32)((f32)(v36 - (f32)((f32)BYTE1(rgba) / 255.0)) * (f32)(v36 - (f32)((f32)BYTE1(rgba) / 255.0)))))) >= 9.9999994e-11)
  {
    v41 = LineHelpUI->helpText;
    (v41->klass->vtable._23_set_color.methodPtr)(v41, v41->klass->vtable._23_set_color.(f32)(u8)rgba / 255.0, (f32)BYTE1(rgba) / 255.0, (f32)BYTE2(rgba) / 255.0, v38);
  }
  v16 = Trim(LocalizeText, 0);
  if (op_Inequality(v25, v16, 0) && textSet)
  {
    v43 = LineHelpUI->helpText;
    (v43->klass->vtable._66_set_text.methodPtr)(v43, v16, v43->klass->vtable._66_set_text.method);
    scrollCtrler = LineHelpUI->scrollCtrler;
    MeshClear(scrollCtrler);
    LODWORD(scrollCtrler->charaInfo.highlightState.padding.m_Bottom) = 1;
  }
  return v16;
}

// 0x1d783b0
char *ButtonLineHelpAddTextSet(char *_addTextLabel, bool tag, s32 _empty, bool _textSet) {
  bool v13;
  char *v14;
  bool v18;
  char *LocalizeText;
  char *SkillHelpValue;
  char *v24;
  char *v25;
  char *v26;
  void *helpText;
  char *v29;
  char *v30;
  void *v31;
  char *v32;
  void *v34;
  char *v35;
  char *v36;

  v13 = op_Equality(LineHelpObj, 0, 0);
  v14 = 0;
  if (v13)
    return v14;
  v18 = op_Equality(LineHelpUI, 0, 0);
  v14 = 0;
  if (v18)
    return v14;
  LocalizeText = GetLocalizeText(addTextLabel, 1);
  if (addTextLabel)
  {
    if (Contains(addTextLabel, "SKILLHELP_L", 0))
    {
      SkillHelpValue = sBtlGetSkillHelpValue(nowSkillHelpID, LocalizeText);
    }
    else
    {
      if (!Contains(addTextLabel, "ITEMHELP_L", 0))
        goto LABEL_27;
      SkillHelpValue = sBtlGetItemHelpValue(nowItemHelpID, LocalizeText);
    }
    LocalizeText = SkillHelpValue;
  }
LABEL_27:
  if (tag)
  {
    LocalizeText = itfTextTagReplace(LocalizeText, 1);
  }
  v24 = Trim(LocalizeText, 0);
  if (empty < 1)
  {
    v25 = 0;
    v14 = Concat_54766928(0, v24, 0);
    if (!textSet)
      return v14;
  }
  else
  {
    v25 = 0;
    do
    {
      v26 = Concat_54766928(v25, " ", 0);
      v25 = v26;
      --empty;
    }
    while (empty);
    v14 = Concat_54766928(v26, v24, 0);
    if (!textSet)
      return v14;
  }
  helpText = LineHelpUI->helpText;
  v29 = (helpText->klass->vtable._65_get_text.methodPtr)(helpText, helpText->klass->vtable._65_get_text.method);
  v30 = Concat_54831728(v29, v25, v24, 0);
  v31 = LineHelpUI->helpText;
  v32 = (v31->klass->vtable._65_get_text.methodPtr)(v31, v31->klass->vtable._65_get_text.method);
  if (op_Inequality(v32, v30, 0))
  {
    v34 = LineHelpUI->helpText;
    v35 = (v34->klass->vtable._65_get_text.methodPtr)(v34, v34->klass->vtable._65_get_text.method);
    v36 = Concat_54831728(v35, v25, v24, 0);
    (v34->klass->vtable._66_set_text.methodPtr)(v34, v36, v34->klass->vtable._66_set_text.method);
  }
  return v14;
}

// 0x1d787c0
void ButtonTmpGuideObjSet(void *GuideObj, bool SetLineHelp) {
  Il2CppObject *Component_object;
  void *monitor;
  Il2CppClass *klass;
  Il2CppObject *v12;
  char *v16;
  Il2CppObject *ProcessData;
  void *v21;
  dds3ProcessFunc_t v22;
  shutdownfuncDelegate v23;
  dds3ProcessID_t *started;

  Component_object = GetComponent_object_(GuideObj);
  if (op_Inequality(Component_object, 0, 0))
  {
    GuideObj = Component_object[2].klass;
    monitor = Component_object[2].monitor;
    ButtonTmpLineHelpSet(monitor, SetLineHelp);
    klass = Component_object[3].klass;
    TmpBaseBroadObj = klass;
  }
  TmpButtonGuideObj = GuideObj;
  v12 = GetComponent_object_(TmpButtonGuideObj);
  TmpButtonguideUI = (void *)v12;
  fldSetupObject(TmpButtonGuideObj, 0);
  fldSetupObject(TmpBaseBroadObj, 0);
  ButtonTmpGuideDispOff();
  v16 = "";
  TmpGuideName = "";
  if (g_mainPID)
  {
    goto LABEL_15;
  }
  else
  {
    v21 = Allocate(Project_ButtonGuide_TmpButtonGuideWk);
    _ctor(v21, 0);
    Init(v21, 0);
    v22 = Allocate(dds3ProcessFunc_t);
    _ctor(v22, 0, Method_Project_ButtonGuide_TmpGuideMain__, 0);
    v23 = Allocate(shutdownfuncDelegate);
    _ctor(v23, 0, Method_Project_ButtonGuide_ShutDown__, 0);
    started = dds3StartProcess("TmpButtonGuide", 21011, 0, 0, v22, v23, v21);
    g_mainPID = started;
LABEL_15:
    goto LABEL_16;
  }
LABEL_16:
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  LOBYTE(ProcessData[1].klass) = 1;
}

// 0x1d78b80
void ButtonTmpLineHelpSet(void *HelpObj, bool setup) {
  Il2CppObject *Component_object;

  TmpLineHelpObj = HelpObj;
  Component_object = GetComponent_object_(TmpLineHelpObj);
  TmpLineHelpUI = (void *)Component_object;
  ButtonTmpLineHelpDispSet(setup);
}

// 0x1d78eb0
void ButtonTmpLineHelpDispSet(bool setup) {
  void *v8;
  void *v13;
  void *v15;
  void *v18;

  if (op_Equality(TmpLineHelpObj, 0, 0))
    return;
  v8 = TmpLineHelpObj;
  fldSetupObject(v8, setup);
  if (setup)
  {
    fldSetupObject(TmpBaseBroadObj, 1);
    return;
  }
  v13 = TmpBaseBroadObj;
  if (op_Equality(v13, 0, 0))
    goto LABEL_36;
  v15 = TmpBaseBroadObj;
  if (!op_Inequality(v15, 0, 0))
    return;
  if (!get_activeSelf(TmpBaseBroadObj, 0))
  {
LABEL_36:
    v18 = TmpBaseBroadObj;
    fldSetupObject(v18, 0);
    return;
  }
}

// 0x1d78c40
void ButtonTmpGuideDispOff(void) {
  void *v8;

  if (!GuideNowAnm)
    return;
  fldSetupObject(TmpButtonGuideObj, 0);
  ButtonTmpLineHelpDispSet(0);
  if (op_Equality(TmpLineHelpObj, 0, 0))
  {
    goto LABEL_24;
  }
  v8 = TmpLineHelpObj;
  if (!op_Inequality(v8, 0, 0))
    goto LABEL_27;
  goto LABEL_21;
  if (op_Inequality(v8, 0, 0))
  {
LABEL_21:
    if (get_activeSelf(TmpLineHelpObj, 0))
      goto LABEL_27;
LABEL_24:
    fldSetupObject(TmpBaseBroadObj, 0);
    goto LABEL_27;
  }
LABEL_27:
  *(u64 *)&TmpWaitTime = 90;
}

// 0x1d791b0
void ButtonTmpGuideObjClr(void) {
  s64 i;
  void *guideObj;
  void *v9;
  Il2CppObject *ProcessData;

  if (op_Inequality(TmpButtonguideUI, 0, 0))
  {
    for (i = 0; ; ++i)
    {
      guideObj = TmpButtonguideUI->guideObj;
      if (i >= SLODWORD(guideObj->max_length))
        goto LABEL_19;
      v9 = guideObj[i];
      fldSetupObject(v9, 0);
    }
  }
LABEL_19:
  fldSetupObject(TmpButtonGuideObj, 0);
  fldSetupObject(TmpLineHelpObj, 0);
  fldSetupObject(TmpBaseBroadObj, 0);
  TmpButtonGuideObj = 0;
  TmpLineHelpObj = 0;
  TmpBaseBroadObj = 0;
  if (!g_mainPID)
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  LOBYTE(ProcessData[1].klass) = 0;
}

// 0x1d794b0
dds3ProcessFunc_t ButtonTmpGuideMain(dds3ProcessID_t *id) {
  Il2CppObject *ProcessData;
  u32 playtime;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (!LOBYTE(ProcessData[1].klass))
    return 0;
  if (!TmpGuideCheck(0))
    return 0;
  if (TmpTypeClose)
  {
    ButtonTmpGuideDispOut();
    playtime = GBWK->playtime;
    TmpTypeClose = 0;
    TmpStartTime = playtime;
    TmpWaitTime = 90;
    return 0;
  }
  ButtonTmpGuideDispIn();
  return 0;
}

// 0x1d79e90
void ButtonShutDown(dds3ProcessID_t *id) {
  ;
}

// 0x1d79ea0
void ButtonTmpGuideDispSet(char *name, bool timer, s32 waitTimer) {
  GuideData *GuideData;
  GuideData *v10;
  char *category;
  GuideSet *guideSet;
  s64 v16;
  char *LocalizeText;
  s32 button1;
  void *v21;
  GuideSet *v22;
  void *v25;
  void *v27;
  char *text;
  void *v29;
  void *v30;
  char TmpTypeClose_local;
  char v35;
  u32 playtime;

  GuideData = GetGuideData(GuideList, name, *(const MethodInfo **)&waitTimer);
  if (!GuideData)
    return;
  v10 = GuideData;
  category = GuideData->category;
  TmpGuideName = category;
  TmpWaitTime = waitTimer;
  guideSet = v10->guideSet;
  if (guideSet[0]->button1 < 1)
  {
    ButtonTmpGuideDispOff();
    TmpTimeCheck = 0;
    return;
  }
  if (SLODWORD(guideSet->max_length) < 1)
    goto LABEL_42;
  v16 = 0;
  do
  {
    while (1)
    {
      button1 = guideSet[v16]->button1;
      if (button1 <= 0)
        break;
      v21 = TmpButtonguideUI->guideObj[v16];
      fldSetupObject(v21, 1);
      v22 = v10->guideSet[v16];
      if (!ChangeMain(TmpButtonguideUI, v16, v22->button1, v22->button2, 0))
      {
        if (v10->guideSet[v16]->button2 <= 0)
        {
          v30 = TmpButtonguideUI->subObj[v16];
          fldSetupObject(v30, 0);
          goto LABEL_27;
        }
        v25 = TmpButtonguideUI->subObj[v16];
        fldSetupObject(v25, 1);
        ChangeSub(TmpButtonguideUI, v16, v10->guideSet[v16]->button2, 0);
      }
LABEL_27:
      v27 = TmpButtonguideUI->_guideText[v16];
      text = v10->guideSet[v16]->text;
      LocalizeText = GetLocalizeText(text, 1);
      (v27->klass->vtable._66_set_text.methodPtr)(v27, LocalizeText, v27->klass->vtable._66_set_text.method);
      guideSet = v10->guideSet;
      if (++v16 >= SLODWORD(guideSet->max_length))
        goto LABEL_41;
    }
    v29 = TmpButtonguideUI->guideObj[v16];
    fldSetupObject(v29, 0);
    guideSet = v10->guideSet;
    ++v16;
  }
  while (v16 < SLODWORD(guideSet->max_length));
LABEL_41:
LABEL_42:
  if (timer)
  {
    if (TmpTypeClose)
      goto LABEL_45;
    ButtonTmpGuideDispOff();
    v35 = 1;
LABEL_60:
    TmpTypeClose_local = v35;
    goto LABEL_61;
  }
LABEL_45:
  ButtonTmpGuideDispOn();
  if (timer)
  {
LABEL_54:
    v35 = 1;
    goto LABEL_60;
  }
  TmpTypeClose_local = TmpTypeClose;
  if (TmpTypeClose_local)
    goto LABEL_54;
  v35 = 0;
LABEL_61:
  TmpTimeCheck = TmpTypeClose_local;
  goto LABEL_63;
LABEL_64:
  playtime = GBWK->playtime;
  goto LABEL_65;
LABEL_63:
  goto LABEL_64;
LABEL_65:
  TmpStartTime = playtime;
}

// 0x1d79710
static bool TmpGuideCheck(bool reset) {
  u32 playtime;

  if (!TmpTimeCheck)
    return 0;
  if (TmpTypeClose)
    goto LABEL_32;
  if (TmpStartTime < 0 || reset)
  {
LABEL_27:
    playtime = GBWK->playtime;
    TmpStartTime = playtime;
    goto LABEL_32;
  }
  if (!fldProcCheckFlag(0x40u))
    goto LABEL_27;
  if ((u32)(SequenceControl->phase - 19) >= 2)
    goto LABEL_27;
LABEL_32:
  return TmpWaitTime + TmpStartTime < (s64)GBWK->playtime;
}

// 0x1d799d0
void ButtonTmpGuideDispIn(void) {
  if (TmpGuideNowAnm == 1)
    return;
  if (TmpGuideNowAnm != 2)
  {
    fldSetupObject(TmpButtonGuideObj, 1);
    fldSetupObject(TmpBaseBroadObj, 1);
    TmpGuideNowAnm = 1;
    return;
  }
}

// 0x1d79b30
void ButtonTmpGuideDispOut(void) {
  void *v8;

  if (TmpGuideNowAnm == 3)
    return;
  if (TmpGuideNowAnm)
  {
    fldSetupObject(TmpButtonGuideObj, 0);
    if (op_Equality(TmpLineHelpObj, 0, 0))
    {
      goto LABEL_27;
    }
    v8 = TmpLineHelpObj;
    if (!op_Inequality(v8, 0, 0))
      goto LABEL_30;
LABEL_24:
    if (get_activeSelf(TmpLineHelpObj, 0))
      goto LABEL_30;
LABEL_27:
    fldSetupObject(TmpBaseBroadObj, 0);
    goto LABEL_30;
    if (!op_Inequality(v8, 0, 0))
    {
LABEL_30:
      *(u64 *)&TmpWaitTime = 0x30000005ALL;
      return;
    }
    goto LABEL_24;
  }
}

// 0x1d79dc0
void ButtonTmpGuideTimerReset(void) {
  u32 playtime;

  playtime = GBWK->playtime;
  TmpStartTime = playtime;
  return;
}

// 0x1d7a400
void ButtonTmpGuideDispOn(void) {
  if (TmpGuideNowAnm == 2)
    return;
  fldSetupObject(TmpButtonGuideObj, 1);
  fldSetupObject(TmpBaseBroadObj, 1);
  TmpGuideNowAnm = 2;
  return;
}

// 0x1d7a520
void *ButtonGetConfigToSetSpr(s32 setSpr, s32 org_setSpr, s32 setSprSub, s32 org_setSprSub) {
  const MethodInfo_3363EC0 *v5;
  s32 PadMapToKeyID;
  s32 v9;
  s32 Item4;
  s32 Item3;
  s32 v12;
  s32 v13;
  s32 v14;
  s32 CmnTypeCD;
  s32 ConfigGAMEPAD;
  s64 v19;
  s64 v20;
  System_ValueTuple_int__int__o RA_Spr;
  System_ValueTuple_int__int__o v22;
  System_ValueTuple_int__int__int__int__o v23;
  System_ValueTuple_int__int__int__int__o JA_Spr;
  System_ValueTuple_int__int__int__int__o v25;
  System_ValueTuple_int__int__int__int__o result;

  if (org_setSpr > 42753)
  {
    if ((u32)org_setSpr <= 0xB404)
    {
      if ((u32)org_setSpr <= 0xB004)
      {
        if ((u32)org_setSpr <= 0xA80E)
        {
          switch (org_setSpr)
          {
            case 42761:
              v9 = 116;
              break;
            case 42772:
              JA_Spr = GetJA_Spr(114, 115);
              setSprSub = JA_Spr.Item2;
              Item4 = JA_Spr.Item4;
              Item3 = JA_Spr.Item3;
              setSpr = JA_Spr.Item1;
              goto LABEL_369;
            case 43022:
              v9 = 131;
              break;
            default:
              goto LABEL_367;
          }
        }
        else
        {
          Item4 = -1;
          if ((u32)org_setSpr <= 0xA912)
          {
            Item3 = -1;
            *(u64 *)&setSprSub = 0xFFFFFFFFLL;
            switch (org_setSpr)
            {
              case 43267:
                v9 = 134;
                goto LABEL_363;
              case 43268:
                v9 = 133;
                goto LABEL_363;
              case 43269:
              case 43271:
              case 43272:
              case 43273:
              case 43274:
              case 43275:
              case 43276:
              case 43277:
              case 43278:
              case 43279:
              case 43280:
              case 43281:
                goto LABEL_369;
              case 43270:
                v9 = 135;
                goto LABEL_363;
              case 43282:
                v12 = 136;
                v13 = 137;
                goto LABEL_272;
              default:
                goto LABEL_368;
            }
            goto LABEL_369;
          }
          if (org_setSpr > 45058)
          {
            if (org_setSpr == 45059)
            {
              v9 = 71;
            }
            else
            {
              v9 = 72;
            }
          }
          else if (org_setSpr == 43529)
          {
            v9 = 49;
          }
          else
          {
            Item3 = -1;
            setSprSub = -1;
            if (org_setSpr != 45057)
              goto LABEL_369;
            v9 = 124;
          }
        }
      }
      else if ((u32)org_setSpr <= 0xB113)
      {
        Item4 = -1;
        Item3 = -1;
        setSprSub = -1;
        switch (org_setSpr)
        {
          case 45313:
            v9 = 132;
            break;
          case 45314:
          case 45317:
          case 45318:
          case 45319:
          case 45320:
          case 45321:
          case 45322:
          case 45323:
          case 45324:
          case 45325:
          case 45326:
          case 45327:
          case 45328:
          case 45329:
          case 45330:
            goto LABEL_369;
          case 45315:
            v9 = 73;
            break;
          case 45316:
            v9 = 75;
            break;
          case 45331:
            v9 = 66;
            break;
          default:
            Item3 = -1;
            setSprSub = -1;
            if (org_setSpr != 45075)
              goto LABEL_369;
            v9 = 64;
            break;
        }
      }
      else if ((u32)org_setSpr <= 0xB303)
      {
        if (org_setSpr == 45572)
        {
          v9 = 74;
        }
        else
        {
          if (org_setSpr != 45827)
            goto LABEL_367;
          v9 = 76;
        }
      }
      else if (org_setSpr == 46083)
      {
        v9 = 118;
      }
      else
      {
        if (org_setSpr != 46084)
          goto LABEL_367;
        v9 = 117;
      }
    }
    else if ((u32)org_setSpr <= 0xB903)
    {
      if ((u32)org_setSpr <= 0xB603)
      {
        switch (org_setSpr)
        {
          case 46339:
            v9 = 119;
            break;
          case 46340:
            v9 = 120;
            break;
          case 46595:
            v9 = 122;
            break;
          default:
            goto LABEL_367;
        }
      }
      else if ((u32)org_setSpr <= 0xB803)
      {
        if (org_setSpr == 46596)
        {
          v9 = 123;
        }
        else
        {
          if (org_setSpr != 47107)
            goto LABEL_367;
          v9 = 125;
        }
      }
      else if (org_setSpr == 47108)
      {
        v9 = 126;
      }
      else
      {
        if (org_setSpr != 47363)
          goto LABEL_367;
        v9 = 127;
      }
    }
    else if ((u32)org_setSpr <= 0xBA04)
    {
      if ((u32)org_setSpr <= 0xB913)
      {
        if (org_setSpr != 47364)
        {
          if (org_setSpr != 47379)
            goto LABEL_367;
          PadMapToKeyID = 23;
          goto LABEL_366;
        }
        v9 = 129;
      }
      else if (org_setSpr == 47619)
      {
        v9 = 128;
      }
      else
      {
        if (org_setSpr != 47620)
          goto LABEL_367;
        v9 = 130;
      }
    }
    else
    {
      if ((u32)org_setSpr > 0xBD04)
      {
        if (org_setSpr == 49155)
        {
          PadMapToKeyID = 12;
        }
        else
        {
          if (org_setSpr != 49156)
            goto LABEL_367;
          PadMapToKeyID = 14;
        }
        goto LABEL_366;
      }
      if (org_setSpr == 48132)
      {
        v9 = 65;
      }
      else
      {
        if (org_setSpr != 48388)
          goto LABEL_367;
        v9 = 67;
      }
    }
LABEL_363:
    ConfigGAMEPAD = cfgGetConfigGAMEPAD(v9, 0);
    PadMapToKeyID = ConfigGAMEPAD;
LABEL_366:
    setSpr = dds3PadGetKeyIDToSprNo(PadMapToKeyID);
LABEL_367:
    Item4 = -1;
LABEL_368:
    Item3 = -1;
    setSprSub = -1;
    goto LABEL_369;
  }
  if (org_setSpr <= 41219)
  {
    if (org_setSpr <= 32772)
    {
      if (org_setSpr <= 20489)
      {
        Item4 = -1;
        Item3 = -1;
        setSprSub = -1;
        switch (org_setSpr)
        {
          case 8195:
            v9 = 51;
            goto LABEL_363;
          case 8196:
            v9 = 57;
            goto LABEL_363;
          case 8197:
            v9 = 53;
            goto LABEL_363;
          case 8198:
            v9 = 58;
            goto LABEL_363;
          case 8199:
            v9 = 56;
            goto LABEL_363;
          case 8200:
            v9 = 54;
            goto LABEL_363;
          case 8201:
            v9 = 50;
            goto LABEL_363;
          case 8202:
          case 8203:
          case 8204:
          case 8205:
          case 8207:
          case 8208:
          case 8209:
          case 8210:
            goto LABEL_369;
          case 8206:
            v9 = 59;
            goto LABEL_363;
          case 8211:
            v9 = 52;
            goto LABEL_363;
          default:
            switch (org_setSpr)
            {
              case 20481:
                v9 = 8;
                goto LABEL_363;
              case 20482:
                v9 = 7;
                goto LABEL_363;
              case 20483:
                v9 = 6;
                goto LABEL_363;
              case 20484:
                v9 = 5;
                goto LABEL_363;
              case 20485:
                v9 = 9;
                goto LABEL_363;
              case 20486:
                v9 = 12;
                goto LABEL_363;
              case 20487:
                v9 = 17;
                goto LABEL_363;
              case 20488:
                v9 = 18;
                goto LABEL_363;
              case 20489:
                goto LABEL_199;
              default:
                Item3 = -1;
                setSprSub = -1;
                switch (org_setSpr)
                {
                  case 4097:
                    v9 = 3;
                    goto LABEL_363;
                  case 4098:
                    v9 = 4;
                    goto LABEL_363;
                  case 4099:
                    v14 = 4098;
                    goto LABEL_354;
                  case 4100:
                    v14 = 4099;
LABEL_354:
                    CmnTypeCD = ConfigGameGetCmnTypeCD(v14);
                    PadMapToKeyID = dds3PadGetPadMapToKeyID(CmnTypeCD);
                    goto LABEL_366;
                  case 4101:
                    v9 = 45;
                    goto LABEL_363;
                  case 4102:
                    v9 = 46;
                    goto LABEL_363;
                  default:
                    goto LABEL_369;
                }
            }
        }
      }
      if ((u32)org_setSpr <= 0x7004)
      {
        switch (org_setSpr)
        {
          case 28673:
            v9 = 20;
            goto LABEL_363;
          case 28674:
            v9 = 23;
            goto LABEL_363;
          case 28675:
            v9 = 21;
            goto LABEL_363;
          case 28676:
            v9 = 22;
            goto LABEL_363;
          default:
            if (org_setSpr != 24584)
              goto LABEL_367;
            v9 = 19;
            break;
        }
      }
      else if (org_setSpr == 32771)
      {
        v9 = 25;
      }
      else
      {
        if (org_setSpr != 32772)
          goto LABEL_367;
        v9 = 24;
      }
    }
    else if ((u32)org_setSpr <= 0x9004)
    {
      switch (org_setSpr)
      {
        case 32782:
          v9 = 106;
          break;
        case 36867:
          v9 = 110;
          break;
        case 36868:
          v9 = 111;
          break;
        default:
          goto LABEL_367;
      }
    }
    else if ((u32)org_setSpr <= 0x900E)
    {
      if (org_setSpr == 36873)
      {
        v9 = 112;
      }
      else
      {
        if (org_setSpr != 36878)
          goto LABEL_367;
        v9 = 113;
      }
    }
    else if (org_setSpr == 40963)
    {
      v9 = 60;
    }
    else
    {
      if (org_setSpr != 41219)
        goto LABEL_367;
      v9 = 63;
    }
    goto LABEL_363;
  }
  if ((u32)org_setSpr <= 0xA401)
  {
    if ((u32)org_setSpr > 0xA214)
    {
      if ((u32)org_setSpr <= 0xA30E)
      {
        if (org_setSpr == 41731)
        {
          v9 = 80;
        }
        else
        {
          if (org_setSpr != 41742)
            goto LABEL_367;
          v9 = 77;
        }
        goto LABEL_363;
      }
      if (org_setSpr != 41745)
      {
        if (org_setSpr != 41985)
          goto LABEL_367;
        v9 = 84;
        goto LABEL_363;
      }
      v12 = 78;
      v13 = 79;
      goto LABEL_272;
    }
    switch (org_setSpr)
    {
      case 41225:
        v9 = 68;
        goto LABEL_363;
      case 41234:
        RA_Spr = GetRA_Spr(61, 62);
        Item4 = -1;
        setSpr = RA_Spr.Item1;
        setSprSub = RA_Spr.Item2;
        Item3 = -1;
        break;
      case 41492:
        v23 = GetJA_Spr(69, 70);
        Item3 = v23.Item3;
        setSprSub = v23.Item2;
        Item4 = v23.Item4;
        setSpr = v23.Item1;
        break;
      default:
        goto LABEL_367;
    }
  }
  else
  {
    if ((u32)org_setSpr > 0xA50E)
    {
      if ((u32)org_setSpr > 0xA603)
      {
        if (org_setSpr == 42505)
        {
LABEL_199:
          v9 = 108;
        }
        else
        {
          if (org_setSpr != 42753)
            goto LABEL_367;
          v9 = 121;
        }
        goto LABEL_363;
      }
      if (org_setSpr != 42258)
      {
        if (org_setSpr != 42499)
          goto LABEL_367;
        v9 = 109;
        goto LABEL_363;
      }
      v12 = 89;
      v13 = 90;
LABEL_272:
      v22 = GetRA_Spr(v12, v13);
      Item4 = -1;
      setSprSub = v22.Item2;
      setSpr = v22.Item1;
      Item3 = -1;
      goto LABEL_369;
    }
    if ((u32)org_setSpr <= 0xA413)
    {
      if (org_setSpr != 42002)
      {
        if (org_setSpr != 42003)
          goto LABEL_367;
        v9 = 83;
        goto LABEL_363;
      }
      v12 = 81;
      v13 = 82;
      goto LABEL_272;
    }
    Item4 = -1;
    Item3 = -1;
    setSprSub = -1;
    switch (org_setSpr)
    {
      case 42243:
        v9 = 95;
        goto LABEL_363;
      case 42244:
        v9 = 96;
        goto LABEL_363;
      case 42245:
        v9 = 94;
        goto LABEL_363;
      case 42246:
      case 42249:
      case 42250:
      case 42251:
      case 42252:
      case 42253:
        break;
      case 42247:
        v9 = 92;
        goto LABEL_363;
      case 42248:
        v9 = 93;
        goto LABEL_363;
      case 42254:
        v9 = 91;
        goto LABEL_363;
      default:
        goto LABEL_368;
    }
  }
LABEL_369:
  *(u64 *)&v25.Item1 = &v19;
  *(u64 *)&v25.Item3 = setSpr;
  v19 = 0;
  v20 = 0;
  int__int__int____ctor(v25, setSprSub, Item3, Item4, Method_System_ValueTuple_int__int__int__int___ctor__, v5);
  *(u64 *)&result.Item1 = v19;
  *(u64 *)&result.Item3 = v20;
  return result;
}

// 0x1d7ba00
static void *GetUDLR_Spr(s32 keyID1, s32 keyID2) {
  s32 v5;
  s32 v6;
  System_ValueTuple_int__int__o v7;

  if (!keyID1 && keyID2 == 1 || keyID1 == 1 && !keyID2)
  {
    v5 = 19;
    v6 = 15;
    goto LABEL_8;
  }
  if (keyID1 == 2 && keyID2 == 3 || keyID1 == 3 && keyID2 == 2)
  {
    v5 = 20;
    v6 = 14;
    goto LABEL_8;
  }
  if (keyID1 == 4 && keyID2 == 5 || keyID1 == 5 && keyID2 == 4)
  {
    v5 = 15;
LABEL_19:
    v6 = -1;
    goto LABEL_8;
  }
  if (keyID1 == 6 && keyID2 == 7 || keyID1 == 7 && keyID2 == 6)
  {
    v5 = 14;
    goto LABEL_19;
  }
  if (keyID1 == 8 && keyID2 == 9 || keyID1 == 9 && keyID2 == 8)
  {
    v5 = 17;
    goto LABEL_19;
  }
  if (keyID1 == 10 && keyID2 == 11)
    goto LABEL_34;
  v6 = -1;
  if (keyID1 != 11)
  {
    v5 = -1;
    goto LABEL_8;
  }
  v5 = -1;
  if (keyID2 == 10)
  {
LABEL_34:
    v5 = 16;
    goto LABEL_19;
  }
LABEL_8:
  v7 = 0;
  int____ctor((System_ValueTuple_int__int__o)&v7, v5, v6);
  return v7;
}

// 0x1d7b800
static void *GetJA_Spr(s32 cfg1, s32 cfg2) {
  u16 ConfigGAMEPAD;
  u16 v7;
  const MethodInfo_3363EC0 *v8;
  u32 Item1;
  s32 Item2;
  s32 v11;
  s32 KeyIDToSprNo;
  s32 v15;
  s64 v16;
  s64 v17;
  System_ValueTuple_int__int__o UDLR_Spr;
  System_ValueTuple_int__int__int__int__o v19;
  System_ValueTuple_int__int__int__int__o result;

  ConfigGAMEPAD = cfgGetConfigGAMEPAD(cfg1, 0);
  v7 = cfgGetConfigGAMEPAD(cfg2, 0);
  UDLR_Spr = GetUDLR_Spr(ConfigGAMEPAD, v7);
  Item1 = UDLR_Spr.Item1;
  if (UDLR_Spr.Item1 == -1)
  {
    if ((ConfigGAMEPAD & 0xFFFC) != 0)
    {
      Item1 = dds3PadGetKeyIDToSprNo(ConfigGAMEPAD);
      Item2 = -1;
      v15 = v7;
    }
    else
    {
      Item2 = ConfigGAMEPAD + 25;
      Item1 = ConfigGAMEPAD + 21;
      v15 = v7;
      if (v7 > 3u)
      {
LABEL_18:
        KeyIDToSprNo = dds3PadGetKeyIDToSprNo(v7);
        v11 = -1;
        goto LABEL_10;
      }
    }
    KeyIDToSprNo = 21;
    v11 = 25;
    switch (v15)
    {
      case 0:
        break;
      case 1:
        KeyIDToSprNo = 22;
        v11 = 26;
        break;
      case 2:
        Item1 = 23;
        Item2 = 27;
        goto LABEL_9;
      case 3:
        Item1 = 24;
        Item2 = 28;
        goto LABEL_9;
      default:
        goto LABEL_18;
    }
  }
  else
  {
    Item2 = UDLR_Spr.Item2;
LABEL_9:
    v11 = -1;
    KeyIDToSprNo = -1;
  }
LABEL_10:
  *(u64 *)&v19.Item1 = &v16;
  *(u64 *)&v19.Item3 = Item1;
  v16 = 0;
  v17 = 0;
  int__int__int____ctor(v19, Item2, KeyIDToSprNo, v11, Method_System_ValueTuple_int__int__int__int___ctor__, v8);
  *(u64 *)&result.Item1 = v16;
  *(u64 *)&result.Item3 = v17;
  return result;
}

// 0x1d7b6b0
static void *GetRA_Spr(s32 cfg1, s32 cfg2) {
  s32 ConfigGAMEPAD;
  s32 v7;
  s32 Item1;
  s32 KeyIDToSprNo;
  System_ValueTuple_int__int__o v10;

  ConfigGAMEPAD = (u16)cfgGetConfigGAMEPAD(cfg1, 0);
  v7 = (u16)cfgGetConfigGAMEPAD(cfg2, 0);
  Item1 = GetUDLR_Spr(ConfigGAMEPAD, v7).Item1;
  if (Item1 == -1)
  {
    Item1 = dds3PadGetKeyIDToSprNo(ConfigGAMEPAD);
    KeyIDToSprNo = dds3PadGetKeyIDToSprNo(v7);
  }
  else
  {
    KeyIDToSprNo = -1;
  }
  v10 = 0;
  int____ctor((System_ValueTuple_int__int__o)&v10, Item1, KeyIDToSprNo);
  return v10;
}
