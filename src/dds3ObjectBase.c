#include "types.h"
#include "MODELTYPE.h"
#include "basic.h"
#include "dds3.h"
#include "dds3areabasic.h"
#include "dds3basic.h"
#include "dds3cameraobjectbasic.h"
#include "dds3effectobjectbasic.h"
#include "dds3eventobjectbasic.h"
#include "dds3kerneldraw.h"
#include "dds3lightobjectbasic.h"
#include "dds3moverbasic.h"
#include "dds3objectbase.h"
#include "dds3scenebasic.h"
#include "dds3worldbasic.h"
#include "evt.h"
#include "mdl.h"
#include "sdf3d.h"
#include "sdf_vu0.h"
#include "sdfmodel.h"
#include "sdfmotion.h"

typedef struct dds3BasicArrayHandle_t dds3BasicArrayHandle_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ObjectBaseControlWorkData_t dds3ObjectBaseControlWorkData_t;
typedef struct dds3PathBasicControl_t dds3PathBasicControl_t;
typedef struct sdfModelOt_t sdfModelOt_t;
typedef struct sdfModelRootNode_t sdfModelRootNode_t;

// 0x23011a0
u32 BasicTypeToItemType(BASIC_TYPE type) {
  s32 v2;
  u32 v3;

  if ((u32)(type - 13) >= 0xFFFFFFFD)
    v2 = 3;
  else
    v2 = 0;
  if (type == 3)
    v3 = 1;
  else
    v3 = v2;
  if (type == 2)
    return 4;
  else
    return v3;
}

// 0x22fae30
dds3ObjectBaseControlWorkData_t *dds3ObjectBaseInitControlWorkData(dds3Basic_t *pObjectBasic) {
  dds3ObjectBaseControlWorkData_t *v3;
  dds3BasicArrayHandle_t *BasicArrayHandle;
  dds3Basic_t *pBasic;
  dds3Basic_t *v10;
  s32 *sdwnodeidx;
  __int128 v12;

  v3 = (dds3ObjectBaseControlWorkData_t *)Allocate(dds3ObjectBaseControlWorkData_t);
  _ctor(v3);
  Clear(v3);
  v3->modelType = 3;
  BasicArrayHandle = dds3GetBasicArrayHandle(0);
  v3->hEventBasicArray = BasicArrayHandle;
  pBasic = v3->pBasic;
  v10 = pObjectBasic;
  pBasic[0] = v10;
  sdwnodeidx = v3->sdwnodeidx;
  *(u64 *)&v12 = -1;
  *((u64 *)&v12 + 1) = -1;
  *(_OWORD *)sdwnodeidx = v12;
  *(_OWORD *)&sdwnodeidx[4] = v12;
  *(_OWORD *)&sdwnodeidx[8] = v12;
  *(_OWORD *)&sdwnodeidx[12] = v12;
  *(_OWORD *)&sdwnodeidx[16] = v12;
  *(_OWORD *)&sdwnodeidx[20] = v12;
  v3->kubinodeidx = -1;
  return v3;
}

// 0x22fb060
void dds3ObjectBaseFreeControlWorkData(dds3ObjectBaseControlWorkData_t *pControl) {
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;
  dds3Basic_t *v4;
  dds3Basic_t *v5;
  dds3ObjectBaseControlWorkData_t *v7;
  dds3Basic_t *v8;
  dds3Basic_t *pAreaBasic;

  v8 = pControl->pBasic[0];
  if (v8 && (BaseControlWorkData = dds3GetBaseControlWorkData(v8)) != 0)
  {
    pAreaBasic = BaseControlWorkData->pBasic[4];
    if (pAreaBasic)
    {
      dds3AreaBasicReleaseItem(pAreaBasic, v8);
    }
  }
  else
  {
    pAreaBasic = 0;
  }
  v4 = pControl->pBasic[1];
  if (v4)
  {
    dds3SceneBasicDelete(v4);
  }
  v5 = pControl->pBasic[2];
  if (v5)
  {
    dds3SceneBasicDelete(v5);
  }
  dds3ObjectBaseFreeModelHandle(v8);
  v7 = pControl;
  dds3FreeBasicArrayHandle(&v7->hEventBasicArray);
}

