#pragma once
#include "types.h"

typedef struct dds3Effect_RippleBlurParam_t dds3Effect_RippleBlurParam_t;
typedef struct effRippleBlurHandle_t effRippleBlurHandle_t;

effRippleBlurHandle_t *dds3EffectRippleBlurCreate(dds3Effect_RippleBlurParam_t *pParam);
void dds3EffectRippleBlurDelete(effRippleBlurHandle_t *hRippleBlur);
void dds3EffectRippleBlurDraw(effRippleBlurHandle_t *hRippleBlur);
