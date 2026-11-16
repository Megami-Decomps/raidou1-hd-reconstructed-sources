#include "types.h"
#include "libsdf.h"
#include "sdfmotion.h"
#include "sdfvsync.h"

typedef struct sdfModelRootNode_t sdfModelRootNode_t;
typedef struct sdfMotionCtrlr_t sdfMotionCtrlr_t;
typedef struct sdfMotionPlayBook_t sdfMotionPlayBook_t;

static void PreSeek(sdfMotionCtrlr_t *aCtrlr, f32 aFrame);
static void _Seek(sdfMotionCtrlr_t *aCtrlr, f32 aFrame);

// 0x2262870
sdfMotionCtrlr_t *sdfMotionCtrlrNew(sdfModelRootNode_t *aModel, sdfMotionPlayBook_t *aBook) {
  u64 *v5;
  sdfMotStateNotice *v6;
  sdfMotionCtrlr_t *motion;

  v5 = Allocate(sdfMotionCtrlr_t);
  v6 = Allocate(sdfMotStateNotice);
  _ctor(v6, 0);
  v5[15] = v6;
  _ctor(v5, 0);
  motion = aModel->motion;
  v5[2] = motion;
  aModel->motion = (sdfMotionCtrlr_t *)v5;
  v5[3] = aModel;
  v5[4] = aBook;
  *((u32 *)v5 + 17) = 0;
  *((u32 *)v5 + 13) = 1065353216;
  *((u8 *)v5 + 72) = 0;
  *((u16 *)v5 + 56) = 0;
  v5[7] = 0;
  *((u8 *)v5 + 64) = 0;
  *(u64 *)((char *)v5 + 76) = 0;
  *((u8 *)v5 + 84) = 0;
  v5[11] = 0;
  *((u8 *)v5 + 96) = 0;
  return (sdfMotionCtrlr_t *)v5;
}

// 0x2262a20
void sdfMotionCtrlrFree(sdfMotionCtrlr_t *aCtrlr) {
  sdfModelRootNode_t *rootNode;
  sdfMotionCtrlr_t *p_motion;
  sdfMotionCtrlr_t *v4;
  sdfMotionCtrlr_t *motion;
  sdfMotionCtrlr_t *v6;
  sdfMotionCtrlr_t *v7;
  sdfMotionCtrlr_t *next;

  if (aCtrlr)
  {
    rootNode = aCtrlr->rootNode;
    if (rootNode)
    {
      motion = rootNode->motion;
      p_motion = &rootNode->motion;
      v4 = motion;
      if (motion == aCtrlr)
      {
        next = aCtrlr->next;
        p_motion = next;
      }
      else
      {
        while (v4)
        {
          v6 = v4;
          v4 = v4->next;
          if (v4 == aCtrlr)
          {
            v7 = aCtrlr->next;
            v6->next = v7;
            return;
          }
        }
      }
    }
  }
}

// 0x2262a80
void sdfMotionChangeBlend(sdfMotionCtrlr_t *aCtrlr, s32 aCutNum, SDF_MOTION aType, f32 aPreFrame, f32 aBlendLeng) {
  void *animator;
  s16 userId;
  sdfMotStateNotice *notice;
  Il2CppObject *v15;
  Il2CppObject *v16;
  char *v17;
  s32 v18;
  sdfMotStateNotice *v19;
  f32 v20;
  f32 v21;
  sdfMotionCutDef_t *cutList;
  sdfMotionPlayBook_t *playbook;
  s32 v24;
  s16 data;

  animator = aCtrlr->rootNode->modelObj->animator;
  if (op_Equality(animator, 0, 0))
    return;
  userId = aCtrlr->userId;
  aCtrlr->cutNumber = aCutNum;
  notice = aCtrlr->notice;
  data = userId;
  v24 = aCutNum;
  v15 = Box(s16, &data);
  v16 = Box(s32, &v24);
  v17 = Format_54759776("anim{0:x1}{1:x2}", v15, v16, 0);
  v18 = StringToHash(v17, 0);
  v19 = aCtrlr->notice;
  v20 = -aPreFrame;
  notice->hash = v18;
  aCtrlr->frame_Animator = 0.0;
  v21 = fmaxf(aBlendLeng, 0.0);
  v19->single = aType == 0;
  v19->play = 0.0;
  if (aBlendLeng <= 0.0)
    v20 = 0.0;
  aCtrlr->stat = 1;
  playbook = aCtrlr->playbook;
  aCtrlr->frame = v20;
  aCtrlr->blendLength = v21;
  aCtrlr->blendPreLength = v20;
  cutList = playbook->cutList;
  LOWORD(playbook) = -36;
  if (SLODWORD(cutList->max_length) > aCutNum && (u16)LODWORD(cutList->max_length) > aCutNum)
  {
    playbook = cutList[aCutNum];
    if (playbook)
      LODWORD(playbook) = playbook->cutList;
    else
      LOWORD(playbook) = -36;
  }
  aCtrlr->frameLength = (u16)playbook;
}

