#pragma once
#include "types.h"

typedef struct dds3Effect_Blur_t dds3Effect_Blur_t;
typedef struct dds3Effect_RipBlurPart_t dds3Effect_RipBlurPart_t;

struct dds3Effect_RipBlurPart_t {
    f32 scale;
    f32 radiun;
    dds3Effect_Blur_t *Blur;
};
