#include "types.h"
#include "effenvquake.h"
#include "effparts.h"
#include "effquake.h"

typedef struct Standard Standard;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct effQuake_Params_t effQuake_Params_t;
typedef struct quakeHandle_t quakeHandle_t;

static quakeHandle_t *Create(effQuake_Params_t *pParams);

// 0x1973430
static quakeHandle_t *Create(effQuake_Params_t *pParams) {
  quakeHandle_t *v3;
  effQuakeRequest_t *v4;

  v3 = Allocate(quakeHandle_t);
  v3->frame = 0;
  v3->param = pParams;
  v4 = effRegist();
  v3->req = v4;
  return v3;
}

// 0x1973500
quakeHandle_t *PartsCreate(Standard *pParts) {
  u8 *v3;
  sdfBinary *v4;
  effQuake_Params_t *v5;

  v3 = effParamsGet(pParts);
  v4 = Allocate(sdfBinary);
  _ctor_36176832(v4, v3, 0);
  v5 = Allocate(effQuake_Params_t);
  v5->life = ReadS32(v4, 0);
  v5->power = ReadU32(v4, 0);
  return Create(v5);
}

// 0x1973640
void Delete(effPartsHandle_t *handle) {
  effOption *option;

  option = handle[1].option;
  effRemove(option);
}

// 0x1973700
quakeHandle_t *Copy(effPartsHandle_t *handle) {
  void *monitor;
  Il2CppObject *v5;

  monitor = handle[1].monitor;
  v5 = Allocate(effQuake_Params_t);
  _ctor(v5, 0);
  v5[1].klass = *((Il2CppClass **)monitor + 2);
  return Create(v5);
}

// 0x1973870
void effRun(effPartsHandle_t *handle) {
  u32 *monitor;
  effOption *option;
  u32 v6;
  u32 v7;

  if (!get_STOP(0))
  {
    if (!LODWORD(handle[1].klass))
    {
      monitor = handle[1].monitor;
      option = handle[1].option;
      v7 = monitor[4];
      v6 = monitor[5];
      if (v7)
      {
        effStartDamp(option, v6, v7);
      }
      else
      {
        effStart(option, v6);
      }
    }
    ++LODWORD(handle[1].klass);
  }
}
