#include "types.h"
#include "MODELTYPE.h"
#include "eff.h"
#include "file.h"
#include "libsdf.h"
#include "mdl.h"
#include "mdl_check.h"
#include "mdleffect.h"
#include "sdf_vu0.h"
#include "sdfmodel.h"
#include "sdfmotion.h"
#include "sdfpac.h"
#include "sdfquat.h"
#include "sdfsystem.h"

#define dummy 23
#define MAX_MOTION_GROUP 8
#define MAX_MOTION_PLAYGROUP 4

typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct dds3ModelResrc_t dds3ModelResrc_t;
typedef struct fileHandle_t fileHandle_t;
typedef struct mdlFileLoadCb_t mdlFileLoadCb_t;
typedef struct mdlLoadingTag_t mdlLoadingTag_t;
typedef struct mdlSetDef_t mdlSetDef_t;
typedef struct pacFileHandle_t pacFileHandle_t;
typedef struct sdf3DLightParallelPacket_t sdf3DLightParallelPacket_t;
typedef struct sdfModelDef_t sdfModelDef_t;
typedef struct sdfModelOt_t sdfModelOt_t;
typedef struct sdfMotionCtrlr_t sdfMotionCtrlr_t;
typedef struct sdfMotionPlayBook_t sdfMotionPlayBook_t;
typedef struct sdfPacDecodeResrcHandle_t sdfPacDecodeResrcHandle_t;

typedef void (*CallbackFunc)(void *parm);

struct mdlFileLoadCb_t {
    MODELTYPE major;
    u16 minor;
    MODEL_REGFLAG regFlags;
    pacFileHandle_t *pacHandle;
    CallbackFunc callback;
    void *callbackParm;
};

static char *modelFileTable;
static s32 *devilModelFileTable;
static s32 *eventModelFileTable;
static dds3ModelResrc_t *mdlResrcMajorList;
static mdlLoadingTag_t *mdlLoadingMajorList;
static sdfModelDef_t *dummyModelDef;

static bool CheckLoading(MODELTYPE aMajor, s32 aMinor);
static void RegLoading(MODELTYPE aMajor, s32 aMinor);
static void UnRegLoading(MODELTYPE aMajor, s32 aMinor);
static void Regist(MODELTYPE aMajor, s32 aMinor, MODEL_REGFLAG aFlag, sdfModelDef_t *aData);
static void UnRegistResrc(dds3ModelResrc_t *resrc_p);
static sdfMotionCtrlr_t *CreateMotion(dds3ModelHandle_t *aHandle, s32 aGroup);
static void FreeMotionCtrlr(dds3ModelHandle_t *aHandle, sdfMotionCtrlr_t *aCtrlr);
static void FreeMotion(dds3ModelHandle_t *aHandle, s32 aGroup);
static void UnRegistResrcMotion(dds3ModelResrc_t *aResrc, s32 aGroup);
static void RegistMotion(MODELTYPE aMajor, s32 aMinor, MODEL_REGFLAG aFlags, s32 aFirstMotion, s32 aGroup, s32 aPlayGroup, sdfMotionPlayBook_t *aData);
static void RegistModelSet(MODELTYPE aMajor, s32 aMinor, MODEL_REGFLAG aFlag, mdlSetDef_t *aSet);
static dds3ModelResrc_t *WaitLoadEnd(MODELTYPE aMajor, s32 aMinor);
static void SetFileName(char **buff, MODELTYPE aMajor, s32 aMinor);
static void UnlinkResrc(dds3ModelHandle_t *aHandle);
static void LinkMotion(dds3ModelHandle_t *aHandle);
static void LinkSet(dds3ModelHandle_t *aHandle, sdfModelOt_t *aModelOt, bool draw);
static void Motion(dds3ModelHandle_t *aHandle, s32 aGroup, s32 aNumber, SDF_MOTION aType, f32 aBeforeLeng, f32 aSmoothLeng);
static sdfPacDecodeResrcHandle_t *PackSet(sdfPacDecodeResrcHandle_t *resrc, MODELTYPE major, s32 minor, MODEL_REGFLAG regFlags);
static void FileCbFree(mdlFileLoadCb_t *cb);
static void FileLoadCallback(fileHandle_t *fileHandle, void *data);
static s32 FileLoad(MODELTYPE major, s32 minor, MODEL_REGFLAG regFlags, char *filename, CallbackFunc callback, void *parm);

// 0x1d812e0
void mdlDummy(void *parm) {
  ;
}

// 0x1d7be60
char *mdlGetModelName(MODELTYPE aMajor, s32 aMinor) {
  u32 v4;
  u32 v5;
  s64 v7;
  s32 v10;
  char *v13;
  Il2CppObject *v14;
  char *result;
  s32 data;

  v4 = aMajor;
  if (v4 == 3 && aMinor <= 207)
  {
    v5 = aMinor - 112;
    if (aMinor - 112 >= 32)
    {
      if (aMinor - 192 >= 0)
      {
        v5 = aMinor - 160;
        goto LABEL_8;
      }
    }
    else if ((v5 & 0x80000000) == 0)
    {
LABEL_8:
      v7 = (s64)eventModelFileTable + 4 * v5;
      v4 = 1;
      aMinor = *(u32 *)(v7 + 32);
      goto LABEL_15;
    }
    v4 = 3;
    goto LABEL_22;
  }
  if (v4 != 7 && v4 != 1)
    goto LABEL_20;
LABEL_16:
  goto LABEL_17;
LABEL_15:
  goto LABEL_16;
LABEL_17:
  v10 = aMinor - 2560;
  if (aMinor < 2560)
    v10 = aMinor;
  aMinor = devilModelFileTable[v10];
LABEL_20:
LABEL_22:
  data = aMinor;
  v13 = modelFileTable[v4];
  v14 = Box(s32, &data);
  result = Format(v13, v14, 0);
  if (v4 == 2 && aMinor == 11)
    return "field00b";
  if (v4 == 2 && aMinor == 16)
    return "field010";
  if (v4 == 2 && aMinor == 17)
    return "field011";
  return result;
}

// 0x1d7c150
char *mdlGetDevilModelName(s32 id) {
  s32 v5;

  v5 = id;
  return mdlGetModelName(1u, v5);
}

// 0x1d7c0d0
s32 mdlGetDevilModelNo(s32 id) {
  s32 v4;

  v4 = id - 2560;
  if (id < 2560)
    v4 = id;
  return devilModelFileTable[v4];
}

// 0x1d7c1e0
s32 mdlGetDevilModelNo2(s32 id) {
  s32 v4;

  v4 = devilModelFileTable[id];
  if (v4 >= 2560)
    return v4 - 2560;
  else
    return devilModelFileTable[id];
}

// 0x1d7c260
char *mdlGetEventModelName(s32 id) {
  s32 v5;

  v5 = id;
  return mdlGetModelName(3u, v5);
}

// 0x1d7c300
void mdlHide(dds3ModelHandle_t *HNDL) {
  HNDL->stat |= 1u;
}

// 0x1d7c310
void mdlHideBG(dds3ModelHandle_t *HNDL) {
  HNDL->stat |= 0x10u;
}

// 0x1d7c320
void mdlShow(dds3ModelHandle_t *HNDL) {
  void *gameObject;
  void *v4;

  HNDL->stat &= ~1u;
  gameObject = get_gameObject(HNDL->modelRoot->modelObj, 0);
  if (!get_activeSelf(gameObject, 0))
  {
    v4 = get_gameObject(HNDL->modelRoot->modelObj, 0);
    SetActive(v4, 1, 0);
  }
}

// 0x1d7c390
void mdlShowBG(dds3ModelHandle_t *HNDL) {
  void *gameObject;
  void *v4;

  HNDL->stat &= ~0x10u;
  gameObject = get_gameObject(HNDL->modelRoot->modelObj, 0);
  if (!get_activeSelf(gameObject, 0))
  {
    v4 = get_gameObject(HNDL->modelRoot->modelObj, 0);
    SetActive(v4, 1, 0);
  }
}

