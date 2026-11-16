#include "types.h"
#include "FILE_TYPE.h"
#include "dds3kernelcore.h"
#include "file.h"
#include "fileEndCallback_t.h"
#include "kernel.h"
#include "libsdf.h"
#include "sdfpac.h"
#include "sdfsystem.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct fileHandle_t fileHandle_t;
typedef struct fileMngCb_t fileMngCb_t;
typedef struct pacFileHandle_t pacFileHandle_t;
typedef struct sdfPacDecodeResrcHandle_t sdfPacDecodeResrcHandle_t;

struct fileMngCb_t {
    fileHandle_t *queue;
    fileHandle_t *queueTail;
};

static fileMngCb_t *fileMngCb;

static bool pacHandleFree_(pacFileHandle_t *pacHandle);
static void LinkQueue(fileHandle_t *fileHandle, FILE_TYPE type, char *abKey, char *assetName, fileEndCallback_t endCallback, void *callbackParm);
static void UnlinkQueue(fileHandle_t *fileHandle);
static dds3ProcessFunc_t ManagerProc(dds3ProcessID_t *procId);

// 0x1b89960
static bool pacHandleFree_(pacFileHandle_t *pacHandle) {
  s32 phase;

  phase = pacHandle->phase;
  if (phase == 3)
  {
    sdfPacFree(pacHandle->decodeCb);
    if (pacHandle->abLoad)
    {
      Unload(Dependent, pacHandle->abKey, 0);
    }
  }
  return phase != 3;
}

// 0x1b89a00
bool pacHandleFree(pacFileHandle_t *pacHandle) {
  s32 phase;

  phase = pacHandle->phase;
  if (phase != 3)
    return phase != 3;
  sdfPacFree(pacHandle->decodeCb);
  if (!pacHandle->abLoad)
    return phase != 3;
  Unload(Dependent, pacHandle->abKey, 0);
  return 0;
}

// 0x1b89b10
bool fileHandleFree(fileHandle_t *fileHandle) {
  if (fileHandle->type != 1)
  {
    if (fileHandle->phase == 3)
      goto LABEL_13;
    return 1;
  }
  if (fileHandle->phase != 3)
    return 1;
  sdfPacFree(fileHandle[1].klass);
LABEL_13:
  if (fileHandle->abLoad)
  {
    Unload(Dependent, fileHandle->abKey, 0);
  }
  return 0;
}

// 0x1b89c60
static void LinkQueue(fileHandle_t *fileHandle, FILE_TYPE type, char *abKey, char *assetName, fileEndCallback_t endCallback, void *callbackParm) {
  fileMngCb_t *fileMngCb_local;
  bool v17;
  fileHandle_t *p_queueTail;
  fileHandle_t *queueTail;
  fileHandle_t *p_next;
  fileHandle_t *v21;

  fileHandle->type = type;
  fileHandle->abKey = abKey;
  fileHandle->phase = 0;
  fileMngCb_local = fileMngCb;
  fileHandle->assetName = assetName;
  v17 = Exists(_Ctrl_k__BackingField, abKey, 0);
  fileHandle->endCallback = endCallback;
  fileHandle->abLoad = !v17;
  fileHandle->endCallbackParm = callbackParm;
  queueTail = fileMngCb_local->queueTail;
  p_queueTail = &fileMngCb_local->queueTail;
  p_next = &queueTail->next;
  if (queueTail)
    v21 = p_next;
  else
    v21 = p_queueTail - 1;
  v21 = fileHandle;
  p_queueTail = fileHandle;
  if (fileHandle->abLoad)
  {
    Load(Dependent, abKey, abKey);
  }
}

// 0x1b89e50
static void UnlinkQueue(fileHandle_t *fileHandle) {
  fileMngCb_t *fileMngCb_local;
  fileMngCb_t *p_fields;
  fileHandle_t *queue;
  fileHandle_t *v7;
  fileHandle_t *next;
  fileHandle_t *v9;

  goto LABEL_3;
  do
  {
LABEL_7:
    v7 = queue;
    queue = queue->next;
  }
  while (queue != fileHandle);
  next = fileHandle->next;
  v7->next = next;
  if (!fileHandle->next)
    goto LABEL_11;
  return;
LABEL_3:
  fileMngCb_local = fileMngCb;
  p_fields = &fileMngCb_local->fields;
  queue = fileMngCb_local->queue;
  if (queue != fileHandle)
    goto LABEL_7;
  v9 = fileHandle->next;
  p_fields->queue = v9;
  v7 = 0;
  if (!fileHandle->next)
  {
LABEL_11:
    fileMngCb_local->queueTail = v7;
  }
}

