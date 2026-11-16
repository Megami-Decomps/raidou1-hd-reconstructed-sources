#pragma once
#include "types.h"

extern s32 ID_algorithm;
extern s32 ID_texture;
extern s32 ID_ambient;
extern s32 ID_diffuse;
extern s32 ID_specular;
extern s32 ID_spSpecular;
extern s32 ID_refmap;
extern s32 ID_constant;
extern s32 ID_mtexAlgorithm;
extern s32 ID_multiTexture;
extern s32 ID_mtexDiffuse;
extern s32 ID_alphaCutout;
extern s32 ID_singleSide;
extern s32 ID_ditherAlpha;
extern s32 ID_texTm;
extern s32 ID_texTm2;
extern s32 ID_mtexTm;
extern s32 ID_mtexTm2;
extern s32 ID_pLightPos;
extern s32 ID_pLightColor;
extern s32 ID_OBJECT_COLOR;
extern s32 ID_LIGHT_NORMAL_0;
extern s32 ID_LIGHT_NORMAL_1;
extern s32 ID_LIGHT_NORMAL_2;
extern s32 ID_LIGHT_COLOR_0;
extern s32 ID_LIGHT_COLOR_1;
extern s32 ID_LIGHT_COLOR_2;
extern s32 ID_AMBIENT_COLOR;
extern s32 ID_AMBIENT2_COLOR;
extern s32 ID_mask;
extern s32 ID_maskTm;
extern s32 ID_maskTm2;
extern s32 ID_Cull;
extern s32 ID_ZWrite;
extern s32 ID_ZTest;
extern s32 ID_BlendSrc;
extern s32 ID_BlendDst;
extern s32 ID_BlendOp;
extern s32 ID_Mul;
extern s32 ID_Add;
extern s32 ID_Sub;

void sdfMatSetUvwParm(const sdfVector4_t *offsetTile, f32 angle, sdfVector4_t *rotate, sdfVector2_t *offset);
bool sdfMatIsParticle(void *renderer);