// 0x22faf40
void dds3ObjectBaseOnFlag(dds3Basic_t *pObjectBasic, u32 flag) {
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;

  BaseControlWorkData = dds3GetBaseControlWorkData(pObjectBasic);
  BaseControlWorkData->flag |= flag;
}

// 0x2301b60
void dds3ObjectBaseOffFlag(dds3Basic_t *pObjectBasic, u32 flag) {
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;

  if (pObjectBasic)
  {
    BaseControlWorkData = dds3GetBaseControlWorkData(pObjectBasic);
    BaseControlWorkData->flag &= ~flag;
  }
}

// 0x22fbf80
bool dds3ObjectBaseCheckFlag(dds3Basic_t *pObjectBasic, DDS3_OBJECTBASE_FLAG flag) {
  return (dds3GetBaseControlWorkData(pObjectBasic)->flag & flag) != 0;
}

// 0x2301ba0
void *dds3ObjectBaseSetUserValue(dds3Basic_t *pObjectBasic, void *pUserValue) {
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;
  Il2CppObject *v7;

  BaseControlWorkData = dds3GetBaseControlWorkData(pObjectBasic);
  v7 = dds3GetBaseControlWorkData(pObjectBasic)->pUserValue;
  BaseControlWorkData->pUserValue = pUserValue;
  return v7;
}

// 0x2301bf0
void *dds3ObjectBaseGetUserValue(dds3Basic_t *pObjectBasic) {
  return dds3GetBaseControlWorkData(pObjectBasic)->pUserValue;
}

// 0x2301c10
dds3Basic_t *dds3ObjectBaseSetControlBasic(dds3Basic_t *pObjectBasic, dds3Basic_t *pItemBasic) {
  dds3Basic_t *result;
  s32 v6;
  u32 v8;
  dds3Basic_t *v9;
  dds3Basic_t *v10;

  result = pItemBasic;
  if (pItemBasic)
  {
    v6 = GETBASICTYPEL(result);
    if (v6 == 2)
    {
      v8 = 4;
      v9 = pObjectBasic;
      v10 = pItemBasic;
    }
    else if (v6 == 3)
    {
      v8 = 1;
      v9 = pObjectBasic;
      v10 = pItemBasic;
    }
    else
    {
      if ((u32)(v6 - 13) >= 0xFFFFFFFD)
        v8 = 3;
      else
        v8 = 0;
      v9 = pObjectBasic;
      v10 = pItemBasic;
    }
    return dds3ObjectBaseSetControlBasicType(v9, v10, v8);
  }
  return result;
}

// 0x22fdf80
dds3Basic_t *dds3ObjectBaseSetControlBasicType(dds3Basic_t *pObjectBasic, dds3Basic_t *pItemBasic, u32 itemType) {
  dds3ObjectBaseControlWorkData_t *v7;
  dds3Basic_t *v8;
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;
  dds3Basic_t *pBasic;
  dds3Basic_t *v12;
  Il2CppClass **v13;

  if (pObjectBasic && (v7 = dds3GetBaseControlWorkData(pObjectBasic)) != 0)
  {
    v8 = v7->pBasic[itemType];
    BaseControlWorkData = dds3GetBaseControlWorkData(pObjectBasic);
    if (!BaseControlWorkData)
      return 0;
  }
  else
  {
    v8 = 0;
    BaseControlWorkData = dds3GetBaseControlWorkData(pObjectBasic);
    if (!BaseControlWorkData)
      return 0;
  }
  pBasic = BaseControlWorkData->pBasic;
  v12 = pItemBasic;
  v13 = &pBasic->obj.klass + itemType;
  v13[4] = v12;
  return v8;
}

