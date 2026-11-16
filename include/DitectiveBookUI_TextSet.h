#pragma once
#include "types.h"
#include "DitectiveBookUI_Mode.h"

typedef struct DitectiveBookUI_ScrollText DitectiveBookUI_ScrollText;
typedef struct DitectiveBookUI_TextSet DitectiveBookUI_TextSet;

struct DitectiveBookUI_TextSet {
    void *TMProUGUI;
    DitectiveBookUI_Mode mode;
    DitectiveBookUI_ScrollText *scrolltext;
};
