#include "types.h"
#include "basic.h"
#include "dds3.h"
#include "dds3basic.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3scenebasic.h"
#include "dds3worldbasic.h"
#include "fld.h"
#include "itf.h"
#include "scr.h"

typedef struct dds3BasicArrayHandle_t dds3BasicArrayHandle_t;
typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sdfBinary sdfBinary;

dds3BasicFunction_t *Function;

static bool Constructor(dds3Basic_t *basic);
static void Destructor(dds3Basic_t *basic);
static bool MainProcuder(dds3Basic_t *basic);
static bool DrawProcuder(dds3Basic_t *basic);

// 0x2303170
static bool Constructor(dds3Basic_t *basic) {
  void *v3;
  Project_Basic_dds3Basic_t_WORK_c *v4;
  void **p_monitor;
  void *v7;
  s64 i;
  u64 *v9;
  s64 v10;
  char *v11;
  Il2CppObject *v12;

  v3 = Allocate(dds3SceneBasic_t);
  v4 = NewSpecific(s32, 7u);
  v3[4].klass = v4;
  _ctor(v3, 0);
  LODWORD(v3[1].klass) = -1;
  v3[1].monitor = 0;
  p_monitor = &v3[1].monitor;
  v3[2].klass = 0;
  v3[2].monitor = 0;
  v3[3].klass = 0;
  LOBYTE(v3[3].monitor) = 1;
  v7 = NewSpecific(dds3SceneBasicTable_t, 0x11u);
  v3[1].monitor = v7;
  for (i = 32; i != 168; i += 8)
  {
    v11 = *p_monitor;
    v12 = Allocate(dds3SceneBasicTable_t);
    _ctor(v12, 0);
    if (v12)
      QueryInterface(v12, *(void **)(*(u64 *)v11 + 64));
    *(u64 *)&v11[i] = v12;
    v9 = *(u64 **)((char *)*p_monitor + i);
    v9[3] = 0;
    v9 += 3;
    *((u32 *)v9 - 2) = 0;
    v10 = *(u64 *)((char *)*p_monitor + i);
    *(u64 *)(v10 + 32) = 0;
  }
  basic->workdata = v3;
  return 1;
}

// 0x23033f0
static void Destructor(dds3Basic_t *basic) {
  void *workdata;
  u64 *monitor;
  s64 i;
  dds3Basic_t *v7;
  u32 v8;
  void *v9;
  s64 v11;
  dds3Basic_t *v12;
  dds3Basic_t *v13;
  dds3Basic_t *next;
  dds3Basic_t *prev;
  void *v17;
  void *v19;
  Project_Basic_dds3Basic_t_WORK_c *klass;

  workdata = basic->workdata;
  if (!workdata)
    return;
  monitor = workdata[1].monitor;
  for (i = 0; i != 17; ++i)
  {
    while (1)
    {
      v7 = *(dds3Basic_t *)(monitor[i + 4] + 24);
      if (!v7)
        break;
      goto LABEL_12;
LABEL_16:
      v9 = v7->workpointer->workdata;
      v11 = *((u64 *)v9[1].monitor + v8 + 4);
      v12 = (v11 + 24);
      if (*(dds3Basic_t *)(v11 + 24) == v7)
      {
        next = v7->next;
        v12 = next;
        v13 = (v11 + 32);
        if (*(dds3Basic_t *)(v11 + 32) != v7)
        {
LABEL_21:
          goto LABEL_7;
        }
      }
      else
      {
        v13 = (v11 + 32);
        if (*(dds3Basic_t *)(v11 + 32) != v7)
          goto LABEL_21;
      }
      prev = v7->prev;
      v13 = prev;
LABEL_7:
      dds3Delete(v7);
      *(u32 *)(v11 + 16) = (*(u32 *)(v11 + 16) - 1) & ~((*(u32 *)(v11 + 16) - 1) >> 31);
      goto LABEL_8;
LABEL_12:
      v8 = GETBASICTYPEL(v7);
      if (v8 - 2 <= 0xE)
        goto LABEL_16;
LABEL_8:
      monitor = workdata[1].monitor;
    }
  }
  goto LABEL_29;
LABEL_30:
  v17 = basic->workdata;
  if (!v17)
    goto LABEL_38;
  goto LABEL_38;
LABEL_29:
  goto LABEL_30;
LABEL_38:
  klass = v17[3].klass;
  v19 = v17 + 3;
  if (klass)
  {
    v19->klass = 0;
  }
  v19->klass = 0;
}

