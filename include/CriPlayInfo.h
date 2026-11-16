#pragma once
#include "types.h"

typedef struct CriPlayInfo CriPlayInfo;

struct CriPlayInfo {
    void *p;
    void *pbak;
    s32 id;
    s32 type;
    char *name;
    f32 volume;
    bool loop;
};
