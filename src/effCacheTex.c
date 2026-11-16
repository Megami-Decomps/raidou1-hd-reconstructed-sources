#include "types.h"
#include "effcachetex.h"

typedef struct effCtexHandle_t effCtexHandle_t;

// 0x1972d80
void effEnvInit(void) {
  ;
}

// 0x1972d90
effCtexHandle_t *Create(void *pTex) {
  effCtexHandle_t *v3;

  v3 = Allocate(effCtexHandle_t);
  v3->pPixel = pTex;
  v3->use = 1;
  return v3;
}

// 0x1972e20
effCtexHandle_t *effCreateGID(void *pTex) {
  effCtexHandle_t *v3;

  v3 = Allocate(effCtexHandle_t);
  v3->pPixel = pTex;
  v3->use = 1;
  return v3;
}

// 0x1972ea0
void Delete(effCtexHandle_t *hCtex) {
  --hCtex->use;
}

// 0x1972eb0
effCtexHandle_t *Copy(effCtexHandle_t *hCTex) {
  ++hCTex->use;
  return hCTex;
}