// 0x2303800
static bool MainProcuder(dds3Basic_t *basic) {
  void *workdata;
  s64 i;
  s64 v6;
  s64 v7;
  s64 v8;
  s64 v9;

  workdata = basic->workdata;
  if (workdata)
  {
    for (i = 0; i != 17; ++i)
    {
      v6 = *((u64 *)workdata[1].monitor + i + 4);
      if (*(u32 *)(v6 + 16))
      {
        v7 = *(u64 *)(v6 + 24);
        v8 = *(u64 *)(v7 + 40);
        if (v8)
        {
          if (*(u64 *)(v8 + 32))
          {
            do
            {
              v9 = *(u64 *)(v7 + 64);
              (*(*(u64 *)(*(u64 *)(v7 + 40) + 32) + 24))(*(u64 *)(*(u64 *)(*(u64 *)(v7 + 40) + 32) + 64));
              v7 = v9;
            }
            while (v9);
          }
        }
      }
    }
  }
  return workdata != 0;
}

// 0x2303900
static bool DrawProcuder(dds3Basic_t *basic) {
  void *workdata;
  s64 v5;
  s64 v6;
  s64 v7;
  s64 v8;

  workdata = basic->workdata;
  if (workdata)
  {
    if (LOBYTE(workdata[3].monitor))
    {
      v5 = *((u64 *)workdata[1].monitor + 6);
      if (*(u32 *)(v5 + 16))
      {
        v6 = *(u64 *)(v5 + 24);
        v7 = *(u64 *)(v6 + 40);
        if (v7)
        {
          if (*(u64 *)(v7 + 40))
          {
            do
            {
              v8 = *(u64 *)(v6 + 64);
              (*(*(u64 *)(*(u64 *)(v6 + 40) + 40) + 24))(*(u64 *)(*(u64 *)(*(u64 *)(v6 + 40) + 40) + 64));
              v6 = v8;
            }
            while (v8);
          }
        }
      }
    }
  }
  return workdata != 0;
}

// 0x2303710
void dds3SceneBasicFreeScene(dds3Basic_t *pBasic) {

}

// 0x23039e0
void dds3SceneBasicVisible(dds3Basic_t *basic, bool visible) {
  void *workdata;

  workdata = basic->workdata;
  if (workdata)
  {
    LOBYTE(workdata[3].monitor) = visible;
  }
}

// 0x22fc1b0
dds3Basic_t *dds3SceneBasicAdd(BASIC_TYPE type) {
  dds3Basic_t *ControlScene;
  dds3Basic_t *v4;
  void *workdata;
  s64 v7;
  dds3Basic_t *v8;
  dds3Basic_t *v9;
  s64 v10;
  void **v11;
  void *v12;
  dds3Basic_t *p_prev;

  if ((u32)(type - 2) > 0xE)
    return 0;
  ControlScene = dds3GetControlScene();
  if (!ControlScene)
    return 0;
  v4 = ControlScene;
  workdata = ControlScene->workdata;
  v7 = *((u64 *)workdata[1].monitor + (u32)type + 4);
  v8 = dds3Add(type);
  v9 = v8;
  if (!v8)
    return v9;
  v8->workpointer = v4;
  v11 = (v7 + 32);
  v10 = *(u64 *)(v7 + 32);
  if (v10)
  {
    *(u64 *)(v10 + 64) = v9;
    v12 = *v11;
    v9->prev = (dds3Basic_t *)*v11;
    p_prev = &v9->prev;
  }
  else
  {
    v12 = v9;
    *(u64 *)(v7 + 24) = v9;
    p_prev = (v7 + 24);
  }
  *(u64 *)(v7 + 32) = v9;
  ++*(u32 *)(v7 + 16);
  return v9;
}

