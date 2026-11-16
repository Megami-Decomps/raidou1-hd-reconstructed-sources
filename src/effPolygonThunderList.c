#include "types.h"
#include "effpolygonthunderlist.h"

typedef struct tplistHandle_t tplistHandle_t;

void *tplistFaceIndex;

// 0x1991870
tplistHandle_t *effPolygonThunderCreate(u32 face) {
  u32 v3;
  tplistHandle_t *v4;
  void *v5;
  void *v6;
  void *v7;

  v3 = face + 1;
  v4 = Allocate(tplistHandle_t);
  v5 = NewSpecific(f32, v3);
  v4->alpha_e = v5;
  v6 = NewSpecific(f32, *(u32 *)((u64)v4->alpha_e + 24));
  v4->alpha_b = v6;
  v7 = NewSpecific(f32, *(u32 *)((u64)v4->alpha_e + 24));
  v4->alpha_c = v7;
  v4->zTest = 0;
  v4->blend = 2;
  v4->point = 5 * v3;
  return v4;
}

// 0x1991970
void effPolygonThunderDelete(tplistHandle_t *hPolygon) {
  ;
}