// 0x1d7c400
bool mdlChkHide(dds3ModelHandle_t *HNDL) {
  return HNDL->stat & 1;
}

// 0x1d7c410
void mdlHideUpdatePos(dds3ModelHandle_t *HNDL, bool _OnOff) {
  s32 v3;

  if (OnOff)
    v3 = 32;
  else
    v3 = 0;
  HNDL->stat = HNDL->stat & 0xFFFFFFDF | v3;
}

// 0x1d7c430
f32 mdlGetRadius(dds3ModelHandle_t *HNDL) {
  return HNDL->radius;
}

// 0x1d7c440
s32 mdlGetMotionLength(dds3ModelHandle_t *HNDL) {
  return HNDL->motionCtrlr->frameLength;
}

// 0x1d7c450
s32 mdlGetMotionFrame(dds3ModelHandle_t *HNDL) {
  f32 frame;

  frame = HNDL->motionCtrlr->frame;
  if (frame == INFINITY)
    return 0x80000000;
  else
    return (s32)frame;
}

// 0x1d7c480
f32 mdlGetMotionFrameF(dds3ModelHandle_t *HNDL) {
  return HNDL->motionCtrlr->frame;
}

// 0x1d7c490
f32 mdlGetMotionFrameFS(dds3ModelHandle_t *HNDL) {
  return HNDL->motionCtrlr->frame + HNDL->motionCtrlr->skipframe;
}

// 0x1d7c4b0
f32 mdlGetMotionFrameAnimator(dds3ModelHandle_t *HNDL) {
  return HNDL->motionCtrlr->frame_Animator;
}

// 0x1d7c4c0
f32 mdlGetMotionNormalAnimator(dds3ModelHandle_t *HNDL) {
  UnityEngine_AnimatorStateInfo_o v3;
  UnityEngine_AnimatorStateInfo_o v4;

  GetCurrentAnimatorStateInfo(&v3, HNDL->modelRoot->modelObj->animator, 0, 0);
  v4 = v3;
  return get_normalizedTime(&v4, 0);
}

// 0x1d7c520
bool mdlChkMotionEnd(dds3ModelHandle_t *HNDL) {
  return HNDL->motionCtrlr->stat == 5;
}

// 0x1d7c540
f32 mdlGetMotionSpeed(dds3ModelHandle_t *HNDL) {
  return HNDL->motionCtrlr->speed;
}

// 0x1d7c550
void mdlSetMotionSpeed(dds3ModelHandle_t *HNDL, f32 spd) {
  HNDL->motionCtrlr->speed = spd;
}

// 0x1d7c560
void mdlSetMotionSkipFrame(dds3ModelHandle_t *HNDL, f32 skipframe) {
  HNDL->motionCtrlr->skipframe = skipframe;
}

// 0x1d7c570
void mdlSetMotionBlendTree1D(dds3ModelHandle_t *HNDL, f32 _BlendTree1D) {
  sdfMotionCtrlr_t *motionCtrlr;

  motionCtrlr = HNDL->motionCtrlr;
  motionCtrlr->BlendTree1D = BlendTree1D;
  motionCtrlr->BlendTree1D_UpdateFlg = 1;
}

// 0x1d7c590
void mdlSetMotionBlendTree2D(dds3ModelHandle_t *HNDL, f32 _BlendTree2DX, f32 _BlendTree2DY) {
  sdfMotionCtrlr_t *motionCtrlr;

  motionCtrlr = HNDL->motionCtrlr;
  motionCtrlr->BlendTree2DX = BlendTree2DX;
  motionCtrlr->BlendTree2DY = BlendTree2DY;
  motionCtrlr->BlendTree2D_UpdateFlg = 1;
}

// 0x1d7c5b0
bool mdlHasMotion(dds3ModelHandle_t *HNDL) {
  return HNDL->motionCtrlr != 0;
}

// 0x1d7c5c0
s16 mdlGetMotionMajorNum(dds3ModelHandle_t *HNDL) {
  return HNDL->motionMajorNum;
}

// 0x1d7c5d0
s16 mdlGetMotionMinorNum(dds3ModelHandle_t *HNDL) {
  return HNDL->motionMinorNum;
}

// 0x1d7c5e0
void mdlSetLight(dds3ModelHandle_t *HNDL, sdf3DLightParallelPacket_t *LIGHT) {
  sdfModelRootNode_t *modelRoot;

  modelRoot = HNDL->modelRoot;
  modelRoot->light = LIGHT;
}

// 0x1d7c5f0
void mdlInit(void) {
  dds3ModelResrc_t *v5;
  mdlLoadingTag_t *v6;
  dds3ModelResrc_t *v8;
  mdlLoadingTag_t *v9;
  dds3ModelResrc_t *v11;
  mdlLoadingTag_t *v12;
  dds3ModelResrc_t *v14;
  mdlLoadingTag_t *v15;
  dds3ModelResrc_t *v17;
  mdlLoadingTag_t *v18;
  dds3ModelResrc_t *v20;
  mdlLoadingTag_t *v21;
  dds3ModelResrc_t *v23;
  mdlLoadingTag_t *v24;
  dds3ModelResrc_t *v26;
  mdlLoadingTag_t *v27;

  mdlResrcMajorList[0] = 0;
  mdlLoadingMajorList[0] = 0;
  v5 = mdlResrcMajorList;
  v5[1] = 0;
  v6 = mdlLoadingMajorList;
  v6[1] = 0;
  v8 = mdlResrcMajorList;
  v8[2] = 0;
  v9 = mdlLoadingMajorList;
  v9[2] = 0;
  v11 = mdlResrcMajorList;
  v11[3] = 0;
  v12 = mdlLoadingMajorList;
  v12[3] = 0;
  v14 = mdlResrcMajorList;
  v14[4] = 0;
  v15 = mdlLoadingMajorList;
  v15[4] = 0;
  v17 = mdlResrcMajorList;
  v17[5] = 0;
  v18 = mdlLoadingMajorList;
  v18[5] = 0;
  v20 = mdlResrcMajorList;
  v20[6] = 0;
  v21 = mdlLoadingMajorList;
  v21[6] = 0;
  v23 = mdlResrcMajorList;
  v23[7] = 0;
  v24 = mdlLoadingMajorList;
  v24[7] = 0;
  v26 = mdlResrcMajorList;
  v26[8] = 0;
  v27 = mdlLoadingMajorList;
  v27[8] = 0;
}

// 0x1d7c870
dds3ModelResrc_t *mdlSearchResrc(MODELTYPE aMajor, s32 aMinor) {
  dds3ModelResrc_t *result;

  result = mdlResrcMajorList[aMajor];
  if (!result)
    return result;
  goto LABEL_7;
  do
  {
LABEL_7:
    if (result->minor == aMinor)
      break;
    result = result->next;
  }
  while (result);
  return result;
}

// 0x1d7c930
static bool CheckLoading(MODELTYPE aMajor, s32 aMinor) {
  mdlLoadingTag_t *next;
  s32 minor;
  bool result;

  next = mdlLoadingMajorList[aMajor];
  if (!next)
    return 0;
  do
  {
    minor = next->minor;
    result = minor == aMinor;
    if (minor == aMinor)
      break;
    next = next->next;
  }
  while (next);
  return result;
}

// 0x1d7ca00
static void RegLoading(MODELTYPE aMajor, s32 aMinor) {
  mdlLoadingTag_t *v5;
  mdlLoadingTag_t *v7;
  mdlLoadingTag_t *mdlLoadingMajorList_local;
  Il2CppClass **v10;

  v5 = Allocate(mdlLoadingTag_t);
  v7 = mdlLoadingMajorList[aMajor];
  v5->next = v7;
  v5->minor = aMinor;
  mdlLoadingMajorList_local = mdlLoadingMajorList;
  v10 = &mdlLoadingMajorList_local->obj.klass + aMajor;
  v10[4] = v5;
}

