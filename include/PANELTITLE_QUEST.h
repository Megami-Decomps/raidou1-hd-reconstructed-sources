#pragma once
#include "types.h"

typedef struct DitectiveBookUI_TextSet DitectiveBookUI_TextSet;
typedef struct PANELTITLE_QUEST PANELTITLE_QUEST;

struct PANELTITLE_QUEST {
    DitectiveBookUI_TextSet *text;
    void *stxt;
    DitectiveBookUI_TextSet *num_text;
};
