#pragma once
#include "types.h"

typedef struct CharaCard CharaCard;

struct CharaCard {
    void *name;
    void *lv;
    void *lvNum;
    void *money;
};