// 0x23014e0
dds3Basic_t *dds3ObjectBaseGetControlBasic(dds3Basic_t *pObjectBasic, u32 itemType) {
  dds3Basic_t *result;

  if (!pObjectBasic)
    return 0;
  result = (dds3Basic_t *)dds3GetBaseControlWorkData(pObjectBasic);
  if (result)
    return *((dds3Basic_t *)&result->workdata[2].klass + itemType);
  return result;
}

// 0x2301cb0
dds3BasicArrayHandle_t *dds3ObjectBaseGetEventArray(dds3Basic_t *pObjectBasic) {
  return dds3GetBaseControlWorkData(pObjectBasic)->hEventBasicArray;
}

// 0x22fb540
void *dds3ObjectBaseGetModelHandle(dds3Basic_t *pObjectBasic) {
  return dds3GetBaseControlWorkData(pObjectBasic)->pModel;
}

// 0x2301520
void dds3ObjectBaseFreeModelHandle(dds3Basic_t *pObjectBasic) {
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;
  Il2CppObject **p_pModel;
  dds3ModelHandle_t *pModel;
  s32 modelType;
  dds3ObjectBaseControlWorkData_t *v7;
  s64 v8;
  void *workdata;
  evtUnitHandle_t *v11;
  Project_Basic_dds3Basic_t_WORK_c *klass;
  s64 naturalAligment;

  BaseControlWorkData = dds3GetBaseControlWorkData(pObjectBasic);
  p_pModel = &BaseControlWorkData->pModel;
  pModel = BaseControlWorkData->pModel;
  if (pModel)
  {
    modelType = BaseControlWorkData->modelType;
    v7 = BaseControlWorkData;
    if (modelType == 1)
    {
      if (pModel->klass->_2.naturalAligment < (u32)naturalAligment || pModel->klass->_2.typeHierarchy[naturalAligment - 1] != sdfModelRootNode_t)
      {
        goto LABEL_22;
      }
      sdfModelRootFree(BaseControlWorkData->pModel);
      sdfMotionCtrlrFree(v7->pMot);
    }
    else if (!modelType)
    {
      if (pModel->klass->_2.naturalAligment >= (u32)v8 && (dds3ModelHandle_t *)pModel->klass->_2.typeHierarchy[v8 - 1] == dds3ModelHandle_t)
      {
        Free(pModel);
        workdata = pObjectBasic->workdata;
        klass = workdata[2].klass;
        v11 = &workdata[2];
        if (klass)
        {
          evtDeleteUnitHandle(v11);
          v11 = 0;
        }
        goto LABEL_21;
      }
LABEL_22:
    }
LABEL_21:
    v7->pModel = 0;
    v7->modelType = 3;
  }
}

// 0x2301cd0
void dds3ObjectBaseMakeUnit(dds3Basic_t *pObjectBasic, MODELTYPE major, s32 minor) {
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;
  dds3ModelHandle_t *pModel;
  dds3ModelHandle_t *v9;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  dds3Basic_t *v17;
  void *workdata;
  evtUnitHandle_t *v20;
  Project_Basic_dds3Basic_t_WORK_c *klass;
  evtUnitHandle_t *v22;
  dds3Basic_t *pObjectBasica;
  sdfVector4_t v25;

  pObjectBasica = pObjectBasic;
  BaseControlWorkData = dds3GetBaseControlWorkData(pObjectBasica);
  pModel = BaseControlWorkData->pModel;
  if (pModel)
  {
    Free(pModel);
  }
  v9 = mdlLoad(major, minor);
  BaseControlWorkData->kubinodeidx = sdfModelGetNodeIndexByName(v9->modelRoot, "Bip01 Head");
  mdlGetScale(v9);
  p_x = &vf00.x;
  x = p_x[4];
  y = p_x[5];
  z = p_x[6];
  w = p_x[7];
  v25.x = x;
  v25.y = y;
  v25.z = z;
  v25.w = w;
  dds3SetSclPoseSet(pObjectBasica, v25);
  dds3GetRotPoseSetMCR(pObjectBasica);
  mdlSetRotate(v9);
  dds3GetPosPoseSetMCR(pObjectBasica);
  mdlSetPosition(v9);
  BaseControlWorkData->modelType = 0;
  BaseControlWorkData->pModel = v9;
  v17 = pObjectBasica;
  BaseControlWorkData->cam_len = 0.0;
  workdata = v17->workdata;
  klass = workdata[2].klass;
  v20 = &workdata[2];
  if (!klass)
  {
    v22 = evtCreateUnitHandle(pObjectBasica, v9);
    v20 = v22;
  }
}

