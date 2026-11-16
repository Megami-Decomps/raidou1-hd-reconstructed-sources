#include "types.h"
#include "PMD_FLAG.h"
#include "dat.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3objectbase.h"
#include "dds3pathbasic.h"
#include "dds3unitobjectbasic.h"
#include "event.h"
#include "evt.h"
#include "evtpmv.h"
#include "evtviewer.h"
#include "file.h"
#include "itf.h"
#include "kernel.h"
#include "localize.h"
#include "mdl.h"
#include "scrcommand.h"
#include "sdf3d.h"
#include "sdfmem.h"
#include "sdfsound.h"
#include "sdfsystem.h"

typedef struct DepthOfFieldSetting DepthOfFieldSetting;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3Effect_Blur_t dds3Effect_Blur_t;
typedef struct dds3Effect_DistortionBlurParam_t dds3Effect_DistortionBlurParam_t;
typedef struct dds3Effect_Filter_t dds3Effect_Filter_t;
typedef struct dds3Effect_ParallelBlur_t dds3Effect_ParallelBlur_t;
typedef struct dds3Effect_PartialMultiBlurParam_t dds3Effect_PartialMultiBlurParam_t;
typedef struct dds3Effect_PartialMultiFilterParam_t dds3Effect_PartialMultiFilterParam_t;
typedef struct dds3Effect_RippleBlurParam_t dds3Effect_RippleBlurParam_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct pmdProcessWork_t pmdProcessWork_t;
typedef struct pmdSceneFogTable_t pmdSceneFogTable_t;
typedef struct pmdSceneLightTable_t pmdSceneLightTable_t;
typedef struct pmdSeqData_t pmdSeqData_t;
typedef struct sdfIVector2_t sdfIVector2_t;

static pmdSceneLightTable_t *hsl_light0;
static dds3Effect_Blur_t *hsl_blur0;
static dds3Effect_PartialMultiBlurParam_t *hsl_mblur0;
static dds3Effect_Filter_t *hsl_filter0;
static dds3Effect_PartialMultiFilterParam_t *hsl_mfilter0;
static dds3Effect_DistortionBlurParam_t *hsl_dist0;
static dds3Effect_RippleBlurParam_t *hsl_rip0;
static dds3Effect_ParallelBlur_t *hsl_hblur0;
s32 PmvEventNo;

static bool CheckPMVLoad(dds3ProcessID_t *id);
static f32 HokanFloat(bool hokan, f32 ratio, f32 f1, f32 f2);
static s32 HokanInt(bool hokan, f32 ratio, s32 i1, s32 i2);
static u32 HokanUInt(bool hokan, f32 ratio, u32 i1, u32 i2);
static sdfVector4_t HokanVector4(bool hokan, f32 ratio, const sdfVector4_t *c1, const sdfVector4_t *c2);
static void HokanPos(bool hokan, f32 ratio, sdfIVector2_t p1, sdfIVector2_t p2, sdfIVector2_t *d);
static void HokanArea(bool hokan, f32 ratio, sdfIVector2_t *a1, sdfIVector2_t *a2, sdfIVector2_t *d);
static void HokanBlur(bool hokan, f32 ratio, dds3Effect_Blur_t *key1, dds3Effect_Blur_t *key2, dds3Effect_Blur_t *d);
static pmdProcessWork_t *InitWorkData(void);
static pmdProcessWork_t *GetWorkData1(pmdProcessWork_t *wdata, void *pm1data);

// 0x1a31040
void evtCheckLoad(pmdProcessWork_t *wdata) {
  long f64 v2;
  s32 flag;
  void *pData;
  pmdSeqData_t *Item;
  pmdSeqData_t *v8;
  s32 EventNo;
  void *v11;
  void *StageF1;
  long f64 v15;
  s64 v16;
  s64 v17;
  s64 v18;
  pmdLoadScene *v19;
  pmdLoadScene **p_loadScene;
  s32 *loadScene;
  s64 v22;
  s64 v23;
  fileHandle_t *FileHandle1;
  fileHandle_t *FileHandle2;
  fileHandle_t *v26;
  pmdPM2_t *pm2;
  s32 v28;
  fileHandle_t *FileHandle3;
  fileHandle_t *v30;
  pmdPM3_t *pm3;
  pmdSeqData_t *pm1data;
  fileHandle_t *v33;
  void *topPtr;
  pmdSeqData_t *p_fields;
  fileHandle_t *p_dofTblFileHandle;
  fileHandle_t *dofTblFileHandle;
  long f64 v40;
  fileHandle_t *v41;
  void *v42;
  void *v43;
  void *p_dofTbl;
  long f64 v46;
  void *v47;
  pmdPM1_t *pm1;
  char *v49;
  pmdLoadScene *v50;
  char *name;
  bool IsValid;
  s64 v53;
  char *v54;
  fileHandle_t *p_volumeHandle;
  fileHandle_t *volumeHandle;
  fileHandle_t *v58;
  Il2CppObject *v59;
  Il2CppObject *Component_object;
  void *transform;
  Il2CppObject *v64;
  void *p_volume;
  pmdLoadScene *v69;
  s64 v70;
  s32 v71;
  void *v72;
  pmdLoadScene *v73;
  s32 step;
  bool IsLoad;
  char *sceneName;
  void *RootGameObjects;
  il2cpp_array_size_t max_length;
  void *v80;
  s64 v81;
  Il2CppObject *v82;
  s64 v85;
  Il2CppObject *v86;
  UnityEngine_SceneManagement_Scene_o v87;
  void *Instance;
  void *model;
  s32 disableParts;
  void *v91;
  s64 v92;
  s64 v93;
  s64 *v94;
  s64 v95;
  s64 v96;
  s64 v97;
  sdfModelDef_t *pMdl;
  void *gameObject;
  s64 v100;
  s32 v102;
  UnityEngine_SceneManagement_Scene_o scene;
  s32 m_Handle;

  flag = wdata->flag;
  m_Handle = 0;
  scene.m_Handle = 0;
  if ((flag & 8) != 0)
    return;
  if ((flag & 2) != 0)
  {
    FileHandle1 = wdata->pm1->FileHandle1;
    if (!FileHandle1)
      return;
    if (!fileCheckEnd(FileHandle1))
      return;
    pm1data = wdata->pm1data;
    v33 = wdata->pm1->FileHandle1;
    topPtr = v33->topPtr;
    if (!topPtr)
    {
      pm1data->pData = 0;
      p_fields = &pm1data->fields;
    }
    fileHandleFree(wdata->pm1->FileHandle1);
    pm1 = wdata->pm1;
    pm1->FileHandle1 = 0;
    v28 = wdata->flag & 0xFFFFFFFD;
    goto LABEL_67;
  }
  if ((flag & 4) != 0)
  {
    FileHandle2 = wdata->pm2->FileHandle2;
    if (FileHandle2)
    {
      if (fileCheckEnd(FileHandle2))
      {
        Set(wdata->pm2data, wdata->pm2->FileHandle2, 0);
        v26 = wdata->pm2->FileHandle2;
        fileHandleFree(v26);
        pm2 = wdata->pm2;
        pm2->FileHandle2 = 0;
        v28 = wdata->flag & 0xFFFFFFFB;
        goto LABEL_67;
      }
    }
    return;
  }
  if ((flag & 0x10) != 0)
  {
    FileHandle3 = wdata->pm3->FileHandle3;
    if (FileHandle3)
    {
      if (fileCheckEnd(FileHandle3))
      {
        Set(wdata->pm3data, wdata->pm3->FileHandle3, 0);
        v30 = wdata->pm3->FileHandle3;
        fileHandleFree(v30);
        pm3 = wdata->pm3;
        pm3->FileHandle3 = 0;
        v28 = wdata->flag & 0xFFFFFFEF;
        goto LABEL_67;
      }
    }
    return;
  }
  if ((flag & 0x40) != 0)
  {
    p_dofTblFileHandle = &wdata->dofTblFileHandle;
    dofTblFileHandle = wdata->dofTblFileHandle;
    if (dofTblFileHandle)
    {
      if (fileCheckEnd(dofTblFileHandle))
      {
        v41 = p_dofTblFileHandle;
        v42 = v41->topPtr;
        v43 = sub_83F0(v42, EvtDofTbl, v40);
        wdata->dofTbl = v43;
        p_dofTbl = &wdata->dofTbl;
        v47 = sub_83F0(v42, EvtDofTbl, v46);
        *(p_dofTbl - 1) = 0;
        *((u32 *)p_dofTbl - 38) &= ~0x40u;
      }
    }
    return;
  }
  if ((flag & 0x80) != 0)
  {
    p_volumeHandle = &wdata->volumeHandle;
    volumeHandle = wdata->volumeHandle;
    if (volumeHandle)
    {
      if (fileCheckEnd(volumeHandle))
      {
        v58 = p_volumeHandle;
        v59 = v58->topPtr;
        Component_object = GetComponent_object_(cameraObject->_camera);
        transform = get_transform(hook, 0);
        v64 = Instantiate_object__39504352(v59, transform);
        wdata->volume = v64;
        p_volume = &wdata->volume;
        HIDWORD(Component_object[3].monitor) = op_Implicit_60988480(1, 0);
        *(p_volume - 1) = 0;
        *((u32 *)p_volume - 44) &= ~0x80u;
      }
    }
    return;
  }
  if ((flag & 0x20) == 0)
  {
    sdfMemRelease();
    pData = wdata->pm1data->pData;
    GetWorkData1(wdata, pData);
    Item = get_Item(wdata->pm2data, wdata->SeqNo, 0);
    v8 = get_Item(wdata->pm3data, wdata->SeqNo, 0);
    evtGetWorkData2and3(wdata, Item, v8);
    EventNo = wdata->EventNo;
    if (EventNo == 616)
    {
      v11 = oldEventSceneUnload("bg13_last_battle");
      un_load_scene = v11;
      EventNo = wdata->EventNo;
    }
    if (EventNo == 609 && wdata->CutNo == 2)
    {
      ScreenParam->nearClip = 12.0;
    }
    StageF1 = wdata->pm1->StageF1;
    if (!op_Inequality(StageF1, 0, 0))
      goto LABEL_176;
    v16 = sub_83F0(wdata->pm1->StageF1->infoHeader, fldFileInfoHeaderFL1_t, v15);
    v17 = *(u64 *)(v16 + 32);
    if (!v17)
      goto LABEL_176;
    v18 = v16;
    v19 = NewSpecific(pmdLoadScene, *(u32 *)(v17 + 24));
    wdata->loadScene = v19;
    p_loadScene = &wdata->loadScene;
    loadScene = wdata->loadScene;
    if (loadScene[6] >= 1)
    {
      v22 = 0;
      v23 = 8;
      do
      {
        while (1)
        {
          v49 = *(char **)(*(u64 *)(v18 + 32) + v23 * 4);
          v50 = Allocate(pmdLoadScene);
          _ctor_27155120(v50, v49, 0);
          if (v50)
            QueryInterface(v50, *(void **)(*(u64 *)loadScene + 64));
          *(u64 *)&loadScene[v23] = v50;
          name = (*(Il2CppClass **)((char *)&(*p_loadScene)->obj.klass + v23 * 4))->_1.name;
          m_Handle = GetSceneByName(name, 0).m_Handle;
          IsValid = IsValid((UnityEngine_SceneManagement_Scene_o)&m_Handle, 0);
          loadScene = *p_loadScene;
          v53 = *(s64 *)((char *)&(*p_loadScene)->obj.klass + v23 * 4);
          if (!IsValid)
            break;
          *(u32 *)(v53 + 88) = 2;
          ++v22;
          v23 += 2;
          if (v22 >= loadScene[6])
            goto LABEL_78;
        }
        v54 = *(char **)(v53 + 24);
        Load(Dependent, v54, v54);
        loadScene = *p_loadScene;
        ++v22;
        v23 += 2;
      }
      while (v22 < SLODWORD((*p_loadScene)->max_length));
    }
LABEL_78:
    v28 = wdata->flag | 0x20;
    goto LABEL_67;
  }
  if (wdata->EventNo == 616)
  {
    if (un_load_scene)
    {
      if (get_isDone(un_load_scene, 0))
      {
        un_load_scene = 0;
        sdfMemRelease();
        return;
      }
    }
  }
  v69 = wdata->loadScene;
  if (SLODWORD(v69->max_length) < 1)
    goto LABEL_167;
  v70 = 0;
  v71 = 1;
  do
  {
    v73 = v69[v70];
    step = v73->step;
    if (step == 2)
    {
      v102 = v71;
      sceneName = v73->sceneName;
      scene.m_Handle = GetSceneByName(sceneName, 0).m_Handle;
      RootGameObjects = GetRootGameObjects((UnityEngine_SceneManagement_Scene_o)&scene, 0);
      max_length = RootGameObjects->max_length;
      v80 = RootGameObjects;
      if ((s32)max_length >= 1)
      {
        v81 = 0;
        while (1)
        {
          v82 = GetComponent_object_(v80[v81]);
          if (op_Inequality(v82, 0, 0))
            break;
          max_length = v80->max_length;
          if (++v81 >= (s32)max_length)
            goto LABEL_144;
        }
        v73->bg = (void *)v82;
        max_length = v80->max_length;
      }
LABEL_144:
      if ((s32)max_length >= 1)
      {
        v85 = 0;
        while (1)
        {
          v86 = GetComponent_object_(v80[v85]);
          if (op_Inequality(v86, 0, 0))
            break;
          if (++v85 >= SLODWORD(v80->max_length))
            goto LABEL_152;
        }
        v73->bgCtrl = (void *)v86;
      }
LABEL_152:
      v87.m_Handle = scene.m_Handle;
      Instance = GetInstance(v87, 0);
      v73->model = Instance;
      model = v73->model;
      if (op_Inequality(model, 0, 0))
      {
        disableParts = v73->disableParts;
        if ((disableParts & 0x80000000) == 0)
          SetParts(v73->model, disableParts, 0);
      }
      v91 = get_Instance(0);
      if (op_Inequality(v91, 0, 0))
      {
        v72 = get_Instance(0);
        SetPos(v72, v73->pos.x, v73->pos.y, v73->pos.z);
      }
      Disp(v73, 0, 0);
      v71 = v102;
      goto LABEL_110;
    }
    if (step != 1)
    {
      if (step)
        goto LABEL_111;
      IsLoad = IsLoad(_Ctrl_k__BackingField, v73->assetBundleName, 0);
      v71 = 0;
      if (IsLoad)
        goto LABEL_110;
      goto LABEL_111;
    }
    m_Handle = GetScene(_Ctrl_k__BackingField, v73->sceneName, 0).m_Handle;
    if (get_isLoaded((UnityEngine_SceneManagement_Scene_o)&m_Handle, 0))
    {
      Unload(Dependent, v73->assetBundleName, 0);
      v71 = 0;
LABEL_110:
      ++v73->step;
      goto LABEL_111;
    }
    v71 = 0;
LABEL_111:
    ++v70;
  }
  while (v70 < SLODWORD(v69->max_length));
  if ((v71 & 1) != 0)
  {
LABEL_167:
    v92 = *(u64 *)(sub_83F0(wdata->pm1->StageF1->infoHeader, fldFileInfoHeaderFL1_t, v2) + 16);
    if ((s32)*(u64 *)(v92 + 24) >= 1)
    {
      v93 = (u32)*(u64 *)(v92 + 24);
      v94 = (v92 + 32);
      while (1)
      {
        v95 = *v94;
        if (*(u32 *)(*v94 + 16) == 2)
          break;
        ++v94;
        if (!--v93)
          goto LABEL_175;
      }
      v96 = *(u64 *)(v95 + 24);
      if (*(s32 *)(v96 + 24) >= 1)
      {
        v97 = 4;
        do
        {
          pMdl = get_pMdl(*(fldResHead_t *)(v96 + 8 * v97), 0)->pMdl;
          gameObject = get_gameObject(*(void *)(*((u64 *)&wdata->loadScene->obj.klass + v97) + 80), 0);
          pMdl->prefab = gameObject;
          v96 = *(u64 *)(v95 + 24);
          v100 = v97 - 3;
          ++v97;
        }
        while (v100 < *(s32 *)(v96 + 24));
      }
    }
LABEL_175:
    wdata->flag &= ~0x20u;
LABEL_176:
    v28 = wdata->flag | 8;
LABEL_67:
    wdata->flag = v28;
  }
}

