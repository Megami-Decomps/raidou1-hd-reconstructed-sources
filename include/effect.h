#pragma once
#include "types.h"
#include "dds3EffectHandle_t_DrawFunc.h"
#include "dds3billboard.h"
#include "dds3particle.h"

typedef enum {
    BILL_MODE_OPAQUE = 0,
    BILL_MODE_SEMITRANS = 1,
    BILL_MODE_ADDTRANS = 2,
    BILL_MODE_SUBTRANS = 3,
    BILL_MODE_MULTI = 4,
    BILL_MODE_COUNT = 5,
} BILL_MODE;

typedef enum {
    DDS3EFFECT_STATE_END = 0,
    DDS3EFFECT_STATE_RUN = 1,
} DDS3EFFECT_STATE;

typedef enum {
    DDS3EFFPART_TYPE_D3P = 0,
    DDS3EFFPART_TYPE_P2A = 1,
    DDS3EFFPART_TYPE_TMX = 2,
    DDS3EFFPART_TYPE_MODEL = 3,
    DDS3EFFPART_TYPE_PCP = 4,
    DDS3EFFPART_TYPE_P2APOLY = 5,
    DDS3EFFPART_TYPE_MAX = 6,
} DDS3EFFPART_TYPE;

typedef enum {
    DDS3PAR_EFFECT_NO = 0,
    DDS3PAR_EFFECT_BLUR = 1,
    DDS3PAR_EFFECT_TRACK = 2,
    DDS3PAR_EFFECT_TRACK2 = 3,
    DDS3PAR_EFFECT_TRACK3 = 4,
    DDS3PAR_EFFECT_COUNT = 5,
} DDS3PAR_EFFECT;

typedef enum {
    TYPE1 = 1,
    TYPE2 = 2,
    TYPE3 = 3,
} DDS3PARCA_COLOR;

typedef struct BillTable_t BillTable_t;
typedef struct dds3Billboard_Basic_t dds3Billboard_Basic_t;
typedef struct dds3Billboard_Tex_t dds3Billboard_Tex_t;
typedef struct dds3EffectBlendData dds3EffectBlendData;
typedef struct dds3EffectTable_t dds3EffectTable_t;
typedef struct dds3Effect_Blur_t dds3Effect_Blur_t;
typedef struct dds3Effect_DistBlurPart_t dds3Effect_DistBlurPart_t;
typedef struct dds3Effect_DistortionBlurParam_t dds3Effect_DistortionBlurParam_t;
typedef struct dds3Effect_Filter_t dds3Effect_Filter_t;
typedef struct dds3Effect_PartialMultiBlurParam_t dds3Effect_PartialMultiBlurParam_t;
typedef struct dds3Effect_PartialMultiFilterParam_t dds3Effect_PartialMultiFilterParam_t;
typedef struct dds3Effect_RippleBlurParam_t dds3Effect_RippleBlurParam_t;
typedef struct dds3ParticleColorAnim_t dds3ParticleColorAnim_t;
typedef struct dds3Particle_Basic_t dds3Particle_Basic_t;
typedef struct dds3Particle_Blur_t dds3Particle_Blur_t;
typedef struct dds3Particle_Effect_t dds3Particle_Effect_t;
typedef struct dds3Particle_Expansion_t dds3Particle_Expansion_t;
typedef struct dds3Particle_Track2_t dds3Particle_Track2_t;
typedef struct dds3Particle_Track3_t dds3Particle_Track3_t;
typedef struct dds3Particle_Track_t dds3Particle_Track_t;
typedef struct effDistortionBlurHandle_t effDistortionBlurHandle_t;
typedef struct effPartHandle_t effPartHandle_t;
typedef struct physicsHandle_t physicsHandle_t;
typedef struct sdfIVector2_t sdfIVector2_t;

typedef void *(*dds3EffectHandle_t_CreateFunc)(void *param);
typedef void (*dds3EffectHandle_t_DeleteFunc)(void *param);

