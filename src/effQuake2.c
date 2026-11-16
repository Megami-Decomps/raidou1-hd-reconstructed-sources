#include "types.h"
#include "__newdds3.h"
#include "effquake2.h"

// 0x1973ee0
bool effSet(s32 frame, s16 power, s32 _in, s32 _out) {
  return SetQuake(frame, power, in, out);
}

// 0x1973c30
void Stop(void) {
  QuakeEnd();
}
