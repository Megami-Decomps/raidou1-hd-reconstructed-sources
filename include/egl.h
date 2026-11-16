#pragma once
#include "types.h"
#include "kernel.h"

typedef struct SDF_GS_TEST SDF_GS_TEST;
typedef struct sdfGrOt_t sdfGrOt_t;

extern s32 OT_Offset;
extern sdfGrOt_t *currentOt;

void eglInit(void);
void eglSetOt(DDS3_OT ot);
void eglLinkTest(SDF_GS_TEST *test);
void eglLinkAlpha(s32 mode);
void eglLinkSpriteF(f32 x, f32 y, f32 w, f32 h, s32 u, s32 v, s32 uw, s32 vh, const sdfColor32_t *rgba0, const sdfColor32_t *rgba1, const sdfColor32_t *rgba2, const sdfColor32_t *rgba3, void *th);
void LinkSpriteF(f32 x, f32 y, f32 w, f32 h, s32 u, s32 v, s32 uw, s32 vh, const sdfVector4_t *rgba0, const sdfVector4_t *rgba1, const sdfVector4_t *rgba2, const sdfVector4_t *rgba3, void *th);
void LinkSpriteF_2(f32 x, f32 y, f32 w, f32 h, s32 u, s32 v, s32 uw, s32 vh, u32 rgba0, u32 rgba1, u32 rgba2, u32 rgba3, void *th);
void eglLinkSprite4F(f32 x0, f32 y0, f32 x1, f32 y1, f32 x2, f32 y2, f32 x3, f32 y3, s32 u, s32 v, s32 uw, s32 vh, const sdfColor32_t *rgba0, const sdfColor32_t *rgba1, const sdfColor32_t *rgba2, const sdfColor32_t *rgba3, void *th);
void LinkSprite4F(f32 x0, f32 y0, f32 x1, f32 y1, f32 x2, f32 y2, f32 x3, f32 y3, s32 u, s32 v, s32 uw, s32 vh, const sdfVector4_t *rgba0, const sdfVector4_t *rgba1, const sdfVector4_t *rgba2, const sdfVector4_t *rgba3, void *th);
void LinkSprite4F_2(f32 x0, f32 y0, f32 x1, f32 y1, f32 x2, f32 y2, f32 x3, f32 y3, s32 u, s32 v, s32 uw, s32 vh, u32 rgba0, u32 rgba1, u32 rgba2, u32 rgba3, void *th);
void eglLinkBoxZ(s32 x, s32 y, s32 w, s32 h, s32 z, const sdfColor32_t *rgba0, const sdfColor32_t *rgba1, const sdfColor32_t *rgba2, const sdfColor32_t *rgba3);
void eglLinkBox(s32 x, s32 y, s32 w, s32 h, const sdfColor32_t *rgba0, const sdfColor32_t *rgba1, const sdfColor32_t *rgba2, const sdfColor32_t *rgba3);
void LinkBox(s32 x, s32 y, s32 w, s32 h, const sdfVector4_t *rgba0, const sdfVector4_t *rgba1, const sdfVector4_t *rgba2, const sdfVector4_t *rgba3);
void eglLinkTri(s32 x0, s32 y0, s32 x1, s32 y1, s32 x2, s32 y2, const sdfColor32_t *rgba0, const sdfColor32_t *rgba1, const sdfColor32_t *rgba2);
void LinkTri(s32 x0, s32 y0, s32 x1, s32 y1, s32 x2, s32 y2, const sdfVector4_t *rgba0, const sdfVector4_t *rgba1, const sdfVector4_t *rgba2);
void eglLinkMaru2D(s32 cx, s32 cy, s32 fr, const sdfColor32_t *in_rgba, const sdfColor32_t *out_rgba);
void eglLinkPoly4(const sdfVector3_t *pos0, const sdfVector3_t *pos1, const sdfVector3_t *pos2, const sdfVector3_t *pos3, const sdfColor32_t *col0, const sdfColor32_t *col1, const sdfColor32_t *col2, const sdfColor32_t *col3);
void eglLinkPoly42(f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2, f32 x3, f32 y3, f32 z3, u32 col0, u32 col1, u32 col2, u32 col3);
void *eglNewMesh3D(bool isEffect);
void *eglNewMesh2D(bool isEffect);
void eglDelMesh(void *mesh);
void DelMesh(void *mesh);
void eglLinkMesh(void *mesh);
void eglCloseMesh(void);
sdfVector4_t eglGetMeshSquareUV(s32 u, s32 v, s32 uw, s32 vh, void *th);
void eglAddMeshTriangleIdx(u16 count);
void eglAddMeshSquareIdx(u16 count);
