#include "types.h"
#include "sdfgrot_t.h"

typedef struct sdfDrawTag_t sdfDrawTag_t;
typedef struct sdfGrOt_t sdfGrOt_t;

struct sdfGrOt_t {
    sdfGrOt_t *next;
    sdfDrawTag_t *tagHead;
    sdfDrawTag_t *tagTail;
    s32 renderQueue;
};

// 0x225d630
sdfGrOt_t *sdfGrGetArray(s32 count) {
  s64 v3;
  s32 *v4;
  s64 v5;
  s64 *v6;
  sdfGrOt_t *v7;

  v3 = NewSpecific(sdfGrOt_t, count);
  v4 = v3;
  if (*(s32 *)(v3 + 24) >= 1)
  {
    v5 = 0;
    v6 = (v3 + 32);
    do
    {
      v7 = Allocate(sdfGrOt_t);
      v7->renderQueue = 3100;
      _ctor(v7, 0);
      QueryInterface(v7, *(void **)(*(u64 *)v4 + 64));
      *v6 = v7;
      ++v5;
      ++v6;
    }
    while (v5 < v4[6]);
  }
  return (sdfGrOt_t *)v4;
}