struct dds3Billboard_Tex_t {
    f32 cx;
    f32 cy;
    f32 width;
    f32 height;
    sdfVector2_t uv0;
    sdfVector2_t uv1;
};

struct BillTable_t {
    DDS3BILLBOARD type;
    BILL_MODE mode;
    f32 magnify;
};

struct dds3Effect_Blur_t {
    sdfVector4_t abgr;
    f32 rotate;
    f32 scale;
    sdfIVector2_t center;
    sdfIVector2_t *xy[2];
    dds3EffectBlendData *_blend;
};

struct dds3Effect_PartialMultiBlurParam_t {
    s32 area;
    dds3Effect_Blur_t *Blur;
};

struct dds3Effect_DistortionBlurParam_t {
    u32 number;
    u32 interval;
    f32 speed;
    sdfVector4_t abgr;
    f32 rotate;
    f32 distortion;
    sdfIVector2_t center;
    s32 area;
    s32 width;
    dds3EffectBlendData *_blend;
};

struct effDistortionBlurHandle_t {
    dds3Effect_DistortionBlurParam_t *param;
    dds3Effect_DistBlurPart_t *pwork;
};

struct dds3Effect_RippleBlurParam_t {
    u32 number;
    f32 speed;
    f32 interval;
    sdfVector4_t abgr;
    f32 rotate;
    f32 power;
    f32 frequency;
    sdfIVector2_t center;
    s32 area;
    dds3EffectBlendData *_blend;
};

struct dds3Effect_Filter_t {
    sdfVector4_t abgr;
    sdfIVector2_t *xy[2];
    void *mesh;
    dds3EffectBlendData *_blend;
};

struct dds3Effect_PartialMultiFilterParam_t {
    s32 area;
    sdfIVector2_t center;
    dds3Effect_Filter_t *Filter;
};

struct dds3EffectTable_t {
    dds3EffectHandle_t_CreateFunc Create;
    dds3EffectHandle_t_DrawFunc Draw;
    dds3EffectHandle_t_DeleteFunc Delete;
};

struct effPartHandle_t {
    DDS3EFFPART_TYPE type;
    void *pHandle;
};

struct dds3Particle_Blur_t {
    u16 length;
};

struct dds3Particle_Track_t {
    u16 length;
    f32 width;
    u32 color;
};

struct dds3Particle_Track2_t {
    u16 length;
    f32 width;
    u32 color_in;
    u32 color_out;
};

struct dds3Particle_Track3_t {
    u16 length;
    f32 width;
    u32 color_s;
    u32 color_e;
};

struct dds3Particle_Effect_t {
    DDS3PAR_EFFECT type;
    void *param;
};

struct dds3ParticleColorAnim_t {
    DDS3PARCA_COLOR type;
    u32 _color[3];
    u32 _alpha;
    s32 alpha_s;
    s32 alpha_e;
    sdfVector4_t *color;
    f32 alpha;
    sdfVector4_t *add;
    s32 frame_end;
    s32 frame_h;
    f32 alpha_s_add;
    f32 alpha_e_sub;
};

struct dds3Particle_Expansion_t {
    f32 scl;
    f32 rot_s;
    f32 scl_r;
    f32 rot_r;
    bool rot_rev;
};

struct dds3Particle_Basic_t {
    sdfVector4_t pos;
    sdfVector4_t scale;
    u32 number;
    s32 frame;
    u32 billno;
    BILL_MODE billmode;
    dds3Particle_Effect_t *effect;
    dds3ParticleColorAnim_t *color;
    dds3Particle_Expansion_t *exp;
    u32 d_frame;
    sdfMatrix4_t rot;
    sdfVector4_t abgr;
    dds3Billboard_Basic_t *hBillboard;
    physicsHandle_t *hPhysics;
    u32 empty_loop;
    sdfMatrix4_t rot_b;
    DDS3PARTICLE type;
    DDS3EFFECT_STATE state;
    void *func;
    bool loop;
};
