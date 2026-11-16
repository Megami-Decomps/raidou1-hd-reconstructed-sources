#include "types.h"
#include "dds3eventbasic.h"
#include "dds3scenebasic.h"

typedef struct dds3Basic_t dds3Basic_t;

// 0x230a170
dds3Basic_t *dds3EventBasicAdd(u32 serialID, void *pData, char *pName) {
  dds3Basic_t *v7;

  v7 = dds3SceneBasicAdd(12);
  v7->workdata = pData;
  v7->serialID = serialID;
  v7->name = pName;
  return v7;
}

// 0x230a210
void *dds3EventBasicGetResource(dds3Basic_t *pBasic) {
  return pBasic->workdata;
}
