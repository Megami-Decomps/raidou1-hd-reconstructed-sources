#pragma once
#include "types.h"

typedef struct DitectiveBookUI_MENU_BAR DitectiveBookUI_MENU_BAR;
typedef struct DitectiveBookUI_TextSet DitectiveBookUI_TextSet;

struct DitectiveBookUI_MENU_BAR {
    DitectiveBookUI_TextSet *messageParent;
    DitectiveBookUI_TextSet *messageChild;
    void *scrolltextParent;
    void *scrolltextChild;
};
