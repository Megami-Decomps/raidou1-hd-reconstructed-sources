#include "types.h"
#include "EFFPFLIST_TYPE.h"
#include "dds3kerneldraw.h"
#include "eff.h"
#include "effcachetex.h"
#include "effpolygonflashlist.h"
#include "sdfbase.h"
#include "sdfdraw.h"
#include "sdfsystem.h"
#include "tneffect.h"

#define EFFPFLIST_CACHETEX_FILE_00 "flash00"
#define EFFPFLIST_CACHETEX_FILE_01 "flash01"

typedef struct effCtexHandle_t effCtexHandle_t;
typedef struct effOption effOption;
typedef struct effPolygonFlashMesh effPolygonFlashMesh;
typedef struct fplistHandle_t fplistHandle_t;

static void *pflist0FaceIndex;
static void *pflist1FaceIndex;
static void *pflist2FaceIndex;
void *pflist3FaceIndex;
void *uvTable;
static effCtexHandle_t *hFplistCacheTex;

static fplistHandle_t *HandleCreate(u32 face, EFFPFLIST_TYPE type, effPolygonFlashMesh *mesh);

// 0x1989e80
static fplistHandle_t *HandleCreate(u32 face, EFFPFLIST_TYPE type, effPolygonFlashMesh *mesh) {
  fplistHandle_t *v7;
  void *p_pflist0FaceIndex;
  s32 v10;
  s32 v11;
  s32 v15;

  v7 = Allocate(fplistHandle_t);
  switch (type)
  {
    case 0u:
      p_pflist0FaceIndex = &pflist0FaceIndex;
      v10 = 5;
      goto LABEL_19;
    case 1u:
      v10 = 13;
      p_pflist0FaceIndex = &pflist1FaceIndex;
      goto LABEL_19;
    case 2u:
      p_pflist0FaceIndex = &pflist2FaceIndex;
      goto LABEL_18;
    case 3u:
    case 4u:
      p_pflist0FaceIndex = &pflist3FaceIndex;
LABEL_18:
      v10 = 4;
LABEL_19:
      mesh->indexJob.table = *p_pflist0FaceIndex;
      mesh->indexJob.count = 0;
      mesh->indexJob.add = v10;
      v15 = (u8)byte_5756171;
      v7->blend = 2;
      if (!v15)
        goto LABEL_20;
      goto LABEL_21;
    default:
      v10 = 0;
      mesh->indexJob.count = 0;
      mesh->indexJob.add = 0;
      v11 = (u8)byte_5756171;
      v7->blend = 2;
      if (!v11)
      {
LABEL_20:
      }
LABEL_21:
      v7->type = type;
      v7->hCacheTex = 0;
      v7->face = face;
      v7->zTest = 0;
      v7->point = v10 * face;
      v7->abgr = oneVector;
      v7->pMesh = mesh;
      return v7;
  }
}

// 0x198a080
fplistHandle_t *effPolygonFlashCreate(u32 face, EFFPFLIST_TYPE type, void *pTex, effPolygonFlashMesh *mesh) {
  fplistHandle_t *v9;
  s32 v10;
  effCtexHandle_t *v12;
  effCtexHandle_t *v13;

  v9 = HandleCreate(face, type, mesh, mesh);
  if (((v9->pMesh->klass->vtable._7_get_UseUV.methodPtr)(v9->pMesh, v9->pMesh->klass->vtable._7_get_UseUV.method) & 1) == 0)
    return v9;
  if (op_Equality(pTex, 0, 0))
    goto LABEL_8;
  v13 = Create(pTex, 0);
LABEL_19:
  v9->hCacheTex = v13;
  return v9;
LABEL_8:
  v10 = v9->type;
  if (v10 == 4)
  {
    v12 = hFplistCacheTex[1];
    goto LABEL_18;
  }
  if (v10 == 3)
  {
    v12 = hFplistCacheTex[0];
LABEL_18:
    v13 = Copy(v12);
    goto LABEL_19;
  }
  return v9;
}

// 0x198a1f0
void effPolygonFlashDelete(fplistHandle_t *hPolygon) {
  effCtexHandle_t *hCacheTex;
  effPolygonFlashMesh *v4;
  void *p_pMesh;
  effPolygonFlashMesh *pMesh;
  void *mesh;
  void *gameObject;

  hCacheTex = hPolygon->hCacheTex;
  if (hCacheTex)
    Delete(hCacheTex);
  pMesh = hPolygon->pMesh;
  p_pMesh = &hPolygon->pMesh;
  v4 = pMesh;
  if (pMesh)
  {
    mesh = v4->mesh;
    if (!op_Inequality(mesh, 0, 0))
      goto LABEL_14;
    goto LABEL_9000;
    if (!op_Inequality(mesh, 0, 0))
    {
LABEL_14:
      Destroy(p_pMesh);
      p_pMesh = 0;
      return;
    }
LABEL_9000:
    gameObject = get_gameObject(p_pMesh[1].klass, 0);
    DestroyImmediate_61008224(gameObject, 0);
    goto LABEL_14;
  }
}