// 0x2301fe0
void dds3ObjectBaseMakeMatter(dds3Basic_t *pObjectBasic) {
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;
  dds3ObjectBaseControlWorkData_t *v5;
  dds3Basic_t *v6;
  sdfModelDef_t *workdata;
  s64 naturalAligment;
  sdfModelRootNode_t *v10;
  s64 v11;
  sdfMotionPlayBook_t *v12;
  sdfMotionCtrlr_t *v13;
  _OWORD *p_x;
  __int128 v18;
  __int128 v19;
  __int128 v20;
  sdfMotionCtrlr_t *p_pMot;

  BaseControlWorkData = dds3GetBaseControlWorkData(pObjectBasic);
  if (!pObjectBasic || (v5 = dds3GetBaseControlWorkData(pObjectBasic)) == 0)
  {
    v6 = 0;
LABEL_8:
    workdata = v6->workdata;
    if (!workdata)
      goto LABEL_15;
    goto LABEL_13;
  }
  v6 = v5->pBasic[3];
  goto LABEL_8;
LABEL_13:
  if (LOBYTE(workdata[9].extraData) < (u32)naturalAligment || *((Project_Basic_dds3ModelBasicWorkData_t_c **)(workdata)[6].monitor + naturalAligment - 1) != Project_Basic_dds3ModelBasicWorkData_t)
  {
    goto LABEL_31;
  }
LABEL_15:
  v10 = Make(workdata[3], workdata[3]->prefab, 0);
  SetAutoHide(v10->modelObj, 1, 0);
  v10->modelObj->isBg = 1;
  workdata = v6->workdata;
  if (workdata)
  {
    if (LOBYTE(workdata[9].extraData) < (u32)v11 || *((Project_Basic_dds3ModelBasicWorkData_t_c **)(workdata)[6].monitor + v11 - 1) != Project_Basic_dds3ModelBasicWorkData_t)
    {
LABEL_31:
    }
  }
  v12 = workdata[4];
  if (v12)
  {
    v13 = sdfMotionCtrlrNew(v10, v12);
    sdfMotionChange(v13, 0, 1);
    goto LABEL_22;
  }
  else
  {
    v13 = 0;
LABEL_22:
    dds3GetTMPoseSet(pObjectBasic);
    goto LABEL_23;
  }
  dds3GetTMPoseSet(pObjectBasic);
LABEL_23:
  p_x = &vf00.x;
  v18 = p_x[4];
  v19 = p_x[5];
  v20 = p_x[6];
  *(_OWORD *)&v10->tm.m03 = p_x[7];
  *(_OWORD *)&v10->tm.m01 = v19;
  *(_OWORD *)&v10->tm.m02 = v20;
  *(_OWORD *)&v10->tm.m00 = v18;
  BaseControlWorkData->modelType = 1;
  BaseControlWorkData->pModel = v10;
  BaseControlWorkData->pMot = v13;
  p_pMot = &BaseControlWorkData->pMot;
  *((u32 *)p_pMot + 2) = 0;
  *(sdfMotionCtrlr_t *)((char *)p_pMot + 12) = (sdfMotionCtrlr_t *)1065353216;
}

// 0x23022e0
void dds3ObjectBaseMatterAnimeSpeed(dds3Basic_t *pObjectBasic, s32 mode) {
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;
  f32 v5;

  BaseControlWorkData = dds3GetBaseControlWorkData(pObjectBasic);
  if ((u32)mode <= 6)
  {
    v5 = flt_3E65F0C[mode];
    BaseControlWorkData->MotMode = mode;
    BaseControlWorkData->MotSpeed = v5;
  }
}

