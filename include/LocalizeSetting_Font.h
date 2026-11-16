#pragma once
#include "types.h"

typedef struct LocalizeSetting_Font LocalizeSetting_Font;

struct LocalizeSetting_Font {
    char *label;
    void *fontAsset;
    void *fallbackFontAssets;
};