// 0x1d7cb00
static void UnRegLoading(MODELTYPE aMajor, s32 aMinor) {
  mdlLoadingTag_t *mdlLoadingMajorList_local;
  mdlLoadingTag_t *v7;
  mdlLoadingTag_t *next;
  mdlLoadingTag_t *v9;
  mdlLoadingTag_t *v10;
  Il2CppClass **v11;

  mdlLoadingMajorList_local = mdlLoadingMajorList;
  v7 = mdlLoadingMajorList_local[aMajor];
  if (!v7)
    return;
  if (v7->minor == aMinor)
  {
    next = v7->next;
    if (!next)
      goto LABEL_17;
    goto LABEL_9000;
    if (!next)
    {
LABEL_17:
      v11 = &mdlLoadingMajorList_local->obj.klass + aMajor;
      v11[4] = next;
      return;
    }
LABEL_9000:
    goto LABEL_17;
  }
  while (1)
  {
    v9 = v7;
    v7 = v7->next;
    if (!v7)
      break;
    if (v7->minor == aMinor)
    {
      v10 = v7->next;
      v9->next = v10;
      return;
    }
  }
}

// 0x1d7cc60
static void Regist(MODELTYPE aMajor, s32 aMinor, MODEL_REGFLAG aFlag, sdfModelDef_t *aData) {
  char v6;
  dds3ModelResrc_t *v9;
  dds3ModelResrc_t *v12;
  dds3ModelResrc_t *mdlResrcMajorList_local;
  Il2CppClass **v14;
  void *v15;
  u64 *v16;

  v6 = aFlag;
  v9 = Allocate(dds3ModelResrc_t);
  v12 = mdlResrcMajorList[aMajor];
  mdlUnRegist(aMajor, aMinor);
  if (v12)
  {
    v12->prev = v9;
  }
  mdlResrcMajorList_local = mdlResrcMajorList;
  if (!v9)
  v14 = &mdlResrcMajorList_local->obj.klass + aMajor;
  v14[4] = v9;
  v9->prev = 0;
  v9->next = v12;
  v9->major = aMajor;
  v9->models = 0;
  v9->minor = aMinor;
  v9->modelDefPtr = aData;
  v15 = NewSpecific(dds3ModelResrcPlayBook_t, 8u);
  v9->playbooks = v15;
  v9->effectData = 0;
  v9->effectResrcList = 0;
  v16 = &v9->effectResrcList;
  *((u8 *)v16 - 36) = v6 & 1;
  v16[1] = 0x42C800003F800000LL;
}

// 0x1d7cf60
static void UnRegistResrc(dds3ModelResrc_t *resrc_p) {
  dds3ModelResrc_t *prev;
  dds3ModelResrc_t *next;
  _BOOL4 autoFreeFlag;
  dds3ModelHandle_t *i;
  dds3ModelResrcPlayBook_t *playbooks;
  s64 v9;
  s64 v10;
  s64 major;
  dds3ModelResrc_t *mdlResrcMajorList_local;
  Il2CppClass **v13;

  if (resrc_p)
  {
    next = resrc_p->next;
    prev = resrc_p->prev;
    if (prev)
    {
      prev->next = next;
      if (!next)
      {
LABEL_7:
        autoFreeFlag = resrc_p->autoFreeFlag;
        resrc_p->autoFreeFlag = 0;
        for (i = resrc_p->models; i; i = resrc_p->models)
        {
          Free(i);
        }
        if (autoFreeFlag)
        {
          playbooks = resrc_p->playbooks;
          if (SLODWORD(playbooks->max_length) >= 1)
          {
            v9 = 0;
            v10 = 32;
            do
            {
              *(Il2CppClass **)((char *)&playbooks->obj.klass + v10) = 0;
              playbooks = resrc_p->playbooks;
              ++v9;
              v10 += 8;
            }
            while (v9 < SLODWORD(playbooks->max_length));
          }
        }
        mdlEffectResrcListFree(resrc_p->effectResrcList);
        return;
      }
LABEL_6:
      next->prev = prev;
      goto LABEL_7;
    }
    major = resrc_p->major;
    mdlResrcMajorList_local = mdlResrcMajorList;
    if (!next)
    v13 = &mdlResrcMajorList_local->obj.klass + major;
    v13[4] = next;
    if (!next)
      goto LABEL_7;
    goto LABEL_6;
  }
}

// 0x1d7ce60
void mdlUnRegist(MODELTYPE aMajor, s32 aMinor) {
  dds3ModelResrc_t *next;

  next = mdlResrcMajorList[aMajor];
  if (!next)
    goto LABEL_13;
  do
  {
    if (next->minor == aMinor)
      break;
    next = next->next;
  }
  while (next);
LABEL_13:
  UnRegistResrc(next);
}

// 0x1d7d1c0
static sdfMotionCtrlr_t *CreateMotion(dds3ModelHandle_t *aHandle, s32 aGroup) {
  s16 v3;
  dds3ModelResrcPlayBook_t *v5;
  s64 playGroup;
  sdfMotionCtrlr_t *v7;
  sdfMotionCtrlr_t *motions;
  sdfMotionCtrlr_t *v9;
  Il2CppClass **v10;

  v3 = aGroup;
  v5 = aHandle->resrc->playbooks[aGroup];
  playGroup = v5->playGroup;
  v7 = sdfMotionCtrlrNew(aHandle->modelRoot, v5->ptr);
  v7->userId = v3;
  motions = aHandle->motions;
  v9 = v7;
  v7->userId2 = playGroup;
  v10 = &motions->obj.klass + playGroup;
  v10[4] = v9;
  if (!(u32)playGroup)
  {
    aHandle->motionCtrlr = v9;
  }
  return v9;
}

// 0x1d7d280
static void FreeMotionCtrlr(dds3ModelHandle_t *aHandle, sdfMotionCtrlr_t *aCtrlr) {
  Il2CppClass **v4;

  v4 = &aHandle->motions->obj.klass + aCtrlr->userId2;
  if (v4[4] == aCtrlr)
  {
    v4[4] = 0;
    sdfMotionCtrlrFree(aCtrlr);
  }
  else
  {
    sdfMotionCtrlrFree(aCtrlr);
  }
}

// 0x1d7d2f0
static void FreeMotion(dds3ModelHandle_t *aHandle, s32 aGroup) {
  sdfMotionCtrlr_t *motion;
  Il2CppClass **v6;

  motion = aHandle->modelRoot->motion;
  if (motion)
  {
    while (motion->userId != aGroup)
    {
      motion = motion->next;
      if (!motion)
        return;
    }
    v6 = &aHandle->motions->obj.klass + motion->userId2;
    if (v6[4] == motion)
    {
      v6[4] = 0;
    }
    sdfMotionCtrlrFree(motion);
  }
}

// 0x1d7d3d0
static void UnRegistResrcMotion(dds3ModelResrc_t *aResrc, s32 aGroup) {
  dds3ModelResrcPlayBook_t *playbooks;
  dds3ModelHandle_t *models;
  sdfMotionCtrlr_t *motion;
  s64 v8;
  Il2CppClass **v9;

  if (!aResrc)
    return;
  playbooks = aResrc->playbooks;
  if (!playbooks[aGroup])
    return;
  models = aResrc->models;
  if (!models)
    goto LABEL_24;
  do
  {
    motion = models->modelRoot->motion;
    if (motion)
    {
      while (motion->userId != aGroup)
      {
        motion = motion->next;
        if (!motion)
          goto LABEL_8;
      }
      v8 = (s64)models->motions + 8 * motion->userId2;
      if (*(sdfMotionCtrlr_t *)(v8 + 32) == motion)
      {
        *(u64 *)(v8 + 32) = 0;
      }
      sdfMotionCtrlrFree(motion);
    }
LABEL_8:
    models = models->next;
  }
  while (models);
  playbooks = aResrc->playbooks;
LABEL_24:
  v9 = &playbooks->obj.klass + aGroup;
  v9[4] = 0;
}