// 0x1b89f50
pacFileHandle_t *pacLoadEx(char *abKey, char *assetName, sdfPacCallback_t callback, fileEndCallback_t endCallback, void *callbackParm) {
  Il2CppObject *v11;
  sdfPacDecodeCb_t *v12;

  v11 = Allocate(pacFileHandle_t);
  v12 = Allocate(sdfPacDecodeCb_t);
  _ctor(v12, 0);
  v11[5].monitor = v12;
  _ctor(v11, 0);
  sdfPacInit(v11[5].monitor, callback);
  LinkQueue(v11, 1u, abKey, assetName, endCallback, callbackParm);
  return (pacFileHandle_t *)v11;
}

// 0x1b8a100
pacFileHandle_t *pacLoad(char *abKey, char *assetName) {
  return pacLoadEx(abKey, assetName, 0, 0, 0);
}

// 0x1b8a180
pacFileHandle_t *pacLoad_2(char *filename) {
  return pacLoadEx(filename, filename, 0, 0, 0);
}

// 0x1b8a250
fileHandle_t *fileLoadEx(char *abKey, char *assetName, fileEndCallback_t endCallback, void *callbackParm) {
  Il2CppObject *v9;

  v9 = Allocate(fileHandle_t);
  _ctor(v9, 0);
  LinkQueue(v9, 0, abKey, assetName, endCallback, callbackParm);
  return (fileHandle_t *)v9;
}

// 0x1b8a320
fileHandle_t *fileLoad(char *abKey, char *assetName) {
  Il2CppObject *v6;

  v6 = Allocate(fileHandle_t);
  _ctor(v6, 0);
  LinkQueue(v6, 0, abKey, assetName, 0, 0);
  return (fileHandle_t *)v6;
}

// 0x1b8a430
fileHandle_t *Load(char *filename) {
  char *v5;
  char *v6;

  v5 = filename;
  v6 = filename;
  return fileLoad(v5, v6);
}

// 0x1b8a4c0
void *fileGetMemHandle(fileHandle_t *fileHandle) {
  return fileHandle->topPtr;
}

// 0x1b8a4d0
void *fileGetLoadPtr(fileHandle_t *fileHandle) {
  return fileHandle->topPtr;
}

// 0x1b8a4e0
bool fileCheckEnd(fileHandle_t *fileHandle) {
  if (fileHandle->type != 1)
    return fileHandle->phase == 3;
  return LOBYTE(fileHandle[1].monitor) && fileHandle->phase == 3;
}

// 0x1b8a5b0
bool pacCheckEnd(pacFileHandle_t *pacHandle) {
  return pacHandle->decodeEnd && pacHandle->phase == 3;
}

// 0x1b8a5d0
void fileSync(fileHandle_t *fileHandle) {
  while (1)
  {
    if (fileHandle->type != 1)
      break;
    if (LOBYTE(fileHandle[1].monitor))
      break;
LABEL_18:
    fileManager(1);
  }
  if (fileHandle->phase != 3)
    goto LABEL_18;
}

// 0x1b8a7c0
void pacSync(pacFileHandle_t *pacFileHandle) {
  fileHandle_t *v4;

  v4 = pacFileHandle;
  fileSync(v4);
}

// 0x1b8a840
void fileSyncAll(void) {
  goto LABEL_3;
  while (1)
  {
LABEL_10:
    fileManager(1);
    if (!fileMngCb->queue)
      return;
  }
LABEL_3:
  if (fileMngCb->queue)
    goto LABEL_10;
}

