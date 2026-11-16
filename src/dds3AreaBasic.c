#include "types.h"
#include "basic.h"
#include "dds3areabasic.h"
#include "dds3objectbase.h"
#include "dds3scenebasic.h"
#include "dds3worldbasic.h"

typedef struct dds3BasicArrayHandle_t dds3BasicArrayHandle_t;
typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;

dds3BasicFunction_t *Function;

static bool Constructor(dds3Basic_t *pBasic);
static void Destructor(dds3Basic_t *pBasic);
static bool Mainprocuder(dds3Basic_t *pBasic);
static bool Drawprocuder(dds3Basic_t *pBasic);

// 0x22efb40
static bool Constructor(dds3Basic_t *pBasic) {
  Il2CppObject *v3;
  void *p_workdata;
  void *v5;
  Project_Basic_dds3Basic_t_WORK_c *v7;
  void *v8;
  Project_Basic_dds3Basic_t_WORK_c *klass;
  dds3BasicArrayHandle_t *v10;
  Project_Basic_dds3Basic_t_WORK_c *v11;
  dds3BasicArrayHandle_t *BasicArrayHandle;
  Project_Basic_dds3Basic_t_WORK_c *v13;
  dds3BasicArrayHandle_t *v14;
  Project_Basic_dds3Basic_t_WORK_c *v15;
  dds3BasicArrayHandle_t *v16;

  v3 = Allocate(dds3AreaBasicWorkData_t);
  _ctor(v3, 0);
  pBasic->workdata = (void *)v3;
  p_workdata = &pBasic->workdata;
  v5 = p_workdata;
  v7 = NewSpecific(dds3BasicArrayHandle_t, 2u);
  v5[1].klass = v7;
  v8 = v5 + 1;
  klass = v5[1].klass;
  v10 = Allocate(dds3BasicArrayHandle_t);
  _ctor(v10, 0);
  if (v10 && !QueryInterface(v10, *((void **)klass->_1.image + 8)))
    goto LABEL_21;
  klass->_1.byval_arg.data = v10;
  v11 = v8->klass;
  BasicArrayHandle = dds3GetBasicArrayHandle(0);
  if (BasicArrayHandle)
  {
    if (!QueryInterface(BasicArrayHandle, *((void **)v11->_1.image + 8)))
      goto LABEL_21;
  }
  v11->_1.byval_arg.data = BasicArrayHandle;
  v13 = v8->klass;
  v14 = Allocate(dds3BasicArrayHandle_t);
  _ctor(v14, 0);
  if (v14 && !QueryInterface(v14, *((void **)v13->_1.image + 8)))
    goto LABEL_21;
  *(u64 *)&v13->_1.byval_arg.bits = v14;
  v15 = v8->klass;
  v16 = dds3GetBasicArrayHandle(0);
  if (!v16)
    goto LABEL_20;
LABEL_19:
  if (QueryInterface(v16, *((void **)v15->_1.image + 8)))
    goto LABEL_20;
LABEL_21:
  v16 = dds3GetBasicArrayHandle(0);
  if (v16)
    goto LABEL_19;
LABEL_20:
  *(u64 *)&v15->_1.byval_arg.bits = v16;
  p_workdata = v5;
  return 1;
}