// 0x22fc4c0
void dds3SceneBasicDelete(dds3Basic_t *basic) {
  u32 v3;
  void *workdata;
  s64 v6;
  dds3Basic_t *v7;
  dds3Basic_t *v8;
  dds3Basic_t *next;
  dds3Basic_t *prev;

  if (basic)
  {
    v3 = GETBASICTYPEL(basic);
    if (v3 - 2 <= 0xE)
    {
      workdata = basic->workpointer->workdata;
      v6 = *((u64 *)workdata[1].monitor + v3 + 4);
      v7 = (v6 + 24);
      if (*(dds3Basic_t *)(v6 + 24) == basic)
      {
        next = basic->next;
        v7 = next;
        v8 = (v6 + 32);
        if (*(dds3Basic_t *)(v6 + 32) != basic)
        {
LABEL_10:
LABEL_11:
          dds3Delete(basic);
          *(u32 *)(v6 + 16) = (*(u32 *)(v6 + 16) - 1) & ~((*(u32 *)(v6 + 16) - 1) >> 31);
          return;
        }
      }
      else
      {
        v8 = (v6 + 32);
        if (*(dds3Basic_t *)(v6 + 32) != basic)
          goto LABEL_10;
      }
      prev = basic->prev;
      v8 = prev;
      goto LABEL_11;
    }
  }
}

// 0x2303a80
dds3Basic_t *SetActiveCamera(dds3Basic_t *pSceneBasic, dds3Basic_t *pCameraBasic) {
  void *workdata;
  s64 naturalAligment;
  void *v7;
  s64 v8;
  dds3Basic_t *klass;

  workdata = pSceneBasic->workdata;
  if (workdata)
  {
    if (workdata->klass->_2.naturalAligment < (u32)naturalAligment || workdata->klass->_2.typeHierarchy[naturalAligment - 1] != dds3SceneBasic_t)
    {
      v7 = pSceneBasic->workdata;
      goto LABEL_16;
    }
  }
  v7 = pSceneBasic->workdata;
  if (!v7)
    goto LABEL_14;
  if (v7->klass->_2.naturalAligment < (u32)v8 || v7->klass->_2.typeHierarchy[v8 - 1] != dds3SceneBasic_t)
  {
LABEL_16:
  }
LABEL_14:
  klass = (dds3Basic_t *)v7[2].klass;
  workdata[2].klass = (Project_Basic_dds3Basic_t_WORK_c *)pCameraBasic;
  return klass;
}

// 0x2303bc0
dds3Basic_t *dds3SceneBasicGetActiveCamera(dds3Basic_t *pBasic) {
  dds3Basic_t *workdata;
  s64 naturalAligment;

  workdata = (dds3Basic_t *)(pBasic)->workdata;
  if (workdata)
  {
    LOBYTE(workdata[2].next) < (u32)naturalAligment || *((dds3SceneBasic_t **)(workdata)[1].worknext + naturalAligment - 1) != dds3SceneBasic_t;
  }
  return workdata[4];
}

// 0x2303c50
dds3Basic_t *dds3SceneBasicSetActiveUnit(dds3Basic_t *pSceneBasic, dds3Basic_t *pUnitBasic) {
  void *workdata;
  s64 naturalAligment;
  void *v7;
  s64 v8;
  dds3Basic_t *monitor;

  workdata = pSceneBasic->workdata;
  if (workdata)
  {
    if (workdata->klass->_2.naturalAligment < (u32)naturalAligment || workdata->klass->_2.typeHierarchy[naturalAligment - 1] != dds3SceneBasic_t)
    {
      v7 = pSceneBasic->workdata;
      goto LABEL_16;
    }
  }
  v7 = pSceneBasic->workdata;
  if (!v7)
    goto LABEL_14;
  if (v7->klass->_2.naturalAligment < (u32)v8 || v7->klass->_2.typeHierarchy[v8 - 1] != dds3SceneBasic_t)
  {
LABEL_16:
  }
LABEL_14:
  monitor = (dds3Basic_t *)v7[2].monitor;
  workdata[2].monitor = pUnitBasic;
  return monitor;
}