// 0x2302320
bool dds3ObjectBaseRegistArea(dds3Basic_t *pObjectBasic) {
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;
  dds3Basic_t *pAreaBasic;

  if (!pObjectBasic)
    goto LABEL_10;
  BaseControlWorkData = dds3GetBaseControlWorkData(pObjectBasic);
  if (!BaseControlWorkData)
    return (char)BaseControlWorkData;
  pAreaBasic = BaseControlWorkData->pBasic[4];
  if (pAreaBasic)
  {
    dds3AreaBasicRegistItem(pAreaBasic, pObjectBasic);
    LOBYTE(BaseControlWorkData) = 1;
  }
  else
  {
LABEL_10:
    LOBYTE(BaseControlWorkData) = 0;
  }
  return (char)BaseControlWorkData;
}

// 0x23023d0
f32 dds3ObjectBaseCalc_Cam_Model_Leng(dds3Basic_t *pObjectBasic, sdfModelRootNode_t *model_root) {
  f32 *static_fields;
  dds3PoseSet_t *poseset;
  f32 v7;
  f32 v8;
  f32 v9;

  poseset = pObjectBasic->poseset;
  v7 = static_fields[42] - poseset->pos.x;
  v8 = static_fields[43] - (f32)(poseset->pos.y + -150.0);
  v9 = static_fields[44] - poseset->pos.z;
  return sqrtf((f32)((f32)(v7 * v7) + (f32)(v8 * v8)) + (f32)(v9 * v9));
}