// 0x22efdd0
static void Destructor(dds3Basic_t *pBasic) {
  void *workdata;
  Project_Basic_dds3Basic_t_WORK_c *klass;
  void *v6;
  Project_Basic_dds3Basic_t_WORK_c *v7;
  void *v8;
  Project_Basic_dds3Basic_t_WORK_c *v9;
  Project_Basic_dds3Basic_t_WORK_c *v10;

  workdata = pBasic->workdata;
  if (workdata)
  {
    klass = workdata[1].klass;
    v6 = Allocate(System_Func_dds3Basic_t__bool_);
    bool____ctor(v6, 0, Method_Project_Basic_dds3AreaBasic_CB_ReleaseObjectBasic__, 0);
    dds3CallbackBasicArray(&klass->_1.byval_arg, v6);
    v7 = workdata[1].klass;
    v8 = Allocate(System_Func_dds3Basic_t__bool_);
    bool____ctor(v8, 0, Method_Project_Basic_dds3AreaBasic_CB_ReleaseObjectBasic__, 0);
    dds3CallbackBasicArray(&v7->_1.byval_arg.bits, v8);
    v9 = workdata[1].klass;
    dds3FreeBasicArrayHandle(&v9->_1.byval_arg);
    v10 = workdata[1].klass;
    dds3FreeBasicArrayHandle(&v10->_1.byval_arg.bits);
  }
}

// 0x22eff60
static bool Mainprocuder(dds3Basic_t *pBasic) {
  return 1;
}

// 0x22eff70
static bool Drawprocuder(dds3Basic_t *pBasic) {
  void *workdata;
  Project_Basic_dds3Basic_t_WORK_c *klass;
  void *v6;

  workdata = pBasic->workdata;
  klass = workdata[1].klass;
  v6 = Allocate(System_Func_dds3Basic_t__bool_);
  bool____ctor(v6, 0, Method_Project_Basic_dds3AreaBasic_CB_BasicDrawProcuder__, 0);
  dds3CallbackBasicArray(&klass->_1.byval_arg, v6);
  return 1;
}

// 0x22f0080
bool CB_BasicDrawProcuder(dds3Basic_t *pBasic) {
  void *drawprocuder;

  drawprocuder = pBasic->basicfunction->drawprocuder;
  return !drawprocuder
      || (drawprocuder->invoke_impl)(drawprocuder->method_code, pBasic, drawprocuder->method);
}

// 0x22f00b0
bool CB_ReleaseObjectBasic(dds3Basic_t *pBasic) {
  dds3Basic_t *v3;
  dds3Basic_t *pObjectBasic;

  v3 = 0;
  pObjectBasic = pBasic;
  dds3ObjectBaseSetControlBasicType(pObjectBasic, v3, 4u);
  return 1;
}

// 0x22f00f0
DDS3_AREABASIC_ITEMTYPE BasicTypeToItemType(BASIC_TYPE type) {
  return type == 8;
}

// 0x22f0110
dds3Basic_t *dds3AreaBasicAdd(u32 serialID, char *pName) {
  dds3Basic_t *v5;

  v5 = dds3SceneBasicAdd(2);
  v5->serialID = serialID;
  v5->name = pName;
  return v5;
}

// 0x22f01a0
void dds3AreaBasicRegistItem(dds3Basic_t *pAreaBasic, dds3Basic_t *pItemBasic) {
  dds3BasicArrayHandle_t *v5;
  u32 type;
  _BOOL4 v8;
  void *workdata;
  dds3BasicArrayHandle_t *hndl;

  v5 = Allocate(dds3BasicArrayHandle_t);
  _ctor(v5, 0);
  type = pItemBasic->type;
  v8 = HIBYTE(type) == 8 && type >> 26 != 1;
  workdata = pAreaBasic->workdata;
  hndl = *((dds3BasicArrayHandle_t *)&workdata[1].klass->_1.byval_arg.data + v8);
  dds3SetFirstBasicArray(hndl);
  if (!dds3SetSearchNextBasicArray(hndl, pItemBasic))
  {
    dds3AddBasicArray(hndl, 1);
    dds3SetBasicArray(hndl, pItemBasic);
  }
}

// 0x22f03e0
void dds3AreaBasicReleaseItem(dds3Basic_t *pAreaBasic, dds3Basic_t *pItemBasic) {
  dds3BasicArrayHandle_t *v5;
  u32 type;
  _BOOL4 v8;
  void *workdata;
  dds3BasicArrayHandle_t *hArray;

  v5 = Allocate(dds3BasicArrayHandle_t);
  _ctor(v5, 0);
  type = pItemBasic->type;
  v8 = HIBYTE(type) == 8 && type >> 26 != 1;
  workdata = pAreaBasic->workdata;
  hArray = *((dds3BasicArrayHandle_t *)&workdata[1].klass->_1.byval_arg.data + v8);
  dds3SearchDeleteBasicArray(hArray, pItemBasic, 0);
}

