#pragma once
#include "types.h"

typedef struct DitectiveBookUI_PANELTITLE DitectiveBookUI_PANELTITLE;
typedef struct DitectiveBookUI_TextSet DitectiveBookUI_TextSet;

struct DitectiveBookUI_PANELTITLE {
    DitectiveBookUI_TextSet *text;
    void *stxt;
};
