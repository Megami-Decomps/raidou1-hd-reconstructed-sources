#include "types.h"
#include "dds3modelrangebasic.h"
#include "dds3worldbasic.h"

typedef struct dds3Basic_t dds3Basic_t;

// 0x22fd890
bool dds3ModelRangeBasicConstructor(dds3Basic_t *pBasic) {
  void *v3;
  void *p_workdata;
  void *v5;
  void *v7;

  v3 = Allocate(Project_Basic_dds3ModelRangeBasicWorkData_t);
  _ctor(v3, 0);
  pBasic->workdata = v3;
  p_workdata = &pBasic->workdata;
  v5 = p_workdata;
  v5[1].klass = 0;
  v7 = v5 + 1;
  v7->monitor = 0;
  v7[1].klass = 0;
  v7[1].monitor = 0;
  return 1;
}

// 0x22fd9b0
s32 dds3ModelRangeBasicDestructor(dds3Basic_t *pBasic) {
  void *workdata;

  workdata = pBasic->workdata;
  return 0;
}

// 0x22fda30
void dds3ModelRangeBasicSetBlockID(dds3Basic_t *aPtr, s32 blockID) {
  void *workdata;

  workdata = aPtr->workdata;
  LODWORD(workdata[2].monitor) = blockID;
}

// 0x22fdac0
s32 dds3ModelRangeBasicGetBlockID(s32 resID) {
  dds3Basic_t *ControlScene;
  void *workdata;
  s64 naturalAligment;
  u64 *v9;
  s64 v10;
  s64 v11;

  ControlScene = dds3GetControlScene();
  workdata = ControlScene->workdata;
  if (!workdata)
    goto LABEL_13;
  if (workdata->klass->_2.naturalAligment < (u32)naturalAligment || workdata->klass->_2.typeHierarchy[naturalAligment - 1] != dds3SceneBasic_t)
  {
LABEL_19:
  }
LABEL_13:
  v9 = (*((u64 *)workdata[1].monitor + 10) + 24);
  do
  {
    v10 = *v9;
    v9 = (*v9 + 64);
  }
  while (*(u32 *)(v10 + 20) != resID);
  workdata = *(void *)(v10 + 48);
  if (workdata)
  {
    if (workdata->klass->_2.naturalAligment < (u32)v11 || workdata->klass->_2.typeHierarchy[v11 - 1] != Project_Basic_dds3ModelRangeBasicWorkData_t)
    {
      goto LABEL_19;
    }
  }
  return (s32)workdata[2].monitor;
}
