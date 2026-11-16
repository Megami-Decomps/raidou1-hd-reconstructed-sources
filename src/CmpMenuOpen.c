#include "types.h"
#include "CMP_MENU_ID.h"
#include "cmpmenuopen.h"
#include "dat.h"

#define BITS_SIZE 2

// 0x2191c80
void CmpClear(void) {
  dds3GlobalWork_t *GBWK_local;
  u8 *v3;

  GBWK_local = GBWK;
  v3 = NewSpecific(byte, 2u);
  GBWK_local->cmpMenuOpenBits = v3;
}

// 0x2191d10
void CmpOnMenu(CMP_MENU_ID _menu) {
  char v3;
  s32 v4;
  u8 *cmpMenuOpenBits;

  if (menu <= 61441)
  {
    switch (menu)
    {
      case 128:
        v3 = 3;
        break;
      case 256:
        v3 = 5;
        break;
      case 61441:
        v3 = 0;
        break;
      default:
        return;
    }
  }
  else
  {
    switch (menu)
    {
      case 61442:
        v3 = 1;
        break;
      case 262146:
        v3 = 4;
        break;
      case 458753:
        v3 = 2;
        break;
      default:
        return;
    }
  }
  v4 = 1 << v3;
  cmpMenuOpenBits = GBWK->cmpMenuOpenBits;
  cmpMenuOpenBits[0] |= v4;
}

// 0x2191e90
bool CmpCheckMenuOpen(CMP_MENU_ID _menu) {
  bool result;
  s32 v4;

  if (menu <= 61441)
  {
    switch (menu)
    {
      case 128:
        result = 3;
        break;
      case 256:
        result = 5;
        break;
      case 61441:
        result = 0;
        break;
      default:
        return 1;
    }
  }
  else
  {
    result = 1;
    if (menu != 61442)
    {
      if (menu == 262146)
      {
        result = 4;
      }
      else
      {
        if (menu != 458753)
          return result;
        result = 2;
      }
    }
  }
  v4 = 1 << result;
  return (u8)(v4 & GBWK->cmpMenuOpenBits[0]) != 0;
}

// 0x2191e10
CMP_MENU_OPEN MenuIDtoOpenID(CMP_MENU_ID _menuID) {
  s32 v2;
  s32 v3;

  if (menuID <= 61441)
  {
    switch (menuID)
    {
      case 128:
        return 3;
      case 256:
        return 5;
      case 61441:
        return 0;
      default:
        return -1;
    }
  }
  else
  {
    if (menuID == 458753)
      v2 = 2;
    else
      v2 = -1;
    if (menuID == 262146)
      v3 = 4;
    else
      v3 = v2;
    if (menuID == 61442)
      return 1;
    else
      return v3;
  }
}
