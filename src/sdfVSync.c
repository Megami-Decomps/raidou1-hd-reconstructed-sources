#include "types.h"
#include "sdfvsync.h"

#define maxCount 3
#define modFrameTime 0.008333334
#define skipFrameTime 0.025000002

u32 Count;
f32 frameTime;
f32 timeScale;
static f32 totalFrameTime;
bool drawSkip;
bool firstFrame;
f32 _ElapsedTime_k__BackingField;
static s32 skipCount;
bool drawSkipMode;
static bool _drawSkipMode;
bool isUpdate;

// 0x2282560
void sdfBegin(void) {
  bool drawSkipMode_local;
  f32 unscaledDeltaTime;

  drawSkipMode_local = _drawSkipMode;
  firstFrame = 1;
  drawSkipMode = drawSkipMode_local;
  unscaledDeltaTime = get_unscaledDeltaTime(0);
  _ElapsedTime_k__BackingField = unscaledDeltaTime;
}

// 0x2282630
void sdfStep(void) {
  firstFrame = 0;
  return;
}

// 0x22826b0
bool sdfIsUpdate(void) {
  return isUpdate;
}

// 0x2282730
void sdfSetFrameTime(f32 time) {
  frameTime = time;
  if (drawSkipMode)
    return;
  totalFrameTime = time;
}

// 0x2282800
void *sdfThread(void) {
  void *v1;

  v1 = Allocate(Project_libsdf_sdfVSync__Thread_d__34);
  v1->__1__state = 0;
  return v1;
}
