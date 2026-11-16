#pragma once
#include "types.h"

typedef struct FontReq_t FontReq_t;
typedef struct defkey_tag defkey_tag;
typedef struct sdfIVector2_t sdfIVector2_t;
typedef struct select_tag select_tag;

struct select_tag {
    sdfIVector2_t pos;
    FontReq_t *pfont;
    u32 mask;
    s16 phase;
    s16 select;
    s16 select_imm;
    s16 lines;
    s16 alpha;
    s16 numdef;
    s16 cancelNum;
    defkey_tag *defkey[24];
};
