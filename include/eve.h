#pragma once
#include "types.h"

typedef struct CtrlBlur CtrlBlur;
typedef struct CtrlDistortionBlur CtrlDistortionBlur;
typedef struct CtrlFilter CtrlFilter;
typedef struct CtrlParallelBlur CtrlParallelBlur;
typedef struct CtrlPartialMultiBlur CtrlPartialMultiBlur;
typedef struct CtrlPartialMultiFilter CtrlPartialMultiFilter;
typedef struct CtrlRippleBlur CtrlRippleBlur;
typedef struct dds3Effect_Blur_t dds3Effect_Blur_t;
typedef struct dds3Effect_Filter_t dds3Effect_Filter_t;
typedef struct dds3Effect_ParallelBlur_t dds3Effect_ParallelBlur_t;
typedef struct effDistortionBlurHandle_t effDistortionBlurHandle_t;
typedef struct effPartialMultiBlurHandle_t effPartialMultiBlurHandle_t;
typedef struct effPartialMultiFilterHandle_t effPartialMultiFilterHandle_t;
typedef struct effRippleBlurHandle_t effRippleBlurHandle_t;

struct CtrlBlur {
    s32 defTex;
    bool Show;
    dds3Effect_Blur_t *param;
};

struct CtrlPartialMultiBlur {
    s32 defTex;
    bool Show;
    void *param;
    effPartialMultiBlurHandle_t *handle;
};

struct CtrlDistortionBlur {
    s32 defTex;
    bool Show;
    void *param;
    effDistortionBlurHandle_t *handle;
};

struct CtrlRippleBlur {
    s32 defTex;
    bool Show;
    void *param;
    effRippleBlurHandle_t *handle;
};

struct CtrlParallelBlur {
    s32 defTex;
    bool Show;
    dds3Effect_ParallelBlur_t *param;
};

struct CtrlFilter {
    s32 defTex;
    bool Show;
    dds3Effect_Filter_t *param;
};

struct CtrlPartialMultiFilter {
    s32 defTex;
    bool Show;
    void *param;
    effPartialMultiFilterHandle_t *handle;
};

extern CtrlBlur *Blur;
extern CtrlPartialMultiBlur *PartialMultiBlur;
extern CtrlDistortionBlur *DistortionBlur;
extern CtrlRippleBlur *RippleBlur;
extern CtrlParallelBlur *ParallelBlur;
extern CtrlFilter *Filter;
extern CtrlPartialMultiFilter *PartialMultiFilter;
extern dds3Effect_Blur_t *effEvent_Edit_Blur;

void EffectInit(void);
void EffectDraw(void);
dds3Effect_Blur_t *BlurEditorGetParams(void);
void BlurSetParam2(dds3Effect_Blur_t *pParam);
