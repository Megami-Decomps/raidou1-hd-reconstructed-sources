#include "types.h"
#include "dds3effectmultifilter.h"
#include "dds3kerneldraw.h"
#include "sdfdraw.h"
#include "sdfsystem.h"
#include "sdfvsync.h"

typedef struct dds3Effect_Filter_t dds3Effect_Filter_t;

// 0x19590c0
void Execute(dds3Effect_Filter_t *pFilter, void *hTex) {
  sdfDrawTag_t *v7;
  void *mesh;
  void *transform;
  void *v11;
  sdfGrPacketHeader_t *packet;
  sdfPrimTransPacket_t *v13;
  void **p_SET_10AADD11;
  void *v16;
  SDF_GS_ALPHA *v18;

  if (drawSkip)
    return;
  v7 = Allocate(sdfDrawTag_t);
  _ctor(v7, 0);
  mesh = pFilter->mesh;
  sdfDrawTagInit(v7);
  if (!!op_Equality(mesh, 0, 0))
  {
    mesh = Make("effect", 0);
    transform = get_transform(mesh, 0);
    v11 = get_transform(hook, 0);
    SetParent_61042560(transform, v11, 0, 0);
    InitSquare(mesh, 1, 0);
    SetAutoHide(mesh, 1, 0);
    packet = mesh->packet;
    pFilter->mesh = mesh;
    packet->ctxt = 1;
  }
  v13 = Allocate(sdfPrimTransPacket_t);
  _ctor(v13, 0);
  v13->ctxt = 1;
  p_SET_10AADD11 = &SET_10AADD11;
  v16 = *p_SET_10AADD11;
  v13->test = (SDF_GS_TEST *)*p_SET_10AADD11;
  v18 = Get(pFilter->_blend);
  v13->alpha = v18;
  sdfDrawTagLink(v7, v13);
  (mesh->klass->vtable._7_SetTexture.methodPtr)(mesh, hTex, mesh->klass->vtable._7_SetTexture.method);
  (mesh->edit->klass->vtable._4_unknown.methodPtr)(mesh->edit, mesh->edit->klass->vtable._4_unknown.method);
  SetSquarePos_36171728(mesh, 0, pFilter->xy[0].x + 28672, pFilter->xy[0].y + 30976, pFilter->xy[1].x + 28672, pFilter->xy[1].y + 30976, 0);
  SetSquareUV_36173248(mesh, 0, 0);
  SetSquareCol_36172464(mesh, 0, pFilter->abgr, 0);
  SetSquareIndex_36173424(mesh, 0);
  SetMarker(mesh, 0);
  (mesh->edit->klass->vtable._5_unknown.methodPtr)(mesh->edit, mesh->edit->klass->vtable._5_unknown.method);
  sdfDrawTagLink(v7, mesh->packet);
  sdfDrawTagLinkOt(Ot[79], v7);
}