// 0x2262c80
void sdfMotionChange(sdfMotionCtrlr_t *aCtrlr, s32 aCutNum, SDF_MOTION aType) {
  sdfMotionChangeBlend(aCtrlr, aCutNum, aType, 0.0, 0.0);
}

// 0x2262c90
void sdfMotionSeek(sdfMotionCtrlr_t *aCtrlr, f32 aFrame) {
  void *animator;
  void *gameObject;
  sdfModelRootNode_t *rootNode;
  void *v9;
  sdfMotionCtrlr_t *motion;
  u32 v11;
  f32 v12;

  animator = aCtrlr->rootNode->modelObj->animator;
  if (!!op_Inequality(animator, 0, 0))
  {
    gameObject = get_gameObject(aCtrlr->rootNode->modelObj, 0);
    if (get_activeSelf(gameObject, 0))
    {
      rootNode = aCtrlr->rootNode;
      v9 = rootNode->modelObj->animator;
      motion = rootNode->motion;
      SetControler(v9, motion, 0);
      LOWORD(v11) = aCtrlr->frameLength;
      Play_60667376(aCtrlr->rootNode->modelObj->animator, aCtrlr->notice->hash, aCtrlr->userId2, aFrame / (f32)v11, 0);
    }
  }
  v12 = 0.0;
  aCtrlr->frame = aFrame;
  aCtrlr->stat = 4;
  if (aFrame >= 0.0)
    v12 = aCtrlr->speed + aCtrlr->speed;
  aCtrlr->frameSpeed = v12;
}

