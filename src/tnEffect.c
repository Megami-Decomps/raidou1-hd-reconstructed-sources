#include "types.h"
#include "effpolygonflash.h"
#include "effpolygonscaly.h"
#include "effpolygonwind.h"
#include "tneffect.h"

TNEFFECT_FLAG Flag;
void *texture;

// 0x1997a40
void tnInit(void) {
  s32 size;
  s32 v5;

  Init();
  Init();
  Init();
  Flag = 0;
  if (texture)
  {
    size = texture->_size;
    v5 = texture->_version + 1;
    texture->_size = 0;
    texture->_version = v5;
    if (size >= 1)
    {
      Clear(texture->_items, 0, size, 0);
    }
    texture = 0;
  }
}

// 0x1997bf0
void tnFlagSet(TNEFFECT_FLAG flag) {
  Flag |= flag;
}

// 0x1997c50
void tnFlagClear(TNEFFECT_FLAG flag) {
  Flag &= ~flag;
}

// 0x1997ba0
void tnFlagAllClear(void) {
  Flag = 0;
}
