#include "types.h"
#include "dds3vrf.h"
#include "sdfvsync.h"

static bool VRF_Disable;
bool VRF_Active;
f32 VRF_DeltaTime;
f32 FPS60;
f32 VRF;

// 0x22956f0
void dds3InitVRF(void) {
  VRF = 0.0;
  *(u64 *)&VRF_DeltaTime = 0x3C88888900000000LL;
  VRF_Active = 0;
}

// 0x2296fe0
void dds3BeginVRF(void) {
  f32 deltaTime;

  if (firstFrame)
    goto LABEL_6;
  return;
  if (firstFrame)
  {
LABEL_6:
    if (!drawSkipMode)
    {
      if (VRF_Disable)
      {
        deltaTime = get_deltaTime(0);
        VRF_DeltaTime = deltaTime;
        VRF = 1.0;
        goto LABEL_23;
      }
      if (VRF_Active)
      {
        deltaTime = get_deltaTime(0);
        VRF_DeltaTime = deltaTime;
        VRF = deltaTime / FPS60;
        goto LABEL_23;
      }
    }
    deltaTime = FPS60;
    VRF_DeltaTime = deltaTime;
    VRF = 1.0;
LABEL_23:
    sdfSetFrameTime(deltaTime);
    return;
  }
}

// 0x22a3130
void VRF_SetActive(bool _act) {
  VRF_Active = !VRF_Disable
                                                            && act;
}
