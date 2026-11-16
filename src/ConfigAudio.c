#include "types.h"
#include "cmpmain.h"
#include "configaudio.h"
#include "configunity.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3kernelcore.h"
#include "fld.h"
#include "sdfsound.h"
#include "sndat3.h"
#include "sndmanager.h"

#define DRAW_LIST_MAX 7
#define MOVIE_CHG_SOUND 95

typedef struct CONFIG_WORK CONFIG_WORK;

char *menuText;
char *helpText;
char *selectText;
s32 **minMaxPar;

// 0x18c5940
char *GetSelectText(s32 _setPar, s32 _value) {
  char **v5;
  char **v6;
  char **v7;

  v5 = &"CONFIG_MAIN_L0011";
  if (value)
    v6 = &"CONFIG_MAIN_L0009";
  else
    v6 = &"CONFIG_MAIN_L0010";
  if (value)
    v7 = &"CONFIG_AUDIO_L0007";
  else
    v7 = &"CONFIG_AUDIO_L0006";
  if (setPar == 6)
    v6 = v7;
  if (setPar)
    v5 = v6;
  return *v5;
}

// 0x18c5a10
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
  s32 **v12;
  s32 *v13;
  s32 **v14;
  s32 *v15;
  s32 **v16;
  s32 *v17;

  v3 = NewSpecific(s32, 2u);
  minMaxPar[0] = v3;
  v4 = minMaxPar;
  v5 = NewSpecific(s32, 2u);
  v5[1] = 10;
  v4[1] = v5;
  v6 = minMaxPar;
  v7 = NewSpecific(s32, 2u);
  v6[2] = v7;
  v7[1] = 10;
  v8 = minMaxPar;
  v9 = NewSpecific(s32, 2u);
  v8[3] = v9;
  v9[1] = 10;
  v10 = minMaxPar;
  v11 = NewSpecific(s32, 2u);
  v11[1] = 1;
  v10[4] = v11;
  v12 = minMaxPar;
  v13 = NewSpecific(s32, 2u);
  v12[5] = v13;
  v13[1] = 10;
  v14 = minMaxPar;
  v15 = NewSpecific(s32, 2u);
  v14[6] = v15;
  v15[1] = 1;
  v16 = minMaxPar;
  v17 = NewSpecific(s32, 2u);
  v16[7] = v17;
  v17[1] = 1;
}

// 0x18c5bf0
void Init(void) {
  ConfigCursor *NowCsr;

  NowCsr = GetNowCsr();
  (NowCsr->klass->vtable._5_SetMaxPar.methodPtr)(NowCsr, 8, 7, NowCsr->klass->vtable._5_SetMaxPar.method);
}

// 0x18c5d80
void Update(CONFIG_WORK *wk) {
  ConfigCursor *NowCsr;
  s64 csrNo;
  s32 ConfigData;
  s32 *v10;
  s32 v11;
  s32 v12;
  s32 v14;
  s32 setNo;
  s32 v21;

  NowCsr = GetNowCsr();
  csrNo = NowCsr->csrNo;
  ConfigData = GetConfigData(NowCsr->setNo);
  v10 = minMaxPar[csrNo];
  v11 = v10[0];
  v12 = v10[1];
  if ((u32)csrNo != 3)
  {
    if (wk->changeBgmPlaying)
    {
      RestoreChangeSound(wk);
      wk->changeBgmPlaying = 0;
    }
    if (!(u32)csrNo)
    {
LABEL_27:
      v14 = 1;
      if (CHECK_TRIG(4096, 1))
      {
        ChangeSound(wk, csrNo);
        InitSaveToMessage(0);
      }
      goto LABEL_46;
    }
  }
  if (CsrTopReturn(NowCsr, 0))
    return;
  v14 = 1;
  if ((u32)csrNo <= 7)
  {
    if (((1 << csrNo) & 0x2E) != 0)
    {
      if (CHECK_REP(4103, 0))
      {
        if (ConfigData >= v12)
          goto LABEL_46;
        ++ConfigData;
        setNo = NowCsr->setNo;
        goto LABEL_37;
      }
      else
      {
        if (!CHECK_REP(4102, 0) || ConfigData <= v11)
          goto LABEL_46;
        --ConfigData;
        setNo = NowCsr->setNo;
        goto LABEL_37;
      }
LABEL_37:
      SetConfigData(setNo, ConfigData);
      VolumeChnage(csrNo, wk);
      ChangeSound(wk, csrNo);
      v14 = 0;
      goto LABEL_46;
    }
    if (((1 << csrNo) & 0xD0) != 0)
    {
      if (CHECK_TRIG(4103, 1))
      {
        ChangeSound(wk, csrNo);
        if (ConfigData + 1 <= v12)
          ++ConfigData;
        else
          ConfigData = v11;
      }
      else if (CHECK_TRIG(4102, 1))
      {
        ChangeSound(wk, csrNo);
        if (ConfigData - 1 >= v11)
          --ConfigData;
        else
          ConfigData = v12;
      }
      goto LABEL_46;
    }
    goto LABEL_27;
  }
LABEL_46:
  v21 = NowCsr->setNo;
  SetConfigData(v21, ConfigData);
  if (!v14)
    return;
  VolumeChnage(csrNo, wk);
}

