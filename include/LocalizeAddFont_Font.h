#pragma once
#include "types.h"

typedef struct LocalizeAddFont_Font LocalizeAddFont_Font;

struct LocalizeAddFont_Font {
    char *label;
    void *fallbackFontAssets;
};