// 0x1a32e70
static bool CheckPMVLoad(dds3ProcessID_t *id) {
  Il2CppObject *ProcessData;
  u8 *monitor;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
    return (char)ProcessData;
  monitor = ProcessData[1].monitor;
  if (monitor)
    LODWORD(ProcessData) = (monitor[16] >> 3) & 1;
  else
    LOBYTE(ProcessData) = 0;
  return (char)ProcessData;
}

// 0x1a32f70
bool evtCheckRun(dds3ProcessID_t *id) {
  Il2CppObject *ProcessData;
  Il2CppObject *v3;
  s64 naturalAligment;
  dds3ProcessID_t *v5;
  s64 v7;
  u32 *monitor;
  dds3ProcessID_t *v10;
  dds3ProcessID_t *ida;

  v10 = id;
  ProcessData = dds3GetProcessData(v10);
  v3 = ProcessData;
  if (ProcessData)
  {
    if (ProcessData->klass->_2.naturalAligment < (u32)naturalAligment || ProcessData->klass->_2.typeHierarchy[naturalAligment - 1] != evtViewerInfo_t)
    {
LABEL_25:
    }
  }
  v5 = v10;
  ida = v10;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
    return 0;
  if (ProcessData->klass->_2.naturalAligment < (u32)v7 || ProcessData->klass->_2.typeHierarchy[v7 - 1] != evtViewerInfo_t)
  {
    goto LABEL_25;
  }
  monitor = ProcessData[1].monitor;
  if (!monitor || (monitor[4] & 8) == 0 || (*((u8 *)v3[1].monitor + 16) & 1) != 0)
    return 0;
  return evtCheckProcess() != 0;
}

// 0x1a33170
bool evtCheckSeqEnd(dds3ProcessID_t *id) {
  Il2CppObject *ProcessData;
  u32 *monitor;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
    return 1;
  monitor = ProcessData[1].monitor;
  return !monitor || (monitor[4] & 9) == 8 && ((s64)ProcessData[1].klass & 0x80) != 0;
}

// 0x1a33280
f32 evtHokanFloat(s32 hokan, f32 ratio, f32 f1, f32 f2) {
  f32 v10;

  if (!hokan)
    return f1;
  v10 = 1.0;
  if (ratio <= 1.0)
    v10 = ratio;
  if (ratio < 0.0)
    v10 = 0.0;
  return (f32)((f32)(f2 - f1) * v10) + f1;
}

// 0x1a33340
static f32 HokanFloat(bool hokan, f32 ratio, f32 f1, f32 f2) {
  f32 v5;
  f32 v6;
  bool v7;
  f32 v8;

  if (hokan)
  {
    v5 = 1.0;
    v6 = f2 - f1;
    if (ratio <= 1.0)
      v5 = ratio;
    v7 = ratio < 0.0;
    v8 = 0.0;
    if (!v7)
      v8 = v5;
    return (f32)(v6 * v8) + f1;
  }
  return f1;
}

// 0x1a33370
s32 evtHokanInt(s32 hokan, f32 ratio, s32 i1, s32 i2) {
  f32 v10;
  f32 v11;

  if (!hokan)
    return i1;
  v10 = 1.0;
  if (ratio <= 1.0)
    v10 = ratio;
  if (ratio < 0.0)
    v10 = 0.0;
  v11 = (f32)(v10 * (f32)((f32)i2 - (f32)i1)) + (f32)i1;
  if (v11 == INFINITY)
    return 0x80000000;
  else
    return (s32)v11;
}

// 0x1a33450
static s32 HokanInt(bool hokan, f32 ratio, s32 i1, s32 i2) {
  f32 v5;
  bool v6;
  f32 v7;
  f32 v8;

  if (hokan)
  {
    v5 = 1.0;
    if (ratio <= 1.0)
      v5 = ratio;
    v6 = ratio < 0.0;
    v7 = 0.0;
    if (!v6)
      v7 = v5;
    v8 = (f32)(v7 * (f32)((f32)i2 - (f32)i1)) + (f32)i1;
    if (v8 == INFINITY)
      return 0x80000000;
    else
      return (s32)v8;
  }
  return i1;
}

// 0x1a334a0
static u32 HokanUInt(bool hokan, f32 ratio, u32 i1, u32 i2) {
  f32 v5;
  bool v6;
  f32 v7;
  f32 v8;

  if (hokan)
  {
    v5 = 1.0;
    if (ratio <= 1.0)
      v5 = ratio;
    v6 = ratio < 0.0;
    v7 = 0.0;
    if (!v6)
      v7 = v5;
    v8 = (f32)(v7 * (f32)((f32)i2 - (f32)i1)) + (f32)i1;
    if (v8 >= 0.0)
      return (u32)v8;
    else
      return (s32)v8;
  }
  return i1;
}

// 0x1a334f0
static sdfVector4_t HokanVector4(bool hokan, f32 ratio, const sdfVector4_t *c1, const sdfVector4_t *c2) {
  f32 v5;
  bool v6;
  f32 v7;
  sdfVector4_t result;

  if (hokan)
  {
    v5 = 1.0;
    if (ratio <= 1.0)
      v5 = ratio;
    v6 = ratio < 0.0;
    v7 = 0.0;
    if (!v6)
      v7 = v5;
    c1->x = c1->x + (f32)(v7 * (f32)(c2->x - c1->x));
    c1->y = c1->y + (f32)(v7 * (f32)(c2->y - c1->y));
    c1->z = c1->z + (f32)(v7 * (f32)(c2->z - c1->z));
    c1->w = c1->w + (f32)(v7 * (f32)(c2->w - c1->w));
  }
  result.x = c1->x;
  result.y = c1->y;
  result.z = c1->z;
  result.w = c1->w;
  return result;
}

