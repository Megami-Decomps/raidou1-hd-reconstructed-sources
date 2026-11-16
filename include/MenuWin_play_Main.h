#pragma once
#include "types.h"

typedef struct MenuWin_play_Main MenuWin_play_Main;
typedef struct SceneInfo SceneInfo;
typedef struct mjnUI_TextSet mjnUI_TextSet;

struct SceneInfo {
    mjnUI_TextSet *ba;
    mjnUI_TextSet *kyoku;
    mjnUI_TextSet *honba;
};

struct MenuWin_play_Main {
    SceneInfo *sceneinfo;
    mjnUI_TextSet *nokori;
    mjnUI_TextSet *remainingNum;
    mjnUI_TextSet *reachBou;
    mjnUI_TextSet *reach;
};