// 0x1d7d540
static void RegistMotion(MODELTYPE aMajor, s32 aMinor, MODEL_REGFLAG aFlags, s32 aFirstMotion, s32 aGroup, s32 aPlayGroup, sdfMotionPlayBook_t *aData) {
  s16 v9;
  s16 v11;
  s16 v12;
  dds3ModelResrc_t *i;
  dds3ModelResrcPlayBook_t *v18;
  dds3ModelResrcPlayBook_t *playbooks;
  Il2CppClass **v20;

  v9 = aPlayGroup;
  v11 = aFirstMotion;
  v12 = aFlags;
  for (i = mdlResrcMajorList[aMajor]; i; i = i->next)
  {
    if (i->minor == aMinor)
      break;
  }
  UnRegistResrcMotion(i, aGroup);
  v18 = Allocate(dds3ModelResrcPlayBook_t);
  v18->flags = 0;
  v18->ptr = aData;
  v18->playGroup = v9;
  v18->firstMotion = v11;
  if ((v12 & 0x100) == 0)
  {
    if ((v12 & 0x200) == 0)
      goto LABEL_10;
LABEL_17:
    v18->flags |= 2u;
    playbooks = i->playbooks;
  }
  v18->flags |= 1u;
  if ((v12 & 0x200) != 0)
    goto LABEL_17;
LABEL_10:
  playbooks = i->playbooks;
  v20 = &playbooks->obj.klass + aGroup;
  v20[4] = v18;
}

// 0x1d7d720
static void RegistModelSet(MODELTYPE aMajor, s32 aMinor, MODEL_REGFLAG aFlag, mdlSetDef_t *aSet) {
  sdfModelDef_t *modelDefPtr;
  sdfMotionPlayBook_t *playbookPtr;
  dds3ModelResrc_t *next;
  pibHeaderChunk_t *effectData;
  mdlEffectResrcList_t *effectResrcList;

  modelDefPtr = aSet->modelDefPtr;
  Regist(aMajor, aMinor, aFlag, modelDefPtr);
  playbookPtr = aSet->playbookPtr;
  if (playbookPtr)
  {
    RegistMotion(aMajor, aMinor, aFlag, 0, 0, 0, playbookPtr);
  }
  if (aSet->effectData)
  {
    next = mdlResrcMajorList[aMajor];
    if (!next)
      goto LABEL_21;
    goto LABEL_19;
    if (!next)
    {
LABEL_21:
      effectData = aSet->effectData;
      next->effectData = effectData;
      effectResrcList = aSet->effectResrcList;
      next->effectResrcList = effectResrcList;
      return;
    }
    do
    {
LABEL_19:
      if (next->minor == aMinor)
        break;
      next = next->next;
    }
    while (next);
    goto LABEL_21;
  }
}

// 0x1d7d8c0
static dds3ModelResrc_t *WaitLoadEnd(MODELTYPE aMajor, s32 aMinor) {
  mdlLoadingTag_t *next;
  dds3ModelResrc_t *result;

LABEL_4:
  goto LABEL_9000;
  while (1)
  {
    break;
LABEL_11:
    while (next->minor != aMinor)
    {
      next = next->next;
      if (!next)
        goto LABEL_18;
    }
    Manager();
    goto LABEL_4;
  }
LABEL_9000:
  next = mdlLoadingMajorList[aMajor];
  if (next)
    goto LABEL_11;
LABEL_18:
  result = mdlResrcMajorList[aMajor];
  if (!result)
    return result;
  goto LABEL_26;
  do
  {
LABEL_26:
    if (result->minor == aMinor)
      break;
    result = result->next;
  }
  while (result);
  return result;
}

// 0x1d7daa0
static void SetFileName(char **buff, MODELTYPE aMajor, s32 aMinor) {
  char *ModelName;

  ModelName = mdlGetModelName(aMajor, aMinor);
  *buff = ModelName;
}

// 0x1d7db30
dds3ModelResrc_t *mdlPrepare(MODELTYPE aMajor, s32 aMinor, bool aBlockMode) {
  dds3ModelResrc_t *next;
  s64 v11;
  mdlLoadingTag_t *v12;
  char *v15;
  CallbackFunc v16;
  char *target;

  target = 0;
  next = mdlResrcMajorList[aMajor];
  if (next)
  {
    while (next->minor != aMinor)
    {
      next = next->next;
      if (!next)
        goto LABEL_8;
    }
    return next;
  }
LABEL_8:
  v11 = aMajor;
  v12 = mdlLoadingMajorList[v11];
  if (v12)
    goto LABEL_12;
LABEL_14:
  RegLoading(aMajor, aMinor);
  target = mdlGetModelName(aMajor, aMinor);
  v15 = target;
  v16 = Allocate(CallbackFunc);
  _ctor(v16, 0);
  FileLoad(aMajor, aMinor, 257, v15, v16, 0);
  next = 0;
  if (aBlockMode)
  {
    return WaitLoadEnd(aMajor, aMinor);
  }
  return next;
LABEL_12:
  while (v12->minor != aMinor)
  {
    v12 = v12->next;
    if (!v12)
      goto LABEL_14;
  }
  if (!aBlockMode)
  {
    return PREPARE_RE_LOADING;
  }
  return WaitLoadEnd(aMajor, aMinor);
}

// 0x1d7e1f0
dds3ModelResrc_t *mdlLoadResrc(MODELTYPE aMajor, s32 aMinor) {
  return mdlPrepare(aMajor, aMinor, 1);
}

// 0x1d7e260
static void UnlinkResrc(dds3ModelHandle_t *aHandle) {
  dds3ModelHandle_t *next;
  dds3ModelHandle_t *prev;
  dds3ModelHandle_t *v5;
  dds3ModelResrc_t *resrc;
  dds3ModelResrc_t *v7;

  next = aHandle->next;
  prev = aHandle->prev;
  if (next)
  {
    v5 = aHandle->prev;
    next->prev = prev;
    if (!prev)
    {
      resrc = aHandle->resrc;
      resrc->models = next;
      return;
    }
    goto LABEL_7;
  }
  if (prev)
  {
LABEL_7:
    prev->next = next;
    return;
  }
  v7 = aHandle->resrc;
  v7->models = 0;
  if (v7->autoFreeFlag)
  {
    UnRegistResrc(v7);
  }
}

