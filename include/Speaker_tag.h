#pragma once
#include "types.h"

typedef struct FontReq_t FontReq_t;
typedef struct Speaker_tag Speaker_tag;
typedef struct sdfIVector2_t sdfIVector2_t;

struct Speaker_tag {
    sdfIVector2_t pos;
    FontReq_t *pfont;
    u16 num;
    s16 reserved;
};