// 0x22fba00
void dds3ObjectBaseModelLinkOt(sdfModelOt_t *pModelOt, dds3Basic_t *pObjectBasic) {
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;
  long f64 v7;
  Il2CppObject *pModel;
  s32 modelType;
  s64 v10;
  long f64 v12;
  sdf3DLightParallelPacket_t *v13;
  long f64 v16;
  void *HcameraObject_local;
  sdf3DScreenParam_t *HScreenParam_local;
  sdfMatrix4_t *p_HCameraTM;
  s64 naturalAligment;
  u32 color;
  sdfMotionCtrlr_t *pMot;
  f32 *p_MotSpeed;
  s32 kubinodeidx;
  f32 v29;
  long f64 v30;
  f32 v31;
  f32 v33;
  f32 MotSpeed;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  void *klass;
  s32 v40;
  s32 v41;
  s32 v42;

  BaseControlWorkData = dds3GetBaseControlWorkData(pObjectBasic);
  if ((dds3GetBaseControlWorkData(pObjectBasic)->flag & 1) != 0)
    return;
  pModel = BaseControlWorkData->pModel;
  if (!pModel)
    return;
  modelType = BaseControlWorkData->modelType;
  if (modelType == 1)
  {
    if (pModel->klass->_2.naturalAligment >= (u32)naturalAligment && (sdfModelRootNode_t *)pModel->klass->_2.typeHierarchy[naturalAligment - 1] == sdfModelRootNode_t)
    {
      color = pObjectBasic->color;
      if (HIBYTE(color))
      {
        pMot = BaseControlWorkData->pMot;
        if (pMot)
        {
          switch (BaseControlWorkData->MotMode)
          {
            case 0:
              p_MotSpeed = &BaseControlWorkData->MotSpeed;
              goto LABEL_61;
            case 1:
              MotSpeed = BaseControlWorkData->MotSpeed;
              p_MotSpeed = &BaseControlWorkData->MotSpeed;
              v35 = MotSpeed;
              v36 = 0.05;
              goto LABEL_60;
            case 2:
              v37 = BaseControlWorkData->MotSpeed;
              p_MotSpeed = &BaseControlWorkData->MotSpeed;
              v35 = v37;
              v36 = 0.025;
LABEL_60:
              v33 = v35 + v36;
              *p_MotSpeed = v33;
              if (v33 <= 1.0)
                goto LABEL_65;
LABEL_61:
              v33 = 1.0;
              *p_MotSpeed = 1.0;
              goto LABEL_66;
            case 3:
              goto LABEL_63;
            case 4:
              v33 = BaseControlWorkData->MotSpeed + -0.05;
              BaseControlWorkData->MotSpeed = v33;
              if (v33 < 0.0)
                goto LABEL_63;
              goto LABEL_65;
            case 5:
              v33 = BaseControlWorkData->MotSpeed + -0.02;
              BaseControlWorkData->MotSpeed = v33;
              if (v33 >= 0.0)
                goto LABEL_65;
LABEL_63:
              BaseControlWorkData->MotSpeed = 0.0;
              break;
            default:
              v33 = BaseControlWorkData->MotSpeed;
LABEL_65:
              if (v33 > 0.0)
              {
LABEL_66:
                pMot->speed = v33;
                sdfMotionNext(pMot);
                color = pObjectBasic->color;
              }
              break;
          }
        }
        *(u64 *)&v7 = 0x4300000043000000LL;
        v38 = (loc_2314DE0)(color, 0, v7);
        klass = pModel[13].klass;
        *(f32 *)&pModel[2].klass = v38;
        HIDWORD(pModel[2].klass) = v40;
        LODWORD(pModel[2].monitor) = v41;
        HIDWORD(pModel[2].monitor) = v42;
        SetActive(klass, 1, 0);
        sdfModelLinkOt(pModelOt, pModel);
      }
      return;
    }
LABEL_70:
  }
  if (modelType)
    return;
  if (pModel->klass->_2.naturalAligment < (u32)v10 || pModel->klass->_2.typeHierarchy[v10 - 1] != dds3ModelHandle_t)
  {
    goto LABEL_70;
  }
  if ((dds3GetBaseControlWorkData(pObjectBasic)->flag & 0x800) != 0 && (dds3ObjectBaseSetControlBasicCamLen(pObjectBasic), BaseControlWorkData->cam_len < 100.0) || (dds3GetBaseControlWorkData(pObjectBasic)->flag & 0x100000) != 0)
  {
    mdlLink_NoDraw(pModel, pModelOt);
  }
  else
  {
    v13 = *(sdf3DLightParallelPacket_t *)(*(u64 *)(sub_83F0(pObjectBasic->workdata, Project_Basic_dds3UnitObjectBasicWorkData_t, v12) + 32) + 328);
    if (v13)
    {
      mdlSetLight(pModel, v13);
      if ((dds3GetBaseControlWorkData(pObjectBasic)->flag & 0x2000) == 0)
      {
LABEL_16:
        if (ModelOt[13] == pModelOt)
        {
          HScreenParam_local = HScreenParam;
          HcameraObject_local = HcameraObject;
          p_HCameraTM = &HCameraTM;
        }
        else
        {
          HScreenParam_local = ScreenParam;
          HcameraObject_local = cameraObject;
          p_HCameraTM = &CameraTM;
        }
        sdf3SetCamera(HScreenParam_local, p_HCameraTM, HcameraObject_local);
        if (mdlGetMajorNum(pModel) == 2)
        {
          if (mdlGetMinorNum(pModel) == 13)
          {
            pModelOt = ModelOt[8];
          }
        }
        Link(pModel, pModelOt);
        return;
      }
    }
    else
    {
      mdlSetLight(pModel, 0);
      if ((dds3GetBaseControlWorkData(pObjectBasic)->flag & 0x2000) == 0)
        goto LABEL_16;
    }
    kubinodeidx = BaseControlWorkData->kubinodeidx;
    v29 = *(f32 *)(sub_83F0(pObjectBasic->workdata, Project_Basic_dds3UnitObjectBasicWorkData_t, v16) + 72);
    v31 = *(f32 *)(sub_83F0(pObjectBasic->workdata, Project_Basic_dds3UnitObjectBasicWorkData_t, v30) + 84);
    mdlLink_Kubi(pModel, pModelOt, kubinodeidx, v29, v31);
  }
}