// 0x18c64a0
void ChangeSound(CONFIG_WORK *_wk, AudioSet _set) {
  void *Instance;
  f32 Volume;
  char **v10;
  char *v11;
  void *v12;

  switch (set)
  {
    case 0:
      SE(0);
      return;
    case 3:
      if (wk->changeBgmPlaying)
        return;
      Instance = get_Instance(0);
      wk->prevBgm = GetPlayBGM_ID(Instance, 0);
      sndImmediateBgmStop();
      mapSoundKankyoEnd();
      p2sdSEStopAll();
      Volume = GetVolume(1.0, 3);
      if (GBWK->config_data[0][6])
        v10 = &"e651_001_e";
      else
        v10 = &"e651_001";
      v11 = *v10;
      v12 = get_Instance(0);
      PlayMOVIE(v12, 1000, v11, 1.0, Volume, 0, 20000, 0);
      wk->changeBgmPlaying = 1;
      return;
    case 5:
      if (!sndIsVoicePlayFile("PVA02A_00_000"))
      {
LABEL_9:
        sndVoicePlayFile("PVA02A_00_000", 0);
        return;
      }
      sndVoiceStop(0);
      goto LABEL_9;
  }
  SE(3);
}

// 0x18c62f0
void RestoreChangeSound(CONFIG_WORK *wk) {
  s32 prevBgm;
  s32 v7;

  sndImmediateBgmStop();
  if (IsBattle)
  {
    prevBgm = wk->prevBgm;
    if (prevBgm != -1)
    {
      sndBgmPlay(prevBgm, 0);
    }
    return;
  }
  if (IsCamp)
  {
    v7 = wk->prevBgm;
    cmpRestorBgm(v7);
    return;
  }
  sndBgmPlay(80, 0);
}

// 0x18c6c50
void VolumeChnage(AudioSet set, CONFIG_WORK *_wk) {
  f32 Volume;
  void *Instance;
  f32 v8;
  void *v9;
  f32 v11;
  void *v12;

  if (set == 3)
  {
    if (!wk->changeBgmPlaying)
      goto LABEL_12;
    set = 3;
    goto LABEL_11;
  }
  if (set != 1)
    goto LABEL_12;
  set = 1;
LABEL_11:
  Volume = GetVolume(1.0, set);
  Instance = get_Instance(0);
  PlayAT3BGM_VolumeSet(Instance, Volume, 0);
LABEL_12:
  v8 = GetVolume(1.0, 2);
  v9 = get_Instance(0);
  PlayAT3SE_VolumeSet(v9, v8, 0);
  v11 = GetVolume(1.0, 2);
  v12 = get_Instance(0);
  PlaySE_VolumeSet(v12, v11, 0);
}

// 0x18c70d0
void Draw(void) {
  ConfigCursor *NowCsr;
  s32 setNo;

  NowCsr = GetNowCsr();
  cmpCmpGuideSet(42, 0, 90);
  setNo = NowCsr->setNo;
  MenuHelpDraw(instance, setNo, helpText, 0);
}

// 0x18c6d70
f32 GetVolume(f32 volume_org, AudioSet type) {
  s32 *ConfigTab;
  f32 v8;
  s32 v9;
  f32 v10;
  s32 *v12;

  if (dds3SearchProcessName("config_main"))
    goto LABEL_4;
LABEL_10:
  ConfigTab = 0;
  v8 = 10.0;
  v9 = type - 1;
  v10 = 10.0;
LABEL_11:
  switch (v9)
  {
    case 0:
      if (!ConfigTab)
      {
        ConfigTab = GBWK->config_data[0];
      }
      v12 = &ConfigTab[1];
      goto LABEL_52;
    case 1:
      if (!ConfigTab)
        ConfigTab = GBWK->config_data[0];
      v12 = &ConfigTab[2];
      goto LABEL_52;
    case 2:
      if (!ConfigTab)
        ConfigTab = GBWK->config_data[0];
      v12 = &ConfigTab[3];
      goto LABEL_52;
    case 4:
      if (!ConfigTab)
        ConfigTab = GBWK->config_data[0];
      v12 = &ConfigTab[5];
LABEL_52:
      v10 = *v12;
      return (f32)(v10 / v8) * volume_org;
    default:
      return (f32)(v10 / v8) * volume_org;
  }
  if (!dds3SearchProcessName("config_main"))
    goto LABEL_10;
LABEL_4:
  ConfigTab = GetConfigTab(0);
  v8 = 10.0;
  v9 = type - 1;
  v10 = 10.0;
  if ((u32)(type - 1) <= 4)
    goto LABEL_11;
  return (f32)(v10 / v8) * volume_org;
}
