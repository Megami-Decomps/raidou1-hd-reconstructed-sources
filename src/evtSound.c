#include "types.h"
#include "evtsound.h"
#include "sdfsound.h"

#define EVT_SND_MAX 855

static s32 GetMidiNo(s32 eventno, s32 seqno);

// 0x1a36c20
static s32 GetMidiNo(s32 eventno, s32 seqno) {
  s32 v3;
  s32 v4;

  v3 = eventno - 670;
  if ((u32)eventno <= 0x383)
    v3 = eventno - 600;
  if (eventno <= 799)
    v3 = eventno - 601;
  if (eventno == 799)
    v4 = 199;
  else
    v4 = v3;
  return seqno + (v4 << 16) + 0x1000000;
}

// 0x1a36c60
s32 evtLoad(s32 eventno) {
  s32 v3;
  s32 v4;
  s32 v5;

  v3 = eventno - 600;
  if ((u32)(eventno - 600) > 0xFF)
    return 0;
  if ((u32)eventno <= 0x31F)
    v3 = eventno - 601;
  v4 = (v3 << 16) + 0x1000000;
  if (eventno == 799)
    v5 = 29818880;
  else
    v5 = v4;
  p2sdLoadSMGFile(v5);
  return v5;
}

// 0x1a36d10
bool CheckLoad(s32 eventno) {
  s32 v3;
  s32 v4;
  s32 v5;

  v3 = eventno - 600;
  if ((u32)(eventno - 600) > 0xFF)
    return 1;
  if ((u32)eventno <= 0x31F)
    v3 = eventno - 601;
  v4 = (v3 << 16) + 0x1000000;
  if (eventno == 799)
    v5 = 29818880;
  else
    v5 = v4;
  return p2sdLoadCheckMidi(v5) == 1;
}

// 0x1a36dc0
s32 evtPlayBgm(s32 eventno, s32 bgmno) {
  s32 v5;
  s32 v6;
  s32 v7;

  v5 = eventno - 600;
  if ((u32)(eventno - 600) > 0xFF)
    return 0;
  if ((u32)eventno <= 0x31F)
    v5 = eventno - 601;
  v6 = v5 << 16;
  if (eventno == 799)
    v6 = 13041664;
  v7 = bgmno + 0x1000000 + v6;
  p2sdPlayBGM(v7);
  return v7;
}

// 0x1a36e90
void evtTransBgm(s32 eventno, s32 bgmno) {
  s32 v5;
  s32 v6;
  s32 v7;

  v5 = eventno - 600;
  if ((u32)(eventno - 600) > 0xFF)
    return;
  if (bgmno < 0)
  {
    v7 = -1;
LABEL_9:
    p2sdMelodyTrans(v7);
    return;
  }
  else
  {
    if ((u32)eventno <= 0x31F)
      v5 = eventno - 601;
    v6 = v5 << 16;
    if (eventno == 799)
      v6 = 13041664;
    v7 = bgmno + 0x1000000 + v6;
    goto LABEL_9;
  }
  p2sdMelodyTrans(v7);
}

// 0x1a36f70
s32 evtFadeInBgm(s32 eventno, s32 bgmno) {
  s32 v5;
  s32 v6;
  s32 v7;

  v5 = eventno - 600;
  if ((u32)(eventno - 600) > 0xFF)
    return 0;
  if ((u32)eventno <= 0x31F)
    v5 = eventno - 601;
  v6 = v5 << 16;
  if (eventno == 799)
    v6 = 13041664;
  v7 = bgmno + 0x1000000 + v6;
  p2sdFadeIn(v7);
  return v7;
}

// 0x1a37040
s32 evtFadeOutBgm(s32 eventno, s32 bgmno) {
  s32 v5;
  s32 v6;
  s32 v7;

  v5 = eventno - 600;
  if ((u32)(eventno - 600) > 0xFF)
    return 0;
  if ((u32)eventno <= 0x31F)
    v5 = eventno - 601;
  v6 = v5 << 16;
  if (eventno == 799)
    v6 = 13041664;
  v7 = bgmno + 0x1000000 + v6;
  p2sdFadeOut(v7);
  return v7;
}

// 0x1a37110
s32 evtPlaySe(s32 eventno, s32 seno) {
  s32 v3;
  s32 v4;
  s32 v5;

  v3 = eventno - 600;
  if ((u32)(eventno - 600) > 0xFF)
    return 0;
  if ((u32)eventno <= 0x31F)
    v3 = eventno - 601;
  v4 = v3 << 16;
  if (eventno == 799)
    v4 = 13041664;
  v5 = seno + 0x1000000 + v4;
  SE(v5);
  return v5;
}

// 0x1a37180
s32 evtStopSe(s32 eventno, s32 seno) {
  s32 v5;
  s32 v6;
  s32 v7;

  v5 = eventno - 600;
  if ((u32)(eventno - 600) > 0xFF)
    return 0;
  if ((u32)eventno <= 0x31F)
    v5 = eventno - 601;
  v6 = v5 << 16;
  if (eventno == 799)
    v6 = 13041664;
  v7 = seno + 0x1000000 + v6;
  p2sdSndStop(v7);
  return v7;
}
