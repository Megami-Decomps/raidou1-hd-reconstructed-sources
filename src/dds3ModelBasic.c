#include "types.h"
#include "dds3modelbasic.h"
#include "dds3scenebasic.h"
#include "sdfmotion.h"

typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct sdfModelDef_t sdfModelDef_t;
typedef struct sdfModelRootNode_t sdfModelRootNode_t;
typedef struct sdfMotionCtrlr_t sdfMotionCtrlr_t;
typedef struct sdfMotionPlayBook_t sdfMotionPlayBook_t;

dds3BasicFunction_t *Function;

static bool Constructor(dds3Basic_t *pBasic);
static void Destructor(dds3Basic_t *pBasic);

// 0x22fd090
static bool Constructor(dds3Basic_t *pBasic) {
  void *v3;
  void *v4;

  v3 = Allocate(Project_Basic_dds3ModelBasicWorkData_t);
  v4 = NewSpecific(uint, 3u);
  v3[2].monitor = v4;
  _ctor(v3, 0);
  pBasic->workdata = v3;
  Clear(v3);
  return 1;
}

// 0x22fd2f0
static void Destructor(dds3Basic_t *pBasic) {
  ;
}

// 0x22fd300
dds3Basic_t *dds3ModelBasicAdd(u32 serialID, sdfModelDef_t *pModelDef, sdfMotionPlayBook_t *pMotDef, dds3Basic_t *pTextureBasic, char *pName) {
  dds3Basic_t *v12;
  void *workdata;
  dds3Basic_t *v14;

  v12 = dds3SceneBasicAdd(10);
  workdata = v12->workdata;
  v14 = v12;
  if (!workdata)
  v14->serialID = serialID;
  v14->name = pName;
  workdata[1].klass = (Project_Basic_dds3Basic_t_WORK_c *)pTextureBasic;
  workdata[1].monitor = pModelDef;
  workdata[2].klass = (Project_Basic_dds3Basic_t_WORK_c *)pMotDef;
  return v14;
}

// 0x22fd450
dds3Basic_t *dds3ModelBasicAdd2(u32 serialID, sdfModelDef_t *pModelDef, sdfMotionPlayBook_t *pMotDef, char *pName) {
  dds3Basic_t *v10;
  void *workdata;
  dds3Basic_t *v12;

  v10 = dds3SceneBasicAdd(10);
  workdata = v10->workdata;
  v12 = v10;
  if (!workdata)
  v12->serialID = serialID;
  v12->name = pName;
  workdata[1].monitor = pModelDef;
  workdata[2].klass = (Project_Basic_dds3Basic_t_WORK_c *)pMotDef;
  return v12;
}

// 0x22fd580
sdfModelRootNode_t *dds3ModelBasicMakeRootNode(dds3Basic_t *pBasic) {
  sdfModelDef_t *workdata;
  s64 naturalAligment;
  sdfModelRootNode_t *v5;

  workdata = pBasic->workdata;
  if (workdata)
  {
    LOBYTE(workdata[9].extraData) < (u32)naturalAligment || *((Project_Basic_dds3ModelBasicWorkData_t_c **)(workdata)[6].monitor + naturalAligment - 1) != Project_Basic_dds3ModelBasicWorkData_t;
  }
  v5 = Make(workdata[3], workdata[3]->prefab, 0);
  SetAutoHide(v5->modelObj, 1, 0);
  v5->modelObj->isBg = 1;
  return v5;
}

// 0x22fd640
sdfMotionCtrlr_t *dds3ModelBasicMakeMotion(dds3Basic_t *pBasic, sdfModelRootNode_t *pRootNode) {
  void *workdata;
  sdfMotionPlayBook_t *klass;

  if (!pRootNode)
    return (sdfMotionCtrlr_t *)pRootNode;
  workdata = pBasic->workdata;
  klass = workdata[2].klass;
  if (klass)
  {
    pRootNode = sdfMotionCtrlrNew(pRootNode, klass);
    sdfMotionChange(pRootNode, 0, 1);
    return (sdfMotionCtrlr_t *)pRootNode;
  }
  return 0;
}