// 0x1d7e360
dds3ModelHandle_t *mdlLoad(MODELTYPE aMajor, s32 aMinor) {
  dds3ModelResrc_t *v8;
  Il2CppObject *v9;
  Il2CppClass *v10;
  dds3ModelHandle_t *models;
  u64 *monitor;
  sdfModelDef_t *modelDefPtr;
  sdfModelDef_t *v15;
  sdfModelRootNode_t *_36047984;
  void *v17;
  void *transform;
  void *v20;
  int32x4_t v27;
  f32 radius;
  dds3ModelResrcPlayBook_t *playbooks;
  s32 max_length;
  s64 i;
  dds3ModelResrcPlayBook_t *v32;
  s32 firstMotion;

  v8 = mdlPrepare(aMajor, aMinor, 1);
  v9 = Allocate(dds3ModelHandle_t);
  v10 = NewSpecific(sdfMotionCtrlr_t, 4u);
  v9[5].klass = v10;
  _ctor(v9, 0);
  v9[2].monitor = v8;
  models = v8->models;
  v9[1].monitor = models;
  monitor = v9[1].monitor;
  if (monitor)
  {
    monitor[4] = v9;
  }
  v8->models = (dds3ModelHandle_t *)v9;
  modelDefPtr = v8->modelDefPtr;
  v15 = v8->modelDefPtr;
  if (modelDefPtr == dummyModelDef)
  {
    v17 = Allocate(UnityEngine_GameObject);
    _ctor_60987488(v17, 0);
    _36047984 = Make(v15, v17, 0);
  }
  else
  {
    _36047984 = sdfModelMake_2(v8->modelDefPtr);
  }
  v9[4].klass = _36047984;
  transform = get_transform(v9[4].klass->_2.unity_user_data, 0);
  v20 = get_transform(hook, 0);
  SetParent_61042560(transform, v20, 0, 0);
  __asm { FMOV            V1.4S, #1.0 }
  _Q1.n128_u32[0] = LODWORD(v8->scale);
  v27 = vzip1q_s32(_Q1, _Q1);
  v27.n128_u32[2] = LODWORD(v8->scale);
  *(int32x4_t *)&v9[4].klass->_1.implementedInterfaces = v27;
  radius = v8->radius;
  LODWORD(v9[3].klass) = -1;
  playbooks = v8->playbooks;
  max_length = playbooks->max_length;
  *(f32 *)&v9[5].monitor = radius;
  if (max_length >= 1)
  {
    for (i = 0; i < SLODWORD(playbooks->max_length); ++i)
    {
      v32 = playbooks[i];
      if (!v32 || (v32->flags & 1) == 0)
        continue;
      CreateMotion(v9, i);
      playbooks = v8->playbooks;
      firstMotion = playbooks[i]->firstMotion;
      if (firstMotion < 0)
        continue;
      Motion(v9, i, firstMotion, 1, 0.0, 0.0);
      playbooks = v8->playbooks;
    }
  }
  v9[3].monitor = 0;
  mdlEffectGen(v9, -1, -1);
  WORD2(v9[5].monitor) = 0;
  return (dds3ModelHandle_t *)v9;
}

// 0x1d7e820
void mdlRegistDummy(MODELTYPE aMajor, s32 aMinor) {
  Regist(aMajor, aMinor, 0, dummyModelDef);
}

// 0x1d7d100
void Free(dds3ModelHandle_t *aHandle) {
  sdfModelRootNode_t *modelRoot;
  sdfMotionCtrlr_t *i;
  dds3ModelEffectCtrlr_t *effects;
  dds3ModelEffectCtrlr_t *next;

  modelRoot = aHandle->modelRoot;
  for (i = modelRoot->motion; i; i = modelRoot->motion)
    sdfMotionCtrlrFree(i);
  effects = aHandle->effects;
  if (effects)
  {
    do
    {
      next = effects->next;
      mdlFree(effects);
      effects = next;
    }
    while (next);
  }
  sdfModelRootFree(modelRoot);
  UnlinkResrc(aHandle);
}

// 0x1d7e8a0
void Link(dds3ModelHandle_t *aHandle, sdfModelOt_t *aModelOt) {
  LinkMotion(aHandle);
  LinkSet(aHandle, aModelOt, 1);
}

// 0x1d7eb80
void mdlLink_NoDraw(dds3ModelHandle_t *aHandle, sdfModelOt_t *aModelOt) {
  void *modelObj;

  LinkMotion(aHandle);
  modelObj = aHandle->modelRoot->modelObj;
  SetLayer(modelObj, excludeLayer, 0);
}

// 0x1d7ec50
void mdlLink_Kubi(dds3ModelHandle_t *aHandle, sdfModelOt_t *aModelOt, s32 node, f32 rx, f32 ry) {
  f32 v13;
  bool v14;
  f32 v15;
  void *transform;
  f32 v17;
  sdfQuaternion_t localRotation;
  sdfVector3_t v20;
  sdfQuaternion_t v21;
  sdfQuaternion_t v22;

  LinkMotion(aHandle);
  if (node != -1)
  {
    v13 = -rx;
    if (rx >= 0.0)
      v13 = rx;
    v14 = v13 < 25.0;
    v15 = v13 / 25.0;
    transform = aHandle->modelRoot->nodeList->items[node]->transform;
    if (v14)
      v17 = v15;
    else
      v17 = 1.0;
    localRotation = get_localRotation(transform, 0);
    v20.x = rx * 0.017453292;
    v20.z = ry * 0.017453292;
    v20.y = 0.0;
    v22 = Internal_FromEulerRad(v20, 0);
    v21 = Lerp(localRotation, v22, v17, 0);
    set_localRotation(transform, v21, 0);
  }
  LinkSet(aHandle, aModelOt, 1);
}

// 0x1d7e920
static void LinkMotion(dds3ModelHandle_t *aHandle) {
  sdfModelRootNode_t *modelRoot;
  void *animator;
  sdfMotionCtrlr_t *motions;
  il2cpp_array_size_t max_length;
  s64 v7;
  sdfMotionCtrlr_t *v8;

  modelRoot = aHandle->modelRoot;
  SetActive(modelRoot->modelObj, 1, 0);
  animator = modelRoot->modelObj->animator;
  if (!op_Inequality(modelRoot->modelObj->animator, 0, 0))
    return;
  motions = aHandle->motions;
  max_length = motions->max_length;
  if ((s32)max_length >= 1)
  {
    v7 = 0;
    do
    {
      v8 = motions[v7];
      if (v8)
      {
        if (v8->stat)
        {
          sdfMotionNext(v8);
          max_length = motions->max_length;
        }
      }
      ++v7;
    }
    while (v7 < (s32)max_length);
  }
  sdfMotionUpdate(modelRoot);
}

// 0x1d7ea20
static void LinkSet(dds3ModelHandle_t *aHandle, sdfModelOt_t *aModelOt, bool draw) {
  u32 stat;
  sdfModelRootNode_t *modelRoot;
  void *modelObj;
  dds3ModelEffectCtrlr_t *effects;
  s32 camID_local;

  stat = aHandle->stat;
  modelRoot = aHandle->modelRoot;
  if ((stat & 0x11) != 0)
  {
    if ((stat & 0x20) != 0 && draw)
      sdfModelLinkOt_PosOnly(aHandle->modelRoot);
    goto LABEL_10;
  }
  if (!draw)
  {
LABEL_10:
    modelObj = modelRoot->modelObj;
    SetLayer(modelObj, excludeLayer, 0);
    return;
  }
  sdfModelLinkOt(aModelOt, aHandle->modelRoot);
  if ((aHandle->stat & 6) == 0)
  {
    effects = aHandle->effects;
    if (effects)
    {
      do
      {
        camID_local = aModelOt->camID;
        camID = camID_local;
        mdlLink(aHandle, effects);
        effects = effects->next;
        camID = 0;
      }
      while (effects);
    }
  }
}

// 0x1d7edf0
static void Motion(dds3ModelHandle_t *aHandle, s32 aGroup, s32 aNumber, SDF_MOTION aType, f32 aBeforeLeng, f32 aSmoothLeng) {
  sdfMotionCtrlr_t *motion;
  sdfMotionCtrlr_t *motions;
  s64 userId2;
  Il2CppClass **v16;

  motion = aHandle->modelRoot->motion;
  if (motion)
  {
    while ((u16)aGroup != motion->userId)
    {
      motion = motion->next;
      if (!motion)
        goto LABEL_6;
    }
  }
  else
  {
LABEL_6:
    motion = CreateMotion(aHandle, aGroup);
  }
  motions = aHandle->motions;
  userId2 = motion->userId2;
  v16 = &motions->obj.klass + userId2;
  v16[4] = motion;
  if (!(u32)userId2)
  {
    aHandle->motionCtrlr = motion;
  }
  sdfMotionChangeBlend(motion, aNumber, aType, aBeforeLeng, aSmoothLeng);
  aHandle->motionMajorNum = aGroup;
  aHandle->motionMinorNum = aNumber;
  mdlEffectStop(aHandle, userId2);
  mdlEffectGen(aHandle, aNumber, userId2);
}

// 0x1d7e790
void mdlLoopMotion(dds3ModelHandle_t *aHandle, s32 aGroup, s32 aNumber) {
  Motion(aHandle, aGroup, aNumber, 1, 0.0, 0.0);
}

// 0x1d7ef40
void mdlSingleMotion(dds3ModelHandle_t *aHandle, s32 aGroup, s32 aNumber) {
  Motion(aHandle, aGroup, aNumber, 0, 0.0, 0.0);
}

// 0x1d7efd0
void mdlSmoothLoopMotion(dds3ModelHandle_t *aHandle, s32 aGroup, s32 aNumber, f32 aBeforeLeng, f32 aSmoothLeng, f32 _SkipFrame) {
  aHandle->motionCtrlr->skipframe = SkipFrame;
  Motion(aHandle, aGroup, aNumber, 1, aBeforeLeng, aSmoothLeng);
}

// 0x1d7f080
void mdlSmoothSingleMotion(dds3ModelHandle_t *aHandle, s32 aGroup, s32 aNumber, f32 aBeforeLeng, f32 aSmoothLeng, f32 _SkipFrame) {
  aHandle->motionCtrlr->skipframe = SkipFrame;
  Motion(aHandle, aGroup, aNumber, 0, aBeforeLeng, aSmoothLeng);
}

// 0x1d7f130
sdfMotionCtrlr_t *mdlGetMotionCtrlr(dds3ModelHandle_t *aHandle, s32 aGroup) {
  sdfMotionCtrlr_t *result;

  for (result = aHandle->modelRoot->motion; result; result = result->next)
  {
    if ((u16)aGroup == result->userId)
      break;
  }
  return result;
}

// 0x1d7f160
s32 mdlGetMotionNum(dds3ModelHandle_t *aHandle, s32 aGroup) {
  u16 v3;
  sdfMotionCtrlr_t *motion;
  s32 result;

  v3 = aGroup;
  motion = aHandle->modelRoot->motion;
  if (!motion)
    return -1;
  result = -1;
  while (v3 != motion->userId)
  {
    motion = motion->next;
    if (!motion)
      return result;
  }
  return motion->cutNumber;
}

// 0x1d7f230
s32 mdlGetMotionLengthEx(dds3ModelHandle_t *aHandle, s32 aGroup) {
  u16 v3;
  sdfMotionCtrlr_t *motion;

  v3 = aGroup;
  motion = aHandle->modelRoot->motion;
  if (!motion)
    return 0;
  while (v3 != motion->userId)
  {
    motion = motion->next;
    if (!motion)
      return 0;
  }
  return motion->frameLength;
}

// 0x1d7f300
s32 mdlGetMotionFrameEx(dds3ModelHandle_t *aHandle, s32 aGroup) {
  u16 v3;
  sdfMotionCtrlr_t *motion;
  f32 frame;

  v3 = aGroup;
  motion = aHandle->modelRoot->motion;
  if (!motion)
    return 0;
  while (v3 != motion->userId)
  {
    motion = motion->next;
    if (!motion)
      return 0;
  }
  frame = motion->frame;
  if (frame == INFINITY)
    return 0x80000000;
  else
    return (s32)frame;
}

// 0x1d7f3f0
bool mdlChkMotionEndEx(dds3ModelHandle_t *aHandle, s32 aGroup) {
  u16 v3;
  sdfMotionCtrlr_t *motion;

  v3 = aGroup;
  motion = aHandle->modelRoot->motion;
  if (!motion)
    return 1;
  while (v3 != motion->userId)
  {
    motion = motion->next;
    if (!motion)
      return 1;
  }
  return motion->stat == 5;
}

// 0x1d7f4d0
void mdlSetMotionSpeedEx(dds3ModelHandle_t *aHandle, s32 aGroup, f32 speed) {
  u16 v5;
  sdfMotionCtrlr_t *motion;

  v5 = aGroup;
  motion = aHandle->modelRoot->motion;
  if (motion)
    goto LABEL_7;
  return;
  if (motion)
  {
LABEL_7:
    while (v5 != motion->userId)
    {
      motion = motion->next;
      if (!motion)
        return;
    }
    motion->speed = speed;
  }
}

// 0x1d7f5a0
void mdlGetPosition(dds3ModelHandle_t *aHandle) {
  sdfVector4_t Row;

  Row = GetRow(&aHandle->modelRoot->tm, 3, 0);
  vct_A = Row;
}

// 0x1d7f690
void mdlSetPosition(dds3ModelHandle_t *aHandle) {
  sdfModelRootNode_t *modelRoot;

  modelRoot = aHandle->modelRoot;
  vct_A.w = 1.0;
  SetRow(&modelRoot->tm, 3, vct_A, 0);
}

// 0x1d7f7b0
void mdlGetRotate(dds3ModelHandle_t *aHandle) {
  struct sdfVector4_t rotate;

  rotate = aHandle->modelRoot->rotate;
  vct_A = rotate;
}

// 0x1d7f8a0
void mdlSetRotate(dds3ModelHandle_t *aHandle) {
  sdfModelRootNode_t *modelRoot;
  sdfVector4_t *p_rotate;
  sdfModelRootNode_t *v6;
  _OWORD *p_x;
  __int128 v9;
  __int128 v10;
  __int128 v11;
  sdfVector4_t Row;

  Row = GetRow(&aHandle->modelRoot->tm, 3, 0);
  modelRoot = aHandle->modelRoot;
  p_rotate = &modelRoot->rotate;
  *p_rotate = vct_A;
  ToMatrix();
  v6 = aHandle->modelRoot;
  p_x = &vf00.x;
  v9 = p_x[4];
  v10 = p_x[5];
  v11 = p_x[6];
  *(_OWORD *)&v6->tm.m03 = p_x[7];
  *(_OWORD *)&v6->tm.m01 = v10;
  *(_OWORD *)&v6->tm.m02 = v11;
  *(_OWORD *)&v6->tm.m00 = v9;
  SetRow(&aHandle->modelRoot->tm, 3, Row, 0);
}

// 0x1d7fa30
void mdlGetScale(dds3ModelHandle_t *aHandle) {
  struct sdfVector4_t scale;

  scale = aHandle->modelRoot->scale;
  vct_A = scale;
}

// 0x1d7fb20
void mdlSetScale(dds3ModelHandle_t *aHandle) {
  sdfModelRootNode_t *modelRoot;

  modelRoot = aHandle->modelRoot;
  modelRoot->scale = vct_A;
}

// 0x1d7fbf0
void mdlSetEffectScale(dds3ModelHandle_t *aHandle, f32 _scale) {
  dds3ModelEffectCtrlr_t *i;

  for (i = aHandle->effects; i; i = i->next)
    mdlEffectSetScaleSub(aHandle, i, scale);
}

// 0x1d7fc40
sdfVector4_t mdlGetColor(dds3ModelHandle_t *aHandle) {
  sdfModelRootNode_t *modelRoot;
  sdfVector4_t result;

  modelRoot = aHandle->modelRoot;
  result.x = modelRoot->color.x;
  result.y = modelRoot->color.y;
  result.z = modelRoot->color.z;
  result.w = modelRoot->color.w;
  return result;
}

// 0x1d7fc50
void mdlSetEffectColor(dds3ModelHandle_t *aHandle, u32 aColor) {
  dds3ModelEffectCtrlr_t *effects;
  u64 v8;
  f32 v9;
  f32 aColora;
  sdfVector4_t v11;

  effects = aHandle->effects;
  if (!effects)
    return;
  v8 = vmul_f32(vcvt_f32_u32(vand_s8(vshl_u32(vdup_n_s32(aColor), (uint32x2_t)0xFFFFFFF0FFFFFFF8LL), (int8x8_t)0xFF000000FFLL)), (float32x2_t)0x3C0000003C000000LL).n64_u64[0];
  v9 = *((f32 *)&v8 + 1);
  aColora = *(f32 *)&v8;
  do
  {
    v11.x = (f32)(u8)aColor * 0.0078125;
    v11.z = v9;
    v11.w = (f32)HIBYTE(aColor) * 0.0078125;
    v11.y = aColora;
    mdlEffectSetColorSub(aHandle, effects, v11);
    effects = effects->next;
  }
  while (effects);
}

// 0x1d7fda0
void SetEffectColor(dds3ModelHandle_t *aHandle, const sdfVector4_t *aColor) {
  dds3ModelEffectCtrlr_t *effects;
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  sdfVector4_t v9;

  effects = aHandle->effects;
  if (effects)
  {
    w = aColor->w;
    z = aColor->z;
    y = aColor->y;
    x = aColor->x;
    do
    {
      v9.x = x;
      v9.y = y;
      v9.z = z;
      v9.w = w;
      mdlEffectSetColorSub(aHandle, effects, v9);
      effects = effects->next;
    }
    while (effects);
  }
}

// 0x1d7fe10
void mdlSetColor(dds3ModelHandle_t *aHandle, u32 aColor) {
  int8x8_t v5;
  f32 v6;
  f32 v7;
  float32x2_t v8;
  float32x2_t v9;
  f32 v10;
  f32 v11;
  float32x2_t *modelRoot;
  dds3ModelEffectCtrlr_t *effects;
  sdfVector4_t v16;

  v5.n64_u32[0] = aColor;
  v6 = BYTE2(aColor);
  v7 = HIBYTE(aColor);
  v5.n64_u32[1] = aColor >> 8;
  v8.n64_u64[0] = vcvt_f32_u32(vand_s8(v5, (int8x8_t)0xFF000000FFLL)).n64_u64[0];
  v9.n64_u64[0] = vmul_f32(v8, (float32x2_t)0x3C0000003C000000LL).n64_u64[0];
  v10 = v6 * 0.0078125;
  v11 = v7 * 0.0078125;
  modelRoot = aHandle->modelRoot;
  modelRoot[4].n64_u64[0] = v9.n64_u64[0];
  modelRoot[5].n64_f32[0] = v10;
  modelRoot[5].n64_f32[1] = v11;
  effects = aHandle->effects;
  if (!effects)
    return;
  goto LABEL_13;
  do
  {
LABEL_13:
    v16.x = 1.0;
    v16.y = 1.0;
    v16.z = 1.0;
    v16.w = v11;
    mdlEffectSetColorSub(aHandle, effects, v16);
    effects = effects->next;
  }
  while (effects);
}

// 0x1d80080
void mdlSetColor_And_EffAlp(dds3ModelHandle_t *aHandle, u32 aColor, f32 _EffAlp) {
  int8x16_t v7;
  int8x16_t v8;
  uint32x4_t v9;
  float32x4_t v10;
  float32x4_t v11;
  float32x4_t v12;
  dds3ModelEffectCtrlr_t *effects;
  sdfVector4_t v18;

  v7.n128_u32[0] = aColor;
  v8.n128_u64[0] = 0xFF000000FFLL;
  v8.n128_u64[1] = 0xFF000000FFLL;
  v7.n128_u32[1] = aColor >> 8;
  v7.n128_u32[2] = HIWORD(aColor);
  v9 = vandq_s8(v7, v8);
  v9.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(aColor), 0x18u).n128_u32[3];
  v10.n128_u64[0] = 0x3C0000003C000000LL;
  v10.n128_u64[1] = 0x3C0000003C000000LL;
  v11 = vcvtq_f32_u32(v9);
  v12 = vmulq_f32(v11, v10);
  aHandle->modelRoot->color = (struct sdfVector4_t)v12;
  effects = aHandle->effects;
  if (!effects)
    return;
  goto LABEL_13;
  do
  {
LABEL_13:
    v18.x = 1.0;
    v18.y = 1.0;
    v18.z = 1.0;
    v18.w = EffAlp;
    mdlEffectSetColorSub(aHandle, effects, v18);
    effects = effects->next;
  }
  while (effects);
}