// 0x22fc360
void dds3ObjectBaseCreateMover(dds3Basic_t *pObjectBasic) {
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;
  dds3Basic_t *v4;
  s32 v5;
  u32 v7;
  dds3Basic_t *pItemBasic;

  if (!pObjectBasic || (BaseControlWorkData = dds3GetBaseControlWorkData(pObjectBasic)) == 0 || !BaseControlWorkData->pBasic[1])
  {
    v4 = dds3MoverBasicAdd(pObjectBasic);
    pItemBasic = v4;
    if (v4)
    {
      v5 = GETBASICTYPEL(v4);
      if (v5 == 2)
      {
        v7 = 4;
      }
      else if (v5 == 3)
      {
        v7 = 1;
      }
      else if ((u32)(v5 - 13) >= 0xFFFFFFFD)
      {
        v7 = 3;
      }
      else
      {
        v7 = 0;
      }
      dds3ObjectBaseSetControlBasicType(pObjectBasic, pItemBasic, v7);
    }
  }
}

// 0x23025c0
bool dds3ObjectBaseSetPadControl(dds3Basic_t *pObjectBasic, dds3MoverBasicObjFunc_t pFuncPadControl) {
  return dds3ObjectBaseSetPrimaryControl(pObjectBasic, pFuncPadControl);
}

// 0x23025d0
bool dds3ObjectBaseSetPrimaryControl(dds3Basic_t *basic, dds3MoverBasicObjFunc_t func) {
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;
  dds3Basic_t *v6;
  void *workdata;

  if (!basic)
    goto LABEL_15;
  BaseControlWorkData = dds3GetBaseControlWorkData(basic);
  if (!BaseControlWorkData)
    return (char)BaseControlWorkData;
  v6 = BaseControlWorkData->pBasic[1];
  if (v6)
  {
    workdata = v6->workdata;
    LOBYTE(BaseControlWorkData) = 1;
  }
  else
  {
LABEL_15:
    LOBYTE(BaseControlWorkData) = 0;
  }
  return (char)BaseControlWorkData;
}

// 0x23026f0
void dds3ObjectBaseMakePath(dds3Basic_t *pObjectBasic, dds3Basic_t *pPathBasic) {
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;
  dds3Basic_t *v6;
  dds3Basic_t *v8;
  void *workdata;

  if (pObjectBasic && (BaseControlWorkData = dds3GetBaseControlWorkData(pObjectBasic)) != 0)
  {
    v6 = BaseControlWorkData->pBasic[1];
    v8 = pPathBasic;
    goto LABEL_9;
  }
  else
  {
    v6 = 0;
    v8 = pPathBasic;
    goto LABEL_9;
  }
LABEL_9:
  workdata = v6->workdata;
  dds3MoverBasicMakePath(pObjectBasic);
}

// 0x2302810
void dds3ObjectBaseFreePath(dds3Basic_t *pObjectBasic) {
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;
  dds3Basic_t *v4;
  dds3Basic_t *v6;

  if (!pObjectBasic || (BaseControlWorkData = dds3GetBaseControlWorkData(pObjectBasic)) == 0)
  {
    v4 = 0;
LABEL_9:
    v6 = v4;
    goto LABEL_7;
  }
  v4 = BaseControlWorkData->pBasic[1];
  goto LABEL_9;
LABEL_7:
  dds3MoverBasicFreePath(v6);
}

// 0x23028b0
dds3PathBasicControl_t *dds3ObjectBaseGetPathControl(dds3Basic_t *pObjectBasic) {
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;
  dds3Basic_t *v4;
  dds3PathBasicControl_t *workdata;
  s64 naturalAligment;

  if (!pObjectBasic || (BaseControlWorkData = dds3GetBaseControlWorkData(pObjectBasic)) == 0)
  {
    v4 = 0;
LABEL_8:
    goto LABEL_9;
  }
  v4 = BaseControlWorkData->pBasic[1];
  goto LABEL_8;
LABEL_9:
  workdata = (dds3PathBasicControl_t *)v4->workdata;
  if (!workdata)
    return workdata[3];
  LOBYTE(workdata[4].pFovy) < (u32)naturalAligment || *((Project_Basic_dds3MoverBasicWorkData_t_c **)(workdata)[3].monitor + naturalAligment - 1) != Project_Basic_dds3MoverBasicWorkData_t;
  return workdata[3];
}

