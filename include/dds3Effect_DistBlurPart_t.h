#pragma once
#include "types.h"

typedef struct dds3Effect_Blur_t dds3Effect_Blur_t;
typedef struct dds3Effect_DistBlurPart_t dds3Effect_DistBlurPart_t;

struct dds3Effect_DistBlurPart_t {
    u32 wait;
    f32 radiun;
    dds3Effect_Blur_t *Blur;
};