// 0x1a33560
void evtHokanSceneLight(s32 hokan, f32 ratio, pmdSceneLightTable_t *key1, pmdSceneLightTable_t *key2, pmdSceneLightTable_t *d) {
  int32x4_t v6;
  pmdSceneLightTable_t *hsl_light0_local;
  f32 v13;
  sdfVector4_t *Color;
  int8x16_t v15;
  f32 v16;
  float32x4_t v17;
  int32x4_t v18;
  int32x4_t v19;
  sdfVector4_t *v20;
  sdfVector4_t *v21;
  float32x4_t v22;
  int8x16_t v23;
  int32x4_t v24;
  sdfVector4_t *v25;
  sdfVector4_t *v26;
  float32x4_t v27;
  int8x16_t v28;
  int32x4_t v29;
  int8x16_t Ambient;
  struct sdfVector4_t v31;
  pmdSceneLightTable_t *v32;
  sdfVector4_t v33;
  float32x4_t v34;
  float32x4_t v35;
  struct sdfVector4_t v36;
  int8x16_t v37;
  int8x16_t v38;
  int8x16_t v39;
  struct sdfVector4_t v40;
  f32 v41;

  hsl_light0_local = key1;
  if (key1)
    goto LABEL_3;
  goto LABEL_9000;
  if (hsl_light0_local)
  {
LABEL_3:
    if (key2)
      goto LABEL_13;
    goto LABEL_10;
  }
LABEL_9000:
  hsl_light0_local = hsl_light0;
  if (key2)
    goto LABEL_13;
LABEL_10:
  key2 = hsl_light0;
LABEL_13:
  v13 = 1.0;
  Color = d->Color;
  if (ratio <= 1.0)
    v13 = ratio;
  v15 = hsl_light0_local->Color[0];
  if (ratio >= 0.0)
    v16 = v13;
  else
    v16 = 0.0;
  v17 = key2->Color[0];
  v41 = v16;
  v33 = key2->Color[0];
  v37 = hsl_light0_local->Color[0];
  v17 = v33;
  v15 = v37;
  v16 = v41;
  v18.n128_u32[0] = 0;
  v6.n128_u32[0] = hokan;
  Color[0] = (sdfVector4_t)vbslq_s8(vdupq_lane_s32((int32x2_t)vceqq_s32(v6, v18).n128_u64[0], 0), v15, vaddq_f32(v15, vmulq_n_f32(vsubq_f32(v17, v15), v16)));
  v19 = hsl_light0_local->Dir[0];
  if (hokan)
    v19 = vaddq_f32(v19, vmulq_n_f32(vsubq_f32((float32x4_t)key2->Dir[0], v19), v16));
  d->Dir[0] = (sdfVector4_t)v19;
  v20 = key2->Color;
  v21 = d->Color;
  v22 = v20[1];
  v23 = hsl_light0_local->Color[1];
  v34 = v20[1];
  v38 = hsl_light0_local->Color[1];
  v22 = v34;
  v23 = v38;
  v16 = v41;
  v19.n128_u32[0] = 0;
  v6.n128_u32[0] = hokan;
  v21[1] = (sdfVector4_t)vbslq_s8(vdupq_lane_s32((int32x2_t)vceqq_s32(v6, v19).n128_u64[0], 0), v23, vaddq_f32(v23, vmulq_n_f32(vsubq_f32(v22, v23), v16)));
  v24 = hsl_light0_local->Dir[1];
  if (hokan)
    v24 = vaddq_f32(v24, vmulq_n_f32(vsubq_f32((float32x4_t)key2->Dir[1], v24), v16));
  d->Dir[1] = (sdfVector4_t)v24;
  v25 = key2->Color;
  v26 = d->Color;
  v27 = v25[2];
  v28 = hsl_light0_local->Color[2];
  v35 = v25[2];
  v39 = hsl_light0_local->Color[2];
  v27 = v35;
  v28 = v39;
  v16 = v41;
  v24.n128_u32[0] = 0;
  v6.n128_u32[0] = hokan;
  v26[2] = (sdfVector4_t)vbslq_s8(vdupq_lane_s32((int32x2_t)vceqq_s32(v6, v24).n128_u64[0], 0), v28, vaddq_f32(v28, vmulq_n_f32(vsubq_f32(v27, v28), v16)));
  v29 = hsl_light0_local->Dir[2];
  if (hokan)
    v29 = vaddq_f32(v29, vmulq_n_f32(vsubq_f32((float32x4_t)key2->Dir[2], v29), v16));
  d->Dir[2] = (sdfVector4_t)v29;
  Ambient = hsl_light0_local->Ambient;
  v31 = key2->Ambient;
  v32 = d;
  v36 = key2->Ambient;
  v40 = hsl_light0_local->Ambient;
  v31 = v36;
  Ambient = v40;
  v16 = v41;
  v29.n128_u32[0] = 0;
  v6.n128_u32[0] = hokan;
  v32->Ambient = (struct sdfVector4_t)vbslq_s8(vdupq_lane_s32((int32x2_t)vceqq_s32(v6, v29).n128_u64[0], 0), Ambient, vaddq_f32(Ambient, vmulq_n_f32(vsubq_f32((float32x4_t)v31, Ambient), v16)));
  d->Ambient.w = 1.0;
}

// 0x1a33830
void evtHokanSceneFog(s32 hokan, f32 ratio, pmdSceneFogTable_t *key1, pmdSceneFogTable_t *key2, pmdSceneFogTable_t *d) {
  ;
}

// 0x1a33840
static void HokanPos(bool hokan, f32 ratio, sdfIVector2_t p1, sdfIVector2_t p2, sdfIVector2_t *d) {
  f32 v9;
  f32 v10;
  s32 Item;
  s32 v12;
  f32 v14;
  s32 v15;
  s32 v16;
  s32 v17;
  f32 v18;
  s32 v19;
  sdfIVector2_t v20;
  sdfIVector2_t v21;

  v20 = p2;
  v21 = p1;
  v9 = 1.0;
  if (ratio <= 1.0)
    v9 = ratio;
  if (ratio >= 0.0)
    v10 = v9;
  else
    v10 = 0.0;
  Item = get_Item((sdfIVector2_t)&v21, 0, 0);
  v12 = get_Item((sdfIVector2_t)&v20, 0, 0);
  if (hokan)
  {
    v14 = (f32)(v10 * (f32)((f32)v12 - (f32)Item)) + (f32)Item;
    if (v14 == INFINITY)
      v15 = 0x80000000;
    else
      v15 = v14;
    set_Item((sdfIVector2_t)d, 0, v15, 0);
    v16 = get_Item((sdfIVector2_t)&v21, 1, 0);
    v17 = get_Item((sdfIVector2_t)&v20, 1, 0);
    v18 = (f32)(v10 * (f32)((f32)v17 - (f32)v16)) + (f32)v16;
    if (v18 == INFINITY)
      v19 = 0x80000000;
    else
      v19 = v18;
  }
  else
  {
    set_Item((sdfIVector2_t)d, 0, Item, 0);
    v19 = get_Item((sdfIVector2_t)&v21, 1, 0);
    get_Item((sdfIVector2_t)&v20, 1, 0);
  }
  set_Item((sdfIVector2_t)d, 1, v19, 0);
}

// 0x1a33a10
static void HokanArea(bool hokan, f32 ratio, sdfIVector2_t *a1, sdfIVector2_t *a2, sdfIVector2_t *d) {
  s64 v11;
  sdfIVector2_t *m_Items;
  sdfIVector2_t *v13;
  sdfIVector2_t *v14;
  _BOOL4 v15;
  sdfIVector2_t v16;
  sdfIVector2_t v17;

  if (SLODWORD(d->max_length) >= 1)
  {
    v11 = 0;
    m_Items = d;
    v13 = a2;
    v14 = a1;
    v15 = hokan;
    do
    {
      v16 = v14[v11];
      v17 = v13[v11];
      (loc_1A3B350)(v15, v16, v17, m_Items, 0, ratio);
      ++v11;
      ++m_Items;
    }
    while (v11 < SLODWORD(d->max_length));
  }
}

// 0x1a33b00
static void HokanBlur(bool hokan, f32 ratio, dds3Effect_Blur_t *key1, dds3Effect_Blur_t *key2, dds3Effect_Blur_t *d) {
  float32x4_t abgr;
  struct sdfVector4_t v13;
  f32 v14;
  float32x4_t v15;
  SDF_GS_ALPHA *blend;
  f32 rotate;
  f32 v18;
  f32 scale;
  sdfIVector2_t *xy;
  sdfIVector2_t *v21;
  sdfIVector2_t *v22;
  s64 v23;
  sdfIVector2_t *m_Items;
  sdfIVector2_t *v25;
  sdfIVector2_t *v26;
  sdfIVector2_t v27;
  sdfIVector2_t v28;

  abgr = key1->abgr;
  v13 = key2->abgr;
  if (hokan)
  {
    v14 = 1.0;
    v15 = vsubq_f32((float32x4_t)v13, abgr);
    if (ratio <= 1.0)
      v14 = ratio;
    if (ratio < 0.0)
      v14 = 0.0;
    abgr = vaddq_f32(abgr, vmulq_n_f32(v15, v14));
  }
  d->abgr = (struct sdfVector4_t)abgr;
  blend = get_blend(key1, 0);
  set_blend(d, blend, 0);
  rotate = key1->rotate;
  if (hokan)
  {
    v18 = 1.0;
    if (ratio <= 1.0)
      v18 = ratio;
    if (ratio < 0.0)
      v18 = 0.0;
    rotate = rotate + (f32)(v18 * (f32)(key2->rotate - rotate));
    scale = key1->scale + (f32)(v18 * (f32)(key2->scale - key1->scale));
  }
  else
  {
    scale = key1->scale;
  }
  d->rotate = rotate;
  d->scale = scale;
  (loc_1A3B350)(hokan, *(u64 *)&key1->center, *(u64 *)&key2->center, &d->center, 0, ratio);
  xy = d->xy;
  v21 = key1->xy;
  v22 = key2->xy;
  if (SLODWORD(xy->max_length) < 1)
    return;
  v23 = 0;
  m_Items = xy;
  v25 = v22;
  v26 = v21;
  do
  {
    v27 = v26[v23];
    v28 = v25[v23];
    (loc_1A3B350)(hokan, v27, v28, m_Items, 0, ratio);
    ++v23;
    ++m_Items;
  }
  while (v23 < SLODWORD(xy->max_length));
}

// 0x1a33d30
void evtHokanBlur2(s32 hokan, f32 ratio, dds3Effect_Blur_t *key1, dds3Effect_Blur_t *key2, dds3Effect_Blur_t *d) {
  dds3Effect_Blur_t *hsl_blur0_local;

  hsl_blur0_local = key1;
  if (key1)
    goto LABEL_3;
  goto LABEL_9000;
  if (hsl_blur0_local)
  {
LABEL_3:
    if (key2)
      goto LABEL_4;
LABEL_12:
    key2 = hsl_blur0;
    goto LABEL_6;
  }
LABEL_9000:
  hsl_blur0_local = hsl_blur0;
  if (!key2)
    goto LABEL_12;
LABEL_4:
LABEL_6:
  HokanBlur(hokan != 0, ratio, hsl_blur0_local, key2, d);
}