// 0x2301860
dds3ObjectBaseControlWorkData_t *dds3GetBaseControlWorkData(dds3Basic_t *pObjectBasic) {
  dds3Basic_t *v3;
  dds3Basic_t *v4;
  dds3ObjectBaseControlWorkData_t *workdata;
  dds3Basic_t *v6;
  dds3Basic_t *v7;
  dds3Basic_t *v8;
  dds3Basic_t *v9;
  s64 naturalAligment;
  s64 v12;

  switch (GETBASICTYPEL(pObjectBasic))
  {
    case 4:
      v3 = pObjectBasic;
      return dds3CameraObjectBasicGetControlWorkData(v3);
    case 5:
      v4 = pObjectBasic;
      workdata = (dds3ObjectBaseControlWorkData_t *)v4->workdata;
      if (!workdata)
        return workdata[5];
LABEL_27:
      if (LOBYTE(workdata[2].sdwid) >= (u32)naturalAligment && *(Project_Basic_dds3UnitObjectBasicWorkData_t_c **)(*(u64 *)&workdata[1].sdwid + 8 * naturalAligment - 8) == Project_Basic_dds3UnitObjectBasicWorkData_t)
      {
        return workdata[5];
      }
LABEL_35:
      workdata = (dds3ObjectBaseControlWorkData_t *)v4->workdata;
      if (!workdata)
        return workdata[5];
      goto LABEL_27;
    case 6:
      v6 = pObjectBasic;
      workdata = (dds3ObjectBaseControlWorkData_t *)v6->workdata;
      if (!workdata)
        return workdata[2];
      if (LOBYTE(workdata[2].sdwid) < (u32)v12 || *(Project_Basic_dds3MatterObjectBasicWorkData_t_c **)(*(u64 *)&workdata[1].sdwid + 8 * v12 - 8) != Project_Basic_dds3MatterObjectBasicWorkData_t)
      {
        goto LABEL_35;
      }
      return workdata[2];
    case 7:
      v7 = pObjectBasic;
      return dds3EffectObjectBasicGetControlWorkData(v7);
    case 8:
      v8 = pObjectBasic;
      return dds3EventObjectBasicGetControlWorkData(v8);
    case 9:
      v9 = pObjectBasic;
      return dds3LightObjectBasicGetControlWorkData(v9);
    default:
      return 0;
  }
}

// 0x2302480
void dds3ObjectBaseSetControlBasicCamLen(dds3Basic_t *pObjectBasic) {
  dds3ModelHandle_t *v3;
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;
  Il2CppObject *pModel;
  f32 *static_fields;
  dds3PoseSet_t *poseset;
  f32 v11;
  f32 v12;
  f32 v13;
  dds3Basic_t *pObjectBasica;

  pObjectBasica = pObjectBasic;
  v3 = Allocate(dds3ModelHandle_t);
  _ctor(v3, 0);
  BaseControlWorkData = dds3GetBaseControlWorkData(pObjectBasica);
  pModel = BaseControlWorkData->pModel;
  poseset = pObjectBasic->poseset;
  v11 = static_fields[42] - poseset->pos.x;
  v12 = static_fields[43] - (f32)(poseset->pos.y + -150.0);
  v13 = static_fields[44] - poseset->pos.z;
  BaseControlWorkData->cam_len = sqrtf((f32)((f32)(v11 * v11) + (f32)(v12 * v12)) + (f32)(v13 * v13));
}

// 0x2302a30
f32 dds3ObjectBaseGetControlBasicCamLen(dds3Basic_t *pObjectBasic) {
  dds3Basic_t *pObjectBasica;

  pObjectBasica = pObjectBasic;
  return dds3GetBaseControlWorkData(pObjectBasica)->cam_len;
}
