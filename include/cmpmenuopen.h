#pragma once
#include "types.h"
#include "CMP_MENU_ID.h"

typedef enum {
    CMP_MENU_OPEN_NONE = -1,
    CMP_MENU_OPEN_SKILL = 0,
    CMP_MENU_OPEN_USE = 1,
    CMP_MENU_OPEN_ORGANIZE = 2,
    CMP_MENU_OPEN_RAIDOU_SKL = 3,
    CMP_MENU_OPEN_SWORD = 4,
    CMP_MENU_OPEN_DVL_REPORT = 5,
    CMP_MENU_OPEN_MAX = 6,
} CMP_MENU_OPEN;

void CmpClear(void);
void CmpOnMenu(CMP_MENU_ID _menu);
bool CmpCheckMenuOpen(CMP_MENU_ID _menu);
CMP_MENU_OPEN MenuIDtoOpenID(CMP_MENU_ID _menuID);
