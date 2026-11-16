#pragma once
#include "types.h"
#include "DitectiveBookUI_Mode.h"

typedef struct TextSet TextSet;

struct TextSet {
    void *TMProUGUI;
    DitectiveBookUI_Mode mode;
    void *scrolltext;
};
