#include "types.h"
#include "__newdds3.h"
#include "effenvquake2.h"
#include "effparts.h"

typedef struct Standard Standard;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct effQuake2_Params_t effQuake2_Params_t;
typedef struct quake2Handle_t quake2Handle_t;

static quake2Handle_t *Create(effQuake2_Params_t *pParams);

// 0x19739a0
static quake2Handle_t *Create(effQuake2_Params_t *pParams) {
  quake2Handle_t *v3;

  v3 = Allocate(quake2Handle_t);
  v3->frame = 0;
  v3->param = pParams;
  return v3;
}

// 0x1973a30
quake2Handle_t *PartsCreate(Standard *pParts) {
  u8 *v3;
  sdfBinary *v4;
  effQuake2_Params_t *v5;
  quake2Handle_t *v6;

  v3 = effParamsGet(pParts);
  v4 = Allocate(sdfBinary);
  _ctor_36176832(v4, v3, 0);
  v5 = Allocate(effQuake2_Params_t);
  v5->life = ReadS32(v4, 0);
  v5->power = ReadU16(v4, 0);
  Align(v4, 4, 0);
  v5->fade_in = ReadU32(v4, 0);
  v5->fade_out = ReadU32(v4, 0);
  v6 = Allocate(quake2Handle_t);
  v6->frame = 0;
  v6->param = v5;
  return v6;
}

// 0x1973c20
void Delete(effPartsHandle_t *handle) {
  QuakeEnd();
}

// 0x1973c40
quake2Handle_t *Copy(effPartsHandle_t *handle) {
  u32 *monitor;
  effQuake2_Params_t *v5;
  s64 v6;
  char v7;
  quake2Handle_t *v8;

  monitor = handle[1].monitor;
  v5 = Allocate(effQuake2_Params_t);
  v5->life = monitor[4];
  v6 = *((u64 *)monitor + 3);
  v5->power = *((u16 *)monitor + 10);
  v7 = byte_57562A6;
  *(u64 *)&v5->fade_in = v6;
  v8 = Allocate(quake2Handle_t);
  v8->frame = 0;
  v8->param = v5;
  return v8;
}

// 0x1973e20
void Run(effPartsHandle_t *handle) {
  s32 klass;

  klass = handle[1].klass;
  if (klass)
  {
    LODWORD(handle[1].klass) = klass + 1;
  }
  else
  {
    SetQuake(*((u32 *)handle[1].monitor + 4), *((u16 *)handle[1].monitor + 10), *((u32 *)handle[1].monitor + 6), *((u32 *)handle[1].monitor + 7));
    ++LODWORD(handle[1].klass);
  }
}