// 0x1b8a950
bool fileManager(bool sync) {
  file **v2;
  _BOOL4 v3;
  fileHandle_t *queue;
  pacFileHandle_t **v7;
  UnityEngine_Object_c **v8;
  void *p_topPtr;
  void *AssetAsync;
  s32 phase;
  file *v14;
  s64 naturalAligment;
  u64 *p_request;
  void *topPtr;
  u32 v18;
  Il2CppClass **typeHierarchy;
  s64 v21;
  void *v22;
  UnityEngine_Object_c *v23;
  pacFileHandle_t **v24;
  void *file;
  sdfBinary *v26;
  void *v27;
  _BOOL4 v28;
  UnityEngine_Object_c **v29;
  file **v30;
  sdfBinary *v31;
  sdfBinary *v32;
  s32 Length;
  void *asset;
  fileEndCallback_t v35;
  fileEndCallback_t endCallback;
  fileMngCb_t *v43;

  v2 = &file;
  v3 = sync;
  queue = fileMngCb->queue;
  if (queue)
  {
    v43 = fileMngCb;
    v7 = &pacFileHandle_t;
    v8 = &UnityEngine_Object;
    while (1)
    {
      phase = queue->phase;
      if (phase == 2)
        break;
      if (phase == 1)
      {
        p_request = &queue->request;
        if (get_isDone(queue->request, 0))
        {
          asset = get_asset(queue->request, 0);
          goto LABEL_45;
        }
        if (!v3)
          goto LABEL_9;
        asset = LoadAsset(_Ctrl_k__BackingField, queue->abKey, queue->assetName, 0);
LABEL_45:
        queue->topPtr = asset;
        queue->request = 0;
        queue->phase = 2;
LABEL_7:
        p_topPtr = p_request;
        AssetAsync = 0;
        goto LABEL_8;
      }
      if (queue->phase)
        goto LABEL_9;
      if (IsLoad(Dependent, queue->abKey, 0))
      {
        goto LABEL_15;
      }
      goto LABEL_9003;
      if (IsLoad(Dependent, queue->abKey, 0))
      {
LABEL_15:
        if (v3)
        {
          queue->phase = 2;
          AssetAsync = LoadAsset(_Ctrl_k__BackingField, queue->abKey, queue->assetName, 0);
          queue->topPtr = AssetAsync;
          p_topPtr = &queue->topPtr;
LABEL_8:
          goto LABEL_9;
        }
        queue->phase = 1;
        AssetAsync = LoadAssetAsync(_Ctrl_k__BackingField, queue->abKey, queue->assetName, 0);
        queue->request = (AssetBundleCtrl_Request *)AssetAsync;
        p_topPtr = &queue->request;
        goto LABEL_8;
      }
LABEL_9003:
      if (v3)
      {
        LoadSync(_Ctrl_k__BackingField, 0);
      }
LABEL_9:
      queue = queue->next;
      if (!queue)
        return v43->queue != 0;
    }
    v14 = *v2;
    queue->phase = 3;
    UnlinkQueue(queue);
    if (!queue->type)
    {
      endCallback = queue->endCallback;
      if (endCallback)
        (endCallback->invoke_impl)(endCallback->method_code, queue, queue->endCallbackParm, endCallback->method);
      goto LABEL_9;
    }
    naturalAligment = (*v7)->_2.naturalAligment;
    p_request = &queue->topPtr;
    topPtr = queue->topPtr;
    if (!topPtr)
      goto LABEL_34;
    v18 = topPtr->klass->_2.naturalAligment;
    if (v18 >= (u32)v21 && (v22 = (void *)queue->topPtr, typeHierarchy[v21 - 1] == Project_libsdf_sdfResourcePrimal))
    {
      v23 = *v8;
      goto LABEL_30;
    }
    else
    {
LABEL_34:
      v22 = 0;
      v23 = *v8;
LABEL_30:
      if (op_Inequality(v22, 0, 0))
      {
LABEL_31:
        v24 = v7;
        file = v22->file;
        v26 = Allocate(sdfBinary);
        v27 = file;
        v28 = v3;
        v29 = v8;
        v30 = v2;
        v31 = v26;
        v7 = v24;
        _ctor_36176736(v26, v27, 0);
        v32 = v31;
        v2 = v30;
        v8 = v29;
        v3 = v28;
        PushBin(v22, v32, 0);
        Length = get_Length(v22->_bin, 0);
LABEL_37:
        if (sdfPacDecode(queue[1].klass, topPtr, Length) == -1)
        {
          v35 = queue->endCallback;
          if (v35)
            (v35->invoke_impl)(v35->method_code, queue, queue->endCallbackParm, v35->method);
          LOBYTE(queue[1].monitor) = 1;
        }
        *p_request = 0;
        goto LABEL_7;
      }
LABEL_36:
      Length = 0;
      goto LABEL_37;
    }
    if (op_Inequality(v22, 0, 0))
      goto LABEL_31;
    goto LABEL_36;
  }
  return 0;
}

// 0x1b8a750
bool Manager(void) {
  return fileManager(1);
}

// 0x1b8af40
static dds3ProcessFunc_t ManagerProc(dds3ProcessID_t *procId) {
  fileManager(0);
  return 0;
}

// 0x1b8afc0
void fileSysInit(void) {
  dds3ProcessFunc_t v1;

  v1 = Allocate(dds3ProcessFunc_t);
  _ctor(v1, 0, Method_Project_file_ManagerProc__, 0);
  dds3StartProcess("fileMan", 900, 1, 0, v1, 0, 0);
  AddComponent_object_(hook);
}

// 0x1b8b120
sdfPacDecodeResrcHandle_t *pacGetResrc(pacFileHandle_t *cb) {
  return cb->decodeCb->resrcHead;
}
