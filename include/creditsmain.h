#pragma once
#include "types.h"

typedef struct Credits_t Credits_t;

struct Credits_t {
    char *caption1;
    char *caption2;
    char *name1;
    char *name2;
    s32 dispControlFlg;
};

extern Credits_t *CreditsData;
extern bool is_end;

s32 GetCreditsTableMax(void);
bool IsEndCredits(void);
