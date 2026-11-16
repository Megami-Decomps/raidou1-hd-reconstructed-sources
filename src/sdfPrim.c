#include "types.h"
#include "sdf_prim.h"
#include "sdfprim.h"

typedef struct sdfDrawTag_t sdfDrawTag_t;
typedef struct sdfPrimTransPacket_t sdfPrimTransPacket_t;

// 0x2265900
sdfDrawTag_t *sdfPrimAllocDrawTag(void) {
  Il2CppObject *v1;

  v1 = Allocate(sdfDrawTag_t);
  _ctor(v1, 0);
  v1[1].klass = 0;
  v1[1].monitor = 0;
  v1[2].klass = 0;
  return (sdfDrawTag_t *)v1;
}

// 0x22618c0
void sdfPrimSetOpaquePacket(sdfPrimTransPacket_t *aPkt) {
  SDF_GS_TEST *p_OPAQUE_TEST_ELEM;
  SDF_GS_TEST *v5;

  p_OPAQUE_TEST_ELEM = &OPAQUE_TEST_ELEM;
  v5 = p_OPAQUE_TEST_ELEM;
  aPkt->test = p_OPAQUE_TEST_ELEM;
  aPkt->alpha = OPAQUE_ALPHA_ELEM;
}

// 0x2261950
void sdfPrimSetSemiTransPacket(sdfPrimTransPacket_t *aPkt) {
  aPkt->test = SEMITRANS_TEST_ELEM;
  aPkt->alpha = SEMITRANS_ALPHA_ELEM;
}

// 0x22619e0
void sdfPrimSetAddTransPacket(sdfPrimTransPacket_t *aPkt) {
  aPkt->test = ADDTRANS_TEST_ELEM;
  aPkt->alpha = ADDTRANS_ALPHA_ELEM;
}

// 0x2261a70
void sdfPrimSetSubTransPacket(sdfPrimTransPacket_t *aPkt) {
  aPkt->test = SUBTRANS_TEST_ELEM;
  aPkt->alpha = SUBTRANS_ALPHA_ELEM;
}
