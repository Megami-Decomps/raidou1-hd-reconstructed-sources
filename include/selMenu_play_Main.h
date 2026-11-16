#pragma once
#include "types.h"

typedef struct mjnUI_TextSet mjnUI_TextSet;
typedef struct selMenu_play_Main selMenu_play_Main;
typedef struct selMenu_play_bar selMenu_play_bar;

struct selMenu_play_bar {
    mjnUI_TextSet *situation;
};

struct selMenu_play_Main {
    selMenu_play_bar *musi;
    void *situationText;
};
