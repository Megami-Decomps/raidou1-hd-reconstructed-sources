#pragma once
#include "types.h"

typedef struct SBTLSOUND_FOOTWORK SBTLSOUND_FOOTWORK;

struct SBTLSOUND_FOOTWORK {
    f32 prevFrame;
    s32 prevSMGID;
    s32 played;
    s32 dummmy0;
};