// 0x198a2f0
fplistHandle_t *Copy(fplistHandle_t *hSrc, effPolygonFlashMesh *mesh) {
  u32 face;
  u16 type;
  fplistHandle_t *v8;
  effCtexHandle_t *hCacheTex;
  effCtexHandle_t *v10;

  face = hSrc->face;
  type = hSrc->type;
  v8 = HandleCreate(face, type);
  hCacheTex = hSrc->hCacheTex;
  if (hCacheTex)
  {
    v10 = Copy(hCacheTex);
    v8->hCacheTex = v10;
  }
  return v8;
}

// 0x198a3a0
void effPolygonFlashDraw(fplistHandle_t *hPolygon, const sdfMatrix4_t *pMatrix, effOption *option) {
  s32 blend;
  sdfGrOt_t *v8;
  sdfDrawTag_t *v9;
  _BOOL4 zTest;
  bool v11;
  s32 FieldOt;
  s32 v14;
  void *transform;
  f32 *p_x;
  void *v18;
  void *v19;
  sdfMatrix4_t v21;
  sdfMatrix4_t v22;
  sdfMatrix4_t v23;
  sdfVector3_t lossyScale;
  sdfVector4_t Row;
  sdfVector3_t v26;
  sdfVector3_t v27;
  sdfQuaternion_t rotation;

  if (hPolygon->abgr.w != 0.0)
  {
    blend = hPolygon->blend;
    v8 = effOtGet(blend);
    v9 = Allocate(sdfDrawTag_t);
    _ctor(v9, 0);
    zTest = hPolygon->zTest;
    sdfDrawTagInit(v9);
    v11 = zTest;
    if (option)
    {
      FieldOt = option->FieldOt;
      if ((FieldOt & 0x80000000) == 0)
      {
        FieldOt = option->FieldOt;
        v14 = hPolygon->blend;
        v8 = Ot[FieldOt];
        effSetAlphaPacket(v9, v14);
        v11 = 0;
      }
    }
    effZTestOff(v9, v11);
    (hPolygon->pMesh->klass->vtable._5_PreUpdate.methodPtr)(hPolygon->pMesh, hPolygon->pMesh->klass->vtable._5_PreUpdate.method);
    transform = get_transform(hPolygon->pMesh->mesh, 0);
    Row = GetRow(pMatrix, 3, 0);
    p_x = &modVec.x;
    v26.y = Row.y * p_x[7];
    v26.x = Row.x * p_x[6];
    v26.z = Row.z * p_x[8];
    set_localPosition(transform, v26, 0);
    v18 = get_transform(hPolygon->pMesh->mesh, 0);
    get_transpose(&v22, pMatrix, 0);
    v23 = v22;
    rotation = get_rotation(&v23, 0);
    set_localRotation(v18, rotation, 0);
    v19 = get_transform(hPolygon->pMesh->mesh, 0);
    get_transpose(&v21, pMatrix, 0);
    v23 = v21;
    lossyScale = get_lossyScale(&v23, 0);
    v27.y = lossyScale.y * modPos.y;
    v27.x = lossyScale.x * modPos.x;
    v27.z = lossyScale.z * modPos.z;
    set_localScale(v19, v27, 0);
    SetColor(hPolygon->pMesh->mesh, hPolygon->abgr);
    sdfDrawTagLink(v9, hPolygon->pMesh->mesh->packet);
    effZTestOn(v9, v11);
    sdfDrawTagLinkOt(v8, v9);
  }
}

// 0x1988720
void effPolygonFlashInit(void) {
  Il2CppObject *Asset_object;
  effCtexHandle_t *GID;
  effCtexHandle_t *v6;
  effCtexHandle_t *v7;
  effCtexHandle_t *v10;

  if (texture)
  {
    Asset_object = GetAsset_object_(texture, "flash00");
    GID = effCreateGID(Asset_object);
    v6 = GID;
    v7[1] = v10;
  }
}

// 0x198a6b0
bool effPolygonFlashSetMesh(fplistHandle_t *hPolygon) {
  void *mesh;
  bool v5;
  void *v7;
  effPolygonFlashMesh *pMesh;
  void *transform;
  void *v11;

  mesh = hPolygon->pMesh->mesh;
  v5 = op_Equality(mesh, 0, 0);
  if (!v5)
    return v5;
  v7 = Make("effect", 0);
  pMesh = hPolygon->pMesh;
  pMesh->mesh = (void *)v7;
  (hPolygon->pMesh->klass[1]._1.image)(hPolygon->pMesh, hPolygon, hPolygon->pMesh->klass[1]._1.gc_desc);
  transform = get_transform(v7, 0);
  v11 = get_transform(hook, 0);
  SetParent_61042560(transform, v11, 0, 0);
  SetAutoHide(v7, 1, 0);
  return v5;
}