// 0x1a33e40
void evtHokanMultBlur(s32 hokan, f32 ratio, dds3Effect_PartialMultiBlurParam_t *key1, dds3Effect_PartialMultiBlurParam_t *key2, dds3Effect_PartialMultiBlurParam_t *d) {
  dds3Effect_PartialMultiBlurParam_t *hsl_mblur0_local;
  s32 area;
  s32 v13;
  f32 v14;
  f32 v15;

  hsl_mblur0_local = key1;
  if (key1)
    goto LABEL_3;
  hsl_mblur0_local = hsl_mblur0;
  if (!key2)
    goto LABEL_19;
LABEL_4:
  area = hsl_mblur0_local->area;
  v13 = key2->area;
  goto LABEL_5;
LABEL_3:
  if (key2)
    goto LABEL_4;
LABEL_19:
  key2 = hsl_mblur0;
  area = hsl_mblur0_local->area;
  v13 = key2->area;
LABEL_5:
  if (hokan)
  {
    v14 = 1.0;
    if (ratio <= 1.0)
      v14 = ratio;
    if (ratio < 0.0)
      v14 = 0.0;
    v15 = (f32)(v14 * (f32)((f32)v13 - (f32)area)) + (f32)area;
    if (v15 == INFINITY)
      area = 0x80000000;
    else
      area = v15;
  }
  d->area = area;
  HokanBlur(hokan != 0, ratio, hsl_mblur0_local->Blur, key2->Blur, d->Blur);
}

// 0x1a33fa0
void evtHokanFilter(s32 hokan, f32 ratio, dds3Effect_Filter_t *key1, dds3Effect_Filter_t *key2, dds3Effect_Filter_t *d) {
  dds3Effect_Filter_t *hsl_filter0_local;
  sdfIVector2_t *xy;
  sdfIVector2_t *v13;
  sdfIVector2_t *v14;
  s64 v15;
  sdfIVector2_t *m_Items;
  sdfIVector2_t *v17;
  sdfIVector2_t *v18;
  long f64 v19;
  sdfIVector2_t v20;
  sdfIVector2_t v21;
  float32x4_t abgr;
  f32 v23;
  float32x4_t v24;
  SDF_GS_ALPHA *blend;
  dds3Effect_Filter_t *v26;
  dds3Effect_Filter_t *v27;

  hsl_filter0_local = key1;
  if (key1)
    goto LABEL_3;
  hsl_filter0_local = hsl_filter0;
  if (!key2)
    goto LABEL_13;
LABEL_4:
  xy = hsl_filter0_local->xy;
  v27 = d;
  v13 = key2->xy;
  v14 = d->xy;
  goto LABEL_5;
LABEL_3:
  if (key2)
    goto LABEL_4;
LABEL_13:
  key2 = hsl_filter0;
  xy = hsl_filter0_local->xy;
  v27 = d;
  v13 = key2->xy;
  v14 = d->xy;
LABEL_5:
  v26 = key2;
  if (SLODWORD(v14->max_length) < 1)
    goto LABEL_22;
  v15 = 0;
  m_Items = v14;
  v17 = v13;
  v18 = xy;
  do
  {
    v20 = v18[v15];
    v21 = v17[v15];
    *(f32 *)&v19 = ratio;
    (loc_1A3B350)(hokan != 0, v20, v21, m_Items, 0, v19);
    ++v15;
    ++m_Items;
  }
  while (v15 < SLODWORD(v14->max_length));
LABEL_22:
  abgr = hsl_filter0_local->abgr;
  if (hokan)
  {
    v23 = 1.0;
    if (ratio <= 1.0)
      v23 = ratio;
    v24 = vsubq_f32((float32x4_t)v26->abgr, abgr);
    if (ratio < 0.0)
      v23 = 0.0;
    abgr = vaddq_f32(abgr, vmulq_n_f32(v24, v23));
  }
  v27->abgr = (struct sdfVector4_t)abgr;
  blend = get_blend(hsl_filter0_local, 0);
  set_blend(v27, blend, 0);
}

// 0x1a341c0
void evtHokanMultFilter(s32 hokan, f32 ratio, dds3Effect_PartialMultiFilterParam_t *key1, dds3Effect_PartialMultiFilterParam_t *key2, dds3Effect_PartialMultiFilterParam_t *d) {
  dds3Effect_PartialMultiFilterParam_t *hsl_mfilter0_local;
  s32 area;
  s32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  long f64 v17;
  struct sdfVector4_t abgr;
  f32 v19;
  dds3Effect_Filter_t *Filter;
  SDF_GS_ALPHA *blend;

  hsl_mfilter0_local = key1;
  if (key1)
    goto LABEL_3;
  hsl_mfilter0_local = hsl_mfilter0;
  if (!key2)
    goto LABEL_27;
LABEL_4:
  area = hsl_mfilter0_local->area;
  v13 = key2->area;
  goto LABEL_5;
LABEL_3:
  if (key2)
    goto LABEL_4;
LABEL_27:
  key2 = hsl_mfilter0;
  area = hsl_mfilter0_local->area;
  v13 = key2->area;
LABEL_5:
  v14 = 1.0;
  if (hokan)
  {
    if (ratio <= v14)
      v15 = ratio;
    else
      v15 = v14;
    if (ratio < 0.0)
      v15 = 0.0;
    v16 = (f32)(v15 * (f32)((f32)v13 - (f32)area)) + (f32)area;
    if (v16 == INFINITY)
      area = 0x80000000;
    else
      area = v16;
  }
  d->area = area;
  *(f32 *)&v17 = ratio;
  (loc_1A3B350)(hokan != 0, *(u64 *)&hsl_mfilter0_local->center, *(u64 *)&key2->center, &d->center, 0, v17);
  abgr = hsl_mfilter0_local->Filter->abgr;
  if (hokan)
  {
    if (ratio <= v14)
      v19 = ratio;
    else
      v19 = v14;
    if (ratio < 0.0)
      v19 = 0.0;
    abgr = (struct sdfVector4_t)vaddq_f32((float32x4_t)abgr, vmulq_n_f32(vsubq_f32((float32x4_t)key2->Filter->abgr, (float32x4_t)abgr), v19));
  }
  d->Filter->abgr = abgr;
  Filter = d->Filter;
  blend = get_blend(hsl_mfilter0_local->Filter, 0);
  set_blend(Filter, blend, 0);
}

// 0x1a34380
void evtHokanDistBlur(s32 hokan, f32 ratio, dds3Effect_DistortionBlurParam_t *key1, dds3Effect_DistortionBlurParam_t *key2, dds3Effect_DistortionBlurParam_t *d) {
  dds3Effect_DistortionBlurParam_t *hsl_dist0_local;
  u32 number;
  u32 v13;
  f32 v14;
  uint32x2_t v15;
  uint32x2_t v16;
  f32 v17;
  f32 v18;
  float32x2_t v19;
  float32x2_t v20;
  f32 v21;
  f32 v22;
  float32x4_t abgr;
  SDF_GS_ALPHA *blend;
  long f64 v25;
  f32 v26;
  f32 v27;
  f32 distortion;
  s32 area;
  s32 width;
  f32 v31;
  f32 v32;
  s64 v33;
  f32 speed;

  hsl_dist0_local = key1;
  if (key1)
    goto LABEL_3;
  hsl_dist0_local = hsl_dist0;
  if (!key2)
    goto LABEL_41;
LABEL_4:
  number = hsl_dist0_local->number;
  v13 = key2->number;
  goto LABEL_5;
LABEL_45:
  LODWORD(v33) = number;
  speed = hsl_dist0_local->speed;
  HIDWORD(v33) = hsl_dist0_local->interval;
  *(u64 *)&d->number = v33;
  d->speed = speed;
  abgr = hsl_dist0_local->abgr;
  goto LABEL_17;
LABEL_3:
  if (key2)
    goto LABEL_4;
LABEL_41:
  key2 = hsl_dist0;
  number = hsl_dist0_local->number;
  v13 = key2->number;
LABEL_5:
  v14 = 1.0;
  if (!hokan)
    goto LABEL_45;
  v15.n64_u32[0] = number;
  v16.n64_u32[0] = v13;
  v17 = 0.0;
  if (ratio <= v14)
    v18 = ratio;
  else
    v18 = v14;
  if (ratio >= 0.0)
    v17 = v18;
  v15.n64_u32[1] = hsl_dist0_local->interval;
  v19.n64_u64[0] = vcvt_f32_u32(v15).n64_u64[0];
  v16.n64_u32[1] = key2->interval;
  v20.n64_u64[0] = vadd_f32(vmul_n_f32(vsub_f32(vcvt_f32_u32(v16), v19), v17), v19).n64_u64[0];
  v21 = hsl_dist0_local->speed + (f32)(v17 * (f32)(key2->speed - hsl_dist0_local->speed));
  *(int8x8_t *)&d->number = vbsl_s8(vcltz_f32(v20), vcvt_s32_f32(v20), vcvt_u32_f32(v20));
  d->speed = v21;
  if (ratio <= v14)
    v22 = ratio;
  else
    v22 = v14;
  if (ratio < 0.0)
    v22 = 0.0;
  abgr = vaddq_f32((float32x4_t)hsl_dist0_local->abgr, vmulq_n_f32(vsubq_f32((float32x4_t)key2->abgr, (float32x4_t)hsl_dist0_local->abgr), v22));
LABEL_17:
  d->abgr = (struct sdfVector4_t)abgr;
  blend = get_blend(hsl_dist0_local, 0);
  set_blend(d, blend, 0);
  *(f32 *)&v25 = hsl_dist0_local->rotate;
  if (hokan)
  {
    if (ratio <= v14)
      v26 = ratio;
    else
      v26 = v14;
    if (ratio < 0.0)
      v26 = 0.0;
    *(f32 *)&v25 = *(f32 *)&v25 + (f32)(v26 * (f32)(key2->rotate - *(f32 *)&v25));
    v27 = (f32)(v26 * (f32)((f32)key2->area - (f32)hsl_dist0_local->area))
        + (f32)hsl_dist0_local->area;
    distortion = hsl_dist0_local->distortion
               + (f32)(v26 * (f32)(key2->distortion - hsl_dist0_local->distortion));
    area = v27;
    if (v27 == INFINITY)
      area = 0x80000000;
  }
  else
  {
    distortion = hsl_dist0_local->distortion;
    area = hsl_dist0_local->area;
  }
  d->rotate = *(f32 *)&v25;
  d->distortion = distortion;
  *(f32 *)&v25 = ratio;
  d->area = area;
  (loc_1A3B350)(hokan != 0, *(u64 *)&hsl_dist0_local->center, *(u64 *)&key2->center, &d->center, 0, v25);
  width = hsl_dist0_local->width;
  if (hokan)
  {
    if (ratio <= v14)
      v31 = ratio;
    else
      v31 = v14;
    if (ratio < 0.0)
      v31 = 0.0;
    v32 = (f32)(v31 * (f32)((f32)key2->width - (f32)width)) + (f32)width;
    width = v32;
    if (v32 == INFINITY)
      width = 0x80000000;
  }
  d->width = width;
}

