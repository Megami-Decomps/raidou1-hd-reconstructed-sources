#pragma once
#include "types.h"

typedef enum {
    AudioSet_Decision = 0,
    AudioSet_Bgm = 1,
    AudioSet_Se = 2,
    AudioSet_Movie = 3,
    AudioSet_VoiceOnOff = 4,
    AudioSet_Voice = 5,
    AudioSet_Language = 6,
    AudioSet_AutoFeed = 7,
    AudioSet_Max = 8,
} AudioSet;

typedef struct CONFIG_WORK CONFIG_WORK;

extern char *menuText;
extern char *helpText;
extern char *selectText;
extern s32 **minMaxPar;

char *GetSelectText(s32 _setPar, s32 _value);
void InitSelectCnt(void);
void Init(void);
void Update(CONFIG_WORK *wk);
void ChangeSound(CONFIG_WORK *_wk, AudioSet _set);
void RestoreChangeSound(CONFIG_WORK *wk);
void VolumeChnage(AudioSet set, CONFIG_WORK *_wk);
void Draw(void);
f32 GetVolume(f32 volume_org, AudioSet type);
