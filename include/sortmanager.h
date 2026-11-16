#pragma once
#include "types.h"

typedef enum {
    SORT_GUIDE_MENU = 0,
    SORT_GUIDE_MENU_CHG = 1,
} SORT_GUIDE;

extern void *sortText;
extern void *sortHelpText;
extern void *sortGuide;
extern void *reversePermit;

void SortGuideSet(SORT_GUIDE _id, bool _timer, s32 _waitTimer);