// 0x2303d90
dds3Basic_t *dds3SceneBasicGetActiveUnit(dds3Basic_t *pSceneBasic) {
  dds3Basic_t *workdata;
  s64 naturalAligment;

  workdata = (dds3Basic_t *)pSceneBasic->workdata;
  if (workdata)
  {
    LOBYTE(workdata[2].next) < (u32)naturalAligment || *((dds3SceneBasic_t **)(workdata)[1].worknext + naturalAligment - 1) != dds3SceneBasic_t;
  }
  return workdata[5];
}

// 0x2303e10
u32 dds3SceneBasicSearchSerialID_Used(u32 serialID) {
  dds3Basic_t *ControlScene;
  dds3Basic_t *v6;
  bool v8;
  s64 v9;
  const Il2CppType **parameters;
  s64 naturalAligment;
  s64 v12;
  s64 v13;
  s64 v14;
  s64 v15;
  s64 v16;
  s64 v18;
  s64 v20;
  s64 v21;
  s64 v22;

  ActiveScene = dds3GetActiveScene();
  ControlScene = dds3GetControlScene();
  v6 = ControlScene;
  v8 = ActiveScene == ControlScene || ControlScene == 0;
  if ()
  {
    while (1)
    {
      v9 = 1;
      while (1)
      {
        parameters = ActiveScene->parameters;
        if (parameters)
        {
          if (LOBYTE((*parameters)[19].data) < (u32)naturalAligment || *(dds3SceneBasic_t **)(*(u64 *)&(*parameters)[12].bits + 8 * naturalAligment - 8) != dds3SceneBasic_t)
          {
            goto LABEL_60;
          }
        }
        v12 = *((u64 *)&parameters[3][2].data + v9);
        if (*(u32 *)(v12 + 16))
          break;
LABEL_28:
        if (!v8)
        {
          parameters = v6->workdata;
          if (parameters)
          {
            if (LOBYTE((*parameters)[19].data) < (u32)v14 || *(dds3SceneBasic_t **)(*(u64 *)&(*parameters)[12].bits + 8 * v14 - 8) != dds3SceneBasic_t)
            {
              goto LABEL_60;
            }
          }
          v15 = *((u64 *)&parameters[3][2].data + v9);
          if (*(u32 *)(v15 + 16))
          {
            v16 = *(u64 *)(v15 + 24);
            while (*(u32 *)(v16 + 20) != serialID)
            {
              v16 = *(u64 *)(v16 + 64);
              if (!v16)
                goto LABEL_15;
            }
            goto LABEL_13;
          }
        }
LABEL_15:
        if (++v9 == 17)
          return serialID;
      }
      v13 = *(u64 *)(v12 + 24);
      while (*(u32 *)(v13 + 20) != serialID)
      {
        v13 = *(u64 *)(v13 + 64);
        if (!v13)
          goto LABEL_28;
      }
LABEL_13:
      serialID = (serialID + 1) & 0xFFF;
    }
  }
  if (!v8)
  {
    v18 = 1;
LABEL_46:
LABEL_47:
    parameters = v6->workdata;
    if (parameters)
      goto LABEL_51;
    goto LABEL_53;
    while (1)
    {
      parameters = v6->workdata;
      if (parameters)
      {
LABEL_51:
        if (LOBYTE((*parameters)[19].data) < (u32)v20 || *(dds3SceneBasic_t **)(*(u64 *)&(*parameters)[12].bits + 8 * v20 - 8) != dds3SceneBasic_t)
        {
LABEL_60:
        }
      }
LABEL_53:
      v21 = *((u64 *)&parameters[3][2].data + v18);
      if (*(u32 *)(v21 + 16))
      {
        v22 = *(u64 *)(v21 + 24);
        while (*(u32 *)(v22 + 20) != serialID)
        {
          v22 = *(u64 *)(v22 + 64);
          if (!v22)
            goto LABEL_44;
        }
        v18 = 1;
        serialID = ((u16)serialID + 1) & 0xFFF;
        goto LABEL_46;
      }
      else
      {
LABEL_44:
        if (++v18 == 17)
          return serialID;
        goto LABEL_46;
      }
      goto LABEL_47;
    }
  }
  return serialID;
}

