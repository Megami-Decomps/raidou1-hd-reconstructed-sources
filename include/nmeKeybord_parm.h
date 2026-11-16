#pragma once
#include "types.h"

typedef struct nmeKeybord_parm nmeKeybord_parm;

struct nmeKeybord_parm {
    s32 mojiNum;
    s32 mojiLang;
    char *endMojiSave[2];
    bool mojiFlag;
    void *kbObj;
    char *endWishSave;
};