// 0x22f0340
dds3BasicArrayHandle_t *dds3AreaBasicGetItemArray(dds3Basic_t *pAreaBasic, DDS3_AREABASIC_ITEMTYPE itemType) {
  void *workdata;

  workdata = pAreaBasic->workdata;
  return *((dds3BasicArrayHandle_t *)&workdata[1].klass->_1.byval_arg.data + itemType);
}

// 0x22f0540
dds3BasicArrayHandle_t *dds3AreaBasicArrangeGetItemArray(dds3Basic_t *pAreaBasic, DDS3_AREABASIC_ITEMTYPE itemType, void *checkFunc, dds3Basic_t *pBasic) {
  dds3BasicArrayHandle_t *v8;
  dds3BasicArrayHandle_t *v9;
  void *workdata;
  dds3Basic_t *data;
  dds3BasicArrayHandle_t *BasicArrayHandle;
  dds3BasicArrayHandle_t *hndl;

  hndl = 0;
  data = 0;
  BasicArrayHandle = 0;
  v8 = Allocate(dds3BasicArrayHandle_t);
  _ctor(v8, 0);
  v9 = Allocate(dds3BasicArrayHandle_t);
  _ctor(v9, 0);
  workdata = pAreaBasic->workdata;
  if (!workdata)
    goto LABEL_11;
  goto LABEL_9;
  if (!workdata)
LABEL_9:
LABEL_11:
  hndl = *((dds3BasicArrayHandle_t *)&workdata[1].klass->_1.byval_arg.data + itemType);
  if (!dds3GetBasicArrayCount(hndl))
    return 0;
  BasicArrayHandle = dds3GetBasicArrayHandle(0);
  dds3SetFirstBasicArray(hndl);
  if (checkFunc)
  {
    do
    {
      while (1)
      {
        data = dds3GetBasicArray(hndl);
        if (((checkFunc->invoke_impl)(checkFunc->method_code, data, checkFunc->method) & 1) != 0)
        {
          dds3AddBasicArray(BasicArrayHandle, 1);
          dds3SetBasicArray(BasicArrayHandle, data);
        }
        if (!dds3SetNextBasicArray(hndl))
          goto LABEL_35;
      }
    }
    while (dds3SetNextBasicArray(hndl));
  }
  else
  {
    do
    {
      data = dds3GetBasicArray(hndl);
      dds3AddBasicArray(BasicArrayHandle, 1);
      dds3SetBasicArray(BasicArrayHandle, data);
    }
    while (dds3SetNextBasicArray(hndl));
  }
LABEL_35:
  if (dds3GetBasicArrayCount(BasicArrayHandle))
    return BasicArrayHandle;
  dds3FreeBasicArrayHandle(BasicArrayHandle);
  return 0;
}

// 0x22f0880
dds3Basic_t *dds3AreaBasicGetFastArea(void) {
  dds3BasicArrayHandle_t *v1;
  dds3Basic_t *BasicArray;
  dds3Basic_t *pBasic;
  dds3BasicArrayHandle_t *hndl;

  v1 = Allocate(dds3BasicArrayHandle_t);
  _ctor(v1, 0);
  pBasic = dds3GetControlScene();
  hndl = dds3SceneBasicGetList(pBasic, 2u);
  if (!hndl)
    return 0;
  if (!dds3GetBasicArrayCount(hndl))
    return 0;
  dds3SetFirstBasicArray(hndl);
  BasicArray = dds3GetBasicArray(hndl);
  dds3FreeBasicArrayHandle(hndl);
  return BasicArray;
}