// 0x1a34650
void evtHokanRipBlur(s32 hokan, f32 ratio, dds3Effect_RippleBlurParam_t *key1, dds3Effect_RippleBlurParam_t *key2, dds3Effect_RippleBlurParam_t *d) {
  dds3Effect_RippleBlurParam_t *hsl_rip0_local;
  u32 number;
  u32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  bool v18;
  s32 v19;
  u32 v20;
  float32x2_t v21;
  u32 v22;
  f32 v23;
  float32x4_t abgr;
  SDF_GS_ALPHA *blend;
  long f64 v26;
  f32 v27;
  float32x2_t v28;
  s32 area;
  f32 v30;
  f32 v31;
  s64 v32;

  hsl_rip0_local = key1;
  if (key1)
    goto LABEL_3;
  hsl_rip0_local = hsl_rip0;
  if (!key2)
    goto LABEL_42;
LABEL_4:
  number = hsl_rip0_local->number;
  v13 = key2->number;
  goto LABEL_5;
LABEL_46:
  v32 = *(u64 *)&hsl_rip0_local->speed;
  d->number = number;
  *(u64 *)&d->speed = v32;
  abgr = hsl_rip0_local->abgr;
  goto LABEL_20;
LABEL_3:
  if (key2)
    goto LABEL_4;
LABEL_42:
  key2 = hsl_rip0;
  number = hsl_rip0_local->number;
  v13 = key2->number;
LABEL_5:
  v14 = 1.0;
  if (!hokan)
    goto LABEL_46;
  v15 = 0.0;
  if (ratio <= v14)
    v16 = ratio;
  else
    v16 = v14;
  if (ratio >= 0.0)
    v15 = v16;
  v17 = (f32)(v15 * (f32)((f32)v13 - (f32)number)) + (f32)number;
  v18 = v17 < 0.0;
  v19 = v17;
  v20 = v17;
  v21.n64_u64[0] = vadd_f32(*(float32x2_t *)&hsl_rip0_local->speed, vmul_n_f32(vsub_f32(*(float32x2_t *)&key2->speed, *(float32x2_t *)&hsl_rip0_local->speed), v15)).n64_u64[0];
  if (v18)
    v22 = v19;
  else
    v22 = v20;
  d->number = v22;
  *(float32x2_t *)&d->speed = v21;
  if (ratio <= v14)
    v23 = ratio;
  else
    v23 = v14;
  if (ratio < 0.0)
    v23 = 0.0;
  abgr = vaddq_f32((float32x4_t)hsl_rip0_local->abgr, vmulq_n_f32(vsubq_f32((float32x4_t)key2->abgr, (float32x4_t)hsl_rip0_local->abgr), v23));
LABEL_20:
  d->abgr = (struct sdfVector4_t)abgr;
  blend = get_blend(hsl_rip0_local, 0);
  set_blend(d, blend, 0);
  *(f32 *)&v26 = hsl_rip0_local->rotate;
  if (hokan)
  {
    if (ratio <= v14)
      v27 = ratio;
    else
      v27 = v14;
    if (ratio < 0.0)
      v27 = 0.0;
    *(f32 *)&v26 = *(f32 *)&v26 + (f32)(v27 * (f32)(key2->rotate - *(f32 *)&v26));
    v28.n64_u64[0] = vadd_f32(*(float32x2_t *)&hsl_rip0_local->power, vmul_n_f32(vsub_f32(*(float32x2_t *)&key2->power, *(float32x2_t *)&hsl_rip0_local->power), v27)).n64_u64[0];
  }
  else
  {
    v28.n64_u64[0] = *(u64 *)&hsl_rip0_local->power;
  }
  d->rotate = *(f32 *)&v26;
  *(f32 *)&v26 = ratio;
  *(float32x2_t *)&d->power = v28;
  (loc_1A3B350)(hokan != 0, *(u64 *)&hsl_rip0_local->center, *(u64 *)&key2->center, &d->center, 0, v26);
  area = hsl_rip0_local->area;
  if (hokan)
  {
    if (ratio <= v14)
      v30 = ratio;
    else
      v30 = v14;
    if (ratio < 0.0)
      v30 = 0.0;
    v31 = (f32)(v30 * (f32)((f32)key2->area - (f32)area)) + (f32)area;
    area = v31;
    if (v31 == INFINITY)
      area = 0x80000000;
  }
  d->area = area;
}

// 0x1a348c0
void evtHokanHeikouBlur(s32 hokan, f32 ratio, dds3Effect_ParallelBlur_t *key1, dds3Effect_ParallelBlur_t *key2, dds3Effect_ParallelBlur_t *d) {
  dds3Effect_ParallelBlur_t *hsl_hblur0_local;
  struct sdfVector4_t abgr;
  struct sdfVector4_t v13;
  f32 v14;
  f32 v15;
  float32x4_t v16;
  SDF_GS_ALPHA *blend;
  long f64 v18;
  f32 v19;
  f32 power;
  long f64 v21;
  sdfIVector2_t *xy;
  sdfIVector2_t *v23;
  sdfIVector2_t *v24;
  s64 v25;
  sdfIVector2_t *m_Items;
  sdfIVector2_t *v27;
  sdfIVector2_t *v28;
  sdfIVector2_t v29;
  sdfIVector2_t v30;

  hsl_hblur0_local = key1;
  if (key1)
    goto LABEL_3;
  hsl_hblur0_local = hsl_hblur0;
  if (!key2)
    goto LABEL_33;
LABEL_4:
  abgr = hsl_hblur0_local->abgr;
  v13 = key2->abgr;
  goto LABEL_5;
LABEL_3:
  if (key2)
    goto LABEL_4;
LABEL_33:
  key2 = hsl_hblur0;
  abgr = hsl_hblur0_local->abgr;
  v13 = key2->abgr;
LABEL_5:
  v14 = 1.0;
  if (hokan)
  {
    if (ratio <= v14)
      v15 = ratio;
    else
      v15 = v14;
    v16 = vsubq_f32((float32x4_t)v13, (float32x4_t)abgr);
    if (ratio < 0.0)
      v15 = 0.0;
    abgr = (struct sdfVector4_t)vaddq_f32((float32x4_t)abgr, vmulq_n_f32(v16, v15));
  }
  d->abgr = abgr;
  blend = get_blend(hsl_hblur0_local, 0);
  set_blend(d, blend, 0);
  *(f32 *)&v18 = hsl_hblur0_local->direction;
  if (hokan)
  {
    if (ratio <= v14)
      v19 = ratio;
    else
      v19 = v14;
    if (ratio < 0.0)
      v19 = 0.0;
    *(f32 *)&v18 = *(f32 *)&v18 + (f32)(v19 * (f32)(key2->direction - *(f32 *)&v18));
    power = hsl_hblur0_local->power + (f32)(v19 * (f32)(key2->power - hsl_hblur0_local->power));
  }
  else
  {
    power = hsl_hblur0_local->power;
  }
  d->direction = *(f32 *)&v18;
  d->power = power;
  *(f32 *)&v18 = ratio;
  (loc_1A3B350)(hokan != 0, *(u64 *)&hsl_hblur0_local->center, *(u64 *)&key2->center, &d->center, 0, v18);
  xy = d->xy;
  v23 = hsl_hblur0_local->xy;
  v24 = key2->xy;
  if (SLODWORD(xy->max_length) >= 1)
  {
    v25 = 0;
    m_Items = xy;
    v27 = v24;
    v28 = v23;
    do
    {
      v29 = v28[v25];
      v30 = v27[v25];
      *(f32 *)&v21 = ratio;
      (loc_1A3B350)(hokan != 0, v29, v30, m_Items, 0, v21);
      ++v25;
      ++m_Items;
    }
    while (v25 < SLODWORD(xy->max_length));
  }
}

// 0x1a34b30
void evtHokanDof(DepthOfFieldSetting *_hokanData) {
  void *mDof;

  mDof = get_Instance(0)->mDof;
  HokanUpdate(hokanData, 0);
  SetParamToDepthOfField(hokanData, mDof, 0);
}

// 0x1a34bb0
void evtRunUnitMode(dds3Basic_t *unit, PMD_UNIT mode, u32 addflag, u32 downflag) {
  dds3ModelHandle_t *Model;
  dds3ModelHandle_t *v10;
  u32 v11;
  dds3Basic_t *pObjectBasic;

  pObjectBasic = unit;
  switch (mode)
  {
    case 0:
      Model = dds3UnitObjectBasicGetUnitHandle(unit)->Model;
      mdlShow(Model);
      return;
    case 1:
      v10 = dds3UnitObjectBasicGetUnitHandle(unit)->Model;
      mdlHide(v10);
      return;
    case 2:
      dds3ObjectBaseOffFlag(pObjectBasic, 0x400u);
      dds3ObjectBaseOffFlag(pObjectBasic, 0x200u);
      dds3ObjectBaseOffFlag(pObjectBasic, 0x4000u);
      v11 = 0x8000;
      goto LABEL_23;
    case 3:
      dds3ObjectBaseOnFlag(pObjectBasic, 0x400u);
      dds3ObjectBaseOffFlag(pObjectBasic, 0x200u);
      if (addflag)
        dds3ObjectBaseOnFlag(pObjectBasic, addflag);
      if (!downflag)
        return;
      goto LABEL_22;
    case 4:
      dds3ObjectBaseOffFlag(pObjectBasic, 0x400u);
      dds3ObjectBaseOnFlag(pObjectBasic, 0x200u);
      if (addflag)
        dds3ObjectBaseOnFlag(pObjectBasic, addflag);
      if (downflag)
      {
LABEL_22:
        v11 = downflag;
LABEL_23:
        dds3ObjectBaseOffFlag(pObjectBasic, v11);
      }
      break;
    case 8:
      dds3UnitObjectBasicSetOt(unit, 0);
      break;
    case 9:
      dds3UnitObjectBasicSetOt(unit, 11);
      break;
    default:
      return;
  }
}

// 0x1a34e40
void evtSetFlag(dds3ProcessID_t *id, PMD_FLAG flag) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
  *((u32 *)ProcessData[1].monitor + 4) |= flag;
}

// 0x1a34f30
void evtResetFlag(dds3ProcessID_t *id, PMD_FLAG flag) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
  LODWORD(ProcessData[1].klass) &= ~flag;
}

// 0x1a35010
void evtStopMover(dds3Basic_t *mover, bool sw, s32 baseframe, s32 nowframe) {
  void *workdata;
  dds3PathBasicControl_t *monitor;
  f32 frameMax;
  s32 v13;
  s32 v14;
  f32 v15;
  dds3PathBasicControl_t *pControl;

  workdata = mover->workdata;
  monitor = workdata[1].monitor;
  pControl = monitor;
  if (monitor)
  {
    frameMax = monitor->frameMax;
    v13 = (nowframe - baseframe) & ~((nowframe - baseframe) >> 31);
    v14 = 2 * (s32)frameMax;
    if (frameMax == INFINITY)
      v14 = 0;
    if (v13 >= v14)
      v13 = v14;
    v15 = (f32)v13 / (f32)v14;
    dds3PathBasicControlSetRatio(pControl, v15);
    if (sw)
    {
      dds3PathBasicPauseOff(pControl);
    }
    else
    {
      dds3PathBasicPause(pControl);
    }
  }
}

// 0x1a35170
void evtMoverFrameSet(dds3Basic_t *mover, bool sw, s32 baseframe, s32 nowframe, s32 offset) {
  void *workdata;
  f32 *monitor;
  f32 v13;
  s32 v14;

  workdata = mover->workdata;
  monitor = workdata[1].monitor;
  if (monitor)
  {
    v13 = monitor[6];
    v14 = 2 * (s32)v13;
    if (v13 == INFINITY)
      v14 = 0;
    if (((nowframe - baseframe + offset) & ~((nowframe - baseframe + offset) >> 31)) < v14)
      v14 = (nowframe - baseframe + offset) & ~((nowframe - baseframe + offset) >> 31);
    monitor[7] = (f32)v14 * 0.5;
  }
}

// 0x1a35250
static pmdProcessWork_t *InitWorkData(void) {
  pmdProcessWork_t *v1;

  v1 = (pmdProcessWork_t *)Allocate(pmdProcessWork_t);
  _ctor(v1, 0);
  if (v1)
  {
    *(_OWORD *)&GlobalParamScaleX = xmmword_3CFEE20;
  }
  return v1;
}