// 0x22fc9d0
dds3Basic_t *dds3SceneBasicSearch(dds3Basic_t *pBasic, u32 serialID, u32 type) {
  void *workdata;
  s64 v9;
  dds3Basic_t *result;

  workdata = pBasic->workdata;
  v9 = *((u64 *)workdata[1].monitor + type + 4);
  if (!*(u32 *)(v9 + 16))
    return 0;
  result = *(dds3Basic_t *)(v9 + 24);
  do
  {
    if (result->serialID == serialID)
      break;
    result = result->next;
  }
  while (result);
  return result;
}

// 0x2304220
dds3BasicArrayHandle_t *dds3SceneBasicGetList(dds3Basic_t *pBasic, u32 type) {
  Il2CppObject *v5;
  void *workdata;
  s64 v9;
  dds3BasicArrayHandle_t *BasicArrayHandle;
  dds3Basic_t *next;
  dds3Basic_t *v15;
  dds3BasicArrayHandle_t *hndl;

  v5 = Allocate(dds3BasicArrayHandle_t);
  _ctor(v5, 0);
  workdata = pBasic->workdata;
  if (!*(u32 *)(*((u64 *)workdata[1].monitor + type + 4) + 16))
    return 0;
  v9 = type;
  BasicArrayHandle = dds3GetBasicArrayHandle(0);
  next = *(dds3Basic_t *)(*((u64 *)workdata[1].monitor + v9 + 4) + 24);
  v15 = next;
  hndl = BasicArrayHandle;
  do
  {
    dds3AddBasicArray(hndl, 1);
    dds3SetBasicArray(hndl, v15);
    next = next->next;
    v15 = next;
  }
  while (next);
  return BasicArrayHandle;
}

// 0x23046b0
void dds3SceneBasicMakeScene(dds3Basic_t *pBasic, char *akey) {
  fldLoadFile();
}

// 0x2304730
void dds3SceneBasicMakeScene_FromMemory(dds3Basic_t *pBasic, s32 field, s32 area, void *pF1, void *pF2, sdfBinary *pTB, sdfBinary *pBF) {
  fldLoadFile_FromMemory(field, area, pF1, pF2, pTB, pBF);
}

// 0x23047e0
bool dds3SceneBasicLoadScriptFile(dds3Basic_t *scene, char *scrfile, char *akey) {
  void *workdata;
  s64 naturalAligment;
  void *Asset;
  u8 *bytes;
  void *v15;

  workdata = scene->workdata;
  if (workdata)
  {
    if (workdata->klass->_2.naturalAligment < (u32)naturalAligment || workdata->klass->_2.typeHierarchy[naturalAligment - 1] != dds3SceneBasic_t)
    {
      Asset = workdata;
      goto LABEL_29;
    }
  }
  if (scrfile)
  {
    if (IsLoad(Dependent, akey, 0))
    {
      goto LABEL_11;
    }
    Load(Dependent, akey, akey);
    LoadSyncAll(_Ctrl_k__BackingField, 0);
LABEL_11:
LABEL_13:
    Asset = LoadAsset(_Ctrl_k__BackingField, akey, scrfile, 0);
    {
      bytes = get_bytes(Asset, 0);
      workdata[3].klass = (Project_Basic_dds3Basic_t_WORK_c *)bytes;
      v15 = workdata + 3;
      return v15->klass != 0;
    }
LABEL_29:
    goto LABEL_13;
  }
  return 0;
}

// 0x2304a40
bool dds3SceneBasicLoadScriptFile_FromMem(dds3Basic_t *scene, void *mem) {
  void *workdata;
  u8 *data;

  workdata = scene->workdata;
  if (op_Equality(mem, 0, 0))
    return 0;
  data = mem->data;
  if (data)
  {
    workdata[3].klass = (Project_Basic_dds3Basic_t_WORK_c *)data;
    return 1;
  }
  return 0;
}