// 0x1d7ffa0
void SetColor(dds3ModelHandle_t *aHandle, const sdfVector4_t *aColor) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  sdfModelRootNode_t *modelRoot;
  dds3ModelEffectCtrlr_t *effects;
  sdfVector4_t v12;

  w = aColor->w;
  z = aColor->z;
  y = aColor->y;
  x = aColor->x;
  modelRoot = aHandle->modelRoot;
  modelRoot->color.x = aColor->x;
  modelRoot->color.y = aColor->y;
  modelRoot->color.z = aColor->z;
  modelRoot->color.w = aColor->w;
  effects = aHandle->effects;
  if (!effects)
    return;
  goto LABEL_7;
  do
  {
LABEL_7:
    v12.x = 1.0;
    v12.y = 1.0;
    v12.z = 1.0;
    v12.w = w;
    mdlEffectSetColorSub(aHandle, effects, v12);
    effects = effects->next;
  }
  while (effects);
}

// 0x1d80200
void SetColor_And_EffAlp(dds3ModelHandle_t *aHandle, const sdfVector4_t *aColor, f32 _EffAlp) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  sdfModelRootNode_t *modelRoot;
  dds3ModelEffectCtrlr_t *effects;
  sdfVector4_t v14;

  w = aColor->w;
  z = aColor->z;
  y = aColor->y;
  x = aColor->x;
  modelRoot = aHandle->modelRoot;
  modelRoot->color.x = aColor->x;
  modelRoot->color.y = aColor->y;
  modelRoot->color.z = aColor->z;
  modelRoot->color.w = aColor->w;
  effects = aHandle->effects;
  if (!effects)
    return;
  goto LABEL_7;
  do
  {
LABEL_7:
    v14.x = 1.0;
    v14.y = 1.0;
    v14.z = 1.0;
    v14.w = EffAlp;
    mdlEffectSetColorSub(aHandle, effects, v14);
    effects = effects->next;
  }
  while (effects);
}