// 0x1a31e30
static pmdProcessWork_t *GetWorkData1(pmdProcessWork_t *wdata, void *pm1data) {
  bool v5;
  pmdProcessWork_t *result;
  dds3Basic_t *v7;
  s64 i;
  u64 *v9;
  pmdPM1_t *pm1;
  pmdHeader_t *header;
  pmdPM1_t *v12;
  pmdTypeTable_t *typeTable;
  pmdPM1_t *v14;
  pmdPM1_t *v15;
  pmdPM1_t *v16;
  pmdPM1_t *v17;
  pmdPM1_t *v18;
  pmdPM1_t *v19;
  pmdPM1_t *v20;
  pmdPM1_t *v21;
  pmdPM1_t *v22;
  s64 v23;
  s64 v24;
  s64 v25;
  u64 *v26;
  s64 naturalAligment;
  pmdNameTable_t *v28;
  pmdPM1_t *v29;
  s64 v30;
  pmdStageTable_t *v31;
  pmdPM1_t *v32;
  s64 v33;
  pmdUnitTable_t *v34;
  pmdPM1_t *v35;
  s32 ItemCount;
  pmdPM1_t *v37;
  u8 *v40;
  u8 *MessageData;
  s64 v42;
  pmdEffectTable_t *v43;
  pmdPM1_t *v44;
  s64 v45;
  void *v46;
  s64 v47;
  void *v48;
  s64 v49;
  pmdTmxTable_t *v50;
  pmdPM1_t *v51;

  v5 = op_Equality(pm1data, 0, 0);
  result = 0;
  if (!v5)
  {
    wdata->MesHandle = -1;
    wdata->NowFrame = 0;
    v7 = NewSpecific(dds3Basic_t, 0x7Fu);
    wdata->EffectBasicTable = v7;
    for (i = 32; i != 1048; i += 8)
    {
      v9 = ((char *)&wdata->EffectBasicTable->obj.klass + i);
      *v9 = 0;
    }
    pm1 = wdata->pm1;
    header = pm1data->header;
    pm1->Header1 = header;
    v12 = wdata->pm1;
    typeTable = pm1data->typeTable;
    v12->TypeTable1 = typeTable;
    v14 = wdata->pm1;
    v14->NameTable1 = 0;
    v15 = wdata->pm1;
    v15->StageTable = 0;
    v15 = ((char *)v15 + 56);
    v15[-1].TmxCount = 0;
    v16 = wdata->pm1;
    v16->StageF1 = 0;
    v16 = ((char *)v16 + 72);
    v16[-1].TmxCount = 0;
    v17 = wdata->pm1;
    v17->StageF2 = 0;
    v18 = wdata->pm1;
    v18->StageTB = 0;
    v19 = wdata->pm1;
    v19->UnitTable = 0;
    v20 = wdata->pm1;
    v20->EffectTable = 0;
    v20 = ((char *)v20 + 112);
    v20[-1].TmxCount = 0;
    v21 = wdata->pm1;
    v21->TmxTable = 0;
    v21 = ((char *)v21 + 136);
    LODWORD(v21[-1].TmxTable) = 0;
    v22 = wdata->pm1;
    v22->TmxCount = 0;
    if (v22->Header1->TypeTableCount >= 1)
    {
      v23 = 4;
      do
      {
        v25 = *((u64 *)&v22->TypeTable1->obj.klass + v23);
        switch (*(u32 *)(v25 + 16))
        {
          case 1:
            v26 = *(u64 **)(v25 + 32);
            if (v26)
            {
              if (*(u8 *)(*v26 + 304) < (u32)naturalAligment || *(Project_pmdNameTable_t_Item_c **)(*(u64 *)(*v26 + 200) + 8 * naturalAligment - 8) != Project_pmdNameTable_t_Item)
              {
                goto LABEL_53;
              }
            }
            v28 = v26[2];
            v22->NameTable1 = v28;
            v29 = wdata->pm1;
            v29->NameCount1 = get_ItemCount(*((pmdTypeTable_t *)&v29->TypeTable1->obj.klass + v23), 0);
            break;
          case 2:
            v26 = *(u64 **)(v25 + 32);
            if (v26)
            {
              if (*(u8 *)(*v26 + 304) < (u32)v30 || *(Project_pmdStageTable_t_Item_c **)(*(u64 *)(*v26 + 200) + 8 * v30 - 8) != Project_pmdStageTable_t_Item)
              {
                goto LABEL_53;
              }
            }
            v31 = *(pmdStageTable_t *)(v26[2] + 32);
            v22->StageTable = v31;
            v32 = wdata->pm1;
            v32->StageCount = get_ItemCount(*((pmdTypeTable_t *)&v32->TypeTable1->obj.klass + v23), 0);
            break;
          case 3:
            v26 = *(u64 **)(v25 + 32);
            if (v26)
            {
              if (*(u8 *)(*v26 + 304) < (u32)v33 || *(Project_pmdUnitTable_t_Item_c **)(*(u64 *)(*v26 + 200) + 8 * v33 - 8) != Project_pmdUnitTable_t_Item)
              {
                goto LABEL_53;
              }
            }
            v34 = v26[2];
            v22->UnitTable = v34;
            v35 = wdata->pm1;
            v35->UnitCount = get_ItemCount(*((pmdTypeTable_t *)&v35->TypeTable1->obj.klass + v23), 0);
            break;
          case 6:
            ItemCount = get_ItemCount(*((pmdTypeTable_t *)&v22->TypeTable1->obj.klass + v23), 0);
            v37 = wdata->pm1;
            if (ItemCount)
            {
              v26 = *(u64 **)(*((u64 *)&v37->TypeTable1->obj.klass + v23) + 32);
              {
LABEL_53:
              }
              v40 = v26[2];
              v37->MessageData = v40;
              MessageData = wdata->pm1->MessageData;
              wdata->MesHandle = itfMesMngInitialize(&MessageData->obj, 0, 0);
            }
            else
            {
              v37->MessageData = 0;
              wdata->MesHandle = -1;
            }
            break;
          case 7:
            v26 = *(u64 **)(v25 + 32);
            if (v26)
            {
              if (*(u8 *)(*v26 + 304) < (u32)v42 || *(Project_pmdEffectTable_t_Item_c **)(*(u64 *)(*v26 + 200) + 8 * v42 - 8) != Project_pmdEffectTable_t_Item)
              {
                goto LABEL_53;
              }
            }
            v43 = v26[2];
            v22->EffectTable = v43;
            v44 = wdata->pm1;
            v44->EffectCount = get_ItemCount(*((pmdTypeTable_t *)&v44->TypeTable1->obj.klass + v23), 0);
            break;
          case 0xA:
            v26 = *(u64 **)(v25 + 32);
            if (v26)
            {
              if (*(u8 *)(*v26 + 304) < (u32)v45 || *(Project_pmdFieldTable_t_Item_c **)(*(u64 *)(*v26 + 200) + 8 * v45 - 8) != Project_pmdFieldTable_t_Item)
              {
                goto LABEL_53;
              }
            }
            v46 = *(void *)(*(u64 *)(v26[2] + 32) + 16);
            v22->StageF1 = v46;
            break;
          case 0xB:
            v26 = *(u64 **)(v25 + 32);
            if (v26)
            {
              if (*(u8 *)(*v26 + 304) < (u32)v47 || *(Project_pmdFieldTable_t_Item_c **)(*(u64 *)(*v26 + 200) + 8 * v47 - 8) != Project_pmdFieldTable_t_Item)
              {
                goto LABEL_53;
              }
            }
            v48 = *(void *)(*(u64 *)(v26[2] + 32) + 16);
            v22->StageF2 = v48;
            break;
          case 0x16:
            v26 = *(u64 **)(v25 + 32);
            if (v26)
            {
              if (*(u8 *)(*v26 + 304) < (u32)v49 || *(Project_pmdTmxTable_t_Item_c **)(*(u64 *)(*v26 + 200) + 8 * v49 - 8) != Project_pmdTmxTable_t_Item)
              {
                goto LABEL_53;
              }
            }
            v50 = v26[2];
            v22->TmxTable = v50;
            v51 = wdata->pm1;
            v51->TmxCount = get_ItemCount(*((pmdTypeTable_t *)&v51->TypeTable1->obj.klass + v23), 0);
            break;
          default:
            break;
        }
        v22 = wdata->pm1;
        v24 = v23 - 3;
        ++v23;
      }
      while (v24 < v22->Header1->TypeTableCount);
    }
    return wdata;
  }
  return result;
}