// 0x2303750
void dds3SceneBasicReleaseScriptFile(dds3Basic_t *scene) {
  void *workdata;
  void *v5;
  Project_Basic_dds3Basic_t_WORK_c *klass;

  workdata = scene->workdata;
  klass = workdata[3].klass;
  v5 = workdata + 3;
  if (klass)
  {
    v5->klass = 0;
  }
  v5->klass = 0;
}

// 0x2304b50
dds3ProcessID_t *dds3SceneBasicStartScript(dds3Basic_t *scene, char *procname) {
  void *workdata;
  u8 *klass;
  void *devilReportWin;
  void *Instance;
  s32 v16;
  s32 v17;

  workdata = scene->workdata;
  if (!procname)
    return 0;
  klass = workdata[3].klass;
  if (!klass)
    return 0;
  if (!op_Inequality(fldUI, 0, 0))
  {
LABEL_17:
    goto LABEL_19;
  }
  devilReportWin = fldUI->devilReportWin;
  if (!op_Inequality(devilReportWin, 0, 0))
    goto LABEL_17;
  WinClose(fldUI->devilReportWin, 0);
LABEL_19:
  Instance = get_Instance(0);
  ItfButtonGuideActive(Instance, 0, 0);
  HDrawSync = 0;
  MiniMapUpdateFlag = 1;
  v16 = scrSearchProcedureName(klass, procname);
  if (v16 < 0)
    return 0;
  v17 = v16;
  if (dds3SearchProcessName(procname))
    return 0;
  return scrStartScript2(1002, klass, v17, 1);
}

// 0x2304ee0
void dds3SceneBasicEndScript(dds3Basic_t *scene, char *procname) {
  dds3ProcessID_t *v4;
  dds3ProcessID_t *id;

  v4 = Allocate(dds3ProcessID_t);
  _ctor(v4, 0);
  if (procname)
  {
    id = dds3SearchProcessName(procname);
    if (id)
    {
      dds3KillProcess(id, 0);
    }
  }
}

// 0x2304fa0
bool dds3SceneBasicExistBasicFromType(dds3Basic_t *scene, BASIC_TYPE type, dds3Basic_t *target) {
  bool result;
  void *workdata;
  dds3Basic_t *next;

  result = 0;
  if (target && scene)
  {
    workdata = scene->workdata;
    next = *(dds3Basic_t *)(*((u64 *)workdata[1].monitor + type + 4) + 24);
    if (next)
    {
      do
      {
        result = next == target;
        if (next == target)
          break;
        next = next->next;
      }
      while (next);
    }
    else
    {
      return 0;
    }
  }
  return result;
}