// 0x1d80300
void mdlSetDitherAlphaUse(dds3ModelHandle_t *aHandle, bool aDitherAlpha) {
  aHandle->modelRoot->ditherAlpha = aDitherAlpha;
}

// 0x1d80310
void mdlSetDitherAlpha(dds3ModelHandle_t *aHandle, f32 aDitherAlpha) {
  sdfModelRootNode_t *modelRoot;

  modelRoot = aHandle->modelRoot;
  modelRoot->color.w = aDitherAlpha;
  modelRoot->ditherAlpha = 1;
}

// 0x1d80330
void mdlSetDissolveAlpha(dds3ModelHandle_t *aHandle, f32 aDissolveAlpha) {
  aHandle->modelRoot->dissolve = 1.0 - aDissolveAlpha;
}

// 0x1d80350
void mdlSetColorChroma(dds3ModelHandle_t *aHandle, u32 aColorChroma) {
  int8x16_t v3;
  int8x16_t v8;
  uint32x4_t v9;
  float32x4_t v10;

  v3.n128_u32[0] = aColorChroma;
  v8.n128_u64[0] = 0xFF000000FFLL;
  v8.n128_u64[1] = 0xFF000000FFLL;
  v3.n128_u32[1] = aColorChroma >> 8;
  v3.n128_u32[2] = HIWORD(aColorChroma);
  v9 = vandq_s8(v3, v8);
  v9.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(aColorChroma), 0x18u).n128_u32[3];
  v10.n128_u64[0] = 0x3C0000003C000000LL;
  v10.n128_u64[1] = 0x3C0000003C000000LL;
  aHandle->modelRoot->color_chroma = (struct sdfVector4_t)vmulq_f32(vcvtq_f32_u32(v9), v10);
}

// 0x1d80440
void SetColorChroma(dds3ModelHandle_t *aHandle, const sdfVector4_t *aColorChroma) {
  aHandle->modelRoot->color_chroma = aColorChroma;
}

// 0x1d80460
void mdlSetStoneUse(dds3ModelHandle_t *aHandle, bool aStoneUse) {
  aHandle->modelRoot->stoneUse = aStoneUse;
}

// 0x1d80470
void mdlMotionPause(dds3ModelHandle_t *aHandle) {
  sdfMotionCtrlr_t *i;

  for (i = aHandle->modelRoot->motion; i; i = i->next)
    sdfMotionPause(i);
}

// 0x1d804b0
void mdlMotionPauseOff(dds3ModelHandle_t *aHandle) {
  sdfMotionCtrlr_t *i;

  for (i = aHandle->modelRoot->motion; i; i = i->next)
    sdfMotionPauseOff(i);
}

// 0x1d804f0
bool mdlHasMotionEx(dds3ModelHandle_t *aHandle, s32 aGroup) {
  u16 v3;
  sdfMotionCtrlr_t *motion;

  v3 = aGroup;
  motion = aHandle->modelRoot->motion;
  if (!motion)
    return motion != 0;
  do
  {
    if (v3 == motion->userId)
      break;
    motion = motion->next;
  }
  while (motion);
  return motion != 0;
}

// 0x1d805a0
MODELTYPE mdlGetMajorNum(dds3ModelHandle_t *aHandle) {
  return aHandle->resrc->major;
}

// 0x1d805b0
s32 mdlGetMinorNum(dds3ModelHandle_t *aHandle) {
  return aHandle->resrc->minor;
}