// 0x1a32470
pmdProcessWork_t *evtGetWorkData2and3(pmdProcessWork_t *wdata, pmdSeqData_t *pm2dataParam, pmdSeqData_t *pm3dataParam) {
  pmdPM2_t *pm2;
  pmdPM2_t *v8;
  pmdPM2_t *v9;
  pmdPM2_t *v10;
  pmdPM2_t *v11;
  pmdPM2_t *v12;
  pmdPM2_t *v13;
  pmdPM2_t *v14;
  pmdPM2_t *v15;
  pmdPM2_t *v16;
  pmdPM2_t *v17;
  pmdPM2_t *v18;
  pmdPM2_t *v19;
  pmdPM2_t *v20;
  pmdPM2_t *v21;
  pmdPM2_t *v22;
  void *pData;
  pmdHeader_t *header;
  pmdPM2_t *v25;
  pmdTypeTable_t *typeTable;
  pmdPM2_t *v27;
  s64 v28;
  pmdRainDataTable_t *v29;
  pmdPM2_t *v30;
  pmdTypeTable_t *v31;
  void *Item;
  s64 naturalAligment;
  pmdCutInfo_t *data;
  s64 v35;
  pmdNameTable_t *klass;
  pmdPM2_t *v37;
  s64 v38;
  pmdFrameTable_t *v39;
  pmdPM2_t *v40;
  s64 v41;
  pmdCameraTable_t *v42;
  pmdPM2_t *v43;
  s64 v44;
  pmdSceneLightTable_t *v45;
  pmdPM2_t *v46;
  s64 v47;
  pmdSceneFogTable_t *v48;
  pmdPM2_t *v49;
  s64 v50;
  pmdBlur2Table_t *v51;
  pmdPM2_t *v52;
  s64 v53;
  pmdMultBlurTable_t *v54;
  pmdPM2_t *v55;
  s64 v56;
  pmdDistBlurTable_t *v57;
  pmdPM2_t *v58;
  s64 v59;
  pmdFilterTable_t *v60;
  pmdPM2_t *v61;
  s64 v62;
  pmdMultFilterTable_t *v63;
  pmdPM2_t *v64;
  s64 v65;
  pmdRipBlurTable_t *v66;
  pmdPM2_t *v67;
  s64 v68;
  pmdObjectTable_t *v69;
  pmdPM2_t *v70;
  s64 v71;
  pmdHeikouBlurTable_t *v72;
  pmdPM2_t *v73;
  s64 v74;
  pmdPM3_t *pm3;
  pmdPM3_t *v76;
  void *v77;
  pmdHeader_t *v78;
  pmdPM3_t *v79;
  pmdTypeTable_t *v80;
  pmdPM3_t *v81;
  s64 v82;
  pmdFrameTable_t *v83;
  pmdPM3_t *v84;
  s64 v85;
  s64 v86;
  s64 v87;
  u64 *p_klass;

  pm2 = wdata->pm2;
  pm2->NameTable2 = 0;
  v8 = wdata->pm2;
  v8->CutInfo = 0;
  v8 = ((char *)v8 + 56);
  v8[-1].RainDataCount = 0;
  v9 = wdata->pm2;
  v9->FrameTable = 0;
  v10 = wdata->pm2;
  v10->CameraTable = 0;
  v10 = ((char *)v10 + 80);
  v10[-1].RainDataCount = 0;
  v11 = wdata->pm2;
  v11->SLightTable = 0;
  v11 = ((char *)v11 + 96);
  v11[-1].RainDataCount = 0;
  v12 = wdata->pm2;
  v12->SFogTable = 0;
  v12 = ((char *)v12 + 112);
  v12[-1].RainDataCount = 0;
  v13 = wdata->pm2;
  v13->Blur2Table = 0;
  v13 = ((char *)v13 + 128);
  v13[-1].RainDataCount = 0;
  v14 = wdata->pm2;
  v14->MBlurTable = 0;
  v14 = ((char *)v14 + 144);
  v14[-1].RainDataCount = 0;
  v15 = wdata->pm2;
  v15->DBlurTable = 0;
  v15 = ((char *)v15 + 160);
  v15[-1].RainDataCount = 0;
  v16 = wdata->pm2;
  v16->FilterTable = 0;
  v16 = ((char *)v16 + 176);
  v16[-1].RainDataCount = 0;
  v17 = wdata->pm2;
  v17->MFilterTable = 0;
  v17 = ((char *)v17 + 192);
  v17[-1].RainDataCount = 0;
  v18 = wdata->pm2;
  v18->RBlurTable = 0;
  v18 = ((char *)v18 + 208);
  v18[-1].RainDataCount = 0;
  v19 = wdata->pm2;
  v19->ObjectTable = 0;
  v19 = ((char *)v19 + 240);
  v19[-1].ObjectCount = 0;
  v20 = wdata->pm2;
  v20->HBlurTable = 0;
  v20 = ((char *)v20 + 224);
  LODWORD(v20->Header2) = 0;
  v21 = wdata->pm2;
  v21->HBlurCount = 0;
  v21->RainDataTable = 0;
  v22 = wdata->pm2;
  v22->RainDataCount = 0;
  if (!pm2dataParam)
  {
    v22->Header2 = 0;
    p_klass = &wdata->pm2->klass;
LABEL_81:
    p_klass[4] = 0;
    return wdata;
  }
  pData = pm2dataParam->pData;
  header = pData->header;
  v22->Header2 = header;
  v25 = wdata->pm2;
  typeTable = pData->typeTable;
  v25->TypeTable2 = typeTable;
  v27 = wdata->pm2;
  if (v27->Header2->TypeTableCount >= 1)
  {
    v28 = 0;
    do
    {
      v31 = v27->TypeTable2[v28];
      switch (v31->Type)
      {
        case 0:
          Item = v31->Item;
          if (Item)
          {
            if (Item->klass->_2.naturalAligment < (u32)naturalAligment || Item->klass->_2.typeHierarchy[naturalAligment - 1] != Project_pmdCutInfo_t_Item)
            {
              goto LABEL_78;
            }
          }
          data = Item[1].klass->_1.byval_arg.data;
          v27->CutInfo = data;
          break;
        case 1:
          Item = v31->Item;
          if (Item)
          {
            if (Item->klass->_2.naturalAligment < (u32)v35 || Item->klass->_2.typeHierarchy[v35 - 1] != Project_pmdNameTable_t_Item)
            {
              goto LABEL_78;
            }
          }
          klass = Item[1].klass;
          v27->NameTable2 = klass;
          v37 = wdata->pm2;
          v37->NameCount2 = get_ItemCount(v37->TypeTable2[v28], 0);
          break;
        case 4:
          Item = v31->Item;
          if (Item)
          {
            if (Item->klass->_2.naturalAligment < (u32)v38 || Item->klass->_2.typeHierarchy[v38 - 1] != Project_pmdFrameTable_t_Item)
            {
              goto LABEL_78;
            }
          }
          v39 = Item[1].klass;
          v27->FrameTable = v39;
          v40 = wdata->pm2;
          v40->FrameCount = get_ItemCount(v40->TypeTable2[v28], 0);
          break;
        case 5:
          Item = v31->Item;
          if (Item)
          {
            if (Item->klass->_2.naturalAligment < (u32)v41 || Item->klass->_2.typeHierarchy[v41 - 1] != Project_pmdCameraTable_t_Item)
            {
              goto LABEL_78;
            }
          }
          v42 = Item[1].klass;
          v27->CameraTable = v42;
          v43 = wdata->pm2;
          v43->CameraCount = get_ItemCount(v43->TypeTable2[v28], 0);
          break;
        case 0xD:
          Item = v31->Item;
          if (Item)
          {
            if (Item->klass->_2.naturalAligment < (u32)v44 || Item->klass->_2.typeHierarchy[v44 - 1] != Project_pmdSceneLightTable_t_Item)
            {
              goto LABEL_78;
            }
          }
          v45 = Item[1].klass;
          v27->SLightTable = v45;
          v46 = wdata->pm2;
          v46->SLightCount = get_ItemCount(v46->TypeTable2[v28], 0);
          break;
        case 0xE:
          Item = v31->Item;
          if (Item)
          {
            if (Item->klass->_2.naturalAligment < (u32)v47 || Item->klass->_2.typeHierarchy[v47 - 1] != Project_pmdSceneFogTable_t_Item)
            {
              goto LABEL_78;
            }
          }
          v48 = Item[1].klass;
          v27->SFogTable = v48;
          v49 = wdata->pm2;
          v49->SFogCount = get_ItemCount(v49->TypeTable2[v28], 0);
          break;
        case 0xF:
          Item = v31->Item;
          if (Item)
          {
            if (Item->klass->_2.naturalAligment < (u32)v50 || Item->klass->_2.typeHierarchy[v50 - 1] != Project_pmdBlur2Table_t_Item)
            {
              goto LABEL_78;
            }
          }
          v51 = Item[1].klass;
          v27->Blur2Table = v51;
          v52 = wdata->pm2;
          v52->Blur2Count = get_ItemCount(v52->TypeTable2[v28], 0);
          break;
        case 0x10:
          Item = v31->Item;
          if (Item)
          {
            if (Item->klass->_2.naturalAligment < (u32)v53 || Item->klass->_2.typeHierarchy[v53 - 1] != Project_pmdMultBlurTable_t_Item)
            {
              goto LABEL_78;
            }
          }
          v54 = Item[1].klass;
          v27->MBlurTable = v54;
          v55 = wdata->pm2;
          v55->MBlurCount = get_ItemCount(v55->TypeTable2[v28], 0);
          break;
        case 0x11:
          Item = v31->Item;
          if (Item)
          {
            if (Item->klass->_2.naturalAligment < (u32)v56 || Item->klass->_2.typeHierarchy[v56 - 1] != Project_pmdDistBlurTable_t_Item)
            {
              goto LABEL_78;
            }
          }
          v57 = Item[1].klass;
          v27->DBlurTable = v57;
          v58 = wdata->pm2;
          v58->DBlurCount = get_ItemCount(v58->TypeTable2[v28], 0);
          break;
        case 0x12:
          Item = v31->Item;
          if (Item)
          {
            if (Item->klass->_2.naturalAligment < (u32)v59 || Item->klass->_2.typeHierarchy[v59 - 1] != Project_pmdFilterTable_t_Item)
            {
              goto LABEL_78;
            }
          }
          v60 = Item[1].klass;
          v27->FilterTable = v60;
          v61 = wdata->pm2;
          v61->FilterCount = get_ItemCount(v61->TypeTable2[v28], 0);
          break;
        case 0x13:
          Item = v31->Item;
          if (Item)
          {
            if (Item->klass->_2.naturalAligment < (u32)v62 || Item->klass->_2.typeHierarchy[v62 - 1] != Project_pmdMultFilterTable_t_Item)
            {
              goto LABEL_78;
            }
          }
          v63 = Item[1].klass;
          v27->MFilterTable = v63;
          v64 = wdata->pm2;
          v64->MFilterCount = get_ItemCount(v64->TypeTable2[v28], 0);
          break;
        case 0x14:
          Item = v31->Item;
          if (Item)
          {
            if (Item->klass->_2.naturalAligment < (u32)v65 || Item->klass->_2.typeHierarchy[v65 - 1] != Project_pmdRipBlurTable_t_Item)
            {
              goto LABEL_78;
            }
          }
          v66 = Item[1].klass;
          v27->RBlurTable = v66;
          v67 = wdata->pm2;
          v67->RBlurCount = get_ItemCount(v67->TypeTable2[v28], 0);
          break;
        case 0x15:
          Item = v31->Item;
          if (Item)
          {
            if (Item->klass->_2.naturalAligment < (u32)v68 || Item->klass->_2.typeHierarchy[v68 - 1] != Project_pmdObjectTable_t_Item)
            {
              goto LABEL_78;
            }
          }
          v69 = Item[1].klass;
          v27->ObjectTable = v69;
          v70 = wdata->pm2;
          v70->ObjectCount = get_ItemCount(v70->TypeTable2[v28], 0);
          break;
        case 0x18:
          Item = v31->Item;
          if (Item)
          {
            if (Item->klass->_2.naturalAligment < (u32)v71 || Item->klass->_2.typeHierarchy[v71 - 1] != Project_pmdHeikouBlurTable_t_Item)
            {
              goto LABEL_78;
            }
          }
          v72 = Item[1].klass;
          v27->HBlurTable = v72;
          v73 = wdata->pm2;
          v73->HBlurCount = get_ItemCount(v73->TypeTable2[v28], 0);
          break;
        case 0x19:
          Item = v31->Item;
          if (Item)
          {
            if (Item->klass->_2.naturalAligment < (u32)v74 || Item->klass->_2.typeHierarchy[v74 - 1] != Project_pmdRainDataTable_t_Item)
            {
              goto LABEL_78;
            }
          }
          v29 = Item[1].klass;
          v27->RainDataTable = v29;
          v30 = wdata->pm2;
          v30->RainDataCount = get_ItemCount(v30->TypeTable2[v28], 0);
          break;
        default:
          break;
      }
      v27 = wdata->pm2;
      ++v28;
    }
    while (v28 < v27->Header2->TypeTableCount);
  }
  pm3 = wdata->pm3;
  pm3->SoundFrameTable = 0;
  v76 = wdata->pm3;
  v76->SoundFrameCount = 0;
  if (!pm3dataParam)
  {
    v76->Header3 = 0;
    p_klass = &wdata->pm3->klass;
    goto LABEL_81;
  }
  v77 = pm3dataParam->pData;
  v78 = v77->header;
  v76->Header3 = v78;
  v79 = wdata->pm3;
  v80 = v77->typeTable;
  v79->TypeTable3 = v80;
  v81 = wdata->pm3;
  if (v81->Header3->TypeTableCount >= 1)
  {
    v82 = 4;
    do
    {
      v86 = *((u64 *)&v81->TypeTable3->obj.klass + v82);
      if (*(u32 *)(v86 + 16) == 4)
      {
        Item = *(void *)(v86 + 32);
        if (Item)
        {
          if (Item->klass->_2.naturalAligment < (u32)v87 || Item->klass->_2.typeHierarchy[v87 - 1] != Project_pmdFrameTable_t_Item)
          {
LABEL_78:
          }
        }
        v83 = Item[1].klass;
        v81->SoundFrameTable = v83;
        v84 = wdata->pm3;
        v84->SoundFrameCount = get_ItemCount(*((pmdTypeTable_t *)&v84->TypeTable3->obj.klass + v82), 0);
        v81 = wdata->pm3;
      }
      v85 = v82 - 3;
      ++v82;
    }
    while (v85 < v81->Header3->TypeTableCount);
  }
  return wdata;
}

