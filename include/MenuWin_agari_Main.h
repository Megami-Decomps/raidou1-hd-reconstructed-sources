#pragma once
#include "types.h"

typedef struct BarTextSet BarTextSet;
typedef struct HuHanBarTextSet HuHanBarTextSet;
typedef struct MenuWin_agari_Main MenuWin_agari_Main;
typedef struct SPRITEICONCLASS SPRITEICONCLASS;
typedef struct mjnUI_ScrollBar mjnUI_ScrollBar;
typedef struct mjnUI_TextSet mjnUI_TextSet;

struct HuHanBarTextSet {
    mjnUI_TextSet *text_hu;
    mjnUI_TextSet *text_han;
};

struct MenuWin_agari_Main {
    BarTextSet *agari;
    SPRITEICONCLASS *icon_agari;
    BarTextSet *ryukyoku;
    BarTextSet *Houju;
    SPRITEICONCLASS *icon_houju;
    HuHanBarTextSet *huhan;
    BarTextSet *topyaku;
    BarTextSet *huriten;
    void *yakuList;
    mjnUI_ScrollBar *scroll;
};