// 0x2262e30
static void PreSeek(sdfMotionCtrlr_t *aCtrlr, f32 aFrame) {
  void *animator;
  void *gameObject;
  sdfModelRootNode_t *rootNode;
  void *v9;
  sdfMotionCtrlr_t *motion;
  bool v11;
  u32 v12;
  s32 BlendTree1D_HashID;
  f32 blendLength;

  animator = aCtrlr->rootNode->modelObj->animator;
  if (!op_Inequality(animator, 0, 0))
    return;
  gameObject = get_gameObject(aCtrlr->rootNode->modelObj, 0);
  if (!get_activeSelf(gameObject, 0))
    return;
  rootNode = aCtrlr->rootNode;
  v9 = rootNode->modelObj->animator;
  motion = rootNode->motion;
  v11 = SetControler(v9, motion, 0);
  if (aCtrlr->BlendTree1D_UpdateFlg)
  {
    if (aCtrlr->BlendTree1D_HashFlg)
    {
      BlendTree1D_HashID = aCtrlr->BlendTree1D_HashID;
    }
    else
    {
      BlendTree1D_HashID = StringToHash("BlendTree1D", 0);
      aCtrlr->BlendTree1D_HashID = BlendTree1D_HashID;
      aCtrlr->BlendTree1D_HashFlg = 1;
    }
    SetFloat(aCtrlr->rootNode->modelObj->animator, BlendTree1D_HashID, aCtrlr->BlendTree1D, 0);
    aCtrlr->BlendTree1D_UpdateFlg = 0;
  }
  if (aCtrlr->BlendTree2D_UpdateFlg)
  {
    if (!aCtrlr->BlendTree2D_HashFlg)
    {
      aCtrlr->BlendTree2DX_HashID = StringToHash("BlendTree2DX", 0);
      aCtrlr->BlendTree2DY_HashID = StringToHash("BlendTree2DY", 0);
      aCtrlr->BlendTree2D_HashFlg = 1;
    }
    SetFloat(aCtrlr->rootNode->modelObj->animator, aCtrlr->BlendTree2DX_HashID, aCtrlr->BlendTree2DX, 0);
    SetFloat(aCtrlr->rootNode->modelObj->animator, aCtrlr->BlendTree2DY_HashID, aCtrlr->BlendTree2DY, 0);
    aCtrlr->BlendTree2D_UpdateFlg = 0;
  }
  if (aCtrlr->stat == 1)
  {
    blendLength = aCtrlr->blendLength;
    if (blendLength > 0.0)
    {
      CrossFadeInFixedTime(aCtrlr->rootNode->modelObj->animator, aCtrlr->notice->hash, (f32)(blendLength * 0.016666668) / aCtrlr->speed, aCtrlr->userId2, 0.0, 0);
      return;
    }
  }
  else if (!v11)
  {
    return;
  }
  LOWORD(v12) = aCtrlr->frameLength;
  Play_60667376(aCtrlr->rootNode->modelObj->animator, aCtrlr->notice->hash, aCtrlr->userId2, (f32)(aCtrlr->skipframe + aFrame) / (f32)v12, 0);
}

// 0x2262e00
static void _Seek(sdfMotionCtrlr_t *aCtrlr, f32 aFrame) {
  f32 v3;

  v3 = 0.0;
  aCtrlr->frame = aFrame;
  aCtrlr->stat = 4;
  if (aFrame >= 0.0)
    v3 = aCtrlr->speed + aCtrlr->speed;
  aCtrlr->frameSpeed = v3;
}