// 0x1a352f0
void evtFreeWorkData1(pmdProcessWork_t *wdata) {
  dds3Basic_t **p_EffectBasicTable;
  s32 MesHandle;
  fileHandle_t *FileHandle1;
  pmdPM1_t *pm1;
  void *Instance;
  pmdLoadScene *loadScene;
  void *v9;
  s64 v10;
  pmdLoadScene *v11;
  void *bgCtrl;
  s32 endMode;
  char *sceneName;
  void *v16;
  s32 EventNo;
  void *v24;

  if (wdata)
  {
    p_EffectBasicTable = &wdata->EffectBasicTable;
    if (wdata->EffectBasicTable)
    {
      *p_EffectBasicTable = 0;
    }
    MesHandle = wdata->MesHandle;
    if ((MesHandle & 0x80000000) == 0)
    {
      itfMesMngRelease(MesHandle);
      wdata->MesHandle = -1;
    }
    fileSyncAll();
    FileHandle1 = wdata->pm1->FileHandle1;
    if (FileHandle1)
    {
      fileHandleFree(FileHandle1);
      pm1 = wdata->pm1;
      pm1->FileHandle1 = 0;
    }
    wdata->pm1data = 0;
    if (wdata->loadScene)
    {
      Instance = get_Instance(0);
      if (!op_Inequality(Instance, 0, 0))
      {
        loadScene = wdata->loadScene;
        if (!loadScene)
          goto LABEL_44;
LABEL_27:
        if (SLODWORD(loadScene->max_length) >= 1)
        {
          v10 = 0;
          while (1)
          {
            v11 = loadScene[v10];
            bgCtrl = v11->bgCtrl;
            if (!op_Inequality(v11->bgCtrl, 0, 0))
              goto LABEL_32;
            PostEffectOff(v11->bgCtrl, 0);
LABEL_33:
            evtFilterTempSettingClear(v11);
            endMode = v11->endMode;
            if (endMode == 2)
              goto LABEL_38;
            Disp(v11, endMode == 1, 0);
            if (++v10 >= SLODWORD(loadScene->max_length))
              break;
            goto LABEL_9000;
LABEL_32:
            goto LABEL_33;
LABEL_38:
            sceneName = v11->sceneName;
            UnloadSceneAsync(sceneName, 0);
            if (++v10 >= SLODWORD(loadScene->max_length))
              break;
LABEL_9000:
          }
        }
        v16 = get_Instance(0);
        if (!op_Inequality(v16, 0, 0))
          goto LABEL_44;
        v24 = get_Instance(0);
        SetPos(v24, 0.0, 0.0, 0.0);
LABEL_46:
        EventNo = wdata->EventNo;
        ScreenParam->nearClip = 16.0;
        RemovePM1LocalizeText(EventNo);
        p2sdUnLoadAllSMGFile();
        if (scrGetAfterSkipBgmFlag() == 2)
          return;
        GBWK->afterSkipPlayBgm = 0;
        return;
      }
      v9 = get_Instance(0);
      RestoreDofSetting(v9, 0);
      loadScene = wdata->loadScene;
      if (loadScene)
        goto LABEL_27;
    }
LABEL_44:
    goto LABEL_46;
  }
}

// 0x1a357f0
void evtFreeWorkData2and3(pmdProcessWork_t *wdata) {
  fileHandle_t *FileHandle2;
  pmdPM2_t *pm2;
  fileHandle_t *FileHandle3;
  pmdPM3_t *pm3;

  FileHandle2 = wdata->pm2->FileHandle2;
  if (FileHandle2)
  {
    fileHandleFree(FileHandle2);
    pm2 = wdata->pm2;
    pm2->FileHandle2 = 0;
  }
  FileHandle3 = wdata->pm3->FileHandle3;
  if (FileHandle3)
  {
    fileHandleFree(FileHandle3);
    pm3 = wdata->pm3;
    pm3->FileHandle3 = 0;
  }
}

// 0x1a358c0
void SetPMFileName(s32 eventno, s32 cutno, char **asset_name, char **pm1file, char **pm2file, char **pm3file) {
  Il2CppObject *v13;
  char *v14;
  Il2CppObject *v15;
  Il2CppObject *v16;
  char *v17;
  char *v18;
  char *v19;
  char *v20;
  s32 v21;
  s32 v22;
  s32 data;

  data = eventno;
  v13 = Box(s32, &data);
  v14 = Format("e{0:D3}", v13, 0);
  *asset_name = v14;
  v22 = eventno;
  v15 = Box(s32, &v22);
  v21 = cutno;
  v16 = Box(s32, &v21);
  v17 = Format_54759776("E{0:D3}_{1:D3}", v15, v16, 0);
  v18 = Concat_54766928(v17, "_PM1", 0);
  *pm1file = v18;
  v19 = Concat_54766928(v17, "_PM2", 0);
  *pm2file = v19;
  v20 = Concat_54766928(v17, "_PM3", 0);
  *pm3file = v20;
}

// 0x1a35a70
void evtSetDofTblFileName(s32 eventno, s32 cutno, char **dofFile) {
  Il2CppObject *v7;
  Il2CppObject *v8;
  char *v9;
  char *v10;
  s32 v11;
  s32 data;

  data = eventno;
  v7 = Box(s32, &data);
  v11 = cutno;
  v8 = Box(s32, &v11);
  v9 = Format_54759776("E{0:D3}_{1:D3}", v7, v8, 0);
  v10 = Concat_54766928(v9, "_EvtDofTbl", 0);
  *dofFile = v10;
}

// 0x1a35b50
dds3ProcessID_t *evtStart2(DDS3_PRIORITY priority, s32 eventno, s32 cutno, s32 seqno) {
  evtViewerInfo_t *v12;
  pmdProcessWork_t *v14;
  char *v17;
  char *v18;
  pmdPM1_t *pm1;
  fileHandle_t *v20;
  pmdPM2_t *pm2;
  fileHandle_t *v23;
  bool exists;
  pmdPM3_t *pm3;
  char *v28;
  char *v29;
  fileHandle_t *v30;
  char *v34;
  char *v35;
  fileHandle_t *v36;
  Il2CppObject *v37;
  Il2CppObject *v38;
  char *v39;
  char *v40;
  char *v42;
  fileHandle_t *v43;
  void *Instance;
  char *v46;
  dds3ProcessFunc_t v47;
  shutdownfuncDelegate v48;
  dds3ProcessID_t *started;
  s32 v52;
  s32 data;
  char *dofFile;
  char *pm3file;
  char *pm2file;
  char *pm1file;
  char *asset_name;

  pm1file = 0;
  asset_name = 0;
  pm2file = 0;
  dofFile = 0;
  pm3file = 0;
  BackColor = (struct sdfVector4_t)xmmword_3CFD5C0;
  v12 = Allocate(evtViewerInfo_t);
  _ctor(v12, 0);
  SetPMFileName(eventno, cutno, &asset_name, &pm1file, &pm2file, &pm3file);
  v14 = Allocate(pmdProcessWork_t);
  _ctor(v14, 0);
  if (v14)
  {
    *(_OWORD *)&GlobalParamScaleX = xmmword_3CFEE20;
  }
  v14->EventNo = eventno;
  v18 = pm1file;
  v17 = asset_name;
  PmvEventNo = eventno;
  v14->CutNo = cutno;
  v14->SeqNo = seqno - 1;
  pm1 = v14->pm1;
  v20 = fileLoad(v17, v18);
  pm1->FileHandle1 = v20;
  v14->flag |= 2u;
  LoadPM1LocalizeText(eventno);
  pm2 = v14->pm2;
  v23 = fileLoad(asset_name, pm2file);
  pm2->FileHandle2 = v23;
  v14->flag |= 4u;
  exists = Exists_36003488(_Ctrl_k__BackingField, asset_name, pm3file, 0);
  pm3 = v14->pm3;
  if (!exists)
  {
    pm3->FileHandle3 = 0;
    goto LABEL_27;
  }
  v28 = asset_name;
  v29 = pm3file;
  v30 = fileLoad(v28, v29);
  pm3->FileHandle3 = v30;
  v14->flag |= 0x10u;
LABEL_27:
  evtSetDofTblFileName(eventno, cutno, &dofFile);
  if (Exists_36003488(_Ctrl_k__BackingField, asset_name, dofFile, 0))
  {
    v34 = asset_name;
    v35 = dofFile;
    v36 = fileLoad(v34, v35);
    v14->dofTblFileHandle = v36;
    v14->flag |= 0x40u;
    if (v14->EventNo != 609)
    {
LABEL_44:
      goto LABEL_46;
    }
  }
  else
  {
    v14->dofTblFileHandle = 0;
    if (v14->EventNo != 609)
      goto LABEL_44;
  }
  if (v14->CutNo != 5)
    goto LABEL_44;
  data = eventno;
  v37 = Box(s32, &data);
  v52 = cutno;
  v38 = Box(s32, &v52);
  v39 = Format_54759776("E{0:D3}_{1:D3}", v37, v38, 0);
  v40 = Concat_54766928(v39, "_Volume", 0);
  if (Exists_36003488(_Ctrl_k__BackingField, asset_name, v40, 0))
  {
    v42 = asset_name;
    v43 = fileLoad(v42, v40);
    v14->volumeHandle = v43;
    v14->flag |= 0x80u;
    goto LABEL_44;
  }
  v14->volumeHandle = 0;
LABEL_46:
  Instance = get_Instance(0);
  ItfButtonGuideActive(Instance, 0, 0);
  itfSetGuide("", 0);
  v46 = "(ZikkiPlayMode)EventViewer";
  v47 = Allocate(dds3ProcessFunc_t);
  _ctor(v47, 0, Method_Project_evtViewer_Process1_RealPlay__, 0);
  v48 = Allocate(shutdownfuncDelegate);
  _ctor(v48, 0, Method_Project_evtViewer_Shutdown_RealPlayMode__, 0);
  started = dds3StartProcess(v46, priority, 1, 1, v47, v48, v12);
  v12->workdata = v14;
  v14->ProcessID = started;
  evtInitZikkiEvent(v12);
  return started;
}

// 0x1a36320
char *evtGetProcessName(void) {
  return "(ZikkiPlayMode)EventViewer";
}

// 0x1a36370
bool evtIsExec(s32 major, s32 cutno) {
  char *v6;
  Il2CppObject *ProcessData;
  u32 *monitor;
  dds3ProcessID_t *id;

  v6 = "(ZikkiPlayMode)EventViewer";
  id = dds3SearchProcessName(v6);
  if (!id)
    return 0;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  monitor = ProcessData[1].monitor;
  return monitor[5] == major && monitor[6] == cutno;
}
