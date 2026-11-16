#include "types.h"
#include "dds3pointbasic.h"
#include "dds3scenebasic.h"
#include "sdf_vu0.h"

typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3PointBasicWorkData_t dds3PointBasicWorkData_t;
typedef struct fldResourcePoint_t fldResourcePoint_t;

// 0x2302e30
dds3Basic_t *dds3PointBasicAdd(u32 serialID, fldResourcePoint_t *pData, char *pName) {
  dds3Basic_t *v7;

  v7 = dds3SceneBasicAdd(16);
  v7->workdata = (void *)pData;
  v7->serialID = serialID;
  v7->name = pName;
  return v7;
}

// 0x2302ed0
void *dds3PointBasicGetResource(dds3Basic_t *pPointBasic) {
  return pPointBasic->workdata;
}

// 0x2302ee0
dds3PointBasicWorkData_t *dds3PointBasicGetWorkData(dds3Basic_t *pBasic) {
  void *workdata;
  dds3PointBasicWorkData_t *v5;

  workdata = pBasic->workdata;
  v5 = Allocate(dds3PointBasicWorkData_t);
  *(void *)&v5->pos = workdata[1];
  *(void *)&v5->rot = workdata[2];
  *(void *)&v5->scl = workdata[3];
  return v5;
}

// 0x2302fc0
void dds3PointBasicGetPosPoseSet(dds3Basic_t *pBasic) {
  struct sdfVector4_t pos;

  pos = dds3PointBasicGetWorkData(pBasic)->pos;
  vct_A = pos;
}

// 0x2303090
void dds3PointBasicGetRotPoseSet(dds3Basic_t *pBasic) {
  struct sdfVector4_t rot;

  rot = dds3PointBasicGetWorkData(pBasic)->rot;
  vct_A = rot;
}