// 0x2305080
bool dds3SceneBasicExistBasic(dds3Basic_t *scene, dds3Basic_t *target) {
  dds3Basic_t *v5;
  void *workdata;
  u64 *monitor;
  dds3Basic_t *next;
  dds3Basic_t *v10;
  dds3Basic_t *v11;
  dds3Basic_t *v12;
  dds3Basic_t *v13;
  dds3Basic_t *v14;
  dds3Basic_t *v15;
  dds3Basic_t *v16;
  dds3Basic_t *v17;
  dds3Basic_t *v18;
  dds3Basic_t *v19;
  dds3Basic_t *v20;
  dds3Basic_t *v21;
  dds3Basic_t *v22;
  dds3Basic_t *v23;
  dds3Basic_t *v24;
  dds3Basic_t *v25;
  bool result;

  if (!scene)
    return 0;
  v5 = target;
  if (!target)
    return 0;
  workdata = scene->workdata;
  monitor = workdata[1].monitor;
  next = *(dds3Basic_t *)(monitor[4] + 24);
  if (next)
  {
    while (next != v5)
    {
      next = next->next;
      if (!next)
        goto LABEL_11;
    }
    return 1;
  }
LABEL_11:
  v10 = *(dds3Basic_t *)(monitor[5] + 24);
  if (v10)
  {
    while (v10 != v5)
    {
      v10 = v10->next;
      if (!v10)
        goto LABEL_14;
    }
    return 1;
  }
LABEL_14:
  v11 = *(dds3Basic_t *)(monitor[6] + 24);
  if (v11)
  {
    while (v11 != v5)
    {
      v11 = v11->next;
      if (!v11)
        goto LABEL_17;
    }
    return 1;
  }
LABEL_17:
  v12 = *(dds3Basic_t *)(monitor[7] + 24);
  if (v12)
  {
    while (v12 != v5)
    {
      v12 = v12->next;
      if (!v12)
        goto LABEL_20;
    }
    return 1;
  }
LABEL_20:
  v13 = *(dds3Basic_t *)(monitor[8] + 24);
  if (v13)
  {
    while (v13 != v5)
    {
      v13 = v13->next;
      if (!v13)
        goto LABEL_23;
    }
    return 1;
  }
LABEL_23:
  v14 = *(dds3Basic_t *)(monitor[9] + 24);
  if (v14)
  {
    while (v14 != v5)
    {
      v14 = v14->next;
      if (!v14)
        goto LABEL_26;
    }
    return 1;
  }
LABEL_26:
  v15 = *(dds3Basic_t *)(monitor[10] + 24);
  if (v15)
  {
    while (v15 != v5)
    {
      v15 = v15->next;
      if (!v15)
        goto LABEL_29;
    }
    return 1;
  }
LABEL_29:
  v16 = *(dds3Basic_t *)(monitor[11] + 24);
  if (v16)
  {
    while (v16 != v5)
    {
      v16 = v16->next;
      if (!v16)
        goto LABEL_32;
    }
    return 1;
  }
LABEL_32:
  v17 = *(dds3Basic_t *)(monitor[12] + 24);
  if (v17)
  {
    while (v17 != v5)
    {
      v17 = v17->next;
      if (!v17)
        goto LABEL_35;
    }
    return 1;
  }
LABEL_35:
  v18 = *(dds3Basic_t *)(monitor[13] + 24);
  if (v18)
  {
    while (v18 != v5)
    {
      v18 = v18->next;
      if (!v18)
        goto LABEL_38;
    }
    return 1;
  }
LABEL_38:
  v19 = *(dds3Basic_t *)(monitor[14] + 24);
  if (v19)
  {
    while (v19 != v5)
    {
      v19 = v19->next;
      if (!v19)
        goto LABEL_41;
    }
    return 1;
  }
LABEL_41:
  v20 = *(dds3Basic_t *)(monitor[15] + 24);
  if (v20)
  {
    while (v20 != v5)
    {
      v20 = v20->next;
      if (!v20)
        goto LABEL_44;
    }
    return 1;
  }
LABEL_44:
  v21 = *(dds3Basic_t *)(monitor[16] + 24);
  if (v21)
  {
    while (v21 != v5)
    {
      v21 = v21->next;
      if (!v21)
        goto LABEL_47;
    }
    return 1;
  }
LABEL_47:
  v22 = *(dds3Basic_t *)(monitor[17] + 24);
  if (v22)
  {
    while (v22 != v5)
    {
      v22 = v22->next;
      if (!v22)
        goto LABEL_50;
    }
    return 1;
  }
LABEL_50:
  v23 = *(dds3Basic_t *)(monitor[18] + 24);
  if (v23)
  {
    while (v23 != v5)
    {
      v23 = v23->next;
      if (!v23)
        goto LABEL_53;
    }
    return 1;
  }
LABEL_53:
  v24 = *(dds3Basic_t *)(monitor[19] + 24);
  if (v24)
  {
    while (v24 != v5)
    {
      v24 = v24->next;
      if (!v24)
        goto LABEL_56;
    }
    return 1;
  }
LABEL_56:
  v25 = *(dds3Basic_t *)(monitor[20] + 24);
  if (!v25)
    return 0;
  do
  {
    result = v25 == v5;
    if (v25 == v5)
      break;
    v25 = v25->next;
  }
  while (v25);
  return result;
}

// 0x2305350
void dds3SetMapNo(dds3Basic_t *scene, s32 mapno) {
  void *workdata;

  if (scene)
  {
    workdata = scene->workdata;
    LODWORD(workdata[1].klass) = mapno;
  }
}

// 0x23053f0
s32 dds3GetMapNo(dds3Basic_t *scene) {
  s32 *workdata;

  if (!scene)
    return -1;
  workdata = scene->workdata;
  return workdata[4];
}

