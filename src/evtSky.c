#include "types.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "evtsky.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

bool skyanime;
static u16 skyanow;
static u16 skyamax;
static s16 skyabase;
static s16 skyatarget;
bool fldbokasi;

static void UpdateAlpha(void);
static dds3ProcessFunc_t Process1(dds3ProcessID_t *id);
static void Shutdown(dds3ProcessID_t *id);

// 0x19e60a0
void evtSetBokasi(bool sw) {
  fldbokasi = sw;
}

// 0x19e6100
void evtSetAlpha(s32 frame, s32 a) {
  if (gFilterFilterAlpOfs == a)
    return;
  if (frame)
  {
    skyabase = gFilterFilterAlpOfs;
    skyanow = 0;
    skyamax = frame;
    skyatarget = a;
    skyanime = 1;
    return;
  }
  gFilterFilterAlpOfs = a;
  skyanime = 0;
  return;
}

// 0x19e62b0
bool evtCheckAlphaAnime(void) {
  return skyanime;
}

// 0x19e6300
static void UpdateAlpha(void) {
  u32 v1;
  s32 v6;
  f32 v7;
  f32 v8;
  s32 v9;
  s32 v11;

  if (skyanime)
  {
    LOWORD(v1) = skyamax;
    v6 = ++skyanow;
    v7 = (f32)v6 / (f32)v1;
    v8 = v7 * (f32)(skyatarget - skyabase);
    if (v8 == INFINITY)
      v9 = 0x80000000;
    else
      v9 = v8;
    v11 = v9 + skyabase;
    gFilterFilterAlpOfs = v11;
    if (skyanow >= (u32)skyamax)
      skyanime = 0;
  }
}

// 0x19e6450
static dds3ProcessFunc_t Process1(dds3ProcessID_t *id) {
  UpdateAlpha();
  return 0;
}

// 0x19e6490
static void Shutdown(dds3ProcessID_t *id) {
  skyanime = 0;
  fldbokasi = 0;
  dds3FilterSet(0, 1, 0);
}

// 0x19e6520
void Exit(void) {
  dds3ProcessID_t *id;

  id = dds3SearchProcessName("sky");
  if (!id)
    return;
  dds3KillProcess(id, 1);
}

// 0x19e6600
dds3ProcessID_t *evtInit(void) {
  dds3ProcessFunc_t v3;
  shutdownfuncDelegate v4;

  dds3FilterSetAnime(0);
  gFilterAlpha = 128;
  gFilterFilterAlpOfs = 0;
  dds3FilterSet(0, 1, 0);
  v3 = Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_evtSky_Process1__, 0);
  v4 = Allocate(shutdownfuncDelegate);
  _ctor(v4, 0, Method_Project_evtSky_Shutdown__, 0);
  return dds3StartProcess("sky", 11020, 1, 1, v3, v4, 0);
}
