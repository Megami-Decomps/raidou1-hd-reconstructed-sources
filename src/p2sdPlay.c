#include "types.h"
#include "p2sdplay.h"
#include "sdfsound.h"

// macros
// 0x22487d0: void SE(s32 _SENo)
#define SE(_SENo) do { \
    s32 v2; \
    s32 v6; \
    v6 = SENo; \
    p2sdPlaySeEx(v6, 127, v2); \
} while (0)

// 0x2248a40
void p2sdPlaySE_Pan(s32 _SENo, PS2DPAN _pan) {
  s32 v6;

  v6 = SENo;
  p2sdPlaySeEx(v6, 127, (s32)method);
}

// 0x2248ad0
void p2sdPlaySE_Vol(s32 _SENo, s32 _vol) {
  s32 v7;
  s32 v8;

  v7 = SENo;
  v8 = vol;
  p2sdPlaySeEx(v7, v8, (s32)method);
}

// 0x2248b60
void p2sdPlaySE_Vol_Loop(s32 _SENo, s32 _vol, bool _loop) {
  p2sdPlaySeExLoop(SENo, vol, loop, loop);
}

// 0x2248dc0
bool p2sdPlayIs_Play_SE(s32 _SENo) {
  void *Instance;
  s32 maxSE;
  void *v7;
  s64 v8;
  CriPlayInfo *v9;

  Instance = get_Instance(sdfSound);
  maxSE = Instance->maxSE;
  if (maxSE < 1)
    return 0;
  v7 = Instance;
  v8 = 0;
  while (1)
  {
    v9 = v7->playerSE[v8];
    if (v9->id == SENo)
      break;
LABEL_8:
    if (++v8 >= maxSE)
      return 0;
  }
  if (GetStatus(v9->p, 0) != 2)
  {
    maxSE = v7->maxSE;
    goto LABEL_8;
  }
  return 1;
}

// 0x2248f60
void p2sdPlaySE_VolAngle(s32 _SENo, s32 _vol, f32 _Angle) {
  p2sdPlaySeEx_VolAngle(SENo, vol, Angle);
}

// 0x22491c0
void p2sdPlaySe3D(s32 _SENo, f32 _posx, f32 _posy, f32 _posz) {

}