// 0x2305490
dds3Basic_t *dds3SceneBasicSearchNameAndType(dds3Basic_t *scene, u32 type, char *name) {
  dds3Basic_t *next;
  void *workdata;
  s64 v10;
  char *v11;
  char *v12;

  next = 0;
  if (scene && name)
  {
    workdata = scene->workdata;
    next = *(dds3Basic_t *)(*((u64 *)workdata[1].monitor + type + 4) + 24);
    if (next)
    {
      v10 = type;
      while (1)
      {
        v11 = next->name;
        if (!IsNullOrEmpty(v11, 0) && Equals_54828784(v11, name, 0))
          break;
        next = next->next;
        if (!next)
        {
          for (next = *(dds3Basic_t *)(*((u64 *)workdata[1].monitor + v10 + 4) + 24); next; next = next->next)
          {
            v12 = next->name;
            if (!IsNullOrEmpty(v12, 0) && Contains(v12, name, 0))
              break;
          }
          return next;
        }
      }
    }
  }
  return next;
}

// 0x23055d0
dds3Basic_t *dds3SceneBasicSearchName(dds3Basic_t *scene, char *name) {
  dds3Basic_t *result;
  dds3Basic_t *v7;
  dds3Basic_t *v10;
  dds3Basic_t *v13;
  dds3Basic_t *v15;
  dds3Basic_t *v17;
  dds3Basic_t *v19;
  dds3Basic_t *v21;
  dds3Basic_t *v23;
  dds3Basic_t *v25;
  dds3Basic_t *v27;
  dds3Basic_t *v29;
  dds3Basic_t *v31;
  dds3Basic_t *v33;
  dds3Basic_t *v35;
  dds3Basic_t *v37;
  dds3Basic_t *v39;
  dds3Basic_t *v41;

  result = 0;
  if (name)
  {
    v7 = scene;
    if (scene)
    {
      result = dds3SceneBasicSearchNameAndType(scene, 0, name);
      if (result)
        return result;
      v10 = scene;
      result = dds3SceneBasicSearchNameAndType(scene, 1u, name);
      if (result)
        return result;
      v13 = scene;
      result = dds3SceneBasicSearchNameAndType(v13, 2u, name);
      if (!result)
      {
        v15 = scene;
        result = dds3SceneBasicSearchNameAndType(v15, 3u, name);
        if (!result)
        {
          v17 = scene;
          result = dds3SceneBasicSearchNameAndType(v17, 4u, name);
          if (!result)
          {
            v19 = scene;
            result = dds3SceneBasicSearchNameAndType(v19, 5u, name);
            if (!result)
            {
              v21 = scene;
              result = dds3SceneBasicSearchNameAndType(v21, 6u, name);
              if (!result)
              {
                v23 = scene;
                result = dds3SceneBasicSearchNameAndType(v23, 7u, name);
                if (!result)
                {
                  v25 = scene;
                  result = dds3SceneBasicSearchNameAndType(v25, 8u, name);
                  if (!result)
                  {
                    v27 = scene;
                    result = dds3SceneBasicSearchNameAndType(v27, 9u, name);
                    if (!result)
                    {
                      v29 = scene;
                      result = dds3SceneBasicSearchNameAndType(v29, 0xAu, name);
                      if (!result)
                      {
                        v31 = scene;
                        result = dds3SceneBasicSearchNameAndType(v31, 0xBu, name);
                        if (!result)
                        {
                          v33 = scene;
                          result = dds3SceneBasicSearchNameAndType(v33, 0xCu, name);
                          if (!result)
                          {
                            v35 = scene;
                            result = dds3SceneBasicSearchNameAndType(v35, 0xDu, name);
                            if (!result)
                            {
                              v37 = scene;
                              result = dds3SceneBasicSearchNameAndType(v37, 0xEu, name);
                              if (!result)
                              {
                                v39 = scene;
                                result = dds3SceneBasicSearchNameAndType(v39, 0xFu, name);
                                if (!result)
                                {
                                  v41 = scene;
                                  return dds3SceneBasicSearchNameAndType(v41, 0x10u, name);
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return result;
}
