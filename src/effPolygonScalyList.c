#include "types.h"
#include "eff.h"
#include "effcachetex.h"
#include "effpolygonscalylist.h"
#include "sdfbase.h"
#include "sdfdraw.h"
#include "tneffect.h"

#define EFFPSLIST_CACHETEX_FILE "scaly00"

typedef struct effCtexHandle_t effCtexHandle_t;
typedef struct splistHandle_t splistHandle_t;

void *splistFaceIndex;
effCtexHandle_t *hSplistCacheTex;
effCtexHandle_t *hSplistCacheMTex;

static splistHandle_t *HandleCreate(u32 number, u32 face);

// 0x198d5f0
static splistHandle_t *HandleCreate(u32 number, u32 face) {
  splistHandle_t *v5;

  v5 = Allocate(splistHandle_t);
  v5->number = number;
  v5->blend = 2;
  v5->point = 4 * face + 4;
  v5->face = face;
  v5->abgr = oneVector;
  return v5;
}

// 0x198d6c0
splistHandle_t *effPolygonScalyCreate(u32 number, u32 face) {
  splistHandle_t *v5;

  if (!number)
    return 0;
  v5 = Allocate(splistHandle_t);
  v5->number = number;
  v5->blend = 2;
  v5->point = 4 * face + 4;
  v5->face = face;
  v5->abgr = oneVector;
  return v5;
}

// 0x198d7e0
void effPolygonScalyDelete(splistHandle_t *hPolygon) {
  ;
}

// 0x198d7f0
splistHandle_t *Copy(splistHandle_t *hSrc) {
  u32 number;
  s32 face;
  splistHandle_t *v6;

  number = hSrc->number;
  face = hSrc->face;
  v6 = Allocate(splistHandle_t);
  v6->number = number;
  v6->blend = 2;
  v6->point = 4 * face + 4;
  v6->face = face;
  v6->abgr = oneVector;
  return v6;
}

// 0x198d910
void effPolygonScalyDraw(splistHandle_t *hPolygon, const sdfMatrix4_t *pMatrix) {
  s32 blend;
  sdfGrOt_t *v6;
  sdfDrawTag_t *v7;
  void *transform;
  f32 *p_x;
  void *v11;
  void *v12;
  sdfMatrix4_t v14;
  sdfMatrix4_t v15;
  sdfMatrix4_t v16;
  sdfVector3_t lossyScale;
  sdfVector4_t Row;
  sdfVector3_t v19;
  sdfVector3_t v20;
  sdfQuaternion_t rotation;

  if ((s32)hPolygon->number >= 1 && hPolygon->abgr.w != 0.0)
  {
    blend = hPolygon->blend;
    v6 = effOtGet(blend);
    v7 = Allocate(sdfDrawTag_t);
    _ctor(v7, 0);
    sdfDrawTagInit(v7);
    transform = get_transform(hPolygon->pMesh->mesh, 0);
    Row = GetRow(pMatrix, 3, 0);
    p_x = &modVec.x;
    v19.y = Row.y * p_x[7];
    v19.x = Row.x * p_x[6];
    v19.z = Row.z * p_x[8];
    set_localPosition(transform, v19, 0);
    v11 = get_transform(hPolygon->pMesh->mesh, 0);
    get_transpose(&v15, pMatrix, 0);
    v16 = v15;
    rotation = get_rotation(&v16, 0);
    set_localRotation(v11, rotation, 0);
    v12 = get_transform(hPolygon->pMesh->mesh, 0);
    get_transpose(&v14, pMatrix, 0);
    v16 = v14;
    lossyScale = get_lossyScale(&v16, 0);
    v20.y = lossyScale.y * modPos.y;
    v20.x = lossyScale.x * modPos.x;
    v20.z = lossyScale.z * modPos.z;
    set_localScale(v12, v20, 0);
    SetColor(hPolygon->pMesh->mesh, hPolygon->abgr);
    sdfDrawTagLink(v7, hPolygon->pMesh->mesh->packet);
    sdfDrawTagLinkOt(v6, v7);
  }
}

// 0x198cd90
void effPolygonScalyInit(void) {
  Il2CppObject *Asset_object;
  effCtexHandle_t *GID;
  Il2CppObject *v6;
  effCtexHandle_t *v7;

  if (texture)
  {
    Asset_object = GetAsset_object_(texture, "scaly00");
    GID = effCreateGID(Asset_object);
    hSplistCacheTex = GID;
    v6 = GetAsset_object_(texture, "scaly00m");
    v7 = effCreateGID(v6);
    hSplistCacheMTex = v7;
  }
}
