#include "types.h"
#include "dds3kernelcore.h"
#include "effblur_filter.h"
#include "effquake.h"
#include "effstat.h"
#include "kernel.h"

#define EFFSTAT_PROCNAME "eff_stat"
#define EFFSTAT_BLURFADEFRAME_OUT 8
#define EFFSTAT_BLURFADEFRAME_IN 0
#define EFF_BLURCTRL_FLAG_FADEOUT 1
#define EFF_BLURCTRL_FLAG_FADEIN 2

typedef struct dds3ProcessID_t dds3ProcessID_t;

static EFFSTAT_FLAG flags_stat;
static dds3ProcessID_t *proc_stat;
static u32 flags_blur;
static f32 vel_blur;

static dds3ProcessFunc_t Process(dds3ProcessID_t *proc);
static void effFadeOutBlur(f32 frame);
static void effFadeInBlur(f32 frame);
static void effUpdateBlur(void);

// 0x19618d0
EFFSTAT_FLAG effGetFlags(void) {
  return flags_stat;
}

// 0x1961920
void effStartEffectStop(void) {
  s32 v3;

  effStopStat();
  if ((flags_stat & 4) != 0)
    v3 = 2;
  else
    v3 = 3;
  flags_stat |= v3;
  flags_blur = flags_blur & 0xFFFFFFFC | 1;
  vel_blur = -0.125;
}

// 0x1961aa0
void effStopEffectStop(void) {
  flags_stat &= 0xFFFFFFFC;
  effRestoreStat();
  flags_blur &= ~1u;
  LODWORD(EFF_BLURVAL) = (struct effBlur_Filter)1065353216;
}

// 0x1961c80
void effStartEffectStop_SUMMON_FR(void) {
  s32 v3;

  effStopStat();
  if ((flags_stat & 4) != 0)
    v3 = 2;
  else
    v3 = 3;
  flags_stat |= v3;
}

// 0x1961d10
void effStopEffectStop_SUMMON_FR(void) {
  flags_stat &= 0xFFFFFFFC;
}

// 0x1961d70
void Init(void) {
  dds3ProcessFunc_t v2;
  dds3ProcessID_t *started;

  flags_stat = 0;
  effInit();
  v2 = Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_effStat_Process__, 0);
  started = dds3StartProcess("eff_stat", 11010, 0, 0, v2, 0, 0);
  proc_stat = started;
}

// 0x1961eb0
static dds3ProcessFunc_t Process(dds3ProcessID_t *proc) {
  effUpdateBlur();
  effUpdate();
  return 0;
}

// 0x19619e0
static void effFadeOutBlur(f32 frame) {
  u32 v4;

  v4 = flags_blur & 0xFFFFFFFD;
  flags_blur = v4;
  if (frame == 0.0)
  {
    LODWORD(EFF_BLURVAL) = 0;
  }
  else
  {
    flags_blur = v4 | 1;
    vel_blur = -1.0 / frame;
  }
}

// 0x1961bb0
static void effFadeInBlur(f32 frame) {
  u32 v4;

  v4 = flags_blur & 0xFFFFFFFE;
  flags_blur = v4;
  if (frame == 0.0)
  {
    LODWORD(EFF_BLURVAL) = (struct effBlur_Filter)1065353216;
  }
  else
  {
    flags_blur = v4 | 2;
    vel_blur = 1.0 / frame;
  }
}

// 0x1961f30
static void effUpdateBlur(void) {
  f32 v4;
  f32 v5;
  s32 v6;

  if (flags_blur)
  {
    v4 = EFF_BLURVAL + vel_blur;
    if ((flags_blur & 2) != 0)
    {
      v5 = 1.0;
      if (v4 >= 1.0)
      {
        v6 = -3;
        goto LABEL_11;
      }
    }
    else if (v4 <= 0.0)
    {
      v5 = 0.0;
      v6 = -2;
LABEL_11:
      v4 = v5;
      flags_blur = flags_blur & v6;
    }
    EFF_BLURVAL = v4;
  }
}
