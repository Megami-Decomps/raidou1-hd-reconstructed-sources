#pragma once
#include "types.h"

s32 evtLoad(s32 eventno);
bool CheckLoad(s32 eventno);
s32 evtPlayBgm(s32 eventno, s32 bgmno);
void evtTransBgm(s32 eventno, s32 bgmno);
s32 evtFadeInBgm(s32 eventno, s32 bgmno);
s32 evtFadeOutBgm(s32 eventno, s32 bgmno);
s32 evtPlaySe(s32 eventno, s32 seno);
s32 evtStopSe(s32 eventno, s32 seno);