// 0x2263100
void sdfMotionNext(sdfMotionCtrlr_t *aCtrlr) {
  s32 stat;
  f32 blendPreLength;
  f32 v5;
  f32 v6;
  s32 frameLength;
  void *animator;
  u32 v11;
  f32 speed;
  f32 length;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 normalizedTime;
  f32 v20;
  f32 v21;
  UnityEngine_AnimatorStateInfo_o v22;
  UnityEngine_AnimatorStateInfo_o v23;
  UnityEngine_AnimatorStateInfo_o v24;

  stat = aCtrlr->stat;
  memset(&v24, 0, sizeof(v24));
  memset(&v23, 0, sizeof(v23));
  if ((u32)(stat - 5) < 2)
  {
    aCtrlr->frameSpeed = 0.0;
    return;
  }
  if (stat == 4)
  {
    v6 = aCtrlr->frame + aCtrlr->speed;
    frameLength = aCtrlr->frameLength;
    animator = aCtrlr->rootNode->modelObj->animator;
    if (v6 < 0.0 || frameLength != 65500)
    {
      if (op_Inequality(animator, 0, 0))
      {
        GetCurrentAnimatorStateInfo(&v22, animator, 0, 0);
        v23 = v22;
        v11 = COERCE_UNSIGNED_INT(get_length(&v23, 0)) & 0x7FFFFFFF;
        speed = aCtrlr->speed;
        if (v11 == 2139095040)
        {
          if (speed > 0.0)
            aCtrlr->frame_Animator = 0.0;
        }
        else if (speed > 0.0)
        {
          v18 = get_length(&v23, 0) / 0.016666668;
          normalizedTime = get_normalizedTime(&v23, 0);
          aCtrlr->frame_Animator = sub_188E3E0(v18 * normalizedTime);
        }
      }
LABEL_34:
      v20 = (u16)frameLength;
      if (v6 >= v20)
      {
        if (aCtrlr->notice->single)
        {
          if ((u16)frameLength)
          {
            PreSeek(aCtrlr, v20);
            v21 = aCtrlr->speed;
            aCtrlr->frame = v20;
            aCtrlr->frameSpeed = v21 + v21;
          }
          aCtrlr->stat = 5;
          return;
        }
        *(u64 *)&aCtrlr->blendLength = 0;
        if ((u16)frameLength)
        {
          do
            v6 = v6 - v20;
          while (v6 >= v20);
        }
      }
      PreSeek(aCtrlr, v6);
      v5 = 0.0;
      aCtrlr->frame = v6;
      aCtrlr->stat = 4;
      if (v6 < 0.0)
        goto LABEL_8;
      goto LABEL_7;
    }
    GetCurrentAnimatorStateInfo(&v22, aCtrlr->rootNode->modelObj->animator, 0, 0);
    v24 = v22;
    length = get_length(&v24, 0);
    v14 = 0.0;
    v15 = aCtrlr->speed;
    if ((LODWORD(length) & 0x7FFFFFFF) == 0x7F800000)
    {
      v16 = 0.0;
      if (v15 <= 0.0)
      {
LABEL_27:
        if (v6 == 0.0 && aCtrlr->notice->single || get_normalizedTime(&v24, 0) < 1.0)
        {
          LOWORD(frameLength) = -36;
        }
        else
        {
          LOWORD(frameLength) = (s32)v14;
        }
        goto LABEL_34;
      }
    }
    else
    {
      if (v15 <= 0.0)
        goto LABEL_27;
      v16 = get_length(&v24, 0) / 0.016666668;
      v17 = get_normalizedTime(&v24, 0);
      v14 = sub_188E3E0(v16 * v17);
    }
    aCtrlr->frame_Animator = v14;
    v14 = v16;
    goto LABEL_27;
  }
  if (stat == 1)
  {
    PreSeek(aCtrlr, aCtrlr->blendPreLength);
    blendPreLength = aCtrlr->blendPreLength;
    v5 = 0.0;
    aCtrlr->stat = 4;
    aCtrlr->frame = blendPreLength;
    if (blendPreLength < 0.0)
    {
LABEL_8:
      aCtrlr->frameSpeed = v5;
      return;
    }
LABEL_7:
    v5 = aCtrlr->speed + aCtrlr->speed;
    goto LABEL_8;
  }
}

// 0x2263440
void sdfMotionPause(sdfMotionCtrlr_t *aCtrlr) {
  s32 stat;

  stat = aCtrlr->stat;
  if (stat != 6)
  {
    aCtrlr->statBeforePause = stat;
    aCtrlr->stat = 6;
  }
}

// 0x2263460
void sdfMotionPauseOff(sdfMotionCtrlr_t *aCtrlr) {
  if (aCtrlr->stat == 6)
    aCtrlr->stat = aCtrlr->statBeforePause;
}

// 0x2263480
void sdfMotionUpdate(sdfModelRootNode_t *modelRoot) {
  void *animator;
  sdfMotionCtrlr_t *i;
  sdfMotStateNotice *notice;
  f32 frameSpeed;
  void *v9;
  sdfMotionCtrlr_t *j;

  animator = modelRoot->modelObj->animator;
  if (op_Equality(animator, 0, 0))
    return;
  for (i = modelRoot->motion; i; notice->play = notice->play + frameSpeed)
  {
    notice = i->notice;
    frameSpeed = i->frameSpeed;
    i = i->next;
  }
  if (drawSkip)
    return;
  set_enabled(modelRoot->modelObj->animator, 1, 0);
  v9 = modelRoot->modelObj->animator;
  Update(v9, frameTime, 0);
  set_enabled(modelRoot->modelObj->animator, 0, 0);
  for (j = modelRoot->motion; j; j = j->next)
    j->notice->play = 0.0;
}
