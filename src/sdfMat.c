#include "types.h"
#include "sdfmat.h"

s32 ID_algorithm;
s32 ID_texture;
s32 ID_ambient;
s32 ID_diffuse;
s32 ID_specular;
s32 ID_spSpecular;
s32 ID_refmap;
s32 ID_constant;
s32 ID_mtexAlgorithm;
s32 ID_multiTexture;
s32 ID_mtexDiffuse;
s32 ID_alphaCutout;
s32 ID_singleSide;
s32 ID_ditherAlpha;
s32 ID_texTm;
s32 ID_texTm2;
s32 ID_mtexTm;
s32 ID_mtexTm2;
s32 ID_pLightPos;
s32 ID_pLightColor;
s32 ID_OBJECT_COLOR;
s32 ID_LIGHT_NORMAL_0;
s32 ID_LIGHT_NORMAL_1;
s32 ID_LIGHT_NORMAL_2;
s32 ID_LIGHT_COLOR_0;
s32 ID_LIGHT_COLOR_1;
s32 ID_LIGHT_COLOR_2;
s32 ID_AMBIENT_COLOR;
s32 ID_AMBIENT2_COLOR;
s32 ID_mask;
s32 ID_maskTm;
s32 ID_maskTm2;
s32 ID_Cull;
s32 ID_ZWrite;
s32 ID_ZTest;
s32 ID_BlendSrc;
s32 ID_BlendDst;
s32 ID_BlendOp;
s32 ID_Mul;
s32 ID_Add;
s32 ID_Sub;

// 0x225e8e0
void sdfMatSetUvwParm(const sdfVector4_t *offsetTile, f32 angle, sdfVector4_t *rotate, sdfVector2_t *offset) {
  f32 x;
  f32 w;
  f32 z;
  f32 y;
  f32 v11;
  s64 v12;
  s64 v13;
  s64 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;

  x = offsetTile->x;
  w = offsetTile->w;
  z = offsetTile->z;
  y = offsetTile->y;
  v11 = sub_188E3D0(angle);
  v15 = sub_188E3C0(v12, v13, v14);
  v16 = z * v15;
  v17 = -(f32)(v11 * w);
  v18 = w * v15;
  rotate->x = v16;
  rotate->y = v17;
  rotate->z = z * v11;
  rotate->w = v18;
  offset->x = (f32)(0.5 - (f32)((f32)(x + 0.5) * v16)) - (f32)((f32)(y + 0.5) * (f32)(z * v11));
  offset->y = (f32)(0.5 - (f32)((f32)(x + 0.5) * v17)) - (f32)((f32)(y + 0.5) * v18);
}

// 0x225e990
bool sdfMatIsParticle(void *renderer) {
  void *gameObject;
  Il2CppObject *Component_object;

  if (renderer && (UnityEngine_ParticleSystemRenderer_c *)renderer->klass == UnityEngine_ParticleSystemRenderer)
  {
    return 1;
  }
  gameObject = get_gameObject(renderer, 0);
  Component_object = GetComponent_object_(gameObject);
  return op_Inequality(Component_object, 0, 0);
}
