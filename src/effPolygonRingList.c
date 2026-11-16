#include "types.h"
#include "eff.h"
#include "effpolygonringlist.h"
#include "sdf_gs_alpha.h"
#include "sdfbase.h"
#include "sdfdraw.h"

typedef struct rplistHandle_t rplistHandle_t;

void *rplistFaceIndex;

// 0x198bc70
rplistHandle_t *effPolygonRingCreate(u32 face) {
  rplistHandle_t *v3;

  v3 = Allocate(rplistHandle_t);
  v3->blend = 2;
  v3->zTest = 0;
  v3->point = 4 * face + 4;
  v3->abgr = oneVector;
  return v3;
}

// 0x198bd40
void effPolygonRingDelete(rplistHandle_t *hPolygon) {
  effPolygonRingMesh *v3;
  void *p_pMesh;
  effPolygonRingMesh *pMesh;
  void *gameObject;

  pMesh = hPolygon->pMesh;
  p_pMesh = &hPolygon->pMesh;
  v3 = pMesh;
  if (pMesh)
  {
    gameObject = get_gameObject(v3->mesh, 0);
    DestroyImmediate_61008224(gameObject, 0);
    Destroy(p_pMesh);
    p_pMesh = 0;
  }
}

// 0x198bdf0
void effPolygonRingDraw(rplistHandle_t *hPolygon, const sdfMatrix4_t *pMatrix) {
  sdfDrawTag_t *v5;
  s32 blend;
  SDF_GS_ALPHA *v7;
  void *v8;
  void **p_SET_01010;
  _BOOL4 zTest;
  void *transform;
  f32 *p_x;
  void *v18;
  void *v19;
  void *v21;
  s32 v22;
  sdfGrOt_t *v23;
  sdfMatrix4_t v24;
  sdfMatrix4_t v25;
  sdfMatrix4_t v26;
  sdfVector3_t lossyScale;
  sdfVector4_t Row;
  sdfVector3_t v29;
  sdfVector3_t v30;
  sdfQuaternion_t rotation;

  memset(&v26, 0, sizeof(v26));
  v5 = Allocate(sdfDrawTag_t);
  _ctor(v5, 0);
  blend = hPolygon->blend;
  sdfDrawTagInit(v5);
  v7 = 0;
  if (blend >= 5)
  {
    v8 = Allocate(Project_libsdf_sdfPrimAlphaPacket_t);
    _ctor(v8, 0);
    v8->alpha = SET_21000;
    sdfDrawTagLink(v5, v8);
    if (hPolygon->blend == 5)
    {
      p_SET_01010 = &SET_01010;
    }
    else
    {
      p_SET_01010 = &SET_20010;
    }
    v7 = *p_SET_01010;
  }
  zTest = hPolygon->zTest;
  effZTestOff(v5, zTest);
  (hPolygon->pMesh->klass->vtable._5_PreUpdate.methodPtr)(hPolygon->pMesh, hPolygon->pMesh->klass->vtable._5_PreUpdate.method);
  transform = get_transform(hPolygon->pMesh->mesh, 0);
  Row = GetRow(pMatrix, 3, 0);
  p_x = &modVec.x;
  v29.y = Row.y * p_x[7];
  v29.x = Row.x * p_x[6];
  v29.z = Row.z * p_x[8];
  set_localPosition(transform, v29, 0);
  v18 = get_transform(hPolygon->pMesh->mesh, 0);
  get_transpose(&v25, pMatrix, 0);
  v26 = v25;
  rotation = get_rotation(&v26, 0);
  set_localRotation(v18, rotation, 0);
  v19 = get_transform(hPolygon->pMesh->mesh, 0);
  get_transpose(&v24, pMatrix, 0);
  v26 = v24;
  lossyScale = get_lossyScale(&v26, 0);
  v30.y = lossyScale.y * modPos.y;
  v30.x = lossyScale.x * modPos.x;
  v30.z = lossyScale.z * modPos.z;
  set_localScale(v19, v30, 0);
  SetColor(hPolygon->pMesh->mesh, hPolygon->abgr);
  sdfDrawTagLink(v5, hPolygon->pMesh->mesh->packet);
  effZTestOn(v5, hPolygon->zTest);
  if (blend >= 5)
  {
    v21 = Allocate(Project_libsdf_sdfPrimAlphaPacket_t);
    _ctor(v21, 0);
    v21->alpha = v7;
    sdfDrawTagLink(v5, v21);
  }
  v22 = hPolygon->blend;
  v23 = effOtGet(v22);
  sdfDrawTagLinkOt(v23, v5);
}
