#pragma once
#include "types.h"

typedef struct dds3Effect_RipBlurPart_t dds3Effect_RipBlurPart_t;
typedef struct dds3Effect_RippleBlurParam_t dds3Effect_RippleBlurParam_t;
typedef struct effRippleBlurHandle_t effRippleBlurHandle_t;

struct effRippleBlurHandle_t {
    dds3Effect_RippleBlurParam_t *param;
    dds3Effect_RipBlurPart_t *pwork;
};
