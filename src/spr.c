#include "types.h"
#include "dds3kerneldraw.h"
#include "kernel.h"
#include "sdfdraw.h"
#include "sdfprim.h"
#include "sdfsystem.h"
#include "spr.h"

typedef struct sdfPrimTransPacket_t sdfPrimTransPacket_t;

static void *mesh;
static sdfPrimTransPacket_t *trans_cz;

// 0x21f7b90
void sprClearZ(DDS3_OT ot) {
  sdfDrawTag_t *v3;
  void *Material;
  void *_36165888;
  void *transform;
  void *v14;
  void *v15;
  MeshEdit *edit;
  void *v17;
  MeshEdit *v18;

  v3 = sdfPrimAllocDrawTag();
  sdfDrawTagLink(v3, trans_cz);
  if (!op_Equality(mesh, 0, 0))
  {
    goto LABEL_8;
  }
  Material = GetMaterial(Instance, "standard", 0);
  _36165888 = Make_36165888(Material, 0);
  mesh = _36165888;
  transform = get_transform(mesh, 0);
  v14 = get_transform(hook, 0);
  SetParent_61042560(transform, v14, 0, 0);
  SetAutoHide(mesh, 1, 0);
  InitSquare(mesh, 1, 0);
  v15 = mesh;
  edit = v15->edit;
  v15->type = 0;
  (edit->klass->vtable._4_unknown.methodPtr)(edit, edit->klass->vtable._4_unknown.method);
  SetSquarePos_36171728(mesh, 0, 28672, 30976, 36864, 34560, 0);
  v17 = mesh;
  SetSquareCol_36172464(v17, 0, zeroVector, 0);
  SetSquareIndex_36173424(mesh, 0);
  SetMarker(mesh, 0);
  v18 = mesh->edit;
  (v18->klass->vtable._5_unknown.methodPtr)(v18, v18->klass->vtable._5_unknown.method);
LABEL_8:
  sdfDrawTagLink(v3, mesh->packet);
  sdfDrawTagLinkOt(Ot[ot], v3);
}
