#include "types.h"
#include "dds3effectfilter.h"
#include "dds3kerneldraw.h"
#include "eff.h"
#include "sdfdraw.h"
#include "sdfsystem.h"
#include "sdfvsync.h"

typedef struct dds3Effect_Filter_t dds3Effect_Filter_t;

// 0x19587b0
void dds3EffectDelete(dds3Effect_Filter_t *pFilter) {
  void *p_mesh;
  void *v5;
  void *mesh;
  void *gameObject;

  mesh = pFilter->mesh;
  p_mesh = &pFilter->mesh;
  v5 = mesh;
  if (!op_Inequality(v5, 0, 0))
    return;
  gameObject = get_gameObject(p_mesh, 0);
  DestroyImmediate_61008224(gameObject, 0);
  p_mesh = 0;
}

// 0x1958890
void Execute(dds3Effect_Filter_t *pFilter) {
  sdfDrawTag_t *v5;
  void *mesh;
  SDF_GS_ALPHA *v10;
  void *transform;
  void *v14;

  if (drawSkip)
    return;
  v5 = Allocate(sdfDrawTag_t);
  _ctor(v5, 0);
  mesh = pFilter->mesh;
  sdfDrawTagInit(v5);
  if (!!op_Equality(mesh, 0, 0))
  {
    mesh = Make("effect", 0);
    transform = get_transform(mesh, 0);
    v14 = get_transform(hook, 0);
    SetParent_61042560(transform, v14, 0, 0);
    InitSquare(mesh, 1, 0);
    mesh->type = 0;
    SetAutoHide(mesh, 1, 0);
    pFilter->mesh = mesh;
  }
  v10 = Get(pFilter->_blend);
  effSetTestAlphaPacket(v5, SET_10AADD11, v10);
  (mesh->edit->klass->vtable._4_unknown.methodPtr)(mesh->edit, mesh->edit->klass->vtable._4_unknown.method);
  SetSquarePos_36171728(mesh, 0, 16 * pFilter->xy[0].x + 28672, 8 * pFilter->xy[0].y + 30976, 16 * pFilter->xy[1].x + 28672, 8 * pFilter->xy[1].y + 30976, 0);
  SetSquareCol_36172464(mesh, 0, pFilter->abgr, 0);
  SetSquareIndex_36173424(mesh, 0);
  SetMarker(mesh, 0);
  (mesh->edit->klass->vtable._5_unknown.methodPtr)(mesh->edit, mesh->edit->klass->vtable._5_unknown.method);
  sdfDrawTagLink(v5, mesh->packet);
  sdfDrawTagLinkOt(Ot[79], v5);
}