// 0x1d805c0
s32 mdlGetNumOfCut(dds3ModelHandle_t *aHandle, s32 aGroup) {
  u16 v3;
  sdfMotionCtrlr_t *motion;

  v3 = aGroup;
  motion = aHandle->modelRoot->motion;
  if (!motion)
    return 0;
  while (v3 != motion->userId)
  {
    motion = motion->next;
    if (!motion)
      return 0;
  }
  return get_numOfCut(motion->playbook, 0);
}

// 0x1d806a0
void mdlSetBustup(dds3ModelHandle_t *aHandle, bool _IsBustUp) {
  aHandle->IsBustUp = IsBustUp;
}

// 0x1d806b0
void mdlSetMdlEffectNonStop(dds3ModelHandle_t *aHandle, bool _IsNonStop) {
  aHandle->IsMdlEffect_NonStop = IsNonStop;
}

// 0x1d806c0
static sdfPacDecodeResrcHandle_t *PackSet(sdfPacDecodeResrcHandle_t *resrc, MODELTYPE major, s32 minor, MODEL_REGFLAG regFlags) {
  Il2CppObject *v7;
  pbResourceUnit *unit;
  s64 naturalAligment;
  s32 v10;
  sdfPacDecodeResrcHandle_t *next;
  mdlEffectResrcList_t *v12;
  void **p_klass;
  s64 v14;
  char *magicCode;
  void *v16;
  s64 v18;
  Il2CppClass *v19;
  sdfPacDecodeResrcHandle_t *v21;
  s32 v23;
  void *extHeader;
  s64 v26;
  sdfMotionPlayBook_t *v27;
  s32 v28;
  s32 klass_low;
  s32 v30;
  u16 *klass;

  v7 = Allocate(mdlSetDef_t);
  _ctor(v7, 0);
  unit = resrc->unit;
  if (unit)
  {
    if (unit->klass->_2.naturalAligment < (u32)naturalAligment || unit->klass->_2.typeHierarchy[naturalAligment - 1] != Project_pbResourceUnit_PIB)
    {
      goto LABEL_38;
    }
  }
  klass = unit[1].klass;
  v10 = klass[10];
  v7[2].klass = klass;
  next = resrc->next;
  if (v10)
  {
    v12 = mdlEffectResrcListNew(v10);
    v7[2].monitor = v12;
    do
    {
      p_klass = &next->unit->klass;
      if (p_klass)
      {
        if (*((u8 *)*p_klass + 304) < (u32)v14 || *(Project_libsdf_pbResourceUnit_BIN_c **)(*((u64 *)*p_klass + 25) + 8 * v14 - 8) != Project_libsdf_pbResourceUnit_BIN)
        {
          p_klass = 0;
        }
      }
      magicCode = next->header->magicCode;
      if (!op_Equality(magicCode, "P2A", 0))
      {
        if (op_Equality(magicCode, "D3P", 0))
        {
          v16 = p_klass[4];
          mdlEffectCreateResrc_D3P(v12, v16);
        }
        else if (op_Equality(magicCode, "IPU", 0))
        {
          mdlEffectCreateResrc_IPU(v12, next->unit);
        }
      }
      next = next->next;
      --v10;
    }
    while (v10);
  }
  unit = next->unit;
  if (unit)
  {
    if (unit->klass->_2.naturalAligment < (u32)v18 || unit->klass->_2.typeHierarchy[v18 - 1] != Project_libsdf_pbResourceUnit_MODEL)
    {
      goto LABEL_38;
    }
  }
  v19 = unit[1].klass;
  v7[1].klass = v19;
  v21 = next->next;
  RegistModelSet(major, minor, regFlags, v7);
  if (klass[11])
  {
    v23 = klass[11] + 1;
    while (1)
    {
      unit = v21->unit;
      extHeader = unit->extHeader;
      if (unit->klass->_2.naturalAligment < (u32)v26 || unit->klass->_2.typeHierarchy[v26 - 1] != Project_libsdf_pbResourceUnit_MOTION)
      {
        break;
      }
      v27 = unit[1].klass;
      v28 = SWORD2(extHeader[1].klass);
      klass_low = LOWORD(extHeader[1].klass);
      v30 = WORD1(extHeader[1].klass);
      RegistMotion(major, minor, regFlags, v28, klass_low, v30, v27);
      v21 = v21->next;
      if (--v23 <= 1)
        return v21;
    }
LABEL_38:
  }
  return v21;
}

// 0x1d80ae0
static void FileCbFree(mdlFileLoadCb_t *cb) {
  pacFileHandle_t *pacHandle;

  pacHandle = cb->pacHandle;
  pacHandleFree(pacHandle);
}

// 0x1d80b70
static void FileLoadCallback(fileHandle_t *fileHandle, void *data) {
  pacFileHandle_t *p_monitor;
  u16 klass;
  s32 v10;
  s32 klass_high;
  Il2CppClass *element_class;
  Project_fileHandle_t_Parm_c *v14;
  pacFileHandle_t *v16;

  data[1].monitor = fileHandle;
  p_monitor = &data[1].monitor;
  klass = data[1].klass;
  v10 = WORD1(data[1].klass);
  klass_high = HIDWORD(data[1].klass);
  element_class = fileHandle[1].klass->_1.element_class;
  PackSet(element_class, klass, v10, klass_high);
  UnRegLoading((u16)data[1].klass, WORD1(data[1].klass));
  v14 = data[2].klass;
  if (v14)
  {
    (v14->_1.namespaze)(v14->_1.element_class, data[2].monitor, *(u64 *)&v14->_1.byval_arg.bits);
    v16 = p_monitor;
    pacHandleFree(v16);
    return;
  }
}

// 0x1d7df80
static s32 FileLoad(MODELTYPE major, s32 minor, MODEL_REGFLAG regFlags, char *filename, CallbackFunc callback, void *parm) {
  s16 v11;
  mdlFileLoadCb_t *v13;
  char *v14;
  fileEndCallback_t v15;
  pacFileHandle_t *v16;
  u64 *v17;
  pacFileHandle_t *v19;

  v11 = minor;
  v13 = Allocate(mdlFileLoadCb_t);
  v13->major = major;
  v13->callback = callback;
  v13->minor = v11;
  v13->regFlags = regFlags;
  v13->callbackParm = parm;
  if (major <= 7u && ((1 << major) & 0x8E) != 0)
  {
    v14 = Concat_54766928(filename, "_pb", 0);
    filename = Concat_54766928(filename, "_0.PBN", 0);
  }
  else
  {
    v14 = filename;
  }
  v15 = Allocate(fileEndCallback_t);
  _ctor(v15, 0, Method_Project_mdl_FileLoadCallback__, 0);
  v16 = pacLoadEx(v14, filename, 0, v15, v13);
  v13->pacHandle = v16;
  v17 = &v13->pacHandle;
  if (!callback)
  {
    pacSync(v16);
    v19 = *v17;
    pacHandleFree(v19);
    return 0;
  }
  return 0;
}

// 0x1d80d80
void mdlPackDecode(MODELTYPE major, s32 minor, MODEL_REGFLAG regFlags, void *buff, s32 leng) {
  sdfPacDecodeCb_t *v11;
  sdfPacDecodeResrcHandle_t *resrcHead;

  v11 = Allocate(sdfPacDecodeCb_t);
  _ctor(v11, 0);
  sdfPacInit(v11, 0);
  if ((regFlags & 2) != 0)
    sdfPacSetStay(v11);
  sdfPacDecode(v11, buff, leng);
  resrcHead = v11->resrcHead;
  PackSet(resrcHead, major, minor, regFlags);
  sdfPacFree(v11);
}

// 0x1d80e80
void PackDecode(MODELTYPE major, s32 minor, MODEL_REGFLAG regFlags, sdfPacDecodeResrcHandle_t *resrc) {
  pbResourceUnit *unit;
  void *klass;

  unit = resrc->unit;
    unit = 0;
  klass = unit[1].klass;
  if (!klass)
  mdlPackDecode(major, minor, regFlags, klass, 0);
}
