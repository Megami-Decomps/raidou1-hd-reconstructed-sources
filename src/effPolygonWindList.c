#include "types.h"
#include "eff.h"
#include "effcachetex.h"
#include "effpolygonwindlist.h"
#include "sdfbase.h"
#include "sdfdraw.h"
#include "tneffect.h"

#define EFFPWLIST_CACHETEX_FILE "wind00"

typedef struct effCtexHandle_t effCtexHandle_t;
typedef struct wplistHandle_t wplistHandle_t;

void *wplistFaceIndex;
static effCtexHandle_t *hWplistCacheTex;

static wplistHandle_t *HandleCreate(u32 number, u32 face);

// 0x1996fb0
static wplistHandle_t *HandleCreate(u32 number, u32 face) {
  wplistHandle_t *v5;

  v5 = Allocate(wplistHandle_t);
  v5->number = number;
  v5->blend = 2;
  v5->zTest = 0;
  v5->point = 4 * face + 4;
  v5->face = face;
  v5->abgr = oneVector;
  return v5;
}

// 0x1997080
wplistHandle_t *effPolygonWindCreate(u32 number, u32 face, void *pTex) {
  wplistHandle_t *v8;
  effCtexHandle_t *v12;

  v8 = Allocate(wplistHandle_t);
  v8->number = number;
  v8->blend = 2;
  v8->zTest = 0;
  v8->point = 4 * face + 4;
  v8->face = face;
  v8->abgr = oneVector;
  if (!op_Equality(pTex, 0, 0))
  {
    v12 = Create(pTex, 0);
    goto LABEL_17;
  }
  v12 = Copy(hWplistCacheTex);
LABEL_17:
  v8->hCacheTex = v12;
  return v8;
}

// 0x1997230
void effPolygonWindDelete(wplistHandle_t *hPolygon) {
  Delete(hPolygon->hCacheTex);
}

// 0x1997240
wplistHandle_t *Copy(wplistHandle_t *hSrc) {
  u32 number;
  s32 face;
  wplistHandle_t *v6;
  effCtexHandle_t *v8;

  number = hSrc->number;
  face = hSrc->face;
  v6 = Allocate(wplistHandle_t);
  v6->number = number;
  v6->blend = 2;
  v6->point = 4 * face + 4;
  v6->face = face;
  v6->zTest = 0;
  v6->abgr = oneVector;
  v8 = Copy(hSrc->hCacheTex);
  v6->hCacheTex = v8;
  return v6;
}

// 0x1997390
void effPolygonWindDraw(wplistHandle_t *hPolygon, const sdfMatrix4_t *pMatrix) {
  s64 blend;
  sdfGrOt_t *v7;
  sdfDrawTag_t *v8;
  void *transform;
  f32 *p_x;
  void *v13;
  void *v14;
  sdfMatrix4_t v17;
  sdfMatrix4_t v18;
  sdfMatrix4_t v19;
  sdfVector3_t lossyScale;
  sdfVector4_t Row;
  sdfVector3_t v22;
  sdfVector3_t v23;
  sdfQuaternion_t rotation;

  if (hPolygon->number && hPolygon->abgr.w != 0.0)
  {
    blend = hPolygon->blend;
    v7 = pOt_Table[camID][blend];
    v8 = Allocate(sdfDrawTag_t);
    _ctor(v8, 0);
    sdfDrawTagInit(v8);
    effZTestOff(v8, hPolygon->zTest);
    transform = get_transform(hPolygon->pMesh->mesh, 0);
    Row = GetRow(pMatrix, 3, 0);
    p_x = &modVec.x;
    v22.y = Row.y * p_x[7];
    v22.x = Row.x * p_x[6];
    v22.z = Row.z * p_x[8];
    set_localPosition(transform, v22, 0);
    v13 = get_transform(hPolygon->pMesh->mesh, 0);
    get_transpose(&v18, pMatrix, 0);
    v19 = v18;
    rotation = get_rotation(&v19, 0);
    set_localRotation(v13, rotation, 0);
    v14 = get_transform(hPolygon->pMesh->mesh, 0);
    get_transpose(&v17, pMatrix, 0);
    v19 = v17;
    lossyScale = get_lossyScale(&v19, 0);
    v23.y = lossyScale.y * modPos.y;
    v23.x = lossyScale.x * modPos.x;
    v23.z = lossyScale.z * modPos.z;
    set_localScale(v14, v23, 0);
    SetColor(hPolygon->pMesh->mesh, hPolygon->abgr);
    sdfDrawTagLink(v8, hPolygon->pMesh->mesh->packet);
    effZTestOn(v8, hPolygon->zTest);
    sdfDrawTagLinkOt(v7, v8);
    return;
  }
}

// 0x1997890
void effPolygonWindInit(void) {
  Il2CppObject *Asset_object;
  effCtexHandle_t *GID;

  if (texture)
  {
    Asset_object = GetAsset_object_(texture, "wind00");
    GID = effCreateGID(Asset_object);
    hWplistCacheTex = GID;
  }
}
